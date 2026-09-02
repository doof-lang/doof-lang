# Bootstrap and Release

The repository is bootstrapped from a reviewed generated-C++ snapshot rather
than another compiler implementation or a committed executable.

`./build.sh` selects the macOS or Linux stage-0 driver from the host and then
performs three compiler generations:

1. The host C++ toolchain compiles `bootstrap/macos-arm64/generated/` into
   stage 0. Apple Clang is the supported path; the Linux driver is experimental.
2. Stage 0 compiles the current Doof sources into B5.
3. B5 compiles the same graph into B6.

The gate compares every generated C/C++/Objective-C++ header and source from B5
and B6 byte-for-byte. After a match, B6 regenerates the deterministic
`doof-stdlib.tar`, packages the same compiler sources with the optimized release
graph, and publishes that executable and its explicit resources to `dist/`.
B5 and B6 remain ordinary development builds because the fixed-point decision
concerns their generated source, not their native flags.

Bootstrap snapshots are source-only and must not contain binaries, objects,
PCH files, build databases, absolute developer paths, or emitted C++ `#line`
directives. Refresh them only from a verified Doof compiler using the final
repository layout, then run the complete release gate and review the generated
diff.

Run `./scripts/refresh-bootstrap.sh` to perform that workflow. It advances
compiler generations until two adjacent generated source graphs match, runs
release verification before changing the trust root, preserves reviewed
Windows and Linux native alternatives that are not emitted by a macOS build,
updates the source-only snapshot, and reruns the complete release gate from the
refreshed stage 0. If the final gate fails, it restores the original snapshot.
Before updating the trust root, the refresh canonicalizes all candidate source
files by removing generated `#line` directives. Ordinary compiler output keeps
those mappings for diagnostics and profiling, while source-line-only edits do
not create unrelated churn in the reviewed bootstrap snapshot.
Set `DOOF_REFRESH_MAX_GENERATIONS` to change the default six-generation
convergence limit.

When a compiler change uses a new self-hosted language/runtime surface that the
checked-in snapshot cannot compile yet, set `DOOF_REFRESH_SEED_COMPILER` to a
candidate compiler. The refresh still requires two consecutive generated
source graphs to match, verifies that fixed-point compiler before changing the
snapshot, and reruns the complete gate from the refreshed stage 0. The seed is
therefore a transition input, never the refreshed trust root by itself.

Before advancing compiler generations, the refresh builds and validates the
stdlib bundle. Missing prepared vendor inputs or required licenses fail before
the expensive fixed-point work.

`./scripts/release.sh` invokes `./build.sh --release`. It adds compiler coverage and
CLI/native/resource/package fixtures, bundled offline standard-library, WebP,
and target-native HTTP acceptance, plus macOS framework and iOS simulator checks. Ordinary
`./build.sh` produces an unverified but content-addressed development bundle so
local stdlib work remains usable. Release artifacts and all mutable state
remain below ignored `build/` and `dist/`.

The outer archive is an uncompressed seekable tar whose package manifests,
individual modules, and package-native trees are independent `tar.zst`
members. Its authoritative index records package names, member hashes, bundle
identity, and mandatory vendored license paths. Curation intentionally removes
obvious project-only and generated build state without attempting source-level
dependency closure. In particular, the image package retains libwebp's complete
`dsp`, `enc`, `dec`, `utils`, `webp`, and `sharpyuv` trees and omits only the
independent `demux` and `mux` components. The authenticated bundle index also
records the release's supported native targets. Apple and Windows bundles omit
vendored curl because those HTTP backends use URLSession and WinHTTP; Linux
bundles retain curl for the Linux HTTP backend.

On macOS, the release gate also compiles and runs the Wasm test fixtures. The
host therefore needs `em++` and `xcrun swiftc`. Emscripten writes cache entries
and lock files inside its installation cache; for a Homebrew installation this
is normally below
`/opt/homebrew/Cellar/emscripten/<version>/libexec/cache`. Sandboxed automation
must be granted write access to that external toolchain cache before starting
`./scripts/release.sh` or `./scripts/refresh-bootstrap.sh`. Without it, the
native portions of the gate may finish before the Wasm link fails with a
`PermissionError` while creating a `symbol_lists/*.json.lock` file.

Supported clean-bootstrap hosts are macOS arm64 with Xcode Command Line Tools
and Windows x64 with the MSVC C++ workload. `DOOF_STDLIB_ROOT` or adjacent
`../doof-stdlib` package checkouts are currently required when rebuilding or
testing source. Windows stage 0 is compiled with
`scripts/bootstrap-compiler.ps1`; B5 and B6 then use the compiler's native
MSVC build plan from an x64 developer environment. Both paths create their
MSVC runtime/Windows precompiled header below the ignored build directory; the
reviewed bootstrap snapshot remains source-only.

`./scripts/bootstrap-compiler-linux.sh` is an experimental portability path
for the checked-in stage-0 source graph. It selects neutral and `_linux`
sources and builds a Linux stage-0 compiler, but it does not run B5/B6,
publish an artifact, or add Linux to the supported clean-bootstrap hosts. A
snapshot containing the curl HTTP backend also requires `pkg-config` and the
host libcurl development package.

## Cross-platform snapshot

The bootstrap trust root is one target-independent generated source graph. Host
build scripts select the native source files, system frameworks/libraries, and
compiler flags for their target; they must not maintain divergent generated
compiler implementations. Platform-neutral native headers use guarded host
implementations where practical, while sources that require a platform language
or SDK (for example Objective-C++ HTTP support) live beside their alternatives
and are selected by the host build.

The shared snapshot remains at the legacy `bootstrap/macos-arm64/generated/`
path while Windows bootstrap orchestration is completed. Build scripts should prefer
`bootstrap/generated/` when that directory exists, so moving the reviewed tree
does not require another build-policy change. A supported host must compile and
smoke-test this same snapshot in addition to the B5/B6 source fixed-point gate.

Target-specific native source filenames end in `_windows`, `_apple`, `_macos`,
`_ios`, or `_linux` before the language extension. Bootstrap drivers compile
neutral sources plus only the suffixes valid for their host. Their
`--list-sources`/`-ListSources` modes expose the selected graph without invoking
the native compiler, so a snapshot refresh can verify that host alternatives do
not leak into one another.

## Development self-install

Run `./install.sh` for a fast, unverified development self-install. The script
uses `DOOF_DEV_COMPILER` when set, otherwise `doof` from `PATH`, with
`dist/doof` as a final fallback. That seed compiler runs an incremental
optimized package build in `build/dev-install/`, then rebuilds the stdlib
bundle from `DOOF_STDLIB_ROOT` or the adjacent `../doof-stdlib` checkout. It
does not compile the bootstrap snapshot, compare B5/B6, or run tests.

The resulting compiler and its adjacent resources are staged and installed as
one version under `~/.doof/versions/dev`. `~/.doof/current` selects that
version, while relative links in `~/.doof/bin` expose the compiler and
resources. The resource links are required because macOS console executables
resolve packaged resources from the launch directory even when the executable
is itself a symlink. Add the stable bin directory to the front of `PATH`:

```sh
export PATH="$HOME/.doof/bin:$PATH"
```

Set `DOOF_HOME` to override the home directory with another absolute path.
Empty or relative roots and `/` are rejected, as are directories at managed
link paths. Reinstalling replaces only the `dev` version and preserves other
versions and package caches. The installer does not edit shell profiles or use
`sudo`.

Run `./build.sh` plus `./scripts/test.sh`, or the complete
`./scripts/release.sh`, when fixed-point or release-grade verification is
required. Once release archives are published, the public installer can put a
selected downloaded release in `versions/<version>` and switch `current`
without changing this layout.
