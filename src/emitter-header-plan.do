// Mutable construction ends at freezeHeaderPlan; renderers share immutable plans.
import { CppType } from "./cpp-type"
import { CppDeclaration } from "./cpp-declaration"

export class HeaderPlan {
  readonly identity: string = ""
  readonly functionSignatures: readonly CppDeclaration[] = []
  readonly nativeAdapterSignatures: readonly CppDeclaration[] = []
  readonly earlyModuleValueDeclarations: readonly CppDeclaration[] = []
  readonly moduleValueDeclarations: readonly CppDeclaration[] = []
  readonly earlyClassDefinitions: readonly CppDeclaration[] = []
  readonly classDefinitions: readonly CppDeclaration[] = []
  readonly interfaceAliases: readonly CppDeclaration[] = []
  readonly enumDefinitions: readonly CppDeclaration[] = []
  readonly earlyTypeAliases: readonly CppDeclaration[] = []
  readonly typeAliases: readonly CppDeclaration[] = []
  readonly classForwardDeclarations: readonly string[] = []
  readonly typeOnlyForwardDeclarations: readonly string[] = []
  readonly nativeIncludes: readonly string[] = []
  readonly nativeAliases: readonly string[] = []
  readonly nativeNamespaces: readonly string[] = []
  readonly reservedNamespaceNames: readonly string[] = []
  readonly preferredTypeAliasNames: readonly string[] = []
  readonly preferredTypeAliasTypes: readonly CppType[] = []
  readonly hasMain: bool = false
  readonly mainReturnsInt: bool = false
  readonly mainAcceptsArgs: bool = false
}

export class HeaderPlanBuilder {
  functionSignatures: CppDeclaration[] = []
  nativeAdapterSignatures: CppDeclaration[] = []
  earlyModuleValueDeclarations: CppDeclaration[] = []
  moduleValueDeclarations: CppDeclaration[] = []
  earlyClassDefinitions: CppDeclaration[] = []
  classDefinitions: CppDeclaration[] = []
  // Parallel to classDefinitions: each definition's emitted name and the
  // same-section names it stores by value. Freezing orders them dependency-first.
  classDefinitionNames: string[] = []
  classDefinitionDependencies: string[][] = []
  interfaceAliases: CppDeclaration[] = []
  enumDefinitions: CppDeclaration[] = []
  earlyTypeAliases: CppDeclaration[] = []
  typeAliases: CppDeclaration[] = []
  classForwardDeclarations: string[] = []
  typeOnlyForwardDeclarations: string[] = []
  nativeIncludes: string[] = []
  nativeAliases: string[] = []
  nativeNamespaces: string[] = []
  reservedNamespaceNames: string[] = []
  preferredTypeAliasNames: string[] = []
  preferredTypeAliasTypes: CppType[] = []
  let hasMain: bool = false
  let mainReturnsInt: bool = false
  let mainAcceptsArgs: bool = false
}

export function addClassDefinition(plan: HeaderPlanBuilder, name: string, dependencies: string[], definition: CppDeclaration): none {
  plan.classDefinitions.push(definition)
  plan.classDefinitionNames.push(name)
  plan.classDefinitionDependencies.push(dependencies)
}

export function freezeHeaderPlan(plan: HeaderPlanBuilder, identity: string = ""): HeaderPlan {
  return HeaderPlan {
    identity,
    functionSignatures: plan.functionSignatures.drainToReadonly(),
    nativeAdapterSignatures: plan.nativeAdapterSignatures.drainToReadonly(),
    earlyModuleValueDeclarations: plan.earlyModuleValueDeclarations.drainToReadonly(),
    moduleValueDeclarations: plan.moduleValueDeclarations.drainToReadonly(),
    earlyClassDefinitions: plan.earlyClassDefinitions.drainToReadonly(),
    classDefinitions: orderClassDefinitions(plan).drainToReadonly(),
    interfaceAliases: plan.interfaceAliases.drainToReadonly(),
    enumDefinitions: plan.enumDefinitions.drainToReadonly(),
    earlyTypeAliases: plan.earlyTypeAliases.drainToReadonly(),
    typeAliases: plan.typeAliases.drainToReadonly(),
    classForwardDeclarations: plan.classForwardDeclarations.drainToReadonly(),
    typeOnlyForwardDeclarations: plan.typeOnlyForwardDeclarations.drainToReadonly(),
    nativeIncludes: plan.nativeIncludes.drainToReadonly(),
    nativeAliases: plan.nativeAliases.drainToReadonly(),
    nativeNamespaces: plan.nativeNamespaces.drainToReadonly(),
    reservedNamespaceNames: plan.reservedNamespaceNames.drainToReadonly(),
    preferredTypeAliasNames: plan.preferredTypeAliasNames.drainToReadonly(),
    preferredTypeAliasTypes: plan.preferredTypeAliasTypes.drainToReadonly(),
    hasMain: plan.hasMain,
    mainReturnsInt: plan.mainReturnsInt,
    mainAcceptsArgs: plan.mainAcceptsArgs,
  }
}

// C++ requires a complete type for every by-value field, so a definition must
// follow the definitions it stores. Source and instantiation order is kept
// otherwise; by-value cycles are rejected before emission, so a back edge
// leaves the remaining order unchanged.
function orderClassDefinitions(plan: HeaderPlanBuilder): CppDeclaration[] {
  let ordered: CppDeclaration[] = []
  let states: int[] = []
  for _ of plan.classDefinitions { states.push(0) }
  for index of 0..<plan.classDefinitions.length { visitClassDefinition(plan, index, states, ordered) }
  return ordered
}

function visitClassDefinition(plan: HeaderPlanBuilder, index: int, states: int[], ordered: CppDeclaration[]): none {
  if states[index] != 0 { return }
  states[index] = 1
  if index < plan.classDefinitionDependencies.length {
    for dependency of plan.classDefinitionDependencies[index] {
      for candidate of 0..<plan.classDefinitionNames.length {
        if plan.classDefinitionNames[candidate] == dependency { visitClassDefinition(plan, candidate, states, ordered) }
      }
    }
  }
  states[index] = 2
  ordered.push(plan.classDefinitions[index])
}

export class HeaderSection {
  readonly namespaceName: string
  readonly plan: HeaderPlan
}
