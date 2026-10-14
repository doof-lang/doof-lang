import { Assert } from "std/assert"
import { ClassType, FunctionParamType, InterfaceType, ResolvedType, Symbol } from "./semantic"
import { actorType, classMetadataType, containsTypeParameter, containsTypeParameters, methodReflectionType, setType, tupleType, applyDeepReadonly, interfaceBoundReceiver, isWeakReferenceTarget, arrayType, classType, displayTypeName, failureType, functionType, isAssignable, mapType, noneType, primitive, promiseType, resultArmExpectation, resultType, sameType, streamType, substituteTypeParams, successType, typeName, typeParameter, mixedWeakUnionMessage, unionMutabilityConflict, unionType, weakType } from "./checker-types"

export function testResultArmAssignabilityUsesOnlyItsPayloadChannel(): none {
  success := successType(primitive("int"))
  failure := failureType(primitive("string"))
  Assert.isTrue(isAssignable(success, resultType(primitive("int"), primitive("bool"))))
  Assert.isTrue(isAssignable(success, resultType(primitive("long"), primitive("bool"))))
  Assert.isTrue(isAssignable(failure, resultType(primitive("bool"), primitive("string"))))
  Assert.isFalse(isAssignable(success, resultType(primitive("string"), primitive("bool"))))
  Assert.isFalse(isAssignable(failure, resultType(primitive("bool"), primitive("int"))))
}

export function testGenericNoneLiteralReadonlyUnionNormalization(): none {
  mutableArray := arrayType(primitive("int"))
  readonlyArray := arrayType(primitive("int"), true)
  Assert.isTrue(sameType(applyDeepReadonly(unionType([mutableArray, readonlyArray])), readonlyArray))
  Assert.isTrue(sameType(applyDeepReadonly(unionType([readonlyArray, mutableArray])), readonlyArray))
  distinct := unionType([arrayType(primitive("int")), arrayType(primitive("string"))])
  Assert.equal(applyDeepReadonly(distinct).kind, "union")
  Assert.isFalse(isAssignable(readonlyArray, mutableArray))
  optional := unionType([primitive("int"), noneType()])
  genericOptional := unionType([typeParameter("T"), noneType()])
  Assert.isTrue(sameType(substituteTypeParams(genericOptional, ["T"], [optional]), optional))
}

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

export function testAllowsByteToWiderNumericWidening(): none {
  Assert.isTrue(isAssignable(primitive("byte"), primitive("long")))
  Assert.isTrue(isAssignable(primitive("byte"), primitive("float")))
  Assert.isTrue(isAssignable(primitive("byte"), primitive("double")))
}

export function testRejectsLossyIntToFloatWidening(): none {
  Assert.isFalse(isAssignable(primitive("int"), primitive("float")))
  Assert.isFalse(isAssignable(primitive("long"), primitive("double")))
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

export function testWeakReferencesWidenOnlyWhereTheReferentKeepsItsIdentity(): none {
  circle := classType("Circle", symbol("Circle", "/main.do"))
  label := classType("Label", symbol("Label", "/main.do"))
  square := classType("Square", symbol("Square", "/main.do"))
  pair := unionType([circle, label])
  Assert.isTrue(isAssignable(weakType(circle), weakType(pair)))
  Assert.isTrue(isAssignable(weakType(pair), weakType(unionType([circle, label, square]))))
  Assert.isTrue(isAssignable(weakType(unionType([circle, noneType()])), weakType(unionType([circle, label, noneType()]))))
  Assert.isFalse(isAssignable(weakType(pair), weakType(circle)))
  Assert.isFalse(isAssignable(weakType(unionType([circle, noneType()])), weakType(pair)))
  Assert.isFalse(isAssignable(weakType(circle), weakType(square)))
  Assert.isTrue(isAssignable(weakType(arrayType(circle)), weakType(unionType([arrayType(circle), label]))))
  Assert.isFalse(isAssignable(weakType(arrayType(circle)), weakType(arrayType(circle, true))))
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

export function testInterfaceBoundReceiverPreservesUnboundedParameters(): none {
  parameter := typeParameter("T")
  Assert.isTrue(sameType(interfaceBoundReceiver(parameter), parameter))
}

export function testUnionMutabilityConflicts(): none {
  mutable := arrayType(primitive("int"))
  frozen := arrayType(primitive("int"), true)
  Assert.isFalse(sameType(mutable, frozen))
  Assert.isTrue(unionMutabilityConflict(unionType([mutable, frozen])) != none)
  Assert.isTrue(unionMutabilityConflict(unionType([arrayType(mutable), arrayType(frozen)])) != none)
  Assert.isTrue(unionMutabilityConflict(unionType([promiseType(mutable), promiseType(frozen)])) != none)
  Assert.isTrue(unionMutabilityConflict(unionType([weakType(mutable), weakType(frozen)])) != none)
  Assert.equal(unionMutabilityConflict(unionType([mutable, mutable])), none)
  Assert.equal(unionMutabilityConflict(unionType([mutable, noneType()])), none)
  Assert.equal(unionMutabilityConflict(unionType([mutable, arrayType(primitive("string"), true)])), none)
  Assert.equal(unionMutabilityConflict(unionType([classType("A", symbol("A", "/a.do")), classType("A", symbol("A", "/b.do"))])), none)
}

import { UnionResolvedType } from "./semantic"

export function testUnionMutabilityConflictPreservesFirstDiagnostic(): none {
  mutable := arrayType(primitive("int"))
  frozen := arrayType(primitive("int"), true)
  expected := unionMutabilityConflict(unionType([mutable, frozen]))
  Assert.isTrue(expected != none)
  // Duplicate and unrelated arms are not conflicts; preserve the first real pair.
  actual := unionMutabilityConflict(UnionResolvedType { types: [
    primitive("string"), mutable, mutable, frozen,
    arrayType(primitive("string")), arrayType(primitive("string"), true),
  ] })
  Assert.equal(actual, expected)
  Assert.equal(unionMutabilityConflict(UnionResolvedType { types: [] }), none)
  Assert.equal(unionMutabilityConflict(UnionResolvedType { types: [mutable, mutable] }), none)
}

export function testUnionMutabilityNominalGuardPreservesGenericConflicts(): none {
  nominal := classType("Node", symbol("Node", "/nodes.do"))
  other := classType("Other", symbol("Other", "/nodes.do"))
  Assert.equal(unionMutabilityConflict(UnionResolvedType { types: [nominal, nominal, other] }), none)
  generic := symbol("Box", "/nodes.do")
  generic.typeParams.push("T")
  mutable := classType("Box", generic, [promiseType(arrayType(primitive("int")))])
  frozen := classType("Box", generic, [promiseType(arrayType(primitive("int"), true))])
  expected := unionMutabilityConflict(UnionResolvedType { types: [mutable, frozen] })
  Assert.isTrue(expected != none)
  Assert.equal(unionMutabilityConflict(UnionResolvedType { types: [nominal, mutable, other, frozen] }), expected)
  Assert.equal(unionMutabilityConflict(UnionResolvedType { types: [mutable, nominal, frozen, other] }), expected)
  Assert.equal(unionMutabilityConflict(UnionResolvedType { types: [nominal] }), none)
}

export function testDisplayTypeNameSpellsCallableSignatures(): none {
  callback := functionType([FunctionParamType { name: "it", type_: primitive("int"), hasDefault: false }, FunctionParamType { name: "index", type_: primitive("int"), hasDefault: false }], typeParameter("U"))
  outer := functionType([FunctionParamType { name: "mapper", type_: callback, hasDefault: false }], arrayType(primitive("string")))
  Assert.equal(displayTypeName(outer), "(mapper: (it: int, index: int): U): string[]")
  Assert.equal(displayTypeName(unionType([primitive("int"), noneType()])), "int | none")
}

export function testResultArmUnionsAreCanonicalResults(): none {
  canonical := resultType(primitive("int"), primitive("string"))
  Assert.isTrue(sameType(unionType([successType(primitive("int")), failureType(primitive("string"))]), canonical))
  Assert.isTrue(sameType(unionType([failureType(primitive("string")), successType(primitive("int"))]), canonical))
  Assert.isTrue(sameType(unionType([successType(primitive("int")), noneType(), failureType(primitive("string"))]), unionType([canonical, noneType()])))
  lone := unionType([successType(primitive("int")), noneType()])
  Assert.equal(displayTypeName(lone), "Success<int> | none")
  Assert.isTrue(isAssignable(successType(primitive("int")), resultType(primitive("long"), primitive("string"))))
  Assert.isFalse(isAssignable(successType(primitive("int")), successType(primitive("long"))))
}

export function testResultArmExpectationsComeFromResultsAndMatchingArms(): none {
  result := resultType(primitive("int"), primitive("string"))
  fromResult := resultArmExpectation("Failure", result)
  Assert.isTrue(fromResult.result != none)
  Assert.isTrue(sameType(fromResult.payload!, primitive("string")))
  fromArm := resultArmExpectation("Success", successType(primitive("long")))
  Assert.equal(fromArm.result, none)
  Assert.isTrue(sameType(fromArm.payload!, primitive("long")))
  Assert.equal(resultArmExpectation("Failure", successType(primitive("long"))).payload, none)
  nullable := resultArmExpectation("Success", unionType([result, noneType()]))
  Assert.isTrue(sameType(nullable.payload!, primitive("int")))
  ambiguous := resultArmExpectation("Success", unionType([result, resultType(primitive("bool"), primitive("string"))]))
  Assert.equal(ambiguous.payload, none)
}

export function testOptionalWeakUnionsAreWeakOptionalReferences(): none {
  node := classType("Node", symbol("Node", "/main.do"))
  canonical := weakType(unionType([node, noneType()]))
  Assert.isTrue(sameType(unionType([weakType(node), noneType()]), canonical))
  Assert.isTrue(sameType(unionType([noneType(), weakType(node)]), canonical))
  Assert.isTrue(sameType(unionType([canonical, noneType()]), canonical))
  Assert.equal(typeName(canonical), "weak Node | none")
  Assert.equal(mixedWeakUnionMessage(canonical), none)
}

export function testMixedWeakUnionsStayDistinctAndReportTheWholeUnionSpelling(): none {
  node := classType("Node", symbol("Node", "/main.do"))
  other := classType("Other", symbol("Other", "/main.do"))
  mixed := unionType([other, weakType(node), noneType()])
  Assert.equal(typeName(mixed), "Other | (weak Node) | none")
  Assert.equal(mixedWeakUnionMessage(mixed)!, "Union \"Other | (weak Node) | none\" mixes weak and strong references; 'weak' qualifies the whole union, as in \"weak Other | Node | none\"")
  twoWeak := unionType([weakType(node), weakType(other)])
  Assert.stringContains(mixedWeakUnionMessage(twoWeak)!, "as in \"weak Node | Other\"")
  Assert.equal(mixedWeakUnionMessage(unionType([node, noneType()])), none)
}

export function testTypeNamesGroupWeakAndUnionCollectionOperands(): none {
  node := classType("Node", symbol("Node", "/main.do"))
  Assert.equal(typeName(arrayType(weakType(node))), "(weak Node)[]")
  Assert.equal(typeName(arrayType(weakType(node), true)), "readonly (weak Node)[]")
  Assert.equal(typeName(arrayType(unionType([node, noneType()]))), "(Node | none)[]")
  Assert.equal(typeName(weakType(arrayType(node))), "weak (Node[])")
  Assert.equal(typeName(weakType(mapType(primitive("string"), node))), "weak (Map<string, Node>)")
  Assert.equal(typeName(weakType(unionType([arrayType(node), noneType()]))), "weak (Node[] | none)")
  Assert.equal(typeName(mapType(primitive("string"), weakType(node))), "Map<string, weak Node>")
}

export function testWeakReferencesWidenIntoOptionalWeakSlots(): none {
  node := classType("Node", symbol("Node", "/main.do"))
  other := classType("Other", symbol("Other", "/main.do"))
  optional := unionType([weakType(node), noneType()])
  Assert.isTrue(isAssignable(weakType(node), optional))
  Assert.isTrue(isAssignable(optional, optional))
  Assert.isFalse(isAssignable(optional, weakType(node)))
  Assert.isFalse(isAssignable(weakType(other), optional))
}

export function testInterfacesAreWeakReferenceTargets(): none {
  shape := InterfaceType { name: "Shape", symbol: Symbol { kind: "interface", name: "Shape", module: "/main.do", exported: false } }
  Assert.isTrue(isWeakReferenceTarget(shape))
  Assert.isTrue(isWeakReferenceTarget(unionType([shape, noneType()])))
  Assert.isFalse(isWeakReferenceTarget(unionType([shape, primitive("int")])))
}

function boxClass(): ClassType {
  return classType("Box", Symbol { kind: "class", name: "Box", module: "/main.do", exported: false })
}

export function testSubstituteTypeParamsReachesMetadataAndReflection(): none {
  t := typeParameter("T")
  metadata := substituteTypeParams(classMetadataType(t), ["T"], [primitive("int")])
  Assert.equal(typeName(metadata), "ClassMetadata<int>")
  reflection := substituteTypeParams(methodReflectionType(classType("Box", boxClass().symbol, [t])), ["T"], [primitive("string")])
  Assert.equal(typeName(reflection), "MethodReflection<Box<string>>")
  // Unrelated names leave the parameter in place.
  Assert.equal(typeName(substituteTypeParams(classMetadataType(t), ["U"], [primitive("int")])), "ClassMetadata<T>")
}

export function testApplyDeepReadonlyReachesMetadataAndReflection(): none {
  inner := classType("Box", boxClass().symbol, [arrayType(primitive("int"))])
  Assert.equal(typeName(applyDeepReadonly(classMetadataType(inner))), "ClassMetadata<Box<readonly int[]>>")
  Assert.equal(typeName(applyDeepReadonly(methodReflectionType(inner))), "MethodReflection<Box<readonly int[]>>")
}

export function testContainsTypeParameterSeesEveryNestedPosition(): none {
  t := typeParameter("T")
  int_ := primitive("int")
  holder := classType("Box", boxClass().symbol, [t])
  generic: ResolvedType[] := [
    t, holder, arrayType(t), mapType(primitive("string"), t), setType(t), streamType(t),
    resultType(int_, t), successType(t), failureType(t), actorType(holder), promiseType(t),
    classMetadataType(t), methodReflectionType(holder), tupleType([int_, t]), unionType([t, noneType()]),
    weakType(holder), functionType([FunctionParamType { name: "value", type_: t, hasDefault: false }], int_), functionType([], t),
  ]
  for type_ of generic {
    if !containsTypeParameter(type_) { panic("expected a type parameter in " + typeName(type_)) }
  }
  concrete := classType("Box", boxClass().symbol, [int_])
  concreteTypes: ResolvedType[] := [
    int_, concrete, arrayType(int_), mapType(primitive("string"), int_), promiseType(int_), actorType(concrete),
    classMetadataType(concrete), methodReflectionType(concrete), functionType([], int_), unionType([int_, noneType()]),
  ]
  for type_ of concreteTypes {
    if containsTypeParameter(type_) { panic("expected no type parameter in " + typeName(type_)) }
  }
  Assert.isFalse(containsTypeParameters([]))
  Assert.isTrue(containsTypeParameters([int_, promiseType(t)]))
}
