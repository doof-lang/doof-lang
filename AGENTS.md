# Doof Compiler Agent Guidelines

This repository is the official Doof compiler. Production compiler
code is Doof source under `src/`; generated release snapshots are derived artifacts, not a second implementation.

## Required workflow

- Add focused `*.test.do` coverage beside every changed compiler module.
- Test happy paths, boundaries, and actionable diagnostics.
- Keep parser, analyzer, checker, emitter, package, and native-driver ownership
  separate. Split modules before they become difficult to understand.
- Treat decorated AST types and bindings as the emitter's semantic input. Do
  not reconstruct checker decisions during emission.
- Prefer collected diagnostics with source spans over panics for user errors.
- Doof imports omit file extensions. JavaScript is prohibited outside
  `extensions/vscode-doof`, where TypeScript tooling and untracked generated
  JavaScript bundles are permitted for the VS Code extension.
- Update `spec/` and the Doof language skill when syntax or semantics change.
- Update architecture/source-structure docs when ownership or lowering changes.

## Repository tooling

- Implement repository automation and its tests in Doof under `tools/`.
- Keep shell only for pre-Doof installation/source rebuilding, thin launchers,
  or native test fixtures. Do not add Python orchestration.
- Remove obsolete tools rather than maintaining unused compatibility logic.

## Release invariants

- No generated bootstrap sources belong in the maintained source tree.
- Release source snapshots contain no binaries, objects, PCH files, developer
  paths, emitted `#line` directives, or mutable build state.
- Generate snapshots only from a verified installed-seed fixed point. Never
  hand-edit generated C++; change `src/` and regenerate the release assets.
- Stamp versions only in isolated build inputs. Published release versions are
  immutable; every development installation receives a unique version.
- Runtime and standard-catalog resources are explicit `doof.json` resources.

## Verification

Use `./dev-install.sh` for an incremental development compiler. Reserve
`./build.sh` for installed-seed fixed-point verification, not the edit-test loop.
Run `./scripts/test.sh` for normal changes and `./scripts/release.sh <version>`
to prepare a release from clean compiler and stdlib checkouts. Release builds
require `DOOF_SIGN_IDENTITY` and `DOOF_NOTARY_PROFILE` and do not publish to GitHub.

The release gate includes macOS Wasm builds. It requires `em++` and
`xcrun swiftc`, and Emscripten must be able to write its toolchain cache.
In a restricted sandbox, request external cache access before running the gate;
Homebrew normally stores that cache under
`/opt/homebrew/Cellar/emscripten/.../libexec/cache`.

### Test execution

- Use `dist/doof test src --filter <exact-test-name>` for focused regression
  work, then run `./scripts/test.sh` once the focused tests pass.
- Run test commands serially. Test invocations share
  `build/.doof-tests/shared`; parallel runs can overwrite the same generated
  sources and objects, cause linker failures, and leave orphaned compiler
  processes.
- Prefer one broader filter or sequential focused invocations over launching
  multiple filtered tests concurrently. A warm shared build makes subsequent
  sequential filters inexpensive.
- If a test run must be stopped, terminate the `dist/doof test` process and
  confirm that compiler children targeting `build/.doof-tests/shared` have
  also exited before starting another run.
- Do not interpret a failure from a contended shared build as a compiler
  regression. Rerun it once in isolation before investigating the result.

### Quark

Use Quark as durable project memory.

- Use the installed Quark MCP tools, not shell commands.
- Ask about known bugs, behavior, workarounds, or history with the Quark `query` tool for `<quark-project>`.
- Lodge a durable bug, gap, or useful finding with the Quark `intake` tool for `<quark-project>`.
- In reports, include expected and actual behavior, reproduction details, evidence, and uncertainty when relevant. Quark handles deduplication; do not invent issue IDs.
- Do not lodge transient environment or tool failures, secrets, or raw logs.
- If Quark is unavailable, continue the main task when safe and mention that its knowledge was not read or updated.
