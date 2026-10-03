# Control Flow

## If/Else Statements

### Basic Forms

```doof
if condition {
    doSomething()
}

if temperature > 30 {
    println("Hot")
} else {
    println("Not hot")
}

if score >= 90 {
    println("A")
} else if score >= 80 {
    println("B")
} else if score >= 70 {
    println("C")
} else {
    println("F")
}
```

### If as Expression

`if` can be used as an expression when all branches return a value:

```doof
grade := if score >= 90 then "A" 
         else if score >= 80 then "B"
         else if score >= 70 then "C"
         else "F"

abs := if x >= 0 then x else -x

println(if isLoggedIn then "Welcome back!" else "Please log in")
```

All branches must be present and return compatible types. The `then` keyword is required for expression form to distinguish it from statement form.
Branches of type `never` do not contribute a value type. If every branch is
`never`, the complete expression is also `never`.

### Block Requirement

Blocks are required for statement forms:

```doof
if x > 0 {
    println("positive")
} else {
    println("non-positive")
}
```

### No Implicit `none` Narrowing in If

```doof
value: int | none := getValue()

if value != none {
    println(value!)  // explicit assertion still required
}

if value == none {
    return
}

println(value!)
```

`none` checks are still useful for control flow, but they do not change the
static type of the checked value. For explicit guard-style narrowing, prefer
declaration-`else`, `case`, `as`, or `!`.

---

## Yielding Blocks

Some expression-like contexts use a block that produces a value by explicitly `yield`ing it.

### Case-Expression Arms

Case-expression arms may use block bodies instead of a single expression:

```doof
result := case n {
    0 -> {
        yield "zero"
    }
    _ -> {
        if n < 0 {
            yield "negative"
        }
        yield "positive"
    }
}
```

### `<-` Value-Yield Blocks

Local `let`, local `readonly`, and statement-only local reassignment can use `<-` followed by a block:

```doof
let x <- {
    if ready {
        yield 10
    }
    yield 5
}

x <- {
    yield x + 1
}
```

### Rules

- Every reachable path in the block must `yield` a value.
- `yield` is only valid inside these value-producing blocks.
- The block cannot affect outer control flow. In particular, `return` and `try` are rejected.
- `:=` does not accept `<-` block initializers.
- A block whose reachable paths all evaluate terminating `never` expressions
  satisfies the non-completion requirement without producing a `yield` value.

For statement-level completion analysis, an `if` with a final `else` is
exhaustive. A `case` is exhaustive when it has a wildcard, covers both Result
arms, covers every enum variant, or covers every member of a nominal union.
When every exhaustive branch returns, yields, loops forever, or evaluates a
`never` expression, control cannot continue after the statement.

---

## While Loops

```doof
let count = 0
while count < 10 {
    println(count)
    count += 1
}

// Infinite loop with break
let i = 0
while true {
    if i >= 10 {
        break
    }
    println(i)
    i += 1
}
```

---

## For Loops

### Traditional For Loop

```doof
for let i = 0; i < 10; i += 1 {
    println(i)
}

// Multiple variables
for let i = 0, j = 10; i < j; i += 1, j -= 1 {
    println("${i}, ${j}")
}

// Reverse iteration
for let i = 9; i >= 0; i -= 1 {
    println(i)
}
```

The initializer is either one `let` followed by comma-separated declarators (`let i = 0, j: long = 10`) or comma-separated expressions (`i = 0, j = 10`). The update clause also takes comma-separated expressions. Each declarator may have its own type annotation.

Variables declared in the initializer are mutable and are scoped to the loop: they are visible in the condition, the update clause and the body, but not in a `then` block or after the loop. A later loop in the same block may reuse the same names.

### For-Of Loop

Iterates over the values of any iterable. Loop variables are **immutable** bindings (no keyword needed):

```doof
names := ["Alice", "Bob", "Charlie"]

for name of names {
    println("Hello, ${name}!")
    // name = "other"  // ❌ Error: cannot reassign
}
```

Use `_` to iterate for side effects or to discard positions from a destructured
element. Discards introduce no loop binding and may be repeated:

```doof
for _ of lines { count += 1 }
for _, value of entries { println(value) }
for _, _ of pairs { tick() }
```

Current iterable forms are arrays, maps, sets, finite `Range` values, and
`Stream<T>` values. A stream yields one element at a time by calling `next()`
until it returns `false`, then reading the current element with `value()`.
The iterable expression is evaluated exactly once, and a collection or stream
temporary returned by that expression remains alive until the loop completes.

```doof
class Counter implements Stream<int> {
    let current: int
    end: int
    let currentValue: int = 0

    next(): bool {
        if this.current < this.end {
            this.currentValue = this.current
            this.current = this.current + 1
            return true
        }
        return false
    }

    value(): int => this.currentValue
}

for value of Counter(0, 3) {
    println(value)
}
```

### For-Of with Maps

```doof
scores: Map<string, int> := { "Alice": 95, "Bob": 87 }

// Destructured entries (MapEntry has key, value fields)
for key, value of scores {
    println("${key} scored ${value}")
}

// Keys or values only
for name of scores.keys() {
    println(name)
}
for score of scores.values() {
    println(score)
}
```

Map iteration follows insertion order. Updating an existing key keeps its current position; deleting and reinserting a key moves it to the end.

### For-Of with Sets

```doof
unique: Set<int> := [1, 2, 3]
for n of unique {
    println(n)
}

```

Set iteration follows first-insertion order. Re-adding an existing value keeps its current position; deleting and adding it again moves it to the end.

---

## Range-Based For Loops

`a..b` and `a..<b` create finite `Range` values. A range can be stored in a
binding, passed to a function, or used directly in `for of`. Range iteration
yields `int`. Ranges only iterate upward; a range whose lower bound is greater
than its upper bound is empty.

### Inclusive Range (`..`)

```doof
for i of 1..5 {
    println(i)  // 1, 2, 3, 4, 5
}

values: Range := 1..5
for value of values {
    println(value)
}
```

### Exclusive Range (`..<`)

```doof
for i of 0..<5 {
    println(i)  // 0, 1, 2, 3, 4
}

// Common pattern for array indices
items := ["a", "b", "c", "d"]
for i of 0..<items.length {
    println("${i}: ${items[i]}")
}
```

Open-ended ranges are not iterable `Range` values; they are only valid in
`case` range patterns.

### Range Accessors

```doof
inclusive := 1..9
exclusive := 1..<10

inclusive.lowerBound // 1
inclusive.upperBound // 10

exclusive.lowerBound // 1
exclusive.upperBound // 10
```

The `upperBound` accessor is always exclusive. For `1..9`, the upper bound is
adjusted to `10`; for `1..<10`, it is already `10`.

### Practical Range Example

```doof
items := loadItems()
indices := 0..<items.length
println("last valid index is ${indices.upperBound - 1}")

for i of indices {
    println("${i}: ${items[i]}")
}
```

---

## Break and Continue

### Basic

```doof
for i of 0..<100 {
    if i == 10 {
        break     // Exits innermost loop
    }
    println(i)
}

for i of 0..<10 {
    if i % 2 == 0 {
        continue  // Skips to next iteration
    }
    println(i)
}
```

### Labeled Break and Continue

```doof
outer: for y of 0..<height {
    for x of 0..<width {
        if grid[y][x] == target {
            println("Found at (${x}, ${y})")
            break outer  // Exits both loops
        }
    }
}

outer: for row of rows {
    for cell of row {
        if cell.isEmpty() {
            continue outer  // Skip to next row
        }
        process(cell)
    }
    markRowComplete(row)
}
```

---

## Loop Then Clause

The `then` clause executes when a loop completes normally, meaning control
leaves the loop without `break` or another non-local exit such as `return`:

```doof
for item of items {
    if item == target {
        println("Found!")
        break
    }
} then {
    println("Not found")
}
```

This applies even when the loop body ran; natural completion still counts:

```doof
while hasMoreData() {
    let data = readData()
    if data.isCorrupt() {
        println("Corrupt data found")
        break
    }
    process(data)
} then {
    println("All data processed successfully")
}
```

Traditional `for` loops support the same follow-up clause:

```doof
for let i = 0; i < 3; i += 1 {
    println(i)
} then {
    println("loop completed")
}
```

---

## Early Return

```doof
function findUser(id: int): User | none {
    if id < 0 {
        return none
    }

    for user of users {
        if user.id == id {
            return user
        }
    }

    return none
}
```

Return exits the entire function, not just the current block.

---

## Best Practices

### Prefer For-Of Over Traditional For

```doof
// ✅ Preferred
for item of items {
    process(item)
}

// ❌ Avoid when index not needed
for let i = 0; i < items.length; i += 1 {
    process(items[i])
}
```

### Use Ranges for Numeric Iteration

```doof
// ✅ Clear and concise
for i of 0..<10 {
    println(i)
}

// ❌ More verbose
for let i = 0; i < 10; i += 1 {
    println(i)
}
```

### Avoid Deep Nesting with Early Returns

```doof
// ❌ Deep nesting
function process(data: Data | none): Result | none {
    if data != none {
        if data.isValid() {
            if data.hasPermission() {
                return compute(data)
            }
        }
    }
    return none
}

// ✅ Early returns flatten the code
function process(data: Data | none): Result | none {
    if data == none {
        return none
    }
    if !data.isValid() {
        return none
    }
    if !data.hasPermission() {
        return none
    }
    return compute(data)
}
```

---

## Summary

| Statement | Purpose |
|-----------|---------|
| `if`/`else` | Conditional execution (also usable as expression) |
| `while` | Loop while condition is true |
| `for init; cond; update` | Traditional counted loop |
| `for x of collection` | Iterate over values |
| `for i of a..b` | Iterate over inclusive range |
| `for i of a..<b` | Iterate over exclusive range |
| `break` / `break label` | Exit innermost or labeled loop |
| `continue` / `continue label` | Skip to next iteration |
| `loop ... then` | Execute then when loop completes without break |
| `return` | Exit function with value |
