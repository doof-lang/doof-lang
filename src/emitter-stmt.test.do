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
