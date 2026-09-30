# Spec Conformance Review (October 2026)

This review compared `spec/` with the compiler at `1213f16`. About 200 small
probe programs were written from spec claims and examples, then run through
`dist/doof check` and `dist/doof run`.

The seven "group 1" defects fixed alongside this document are listed first for
reference. Everything else below is open.

## Fixed with this review

| Defect | Fix |
|---|---|
| Loop `then` clauses were parsed and checked but never emitted, so they never ran. | `emitter-stmt.do` emits the clause after the loop; breaks that exit a `then` loop jump past it. |
| `??=` was copied verbatim into C++. | `emitter-expr-ops.do` lowers it lazily for nullable and Result targets. |
| `Map.delete(k)` emitted `->delete_(...)`. | `emitter-expr-calls.do` lowers it to `erase`. |
| `if c then Failure(..) else Success(..)` produced an invalid C++ ternary. | Result-typed if-expressions convert each arm (`emitter-expr-control.do`). |
| `weakRef?.method()` on a `none` method emitted `Success<void>{void{}}`. | The absent-reference path emits `Success<void>{}`. |
| A trailing lambda on a value-returning callback passed the checker and failed in C++; `return` inside a trailing lambda was unchecked. | Both are now checker errors. |
| `struct S implements I` and assigning a struct to an interface passed the checker and failed in C++. | Both are rejected. Structs still satisfy interface generic bounds. |

Reassigning a Result-typed `let` (`data = load()`) was also rejected with
"Result value must be handled". It is now accepted, because `??=` on Result
targets depends on it.

## How to read the recommendations

Each open item carries one of three recommendations:

- **Implement**: the spec describes the intended language. Change the compiler.
- **Spec**: the compiler's behavior is reasonable. Change the spec to match it.
- **Decide**: both are defensible. Someone needs to choose before either side changes.

Items are ordered by how much they affect users.

---

## A. The compiler lacks or rejects documented features

### A1. Literal-valued fields — **Decide (high priority)**

- **Spec** (ch. 2, 7, 12): `kind: "Success"` is the canonical form. `kind := "Success"` is deprecated. Field `const` is deprecated.
- **Compiler**:
  - Only `const kind = "circle"` parses, and it gives no deprecation warning.
  - `kind: "a"` fails with "Expected a type name". `kind := "a"` also fails.
  - JSON diagnostics still recommend `const kind = "variant"`.
- **Test gap**: `checker.test.do:188` asserts that `kind: "point"` is valid. It only passes because its `checked()` helper doesn't surface parse errors.

Discriminated unions are central to the spec, so this gap affects many examples.

**Recommendation**: implement `kind: "literal"`, since it matches the spec and the literal type sits in type position. Then warn on field `const`, update the JSON diagnostic text, and make the checker test helpers fail on parse diagnostics.

### A2. Enum-valued discriminator fields — **Implement** (after A1)

`kind: ShapeKind.Circle` doesn't parse (ch. 2 "Enums as Union
Discriminators"). This belongs in the same literal-type work as A1.

### A3. Positional literals don't construct classes — **Decide**

The spec (ch. 2, 7) says `(1.0, 2.0)` constructs `Point` when the expected type
is a class. The compiler always builds a Tuple, so every one of these fails:

- `draw((1.0, 2.0))` (argument)
- `let p: Point = (…)` (annotation)
- `return (…)` (return value)
- `[(1.0, 2.0)]` for `Point[]` (array element)
- `verts.push((…))`
- `Line ((0.0, 0.0), (1.0, 1.0))` (nested)

**Recommendation**: implement it if positional construction by context is still wanted. Otherwise remove the claims from ch. 2 and ch. 7. `Point(1.0, 2.0)` already covers the need, so removing them is the cheaper option.

### A4. `Array<T>` and `ReadonlyArray<T>` — **Implement**

- Both are unknown types.
- `readonly Array<T>` is rewritten to `ReadonlyArray` in `parser-types.do` and then fails.
- Spec ch. 2 and ch. 3 list both names.

**Recommendation**: add both to the builtin types in `analyzer.do` and resolve them as aliases of `T[]` and `readonly T[]`.

### A5. Result helper methods — **Implement**

Only `isSuccess`, `isFailure` and `unwrapOr` exist. These are missing:

- `map`, `mapError`, `andThen`, `orElse`
- `unwrapOrElse`, `ok`, `err`

Ch. 9 and ch. 13 document all of them. If they're deferred, mark them as planned in the spec.

### A6. `!.` doesn't unwrap Results — **Implement**

`loadUser()!.email` fails with `Result<User, string> has no member "email"`.
Ch. 5 and ch. 9 specify it, and postfix `!` already unwraps Results.

### A7. Array callback conventions — **Decide**

- Callbacks receive only `it`, with no `index`.
- `forEach`, `find`, `reduce`, `reduceRight` and `sort` don't exist.
- Ch. 4 ("Standard Library Conventions", "Practical Usage") documents all of them, and its trailing-lambda examples use `forEach`. The ch. 2 method table does not.

**Recommendation**: implement `forEach`, `find` and `reduce`, which are core. Then either implement `index` or remove it and the "flexible parameter specification" example.

### A8. `try target = expr` doesn't unwrap — **Implement**

It reports `Cannot assign Result<string, string> to string`. Ch. 9 lists it
among the supported `try` forms.

### A9. Standalone Result arm types — **Implement**

`ok: Success<int> := Success(42)` becomes `Result<int, unknown>`, then fails
with "has no member value" or internal "Unknown resolved type" errors (ch. 9).

### A10. Static member access through `::` — **Implement**

- `rect::kind` and `c::zeroLabel()` don't parse; the expression parser has no `::` postfix.
- The checker's own diagnostic ("use '::'") recommends that syntax.
- Static interface members (`static zeroLabel(): string`) don't parse either.

**Recommendation**: implement both. At minimum, stop recommending `::` in the diagnostic until it exists.

### A11. Implicit numeric widening isn't transitive — **Implement**

`checker-types.do:663` allows only four conversions:

- `byte`→`int`
- `int`→`long`
- `int`→`double`
- `float`→`double`

So these are rejected even though they're safe: `byte`→`long`, `byte`→`float`,
`byte`→`double`, `int`→`float`. Ch. 2 says safe widening is implicit.

**Recommendation**: allow every lossless pair. `int`→`float` is lossy above 2^24, so leave it out and say so in the spec.

### A12. Semicolons after block statements — **Implement**

`if x { }; y`, `for … { };` and `class A {};` fail with "Expected an
expression". Ch. 1 says semicolons may follow any statement or declaration.

### A13. Map key types aren't checked in declared types — **Implement**

- `Map<float, int>`, `Map<Tuple<…>, int>` and `Map<Point, int>` are accepted, and `Map<float, int>` compiles and runs.
- `{ 1.5: "v" }` reports an internal "Missing resolved type" error.
- Set element restrictions are enforced correctly.

### A14. Empty array literal without an annotation — **Decide**

`let empty = []` reports internal "Unknown resolved type" errors. Ch. 2 says
it's currently accepted. The simplest fix is to reject it with a proper
diagnostic and update the spec.

### A15. Object literal without context — **Spec or Implement**

- `let q = { x: 1.0 }` is accepted as `Map<string, SerialValue>`; ch. 2 says it's an error.
- An ambiguous interface literal reports "Cannot assign Map<string, SerialValue> to Positioned" instead of "multiple candidates".

**Recommendation**: document the SerialValue-map fallback, and improve the interface diagnostic.

### A16. `println` and `print` — **Decide**

- `println` accepts only `SerialValue`, so `println('c')` and `println(Direction.North)` are rejected.
- `print` doesn't exist.
- Ch. 2 says `print` and `println` format enums by name.

**Recommendation**: accept every interpolatable type in `println` (the same set as `${}`), and add `print` or remove it from the spec.

### A17. `string.replace` is missing — **Implement**

`replaceAll` exists. Ch. 2 documents `replace` as replacing the first occurrence.

### A18. Traditional `for` with two variables — **Implement or Spec**

`for let i = 0, j = 10; …` doesn't parse, though a two-part update clause does
(ch. 6).

### A19. Static-method shorthand in defaults — **Implement**

In parameter and field defaults, `.identity()` fails with "Cannot resolve
shorthand .identity". Static fields such as `.zero` work (ch. 4, 7).

### A20. Generic class inference — **Implement**

- `Channel { handler: onString }` and `Channel.constructor{ handler: onString }` fail with "type function; expected function".
- `Container { result: Success { value: 42 } }` fails with "Cannot assign int to T".
- `each([1, 2], => println(it))` against `f: (it: T): none` leaves `it` typed as the unsubstituted `T`. This affects parameterless and trailing lambdas passed to generic functions.

### A21. Namespace named construction — **Implement**

`math.Vector { x: … }` doesn't parse. Positional `math.Vector(…)` works (ch. 11).

### A22. Comma-separated class fields — **Spec**

`class Request { method: string, path: string }` doesn't parse. Use newlines
or `;` in the ch. 2 example.

### A23. Scientific-notation literals — **Decide**

`1e-10` doesn't lex. Ch. 11 uses it, but ch. 2 doesn't define exponent
notation. Either add it to the lexer and ch. 2, or change the example.

### A24. Accepted when the spec says it's an error — **Implement**

- `export function main()` (ch. 11: `main` must not be exported).
- `return Success()` in a function returning `Result<int, string>` (ch. 9: only valid for `Result<none, E>`).
- `(message) => …` where the contextual type names the parameter `msg` (ch. 4: names must match). The compiler currently binds by position.

### A25. Minor contextual typing gaps — **Implement**

- `Success(3)` fails when the expected type is `Result<int, string> | none`: "Success requires an expected Result type".
- Double range patterns (`case score { 90.0.. -> … }`) report "Case range bound of type double cannot match subject type double". Either support them or give a clear "integer subjects only" diagnostic.

### A26. Interfaces with no class implementers — **Decide**

`interface I { … }` with no implementing class is a hard error at `check`:
"Cannot emit interface I without implementing classes". This also happens when
a struct satisfies the interface only as a generic bound. A library that
exports an interface for consumers to implement can't be checked on its own.

**Recommendation**: emit nothing (or a warning) when no value of the
interface type is reachable, and document the rule in ch. 7.

---

## B. Spec text that contradicts itself or the compiler (doc fixes)

| Where | Problem | Fix |
|---|---|---|
| ch. 3 "Nested (Local) Scope" | Says nested functions can recurse. Ch. 4 says they can't, and the compiler agrees with ch. 4. | Remove the recursion example from ch. 3. |
| ch. 3 (lines ~21, 180, 274) | `readonly CONFIG = loadConfig()` at module scope is shown as valid. Ch. 11 limits declarative module initializers to construction-only values; runtime initializers work only in native entry scripts. | Say that runtime-computed module values are script-entry-only, or move them into `main()`. |
| ch. 2 "Built-in Range Type" | `window: Range := 1..<5` at module scope is rejected for the same reason. | Show it as a local. |
| ch. 2 structural interfaces | `distance(): float` returns `(…) ** 2`, which is `double`. | Change the return type to `double`. |
| ch. 5 compound assignment | `x **= 3` on an `int` is rejected because `**` produces `double`. | Use a `double` variable. |
| ch. 6 summary table | Lists `loop ... else`; the body uses `then`. | Change it to `loop ... then`. |
| ch. 12 type table | "Enums: JSON string (member name)", while the enum section says backing value. | Say "backing value (int or string)". |
| ch. 13 invoke examples | Reads `result.value` after `if result.isSuccess()`, which contradicts the narrowing rules; the compiler rejects it. | Use `case`. |
| ch. 2 summary | Says user-defined generics are "planned", but they're implemented. | Update the summary. |
| ch. 2 "Type Narrowing" | Refers to "one limited implicit rule" and "the simple none-check rule above", but no implicit rule exists. | Remove both references. |
| ch. 7 `this` section | `setX` assigns to a bare `x` field, which the compiler rejects without `let`. | Declare `let x, y: float`. |
| ch. 7, ch. 12, ch. 10 | Examples still use the deprecated `function` keyword on methods (`private function advance()`, `function area()`, `function get()`). | Remove the keyword. |
| ch. 14 `std/http` examples | `try resp := get(…)` propagates `HttpError` into `Result<_, string>` functions. | Map the error or change the return type. |
| ch. 14 crypto and stream examples | Use `JwtError` and `IoError` without importing them. | Add the imports. |
| ch. 5 precedence table | Leaves out `\` at level 5. | Add it next to `/`. |
| ch. 11 exports | `export type Result<T> = Success<T> \| Failure` shadows the builtin Result and uses a bare `Failure`. | Use a different name. |
| ch. 4 and ch. 2 | Ch. 4's array method conventions list methods that ch. 2's table and the compiler don't have. | Reconcile them after A7. |

---

## C. Test infrastructure

- **Parse errors can hide.** The `checked()` helpers in several `checker*.test.do` files build through `createAnalyzer(...).analyze(...)`, and some don't assert on parse diagnostics. `checker.test.do:188` passes even though its source doesn't parse. Make every checker helper fail on parse diagnostics, as `checker-statements.test.do` already does.
- **Emitter bugs need native builds to show up.** The fixed emitter bugs were only visible when the generated C++ was compiled. The `runNativeFixture` harness in `emitter-carrier-native.test.do` catches this class of bug; adding a native fixture per statement and expression family would reduce future regressions.
- **Spec examples aren't compile-checked.** A `tools/` check that extracts fenced `doof` examples marked as valid and compile-checks them would stop the spec and compiler drifting apart. Many spec blocks are deliberately partial, so this needs an opt-in marker such as `doof check` fences.

## Suggested order

1. **A1 and A2** (literal and enum fields), plus the checker test helper fix. Discriminated unions depend on them.
2. **Chapter B doc fixes.** Cheap, and they remove misleading examples.
3. **Common gaps: A5, A6, A8, A9, A10, A12, A13.**
4. **Needs a decision first: A3, A7, A14, A16, A23, A26.**
