import { Assert } from "std/assert"
import {
  NATIVE_BUILD_STATE_VERSION, NativeBuildState, NativeInputSignature, NativeTaskState,
  parseMakeDependencies, parseMsvcDependencies, parseNativeBuildState, renderNativeBuildState,
} from "./native-build-state"

export function testParsesMakeDependenciesWithContinuationsAndEscapedSpaces(): none {
  dependencies := parseMakeDependencies("build/main.o: src/main.cpp include/a.hpp \\\n include/path\\ with\\ spaces.hpp include/a.hpp\n")
  Assert.equal(dependencies.length, 3)
  Assert.equal(dependencies[0], "src/main.cpp")
  Assert.equal(dependencies[1], "include/a.hpp")
  Assert.equal(dependencies[2], "include/path with spaces.hpp")
  Assert.equal(parseMakeDependencies("missing target separator").length, 0)
}

export function testParsesMsvcSourceDependencies(): none {
  dependencies := parseMsvcDependencies(
    "{\"Version\":\"1.2\",\"Data\":{\"Source\":\"C:\\\\src\\\\main.cpp\",\"Includes\":[\"C:\\\\src\\\\main.hpp\",\"C:\\\\sdk\\\\vector\",\"C:\\\\src\\\\main.hpp\"]}}",
  )
  Assert.equal(dependencies.length, 2)
  Assert.equal(dependencies[0], "C:\\src\\main.hpp")
  Assert.equal(dependencies[1], "C:\\sdk\\vector")
  Assert.equal(parseMsvcDependencies("{}").length, 0)
  Assert.equal(parseMsvcDependencies("not json").length, 0)
}

export function testRoundTripsVersionedNativeBuildState(): none {
  state := NativeBuildState {
    tasks: [NativeTaskState {
      id: "object:main",
      fingerprint: "abc",
      outputPath: "/build/main.o",
      outputSize: 42L,
      outputModifiedNanos: 99L,
      inputs: [NativeInputSignature { path: "/src/main.cpp", signature: "def", size: 12L, modifiedNanos: 13L }],
    }],
    managedOutputs: ["/build/main.o"],
  }
  parsed := parseNativeBuildState(renderNativeBuildState(state))
  Assert.equal(parsed != none, true)
  Assert.equal(parsed!.tasks.length, 1)
  Assert.equal(parsed!.tasks[0].id, "object:main")
  Assert.equal(parsed!.tasks[0].inputs[0].signature, "def")
  Assert.equal(parsed!.tasks[0].inputs[0].size, 12L)
  Assert.equal(parsed!.version, NATIVE_BUILD_STATE_VERSION)
  Assert.equal(parseNativeBuildState("{\"version\":999}"), none)
  Assert.equal(parseNativeBuildState("not json"), none)
}
