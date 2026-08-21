import { Assert } from "std/assert"
import isolated function codePointToUtf8(value: int): string from "doof_runtime.hpp" as doof::char_to_utf8
import { createAnalyzer } from "./analyzer"
import { createChecker, validateIsolationEffects } from "./checker"
import { AnalysisResult } from "./analyzer"
import { ClassDeclaration, ConstructExpression, ImmutableBinding, Program } from "./ast"
import { SourceFile } from "./semantic"
import { ModuleEmission, emitModule, emitModuleGraph, ModuleGraphPlan, planModuleGraph } from "./emitter-module"
import { buildInstantiationPlan } from "./emitter-monomorphize"
import { canGenerateJsonDeserialization, canGenerateJsonSerialization, JsonEligibilityCache } from "./json-semantics"
import { ModuleNamespaceMapping, configureModuleNamespaces } from "./emitter-names"
import { hasErrorDiagnostics } from "./diagnostics"

function emit(source: string): ModuleEmission {
  return emitSources([SourceFile { path: "/main.do", source }], "/main.do")
}

function emitSources(sources: SourceFile[], entry: string): ModuleEmission {
  analysis := createAnalyzer(sources).analyze(entry)
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis, entry).check(entry)
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  program := findProgram(analysis, entry)
  return emitModule(program!, "main", buildInstantiationPlan(analysis))
}

function emitMonomorphized(source: string): ModuleEmission {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis).check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  return graph.modules[0]
}

export function testCachesJsonEligibilityAcrossProjectedHeaders(): none {
  analysis := createAnalyzer([SourceFile { path: "/payload.do", source: "class Payload { value: int }" }]).analyze("/payload.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis).check("/payload.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  program := findProgram(analysis, "/payload.do")!
  case program.statements[0] {
    owner: ClassDeclaration -> {
      cache := JsonEligibilityCache {}
      Assert.equal(canGenerateJsonSerialization(owner, [program], cache), true)
      Assert.equal(canGenerateJsonSerialization(owner, [program], cache), true)
      Assert.equal(canGenerateJsonDeserialization(owner, [program], cache), true)
      Assert.equal(canGenerateJsonDeserialization(owner, [program], cache), true)
      Assert.equal(cache.serialization.size, 1)
      Assert.equal(cache.deserialization.size, 1)
    }
    _ -> { panic("expected class declaration") }
  }
}

export function testKeepsLetFieldLoweringRepresentationNeutral(): none {
  bare := emit("class State { value: int }\nfunction main(): int => State { value: 1 }.value")
  mutable := emit("class State { let value: int }\nfunction main(): int => State { value: 1 }.value")
  Assert.equal(mutable.header, bare.header)
  Assert.equal(mutable.source, bare.source)
}

export function testEmitsTypedTagsThroughNamedCallAndConstructorPaths(): none {
  result := emit(
    "class Widget { id: int\nname: string\nchildren: string[] = [] }\n" +
    "class Custom { value: int\nstatic constructor(label: string, value: int): Custom => Custom { value } }\n" +
    "function render(id: int, label: string): string => label + string(id)\n" +
    "function makeWidget(): Widget => <Widget name=\"red\" id=1>hello</Widget>\n" +
    "function main(): int { label := <render label=\"item\" id=2/>\ncustom := <Custom value=3 label=\"custom\"/>\nreturn makeWidget().id + custom.value + label.length }",
  )
  Assert.stringContains(result.source, "1, std::string(\"red\")")
  Assert.stringContains(result.source, "render(2, std::string(\"item\"))")
  Assert.stringContains(result.source, "Custom::constructor(std::string(\"custom\"), 3)")
  Assert.stringContains(result.source, "std::string(\"hello\")")
}

export function testEscapesQuestionMarksInCppStringLiteralsToAvoidTrigraphs(): none {
  result := emit("function main(): string => \"Operator '??=' remains readable\"")
  Assert.stringContains(result.source, "std::string(\"Operator '\\?\\?=' remains readable\")")
  Assert.stringNotContains(result.source, "Operator '??='")
}

export function testOmitsEmptyNamespaceBlocksFromHeaders(): none {
  functionOnly := emit("function main(): int => 0")
  Assert.stringNotContains(functionOnly.header, "namespace main_ {\n}\n")
  Assert.stringContains(functionOnly.header, "namespace main_ {\n    int32_t doof_main()")
  Assert.isFalse(functionOnly.header.endsWith("\n\n"))

  enumOnly := emit("enum Color { Red }")
  Assert.stringNotContains(enumOnly.header, "namespace main_ {\n}\n")
  Assert.stringContains(enumOnly.header, "namespace main_ {\n    enum class Color")
  Assert.isFalse(enumOnly.header.endsWith("\n\n"))
}

export function testEmitsIOSAppEntryWithoutNativeMain(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "function main(): void {}" }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis).check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  source := emitModuleGraph(analysis, "/main.do", none, "ios-app").modules[0].source
  Assert.stringContains(source, "extern \"C\" int doof_entry_main")
  Assert.equal(source.contains("int main("), false)
}

export function testEmitsDirectModuleStorageAndExplicitAssignments(): none {
  result := emit(
    "export readonly label = \"ready\"\n" +
    "export readonly primes = [2, 3, 5, 7]\n" +
    "readonly answer = 3\n" +
    "class Globals { static message = \"hello\" }\n" +
    "function main(): int => answer",
  )
  Assert.stringContains(result.header, "extern std::string label;")
  Assert.stringContains(result.header, "extern std::shared_ptr<std::vector<int32_t>> primes;")
  Assert.equal(result.header.contains("inline const auto"), false)
  Assert.stringContains(result.source, "std::string label;")
  Assert.stringContains(result.source, "int32_t answer = 3;")
  Assert.stringContains(result.source, "std::shared_ptr<std::vector<int32_t>> primes;")
  Assert.stringContains(result.source, "primes = std::make_shared<std::vector<int32_t>>")
  Assert.stringContains(result.source, "Globals::message = std::string(\"hello\");")
  Assert.equal(result.source.contains("__doof_module_initialization_state"), false)
  Assert.equal(result.source.contains("__doof_script_get_"), false)
  Assert.equal(result.source.contains("std::optional<"), false)
}

export function testDeclaresPublicAndPrivateModuleConstantsBeforeClassFieldDefaults(): none {
  result := emit(
    "export readonly PUBLIC_DURATION = 0.25\n" +
    "readonly PRIVATE_DURATION = 0.5\n" +
    "class Movement { publicDuration: double = PUBLIC_DURATION\nprivateDuration: double = PRIVATE_DURATION }\n" +
    "function make(): Movement => Movement {}",
  )
  publicDeclaration := result.header.indexOf("extern double PUBLIC_DURATION;")
  privateDeclaration := result.header.indexOf("extern double PRIVATE_DURATION;")
  classDefinition := result.header.indexOf("struct Movement : public")
  Assert.isTrue(publicDeclaration >= 0)
  Assert.isTrue(privateDeclaration >= 0)
  Assert.isTrue(publicDeclaration < classDefinition)
  Assert.isTrue(privateDeclaration < classDefinition)
  Assert.stringContains(result.header, "double publicDuration = PUBLIC_DURATION;")
  Assert.stringContains(result.header, "double privateDuration = PRIVATE_DURATION;")
  Assert.stringContains(result.header, "Movement(double publicDuration = PUBLIC_DURATION, double privateDuration = PRIVATE_DURATION)")
}

export function testEmitsAssignableDefaultConstructedStructStaticStorage(): none {
  result := emit(
    "struct Vec3 { const kind = \"vec3\"\nx: double\ny: double\nz: double\n" +
    "static zero = Vec3 { x: 0.0, y: 0.0, z: 0.0 } }\n" +
    "struct Defaults { value: int = 0\nstatic zero = Defaults {} }\n" +
    "readonly origin = Vec3 { x: 0.0, y: 0.0, z: 0.0 }\n" +
    "function main(): int => 0",
  )
  Assert.stringContains(result.header, "std::string kind = std::string(\"vec3\");")
  Assert.equal(result.header.contains("const std::string kind"), false)
  Assert.stringContains(result.header, "Vec3() {}")
  Assert.stringContains(result.header, "Defaults(int32_t value = 0)")
  Assert.equal(result.header.contains("Defaults() {}"), false)
  Assert.stringContains(result.source, "Vec3 Vec3::zero;")
  Assert.stringContains(result.source, "Vec3 origin;")
  Assert.stringContains(result.source, "Vec3::zero = Vec3{")
  Assert.stringContains(result.source, "origin = Vec3{")
}

export function testOmitsInitializerForModulesWithoutDeferredState(): none {
  result := emit("export readonly answer = 3\nfunction main(): int => answer")
  Assert.stringContains(result.source, "int32_t answer = 3;")
  Assert.equal(result.source.contains("__doof_initialize_module"), false)
}

export function testEmitsDependencyFirstInitializationCallsInsideActorScope(): none {
  sources := [
    SourceFile { path: "/main.do", source: "import { b } from \"./b\"\nfunction main(): int => b.length" },
    SourceFile { path: "/b.do", source: "import { a } from \"./a\"\nexport readonly b = \"b\"" },
    SourceFile { path: "/a.do", source: "export readonly a = \"a\"" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checker := createChecker(analysis, "/main.do")
  for module of analysis.modules { Assert.equal(hasErrorDiagnostics(checker.check(module.path).diagnostics), false) }
  graph := emitModuleGraph(analysis, "/main.do")
  source := graph.modules[0].source
  actor := source.indexOf("ActiveActorScope __doof_application_scope")
  initializeA := source.indexOf("::app_a_::__doof_initialize_module();")
  initializeB := source.indexOf("::app_b_::__doof_initialize_module();")
  Assert.isTrue(actor >= 0)
  Assert.isTrue(actor < initializeA)
  Assert.isTrue(initializeA < initializeB)
  Assert.equal(source.contains("::app_main_::__doof_initialize_module();"), false)
}

export function testEmitsWeakFieldsAsWeakPointers(): none {
  result := emit("class Node { weak parent: Node\nancestor: weak Node }")
  Assert.equal(result.header.contains("std::weak_ptr<Node> parent"), true)
  Assert.equal(result.header.contains("std::weak_ptr<Node> ancestor"), true)
  Assert.equal(result.header.contains("Node(std::weak_ptr<Node> parent, std::weak_ptr<Node> ancestor)"), true)
}

export function testEmitsReflectableTypeParameterMetadataAccess(): none {
  result := emitMonomorphized("class Tool { function run(input: string): string => input }\nfunction describe<T: Reflectable>(tool: T): string => T.metadata.name\nfunction main(): int { println(describe<Tool>(Tool {}))\nreturn 0 }")
  Assert.stringContains(result.source, "doof::metadata_for_type<std::shared_ptr<Tool>>().name")
  Assert.stringContains(result.header, "static const doof::ClassMetadata<Tool> _metadata")
}

export function testEmitsJsonValueNullCasePattern(): none {
  result := emit("function isNull(value: JsonValue): bool => case value { _: null -> true, _ -> false }")
  Assert.stringContains(result.source, "doof::json_is_null(")
}

export function testLambdaCaptureExcludesItsOwnTypedParameters(): none {
  result := emit("function make(): (path: string): string { prefix := \"root/\"\nreturn (path: string): string => prefix + path }")
  Assert.equal(result.source.contains("[prefix](std::string path)"), true)
  Assert.equal(result.source.contains("[prefix, path]"), false)
}

export function testSynthesizesDistinctCppNamesForDiscardTargets(): none {
  result := emit(
    "class Guard {}\n" +
    "function apply(callback: (value: int, label: string): int): int => callback(1, \"ok\")\n" +
    "function main(): int { let total = 0\n" +
    "for _, _ of [(1, 2)] { total += 1 }\n" +
    "with _ := Guard {}, _ := Guard {} { total += apply((_, _): int => 1) }\n" +
    "return total }",
  )
  Assert.stringContains(result.source, "const auto& [_discard_")
  Assert.stringContains(result.source, "_with_discard_")
  Assert.stringContains(result.source, "int32_t _discard_parameter_0, std::string _discard_parameter_1")
}

export function testLambdaCapturesExplicitThis(): none {
  result := emit("class Receiver { values: int[] = []\nfunction make(): (value: int): void { return (value: int): void => this.values.push(value) } }")
  Assert.equal(result.source.contains("[this](int32_t value)"), true)
}

export function testLambdaCapturesThisForImplicitMethodCalls(): none {
  result := emit("class Receiver { handle(value: int): void {}\nmake(): (value: int): void => (value: int): void => handle(value) }")
  Assert.equal(result.source.contains("[this](int32_t value)"), true)
  Assert.equal(result.source.contains("return handle(value)"), true)
}

struct CapturedOptionalPoint {
  x: int
  y: int
}

function invokeMovement(callback: (point: CapturedOptionalPoint): int, point: CapturedOptionalPoint): int {
  return callback(point)
}

export function testNarrowsCapturedMutableOptionalStructInCallback(): none {
  let pressPoint: CapturedOptionalPoint | none = none
  callback := (point: CapturedOptionalPoint): int => {
    start := pressPoint as CapturedOptionalPoint else { return -1 }
    return start.x + point.y
  }

  Assert.equal(invokeMovement(callback, CapturedOptionalPoint { x: 2, y: 3 }), -1)
  pressPoint = CapturedOptionalPoint { x: 4, y: 5 }
  Assert.equal(invokeMovement(callback, CapturedOptionalPoint { x: 6, y: 3 }), 7)
}

export function testEmitsJsonValueAsNarrowing(): none {
  result := emit("function read(raw: JsonValue): bool { value := raw as bool else { return false }\nreturn value }")
  Assert.equal(result.source.contains("doof::json_is_boolean(_as_value)"), true)
  Assert.equal(result.source.contains("doof::json_as_bool(_as_value)"), true)
}

export function testEmitsDotShorthandEnumMapKeys(): none {
  result := emit("enum Suit { Spades, Hearts }\nclass Pile {}\nclass State { foundations: Map<Suit, Pile> = { .Spades: Pile {}, .Hearts: Pile {} } }")
  Assert.stringContains(result.header, "{Suit::Spades, std::make_shared<Pile>()}")
  Assert.stringContains(result.header, "{Suit::Hearts, std::make_shared<Pile>()}")
}

export function testEmitsEnumInstanceNameLookup(): none {
  result := emit("enum Terrain { Normal, Dangerous }\nfunction terrainName(terrain: Terrain): string => terrain.name\nfunction dangerousName(): string => Terrain.Dangerous.name")
  Assert.stringContains(result.source, "return Terrain_name(terrain);")
  Assert.stringContains(result.source, "return Terrain_name(Terrain::Dangerous);")
  Assert.stringNotContains(result.source, "terrain::name")
}

export function testEmitsIntegerMapKeys(): none {
  result := emit("function ints(): Map<int, string> => { 1: \"one\", 2: \"two\" }\nfunction longs(): Map<long, string> => { 1L: \"one\", 2L: \"two\" }")
  Assert.stringContains(result.source, "{1, std::string(\"one\")}")
  Assert.stringContains(result.source, "{2LL, std::string(\"two\")}")
}

export function testEmitsMinimumIntWithoutDoubleNegation(): none {
  result := emit("function minimum(): int => -2147483648")
  Assert.stringContains(result.source, "return -2147483648;")
  Assert.equal(result.source.contains("--2147483648"), false)
}

export function testEmitsArrayCollectionConversionsAndEnumFromValue(): none {
  result := emit("enum Suit { Spades = 0, Hearts = 1 }\nfunction drain(values: int[]): readonly int[] => values.drainToReadonly()\nfunction snapshot(values: int[]): readonly int[] => values.cloneReadonly()\nfunction clone(values: int[]): int[] => values.cloneMutable()\nfunction suit(index: int): Suit => Suit.fromValue(index) ?? .Spades")
  Assert.stringContains(result.source, "doof::array_drainToReadonly(values")
  Assert.stringContains(result.source, "doof::array_cloneReadonly(values")
  Assert.stringContains(result.source, "doof::array_cloneMutable(values")
  Assert.stringContains(result.source, "Suit_fromValue(index)")
  Assert.stringContains(result.header, "Suit_fromValue(int32_t value)")
}

export function testEmitsCStyleForInitializerWithoutExtraSemicolon(): none {
  result := emit("function sum(limit: int): int { let total = 0\nfor let i = 0; i < limit; i += 1 { total += i }\nreturn total }")
  Assert.stringContains(result.source, "for (auto i = 0; i < limit; (i += 1))")
  Assert.equal(result.source.contains("for (auto i = 0;;"), false)
}

export function testDoesNotCaptureModuleReadonlyValuesInLambdas(): none {
  result := emit("readonly CLICK_THRESHOLD: double = 5.0\nfunction invoke(handler: (): double): double => handler()\nfunction read(): double => invoke((): double => CLICK_THRESHOLD)")
  Assert.stringContains(result.source, "[]() -> double { return CLICK_THRESHOLD; }")
  Assert.equal(result.source.contains("[CLICK_THRESHOLD]"), false)
}

export function testEmitsRangeValuesSignaturesAndMembers(): none {
  result := emit("function first(values: Range): int { for value of values { return value }\nreturn values.lowerBound + values.upperBound }\nfunction main(): int => first(1..<4)")
  Assert.equal(result.header.contains("int32_t first(doof::Range values)"), true)
  Assert.equal(result.source.contains("for (const auto& value : _iterable_"), true)
  Assert.equal(result.source.contains("values.lowerBound + values.upperBound"), true)
  Assert.equal(result.source.contains("first(doof::range_exclusive(1, 4))"), true)
}

export function testEmitsFiniteAndOpenEndedCaseRangePatterns(): none {
  result := emit("function category(value: int): int => case value { ..<0 -> 1, 0..<10 -> 2, 10..20 -> 3, 21.. -> 4 }")
  Assert.stringContains(result.source, "_case_subject < 0")
  Assert.stringContains(result.source, "_case_subject >= 0 && _case_subject < 10")
  Assert.stringContains(result.source, "_case_subject >= 10 && _case_subject <= 20")
  Assert.stringContains(result.source, "_case_subject >= 21")
}

export function testEmitsCaseStatementRangePatterns(): none {
  result := emit("function category(value: int): void { case value { ..<0 -> println(\"negative\"), 0..10 -> println(\"small\"), 11.. -> println(\"large\") } }")
  Assert.stringContains(result.source, "if (_case_subject < 0)")
  Assert.stringContains(result.source, "else if (_case_subject >= 0 && _case_subject <= 10)")
  Assert.stringContains(result.source, "else if (_case_subject >= 11)")
}

export function testEmitsSetAndReadonlySetOperations(): none {
  result := emit("enum Flag { One, Two }\nfunction count(values: ReadonlySet<Flag>): int { let total = 0\nfor value of values { total = total + 1 }\nreturn total }\nfunction main(): int { let values: Set<Flag> = [Flag.One, Flag.Two, Flag.One]\nvalues.add(Flag.Two)\nvalues.delete(Flag.One)\nsnapshot := values.cloneReadonly()\nfrozen := values.drainToReadonly()\ncopy := frozen.cloneMutable()\nreturn count(snapshot) + count(frozen) + copy.values().length + copy.size }")
  Assert.equal(result.header.contains("std::shared_ptr<doof::ordered_set<Flag>>"), true)
  Assert.equal(result.source.contains("std::make_shared<doof::ordered_set<Flag>>"), true)
  Assert.equal(result.source.contains("->insert(Flag::Two)"), true)
  Assert.equal(result.source.contains("->erase(Flag::One)"), true)
  Assert.equal(result.source.contains("doof::set_drainToReadonly"), true)
  Assert.equal(result.source.contains("doof::set_cloneReadonly"), true)
  Assert.equal(result.source.contains("doof::set_cloneMutable"), true)
  Assert.equal(result.source.contains("doof::set_values"), true)
  Assert.equal(result.source.contains("->size()"), true)
}

export function testEmitsNullableJsonValueAsNarrowing(): none {
  result := emit("function read(value: JsonValue | null): Result<string, string> => value! as string")
  Assert.equal(result.source.contains("std::get<doof::JsonValue>(value)"), true)
  Assert.equal(result.source.contains("doof::unwrap_optional(value)"), false)
}

export function testEmitsRepresentationAwareNullableAsNarrowing(): none {
  result := emit("class Config { value: int }\nfunction config(value: Config | null): Result<Config, string> => value as Config\nfunction items(value: int[] | null): Result<int[], string> => value as int[]\nfunction count(value: int | null): Result<int, string> => value as int\nfunction wide(value: int | null): Result<long, string> => value as long")

  Assert.equal(result.source.contains("if (_as_value) return doof::Success<std::shared_ptr<Config>>{_as_value}"), true)
  Assert.equal(result.source.contains("if (_as_value) return doof::Success<std::shared_ptr<std::vector<int32_t>>>{_as_value}"), true)
  Assert.equal(result.source.contains("if (_as_value.has_value()) return doof::Success<int32_t>{_as_value.value()}"), true)
  Assert.equal(result.source.contains("doof::checked_numeric_as<int64_t>(_as_value.value())"), true)
  Assert.equal(result.source.contains("doof::variant_is"), false)
  Assert.equal(result.source.contains("doof::variant_narrow"), false)
}

export function testRetainsVariantBackedAsNarrowing(): none {
  result := emit("function text(value: int | string): Result<string, string> => value as string")
  Assert.equal(result.source.contains("doof::variant_is<std::string>(_as_value)"), true)
  Assert.equal(result.source.contains("doof::variant_narrow<std::string>(_as_value)"), true)
}

export function testEmitsNumericAsThroughMixedUnionAndResult(): none {
  result := emit("function mixed(value: int | string): Result<long, string> => value as long\nfunction fallible(value: Result<int, bool>): Result<long, bool | string> => value as long")
  Assert.stringContains(result.source, "std::visit([](const auto& _as_item) -> std::optional<int64_t>")
  Assert.stringContains(result.source, "doof::checked_numeric_as<int64_t>(_as_item)")
  Assert.stringContains(result.source, "if (doof::is_failure(_as_source))")
  Assert.stringContains(result.source, "doof::checked_numeric_as<int64_t>(doof::success_value(_as_source))")
  Assert.stringNotContains(result.source, "Unsupported narrowing")
}

export function testWrapsIdentityAsInItsDeclaredResultType(): none {
  result := emit("function same(value: int): Result<int, string> => value as int")
  Assert.stringContains(result.source, "doof::Result<int32_t, std::string>{doof::Success<int32_t>{value}}")
}

export function testEmitsLenientGeneratedJsonDecode(): none {
  result := emit("class Options { enabled: bool\nname: string }\nfunction decode(value: JsonValue): Result<Options, string> => Options.fromJsonValue(value, true)")
  Assert.equal(result.header.contains("bool _lenient = false"), true)
  Assert.equal(result.source.contains("json_is_lenient_boolean"), true)
  Assert.equal(result.source.contains("json_as_string_lenient"), true)
}

export function testEscapesShortCppKeywordEverywhere(): none {
  result := emit("class Option { short: string | null }\nfunction read(short: string): string => Option { short }.short!")
  Assert.equal(result.header.contains(" short_;"), true)
  Assert.equal(result.header.contains("const std::string& short_"), true)
  Assert.equal(result.source.contains("->short_"), true)
}

export function testEscapesCharCppKeywordEverywhere(): none {
  result := emit("function first(value: string): char { char := value[0]\nreturn char }")
  Assert.stringContains(result.source, "const auto char_ = doof::string_at(value, 0, \"<module>\", 1)")
  Assert.equal(result.source.contains("return char_"), true)
  Assert.equal(result.source.contains("auto char ="), false)
}

export function testEscapesDeleteCppKeywordForMethods(): none {
  result := emit("class Router { delete(pattern: string): Router => this }\nfunction remove(router: Router): Router => router.delete(\"/old\")")
  Assert.equal(result.header.contains(" delete_(const std::string& pattern)"), true)
  Assert.equal(result.source.contains("Router::delete_(const std::string& pattern)"), true)
  Assert.equal(result.source.contains("router->delete_(std::string(\"/old\"))"), true)
}

export function testEscapesPlatformStdioIdentifiersEverywhere(): none {
  result := emit("class Streams { stdin: string\nstdout: string\nstderr: string }\nfunction combine(stdin: string, stdout: string, stderr: string): string => Streams { stdin, stdout, stderr }.stdin + stdout + stderr")
  Assert.stringContains(result.header, "std::string stdin_;")
  Assert.stringContains(result.header, "std::string stdout_;")
  Assert.stringContains(result.header, "std::string stderr_;")
  Assert.stringContains(result.header, "const std::string& stdin_")
  Assert.stringContains(result.header, "const std::string& stdout_")
  Assert.stringContains(result.header, "const std::string& stderr_")
  Assert.stringContains(result.source, "->stdin_")
  Assert.stringContains(result.source, "+ stdout_")
  Assert.stringContains(result.source, "+ stderr_")
}

export function testPreservesPlatformStdioNamesAtNativeInteropBoundary(): none {
  result := emit("import class NativeStreams from \"native.hpp\" as native::Streams { stdout(): string\nstderr(): string\nstatic stdin(): string }\nfunction combine(streams: NativeStreams): string => streams.stdout() + streams.stderr() + NativeStreams.stdin()")
  Assert.stringContains(result.source, "streams->stdout()")
  Assert.stringContains(result.source, "streams->stderr()")
  Assert.stringContains(result.source, "::native::Streams::stdin()")
  Assert.stringNotContains(result.source, "streams->stdout_()")
  Assert.stringNotContains(result.source, "streams->stderr_()")
  Assert.stringNotContains(result.source, "::native::Streams::stdin_()")
}

export function testReturningThisRetainsOwningSharedPointer(): none {
  result := emit("class Builder { chain(): Builder => this }")
  Assert.equal(result.header.contains("public std::enable_shared_from_this<Builder>"), true)
  Assert.equal(result.source.contains("return this->shared_from_this();"), true)
  Assert.equal(result.source.contains("[](Builder*) {}"), false)
}

export function testFieldlessClassHasPublicDefaultConstructor(): none {
  result := emit("class Marker {}\nfunction make(): Marker => Marker {}")
  Assert.equal(result.header.contains("Marker() {}"), true)
}

export function testEmitsImportedFieldlessClassCallAsSharedPointer(): none {
  result := emitSources([
    SourceFile { path: "/main.do", source: "import { Marker } from \"./marker\"\nfunction makePositional(): Marker => Marker()" },
    SourceFile { path: "/marker.do", source: "export class Marker {}" },
  ], "/main.do")
  Assert.equal(result.source.contains("makePositional() {\n    return std::make_shared<::app_marker_::Marker>"), true)
}

export function testMaterializesCallerDefaultsAtPackageRelativeCallSite(): none {
  source := "function debug(source: SourceLocation = @caller): string => source.fileName\n" +
    "class Marker {\n" +
    "  source: SourceLocation\n" +
    "  static constructor(source: SourceLocation = @caller): Marker => Marker { source }\n" +
    "}\n" +
    "function wrapper(): string {\n" +
    "  ignored := debug()\n" +
    "  marker := Marker {}\n" +
    "  return marker.source.fileName\n" +
    "}\n"
  path := "/workspace/assert/tests/caller.test.do"
  analysis := createAnalyzer([SourceFile { path, source }]).analyze(path)
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis).check(path)
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  configureModuleNamespaces([
    ModuleNamespaceMapping { logicalPrefix: "/workspace/assert", packageName: "std/assert" },
  ])
  emitted := emitModuleGraph(analysis, path).modules[0].source
  configureModuleNamespaces([])

  Assert.equal(emitted.contains("SourceLocation>(std::string(\"tests/caller.test\"), 7, std::string(\"wrapper\"))"), true)
  Assert.equal(emitted.contains("SourceLocation>(std::string(\"tests/caller.test\"), 8, std::string(\"wrapper\"))"), true)
}

function findProgram(analysis: AnalysisResult, path: string): Program | none {
  for module of analysis.modules { if module.path == path { return module.program } }
  return none
}

export function testConstructionPanicsWhenConstructorAttachmentIsMissing(): none {
  source := "class Widget { value: int\nstatic constructor(value: int): Widget => Widget { value } }\nwidget := Widget { value: 1 }\nprintln(\"\")"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(hasErrorDiagnostics(createChecker(analysis, "/main.do").check("/main.do").diagnostics), false)
  program := findProgram(analysis, "/main.do")!
  case program.statements[1] {
    binding: ImmutableBinding -> {
      case binding.value {
        construct: ConstructExpression -> { construct.resolvedConstructor = none }
        _ -> { panic("expected a construct expression") }
      }
    }
    _ -> { panic("expected an immutable binding") }
  }

  result := catchPanic(=> emitModule(program, "main"))
  case result {
    failure: Failure<string> -> { Assert.equal(failure.error.contains("has no resolved constructor"), true) }
    _ -> { panic("expected missing constructor metadata to panic") }
  }
}

export function testConstructionPanicsWhenRequiredFieldIsMissing(): none {
  source := "class Widget { value: int }\nwidget := Widget { value: 1 }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(hasErrorDiagnostics(createChecker(analysis).check("/main.do").diagnostics), false)
  program := findProgram(analysis, "/main.do")!
  case program.statements[1] {
    binding: ImmutableBinding -> {
      case binding.value {
        construct: ConstructExpression -> { construct.args = [] }
        _ -> { panic("expected a construct expression") }
      }
    }
    _ -> { panic("expected an immutable binding") }
  }

  result := catchPanic(=> emitModule(program, "main"))
  case result {
    failure: Failure<string> -> { Assert.equal(failure.error.contains("is missing required field 'value'"), true) }
    _ -> { panic("expected missing required field to panic") }
  }
}

export function testKeepsHeaderAndSourceSeparate(): none {
  result := emit("function add(a: int, b: int): int => a + b\nfunction main(): int => add(2, 3)")
  Assert.equal(result.header.contains("int32_t add(int32_t a, int32_t b);"), true)
  Assert.equal(result.header.contains("return a + b"), false)
  Assert.equal(result.source.contains("int32_t add(int32_t a, int32_t b)"), true)
  Assert.equal(result.source.contains("doof::detail::ApplicationDomain::shared()"), true)
  Assert.equal(result.source.contains("doof::detail::ActiveActorScope __doof_application_scope"), true)
  Assert.equal(result.source.contains("return main_::doof_main();"), true)
}

export function testEmitsNamedNativeConstructionThroughStaticConstructor(): none {
  result := emit("enum Endian { LittleEndian, BigEndian }\nimport class BlobBuilder from \"native.hpp\" as native::BlobBuilder { static constructor(size: long = 0L, endianness: Endian = .LittleEndian): BlobBuilder }\nfunction build(): void { builder := BlobBuilder{endianness: .BigEndian} }")
  Assert.equal(result.source.contains("::native::BlobBuilder::constructor("), true)
  Assert.equal(result.source.contains("Endian::BigEndian"), true)
}

export function testEmitsNamedDoofConstructionThroughStaticConstructor(): none {
  result := emit("class Widget { value: int\nstatic constructor(value: int): Widget => Widget { value } }\nfunction build(): void { widget := Widget{value: 7} }")
  Assert.equal(result.source.contains("Widget::constructor(7)"), true)
}

export function testSpecializesGenericResultCasePatterns(): none {
  result := emitMonomorphized("function failed<T, E>(result: Result<T, E>): bool => case result { _: Success -> false, _: Failure -> true }\nfunction main(): bool => failed<int, string>(Failure { error: \"no\" })")
  Assert.equal(result.source.contains("doof::Success<int32_t>"), true)
  Assert.equal(result.source.contains("doof::Failure<std::string>"), true)
  Assert.equal(result.source.contains("doof::Success<T>"), false)
  Assert.equal(result.source.contains("doof::Failure<E>"), false)
}

export function testEmitsActorCreationCallsPromiseAndRetirement(): none {
  result := emit("class Worker { let value: int\nfunction add(amount: int): int { this.value = this.value + amount\nreturn this.value } }\nfunction main(): int { worker := Actor<Worker>(1)\nfirst := worker.add(2)\npromise := async worker.add(3)\nsecond := try! promise.get()\nstate := retire worker\nreturn first + second + state.value }")
  Assert.equal(result.source.contains("std::make_shared<doof::Actor<Worker>>(Worker{1})"), true)
  Assert.equal(result.source.contains("->template call_sync<int32_t>"), true)
  Assert.equal(result.source.contains("->template call_async<int32_t>"), true)
  Assert.equal(result.source.contains("promise.get()"), true)
  Assert.equal(result.source.contains("worker->retire()"), true)
}

export function testEmitsAsyncValueBlocksWithDecoratedCaptures(): none {
  source := "function run(input: int): Promise<int[]> { offset := 2\nreturn async { let values = [input, offset]\nvalues.push(5)\nyield values } }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  isolation := validateIsolationEffects(analysis)
  Assert.equal(hasErrorDiagnostics(isolation), false)
  result := emitModule(findProgram(analysis, "/main.do")!, "main")
  Assert.stringContains(result.header, "doof::Promise<std::shared_ptr<std::vector<int32_t>>> run")
  Assert.stringContains(result.source, "doof::submit_async<std::shared_ptr<std::vector<int32_t>>>([input, offset]()")
  Assert.stringContains(result.source, "return values;")
}

export function testEmitsFirstCompletedPromiseExtraction(): none {
  result := emit("function take(promises: Promise<int>[]): Result<int, string> => promises.takeFirstCompleted()")
  Assert.stringContains(result.source, "doof::promise_take_first_completed(promises)")
}

export function testEmitsNoneAsyncBlocksAsVoidTasks(): none {
  source := "function run(): Promise<none> => async { println(\"done\")\nyield none }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  checked := createChecker(analysis, "/main.do").check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)
  Assert.equal(hasErrorDiagnostics(validateIsolationEffects(analysis)), false)
  result := emitModule(findProgram(analysis, "/main.do")!, "main")
  Assert.stringContains(result.source, "doof::submit_async<void>([]() -> void")
  Assert.stringContains(result.source, "return;")
}

export function testEmitsIsolatedAsyncFunctionCalls(): none {
  result := emit("function compute(value: int): int => value * 2\nfunction run(value: int): Promise<int> => async compute(value)")
  Assert.stringContains(result.source, "doof::submit_async<int32_t>([=]() -> int32_t { return compute(value); })")

  noneResult := emit("function notify(value: int): none { println(value) }\nfunction run(value: int): Promise<none> => async notify(value)")
  Assert.stringContains(noneResult.source, "doof::submit_async<void>([=]() { notify(value); })")
}

export function testTryBangPanicIncludesOriginAndStringFailure(): none {
  result := emitMonomorphized("function load(): Result<int, string> => Failure { error: \"disk failed\" }\nfunction main(): int => try! load()")
  Assert.stringContains(result.source, "doof::panic_at(\"main\", 2, std::string(\"try! failed\") + std::string(\": \") + doof::failure_error(_try_value))")

  enumFailure := emitMonomorphized("enum Problem { Broken }\nfunction load(): Result<int, Problem> => Failure { error: Problem.Broken }\nfunction main(): int => try! load()")
  Assert.stringContains(enumFailure.source, "doof::panic_at(\"main\", 3, std::string(\"try! failed\"))")
}

export function testActorCreationUsesTrailingFieldDefaults(): none {
  result := emit("class Worker { values: int[] = []\nlimit: int = 4 }\nfunction create(): Actor<Worker> => Actor<Worker>()")
  Assert.equal(result.header.contains("Worker(std::shared_ptr<std::vector<int32_t>> values = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), int32_t limit = 4)"), true)
  Assert.equal(result.source.contains("std::make_shared<doof::Actor<Worker>>(Worker{})"), true)
}

export function testActorCallsUseConcreteGenericReturnTypes(): none {
  result := emitMonomorphized("class Sender<T> { readonly value: T }\nclass Receiver<T> { readonly value: T }\nclass Worker { function open(): Tuple<Sender<int>, Receiver<int> > => (Sender { value: 1 }, Receiver { value: 2 }) }\nfunction main(): int { worker := Actor<Worker>()\n(sender, receiver) := worker.open()\nretired := retire worker\nreturn sender.value + receiver.value }")
  Assert.equal(result.source.contains("call_sync<std::tuple<std::shared_ptr<Sender__int>, std::shared_ptr<Receiver__int>>>"), true)
  Assert.equal(result.source.contains("Sender<int32_t>"), false)
  Assert.equal(result.source.contains("Receiver<int32_t>"), false)
}

export function testEmitsVoidActorCallsAndPromiseAnnotation(): none {
  result := emit("class Worker { let value: int\nfunction set(value: int): void { this.value = value } }\nfunction create(): Actor<Worker> => Actor<Worker>(0)\nfunction run(worker: Actor<Worker>): Promise<void> => async worker.set(2)")
  Assert.equal(result.header.contains("std::shared_ptr<doof::Actor<Worker>> create()"), true)
  Assert.equal(result.header.contains("doof::Promise<void> run"), true)
  Assert.equal(result.source.contains("call_async<void>"), true)
}

export function testMainWrapperReportsPanicsForEverySupportedSignature(): none {
  intMain := emit("function main(): int => 0").source
  voidMain := emit("function main(): void { }").source
  intArgsMain := emit("function main(args: string[]): int => args.length").source
  voidArgsMain := emit("function main(args: string[]): void { println(string(args.length)) }").source

  for source of [intMain, voidMain, intArgsMain, voidArgsMain] {
    Assert.equal(source.contains("catch (const doof::Panic& _panic)"), true)
    Assert.equal(source.contains("std::cerr << \"panic: \" << _panic.what() << std::endl;"), true)
    Assert.equal(source.contains("std::abort();"), true)
  }
}

export function testEmitsCheckedCoreExpressions(): none {
  result := emit("function main(): int { values: int[] := [1, 2, 3]\nreturn values[1] + 4 }")
  Assert.equal(result.source.contains("std::make_shared<std::vector<int32_t>>"), true)
  Assert.stringContains(result.source, "doof::array_at(values, 1, \"<module>\", 2)")
  Assert.equal(result.source.contains("return ("), true)
}

export function testEmitsCheckedCollectionIndexReads(): none {
  result := emit("function readArray(values: int[], index: int): int => values[index]\nfunction readString(value: string, index: int): char => value[index]\nfunction readMap(values: Map<string, int>, key: string): int => values[key]")
  Assert.stringContains(result.source, "doof::array_at(values, index, \"<module>\", 1)")
  Assert.stringContains(result.source, "doof::string_at(value, index, \"<module>\", 2)")
  Assert.stringContains(result.source, "doof::map_at(values, key, \"<module>\", 3)")
  Assert.stringNotContains(result.source, "(*values)[index]")
  Assert.stringNotContains(result.source, "value[index]")
  Assert.stringNotContains(result.source, "(*values)[key]")
}

export function testEmitsCheckedBooleanArrayIndexReadsAndWrites(): none {
  result := emit("function settle(settled: bool[], index: int): bool { if settled[index] { return false }\nsettled[index] = true\nreturn settled[index] }")
  Assert.stringContains(result.source, "if (doof::array_at(settled, index, \"<module>\", 1))")
  Assert.stringContains(result.source, "doof::array_at(settled, index, \"<module>\", 2) = true")
  Assert.stringContains(result.source, "return doof::array_at(settled, index, \"<module>\", 3)")
}

export function testEmitsSafeCollectionIndexWrites(): none {
  result := emit("function writeArray(values: int[], index: int): none { values[index] = 7 }\nfunction writeMap(values: Map<string, int>, key: string): none { values[key] = 7 }")
  Assert.stringContains(result.source, "doof::array_at(values, index, \"<module>\", 1) = 7")
  Assert.stringContains(result.source, "doof::map_index(values, key, \"<module>\", 2) = 7")
  Assert.stringNotContains(result.source, "(*values)[index]")
  Assert.stringNotContains(result.source, "(*values)[key]")
}

export function testPreservesFullFloatingPointLiteralText(): none {
  result := emit("function value(): double => 1.4142135623730951")
  Assert.equal(result.source.contains("1.4142135623730951"), true)
}

export function testEmitsArrayAndStringSearchMembers(): none {
  result := emit("function main(): int { values := [1, 2, 3]\ntext := \"hello\"\nif values.contains(2) && text.contains(\"ell\") { return values.indexOf(3) + text.indexOf(\"e\") }\nreturn 0 }")
  Assert.equal(result.source.contains("doof::array_contains(values, 2"), true)
  Assert.equal(result.source.contains("doof::array_indexOf(values, 3"), true)
  Assert.equal(result.source.contains("doof::string_contains(text, "), true)
  Assert.equal(result.source.contains("doof::string_indexOf(text, "), true)
}

export function testEmitsTrimStartAssignmentInsideConditional(): none {
  result := emit("function normalize(value: string, shouldTrim: bool): string { let result = value\nif shouldTrim { result = result.trimStart() }\nreturn result }")
  Assert.equal(result.source.contains("result = doof::string_trimStart(result)"), true)
}

export function testEmitsStringPaddingMethodsWithUnicodeChars(): none {
  result := emit("function padded(value: string): string => value.padStart(4) + value.padEnd(4, '" + codePointToUtf8(233) + "')")
  Assert.stringContains(result.source, "doof::string_padStart(value, 4, U' ')")
  Assert.stringContains(result.source, "doof::string_padEnd(value, 4, U'\\u00E9')")
}

export function testEmitsShadowedBuiltinCallsFromResolvedBindings(): none {
  result := emit("class Parser { parse(value: string): int => value.length }\nfunction println(value: int): int => value + 1\nfunction catchPanic(value: int): int => value + 2\nfunction Success(value: int): int => value + 3\nfunction main(): int { byte := Parser {}\nreturn println(1) + catchPanic(2) + Success(3) + byte.parse(\"ok\") }")
  Assert.stringContains(result.source, "println(1)")
  Assert.stringContains(result.source, "catchPanic(2)")
  Assert.stringContains(result.source, "Success(3)")
  Assert.stringContains(result.source, "byte->parse")
  Assert.equal(result.source.contains("doof::println(1)"), false)
  Assert.equal(result.source.contains("doof::Success<int32_t>{ 3 }"), false)
}

export function testDoesNotHardwireAliasFieldInIfExpressions(): none {
  result := emit("class Label { alias: string }\nfunction choose(label: Label, first: bool): string => if first then \"first\" else label.alias")
  Assert.stringContains(result.source, "label->alias)")
  Assert.equal(result.source.contains("label->alias.value()"), false)
}

export function testEmitsNullableIfExpressionBranchesThroughCheckedResultType(): none {
  result := emit(
    "struct MovementRoute { distance: int }\n" +
    "function route(airborne: bool): MovementRoute | none => if airborne then none else MovementRoute { distance: 6 }\n" +
    "function count(missing: bool): int | none => if missing then none else 6",
  )
  Assert.stringContains(result.source, "[&]() -> std::optional<MovementRoute> { if (airborne) { return std::nullopt; } return MovementRoute{6}; }()")
  Assert.stringContains(result.source, "[&]() -> std::optional<int32_t> { if (missing) { return std::nullopt; } return 6; }()")
  Assert.equal(result.source.contains("airborne ? nullptr"), false)
}

export function testKeepsNullableNativePseudoFieldNamesAsMethodCalls(): none {
  result := emit("import class NativeNode from \"native.hpp\" as native::Node { kind(): string resolvedType(): string span(): int }\nfunction describe(node: NativeNode | none): string { if node != none { return node!.kind() + node!.resolvedType() + string(node!.span()) }\nreturn \"\" }")
  Assert.stringContains(result.source, "node->kind()")
  Assert.stringContains(result.source, "node->resolvedType()")
  Assert.stringContains(result.source, "node->span()")
  Assert.equal(result.source.contains("doof::kind(node)"), false)
  Assert.equal(result.source.contains("doof::resolved_type(node)"), false)
  Assert.equal(result.source.contains("doof::span(node)"), false)
}

export function testUnwrapsNullableEnumFieldsToTheirEnumValue(): none {
  result := emit(
    "enum Outcome { Victory, Defeat }\n" +
    "class State { let pending: Outcome | none = none }\n" +
    "function isVictory(outcome: Outcome): bool => outcome == Outcome.Victory\n" +
    "function checkField(state: State): bool => isVictory(state.pending!)\n" +
    "function checkLocal(pending: Outcome | none): bool => isVictory(pending!)",
  )
  Assert.stringContains(result.source, "isVictory(std::get<Outcome>(state->pending))")
  Assert.stringContains(result.source, "isVictory(std::get<Outcome>(pending))")
  Assert.equal(result.source.contains("isVictory(doof::unwrap_optional(state->pending))"), false)
}

export function testTreatsCompilerAstSpellingsAsOrdinaryNominalTypes(): none {
  result := emit("class Expression { kind: string\nresolvedType: string\nspan: int }\nfunction describe(value: Expression): string => value.kind + value.resolvedType + string(value.span)\nfunction missing(): Expression | none => none")
  Assert.stringContains(result.header, "std::shared_ptr<Expression>")
  Assert.stringContains(result.source, "value->kind")
  Assert.stringContains(result.source, "value->resolvedType")
  Assert.stringContains(result.source, "value->span")
  Assert.equal(result.header.contains("using Expression = std::variant"), false)
}

export function testPromotesShorthandConstructionFieldsByResolvedTypes(): none {
  result := emit("class Leaf {}\nclass Branch {}\ntype Node = Leaf | Branch\nclass Envelope { body: Node }\nfunction wrap(body: Leaf): Envelope => Envelope { body }")
  Assert.stringContains(result.source, "doof::variant_promote<std::variant<std::shared_ptr<Leaf>, std::shared_ptr<Branch>>>(body)")
}

export function testReusesNamedAliasesForRepeatedHeaderVariants(): none {
  result := emit(
    "class Leaf {}\nclass Branch {}\n" +
    "type Node = Leaf | Branch\n" +
    "class Pair { left: Node\nright: Node }\n" +
    "function choose(value: Node): Node => value",
  )
  spelling := "std::variant<std::shared_ptr<Leaf>, std::shared_ptr<Branch>>"
  Assert.stringContains(result.header, "using Node = " + spelling + ";")
  Assert.stringContains(result.header, "Node left;")
  Assert.stringContains(result.header, "Node choose(const Node& value);")
  Assert.equal(result.header.split(spelling).length, 2)
  // Source definitions remain free to use the canonical structural spelling;
  // a C++ alias denotes exactly the same declaration type.
  Assert.stringContains(result.source, spelling)
}

export function testSynthesizesNamesForRepeatedAnonymousHeaderVariants(): none {
  result := emit("class Left {}\nclass Right {}\nclass Pair { left: Left | Right\nright: Left | Right }")
  spelling := "std::variant<std::shared_ptr<Left>, std::shared_ptr<Right>>"
  Assert.stringContains(result.header, "using __type1 = " + spelling + ";")
  Assert.stringContains(result.header, "__type1 left;")
  Assert.stringContains(result.header, "__type1 right;")
}

export function testProjectsNamedAliasesIntoConsumerHeaders(): none {
  sources := [
    SourceFile {
      path: "/tree.do",
      source: "export class Leaf {}\nexport class Branch {}\nexport type Node = Leaf | Branch\nexport class Pair { left: Node\nright: Node }",
    },
    SourceFile { path: "/main.do", source: "import { Pair } from \"./tree\"\nfunction pass(value: Pair): Pair => value" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/tree.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/main.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  let header = ""
  for module of graph.modules { if module.modulePath == "/main.do" { header = module.header } }
  Assert.stringContains(header, "using Node = std::variant<std::shared_ptr<Leaf>, std::shared_ptr<Branch>>;")
  Assert.stringContains(header, "Node left;")
  Assert.stringContains(header, "Node right;")
  Assert.equal(header.contains("using __type"), false)
}

export function testIndexesAnonymousHeaderTypesAcrossProjectedNamespaces(): none {
  sources := [
    SourceFile { path: "/a.do", source: "export class ALeft {}\nexport class ARight {}\nexport class APair { left: ALeft | ARight\nright: ALeft | ARight }" },
    SourceFile { path: "/b.do", source: "export class BLeft {}\nexport class BRight {}\nexport class BPair { left: BLeft | BRight\nright: BLeft | BRight }" },
    SourceFile { path: "/main.do", source: "import { APair } from \"./a\"\nimport { BPair } from \"./b\"\nfunction first(a: APair, b: BPair): APair => a" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/a.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/b.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/main.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  let header = ""
  for module of graph.modules { if module.modulePath == "/main.do" { header = module.header } }
  Assert.equal(header.split("using __type1 =").length, 2)
  Assert.equal(header.split("using __type2 =").length, 2)
  Assert.stringContains(header, "namespace app_a_ {\n    using __type1 =")
  Assert.stringContains(header, "namespace app_b_ {\n    using __type2 =")
}

export function testDoesNotHoistSingleOrValueBearingHeaderVariants(): none {
  single := emit("class Left {}\nclass Right {}\nfunction choose(value: Left | Right): none {}")
  Assert.equal(single.header.contains("using __type"), false)
  valueBearing := emit("struct Left { value: int }\nstruct Right { value: int }\nclass Pair { left: Left | Right\nright: Left | Right }")
  Assert.equal(valueBearing.header.contains("using __type"), false)
}

export function testEmitsArbitrarySharedUnionMembersFromResolvedTypes(): none {
  result := emit("class Left { value: int\nread(): int => value }\nclass Right { value: int\nread(): int => value }\ntype Either = Left | Right\ntype MaybeEither = Left | Right | none\nfunction total(item: Either): int => item.value + item.read()\nfunction maybeTotal(item: MaybeEither): int => item.value + item.read()")
  Assert.stringContains(result.source, "std::visit([](auto&& _obj) { return _obj->value; }, item)")
  Assert.stringContains(result.source, "std::visit([&](auto&& _obj) { return _obj->read(); }, item)")
  Assert.stringContains(result.source, "std::visit([](auto&& _obj) { return _obj->value; }, doof::unwrap_optional(item))")
  Assert.stringContains(result.source, "std::visit([&](auto&& _obj) { return _obj->read(); }, doof::unwrap_optional(item))")
}

export function testEmitsMapSizeAsContainerCall(): none {
  result := emit("function size(values: readonly Map<string, int>): int => values.size\nfunction keys(values: Map<string, int>): string[] => values.keys()\nfunction snapshot(values: Map<string, int>): readonly Map<string, int> => values.cloneReadonly()\nfunction freeze(values: Map<string, int>): readonly Map<string, int> => values.drainToReadonly()")
  Assert.equal(result.source.contains("values->size()"), true)
  Assert.equal(result.source.contains("doof::map_keys(values"), true)
  Assert.equal(result.source.contains("doof::map_cloneReadonly(values"), true)
  Assert.equal(result.source.contains("doof::map_drainToReadonly(values"), true)
}

export function testEmitsDeprecatedBuildReadonlyThroughDrainHelper(): none {
  result := emit("function freeze(values: int[]): readonly int[] => values.buildReadonly()")
  Assert.stringContains(result.source, "doof::array_drainToReadonly(values")
}

export function testWrapsMapSetArgumentsForJsonValueMaps(): none {
  result := emit("function fill(receipt: Map<string, JsonValue>, version: int, name: string): void { receipt.set(\"schemaVersion\", version)\nreceipt.set(\"name\", name) }\nfunction widen(value: int): long => long(value)")
  Assert.stringContains(result.source, "doof::map_set(receipt, std::string(\"schemaVersion\"), doof::json_value(version)")
  Assert.stringContains(result.source, "doof::map_set(receipt, std::string(\"name\"), doof::json_value(name)")
  Assert.stringContains(result.source, "static_cast<int64_t>(value)")
  Assert.equal(result.source.contains("static_cast<int64_t>(doof::json_value(value))"), false)
}

export function testInvokesCallbackValuedMemberThroughCallMethod(): none {
  result := emit("class Route { handler: (value: int): int\nget(value: int): int => value }\nfunction invoke(route: Route): int => route.handler(1) + route.get(1)")
  Assert.equal(result.source.contains("route->handler.call(1)"), true)
  Assert.equal(result.source.contains("route->get(1)"), true)
  Assert.equal(result.source.contains("route->get.call(1)"), false)
}

export function testInvokesCallbackFieldAfterPostfixNullableStructUnwrap(): none {
  result := emit("struct Handler { callback: (value: int): int }\nfunction findHandler(): Handler | none => Handler { callback: (value: int): int => value + 1 }\nfunction invoke(): int { handler := findHandler()\nif handler != none { return handler!.callback(41) }\nreturn 0 }")
  Assert.stringContains(result.source, "handler->callback.call(41)")
  Assert.equal(result.source.contains("handler->callback(41)"), false)
}

export function testEmitsInterpolationInSourceOrder(): none {
  result := emit("function first(): int => 1\nfunction second(): int => 2\nfunction render(): string => \"a=\${first()}, b=\${second()}\"")
  Assert.stringContains(result.source, "std::string _interpolation = \"a=\"")
  firstPosition := result.source.indexOf("doof::to_string(first())")
  secondPosition := result.source.indexOf("doof::to_string(second())")
  Assert.equal(firstPosition >= 0, true)
  Assert.equal(secondPosition > firstPosition, true)
  Assert.stringContains(result.source, "return _interpolation; }())")
}

export function testFoldsConstantStringConcatenation(): none {
  result := emit("function constant(): string => \"alpha\" + \"\\n\" + \"beta\"\nfunction mixed(value: string): string => \"left\" + \"-\" + value")
  Assert.stringContains(result.source, "return std::string(\"alpha\\nbeta\");")
  Assert.stringNotContains(result.source, "std::string(\"alpha\") + std::string")
  Assert.stringContains(result.source, "std::string(\"left-\") + value")
}

export function testOrdersNamedCallbackArgumentsByFunctionType(): none {
  result := emit("function invoke(callback: (left: int, right: int): int): int => callback{right: 2, left: 1}")
  Assert.equal(result.source.contains("callback.call(1, 2)"), true)
  Assert.equal(result.source.contains("callback.call(2, 1)"), false)
}

export function testContextuallyPromotesLambdaReturnIntoCallbackUnion(): none {
  result := emit("class Response {}\nclass Upgrade {}\ntype Outcome = Response | Upgrade\nclass Router { websocket(handler: (): Outcome): void {} }\nfunction register(router: Router): void { router.websocket((): Response => Response {}) }")
  Assert.equal(result.source.contains("doof::callback<std::variant<std::shared_ptr<Response>, std::shared_ptr<Upgrade>>()>([]() -> std::variant<std::shared_ptr<Response>, std::shared_ptr<Upgrade>>"), true)
  Assert.equal(result.source.contains("return doof::variant_promote<std::variant<std::shared_ptr<Response>, std::shared_ptr<Upgrade>>>(std::make_shared<Response>"), true)
}

export function testEmitsArrayCallbackMembers(): none {
  result := emit("class Item { value: int }\nfunction values(items: Item[]): int[] => items.map(=> it.value)\nfunction positive(values: int[]): int[] => values.filter(=> it > 0)")
  Assert.equal(result.source.contains("doof::array_map(items"), true)
  Assert.equal(result.source.contains("doof::array_filter(values"), true)
}

export function testEmitsReadonlyArrayAndGenericNamedCall(): none {
  result := emitMonomorphized("function create<T>(value: T, count: int = 1): T => value\nfunction main(): string { values := readonly [1, 2]\nreturn create<string>{ value: \"ok\" } }")
  Assert.equal(result.header.contains("create__string"), true)
  Assert.equal(result.header.contains("T create("), false)
  Assert.equal(result.source.contains("create__string(std::string(\"ok\"), 1)"), true)
  Assert.equal(result.source.contains("std::make_shared<std::vector<int32_t>>"), true)
}

export function testEmitsGenericTupleDestructuring(): none {
  result := emitMonomorphized("function pair<T>(value: T): Tuple<T, T> => (value, value)\nfunction main(): int { (first, second) := pair<int>(1)\nreturn first + second }")
  Assert.equal(result.source.contains("pair__int(1)"), true)
  Assert.equal(result.source.contains("std::get<0>(_destructure_"), true)
  Assert.equal(result.source.contains("std::get<1>(_destructure_"), true)
}

export function testEmitsDeclarationElseNarrowingAndCapture(): none {
  result := emit("function load(): Result<int, string> => Success { value: 4 }\nfunction main(): int { value := load() else error { println(error)\nreturn 1 }\nreturn value }")
  Assert.equal(result.source.contains("if (doof::is_failure(_binding_value_"), true)
  Assert.equal(result.source.contains("const auto error = doof::failure_error(_binding_value_"), true)
  Assert.equal(result.source.contains("const auto value = doof::success_value(_binding_value_"), true)
}

export function testKeepsDeclarationElseStructBindingsShallowImmutable(): none {
  result := emit(
    "struct Evaluation { readonly skulls: int\nhasSkull(): bool => skulls > 0 }\n" +
    "function evaluate(): Result<Evaluation, string> => Success(Evaluation { skulls: 1 })\n" +
    "function maybeEvaluate(): Evaluation | none => Evaluation { skulls: 1 }\n" +
    "function main(): bool { fromResult := evaluate() else { return false }\n" +
    "fromOptional := maybeEvaluate() else { return false }\n" +
    "return fromResult.hasSkull() && fromOptional.hasSkull() }",
  )
  Assert.stringContains(result.source, "auto fromResult = doof::success_value(_binding_value_")
  Assert.stringContains(result.source, "auto fromOptional = doof::unwrap_optional(_binding_value_")
  Assert.stringNotContains(result.source, "const auto fromResult")
  Assert.stringNotContains(result.source, "const auto fromOptional")
  Assert.stringContains(result.header, "bool hasSkull();")
  Assert.stringNotContains(result.header, "bool hasSkull() const;")
}

export function testEmitsPostfixBangResultUnwrap(): none {
  result := emit("function decode(): Result<string, string> => Success { value: \"ok\" }\nfunction main(): string => decode()!")
  Assert.equal(result.source.contains("if (doof::is_failure(_assert_value)) doof::panic(\"! failed\")"), true)
  Assert.equal(result.source.contains("return std::move(doof::success_value(_assert_value))"), true)
}

export function testEmitsResultStatusMethods(): none {
  result := emit("function load(): Result<int, string> => Failure { error: \"no\" }\nfunction main(): bool => load().isFailure() || load().isSuccess()")
  Assert.equal(result.source.contains("doof::is_failure(load())"), true)
  Assert.equal(result.source.contains("doof::is_success(load())"), true)
}

export function testEmitsResultUnwrapOrWithSingleEvaluation(): none {
  result := emit("function load(): Result<JsonValue, string> => Failure { error: \"no\" }\nfunction value(): JsonValue => load().unwrapOr(null)")
  Assert.stringContains(result.source, "auto _result_unwrap_")
  Assert.stringContains(result.source, "if (doof::is_failure(_result_unwrap_")
  Assert.stringContains(result.source, "return doof::json_value(nullptr);")
  Assert.stringContains(result.source, "return std::move(doof::success_value(_result_unwrap_")
}

export function testEmitsCoalescingWithSingleEvaluationAndCarrierSpecificChecks(): none {
  result := emit("function nullable(): int | none => 7\nfunction fallible(): Result<int, string> => Success(8)\nfunction fromNullable(): int => nullable() ?? 0\nfunction fromResult(): int => fallible() ?? 0")
  Assert.stringContains(result.source, "auto _coalesce_")
  Assert.stringContains(result.source, "= nullable(); if (doof::is_null(_coalesce_")
  Assert.stringContains(result.source, "= fallible(); if (doof::is_failure(_coalesce_")
  Assert.equal(result.source.contains("doof::is_null(fallible())"), false)
  Assert.equal(result.source.contains("doof::unwrap_optional(fallible())"), false)
}

export function testPromotesTryErrorsIntoWiderReturnUnion(): none {
  result := emit("function inner(): Result<int, string | int> => Failure(1)\nfunction outer(): Result<int, string | int | bool> { try value := inner()\nreturn Success(value) }")
  target := "std::variant<std::string, int32_t, bool>"
  Assert.stringContains(result.source, "doof::Failure<" + target + ">{doof::variant_promote<" + target + ">(doof::failure_error(_try_value_")
}

export function testEvaluatesComputedMapHasReceiverOnce(): none {
  result := emit("function values(): Map<string, int> => { key: 1 }\nfunction found(): bool => values().has(\"key\")")
  Assert.stringContains(result.source, "auto _map_has_")
  Assert.stringContains(result.source, "= values(); return _map_has_")
  Assert.equal(result.source.contains("values()->find"), false)
}

export function testEmitsTryValueDeclarationsWithMutability(): none {
  result := emit("struct Frozen { readonly value: int }\nfunction load(): Result<int, string> => Success { value: 1 }\nfunction loadFrozen(): Result<Frozen, string> => Success(Frozen { value: 2 })\nfunction run(): Result<int, string> { try const first = load()\ntry readonly second = load()\ntry let third = load()\ntry readonly frozen = loadFrozen()\nthird = third + first\nreturn Success { value: third + second + frozen.value } }")
  Assert.equal(result.source.contains("const auto first = doof::success_value("), true)
  Assert.equal(result.source.contains("const auto second = doof::success_value("), true)
  Assert.equal(result.source.contains("auto third = doof::success_value("), true)
  Assert.equal(result.source.contains("const auto frozen = doof::success_value("), true)
}

export function testKeepsTryStructBindingsShallowImmutableAcrossFailureContexts(): none {
  result := emit(
    "struct Evaluation { readonly skulls: int\nhasSkull(): bool => skulls > 0 }\n" +
    "function evaluate(): Result<Evaluation, string> => Success(Evaluation { skulls: 1 })\n" +
    "function propagated(): Result<bool, string> { try propagatedValue := evaluate()\nreturn Success(propagatedValue.hasSkull()) }\n" +
    "function captured(): bool { ignored := catch { try capturedValue := evaluate()\nif capturedValue.hasSkull() { println(\"skull\") } }\nreturn ignored == none }\n" +
    "try scriptValue := evaluate()\nprintln(string(scriptValue.hasSkull()))",
  )
  Assert.stringContains(result.source, "auto propagatedValue = doof::success_value(_try_value_")
  Assert.stringContains(result.source, "auto capturedValue = doof::success_value(_try_value_")
  Assert.stringContains(result.source, "auto scriptValue = doof::success_value(_try_value_")
  Assert.stringNotContains(result.source, "const auto propagatedValue")
  Assert.stringNotContains(result.source, "const auto capturedValue")
  Assert.stringNotContains(result.source, "const auto scriptValue")
}

export function testEmitsWithBindingsInOrderedLexicalScope(): none {
  result := emit("function main(): int { with base := 20, doubled := base * 2 { return doubled + 2 }\nreturn 0 }")
  Assert.equal(result.source.contains("    {\n        const auto base = 20;\n        const auto doubled = (base * 2);\n        return (doubled + 2);\n    }"), true)
}

export function testEmitsTypedWithUnionUsingItsVariantCarrier(): none {
  result := emit("class Left { value: int }\nclass Right { value: int }\nfunction main(): int { with value: Left | Right := Left { value: 42 } { return case value { left: Left -> left.value right: Right -> right.value } }\nreturn 0 }")
  Assert.equal(result.source.contains("const std::variant<std::shared_ptr<Left>, std::shared_ptr<Right>> value = doof::variant_promote<"), true)
}

export function testEmitsYieldingCaseExpressionBlocks(): none {
  result := emit("function describe(value: int): string => case value { 0 -> { yield \"zero\" } _ -> { yield \"other\" } }")
  Assert.equal(result.source.contains("return std::string(\"zero\");"), true)
  Assert.equal(result.source.contains("return std::string(\"other\");"), true)
}

export function testEmitsNoneReturningCaseExpressionArms(): none {
  result := emit("function verify(condition: bool): none {}\nfunction check(condition: bool): none => case condition { true -> verify(true), _ -> verify(false) }\nfunction checkReturned(condition: bool): none { return case condition { true -> verify(true), _ -> verify(false) } }")
  Assert.stringContains(result.source, "verify(true);\n        return std::monostate{};")
  Assert.stringContains(result.source, "verify(false);\n        return std::monostate{};")
  Assert.equal(result.source.contains("return [&]() -> std::monostate"), false)
}

export function testPromotesNarrowVariantReturnsIntoWiderUnions(): none {
  result := emit("class First { value: int }\nclass Second { value: int }\nfunction widen(value: First): First | Second { return value }")
  Assert.equal(result.source.contains("doof::variant_promote<std::variant<std::shared_ptr<First>, std::shared_ptr<Second>>>(value)"), true)
}

export function testPromotesScalarAlternativesIntoNullableVariantFields(): none {
  result := emit("class Left {}\nclass Right {}\ntype Choice = Left | Right\nclass Box { choice: Choice | null }\nfunction explicit(left: Left): Box => Box { choice: left }\nfunction shorthand(choice: Left): Box => Box { choice }")
  target := "std::variant<std::monostate, std::shared_ptr<Left>, std::shared_ptr<Right>>"
  Assert.equal(result.source.contains("doof::variant_promote<" + target + ">(left)"), true)
  Assert.equal(result.source.contains("doof::variant_promote<" + target + ">(choice)"), true)
  Assert.equal(result.source.contains("doof::optional_value(left)"), false)
  Assert.equal(result.source.contains("doof::optional_value(choice)"), false)
}

export function testEmitsNullableAndDiscardDeclarationElse(): none {
  result := emit("function maybe(): string | null => \"ok\"\nfunction save(): Result<void, string> => Success()\nfunction main(): int { name := maybe() else { return 1 }\n_ := save() else error { println(error) }\nreturn name.length }")
  Assert.equal(result.source.contains("if (doof::is_null(_binding_value_"), true)
  Assert.equal(result.source.contains("const auto name = doof::unwrap_optional(_binding_value_"), true)
  Assert.equal(result.source.contains("const auto _ ="), false)
}

export function testEmitsClassesMethodsAndConstruction(): none {
  result := emit("class Point { x: int\nfunction double(): int => x * 2 }\nfunction main(): int { point := Point { x: 4 }\nreturn point.double() }")
  Assert.equal(result.header.contains("struct Point"), true)
  Assert.equal(result.header.contains("int32_t x;"), true)
  Assert.equal(result.header.contains("int32_t double();"), true)
  Assert.equal(result.source.contains("int32_t Point::double()"), true)
  Assert.equal(result.source.contains("this->x"), true)
  Assert.equal(result.source.contains("std::make_shared<Point>(4)"), true)
}

export function testEmitsClassDestructorBody(): none {
  result := emit("class Resource { value: int = 1\ndestructor { println(\"closed\") } }\nfunction open(): Resource => Resource {}")
  Assert.equal(result.header.contains("~Resource()"), true)
  Assert.equal(result.header.contains("doof::println(std::string(\"closed\"));"), true)
  Assert.equal(result.source.contains("std::make_shared<Resource>(1)"), true)
  Assert.equal(result.source.contains("std::make_shared<Resource>(Resource{"), false)
}

export function testEmitsStrictPrimitiveJsonDeserialization(): none {
  result := emit("class Config { name: string\nenabled: bool\ncount: int = 10\nnotes: string | null = null }\nfunction parse(value: JsonValue): Result<Config, string> => Config.fromJsonValue(value)")
  Assert.equal(result.header.contains("static doof::Result<std::shared_ptr<Config>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);"), true)
  Assert.equal(result.source.contains("const auto* _object = doof::json_as_object(_json);"), true)
  Assert.equal(result.source.contains("Missing required field \\\"name\\\""), true)
  Assert.equal(result.source.contains("Field \\\"enabled\\\" expected boolean but got"), true)
  Assert.equal(result.source.contains("_field_count = 10;"), true)
  Assert.equal(result.source.contains("_field_notes = std::optional<std::string>{std::nullopt};"), true)
  Assert.equal(result.source.contains("doof::json_is_null(_iterator_notes->second)"), true)
  Assert.equal(result.source.contains("std::make_shared<Config>(_field_name, _field_enabled, _field_count.value(), _field_notes.value())"), true)
}

export function testDeserializesDefaultedStructFieldsWithoutDefaultConstruction(): none {
  result := emit("struct Depth { mode: int }\nclass Pass { depth: Depth = Depth { mode: 0 } }\nfunction parse(value: JsonValue): Result<Pass, string> => Pass.fromJsonValue(value)")
  Assert.stringContains(result.source, "std::optional<Depth> _field_depth;")
  Assert.stringContains(result.source, "std::make_shared<Pass>(_field_depth.value())")
  Assert.equal(result.source.contains("Depth _field_depth;"), false)
}

export function testEmitsStructJsonDeserializationByValue(): none {
  result := emit("struct Point { x: int\ny: double }\nfunction parse(value: JsonValue): Result<Point, string> => Point.fromJsonValue(value)")
  Assert.equal(result.header.contains("static doof::Result<Point, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);"), true)
  Assert.equal(result.source.contains("return doof::Success<Point>{Point{_field_x, _field_y}};"), true)
  Assert.equal(result.source.contains("std::make_shared<Point>"), false)
}

export function testEmitsJsonCollectionSerializationAndDeserialization(): none {
  result := emit("class Payload { items: JsonValue[]\nvalues: Map<string, JsonValue> }\nfunction serialize(value: Payload): JsonObject => value.toJsonObject()")
  Assert.equal(result.header.contains("doof::JsonObject toJsonObject() const;"), true)
  Assert.equal(result.header.contains("fromJsonValue"), false)
  Assert.equal(result.source.contains("doof::json_value(this->items)"), true)
  Assert.equal(result.source.contains("doof::json_value(this->values)"), true)
}

export function testEmitsNullableJsonObjectSerialization(): none {
  result := emit("class Config { values: JsonObject | null = null }\nfunction write(value: Config): JsonObject => value.toJsonObject()")
  Assert.equal(result.source.contains("this->values ? doof::json_value(this->values) : doof::json_value(nullptr)"), true)
  Assert.equal(result.header.contains("fromJsonValue"), false)
}

export function testDoesNotEmitAutomaticJsonForUnusedEligibleType(): none {
  result := emit("class Point { x: int\ny: int }\nfunction main(): int => Point { x: 1, y: 2 }.x")
  Assert.stringNotContains(result.header, "toJsonObject")
  Assert.stringNotContains(result.header, "fromJsonValue")
  Assert.stringNotContains(result.source, "Point::toJsonObject")
  Assert.stringNotContains(result.source, "Point::fromJsonValue")
}

export function testKeepsAutomaticJsonDemandDirectionSpecificAndTransitive(): none {
  encoded := emit("class Inner { value: int }\nclass Outer { inner: Inner }\nfunction encode(value: Outer): JsonObject => value.toJsonObject()")
  Assert.stringContains(encoded.source, "Outer::toJsonObject")
  Assert.stringContains(encoded.source, "Inner::toJsonObject")
  Assert.stringNotContains(encoded.source, "Outer::fromJsonValue")
  Assert.stringNotContains(encoded.source, "Inner::fromJsonValue")

  decoded := emit("class Inner { value: int }\nclass Outer { inner: Inner }\nfunction decode(value: JsonValue): Result<Outer, string> => Outer.fromJsonValue(value)")
  Assert.stringContains(decoded.source, "Outer::fromJsonValue")
  Assert.stringContains(decoded.source, "Inner::fromJsonValue")
  Assert.stringNotContains(decoded.source, "Outer::toJsonObject")
  Assert.stringNotContains(decoded.source, "Inner::toJsonObject")
}

export function testDiscoversJsonDemandThroughGenericSpecialization(): none {
  result := emitMonomorphized("class Config { name: string }\nfunction decode<T: JsonSerializable>(value: JsonValue): Result<T, string> => T.fromJsonValue(value)\nfunction main(): int { config := decode<Config>({ name: \"ok\" }) else { return 0 }\nreturn config.name.length }")
  Assert.stringContains(result.source, "Config::fromJsonValue")
  Assert.stringNotContains(result.source, "Config::toJsonObject")
}

export function testDiscoversJsonDemandThroughGenericMethodTemplate(): none {
  result := emitMonomorphized("class Config { name: string }\nclass Decoder { function decode<T: JsonSerializable>(value: JsonValue): Result<T, string> => T.fromJsonValue(value) }\nfunction main(): int { config := Decoder {}.decode<Config>({ name: \"ok\" }) else { return 0 }\nreturn config.name.length }")
  Assert.stringContains(result.source, "Config::fromJsonValue")
  Assert.stringNotContains(result.source, "Config::toJsonObject")
}

export function testEngagesOuterPresenceForNullableJsonDefaults(): none {
  result := emit("class Config { notes: string | null = null }\nfunction read(value: JsonValue): Result<Config, string> => Config.fromJsonValue(value)")
  Assert.stringContains(result.source, "std::optional<std::optional<std::string>> _field_notes;")
  Assert.stringContains(result.source, "_field_notes = std::optional<std::string>{std::nullopt};")
  Assert.stringContains(result.source, "_field_notes.value()")
}

export function testEmitsRecursiveAutomaticJsonTypes(): none {
  result := emit("enum Kind { One, Two }\nclass Point { x: double\ny: double }\nclass Payload { kind: Kind\nids: int[]\npoints: Point[]\nselected: Point | null = null }\nfunction encode(value: Payload): JsonObject => value.toJsonObject()\nfunction decode(value: JsonValue): Result<Payload, string> => Payload.fromJsonValue(value)")
  Assert.equal(result.header.contains("Kind_fromName"), true)
  Assert.equal(result.source.contains("this->kind"), true)
  Assert.equal(result.source.contains("for (const auto& _element : *this->ids)"), true)
  Assert.equal(result.source.contains("Point::fromJsonValue"), true)
  Assert.stringContains(result.source, "doof::json_decode_value(Point::fromJsonValue")
  Assert.stringContains(result.source, "catch (const doof::JsonDecodeError& _error)")
}

export function testEmitsUnicodeCharJsonConversionAndValidation(): none {
  result := emit("class Mark { value: char }\nfunction decode(value: JsonValue): Result<Mark, string> => Mark.fromJsonValue(value)\nfunction encode(value: Mark): JsonObject => value.toJsonObject()")
  Assert.stringContains(result.source, "doof::json_is_char(_iterator_value->second, _lenient)")
  Assert.stringContains(result.source, "doof::json_as_char(_iterator_value->second, _lenient)")
  Assert.stringContains(result.source, "doof::json_value(doof::char_to_utf8(this->value))")
  Assert.equal(result.source.contains("json_as_string(_iterator_value->second)[0]"), false)
}

export function testEmitsTupleAutomaticJsonTypes(): none {
  result := emit("class Point { x: int\ny: int }\nclass Payload { pair: Tuple<string, int>\npoint: Tuple<Point, bool>\noptional: Tuple<int, string> | null = null }\nfunction encode(value: Payload): JsonObject => value.toJsonObject()\nfunction decode(value: JsonValue): Result<Payload, string> => Payload.fromJsonValue(value)")
  Assert.stringContains(result.header, "doof::JsonObject toJsonObject() const;")
  Assert.stringContains(result.header, "fromJsonValue(const doof::JsonValue& _json")
  Assert.stringContains(result.source, "std::get<0>(this->pair)")
  Assert.stringContains(result.source, "std::get<1>(this->point)")
  Assert.stringContains(result.source, "std::make_tuple(")
  Assert.stringContains(result.source, "Point::fromJsonValue((*_tuple)[0], _lenient)")
  Assert.stringContains(result.source, "std::holds_alternative<std::monostate>(this->optional)")
  Assert.stringContains(result.source, "std::variant<std::monostate, std::tuple<int32_t, std::string>>{std::monostate{}}")
}

export function testEmitsStringMapAutomaticJsonTypes(): none {
  result := emit("class Point { x: int\ny: int }\nclass Payload { counts: Map<string, int>\npoints: Map<string, Point> }\nfunction encode(value: Payload): JsonObject => value.toJsonObject()\nfunction decode(value: JsonValue): Result<Payload, string> => Payload.fromJsonValue(value)")
  Assert.stringContains(result.source, "std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();")
  Assert.stringContains(result.source, "for (const auto& _entry : *this->counts)")
  Assert.stringContains(result.source, "doof::json_value(_entry.second)")
  Assert.stringContains(result.source, "std::make_shared<doof::ordered_map<std::string, std::shared_ptr<Point>>>()")
  Assert.stringContains(result.source, "Point::fromJsonValue(_entry.second, _lenient)")
}

export function testEmitsDiscriminatedInterfaceJsonDeserialization(): none {
  result := emit("interface Shape { area(): double }\nclass Circle implements Shape { const kind = \"circle\"\nradius: double\narea(): double => radius * radius }\nclass Rect implements Shape { const kind = \"rect\"\nwidth: double\nheight: double\narea(): double => width * height }\nfunction decode(value: JsonValue): Result<Shape, string> => Shape.fromJsonValue(value, true)")
  Assert.stringContains(result.header, "doof::Result<Shape, std::string> Shape_fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);")
  Assert.stringContains(result.source, "Shape_fromJsonValue(value, true)")
  Assert.stringContains(result.source, "_object->find(\"kind\")")
  Assert.stringContains(result.source, "if (_discriminator == \"circle\")")
  Assert.stringContains(result.source, "Circle::fromJsonValue(_json, _lenient)")
  Assert.stringContains(result.source, "Rect::fromJsonValue(_json, _lenient)")
  Assert.stringContains(result.source, "doof::Success<Shape>{Shape{doof::success_value(_result)}}")
  Assert.stringContains(result.header, "const std::string kind = std::string(\"circle\")")
  Assert.stringContains(result.source, "Field \\\"kind\\\" must be \\\"circle\\\"")
}

export function testEmitsDescriptionsMetadataSchemasAndInvoke(): none {
  result := emit("class Tool \"A tool.\" { count \"Current count.\": int = 0\nfunction run \"Runs it.\"(input \"The input.\": string): string => input }\nfunction invoke(tool: Tool, params: JsonValue): Result<JsonValue, JsonValue> => Tool.metadata.invoke(tool, \"run\", params)")
  Assert.equal(result.header.contains("// A tool."), true)
  Assert.equal(result.header.contains("// Current count."), true)
  Assert.equal(result.header.contains("// Runs it."), true)
  Assert.equal(result.header.contains("// @param input The input."), true)
  Assert.equal(result.header.contains("static const doof::ClassMetadata<Tool> _metadata;"), true)
  Assert.equal(result.source.contains("inline const doof::ClassMetadata<Tool> Tool::_metadata"), true)
  Assert.equal(result.source.contains("doof::MethodReflection<Tool>"), true)
  Assert.equal(result.source.contains("\"input\""), true)
  Assert.equal(result.source.contains("\"required\""), true)
  Assert.equal(result.source.contains("_instance.run(input)"), true)
  Assert.equal(result.source.contains("doof::Success<doof::JsonValue>"), true)
  Assert.equal(result.source.contains("Tool::_metadata"), true)
  Assert.equal(result.source.contains("metadata.invoke"), true)
}

export function testEmitsDirectionalJsonDependenciesForMetadataInvoke(): none {
  result := emit("class Input { value: int }\nclass Output { label: string }\nclass Tool { function convert(input: Input): Output => Output { label: string(input.value) } }\nfunction metadata(): string => Tool.metadata.name")
  Assert.stringContains(result.source, "Input::fromJsonValue")
  Assert.stringNotContains(result.source, "Input::toJsonObject")
  Assert.stringContains(result.source, "Output::toJsonObject")
  Assert.stringNotContains(result.source, "Output::fromJsonValue")
  Assert.stringNotContains(result.source, "Tool::toJsonObject")
  Assert.stringNotContains(result.source, "Tool::fromJsonValue")
}

export function testDoesNotEmitMetadataWhenUnused(): none {
  result := emit("class Tool { function run(input: string): string => input }")
  Assert.equal(result.header.contains("ClassMetadata<Tool>"), false)
  Assert.equal(result.source.contains("Tool::_metadata"), false)
}

export function testDoesNotEmitJsonMethodsThatDependOnUnsupportedNominalFields(): none {
  result := emit("class Handler { callback: (value: int): void }\nclass Envelope { handler: Handler }")
  Assert.equal(result.header.contains("doof::JsonObject toJsonObject() const;"), false)
  Assert.equal(result.source.contains("Envelope::toJsonObject"), false)
  Assert.equal(result.source.contains("Handler::fromJsonValue"), false)
}

export function testEmitsStructThisByValue(): none {
  result := emit("struct Point { length, kind, resolvedType, span, push, value: int\nfunction copy(): Point => this }\nstruct Methods { startsWith(): int => 1\npop(): int => 2 }\nfunction read(point: Point): int => point.length + point.kind + point.resolvedType + point.span + point.push + point.value\nfunction invoke(methods: Methods): int => methods.startsWith() + methods.pop()")
  Assert.equal(result.source.contains("return *this;"), true)
  Assert.equal(result.source.contains("std::shared_ptr<Point>(this"), false)
  for name of ["length", "kind", "resolvedType", "span", "push", "value"] {
    Assert.equal(result.source.contains("point." + name), true)
  }
  Assert.equal(result.source.contains("doof::length(point)"), false)
  Assert.equal(result.source.contains("doof::span(point)"), false)
  Assert.equal(result.source.contains("point->push_back"), false)
  Assert.equal(result.source.contains("methods.startsWith()"), true)
  Assert.equal(result.source.contains("methods.pop()"), true)
  Assert.equal(result.source.contains("doof::starts_with(methods"), false)
  Assert.equal(result.source.contains("doof::pop(methods"), false)
}

export function testEmitsCanonicalStringAndArrayHelpers(): none {
  result := emit("function transform(text: string, values: int[]): Result<int, string> { cleaned := text.trim().replaceAll(\"a\", \"b\")\nif cleaned.startsWith(\"b\") && cleaned.endsWith(\"b\") { return values.pop() }\nreturn Failure(\"missing\") }")
  Assert.equal(result.source.contains("doof::string_trim("), true)
  Assert.equal(result.source.contains("doof::string_replaceAll("), true)
  Assert.equal(result.source.contains("doof::string_startsWith("), true)
  Assert.equal(result.source.contains("doof::string_endsWith("), true)
  Assert.equal(result.source.contains("doof::array_pop("), true)
  Assert.equal(result.source.contains("doof::trim("), false)
  Assert.equal(result.source.contains("doof::starts_with("), false)
  Assert.equal(result.source.contains("doof::pop("), false)
}

export function testEmitsVariantCaseBindings(): none {
  result := emit("class Left { value: int }\nclass Right { value: int }\nfunction main(value: Left | Right): int { case value { left: Left -> { return left.value } _ -> { return 0 } }\nreturn 0 }")
  Assert.equal(result.source.contains("std::holds_alternative<std::shared_ptr<Left>>(_case_subject)"), true)
  Assert.equal(result.source.contains("std::get<std::shared_ptr<Left>>(_case_subject)"), true)
  Assert.equal(result.source.contains("else {"), true)
}

export function testEmitsExactClassCaseWithoutVariantOperations(): none {
  result := emit("class Node { value: int }\nfunction read(value: Node | null): int { case value! { node: Node -> { return node.value } }\nreturn 0 }")
  Assert.equal(result.source.contains("std::holds_alternative<std::shared_ptr<Node>>(_case_subject)"), false)
  Assert.equal(result.source.contains("const auto node = _case_subject;"), true)
}

export function testEmitsNullableClassCaseWithNullGuard(): none {
  result := emit("class Node { value: int }\nfunction read(value: Node | null): int { case value { node: Node -> { return node.value } _ -> { return 0 } } }")
  Assert.equal(result.source.contains("if (!doof::is_null(_case_subject))"), true)
  Assert.equal(result.source.contains("const auto node = doof::unwrap_optional(_case_subject);"), true)
}

export function testEmitsExactClassCaseExpressionWithoutVariantOperations(): none {
  result := emit("class Node { value: int }\nfunction read(value: Node): int => case value { node: Node -> node.value }")
  Assert.equal(result.source.contains("std::holds_alternative<std::shared_ptr<Node>>(_case_subject)"), false)
  Assert.equal(result.source.contains("const auto node = _case_subject;"), true)
}

export function testEmitsJsonValueCaseTypeGuardsAndNarrowing(): none {
  result := emit("function read(value: JsonValue): int { case value { text: string -> { return text.length } object: JsonObject -> { return object.size } _ -> { return 0 } } }")
  Assert.equal(result.source.contains("if (doof::json_is_string(_case_subject))"), true)
  Assert.equal(result.source.contains("const auto text = doof::json_as_string(_case_subject);"), true)
  Assert.equal(result.source.contains("else if (doof::json_is_object(_case_subject))"), true)
  Assert.equal(result.source.contains("const auto object = doof::json_object(_case_subject);"), true)
}

export function testGeneratedModulesUseRuntimeStandardLibraryBaseline(): none {
  result := emit("function square(value: double): double => value ** value")
  Assert.equal(result.header.startsWith("#pragma once\n#include \"doof_runtime.hpp\"\n"), true)
  Assert.equal(result.header.contains("DOOF_SELFHOST_COMMON_HELPERS"), false)
  Assert.equal(result.header.contains("inline bool starts_with"), false)
  Assert.equal(result.header.contains("#include <cstdint>"), false)
  Assert.equal(result.header.contains("#include <cmath>"), false)
  Assert.equal(result.header.contains("#include <functional>"), false)
  Assert.equal(result.header.contains("#include <memory>"), false)
  Assert.equal(result.header.contains("#include <optional>"), false)
  Assert.equal(result.header.contains("#include <ostream>"), false)
  Assert.equal(result.header.contains("#include <string>"), false)
  Assert.equal(result.header.contains("#include <tuple>"), false)
  Assert.equal(result.header.contains("#include <type_traits>"), false)
  Assert.equal(result.header.contains("#include <variant>"), false)
  Assert.equal(result.header.contains("#include <vector>"), false)
  Assert.equal(result.source.contains("#include <cmath>"), false)
  Assert.equal(result.source.contains("std::pow(value, value)"), true)
}

export function testBreaksCircularStructHeaderDependencies(): none {
  sources := [
    SourceFile {
      path: "/render.do",
      source: "import { Transform } from \"./transform\"\nexport struct Point3 { x: double\ny: double\nz: double }\nexport class Camera { transform: Transform }",
    },
    SourceFile {
      path: "/transform.do",
      source: "import { Point3 } from \"./render\"\nexport struct Vec3 { x: double\ny: double\nz: double\nstatic fromPoint(point: Point3): Vec3 => Vec3 { x: point.x, y: point.y, z: point.z } }\nexport struct Transform { position: Point3 }",
    },
    SourceFile { path: "/main.do", source: "import { Camera } from \"./render\"\nfunction main(): int => 0" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/render.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/transform.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/main.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  let renderHeader = ""
  let transformHeader = ""
  for module of graph.modules {
    if module.modulePath == "/render.do" { renderHeader = module.header }
    if module.modulePath == "/transform.do" { transformHeader = module.header }
  }

  renderTransformForward := renderHeader.indexOf("namespace app_transform_ {\n    struct Transform;")
  renderPointDefinition := renderHeader.indexOf("struct Point3 {")
  renderTransformDefinition := renderHeader.indexOf("struct Transform {")
  Assert.isTrue(renderTransformForward >= 0)
  Assert.equal(renderHeader.contains("#include \"transform.hpp\""), false)
  Assert.isTrue(renderTransformForward < renderTransformDefinition)
  Assert.isTrue(renderPointDefinition < renderTransformDefinition)

  transformPointForward := transformHeader.indexOf("namespace app_render_ {\n    struct Point3;")
  transformPointDefinition := transformHeader.indexOf("struct Point3 {")
  transformDefinition := transformHeader.indexOf("struct Transform {")
  Assert.isTrue(transformPointForward >= 0)
  Assert.equal(transformHeader.contains("#include \"render.hpp\""), false)
  Assert.isTrue(transformPointForward < transformPointDefinition)
  Assert.isTrue(transformDefinition > transformPointDefinition)
}

export function testKeepsImportedStaticDefaultsOutOfHeaders(): none {
  sources := [
    SourceFile { path: "/dep.do", source: "export class Dep { static create(): Dep => Dep {} }" },
    SourceFile { path: "/main.do", source: "import { Dep } from \"./dep\"\nclass Holder { count: int = 1\ndep: Dep = Dep.create() }\nfunction make(): Holder => Holder()" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/dep.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/main.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  let header = ""
  let source = ""
  for module of graph.modules {
    if module.modulePath == "/main.do" { header = module.header; source = module.source }
  }
  Assert.equal(header.contains("Dep::create()"), false)
  Assert.equal(header.contains("Holder(int32_t count = 1"), false)
  Assert.equal(source.contains("std::make_shared<Holder>(1, ::app_dep_::Dep::create())"), true)
}

export function testEmitsNullableStructParametersAsOptionalValues(): none {
  result := emit("struct Point { x: int }\nfunction read(point: Point | none = none): bool => point == none\nfunction legacy(point: Point | null = null): bool => null == point")
  Assert.equal(result.header.contains("bool read(std::optional<Point> point = std::nullopt)"), true)
  Assert.equal(result.source.contains("doof::is_null(point)"), true)
  Assert.equal(result.header.contains("bool legacy(std::optional<Point> point = std::nullopt)"), true)
  Assert.equal(result.source.contains("bool legacy"), true)
}

export function testEmitsUniformNoneComparisons(): none {
  result := emit("function nullable(value: int | none): bool => value != none\nfunction jsonNull(value: JsonValue): bool => none == value")
  Assert.stringContains(result.source, "(!doof::is_null(value))")
  Assert.stringContains(result.source, "doof::is_null(value)")
  Assert.stringNotContains(result.source, "doof::json_is_null(value)")
}

export function testEmitsPositionAwareNoneRepresentations(): none {
  result := emit("function fallthrough(): none { }\nfunction explicit(): none { return none }\nfunction invoke(callback: (): none): none { callback() }\nfunction save(): Result<none, string> => Success()\nfunction fail(): Result<int, none> => Failure()\nfunction settle(value: Promise<none>): Promise<none> => value")
  Assert.stringContains(result.header, "void fallthrough()")
  Assert.stringContains(result.header, "void explicit()")
  Assert.stringContains(result.header, "const doof::callback<void()>& callback")
  Assert.stringContains(result.header, "doof::Result<void, std::string> save()")
  Assert.stringContains(result.header, "doof::Result<int32_t, void> fail()")
  Assert.stringContains(result.header, "doof::Promise<void> settle(const doof::Promise<void>& value)")
  Assert.stringContains(result.source, "void explicit() {\n    return;")
}

export function testEmitsNullableMapsWithTheirPointerCarrier(): none {
  result := emit("function read(value: Map<string, int> | null): int => value!.size")
  Assert.equal(result.header.contains("std::variant<std::monostate"), false)
  Assert.equal(result.header.contains("const std::shared_ptr<doof::ordered_map<std::string, int32_t>>& value"), true)
}

export function testKeepsImmutableStructBindingInteriorMutable(): none {
  result := emit("struct Point { x: int\nsum(): int => x }\nfunction read(): int { point := Point(4)\nreturn point.sum() }")
  Assert.equal(result.source.contains("auto point ="), true)
  Assert.equal(result.source.contains("const auto point"), false)
}

export function testEmitsEnumsAndTypeAliases(): none {
  result := emit("enum Color { Red, Green = 3 }\ntype MaybeColor = Color | null\nfunction main(): int { color := Color.Red\nreturn 0 }")
  Assert.equal(result.header.contains("enum class Color"), true)
  Assert.equal(result.header.contains("Green = 3"), true)
  Assert.equal(result.header.contains("operator<<(std::ostream& output, Color value)"), true)
  Assert.equal(result.header.contains("using MaybeColor ="), true)
  Assert.equal(result.source.contains("Color::Red"), true)
}

export function testEmitsAssignmentsAndArrayLoops(): none {
  result := emit("function main(): int { let values: int[] = [1, 2]\nvalues[0] = 4\nlet total = 0\nfor item of values { total = total + item }\nreturn total }")
  Assert.stringContains(result.source, "doof::array_at(values, 0, \"<module>\", 2) = 4")
  Assert.equal(result.source.contains("const auto& _iterable_"), true)
  Assert.equal(result.source.contains("for (const auto& item : *_iterable_"), true)
}

export function testKeepsComputedForOfCollectionAlive(): none {
  result := emit("function values(): int[] => [1, 2, 3]\nfunction main(): int { let total = 0\nfor item of values() { total = total + item }\nreturn total }")
  Assert.equal(result.source.contains("const auto& _iterable_"), true)
  Assert.equal(result.source.contains(" = values();"), true)
  Assert.equal(result.source.contains("for (const auto& item : *_iterable_"), true)
  Assert.equal(result.source.contains("for (const auto& item : *values())"), false)
}

export function testEmitsStringCaseAndCallbackCallMembers(): none {
  result := emit("function invoke(handler: (): void): string { handler.call()\nreturn \"HTTP\".toLowerCase() }")
  Assert.equal(result.source.contains("handler.call()"), true)
  Assert.equal(result.source.contains("doof::string_toLowerCase("), true)
  Assert.equal(result.source.contains("HTTP"), true)
}

export function testAvoidsRedundantConditionParentheses(): none {
  result := emit("function main(flag: bool): int { if flag == true { return 1 } return 0 }")
  Assert.equal(result.source.contains("if (flag == true)"), true)
  Assert.equal(result.source.contains("if ((flag == true))"), false)
}

export function testEmitsNeverFunctionsAndBottomCoercions(): none {
  result := emit("function fail(message: string): never => panic(message)\nfunction choose(flag: bool): int => if flag then 42 else fail(\"missing\")\nfunction main(): int => choose(true)")
  Assert.stringContains(result.header, "[[noreturn]] doof::Never fail")
  Assert.stringContains(result.source, "doof::panic(message)")
  Assert.stringContains(result.source, "flag ? 42 : fail(std::string(\"missing\"))")
}

export function testEmitsUnreachableAfterDivergentExhaustiveCaseStatements(): none {
  exhaustive := emit("function load(): Result<int, string> => Success { value: 1 }\nfunction answer(): int { case load() { value: Success -> { return value.value }, error: Failure -> { return 0 } } }")
  Assert.stringContains(exhaustive.source, "doof::unreachable();")

  completing := emit("function inspect(value: int): none { case value { 1 -> { println(\"one\") } } }")
  Assert.equal(completing.source.contains("doof::unreachable();"), false)
}

export function testPlansStableModuleNamesWithoutImportHeaders(): none {
  analysis := createAnalyzer([
    SourceFile { path: "/main.do", source: "import { add } from \"./lib/math\"\nfunction main(): int => add(2, 3)" },
    SourceFile { path: "/lib/math.do", source: "export function add(a: int, b: int): int => a + b" },
  ]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  plan: ModuleGraphPlan := planModuleGraph(analysis)
  Assert.equal(plan.modules.length, 2)
  Assert.equal(plan.modules[0].path, "/main.do")
  Assert.equal(plan.modules[0].namespaceName, "app_main_")
  Assert.equal(plan.modules[0].headerName, "main.hpp")
  Assert.equal(plan.modules[0].sourceName, "main.cpp")
  Assert.equal(plan.modules[1].namespaceName, "app_lib_math_")
  Assert.equal(plan.modules[1].headerName, "lib_math.hpp")
}

export function testEmitsNativeClassInterop(): none {
  result := emit("import class Client from \"<client.hpp>\" as native::Client { value: int get(): int static make(value: int): Client same(): Client { return this } }\nfunction read(client: Client): Client => client\nfunction main(): int { client := Client { value: 4 }\nmade := Client.make(4)\nreturn client.get() + made.get() }")
  Assert.equal(result.header.contains("#include <client.hpp>"), true)
  Assert.equal(result.header.contains("struct Client"), false)
  Assert.equal(result.header.contains("std::shared_ptr<::native::Client>"), true)
  Assert.equal(result.source.contains("std::make_shared<::native::Client>(4)"), true)
  Assert.equal(result.source.contains("::native::Client::make(4)"), true)
  Assert.equal(result.source.contains("std::shared_ptr<::native::Client> native::Client::same()"), true)
  Assert.equal(result.source.contains("this->shared_from_this()"), true)
  Assert.equal(result.source.contains("client->get()"), true)
}

export function testEmitsNativeCppNameThroughLocalExportList(): none {
  sources := [
    SourceFile { path: "/main.do", source: "import { NativeImage } from \"./native\"\nfunction load(image: NativeImage): NativeImage => image" },
    SourceFile { path: "/native.do", source: "import class NativeImage from \"native_image.hpp\" as doof_image::NativeImage {}\nexport { NativeImage }" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/native.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/main.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  let header = ""
  for module of graph.modules { if module.modulePath == "/main.do" { header = module.header } }

  Assert.equal(header.contains("std::shared_ptr<::doof_image::NativeImage>"), true)
  Assert.equal(header.contains("app_native_::NativeImage"), false)
}

export function testResolvesNestedSourceRelativeNativeHeaderIntoPackageOutput(): none {
  path := "/workspace/http-server/tests/http_server.test.do"
  source := "import class NativeRequest from \"../native_http_server_test_support.hpp\" as native::NativeRequest {}"
  analysis := createAnalyzer([SourceFile { path, source }]).analyze(path)
  Assert.equal(analysis.diagnostics.length, 0)
  Assert.equal(hasErrorDiagnostics(createChecker(analysis).check(path).diagnostics), false)
  configureModuleNamespaces([
    ModuleNamespaceMapping {
      logicalPrefix: "/workspace/http-server",
      packageName: "std/http-server",
      outputRoot: "",
    },
  ])
  header := emitModuleGraph(analysis, path).modules[0].header
  configureModuleNamespaces([])

  Assert.equal(header.contains("#include \"native_http_server_test_support.hpp\""), true)
  Assert.equal(header.contains("#include \"../native_http_server_test_support.hpp\""), false)
}

export function testEmitsByteCastBuiltin(): none {
  result := emit("function carriageReturn(): byte => byte(13)")
  Assert.equal(result.source.contains("static_cast<uint8_t>(13)"), true)
  Assert.equal(result.source.contains("byte.call"), false)
}

export function testEmitsExplicitArgumentsForTemplateGenericMethods(): none {
  result := emit("class Assert { static equal<T>(actual: T, expected: T): void {} }\nfunction compare(value: string | null): void { Assert.equal(value, \"ok\") }")
  Assert.equal(result.source.contains("Assert::equal<std::optional<std::string>>"), true)
  Assert.equal(result.source.contains("value, std::string(\"ok\"))"), true)
}

export function testEmitsImportedTypeAliasesForNativeNamespaces(): none {
  sources := [
    SourceFile { path: "/main.do", source: "export { EncodingError } from \"./types\"\nimport class Native from \"native.hpp\" as doof_blob::Native { error(): EncodingError }\nfunction read(value: Native): EncodingError => value.error()" },
    SourceFile { path: "/types.do", source: "export enum EncodingError { Invalid }" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/types.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/main.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  let header = ""
  for module of graph.modules { if module.modulePath == "/main.do" { header = module.header } }
  Assert.equal(header.contains("namespace doof_blob { using EncodingError = ::app_types_::EncodingError; }"), true)
}

export function testEmitsVisibleNativeAliasesAndCompleteRecursiveTypes(): none {
  sources := [
    SourceFile { path: "/main.do", source: "import { FileInfo, IoError } from \"./types\"\nexport { EntryKind } from \"./types\"\nimport class NativeReader from \"native.hpp\" as NativeReader { error(): IoError }\nexport import function metadata(path: string): Result<FileInfo, IoError> from \"native.hpp\" as doof_fs::metadata" },
    SourceFile { path: "/types.do", source: "import { Instant } from \"./time\"\nexport enum EntryKind { File }\nexport enum IoError { Other }\nexport class FileInfo { kind: EntryKind\nmodifiedAt: Instant }" },
    SourceFile { path: "/time.do", source: "export class Instant {}\nexport class Duration {}" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/time.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/types.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/main.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  let header = ""
  for module of graph.modules { if module.modulePath == "/main.do" { header = module.header } }
  Assert.equal(header.contains("#include \"types.hpp\""), false)
  Assert.equal(header.contains("namespace doof_fs { using FileInfo = ::app_types_::FileInfo; }"), true)
  Assert.equal(header.contains("namespace doof_fs { using IoError = ::app_types_::IoError; }"), true)
  Assert.equal(header.contains("namespace doof_fs { using EntryKind = ::app_types_::EntryKind; }"), true)
  Assert.equal(header.contains("namespace doof_fs { using Instant = ::app_time_::Instant; }"), false)
  instantDefinition := header.indexOf("namespace app_time_ {\n    struct Instant : public")
  nativeInclude := header.indexOf("#include \"native.hpp\"")
  Assert.equal(instantDefinition >= 0 && instantDefinition < nativeInclude, true)
  Assert.equal(header.contains("using IoError = ::app_types_::IoError;"), true)
  Assert.equal(header.contains("using Duration = ::app_time_::Duration;"), false)
}

export function testDoesNotForwardDeclareOrAliasImportedGenericTypesForNativeHeaders(): none {
  sources := [
    SourceFile { path: "/main.do", source: "import { Channel, createChannel } from \"./event\"\nimport class Native from \"native.hpp\" as native::Native {}\nfunction receive(channel: Channel<int>): void { created := createChannel<int>() }" },
    SourceFile { path: "/event.do", source: "export class Channel<T> {}\nexport function createChannel<T>(): Channel<T> => Channel<T> {}" },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/event.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/main.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/main.do")
  let header = ""
  for module of graph.modules { if module.modulePath == "/main.do" { header = module.header } }
  Assert.equal(header.contains("namespace app_event_ { struct Channel; }"), false)
  Assert.equal(header.contains("namespace native { using Channel = ::app_event_::Channel; }"), false)
  Assert.equal(header.contains("namespace native { using ::app_event_::createChannel; }"), false)
}

export function testEmitsInterfaceVariantsAndDispatch(): none {
  result := emit("interface Drawable { value: int\nrender(): int }\nclass Point implements Drawable { readonly value: int\nfunction render(): int => value }\nfunction read(shape: Drawable): int => shape.render()\nfunction main(): int { point := Point { value: 5 }\nshape: Drawable := point\nreturn read(shape) + shape.value }")
  Assert.equal(result.header.contains("using Drawable = std::variant<std::shared_ptr<Point>>;"), true)
  Assert.equal(result.source.contains("const Drawable shape = point;"), true)
  Assert.equal(result.source.contains("std::visit([&](auto&& _obj) { return _obj->render(); }, shape)"), true)
  Assert.equal(result.source.contains("std::visit([](auto&& _obj) { return _obj->value; }, shape)"), true)
}

export function testEmitsIntrinsicJsonValueLiterals(): none {
  result := emit("function main(): JsonValue { payload: JsonValue := { name: \"Ada\", values: [1, true] }\nreturn payload }")
  Assert.equal(result.header.contains("doof::JsonValue"), true)
  Assert.equal(result.source.contains("doof::ordered_map<std::string, doof::JsonValue>"), true)
  Assert.equal(result.source.contains("doof::json_value"), true)
}

export function testParsesNativeJsonFunctionSurface(): none {
  native := emit("export import function formatJsonValue(value: JsonValue): string from \"<json.hpp>\" as doof_json::format")
  Assert.equal(native.header.contains("#include <json.hpp>"), true)
  result := emitSources([
    SourceFile { path: "/main.do", source: "import { formatJsonValue } from \"./json\"\nfunction main(): string => formatJsonValue({ ok: true })" },
    SourceFile { path: "/json.do", source: "export import function formatJsonValue(value: JsonValue): string from \"<json.hpp>\" as doof_json::format" },
  ], "/main.do")
  Assert.equal(result.source.contains("doof_json::format"), true)
}

export function testEmitsNonGenericNativeFunctionNameAcrossModules(): none {
  sources := [
    SourceFile { path: "/std/path/path.test.do", source: "import { setCurrentWorkingDirectory } from \"./index\"\nfunction change(path: string): Result<none, string> => setCurrentWorkingDirectory(path)" },
    SourceFile { path: "/std/path/index.do", source: "export import function setCurrentWorkingDirectory(path: string): Result<none, string> from \"native_path.hpp\" as doof_path::setCurrentWorkingDirectory" },
  ]
  analysis := createAnalyzer(sources).analyze("/std/path/path.test.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checker := createChecker(analysis)
  Assert.equal(hasErrorDiagnostics(checker.check("/std/path/index.do").diagnostics), false)
  Assert.equal(hasErrorDiagnostics(checker.check("/std/path/path.test.do").diagnostics), false)
  graph := emitModuleGraph(analysis, "/std/path/path.test.do")
  let source = ""
  for module of graph.modules { if module.modulePath == "/std/path/path.test.do" { source = module.source } }
  Assert.stringContains(source, "::doof_path::setCurrentWorkingDirectory(path)")
  Assert.equal(source.contains("::app_std_path_index_::setCurrentWorkingDirectory(path)"), false)
}

export function testEmitsContextualResultAndClassObjectLiterals(): none {
  result := emit("class Payload { count: int }\nfunction load(): Result<Payload, string> => { value: { count: 4 } }")
  Assert.equal(result.source.contains("doof::Success<std::shared_ptr<Payload>>"), true)
  Assert.stringContains(result.source, "std::make_shared<::app_main_::Payload>(4)")
}

export function testEmitsContextualSumObjectLiteralsAndPromotions(): none {
  result := emit(
    "class Animal { name: string }\n" +
    "class Question { text: string\nlet yes: Knowledge\nlet no: Knowledge }\n" +
    "type Knowledge = Animal | Question\n" +
    "function initial(): Knowledge => { text: \"Does it swim\", yes: { name: \"fish\" }, no: { name: \"bird\" } }",
  )
  Assert.stringContains(result.source, "std::make_shared<::app_main_::Question>")
  Assert.stringContains(result.source, "std::make_shared<::app_main_::Animal>")
  Assert.stringContains(result.source, "doof::variant_promote<")
}

export function testEmitsResultPayloadAccessThroughRuntimeHelpers(): none {
  result := emit("function load(): Result<int, string> => Failure { error: \"bad\" }\nfunction read(): Result<int, string> { value := load() else { return { error: value.error } }\nreturn { value } }")
  Assert.equal(result.source.contains("doof::failure_error(value)"), true)
}

export function testEmitsAsNarrowingOverResultValues(): none {
  result := emit("function parse(): Result<JsonValue, string> => Success { value: \"ok\" }\nfunction read(): Result<string, string> { value := parse() as string else { return { error: value.error } }\nreturn { value } }")
  Assert.equal(result.source.contains("if (doof::is_failure(_as_source))"), true)
  Assert.equal(result.source.contains("auto _as_value = doof::success_value(_as_source)"), true)
  Assert.equal(result.source.contains("doof::json_as_string(_as_value)"), true)
}

export function testDoesNotTreatFunctionsReturningNativeClassesAsConstructors(): none {
  result := emit("import class Handle from \"handle.hpp\" as native::Handle { value(): int }\nimport function open(): Handle from \"handle.hpp\" as native::open\nfunction read(): int => open().value()")
  Assert.equal(result.source.contains("native::open()"), true)
  Assert.equal(result.source.contains("make_shared<::native::Handle>()"), false)
}

export function testDoesNotTreatImplicitMethodsReturningNominalTypesAsConstructors(): none {
  result := emit("struct Token { kind: int }\nstruct Location { line: int }\nclass Parser { current(): Token => Token { kind: 1 }\nlocation(): Location => Location { line: 2 }\natEnd(): bool => current().kind == 0\nstart(): int => location().line }")
  Assert.equal(result.source.contains("current().kind"), true)
  Assert.equal(result.source.contains("location().line"), true)
  Assert.equal(result.source.contains("Token{}.kind"), false)
  Assert.equal(result.source.contains("Location{}.line"), false)
}

export function testEmitsYieldBlockDeclarationsAndReassignment(): none {
  result := emit("function main(): int { let value <- { if true { yield 1 } else { yield 2 } }\nvalue <- { yield value + 1 }\nreturn value }")
  Assert.stringContains(result.source, "auto value = [&]() -> int32_t")
  Assert.stringContains(result.source, "value = [&]() -> int32_t")
  Assert.stringContains(result.source, "return (value + 1)")
}

export function testEmitsYieldBlockReassignmentToCapturedMutable(): none {
  result := emit("function make(): (): int { let value = 0\nread := (): int => value\nvalue <- { yield value + 1 }\nreturn read }")
  Assert.stringContains(result.source, "auto value = std::make_shared<int32_t>(0)")
  Assert.stringContains(result.source, "(*value) = [&]() -> int32_t")
}

export function testEmitsCatchExpressionsWithRedirectedTryFailures(): none {
  result := emit("enum LoadError { Missing }\nfunction load(ok: bool): Result<int, LoadError> { if ok { return Success { value: 1 } }\nreturn Failure { error: .Missing } }\nfunction main(): int { error := catch { try value := load(false)\nprintln(string(value)) }\nreturn case error { _: LoadError -> 1, _ -> 0 } }")
  Assert.stringContains(result.source, "do {")
  Assert.stringContains(result.source, "doof::variant_promote<")
  Assert.stringContains(result.source, "doof::failure_error(_try_value_")
  Assert.stringContains(result.source, "break;")
}

export function testEmitsCompleteDestructuringSurface(): none {
  result := emit("class Person { name: string\nage: int }\nstruct Pair { left: int\nright: string }\nfunction main(): int { values := [1, 2, 3]\n[first, _, third] := values\nperson := Person { name: \"Ada\", age: 37 }\n{ name as displayName, age } := person\npair := Pair { left: 4, right: \"ok\" }\n(left, right) := pair\nlet target = 0\n[target, _] = values\nlet renamed = \"\"\n{ name as renamed } = person\nreturn first + third + age + left + target + displayName.length + right.length + renamed.length }")
  Assert.stringContains(result.source, "doof::array_require_min_size(")
  Assert.stringContains(result.source, "doof::array_at(")
  Assert.stringContains(result.source, "->name")
  Assert.stringContains(result.source, "->age")
  Assert.stringContains(result.source, ".left")
  Assert.stringContains(result.source, ".right")
  Assert.stringContains(result.source, "target = doof::array_at(")
  Assert.stringContains(result.source, "renamed = _destructure_")
}

export function testEmitsTryDestructuringFromSuccessPayload(): none {
  result := emit("function load(): Result<Tuple<int, int>, string> => Success { value: (1, 2) }\nfunction run(): Result<int, string> { try (left, right) := load()\nreturn Success { value: left + right } }")
  Assert.stringContains(result.source, "doof::success_value(_try_value_")
  Assert.stringContains(result.source, "std::get<0>(")
  Assert.stringContains(result.source, "std::get<1>(")
}
