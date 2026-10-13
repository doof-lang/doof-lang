// Case expressions, case-pattern binding, and exhaustiveness.

import { Block, BoolLiteral, CaseExpression, CasePattern, DotShorthand, EnumDeclaration, Expression, IntLiteral, LongLiteral, MemberExpression, NamedType, NoneLiteral, RangePattern, SourceSpan, TypeAnnotation, TypePattern, UnaryExpression, ValuePattern, WildcardPattern } from "./ast"
import { typeError } from "./checker-common"
import { checkExpression } from "./checker-expressions"
import { pathType } from "./checker-inference"
import { isIntegerOperand } from "./checker-numeric"
import { typesOverlap } from "./checker-operators"
import { resolveType } from "./checker-resolution"
import { CheckerState } from "./checker-state"
import { checkBlock } from "./checker-statements"
import { casePatternName, declarationFor, declare, optionalResolvedType } from "./checker-symbols"
import { failureType, neverType, resultType, sameType, successType, typeName, unknownType, weakReferenceErrorType } from "./checker-types"
import { checkerSemanticSpan } from "./checker-validation"
import type { Symbol } from "./semantic"
import { Binding, ClassType, EnumType, FailureResolvedType, PrimitiveType, ResolvedType, ResultResolvedType, Scope, SuccessResolvedType, UnionResolvedType, WeakResolvedType } from "./semantic"

export function checkCaseExpression(state: CheckerState, expression: CaseExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  subjectType := checkedCaseSubjectType(checkExpression(state, expression.subject, scope, none))
  expression.resolvedSubjectType = optionalResolvedType(subjectType)
  let inferredType: ResolvedType = neverType()
  let armPatterns: CasePattern[][] = []
  for arm of expression.arms {
    armPatterns.push(arm.patterns)
    armScope := Scope { parent: scope }
    checkCasePatterns(state, arm.patterns, subjectType, armScope)
    armExpected := expected
    let armType: ResolvedType = unknownType()
    case arm.body {
      block: Block -> {
        armScope.inValueYieldBlock = true
        armScope.yieldExpectedType = armExpected
        armScope.yieldType = if armExpected == none then optionalResolvedType(unknownType()) else armExpected
        completes := checkBlock(state, block, armScope)
        if completes { typeError(state, "Block case-expression arms must yield a value on every path", block.span) }
        armType = armScope.yieldType ?? unknownType()
        if !completes && armType.kind == "unknown" { armType = neverType() }
      }
      bodyExpression: Expression -> { armType = checkExpression(state, bodyExpression, armScope, armExpected) }
    }
    inferredType = pathType(state, inferredType, armType, expected, arm.span)
  }
  if subjectType.kind != "unknown" && subjectType.kind != "never" && !casePatternsExhaustive(state, subjectType, armPatterns) {
    typeError(state, "Case expression must be exhaustive", expression.span)
  }
  expression.resolvedType = optionalResolvedType(inferredType)
  return inferredType
}

export function checkedCaseSubjectType(type_: ResolvedType): ResolvedType {
  case type_ {
    weak_: WeakResolvedType -> { return resultType(weak_.inner, weakReferenceErrorType()) }
    _ -> { return type_ }
  }
}

export function casePatternsExhaustive(state: CheckerState, subjectType: ResolvedType, arms: CasePattern[][]): bool {
  for patterns of arms {
    for pattern of patterns {
      case pattern {
        _: WildcardPattern -> { return true }
        type_: TypePattern -> { if type_.resolvedType != none && sameType(subjectType, type_.resolvedType!) { return true } }
        _ -> { }
      }
    }
  }
  case subjectType {
    primitive_: PrimitiveType -> {
      if primitive_.name == "byte" { return integerPatternsExhaustive(arms, 0L, 255L) }
      if primitive_.name == "int" { return integerPatternsExhaustive(arms, -2147483648L, 2147483647L) }
      if primitive_.name == "long" { return integerPatternsExhaustive(arms, -9223372036854775807L - 1L, 9223372036854775807L) }
      if primitive_.name != "bool" { return false }
      let hasTrue = false
      let hasFalse = false
      for patterns of arms {
        for pattern of patterns {
          case pattern {
            value: ValuePattern -> {
              case value.value {
                boolean: BoolLiteral -> { if boolean.value { hasTrue = true } else { hasFalse = true } }
                _ -> { }
              }
            }
            _ -> { }
          }
        }
      }
      return hasTrue && hasFalse
    }
    result: ResultResolvedType -> { return unionPatternsExhaustive(UnionResolvedType { types: patternSubjectMembers(result) }, arms) }
    enum_: EnumType -> { return enumPatternsExhaustive(state, enum_, arms) }
    union_: UnionResolvedType -> { return unionPatternsExhaustive(union_, arms) }
    _ -> { }
  }
  return false
}

// Integer subjects are exhaustive when their value and range patterns cover
// every value of the subject type, [minimum, maximum], without gaps.
function integerPatternsExhaustive(arms: CasePattern[][], minimum: long, maximum: long): bool {
  let lowers: long[] = []
  let uppers: long[] = []
  for patterns of arms {
    for pattern of patterns {
      case pattern {
        range: RangePattern -> {
          let lower = minimum
          if range.start != none {
            resolvedLower := integerPatternValue(range.start!)
            if resolvedLower == none { continue }
            lower = resolvedLower!
          }
          let upper = maximum
          if range.end != none {
            resolvedUpper := integerPatternValue(range.end!)
            if resolvedUpper == none { continue }
            upper = resolvedUpper!
            if !range.inclusive {
              if upper <= minimum { continue }
              upper = upper - 1L
            }
          }
          lowers.push(lower); uppers.push(upper)
        }
        value: ValuePattern -> {
          resolved := integerPatternValue(value.value)
          if resolved != none { lowers.push(resolved!); uppers.push(resolved!) }
        }
        _ -> { }
      }
    }
  }
  // Extend the covered prefix [minimum, next) until no pattern reaches it.
  let next = minimum
  while true {
    let extended = false
    for index of 0..<lowers.length {
      if lowers[index] > next || uppers[index] < next { continue }
      if uppers[index] >= maximum { return true }
      next = uppers[index] + 1L
      extended = true
    }
    if !extended { return false }
  }
  return false
}

function integerPatternValue(expression: Expression): long | none {
  case expression {
    literal: IntLiteral -> { return long(literal.value) }
    literal: LongLiteral -> { return literal.value }
    unary: UnaryExpression -> {
      if unary.operator == "-" {
        value := integerPatternValue(unary.operand)
        if value != none { return -value! }
      }
    }
    _ -> { }
  }
  return none
}

function enumPatternsExhaustive(state: CheckerState, enum_: EnumType, arms: CasePattern[][]): bool {
  declaration := declarationFor(state.result, enum_.symbol)
  if declaration == none { return false }
  case declaration! {
    enumDeclaration: EnumDeclaration -> {
      for variant of enumDeclaration.variants {
        let found = false
        for patterns of arms {
          for pattern of patterns {
            case pattern {
              value: ValuePattern -> {
                case value.value {
                  dot: DotShorthand -> { if dot.name == variant.name { found = true } }
                  member: MemberExpression -> { if member.property == variant.name { found = true } }
                  _ -> { }
                }
              }
              _ -> { }
            }
          }
        }
        if !found { return false }
      }
      return true
    }
    _ -> { }
  }
  return false
}

function unionPatternsExhaustive(union_: UnionResolvedType, arms: CasePattern[][]): bool {
  for member of union_.types {
    let found = false
    for patterns of arms {
      for pattern of patterns {
        case pattern {
          type_: TypePattern -> { if type_.resolvedType != none && sameType(member, type_.resolvedType!) { found = true } }
          value: ValuePattern -> { case value.value { _: NoneLiteral -> { if member.kind == "none" { found = true } } _ -> { } } }
          _ -> { }
        }
      }
    }
    if !found { return false }
  }
  return true
}

// The subject members a type pattern selects among. A Result is the union of
// its two arms.
function patternSubjectMembers(subjectType: ResolvedType): ResolvedType[] {
  case subjectType {
    union_: UnionResolvedType -> { return union_.types }
    result: ResultResolvedType -> { return [successType(result.valueType), failureType(result.errorType)] }
    _ -> { return [subjectType] }
  }
}

// The generic type a member instantiates, for matching bare patterns.
function sameGenericHead(member: ResolvedType, name: string, symbol: Symbol | none): bool {
  case member {
    _: SuccessResolvedType -> { return name == "Success" }
    _: FailureResolvedType -> { return name == "Failure" }
    class_: ClassType -> {
      if class_.typeArgs.length == 0 { return false }
      return if symbol != none then class_.symbol == symbol! else class_.symbol.name == name
    }
    _ -> { return false }
  }
}

/** A bare generic pattern (`Success`, `Box`) takes its type arguments from the one subject member of that type. */
function inferredGenericPattern(named: NamedType, subjectType: ResolvedType): ResolvedType | none {
  if named.typeArgs.length > 0 { return none }
  let found: ResolvedType | none = none
  for member of patternSubjectMembers(subjectType) {
    if !sameGenericHead(member, named.name, named.resolvedSymbol) { continue }
    if found != none { return none }
    found = member
  }
  return found
}

/** The subject member instantiating the same generic type as an explicit pattern. */
function genericPatternMember(pattern: ResolvedType, subjectType: ResolvedType): ResolvedType | none {
  let name = ""
  let symbol: Symbol | none = none
  case pattern {
    _: SuccessResolvedType -> { name = "Success" }
    _: FailureResolvedType -> { name = "Failure" }
    class_: ClassType -> { if class_.typeArgs.length == 0 { return none } name = class_.symbol.name; symbol = class_.symbol }
    _ -> { return none }
  }
  for member of patternSubjectMembers(subjectType) { if sameGenericHead(member, name, symbol) { return member } }
  return none
}

function hasNoTypeArguments(annotation: TypeAnnotation): bool {
  case annotation {
    named: NamedType -> { return named.typeArgs.length == 0 }
    _ -> { return false }
  }
}

export function checkCasePatterns(state: CheckerState, patterns: CasePattern[], subjectType: ResolvedType, scope: Scope): none {
  for pattern of patterns {
    case pattern {
      type_: TypePattern -> {
        let resolved: ResolvedType = unknownType()
        let inferred: ResolvedType | none = none
        case type_.type_ {
          named: NamedType -> { inferred = inferredGenericPattern(named, subjectType) }
          _ -> { }
        }
        // A bare Success/Failure arm takes its payload from the subject; an
        // unknown subject has already been reported, so the arm stays unknown.
        bareResultArm := subjectType.kind == "unknown" && casePatternName(type_) != "" && hasNoTypeArguments(type_.type_)
        if inferred != none { resolved = inferred! }
        else if !bareResultArm {
          resolved = resolveType(state, type_.type_, state.info!, scope)
          // An explicit generic pattern must name the subject member exactly;
          // a different instantiation is never stored in the subject.
          member := genericPatternMember(resolved, subjectType)
          if member != none && !sameType(member!, resolved) {
            typeError(state, "Case type pattern \"" + typeName(resolved) + "\" must be \"" + typeName(member!) + "\" to match subject type \"" + typeName(subjectType) + "\"", type_.span)
          }
        }
        case type_.type_ {
          named: NamedType -> { named.resolvedType = optionalResolvedType(resolved) }
          _ -> { }
        }
        type_.resolvedType = optionalResolvedType(resolved)
        if !typesOverlap(state, subjectType, resolved) {
          typeError(state, "Case type pattern \"" + typeName(resolved) + "\" cannot match subject type \"" + typeName(subjectType) + "\"", type_.span)
        }
        if type_.name != "_" {
          declare(scope, Binding {
            name: type_.name,
            kind: "case-binding",
            type_: resolved,
            mutable: false,
            span: checkerSemanticSpan(type_.span),
            module: state.info!.path,
            casePattern: casePatternName(type_),
          })
        }
      }
      value: ValuePattern -> {
        valueType := checkExpression(state, value.value, scope, optionalResolvedType(subjectType))
        if !typesOverlap(state, subjectType, valueType) {
          typeError(state, "Case value pattern of type \"" + typeName(valueType) + "\" cannot match subject type \"" + typeName(subjectType) + "\"", value.span)
        }
      }
      range: RangePattern -> {
        // Ranges compare integer bounds; floating-point and other subjects are
        // reported once per pattern rather than once per bound.
        if subjectType.kind != "unknown" && !isIntegerOperand(subjectType) {
          typeError(state, "Range patterns require an integer subject (byte, int, or long); got \"" + typeName(subjectType) + "\"", range.span)
          if range.start != none { checkExpression(state, range.start!, scope, none) }
          if range.end != none { checkExpression(state, range.end!, scope, none) }
        } else {
          validateCaseRangeBound(state, range.start, subjectType, scope, range.span)
          validateCaseRangeBound(state, range.end, subjectType, scope, range.span)
        }
      }
      _: WildcardPattern -> { }
    }
  }
}

function validateCaseRangeBound(state: CheckerState, bound: Expression | none, subjectType: ResolvedType, scope: Scope, span: SourceSpan): none {
  if bound == none { return }
  boundType := checkExpression(state, bound!, scope, optionalResolvedType(subjectType))
  if boundType.kind != "unknown" && !isIntegerOperand(boundType) {
    typeError(state, "Range pattern bounds must be integers; got \"" + typeName(boundType) + "\"", bound!.span)
    return
  }
  if !typesOverlap(state, subjectType, boundType) {
    typeError(state, "Case range bound of type \"" + typeName(boundType) + "\" cannot match subject type \"" + typeName(subjectType) + "\"", span)
  }
}
