# Doof

Doof is a statically typed language with familiar curly-brace syntax that
compiles to native C++17. This repository contains the official compiler,
written in Doof itself.

> [!CAUTION]
> Doof is experimental and largely AI generated. It is not recommended for
> production use.

## Requirements

The bootstrap supports Apple Silicon macOS with Xcode Command Line Tools and
Windows x64 with the MSVC C++ workload. Provide the Doof standard-library
package checkouts through either `DOOF_STDLIB_ROOT` or an adjacent
`../doof-stdlib` directory.

```sh
export DOOF_STDLIB_ROOT=/path/to/doof-stdlib
./build.sh
```

On Windows, run `scripts/bootstrap-compiler.ps1` and subsequent `doof build`
commands from an MSVC x64 developer environment. Native builds default to
`cl.exe` and `link.exe` and produce `.exe` outputs.

On macOS and Linux, the build selects the host stage-0 driver, compiles the
checked-in generated C++ snapshot, rebuilds the compiler twice, compares the
B5 and B6 generated sources byte-for-byte, and publishes the verified compiler
as `dist/doof`. Stage-0 sources compile in parallel using the available CPU
count; set `DOOF_BUILD_JOBS` to a positive integer to override the number of
compiler jobs. The Linux path remains experimental until its shared snapshot
and release gate are verified on a clean host.

## Compiler commands

```sh
dist/doof check path/to/package
dist/doof emit path/to/package
dist/doof build path/to/package
dist/doof run path/to/package -- --program-argument
dist/doof profile path/to/package -- --program-argument
dist/doof package path/to/package
dist/doof test path/to/package
```

POSIX scripts can place `#!/usr/bin/env doof` at the start of an executable
`.do` file. Invoking `./script.do arg` is equivalent to direct script mode,
`doof script.do arg`, and forwards trailing arguments to the program. See
[CLI](docs/cli.md) for details.

Each package is described by a `doof.json`. See [CLI](docs/cli.md),
[packages](docs/packages.md), and [testing](docs/testing.md) for the supported
contracts.

## Repository commands

```sh
./build.sh                         # bootstrap and fixed-point verification
./scripts/refresh-bootstrap.sh     # regenerate and verify the bootstrap snapshot
./scripts/test.sh                  # compiler unit/component tests
./scripts/bootstrap-compiler-linux.sh # experimental Linux stage-0 compile
./scripts/release.sh               # full release acceptance gate
./scripts/update-std-catalog.sh    # regenerate the exact std package catalog
./install.sh                       # build, test, and sudo-install the compiler
```

`./install.sh` is the development self-install workflow. It completes the
verified fixed-point build and compiler tests before requesting `sudo`, then
installs the compiler bundle under `/usr/local/libexec/doof` and exposes it as
`/usr/local/bin/doof`. Relative resource symlinks in `/usr/local/bin` support
the macOS console-executable resource lookup while keeping the canonical files
in the bundle. Use `./install.sh --prefix /absolute/path` to select a different
prefix. Existing compiler files or symlinks are replaced; an existing
directory at any managed path is left untouched and reported as an error.

The Linux stage-0 driver selects neutral and `_linux` sources from the shared
bootstrap graph. It is an experimental portability path, not yet a supported
clean-bootstrap host or part of the release gate. On Ubuntu, install a C++17
toolchain, `pkg-config`, and the libcurl development package before building.

Language behavior is defined by the [language specification](spec/01-overview.md).
Compiler contributors should start with the [documentation map](docs/README.md),
then use [source structure](docs/source-structure.md) for vertical file
ownership or [compiler architecture](docs/compiler-architecture.md) for
horizontal concepts spanning phases. Current operational and compatibility
limitations are tracked in [ROADMAP.md](ROADMAP.md).

## Source layout

- `src/` — compiler, CLI, native build drivers, and adjacent Doof tests
- `docs/` — contributor maps, operational contracts, and lowering notes
- `runtime/` — canonical generated-program runtime header
- `resources/` — immutable resources embedded in compiler releases
- `bootstrap/macos-arm64/` — trusted generated-C++ stage-0 source snapshot (legacy location for the shared cross-platform graph)
- `tests/release-fixtures/` — native and platform release acceptance packages
- `.github/skills/doof-language/` — Codex/Copilot language guidance

## License

ISC. See [LICENSE](LICENSE).
