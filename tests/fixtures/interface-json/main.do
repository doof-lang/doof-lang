// Interface values encode through their implementation and decode through the
// shared discriminator, directly, as nested fields, and recursively.
interface Shape { area(): double }
class Circle implements Shape { kind: "circle"; radius: double; area(): double => radius }
class Rect implements Shape { kind: "rect"; width, height: double; area(): double => width * height }

class Scene {
  shapes: Shape[]
  focus: Shape | none = none
  named: Map<string, Shape> = {}
}

interface Node { weight(): int }
class Leaf implements Node { kind: "leaf"; value: int; weight(): int => value }
class Branch implements Node {
  kind: "branch"
  children: Node[]
  weight(): int {
    let total = 0
    for child of children { total += child.weight() }
    return total
  }
}

// Encoding needs no discriminator.
interface Pet { speak(): string }
class Dog implements Pet { name: string; speak(): string => "woof" }
class Cat implements Pet { lives: int; speak(): string => "meow" }
class Kennel { pets: Pet[] }

interface Ghost { haunt(): int }
class Mansion { ghost: Ghost | none = none }

function encode<T: Serializable>(value: T): SerialObject => value.toSerialObject()
function decode<T: Serializable>(json: SerialValue): Result<T, string> => T.fromSerialValue(json)

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function totalArea(scene: Scene): double {
  let total = 0.0
  for shape of scene.shapes { total += shape.area() }
  return total
}

function main(): int {
  circle: Shape := Circle { radius: 2.0 }
  direct := circle.toSerialObject()
  check((direct.get("kind")! as string)! == "circle", "direct encode keeps the discriminator")
  check((direct.get("radius")! as double)! == 2.0, "direct encode keeps implementation fields")

  scene := Scene { shapes: [circle, Rect { width: 1.0, height: 3.0 }], focus: circle, named: { a: circle } }
  json := scene.toSerialObject()
  restored := Scene.fromSerialValue(json)!
  check(totalArea(restored) == 5.0, "interface array round-trips")
  check(restored.focus != none, "nullable interface field round-trips")
  check(restored.named.get("a").isSuccess(), "interface map value round-trips")
  check(Scene.fromSerialValue({ shapes: [] }).isSuccess(), "nullable and defaulted interface fields are optional")
  unknown := Scene.fromSerialValue({ shapes: [{ kind: "hex" }] })
  check(case unknown { _: Success -> "", f: Failure -> f.error } == "Field \"shapes\": [0]: Unknown kind: \"hex\"", "nested unknown discriminator reports its path")

  tree: Node := Branch { children: [Leaf { value: 1 }, Branch { children: [Leaf { value: 2 }] }] }
  check((Node.fromSerialValue(tree.toSerialObject())!).weight() == 3, "recursive interface round-trips")

  check((encode<Shape>(circle).get("kind")! as string)! == "circle", "Serializable parameter encodes an interface")
  check((decode<Shape>({ kind: "rect", width: 2.0, height: 2.0 })!).area() == 4.0, "Serializable parameter decodes an interface")

  kennel := Kennel { pets: [Dog { name: "Rex" }, Cat { lives: 9 }] }.toSerialObject()
  check(kennel.has("pets"), "interfaces without a discriminator still encode")
  check(Mansion {}.toSerialObject().get("ghost")! == none, "an interface without implementations encodes as absent")
  println("ok")
  return 0
}
