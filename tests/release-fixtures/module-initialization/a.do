readonly value = "ready"

export class Globals {
  static suffix = "!"
}

export struct Vec3 {
  x: double
  y: double
  z: double

  static zero = Vec3 { x: 0.0, y: 0.0, z: 0.0 }
}

export struct Defaults {
  value: int = 0

  static zero = Defaults {}
}

export function getValue(): string => value
