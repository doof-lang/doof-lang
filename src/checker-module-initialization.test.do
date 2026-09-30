import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

export function testPositionalClassLiteralsFollowModuleInitializerRules(): none {
  valid := compile([SourceFile { path: "/main.do", source:
    "class Point { x, y: float }\nstruct Vec { x: int\ny: int = 0 }\nreadonly ORIGIN: Point = (0.0, 0.0)\nreadonly AXIS: Vec = (1, 0)",
  }], "/main.do")
  for diagnostic of valid.diagnostics { println(diagnostic.message) }
  Assert.equal(valid.diagnostics.length, 0)
  // Custom constructors execute code, so they are not construction-only.
  factory := compile([SourceFile { path: "/main.do", source:
    "class Counter { count: int\nstatic constructor(initial: int, step: int): Counter { return Counter { count: initial + step } } }\nreadonly START: Counter = (1, 2)",
  }], "/main.do")
  Assert.equal(factory.diagnostics.length, 1)
  Assert.stringContains(factory.diagnostics[0].message, "Module initializer for 'START' must be a literal tree")
}
