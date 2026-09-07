# Doof for Visual Studio Code

Desktop language support powered by the production Doof compiler, bundled as
WebAssembly. No native compiler installation is needed for editor intelligence.

## Install

Use **Extensions → … → Install from VSIX…** and select
`doof-language-0.2.0.vsix`, then open a `.do` file. The extension provides live
Problems, completion, hover, definitions/type definitions, references, symbols,
signature help, semantic colouring, rename, quick fixes, and explicit formatting.
Completion also suggests unimported workspace and standard-library exports;
selecting one adds or extends its import. The suggestion shows the source module.

Use **Doof: Build Project**, **Doof: Run Project**, and the Testing sidebar for
native workflows. Set `doof.compilerPath` to the current compiler executable,
or put `doof` on PATH. Native workflows require workspace trust and offer to save
dirty Doof files and manifests. Test discovery uses the bundled parser; execution
uses exact test IDs and JSON result reports. Test runs are serialized and
cancellation terminates their process group.

**Doof: Show Toolchain Versions** reports the bundled compiler version, revision,
artifact hash, and installed native version. The extension never downloads or
replaces your native compiler. **Doof: Restart Language Service** replays open
buffers after restarting the server.

## Editing behaviour

- Unsaved files overlay disk sources, including local package dependencies.
  Configured entry graphs and otherwise unreached open files are analyzed.
  Separate test graphs retain compiler mock-import behaviour.
- Standard-library types, generics, and documentation come from bundled `.do`
  sources. Definitions navigate to those same sources.
- Diagnostics wait for a 200 ms quiet period. A separate query worker retains the
  last completed snapshot during analysis; stale results and unsafe edits are
  discarded. Newly introduced declarations become available when their check
  completes. Typing is never blocked by synchronous work in the extension host.
- Reuse is conservative: edits to nominal declarations, changed imports, and
  uncertain dependency effects trigger a full background check. This is module
  invalidation, not an incremental type checker for every possible edit.
- Rename uses binding identities and preserves explicit aliases and construction
  shorthand. It rechecks the proposed edit and refuses ambiguous collisions,
  incomplete graphs, and bundled-library changes. A dependent file outside the
  checked graph must be opened before renaming a symbol it may use.
- **Format Document** adjusts indentation only, defaults to two spaces, preserves
  comments and literal contents, and refuses malformed source. Configure
  `doof.indentSize` for another width. Format-on-save is not enabled.
- Completion during pending edits supports simple member receivers and named
  arguments using the last checked scope. Complex new expressions require their
  next analysis. Import quick fixes are offered only for unique parsed exports.

On the development Apple Silicon host, the compiler frontend graph took about
1.3 seconds for a full editor check and warm in-service queries had a roughly
0.7 ms p95. These are measurements, not a latency guarantee for every project.
MiddAI also checks cleanly: approximately 3.7 seconds cold, 1.9 seconds for a
background edit check, and 4.3 ms p95 warm queries on the same host. Newly typed
declarations and fresh diagnostics may wait for that background check.
The language service bounds repeated-edit memory by recycling the spare worker
above 192 MiB; the published snapshot remains available during replay.

Browser VS Code, debugging, automatic compiler downloads, and Marketplace
publication are outside this version. Windows and Linux desktop smoke tests must
be run on those hosts before declaring cross-platform release support.

## Develop and verify

Use Node 22.18+ (or newer), npm, a verified development Doof compiler in
`dist/doof`, Emscripten, and its matching `dist/doof-stdlib.tar` resource.

```sh
npm ci
npm run build:service
npm run check
npm test
npm run test:parity
npm run test:server
npm run test:native
npm run benchmark
npm run package
VSCODE_EXECUTABLE="/path/to/Visual Studio Code executable" npm run test:extension
```

Run from this directory. The service build needs Emscripten cache write access;
stdlib sources are extracted from the verified compiler’s curated bundle, so
nearby projects and samples never become fake standard packages. `test:extension` unpacks
the VSIX and tests that packaged copy with an isolated VS Code profile, leaving
the user's extensions and settings alone. Omit `VSCODE_EXECUTABLE` to let the
VS Code test runner obtain a supported editor. On Linux, run it under `xvfb-run`
when no display is available. `node scripts/test-server.ts --benchmark` measures
warm LSP queries while the compiler project is being reanalyzed.

Also run repository `./scripts/test.sh` and the release gates. Bootstrap source
is never edited by the extension build. Wasm, matching stdlib sources, version
metadata, TypeScript bundles, and VSIX files are generated and untracked.

Test Explorer needs a native compiler supporting `--selection-json`, `--json`, and
`--report-json`. Installing the VSIX does not update a compiler already on PATH.
If Test Explorer reports an incompatible compiler, run `./install.sh` from the
current compiler checkout, or use **Doof: Select Native Compiler** to choose that
checkout's `dist/doof`. The extension checks this protocol before running tests;
older development builds can share the same version number.

Test Explorer sends one exact-selection JSON file per workspace/compiler group.
The native runner builds its existing compound harness (including unselected
tests) once and executes only selected ids. Changing the selection reuses that
harness and the native frontend cache; it does not rebuild a smaller harness.

The Test Explorer tree is project → test file → test. Nested `doof.json` projects
have separate roots and runner invocations, matching native discovery boundaries.
Selecting a project/file runs its descendants; exclusions apply to whole subtrees.
Early compiler failures retain the compiler diagnostic in each affected test's
message and the Doof output channel.

Compiler-provided function ranges for exported `test…` functions in `.test.do`
files support VS Code's test gutter controls and
**Run Test at Cursor**, including cursors inside the test body.
