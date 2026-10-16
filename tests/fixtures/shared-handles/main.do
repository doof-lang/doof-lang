class Sink {
  let total: int = 0
  add(amount: int): none { this.total += amount }
  read(): int => this.total
}

class Envelope {
  readonly sink: Actor<Sink>
  readonly amount: int
}

class Worker {
  // Actor handles received from another domain are ordinary call targets.
  deliver(sink: Actor<Sink>, amount: int): none { sink.add(amount) }
  forward(envelope: Envelope): none { envelope.sink.add(envelope.amount) }
  // The consuming domain receives the promise's owned mutable result.
  consume(pending: Promise<int[]>): int {
    values := pending.get()!
    values.push(3)
    return values.length
  }
  create(): Actor<Sink> => Actor<Sink>()
}

class Loop {
  value(): int => 1
  callSelf(self: Actor<Loop>): int => self.value()
}

function main(): int {
  sink := Actor<Sink>()
  worker := Actor<Worker>()
  worker.deliver(sink, 1)
  worker.forward(Envelope { sink, amount: 2 })

  // Async workers capture the sink handle and fan in to it.
  let pending: Promise<none>[] = []
  for amount of 1..3 {
    pending.push(async {
      sink.add(amount)
      yield none
    })
  }
  for promise of pending { promise.get()! }
  assert(sink.read() == 9, "fan-in through a shared actor handle")

  assert(worker.consume(async { yield [1, 2] }) == 3, "promise consumed by another domain")

  created := async { yield Actor<Sink>() }
  fresh := created.get()!
  fresh.add(4)
  remote := worker.create()
  remote.add(5)
  assert(fresh.read() + remote.read() == 9, "actor handles returned across domains")

  // A synchronous call cycle panics instead of hanging.
  loop := Actor<Loop>()
  outcome := catchPanic(=> loop.callSelf(loop))
  assert(outcome.isFailure(), "self-call deadlock must panic")
  assert(loop.value() == 1, "actor keeps serving after a detected deadlock")

  println("shared handles ok")
  return 0
}
