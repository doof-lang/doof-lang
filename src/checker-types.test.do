import { Assert } from "std/assert"
import { FunctionParamType, Symbol } from "./semantic"
import { arrayType, classType, functionType, isAssignable, mapType, primitive, promiseType, sameType, streamType, typeParameter, unionType, weakType } from "./checker-types"

function symbol(name: string, module: string): Symbol {
  return Symbol { kind: "class", name, module, exported: false }
}

export function testComparesResolvedTypesStructurally(): none {
  Assert.isTrue(sameType(arrayType(primitive("int")), arrayType(primitive("int"))))
  Assert.isFalse(sameType(arrayType(primitive("int")), arrayType(primitive("string"))))
}

export function testAllowsLosslessIntToDoubleWidening(): none {
  Assert.isTrue(isAssignable(primitive("int"), primitive("double")))
  Assert.isFalse(isAssignable(primitive("long"), primitive("double")))
  Assert.isFalse(isAssignable(primitive("double"), primitive("int")))
}

export function testAllowsByteToIntWidening(): none {
  Assert.isTrue(isAssignable(primitive("byte"), primitive("int")))
}

export function testRequiresInvariantCollectionElementTypes(): none {
  Assert.isFalse(isAssignable(arrayType(primitive("int")), arrayType(primitive("long"))))
  Assert.isFalse(isAssignable(mapType(primitive("string"), primitive("int")), mapType(primitive("string"), primitive("long"))))
}

export function testRequiresInvariantPromiseAndStreamValueTypes(): none {
  Assert.isFalse(isAssignable(promiseType(primitive("int")), promiseType(primitive("long"))))
  Assert.isFalse(isAssignable(streamType(primitive("int")), streamType(primitive("long"))))
}

export function testRequiresInvariantWeakReferenceTargets(): none {
  Assert.isFalse(isAssignable(weakType(primitive("int")), weakType(primitive("long"))))
}

export function testDoesNotAssignConcreteValuesToUnconstrainedTypeParameters(): none {
  Assert.isFalse(isAssignable(primitive("int"), typeParameter("T")))
}

export function testRejectsNonLiteralIntToByteNarrowing(): none {
  Assert.isFalse(isAssignable(primitive("int"), primitive("byte")))
}

export function testDistinguishesFunctionSignatures(): none {
  intToString := functionType(
    [FunctionParamType { name: "value", type_: primitive("int"), hasDefault: false }],
    primitive("string"),
  )
  stringToString := functionType(
    [FunctionParamType { name: "value", type_: primitive("string"), hasDefault: false }],
    primitive("string"),
  )
  intToInt := functionType(
    [FunctionParamType { name: "value", type_: primitive("int"), hasDefault: false }],
    primitive("int"),
  )

  Assert.isTrue(sameType(intToString, intToString))
  Assert.isFalse(sameType(intToString, stringToString))
  Assert.isFalse(sameType(intToString, intToInt))
}

export function testIgnoresFunctionParameterNamesForCompatibility(): none {
  response := classType("Response", symbol("Response", "/main.do"))
  upgrade := classType("Upgrade", symbol("Upgrade", "/main.do"))
  outcome := unionType([response, upgrade])
  responseCallback := functionType([], response)
  outcomeCallback := functionType([], outcome)
  renamed := functionType(
    [FunctionParamType { name: "other", type_: primitive("int"), hasDefault: false }],
    primitive("string"),
  )
  named := functionType(
    [FunctionParamType { name: "value", type_: primitive("int"), hasDefault: false }],
    primitive("string"),
  )

  wrongParameterType := functionType(
    [FunctionParamType { name: "other", type_: primitive("string"), hasDefault: false }],
    primitive("string"),
  )
  wrongArity := functionType([], primitive("string"))

  Assert.isTrue(isAssignable(responseCallback, outcomeCallback))
  Assert.isFalse(isAssignable(outcomeCallback, responseCallback))
  Assert.isFalse(sameType(named, renamed))
  Assert.isTrue(isAssignable(named, renamed))
  Assert.isFalse(isAssignable(named, wrongParameterType))
  Assert.isFalse(isAssignable(named, wrongArity))
}

export function testUsesNominalIdentityForSameNamedClasses(): none {
  left := classType("Config", symbol("Config", "/left.do"))
  same := classType("Config", symbol("Config", "/left.do"))
  other := classType("Config", symbol("Config", "/right.do"))

  Assert.isTrue(sameType(left, same))
  Assert.isFalse(sameType(left, other))
}

export function testRequiresRecordedStructuralStreamConformance(): none {
  plainSymbol := symbol("Plain", "/main.do")
  plain := classType("Plain", plainSymbol)
  Assert.isFalse(isAssignable(plain, streamType(primitive("int"))))

  streamSymbol := symbol("Values", "/main.do")
  streamSymbol.typeParams.push("T")
  streamSymbol.streamElementTypes.push(typeParameter("T"))
  ints := classType("Values", streamSymbol, [primitive("int")])
  Assert.isTrue(isAssignable(ints, streamType(primitive("int"))))
  Assert.isFalse(isAssignable(ints, streamType(primitive("string"))))
}
