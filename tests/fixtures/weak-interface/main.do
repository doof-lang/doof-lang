// A weak interface reference holds a weak_ptr for each implementing class in
// one variant; locking it yields the strong interface value.
interface Shape { area(): double }
class Circle implements Shape { radius: double; area(): double => radius * 2.0 }
class Square implements Shape { side: double; area(): double => side * side }
class Label { text: string }
interface Plugin { run(): int }

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
  println("weak interface ok")
  return 0
}
