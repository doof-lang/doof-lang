import { Assert } from "std/assert"

function load(): Result<int, string> => Success { value: 7 }

function widened(): Result<long, string> {
  try let value: long = load()
  return Success { value }
}

function failed(error: string): Result<int, string> => Failure { error }

function promoted(value: int | string): Result<int | string | bool, string> => Success { value }

function generic<T>(value: T): Result<T, string> => Success { value }

function captured(): (): Result<int, string> {
  let value = 3
  result := (): Result<int, string> => Success { value }
  value = 11
  return result
}

function main(): none {
  Assert.equal(widened()!, 7)
  error := catch { try failed("bad") }
  Assert.equal(error!, "bad")
  value := promoted("kept")!
  Assert.equal((value as string)!, "kept")
  Assert.equal(generic(19)!, 19)
  read := captured()
  Assert.equal(read()!, 11)
}
