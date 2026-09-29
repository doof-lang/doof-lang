import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { CheckResult, SourceFile } from "./semantic"

function checked(source: string): CheckResult {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  return createChecker(analysis, "/main.do").check("/main.do")
}

export function testStructsCannotContainThemselvesByValue(): none {
  direct := checked("struct Node { value: int\nnext: Node | none }")
  Assert.equal(direct.diagnostics.length, 1)
  Assert.equal(direct.diagnostics[0].message, "Struct \"Node\" cannot contain itself by value through field \"next\"; use a class or a collection to add indirection")
  indirect := checked("struct A { b: Tuple<int, B> | none }\nstruct B { a: A }")
  Assert.equal(indirect.diagnostics.length, 2)
}

export function testStructIndirectionThroughReferencesIsAllowed(): none {
  result := checked("struct Tree { children: Tree[]\nparent: Holder | none }\nclass Holder { tree: Tree }\nstruct Pair { left: Leaf\nright: Leaf }\nstruct Leaf { value: int }")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
}
