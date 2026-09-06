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
| `ast.do` | Syntax node shapes, source spans, semantic decoration slots including checked member selections | Resolved-type definitions or checking policy |
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
| `checker-symbols.do` | Scope/binding operations, builtins, shared declaration signatures, symbol/declaration lookup |
| `checker-types.do` | Resolved-type construction, comparison, assignability, substitution, interface-bound receiver views, and display |
| `checker-annotations.do` | One annotation resolver for provisional signatures and checked types; builtin arity, alias expansion, constraints, and annotation decoration |
| `checker-resolution.do` | Bound-aware member selections (type, declaration, owner, static/field flags), assignment bindings, indexing, and annotation API forwarding |
| `checker-common.do` | State-aware diagnostics, expression type decoration, and centralized assignment-binding validation |
| `checker-statements.do` | Statements, declarations, scopes, returns, destructuring, enum backing-value resolution, and control-flow continuation |
| `checker-try.do` | Result propagation boundaries, error compatibility, and success declaration checking |
| `checker-numeric.do` | Numeric bound membership, operator capabilities, and correlated promotion |
| `checker-inference.do` | Contextual path validation and common-type inference; only optional unions are synthesized for value paths |
| `checker-expressions.do` | Expression dispatch, operators, narrowing, assignment, and case expressions |
| `checker-calls.do` | Calls, lambdas, generic inference/application, and actor-call boundaries |
| `checker-arguments.do` | Shared positional/named parameter mapping, contextual value checking, argument diagnostics, and required/default/spread validation |
| `checker-construction.do` | Retained specialized construction plans for ordinary, named, contextual, and actor construction; shared field validation and visibility |
| `checker-properties.do` | Shorthand/explicit property decoration, contextual assignability, and fixed literal field validation |
| `checker-literals.do` | Contextual array and object literal inference |
| `checker-generics.do` | Structural generic type-argument inference |
| `checker-interfaces.do` | Structural conformance and closed-world implementation discovery |
| `checker-actor-boundary.do` | Deep immutability graph analysis for actor payloads and `readonly` fields |
| `checker-actor-lifecycle.do` | Conservative straight-line use-after-retire diagnostics |
| `ast-walk.do` | Shared shallow traversal and explicit preorder expression-tree collection for semantic and lowering passes |
| `checker-module-initialization.do` | Construction-only declarative initializer validation and direct-storage eligibility |
| `checker-async.do` | One recursive async boundary walk with direction-specific handle rules; capture decoration |
| `checker-isolation.do` | Graph-wide transitive mutable-global effect validation |
| `checker-validation.do` | Final graph walk proving the AST is decorated and safe to emit |
| `json-semantics.do` | Shared eligibility contract for generated JSON methods |

When a check produces information needed for lowering, add an explicit
decoration to `ast.do`, populate it in the owning checker module, require it in
`checker-validation.do`, and consume it in the focused emitter.

Annotation predeclaration and full checking run the same resolver. Provisional
signatures use a disposable diagnostic context and do not decorate the AST or
register concrete interfaces; declaration checking owns those effects and
dependent constraint validation. Alias expansion tracks active declarations to
reject cycles. Function and method signatures share parameter construction,
with owner and method type parameters supplied explicitly.

Member selection is recorded once while checking the receiver, including the
underlying owner of weak and actor access and the exposed contract of an
interface bound. Calls consume that selection; graph validation rejects missing
member selections or inconsistent call targets. Type-only member queries use the
same resolver. Synthetic members and callable fields have no method declaration.
Distinct union method declarations do not select an arbitrary arm's defaults.

Constructor planning specializes the factory signature against the checked owner
before any syntax-specific argument adapter runs. Ordinary calls, constructors,
and actors share argument validation; actor payload restrictions remain a
separate boundary check. Explicit construction and contextual class literals
share property/field validation after union shape selection. `CheckedConstruction`
retains the owner, declaration, factory, specialized signature, and ordered default
expressions on the AST. Emission and graph validation consume this plan without
rescanning constructors or rechecking whether construction occurs inside a factory.
Actor construction shares argument/default lowering while retaining actor storage.

Async capture and result validation share container and nominal-type recursion.
Directional handle restrictions remain explicit: accepting an actor handle as a
capture does not imply that returning that handle from async is permitted.

Expression nodes explicitly declare their writable `resolvedType` decorations
with `let`, including writes made through the `Expression` union.

Field mutability provenance is carried from the AST into semantic bindings.
Implicit, explicit member, destructuring, and yield-block writes must use the
shared assignment validator rather than reconstructing field policy in an
emitter or individual expression branch.

## C++ emission

| File | Responsibility |
| --- | --- |
| `emitter-context.do` | Graph-wide nominal/method context and per-module emission state |
| `emitter-names.do` | Stable C++ namespaces, filenames, and diagnostic paths from logical module identity; shared C++ keyword escaping for namespace and value identifiers |
| `emitter-monomorphize.do` | Fixed-point discovery of concrete generic instantiations and direction-specific generated-JSON demand |
| `emitter-worldview.do` | Consumer-projected declaration closure from checked symbol/type uses and concrete arguments of module-owned generic specializations |
| `emitter-module.do` | Module graph orchestration, transitive emission fingerprints, and header/source pairing |
| `emitter-header.do` | Multi-namespace worldview declaration ordering, enum identity/helper generation, and rendering |
| `string-builder.do` | Runtime-backed append-only construction for large generated text |
| `emitter-decl.do` | Shared function/method body and return boundaries, signatures, class declarations, top-level definitions, and field equality operators for structs |
| `emitter-stmt.do` | Blocks and statement/control-flow lowering |
| `emitter-expr.do` | Single expression dispatch façade; contextual conversion of checked unit expressions and native void calls to stored unit values while preserving evaluation |
| `emitter-expr-ops.do` | Assignment, identifiers, operators, members, indexing, and `as`; equality uses checked none types and unit unwraps produce stored unit values |
| `emitter-expr-calls.do` | Call target selection, runtime member dispatch, and positional Result payload construction |
| `emitter-call-arguments.do` | Shared named/positional argument ordering, checked contextual argument types, and call-site default emission for direct and dispatched calls |
| `emitter-construction.do` | Positional, named, contextual, and actor construction from checked plans; shared argument/default lowering, owner specialization, and spread handling |
| `emitter-expr-literals.do` | Literal, array, object, tuple, and string lowering; shared contextual absence values for literals and catch initialization |
| `emitter-expr-control.do` | Conditional, case, catch, dot-shorthand, and yield-block expressions |
| `emitter-expr-lambda.do` | Lambda capture analysis, mutable capture boxing, and callback lowering |
| `emitter-expr-actor.do` | Actors, promises, async calls, and retirement |
| `emitter-expr-utils.do` | Decorated-type requirements, shared shorthand property emission, specialized expression-return boundaries, and model-backed nullable queries |
| `emitter-case-pattern.do` | Type-pattern lowering shared by statement and expression cases; natural nullable absence patterns test for null, and absence bindings use the unit carrier |
| `emitter-carriers.do` | Pure specialized-type classification for value, return, payload, nullable storage, and explicit absence |
| `emitter-carrier-values.do` | Shared absence construction and native carrier conversion, with exactly-once evaluation |
| `emitter-carrier-native.test.do` | Compiles current-source emitter output and executes the durable native carrier matrix in the normal suite |
| `emitter-types.do` | C++ type spelling and generic specialization using the shared carrier classification |
| `emitter-json.do` | Demand-gated generated JSON reads, writes, enum backing values, paths, and interface dispatch; unit decoding validates null and all nested containers validate shape before access |
| `emitter-metadata.do` | Reflection metadata, backing-value JSON Schema, and JSON invocation |
| `emitter-wasm.do` | JSON-over-C-ABI WebAssembly wrapper generation |
| `emitter-project.do` | Generated project shape and reached-package native input collation |

Function and method definitions share capture/context setup and a specialized return
boundary. Both expression and block bodies of `never` callables retain the
non-returning fallback. Class construction omits static and literal-valued fields
from stored-field arguments; literal-valued fields initialize in declarations.
Contextual object defaults use the same construction-site attribution and owner
substitution as explicit construction. The native emission-consolidation fixture
checks these boundaries alongside contextual callback arguments through unions.

The [native carrier model](native-carriers.md) defines representation and conversion
invariants and its native test matrix.

`runtime/doof_runtime.h` owns reusable generated-program behavior. It is not a
place to hide a missing checker rule or an emitter decision.
Its nullable weak-pointer helpers distinguish an empty pointer from an expired
owner and preserve that owner when unwrapping. Map mutation emission supplies
the checked key and value template types so absence tokens cannot change native
template deduction.

Conditional expressions with nullable, variant, or JSON carriers lower through
an explicitly typed lambda so each selected branch converts to the checked
result type. Lambda capture analysis traverses destructuring initializers;
statement lowering boxes captured mutable destructured locals just like ordinary
`let` locals, while evaluating the destructuring source only once.

Lambda lowering uses owned init-captures and mutable C++ closure bodies for
struct values captured by value, including concrete generic struct arguments.
This permits checker-approved struct method calls through nested closures;
captured `let` bindings continue to share their boxed storage. Doof binding and
field immutability remain checker responsibilities.

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
| `project-build-lock.do` | Stable project lock path, directory creation, blocking OS lock acquisition, and contention diagnostics |
| `package-manifest.do` | `doof.json` validation and normalized package/native models |
| `stdlib-bundle.do` | Seekable archive validation and reached-package materialization |
| `module-acquisition.do` | Logical module prefix → acquired disk root mapping |
| `stdlib-preparation.do` | Bounded preparation commands for reached standard packages |
| `pkg-config.do` | Pure interpretation of bounded `pkg-config` results |
| `native-build.do` | Pure GCC-compatible/MSVC support-file, PCH, compile, and link task planning |
| `native-build-state.do` | Versioned incremental state plus Make/MSVC dependency parsing |
| `native-build-driver.do` | Native compiler processes, fingerprints, dependency signatures, PCH/object/link execution |
| `test-runner.do` | Pure test discovery, grouping, harness generation, coverage reports, and relative URL-safe coverage page paths |
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
- `tools/stdlib-bundle.do` — deterministic curated stdlib bundle builder and strict release verifier
- `build/doof-stdlib.tar` — generated compiler resource, published beside `doof`
- `tests/release-fixtures/` — native and platform acceptance packages
- `bootstrap/macos-arm64/generated/` — shared generated stage-0 trust root in its legacy location; host build scripts own target-native source selection

Primitive string parsing is a standard-library concern owned by `std/parse`.
The checker provides only an actionable migration diagnostic for removed
numeric `.parse` intrinsics; the emitter and runtime contain no parsing
lowering or `ParseError` compatibility implementation.

Keep files focused and make ownership changes explicit in this document.

Coverage source-page paths are mapped component by component inside the report's
`*_files` directory. Absolute paths receive an `_absolute` prefix, parent
components become `_external`, and punctuation or marker-name collisions are
escaped. The same mapping drives summary links and filesystem writes; the driver
creates the index directory even for an empty report.
