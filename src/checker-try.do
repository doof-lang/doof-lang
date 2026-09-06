// Statement-level Result propagation and success-payload binding checks.

import { Binding, ResolvedType, ResultResolvedType, Scope } from "./semantic"
import {
  ConstDeclaration, DestructuringStatement, Expression, ExpressionStatement,
  ImmutableBinding, LetDeclaration, ReadonlyDeclaration, SourceSpan, TryStatement,
  TypeAnnotation,
} from "./ast"
import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { checkDestructuring, declareUserBinding } from "./checker-statements"
import { applyDeepReadonly, typeName } from "./checker-types"
import { isAssignableWithInterfaces } from "./checker-interfaces"
import { resolveType } from "./checker-resolution"
import { optionalResolvedType } from "./checker-symbols"
import { typeError } from "./checker-common"
import { checkerSemanticSpan } from "./checker-validation"

export function checkTry(state: CheckerState, statement: TryStatement, scope: Scope): bool {
  let value: Expression | none = none
  let annotation: TypeAnnotation | none = none
  let name = ""
  let kind = ""
  case statement.binding {
    declaration: ConstDeclaration -> { value = declaration.value; annotation = declaration.type_; name = declaration.name; kind = "const" }
    declaration: ReadonlyDeclaration -> { value = declaration.value; annotation = declaration.type_; name = declaration.name; kind = "readonly" }
    binding: ImmutableBinding -> { value = binding.value; annotation = binding.type_; name = binding.name; kind = "immutable-binding" }
    declaration: LetDeclaration -> { value = declaration.value; annotation = declaration.type_; name = declaration.name; kind = "let" }
    expression: ExpressionStatement -> { value = expression.expression }
    destructuring: DestructuringStatement -> { value = destructuring.value }
  }
  if value == none { return true }
  resultValue := checkExpression(state, value!, scope, none)
  case resultValue {
    result: ResultResolvedType -> {
      validatePropagation(state, scope, result.errorType, statement.span)
      case statement.binding {
        _: ExpressionStatement -> { return true }
        _ -> {
          if result.valueType.kind == "none" { typeError(state, "Cannot bind a none success value; use bare 'try expr'", statement.span) }
        }
      }
      if kind != "" {
        let bindingType = if annotation == none then result.valueType else resolveType(state, annotation!, state.info!, scope)
        let valueType = result.valueType
        if kind == "readonly" || kind == "const" {
          bindingType = applyDeepReadonly(bindingType)
          valueType = applyDeepReadonly(valueType)
        }
        if !isAssignableWithInterfaces(state.result, valueType, bindingType) {
          typeError(state, "Cannot assign " + typeName(valueType) + " to " + typeName(bindingType), statement.span)
        }
        case statement.binding {
          declaration: ConstDeclaration -> { declaration.resolvedType = optionalResolvedType(bindingType) }
          declaration: ReadonlyDeclaration -> { declaration.resolvedType = optionalResolvedType(bindingType) }
          binding: ImmutableBinding -> { binding.resolvedType = optionalResolvedType(bindingType) }
          declaration: LetDeclaration -> { declaration.resolvedType = optionalResolvedType(bindingType) }
          _ -> { }
        }
        if name != "_" {
          declareUserBinding(state, scope, Binding {
            name, kind, type_: bindingType, mutable: kind == "let",
            span: checkerSemanticSpan(statement.span), module: state.info!.path,
          }, statement.span)
        }
      } else {
        case statement.binding {
          destructuring: DestructuringStatement -> { checkDestructuring(state, destructuring, scope, result.valueType) }
          _ -> { }
        }
      }
    }
    _ -> { typeError(state, "try requires a Result expression", value!.span) }
  }
  return resultValue.kind != "never"
}

// The first enclosing handler or function owns propagation. A catch or native
// script outside a nested function must never capture that function's errors.
function validatePropagation(state: CheckerState, scope: Scope, errorType: ResolvedType, span: SourceSpan): none {
  let current: Scope | none = scope
  while current != none {
    target := current!
    if target.capturesTryErrors { target.catchErrorTypes.push(errorType); return }
    if target.inValueYieldBlock {
      typeError(state, "'try' cannot be used inside a value-producing block; handle the Result outside the block", span)
      return
    }
    if target.returnType != none {
      case target.returnType! {
        result: ResultResolvedType -> {
          if !isAssignableWithInterfaces(state.result, errorType, result.errorType) {
            typeError(state, "Cannot propagate error " + typeName(errorType) + " from function returning " + typeName(result), span)
          }
          return
        }
        _ -> { break }
      }
    }
    if target.tryPanics { return }
    current = target.parent
  }
  typeError(state, "'try' requires a Result-returning function, a catch block, or native entry-script scope", span)
}
