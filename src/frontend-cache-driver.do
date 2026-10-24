// Frontend cache validation, recording, and stale-output cleanup.

import { compilerVersion, compilerVersionStamped, versionCacheIdentity } from "./version"
import { Compilation } from "./compiler"
import { ModuleEmission, ModuleEmissionCacheKey, ModuleGraphEmission } from "./emitter-module"
import {
  FRONTEND_SEMANTIC_ABI, FrontendCacheState, FrontendFileInput, FrontendModuleOutput, FrontendSourceProbe,
  parseFrontendCacheState, renderFrontendCacheState,
} from "./frontend-cache"
import { driverOutputPath, ensureOutputDirectory } from "./materialize-driver"
import { PackageManifest } from "./package-manifest"
import { parentPath } from "./project"
import { SourceLoader } from "./resolver"
import { SourceFile } from "./semantic"
import { configuredStdlibBundleFingerprint, reachedPackageManifestPaths } from "./source-loader-driver"
import { sha256HexString } from "std/crypto"
import { exists, isDirectory, readText, remove, rename, writeText } from "std/fs"

export function frontendCachePath(buildDirectory: string, kind: string): string {
  return driverOutputPath(driverOutputPath(buildDirectory, ".doof-cache/v1"), kind + ".json")
}

/** Unstamped source builds cannot claim a stable compiler cache identity. */
export function compilerCacheIdentity(): string {
  return versionCacheIdentity(compilerVersion, compilerVersionStamped)
}

export function frontendConfigurationFingerprint(
  entry: string,
  entryMode: string,
  target: string,
  manifest: PackageManifest,
  stdlibRoot: string,
  nativePlatform: string,
  stdlibTarget: string,
): string {
  compilerIdentity := compilerCacheIdentity()
  if compilerIdentity == "" { return "" }
  manifestSource := readTextOrEmpty(manifest.manifestPath)
  return sha256HexString(
    "doof-frontend-cache-4:" + string(FRONTEND_SEMANTIC_ABI) + "\n" + compilerIdentity + "\n" + entry + "\n" + entryMode + "\n" + target + "\n" +
      stdlibRoot + "\n" + nativePlatform + "\n" + stdlibTarget + "\n" +
      configuredStdlibBundleFingerprint() + "\n" + manifestSource,
  )
}

function readTextOrEmpty(path: string): string {
  source := readText(path) else { return "" }
  return source
}

export function readFrontendState(path: string): FrontendCacheState | none {
  if !exists(path) { return none }
  source := readText(path) else { return none }
  return parseFrontendCacheState(source)
}

export function frontendStateMatches(
  state: FrontendCacheState | none,
  configurationFingerprint: string,
  loader: SourceLoader,
): bool {
  if configurationFingerprint == "" || state == none || state!.configurationFingerprint != configurationFingerprint { return false }
  for input of state!.fileInputs {
    source := readText(input.path) else { return false }
    if sha256HexString(source) != input.sourceHash { return false }
  }
  for probe of state!.probes {
    // A missing source is none; a Failure is a load error.
    source := loader(probe.logicalPath) else error {
      if error != none || !probe.missing { return false }
      continue
    }
    if probe.missing || sha256HexString(source.source) != probe.sourceHash { return false }
  }
  return true
}

export function frontendStateForCompilation(
  result: Compilation,
  configurationFingerprint: string,
  rootManifest: PackageManifest,
): FrontendCacheState {
  state := FrontendCacheState { configurationFingerprint }
  for path of result.resolutionProbes {
    let matched: SourceFile | none = none
    for source of result.sourceFiles { if source.path == path { matched = source } }
    state.probes.push(FrontendSourceProbe {
      logicalPath: path,
      sourceHash: if matched == none then "" else sha256HexString(matched!.source),
      missing: matched == none,
    })
  }
  addFrontendFileInput(state.fileInputs, rootManifest.manifestPath)
  for manifestPath of reachedPackageManifestPaths() {
    addFrontendFileInput(state.fileInputs, manifestPath)
  }
  if result.emission != none {
    for module of result.emission!.modules {
      state.modules.push(FrontendModuleOutput {
        modulePath: module.modulePath, headerName: module.headerName, sourceName: module.sourceName,
        fingerprint: module.fingerprint,
      })
    }
  }
  return state
}

export function cachedModuleGraph(state: FrontendCacheState, outputDirectory: string): ModuleGraphEmission | none {
  if state.modules.length == 0 { return none }
  graph := ModuleGraphEmission {}
  for module of state.modules {
    if !exists(driverOutputPath(outputDirectory, module.headerName)) ||
      !exists(driverOutputPath(outputDirectory, module.sourceName)) { return none }
    graph.modules.push(ModuleEmission {
      modulePath: module.modulePath, headerName: module.headerName, sourceName: module.sourceName,
      header: "", source: "", reused: true, fingerprint: module.fingerprint,
    })
  }
  return graph
}

/** App bundles reuse ordinary generated modules; iOS keeps its distinct entry wrapper out of the cache for now. */
export function frontendEmissionCacheSupported(target: string): bool {
  return target != "wasm" && target != "ios-app"
}

export function reusableEmissionKeys(
  state: FrontendCacheState | none,
  outputDirectory: string,
): ModuleEmissionCacheKey[] {
  let keys: ModuleEmissionCacheKey[] = []
  if state == none { return keys }
  for module of state!.modules {
    if module.fingerprint == "" || !exists(driverOutputPath(outputDirectory, module.headerName)) ||
      !exists(driverOutputPath(outputDirectory, module.sourceName)) { continue }
    keys.push(ModuleEmissionCacheKey { modulePath: module.modulePath, fingerprint: module.fingerprint })
  }
  return keys
}

function addFrontendFileInput(inputs: FrontendFileInput[], path: string): none {
  for input of inputs { if input.path == path { return } }
  source := readText(path) else { return }
  inputs.push(FrontendFileInput { path, sourceHash: sha256HexString(source) })
}

export function writeFrontendState(path: string, state: FrontendCacheState): none {
  ensureOutputDirectory(parentPath(path))
  temporaryPath := path + ".tmp"
  writeText(temporaryPath, renderFrontendCacheState(state))!
  rename(temporaryPath, path)!
}

export function removeStaleFrontendOutputs(
  previous: FrontendCacheState | none,
  current: FrontendCacheState,
  outputDirectory: string,
): none {
  if previous == none { return }
  prefix := if outputDirectory.endsWith("/") then outputDirectory else outputDirectory + "/"
  for old of previous!.modules {
    let retained = false
    for module of current.modules {
      if module.modulePath == old.modulePath && module.headerName == old.headerName && module.sourceName == old.sourceName {
        retained = true
      }
    }
    if retained { continue }
    for name of [old.headerName, old.sourceName] {
      path := driverOutputPath(outputDirectory, name)
      if path.startsWith(prefix) && exists(path) && !isDirectory(path) { remove(path)! }
    }
  }
}
