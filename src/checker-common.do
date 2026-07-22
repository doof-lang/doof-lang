// State-aware diagnostics and expression decoration helpers.

import {
  ActorType, ArrayResolvedType, Binding, CheckResult, ClassType, EnumType, InterfaceType,
  Diagnostic, FunctionParamType, FunctionType,
  JsonValueResolvedType, MapResolvedType, NeverType, NoneType, PrimitiveType, PromiseType, ResolvedType, ResultResolvedType, Scope, SemanticLocation, SemanticSpan, Symbol,
  StreamResolvedType, TupleResolvedType, UnionResolvedType, UnknownType, TypeParameterType,
} from "./semantic"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import {
  ArrayLiteral, ArrayType, AsExpression, AssignmentExpression, AstLocation, BinaryExpression, Block,
  BoolLiteral, CallExpression, CallerExpression, CharLiteral, ClassDeclaration, ClassField, ConstructExpression,
  ConstDeclaration, ContinueStatement, DestructuringStatement, DoubleLiteral,
  DotShorthand, EnumDeclaration, ExportDeclaration, ExportList, Expression, ExpressionStatement,
  FloatLiteral, ForOfStatement, ForStatement, FunctionDeclaration, AstFunctionType,
  IfExpression, IfStatement, ImmutableBinding, Identifier, ImportDeclaration,
  IndexExpression, IntLiteral, InterfaceDeclaration, LetDeclaration,
  LambdaExpression, LongLiteral, MemberExpression, NamedType, NoneLiteral,
  NamedImport, NamespaceImport, ObjectLiteral, ObjectProperty, Program,
  ReadonlyDeclaration, ReturnStatement, SourceSpan, Statement, StringLiteral,
  ThisExpression, TupleLiteral, TypeAliasDeclaration, TypeAnnotation,
  UnaryExpression, UnionType, WhileStatement, WithBinding, WithStatement, BreakStatement,
  YieldStatement, CaseArm, CaseExpression, CasePattern, CaseStatement, TypePattern, ValuePattern, WildcardPattern,
  TryStatement,
  AsyncExpression, RetireExpression, ActorCreationExpression, Parameter,
  CatchExpression, YieldBlockExpression, YieldBlockAssignmentStatement,
} from "./ast"
import {
  actorType, applyDeepReadonly, arrayType, classType, enumType, functionType, interfaceType, isAssignable, isNumeric, joinTypes,
  isJsonValueType, jsonObjectType, jsonValueType, mapType, resultType, streamType,
  noneType, numericResult, primitive, promiseType, sameType, tupleType, typeName, unionType,
  substituteTypeParams, typeParameter, unknownType,
} from "./checker-types"
import { canGenerateJsonDeserialization, canGenerateJsonSerialization } from "./json-semantics"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { collectRetiredActorBindings, reportRetiredActorUses } from "./checker-actor-lifecycle"


import { CheckerState } from "./checker-state"
import { optionalResolvedType } from "./checker-symbols"
import { checkerSemanticSpan } from "./checker-validation"

export function finish(state: CheckerState, expression: Expression, resolvedType: ResolvedType): ResolvedType { expression.resolvedType = optionalResolvedType(resolvedType); return resolvedType }
export function typeError(state: CheckerState, message: string, span: SourceSpan): none { state.diagnostics.push(Diagnostic { severity: "error", message, span: checkerSemanticSpan(span), module: state.info!.path }) }
export function deprecatedNoneAlias(state: CheckerState, spelling: string, span: SourceSpan, module: string = ""): none {
  state.diagnostics.push(Diagnostic {
    severity: "warning",
    message: "'" + spelling + "' is deprecated; replace it with 'none'",
    span: checkerSemanticSpan(span),
    module: if module == "" then state.info!.path else module,
    replacement: "none",
  })
}
export function requireBool(state: CheckerState, resolvedType: ResolvedType, span: SourceSpan): none {
  case resolvedType {
    _: NeverType -> { return }
    _ -> { }
  }
  if typeName(resolvedType) != "bool" && typeName(resolvedType) != "unknown" { typeError(state, "Expected bool, got " + typeName(resolvedType), span) }
}

// Keep the full AST union visible in this module's generated header.
export function keepAstTypes(state: CheckerState, 
  enum_: EnumDeclaration | none = none,
  import_: ImportDeclaration | none = none,
  export_: ExportDeclaration | none = none,
  exports_: ExportList | none = none,
  namedImport: NamedImport | none = none,
  namespaceImport: NamespaceImport | none = none,
  dot: DotShorthand | none = none,
  caller: CallerExpression | none = none,
  yield_: YieldStatement | none = none,
): none { }
