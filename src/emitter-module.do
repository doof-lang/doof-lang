// Module-level orchestration for the Doof C++ emitter.
//
// Worldview planning stays at this boundary so expression and statement
// emitters remain independent of module layout. Every analyzed module becomes
// its own self-contained header/source pair.

import {
  BoolLiteral, CharLiteral, ClassDeclaration, ConstDeclaration, DotShorthand, DoubleLiteral, EnumDeclaration, ExportDeclaration, ExportList, Expression, FloatLiteral, FunctionDeclaration,
  ImmutableBinding, ImportDeclaration, InterfaceDeclaration, LetDeclaration, MockImportDirective, Program,
  IntLiteral, LongLiteral, ReadonlyDeclaration, Statement, TryStatement, TypeAliasDeclaration,
} from "./ast"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import { createEmitContextForModule, EmitContext, EmitModuleSurface, generatedLineDirective } from "./emitter-context"
import { emitClassDeclaration, emitClassDestructorDefinition, emitClassMethodDefinition, emitFunctionDeclaration, emitFunctionDefinition, emitModuleValueStorage, emitNativeFunctionAdapterDefinition, emitStaticClassFieldDefinitions } from "./emitter-decl"
import { emitGeneratedJsonMethods, emitInterfaceJsonDefinition } from "./emitter-json"
import { emitMetadataDefinition } from "./emitter-metadata"
import { emitStatement } from "./emitter-stmt"
import { emitContextType } from "./emitter-types"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { HeaderPlan, HeaderSection, planHeader, renderProjectedHeader, reserveHeaderNamespaceName } from "./emitter-header"
import { indexWorldviewGraph, planWorldview, WorldviewModule } from "./emitter-worldview"
import { buildInstantiationPlan, classInstantiationKey, InstantiationPlan, MethodInstantiation } from "./emitter-monomorphize"
import { moduleHeaderName, moduleNamespace, moduleSourceName } from "./emitter-names"
import { sha256HexString } from "std/crypto"
import { JsonEligibilityCache } from "./json-semantics"
import { StringBuilder } from "./string-builder"
import {
  ActorType, ArrayResolvedType, ClassType, EnumType, FunctionType, ImportBinding, InterfaceType, MapResolvedType, NamespaceBinding,
  PromiseType, ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType, TupleResolvedType, UnionResolvedType, WeakResolvedType,
} from "./semantic"

export class ModulePlan {
  path: string
  namespaceName: string
  headerName: string
  sourceName: string
}

export class ModuleGraphPlan {
  modules: ModulePlan[] = []
}

// Plan stable output names before split-module emission.
export function planModuleGraph(result: AnalysisResult): ModuleGraphPlan {
  plan := ModuleGraphPlan {}
  for info of result.modules {
    module := ModulePlan {
      path: info.path,
      namespaceName: moduleNamespace(info.path),
      headerName: moduleHeaderName(info.path),
      sourceName: moduleSourceName(info.path),
    }
    plan.modules.push(module)
  }
  return plan
}

export class ModuleEmission {
  modulePath: string
  header: string
  source: string
  headerName: string
  sourceName: string
  coverageModuleId: int = -1
  instrumentedLines: int[] = []
  // Exact frontend-cache hits retain the already materialized files. The
  // native planner still consumes their stable names.
  reused: bool = false
  let fingerprint: string = ""
}

export class ModuleEmissionCacheKey {
  modulePath: string
  fingerprint: string
}

export class CoverageModuleMetadata {
  moduleId: int
  modulePath: string
  instrumentedLines: int[] = []
}

export class ModuleGraphEmission {
  modules: ModuleEmission[] = []
  coverageModules: CoverageModuleMetadata[] = []
  let wasmSupportSource: string = ""
  let wasmExportNames: string[] = []
}

class CxxModuleEmitter {
  headerNameOverride: string = ""
  sourceNameOverride: string = ""
  namespaceNameOverride: string = ""
  modulePath: string = ""
  allPrograms: Program[] = []
  namespaceImports: NamespaceBinding[] = []
  imports: ImportBinding[] = []
  moduleSurfaces: EmitModuleSurface[] = []
  let worldviewModules: WorldviewModule[] = []
  let worldviewInterfaceKeys: string[] = []
  instantiations: InstantiationPlan | none = none
  coverageModuleId: int = -1
  initializationModuleNamespaces: string[] = []
  jsonEligibility: JsonEligibilityCache = JsonEligibilityCache {}
  sourcePaths: Map<string, string> = {}

  emit(program: Program, entryMode: string = "executable"): ModuleEmission {
    context := createEmitContextForModule(program, modulePath, allPrograms)
    context.namespaceImports = namespaceImports
    context.sourcePath = sourcePathFor(sourcePaths, context.modulePath)
    context.imports = imports
    context.moduleSurfaces = moduleSurfaces
    context.jsonEligibility = jsonEligibility
    if coverageModuleId >= 0 {
      context.coverageEnabled = true
      context.coverageModuleId = coverageModuleId
    }
    if instantiations != none { configureInstantiationRegistry(context, instantiations!) }
    let sections: HeaderSection[] = []
    let plan: HeaderPlan | none = none
    let views = worldviewModules
    if views.length == 0 { views = [WorldviewModule { path: modulePath, program }] }
    for view of views {
      sectionContext := createEmitContextForModule(view.program, view.path, allPrograms)
      sectionContext.imports = surfaceImports(moduleSurfaces, view.path)
      sectionContext.sourcePath = sourcePathFor(sourcePaths, view.path)
      sectionContext.moduleSurfaces = moduleSurfaces
      sectionContext.jsonEligibility = jsonEligibility
      if instantiations != none { configureInstantiationRegistry(sectionContext, instantiations!) }
      sectionPlan := planHeader(
        view.program,
        sectionContext,
        if instantiations == none then [] else instantiations!.methods,
        if instantiations == none then [] else instantiations!.classes,
      )
      if instantiations != none {
        addConcreteHeaderDeclarations(sectionPlan, sectionContext, instantiations!, view.program, worldviewInterfaceKeys)
      }
      sectionNamespace := if view.path == modulePath
        then namespaceNameOverride
        else moduleNamespace(view.path)
      sections.push(HeaderSection { namespaceName: sectionNamespace, plan: sectionPlan })
      if view.path == modulePath { plan = sectionPlan }
    }
    if plan == none { panic("worldview omitted root module " + modulePath) }
    context.scriptEntry = (entryMode == "executable" || entryMode == "ios-app") && hasScriptStatements([program])
    return emitPlanned([program], context, plan!, sections, entryMode)
  }

  private emitPlanned(programs: Program[], context: EmitContext, plan: HeaderPlan, sections: HeaderSection[], entryMode: string): ModuleEmission {
    headerName := headerNameOverride
    sourceName := sourceNameOverride
    namespaceName := namespaceNameOverride
    header := renderProjectedHeader(sections)
    sourceBuilder := StringBuilder()
    sourceBuilder.append("#include \"" + headerName + "\"\n\n")
    for namespace of initializationModuleNamespaces {
      sourceBuilder.append("namespace " + namespace + " { void __doof_initialize_module(); }\n")
    }
    if initializationModuleNamespaces.length > 0 { sourceBuilder.append("\n") }
    sourceBuilder.append("namespace " + namespaceName + " {\n")
    sourceBuilder.append(emitImportedNamespaces(context, worldviewModules))
    if context.scriptEntry { sourceBuilder.append(emitScriptStorage(programs, context)) }
    for program of programs {
      for statement of program.statements {
        if !(context.scriptEntry && scriptGlobalDeclaration(statement) != none) {
          sourceBuilder.append(emitSourceStatement(statement, context))
        }
      }
    }
    sourceBuilder.append(generatedLineDirective())
    sourceBuilder.append(emitModuleInitializer(programs, context, !context.scriptEntry))
    if context.scriptEntry { sourceBuilder.append(emitScriptRunner(programs, context)) }
    if instantiations != none {
      sourceBuilder.append(emitConcreteClassDefinitions(context, instantiations!))
      sourceBuilder.append(emitConcreteMethodDefinitions(context, instantiations!))
      sourceBuilder.append(emitConcreteFunctions(context, instantiations!))
    }
    sourceBuilder.append("}\n")
    nativeMethods := emitNativeClassMethods(programs, context)
    if nativeMethods != "" {
      sourceBuilder.append("\nusing namespace ::" + namespaceName + ";\n\n" + nativeMethods)
    }
    initializationCall := emitGraphInitializationCall(initializationModuleNamespaces)
    if entryMode == "executable" && (plan.hasMain || context.scriptEntry) { sourceBuilder.append(generatedLineDirective() + emitMainWrapper(namespaceName, plan, context.scriptEntry, initializationCall)) }
    if entryMode == "ios-app" && (plan.hasMain || context.scriptEntry) { sourceBuilder.append(generatedLineDirective() + emitAppEntryWrapper(namespaceName, plan, context.scriptEntry, initializationCall)) }
    source := sourceBuilder.drainToString()
    return ModuleEmission {
      modulePath: context.modulePath, header, source, headerName, sourceName,
      coverageModuleId: context.coverageModuleId,
      instrumentedLines: sortedCoverageLines(context.coverageInstrumentedLines),
    }
  }
}

function sourcePathFor(paths: Map<string, string>, modulePath: string): string {
  path := paths.get(modulePath) else { return modulePath }
  return path
}

function hasScriptStatements(programs: Program[]): bool {
  for program of programs { for statement of program.statements {
    if !isModuleDeclaration(statement) { return true }
  } }
  return false
}

function isValueDeclaration(statement: Statement): bool {
  case statement {
    _: ConstDeclaration -> { return true }
    _: ReadonlyDeclaration -> { return true }
    _: ImmutableBinding -> { return true }
    _: LetDeclaration -> { return true }
    _ -> { return false }
  }
  return false
}

function isModuleDeclaration(statement: Statement): bool {
  if isValueDeclaration(statement) { return true }
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

function scriptGlobalDeclaration(statement: Statement): Statement | none {
  if isValueDeclaration(statement) { return statement }
  case statement {
    try_: TryStatement -> { case try_.binding {
      value: ConstDeclaration -> { return value }
      value: ReadonlyDeclaration -> { return value }
      value: ImmutableBinding -> { return value }
      value: LetDeclaration -> { return value }
      _ -> { }
    } }
    _ -> { }
  }
  return none
}

function scriptDeclarationName(statement: Statement): string {
  case statement {
    value: ConstDeclaration -> { return value.name }
    value: ReadonlyDeclaration -> { return value.name }
    value: ImmutableBinding -> { return value.name }
    value: LetDeclaration -> { return value.name }
    _ -> { return "" }
  }
  return ""
}

function scriptDeclarationType(statement: Statement): ResolvedType | none {
  case statement {
    value: ConstDeclaration -> { return value.resolvedType }
    value: ReadonlyDeclaration -> { return value.resolvedType }
    value: ImmutableBinding -> { return value.resolvedType }
    value: LetDeclaration -> { return value.resolvedType }
    _ -> { return none }
  }
  return none
}

function scriptDeclarationMutable(statement: Statement): bool {
  case statement {
    _: LetDeclaration -> { return true }
    _ -> { return false }
  }
  return false
}

function emitScriptStorage(programs: Program[], context: EmitContext): string {
  let source = "\n"
  for program of programs { for statement of program.statements {
    declaration := scriptGlobalDeclaration(statement)
    if declaration == none { continue }
    name := scriptDeclarationName(declaration!)
    type_ := scriptDeclarationType(declaration!)
    if name == "" || name == "_" || type_ == none { continue }
    cppName := cppIdentifier(name)
    typeText := emitContextType(type_!, context)
    source = source + "std::optional<" + typeText + "> __doof_script_storage_" + cppName + ";\n"
    returnType := if scriptDeclarationMutable(declaration!) then typeText + "&" else "const " + typeText + "&"
    source = source + returnType + " __doof_script_get_" + cppName + "() { if (!__doof_script_storage_" + cppName + ".has_value()) doof::panic(\"Entry binding '" + name + "' was accessed before initialization\"); return *__doof_script_storage_" + cppName + "; }\n"
  } }
  return source + "\n"
}

function emitScriptRunner(programs: Program[], context: EmitContext): string {
  previousTryPanics := context.tryPanics
  context.tryPanics = true
  let source = "\nvoid __doof_run_script(std::shared_ptr<std::vector<std::string>> arguments) {\n"
  for program of programs { for statement of program.statements {
    declaration := scriptGlobalDeclaration(statement)
    if declaration != none {
      source = source + emitStatement(statement, 1, context)
      name := scriptDeclarationName(declaration!)
      if name != "" && name != "_" { source = source + "    __doof_script_storage_" + cppIdentifier(name) + ".emplace(" + cppIdentifier(name) + ");\n" }
    } else if !isModuleDeclaration(statement) {
      source = source + emitStatement(statement, 1, context)
    }
  } }
  context.tryPanics = previousTryPanics
  return source + "}\n"
}

function containsString(values: string[], value: string): bool {
  for existing of values { if existing == value { return true } }
  return false
}

function emitImportedNamespaces(context: EmitContext, worldviewModules: WorldviewModule[]): string {
  let namespaces: string[] = []
  for imported of context.imports {
    if !worldviewContainsModule(worldviewModules, imported.sourceModule) { continue }
    namespace := moduleNamespace(imported.sourceModule)
    addNamespace(namespaces, namespace)
  }
  for imported of context.namespaceImports {
    if !worldviewContainsModule(worldviewModules, imported.sourceModule) { continue }
    namespace := moduleNamespace(imported.sourceModule)
    addNamespace(namespaces, namespace)
  }
  let result = ""
  for namespace of namespaces { result = result + "using namespace ::" + namespace + ";\n" }
  return result
}

function worldviewContainsModule(modules: WorldviewModule[], path: string): bool {
  for module of modules { if module.path == path { return true } }
  return false
}

function addNamespace(namespaces: string[], namespace: string): none {
  for existing of namespaces { if existing == namespace { return } }
  namespaces.push(namespace)
}

// Emit one header/source pair for every analyzed module.
export function emitModuleGraph(
  result: AnalysisResult,
  entry: string = "",
  instantiations: InstantiationPlan | none = none,
  entryMode: string = "executable",
  coverage: bool = false,
  reusableModules: ModuleEmissionCacheKey[] = [],
  configurationFingerprint: string = "",
  physicalSourcePaths: bool = false,
): ModuleGraphEmission {
  graph := ModuleGraphEmission {}
  concretePlan := instantiations ?? buildInstantiationPlan(result)
  plan := planModuleGraph(result)
  initializationOrder := planModuleInitializationOrder(result, entry, entryMode)
  graphPrograms := allPrograms(result)
  graphSurfaces := emitModuleSurfaces(result)
  moduleIndex := indexGraphModules(result)
  reusableFingerprints := indexReusableModuleFingerprints(reusableModules)
  instantiationFingerprintInput := moduleInstantiationFingerprintInput(concretePlan)
  jsonEligibility := JsonEligibilityCache {}
  worldviewGraphIndex := indexWorldviewGraph(result)
  let sourcePaths: Map<string, string> = {}
  for info of result.modules {
    sourcePaths.set(info.path, if physicalSourcePaths && info.physicalPath != "" then info.physicalPath else info.path)
  }
  let nextCoverageModuleId = 0
  for module of plan.modules {
    info := indexedGraphModule(moduleIndex, module.path)
    if info == none { continue }
    let coverageModuleId = -1
    if coverage && isCoverageEligible(module.path) {
      coverageModuleId = nextCoverageModuleId
      nextCoverageModuleId += 1
    }
    fingerprint := moduleEmissionFingerprint(
      result, moduleIndex, module.path, entry, entryMode, coverage,
      initializationOrder, configurationFingerprint + "\nphysical-source-paths:" + string(physicalSourcePaths), instantiationFingerprintInput,
    )
    if !coverage && reusableModuleMatches(reusableFingerprints, module.path, fingerprint) {
      graph.modules.push(ModuleEmission {
        modulePath: module.path, headerName: module.headerName, sourceName: module.sourceName,
        header: "", source: "", reused: true, fingerprint,
      })
      continue
    }
    emitter := CxxModuleEmitter {
      headerNameOverride: module.headerName,
      sourceNameOverride: module.sourceName,
      namespaceNameOverride: module.namespaceName,
      modulePath: module.path,
      allPrograms: graphPrograms,
      namespaceImports: infoNamespaceImports(result, module.path),
      imports: infoImports(result, module.path),
      moduleSurfaces: graphSurfaces,
      instantiations: concretePlan,
      coverageModuleId,
      initializationModuleNamespaces: if module.path == entry then moduleInitializationNamespaces(initializationOrder) else [],
      jsonEligibility,
      sourcePaths,
    }
    worldview := planWorldview(result, module.path, concretePlan, worldviewGraphIndex)
    emitter.worldviewModules = worldview.modules
    emitter.worldviewInterfaceKeys = worldview.interfaceKeys
    emitted := emitter.emit(info!.program, if module.path == entry then entryMode else "none")
    emitted.fingerprint = fingerprint
    graph.modules.push(emitted)
    if coverageModuleId >= 0 {
      graph.coverageModules.push(CoverageModuleMetadata {
        moduleId: coverageModuleId,
        modulePath: module.path,
        instrumentedLines: emitted.instrumentedLines,
      })
    }
  }
  return graph
}

function indexGraphModules(result: AnalysisResult): Map<string, ModuleInfo> {
  let indexed: Map<string, ModuleInfo> = {}
  for module of result.modules { indexed.set(module.path, module) }
  return indexed
}

function indexedGraphModule(indexed: Map<string, ModuleInfo>, path: string): ModuleInfo | none {
  module := indexed.get(path) else { return none }
  return module
}

function indexReusableModuleFingerprints(keys: ModuleEmissionCacheKey[]): Map<string, string> {
  let indexed: Map<string, string> = {}
  for key of keys {
    if !indexed.has(key.modulePath) { indexed.set(key.modulePath, key.fingerprint) }
  }
  return indexed
}

function reusableModuleMatches(indexed: Map<string, string>, path: string, fingerprint: string): bool {
  cached := indexed.get(path) else { return false }
  return cached == fingerprint
}

// Every module fingerprint includes the same closed-world specialization plan.
// Build that potentially large input once per graph rather than once per module.
function moduleInstantiationFingerprintInput(instantiations: InstantiationPlan): string {
  let value = ""
  for item of instantiations.functions { value = value + "\nfunction:" + item.key }
  for item of instantiations.classes { value = value + "\nclass:" + item.key }
  for item of instantiations.methods { value = value + "\nmethod:" + item.key }
  for item of instantiations.interfaces {
    value = value + "\ninterface:" + item.key
    for implementation of item.implementations {
      value = value + ":" + implementation.modulePath + ":" + implementation.typeName
    }
  }
  for key of instantiations.jsonSerializationKeys { value = value + "\njson-serialize:" + key }
  for key of instantiations.jsonDeserializationKeys { value = value + "\njson-deserialize:" + key }
  return value
}

function moduleEmissionFingerprint(
  result: AnalysisResult,
  moduleIndex: Map<string, ModuleInfo>,
  path: string,
  entry: string,
  entryMode: string,
  coverage: bool,
  initializationOrder: string[],
  configurationFingerprint: string,
  instantiationFingerprintInput: string,
): string {
  let value = "doof-module-emission-2\n" + configurationFingerprint + "\n" + path + "\n" +
    entryMode + "\n" + string(coverage)
  let reachable: Set<string> = []
  collectModuleDependencyClosure(moduleIndex, path, reachable)
  for candidate of result.modules {
    if reachable.has(candidate.path) {
      value = value + "\nsource:" + candidate.path + ":" + candidate.sourceHash
    }
  }
  // Concrete specialization ownership can flow opposite to import edges: a
  // caller may add code to a generic declaration's module. Include the global
  // plan conservatively so such changes can never retain stale C++.
  value = value + instantiationFingerprintInput
  if path == entry {
    for initialized of initializationOrder { value = value + "\ninitialize:" + initialized }
  }
  return sha256HexString(value)
}

function collectModuleDependencyClosure(moduleIndex: Map<string, ModuleInfo>, path: string, reachable: Set<string>): none {
  if reachable.has(path) { return }
  reachable.add(path)
  module := indexedGraphModule(moduleIndex, path)
  if module == none { return }
  for imported of module!.imports { collectModuleDependencyClosure(moduleIndex, imported.sourceModule, reachable) }
  for imported of module!.namespaceImports { collectModuleDependencyClosure(moduleIndex, imported.sourceModule, reachable) }
  for reExport of module!.reExports { collectModuleDependencyClosure(moduleIndex, reExport, reachable) }
}

function isCoverageEligible(modulePath: string): bool {
  return !modulePath.endsWith(".test.do")
    && !modulePath.contains("/.doof-tests/")
    && !modulePath.startsWith("/std/")
}

function sortedCoverageLines(lines: int[]): int[] {
  let result: int[] = []
  let last = -1
  for count of 0..<lines.length {
    let candidate: int | none = none
    for line of lines {
      if line > last && (candidate == none || line < candidate!) { candidate = line }
    }
    if candidate != none { result.push(candidate!); last = candidate! }
  }
  return result
}

function configureInstantiationRegistry(context: EmitContext, plan: InstantiationPlan): none {
  for instantiation of plan.functions {
    context.concreteFunctionKeys.push(instantiation.key)
    context.concreteFunctionNames.push(instantiation.emittedName)
  }
  for instantiation of plan.classes {
    context.concreteClassKeys.push(instantiation.key)
    context.concreteClassNames.push(instantiation.emittedName)
  }
  for instantiation of plan.methods {
    context.concreteMethodKeys.push(instantiation.key)
    context.concreteMethodNames.push(instantiation.emittedName)
  }
  for instantiation of plan.interfaces {
    context.concreteInterfaceKeys.push(instantiation.key)
    context.concreteInterfaceNames.push(instantiation.emittedName)
  }
  for key of plan.jsonSerializationKeys { context.jsonSerializationKeys.push(key) }
  for key of plan.jsonDeserializationKeys { context.jsonDeserializationKeys.push(key) }
}

function addConcreteHeaderDeclarations(
  plan: HeaderPlan,
  context: EmitContext,
  instantiations: InstantiationPlan,
  program: Program,
  interfaceKeys: string[] = [],
): none {
  for instantiation of instantiations.methods {
    if instantiation.modulePath != context.modulePath { continue }
    if !programDeclares(program, instantiation.owner.name) { continue }
    for argument of instantiation.substitution.arguments { addConcreteTypeForwardDeclarations(plan, context, argument) }
  }
  for interface_ of instantiations.interfaces {
    if !containsString(interfaceKeys, interface_.key) { continue }
    if interface_.name != "Stream" && interface_.modulePath != context.modulePath { continue }
    if interface_.name != "Stream" && !programDeclares(program, interface_.name) { continue }
    let alternatives = ""
    for implementation of interface_.implementations {
      if alternatives != "" { alternatives = alternatives + ", " }
      let typeName = implementation.typeName
      if implementation.modulePath != context.modulePath {
        namespace := moduleNamespace(implementation.modulePath)
        plan.typeOnlyForwardDeclarations.push("namespace " + namespace + " { struct " + implementation.typeName + "; }\n")
        typeName = "::" + namespace + "::" + typeName
      }
      alternatives = alternatives + "std::shared_ptr<" + typeName + ">"
    }
    if alternatives == "" { alternatives = "std::monostate" }
    reserveHeaderNamespaceName(plan, interface_.emittedName)
    plan.interfaceAliases.push("using " + interface_.emittedName + " = std::variant<" + alternatives + ">;\n")
  }
  for instantiation of instantiations.classes {
    if instantiation.modulePath != context.modulePath { continue }
    if !programDeclares(program, instantiation.declaration.name) { continue }
    for argument of instantiation.substitution.arguments { addConcreteTypeForwardDeclarations(plan, context, argument) }
    plan.classForwardDeclarations.push("struct " + instantiation.emittedName + ";\n")
    reserveHeaderNamespaceName(plan, instantiation.emittedName)
    context.substitution = instantiation.substitution
    let methods: MethodInstantiation[] = []
    for method of instantiations.methods { if method.ownerKey == instantiation.key { methods.push(method) } }
    plan.classDefinitions.push(emitClassDeclaration(instantiation.declaration, context, instantiation.emittedName, methods))
    clearInstantiation(context)
  }
  for instantiation of instantiations.functions {
    if instantiation.modulePath != context.modulePath { continue }
    if !programDeclares(program, instantiation.declaration.name) { continue }
    for argument of instantiation.substitution.arguments { addConcreteTypeForwardDeclarations(plan, context, argument) }
    context.substitution = instantiation.substitution
    signature := emitFunctionDeclaration(instantiation.declaration, instantiation.emittedName, context.modulePath, context)
    reserveHeaderNamespaceName(plan, instantiation.emittedName)
    if instantiation.declaration.native_ { plan.nativeAdapterSignatures.push(signature) }
    else { plan.functionSignatures.push(signature) }
    clearInstantiation(context)
  }
}

function programDeclares(program: Program, name: string): bool {
  for statement of program.statements { if headerDeclarationName(statement) == name { return true } }
  return false
}

function headerDeclarationName(statement: Statement): string {
  case statement {
    export_: ExportDeclaration -> { return headerDeclarationName(export_.declaration) }
    class_: ClassDeclaration -> { return class_.name }
    interface_: InterfaceDeclaration -> { return interface_.name }
    fn: FunctionDeclaration -> { return fn.name }
    _ -> { return "" }
  }
  return ""
}

function addConcreteTypeForwardDeclarations(plan: HeaderPlan, context: EmitContext, type_: ResolvedType): none {
  case type_ {
    class_: ClassType -> {
      if class_.symbol.module != "" && class_.symbol.module != context.modulePath {
        typeName := concreteClassTypeName(context, class_)
        declaration := "namespace " + moduleNamespace(class_.symbol.module) + " { struct " + typeName + "; }\n"
        if !containsString(plan.typeOnlyForwardDeclarations, declaration) { plan.typeOnlyForwardDeclarations.push(declaration) }
      }
      for argument of class_.typeArgs { addConcreteTypeForwardDeclarations(plan, context, argument) }
    }
    enum_: EnumType -> {
      if enum_.symbol.module != "" && enum_.symbol.module != context.modulePath {
        declaration := "namespace " + moduleNamespace(enum_.symbol.module) + " { enum class " + enum_.name + "; }\n"
        if !containsString(plan.typeOnlyForwardDeclarations, declaration) { plan.typeOnlyForwardDeclarations.push(declaration) }
      }
    }
    interface_: InterfaceType -> { for argument of interface_.typeArgs { addConcreteTypeForwardDeclarations(plan, context, argument) } }
    array: ArrayResolvedType -> { addConcreteTypeForwardDeclarations(plan, context, array.elementType) }
    map: MapResolvedType -> { addConcreteTypeForwardDeclarations(plan, context, map.keyType); addConcreteTypeForwardDeclarations(plan, context, map.valueType) }
    set_: SetResolvedType -> { addConcreteTypeForwardDeclarations(plan, context, set_.elementType) }
    stream: StreamResolvedType -> { addConcreteTypeForwardDeclarations(plan, context, stream.elementType) }
    result_: ResultResolvedType -> { addConcreteTypeForwardDeclarations(plan, context, result_.valueType); addConcreteTypeForwardDeclarations(plan, context, result_.errorType) }
    actor: ActorType -> { addConcreteTypeForwardDeclarations(plan, context, actor.innerClass) }
    promise: PromiseType -> { addConcreteTypeForwardDeclarations(plan, context, promise.valueType) }
    tuple: TupleResolvedType -> { for element of tuple.elements { addConcreteTypeForwardDeclarations(plan, context, element) } }
    union_: UnionResolvedType -> { for member of union_.types { addConcreteTypeForwardDeclarations(plan, context, member) } }
    weak_: WeakResolvedType -> { addConcreteTypeForwardDeclarations(plan, context, weak_.inner) }
    function_: FunctionType -> {
      for parameter of function_.params { addConcreteTypeForwardDeclarations(plan, context, parameter.type_) }
      addConcreteTypeForwardDeclarations(plan, context, function_.returnType)
    }
    _ -> { }
  }
}

function concreteClassTypeName(context: EmitContext, class_: ClassType): string {
  if class_.typeArgs.length == 0 { return class_.name }
  key := classInstantiationKey(class_.symbol.module, class_.name, class_.typeArgs)
  for index of 0..<context.concreteClassKeys.length {
    if context.concreteClassKeys[index] == key { return context.concreteClassNames[index] }
  }
  panic("Missing concrete class instantiation for " + key)
  return ""
}

function emitConcreteFunctions(context: EmitContext, instantiations: InstantiationPlan): string {
  let result = ""
  for instantiation of instantiations.functions {
    if instantiation.modulePath != context.modulePath { continue }
    context.substitution = instantiation.substitution
    if instantiation.declaration.native_ { result = result + emitNativeFunctionAdapterDefinition(instantiation.declaration, instantiation.emittedName, context) }
    else { result = result + emitFunctionDefinition(instantiation.declaration, context, instantiation.emittedName) }
    clearInstantiation(context)
  }
  return result
}

function emitConcreteClassDefinitions(context: EmitContext, instantiations: InstantiationPlan): string {
  let result = ""
  for instantiation of instantiations.classes {
    if instantiation.modulePath != context.modulePath { continue }
    context.substitution = instantiation.substitution
    result = result + emitStaticClassFieldDefinitions(instantiation.declaration, context, instantiation.emittedName)
    for method of instantiation.declaration.methods {
      if method.typeParams.length == 0 {
        result = result + emitClassMethodDefinition(instantiation.declaration, method, context, instantiation.emittedName)
      }
    }
    result = result + emitClassDestructorDefinition(instantiation.declaration, context, instantiation.emittedName)
    clearInstantiation(context)
  }
  return result
}

function emitConcreteMethodDefinitions(context: EmitContext, instantiations: InstantiationPlan): string {
  let result = ""
  for instantiation of instantiations.methods {
    if instantiation.modulePath != context.modulePath { continue }
    context.substitution = instantiation.substitution
    result = result + emitClassMethodDefinition(
      instantiation.owner, instantiation.declaration, context,
      instantiation.ownerEmittedName, instantiation.emittedName,
    )
    clearInstantiation(context)
  }
  return result
}

function clearInstantiation(context: EmitContext): none {
  context.substitution = none
}

function emitModuleSurfaces(result: AnalysisResult): EmitModuleSurface[] {
  let surfaces: EmitModuleSurface[] = []
  for module of result.modules {
    let genericTypes: string[] = []
    for statement of module.program.statements { collectGenericSurfaceSymbols(statement, genericTypes) }
    surfaces.push(EmitModuleSurface { path: module.path, exports: module.exports, imports: module.imports, genericTypes })
  }
  return surfaces
}

function collectGenericSurfaceSymbols(statement: Statement, typeNames: string[]): none {
  case statement {
    class_: ClassDeclaration -> { if class_.typeParams.length > 0 { typeNames.push(class_.name) } }
    interface_: InterfaceDeclaration -> { if interface_.typeParams.length > 0 { typeNames.push(interface_.name) } }
    alias: TypeAliasDeclaration -> { if alias.typeParams.length > 0 { typeNames.push(alias.name) } }
    export_: ExportDeclaration -> { collectGenericSurfaceSymbols(export_.declaration, typeNames) }
    _ -> { }
  }
}

function allPrograms(result: AnalysisResult): Program[] {
  let programs: Program[] = []
  for module of result.modules { programs.push(module.program) }
  return programs
}

function surfaceImports(surfaces: EmitModuleSurface[], path: string): ImportBinding[] {
  for surface of surfaces { if surface.path == path { return surface.imports } }
  return []
}

function infoNamespaceImports(result: AnalysisResult, path: string): NamespaceBinding[] {
  for module of result.modules { if module.path == path { return module.namespaceImports } }
  return []
}

function infoImports(result: AnalysisResult, path: string): ImportBinding[] {
  for module of result.modules { if module.path == path { return module.imports } }
  return []
}

function findGraphModule(result: AnalysisResult, path: string): ModuleInfo | none {
  for module of result.modules { if module.path == path { return module } }
  return none
}

export function planModuleInitializationOrder(
  result: AnalysisResult,
  entry: string,
  entryMode: string = "executable",
): string[] {
  let order: string[] = []
  let visiting: string[] = []
  let visited: string[] = []
  visitInitializationModule(result, entry, entry, entryMode, visiting, visited, order)
  return order
}

function visitInitializationModule(
  result: AnalysisResult,
  path: string,
  entry: string,
  entryMode: string,
  visiting: string[],
  visited: string[],
  order: string[],
): none {
  if containsString(visited, path) || containsString(visiting, path) { return }
  info := findGraphModule(result, path)
  if info == none { return }
  visiting.push(path)
  for imported of info!.imports {
    if !imported.typeOnly { visitInitializationModule(result, imported.sourceModule, entry, entryMode, visiting, visited, order) }
  }
  for imported of info!.namespaceImports {
    if !imported.typeOnly { visitInitializationModule(result, imported.sourceModule, entry, entryMode, visiting, visited, order) }
  }
  for reExport of info!.reExports { visitInitializationModule(result, reExport, entry, entryMode, visiting, visited, order) }
  let ignored = try! visiting.pop()
  visited.push(path)
  scriptEntry := path == entry && (entryMode == "executable" || entryMode == "ios-app") &&
    hasScriptStatements([info!.program])
  if !scriptEntry && moduleHasDeferredInitialization(info!.program) { order.push(path) }
}

function moduleInitializationNamespaces(paths: string[]): string[] {
  let result: string[] = []
  for path of paths { result.push(moduleNamespace(path)) }
  return result
}

function emitSourceStatement(statement: Statement, context: EmitContext): string {
  case statement {
    fn: FunctionDeclaration -> {
      if fn.typeParams.length > 0 { return "" }
      return emitFunctionDefinition(fn, context, if fn.name == "main" then "doof_main" else fn.name)
    }
    class_: ClassDeclaration -> {
      if class_.native_ { return "" }
      let result = "\n" + emitStaticClassFieldDefinitions(class_, context)
      if class_.typeParams.length == 0 {
        for method of class_.methods { result = result + emitClassMethodDefinition(class_, method, context) }
        result = result + emitClassDestructorDefinition(class_, context)
      }
      result = result + emitGeneratedJsonMethods(class_, context)
      result = result + emitMetadataDefinition(class_, context)
      return result
    }
    interface_: InterfaceDeclaration -> { return emitInterfaceJsonDefinition(interface_, context) }
    const_: ConstDeclaration -> { return emitModuleStorage(const_, const_.value, context) }
    readonly_: ReadonlyDeclaration -> { return emitModuleStorage(readonly_, readonly_.value, context) }
    binding: ImmutableBinding -> { return emitModuleStorage(binding, binding.value, context) }
    let_: LetDeclaration -> { return emitModuleStorage(let_, let_.value, context) }
    export_: ExportDeclaration -> { return emitSourceStatement(export_.declaration, context) }
    _ -> { return "" }
  }
  return ""
}

function emitModuleStorage(
  declaration: ConstDeclaration | ReadonlyDeclaration | ImmutableBinding | LetDeclaration,
  value: Expression,
  context: EmitContext,
): string {
  initializer := if isCxxConstantInitializer(value) then emitExpression(value, context, moduleValueType(declaration)) else ""
  return emitModuleValueStorage(declaration, context, initializer)
}

function moduleValueType(
  declaration: ConstDeclaration | ReadonlyDeclaration | ImmutableBinding | LetDeclaration,
): ResolvedType | none {
  case declaration {
    value: ConstDeclaration -> { return value.resolvedType }
    value: ReadonlyDeclaration -> { return value.resolvedType }
    value: ImmutableBinding -> { return value.resolvedType }
    value: LetDeclaration -> { return value.resolvedType }
  }
  return none
}

function isCxxConstantInitializer(value: Expression): bool {
  case value {
    _: IntLiteral -> { return true }
    _: LongLiteral -> { return true }
    _: FloatLiteral -> { return true }
    _: DoubleLiteral -> { return true }
    _: CharLiteral -> { return true }
    _: BoolLiteral -> { return true }
    dot: DotShorthand -> { return dot.resolvedShorthandOwnerKind == "enum" }
    _ -> { return false }
  }
  return false
}

function moduleHasDeferredInitialization(program: Program): bool {
  for statement of program.statements {
    if statementHasDeferredInitialization(statement) { return true }
  }
  return false
}

function statementHasDeferredInitialization(statement: Statement): bool {
  case statement {
    value: ConstDeclaration -> { return !isCxxConstantInitializer(value.value) }
    value: ReadonlyDeclaration -> { return !isCxxConstantInitializer(value.value) }
    value: ImmutableBinding -> { return !isCxxConstantInitializer(value.value) }
    value: LetDeclaration -> { return !isCxxConstantInitializer(value.value) }
    class_: ClassDeclaration -> {
      if class_.native_ || class_.typeParams.length > 0 { return false }
      for field of class_.fields { if field.static_ && field.defaultValue != none { return true } }
      return false
    }
    export_: ExportDeclaration -> { return statementHasDeferredInitialization(export_.declaration) }
    _ -> { return false }
  }
  return false
}

function emitModuleInitializer(programs: Program[], context: EmitContext, includeValues: bool = true): string {
  let assignments = ""
  if includeValues {
    for program of programs {
      for statement of program.statements {
        assignments = assignments + emitModuleInitializerStatement(statement, context)
      }
    }
  }
  if assignments == "" { return "" }
  return "\nvoid __doof_initialize_module() {\n" + assignments + "}\n"
}

function emitModuleInitializerStatement(statement: Statement, context: EmitContext): string {
  case statement {
    value: ConstDeclaration -> { return emitModuleValueAssignment(value, value.value, context) }
    value: ReadonlyDeclaration -> { return emitModuleValueAssignment(value, value.value, context) }
    value: ImmutableBinding -> { return emitModuleValueAssignment(value, value.value, context) }
    value: LetDeclaration -> { return emitModuleValueAssignment(value, value.value, context) }
    class_: ClassDeclaration -> {
      let result = ""
      if class_.native_ || class_.typeParams.length > 0 { return result }
      for field of class_.fields {
        if !field.static_ || field.defaultValue == none { continue }
        for name of field.names {
          result = result + "        " + class_.name + "::" + cppIdentifier(name) + " = " +
            emitExpression(field.defaultValue!, context, field.resolvedType) + ";\n"
        }
      }
      return result
    }
    export_: ExportDeclaration -> { return emitModuleInitializerStatement(export_.declaration, context) }
    _ -> { return "" }
  }
  return ""
}

function emitModuleValueAssignment(
  declaration: ConstDeclaration | ReadonlyDeclaration | ImmutableBinding | LetDeclaration,
  value: Expression,
  context: EmitContext,
): string {
  if isCxxConstantInitializer(value) { return "" }
  name := scriptDeclarationName(declaration)
  if name == "" || name == "_" { return "" }
  return "        " + cppIdentifier(name) + " = " + emitExpression(value, context, moduleValueType(declaration)) + ";\n"
}

function emitGraphInitializationCall(namespaces: string[]): string {
  let result = ""
  for namespace of namespaces { result = result + "::" + namespace + "::__doof_initialize_module(); " }
  return result
}

function emitNativeClassMethods(programs: Program[], context: EmitContext): string {
  let result = ""
  for program of programs {
    for statement of program.statements {
      result = result + emitNativeClassMethodsForStatement(statement, context)
    }
  }
  return result
}

function emitNativeClassMethodsForStatement(statement: Statement, context: EmitContext): string {
  case statement {
    class_: ClassDeclaration -> {
      if !class_.native_ { return "" }
      let result = ""
      for method of class_.methods {
        if !method.bodyless { result = result + emitClassMethodDefinition(class_, method, context) }
      }
      return result
    }
    export_: ExportDeclaration -> { return emitNativeClassMethodsForStatement(export_.declaration, context) }
    _ -> { return "" }
  }
  return ""
}

// Translate an uncaught Doof panic into a stable process-boundary diagnostic.
function emitMainWrapper(moduleName: string, plan: HeaderPlan, hasScript: bool = false, initializationCall: string = ""): string {
  if !hasScript {
    signature := if plan.mainAcceptsArgs then "int main(int argc, char** argv)" else "int main()"
    argumentSetup := if plan.mainAcceptsArgs then "std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); " else ""
    call := if plan.mainAcceptsArgs then moduleName + "::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))" else moduleName + "::doof_main()"
    success := if plan.mainReturnsInt then "return " + call + ";" else call + "; return 0;"
    panicHandler := "catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }"
    actorSetup := "auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); "
    return "\n" + signature + " { try { " + actorSetup + initializationCall + argumentSetup + success + " } " + panicHandler + " catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"
  }
  needsArguments := plan.mainAcceptsArgs || hasScript
  signature := if needsArguments then "int main(int argc, char** argv)" else "int main()"
  argumentSetup := if needsArguments then "std::vector<std::string> raw_arguments; for (int i = 1; i < argc; ++i) raw_arguments.emplace_back(argv[i]); auto arguments = std::make_shared<std::vector<std::string>>(std::move(raw_arguments)); " else ""
  scriptCall := if hasScript then moduleName + "::__doof_run_script(arguments); " else ""
  call := if plan.mainAcceptsArgs then moduleName + "::doof_main(arguments)" else moduleName + "::doof_main()"
  success := if !plan.hasMain then scriptCall + "return 0;" else if plan.mainReturnsInt then scriptCall + "return " + call + ";" else scriptCall + call + "; return 0;"
  panicHandler := "catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }"
  actorSetup := "auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); "
  return "\n" + signature + " { try { " + actorSetup + initializationCall + argumentSetup + success + " } " + panicHandler + " catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"
}

// App targets provide their own platform main and enter Doof through this C ABI.
function emitAppEntryWrapper(moduleName: string, plan: HeaderPlan, hasScript: bool = false, initializationCall: string = ""): string {
  if !hasScript {
    argumentSetup := if plan.mainAcceptsArgs then "std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); " else "(void)argc; (void)argv; "
    call := if plan.mainAcceptsArgs then moduleName + "::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))" else moduleName + "::doof_main()"
    success := if plan.mainReturnsInt then "return " + call + ";" else call + "; return 0;"
    panicHandler := "catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }"
    actorSetup := "auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); "
    return "\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { " + actorSetup + initializationCall + argumentSetup + success + " } " + panicHandler + " catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"
  }
  needsArguments := plan.mainAcceptsArgs || hasScript
  argumentSetup := if needsArguments then "std::vector<std::string> raw_arguments; for (int i = 1; i < argc; ++i) raw_arguments.emplace_back(argv[i]); auto arguments = std::make_shared<std::vector<std::string>>(std::move(raw_arguments)); " else "(void)argc; (void)argv; "
  scriptCall := if hasScript then moduleName + "::__doof_run_script(arguments); " else ""
  call := if plan.mainAcceptsArgs then moduleName + "::doof_main(arguments)" else moduleName + "::doof_main()"
  success := if !plan.hasMain then scriptCall + "return 0;" else if plan.mainReturnsInt then scriptCall + "return " + call + ";" else scriptCall + call + "; return 0;"
  panicHandler := "catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }"
  actorSetup := "auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); "
  return "\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { " + actorSetup + initializationCall + argumentSetup + success + " } " + panicHandler + " catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"
}
