// Conditional and pattern-based expression lowering.

import { Block, CaseExpression, CatchExpression, DotShorthand, Expression, IfExpression, RangePattern, TypePattern, ValuePattern, WildcardPattern, YieldBlockExpression } from "./ast"
import { JsonValueResolvedType, ResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitCaseTypePattern } from "./emitter-case-pattern"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { emitBlock } from "./emitter-stmt"
import { exprModuleNamespaceFor, hasNoneMember } from "./emitter-expr-utils"
import { emitContextType, emitType, specializeEmitType, usesVariantRepresentation } from "./emitter-types"
import { sameType } from "./checker-types"

export function emitDotShorthand(expression: DotShorthand, context: EmitContext): string {
  if expression.resolvedShorthandOwnerKind != "enum" && expression.resolvedShorthandOwnerKind != "class" {
    panic("Cannot emit unresolved dot shorthand ." + expression.name)
  }
  let owner = expression.resolvedShorthandOwnerName
  if expression.resolvedShorthandOwnerNative {
    if expression.resolvedShorthandOwnerCppName != "" { owner = "::" + expression.resolvedShorthandOwnerCppName }
    else { owner = "::" + owner }
  } else if context.modulePath != "" && expression.resolvedShorthandOwnerModule != "" && expression.resolvedShorthandOwnerModule != context.modulePath {
    owner = "::" + exprModuleNamespaceFor(expression.resolvedShorthandOwnerModule) + "::" + owner
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
    return "[&]() -> " + emitContextType(resultType, context) + " { if (" + emitExpression(expression.condition, context) + ") { return " + emitExpression(expression.then_, context, resultType) + "; } return " + emitExpression(expression.else_, context, resultType) + "; }()"
  }
  return "(" + emitExpression(expression.condition, context) + " ? " + emitExpression(expression.then_, context) + " : " + emitExpression(expression.else_, context) + ")"
}

export function emitYieldBlockExpression(expression: YieldBlockExpression, context: EmitContext, expected: ResolvedType | none): string {
  resultType := if expected == none then expression.resolvedType else expected
  if resultType == none { panic("Yield block has no resolved result type") }
  previousYieldState := context.inValueYieldBlock
  context.inValueYieldBlock = true
  body := emitBlock(expression.body, 1, context)
  context.inValueYieldBlock = previousYieldState
  return "[&]() -> " + emitType(resultType!, context.modulePath) + " {\n" + body + "}()"
}

export function emitCatchExpression(expression: CatchExpression, context: EmitContext): string {
  if expression.resolvedType == none { panic("Catch expression has no resolved result type") }
  resultType := expression.resolvedType!
  resultCppType := emitType(resultType, context.modulePath)
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
    "    " + resultCppType + " " + catchVar + " = " + catchNullValue(resultCppType) + ";\n" +
    "    do {\n" + body + "    } while (false);\n" +
    "    return " + catchVar + ";\n}()"
}

function catchNullValue(resultCppType: string): string {
  if resultCppType.startsWith("std::optional<") { return "std::nullopt" }
  if resultCppType.startsWith("std::shared_ptr<") || resultCppType.startsWith("std::weak_ptr<") { return "nullptr" }
  return "std::monostate{}"
}

export function emitCaseExpression(expression: CaseExpression, context: EmitContext, expected: ResolvedType | none): string {
  let resultType: ResolvedType | none = none
  if expected != none { resultType = expected! }
  else if expression.resolvedType != none { resultType = expression.resolvedType! }
  if resultType == none { panic("Case expression has no resolved result type") }
  let output = "[&]() -> " + emitType(resultType!, context.modulePath) + " {\n"
  output = output + "    auto _case_subject = " + emitExpression(expression.subject, context) + ";\n"
  subjectResult := caseSubjectResultType(expression.subject)
  for arm of expression.arms {
    for pattern of arm.patterns {
      let condition = "true"
      let binding = ""
      case pattern {
        type_: TypePattern -> {
          bindingName := if type_.name == "_" then "" else cppIdentifier(type_.name)
          emitted := emitCaseTypePattern(type_, specializeEmitType(subjectResult, context), "_case_subject", bindingName, context.modulePath)
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
          previousYieldState := context.inValueYieldBlock
          context.inValueYieldBlock = true
          output = output + emitBlock(block, 2, context)
          context.inValueYieldBlock = previousYieldState
        }
        bodyExpression: Expression -> {
          emittedBody := emitExpression(bodyExpression, context, resultType)
          if resultType!.kind == "none" {
            output = output + "        " + emittedBody + ";\n        return std::monostate{};\n"
          } else {
            output = output + "        return " + emittedBody + ";\n"
          }
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
