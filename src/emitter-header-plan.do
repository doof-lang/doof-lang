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

export function freezeHeaderPlan(plan: HeaderPlanBuilder, identity: string = ""): HeaderPlan {
  return HeaderPlan {
    identity,
    functionSignatures: plan.functionSignatures.drainToReadonly(),
    nativeAdapterSignatures: plan.nativeAdapterSignatures.drainToReadonly(),
    earlyModuleValueDeclarations: plan.earlyModuleValueDeclarations.drainToReadonly(),
    moduleValueDeclarations: plan.moduleValueDeclarations.drainToReadonly(),
    earlyClassDefinitions: plan.earlyClassDefinitions.drainToReadonly(),
    classDefinitions: plan.classDefinitions.drainToReadonly(),
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

export class HeaderSection {
  readonly namespaceName: string
  readonly plan: HeaderPlan
}
