// A weak interface reference holds a weak_ptr for each implementing class in
// one variant; locking it yields the strong interface value.
interface Shape { area(): double }
class Circle implements Shape { radius: double; area(): double => radius * 2.0 }
class Square implements Shape { side: double; area(): double => side * side }
class Label { text: string }
interface Plugin { run(): int }
interface Named { name(): string }
interface Solo { solo(): int }
interface Source<T> { pull(): T }
class Badge implements Shape, Named { area(): double => 1.0; name(): string => "badge" }
class Tag implements Named { text: string; name(): string => text }
class Only implements Solo { solo(): int => 7 }
class Counter implements Source<int> { let count: int = 0; pull(): int { count += 1; return count } }

class Canvas {
  let weak focus: Shape = Circle { radius: 0.0 }
  let selection: weak Shape | none = none
  let tagged: weak Shape | Label | none = none
  watchers: (weak Shape)[] = []
  let plugin: weak Plugin | none = none
}

class Slot<T: Shape> {
  let held: weak T | none = none
}

function pick(flag: bool): Shape | none => if flag then Square { side: 2.0 } else none

function describe(value: weak Shape | none): string {
  return case value {
    s: Success -> if s.value == none then "absent" else "live " + string(s.value!.area()),
    _: Failure -> "expired"
  }
}

function tag(value: weak Shape | Label | none): string {
  return case value {
    s: Success -> case s.value {
      label: Label -> "label " + label.text,
      shape: Shape -> "shape " + string(shape.area()),
      _ -> "absent"
    },
    _: Failure -> "expired"
  }
}

function viaShape(value: weak Shape): double | none => value?.area()

function expire(): weak Circle | none {
  temporary := Circle { radius: 1.0 }
  held: weak Circle | none := temporary
  return held
}

// A weak union of two interfaces shares the arm of a class implementing both.
function weakName(value: weak Shape | Named | none): string {
  return case value {
    s: Success -> case s.value {
      badge: Badge -> "badge",
      named: Named -> "named " + named.name(),
      shape: Shape -> "shape " + string(shape.area()),
      _ -> "absent"
    },
    _: Failure -> "expired"
  }
}

function weakTwoInterfaces(): none {
  badge := Badge {}
  tag := Tag { text: "t" }
  let held: weak Shape | Named | none = badge
  assert(weakName(held) == "badge", "a shared implementor is one weak arm")
  held = tag
  assert(weakName(held) == "named t", "a second interface arm stays weak")
  held = Circle { radius: 1.0 }
  assert(weakName(held) == "expired", "a temporary stored weakly expires at once")
}

function weakSingleAndGeneric(): none {
  only := Only {}
  solo: weak Solo := only
  assert(solo?.solo() == 7, "a single-implementor weak interface")
  counter := Counter {}
  source: weak Source<int> | none := counter
  assert(source?.pull() == 1 && source!.pull() == 2 && counter.count == 2, "a weak generic interface reaches the shared referent")
  byName: Map<string, weak Shape> := {}
  square := Square { side: 2.0 }
  byName.set("square", square)
  assert(byName.get("square")!?.area() == 4.0, "weak interface map values stay live while held")
}

function live(canvas: Canvas): int {
  let count = 0
  for watcher of canvas.watchers {
    if watcher?.area() != none { count += 1 }
  }
  return count
}

// Every referent created here is released when the function returns.
function holdTemporary(canvas: Canvas): none {
  square := Square { side: 3.0 }
  canvas.focus = square
  canvas.selection = square
  canvas.tagged = square
  canvas.watchers.push(square)
  assert(canvas.focus!.area() == 9.0, "force access calls through a live weak interface")
  assert(canvas.selection?.area() == 9.0, "optional access calls through a live weak interface")
  assert(describe(canvas.selection) == "live 9", "a case read locks the weak interface")
  assert(tag(canvas.tagged) == "shape 9", "a weak union narrows its interface arm")
  assert(live(canvas) == 2, "both watchers are live in scope")
}

function main(): int {
  canvas := Canvas {}
  kept := Circle { radius: 1.5 }
  canvas.watchers.push(kept)
  assert(describe(canvas.selection) == "absent", "an unset weak interface is absent")
  assert(canvas.selection == none, "an unset weak interface compares equal to none")
  holdTemporary(canvas)
  assert(live(canvas) == 1, "a weak interface element expires with its referent")
  assert(describe(canvas.selection) == "expired", "an expired weak interface is not absent")
  assert(canvas.selection?.area() == none, "?. on an expired weak interface is none")
  assert(canvas.focus?.area() == none, "a non-nullable weak interface expires too")
  assert(tag(canvas.tagged) == "expired", "an expired weak union reports expiry")
  label := Label { text: "x" }
  strong := pick(true)
  canvas.selection = strong
  canvas.tagged = strong
  assert(canvas.selection?.area() == 4.0 && tag(canvas.tagged) == "shape 4", "a strong interface value stores into weak references")
  canvas.selection = pick(false)
  assert(describe(canvas.selection) == "absent", "an absent strong value stores as absent, not expired")
  assert(canvas.plugin?.run() == none, "an implementationless weak interface checks and stays absent")
  slot := Slot<Shape> {}
  slot.held = strong
  assert(slot.held?.area() == 4.0, "a weak type parameter accepts an interface")
  canvas.tagged = label
  assert(tag(canvas.tagged) == "label x", "a weak union keeps its class arm")

  // Weak references widen wherever the referent keeps its identity.
  weakCircle: weak Circle := kept
  assert(viaShape(weakCircle) == 3.0, "a weak class widens to its weak interface")
  pair: weak Circle | Label := weakCircle
  wider: weak Circle | Label | Square := pair
  assert(tag(wider) == "shape 3", "a weak union widens to a wider weak union")
  canvas.selection = weakCircle
  canvas.tagged = canvas.selection
  assert(tag(canvas.tagged) == "shape 3", "an optional weak interface widens to a wider optional")
  canvas.selection = none
  canvas.tagged = canvas.selection
  assert(tag(canvas.tagged) == "absent", "absence stays absent when widening")
  assert(tag(expire()) == "expired", "expiry survives widening")
  weakTwoInterfaces()
  weakSingleAndGeneric()
  println("weak interface ok")
  return 0
}
