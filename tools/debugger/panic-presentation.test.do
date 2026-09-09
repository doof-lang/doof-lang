import { Assert } from "std/assert"
import { panicMessageFromVariables } from "./panic-presentation"

export function testPanicMessageUsesRuntimeMessageArgument(): none {
  Assert.equal(panicMessageFromVariables([{ name: "other", value: "ignore" }, { name: "msg", value: "\"fixture panic\"" }]), "fixture panic")
  Assert.equal(panicMessageFromVariables([{ name: "msg", value: "0x1aB3 \"bounds failure\"" }]), "bounds failure")
  Assert.equal(panicMessageFromVariables([{ name: "msg", value: "0xG not an address" }]), "0xG not an address")
  Assert.equal(panicMessageFromVariables([]), "")
  Assert.equal(panicMessageFromVariables([none, { name: "msg" }]), "")
}
