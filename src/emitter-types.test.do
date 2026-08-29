import { Assert } from "std/assert"
import { EmitContext } from "./emitter-context"
import { emitContextType, emitType } from "./emitter-types"
import { ClassType, InterfaceType, PrimitiveType, Symbol } from "./semantic"

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

export function testRequiresRegisteredConcreteClassNames(): none {
  symbol := Symbol { kind: "class", name: "Box", module: "/box.do", exported: true }
  unresolved := ClassType { name: "Box", symbol, typeArgs: [PrimitiveType { name: "int" }] }

  result := catchPanic(=> emitContextType(unresolved, EmitContext { modulePath: "/main.do" }))
  case result {
    failure: Failure<string> -> { Assert.stringContains(failure.error, "Missing concrete class instantiation") }
    _ -> { panic("expected a missing concrete class registration to panic") }
  }
}

export function testRequiresRegisteredConcreteInterfaceNames(): none {
  symbol := Symbol { kind: "interface", name: "Reader", module: "/reader.do", exported: true }
  unresolved := InterfaceType { name: "Reader", symbol, typeArgs: [PrimitiveType { name: "string" }] }

  result := catchPanic(=> emitContextType(unresolved, EmitContext { modulePath: "/main.do" }))
  case result {
    failure: Failure<string> -> { Assert.stringContains(failure.error, "Missing concrete interface instantiation") }
    _ -> { panic("expected a missing concrete interface registration to panic") }
  }
}
