// Native compiler argument planning for materialized Doof projects.
//
// Project emission keeps native paths output-relative. This module owns the
// single transition to concrete disk paths and compiler command arguments,
// leaving process execution at the driver boundary.

import { ModuleEmission } from "./emitter-module"
import { NativeBuildPlan } from "./package-manifest"
import { sha1HexString } from "std/crypto"

export enum NativeBuildMode {
  Debug,
  Release,
  Profile,
}

/** One independently executable object compilation task. */
export class NativeCompileTask {
  readonly id: string
  readonly compiler: string
  readonly sourcePath: string
  readonly outputPath: string
  readonly dependencyFilePath: string = ""
  readonly auxiliaryOutputPaths: readonly string[] = []
  readonly usesPrecompiledHeader: bool = false
  readonly arguments: string[] = []
}

/** Build-only generated input consumed by native compiler tasks. */
export class NativeBuildSupportFile {
  readonly outputPath: string
  readonly content: string
}

/** A complete native compiler invocation for one emitted executable. */
export class NativeCompilePlan {
  compiler: string
  linker: string
  supportFiles: NativeBuildSupportFile[] = []
  precompiledHeaderTask: NativeCompileTask | none = none
  compileTasks: NativeCompileTask[] = []
  linkArguments: string[] = []
  outputPath: string
}

/** Returns whether a compiler command selects the Microsoft C/C++ driver. */
export function isMsvcCompiler(compiler: string): bool {
  normalized := compiler.replaceAll("\\", "/").toLowerCase()
  let slash = -1
  for index of 0..<normalized.length { if normalized[index] == '/' { slash = index } }
  name := if slash < 0 then normalized else normalized.substring(slash + 1, normalized.length)
  return name == "cl" || name == "cl.exe"
}

/**
 * Plans independent GCC-compatible object compilations followed by one link.
 *
 * Source and output paths stay explicit so the native driver can fingerprint
 * and skip unchanged tasks without changing this pure build model.
 */
export function planNativeCompile(
  compiler: string,
  outputDirectory: string,
  outputPath: string,
  modules: ModuleEmission[],
  native: NativeBuildPlan,
  mode: NativeBuildMode = .Debug,
  platform: string = "",
  wasmExportNames: string[] = [],
  wasm: bool = false,
  wasmCommand: bool = false,
): NativeCompilePlan {
  if isMsvcCompiler(compiler) && !wasm {
    return planMsvcNativeCompile(compiler, outputDirectory, outputPath, modules, native, mode)
  }
  release := mode == .Release
  profile := mode == .Profile
  swiftLink := hasSwiftSource(native.sourceFiles)
  let compileArguments: string[] = ["-std=c++17"]
  // Release defaults precede manifest flags so packages can intentionally
  // override optimization while still receiving the NDEBUG contract.
  if release || profile {
    compileArguments.push("-O2")
    compileArguments.push("-DNDEBUG")
    // Keep generated and native functions independently discardable. Apple
    // and GNU-compatible linkers use different flags below, but both need
    // section granularity to reliably remove unreachable code and data.
    compileArguments.push("-ffunction-sections")
    compileArguments.push("-fdata-sections")
    // Full LTO is valuable for release builds, but a later dsymutil invocation
    // cannot recover line tables from the linker's deleted temporary LTO
    // object. Profile builds retain ordinary optimized objects instead.
    if release && !wasm && !swiftLink { compileArguments.push("-flto") }
  }
  if profile {
    compileArguments.push("-g")
    compileArguments.push("-fno-omit-frame-pointer")
  }
  if wasm {
    compileArguments.push("-Oz")
    compileArguments.push("-flto")
    if wasmCommand { compileArguments.push("-fwasm-exceptions") }
  }
  for define of native.defines { compileArguments.push("-D" + define) }
  compileArguments.push("-I")
  compileArguments.push(outputDirectory)
  for includePath of native.includePaths {
    compileArguments.push("-I")
    compileArguments.push(resolveBuildPath(outputDirectory, includePath))
  }
  for flag of native.compilerFlags { compileArguments.push(flag) }
  let precompiledHeaderTask: NativeCompileTask | none = none
  let clangPchPath = ""
  // The runtime dominates repeated parsing in larger generated projects. Build
  // it once, but avoid paying the PCH startup cost for a single module.
  if modules.length > 1 && !wasm {
    runtimeHeader := resolveBuildPath(outputDirectory, "doof_runtime.hpp")
    clangPch := usesClangPrecompiledHeader(compiler, platform)
    pchPath := runtimeHeader + if clangPch then ".pch" else ".gch"
    let pchArguments: string[] = []
    for argument of compileArguments { pchArguments.push(argument) }
    dependencyFile := pchPath + ".d"
    pchArguments.push("-MMD")
    pchArguments.push("-MF")
    pchArguments.push(dependencyFile)
    pchArguments.push("-x")
    pchArguments.push("c++-header")
    pchArguments.push(runtimeHeader)
    pchArguments.push("-o")
    pchArguments.push(pchPath)
    precompiledHeaderTask = NativeCompileTask {
      id: "pch:" + pchPath,
      compiler,
      sourcePath: runtimeHeader,
      outputPath: pchPath,
      dependencyFilePath: dependencyFile,
      arguments: pchArguments.drainToReadonly(),
    }
    if clangPch { clangPchPath = pchPath }
  }

  let compileTasks: NativeCompileTask[] = []
  let objectPaths: string[] = []
  for index of 0..<modules.length {
    sourcePath := resolveBuildPath(outputDirectory, modules[index].sourceName)
    objectPath := resolveBuildPath(outputDirectory, ".doof-objects/generated/" + replaceSourceExtension(modules[index].sourceName, ".o"))
    dependencyFile := objectPath + ".d"
    arguments := copyArguments(compileArguments)
    // A C++ PCH is valid for generated C++ translation units. Native sources
    // may be C or Objective-C++, whose compiler language mode is incompatible.
    if clangPchPath != "" {
      arguments.push("-include-pch")
      arguments.push(clangPchPath)
    }
    arguments.push("-MMD")
    arguments.push("-MF")
    arguments.push(dependencyFile)
    appendObjectArguments(arguments, sourcePath, objectPath)
    compileTasks.push(NativeCompileTask {
      id: "object:" + objectPath,
      compiler,
      sourcePath,
      outputPath: objectPath,
      dependencyFilePath: dependencyFile,
      usesPrecompiledHeader: precompiledHeaderTask != none,
      arguments: arguments.drainToReadonly(),
    })
    objectPaths.push(objectPath)
  }
  for index of 0..<native.sourceFiles.length {
    sourcePath := resolveBuildPath(outputDirectory, native.sourceFiles[index])
    swiftSource := isSwiftSource(sourcePath)
    objectPath := resolveBuildPath(outputDirectory, ".doof-objects/native/" + sha1HexString(native.sourceFiles[index]) + ".o")
    dependencyFile := if swiftSource then "" else objectPath + ".d"
    cSource := isCSource(sourcePath)
    arguments := if swiftSource then swiftObjectArguments(sourcePath, objectPath, mode) else copyNativeCompileArguments(compileArguments, cSource)
    if !swiftSource {
      arguments.push("-MMD")
      arguments.push("-MF")
      arguments.push(dependencyFile)
      appendObjectArguments(arguments, sourcePath, objectPath)
    }
    taskCompiler := if swiftSource then "swiftc" else if cSource then deriveCCompiler(compiler) else compiler
    compileTasks.push(NativeCompileTask {
      id: "object:" + objectPath,
      compiler: taskCompiler,
      sourcePath,
      outputPath: objectPath,
      dependencyFilePath: dependencyFile,
      arguments: arguments.drainToReadonly(),
    })
    objectPaths.push(objectPath)
  }

  let linkArguments: string[] = []
  for objectPath of objectPaths { linkArguments.push(objectPath) }
  for libraryPath of native.libraryPaths {
    linkArguments.push("-L" + resolveBuildPath(outputDirectory, libraryPath))
  }
  for library of native.linkLibraries { linkArguments.push("-l" + library) }
  for framework of native.frameworks {
    linkArguments.push("-framework")
    linkArguments.push(framework)
  }
  if swiftLink && platform == "macos" {
    linkArguments.push("-Xlinker")
    linkArguments.push("-lc++")
  }
  if (release || profile) && !wasm {
    if release && !swiftLink { linkArguments.push("-flto") }
    appendOptimizedLinkerArguments(linkArguments, platform, swiftLink, release)
  }
  if !wasm { for flag of native.linkerFlags { linkArguments.push(flag) } }
  if wasm {
    linkArguments.push("-Oz")
    linkArguments.push("-flto")
    linkArguments.push("--strip-debug")
    linkArguments.push("-sASSERTIONS=0")
    linkArguments.push("-sMALLOC=emmalloc")
    linkArguments.push("-sSTANDALONE_WASM=1")
    linkArguments.push("-sFILESYSTEM=0")
    if wasmCommand {
      linkArguments.push("-fwasm-exceptions")
    } else {
      linkArguments.push("--no-entry")
      linkArguments.push("-sEXPORTED_FUNCTIONS=" + wasmExportList(wasmExportNames))
    }
    for flag of native.linkerFlags { linkArguments.push(flag) }
  }
  linkArguments.push("-o")
  linkArguments.push(outputPath)
  return NativeCompilePlan {
    compiler,
    linker: if swiftLink then "swiftc" else compiler,
    precompiledHeaderTask,
    compileTasks,
    linkArguments,
    outputPath,
  }
}

/** Plans native Windows compilation using cl.exe and link.exe. */
function planMsvcNativeCompile(
  compiler: string,
  outputDirectory: string,
  outputPath: string,
  modules: ModuleEmission[],
  native: NativeBuildPlan,
  mode: NativeBuildMode,
): NativeCompilePlan {
  release := mode == .Release
  profile := mode == .Profile
  let compileArguments: string[] = [
    "/nologo", "/std:c++17", "/EHsc", "/utf-8", "/Zc:__cplusplus", "/permissive-",
  ]
  if release || profile {
    compileArguments.push("/O2")
    compileArguments.push("/DNDEBUG")
    compileArguments.push("/Gy")
    compileArguments.push("/Gw")
    compileArguments.push("/GL")
  }
  if profile {
    compileArguments.push("/Zi")
    compileArguments.push("/Oy-")
  }
  for define of native.defines { compileArguments.push("/D" + define) }
  compileArguments.push("/I")
  compileArguments.push(outputDirectory)
  for includePath of native.includePaths {
    compileArguments.push("/I")
    compileArguments.push(resolveBuildPath(outputDirectory, includePath))
  }
  for flag of native.compilerFlags { compileArguments.push(flag) }

  let supportFiles: NativeBuildSupportFile[] = []
  let precompiledHeaderTask: NativeCompileTask | none = none
  let pchHeaderName = ""
  let pchPath = ""
  let pchObjectPath = ""
  if modules.length > 1 {
    pchHeaderName = "doof_msvc_pch.hpp"
    pchHeaderPath := resolveBuildPath(outputDirectory, pchHeaderName)
    pchSourcePath := resolveBuildPath(outputDirectory, "doof_msvc_pch.cpp")
    pchPath = resolveBuildPath(outputDirectory, ".doof-objects/pch/doof_msvc.pch")
    pchObjectPath = resolveBuildPath(outputDirectory, ".doof-objects/pch/doof_msvc_pch.obj")
    pchDependencyPath := pchPath + ".json"
    supportFiles.push(NativeBuildSupportFile { outputPath: pchHeaderPath, content: msvcPchHeaderSource() })
    supportFiles.push(NativeBuildSupportFile { outputPath: pchSourcePath, content: "#include \"" + pchHeaderName + "\"\n" })
    pchArguments := copyArguments(compileArguments)
    pchArguments.push("/TP")
    pchArguments.push("/Yc" + pchHeaderName)
    pchArguments.push("/Fp" + pchPath)
    pchArguments.push("/sourceDependencies")
    pchArguments.push(pchDependencyPath)
    pchArguments.push("/c")
    pchArguments.push(pchSourcePath)
    pchArguments.push("/Fo" + pchObjectPath)
    precompiledHeaderTask = NativeCompileTask {
      id: "pch:" + pchPath,
      compiler,
      sourcePath: pchSourcePath,
      outputPath: pchPath,
      dependencyFilePath: pchDependencyPath,
      auxiliaryOutputPaths: [pchObjectPath],
      arguments: pchArguments.drainToReadonly(),
    }
  }

  let compileTasks: NativeCompileTask[] = []
  let objectPaths: string[] = []
  if pchObjectPath != "" { objectPaths.push(pchObjectPath) }
  for module of modules {
    sourcePath := resolveBuildPath(outputDirectory, module.sourceName)
    objectPath := resolveBuildPath(outputDirectory, ".doof-objects/generated/" + replaceSourceExtension(module.sourceName, ".obj"))
    dependencyFile := objectPath + ".json"
    arguments := copyArguments(compileArguments)
    if precompiledHeaderTask != none {
      arguments.push("/FI" + pchHeaderName)
      arguments.push("/Yu" + pchHeaderName)
      arguments.push("/Fp" + pchPath)
    }
    appendMsvcObjectArguments(arguments, sourcePath, objectPath, dependencyFile, false)
    compileTasks.push(NativeCompileTask {
      id: "object:" + objectPath,
      compiler,
      sourcePath,
      outputPath: objectPath,
      dependencyFilePath: dependencyFile,
      usesPrecompiledHeader: precompiledHeaderTask != none,
      arguments: arguments.drainToReadonly(),
    })
    objectPaths.push(objectPath)
  }
  for sourceFile of native.sourceFiles {
    sourcePath := resolveBuildPath(outputDirectory, sourceFile)
    objectPath := resolveBuildPath(outputDirectory, ".doof-objects/native/" + sha1HexString(sourceFile) + ".obj")
    dependencyFile := objectPath + ".json"
    arguments := copyArguments(compileArguments)
    appendMsvcObjectArguments(arguments, sourcePath, objectPath, dependencyFile, isCSource(sourcePath))
    compileTasks.push(NativeCompileTask {
      id: "object:" + objectPath,
      compiler,
      sourcePath,
      outputPath: objectPath,
      dependencyFilePath: dependencyFile,
      arguments: arguments.drainToReadonly(),
    })
    objectPaths.push(objectPath)
  }

  let linkArguments: string[] = ["/nologo"]
  for objectPath of objectPaths { linkArguments.push(objectPath) }
  for libraryPath of native.libraryPaths {
    linkArguments.push("/LIBPATH:" + resolveBuildPath(outputDirectory, libraryPath))
  }
  for library of native.linkLibraries {
    linkArguments.push(if library.toLowerCase().endsWith(".lib") then library else library + ".lib")
  }
  if release || profile {
    linkArguments.push("/LTCG")
    linkArguments.push("/OPT:REF")
    linkArguments.push("/OPT:ICF")
  }
  if profile { linkArguments.push("/DEBUG") }
  for flag of native.linkerFlags { linkArguments.push(flag) }
  linkArguments.push("/OUT:" + outputPath)
  return NativeCompilePlan {
    compiler,
    linker: "link.exe",
    supportFiles,
    precompiledHeaderTask,
    compileTasks,
    linkArguments,
    outputPath,
  }
}

/** Stable MSVC-only umbrella captured before generated module compilation. */
export function msvcPchHeaderSource(): string {
  return "#pragma once\n" +
    "#include \"doof_runtime.hpp\"\n" +
    "#if defined(_WIN32)\n" +
    "#ifndef WIN32_LEAN_AND_MEAN\n#define WIN32_LEAN_AND_MEAN\n#endif\n" +
    "#ifndef NOMINMAX\n#define NOMINMAX\n#endif\n" +
    "#include <windows.h>\n" +
    "#ifdef small\n#undef small\n#endif\n" +
    "#endif\n"
}

function appendMsvcObjectArguments(
  arguments: string[],
  sourcePath: string,
  outputPath: string,
  dependencyFilePath: string,
  cSource: bool,
): none {
  arguments.push(if cSource then "/TC" else "/TP")
  arguments.push("/sourceDependencies")
  arguments.push(dependencyFilePath)
  arguments.push("/c")
  arguments.push(sourcePath)
  arguments.push("/Fo" + outputPath)
}

/** Adds optimized dead-code elimination and optional release symbol stripping. */
function appendOptimizedLinkerArguments(arguments: string[], platform: string, swiftLink: bool, stripSymbols: bool): none {
  if platform == "macos" || platform.startsWith("ios-") {
    appendLinkerOption(arguments, "-dead_strip", swiftLink)
    if stripSymbols {
      appendLinkerOption(arguments, "-S", swiftLink)
      appendLinkerOption(arguments, "-x", swiftLink)
    }
    return
  }
  appendLinkerOption(arguments, "--gc-sections", swiftLink)
  if stripSymbols { appendLinkerOption(arguments, "--strip-all", swiftLink) }
}

function appendLinkerOption(arguments: string[], option: string, swiftLink: bool): none {
  if swiftLink {
    arguments.push("-Xlinker")
    arguments.push(option)
  } else {
    arguments.push("-Wl," + option)
  }
}

function replaceSourceExtension(path: string, extension: string): string {
  if path.endsWith(".cpp") { return path.substring(0, path.length - 4) + extension }
  return path + extension
}

function copyArguments(source: string[]): string[] {
  let result: string[] = []
  for argument of source { result.push(argument) }
  return result
}

function copyNativeCompileArguments(source: string[], cSource: bool): string[] {
  let result: string[] = []
  for argument of source {
    if !cSource || argument != "-std=c++17" { result.push(argument) }
  }
  return result
}

function isCSource(path: string): bool {
  return path.toLowerCase().endsWith(".c")
}

function isSwiftSource(path: string): bool {
  return path.toLowerCase().endsWith(".swift")
}

function hasSwiftSource(paths: string[]): bool {
  for path of paths { if isSwiftSource(path) { return true } }
  return false
}

function swiftObjectArguments(sourcePath: string, objectPath: string, mode: NativeBuildMode): string[] {
  let arguments = ["-parse-as-library", "-emit-object"]
  if mode == .Release || mode == .Profile { arguments.push("-O") }
  if mode == .Profile { arguments.push("-g") }
  arguments.push(sourcePath)
  arguments.push("-o")
  arguments.push(objectPath)
  return arguments
}

/** Selects the C driver adjacent to the configured GCC-compatible C++ driver. */
function deriveCCompiler(compiler: string): string {
  if compiler == "em++" || compiler.endsWith("/em++") {
    return compiler.substring(0, compiler.length - 4) + "emcc"
  }
  if compiler == "g++" || compiler.endsWith("/g++") {
    return compiler.substring(0, compiler.length - 3) + "gcc"
  }
  if compiler == "c++" || compiler.endsWith("/c++") {
    return compiler.substring(0, compiler.length - 3) + "cc"
  }
  if compiler.endsWith("++") {
    return compiler.substring(0, compiler.length - 2)
  }
  return compiler
}

function wasmExportList(names: string[]): string {
  let result = "[\"_malloc\",\"_free\",\"_doof_free\""
  for name of names { result = result + ",\"_" + name + "\"" }
  return result + "]"
}

function appendObjectArguments(arguments: string[], sourcePath: string, outputPath: string): none {
  arguments.push("-c")
  arguments.push(sourcePath)
  arguments.push("-o")
  arguments.push(outputPath)
}

function usesClangPrecompiledHeader(compiler: string, platform: string): bool {
  name := compiler.toLowerCase()
  if name.contains("clang") { return true }
  if name.contains("g++") || name.contains("gcc") { return false }
  // The default c++ driver is Clang on Apple hosts and conventionally GCC on
  // other supported hosts. Explicit compiler names take precedence above.
  return platform == "macos"
}

function resolveBuildPath(outputDirectory: string, path: string): string {
  if path.startsWith("/") { return path }
  if outputDirectory.endsWith("/") { return outputDirectory + path }
  return outputDirectory + "/" + path
}
