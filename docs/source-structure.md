# Source Structure

Production code and focused tests live together under `src/`.

This document is the vertical ownership map: read down a section to find the
file responsible for a particular operation. To follow a feature across
several layers, use the [horizontal architecture map](compiler-architecture.md).

## Ownership rules

- The public façade for a subsystem coordinates; focused modules implement its
  parts. Do not grow the façade into a parallel implementation.
- Syntax nodes in `ast.do` are decorated in place. `semantic.do` defines the
  resolved types and bindings stored on them.
- The checker decides meaning. The emitter consumes those decisions and must
  not recover them from names or syntax.
- Planning modules return deterministic values. Filesystem, network, and
  subprocess work stays in an explicitly named driver or acquisition boundary.
- Focused tests live in the adjacent `*.test.do`. Native representation,
  resource, packaging, and Apple-platform acceptance belongs under
  `tests/release-fixtures/`.

## Front end and graph orchestration

| File | Owns | Does not own |
| --- | --- | --- |
| `lexer.do` | Tokens, lexical scanning, token source spans, and typed-tag header/text lexical modes | Grammar or diagnostics about program meaning |
| `parser.do` | Parser façade and token cursor | Individual grammar families |
| `parser-declarations.do` | Declarations, imports, exports | Expressions, control flow, type grammar |
| `parser-statements.do` | Statements, control flow, case patterns | Declaration and expression internals |
| `parser-expressions.do` | Expressions, literals, precedence, and typed-tag desugaring into named calls | Type annotations |
| `parser-types.do` | Type annotation grammar | Type resolution |
| `ast.do` | Syntax node shapes, source spans, semantic decoration slots | Resolved-type definitions or checking policy |
| `resolver.do` | Logical module-path resolution, lazy source loading, source cache | Disk/package acquisition |
| `analyzer.do` | Main-thread module discovery, parallel parse scheduling, deterministic graph ordering, declaration collection, imports/re-exports, module symbols, named-type decoration | Lexical scopes or expression typing |
| `semantic.do` | Diagnostics, symbols, bindings, scopes, resolved-type records | Pass orchestration |
| `diagnostics.do` | Shared diagnostic severity queries | Creation of feature-specific diagnostics |
| `compiler.do` | Analyze → check all modules → graph validations → specialize → emit orchestration | Filesystem, package, or native compiler operations |
| `frontend-cache.do` | Versioned pointer-free frontend fingerprints, resolution probes, and module-output records | AST/checker serialization or filesystem access |
| `resource-state.do` | Versioned executable-resource source/output metadata and pure currentness checks | Filesystem traversal or copying |

## Checker

`checker.do` is the public façade and module-level coordinator. Its focused
modules own the following decisions:

| File | Responsibility |
| --- | --- |
| `checker-state.do` | Mutable per-run and per-module checker state |
| `checker-symbols.do` | Scope/binding operations, builtins, annotation resolution, symbol/declaration lookup |
| `checker-types.do` | Resolved-type construction, comparison, assignability, substitution, and display |
| `checker-resolution.do` | Type annotations, members, indexing, callable fields, and type-argument constraints |
| `checker-common.do` | State-aware diagnostics, expression type decoration, and centralized assignment-binding validation |
| `checker-statements.do` | Statements, declarations, scopes, returns, destructuring, and control-flow continuation |
| `checker-expressions.do` | Expression dispatch, operators, narrowing, assignment, and case expressions |
| `checker-calls.do` | Calls, positional/named construction, lambdas, generic calls, and actor-call boundaries |
| `checker-literals.do` | Contextual array and object literal inference |
| `checker-generics.do` | Generic inference and decorated call-target resolution |
| `checker-interfaces.do` | Structural conformance and closed-world implementation discovery |
| `checker-actor-boundary.do` | Deep immutability graph analysis for actor payloads and `readonly` fields |
| `checker-actor-lifecycle.do` | Conservative straight-line use-after-retire diagnostics |
| `ast-walk.do` | Shared shallow statement/expression traversal primitives for semantic and lowering passes |
| `checker-module-initialization.do` | Construction-only declarative initializer validation and direct-storage eligibility |
| `checker-isolation.do` | Graph-wide transitive mutable-global effect validation |
| `checker-validation.do` | Final graph walk proving the AST is decorated and safe to emit |
| `json-semantics.do` | Shared eligibility contract for generated JSON methods |

When a check produces information needed for lowering, add an explicit
decoration to `ast.do`, populate it in the owning checker module, require it in
`checker-validation.do`, and consume it in the focused emitter.

Field mutability provenance is carried from the AST into semantic bindings.
Implicit, explicit member, destructuring, and yield-block writes must use the
shared assignment validator rather than reconstructing field policy in an
emitter or individual expression branch.

## C++ emission

| File | Responsibility |
| --- | --- |
| `emitter-context.do` | Graph-wide nominal/method context and per-module emission state |
| `emitter-names.do` | Stable C++ namespaces, filenames, and diagnostic paths from logical module identity |
| `emitter-monomorphize.do` | Fixed-point discovery of concrete generic instantiations and direction-specific generated-JSON demand |
| `emitter-worldview.do` | Consumer-projected declaration closure from checked symbol/type uses |
| `emitter-module.do` | Module graph orchestration, transitive emission fingerprints, and header/source pairing |
| `emitter-header.do` | Multi-namespace worldview declaration ordering and rendering |
| `string-builder.do` | Runtime-backed append-only construction for large generated text |
| `emitter-decl.do` | Functions, classes, top-level declarations, signatures, and definitions |
| `emitter-stmt.do` | Blocks and statement/control-flow lowering |
| `emitter-expr.do` | Single expression dispatch façade |
| `emitter-expr-ops.do` | Assignment, identifiers, operators, members, indexing, and `as` |
| `emitter-expr-calls.do` | Calls, native construction, and positional/named class construction |
| `emitter-expr-literals.do` | Literal, array, object, tuple, and string lowering |
| `emitter-expr-control.do` | Conditional, case, catch, dot-shorthand, and yield-block expressions |
| `emitter-expr-lambda.do` | Lambda capture analysis, mutable capture boxing, and callback lowering |
| `emitter-expr-actor.do` | Actors, promises, async calls, and retirement |
| `emitter-expr-utils.do` | Decorated-type requirements and contextual/variant promotion helpers |
| `emitter-case-pattern.do` | Type-pattern lowering shared by statement and expression cases |
| `emitter-types.do` | C++ representation choices for resolved Doof types |
| `emitter-json.do` | Demand-gated generated JSON reads, writes, and interface dispatch |
| `emitter-metadata.do` | Reflection metadata, JSON Schema, and JSON invocation |
| `emitter-wasm.do` | JSON-over-C-ABI WebAssembly wrapper generation |
| `emitter-project.do` | Generated project shape and reached-package native input collation |

`runtime/doof_runtime.h` owns reusable generated-program behavior. It is not a
place to hide a missing checker rule or an emitter decision.

Async-block capture decoration and transfer restrictions belong to
`checker-async.do`; transitive callable effects remain owned by
`checker-isolation.do`. `emitter-expr-actor.do` lowers actor async calls,
decorated isolated calls, and async blocks through the runtime's
scheduling-policy-neutral submission boundary. `runtime/doof_runtime.h` owns
the process-wide bounded scheduler, CPU-token release around blocking waits,
and per-actor serial mailbox admission; compiler lowering does not select
threads or reconstruct scheduling policy.

## Packages, native builds, and command boundaries

| File | Responsibility |
| --- | --- |
| `cli.do` | Pure command-line parsing and request model |
| `project.do` | Requested entry, manifest discovery, and project settings |
| `package-manifest.do` | `doof.json` validation and normalized package/native models |
| `std-catalog.do` | Immutable standard-package catalog parsing and canonical URLs |
| `module-acquisition.do` | Logical module prefix → acquired disk root mapping |
| `package-acquisition.do` | Workspace-local exact Git package acquisition |
| `dependency-policy.do` | Root-owned conflict selection and transitive input policy |
| `external-dependency.do` | External archive/Git acquisition, sentinels, and build commands |
| `provenance.do` | Deterministic reached-input and native-build provenance |
| `pkg-config.do` | Pure interpretation of bounded `pkg-config` results |
| `native-build.do` | Pure GCC-compatible/MSVC support-file, PCH, compile, and link task planning |
| `native-build-state.do` | Versioned incremental state plus Make/MSVC dependency parsing |
| `native-build-driver.do` | Native compiler processes, fingerprints, dependency signatures, PCH/object/link execution |
| `test-runner.do` | Pure test discovery, grouping, harness generation, and coverage reports |
| `wasm-test-runner.do` | Pure Apple JavaScriptCore runner build and per-test invocation plans |
| `run-command.do` | Pure invocation plans for built artifacts |
| `profile-command.do` | Pure macOS xctrace capture and completed-trace open plans |
| `macos-app.do` / `ios-app.do` | Deterministic bundle metadata, signing arguments, and platform plans |
| `macos-app-driver.do` / `ios-app-driver.do` | Bundle materialization and Apple tool execution |
| `ios-device.do` | Physical-device discovery, provisioning selection, signing, install, and launch boundary |
| `driver.do` | Top-level CLI workflow, filesystem materialization, source-loader adaptation, and delegation to focused boundaries |

If `driver.do` starts making a reusable semantic or planning decision, extract
that decision into a pure owning module and keep only environment adaptation in
the driver.

Other maintained inputs:

- `runtime/doof_runtime.h` — canonical generated-program runtime
- `runtime/doof_wasm_test_runner_apple.swift` — bounded JavaScriptCore/WASI host for Wasm test commands
- `resources/std-catalog.json` — embedded exact standard-package catalog
- `tools/update-std-catalog.do` — catalog maintenance tool
- `tests/release-fixtures/` — native and platform acceptance packages
- `bootstrap/macos-arm64/generated/` — shared generated stage-0 trust root in its legacy location; host build scripts own target-native source selection

Primitive string parsing is a standard-library concern owned by `std/parse`.
The checker provides only an actionable migration diagnostic for removed
numeric `.parse` intrinsics; the emitter and runtime contain no parsing
lowering or `ParseError` compatibility implementation.

Keep files focused and make ownership changes explicit in this document.
