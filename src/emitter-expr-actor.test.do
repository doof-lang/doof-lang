import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testAsyncUnitCallOmitsUnusedCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "isolated function effect(): none {}\nfunction main(): none { task := async effect() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source,
    "doof::submit_async<void>([=]() { effect(); })")
}

export function testRestrictedAsyncYieldCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function run(flag: bool): Promise<int | none> => async { if flag { yield 1 } else { yield none } }\nfunction main(): none { run(true) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "return std::nullopt;")
}

export function testRestrictedAsyncYieldRuntime(): none {
  task := async { if true { yield none } else { yield 1 } }
  value := try! task.get()
  Assert.isTrue(value == none)
}

export function testSecondConsolidationActorStoredAndFactoryDefaults(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class Stored { const kind: string = \"stored\"\nvalue: int = 7 }\nclass Factory { value: int\nstatic constructor(value: int = 9): Factory => Factory { value } }\nfunction make(): none { first := Actor<Stored>()\nsecond := Actor<Factory>() }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "Stored{7}")
  Assert.stringContains(source, "Factory::constructor(9)")
}

export function testReadonlyEmissionActorUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction build(): none { actor := Actor<Item>() }" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "::mapped::types::Item")
  Assert.stringNotContains(output, "app_vendor_types_")
}
