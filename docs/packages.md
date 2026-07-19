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
and exact remote dependencies are declared in `dependencies`; the compiler
maps each acquired package to a logical module prefix before source resolution.
Root resolutions and dependency policy constrain transitive package/native
inputs.

`resources` copies explicit package files beside a command-line executable or
into an application bundle. `build.native` declares include paths, source
files, libraries, frameworks, pkg-config packages, compiler/linker flags, and
platform-specific fragments. Paths remain package-root relative.

Normal builds use the debug build graph. `package` uses an independent release
graph and writes final artifacts to `dist/` unless overridden. Packaging emits
provenance identifying exact and mutable package/native inputs.

macOS and iOS application settings live under `build.macosApp`, `build.iosApp`,
and `build.package`. WebAssembly packages set `target` to `wasm`; exported entry
functions become JSON-over-C-ABI wrappers.

