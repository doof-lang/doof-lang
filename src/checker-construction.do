// One specialized constructor signature and field contract for all construction syntax.

import { checkArguments, propertyArguments, SuppliedArgument } from "./checker-arguments"
import { ClassType, InterfaceType, NoneType, UnknownType, FunctionParamType, FunctionType, ResolvedType, ResultResolvedType, Scope, TypeParameterType, UnionResolvedType } from "./semantic"

import { CheckedConstruction, ConstructionDefault, ClassDeclaration, ConstructExpression, ObjectProperty, FunctionDeclaration, SourceSpan, TupleLiteral } from "./ast"
import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { memberType, resolveType, validateTypeArgumentConstraints } from "./checker-resolution"
import { classModuleFor, findClassField, isAssignableWithInterfaces } from "./checker-interfaces"
import { containsString, declarationFor, hasObjectProperty, methodSignature, optionalResolvedType, valueSymbolFor, valueUseDiagnostic } from "./checker-symbols"
import { classType, noneType, resultArmExpectation, resultArmType, resultType, substituteTypeParams, typeName, unknownType } from "./checker-types"
import { finish, typeError } from "./checker-common"
import { checkPropertyValue, checkAssignableProperty, sameFixedFieldValue } from "./checker-properties"

export function resolveConstructor(state: CheckerState, owner: ClassType, useFactory: bool = true): CheckedConstruction {
  target := declarationFor(state.result, owner.symbol)
  let declaration: ClassDeclaration | none = none
  if target != none { case target! { class_: ClassDeclaration -> { declaration = class_ } _ -> { } } }
  let factory: FunctionDeclaration | none = none
  if useFactory && declaration != none {
    for method of declaration!.methods { if method.name == "constructor" { factory = method; break } }
  }
  if factory != none {
    signature := factory!.resolvedType ?? methodSignature(factory!, classModuleFor(state.result, owner.symbol), state.result, owner.symbol.typeParams)
    specialized := if declaration == none then signature else substituteTypeParams(signature, declaration!.typeParams, owner.typeArgs)
    case specialized {
      fn: FunctionType -> {
        let defaults: ConstructionDefault[] = []
        for parameter of factory!.params { defaults.push(ConstructionDefault { value: parameter.defaultValue }) }
        return CheckedConstruction { owner, declaration, factory, signature: fn, defaults }
      }
      _ -> { }
    }
  }
  let params: FunctionParamType[] = []
  let defaults: ConstructionDefault[] = []
  if declaration != none {
    for field of declaration!.fields {
      if field.static_ || field.const_ { continue }
      for name of field.names {
        defaults.push(ConstructionDefault { value: field.defaultValue })
        params.push(FunctionParamType { name, type_: memberType(state, owner, name, field.span, false), hasDefault: field.defaultValue != none })
      }
    }
  }
  return CheckedConstruction { owner, declaration, factory: none, signature: FunctionType { params, returnType: owner }, defaults }
}

export function insideConstructorFactory(scope: Scope, class_: ClassType): bool {
  let current: Scope | none = scope
  while current != none {
    if current!.functionName != "" {
      if current!.functionName != "constructor" { return false }
      if current!.thisType == none { return false }
      case current!.thisType! {
        owner: ClassType -> { return owner.symbol.module == class_.symbol.module && owner.symbol.name == class_.symbol.name }
        _ -> { return false }
      }
    }
    current = current!.parent
  }
  return false
}

export function checkConstruct(state: CheckerState, expression: ConstructExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  if expression.type_ == "Success" || expression.type_ == "Failure" {
    if expression.spread != none {
      expression.resolvedSpreadType = optionalResolvedType(checkExpression(state, expression.spread!, scope, none))
      typeError(state, expression.type_ + " construction does not support field spread", expression.spread!.span)
    }
    // A surrounding Result or matching arm types the payload; otherwise the
    // payload determines a standalone arm type.
    expectation := resultArmExpectation(expression.type_, expected)
    let valueType: ResolvedType = expectation.payload ?? noneType()
    for property of expression.args {
      valueType = checkAssignableProperty(state, property, scope, expectation.payload)
      if expectation.payload != none { valueType = expectation.payload! }
    }
    if expression.args.length == 0 && valueType.kind != "none" && valueType.kind != "unknown" {
      typeError(state, expression.type_ + " {} needs a value for " + typeName(expectation.result ?? resultArmType(expression.type_, valueType)), expression.span)
    }
    return finish(state, expression, expectation.result ?? resultArmType(expression.type_, valueType))
  }
  symbol := valueSymbolFor(state.info!, expression.type_)
  if symbol == none {
    message := valueUseDiagnostic(state.info!, expression.type_)
    typeError(state, if message == "" then "Unknown constructed type '" + expression.type_ + "'" else message, expression.span)
    return finish(state, expression, unknownType())
  }
  declaration := declarationFor(state.result, symbol!)
  if declaration != none {
    case declaration! {
      classDeclaration: ClassDeclaration -> { expression.resolvedClass = classDeclaration }
      _ -> { }
    }
  }
  let resolvedTypeArgs: ResolvedType[] = []
  for argument of expression.typeArgs { resolvedTypeArgs.push(resolveType(state, argument, state.info!, scope)) }
  if resolvedTypeArgs.length == 0 && expected != none {
    case expected! {
      expectedClass: ClassType -> {
        if expectedClass.symbol.module == symbol!.module && expectedClass.symbol.name == symbol!.name {
          for argument of expectedClass.typeArgs { resolvedTypeArgs.push(argument) }
        }
      }
      _ -> { }
    }
  }
  if expression.resolvedClass != none {
    validateTypeArgumentConstraints(state, expression.resolvedClass!.typeParams, expression.resolvedClass!.typeParamConstraints, resolvedTypeArgs, expression.span, classModuleFor(state.result, symbol!), scope)
  }
  constructed := classType(expression.type_, symbol!, resolvedTypeArgs)
  expression.resolvedConstructedType = optionalResolvedType(constructed)
  checkConstructionSpread(state, expression, scope)
  plan := resolveConstructor(state, constructed, !insideConstructorFactory(scope, constructed))
  expression.resolvedConstruction = plan
  constructorMethod := plan.factory
  if constructorMethod != none {
    expression.resolvedConstructor = constructorMethod
    validateConstructorVisibility(state, constructed, constructorMethod!, expression.span)
    let spread: FunctionParamType[] = []
    for parameter of plan.signature.params {
      if hasObjectProperty(expression.args, parameter.name) { continue }
      spreadType := constructionSpreadFieldType(state, expression, parameter.name)
      if spreadType != none { spread.push(FunctionParamType { name: parameter.name, type_: spreadType!, hasDefault: false }) }
    }
    checkArguments(state, propertyArguments(expression.args), plan.signature.params, scope, expression.span,
      "Class \"" + constructed.name + "\"", "Argument", true, true, spread, if expression.spread == none then none else expression.spread!.span, true)
    return finish(state, expression, plan.signature.returnType)
  }
  if expression.resolvedClass != none { checkClassProperties(state, expression.args, scope, constructed, expression.resolvedClass!, expression.span, false, expression) }
  return finish(state, expression, constructed)
}

export function validateConstructorVisibility(state: CheckerState, owner: ClassType, constructor: FunctionDeclaration, span: SourceSpan): none {
  if constructor.private_ && owner.symbol.module != state.info!.path {
    typeError(state, "Constructor for \"" + owner.name + "\" is private", span)
  }
}

export function checkClassProperties(state: CheckerState, properties: ObjectProperty[], scope: Scope, constructed: ClassType, declaration: ClassDeclaration, span: SourceSpan, structural: bool = false, spread: ConstructExpression | none = none): none {
  let used: string[] = []
  for property of properties {
    if containsString(used, property.name) { typeError(state, "Duplicate field '" + property.name + "' in " + declaration.name + " construction", property.span) }
    used.push(property.name)
    field := findClassField(declaration.fields, property.name)
    if field == none || field!.static_ || (!structural && field!.const_) {
      typeError(state, "Unknown field '" + property.name + "' for " + declaration.name, property.span)
      checkPropertyValue(state, property, scope, none)
      continue
    }
    expected := memberType(state, constructed, property.name, property.span)
    checkAssignableProperty(state, property, scope, optionalResolvedType(expected))
    if structural && field!.const_ {
      if property.value == none || field!.defaultValue == none || !sameFixedFieldValue(property.value!, field!.defaultValue!) {
        typeError(state, "Field '" + property.name + "' must match its literal-valued declaration", property.span)
      }
    }
  }
  for field of declaration.fields {
    if field.static_ || (!structural && field.const_) { continue }
    for name of field.names {
      if containsString(used, name) { continue }
      spreadType := if spread == none then none else constructionSpreadFieldType(state, spread!, name)
      if spreadType == none {
        if field.const_ || field.defaultValue == none { typeError(state, "Missing required field '" + name + "'", span) }
      }
      else {
        expected := memberType(state, constructed, name, span)
        if !isAssignableWithInterfaces(state.result, spreadType!, expected) {
          typeError(state, "Cannot assign spread field " + typeName(spreadType!) + " to " + typeName(expected), spread!.spread!.span)
        }
      }
    }
  }
}

function checkConstructionSpread(state: CheckerState, expression: ConstructExpression, scope: Scope): none {
  if expression.spread == none { return }
  spreadType := checkExpression(state, expression.spread!, scope, none)
  expression.resolvedSpreadType = optionalResolvedType(spreadType)
  case spreadType {
    _: ClassType -> { }
    _: InterfaceType -> { }
    _: UnknownType -> { }
    _ -> { typeError(state, "Field spread requires a class, struct, or interface value; got " + typeName(spreadType), expression.spread!.span) }
  }
}

function constructionSpreadFieldType(state: CheckerState, expression: ConstructExpression, name: string): ResolvedType | none {
  if expression.spread == none || expression.resolvedSpreadType == none { return none }
  spreadType := expression.resolvedSpreadType!
  let supported = false
  case spreadType {
    _: ClassType -> { supported = true }
    _: InterfaceType -> { supported = true }
    _ -> { }
  }
  if !supported { return none }
  fieldType := memberType(state, spreadType, name, expression.spread!.span)
  if fieldType.kind == "unknown" { return none }
  if !containsString(expression.spreadFields, name) { expression.spreadFields.push(name) }
  return fieldType
}

// Visibility uses the same stored-field parameter order used for validation.
export function validateFieldArguments(state: CheckerState, plan: CheckedConstruction, owner: ClassType, args: SuppliedArgument[]): none {
  if plan.factory != none || plan.declaration == none || owner.symbol.module == state.info!.path { return }
  for i of 0..<args.length {
    argument := args[i]
    name := argument.name ?? (if i < plan.signature.params.length then plan.signature.params[i].name else "")
    field := findClassField(plan.declaration!.fields, name)
    if field != none && field!.private_ {
      typeError(state, "Field '" + name + "' is private to module '" + owner.symbol.module + "'", argument.span)
    }
  }
}

/**
 * The class or struct a positional literal `(a, b)` constructs when its
 * expected type names one, directly or as the present arm of `T | none`.
 * Anything else (unions of several classes, interfaces, tuples, generic
 * contexts still being inferred) leaves the literal an ordinary Tuple.
 */
export function positionalLiteralClass(expected: ResolvedType | none): ClassType | none {
  if expected == none { return none }
  case expected! {
    class_: ClassType -> { return if containsTypeParameter(class_) then none else class_ }
    union_: UnionResolvedType -> {
      let found: ClassType | none = none
      for member of union_.types {
        case member {
          _: NoneType -> { }
          class_: ClassType -> {
            if found != none { return none }
            found = class_
          }
          _ -> { return none }
        }
      }
      return if found == none || containsTypeParameter(found!) then none else found
    }
    _ -> { return none }
  }
}

function containsTypeParameter(class_: ClassType): bool {
  for argument of class_.typeArgs {
    case argument {
      _: TypeParameterType -> { return true }
      nested: ClassType -> { if containsTypeParameter(nested) { return true } }
      _ -> { }
    }
  }
  return false
}

/** Checks `(a, b)` against an expected class exactly like the positional call `Point(a, b)`. */
export function checkPositionalLiteralConstruction(state: CheckerState, expression: TupleLiteral, scope: Scope, class_: ClassType): ResolvedType {
  construction := resolveConstructor(state, class_, !insideConstructorFactory(scope, class_))
  expression.resolvedConstruction = construction
  expression.resolvedClass = construction.declaration
  if construction.factory != none { validateConstructorVisibility(state, class_, construction.factory!, expression.span) }
  let args: SuppliedArgument[] = []
  for element of expression.elements { args.push(SuppliedArgument { name: none, value: element, span: element.span }) }
  validateFieldArguments(state, construction, class_, args)
  kind := if class_.symbol.kind == "struct" then "Struct" else "Class"
  checkArguments(state, args, construction.signature.params, scope, expression.span, kind + " \"" + class_.name + "\"")
  return finish(state, expression, construction.signature.returnType)
}
