# Doof JSON Serialization and Metadata Reference

## JSON Serialization

Classes and structs with all-serializable fields and no dedicated `constructor` method automatically get `.toSerialObject()` and `.fromSerialValue(json, lenient = false)`. Code is generated **on-demand** — only when each method is actually required. Generation is transitive and direction-specific: encoding generates nested encoders, while decoding generates nested decoders, without generating the unused opposite direction.

### `.toSerialObject()` — Instance Method

Returns a `SerialObject` representation. `SerialObject` is the intrinsic alias for `Map<string, SerialValue>`, so it is still accepted anywhere a `SerialValue` is expected.

```doof
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
| `int`, `long` | number |
| `float`, `double` | number |
| `string`, `char` | string |
| `bool` | boolean |
| `none` | JSON `null` |
| Class or struct instances | object (recursive) |
| `T[]` | array |
| `Tuple<T1, T2>` | array |
| Enums (opaque) | string (member name) |
| Enums (string) | string (value) |
| Enums (int) | number (value) |
| `T | none` | value or JSON `null` |

**Not serializable:** function types, `weak` references, `Actor<T>`,
`Promise<T>`, `Result<T,E>`, and classes or structs with a dedicated static
`constructor(...): Self`.

### `.fromSerialValue()` — Static Method

```doof
result := Point.fromSerialValue({ x: 1.5, y: 2.5 })  // Result<Point, string>
lenient := Point.fromSerialValue({ x: 1, y: none }, true)
```

Generic helpers can deserialize through a type parameter when it is explicitly
constrained with the intrinsic `Serializable` constraint:

```doof
function decode<T: Serializable>(json: SerialValue): Result<T, string> {
    return T.fromSerialValue(json)
}

payload: SerialValue := { name: "Ada" }
user := decode<User>{ json: payload }
```

`Serializable` is constraint-only, not a normal value type. Concrete
instantiations must use JSON-serializable classes or structs.

Rules:
- Fields without defaults are **required**
- Fields with defaults are **optional** (use default if absent)
- Literal-valued fields are auto-filled; if present in JSON, value must match
- Extra JSON fields are silently ignored
- Type mismatches produce `Failure`
- Non-object SerialValue input produces `Failure`

When `lenient` is `true`:
- Required `string` fields accept JSON `null` (represented by source `none`) as `""`
- `string` fields accept booleans and numbers via stringification
- `bool` fields accept numbers and `"true"` / `"false"` / `"1"` / `"0"`
- Numeric fields accept booleans as `1` / `0`

### Interface Deserialization

Requires a shared literal-valued discriminator field with distinct string values across all implementing classes:

```doof
interface Shape { area(): float }

class Circle implements Shape {
    kind: "circle"
    radius: float
    function area(): float => 3.14159 * radius * radius
}

class Rect implements Shape {
    kind: "rect"
    width, height: float
    function area(): float => width * height
}

Shape.fromSerialValue({ kind: "circle", radius: 5.0 })  // Result<Shape, string>
Shape.fromSerialValue({ kind: "circle", radius: 5.0 }, true)
```

Compile error if implementing classes lack a shared literal-valued discriminator.

### Reserved Names

`toSerialObject` and `fromSerialValue` are reserved — user-defined methods with these names produce a compile error.

## Description Metadata

Optional description strings on declarations (pure metadata, no runtime effect):

```doof
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

```doof
meta := Calculator.metadata

meta.name               // "Calculator"
meta.description        // "A simple calculator."
meta.methods            // MethodReflection[]
meta.methods[0].name            // "add"
meta.methods[0].description     // "Adds two numbers."
meta.methods[0].inputSchema     // SerialValue JSON Schema Draft 7 object
meta.methods[0].outputSchema    // SerialValue JSON Schema Draft 7 object
meta.methods[0].invoke(instance, { a: 1, b: 2 })  // Result<SerialValue, SerialValue>
```

Generic helpers can access metadata on a type parameter with the compiler-known
`Reflectable` constraint:

```doof
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
| `enum E` | `{ "enum": ["A", "B", ...] }` |
| Class or struct type | `{ "$ref": "#/$defs/TypeName" }` |
