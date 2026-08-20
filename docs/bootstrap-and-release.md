# Bootstrap and Release

The repository is bootstrapped from a reviewed generated-C++ snapshot rather
than another compiler implementation or a committed executable.

`./build.sh` performs three compiler generations:

1. Apple Clang compiles `bootstrap/macos-arm64/generated/` into stage 0.
2. Stage 0 compiles the current Doof sources into B5.
3. B5 compiles the same graph into B6.

The gate compares every generated C/C++/Objective-C++ header and source from B5
and B6 byte-for-byte. After a match, B6 packages the same compiler sources with
the optimized release graph and publishes that executable and its explicit
resources to `dist/`. B5 and B6 remain ordinary development builds because the
fixed-point decision concerns their generated source, not their native flags.

Bootstrap snapshots are source-only and must not contain binaries, objects,
PCH files, build databases, or absolute developer paths. Refresh them only
from a verified Doof compiler using the final repository layout, then
run the complete release gate and review the generated diff.

Run `./scripts/refresh-bootstrap.sh` to perform that workflow. It advances
compiler generations until two adjacent generated source graphs match, runs
release verification before changing the trust root, preserves reviewed
Windows and Linux native alternatives that are not emitted by a macOS build,
updates the source-only snapshot, and reruns the complete release gate from the
refreshed stage 0. If the final gate fails, it restores the original snapshot.
Set `DOOF_REFRESH_MAX_GENERATIONS` to change the default six-generation
convergence limit.

When a compiler change uses a new self-hosted language/runtime surface that the
checked-in snapshot cannot compile yet, set `DOOF_REFRESH_SEED_COMPILER` to a
candidate compiler. The refresh still requires two consecutive generated
source graphs to match, verifies that fixed-point compiler before changing the
snapshot, and reruns the complete gate from the refreshed stage 0. The seed is
therefore a transition input, never the refreshed trust root by itself.

`./scripts/release.sh` adds compiler coverage and CLI/native/resource/package
fixtures, plus macOS framework and iOS simulator acceptance checks. Release
artifacts and all mutable state remain below ignored `build/` and `dist/`.

Supported clean-bootstrap hosts are macOS arm64 with Xcode Command Line Tools
and Windows x64 with the MSVC C++ workload. `DOOF_STDLIB_ROOT` or adjacent
`../doof-stdlib` package checkouts are currently required when rebuilding or
testing source. Windows stage 0 is compiled with
`scripts/bootstrap-compiler.ps1`; B5 and B6 then use the compiler's native
MSVC build plan from an x64 developer environment. Both paths create their
MSVC runtime/Windows precompiled header below the ignored build directory; the
reviewed bootstrap snapshot remains source-only.

`./scripts/test-bootstrap-alpine.sh` is an experimental portability gate for
the checked-in stage-0 source graph. It builds an Alpine image with Apple's
`container` CLI, mounts the repository read-only, selects neutral and `_linux`
sources, compiles and links them against musl in temporary container storage,
and smoke-tests the resulting compiler executable. It does not
run B5/B6, publish an artifact, or add Linux to the supported clean-bootstrap
hosts. `DOOF_ALPINE_VERSION` overrides the pinned Alpine base image for matrix
testing, and `DOOF_ALPINE_MEMORY` overrides the 4 GB container memory limit.

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

Run `./install.sh` to build through the B5/B6 fixed point, run the compiler
suite, and install the verified artifacts. No privileged command runs until
both verification steps pass. The default layout keeps `doof`,
`doof_runtime.h`, and `std-catalog.json` together in
`/usr/local/libexec/doof`, with `/usr/local/bin/doof` as a relative symlink to
the bundled executable. Relative links for both resources are also placed in
`/usr/local/bin`, because macOS console executables resolve packaged resources
from the launch directory even when the executable itself is a symlink.

An alternate absolute prefix can be supplied with
`./install.sh --prefix /opt/doof`. Empty and relative prefixes, and `/` itself,
are rejected before the build or privilege boundary. Installation replaces
existing compiler files and symlinks but refuses to replace a directory at any
managed destination.
