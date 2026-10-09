// `weak` prefixes a complete type. Grouped spellings choose which side of a
// collection is weak, and every optional weak spelling is one type.
class Listener {
  id: int
}

class Registry {
  listeners: (weak Listener)[] = []
  byName: Map<string, weak Listener> = {}
  let grouped: (weak Listener) | none = none
  let whole: weak Listener | none = none
  let weak modifier: Listener | none = none
}

function live(registry: Registry): int {
  let count = 0
  for listener of registry.listeners {
    if listener?.id != none { count += 1 }
  }
  return count
}

function describe(value: weak Listener | none): string {
  return case value {
    s: Success -> if s.value == none then "absent" else "live",
    _: Failure -> "expired"
  }
}

// The temporary listener is released when this function returns.
function holdTemporary(registry: Registry): none {
  dropped := Listener { id: 2 }
  registry.listeners.push(dropped)
  registry.grouped = dropped
  registry.whole = registry.grouped
  registry.modifier = registry.whole
  assert(live(registry) == 2, "both listeners are live in scope")
  assert(describe(registry.whole) == "live", "a held referent is live")
}

function main(): int {
  registry := Registry {}
  kept := Listener { id: 1 }
  registry.listeners.push(kept)
  registry.byName.set("kept", kept)
  assert(describe(registry.grouped) == "absent", "an unset optional weak reference is absent")
  assert(registry.grouped == none, "an unset optional weak reference compares equal to none")
  holdTemporary(registry)
  assert(live(registry) == 1, "a weak array element expires with its referent")
  assert(describe(registry.grouped) == "expired", "an expired reference is not absent")
  assert(registry.grouped != none, "== none tests absence, not expiry")
  assert(registry.whole?.id == none, "?. on an expired reference is none")
  assert(describe(registry.modifier) == "expired", "the field modifier spelling is the same type")
  assert(registry.byName.get("kept")!?.id == 1, "weak map values stay live while held")
  println("weak precedence ok")
  return 0
}
