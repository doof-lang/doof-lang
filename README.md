# Doof

Doof is a statically typed language with familiar curly-brace syntax that
compiles to native C++17. This repository contains the official compiler,
written in Doof itself.

> [!CAUTION]
> Doof is experimental and largely AI generated. It is not recommended for
> production use.

## Requirements

The initial bootstrap target is Apple Silicon macOS. Install Xcode Command
Line Tools and provide the Doof standard-library package checkouts through
either `DOOF_STDLIB_ROOT` or an adjacent `../doof-stdlib` directory.

```sh
export DOOF_STDLIB_ROOT=/path/to/doof-stdlib
./build.sh
```

The build compiles the checked-in generated C++ stage 0, rebuilds the compiler
twice, compares the B5 and B6 generated sources byte-for-byte, and publishes
the verified compiler as `dist/doof`. Stage-0 sources compile in parallel using
the available CPU count; set `DOOF_BUILD_JOBS` to a positive integer to override
the number of compiler jobs.

## Compiler commands

```sh
dist/doof check path/to/package
dist/doof emit path/to/package
dist/doof build path/to/package
dist/doof run path/to/package -- --program-argument
dist/doof package path/to/package
dist/doof test path/to/package
```

Each package is described by a `doof.json`. See [CLI](docs/cli.md),
[packages](docs/packages.md), and [testing](docs/testing.md) for the supported
contracts.

## Repository commands

```sh
./build.sh                         # bootstrap and fixed-point verification
./scripts/test.sh                  # compiler unit/component tests
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

Language behavior is defined by [spec/](spec/). Current operational and
compatibility limitations are tracked in [ROADMAP.md](ROADMAP.md).

## Source layout

- `src/` — compiler, CLI, native build drivers, and adjacent Doof tests
- `runtime/` — canonical generated-program runtime header
- `resources/` — immutable resources embedded in compiler releases
- `bootstrap/macos-arm64/` — trusted generated-C++ stage-0 source snapshot
- `tests/release-fixtures/` — native and platform release acceptance packages
- `.github/skills/doof-language/` — Codex/Copilot language guidance

## License

ISC. See [LICENSE](LICENSE).
