// Public facade and module-level orchestration for the Doof checker.
//
// Focused checker phases operate on CheckerState through module functions.
// ModuleChecker remains as the small stable API consumed by the compiler.

import { AnalysisResult } from "./analyzer"
import { Binding, CheckResult, Diagnostic, Scope } from "./semantic"
import { CheckerState } from "./checker-state"
import { checkStatement, validateInterfaces } from "./checker-statements"
import { checkExpression } from "./checker-expressions"
import { resolveType } from "./checker-resolution"
import { collectRetiredActorBindings, reportRetiredActorUses } from "./checker-actor-lifecycle"
import { discoverInterfaceImplementations, findModule } from "./checker-interfaces"
import { declare, predeclareModuleBindings } from "./checker-symbols"
import { checkerSemanticSpan, validateCheckedTypes as validateCheckedTypesImpl } from "./checker-validation"
import { validateIsolationEffects as validateIsolationEffectsImpl } from "./checker-isolation"
import { validateDeepReadonlyFields as validateDeepReadonlyFieldsImpl } from "./checker-actor-boundary"
import {
  ConstDeclaration, ExportDeclaration, ExportList, FunctionDeclaration, ImportDeclaration,
  ImmutableBinding, InterfaceDeclaration, ClassDeclaration, EnumDeclaration, LetDeclaration,
  MockImportDirective, ReadonlyDeclaration, Statement, TryStatement, TypeAliasDeclaration,
} from "./ast"
import { applyDeepReadonly, arrayType, primitive, unknownType, weakType } from "./checker-types"
import { typeError } from "./checker-common"
import { validateModuleInitializerStatement } from "./checker-module-initialization"
import { optionalResolvedType } from "./checker-symbols"

export class ModuleChecker {
  state: CheckerState

  check(entry: string): CheckResult {
    return checkModule(state, entry)
  }
}

// Reset only per-module state; the analysis graph is shared across checks so
// dependency-first checking can decorate every module in the same graph.
function checkModule(state: CheckerState, entry: string): CheckResult {
  state.diagnostics = []
  state.info = findModule(state.result, if entry.endsWith(".do") then entry else entry + ".do")
  if state.info == none { return CheckResult { diagnostics: state.diagnostics } }
  discoverInterfaceImplementations(state.result)
  state.moduleScope = Scope { parent: none }
  predeclareModuleBindings(state.info!, state.moduleScope!, state.result)
  let scriptEntry = false
  let rejectedWasmScript = false
  if state.info!.path == state.entry {
    for statement of state.info!.program.statements {
      if !isModuleDeclaration(statement) { scriptEntry = true }
    }
  }
  if scriptEntry && state.entryMode == "wasm" {
    for statement of state.info!.program.statements {
      if !isModuleDeclaration(statement) {
        typeError(state, "WebAssembly entry modules do not support top-level executable statements", statement.span)
      }
    }
    rejectedWasmScript = true
    scriptEntry = false
  }
  if scriptEntry {
    for statement of state.info!.program.statements {
      if isExport(statement) {
        typeError(state, "Native script entry modules cannot export declarations", statement.span)
      }
      if scriptGlobalName(statement) == "arguments" {
        typeError(state, "'arguments' is reserved by native script entry modules", statement.span)
      }
    }
  }
  scriptScope := Scope { parent: state.moduleScope, tryPanics: scriptEntry }
  if scriptEntry {
    declare(scriptScope, Binding {
      name: "arguments", kind: "script-arguments", type_: arrayType(primitive("string")), mutable: false,
      span: checkerSemanticSpan(state.info!.program.span), module: state.info!.path,
    })
  }
  let retiredActors: Binding[] = []
  for statement of state.info!.program.statements {
    if scriptEntry && isScriptGlobalDeclaration(statement) {
      checkStatement(state, statement, scriptScope)
      promoteScriptBinding(statement, scriptScope, state.moduleScope!)
    } else if scriptEntry && !isModuleDeclaration(statement) {
      checkStatement(state, statement, scriptScope)
    } else {
      if !scriptEntry && !rejectedWasmScript && !isModuleDeclaration(statement) {
        typeError(state, "Top-level executable statements are only allowed in a native entry module", statement.span)
      }
      checkStatement(state, statement, state.moduleScope!)
      if !scriptEntry { validateModuleInitializerStatement(state, statement) }
    }
    reportRetiredActorUses(statement, retiredActors, state.info!.path, state.diagnostics)
    collectRetiredActorBindings(statement, retiredActors)
  }
  validateInterfaces(state, state.info!)
  return CheckResult { diagnostics: state.diagnostics }
}

function scriptGlobalName(statement: Statement): string {
  let declaration = statement
  case statement {
    try_: TryStatement -> { declaration = try_.binding }
    _ -> { }
  }
  case declaration {
    value: ConstDeclaration -> { return value.name }
    value: ReadonlyDeclaration -> { return value.name }
    value: ImmutableBinding -> { return value.name }
    value: LetDeclaration -> { return value.name }
    _ -> { return "" }
  }
  return ""
}

function isScriptValueDeclaration(statement: Statement): bool {
  case statement {
    _: ConstDeclaration -> { return true }
    _: ReadonlyDeclaration -> { return true }
    _: ImmutableBinding -> { return true }
    _: LetDeclaration -> { return true }
    _ -> { return false }
  }
  return false
}

function isScriptGlobalDeclaration(statement: Statement): bool {
  if isScriptValueDeclaration(statement) { return true }
  case statement {
    try_: TryStatement -> { return isScriptValueDeclaration(try_.binding) }
    _ -> { return false }
  }
  return false
}

function isModuleDeclaration(statement: Statement): bool {
  if isScriptValueDeclaration(statement) { return true }
  case statement {
    _: FunctionDeclaration -> { return true }
    _: ClassDeclaration -> { return true }
    _: InterfaceDeclaration -> { return true }
    _: EnumDeclaration -> { return true }
    _: TypeAliasDeclaration -> { return true }
    _: ImportDeclaration -> { return true }
    _: MockImportDirective -> { return true }
    _: ExportDeclaration -> { return true }
    _: ExportList -> { return true }
    _ -> { return false }
  }
  return false
}

function isExport(statement: Statement): bool {
  case statement {
    _: ExportDeclaration -> { return true }
    _: ExportList -> { return true }
    const_: ConstDeclaration -> { return const_.exported }
    readonly_: ReadonlyDeclaration -> { return readonly_.exported }
    fn: FunctionDeclaration -> { return fn.exported }
    class_: ClassDeclaration -> { return class_.exported }
    interface_: InterfaceDeclaration -> { return interface_.exported }
    enum_: EnumDeclaration -> { return enum_.exported }
    alias: TypeAliasDeclaration -> { return alias.exported }
    _ -> { return false }
  }
  return false
}

function promoteScriptBinding(statement: Statement, scriptScope: Scope, moduleScope: Scope): none {
  let name = ""
  let declaration = statement
  case statement {
    try_: TryStatement -> { declaration = try_.binding }
    _ -> { }
  }
  case declaration {
    value: ConstDeclaration -> { name = value.name }
    value: ReadonlyDeclaration -> { name = value.name }
    value: ImmutableBinding -> { name = value.name }
    value: LetDeclaration -> { name = value.name }
    _ -> { return }
  }
  if name == "" || name == "_" { return }
  for binding of scriptScope.bindings {
    if binding.name == name && binding.kind != "script-arguments" {
      binding.kind = "script-global"
      moduleScope.bindings.push(binding)
      return
    }
  }
}

export function createChecker(result: AnalysisResult, entry: string = "", entryMode: string = "executable"): ModuleChecker {
  state := CheckerState { result, entry: if entry.endsWith(".do") then entry else entry + ".do", entryMode }
  prepareClassFieldTypes(state)
  return ModuleChecker { state }
}

// Class declarations are semantic signatures consumed across module
// boundaries. Prepare their field types graph-wide before checking any body so
// an import cycle cannot expose an inferred field as UnknownType merely because
// its owning module has not reached its class statement yet. This pass is
// intentionally diagnostic-free and converges over fields whose defaults
// depend on other declarations; normal class checking still validates every
// initializer and reports errors in its owning module.
function prepareClassFieldTypes(state: CheckerState): none {
  let changed = true
  while changed {
    changed = false
    for module of state.result.modules {
      state.info = module
      state.moduleScope = Scope { parent: none }
      predeclareModuleBindings(module, state.moduleScope!, state.result)
      for statement of module.program.statements {
        case statement {
          class_: ClassDeclaration -> {
            classScope := Scope { parent: state.moduleScope, typeParams: class_.typeParams }
            for field of class_.fields {
              if field.resolvedType != none { continue }
              diagnosticCount := state.diagnostics.length
              let fieldType = unknownType()
              if field.type_ != none {
                fieldType = resolveType(state, field.type_!, module, classScope)
              } else if field.defaultValue != none {
                previousAllowsCaller := state.allowsCaller
                state.allowsCaller = true
                fieldType = checkExpression(state, field.defaultValue!, classScope, none)
                state.allowsCaller = previousAllowsCaller
              }
              while state.diagnostics.length > diagnosticCount { ignored := try! state.diagnostics.pop() }
              if fieldType.kind == "unknown" { continue }
              if field.readonly_ || field.const_ { fieldType = applyDeepReadonly(fieldType) }
              field.resolvedType = optionalResolvedType(if field.weak_ then weakType(fieldType) else fieldType)
              changed = true
            }
          }
          _ -> { }
        }
      }
    }
  }
  state.diagnostics = []
  state.info = none
  state.moduleScope = none
}

export function validateCheckedTypes(result: AnalysisResult): Diagnostic[] {
  return validateCheckedTypesImpl(result)
}

// Isolation is a graph-wide phase. Run it only after every module has been
// checked so all bindings and types are decorated and the graph is scanned once.
export function validateIsolationEffects(result: AnalysisResult): Diagnostic[] {
  let diagnostics: Diagnostic[] = []
  validateIsolationEffectsImpl(result, diagnostics)
  return diagnostics
}

export function validateDeepReadonlyFields(result: AnalysisResult): Diagnostic[] {
  return validateDeepReadonlyFieldsImpl(result)
}
