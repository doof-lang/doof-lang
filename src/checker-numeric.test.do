import { Assert } from "std/assert"
import { primitive, sameType, typeParameter, unionType } from "./checker-types"
import { isNumericOperand, isIntegerOperand, numericOperationType, numericOperatorAllowed, satisfiesNumericConstraint } from "./checker-numeric"

export function testCheckerReviewNumericCapabilities(): none {
  floating := typeParameter("T", "", unionType([primitive("float"), primitive("double")]))
  integral := typeParameter("I", "", unionType([primitive("int"), primitive("long")]))
  Assert.isTrue(isNumericOperand(floating))
  Assert.isFalse(isIntegerOperand(floating))
  Assert.isTrue(isIntegerOperand(integral))
  Assert.isTrue(sameType(numericOperationType(floating, floating), floating))
  Assert.isTrue(sameType(numericOperationType(integral, integral), integral))
  Assert.isTrue(sameType(numericOperationType(floating, primitive("int")), floating))
  Assert.isTrue(sameType(numericOperationType(floating, primitive("double")), primitive("double")))
  Assert.isTrue(sameType(numericOperationType(primitive("byte"), primitive("byte")), primitive("int")))
  Assert.isTrue(numericOperatorAllowed("/", floating, floating))
  Assert.isFalse(numericOperatorAllowed("/", integral, integral))
  Assert.isFalse(numericOperatorAllowed("%", floating, floating))
  Assert.isFalse(isNumericOperand(unionType([primitive("int"), primitive("long")])))
  Assert.isFalse(satisfiesNumericConstraint(primitive("int"), primitive("double")))
  Assert.isTrue(satisfiesNumericConstraint(floating, unionType([primitive("float"), primitive("double")])) )
}
