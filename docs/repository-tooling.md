# Repository tooling

Repository automation is Doof under `tools/repository/`. It invokes native
programs where those programs own the operation: rsync, Git, Apple toolchains,
archive utilities, Apple Container, code signing and notarization. It does not embed shell or
Python implementations of build policy.

## Non-Doof entry points

| Entry | Why it exists |
| --- | --- |
| `install.sh` | Must run before Doof is installed; standalone macOS/Linux HTTPS installer and the shared artifact transaction. |
| `tools/run.sh` | Resolves an installed seed and launches the Doof repository tool. No build/release policy. |
| `dev-install.sh`, `build.sh` | Thin entry points for development installation and fixed-point verification. |
| `scripts/test.sh`, `scripts/release.sh` | Thin entry points for normal tests and explicit-version releases. |
| `tools/repository/source-build.sh.in` | Source-archive entry point must build without an installed Doof. Native command replay scripts are generated from captured builds. |
| VS Code/LSP/Wasm-runtime TypeScript tests | Exercise JavaScript runtime APIs directly; build, service packaging, artifact verification, and native CLI checks are Doof. |

The generated native compiler capture shims contain only `exec` into the Doof
capture command. Shell programs inside test fixtures simulate external programs
or supply file-descriptor redirection; assertions and sequencing are Doof.

## Commands

Use `tools/run.sh test`, `verify`, `debugger-test`, `process-test`, `corpus-test`, `preflight`,
`snapshot-test` (after `build.sh`), or
`cache-test <old-stamped-compiler> <new-stamped-compiler>` for the corresponding
repository checks. `verify` is the full platform acceptance gate without signing
or publishing; `linux-test <version>` builds the static arm64 and x64 musl
artifacts in Apple Container; `windows-test <version>` runs the optional remote
MSVC build; `release <version>` also enforces clean inputs and signing. The
`extension-build`, `extension-service`, `extension-verify`, and
`extension-native` commands back the VS Code extension's npm scripts.

Superseded shell, Python, and TypeScript build scripts have been removed; their
replacements are the Doof modules in `tools/repository/` (`build.do`,
`snapshot.do`, `verify.do`, `process-checks.do`, `extension.do`, and peers).
Remove obsolete tools rather than keeping compatibility wrappers.
