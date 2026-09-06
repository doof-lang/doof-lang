import { Assert } from "std/assert"

import {
  ModuleNamespaceMapping,
  configureModuleNamespaces,
  moduleDiagnosticPath,
  moduleHeaderName,
  moduleNamespace,
  moduleSourceName,
} from "./emitter-names"

export function testUsesPackageIdentityForOwnedModuleNamespaces(): none {
  configureModuleNamespaces([
    ModuleNamespaceMapping { logicalPrefix: "/std/time", packageName: "std/time" },
    ModuleNamespaceMapping { logicalPrefix: "/vendor/cache", packageName: "acme-clock" },
  ])
  Assert.equal(moduleNamespace("/std/time/temporal.do"), "std_::time::temporal")
  Assert.equal(moduleNamespace("/vendor/cache/index.do"), "acme_clock::index")
  configureModuleNamespaces([])
}

export function testChoosesMostSpecificPackageNamespaceMapping(): none {
  configureModuleNamespaces([
    ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "umbrella" },
    ModuleNamespaceMapping { logicalPrefix: "/vendor/clock", packageName: "acme/clock" },
  ])
  Assert.equal(moduleNamespace("/vendor/clock/index.do"), "acme::clock::index")
  configureModuleNamespaces([])
}

export function testRetainsPathNamespaceWithoutPackageOwnership(): none {
  configureModuleNamespaces([])
  Assert.equal(moduleNamespace("/app/main.do"), "app_app_main_")
}

export function testInvalidatesCachedModuleNamespacesWhenMappingsChange(): none {
  configureModuleNamespaces([])
  Assert.equal(moduleNamespace("/vendor/cache/index.do"), "app_vendor_cache_index_")

  configureModuleNamespaces([
    ModuleNamespaceMapping { logicalPrefix: "/vendor/cache", packageName: "acme-clock" },
  ])
  Assert.equal(moduleNamespace("/vendor/cache/index.do"), "acme_clock::index")

  configureModuleNamespaces([])
  Assert.equal(moduleNamespace("/vendor/cache/index.do"), "app_vendor_cache_index_")
}

export function testFormatsPackageRelativeDiagnosticPaths(): none {
  configureModuleNamespaces([
    ModuleNamespaceMapping { logicalPrefix: "/workspace/assert", packageName: "std/assert" },
  ])
  Assert.equal(moduleDiagnosticPath("/workspace/assert/tests/assert.test.do", true), "tests/assert.test")
  Assert.equal(moduleDiagnosticPath("/workspace/assert/tests/assert.test.do", false), "tests/assert.test.do")
  configureModuleNamespaces([])
}

export function testUsesPackageRelativeGeneratedArtifactNames(): none {
  configureModuleNamespaces([
    ModuleNamespaceMapping {
      logicalPrefix: "/home/developer/work/doof-stdlib/os",
      packageName: "std/os",
    },
  ])
  Assert.equal(moduleHeaderName("/home/developer/work/doof-stdlib/os/index.do"), "std_os_index.hpp")
  Assert.equal(moduleSourceName("/home/developer/work/doof-stdlib/os/tests/os.test.do"), "std_os_tests_os_test.cpp")
  configureModuleNamespaces([])
}

export function testQuarkFixKeywordNamespaceComponents(): none {
  configureModuleNamespaces([ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "switch/more" }])
  let actual: string[] = []
  for name of ["explicit", "class", "namespace", "and", "co_await", "constexpr", "requires"] {
    actual.push(moduleNamespace("/vendor/" + name + ".do"))
  }
  configureModuleNamespaces([])
  let index = 0
  for name of ["explicit", "class", "namespace", "and", "co_await", "constexpr", "requires"] {
    Assert.equal(actual[index], "switch_::more::" + name + "_")
    index += 1
  }
}

import { join, tempDirectory } from "std/path"
import { ExecOptions, env, run } from "std/os"
import { exists, isDirectory, mkdir, readDir, readText, remove, writeText } from "std/fs"
import { BlobReader } from "std/blob"
import { compileWithLoader } from "./compiler"
import { noSourceLoader } from "./resolver"
import { SourceFile } from "./semantic"
import { hasErrorDiagnostics } from "./diagnostics"

export function testQuarkFixKeywordNamespacesCompileNatively(): none {
  root := join([tempDirectory(), "doof-native-keyword-namespaces"])
  clearNativeMatrix(root)
  try! mkdir(root)
  compiled := compileWithLoader([
    SourceFile { path: "/main.do", source: "import { left } from \"./vendor/explicit\"\nimport { right } from \"./vendor/class\"\nfunction main(): int => if left() + right() == 42 then 0 else 1" },
    SourceFile { path: "/vendor/explicit.do", source: "export function left(): int => 20" },
    SourceFile { path: "/vendor/class.do", source: "export function right(): int => 22" },
  ], "/main.do", noSourceLoader, [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "switch/more" }])
  for diagnostic of compiled.diagnostics { println(diagnostic.message) }
  Assert.equal(hasErrorDiagnostics(compiled.diagnostics), false)
  Assert.isTrue(compiled.emission != none)
  try! writeText(join([root, "doof_runtime.hpp"]), try! readText("runtime/doof_runtime.h"))
  executable := join([root, "matrix"])
  let args = ["-std=c++17", "-O0", "-pthread", "-o", executable]
  for module of compiled.emission!.modules {
    try! writeText(join([root, module.headerName]), module.header)
    path := join([root, module.sourceName])
    try! writeText(path, module.source)
    args.push(path)
  }
  compiler := env("CXX") ?? "c++"
  built := try! run(compiler, args, ExecOptions { withStdin: false, mergeStderrIntoStdout: true })
  if built.exitCode != 0 { println(BlobReader(built.stdout).readString(long(built.stdout.length))) }
  Assert.equal(built.exitCode, 0)
  executed := try! run(executable, [], ExecOptions { withStdin: false, mergeStderrIntoStdout: true })
  if executed.exitCode != 0 { println(BlobReader(executed.stdout).readString(long(executed.stdout.length))) }
  Assert.equal(executed.exitCode, 0)
  clearNativeMatrix(root)
}

function clearNativeMatrix(path: string): none {
  if !exists(path) { return }
  if isDirectory(path) { for entry of try! readDir(path) { clearNativeMatrix(join([path, entry.name])) } }
  try! remove(path)
}
