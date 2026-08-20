// Internal append-only text construction backed by the native runtime.

export import class StringBuilder from "doof_runtime.hpp" as doof::StringBuilder {
  static constructor(): StringBuilder
  append(value: string): none
  drainToString(): string
}
