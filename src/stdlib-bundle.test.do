import { TarWriteEntry, readTarBlob, writeTarBlob } from "std/archive"
import { BlobBuilder } from "std/blob"
import { sha256Hex, sha256HexString } from "std/crypto"
import { EntryKind, exists, mkdir, readBlob, readDir, readText, remove, writeBlob, writeText } from "std/fs"
import { formatJsonValue } from "std/json"
import { ExecOptions, platform, run } from "std/os"
import { join } from "std/path"
import { zstdCompressWithLevel } from "std/zstd"
import { materializeStdlibBundlePackage, openStdlibBundle, stdlibBundleTargetKey } from "./stdlib-bundle"

function bundleTestPath(directory: string, name: string): string => join([directory, name])

function removeBundleTestTree(target: string): none {
  if !exists(target) { return }
  entries := try! readDir(target)
  for entry of entries {
    child := bundleTestPath(target, entry.name)
    if entry.kind == EntryKind.Directory { removeBundleTestTree(child) } else { try! remove(child) }
  }
  try! remove(target)
}

class TestBundleMember {
  kind: string
  logicalPath: string
  memberPath: string
  data: readonly byte[]
  sourceBytes: long
  mode: int = 420
}

function bundleTestBytes(text: string): readonly byte[] {
  builder := BlobBuilder()
  builder.writeString(text)
  return builder.build()
}

function compressedTestMember(path: string, source: string, mode: int = 420): readonly byte[] {
  tar := writeTarBlob(readonly [TarWriteEntry { name: path, data: bundleTestBytes(source), mode }])
  return try! zstdCompressWithLevel(tar, 3)
}

function testMemberJson(member: TestBundleMember): JsonObject {
  let value: JsonObject = {}
  value.set("kind", member.kind)
  value.set("packageName", "std/json")
  value.set("path", member.logicalPath)
  value.set("member", member.memberPath)
  value.set("sourceBytes", member.sourceBytes)
  value.set("compressedBytes", long(member.data.length))
  value.set("sha256", sha256Hex(member.data))
  return value
}

function fixtureBundle(customNativeEntries: TarWriteEntry[] | none = none): readonly byte[] {
  manifestSource := "{\"name\":\"std/json\",\"version\":\"0.1.0\",\"dependencies\":{}}\n"
  indexSource := "export function answer(): int => 42\n"
  nestedSource := "export readonly VALUE = 7\n"
  scriptSource := "#!/bin/sh\nexit 0\n"
  let nativeTarEntries: TarWriteEntry[] = [
    TarWriteEntry { name: "prepare.sh", data: bundleTestBytes(scriptSource), mode: 493 },
  ]
  if customNativeEntries != none { nativeTarEntries = customNativeEntries! }
  nativeData := try! zstdCompressWithLevel(writeTarBlob(nativeTarEntries.cloneReadonly()), 3)
  let members: TestBundleMember[] = [
    TestBundleMember {
      kind: "manifest", logicalPath: "doof.json", memberPath: "manifests/json.tar.zst",
      data: compressedTestMember("doof.json", manifestSource), sourceBytes: long(bundleTestBytes(manifestSource).length),
    },
    TestBundleMember {
      kind: "module", logicalPath: "index.do", memberPath: "modules/json/index.do.tar.zst",
      data: compressedTestMember("index.do", indexSource), sourceBytes: long(bundleTestBytes(indexSource).length),
    },
    TestBundleMember {
      kind: "module", logicalPath: "nested/value.do", memberPath: "modules/json/nested/value.do.tar.zst",
      data: compressedTestMember("nested/value.do", nestedSource), sourceBytes: long(bundleTestBytes(nestedSource).length),
    },
    TestBundleMember {
      kind: "native", logicalPath: "", memberPath: "native/json.tar.zst",
      data: nativeData, sourceBytes: long(bundleTestBytes(scriptSource).length),
    },
  ]
  let canonical = "schema=4\ntarget=linux\ntarget=macos\npackage=std/json\n"
  let memberValues: JsonValue[] = []
  for member of members {
    canonical += "member=" + member.kind + "\u0000std/json\u0000" + member.logicalPath + "\u0000" +
      member.memberPath + "\u0000" + string(member.sourceBytes) + "\u0000" + string(member.data.length) +
      "\u0000" + sha256Hex(member.data) + "\n"
    memberValues.push(testMemberJson(member))
  }
  let index: JsonObject = {}
  index.set("schemaVersion", 4)
  index.set("format", "doof-stdlib-tar-of-tar-zst")
  index.set("bundleDigest", sha256HexString(canonical))
  index.set("zstdLevel", 3)
  index.set("targets", ["linux", "macos"])
  index.set("packages", ["std/json"])
  index.set("members", memberValues)
  index.set("licenseFiles", readonly [])
  let outer: TarWriteEntry[] = [
    TarWriteEntry { name: "bundle-index.json", data: bundleTestBytes(formatJsonValue(index) + "\n") },
  ]
  for member of members { outer.push(TarWriteEntry { name: member.memberPath, data: member.data }) }
  return writeTarBlob(outer.cloneReadonly())
}

function createBundleReaderFixture(root: string): string {
  removeBundleTestTree(root)
  try! mkdir(root)
  bundlePath := bundleTestPath(root, "doof-stdlib.tar")
  try! writeBlob(bundlePath, fixtureBundle())
  return bundlePath
}

function failureText<T>(result: Result<T, string>): string {
  return case result {
    _: Success -> "",
    failure: Failure -> failure.error,
  }
}

export function testMaterializesAddressableStdlibBundlePackage(): none {
  root := "build/stdlib-bundle-reader-test"
  bundlePath := createBundleReaderFixture(root)
  provider := try! openStdlibBundle(bundlePath)
  assert(provider.index.bundleDigest.length == 64, "expected bundle digest")
  targetKey := stdlibBundleTargetKey("macos", "", "", "")
  materialized := try! materializeStdlibBundlePackage(
    provider, "std/json", bundleTestPath(root, "packages"), targetKey, "macos",
  )
  assert(try! readText(bundleTestPath(materialized.rootDirectory, "index.do")) == "export function answer(): int => 42\n", "expected root module")
  assert(try! readText(bundleTestPath(materialized.rootDirectory, "nested/value.do")) == "export readonly VALUE = 7\n", "expected nested module")
  assert(exists(bundleTestPath(materialized.rootDirectory, ".doof-stdlib-bundle.json")), "expected receipt")
  if platform() != "windows" {
    executable := try! run("test", ["-x", bundleTestPath(materialized.rootDirectory, "prepare.sh")], ExecOptions { withStdin: false })
    assert(executable.exitCode == 0, "expected executable archive mode")
  }
  otherTarget := try! materializeStdlibBundlePackage(
    provider, "std/json", bundleTestPath(root, "packages"),
    stdlibBundleTargetKey("linux", "", "", ""),
    "linux",
  )
  assert(otherTarget.rootDirectory != materialized.rootDirectory, "expected target-separated materialization")
  removeBundleTestTree(root)
}

export function testRejectsUnknownStdlibBundlePackage(): none {
  root := "build/stdlib-bundle-catalog-mismatch-test"
  bundlePath := createBundleReaderFixture(root)
  provider := try! openStdlibBundle(bundlePath)
  message := failureText(materializeStdlibBundlePackage(
    provider, "std/missing", bundleTestPath(root, "packages"), stdlibBundleTargetKey("macos", "", "", ""), "macos",
  ))
  assert(message.contains("Unknown standard package"), "expected unknown-package diagnostic")
  removeBundleTestTree(root)
}

export function testRejectsStdlibBundleForUnsupportedTarget(): none {
  root := "build/stdlib-bundle-target-mismatch-test"
  bundlePath := createBundleReaderFixture(root)
  provider := try! openStdlibBundle(bundlePath)
  message := failureText(materializeStdlibBundlePackage(
    provider, "std/json", bundleTestPath(root, "packages"),
    stdlibBundleTargetKey("windows", "", "", ""), "windows",
  ))
  assert(message.contains("does not support target windows"), "expected actionable target diagnostic")
  removeBundleTestTree(root)
}

export function testRejectsCorruptedStdlibBundleMemberOnMaterialization(): none {
  root := "build/stdlib-bundle-corruption-test"
  bundlePath := createBundleReaderFixture(root)
  bytes := try! readBlob(bundlePath)
  archive := try! readTarBlob(bytes)
  let memberOffset = -1L
  for entry of archive.entries {
    if entry.name == "modules/json/index.do.tar.zst" { memberOffset = entry.contentOffset }
  }
  assert(memberOffset >= 0L, "expected module member")
  builder := BlobBuilder()
  builder.writeBytes(bytes)
  builder.setPosition(memberOffset)
  builder.writeByte(byte((int(bytes[int(memberOffset)]) + 1) % 256))
  try! writeBlob(bundlePath, builder.build())
  provider := try! openStdlibBundle(bundlePath)
  message := failureText(materializeStdlibBundlePackage(
    provider, "std/json", bundleTestPath(root, "packages"),
    stdlibBundleTargetKey("macos", "", "", ""),
    "macos",
  ))
  assert(message.contains("SHA-256"), "expected member integrity diagnostic")
  removeBundleTestTree(root)
}

export function testRejectsUnsafeAndDuplicateInnerEntries(): none {
  let cases: TarWriteEntry[][] = []
  cases.push([TarWriteEntry { name: "../escape", data: bundleTestBytes("no") }])
  cases.push([TarWriteEntry { name: "directory/", kind: .Directory }])
  cases.push(
    [
      TarWriteEntry { name: "duplicate", data: bundleTestBytes("one") },
      TarWriteEntry { name: "duplicate", data: bundleTestBytes("two") },
    ],
  )
  for entries of cases {
    root := "build/stdlib-bundle-unsafe-test"
    removeBundleTestTree(root)
    try! mkdir(root)
    bundlePath := bundleTestPath(root, "doof-stdlib.tar")
    try! writeBlob(bundlePath, fixtureBundle(entries))
    provider := try! openStdlibBundle(bundlePath)
    message := failureText(materializeStdlibBundlePackage(
      provider, "std/json", bundleTestPath(root, "packages"),
      stdlibBundleTargetKey("macos", "", "", ""),
      "macos",
    ))
    assert(message.contains("unsafe") || message.contains("duplicates"), "expected unsafe inner-entry diagnostic")
    removeBundleTestTree(root)
  }
}

export function testRejectsMissingOuterMember(): none {
  root := "build/stdlib-bundle-missing-member-test"
  removeBundleTestTree(root)
  try! mkdir(root)
  original := try! readTarBlob(fixtureBundle())
  let incomplete: TarWriteEntry[] = []
  for entry of original.entries {
    if entry.name != "modules/json/index.do.tar.zst" {
      incomplete.push(TarWriteEntry { name: entry.name, data: original.entryData(entry), mode: entry.mode })
    }
  }
  bundlePath := bundleTestPath(root, "doof-stdlib.tar")
  try! writeBlob(bundlePath, writeTarBlob(incomplete.cloneReadonly()))
  message := failureText(openStdlibBundle(bundlePath))
  assert(message.contains("does not match its index") || message.contains("missing"), "expected missing-member diagnostic")
  removeBundleTestTree(root)
}
