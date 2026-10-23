# Runtime observability

## Outcome

`doof observe` is an opt-in workflow that builds and runs a Doof program with
a local HTML observability UI. The current implementation exposes structured
logs, process-local metrics, and compiler-instrumented class lifecycle counts.
It remains separate from interactive debugging and sampled profiling. User-facing
command options are in [CLI](cli.md); this document records the design
contract and ownership.

The observer is passive: it must not control program execution, replace an
application logger, or allow a slow browser to backpressure the observed
program. Ordinary `run`, `build`, and packaged release programs do not include
observer server or UI support.

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

The server always binds to loopback. There is no public `--host` option.

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

Programs record counters through two intrinsics:

```doof
function metricsIncrement(name: string, value: long): none
function metricsSnapshotPrometheus(): string
```

The checker validates both calls and the emitter lowers them to runtime
functions.

Counters are process-local and thread-safe. Snapshots are deterministically
sorted. The intrinsic accepts a full Prometheus identity
string; the observer's internal protocol does not preclude a later typed metric
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

Lifecycle counters use the thread-safe runtime metric map.

## Structured logs

`std/log.LogEntry` is the source of observer logs. It carries severity,
message, structured context, source location, and timestamp.

Observation is an additive tap. It does not replace the logger installed with
`setLogger`, change level filtering for the application sink, or cause formerly
visible console/file logs to disappear. The tap receives structured entries
even when no ordinary logger is installed so `doof observe` works without
application setup. `fatal` retains its existing panic behavior.

Standard output and standard error are not log streams and are not captured.

The tap lives in `doof-stdlib/log`. The compiler/runtime exposes only a stable
event-ingestion boundary; it has no knowledge of `std/log` source declarations.

## Versioned HTTP contract

API version 1 is:

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
ring. Event kinds are:

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

The built-in UI provides:

- connection/session status;
- filterable structured logs with severity and source;
- metric values and recent deltas;
- consolidated live class counts;
- a raw Prometheus view or download link.

The UI uses only `/api/v1`; it has no privileged runtime coupling. Static HTML,
CSS, and JavaScript assets are maintained in `observer-ui/` and embedded or
copied through the explicit project/resource plan. There is no JavaScript build
step.

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

| Area | Owner |
| --- | --- |
| CLI syntax and validation | `src/cli.do` |
| Observe target validation, launch environment, and bundle invocation plan | `src/observe-command.do` |
| Build, launch, URL discovery, browser open | `src/launch-driver.do`, routed by `src/driver.do` |
| Intrinsic declarations | `src/checker-symbols.do` |
| Intrinsic lowering | `src/emitter-expr-calls.do` |
| Class lifecycle instrumentation | `src/emitter-decl.do`, driven by `src/emitter-context.do` configuration |
| Observer define and support-file planning | `src/emitter-project.do`, `src/materialize-driver.do` |
| Metric/event primitives, server, and platform sockets | `runtime/doof_observer.hpp`, `runtime/doof_observer_platform.hpp` |
| Structured log tap | `doof-stdlib/log` |
| UI source assets | `observer-ui/` |
| Live acceptance checks | `tools/repository/observe-checks.do` |

Ownership changes update [source structure](source-structure.md) and
[compiler architecture](compiler-architecture.md).

## Remaining work

- Native Linux console acceptance. Windows observe planning is covered by pure
  tests but has no native acceptance run.
- Lifecycle-counter lock contention under very high object churn has not been
  measured; atomic or thread-local aggregation is a possible follow-up.
- Optional debugger discovery: publish the observer URL/session token through a
  versioned debug launch or DAP discovery record so debugger clients can link
  to it, without moving observer ownership into the debugger.

## Explicit non-goals

- Remote network exposure or production telemetry collection.
- OpenTelemetry/OTLP export.
- Query storage, alerting, or durable log retention.
- Execution control through the observer UI.
- Capturing arbitrary stdout/stderr as structured logs.
- Loading native UI plugins into the observed program.
- Replacing Instruments profiling or the DAP debugger.
