import { homeDirectory, join } from "std/path"
import { exists } from "std/fs"
import { require, setting } from "./common"

export class WindowsBuildConfig {
  readonly host: string
  readonly mac: string | none
  readonly broadcast: string | none
  readonly username: string
  readonly password: string
  readonly knownHostsPath: string
}

export function windowsBuildEnabled(): bool => setting("DOOF_WINDOWS_HOST") != ""

export function windowsBuildConfig(): Result<WindowsBuildConfig, string> {
  host := setting("DOOF_WINDOWS_HOST")
  if host == "" { return Failure("") }
  try require(setting("DOOF_WINDOWS_HOST_USERNAME") != "", "DOOF_WINDOWS_HOST_USERNAME is required when DOOF_WINDOWS_HOST is set")
  try require(setting("DOOF_WINDOWS_HOST_PASSWORD") != "", "DOOF_WINDOWS_HOST_PASSWORD is required when DOOF_WINDOWS_HOST is set")
  macValue := setting("DOOF_WINDOWS_HOST_MAC")
  broadcastValue := setting("DOOF_WINDOWS_HOST_BROADCAST")
  try home := homeDirectory()
  knownHosts := setting("DOOF_WINDOWS_HOST_KNOWN_HOSTS", join([home, ".ssh", "known_hosts"]))
  try require(exists(knownHosts), "Windows SSH known-hosts file does not exist: " + knownHosts + " (set DOOF_WINDOWS_HOST_KNOWN_HOSTS to override)")
  return Success(WindowsBuildConfig {
    host,
    mac: if macValue == "" then none else macValue,
    broadcast: if broadcastValue == "" then none else broadcastValue,
    username: setting("DOOF_WINDOWS_HOST_USERNAME"),
    password: setting("DOOF_WINDOWS_HOST_PASSWORD"),
    knownHostsPath: knownHosts,
  })
}

export function windowsReleaseArchiveName(version: string): string => "doof-" + version + "-windows-x64.zip"

function xmlPath(path_: string): string => path_.replaceAll("&", "&amp;").replaceAll("<", "&lt;").replaceAll(">", "&gt;").replaceAll("\"", "&quot;")

export function windowsProjectFile(emittedFiles: string[]): string {
  let directories: string[] = []
  for file of emittedFiles {
    parts := file.split("/")
    let prefix = ""
    for index of 0..<(parts.length - 1) {
      prefix = if prefix == "" then parts[index] else prefix + "\\" + parts[index]
      if !directories.contains(prefix) { directories.push(prefix) }
    }
  }
  let includes = "$(ProjectDir)emitted-extract;"
  for directory of directories { includes += "$(ProjectDir)emitted-extract\\" + directory + ";" }
  return "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" +
    "<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n" +
    "  <ItemGroup Label=\"ProjectConfigurations\"><ProjectConfiguration Include=\"Release|x64\"><Configuration>Release</Configuration><Platform>x64</Platform></ProjectConfiguration></ItemGroup>\n" +
    "  <PropertyGroup Label=\"Globals\"><ProjectGuid>{7A3E72D0-7F5D-4F7A-AE3D-6C5D6CCB7D02}</ProjectGuid><Keyword>Win32Proj</Keyword><RootNamespace>doof</RootNamespace></PropertyGroup>\n" +
    "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" />\n" +
    "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\" Label=\"Configuration\"><ConfigurationType>Application</ConfigurationType><UseDebugLibraries>false</UseDebugLibraries><WholeProgramOptimization>true</WholeProgramOptimization><PlatformToolset>v145</PlatformToolset><WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion></PropertyGroup>\n" +
    "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />\n" +
    "  <PropertyGroup><OutDir>$(ProjectDir)dist\\</OutDir><IntDir>$(ProjectDir)objects\\</IntDir></PropertyGroup>\n" +
    "  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\"><ClCompile><WarningLevel>Level3</WarningLevel><Optimization>MaxSpeed</Optimization><LanguageStandard>stdcpp17</LanguageStandard><RuntimeLibrary>MultiThreaded</RuntimeLibrary><AdditionalIncludeDirectories>$(ProjectDir);" + includes + "%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories><PreprocessorDefinitions>NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions><MultiProcessorCompilation>true</MultiProcessorCompilation></ClCompile><Link><SubSystem>Console</SubSystem><EnableCOMDATFolding>true</EnableCOMDATFolding><OptimizeReferences>true</OptimizeReferences><GenerateDebugInformation>false</GenerateDebugInformation></Link></ItemDefinitionGroup>\n" +
    "  <ItemGroup><ClCompile Include=\"**\\*.cpp\" Exclude=\"**\\test\\**;**\\tests\\**;**\\examples\\**;**\\contrib\\**;**\\legacy\\**;**\\deprecated\\**;**\\dictBuilder\\**\" /><ClCompile Include=\"**\\*.c\" Exclude=\"**\\test\\**;**\\tests\\**;**\\examples\\**;**\\contrib\\**;**\\legacy\\**;**\\deprecated\\**;**\\dictBuilder\\**\"><CompileAs>CompileAsC</CompileAs></ClCompile></ItemGroup>\n" +
    "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" />\n</Project>\n"
}

export function windowsBuildScript(version: string): string {
  // The Mac emits all Doof and native inputs. The Windows host only supplies
  // MSVC; it must not have a Doof checkout or compiler installed.
  return "$ErrorActionPreference = 'Stop'\n" +
    "$work = Join-Path $env:USERPROFILE 'doof-release-" + version + "'\n" +
    "$emittedArchive = Join-Path $work 'emitted.zip'\n" +
    "$dist = Join-Path $work 'dist'\n" +
    "$emittedExtract = Join-Path $work 'emitted-extract'\n" +
    "Remove-Item $emittedExtract,$dist -Recurse -Force -ErrorAction SilentlyContinue\n" +
    "New-Item -ItemType Directory -Force -Path $emittedExtract,$dist | Out-Null\n" +
    "Expand-Archive -LiteralPath $emittedArchive -DestinationPath $emittedExtract -Force\n" +
    "$project = Join-Path $work 'doof.vcxproj'\n" +
    "$msbuild = (Get-Command msbuild.exe -ErrorAction SilentlyContinue).Source\n" +
    "if (-not $msbuild) { throw 'MSBuild was not found in the Visual Studio developer environment' }\n" +
    "& $msbuild $project /m /p:Configuration=Release /p:Platform=x64 /nologo\n" +
    "if ($LASTEXITCODE -ne 0) { throw 'MSBuild failed' }\n" +
    "if (-not (Test-Path (Join-Path $dist 'doof.exe'))) { throw 'MSVC build did not produce dist\\doof.exe' }\n" +
    "if ((& (Join-Path $dist 'doof.exe') --version).Trim() -ne 'doof " + version + "') { throw 'Windows compiler version mismatch' }\n" +
    "Copy-Item (Join-Path $emittedExtract 'doof_runtime.hpp') (Join-Path $dist 'doof_runtime.hpp') -Force\n" +
    "Copy-Item (Join-Path $emittedExtract 'doof_observer.hpp') (Join-Path $dist 'doof_observer.hpp') -Force\n" +
    "Copy-Item (Join-Path $emittedExtract 'doof_observer_platform.hpp') (Join-Path $dist 'doof_observer_platform.hpp') -Force\n" +
    "Copy-Item (Join-Path $emittedExtract 'doof_wasm_test_runner_apple.swift') (Join-Path $dist 'doof_wasm_test_runner_apple.swift') -Force\n" +
    "Copy-Item (Join-Path $emittedExtract 'observer-ui') (Join-Path $dist 'observer-ui') -Recurse -Force\n" +
    "Copy-Item (Join-Path $work 'doof-stdlib.tar') (Join-Path $dist 'doof-stdlib.tar') -Force\n" +
    "Compress-Archive -Path (Join-Path $dist '*') -DestinationPath (Join-Path $work '" + windowsReleaseArchiveName(version) + "') -Force\n"
}

export function windowsVisualStudioCommand(version: string): string {
  return "cmd.exe /d /c call \"%USERPROFILE%\\doof-release-" + version + "\\build.cmd\""
}

export function windowsVisualStudioScript(version: string): string {
  return "@echo off\n" +
    "setlocal\n" +
    "set \"WORK_ROOT=%USERPROFILE%\\doof-release-" + version + "\"\n" +
    "set \"VSWHERE=C:\\Program Files (x86)\\Microsoft Visual Studio\\Installer\\vswhere.exe\"\n" +
    "if exist \"%VSWHERE%\" for /f \"usebackq delims=\" %%V in (`\"%VSWHERE%\" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do call \"%%V\\Common7\\Tools\\VsDevCmd.bat\" -arch=x64\n" +
    "if not defined VSCMD_ARG_TGT_ARCH if exist \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\" call \"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\" -arch=x64\n" +
    "if not defined VSCMD_ARG_TGT_ARCH echo Could not locate a Visual Studio C++ x64 developer environment 1>&2 & exit /b 1\n" +
    "powershell.exe -NoProfile -NonInteractive -ExecutionPolicy Bypass -File \"%WORK_ROOT%\\build.ps1\"\n"
}
