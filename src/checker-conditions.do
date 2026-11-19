// Checking of `if`, `else if`, `while`, and `if ... then` conditions.
//
// A condition is a chain of top-level `&&` clauses. A binding clause
// (`name := value`) is true when every absent layer of its value is present
// and binds that present value in later clauses and in the guarded body. The
// bindings live in a condition scope that the else path never sees.

import { BinaryExpression, BindingCondition, Expression, Identifier, IfStatement } from "./ast"
import { Binding, ResolvedType, Scope } from "./semantic"
import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { finish, requireBool, retainEditorScope, typeError } from "./checker-common"
import { declare } from "./checker-symbols"
import { resolveType } from "./checker-annotations"
import { isAssignableWithInterfaces } from "./checker-interfaces"
import { checkerSemanticSpan } from "./checker-validation"
import { absenceErrorType, canBeAbsent, presentType } from "./absence-types"
import { hasBindingClause } from "./ast-walk"
import { displayTypeName, neverType, primitive, unknownType } from "./checker-types"

export class CheckedCondition {
  let type_: ResolvedType
  // Holds the condition's bindings; the guarded body is checked inside it.
  scope: Scope
  boundNames: string[] = []
}

/** The binding clause when a condition is exactly one clause. */
export function singleBindingClause(condition: Expression): BindingCondition | none {
  case condition {
    binding: BindingCondition -> { return binding }
    _ -> { return none }
  }
}

export function checkCondition(state: CheckerState, condition: Expression, scope: Scope, expected: ResolvedType | none = none): CheckedCondition {
  if !hasBindingClause(condition) {
    conditionType := checkExpression(state, condition, scope, expected)
    requireBool(state, conditionType, condition.span)
    return CheckedCondition { type_: conditionType, scope }
  }
  conditionScope := Scope { parent: scope }
  retainEditorScope(state, conditionScope, condition.span)
  checked := CheckedCondition { type_: primitive("bool"), scope: conditionScope }
  checkClauses(state, condition, checked)
  return checked
}

function checkClauses(state: CheckerState, clause: Expression, checked: CheckedCondition): none {
  case clause {
    binding: BindingCondition -> { checkBindingClause(state, binding, checked) }
    binary: BinaryExpression -> {
      if binary.operator == "&&" && hasBindingClause(binary) {
        checkClauses(state, binary.left, checked)
        checkClauses(state, binary.right, checked)
        finish(state, binary, primitive("bool"))
        return
      }
      checkBoolClause(state, clause, checked)
    }
    _ -> { checkBoolClause(state, clause, checked) }
  }
}

function checkBoolClause(state: CheckerState, clause: Expression, checked: CheckedCondition): none {
  clauseType := checkExpression(state, clause, checked.scope, primitive("bool"))
  requireBool(state, clauseType, clause.span)
  if clauseType.kind == "never" { checked.type_ = neverType() }
}

function checkBindingClause(state: CheckerState, clause: BindingCondition, checked: CheckedCondition): none {
  finish(state, clause, primitive("bool"))
  valueType := checkExpression(state, clause.value, checked.scope, none)
  if valueType.kind == "never" { checked.type_ = neverType() }
  let bindingType: ResolvedType = unknownType()
  if valueType.kind != "unknown" && valueType.kind != "never" {
    if !canBeAbsent(valueType) {
      typeError(state, "Binding condition requires a nullable or Result value; \"${clauseSubjectName(clause)}\" has type \"${displayTypeName(valueType)}\"", clause.value.span)
    } else {
      present := presentType(valueType)
      // `_ := save()` tests success of a Result<none, E> without binding.
      if present.kind == "none" && clause.name != "_" {
        typeError(state, "Cannot bind a none success value; use a discard binding '_ := expr' to test for success", clause.value.span)
      } else {
        bindingType = present
      }
    }
  }
  if type_ := clause.type_ {
    annotated := resolveType(state, type_, state.info!, checked.scope)
    if bindingType.kind != "unknown" && annotated.kind != "unknown" && !isAssignableWithInterfaces(state.result, bindingType, annotated) {
      typeError(state, "Cannot assign ${displayTypeName(bindingType)} to ${displayTypeName(annotated)}", clause.span)
    }
    bindingType = annotated
  }
  clause.resolvedBindingType = bindingType
  if clause.name == "_" { return }
  if !declare(checked.scope, Binding { name: clause.name, kind: "immutable-binding", type_: bindingType, mutable: false, span: checkerSemanticSpan(clause.span), module: state.info!.path }) {
    typeError(state, "Binding '${clause.name}' is already declared in this condition", clause.span)
  }
  checked.boundNames.push(clause.name)
}

function clauseSubjectName(clause: BindingCondition): string {
  case clause.value {
    identifier: Identifier -> { return identifier.name }
    _ -> { return clause.name }
  }
}

/**
 * The scope for paths that run when a condition fails: the else branch and
 * later `else if` conditions. Naming a condition binding there gets a
 * specific diagnostic instead of "Unknown identifier".
 */
export function conditionElseScope(scope: Scope, boundNames: string[]): Scope {
  if boundNames.length == 0 { return scope }
  return Scope { parent: scope, unboundConditionNames: boundNames }
}

/** Declares the `else error` capture of an if statement in its else scope. */
export function declareElseFailure(state: CheckerState, statement: IfStatement, lastCondition: Expression, elseScope: Scope): none {
  failureName := statement.elseFailureName else { return }
  span := statement.else_?.span ?? statement.span
  let failureType = unknownType()
  clause := singleBindingClause(lastCondition)
  if clause == none {
    typeError(state, "Failure capture requires a condition that is a single Result binding clause", span)
  } else {
    subjectType := clause!.value.resolvedType ?? unknownType()
    if subjectType.kind != "unknown" {
      captured := absenceErrorType(subjectType)
      if captured == none {
        typeError(state, "Failure capture requires a Result binding clause; \"${displayTypeName(subjectType)}\" can only be absent as none", span)
      } else {
        failureType = captured!
      }
    }
  }
  // A rejected capture is still declared, as unknown, so uses do not cascade.
  if failureName == "_" { return }
  declare(elseScope, Binding { name: failureName, kind: "else-failure", type_: failureType, mutable: false, span: checkerSemanticSpan(span), module: state.info!.path })
}

/** The diagnostic for a condition binding named on a path where it is unbound, or "". */
export function unboundConditionBindingMessage(scope: Scope, name: string): string {
  let current: Scope | none = scope
  while current != none {
    if current!.unboundConditionNames.contains(name) {
      return "\"${name}\" is not in scope here; it is bound only when its condition holds"
    }
    current = current!.parent
  }
  return ""
}
