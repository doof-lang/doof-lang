# Native carrier model

Doof has one semantic `none` type. Its C++ representation depends on position.
The checker owns assignability and narrowing; the emitter receives decorated
bindings and types, specializes generics, then chooses a native carrier.

## Ownership

- `src/emitter-carriers.do` is the pure representation classifier. It owns
  union flattening, explicit absence membership, natural nullable members,
  optional wrapping, and value/return/payload positions. It imports no AST,
  emitter context, C++ renderer, or checker.
- `src/emitter-types.do` spells the classified types and nominal names.
- `src/emitter-carrier-values.do` emits absence and conversions. It evaluates
  source expressions once and maps absence into the actual target arm.
- `src/emitter-expr.do` marks a native call result as a return-position source;
  other expression producers supply value-position carriers. Shared property
  emission routes shorthand bindings through that same expression boundary.
- `emitExpressionReturn` is the shared exit boundary for functions, methods,
  lambdas, and return statements. It specializes before discarding unit values
  for a void ABI. Result and Promise payloads use the payload position.
- JSON eligibility remains a semantic contract in `json-semantics.do`. JSON
  reading/writing uses the carrier classifier for optional storage. Wire null
  validation and container shape validation happen recursively before access.
- Runtime helpers implement operations on C++ carrier families. They do not
  decide source-language assignability.

## Representation table

| Checked type or position | Native carrier | Absence |
| --- | --- | --- |
| `none` value | `std::monostate` | `std::monostate{}` |
| `none` return or Result/Promise payload | `void` | no returned/payload value |
| Class, array, map, or set plus `none` | shared pointer | null pointer |
| Primitive, enum, or struct plus `none` | `std::optional<T>` | empty optional |
| Weak pointer plus `none` | weak pointer | empty ownership identity |
| Tuple, callback, Result, or multi-arm union plus `none` | variant | monostate arm |
| `JsonValue` | JSON storage | JSON null |

The descriptor distinguishes a native variant from an explicit nullable union.
For example, a Result is physically a variant but may be one indivisible arm
inside another union. Widening must preserve that arm when the target contains
it; only otherwise may it visit and widen the source alternatives.

Weak expiration is distinct from absence: an expired reference retains its
ownership identity and must still produce a weak-reference failure on access.
Neither widening nor unwrapping locks it or erases that identity.

## Conversion invariants

1. Specialize checked source and target types before selecting a carrier.
2. A value-position unit is never native `void`. A void call is evaluated once
   and then materializes unit, including inside tuples or other expressions.
3. A nullable pointer/optional widened into a variant must test absence before
   constructing the present arm. A null pointer in a class arm is not the
   variant's monostate arm.
4. Variant conversion uses the concrete target type. It preserves nested
   Result/variant arms and handles reordered or wider alternatives.
5. Equality and patterns inspect semantic unit/absence, not only literal AST
   syntax. Reads, writes, calls, and returns share the same conversion path.
6. Runtime template argument deduction cannot redefine checked types. Map
   mutation supplies explicit key and value template arguments.
7. Unsupported absence requests fail at the compiler invariant boundary;
   they do not silently fall back to an unrelated null pointer.

## Verification

`src/emitter-carriers.test.do` tests positions and representation families;
`src/emitter-carrier-values.test.do` tests conversion decisions and rejection.
`src/emitter-carrier-native.test.do` reads
`tests/fixtures/none-carriers/main.do`, runs the **current source compiler**
through checking/emission, compiles the resulting C++ with the canonical runtime,
and executes it. It runs in the normal `./scripts/test.sh` suite. It does not
invoke an installed compiler to emit the fixture and cannot accidentally test a
stale emitter. Failed native artifacts remain under the system temporary
`doof-native-carrier-matrix` directory for diagnosis.

The native matrix spans nullable carrier families through generic calls,
returns, assignment, equality, arrays, maps, union widening, unit calls and
unwraps, callbacks, weak lifetimes, and valid/invalid nested JSON containers.
It is a maintained interaction matrix, not a claim to cover every possible
program. Add a row and a native assertion whenever a new carrier or boundary
is introduced. Bootstrap fixed-point and platform release gates remain separate.
