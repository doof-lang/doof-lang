// Member access, indexing, static receivers, dot shorthand, and union-alias
// JSON decoders.

import { canBeAbsent, hasFailureLayer, hasPresentValue, presentType } from "./absence-types"
import type { TypeAliasDeclaration } from "./ast"
import { CheckedMember, ClassDeclaration, DotShorthand, EnumDeclaration, Expression, Identifier, IndexExpression, MemberExpression, NamedType } from "./ast"
import { isTypeParameterName } from "./ast-walk"
import { forcedValue, optionalAccessType, optionalConversion } from "./checker-absence"
import { finish, typeArgumentArityMessage, typeError } from "./checker-common"
import { checkExpression } from "./checker-expressions"
import { instantiateGenericReference } from "./checker-generic-references"
import { classModuleFor } from "./checker-interfaces"
import { hasNoneMember } from "./checker-operators"
import { indexType, jsonPrograms, resolveBoundStaticMember, serialDecodeType, resolveMember } from "./checker-resolution"
import { resolveType, resolveTypeArguments, validateTypeArgumentConstraints } from "./checker-annotations"
import { CheckerState } from "./checker-state"
import { declarationFor, lookup } from "./checker-symbols"
import { displayTypeName, neverType, primitive, sameType, typeName, unionType, unknownType } from "./checker-types"
import { checkerSemanticSpan } from "./checker-validation"
import { unionAliasJsonDiscriminator } from "./json-semantics"
import type { Symbol } from "./semantic"
import { Binding, ClassType, EnumType, FunctionType, ResolvedType, Scope, UnionResolvedType, WeakResolvedType } from "./semantic"

/** Checks 'object.member', including '?.' and '!.' over absent and weak receivers. */
export function checkMember(state: CheckerState, member: MemberExpression, scope: Scope, expected: ResolvedType | none, calleePosition: bool): ResolvedType {
  let objectType = unknownType()
  case member.object {
    identifier: Identifier -> {
      // Bindings shadow alias spellings. Resolve capabilities from the
      // selected binding instead of the identifier text alone.
      localBinding := lookup(scope, identifier.name)
      if localBinding == none && member.property == "fromSerialValue" && jsonAliasSymbol(state, identifier.name) != none {
        return checkUnionAliasJsonMember(state, member, identifier, jsonAliasSymbol(state, identifier.name)!, scope)
      } else {
        objectType = checkExpression(state, member.object, scope, none)
      }
    }
    _ -> { objectType = checkExpression(state, member.object, scope, none) }
  }
  if member.completionPoint { return finish(state, member, unknownType()) }
  if objectType.kind == "never" { return finish(state, member, neverType()) }
  let weakReceiver: WeakResolvedType | none = none
  let nullableReceiver = false
  // 'x!.m' is '(x!).m' for every absent receiver, and 'r?.m' is '(r?)?.m'
  // when the receiver has a Result layer, so lowering reuses the postfix
  // step. Weak references keep their own checked access.
  if member.force && canBeAbsent(objectType) || member.optional && hasFailureLayer(objectType) {
    if !hasPresentValue(objectType) {
      typeError(state, "Cannot access member \"" + member.property + "\" on " + typeName(objectType) + ": the Result has no success value", member.span)
      return finish(state, member, unknownType())
    }
    if member.optional {
      member.object = optionalConversion(state, member.object, objectType)
      nullableReceiver = true
      objectType = presentType(objectType)
      member.resolvedOptionalReceiver = objectType
    } else {
      member.object = forcedValue(state, member.object, objectType)
      member.force = false
      objectType = presentType(objectType)
    }
  } else if member.force && objectType.kind != "weak" && objectType.kind != "unknown" {
    typeError(state, "Force access '!.' requires a nullable or Result receiver, got " + typeName(objectType), member.span)
    member.force = false
  }
  case objectType {
    weak_: WeakResolvedType -> {
      weakReceiver = weak_
      objectType = weakAccessTarget(weak_.inner)
      if !member.optional && !member.force {
        typeError(state, "Weak reference member access requires '?.' or '!.'", member.span)
      }
    }
    union_: UnionResolvedType -> {
      if member.optional && !nullableReceiver {
        unwrapped := weakAccessTarget(union_)
        if !sameType(unwrapped, union_) {
          objectType = unwrapped
          nullableReceiver = true
          member.resolvedOptionalReceiver = unwrapped
        }
      } else if !member.optional && !member.force && hasNoneMember(state, union_) {
        // Member resolution skips the none arm so '?.' and '!.' can share
        // it; a plain '.' must not read through an absent value.
        typeError(state, "Cannot access member \"" + member.property + "\" on possibly-none value of type \"" + typeName(objectType) + "\"; use '?.', '!.', or narrow it first", member.span)
      }
    }
    _ -> { }
  }
  case member.object {
    identifier: Identifier -> {
      if member.property == "parse" && legacyNumericParseType(identifier) {
        replacement := if identifier.name == "byte" then "parseByte" else
          if identifier.name == "int" then "parseInt" else
          if identifier.name == "long" then "parseLong" else
          if identifier.name == "float" then "parseFloat" else "parseDouble"
        typeError(state, identifier.name + ".parse was removed; import " + replacement + " from \"std/parse\"", member.span)
        return finish(state, member, unknownType())
      }
    }
    _ -> { }
  }
  if member.receiverTypeArgs.length > 0 { objectType = explicitStaticReceiver(state, member, objectType, scope) }
  diagnosticCount := state.diagnostics.length
  boundStatic := if isTypeParameterName(member.object) then resolveBoundStaticMember(state, objectType, member.property) else none
  selected := if boundStatic != none then boundStatic! else resolveMember(state, objectType, member.property, member.span)
  member.resolvedMember = selected
  let memberValue = selected.type_!
  if memberValue.kind == "unknown" && objectType.kind != "unknown" && state.diagnostics.length == diagnosticCount {
    typeError(state, "Type \"" + typeName(objectType) + "\" has no member \"" + member.property + "\"", member.span)
  }
  member.resolvedStaticOwner = selected.staticOwner
  if member.resolvedStaticOwner != none && !isNamedStaticReceiver(member.object) {
    typeError(state, "Static member '" + member.property + "' must be accessed through its class: use '" + member.resolvedStaticOwner!.name + "." + member.property + "'", member.span)
  }
  if member.resolvedStaticOwner == none && isNamedStaticReceiver(member.object) && selected.instance {
    typeError(state, "Instance member '" + member.property + "' cannot be accessed through a class", member.span)
  }
  // The implied JSON members on a type parameter keep their static/instance
  // split: `T.fromSerialValue(...)` but `value.toSerialObject()`.
  if objectType.kind == "type-parameter" {
    typeReceiver := isTypeParameterName(member.object)
    if typeReceiver && member.property == "toSerialObject" {
      typeError(state, "Instance member 'toSerialObject' cannot be accessed through type parameter \"" + typeName(objectType) + "\"; call it on a value", member.span)
    } else if !typeReceiver && member.property == "fromSerialValue" {
      typeError(state, "Static member 'fromSerialValue' cannot be accessed through a value; use '" + typeName(objectType) + ".fromSerialValue'", member.span)
    }
  }
  case objectType {
    _: EnumType -> {
      namedReceiver := isNamedStaticReceiver(member.object)
      staticMember := member.property == "values" || member.property == "fromName" || member.property == "fromValue" || member.property == "fromSerialValue"
      if namedReceiver && (member.property == "name" || member.property == "value" || member.property == "toSerialValue") {
        typeError(state, "Instance member '" + member.property + "' cannot be accessed through an enum type", member.span)
      } else if !namedReceiver && staticMember {
        typeError(state, "Static enum member '" + member.property + "' cannot be accessed through a value", member.span)
      }
      if !namedReceiver && enumVariantMember(state, objectType, member.property) {
        typeError(state, "Enum variant '" + member.property + "' cannot be accessed through a value", member.span)
      }
    }
    _ -> { }
  }
  member.resolvedCallableField = selected.field
  memberValue = instantiateGenericReference(state, member, memberValue, expected, scope, calleePosition)
  // A function-valued member reached through '?.' is absent with its
  // receiver unless a call short-circuits it as a whole. Any other value read
  // through an absent receiver, or through a weak one with '?.', is absent too.
  optionalValue := if memberValue.kind == "function"
    then !calleePosition && member.optional && (weakReceiver != none || nullableReceiver)
    else nullableReceiver || (weakReceiver != none && member.optional)
  if !optionalValue { return finish(state, member, memberValue) }
  member.resolvedOptionalValue = memberValue
  return finish(state, member, optionalAccessType(memberValue))
}

/** Checks 'object[index]', including '?[]' over absent receivers. */
export function checkIndex(state: CheckerState, index: IndexExpression, scope: Scope): ResolvedType {
  let objectType = checkExpression(state, index.object, scope, none)
  indexValueType := checkExpression(state, index.index, scope, primitive("int"))
  let optionalReceiver = false
  if index.optional {
    if hasFailureLayer(objectType) {
      // 'r?[i]' is '(r?)?[i]'.
      if !hasPresentValue(objectType) {
        typeError(state, "Cannot index " + typeName(objectType) + ": the Result has no success value", index.span)
        return finish(state, index, unknownType())
      }
      index.object = optionalConversion(state, index.object, objectType)
      objectType = presentType(objectType)
      optionalReceiver = true
      index.resolvedOptionalReceiver = objectType
    } else {
      case objectType {
        union_: UnionResolvedType -> {
          if hasNoneMember(state, union_) {
            objectType = weakAccessTarget(union_)
            optionalReceiver = true
            index.resolvedOptionalReceiver = objectType
          }
        }
        _ -> { }
      }
    }
  }
  resolved := indexType(state, objectType, indexValueType, index.span)
  if objectType.kind == "never" || indexValueType.kind == "never" { return finish(state, index, neverType()) }
  if optionalReceiver && resolved.kind != "unknown" {
    index.resolvedOptionalValue = resolved
    return finish(state, index, optionalAccessType(resolved))
  }
  return finish(state, index, resolved)
}

/**
 * Specializes `Channel<string>.member` to the named instantiation. Explicit
 * type arguments are only meaningful on a generic class name, whose statics
 * exist once per instantiation.
 */
function explicitStaticReceiver(state: CheckerState, member: MemberExpression, objectType: ResolvedType, scope: Scope): ResolvedType {
  resolvedArgs := resolveTypeArguments(state, member.receiverTypeArgs, scope)
  case objectType {
    class_: ClassType -> {
      declaration := declarationFor(state.result, class_.symbol)
      if declaration != none && class_.typeArgs.length == 0 && isNamedStaticReceiver(member.object) {
        case declaration! {
          generic: ClassDeclaration -> {
            if generic.typeParams.length == 0 {
              typeError(state, "Class '" + generic.name + "' is not generic and takes no type arguments", member.span)
              return objectType
            }
            if resolvedArgs.length != generic.typeParams.length {
              typeError(state, typeArgumentArityMessage("Generic class '" + generic.name + "'", generic.typeParams.length, resolvedArgs.length), member.span)
              return unknownType()
            }
            validateTypeArgumentConstraints(state, generic.typeParams, generic.typeParamConstraints, resolvedArgs, member.span, classModuleFor(state.result, class_.symbol), scope)
            receiver := ClassType { name: class_.name, symbol: class_.symbol, typeArgs: resolvedArgs }
            member.resolvedStaticReceiver = receiver
            return receiver
          }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  if objectType.kind != "unknown" {
    typeError(state, "Type arguments are only allowed on a generic class name before a static member", member.span)
  }
  return objectType
}

function weakAccessTarget(type_: ResolvedType): ResolvedType {
  case type_ {
    union_: UnionResolvedType -> {
      let present: ResolvedType[] = []
      for member of union_.types { if member.kind != "none" { present.push(member) } }
      if present.length > 0 { return unionType(present) }
    }
    _ -> { }
  }
  return type_
}

function isNamedStaticReceiver(expression: Expression): bool {
  case expression {
    identifier: Identifier -> {
      if identifier.resolvedBinding == none { return false }
      binding := identifier.resolvedBinding!
      if binding.kind == "type-parameter" || binding.kind == "class" || binding.kind == "struct" || binding.kind == "interface" || binding.kind == "enum" { return true }
      if binding.kind == "import" && binding.symbol != none {
        kind := binding.symbol!.kind
        return kind == "class" || kind == "struct" || kind == "interface" || kind == "enum"
      }
    }
    _ -> { }
  }
  return false
}

function enumVariantMember(state: CheckerState, receiver: ResolvedType, property: string): bool {
  case receiver {
    enum_: EnumType -> {
      declaration := declarationFor(state.result, enum_.symbol)
      if declaration != none {
        case declaration! {
          owner: EnumDeclaration -> { for variant of owner.variants { if variant.name == property { return true } } }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  return false
}

export function checkDotShorthand(state: CheckerState, expression: DotShorthand, expected: ResolvedType | none, allowsNone: bool = false): ResolvedType {
  if expected == none {
    typeError(state, "Cannot resolve shorthand ." + expression.name + " without an expected class or enum type", expression.span)
    return finish(state, expression, unknownType())
  }
  case expected! {
    enum_: EnumType -> {
      declaration := declarationFor(state.result, enum_.symbol)
      let found = false
      if declaration != none {
        case declaration! {
          enumDeclaration: EnumDeclaration -> {
            for variant of enumDeclaration.variants { if variant.name == expression.name { found = true } }
          }
          _ -> { }
        }
      }
      if !found {
        typeError(state, "Enum \"" + enum_.name + "\" has no variant \"" + expression.name + "\"", expression.span)
        return finish(state, expression, unknownType())
      }
      expression.resolvedShorthandOwnerName = enum_.name
      expression.resolvedShorthandOwnerKind = "enum"
      expression.resolvedShorthandOwnerModule = enum_.symbol.module
      expression.resolvedShorthandOwnerNative = enum_.symbol.native_
      expression.resolvedShorthandOwnerCppName = enum_.symbol.nativeCppName
      return finish(state, expression, enum_)
    }
    class_: ClassType -> {
      diagnosticCount := state.diagnostics.length
      selected := resolveMember(state, class_, expression.name, expression.span)
      value := selected.type_!
      if selected.staticOwner == none {
        if state.diagnostics.length == diagnosticCount {
          typeError(state, "Type \"" + class_.name + "\" has no static member \"" + expression.name + "\"", expression.span)
        }
        return finish(state, expression, unknownType())
      }
      expression.resolvedShorthandOwnerName = class_.name
      expression.resolvedShorthandOwnerKind = "class"
      expression.resolvedShorthandOwnerModule = class_.symbol.module
      expression.resolvedShorthandOwnerNative = class_.symbol.native_
      expression.resolvedShorthandOwnerCppName = class_.symbol.nativeCppName
      expression.resolvedMember = selected
      // A class shorthand names a static field holding, or a static method
      // producing, the expected class: `T`, or `T | none` where the expected
      // type admits none.
      allowed := typeName(class_) + (if allowsNone then " or " + typeName(class_) + " | none" else "")
      case value {
        method: FunctionType -> {
          if !producesShorthandOwner(method.returnType, class_, allowsNone) {
            typeError(state, "Shorthand ." + expression.name + " must name a static method returning " + allowed + "; it returns " + displayTypeName(method.returnType), expression.span)
            return finish(state, expression, unknownType())
          }
        }
        _ -> {
          if value.kind != "unknown" && !producesShorthandOwner(value, class_, allowsNone) {
            typeError(state, "Shorthand ." + expression.name + " must name a static field of type " + allowed + "; it has type " + displayTypeName(value), expression.span)
            return finish(state, expression, unknownType())
          }
        }
      }
      return finish(state, expression, value)
    }
    union_: UnionResolvedType -> {
      // `T | none` resolves against its single class or enum arm.
      let owner: ResolvedType | none = none
      let owners = 0
      for member of union_.types {
        if member.kind == "class" || member.kind == "enum" { owner = member; owners += 1 }
        else if member.kind != "none" { owners += 2 }
      }
      if owners == 1 { return checkDotShorthand(state, expression, owner, true) }
    }
    _ -> { }
  }
  typeError(state, "Cannot resolve shorthand ." + expression.name + " for expected type \"" + typeName(expected!) + "\"", expression.span)
  return finish(state, expression, unknownType())
}

function producesShorthandOwner(returnType: ResolvedType, owner: ClassType, allowsNone: bool): bool {
  if sameType(returnType, owner) { return true }
  if !allowsNone { return false }
  case returnType {
    union_: UnionResolvedType -> {
      for member of union_.types { if member.kind != "none" && !sameType(member, owner) { return false } }
      return true
    }
    _ -> { return false }
  }
}

function legacyNumericParseType(identifier: Identifier): bool {
  if identifier.resolvedBinding == none || identifier.resolvedBinding!.kind != "builtin" { return false }
  name := identifier.name
  return name == "byte" || name == "int" || name == "long" || name == "float" || name == "double"
}

/** The type-alias symbol a value-position name refers to, if any. */
function jsonAliasSymbol(state: CheckerState, name: string): Symbol | none {
  info := state.info!
  for symbol of info.symbols {
    if symbol.name == name && symbol.kind == "type-alias" && typeAliasDeclaration(state, symbol) != none { return symbol }
  }
  for imported of info.imports {
    if imported.localName == name && !imported.typeOnly && imported.symbol != none && imported.symbol!.kind == "type-alias" && typeAliasDeclaration(state, imported.symbol!) != none {
      return imported.symbol
    }
  }
  return none
}

function typeAliasDeclaration(state: CheckerState, symbol: Symbol): TypeAliasDeclaration | none {
  declaration := declarationFor(state.result, symbol)
  if declaration == none { return none }
  case declaration! {
    alias: TypeAliasDeclaration -> { return alias }
    _ -> { return none }
  }
}

// `Alias.fromSerialValue(json)` decodes a named union of classes by the same
// literal-discriminator rule as interfaces. The alias names a type, so it is
// accepted only as this static receiver.
function checkUnionAliasJsonMember(state: CheckerState, member: MemberExpression, identifier: Identifier, symbol: Symbol, scope: Scope): ResolvedType {
  alias := typeAliasDeclaration(state, symbol)!
  aliasType := resolveType(state, NamedType { kind: "named-type", name: identifier.name, typeArgs: [], span: identifier.span }, state.info!, scope)
  // The binding records the alias symbol so lowering can qualify an imported decoder.
  identifier.resolvedBinding = Binding { name: identifier.name, kind: "type-alias", type_: aliasType, mutable: false, span: checkerSemanticSpan(alias.span), module: symbol.module, symbol }
  finish(state, identifier, aliasType)
  if aliasType.kind == "unknown" { return finish(state, member, unknownType()) }
  if alias.typeParams.length > 0 {
    typeError(state, "Automatic JSON deserialization is not available on generic type alias \"" + alias.name + "\"", member.span)
    return finish(state, member, unknownType())
  }
  if unionAliasJsonDiscriminator(alias, jsonPrograms(state.result)) == none {
    typeError(state, "Cannot deserialize type alias \"" + alias.name + "\": it must be a union of classes that share a literal-valued string field with distinct values (e.g. kind: \"variant\")", member.span)
    return finish(state, member, unknownType())
  }
  alias.needsJson = true
  member.resolvedJsonAlias = alias
  decoder := serialDecodeType(aliasType)
  member.resolvedMember = CheckedMember { type_: decoder, modulePath: symbol.module, owner: aliasType }
  return finish(state, member, decoder)
}
