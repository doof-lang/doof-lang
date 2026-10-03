# Spec Conformance Review (October 2026)

This review compared `spec/` with the compiler at `1213f16`. About 200 small
probe programs were written from spec claims and examples, then run through
`dist/doof check` and `dist/doof run`.

The seven "group 1" defects fixed alongside this document are listed first for
reference. Chapter B's documentation fixes are also complete; the other items
remain open unless marked otherwise.

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

### A1. Literal-valued fields — **Fixed**

`kind: "circle"` (and other string, char, boolean or numeric literals) now
parses as a literal-valued field with the same meaning as the legacy
`const kind = "circle"`, which now warns. The JSON interface diagnostic
recommends the new spelling, and `checker.test.do`'s helper now reports
parse diagnostics. The never-implemented `kind := "circle"` spelling was
removed from the spec rather than added.

### A2. Enum-valued discriminator fields — **Fixed**

`kind: ShapeKind.Circle` now declares a literal-valued field. Qualified type
names don't exist in Doof today, so a dotted name after a field's `:` is read
as an enum member unless it continues like a type (`=`, `<`, `|`, `[`) or
follows a modifier. The checker rejects dotted values that aren't enum
variants, such as static fields. If namespace-qualified types are added later
(see A30), this rule needs revisiting.

JSON decoding previously validated only string and int literal fields; enum,
bool, negative and other literal fields accepted any value. They are now
decoded with the field's type and compared against the declared constant.

### A3. Positional literals don't construct classes — **Fixed**

`(a, b)` now constructs the class or struct its expected type names (directly
or as the present arm of `T | none`) in every listed context, and is checked
and lowered exactly like `Point(a, b)`, including defaults, custom
constructors, generic classes, cross-module classes and module initializers.
With no single class expected, it remains a Tuple. The spec's positional union
example `let r2: Result = ("Success", 42)` was removed: positional construction
skips literal-valued fields, so it could never select a union member.

### A4. `Array<T>` and `ReadonlyArray<T>` — **Removed from the spec**

Nothing used either name, and `T[]` and `readonly T[]`, with parentheses for
complex element types, already express every array type. A second spelling
would have diverged from the `int[]` form that diagnostics print. The spec
drops both names. The parser no longer rewrites `readonly Array<T>`, and
`Array<…>` and `ReadonlyArray<…>` now report "Unknown type 'Array'; write
arrays as T[]" (or the `readonly T[]` equivalent).

### A5. Result helper methods — **Removed from the spec**

Only `isSuccess`, `isFailure` and `unwrapOr` existed, while ch. 9 and ch. 13
also documented `map`, `mapError`, `andThen`, `orElse`, `unwrapOrElse`, `ok`
and `err`. Each duplicates an existing form: `try` in a Result-returning
function chains and transforms, postfix `?` converts to a nullable, and `case` or a
declaration `else` recovers from the error. The callback combinators also
needed special rules for payloadless arms. They are removed from the spec, and
ch. 9 shows the `try` and `else` equivalents.

### A6. `!.` doesn't unwrap Results — **Fixed**

`loadUser()!.email` failed with `Result<User, string> has no member "email"`.
The checker now treats `r!.m` as `(r!).m`, so the receiver is evaluated once
and lowered through postfix `!`, panicking on Failure. Every absent layer
panics, so `Result<User | none, E>!.email` also panics on none. On
`Result<none, E>` there is no success value, and member access reports that.

### A7. Array callback conventions — **Fixed**

- Element callbacks take `(it: T, index: int)`; `reduce` and `reduceRight`
  take an initial value and `(acc: U, it: T, index: int)`.
- `forEach`, `find` (`T | none`), `reduce`, `reduceRight` and `sort` (stable,
  in place, mutable arrays only) are implemented.
- Explicit lambda parameters that all name signature parameters bind by name
  (any subset, any order). Other lists bind by position and may omit trailing
  parameters, so `users.map((user) => …)` stays valid. A signature name listed
  out of position is an error. Named functions may omit the trailing `index`.
- Generic callback results rank their sources: explicit type arguments; then
  argument values and lambdas with a declared return type; then the contextual
  result type; then the lambda body. `map<double>(=> it + 1)`,
  `map((it): double => it + 1)` and `r: double[] := map(=> it + 1)` agree, and
  disagreeing explicit sources are reported.
- An expression-bodied lambda's declared or contextual return type is now its
  signature, as for block bodies. Previously `(it): double => it + 1` had type
  `(it: int): int`.
- Ch. 4's no-initial-value `reduce(=> acc + it)` example was changed to pass
  an initial value. Ch. 3's `reduce(0.0, (a, b) => …)` now binds by position.

### A8. `try target = expr` doesn't unwrap — **Fixed**

It reported `Cannot assign Result<string, string> to string`. The tried value
is now checked as a Result and its success value is assigned with ordinary
assignment rules, so variables, fields, and elements all work, and union
targets receive the converted value. Compound operators such as `try n += …`,
non-Result values, and `Result<none, E>` report direct diagnostics. Ch. 9
documents the targets and the `=`-only rule.

### A9. Standalone Result arm types — **Fixed**

`ok: Success<int> := Success(42)` became `Result<int, unknown>`, then failed
with "has no member value" or internal "Unknown resolved type" errors (ch. 9).
`Success<T>` and `Failure<E>` are now intrinsic structs. Annotations, including
function signatures, resolve to the arm types, and both construction forms
produce an arm without a Result context. Arms lower to `doof::Success<T>` and
`doof::Failure<E>` and convert to any compatible Result. `Success<T> |
Failure<E>` is canonicalized to `Result<T, E>`. `Success()` for a Result with a
present success type is now rejected, as ch. 9 requires.

Treating the arms as structs exposed two general gaps, fixed with it:

- Equality between a union and one of its members (`u == 1` for
  `int | string`, `ok() == Success(1)`, an interface with an implementing
  class) emitted invalid C++. The checker now records the wider comparison
  type and the narrower operand converts to it. Arms compare their payload as
  struct equality does, so Result equality works too.
- A bare generic type pattern (`s: Success`, `b: Box`) took its arguments from
  the subject only when the subject was a Result. It now takes them from the
  one matching subject member of any union, and Result exhaustiveness uses the
  ordinary union rule. A pattern naming the whole Result type now matches.

### A10. Static member access through `::` — **Decided: class name only**

Statics are accessed only through the class name (`Rectangle.kind`). Neither
`.` nor `::` reaches them through an instance, and the diagnostic for
`rect.kind` now says "use 'Rectangle.kind'" instead of recommending `::`.
Ch. 7 drops the `::` syntax. Interfaces may declare static members as a
contract for generic bounds, and a type parameter reaches them through `T.name`
(`T.zero()`); statics remain unreachable through instances or interface values.

### A11. Implicit numeric widening isn't transitive — **Done**

`byte` now widens to `int`, `long`, `float` and `double`, in addition to `int`→`long`, `int`→`double` and `float`→`double`. `int`→`float` stays rejected because it is lossy above 2^24; Ch. 2 says so.

### A12. Semicolons after block statements — **Done**

A `;` where a statement may start is now an empty terminator, so `if x { }; y`, `for … { };`, `class A {};` and repeated `;;` parse. Ch. 1 already allowed this.

### A13. Map key types aren't checked in declared types — **Done**

`Map` and `ReadonlyMap` annotations now reject unsupported key types (`float`, `double`, tuples, classes and so on) wherever they appear, with the same "Map key type … is not supported" error as inferred map literals. Type-parameter keys are still accepted. Local `let` annotations used to report Set element errors twice; Set and Map errors are now reported once per site. The bare `{ 1.5: "v" }` case already reported A15's "Cannot infer the type of an object literal" error.

### A14. Empty array literal without an annotation — **Done**

An empty array literal now needs an expected type (annotation, parameter, return type, field, nullable context) and otherwise reports "Cannot infer the element type of an empty array literal". Ch. 2 is updated.

### A15. Object literal without context — **Done**

The spec was right. `let q = { x: 1.0 }` is now an error ("Cannot infer the type of an object literal without context"), and an object literal assigned to an interface reports "Ambiguous object literal for Positioned; multiple candidates: ..." instead of a Map-to-interface assignment error.

### A16. `println` and `print` — **Done**

`print` is dropped from the spec. `println` now accepts every type string interpolation accepts (chars, enums, collections of them, and so on) and rejects the rest with "cannot be passed to println".

### A17. `string.replace` is missing — **Implement**

`replaceAll` exists. Ch. 2 documents `replace` as replacing the first occurrence.

### A18. Traditional `for` with two variables — **Implement or Spec**

`for let i = 0, j = 10; …` doesn't parse, though a two-part update clause does
(ch. 6).

### A19. Static-method shorthand in defaults — **Fixed**

`.identity()` failed in every position, not only defaults: a dot-shorthand
callee was checked without the call's expected type. It now resolves against
that type and records the selected static member, so it lowers exactly like
`Matrix.identity()`. A shorthand must name a static field of the expected
class's type or a static method returning it; with an expected `T | none`,
the field or method may also produce `T | none`
(`parsed: Matrix | none := .parse(text)`). Other members get a targeted
diagnostic. Module-level and static `T | none` values are now accepted as
direct storage, so optional static fields can be shorthand sources.

### A20. Generic class inference — **Implement**

- `Channel { handler: onString }` and `Channel.constructor{ handler: onString }` fail with "type function; expected function".
- `Container { result: Success { value: 42 } }` fails with "Cannot assign int to T".
- `each([1, 2], => println(it))` against `f: (it: T): none` leaves `it` typed as the unsubstituted `T`. This affects parameterless and trailing lambdas passed to generic functions.

### A21. Namespace named construction — **Removed: no namespace imports**

Namespace imports were only partly implemented: values, calls and positional
construction worked, but `math.Vector { … }`, qualified type annotations and
qualified enum variants did not, and no Doof code outside the compiler's own
tests used them. They are removed from the language. `import * as ns from
"mod"` is now a parse error pointing at named imports, and ch. 11 documents
named imports with `as` for collisions. This also closes A30.

### A22. Comma-separated class fields — **Fixed in the spec**

Fields stay separated by newlines or `;`; a comma after a field name still
declares several names of one type (`x, y: int`). The ch. 2 union example now
writes `class Request { method: string; path: string }`.

### A23. Scientific-notation literals — **Fixed**

Decimal literals accept an exponent (`1e-10`, `6.02E23`, `2.5e3f`), which makes
them floating-point even without a decimal point. Long literals reject a
fraction or exponent with a direct diagnostic, an `e` not followed by digits
still starts the next token, and hex literals are unaffected. Ch. 2 documents
the form; ch. 11's `1e-10` example now compiles.

### A24. Accepted when the spec says it's an error — **Implement**

- `export function main()` (ch. 11: `main` must not be exported).
- `return Success()` in a function returning `Result<int, string>` (ch. 9: only valid for `Result<none, E>`).
- ~~`(message) => …` where the contextual type names the parameter `msg`.~~ Resolved: ch. 4 no longer requires lambda parameter names to match the signature. Names from the signature bind by name; other names bind by position (see A7).

### A25. Minor contextual typing gaps — **Implement**

- ~~`Success(3)` fails when the expected type is `Result<int, string> | none`~~. Fixed with A9: a union with one Result member provides the payload context.
- Double range patterns (`case score { 90.0.. -> … }`) report "Case range bound of type double cannot match subject type double". Either support them or give a clear "integer subjects only" diagnostic.

### A26. Interfaces with no class implementers — **Fixed**

Interfaces may have no implementing classes, so a library that exports an
interface and helpers declared against it now checks and compiles alone. Such
an interface, including one implemented only by never-instantiated generic
classes, lowers to `std::variant<doof::NoImplementations>`. No value can exist,
so member reads, calls, assignments, destructuring, and spreads on it lower to
an unreachable panic of the checked result type, and `.fromSerialValue()`
always returns a Failure. This also fixes the never-instantiated generic case,
which previously passed `check` and then failed in C++ with a
`std::monostate` variant. Documented in ch. 7 and ch. 12.

### A27. Named union alias deserialization — **Fixed**

`Shape.fromSerialValue(json, lenient)` now works for a non-generic alias of a
union of classes that share a literal string discriminator, including aliases
imported from another module. The alias module emits a `Shape_fromSerialValue`
decoder that shares the interface decoder's dispatch. Other aliases report a
targeted error, and the alias still can't be used as a value otherwise.

### A28. Generic `T.fromSerialValue(json)` emits invalid C++ — **Fixed**

A one-argument call now supplies the default `lenient` argument. The
specialized callee also no longer assumes a shared-pointer class: struct
arguments use the value type, and enum arguments call the generated enum
decoder (previously both produced invalid C++).

### A29. Deprecated module `const` gives no warning — **Done**

Every `const` declaration (module-level, exported, local and `try const`) now warns "'const' declarations are deprecated; replace it with 'readonly'". The warning covers the `const` keyword and offers `readonly` as its replacement. Both are deeply immutable, so the meaning doesn't change. Class-field `const` keeps its own warning (see A1).

### A30. Namespace-qualified enums and types — **Removed with A21**

Namespace imports no longer exist, so qualified enums and types have nothing
to qualify.

---

## B. Spec text that contradicts itself or the compiler (doc fixes) — Fixed

All 16 recommendations below are implemented in `spec/`. Revised examples
were checked with the installed compiler, with local context and supporting
declarations supplied where the spec uses partial snippets.

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

---

## C. Test infrastructure

- **Parse errors can hide.** The `checked()` helpers in several `checker*.test.do` files build through `createAnalyzer(...).analyze(...)`, and some don't assert on parse diagnostics. `checker.test.do:188` passed even though its source didn't parse. `checker.test.do` now includes analysis diagnostics; `checker-async.test.do`, `checker-symbols.test.do` and `checker-validation.test.do` still don't, and should get the same treatment.
- **Emitter bugs need native builds to show up.** The fixed emitter bugs were only visible when the generated C++ was compiled. The `runNativeFixture` harness in `emitter-carrier-native.test.do` catches this class of bug; adding a native fixture per statement and expression family would reduce future regressions.
- **Spec examples aren't compile-checked.** A `tools/` check that extracts fenced `doof` examples marked as valid and compile-checks them would stop the spec and compiler drifting apart. Many spec blocks are deliberately partial, so this needs an opt-in marker such as `doof check` fences.

## Suggested order

1. **The remaining checker test helpers** (section C), now that A1, A2, A27 and A28 are done.
2. **Chapter B doc fixes — completed.** The misleading examples and contradictory text are corrected.
3. **Common gaps — completed.** A10, A12, A13 and A29 are done.
4. **No remaining decisions.**
