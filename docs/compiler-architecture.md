# Compiler Architecture

This document is the horizontal concept map: it shows how information crosses
phase and file boundaries. For a file-by-file ownership index, see
[source structure](source-structure.md).

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
| `emitter-monomorphize.do` | concrete whole-program instantiation plan | module/header/type emitters |
| `emitter-module.do` | generated header/source pairs and graph support | `emitter-project.do` |
| `emitter-project.do` | generated project plus normalized native inputs | native build planner and driver |
| `native-build.do` | deterministic PCH/compile/link tasks | `native-build-driver.do` |

`compiler.do` coordinates the pure graph pipeline. `driver.do` adapts CLI,
filesystem, acquired-package, test, app, and process boundaries to it. Source
loading is inverted through `SourceLoader`, so the analyzer discovers the
transitive graph without gaining filesystem ownership.

## Horizontal concepts

Each row names the authoritative path for a concept. A change normally follows
the row from left to right.

| Concept | Established or modeled | Checked or decorated | Consumed or executed |
| --- | --- | --- | --- |
| Source identity and diagnostics | token/AST spans in `lexer.do` and `ast.do`; diagnostic records in `semantic.do` | analyzer and focused checker module attach semantic spans | `driver.do` formats bounded diagnostic output |
| Modules and names | `resolver.do` resolves logical paths; `analyzer.do` owns imports, exports, symbols, and defining-module identity | `checker-symbols.do` resolves lexical and module bindings | `emitter-names.do` derives stable C++ identity; module/header emitters use it |
| Types and assignability | resolved type records in `semantic.do`; shared operations in `checker-types.do` | focused checker modules decorate annotations and expressions | `emitter-types.do` chooses representation; expression/declaration emitters require decorations |
| Calls and dispatch | declarations and symbols from analysis | `checker-calls.do`, `checker-generics.do`, and `checker-interfaces.do` choose targets and substitutions | `emitter-expr-calls.do` lowers the recorded target |
| Control flow and narrowing | statement/expression/pattern AST in parser modules | `checker-statements.do` and `checker-expressions.do` determine continuation, exhaustiveness, and narrowed bindings | `emitter-stmt.do`, `emitter-expr-control.do`, and `emitter-case-pattern.do` lower those decisions |
| Generics | type parameters in AST and resolved types | checker infers/substitutes concrete arguments | `emitter-monomorphize.do` discovers a fixed point; emitters output concrete forms |
| Interfaces | interface/class declarations and resolved nominal types | `checker-interfaces.do` validates structural conformance and discovers the closed implementor set | `emitter-types.do` and declaration/JSON emitters lower interface variants |
| JSON and reflection | annotations/declarations in AST; eligibility in `json-semantics.do` | checker advertises only supported synthetic members and records metadata demand | `emitter-json.do`, `emitter-metadata.do`, and `emitter-wasm.do` generate definitions/adapters |
| Actors and isolation | actor/promise types and actor syntax | `checker-actor-boundary.do`, `checker-actor-lifecycle.do`, and `checker-isolation.do` own call boundaries, retirement diagnostics, and graph-wide effects | `emitter-expr-actor.do` and lambda/call emitters lower checked operations; the bounded runtime scheduler executes isolated function calls, async blocks, and serial actor messages |
| Closures and mutable capture | lambda/binding AST and checker bindings | checker establishes callable types and resolved captures | `emitter-expr-lambda.do` finds escaping captures and boxes mutable storage |
| Module initialization | top-level checked declarations/statements and compiler entry mode | `checker-module-initialization.do` validates construction-only expressions and direct storage | `emitter-module.do`, `emitter-header.do`, and `emitter-decl.do` emit direct storage and graph-ordered execution |
| Packages and reproducible inputs | manifests/catalog in `package-manifest.do` and `std-catalog.do` | `dependency-policy.do` selects exact reached inputs | acquisition modules materialize; `provenance.do` records; `emitter-project.do` collates |
| Incremental native builds | normalized native plan and emitted modules | `native-build.do` creates stable tasks; `pkg-config.do` normalizes flags | `native-build-driver.do` fingerprints arguments/dependencies, persists state, and runs dirty work |
| Tests, mocks, and coverage | `test-runner.do` discovers tests and generates harnesses | analyzer rewrites mock imports; emitter inserts stable coverage markers | driver groups, builds, isolates, runs, merges, and renders reports |

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

Declarative module values use direct typed C++ storage. Safe scalar constants
retain C++ constant initialization; constructed values are assigned by one
plain generated initializer for each module that has deferred assignments.
Stateless and constant-only modules emit no initializer. The entry emitter
computes a deterministic dependency-first order and calls those initializers
after installing the application actor scope; initializer functions contain no
per-module lifecycle state. Native entry scripts retain their separate
source-order runner. Standalone WebAssembly exposes the graph protocol through
`doof_initialize` after the host calls Emscripten `_initialize`.

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

- `package-acquisition.do` and `external-dependency.do` for network/disk input
  acquisition;
- `native-build-driver.do` for compiler/linker subprocesses and incremental
  build state;
- Apple `*-driver.do` and `ios-device.do` modules for platform tools;
- `driver.do` for top-level workflow, filesystem materialization, and command
  routing.

This separation keeps semantic tests in memory and planning tests
deterministic.

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
