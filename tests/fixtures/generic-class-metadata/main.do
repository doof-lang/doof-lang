// A ClassMetadata<T> passed through a generic call is substituted per caller,
// so each instantiation names the concrete class, never the caller's T.
class Point { x: int = 0 }
class Line { length: int = 0 }

function keep<V>(value: V): V => value
function describe<T: Reflectable>(): string => keep(T.metadata).name

function main(): int {
  if describe<Point>() != "Point" || describe<Line>() != "Line" { panic("metadata names") }
  println("metadata " + describe<Point>() + "," + describe<Line>())
  return 0
}
