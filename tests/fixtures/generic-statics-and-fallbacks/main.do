// Generic static methods and static fields of generic classes, `??` and other
// fallbacks inside generic bodies, and formatting of nested optional values.
class Stack<T> {
  let items: T[] = []
  static let created: int = 0
  static empty<U>(): Stack<U> => Stack<U> {}
  static single<U>(value: U): Stack<U> { stack := Stack<U> {}; stack.items.push(value); return stack }
  static wrap<U>(value: U): U[] => [value]
  // Bare static fields resolve in static methods and in their lambdas.
  static count(): int { created += 1; next := () => created * 10; return next() }
  peek(): int { read := () => created; return read() }
}
class Holder<T> { value: T }
class Ref<T> { weak target: Holder<T> }
class Cache<K, V> {
  let store: Map<K, V> = {}
  item: V
  lookup(key: K): V | none => store.get(key) ?? none
  fallback(result: Result<V, string>): V => result.unwrapOr(item)
  scoped(): V {
    with holder := Holder<V> { value: item } { return holder.value }
  }
  caught(read: (): Result<V, string>): string | none => catch { try value := read() }
  deref(ref: Ref<V>): V => ref.target!.value
}

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

let idled = 0
function idle(): none { idled += 1 }

function wrapInt(wrap: (value: int): int[], value: int): int[] => wrap(value)

function main(): int {
  check(Stack<string>.empty<int>().items.length == 0, "explicit class and method arguments")
  check(Stack<int>.single<string>("a").items[0] == "a", "method arguments differ from class arguments")
  check(Stack<string>.wrap<int>(3)[0] == 3, "a non-class generic result")
  check(wrapInt(Stack<string>.wrap, 4)[0] == 4, "a generic static method reference")

  check(Stack<int>.count() == 10 && Stack<int>.count() == 20, "static fields are per instantiation")
  check(Stack<string>.count() == 10, "another instantiation has its own static field")
  check(Stack<int> {}.peek() == 2, "an instance method lambda reads a static field")

  cache := Cache<string, int> { item: 7 }
  cache.store["a"] = 1
  check((cache.lookup("a") ?? 0) == 1 && (cache.lookup("b") ?? -1) == -1, "?? in a generic method")
  check(cache.fallback(Failure("x")) == 7, "unwrapOr in a generic method")
  check(cache.scoped() == 7, "with in a generic method")
  check((cache.caught(() => Failure("bad")) ?? "fine") == "bad", "catch in a generic method")
  holder := Holder<int> { value: 9 }
  check(cache.deref(Ref<int> { target: holder }) == 9, "forced weak access in a generic method")

  check((idle() ?? "ok") == "ok" && idled == 1, "?? over an always-none source evaluates it once, then falls back")

  optionals: (int | none)[] := [1, none]
  check("${optionals}" == "[1, null]", "arrays of optionals format")
  mixed: Map<string, int | string> := { a: 1, b: "x" }
  check("${mixed}" == "{a: 1, b: x}", "maps of unions format")
  check("${(1, [none, 2])}" == "(1, [null, 2])", "tuples of optional arrays format")
  println("generic statics and fallbacks ok")
  return 0
}
