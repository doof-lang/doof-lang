import { Shape, Tagged } from "./shapes"
import { Circle } from "./circle"
import { Marker } from "./marker"

export class Scene {
  let focus: Shape | none = none
  let extra: Shape | Circle | none = none
}

export class Snapshot {
  focus: Tagged | none = none
  mark: Tagged | Marker | none = none
}

export class Watcher {
  let watched: weak Shape | none = none
}

export function focusArea(scene: Scene): double => scene.focus?.area() ?? 0.0

export function narrow(scene: Scene): string {
  return case scene.focus {
    circle: Circle -> "circle " + string(circle.radius),
    shape: Shape -> "shape " + string(shape.area()),
    _ -> "none"
  }
}
