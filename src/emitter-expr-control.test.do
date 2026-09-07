import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testContextualIfUsesSharedConditionEmission(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function choose(value: int): int | string => if value == 1 then 7 else \"other\"",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "if (value == 1)")
  Assert.stringNotContains(source, "if ((value == 1))")
}

function chooseMixed(flag: bool, calls: int[]): int | string {
  calls[0] += 1
  return if flag then 7 else "seven"
}

struct ConditionalValue { value: int }

function chooseNullable(flag: bool): ConditionalValue | none => if flag then ConditionalValue { value: 9 } else none

export function testEmitterGapConditionalBranchesUseCheckedCarrier(): none {
  calls := [0]
  first := chooseMixed(true, calls)
  second := chooseMixed(false, calls)
  Assert.equal((first as int)!, 7)
  Assert.equal((second as string)!, "seven")
  Assert.equal(calls[0], 2)
  Assert.equal(chooseNullable(true)!.value, 9)
  Assert.isTrue(chooseNullable(false) == none)
  let evaluated = 0
  selected: int | string := if true then "selected" else (evaluated += 1)
  Assert.equal((selected as string)!, "selected")
  Assert.equal(evaluated, 0)
}

export function testEmitterGapConditionalIncompatibleReturnRemainsDiagnostic(): none {
  result := compile([SourceFile {
    path: "/conditional.do",
    source: "function choose(flag: bool): int => if flag then 1 else \"two\"",
  }], "/conditional.do")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "Cannot use string in expression expecting int")
  Assert.isTrue(result.emission == none)
}

export function testGenericNoneLiteralCatchUsesSpecializedCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Error { message: string }\n" +
    "function fail<E>(error: E): Result<int, E> { return Failure { error: error } }\n" +
    "function capture<E>(error: E): E | none { return catch { try value := fail(error) } }\n" +
    "function main(): none { capture(Error { message: \"bad\" })\ncapture(7) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, " = nullptr;")
  Assert.stringContains(source, " = std::nullopt;")
  Assert.stringNotContains(source, " = std::monostate{};")
  Assert.stringNotContains(source, "std::variant<std::monostate, E>")
}

export function testGenericNoneLiteralReadonlyConditionalHasOneCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Effect { rerollScope: int\nreadonly rerollScopes: int[] }\n" +
    "function scopes(effect: Effect): int {\n" +
    "readonly scopes: int[] = if effect.rerollScopes.length == 0 then [effect.rerollScope] else effect.rerollScopes\n" +
    "return scopes.length }\nfunction main(): none { scopes(Effect { rerollScope: 7, rerollScopes: [] }) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringNotContains(source, "std::variant<std::shared_ptr<std::vector<int32_t>>")
  Assert.stringContains(source, "const std::shared_ptr<std::vector<int32_t>> scopes =")
}

export function testRestrictedPathRuntimeCarriers(): none {
  flag := true
  optional := if flag then 7 else none
  Assert.equal(optional!, 7)
  reversed := if flag then none else 9
  Assert.isTrue(reversed == none)
  let yielded <- { if flag { yield 3 } else { yield none } }
  Assert.equal(yielded!, 3)
  absent: int | none := none
  fallback: int | string := absent ?? "fallback"
  Assert.equal((fallback as string)!, "fallback")
  chosen := case flag { true -> none, false -> 4 }
  Assert.isTrue(chosen == none)
}
export function testUnitCaseArmReturnsCarrierDirectly(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\nfunction run(flag: bool): none => case flag { true -> effect(), _ -> none }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "return (static_cast<void>(effect()), std::monostate{});")
  Assert.stringContains(source, "return std::monostate{};")
}

export function testReadonlyEmissionControlUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction choose(): Choice => .One" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "::mapped::types::Choice")
  Assert.stringNotContains(output, "app_vendor_types_")
}
