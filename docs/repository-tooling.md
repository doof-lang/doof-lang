# Repository tooling audit

Repository automation is Doof under `tools/repository/`. It invokes native
programs where those programs own the operation: rsync, Git, Apple toolchains,
archive utilities, code signing and notarization. It does not embed shell or
Python implementations of build policy.

## Retained entry points

| Entry | Why it exists |
| --- | --- |
| `install.sh` | Must run before Doof is installed; standalone HTTPS installer and the shared artifact transaction. |
| `tools/run.sh` | Resolves an installed seed and launches the Doof repository tool. No build/release policy. |
| `dev-install.sh`, `build.sh` | Thin compatibility entry points for development installation and fixed-point verification. |
| `scripts/test.sh`, `scripts/release.sh` | Thin compatibility entry points for normal tests and explicit-version releases. |
| `tools/repository/source-build.sh.in` | Source-archive entry point must build without an installed Doof. Native command replay scripts are generated from captured builds. |
| VS Code/LSP/Wasm-runtime TypeScript tests | Exercise JavaScript runtime APIs directly; build, service packaging, artifact verification, and native CLI checks have moved to Doof. |

The generated native compiler capture shims contain only `exec` into the Doof
capture command. Shell programs inside test fixtures simulate external programs
or supply file-descriptor redirection; assertions and sequencing are Doof.

## Removed or consolidated

| Previous tools | Replacement or reason for deletion |
| --- | --- |
| Platform bootstrap drivers, snapshot refresh, canonicalization and platform-source preservation | No tracked bootstrap; `build.do` verifies generations and `snapshot.do` creates release assets. |
| Generated-source comparison script | Whole-graph source comparison in `build.do`, including rejection of empty graphs. |
| Debugger build script | `buildDebugger` in `build.do`. |
| Release verification script | `verify.do`, with mandatory release prerequisites instead of silently skipped Wasm gates. |
| Runtime scheduler test script | `runtimeChecks` in `verify.do`; native C++ runtime test remains a C++ test of the C++ runtime. |
| Command-output, interactive-run, frontend-cache and project-build-lock scripts | `process-checks.do` and focused test coverage; PTYs are supplied by the native `script` utility. |
| Debugger test script | `debuggerChecks` in `verify.do`. |
| Artifact-install helper and installer shell tests | `installArtifacts` delegates to the public installer's single transaction; `install.test.do` owns offline download and rollback fixtures. |
| Editor extension build/service/verification and native-test TypeScript scripts | `extension.do` and `nativeEditorChecks`; npm commands invoke the shared Doof tool. |
| Historical emission-model Python utility and its test | Removed; exploratory estimates are documented in the archived performance report and are not a maintained workflow. |

Use `tools/run.sh test`, `verify`, `debugger-test`, `process-test`, `preflight`,
`snapshot-test` (after `build.sh`), or
`cache-test <old-stamped-compiler> <new-stamped-compiler>` for the corresponding
repository checks. `verify` is the full platform acceptance gate without signing
or publishing; `release <version>` also enforces clean inputs and signing.

Historical reports retain the command names that were actually run at the time.
They are not current operating instructions.
