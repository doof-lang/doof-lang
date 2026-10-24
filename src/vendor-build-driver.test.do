// Runs real vendor scripts in hermetic temporary output directories.
import { Assert } from "std/assert"
import { exists, isDirectory, mkdir, readDir, readText, remove, writeText } from "std/fs"
import { platform } from "std/os"
import { join, tempDirectory } from "std/path"
import { uuidV4 } from "std/crypto"
import { NativeVendorToolchain } from "./native-build"
import { NativeBuildPlan, NativeVendorBuild } from "./package-manifest"
import { prepareVendorBuilds } from "./vendor-build-driver"

function erase(path: string): none {
  if !exists(path) { return }
  if isDirectory(path) { for entry of readDir(path)! { erase(join([path, entry.name])) } }
  remove(path)!
}

// The emitted vendor tree sits at std/demo/vendor below the output directory.
function fixture(script: string): string {
  root := join([tempDirectory(), "doof-vendor-build-" + uuidV4()])
  for directory of [root, root + "/std", root + "/std/demo", root + "/std/demo/vendor", root + "/std/demo/vendor/headers"] { mkdir(directory)! }
  writeText(root + "/std/demo/vendor/headers/demo.h", "int demo(void);\n")!
  if script != "" { writeText(root + "/std/demo/vendor/build.sh", script)! }
  return root
}

function plan(staticLibraries: string[]): NativeBuildPlan {
  return NativeBuildPlan { vendorBuilds: [NativeVendorBuild {
    packageName: "std/demo", key: "demo-1", directory: "std/demo/vendor", staticLibraries,
  }] }
}

function toolchain(): NativeVendorToolchain {
  return NativeVendorToolchain { cc: "cc", cxx: "c++", ar: "ar", cflags: ["-O2"], cxxflags: ["-std=c++17", "-O2"] }
}

function prepare(root: string, native: NativeBuildPlan): Result<none, string> {
  return prepareVendorBuilds(root, native, toolchain(), "compiler", "linux", .Debug, false)
}

readonly countingScript = "set -eu\nmkdir -p include lib\ncp headers/demo.h include/\nprintf '%s' \"$CFLAGS\" > lib/libdemo.a\necho run >> ../../runs-$DOOF_PLATFORM\n"

export function testVendorBuildRunsOnceAndPublishesOutputs(): none {
  if platform() == "windows" { return }
  root := fixture(countingScript)
  native := plan(["libdemo.a"])
  prepare(root, native)!
  Assert.equal(native.includePaths.length, 1)
  Assert.isTrue(native.includePaths[0].startsWith(".doof-vendor/std-demo-"))
  Assert.isTrue(native.includePaths[0].endsWith("/include"))
  Assert.isTrue(exists(join([root, native.includePaths[0], "demo.h"])))
  Assert.equal(native.linkInputs.length, 1)
  Assert.equal(readText(native.linkInputs[0])!, "-O2")
  // The pristine emitted tree never receives build products.
  Assert.isFalse(exists(root + "/std/demo/vendor/lib"))

  // An unchanged fingerprint reuses the finished build without rerunning it.
  again := plan(["libdemo.a"])
  prepare(root, again)!
  Assert.equal(again.linkInputs[0], native.linkInputs[0])
  Assert.equal(readText(root + "/runs-linux")!, "run\n")
  erase(root)
}

export function testVendorBuildRebuildsAndRetiresOldFingerprints(): none {
  if platform() == "windows" { return }
  root := fixture("set -eu\nmkdir -p lib\n: > lib/libdemo.a\n")
  first := plan(["libdemo.a"])
  prepare(root, first)!
  writeText(root + "/std/demo/vendor/build.sh", "set -eu\nmkdir -p lib\necho changed > lib/libdemo.a\n")!
  second := plan(["libdemo.a"])
  prepare(root, second)!
  Assert.notEqual(second.linkInputs[0], first.linkInputs[0])
  Assert.equal(readText(second.linkInputs[0])!, "changed\n")
  Assert.equal(readDir(root + "/.doof-vendor")!.length, 1)
  erase(root)
}

export function testVendorBuildWithoutScriptPublishesStaticHeaders(): none {
  root := fixture("")
  mkdir(root + "/std/demo/vendor/include")!
  writeText(root + "/std/demo/vendor/include/static.h", "#define STATIC 1\n")!
  native := plan([])
  prepare(root, native)!
  Assert.isTrue(exists(join([root, native.includePaths[0], "static.h"])))
  Assert.equal(native.linkInputs.length, 0)
  erase(root)
}

export function testVendorBuildReportsFailuresWithScriptOutput(): none {
  if platform() == "windows" { return }
  root := fixture("echo compiler exploded\nexit 3\n")
  failed := prepare(root, plan(["libdemo.a"]))
  _ := failed else error {
    Assert.stringContains(error, "Vendor build.sh for std/demo exited with code 3")
    Assert.stringContains(error, "compiler exploded")
    erase(root)
    return
  }
  panic("expected vendor script failure")
}

export function testVendorBuildReportsMissingDeclaredOutputs(): none {
  if platform() == "windows" { return }
  root := fixture("mkdir -p lib\n")
  missing := prepare(root, plan(["libdemo.a"]))
  _ := missing else error {
    Assert.stringContains(error, "did not produce the outputs declared in build.native.vendor: lib/libdemo.a")
    // A failed build leaves no receipt, so the next build starts again.
    retried := prepare(root, plan(["libdemo.a"]))
    _ := retried else { erase(root); return }
    panic("expected the retried vendor build to fail again")
  }
  panic("expected missing vendor output failure")
}
