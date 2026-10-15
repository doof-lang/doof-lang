// Conditional and pattern-based expression lowering.

import { Block, CaseExpression, CatchExpression, DotShorthand, Expression, IfExpression, YieldBlockExpression } from "./ast"
import { ResultResolvedType, SerialValueResolvedType, ResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitCasePattern, emitCaseSubjectValue } from "./emitter-case-pattern"
import { emitExpression } from "./emitter-expr"
import { cppIdentifier } from "./emitter-names"
import { emitBlock, emitCondition } from "./emitter-stmt"
import { exprModuleNamespaceFor, hasNoneMember } from "./emitter-expr-utils"
import { emitContextType, specializeEmitType, usesVariantRepresentation } from "./emitter-types"
import { sameType } from "./checker-types"
import { emitNoneLiteral } from "./emitter-expr-literals"

export function emitDotShorthand(expression: DotShorthand, context: EmitContext): string {
  if expression.resolvedShorthandOwnerKind != "enum" && expression.resolvedShorthandOwnerKind != "class" {
    panic("Cannot emit unresolved dot shorthand ." + expression.name)
  }
  let owner = expression.resolvedShorthandOwnerName
  if expression.resolvedShorthandOwnerNative {
    if expression.resolvedShorthandOwnerCppName != "" { owner = "::" + expression.resolvedShorthandOwnerCppName }
    else { owner = "::" + owner }
  } else if context.modulePath != "" && expression.resolvedShorthandOwnerModule != "" && expression.resolvedShorthandOwnerModule != context.modulePath {
    owner = "::" + exprModuleNamespaceFor(expression.resolvedShorthandOwnerModule, context.names) + "::" + owner
  }
  return owner + "::" + cppIdentifier(expression.name)
}

export function emitIfExpression(expression: IfExpression, context: EmitContext, expected: ResolvedType | none = none): string {
  // C++ determines the common type of `?:` operands before applying the
  // surrounding expression's conversion. Mixed union arms and nullable
  // branches therefore need their checked carrier before C++ joins them.
  // Result arms are distinct Success/Failure types with no common type.
  // An explicit lambda result type gives each branch the checked contextual
  // conversion independently.
  let contextualBranches = false
  if expression.resolvedType != none {
    resultType := specializeEmitType(expression.resolvedType!, context)
    contextualBranches = hasNoneMember(resultType) || usesVariantRepresentation(resultType)
    case resultType {
      _: SerialValueResolvedType -> { contextualBranches = true }
      _: ResultResolvedType -> { contextualBranches = true }
      _ -> { }
    }
  }
  if contextualBranches {
    let resultType = specializeEmitType(expression.resolvedType!, context)
    // Union equality ignores arm order, but C++ variant identity does not.
    // Preserve the contextual carrier when it denotes the same Doof type.
    if expected != none && sameType(resultType, specializeEmitType(expected!, context)) {
      resultType = specializeEmitType(expected!, context)
    }
    return "[&]() -> " + emitContextType(resultType, context) + " { if (" + emitCondition(expression.condition, context) + ") { return " + emitExpression(expression.then_, context, resultType) + "; } return " + emitExpression(expression.else_, context, resultType) + "; }()"
  }
  return "(" + emitExpression(expression.condition, context) + " ? " + emitExpression(expression.then_, context) + " : " + emitExpression(expression.else_, context) + ")"
}

export function emitYieldBlockExpression(expression: YieldBlockExpression, context: EmitContext, expected: ResolvedType | none): string {
  checkedResultType := if expected == none then expression.resolvedType else expected
  if checkedResultType == none { panic("Yield block has no resolved result type") }
  resultType := specializeEmitType(checkedResultType!, context)
  body := emitValueYieldBlock(expression.body, 1, resultType, false, context)
  return "[&]() -> " + emitContextType(resultType, context) + " {\n" + body + "}()"
}

export function emitCatchExpression(expression: CatchExpression, context: EmitContext): string {
  if expression.resolvedType == none { panic("Catch expression has no resolved result type") }
  resultType := specializeEmitType(expression.resolvedType!, context)
  resultCppType := emitContextType(resultType, context)
  catchVar := context.temporary("_catch_")
  previousCatchVar := context.catchVarName
  previousCatchType := context.catchResultType
  context.catchVarName = catchVar
  context.catchResultType = resultType
  body := emitBlock(expression.body, 2, context)
  context.catchVarName = previousCatchVar
  context.catchResultType = previousCatchType
  return "[&]() -> " + resultCppType + " {\n" +
    "    " + resultCppType + " " + catchVar + " = " + emitNoneLiteral(resultType, context) + ";\n" +
    "    do {\n" + body + "    } while (false);\n" +
    "    return " + catchVar + ";\n}()"
}

export function emitCaseExpression(expression: CaseExpression, context: EmitContext, expected: ResolvedType | none): string {
  let checkedResultType: ResolvedType | none = none
  if expected != none { checkedResultType = expected! }
  else if expression.resolvedType != none { checkedResultType = expression.resolvedType! }
  if checkedResultType == none { panic("Case expression has no resolved result type") }
  resultType := specializeEmitType(checkedResultType!, context)
  let output = "[&]() -> " + emitContextType(resultType, context) + " {\n"
  subjectResult := expression.resolvedSubjectType else { panic("Case expression has no checked subject type") }
  storageType := expression.subject.resolvedType else { panic("Case expression subject has no resolved type") }
  output = output + "    auto _case_subject = " + emitCaseSubjectValue(emitExpression(expression.subject, context), specializeEmitType(storageType, context), specializeEmitType(subjectResult, context), context) + ";\n"
  for arm of expression.arms {
    for pattern of arm.patterns {
      emitted := emitCasePattern(pattern, specializeEmitType(subjectResult, context), "_case_subject", context)
      output = output + "    if (" + emitted.condition + ") {\n"
      if emitted.binding != "" { output = output + "        " + emitted.binding }
      case arm.body {
        block: Block -> { output = output + emitValueYieldBlock(block, 2, resultType, false, context) }
        bodyExpression: Expression -> {
          emittedBody := emitExpression(bodyExpression, context, resultType)
          output = output + "        return " + emittedBody + ";\n"
        }
      }
      output = output + "    }\n"
    }
  }
  return output + "    throw std::runtime_error(\"non-exhaustive case expression\");\n}()"
}

/** Emits a block whose `yield` returns from the enclosing C++ lambda, restoring the outer yield target afterwards. */
export function emitValueYieldBlock(block: Block, level: int, valueType: ResolvedType | none, returnsVoid: bool, context: EmitContext): string {
  previousYieldState := context.inValueYieldBlock
  previousVoidState := context.valueYieldReturnsVoid
  previousYieldType := context.valueYieldType
  context.inValueYieldBlock = true
  context.valueYieldReturnsVoid = returnsVoid
  context.valueYieldType = valueType
  body := emitBlock(block, level, context)
  context.inValueYieldBlock = previousYieldState
  context.valueYieldReturnsVoid = previousVoidState
  context.valueYieldType = previousYieldType
  return body
}
