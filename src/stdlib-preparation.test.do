import {
  StdlibPreparationTarget, applyStdlibPreparationSubstitutions,
} from "./stdlib-preparation"
import { Assert } from "std/assert"

export function testAppliesStdlibPreparationSubstitutions(): none {
  actual := applyStdlibPreparationSubstitutions(
    "\${packageRoot}|\${jobs}|\${nativeTarget}|\${sdkPath}|\${targetTriple}|\${configureHost}",
    "/stdlib/http",
    StdlibPreparationTarget {
      nativeTarget: "linux", jobs: 4, sdkPath: "/sdk",
      targetTriple: "wasm32-unknown-emscripten", configureHost: "wasm32-unknown-emscripten",
    },
  )
  Assert.equal(actual, "/stdlib/http|4|linux|/sdk|wasm32-unknown-emscripten|wasm32-unknown-emscripten")
}
