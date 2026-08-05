import { Assert } from "std/assert"

function assertFailure<T, E>(result: Result<T, E>, message: string): none {
  case result {
    _: Failure -> { return }
    _: Success -> { Assert.fail(message) }
  }
}

function unwrapByte(result: Result<byte, string>): byte => result!
function unwrapInt(result: Result<int, string>): int => result!
function unwrapLong(result: Result<long, string>): long => result!
function unwrapFloat(result: Result<float, string>): float => result!
function unwrapDouble(result: Result<double, string>): double => result!
function unwrapFallibleLong(result: Result<long, bool | string>): long => result!

function takeLong(value: long): long => value

function returnLong(value: int): long => value

export function testCheckedNumericConversionMatrix(): none {
  b: byte := 7
  i: int := 7
  l: long := 7L
  f: float := 7.0f
  d: double := 7.0

  Assert.equal(unwrapByte(b as byte), byte(7))
  Assert.equal(unwrapInt(b as int), 7)
  Assert.equal(unwrapLong(b as long), 7L)
  Assert.equal(unwrapFloat(b as float), 7.0f)
  Assert.equal(unwrapDouble(b as double), 7.0)

  Assert.equal(unwrapByte(i as byte), byte(7))
  Assert.equal(unwrapInt(i as int), 7)
  Assert.equal(unwrapLong(i as long), 7L)
  Assert.equal(unwrapFloat(i as float), 7.0f)
  Assert.equal(unwrapDouble(i as double), 7.0)

  Assert.equal(unwrapByte(l as byte), byte(7))
  Assert.equal(unwrapInt(l as int), 7)
  Assert.equal(unwrapLong(l as long), 7L)
  Assert.equal(unwrapFloat(l as float), 7.0f)
  Assert.equal(unwrapDouble(l as double), 7.0)

  Assert.equal(unwrapByte(f as byte), byte(7))
  Assert.equal(unwrapInt(f as int), 7)
  Assert.equal(unwrapLong(f as long), 7L)
  Assert.equal(unwrapFloat(f as float), 7.0f)
  Assert.equal(unwrapDouble(f as double), 7.0)

  Assert.equal(unwrapByte(d as byte), byte(7))
  Assert.equal(unwrapInt(d as int), 7)
  Assert.equal(unwrapLong(d as long), 7L)
  Assert.equal(unwrapFloat(d as float), 7.0f)
  Assert.equal(unwrapDouble(d as double), 7.0)
}

export function testCheckedNumericConversionRejectsLossyValues(): none {
  assertFailure(((-1) as byte), "negative int must not narrow to byte")
  assertFailure((256 as byte), "out-of-range int must not narrow to byte")
  assertFailure((2147483648L as int), "out-of-range long must not narrow to int")
  assertFailure((7.5 as int), "fractional double must not narrow to int")
  assertFailure((16777217 as float), "inexact int must not narrow to float")
  assertFailure((9007199254740993L as double), "inexact long must not narrow to double")
}

export function testCheckedNumericConversionThroughNullable(): none {
  present: int | none := 7
  absent: int | none := none

  Assert.equal(unwrapLong(present as long), 7L)
  assertFailure((absent as long), "none must not narrow to a number")
}

export function testCheckedNumericConversionThroughMixedUnion(): none {
  mixedNumber: int | string := 7
  mixedText: int | string := "seven"

  Assert.equal(unwrapLong(mixedNumber as long), 7L)
  assertFailure((mixedText as long), "a non-numeric union arm must not narrow to a number")
}

export function testCheckedNumericConversionThroughResult(): none {
  successful: Result<int, bool> := Success(7)
  failed: Result<int, bool> := Failure(false)

  Assert.equal(unwrapFallibleLong(successful as long), 7L)
  assertFailure((failed as long), "an existing Result failure must pass through")
}

export function testImplicitNumericWideningInTypedContexts(): none {
  i: int := 7
  l: long := i
  d: double := i
  f: float := 7.0f
  fd: double := f

  widenedUnion: long | string := i

  Assert.equal(i, 7)
  Assert.equal(l, 7L)
  Assert.equal(d, 7.0)
  Assert.equal(fd, 7.0)
  Assert.equal(takeLong(i), 7L)
  Assert.equal(returnLong(i), 7L)
  Assert.equal(unwrapLong(widenedUnion as long), 7L)
}
