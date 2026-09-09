# Doof

Doof is a statically typed language with familiar curly-brace syntax that
compiles to native C++17. This repository contains the official compiler,
written in Doof itself.

> [!CAUTION]
> Doof is experimental and largely AI generated. It is not recommended for
> production use.

## Requirements

Install the latest macOS arm64 release (once published):

```sh
curl -fsSL https://raw.githubusercontent.com/doof-lang/doof-lang/main/install.sh | bash
export PATH="$HOME/.doof/bin:$PATH"
doof --version
```

Use `bash -s -- --version 0.1.0` to select a release. Releases include the
standard library and native debugger. Xcode Command Line Tools are required to
compile native Doof programs. No administrator privileges are required.

Compiler development requires an installed Doof compiler, rsync,
Xcode Command Line Tools, and the standard-library checkout at
`DOOF_STDLIB_ROOT` or adjacent `../doof-stdlib`. There is no checked-in generated
bootstrap. Each release also supplies a standalone source snapshot that builds
with Xcode Command Line Tools without an installed Doof compiler.

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
./dev-install.sh                   # incremental, uniquely versioned development install
./build.sh                         # installed-seed generated-source fixed-point verification
./scripts/test.sh                  # compiler, orchestration, installer, and debugger tests
./scripts/release.sh 0.1.0          # verified, signed assets for manual publication
```

Development installs use `~/.doof/versions/dev`, selected by `~/.doof/current`.
Release installs use `versions/<version>`. `DOOF_HOME` selects another absolute
installation root; neither installer edits shell profiles or uses `sudo`.
Set `DOOF_DEV_COMPILER` for a development seed or `DOOF_SEED_COMPILER` for
fixed-point/release builds. Both otherwise prefer installed `doof`, then
`dist/doof`. Build scripts never download a seed implicitly.

Release builds require clean compiler and stdlib checkouts, `em++`, `xcrun swiftc`,
`DOOF_SIGN_IDENTITY`, and `DOOF_NOTARY_PROFILE`. They stage the requested version
without changing tracked files, converge, verify, sign, notarize, and prepare
assets under `dist/releases/<version>`. See [release strategy](docs/bootstrap-and-release.md)
for credentials, source rebuilding, and manual GitHub publication.

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
- `scripts/` — version stamping, installed-seed builds, release verification and packaging
- `tests/release-fixtures/` — native and platform release acceptance packages
- `.github/skills/doof-language/` — Codex/Copilot language guidance

## License

ISC. See [LICENSE](LICENSE).
