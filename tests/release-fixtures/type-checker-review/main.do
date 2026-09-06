import { Assert } from "std/assert"

function add<T: float | double>(a: T, b: T): T => a + b
function divide<T: float | double>(a: T, b: T): T => a / b
function negate<T: int | long>(a: T): T => -a
function invert<T: int | long>(a: T): T => ~a
function increase<T: float | double>(a: T): T {
  let value = a
  value += 1
  return value
}
function unsignedShift<T: int | long>(a: T): T => a >>> 1
function square<T: float | double>(a: T): T {
  let value = a
  value **= a
  return value
}
function shifted<T: int | long>(a: T, count: long): T => a << count
function integerPower<T: int | long>(a: T): double => a ** a
function equal<T: int | long, U: float | double>(a: T, b: U): bool => a == b
function load(): Result<int, string> => Success { value: 1 }
function loadArray(): Result<int[], string> => Success { value: [1, 2] }
function loadFailure(): Result<int, string> => Failure { error: "expected" }
function widened(): Result<long, string> {
  try let value: long = load()
  value += 2147483648L
  return Success { value: value }
}
function propagate(): Result<int, string | int> {
  try value := loadFailure()
  return Success { value: value }
}
function scoped(): int { with value := 7 { return value } }
function main(): none {
  Assert.equal(add(1.25f, 2.5f), 3.75f)
  Assert.equal(add(1.25, 2.5), 3.75)
  Assert.equal(divide(7.5f, 2.5f), 3.0f)
  Assert.equal(increase(4.0f), 5.0f)
  Assert.equal(negate(3), -3)
  Assert.equal(invert(0L), -1L)
  Assert.equal(unsignedShift(-1), 2147483647)
  Assert.equal(unsignedShift(-1L), 9223372036854775807L)
  Assert.equal(square(2.0f), 4.0f)
  Assert.equal(square(2.0), 4.0)
  Assert.equal(shifted(3, 2L), 12)
  Assert.equal(integerPower(3), 27.0)
  Assert.isTrue(equal(2, 2.0))
  Assert.equal(try! widened(), 2147483649L)
  error := catch {
    try readonly values: int[] = loadArray()
    Assert.equal(values.length, 2)
    try readonly value: long = load()
    Assert.equal(value + 2147483648L, 2147483649L)
    try propagate()
  }
  Assert.equal(try! (error as string), "expected")
  Assert.equal(scoped(), 7)
  println("type checker review native checks passed")
}
