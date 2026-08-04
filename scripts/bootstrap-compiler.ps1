[CmdletBinding()]
param(
    [ValidateSet("x64", "arm64")]
    [string]$Architecture = "x64",

    [switch]$DeveloperEnvironmentReady,

    [switch]$ListSources
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

function Find-VSWhere {
    $candidates = @(
        (Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"),
        (Join-Path $env:ProgramFiles "Microsoft Visual Studio\Installer\vswhere.exe")
    )
    foreach ($candidate in $candidates) {
        if (Test-Path -LiteralPath $candidate -PathType Leaf) { return $candidate }
    }
    throw "Could not find vswhere.exe. Install Build Tools for Visual Studio with the Desktop development with C++ workload."
}

function Enter-MSVCDeveloperEnvironment {
    if (Get-Command cl.exe -ErrorAction SilentlyContinue) { return }
    if ($DeveloperEnvironmentReady) {
        throw "VsDevCmd.bat completed, but cl.exe is unavailable. Add the MSVC x64/x86 build tools and a Windows SDK in Visual Studio Installer."
    }

    $vswhere = Find-VSWhere
    $installationPath = & $vswhere -latest -products * `
        -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
        -property installationPath
    if ($LASTEXITCODE -ne 0 -or [string]::IsNullOrWhiteSpace($installationPath)) {
        throw "No Visual Studio Build Tools installation with the MSVC x64/x86 component was found."
    }

    $devCommand = Join-Path $installationPath.Trim() "Common7\Tools\VsDevCmd.bat"
    if (-not (Test-Path -LiteralPath $devCommand -PathType Leaf)) {
        throw "Visual Studio developer environment script was not found at: $devCommand"
    }

    $powershell = (Get-Process -Id $PID).Path
    $commandLine = ('call "{0}" -no_logo -arch={1} -host_arch=x64 && "{2}" -NoProfile -ExecutionPolicy Bypass -File "{3}" -Architecture {1} -DeveloperEnvironmentReady' -f `
        $devCommand, $Architecture, $powershell, $PSCommandPath)
    & $env:ComSpec /d /s /c $commandLine
    exit $LASTEXITCODE
}

function Write-ResponseFile {
    param(
        [Parameter(Mandatory)] [string]$Path,
        [Parameter(Mandatory)] [string[]]$Values
    )
    $quoted = foreach ($value in $Values) { '"' + $value.Replace('"', '\"') + '"' }
    [System.IO.File]::WriteAllLines($Path, $quoted, [System.Text.Encoding]::ASCII)
}

if (-not $ListSources) {
    Enter-MSVCDeveloperEnvironment
}

$repoRoot = Split-Path -Parent $PSScriptRoot
$universalSnapshotRoot = Join-Path $repoRoot "bootstrap\generated"
$legacySnapshotRoot = Join-Path $repoRoot "bootstrap\macos-arm64\generated"
$snapshotRoot = if (Test-Path -LiteralPath $universalSnapshotRoot -PathType Container) {
    $universalSnapshotRoot
} else {
    $legacySnapshotRoot
}
$outputRoot = Join-Path $repoRoot "build\bootstrap-stage0-windows-$Architecture"
$objectRoot = Join-Path $outputRoot "objects"
$sourceResponse = Join-Path $outputRoot "msvc-sources.rsp"
$objectResponse = Join-Path $outputRoot "msvc-objects.rsp"
$executable = Join-Path $outputRoot "doof.exe"

if (-not (Test-Path -LiteralPath $snapshotRoot -PathType Container)) {
    throw "Missing bootstrap snapshot: $snapshotRoot"
}

Write-Host "  Discovering bootstrap headers and sources..."
$sources = @(Get-ChildItem -LiteralPath $snapshotRoot -Recurse -File |
    Where-Object {
        $_.Extension -in ".c", ".cc", ".cpp" -and
        $_.BaseName -notmatch "_(apple|macos|ios|linux)$"
    } |
    Sort-Object FullName)
$objectiveCSources = @(Get-ChildItem -LiteralPath $snapshotRoot -Recurse -File |
    Where-Object { $_.Extension -in ".m", ".mm" } |
    Sort-Object FullName)
$includeDirectories = @(Get-ChildItem -LiteralPath $snapshotRoot -Recurse -File |
    Where-Object { $_.Extension -in ".h", ".hh", ".hpp" } |
    ForEach-Object { $_.Directory.FullName } |
    Sort-Object -Unique)

if ($sources.Count -eq 0) { throw "Bootstrap snapshot contains no C or C++ sources." }

if ($ListSources) {
    foreach ($source in $sources) {
        $source.FullName.Substring($snapshotRoot.Length + 1).Replace("\", "/")
    }
    exit 0
}

if (Test-Path -LiteralPath $outputRoot) {
    Remove-Item -LiteralPath $outputRoot -Recurse -Force
}
New-Item -ItemType Directory -Path $objectRoot -Force | Out-Null

$duplicateBasenames = @($sources | Group-Object BaseName | Where-Object Count -gt 1)
if ($duplicateBasenames.Count -ne 0) {
    $names = ($duplicateBasenames | ForEach-Object Name) -join ", "
    throw "MSVC's multi-source object directory would contain duplicate object names: $names"
}

if ($objectiveCSources.Count -ne 0) {
    Write-Host ("  Skipping {0} target-specific Objective-C/Objective-C++ source(s)." -f $objectiveCSources.Count)
}

Write-ResponseFile -Path $sourceResponse -Values @($sources.FullName)

$compileArguments = @(
    "/nologo",
    "/std:c++17",
    "/O2",
    "/DNDEBUG",
    "/EHsc",
    "/utf-8",
    "/Zc:__cplusplus",
    "/permissive-",
    "/MP",
    "/FS"
)
foreach ($directory in $includeDirectories) { $compileArguments += "/I$directory" }
$compileArguments += "/c"
$compileArguments += "@$sourceResponse"
$compileArguments += "/Fo$objectRoot\"

Write-Host "  Compiling $($sources.Count) generated source files with MSVC..."
& cl.exe @compileArguments
if ($LASTEXITCODE -ne 0) {
    throw "MSVC bootstrap compilation failed with exit code $LASTEXITCODE. The macOS snapshot may still contain platform-specific native support."
}

$objects = @(Get-ChildItem -LiteralPath $objectRoot -File -Filter "*.obj" | Sort-Object FullName)
if ($objects.Count -ne $sources.Count) {
    throw "Bootstrap compilation produced $($objects.Count) of $($sources.Count) expected objects."
}
Write-ResponseFile -Path $objectResponse -Values @($objects.FullName)

Write-Host "  Linking $($objects.Count) bootstrap objects..."
& link.exe /nologo "/OUT:$executable" /SUBSYSTEM:CONSOLE "@$objectResponse"
if ($LASTEXITCODE -ne 0) { throw "MSVC bootstrap link failed with exit code $LASTEXITCODE." }

Copy-Item -LiteralPath (Join-Path $repoRoot "runtime\doof_runtime.h") -Destination $outputRoot
Copy-Item -LiteralPath (Join-Path $repoRoot "resources\std-catalog.json") -Destination $outputRoot

Write-Host "  Windows stage-0 compiler is ready: $executable"
