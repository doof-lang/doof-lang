import { Assert } from "std/assert"
import { optionalAccessType, optionalType } from "./checker-absence"
import { noneType, primitive, resultType, typeName, unionType } from "./checker-types"

export function testOptionalTypeIsThePresentValueOrNone(): none {
  layered := unionType([resultType(unionType([primitive("int"), noneType()]), primitive("string")), noneType()])
  Assert.equal(typeName(optionalType(layered)), "int | none")
  Assert.equal(typeName(optionalType(unionType([primitive("int"), noneType()]))), "int | none")
}

export function testOptionalAccessWidensAResultSuccessValue(): none {
  // A Result-valued access keeps its own Failure.
  Assert.equal(typeName(optionalAccessType(resultType(primitive("int"), primitive("string")))), "Result<int | none, string>")
  Assert.equal(typeName(optionalAccessType(resultType(noneType(), primitive("string")))), "Result<none, string>")
  Assert.equal(typeName(optionalAccessType(primitive("int"))), "int | none")
  Assert.equal(typeName(optionalAccessType(noneType())), "none")
}
