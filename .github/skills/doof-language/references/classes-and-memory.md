# Doof Classes, Structs, and Memory Management Reference

## Class Declarations

```doof check
function nextId(): int => 1

class User {
    readonly id: int
    let name: string
    email: string | none = none
    role: string = "user"
    version: 1

    greet(): string => "Hi, ${name}"

    private internalHelper(): none { }

    static constructor(name: string): User => User { id: nextId(), name: name }
}
```

Classes are nominal reference types with identity and shared ownership in generated C++.

Each field needs either a type annotation or a default so the compiler can determine its type.
Field and parameter defaults may call static methods, for example `Transform.identity()`.
When the expected type is a class or struct, `.member` may shorthand a static field of that type or a static method returning it, for example `transform: Transform = .identity()`. It works in any typed position (defaults, bindings, arguments). With an expected `T | none`, the field or method may also produce `T | none`: `parsed: Transform | none := .parse(text)`. Members of other types are errors.

## Struct Declarations

```doof check
struct Point {
    x: int
    y: int

    lengthSquared(): int => x * x + y * y
}
```

Structs are nominal value types. They use class-like syntax for fields, readonly fields, literal-valued fields, defaults, methods, static members, type parameters, construction, JSON, and metadata, but assignment, parameter passing, and return values copy the struct value.

Struct `==` compares all instance fields in declaration order using each field's
equality semantics; `!=` negates that result. Nested structs compare by value,
while class and mutable collection fields compare by reference. Static fields
are excluded, empty structs of the same type compare equal, and distinct nominal
types cannot be compared. `Assert.equal` uses the same rules.

Current v1 restrictions:

- Structs do not implement interfaces yet.
- Structs cannot declare destructors.
- Structs cannot use `weak` fields or be the target of `weak`.
- Structs cannot contain themselves by value (directly or via `T | none`, unions, tuples, `Result`, or other structs); use a class or collection for recursive data.
- Avoid fluent `return this` identity patterns; return an explicit copied value instead.

### Field Modifiers

| Modifier | Behavior |
| --- | --- |
| none | shallow immutable field; mutable interiors remain usable |
| `let` | reassignable field |
| `readonly` | deeply immutable field |
| literal value after `:` | compile-time constant, for example `kind: "circle"`, `version: 1`, or enum variant `kind: ShapeKind.Circle`; JSON decoding rejects a different value |
| `private` | file-scoped visibility |

Assigning a bare field after construction is an error. Bare collection fields
still allow interior operations such as `.push(...)`; use `let` only when the
field slot itself must be reassigned.

## Construction

```doof check
class User { id: int; name: string }
class Config { host: string = "localhost"; timeout: int = 10 }
struct Vec { x: float; y: float }
struct Line { start: Vec; end: Vec }
class Button { id: int; label: string }
class Panel { title: string; children: string[] }

function main(): none {
    first := User { id: 1, name: "Alice" }
    second := User(1, "Alice")

    name := "Alice"
    user := User { id: 1, name }

    base := Config {}
    extended := Config { ...base, timeout: 30 }
    line := Line { start: { x: 0.0, y: 0.0 }, end: { x: 1.0, y: 1.0 } }

    button := <Button id=1 label="Save"/>
    panel := <Panel title="Welcome">Hello {user.name}</Panel>
}
```

Rules:

- Named construction may omit fields that have defaults.
- Positional construction follows declaration order and may omit trailing defaults.
- A positional literal constructs its expected class or struct: `let p: Point = (1.0, 2.0)`,
  `draw((1.0, 2.0))`, `points.push((1.0, 2.0))`. Without a single expected class
  (including unions of several classes) `(a, b)` is a `Tuple`; `(a)` is just parentheses.
  Inside a generic body the expected class may use the body's own type parameters:
  `function tag<T>(v: T): Pair<T, int> => (v, 1)`. A call that is still inferring
  its type arguments gives the literal no class context; write them explicitly,
  as in `first<string>(("a", 1))`.
- If a class or struct has a static `constructor` method returning that type, or
  `Result<ThatType, E>` for fallible construction, direct construction delegates
  to `constructor`, uses its parameters for validation, and has the constructor
  method's return type. Inside that type's own `constructor` method, construction
  still uses fields so the factory can build the instance.
- Classes and structs with a dedicated `constructor` method are not eligible for automatic
  JSON serialization/deserialization.
- Name-value shorthand such as `{ name }` expands to `{ name: name }`.
- Generic class type arguments are inferred from named, positional, and tag
  construction arguments and the expected type: `Box { value: 42 }` is
  `Box<int>`. Every type parameter must be determined; `Container { result:
  Success { value: 42 } }` is an error until written `Container<int, string> { ... }`.
- Spread fields work in named construction. A construction or object literal
  takes at most one `...source` spread.
- Typed tags are named calls: classes and structs construct normally, while
  functions, callbacks, and callable members are invoked normally. Scalar
  attributes may be bare; general expressions use `{expression}`. Paired
  content becomes a contextually typed array argument named `children`.
- Tag callbacks may use contextual `=>` lambda syntax directly. The lambda
  inherits the expected callback's parameter names and types, so a callback
  typed `(event: Event): none` makes `event` available in
  `<Button onClick=>println(event.name)/>`. Zero-parameter callbacks remain
  available as `<Button onClick=>{ refresh() }/>`. This also works when the
  expected type is a union with one unique callback member, such as
  `((event: Event): none) | none`.
- A bare object literal expected as a class/struct union constructs the unique
  member matching its field shape. Value types do not resolve shape ties;
  ambiguous, unmatched, and spread-based literals require explicit nominal
  construction.

### Literal-Valued Fields in Construction

Nominal construction auto-fills literal-valued fields, while structural construction requires them explicitly. The older `const kind = "Success"` spelling is deprecated and remains accepted temporarily with a warning.

```doof check
class Loaded { kind: "Loaded"; value: int }
class Missing { kind: "Missing"; error: string }
type Lookup = Loaded | Missing

function main(): none {
    nominal := Loaded { value: 42 }
    structural: Lookup := { kind: "Loaded", value: 42 }
}
```

## Methods and `this`

```doof check
class Counter {
    let count = 0

    increment(n: int): none { count += n }
    getCount(): int => count
    reset(count: int): none { this.count = count }
    add(n: int): Counter { count += n; return this }
}
```

- Instance methods get implicit `this` access.
- Use `this.` only for disambiguation.
- Fluent APIs commonly return `this`.
- Methods omit the `function` keyword. The older `function name(...)` class
  spelling is deprecated and warns; free functions still use `function`.
- Canonical method modifiers are `[private] [isolated] [static] name(...)`.
  `isolated` is valid on both instance and static methods.

## Static Members

```doof check
class Rectangle {
    width: int
    static kind = "rectangle"
    static describe(): string => "Rectangles"
}

rect := Rectangle { width: 10 }

Rectangle.kind
Rectangle.describe()
```

Rules:

- Static methods cannot access instance state.
- Access statics only through the class name: `Rectangle.kind`.
- Instances never reach statics; `rect.kind` is an error that names `Rectangle.kind`.
- Statics of a generic class belong to one instantiation, with separate static
  fields per instantiation. Write it explicitly as `Channel<string>.tag()` or
  `Channel<int>.count`, or let a static call infer it from its arguments:
  `Channel.constructor(onString)` calls it on `Channel<string>`. Static fields
  and statics whose arguments don't determine `T` need the explicit form.
- Interfaces may declare `static name: T`, `static readonly name: T`, and bodyless
  `static method(...)` members as a contract for generic bounds. With `T: Iface`,
  `T.name` / `T.method()` reach the concrete argument's statics (classes and structs
  only; static fields must be non-`let`). Interface values never satisfy such a bound.
- Static field defaults at module scope must satisfy the construction-only
  initializer rules and run in module/declaration order.
- Construction-only non-native struct values may initialize module bindings
  and static fields; source-level readonly and literal-valued field rules still
  apply after initialization.
- This subset includes named and positional construction and signed numeric
  literals, pure arithmetic/string concatenation, and references to immutable
  module bindings initialized directly from scalar constants. It excludes
  custom constructors, ordinary function calls, and reads of dynamically
  initialized bindings.

## Private Members

`private` is file-scoped.

```doof check
class Config {
    private secret: string
    name: string
}

export function makeConfig(name: string): Config {
    return Config { secret: "hidden", name: name }
}
```

Private fields without defaults block external construction.

## Interfaces

```doof check
class Canvas {}

interface Drawable {
    draw(canvas: Canvas): none
}

interface Shape {
    area(): float
    static describe(): string
}
```

Rules:

- Interfaces are structural. They can constrain generics (`T: Reader<int>`), exposing their instance contract without erasing the concrete `T`.
- Classes satisfy them automatically when structure matches.
- Generic class and interface arguments are substituted before structure is compared.
- Writable (`let`) interface fields require identical implementation types after substitution; read-only field compatibility remains covariant.
- Interface method parameters match exactly; implementation returns may be narrower when assignable to the required return type.
- An unresolved inferred field cannot establish structural conformance.
- Structs do not satisfy interfaces in v1.
- `implements` is optional and mainly useful for documentation and early validation.
- Interfaces declare instance members only; class statics do not take part in structural matching. Static interface members and `T.member` access through type parameters are reserved.
- Interface members cannot be `private`.
- An interface may have no implementing class (for example a library interface
  that consumers implement). Helpers declared against it still check and
  compile; with no implementations no value exists, member access cannot run,
  and `.fromSerialValue()` always fails.

## Memory Management

### Reference Counting

Class instances are reference-counted. When the last strong reference disappears, the destructor runs immediately.

Struct values are stored directly and copied by value. Nullable structs use an optional value representation in generated C++.

### Destructors

```doof check
function closeRawHandle(handle: int): none {}

class FileHandle {
    handle: int

    destructor {
        closeRawHandle(handle)
    }
}
```

Rules:

- At most one destructor per class.
- Structs cannot declare destructors.
- Destructors cannot be called directly.
- They run on scope exit regardless of exit path.
- Locals are destroyed in reverse declaration order.

### Weak References

```doof check
class TreeNode {
    children: TreeNode[] = []
    parent: weak TreeNode | none = none
}
```

- Use `weak` to break reference cycles.
- `weak` starts a type and qualifies all of it: `weak A | B` is `weak (A | B)`. `A | weak B` is an error.
- `weak A | none`, `(weak A) | none`, and `weak (A | none)` are one type. Other weak/strong union mixes are errors.
- Collections need grouping: `(weak A)[]` is an array of weak references, `Map<K, weak V>` holds weak values, `weak (A[])` weakly references the array. Bare `weak A[]` or `weak Map<...>` is rejected as ambiguous.
- Accessing a weak reference yields `Result<T, WeakReferenceError>`.
- A `case` weak subject is read once: `Success` retains a live target and `Failure` reports expiration. An absent nullable weak reference is `Success(none)`.
- Weak targets are classes, interfaces, arrays, maps, sets, and unions of them (with `none`). An interface target such as `weak Shape | none` weakly references whichever implementing class it holds.
- Weak references widen where the referent keeps its identity: `weak Circle` fits `weak Shape`, `weak (Circle | Label)`, or `weak (Shape | none)`. Collection arms must match exactly, and weak references never narrow.
- `weak` is class-only; structs are value types and cannot be weak targets.

## Description Metadata

```doof check
class Calculator "A simple calculator." {
    add "Adds two numbers."(a "First.": int, b "Second.": int): int => a + b
}

function main(): none {
    meta := Calculator.metadata
}
```

See [json-and-metadata.md](./json-and-metadata.md) for generated metadata, schemas, and `.invoke(...)` behavior.
