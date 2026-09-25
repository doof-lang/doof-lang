import { join as joinStrings } from "std/string"

export class LinuxReleaseTarget {
  readonly name: string
  readonly platform: string
  readonly machine: string
  readonly elfPattern: string
  readonly rosetta: bool
}

/** Architectures built from the same Linux-targeted compiler graph. */
export function linuxReleaseTargets(): LinuxReleaseTarget[] => [
  LinuxReleaseTarget { name: "arm64", platform: "linux/arm64", machine: "aarch64", elfPattern: "ARM aarch64", rosetta: false },
  LinuxReleaseTarget { name: "x64", platform: "linux/amd64", machine: "x86_64", elfPattern: "x86-64", rosetta: true },
]

export function linuxReleaseArchiveName(version: string, target: LinuxReleaseTarget): string => "doof-" + version + "-linux-" + target.name + "-musl.tar.gz"

function makeVariable(name: string, values: string[]): string {
  if values.length == 0 { return name + " :=\n" }
  return name + " := \\\n  " + joinStrings(values.cloneReadonly(), " \\\n  ") + "\n"
}

/**
 * Builds only the exact C/C++ graph emitted on the release host. Native
 * package inputs live below std/, while generated Doof modules are at root.
 */
export function linuxMakefile(emittedFiles: string[]): string {
  let cpp: string[] = []
  let c: string[] = []
  let directories: string[] = []
  for name of emittedFiles {
    if name.startsWith(".doof-") || name.contains("/.doof-") { continue }
    parts := name.split("/")
    let prefix = ""
    for index of 0..<(parts.length - 1) {
      prefix = if prefix == "" then parts[index] else prefix + "/" + parts[index]
      if !directories.contains(prefix) { directories.push(prefix) }
    }
    if name.contains("/test/") || name.contains("/tests/") || name.contains("/examples/") || name.contains("/contrib/") || name.contains("/legacy/") || name.contains("/deprecated/") || name.contains("/dictBuilder/") { continue }
    if name.endsWith(".cpp") { cpp.push(name) }
    else if name.endsWith(".c") { c.push(name) }
  }
  return makeVariable("CXX_SOURCES", cpp) +
    makeVariable("C_SOURCES", c) +
    makeVariable("INCLUDE_DIRS", directories) +
    "OBJECTS := $(CXX_SOURCES:.cpp=.o) $(C_SOURCES:.c=.o)\n" +
    "CPPFLAGS := -I. $(addprefix -I,$(INCLUDE_DIRS))\n" +
    "COMMON_FLAGS := -O2 -DNDEBUG -DZSTD_DISABLE_ASM -ffunction-sections -fdata-sections -flto -pthread\n" +
    "CXXFLAGS := -std=c++17 $(COMMON_FLAGS)\n" +
    "CFLAGS := -std=c11 $(COMMON_FLAGS)\n" +
    "LDFLAGS := -static -flto -pthread -Wl,--gc-sections -Wl,--strip-all\n\n" +
    ".PHONY: all clean\n" +
    "all: doof\n\n" +
    "doof: $(OBJECTS)\n\t$(CXX) $(OBJECTS) $(LDFLAGS) -o $@\n\n" +
    "%.o: %.cpp\n\t$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@\n\n" +
    "%.o: %.c\n\t$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@\n\n" +
    "clean:\n\trm -f $(OBJECTS) doof\n"
}

/** Runs inside Alpine after the emitted graph has crossed the VM boundary. */
export function linuxBuildScript(target: LinuxReleaseTarget): string {
  return "#!/bin/sh\n" +
    "set -eu\n" +
    "[ \"$#\" -eq 2 ] || { echo 'usage: build.sh <version> <archive>' >&2; exit 2; }\n" +
    "version=$1\n" +
    "archive=$2\n" +
    "root=$(CDPATH= cd -- \"$(dirname -- \"$0\")\" && pwd)\n" +
    "[ \"$(uname -s)/$(uname -m)\" = Linux/" + target.machine + " ] || { echo 'Linux " + target.name + " container is required' >&2; exit 1; }\n" +
    "apk add --no-cache build-base file linux-headers tar\n" +
    "{ printf 'alpine '; cat /etc/alpine-release; c++ --version | head -n 1; ldd --version 2>&1 | head -n 1; } > \"$root/toolchain.txt\"\n" +
    "jobs=\"\${DOOF_BUILD_JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}\"\n" +
    "case \"$jobs\" in ''|*[!0-9]*|0) echo 'DOOF_BUILD_JOBS must be positive' >&2; exit 1 ;; esac\n" +
    "make -C \"$root/emitted\" -f \"$root/Makefile\" -j\"$jobs\"\n" +
    "rm -rf \"$root/dist\" \"$root/smoke\"\n" +
    "mkdir -p \"$root/dist\" \"$root/smoke\"\n" +
    "cp \"$root/emitted/doof\" \"$root/dist/doof\"\n" +
    "cp \"$root/resources/doof_runtime.hpp\" \"$root/resources/doof_observer.hpp\" \"$root/resources/doof_observer_platform.hpp\" \"$root/resources/doof_wasm_test_runner_apple.swift\" \"$root/resources/doof-stdlib.tar\" \"$root/dist/\"\n" +
    "cp -R \"$root/resources/observer-ui\" \"$root/dist/observer-ui\"\n" +
    "[ \"$(\"$root/dist/doof\" --version)\" = \"doof $version\" ] || { echo 'Linux compiler version mismatch' >&2; exit 1; }\n" +
    "file \"$root/dist/doof\" | grep -Eq 'ELF 64-bit.*" + target.elfPattern + ".*statically linked' || { echo 'Linux compiler is not a static " + target.name + " ELF binary' >&2; exit 1; }\n" +
    "\"$root/dist/doof\" --help >/dev/null\n" +
    "printf 'function main(): int => 0\\n' > \"$root/smoke/main.do\"\n" +
    "env -u DOOF_STDLIB_ROOT -u DOOF_RUNTIME_HEADER \"$root/dist/doof\" run \"$root/smoke/main.do\" -o \"$root/smoke/output\" >/dev/null\n" +
    "rm -f \"$archive\"\n" +
    "tar --sort=name --mtime='@0' --owner=0 --group=0 --numeric-owner -czf \"$archive\" -C \"$root/dist\" doof doof_runtime.hpp doof_observer.hpp doof_observer_platform.hpp doof_wasm_test_runner_apple.swift doof-stdlib.tar observer-ui\n"
}

export function linuxContainerArguments(work: string, image: string, version: string, target: LinuxReleaseTarget, cpus: string = "8", memory: string = "8G", jobs: string = "4"): string[] {
  archive := "/work/pending/" + linuxReleaseArchiveName(version, target)
  arguments := ["run", "--rm", "--platform", target.platform]
  if target.rosetta { arguments.push("--rosetta") }
  for argument of ["--cpus", cpus, "--memory", memory, "--env", "DOOF_BUILD_JOBS=" + jobs, "--volume", work + ":/work", image, "sh", "/work/linux-" + target.name + "/build.sh", version, archive] { arguments.push(argument) }
  return arguments
}
