import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

function chooseMixed(flag: bool, calls: int[]): int | string {
  calls[0] += 1
  return if flag then 7 else "seven"
}

struct ConditionalValue { value: int }

function chooseNullable(flag: bool): ConditionalValue | none => if flag then ConditionalValue { value: 9 } else none

export function testEmitterGapConditionalBranchesUseCheckedCarrier(): none {
  calls := [0]
  first := chooseMixed(true, calls)
  second := chooseMixed(false, calls)
  Assert.equal((first as int)!, 7)
  Assert.equal((second as string)!, "seven")
  Assert.equal(calls[0], 2)
  Assert.equal(chooseNullable(true)!.value, 9)
  Assert.isTrue(chooseNullable(false) == none)
  let evaluated = 0
  selected: int | string := if true then "selected" else (evaluated += 1)
  Assert.equal((selected as string)!, "selected")
  Assert.equal(evaluated, 0)
}

export function testEmitterGapConditionalIncompatibleReturnRemainsDiagnostic(): none {
  result := compile([SourceFile {
    path: "/conditional.do",
    source: "function choose(flag: bool): int => if flag then 1 else \"two\"",
  }], "/conditional.do")
  Assert.isTrue(result.diagnostics.length > 0)
  Assert.stringContains(result.diagnostics[0].message, "Cannot return int | string from function returning int")
  Assert.isTrue(result.emission == none)
}
