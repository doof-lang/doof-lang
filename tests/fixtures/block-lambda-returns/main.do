function identity<T>(value: T): T => value
function main(): none {
  let count = 0
  caught := catchPanic(=> { count += 1
    return panic("captured") })
  assert(caught.isFailure() && count == 1, "inferred never callback runs once")
  case caught {
    failed: Failure -> { assert(failed.error == "captured", "panic payload") }
    _ -> { panic("unexpected success") }
  }
  direct := catchPanic(=> { panic("direct") })
  assert(direct.isFailure(), "never without explicit return")
  value := catchPanic(=> { return 42 })
  assert(value.unwrapOr(0) == 42, "generic int return")
  unit := catchPanic(=> {})
  assert(unit.isSuccess(), "empty block returns none")
  bare := => { return }
  bare()
  nullable := (present: bool) => { if present { return 42 }
    return none }
  assert(nullable(true)! == 42 && nullable(false) == none, "nullable return carriers")
  widened := (small: bool) => { if small { return 1 }
    return 2L }
  assert(widened(true) == 1L && widened(false) == 2L, "numeric widening")
  diverging := (fail: bool) => { if fail { return panic("branch") }
    return 42 }
  assert(diverging(false) == 42, "never does not widen the return type")
  failedBranch := catchPanic(=> diverging(true))
  assert(failedBranch.isFailure(), "explicit diverging return")
  outer := => { nested := => { return "nested" }
    assert(nested() == "nested", "nested return")
    return 7 }
  assert(outer() == 7, "nested return types stay separate")
  independent := identity((flag: bool) => { if flag { return 3 }
    return 4 })
  assert(independent(true) == 3 && independent(false) == 4, "generic callback value")
}
