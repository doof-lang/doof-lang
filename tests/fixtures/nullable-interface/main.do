// A union carrier splices an interface member's implementing classes into one
// flat variant, so removing none from `Shape | none` yields `Shape` itself.
interface Shape { area(): double }
class Circle implements Shape { radius: double; area(): double => radius * 2.0 }
class Square implements Shape { side: double; area(): double => side * side }
class Label { text: string; width(): double => 0.5 }

class Holder {
  focus: Shape | none = none
}

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function bound(holder: Holder): double {
  shape := holder.focus else { return -1.0 }
  return shape.area()
}

function matched(holder: Holder): double {
  case holder.focus {
    shape: Shape -> { return shape.area() }
    _ -> { return -1.0 }
  }
}

function classify(item: Shape | Label | none): string {
  case item {
    circle: Circle -> { return "circle " + string(circle.radius) }
    shape: Shape -> { return "shape " + string(shape.area()) }
    label: Label -> { return "label " + label.text }
    _ -> { return "none" }
  }
}

function widen(shape: Shape): Shape | none => shape

function main(): int {
  holder := Holder { focus: Square { side: 3.0 } }
  empty := Holder {}
  check(holder.focus!.area() == 9.0, "force access calls through the interface")
  forced: Shape := holder.focus!
  check(forced.area() == 9.0, "force yields the interface value")
  check((holder.focus?.area() ?? 0.0) == 9.0, "optional access calls through the interface")
  check((empty.focus?.area() ?? 0.0) == 0.0, "optional access short-circuits on none")
  fallback: Shape := empty.focus ?? Circle { radius: 1.0 }
  check(fallback.area() == 2.0, "coalesce yields the interface value")
  check(bound(holder) == 9.0 && bound(empty) == -1.0, "declaration-else binds the interface value")
  check(matched(holder) == 9.0 && matched(empty) == -1.0, "case binds the interface value")

  check(widen(forced)!.area() == 9.0, "an interface value widens into its nullable union")
  check(classify(Circle { radius: 4.0 }) == "circle 4", "a class pattern matches an implementor arm")
  check(classify(Square { side: 2.0 }) == "shape 4", "an interface pattern gathers implementor arms")
  check(classify(Label { text: "x" }) == "label x", "other union members keep their own arm")
  check(classify(none) == "none", "none stays the empty arm")
  // Circle is already a Shape arm; member dispatch visits each flattened arm.
  overlapping: Shape | Circle := Circle { radius: 1.5 }
  check(overlapping.area() == 3.0, "an implementor named beside its interface shares one arm")
  println("ok")
  return 0
}
