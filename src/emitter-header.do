// Initial C++ header planner and renderer for the Doof emitter.
//
// The planner is intentionally explicit: class declarations, function
// signatures, and future dependency decisions belong here, not in expression
// or statement emission.

import {
  ClassDeclaration, ConstDeclaration, EnumDeclaration, ExportDeclaration, Expression, FunctionDeclaration, InterfaceDeclaration,
  ImmutableBinding, LetDeclaration, Program, ReadonlyDeclaration, Statement, TypeAliasDeclaration,
} from "./ast"
import { EmitContext, EmitModuleSurface } from "./emitter-context"
import { emitClassDeclaration, emitDescriptionComment, emitFunctionDeclaration, emitInterfaceAlias } from "./emitter-decl"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { quote } from "./emitter-expr-literals"
import { emitInterfaceJsonDeclaration } from "./emitter-json"
import { emitContextType, emitType } from "./emitter-types"
import {
  ActorType, ArrayResolvedType, ClassType, EnumType, FunctionType, InterfaceType,
  MapResolvedType, PrimitiveType, ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType,
  PromiseType, Symbol, TupleResolvedType, UnionResolvedType, WeakResolvedType,
} from "./semantic"
import { moduleNamespace, moduleNativeHeaderPath } from "./emitter-names"
import { StringBuilder } from "./string-builder"
import { ClassInstantiation, classInstantiationKey, MethodInstantiation } from "./emitter-monomorphize"

export class HeaderPlan {
  functionSignatures: string[] = []
  nativeAdapterSignatures: string[] = []
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
  reservedNamespaceNames: string[] = []
  let hasMain: bool = false
  let mainReturnsInt: bool = false
  let mainAcceptsArgs: bool = false
}

export class HeaderSection {
  namespaceName: string
  plan: HeaderPlan
}

export function planHeader(program: Program, context: EmitContext, methods: MethodInstantiation[] = [], classes: ClassInstantiation[] = []): HeaderPlan {
  plan := HeaderPlan {}
  for statement of program.statements { collect(statement, plan, context, methods, classes) }
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

function collect(statement: Statement, plan: HeaderPlan, context: EmitContext, methods: MethodInstantiation[], classes: ClassInstantiation[]): none {
  case statement {
    class_: ClassDeclaration -> {
      reserveHeaderNamespaceName(plan, class_.name)
      if class_.native_ {
        rawInclude := if class_.nativeHeader == "" then class_.name + ".hpp" else class_.nativeHeader
        include := moduleNativeHeaderPath(context.modulePath, rawInclude)
        addUnique(plan.nativeIncludes, include)
        namespace := nativeNamespace(class_.nativeCppName)
        addUnique(plan.nativeNamespaces, namespace)
        collectNativeClassAliases(class_, namespace, plan, context)
      } else if class_.typeParams.length == 0 {
        plan.classForwardDeclarations.push("struct " + class_.name + ";\n")
        let concreteMethods: MethodInstantiation[] = []
        ownerKey := classInstantiationKey(context.modulePath, class_.name, [])
        for method of methods { if method.ownerKey == ownerKey { concreteMethods.push(method) } }
        definition := emitClassDeclaration(class_, context, "", concreteMethods)
        if classCanEmitBeforeModuleIncludes(class_) { plan.earlyClassDefinitions.push(definition) }
        else { plan.classDefinitions.push(definition) }
      }
    }
    interface_: InterfaceDeclaration -> {
      reserveHeaderNamespaceName(plan, interface_.name)
      if interface_.typeParams.length == 0 {
        if interface_.resolvedSymbol != none {
          for implementation of interface_.resolvedSymbol!.implementations {
            if implementation.native_ { addNativeClassForwardDeclaration(implementation, plan) }
          }
        }
        plan.interfaceAliases.push(emitInterfaceAlias(interface_, context, classes))
        declaration := emitInterfaceJsonDeclaration(interface_)
        if declaration != "" { plan.functionSignatures.push(declaration) }
      }
    }
    enum_: EnumDeclaration -> { reserveHeaderNamespaceName(plan, enum_.name); plan.enumDefinitions.push(emitEnumDeclaration(enum_, context)) }
    // Generic aliases are erased after checker substitution. Concrete uses
    // lower directly to their substituted concrete type.
    alias: TypeAliasDeclaration -> {
      reserveHeaderNamespaceName(plan, alias.name)
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
      reserveHeaderNamespaceName(plan, const_.name)
      collectModuleValueDeclaration(
        plan,
        emitDescriptionComment(const_.description, "") + emitModuleValueDeclaration(const_.name, const_.resolvedType!, context),
        const_.resolvedType!,
      )
    }
    readonly_: ReadonlyDeclaration -> {
      reserveHeaderNamespaceName(plan, readonly_.name)
      collectModuleValueDeclaration(
        plan,
        emitDescriptionComment(readonly_.description, "") + emitModuleValueDeclaration(readonly_.name, readonly_.resolvedType!, context),
        readonly_.resolvedType!,
      )
    }
    binding: ImmutableBinding -> {
      reserveHeaderNamespaceName(plan, binding.name)
      collectModuleValueDeclaration(plan, emitModuleValueDeclaration(binding.name, binding.resolvedType!, context), binding.resolvedType!)
    }
    let_: LetDeclaration -> {
      reserveHeaderNamespaceName(plan, let_.name)
      collectModuleValueDeclaration(plan, emitModuleValueDeclaration(let_.name, let_.resolvedType!, context), let_.resolvedType!)
    }
    fn: FunctionDeclaration -> {
      reserveHeaderNamespaceName(plan, if fn.name == "main" then "doof_main" else fn.name)
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
    export_: ExportDeclaration -> { collect(export_.declaration, plan, context, methods, classes) }
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
    actor: ActorType -> { collectNativeTypeAliases(actor.innerClass, namespace, plan, context) }
    promise: PromiseType -> { collectNativeTypeAliases(promise.valueType, namespace, plan, context) }
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
  if symbol.kind == "class" || symbol.kind == "struct" {
    addUnique(plan.typeOnlyForwardDeclarations, "namespace " + moduleNamespace(symbol.module) + " { struct " + symbol.name + "; }\n")
  } else if symbol.kind == "enum" {
    addUnique(plan.typeOnlyForwardDeclarations, "namespace " + moduleNamespace(symbol.module) + " { enum class " + symbol.name + "; }\n")
  }
  alias := "using " + symbol.name + " = ::" + moduleNamespace(symbol.module) + "::" + symbol.name + ";"
  addUnique(plan.nativeAliases, if namespace == "" then alias + "\n" else "namespace " + namespace + " { " + alias + " }\n")
}

export function renderProjectedHeader(sections: HeaderSection[]): string {
  compression := HeaderCompressionState {}
  for section of sections { compressRepeatedHeaderVariants(section.plan, compression) }
  result := StringBuilder()
  result.append("#pragma once\n")
  // The runtime owns the generated C++ standard-library baseline. Keep it as
  // the first header so GCC can consume its adjacent .gch without reparsing
  // those headers in every generated translation unit.
  result.append("#include \"doof_runtime.hpp\"\n")
  let emittedForward = false
  for section of sections {
    for declaration of section.plan.typeOnlyForwardDeclarations { result.append(declaration); emittedForward = true }
  }
  if emittedForward { result.append("\n") }
  // Establish every generated namespace and nominal forward declaration
  // before any worldview definition is completed.
  for section of sections {
    if section.plan.classForwardDeclarations.length == 0 &&
      section.plan.earlyModuleValueDeclarations.length == 0 &&
      headerPlanEmitsNamespaceContent(section.plan) { continue }
    result.append("namespace " + section.namespaceName + " {\n")
    for declaration of section.plan.classForwardDeclarations { result.append("    " + declaration) }
    // Module bindings are source-private at the Doof level. They may still be
    // declared in generated C++ because projected declarations can name their
    // types and generated definitions can reference their storage.
    for declaration of section.plan.earlyModuleValueDeclarations { result.append("    " + declaration) }
    result.append("}\n\n")
  }
  // Reference-only variants need nominal declarations but not complete class
  // definitions. Hoist their short structural names once per namespace.
  for section of sections {
    if section.plan.ephemeralTypeAliases.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for alias of section.plan.ephemeralTypeAliases { result.append("    " + alias) }
      result.append("}\n\n")
    }
  }
  // Enums are complete value types and can be referenced by any later class
  // signature. Emit the whole selected enum layer before class definitions,
  // regardless of analyzer discovery order.
  for section of sections {
    if section.plan.enumDefinitions.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for definition of section.plan.enumDefinitions { result.append("    " + definition) }
      result.append("}\n\n")
    }
  }
  for section of sections {
    if section.plan.interfaceAliases.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for alias of section.plan.interfaceAliases { result.append("    " + alias) }
      result.append("}\n\n")
    }
  }
  for section of sections {
    if section.plan.earlyTypeAliases.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for alias of section.plan.earlyTypeAliases { result.append("    " + alias) }
      result.append("}\n\n")
    }
  }
  for section of sections {
    if section.plan.earlyClassDefinitions.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for definition of section.plan.earlyClassDefinitions { result.append("    " + definition) }
      result.append("}\n\n")
    }
  }
  // Materialize each dependency section in planner order. A native header is
  // part of its defining section: its aliases/includes precede declarations
  // that use its native types, while earlier dependency sections have already
  // supplied any complete Doof types the native header requires.
  for section of sections {
    let emittedNative = false
    for alias of section.plan.nativeAliases { result.append(alias); emittedNative = true }
    for include of section.plan.nativeIncludes {
      if include.startsWith("<") { result.append("#include " + include + "\n") }
      else { result.append("#include \"" + include + "\"\n") }
      emittedNative = true
    }
    if emittedNative { result.append("\n") }
    renderFinalSection(result, section)
  }
  let rendered = result.drainToString()
  while rendered.endsWith("\n\n") { rendered = rendered.substring(0, rendered.length - 1) }
  return rendered
}

function renderFinalSection(result: StringBuilder, section: HeaderSection): none {
  plan := section.plan
  if plan.nativeAdapterSignatures.length == 0 &&
    plan.moduleValueDeclarations.length == 0 &&
    plan.classDefinitions.length == 0 &&
    plan.typeAliases.length == 0 &&
    plan.functionSignatures.length == 0 { return }
  result.append("namespace " + section.namespaceName + " {\n")
  // Concrete class methods may call module-owned native adapters.
  for signature of plan.nativeAdapterSignatures { result.append("    " + signature) }
  for declaration of plan.moduleValueDeclarations { result.append("    " + declaration) }
  for definition of plan.classDefinitions { result.append("    " + definition) }
  for alias of plan.typeAliases { result.append("    " + alias) }
  for signature of plan.functionSignatures { result.append("    " + signature) }
  result.append("}\n\n")
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
    plan.functionSignatures.length > 0
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
      name = nextHeaderTypeAliasName(plan, state)
      plan.ephemeralTypeAliases.push("using " + name + " = " + use.spelling + ";\n")
    }
    replaceHeaderTypeUses(plan.functionSignatures, use.spelling, name)
    replaceHeaderTypeUses(plan.nativeAdapterSignatures, use.spelling, name)
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

function nextHeaderTypeAliasName(plan: HeaderPlan, state: HeaderCompressionState): string {
  while true {
    candidate := "doof_header_type_" + string(state.nextAnonymousTypeIndex)
    state.nextAnonymousTypeIndex += 1
    let occupied = false
    for existing of plan.reservedNamespaceNames { if existing == candidate { occupied = true; break } }
    if !occupied {
      plan.reservedNamespaceNames.push(candidate)
      return candidate
    }
  }
  return ""
}

export function reserveHeaderNamespaceName(plan: HeaderPlan, name: string): none {
  emitted := cppIdentifier(name)
  for existing of plan.reservedNamespaceNames { if existing == emitted { return } }
  plan.reservedNamespaceNames.push(emitted)
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

// Structural interface aliases are emitted before selected native headers so
// those headers can consume generated Doof aliases. A native implementation
// arm therefore needs its own nominal declaration at the earlier alias layer.
function addNativeClassForwardDeclaration(symbol: Symbol, plan: HeaderPlan): none {
  cppName := if symbol.nativeCppName == "" then symbol.name else symbol.nativeCppName
  namespace := nativeNamespace(cppName)
  name := if namespace == "" then cppName else cppName.substring(namespace.length + 2, cppName.length)
  declaration := if namespace == "" then "class " + name + ";\n" else "namespace " + namespace + " { class " + name + "; }\n"
  addUnique(plan.typeOnlyForwardDeclarations, declaration)
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
    if declaration.backingKind == "string" { result = result + " = " + string(i) }
    else if variant.resolvedIntValue != none { result = result + " = " + string(variant.resolvedIntValue!) }
    if i + 1 < declaration.variants.length { result = result + "," }
    result = result + "\n"
  }
  result = result + "};\n"
  result = result + "inline const char* " + declaration.name + "_name(" + declaration.name + " value) {\n"
  result = result + "  switch (value) {\n"
  for variant of declaration.variants {
    result = result + "    case " + declaration.name + "::" + variant.name + ": return \"" + variant.name + "\";\n"
  }
  result = result + "  }\n  doof::panic(std::string(\"Invalid " + declaration.name + " enum value: \") + doof::to_string(static_cast<int32_t>(value)));\n}\n"
  result = result + "inline std::optional<" + declaration.name + "> " + declaration.name + "_fromName(std::string_view value) {\n"
  for variant of declaration.variants {
    result = result + "  if (value == \"" + variant.name + "\") return " + declaration.name + "::" + variant.name + ";\n"
  }
  result = result + "  return std::nullopt;\n}\n"
  if declaration.backingKind == "string" {
    result = result + "inline std::string " + declaration.name + "_value(" + declaration.name + " value) {\n  switch (value) {\n"
    for variant of declaration.variants { result = result + "    case " + declaration.name + "::" + variant.name + ": return " + quote(variant.resolvedStringValue ?? "") + ";\n" }
    result = result + "  }\n  doof::panic(std::string(\"Invalid " + declaration.name + " enum value: \") + doof::to_string(static_cast<int32_t>(value)));\n}\n"
    result = result + "inline std::optional<" + declaration.name + "> " + declaration.name + "_fromValue(std::string_view value) {\n"
    for variant of declaration.variants { result = result + "  if (value == " + quote(variant.resolvedStringValue ?? "") + ") return " + declaration.name + "::" + variant.name + ";\n" }
    result = result + "  return std::nullopt;\n}\n"
  } else {
    result = result + "inline int32_t " + declaration.name + "_value(" + declaration.name + " value) { return static_cast<int32_t>(value); }\n"
    result = result + "inline std::optional<" + declaration.name + "> " + declaration.name + "_fromValue(int32_t value) {\n"
    for variant of declaration.variants { result = result + "  if (value == " + string(variant.resolvedIntValue ?? 0) + ") return " + declaration.name + "::" + variant.name + ";\n" }
    result = result + "  return std::nullopt;\n}\n"
  }
  result = result + "inline std::shared_ptr<std::vector<" + declaration.name + ">> " + declaration.name + "_values() { return std::make_shared<std::vector<" + declaration.name + ">>(std::initializer_list<" + declaration.name + ">{"
  for i of 0..<declaration.variants.length {
    if i > 0 { result = result + ", " }
    result = result + declaration.name + "::" + declaration.variants[i].name
  }
  result = result + "}); }\n"
  valueRead := if declaration.backingKind == "string" then "doof::json_as_string(value)" else "doof::json_as_int(value)"
  typeCheck := if declaration.backingKind == "string" then "doof::json_is_string(value)" else "doof::json_is_integer(value)"
  expectedType := if declaration.backingKind == "string" then "string" else "integer"
  result = result + "inline doof::JsonValue " + declaration.name + "_toJsonValue(" + declaration.name + " value) { return doof::json_value(" + declaration.name + "_value(value)); }\n"
  result = result + "inline doof::Result<" + declaration.name + ", std::string> " + declaration.name + "_fromJsonValue(const doof::JsonValue& value, bool) {\n"
  result = result + "  if (!(" + typeCheck + ")) return doof::Failure<std::string>{std::string(\"Expected " + expectedType + " for enum " + declaration.name + ", got \") + doof::json_type_name(value)};\n"
  result = result + "  auto resolved = " + declaration.name + "_fromValue(" + valueRead + ");\n"
  let validValues = ""
  for i of 0..<declaration.variants.length {
    if i > 0 { validValues = validValues + ", " }
    if declaration.backingKind == "string" { validValues = validValues + "\"" + (declaration.variants[i].resolvedStringValue ?? "") + "\"" }
    else { validValues = validValues + string(declaration.variants[i].resolvedIntValue ?? 0) }
  }
  result = result + "  if (!resolved.has_value()) return doof::Failure<std::string>{std::string(\"Unknown backing value for enum " + declaration.name + ": \") + doof::to_string(" + valueRead + ") + " + quote("; expected one of " + validValues) + "};\n"
  result = result + "  return doof::Success<" + declaration.name + ">{resolved.value()};\n}\n"
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
