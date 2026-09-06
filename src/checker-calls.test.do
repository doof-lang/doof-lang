import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { compile } from "./compiler"
import { CheckResult, SourceFile } from "./semantic"

function checked(source: string): CheckResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  return createChecker(analysis, "/main.do").check("/main.do")
}

export function testResultConstructorShorthandPayloads(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "function load(): Result<int, string> => Success { value: 1 }\n" +
    "function widened(): Result<long, string> { try let value: long = load()\nreturn Success { value } }\n" +
    "function failed(error: string): Result<int, string> => Failure { error }",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  inferred := checked("function inferred(): none { value := 1\nsuccess := Success { value }\nerror := \"bad\"\nfailure := Failure { error } }")
  Assert.equal(inferred.diagnostics.length, 0)
}

export function testResultConstructorShorthandDiagnostics(): none {
  for source of [
    "function success(): Result<int, string> => Success { value }",
    "function failure(): Result<int, string> => Failure { error }",
  ] {
    result := checked(source)
    Assert.equal(result.diagnostics.length, 1)
    Assert.stringContains(result.diagnostics[0].message, "Unknown shorthand property")
  }
  for source of [
    "function success(value: string): Result<int, string> => Success { value }",
    "function failure(error: int): Result<int, string> => Failure { error }",
  ] {
    result := checked(source)
    Assert.equal(result.diagnostics.length, 1)
    Assert.stringContains(result.diagnostics[0].message, "Cannot assign")
  }
}

export function testInterfaceBoundCallableField(): none {
  result := checked("interface Handler { invoke: (value: int): int }\nclass Adder { invoke: (value: int): int }\nfunction call<T: Handler>(handler: T): int => handler.invoke{value: 1}\nfunction main(): int => call(Adder { invoke: (value: int): int => value + 1 })")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testInterfaceBoundNamedDefaultCall(): none {
  result := checked("interface Reader<V> { read(value: int = 1): int }\nclass IntReader { read(value: int = 1): int => value }\nfunction readOne<T: Reader<int>>(reader: T): int => reader.read{value: 2}\nfunction readDefault<T: Reader<int>>(reader: T): int => reader.read()")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testInterfaceBoundUnconstrainedForwarding(): none {
  result := checked("interface Reader<V> { read(): V }\nclass IntReader { read(): int => 7 }\nfunction keep<T: Reader<int>>(value: T): T => value\nfunction invalid<U>(value: U): U => keep(value)")
  let found = false
  for diagnostic of result.diagnostics { if diagnostic.message.contains("does not satisfy constraint") { found = true } }
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.isTrue(found)
}


export function testInterfaceBoundMethodOwnerSubstitution(): none {
  result := checked("interface Reader<V> { read(): V }\nclass R { read(): int => 1 }\nclass Consumer<V> { value: V\nconsume<T: Reader<V>>(reader: T): V => reader.read() }\nfunction main(): int => Consumer(0).consume(R {})")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testUppercaseNamedCallReturnsView(): none {
  result := checked("class View { prepareLayout(): none {}\nlayoutNode(): int => 7 }\nfunction GroupBox(title: string, gap: int = 8): View => View {}\nfunction main(): int { box := GroupBox{title: \"Account\"}\nbox.prepareLayout()\nreturn box.layoutNode() }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testUppercaseNamedCallDiagnostics(): none {
  result := checked("function GroupBox(title: string): int => 1\nfunction main(): none { GroupBox{unknown: 1} }")
  let unknown = false
  let missing = false
  for diagnostic of result.diagnostics {
    if diagnostic.message.contains("Unknown named argument 'unknown'") { unknown = true }
    if diagnostic.message.contains("Missing required argument 'title'") { missing = true }
  }
  Assert.isTrue(unknown)
  Assert.isTrue(missing)
}

export function testUppercaseNamedCallGenericAndEmpty(): none {
  result := checked("class View { layoutNode(): int => 7 }\nfunction GroupBox(): View => View {}\nfunction Identity<T>(value: T): T => value\nfunction main(): int { box := Identity<View>{value: GroupBox{}}\nreturn box.layoutNode() }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testUppercaseNamedCallImportedReturn(): none {
  analysis := createAnalyzer([
    SourceFile { path: "/main.do", source: "import { GroupBox } from \"./factory\"\nfunction main(): int { box := GroupBox{title: \"Account\"}\nreturn box.layoutNode() }" },
    SourceFile { path: "/factory.do", source: "export class View { layoutNode(): int => 7 }\nexport function GroupBox(title: string): View => View {}" },
  ]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  result := createChecker(analysis, "/main.do").check("/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}

export function testCheckerConsolidationWeakDefaultsKeepDeclaration(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "class C { read(first: int = 9, second: int = 9): int => first + second }\n" +
    "function call(value: weak C): int => value!.read{second: 4}",
  }], "/main.do")
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
  Assert.stringContains(result.emission!.modules[0].source, "->read(9, 4)")
}

export function testCheckerConsolidationGenericFactorySyntaxParity(): none {
  for construction of ["Box<int>(3)", "Box<int> { value: 3 }"] {
    result := compile([SourceFile { path: "/main.do", source:
      "class Box<T> { value: T\nstatic constructor(value: T): Box<T> => Box<T> { value } }\n" +
      "function make(): Box<int> => " + construction,
    }], "/main.do")
    for diagnostic of result.diagnostics { println(diagnostic.message) }
    Assert.equal(result.diagnostics.length, 0)
    Assert.isTrue(result.emission != none)
    Assert.stringContains(result.emission!.modules[0].source, "Box__int::constructor(3)")
  }
}

export function testSecondConsolidationRecursiveGenericAliasSignature(): none {
  result := compile([SourceFile { path: "/main.do", source:
    "type Items<T> = readonly T[]\nfunction first(values: Items<int>, again: bool): int { if again { return second(values) }\nreturn values[0] }\nfunction second(values: Items<int>): int => first(values, false)",
  }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  Assert.isTrue(result.emission != none)
}
