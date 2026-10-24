// Pure planning for standard-package vendor builds.
//
// A standard package may ship a vendor/ tree with a build.sh (or build.ps1 on
// Windows). The native driver copies the emitted vendor tree into a private
// build directory, runs the script there with this module's environment, and
// consumes the include/ and lib/ directories the copy then contains.

import { NativeBuildMode, NativeVendorToolchain } from "./native-build"
import { NativeVendorBuild } from "./package-manifest"
import { join } from "std/string"
import { sha256HexString } from "std/crypto"

readonly VENDOR_BUILD_SCHEMA = 1

/** Directory under the output directory that holds private vendor builds. */
export readonly vendorBuildRoot = ".doof-vendor"

/** Completion receipt written into a vendor build directory after it succeeds. */
export readonly vendorBuildReceiptName = ".doof-vendor-build.json"

/** Recorded completion of one vendor build, also read by release snapshots. */
export class VendorBuildReceipt {
  schemaVersion: int
  packageName: string
  key: string
  fingerprint: string
  // Output-relative pristine vendor tree the build directory was copied from.
  source: string
  script: string
  environment: Map<string, string>
}

/** One process invocation of a vendor build script. */
export class VendorScriptCommand {
  program: string
  arguments: string[]
}

/** Names the script a platform runs; Windows uses PowerShell, others POSIX sh. */
export function vendorScriptName(platform: string): string {
  return if platform == "windows" then "build.ps1" else "build.sh"
}

export function vendorScriptCommand(platform: string): VendorScriptCommand {
  if platform == "windows" {
    return VendorScriptCommand {
      program: "powershell.exe",
      arguments: ["-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", "build.ps1"],
    }
  }
  return VendorScriptCommand { program: "sh", arguments: ["build.sh"] }
}

export function nativeBuildModeName(mode: NativeBuildMode): string {
  return case mode {
    .Debug -> "debug",
    .InteractiveDebug -> "interactive-debug",
    .Release -> "release",
    .Profile -> "profile",
  }
}

/** Environment variables a vendor build script receives in addition to the inherited environment. */
export function vendorBuildEnvironment(
  toolchain: NativeVendorToolchain,
  platform: string,
  mode: NativeBuildMode,
  jobs: int,
): Map<string, string> {
  let environment: Map<string, string> = {
    CC: toolchain.cc,
    CXX: toolchain.cxx,
    AR: toolchain.ar,
    CFLAGS: join(toolchain.cflags.cloneReadonly(), " "),
    CXXFLAGS: join(toolchain.cxxflags.cloneReadonly(), " "),
    DOOF_PLATFORM: platform,
    DOOF_MODE: nativeBuildModeName(mode),
    DOOF_JOBS: string(if jobs < 1 then 1 else jobs),
  }
  // libtool indexes archives itself; it needs the LTO-aware ranlib that
  // matches AR, or LTO objects lose their symbol index.
  if toolchain.ranlib != "" { environment.set("RANLIB", toolchain.ranlib) }
  return environment
}

/**
 * Identifies one vendor build for one target.
 *
 * The manifest key stands in for the vendored content, so large trees are
 * never hashed. The scripts are hashed because they are small and are the
 * part most often edited while a package is developed.
 */
export function vendorBuildFingerprint(
  build: NativeVendorBuild,
  environment: Map<string, string>,
  compilerIdentity: string,
  scriptContent: string,
): string {
  let value = "schema=" + string(VENDOR_BUILD_SCHEMA) + "\npackage=" + build.packageName + "\nkey=" + build.key
  // Parallelism changes how long a build takes, not what it produces.
  for name of sortedKeys(environment) {
    if name != "DOOF_JOBS" { value += "\n" + name + "=" + environment.get(name)! }
  }
  value += "\ncompiler=" + compilerIdentity + "\nscript=" + sha256HexString(scriptContent)
  for library of build.staticLibraries { value += "\nstatic=" + library }
  for library of build.bundleLibraries { value += "\nbundle=" + library }
  return sha256HexString(value)
}

/** Groups a package's builds so a new fingerprint can retire older siblings. */
export function vendorBuildPrefix(packageName: string): string {
  return packageName.replaceAll("/", "-") + "-"
}

/** Output-relative directory of one fingerprinted vendor build. */
export function vendorBuildDirectory(packageName: string, fingerprint: string): string {
  return vendorBuildRoot + "/" + vendorBuildPrefix(packageName) + fingerprint.substring(0, 16)
}

/** Lists declared lib/ outputs absent from a finished build directory listing. */
export function missingVendorOutputs(build: NativeVendorBuild, present: (relativePath: string): bool): string[] {
  let missing: string[] = []
  for library of build.staticLibraries { if !present("lib/" + library) { missing.push("lib/" + library) } }
  for library of build.bundleLibraries { if !present("lib/" + library) { missing.push("lib/" + library) } }
  return missing
}

function sortedKeys(values: Map<string, string>): string[] {
  let keys: string[] = []
  for key, _ of values {
    keys.push(key)
    let index = keys.length - 1
    while index > 0 && keys[index - 1] > key {
      keys[index] = keys[index - 1]
      index -= 1
    }
    keys[index] = key
  }
  return keys
}
