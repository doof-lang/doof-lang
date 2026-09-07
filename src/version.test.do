import { Assert as EditorAssert } from "std/assert"
import { compilerVersion } from "./version"
import { readText } from "std/fs"
import { parseJsonValue } from "std/json"

export function testEditorCompilerVersionMatchesManifest(): none {
  manifest := try! (try! parseJsonValue(try! readText("doof.json"))) as JsonObject
  version := try! (try! manifest.get("version")) as string
  EditorAssert.equal(compilerVersion, version)
}
