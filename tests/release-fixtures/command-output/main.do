import function nativeValue(): int from "native.hpp" as nativeValue

function main(): void {
  println("program-output " + string(nativeValue()))
}
