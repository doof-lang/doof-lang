function fail(): Result<never, string> => Failure { error: "bad" }
function propagate(): Result<int, string> { try fail() }
function bind(): Result<int, string> { try x: int := fail() }
function forward<T>(value: Result<never, string>): Result<T, string> { try value }
function nested(): Result<Result<never, string>, never> => Success { value: fail() }
function use(x: int): none { panic("argument should not arrive") }
function infallible(): Result<int, never> => Success { value: 42 }
function main(): none {
  assert(propagate().isFailure(), "bare propagation")
  assert(bind().isFailure(), "binding propagation")
  assert(forward<int>(fail()).isFailure(), "generic propagation")
  assert("${nested()}" == "Success(Failure(bad))", "nested formatting")
  caught := catch { try fail() }
  assert(caught == "bad", "catch remains reachable")
  assert("${fail()}" == "Failure(bad)", "failure formatting")
  assert("${infallible()}" == "Success(42)", "success formatting")
  assert((fail() ?? 42) == 42, "fallback")
  optional := try? fail()
  assert(optional == none, "optional")
  let calls = 0
  local := catchPanic((): none => { calls += 1
    x: int := panic("local") })
  assert(local.isFailure() && calls == 1, "local panic runs once")
  argument := catchPanic((): none => { use(panic("argument")) })
  assert(argument.isFailure(), "argument panic")
  payload := catchPanic((): none => { x: Result<never, string> := Success { value: panic("payload") } })
  assert(payload.isFailure(), "payload panic")
}
