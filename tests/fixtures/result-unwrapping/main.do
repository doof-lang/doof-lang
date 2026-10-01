// Result unwrapping and intrinsic arms: `!.`, `try target = expr`, standalone
// Success/Failure structs, their equality, and arm case patterns.
enum Color { Red, Green }
struct Point { x: int }
class User { email: string; let tags: string[] = [] }
class Box<T> { value: T }
class Holder { let result: Result<int, string> = Failure("unset") }

let loads = 0
function loadUser(): Result<User, string> { loads += 1; return Success(User { email: "a@b" }) }
function maybeUser(): Result<User | none, string> => Success(User { email: "n@b" })
function color(): Result<Color, string> => Success(.Green)
function num(ok: bool): Result<int, string> => if ok then Success(7) else Failure("bad")
function loadFail(): Result<User, string> => Failure("gone")
function text(): Result<string, string> => Success("t")

function arm(): Success<int> => Success(5)
function failed(): Failure<string> => Failure { error: "no" }
function widened(): Result<long, string> { s: Success<int> := Success(2); return s }
function optional(): Result<int, string> | none => Success(3)
function explicit(flag: bool): Success<int> | Failure<string> => if flag then Success(1) else Failure("x")

function assigned(ok: bool): Result<int, string> {
  holder := Box<int> { value: 0 }
  let items = [0, 0]
  let wide: long | string = 0L
  let n = 0
  try items[1] = num(true)
  try wide = text()
  try n = num(ok)
  return Success(n + items[1] + (case wide { _: string -> 1, _ -> 0 }) + holder.value)
}

struct Wrapped { inner: Success<Point> }
function wrap<T>(x: T): Success<T> => Success(x)

function armOf(x: Success<int> | none): int => case x { s: Success -> s.value, _ -> 0 }
function boxed(x: Box<int> | string): int => case x { b: Box -> b.value, s: string -> s.length }
function bare(r: Result<int, string>): string => case r { s: Success -> string(s.value), f: Failure -> f.error }
function whole(r: Result<int, string>): int => case r { all: Result<int, string> -> all.unwrapOr(0) }

function main(): int {
  // A6: force access unwraps the receiver once, through nullable success values.
  if loadUser()!.email != "a@b" || loads != 1 { return 1 }
  if maybeUser()!.email != "n@b" || color()!.name != "Green" { return 2 }
  loadUser()!.tags.push("x")
  forced := catchPanic(=> loadFail()!.email)
  if forced.isSuccess() { return 3 }

  // A8: try assignment stores the converted success value or propagates.
  if assigned(true).unwrapOr(-1) != 15 || !assigned(false).isFailure() { return 4 }
  let caught = 0
  err: string | none := catch { try caught = num(false) }
  if err != "bad" || caught != 0 { return 5 }

  // A9: arms are values of their own types that convert to Results.
  inferred := Success(1)
  wide: Success<long> := Success(9)
  holder := Holder {}
  holder.result = arm()
  items: Result<int, string>[] := [arm(), failed(), Success(7)]
  let total = 0
  for item of items { total += item.unwrapOr(100) }
  if total != 112 || holder.result.unwrapOr(0) != 5 || widened().unwrapOr(0L) != 2L { return 6 }
  if inferred.value + int(wide.value) != 10 || optional() == none || explicit(false).isSuccess() { return 7 }
  { value } := inferred
  if value != 1 { return 8 }

  // Equality: arms compare their payload; Results and unions compare members.
  if Success(5) != Success(5) || Success(5) == Success(6) || Failure() != Failure() { return 9 }
  if num(true) != Success(7) || num(false) != Failure("bad") || num(true) == num(false) { return 10 }
  u: int | string := 1
  v: Point | string := Point { x: 1 }
  if u != 1 || u == "a" || v != Point { x: 1 } { return 11 }

  // Patterns: bare generic names take the subject member's arguments.
  if armOf(Success(4)) != 4 || armOf(none) != 0 { return 12 }
  if boxed(Box<int> { value: 7 }) != 7 || boxed("ab") != 2 { return 13 }
  if bare(num(true)) != "7" || bare(num(false)) != "bad" || whole(num(true)) != 7 { return 14 }

  // Arms hold struct and generic class payloads, through generic functions.
  wrapped := Wrapped { inner: Success(Point { x: 2 }) }
  boxedArm := wrap(Box<int> { value: 3 })
  if wrapped.inner.value.x != 2 || boxedArm.value.value != 3 || wrapped != Wrapped { inner: Success(Point { x: 2 }) } { return 15 }
  return 0
}
