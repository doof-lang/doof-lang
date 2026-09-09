function stop(): never => panic("named")

function main(): none {
  inferred := catchPanic(=> panic("inferred"))
  assert(inferred.isFailure(), "inferred never callback")
  case inferred {
    failure: Failure -> { assert(failure.error == "inferred", "panic message") }
    _ -> { panic("unexpected success") }
  }
  block := catchPanic((): never => { panic("block") })
  assert(block.isFailure(), "block never callback")
  returned := catchPanic((): never => { return panic("returned") })
  assert(returned.isFailure(), "explicit never return")
  named := catchPanic(stop)
  assert(named.isFailure(), "named never callback")
  let count = 0
  captured := catchPanic((): never => { count += 1
    return panic("captured") })
  assert(captured.isFailure() && count == 1, "callback runs once")
  unit := catchPanic((): none => {})
  assert(unit.isSuccess(), "unit success")
  value := catchPanic(=> 42)
  assert(value.unwrapOr(0) == 42, "value success")
}
