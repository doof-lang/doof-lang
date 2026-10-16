class Receiver {
  let total: int = 0

  doubler(): (n: int): int => (n: int): int => n * 2

  start(): none {
    promise := async { yield [3, 4] }
    promise.onComplete((result) => {
      values := result!
      values.push(5)
      this.total = values[0] + values[1] + values[2]
    })
  }
}

function register<T>(promise: Promise<T>, callback: (result: Result<T, string>): none): none {
  promise.onComplete(callback)
}

// Script work and main work both finish before the root mailbox drains.
let scriptDelivered = false
scriptTask := async { yield none }
scriptTask.onComplete((result) => { result!; scriptDelivered = true })

function main(): int {
  receiver := Actor<Receiver>()
  receiver.start()
  retired := retire receiver
  assert(retired.total == 12, "retirement must drain reserved completions")

  promise := async { yield [1, 2] }
  alias := promise
  let called = false
  register<int[]>(promise, (result) => {
    values := result!
    values.push(3)
    assert(values.length == 3, "mutable result must transfer")
    called = true
    // New callbacks created by a completion still belong to the root domain.
    next := async { yield 4 }
    next.onComplete((result) => {
      assert(result! == 4 && called && scriptDelivered, "root delivery must drain")
      println("onComplete delivered")
    })
  })
  assert(!called, "registration must never invoke inline")
  assert(catchPanic(=> alias.get()).isFailure(), "get after registration must panic")
  assert(catchPanic(=> alias.onComplete((result) => { result! })).isFailure(), "second registration must panic")

  callback := (): int => 11
  posted := callback.post()
  posted.onComplete((result) => { assert(result! == 11, "posted callback promises support completion") })

  tried := callback.tryPost()!
  tried.onComplete((result) => { assert(result! == 11, "accepted tryPost delivers through the root mailbox") })
  doubling := Actor<Receiver>()
  double := doubling.doubler()
  assert(double.tryPost(4)!.get()! == 8, "actor tryPost runs on the owning actor")
  retire doubling
  case double.tryPost(1) {
    _: Success -> assert(false, "tryPost to a retired actor must be rejected"),
    f: Failure -> assert(f.error == "retired", "retired owner reports retired"),
  }

  consumed := async { yield 5 }
  pending := [consumed]
  assert(pending.takeFirstCompleted()! == 5, "array consumer result")
  assert(catchPanic(=> consumed.get()).isFailure(), "array extraction consumes aliases")
  return 7
}
