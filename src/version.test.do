import { Assert as EditorAssert } from "std/assert"
import { compilerVersion, compilerVersionStamped, versionCacheIdentity } from "./version"
import { readText } from "std/fs"
import { parseJsonValue } from "std/json"

export function testEditorCompilerVersionMatchesManifest(): none {
  manifest := try! (try! parseJsonValue(try! readText("doof.json"))) as SerialObject
  version := try! (try! manifest.get("version")) as string
  EditorAssert.equal(compilerVersion, if compilerVersionStamped then version else version + "-dev.unstamped")
}

export function testVersionCacheIdentityRequiresStamp(): none {
  EditorAssert.equal(versionCacheIdentity("0.2.0", false), "")
  EditorAssert.equal(versionCacheIdentity("", true), "")
  EditorAssert.equal(versionCacheIdentity("0.2.0", true), "0.2.0")
}

export function testVersionCacheIdentityTracksBuilds(): none {
  EditorAssert.equal(versionCacheIdentity("0.2.0", true), versionCacheIdentity("0.2.0", true))
  EditorAssert.isTrue(versionCacheIdentity("0.2.0", true) != versionCacheIdentity("0.2.1", true))
  EditorAssert.isTrue(versionCacheIdentity("0.2.0-dev.one", true) != versionCacheIdentity("0.2.0-dev.two", true))
}
