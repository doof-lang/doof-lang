import { Assert } from "std/assert"
import { windowsBuildScript, windowsProjectFile, windowsReleaseArchiveName, windowsVisualStudioCommand, windowsVisualStudioScript } from "./windows-build"

export function testWindowsReleaseArchiveNameIsStable(): none {
  Assert.equal(windowsReleaseArchiveName("1.2.3"), "doof-1.2.3-windows-x64.zip")
}

export function testWindowsBuildScriptUsesUploadedInputsAndChecksVersion(): none {
  script := windowsBuildScript("1.2.3")
  Assert.isTrue(script.contains("Expand-Archive -LiteralPath $emittedArchive"))
  Assert.isTrue(script.contains("doof.vcxproj"))
  Assert.isTrue(script.contains("/m /p:Configuration=Release"))
  Assert.isTrue(script.contains("MSBuild"))
  Assert.isTrue(script.contains("$env:USERPROFILE"))
  Assert.isFalse(script.contains("Users\\Public"))
  Assert.isTrue(script.contains("doof 1.2.3"))
  Assert.isTrue(script.contains("doof-1.2.3-windows-x64.zip"))
  Assert.isFalse(script.contains("DOOF_WINDOWS_HOST_PASSWORD"))
}

export function testWindowsProjectFileUsesParallelReleaseBuildAndNativeIncludes(): none {
  project := windowsProjectFile(["src_main.cpp", "std/blob/native_blob.hpp", "std/time/doof_time.cpp", "std/gzip/vendor/zlib/adler32.c"])
  Assert.isTrue(project.contains("<MultiProcessorCompilation>true</MultiProcessorCompilation>"))
  Assert.isTrue(project.contains("<ClCompile Include=\"**\\*.cpp\""))
  Assert.isTrue(project.contains("<CompileAs>CompileAsC</CompileAs>"))
  Assert.isTrue(project.contains("$(ProjectDir)emitted-extract\\std\\blob;"))
  Assert.isFalse(project.contains("Users\\Public"))
}

export function testWindowsVisualStudioCommandUsesX64DeveloperEnvironment(): none {
  command := windowsVisualStudioCommand("1.2.3")
  Assert.isTrue(command.contains("build.cmd"))
}

export function testWindowsVisualStudioScriptUsesVsWhereAndFallback(): none {
  script := windowsVisualStudioScript("1.2.3")
  Assert.isTrue(script.contains("%USERPROFILE%\\doof-release-1.2.3"))
  Assert.isFalse(script.contains("Users\\Public"))
  Assert.isTrue(script.contains("vswhere.exe"))
  Assert.isTrue(script.contains("Microsoft.VisualStudio.Component.VC.Tools.x86.x64"))
  Assert.isTrue(script.contains("VsDevCmd.bat"))
}
