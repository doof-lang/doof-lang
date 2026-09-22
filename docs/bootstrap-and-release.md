# Versioned builds and releases

The compiler is maintained exclusively as Doof sources. Generated C++ is no
longer checked into this repository. It is distributed as a release-owned,
standalone source snapshot alongside macOS arm64 and Linux arm64/x64 musl
binary toolchains.

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
./scripts/release.sh 0.2.0
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
before expensive compilation. Xcode tools, Apple Container with its system
service running, `em++`, and `xcrun swiftc` are required. Sandboxed runs need
access to Emscripten's external cache, normally
under `/opt/homebrew/Cellar/emscripten/.../libexec/cache`.

The command accepts a stable `MAJOR.MINOR.PATCH` version, requires clean compiler
and stdlib checkouts, records their revisions, and refuses existing local assets
or a published GitHub release with that version. The requested version is
written only into the staged inputs and stays constant across generations.
The checkout manifest remains the base version for subsequent development.

### Optional Windows release verification

The release command can also build the staged compiler on a Windows x64 machine
with Visual Studio Community installed. Set the SSH host, username, and password
before running the release:

~~~sh
export DOOF_WINDOWS_HOST='windows-host-or-address'
export DOOF_WINDOWS_HOST_USERNAME='build-user'
export DOOF_WINDOWS_HOST_PASSWORD='password-from-your-secret-store'
~~~

SSH host-key verification uses ~/.ssh/known_hosts; set
`DOOF_WINDOWS_HOST_KNOWN_HOSTS` when the release runner uses another file.
Credentials are passed directly to the SSH client and are not written to
release metadata or command output.

Wake-on-LAN is optional. To wake the machine before SSH, set both values:

~~~sh
export DOOF_WINDOWS_HOST_MAC='aa:bb:cc:dd:ee:ff'
export DOOF_WINDOWS_HOST_BROADCAST='192.168.1.255'
~~~

When either Wake-on-LAN value is absent, the release skips the wake packet and
waits for SSH connectivity. The release uploads the stamped source and stdlib
inputs over SFTP, invokes the build from the Visual Studio x64 developer
environment, verifies the resulting compiler version, downloads
`doof-<version>-windows-x64.zip`, and includes it in `SHA256SUMS`. The remote
build is driven from those staged inputs rather than a mutable checkout.

For a non-publishing end-to-end check of the current checkout, use:

~~~sh
./tools/run.sh windows-test 0.2.0
~~~

This uses the same remote workflow and writes the downloaded test archive below
build/windows-e2e/; it does not sign, notarize, or publish release assets.

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

### Linux musl release verification

Every release emits the staged compiler for Linux, generates an explicit
Makefile for that closed source graph, and bind-mounts only the release work
area into arm64 and amd64 Alpine VMs run by Apple Container. The amd64 VM runs
under Rosetta. Alpine supplies GCC, musl, and Linux headers; neither VM receives
a compiler or stdlib checkout. Each build links a static ELF executable, checks
its architecture, embedded version, and file type, then uses that compiler and
its adjacent stdlib bundle to compile and run a smoke program before creating
the deterministic release archive.

The default image is `docker.io/library/alpine:3.22.1`. Override it with
`DOOF_LINUX_CONTAINER_IMAGE`. The build VM defaults to 8 CPUs, 8 GB of memory,
and four compiler jobs; `DOOF_LINUX_CONTAINER_CPUS`,
`DOOF_LINUX_CONTAINER_MEMORY`, and `DOOF_LINUX_BUILD_JOBS` override those
values. The image name, Apple Container version, and per-architecture
Alpine/GCC/musl versions are recorded in `release.json`.

For a non-publishing end-to-end check of the current checkout, use:

~~~sh
container system start
./tools/run.sh linux-test 0.2.0
~~~

The verified archive is written below `build/linux-e2e/<version>/pending/`.

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
- `doof-<version>-linux-arm64-musl.tar.gz`: static arm64 musl compiler, runtime
  header, Wasm host source, and Linux-capable stdlib archive.
- `doof-<version>-linux-x64-musl.tar.gz`: static x86-64 musl compiler, runtime
  header, Wasm host source, and Linux-capable stdlib archive.
- `doof-<version>-windows-x64.zip`: present when the optional Windows release
  verification is configured.
- `doof-<version>-source.tar.gz`: generated compiler/debugger sources, native
  sources/headers, license material, resources, and standalone build scripts.
- `release.json`: version, input revisions, seed version, toolchain details,
  fixed-point generation, notarization submission, and completed verification.
- `SHA256SUMS`: SHA-256 checksums for every archive and release metadata.

The source archive builds on macOS arm64 with Xcode Command Line Tools using
`./build.sh`, writing an ad-hoc signed local toolchain to `dist/`. It contains
no binaries, PCHs, object files, build databases, developer paths, or generated
`#line` directives. The bundled stdlib retains its indexed licenses and
content-addressed package resources. Other compiler target backends remain
maintained, but no other host release archive is promised yet.

## Publication and installation

The script creates no tags and uploads nothing to GitHub. Manually create tag
`v<version>` at the compiler revision in `release.json`, create a release in
`doof-lang/doof-lang`, and upload all listed assets before publishing it as the
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
