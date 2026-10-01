const EPSILON = 1e-10
function main(): int {
  avogadro := 6.02E23
  small: float := 2.5e-3f
  big := 1_000e3
  if 1e3 != 1000.0 || big != 1000000.0 { return 1 }
  if avogadro < 6.0e23 || avogadro > 6.1e23 { return 2 }
  if EPSILON <= 0.0 || EPSILON >= 1e-9 { return 3 }
  if small < 0.0024f || small > 0.0026f { return 4 }
  return 0
}
