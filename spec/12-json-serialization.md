# 12. JSON Serialization

Doof provides built-in JSON serialization and deserialization for class and struct instances. Nominal objects with all-serializable fields and no dedicated `constructor` method are eligible for `.toSerialObject()` and `.fromSerialValue()` with no annotations or special syntax. JSON support code is generated on-demand: the compiler only emits serialization methods when your code actually uses these intrinsics.

## Overview

```doof check
class Point {
  x, y: float
}

p := Point { x: 1.5, y: 2.5 }
json := p.toSerialObject()               // SerialObject
result := Point.fromSerialValue(json)    // Result<Point, string>
println(result.isSuccess())              // true
```

Structs use the same source-level JSON API and return `Result<StructName, string>` from `.fromSerialValue()`, but the generated C++ stores and returns direct values rather than `shared_ptr` objects.

When you need text rather than structured JSON, use the standard JSON helpers:

```doof check
import { parseJsonValue, formatJsonValue } from "std/json"

class Point { x, y: float }

p := Point { x: 1.5, y: 2.5 }
text := formatJsonValue(p.toSerialObject())
parsed := parseJsonValue(text)         // Result<SerialValue, string>
println(text)                          // {"x":1.5,"y":2.5}
```

`SerialValue` objects preserve insertion order for object keys. `formatJsonValue(...)` emits object members in that order, and generated `.toSerialObject()` methods emit class or struct fields in declaration order.

## On-Demand Generation

JSON methods are only generated for classes, structs, and supported interfaces where user code actually accesses `.toSerialObject()` or `.fromSerialValue()`. If a program never calls these methods, no nominal-object JSON code is generated.

Generation is transitive and direction-specific: if nominal object `A` has a field of type `B`, calling `A.toSerialObject()` generates `toSerialObject()` for `B`, while calling `A.fromSerialValue()` generates `fromSerialValue()` for `B`. Neither operation generates the unused opposite direction.

```doof check
import { formatJsonValue } from "std/json"

class Inner { value: int }
class Outer { inner: Inner }

json := Outer { inner: Inner { value: 42 } }.toSerialObject()
println(formatJsonValue(json))  // {"inner":{"value":42}}
```

## Serialization — `.toSerialObject()`

Every eligible class or struct instance has a `.toSerialObject()` method that returns a `SerialObject` value. `SerialObject` is the intrinsic alias for `readonly Map<string, SerialValue>`, so it can still be passed anywhere a `SerialValue` is expected.

```doof check
import { formatJsonValue } from "std/json"

class User {
  name: string
  age: int
  private email: string
}

u := User { name: "Alice", age: 30, email: "alice@example.com" }
println(formatJsonValue(u.toSerialObject()))
// {"name":"Alice","age":30,"email":"alice@example.com"}
```

### Rules

- All fields are serialized, including `private` and `readonly` fields.
- Literal-valued fields are serialized with their compile-time values.
- Serialization is deep: nested class/struct instances, arrays of serializable nominal objects, and tuples are serialized recursively.
- Multi-name fields (`x, y, z: float`) produce separate JSON object keys.
- Field order follows declaration order.

### Serializable Field Types

| Doof Type | JSON Representation |
|-----------|-------------------|
| `byte`, `int`, `long` | JSON number; decoding requires a whole number in range |
| `float`, `double` | JSON number |
| `string` | JSON string |
| `char` | JSON string (single character) |
| `bool` | JSON boolean |
| `none` | JSON `null` |
| Class or struct instances | JSON object (recursive) |
| Non-generic interfaces | The implementation's JSON object (see [Interface Serialization](#interface-serialization)) |
| `T[]` | JSON array |
| `Tuple<T1, T2, ...>` | JSON array |
| `Map<string, T>` | JSON object when `T` is serializable |
| Enums | JSON backing value (int or string) |
| `T | none` | Value or JSON `null` |
| Unions with one member per JSON kind | The held member's JSON value, or `null` for `none` (see [Union-Typed Fields](#union-typed-fields)) |
| `SerialValue` | Preserved as-is |

### Non-Serializable Types

The following types are not JSON-serializable. A compile-time error is produced if `.toSerialObject()` or `.fromSerialValue()` is used on a class or struct containing these field types:

- Function types (`(value: int): string`)
- `weak` references
- `Actor<T>`
- `Promise<T>`
- `Result<T, E>`
- Classes or structs with a dedicated static `constructor(...): Self` or
  `constructor(...): Result<Self, E>` method

```doof reject
class Bad {
  callback: (value: int): none
}

b := Bad { callback: (x) => println(x) }
b.toSerialObject()  // ❌ compile error: callback is not serializable
```

Nominal objects with a dedicated `constructor` method are excluded because custom
construction usually encodes invariants that the automatic field-by-field JSON
deserializer cannot safely recreate.

## Deserialization — `.fromSerialValue()`

Every eligible class or struct has a `.fromSerialValue(json: SerialValue, lenient: bool = false)` method accessible on the type name that returns `Result<TypeName, string>`.

```doof check
class Point { x, y: float }

result := Point.fromSerialValue({ x: 1.5, y: 2.5 })

case result {
  p: Success -> println("Got point: ${p.value.x}, ${p.value.y}")
  e: Failure -> println("Parse error: ${e.error}")
}
```

Generic functions can call `.fromSerialValue()` on a type parameter only when that
parameter has the compiler-known `Serializable` constraint:

```doof check
class User { name: string }

function decode<T: Serializable>(json: SerialValue): Result<T, string> {
  return T.fromSerialValue(json)
}

payload: SerialValue := { name: "Ada" }
user := decode<User>{ json: payload }
println(user.isSuccess())  // true
```

`value.toSerialObject()` is likewise available on a `Serializable` parameter's values.

A type parameter bounded by an ordinary interface also gets `T.fromSerialValue(...)`
and `value.toSerialObject()` implicitly; the interface need not declare them (they
are reserved names). Each concrete argument must then be a class or struct eligible
for that direction (`fromSerialValue` also accepts enums and interfaces that
`Interface.fromSerialValue` could decode directly; `toSerialObject` also accepts
interfaces whose `value.toSerialObject()` is available); otherwise compilation reports
an error at the member access naming the argument type. The generated JSON code is
emitted for the concrete arguments, exactly as for direct calls.

These implied members keep their static/instance split for every type parameter:
`T.fromSerialValue(...)` is reached only through the type, and
`value.toSerialObject()` only through a value. `T.toSerialObject` and
`value.fromSerialValue(...)` are errors.

`Serializable` is a constraint-only intrinsic. It is not a normal value type,
and each concrete type argument must be a class or struct whose fields are JSON-serializable.
The concrete nominal-object JSON methods are still generated on demand when the generic is
instantiated.

### Required vs Optional Fields

Deserialization follows the same rules as object construction:

- Fields without a default initializer are required.
- Fields with a default initializer are optional; the default is used when absent.
- Literal-valued fields are auto-filled; if present in the JSON object, their value must match the compile-time value.

```doof check
class Config {
  host: string
  port: int = 8080
  version: "1.0"
}

defaults := Config.fromSerialValue({ host: "localhost" })
// Success: Config { host: "localhost", port: 8080, version: "1.0" }

missing := Config.fromSerialValue({ port: 3000 })
// Failure: "Missing required field \"host\""

mismatched := Config.fromSerialValue({ host: "localhost", version: "2.0" })
// Failure: "Field \"version\" must be \"1.0\" but got \"2.0\""
println(defaults.isSuccess() && missing.isFailure() && mismatched.isFailure())  // true
```

### Type Validation

Field values are checked during deserialization:

```doof check
class Point { x, y: float }

result := Point.fromSerialValue({ x: "not a number", y: 2.5 })
// Failure: "Field \"x\" expected number but got string"
println(result.isFailure())  // true
```

Integral fields (`byte`, `int`, `long`) accept any JSON number whose value is
whole and inside the field type's range, so `3.0` decodes as `3`. Fractional or
out-of-range values fail instead of truncating or wrapping:

```doof check
class Counter { count: int }

whole := Counter.fromSerialValue({ count: 3.0 })    // Success: Counter { count: 3 }
result := Counter.fromSerialValue({ count: 1.5 })
// Failure: "Field \"count\" expected int but got number"
println(whole.isSuccess() && result.isFailure())  // true
```

### Unknown Fields

Extra object fields that do not correspond to class fields are ignored:

```doof check
class Point { x, y: float }

result := Point.fromSerialValue({ x: 1.0, y: 2.0, z: 3.0 })
// Success: Point { x: 1.0, y: 2.0 }
println(result.isSuccess())  // true
```

### Non-Object Inputs

`.fromSerialValue()` expects a JSON object. Passing a non-object `SerialValue` fails:

```doof check
class Point { x, y: float }

result := Point.fromSerialValue("not an object")
// Failure: "Expected JSON object"
println(result.isFailure())  // true
```

If your input starts as text, import `parseJsonValue` from `std/json` and handle that result separately.

### Lenient Mode

Passing `true` for the optional `lenient` parameter enables a limited set of scalar coercions during deserialization while keeping the default strict behaviour unchanged.

```doof check
class Todo {
  title: string
  done: bool
}

result := Todo.fromSerialValue({ title: none, done: 1 }, true)
// Success: Todo { title: "", done: true }
println(result.isSuccess())  // true
```

When `lenient` is `true`:

- Required `string` fields accept JSON `null` (source `none`) as `""`.
- `string` fields also accept booleans and numbers via stringification.
- `bool` fields accept booleans, numbers (`0` => `false`, non-zero => `true`), and strings `"true"`, `"false"`, `"1"`, and `"0"`.
- Numeric fields accept booleans as `1` or `0`.

Lenient mode does not relax structural requirements: objects must still be objects, arrays must still be arrays, required fields must still be present unless they have defaults, and unsupported coercions still fail.

## Interface Serialization

A value of a non-generic interface type has a `.toSerialObject()` method that
encodes the value's runtime implementation exactly as that class's own
`.toSerialObject()` would. Encoding needs no discriminator, but an
implementation's literal-valued fields are encoded like any other field, so a
discriminated interface round-trips through `Interface.fromSerialValue`.

```doof check
import { formatJsonValue } from "std/json"

interface Pet {
  speak(): string
}

class Dog implements Pet {
  name: string
  speak(): string => "woof"
}

class Cat implements Pet {
  lives: int
  speak(): string => "meow"
}

pet: Pet := Dog { name: "Rex" }
println(formatJsonValue(pet.toSerialObject()))  // {"name":"Rex"}
```

Every implementing class must support automatic JSON serialization; the error
names the first class that does not. Interfaces are structural, so this includes
every class whose shape satisfies the interface, whether or not it declares
`implements`. An interface with no implementing classes has no values, so encoding
it is always accepted. Generic interfaces cannot be encoded.

```doof reject
interface Pet {
  speak(): string
}

class Dog implements Pet {
  name: string
  speak(): string => "woof"
}

class Robot implements Pet {
  onSpeak: (): string
  speak(): string => onSpeak()
}

pet: Pet := Dog { name: "Rex" }
pet.toSerialObject()  // ❌ implementing class "Robot" does not support automatic JSON serialization
```

## Interface Deserialization

Interfaces can be deserialized using a shared literal-valued discriminator field. All implementing classes must share a literal-valued field with the same name and distinct string values.

```doof check
interface Shape {
  area(): float
}

class Circle implements Shape {
  kind: "circle"
  radius: float

  area(): float => 3.14159f * radius * radius
}

class Rect implements Shape {
  kind: "rect"
  width, height: float

  area(): float => width * height
}

result := Shape.fromSerialValue({ kind: "circle", radius: 5.0 })
unknown := Shape.fromSerialValue({ kind: "triangle", base: 3.0 })
// Failure: "Unknown kind: \"triangle\""
println(result.isSuccess() && unknown.isFailure())  // true
```

### Discriminator Requirements

- All implementing classes must share a literal-valued field with the same name, such as `kind`.
- Each implementing class must use a distinct string discriminator value.
- If these requirements are not met, using `.fromSerialValue()` on the interface is a compile-time error.
- An interface with no implementing classes always fails to decode, returning
  `Failure("Interface Animal has no implementing classes")` rather than a
  compile-time error, so library helpers still check on their own.

```doof reject
interface Animal {}

class Dog implements Animal {
  name: string
}

class Cat implements Animal {
  name: string
}

Animal.fromSerialValue({})  // ❌ implementing classes must share a literal string discriminator
```

### Unknown Discriminator Values

A discriminator value that names no implementing class fails at run time, as
the `unknown` binding in the example above shows:
`Failure("Unknown kind: \"triangle\"")`.

### Interface-Typed Fields

Interface types may appear in fields, array elements, string-keyed map values,
tuples, and nullable fields. Each direction applies its own interface rule:
encoding a containing class requires the interface to be encodable, and decoding
it requires the interface's discriminator. Recursive interfaces are supported.

```doof check
import { formatJsonValue } from "std/json"

interface Node {
  weight(): int
}

class Leaf implements Node {
  kind: "leaf"
  value: int
  weight(): int => value
}

class Branch implements Node {
  kind: "branch"
  children: Node[]

  weight(): int {
    let total = 0
    for child of children { total += child.weight() }
    return total
  }
}

class Tree {
  root: Node
}

tree := Tree { root: Branch { children: [Leaf { value: 1 }, Leaf { value: 2 }] } }
json := tree.toSerialObject()
println(formatJsonValue(json))
// {"root":{"kind":"branch","children":[{"kind":"leaf","value":1},{"kind":"leaf","value":2}]}}
restored := Tree.fromSerialValue(json)
println(restored.isSuccess())  // true
```

An unknown discriminator inside a nested value reports its path, for example
`Field "root": Field "children": [0]: Unknown kind: "twig"` for a `Tree` whose
first child has `kind: "twig"`.

### Union-Typed Fields

A field, array element, map value, or tuple element may be a union of two or
more members, optionally with `none`. Each member must have one JSON kind:

| Member | JSON kind |
|---|---|
| `string`, `char`, string-backed enums | string |
| `byte`, `int`, `long`, `float`, `double`, int-backed enums | number |
| `bool` | boolean |
| Arrays and tuples | array |
| Classes, interfaces, and `Map<string, T>` | object |

`SerialValue` and structs cannot be union members. Encoding writes the held
member's own JSON value, or `null` for `none`. Decoding dispatches on the JSON
value's kind before any lenient conversion, so each kind may have only one
member. The exception is classes and interfaces: each interface member stands
for its implementing classes, a class reached through several members counts
once, and all of them may share the object kind when every class is
non-generic and has a literal-valued string discriminator with distinct
values, the same rule as interfaces:

```doof check
interface Shape { area(): double }

class Circle implements Shape {
  kind: "circle"
  radius: double
  area(): double => radius * 2.0
}

class Note {
  kind: "note"
  text: string
}

class Canvas {
  id: int | string
  focus: Shape | Note | string | none = none
}

canvas := Canvas { id: "main", focus: Circle { radius: 1.0 } }
restored := Canvas.fromSerialValue(canvas.toSerialObject())
println(restored.isSuccess())  // true
```

A JSON value whose kind has no member fails with the expected kinds, as in
`Field "id" expected int or string but got boolean`. A member that rejects a
value of its kind reports its own error, such as `Field "id": Expected int but
got number` for `1.5`.

A union with two members of one JSON kind, such as `int | double`,
`char | string`, or `Map<string, int> | Note`, or with classes that lack a
shared discriminator, still encodes. Decoding it is a compile error that
names the field and the clash:

```doof reject
class Circle { radius: double }
class Note { text: string }
class Loose { pick: Circle | Note }
class Reading { value: int | double }

Loose { pick: Note { text: "n" } }.toSerialObject()
Reading { value: 1 }.toSerialObject()
Loose.fromSerialValue({ pick: { text: "n" } })  // ❌ field "pick" needs a shared discriminator
Reading.fromSerialValue({ value: 1 })           // ❌ int and double both decode from a JSON number
```

## Named Union Alias Deserialization

Named union aliases over classes can also be deserialized when they follow the same discriminator rule as interfaces.

```doof check
class Circle {
  kind: "circle"
  radius: double
}

class Rect {
  kind: "rect"
  width, height: double
}

type Shape = Circle | Rect

result := Shape.fromSerialValue({ kind: "circle", radius: 5.0 })
println(result.isSuccess())  // true
```

### Alias Requirements

- `.fromSerialValue()` is available only on named type aliases, not on bare union expressions.
- The alias must resolve to a union of classes.
- All member classes must be JSON-serializable.
- All member classes must share a literal string discriminator field with distinct values, the same as interface deserialization.

If these requirements are not met, using `.fromSerialValue()` on the alias is a compile-time error.

## Nested Serialization

Serialization and deserialization are fully recursive:

```doof check
class Point { x, y: float }

class Line {
  start, end: Point
}

line := Line {
  start: Point { x: 0.0, y: 0.0 },
  end: Point { x: 1.0, y: 1.0 }
}

json := line.toSerialObject()
restored := Line.fromSerialValue(json)
println(restored.isSuccess())  // true
```

## Arrays and Tuples

```doof check
import { formatJsonValue } from "std/json"

class Point { x, y: float }

class Polygon {
  vertices: Point[]
}

poly := Polygon {
  vertices: [Point { x: 0.0, y: 0.0 }, Point { x: 1.0, y: 0.0 }, Point { x: 0.0, y: 1.0 }]
}

println(formatJsonValue(poly.toSerialObject()))
// {"vertices":[{"x":0.0,"y":0.0},{"x":1.0,"y":0.0},{"x":0.0,"y":1.0}]}
```

Tuples serialize as JSON arrays:

```doof check
import { formatJsonValue } from "std/json"

class Pair {
  value: Tuple<string, int>
}

println(formatJsonValue(Pair { value: ("hello", 42) }.toSerialObject()))
// {"value":["hello",42]}
```

String-keyed maps serialize as JSON objects and recursively convert their values:

```doof check
class Scores {
  values: Map<string, int>
}

scores := Scores.fromSerialValue({ values: { alice: 10, bob: 12 } })
println(scores.isSuccess())  // true
```

## Enums

```doof check
import { formatJsonValue } from "std/json"

enum Color { Red, Green, Blue }

class Pixel {
  x, y: int
  color: Color
}

println(formatJsonValue(Pixel { x: 10, y: 20, color: Color.Green }.toSerialObject()))
// {"x":10,"y":20,"color":1}
```

Enum JSON is always its backing value, never its declared name:

```doof check
import { formatJsonValue } from "std/json"

enum Status { Pending, Ready = 7, Done }
enum WireStatus { Pending = "pending", Ready = "ready" }

println(formatJsonValue(Status.Pending.toSerialValue()))    // 0
println(formatJsonValue(Status.Ready.toSerialValue()))      // 7
println(formatJsonValue(WireStatus.Ready.toSerialValue()))  // "ready"

ready := Status.fromSerialValue(7)                // Success(Status.Ready)
wireReady := WireStatus.fromSerialValue("ready")  // Success(WireStatus.Ready)
```

The scalar JSON type must match the enum backing kind exactly. Lenient decoding
does not coerce enum strings to integers or enum integers to strings. Unknown
values report the containing field/index/map path, enum type, received value,
and the valid backing values. This rule applies identically to direct enum
decoding, nullable fields, arrays, tuples, string-keyed maps, and generic
`T.fromSerialValue(...)` calls where `T: Serializable`.

## Reserved Method Names

`toSerialObject` and `fromSerialValue` are reserved intrinsic method names. User-defined methods with these names on classes produce a compile-time error:

```doof reject
class Foo {
  x: int

  toSerialObject(): SerialObject {  // ❌ reserved method name
    return { "x": 1 }
  }
}
```
