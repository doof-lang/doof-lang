let received = ""

function onString(value: string): none { received = received + value }

class Channel<T> {
  handler: (value: T): none
  static constructor(handler: (value: T): none): Channel<T> {
    return Channel<T> { handler }
  }
}

class Box<T> { value: T }

class Codec<T> {
  static let created = 0
  static tag(): string => "codec"
  static describe(value: T): string => "codec"
  static wrap(value: T): Result<Codec<T>, string> {
    if false { return Failure("never") }
    return Success(Codec<T> {})
  }
}

function describeAll<T>(value: T): string => Codec.describe(value)

function unbox<T>(value: T): T {
  box := Box { value }
  return box.value
}

function main(): none {
  a := Channel<string> { handler: onString }
  b := Channel { handler: onString }
  c := Channel.constructor{ handler: onString }
  d := Channel.constructor(onString)
  e := <Channel handler={onString}/>
  a.handler("a"); b.handler("b"); c.handler("c"); d.handler("d"); e.handler("e")
  assert(received == "abcde", "every construction spelling infers Channel<string>")

  assert(Box { value: 42 }.value + 1 == 43, "named construction infers Box<int>")
  assert(Box("s").value == "s", "call construction infers Box<string>")
  assert(unbox(2.5) == 2.5, "inference inside a generic function")

  assert(Codec.describe(3) == "codec", "static call instantiates Codec<int>")
  assert(describeAll(true) == "codec", "static call inside a generic function")
  codec := Codec.wrap(1.5)
  assert(codec.isSuccess(), "static factory returning Result")

  assert(Codec<string>.tag() == "codec", "explicit static receiver")
  explicit := Channel<string>.constructor(onString)
  explicit.handler("f")
  assert(received == "abcdef", "explicit static factory")
  Codec<string>.created += 2
  Codec<int>.created += 1
  assert(Codec<string>.created == 2 && Codec<int>.created == 1, "static fields exist per instantiation")
}
