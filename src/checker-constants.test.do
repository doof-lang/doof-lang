import { Assert } from "std/assert"
import { ConstDeclaration } from "./ast"
import { constantInt } from "./checker-constants"
import { parse } from "./parser"

function evaluate(expression: string): long | none {
  program := parse("const value = " + expression)
  declaration := program.statements[0] as ConstDeclaration else { panic("expected a const declaration") }
  return constantInt(declaration.value)
}

export function testConstantIntEvaluatesLiteralArithmetic(): none {
  Assert.equal(evaluate("42")!, 42L)
  Assert.equal(evaluate("-7")!, -7L)
  Assert.equal(evaluate("2 + 3 * 4")!, 14L)
  Assert.equal(evaluate("17 \\ 5 - 17 % 5")!, 1L)
  Assert.equal(evaluate("2147483646 + 1")!, 2147483647L)
  Assert.equal(evaluate("-2147483647 - 1")!, -2147483648L)
}

export function testConstantIntRejectsNonConstantsAndOverflow(): none {
  Assert.equal(evaluate("limit") == none, true)
  Assert.equal(evaluate("1 + limit") == none, true)
  Assert.equal(evaluate("top()") == none, true)
  Assert.equal(evaluate("1 \\ 0") == none, true)
  Assert.equal(evaluate("2147483647 + 1") == none, true)
  Assert.equal(evaluate("1 << 2") == none, true)
}
