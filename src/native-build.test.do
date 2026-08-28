import { Assert } from "std/assert"

import { ModuleEmission } from "./emitter-module"
import { NativeBuildMode, NativeCompileTask, NativeCompileTaskBatch, batchNativeCompileTasks, isMsvcCompiler, msvcPchHeaderSource, planNativeCompile } from "./native-build"
import { NativeBuildPlan } from "./package-manifest"

export function testPlansGeneratedAndManifestNativeSources(): none {
  plan := planNativeCompile(
    "clang++",
    "/tmp/generated",
    "/tmp/generated/demo",
    [ModuleEmission {
      modulePath: "/main.do",
      header: "",
      source: "",
      headerName: "main.hpp",
      sourceName: "main.cpp",
    }],
    NativeBuildPlan {
      includePaths: ["include", "std/time"],
      sourceFiles: ["native/root.cpp", "std/time/doof_time.cpp"],
      libraryPaths: ["vendor/lib"],
      linkLibraries: ["sqlite3"],
      frameworks: ["CoreFoundation"],
      defines: ["ROOT_NATIVE=11"],
      compilerFlags: ["-Wconversion"],
      linkerFlags: ["-pthread"],
    },
  )

  Assert.equal(plan.compiler, "clang++")
  Assert.equal(plan.outputPath, "/tmp/generated/demo")
  Assert.equal(plan.compileTasks.length, 3)
  let expectedCompilePrefix: string[] = [
    "-std=c++17",
    "-DROOT_NATIVE=11",
    "-I", "/tmp/generated",
    "-I", "/tmp/generated/include",
    "-I", "/tmp/generated/std/time",
    "-Wconversion",
  ]
  for task of plan.compileTasks {
    for index of 0..<expectedCompilePrefix.length {
      Assert.equal(task.arguments[index], expectedCompilePrefix[index])
    }
    Assert.equal(task.arguments.contains("-c"), true)
    Assert.equal(task.arguments.contains(task.sourcePath), true)
    Assert.equal(task.arguments.contains(task.outputPath), true)
  }
  Assert.equal(plan.linkArguments.length, 10)
  Assert.equal(plan.linkArguments[0], "/tmp/generated/.doof-objects/generated/main.o")
  Assert.equal(plan.linkArguments[1].startsWith("/tmp/generated/.doof-objects/native/"), true)
  Assert.equal(plan.linkArguments[2].startsWith("/tmp/generated/.doof-objects/native/"), true)
  Assert.equal(plan.linkArguments[3], "-L/tmp/generated/vendor/lib")
  Assert.equal(plan.linkArguments[9], "/tmp/generated/demo")
  Assert.equal(plan.precompiledHeaderTask, none)
}

export function testPreservesAbsoluteNativePaths(): none {
  plan := planNativeCompile(
    "c++",
    "/tmp/generated",
    "/tmp/generated/demo",
    [],
    NativeBuildPlan { sourceFiles: ["/opt/native.cpp"], includePaths: ["/opt/include"] },
  )
  Assert.equal(plan.compileTasks[0].sourcePath, "/opt/native.cpp")
  Assert.equal(plan.compileTasks[0].arguments.contains("/opt/include"), true)
}

export function testCompilesNativeCSourcesWithAdjacentCDriver(): none {
  clangPlan := planNativeCompile(
    "/opt/llvm/bin/clang++",
    "/tmp/generated",
    "/tmp/generated/demo",
    [ModuleEmission {
      modulePath: "/main.do",
      header: "",
      source: "",
      headerName: "main.hpp",
      sourceName: "main.cpp",
    }],
    NativeBuildPlan { sourceFiles: ["vendor/zstd/debug.c", "native/bridge.cpp"] },
  )

  Assert.equal(clangPlan.compileTasks[0].compiler, "/opt/llvm/bin/clang++")
  Assert.equal(clangPlan.compileTasks[1].compiler, "/opt/llvm/bin/clang")
  Assert.equal(clangPlan.compileTasks[1].arguments.contains("-std=c++17"), false)
  Assert.equal(clangPlan.compileTasks[2].compiler, "/opt/llvm/bin/clang++")
  Assert.equal(clangPlan.compileTasks[2].arguments.contains("-std=c++17"), true)

  gccPlan := planNativeCompile(
    "g++",
    "/tmp/generated",
    "/tmp/generated/demo",
    [],
    NativeBuildPlan { sourceFiles: ["native.c"] },
  )
  Assert.equal(gccPlan.compileTasks[0].compiler, "gcc")

  defaultPlan := planNativeCompile(
    "c++",
    "/tmp/generated",
    "/tmp/generated/demo",
    [],
    NativeBuildPlan { sourceFiles: ["native.c"] },
  )
  Assert.equal(defaultPlan.compileTasks[0].compiler, "cc")
}

export function testCompilesSwiftSourcesAndLinksWithSwiftRuntime(): none {
  plan := planNativeCompile(
    "clang++",
    "/tmp/generated",
    "/tmp/generated/demo",
    [ModuleEmission {
      modulePath: "/main.do",
      header: "",
      source: "",
      headerName: "main.hpp",
      sourceName: "main.cpp",
    }],
    NativeBuildPlan {
      sourceFiles: ["std/apple-intelligence/apple_intelligence_impl.swift"],
      frameworks: ["Foundation", "FoundationModels"],
      linkerFlags: ["-Wl,-rpath,/tmp/lib"],
    },
    .Debug,
    "macos",
  )

  Assert.equal(plan.compiler, "clang++")
  Assert.equal(plan.linker, "swiftc")
  Assert.equal(plan.compileTasks.length, 2)
  swiftTask: NativeCompileTask := plan.compileTasks[1]
  Assert.equal(swiftTask.compiler, "swiftc")
  Assert.equal(swiftTask.sourcePath, "/tmp/generated/std/apple-intelligence/apple_intelligence_impl.swift")
  Assert.equal(swiftTask.arguments[0], "-parse-as-library")
  Assert.equal(swiftTask.arguments[1], "-emit-object")
  Assert.equal(swiftTask.arguments.contains("-std=c++17"), false)
  Assert.equal(plan.linkArguments.contains("-framework"), true)
  Assert.equal(plan.linkArguments.contains("FoundationModels"), true)
  Assert.equal(plan.linkArguments.contains("-Xlinker"), true)
  Assert.equal(plan.linkArguments.contains("-lc++"), true)
  Assert.equal(plan.linkArguments.contains("-Wl,-rpath,/tmp/lib"), true)
}

export function testAddsReleaseDefaultsBeforeManifestFlags(): none {
  plan := planNativeCompile(
    "clang++",
    "/tmp/generated",
    "/tmp/dist/demo",
    [ModuleEmission {
      modulePath: "/main.do",
      header: "",
      source: "",
      headerName: "main.hpp",
      sourceName: "main.cpp",
    }],
    NativeBuildPlan {
      defines: ["APP_RELEASE=1"],
      compilerFlags: ["-O3"],
    },
    .Release,
    "macos",
  )
  Assert.equal(plan.compileTasks[0].arguments[0], "-std=c++17")
  Assert.equal(plan.compileTasks[0].arguments[1], "-O2")
  Assert.equal(plan.compileTasks[0].arguments[2], "-DNDEBUG")
  Assert.equal(plan.compileTasks[0].arguments[3], "-ffunction-sections")
  Assert.equal(plan.compileTasks[0].arguments[4], "-fdata-sections")
  Assert.equal(plan.compileTasks[0].arguments[5], "-flto")
  Assert.equal(plan.compileTasks[0].arguments[6], "-DAPP_RELEASE=1")
  Assert.equal(plan.compileTasks[0].arguments.contains("-O3"), true)
  Assert.equal(plan.linkArguments.contains("-flto"), true)
  Assert.equal(plan.linkArguments.contains("-Wl,-dead_strip"), true)
  Assert.equal(plan.linkArguments.contains("-Wl,-S"), true)
  Assert.equal(plan.linkArguments.contains("-Wl,-x"), true)
  Assert.equal(plan.outputPath, "/tmp/dist/demo")
}

export function testAddsElfReleaseLinkerDefaultsOnlyForReleaseBuilds(): none {
  release := planNativeCompile(
    "g++", "/tmp/generated", "/tmp/dist/demo", [],
    NativeBuildPlan { linkerFlags: ["-pthread"] }, .Release, "linux",
  )
  Assert.equal(release.linkArguments.contains("-Wl,--gc-sections"), true)
  Assert.equal(release.linkArguments.contains("-Wl,--strip-all"), true)
  Assert.equal(release.linkArguments.indexOf("-Wl,--strip-all") < release.linkArguments.indexOf("-pthread"), true)

  debug := planNativeCompile("g++", "/tmp/generated", "/tmp/generated/demo", [], NativeBuildPlan {}, .Debug, "linux")
  Assert.equal(debug.linkArguments.contains("-Wl,--gc-sections"), false)
  Assert.equal(debug.linkArguments.contains("-Wl,--strip-all"), false)
}

export function testAddsOptimizedObservableProfileDefaultsWithoutStripping(): none {
  plan := planNativeCompile(
    "clang++", "/tmp/generated", "/tmp/generated/demo", [], NativeBuildPlan {}, .Profile, "macos",
  )
  Assert.equal(plan.linkArguments.contains("-flto"), false)
  Assert.equal(plan.linkArguments.contains("-Wl,-dead_strip"), true)
  Assert.equal(plan.linkArguments.contains("-Wl,-S"), false)
  Assert.equal(plan.linkArguments.contains("-Wl,-x"), false)
  // With no source modules there are no compile tasks, so use the PCH-free
  // Swift path below to verify profile-specific source flags separately.
  swift := planNativeCompile(
    "clang++", "/tmp/generated", "/tmp/generated/swift-demo", [],
    NativeBuildPlan { sourceFiles: ["native/bridge.swift"] }, .Profile, "macos",
  )
  Assert.equal(swift.compileTasks[0].arguments.contains("-O"), true)
  Assert.equal(swift.compileTasks[0].arguments.contains("-g"), true)
}

export function testAddsCppProfileDebugInformationAndFramePointers(): none {
  plan := planNativeCompile(
    "clang++", "/tmp/generated", "/tmp/generated/demo",
    [ModuleEmission { modulePath: "/main.do", header: "", source: "", headerName: "main.hpp", sourceName: "main.cpp" }],
    NativeBuildPlan {}, .Profile, "macos",
  )
  Assert.equal(plan.compileTasks[0].arguments.contains("-O2"), true)
  Assert.equal(plan.compileTasks[0].arguments.contains("-DNDEBUG"), true)
  Assert.equal(plan.compileTasks[0].arguments.contains("-g"), true)
  Assert.equal(plan.compileTasks[0].arguments.contains("-fno-omit-frame-pointer"), true)
  Assert.equal(plan.compileTasks[0].arguments.contains("-flto"), false)
}

export function testUsesSwiftLinkerSpellingForAppleReleaseDefaults(): none {
  plan := planNativeCompile(
    "clang++", "/tmp/generated", "/tmp/dist/demo", [],
    NativeBuildPlan { sourceFiles: ["native/bridge.swift"] }, .Release, "macos",
  )
  Assert.equal(plan.linker, "swiftc")
  Assert.equal(plan.compileTasks[0].arguments.contains("-flto"), false)
  Assert.equal(plan.linkArguments.contains("-flto"), false)
  Assert.equal(plan.linkArguments.contains("-Wl,-dead_strip"), false)
  Assert.equal(plan.linkArguments.contains("-dead_strip"), true)
  Assert.equal(plan.linkArguments.contains("-S"), true)
  Assert.equal(plan.linkArguments.contains("-x"), true)
}

export function testPlansClangPrecompiledRuntimeForMultiModuleBuilds(): none {
  modules := [
    ModuleEmission { modulePath: "/one.do", header: "", source: "", headerName: "one.hpp", sourceName: "one.cpp" },
    ModuleEmission { modulePath: "/two.do", header: "", source: "", headerName: "two.hpp", sourceName: "two.cpp" },
  ]
  plan := planNativeCompile(
    "c++",
    "/tmp/generated",
    "/tmp/generated/demo",
    modules,
    NativeBuildPlan { defines: ["DEBUG_BUILD=1"], compilerFlags: ["-Wconversion"] },
    .Debug,
    "macos",
  )

  Assert.equal(plan.precompiledHeaderTask != none, true)
  Assert.equal(plan.precompiledHeaderTask!.arguments.contains("c++-header"), true)
  Assert.equal(plan.precompiledHeaderTask!.arguments.contains("/tmp/generated/doof_runtime.hpp"), true)
  Assert.equal(plan.precompiledHeaderTask!.arguments.contains("/tmp/generated/doof_runtime.hpp.pch"), true)
  Assert.equal(plan.precompiledHeaderTask!.arguments.contains("-DDEBUG_BUILD=1"), true)
  Assert.equal(plan.precompiledHeaderTask!.arguments.contains("-Wconversion"), true)
  Assert.equal(plan.compileTasks[0].arguments.contains("-include-pch"), true)
  Assert.equal(plan.compileTasks[0].arguments.contains("/tmp/generated/doof_runtime.hpp.pch"), true)
  Assert.equal(plan.compileTasks[1].arguments.contains("-include-pch"), true)
}

export function testDoesNotApplyCxxPrecompiledHeaderToObjectiveCxxSources(): none {
  modules := [
    ModuleEmission { modulePath: "/one.do", header: "", source: "", headerName: "one.hpp", sourceName: "one.cpp" },
    ModuleEmission { modulePath: "/two.do", header: "", source: "", headerName: "two.hpp", sourceName: "two.cpp" },
  ]
  plan := planNativeCompile(
    "clang++",
    "/tmp/generated",
    "/tmp/generated/demo",
    modules,
    NativeBuildPlan { sourceFiles: ["std/http/native_http_client_apple.mm"] },
    .Debug,
    "macos",
  )

  objectiveCxxTask: NativeCompileTask := plan.compileTasks[2]
  Assert.equal(objectiveCxxTask.sourcePath, "/tmp/generated/std/http/native_http_client_apple.mm")
  Assert.equal(objectiveCxxTask.arguments.contains("-include-pch"), false)
  Assert.equal(objectiveCxxTask.arguments.contains("/tmp/generated/doof_runtime.hpp.pch"), false)
}

export function testBatchesCompileTasksAcrossAtMostFourWorkers(): none {
  let tasks: NativeCompileTask[] = []
  for index of 0..<19 {
    tasks.push(NativeCompileTask {
      id: "source-" + string(index),
      compiler: "clang++",
      sourcePath: "/tmp/source-" + string(index) + ".cpp",
      outputPath: "/tmp/source-" + string(index) + ".o",
    })
  }

  batches := batchNativeCompileTasks(tasks)
  readonly frozenBatches: readonly NativeCompileTaskBatch[] = batches
  Assert.equal(batches.length, 4)
  Assert.equal(batches[0].length, 5)
  Assert.equal(batches[1].length, 5)
  Assert.equal(batches[2].length, 5)
  Assert.equal(batches[3].length, 4)
  let assigned = 0
  for batch of batches { assigned = assigned + batch.length }
  Assert.equal(assigned, 19)

  small := batchNativeCompileTasks([tasks[0], tasks[1], tasks[2]])
  Assert.equal(small.length, 3)
  Assert.equal(batchNativeCompileTasks([]).length, 0)
}

export function testUsesStableObjectPathsAndDependencyFiles(): none {
  first := ModuleEmission { modulePath: "/one.do", header: "", source: "", headerName: "one.hpp", sourceName: "one.cpp" }
  second := ModuleEmission { modulePath: "/two.do", header: "", source: "", headerName: "two.hpp", sourceName: "two.cpp" }
  forward := planNativeCompile("clang++", "/tmp/generated", "/tmp/generated/demo", [first, second], NativeBuildPlan {}, .Debug, "macos")
  reverse := planNativeCompile("clang++", "/tmp/generated", "/tmp/generated/demo", [second, first], NativeBuildPlan {}, .Debug, "macos")

  Assert.equal(forward.compileTasks[0].outputPath, reverse.compileTasks[1].outputPath)
  Assert.equal(forward.compileTasks[1].outputPath, reverse.compileTasks[0].outputPath)
  Assert.equal(forward.compileTasks[0].outputPath, "/tmp/generated/.doof-objects/generated/one.o")
  Assert.equal(forward.compileTasks[0].dependencyFilePath.endsWith("one.o.d"), true)
  Assert.equal(forward.compileTasks[0].arguments.contains("-MMD"), true)
  Assert.equal(forward.compileTasks[0].arguments.contains("-MF"), true)
  Assert.equal(forward.compileTasks[0].usesPrecompiledHeader, true)
}

export function testPlansGccAdjacentPrecompiledRuntime(): none {
  modules := [
    ModuleEmission { modulePath: "/one.do", header: "", source: "", headerName: "one.hpp", sourceName: "one.cpp" },
    ModuleEmission { modulePath: "/two.do", header: "", source: "", headerName: "two.hpp", sourceName: "two.cpp" },
  ]
  plan := planNativeCompile(
    "g++",
    "/tmp/generated",
    "/tmp/generated/demo",
    modules,
    NativeBuildPlan {},
  )

  Assert.equal(plan.precompiledHeaderTask!.arguments.contains("/tmp/generated/doof_runtime.hpp.gch"), true)
  Assert.equal(plan.compileTasks[0].arguments.contains("-include-pch"), false)
}

export function testPlansStandaloneEmscriptenWasmLink(): none {
  plan := planNativeCompile(
    "em++",
    "/tmp/generated",
    "/tmp/generated/demo.wasm",
    [ModuleEmission { modulePath: "/main.do", header: "", source: "", headerName: "main.hpp", sourceName: "main.cpp" }],
    NativeBuildPlan { sourceFiles: ["doof_wasm.cpp"], linkerFlags: ["-sINITIAL_MEMORY=33554432"] },
    .Debug,
    "linux",
    ["doof_initialize", "doof_export_add"],
    true,
  )

  Assert.equal(plan.precompiledHeaderTask, none)
  Assert.equal(plan.compileTasks[0].arguments.contains("-Oz"), true)
  Assert.equal(plan.compileTasks[0].arguments.contains("-flto"), true)
  Assert.equal(plan.linkArguments.contains("-sSTANDALONE_WASM=1"), true)
  Assert.equal(plan.linkArguments.contains("--no-entry"), true)
  Assert.equal(plan.linkArguments.contains("-sEXPORTED_FUNCTIONS=[\"_malloc\",\"_free\",\"_doof_free\",\"_doof_initialize\",\"_doof_export_add\"]"), true)
  Assert.equal(plan.linkArguments.contains("-sINITIAL_MEMORY=33554432"), true)
}

export function testPlansStandaloneEmscriptenWasmCommand(): none {
  plan := planNativeCompile(
    "em++",
    "/tmp/generated",
    "/tmp/generated/doof-tests.wasm",
    [ModuleEmission { modulePath: "/tests.do", header: "", source: "", headerName: "tests.hpp", sourceName: "tests.cpp" }],
    NativeBuildPlan {},
    .Debug,
    "macos",
    [],
    true,
    true,
  )

  Assert.equal(plan.compileTasks[0].arguments.contains("-fwasm-exceptions"), true)
  Assert.equal(plan.linkArguments.contains("-fwasm-exceptions"), true)
  Assert.equal(plan.linkArguments.contains("-sSTANDALONE_WASM=1"), true)
  Assert.equal(plan.linkArguments.contains("--no-entry"), false)
  Assert.equal(plan.linkArguments.contains("-sEXPORTED_FUNCTIONS=[]"), false)
}

export function testPlansMsvcCompilationAndLinking(): none {
  Assert.equal(isMsvcCompiler("cl.exe"), true)
  Assert.equal(isMsvcCompiler("C:\\VS\\bin\\cl.exe"), true)
  Assert.equal(isMsvcCompiler("clang++"), false)

  plan := planNativeCompile(
    "cl.exe",
    "C:/generated",
    "C:/generated/demo.exe",
    [ModuleEmission {
      modulePath: "/main.do",
      header: "",
      source: "",
      headerName: "main.hpp",
      sourceName: "main.cpp",
    }],
    NativeBuildPlan {
      sourceFiles: ["native/bridge.c", "native/helper.cpp"],
      includePaths: ["include"],
      libraryPaths: ["vendor/lib"],
      linkLibraries: ["winhttp", "custom.lib"],
      defines: ["WINDOWS_BUILD=1"],
      compilerFlags: ["/W4"],
      linkerFlags: ["/INCREMENTAL:NO"],
    },
    .Release,
    "windows",
  )

  Assert.equal(plan.compiler, "cl.exe")
  Assert.equal(plan.linker, "link.exe")
  Assert.equal(plan.precompiledHeaderTask, none)
  Assert.equal(plan.compileTasks.length, 3)
  generated := plan.compileTasks[0]
  Assert.equal(generated.outputPath, "C:/generated/.doof-objects/generated/main.obj")
  Assert.equal(generated.dependencyFilePath, generated.outputPath + ".json")
  Assert.equal(generated.arguments.contains("/TP"), true)
  Assert.equal(generated.arguments.contains("/sourceDependencies"), true)
  Assert.equal(generated.arguments.contains("/Fo" + generated.outputPath), true)
  Assert.equal(generated.arguments.contains("/GL"), true)
  Assert.equal(generated.arguments.contains("/DWINDOWS_BUILD=1"), true)
  Assert.equal(generated.arguments.contains("/W4"), true)
  Assert.equal(plan.compileTasks[1].arguments.contains("/TC"), true)
  Assert.equal(plan.compileTasks[2].arguments.contains("/TP"), true)
  Assert.equal(plan.linkArguments.contains("/LIBPATH:C:/generated/vendor/lib"), true)
  Assert.equal(plan.linkArguments.contains("winhttp.lib"), true)
  Assert.equal(plan.linkArguments.contains("custom.lib"), true)
  Assert.equal(plan.linkArguments.contains("/LTCG"), true)
  Assert.equal(plan.linkArguments.contains("/OPT:REF"), true)
  Assert.equal(plan.linkArguments.contains("/OPT:ICF"), true)
  Assert.equal(plan.linkArguments.contains("/INCREMENTAL:NO"), true)
  Assert.equal(plan.linkArguments[plan.linkArguments.length - 1], "/OUT:C:/generated/demo.exe")
}

export function testPlansMsvcPrecompiledRuntimeAndWindowsHeadersForGeneratedModules(): none {
  modules := [
    ModuleEmission { modulePath: "/one.do", header: "", source: "", headerName: "one.hpp", sourceName: "one.cpp" },
    ModuleEmission { modulePath: "/two.do", header: "", source: "", headerName: "two.hpp", sourceName: "two.cpp" },
  ]
  plan := planNativeCompile(
    "cl.exe",
    "C:/generated",
    "C:/generated/demo.exe",
    modules,
    NativeBuildPlan {
      sourceFiles: ["native/bridge.c", "native/helper.cpp"],
      defines: ["WINDOWS_BUILD=1"],
      compilerFlags: ["/W4"],
    },
    .Debug,
    "windows",
  )

  Assert.equal(plan.supportFiles.length, 2)
  Assert.equal(plan.supportFiles[0].outputPath, "C:/generated/doof_msvc_pch.hpp")
  Assert.equal(plan.supportFiles[0].content, msvcPchHeaderSource())
  Assert.equal(plan.supportFiles[0].content.contains("#include \"doof_runtime.hpp\""), true)
  Assert.equal(plan.supportFiles[0].content.contains("#define WIN32_LEAN_AND_MEAN"), true)
  Assert.equal(plan.supportFiles[0].content.contains("#define NOMINMAX"), true)
  Assert.equal(plan.supportFiles[0].content.contains("#include <windows.h>"), true)
  Assert.equal(plan.supportFiles[0].content.contains("#undef small"), true)
  Assert.equal(plan.supportFiles[1].content, "#include \"doof_msvc_pch.hpp\"\n")

  pch := plan.precompiledHeaderTask!
  Assert.equal(pch.outputPath, "C:/generated/.doof-objects/pch/doof_msvc.pch")
  Assert.equal(pch.dependencyFilePath, pch.outputPath + ".json")
  Assert.equal(pch.auxiliaryOutputPaths.length, 1)
  Assert.equal(pch.auxiliaryOutputPaths[0], "C:/generated/.doof-objects/pch/doof_msvc_pch.obj")
  Assert.equal(pch.arguments.contains("/Ycdoof_msvc_pch.hpp"), true)
  Assert.equal(pch.arguments.contains("/Fp" + pch.outputPath), true)
  Assert.equal(pch.arguments.contains("/DWINDOWS_BUILD=1"), true)
  Assert.equal(pch.arguments.contains("/W4"), true)
  Assert.equal(plan.linkArguments.contains(pch.auxiliaryOutputPaths[0]), true)

  for index of 0..<2 {
    generated := plan.compileTasks[index]
    Assert.equal(generated.usesPrecompiledHeader, true)
    Assert.equal(generated.arguments.contains("/FIdoof_msvc_pch.hpp"), true)
    Assert.equal(generated.arguments.contains("/Yudoof_msvc_pch.hpp"), true)
    Assert.equal(generated.arguments.contains("/Fp" + pch.outputPath), true)
  }
  for index of 2..<plan.compileTasks.length {
    native := plan.compileTasks[index]
    Assert.equal(native.usesPrecompiledHeader, false)
    Assert.equal(native.arguments.contains("/Yudoof_msvc_pch.hpp"), false)
    Assert.equal(native.arguments.contains("/FIdoof_msvc_pch.hpp"), false)
  }
}
