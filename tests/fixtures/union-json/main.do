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

// Primitive, enum, container, and class members decode by their JSON kind.
enum Level { Low = "low", High = "high" }

class Record {
  id: int | string
  flag: bool | Level | none = none
  values: (double | string)[] = []
  extra: Map<string, int | bool> = {}
  shape: Shape | Note | int[] | string = "none"
  pair: Tuple<int | string, bool>
}

function recordError(input: SerialValue): string {
  return case Record.fromSerialValue(input) {
    _: Success -> "decoded",
    failure: Failure -> failure.error
  }
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
  record := Record { id: "r1", flag: Level.High, values: [1.5, "x"], extra: { "n": 2, "b": true }, shape: Circle { radius: 2.0 }, pair: (3, false) }
  recordJson := record.toSerialObject()
  check((recordJson.get("id")! as string)! == "r1" && (recordJson.get("flag")! as string)! == "high", "primitive and enum arms encode as their JSON values")
  decoded := Record.fromSerialValue(recordJson)!
  check((decoded.id as string)! == "r1" && (decoded.flag as Level)! == Level.High, "string and enum arms decode by JSON kind")
  check((decoded.values[0] as double)! == 1.5 && (decoded.values[1] as string)! == "x", "array elements decode per JSON kind")
  check((decoded.extra.get("b")! as bool)! && (decoded.extra.get("n")! as int)! == 2, "map values decode per JSON kind")
  check((decoded.shape as Circle)!.radius == 2.0, "a class arm decodes beside primitive arms")
  (pairId, pairFlag) := decoded.pair
  check((pairId as int)! == 3 && !pairFlag, "tuple elements decode per JSON kind")
  numeric := Record.fromSerialValue({ id: 4, flag: true, shape: [1, 2], pair: ["p", true] })!
  check((numeric.id as int)! == 4 && (numeric.flag as bool)! && (numeric.shape as int[])!.length == 2, "number, boolean, and array arms decode")
  check(recordError({ id: true, pair: [1, true] }) == "Field \"id\" expected int or string but got boolean", "a union rejects a JSON kind it has no member for")
  check(recordError({ id: 1.5, pair: [1, true] }) == "Field \"id\": Expected int but got number", "a number arm validates its own range")
  check(recordError({ id: 1, values: [none], pair: [1, true] }) == "Field \"values\": [0]: Expected number or string but got null", "a nested union reports its path")
  check(recordError({ id: 1, flag: "mid", pair: [1, true] }).startsWith("Field \"flag\": Unknown backing value"), "an enum arm validates its backing value")

  // A malformed scalar inside a container is a decode failure, not a panic.
  check(recordError({ id: 1, extra: { "n": "x" }, pair: [1, true] }) == "Field \"extra\": .n: Expected int or boolean but got string", "a map value union reports its key path")

  println("union json ok")
  return 0
}
