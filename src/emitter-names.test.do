import { Assert } from "std/assert"

import {
  ModuleNamespaceMapping,
  prepareModuleNames,
  moduleDiagnosticPath,
  moduleHeaderName,
  moduleNamespace,
  moduleSourceName,
} from "./emitter-names"

export function testUsesPackageIdentityForOwnedModuleNamespaces(): none {
  names := prepareModuleNames([
    ModuleNamespaceMapping { logicalPrefix: "/std/time", packageName: "std/time" },
    ModuleNamespaceMapping { logicalPrefix: "/vendor/cache", packageName: "acme-clock" },
  ])
  Assert.equal(moduleNamespace("/std/time/temporal.do", names), "std_::time::temporal")
  Assert.equal(moduleNamespace("/vendor/cache/index.do", names), "acme_clock::index")
}

export function testChoosesMostSpecificPackageNamespaceMapping(): none {
  names := prepareModuleNames([
    ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "umbrella" },
    ModuleNamespaceMapping { logicalPrefix: "/vendor/clock", packageName: "acme/clock" },
  ])
  Assert.equal(moduleNamespace("/vendor/clock/index.do", names), "acme::clock::index")
}

export function testRetainsPathNamespaceWithoutPackageOwnership(): none {
  names := prepareModuleNames([])
  Assert.equal(moduleNamespace("/app/main.do", names), "app_app_main_")
}

export function testUsesEachExplicitModuleNamespaceSnapshot(): none {
  let names = prepareModuleNames([])
  Assert.equal(moduleNamespace("/vendor/cache/index.do", names), "app_vendor_cache_index_")

  names = prepareModuleNames([
    ModuleNamespaceMapping { logicalPrefix: "/vendor/cache", packageName: "acme-clock" },
  ])
  Assert.equal(moduleNamespace("/vendor/cache/index.do", names), "acme_clock::index")

  names = prepareModuleNames([])
  Assert.equal(moduleNamespace("/vendor/cache/index.do", names), "app_vendor_cache_index_")
}

export function testFormatsPackageRelativeDiagnosticPaths(): none {
  names := prepareModuleNames([
    ModuleNamespaceMapping { logicalPrefix: "/workspace/assert", packageName: "std/assert" },
  ])
  Assert.equal(moduleDiagnosticPath("/workspace/assert/tests/assert.test.do", true, names), "tests/assert.test")
  Assert.equal(moduleDiagnosticPath("/workspace/assert/tests/assert.test.do", false, names), "tests/assert.test.do")
}

export function testUsesPackageRelativeGeneratedArtifactNames(): none {
  names := prepareModuleNames([
    ModuleNamespaceMapping {
      logicalPrefix: "/home/developer/work/doof-stdlib/os",
      packageName: "std/os",
    },
  ])
  Assert.equal(moduleHeaderName("/home/developer/work/doof-stdlib/os/index.do", names), "std_os_index.hpp")
  Assert.equal(moduleSourceName("/home/developer/work/doof-stdlib/os/tests/os.test.do", names), "std_os_tests_os_test.cpp")
}

export function testQuarkFixKeywordNamespaceComponents(): none {
  names := prepareModuleNames([ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "switch/more" }])
  let actual: string[] = []
  for name of ["explicit", "class", "namespace", "and", "co_await", "constexpr", "requires"] {
    actual.push(moduleNamespace("/vendor/" + name + ".do", names))
  }
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
    SourceFile { path: "/vendor/explicit.do", source: "
export function left(): int => 20" },
    SourceFile { path: "/vendor/class.do", source: "
export function right(): int => 22" },
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

export function testReadonlyEmissionNamesAreIndependentAndDoNotCacheMisses(): none {
  mappings := [ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "one", outputRoot: "native" }]
  first := prepareModuleNames(mappings, ["/vendor/item.do"])
  mappings[0] = ModuleNamespaceMapping { logicalPrefix: "/vendor", packageName: "two" }
  second := prepareModuleNames(mappings, ["/vendor/item.do"])
  Assert.equal(moduleNamespace("/vendor/item.do", first), "one::item")
  Assert.equal(moduleNamespace("/vendor/item.do", second), "two::item")
  Assert.equal(moduleNamespace("/vendor/missing.do", first), "one::missing")
  Assert.equal(first.namespaces.size, 1)
  Assert.equal(moduleNamespace("/vendor/item.do"), "app_vendor_item_")
  Assert.equal(moduleDiagnosticPath("/vendor/item.do", true, first), "item")
}

import { cppIdentifier } from "./emitter-names"

export function testKeywordLengthDispatchPreservesEveryKeyword(): none {
  keywords := [
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
    "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
    "class", "compl", "concept", "const", "consteval", "constexpr", "constinit", "const_cast",
    "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete", "do",
    "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false",
    "float", "for", "friend", "goto", "if", "inline", "int", "long",
    "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
    "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "requires",
    "return", "short", "signed", "sizeof", "static", "static_assert", "struct", "switch",
    "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid",
    "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t",
    "while", "xor", "xor_eq",
  ]
  for keyword of keywords {
    Assert.equal(cppIdentifier(keyword), keyword + "_")
    Assert.equal(cppIdentifier(keyword + "_"), keyword + "_")
    Assert.equal(cppIdentifier("0" + keyword.substring(1, keyword.length)), "0" + keyword.substring(1, keyword.length))
  }
}

export function testKeywordLengthDispatchPreservesOrdinaryNamesAndStreamMacros(): none {
  for name of ["", "x", "node", "Value", "abcdefghijklmnop", "abcdefghijklmnopq", "co_return_value", "CLASS", "π"] {
    Assert.equal(cppIdentifier(name), name)
  }
  for name of ["stdin", "stdout", "stderr"] { Assert.equal(cppIdentifier(name), name + "_") }
}
