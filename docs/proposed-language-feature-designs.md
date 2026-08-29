# Proposed Language Feature Designs

Status: design proposal, not part of the Doof language specification.

This document develops seven related language and compiler proposals:

1. named-union JSON dispatch;
2. capability-bearing generic constraints;
3. owned values, borrowing, and explicit moves;
4. payload-bearing unions and destructuring patterns;
5. structured concurrency, cancellation, and deadlines;
6. structural interface conformance for structs; and
7. package-scoped visibility.

The proposals build on Doof's existing closed-world compiler, explicit
`Result` error handling, actor-owned mutable domains, structural interfaces,
nominal classes and structs, and generated JSON metadata. They are intended to
close gaps in those systems rather than introduce independent abstraction
models.

Nothing in this document is normative until it is incorporated into `spec/`,
implemented in `src/`, covered by focused tests, reflected in the Doof language
skill, and accepted through the normal bootstrap and release process.

## Design principles

Every proposal follows these constraints:

- Preserve explicit failure. New recoverable operations return `Result`; they
  do not throw exceptions.
- Preserve closed-world reasoning. Exhaustiveness, structural conformance,
  transfer safety, and generated dispatch should be decided by the checker.
- Preserve the decorated-AST boundary. Emitters consume checker decisions and
  must not reconstruct overload, ownership, exhaustiveness, or visibility
  policy.
- Prefer small orthogonal additions. A proposal should reuse existing syntax
  and semantic machinery where that remains clear.
- Keep source behavior independent of C++ accidents such as `shared_ptr`
  reference counts, `std::variant` ordering, or template substitution errors.
- Diagnose invalid programs at the source construct that introduced the
  problem, with a useful source span and a suggested repair when one exists.
- Stage high-risk features. The first accepted version should be sound and
  deliberately narrower than the eventual feature.

## Dependency and delivery overview

| Proposal | Depends on | Relative risk | Suggested delivery |
| --- | --- | --- | --- |
| Named-union JSON dispatch | Existing aliases, unions, JSON generation | Medium | First |
| Capability-bearing constraints | Existing generics and interfaces | Medium | First |
| Struct interface conformance | Existing structural interface machinery | Medium | After generic constraints |
| Package-scoped visibility | Existing resolver and package identity | Low | Independently |
| Payload-bearing unions | Existing unions, cases, JSON, metadata | Medium-high | After named-union JSON |
| Owned values and moves | Flow analysis and actor-boundary checking | High | After semantic hardening |
| Structured concurrency | Runtime scheduler and must-use checking | High | After task error and ownership decisions |

The first four can be delivered without changing Doof's runtime scheduling or
memory model. Payload-bearing unions change representation but remain largely
compile-time. Ownership and structured concurrency require the strongest
cross-phase and runtime review.

---

## 1. Named-union JSON dispatch

### Summary

A named type alias whose underlying type is a union of JSON-serializable classes
can synthesize `Alias.fromJsonValue(...)`. A shared literal-valued string field
selects the concrete class to decode.

The language specification already describes this surface. This proposal
defines the remaining semantic and lowering work needed to make the behavior
complete and usable recursively.

### Motivation

Doof already represents many domain models as discriminated class unions:

```doof
class Circle {
    kind: "circle"
    radius: double
}

class Rectangle {
    kind: "rectangle"
    width, height: double
}

type Shape = Circle | Rectangle
```

Each member can decode itself, but callers should not have to duplicate the
discriminator switch:

```doof
function decodeShape(value: JsonValue): Result<Shape, string> {
    // This should be generated from the alias declaration.
    return Shape.fromJsonValue(value)
}
```

The alias provides a stable source name for the generated operation, JSON
Schema, diagnostics, and emitted adapter. A bare `Circle | Rectangle` has no
such owner.

### Source syntax

No new declaration syntax is required:

```doof
type Shape = Circle | Rectangle

result := Shape.fromJsonValue({
    kind: "circle",
    radius: 5.0,
})

lenient := Shape.fromJsonValue(payload, true)
```

The synthetic signature is:

```doof
Shape.fromJsonValue(
    value: JsonValue,
    lenient: bool = false,
): Result<Shape, string>
```

The method is available only through the alias name. It is not added as a
shared instance member of the union and cannot be accessed through a bare union
annotation.

### Eligibility

The checker exposes the synthetic method only when all of the following hold:

1. The receiver symbol is a named type alias.
2. The fully expanded alias is a union with at least two members.
3. Every member is a non-native, non-generic class eligible for generated JSON
   deserialization.
4. Every member declares a non-static literal-valued string field with the same
   name.
5. Every discriminator value is distinct.
6. The alias is not recursive solely through alias expansion. Recursion through
   class fields remains valid and uses the normal JSON recursion guard.

The initial version deliberately excludes generic aliases. Generic JSON support
can be added later by specializing a dispatcher for every reached concrete alias
instantiation, but it should not be inferred accidentally from monomorphization.

### Discriminator selection

The compiler examines fields in the first member's declaration order. The
first field satisfying the complete shared-and-unique rule becomes the
discriminator. This matches interface JSON dispatch and makes selection
deterministic.

Shape-based guessing is not allowed. The following remains invalid even though
the fields currently appear distinguishable:

```doof
class Circle { radius: double }
class Rectangle { width, height: double }
type Shape = Circle | Rectangle

// Compile error: no shared literal string discriminator.
value := Shape.fromJsonValue(payload)
```

Field-based guessing is unstable when a default is added, a field is renamed,
or variants acquire overlapping shapes. An explicit discriminator is a durable
wire contract.

### Runtime behavior

The generated decoder performs these steps in order:

1. Require a JSON object.
2. Find the discriminator field.
3. Require a JSON string discriminator value.
4. Select the member with that literal value.
5. Invoke that member's generated `fromJsonValue(value, lenient)`.
6. Promote a successful member into the alias union.
7. Forward a member decoding failure unchanged.

Example outcomes:

```doof
Shape.fromJsonValue("circle")
// Failure("Expected JSON object")

Shape.fromJsonValue({ radius: 5.0 })
// Failure("Missing or invalid discriminator field \"kind\"")

Shape.fromJsonValue({ kind: "triangle" })
// Failure("Unknown kind: \"triangle\"")

Shape.fromJsonValue({ kind: "circle", radius: "large" })
// Failure from Circle.fromJsonValue concerning radius.
```

### Nested use

Named aliases must remain JSON-aware when used as fields or collection
elements:

```doof
class Drawing {
    primary: Shape
    layers: Shape[]
    named: Map<string, Shape>
}

drawing := Drawing.fromJsonValue({
    primary: { kind: "circle", radius: 2.0 },
    layers: [
        { kind: "rectangle", width: 10.0, height: 4.0 },
    ],
    named: {
        logo: { kind: "circle", radius: 1.0 },
    },
})
```

Deserialization recursively invokes the alias dispatcher. Serialization visits
the active union member and calls that member's generated encoder. The alias
does not add a public instance method; the containing generated encoder uses an
internal alias adapter.

### Type-system representation

Aliases are transparent for assignability but cannot be erased before
alias-owned behavior has been considered. Introduce a resolved alias wrapper:

```text
AliasResolvedType {
    symbol
    arguments
    underlying
}
```

Core type operations use `underlying`:

- assignability;
- equality and union normalization;
- narrowing;
- C++ representation selection; and
- ordinary shared-member lookup.

Alias-sensitive operations retain the wrapper:

- `Alias.fromJsonValue` lookup;
- generated JSON eligibility for annotated fields;
- schema naming and `$defs` ownership;
- diagnostics; and
- on-demand generation keys.

An implementation may instead decorate the source annotation and member access
with the alias symbol, but it must also retain alias provenance for nested JSON
fields. A purely syntactic special case at `Shape.fromJsonValue` is
insufficient.

### Checker and emitter contract

When the checker accepts `Shape.fromJsonValue(...)`, it decorates the call with:

- the alias symbol;
- the resolved union result type;
- the selected discriminator field;
- the ordered discriminator-to-member table;
- the concrete member decoder symbols; and
- the lenient argument after default insertion.

The emitter consumes this table. It must not rediscover fields or search for a
discriminator.

The generated C++ is conceptually:

```cpp
doof::Result<Shape, std::string> Shape_fromJsonValue(
    const doof::JsonValue& json,
    bool lenient
) {
    // Validate object and discriminator.
    // Call Circle::fromJsonValue or Rectangle::fromJsonValue.
    // Promote the successful shared_ptr into Shape's std::variant.
}
```

Demand discovery must mark:

- the alias dispatcher;
- every reachable member deserializer;
- nested deserializers required by those members; and
- the corresponding encoder adapters only when serialization is requested.

### Diagnostics

Recommended diagnostics include:

```text
Automatic JSON deserialization is available only on named union aliases;
name this union with `type` before calling `fromJsonValue`
```

```text
Cannot deserialize union alias "Shape": member "Circle" is not eligible for
automatic JSON deserialization because field "callback" has function type
```

```text
Cannot deserialize union alias "Shape": members must share a literal string
field with distinct values; "Circle.kind" and "Rectangle.kind" both use
"shape"
```

The error is attached to the `fromJsonValue` member access. Secondary spans may
point to conflicting discriminator declarations.

### Tests

Focused coverage should include:

- happy-path dispatch for every member;
- strict and lenient member decoding;
- non-object, missing, wrong-type, and unknown discriminators;
- duplicate and missing discriminator compile errors;
- an ineligible member with an actionable reason;
- nested aliases in classes, arrays, maps, and tuples;
- imported and re-exported aliases;
- aliases with the same underlying union but different source names;
- demand generation in only the required direction; and
- emitted C++ compilation and runtime behavior.

### Non-goals

- Guessing a member from object shape.
- Supporting bare union expressions as static method receivers.
- Custom field renaming or discriminator annotations in the first version.
- Automatically serializing `Result`, actors, promises, callbacks, or native
  classes.

---

## 2. Capability-bearing generic constraints

### Summary

Generic constraints should describe not only which concrete arguments are
admissible, but also which operations are available on the type parameter
inside the generic declaration.

```doof
interface Hashable {
    hash(): long
}

function bucket<T: Hashable>(value: T, count: long): long {
    return value.hash() % count
}
```

No trait or type-class system is introduced. Existing structural interfaces
become the reusable capability vocabulary for generics.

### Motivation

Doof already validates concrete type arguments against generic constraints.
However, an ordinary constraint is of limited value if the generic body cannot
use the members guaranteed by that constraint. Compiler-known constraints such
as `JsonSerializable` and `Reflectable` currently receive special member
behavior. User-defined structural interfaces should receive the same general
principle without becoming compiler intrinsics.

### Source syntax

The basic syntax is unchanged:

```doof
interface Identified {
    readonly id: long
}

function idOf<T: Identified>(value: T): long => value.id
```

Generic classes and methods use the same rule:

```doof
interface Measurable {
    measure(): double
}

class Largest<T: Measurable> {
    value: T

    choose(other: T): T {
        if other.measure() > value.measure() { return other }
        return value
    }
}
```

Static interface requirements are also available through the type parameter:

```doof
interface Zero {
    static zero(): Self
}

function origin<T: Zero>(): T => T.zero()
```

`Self` in an interface constraint denotes the concrete type argument. Its first
use should be restricted to method return types and parameter types; it does not
introduce associated types.

### Constraint categories

The checker distinguishes three categories:

1. **Admissible-set constraints**, such as `T: int | long`. A concrete argument
   must be assignable to one member of the constraint.
2. **Structural capability constraints**, such as `T: Hashable`. A concrete
   class, and eventually a struct, must structurally implement the interface.
3. **Compiler capability constraints**, currently `JsonSerializable` and
   `Reflectable`, which expose documented generated static members.

The categories can share one resolved constraint representation while retaining
their origin for diagnostics and member lookup.

### Available operations

For an interface-constrained parameter, the generic body may:

- read interface fields;
- call interface instance methods;
- access interface static methods through `T`;
- pass a `T` where the interface type is expected;
- return or store `T` without erasing its concrete type; and
- use the constraint in nested generic inference.

For an admissible union constraint, an operation is available only when it is
valid with one compatible signature for every possible member. This mirrors
ordinary union shared-member access.

```doof
interface Named { readonly name: string }

function label<T: Named>(value: T): string {
    return value.name
}
```

The declared type of `value` remains `T`, not `Named`. Calling `label(User {})`
therefore returns and specializes against `User` wherever `T` appears in the
result.

### Structural satisfaction

A concrete argument satisfies `T: Interface` when the existing structural
interface checker accepts the concrete type after substituting all generic
arguments.

Explicit `implements` remains optional but provides earlier diagnostics:

```doof
class CacheKey implements Hashable {
    text: string
    hash(): long => stableHash(text)
}
```

The constraint does not use nominal declarations as hidden witnesses. Closed-
world structural conformance remains the source of truth.

### Multiple capabilities

The initial version does not add an intersection operator. Libraries can define
a composite structural interface:

```doof
interface HashableAndNamed {
    hash(): long
    readonly name: string
}
```

An eventual `T: Hashable & Named` spelling should be considered only after
intersection types have a coherent meaning outside constraints. Adding a
constraint-only `&` would create a second type algebra and is not recommended.

### Type inference

Call-site inference is unchanged:

```doof
key := CacheKey { text: "session" }
slot := bucket(key, 64L) // T is CacheKey
```

Inference first finds candidate type arguments from value arguments, then
validates each constraint. Expected return types still do not infer otherwise
unresolved parameters.

When inference fails because the inferred type lacks a capability, the
diagnostic should name both the missing member and the constraint:

```text
Inferred type "User" does not satisfy constraint "Hashable" for "T":
missing method "hash(): long"
```

### Variance and compatibility

This proposal does not introduce variance. Collections and generic nominal
types retain their existing invariance rules. Interface method compatibility
uses the existing structural rules after substituting `T` and `Self`.

Two constraints with structurally identical members remain distinct named
interface declarations for documentation and diagnostics, even though the same
class may satisfy both automatically.

### Isolation and ownership effects

Constraint member lookup must retain semantic effects:

- An actor-dispatched generic may call a constrained method only when that
  method requirement is `isolated`.
- A future `borrow` or ownership qualifier on an interface method participates
  in checking.
- Boundary safety of a constrained `T` is not implied by ordinary structural
  conformance. It must be checked for every reached concrete instantiation.

Example:

```doof
interface Computable {
    isolated compute(): int
}

isolated function evaluate<T: Computable>(value: T): int {
    return value.compute()
}
```

### Lowering

Doof monomorphizes reached generic declarations. A constrained call therefore
does not require a new runtime witness-table or vtable representation.

For each concrete specialization, the checker records the concrete member that
satisfies every constrained access. The emitter lowers directly to that member:

```text
bucket<CacheKey>(key, 64)
    -> specialized bucket__CacheKey
    -> direct CacheKey.hash call
```

The emitter must not repeat structural matching. If a generic specialization
somehow lacks a decorated target, emit-readiness validation reports an internal
compiler contract violation before C++ generation.

### Diagnostics

Required diagnostic classes include:

- unsupported member on an unconstrained type parameter;
- member absent from the declared constraint;
- inferred or explicit argument failing structural conformance;
- incompatible method parameter or return type;
- missing static requirement;
- non-isolated constrained call from isolated code; and
- ambiguous shared member on an admissible union constraint.

Example:

```text
Type parameter "T" has constraint "Named", which does not provide member
"hash"; add the member to the constraint or use a more specific constraint
```

### Tests

Coverage should include fields, instance methods, static methods, `Self`,
generic interfaces, imported constraints, nested generic methods, inference,
explicit arguments, recursive generic calls, isolation, missing members, and
emitted specialization calls.

### Non-goals

- Associated types.
- Higher-kinded types.
- Default interface method bodies.
- Runtime trait objects beyond Doof's existing interface representation.
- A second constraint solver or implicit witness search.

---

## 3. Owned values, borrowing, and explicit moves

### Summary

Introduce an affine `owned T` qualifier, non-escaping `borrow T` parameters,
and a `move` expression. Together they permit the checker to prove that a
mutable graph has a single external owner and can safely transfer that graph
across an actor or async boundary.

```doof
state: owned WorkerState := WorkerState { jobs: [] }
worker := Actor<WorkerState>(move state)

// Compile error: state was moved into worker.
println(state.jobs.length)
```

This is not a Rust-style general lifetime system. The first version supports
whole-value ownership, lexical borrows, and explicit consumption only.

### Motivation

Actor construction currently rejects mutable arguments because moving a
`shared_ptr` or collection handle does not prove that no aliases remain. C++
reference counts cannot provide a recursive source-level ownership guarantee,
and runtime `use_count()` checks would be incomplete and timing-sensitive.

An explicit affine qualifier makes uniqueness a checked language fact. It also
supports zero-copy pipelines and native APIs that consume buffers without
weakening Doof's actor isolation.

### Source syntax

Ownership qualifies a type:

```doof
buffer: owned byte[] := [1, 2, 3]
state: owned State := State { values: [] }
```

Owned parameters and returns are explicit:

```doof
function createState(): owned State {
    return State { values: [] }
}

function install(state: owned State): Actor<State> {
    return Actor<State>(move state)
}
```

A consuming use requires `move`:

```doof
next: owned State := move state
```

Read-only, non-escaping helper access uses `borrow` parameters:

```doof
enum ValidationError { Empty }

function validate(state: borrow State): Result<none, ValidationError> {
    if state.values.length == 0 {
        return Failure { error: ValidationError.Empty }
    }
    return Success()
}

state: owned State := createState()
try validate(state) // implicit lexical borrow; state remains owned
worker := Actor<State>(move state)
```

`borrow` is permitted on parameters only in the initial version. It cannot
appear on fields, return types, module bindings, or generic aliases.

### Ownership model

`owned T` means:

- the current binding is the only external owner of the reachable mutable
  graph;
- the value cannot be copied, captured, stored in shared state, or implicitly
  widened to ordinary `T`;
- nested mutable class and collection references must themselves be owned by
  the same graph or freshly constructed within it;
- deeply immutable values may be referenced by both owned and shared graphs;
  and
- moving the root transfers ownership of the entire graph.

Internal aliases within an owned graph are allowed only when the checker can
see that they do not escape the graph. The first implementation may
conservatively reject internal aliasing and cycles. This is preferable to a
runtime uniqueness check or an unsound optimistic rule.

Ownership is not part of nominal type identity. `owned State` and `State` use
the same class declaration and methods, but assignment and call compatibility
consider the qualifier.

### Sources of owned values

An owned context accepts:

- fresh class construction;
- fresh mutable collection literals;
- fresh structs containing owned members;
- a function returning `owned T`;
- `move` from another owned binding;
- mutable results transferred out of an async worker;
- state returned by `retire actor`; and
- selected native functions explicitly declared to return `owned T`.

It does not accept an ordinary shared value:

```doof
shared := State { values: [] }

// Compile error: a shared value cannot be recovered as owned.
unique: owned State := shared
```

Even when a runtime reference count happens to be one, source-level aliases may
exist through native code, fields, or closures. Ownership can be preserved or
consumed, never guessed back into existence.

### Move semantics

`move expression` is a consuming expression. In the initial version its operand
must be a simple local binding of owned type.

After a move, the binding is unavailable until every control-flow path assigns
it a new owned value:

```doof
let state: owned State = createState()

if restart {
    replacement := Actor<State>(move state)
    state = retire replacement
}

// Valid only because the restart path reinitializes state.
println(state.values.length)
```

For an immutable `:=` binding, any move permanently consumes the binding:

```doof
state: owned State := createState()
worker := Actor<State>(move state)
println(state.values.length)
// Error: use of moved binding "state".
```

The flow state for an owned binding is one of:

- initialized;
- moved;
- maybe moved; or
- reinitialized.

A use in the maybe-moved state is rejected with notes pointing to the paths
that consume it.

### Borrow semantics

Passing an owned value to `borrow T` creates a lexical, non-escaping view for
the duration of the call.

A borrowed value may:

- read fields;
- call methods proven not to let the receiver escape;
- mutate when the borrow is uniquely mutable and the parameter is declared
  `borrow let T`, if that extension is accepted; and
- create shorter nested borrows.

A borrowed value may not:

- be returned;
- be stored in a field, collection, module binding, or static field;
- be captured by a lambda or async block;
- cross an actor boundary;
- be converted to `weak`;
- be moved; or
- outlive the call.

The recommended first version supports immutable `borrow T` only. Mutable
borrows can be added later as `borrow let T` after alias diagnostics and method
receiver effects are proven usable.

### Method calls on owned receivers

Field access creates a temporary borrow. A method may be called through an
owned receiver only when the checker proves that `this` does not escape through
the method body or any transitive call.

```doof
class State {
    values: int[]

    count(): int => values.length

    fluent(): State => this
}

state: owned State := State { values: [] }
println(state.count())  // Valid: receiver does not escape.
copy := state.fluent()  // Error: this call would create a shared alias.
```

This receiver behavior should be represented as an inferred effect on the
method, similar to isolation inference. A future explicit `borrow` method
modifier may promise and enforce non-escape for public API documentation, but
is not necessary for initial syntax.

### Actor and async boundaries

Ownership enables mutable transfer where sharing remains forbidden:

```doof
state: owned WorkerState := WorkerState { pending: [] }
worker := Actor<WorkerState>(move state)
```

The rules are:

- deeply immutable shared values may still cross by copy as today;
- mutable values may cross only as `move owned T`;
- the sending binding becomes moved before scheduling or actor construction;
- failure to enqueue must return ownership or be impossible after validation;
- actor method parameters may opt into ownership with `owned T`;
- an actor method returning `owned T` transfers that graph to the caller; and
- `retire actor` returns `owned T` for mutable actor state.

Example consuming actor method:

```doof
class Store {
    blobs: byte[][] = []

    isolated add(blob: owned byte[]): none {
        blobs.push(move blob)
    }
}

blob: owned byte[] := loadBlob()
store := Actor<Store>()
store.add(move blob)
```

The actor owns the moved blob after the call is accepted. Other aliases cannot
exist by construction.

### Generics

Ownership qualifiers participate in generic signatures but do not create a
second type parameter:

```doof
function forward<T>(value: owned T): owned T {
    return move value
}
```

The checker validates that the concrete `T` has an ownership-capable
representation. Primitive and deeply immutable values may be moved uniformly,
but the compiler may warn that moving them is unnecessary. It should not make
generic code ill-formed merely because one specialization is trivially
copyable.

### Destructors and early exit

An initialized owned value is destroyed normally if control exits without
moving it. A moved binding has no remaining value and therefore performs no
second destruction.

`return`, `try` propagation, declaration-`else`, and `panic` cleanup all obey
the same flow state. Moving into a function argument occurs only after argument
evaluation succeeds, left to right.

### Native interop

Native imports must state ownership explicitly:

```doof
import isolated function readPacket(): owned byte[] from "packet.hpp"
import isolated function sendPacket(packet: owned byte[]): none from "packet.hpp"
```

The native ABI contract promises exclusive transfer. Generated adapters should
prefer move-capable C++ values rather than using reference-count inspection.
Incorrect native declarations remain trusted-contract violations, like
incorrect `isolated` declarations.

### Lowering

Ownership is primarily a checker property. Existing C++ representations can be
moved:

- class values move `std::shared_ptr<T>`;
- arrays, maps, and sets move their owning handle;
- structs use C++ move construction where available; and
- union alternatives use variant move construction.

The source guarantee is stronger than the C++ operation: the checker proves no
external mutable aliases before emitting `std::move`.

The decorated AST records:

- whether each expression is borrowed, copied, or moved;
- the ownership source and destination;
- binding flow state after the expression;
- ownership-bearing call parameters and returns; and
- actor-boundary transfer approval.

The emitter consumes those decorations and never asks whether a reference count
appears unique.

### Diagnostics

Examples:

```text
Cannot copy owned value "state"; use `move state` to transfer ownership or
pass it to a `borrow State` parameter
```

```text
Use of moved binding "state"; ownership was transferred to Actor<WorkerState>
on line 18
```

```text
Cannot pass shared mutable value "state" across an actor boundary; construct
an owned value or change the parameter to a deeply immutable type
```

```text
Borrowed parameter "state" escapes through return value
```

### Tests

Coverage must include moves through branches, loops, returns, `try`, cases,
closures, actor construction, actor calls, async blocks, retirement, generics,
destructors, native imports, collections, nested mutable graphs, invalid
borrows, double moves, use-after-move, and reinitialization.

### Non-goals

- Named lifetimes or general reference types.
- Partial moves from object fields or collection elements.
- Recovering ownership from an ordinary shared value.
- Runtime reference-count uniqueness checks.
- Implicit copy-on-write.
- Concurrent shared mutation outside actor ownership.

---

## 4. Payload-bearing unions and destructuring patterns

### Summary

Add a declaration form for closed nominal alternatives with payload fields, and
allow `case` arms to bind those fields directly.

```doof
union Expression {
    Number { value: double }
    Add { left: Expression, right: Expression }
}

function evaluate(expression: Expression): double {
    return case expression {
        .Number { value } -> value
        .Add { left, right } -> evaluate(left) + evaluate(right)
    }
}
```

This packages the existing class-plus-type-alias discriminated-union pattern
without changing the meaning of ordinary structural unions.

### Why a new declaration

The existing spelling remains valid and useful when variants need independent
class identities or methods:

```doof
class NumberExpression {
    kind: "number"
    value: double
}

class AddExpression {
    kind: "add"
    left, right: Expression
}

type Expression = NumberExpression | AddExpression
```

A payload-bearing union is preferable when alternatives exist only as cases of
one domain type. It provides:

- one declaration to export and document;
- guaranteed closed exhaustiveness;
- generated discriminator metadata;
- concise construction and matching;
- no globally visible helper class names; and
- a natural target for JSON Schema and reflection.

The keyword `union` is recommended instead of extending scalar `enum`. Existing
enums have integer/string values, `.value`, `.fromValue`, and native ABI uses.
Mixing payload cases into that model would create many conditional enum rules.

### Declaration syntax

```doof
export union HttpOutcome<T> "The result of an HTTP operation." {
    Response {
        status: int
        value: T
    }

    Redirect {
        location: string
        permanent: bool = false
    }

    NetworkError {
        message: string
    }

    Cancelled
}
```

A case may have named payload fields or no payload. Fields support:

- explicit types;
- defaults;
- `readonly`;
- literal-valued fields;
- descriptions; and
- generic parameters from the enclosing union.

The initial version does not permit methods, static members, destructors,
custom constructors, inheritance, or per-case type parameters. Put shared
behavior in free functions or interfaces until the representation and method
surface have demonstrated a real need.

### Construction

Use the union name and case name:

```doof
value := Expression.Number { value: 4.0 }
sum := Expression.Add { left: value, right: value }
cancelled := HttpOutcome<string>.Cancelled
```

When the expected union type is known, dot shorthand is allowed:

```doof
function zero(): Expression => .Number { value: 0.0 }

outcome: HttpOutcome<string> := .Cancelled
```

Named payload construction follows ordinary class/struct field rules: required
fields must be present, defaults may be omitted, unknown fields are rejected,
and each expression is evaluated once in source order.

Positional construction is not supported initially. Named fields make variant
payloads resilient to later additions and produce clearer wire contracts.

### Type identity

`Expression` is a nominal union type. Its cases are constructors and patterns,
not independently nameable top-level types. The following is invalid:

```doof
let number: Expression.Number // Error: a union case is not a standalone type.
```

This prevents case implementation details from escaping and distinguishes the
feature from a shorthand that silently declares classes.

An ordinary structural union remains transparent:

```doof
type Scalar = int | string
```

Nominal payload unions and structural type-alias unions should have distinct
resolved semantic representations even if both lower to `std::variant`.

### Pattern syntax

Payload cases can be matched and destructured:

```doof
case outcome {
    .Response { status, value } -> handle(status, value)
    .Redirect { location, permanent } -> follow(location, permanent)
    .NetworkError { message } -> println(message)
    .Cancelled -> println("cancelled")
}
```

Bindings may be renamed or discarded:

```doof
case outcome {
    .Response { status as code, value: _ } -> println(code)
    _ -> println("not a response")
}
```

The recommended field-pattern grammar mirrors named destructuring:

```text
field
field as localName
field: _
field: nestedPattern
```

The first release should support field binding, renaming, and discard. Recursive
nested patterns can follow once exhaustiveness and source-span diagnostics are
stable.

Class and struct destructuring patterns may reuse the same syntax in a later
stage:

```doof
case shape {
    Circle { radius } -> area(radius)
    Rectangle { width, height } -> width * height
}
```

That extension is orthogonal to payload unions and should not block their first
implementation.

### Exhaustiveness

A `case` over a nominal payload union is exhaustive when every declared case is
covered or a wildcard is present.

```doof
function describe(value: Expression): string {
    return case value {
        .Number { value } -> string(value)
        // Error: missing case Expression.Add.
    }
}
```

Multiple patterns in one arm remain supported when they bind the same names
with compatible types:

```doof
case outcome {
    .Cancelled | .NetworkError { message: _ } -> "unavailable"
    .Response { value, status: _ } -> value
    .Redirect { location, permanent: _ } -> fetch(location)
}
```

If alternatives bind different variables, the arm is rejected rather than
introducing optional pattern bindings.

Guards are not part of this proposal. A guard can cause a syntactically covered
case to fail at runtime and therefore complicates exhaustiveness. Use an `if`
inside the selected arm.

### JSON representation

A payload union whose fields are all JSON-serializable automatically supports
generated JSON. The default representation is an object with a reserved `kind`
field:

```doof
Expression.Number { value: 4.0 }
// { "kind": "Number", "value": 4.0 }

HttpOutcome<string>.Cancelled
// { "kind": "Cancelled" }
```

`kind` is reserved within a payload union. The default wire value is the case
name exactly as declared. Renaming cases is therefore a wire-format change.

This representation deliberately matches named-union and interface
discriminator dispatch. The compiler may lower payload-union JSON through the
same decorated dispatcher table.

Custom discriminator names and case wire names are deferred until Doof has a
general annotation policy. Description strings are documentation, not wire
configuration.

### Metadata and schema

Generated JSON Schema uses `oneOf`, not an unconstrained `anyOf`, because the
literal discriminator makes cases mutually distinguishable. Each case schema
requires its `kind` literal and required payload fields.

Conceptually:

```json
{
  "oneOf": [
    {
      "type": "object",
      "properties": {
        "kind": { "const": "Number" },
        "value": { "type": "number" }
      },
      "required": ["kind", "value"]
    }
  ]
}
```

Metadata exposes the union name, description, discriminator field, and an
ordered list of cases and fields. Invocation metadata may use a payload union
wherever generated JSON already accepts the type.

### Memory representation

Lower a payload union to one generated nominal wrapper containing a
`std::variant` of private generated case payloads. To support recursive unions
without representation cycles, payload alternatives are reference-counted
generated objects in the initial implementation.

Conceptually:

```cpp
struct Expression_NumberPayload { double value; };
struct Expression_AddPayload {
    Expression left;
    Expression right;
};

using ExpressionStorage = std::variant<
    std::shared_ptr<Expression_NumberPayload>,
    std::shared_ptr<Expression_AddPayload>
>;
```

The exact C++ names and wrapper layout are not language behavior. Source code
observes nominal union value semantics, exhaustive cases, and deterministic
destruction of the active payload.

### Lowering contract

The checker decorates every case pattern with:

- the nominal union declaration;
- the selected case ordinal;
- validated payload field bindings;
- binding types after generic substitution; and
- exhaustiveness contribution.

The emitter selects the stored alternative by ordinal and binds fields from the
decorated payload. It does not search names or recalculate exhaustiveness.

### Diagnostics

Examples:

```text
Non-exhaustive case over "Expression"; missing `.Add`
```

```text
Union case "Response" has no payload field "body"; available fields are
"status" and "value"
```

```text
Patterns combined with `|` must bind the same names; `.Response` binds "value"
but `.Cancelled` does not
```

### Tests

Cover declaration parsing, construction, defaults, generics, recursive unions,
unit cases, expression and statement cases, exhaustiveness, combined patterns,
renaming, discards, JSON, metadata, imported/re-exported unions, ownership,
readonly behavior, and generated C++ runtime execution.

### Non-goals

- Inheritance between cases.
- Per-case methods or custom constructors in the first version.
- Pattern guards.
- Open/extensible unions.
- Implicit conversion from a structurally similar class union.
- Layout guarantees for native ABI use.

---

## 5. Structured concurrency, cancellation, and deadlines

### Summary

Add lexical task groups whose child tasks cannot escape, plus cooperative
cancellation and optional deadlines. The scope guarantees that all accepted
children have completed before it exits.

```doof
with tasks := TaskGroup { timeoutMs: 5_000 } {
    left := async(tasks) computeLeft(input)
    right := async(tasks) computeRight(input)

    leftValue := try left.get()
    rightValue := try right.get()
    consume(leftValue, rightValue)
}
```

This complements actors. Actors own persistent mutable domains; task groups own
the lifetime of temporary concurrent work.

### Motivation

`Promise<T>` provides completion, but it does not express:

- which scope owns the work;
- whether a dropped promise leaves work running;
- how sibling work is cancelled after an early failure;
- how deadlines propagate; or
- when all child jobs are guaranteed to have stopped.

Structured concurrency makes those properties lexical and checkable. Adding an
`await` spelling alone would not solve task lifetime.

### Core types and syntax

`TaskGroup` is a compiler-known scoped runtime handle:

```doof
with tasks := TaskGroup() {
    task := async(tasks) compute(input)
    result := try task.get()
}
```

Configuration uses named construction:

```doof
with tasks := TaskGroup {
    timeoutMs: 10_000,
    cancelOnFailure: true,
} {
    // ...
}
```

`async(group)` accepts the same forms as existing `async`:

```doof
first := async(tasks) actor.method(argument)
second := async(tasks) isolatedFunction(argument)
third := async(tasks) {
    yield computeLocally(argument)
}
```

It returns `Task<T>`, not `Promise<T>`:

```doof
class Task<T> {
    get(): Result<T, TaskError>
    isCompleted(): bool
}
```

`Task<T>` is scoped to its group. It cannot be returned, stored in a field or
module binding, captured by work outside that group, sent to an actor, or used
after the group scope.

### Task errors

Use a payload-bearing union once available:

```doof
union TaskError {
    Cancelled
    DeadlineExceeded
    RuntimeFailure { message: string }
}
```

Until payload unions ship, the runtime can use equivalent nominal classes and a
type alias. A typed error distinguishes cancellation from bugs and deadlines
without parsing strings.

Existing `Promise<T>.get(): Result<T, string>` remains source-compatible during
an initial transition. Structured `Task<T>` can adopt `TaskError` independently.

### Scope-exit rules

A task group has two exit modes.

**Normal completion:**

- Every `Task<T>` must be observed with `get()`, consumed by a group aggregate,
  or cancelled and then observed.
- The group waits for all accepted children before leaving the scope.
- An unobserved task is a compile-time error because its failure would be
  silently discarded.

**Early completion:**

- `return`, `try` propagation, declaration-`else`, and `panic` request
  cancellation of unfinished children.
- The scope waits until every child has completed or acknowledged
  cancellation.
- The original control-flow result remains authoritative; cancellation cleanup
  does not replace it.

There is no implicit detachment. If long-lived work is desired, use an actor or
a future explicitly named application-runtime facility.

### Must-use analysis

Every structured task handle has one of these states:

- pending and unobserved;
- observed by `get()`;
- transferred to a group aggregate;
- cancelled and observed; or
- maybe observed across control-flow paths.

Normal scope exit requires no pending or maybe-observed handles. This extends
the existing principle that `Result` values must be handled.

```doof
with tasks := TaskGroup() {
    task := async(tasks) compute(input)
}
// Compile error: task may fail but was never observed.
```

The group itself is still responsible for runtime cleanup after a diagnostic-
free program takes an early exit.

### Cancellation

Cancellation is cooperative for running Doof code and immediate for accepted
work that has not started.

```doof
with tasks := TaskGroup() {
    token := tasks.cancellationToken

    task := async(tasks) {
        for item of work {
            try token.checkpoint()
            process(item)
        }
        yield result()
    }

    if noLongerNeeded {
        tasks.cancel()
    }

    handled := task.get()
}
```

The token is a deeply immutable, thread-safe runtime handle exposing:

```doof
class CancellationToken {
    isCancelled(): bool
    checkpoint(): Result<none, TaskError>
}
```

It is explicitly allowed across isolated async boundaries. It exposes no
user-mutable state and does not generalize actor-handle transfer.

Cancellation semantics:

- `cancel()` is idempotent.
- Children accepted but not started complete as `Cancelled`.
- Running children observe cancellation at explicit checkpoints or in standard
  library operations documented as cancellable.
- Cancellation does not asynchronously interrupt arbitrary user code.
- A child that ignores cancellation may delay group exit.
- Starting a new child after cancellation returns an already-cancelled task.

### Deadlines

`timeoutMs` establishes a monotonic deadline when the group is created.
Expiration requests cancellation and causes unfinished tasks to complete with
`DeadlineExceeded` once they stop.

Nested groups use the earlier of their configured deadline and their parent's
deadline. Wall-clock changes do not affect timeouts.

Standard library operations such as HTTP, database waits, and process waits may
accept a `CancellationToken` and deadline so native blocking work can wake
promptly. Native integrations declare whether they honor cancellation; the
compiler cannot infer that contract from C++.

### Failure propagation

With `cancelOnFailure: true`, a child that completes with an outer
`RuntimeFailure` or `DeadlineExceeded` requests cancellation of its unfinished
siblings. Domain-level `Failure<E>` returned as the child's successful value
does not trigger group cancellation automatically:

```doof
task: Task<Result<User, LookupError>> := async(tasks) lookupUser(id)
```

The outer `TaskError` reports scheduling/runtime failure. The inner
`LookupError` is ordinary application behavior. Keeping those channels separate
avoids treating expected domain failures as task crashes.

### Completion-order operations

Task groups provide aggregate operations corresponding to existing promise
array support:

```doof
next := tasks.takeFirstCompleted(pending)
all := tasks.waitAll(pending)
```

Suggested signatures:

```doof
takeFirstCompleted<T>(tasks: Task<T>[]): Result<T, TaskError>
waitAll<T>(tasks: Task<T>[]): Result<T[], TaskError>
```

The aggregate consumes the listed task handles for must-use analysis. With
`cancelOnFailure`, `waitAll` cancels remaining siblings after the first task
error, waits for them, and returns the first error in acceptance order for
determinism.

### Actors and callbacks

`async(group) actor.method(...)` schedules the same actor message as existing
`async`, but associates its result lifetime with the group. Cancelling the task
before the message starts removes or skips the message. Once an actor message
begins, cancellation remains cooperative and must not violate actor mailbox
ordering.

Posted actor-affine callbacks may also be group-owned in a later extension.
The initial version should limit structured spawning to the three already
supported async forms.

### Ownership interaction

Moving an owned value into a task transfers ownership when the task is accepted:

```doof
payload: owned Payload := buildPayload()

with tasks := TaskGroup() {
    task := async(tasks) process(move payload)
    output := try task.get()
}
```

If validation fails before acceptance, the source binding remains initialized.
After acceptance, cancellation destroys the payload inside the task unless the
task returns it through an explicit result. There must be no state where both
the caller and child believe they own the graph.

### Runtime lowering

Each group owns shared runtime state containing:

- cancellation status and reason;
- optional monotonic deadline;
- accepted-child count;
- completion notification;
- child result states; and
- configuration such as `cancelOnFailure`.

Each child scheduler job references that state. Scope exit performs cancellation
when required and waits without holding a runtime CPU token, using the same
worker-token release mechanism as `Promise.get()`.

The generated scope guard guarantees cleanup on every Doof exit path. The
checker still performs must-use validation; the runtime guard is not a
substitute for handling task results.

### Diagnostics

Examples:

```text
Task "thumbnail" may leave this TaskGroup scope without its result being
observed; call `get()`, pass it to a group aggregate, or use an Actor for
detached work
```

```text
Task<T> belongs to TaskGroup "tasks" and cannot be returned from its scope
```

```text
TaskGroup "tasks" is not in scope here; structured tasks cannot outlive their
owning group
```

### Tests

Coverage must include normal join, early return, `try` propagation, panic
cleanup, cancellation before start, cooperative cancellation while running,
deadline expiry, nested deadlines, actor mailbox ordering, one-worker progress,
must-use branches, aggregate ordering, owned arguments, native cancellation,
and runtime shutdown.

Tests using the shared scheduler must remain serial.

### Non-goals

- Preemptive cancellation of arbitrary code.
- A promise-compatible `await` keyword in the first version.
- Detached tasks owned by a lexical group.
- Changing actor serial execution or boundary rules.
- Treating application `Result` failures as runtime task failures.

---

## 6. Structural interface conformance for structs

### Summary

Allow structs to satisfy structural interfaces automatically and to declare
`implements` for early validation.

```doof
interface Measurable {
    area(): double
}

struct Rectangle implements Measurable {
    width, height: double

    area(): double => width * height
}

function printArea<T: Measurable>(value: T): none {
    println(value.area())
}

printArea(Rectangle { width: 4.0, height: 3.0 })
```

### Motivation

Structs already support fields, methods, statics, generics, JSON, metadata, and
nominal identity. Excluding them from interfaces prevents lightweight value
types from participating in the same reusable APIs as classes and creates an
arbitrary boundary in capability-bearing generic constraints.

### Conformance rules

A struct satisfies an interface when, after generic substitution:

- every required instance field exists with a compatible type and mutability;
- every required instance method has a compatible parameter and return type;
- every required static method exists with a compatible signature;
- visibility permits the conformance at the declaration site; and
- required isolation and future ownership effects are satisfied.

The rules are identical to class structural conformance unless value semantics
require an explicit difference below.

`implements` remains optional:

```doof
struct Point implements Named, Measurable {
    readonly name: string
    x, y: double

    area(): double => 0.0
}
```

An explicit clause validates immediately even when no interface-typed use is
reached.

### Value semantics through interfaces

Converting a struct to an interface copies the struct value into the interface
container:

```doof
struct Counter {
    let value: int
    increment(): none { value += 1 }
}

interface Incrementable {
    increment(): none
}

let original = Counter { value: 0 }
let erased: Incrementable = original
erased.increment()

// original.value remains 0; the interface contains its own copied Counter.
```

Copying an interface value containing a struct also copies that struct. This
preserves struct value semantics and avoids invisible boxing identity.

For mutable struct methods, the interface receiver must be held in a context
that permits mutation. A deeply readonly interface value rejects a method that
mutates the contained struct. The checker should infer receiver mutation in the
same semantic analysis used for readonly compatibility; the C++ emitter must
not infer mutability from method syntax.

### Interface representation

An interface's closed-world representation may contain both reference and
value alternatives:

```cpp
using Measurable = std::variant<
    std::shared_ptr<Circle>,
    Rectangle
>;
```

Class alternatives retain reference identity. Struct alternatives are stored
and copied directly. Dispatch uses `std::visit`, selecting `->` for class
alternatives and `.` for struct alternatives from checker-provided
representation metadata.

This mixed representation is internal. Source behavior is defined by class
reference semantics and struct value semantics, not by variant layout.

### Narrowing and cases

Type patterns include struct implementations:

```doof
case value {
    rectangle: Rectangle -> println(rectangle.width)
    circle: Circle -> println(circle.radius)
}
```

Narrowing an interface-held struct produces a value copy. Narrowing a class
produces the existing shared class reference. This difference follows the
underlying nominal type's normal assignment behavior.

When a `case` expression exhaustively covers an interface, the checker includes
all reached class and struct implementations in the closed world.

### Generic structs and interfaces

Concrete generic struct instantiations may satisfy concrete generic interfaces:

```doof
interface Reader<T> {
    read(): T
}

struct ConstantReader<T> implements Reader<T> {
    value: T
    read(): T => value
}

reader: Reader<int> := ConstantReader<int> { value: 42 }
```

Conformance and emitted alternatives are recorded per concrete specialization.
Open C++ templates are not exposed as interface implementations.

### Actor boundaries and readonly values

A struct does not become safe to share merely because it is stored in an
interface. Boundary checking examines every concrete alternative recursively.

- A deeply immutable struct alternative may cross by copy.
- A mutable value-only struct may cross by copy when every field is itself a
  value type and copying cannot preserve an alias to mutable storage.
- A struct containing mutable collections is rejected as a shared interface
  argument.
- A future `owned` interface value may move a contained mutable struct across a
  boundary if every active representation rule preserves uniqueness.

Widening to an interface cannot hide mutable storage.

### JSON and metadata

Interface JSON dispatch should include struct implementations once struct
conformance exists. Because struct `fromJsonValue` returns a direct value, the
generated dispatcher promotes that value directly into the interface variant.

The discriminator requirements remain unchanged: every implementation must
share a literal string field with a distinct value.

Reflection records whether an implementation is a class or struct only when
that distinction affects invocation or schema generation. It should not expose
C++ storage details.

### Lowering contract

The checker and monomorphization plan record, for each concrete interface:

- all reached class and struct implementations;
- the substituted method table;
- each alternative's value/reference representation;
- receiver mutability and isolation effects; and
- JSON discriminator information when demanded.

The emitter uses that plan to build the variant and dispatch calls. Existing
filters that skip `struct_` declarations must be removed only after all
consumers understand value alternatives.

### Diagnostics

Examples:

```text
Struct "Point" does not satisfy interface "Named": missing readonly field
"name: string"
```

```text
Cannot call mutating method "increment" through readonly interface value
"counter"
```

```text
Interface "Shape" cannot cross this actor boundary because implementation
"Polygon" contains mutable field "vertices"
```

### Tests

Coverage should include implicit and explicit conformance, fields, methods,
statics, generic substitutions, mixed class/struct interfaces, interface copy
semantics, mutation, readonly calls, narrowing, exhaustive cases, JSON dispatch,
actor boundaries, imports, and emitted C++ behavior.

### Non-goals

- Changing structs into reference types when widened.
- Struct inheritance.
- Weak references to structs.
- Destructors on structs.
- Open-world runtime registration of implementations.

---

## 7. Package-scoped visibility

### Summary

Add an `internal` visibility modifier for declarations and members intended to
be shared across files in one package but hidden from dependent packages.

```doof
export internal class ParserState {
    tokens: Token[]
}

export internal function parseExpression(state: ParserState): Expression {
    // ...
}
```

The declaration is exportable and importable inside its package, but it is not
part of the package's public API.

### Motivation

File-scoped `private` is an excellent default for small modules. Larger
packages, especially a compiler, need implementation types shared by several
focused files. Making those types public prevents refactoring and leaks
internal architecture to dependants. Combining modules to preserve privacy
works against Doof's source-ownership guidance.

### Visibility levels

Doof gains three source visibility levels:

| Visibility | Same file | Same package | Dependent package |
| --- | --- | --- | --- |
| `private` | Yes | No | No |
| `internal` | Yes | Yes | No |
| public/default | Yes | Yes | Yes when exported |

Top-level declarations still need an export surface to be imported from
another file. The recommended spelling is `export internal`:

```doof
export internal type CheckedNode = CheckedExpression | CheckedStatement
export internal function decorate(node: Node): CheckedNode => check(node)
```

`internal` without `export` is allowed but redundant for top-level declarations
because an unexported declaration is already file-local. The compiler should
warn and suggest either `private` or `export internal`.

Class and struct members use `internal` without `export`:

```doof
export class Client {
    internal connection: NativeConnection

    internal reconnect(): Result<none, NetworkError> {
        // ...
    }

    request(input: Request): Result<Response, NetworkError> {
        // Public method may use internal implementation details.
    }
}
```

Recommended modifier order is:

```text
[export] [private | internal] [isolated] [static] declaration
```

`private` and `internal` are mutually exclusive.

### Package identity

Visibility uses resolved package identity, not filesystem-prefix comparison.

- Modules belonging to the same `doof.json` package are internal peers.
- Dependency packages are distinct even if their source happens to be checked
  out beneath the root directory.
- Different versions or commits of the same package name remain distinct
  resolved package instances.
- Standard packages are separate from user packages.
- For a manifestless single-entry build, the compiler creates one implicit
  package identity rooted at the entry's module graph.

This prevents symlinks, vendor layout, or duplicate names from widening access.

### Imports and re-exports

An internal export may be imported only by a module with the same resolved
package identity:

```doof
// checker-state.do
export internal class CheckerState { /* ... */ }

// checker-expressions.do, same package
import { CheckerState } from "./checker-state" // Valid.
```

A dependent package receives an error:

```doof
import { CheckerState } from "doof-compiler/checker-state"
// Error: CheckerState is internal to package "doof-compiler".
```

Re-exporting cannot widen visibility:

```doof
// Same package barrel.
export { CheckerState } from "./checker-state"
```

The re-export remains internal automatically. An explicit public re-export is
rejected. Namespace imports may contain internal names only for same-package
consumers; public metadata and completion surfaces filter them for dependants.

### Public API leakage

A public declaration may use an internal type in its implementation but not in
its externally visible signature:

```doof
export internal class ConnectionPool { /* ... */ }

export class Client {
    internal pool: ConnectionPool // Valid internal member.

    request(input: Request): Response { /* ... */ }
}
```

These public surfaces are rejected:

```doof
export function pool(): ConnectionPool

export class Client {
    connectionPool(): ConnectionPool
}
```

Leak checking recursively examines generic arguments, unions, tuples,
callbacks, fields, defaults whose inferred types are public, and generated
metadata schemas. A private or internal member may freely mention internal
types.

### Construction and member access

Internal fields without defaults block construction from other packages but not
from another file in the same package:

```doof
export class Config {
    internal token: string
    name: string
}

// Same package: valid.
config := Config { token: secret, name: "prod" }

// Dependent package: construction is unavailable because token is inaccessible.
```

If every inaccessible internal field has a default, external construction may
omit those fields, following the existing private-field rule.

### Metadata, JSON, and Wasm exports

Generated JSON continues to include internal fields just as it includes private
fields. Visibility is a source-access rule, not an automatic wire-redaction
rule. Libraries handling secrets must use explicit DTOs rather than assuming
visibility changes serialization.

Public `.metadata`, schema, and Wasm export surfaces must not reveal internal
types. A class whose reflected public method mentions an internal type is
ineligible for public reflection and receives a compile-time diagnostic.

Internal descriptions may remain in compiler-internal metadata but are omitted
from package-facing metadata artifacts.

### Native interop

An `export internal import class` or `export internal import function` is
available to bridge modules within the declaring package and hidden from
dependants. Native C++ symbol visibility is not implied; platform linker
visibility remains a build-system concern.

### Lowering

Visibility is enforced by resolution and API validation. Generated C++ may use
ordinary namespace-visible declarations because emitted identifiers and headers
are not the Doof source API.

Every symbol records:

- declaring module;
- resolved package identity;
- source visibility; and
- effective visibility after re-export chains.

The resolver validates access at each import and member expression. A separate
public-surface pass rejects internal-type leakage even when all accesses inside
the defining package are otherwise valid.

### Diagnostics

Examples:

```text
"CheckerState" is internal to package "doof-compiler" and cannot be imported
by package "my-tool"
```

```text
Public function "connectionPool" exposes internal type "ConnectionPool" in
its return type; make the function internal or return a public abstraction
```

```text
Top-level `internal` declaration "helper" is not exported and is already
file-local; use `private` or `export internal`
```

### Tests

Coverage should include same-file, same-package, dependency-package, duplicate
package names at different commits, manifestless builds, local dependencies,
namespace imports, re-export chains, public API leakage, construction,
reflection, JSON, Wasm, native imports, mocks, and test modules.

### Non-goals

- C++ linker symbol visibility.
- Friend declarations.
- Per-dependent allowlists.
- Protected or subclass visibility.
- Making private members package-visible.

---

## Cross-feature example

The proposals are designed to compose. This example uses a payload union,
capability constraint, structured tasks, struct conformance, and internal
helpers:

```doof
export interface Command {
    isolated execute(): Result<Response, string>
}

export union Response {
    Text { value: string }
    Binary { value: readonly byte[] }
}

export struct HealthCheck implements Command {
    isolated execute(): Result<Response, string> {
        return Success { value: .Text { value: "ok" } }
    }
}

export internal function runOne<T: Command>(
    command: T,
): Result<Response, string> {
    return command.execute()
}

export function runAll<T: Command>(
    commands: readonly T[],
): Result<Response[], TaskError> {
    with tasks := TaskGroup { cancelOnFailure: true } {
        let pending: Task<Result<Response, string>>[] = []

        for command of commands {
            pending.push(async(tasks) runOne(command))
        }

        completed := try tasks.waitAll(pending)
        let responses: Response[] = []

        for result of completed {
            response := result else error {
                return Failure {
                    error: TaskError.RuntimeFailure {
                        message: error,
                    },
                }
            }
            responses.push(response)
        }

        return Success { value: responses }
    }
}
```

The example is illustrative rather than normative: exact error payloads and the
eventual standard task APIs should be settled with the corresponding proposal.

## Recommended implementation sequence

### Stage 0: semantic hardening

- Expand the invalid-program diagnostic corpus.
- Complete current named-union, reflection, and collection/default-inference
  roadmap items.
- Ensure emit-readiness validation covers every decorated semantic decision.

### Stage 1: low-runtime-risk additions

1. Named-union JSON dispatch.
2. Capability-bearing generic constraints.
3. Package-scoped visibility.
4. Struct structural interface conformance.

These features primarily extend resolver, checker, monomorphization, JSON, and
emission planning without changing the scheduler.

### Stage 2: nominal payload unions

1. Parse and resolve declarations and constructors.
2. Add exhaustive case matching and shallow field destructuring.
3. Lower the nominal variant representation.
4. Add JSON, schema, metadata, and Wasm integration.
5. Consider general class/struct destructuring patterns after the union path is
   stable.

### Stage 3: ownership

1. Add ownership-qualified semantic types.
2. Implement local affine flow and whole-binding moves.
3. Add non-escaping immutable borrows.
4. Integrate method receiver escape analysis.
5. Permit owned transfer at actor and async boundaries.
6. Add native ownership contracts.

Do not permit actor transfer merely because `std::move` can be emitted. The
source uniqueness proof must land first.

### Stage 4: structured concurrency

1. Add scoped `TaskGroup` and `Task<T>` checking.
2. Implement must-use and non-escape analysis.
3. Add runtime group join and early-exit cleanup.
4. Add cancellation tokens.
5. Add deadlines and cancellable standard-library integrations.
6. Integrate owned task arguments and results.

## Specification and documentation impact

If accepted, the proposals should update these specification areas:

- type aliases and JSON serialization for named-union dispatch;
- generics and interfaces for capability-bearing constraints;
- variables, functions, memory management, and concurrency for ownership;
- declarations and pattern matching for payload unions;
- concurrency and error handling for task groups;
- classes/interfaces for struct conformance; and
- modules, imports, exports, and access control for package visibility.

The Doof language skill should receive matching concise guidance only after the
normative specification is settled. Architecture and source-structure docs
should be updated when phase ownership or lowering changes, not merely because
this proposal document exists.

## Decisions required before implementation

The following choices should be resolved explicitly rather than discovered
during emitter work:

1. Whether `Self` is accepted in interface requirements with the first generic
   constraint release.
2. Whether `owned` is spelled as a type qualifier, binding modifier, or both.
3. Whether the first borrow release supports mutation or immutable access only.
4. Whether payload-union cases are always reference-backed or whether a later
   representation optimization may store non-recursive payloads directly.
5. Whether `kind` is permanently reserved as the payload-union JSON
   discriminator.
6. Whether structured task errors use a new `TaskError` immediately or retain
   `string` during migration.
7. Whether normal TaskGroup scope exit statically requires every task to be
   observed or permits an explicit group-level discard operation.
8. How manifestless multi-entry builds establish implicit package identity.

These are language-contract decisions. Each should be answered in the
specification before generated C++ shape or runtime convenience determines the
source semantics accidentally.
