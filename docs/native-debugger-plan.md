# Native Doof Debugger Tracking Plan

Updated: 2026-09-08

## Goal and completion rules

`doof debug [entry.do|package-dir] [-- program-args...]` makes a debug build
and opens **Doof Debugger**, our standalone macOS application written in Doof
using `std/appkit`. The application owns an LLDB-DAP subprocess and the debug
session. No editor extension is required.

Check an item only after its implementation and relevant verification pass.
Check a milestone only when its acceptance gate passes; record evidence in the
table below. The native launch workflow is implemented and has been exercised against LLDB-DAP.
Unchecked items below remain acceptance work or follow-up coverage; they are not
implicitly complete because the app launches.

| Milestone | Status | Acceptance evidence |
| --- | --- | --- |
| M0 — Ground architecture and dependencies | Complete | Compiler, AppKit, process bindings, install scripts, local Xcode tools inspected |
| M1 — Debug build and launch contract | Implemented; coverage remaining | CLI/build/launch unit tests; real fixture Doof line tables and locals |
| M2 — LLDB-DAP transport and session | Implemented; failure-matrix coverage remaining | Framing, transport, session tests; real launch/inspect/step/exit |
| M3 — Standalone AppKit debugger | Implemented; interaction QA ongoing | Native source, stack, variables, output; event-loop pane and proportion regressions |
| M4 — Complete `doof debug` workflow | Working for console fixture | Installed app launch, args/environment, source stop, output and Stop |
| M5 — Regression coverage and distribution | In progress | Transactional installer tests; normal compiler/debugger gate passed |
| M6 — Doof-specific inspection | Follow-up | — |

## Architecture and first-version scope

- Keep CLI parsing, pure debug invocation planning, build planning, and native
  driver execution separate. Add the debugger as its own package under
  `tools/debugger/`; keep protocol, session state, and UI in focused Doof modules.
- Use a small POSIX transport bridge for nonblocking LLDB-DAP pipes; keep framing,
  request handling and session state in Doof. `std/event` drives bounded polling
  on the AppKit main loop. Launch the installed Xcode adapter through `xcrun lldb-dap`.
  The existing `std/os.Exec` reads block, so they cannot drive this UI loop directly.
- Build the shell with AppKit windows, toolbars, split panes, and outline/table
  controls. Extend reusable stdlib bindings where appropriate. Keep the source
  viewer and debugger-specific presentation local to the application, with thin
  native bridges only where existing bindings cannot expose a required view.
- First version supports launching native console programs and macOS app
  executables, source breakpoints, pause/continue/step, thread and stack
  selection, expandable variables, target output, and stopping the session.
  Start stopped at entry so users can set breakpoints before continuing.
- Source viewing is read-only. Attach, interactive terminal input, arbitrary
  Doof watch expressions, reverse execution, and actor/async history are later
  work. Native C++ representations may remain visible in first-version values.
  Explicitly explain the terminal-input limitation in UI/docs.

## Markable milestones

### M0 — Ground architecture and dependencies

- [x] Confirm generated definitions/statements carry Doof `#line` mappings.
- [x] Confirm physical source paths and dSYM generation already exist for profiling.
- [x] Identify that the current native `Debug` mode does not itself add `-g`.
- [x] Confirm `lldb` and `lldb-dap` are available through local Xcode.
- [x] Inspect AppKit views, reactive updates, and native application lifecycle.
- [x] Confirm `std/os.Exec` provides stdin writes and separate stdout/stderr chunks.
- [x] Inspect installation layout and resource packaging boundaries.
- [x] **Gate:** enough repository evidence exists to start M1 and M2 without
  replacing the native backend or inventing a new UI framework.

### M1 — Debug build and launch contract

- [x] Add `debug` to command parsing/help, including entry/package selection,
  output-directory/compiler options, and argument forwarding after `--`.
- [x] Reject unsupported hosts and Wasm/iOS targets before expensive build work.
- [ ] Add a dedicated interactive-debug build configuration using `-O0 -g`
  and frame pointers, without release `NDEBUG`, stripping, or LTO. Keep ordinary
  development builds and profiling behavior unchanged; cover flag precedence.
- [x] Isolate generated files, objects, and cache state under `build/debug`
  (or `<output-root>/debug`) and include debug configuration in cache identity.
- [x] Select physical source mappings for interactive debugging, including
  imported packages; preserve generated-glue attribution and bootstrap rules.
- [x] Produce an adjacent dSYM, using the actual Mach-O executable for app
  bundles, and retain source/object resources required by the session.
- [x] Define a versioned launch JSON containing executable path, package working
  directory, entry source, argument array, and symbol path. Pass its absolute
  path to the debugger app; avoid shell interpolation and global shared files.
- [ ] Add adjacent CLI, build-planning, mapping, and launch-planning tests for
  defaults, invalid targets, paths with spaces/Unicode, and forwarded arguments.
- [x] **Gate:** a fixture has Doof line tables and inspectable locals in LLDB;
  the launch descriptor round-trips paths and arguments exactly.

### M2 — LLDB-DAP transport and session

- [x] Implement byte-counted `Content-Length` framing and JSON decoding in Doof;
  handle fragmented headers/bodies, multiple messages, Unicode, malformed input,
  bounded buffers, and truncated EOF.
- [x] Keep adapter stderr separate from protocol stdout and drain both streams.
  Verify read/write behavior and schedule bounded work without blocking UI.
- [ ] Correlate requests/responses by sequence, handle asynchronous events,
  negotiate capabilities, and fail pending requests on disconnect or timeout.
- [x] Implement the initialize/launch/initialized/configurationDone sequence;
  do not wait for launch completion before sending required configuration.
- [x] Support source breakpoints with verified/unverified status, threads,
  stackTrace, scopes, variables, continue, pause, next, stepIn, stepOut, and
  disconnect with termination of the session-owned target.
- [x] Model starting/running/stopped/exited/failed states explicitly. Invalidate
  frame/variable handles on resume and ignore stale responses after a new stop
  or session. Handle adapter errors and unsupported reverse requests clearly.
- [ ] Preserve target output and exit status; close/reap the adapter and target
  on cancellation, window close, failed startup, and unexpected adapter exit.
- [ ] Add deterministic protocol/session tests with a fake adapter and a real
  LLDB-DAP smoke fixture, including stderr noise and failure cleanup.
- [x] **Gate:** a headless session launches a fixture, stops, inspects locals,
  steps, continues, and exits without leaking child processes.

### M3 — Standalone AppKit debugger

- [x] Create the Doof application package and native `.app` configuration.
- [ ] Add a toolbar with Continue/Pause, Step Over, Step Into, Step Out, and Stop;
  enable actions from session state and adapter capabilities.
- [ ] Build resizable panes for source, threads/call stack, variables, and output,
  with explicit loading, empty, terminated, and error states.
- [x] Add a read-only monospaced source view with line numbers, breakpoint gutter,
  current-line highlight, and scrolling to the selected stack frame.
- [x] Allow opening a source file to set breakpoints before execution reaches it;
  show pending/rejected breakpoints and adapter-provided locations/messages.
- [x] Implement frame/thread selection and lazy variable expansion; use stable
  identities for native selection and avoid rebuilding the window on events.
- [x] Extend AppKit selection or custom-view bindings as needed with focused
  stdlib tests/docs. Keep debugger state and DAP logic in Doof.
- [ ] Add keyboard actions, accessible control labels, readable output, and
  source-unavailable diagnostics. Make close/quit shut down the owned session.
- [ ] **Gate:** visually exercise a real LLDB session in the native window;
  source navigation, breakpoints, stepping, expansion, resizing, and quit work.

### M4 — Complete `doof debug` workflow

- [x] Locate the debugger bundle belonging to the active compiler installation;
  launch a fresh app instance with the descriptor after a successful build.
- [x] Package a version-matched app beside compiler resources; do not compile the
  debugger UI on every user invocation. Diagnose missing/incompatible artifacts.
- [x] Preserve target working directory, argument boundaries, and inherited
  environment through the app launch boundary. Do not persist environment
  secrets in the launch descriptor; verify environment forwarding explicitly.
- [ ] Support console and `.app` targets, including bundle resources and source
  navigation into dependencies. Keep each session's launch data independent.
- [x] Show actionable failures for unavailable LLDB-DAP, invalid descriptors,
  missing binaries/sources, and macOS launch/debugging permission failures.
- [ ] Keep the first-version launch path local; document target signing and
  entitlement requirements established by testing without changing release
  signing defaults.
- [x] **Gate:** `doof debug <fixture> -- <args>` builds and opens our app, stops
  in Doof source, displays locals/output, and cleans up on Stop or close.

### M5 — Regression coverage and distribution

- [ ] Exercise loops, calls, multiple modules, generics, closures, objects,
  unions/optionals, panics, and native interop; document stepping/inspection gaps.
- [ ] Verify breakpoint updates while running, multiple stop cycles, normal and
  nonzero exit, early close, missing adapter, adapter crash, and large output.
- [ ] Verify paths with spaces/Unicode, unchanged-build reuse, rebuild after
  source edits, independent sessions, app resources, and installation relocation.
- [x] Include debugger packaging in macOS development install and release
  artifacts, preserving transactional install behavior and other host installs.
- [x] Add automated debugger tests to the appropriate normal/platform gates;
  use `./install.sh` for the development compiler and run test commands serially.
- [x] Run focused tests, then `./scripts/test.sh`.
- [ ] Run `./scripts/release.sh` before release, with external Emscripten cache
  access as required. No bootstrap refresh or release has been performed.
- [x] Update CLI, architecture, source-structure, installation, and limitations
  docs. Update language spec/skill only if syntax or semantics change. Leave
  generated bootstrap C++ untouched unless a separately verified refresh occurs.
- [ ] Record durable findings and remaining gaps in Quark; add command output,
  test summaries, and visual QA evidence to this tracker.
- [ ] **Gate:** a clean macOS installation completes M4 without the source
  checkout, with all required tests passing and limitations documented.

### M6 — Follow-up: Doof-specific inspection

These are separate enhancements after the complete M1–M5 debugger ships.

- [ ] Present Doof class/collection/union/`Result` values with LLDB formatters.
- [ ] Recover original function, generic, and binding names from compiler-owned
  metadata; hide generated frames/temporaries with an option to reveal them.
- [x] Stop automatically on panic with useful Doof source attribution.
- [ ] Design Doof watch/condition evaluation as an explicit compiler/debugger
  interface; do not silently interpret Doof expressions as C++.
- [ ] Design actor/mailbox and promise-state inspection before adding runtime
  instrumentation; assess overhead and suspended-process read consistency.
- [ ] Track logical async origins only with explicit runtime support and tests.

## Evidence and references

- Current source mapping contract: [C++ lowering](cpp-lowering.md).
- CLI/build ownership: [compiler architecture](compiler-architecture.md) and
  [source structure](source-structure.md).
- LLDB transport/integration: [LLDB-DAP documentation](https://lldb.llvm.org/use/lldbdap.html).
- Initial research: Quark `doof-lang` reports no verified interactive LLDB
  integration at the start of this work. The implementation now has a verified
  real LLDB-DAP fixture and installed native application.
- Quark AppKit guidance requires main-loop delivery through `std/event`, explicit
  reloads, and careful callback disposal. Its subprocess-API absence claim was
  contradicted by the current `std/os.Exec` source; a correction was submitted.

### Implementation and UI evidence — 2026-09-08

- `./install.sh` installed the compiler, stdlib bundle and standalone debugger at
  `~/.doof/bin`. The app is built once during installation.
- Focused compiler coverage passed: debug command/launch contracts, interactive
  debug flag precedence, and unit `Result` carrier emission.
- Protocol (2), transport (2), session (4), and real LLDB integration (1) tests passed.
  Integration checks line 4, local `count = 41`, stepping, output, arguments and environment.
- AppKit source-view update/disposal and three-pane resize tests passed. The shown-window
  regression runs eight native event-loop turns. A weighted-pane test checks a dominant source pane.
- Live QA exposed a second split collapse after initial sizing. `DoofSplitView` now
  owns frame layout instead of invoking NSSplitView's competing constraint layout.
  Resize notifications synchronously lay out contents during divider tracking.
- Default pane weights are **16% navigation / 66% source / 18% variables**.
  Compact thread section, icon toolbar, source filename/line header,
  quieter labels and status, and content-sized source columns replace the initial UI.
- Native toolbar items disable automatic validation so Doof session enablement persists.
- Remaining acceptance coverage includes app-resource targets, independent concurrent
  builds, a deterministic fake-adapter timeout/reordering matrix, and release/relocation gates.
  Doof-specific value formatting and compiler-owned name metadata remain M6 work.

- Full `./scripts/test.sh` passed: **1,149 compiler tests**, host dispatch, runtime
  scheduler, bootstrap-script and installer checks, nine debugger test entries
  (real integration is opt-in in that batch), and the separately enabled real
  LLDB-DAP integration test. Log: `build/debugger-full-tests.log`.
- Full `std/appkit` suite passed: **56 tests**, including native event-loop
  pane stability and weighted initial proportions. Log: `build/debugger-appkit-tests.log`.

### Source and inspection refinements — 2026-09-08

- [x] Remove source row/text selection; use a separate accessible breakpoint button
  beside each line, with quiet empty markers and red pending/verified markers.
- [x] Remove the separate breakpoint table from the navigation sidebar.
- [x] Color Doof source using the compiler lexer, including retained multiline
  comments and UTF-8 spans converted to AppKit UTF-16 ranges. Cache colors per file.
- [x] Hide known compiler-generated local names and register scopes by default.
  Preserve source-declared underscore names; “Show internals” reveals the raw rows.
- [x] Shorten stack names (`doof_main` → `main`), omit implementation namespaces,
  and show only frames with available Doof source. Select the first available Doof
  frame when stopped in native glue. An empty stack says “No Doof source frames”.
- Name filtering is a presentation heuristic backed by source identifiers; complete
  Doof binding metadata and native collection pretty-printing remain follow-up work.

- Refinement verification: full normal gate passed (1,149 compiler tests, 15 debugger
  test entries and real LLDB integration); full AppKit suite passed 57 tests.
  Live native QA confirmed syntax colors, no source text/row selection, a dedicated
  line-4 breakpoint button, `main · 4` as the only visible stack frame, `count = 41`,
  and toggling “Show internals” to reveal/hide `_iterable_2` and Registers.
  The rebuilt app and stdlib bundle are installed in the local toolchain.

### String-array presentation — 2026-09-08

- [x] Recognize Doof `string[]` native shared-vector carriers (including libc++ type
  spelling), show the logical type/count, and flatten LLDB's synthetic `pointer`
  node into indexed string elements. Preserve raw rows under “Show internals”.
- [x] Load vector storage lazily within the existing request bounds and stale-frame
  guards. Failed expansions can be retried. Unrecognized types retain native display.
- [x] Cover empty arrays, unknown size, unrelated types, raw-view preservation, and
  a real LLDB expansion of `arguments` with spaces and Unicode. Full normal gate
  passes: 1,149 compiler tests, 17 debugger entries, and real LLDB integration.
- This is the first collection presenter; arbitrary collections and full Doof
  value formatting remain follow-up work. Variable fetches remain bounded to 200.
- Live AppKit QA confirmed the expanded row reads `arguments : string[] · 2 items`
  with `[0] = "argument space"` and `[1] = "工具"` directly beneath it. The updated
  bundle is installed in the local toolchain.

### System globals — 2026-09-08

- [x] Filter system-owned global names (`std::`, `doof::`, GNU C++ and C++ ABI
  namespaces) only within the Globals scope. Preserve application globals,
  including globals with C++ library types and escaped `std_`/`doof_` namespaces.
- [x] Hide a loaded Globals section if no user-visible entries remain. Keep
  loading separate from loaded state; never hide it while a fetch is in flight.
- [x] “Show internals” restores the original globals and register scopes.
- Verified a real application `debuggerGlobal = 73` remains visible with system
  globals filtered. Fixture's increment/breakpoint is now line 5. Focused coverage
  also checks namespace boundaries, scope context, empty/loading behavior, and raw
  visibility. Full normal gate passes (1,149 compiler tests, 19 debugger entries,
  plus the real LLDB integration).

### Panic stops and continuous splitters — 2026-09-08

- [x] Install an internal `doof::panic` function breakpoint before configurationDone.
  Explicit panic and runtime panic_at callers stop before unwinding. Select the
  first available Doof frame and report “Stopped: panic”. Caught panics also stop;
  Continue allows catchPanic to recover normally. No broad C++ exception breakpoint.
- [x] Real LLDB cases verify explicit panic/source/locals, bounds-check panic, and
  successful continuation through catchPanic. A dedicated fixture keeps these
  separate from the normal globals/arrays launch test.
- [x] Replace the ineffective resize-notification-only fix with native per-event
  divider tracking. Each dragged event resizes adjacent panes, calls Doof layout,
  and displays the window immediately. Wider hit targets and resize cursors aid
  dragging; minimum pane sizes prevent accidental collapse. Both axes covered.
- The split implementation now lives in std/appkit/native_split_view.hpp. Native
  regression verifies successive divider moves change child bounds synchronously,
  without another application-loop turn. User confirmed live splitters improved.
- Full validation passed: 58 AppKit tests; 1,149 compiler tests; 22 debugger test
  entries; normal LLDB integration and three enabled panic integration tests.

- Panic stops now display a prominent **Paused on panic** banner above the source,
  with the runtime panic text when available. LLDB scope references are reused
  across selected frames, so runtime message scopes/variables are read before
  selecting the Doof caller. Selection/stop generation checks discard stale reads.
  Real integration checks all three messages and confirms the banner state clears
  when continuing a caught panic.

- [x] Keep the temporary startup source breakpoint private, merging it only into
  DAP requests. It no longer appears as an unresolved import-line gutter marker.
  Remove it on the first Doof-source or panic stop, including native panic frames,
  while preserving user breakpoints on the same line. Full scripts/test.sh passed,
  including real LLDB coverage of empty user breakpoints and line-1 preservation.

### VS Code launch integration — 2026-09-08

- Added `debug --launch-json <path>` so external clients can reuse the native
  debug build and versioned descriptor without requiring the AppKit bundle.
- Added VS Code's `doof` launch type, `.do` source breakpoints and **Doof: Debug
  Project**. The extension delegates protocol/session UI to Xcode LLDB-DAP.
- Default entry and panic stops use LLDB function breakpoints. Native app
  presentation (filtered frames/variables, collection formatting, panic banner)
  remains separate. Doof expression evaluation remains M6 follow-up work.
- Verification: 1,170 compiler tests, runtime/host/bootstrap-script/installer
  checks, and 23 debugger protocol/session test entries passed. The sandboxed
  normal gate failed only at real LLDB launch; rerunning `scripts/debugger.test.sh`
  with native debugging permissions passed the real session, three panic cases,
  and external-descriptor console/macOS-app builds without a debugger bundle.
- Extension validation: TypeScript check, all 10 Node tests, service artifact
  verification and VSIX packaging passed. The packaged 0.2.7 extension passed a
  real isolated VS Code session covering entry/source breakpoints, locals, step
  over, arguments/environment/output, panic stops, and target-process cleanup.
- Logs: `build/vscode-debug-full-tests.log`, `build/vscode-debug-native-tests.log`,
  `build/vscode-debug-extension-tests.log`, and `build/vscode-debug-package.log`.
  The development compiler/debugger are installed; the extension is packaged
  as `extensions/vscode-doof/doof-language-0.2.7.vsix`. No Marketplace publication
  or compiler bootstrap refresh was performed.
