import { Assert } from "std/assert"
import { AnalysisResult, createAnalyzer } from "./analyzer"
import { ClassDeclaration, ClassField } from "./ast"
import { SourceFile, FunctionType } from "./semantic"
import { builtinCallable, classFieldBinding, classFieldMode, fieldDisplayName, isBuiltinCallable, methodSignature } from "./checker-symbols"
import { primitive, typeName } from "./checker-types"

// Fails on parse or analysis diagnostics so a malformed fixture cannot pass
// unnoticed through a test that only inspects checker output.
function analyzed(source: string): AnalysisResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  return analysis
}

export function testSecondConsolidationOwnerAndMethodSignatureParameters(): none {
  analysis := analyzed("class Box<T> { pair<U>(first: T, second: U): T => first }")
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

function firstClass(analysis: AnalysisResult): ClassDeclaration {
  class_ := analysis.modules[0].program.statements[0] as ClassDeclaration else { panic("expected class") }
  return class_
}

export function testClassFieldModeFollowsDeclarationKeyword(): none {
  class_ := firstClass(analyzed("class Point { let x: int\nreadonly y: int\nz: int\nkind: \"point\" }"))
  Assert.equal(classFieldMode(class_.fields[0]), "let")
  Assert.equal(classFieldMode(class_.fields[1]), "readonly")
  Assert.equal(classFieldMode(class_.fields[2]), "implicit")
  Assert.equal(classFieldMode(class_.fields[3]), "const")
}

export function testClassFieldBindingRecordsOwnerAndMutability(): none {
  analysis := analyzed("class Point { let x: int\nz: int }")
  class_ := firstClass(analysis)
  mutable := classFieldBinding(class_.fields[0], "x", class_, primitive("int"), "/main.do")
  Assert.equal(mutable.kind, "field")
  Assert.equal(mutable.name, "x")
  Assert.isTrue(mutable.mutable)
  Assert.equal(mutable.fieldMode, "let")
  Assert.equal(mutable.fieldOwner, "Point")
  Assert.equal(mutable.module, "/main.do")
  Assert.isTrue(mutable.symbol == none)
  Assert.equal(mutable.span.start.line, class_.fields[0].span.start.line)
  symbol := analysis.modules[0].symbols[0]
  implicit := classFieldBinding(class_.fields[1], "z", class_, primitive("int"), "/other.do", symbol)
  Assert.isFalse(implicit.mutable)
  Assert.equal(implicit.fieldMode, "implicit")
  Assert.equal(implicit.module, "/other.do")
  Assert.isTrue(implicit.symbol != none)
}

export function testFieldDisplayNameFallsBackForRecoveredFields(): none {
  class_ := firstClass(analyzed("class Point { x: int }"))
  Assert.equal(fieldDisplayName(class_.fields[0]), "x")
  nameless := ClassField { kind: "class-field", names: [], type_: none, defaultValue: none, static_: false, readonly_: false, private_: false, span: class_.span }
  Assert.equal(fieldDisplayName(nameless), "<field>")
}
