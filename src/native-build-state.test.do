import { Assert } from "std/assert"
import {
  NATIVE_BUILD_STATE_VERSION, NativeBuildState, NativeInputSignature, NativeTaskState,
  findNativeTaskState, parseMakeDependencies, parseNativeBuildState, renderNativeBuildState,
} from "./native-build-state"

export function testParsesMakeDependenciesWithContinuationsAndEscapedSpaces(): none {
  dependencies := parseMakeDependencies("build/main.o: src/main.cpp include/a.hpp \\\n include/path\\ with\\ spaces.hpp include/a.hpp\n")
  Assert.equal(dependencies.length, 3)
  Assert.equal(dependencies[0], "src/main.cpp")
  Assert.equal(dependencies[1], "include/a.hpp")
  Assert.equal(dependencies[2], "include/path with spaces.hpp")
  Assert.equal(parseMakeDependencies("missing target separator").length, 0)
}

export function testRoundTripsVersionedNativeBuildState(): none {
  state := NativeBuildState {
    tasks: [NativeTaskState {
      id: "object:main",
      fingerprint: "abc",
      outputPath: "/build/main.o",
      outputSize: 42L,
      outputModifiedNanos: 99L,
      inputs: [NativeInputSignature { path: "/src/main.cpp", signature: "def" }],
    }],
    managedOutputs: ["/build/main.o"],
  }
  parsed := parseNativeBuildState(renderNativeBuildState(state))
  Assert.equal(parsed != none, true)
  task := findNativeTaskState(parsed!, "object:main")
  Assert.equal(task != none, true)
  Assert.equal(task!.inputs[0].signature, "def")
  Assert.equal(parsed!.version, NATIVE_BUILD_STATE_VERSION)
  Assert.equal(parseNativeBuildState("{\"version\":999}"), none)
  Assert.equal(parseNativeBuildState("not json"), none)
}
