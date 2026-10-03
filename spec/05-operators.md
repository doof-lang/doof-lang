# Operators

## Arithmetic Operators

Standard arithmetic operators with familiar precedence:

```doof
a := 10 + 5    // Addition: 15
b := 10 - 5    // Subtraction: 5
c := 10 * 5    // Multiplication: 50
d := 10.0 / 5.0  // Division: 2.0 (/ requires at least one float/double operand)
e := 10 \ 3    // Integer division: 3 (truncates toward zero)
f := 10 % 3    // Modulo: 1 (integer operands only)
g := 2 ** 3    // Exponentiation: 8
```

Exponentiation uses `double` when either operand is integral; two floating
operands use their common floating type. Shift results use the promoted left
operand type, independently of the shift-count type.

### Division Operators

Doof has two division operators:

- **`/`** — floating-point division. **Cannot** be applied to two integer operands (compile error). At least one operand must be `float` or `double`, or use a numeric cast.
- **`\`** — integer division. **Requires** both operands to be integer types (`int` or `long`). Truncates toward zero.

```doof
// Floating-point division (/ operator)
floatDiv := 7.0 / 2.0          // 3.5
mixed := float(7) / 2.0        // 3.5 (cast int to float)
precise := double(a) / double(b) // double division via casts

// Integer division (\ operator)
intDiv := 7 \ 2        // 3 (truncates toward zero)
negDiv := -7 \ 2       // -3
longDiv := 100L \ 3L   // 33L

// Compile errors:
7 / 2          // ❌ Error: "/" cannot be applied to two integer operands
7.0 \ 2.0      // ❌ Error: "\" requires integer operands
7.0 % 2.0      // ❌ Error: "%" requires integer operands
```

### Modulo Operator

The `%` operator requires both operands to be integer types (`int` or `long`):

```doof
remainder := 10 % 3    // 1
negMod := -7 % 3       // -1 (C++ truncated division semantics)
```

### Numeric Casts

Numeric types can be explicitly cast using function-call syntax:

```doof
x := 42
f := float(x)         // int → float
d := double(x)        // int → double
n := int(3.14)         // double → int (truncates: 3)
l := long(x)           // int → long

// Common pattern: dividing integers as floats
a := 7
b := 2
result := float(a) / float(b)  // 3.5
```

Numeric casts accept exactly one argument of a numeric type (`int`, `long`, `float`, `double`) and return the target type. Non-numeric arguments are a compile error.

### Unary Operators

```doof
x := 5
neg := -x     // Negation: -5
pos := +x     // Unary plus: 5
```

### No Increment/Decrement

Doof does **not** have `++` or `--` operators:

```doof
let x = 5
x++      // ❌ Error: no increment operator
x += 1   // ✅ Use compound assignment instead
```

**Rationale:** `++` and `--` have confusing prefix/postfix semantics and encourage imperative mutation. `x += 1` is equally concise and unambiguous.

---

## Comparison Operators

```doof
a == b     // Equality (reference for objects)
a != b     // Inequality
a < b      // Less than
a <= b     // Less than or equal
a > b      // Greater than
a >= b     // Greater than or equal
```

### Reference vs Structural Equality

```doof
class Point { x, y: int; }

p1 := Point { x: 1, y: 2 }
p2 := Point { x: 1, y: 2 }
p3 := p1

p1 == p2    // false  — reference equality (different objects)
p1 == p3   // true  — same reference
```

| Operator | Behaviour |
|----------|-----------|
| `==` on classes | Reference identity — same object in memory |
| `!=` on classes | Reference non-identity |
| `==` on function values | Callback identity — copies of the same callback compare equal |
| `!=` on function values | Different callback identities |
| `==` on structs | Equality of every instance field, in declaration order |
| `!=` on structs | Negation of field equality |
| `==` between a union and a member type | The member converts to the union; equal when both hold the same member with equal values |

Struct equality compares corresponding fields using their own `==` semantics.
Nested structs compare recursively; class and mutable collection fields retain
reference identity. Static fields do not participate, and two values of the same
empty struct compare equal. Equality short-circuits at the first unequal field.
This also applies when structs are passed to generic functions such as
`Assert.equal`. Distinct nominal struct types cannot be compared. The intrinsic
`Success<T>` and `Failure<E>` arms are structs and compare their payload field.

A union compares with a value of one of its member types, as in
`u: int | string; u == 1`. The member value converts to the union first, so the
comparison is true only when the union holds that member and the values are
equal under the member's own rules. Results and interfaces compare the same
way with their arms and implementing classes.

Creating a function value creates a callback identity. Assigning or passing it
preserves that identity and its captured state; separately created callbacks
compare unequal even when their code is identical. Optional function values
support equality with `none`, including through generic functions such as
`Assert.equal`. Equality does not invoke the callback.

---

## Logical Operators

```doof
a && b    // Logical AND
a || b    // Logical OR
!a        // Logical NOT
```

All logical operators require `bool` operands. Short-circuit evaluation applies:

```doof
false && expensiveCall()  // expensiveCall() never executed
true || expensiveCall()   // expensiveCall() never executed

if list.length > 0 && list[0] == target {
    // ...
}
```

---

## Absence Operators

`none` and a `Failure` are both **absent**. The `?` operators collapse absence
to `none`, the `!` operators panic on it, and `??` replaces it. None of them
propagates a `Failure`; use the `try` statement to return one (see
[Result Propagation](#result-propagation)).

A value can be absent at up to three layers, outermost first: an outer `none`
arm, one `Result`, and a `none` success value. Every operator below handles all
of them at once:

| Operand type | Present value | `x?` | `x!` |
|---|---|---|---|
| `T \| none` | `T` | `T \| none` | `T` |
| `Result<T, E>` | `T` | `T \| none` | `T` |
| `Result<T \| none, E>` | `T` | `T \| none` | `T` |
| `Result<T, E> \| none` | `T` | `T \| none` | `T` |

A `Result` inside a success value is a present value, not another layer.
`Result<none, E>` has no present value: `x!` is a statement that panics on
`Failure`, and `x?` is an error.

Applying any absence operator to a value that is neither nullable nor a
`Result` is a compile error.

### Postfix `?` — Convert to Optional

```doof
import { parseInt } from "std/parse"

value := parseInt("12")?          // int | none (none on Failure)
name := maybeName()?              // string | none (a no-op on a nullable)
profile := loadProfile()?         // Profile | none for Result<Profile | none, E>
```

### Postfix `!` — Panic When Absent

```doof
value := parseInt("12")!          // int (panics on Failure)
sum := parseInt("12")! + 2        // int
user := maybeUser()!              // User (panics on none)
saveConfig(config)!               // Result<none, E>: panics on Failure
```

The panic names the source path and line. A `Failure` with a `string` error
includes the error text.

### Optional Coalescing (`??`)

Provides a fallback when the left operand is absent:

```doof
name: string | none := none
displayName := name ?? "Anonymous"          // "Anonymous"

config := loadConfig() ?? defaultConfig     // Config (fallback on Failure)
data := readFile("cache.txt") ?? ""         // string
```

**Type:** `x ?? y` has the present type of `x`, joined with the type of `y`.

**Associativity:** Right-to-left, so chains compose:

```doof
config := loadFromCache() ?? loadFromDisk() ?? fetchFromNetwork() ?? defaultConfig
// Groups as: loadFromCache() ?? (loadFromDisk() ?? (fetchFromNetwork() ?? defaultConfig))
```

**Lazy evaluation:** The right operand is evaluated only when the left is
absent.

**Important:** `??` checks only for absence, not falsiness. `||` requires
`bool` operands.

### Optional Coalescing Assignment (`??=`)

Assigns only when the target is currently absent:

```doof
let cache: string | none = none
cache ??= loadFromDisk()  // Assigns result of loadFromDisk()
cache ??= loadFromDisk()  // No-op, cache already has value

let data: Result<string, Error> = readCache()
data ??= readFromDisk()     // Replaces data only if it is absent
data ??= fetchFromNetwork() // No-op if data is present
```

**Type requirement:** The right-hand side must be assignable to the target. For
a `Result<T, E>` target, the right-hand side can be a `Result<T, E>` or a plain
`T`, which is wrapped in `Success`.

**Lazy evaluation:** Like `??`, the right operand is only evaluated if the
assignment will occur.

### Optional Chaining (`?.`) and Indexing (`?[]`)

Access a member or element only when the receiver is present:

```doof
user: User | none := getUser()
city := user?.address?.city     // string | none
logger?.log("Hello")            // Only calls if logger is present

items: string[] | none := getItems()
first := items?[0]              // string | none

name := loadUser(id)?.name      // string | none: none when loadUser fails
```

`x?.m` is `(x?)?.m`. The receiver is evaluated once; when it is absent, field
reads and value-returning calls produce `none`, and calls returning `none` are
skipped. `?.` and `?[]` cannot be used as assignment targets.
A method named through `?.` without a call is an optional function value
(`user?.describe` is `((): string) | none`); see [Functions and Methods as
Values](04-functions-and-lambdas.md#functions-and-methods-as-values).

The receiver's absence becomes `none`. A member that itself returns a `Result`
keeps its own `Failure`, and the `none` joins its success value:

```doof
// findUser(): Result<User, LookupError>
// User.profile(): Result<Profile, ProfileError>
profile := findUser(id)?.profile()   // Result<Profile | none, ProfileError>
// findUser fails or yields none -> Success(none); profile() fails -> its Failure

bio := findUser(id)?.profile()?.bio  // string | none: every absence collapses
```

`Result<none, E>` receivers have no present value, so `?.` on them is an error.

### Force Access (`!.` and `![]`)

`x!.m` is `(x!).m` and `x![i]` is `(x!)[i]`: the receiver panics when absent,
then the access proceeds.

```doof
user: User | none := getUser()
name := user!.name                   // string (panics if user is none)

email := loadUser()!.getEmail()      // panics if loadUser fails
first := maybeItems()![0]            // panics if maybeItems() is absent
```

**When to use `!`:**

```doof
// ✅ When absence indicates a programming error
port := loadConfig()!.port

// ❌ For expected absence — use ?, ??, declaration-else, or case instead
value := tryLoadData()!.field  // Bad: failure might be expected
```

**Comparison:**

| Operator | When absent | Result |
|----------|-------------|--------|
| `x?`, `x?.m`, `x?[i]` | `none` | present value or `none` |
| `x!`, `x!.m`, `x![i]` | panics | present value |
| `x ?? y` | evaluates `y` | present value or `y` |

**Note:** Weak references read as `Result<T, WeakReferenceError>` (see
[Type System — Weak References](02-type-system.md)), so `?.` and `!.` treat an
expired reference as absent.

---
## Bitwise Operators

```doof
a & b     // Bitwise AND
a | b     // Bitwise OR
a ^ b     // Bitwise XOR
~a        // Bitwise NOT
a << 2    // Left shift
a >> 2    // Right shift (arithmetic)
a >>> 2   // Unsigned right shift
```

---

## Assignment Operators

### Compound Assignment

```doof
let x = 10
x += 5    // x = x + 5
x -= 3    // x = x - 3
x *= 2    // x = x * 2
x \= 4    // x = x \ 4 (integer division)
x %= 4    // x = x % 4

let y: double = 10.0
y /= 4    // y = y / 4
y **= 3   // y = y ** 3 (exponentiation produces double)

// Bitwise compound assignment
x &= 0b111
x |= 0b100
x ^= 0b010
x <<= 2
x >>= 1
```

---

## Range Operators

Finite range operators produce a built-in `Range` value:

```doof
1..5      // Inclusive range: 1, 2, 3, 4, 5
1..<5     // Exclusive upper bound: 1, 2, 3, 4
```

`Range` values can be stored, passed to functions, returned, and used anywhere an
ordinary expression is valid. Bounds must be `int`-compatible integer values.
Open-ended forms such as `10..` and `..<10` are valid only as `case` range
patterns.

---

## String Operators

```doof
greeting := "Hello, " + "World!"  // Concatenation

// Prefer string interpolation
name := "Alice"
msg := "Hello, ${name}!"
```

---

## Type Narrowing Operator (`as`)

The `as` operator performs checked runtime narrowing/conversion. For plain values it yields `Result<T, string>`. For `Result<V, F>` sources it narrows the success channel and yields `Result<T, F | string>`:

```doof
value: int | string := "hello"
r := value as string   // Result<string, string>

input: Result<int | string, bool> := Success("hello")
next := input as string  // Result<string, bool | string>

numeric: int | string := 42
wide := numeric as long  // Result<long, string>
```

### Supported Narrowing

| Source Type      | Target Type    | Runtime Check                          |
|-----------------|----------------|----------------------------------------|
| `T \| none`     | `T`            | `none` check                            |
| `U1 \| U2`      | `Ui`           | `std::holds_alternative<Ui>` variant check |
| Numeric primitive or numeric union member | Numeric primitive | Checked numeric conversion; succeeds only when the runtime value is exactly representable in the target type |
| `SerialValue`      | Exact JSON member (`string`, `int`, `long`, `float`, `double`, `bool`, `none`, `readonly SerialValue[]`, `readonly byte[]`, `readonly Map<string, SerialValue>`) | JSON carrier tag check |
| Interface       | Class          | `std::holds_alternative<Class>` variant check |
| `Result<V, F>`  | `T`            | If failure: pass through `F`; if success: narrow `V` to `T` |
| `T`             | `T`            | Identity — always succeeds            |

### Result Handling

Since `as` always returns a `Result`, use standard Result patterns:

Unlike `int(x)` / `long(x)` / `float(x)` / `double(x)`, which are direct casts, numeric `as` is checked. For example, `x as int` fails when a `long` is out of range or a floating-point value has a fractional component.

```doof
// With try (in Result-returning function):
try s := value as string

// With else-narrow:
s := value as string else { return defaultValue }

// Else blocks may also terminate with panic:
object := value as readonly Map<string, SerialValue> else { panic("Expected object") }

// With postfix ! (panic on failure):
s := (value as string)!

// Pattern match:
case value as string {
    ok: Success -> println(ok.value),
    err: Failure -> println(err.error)
}
```

### Precedence

`as` binds tighter than unary prefix operators (`!`, `-`) but looser than postfix operators (`.`, `()`, `[]`, `?`, `!`):

```doof
(value as string)!          // parentheses unwrap the narrowing Result
obj.method() as Foo         // (obj.method()) as Foo
maybeValue()! as string     // (maybeValue()!) as string
```

### Invalid Narrowing

The compiler rejects narrowing that has no runtime path to success:

```doof
x: int := 42
r := x as string    // ❌ Error: Cannot narrow "int" to "string"
```

---

## Result Propagation

The `try` statement unwraps a `Success` value or returns the `Failure` from the
enclosing function:

```doof
function loadConfig(): Result<Config, Error> {
    try content := readFile("config.json")   // Returns Failure early if error
    try parsed := parseJSON(content)
    try config := validate(parsed)
    return Success { value: config }
}
```

`try` can only be used inside functions returning `Result<T, E>`, and only as a
statement. Within an expression, use postfix `!` to panic or postfix `?` to
convert to `none` (see [Absence Operators](#absence-operators)). The prefix
`try!` and `try?` forms were removed; the compiler names their postfix
replacement.

See [09-error-handling.md](09-error-handling.md) for detailed semantics.

---

## Operator Precedence

From highest to lowest:

| Precedence | Operators | Associativity |
|------------|-----------|---------------|
| 1 | `()` `[]` `.` `?.` `!.` `?[]` postfix `?` postfix `!` | Left to right |
| 2 | `as` | Left to right |
| 3 | `!` `~` `-` (unary) `+` (unary) | Right to left |
| 4 | `**` | Right to left |
| 5 | `*` `/` `\` `%` | Left to right |
| 6 | `+` `-` | Left to right |
| 7 | `<<` `>>` `>>>` | Left to right |
| 8 | `<` `<=` `>` `>=` | Left to right |
| 9 | `==` `!=` | Left to right |
| 10 | `&` | Left to right |
| 11 | `^` | Left to right |
| 12 | `\|` | Left to right |
| 13 | `&&` | Left to right |
| 14 | `\|\|` | Left to right |
| 15 | `??` | Right to left |
| 16 | `??=` `:=` `=` `+=` `-=` etc. | Right to left |

**Note:** Postfix `?` and `!` bind as tightly as member access, so
`loadUser()!.email` reads the email of the unwrapped user and
`(value as string)!` needs parentheses to unwrap the narrowing result. A postfix
`?` or `!` must be on the same line as its operand.

**Best Practice:** Use parentheses for clarity when mixing operators.

---

## No Operator Overloading

Doof does **not** support user-defined operator overloading:

```doof
class Vector {
    x, y: float
    
    // ✅ Use methods instead
    add(other: Vector): Vector {
        return Vector { x: x + other.x, y: y + other.y }
    }
}

v3 := v1 + v2       // ❌ Error
v3 := v1.add(v2)    // ✅ OK
```

**Rationale:** Operator overloading can make code harder to reason about. Method calls are explicit about what operation occurs and avoid precedence/associativity surprises.
