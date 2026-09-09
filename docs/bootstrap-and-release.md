# Versioned builds and releases

The compiler is maintained exclusively as Doof sources. Generated C++ is no
longer checked into this repository. It is distributed as a release-owned,
standalone source snapshot alongside the macOS arm64 binary toolchain.

## Development and fixed points

`./dev-install.sh` uses `DOOF_DEV_COMPILER`, installed `doof`, or `dist/doof`, in
that order. It copies compiler/runtime and prepared stdlib inputs to ignored
`build/dev-install/`, preserving timestamps for incremental compilation. Repository tooling is written in Doof; rsync performs source staging. The stdlib comes from
`DOOF_STDLIB_ROOT` or adjacent `../doof-stdlib`.

Each invocation stamps `<manifest version>-dev.<UTC timestamp>.<UUID>` into the
staged compiler and package manifests. It builds an optimized compiler, its
bundled stdlib, and the debugger, then installs them under
`~/.doof/versions/dev`. It skips fixed-point and release acceptance checks.
An advisory lock prevents overlapping development, verification, and release
builds. Existing pre-staging native caches are migrated once.

`./build.sh` uses `DOOF_SEED_COMPILER` or the same installed/dist fallback and
builds successive generations from frozen, identically stamped inputs. Fresh
output directories prevent one generation from reusing another's frontend
cache. Two adjacent generated C/C++/Objective-C++ graphs must match byte for
byte; `DOOF_MAX_GENERATIONS` defaults to six and must be at least two. Failure
never publishes a compiler to `dist/`. A successful verification build packages
the compiler and resources there for testing. Neither script downloads a seed.

`doof --version` reports the embedded version. Stamped versions replace the
executable byte hash in compiler cache identity. Source, resource, stdlib,
option, semantic ABI, cache schema, and native toolchain fingerprints remain
in effect. Direct, unstamped source builds report `<base>-dev.unstamped` and
disable frontend cache reuse. Never reuse a published version for changed code.

## Preparing a release

```sh
export DOOF_STDLIB_ROOT=/absolute/path/to/doof-stdlib
export DOOF_SIGN_IDENTITY='Developer ID Application: Your Organization (TEAMID)'
export DOOF_NOTARY_PROFILE=doof-release
./scripts/release.sh 0.1.0
```

Provision the Developer ID Application certificate and its private key in the
build user's Keychain. Run `security find-identity -v -p codesigning` and copy
the exact `Developer ID Application: ...` name into `DOOF_SIGN_IDENTITY` (the
certificate's SHA-1 identity also works). `DEVELOPMENT_TEAM` alone is not a
signing identity, and an `Apple Development` certificate used by
`DOOF_IOS_SIGN_IDENTITY` does not qualify for macOS release distribution.
See [Apple's Developer ID certificate instructions](https://developer.apple.com/help/account/certificates/create-developer-id-certificates).

Store notarization credentials in a named profile with
`xcrun notarytool store-credentials doof-release`; credentials are never stored
in source or release metadata. The script checks the identity and profile
before expensive compilation. Xcode tools, `em++`, and `xcrun swiftc` are
required. Sandboxed runs need access to Emscripten's external cache, normally
under `/opt/homebrew/Cellar/emscripten/.../libexec/cache`.

The command accepts a stable `MAJOR.MINOR.PATCH` version, requires clean compiler
and stdlib checkouts, records their revisions, and refuses existing local assets
or a published GitHub release with that version. The requested version is
written only into the staged inputs and stays constant across generations.
The checkout manifest remains the base version for subsequent development.

The stdlib may be a single Git checkout or a workspace of separate `std/*`
package checkouts. In the latter layout, every standard package must be clean;
release metadata records a revision per package. Non-standard example projects
in that workspace are not release inputs.

The pipeline validates the stdlib bundle before compiler generations, converges,
packages the optimized compiler and debugger, and runs the compiler, tooling,
native, package, resource, Wasm, framework, iOS, and debugger gates. It captures
actual native compile/link invocations while building the final toolchain.
Source snapshot scripts replay those commands with relocated paths, without
relying on the repository, an installed Doof, Python, Node, or a stdlib checkout.
The snapshot is extracted at a different path, compiled, and smoke-tested.

Binary releases are Developer ID signed with hardened runtime and secure
timestamps. The debugger receives the debugger entitlement. The release ZIP is
submitted to Apple's notary service; acceptance is mandatory. The debugger app
is stapled and the final ZIP recreated before checksumming. The final archive
is extracted, quarantined, signature/Gatekeeper assessed, and tested again.
The CLI uses `codesign -R=notarized --check-notarization`; the debugger app uses
`spctl --assess --type execute`. Both are launched after quarantine is applied.
Failures leave diagnostics under `build/releases/<version>/` and no final assets.

Completed assets appear under `dist/releases/<version>/`:

- `doof-<version>-macos-arm64.zip`: compiler, runtime resources, stdlib archive,
  and `Doof Debugger.app`.
- `doof-<version>-source.tar.gz`: generated compiler/debugger sources, native
  sources/headers, license material, resources, and standalone build scripts.
- `release.json`: version, input revisions, seed version, toolchain details,
  fixed-point generation, notarization submission, and completed verification.
- `SHA256SUMS`: SHA-256 checksums for both archives and release metadata.

The source archive builds on macOS arm64 with Xcode Command Line Tools using
`./build.sh`, writing an ad-hoc signed local toolchain to `dist/`. It contains
no binaries, PCHs, object files, build databases, developer paths, or generated
`#line` directives. The bundled stdlib retains its indexed licenses and
content-addressed package resources. Other compiler target backends remain
maintained, but no other host release archive is promised yet.

## Publication and installation

The script creates no tags and uploads nothing to GitHub. Manually create tag
`v<version>` at the compiler revision in `release.json`, create a release in
`doof-lang/doof-lang`, and upload all four assets before publishing it as the
latest stable release. Versions and published asset contents are immutable.
Changing any released content requires a new version.

The root `install.sh` is self-contained for `curl | bash`. It resolves the latest
stable release once, or accepts `--version <version>`, downloads the matching
ZIP and checksum list, verifies the checksum, rejects unsafe archive entries,
checks embedded version/resources, and smoke-tests before installation.
Downloads use HTTPS. It rejects unsupported hosts rather than selecting an
incompatible archive or silently building from source.

The common artifact transaction stages under `~/.doof/versions/`, preserves
previous versions and package caches, and rolls back failed activation. Release
installs use `versions/<version>`; development installs replace `versions/dev`.
`current` selects the active toolchain and relative links in `bin` expose the
compiler and adjacent resources. Resource links matter on macOS because resource
lookup uses the launch directory even when the executable is a symlink.

Set `DOOF_HOME` to another absolute directory. The installers use no `sudo` and
do not edit shell profiles. Add the stable executable directory to PATH:

```sh
export PATH="$HOME/.doof/bin:$PATH"
```

A leftover `.install-lock` after an uncatchable process termination requires
checking that no installer is active before removing the empty lock directory.

See [repository tooling audit](repository-tooling.md) for removed scripts,
retained pre-Doof shell boundaries, and the Doof acceptance commands.
