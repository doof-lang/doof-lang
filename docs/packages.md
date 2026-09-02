# Packages

A Doof package is a directory containing `doof.json`. The compiler discovers
the package root from the requested source or directory.

```json
{
  "name": "hello",
  "version": "0.1.0",
  "build": {
    "entry": "main.do",
    "buildDir": "build"
  }
}
```

Source imports are relative (`./module`) or package-qualified (`std/fs`). Local
path dependencies are declared in `dependencies`; the compiler maps each local
package to a logical module prefix before source resolution. Doof performs no
remote package or third-party source acquisition.

Standard packages are a separate offline provider boundary. A global
`DOOF_STDLIB_ROOT` checkout takes precedence when present; otherwise the
compiler lazily materializes each reached package from its adjacent
`doof-stdlib.tar`. Its index is authoritative for package availability, and its
content digest participates in frontend cache configuration. Standard packages
may declare bounded `build.stdlib.prepare` commands for target preparation;
ordinary packages cannot.

The preparation hook is an array of bounded command objects:

```json
{
  "build": {
    "stdlib": {
      "prepare": [{
        "program": "./prepare.sh",
        "args": ["{packageRoot}/vendor", "{targetTriple}"],
        "env": { "SDK_PATH": "{sdkPath}" },
        "workingDirectory": "."
      }]
    }
  }
}
```

Preparation supports `{packageRoot}`, `{jobs}`, `{nativeTarget}`, `{sdkPath}`,
`{targetTriple}`, and `{configureHost}` substitutions. The program and working
directory must remain inside the standard package. Hooks run only for reached
standard packages when a command materializes native output; they do not run
for `check` or test listing. The scripts own their idempotence and freshness.

`resources` copies explicit package files beside a command-line executable or
into an application bundle. `build.native` declares include paths, source
files, libraries, frameworks, pkg-config packages, compiler/linker flags, and
platform-specific fragments. Paths remain package-root relative.

Normal builds use the debug build graph. `package` uses an independent release
graph and writes final artifacts to `dist/` unless overridden. Native release
builds optimize with link-time optimization (for non-Swift native builds) and
place functions/data in discardable sections; linking removes unreachable
sections, debug information, and nonessential symbols.
Manifest compiler and linker flags follow these defaults and can refine the
package build. Packaging does not emit dependency provenance.

macOS and iOS application settings live under `build.macosApp`, `build.iosApp`,
and `build.package`. WebAssembly packages set `target` to `wasm`; exported entry
functions become JSON-over-C-ABI wrappers.
