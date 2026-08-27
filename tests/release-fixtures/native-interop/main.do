import class Client from "client.hpp" as release_native::Client {
  value: int
  get(): int
  static make(value: int): Client
  same(): Client { return this }
}

import function boxValue<T>(box: Box<T>): T from "client.hpp" as release_native::boxValue

class Box<T> {
  value: T
}

function main(): int {
  client := Client { value: 4 }
  made := Client.make(6)
  same := client.same()
  boxed := boxValue(Box<int> { value: 7 })
  return if client.get() + made.get() + same.get() + boxed == 21 then 0 else 1
}
