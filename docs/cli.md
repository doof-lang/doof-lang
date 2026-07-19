# Compiler CLI

The compiler accepts a source file or a package directory. Package commands
discover the nearest `doof.json` and use `build.entry` when present.

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

The compiler supports native executables, macOS applications, iOS simulator
and device applications, and WebAssembly libraries. Platform signing and target
options are read from `doof.json`; command-line overrides take precedence.

Every command honors `DOOF_STDLIB_ROOT` as an explicit mutable standard-library
checkout. The override is required for compiler development until clean remote
standard-package acquisition is part of the supported bootstrap contract.

