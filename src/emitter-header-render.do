// Render frozen typed plans into ergonomic C++ without mutating their inputs.
import { CppTypeRegistry } from "./cpp-type"
import { CppDeclaration, renderDeclaration } from "./cpp-declaration"
import { HeaderPlan, HeaderSection } from "./emitter-header-plan"
import { HeaderAliasState, planHeaderAliases } from "./emitter-header-aliases"
import { StringBuilder } from "./string-builder"

class RenderedHeaderSection {
  readonly namespaceName: string
  readonly plan: HeaderPlan
  readonly nextAliasIndex: int
  readonly aliasDeclarations: readonly string[]
  readonly functionSignatures: readonly string[]
  readonly nativeAdapterSignatures: readonly string[]
  readonly earlyModuleValueDeclarations: readonly string[]
  readonly moduleValueDeclarations: readonly string[]
  readonly earlyClassDefinitions: readonly string[]
  readonly classDefinitions: readonly string[]
  readonly interfaceAliases: readonly string[]
  readonly enumDefinitions: readonly string[]
  readonly earlyTypeAliases: readonly string[]
  readonly typeAliases: readonly string[]
}

/** Cache lifetime is one emitModuleGraph, just like its frozen input plans. */
export class HeaderRenderCache {
  private sections: Map<string, RenderedHeaderSection> = {}

  section(section: HeaderSection, state: HeaderAliasState, registry: CppTypeRegistry | none): RenderedHeaderSection {
    key := string(section.namespaceName.length) + ":" + section.namespaceName + ":" + string(state.nextIndex) + ":" + section.plan.identity
    if section.plan.identity != "" && sections.has(key) {
      value := try! sections.get(key)
      state.nextIndex = value.nextAliasIndex
      return value
    }
    value := renderHeaderSection(section, state, registry)
    if section.plan.identity != "" { sections.set(key, value) }
    return value
  }
}

function renderHeaderSection(section: HeaderSection, state: HeaderAliasState, registry: CppTypeRegistry | none): RenderedHeaderSection {
  aliases := planHeaderAliases(section.plan, section.namespaceName, state, registry)
  return RenderedHeaderSection {
    namespaceName: section.namespaceName, plan: section.plan, nextAliasIndex: state.nextIndex,
    aliasDeclarations: aliases.declarations.drainToReadonly(),
    functionSignatures: renderDeclarations(section.plan.functionSignatures, section.namespaceName, aliases.names, registry, aliases.renderedTypes),
    nativeAdapterSignatures: renderDeclarations(section.plan.nativeAdapterSignatures, section.namespaceName, aliases.names, registry, aliases.renderedTypes),
    earlyModuleValueDeclarations: renderDeclarations(section.plan.earlyModuleValueDeclarations, section.namespaceName, aliases.names, registry, aliases.renderedTypes),
    moduleValueDeclarations: renderDeclarations(section.plan.moduleValueDeclarations, section.namespaceName, aliases.names, registry, aliases.renderedTypes),
    earlyClassDefinitions: renderDeclarations(section.plan.earlyClassDefinitions, section.namespaceName, aliases.names, registry, aliases.renderedTypes),
    classDefinitions: renderDeclarations(section.plan.classDefinitions, section.namespaceName, aliases.names, registry, aliases.renderedTypes),
    interfaceAliases: renderDeclarations(section.plan.interfaceAliases, section.namespaceName, aliases.names, registry, aliases.renderedTypes),
    enumDefinitions: renderDeclarations(section.plan.enumDefinitions, section.namespaceName, aliases.names, registry, aliases.renderedTypes),
    earlyTypeAliases: renderDeclarations(section.plan.earlyTypeAliases, section.namespaceName, aliases.definitionNames, registry, aliases.definitionRenderedTypes),
    typeAliases: renderDeclarations(section.plan.typeAliases, section.namespaceName, aliases.definitionNames, registry, aliases.definitionRenderedTypes),
  }
}

function renderDeclarations(declarations: readonly CppDeclaration[], namespace: string, aliases: Map<int, string>, registry: CppTypeRegistry | none, rendered: Map<int, string>): readonly string[] {
  let result: string[] = []
  for declaration of declarations { result.push(renderDeclaration(declaration, namespace, aliases, registry, rendered)) }
  return result.drainToReadonly()
}

export function renderProjectedHeader(inputSections: HeaderSection[], registry: CppTypeRegistry | none = none, cache: HeaderRenderCache = HeaderRenderCache {}): string {
  state := HeaderAliasState {}
  let sections: RenderedHeaderSection[] = []
  for section of inputSections {
    sections.push(cache.section(section, state, registry))
  }
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
    for declaration of section.earlyModuleValueDeclarations { result.append("    " + declaration) }
    result.append("}\n\n")
  }
  // Reference-only variants need nominal declarations but not complete class
  // definitions. Hoist their short structural names once per namespace.
  for section of sections {
    if section.aliasDeclarations.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for alias of section.aliasDeclarations { result.append("    " + alias) }
      result.append("}\n\n")
    }
  }
  // Enums are complete value types and can be referenced by any later class
  // signature. Emit the whole selected enum layer before class definitions,
  // regardless of analyzer discovery order.
  for section of sections {
    if section.plan.enumDefinitions.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for definition of section.enumDefinitions { result.append("    " + definition) }
      result.append("}\n\n")
    }
  }
  for section of sections {
    if section.plan.interfaceAliases.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for alias of section.interfaceAliases { result.append("    " + alias) }
      result.append("}\n\n")
    }
  }
  for section of sections {
    if section.plan.earlyTypeAliases.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for alias of section.earlyTypeAliases { result.append("    " + alias) }
      result.append("}\n\n")
    }
  }
  for section of sections {
    if section.plan.earlyClassDefinitions.length > 0 {
      result.append("namespace " + section.namespaceName + " {\n")
      for definition of section.earlyClassDefinitions { result.append("    " + definition) }
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

function renderFinalSection(result: StringBuilder, section: RenderedHeaderSection): none {
  plan := section.plan
  if plan.nativeAdapterSignatures.length == 0 &&
    plan.moduleValueDeclarations.length == 0 &&
    plan.classDefinitions.length == 0 &&
    plan.typeAliases.length == 0 &&
    plan.functionSignatures.length == 0 { return }
  result.append("namespace " + section.namespaceName + " {\n")
  // Concrete class methods may call module-owned native adapters.
  for signature of section.nativeAdapterSignatures { result.append("    " + signature) }
  for declaration of section.moduleValueDeclarations { result.append("    " + declaration) }
  for definition of section.classDefinitions { result.append("    " + definition) }
  for alias of section.typeAliases { result.append("    " + alias) }
  for signature of section.functionSignatures { result.append("    " + signature) }
  result.append("}\n\n")
}

function headerPlanEmitsNamespaceContent(plan: HeaderPlan): bool {
  return plan.enumDefinitions.length > 0 ||
    plan.interfaceAliases.length > 0 ||
    plan.earlyClassDefinitions.length > 0 ||
    plan.earlyTypeAliases.length > 0 ||
    plan.nativeAdapterSignatures.length > 0 ||
    plan.moduleValueDeclarations.length > 0 ||
    plan.classDefinitions.length > 0 ||
    plan.typeAliases.length > 0 ||
    plan.functionSignatures.length > 0
}

