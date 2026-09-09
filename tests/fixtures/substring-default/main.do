let receiverCalls = 0
let startCalls = 0

function text(): string {
  receiverCalls += 1
  return "hello"
}

function start(): int {
  startCalls += 1
  return 2
}

function main(): none {
  assert(text().substring(start()) == "llo", "default end")
  assert(receiverCalls == 1 && startCalls == 1, "evaluate receiver and start once")
  assert("hello".substring(0) == "hello", "zero start")
  assert("hello".substring(-2) == "hello", "negative start")
  assert("hello".substring(5) == "", "start at end")
  assert("hello".substring(9) == "", "start beyond end")
  assert("".substring(0) == "", "empty string")
  assert("hello".substring{start: 2} == "llo", "named start")
  assert("hello".substring(1, 4) == "ell", "explicit end")
  assert("hello".substring{end: 4, start: 1} == "ell", "named range order")
  assert("hello".substring(2, 99) == "llo", "clamped end")
  assert("hello".substring(4, 1) == "", "reversed range")
}
