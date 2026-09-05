import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

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
