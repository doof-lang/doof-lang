import { Assert } from "std/assert"
import { nativeTaskStateIsCurrent } from "./native-build-driver"
import { NativeInputSignature, NativeTaskState } from "./native-build-state"

function sampleTaskState(): NativeTaskState {
  return NativeTaskState {
    id: "object:main",
    fingerprint: "compiler-and-arguments",
    outputPath: "/build/main.o",
    outputSize: 40L,
    outputModifiedNanos: 50L,
    inputs: [NativeInputSignature {
      path: "/src/main.cpp", signature: "source-hash", contentHash: true, size: 30L, modifiedNanos: 35L,
    }],
  }
}

export function testInvalidatesNativeTaskStateConservatively(): none {
  state := sampleTaskState()
  inputs := [NativeInputSignature {
    path: "/src/main.cpp", signature: "source-hash", contentHash: true, size: 30L, modifiedNanos: 35L,
  }]
  Assert.equal(nativeTaskStateIsCurrent(state, "compiler-and-arguments", 40L, 50L, inputs), true)
  Assert.equal(nativeTaskStateIsCurrent(state, "changed-arguments", 40L, 50L, inputs), false)
  Assert.equal(nativeTaskStateIsCurrent(state, "compiler-and-arguments", 41L, 50L, inputs), false)
  Assert.equal(nativeTaskStateIsCurrent(state, "compiler-and-arguments", 40L, 51L, inputs), false)
  inputs[0].signature = "changed-source"
  Assert.equal(nativeTaskStateIsCurrent(state, "compiler-and-arguments", 40L, 50L, inputs), false)
  inputs[0] = NativeInputSignature {
    path: "/src/main.cpp", signature: "source-hash", contentHash: true, size: 30L, modifiedNanos: 36L,
  }
  Assert.equal(nativeTaskStateIsCurrent(state, "compiler-and-arguments", 40L, 50L, inputs), false)
  Assert.equal(nativeTaskStateIsCurrent(none, "compiler-and-arguments", 40L, 50L, []), false)
}
