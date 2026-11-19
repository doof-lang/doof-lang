// Case expressions, case-pattern binding, and exhaustiveness.

import { Block, BoolLiteral, CaseExpression, CasePattern, DotShorthand, EnumDeclaration, Expression, IntLiteral, LongLiteral, MemberExpression, NamedType, NoneLiteral, RangePattern, SourceSpan, TypeAnnotation, TypePattern, UnaryExpression, ValuePattern, WildcardPattern } from "./ast"
import { typeError } from "./checker-common"
import { checkExpression } from "./checker-expressions"
import { pathType } from "./checker-inference"
import { isIntegerOperand } from "./checker-numeric"
import { typesOverlap } from "./checker-operators"
import { resolveType } from "./checker-annotations"
import { concreteInterfaceImplementations } from "./checker-interfaces"
import { CheckerState } from "./checker-state"
import { checkBlock } from "./checker-statements"
import { casePatternName, declarationFor, declare } from "./checker-symbols"
import { classType, failureType, neverType, resultType, sameType, successType, typeName, unknownType, weakReferenceErrorType } from "./checker-types"
import { checkerSemanticSpan } from "./checker-validation"
import type { Symbol } from "./semantic"
import { Binding, ClassType, EnumType, FailureResolvedType, InterfaceType, PrimitiveType, ResolvedType, ResultResolvedType, Scope, SuccessResolvedType, UnionResolvedType, WeakResolvedType } from "./semantic"

export function checkCaseExpression(state: CheckerState, expression: CaseExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  subjectType := checkedCaseSubjectType(checkExpression(state, expression.subject, scope, none))
  expression.resolvedSubjectType = subjectType
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
        armScope.yieldType = if armExpected == none then unknownType() else armExpected
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
  expression.resolvedType = inferredType
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
        type_: TypePattern -> { if resolvedType := type_.resolvedType && sameType(subjectType, resolvedType) { return true } }
        _ -> { }
      }
    }
  }
  if primitive_ := subjectType as PrimitiveType {
    if primitive_.name == "byte" { return integerPatternsExhaustive(arms, 0L, 255L) }
    if primitive_.name == "int" { return integerPatternsExhaustive(arms, -2147483648L, 2147483647L) }
    if primitive_.name == "long" { return integerPatternsExhaustive(arms, -9223372036854775807L - 1L, 9223372036854775807L) }
  }
  return memberCovered(state, subjectType, arms, false)
}

// A subject, or one member of a union subject, is covered by a type pattern
// naming it or by covering each of its parts: both arms of a Result, every
// variant of an enum, both bool values, every member of a union, or every
// implementation of a closed-world interface. Enum value patterns inside a
// union must name that enum.
function memberCovered(state: CheckerState, member: ResolvedType, arms: CasePattern[][], inUnion: bool): bool {
  for patterns of arms {
    for pattern of patterns {
      case pattern {
        type_: TypePattern -> { if resolvedType := type_.resolvedType && sameType(member, resolvedType) { return true } }
        value: ValuePattern -> { case value.value { _: NoneLiteral -> { if member.kind == "none" { return true } } _ -> { } } }
        _ -> { }
      }
    }
  }
  case member {
    primitive_: PrimitiveType -> { return primitive_.name == "bool" && boolPatternsExhaustive(arms) }
    result: ResultResolvedType -> { return memberCovered(state, successType(result.valueType), arms, true) && memberCovered(state, failureType(result.errorType), arms, true) }
    enum_: EnumType -> { return enumPatternsExhaustive(state, enum_, arms, inUnion) }
    union_: UnionResolvedType -> {
      for type_ of union_.types { if !memberCovered(state, type_, arms, true) { return false } }
      return true
    }
    interface_: InterfaceType -> {
      implementations := closedInterfaceImplementations(state, interface_)
      if implementations == none { return false }
      for implementation of implementations! { if !memberCovered(state, implementation, arms, true) { return false } }
      return true
    }
    _ -> { }
  }
  return false
}

// The classes an interface lowers to. Generic implementing classes depend on
// emitted instantiations, so their cases need a wildcard.
function closedInterfaceImplementations(state: CheckerState, interface_: InterfaceType): ClassType[] | none {
  if interface_.typeArgs.length > 0 { return concreteInterfaceImplementations(state.result, interface_) }
  let classes: ClassType[] = []
  for implementation of interface_.symbol.implementations {
    if implementation.typeParams.length > 0 { return none }
    classes.push(classType(implementation.name, implementation))
  }
  return classes
}

function boolPatternsExhaustive(arms: CasePattern[][]): bool {
  let hasTrue = false
  let hasFalse = false
  for patterns of arms {
    for pattern of patterns {
      if value := pattern as ValuePattern {
        if boolean := value.value as BoolLiteral { if boolean.value { hasTrue = true } else { hasFalse = true } }
      }
    }
  }
  return hasTrue && hasFalse
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
          if start := range.start {
            resolvedLower := integerPatternValue(start)
            if resolvedLower == none { continue }
            lower = resolvedLower!
          }
          let upper = maximum
          if end := range.end {
            resolvedUpper := integerPatternValue(end)
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
          if resolved := integerPatternValue(value.value) { lowers.push(resolved); uppers.push(resolved) }
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
        if value := integerPatternValue(unary.operand) { return -value }
      }
    }
    _ -> { }
  }
  return none
}

function enumPatternsExhaustive(state: CheckerState, enum_: EnumType, arms: CasePattern[][], inUnion: bool): bool {
  declaration := declarationFor(state.result, enum_.symbol)
  if declaration == none { return false }
  if enumDeclaration := declaration! as EnumDeclaration {
    for variant of enumDeclaration.variants {
      let found = false
      for patterns of arms {
        for pattern of patterns {
          if value := pattern as ValuePattern {
            if inUnion && (value.value.resolvedType == none || !sameType(value.value.resolvedType!, enum_)) { continue }
            case value.value {
              dot: DotShorthand -> { if dot.name == variant.name { found = true } }
              member: MemberExpression -> { if member.property == variant.name { found = true } }
              _ -> { }
            }
          }
        }
      }
      if !found { return false }
    }
    return true
  }
  return false
}

// The subject members a type pattern selects among. A Result is the union of
// its two arms, including a Result member of a wider union.
function patternSubjectMembers(subjectType: ResolvedType): ResolvedType[] {
  case subjectType {
    union_: UnionResolvedType -> {
      let members: ResolvedType[] = []
      for member of union_.types { for flattened of patternSubjectMembers(member) { members.push(flattened) } }
      return members
    }
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
      return if expectedSymbol := symbol then class_.symbol == expectedSymbol else class_.symbol.name == name
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
  let found: ResolvedType | none = none
  for member of patternSubjectMembers(subjectType) {
    if !sameGenericHead(member, name, symbol) { continue }
    if sameType(member, pattern) { return member }
    if found == none { found = member }
  }
  return found
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
        let mismatched = false
        if named := type_.type_ as NamedType { inferred = inferredGenericPattern(named, subjectType) }
        // A bare Success/Failure arm takes its payload from the subject; an
        // unknown subject has already been reported, so the arm stays unknown.
        bareResultArm := subjectType.kind == "unknown" && casePatternName(type_) != "" && hasNoTypeArguments(type_.type_)
        if inferredType := inferred { resolved = inferredType }
        else if !bareResultArm {
          resolved = resolveType(state, type_.type_, state.info!, scope)
          // An explicit generic pattern must name the subject member exactly;
          // a different instantiation is never stored in the subject.
          if member := genericPatternMember(resolved, subjectType) && !sameType(member, resolved) {
            mismatched = true
            typeError(state, "Case type pattern \"${typeName(resolved)}\" must be \"${typeName(member)}\" to match subject type \"${typeName(subjectType)}\"", type_.span)
          }
        }
        if named := type_.type_ as NamedType { named.resolvedType = resolved }
        type_.resolvedType = resolved
        if !mismatched && !typesOverlap(state, subjectType, resolved) {
          typeError(state, "Case type pattern \"${typeName(resolved)}\" cannot match subject type \"${typeName(subjectType)}\"", type_.span)
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
        valueType := checkExpression(state, value.value, scope, subjectType)
        if !typesOverlap(state, subjectType, valueType) {
          typeError(state, "Case value pattern of type \"${typeName(valueType)}\" cannot match subject type \"${typeName(subjectType)}\"", value.span)
        }
      }
      range: RangePattern -> {
        // Ranges compare integer bounds; floating-point and other subjects are
        // reported once per pattern rather than once per bound.
        if subjectType.kind != "unknown" && !isIntegerOperand(subjectType) {
          typeError(state, "Range patterns require an integer subject (byte, int, or long); got \"${typeName(subjectType)}\"", range.span)
          if start := range.start { checkExpression(state, start, scope, none) }
          if end := range.end { checkExpression(state, end, scope, none) }
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
  boundType := checkExpression(state, bound!, scope, subjectType)
  if boundType.kind != "unknown" && !isIntegerOperand(boundType) {
    typeError(state, "Range pattern bounds must be integers; got \"${typeName(boundType)}\"", bound!.span)
    return
  }
  if !typesOverlap(state, subjectType, boundType) {
    typeError(state, "Case range bound of type \"${typeName(boundType)}\" cannot match subject type \"${typeName(subjectType)}\"", span)
  }
}
