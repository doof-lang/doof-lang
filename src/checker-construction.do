// One specialized constructor signature and field contract for all construction syntax.

import { checkArguments, positionalArguments, propertyArguments, SuppliedArgument } from "./checker-arguments"
import { ClassType, InterfaceType, NoneType, UnknownType, FunctionParamType, FunctionType, ResolvedType, ResultResolvedType, Scope, TypeParameterType, UnionResolvedType } from "./semantic"

import { ActorCreationExpression, CallArgument, CheckedConstruction, ConstructionDefault, ClassDeclaration, ConstructExpression, Identifier, ObjectProperty, FunctionDeclaration, SourceSpan, TupleLiteral } from "./ast"
import { CheckerState } from "./checker-state"
import { checkExpression } from "./checker-expressions"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { memberType } from "./checker-resolution"
import { resolveTypeArguments, validateTypeArgumentConstraints } from "./checker-annotations"
import { classModuleFor, findClassField, isAssignableWithInterfaces } from "./checker-interfaces"
import { declarationFor, hasObjectProperty, methodSignature, symbolFor, valueSymbolFor, valueUseDiagnostic } from "./checker-symbols"
import { actorType, classType, noneType, resultArmExpectation, resultArmType, resultType, sameType, substituteTypeParams, typeName, typeParameter, unknownType } from "./checker-types"
import { inferCallTypeArguments } from "./checker-call-inference"
import { discardDiagnosticsSince, finish, typeError } from "./checker-common"
import { checkPropertyValue, checkAssignableProperty, sameFixedFieldValue } from "./checker-properties"

export function resolveConstructor(state: CheckerState, owner: ClassType, useFactory: bool = true): CheckedConstruction {
  let declaration: ClassDeclaration | none = none
  if class_ := declarationFor(state.result, owner.symbol) as ClassDeclaration { declaration = class_ }
  let factory: FunctionDeclaration | none = none
  if useFactory && classDeclaration := declaration {
    for method of classDeclaration.methods { if method.name == "constructor" { factory = method; break } }
  }
  if factoryMethod := factory {
    signature := factoryMethod.resolvedType ?? methodSignature(factoryMethod, classModuleFor(state.result, owner.symbol), state.result, owner.symbol.typeParams)
    specialized := if classDeclaration := declaration then substituteTypeParams(signature, classDeclaration.typeParams, owner.typeArgs) else signature
    if fn := specialized as FunctionType {
      let defaults: ConstructionDefault[] = []
      for parameter of factoryMethod.params { defaults.push(ConstructionDefault { value: parameter.defaultValue }) }
      return CheckedConstruction { owner, declaration, factory, signature: fn, defaults }
    }
  }
  let params: FunctionParamType[] = []
  let defaults: ConstructionDefault[] = []
  if classDeclaration := declaration {
    for field of classDeclaration.fields {
      if field.static_ || field.const_ { continue }
      for name of field.names {
        defaults.push(ConstructionDefault { value: field.defaultValue })
        params.push(FunctionParamType { name, type_: memberType(state, owner, name, field.span, false), hasDefault: field.defaultValue != none })
      }
    }
  }
  return CheckedConstruction { owner, declaration, factory: none, signature: FunctionType { params: params.drainToReadonly(), returnType: owner }, defaults }
}

/**
 * Infers a generic class's type arguments from construction arguments, using
 * the constructor or field signature over the class's own type parameters.
 * Speculative diagnostics are discarded when inference fails, so the caller
 * reports one actionable error.
 */
export function inferConstructionTypeArguments(state: CheckerState, args: CallArgument[], owner: ClassType, declaration: ClassDeclaration, scope: Scope, expected: ResolvedType | none): readonly ResolvedType[] | none {
  let parameters: ResolvedType[] = []
  for name of declaration.typeParams { parameters.push(typeParameter(name)) }
  generic := classType(owner.name, owner.symbol, parameters.drainToReadonly())
  plan := resolveConstructor(state, generic, !insideConstructorFactory(scope, generic))
  signature := FunctionType { params: plan.signature.params, returnType: plan.signature.returnType, typeParams: declaration.typeParams }
  diagnosticMark := state.diagnostics.length
  inferred := inferCallTypeArguments(state, args, signature, scope, expected)
  if inferred == none { discardDiagnosticsSince(state, diagnosticMark) }
  return inferred
}

/**
 * Reports a construction whose type arguments cannot be inferred. Arguments
 * are still checked for their own errors; the result is unknown so the failure
 * does not cascade into diagnostics about unresolved members.
 */
export function cannotInferConstruction(state: CheckerState, declaration: ClassDeclaration, args: CallArgument[], scope: Scope, span: SourceSpan): none {
  for argument of args { checkExpression(state, argument.value, scope, none) }
  let names = ""
  for i of 0..<declaration.typeParams.length { names = names + (if i > 0 then ", " else "") + declaration.typeParams[i] }
  typeError(state, "Cannot infer type arguments for generic class '${declaration.name}'; provide them explicitly as ${declaration.name}<${names}>", span)
}

function constructionArguments(properties: ObjectProperty[]): CallArgument[] {
  let result: CallArgument[] = []
  for property of properties {
    // A shorthand property `{ handler }` reads the binding of the same name.
    value := property.value ?? Identifier { kind: "identifier", name: property.name, span: property.span }
    result.push(CallArgument { name: property.name, value, span: property.span })
  }
  return result
}

export function insideConstructorFactory(scope: Scope, class_: ClassType): bool {
  let current: Scope | none = scope
  while current != none {
    if current!.functionName != "" {
      if current!.functionName != "constructor" { return false }
      if current!.thisType == none { return false }
      case current!.thisType! {
        owner: ClassType -> { return owner.symbol.module == class_.symbol.module && owner.symbol.name == class_.symbol.name }
        _ -> { return false }
      }
    }
    current = current!.parent
  }
  return false
}

export function checkConstruct(state: CheckerState, expression: ConstructExpression, scope: Scope, expected: ResolvedType | none): ResolvedType {
  if expression.type_ == "Success" || expression.type_ == "Failure" {
    if spread := expression.spread {
      expression.resolvedSpreadType = checkExpression(state, spread, scope, none)
      typeError(state, "${expression.type_} construction does not support field spread", spread.span)
    }
    // A surrounding Result or matching arm types the payload; otherwise the
    // payload determines a standalone arm type.
    expectation := resultArmExpectation(expression.type_, expected)
    let valueType: ResolvedType = expectation.payload ?? noneType()
    for property of expression.args {
      valueType = checkAssignableProperty(state, property, scope, expectation.payload)
      if payload := expectation.payload { valueType = payload }
    }
    if expression.args.length == 0 && valueType.kind != "none" && valueType.kind != "unknown" {
      typeError(state, "${expression.type_} {} needs a value for ${typeName(expectation.result ?? resultArmType(expression.type_, valueType))}", expression.span)
    }
    return finish(state, expression, expectation.result ?? resultArmType(expression.type_, valueType))
  }
  symbol := valueSymbolFor(state.info!, expression.type_)
  if symbol == none {
    message := valueUseDiagnostic(state.info!, expression.type_)
    typeError(state, if message == "" then "Unknown constructed type '" + expression.type_ + "'" else message, expression.span)
    return finish(state, expression, unknownType())
  }
  if declaration := declarationFor(state.result, symbol!) {
    if classDeclaration := declaration as ClassDeclaration { expression.resolvedClass = classDeclaration }
  }
  let resolvedTypeArgs = resolveTypeArguments(state, expression.typeArgs, scope)
  if resolvedTypeArgs.length == 0 && expected != none {
    if expectedClass := expected! as ClassType {
      if expectedClass.symbol.module == symbol!.module && expectedClass.symbol.name == symbol!.name {
        resolvedTypeArgs = expectedClass.typeArgs
      }
    }
  }
  generic := expression.resolvedClass
  if resolvedTypeArgs.length == 0 && generic != none && generic!.typeParams.length > 0 {
    args := constructionArguments(expression.args)
    inferred := inferConstructionTypeArguments(state, args, classType(expression.type_, symbol!, []), generic!, scope, expected)
    if inferred == none {
      cannotInferConstruction(state, generic!, args, scope, expression.span)
      return finish(state, expression, unknownType())
    }
    resolvedTypeArgs = inferred!
  }
  if resolvedClass := expression.resolvedClass {
    validateTypeArgumentConstraints(state, resolvedClass.typeParams, resolvedClass.typeParamConstraints, resolvedTypeArgs, expression.span, classModuleFor(state.result, symbol!), scope)
  }
  constructed := classType(expression.type_, symbol!, resolvedTypeArgs)
  expression.resolvedConstructedType = constructed
  checkConstructionSpread(state, expression, scope)
  plan := resolveConstructor(state, constructed, !insideConstructorFactory(scope, constructed))
  expression.resolvedConstruction = plan
  if constructorMethod := plan.factory {
    expression.resolvedConstructor = constructorMethod
    validateConstructorVisibility(state, constructed, constructorMethod, expression.span)
    let spread: FunctionParamType[] = []
    for parameter of plan.signature.params {
      if hasObjectProperty(expression.args, parameter.name) { continue }
      if spreadType := constructionSpreadFieldType(state, expression, parameter.name) { spread.push(FunctionParamType { name: parameter.name, type_: spreadType, hasDefault: false }) }
    }
    checkArguments(state, propertyArguments(expression.args), plan.signature.params, scope, expression.span,
      "Class \"${constructed.name}\"", "Argument", true, true, spread.drainToReadonly(), expression.spread?.span, true)
    return finish(state, expression, plan.signature.returnType)
  }
  if resolvedClass := expression.resolvedClass { checkClassProperties(state, expression.args, scope, constructed, resolvedClass, expression.span, false, expression) }
  return finish(state, expression, constructed)
}

export function validateConstructorVisibility(state: CheckerState, owner: ClassType, constructor: FunctionDeclaration, span: SourceSpan): none {
  if constructor.private_ && owner.symbol.module != state.info!.path {
    typeError(state, "Constructor for \"${owner.name}\" is private", span)
  }
}

export function checkClassProperties(state: CheckerState, properties: ObjectProperty[], scope: Scope, constructed: ClassType, declaration: ClassDeclaration, span: SourceSpan, structural: bool = false, spread: ConstructExpression | none = none): none {
  let used: string[] = []
  for property of properties {
    if used.contains(property.name) { typeError(state, "Duplicate field '${property.name}' in ${declaration.name} construction", property.span) }
    used.push(property.name)
    field := findClassField(declaration.fields, property.name)
    if field == none || field!.static_ || (!structural && field!.const_) {
      typeError(state, "Unknown field '${property.name}' for ${declaration.name}", property.span)
      checkPropertyValue(state, property, scope, none)
      continue
    }
    expected := memberType(state, constructed, property.name, property.span)
    checkAssignableProperty(state, property, scope, expected)
    if structural && field!.const_ {
      if property.value == none || field!.defaultValue == none || !sameFixedFieldValue(property.value!, field!.defaultValue!) {
        typeError(state, "Field '${property.name}' must match its literal-valued declaration", property.span)
      }
    }
  }
  for field of declaration.fields {
    if field.static_ || (!structural && field.const_) { continue }
    for name of field.names {
      if used.contains(name) { continue }
      spreadType := if spread == none then none else constructionSpreadFieldType(state, spread!, name)
      if spreadType == none {
        if field.const_ || field.defaultValue == none { typeError(state, "Missing required field '${name}'", span) }
      }
      else {
        expected := memberType(state, constructed, name, span)
        if !isAssignableWithInterfaces(state.result, spreadType!, expected) {
          typeError(state, "Cannot assign spread field ${typeName(spreadType!)} to ${typeName(expected)}", spread!.spread!.span)
        }
      }
    }
  }
}

function checkConstructionSpread(state: CheckerState, expression: ConstructExpression, scope: Scope): none {
  if expression.spread == none { return }
  spreadType := checkExpression(state, expression.spread!, scope, none)
  expression.resolvedSpreadType = spreadType
  case spreadType {
    _: ClassType -> { }
    _: InterfaceType -> { }
    _: UnknownType -> { }
    _ -> { typeError(state, "Field spread requires a class, struct, or interface value; got ${typeName(spreadType)}", expression.spread!.span) }
  }
}

function constructionSpreadFieldType(state: CheckerState, expression: ConstructExpression, name: string): ResolvedType | none {
  if expression.spread == none || expression.resolvedSpreadType == none { return none }
  spreadType := expression.resolvedSpreadType!
  let supported = false
  case spreadType {
    _: ClassType -> { supported = true }
    _: InterfaceType -> { supported = true }
    _ -> { }
  }
  if !supported { return none }
  fieldType := memberType(state, spreadType, name, expression.spread!.span)
  if fieldType.kind == "unknown" { return none }
  if !expression.spreadFields.contains(name) { expression.spreadFields.push(name) }
  return fieldType
}

// Visibility uses the same stored-field parameter order used for validation.
export function validateFieldArguments(state: CheckerState, plan: CheckedConstruction, owner: ClassType, args: SuppliedArgument[]): none {
  if plan.factory != none || plan.declaration == none || owner.symbol.module == state.info!.path { return }
  for i of 0..<args.length {
    argument := args[i]
    name := argument.name ?? (if i < plan.signature.params.length then plan.signature.params[i].name else "")
    if field := findClassField(plan.declaration!.fields, name) && field.private_ {
      typeError(state, "Field '${name}' is private to module '${owner.symbol.module}'", argument.span)
    }
  }
}

/**
 * The class or struct a positional literal `(a, b)` constructs when its
 * expected type names one, directly or as the present arm of `T | none`.
 * Anything else (unions of several classes, interfaces, tuples) leaves the
 * literal an ordinary Tuple. The expected class may mention the enclosing
 * declaration's own type parameters; call inference never supplies an
 * expected type that still mentions a parameter it is inferring.
 */
export function positionalLiteralClass(expected: ResolvedType | none): ClassType | none {
  if expected == none { return none }
  case expected! {
    class_: ClassType -> { return class_ }
    union_: UnionResolvedType -> {
      let found: ClassType | none = none
      for member of union_.types {
        case member {
          _: NoneType -> { }
          class_: ClassType -> {
            if found != none { return none }
            found = class_
          }
          _ -> { return none }
        }
      }
      return found
    }
    _ -> { return none }
  }
}

/** Checks `(a, b)` against an expected class exactly like the positional call `Point(a, b)`. */
export function checkPositionalLiteralConstruction(state: CheckerState, expression: TupleLiteral, scope: Scope, class_: ClassType): ResolvedType {
  construction := resolveConstructor(state, class_, !insideConstructorFactory(scope, class_))
  expression.resolvedConstruction = construction
  expression.resolvedClass = construction.declaration
  if factory := construction.factory { validateConstructorVisibility(state, class_, factory, expression.span) }
  let args: SuppliedArgument[] = []
  for element of expression.elements { args.push(SuppliedArgument { name: none, value: element, span: element.span }) }
  validateFieldArguments(state, construction, class_, args)
  kind := if class_.symbol.kind == "struct" then "Struct" else "Class"
  checkArguments(state, args, construction.signature.params, scope, expression.span, "${kind} \"${class_.name}\"")
  return finish(state, expression, construction.signature.returnType)
}

/** Checks 'Actor<T>(...)' creation: T's constructor, its arguments, and what may cross into the actor. */
export function checkActorCreation(state: CheckerState, actorCreation: ActorCreationExpression, scope: Scope): ResolvedType {
  symbol := symbolFor(state.info!, actorCreation.className)
  if symbol == none || symbol!.kind != "class" {
    for argument of actorCreation.args { checkExpression(state, argument, scope, none) }
    typeError(state, "Actor requires a class type; \"${actorCreation.className}\" is not a class", actorCreation.span)
    return finish(state, actorCreation, unknownType())
  }
  inner := classType(actorCreation.className, symbol!)
  construction := resolveConstructor(state, inner)
  actorCreation.resolvedConstruction = construction
  actorCreation.resolvedConstructor = construction.factory
  if factory := construction.factory {
    validateConstructorVisibility(state, inner, factory, actorCreation.span)
    if !sameType(construction.signature.returnType, inner) {
      typeError(state, "Actor constructor factory for \"${inner.name}\" must return ${inner.name} directly", actorCreation.span)
    }
  }
  params := construction.signature.params
  validateFieldArguments(state, construction, inner, positionalArguments(actorCreation.args))
  checkArguments(state, positionalArguments(actorCreation.args), params, scope, actorCreation.span,
    "Actor \"${actorCreation.className}\"", "Actor constructor argument")
  for i of 0..<actorCreation.args.length {
    actual := actorCreation.args[i].resolvedType ?? unknownType()
    if violation := findActorBoundaryViolation(state.result, actual) {
      typeError(state,
        "Actor constructor argument " + string(i + 1) + " of type \"" + typeName(actual) + "\" cannot cross actor boundary: " + violation.reason,
        actorCreation.args[i].span,
      )
    }
  }
  return finish(state, actorCreation, actorType(inner))
}
