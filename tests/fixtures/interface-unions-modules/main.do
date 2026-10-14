// Interface unions across modules: the interface, its implementors (one
// generic), and the classes holding nullable and weak interface values each
// live in their own module.
import { Shape } from "./shapes"
import { Circle } from "./circle"
import { Boxed } from "./boxed"
import { Marker } from "./marker"
import { Scene, Snapshot, Watcher, focusArea, narrow } from "./scene"

function check(condition: bool, message: string): none {
  if !condition { panic(message) }
}

function watch(watcher: Watcher): none {
  temporary := Circle { radius: 5.0 }
  watcher.watched = temporary
  check(watcher.watched?.area() == 10.0, "a weak interface across modules is live in scope")
}

function main(): int {
  scene := Scene {}
  check(focusArea(scene) == 0.0 && narrow(scene) == "none", "an unset cross-module nullable interface")
  scene.focus = Circle { radius: 2.0 }
  check(focusArea(scene) == 4.0 && narrow(scene) == "circle 2", "a class from another module fills the interface arm")
  boxed: Shape := Boxed<int> { value: 3 }
  scene.focus = boxed
  check(narrow(scene) == "shape 1", "a generic implementor instantiated in main is an interface arm")
  scene.extra = scene.focus
  check(scene.extra?.area() == 1.0, "a nullable interface widens into a union naming one implementor")

  // A nullable interface field round-trips through JSON across modules.
  snapshot := Snapshot { focus: Circle { radius: 1.25 } }
  restored := Snapshot.fromSerialValue(snapshot.toSerialObject())!
  check(restored.focus?.label() == "circle" && (restored.focus as Circle)!.radius == 1.25, "a cross-module nullable interface round-trips through JSON")
  check(Snapshot.fromSerialValue(Snapshot {}.toSerialObject())!.focus == none, "an absent interface round-trips as null")
  marked := Snapshot.fromSerialValue(Snapshot { mark: Marker { note: "m" } }.toSerialObject())!
  check((marked.mark as Marker)!.note == "m", "a cross-module object union decodes its class arm")
  tagged := Snapshot.fromSerialValue(Snapshot { mark: Circle { radius: 0.5 } }.toSerialObject())!
  check((tagged.mark as Circle)!.radius == 0.5, "a cross-module object union decodes an interface implementor")

  watcher := Watcher {}
  watch(watcher)
  check(watcher.watched?.area() == none, "a cross-module weak interface expires with its referent")
  println("interface unions modules ok")
  return 0
}
