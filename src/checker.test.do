import { Assert } from "std/assert"
import isolated function codePointToUtf8(value: int): string from "doof_runtime.hpp" as doof::char_to_utf8
import { createAnalyzer } from "./analyzer"
import { createChecker, validateCheckedTypes, validateDeepReadonlyFields, validateIsolationEffects } from "./checker"
import { CheckResult, Diagnostic, FunctionType, SourceFile } from "./semantic"
import { AsExpression, AssignmentExpression, BinaryExpression, Block, CallExpression, CaseStatement, ClassDeclaration, ConstructExpression, Expression, ExpressionStatement, Identifier, IfStatement, FunctionDeclaration, ImmutableBinding, LetDeclaration, MemberExpression, ObjectLiteral, ReadonlyDeclaration, ReturnStatement, WithStatement } from "./ast"
import { typeName, unknownType } from "./checker-types"

function checkedIncludingDeprecations(source: string): CheckResult {
  sources := [SourceFile { path: "/main.do", source }]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checker := createChecker(analysis, "/main.do")
  semantic := checker.check("/main.do")
  diagnostics := semantic.diagnostics
  for diagnostic of validateDeepReadonlyFields(analysis) { diagnostics.push(diagnostic) }
  for diagnostic of validateIsolationEffects(analysis) { diagnostics.push(diagnostic) }
  return CheckResult { diagnostics }
}

// Most checker fixtures intentionally exercise behavior unrelated to legacy
// spelling. Keep their historical assertions focused while dedicated tests
// below verify the deprecation diagnostics themselves.
function checked(source: string): CheckResult {
  result := checkedIncludingDeprecations(source)
  let diagnostics: Diagnostic[] = []
  for diagnostic of result.diagnostics {
    if diagnostic.replacement != "none" && !diagnostic.message.contains("'function' on class methods is deprecated") {
      diagnostics.push(diagnostic)
    }
  }
  return CheckResult { diagnostics }
}

function checkedEntry(source: string, entryMode: string = "executable"): CheckResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  return createChecker(analysis, "/main.do", entryMode).check("/main.do")
}

function assertRejected(source: string): none {
  result := checked(source)
  Assert.isTrue(result.diagnostics.length > 0)
}

export function testChecksTypedTagsAsNamedCallsAndConstruction(): none {
  result := checked(
    "class Widget { id: int\nname: string\nchildren: string[] = []\nonClick: (): none = => {} }\n" +
    "class Box<T> { value: T }\n" +
    "function render<T>(value: T, children: T[] = []): T => value\n" +
    "class Renderers { card: (title: string, children: string[]): string }\n" +
    "renderers := Renderers { card: (title: string, children: string[]): string => title }\n" +
    "widget := <Widget name=\"red\" id=1 onClick=>println(\"hello\")>hello</Widget>\n" +
    "generic := <render value=\"ok\">child</render>\n" +
    "boxed := <Box<string> value=\"boxed\"/>\n" +
    "member := <renderers.card title=\"Title\">Body</renderers.card>\n" +
    "println(widget.name + generic + boxed.value + member)",
  )
  Assert.equal(result.diagnostics.length, 0)
}

export function testContextualLambdaUsesUniqueCallableUnionMember(): none {
  result := checked(
    "type Handler = (event: string): none\n" +
    "function install(handler: Handler | none = none): none {}\n" +
    "function button(onClick: Handler | none = none, children: string[] = []): none {}\n" +
    "install(=> println(event))\n" +
    "<button onClick=>println(event)>Save</button>",
  )
  Assert.equal(result.diagnostics.length, 0)

  ambiguous := checked(
    "type First = (left: int): none\n" +
    "type Second = (right: string): none\n" +
    "function install(handler: First | Second): none {}\n" +
    "install(=> println(left))",
  )
  Assert.isTrue(ambiguous.diagnostics.length > 0)
  Assert.stringContains(ambiguous.diagnostics[0].message, "Unknown identifier 'left'")
}

export function testDiagnosesInvalidTypedTagCalls(): none {
  missingChildren := checked("function render(title: string): string => title\nvalue := <render title=\"x\">body</render>\nprintln(value)")
  Assert.equal(missingChildren.diagnostics.length, 1)
  Assert.stringContains(missingChildren.diagnostics[0].message, "Unknown named argument 'children'")

  wrongType := checked("class Widget { id: int }\nvalue := <Widget id=\"bad\"/>\nprintln(\"\")")
  Assert.equal(wrongType.diagnostics.length, 1)
  Assert.stringContains(wrongType.diagnostics[0].message, "expected int")

  nonCallable := checked("value := 1\nother := <value/>\nprintln(other)")
  Assert.equal(nonCallable.diagnostics.length, 1)
  Assert.stringContains(nonCallable.diagnostics[0].message, "is not callable")
}

export function testRejectsInvalidDeclaredDefaultsAndExpressionBodies(): none {
  assertRejected("function useCount(count: int = \"many\"): none {}")
  assertRejected("class Counter { count: int = \"zero\" }")
  assertRejected("function wrongReturnType(): int => \"not an int\"")
}

export function testRejectsInvalidOperatorOperandDomains(): none {
  validNullableChain := checked("function choose(first: string | none, second: string | none): string => first ?? second ?? \"fallback\"")
  Assert.equal(validNullableChain.diagnostics.length, 0)
  validGenericComparison := checked("function larger<T>(left: T, right: T): bool => left > right")
  Assert.equal(validGenericComparison.diagnostics.length, 0)
  validGenericActors := checked("class Sender<T> { readonly value: T }\nclass Receiver<T> { readonly value: T }\nclass Worker { function open(): Tuple<Sender<int>, Receiver<int> > => (Sender { value: 1 }, Receiver { value: 2 }) }\nfunction main(): int { worker := Actor<Worker>()\n(sender, receiver) := worker.open()\nretired := retire worker\nreturn sender.value + receiver.value }")
  Assert.equal(validGenericActors.diagnostics.length, 0)
  assertRejected("function main(): none { ignored := 7 / 2 }")
  assertRejected("function main(): none { ignored := 7.0 \\ 2.0 }")
  assertRejected("function main(): none { ignored := 7.0 % 2.0 }")
  assertRejected("function main(): none { ignored := 1.0 & 2.0 }")
  assertRejected("function main(): none { ignored := ~1.0 }")
  assertRejected("function main(): none { ignored := 1 == \"1\" }")
  assertRejected("function main(): none { ignored := 1 < \"two\" }")
  assertRejected("function main(): none { ignored := 1 ?? 2 }")
  assertRejected("function main(): none { value := 1!\nprintln(value) }")
  assertRejected("function main(): none { let value = 1\nvalue ??= 2 }")
  assertRejected("function main(): none { let count = 1\ncount += \"two\" }")
}

export function testRejectsLoopExitsAndCallerOutsideTheirContexts(): none {
  assertRejected("function main(): none { break }")
  assertRejected("function main(): none { continue }")
  assertRejected("function main(): none { ignored := @caller }")
}

export function testRejectsInvalidForOfSourcesAndDestructuringArity(): none {
  nonIterable := checked("function main(): none { for _ of 1 {} }")
  Assert.equal(nonIterable.diagnostics.length, 1)
  Assert.stringContains(nonIterable.diagnostics[0].message, "For-of requires")

  scalarElement := checked("function main(): none { for _, _ of [1, 2] {} }")
  Assert.equal(scalarElement.diagnostics.length, 1)
  Assert.stringContains(scalarElement.diagnostics[0].message, "requires a tuple with 2 elements")

  wrongTupleArity := checked("function main(): none { for _, _ of [(1, 2, 3)] {} }")
  Assert.equal(wrongTupleArity.diagnostics.length, 1)
  Assert.stringContains(wrongTupleArity.diagnostics[0].message, "requires a tuple with 2 elements")
}

export function testChecksStructuralStreamConformance(): none {
  missingProtocol := checked("class Broken implements Stream<int> {}")
  Assert.equal(missingProtocol.diagnostics.length, 1)
  Assert.stringContains(missingProtocol.diagnostics[0].message, "does not satisfy interface \"Stream<int>\"")

  wrongNext := checked("class Broken implements Stream<int> { next(): int => 1\nvalue(): int => 1 }")
  Assert.equal(wrongNext.diagnostics.length, 1)
  Assert.stringContains(wrongNext.diagnostics[0].message, "does not satisfy interface")

  structural := checked("class Counter { next(): bool => false\nvalue(): int => 1 }\nfunction consume(stream: Stream<int>): none {}\nfunction main(): none { consume(Counter()) }")
  Assert.equal(structural.diagnostics.length, 0)

  unrelated := checked("class Counter {}\nfunction consume(stream: Stream<int>): none {}\nfunction main(): none { consume(Counter()) }")
  Assert.equal(unrelated.diagnostics.length, 1)
  Assert.stringContains(unrelated.diagnostics[0].message, "expected Stream<int>")
}

export function testRejectsCasePatternsIncompatibleWithTheirSubject(): none {
  assertRejected("function describe(value: int): string => case value { \"zero\" -> \"impossible\" _ -> \"number\" }")
  assertRejected("function describe(value: int): string => case value { \"a\"..\"z\" -> \"letter\" _ -> \"number\" }")
  assertRejected("class Cat {}\nclass Dog {}\nfunction describe(value: Cat): string => case value { dog: Dog -> \"dog\" _ -> \"cat\" }")
}

export function testRejectsInvalidNamedConstructionShapes(): none {
  missing := checked("class Point { x: int\ny: int }\npoint := Point { x: 1 }")
  Assert.equal(missing.diagnostics.length, 1)
  Assert.stringContains(missing.diagnostics[0].message, "Missing required field 'y'")

  unknown := checked("class Point { x: int\ny: int }\npoint := Point { x: 1, y: 2, z: 3 }")
  Assert.equal(unknown.diagnostics.length, 1)
  Assert.stringContains(unknown.diagnostics[0].message, "Unknown field 'z'")

  duplicate := checked("class Point { x: int\ny: int }\npoint := Point { x: 1, y: 2, x: 3 }")
  Assert.equal(duplicate.diagnostics.length, 1)
  Assert.stringContains(duplicate.diagnostics[0].message, "Duplicate field 'x'")

  valid := checked("class Point { x: int\ny: int = 2\nkind: \"point\" }\npoint := Point { x: 1 }")
  Assert.equal(valid.diagnostics.length, 0)
}

export function testRejectsReadonlyCollectionMutators(): none {
  readonlyCollections := checked(
    "function mutateArray(values: readonly int[]): none { values.push(1)\nvalues.reserve(4)\nignored := values.pop() }\n" +
    "function mutateMap(values: ReadonlyMap<string, int>): none { values.set(\"one\", 1)\nvalues.delete(\"one\") }",
  )
  Assert.equal(readonlyCollections.diagnostics.length, 5)
  for diagnostic of readonlyCollections.diagnostics { Assert.stringContains(diagnostic.message, "not available on readonly") }

  mutableCollections := checked(
    "function mutateArray(values: int[]): none { values.push(1)\nvalues.reserve(4)\nignored := values.pop() }\n" +
    "function mutateMap(values: Map<string, int>): none { values.set(\"one\", 1)\nvalues.delete(\"one\") }",
  )
  Assert.equal(mutableCollections.diagnostics.length, 0)
}

export function testStringSplitReturnsReadonlyArray(): none {
  accepted := checked(
    "function consume(values: readonly string[]): none {}\n" +
    "function parts(): readonly string[] => \"left,right\".split(\",\")\n" +
    "function main(): none { values := parts()\nconsume(values) }",
  )
  Assert.equal(accepted.diagnostics.length, 0)

  mutation := checked("function main(): none { values := \"left,right\".split(\",\")\nvalues.push(\"extra\") }")
  Assert.equal(mutation.diagnostics.length, 1)
  Assert.equal(mutation.diagnostics[0].message, "Method \"push\" is not available on readonly array")

  mutableReturn := checked("function parts(): string[] => \"left,right\".split(\",\")")
  Assert.equal(mutableReturn.diagnostics.length, 1)
  Assert.equal(mutableReturn.diagnostics[0].message, "Cannot return readonly string[] from function returning string[]")
}

export function testRequiresExhaustiveCaseExpressions(): none {
  enumCase := checked("enum Direction { North, South }\nfunction describe(value: Direction): string => case value { .North -> \"north\" }")
  Assert.equal(enumCase.diagnostics.length, 1)
  Assert.stringContains(enumCase.diagnostics[0].message, "must be exhaustive")

  boolCase := checked("function describe(value: bool): string => case value { true -> \"yes\" }")
  Assert.equal(boolCase.diagnostics.length, 1)
  Assert.stringContains(boolCase.diagnostics[0].message, "must be exhaustive")

  exhaustive := checked(
    "enum Direction { North, South }\n" +
    "function direction(value: Direction): string => case value { .North -> \"north\" .South -> \"south\" }\n" +
    "function boolean(value: bool): string => case value { true -> \"yes\" false -> \"no\" }",
  )
  Assert.equal(exhaustive.diagnostics.length, 0)
}

export function testChecksPrimitiveCastInputs(): none {
  invalid := checked("function cast(): int => int(\"42\")")
  Assert.equal(invalid.diagnostics.length, 1)
  Assert.stringContains(invalid.diagnostics[0].message, "expected")

  valid := checked(
    "function casts(): none { b := byte(1)\ni := int('A')\nl := long(i)\nf := float(l)\nd := double(f)\n" +
    "s := string(d)\nok := bool(true) }",
  )
  Assert.equal(valid.diagnostics.length, 0)
}

export function testRejectsStaticMemberAccessThroughInstances(): none {
  invalid := checked("class Counter { static count: int = 0 }\nfunction main(): none { counter := Counter {}\nvalue := counter.count }")
  Assert.equal(invalid.diagnostics.length, 1)
  Assert.stringContains(invalid.diagnostics[0].message, "cannot be accessed through an instance")

  valid := checked("class Counter { static count: int = 0\nvalue: int = 1 }\nfunction main(): none { staticValue := Counter.count\ncounter := Counter {}\ninstanceValue := counter.value }")
  Assert.equal(valid.diagnostics.length, 0)
}

export function testRejectsInstanceMemberAccessThroughClasses(): none {
  result := checked("class Item { value: int\nread(): int => this.value }\nfunction main(): none { first := Item.value\nsecond := Item.read() }")
  Assert.equal(result.diagnostics.length, 2)
  Assert.stringContains(result.diagnostics[0].message, "Instance member 'value'")
  Assert.stringContains(result.diagnostics[1].message, "Instance member 'read'")
}

export function testRejectsDuplicateLocalAndParameterBindings(): none {
  locals := checked("function run(): none { value := 1\nvalue := 2 }")
  Assert.equal(locals.diagnostics.length, 1)
  Assert.equal(locals.diagnostics[0].message, "Binding 'value' is already declared in this scope")

  parameters := checked("function run(value: int, value: string): none {}")
  Assert.equal(parameters.diagnostics.length, 1)
  Assert.equal(parameters.diagnostics[0].message, "Binding 'value' is already declared in this scope")

  lambdaParameters := checked("function run(callback: (value: int): int): none { ignored := (value: int, value: int): int => value }")
  Assert.equal(lambdaParameters.diagnostics.length, 1)
  Assert.equal(lambdaParameters.diagnostics[0].message, "Binding 'value' is already declared in this scope")
}

export function testChecksDiscardTargetsWithoutDeclaringBindings(): none {
  result := checked(
    "class Guard {}\n" +
    "function apply(callback: (value: int, label: string): int): int => callback(1, \"ok\")\n" +
    "function main(): int { let total = 0\n" +
    "for _, value of [(1, 2), (3, 4)] { total += value }\n" +
    "with _ := Guard {}, _ := Guard {} { total += 1 }\n" +
    "return total + apply((_, _): int => 1) }",
  )
  Assert.equal(result.diagnostics.length, 0)

  rejectedResult := checked(
    "function acquire(): Result<int, string> => Success { value: 1 }\n" +
    "function main(): none { with _ := acquire() { } }",
  )
  Assert.equal(rejectedResult.diagnostics.length, 1)
  Assert.stringContains(rejectedResult.diagnostics[0].message, "cannot discard a Result")
}

export function testRejectsRuntimeUseOfTypeOnlyAndTypeSymbols(): none {
  typeOnly := checkedSources([
    SourceFile { path: "/main.do", source: "import type { User } from \"./types\"\nfunction main(): none { ignored := User {} }" },
    SourceFile { path: "/types.do", source: "export class User {}" },
  ], "/main.do")
  Assert.equal(typeOnly.diagnostics.length, 1)
  Assert.equal(typeOnly.diagnostics[0].message, "Type-only import 'User' cannot be used as a value")

  aliasValue := checkedSources([
    SourceFile { path: "/main.do", source: "import { Identifier } from \"./types\"\nfunction value(): Identifier => Identifier" },
    SourceFile { path: "/types.do", source: "export type Identifier = int" },
  ], "/main.do")
  Assert.equal(aliasValue.diagnostics.length, 1)
  Assert.equal(aliasValue.diagnostics[0].message, "Type 'Identifier' cannot be used as a value")

  namespaceValue := checkedSources([
    SourceFile { path: "/main.do", source: "import type * as types from \"./types\"\nfunction main(): none { ignored := types.value }" },
    SourceFile { path: "/types.do", source: "export readonly value = 1" },
  ], "/main.do")
  Assert.equal(namespaceValue.diagnostics.length, 1)
  Assert.equal(namespaceValue.diagnostics[0].message, "Type-only namespace import 'types' cannot be used as a value")
}

export function testRejectsInvalidNominalAndScalarTypeArguments(): none {
  result := checked(
    "class Box<T> { value: T }\n" +
    "interface Marker<T> {}\n" +
    "function missingClass(value: Box): none {}\n" +
    "function extraClass(value: Box<int, string>): none {}\n" +
    "function missingInterface(value: Marker): none {}\n" +
    "function extraInterface(value: Marker<int, string>): none {}\n" +
    "function scalar(value: int<string>): none {}",
  )
  Assert.equal(result.diagnostics.length, 5)
  Assert.equal(result.diagnostics[0].message, "Box requires 1 type argument; received 0")
  Assert.equal(result.diagnostics[1].message, "Box requires 1 type argument; received 2")
  Assert.equal(result.diagnostics[2].message, "Marker requires 1 type argument; received 0")
  Assert.equal(result.diagnostics[3].message, "Marker requires 1 type argument; received 2")
  Assert.equal(result.diagnostics[4].message, "int does not accept type arguments")
}

export function testRejectsDuplicateGenericTypeParameters(): none {
  function_ := checked("function pick<T, T>(first: T, second: T): T => first")
  Assert.equal(function_.diagnostics.length, 1)
  Assert.stringContains(function_.diagnostics[0].message, "Type parameter \"T\" is already declared")

  method := checked("class Picker { pick<T, T>(first: T, second: T): T => first }")
  Assert.equal(method.diagnostics.length, 1)
  Assert.stringContains(method.diagnostics[0].message, "Type parameter \"T\" is already declared")

  class_ := checked("class Pair<T, T> { first: T }")
  Assert.equal(class_.diagnostics.length, 1)
  Assert.stringContains(class_.diagnostics[0].message, "Type parameter \"T\" is already declared")

  struct_ := checked("struct Pair<T, T> { first: T }")
  Assert.equal(struct_.diagnostics.length, 1)
  Assert.stringContains(struct_.diagnostics[0].message, "Type parameter \"T\" is already declared")

  interface_ := checked("interface Pair<T, T> { first: T }")
  Assert.equal(interface_.diagnostics.length, 1)
  Assert.stringContains(interface_.diagnostics[0].message, "Type parameter \"T\" is already declared")

  alias := checked("type Pair<T, T> = Tuple<T, T>")
  Assert.equal(alias.diagnostics.length, 1)
  Assert.stringContains(alias.diagnostics[0].message, "Type parameter \"T\" is already declared")

  shadowedMethod := checked("class Box<T> { map<T>(value: T): T => value }")
  Assert.equal(shadowedMethod.diagnostics.length, 1)
  Assert.stringContains(shadowedMethod.diagnostics[0].message, "shadows a type parameter from the enclosing declaration")

}

export function testReportsNestedUnknownTypesWithSourceDiagnostic(): none {
  result := checked("function main(): none { function consume(value: MissingType): none {} }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Unknown type 'MissingType'")
}

export function testChecksNativeEntryScriptScopeAndArguments(): none {
  result := checkedEntry("let count = arguments.length\nfunction current(): int => count\ncount = count + 1\nprintln(string(current()))")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)

  conflict := checkedEntry("arguments := [\"shadow\"]\nprintln(arguments[0])")
  Assert.equal(conflict.diagnostics.length > 0, true)
  Assert.stringContains(conflict.diagnostics[0].message, "reserved")
}

export function testChecksNativeEntryTryAsPanicAndRejectsExports(): none {
  valid := checkedEntry("function load(): Result<int, string> => Success { value: 4 }\ntry value := load()\nprintln(string(value))")
  Assert.equal(valid.diagnostics.length, 0)

  exported := checkedEntry("export function helper(): int => 1\nprintln(string(helper()))")
  Assert.equal(exported.diagnostics.length, 1)
  Assert.stringContains(exported.diagnostics[0].message, "cannot export")
}

export function testRejectsExecutableStatementsForWasmAndReferenceModules(): none {
  wasm := checkedEntry("export function add(a: int, b: int): int => a + b\nprintln(\"ready\")", "wasm")
  Assert.equal(wasm.diagnostics.length, 1)
  Assert.stringContains(wasm.diagnostics[0].message, "WebAssembly entry modules")

  sources := [
    SourceFile { path: "/main.do", source: "import { value } from \"./lib\"\nfunction main(): int => value" },
    SourceFile { path: "/lib.do", source: "export readonly value = 1\nprintln(\"bad\")" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checker := createChecker(analysis, "/main.do", "executable")
  dependency := checker.check("/lib.do")
  Assert.equal(dependency.diagnostics.length, 1)
  Assert.stringContains(dependency.diagnostics[0].message, "only allowed in a native entry module")
}

export function testRejectsModuleLetFromIsolatedFunctions(): none {
  result := checked("let count = 0\nisolated function read(): int => count")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "mutable module binding")
}

export function testAcceptsLiteralTreeModuleInitializers(): none {
  result := checked(
    "class Config { name: string\nvalues: int[] }\n" +
    "readonly label = \"ready\"\n" +
    "readonly values = [2, 3, 5, 7]\n" +
    "readonly config = Config { name: \"demo\", values: [1, 2] }\n" +
    "class Globals { static message = \"hello\" }",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsExecutableModuleInitializers(): none {
  call := checked("function load(): string => \"ready\"\nreadonly value = load()")
  Assert.equal(call.diagnostics.length, 1)
  Assert.stringContains(call.diagnostics[0].message, "must be a literal tree")

  interpolation := checked("readonly value = \"value: \${1}\"")
  Assert.equal(interpolation.diagnostics.length, 1)
  Assert.stringContains(interpolation.diagnostics[0].message, "must be a literal tree")

  staticCall := checked("function load(): string => \"ready\"\nclass Globals { static value = load() }")
  Assert.equal(staticCall.diagnostics.length, 1)
  Assert.stringContains(staticCall.diagnostics[0].message, "Static field initializer")

  customConstructor := checked(
    "struct Value { number: int\nstatic constructor(number: int): Value => Value { number }\n" +
    "static zero = Value(0) }",
  )
  Assert.equal(customConstructor.diagnostics.length, 1)
  Assert.stringContains(customConstructor.diagnostics[0].message, "must be a literal tree")
}

export function testChecksStringInterpolationRepresentations(): none {
  supported := checked("enum State { Ready }\nfunction render(value: int | none): string => \"value=\${value}, values=\${[1, 2]}, state=\${State.Ready}\"")
  Assert.equal(supported.diagnostics.length, 0)

  callback := checked("function render(fn: (value: int): int): string => \"fn=\${fn}\"")
  Assert.equal(callback.diagnostics.length, 1)
  Assert.stringContains(callback.diagnostics[0].message, "cannot be used in string interpolation")

  classValue := checked("class Point { x: int }\nfunction render(point: Point): string => \"point=\${point}\"")
  Assert.equal(classValue.diagnostics.length, 1)
  Assert.stringContains(classValue.diagnostics[0].message, "Type \"Point\" cannot be used in string interpolation")

  constrained := checked("function render<T: int | string>(value: T): string => \"value=\${value}\"")
  Assert.equal(constrained.diagnostics.length, 0)

  unconstrained := checked("function render<T>(value: T): string => \"value=\${value}\"")
  Assert.equal(unconstrained.diagnostics.length, 1)
  Assert.stringContains(unconstrained.diagnostics[0].message, "cannot be used in string interpolation")
}

export function testAcceptsStructModuleAndStaticInitializers(): none {
  result := checked(
    "struct Point { x: int\ny: int\n" +
    "static zero = Point { x: 0, y: 0 }\n" +
    "static left = Point { x: -1, y: 0 } }\n" +
    "struct Color { r: double\ng: double\nb: double\na: double = 1.0\n" +
    "static black = Color(0.0, 0.0, 0.0) }\n" +
    "readonly origin = Point { x: 0, y: 0 }",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testAcceptsPureModuleConstantExpressions(): none {
  result := checkedSources([
    SourceFile {
      path: "/main.do",
      source: "import { PI } from \"./math\"\nreadonly TAU = PI * 2.0\nreadonly text = \"a\" + \"b\"",
    },
    SourceFile { path: "/math.do", source: "export readonly PI = 3.141592653589793" },
  ], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)

  dynamicRead := checkedSources([
    SourceFile {
      path: "/main.do",
      source: "import { label } from \"./values\"\nreadonly copied = label",
    },
    SourceFile { path: "/values.do", source: "export readonly label = \"a\" + \"b\"" },
  ], "/main.do")
  Assert.equal(dynamicRead.diagnostics.length, 1)
  Assert.stringContains(dynamicRead.diagnostics[0].message, "must be a literal tree")
}

export function testRejectsDependencySensitiveCallInitializer(): none {
  result := checkedSources([
    SourceFile { path: "/main.do", source: "import { combined } from \"./b\"\nfunction main(): int => combined.length" },
    SourceFile { path: "/a.do", source: "readonly value = \"ready\"\nexport function getValue(): string => value" },
    SourceFile { path: "/b.do", source: "import { getValue } from \"./a\"\nexport readonly combined = getValue()" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "must be a literal tree")
}

function checkedSources(sources: SourceFile[], entry: string): CheckResult {
  analysis := createAnalyzer(sources).analyze(entry)
  checker := createChecker(analysis, entry)
  let diagnostics: Diagnostic[] = []
  for i of 0..<analysis.modules.length {
    module := analysis.modules[analysis.modules.length - 1 - i]
    checkedModule := checker.check(module.path)
    for diagnostic of checkedModule.diagnostics { diagnostics.push(diagnostic) }
  }
  for diagnostic of validateDeepReadonlyFields(analysis) { diagnostics.push(diagnostic) }
  for diagnostic of validateIsolationEffects(analysis) { diagnostics.push(diagnostic) }
  return CheckResult { diagnostics }
}

export function testResolvesInferredStaticFieldsAcrossCircularImports(): none {
  result := checkedSources([
    SourceFile {
      path: "/transform.do",
      source:
        "import { Point } from \"./render\"\n" +
        "export struct Vec {\n" +
        "  readonly x: double\n" +
        "  static readonly up = Vec { x: 1.0 }\n" +
        "  static fromPoint(point: Point): Vec => Vec { x: point.x }\n" +
        "}\n",
    },
    SourceFile {
      path: "/render.do",
      source:
        "import { Vec } from \"./transform\"\n" +
        "export struct Point { readonly x: double }\n" +
        "export function direction(point: Point): Vec {\n" +
        "  ignored := Vec.fromPoint(point)\n" +
        "  return Vec.up\n" +
        "}\n",
    },
  ], "/transform.do")

  Assert.equal(result.diagnostics.length, 0)
}

export function testWarnsForLegacyNoneAliasesWithReplacementAndExactSpans(): none {
  voidAlias := checkedIncludingDeprecations("function legacy(): void {}")
  Assert.equal(voidAlias.diagnostics.length, 1)
  Assert.equal(voidAlias.diagnostics[0].severity, "warning")
  Assert.equal(voidAlias.diagnostics[0].message, "'void' is deprecated; replace it with 'none'")
  Assert.equal(voidAlias.diagnostics[0].replacement, "none")
  Assert.equal(voidAlias.diagnostics[0].span.start.line, 1)
  Assert.equal(voidAlias.diagnostics[0].span.start.column, 20)
  Assert.equal(voidAlias.diagnostics[0].span.end.column, 24)

  nullTypeAlias := checkedIncludingDeprecations("value: string | null := none\nprintln(\"\")")
  Assert.equal(nullTypeAlias.diagnostics.length, 1)
  Assert.equal(nullTypeAlias.diagnostics[0].message, "'null' is deprecated; replace it with 'none'")
  Assert.equal(nullTypeAlias.diagnostics[0].replacement, "none")
  Assert.equal(nullTypeAlias.diagnostics[0].span.start.column, 17)
  Assert.equal(nullTypeAlias.diagnostics[0].span.end.column, 21)

  nullLiteralAlias := checkedIncludingDeprecations("value := null")
  Assert.equal(nullLiteralAlias.diagnostics.length, 1)
  Assert.equal(nullLiteralAlias.diagnostics[0].message, "'null' is deprecated; replace it with 'none'")
  Assert.equal(nullLiteralAlias.diagnostics[0].replacement, "none")
  Assert.equal(nullLiteralAlias.diagnostics[0].span.start.column, 10)
  Assert.equal(nullLiteralAlias.diagnostics[0].span.end.column, 14)
}

export function testInfersExpressionsAndCalls(): none {
  source := "values: int[] := [1, 2, 3]\nfunction main(): int { total := values.length\nreturn total }"
  sources := [SourceFile { path: "/main.do", source }]
  analysis := createAnalyzer(sources).analyze("/main.do")
  semantic := createChecker(analysis).check("/main.do")
  Assert.equal(semantic.diagnostics.length, 0)
  case analysis.modules[0].program.statements[0] {
    binding: ImmutableBinding -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "int[]") }
    _ -> { panic("expected an immutable binding") }
  }
}

export function testChecksNoneComparisonOperands(): none {
  resultEquality := checked("function load(): Result<int, string> => Success(1)\nfunction main(): bool => load() == none")
  Assert.equal(resultEquality.diagnostics.length, 1)
  Assert.stringContains(resultEquality.diagnostics[0].message, "Operator '==' is not defined for Result<int, string> and none")

  resultInequality := checked("function load(): Result<int, string> => Success(1)\nfunction main(): bool => none != load()")
  Assert.equal(resultInequality.diagnostics.length, 1)
  Assert.stringContains(resultInequality.diagnostics[0].message, "Operator '!=' is not defined for none and Result<int, string>")

  nonNullableUnion := checked("function present(value: int | string): bool => value != none")
  Assert.equal(nonNullableUnion.diagnostics.length, 1)
  Assert.stringContains(nonNullableUnion.diagnostics[0].message, "is not defined for int | string and none")

  generic := checked("function present<T>(value: T): bool => value != none")
  Assert.equal(generic.diagnostics.length, 1)
  Assert.stringContains(generic.diagnostics[0].message, "is not defined for T and none")

  nullable := checked("class Box {}\nfunction hasBox(value: Box | none): bool => value != none\nfunction hasScalar(value: int | none): bool => none != value\nfunction isJsonNull(value: JsonValue): bool => value == none")
  Assert.equal(nullable.diagnostics.length, 0)
}

export function testPreservesCallableFieldDecorationThroughNullableReceiver(): none {
  source := "struct Handler { callback: (value: int): int }\nfunction findHandler(): Handler | none => Handler { callback: (value: int): int => value + 1 }\nfunction invoke(): int { handler := findHandler()\nif handler != none { return handler!.callback(41) }\nreturn 0 }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  semantic := createChecker(analysis).check("/main.do")
  Assert.equal(semantic.diagnostics.length, 0)
  case analysis.modules[0].program.statements[2] {
    function_: FunctionDeclaration -> { case function_.body {
      body: Block -> { case body.statements[1] {
        if_: IfStatement -> { case if_.body.statements[0] {
          return_: ReturnStatement -> { case return_.value! {
            call: CallExpression -> { case call.callee {
              member: MemberExpression -> { Assert.equal(member.resolvedCallableField, true) }
              _ -> { panic("expected callback member") }
            } }
            _ -> { panic("expected callback call") }
          } }
          _ -> { panic("expected return") }
        } }
        _ -> { panic("expected if") }
      } }
      _ -> { panic("expected function body") }
    } }
    _ -> { panic("expected invoke function") }
  }
}

export function testChecksWeakTypesAndStructRestrictions(): none {
  source := "class Node { weak parent: Node\nancestor: weak Node }\nfunction keep(value: weak Node): weak Node => value"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  semantic := createChecker(analysis).check("/main.do")
  Assert.equal(semantic.diagnostics.length, 0)
  case analysis.modules[0].program.statements[0] {
    class_: ClassDeclaration -> {
      Assert.equal(typeName(class_.fields[0].resolvedType ?? unknownType()), "weak Node")
      Assert.equal(typeName(class_.fields[1].resolvedType ?? unknownType()), "weak Node")
    }
    _ -> { panic("expected class") }
  }

  invalid := checked("class Node {}\nstruct Links { weak parent: Node\nancestor: weak Node }")
  Assert.equal(invalid.diagnostics.length, 2)
  Assert.equal(invalid.diagnostics[0].message.contains("cannot be weak"), true)
  Assert.equal(invalid.diagnostics[1].message.contains("cannot be weak"), true)
}

export function testDoesNotExposeWeakFieldsAsStrongValues(): none {
  result := checked("class Node { weak parent: Node\nstrongParent(): Node => parent }")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "Cannot return weak Node from function returning Node")

  construction := checked("class Node {}\nclass Link { weak parent: Node }\nclass Registry { weak nodes: Node[]\nweak optional: Node | none = none }\nfunction main(): none { parent := Node {}\nlink := Link(parent)\nregistry := Registry([parent]) }")
  Assert.equal(construction.diagnostics.length, 0)
}

export function testRejectsGeneratedJsonForWeakFields(): none {
  modifier := checked("class Node { weak parent: Node }\nfunction encode(value: Node): JsonValue => value.toJsonObject()")
  Assert.equal(modifier.diagnostics.length > 0, true)
  Assert.equal(modifier.diagnostics[0].message.contains("does not support automatic JSON serialization"), true)

  qualifier := checked("class Node { parent: weak Node }\nfunction encode(value: Node): JsonValue => value.toJsonObject()")
  Assert.equal(qualifier.diagnostics.length > 0, true)
  Assert.equal(qualifier.diagnostics[0].message.contains("does not support automatic JSON serialization"), true)
}

export function testChecksArrayAndStringSearchMembers(): none {
  result := checked("function main(): int { values := [1, 2, 3]\ntext := \"hello\"\nif values.contains(2) && text.contains(\"ell\") { return values.indexOf(3) + text.indexOf(\"e\") }\nreturn 0 }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksTrimStartAssignmentInsideConditional(): none {
  result := checked("function normalize(value: string, shouldTrim: bool): string { let result = value\nif shouldTrim { result = result.trimStart() }\nreturn result }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksStringPaddingMethods(): none {
  result := checked("function padded(value: string): string => value.padStart(4) + value.padEnd(4, '" + codePointToUtf8(233) + "')")
  Assert.equal(result.diagnostics.length, 0)

  invalid := checked("function padded(value: string): string => value.padEnd(4, \"x\")")
  Assert.equal(invalid.diagnostics.length, 1)
  Assert.stringContains(invalid.diagnostics[0].message, "expected char")
}

export function testReportsUnknownMembersAcrossResolvedTypes(): none {
  stringResult := checked("function bad(value: string): string => value.missing()")
  Assert.equal(stringResult.diagnostics.length, 1)
  Assert.equal(stringResult.diagnostics[0].message, "Type \"string\" has no member \"missing\"")

  arrayResult := checked("function bad(value: int[]): int => value.missing()")
  Assert.equal(arrayResult.diagnostics.length, 1)
  Assert.equal(arrayResult.diagnostics[0].message, "Type \"int[]\" has no member \"missing\"")

  classResult := checked("class Widget {}\nfunction bad(value: Widget): int => value.missing")
  Assert.equal(classResult.diagnostics.length, 1)
  Assert.equal(classResult.diagnostics[0].message, "Type \"Widget\" has no member \"missing\"")

  interfaceResult := checked("interface Drawable { render(): int }\nfunction bad(value: Drawable): int => value.missing()")
  Assert.equal(interfaceResult.diagnostics.length, 2)
  Assert.equal(interfaceResult.diagnostics[0].message, "Type \"Drawable\" has no member \"missing\"")

  builtinCallableResult := checked("function bad(): int => int.missing(1)")
  Assert.equal(builtinCallableResult.diagnostics.length, 1)
  Assert.equal(builtinCallableResult.diagnostics[0].message, "Type \"function\" has no member \"missing\"")
}

export function testReportsUnknownImportedNamespaceMember(): none {
  result := checkedSources([
    SourceFile { path: "/main.do", source: "import * as tools from \"./tools\"\nfunction bad(): int => tools.missing()" },
    SourceFile { path: "/tools.do", source: "export function present(): int => 1" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Namespace \"tools\" has no member \"missing\"")
}

export function testDecoratesImportedNamespaceMemberWithResolvedSymbol(): none {
  analysis := createAnalyzer([
    SourceFile { path: "/main.do", source: "import * as tools from \"./tools\"\nfunction value(): int => tools.present()" },
    SourceFile { path: "/tools.do", source: "export function present(): int => 1" },
  ]).analyze("/main.do")
  checker := createChecker(analysis)
  Assert.equal(checker.check("/tools.do").diagnostics.length, 0)
  Assert.equal(checker.check("/main.do").diagnostics.length, 0)
  case analysis.modules[0].program.statements[1] {
    fn: FunctionDeclaration -> { case fn.body {
      call: CallExpression -> { case call.callee {
        member: MemberExpression -> {
          Assert.equal(member.resolvedNamespaceAccess, true)
          Assert.equal(member.resolvedNamespaceSymbol!.name, "present")
          Assert.equal(member.resolvedNamespaceSymbol!.module, "/tools.do")
          member.resolvedNamespaceSymbol = none
        }
        _ -> { panic("expected namespace member") }
      } }
      _ -> { panic("expected call") }
    } }
    _ -> { panic("expected function") }
  }
  diagnostics := validateCheckedTypes(analysis)
  Assert.equal(diagnostics.length, 1)
  Assert.stringContains(diagnostics[0].message, "has no resolved symbol")
}

export function testDecoratesNamespaceGenericCallWithDefiningModule(): none {
  analysis := createAnalyzer([
    SourceFile { path: "/main.do", source: "import * as tools from \"./tools\"\nfunction value(): int => tools.identity<int>(1)" },
    SourceFile { path: "/tools.do", source: "export function identity<T>(value: T): T => value" },
  ]).analyze("/main.do")
  checker := createChecker(analysis)
  Assert.equal(checker.check("/tools.do").diagnostics.length, 0)
  Assert.equal(checker.check("/main.do").diagnostics.length, 0)
  case analysis.modules[0].program.statements[1] {
    fn: FunctionDeclaration -> { case fn.body {
      call: CallExpression -> {
        Assert.equal(call.resolvedFunction != none, true)
        Assert.equal(call.resolvedFunction!.name, "identity")
        Assert.equal(call.resolvedFunctionModule, "/tools.do")
        call.resolvedFunctionModule = ""
      }
      _ -> { panic("expected generic call") }
    } }
    _ -> { panic("expected function") }
  }
  diagnostics := validateCheckedTypes(analysis)
  Assert.equal(diagnostics.length, 1)
  Assert.stringContains(diagnostics[0].message, "no defining module")
}

export function testChecksGenericClassesAgainstConcreteStructuralInterfaces(): none {
  result := checked(
    "interface Reader<T> { readonly value: T\nread(): T }\n" +
    "class Box<T> { readonly value: T\nread(): T => value }\n" +
    "class Base {}\nclass Derived {}\n" +
    "interface Factory { make(): Base | Derived }\n" +
    "class DerivedFactory { make(): Derived => Derived {} }\n" +
    "function consume(reader: Reader<int>): int => reader.read()\n" +
    "function produce(factory: Factory): Base | Derived => factory.make()\n" +
    "function main(): int { reader: Reader<int> := Box<int> { value: 7 }\n" +
    "consume(Box<int> { value: reader.read() })\n" +
    "produce(DerivedFactory {})\nreturn reader.read() }",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testUnresolvedInferredFieldsFailConformanceWithoutPanicking(): none {
  result := checked(
    "shared := \"text\"\n" +
    "interface HasInt { readonly value: int }\n" +
    "class Inferred { readonly value = shared }\n" +
    "function consume(value: HasInt): none {}\n" +
    "function main(): none { consume(Inferred {}) }",
  )
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.stringContains(result.diagnostics[0].message, "expected HasInt")
}

export function testValueBindingsShadowBuiltinConversionNames(): none {
  result := checked("class Parser { parse(value: string): int => value.length }\nfunction read(): int { byte := Parser {}\nreturn byte.parse(\"ok\") }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testFunctionBindingsShadowIntrinsicConstructorNames(): none {
  result := checked("function Success(value: int): int => value + 1\nfunction Failure(value: int): int => value + 2\nfunction main(): int => Success(1) + Failure(2)")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRequiresMembersOnEveryPresentUnionType(): none {
  result := checked("class Named { name: string }\nclass Counted { count: int }\nfunction bad(value: Named | Counted): string => value.name")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Type \"Named | Counted\" has no member \"name\"")
}

export function testChecksRangeValuesSignaturesAndMembers(): none {
  result := checked("function first(values: Range): int { for value of values { return value }\nreturn values.lowerBound + values.upperBound }\nfunction main(): int => first(1..<4)")
  Assert.equal(result.diagnostics.length, 0)
}

export function testResolvesImportedRangeSignatures(): none {
  result := checkedSources([
    SourceFile { path: "/main.do", source: "import { first } from \"./range\"\nfunction main(): int => first(1..3)" },
    SourceFile { path: "/range.do", source: "export function first(values: int | Range): int => 1" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsUnsupportedRangeBounds(): none {
  result := checked("function main(): void { floatRange := 1.0..3.0\nlongRange := 1L..<3L }")
  Assert.equal(result.diagnostics.length, 4)
  Assert.equal(result.diagnostics[0].message.contains("requires integer bounds"), true)
  Assert.equal(result.diagnostics[2].message.contains("currently requires int-compatible bounds"), true)
}

export function testChecksFiniteAndOpenEndedCaseRangePatterns(): none {
  result := checked("function category(value: int): string => case value { ..<0 -> \"negative\", 0..<10 -> \"small\", 10..20 -> \"medium\", 21.. -> \"large\" }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testArrayPopReturnsResult(): none {
  valid := checked("function take(values: int[]): Result<int, string> => values.pop()")
  Assert.equal(valid.diagnostics.length, 0)

  ignored := checked("function take(values: int[]): void { values.pop() }")
  Assert.equal(ignored.diagnostics.length, 1)
  Assert.equal(ignored.diagnostics[0].message.contains("Result value must be handled"), true)
}

export function testDecoratesArrayCloneMutableAndEnumLookupHelpers(): none {
  source := "enum Suit { Spades = 0, Hearts = 1 }\nclass Pile { cardIndices: int[] = [] }\nfunction clonePile(pile: Pile): Pile { return Pile { cardIndices: pile.cardIndices.cloneMutable() } }\nfunction foundationSuit(index: int): Suit { return Suit.fromValue(index) ?? .Spades }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  diagnostics := validateCheckedTypes(analysis)
  for diagnostic of diagnostics { println(diagnostic.message) }
  Assert.equal(diagnostics.length, 0)
}

export function testDecoratesReadonlyMapConstructionAndSizeMember(): none {
  source := "class RouteMatch { params: readonly Map<string, string> }\nfunction equal<T>(actual: T, expected: T): none {}\nfunction match(params: Map<string, string>): RouteMatch { return RouteMatch { params: params.drainToReadonly() } }\nfunction verify(matched: RouteMatch | none): none { equal(matched!.params.size, 0) }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  diagnostics := validateCheckedTypes(analysis)
  for diagnostic of diagnostics { println(diagnostic.message) }
  Assert.equal(diagnostics.length, 0)
}

export function testCompleteDecorationGateRejectsMissingWithBindingType(): none {
  source := "function main(): int { with base := 20 { return base }\nreturn 0 }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  case analysis.modules[0].program.statements[0] {
    fn: FunctionDeclaration -> {
      case fn.body {
        block: Block -> {
          case block.statements[0] {
            with_: WithStatement -> { with_.bindings[0].resolvedType = none }
            _ -> { panic("expected a with statement") }
          }
        }
        _ -> { panic("expected a block function") }
      }
    }
    _ -> { panic("expected a function") }
  }
  diagnostics := validateCheckedTypes(analysis)
  Assert.equal(diagnostics.length, 1)
  Assert.equal(diagnostics[0].message.contains("Missing resolved type for with binding base"), true)
}

export function testCompleteDecorationGateTraversesAsSourceAndTarget(): none {
  source := "function narrow(raw: JsonValue): Result<string, string> => raw as string"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  case analysis.modules[0].program.statements[0] {
    fn: FunctionDeclaration -> {
      case fn.body {
        expression: Expression -> {
          case expression {
            as_: AsExpression -> {
              as_.expression.resolvedType = none
              as_.targetType.resolvedType = none
            }
            _ -> { panic("expected an as expression") }
          }
        }
        _ -> { panic("expected an expression function") }
      }
    }
    _ -> { panic("expected a function") }
  }
  diagnostics := validateCheckedTypes(analysis)
  Assert.equal(diagnostics.length, 2)
  Assert.equal(diagnostics[0].message.contains("Missing resolved type for expression identifier"), true)
  Assert.equal(diagnostics[1].message.contains("Missing resolved type for type annotation"), true)
}

export function testCompleteDecorationGateRequiresConstructionAttachments(): none {
  source := "class Widget { value: int\nstatic constructor(value: int): Widget => Widget { value } }\nwidget := Widget { value: 1 }\nprintln(\"\")"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis, "/main.do").check("/main.do").diagnostics.length, 0)
  case analysis.modules[0].program.statements[1] {
    binding: ImmutableBinding -> {
      case binding.value {
        construct: ConstructExpression -> {
          constructedType := construct.resolvedConstructedType
          construct.resolvedConstructedType = none
          missingType := validateCheckedTypes(analysis)
          Assert.equal(missingType.length, 1)
          Assert.equal(missingType[0].message.contains("Missing resolved type for constructed type"), true)
          construct.resolvedConstructedType = constructedType

          resolvedClass := construct.resolvedClass
          construct.resolvedClass = none
          missingClass := validateCheckedTypes(analysis)
          Assert.equal(missingClass.length, 1)
          Assert.equal(missingClass[0].message.contains("has no resolved class"), true)
          construct.resolvedClass = resolvedClass

          construct.resolvedConstructor = none
          missingConstructor := validateCheckedTypes(analysis)
          Assert.equal(missingConstructor.length, 1)
          Assert.equal(missingConstructor[0].message.contains("has no resolved constructor"), true)
        }
        _ -> { panic("expected a construct expression") }
      }
    }
    _ -> { panic("expected an immutable binding") }
  }
}

export function testCompleteDecorationGateRequiresClassObjectLiteralAttachment(): none {
  source := "class Widget { value: int }\nfunction make(): Widget => { value: 1 }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  case analysis.modules[0].program.statements[1] {
    fn: FunctionDeclaration -> {
      case fn.body {
        expression: Expression -> {
          case expression {
            object: ObjectLiteral -> { object.resolvedClass = none }
            _ -> { panic("expected an object literal") }
          }
        }
        _ -> { panic("expected an expression function") }
      }
    }
    _ -> { panic("expected a function") }
  }
  diagnostics := validateCheckedTypes(analysis)
  Assert.equal(diagnostics.length, 1)
  Assert.equal(diagnostics[0].message.contains("Class object literal has no resolved class"), true)
}

export function testDefaultsUnannotatedBlockFunctionReturnToNone(): none {
  source := "export function testAll() { println(\"ok\") }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  Assert.equal(validateCheckedTypes(analysis).length, 0)
  case analysis.modules[0].program.statements[0] {
    fn: FunctionDeclaration -> { case fn.resolvedType! {
      function_: FunctionType -> { Assert.equal(typeName(function_.returnType), "none") }
      _ -> { panic("expected resolved function type") }
    } }
    _ -> { panic("expected function declaration") }
  }
}

export function testResolvesForwardNoneReturningMethodFromInferredMethod(): none {
  source := "class Bucket { record() { insertSorted() }\nprivate insertSorted() {} }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  Assert.equal(validateCheckedTypes(analysis).length, 0)
}

export function testRejectsValueReturnFromUnannotatedFunction(): none {
  result := checked("function answer() { return 42 }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Cannot return int from function returning none")
}

export function testImportedUnannotatedFunctionReturnsNone(): none {
  analysis := createAnalyzer([
    SourceFile { path: "/main.do", source: "import { finish } from \"./worker\"\nfunction main(): none { finish() }" },
    SourceFile { path: "/worker.do", source: "export function finish() {}" },
  ]).analyze("/main.do")
  checker := createChecker(analysis)
  Assert.equal(checker.check("/worker.do").diagnostics.length, 0)
  Assert.equal(checker.check("/main.do").diagnostics.length, 0)
  Assert.equal(validateCheckedTypes(analysis).length, 0)
}

export function testChecksCanonicalNoneReturnsAndLegacyUnionNormalization(): none {
  source := "function fallthrough(): none { }\nfunction bare(): none { return }\nfunction explicit(): none { return none }\nfunction inferred() { return none }\nfunction mixed(value: string | null | void | none): string | none => value"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  diagnostics := createChecker(analysis).check("/main.do").diagnostics
  Assert.equal(diagnostics.length, 2)
  Assert.equal(diagnostics[0].replacement, "none")
  Assert.equal(diagnostics[1].replacement, "none")
  case analysis.modules[0].program.statements[4] {
    fn: FunctionDeclaration -> { case fn.resolvedType! {
      function_: FunctionType -> {
        Assert.equal(typeName(function_.params[0].type_), "string | none")
        Assert.equal(typeName(function_.returnType), "string | none")
      }
      _ -> { panic("expected resolved function type") }
    } }
    _ -> { panic("expected mixed function") }
  }
}

export function testChecksPayloadlessNoneResultAndRejectsTryQuestion(): none {
  valid := checked("function save(): Result<none, string> => Success()\nfunction fail(): Result<int, none> => Failure()\nfunction use(): none { try save() }")
  Assert.equal(valid.diagnostics.length, 0)

  invalid := checked("function save(): Result<none, string> => Success()\nfunction use(): none { value := try? save() }")
  Assert.equal(invalid.diagnostics.length, 1)
  Assert.equal(invalid.diagnostics[0].message.contains("requires a Result with a success value"), true)
}

export function testChecksNamedStaticConstructorAndEnumShorthand(): none {
  source := "enum Endian { LittleEndian, BigEndian }\nimport class BlobBuilder from \"native.hpp\" as native::BlobBuilder { static constructor(size: long = 0L, endianness: Endian = .LittleEndian): BlobBuilder }\nfunction build(): none { builder := BlobBuilder{endianness: .BigEndian} }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  Assert.equal(validateCheckedTypes(analysis).length, 0)
}

export function testContextuallyTypesEnumShorthandInBinaryComparisons(): none {
  result := checked("enum Compression { Store, Deflate }\nfunction stored(compression: Compression): bool => compression == .Store\nfunction deflated(compression: Compression): bool => .Deflate == compression")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsUnresolvedAndMissingDotShorthandMembers(): none {
  missingEnum := checked("enum Direction { North }\nfunction direction(): Direction => .South")
  Assert.equal(missingEnum.diagnostics.length, 1)
  Assert.equal(missingEnum.diagnostics[0].message, "Enum \"Direction\" has no variant \"South\"")

  instanceMember := checked("class Widget { value: int }\nfunction widget(): Widget => .value")
  Assert.equal(instanceMember.diagnostics.length, 1)
  Assert.equal(instanceMember.diagnostics[0].message, "Type \"Widget\" has no static member \"value\"")

  noContext := checked("function test(): none { value := .Missing }")
  Assert.equal(noContext.diagnostics.length, 1)
  Assert.equal(noContext.diagnostics[0].message, "Cannot resolve shorthand .Missing without an expected class or enum type")

}

export function testRejectsRemovedNumericParseIntrinsicsWithMigrationDiagnostic(): none {
  result := checked("function parsed(value: string): int => int.parse(value)!")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "int.parse was removed; import parseInt from \"std/parse\"")
}

export function testChecksBlockBodiedCaseExpressionArms(): none {
  result := checked("function describe(value: int): string => case value { 0 -> { yield \"zero\" } _ -> { if value < 0 { yield \"negative\" }\nyield \"positive\" } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsCaseExpressionBlockThatCanCompleteWithoutYield(): none {
  result := checked("function describe(value: int): string => case value { 0 -> { if value < 0 { yield \"negative\" } } _ -> \"positive\" }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "Block case-expression arms must yield a value on every path")
}

export function testContextuallyTypesShorthandArrayMapLambda(): none {
  result := checked("class Item { value: int }\nfunction values(items: Item[]): int[] => items.map(=> it.value)")
  Assert.equal(result.diagnostics.length, 0)
}

export function testInfersWiderCompatibleGenericArgument(): none {
  result := checked("function equal<T>(actual: T, expected: T): void {}\nfunction compare(value: string | null): void { equal(value, \"ok\") }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testContextuallyTypesDotShorthandDuringGenericCallInference(): none {
  source := "enum EncodingError { InvalidData, UnrepresentableCharacter }\nfunction assertEncodingError<T>(result: Result<T, EncodingError>, expected: EncodingError): none {}\nfunction equal<T>(actual: T, expected: T): none {}\nfunction verify(result: Result<int, EncodingError>, error: EncodingError): none {\nassertEncodingError(result, .InvalidData)\nequal(error, .UnrepresentableCharacter)\nequal(.InvalidData, error)\n}"
  result := checked(source)
  Assert.equal(result.diagnostics.length, 0)
}

export function testWidensIntValuesToDoubleAtTypedBoundaries(): none {
  accepted := checked("function scale(value: double): double => value\nfunction apply(value: double): double => value\nfunction main(): double { count: int := 42\nscaled: double := count\nreturn apply(scale(count)) + scaled }")
  Assert.equal(accepted.diagnostics.length, 0)

  rejected := checked("function apply(value: double): double => value\nfunction main(): double { count: long := 9007199254740993L\nreturn apply(count) }")
  Assert.equal(rejected.diagnostics.length, 1)
  Assert.equal(rejected.diagnostics[0].message, "Argument 1 has type long; expected double")
}

export function testChecksBuiltinSourceLocationAndCallerDefaults(): none {
  result := checked("function debug(source: SourceLocation = @caller): string => source.fileName + string(source.line) + source.functionName")
  Assert.equal(result.diagnostics.length, 0)
}

export function testValidatesStaticGenericMethodsWithCallerDefaults(): none {
  source := "class Assert { static equal<T>(actual: T, expected: T, source: SourceLocation = @caller): void { assert(actual == expected, \"equal\") } }\nfunction test(): void { Assert.equal(1, 1) }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  createChecker(analysis).check("/main.do")
  diagnostics := validateCheckedTypes(analysis)
  for diagnostic of diagnostics { println(diagnostic.message) }
  Assert.equal(diagnostics.length, 0)
}

export function testRejectsMissingRequiredPositionalFunctionArguments(): none {
  result := checked("function combine(first: int, second: string, suffix: string = \"!\"): string => string(first) + second + suffix\nvalue := combine(1)\nprintln(\"\")")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Expected 2-3 argument(s) but got 1")
}

export function testValidatesFieldConstructorPositionalArguments(): none {
  missing := checked("class Config { host: string\nport: int = 8080 }\nconfig := Config()\nprintln(\"\")")
  Assert.equal(missing.diagnostics.length, 1)
  Assert.equal(missing.diagnostics[0].message, "Class \"Config\" expects 1-2 constructor argument(s) but got 0")

  excess := checked("class Point { x, y: int }\npoint := Point(1, 2, 3)\nprintln(\"\")")
  Assert.equal(excess.diagnostics.length, 1)
  Assert.equal(excess.diagnostics[0].message, "Class \"Point\" expects 2 constructor argument(s) but got 3")

  incompatible := checked("class Point { x: int\ny: string }\npoint := Point(1, 2)\nprintln(\"\")")
  Assert.equal(incompatible.diagnostics.length, 1)
  Assert.equal(incompatible.diagnostics[0].message, "Argument 2 has type int; expected string")
}

export function testValidatesDedicatedConstructorPositionalArguments(): none {
  missing := checked("class Widget { value: int\nstatic constructor(value: int, label: string = \"widget\"): Widget => Widget { value } }\nwidget := Widget()\nprintln(\"\")")
  Assert.equal(missing.diagnostics.length, 1)
  Assert.equal(missing.diagnostics[0].message, "Class \"Widget\" expects 1-2 constructor argument(s) but got 0")

  incompatible := checked("class Widget { value: int\nstatic constructor(value: int): Widget => Widget { value } }\nwidget := Widget(\"bad\")\nprintln(\"\")")
  Assert.equal(incompatible.diagnostics.length, 1)
  Assert.equal(incompatible.diagnostics[0].message, "Argument 1 has type string; expected int")
}

export function testValidatesDedicatedConstructorDeclarationShape(): none {
  instance := checked("class Broken { value: int\nconstructor(value: int): Broken => Broken { value } }\nfunction main(): none { Broken(1) }")
  Assert.equal(instance.diagnostics.length, 1)
  Assert.stringContains(instance.diagnostics[0].message, "must be static")

  wrongReturn := checked("class Broken { value: int\nstatic constructor(value: int): int => value }\nfunction main(): none { Broken(1) }")
  Assert.equal(wrongReturn.diagnostics.length, 1)
  Assert.stringContains(wrongReturn.diagnostics[0].message, "must return Broken or Result<Broken, E>")
}

export function testChecksSupportedJsonDeserializationSurface(): none {
  result := checked("class Config { name: string\nenabled: bool\ncount: int = 10\nnotes: string | null = null }\nfunction parse(value: JsonValue): Result<Config, string> => Config.fromJsonValue(value)")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksJsonValueAsNarrowingWithDeclarationElse(): none {
  result := checked("function read(raw: JsonValue): string { flag := raw as bool else { return \"bad\" }\nname := raw as string else { return \"bad\" }\nvalues := raw as readonly JsonValue[] else { return \"bad\" }\nreturn name + string(flag) + string(values.length) }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testAcceptsNullableNaturalRepresentationAsNarrowing(): none {
  result := checked("class Config { value: int }\nfunction config(value: Config | null): Result<Config, string> => value as Config\nfunction items(value: int[] | null): Result<int[], string> => value as int[]\nfunction count(value: int | null): Result<int, string> => value as int")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksExpressionResultElseWithFailureCapture(): none {
  result := checked("function save(): Result<void, string> => Success()\nfunction run(): void { save() else error { println(error) } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testAllowsDeclarationElseContinueAndMutableMapInterior(): none {
  result := checked("function run(values: Map<string, JsonValue>, items: JsonValue[]): void { for item of items { text := item as string else { continue }\nvalues[\"name\"] = text } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testAllowsJsonCollectionsAndLenientGeneratedDecode(): none {
  result := checked("class Options { enabled: bool\nname: string }\nfunction run(value: JsonValue, values: Map<string, JsonValue>, items: JsonValue[]): Result<Options, string> { values[\"items\"] = items\nreturn Options.fromJsonValue(value, true) }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testDecoratesPrivateMethodParameterMembers(): none {
  source := "class Option { readonly name: string\nreadonly multiple: bool }\nclass Spec { option(): none {}\nprivate add(option: Option, values: Map<string, JsonValue>): none { if option.multiple { raw := values.get(option.name) else { values[option.name] = []\nreturn }\nvalues[option.name] = raw } } }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  diagnostics := validateCheckedTypes(analysis)
  for diagnostic of diagnostics { println(diagnostic.message) }
  Assert.equal(diagnostics.length, 0)
}

export function testChecksJsonDeserializationBeforeClassDeclaration(): none {
  result := checked("function parse(value: JsonValue): Result<Config, string> => Config.fromJsonValue(value)\nclass Config { name: string\ncount = 10 }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsJsonDeserializationForUnsupportedFields(): none {
  result := checked("class Handler { callback: (value: int): void }\nfunction parse(value: JsonValue): Result<Handler, string> => Handler.fromJsonValue(value)")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "Type \"Handler\" does not support automatic JSON deserialization")
}

export function testRejectsJsonMethodsForNestedUnsupportedFields(): none {
  decode := checked("class Handler { callback: (value: int): void }\nclass Envelope { handler: Handler }\nfunction parse(value: JsonValue): Result<Envelope, string> => Envelope.fromJsonValue(value)")
  Assert.equal(decode.diagnostics.length > 0, true)
  Assert.equal(decode.diagnostics[0].message, "Type \"Envelope\" does not support automatic JSON deserialization")

  encode := checked("class Handler { callback: (value: int): void }\nclass Envelope { handler: Handler }\nfunction write(value: Envelope): JsonObject => value.toJsonObject()")
  Assert.equal(encode.diagnostics.length > 0, true)
  Assert.equal(encode.diagnostics[0].message, "Type \"Envelope\" does not support automatic JSON serialization")
}

export function testChecksContextualNumericLiteralAssignments(): none {
  result := checked("function update(): double { let value: double = 1.0\nvalue = 2\nreturn value }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksRecursiveAutomaticJsonTypes(): none {
  source := "enum Kind { One, Two }\nclass Point { x: double\ny: double }\nclass Payload { kind: Kind\nids: int[]\npoints: Point[]\nselected: Point | null = null }\nfunction encode(value: Payload): JsonObject => value.toJsonObject()\nfunction decode(value: JsonValue): Result<Payload, string> => Payload.fromJsonValue(value)"
  result := checked(source)
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksTupleAutomaticJsonTypes(): none {
  source := "class Point { x: int\ny: int }\nclass Payload { pair: Tuple<string, int>\npoint: Tuple<Point, bool>\noptional: Tuple<int, string> | null = null }\nfunction encode(value: Payload): JsonObject => value.toJsonObject()\nfunction decode(value: JsonValue): Result<Payload, string> => Payload.fromJsonValue(value)"
  result := checked(source)
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksStringMapAutomaticJsonTypes(): none {
  source := "class Point { x: int\ny: int }\nclass Payload { counts: Map<string, int>\npoints: Map<string, Point> }\nfunction encode(value: Payload): JsonObject => value.toJsonObject()\nfunction decode(value: JsonValue): Result<Payload, string> => Payload.fromJsonValue(value)"
  result := checked(source)
  Assert.equal(result.diagnostics.length, 0)

  invalid := checked("class Payload { values: Map<int, string> }\nfunction decode(value: JsonValue): Result<Payload, string> => Payload.fromJsonValue(value)")
  Assert.equal(invalid.diagnostics.length > 0, true)
  Assert.equal(invalid.diagnostics[0].message, "Type \"Payload\" does not support automatic JSON deserialization")
}

export function testChecksDiscriminatedInterfaceJsonDeserialization(): none {
  valid := checked("interface Shape { area(): double }\nclass Circle implements Shape { const kind = \"circle\"\nradius: double\narea(): double => radius * radius }\nclass Rect implements Shape { const kind = \"rect\"\nwidth: double\nheight: double\narea(): double => width * height }\nfunction decode(value: JsonValue): Result<Shape, string> => Shape.fromJsonValue(value, true)")
  Assert.equal(valid.diagnostics.length, 0)

  invalid := checked("interface Shape { area(): double }\nclass Circle implements Shape { radius: double\narea(): double => radius * radius }\nclass Rect implements Shape { width: double\narea(): double => width }\nfunction decode(value: JsonValue): Result<Shape, string> => Shape.fromJsonValue(value)")
  Assert.equal(invalid.diagnostics.length > 0, true)
  Assert.stringContains(invalid.diagnostics[0].message, "must share a const string field with distinct values")

  duplicate := checked("interface Shape { area(): double }\nclass Circle implements Shape { const kind = \"shape\"\nradius: double\narea(): double => radius }\nclass Rect implements Shape { const kind = \"shape\"\nwidth: double\narea(): double => width }\nfunction decode(value: JsonValue): Result<Shape, string> => Shape.fromJsonValue(value)")
  Assert.equal(duplicate.diagnostics.length > 0, true)
  Assert.stringContains(duplicate.diagnostics[0].message, "distinct values")
}

export function testAcceptsLenientJsonDeserialization(): none {
  result := checked("class Config { name: string }\nfunction parse(value: JsonValue): Result<Config, string> => Config.fromJsonValue(value, true)")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksMetadataSchemaAndInvokeSurface(): none {
  result := checked("class Tool \"A tool.\" { function run \"Runs.\"(input \"Payload.\": string): string => input }\nmetadata := Tool.metadata\nname := metadata.name\nmethods := metadata.methods\ninvoked := metadata.invoke(Tool {}, \"run\", { input: \"ok\" })\nmethodInvoked := methods[0].invoke(Tool {}, { input: \"ok\" })\nprintln(\"\")")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksMetadataOnReflectableTypeParameter(): none {
  result := checked("function describe<T: Reflectable>(tool: T): string => T.metadata.name")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsMetadataOnUnconstrainedTypeParameter(): none {
  result := checked("function describe<T>(tool: T): string => T.metadata.name")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("constrained by Reflectable"), true)
}

export function testRejectsNonClassReflectableTypeArgument(): none {
  result := checked("function describe<T: Reflectable>(tool: T): string => T.metadata.name\nname := describe<int>(1)")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("does not satisfy constraint \"Reflectable\""), true)
}

export function testEnforcesOrdinaryGenericFunctionConstraints(): none {
  valid := checked("function keep<T: int | long>(value: T): T => value\nfirst := keep<int>(1)\nsecond := keep(2L)\nprintln(\"\")")
  Assert.equal(valid.diagnostics.length, 0)

  explicitInvalid := checked("function keep<T: int | long>(value: T): T => value\nvalue := keep<string>(\"no\")\nprintln(\"\")")
  Assert.equal(explicitInvalid.diagnostics.length, 1)
  Assert.equal(explicitInvalid.diagnostics[0].message.contains("does not satisfy constraint \"int | long\""), true)

  inferredInvalid := checked("function keep<T: int | long>(value: T): T => value\nvalue := keep(\"no\")\nprintln(\"\")")
  Assert.equal(inferredInvalid.diagnostics.length, 1)
  Assert.equal(inferredInvalid.diagnostics[0].message.contains("does not satisfy constraint \"int | long\""), true)
}

export function testEnforcesOrdinaryGenericNominalAndAliasConstraints(): none {
  valid := checked("class Box<T: int | long> { value: T }\ntype NumberBox<T: int | long> = Box<T>\nbox: NumberBox<long> := Box<long> { value: 1L }\ninferred := Box(1)\nprintln(\"\")")
  Assert.equal(valid.diagnostics.length, 0)

  invalidClass := checked("class Box<T: int | long> { value: T }\nbox := Box<string> { value: \"no\" }\nprintln(\"\")")
  Assert.equal(invalidClass.diagnostics.length > 0, true)
  Assert.equal(invalidClass.diagnostics[0].message.contains("does not satisfy constraint \"int | long\""), true)

  inferredInvalidClass := checked("class Box<T: int | long> { value: T }\nbox := Box(\"no\")\nprintln(\"\")")
  Assert.equal(inferredInvalidClass.diagnostics.length > 0, true)
  Assert.equal(inferredInvalidClass.diagnostics[0].message.contains("does not satisfy constraint \"int | long\""), true)

  invalidAlias := checked("type Numeric<T: int | long> = T\nvalue: Numeric<string> := \"no\"\nprintln(\"\")")
  Assert.equal(invalidAlias.diagnostics.length > 0, true)
  Assert.equal(invalidAlias.diagnostics[0].message.contains("does not satisfy constraint \"int | long\""), true)
}

export function testEnforcesImportedOrdinaryGenericConstraints(): none {
  result := checkedSources([
    SourceFile { path: "/main.do", source: "import { keep } from \"./numbers\"\nvalue := keep(\"no\")\nprintln(\"\")" },
    SourceFile { path: "/numbers.do", source: "export function keep<T: int | long>(value: T): T => value" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message.contains("does not satisfy constraint \"int | long\""), true)
}

export function testRejectsMetadataForNonSerializableMethods(): none {
  result := checked("class Bad { function run(callback: (value: int): void): string => \"no\" }\nmetadata := Bad.metadata")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("not JSON-serializable"), true)
}

export function testChecksReadonlyArrayLiteralAndReadonlyField(): none {
  result := checked("class Request { readonly headers: int[] }\nfunction use(values: readonly int[]): int => values.length\nfunction main(): int { values := readonly [1, 2]\nrequest := Request { headers: values }\nreturn use(request.headers) }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testContextuallyInfersArrayLiteralReadonlyness(): none {
  result := checked("expectedBuilt: readonly byte[] := [1, 2, 3, 4, 5]")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksByteCastBuiltin(): none {
  result := checked("function carriageReturn(): byte => byte(13)")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksActorCreationSyncAsyncPromiseAndRetire(): none {
  result := checked("class Worker { let value: int\nfunction add(amount: int): int { this.value = this.value + amount\nreturn this.value } }\nfunction run(): int { worker: Actor<Worker> := Actor<Worker>(1)\nvalue := worker.add(2)\npromise: Promise<int> := async worker.add(3)\nasyncValue := try! promise.get()\nstate: Worker := retire worker\nreturn value + asyncValue + state.value }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testValidatesActorConstructorArguments(): none {
  wrongType := checked("class Worker { value: int }\nfunction make(): Actor<Worker> => Actor<Worker>(\"wrong\")")
  Assert.equal(wrongType.diagnostics.length, 1)
  Assert.stringContains(wrongType.diagnostics[0].message, "expected int")

  wrongArity := checked("class Worker { value: int }\nfunction make(): Actor<Worker> => Actor<Worker>(1, 2)")
  Assert.equal(wrongArity.diagnostics.length, 1)
  Assert.stringContains(wrongArity.diagnostics[0].message, "expects 1 constructor argument")
}

export function testChecksAsyncBlocksWithImmutableCapturesAndMutableResults(): none {
  result := checked("function run(input: int): int { offset := 2\npromise: Promise<int[]> := async { let values = [input, offset]\nvalues.push(5)\nyield values }\nvalues := try! promise.get()\nreturn values.length }\n")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)

  missingYield := checked("function run(): Promise<int> => async { if true { yield 1 } }")
  Assert.equal(missingYield.diagnostics.length > 0, true)
  Assert.equal(missingYield.diagnostics[0].message.contains("must yield a value on every path"), true)
}

export function testTakesTheFirstCompletedPromiseFromMutableArrays(): none {
  valid := checked("function take(promises: Promise<int>[]): Result<int, string> => promises.takeFirstCompleted()")
  Assert.equal(valid.diagnostics.length, 0)

  readonlyResult := checked("function take(promises: readonly Promise<int>[]): Result<int, string> => promises.takeFirstCompleted()")
  Assert.equal(readonlyResult.diagnostics.length, 1)
  Assert.equal(readonlyResult.diagnostics[0].message, "Method \"takeFirstCompleted\" is not available on readonly array")

  wrongElement := checked("function take(values: int[]): none { values.takeFirstCompleted() }")
  Assert.equal(wrongElement.diagnostics.length, 1)
  Assert.equal(wrongElement.diagnostics[0].message, "Type \"int[]\" has no member \"takeFirstCompleted\"")
}

export function testChecksSharedAsyncResultTypeGraphsOnce(): none {
  result := checked(
    "class Leaf { value: int }\n" +
    "class Branch { left: Leaf\nright: Leaf }\n" +
    "class Tree { first: Branch\nsecond: Branch }\n" +
    "function build(): Promise<Tree> => async { yield Tree { first: Branch { left: Leaf { value: 1 }, right: Leaf { value: 2 } }, second: Branch { left: Leaf { value: 3 }, right: Leaf { value: 4 } } } }",
  )
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsUnsafeAsyncBlockCaptures(): none {
  mutableBinding := checked("function run(): Promise<int> { let value = 1\nreturn async { yield value } }")
  Assert.equal(mutableBinding.diagnostics.length > 0, true)
  Assert.equal(mutableBinding.diagnostics[0].message.contains("must come from an immutable binding"), true)

  mutableInterior := checked("function run(): Promise<int> { values := [1]\nreturn async { yield values.length } }")
  Assert.equal(mutableInterior.diagnostics.length > 0, true)
  Assert.equal(mutableInterior.diagnostics[0].message.contains("array type"), true)

  callback := checked("function run(callback: (): int): Promise<int> => async { yield callback() }")
  Assert.equal(callback.diagnostics.length > 0, true)
  let foundCallback = false
  for diagnostic of callback.diagnostics { if diagnostic.message.contains("actor-affine callbacks") { foundCallback = true } }
  Assert.equal(foundCallback, true)
}

export function testRejectsNonIsolatedAsyncBlocksAndUnsafeResults(): none {
  nonIsolated := checked("let shared = 0\nfunction mutate(): int { shared = shared + 1\nreturn shared }\nfunction run(): Promise<int> => async { yield mutate() }")
  let foundIsolation = false
  for diagnostic of nonIsolated.diagnostics { if diagnostic.message.contains("Async block is not isolated") { foundIsolation = true } }
  Assert.equal(foundIsolation, true)

  promiseResult := checked("function run(): Promise<(): int> { return async { yield (): int => 1 } }")
  let foundResult = false
  for diagnostic of promiseResult.diagnostics { if diagnostic.message.contains("callback") && diagnostic.message.contains("cannot cross from the worker") { foundResult = true } }
  Assert.equal(foundResult, true)
}

export function testAllowsNestedAsyncWorkOwnedByTheOuterBlock(): none {
  result := checked("class Job { function value(): int => 7 }\nfunction run(): Promise<int> => async { worker := Actor<Job>()\nnested := async worker.value()\nvalue := try! nested.get()\nretire worker\nyield value }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsNonActorAsyncAndRetire(): none {
  asyncResult := checked("function value(): int => 1\nfunction run(): Promise<int> => async value()")
  Assert.equal(asyncResult.diagnostics.length, 0)
  retireResult := checked("value := retire 1")
  Assert.equal(retireResult.diagnostics.length > 0, true)
  Assert.equal(retireResult.diagnostics[0].message.contains("Cannot retire non-actor"), true)
}

export function testChecksIsolatedAsyncFunctionCallBoundaries(): none {
  valid := checked("function copyFirst(values: readonly int[]): int[] => [values[0]]\nfunction run(values: readonly int[]): Promise<int[]> => async copyFirst(values)")
  Assert.equal(valid.diagnostics.length, 0)

  unsafeArgument := checked("function length(values: int[]): int => values.length\nfunction run(values: int[]): Promise<int> => async length(values)")
  Assert.equal(unsafeArgument.diagnostics.length, 1)
  Assert.equal(unsafeArgument.diagnostics[0].message.contains("Async call argument 1"), true)

  nonIsolated := checked("let shared = 0\nfunction next(): int { shared = shared + 1\nreturn shared }\nfunction run(): Promise<int> => async next()")
  let foundIsolation = false
  for diagnostic of nonIsolated.diagnostics { if diagnostic.message.contains("Async call is not isolated") { foundIsolation = true } }
  Assert.equal(foundIsolation, true)

  unsafeResult := checked("function callback(): (): int => (): int => 1\nfunction run(): Promise<(): int> => async callback()")
  let foundResult = false
  for diagnostic of unsafeResult.diagnostics { if diagnostic.message.contains("Async call result type") { foundResult = true } }
  Assert.equal(foundResult, true)
}

export function testRejectsSameBindingUseAfterRetireButAllowsShadowing(): none {
  used := checked("class Worker { function value(): int => 1 }\nfunction run(): int { worker := Actor<Worker>()\nretire worker\nreturn worker.value() }")
  Assert.equal(used.diagnostics.length > 0, true)
  Assert.equal(used.diagnostics[0].message.contains("after it has been retired"), true)

  shadowed := checked("class Worker { function value(): int => 1 }\nfunction run(): int { worker := Actor<Worker>()\nretire worker\nif true { worker := Actor<Worker>()\nvalue := worker.value()\nretire worker\nreturn value }\nreturn 0 }")
  Assert.equal(shadowed.diagnostics.length, 0)
}

export function testValidatesActorBoundaryPayloads(): none {
  immutableResult := checked("class Payload { value: int }\nclass Worker { function accept(payload: Payload): void {} }\nfunction main(): none { worker := Actor<Worker>()\npayload := Payload { value: 1 }\nworker.accept(payload) }")
  Assert.equal(immutableResult.diagnostics.length, 0)

  mutableResult := checked("class Payload { let value: int }\nclass Worker { function accept(payload: Payload): void {} }\nfunction main(): none { worker := Actor<Worker>()\npayload := Payload { value: 1 }\nworker.accept(payload) }")
  Assert.equal(mutableResult.diagnostics.length > 0, true)
  Assert.equal(mutableResult.diagnostics[0].message.contains("field \"value\" is mutable"), true)

  readonlyResult := checked("class Payload { readonly value: int }\nclass Worker { function accept(payload: Payload): int => payload.value }\nfunction main(): none { worker := Actor<Worker>()\npayload := Payload { value: 1 }\nvalue := worker.accept(payload) }")
  Assert.equal(readonlyResult.diagnostics.length, 0)

  nestedImmutable := checked("class Payload { value: int }\nclass Envelope { payload: Payload }\nclass Worker { function accept(envelope: Envelope): int => envelope.payload.value }\nfunction main(): none { worker := Actor<Worker>()\nworker.accept(Envelope { payload: Payload { value: 1 } }) }")
  Assert.equal(nestedImmutable.diagnostics.length, 0)

  mutableInterior := checked("class Payload { values: int[] }\nclass Worker { function accept(payload: Payload): void {} }\nfunction main(): none { worker := Actor<Worker>()\nworker.accept(Payload { values: [1] }) }")
  Assert.equal(mutableInterior.diagnostics.length > 0, true)
  Assert.stringContains(mutableInterior.diagnostics[0].message, "array type \"int[]\" is mutable")

  mutableSet := checked("class Worker { function accept(values: Set<int>): void {} }\nfunction main(): none { worker := Actor<Worker>()\nvalues: Set<int> := [1]\nworker.accept(values) }")
  Assert.equal(mutableSet.diagnostics.length > 0, true)
  Assert.equal(mutableSet.diagnostics[0].message.contains("set type \"Set<int>\" is mutable"), true)

  readonlySet := checked("class Worker { function accept(values: ReadonlySet<int>): int => values.size }\nfunction main(): none { worker := Actor<Worker>()\nvalues: Set<int> := [1]\nfrozen := values.drainToReadonly()\nvalue := worker.accept(frozen) }")
  Assert.equal(readonlySet.diagnostics.length, 0)
}

export function testValidatesDeepReadonlyFieldGraphs(): none {
  immutable := checked("class Point { x: int }\nclass Container { readonly point: Point\nreadonly values: int[] }")
  Assert.equal(immutable.diagnostics.length, 0)

  mutableClass := checked("class MutablePoint { let x: int }\nclass Container { readonly point: MutablePoint }")
  Assert.equal(mutableClass.diagnostics.length, 1)
  Assert.stringContains(mutableClass.diagnostics[0].message, "Readonly field \"Container.point\" must be deeply immutable")
  Assert.stringContains(mutableClass.diagnostics[0].message, "field \"x\" is mutable")

  actor := checked("class Worker {}\nclass Container { readonly worker: Actor<Worker> }")
  Assert.equal(actor.diagnostics.length, 1)
  Assert.stringContains(actor.diagnostics[0].message, "Actor<T> references cannot cross actor boundaries")
}

export function testValidatesNestedAndGenericActorBoundaryPayloads(): none {
  nested := checked("class Worker { function accept(payload: Payload): void {} }\nclass Payload { readonly actor: Actor<Worker> }\nfunction main(): none { worker := Actor<Worker>()\npayload := Payload { actor: worker }\nworker.accept(payload) }")
  Assert.equal(nested.diagnostics.length > 0, true)
  Assert.equal(nested.diagnostics[0].message.contains("Actor<T> references"), true)

  generic := checked("class Worker { function echo<T>(value: T): T => value }\nfunction main(): none { worker := Actor<Worker>()\nother := Actor<Worker>()\nresult := worker.echo<Actor<Worker> >(other) }")
  Assert.equal(generic.diagnostics.length > 0, true)
  Assert.equal(generic.diagnostics[0].message.contains("Actor<T> references"), true)
}

export function testRejectsActorMethodsThatAccessMutableModuleState(): none {
  result := checked("shared := [0]\nclass Worker { function run(): void { shared.push(1) } }\nfunction main(): void { worker := Actor<Worker>()\nworker.run() }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("Actor method \"run\" is not isolated"), true)
  Assert.equal(result.diagnostics[0].message.contains("mutable module binding \"shared\""), true)
}

export function testEnforcesExplicitIsolationTransitively(): none {
  result := checked("shared := [0]\nfunction mutate(): void { shared.push(1) }\nisolated function run(): void { mutate() }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("Isolated function \"run\" cannot call non-isolated function \"mutate\""), true)
}

export function testWarnsForFunctionKeywordOnClassMethods(): none {
  result := checkedIncludingDeprecations("class Worker { function run(): int => 1\nstatic function create(): Worker => Worker {} }")
  Assert.equal(result.diagnostics.length, 2)
  Assert.equal(result.diagnostics[0].severity, "warning")
  Assert.stringContains(result.diagnostics[0].message, "'function' on class methods is deprecated")
  Assert.equal(result.diagnostics[0].replacement, "run")
  Assert.equal(result.diagnostics[1].replacement, "create")
}

export function testEnforcesExplicitIsolationOnClassMethods(): none {
  result := checked("shared := [0]\nclass Worker { isolated run(): none { shared.push(1) }\nisolated static create(): Worker => Worker {} }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "Isolated method \"Worker.run\"")
  Assert.stringContains(result.diagnostics[0].message, "mutable module binding \"shared\"")
}

export function testValidatesNestedAsyncIsolationOnce(): none {
  result := checked("shared := [0]\nfunction run(): Promise<int>[] => [async { yield shared.length }]")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message.contains("Async block is not isolated"), true)
  Assert.equal(result.diagnostics[0].message.contains("mutable module binding \"shared\""), true)
}

export function testAllowsActorMethodsToCallIsolatedNativeMethodContracts(): none {
  result := checked("import class NativeProcess from \"native_process.hpp\" { isolated static run(): int }\nclass Worker { function compile(): int => NativeProcess.run() }\nfunction main(): void { worker := Actor<Worker>()\nworker.compile() }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testAllowsActorMethodsToCallIsolatedNativeFunctionContracts(): none {
  result := checked("import isolated function nativeRun(): int from \"native.hpp\"\nclass Worker { function run(): int => nativeRun() }\nfunction main(): void { worker := Actor<Worker>()\nworker.run() }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsActorMethodsThatCallNativeFunctionsWithoutIsolatedContracts(): none {
  result := checked("import function nativeRun(): int from \"native.hpp\"\nclass Worker { function run(): int => nativeRun() }\nfunction main(): void { worker := Actor<Worker>()\nworker.run() }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("Actor method \"run\" is not isolated"), true)
  Assert.equal(result.diagnostics[0].message.contains("non-isolated function \"nativeRun\""), true)
}

export function testRejectsActorMethodsThatTransitivelyAccessImportedMutableState(): none {
  result := checkedSources([
    SourceFile { path: "/main.do", source: "import { mutate } from \"./state\"\nclass Worker { function run(): void { mutate() } }\nfunction main(): void { worker := Actor<Worker>()\nworker.run() }" },
    SourceFile { path: "/state.do", source: "values := [0]\nexport function mutate(): void { values.push(1) }" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length > 0, true)
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("Actor method \"run\" is not isolated") && diagnostic.message.contains("non-isolated function \"mutate\"") { found = true }
  }
  Assert.equal(found, true)
}

export function testAllowsActorLocalMutationAndRecursiveIsolatedCalls(): none {
  result := checked("readonly SCALE = 2\nfunction multiply(value: int): int => value * SCALE\nclass Worker { let value: int\nfunction step(remaining: int): void { if remaining <= 0 { return }\nthis.value = multiply(this.value)\nstep(remaining - 1) } }\nfunction main(): void { worker := Actor<Worker>(1)\nworker.step(3) }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsMutableActorConstructionArguments(): none {
  result := checked("class Payload { let value: int }\nclass Worker { payload: Payload }\nfunction main(): void { payload := Payload { value: 1 }\nworker := Actor<Worker>(payload) }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("Actor constructor argument 1"), true)
  Assert.equal(result.diagnostics[0].message.contains("field \"value\" is mutable"), true)
}

export function testRejectsActorDefaultsThatCaptureMutableModuleState(): none {
  result := checked("shared := [0]\nclass Worker { values: int[] = shared }\nfunction main(): void { worker := Actor<Worker>() }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("Actor<Worker> construction is not isolated"), true)
  Assert.equal(result.diagnostics[0].message.contains("mutable module binding \"shared\""), true)
}

export function testReadonlyInterfaceFieldsRequireReadonlyImplementations(): none {
  result := checked("interface Payload { readonly value: int }\nclass MutablePayload implements Payload { value: int }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("does not satisfy interface \"Payload\""), true)
}

export function testRejectsMutableStaticStateReachedFromActorMethods(): none {
  result := checked("class Globals { static let count: int = 0 }\nclass Worker { function run(): void { Globals.count = Globals.count + 1 } }\nfunction main(): void { worker := Actor<Worker>()\nworker.run() }")
  Assert.equal(result.diagnostics.length > 0, true)
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("mutable static field \"Globals.count\"") { found = true } }
  Assert.equal(found, true)
}

export function testAllowsStableStaticValuesButRejectsMutableStaticInteriorsInActorMethods(): none {
  stable := checked("class Globals { static count: int = 1 }\nclass Worker { function read(): int => Globals.count }\nfunction main(): none { worker := Actor<Worker>()\nworker.read() }")
  Assert.equal(stable.diagnostics.length, 0)

  mutableInterior := checked("class Globals { static values: int[] = [] }\nclass Worker { function read(): int => Globals.values.length }\nfunction main(): none { worker := Actor<Worker>()\nworker.read() }")
  Assert.equal(mutableInterior.diagnostics.length > 0, true)
  let found = false
  for diagnostic of mutableInterior.diagnostics { if diagnostic.message.contains("mutable static field \"Globals.values\"") { found = true } }
  Assert.equal(found, true)

  implicitMutableInterior := checked("class Worker { static values: int[] = []\nfunction read(): int => values.length }\nfunction main(): none { worker := Actor<Worker>()\nworker.read() }")
  Assert.equal(implicitMutableInterior.diagnostics.length > 0, true)
  found = false
  for diagnostic of implicitMutableInterior.diagnostics { if diagnostic.message.contains("mutable static field \"Worker.values\"") { found = true } }
  Assert.equal(found, true)
}

export function testPropagatesIsolationThroughInterfaceDispatch(): none {
  source := "shared := [0]\ninterface Job { run(): void }\nclass UnsafeJob implements Job { function run(): void { shared.push(1) } }\nclass Worker { job: Job = UnsafeJob {}\nfunction execute(): void { this.job.run() } }\nfunction main(): void { worker := Actor<Worker>()\nworker.execute() }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  semantic := createChecker(analysis).check("/main.do")
  diagnostics := semantic.diagnostics
  for diagnostic of validateIsolationEffects(analysis) { diagnostics.push(diagnostic) }
  let unsafeFound = false
  let workerFound = false
  for statement of analysis.modules[0].program.statements {
    case statement {
      class_: ClassDeclaration -> {
        if class_.name == "UnsafeJob" { unsafeFound = true; Assert.equal(class_.methods[0].resolvedIsolated, false) }
        if class_.name == "Worker" { workerFound = true; Assert.equal(class_.methods[0].resolvedIsolated, false) }
      }
      _ -> { }
    }
  }
  Assert.equal(unsafeFound, true)
  Assert.equal(workerFound, true)
  result := CheckResult { diagnostics }
  Assert.equal(result.diagnostics.length > 0, true)
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("Actor method \"execute\" is not isolated") && diagnostic.message.contains("non-isolated function \"run\"") { found = true }
  }
  Assert.equal(found, true)
}

export function testRejectsMutableImplementationsWidenedToBoundaryInterfaces(): none {
  result := checked("interface Payload { readonly id: int }\nclass MutablePayload implements Payload { readonly id: int\nlet value: int }\nclass Worker { function accept(payload: Payload): void {} }\nfunction main(): void { worker := Actor<Worker>()\npayload: Payload := MutablePayload { id: 1, value: 2 }\nworker.accept(payload) }")
  Assert.equal(result.diagnostics.length > 0, true)
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("implementation \"MutablePayload\"") && diagnostic.message.contains("field \"value\" is mutable") { found = true }
  }
  Assert.equal(found, true)
}

export function testRequiresActorConstructorFactoriesToBeIsolated(): none {
  result := checked("shared := [0]\nclass Worker { values: int[]\nstatic constructor(): Worker => Worker { values: shared } }\nfunction main(): void { worker := Actor<Worker>() }")
  Assert.equal(result.diagnostics.length > 0, true)
  let found = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("Actor<Worker> construction is not isolated") && diagnostic.message.contains("non-isolated function \"constructor\"") { found = true }
  }
  Assert.equal(found, true)
}

export function testRejectsFallibleActorConstructorFactories(): none {
  result := checked("class Worker { static constructor(): Result<Worker, string> => Success { value: Worker {} } }\nfunction main(): none { worker := Actor<Worker>() }")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "must return Worker directly")
}

export function testChecksPromiseVoidGet(): none {
  result := checked("function settle(promise: Promise<void>): Result<void, string> => promise.get()")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksActorAffineCallbackMembers(): none {
  result := checked("function use(callback: (value: int): int): Promise<int> => callback.post(1)\nfunction notify(callback: (value: int): void): void { callback.dispatch(1) }")
  Assert.equal(result.diagnostics.length, 0)
  invalid := checked("function use(callback: (value: int): int): void { callback.dispatch(1) }")
  Assert.equal(invalid.diagnostics.length > 0, true)
  Assert.equal(invalid.diagnostics[0].message.contains("none-returning callbacks"), true)
}

export function testChecksExplicitGenericNamedCall(): none {
  result := checked("function create<T>(value: T, count: int = 1): T => value\nfunction main(): string => create<string>{ value: \"ok\" }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testSubstitutesExplicitGenericTupleReturn(): none {
  result := checked("function pair<T>(value: T): Tuple<T, T> => (value, value)\nfunction total(): int { (first, second) := pair<int>(1)\nreturn first + second }\n")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsExplicitGenericCallArity(): none {
  result := checked("function create<T>(value: T): T => value\nfunction main(): int => create<int, string>(1)")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "Generic call requires 1 type argument; received 2")
}

export function testChecksDeclarationElseNarrowingAndCapture(): none {
  result := checked("function load(): Result<int, string> => Success { value: 4 }\nfunction maybe(): string | null => \"ok\"\nfunction main(): int { value := load() else error { println(error)\nreturn 1 }\nname := maybe() else { return 2 }\nreturn value + name.length }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksDeclarationElseNarrowsOneLayerAtATime(): none {
  result := checked("function load(): Result<int, string> | null => null\nfunction main(): int { result := load() else { return 1 }\nvalue := result else { return 2 }\nreturn value }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRequiresDeclarationElseHandlerToExit(): none {
  result := checked("function load(): Result<int, string> => Success { value: 4 }\nfunction main(): int { value := load() else { println(\"failed\") }\nreturn value }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "Declaration-else block must exit scope")
}

export function testAllowsDiscardDeclarationElseToContinue(): none {
  result := checked("function save(): Result<void, string> => Success()\nfunction main(): int { _ := save() else error { println(error) }\nreturn 0 }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testAcceptsPanicAsDeclarationElseExit(): none {
  result := checked("function load(): Result<int, string> => Success { value: 4 }\nfunction main(): int { value := load() else { panic(\"load failed\") }\nreturn value }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsImmutableAssignment(): none {
  result := checked("function main(): void { value := 1\nvalue = 2 }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "Cannot assign to immutable binding 'value'")
}

export function testRequiresReturnsOnEveryPath(): none {
  result := checked("function answer(flag: bool): int { if flag { return 1 } }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "Function 'answer' may complete without returning int")
}

export function testAcceptsReturnsOnEveryIfPath(): none {
  result := checked("function answer(flag: bool): int { if flag { return 1 } else { return 2 } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testAcceptsReturnsFromExhaustiveCase(): none {
  result := checked("function answer(value: int): int { case value { 1 -> { return 1 }, _ -> { return 2 } } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testAcceptsReturnsFromExhaustiveResultCase(): none {
  result := checked("function load(): Result<int, string> => Success { value: 1 }\nfunction answer(): Result<int, string> { case load() { success: Success -> { return Success { value: success.value } }, failure: Failure -> { return Failure { error: failure.error } } } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testDecoratesCaseStatementControlFlowCompletion(): none {
  source := "function load(): Result<int, string> => Success { value: 1 }\nfunction answer(): int { case load() { value: Success -> { return value.value }, error: Failure -> { return 0 } } }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  case analysis.modules[0].program.statements[1] {
    fn: FunctionDeclaration -> { case fn.body {
      block: Block -> { case block.statements[0] {
        case_: CaseStatement -> { Assert.equal(case_.resolvedCompletes, false) }
        _ -> { panic("expected case statement") }
      } }
      _ -> { panic("expected block body") }
    } }
    _ -> { panic("expected function declaration") }
  }
  Assert.equal(validateCheckedTypes(analysis).length, 0)
}

export function testChecksNeverAsBottomTypeAndPropagatesDivergence(): none {
  result := checked("function fail(message: string): never => panic(message)\nfunction choose(flag: bool): int => if flag then 42 else fail(\"no value\")\nfunction required(): string { return fail(\"missing\") }\ntype Value = int | never\nfunction failure(): Result<never, string> => Failure { error: \"failed\" }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsNeverFunctionsThatCanReturnOrFallThrough(): none {
  value := checked("function bad(): never => 1")
  Assert.equal(value.diagnostics.length, 1)
  Assert.equal(value.diagnostics[0].message, "Cannot return int from function returning never")

  fallthrough := checked("function bad(): never {}")
  Assert.equal(fallthrough.diagnostics.length, 1)
  Assert.equal(fallthrough.diagnostics[0].message, "Function 'bad' may complete without returning never")
}

export function testAcceptsDivergentExhaustiveEnumAndUnionCases(): none {
  enumResult := checked("enum Direction { North, South }\nfunction failDirection(direction: Direction): never { case direction { .North -> { panic(\"north\") }, .South -> { panic(\"south\") } } }")
  Assert.equal(enumResult.diagnostics.length, 0)

  unionResult := checked("class Left {}\nclass Right {}\ntype Side = Left | Right\nfunction failSide(side: Side): never { case side { _: Left -> { panic(\"left\") }, _: Right -> { panic(\"right\") } } }")
  Assert.equal(unionResult.diagnostics.length, 0)
}

export function testDecoratesTypedResultArmPatterns(): none {
  source := "function load(): Result<int, string> => Failure { error: \"no\" }\nfunction inspect(): void { case load() { _: Failure<string> -> { } _ -> { } } }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  createChecker(analysis).check("/main.do")
  Assert.equal(validateCheckedTypes(analysis).length, 0)
}

export function testPostfixBangUnwrapsResultSuccessType(): none {
  result := checked("function decode(): Result<string, string> => Success { value: \"ok\" }\nfunction consume(value: string): void {}\nfunction main(): void { consume(decode()!) }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksResultStatusMethods(): none {
  result := checked("function load(): Result<int, string> => Failure { error: \"no\" }\nfunction failed(): bool => load().isFailure()\nfunction succeeded(): bool => load().isSuccess()")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksResultUnwrapOrFallback(): none {
  result := checked("function load(): Result<JsonValue, string> => Failure { error: \"no\" }\nfunction value(): JsonValue => load().unwrapOr(null)")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksResultCoalescingAsSuccessPayload(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function load(): Result<int, string> => Success(7)\nfunction value(): int => load() ?? 0" }]).analyze("/main.do")
  semantic := createChecker(analysis).check("/main.do")
  Assert.equal(semantic.diagnostics.length, 0)
  case analysis.modules[0].program.statements[1] {
    function_: FunctionDeclaration -> { case function_.body {
      expression: BinaryExpression -> { Assert.equal(typeName(expression.resolvedType!), "int") }
      _ -> { panic("expected coalescing expression") }
    } }
    _ -> { panic("expected value function") }
  }
}

export function testAcceptsUnconditionalNonTerminatingLoop(): none {
  result := checked("function run(): int { while true {} }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksStatementsAfterBreakableLoop(): none {
  result := checked("function run(flag: bool): int { while true { if flag { break } }\nreturn 1 }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testResolvesImplicitClassMethodCalls(): none {
  result := checked("class Box { function value(): int => 7\nfunction read(): int { answer := value()\nreturn answer } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksClassDestructorBody(): none {
  result := checked("class Resource { function close(): void {}\ndestructor { close() } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsStructDestructor(): none {
  result := checked("struct Resource { destructor {} }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].message, "Struct \"Resource\" cannot declare a destructor")
}

export function testResolvesClassAndMethodTypeParameters(): none {
  source := "class Box<T> { map<U>(transform: (it: T): U): Box<U> => Box<U> {} }"
  result := checked(source)
  Assert.equal(result.diagnostics.length, 0)
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  createChecker(analysis).check("/main.do")
  Assert.equal(validateCheckedTypes(analysis).length, 0)
}

export function testValidatesGenericStreamMembers(): none {
  source := "class FilteredStream<T> implements Stream<T> { source: Stream<T>\npred: (it: T): bool\nnext(): bool => source.next()\nvalue(): T => source.value() }\nclass MappedStream<T, U> implements Stream<U> { source: Stream<T>\ntransform: (it: T): U\nnext(): bool => source.next()\nvalue(): U => transform(source.value()) }\nclass Chain<T> implements Stream<T> { source: Stream<T>\nnext(): bool => source.next()\nvalue(): T => source.value()\nmap<U>(transform: (it: T): U): Chain<U> => Chain<U> { source: MappedStream<T, U> { source, transform } } }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(createChecker(analysis).check("/main.do").diagnostics.length, 0)
  Assert.equal(validateCheckedTypes(analysis).length, 0)
}

export function testInfersNullableImplicitMethodResults(): none {
  result := checked("class Item {}\nclass Box { function maybe(): Item | null => null\nfunction read(): void { ignored := maybe() } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testDecoratesNestedNullableAssignmentTargets(): none {
  source := "class Left { value: int }\nclass Right { value: int }\ntype Expression = Left | Right\nclass ParserLike { parse(): none { let value: Expression | none = none\nif true { value = Left { value: 1 } } else { value = Right { value: 2 } } } }"
  sources := [SourceFile { path: "/main.do", source }]
  analysis := createAnalyzer(sources).analyze("/main.do")
  semantic := createChecker(analysis).check("/main.do")
  Assert.equal(semantic.diagnostics.length, 0)
  case analysis.modules[0].program.statements[3] {
    class_: ClassDeclaration -> {
      case class_.methods[0].body {
        block: Block -> {
          case block.statements[1] {
            if_: IfStatement -> {
              case if_.body.statements[0] {
                expression: ExpressionStatement -> {
                  case expression.expression {
                    assignment: AssignmentExpression -> {
                      case assignment.target {
                        identifier: Identifier -> { Assert.equal(identifier.resolvedBinding != none, true) }
                      }
                    }
                  }
                }
              }
              case if_.else_! {
                elseBlock: Block -> {
                  case elseBlock.statements[0] {
                    expression: ExpressionStatement -> {
                      case expression.expression {
                        assignment: AssignmentExpression -> {
                          case assignment.target {
                            identifier: Identifier -> { Assert.equal(identifier.resolvedBinding != none, true) }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

export function testChecksNativeMethodsAndStaticMethods(): none {
  result := checked("import class Client from \"client.hpp\" as native::Client { get(): int static make(): Client }\nfunction read(client: Client): int { made := Client.make()\nreturn client.get() + made.get() }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksNativeResultMethodsThroughTryBindings(): none {
  result := checked("import class Writer from \"writer.hpp\" as native::Writer { static open(path: string): Result<Writer, string> writeBlob(data: byte[]): Result<void, string> }\nfunction write(): void { try writer := Writer.open(\"path\")\ntry writer.writeBlob([]) }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksTryValueDeclarations(): none {
  result := checked("function load(): Result<int, string> => Success { value: 1 }\nfunction run(): Result<int, string> { try const first = load()\ntry readonly second = load()\ntry let third = load()\nthird = third + first\nreturn Success { value: third + second } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksExplicitAndStructuralInterfaceImplementations(): none {
  result := checked("interface Drawable { value: int\nrender(): int }\nclass Point implements Drawable { readonly value: int\nfunction render(): int => value }\nclass Other { value: int\nfunction render(): int => value }\nfunction read(shape: Drawable): int => shape.render()\nfunction main(): int { point := Point { value: 3 }\nother := Other { value: 4 }\nfirst := read(point)\nsecond := read(other)\nreturn first + second }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsAssignmentToImplicitlyImmutableFields(): none {
  result := checked("class Counter { value: int\nfunction update(): none { value += 1\nthis.value = value + 1 } }\nfunction updateOutside(counter: Counter): none { counter.value = 3 }")
  Assert.equal(result.diagnostics.length, 3)
  for diagnostic of result.diagnostics {
    Assert.equal(diagnostic.severity, "error")
    Assert.stringContains(diagnostic.message, "Cannot assign to immutable field 'Counter.value'")
    Assert.stringContains(diagnostic.message, "declare it with 'let'")
  }
}

export function testChecksExplicitFieldMutabilityModes(): none {
  mutable := checked("class Counter { let value: int\nfunction update(): none { value += 1\nthis.value = value + 1 } }\nfunction updateOutside(counter: Counter): none { counter.value = 3 }")
  Assert.equal(mutable.diagnostics.length, 0)

  frozen := checked("class Counter { readonly value: int }\nfunction update(counter: Counter): none { counter.value = 3 }")
  Assert.equal(frozen.diagnostics.length, 1)
  Assert.equal(frozen.diagnostics[0].severity, "error")
  Assert.stringContains(frozen.diagnostics[0].message, "immutable field 'Counter.value'")

  interior := checked("class Buffer { values: int[] }\nfunction append(buffer: Buffer): none { buffer.values.push(1) }")
  Assert.equal(interior.diagnostics.length, 0)
}

export function testRejectsGroupedStaticStructAndNativeBareFieldWrites(): none {
  grouped := checked("class Point { x, y: int\nfunction move(): none { x += 1\ny += 1 } }\nstruct State { value: int }\nclass Globals { static count: int = 0 }\nimport class Native from \"native.hpp\" { value: int }\nfunction update(state: State, native: Native): none { state.value = 1\nGlobals.count += 1\nnative.value = 2 }")
  Assert.equal(grouped.diagnostics.length, 5)
  for diagnostic of grouped.diagnostics {
    Assert.equal(diagnostic.severity, "error")
    Assert.stringContains(diagnostic.message, "declare it with 'let'")
  }
}

export function testChecksInterfaceFieldMutabilityContracts(): none {
  valid := checked("interface Mutable { let value: int }\nclass Counter implements Mutable { let value: int }\nfunction update(counter: Mutable): none { counter.value += 1 }")
  Assert.equal(valid.diagnostics.length, 0)

  missingLet := checked("interface Mutable { let value: int }\nclass Counter implements Mutable { value: int }")
  Assert.equal(missingLet.diagnostics.length > 0, true)
  Assert.stringContains(missingLet.diagnostics[0].message, "does not satisfy interface")

  immutableView := checked("interface View { value: int }\nclass Counter implements View { let value: int }\nfunction update(view: View): none { view.value = 1 }")
  Assert.equal(immutableView.diagnostics.length, 1)
  Assert.equal(immutableView.diagnostics[0].severity, "error")
  Assert.stringContains(immutableView.diagnostics[0].message, "immutable field 'View.value'")
}

export function testRejectsClassesThatDoNotSatisfyInterfaces(): none {
  result := checked("interface Drawable { render(): int }\nclass Point implements Drawable { function render(): string => \"bad\" }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "Class \"Point\" does not satisfy interface \"Drawable\"")
}

export function testRejectsInterfacesWithoutImplementations(): none {
  result := checked("interface Empty { value: int }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message, "Cannot emit interface \"Empty\" without implementing classes")
}

export function testChecksIntrinsicJsonValueLiterals(): none {
  result := checked("function main(): JsonValue { payload: JsonValue := { name: \"Ada\", values: [1, true, null] }\nreturn payload }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsNonJsonCollections(): none {
  result := checked("function main(): void { values: int[] := [1, 2]\npayload: JsonValue := values }")
  Assert.equal(result.diagnostics.length > 0, true)
}

export function testChecksContextualResultAndClassObjectLiterals(): none {
  result := checked("class Payload { count: int }\nenum LoadError { Missing }\nfunction load(ok: bool): Result<Payload, LoadError> { if !ok { return { error: .Missing } }\nreturn { value: { count: 4 } } }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testInfersContextualSumObjectLiteralsByShape(): none {
  result := checked(
    "class Animal { name: string }\n" +
    "class Question { text: string\nlet yes: Knowledge\nlet no: Knowledge }\n" +
    "type Knowledge = Animal | Question\n" +
    "function keep(value: Knowledge): Knowledge => value\n" +
    "function initial(): Knowledge => { text: \"Does it swim\", yes: { name: \"fish\" }, no: { name: \"bird\" } }\n" +
    "function main(): Knowledge { let knowledge: Knowledge = { name: \"cat\" }\nknowledge = keep({ text: \"Does it fly\", yes: { name: \"eagle\" }, no: { name: \"fish\" } })\nreturn knowledge }",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testInfersStructNullableDefaultShorthandAndLiteralSumObjects(): none {
  result := checked(
    "struct Leaf { value: int\nlabel: string = \"leaf\" }\n" +
    "struct Pair { left: int\nright: int }\n" +
    "type Node = Leaf | Pair | none\n" +
    "function leaf(value: int): Node => { value }\n" +
    "class TaggedSuccess { const kind = \"Success\"\nvalue: int }\n" +
    "class TaggedFailure { const kind = \"Failure\"\nerror: string }\n" +
    "type Outcome = TaggedSuccess | TaggedFailure\n" +
    "function outcome(): Outcome => { kind: \"Success\", value: 1 }",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsAmbiguousContextualSumObjectsWithoutValueTypeTieBreaking(): none {
  result := checked("class Count { value: int }\nclass Label { value: string }\ntype Item = Count | Label\nfunction make(): Item => { value: 1 }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "Ambiguous object literal")
  Assert.stringContains(result.diagnostics[0].message, "Count, Label")
  Assert.stringContains(result.diagnostics[0].message, "explicit Type { ... } construction")
}

export function testRejectsUnmatchedAndSpreadContextualSumObjects(): none {
  unmatched := checked("class Left { left: int }\nclass Right { right: int }\ntype Side = Left | Right\nfunction make(): Side => { missing: 1 }")
  Assert.equal(unmatched.diagnostics.length, 1)
  Assert.stringContains(unmatched.diagnostics[0].message, "does not match any constructible member")
  Assert.stringContains(unmatched.diagnostics[0].message, "Left, Right")

  missingLiteral := checked("class TaggedSuccess { const kind = \"Success\"\nvalue: int }\nclass TaggedFailure { const kind = \"Failure\"\nerror: string }\ntype Outcome = TaggedSuccess | TaggedFailure\nfunction make(): Outcome => { value: 1 }")
  Assert.equal(missingLiteral.diagnostics.length, 1)
  Assert.stringContains(missingLiteral.diagnostics[0].message, "does not match any constructible member")

  wrongLiteral := checked("class TaggedSuccess { const kind = \"Success\"\nvalue: int }\nclass TaggedFailure { const kind = \"Failure\"\nerror: string }\ntype Outcome = TaggedSuccess | TaggedFailure\nfunction make(): Outcome => { kind: \"Failure\", value: 1 }")
  Assert.equal(wrongLiteral.diagnostics.length, 1)
  Assert.stringContains(wrongLiteral.diagnostics[0].message, "must match its literal-valued declaration")

  spread := checked("class Left { left: int }\nclass Right { right: int }\ntype Side = Left | Right\nfunction make(): Side { base := Left { left: 1 }\nreturn { ...base } }")
  Assert.equal(spread.diagnostics.length, 1)
  Assert.stringContains(spread.diagnostics[0].message, "spread fields")
}

export function testPreservesJsonObjectTypingWhenUnionHasNominalMember(): none {
  result := checked("class Payload { name: string }\ntype Value = Payload | JsonValue\nfunction make(): Value => { name: \"Ada\" }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testCollapsesDuplicateUnionMembers(): none {
  result := checked("function choose(value: string | string): string => value")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksEmptyMapsWithNonStringKeyTypes(): none {
  result := checked("class State { glyphs: Map<int, string> = {} }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksStringCompoundAssignmentFromChar(): none {
  result := checked("function main(): string { let value = \"\"\nvalue += 'x'\nreturn value + 'y' }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testResolvesImportedReadonlyValueTypes(): none {
  result := checkedSources([
    SourceFile { path: "/constants.do", source: "export readonly TAU = 6.283185307179586" },
    SourceFile { path: "/main.do", source: "import { TAU } from \"./constants\"\nfunction scale(value: double): double => value * TAU" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
}

export function testAssignsJsonValueNullableUnions(): none {
  result := checked("function wrap(value: JsonValue): JsonValue | null { return value }\nfunction keep(value: JsonValue | null): JsonValue | null { let current: JsonValue | null = value\ncurrent = value\nreturn current }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testResolvesMapKeyAndValueArrays(): none {
  result := checked("function main(): int { values: Map<int, string> = {}\nreturn values.keys().length + values.values().length }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksSetAndReadonlySetMembers(): none {
  result := checked("enum Flag { One, Two }\nfunction bytes(values: Set<byte>): int => values.size\nfunction count(values: ReadonlySet<Flag>): int { let total = 0\nfor value of values { if values.has(value) { total = total + 1 } }\nreturn total + values.values().length }\nfunction main(): int { let values: Set<Flag> = [Flag.One, Flag.Two, Flag.One]\nvalues.add(Flag.Two)\nvalues.delete(Flag.One)\nsnapshot := values.cloneReadonly()\nfrozen := values.drainToReadonly()\ncopy := frozen.cloneMutable()\ncopy.add(Flag.One)\nreturn count(snapshot) + count(frozen) + copy.size }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksReadonlyCollectionConversions(): none {
  result := checked(
    "function arrays(values: int[]): readonly int[] { snapshot: readonly int[] := values.cloneReadonly()\nreturn values.drainToReadonly() }\n" +
    "function maps(values: Map<string, int>): ReadonlyMap<string, int> { snapshot: ReadonlyMap<string, int> := values.cloneReadonly()\nreturn values.drainToReadonly() }\n" +
    "function sets(values: Set<int>): ReadonlySet<int> { snapshot: ReadonlySet<int> := values.cloneReadonly()\nreturn values.drainToReadonly() }",
  )
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testWarnsForDeprecatedBuildReadonly(): none {
  result := checkedIncludingDeprecations("function freeze(values: int[]): readonly int[] => values.buildReadonly()")
  Assert.equal(result.diagnostics.length, 1)
  Assert.equal(result.diagnostics[0].severity, "warning")
  Assert.equal(result.diagnostics[0].message, "'buildReadonly' is deprecated; replace it with 'drainToReadonly'")
  Assert.equal(result.diagnostics[0].replacement, "drainToReadonly")
}

export function testInfersOmittedCollectionTypeArgumentsFromLiterals(): none {
  source := "numbers: Set := [1, 2, 3]\nfrozen: ReadonlySet := [1, 2, 3]\nqualified: readonly Set := [1, 2, 3]\nlet reboundable: readonly Set = [1, 2, 3]\nreadonly deep: Set = [1, 2, 3]\nscores: Map := { \"Ada\": 10, \"Grace\": 20 }\nfrozenScores: readonly Map := { \"Ada\": 10 }\nreadonly deepScores: Map = { \"Ada\": 10 }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  semantic := createChecker(analysis).check("/main.do")
  for diagnostic of semantic.diagnostics { println(diagnostic.message) }
  Assert.equal(semantic.diagnostics.length, 0)

  case analysis.modules[0].program.statements[0] {
    binding: ImmutableBinding -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "Set<int>") }
    _ -> { panic("expected an immutable binding") }
  }
  case analysis.modules[0].program.statements[1] {
    binding: ImmutableBinding -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "ReadonlySet<int>") }
    _ -> { panic("expected an immutable binding") }
  }
  case analysis.modules[0].program.statements[2] {
    binding: ImmutableBinding -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "ReadonlySet<int>") }
    _ -> { panic("expected an immutable binding") }
  }
  case analysis.modules[0].program.statements[3] {
    binding: LetDeclaration -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "ReadonlySet<int>") }
    _ -> { panic("expected a let binding") }
  }
  case analysis.modules[0].program.statements[4] {
    binding: ReadonlyDeclaration -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "ReadonlySet<int>") }
    _ -> { panic("expected a readonly binding") }
  }
  case analysis.modules[0].program.statements[5] {
    binding: ImmutableBinding -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "Map<string, int>") }
    _ -> { panic("expected an immutable binding") }
  }
  case analysis.modules[0].program.statements[6] {
    binding: ImmutableBinding -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "readonly Map<string, int>") }
    _ -> { panic("expected an immutable binding") }
  }
  case analysis.modules[0].program.statements[7] {
    binding: ReadonlyDeclaration -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "readonly Map<string, int>") }
    _ -> { panic("expected a readonly binding") }
  }
}

export function testChecksDotShorthandEnumMapKeysInFieldDefaults(): none {
  result := checked("enum Suit { Spades, Hearts }\nclass Pile {}\nclass State { foundations: Map<Suit, Pile> = { .Spades: Pile {}, .Hearts: Pile {} } }")
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksAndInfersIntegerMapKeys(): none {
  annotated := checked("ints: Map<int, string> := { 1: \"one\", 2: \"two\" }\nlongs: Map<long, string> := { 1L: \"one\", 2L: \"two\" }")
  Assert.equal(annotated.diagnostics.length, 0)

  source := "inferred: Map := { 1: \"one\", 2: \"two\" }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  semantic := createChecker(analysis).check("/main.do")
  Assert.equal(semantic.diagnostics.length, 0)
  case analysis.modules[0].program.statements[0] {
    binding: ImmutableBinding -> { Assert.equal(typeName(binding.resolvedType ?? unknownType()), "Map<int, string>") }
    _ -> { panic("expected an immutable binding") }
  }
}

export function testRejectsInvalidOmittedCollectionInferenceSites(): none {
  emptySet := checked("values: Set := []")
  Assert.equal(emptySet.diagnostics.length > 0, true)
  Assert.equal(emptySet.diagnostics[0].message.contains("empty set literal"), true)

  mixedSet := checked("values: Set := [1, \"two\"]")
  Assert.equal(mixedSet.diagnostics.length > 0, true)
  Assert.equal(mixedSet.diagnostics[0].message.contains("heterogeneous set elements"), true)

  wrongLiteral := checked("values: Set := { \"one\": 1 }")
  Assert.equal(wrongLiteral.diagnostics.length > 0, true)
  Assert.equal(wrongLiteral.diagnostics[0].message.contains("same-site non-empty set literal"), true)

  emptyMap := checked("values: Map := {}")
  Assert.equal(emptyMap.diagnostics.length > 0, true)
  Assert.equal(emptyMap.diagnostics[0].message.contains("empty map literal"), true)
}

export function testRejectsReadonlyCollectionConversions(): none {
  result := checked(
    "function arrayConversions(values: readonly int[]): none { values.buildReadonly()\nvalues.drainToReadonly()\nvalues.cloneReadonly() }\n" +
    "function mapConversions(values: ReadonlyMap<string, int>): none { values.buildReadonly()\nvalues.drainToReadonly()\nvalues.cloneReadonly() }\n" +
    "function setConversions(values: ReadonlySet<int>): none { values.buildReadonly()\nvalues.drainToReadonly()\nvalues.cloneReadonly() }",
  )
  Assert.equal(result.diagnostics.length, 9)
  let arrayErrors = 0
  let mapErrors = 0
  let setErrors = 0
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("not available on readonly array") { arrayErrors = arrayErrors + 1 }
    if diagnostic.message.contains("not available on readonly map") { mapErrors = mapErrors + 1 }
    if diagnostic.message.contains("not available on readonly set") { setErrors = setErrors + 1 }
  }
  Assert.equal(arrayErrors, 3)
  Assert.equal(mapErrors, 3)
  Assert.equal(setErrors, 3)
}

export function testRejectsReadonlySetMutation(): none {
  result := checked("function mutate(values: ReadonlySet<int>): void { values.add(1)\nvalues.delete(1) }")
  Assert.equal(result.diagnostics.length, 2)
  Assert.stringContains(result.diagnostics[0].message, "not available on readonly set")
  Assert.stringContains(result.diagnostics[1].message, "not available on readonly set")
}

export function testRejectsUnsupportedSetElementTypes(): none {
  numeric := checked("function use(values: Set<float>): void {}")
  Assert.equal(numeric.diagnostics.length > 0, true)
  Assert.equal(numeric.diagnostics[0].message.contains("Set element type \"float\" is not supported"), true)

  nominal := checked("class Item {}\nfunction use(values: ReadonlySet<Item>): void {}")
  Assert.equal(nominal.diagnostics.length > 0, true)
  Assert.equal(nominal.diagnostics[0].message.contains("Set element type \"Item\" is not supported"), true)
}

export function testKeepsSetMutabilityInvariant(): none {
  result := checked("function bad(values: Set<int>): ReadonlySet<int> { return values }")
  Assert.equal(result.diagnostics.length > 0, true)
  Assert.equal(result.diagnostics[0].message.contains("Cannot return Set<int> from function returning ReadonlySet<int>"), true)
}

export function testChecksYieldBlockDeclarationsAndReassignment(): none {
  valid := checked("function main(): int { let score: int <- { if true { yield 10 } else { yield 5 } }\nscore <- { yield score + 1 }\nreturn score }")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)

  missingYield := checked("function main(): int { let score <- { if true { yield 10 } }\nreturn score }")
  Assert.equal(missingYield.diagnostics.length > 0, true)
  Assert.equal(missingYield.diagnostics[0].message.contains("must yield a value on every path"), true)

  immutable := checked("function main(): int { value := 1\nvalue <- { yield 2 }\nreturn value }")
  Assert.equal(immutable.diagnostics.length > 0, true)
  Assert.equal(immutable.diagnostics[0].message.contains("immutable"), true)

  global := checked("readonly value <- { yield 1 }")
  Assert.equal(global.diagnostics.length > 0, true)
  Assert.equal(global.diagnostics[0].message.contains("local declarations"), true)

  prohibited := checked("function load(): Result<int, string> => Success { value: 1 }\nfunction main(): int { let value <- { try load()\nyield 1 }\nreturn value }")
  Assert.equal(prohibited.diagnostics.length > 0, true)
  Assert.equal(prohibited.diagnostics[0].message.contains("'try' cannot be used inside a value-producing block"), true)
}

export function testChecksCatchExpressionErrorUnionsAndNesting(): none {
  valid := checked("enum ReadError { Missing }\nenum DecodeError { Invalid }\nfunction read(): Result<int, ReadError> => Failure { error: .Missing }\nfunction parse(): Result<int, DecodeError> => Failure { error: .Invalid }\nfunction main(): void { error := catch { try read()\ninner := catch { try parse() } }\ncase error { _: ReadError -> println(\"read\"), _ -> println(\"ok\") } }")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)

  warning := checked("function main(): void { error := catch { println(\"ok\") } }")
  Assert.equal(warning.diagnostics.length, 1)
  Assert.equal(warning.diagnostics[0].severity, "warning")
  Assert.equal(warning.diagnostics[0].message.contains("contains no 'try'"), true)
}

export function testChecksDestructuringDeclarationsAndAssignments(): none {
  valid := checked("class Person { name: string\nage: int }\nstruct Pair { left: int\nright: string }\nfunction main(): int { values := [1, 2, 3]\n[first, _, third] := values\nperson := Person { name: \"Ada\", age: 37 }\n{ name as displayName, age } := person\npair := Pair { left: 4, right: \"ok\" }\n(left, right) := pair\nlet target = 0\n[target, _] = values\nlet renamed = \"\"\n{ name as renamed } = person\nreturn first + third + age + left + target + displayName.length + right.length + renamed.length }")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
}

export function testRejectsInvalidDestructuringAssignmentsAndShapes(): none {
  immutable := checked("function main(): void { value := 0\n(value, _) = (1, 2) }")
  Assert.equal(immutable.diagnostics.length > 0, true)
  Assert.equal(immutable.diagnostics[0].message.contains("immutable"), true)

  missing := checked("function main(): void { (missing, _) = (1, 2) }")
  Assert.equal(missing.diagnostics.length > 0, true)
  Assert.equal(missing.diagnostics[0].message.contains("not defined"), true)

  incompatible := checked("function main(): void { let value = \"\"\n(value, _) = (1, 2) }")
  Assert.equal(incompatible.diagnostics.length > 0, true)
  Assert.equal(incompatible.diagnostics[0].message.contains("Cannot assign"), true)

  nonArray := checked("function main(): void { [value] := 1 }")
  Assert.equal(nonArray.diagnostics.length > 0, true)
  Assert.equal(nonArray.diagnostics[0].message.contains("Array destructuring requires"), true)

  tooShort := checked("class One { value: int }\nfunction main(): void { (first, second) := One { value: 1 } }")
  Assert.equal(tooShort.diagnostics.length > 0, true)
  Assert.equal(tooShort.diagnostics[0].message.contains("expected at least 2"), true)
}

export function testChecksTryDestructuringAgainstSuccessPayload(): none {
  result := checked("class Person { name: string\nage: int }\nfunction load(): Result<Person, string> => Success { value: Person { name: \"Ada\", age: 37 } }\nfunction run(): Result<int, string> { try { name, age } := load()\nreturn Success { value: name.length + age } }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsConflictingGenericInferenceCandidates(): none {
  result := checked("function choose<T>(left: T, right: T): T => left\nfunction main(): none { choose(1, \"wrong\") }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "Cannot infer consistent type arguments")
}

export function testPreservesConcreteGenericInterfaceArguments(): none {
  result := checked("interface Box<T> { get(): T }\nclass IntBox implements Box<int> { get(): int => 1 }\nfunction consume(value: Box<string>): string => value.get()\nfunction main(): none { consume(IntBox {}) }")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "expected Box<string>")
}

export function testRejectsPrivateMemberAccessAcrossModules(): none {
  result := checkedSources([
    SourceFile {
      path: "/main.do",
      source: "import { Secret } from \"./secret\"\n" +
        "function main(): none {\n" +
        "  secret := Secret { value: 1 }\n" +
        "  first := secret.value\n" +
        "  second := secret.reveal()\n" +
        "}",
    },
    SourceFile { path: "/secret.do", source: "export class Secret { private value: int\nprivate reveal(): int => this.value }" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 3)
  for diagnostic of result.diagnostics {
    Assert.stringContains(diagnostic.message, "private")
    Assert.equal(diagnostic.module, "/main.do")
  }
  Assert.equal(result.diagnostics[0].span.start.line, 3)
  Assert.equal(result.diagnostics[1].span.start.line, 4)
  Assert.equal(result.diagnostics[2].span.start.line, 5)
}

export function testAllowsExternalConstructionWithDefaultedPrivateFields(): none {
  result := checkedSources([
    SourceFile {
      path: "/main.do",
      source: "import { Builder } from \"./builder\"\nfunction main(): none { builder := Builder() }",
    },
    SourceFile {
      path: "/builder.do",
      source: "export class Builder { private positions: int[] = []\nprivate indices: int[] = [] }",
    },
  ], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.module + ": " + diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testReportsPositionalPrivateFieldConstructionAtCaller(): none {
  result := checkedSources([
    SourceFile {
      path: "/main.do",
      source: "import { Secret } from \"./secret\"\nfunction main(): none {\n  value := Secret(1)\n}",
    },
    SourceFile { path: "/secret.do", source: "export class Secret { private value: int }" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "Field 'value' is private")
  Assert.equal(result.diagnostics[0].module, "/main.do")
  Assert.equal(result.diagnostics[0].span.start.line, 3)
  Assert.equal(result.diagnostics[0].span.start.column, 19)
}

export function testReportsActorPrivateFieldConstructionAtCaller(): none {
  result := checkedSources([
    SourceFile {
      path: "/main.do",
      source: "import { Secret } from \"./secret\"\nfunction make(): Actor<Secret> => Actor<Secret>(1)",
    },
    SourceFile { path: "/secret.do", source: "export class Secret { private value: int }" },
  ], "/main.do")
  Assert.equal(result.diagnostics.length, 1)
  Assert.stringContains(result.diagnostics[0].message, "Field 'value' is private")
  Assert.equal(result.diagnostics[0].module, "/main.do")
  Assert.equal(result.diagnostics[0].span.start.line, 2)
}

export function testRejectsConcreteReturnsForUnconstrainedTypeParameters(): none {
  result := checked("function fabricate<T>(): T => 1\nfunction main(): string => fabricate<string>()")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "Cannot return int from function returning T")
}

export function testRejectsInstanceMemberAccessFromStaticMethods(): none {
  result := checked("class Counter { value: int\nstatic read(): int => value }")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "Unknown identifier 'value'")
}

export function testRejectsPrivateConstructorsAcrossModules(): none {
  result := checkedSources([
    SourceFile { path: "/main.do", source: "import { Secret } from \"./secret\"\nfunction main(): none { value := Secret(1) }" },
    SourceFile { path: "/secret.do", source: "export class Secret { value: int\nprivate static constructor(value: int): Secret => Secret { value } }" },
  ], "/main.do")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "private")
}

export function testPrivateMethodsDoNotSatisfyPublicInterfaces(): none {
  result := checked("interface Reader { read(): int }\nclass SecretReader implements Reader { private read(): int => 1 }")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "does not satisfy interface")
}

export function testRejectsDuplicateClassMembers(): none {
  result := checked("class Broken { value: int\nvalue: int }")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "already declared")
}

export function testRejectsDuplicateInterfaceMembers(): none {
  fields := checked("interface Duplicate { value: int\nvalue: int }\nclass Value implements Duplicate { value: int }")
  Assert.isTrue(fields.diagnostics.length > 0)
  Assert.stringContains(fields.diagnostics[0].message, "already declared in interface")

  methods := checked("interface Duplicate { read(): int\nread(): int }\nclass Reader implements Duplicate { read(): int => 1 }")
  Assert.isTrue(methods.diagnostics.length > 0)
  Assert.stringContains(methods.diagnostics[0].message, "already declared in interface")
}

export function testRejectsDuplicateEnumVariantNames(): none {
  result := checked("enum Duplicate { Same, Same }")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "already declared in enum")
}

export function testRequiresUniqueEnumValues(): none {
  explicitResult := checked("enum Duplicate { First = 1, Second = 1 }")
  Assert.isTrue(explicitResult.diagnostics.length > 0)
  Assert.stringContains(explicitResult.diagnostics[0].message, "duplicates the value")

  implicit := checked("enum Duplicate { First, Second = 0 }")
  Assert.isTrue(implicit.diagnostics.length > 0)
  Assert.stringContains(implicit.diagnostics[0].message, "duplicates the value")
}

export function testRequiresCompileTimeIntegerEnumValues(): none {
  result := checked("function computed(): int => 1\nenum Dynamic { Value = computed() }")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "compile-time int constant")

  arithmetic := checked("enum Calculated { Two = 1 + 1, Three = 7 % 4, Five = 10 \\ 2, Six = 2 * 3 }")
  Assert.equal(arithmetic.diagnostics.length, 0)

  overflow := checked("enum Overflow { Last = 2147483647, TooFar }")
  Assert.isTrue(overflow.diagnostics.length > 0)
  Assert.stringContains(overflow.diagnostics[0].message, "outside the int range")

  divideByZero := checked("enum Invalid { Value = 1 \\ 0 }")
  Assert.isTrue(divideByZero.diagnostics.length > 0)
  Assert.stringContains(divideByZero.diagnostics[0].message, "compile-time int constant")
}

export function testRejectsWeakScalarTargets(): none {
  modifier := checked("class Invalid { weak count: int }")
  Assert.isTrue(modifier.diagnostics.length > 0)
  Assert.stringContains(modifier.diagnostics[0].message, "weak reference target")

  annotation := checked("function invalid(value: weak int): none {}")
  Assert.isTrue(annotation.diagnostics.length > 0)
  Assert.stringContains(annotation.diagnostics[0].message, "weak reference target")
}

export function testChecksWeakReferenceAccessOperators(): none {
  source := "class Node { value: int\nread(): int => value\nfallible(): Result<int, string> => Success { value } }\n" +
    "function optionalField(node: weak Node): Result<int | none, WeakReferenceError> => node?.value\n" +
    "function optionalCall(node: weak Node): Result<int | none, WeakReferenceError> => node?.read()\n" +
    "function optionalFallibleCall(node: weak Node): Result<int | none, string | WeakReferenceError> => node?.fallible()\n" +
    "function forcedField(node: weak Node): int => node!.value\n" +
    "function forcedCall(node: weak Node): int => node!.read()"
  result := checked(source)
  Assert.equal(result.diagnostics.length, 0)
}

export function testChecksWeakUnionReferenceAccess(): none {
  result := checked("class Cat { name: string\nspeak(): string => name }\nclass Dog { name: string\nspeak(): string => name }\nclass Holder { weak pet: Cat | Dog }\nfunction make(cat: Cat): Holder => Holder { pet: cat }\nfunction name(holder: Holder): Result<string | none, WeakReferenceError> => holder.pet?.name\nfunction speak(holder: Holder): string => holder.pet!.speak()")
  Assert.equal(result.diagnostics.length, 0)
}

export function testRejectsUncheckedWeakReferenceMemberAccess(): none {
  result := checked("class Node { value: int\nread(): int => value }\nfunction field(node: weak Node): int => node.value\nfunction call(node: weak Node): int => node.read()")
  Assert.equal(result.diagnostics.length, 2)
  Assert.stringContains(result.diagnostics[0].message, "requires '?.' or '!.'")
  Assert.stringContains(result.diagnostics[1].message, "requires '?.' or '!.'")
}
