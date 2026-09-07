// Shared semantic data for the Doof front end.
//
// These are intentionally small, nominal records.  The analyzer owns module
// symbols; the checker owns resolved types and lexical bindings.

export struct SemanticLocation {
  line: int
  column: int
  offset: int
}

export struct SemanticSpan {
  start: SemanticLocation
  end: SemanticLocation
}

export class Diagnostic {
  severity: string
  message: string
  span: SemanticSpan
  module: string
  replacement: string = ""
}

export class Symbol {
  kind: string
  name: string
  module: string
  exported: bool
  originalName: string = ""
  native_: bool = false
  nativeHeader: string = ""
  nativeCppName: string = ""
  implementations: Symbol[] = []
  implementedInterfaceTypes: string[] = []
  typeParams: string[] = []
  streamElementTypes: ResolvedType[] = []
}

export class ImportBinding {
  localName: string
  sourceName: string
  sourceModule: string
  typeOnly: bool
  symbol: Symbol | none = none
}

export class NamespaceBinding {
  localName: string
  sourceModule: string
  typeOnly: bool
}

export class SourceFile {
  path: string
  source: string
  // Optional physical location used by native debug information. Logical
  // module identity remains authoritative for imports and diagnostics.
  physicalPath: string = ""
}

// Non-semantic identity metadata, assigned lazily by one emission graph.
// The owner token contains no graph/cache references, avoiding ownership cycles.
export class SemanticTypeIdentityOwner {}
export class SemanticTypeIdentity {
  owner: SemanticTypeIdentityOwner
  id: int
}

export class PrimitiveType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "primitive"
  name: string
}

export class ClassType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "class"
  name: string
  symbol: Symbol
  typeArgs: ResolvedType[] = []
}

export class EnumType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "enum"
  name: string
  symbol: Symbol
}

export class InterfaceType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "interface"
  name: string
  symbol: Symbol
  typeArgs: ResolvedType[] = []
}

export class FunctionType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "function"
  params: FunctionParamType[]
  returnType: ResolvedType
  typeParams: string[] = []
}

export class FunctionParamType {
  name: string
  type_: ResolvedType
  hasDefault: bool
}

export class ActorType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "actor"
  innerClass: ClassType
}

export class PromiseType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "promise"
  valueType: ResolvedType
}

export class ArrayResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "array"
  elementType: ResolvedType
  readonly_: bool
}

export class MapResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "map"
  keyType: ResolvedType
  valueType: ResolvedType
  readonly_: bool
}

export class SetResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "set"
  elementType: ResolvedType
  readonly_: bool
}

export class StreamResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "stream"
  elementType: ResolvedType
}

// Finite integer ranges are immutable runtime values with an exclusive upper
// bound. Keep them distinct from arrays so signatures retain Range semantics.
export class RangeResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "range"
}

// JsonValue is recursive, so it is represented as a dedicated intrinsic
// semantic type rather than expanding into a finite union of containers.
export class JsonValueResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "json-value"
}

export class ResultResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "result"
  valueType: ResolvedType
  errorType: ResolvedType
}

export class TupleResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "tuple"
  elements: ResolvedType[]
}

export class UnionResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "union"
  types: ResolvedType[]
}

export class WeakResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "weak"
  inner: ResolvedType
}

export class NoneType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "none"
}

// The uninhabited bottom type. Expressions of this type never produce a
// runtime value and may therefore be used wherever a value is expected.
export class NeverType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "never"
}

export class UnknownType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "unknown"
}

// A type parameter is resolved semantic information, not recovery unknown.
// Keeping it explicit lets the checker prove generic declarations before the
// emitter sees them while preserving the parameter spelling for C++ templates.
export class TypeParameterType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "type-parameter"
  name: string
  constraintName: string = ""
  constraint: ResolvedType | none = none
}

/** Compiler-known reflection value returned by `Type.metadata`. */
export class ClassMetadataResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "class-metadata"
  classType: ResolvedType
}

/** Compiler-known element type of `ClassMetadata.methods`. */
export class MethodReflectionResolvedType {
  let emissionIdentity: SemanticTypeIdentity | none = none
  kind: string = "method-reflection"
  classType: ResolvedType
}

export type ResolvedType = PrimitiveType | ClassType | EnumType | InterfaceType | FunctionType |
  ActorType | PromiseType | ArrayResolvedType | MapResolvedType | SetResolvedType | StreamResolvedType | RangeResolvedType | JsonValueResolvedType | ResultResolvedType | TupleResolvedType | UnionResolvedType | WeakResolvedType |
  NoneType | NeverType | UnknownType | TypeParameterType | ClassMetadataResolvedType | MethodReflectionResolvedType

export class TypeSubstitution {
  names: string[] = []
  arguments: ResolvedType[] = []
}

export class Binding {
  name: string
  let kind: string
  type_: ResolvedType
  mutable: bool
  span: SemanticSpan
  module: string
  symbol: Symbol | none = none
  casePattern: string = ""
  fieldMode: string = ""
  fieldOwner: string = ""
}

export class Scope {
  let editorIndexed: bool = false
  parent: Scope | none
  bindings: Binding[] = []
  typeParams: string[] = []
  typeParamConstraintNames: string[] = []
  typeParamConstraints: ResolvedTypeConstraint[] = []
  let returnType: ResolvedType | none = none
  thisType: ResolvedType | none = none
  functionName: string = ""
  staticContext: bool = false
  let inValueYieldBlock: bool = false
  let yieldExpectedType: ResolvedType | none = none
  let yieldType: ResolvedType | none = none
  capturesTryErrors: bool = false
  catchErrorTypes: ResolvedType[] = []
  tryPanics: bool = false
  loopLabel: string | none = none
}

export class ResolvedTypeConstraint {
  let type_: ResolvedType | none = none
}

export class CheckResult {
  diagnostics: Diagnostic[] = []
}

// Optional editor observations retain checker scopes without changing bindings.
export class EditorScope {
  span: SemanticSpan
  scope: Scope
}
