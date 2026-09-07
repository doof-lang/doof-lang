// Alias selection consumes type nodes only; declaration text is opaque.
import { CppType, CppTypeRegistry, isReferenceVariant, renderCppType } from "./cpp-type"
import { CppDeclaration } from "./cpp-declaration"
import { HeaderPlan } from "./emitter-header-plan"

export class HeaderAliasState {
  let nextIndex: int = 1
}

export class HeaderAliasPlan {
  names: Map<int, string> = {}
  definitionNames: Map<int, string> = {}
  declarations: string[] = []
  renderedTypes: Map<int, string> = {}
  definitionRenderedTypes: Map<int, string> = {}
}

class HeaderTypeUse {
  type_: CppType
  let count: int = 0
}

export function planHeaderAliases(plan: HeaderPlan, namespace: string, state: HeaderAliasState, registry: CppTypeRegistry | none = none): HeaderAliasPlan {
  let uses: HeaderTypeUse[] = []
  let indices: Map<int, int> = {}
  for declarations of [plan.functionSignatures, plan.nativeAdapterSignatures, plan.earlyModuleValueDeclarations,
    plan.moduleValueDeclarations, plan.earlyClassDefinitions, plan.classDefinitions, plan.interfaceAliases,
    plan.enumDefinitions, plan.earlyTypeAliases, plan.typeAliases] {
    for declaration of declarations {
      for part of declaration.parts { if part.type_ != none { collectTypeUses(part.type_!, uses, indices) } }
    }
  }
  aliases := HeaderAliasPlan {}
  let reserved: Set<string> = []
  for name of plan.reservedNamespaceNames { reserved.add(name) }
  for use of uses {
    if use.count < 2 { continue }
    let name = ""
    for index of 0..<plan.preferredTypeAliasTypes.length {
      if plan.preferredTypeAliasTypes[index].id == use.type_.id { name = plan.preferredTypeAliasNames[index]; break }
    }
    if name == "" {
      name = "doof_header_type_" + string(state.nextIndex)
      state.nextIndex += 1
      while reserved.has(name) { name = "doof_header_type_" + string(state.nextIndex); state.nextIndex += 1 }
      reserved.add(name)
      aliases.declarations.push("using " + name + " = " + (if registry == none then renderCppType(use.type_, namespace) else registry!.render(use.type_, namespace)) + ";\n")
      aliases.definitionNames.set(use.type_.id, name)
    }
    aliases.names.set(use.type_.id, name)
  }
  return aliases
}

function collectTypeUses(type_: CppType, uses: HeaderTypeUse[], indices: Map<int, int>): none {
  if type_.kind == "template" && type_.name == "std::variant" {
    if isReferenceVariant(type_) {
      index := indices.get(type_.id) else {
        indices.set(type_.id, uses.length)
        uses.push(HeaderTypeUse { type_, count: 1 })
        return
      }
      uses[index].count += 1
    }
    // Match the existing outer-variant completeness boundary.
    return
  }
  for argument of type_.arguments { collectTypeUses(argument, uses, indices) }
}
