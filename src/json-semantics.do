// Shared semantic eligibility for compiler-generated JSON methods.
//
// The checker and emitter both consume this boundary so a synthetic method is
// never advertised without a matching generated definition.

import {
  ArrayType, BoolLiteral, CharLiteral, ClassDeclaration, ClassField, DoubleLiteral, FloatLiteral,
  ExportDeclaration, IntLiteral, InterfaceDeclaration, LongLiteral, NamedType, Program, Statement, StringLiteral, TypeAliasDeclaration, TypeAnnotation, UnionType,
} from "./ast"
import { ArrayResolvedType, ClassType, EnumType, InterfaceType, SerialValueResolvedType, MapResolvedType, NoneType, PrimitiveType, ResolvedType, Symbol, TupleResolvedType, UnionResolvedType } from "./semantic"
import { typeName } from "./checker-types"

export class JsonDiscriminatorEntry {
  value: string
  declaration: ClassDeclaration
}

export class JsonDiscriminator {
  fieldName: string
  let entries: JsonDiscriminatorEntry[] = []
}

/** Whole-graph memoization for repeated emitter eligibility queries. */
export class JsonEligibilityCache {
  serialization: Map<string, bool> = {}
  deserialization: Map<string, bool> = {}
}

// Automatic dispatch deliberately uses only fixed string fields. Shape-based
// unique-field matching belongs to contextual object literal inference and is
// not stable enough for decoding untrusted JSON.
export function interfaceJsonDiscriminator(
  owner: InterfaceDeclaration,
  programs: Program[],
  cache: JsonEligibilityCache | none = none,
): JsonDiscriminator | none {
  let visited: string[] = []
  return interfaceJsonDiscriminatorInner(owner, programs, cache, visited)
}

function interfaceJsonDiscriminatorInner(
  owner: InterfaceDeclaration,
  programs: Program[],
  cache: JsonEligibilityCache | none,
  visited: string[],
): JsonDiscriminator | none {
  if owner.resolvedSymbol == none || owner.resolvedSymbol!.implementations.length == 0 { return none }
  let implementations: ClassDeclaration[] = []
  for symbol of owner.resolvedSymbol!.implementations {
    declaration := findJsonClassDeclaration(programs, symbol)
    if declaration == none { return none }
    implementations.push(declaration!)
  }
  return classesJsonDiscriminator(implementations, programs, cache, visited)
}

/**
 * An interface value encodes through its runtime implementation, so every
 * implementing class must support serialization. Without implementations no
 * value can exist and encoding is vacuously available.
 */
export function canGenerateInterfaceJsonSerialization(owner: InterfaceDeclaration, programs: Program[] = []): bool {
  return owner.typeParams.length == 0 && owner.resolvedSymbol != none && interfaceJsonSerializationBlocker(owner, programs) == none
}

/** Names the first implementing class that prevents encoding the interface. */
export function interfaceJsonSerializationBlocker(owner: InterfaceDeclaration, programs: Program[] = []): string | none {
  let visited: string[] = []
  return interfaceJsonSerializationBlockerInner(owner, programs, visited)
}

function interfaceJsonSerializationBlockerInner(owner: InterfaceDeclaration, programs: Program[], visited: string[]): string | none {
  if owner.resolvedSymbol == none || markJsonKeyVisited(jsonInterfaceKey(owner), visited) { return none }
  for symbol of owner.resolvedSymbol!.implementations {
    if symbol.native_ || symbol.typeParams.length > 0 { return symbol.name }
    declaration := findJsonClassDeclaration(programs, symbol)
    if declaration == none || !canGenerateJsonSerializationInner(declaration!, programs, visited) { return symbol.name }
  }
  return none
}

function canGenerateInterfaceJsonSerializationInner(owner: InterfaceDeclaration, programs: Program[], visited: string[]): bool {
  return owner.typeParams.length == 0 && owner.resolvedSymbol != none && interfaceJsonSerializationBlockerInner(owner, programs, visited) == none
}

// Interface decoders reuse the direct `Interface.fromSerialValue` rule: a
// shared string discriminator, or no implementations at all.
function canGenerateInterfaceJsonDeserializationInner(owner: InterfaceDeclaration, programs: Program[], visited: string[]): bool {
  if owner.typeParams.length > 0 || owner.resolvedSymbol == none { return false }
  if markJsonKeyVisited(jsonInterfaceKey(owner), visited) { return true }
  if owner.resolvedSymbol!.implementations.length == 0 { return true }
  return interfaceJsonDiscriminatorInner(owner, programs, none, visited) != none
}

function interfaceTypeSerializable(symbol: Symbol, typeArgs: int, programs: Program[], visited: string[], encode: bool): bool {
  if typeArgs > 0 { return false }
  declaration := findJsonInterfaceDeclaration(programs, symbol)
  if declaration == none { return programs.length == 0 }
  return if encode then canGenerateInterfaceJsonSerializationInner(declaration!, programs, visited) else canGenerateInterfaceJsonDeserializationInner(declaration!, programs, visited)
}

/**
 * Discriminates a named union alias of classes, such as
 * `type Shape = Circle | Rect`, by the same rule as interfaces.
 */
export function unionAliasJsonDiscriminator(
  alias: TypeAliasDeclaration,
  programs: Program[],
  cache: JsonEligibilityCache | none = none,
): JsonDiscriminator | none {
  if alias.typeParams.length > 0 || alias.resolvedType == none { return none }
  case alias.resolvedType! {
    union_: UnionResolvedType -> {
      let members: ClassDeclaration[] = []
      for member of union_.types {
        case member {
          class_: ClassType -> {
            if class_.typeArgs.length > 0 || class_.symbol.kind != "class" { return none }
            declaration := findJsonClassDeclaration(programs, class_.symbol)
            if declaration == none { return none }
            members.push(declaration!)
          }
          _ -> { return none }
        }
      }
      let visited: string[] = []
      return classesJsonDiscriminator(members, programs, cache, visited)
    }
    _ -> { return none }
  }
}

function classesJsonDiscriminator(
  implementations: ClassDeclaration[],
  programs: Program[],
  cache: JsonEligibilityCache | none,
  visited: string[],
): JsonDiscriminator | none {
  for implementation of implementations {
    if !implementationDecodes(implementation, programs, cache, visited) { return none }
  }
  if implementations.length == 0 { return none }
  for candidate of implementations[0].fields {
    if candidate.static_ || !candidate.const_ || candidate.names.length != 1 || candidate.defaultValue == none { continue }
    case candidate.defaultValue! {
      firstValue: StringLiteral -> {
        discriminator := JsonDiscriminator { fieldName: candidate.names[0] }
        for implementation of implementations {
          matching := fixedStringField(implementation, discriminator.fieldName)
          if matching == none || discriminatorHasValue(discriminator, matching!) { discriminator.entries = []; break }
          discriminator.entries.push(JsonDiscriminatorEntry { value: matching!, declaration: implementation })
        }
        if discriminator.entries.length == implementations.length { return discriminator }
      }
      _ -> { }
    }
  }
  return none
}

// The cache only memoizes top-level answers; nested queries share `visited` so
// recursive interfaces terminate.
function implementationDecodes(implementation: ClassDeclaration, programs: Program[], cache: JsonEligibilityCache | none, visited: string[]): bool {
  if visited.length == 0 { return canGenerateJsonDeserialization(implementation, programs, cache) }
  return canGenerateJsonDeserializationInner(implementation, programs, visited)
}

function fixedStringField(owner: ClassDeclaration, name: string): string | none {
  for field of owner.fields {
    if field.static_ || !field.const_ || field.defaultValue == none { continue }
    let matches = false
    for fieldName of field.names { if fieldName == name { matches = true } }
    if !matches { continue }
    case field.defaultValue! {
      value: StringLiteral -> { return value.value }
      _ -> { return none }
    }
  }
  return none
}

function discriminatorHasValue(discriminator: JsonDiscriminator, value: string): bool {
  for entry of discriminator.entries { if entry.value == value { return true } }
  return false
}

export function canGenerateJsonSerialization(
  owner: ClassDeclaration,
  programs: Program[] = [],
  cache: JsonEligibilityCache | none = none,
): bool {
  key := jsonOwnerKey(owner)
  if cache != none && cache!.serialization.has(key) { return cache!.serialization.get(key)! }
  let visited: string[] = []
  result := canGenerateJsonSerializationInner(owner, programs, visited)
  if cache != none { cache!.serialization.set(key, result) }
  return result
}

function canGenerateJsonSerializationInner(owner: ClassDeclaration, programs: Program[], visited: string[]): bool {
  if owner.native_ || owner.typeParams.length > 0 || hasDedicatedConstructor(owner) { return false }
  if markJsonOwnerVisited(owner, visited) { return true }
  for field of owner.fields {
    if field.static_ { continue }
    if !isGeneratedJsonSerializationField(field, programs, visited) { return false }
  }
  return true
}

export function canGenerateJsonDeserialization(
  owner: ClassDeclaration,
  programs: Program[] = [],
  cache: JsonEligibilityCache | none = none,
): bool {
  key := jsonOwnerKey(owner)
  if cache != none && cache!.deserialization.has(key) { return cache!.deserialization.get(key)! }
  let visited: string[] = []
  result := canGenerateJsonDeserializationInner(owner, programs, visited)
  if cache != none { cache!.deserialization.set(key, result) }
  return result
}

function canGenerateJsonDeserializationInner(owner: ClassDeclaration, programs: Program[], visited: string[]): bool {
  if owner.native_ || owner.typeParams.length > 0 || hasDedicatedConstructor(owner) { return false }
  if markJsonOwnerVisited(owner, visited) { return true }
  for field of owner.fields {
    if field.static_ { continue }
    if !isGeneratedJsonDeserializationField(field, programs, visited) { return false }
  }
  return true
}

export function nullableJsonMember(type_: ResolvedType): ResolvedType | none {
  case type_ {
    union_: UnionResolvedType -> { return nullableJsonMemberUnchecked(union_) }
    _ -> { return none }
  }
  return none
}

export function isGeneratedJsonType(type_: ResolvedType, programs: Program[] = [], visited: string[] = []): bool {
  case type_ {
    _: PrimitiveType -> { return true }
    _: SerialValueResolvedType -> { return true }
    _: NoneType -> { return true }
    _: EnumType -> { return true }
    class_: ClassType -> {
      if class_.symbol.native_ || class_.typeArgs.length > 0 { return false }
      declaration := findJsonClassDeclaration(programs, class_.symbol)
      if declaration == none { return programs.length == 0 }
      return canGenerateJsonDeserializationInner(declaration!, programs, visited)
    }
    interface_: InterfaceType -> { return interfaceTypeSerializable(interface_.symbol, interface_.typeArgs.length, programs, visited, false) }
    array: ArrayResolvedType -> { return isGeneratedJsonType(array.elementType, programs, visited) }
    map: MapResolvedType -> {
      case map.keyType {
        key: PrimitiveType -> { return key.name == "string" && isGeneratedJsonType(map.valueType, programs, visited) }
        _ -> { return false }
      }
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        if !isGeneratedJsonType(element, programs, visited) { return false }
      }
      return true
    }
    union_: UnionResolvedType -> {
      inner := nullableJsonMemberUnchecked(union_)
      if inner == none { return objectUnionDecodes(union_, programs, visited) }
      return isGeneratedJsonType(inner!, programs, visited)
    }
    _ -> { return false }
  }
  return false
}

function isGeneratedJsonSerializationType(type_: ResolvedType, programs: Program[] = [], visited: string[] = []): bool {
  case type_ {
    class_: ClassType -> {
      if class_.symbol.native_ || class_.typeArgs.length > 0 { return false }
      declaration := findJsonClassDeclaration(programs, class_.symbol)
      if declaration == none { return programs.length == 0 }
      return canGenerateJsonSerializationInner(declaration!, programs, visited)
    }
    interface_: InterfaceType -> { return interfaceTypeSerializable(interface_.symbol, interface_.typeArgs.length, programs, visited, true) }
    array: ArrayResolvedType -> {
      if array.elementType.kind == "json-value" { return true }
      return isGeneratedJsonSerializationType(array.elementType, programs, visited)
    }
    map: MapResolvedType -> {
      case map.keyType {
        key: PrimitiveType -> { return key.name == "string" && isGeneratedJsonSerializationType(map.valueType, programs, visited) }
        _ -> { return false }
      }
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements {
        if !isGeneratedJsonSerializationType(element, programs, visited) { return false }
      }
      return true
    }
    union_: UnionResolvedType -> {
      inner := nullableJsonMemberUnchecked(union_)
      if inner == none { return objectUnionEncodes(union_, programs, visited) }
      case inner! {
        _: ClassType -> { return isGeneratedJsonSerializationType(inner!, programs, visited) }
        _: InterfaceType -> { return isGeneratedJsonSerializationType(inner!, programs, visited) }
        _: ArrayResolvedType -> { return isGeneratedJsonSerializationType(inner!, programs, visited) }
        _: MapResolvedType -> { return isGeneratedJsonSerializationType(inner!, programs, visited) }
        _ -> { return isGeneratedJsonType(inner!, programs, visited) }
      }
    }
    _ -> { }
  }
  if isGeneratedJsonType(type_, programs, visited) { return true }
  case type_ {
    _: NoneType -> { return true }
    map: MapResolvedType -> {
      case map.keyType {
        key: PrimitiveType -> { return key.name == "string" && map.valueType.kind == "json-value" }
        _ -> { return false }
      }
    }
    _ -> { return false }
  }
  return false
}

function nullableJsonMemberUnchecked(union_: UnionResolvedType): ResolvedType | none {
  let value: ResolvedType | none = none
  let nullCount = 0
  for member of union_.types {
    case member {
      _: NoneType -> { nullCount = nullCount + 1 }
      _ -> {
        if value != none { return none }
        value = member
      }
    }
  }
  if value == none || nullCount != 1 || union_.types.length != 2 { return none }
  return value
}

// Static member lookup can precede the class declaration in source order.
// Use syntax/default literals until the normal class-checking pass decorates
// the field, then defer to the resolved semantic type thereafter.
function isGeneratedJsonDeserializationField(field: ClassField, programs: Program[], visited: string[]): bool {
  if field.weak_ { return false }
  if field.resolvedType != none { return isGeneratedJsonType(field.resolvedType!, programs, visited) }
  if field.type_ != none { return isGeneratedJsonDeserializationAnnotation(field.type_!, programs, visited) }
  if field.defaultValue == none { return false }
  case field.defaultValue! {
    _: IntLiteral -> { return true }
    _: LongLiteral -> { return true }
    _: FloatLiteral -> { return true }
    _: DoubleLiteral -> { return true }
    _: StringLiteral -> { return true }
    _: CharLiteral -> { return true }
    _: BoolLiteral -> { return true }
    _ -> { return false }
  }
  return false
}

function isGeneratedJsonSerializationField(field: ClassField, programs: Program[], visited: string[]): bool {
  if field.weak_ { return false }
  if field.resolvedType != none { return isGeneratedJsonSerializationType(field.resolvedType!, programs, visited) }
  if field.type_ != none { return isGeneratedJsonSerializationAnnotation(field.type_!, programs, visited) }
  return isGeneratedJsonDeserializationField(field, programs, visited)
}

function isGeneratedJsonDeserializationAnnotation(annotation: TypeAnnotation, programs: Program[], visited: string[]): bool {
  if annotation.resolvedType != none { return isGeneratedJsonType(annotation.resolvedType!, programs, visited) }
  case annotation {
    named: NamedType -> {
      if named.name == "byte" || named.name == "int" || named.name == "long" ||
        named.name == "float" || named.name == "double" || named.name == "string" ||
        named.name == "char" || named.name == "bool" || named.name == "SerialValue" { return true }
      if named.name == "Tuple" {
        if named.typeArgs.length == 0 { return false }
        for element of named.typeArgs {
          if !isGeneratedJsonDeserializationAnnotation(element, programs, visited) { return false }
        }
        return true
      }
      if named.name == "Map" || named.name == "ReadonlyMap" {
        if named.typeArgs.length != 2 { return false }
        case named.typeArgs[0] {
          key: NamedType -> { return key.name == "string" && isGeneratedJsonDeserializationAnnotation(named.typeArgs[1], programs, visited) }
          _ -> { return false }
        }
      }
      if named.typeArgs.length != 0 || named.resolvedSymbol == none || named.resolvedSymbol!.native_ { return false }
      if named.resolvedSymbol!.kind == "enum" { return true }
      if named.resolvedSymbol!.kind == "interface" { return interfaceTypeSerializable(named.resolvedSymbol!, 0, programs, visited, false) }
      if named.resolvedSymbol!.kind != "class" && named.resolvedSymbol!.kind != "struct" { return false }
      declaration := findJsonClassDeclaration(programs, named.resolvedSymbol!)
      if declaration == none { return programs.length == 0 }
      return canGenerateJsonDeserializationInner(declaration!, programs, visited)
    }
    array: ArrayType -> {
      return isGeneratedJsonDeserializationAnnotation(array.elementType, programs, visited)
    }
    union_: UnionType -> {
      objectUnion := objectUnionAnnotationType(union_)
      if objectUnion != none { return isGeneratedJsonType(objectUnion!, programs, visited) }
      if union_.types.length != 2 { return false }
      let hasNull = false
      let hasPrimitive = false
      for member of union_.types {
        case member {
          named: NamedType -> {
            if named.name == "null" { hasNull = true }
            else if named.name != "SerialValue" && isGeneratedJsonDeserializationAnnotation(member, programs, visited) { hasPrimitive = true }
            else { return false }
          }
          _ -> { return false }
        }
      }
      return hasNull && hasPrimitive
    }
    _ -> { return false }
  }
  return false
}

function isGeneratedJsonSerializationAnnotation(annotation: TypeAnnotation, programs: Program[], visited: string[]): bool {
  if annotation.resolvedType != none { return isGeneratedJsonSerializationType(annotation.resolvedType!, programs, visited) }
  case annotation {
    union_: UnionType -> {
      objectUnion := objectUnionAnnotationType(union_)
      if objectUnion != none { return isGeneratedJsonSerializationType(objectUnion!, programs, visited) }
    }
    named: NamedType -> {
      if named.name == "Tuple" {
        if named.typeArgs.length == 0 { return false }
        for element of named.typeArgs {
          if !isGeneratedJsonSerializationAnnotation(element, programs, visited) { return false }
        }
        return true
      }
      if named.name == "Map" || named.name == "ReadonlyMap" {
        if named.typeArgs.length != 2 { return false }
        case named.typeArgs[0] {
          key: NamedType -> { return key.name == "string" && isGeneratedJsonSerializationAnnotation(named.typeArgs[1], programs, visited) }
          _ -> { return false }
        }
      }
      if named.resolvedSymbol != none && named.resolvedSymbol!.kind == "interface" {
        return named.typeArgs.length == 0 && interfaceTypeSerializable(named.resolvedSymbol!, 0, programs, visited, true)
      }
      if named.resolvedSymbol != none && (named.resolvedSymbol!.kind == "class" || named.resolvedSymbol!.kind == "struct") {
        declaration := findJsonClassDeclaration(programs, named.resolvedSymbol!)
        if declaration == none { return programs.length == 0 }
        return canGenerateJsonSerializationInner(declaration!, programs, visited)
      }
    }
    array: ArrayType -> {
      return isGeneratedJsonSerializationAnnotation(array.elementType, programs, visited)
    }
    _ -> { }
  }
  if isGeneratedJsonDeserializationAnnotation(annotation, programs, visited) { return true }
  case annotation {
    named: NamedType -> {
      if named.name == "null" { return true }
      if (named.name == "Map" || named.name == "ReadonlyMap") && named.typeArgs.length == 2 {
        case named.typeArgs[0] {
          key: NamedType -> {
            case named.typeArgs[1] {
              value: NamedType -> { return key.name == "string" && value.name == "SerialValue" }
              _ -> { return false }
            }
          }
          _ -> { return false }
        }
      }
      return false
    }
    array: ArrayType -> {
      case array.elementType {
        element: NamedType -> { return element.name == "SerialValue" }
        _ -> { return false }
      }
    }
    _ -> { return false }
  }
  return false
}

function markJsonOwnerVisited(owner: ClassDeclaration, visited: string[]): bool {
  return markJsonKeyVisited(jsonOwnerKey(owner), visited)
}

function markJsonKeyVisited(key: string, visited: string[]): bool {
  for existing of visited { if existing == key { return true } }
  visited.push(key)
  return false
}

export function jsonOwnerKey(owner: ClassDeclaration): string {
  module := if owner.resolvedSymbol == none then "" else owner.resolvedSymbol!.module
  return module + "::" + owner.name
}

/** Interfaces share the class key space; one module cannot declare both names. */
export function jsonInterfaceKey(owner: InterfaceDeclaration): string {
  module := if owner.resolvedSymbol == none then "" else owner.resolvedSymbol!.module
  return module + "::" + owner.name
}

function findJsonClassDeclaration(programs: Program[], symbol: Symbol): ClassDeclaration | none {
  for program of programs {
    for statement of program.statements {
      declaration := jsonClassDeclaration(statement)
      if declaration == none || declaration!.resolvedSymbol == none { continue }
      if declaration!.resolvedSymbol!.module == symbol.module && declaration!.name == symbol.name { return declaration }
    }
  }
  return none
}

function findJsonInterfaceDeclaration(programs: Program[], symbol: Symbol): InterfaceDeclaration | none {
  for program of programs {
    for statement of program.statements {
      declaration := jsonInterfaceDeclaration(statement)
      if declaration == none || declaration!.resolvedSymbol == none { continue }
      if declaration!.resolvedSymbol!.module == symbol.module && declaration!.name == symbol.name { return declaration }
    }
  }
  return none
}

function jsonInterfaceDeclaration(statement: Statement): InterfaceDeclaration | none {
  case statement {
    interface_: InterfaceDeclaration -> { return interface_ }
    export_: ExportDeclaration -> { return jsonInterfaceDeclaration(export_.declaration) }
    _ -> { return none }
  }
  return none
}

function jsonClassDeclaration(statement: Statement): ClassDeclaration | none {
  case statement {
    class_: ClassDeclaration -> { return class_ }
    export_: ExportDeclaration -> { return jsonClassDeclaration(export_.declaration) }
    _ -> { return none }
  }
  return none
}

function hasDedicatedConstructor(owner: ClassDeclaration): bool {
  for method of owner.methods {
    if method.static_ && method.name == "constructor" { return true }
  }
  return false
}

/**
 * The present members of an object union: two or more class or interface
 * members, optionally with none. A single member with none is a nullable value
 * instead (see nullableJsonMember).
 */
export function objectUnionJsonMembers(type_: ResolvedType): ResolvedType[] | none {
  union_ := type_ as UnionResolvedType else { return none }
  let members: ResolvedType[] = []
  let noneCount = 0
  for member of union_.types {
    case member {
      _: NoneType -> { noneCount += 1 }
      class_: ClassType -> {
        if class_.symbol.kind != "class" { return none }
        members.push(member)
      }
      _: InterfaceType -> { members.push(member) }
      _ -> { return none }
    }
  }
  if members.length < 2 || noneCount > 1 { return none }
  return members
}

/**
 * Decodes an object union by one string discriminator shared by every class it
 * flattens to, each interface member contributing its implementing classes.
 * A union whose interfaces have no implementations decodes only `null`, so its
 * discriminator has no entries.
 */
export function objectUnionJsonDiscriminator(
  type_: ResolvedType,
  programs: Program[],
  cache: JsonEligibilityCache | none = none,
): JsonDiscriminator | none {
  let visited: string[] = []
  return objectUnionJsonDiscriminatorInner(type_, programs, cache, visited)
}

function objectUnionJsonDiscriminatorInner(
  type_: ResolvedType,
  programs: Program[],
  cache: JsonEligibilityCache | none,
  visited: string[],
): JsonDiscriminator | none {
  members := objectUnionJsonMembers(type_) else { return none }
  let classes: ClassDeclaration[] = []
  for member of members {
    case member {
      class_: ClassType -> {
        if class_.typeArgs.length > 0 || !addUnionJsonClass(classes, class_.symbol, programs) { return none }
      }
      interface_: InterfaceType -> {
        if interface_.typeArgs.length > 0 { return none }
        for implementation of interface_.symbol.implementations {
          if !addUnionJsonClass(classes, implementation, programs) { return none }
        }
      }
      _ -> { return none }
    }
  }
  if classes.length == 0 { return JsonDiscriminator { fieldName: "" } }
  return classesJsonDiscriminator(classes, programs, cache, visited)
}

// A class reached through several members (directly and through an interface,
// or through two interfaces) is one decoding candidate.
function addUnionJsonClass(classes: ClassDeclaration[], symbol: Symbol, programs: Program[]): bool {
  if symbol.native_ || symbol.typeParams.length > 0 { return false }
  declaration := findJsonClassDeclaration(programs, symbol) else { return false }
  for existing of classes { if jsonOwnerKey(existing) == jsonOwnerKey(declaration) { return true } }
  classes.push(declaration)
  return true
}

function objectUnionDecodes(type_: ResolvedType, programs: Program[], visited: string[]): bool {
  if programs.length == 0 { return objectUnionJsonMembers(type_) != none }
  return objectUnionJsonDiscriminatorInner(type_, programs, none, visited) != none
}

function objectUnionEncodes(type_: ResolvedType, programs: Program[], visited: string[]): bool {
  members := objectUnionJsonMembers(type_) else { return false }
  for member of members {
    if !isGeneratedJsonSerializationType(member, programs, visited) { return false }
  }
  return true
}

// Static member lookup can see a union annotation before it is resolved; its
// named class and interface members resolve the same way the checker will.
function objectUnionAnnotationType(union_: UnionType): ResolvedType | none {
  let members: ResolvedType[] = []
  for member of union_.types {
    named := member as NamedType else { return none }
    if named.name == "none" || named.name == "null" { members.push(NoneType {}); continue }
    if named.typeArgs.length > 0 || named.resolvedSymbol == none { return none }
    symbol := named.resolvedSymbol!
    if symbol.kind == "class" { members.push(ClassType { name: symbol.name, symbol }) }
    else if symbol.kind == "interface" { members.push(InterfaceType { name: symbol.name, symbol }) }
    else { return none }
  }
  resolved := UnionResolvedType { types: members }
  return if objectUnionJsonMembers(resolved) == none then none else resolved
}

/**
 * Explains a direct field whose object union cannot decode, for diagnostics.
 * Other blockers keep the owner's general message.
 */
export function objectUnionJsonDecodeBlocker(owner: ClassDeclaration, programs: Program[]): string | none {
  for field of owner.fields {
    if field.static_ || field.const_ || field.resolvedType == none { continue }
    if objectUnionJsonMembers(field.resolvedType!) == none { continue }
    if objectUnionJsonDiscriminator(field.resolvedType!, programs) != none { continue }
    name := if field.names.length == 0 then "<field>" else field.names[0]
    return "field \"" + name + "\" has union type \"" + typeName(field.resolvedType!) + "\", whose member classes must be non-generic and share a literal-valued string field with distinct values"
  }
  return none
}
