// Every absent layer (an outer none, a Failure, a none success value) panics
// under '!', becomes none under '?', falls back under '??', and runs a
// declaration-else handler.
class Box { value: int }

function nested(kind: int): Result<Box | none, string> {
  if kind == 0 { return Failure("nested failure") }
  if kind == 1 { return Success(none) }
  return Success(Box { value: 9 })
}

function outer(kind: int): Result<Box, string> | none {
  if kind == 0 { return none }
  if kind == 1 { return Failure("outer failure") }
  return Success(Box { value: 11 })
}

function viaElse(kind: int): string {
  box := nested(kind) else error {
    return "else ${error ?? "none"}"
  }
  return "bound ${box.value}"
}

function viaOuterElse(kind: int): string {
  box := outer(kind) else error {
    return "else ${error ?? "none"}"
  }
  return "bound ${box.value}"
}

function panics(action: (): none): string => case catchPanic(action) {
  _: Success -> "no panic",
  failure: Failure -> failure.error,
}

function main(): none {
  assert(nested(0)? == none && nested(1)? == none && nested(2)?!.value == 9, "postfix ? on a nullable success value")
  assert(outer(0)? == none && outer(1)? == none && outer(2)?!.value == 11, "postfix ? on an outer none")
  assert((nested(1) ?? Box { value: 1 }).value == 1 && (outer(1) ?? Box { value: 2 }).value == 2, "?? falls back on every layer")
  assert(nested(2)!.value == 9 && outer(2)!.value == 11, "! reads the present value")
  assert(panics(() => { println(nested(0)!.value) }).contains("! failed: nested failure"), "! reports the Failure")
  assert(panics(() => { println(nested(1)!.value) }).contains("! failed: value is none"), "! reports a none success value")
  assert(panics(() => { println(outer(0)!.value) }).contains("! failed: value is none"), "! reports an outer none")
  maybeBox: Box | none := none
  assert(panics(() => { println(maybeBox!.value) }).contains("! failed: value is none"), "!. on a none class reference panics")
  assert(panics(() => { box := maybeBox!
 println(box.value) }).contains("! failed: value is none"), "! on a none class reference panics")
  assert((nested(1)?.value ?? -1) == -1 && (outer(1)?.value ?? -1) == -1 && (outer(2)?.value ?? -1) == 11, "?. on every layer")
  assert(viaElse(0) == "else nested failure" && viaElse(1) == "else none" && viaElse(2) == "bound 9", "declaration-else error")
  assert(viaOuterElse(0) == "else none" && viaOuterElse(1) == "else outer failure" && viaOuterElse(2) == "bound 11", "declaration-else outer error")
  let cached: Result<Box | none, string> = Success(none)
  cached ??= Success(Box { value: 42 })
  assert(cached!.value == 42, "??= assigns over a none success value")
}
