# `none` unification implementation plan

## Goal

Replace Doof's source-level `void` and `null` concepts with one unit/absence
type and value spelled `none`. During migration, `void` and `null` remain
accepted as deprecated aliases and produce actionable warnings.

The unification is a source-language and semantic-model change. It does not
rename concepts owned by external formats or the native backend: generated C++
continues to use `void`, and JSON continues to encode absence as `null`.

## Canonical semantics

- `none` is both a type and the single value of that type.
- `T | none` is the canonical optional type.
- A function returning `none` may fall through, use `return`, or use
  `return none`.
- Calls returning `none` may be used as unit-valued expressions.
- `Result<none, E>`, `Promise<none>`, and callbacks returning `none` retain
  their payloadless behavior.
- `Success()` and bare statement-level `try` remain the canonical forms for a
  payloadless success channel.
- `try?` remains invalid for `Result<none, E>` because success and failure
  would both collapse to `none`.
- `none` is assignable to `JsonValue` and serializes as JSON `null`.
- `??`, `??=`, `?.`, postfix `!`, declaration-`else`, `as`, and case patterns
  use `none` as their absence member without changing operator spelling.
- The legacy spellings `void` and `null` canonicalize to `none` before
  emission. Their use produces a warning with a source span and replacement.

## Lowering contract

One semantic `NoneType` has position-dependent native lowering. The emitter
must consume the checker's decorated types and the syntactic position rather
than reconstructing a distinction between legacy spellings.

| Checked Doof position | Native representation |
| --- | --- |
| Function or callback return | C++ `void` |
| `Result<none, E>` payload | Existing `Result<void, E>` specialization |
| `Promise<none>` payload | Existing `Promise<void>` specialization |
| Standalone `none` value | `std::monostate` |
| Optional primitive or struct | `std::optional<T>` |
| Optional class or collection | Existing nullable pointer representation |
| General union absence arm | `std::monostate` |
| `JsonValue` | JSON `null` |
| Metadata and WASM absent result | JSON `null` |

Dedicated helpers such as `emitReturnType` and `emitResultPayloadType` should
make these position rules explicit. A generic `emitType(NoneType)` should not
silently choose C++ `void`.

## Delivery stages

### 1. Make warnings non-fatal

- Distinguish error diagnostics from warning diagnostics in compiler
  orchestration.
- Continue checking and emission when only warnings are present.
- Print warnings in the CLI while preserving a successful exit status.
- Cover warning-only and mixed warning/error compilations.

This is a prerequisite for deprecation warnings; the current compiler stops on
every diagnostic regardless of severity.

### 2. Introduce syntax using bootstrap-compatible compiler source

- Add a `none` keyword token.
- Accept `none` in type and expression positions.
- Introduce `NoneLiteral` and retain source-spelling provenance for legacy
  literals.
- Preserve legacy `void` and `null` tokens long enough to diagnose them.
- Add lexer and parser tests for canonical and legacy spellings.

The implementation source in this stage must still use syntax understood by
the checked-in bootstrap compiler.

### 3. Canonicalize the semantic model

- Replace `NullType` and `VoidType` with `NoneType`.
- Add `noneType()` and update type naming, equality, union normalization,
  assignability, substitution, and generic inference.
- Replace null-specific helpers with `nonNoneType` and `hasNoneMember`.
- Update function completion, return checking, JSON assignability, Results,
  optional operators, narrowing, patterns, async, actors, and reflection.
- Ensure mixed legacy unions such as `T | null | void | none` normalize to
  `T | none` while reporting each deprecated spelling.

### 4. Update lowering without changing ABI or wire formats

- Add position-aware `none` lowering.
- Update declarations, lambdas, Results, Promises, native imports, metadata,
  WASM, JSON, case patterns, and optional representations.
- Keep generated C++ and externally visible JSON behavior stable wherever
  possible.
- Add emitter and compile/run regressions across primitive, struct, class,
  collection, interface, recursive AST, Result, and Promise shapes.

### 5. Bootstrap the new compiler

1. Build the compiler that accepts `none` while its own source still uses
   legacy spellings.
2. Run the release workflow and verify the B5/B6 byte-for-byte fixed point.
3. Refresh the reviewed generated bootstrap snapshot.
4. Only then migrate compiler source to `none`.
5. Refresh and verify the bootstrap again after first-party migration.

Generated bootstrap C++ must never be edited by hand.

### 6. Migrate first-party source

Use a token-aware migration rather than global text replacement, in this
order:

1. compiler modules and focused tests;
2. standard packages and native catalog declarations;
3. samples and compiler fixtures;
4. the language specification and architecture documentation;
5. the Doof language skill;
6. external packages over later releases.

The migration must not rewrite C++ `void`, JSON `null`, JSON Schema `"null"`,
or unrelated prose and string values.

### 7. Deprecation lifecycle

- Release N: `none` is supported and `void`/`null` warn.
- Release N+1: all first-party Doof source uses `none`; aliases remain.
- A later major release may remove the aliases after ecosystem migration.
- JSON `null` support remains permanent.

## Verification matrix

Focused `*.test.do` coverage belongs beside every changed compiler module and
must include:

- canonical parsing in type, literal, union, generic, and pattern positions;
- warning text, severity, and exact spans for both legacy spellings;
- warning-only compilation proceeding to emission;
- mixed warnings and errors still blocking emission;
- function fallthrough, bare return, explicit `return none`, and inferred
  returns;
- optional assignment and every optional/narrowing operator;
- `Result<none, E>`, `Failure<none>`, `Promise<none>`, `Success()`, bare `try`,
  and rejected `try?`;
- callbacks, native declarations, async functions, actors, metadata, and WASM;
- JSON values and schemas preserving external `null` spelling;
- mixed `void`/`null`/`none` union normalization;
- representative emitted C++ retaining compatible representations.

Run `./scripts/test.sh` for normal stages. Run `./scripts/release.sh` and verify
the B5/B6 fixed point for bootstrap refreshes.

## Implementation status

- [x] Warning-only compilations proceed to emission.
- [x] `none` syntax is accepted.
- [x] `NoneType` is the sole semantic absence type.
- [x] Position-aware native lowering is complete.
- [x] Legacy aliases warn without failing builds.
- [x] Pre-migration bootstrap fixed point is refreshed and verified.
- [x] Compiler modules and focused tests use canonical `none`.
- [x] Compiler-source bootstrap fixed point is refreshed and verified.
- [x] First-party Doof source is migrated.
- [x] Specification and language skill are updated.
- [x] Final bootstrap fixed point after all first-party migration is refreshed and verified.
