# Compiler CLI

The compiler accepts a source file or a package directory. Package commands
discover the nearest `doof.json` and use `build.entry` when present.
An explicit `.do` file overrides that entry. Without a `doof.json`, source
commands require an explicit `.do` file; directory/default discovery is not
available.

```text
doof <script.do> [program arguments]
doof check <path>
doof emit <path> [-o <directory>]
doof build <path> [-o <directory>]
doof run <path> [build options] [-- program arguments]
doof package <path> [-o <build-directory>] [--distdir <directory>]
doof test <path> [filter] [--list] [--coverage]
```

## Executable scripts

On POSIX systems, a `.do` source file can be invoked directly with a shebang:

```doof
#!/usr/bin/env doof

function main(arguments: string[]): none {
    println(arguments.join(", "))
}
```

Make the file executable once with `chmod +x script.do`, then run it normally:

```text
./script.do one two
```

The direct `doof script.do ...` form runs the source and forwards every value
after the path verbatim to the program, including option-like values. Use the
explicit `doof run script.do [build options] -- [program arguments]` form when
compiler or build options are required. Windows accepts the same source file,
but does not natively launch files through POSIX shebangs.

`check` parses, resolves, analyzes, and type-checks the reached source graph.
`emit` also writes split C++ headers/sources and required runtime/native inputs.
`build` compiles and links those inputs. `run` builds and launches the result
from its package root. `package` creates an optimized release artifact and
records provenance. `test` discovers and runs exported test functions.

Successful compilation performed by `run` is silent: the launched program owns
its inherited standard input, output, and error streams without compiler
messages mixed into them. Warning-only source diagnostics and successful native
compiler or linker output are suppressed. If compilation fails and the program
cannot launch, Doof prints the captured diagnostics.

`build`, `test`, and `package` report native recompilation concisely. When native
source files are dirty they print `Compiling N files` followed by one dot per
successfully compiled source, grouped as worker batches finish. Exact native
cache hits print no compilation progress. Successful compiler and linker
chatter remains hidden; failed steps print their captured output. `emit` does
not invoke the native compiler and remains quiet except for source diagnostics.

Native Windows builds use MSVC by default. Run the compiler from an MSVC x64
developer environment, or pass an explicit compiler with `--compiler`/`CXX`.
The MSVC plan uses `cl.exe`, `.obj` files, `/sourceDependencies` JSON for
incremental invalidation, and `link.exe`; Windows executable outputs receive
the `.exe` suffix. Multi-module builds create a build-local precompiled header
containing the portable Doof runtime plus lean Windows SDK declarations, then
reuse it across generated modules. Manifest-native sources retain their own
language and include environments and do not consume this PCH. GCC-compatible
compiler planning remains available when an explicit non-MSVC compiler is
selected. Native object compilation uses at most four compiler workers by
default to avoid oversubscribing smaller development machines.

For `check`, `emit`, `build`, and `run`, successful exact source/configuration
fingerprints are cached below `<build-directory>/.doof-cache/v1/`. Exact hits
skip the frontend. After an edit, Doof performs a normal semantic compilation
and retains any generated module whose transitive inputs and lowering plan are
unchanged. Retained generated files keep their timestamps so the native object
and dependency cache can reuse them. Removing the build directory clears both
caches. Generated module sources include only their matching consumer-projected
header; that header directly contains the checked foreign declaration closure
rather than including other generated module headers. Native dependency
validation uses persisted size and nanosecond
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
