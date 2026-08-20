import { Assert } from "std/assert"

import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { hasErrorDiagnostics } from "./diagnostics"
import { buildInstantiationPlan } from "./emitter-monomorphize"
import { planWorldview } from "./emitter-worldview"
import { SourceFile } from "./semantic"

export function testPlansDenseRepeatedForeignUsesOnceInDeclarationOrder(): none {
  sources := [
    SourceFile {
      path: "/main.do",
      source: "import { makePair } from \"./factory\"\nfunction main(): int { first := makePair()\nsecond := makePair()\nreturn first.left.value + second.right.value }",
    },
    SourceFile {
      path: "/factory.do",
      source: "import { Left, Right } from \"./types\"\nexport class Pair { left: Left\nright: Right }\nexport function makePair(): Pair => Pair { left: Left { value: 1 }, right: Right { value: 2 } }",
    },
    SourceFile {
      path: "/types.do",
      source: "export class Unused { value: int }\nexport class Left { value: int }\nexport class Right { value: int }",
    },
  ]
  analysis := createAnalyzer(sources).analyze("/main.do")
  checked := createChecker(analysis).check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)

  plan := planWorldview(analysis, "/main.do")
  Assert.equal(plan.modules.length, 3)
  Assert.equal(plan.modules[0].path, "/types.do")
  Assert.equal(plan.modules[0].program.statements.length, 2)
  Assert.equal(plan.modules[1].path, "/factory.do")
  Assert.equal(plan.modules[1].program.statements.length, 2)
  Assert.equal(plan.modules[2].path, "/main.do")
  Assert.equal(plan.modules[2].program.statements.length, 2)
}

export function testCollectsGenericInterfaceKeysDuringPrimaryWorldviewTraversal(): none {
  source := "interface Reader<T> { read(): T }\nclass IntReader { value: int\nread(): int => value }\nfunction makeReader(): Reader<int> => IntReader { value: 7 }\nfunction main(): int { reader := makeReader()\nreturn reader.read() }"
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  checked := createChecker(analysis).check("/main.do")
  Assert.equal(hasErrorDiagnostics(checked.diagnostics), false)

  plan := planWorldview(analysis, "/main.do", buildInstantiationPlan(analysis))
  Assert.equal(plan.interfaceKeys.length, 1)
}
