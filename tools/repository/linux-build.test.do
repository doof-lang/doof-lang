import { Assert } from "std/assert"
import { parseJsonObject } from "std/json"
import { linuxBuildScript, linuxContainerArguments, linuxMakefile, linuxProbeSources, linuxReleaseArchiveName, linuxReleaseTargets } from "./linux-build"

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
  Assert.stringContains(makefile, "-DZSTD_DISABLE_ASM")
  Assert.stringContains(makefile, "-std=c++17")
  Assert.stringNotContains(makefile, ".doof-cache")
  Assert.stringNotContains(makefile, "zstd_v01.c")
  Assert.stringNotContains(makefile, "zdict.c")
}

export function testLinuxMakefileSkipsOptionalProbeSources(): none {
  makefile := linuxMakefile(["src_driver.cpp", "std/crypto/doof_rsa.cpp", "std/crypto/rsa_openssl_probe.cpp"], ["std/crypto/rsa_openssl_probe.cpp"])
  Assert.stringContains(makefile, "std/crypto/doof_rsa.cpp")
  Assert.stringNotContains(makefile, "rsa_openssl_probe.cpp")
}

export function testLinuxProbeSourcesReadsManifestProbes(): none {
  manifest := parseJsonObject(`{"build":{"native":{"sourceFiles":["./doof_rsa.cpp"],"linux":{"optionalPkgConfigPackages":[
    {"name":"libcrypto","define":"RSA_EVP","probeSource":"./rsa_openssl_probe.cpp"},
    {"name":"libz","define":"Z","probeSource":"probes/z.cpp"}]}}}}`)!
  probes := linuxProbeSources("std/crypto", manifest)
  Assert.equal(probes.length, 2)
  Assert.equal(probes[0], "std/crypto/rsa_openssl_probe.cpp")
  Assert.equal(probes[1], "std/crypto/probes/z.cpp")
}

export function testLinuxProbeSourcesIgnoresManifestsWithoutProbes(): none {
  Assert.equal(linuxProbeSources("std/time", parseJsonObject(`{"build":{"native":{"sourceFiles":["./doof_time.cpp"]}}}`)!).length, 0)
  Assert.equal(linuxProbeSources("std/time", parseJsonObject(`{"name":"std/time"}`)!).length, 0)
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
