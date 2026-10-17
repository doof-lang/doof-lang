# Doof Error Handling Reference

## Overview

Doof has no exceptions.

- Use `Result<T, E>` for expected, recoverable failures.
- Use `panic(...)` for unrecoverable programmer errors.

## Result Types

```doof
Result<T, E>
```

`Success<T>` and `Failure<E>` are intrinsic arm types. `Result<T, E>` is exactly
the canonical union `Success<T> | Failure<E>`; explicitly spelling that union in
either arm order enables the same Result operations. Constructors infer
standalone arm types, while an expected Result context supplies contextual
payload typing. Normal union case patterns expose `.value` only on Success and
`.error` only on Failure.

`Success { value }` and `Failure { error }` use the in-scope payload binding,
with the same contextual assignability requirements as explicit properties.

`Success()` / `Success {}` construct `Success<none>`. `Failure()` /
`Failure {}` construct `Failure<none>`. Payloadless arms omit their payload
member, and failure capture is unavailable for `Failure<none>`.

Arms are intrinsic structs. Without a Result context, `Success(42)` has type
`Success<int>`; it converts to any compatible Result. `==` compares the payload
(`Success(5) == Success(5)`), Results compare arm and payload, and a Result
compares with an arm directly (`parse(text) == Success(3)`). The bare pattern
`s: Success` takes its payload type from the subject wherever the arm appears,
including `Success<int> | none`.

### Returning Results

```doof check
function parseBit(s: string): Result<int, string> {
    if s != "0" && s != "1" {
        return Failure { error: "Invalid bit" }
    }
    parsed := if s == "1" then 1 else 0
    return Success { value: parsed }
}
```

### Handling with `case`

```doof check body
result: Result<int, string> := Success(42)
case result {
    s: Success -> println(s.value),
    f: Failure -> println(f.error)
}
```

Direct field access such as `result.value` or `result.error` is rejected because
the `Result` must be unwrapped or matched first.

### Must-Use Rule

Result values cannot be silently discarded. Ignoring a `Result` is a compile error.

## Propagation and Unwrapping

### `try` Statement

Statement-level `try` unwraps the success payload or propagates the failure from the enclosing function. It only works inside functions that themselves return `Result<..., ...>`.

The native entry-script scope is the exception: because top-level execution
has no return channel, statement-level `try` panics on failure.

`try` is a statement, not an expression: write `try x := load()`, not
`x := try load()`. Inside an expression use postfix `!` or `?`. A `try`
binding cannot take `else`; to handle the failure locally, drop `try` and use
declaration-`else` (`x := load() else { ... }`).

```doof check
class Config { name: string }
function readFile(path: string): Result<string, string> => Success("{\"name\": \"app\"}")
function parseJSON(text: string): Result<SerialValue, string> => Success({ name: "app" })
function validate(value: SerialValue): Result<Config, string> => Config.fromSerialValue(value)

function loadConfig(): Result<Config, string> {
    try content := readFile("config.json")
    try parsed := parseJSON(content)
    try config := validate(parsed)
    return Success { value: config }
}
```

Supported binding forms include declarations, typed declarations, destructuring, and assignment:

```doof check
class Person { name: string; age: int }
function load(): Result<int, string> => Success(1)
function loadPair(): Result<Tuple<int, int>, string> => Success((1, 2))
function loadPerson(): Result<Person, string> => Success(Person { name: "Ada", age: 36 })

function bindings(): Result<none, string> {
    try x := load()
    try typed: int := load()
    try readonly frozen = load()
    try let counter = load()
    try (a, b) := loadPair()
    try { name, age } := loadPerson()
    try counter = load()
    return Success()
}
```

### Absence: `!`, `?`, `??`

`none`, a `Failure`, and a `none` success value are all **absent**. The `?`
forms collapse absence to `none`, the `!` forms panic on it, and `??` replaces
it. None of them propagates a `Failure`; use statement `try` for that.
`Result<T | none, E>` and `Result<T, E> | none` both read as `T` once present.

```doof check
class Config { name: string }
function loadConfig(): Result<Config, string> => Success(Config { name: "app" })
function saveState(): Result<none, string> => Success()
function loadFromDisk(): string => "cached"

defaultConfig := Config { name: "default" }

config := loadConfig()!            // Config; panics on Failure (or a none success)
maybe := loadConfig()?             // Config | none
fallback := loadConfig() ?? defaultConfig
saveState()!                       // Result<none, E>: panics on Failure

let cache: string | none = none
cache ??= loadFromDisk()           // assigns only when absent
```

`!` panics identify the source path and line; a `string` error payload is
included in the message. `x?` requires a success value (not `Result<none, E>`).
`??` is right-associative and lazy. The prefix `try!` / `try?` forms were
removed.

### Force and Optional Access

```doof check
class Address { city: string }
class User { name: string; email: string; address: Address | none = none }
function loadUser(): Result<User, string> => Success(User { name: "Ada", email: "ada@example.com" })

user: User | none := loadUser()?
items: int[] | none := [1, 2, 3]

user!.name                // (user!).name
loadUser()!.email         // panics if loadUser() fails
items![0]                 // (items!)[0]
user?.address?.city       // string | none
loadUser()?.name          // string | none: none when loadUser() fails
```

`?.` and `?[]` turn the receiver's absence into `none`. A member that itself
returns `Result<U, E2>` keeps its own Failure: `loadUser()?.profile()` is
`Result<Profile | none, E2>`; chain `?.`, or add `?`, `!`, or `??`, to collapse it.

## Declaration-`else`

Declaration-`else` provides an unwrap-or-bail pattern for nullable and `Result` values.

```doof check
class LoadError { message: string }
function loadConfig(): Result<string, LoadError> => Success("debug")
function saveState(): Result<none, string> => Success()

function describe(maybeName: string | none): string {
    config := loadConfig() else error { return "load failed: " + error.message }
    name := maybeName else { panic("missing name") }
    _ := saveState() else error { println("save failed: " + error) }
    return name + ": " + config
}
```

Rules:

- The `else` block must exit the current scope via `return`, `break`, `continue`, or `panic(...)` when the binding name is used after the block.
- `_ := result else ...` is a discard handler; it does not introduce a binding after the block, so its `else` block can continue.
- Every absent layer runs the block, so the binding is the present value:
  `Result<T, E> | none` and `Result<T | none, E>` both bind `T`.
- `else error { ... }` captures the Failure's error as `E`. When the subject can
  also be absent as `none`, `error` is `E | none` and `none` means no Failure.
- The success binding is not in scope inside the `else` block.
- It applies only to nullable and/or `Result` types; nullable-only subjects
  cannot capture an error.

```doof check
class Source { text: string }
class Diagnostic { message: string }
function report(diagnostic: Diagnostic): none { println(diagnostic.message) }

// none means "not found"
function loadSource(path: string): Result<Source | none, Diagnostic> => Success(none)

function compile(path: string): Source | none {
    source := loadSource(path) else diagnostic {
        if diagnostic != none { report(diagnostic!) }
        return none
    }
    return source
}
```

When you need to keep a none success value while handling Failure, use `case`.

## Result Statement-`else`

Use statement-`else` to acknowledge and handle a `Result` returned from a side-effecting expression without a full `case` statement.

```doof check
function saveState(): Result<none, string> => Success()

function main(): none {
    saveState() else error {
        println("save failed: " + error)
    }
}
```

Rules:

- It applies only to present `Result<T, E>` expressions.
- `else error { ... }` captures the error payload as `E`.
- The handler does not need to exit scope because no success-path binding must be satisfied.

## Checked Narrowing with `as`

`as` performs checked runtime narrowing or conversion.

```doof check body
x: int | string := "hello"
s := x as string

payload: SerialValue := { ok: true }
obj := payload as readonly Map<string, SerialValue>

numeric: int | string := 42
wide := numeric as long
```

Behavior:

- For plain values, `as` yields `Result<T, string>`.
- For `Result<V, F>` sources, it narrows the success channel and yields `Result<T, F | string>`.
- Supported sources include unions, nullable types, interfaces, exact numeric conversions, `SerialValue`, and `Result` values wrapping those forms.
- Numeric `as` is checked. It fails when the runtime value cannot be represented exactly in the target type.

Useful combinations:

```doof check
function narrow(x: int | string): Result<string, string> {
    try s := x as string
    forced := (x as string)!
    handled := x as string else { return Success("") }
    return Success(s + forced + handled)
}
```

## Catch Expressions

`catch` captures fallible work locally instead of propagating it.

```doof check body
a := (): Result<int, string> => Success(1)
b := (): Result<none, string> => Failure("b failed")
err := catch {
    try a()
    try b()
}
```

Without an annotation, captured errors must share an assignable type `E`;
the result is `E | none`. For unrelated errors, annotate the result with
an explicit union of the error types plus `none`.

Inside `catch`:

- statement-level `try` exits the `catch` block, not the outer function
- postfix `!` and `?` keep their usual behavior

## Panic

```doof check
function at(array: int[], index: int): int {
    if index < 0 || index >= array.length {
        panic("Index out of bounds: ${index}")
    }
    return array[index]
}
```

Use panic for impossible states, assertion failures, or other programmer bugs.
`panic(...)` returns `never`, so direct calls and user-defined wrappers are
recognized as terminating paths and may appear in value-producing expressions.

### `catchPanic`

`catchPanic<T>(f: () => T): Result<T, string>` runs a parameterless callback and returns a success Result when it completes normally. If the callback panics, it returns a failure Result with the panic message as the string error payload.

`catchPanic(=> panic("stopped"))` infers `Result<never, string>`: the callback
cannot return a success value, and a caught panic provides the failure payload.

Use it only as a controlled escape hatch at process or host boundaries. It is not a general exception system, and expected failures should stay as `Result<T, E>`.

## When to Use What

| Mechanism | Use For |
| --- | --- |
| `Result` + `case` | detailed error handling and branching |
| statement-level `try` | sequential propagation in `Result`-returning functions |
| postfix `!` | required value or crash |
| postfix `?` | convert absence to `none` when details do not matter |
| declaration-`else` | unwrap-or-bail control flow |
| `??` | specific fallback value |
| `catch` | local error capture without propagation |
| `catchPanic` | controlled boundary recovery from panics |
| `panic` | programmer errors |

## Resource Cleanup

There is no `finally` or `defer`. Cleanup relies on deterministic destructors and reference counting.

All typed `try` declaration forms validate and store the annotated success type.
`try readonly` deep-freezes the success binding. A `none` success payload is
allowed only in bare `try expr`. Propagated errors must fit the enclosing
function’s error type; catches and native-script handlers do not cross nested
function, lambda, or value-producing-block boundaries.

A statement-level `try` on `Result<never, E>` cannot continue normally: its
failure propagates to the enclosing function or catch block, and its success
payload is uninhabited. This applies to both bare and binding forms.
