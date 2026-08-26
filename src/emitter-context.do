// Shared state for the Doof emitter's nominal lowering.
//
// This intentionally owns only graph-wide nominal and method context. It owns
// only the declarations needed by class construction and method field access;
// module dependency state belongs to the module/header planner.

import { Program, SourceSpan } from "./ast"
import { JsonEligibilityCache } from "./json-semantics"
import {
  ActorType, ArrayResolvedType, ClassMetadataResolvedType, ClassType, EnumType, FunctionType, ImportBinding,
  InterfaceType, JsonValueResolvedType, MapResolvedType, MethodReflectionResolvedType, NamespaceBinding, NoneType,
  PrimitiveType, PromiseType, RangeResolvedType, ResolvedType, ResultResolvedType,
  SetResolvedType, StreamResolvedType, Symbol, TupleResolvedType, TypeParameterType,
  TypeSubstitution, UnionResolvedType, UnknownType, WeakResolvedType,
} from "./semantic"

export class EmitModuleSurface {
  path: string
  exports: Symbol[] = []
  imports: ImportBinding[] = []
  genericTypes: string[] = []
  genericFunctions: string[] = []
}

export class SourceLocationSpanOverride {
  span: SourceSpan
}

export class EmitContext {
  let modulePath: string = ""
  let sourcePath: string = ""
  allPrograms: Program[] = []
  let namespaceImports: NamespaceBinding[] = []
  let imports: ImportBinding[] = []
  let importedDefinitionNeedles: string[] = []
  let importedDefinitionNeedlesReady: bool = false
  let moduleSurfaces: EmitModuleSurface[] = []
  let jsonEligibility: JsonEligibilityCache = JsonEligibilityCache {}
  let currentClass: string = ""
  let currentClassNative: bool = false
  let currentFunctionStatic: bool = false
  let currentReturnErrorType: string = ""
  let currentFunctionName: string = ""
  let inValueYieldBlock: bool = false
  let valueYieldReturnsVoid: bool = false
  let catchVarName: string = ""
  let catchResultType: ResolvedType | none = none
  // Call-site override used while materializing defaults such as @caller.
  let sourceLocationSpanOverride: SourceLocationSpanOverride | none = none
  let genericTypeParams: string[] = []
  // Concrete Doof monomorphization substitution active while emitting a
  // specialized function, class, or method body.
  let substitution: TypeSubstitution | none = none
  concreteFunctionNames: string[] = []
  concreteFunctionKeys: string[] = []
  concreteClassNames: string[] = []
  concreteClassKeys: string[] = []
  nativeTemplateClassKeys: string[] = []
  concreteMethodNames: string[] = []
  concreteMethodKeys: string[] = []
  concreteInterfaceNames: string[] = []
  concreteInterfaceKeys: string[] = []
  jsonSerializationKeys: string[] = []
  jsonDeserializationKeys: string[] = []
  // Mutable locals captured by any lambda in the current callable. Their
  // declarations are heap-boxed and every identifier use dereferences the box.
  let capturedMutables: string[] = []
  let tryCounter: int = 0
  // Native entry scripts lower direct bindings into private deferred storage.
  let scriptEntry: bool = false
  let tryPanics: bool = false
  // Coverage is configured per source module by the graph emitter.
  let coverageEnabled: bool = false
  let coverageModuleId: int = -1
  coverageInstrumentedLines: int[] = []
}

/** Maps generated C++ back to the active Doof source location. */
export function sourceLineDirective(span: SourceSpan, context: EmitContext): string {
  path := if context.sourcePath == "" then context.modulePath else context.sourcePath
  escaped := path.replaceAll("\\", "\\\\").replaceAll("\"", "\\\"")
  return "#line " + string(span.start.line) + " \"" + escaped + "\"\n"
}

/** Marks compiler-owned glue so it is not attributed to an adjacent Doof line. */
export function generatedLineDirective(): string => "#line 1 \"<doof-generated>\"\n"

export function recordCoverageLine(context: EmitContext, line: int): none {
  for existing of context.coverageInstrumentedLines { if existing == line { return } }
  context.coverageInstrumentedLines.push(line)
}

export function isCapturedMutable(context: EmitContext, name: string): bool {
  for captured of context.capturedMutables { if captured == name { return true } }
  return false
}

export function createEmitContext(program: Program): EmitContext {
  return createEmitContextForPrograms([program])
}

export function createEmitContextForPrograms(programs: Program[]): EmitContext {
  return EmitContext { allPrograms: programs }
}

export function createEmitContextForModule(program: Program, modulePath: string, allPrograms: Program[] = []): EmitContext {
  let programs = allPrograms
  if programs.length == 0 { programs = [program] }
  context := createEmitContextForPrograms(programs)
  context.modulePath = modulePath
  context.sourcePath = modulePath
  return context
}
