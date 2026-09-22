import { Assert } from "std/assert"
import { linuxBuildScript, linuxContainerArguments, linuxMakefile, linuxReleaseArchiveName, linuxReleaseTargets } from "./linux-build"

export function testLinuxReleaseArchiveNameIsStable(): none {
  targets := linuxReleaseTargets()
  Assert.equal(linuxReleaseArchiveName("1.2.3", targets[0]), "doof-1.2.3-linux-arm64-musl.tar.gz")
  Assert.equal(linuxReleaseArchiveName("1.2.3", targets[1]), "doof-1.2.3-linux-x64-musl.tar.gz")
}

export function testLinuxMakefileBuildsExactStaticMuslGraph(): none {
  makefile := linuxMakefile(["src_driver.cpp", "std/time/doof_time.cpp", "std/gzip/vendor/zlib/adler32.c", "std/zstd/vendor/zstd/lib/legacy/zstd_v01.c", "std/zstd/vendor/zstd/lib/dictBuilder/zdict.c", ".doof-cache/v1/check.json", "README"])
  Assert.stringContains(makefile, "src_driver.cpp")
  Assert.stringContains(makefile, "std/time/doof_time.cpp")
  Assert.stringContains(makefile, "std/gzip/vendor/zlib/adler32.c")
  Assert.stringContains(makefile, "std/time")
  Assert.stringContains(makefile, "$(addprefix -I,$(INCLUDE_DIRS))")
  Assert.stringContains(makefile, "-static")
  Assert.stringContains(makefile, "-std=c++17")
  Assert.stringNotContains(makefile, ".doof-cache")
  Assert.stringNotContains(makefile, "zstd_v01.c")
  Assert.stringNotContains(makefile, "zdict.c")
}

export function testLinuxContainerBuildChecksArchitectureVersionAndStaticElf(): none {
  targets := linuxReleaseTargets()
  arm64 := linuxBuildScript(targets[0])
  x64 := linuxBuildScript(targets[1])
  Assert.stringContains(arm64, "Linux/aarch64")
  Assert.stringContains(arm64, "ELF 64-bit.*ARM aarch64.*statically linked")
  Assert.stringContains(x64, "Linux/x86_64")
  Assert.stringContains(x64, "ELF 64-bit.*x86-64.*statically linked")
  for script of [arm64, x64] {
    Assert.stringContains(script, "apk add --no-cache build-base file linux-headers tar")
    Assert.stringContains(script, "toolchain.txt")
    Assert.stringContains(script, "doof $version")
    Assert.stringContains(script, "smoke/main.do")
    Assert.stringContains(script, "--sort=name")
  }
}

export function testLinuxContainerInvocationMountsOnlyStagedReleaseWork(): none {
  targets := linuxReleaseTargets()
  arm64 := linuxContainerArguments("/release work", "docker.io/library/alpine:3.22.1", "1.2.3", targets[0])
  readonly expectedArm64 = [
    "run", "--rm", "--platform", "linux/arm64", "--cpus", "8", "--memory", "8G", "--env", "DOOF_BUILD_JOBS=4", "--volume", "/release work:/work",
    "docker.io/library/alpine:3.22.1", "sh", "/work/linux-arm64/build.sh", "1.2.3",
    "/work/pending/doof-1.2.3-linux-arm64-musl.tar.gz",
  ]
  Assert.arrayEqual(arm64.cloneReadonly(), expectedArm64)
  x64 := linuxContainerArguments("/release work", "docker.io/library/alpine:3.22.1", "1.2.3", targets[1])
  readonly expectedX64 = [
    "run", "--rm", "--platform", "linux/amd64", "--rosetta", "--cpus", "8", "--memory", "8G", "--env", "DOOF_BUILD_JOBS=4", "--volume", "/release work:/work",
    "docker.io/library/alpine:3.22.1", "sh", "/work/linux-x64/build.sh", "1.2.3",
    "/work/pending/doof-1.2.3-linux-x64-musl.tar.gz",
  ]
  Assert.arrayEqual(x64.cloneReadonly(), expectedX64)
}
