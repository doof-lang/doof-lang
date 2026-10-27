import { Assert } from "std/assert"
import {
  collectNestedCode, copyBundleResource, ensureDirectory, globBaseDirectory, globMatches, removeTree,
} from "./app-bundle-files"
import { exists, readText, writeText } from "std/fs"
import { Instant } from "std/time"

function scratchRoot(name: string): string {
  root := "/tmp/doof-app-bundle-files-" + name + "-" + string(Instant.now().toEpochMillis())
  ensureDirectory(root)
  return root
}

function failureMessage(result: Result<none, string>): string {
  return case result {
    _: Success -> "",
    failure: Failure -> failure.error,
  }
}

export function testGlobMatchesSingleAndDoubleStar(): none {
  Assert.isTrue(globMatches("*.png", "icon.png"))
  Assert.isFalse(globMatches("*.png", "images/icon.png"), "single star must not cross directories")
  Assert.isTrue(globMatches("**/*.png", "images/hd/icon.png"))
  Assert.isTrue(globMatches("**", "a/b/c"))
  Assert.isFalse(globMatches("*.png", "icon.jpg"))
  Assert.isTrue(globMatches("", ""))
}

export function testGlobBaseDirectoryStopsBeforeWildcardSegment(): none {
  Assert.equal(globBaseDirectory("/pkg/assets/*.png"), "/pkg/assets")
  Assert.equal(globBaseDirectory("/pkg/assets/img*/a.png"), "/pkg/assets")
  Assert.equal(globBaseDirectory("/pkg/assets/a.png"), "/pkg/assets")
  Assert.equal(globBaseDirectory("/*.png"), "/")
}

export function testCopiesFileDirectoryAndGlobResources(): none {
  root := scratchRoot("copy")
  ensureDirectory(root + "/pkg/assets/sub")
  writeText(root + "/pkg/assets/a.png", "a")!
  writeText(root + "/pkg/assets/sub/b.png", "b")!
  writeText(root + "/pkg/assets/notes.txt", "notes")!
  writeText(root + "/pkg/config.json", "{}")!
  let destinations: string[] = []
  bundle := root + "/App.app"
  copyBundleResource(root + "/pkg/config.json", "", bundle, destinations, "macOS")!
  copyBundleResource(root + "/pkg/assets", "data", bundle, destinations, "macOS")!
  copyBundleResource(root + "/pkg/assets/*.png", "icons", bundle, destinations, "macOS")!
  Assert.equal(readText(bundle + "/config.json")!, "{}")
  Assert.equal(readText(bundle + "/data/sub/b.png")!, "b")
  Assert.equal(readText(bundle + "/data/notes.txt")!, "notes")
  Assert.equal(readText(bundle + "/icons/a.png")!, "a")
  Assert.isFalse(exists(bundle + "/icons/sub/b.png"), "single-star glob must not copy nested files")
  Assert.isFalse(exists(bundle + "/icons/notes.txt"))
  removeTree(root)
}

export function testUnmatchedResourceReportsPattern(): none {
  root := scratchRoot("unmatched")
  let destinations: string[] = []
  message := failureMessage(copyBundleResource(root + "/missing/*.png", "", root + "/App.app", destinations, "macOS"))
  Assert.isTrue(message.contains("No files matched resource pattern: " + root + "/missing/*.png"), message)
  removeTree(root)
}

export function testDuplicateDestinationNamesPlatform(): none {
  root := scratchRoot("duplicate")
  ensureDirectory(root + "/one")
  ensureDirectory(root + "/two")
  writeText(root + "/one/a.txt", "one")!
  writeText(root + "/two/a.txt", "two")!
  let destinations: string[] = []
  bundle := root + "/App.app"
  copyBundleResource(root + "/one/a.txt", "", bundle, destinations, "iOS")!
  message := failureMessage(copyBundleResource(root + "/two/a.txt", "", bundle, destinations, "iOS"))
  Assert.isTrue(message.contains("Duplicate iOS app resource destination: " + bundle + "/a.txt"), message)
  Assert.equal(readText(bundle + "/a.txt")!, "one", "a rejected duplicate must not overwrite the first copy")
  removeTree(root)
}

export function testCollectNestedCodeListsInnermostFirst(): none {
  root := scratchRoot("nested")
  ensureDirectory(root + "/Frameworks/Outer.framework/Frameworks/Inner.framework")
  ensureDirectory(root + "/Frameworks/Helper.xpc")
  writeText(root + "/Frameworks/libz.dylib", "")!
  writeText(root + "/Frameworks/readme.txt", "")!
  let nested: string[] = []
  collectNestedCode(root + "/Frameworks", [".framework", ".appex"], nested)
  inner := nested.indexOf(root + "/Frameworks/Outer.framework/Frameworks/Inner.framework")
  outer := nested.indexOf(root + "/Frameworks/Outer.framework")
  Assert.isTrue(inner >= 0 && outer > inner, "inner frameworks must be signed before their container")
  Assert.isTrue(nested.contains(root + "/Frameworks/libz.dylib"))
  Assert.isFalse(nested.contains(root + "/Frameworks/Helper.xpc"), "unlisted bundle extensions are skipped")
  Assert.isFalse(nested.contains(root + "/Frameworks/readme.txt"))
  let missing: string[] = []
  collectNestedCode(root + "/Missing", [".framework"], missing)
  Assert.equal(missing.length, 0)
  removeTree(root)
}
