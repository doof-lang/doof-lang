// Initial C++ header planner and renderer for the Doof emitter.
//
// The planner is intentionally explicit: class declarations, function
// signatures, and future dependency decisions belong here, not in expression
// or statement emission.

import {
  ClassDeclaration, ConstDeclaration, EnumDeclaration, ExportDeclaration, Expression, FunctionDeclaration, InterfaceDeclaration,
  ImmutableBinding, Program, ReadonlyDeclaration, Statement, TypeAliasDeclaration,
} from "./ast"
import { EmitContext, EmitModuleSurface } from "./emitter-context"
import { emitClassDeclaration, emitDescriptionComment, emitFunctionDeclaration, emitFunctionDefinition, emitInterfaceAlias } from "./emitter-decl"
import { emitExpression } from "./emitter-expr"
import { emitInterfaceJsonDeclaration } from "./emitter-json"
import { emitContextType, emitType } from "./emitter-types"
import {
  ArrayResolvedType, ClassType, EnumType, FunctionType, InterfaceType,
  MapResolvedType, PrimitiveType, ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType,
  Symbol, TupleResolvedType, UnionResolvedType, WeakResolvedType,
} from "./semantic"
import { moduleNamespace, moduleNativeHeaderPath } from "./emitter-names"

export class HeaderPlan {
  functionSignatures: string[] = []
  nativeAdapterSignatures: string[] = []
  genericFunctionDefinitions: string[] = []
  earlyModuleValueDeclarations: string[] = []
  moduleValueDeclarations: string[] = []
  earlyClassDefinitions: string[] = []
  classDefinitions: string[] = []
  interfaceAliases: string[] = []
  enumDefinitions: string[] = []
  // Namespace-local structural aliases deduplicate long, reference-only
  // variant spellings. They are a C++ rendering detail, not Doof aliases.
  ephemeralTypeAliases: string[] = []
  preferredTypeAliasNames: string[] = []
  preferredTypeAliasSpellings: string[] = []
  earlyTypeAliases: string[] = []
  typeAliases: string[] = []
  classForwardDeclarations: string[] = []
  typeOnlyForwardDeclarations: string[] = []
  nativeIncludes: string[] = []
  nativeAliases: string[] = []
  nativeNamespaces: string[] = []
  let hasMain: bool = false
  let mainReturnsInt: bool = false
  let mainAcceptsArgs: bool = false
}

export class HeaderSection {
  namespaceName: string
  plan: HeaderPlan
}

export function planHeader(program: Program, context: EmitContext): HeaderPlan {
  return planHeaders([program], context)
}

export function planHeaders(programs: Program[], context: EmitContext): HeaderPlan {
  plan := HeaderPlan {}
  for program of programs {
    for statement of program.statements { collect(statement, plan, context) }
  }
  // Native headers are opaque to the Doof compiler. Give each selected native
  // namespace the nominal names visible in its defining module, while keeping
  // recursively required declarations in their original namespaces.
  for namespace of plan.nativeNamespaces {
    collectNativeModuleTypeAliases(context.modulePath, namespace, plan, context)
  }
  return plan
}

function collectNativeModuleTypeAliases(modulePath: string, namespace: string, plan: HeaderPlan, context: EmitContext): none {
  for surface of context.moduleSurfaces {
    if surface.path != modulePath { continue }
    for symbol of surface.exports {
      if isNativeAliasType(symbol) && !surfaceTypeIsGeneric(surface, symbol.name) {
        addNativeSymbolAlias(symbol, namespace, plan)
      }
    }
    for imported of surface.imports {
      if imported.symbol != none && isNativeAliasType(imported.symbol!) && !surfaceSymbolIsGeneric(context, imported.symbol!) {
        addNativeSymbolAlias(imported.symbol!, namespace, plan)
      }
    }
    return
  }
}

function surfaceTypeIsGeneric(surface: EmitModuleSurface, name: string): bool {
  for genericName of surface.genericTypes { if genericName == name { return true } }
  return false
}

function isNativeAliasType(symbol: Symbol): bool {
  return symbol.kind == "class" || symbol.kind == "struct" || symbol.kind == "enum" || symbol.kind == "interface" || symbol.kind == "type-alias"
}

function collect(statement: Statement, plan: HeaderPlan, context: EmitContext): none {
  case statement {
    class_: ClassDeclaration -> {
      if class_.native_ {
        rawInclude := if class_.nativeHeader == "" then class_.name + ".hpp" else class_.nativeHeader
        include := moduleNativeHeaderPath(context.modulePath, rawInclude)
        addUnique(plan.nativeIncludes, include)
        namespace := nativeNamespace(class_.nativeCppName)
        addUnique(plan.nativeNamespaces, namespace)
        collectNativeClassAliases(class_, namespace, plan, context)
      } else if class_.typeParams.length == 0 || isNativeTemplateClass(context, class_.name) {
        if class_.typeParams.length == 0 { plan.classForwardDeclarations.push("struct " + class_.name + ";\n") }
        definition := emitClassDeclaration(class_, context)
        if classCanEmitBeforeModuleIncludes(class_) { plan.earlyClassDefinitions.push(definition) }
        else { plan.classDefinitions.push(definition) }
      }
    }
    interface_: InterfaceDeclaration -> {
      if interface_.typeParams.length == 0 {
        plan.interfaceAliases.push(emitInterfaceAlias(interface_, context))
        declaration := emitInterfaceJsonDeclaration(interface_)
        if declaration != "" { plan.functionSignatures.push(declaration) }
      }
    }
    enum_: EnumDeclaration -> { plan.enumDefinitions.push(emitEnumDeclaration(enum_, context)) }
    // Generic aliases are erased after checker substitution. Concrete uses
    // lower directly to their substituted concrete type.
    alias: TypeAliasDeclaration -> {
      if alias.typeParams.length == 0 {
        emitted := emitTypeAlias(alias, context)
        if alias.resolvedType != none && !typeNeedsCompleteNominalDefinition(alias.resolvedType!) {
          plan.earlyTypeAliases.push(emitted)
          spelling := emitType(alias.resolvedType!, context.modulePath)
          if referenceOnlyVariant(spelling) {
            plan.preferredTypeAliasNames.push(alias.name)
            plan.preferredTypeAliasSpellings.push(spelling)
          }
        }
        else { plan.typeAliases.push(emitted) }
      }
    }
    const_: ConstDeclaration -> {
      collectModuleValueDeclaration(
        plan,
        emitDescriptionComment(const_.description, "") + emitModuleValueDeclaration(const_.name, const_.resolvedType!, context),
        const_.resolvedType!,
      )
    }
    readonly_: ReadonlyDeclaration -> {
      collectModuleValueDeclaration(
        plan,
        emitDescriptionComment(readonly_.description, "") + emitModuleValueDeclaration(readonly_.name, readonly_.resolvedType!, context),
        readonly_.resolvedType!,
      )
    }
    binding: ImmutableBinding -> {
      collectModuleValueDeclaration(plan, emitModuleValueDeclaration(binding.name, binding.resolvedType!, context), binding.resolvedType!)
    }
    fn: FunctionDeclaration -> {
      if fn.native_ {
        if fn.nativeHeader != "" { addUnique(plan.nativeIncludes, moduleNativeHeaderPath(context.modulePath, fn.nativeHeader)) }
        namespace := nativeNamespace(fn.nativeCppName)
        addUnique(plan.nativeNamespaces, namespace)
        if fn.resolvedType != none { collectNativeTypeAliases(fn.resolvedType!, namespace, plan, context) }
        return
      }
      if fn.name == "main" {
        plan.hasMain = true
        plan.mainReturnsInt = functionReturnsInt(fn)
        plan.mainAcceptsArgs = fn.params.length == 1
        plan.functionSignatures.push(emitFunctionDeclaration(fn, "doof_main", context.modulePath, context))
      } else if fn.typeParams.length > 0 {
        // Concrete definitions are added by the whole-program instantiation
        // plan; never expose a Doof generic as a C++ template.
      } else {
        plan.functionSignatures.push(emitFunctionDeclaration(fn, "", context.modulePath, context))
      }
    }
    export_: ExportDeclaration -> { collect(export_.declaration, plan, context) }
    _ -> { }
  }
}

// Primitive-only structs can be completed before generated module includes.
// This gives the opposite side of a header cycle the complete value types it
// needs while structs that store imported values still wait for their headers.
function classCanEmitBeforeModuleIncludes(class_: ClassDeclaration): bool {
  if class_.typeParams.length > 0 { return false }
  for field of class_.fields {
    if !field.static_ && field.resolvedType != none && typeNeedsCompleteNominalDefinition(field.resolvedType!) { return false }
  }
  return true
}

function typeNeedsCompleteNominalDefinition(type_: ResolvedType): bool {
  case type_ {
    class_: ClassType -> {
      if class_.symbol.kind == "struct" || class_.symbol.native_ { return true }
      for argument of class_.typeArgs { if typeNeedsCompleteNominalDefinition(argument) { return true } }
      return false
    }
    enum_: EnumType -> { return true }
    interface_: InterfaceType -> {
      for argument of interface_.typeArgs { if typeNeedsCompleteNominalDefinition(argument) { return true } }
      return false
    }
    array: ArrayResolvedType -> { return typeNeedsCompleteNominalDefinition(array.elementType) }
    map: MapResolvedType -> {
      return typeNeedsCompleteNominalDefinition(map.keyType) || typeNeedsCompleteNominalDefinition(map.valueType)
    }
    set_: SetResolvedType -> { return typeNeedsCompleteNominalDefinition(set_.elementType) }
    stream: StreamResolvedType -> { return typeNeedsCompleteNominalDefinition(stream.elementType) }
    result: ResultResolvedType -> {
      return typeNeedsCompleteNominalDefinition(result.valueType) || typeNeedsCompleteNominalDefinition(result.errorType)
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements { if typeNeedsCompleteNominalDefinition(element) { return true } }
      return false
    }
    union_: UnionResolvedType -> {
      for member of union_.types { if typeNeedsCompleteNominalDefinition(member) { return true } }
      return false
    }
    function_: FunctionType -> {
      for parameter of function_.params { if typeNeedsCompleteNominalDefinition(parameter.type_) { return true } }
      return typeNeedsCompleteNominalDefinition(function_.returnType)
    }
    weak_: WeakResolvedType -> { return typeNeedsCompleteNominalDefinition(weak_.inner) }
    _ -> { return false }
  }
}

function isNativeTemplateClass(context: EmitContext, name: string): bool {
  key := context.modulePath + "::" + name
  for existing of context.nativeTemplateClassKeys { if existing == key { return true } }
  return false
}

function collectNativeClassAliases(class_: ClassDeclaration, namespace: string, plan: HeaderPlan, context: EmitContext): none {
  for field of class_.fields { if field.resolvedType != none { collectNativeTypeAliases(field.resolvedType!, namespace, plan, context) } }
  for method of class_.methods { if method.resolvedType != none { collectNativeTypeAliases(method.resolvedType!, namespace, plan, context) } }
}

function collectNativeTypeAliases(type_: ResolvedType, namespace: string, plan: HeaderPlan, context: EmitContext): none {
  case type_ {
    class_: ClassType -> {
      if !surfaceSymbolIsGeneric(context, class_.symbol) { addNativeSymbolAlias(class_.symbol, namespace, plan) }
      for argument of class_.typeArgs { collectNativeTypeAliases(argument, namespace, plan, context) }
    }
    enum_: EnumType -> { addNativeSymbolAlias(enum_.symbol, namespace, plan) }
    interface_: InterfaceType -> { if !surfaceSymbolIsGeneric(context, interface_.symbol) { addNativeSymbolAlias(interface_.symbol, namespace, plan) } }
    array: ArrayResolvedType -> { collectNativeTypeAliases(array.elementType, namespace, plan, context) }
    map: MapResolvedType -> {
      collectNativeTypeAliases(map.keyType, namespace, plan, context)
      collectNativeTypeAliases(map.valueType, namespace, plan, context)
    }
    set_: SetResolvedType -> { collectNativeTypeAliases(set_.elementType, namespace, plan, context) }
    stream: StreamResolvedType -> { collectNativeTypeAliases(stream.elementType, namespace, plan, context) }
    result: ResultResolvedType -> {
      collectNativeTypeAliases(result.valueType, namespace, plan, context)
      collectNativeTypeAliases(result.errorType, namespace, plan, context)
    }
    tuple: TupleResolvedType -> { for element of tuple.elements { collectNativeTypeAliases(element, namespace, plan, context) } }
    union_: UnionResolvedType -> { for member of union_.types { collectNativeTypeAliases(member, namespace, plan, context) } }
    weak_: WeakResolvedType -> { collectNativeTypeAliases(weak_.inner, namespace, plan, context) }
    function_: FunctionType -> {
      for parameter of function_.params { collectNativeTypeAliases(parameter.type_, namespace, plan, context) }
      collectNativeTypeAliases(function_.returnType, namespace, plan, context)
    }
    _ -> { }
  }
}

function surfaceSymbolIsGeneric(context: EmitContext, symbol: Symbol): bool {
  for surface of context.moduleSurfaces {
    if surface.path == symbol.module { return surfaceTypeIsGeneric(surface, symbol.name) }
  }
  return false
}

function addNativeSymbolAlias(symbol: Symbol, namespace: string, plan: HeaderPlan): none {
  if symbol.native_ || symbol.module == "" { return }
  if symbol.kind == "class" || symbol.kind == "struct" || symbol.kind == "interface" {
    addUnique(plan.typeOnlyForwardDeclarations, "namespace " + moduleNamespace(symbol.module) + " { struct " + symbol.name + "; }\n")
  } else if symbol.kind == "enum" {
    addUnique(plan.typeOnlyForwardDeclarations, "namespace " + moduleNamespace(symbol.module) + " { enum class " + symbol.name + "; }\n")
  }
  alias := "using " + symbol.name + " = ::" + moduleNamespace(symbol.module) + "::" + symbol.name + ";"
  addUnique(plan.nativeAliases, if namespace == "" then alias + "\n" else "namespace " + namespace + " { " + alias + " }\n")
}

export function renderHeader(plan: HeaderPlan, guardName: string): string {
  return renderProjectedHeader([HeaderSection { namespaceName: guardName, plan }])
}

export function renderProjectedHeader(sections: HeaderSection[]): string {
  compression := HeaderCompressionState {}
  for section of sections { compressRepeatedHeaderVariants(section.plan, compression) }
  let result = "#pragma once\n"
  // The runtime owns the generated C++ standard-library baseline. Keep it as
  // the first header so GCC can consume its adjacent .gch without reparsing
  // those headers in every generated translation unit.
  result = result + "#include \"doof_runtime.hpp\"\n"
  let emittedForward = false
  for section of sections {
    for declaration of section.plan.typeOnlyForwardDeclarations { result = result + declaration; emittedForward = true }
  }
  if emittedForward { result = result + "\n" }
  // Establish every generated namespace and nominal forward declaration
  // before any worldview definition is completed.
  for section of sections {
    if section.plan.classForwardDeclarations.length == 0 &&
      section.plan.earlyModuleValueDeclarations.length == 0 &&
      headerPlanEmitsNamespaceContent(section.plan) { continue }
    result = result + "namespace " + section.namespaceName + " {\n"
    for declaration of section.plan.classForwardDeclarations { result = result + "    " + declaration }
    // Module bindings are source-private at the Doof level. They may still be
    // declared in generated C++ so inline class field defaults can name them.
    for declaration of section.plan.earlyModuleValueDeclarations { result = result + "    " + declaration }
    result = result + "}\n\n"
  }
  // Reference-only variants need nominal declarations but not complete class
  // definitions. Hoist their short structural names once per namespace.
  for section of sections {
    if section.plan.ephemeralTypeAliases.length > 0 {
      result = result + "namespace " + section.namespaceName + " {\n"
      for alias of section.plan.ephemeralTypeAliases { result = result + "    " + alias }
      result = result + "}\n\n"
    }
  }
  // Enums are complete value types and can be referenced by any later class
  // signature. Emit the whole selected enum layer before class definitions,
  // regardless of analyzer discovery order.
  for section of sections {
    if section.plan.enumDefinitions.length > 0 {
      result = result + "namespace " + section.namespaceName + " {\n"
      for definition of section.plan.enumDefinitions { result = result + "    " + definition }
      result = result + "}\n\n"
    }
  }
  for section of sections {
    if section.plan.interfaceAliases.length > 0 {
      result = result + "namespace " + section.namespaceName + " {\n"
      for alias of section.plan.interfaceAliases { result = result + "    " + alias }
      result = result + "}\n\n"
    }
  }
  for section of sections {
    if section.plan.earlyTypeAliases.length > 0 {
      result = result + "namespace " + section.namespaceName + " {\n"
      for alias of section.plan.earlyTypeAliases { result = result + "    " + alias }
      result = result + "}\n\n"
    }
  }
  for section of sections {
    if section.plan.earlyClassDefinitions.length > 0 {
      result = result + "namespace " + section.namespaceName + " {\n"
      for definition of section.plan.earlyClassDefinitions { result = result + "    " + definition }
      result = result + "}\n\n"
    }
  }
  // Materialize each dependency section in planner order. A native header is
  // part of its defining section: its aliases/includes precede declarations
  // that use its native types, while earlier dependency sections have already
  // supplied any complete Doof types the native header requires.
  for section of sections {
    let emittedNative = false
    for alias of section.plan.nativeAliases { result = result + alias; emittedNative = true }
    for include of section.plan.nativeIncludes {
      if include.startsWith("<") { result = result + "#include " + include + "\n" }
      else { result = result + "#include \"" + include + "\"\n" }
      emittedNative = true
    }
    if emittedNative { result = result + "\n" }
    result = renderFinalSection(result, section)
  }
  for section of sections {
    if section.plan.genericFunctionDefinitions.length == 0 { continue }
    result = result + "namespace " + section.namespaceName + " {\n"
    for definition of section.plan.genericFunctionDefinitions { result = result + definition }
    result = result + "}\n"
  }
  while result.endsWith("\n\n") { result = result.substring(0, result.length - 1) }
  return result
}

function renderFinalSection(result_: string, section: HeaderSection): string {
  let result = result_
  plan := section.plan
  if plan.nativeAdapterSignatures.length == 0 &&
    plan.moduleValueDeclarations.length == 0 &&
    plan.classDefinitions.length == 0 &&
    plan.typeAliases.length == 0 &&
    plan.functionSignatures.length == 0 { return result }
  result = result + "namespace " + section.namespaceName + " {\n"
  // Concrete class methods may call module-owned native adapters.
  for signature of plan.nativeAdapterSignatures { result = result + "    " + signature }
  for declaration of plan.moduleValueDeclarations { result = result + "    " + declaration }
  for definition of plan.classDefinitions { result = result + "    " + definition }
  for alias of plan.typeAliases { result = result + "    " + alias }
  for signature of plan.functionSignatures { result = result + "    " + signature }
  return result + "}\n\n"
}

function headerPlanEmitsNamespaceContent(plan: HeaderPlan): bool {
  return plan.ephemeralTypeAliases.length > 0 ||
    plan.enumDefinitions.length > 0 ||
    plan.interfaceAliases.length > 0 ||
    plan.earlyClassDefinitions.length > 0 ||
    plan.earlyTypeAliases.length > 0 ||
    plan.nativeAdapterSignatures.length > 0 ||
    plan.moduleValueDeclarations.length > 0 ||
    plan.classDefinitions.length > 0 ||
    plan.typeAliases.length > 0 ||
    plan.functionSignatures.length > 0 ||
    plan.genericFunctionDefinitions.length > 0
}

class HeaderTypeUse {
  spelling: string
  let count: int = 0
}

class HeaderCompressionState {
  let nextAnonymousTypeIndex: int = 1
}

// Consumer-projected headers can repeat erased union spellings many times.
// Deduplicate only variants whose alternatives are monostate/shared_ptr: they
// are valid after forward declarations, so introducing the alias cannot move a
// value type across its required completeness boundary.
function compressRepeatedHeaderVariants(plan: HeaderPlan, state: HeaderCompressionState): none {
  let uses: HeaderTypeUse[] = []
  collectHeaderTypeUses(plan.functionSignatures, uses)
  collectHeaderTypeUses(plan.nativeAdapterSignatures, uses)
  collectHeaderTypeUses(plan.genericFunctionDefinitions, uses)
  collectHeaderTypeUses(plan.earlyModuleValueDeclarations, uses)
  collectHeaderTypeUses(plan.moduleValueDeclarations, uses)
  collectHeaderTypeUses(plan.earlyClassDefinitions, uses)
  collectHeaderTypeUses(plan.classDefinitions, uses)
  collectHeaderTypeUses(plan.interfaceAliases, uses)
  collectHeaderTypeUses(plan.enumDefinitions, uses)
  collectHeaderTypeUses(plan.earlyTypeAliases, uses)
  collectHeaderTypeUses(plan.typeAliases, uses)

  for use of uses {
    if use.count < 2 { continue }
    let name = preferredHeaderTypeAlias(plan, use.spelling)
    if name == "" {
      name = "__type" + string(state.nextAnonymousTypeIndex)
      state.nextAnonymousTypeIndex += 1
      plan.ephemeralTypeAliases.push("using " + name + " = " + use.spelling + ";\n")
    }
    replaceHeaderTypeUses(plan.functionSignatures, use.spelling, name)
    replaceHeaderTypeUses(plan.nativeAdapterSignatures, use.spelling, name)
    replaceHeaderTypeUses(plan.genericFunctionDefinitions, use.spelling, name)
    replaceHeaderTypeUses(plan.earlyModuleValueDeclarations, use.spelling, name)
    replaceHeaderTypeUses(plan.moduleValueDeclarations, use.spelling, name)
    replaceHeaderTypeUses(plan.earlyClassDefinitions, use.spelling, name)
    replaceHeaderTypeUses(plan.classDefinitions, use.spelling, name)
    replaceHeaderTypeUses(plan.interfaceAliases, use.spelling, name)
    replaceHeaderTypeUses(plan.enumDefinitions, use.spelling, name)
    // Keep named alias declarations canonical: replacing their own RHS would
    // produce `using Expression = Expression`.
    if preferredHeaderTypeAlias(plan, use.spelling) == "" {
      replaceHeaderTypeUses(plan.earlyTypeAliases, use.spelling, name)
      replaceHeaderTypeUses(plan.typeAliases, use.spelling, name)
    }
  }
}

function preferredHeaderTypeAlias(plan: HeaderPlan, spelling: string): string {
  for index of 0..<plan.preferredTypeAliasSpellings.length {
    if plan.preferredTypeAliasSpellings[index] == spelling { return plan.preferredTypeAliasNames[index] }
  }
  return ""
}

function collectHeaderTypeUses(values: string[], uses: HeaderTypeUse[]): none {
  for value of values {
    let offset = 0
    prefix := "std::variant<"
    while offset < value.length {
      relative := value.substring(offset, value.length).indexOf(prefix)
      if relative < 0 { break }
      start := offset + relative
      end := matchingAngleEnd(value, start + prefix.length - 1)
      if end < 0 { break }
      spelling := value.substring(start, end + 1)
      if referenceOnlyVariant(spelling) { addHeaderTypeUse(uses, spelling) }
      offset = end + 1
    }
  }
}

function matchingAngleEnd(value: string, opening: int): int {
  let depth = 0
  for index of opening..<value.length {
    if value[index] == '<' { depth += 1 }
    else if value[index] == '>' {
      depth -= 1
      if depth == 0 { return index }
    }
  }
  return -1
}

function referenceOnlyVariant(spelling: string): bool {
  inner := spelling.substring(13, spelling.length - 1)
  let memberStart = 0
  let depth = 0
  for index of 0..inner.length {
    atEnd := index == inner.length
    if !atEnd {
      if inner[index] == '<' { depth += 1 }
      else if inner[index] == '>' { depth -= 1 }
    }
    if atEnd || (inner[index] == ',' && depth == 0) {
      member := inner.substring(memberStart, index).trim()
      if member != "std::monostate" && !(member.startsWith("std::shared_ptr<") && member.endsWith(">")) { return false }
      memberStart = index + 1
    }
  }
  return true
}

function addHeaderTypeUse(uses: HeaderTypeUse[], spelling: string): none {
  for use of uses {
    if use.spelling == spelling { use.count += 1; return }
  }
  uses.push(HeaderTypeUse { spelling, count: 1 })
}

function replaceHeaderTypeUses(values: string[], spelling: string, name: string): none {
  for index of 0..<values.length { values[index] = values[index].replaceAll(spelling, name) }
}

function collectModuleValueDeclaration(plan: HeaderPlan, declaration: string, type_: ResolvedType): none {
  if moduleValueDeclarationNeedsIncludes(type_) { plan.moduleValueDeclarations.push(declaration) }
  else { plan.earlyModuleValueDeclarations.push(declaration) }
}

// Values whose C++ spelling requires an enum/interface definition or a
// complete by-value nominal type wait until generated/native includes and
// aliases are available. Ordinary Doof classes lower through shared_ptr and
// can use the existing forward declaration.
function moduleValueDeclarationNeedsIncludes(type_: ResolvedType): bool {
  case type_ {
    class_: ClassType -> {
      if class_.symbol.kind == "struct" || class_.symbol.native_ { return true }
      for argument of class_.typeArgs { if moduleValueDeclarationNeedsIncludes(argument) { return true } }
      return false
    }
    _: EnumType -> { return true }
    _: InterfaceType -> { return true }
    array: ArrayResolvedType -> { return moduleValueDeclarationNeedsIncludes(array.elementType) }
    map: MapResolvedType -> {
      return moduleValueDeclarationNeedsIncludes(map.keyType) || moduleValueDeclarationNeedsIncludes(map.valueType)
    }
    set_: SetResolvedType -> { return moduleValueDeclarationNeedsIncludes(set_.elementType) }
    stream: StreamResolvedType -> { return moduleValueDeclarationNeedsIncludes(stream.elementType) }
    result: ResultResolvedType -> {
      return moduleValueDeclarationNeedsIncludes(result.valueType) || moduleValueDeclarationNeedsIncludes(result.errorType)
    }
    tuple: TupleResolvedType -> {
      for element of tuple.elements { if moduleValueDeclarationNeedsIncludes(element) { return true } }
      return false
    }
    union_: UnionResolvedType -> {
      for member of union_.types { if moduleValueDeclarationNeedsIncludes(member) { return true } }
      return false
    }
    weak_: WeakResolvedType -> { return moduleValueDeclarationNeedsIncludes(weak_.inner) }
    function_: FunctionType -> {
      for parameter of function_.params { if moduleValueDeclarationNeedsIncludes(parameter.type_) { return true } }
      return moduleValueDeclarationNeedsIncludes(function_.returnType)
    }
    _ -> { return false }
  }
  return false
}

function emitModuleValueDeclaration(name: string, type_: ResolvedType, context: EmitContext): string {
  return "extern " + emitContextType(type_, context) + " " + name + ";\n"
}

function addUnique(values: string[], value: string): none {
  for existing of values { if existing == value { return } }
  values.push(value)
}

function nativeNamespace(cppName: string): string {
  let separator = -1
  for i of 0..<cppName.length {
    if i + 1 < cppName.length && cppName.substring(i, i + 2) == "::" {
      separator = i
    }
  }
  if separator < 0 { return "" }
  return cppName.substring(0, separator)
}

function emitEnumDeclaration(declaration: EnumDeclaration, context: EmitContext): string {
  let result = emitDescriptionComment(declaration.description, "") + "enum class " + declaration.name + " {\n"
  for i of 0..<declaration.variants.length {
    variant := declaration.variants[i]
    result = result + emitDescriptionComment(variant.description, "    ") + "    " + variant.name
    if variant.value != none { result = result + " = " + emitExpression(variant.value!, context) }
    if i + 1 < declaration.variants.length { result = result + "," }
    result = result + "\n"
  }
  result = result + "};\n"
  result = result + "inline const char* " + declaration.name + "_name(" + declaration.name + " value) {\n"
  result = result + "  switch (value) {\n"
  for variant of declaration.variants {
    result = result + "    case " + declaration.name + "::" + variant.name + ": return \"" + variant.name + "\";\n"
  }
  result = result + "  }\n  return \"\";\n}\n"
  result = result + "inline std::optional<" + declaration.name + "> " + declaration.name + "_fromName(std::string_view value) {\n"
  for variant of declaration.variants {
    result = result + "  if (value == \"" + variant.name + "\") return " + declaration.name + "::" + variant.name + ";\n"
  }
  result = result + "  return std::nullopt;\n}\n"
  result = result + "inline std::optional<" + declaration.name + "> " + declaration.name + "_fromValue(int32_t value) {\n"
  result = result + "  switch (static_cast<" + declaration.name + ">(value)) {\n"
  for variant of declaration.variants {
    result = result + "    case " + declaration.name + "::" + variant.name + ": return " + declaration.name + "::" + variant.name + ";\n"
  }
  result = result + "    default: return std::nullopt;\n  }\n}\n"
  return result + "inline std::ostream& operator<<(std::ostream& output, " + declaration.name + " value) { return output << " + declaration.name + "_name(value); }\n"
}

function emitTypeAlias(alias: TypeAliasDeclaration, context: EmitContext): string {
  if alias.resolvedType == none { panic("Type alias " + alias.name + " was not checked before emission") }
  return emitDescriptionComment(alias.description, "") + "using " + alias.name + " = " + emitType(alias.resolvedType!, context.modulePath) + ";\n"
}

function functionReturnsInt(fn: FunctionDeclaration): bool {
  case fn.resolvedType! {
    function_: FunctionType -> {
      case function_.returnType {
        primitive: PrimitiveType -> { return primitive.name == "int" }
        _ -> { return false }
      }
    }
    _ -> { return false }
  }
  return false
}
