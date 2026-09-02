import { buildStdlibBundle, includeStdlibBundlePath } from "./stdlib-bundle"
import { readTarBlob } from "std/archive"
import { BlobReader } from "std/blob"
import { EntryKind, exists, mkdir, readDir, remove, writeText } from "std/fs"
import { parseJsonValue } from "std/json"
import { ExecOptions, run } from "std/os"
import { join } from "std/path"
import { zstdDecompress } from "std/zstd"

function path(directory: string, name: string): string => join([directory, name])

function removeTree(target: string): none {
  if !exists(target) { return }
  entries := try! readDir(target)
  for entry of entries {
    child := path(target, entry.name)
    if entry.kind == EntryKind.Directory { removeTree(child) } else { try! remove(child) }
  }
  try! remove(target)
}

function assertBytes(actual: readonly byte[], expected: readonly byte[]): none {
  assert(actual.length == expected.length, "expected equal byte lengths")
  for index of 0..<actual.length { assert(actual[index] == expected[index], "expected equal bytes") }
}

function entryData(archiveData: readonly byte[], name: string): readonly byte[] {
  archive := try! readTarBlob(archiveData)
  for entry of archive.entries {
    if entry.name == name { return archive.entryData(entry) }
  }
  assert(false, "missing archive entry " + name)
  return []
}

function text(data: readonly byte[]): string => BlobReader(data).readString(long(data.length))

function testCommand(program: string, arguments: string[]): string {
  result := try! run(program, arguments, ExecOptions { withStdin: false, mergeStderrIntoStdout: true })
  output := text(result.stdout).trim()
  assert(result.exitCode == 0, program + " failed: " + output)
  return output
}

export function testStdlibBundleCurationIsCoarseAndExplicit(): none {
  assert(includeStdlibBundlePath("std/json", "index.do"), "expected module")
  assert(!includeStdlibBundlePath("std/json", "index.test.do"), "expected colocated test exclusion")
  assert(!includeStdlibBundlePath("std/json", "docs/API.md"), "expected docs exclusion")
  assert(includeStdlibBundlePath("std/gzip", "vendor/zlib/inflate.c"), "expected zlib root source")
  assert(!includeStdlibBundlePath("std/gzip", "vendor/zlib/examples/zpipe.c"), "expected zlib examples exclusion")
  assert(includeStdlibBundlePath("std/http", "vendor/curl/lib/vtls/openssl.c"), "expected full curl lib")
  assert(includeStdlibBundlePath("std/http", "vendor/curl/Makefile.in"), "expected curl configure scaffold")
  assert(
    !includeStdlibBundlePath("std/http", "vendor/curl/lib/vtls/openssl.c", ["macos", "wasm"]),
    "expected Apple bundle to omit curl",
  )
  assert(
    !includeStdlibBundlePath("std/http", "vendor/curl/Makefile.in", ["wasm", "windows"]),
    "expected Windows bundle to omit curl",
  )
  assert(
    includeStdlibBundlePath("std/http", "vendor/curl/lib/vtls/openssl.c", ["linux", "wasm"]),
    "expected Linux bundle to retain curl",
  )
  assert(!includeStdlibBundlePath("std/http", "vendor/curl/tests/data/test1"), "expected curl tests exclusion")
  assert(!includeStdlibBundlePath("std/http", "vendor/curl/.doof-build/linux/lib/libcurl.a"), "expected target build-state exclusion")
  assert(!includeStdlibBundlePath("std/zstd", "vendor/zstd/.doof-external-native-linux.json"), "expected native receipt exclusion")
  assert(includeStdlibBundlePath("std/image", "vendor/libwebp/src/enc/webp_enc.c"), "expected full webp source")
  assert(includeStdlibBundlePath("std/image", "vendor/libwebp/src/dec/common_dec.h"), "expected encoder-coupled webp decoder headers")
  assert(includeStdlibBundlePath("std/image", "vendor/libwebp/src/dsp/filters.c"), "expected full webp dsp tree")
  assert(includeStdlibBundlePath("std/image", "vendor/libwebp/src/utils/bit_writer_utils.c"), "expected full webp utils tree")
  assert(includeStdlibBundlePath("std/image", "vendor/libwebp/src/webp/encode.h"), "expected full webp public headers")
  assert(includeStdlibBundlePath("std/image", "vendor/libwebp/sharpyuv/sharpyuv.c"), "expected full sharpyuv tree")
  assert(!includeStdlibBundlePath("std/image", "vendor/libwebp/src/demux/demux.c"), "expected unused webp demux exclusion")
  assert(!includeStdlibBundlePath("std/image", "vendor/libwebp/src/mux/muxedit.c"), "expected unused webp mux exclusion")
  assert(includeStdlibBundlePath("std/regex", "vendor/pcre2/src/pcre2_match.c"), "expected full PCRE2 source")
  assert(includeStdlibBundlePath("std/ts", "vendor/tree-sitter/lib/src/lib.c"), "expected tree-sitter library")
  assert(includeStdlibBundlePath("std/ts", "vendor/tree-sitter-typescript/common/scanner.h"), "expected grammar common source")
  assert(includeStdlibBundlePath("std/zstd", "vendor/zstd/lib/compress/zstd_compress.c"), "expected full zstd library")
}

export function testStdlibBundleCreatesDeterministicAddressableMembers(): none {
  root := "build/stdlib-bundle-test"
  removeTree(root)
  try! mkdir(root)
  packageRoot := path(root, "json")
  try! mkdir(packageRoot)
  try! mkdir(path(packageRoot, "nested"))
  try! mkdir(path(packageRoot, "tests"))
  try! writeText(path(packageRoot, "doof.json"), "{\"name\":\"std/json\",\"version\":\"0.1.0\",\"dependencies\":{}}\n")
  try! writeText(path(packageRoot, "index.do"), "export function answer(): int => 42\n")
  try! writeText(path(packageRoot, "nested/codec.do"), "export function encode(): string => \"ok\"\n")
  try! writeText(path(packageRoot, "index.test.do"), "export function testNope(): none {}\n")
  try! writeText(path(packageRoot, "native_json.hpp"), "// native\n")
  try! writeText(path(packageRoot, "tests/fixture.txt"), "excluded\n")

  catalog := "{\"schemaVersion\":1,\"compilerVersion\":\"0.1.0\",\"digest\":\"" +
    "0000000000000000000000000000000000000000000000000000000000000000\",\"packages\":[{" +
    "\"name\":\"std/json\",\"url\":\"https://example.invalid/json\",\"ref\":\"v0.1.0\"," +
    "\"version\":\"0.1.0\",\"commit\":\"0000000000000000000000000000000000000000\"}]}"
  first := try! buildStdlibBundle(root, 3)
  second := try! buildStdlibBundle(root, 3)
  assertBytes(first.data, second.data)
  assert(first.packageCount == 1, "expected one package")
  assert(first.moduleCount == 2, "expected production modules only")
  assert(first.nativePackageCount == 1, "expected native blob")

  indexSource := text(entryData(first.data, "bundle-index.json"))
  indexValue := try! parseJsonValue(indexSource)
  index := indexValue as JsonObject else { panic("expected bundle index object") }
  format := (try! index.get("format")) as string else { panic("expected bundle format string") }
  assert(format == "doof-stdlib-tar-of-tar-zst", "expected bundle format")
  schemaVersion := (try! index.get("schemaVersion")) as int else { panic("expected schema version") }
  assert(schemaVersion == 4, "expected target-aware bundle schema")
  targets := (try! index.get("targets")) as JsonValue[] else { panic("expected bundle targets") }
  assert(targets.length == 6, "expected default bundle to support every target")
  bundleDigest := (try! index.get("bundleDigest")) as string else { panic("expected bundle digest") }
  assert(bundleDigest == first.bundleDigest && bundleDigest.length == 64, "expected bundle identity")
  membersValue := (try! index.get("members")) as JsonValue[] else { panic("expected members") }
  firstMember := membersValue[0] as JsonObject else { panic("expected member object") }
  memberHash := (try! firstMember.get("sha256")) as string else { panic("expected member hash") }
  assert(memberHash.length == 64, "expected member SHA-256")

  moduleCompressed := entryData(first.data, "modules/json/nested/codec.do.tar.zst")
  moduleTar := try! zstdDecompress(moduleCompressed)
  assert(text(entryData(moduleTar, "nested/codec.do")) == "export function encode(): string => \"ok\"\n", "expected module payload")

  nativeCompressed := entryData(first.data, "native/json.tar.zst")
  nativeTar := try! zstdDecompress(nativeCompressed)
  nativeArchive := try! readTarBlob(nativeTar)
  assert(nativeArchive.entries.length == 1, "expected only build native material")
  assert(nativeArchive.entries[0].name == "native_json.hpp", "expected native header")
  removeTree(root)
}

export function testStdlibBundleIncludesCurlOnlyForLinuxProfiles(): none {
  root := "build/stdlib-bundle-curl-profile-test"
  removeTree(root)
  try! mkdir(root)
  packageRoot := path(root, "http")
  try! mkdir(packageRoot)
  try! mkdir(path(packageRoot, "vendor"))
  try! mkdir(path(packageRoot, "vendor/curl"))
  try! mkdir(path(packageRoot, "vendor/curl/lib"))
  try! writeText(path(packageRoot, "doof.json"), "{\"name\":\"std/http\",\"version\":\"0.1.0\",\"dependencies\":{}}\n")
  try! writeText(path(packageRoot, "index.do"), "export function get(): none {}\n")
  try! writeText(path(packageRoot, "native_http_client.hpp"), "// shared native input\n")
  try! writeText(path(packageRoot, "vendor/curl/COPYING"), "curl license\n")
  try! writeText(path(packageRoot, "vendor/curl/lib/easy.c"), "/* curl source */\n")

  apple := try! buildStdlibBundle(root, 3, ["macos", "wasm"])
  appleNative := try! readTarBlob(try! zstdDecompress(entryData(apple.data, "native/http.tar.zst")))
  assert(appleNative.entries.length == 1, "expected Apple native member to omit curl")
  assert(appleNative.entries[0].name == "native_http_client.hpp", "expected shared HTTP native input")

  linux := try! buildStdlibBundle(root, 3, ["linux", "wasm"])
  linuxNative := try! readTarBlob(try! zstdDecompress(entryData(linux.data, "native/http.tar.zst")))
  let foundCurlSource = false
  let foundCurlLicense = false
  for entry of linuxNative.entries {
    if entry.name == "vendor/curl/lib/easy.c" { foundCurlSource = true }
    if entry.name == "vendor/curl/COPYING" { foundCurlLicense = true }
  }
  assert(foundCurlSource, "expected Linux native member to retain curl source")
  assert(foundCurlLicense, "expected Linux native member to retain curl license")
  removeTree(root)
}

export function testStdlibBundleRejectsMissingVendoredLicense(): none {
  root := "build/stdlib-bundle-license-test"
  removeTree(root)
  try! mkdir(root)
  packageRoot := path(root, "image")
  try! mkdir(packageRoot)
  try! mkdir(path(packageRoot, "vendor"))
  try! mkdir(path(packageRoot, "vendor/libwebp"))
  try! writeText(path(packageRoot, "doof.json"), "{\"name\":\"std/image\",\"version\":\"0.1.0\",\"dependencies\":{}}\n")
  try! writeText(path(packageRoot, "index.do"), "export function width(): int => 1\n")
  try! writeText(path(packageRoot, "vendor/libwebp/COPYING"), "license\n")

  catalog := "{\"schemaVersion\":1,\"compilerVersion\":\"0.1.0\",\"digest\":\"" +
    "0000000000000000000000000000000000000000000000000000000000000000\",\"packages\":[{" +
    "\"name\":\"std/image\",\"url\":\"https://example.invalid/image\",\"ref\":\"v0.1.0\"," +
    "\"version\":\"0.1.0\",\"commit\":\"0000000000000000000000000000000000000000\"}]}"
  result := buildStdlibBundle(root, 3)
  message := case result {
    _: Success -> "",
    failure: Failure -> failure.error,
  }
  assert(message.contains("vendor/libwebp/PATENTS"), "expected actionable missing-license diagnostic")
  removeTree(root)
}
