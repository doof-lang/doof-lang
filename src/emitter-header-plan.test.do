import { Assert } from "std/assert"
import { textDeclaration, renderDeclaration } from "./cpp-declaration"
import { addClassDefinition, HeaderPlanBuilder, freezeHeaderPlan } from "./emitter-header-plan"

export function testStructuredHeaderFreezeDetachesBuilder(): none {
  builder := HeaderPlanBuilder { hasMain: true, mainReturnsInt: true }
  builder.functionSignatures.push(textDeclaration("int32_t doof_main();\n"))
  plan := freezeHeaderPlan(builder)
  builder.functionSignatures.push(textDeclaration("poison"))
  builder.hasMain = false
  Assert.isTrue(plan.hasMain && plan.mainReturnsInt)
  Assert.equal(plan.functionSignatures.length, 1)
  Assert.equal(renderDeclaration(plan.functionSignatures[0]), "int32_t doof_main();\n")
}

export function testClassDefinitionsFollowTheirByValueDependencies(): none {
  builder := HeaderPlanBuilder {}
  addClassDefinition(builder, "Owner", ["Inner", "Elsewhere"], textDeclaration("Owner"))
  addClassDefinition(builder, "Unrelated", [], textDeclaration("Unrelated"))
  addClassDefinition(builder, "Inner", ["Leaf"], textDeclaration("Inner"))
  addClassDefinition(builder, "Leaf", [], textDeclaration("Leaf"))
  plan := freezeHeaderPlan(builder)
  let order: string[] = []
  for definition of plan.classDefinitions { order.push(renderDeclaration(definition)) }
  // Dependencies move ahead of their owner; unrelated definitions and names
  // defined outside this section keep the original order.
  Assert.mutableArrayEqual(order, ["Leaf", "Inner", "Owner", "Unrelated"])
}
