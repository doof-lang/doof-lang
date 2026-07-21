// Nullable alias assignment slice for the parser's Expression/Statement locals.

class ExpressionLeft {
  value: int
}

class ExpressionRight {
  value: int
}

type Expression = ExpressionLeft | ExpressionRight

class StatementLeft {
  value: int
}

class StatementRight {
  value: int
}

type Statement = StatementLeft | StatementRight

class Holder {
  expression: Expression | none
  statement: Statement | none
}

function makeExpression(): Expression => ExpressionLeft { value: 1 }
function makeStatement(): Statement => StatementLeft { value: 2 }

function makeHolder(): Holder {
  let expression: Expression | none = none
  expression = makeExpression()
  let statement: Statement | none = none
  statement = makeStatement()
  return Holder { expression, statement }
}

function main(): int => 0
