import { Assert } from "std/assert"
import {
  FRONTEND_SEMANTIC_ABI,
  FrontendCacheState, FrontendFileInput, FrontendModuleOutput, FrontendSourceProbe,
  parseFrontendCacheState, renderFrontendCacheState,
} from "./frontend-cache"

export function testFrontendSemanticAbiInvalidatesPreValidationCaches(): none {
  Assert.equal(FRONTEND_SEMANTIC_ABI, 10)
}

export function testFrontendCacheStateRoundTrips(): none {
  state := FrontendCacheState {
    configurationFingerprint: "configuration",
    probes: [FrontendSourceProbe { logicalPath: "/main.do", sourceHash: "source" }],
    fileInputs: [FrontendFileInput { path: "/project/doof.json", sourceHash: "manifest" }],
    modules: [FrontendModuleOutput { modulePath: "/main.do", headerName: "main.hpp", sourceName: "main.cpp" }],
  }
  parsed := parseFrontendCacheState(renderFrontendCacheState(state))
  Assert.equal(parsed != none, true)
  Assert.equal(parsed!.configurationFingerprint, "configuration")
  Assert.equal(parsed!.probes[0].logicalPath, "/main.do")
  Assert.equal(parsed!.modules[0].sourceName, "main.cpp")
}

export function testFrontendCacheRejectsCorruptionAndSchemaMismatch(): none {
  Assert.equal(parseFrontendCacheState("not json"), none)
  Assert.equal(parseFrontendCacheState("{\"version\":99,\"configurationFingerprint\":\"old\"}"), none)
}
