function equal<T>(actual: T, expected: T): bool => actual == expected
function keep<T>(value: T): T => value

function main(): none {
  f := (x: int): int => x + 1
  copy := f
  other := (x: int): int => x + 1
  assert(f == copy && equal(f, copy), "callback copies share identity")
  assert(f != other && !equal(f, other), "separate callbacks have different identities")
  first: ((x: int): int) | none := f
  absent: ((x: int): int) | none := none
  assert(equal(absent, none), "optional callback absence through a generic")
  assert(!equal(first, none), "present callback differs from absence")
  assert(equal(first, copy), "optional callback retains identity")
  second: ((x: string): int) | none := (x: string): int => x.length
  third: ((x: int): string) | none := (x: int): string => string(x)
  assert(!equal(second, none) && !equal(third, none), "different generic signatures")
  assert(keep(second)!("hello") == 5, "string parameter signature retained")
  assert(keep(third)!(42) == "42", "string return signature retained")
  empty: ((x: string): int) | none := none
  assert(equal(empty, none), "second absent signature")
}
