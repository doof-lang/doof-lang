// Lowering of conditions with binding clauses (`if user := maybeUser { ... }`).
//
// Each binding clause evaluates its subject once into a temporary, tests every
// absent layer recorded by the checker's types, and declares the binding from
// the unwrapped temporary before later clauses run. A narrowing `as` subject
// that is a plain type test skips its Result: the clause binds the source by
// reference, tests it directly, and narrows it in place. Ordinary clauses
// become nested tests. The guarded body sits inside the innermost test, so a
// branch body never needs to be emitted twice.

import { AsExpression, BindingCondition, Block, Expression, IfExpression, IfStatement, WhileStatement } from "./ast"
import { conditionClauses, hasBindingClause } from "./ast-walk"
import { absenceErrorType, presentType } from "./absence-types"
import { ResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitCarrierConversion } from "./emitter-carrier-values"
import { emitAbsentError, emitAbsentTest, emitPresentValue, emitterAbsenceLayers } from "./emitter-absence"
import { emitExpression } from "./emitter-expr"
import { cppIdentifier } from "./emitter-names"
import { emitBlock, emitCondition, emitExtractedLocal } from "./emitter-stmt"
import { emitContextType, specializeEmitType } from "./emitter-types"
import { asTypeTest } from "./emitter-expr-ops"
import { sameType } from "./checker-types"

// How one binding clause evaluates, tests, and reads its subject.
class ClauseTest {
  // Declares the temporary, without indentation or newline.
  subject: string
  // True when the clause holds.
  present: string
  // The present value, of type `presentType`.
  value: string
  presentType: ResolvedType
}

function clauseTest(binding: BindingCondition, temporaryName: string, allowTypeTest: bool, context: EmitContext): ClauseTest {
  if allowTypeTest && as_ := binding.value as AsExpression && typeTest := asTypeTest(as_, temporaryName, context) {
    target := specializeEmitType(binding.value.resolvedType!, context)
    return ClauseTest {
      subject: "auto&& " + temporaryName + " = " + emitExpression(as_.expression, context) + ";",
      present: typeTest.test,
      value: typeTest.value,
      presentType: presentType(target),
    }
  }
  subjectType := specializeEmitType(binding.value.resolvedType!, context)
  layers := emitterAbsenceLayers(subjectType, context)
  return ClauseTest {
    subject: "auto " + temporaryName + " = " + emitExpression(binding.value, context) + ";",
    present: "!(" + emitAbsentTest(temporaryName, layers, context) + ")",
    value: emitPresentValue(temporaryName, layers, context),
    presentType: presentType(subjectType),
  }
}

class ConditionGuard {
  // Declarations and nested tests; the body goes at `bodyLevel`.
  opening: string
  closing: string
  bodyLevel: int
}

/** Whether an if statement needs binding-condition lowering. */
export function ifHasBindingClauses(statement: IfStatement): bool {
  if hasBindingClause(statement.condition) { return true }
  for branch of statement.elseIfs { if hasBindingClause(branch.condition) { return true } }
  return false
}

/**
 * Nested tests that reach `bodyLevel` only when every clause holds. The first
 * clause's temporary is declared at `level`, so callers open a block first.
 */
function emitConditionGuard(condition: Expression, level: int, context: EmitContext): ConditionGuard {
  let opening = ""
  let closing = ""
  let depth = level
  for clause of conditionClauses(condition) {
    ind := indent(depth)
    case clause {
      binding: BindingCondition -> {
        test := clauseTest(binding, context.temporary("_condition_value_"), true, context)
        opening = opening + ind + test.subject + "\n" + ind + "if (" + test.present + ") {\n"
        opening = opening + emitConditionBinding(binding, test, depth + 1, context)
      }
      _ -> { opening = opening + ind + "if (" + emitCondition(clause, context) + ") {\n" }
    }
    closing = ind + "}\n" + closing
    depth = depth + 1
  }
  return ConditionGuard { opening, closing, bodyLevel: depth }
}

/** Declares a binding clause's name from its tested temporary. */
function emitConditionBinding(binding: BindingCondition, test: ClauseTest, level: int, context: EmitContext): string {
  if binding.name == "_" { return "" }
  bindingType := binding.resolvedBindingType else { panic("Binding condition has no checked binding type: " + binding.name) }
  let value = test.value
  if !sameType(test.presentType, specializeEmitType(bindingType, context)) {
    value = emitCarrierConversion(value, test.presentType, bindingType, context)
  }
  return emitExtractedLocal(indent(level), binding.name, bindingType, value, true, true)
}

/** The body of a guarded branch, in its own block so body locals may reuse binding names. */
function emitGuardedBody(body: Block, level: int, context: EmitContext): string {
  return indent(level) + "{\n" + emitBlock(body, level + 1, context) + indent(level) + "}\n"
}

/** An if/else-if/else chain in which some condition has binding clauses. */
export function emitIfWithBindings(statement: IfStatement, level: int, context: EmitContext): string {
  let conditions: Expression[] = [statement.condition]
  let bodies: Block[] = [statement.body]
  for branch of statement.elseIfs {
    conditions.push(branch.condition)
    bodies.push(branch.body)
  }
  return emitBranch(statement, conditions, bodies, 0, level, context)
}

// Emits branch `index` and, on its failure path, every later branch and the
// else block. Each statement is emitted exactly once.
function emitBranch(statement: IfStatement, conditions: Expression[], bodies: Block[], index: int, level: int, context: EmitContext): string {
  ind := indent(level)
  inner := indent(level + 1)
  condition := conditions[index]
  last := index == conditions.length - 1
  if !hasBindingClause(condition) {
    let output = ind + "if (" + emitCondition(condition, context) + ") {\n" + emitBlock(bodies[index], level + 1, context) + ind + "}"
    rest := emitRest(statement, conditions, bodies, index, level + 1, context)
    if rest != "" { output = output + " else {\n" + rest + ind + "}" }
    return output + "\n"
  }
  clauses := conditionClauses(condition)
  if clauses.length == 1 {
    // A single clause owns its else path, which can read the tested value
    // for an `else error` capture.
    let binding: BindingCondition | none = none
    if clause := clauses[0] as BindingCondition { binding = clause }
    clause := binding else { panic("Binding condition clause expected") }
    temporaryName := context.temporary("_condition_value_")
    subjectType := specializeEmitType(clause.value.resolvedType!, context)
    layers := emitterAbsenceLayers(subjectType, context)
    failureName := statement.elseFailureName ?? "_"
    // A failure capture reads the Result's error, so it keeps the Result.
    test := clauseTest(clause, temporaryName, !last || failureName == "_", context)
    let output = ind + "{\n" + inner + test.subject + "\n"
    output = output + inner + "if (" + test.present + ") {\n"
    output = output + emitConditionBinding(clause, test, level + 2, context)
    output = output + emitGuardedBody(bodies[index], level + 2, context) + inner + "}"
    let capture = ""
    if last && failureName != "_" {
      errorType := absenceErrorType(subjectType) else { panic("Failure capture reached emission without a Result subject") }
      error := if layers.length == 1 then "doof::failure_error(" + temporaryName + ")" else emitAbsentError(temporaryName, layers, errorType, context)
      capture = indent(level + 2) + "const auto " + cppIdentifier(failureName) + " = " + error + ";\n"
    }
    rest := emitRest(statement, conditions, bodies, index, level + 2, context)
    if capture != "" || rest != "" { output = output + " else {\n" + capture + rest + inner + "}" }
    return output + "\n" + ind + "}\n"
  }
  // Several clauses can fail at different points; a flag records whether the
  // body ran so the failure path is emitted once.
  held := context.temporary("_condition_held_")
  guard := emitConditionGuard(condition, level + 1, context)
  let output = ind + "{\n" + inner + "bool " + held + " = false;\n" + guard.opening
  output = output + indent(guard.bodyLevel) + held + " = true;\n" + emitGuardedBody(bodies[index], guard.bodyLevel, context) + guard.closing
  rest := emitRest(statement, conditions, bodies, index, level + 2, context)
  if rest != "" { output = output + inner + "if (!" + held + ") {\n" + rest + inner + "}\n" }
  return output + ind + "}\n"
}

function emitRest(statement: IfStatement, conditions: Expression[], bodies: Block[], index: int, level: int, context: EmitContext): string {
  if index + 1 < conditions.length { return emitBranch(statement, conditions, bodies, index + 1, level, context) }
  if statement.else_ == none { return "" }
  return emitBlock(statement.else_!, level, context)
}

/**
 * The head of a `while` loop whose condition has binding clauses: each failed
 * clause leaves the loop as normal completion, so a loop `then` still runs.
 * Returns the statements that open the loop body, at `level`.
 */
export function emitWhileBindingHead(statement: WhileStatement, level: int, context: EmitContext): string {
  ind := indent(level)
  let output = ""
  for clause of conditionClauses(statement.condition) {
    case clause {
      binding: BindingCondition -> {
        test := clauseTest(binding, context.temporary("_condition_value_"), true, context)
        output = output + ind + test.subject + "\n" + ind + "if (!(" + test.present + ")) break;\n"
        output = output + emitConditionBinding(binding, test, level, context)
      }
      _ -> { output = output + ind + "if (!(" + emitCondition(clause, context) + ")) break;\n" }
    }
  }
  return output
}

/** An `if ... then ... else` expression whose condition has binding clauses. */
export function emitIfExpressionWithBindings(expression: IfExpression, resultType: ResolvedType, context: EmitContext): string {
  guard := emitConditionGuard(expression.condition, 1, context)
  thenValue := emitExpression(expression.then_, context, resultType)
  elseValue := emitExpression(expression.else_, context, resultType)
  return "[&]() -> " + emitContextType(resultType, context) + " {\n" + guard.opening +
    indent(guard.bodyLevel) + "return " + thenValue + ";\n" + guard.closing +
    "    return " + elseValue + ";\n}()"
}

function indent(level: int): string {
  return "    ".repeat(level)
}
