// Expression dispatch, operators, narrowing, and assignment checking.

import {
  ActorType, ArrayResolvedType, Binding, CheckResult, ClassType, EnumType, InterfaceType,
  Diagnostic, FunctionParamType, FunctionType,
  JsonValueResolvedType, MapResolvedType, NeverType, NoneType, PrimitiveType, PromiseType, RangeResolvedType, ResolvedType, ResultResolvedType, Scope, SemanticLocation, SemanticSpan, Symbol,
  StreamResolvedType, TupleResolvedType, UnionResolvedType, UnknownType, TypeParameterType,
} from "./semantic"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import {
  ArrayLiteral, ArrayType, AsExpression, AssignmentExpression, AstLocation, BinaryExpression, Block,
  BoolLiteral, CallExpression, CallerExpression, CharLiteral, ClassDeclaration, ClassField, ConstructExpression,
  ConstDeclaration, ContinueStatement, DestructuringStatement, DoubleLiteral,
  DotShorthand, EnumDeclaration, ExportDeclaration, ExportList, Expression, ExpressionStatement,
  FloatLiteral, ForOfStatement, ForStatement, FunctionDeclaration, AstFunctionType,
  IfExpression, IfStatement, ImmutableBinding, Identifier, ImportDeclaration,
  IndexExpression, IntLiteral, InterfaceDeclaration, LetDeclaration,
  LambdaExpression, LongLiteral, MemberExpression, NamedType, NoneLiteral,
  NamedImport, NamespaceImport, ObjectLiteral, ObjectProperty, Program,
  ReadonlyDeclaration, ReturnStatement, SourceSpan, Statement, StringLiteral,
  ThisExpression, TupleLiteral, TypeAliasDeclaration, TypeAnnotation,
  UnaryExpression, UnionType, WhileStatement, WithBinding, WithStatement, BreakStatement,
  YieldStatement, YieldBlockExpression, CatchExpression, CaseArm, CaseExpression, CasePattern, CaseStatement, RangePattern, TypePattern, ValuePattern, WildcardPattern,
  TryStatement,
  AsyncExpression, RetireExpression, ActorCreationExpression, Parameter,
} from "./ast"
import {
  actorType, applyDeepReadonly, arrayType, classType, enumType, functionType, interfaceType, isAssignable, isNumeric, joinTypes,
  isJsonValueType, jsonObjectType, jsonValueType, mapType, resultType, streamType,
  neverType, noneType, numericResult, primitive, promiseType, rangeType, sameType, tupleType, typeName, unionType,
  substituteTypeParams, typeParameter, unknownType,
} from "./checker-types"
import { canGenerateJsonDeserialization, canGenerateJsonSerialization } from "./json-semantics"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { collectRetiredActorBindings, reportRetiredActorUses } from "./checker-actor-lifecycle"


import { CheckerState } from "./checker-state"
import { checkFunction, checkBlock } from "./checker-statements"
import { checkCall, checkLambda, checkConstruct, callableField } from "./checker-calls"
import { checkArray, checkObject } from "./checker-literals"
import { resolveType, memberType, indexType } from "./checker-resolution"
import { deprecatedNoneAlias, finish, typeError, requireBool } from "./checker-common"
import { builtinSourceLocationType, casePatternName, optionalResolvedType, isNamespaceImport, isBuiltinNamespace, builtinNamespaceMemberType, namespaceMemberType, resolveAnnotation, declare, lookup, currentThisType, isBuiltinCallable, builtinCallable, hasTypeParam, typeParamConstraintName, typeParamConstraint, symbolFor, declarationFor } from "./checker-symbols"
import { constructorForClass, staticMemberOwner } from "./checker-generics"
import { checkerSemanticSpan } from "./checker-validation"

export function checkCaseExpression(state: CheckerState, expression: CaseExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  subjectType := checkExpression(state, expression.subject, scope, none)
  let inferredType: ResolvedType = unknownType()
  for arm of expression.arms {
    armScope := Scope { parent: scope }
    checkCasePatterns(state, arm.patterns, subjectType, armScope)
    let armExpected = expected
    if armExpected == none {
      case inferredType {
        _: UnknownType -> { }
        _ -> { armExpected = inferredType }
      }
    }
    let armType: ResolvedType = unknownType()
    case arm.body {
      block: Block -> {
        armScope.inValueYieldBlock = true
        armScope.yieldType = if armExpected == none then optionalResolvedType(unknownType()) else armExpected
        completes := checkBlock(state, block, armScope)
        if completes { typeError(state, "Block case-expression arms must yield a value on every path", block.span) }
        armType = armScope.yieldType ?? unknownType()
        if !completes && armType.kind == "unknown" { armType = neverType() }
      }
      bodyExpression: Expression -> { armType = checkExpression(state, bodyExpression, armScope, armExpected) }
    }
    if inferredType.kind == "unknown" { inferredType = armType } else { inferredType = joinTypes(inferredType, armType) }
  }
  expression.resolvedType = optionalResolvedType(inferredType)
  return inferredType
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
      value: ValuePattern -> { checkExpression(state, value.value, scope, optionalResolvedType(subjectType)) }
      range: RangePattern -> {
        if range.start != none { checkExpression(state, range.start!, scope, optionalResolvedType(subjectType)) }
        if range.end != none { checkExpression(state, range.end!, scope, optionalResolvedType(subjectType)) }
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
      let members: ResolvedType[] = []
      for errorType of errorTypes { members.push(errorType) }
      members.push(noneType())
      return finish(state, catch_, unionType(members))
    }
    _: IntLiteral -> {
      if expected != none { case expected! {
        primitiveExpected: PrimitiveType -> {
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
        if checkExpression(state, interpolation, scope, none).kind == "never" { diverges = true }
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
    _: CallerExpression -> { return finish(state, expression, builtinSourceLocationType()) }
    dot: DotShorthand -> { return checkDotShorthand(state, dot, expected) }
    identifier: Identifier -> { return checkIdentifier(state, identifier, scope) }
    binary: BinaryExpression -> { return checkBinary(state, binary, scope) }
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
            namespaceMember = namespaceMemberType(state.info!, identifier.name, member.property, state.result)
          } else if localBinding == none && isBuiltinNamespace(identifier.name) {
            namespaceName = identifier.name
            identifier.resolvedBinding = Binding {
              name: identifier.name,
              kind: "builtin-type-namespace",
              type_: primitive(identifier.name),
              mutable: false,
              span: checkerSemanticSpan(identifier.span),
              module: state.info!.path,
            }
            identifier.resolvedType = optionalResolvedType(primitive(identifier.name))
            namespaceMember = builtinNamespaceMemberType(identifier.name, member.property)
          } else {
            objectType = checkExpression(state, member.object, scope, none)
          }
        }
        _ -> { objectType = checkExpression(state, member.object, scope, none) }
      }
      if namespaceMember != none {
        if namespaceMember!.kind == "unknown" {
          typeError(state, "Namespace \"" + namespaceName + "\" has no member \"" + member.property + "\"", member.span)
        }
        return finish(state, expression, namespaceMember!)
      }
      if objectType.kind == "never" { return finish(state, expression, neverType()) }
      diagnosticCount := state.diagnostics.length
      memberValue := memberType(state, objectType, member.property, member.span)
      if memberValue.kind == "unknown" && objectType.kind != "unknown" && state.diagnostics.length == diagnosticCount {
        typeError(state, "Type \"" + typeName(objectType) + "\" has no member \"" + member.property + "\"", member.span)
      }
      member.resolvedStaticOwner = staticMemberOwner(objectType, member.property, state.result)
      member.resolvedCallableField = callableField(state, objectType, member.property)
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
      for item of tuple.elements {
        itemType := checkExpression(state, item, scope, none)
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
      return finish(state, expression, joinTypes(thenType, elseType))
    }
    case_: CaseExpression -> { return finish(state, expression, checkCaseExpression(state, case_, scope, expected)) }
    construct: ConstructExpression -> { return checkConstruct(state, construct, scope, expected) }
    async_: AsyncExpression -> {
      case async_.expression {
        block: Block -> {
          checkBlock(state, block, scope)
          typeError(state, "`async` is only valid for actor method calls; use a temporary actor for background work", async_.span)
          return finish(state, expression, promiseType(unknownType()))
        }
        inner: Expression -> {
          innerType := checkExpression(state, inner, scope, none)
          let actorCall = false
          case inner {
            call: CallExpression -> {
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
            }
            _ -> { }
          }
          if !actorCall { typeError(state, "`async` is only valid for actor method calls; use a temporary actor for background work", async_.span) }
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
      constructorMethod := constructorForClass(inner, state.result)
      for i of 0..<actorCreation.args.length {
        let expectedArgument: ResolvedType | none = none
        if constructorMethod != none && i < constructorMethod!.params.length { expectedArgument = constructorMethod!.params[i].resolvedType }
        actual := checkExpression(state, actorCreation.args[i], scope, expectedArgument)
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
    _: ThisExpression -> { return finish(state, expression, currentThisType(scope)) }
    _ -> { return finish(state, expression, unknownType()) }
  }
  return unknownType()
}

export function checkDotShorthand(state: CheckerState, expression: DotShorthand, expected: ResolvedType | none): ResolvedType {
  if expected == none {
    typeError(state, "Cannot resolve shorthand ." + expression.name + " without an expected class or enum type", expression.span)
    return finish(state, expression, unknownType())
  }
  case expected! {
    enum_: EnumType -> {
      declaration := declarationFor(state.result, enum_.symbol)
      let found = enum_.name == "ParseError" && enum_.symbol.module == "<builtin>" && builtinParseErrorVariant(expression.name)
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
      value := memberType(state, class_, expression.name, expression.span)
      if staticMemberOwner(class_, expression.name, state.result) == none {
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

function builtinParseErrorVariant(name: string): bool {
  return name == "InvalidFormat" || name == "Overflow" || name == "Underflow" || name == "EmptyInput"
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
    typeError(state, "Unknown identifier '" + identifier.name + "'", identifier.span)
    return finish(state, identifier, unknownType())
  }
  identifier.resolvedBinding = binding
  return finish(state, identifier, binding.type_)
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

export function checkBinary(state: CheckerState, expression: BinaryExpression, scope: Scope): ResolvedType {
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
          right = checkExpression(state, expression.right, scope, none)
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
    return finish(state, expression, coalescedType(state, left, right))
  }
  if right.kind == "never" { return finish(state, expression, neverType()) }
  if operator == "..<" || operator == ".." {
    validateRangeOperand(state, operator, "left", left, expression.left.span)
    validateRangeOperand(state, operator, "right", right, expression.right.span)
    return finish(state, expression, rangeType())
  }
  if operator == "==" || operator == "!=" || operator == "<" || operator == "<=" || operator == ">" || operator == ">=" {
    return finish(state, expression, primitive("bool"))
  }
  if operator == "+" && typeName(left) == "string" && (typeName(right) == "string" || typeName(right) == "char" || typeName(right) == "unknown") { return finish(state, expression, primitive("string")) }
  if operator == "+" && typeName(right) == "string" && (typeName(left) == "char" || typeName(left) == "unknown") { return finish(state, expression, primitive("string")) }
  if isNumeric(left) && isNumeric(right) { return finish(state, expression, numericResult(left, right)) }
  typeError(state, "Operator '" + operator + "' is not defined for " + typeName(left) + " and " + typeName(right), expression.span)
  return finish(state, expression, unknownType())
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

export function coalescedType(state: CheckerState, left: ResolvedType, right: ResolvedType): ResolvedType {
  case left {
    union_: UnionResolvedType -> {
      let nonNull: ResolvedType | none = none
      for member of union_.types {
        if member.kind != "none" {
          nonNull = if nonNull == none then member else joinTypes(nonNull!, member)
        }
      }
      if nonNull == none { return right }
      return joinTypes(nonNull!, right)
    }
    _: NoneType -> { return right }
    _ -> { return left }
  }
  return unknownType()
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
    return finish(state, expression, nonNoneType(state, value))
  }
  if expression.operator == "!" { requireBool(state, value, expression.span); return finish(state, expression, primitive("bool")) }
  if expression.operator == "+" || expression.operator == "-" || expression.operator == "~" {
    if !isNumeric(value) { typeError(state, "Unary '" + expression.operator + "' requires a numeric operand", expression.span) }
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
  case expression.target {
    identifier: Identifier -> {
      target := lookup(scope, identifier.name)
      if target == none { typeError(state, "Unknown assignment target '" + identifier.name + "'", identifier.span) }
      else {
        if !target!.mutable { typeError(state, "Cannot assign to immutable binding '" + identifier.name + "'", identifier.span) }
        if expression.operator == "=" && !isAssignable(value, target!.type_) { typeError(state, "Cannot assign " + typeName(value) + " to " + typeName(target!.type_), expression.span) }
      }
    }
    index: IndexExpression -> {
      objectType := checkExpression(state, index.object, scope, none)
      case objectType {
        array: ArrayResolvedType -> {
          checkExpression(state, index.index, scope, optionalResolvedType(primitive("int")))
          if array.readonly_ { typeError(state, "Cannot assign through readonly array", expression.span) }
          if expression.operator == "=" && !isAssignable(value, array.elementType) { typeError(state, "Cannot assign " + typeName(value) + " to " + typeName(array.elementType), expression.span) }
        }
        map: MapResolvedType -> {
          key := checkExpression(state, index.index, scope, optionalResolvedType(map.keyType))
          if !isAssignable(key, map.keyType) { typeError(state, "Cannot use " + typeName(key) + " as map key " + typeName(map.keyType), index.index.span) }
          if map.readonly_ { typeError(state, "Cannot assign through readonly map", expression.span) }
          if expression.operator == "=" && !isAssignable(value, map.valueType) { typeError(state, "Cannot assign " + typeName(value) + " to " + typeName(map.valueType), expression.span) }
        }
        _ -> { typeError(state, "Index assignment requires an array or map", expression.span) }
      }
    }
    member: MemberExpression -> {
      checkExpression(state, member.object, scope, none)
      targetType := memberType(state, checkExpression(state, member.object, scope, none), member.property, member.span)
      if expression.operator == "=" && !isAssignable(value, targetType) { typeError(state, "Cannot assign " + typeName(value) + " to " + typeName(targetType), expression.span) }
    }
    _ -> { typeError(state, "Assignment target must be a binding", expression.target.span) }
  }
  if targetType.kind == "never" || value.kind == "never" { return finish(state, expression, neverType()) }
  return finish(state, expression, value)
}
