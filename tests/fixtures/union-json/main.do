// Unions of classes and interfaces encode each arm through its own class and
// decode through one discriminator shared by every class they flatten to.
interface Shape { area(): double }
interface Named { name(): string }
class Circle implements Shape { kind: "circle"; radius: double; area(): double => radius * 2.0 }
class Square implements Shape { kind: "square"; side: double; area(): double => side * side }
class Badge implements Shape, Named { kind: "badge"; area(): double => 1.0; name(): string => "badge" }
class Tag implements Named { kind: "tag"; text: string; name(): string => text }
class Note { kind: "note"; text: string }

class Leaf { kind: "leaf"; value: int }
class Branch { kind: "branch"; children: (Leaf | Branch)[] }

class Scene {
  pick: Circle | Note
  focus: Shape | Note | none = none
  either: Shape | Named | none = none
  items: (Shape | Note)[] = []
  byName: Map<string, Circle | Square | none> = {}
  pair: Tuple<Shape | Note, int>
}

// A class without the shared discriminator still encodes.
class Plain { text: string }
class EncodeOnly { value: Plain | Note }

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function decodeError(input: SerialValue): string {
  return case Scene.fromSerialValue(input) {
    _: Success -> "decoded",
    failure: Failure -> failure.error
  }
}

function weight(node: Leaf | Branch): int {
  return case node {
    leaf: Leaf -> leaf.value,
    branch: Branch -> {
      let total = 0
      for child of branch.children { total += weight(child) }
      yield total
    }
  }
}

function main(): int {
  pairShape: Shape | Note := Circle { radius: 0.5 }
  scene := Scene {
    pick: Note { text: "n" },
    focus: Square { side: 2.0 },
    either: Badge {},
    items: [Circle { radius: 1.0 }, Note { text: "m" }, Badge {}],
    byName: { "c": Circle { radius: 3.0 }, "n": none },
    pair: (pairShape, 7),
  }
  restored := Scene.fromSerialValue(scene.toSerialObject())!
  check((restored.focus as Square)!.side == 2.0, "an interface arm decodes to its implementing class")
  check((restored.either as Badge).isSuccess(), "a class shared by two interfaces decodes once")
  check((restored.pick as Note)!.text == "n", "a class arm decodes beside another class")
  check(restored.items.length == 3 && (restored.items[1] as Note)!.text == "m", "array elements decode per arm")
  (decodedShape, pairCount) := restored.pair
  check((decodedShape as Circle)!.radius == 0.5 && pairCount == 7, "a tuple element decodes as an object union")
  storedNone := case restored.byName.get("n") { s: Success -> s.value == none, _: Failure -> false }
  check(storedNone && restored.byName.get("c")!.area() == 6.0, "map values decode with null as none")

  tree := Branch { children: [Leaf { value: 1 }, Branch { children: [Leaf { value: 2 }, Leaf { value: 3 }] }] }
  treeJson := tree.toSerialObject()
  check(weight(Branch.fromSerialValue(treeJson)!) == 6, "a recursive object union round-trips")

  check(decodeError({ pick: { kind: "triangle" } }) == "Field \"pick\": Unknown kind: \"triangle\"", "an unknown discriminator names its field")
  check(decodeError({ pick: { radius: 1.0 } }) == "Field \"pick\": Missing or invalid discriminator field \"kind\"", "a missing discriminator names its field")
  check(decodeError({ pick: none }) == "Field \"pick\" expected object but got null", "a union without none rejects null")
  check(decodeError({ pick: { kind: "note", text: 3 } }).startsWith("Field \"pick\": "), "a member class failure keeps the union field path")

  plain := EncodeOnly { value: Plain { text: "p" } }.toSerialObject()
  check(Plain.fromSerialValue(plain.get("value")!)!.text == "p", "a union without a discriminator still encodes its class arm")
  println("union json ok")
  return 0
}
