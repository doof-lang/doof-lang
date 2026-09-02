import { Assert } from "std/assert"
import { NativeBuildPlan, parsePackageManifest } from "./package-manifest"

export function testParsesLocalPackageDependenciesAndStdlibPreparation(): none {
  manifest := try! parsePackageManifest(
    "{\"dependencies\":{\"local\":{\"path\":\"../local\"}},\"build\":{\"stdlib\":{\"prepare\":[{\"program\":\"sh\",\"args\":[\"\${packageRoot}/build.sh\",\"\${nativeTarget}\"],\"env\":{\"SDKROOT\":\"\${sdkPath}\"},\"workingDirectory\":\"vendor\"}]}}}",
    "/app/doof.json",
    "/app",
    "macos",
  )

  Assert.equal(manifest.dependencies[0].path, "/local")
  Assert.equal(manifest.stdlibPreparation[0].args[1], "\${nativeTarget}")
  Assert.equal(try! manifest.stdlibPreparation[0].env.get("SDKROOT"), "\${sdkPath}")
}

export function testRejectsRemotePackageDependencies(): none {
  result := parsePackageManifest(
    "{\"dependencies\":{\"remote\":{\"url\":\"https://example.com/remote.git\",\"version\":\"1.2\"}}}",
    "/app/doof.json", "/app", "linux",
  )
  _ := result else error {
    Assert.stringContains(error, "must use a local path")
    return
  }
  panic("expected floating package dependency failure")
}

export function testRejectsRetiredDependencyFields(): none {
  external := parsePackageManifest(
    "{\"externalDependencies\":{\"bad\":{\"kind\":\"archive\",\"url\":\"https://example.com/a.tar.gz\",\"destination\":\"vendor/a\"}}}",
    "/app/doof.json", "/app", "linux",
  )
  _ := external else error {
    Assert.stringContains(error, "externalDependencies is no longer supported")
  }
  resolutions := parsePackageManifest(
    "{\"resolutions\":{}}",
    "/app/doof.json", "/app", "linux",
  )
  _ := resolutions else error {
    Assert.stringContains(error, "resolutions is no longer supported")
    return
  }
  panic("expected retired dependency field failure")
}

export function testParsesAndNormalizesExecutableResources(): none {
  manifest := try! parsePackageManifest(
    "{\"name\":\"doof\",\"resources\":[{\"from\":\"doof_runtime.h\",\"to\":\".\"},\"assets\"]}",
    "/compiler/doof.json",
    "/compiler",
    "macos",
  )

  Assert.equal(manifest.resources.length, 2)
  Assert.equal(manifest.resources[0].sourcePath, "/compiler/doof_runtime.h")
  Assert.equal(manifest.resources[0].destination, "")
  Assert.equal(manifest.resources[1].sourcePath, "/compiler/assets")
  Assert.equal(manifest.resources[1].destination, "assets")
}

export function testUsesBuildResourcesWhenRootResourcesAreAbsent(): none {
  manifest := try! parsePackageManifest(
    "{\"build\":{\"resources\":[\"assets\"]}}",
    "/app/doof.json",
    "/app",
    "linux",
  )

  Assert.equal(manifest.resources.length, 1)
  Assert.equal(manifest.resources[0].sourcePath, "/app/assets")
  Assert.equal(manifest.resources[0].destination, "assets")
}

export function testRejectsExecutableResourceDestinationsOutsideResourceDirectory(): none {
  result := parsePackageManifest(
    "{\"resources\":[{\"from\":\"runtime.h\",\"to\":\"../runtime.h\"}]}",
    "/bad/doof.json",
    "/bad",
    "linux",
  )
  _ := result else error {
    Assert.stringContains(error, "resources[0].to must stay within the executable resource directory")
    return
  }
  panic("expected invalid resource destination failure")
}

export function testParsesAndNormalizesBaseNativeInputs(): none {
  manifest := try! parsePackageManifest(
    "{\"name\":\"std/time\",\"build\":{\"native\":{\"includePaths\":[\"include\"],\"sourceFiles\":[\"./doof_time.cpp\"],\"extraCopyPaths\":[\"doof_time.hpp\"],\"defines\":[\"DOOF_TIME=1\"]}}}",
    "/stdlib/time/doof.json",
    "/stdlib/time",
    "macos",
  )

  Assert.equal(manifest.name, "std/time")
  Assert.equal(manifest.nativeBuild.includePaths.length, 1)
  Assert.equal(manifest.nativeBuild.includePaths[0], "/stdlib/time/include")
  Assert.equal(manifest.nativeBuild.sourceFiles.length, 1)
  Assert.equal(manifest.nativeBuild.sourceFiles[0], "/stdlib/time/doof_time.cpp")
  Assert.equal(manifest.nativeBuild.extraCopyPaths.length, 1)
  Assert.equal(manifest.nativeBuild.extraCopyPaths[0], "/stdlib/time/doof_time.hpp")
  Assert.equal(manifest.nativeBuild.defines.length, 1)
  Assert.equal(manifest.nativeBuild.defines[0], "DOOF_TIME=1")
}

export function testMergesOnlyTheSelectedPlatformFragment(): none {
  manifest := try! parsePackageManifest(
    "{\"name\":\"std/path\",\"build\":{\"native\":{\"frameworks\":[\"Base\"],\"macos\":{\"frameworks\":[\"CoreFoundation\"],\"sourceFiles\":[\"path.mm\"]},\"linux\":{\"linkLibraries\":[\"pthread\"],\"sourceFiles\":[\"path.cpp\"]}}}}",
    "/stdlib/path/doof.json",
    "/stdlib/path",
    "macos",
  )

  Assert.equal(manifest.nativeBuild.frameworks.length, 2)
  Assert.equal(manifest.nativeBuild.frameworks[0], "Base")
  Assert.equal(manifest.nativeBuild.frameworks[1], "CoreFoundation")
  Assert.equal(manifest.nativeBuild.sourceFiles.length, 1)
  Assert.equal(manifest.nativeBuild.sourceFiles[0], "/stdlib/path/path.mm")
  Assert.equal(manifest.nativeBuild.linkLibraries.length, 0)
}

export function testSelectsWasmNativeFragmentForWasmTargets(): none {
  manifest := try! parsePackageManifest(
    "{\"build\":{\"target\":\"wasm\",\"native\":{\"defines\":[\"BASE\"],\"linux\":{\"defines\":[\"LINUX\"]},\"wasm\":{\"sourceFiles\":[\"native_wasm.cpp\"],\"defines\":[\"WASM\"]}}}}",
    "/app/doof.json",
    "/app",
    "linux",
  )

  Assert.equal(manifest.target, "wasm")
  Assert.equal(manifest.nativeBuild.sourceFiles[0], "/app/native_wasm.cpp")
  Assert.equal(manifest.nativeBuild.defines.contains("BASE"), true)
  Assert.equal(manifest.nativeBuild.defines.contains("WASM"), true)
  Assert.equal(manifest.nativeBuild.defines.contains("LINUX"), false)
}

export function testDeduplicatesManifestNativeInputs(): none {
  first := try! parsePackageManifest(
    "{\"build\":{\"native\":{\"frameworks\":[\"CoreFoundation\",\"CoreFoundation\"]}}}",
    "/one/doof.json",
    "/one",
    "macos",
  )
  Assert.equal(first.nativeBuild.frameworks.length, 1)
  Assert.equal(first.nativeBuild.frameworks[0], "CoreFoundation")
}

export function testRejectsInvalidNativeStringArrays(): none {
  result := parsePackageManifest(
    "{\"build\":{\"native\":{\"sourceFiles\":[4]}}}",
    "/bad/doof.json",
    "/bad",
    "linux",
  )
  _ := result else error {
    Assert.stringContains(error, "build.native.sourceFiles[0] must be a string")
    return
  }
  panic("expected invalid manifest failure")
}

export function testParsesCompactMacOSAppAndReleaseSettings(): none {
  manifest := try! parsePackageManifest(
    "{\"name\":\"demo-app\",\"version\":\"1.2\",\"target\":\"macos-app\",\"executable\":\"Demo\",\"id\":\"dev.example.demo\",\"title\":\"Demo App\",\"icon\":\"icon.png\",\"resources\":[\"assets\"],\"build\":{\"macosApp\":{\"category\":\"public.app-category.games\",\"embeddedLibraries\":[{\"library\":\"SDL3\"},{\"path\":\"vendor/Foo.framework\"}]},\"package\":{\"distDir\":\"artifacts\",\"macos\":{\"signing\":\"ad-hoc\",\"sandbox\":true,\"entitlements\":\"release.plist\"}}}}",
    "/app/doof.json",
    "/app",
    "macos",
  )

  Assert.equal(manifest.target, "macos-app")
  Assert.equal(manifest.macosApp != none, true)
  Assert.equal(manifest.macosApp!.executableName, "Demo")
  Assert.equal(manifest.macosApp!.bundleId, "dev.example.demo")
  Assert.equal(manifest.macosApp!.displayName, "Demo App")
  Assert.equal(manifest.macosApp!.version, "1.2")
  Assert.equal(manifest.macosApp!.iconPath, "/app/icon.png")
  Assert.equal(manifest.macosApp!.resources[0].sourcePath, "/app/assets")
  Assert.equal(manifest.macosApp!.embeddedLibraries[0].library, "SDL3")
  Assert.equal(manifest.macosApp!.embeddedLibraries[1].path, "/app/vendor/Foo.framework")
  Assert.equal(manifest.packageConfig!.distDirectory, "/app/artifacts")
  Assert.equal(manifest.packageConfig!.signing, "ad-hoc")
  Assert.equal(manifest.packageConfig!.sandbox, true)
  Assert.equal(manifest.packageConfig!.entitlementsPath, "/app/release.plist")
}

export function testRejectsManagedMacOSInfoPlistOverrides(): none {
  result := parsePackageManifest(
    "{\"name\":\"demo\",\"build\":{\"target\":\"macos-app\",\"macosApp\":{\"infoPlist\":{\"CFBundleIdentifier\":\"override\"}}}}",
    "/app/doof.json",
    "/app",
    "macos",
  )
  _ := result else error {
    Assert.stringContains(error, "CFBundleIdentifier conflicts with a Doof-managed Info.plist key")
    return
  }
  panic("expected managed plist override failure")
}

export function testParsesIOSAppAndPackageSettings(): none {
  manifest := try! parsePackageManifest(
    "{\"name\":\"demo-ios\",\"version\":\"2.0\",\"target\":\"ios-app\",\"executable\":\"Demo\",\"build\":{\"iosApp\":{\"bundleId\":\"dev.example.ios\",\"displayName\":\"Demo iOS\",\"minimumDeploymentTarget\":\"17.0\",\"icon\":\"icon.png\",\"resources\":[{\"from\":\"assets\",\"to\":\"Data\"}]},\"package\":{\"ios\":{\"identity\":\"Apple Distribution: Example\",\"provisioningProfile\":\"profiles/app.mobileprovision\"}},\"native\":{\"frameworks\":[\"Base\"],\"iosDevice\":{\"frameworks\":[\"UIKit\"]}}}}",
    "/app/doof.json",
    "/app",
    "ios-device",
  )

  Assert.equal(manifest.iosApp != none, true)
  Assert.equal(manifest.iosApp!.executableName, "Demo")
  Assert.equal(manifest.iosApp!.bundleId, "dev.example.ios")
  Assert.equal(manifest.iosApp!.minimumDeploymentTarget, "17.0")
  Assert.equal(manifest.iosApp!.iconPath, "/app/icon.png")
  Assert.equal(manifest.iosApp!.resources[0].destination, "Data")
  Assert.equal(manifest.nativeBuild.frameworks.contains("UIKit"), true)
  Assert.equal(manifest.iosPackageConfig!.identity, "Apple Distribution: Example")
  Assert.equal(manifest.iosPackageConfig!.provisioningProfilePath, "/app/profiles/app.mobileprovision")
}

export function testRejectsManagedIOSInfoPlistOverrides(): none {
  result := parsePackageManifest(
    "{\"name\":\"demo\",\"build\":{\"target\":\"ios-app\",\"iosApp\":{\"infoPlist\":{\"CFBundleIdentifier\":\"override\"}}}}",
    "/app/doof.json",
    "/app",
    "ios-simulator",
  )
  _ := result else error {
    Assert.stringContains(error, "CFBundleIdentifier conflicts with a Doof-managed Info.plist key")
    return
  }
  panic("expected managed plist override failure")
}

export function testRejectsInvalidMacOSSigningMode(): none {
  result := parsePackageManifest(
    "{\"name\":\"demo\",\"build\":{\"package\":{\"macos\":{\"signing\":\"mystery\"}}}}",
    "/app/doof.json",
    "/app",
    "macos",
  )
  _ := result else error {
    Assert.stringContains(error, "build.package.macos.signing")
    return
  }
  panic("expected invalid signing mode failure")
}

export function testRejectsMacOSPackagePathsOutsidePackageRoot(): none {
  result := parsePackageManifest(
    "{\"name\":\"demo\",\"build\":{\"package\":{\"distDir\":\"../artifacts\"}}}",
    "/app/doof.json",
    "/app",
    "macos",
  )
  _ := result else error {
    Assert.stringContains(error, "build.package.distDir must stay within the package root")
    return
  }
  panic("expected invalid dist directory failure")
}
