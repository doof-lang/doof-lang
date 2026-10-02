// Optional chaining over every nullable carrier: shared_ptr classes,
// std::optional strings and structs, and variants with a none arm.
class Address { city: string }
class User {
  name: string
  address: Address | none
  let visits: int = 0
  greet(prefix: string): string => prefix + name
  visit(): none { visits += 1 }
  maybeCity(): string | none => address?.city
}
class Left { value: int
  read(): int => value * 2 }
class Right { value: int
  read(): int => value * 3 }
struct Point { x: int
  y: int
  sum(): int => x + y }

let lookups = 0
function lookup(present: bool): User | none {
  lookups += 1
  return if present then User { name: "ada", address: Address { city: "Paris" } } else none
}

enum LookupError { Missing }
enum ProfileError { Private }
class Profile { bio: string }
class Account {
  name: string
  hidden: bool
  profile(): Result<Profile, ProfileError> {
    if hidden { return Failure(.Private) }
    return Success(Profile { bio: name })
  }
  shout(): string => name.toUpperCase()
}
function findAccount(id: int): Result<Account, LookupError> {
  if id == 0 { return Failure(.Missing) }
  return Success(Account { name: "ada", hidden: id == 2 })
}
function maybeAccount(present: bool): Result<Account | none, LookupError> {
  return if present then Success(Account { name: "bob", hidden: false }) else Success(none)
}
function chainText<E>(value: Result<Profile | none, E>): string => case value {
  s: Success -> s.value?.bio ?? "<none>",
  _: Failure -> "<failure>",
}
function outerAccount(id: int): Result<Account, LookupError> | none {
  if id == 0 { return none }
  return findAccount(id)
}

function main(): none {
  user: User | none := lookup(true)
  missing: User | none := none
  assert((user?.name ?? "-") == "ada" && (missing?.name ?? "-") == "-", "optional field")
  assert((user?.greet("hi ") ?? "-") == "hi ada" && (missing?.greet("hi ") ?? "-") == "-", "optional method call")
  user?.visit()
  missing?.visit()
  assert(user!.visits == 1, "none-returning call runs only when present")
  assert((user?.address?.city ?? "-") == "Paris" && (missing?.address?.city ?? "-") == "-", "chained access")
  assert((user?.maybeCity() ?? "-") == "Paris", "nullable result is not double wrapped")
  text: string | none := "hello"
  noText: string | none := none
  assert((text?.length ?? -1) == 5 && (noText?.length ?? -1) == -1, "optional builtin property")
  assert((text?.toUpperCase() ?? "-") == "HELLO", "optional builtin method")
  either: Left | Right | none := Right { value: 5 }
  neither: Left | Right | none := none
  assert((either?.value ?? -1) == 5 && (either?.read() ?? -1) == 15 && (neither?.read() ?? -1) == -1, "variant receiver")
  point: Point | none := Point { x: 2, y: 3 }
  noPoint: Point | none := none
  assert((point?.x ?? -1) == 2 && (point?.sum() ?? -1) == 5 && (noPoint?.sum() ?? -1) == -1, "struct receiver")
  items: string[] | none := ["a", "b"]
  noItems: string[] | none := none
  assert((items?[1] ?? "-") == "b" && (noItems?[0] ?? "-") == "-", "optional array index")
  maybeScores: Map<string, int> | none := { "k": 7 }
  assert((maybeScores?["k"] ?? -1) == 7, "optional map index")
  lookups = 0
  assert((lookup(true)?.name ?? "-") == "ada" && lookups == 1, "receiver is evaluated once")
  // A Result receiver is absent on Failure or a none success value.
  assert((findAccount(1)?.name ?? "-") == "ada", "Result field")
  assert((findAccount(0)?.name ?? "-") == "-", "Result failure is absent")
  assert((maybeAccount(false)?.shout() ?? "-") == "-" && (maybeAccount(true)?.shout() ?? "-") == "BOB", "none success is absent")
  assert((outerAccount(0)?.name ?? "-") == "-" && (outerAccount(1)?.name ?? "-") == "ada", "outer none is absent")
  // A Result-returning member keeps its Failure and widens its success value.
  assert(chainText(findAccount(1)?.profile()) == "ada", "Result-returning call")
  assert(chainText(findAccount(2)?.profile()) == "<failure>", "member failure is kept")
  assert(chainText(findAccount(0)?.profile()) == "<none>", "absent receiver is a none success value")
  assert((findAccount(2)?.profile()?.bio ?? "-") == "-" && (findAccount(1)?.profile()?.bio ?? "-") == "ada", "chained Result")
  assert(findAccount(0)? == none && findAccount(1)?!.name == "ada", "postfix ? collapses failure")
  assert(maybeAccount(true)!.name == "bob" && (maybeAccount(false) ?? Account { name: "z", hidden: false }).name == "z", "! and ?? collapse every layer")
}
