import { Assert } from "std/assert"
import { DebugTransport } from "./transport"
import { BlobReader } from "std/blob"
import { Duration, Thread } from "std/time"

export function testTransportDrainsSeparateStreamsAndCloses(): none {
  process := try! DebugTransport.start("/bin/sh", ["-c", "printf protocol; printf diagnostic >&2"])
  let out = ""
  let err = ""
  for i of 0..<100 {
    bytes := process.read(false)
    errors := process.read(true)
    if bytes.length > 0 { out += BlobReader(bytes).readTextLossy(bytes.length) }
    if errors.length > 0 { err += BlobReader(errors).readTextLossy(errors.length) }
    if !process.stdoutOpen() && !process.running() { break }
    Thread.sleep(Duration.ofMillis(10L))
  }
  Assert.equal(out, "protocol")
  Assert.equal(err, "diagnostic")
  process.close()
  Assert.equal(process.running(), false)
}

export function testTransportNonblockingRoundTripAndCancellation(): none {
  process := try! DebugTransport.start("/bin/cat", [])
  let payload = "工具"
  for i of 0..<15 { payload += payload }
  try! process.send(payload)
  let count = 0
  for i of 0..<1000 {
    process.flush()
    count += process.read(false).length
    if count == 196608 { break }
    Thread.sleep(Duration.ofMillis(1L))
  }
  Assert.equal(count, 196608)
  process.close()
  Assert.equal(process.running(), false)
  Assert.equal(process.send("closed").isFailure(), true)
}
