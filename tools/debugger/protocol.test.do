import { Assert } from "std/assert"
import { DapDecoder, bytesOf, frameMessage, textField, intField } from "./protocol"

export function testDapFramingFragmentedUnicodeAndBatchedMessages(): none {
  decoder := DapDecoder {}
  wire := bytesOf(frameMessage({ seq: 7, "type": "event", event: "工具" }) + frameMessage({ seq: 8, "type": "event" }))
  let count = 0
  for byteValue of wire {
    let one: byte[] = [byteValue]
    messages := try! decoder.feed(one.drainToReadonly())
    for message of messages {
      if count == 0 { Assert.equal(textField(message, "event"), "工具"); Assert.equal(intField(message, "seq"), 7) }
      count += 1
    }
  }
  Assert.equal(count, 2)
  try! decoder.finish()
  batched := try! DapDecoder {}.feed(wire)
  Assert.equal(batched.length, 2)
}

export function testDapFramingRejectsInvalidAndTruncatedMessages(): none {
  for wire of ["Bad: 2\r\n\r\n{}", "Content-Length: -1\r\n\r\n", "Content-Length: 99999999999\r\n\r\n", "Content-Length: 2\r\nContent-Length: 2\r\n\r\n{}", "Content-Length: 1\r\n\r\n!"] {
    result := DapDecoder {}.feed(bytesOf(wire))
    Assert.equal(result.isFailure(), true)
  }
  decoder := DapDecoder {}
  try! decoder.feed(bytesOf("Content-Length: 10\r\n\r\n{}"))
  Assert.equal(decoder.finish().isFailure(), true)
}
