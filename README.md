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

The published compiler includes `dist/doof-stdlib.tar`. With
`DOOF_STDLIB_ROOT` unset, standard imports are resolved offline from that
adjacent bundle and reached packages are materialized lazily. Setting the
environment variable remains the global mutable override used for compiler and
stdlib development.

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
./install.sh                       # quickly package and install a development compiler
```

`./install.sh` is the supported incremental development workflow. It uses an
existing `doof` compiler to incrementally package the current compiler sources,
rebuild the adjacent standard-library bundle, and install the result under
`~/.doof/versions/dev`. Stable links in `~/.doof/bin` point through
`~/.doof/current`, so put that bin directory at the front of `PATH`:

```sh
export PATH="$HOME/.doof/bin:$PATH"
```

Do not use `./build.sh` as an incremental edit-test loop: it intentionally
rebuilds the bootstrap chain and verifies the B5/B6 fixed point. The development
installer deliberately skips those release-oriented checks and the compiler
test suite. Use `./build.sh`, `./scripts/test.sh`, or `./scripts/release.sh` once
their respective gates are required.
Set `DOOF_DEV_COMPILER` to select the seed compiler, `DOOF_STDLIB_ROOT` to use a
non-adjacent stdlib checkout, or `DOOF_HOME` to choose another absolute install
root. The installer never edits shell startup files and does not require
`sudo`.

The Linux stage-0 driver selects neutral and `_linux` sources from the shared
bootstrap graph. It is an experimental portability path, not yet a supported
clean-bootstrap host or part of the release gate. On Ubuntu, install a C++17
toolchain and `pkg-config` before building.

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
