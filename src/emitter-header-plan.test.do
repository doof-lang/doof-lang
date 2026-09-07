import { Assert } from "std/assert"
import { textDeclaration, renderDeclaration } from "./cpp-declaration"
import { HeaderPlanBuilder, freezeHeaderPlan } from "./emitter-header-plan"

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
