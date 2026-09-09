import { ModuleNamespaceMapping } from "./emitter-names"
import { noSourceLoader } from "./resolver"
import { compileWithLoader } from "./compiler"
import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testDiscardedExpressionValuesAreExplicit(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\n" +
    "function main(): none { effect()\nnone\n42\nlet count = 0\ncount += 1\nvalue := effect() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "effect();")
  Assert.stringContains(source, "static_cast<void>(std::monostate{});")
  Assert.stringContains(source, "static_cast<void>(42);")
  Assert.stringContains(source, "static_cast<void>((count += 1));")
  Assert.stringContains(source, "value = (static_cast<void>(effect()), std::monostate{});")
}

export function testUnitAsyncYieldExplicitlyDiscardsCarrier(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\nfunction main(): none { task := async { yield effect() } }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source,
    "effect();\n    return;")
}

export function testLoopUpdatesExplicitlyDiscardEachValue(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function effect(): none {}\nfunction main(): none { for let i = 0; i < 2; effect(), i += 1 {} }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source,
    "effect(), static_cast<void>((i += 1))")
}

export function testCapturedOptionalGenericLocalUsesConcreteStorageType(): none {
  result := compile([
    SourceFile {
      path: "/event.do",
      source:
        "export class ChannelSender<T> { close(): none {} }\n" +
        "export function createChannel<T>(): ChannelSender<T> => ChannelSender<T> {}",
    },
    SourceFile {
      path: "/main.do",
      source:
        "import { ChannelSender, createChannel } from \"./event\"\n" +
        "class Message {}\n" +
        "function invoke(handler: (message: Message): none): none {}\n" +
        "function accept(sender: ChannelSender<Message>, message: Message): none { sender.close() }\n" +
        "function main(): none {\n" +
        "let channel: ChannelSender<Message> | none = none\n" +
        "sender := createChannel<Message>()\n" +
        "invoke((message: Message): none => accept(channel!, message))\n" +
        "channel = sender\n" +
        "}",
    },
  ], "/main.do")

  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  let source = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { source = module.source } }
  Assert.stringContains(source, "std::make_shared<std::shared_ptr<::app_event_::ChannelSender__app_main__Message_>>(nullptr)")
  Assert.stringNotContains(source, "ChannelSender<std::shared_ptr<Message>>")
}

class DestructuredCounter { value: int }

function tupleCounter(): (): int {
  let (count, _) = (1, 0)
  return (): int => { count += 1
    return count }
}

function arrayCounter(): (): int {
  let [count, _] = [3, 0]
  return (): int => { count += 1
    return count }
}

function namedCounter(): (): int {
  let { value as count } = DestructuredCounter { value: 5 }
  return (): int => { count += 1
    return count }
}

export function testEmitterGapDestructuredMutablesShareEscapingStorage(): none {
  tuple := tupleCounter()
  array := arrayCounter()
  named := namedCounter()
  Assert.equal(tuple(), 2)
  Assert.equal(tuple(), 3)
  Assert.equal(array(), 4)
  Assert.equal(array(), 5)
  Assert.equal(named(), 6)
  Assert.equal(named(), 7)
  let (uncaptured, _) = (10, 0)
  uncaptured += 1
  Assert.equal(uncaptured, 11)
}

export function testDeclarationElseExtractsSingleCallbackVariant(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function main(): none { let callback: ((): none) | none = (): none => {}\n" +
    "narrowed := callback else { panic(\"missing\") }\nnarrowed() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  for module of result.emission!.modules {
    if module.modulePath != "/main.do" { continue }
    Assert.stringContains(module.source, "std::get<doof::callback<void()>>(_binding_value_")
    Assert.stringContains(module.source, "narrowed.call()")
  }
}

export function testDeclarationElseCallbackRuntimePaths(): none {
  let count = 0
  let callback: ((): none) | none = (): none => { count = count + 1 }
  narrowed := callback else { panic("missing callback") }
  narrowed()
  Assert.equal(count, 1)
  Assert.equal(optionalCallbackValue(none), -1)
  Assert.equal(optionalCallbackValue((): int => 7), 7)
}

function optionalCallbackValue(callback: ((): int) | none): int {
  narrowed := callback else { return -1 }
  return narrowed()
}

export function testCheckerReviewTypedTryStorage(): none {
  result := compile([SourceFile { path: "/main.do", source: "function load(): Result<int, string> => Success { value: 1 }\nfunction good(): Result<long, string> { try let x: long = load()\nx += 2147483648L\nreturn Success { value: x } }\nfunction caught(): none { error := catch { try readonly x: long = load() } }\ntry value: long := load()\nprintln(value)" }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "int64_t x = doof::variant_promote<int64_t>(doof::success_value(")
  Assert.stringContains(source, "const int64_t x = doof::variant_promote<int64_t>(doof::success_value(")
  Assert.stringContains(source, "const int64_t value = doof::variant_promote<int64_t>(doof::success_value(")
}

export function testRestrictedNestedYieldCarriers(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function run(flag: bool): int | none { let x <- { let inner: string | none <- { yield none }\nif flag { yield 1 } else { yield none } }\nreturn x }\nfunction main(): none { run(true) }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let source = ""
  for module of result.emission!.modules { source = source + module.source }
  Assert.stringContains(source, "return std::nullopt;")
  Assert.stringNotContains(source, "return std::monostate{};")
}

export function testCombinationNoneGenericBlockReturn(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function identity<T>(value: T): T { return value }\nfunction main(): none { identity(none)\nidentity(7) }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  source := result.emission!.modules[0].source
  Assert.stringContains(source, "return static_cast<void>(value);")
  Assert.stringContains(source, "return value;")
}

export function testReadonlyEmissionStatementsUsesExplicitNames(): none {
  result := compileWithLoader([
    SourceFile { path: "/vendor/types.do", source: "export class Item { value: int = 1 }\nexport class Other {}\nexport enum Choice { One, Two }\nexport function make(): Item => Item {}" },
    SourceFile { path: "/main.do", source: "import { Item, Other, Choice, make } from \"./vendor/types\"\nfunction build(): none { value := Item {} }" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "mapped" }])
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  let output = ""
  for module of result.emission!.modules { if module.modulePath == "/main.do" { output = module.header + module.source } }
  Assert.stringContains(output, "::mapped::types::Item")
  Assert.stringNotContains(output, "app_vendor_types_")
}

export function testNeverReviewTryEmission(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function load(): Result<never, string> => Failure { error: \"bad\" }\n" +
    "function propagate(): Result<int, string> { try load() }",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.stringContains(result.emission!.modules[0].source, "doof::unreachable();")
}
