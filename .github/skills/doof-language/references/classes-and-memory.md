# Doof Classes, Structs, and Memory Management Reference

## Class Declarations

```doof
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
When the expected type is a class or struct, `.member` may shorthand a static field or method on that type, for example `transform: Transform = .identity()`.

## Struct Declarations

```doof
struct Point {
    x: int
    y: int

    lengthSquared(): int => x * x + y * y
}
```

Structs are nominal value types. They use class-like syntax for fields, readonly fields, literal-valued fields, defaults, methods, static members, type parameters, construction, JSON, and metadata, but assignment, parameter passing, and return values copy the struct value.

Current v1 restrictions:

- Structs do not implement interfaces yet.
- Structs cannot declare destructors.
- Structs cannot use `weak` fields or be the target of `weak`.
- Avoid fluent `return this` identity patterns; return an explicit copied value instead.

### Field Modifiers

| Modifier | Behavior |
| --- | --- |
| none | shallow immutable field; mutable interiors remain usable |
| `let` | reassignable field |
| `readonly` | deeply immutable field |
| literal value after `:` | compile-time constant, for example `kind: "circle"` or `version: 1` |
| `private` | file-scoped visibility |

Assigning a bare field after construction is an error. Bare collection fields
still allow interior operations such as `.push(...)`; use `let` only when the
field slot itself must be reassigned.

## Construction

```doof
user := User { id: 1, name: "Alice" }
user := User(1, "Alice")

readonly name = "Alice"
user := User { id: 1, name }

extended := ExtendedConfig { ...base, timeout: 30 }
line := Line { start: { x: 0.0, y: 0.0 }, end: { x: 1.0, y: 1.0 } }
```

Rules:

- Named construction may omit fields that have defaults.
- Positional construction follows declaration order and may omit trailing defaults.
- If a class or struct has a static `constructor` method returning that type, or
  `Result<ThatType, E>` for fallible construction, direct construction delegates
  to `constructor`, uses its parameters for validation, and has the constructor
  method's return type. Inside that type's own `constructor` method, construction
  still uses fields so the factory can build the instance.
- Classes and structs with a dedicated `constructor` method are not eligible for automatic
  JSON serialization/deserialization.
- Name-value shorthand such as `{ name }` expands to `{ name: name }`.
- Spread fields work in named construction.
- A bare object literal expected as a class/struct union constructs the unique
  member matching its field shape. Value types do not resolve shape ties;
  ambiguous, unmatched, and spread-based literals require explicit nominal
  construction.

### Literal-Valued Fields in Construction

Nominal construction auto-fills literal-valued fields, while structural construction requires them explicitly. The older `const kind = "Success"` spelling is deprecated and remains accepted temporarily with a warning.

```doof
result1 := Success { value: 42 }
result2: Result = { kind: "Success", value: 42 }
```

## Methods and `this`

```doof
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

## Static Members

```doof
class Rectangle {
    width: int
    static kind = "rectangle"
    static describe(): string => "Rectangles"
}

rect := Rectangle { width: 10 }

Rectangle.kind
Rectangle.describe()
rect::kind
rect::describe()
```

Rules:

- Static methods cannot access instance state.
- Access statics with `.` through a named class or interface type.
- Access statics with `::` through an instance or interface value.
- `rect.kind` and `rect.describe()` are invalid for statics.
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

```doof
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

```doof
interface Drawable {
    draw(canvas: Canvas): none
}

interface Shape {
    area(): float
    static describe(): string
}
```

Rules:

- Interfaces are structural.
- Classes satisfy them automatically when structure matches.
- Structs do not satisfy interfaces in v1.
- `implements` is optional and mainly useful for documentation and early validation.
- Interface statics are checked structurally against class statics and are invoked from interface values with `::`.
- Interface members cannot be `private`.

## Memory Management

### Reference Counting

Class instances are reference-counted. When the last strong reference disappears, the destructor runs immediately.

Struct values are stored directly and copied by value. Nullable structs use an optional value representation in generated C++.

### Destructors

```doof
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

```doof
class TreeNode {
    children: TreeNode[] = []
    parent: weak TreeNode | none = none
}
```

- Use `weak` to break reference cycles.
- `weak` qualifies the whole type expression.
- Accessing a weak reference yields `Result<T, WeakReferenceError>`.
- `weak` is class-only; structs are value types and cannot be weak targets.

## Description Metadata

```doof
class Calculator "A simple calculator." {
    add "Adds two numbers."(a "First.": int, b "Second.": int): int => a + b
}

meta := Calculator.metadata
```

See [json-and-metadata.md](./json-and-metadata.md) for generated metadata, schemas, and `.invoke(...)` behavior.
