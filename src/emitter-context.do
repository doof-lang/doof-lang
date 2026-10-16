import { ModuleNames } from "./emitter-names"
import { TypeLoweringSession } from "./emitter-type-cache"
// Shared state for the Doof emitter's nominal lowering.
//
// This intentionally owns only graph-wide nominal and method context. It owns
// only the declarations needed by class construction and method field access;
// module dependency state belongs to the module/header planner.

import { CppTypeRegistry } from "./cpp-type"
import { DeclarationIndex } from "./emitter-declarations"
import { Program, SourceSpan } from "./ast"
import { JsonEligibilityCache } from "./json-semantics"
import {
  ImportBinding, ResolvedType, Symbol, TypeSubstitution,
} from "./semantic"

export class EmitModuleSurface {
  path: string
  exports: Symbol[] = []
  imports: ImportBinding[] = []
  genericTypes: string[] = []
}

export class SourceLocationSpanOverride {
  span: SourceSpan
}

/** Build-scoped instrumentation and optional runtime feature selection. */
export class EmissionConfiguration {
  readonly observe: bool = false
  readonly metricsClassLifecycle: bool = false
}

export class EmitContext {
  let names: ModuleNames = ModuleNames {}
  let typeLowering: TypeLoweringSession | none = none
  let cppTypes: CppTypeRegistry = CppTypeRegistry {}
  let modulePath: string = ""
  let sourcePath: string = ""
  // Every program in the graph, with its top-level declarations by module and name.
  declarations: DeclarationIndex = DeclarationIndex {}
  let imports: ImportBinding[] = []
  let moduleSurfaces: EmitModuleSurface[] = []
  let jsonEligibility: JsonEligibilityCache = JsonEligibilityCache {}
  let currentClass: string = ""
  let currentClassNative: bool = false
  let currentClassStruct: bool = false
  let currentFunctionStatic: bool = false
  let currentReturnErrorType: string = ""
  let currentFunctionName: string = ""
  let inValueYieldBlock: bool = false
  let valueYieldReturnsVoid: bool = false
  let valueYieldType: ResolvedType | none = none
  let catchVarName: string = ""
  let catchResultType: ResolvedType | none = none
  // Call-site override used while materializing defaults such as @caller.
  let sourceLocationSpanOverride: SourceLocationSpanOverride | none = none
  // Concrete Doof monomorphization substitution active while emitting a
  // specialized function, class, or method body.
  let substitution: TypeSubstitution | none = none
  concreteFunctionNames: string[] = []
  concreteFunctionKeys: string[] = []
  concreteClassNames: string[] = []
  concreteClassKeys: string[] = []
  concreteMethodNames: string[] = []
  concreteMethodKeys: string[] = []
  concreteInterfaceNames: string[] = []
  concreteInterfaceKeys: string[] = []
  // Owners ("module::Name") of generic classes with at least one instantiation,
  // and generic interface instantiations without implementations. Together
  // they identify interfaces lowered to doof::NoImplementations.
  instantiatedClassOwners: string[] = []
  implementationlessInterfaceKeys: string[] = []
  jsonSerializationKeys: string[] = []
  jsonDeserializationKeys: string[] = []
  // Mutable locals captured by any lambda in the current callable. Their
  // declarations are heap-boxed and every identifier use dereferences the box.
  let capturedMutables: string[] = []
  private let temporaryCounter: int = 0
  loopLabels: string[] = []
  loopBreakTargets: string[] = []
  loopContinueTargets: string[] = []
  // One entry per enclosing loop, innermost last. Loops with a `then` clause
  // record the label an unlabeled `break` jumps to so it skips that clause.
  loopUnlabeledBreakTargets: string[] = []
  // Native entry scripts lower direct bindings into private deferred storage.
  let scriptEntry: bool = false
  let tryPanics: bool = false
  let metricsClassLifecycle: bool = false
  // Coverage is configured per source module by the graph emitter.
  let coverageEnabled: bool = false
  let coverageModuleId: int = -1
  coverageInstrumentedLines: int[] = []

  // Operands of the `async` or actor call being lowered. Each is evaluated
  // once into a caller-side temporary before work is dispatched to another
  // domain; see emitter-expr-actor.do.
  let hoistedOperands: HoistedOperand[] = []

  /** A number not yet used for a generated local in this context. */
  nextTemporaryId(): int {
    temporaryCounter += 1
    return temporaryCounter
  }

  /** A fresh generated C++ local name: `prefix` followed by a new id. */
  temporary(prefix: string): string => prefix + string(nextTemporaryId())
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

export function createEmitContextForModule(program: Program, modulePath: string, declarations: DeclarationIndex = DeclarationIndex {}): EmitContext {
  context := EmitContext { declarations: if declarations.programs.length == 0 then DeclarationIndex { programs: [program] } else declarations }
  context.modulePath = modulePath
  context.sourcePath = modulePath
  return context
}

/** A call operand that is evaluated in the caller's domain before dispatch. */
export class HoistedOperand {
  span: SourceSpan
  kind: string
  let temporary: string = ""
  let initializer: string = ""
}
