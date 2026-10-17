# Doof JSON Serialization and Metadata Reference

## JSON Serialization

Classes and structs with all-serializable fields and no dedicated `constructor` method automatically get `.toSerialObject()` and `.fromSerialValue(json, lenient = false)`. Code is generated **on-demand** — only when each method is actually required. Generation is transitive and direction-specific: encoding generates nested encoders, while decoding generates nested decoders, without generating the unused opposite direction.

### `.toSerialObject()` — Instance Method

Returns a `SerialObject` representation. `SerialObject` is the intrinsic alias for `readonly Map<string, SerialValue>`, so it is still accepted anywhere a `SerialValue` is expected.

```doof check
import { formatJsonValue } from "std/json"

class User {
    name: string
    age: int
    private email: string
}

println(formatJsonValue(User("Alice", 30, "a@b.com").toSerialObject()))
// {"name":"Alice","age":30,"email":"alice@example.com"}
```

Rules:
- All fields serialized, including `private`, `readonly`, and literal-valued fields
- Serialization is deep / recursive
- Field order matches declaration order

### Serializable Types

| Doof Type | JSON |
|-----------|------|
| `byte`, `int`, `long` | number (whole and in range when decoding) |
| `float`, `double` | number |
| `string`, `char` | string |
| `bool` | boolean |
| `none` | JSON `null` |
| Class or struct instances | object (recursive) |
| Non-generic interfaces | the implementation's object (see Interface JSON) |
| `T[]` | array |
| `Tuple<T1, T2>` | array |
| Enums (implicit or int-backed) | integer backing value |
| Enums (string-backed) | string backing value |
| `T | none` | value or JSON `null` |

**Not serializable:** function types, `weak` references, `Actor<T>`,
`Promise<T>`, `Result<T,E>`, and classes or structs with a dedicated static
`constructor(...): Self`.

### `.fromSerialValue()` — Static Method

```doof check
struct Point { x: double; y: double = 0.0 }

function main(): none {
    result := Point.fromSerialValue({ x: 1.5, y: 2.5 })  // Result<Point, string>
    lenient := Point.fromSerialValue({ x: 1, y: none }, true)
}
```

Generic helpers can deserialize through a type parameter when it is explicitly
constrained with the intrinsic `Serializable` constraint:

```doof check
class User { name: string }

function decode<T: Serializable>(json: SerialValue): Result<T, string> {
    return T.fromSerialValue(json)
}

function main(): none {
    payload: SerialValue := { name: "Ada" }
    user := decode<User>{ json: payload }
}
```

`Serializable` is constraint-only, not a normal value type. Concrete
instantiations may use eligible JSON-serializable classes, structs, or enums.

A parameter bounded by an ordinary interface (`T: Named`) also gets
`T.fromSerialValue(...)` and `value.toSerialObject()` without declaring them.
Each concrete argument is checked at instantiation, and an ineligible one is
reported at the member access. Keep the receivers straight: `T.toSerialObject`
and `value.fromSerialValue(...)` are errors.

Enums also expose `.toSerialValue()` and static `.fromSerialValue(...)` directly.
Enum decoding requires the exact scalar kind even in lenient mode; lenient mode
does not coerce enum values. Unknown values report the enum, received backing
value, valid values, and any containing field/index/map path.

Rules:
- Fields without defaults are **required**
- Fields with defaults are **optional** (use default if absent)
- Literal-valued fields are auto-filled; if present in JSON, value must match
- Extra JSON fields are silently ignored
- Type mismatches produce `Failure`
- Integral fields accept whole numbers in range (`3.0` → `3`); `1.5` or an
  out-of-range number fails instead of truncating or wrapping
- Non-object SerialValue input produces `Failure`

When `lenient` is `true`:
- Required `string` fields accept JSON `null` (represented by source `none`) as `""`
- `string` fields accept booleans and numbers via stringification
- `bool` fields accept numbers and `"true"` / `"false"` / `"1"` / `"0"`
- Numeric fields accept booleans as `1` / `0`

### Interface JSON

An interface value encodes as its runtime implementation: `shape.toSerialObject()`
is available when every implementing class is serializable, and needs no
discriminator. Decoding requires a shared literal-valued discriminator field with
distinct string values across all implementing classes. Interface-typed fields,
array elements, map values, and nullable fields follow the same per-direction
rules, so a class with a `Shape[]` field encodes and decodes on demand, and
recursive interfaces such as tree nodes work. Generic interfaces are not JSON types.

```doof check
interface Shape { area(): double }

class Circle implements Shape {
    kind: "circle"
    radius: double
    area(): double => 3.14159 * radius * radius
}

class Rect implements Shape {
    kind: "rect"
    width, height: double
    area(): double => width * height
}

decoded := Shape.fromSerialValue({ kind: "circle", radius: 5.0 })  // Result<Shape, string>
lenient := Shape.fromSerialValue({ kind: "circle", radius: 5.0 }, true)
shape: Shape := Circle { radius: 2.0 }
shape.toSerialObject()  // {"kind":"circle","radius":2.0}
```

Compile error if implementing classes lack a shared literal-valued discriminator
(decoding) or if any implementing class is not serializable (encoding; the error
names the class).

A named alias of a class union uses the same rule: with `type Shape = Circle | Rect`,
`Shape.fromSerialValue(json)` returns `Result<Shape, string>`. Generic aliases and
unions containing non-class members are compile errors.

Union-typed fields (with optional `none`) encode the held member and decode by the JSON
value's kind: string (`string`, `char`, string enums), number (numerics, int enums),
boolean, array (arrays, tuples), or object (classes, interfaces, `Map<string, T>`).
Each kind may have one member, so `int | string` decodes but `int | double` or
`char | string` is a decode-time compile error naming the field (encoding still works).
Classes and interfaces may share the object kind through one discriminator shared by
every class they stand for (interfaces expand to their implementors). `SerialValue`
and structs cannot be union members.

### Reserved Names

`toSerialObject` and `fromSerialValue` are reserved — user-defined methods with these names produce a compile error.

## Description Metadata

Optional description strings on declarations (pure metadata, no runtime effect):

```doof check
class DevAssistant "AI assistant for development." {
    rootPath "Path to the project root.": string
    
    // Multi-name fields: each name gets its own description
    x "x-axis", y "y-axis", z "z-axis": float
    
    createProject "Creates a new project scaffold."(
        name "The name of the project.": string
    ): string => name
}
```

Supported on: `class`, fields, `function`, methods, parameters, `interface`, interface fields/methods, `enum`, enum variants, `type` alias, and `readonly`.

Not supported on: `let`, `:=`, imports/exports.

## Tool Metadata (`.metadata`)

Classes and structs with descriptions can expose structured metadata (generated on-demand):

```doof check
class Calculator "A simple calculator." {
    add "Adds two numbers."(a "First.": int, b "Second.": int): int => a + b
}

instance := Calculator {}
meta := Calculator.metadata

meta.name               // "Calculator"
meta.description        // "A simple calculator."
meta.methods            // MethodReflection[]
meta.methods[0].name            // "add"
meta.methods[0].description     // "Adds two numbers."
meta.methods[0].inputSchema     // SerialValue JSON Schema Draft 7 object
meta.methods[0].outputSchema    // SerialValue JSON Schema Draft 7 object
sum := meta.methods[0].invoke(instance, { a: 1, b: 2 })  // Result<SerialValue, SerialValue>
```

Generic helpers can access metadata on a type parameter with the compiler-known
`Reflectable` constraint:

```doof check
function toolName<T: Reflectable>(tool: T): string {
  return T.metadata.name
}
```

`Reflectable` is constraint-only; concrete arguments must be non-generic classes
or structs that are eligible for metadata and automatic JSON generation.

### JSON Schema Type Mappings

| Doof type | JSON Schema |
|-----------|-------------|
| `int`, `long` | `{ "type": "integer" }` |
| `float`, `double` | `{ "type": "number" }` |
| `string`, `char` | `{ "type": "string" }` |
| `bool` | `{ "type": "boolean" }` |
| `none` | `{ "type": "null" }` |
| `T[]` | `{ "type": "array", "items": { ... } }` |
| `(T, U)` | `{ "type": "array", "prefixItems": [...] }` |
| `T \| U` | `{ "anyOf": [...] }` |
| integer-backed `enum E` | `{ "type": "integer", "enum": [0, 1, ...] }` |
| string-backed `enum E` | `{ "type": "string", "enum": ["wire-a", "wire-b", ...] }` |
| Class or struct type | `{ "$ref": "#/$defs/TypeName" }` |
