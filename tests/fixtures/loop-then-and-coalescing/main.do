// Runtime behavior for loop `then` clauses, `??=`, Map.delete, Result-valued
// if-expressions, and weak optional calls to none-returning methods.
function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function forOfThen(items: int[], target: int): string {
  let result = "none"
  for item of items {
    if item == target {
      result = "found"
      break
    }
  } then {
    result = "completed"
  }
  return result
}

function whileThen(limit: int, stopAt: int): int {
  let count = 0
  let marker = 0
  while count < limit {
    if count == stopAt { break }
    count += 1
  } then {
    marker = 100
  }
  return count + marker
}

function forThen(limit: int, stopAt: int): int {
  let marker = 0
  for let i = 0; i < limit; i += 1 {
    if i == stopAt { break }
  } then {
    marker = 1
  }
  return marker
}

function nestedThen(): string {
  let log = ""
  outer: for row of [1, 2] {
    for cell of [1, 2, 3] {
      if cell == 2 { break }
    } then {
      log = log + "inner"
    }
    if row == 2 { break outer }
  } then {
    log = log + "outer"
  }
  return log
}

function earlyReturn(): int {
  for item of [1, 2, 3] {
    if item == 2 { return item }
  } then {
    return -1
  }
  return 0
}

function lookup(ok: bool): Result<int, string> => if ok then Success(7) else Failure("missing")

class Watcher {
  let seen: int = 0
  touch(): none { seen += 1 }
}

class Holder {
  let target: weak Watcher | none = none
}

function main(): int {
  check(forOfThen([1, 2, 3], 2) == "found", "for-of break skips then")
  check(forOfThen([1, 2, 3], 9) == "completed", "for-of completion runs then")
  check(forOfThen([], 9) == "completed", "empty for-of runs then")
  check(whileThen(3, 1) == 1, "while break skips then")
  check(whileThen(3, 9) == 103, "while completion runs then")
  check(forThen(3, 1) == 0, "for break skips then")
  check(forThen(3, 9) == 1, "for completion runs then")
  check(nestedThen() == "", "breaks skip inner and labeled outer then")
  check(earlyReturn() == 2, "return skips then")

  let cache: string | none = none
  cache ??= "disk"
  cache ??= "network"
  check(cache! == "disk", "??= assigns only when none")
  let data: Result<int, string> = lookup(false)
  data ??= 4
  check(data! == 4, "??= wraps a plain value for a Failure target")
  data ??= lookup(false)
  check(data! == 4, "??= keeps an existing Success")

  let scores: Map<string, int> = { "a": 1, "b": 2, "c": 3 }
  scores.delete("b")
  scores.delete("missing")
  check(scores.size == 2 && !scores.has("b"), "Map.delete removes the key")
  scores.set("b", 9)
  check(scores.keys()[2] == "b", "reinsertion after delete appends")

  check(lookup(true)! == 7, "Result if-expression success arm")
  check((lookup(false) ?? 0) == 0, "Result if-expression failure arm")

  watcher := Watcher {}
  let holder = Holder {}
  _ := holder.target?.touch()
  holder.target = watcher
  _ := holder.target?.touch()
  check(watcher.seen == 1, "weak optional none call reaches the live target")
  println("ok")
  return 0
}
