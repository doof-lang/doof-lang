# Runtime Observability: Design and Implementation Status

## Outcome

`doof observe` is an opt-in workflow that builds and runs a Doof program with
a local HTML observability UI. The current implementation exposes structured
logs, process-local metrics, and compiler-instrumented class lifecycle counts.
It remains separate from interactive debugging and sampled profiling.

The observer is passive: it must not control program execution, replace an
application logger, or allow a slow browser to backpressure the observed
program. Ordinary `run`, `build`, and packaged release programs do not include
observer server or UI support unless a future explicit package setting requests
it.

## Current state (2026-09-23)

The implementation is present in the local compiler and standard-library
worktrees; it has not been committed or published as a release. Phases 1–4 are
implemented. Phase 5, debugger discovery, is optional and not implemented.

| Area | Current state |
| --- | --- |
| Metrics intrinsics | Checker, emitter, and thread-safe sorted runtime counters implemented and tested. |
| `doof observe` | Dedicated command, isolated build graph, argument/exit-status forwarding, browser policy, and detached macOS app URL discovery implemented. |
| Lifecycle and logs | Reference-class create/dispose counters and an additive `std/log` tap implemented; the application logger remains independent. |
| HTTP/SSE and UI | Token-scoped snapshot, Prometheus, bounded SSE, built-in HTML UI, and package-selected static UI implemented. |
| Platform acceptance | Native console and macOS app exercised on macOS. Linux native acceptance is outstanding; Windows has planning tests but no native acceptance run. |

Verification completed on macOS:

- `./scripts/test.sh` passed, including compiler, repository, native observer,
  debugger, and LLDB checks; `dist/doof test /Users/andrew/doof-stdlib/log`
  passed the affected standard-library package tests.
- `./build.sh` reached an installed-seed generated-source fixed point in two
  generations across 424 sources.
- `./tools/run.sh verify` passed the release acceptance gate, including the
  observed custom-UI fixture, WebAssembly and iOS builds. Its live Doof target
  check subscribes to SSE, reconnects after a retention gap, and recovers final
  metrics and logs from the snapshot.
- A browser check showed the built-in UI displaying live metrics, class counts,
  and structured logs; HTML-like log content remained text, and filtering
  worked. Native tests cover IPv4/available IPv6 loopback, authentication,
  request bounds, slow clients, and clean shutdown delivery.

The remaining required gate is native Linux console acceptance. Windows native
acceptance should be run when a Windows host is available; until then its
build/resource planning is covered by pure tests. The server binds to
`127.0.0.1` and also to `::1` when available. No public bind mode is provided.

## Product boundaries

Doof retains three distinct workflows:

| Workflow | Purpose | Presentation and transport |
| --- | --- | --- |
| `doof debug` | Breakpoints, stepping, inspection, and execution control | Native debugger or another DAP client |
| `doof profile` | Sampled performance capture and post-run analysis | Instruments trace on macOS |
| `doof observe` | Passive live logs, metrics, and object lifecycle visibility | Local versioned HTTP API and HTML UI |

The debugger may eventually display or link to an observer URL, but it does not
own the observer protocol, server, or UI. Stopping a program in the debugger may
also stop in-process telemetry production; that is not a reason to merge the
systems.

## Command and build model

The primary interface is:

```text
doof observe <entry.do|package-dir> [options] [-- program-args...]
```

Observer-specific options are:

- `--no-open`: print the URL without opening a browser;
- `--retain-events <count>`: bound the recent event ring;
- `--port <port>`: primarily for deterministic integration tests, with `0` as
  the normal ephemeral-port default.

The server always binds to loopback in the first version. There is no public
`--host` option.

`observe` uses an isolated `<build-directory>/observe` graph. It enables class
lifecycle instrumentation and optional runtime observer support without
changing ordinary build outputs or their cache identity. Native builds use the
normal native build configuration, with observation support enabled explicitly.

The driver releases the project build lock before starting the observed target,
matching `run` lifecycle behavior. It forwards program arguments and preserves
the target's standard input, output, error, and exit status for console targets.
For detached macOS apps it uses a private URL-discovery file so `--no-open` can
still print the session URL.

## Architecture

The implementation has four layers with one-way dependencies:

1. **Telemetry producers** record metrics, class lifecycle changes, and
   structured log entries.
2. **Observer hub** owns current metric state, monotonically sequenced events,
   and a bounded recent-event ring.
3. **Local transport** exposes snapshots, an SSE subscription, Prometheus text,
   and static UI assets.
4. **HTML presentation** consumes only the versioned HTTP contract.

The observer hub is independent of HTTP. This keeps a future sidecar, IDE
panel, test harness, or alternate transport possible without changing
instrumentation.

Optional observer support belongs in focused runtime/native modules rather than
growing `runtime/doof_runtime.hpp` into a web application. The canonical
runtime may expose the small process-local metric/event primitives needed by
generated code. Socket handling, HTTP framing, event retention, and embedded
assets remain separately owned and are materialized only for observable builds.

The implementation does not import `std/http-server` into the core runtime.
That would invert the runtime-to-standard-library dependency and introduce
hidden event-loop ownership into arbitrary programs. Protocol behavior should
nevertheless follow the same bounded I/O and actionable-error standards.

## Metrics

The documented intrinsic surface is implemented:

```doof
function metricsIncrement(name: string, value: long): none
function metricsSnapshotPrometheus(): string
```

The self-hosted checker validates both calls, the emitter lowers them to runtime
functions, and native tests cover accumulation, negative increments, sorting,
and concurrent access.

Counters are process-local and thread-safe. Snapshots are deterministically
sorted. The initial compatibility surface accepts a full Prometheus identity
string; the observer's internal protocol must not prevent a later typed metric
API with separately validated names and labels.

Observable builds instrument reference-class construction and destruction with:

```text
doof_class_created_total{module="...",class="..."}
doof_class_disposed_total{module="...",class="..."}
```

Value structs are not instrumented. The UI derives live instances as created
minus disposed, preserving monotonic export counters. Escaping of module and
class labels is deterministic and tested. Instrumentation is emitted from the
checked class declaration and concrete specialization already selected by the
compiler; the emitter does not reconstruct semantic ownership.

Lifecycle counters currently use the thread-safe runtime metric map. Lock
contention under very high object churn has not been measured; atomic or
thread-local aggregation remains a possible performance follow-up.

## Structured logs

`std/log.LogEntry` is the source of observer logs. It already carries severity,
message, structured context, source location, and timestamp.

Observation is an additive tap. It must not replace the logger installed with
`setLogger`, change level filtering for the application sink, or cause formerly
visible console/file logs to disappear. The tap receives structured entries
even when no ordinary logger is installed so `doof observe` works without
application setup. `fatal` retains its existing panic behavior.

Standard output and standard error are not log streams and are not captured in
the first version. An explicit console-capture channel may be designed later.

The standard-library change is made in `doof-stdlib/log` with focused package
tests. The compiler/runtime exposes only a stable event-ingestion boundary; it
does not acquire knowledge of `std/log` source declarations.

## Versioned HTTP contract

The first API version is:

```text
GET /api/v1/snapshot
GET /api/v1/events
GET /api/v1/metrics/prometheus
GET /                         built-in or project-provided UI
GET /assets/...               UI assets
```

`snapshot` returns session metadata, capabilities, current metrics, and the
retained log window. It is the authoritative recovery path after connection or
retention gaps.

`events` is `text/event-stream`. Each event has a monotonically increasing ID.
The server accepts `Last-Event-ID` when the requested position remains in the
ring. Event kinds initially include:

- `hello`: protocol version, session identity, and capabilities;
- `log`: one structured log entry;
- `metrics`: a coalesced set of changed metric values;
- `gap`: the client fell behind retention and must reload `snapshot`;
- `shutdown`: best-effort clean target termination notification.

The server sends heartbeat comments. Metric events are coalesced on a bounded
interval rather than generated for every increment. A slow or disconnected
client cannot block telemetry producers; it loses retained events and receives
`gap` on recovery.

JSON response shapes and SSE rendering live in pure planning/formatting modules
with focused tests. Socket lifecycle and writes remain in a driver/native
boundary. End-to-end tests verify browser-independent HTTP behavior.

## UI and extension point

The built-in UI initially provides:

- connection/session status;
- filterable structured logs with severity and source;
- metric values and recent deltas;
- consolidated live class counts;
- a raw Prometheus view or download link.

The UI uses only `/api/v1`; it has no privileged runtime coupling. Static HTML,
CSS, and JavaScript assets are maintained as source assets and embedded or
copied through the explicit project/resource plan. Generated JavaScript is not
maintained under the compiler tree.

Packages select a static replacement bundle through this manifest field:

```json
{
  "observe": {
    "ui": "observability/"
  }
}
```

The path is resolved within the package root and must contain `index.html`.
A custom UI receives no extra native privileges;
it consumes the same API as the built-in UI. Arbitrary native observer plugins
are out of scope.

## Security and failure behavior

- Bind only to `127.0.0.1` and `::1` where supported.
- Use an ephemeral port by default.
- Generate an unguessable per-session token and require it for API and asset
  requests. Do not rely on loopback as authorization because logs may contain
  secrets and unrelated local processes can issue requests.
- Send restrictive Content Security Policy, `X-Content-Type-Options: nosniff`,
  no-store cache policy for API responses, and no permissive CORS headers.
- Accept only the methods and bounded request sizes needed by the read-only API.
- Escape all HTML through DOM text operations; telemetry data is never treated
  as markup.
- Server startup failure produces an actionable warning and does not crash the
  target unless `doof observe` cannot discover any usable session endpoint.
- Telemetry producers never panic because a browser disconnected or an event
  could not be retained.

## Ownership map

The intended compiler ownership is:

| Area | Owner |
| --- | --- |
| CLI syntax and validation | `src/cli.do` with adjacent tests |
| Pure observe invocation/session plan | new focused `src/observe-command.do` |
| Build, launch, URL discovery, browser open | focused observe driver plus `src/driver.do` routing |
| Intrinsic declarations | `src/checker-symbols.do` |
| Intrinsic lowering | focused builtin-call emitter path |
| Class lifecycle instrumentation | `src/emitter-decl.do`, driven by explicit emission configuration |
| Optional support-file planning | `src/emitter-project.do` and focused observer support planner |
| Process-local metric/event primitives | focused files under `runtime/` |
| Structured log tap | `doof-stdlib/log` |
| UI source assets | `observer-ui/`, with maintained browser JavaScript and no JavaScript build step |

Final filenames may change when the nearest existing modules are inspected.
Any ownership change updates `docs/source-structure.md` and
`docs/compiler-architecture.md` in the same phase.

## Implementation phases

### Phase 1: restore the metrics contract

- Add checker builtins for `metricsIncrement` and
  `metricsSnapshotPrometheus`.
- Lower calls directly to focused runtime functions.
- Add thread-safe counters and deterministic Prometheus snapshots to runtime
  support.
- Cover valid calls, arity/type diagnostics, emitted C++, increments, negative
  values, empty snapshots, sorting, and concurrent access.
- Reconcile the specification and Doof skill with the implemented behavior.

Exit gate: focused tests pass, then `./scripts/test.sh` passes serially.

### Phase 2: command, instrumentation, and polling MVP

- Add `doof observe`, isolated cache/output paths, argument forwarding, and
  browser-open policy.
- Add explicit observable-build configuration through planning and emission.
- Emit reference-class create/dispose counters with stable escaped labels.
- Materialize optional server support and built-in assets only for observable
  builds.
- Serve authenticated `/api/v1/snapshot` and Prometheus endpoints.
- Build the initial metrics/object-count HTML UI using periodic snapshots.
- Test CLI diagnostics, build-cache separation, support-file inclusion,
  lifecycle counts, loopback binding, authentication, response bounds, and
  target exit propagation.

Exit gate: native console acceptance on macOS and Linux, plus the normal test
suite. Windows behavior is covered by pure planning tests until an acceptance
host is available.

### Phase 3: bounded events, structured logs, and SSE

- Add the sequenced bounded event ring and nonblocking producer API.
- Add SSE framing, heartbeats, reconnect replay, coalesced metric changes, and
  explicit gap recovery.
- Add the additive `std/log` observer tap and preserve existing sinks.
- Extend the UI with live structured logs and connection recovery.
- Test ordering, retention boundaries, slow clients, reconnection, malicious
  log content, application logger coexistence, and clean shutdown.

Exit gate: compiler and stdlib suites pass serially, with an end-to-end target
that produces logs and metrics while a client reconnects across a retention
gap.

### Phase 4: custom static UI

- Define and validate the package manifest/resource contract.
- Retain the built-in UI as fallback.
- Serve custom assets under the same authentication and response policies.
- Test missing assets, traversal attempts, MIME types, CSP behavior, and API
  compatibility.

Exit gate: a release fixture packages and runs a bespoke UI without changing
the telemetry protocol or runtime instrumentation.

### Phase 5: debugger discovery integration

- Optionally add the observer URL/session token to a versioned debug launch or
  DAP-facing discovery record.
- Present a link from debugger clients without moving observer ownership into
  the debugger.

This phase is optional and does not block the observability feature.

## Verification discipline

- Add focused `*.test.do` coverage beside every changed compiler module.
- Run focused exact-name tests with `dist/doof test src --filter <name>` before
  the serial full suite.
- Never run compiler test invocations concurrently because they share the
  generated test build.
- Add native runtime tests for concurrency, HTTP framing, bounds, and shutdown.
- Add release fixtures for optional support assets and the eventual custom UI.
- Keep diagnostics actionable and source-spanned for user errors.
- Update `spec/`, the Doof language skill, CLI documentation, source ownership,
  and the horizontal architecture map as each contract lands.

## Explicit non-goals

- Remote network exposure or production telemetry collection.
- OpenTelemetry/OTLP export in the initial implementation.
- Query storage, alerting, or durable log retention.
- Execution control through the observer UI.
- Capturing arbitrary stdout/stderr as structured logs.
- Loading native UI plugins into the observed program.
- Replacing Instruments profiling or the DAP debugger.
