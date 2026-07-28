import { getValue, Defaults, Globals, Vec3 } from "./a"

export readonly primes = [2, 3, 5, 7]

export function snapshot(): string {
  return getValue() + Globals.suffix + ":" + string(primes.length) + ":" +
    string(Vec3.zero.x) + ":" + string(Defaults.zero.value)
}
