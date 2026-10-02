import { Assert } from "std/assert"
import { absenceErrorType, absenceLayers, canBeAbsent, hasFailureLayer, hasPresentValue, presentType } from "./absence-types"
import { noneType, primitive, resultType, typeName, unionType } from "./checker-types"

export function testLayersPeelOuterNoneResultAndInnerNone(): none {
  int_ := primitive("int")
  string_ := primitive("string")
  layered := unionType([resultType(unionType([int_, noneType()]), string_), noneType()])
  layers := absenceLayers(layered)
  Assert.equal(layers.length, 3)
  Assert.isFalse(layers[0].failure)
  Assert.isTrue(layers[1].failure)
  Assert.isFalse(layers[2].failure)
  Assert.equal(typeName(layers[2].present), "int")
  Assert.equal(typeName(presentType(layered)), "int")
}

export function testPlainValuesHaveNoLayers(): none {
  Assert.equal(absenceLayers(primitive("int")).length, 0)
  Assert.isFalse(canBeAbsent(primitive("string")))
  Assert.equal(typeName(presentType(primitive("int"))), "int")
  // A union without a none arm is present.
  Assert.isFalse(canBeAbsent(unionType([primitive("int"), primitive("string")])))
}

export function testNullableUnionKeepsItsPresentArms(): none {
  nullable := unionType([primitive("int"), primitive("string"), noneType()])
  Assert.equal(absenceLayers(nullable).length, 1)
  Assert.isFalse(hasFailureLayer(nullable))
  Assert.equal(typeName(presentType(nullable)), "int | string")
  Assert.equal(absenceErrorType(nullable), none)
}

export function testResultSuccessValueResultIsPresent(): none {
  // Only one Result layer is peeled; a Result in the success value is a value.
  nested := resultType(resultType(primitive("int"), primitive("string")), primitive("string"))
  Assert.equal(absenceLayers(nested).length, 1)
  Assert.equal(typeName(presentType(nested)), "Result<int, string>")
}

export function testResultWithoutSuccessValueHasNoPresentValue(): none {
  done := resultType(noneType(), primitive("string"))
  Assert.isTrue(hasFailureLayer(done))
  Assert.isFalse(hasPresentValue(done))
  Assert.equal(typeName(absenceErrorType(done)!), "string")
}

export function testErrorCaptureIncludesNoneWhenNoneIsAlsoAbsent(): none {
  plain := resultType(primitive("int"), primitive("string"))
  Assert.equal(typeName(absenceErrorType(plain)!), "string")
  inner := resultType(unionType([primitive("int"), noneType()]), primitive("string"))
  Assert.equal(typeName(absenceErrorType(inner)!), "string | none")
  outer := unionType([plain, noneType()])
  Assert.equal(typeName(absenceErrorType(outer)!), "string | none")
}
