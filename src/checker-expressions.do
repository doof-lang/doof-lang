// Expression dispatch, operators, narrowing, and assignment checking.

import { checkArguments, positionalArguments } from "./checker-arguments"
import { resolveMember } from "./checker-resolution"

import { ActorType, ArrayResolvedType, Binding, ClassType, EnumType, InterfaceType, Diagnostic, FunctionParamType, FunctionType, JsonValueResolvedType, MapResolvedType, NoneType, PrimitiveType, PromiseType, ResolvedType, ResultResolvedType, Scope, TupleResolvedType, UnionResolvedType, UnknownType, TypeParameterType, WeakResolvedType } from "./semantic"

import { CheckedMember, ArrayLiteral, AsExpression, AssignmentExpression, BinaryExpression, Block, BoolLiteral, CallExpression, CallerExpression, CharLiteral, ClassDeclaration, ConstructExpression, DoubleLiteral, DotShorthand, EnumDeclaration, Expression, FloatLiteral, FunctionDeclaration, IfExpression, Identifier, IndexExpression, IntLiteral, LambdaExpression, LongLiteral, MemberExpression, NamedType, NoneLiteral, ObjectLiteral, SourceSpan, StringLiteral, ThisExpression, TupleLiteral, UnaryExpression, YieldBlockExpression, CatchExpression, CaseExpression, CasePattern, RangePattern, TypePattern, ValuePattern, WildcardPattern, AsyncExpression, RetireExpression, ActorCreationExpression } from "./ast"
import { actorType, classType, functionType, isNumeric, isJsonValueType, resultType, neverType, noneType, primitive, promiseType, rangeType, sameType, tupleType, typeName, unionType, isStringInterpolatable, typeParameter, unknownType, weakReferenceErrorType } from "./checker-types"

import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { asyncResultViolation } from "./checker-async"

import { pathType } from "./checker-inference"
import { CheckerState } from "./checker-state"
import { isNumericOperand, isIntegerOperand, numericOperatorAllowed, numericOperationType } from "./checker-numeric"
import { checkFunction, checkBlock } from "./checker-statements"
import { checkCall, checkLambda } from "./checker-calls"
import { checkArray, checkObject } from "./checker-literals"
import { fieldAssignmentBinding, resolveType, memberType, indexType } from "./checker-resolution"
import { deprecatedNoneAlias, finish, typeError, requireBool, validateAssignmentBinding } from "./checker-common"
import { builtinSourceLocationType, casePatternName, optionalResolvedType, isNamespaceImport, isTypeOnlyNamespaceImport, namespaceMemberSymbol, namespaceMemberType, resolveAnnotation, declare, lookup, currentThisType, isBuiltinCallable, builtinCallable, hasTypeParam, typeParamConstraintName, typeParamConstraint, symbolFor, valueUseDiagnostic, declarationFor } from "./checker-symbols"
import { resolveConstructor, validateConstructorVisibility, validateFieldArguments, checkConstruct } from "./checker-construction"
import { checkerSemanticSpan } from "./checker-validation"
import { isAssignableWithInterfaces } from "./checker-interfaces"

export function checkCaseExpression(state: CheckerState, expression: CaseExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  subjectType := checkExpression(state, expression.subject, scope, none)
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
      if primitive_.name == "int" { return integerPatternsExhaustive(arms) }
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
    _: ResultResolvedType -> {
      let hasSuccess = false
      let hasFailure = false
      for patterns of arms {
        for pattern of patterns {
          case pattern {
            type_: TypePattern -> {
              case type_.type_ {
                named: NamedType -> {
                  if named.name == "Success" { hasSuccess = true }
                  if named.name == "Failure" { hasFailure = true }
                }
                _ -> { }
              }
            }
            _ -> { }
          }
        }
      }
      return hasSuccess && hasFailure
    }
    enum_: EnumType -> { return enumPatternsExhaustive(state, enum_, arms) }
    union_: UnionResolvedType -> { return unionPatternsExhaustive(union_, arms) }
    _ -> { }
  }
  return false
}

function integerPatternsExhaustive(arms: CasePattern[][]): bool {
  let hasLower: bool[] = []
  let lowers: int[] = []
  let hasUpper: bool[] = []
  let uppers: int[] = []
  for patterns of arms {
    for pattern of patterns {
      case pattern {
        range: RangePattern -> {
          let lower = 0
          let lowerPresent = range.start != none
          if lowerPresent {
            resolvedLower := integerPatternValue(range.start!)
            if resolvedLower == none { continue }
            lower = resolvedLower!
          }
          let upper = 0
          let upperPresent = range.end != none
          if upperPresent {
            resolvedUpper := integerPatternValue(range.end!)
            if resolvedUpper == none { continue }
            upper = resolvedUpper!
            if !range.inclusive {
              if upper == (-2147483647 - 1) { continue }
              upper = upper - 1
            }
          }
          hasLower.push(lowerPresent); lowers.push(lower)
          hasUpper.push(upperPresent); uppers.push(upper)
        }
        value: ValuePattern -> {
          resolved := integerPatternValue(value.value)
          if resolved != none {
            hasLower.push(true); lowers.push(resolved!)
            hasUpper.push(true); uppers.push(resolved!)
          }
        }
        _ -> { }
      }
    }
  }
  let started = false
  let currentUpper = 0
  for index of 0..<hasLower.length {
    if hasLower[index] { continue }
    if !hasUpper[index] { return true }
    if !started || uppers[index] > currentUpper { currentUpper = uppers[index]; started = true }
  }
  if !started { return false }
  for pass of 0..<hasLower.length {
    let extended = false
    for index of 0..<hasLower.length {
      if !hasLower[index] { continue }
      connects := lowers[index] <= currentUpper || (currentUpper < 2147483647 && lowers[index] == currentUpper + 1)
      if !connects { continue }
      if !hasUpper[index] { return true }
      if uppers[index] > currentUpper { currentUpper = uppers[index]; extended = true }
    }
    if currentUpper == 2147483647 { return true }
    if !extended { return false }
  }
  return currentUpper == 2147483647
}

function integerPatternValue(expression: Expression): int | none {
  case expression {
    literal: IntLiteral -> { return literal.value }
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

export function checkCasePatterns(state: CheckerState, patterns: CasePattern[], subjectType: ResolvedType, scope: Scope): none {
  for pattern of patterns {
    case pattern {
      type_: TypePattern -> {
        let resolved: ResolvedType = unknownType()
        let contextualResultArm = false
        case subjectType {
          _: ResultResolvedType -> {
            case type_.type_ {
              named: NamedType -> {
                if named.name == "Success" || named.name == "Failure" {
                  contextualResultArm = true
                  resolved = subjectType
                  // Explicit payload arguments still need full decoration.
                  for argument of named.typeArgs { resolveType(state, argument, state.info!, scope) }
                }
              }
              _ -> { }
            }
          }
          _ -> { }
        }
        if !contextualResultArm { resolved = resolveType(state, type_.type_, state.info!, scope) }
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
        validateCaseRangeBound(state, range.start, subjectType, scope, range.span)
        validateCaseRangeBound(state, range.end, subjectType, scope, range.span)
      }
      _: WildcardPattern -> { }
    }
  }
}

export function checkExpression(state: CheckerState, expression: Expression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  case expression {
    yieldBlock: YieldBlockExpression -> {
      yieldScope := Scope {
        parent: scope,
        inValueYieldBlock: true,
        yieldExpectedType: expected,
        yieldType: if expected == none then optionalResolvedType(unknownType()) else expected,
      }
      completes := checkBlock(state, yieldBlock.body, yieldScope)
      if completes {
        typeError(state, "Yield blocks must yield a value on every path", yieldBlock.body.span)
      }
      let resolved = yieldScope.yieldType ?? unknownType()
      if !completes && resolved.kind == "unknown" { resolved = neverType() }
      return finish(state, yieldBlock, resolved)
    }
    catch_: CatchExpression -> {
      let errorTypes: ResolvedType[] = []
      catchScope := Scope { parent: scope, capturesTryErrors: true, catchErrorTypes: errorTypes }
      checkBlock(state, catch_.body, catchScope)
      if errorTypes.length == 0 {
        state.diagnostics.push(Diagnostic {
          severity: "warning",
          message: "catch block contains no 'try' statements",
          span: checkerSemanticSpan(catch_.span),
          module: state.info!.path,
        })
        return finish(state, catch_, noneType())
      }
      let caught: ResolvedType = noneType()
      for errorType of errorTypes { caught = pathType(state, caught, errorType, expected, catch_.span) }
      return finish(state, catch_, caught)
    }
    literal: IntLiteral -> {
      if expected != none { case expected! {
        primitiveExpected: PrimitiveType -> {
          if primitiveExpected.name == "byte" && (literal.value < 0 || literal.value > 255) {
            typeError(state, "Byte literal must be in the range 0–255", expression.span)
          }
          if primitiveExpected.name == "byte" || primitiveExpected.name == "long" || primitiveExpected.name == "float" || primitiveExpected.name == "double" {
            return finish(state, expression, expected!)
          }
        }
        _ -> { }
      } }
      return finish(state, expression, primitive("int"))
    }
    _: LongLiteral -> {
      if expected != none { case expected! {
        primitiveExpected: PrimitiveType -> { if primitiveExpected.name == "double" { return finish(state, expression, expected!) } }
        _ -> { }
      } }
      return finish(state, expression, primitive("long"))
    }
    _: FloatLiteral -> {
      if expected != none { case expected! {
        primitiveExpected: PrimitiveType -> { if primitiveExpected.name == "double" { return finish(state, expression, expected!) } }
        _ -> { }
      } }
      return finish(state, expression, primitive("float"))
    }
    _: DoubleLiteral -> {
      if expected != none { case expected! {
        primitiveExpected: PrimitiveType -> { if primitiveExpected.name == "float" { return finish(state, expression, expected!) } }
        _ -> { }
      } }
      return finish(state, expression, primitive("double"))
    }
    string_: StringLiteral -> {
      let diverges = false
      for interpolation of string_.interpolations {
        interpolationType := checkExpression(state, interpolation, scope, none)
        if interpolationType.kind == "never" { diverges = true }
        else if !isStringInterpolatable(interpolationType) {
          typeError(state, "Type \"" + typeName(interpolationType) + "\" cannot be used in string interpolation", interpolation.span)
        }
      }
      if diverges { return finish(state, expression, neverType()) }
      return finish(state, expression, primitive("string"))
    }
    _: CharLiteral -> { return finish(state, expression, primitive("char")) }
    _: BoolLiteral -> { return finish(state, expression, primitive("bool")) }
    noneLiteral: NoneLiteral -> {
      if noneLiteral.sourceSpelling != "none" && noneLiteral.resolvedType == none { deprecatedNoneAlias(state, noneLiteral.sourceSpelling, noneLiteral.span) }
      return finish(state, expression, noneType())
    }
    _: CallerExpression -> {
      if !state.allowsCaller { typeError(state, "@caller is only valid as a parameter or class-field default value", expression.span) }
      return finish(state, expression, builtinSourceLocationType())
    }
    dot: DotShorthand -> { return checkDotShorthand(state, dot, expected) }
    identifier: Identifier -> { return checkIdentifier(state, identifier, scope) }
    binary: BinaryExpression -> { return checkBinary(state, binary, scope, expected) }
    unary: UnaryExpression -> { return checkUnary(state, unary, scope) }
    as_: AsExpression -> { return checkAs(state, as_, scope) }
    assignment: AssignmentExpression -> { return checkAssignment(state, assignment, scope) }
    member: MemberExpression -> {
      let objectType = unknownType()
      let namespaceMember: ResolvedType | none = none
      let namespaceName = ""
      case member.object {
        identifier: Identifier -> {
          // Bindings shadow namespace-like spellings. Resolve capabilities from
          // the selected binding instead of the identifier text alone.
          localBinding := lookup(scope, identifier.name)
          if localBinding == none && isNamespaceImport(state.info!, identifier.name) {
            namespaceName = identifier.name
            member.resolvedNamespaceAccess = true
            if isTypeOnlyNamespaceImport(state.info!, identifier.name) {
              typeError(state, "Type-only namespace import '" + identifier.name + "' cannot be used as a value", member.span)
              return finish(state, expression, unknownType())
            } else {
              member.resolvedNamespaceSymbol = namespaceMemberSymbol(state.info!, identifier.name, member.property, state.result)
              namespaceMember = namespaceMemberType(state.info!, identifier.name, member.property, state.result)
            }
          } else {
            objectType = checkExpression(state, member.object, scope, none)
          }
        }
        _ -> { objectType = checkExpression(state, member.object, scope, none) }
      }
      if namespaceMember != none {
        selected := CheckedMember { type_: namespaceMember }
        if member.resolvedNamespaceSymbol != none {
          selected.modulePath = member.resolvedNamespaceSymbol!.module
          declaration := declarationFor(state.result, member.resolvedNamespaceSymbol!)
          if declaration != none { case declaration! { fn: FunctionDeclaration -> { selected.function_ = fn } _ -> { } } }
        }
        member.resolvedMember = selected
        if namespaceMember!.kind == "unknown" {
          typeError(state, "Namespace \"" + namespaceName + "\" has no member \"" + member.property + "\"", member.span)
        }
        return finish(state, expression, namespaceMember!)
      }
      if objectType.kind == "never" { return finish(state, expression, neverType()) }
      let weakReceiver: WeakResolvedType | none = none
      case objectType {
        weak_: WeakResolvedType -> {
          weakReceiver = weak_
          objectType = weakAccessTarget(weak_.inner)
          if !member.optional && !member.force {
            typeError(state, "Weak reference member access requires '?.' or '!.'", member.span)
          }
        }
        _ -> { }
      }
      case member.object {
        identifier: Identifier -> {
          if member.property == "parse" && legacyNumericParseType(identifier) {
            replacement := if identifier.name == "byte" then "parseByte" else
              if identifier.name == "int" then "parseInt" else
              if identifier.name == "long" then "parseLong" else
              if identifier.name == "float" then "parseFloat" else "parseDouble"
            typeError(state, identifier.name + ".parse was removed; import " + replacement + " from \"std/parse\"", member.span)
            return finish(state, expression, unknownType())
          }
        }
        _ -> { }
      }
      diagnosticCount := state.diagnostics.length
      selected := resolveMember(state, objectType, member.property, member.span)
      member.resolvedMember = selected
      memberValue := selected.type_!
      if memberValue.kind == "unknown" && objectType.kind != "unknown" && state.diagnostics.length == diagnosticCount {
        typeError(state, "Type \"" + typeName(objectType) + "\" has no member \"" + member.property + "\"", member.span)
      }
      member.resolvedStaticOwner = selected.staticOwner
      if member.resolvedStaticOwner != none && !isNamedStaticReceiver(member.object) {
        typeError(state, "Static member '" + member.property + "' cannot be accessed through an instance with '.'; use '::'", member.span)
      }
      if member.resolvedStaticOwner == none && isNamedStaticReceiver(member.object) && selected.instance {
        typeError(state, "Instance member '" + member.property + "' cannot be accessed through a class", member.span)
      }
      case objectType {
        _: EnumType -> {
          namedReceiver := isNamedStaticReceiver(member.object)
          staticMember := member.property == "values" || member.property == "fromName" || member.property == "fromValue" || member.property == "fromJsonValue"
          if namedReceiver && (member.property == "name" || member.property == "value" || member.property == "toJsonValue") {
            typeError(state, "Instance member '" + member.property + "' cannot be accessed through an enum type", member.span)
          } else if !namedReceiver && staticMember {
            typeError(state, "Static enum member '" + member.property + "' cannot be accessed through a value", member.span)
          }
          if !namedReceiver && enumVariantMember(state, objectType, member.property) {
            typeError(state, "Enum variant '" + member.property + "' cannot be accessed through a value", member.span)
          }
        }
        _ -> { }
      }
      member.resolvedCallableField = selected.field
      if weakReceiver != none {
        case memberValue {
          _: FunctionType -> { return finish(state, expression, memberValue) }
          _ -> {
            if member.optional { return finish(state, expression, resultType(unionType([memberValue, noneType()]), weakReferenceErrorType())) }
          }
        }
      }
      return finish(state, expression, memberValue)
    }
    index: IndexExpression -> {
      objectType := checkExpression(state, index.object, scope, none)
      indexValueType := checkExpression(state, index.index, scope, optionalResolvedType(primitive("int")))
      resolved := indexType(state, objectType, indexValueType, index.span)
      if objectType.kind == "never" || indexValueType.kind == "never" { return finish(state, expression, neverType()) }
      return finish(state, expression, resolved)
    }
    call: CallExpression -> { return checkCall(state, call, scope, expected) }
    array: ArrayLiteral -> { return checkArray(state, array, scope, expected) }
    tuple: TupleLiteral -> {
      let elements: ResolvedType[] = []
      let diverges = false
      let expectedTuple: TupleResolvedType | none = none
      if expected != none {
        case expected! { tupleExpected: TupleResolvedType -> { expectedTuple = tupleExpected } _ -> { } }
      }
      for index of 0..<tuple.elements.length {
        item := tuple.elements[index]
        let itemExpected: ResolvedType | none = none
        if expectedTuple != none && index < expectedTuple!.elements.length { itemExpected = optionalResolvedType(expectedTuple!.elements[index]) }
        itemType := checkExpression(state, item, scope, itemExpected)
        elements.push(itemType)
        if itemType.kind == "never" { diverges = true }
      }
      if diverges { return finish(state, expression, neverType()) }
      return finish(state, expression, tupleType(elements))
    }
    object: ObjectLiteral -> {
      return checkObject(state, object, scope, expected)
    }
    lambda: LambdaExpression -> { return checkLambda(state, lambda, scope, expected) }
    if_: IfExpression -> {
      conditionType := checkExpression(state, if_.condition, scope, optionalResolvedType(primitive("bool")))
      requireBool(state, conditionType, if_.condition.span)
      thenType := checkExpression(state, if_.then_, scope, expected)
      elseType := checkExpression(state, if_.else_, scope, expected)
      if conditionType.kind == "never" { return finish(state, expression, neverType()) }
      return finish(state, expression, pathType(state, thenType, elseType, expected, if_.span))
    }
    case_: CaseExpression -> { return finish(state, expression, checkCaseExpression(state, case_, scope, expected)) }
    construct: ConstructExpression -> { return checkConstruct(state, construct, scope, expected) }
    async_: AsyncExpression -> {
      case async_.expression {
        block: Block -> {
          let expectedValue: ResolvedType | none = none
          if expected != none {
            case expected! {
              promise: PromiseType -> { expectedValue = promise.valueType }
              _ -> { }
            }
          }
          asyncScope := Scope {
            parent: scope,
            inValueYieldBlock: true,
            yieldExpectedType: expectedValue,
            yieldType: if expectedValue == none then optionalResolvedType(unknownType()) else expectedValue,
          }
          completes := checkBlock(state, block, asyncScope)
          if completes { typeError(state, "Async blocks must yield a value on every path", block.span) }
          let valueType = asyncScope.yieldType ?? unknownType()
          if !completes && valueType.kind == "unknown" { valueType = neverType() }
          violation := asyncResultViolation(state.result, valueType)
          if violation != none {
            typeError(state, "Async block result type \"" + typeName(valueType) + "\" cannot cross from the worker: " + violation!, async_.span)
          }
          return finish(state, expression, promiseType(valueType))
        }
        inner: Expression -> {
          innerType := checkExpression(state, inner, scope, none)
          let actorCall = false
          let isolatedCall = false
          case inner {
            call: CallExpression -> {
              isolatedCall = call.resolvedFunction != none
              case call.callee {
                member: MemberExpression -> {
                  if member.object.resolvedType != none {
                    case member.object.resolvedType! {
                      _: ActorType -> { actorCall = true }
                      _ -> { }
                    }
                  }
                }
                _ -> { }
              }
              if !actorCall && isolatedCall {
                for i of 0..<call.args.length {
                  argumentType := call.args[i].value.resolvedType
                  if argumentType == none { continue }
                  violation := findActorBoundaryViolation(state.result, argumentType!)
                  if violation != none {
                    typeError(state,
                      "Async call argument " + string(i + 1) + " of type \"" + typeName(argumentType!) + "\" cannot cross to the worker: " + violation!.reason,
                      call.args[i].span,
                    )
                  }
                }
                case call.callee {
                  member: MemberExpression -> {
                    if member.resolvedStaticOwner == none && member.object.resolvedType != none {
                      receiverViolation := findActorBoundaryViolation(state.result, member.object.resolvedType!)
                      if receiverViolation != none {
                        typeError(state,
                          "Async call receiver of type \"" + typeName(member.object.resolvedType!) + "\" cannot cross to the worker: " + receiverViolation!.reason,
                          member.object.span,
                        )
                      }
                    }
                  }
                  _ -> { }
                }
                resultViolation := asyncResultViolation(state.result, innerType)
                if resultViolation != none {
                  typeError(state,
                    "Async call result type \"" + typeName(innerType) + "\" cannot cross from the worker: " + resultViolation!,
                    async_.span,
                  )
                }
              }
            }
            _ -> { }
          }
          if !actorCall && !isolatedCall {
            typeError(state, "`async` requires an actor method call or an inferrably isolated function call", async_.span)
          }
          return finish(state, expression, promiseType(innerType))
        }
      }
    }
    retire_: RetireExpression -> {
      retiredType := checkExpression(state, retire_.actor, scope, none)
      case retiredType {
        actor: ActorType -> { return finish(state, expression, actor.innerClass) }
        _ -> { typeError(state, "Cannot retire non-actor type \"" + typeName(retiredType) + "\"", retire_.span); return finish(state, expression, unknownType()) }
      }
    }
    actorCreation: ActorCreationExpression -> {
      symbol := symbolFor(state.info!, actorCreation.className)
      if symbol == none || symbol!.kind != "class" {
        for argument of actorCreation.args { checkExpression(state, argument, scope, none) }
        typeError(state, "Actor requires a class type; \"" + actorCreation.className + "\" is not a class", actorCreation.span)
        return finish(state, expression, unknownType())
      }
      inner := classType(actorCreation.className, symbol!)
      construction := resolveConstructor(state, inner)
      actorCreation.resolvedConstruction = construction
      actorCreation.resolvedConstructor = construction.factory
      if construction.factory != none {
        validateConstructorVisibility(state, inner, construction.factory!, actorCreation.span)
        if !sameType(construction.signature.returnType, inner) {
          typeError(state, "Actor constructor factory for \"" + inner.name + "\" must return " + inner.name + " directly", actorCreation.span)
        }
      }
      params := construction.signature.params
      validateFieldArguments(state, construction, inner, positionalArguments(actorCreation.args))
      checkArguments(state, positionalArguments(actorCreation.args), params, scope, actorCreation.span,
        "Actor \"" + actorCreation.className + "\"", "Actor constructor argument")
      for i of 0..<actorCreation.args.length {
        actual := actorCreation.args[i].resolvedType ?? unknownType()
        violation := findActorBoundaryViolation(state.result, actual)
        if violation != none {
          typeError(state,
            "Actor constructor argument " + string(i + 1) + " of type \"" + typeName(actual) + "\" cannot cross actor boundary: " + violation!.reason,
            actorCreation.args[i].span,
          )
        }
      }
      return finish(state, expression, actorType(inner))
    }
    this_: ThisExpression -> {
      let current: Scope | none = scope
      while current != none {
        if current!.staticContext {
          typeError(state, "Cannot use 'this' in a static method", this_.span)
          return finish(state, expression, unknownType())
        }
        if current!.thisType != none { break }
        current = current!.parent
      }
      return finish(state, expression, currentThisType(scope))
    }
    _ -> { return finish(state, expression, unknownType()) }
  }
  return unknownType()
}

function weakAccessTarget(type_: ResolvedType): ResolvedType {
  case type_ {
    union_: UnionResolvedType -> {
      let present: ResolvedType[] = []
      for member of union_.types { if member.kind != "none" { present.push(member) } }
      if present.length > 0 { return unionType(present) }
    }
    _ -> { }
  }
  return type_
}

function isNamedStaticReceiver(expression: Expression): bool {
  case expression {
    identifier: Identifier -> {
      if identifier.resolvedBinding == none { return false }
      binding := identifier.resolvedBinding!
      if binding.kind == "type-parameter" || binding.kind == "class" || binding.kind == "struct" || binding.kind == "interface" || binding.kind == "enum" { return true }
      if binding.kind == "import" && binding.symbol != none {
        kind := binding.symbol!.kind
        return kind == "class" || kind == "struct" || kind == "interface" || kind == "enum"
      }
    }
    _ -> { }
  }
  return false
}

function enumVariantMember(state: CheckerState, receiver: ResolvedType, property: string): bool {
  case receiver {
    enum_: EnumType -> {
      declaration := declarationFor(state.result, enum_.symbol)
      if declaration != none {
        case declaration! {
          owner: EnumDeclaration -> { for variant of owner.variants { if variant.name == property { return true } } }
          _ -> { }
        }
      }
    }
    _ -> { }
  }
  return false
}

export function checkDotShorthand(state: CheckerState, expression: DotShorthand, expected: ResolvedType | none): ResolvedType {
  if expected == none {
    typeError(state, "Cannot resolve shorthand ." + expression.name + " without an expected class or enum type", expression.span)
    return finish(state, expression, unknownType())
  }
  case expected! {
    enum_: EnumType -> {
      declaration := declarationFor(state.result, enum_.symbol)
      let found = false
      if declaration != none {
        case declaration! {
          enumDeclaration: EnumDeclaration -> {
            for variant of enumDeclaration.variants { if variant.name == expression.name { found = true } }
          }
          _ -> { }
        }
      }
      if !found {
        typeError(state, "Enum \"" + enum_.name + "\" has no variant \"" + expression.name + "\"", expression.span)
        return finish(state, expression, unknownType())
      }
      expression.resolvedShorthandOwnerName = enum_.name
      expression.resolvedShorthandOwnerKind = "enum"
      expression.resolvedShorthandOwnerModule = enum_.symbol.module
      expression.resolvedShorthandOwnerNative = enum_.symbol.native_
      expression.resolvedShorthandOwnerCppName = enum_.symbol.nativeCppName
      return finish(state, expression, enum_)
    }
    class_: ClassType -> {
      diagnosticCount := state.diagnostics.length
      selected := resolveMember(state, class_, expression.name, expression.span)
      value := selected.type_!
      if selected.staticOwner == none {
        if state.diagnostics.length == diagnosticCount {
          typeError(state, "Type \"" + class_.name + "\" has no static member \"" + expression.name + "\"", expression.span)
        }
        return finish(state, expression, unknownType())
      }
      expression.resolvedShorthandOwnerName = class_.name
      expression.resolvedShorthandOwnerKind = "class"
      expression.resolvedShorthandOwnerModule = class_.symbol.module
      expression.resolvedShorthandOwnerNative = class_.symbol.native_
      expression.resolvedShorthandOwnerCppName = class_.symbol.nativeCppName
      return finish(state, expression, value)
    }
    _ -> { }
  }
  typeError(state, "Cannot resolve shorthand ." + expression.name + " for expected type \"" + typeName(expected!) + "\"", expression.span)
  return finish(state, expression, unknownType())
}

export function checkIdentifier(state: CheckerState, identifier: Identifier, scope: Scope): ResolvedType {
  let binding: Binding | none = lookup(scope, identifier.name)
  if binding == none && hasTypeParam(scope, identifier.name) {
    binding = Binding {
      name: identifier.name, kind: "type-parameter", type_: typeParameter(identifier.name, typeParamConstraintName(scope, identifier.name), typeParamConstraint(scope, identifier.name)), mutable: false,
      span: checkerSemanticSpan(identifier.span), module: state.info!.path,
    }
  }
  if binding == none { binding = implicitMethod(state, scope, identifier.name, identifier.span) }
  if binding == none && isBuiltinCallable(identifier.name) {
    binding = Binding { name: identifier.name, kind: "builtin", type_: builtinCallable(identifier.name), mutable: false, span: checkerSemanticSpan(identifier.span), module: state.info!.path }
  }
  if binding == none {
    message := valueUseDiagnostic(state.info!, identifier.name)
    typeError(state, if message == "" then "Unknown identifier '" + identifier.name + "'" else message, identifier.span)
    return finish(state, identifier, unknownType())
  }
  identifier.resolvedBinding = binding
  return finish(state, identifier, binding.type_)
}

function legacyNumericParseType(identifier: Identifier): bool {
  if identifier.resolvedBinding == none || identifier.resolvedBinding!.kind != "builtin" { return false }
  name := identifier.name
  return name == "byte" || name == "int" || name == "long" || name == "float" || name == "double"
}

export function implicitMethod(state: CheckerState, scope: Scope, name: string, span: SourceSpan): Binding | none {
  case currentThisType(scope) {
    owner: ClassType -> {
      declaration := declarationFor(state.result, owner.symbol)
      if declaration == none { return none }
      case declaration! {
        class_: ClassDeclaration -> {
          for method of class_.methods {
            if method.name == name {
              methodType := method.resolvedType ?? checkFunction(state, method, scope, owner)
              return Binding {
                name, kind: "method", type_: methodType, mutable: false,
                span: checkerSemanticSpan(span), module: state.info!.path, symbol: owner.symbol,
              }
            }
          }
        }
        _ -> { }
      }
    }
    _ -> { }
  }
  return none
}

export function addClassMethods(state: CheckerState, scope: Scope, owner: ClassType): none {
  declaration := declarationFor(state.result, owner.symbol)
  if declaration == none { return }
  case declaration! {
    class_: ClassDeclaration -> {
      for method of class_.methods {
        let methodType: ResolvedType = unknownType()
        if method.resolvedType != none {
          methodType = method.resolvedType!
        } else {
          // Predeclare methods without decorating their annotations.  This
          // helper runs while another method is being checked, so its scope
          // does not contain the method's own type parameters.  The owning
          // method check is the authority that decorates those annotations.
          let methodTypeParams: string[] = []
          for typeParam of class_.typeParams { methodTypeParams.push(typeParam) }
          for typeParam of method.typeParams { methodTypeParams.push(typeParam) }
          let parameters: FunctionParamType[] = []
          for parameter of method.params {
            parameterType := if parameter.type_ == none then unknownType() else resolveAnnotation(parameter.type_!, state.info!, state.result, methodTypeParams)
            parameters.push(FunctionParamType { name: parameter.name, type_: parameterType, hasDefault: parameter.defaultValue != none })
          }
          returnType := if method.returnType == none then noneType() else resolveAnnotation(method.returnType!, state.info!, state.result, methodTypeParams)
          methodType = functionType(parameters, returnType, method.typeParams)
        }
        declare(scope, Binding {
          name: method.name, kind: "method", type_: methodType, mutable: false,
          span: checkerSemanticSpan(method.span), module: state.info!.path, symbol: owner.symbol,
        })
      }
    }
    _ -> { }
  }
}

export function checkBinary(state: CheckerState, expression: BinaryExpression, scope: Scope, expected: ResolvedType | none = none): ResolvedType {
  let left: ResolvedType = unknownType()
  let right: ResolvedType = unknownType()
  case expression.left {
    _: DotShorthand -> {
      right = checkExpression(state, expression.right, scope, none)
      left = checkExpression(state, expression.left, scope, optionalResolvedType(right))
    }
    _ -> {
      case expression.right {
        _: DotShorthand -> {
          left = checkExpression(state, expression.left, scope, none)
          shorthandExpected := if expression.operator == "??" then nonNoneType(state, left) else left
          right = checkExpression(state, expression.right, scope, optionalResolvedType(shorthandExpected))
        }
        _ -> {
          left = checkExpression(state, expression.left, scope, none)
          right = checkExpression(state, expression.right, scope, if expression.operator == "??" then expected else none)
        }
      }
    }
  }
  operator := expression.operator
  if left.kind == "never" { return finish(state, expression, neverType()) }
  if operator == "&&" || operator == "||" {
    requireBool(state, left, expression.left.span); requireBool(state, right, expression.right.span)
    return finish(state, expression, primitive("bool"))
  }
  if operator == "??" {
    if !isFallibleType(left) { typeError(state, "Operator '??' requires a nullable or Result left operand, got " + typeName(left), expression.left.span) }
    return finish(state, expression, pathType(state, fallibleValueType(left) ?? unknownType(), right, expected, expression.span))
  }
  if right.kind == "never" { return finish(state, expression, neverType()) }
  if operator == "..<" || operator == ".." {
    validateRangeOperand(state, operator, "left", left, expression.left.span)
    validateRangeOperand(state, operator, "right", right, expression.right.span)
    return finish(state, expression, rangeType())
  }
  if operator == "==" || operator == "!=" {
    validateNoneComparison(state, operator, left, right, expression.span)
    if left.kind != "none" && right.kind != "none" && !typesOverlap(state, left, right) {
      typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), expression.span)
    }
    return finish(state, expression, primitive("bool"))
  }
  if operator == "<" || operator == "<=" || operator == ">" || operator == ">=" {
    if !orderedTypes(state, left, right) { typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), expression.span) }
    return finish(state, expression, primitive("bool"))
  }
  if operator == "+" && typeName(left) == "string" && (typeName(right) == "string" || typeName(right) == "char" || typeName(right) == "unknown") { return finish(state, expression, primitive("string")) }
  if operator == "+" && typeName(right) == "string" && (typeName(left) == "char" || typeName(left) == "unknown") { return finish(state, expression, primitive("string")) }
  if isNumericOperand(left) && isNumericOperand(right) {
    validateNumericOperator(state, operator, left, right, expression.span)
    return finish(state, expression, numericOperationType(left, right, operator))
  }
  typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), expression.span)
  return finish(state, expression, unknownType())
}

function validateNoneComparison(state: CheckerState, operator: string, left: ResolvedType, right: ResolvedType, span: SourceSpan): none {
  if left.kind == "none" && !admitsNone(right) {
    typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), span)
  } else if right.kind == "none" && !admitsNone(left) {
    typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), span)
  }
}

function admitsNone(type_: ResolvedType): bool {
  case type_ {
    _: NoneType -> { return true }
    _: UnknownType -> { return true }
    _: JsonValueResolvedType -> { return true }
    union_: UnionResolvedType -> {
      for member of union_.types { if member.kind == "none" { return true } }
    }
    _ -> { }
  }
  return false
}

function validateRangeOperand(state: CheckerState, operator: string, side: string, operand: ResolvedType, span: SourceSpan): none {
  if operand.kind == "unknown" { return }
  case operand {
    primitive_: PrimitiveType -> {
      if primitive_.name != "byte" && primitive_.name != "int" && primitive_.name != "long" {
        typeError(state, "Range operator \"" + operator + "\" requires integer bounds, got " + side + " bound of type \"" + typeName(operand) + "\"", span)
      } else if primitive_.name == "long" {
        typeError(state, "Range operator \"" + operator + "\" currently requires int-compatible bounds, got " + side + " bound of type \"long\"", span)
      }
    }
    _ -> { typeError(state, "Range operator \"" + operator + "\" requires integer bounds, got " + side + " bound of type \"" + typeName(operand) + "\"", span) }
  }
}

export function checkUnary(state: CheckerState, expression: UnaryExpression, scope: Scope): ResolvedType {
  value := checkExpression(state, expression.operand, scope, none)
  // Keep the operand decoration explicit at this boundary.  The emitter
  // consumes the operand node later, and must not reconstruct its type from
  // the unary state.result (notably for try! over imported Result functions).
        expression.operand.resolvedType = optionalResolvedType(value)
  if value.kind == "never" { return finish(state, expression, neverType()) }
  if expression.operator == "try!" || expression.operator == "try?" {
    case value {
      result: ResultResolvedType -> {
        if result.valueType.kind == "none" {
          if expression.operator == "try?" { typeError(state, "try? requires a Result with a success value", expression.span) }
          return finish(state, expression, result.valueType)
        }
        if expression.operator == "try?" { return finish(state, expression, unionType([result.valueType, noneType()])) }
        return finish(state, expression, result.valueType)
      }
      _ -> { typeError(state, expression.operator + " requires a Result expression", expression.span) }
    }
    return finish(state, expression, unknownType())
  }
  if !expression.prefix && expression.operator == "!" {
    case value {
      result: ResultResolvedType -> { return finish(state, expression, result.valueType) }
      _ -> { }
    }
    if !isNullableType(value) {
      typeError(state, "Postfix '!' requires a nullable or Result operand, got " + typeName(value), expression.span)
      return finish(state, expression, unknownType())
    }
    return finish(state, expression, nonNoneType(state, value))
  }
  if expression.operator == "!" { requireBool(state, value, expression.span); return finish(state, expression, primitive("bool")) }
  if expression.operator == "+" || expression.operator == "-" || expression.operator == "~" {
    if !isNumericOperand(value) { typeError(state, "Unary '" + expression.operator + "' requires a numeric operand", expression.span) }
    else {
      if expression.operator == "~" && !isIntegerOperand(value) { typeError(state, "Unary '~' requires an integer operand", expression.span) }
      return finish(state, expression, numericOperationType(value, value))
    }
    return finish(state, expression, value)
  }
  return finish(state, expression, value)
}

/** Validates checked narrowing and preserves its fallible Result shape. */
export function checkAs(state: CheckerState, expression: AsExpression, scope: Scope): ResolvedType {
  sourceType := checkExpression(state, expression.expression, scope, none)
  targetType := resolveType(state, expression.targetType, state.info!, scope)
  if sourceType.kind == "never" { return finish(state, expression, neverType()) }
  case sourceType {
    result: ResultResolvedType -> {
      if !isValidAsNarrow(state, result.valueType, targetType) {
        typeError(state, "Cannot narrow \"" + typeName(sourceType) + "\" to \"" + typeName(targetType) + "\" with \"as\"", expression.span)
        return finish(state, expression, unknownType())
      }
      return finish(state, expression, resultType(targetType, unionType([result.errorType, primitive("string")])))
    }
    _ -> { }
  }
  if !isValidAsNarrow(state, sourceType, targetType) {
    typeError(state, "Cannot narrow \"" + typeName(sourceType) + "\" to \"" + typeName(targetType) + "\" with \"as\"", expression.span)
    return finish(state, expression, unknownType())
  }
  return finish(state, expression, resultType(targetType, primitive("string")))
}

export function isValidAsNarrow(state: CheckerState, source: ResolvedType, target: ResolvedType): bool {
  if sameType(source, target) { return true }
  if isNumeric(source) && isNumeric(target) { return true }
  case source {
    _: JsonValueResolvedType -> { return isJsonAsTarget(state, target) }
    union_: UnionResolvedType -> {
      for member of union_.types { if isValidAsNarrow(state, member, target) { return true } }
    }
    _: InterfaceType -> {
      case target {
        _: ClassType -> { return true }
        _ -> { }
      }
    }
    _ -> { }
  }
  return false
}

export function isJsonAsTarget(state: CheckerState, target: ResolvedType): bool {
  case target {
    primitiveType: PrimitiveType -> {
      return primitiveType.name == "bool" || primitiveType.name == "string" || isNumeric(primitiveType)
    }
    array: ArrayResolvedType -> { return isJsonValueType(array.elementType) }
    map: MapResolvedType -> { return sameType(map.keyType, primitive("string")) && isJsonValueType(map.valueType) }
    _: JsonValueResolvedType -> { return true }
    _ -> { return false }
  }
  return false
}

export function nonNoneType(state: CheckerState, value: ResolvedType): ResolvedType {
  case value {
    union_: UnionResolvedType -> {
      let members: ResolvedType[] = []
      for member of union_.types { if member.kind != "none" { members.push(member) } }
      if members.length == 1 { return members[0] }
      if members.length > 1 { return unionType(members) }
      return unknownType()
    }
    _: NoneType -> { return unknownType() }
    _ -> { return value }
  }
  return unknownType()
}

export function hasNoneMember(state: CheckerState, value: UnionResolvedType): bool {
  for member of value.types { if member.kind == "none" { return true } }
  return false
}

export function checkAssignment(state: CheckerState, expression: AssignmentExpression, scope: Scope): ResolvedType {
  targetType := checkExpression(state, expression.target, scope, none)
  // Assignment emission needs the target decoration to choose representation
  // conversions, especially when a member is a nullable AST union field.
  finish(state, expression.target, targetType)
  case expression.target {
    identifier: Identifier -> {
      binding := lookup(scope, identifier.name)
      if binding != none {
        identifier.resolvedBinding = binding
        identifier.resolvedType = optionalResolvedType(binding!.type_)
      }
    }
    _ -> { }
  }
  value := checkExpression(state, expression.value, scope, optionalResolvedType(targetType))
  validateAssignmentOperator(state, expression.operator, targetType, value, expression.span)
  case expression.target {
    identifier: Identifier -> {
      target := lookup(scope, identifier.name)
      if target == none { typeError(state, "Unknown assignment target '" + identifier.name + "'", identifier.span) }
      else {
        validateAssignmentBinding(state, target!, identifier.span)
        if expression.operator == "=" && !isAssignableWithInterfaces(state.result, value, target!.type_) { typeError(state, "Cannot assign " + typeName(value) + " to " + typeName(target!.type_), expression.span) }
      }
    }
    index: IndexExpression -> {
      objectType := checkExpression(state, index.object, scope, none)
      case objectType {
        array: ArrayResolvedType -> {
          checkExpression(state, index.index, scope, optionalResolvedType(primitive("int")))
          if array.readonly_ { typeError(state, "Cannot assign through readonly array", expression.span) }
          if expression.operator == "=" && !isAssignableWithInterfaces(state.result, value, array.elementType) { typeError(state, "Cannot assign " + typeName(value) + " to " + typeName(array.elementType), expression.span) }
        }
        map: MapResolvedType -> {
          key := checkExpression(state, index.index, scope, optionalResolvedType(map.keyType))
          if !isAssignableWithInterfaces(state.result, key, map.keyType) { typeError(state, "Cannot use " + typeName(key) + " as map key " + typeName(map.keyType), index.index.span) }
          if map.readonly_ { typeError(state, "Cannot assign through readonly map", expression.span) }
          if expression.operator == "=" && !isAssignableWithInterfaces(state.result, value, map.valueType) { typeError(state, "Cannot assign " + typeName(value) + " to " + typeName(map.valueType), expression.span) }
        }
        _ -> { typeError(state, "Index assignment requires an array or map", expression.span) }
      }
    }
    member: MemberExpression -> {
      // The target was already checked above. In particular, do not resolve an
      // inaccessible actor field again or add assignment errors to that failure.
      if targetType.kind == "unknown" { return finish(state, expression, value) }
      objectType := member.object.resolvedType ?? unknownType()
      fieldBinding := fieldAssignmentBinding(state, objectType, member.property, targetType, member.span)
      if fieldBinding != none { validateAssignmentBinding(state, fieldBinding!, member.span) }
      else if objectType.kind != "unknown" && objectType.kind != "never" { typeError(state, "Member '" + member.property + "' is not an assignable field", member.span) }
      if expression.operator == "=" && !isAssignableWithInterfaces(state.result, value, targetType) { typeError(state, "Cannot assign " + typeName(value) + " to " + typeName(targetType), expression.span) }
    }
    _ -> { typeError(state, "Assignment target must be a binding", expression.target.span) }
  }
  if targetType.kind == "never" || value.kind == "never" { return finish(state, expression, neverType()) }
  return finish(state, expression, if expression.operator == "=" then value else targetType)
}

function validateAssignmentOperator(state: CheckerState, operator: string, target: ResolvedType, value: ResolvedType, span: SourceSpan): none {
  if operator == "=" || target.kind == "unknown" || value.kind == "unknown" { return }
  if operator == "??=" {
    if !isFallibleType(target) { typeError(state, "Operator '??=' requires a nullable or Result assignment target, got " + typeName(target), span); return }
    case target {
      result: ResultResolvedType -> {
        if !isAssignableWithInterfaces(state.result, value, target) && !isAssignableWithInterfaces(state.result, value, result.valueType) {
          typeError(state, "Cannot assign " + typeName(value) + " through ??= to " + typeName(target), span)
        }
      }
      _ -> { if !isAssignableWithInterfaces(state.result, value, target) { typeError(state, "Cannot assign " + typeName(value) + " through ??= to " + typeName(target), span) } }
    }
    return
  }
  base := operator.substring(0, operator.length - 1)
  result := binaryOperatorType(state, base, target, value, span)
  if !isAssignableWithInterfaces(state.result, result, target) { typeError(state, "Operator '" + operator + "' produces " + typeName(result) + ", which cannot be assigned to " + typeName(target), span) }
}

function binaryOperatorType(state: CheckerState, operator: string, left: ResolvedType, right: ResolvedType, span: SourceSpan): ResolvedType {
  if operator == "+" && typeName(left) == "string" && (typeName(right) == "string" || typeName(right) == "char") { return primitive("string") }
  if isNumericOperand(left) && isNumericOperand(right) {
    validateNumericOperator(state, operator, left, right, span)
    return numericOperationType(left, right, operator)
  }
  typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), span)
  return unknownType()
}

function validateNumericOperator(state: CheckerState, operator: string, left: ResolvedType, right: ResolvedType, span: SourceSpan): none {
  if numericOperatorAllowed(operator, left, right) { return }
  if operator == "/" { typeError(state, "Operator '/' requires at least one floating-point operand for every allowed type", span) }
  else { typeError(state, "Operator '" + operator + "' requires integer operands, got " + typeName(left) + " and " + typeName(right), span) }
}

function isInteger(type_: ResolvedType): bool { return isIntegerOperand(type_) }

function isNullableType(type_: ResolvedType): bool {
  case type_ {
    _: NoneType -> { return true }
    union_: UnionResolvedType -> { for member of union_.types { if member.kind == "none" { return true } } }
    _ -> { }
  }
  return false
}

function isFallibleType(type_: ResolvedType): bool {
  case type_ { _: ResultResolvedType -> { return true } _ -> { return isNullableType(type_) } }
}

function fallibleValueType(type_: ResolvedType): ResolvedType | none {
  case type_ {
    result: ResultResolvedType -> { return result.valueType }
    union_: UnionResolvedType -> {
      let members: ResolvedType[] = []
      for member of union_.types { if member.kind != "none" { members.push(member) } }
      if members.length == 1 { return members[0] }
      if members.length > 1 { return unionType(members) }
    }
    _: NoneType -> { return unknownType() }
    _ -> { }
  }
  return none
}

function orderedTypes(state: CheckerState, left: ResolvedType, right: ResolvedType): bool {
  if left.kind == "unknown" || right.kind == "unknown" { return true }
  if isNumericOperand(left) && isNumericOperand(right) { return true }
  if sameType(left, right) {
    case left {
      primitive_: PrimitiveType -> { return primitive_.name == "string" || primitive_.name == "char" }
      enum_: EnumType -> {
        declaration := declarationFor(state.result, enum_.symbol)
        if declaration != none {
          case declaration! {
            owner: EnumDeclaration -> { return owner.backingKind == "int" }
            _ -> { }
          }
        }
        return true
      }
      _: TypeParameterType -> { return true }
      _ -> { }
    }
  }
  return false
}

function typesOverlap(state: CheckerState, left: ResolvedType, right: ResolvedType): bool {
  if left.kind == "unknown" || right.kind == "unknown" { return true }
  case left {
    union_: UnionResolvedType -> {
      for member of union_.types { if typesOverlap(state, member, right) { return true } }
      return false
    }
    _ -> { }
  }
  case right {
    union_: UnionResolvedType -> {
      for member of union_.types { if typesOverlap(state, left, member) { return true } }
      return false
    }
    _ -> { }
  }
  return isAssignableWithInterfaces(state.result, left, right) || isAssignableWithInterfaces(state.result, right, left) || (isNumericOperand(left) && isNumericOperand(right))
}

function validateCaseRangeBound(state: CheckerState, bound: Expression | none, subjectType: ResolvedType, scope: Scope, span: SourceSpan): none {
  if bound == none { return }
  boundType := checkExpression(state, bound!, scope, optionalResolvedType(subjectType))
  if !isInteger(subjectType) || !isInteger(boundType) || !typesOverlap(state, subjectType, boundType) {
    typeError(state, "Case range bound of type \"" + typeName(boundType) + "\" cannot match subject type \"" + typeName(subjectType) + "\"", span)
  }
}
