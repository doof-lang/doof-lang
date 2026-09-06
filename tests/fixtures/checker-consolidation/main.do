function check(value: bool): none { if !value { panic("checker consolidation check failed") } }
class Box<T> { value: T
  static constructor(value: T): Box<T> => Box<T> { value } }
class Reader { read(first: int = 9, second: int = 9): int => first + second }
class Generic<T> { size(values: T[] = []): int => values.length }
interface Contract { read(first: int = 2, second: int = 3): int }
class Input { value: int }
function weakRead(value: weak Reader): int => value!.read{second: 4}
function optionalRead(value: weak Reader): Result<int | none, WeakReferenceError> => value?.read{second: 4}
function size(value: weak Generic<int>): int => value!.size()
class Stored { let value: int = 7
read(): int => this.value
update(value: int): none { this.value = value } }
class Factory { value: int
  static constructor(value: int = 9): Factory => Factory { value }
read(): int => value }
class DefaultBox<T> { values: T[] = [] }
class FallibleBox<T> { value: T
  static constructor(value: T): Result<FallibleBox<T>, string> => Success { value: FallibleBox<T> { value } } }
function main(): int {
  first := Actor<Stored>()
  second := Actor<Factory>()
  check(first.read() == 7)
  first.update(12)
  check(first.read() == 12)
  owned := retire first
  check(owned.value == 12)
  owned.value = 13
  check(owned.value == 13)
  check(second.read() == 9)
  check(DefaultBox<int>().values.length == 0)
  check((try! FallibleBox<int> { value: 8 }).value == 8)
  check(Box<int>(3).value == 3)
  check(Box<int> { value: 4 }.value == 4)
  input := Input { value: 5 }
  check(Box<int> { ...input }.value == 5)
  reader := Reader {}
  check(weakRead(reader) == 13)
  check((try! optionalRead(reader))! == 13)
  contract: Contract := reader
  check(contract.read{second: 4} == 6)
  generic := Generic<int> {}
  check(size(generic) == 0)
  value := 7
  values: Map<string, int> := { value }
  check(values["value"] == 7)
  return 0
}
