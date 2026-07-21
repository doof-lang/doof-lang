// Smallest current Doof emitter bottleneck:
// converting a present variant into an optional variant field and binding.

class Left {
  value: int
}

class Right {
  value: int
}

type Value = Left | Right

class Holder {
  value: Value | none
}

function makeValue(): Value => Left { value: 1 }

function makeHolder(): Holder {
  let value: Value | none = none
  value = makeValue()
  return Holder { value }
}

function main(): int => 0
