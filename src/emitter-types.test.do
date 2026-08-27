import { Assert } from "std/assert"
import { emitType } from "./emitter-types"
import { ClassType, PrimitiveType, Symbol } from "./semantic"

export function testRejectsUnloweredNonNativeGenericClassTypes(): none {
  symbol := Symbol { kind: "class", name: "Box", module: "/box.do", exported: true }
  unresolved := ClassType {
    name: "Box",
    symbol,
    typeArgs: [PrimitiveType { name: "int" }],
  }

  result := catchPanic(=> emitType(unresolved, "/main.do"))
  case result {
    failure: Failure<string> -> {
      Assert.stringContains(failure.error, "before monomorphization: /box.do::Box")
    }
    _ -> { panic("expected unlowered non-native generic type emission to panic") }
  }
}

export function testKeepsNativeGenericClassTypesAtCppBoundary(): none {
  symbol := Symbol {
    kind: "class",
    name: "Box",
    module: "/native.do",
    exported: true,
    native_: true,
    nativeCppName: "native::Box",
  }
  native := ClassType {
    name: "Box",
    symbol,
    typeArgs: [PrimitiveType { name: "int" }],
  }

  Assert.equal(emitType(native, "/main.do"), "std::shared_ptr<::native::Box<int32_t>>")
}
