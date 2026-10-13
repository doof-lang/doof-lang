// Expression dispatch, literals, identifiers, and implicit method bindings.

import { ActorCreationExpression, ArrayLiteral, AsExpression, AssignmentExpression, AsyncExpression, BinaryExpression, BoolLiteral, CallExpression, CallerExpression, CaseExpression, CatchExpression, CharLiteral, ClassDeclaration, ConstructExpression, DotShorthand, DoubleLiteral, Expression, FloatLiteral, Identifier, IfExpression, IndexExpression, IntLiteral, LambdaExpression, LongLiteral, MemberExpression, NoneLiteral, ObjectLiteral, RetireExpression, SourceSpan, StringLiteral, ThisExpression, TupleLiteral, UnaryExpression, YieldBlockExpression } from "./ast"
import { checkAssignment } from "./checker-assignment"
import { checkAsync } from "./checker-async"
import { checkCall, checkLambda } from "./checker-calls"
import { checkCaseExpression } from "./checker-case"
import { deprecatedNoneAlias, finish, requireBool, retainEditorScope, typeError } from "./checker-common"
import { checkActorCreation, checkConstruct, checkPositionalLiteralConstruction, positionalLiteralClass } from "./checker-construction"
import { instantiateGenericReference } from "./checker-generic-references"
import { pathType } from "./checker-inference"
import { checkArray, checkObject } from "./checker-literals"
import { checkDotShorthand, checkIndex, checkMember } from "./checker-members"
import { checkAs, checkBinary, checkUnary } from "./checker-operators"
import { CheckerState } from "./checker-state"
import { checkBlock, checkFunction } from "./checker-statements"
import { builtinCallable, builtinSourceLocationType, currentThisType, declarationFor, declare, hasTypeParam, isBuiltinCallable, lookup, optionalResolvedType, resolveAnnotation, typeParamConstraint, typeParamConstraintName, valueUseDiagnostic } from "./checker-symbols"
import { functionType, isStringInterpolatable, neverType, noneType, primitive, tupleType, typeName, typeParameter, unknownType } from "./checker-types"
import { checkerSemanticSpan } from "./checker-validation"
import { ActorType, Binding, ClassType, Diagnostic, FunctionParamType, PrimitiveType, ResolvedType, Scope, TupleResolvedType } from "./semantic"

export function checkExpression(state: CheckerState, expression: Expression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  calleePosition := state.checkingCallee
  state.checkingCallee = false
  retainEditorScope(state, scope, expression.span)
  if state.editorMode { state.info!.editorExpressions.push(expression) }
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
    identifier: Identifier -> { return finish(state, identifier, instantiateGenericReference(state, identifier, checkIdentifier(state, identifier, scope), expected, scope, calleePosition)) }
    binary: BinaryExpression -> { return checkBinary(state, binary, scope, expected) }
    unary: UnaryExpression -> { return checkUnary(state, unary, scope) }
    as_: AsExpression -> { return checkAs(state, as_, scope) }
    assignment: AssignmentExpression -> { return checkAssignment(state, assignment, scope) }
    member: MemberExpression -> { return checkMember(state, member, scope, expected, calleePosition) }
    index: IndexExpression -> { return checkIndex(state, index, scope) }
    call: CallExpression -> { return checkCall(state, call, scope, expected) }
    array: ArrayLiteral -> { return checkArray(state, array, scope, expected) }
    tuple: TupleLiteral -> {
      constructed := positionalLiteralClass(expected)
      if constructed != none { return checkPositionalLiteralConstruction(state, tuple, scope, constructed!) }
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
    async_: AsyncExpression -> { return checkAsync(state, async_, scope, expected) }
    retire_: RetireExpression -> {
      retiredType := checkExpression(state, retire_.actor, scope, none)
      case retiredType {
        actor: ActorType -> { return finish(state, expression, actor.innerClass) }
        _ -> { typeError(state, "Cannot retire non-actor type \"" + typeName(retiredType) + "\"", retire_.span); return finish(state, expression, unknownType()) }
      }
    }
    actorCreation: ActorCreationExpression -> { return checkActorCreation(state, actorCreation, scope) }
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
  return finish(state, identifier, binding!.type_)
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
