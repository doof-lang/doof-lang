import { Assert } from "std/assert"
import { AstLocation, Block, BoolLiteral, CatchExpression, Expression, SourceSpan } from "./ast"
import { primitive, typeName } from "./checker-types"

export function testCheckerReviewMutableExpressionDecorations(): none {
  location := AstLocation { line: 1, column: 1, offset: 0 }
  span := SourceSpan { start: location, end: location }
  literal := BoolLiteral { kind: "bool-literal", value: true, span }
  caught := CatchExpression { body: Block { kind: "block", statements: [], span }, span }
  expressions: Expression[] := [literal, caught]
  for expression of expressions { expression.resolvedType = primitive("bool") }
  Assert.equal(typeName(literal.resolvedType!), "bool")
  Assert.equal(typeName(caught.resolvedType!), "bool")
}
