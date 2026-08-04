# Compiler CLI

The compiler accepts a source file or a package directory. Package commands
discover the nearest `doof.json` and use `build.entry` when present.
An explicit `.do` file overrides that entry. Without a `doof.json`, source
commands require an explicit `.do` file; directory/default discovery is not
available.

```text
doof check <path>
doof emit <path> [-o <directory>]
doof build <path> [-o <directory>]
doof run <path> [build options] [-- program arguments]
doof package <path> [-o <build-directory>] [--distdir <directory>]
doof test <path> [filter] [--list] [--coverage]
```

`check` parses, resolves, analyzes, and type-checks the reached source graph.
`emit` also writes split C++ headers/sources and required runtime/native inputs.
`build` compiles and links those inputs. `run` builds and launches the result
from its package root. `package` creates an optimized release artifact and
records provenance. `test` discovers and runs exported test functions.

Native Windows builds use MSVC by default. Run the compiler from an MSVC x64
developer environment, or pass an explicit compiler with `--compiler`/`CXX`.
The MSVC plan uses `cl.exe`, `.obj` files, `/sourceDependencies` JSON for
incremental invalidation, and `link.exe`; Windows executable outputs receive
the `.exe` suffix. GCC-compatible compiler planning remains available when an
explicit non-MSVC compiler is selected.

For `check`, `emit`, `build`, and `run`, successful exact source/configuration
fingerprints are cached below `<build-directory>/.doof-cache/v1/`. Exact hits
skip the frontend. After an edit, Doof performs a normal semantic compilation
and retains any generated module whose transitive inputs and lowering plan are
unchanged. Retained generated files keep their timestamps so the native object
and dependency cache can reuse them. Removing the build directory clears both
caches. Native dependency validation uses persisted size and nanosecond
modification metadata on the unchanged hot path and falls back to content
fingerprints after metadata changes. Executable resources have a separate
materialization record: unchanged files are not reread, while edits, additions,
removals, and changes to copied outputs are synchronized before launch. Cache
corruption or incompatibility is treated as a miss.

Manifestless WebAssembly libraries use an explicit source and target:

```text
doof build library.do --target wasm
```

Their entry modules remain declarative libraries: exported functions use the
JSON ABI, while native script statements and `arguments` are unavailable.

The compiler supports native executables, macOS applications, iOS simulator
and device applications, and WebAssembly libraries. Platform signing and target
options are read from `doof.json`; command-line overrides take precedence.

Every command honors `DOOF_STDLIB_ROOT` as an explicit mutable standard-library
checkout. The override is required for compiler development until clean remote
standard-package acquisition is part of the supported bootstrap contract.
