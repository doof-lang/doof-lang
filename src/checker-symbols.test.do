import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { ClassDeclaration } from "./ast"
import { SourceFile, FunctionType } from "./semantic"
import { builtinCallable, isBuiltinCallable, methodSignature } from "./checker-symbols"
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

export function testRuntimeMetricBuiltinsExposeDocumentedSignatures(): none {
  Assert.isTrue(isBuiltinCallable("metricsIncrement"))
  Assert.isTrue(isBuiltinCallable("metricsSnapshotPrometheus"))
  increment := builtinCallable("metricsIncrement") as FunctionType else { panic("expected metricsIncrement function") }
  Assert.equal(increment.params.length, 2)
  Assert.equal(increment.params[0].name, "name")
  Assert.equal(typeName(increment.params[0].type_), "string")
  Assert.equal(increment.params[1].name, "value")
  Assert.equal(typeName(increment.params[1].type_), "long")
  Assert.equal(typeName(increment.returnType), "none")
  snapshot := builtinCallable("metricsSnapshotPrometheus") as FunctionType else { panic("expected metricsSnapshotPrometheus function") }
  Assert.equal(snapshot.params.length, 0)
  Assert.equal(typeName(snapshot.returnType), "string")
}
