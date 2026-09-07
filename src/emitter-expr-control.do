// Conditional and pattern-based expression lowering.

import { Block, CaseExpression, CatchExpression, DotShorthand, Expression, IfExpression, RangePattern, TypePattern, ValuePattern, WildcardPattern, YieldBlockExpression } from "./ast"
import { JsonValueResolvedType, ResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitCaseTypePattern } from "./emitter-case-pattern"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { emitBlock, emitCondition } from "./emitter-stmt"
import { exprModuleNamespaceFor, hasNoneMember } from "./emitter-expr-utils"
import { emitContextType, emitType, specializeEmitType, usesVariantRepresentation } from "./emitter-types"
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
  // An explicit lambda result type gives each branch the checked contextual
  // conversion independently.
  let contextualBranches = false
  if expression.resolvedType != none {
    resultType := specializeEmitType(expression.resolvedType!, context)
    contextualBranches = hasNoneMember(resultType) || usesVariantRepresentation(resultType)
    case resultType {
      _: JsonValueResolvedType -> { contextualBranches = true }
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
  resultType := if expected == none then expression.resolvedType else expected
  if resultType == none { panic("Yield block has no resolved result type") }
  previousYieldType := context.valueYieldType
  previousYieldVoid := context.valueYieldReturnsVoid
  previousYieldState := context.inValueYieldBlock
  context.inValueYieldBlock = true
  context.valueYieldReturnsVoid = false
  context.valueYieldType = resultType
  body := emitBlock(expression.body, 1, context)
  context.inValueYieldBlock = previousYieldState
  context.valueYieldType = previousYieldType
  context.valueYieldReturnsVoid = previousYieldVoid
  return "[&]() -> " + emitType(resultType!, context.modulePath, context.names) + " {\n" + body + "}()"
}

export function emitCatchExpression(expression: CatchExpression, context: EmitContext): string {
  if expression.resolvedType == none { panic("Catch expression has no resolved result type") }
  resultType := specializeEmitType(expression.resolvedType!, context)
  resultCppType := emitContextType(resultType, context)
  context.tryCounter = context.tryCounter + 1
  catchVar := "_catch_" + string(context.tryCounter)
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
  let resultType: ResolvedType | none = none
  if expected != none { resultType = expected! }
  else if expression.resolvedType != none { resultType = expression.resolvedType! }
  if resultType == none { panic("Case expression has no resolved result type") }
  let output = "[&]() -> " + emitType(resultType!, context.modulePath, context.names) + " {\n"
  output = output + "    auto _case_subject = " + emitExpression(expression.subject, context) + ";\n"
  subjectResult := caseSubjectResultType(expression.subject)
  for arm of expression.arms {
    for pattern of arm.patterns {
      let condition = "true"
      let binding = ""
      case pattern {
        type_: TypePattern -> {
          bindingName := if type_.name == "_" then "" else cppIdentifier(type_.name)
          emitted := emitCaseTypePattern(type_, specializeEmitType(subjectResult, context), "_case_subject", bindingName, context.modulePath, context.names)
          condition = emitted.condition
          binding = emitted.binding
        }
        value: ValuePattern -> { condition = "_case_subject == " + emitExpression(value.value, context) }
        range: RangePattern -> { condition = emitRangePatternCondition(range, "_case_subject", context) }
        _: WildcardPattern -> { condition = "true" }
      }
      output = output + "    if (" + condition + ") {\n"
      if binding != "" { output = output + "        " + binding }
      case arm.body {
        block: Block -> {
          previousYieldType := context.valueYieldType
          previousYieldVoid := context.valueYieldReturnsVoid
          previousYieldState := context.inValueYieldBlock
          context.inValueYieldBlock = true
          context.valueYieldReturnsVoid = false
          context.valueYieldType = resultType
          output = output + emitBlock(block, 2, context)
          context.inValueYieldBlock = previousYieldState
          context.valueYieldType = previousYieldType
          context.valueYieldReturnsVoid = previousYieldVoid
        }
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

function emitRangePatternCondition(pattern: RangePattern, subject: string, context: EmitContext): string {
  let condition = ""
  if pattern.start != none { condition = subject + " >= " + emitExpression(pattern.start!, context) }
  if pattern.end != none {
    operator := if pattern.inclusive then " <= " else " < "
    if condition != "" { condition = condition + " && " }
    condition = condition + subject + operator + emitExpression(pattern.end!, context)
  }
  return condition
}

function caseSubjectResultType(subject: Expression): ResolvedType {
  if subject.resolvedType == none {
    panic("Case expression subject has no resolved type")
  }
  return subject.resolvedType!
}
