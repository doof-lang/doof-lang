# Compiler Architecture

This document is the horizontal concept map: it shows how information crosses
phase and file boundaries. For a file-by-file ownership index, see
[source structure](source-structure.md). For the detailed checker, decorated
call, structural-interface, and generic-specialization paths, see
[checker and monomorphisation](checker-and-monomorphisation.md).

## Pipeline and data contracts

The compiler processes a closed source graph in four front-end/back-end phases:

1. The lexer and parser produce a source-spanned AST.
2. The analyzer collects module symbols, resolves imports/re-exports, and
   decorates named types.
3. The checker builds scopes, resolves bindings, infers expression types,
   validates control flow/isolation, and decorates the AST in place.
4. The emitter consumes only the decorated graph and writes split C++17
   modules plus explicit runtime/native support inputs.

The important hand-offs are:

| Producer | Product | Consumer |
| --- | --- | --- |
| `lexer.do` | Source-spanned tokens | focused `parser-*.do` modules |
| Parser | AST nodes from `ast.do` | `analyzer.do` |
| Analyzer | `AnalysisResult`, module symbols, resolved named annotations | checker modules |
| Checker | bindings, resolved expression types, targets, and control-flow decorations on the AST | `checker-validation.do`, then emitter |
| `checked-instantiations.do` | semantic specialization closure | C++ naming adapter |
| `emitter-monomorphize.do` | C++ names for discovered specializations | module/header/type emitters |
| `emitter-worldview.do` / `emitter-module.do` | checked declaration closures and generated header/source pairs | `emitter-project.do` |
| `emitter-project.do` | generated project plus normalized native inputs | native build planner and driver |
| `native-build.do` | deterministic PCH/compile/link tasks | `native-build-driver.do` |
| `frontend-cache.do` | exact source/configuration fingerprints and emitted-module names | `driver.do` cache validation and materialization |

`compiler.do` coordinates the pure graph pipeline. `driver.do` adapts CLI,
filesystem, acquired-package, test, app, and process boundaries to it. It also
selects the command-aware native-build output mode: successful `run`
compilation is silent, while `build`, `test`, and `package` request concise
progress. `native-build-driver.do` applies that policy while retaining captured
output for failed compiler and linker commands. Source loading is inverted
through `SourceLoader`, so the analyzer discovers the transitive graph without
gaining filesystem ownership.

The analyzer keeps source resolution, graph deduplication, module ordering, and
all semantic mutation on its calling thread. Parser workers capture only source
text and module identity, return independently owned mutable ASTs, and are
consumed through a first-completed promise queue. Completed modules reveal more
imports to the main-thread driver; a deterministic depth-first ordering pass
runs before symbol/import/type resolution so worker completion order is not a
semantic input.

## Horizontal concepts

Each row names the authoritative path for a concept. A change normally follows
the row from left to right.

| Concept | Established or modeled | Checked or decorated | Consumed or executed |
| --- | --- | --- | --- |
| Source identity and diagnostics | token/AST spans in `lexer.do` and `ast.do`; diagnostic records in `semantic.do` | analyzer and focused checker module attach semantic spans | `driver.do` formats bounded diagnostic output |
| Modules and names | `resolver.do` resolves logical paths; `analyzer.do` owns imports, exports, symbols, and defining-module identity | `checker-symbols.do` resolves lexical, named-import, and namespace-member bindings | `emitter-names.do` derives stable C++ identity; the worldview planner projects referenced declarations into each module header |
| Types and assignability | resolved type records in `semantic.do`; shared operations in `checker-types.do` | focused checker modules decorate annotations and expressions | `emitter-types.do` chooses representation; expression/declaration emitters require decorations. Absence values share `emitNoneLiteral`, which specializes the checked type and uses type lowering's flattened nullable-member classification; catch initialization uses the same path. |
| Numeric constraints | resolved primitive alternatives | `checker-numeric.do` proves operator capabilities and promotion; `checker-annotations.do` validates exact numeric arguments | specialized expression emission consumes checked types; unsigned shifts and compound powers lower explicitly |
| Result propagation | try statements and lexical scopes | `checker-try.do` validates the nearest error channel and decorates success bindings | `emitter-stmt.do` stores typed success payloads using their checked representation |
| Enums | variant syntax and resolved backing slots in `ast.do` | `checker-statements.do` selects integer/string backing kind, resolves values, and validates uniqueness; `checker-resolution.do` exposes the typed API | `emitter-header.do` emits identity/lookups/formatting, `emitter-types.do` selects optional nullable carriers, and JSON/metadata emitters consume the checked backing values |
| Calls and dispatch | declarations and symbols from analysis | `checker-resolution.do` records member targets; `checker-calls.do` applies generic inference and shared `checker-arguments.do` validation | `emitter-expr-calls.do` lowers the recorded target; `emitter-call-arguments.do` shares ordering/defaults across direct and dispatched calls |
| Control flow and narrowing | statement/expression/pattern AST in parser modules | `checker-statements.do` and `checker-expressions.do` determine continuation, exhaustiveness, and narrowed bindings | `emitter-stmt.do`, `emitter-expr-control.do`, and `emitter-case-pattern.do` lower those decisions |
| Generics | type parameters in AST and resolved types | checker infers/substitutes concrete arguments | `checked-instantiations.do` discovers a fixed point; `emitter-monomorphize.do` assigns C++ names; emitters output concrete forms for every Doof-owned generic, including methods, while runtime/native-owned C++ templates remain external |
| Interfaces | interface/class declarations and resolved nominal types | `checker-interfaces.do` validates structural conformance and discovers the closed implementor set | `emitter-types.do` and declaration/JSON emitters lower interface variants |
| JSON and reflection | annotations/declarations in AST; eligibility in `json-semantics.do` | checker advertises only supported synthetic members and records metadata demand | `emitter-json.do`, `emitter-metadata.do`, and `emitter-wasm.do` generate definitions/adapters |
| Actors and isolation | actor/promise types and actor syntax | `checker-actor-boundary.do`, `checker-actor-lifecycle.do`, and `checker-isolation.do` own call boundaries, retirement diagnostics, and graph-wide effects | `emitter-expr-actor.do` and lambda/call emitters lower checked operations; the bounded runtime scheduler executes isolated function calls, async blocks, and serial actor messages |
| Closures and mutable capture | lambda/binding AST and checker bindings | checker establishes callable types and retains lexical bindings on identifier and shorthand-property nodes, including Result payloads | `emitter-expr-lambda.do` finds escaping captures, including uses nested in shorthand construction, and boxes mutable storage; Result construction emits shorthand through a decorated identifier using the checked binding and type |
| Construction | `CheckedConstruction` with specialized owner, signature, factory, and defaults | `checker-construction.do` specializes the factory/field plan; `checker-properties.do` shares value decoration after contextual shape selection | `emitter-construction.do` consumes the retained plan and shares argument/default lowering across syntax forms and actors |
| Callable bodies | checked function/method signatures and bodies | `checker-statements.do` enforces return completion | `emitter-decl.do` shares capture/context management and specialized return boundaries, including `never` |
| Module initialization | top-level checked declarations/statements and compiler entry mode | `checker-module-initialization.do` validates construction-only expressions and direct storage | `emitter-module.do`, `emitter-header.do`, and `emitter-decl.do` emit direct storage and graph-ordered execution |
| Packages and standard inputs | local-path manifests in `package-manifest.do`; authoritative bundled stdlib index in `stdlib-bundle.do` | the driver registers reached local and standard packages | bundle materialization and std-only preparation feed `emitter-project.do` |
| Incremental native builds | normalized native plan and emitted modules | `native-build.do` creates stable tasks; `pkg-config.do` normalizes flags | `native-build-driver.do` fingerprints arguments/dependencies, persists content fingerprints plus metadata, and runs dirty work |
| Incremental frontend/emission | resolver probes, source hashes, configuration, and transitive module dependencies | `frontend-cache.do` persists pointer-free exact state; `emitter-module.do` fingerprints module inputs plus the global lowering plan | `driver.do` skips exact graph hits and retains matching generated files without changing timestamps |
| Incremental executable resources | root-package resource declarations and recursive source trees | `resource-state.do` persists source/output metadata for copied files | `driver.do` skips unchanged blob reads and synchronizes edited, added, removed, or externally changed outputs before launch |
| Tests, mocks, and coverage | `test-runner.do` discovers tests and generates harnesses | analyzer rewrites mock imports; emitter inserts stable coverage markers | driver groups, builds, isolates, runs, merges, and renders reports |
| Runtime profiling | source loaders retain optional physical paths; CLI selects profile requests | emitter writes Doof `#line` mappings; native planner selects optimized symbol-rich profile flags | `profile-command.do` plans xctrace launch/open operations; driver records the trace |

## The decorated-AST boundary

This is the central phase boundary:

1. `ast.do` declares an explicit slot for information that lowering needs.
2. The owning analyzer or checker module populates it.
3. `checker-validation.do` rejects a graph where the required decoration is
   missing, unknown, or inconsistent.
4. A focused emitter consumes the decoration without re-running semantic
   analysis.

Unknown types, unresolved bindings, missing substitutions, missing
control-flow facts, or unresolved dispatch targets suppress emission. A panic
in the emitter is reserved for violation of this internal contract, not for a
user program error.

Enum backing kind and resolved values are part of this decorated-AST contract.
Emitters never infer them again from initializer syntax. Internal identity stays
a C++ `enum class`; string-backed enums use declaration ordinals internally,
while generated helpers expose the checked string backing values. A nullable
single enum is represented as `std::optional<Enum>` consistently across type,
expression, statement, JSON, metadata, and Wasm lowering.

Declarative module values use direct typed C++ storage. Safe scalar constants
retain C++ constant initialization; constructed values are assigned by one
plain generated initializer for each module that has deferred assignments.
Stateless and constant-only modules emit no initializer. The entry emitter
computes a deterministic dependency-first order and calls those initializers
after installing the application actor scope; initializer functions contain no
per-module lifecycle state. Native entry scripts retain their separate
source-order runner. Standalone WebAssembly exposes the graph protocol through
`doof_initialize` after the host calls Emscripten `_initialize`.
Wasm test harnesses instead retain their generated executable `main(arguments)`
and link as Emscripten command modules with `_start`. On macOS the driver runs
each test id in a fresh JavaScriptCore host process and Wasm instance through a
bounded WASI command shim.

Interface-constrained parameters retain their `TypeParameterType` on decorated
receivers. Checker member lookup borrows the resolved interface contract for
field bindings, signatures, callable-field identity, and method targets. Generic
argument validation substitutes declaration and enclosing-owner parameters;
symbolic alias/bound expansion does not validate temporary placeholders as real
arguments. The emitter specializes those decorated receivers before choosing
class/struct member access or variant dispatch, and uses the checked contract's
argument order and defaults. It does not discover constraints during emission.

Closed-world information drives interface variants, generic specialization,
actor isolation validation, JSON/reflection generation, and stable module
namespaces. The runtime header supplies intrinsic values, collections, actors,
the process-wide CPU-token scheduler, JSON, metrics, resource lookup, and other
generated-code support. Actor identity is independent of worker-thread
identity; the runtime admits one message per actor while sharing workers across
domains.

## Side-effect boundary

The compiler core accepts `SourceFile` values and returns diagnostics and
generated text. Pure planners then describe packages, project files, native
tasks, app bundles, and run invocations. Environment-facing modules are:

- `stdlib-bundle.do` and `stdlib-preparation.do` for offline standard-package
  materialization and bounded target preparation;
- `native-build-driver.do` for compiler/linker subprocesses and incremental
  build state;
- Apple `*-driver.do` and `ios-device.do` modules for platform tools;
- `driver.do` for top-level workflow, filesystem materialization, and command
  routing.

This separation keeps semantic tests in memory and planning tests
deterministic.

## Incremental cache boundary

Before reading or mutating shared build state, the driver retains an exclusive
`std/fs.File` lock in the project's configured build directory. The lock path
does not depend on command output overrides. Test invocations retain their locks
through all worker execution and coverage output; multiple roots are locked in
sorted, deduplicated order. `project-build-lock.do` owns acquisition and the
waiting diagnostic. The handle lifetime releases the OS lock, including on
early returns; the stable lock file is never unlinked during normal operation.

Incrementality deliberately stops at generated artifacts. The persistent
frontend cache contains source-resolution probes (including missing exact-path
probes), content hashes, relevant manifests/configuration, module output names,
and emission fingerprints. Configuration includes a SHA-256 digest of the running
compiler executable, so replacing its bytes invalidates both checked graph and
module emission reuse even at the same install path. Identical compiler copies
retain the same identity. If executable discovery or reading fails, the driver
disables both reuse paths for that invocation. It never serializes AST, symbol, binding, or checker
objects.

An exact graph/configuration hit skips checking and emission. After any input
change, the ordinary clean semantic pipeline runs. Each module is then emitted
only when its own/transitive source fingerprint or the conservative global
lowering-plan fingerprint changed. Retained `.cpp`/`.hpp` files keep their
timestamps, allowing the native dependency cache to reuse objects safely.

Missing, corrupt, or version-mismatched cache files are ordinary cache misses.
Clean compilation semantics remain authoritative.
Changes to checking or lowering semantics must bump `FRONTEND_SEMANTIC_ABI`
even when the serialized JSON shape is unchanged.

After rebuilding the development compiler, run
`sh scripts/frontend-compiler-cache.test.sh <old-compiler> <new-compiler>` to
verify same-path replacement invalidates checked state and emitted files while
unchanged compiler bytes continue to reuse them.

## Adding or changing a language concept

Before considering a feature complete:

1. Update the specification and parse it into an explicit AST shape.
2. Put name/type/control-flow policy in its owning analyzer or checker module.
3. Decorate every semantic choice needed later and extend emit-readiness
   validation.
4. Lower only those decorations in a focused emitter; update
   [C++ lowering](cpp-lowering.md) if representation changes.
5. Add adjacent happy-path, boundary, and actionable-diagnostic tests.
6. Add generated-C++ compile/runtime acceptance coverage when representation,
   runtime, native resources, or platform behavior changes.
7. Update [source structure](source-structure.md) if ownership moved and this
   map if the cross-phase path changed.

Adjacent braces produce a named-call AST even for uppercase callees; spaced uppercase braces retain named-construction parsing. The checker resolves the call target and its return type through ordinary call checking.

Multi-path expression joins are owned by `checker-inference.do`. The expression
checker supplies explicit context and branch types; the statement checker uses
the same rule for yields. `Scope.yieldExpectedType` retains the explicit
contract separately from accumulated `yieldType`. Resolved expression types
remain the emitter's carrier input; general union construction and existing
union member lookup remain in the type and resolution modules.
Yield emission carries that decorated block result through
`EmitContext.valueYieldType`, restoring the outer context after nested blocks.
Yield, case-arm, and async block owners set it; the statement emitter uses it
for contextual value conversion, including the representation of `none`.

## Native representation boundary

The [native carrier model](native-carriers.md) separates checked semantic types
from value, return, and Result/Promise payload representations. A pure classifier
owns nullable storage choices; one conversion layer preserves evaluation and
absence when crossing native carriers. The normal compiler suite compiles and
runs a durable matrix using the current source emitter, in addition to its
structural emission tests.

## Compiler phase timings

`DOOF_TIMINGS=1 doof emit` (or `doof check`) prints opt-in monotonic wall-clock
milliseconds after the command, including on diagnostic and exact-cache-hit
returns. Other commands ignore this setting. Normal compilation remains silent.
`phase-timings.do` owns a caller-local collector passed through the driver,
compiler, analyzer, and module emitter; it reads no clocks when disabled.

`command.total` includes setup, cache lookup, compilation, stdlib preparation,
project planning, and materialization/cache writes. `compiler.*` breaks down
analysis, checking, decorated-type validation, instantiation planning, optional
Wasm support, and module emission. `analysis.*` separates loading/parsing/discovery
from resolution; parsing includes parallel-worker waits. `checking.*` separates
module checking from deep-readonly and isolation validation. `emission.*`
separates graph planning, fingerprints, worldviews, header planning/rendering,
and source rendering. Repeated phases aggregate elapsed time and report a count.
Parent timings include child timings: do not sum rows across levels. Uninstrumented
or failed partial phases remain included in the enclosing command total.

To measure a cold frontend without removing an existing build, use a fresh output
directory: `DOOF_TIMINGS=1 doof emit -o "$(mktemp -d)/emit"`. This bypasses the
output-local frontend/emission caches, but does not flush OS file caches or
installed/prepared standard packages. Repeat serially with fresh directories and
report the compiler binary, stdlib selection, and median of multiple runs. Reuse
one output directory to measure the warm frontend-cache path separately.

The [2026-09-07 cold-emission measurements](archive/emission-2026-09-07.md#cold-emission-timings) compare the compiler and Middai workloads.

### Projected header reuse

Each `emitModuleGraph` invocation owns a fresh `HeaderPlanCache`. The cache
stores pre-render header plans for exact ordered selections of original checked
statements, identified by defining module path and source-span offsets, plus the
ordered concrete-interface keys selected by the consumer worldview. The worldview
planner selects the original statements; it does not synthesize replacement
statements with reused spans. Namespace mappings, physical source paths, module
surfaces, checked types, JSON demand and concrete instantiations are fixed for the
cache lifetime. The cache is never persisted or shared between compilations.

A cache miss builds the complete section, including concrete declarations, in a
fresh context. `freezeHeaderPlan` drains the builder into deeply immutable arrays
of declaration fragments and type references. The cache shares that snapshot
without copies. Each consumer retains its original worldview order and chooses
its own aliases; rendering never rewrites the cached plan. Root source-emission
context and coverage state remain per module.

`header.*` timing rows subdivide `emission.header-planning`: root context, cache
key/lookup/copy, section context, declarations, concrete declarations and cache
store. Cache lookup count is the total section demand; declaration count is the
number of misses. Their difference is the number of reused plans.

### Structured C++ types and declarations

`emitter-types.do` owns the one lowering path from decorated/specialized Doof types
to C++ representation nodes. A graph-local `CppTypeRegistry` interns ordered type
structure, template names and qualified nominal owners. IDs belong to that
registry and must not be combined with types from another registry in one plan.
Variant arms keep their existing order and nullable carrier choice. Native generic
arguments remain ordinary C++ template arguments; reached Doof generics retain
their concrete emitted names. `std::variant` is unchanged as the output carrier.

`cpp-declaration.do` separates literal C++ fragments from typed slots in immutable
declarations. Class fields, constructor parameters, function/method signatures,
module values and aliases use these slots. Comments, strings, already-lowered
expression/default snippets and opaque native glue remain text; the header pass
never reparses or substitutes inside them. The existing string-returning emitter
APIs render the same structured declarations for source definitions.

`emitter-header-aliases.do` visits type nodes before text rendering. It counts
reference-only variants in declaration order, prefers valid named aliases, skips
reserved names and allocates readable `doof_header_type_N` aliases in header
section order. Value-bearing variants retain their completeness boundary. Named
alias definitions use a separate alias view to prevent self-referential `using`
declarations. This preserves ergonomic `std::variant` and `using` output without
searching generated strings for template brackets or rewriting declarations.

Canonical type spelling is memoized by registry-local type ID and rendering
namespace. Alias-dependent spelling caches belong to each header section and
alias view; no mutable cache is embedded in a type node or header plan. Future
parallel rendering must give each worker its own mutable rendering caches.
The legacy timing label `header.cache-lookup-copy` now measures key construction
and lookup only; frozen plans are returned directly.

Completed section rendering is also cached within the graph, keyed by frozen-plan
identity, namespace and incoming alias index. A hit restores the outgoing alias
index, preserving numbering in later sections. These cached rendered sections
are immutable strings; unknown/manual plans without a graph identity bypass this
cache. Type/declaration plans remain the source of truth. The rendering cache is
external to those plans and must be worker-local if emission is parallelized.


### Semantic identity and contextual type-lowering memoization

`semantic-type-identities.do` assigns object IDs during serial preparation.
Resolved types carry an optional non-semantic `emissionIdentity` stamp; a stamp
contains only an owner token and integer, never the cache or checked graph.
There is no global counter. Another emission can restamp the same checked graph;
A renderer using an older snapshot treats a restamped object as a cache miss
instead of allocating a new ID or colliding with an existing entry. Semantic equality ignores this metadata. Check-only
compilation does not assign IDs.

`emitter-type-cache.do` owns the mutable memo tables. Module-graph emission creates
a preparation `TypeLoweringGraph` alongside its C++ registry. Each source renderer
gets a private graph/session using a prepared read-only identity snapshot, after
concrete registration is complete.
The session is valid only while its module, registry and concrete registration
tables are fixed. Its substitution object and argument arrays are stable during
each specialization. Switching substitution identity clears value, return and
registered-type memo tables, including when restoring the ordinary context.
Standalone emitter contexts default to uncached operation.

A contextual cache hit occurs before substitution, semantic reconstruction and
C++ lowering. On misses, registered-type reconstruction also memoizes children;
the graph-level C++ table then memoizes already-specialized/registered semantic
objects. Value and return entries remain separate. Payload, weak-target and
class-inner handling preserve their existing representation rules instead of
sharing incompatible cached results. Namespaces and aliases remain rendering
concerns. C++ output, including variant alternative order, is unchanged.

This cache relies on the existing emission boundary: checking and instantiation
planning have completed. Dependency extraction prepares semantic identity trees,
including root bodies and concrete arguments, and header lowering may assign IDs
in this serial phase. Source rendering only looks up IDs. Unknown/scratch types
bypass every ID-keyed cache rather than stamping shared input or sharing the -1
miss sentinel. Checking or re-preparing the same AST must not overlap rendering;
its semantic graph is still not deeply readonly at the language type level.


### Dependency fingerprint construction and native-header expansion

Module emission fingerprints retain the exact ordered source/dependency,
configuration, specialization/JSON and initialization inputs. Their input is
assembled with StringBuilder so each source record is appended without repeatedly
copying the growing prefix; the SHA-256 format and invalidation policy are unchanged.

Opaque native-header closure expands once for each defining-module/header pair
within a worldview. The length-prefixed key is marked before following sibling
and nominal import/export edges, including cycles. Visitation belongs to the
per-consumer WorldviewIndex, never the reusable graph index. Source declaration
ordering and concrete interface-key order remain part of the output contract.

These changes reduce serial planning costs; they do not freeze the graph or add
parallel emission. The immutable direct-dependency summaries described below now separate
foreign checked-AST traversal from consumer projection. Worker
selection sets, alias numbering and rendering caches must remain private. The preparation/rendering split and read-only identity/naming contracts below
describe how these remaining inputs are now prepared or isolated.

### Immutable declaration dependency summaries

`emitter-dependencies.do` owns checked-AST dependency extraction. Its builder
records ordered symbol and concrete-interface events, stopping at symbol edges
instead of recursively selecting declarations. Symbol events copy only scalar
module/name/key/native-header values; interface events contain a canonical key.
The completed event array and every event field are deeply readonly. No summary
retains an AST, Symbol or ResolvedType reference.

`indexWorldviewGraph` builds one foreign-surface summary per named declaration
and freezes the summary map before returning. The lifetime is one checked
graph: rebuild after semantic decorations or implementation sets change. Root
surfaces/bodies and concrete specialization arguments use the same extraction
rules but are collected separately per consumer. Foreign summaries include
defaults, alias annotations and enum values, excluding function/method bodies.

`emitter-worldview.do` owns recursive event replay, native-header closure,
consumer-local visited/selection sets, and dependency/source ordering. Replaying
a symbol immediately expands its declaration before continuing the event list;
this retains the original depth-first interface-key discovery order. Repeated
direct symbol/key events can be omitted because replay's corresponding visited
sets only grow. Final declaration order still comes from the source program.

This is a concrete immutable input boundary for future workers, not a claim
that WorldviewGraphIndex or emission as a whole is immutable. Module/AST lookup
tables, root traversal and native closure still read the checked graph. Semantic identity preparation and private C++ interning/lowering/rendering state
are described in the subsequent preparation and read-only-input sections.

### Preparation and source-rendering boundary

Module graph emission completes worldview/header preparation before any source
body is rendered. Headers are planned and rendered serially during preparation,
using a shared projection cache. Each pending module retains its readonly header
plan and rendered header text. Pending results retain their original output
positions, including reused modules and coverage IDs, preserving graph output
order.

`CppTypeRegistry.snapshot()` publishes readonly maps of immutable type nodes and
canonical render strings. Each source renderer creates a registry overlay over
that snapshot, with private interning and render maps. Inherited nodes retain
their IDs; new IDs start after the snapshot's node count. New IDs are local to
an overlay: never exchange those nodes or ID-keyed caches between siblings.
Snapshotting an overlay includes its inherited nodes without renumbering them.

Source rendering also owns its TypeLoweringGraph/session and JSON eligibility
cache. Source-local results never flow back into header preparation caches. The
preparation registry and its lowering cache are no longer the source renderer's
mutable workspace.

Pending jobs still carry checked AST references (but no retained emitter object).
Source rendering now consumes lookup-only semantic identity snapshots and explicit
immutable naming state as described below. Source rendering remains serial: the
checked AST contains mutable fields and cannot cross a Doof actor boundary.

### Read-only identity and namespace inputs

`ModuleNames` replaces emitter-names.do's process-global configuration and cache.
The compiler copies namespace mapping records and precomputes known module paths
before monomorphization. Missing paths are computed purely without inserting a
cache entry. Prefix boundaries, longest-prefix selection, sanitization, native
output roots and diagnostic path rules remain unchanged.

The same snapshot is passed through instantiation planning, module/header/source
contexts, C++ type lowering, native aliases, caller defaults, patterns, JSON and
Wasm support. Standalone helpers accept an explicit snapshot and default to an
empty mapping, never to the most recent compilation. C++ registry snapshots retain
the naming input, and a source overlay receives that same input explicitly.

`SemanticTypeIdentitySnapshot` contains only a readonly owner token and a lookup
method. It has no assignment path. Dependency builders can receive the mutable
identity preparation service during serial graph preparation; published dependency
summaries still contain no semantic references. Preparation visits semantic children
once, including recursive constraints. Source rendering receives only the snapshot.

A lookup miss returns -1, which all three lowering cache stages bypass. This covers
unprepared inputs and freshly reconstructed or specialized semantic objects without
assuming that equal C++ output implies semantic object identity. It is a deliberate
performance/correctness tradeoff: caches must never merge two unknown objects.

The two identified rendering-time shared writes are removed. Source workers still
require a deeply immutable source representation or an explicit owned-graph
transfer design. Read-only usage alone does not make mutable checked AST objects
transferable. No isolation exception is introduced for emission.

The opt-in header worker experiment was removed after its small rendering saving
and increased memory failed the simplicity test. Headers render serially through
the existing projection caches. Historical results remain in
[header worker measurements](archive/emission-2026-09-07.md#header-emission-workers).

### Semantic specialization boundary

`discoverInstantiations` consumes checked decorations and computes the existing
fixed point independently of C++ namespaces and spelling. `CheckedInstantiations`
contains semantic records, including interface implementations and JSON demands.
An ordered union of references to those same records preserves cross-kind naming
order. There is no duplicate immutable catalogue, transfer wrapper, or graph copy.

`nameInstantiations` assigns C++ names after discovery. Generic interface
implementors resolve by specialization key. Nonconvergence traces use semantic
keys. Wasm entry-point JSON demands are added before module emission through the
shared semantic traversal. The ordinary mutable checked AST remains the semantic
input; worker transfer is not an architectural requirement.

Per-module `module.prepare:<path>` and `module.render:<path>` timing entries expose
candidate worker costs. They are nested inside existing phase timings and must not
be added to their parents. `scripts/model-emission.py` models cold serial runs;
[the modelling report](archive/emission-2026-09-07.md#instantiation-catalogue-modelling) explains its limits.
