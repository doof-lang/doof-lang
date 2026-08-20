// Internal append-only text construction backed by the native runtime.

export import class StringBuilder from "doof_runtime.hpp" as doof::StringBuilder {
  isolated static constructor(): StringBuilder
  isolated append(value: string): none
  isolated appendLine(value: string = ""): none
  isolated length(): int
  isolated reserve(capacity: int): none
  isolated clear(): none
  isolated drainToString(): string
}
