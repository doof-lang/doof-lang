import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { ClassDeclaration } from "./ast"
import { SourceFile, FunctionType } from "./semantic"
import { methodSignature } from "./checker-symbols"
import { typeName } from "./checker-types"

export function testSecondConsolidationOwnerAndMethodSignatureParameters(): none {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source: "class Box<T> { pair<U>(first: T, second: U): T => first }" }]).analyze("/main.do")
  module := analysis.modules[0]
  case module.program.statements[0] {
    class_: ClassDeclaration -> {
      signature := methodSignature(class_.methods[0], module, analysis, class_.typeParams)
      case signature {
        fn: FunctionType -> {
          Assert.equal(typeName(fn.params[0].type_), "T")
          Assert.equal(typeName(fn.params[1].type_), "U")
          Assert.equal(typeName(fn.returnType), "T")
          Assert.equal(fn.typeParams.length, 1)
          Assert.equal(fn.typeParams[0], "U")
        }
        _ -> { panic("expected signature") }
      }
    }
    _ -> { panic("expected class") }
  }
}
