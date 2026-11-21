import { retainEditorScope } from "./checker-common"
// Statement, declaration, scope, and control-flow checking.

import {
  ActorType, ArrayResolvedType, Binding, CheckResult, ClassType, EnumType, InterfaceType,
  Diagnostic, FunctionParamType, FunctionType,
  SerialValueResolvedType, MapResolvedType, NoneType, PrimitiveType, PromiseType, ResolvedType, ResultResolvedType, Scope, SemanticLocation, SemanticSpan, SetResolvedType, Symbol,
  StreamResolvedType, TupleResolvedType, UnionResolvedType, UnknownType, TypeParameterType, WeakResolvedType, ResolvedTypeConstraint,
} from "./semantic"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import {
  ArrayLiteral, ArrayType, AsExpression, AssignmentExpression, AstLocation, BinaryExpression, Block,
  BoolLiteral, CallExpression, CallerExpression, CharLiteral, ClassDeclaration, ClassField, ConstructExpression,
  ConstDeclaration, ContinueStatement, DestructuringStatement, DoubleLiteral,
  DotShorthand, EnumDeclaration, EnumVariant, ExportList, Expression, ExpressionStatement,
  FloatLiteral, ForOfStatement, ForStatement, FunctionDeclaration, AstFunctionType,
  IfExpression, IfStatement, ImmutableBinding, Identifier, ImportDeclaration, MockImportDirective,
  IndexExpression, IntLiteral, InterfaceDeclaration, InterfaceField, LetDeclaration,
  LambdaExpression, LongLiteral, MemberExpression, NamedType, NoneLiteral,
  NamedImport, ObjectLiteral, ObjectProperty, Program,
  ReadonlyDeclaration, ReturnStatement, SourceSpan, Statement, StringLiteral,
  ThisExpression, TupleLiteral, TypeAliasDeclaration, TypeAnnotation,
  UnaryExpression, UnionType, WhileStatement, WithBinding, WithStatement, BreakStatement,
  YieldStatement, YieldBlockExpression, YieldBlockAssignmentStatement, CaseArm, CaseExpression, CasePattern, CaseStatement, TypePattern, ValuePattern, WildcardPattern,
  TryStatement,
  AsyncExpression, RetireExpression, ActorCreationExpression, Parameter, TypeParameterConstraint,
} from "./ast"
import {
  actorType, applyDeepReadonly, arrayType, classType, enumType, functionType, interfaceType, isNumeric, isWeakReferenceTarget, joinTypes,
  isJsonValueType, jsonObjectType, jsonValueType, mapType, resultType, streamType,
  noneType, numericResult, primitive, promiseType, sameType, tupleType, displayTypeName, typeName, unionType,
  substituteTypeParams, typeParameter, unknownType, weakType,
} from "./checker-types"
import { canGenerateJsonDeserialization, canGenerateJsonSerialization } from "./json-semantics"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { collectRetiredActorBindings, reportRetiredActorUses } from "./checker-actor-lifecycle"


import { pathType } from "./checker-inference"
import { CheckerState, LambdaReturnObservation } from "./checker-state"
import { checkTry } from "./checker-try"
import { validateStructLayout } from "./checker-struct-layout"
import { includedFieldType, resolveFieldInclusions } from "./checker-inclusions"
import { checkCallerDefault, checkExpression, addClassMethods } from "./checker-expressions"
import { checkedCaseSubjectType, casePatternsExhaustive, checkCasePatterns } from "./checker-case"
import { checkOmittedCollectionLiteral } from "./checker-literals"
import { constantInt } from "./checker-constants"
import { memberType, resolveMember } from "./checker-resolution"
import { resolveType } from "./checker-annotations"
import { deprecatedClassMethodFunction, deprecatedConstDeclaration, deprecatedConstField, typeError, requireBool, validateAssignmentBinding } from "./checker-common"
import { decorateAnnotationWithResolved, blockContainsLoopExit, classFieldBinding, fieldDisplayName, resolveAnnotation, declare, declareShadowing, lookup, returnScope, valueYieldScope, iterableElement, symbolFor, declarationFor } from "./checker-symbols"
import { symbolSpan, addImplementedInterfaceType, classSatisfiesConcreteInterface, isAssignableWithInterfaces } from "./checker-interfaces"
import { absenceErrorType, canBeAbsent, presentType } from "./absence-types"
import { checkerSemanticSpan } from "./checker-validation"
import { checkCondition, conditionElseScope, declareElseFailure } from "./checker-conditions"

export function checkStatement(state: CheckerState, statement: Statement, scope: Scope, inLoop: bool = false): bool {
  retainEditorScope(state, scope, statement.span)
  case statement {
    const_: ConstDeclaration -> { deprecatedConstDeclaration(state, const_); return checkValueDeclaration(state, const_, scope, "const", false, inLoop) }
    readonly_: ReadonlyDeclaration -> { return checkValueDeclaration(state, readonly_, scope, "readonly", false, inLoop) }
    binding: ImmutableBinding -> { return checkValueDeclaration(state, binding, scope, "immutable-binding", false, inLoop) }
    let_: LetDeclaration -> { return checkValueDeclaration(state, let_, scope, "let", true, inLoop) }
    fn: FunctionDeclaration -> { checkFunction(state, fn, scope, none); return true }
    class_: ClassDeclaration -> { checkClass(state, class_, scope); return true }
    interface_: InterfaceDeclaration -> { checkInterface(state, interface_, scope); return true }
    enum_: EnumDeclaration -> { checkEnum(state, enum_, scope); return true }
    alias: TypeAliasDeclaration -> {
      validateUniqueTypeParameters(state, alias.typeParams, alias.span)
      aliasScope := Scope { parent: scope }
      populateTypeParameters(state, aliasScope, alias.typeParams, alias.typeParamConstraints)
      resolvedAlias := resolveType(state, alias.type_, state.info!, aliasScope)
      alias.resolvedType = resolvedAlias
      return true
    }
    _: MockImportDirective -> { return true }
    if_: IfStatement -> {
      // Condition bindings are visible in their own body only; every later
      // condition and the else branch run when they are unbound.
      condition := checkCondition(state, if_.condition, scope)
      thenCompletes := checkBlock(state, if_.body, condition.scope, inLoop)
      let allComplete = thenCompletes
      let unbound: string[] = []
      for name of condition.boundNames { unbound.push(name) }
      let lastCondition = if_.condition
      for branch of if_.elseIfs {
        branchCondition := checkCondition(state, branch.condition, conditionElseScope(scope, unbound))
        let branchCompletes = checkBlock(state, branch.body, branchCondition.scope, inLoop)
        if branchCondition.type_.kind == "never" { branchCompletes = false }
        allComplete = allComplete || branchCompletes
        for name of branchCondition.boundNames { unbound.push(name) }
        lastCondition = branch.condition
      }
      if condition.type_.kind == "never" { return false }
      if if_.else_ == none { return true }
      elseScope := Scope { parent: conditionElseScope(scope, unbound) }
      declareElseFailure(state, if_, lastCondition, elseScope)
      elseCompletes := checkBlock(state, if_.else_!, elseScope, inLoop)
      return allComplete || elseCompletes
    }
    case_: CaseStatement -> { return checkCase(state, case_, scope, inLoop) }
    while_: WhileStatement -> {
      // Each iteration re-evaluates the condition and receives fresh bindings.
      condition := checkCondition(state, while_.condition, scope)
      conditionType := condition.type_
      loopScope := createLoopScope(state, condition.scope, while_.label, while_.span)
      checkBlock(state, while_.body, loopScope, true)
      if then_ := while_.then_ { checkBlock(state, then_, scope) }
      if conditionType.kind == "never" { return false }
      if literal := while_.condition as BoolLiteral {
        if literal.value && !blockContainsLoopExit(while_.body) { return false }
      }
      return true
    }
    for_: ForStatement -> {
      // Header bindings are visible to the condition, update and body only.
      headerScope := Scope { parent: scope }
      for init of for_.init { checkStatement(state, init, headerScope) }
      if condition := for_.condition {
        requireBool(state, checkExpression(state, condition, headerScope, none), condition.span)
      }
      for update of for_.update { checkExpression(state, update, headerScope, none) }
      loopScope := createLoopScope(state, headerScope, for_.label, for_.span)
      checkBlock(state, for_.body, loopScope, true)
      if then_ := for_.then_ { checkBlock(state, then_, scope) }
      return true
    }
    forOf: ForOfStatement -> {
      iterable := checkExpression(state, forOf.iterable, scope, none)
      element := forOfElement(state, iterable, forOf.iterable.span)
      if iterable.kind != "unknown" && iterable.kind != "never" && element.kind == "unknown" {
        typeError(state, "For-of requires an array, map, set, Range, or Stream value; got ${typeName(iterable)}", forOf.iterable.span)
      }
      if forOf.bindings.length > 1 {
        let validArity = false
        if tuple := element as TupleResolvedType { validArity = tuple.elements.length == forOf.bindings.length }
        if !validArity {
          typeError(state, "For-of destructuring requires a tuple with ${forOf.bindings.length} elements; got ${typeName(element)}", forOf.span)
        }
      }
      bodyScope := Scope { parent: scope }
      case element {
        tuple: TupleResolvedType -> {
          if tuple.elements.length == forOf.bindings.length {
            for i of 0..<forOf.bindings.length {
              name := forOf.bindings[i]
              if name != "_" { declareUserBinding(state, bodyScope, Binding { name, kind: "for-binding", type_: tuple.elements[i], mutable: false, span: checkerSemanticSpan(forOf.span), module: state.info!.path }, forOf.span) }
            }
          } else {
            for name of forOf.bindings { if name != "_" { declareUserBinding(state, bodyScope, Binding { name, kind: "for-binding", type_: element, mutable: false, span: checkerSemanticSpan(forOf.span), module: state.info!.path }, forOf.span) } }
          }
        }
        _ -> {
          for name of forOf.bindings { if name != "_" { declareUserBinding(state, bodyScope, Binding { name, kind: "for-binding", type_: element, mutable: false, span: checkerSemanticSpan(forOf.span), module: state.info!.path }, forOf.span) } }
        }
      }
      loopScope := createLoopScope(state, bodyScope, forOf.label, forOf.span)
      checkBlock(state, forOf.body, loopScope, true)
      if then_ := forOf.then_ { checkBlock(state, then_, scope) }
      return true
    }
    with_: WithStatement -> {
      bodyScope := Scope { parent: scope }
      let bindingsComplete = true
      for binding of with_.bindings {
        valueType := checkExpression(state, binding.value, bodyScope, none)
        if valueType.kind == "never" { bindingsComplete = false }
        declaredType := if binding.type_ == none then valueType else resolveType(state, binding.type_!, state.info!, scope)
        binding.resolvedType = declaredType
        if !isAssignableWithInterfaces(state.result, valueType, declaredType) { typeError(state, "Cannot assign ${displayTypeName(valueType)} to ${displayTypeName(declaredType)}", binding.span) }
        if binding.name == "_" {
          if _ := valueType as ResultResolvedType { typeError(state, "Scoped discard '_' cannot discard a Result; handle the Result before entering the with scope", binding.span) }
        }
        if binding.name != "_" {
          declareUserBinding(state, bodyScope, Binding { name: binding.name, kind: "with", type_: declaredType, mutable: false, span: checkerSemanticSpan(binding.span), module: state.info!.path }, binding.span)
        }
      }
      bodyCompletes := checkBlock(state, with_.body, bodyScope, inLoop)
      return bindingsComplete && bodyCompletes
    }
    return_: ReturnStatement -> { return checkReturn(state, return_, scope) }
    yield_: YieldStatement -> {
      target := valueYieldScope(scope)
      if target == none {
        typeError(state, "'yield' can only be used inside a value-producing block", yield_.span)
        checkExpression(state, yield_.value, scope, none)
        return false
      }
      expectedYield := target!.yieldExpectedType
      valueType := checkExpression(state, yield_.value, scope, expectedYield)
      target!.yieldType = pathType(state, target!.yieldType ?? unknownType(), valueType, expectedYield, yield_.span)
      return false
    }
    assignment: YieldBlockAssignmentStatement -> {
      if scope.parent == none {
        typeError(state, "'<-' yield-block reassignment is only allowed for local variables", assignment.span)
      }
      binding := lookup(scope, assignment.name)
      valueType := checkExpression(state, assignment.value, scope, binding?.type_)
      if binding == none {
        typeError(state, "Undefined identifier \"${assignment.name}\"", assignment.span)
        return true
      }
      validateAssignmentBinding(state, binding!, assignment.span)
      if !isAssignableWithInterfaces(state.result, valueType, binding!.type_) {
        typeError(state, "Cannot assign ${displayTypeName(valueType)} to ${displayTypeName(binding!.type_)}", assignment.span)
      }
      assignment.resolvedType = binding!.type_
      return true
    }
    expression: ExpressionStatement -> {
      expressionType := checkExpression(state, expression.expression, scope, none)
      case expressionType {
        // An assignment stores the Result in its target, which handles it.
        _: ResultResolvedType -> { if expression.expression.kind != "assignment-expression" { typeError(state, "Result value must be handled", expression.span) } }
        _ -> { }
      }
      return expressionType.kind != "never"
    }
    destructuring: DestructuringStatement -> {
      checkDestructuring(state, destructuring, scope, none)
      return true
    }
    try_: TryStatement -> { return checkTry(state, try_, scope) }
    continue_: ContinueStatement -> {
      if label := continue_.label {
        if !hasActiveLoopLabel(scope, label) { typeError(state, "Unknown loop label '${label}'", continue_.span) }
      } else if !inLoop { typeError(state, "Continue is only valid inside a loop", continue_.span) }
      return false
    }
    break_: BreakStatement -> {
      if label := break_.label {
        if !hasActiveLoopLabel(scope, label) { typeError(state, "Unknown loop label '${label}'", break_.span) }
      } else if !inLoop { typeError(state, "Break is only valid inside a loop", break_.span) }
      return false
    }
    block: Block -> { return checkBlock(state, block, scope, inLoop) }
    _ -> { return true }
  }
  return true
}

function createLoopScope(state: CheckerState, parent: Scope, label: string | none, span: SourceSpan): Scope {
  if name := label && hasActiveLoopLabel(parent, name) {
    typeError(state, "Loop label '${name}' is already active", span)
  }
  return Scope { parent, loopLabel: label }
}

function hasActiveLoopLabel(scope: Scope, label: string): bool {
  let current: Scope | none = scope
  while current != none {
    if current!.loopLabel == label { return true }
    if current!.functionName != "" { return false }
    current = current!.parent
  }
  return false
}

export function checkValueDeclaration(state: CheckerState, declaration: Statement, scope: Scope, kind: string, mutable: bool, inLoop: bool = false): bool {
  let name = ""
  let annotation: TypeAnnotation | none = none
  let value: Expression = NoneLiteral { kind: "none-literal", span: declaration.span }
  let span = declaration.span
  let elseBlock: Block | none = none
  let failureName: string | none = none
  case declaration {
    const_: ConstDeclaration -> { name = const_.name; annotation = const_.type_; value = const_.value }
    readonly_: ReadonlyDeclaration -> { name = readonly_.name; annotation = readonly_.type_; value = readonly_.value }
    binding: ImmutableBinding -> { name = binding.name; annotation = binding.type_; value = binding.value; elseBlock = binding.else_; failureName = binding.failureName }
    let_: LetDeclaration -> { name = let_.name; annotation = let_.type_; value = let_.value }
    _ -> { return true }
  }
  if _ := value as YieldBlockExpression {
    if scope.parent == none {
      typeError(state, "'<-' yield blocks are only allowed in local declarations", declaration.span)
    }
  }
  let inferredCollectionType: ResolvedType | none = none
  if typeAnnotation := annotation && elseBlock == none { inferredCollectionType = checkOmittedCollectionLiteral(state, typeAnnotation, value, scope) }
  // Resolve the annotation once: resolution reports its diagnostics.
  let annotatedType: ResolvedType | none = none
  if typeAnnotation := annotation && inferredCollectionType == none { annotatedType = resolveType(state, typeAnnotation, state.info!, scope) }
  let expectedValueType: ResolvedType | none = if elseBlock == none then annotatedType else none
  if kind == "readonly" && expectedValueType != none { expectedValueType = applyDeepReadonly(expectedValueType!) }
  let valueType = inferredCollectionType ?? checkExpression(state, value, scope, expectedValueType)
  let declaredType: ResolvedType = annotatedType ?? valueType
  if kind == "readonly" {
    valueType = applyDeepReadonly(valueType)
    declaredType = applyDeepReadonly(declaredType)
    value.resolvedType = valueType
    // Readonly collections are applied structurally above; nominal classes
    // must already be deeply immutable, matching readonly field validation.
    if violation := findActorBoundaryViolation(state.result, declaredType) {
      typeError(state, "Readonly binding \"${name}\" must be deeply immutable: ${violation.reason}", span)
    }
  }
  if typeAnnotation := annotation && inferredCollectionType != none { decorateAnnotationWithResolved(typeAnnotation, declaredType) }
  if handler := elseBlock {
    // Every absent layer (an outer none, a Failure, a none success value)
    // takes the else path, so the binding is the present value.
    let narrowedType: ResolvedType = unknownType()
    let failureType: ResolvedType | none = absenceErrorType(valueType)
    let validElseSubject = true
    if !canBeAbsent(valueType) {
      typeError(state, "declaration-else requires a Result or nullable expression", span)
      validElseSubject = false
    } else {
      narrowedType = presentType(valueType)
      if narrowedType.kind == "none" && name != "_" {
        typeError(state, "Cannot bind a none success value; use a discard binding '_ := expr else ...'", span)
      }
    }
    if annotation == none { declaredType = narrowedType }
    else if validElseSubject && !isAssignableWithInterfaces(state.result, narrowedType, declaredType) {
      typeError(state, "Cannot assign ${displayTypeName(narrowedType)} to ${displayTypeName(declaredType)}", span)
    }
    elseScope := Scope { parent: scope }
    if captured := failureName {
      if errorType := failureType {
        if captured != "_" {
          declare(elseScope, Binding { name: captured, kind: "else-failure", type_: errorType, mutable: false, span: checkerSemanticSpan(span), module: state.info!.path })
        }
      } else {
        typeError(state, "declaration-else failure capture requires a Result expression", span)
      }
    }
    handlerCompletes := checkBlock(state, handler, elseScope, inLoop)
    if name != "_" && handlerCompletes {
      typeError(state, "Declaration-else block must exit scope", handler.span)
    }
  } else if !isAssignableWithInterfaces(state.result, valueType, declaredType) {
    typeError(state, "Cannot assign ${displayTypeName(valueType)} to ${displayTypeName(declaredType)}", span)
  }
  case declaration {
    const_: ConstDeclaration -> { const_.resolvedType = declaredType }
    readonly_: ReadonlyDeclaration -> { readonly_.resolvedType = declaredType }
    binding: ImmutableBinding -> { binding.resolvedType = declaredType }
    let_: LetDeclaration -> { let_.resolvedType = declaredType }
    _ -> { }
  }
  if name != "_" {
    let declarationSymbol: Symbol | none = none
    if scope.parent == none { declarationSymbol = symbolFor(state.info!, name) }
    bindingKind := if scope.parent == none && kind == "let" then "module-let" else kind
    declareUserBinding(state, scope, Binding { name, kind: bindingKind, type_: declaredType, mutable, span: checkerSemanticSpan(span), module: state.info!.path, symbol: declarationSymbol }, span)
  }
  return valueType.kind != "never"
}

export function checkFunction(state: CheckerState, fn: FunctionDeclaration, outer: Scope, owner: ClassType | none): ResolvedType {
  validateUniqueTypeParameters(state, fn.typeParams, fn.span)
  validateTypeParameterShadowing(state, fn.typeParams, outer, fn.span)
  scope := Scope { parent: outer, typeParams: [], thisType: owner ?? unknownType(), functionName: fn.name, staticContext: owner != none && fn.static_ }
  populateTypeParameters(state, scope, fn.typeParams, fn.typeParamConstraints)
  if ownerClass := owner {
    if declaration := declarationFor(state.result, ownerClass.symbol) {
      if classDeclaration := declaration as ClassDeclaration { populateTypeParameters(state, scope, classDeclaration.typeParams, classDeclaration.typeParamConstraints) }
    }
    // Static methods see the class's static fields by bare name, as they do its
    // static methods; instance members need an instance.
    if fn.static_ { addClassFields(state, scope, ownerClass, true) }
    else { addClassFields(state, scope, ownerClass); addClassMethods(state, scope, ownerClass) }
  }
  returnType := if annotation := fn.returnType then resolveType(state, annotation, state.info!, scope) else noneType()
  scope.returnType = returnType
  // Resolve through the scope chain so owner type parameters (such as an
  // interface's `V`) are visible to the cached signature, not only the body.
  let collectedParameterTypes: FunctionParamType[] = []
  for parameter of fn.params {
    collectedParameterTypes.push(FunctionParamType {
      name: parameter.name,
      type_: if parameter.type_ == none then unknownType() else resolveType(state, parameter.type_!, state.info!, scope),
      hasDefault: parameter.defaultValue != none,
    })
  }
  parameterTypes := collectedParameterTypes.drainToReadonly()
  functionValue := functionType(parameterTypes, returnType, fn.typeParams)
  fn.resolvedType = functionValue
  for index of 0..<fn.params.length {
    parameter := fn.params[index]
    parameterType := parameterTypes[index].type_
    parameter.resolvedType = parameterType
    if defaultValue := parameter.defaultValue {
      defaultType := checkCallerDefault(state, defaultValue, scope, parameterType)
      if !isAssignableWithInterfaces(state.result, defaultType, parameterType) {
        typeError(state, "Cannot use default value of type ${typeName(defaultType)} for parameter '${parameter.name}' of type ${typeName(parameterType)}", defaultValue.span)
      }
    }
    if !declareShadowing(scope, Binding { name: parameter.name, kind: "parameter", type_: parameterType, mutable: false, span: checkerSemanticSpan(parameter.span), module: state.info!.path }) {
      typeError(state, "Binding '${parameter.name}' is already declared in this scope", parameter.span)
    }
  }
  if fn.bodyless { return functionValue }
  let actualReturn = noneType()
  let completes = true
  case fn.body {
    expression: Expression -> {
      actualReturn = checkExpression(state, expression, scope, returnType)
      if returnType.kind != "never" && !isAssignableWithInterfaces(state.result, actualReturn, returnType) {
        typeError(state, "Cannot return ${typeName(actualReturn)} from function returning ${typeName(returnType)}", expression.span)
      }
      if returnType.kind == "never" && actualReturn.kind != "never" {
        typeError(state, "Cannot return ${typeName(actualReturn)} from function returning never", expression.span)
      }
      completes = false
    }
    block: Block -> { completes = checkBlock(state, block, scope); actualReturn = inferredReturn(state, block) }
  }
  if completes && returnType.kind != "none" && returnType.kind != "unknown" {
    typeError(state, "Function '${fn.name}' may complete without returning ${typeName(returnType)}", fn.span)
  }
  if annotation := fn.returnType { decorateAnnotationWithResolved(annotation, returnType) }
  for parameter of fn.params {
    if type_ := parameter.type_ && resolvedType := parameter.resolvedType { decorateAnnotationWithResolved(type_, resolvedType) }
  }
  return functionValue
}

export function checkClass(state: CheckerState, class_: ClassDeclaration, scope: Scope): none {
  validateUniqueTypeParameters(state, class_.typeParams, class_.span)
  validateUniqueClassMembers(state, class_)
  symbol := symbolFor(state.info!, class_.name)
  if symbol == none { return }
  classScope := Scope { parent: scope, typeParams: [] }
  populateTypeParameters(state, classScope, class_.typeParams, class_.typeParamConstraints)
  let ownerTypeArgs: ResolvedType[] = []
  for typeParam of class_.typeParams { ownerTypeArgs.push(typeParameter(typeParam)) }
  owner := classType(class_.name, symbol!, ownerTypeArgs.drainToReadonly())
  resolveFieldInclusions(state, class_, state.info!, classScope)
  for field of class_.fields {
    if origin := field.includedFrom {
      // The source declaration already checked the type, default, and name.
      includedType := includedFieldType(state, origin, state.info!, classScope)
      field.resolvedType = includedType
      if class_.struct_ && containsWeakType(includedType) {
        typeError(state, "Struct field \"${fieldDisplayName(field)}\" cannot be weak", field.span)
      }
      continue
    }
    deprecatedConstField(state, field)
    for fieldName of field.names {
      if generatedMemberName(fieldName) { typeError(state, "Member name \"${fieldName}\" is reserved for compiler-generated reflection and JSON support", field.span) }
    }
    let fieldType = unknownType()
    if type_ := field.type_ {
      fieldType = resolveType(state, type_, state.info!, classScope)
    } else if defaultValue := field.defaultValue {
      fieldType = checkCallerDefault(state, defaultValue, classScope, none)
    }
    validateEnumLiteralField(state, field, fieldType)
    if field.readonly_ || field.const_ { fieldType = applyDeepReadonly(fieldType) }
    field.resolvedType = if field.weak_ then weakType(fieldType) else fieldType
    if field.weak_ && !isWeakReferenceTarget(fieldType) {
      name := fieldDisplayName(field)
      typeError(state, "Field \"${name}\" has type \"${typeName(fieldType)}\", which is not a valid weak reference target", field.span)
    }
    if class_.struct_ && (field.weak_ || containsWeakType(fieldType)) {
      name := fieldDisplayName(field)
      typeError(state, "Struct field \"${name}\" cannot be weak", field.span)
    }
    if defaultValue := field.defaultValue && field.type_ != none {
      defaultType := checkCallerDefault(state, defaultValue, classScope, fieldType)
      if !isAssignableWithInterfaces(state.result, defaultType, fieldType) {
        typeError(state, "Cannot use default value of type ${typeName(defaultType)} for field of type ${typeName(fieldType)}", defaultValue.span)
      }
    }
  }
  validateStructLayout(state, class_, symbol!)
  for method of class_.methods {
    deprecatedClassMethodFunction(state, method)
    if generatedMemberName(method.name) { typeError(state, "Method name \"${method.name}\" is reserved for compiler-generated reflection and JSON support", method.span) }
    checkFunction(state, method, classScope, owner)
    if method.name == "constructor" { validateConstructorDeclaration(state, class_, method, owner) }
  }
  streamElement := classStreamElementType(class_)
  if element := streamElement { symbol!.streamElementTypes.push(element) }
  if destructor_ := class_.destructor_ {
    if class_.struct_ {
      typeError(state, "Struct \"${class_.name}\" cannot declare a destructor", destructor_.span)
    } else {
      destructorScope := Scope {
        parent: classScope,
        returnType: noneType(),
        thisType: owner,
        functionName: "${class_.name}.destructor",
      }
      addClassFields(state, destructorScope, owner)
      addClassMethods(state, destructorScope, owner)
      checkBlock(state, destructor_, destructorScope)
    }
  }
  for interfaceRef of class_.implements_ {
    if class_.struct_ {
      typeError(state, "Struct \"${class_.name}\" cannot implement interfaces; use a class for interface participation", interfaceRef.span)
      continue
    }
    target := resolveType(state, interfaceRef, state.info!, classScope)
    case target {
      _: UnknownType -> { if interfaceRef.name != "Stream" { typeError(state, "Interface \"" + interfaceRef.name + "\" is not defined", interfaceRef.span) } }
      interface_: InterfaceType -> {
        if !classSatisfiesConcreteInterface(state.result, class_, owner, interface_) {
          typeError(state, "Class \"${class_.name}\" does not satisfy interface \"${typeName(target)}\"", interfaceRef.span)
        } else {
          addImplementedInterfaceType(symbol!, typeName(target))
        }
      }
      stream: StreamResolvedType -> {
        if streamElement == none || !sameType(streamElement!, stream.elementType) {
          typeError(state, "Class \"${class_.name}\" does not satisfy interface \"${typeName(target)}\"", interfaceRef.span)
        }
      }
      _ -> { typeError(state, "\"${interfaceRef.name}\" is not an interface", interfaceRef.span) }
    }
  }
}

function validateUniqueClassMembers(state: CheckerState, class_: ClassDeclaration): none {
  owner := "class \"${class_.name}\""
  let names: string[] = []
  for field of class_.fields {
    for name of field.names { declareUniqueName(state, names, "Member", name, owner, field.span) }
  }
  for method of class_.methods { declareUniqueName(state, names, "Member", method.name, owner, method.span) }
}

// Reports a name already declared in the same namespace and records the rest.
function declareUniqueName(state: CheckerState, names: string[], label: string, name: string, owner: string, span: SourceSpan): none {
  if names.contains(name) { typeError(state, "${label} \"${name}\" is already declared in ${owner}", span) }
  else { names.push(name) }
}

function validateConstructorDeclaration(state: CheckerState, class_: ClassDeclaration, constructor: FunctionDeclaration, owner: ClassType): none {
  if !constructor.static_ {
    typeError(state, "Constructor method for \"${class_.name}\" must be static", constructor.span)
  }
  if constructor.resolvedType == none { return }
  if function_ := constructor.resolvedType! as FunctionType {
    let validReturn = sameType(function_.returnType, owner)
    if result := function_.returnType as ResultResolvedType { validReturn = sameType(result.valueType, owner) }
    if !validReturn {
      typeError(state, "Constructor method for \"${class_.name}\" must return ${class_.name} or Result<${class_.name}, E>", constructor.span)
    }
  }
}

function classStreamElementType(class_: ClassDeclaration): ResolvedType | none {
  let nextType: FunctionType | none = none
  let valueType: FunctionType | none = none
  for method of class_.methods {
    if method.static_ || method.resolvedType == none { continue }
    if function_ := method.resolvedType! as FunctionType {
      if method.name == "next" { nextType = function_ }
      if method.name == "value" { valueType = function_ }
    }
  }
  if nextType == none || valueType == none { return none }
  if nextType!.params.length != 0 || !sameType(nextType!.returnType, primitive("bool")) { return none }
  if valueType!.params.length != 0 { return none }
  return valueType!.returnType
}

function generatedMemberName(name: string): bool {
  return name == "metadata" || name == "toSerialObject" || name == "fromSerialValue"
}

function containsWeakType(type_: ResolvedType): bool {
  case type_ {
    _: WeakResolvedType -> { return true }
    array: ArrayResolvedType -> { return containsWeakType(array.elementType) }
    map: MapResolvedType -> { return containsWeakType(map.keyType) || containsWeakType(map.valueType) }
    set_: SetResolvedType -> { return containsWeakType(set_.elementType) }
    tuple: TupleResolvedType -> { for item of tuple.elements { if containsWeakType(item) { return true } } }
    union_: UnionResolvedType -> { for member of union_.types { if containsWeakType(member) { return true } } }
    result: ResultResolvedType -> { return containsWeakType(result.valueType) || containsWeakType(result.errorType) }
    promise: PromiseType -> { return containsWeakType(promise.valueType) }
    _ -> { }
  }
  return false
}

export function checkInterface(state: CheckerState, interface_: InterfaceDeclaration, scope: Scope): none {
  validateUniqueTypeParameters(state, interface_.typeParams, interface_.span)
  validateUniqueInterfaceMembers(state, interface_)
  interfaceScope := Scope { parent: scope, typeParams: [] }
  populateTypeParameters(state, interfaceScope, interface_.typeParams, interface_.typeParamConstraints)
  for field of interface_.fields { resolveInterfaceField(state, field, interfaceScope) }
  for method of interface_.methods { checkFunction(state, method, interfaceScope, none) }
  for field of interface_.staticFields { resolveInterfaceField(state, field, interfaceScope) }
  for method of interface_.staticMethods { checkFunction(state, method, interfaceScope, none) }
}

function resolveInterfaceField(state: CheckerState, field: InterfaceField, scope: Scope): none {
  fieldType := resolveType(state, field.type_, state.info!, scope)
  field.resolvedType = if field.readonly_ then applyDeepReadonly(fieldType) else fieldType
}

function validateUniqueInterfaceMembers(state: CheckerState, interface_: InterfaceDeclaration): none {
  owner := "interface \"${interface_.name}\""
  let names: string[] = []
  for field of interface_.fields { declareUniqueName(state, names, "Member", field.name, owner, field.span) }
  for method of interface_.methods { declareUniqueName(state, names, "Member", method.name, owner, method.span) }
  let staticNames: string[] = []
  for field of interface_.staticFields { declareUniqueName(state, staticNames, "Static member", field.name, owner, field.span) }
  for method of interface_.staticMethods { declareUniqueName(state, staticNames, "Static member", method.name, owner, method.span) }
}

// Constraint annotations live in the declaration scope so ordinary constraints
// participate in body checking while the two constraint-only intrinsics retain
// their dedicated member semantics.
function populateTypeParameters(state: CheckerState, scope: Scope, names: readonly string[], constraints: TypeParameterConstraint[]): none {
  offset := scope.typeParams.length
  for name of names {
    scope.typeParams.push(name)
    scope.typeParamConstraintNames.push("")
    scope.typeParamConstraints.push(ResolvedTypeConstraint {})
  }
  let active: string[] = []
  let completed: string[] = []
  for index of 0..<names.length { populateConstraint(state, scope, names, constraints, offset, index, active, completed) }
  // Validate nested applications only after every parameter has its bound.
  for index of 0..<names.length {
    if index >= constraints.length || constraints[index].type_ == none || scope.typeParamConstraintNames[offset + index] != "" { continue }
    if scope.typeParamConstraints[offset + index].type_ != none && scope.typeParamConstraints[offset + index].type_!.kind == "unknown" { continue }
    resolveType(state, constraints[index].type_!, state.info!, scope)
  }
}

function populateConstraint(state: CheckerState, scope: Scope, names: readonly string[], constraints: TypeParameterConstraint[], offset: int, index: int, active: string[], completed: string[]): none {
  if completed.contains(names[index]) { return }
  if index >= constraints.length || constraints[index].type_ == none { completed.push(names[index]); return }
  annotation := constraints[index].type_!
  if active.contains(names[index]) {
    typeError(state, "Cyclic constraint for type parameter '${names[index]}'", annotation.span)
    scope.typeParamConstraints[offset + index].type_ = unknownType()
    completed.push(names[index])
    return
  }
  active.push(names[index])
  if named := annotation as NamedType {
    if named.typeArgs.length == 0 && (named.name == "Serializable" || named.name == "Reflectable") {
      scope.typeParamConstraintNames[offset + index] = named.name
      completed.push(names[index])
      return
    }
  }
  let resolved = resolveType(state, annotation, state.info!, scope, false)
  if parameter := resolved as TypeParameterType {
    // Alias-expanded parameter bounds also resolve independently of order.
    for dependency of 0..<names.length {
      if parameter.name == names[dependency] { populateConstraint(state, scope, names, constraints, offset, dependency, active, completed) }
    }
    if !completed.contains(names[index]) { resolved = resolveType(state, annotation, state.info!, scope, false) }
  }
  if !completed.contains(names[index]) {
    scope.typeParamConstraints[offset + index].type_ = resolved
    completed.push(names[index])
  }
}

function validateUniqueTypeParameters(state: CheckerState, names: readonly string[], span: SourceSpan): none {
  for index of 0..<names.length {
    for previous of 0..<index {
      if names[previous] == names[index] {
        typeError(state, "Type parameter \"${names[index]}\" is already declared in this declaration", span)
        break
      }
    }
  }
}

function validateTypeParameterShadowing(state: CheckerState, names: readonly string[], outer: Scope, span: SourceSpan): none {
  let current: Scope | none = outer
  while current != none {
    for name of names {
      for visible of current!.typeParams {
        if name == visible {
          typeError(state, "Type parameter \"${name}\" shadows a type parameter from the enclosing declaration", span)
        }
      }
    }
    current = current!.parent
  }
}

export function checkEnum(state: CheckerState, enum_: EnumDeclaration, scope: Scope): none {
  let stringBacked = false
  for variant of enum_.variants {
    if value := variant.value && literalStringValue(value) != none { stringBacked = true }
  }
  enum_.backingKind = if stringBacked then "string" else "int"
  owner := "enum \"${enum_.name}\""
  let names: string[] = []
  // Values are compared by their source text; one enum never mixes kinds.
  let values: string[] = []
  let valueNames: string[] = []
  let nextValue = 0L
  for variant of enum_.variants {
    declareUniqueName(state, names, "Variant", variant.name, owner, variant.span)
    if stringBacked {
      if variant.value == none {
        typeError(state, "String enum variant \"${variant.name}\" requires an explicit string value", variant.span)
        continue
      }
      checkExpression(state, variant.value!, scope, primitive("string"))
      value := literalStringValue(variant.value!)
      if value == none {
        typeError(state, "String enum variant \"${variant.name}\" value must be a non-interpolated string literal", variant.value!.span)
        continue
      }
      recordUniqueEnumValue(state, values, valueNames, value!, variant)
      variant.resolvedStringValue = value
      continue
    }
    let value: long | none = nextValue
    if valueExpression := variant.value {
      valueType := checkExpression(state, valueExpression, scope, primitive("int"))
      if !isAssignableWithInterfaces(state.result, valueType, primitive("int")) { typeError(state, "Enum value must be an int", variant.span) }
      value = constantInt(valueExpression)
      if value == none { typeError(state, "Enum variant \"${variant.name}\" value must be a compile-time int constant", valueExpression.span) }
    }
    if value == none { continue }
    nextValue = value! + 1L
    if value! < -2147483648L || value! > 2147483647L {
      typeError(state, "Enum variant \"${variant.name}\" value is outside the int range", variant.span)
      continue
    }
    recordUniqueEnumValue(state, values, valueNames, string(value!), variant)
    variant.resolvedIntValue = int(value!)
  }
}

function literalStringValue(expression: Expression): string | none {
  if literal := expression as StringLiteral { if literal.interpolations.length == 0 { return literal.value } }
  return none
}

function recordUniqueEnumValue(state: CheckerState, values: string[], valueNames: string[], value: string, variant: EnumVariant): none {
  for previous of 0..<values.length {
    if values[previous] == value {
      typeError(state, "Enum variant \"${variant.name}\" duplicates the value of \"${valueNames[previous]}\"", variant.span)
      break
    }
  }
  values.push(value)
  valueNames.push(variant.name)
}

// The parser accepts any dotted name as a literal-valued field; only an enum
// variant is a compile-time constant, so static fields and namespaces are rejected.
function validateEnumLiteralField(state: CheckerState, field: ClassField, fieldType: ResolvedType): none {
  if !field.const_ || field.legacyConstSpan != none || field.defaultValue == none || field.names.length == 0 || fieldType.kind == "unknown" { return }
  if member := field.defaultValue! as MemberExpression {
    if enum_ := fieldType as EnumType {
      if declaration := declarationFor(state.result, enum_.symbol) {
        if owner := declaration as EnumDeclaration { for variant of owner.variants { if variant.name == member.property { return } } }
      }
    }
    typeError(state, "Literal-valued field \"${field.names[0]}\" must be a literal or an enum variant such as Kind.Variant", member.span)
  }
}

export function checkReturn(state: CheckerState, statement: ReturnStatement, scope: Scope): bool {
  if valueYieldScope(scope) != none {
    typeError(state, "'return' cannot be used inside a value-producing block; use 'yield' to produce the block value", statement.span)
    if value := statement.value { checkExpression(state, value, scope, none) }
    return false
  }
  target := returnScope(scope)
  if target == none { typeError(state, "Return is only valid inside a function", statement.span); return false }
  if target!.trailingLambda {
    typeError(state, "'return' cannot be used inside a trailing lambda; use an explicit lambda instead", statement.span)
    if value := statement.value { checkExpression(state, value, scope, none) }
    return false
  }
  returnType := target!.returnType!
  statement.resolvedExpectedType = returnType
  let actualReturn = noneType()
  if statement.value == none {
    if returnType.kind != "none" && returnType.kind != "unknown" {
      typeError(state, "Expected a return value of type ${typeName(returnType)}", statement.span)
    }
  } else {
    valueType := checkExpression(state, statement.value!, scope, returnType)
    actualReturn = valueType
    if !isAssignableWithInterfaces(state.result, valueType, returnType) { typeError(state, "Cannot return ${typeName(valueType)} from function returning ${typeName(returnType)}", statement.span) }
  }
  if inference := state.lambdaReturns && inference.scope == target! {
    inference.returns.push(LambdaReturnObservation { statement, type_: actualReturn, reachable: inference.reachable })
  }
  return false
}

export function checkBlock(state: CheckerState, block: Block, parent: Scope, inLoop: bool = false): bool {
  scope := Scope { parent }
  retainEditorScope(state, scope, block.span)
  let completes = true
  let retiredActors: Binding[] = []
  for statement of block.statements {
    maybeInference := state.lambdaReturns
    reachable := maybeInference?.reachable ?? false
    if !completes && inference := maybeInference { inference.reachable = false }
    if completes {
      completes = checkStatement(state, statement, scope, inLoop)
    } else {
      // Unreachable statements still need full semantic decoration. The
      // emitter consumes the entire AST, so skipping them would create a
      // hidden unchecked region even though control-flow analysis already
      // knows the block cannot complete normally.
      let ignored = checkStatement(state, statement, scope, inLoop)
    }
    if inference := maybeInference { inference.reachable = reachable }
    reportRetiredActorUses(statement, retiredActors, state.info!.path, state.diagnostics)
    collectRetiredActorBindings(statement, retiredActors)
  }
  return completes
}

/** Checks declaration and assignment destructuring against an already-resolved source shape. */
export function checkDestructuring(state: CheckerState, statement: DestructuringStatement, scope: Scope, sourceType: ResolvedType | none): none {
  valueType := sourceType ?? checkExpression(state, statement.value, scope, none)
  let bindingTypes: ResolvedType[] = []

  if statement.kind.startsWith("array-destructuring") {
    case valueType {
      array: ArrayResolvedType -> { for ignored of statement.bindings { bindingTypes.push(array.elementType) } }
      _ -> { typeError(state, "Array destructuring requires a T[] value, but got \"${typeName(valueType)}\"", statement.value.span) }
    }
  } else if statement.kind.startsWith("positional-destructuring") {
    bindingTypes = positionalDestructuringTypes(state, valueType, statement.value.span)
    if bindingTypes.length < statement.bindings.length {
      typeError(state, "Positional destructuring expected at least ${statement.bindings.length} values, but got ${bindingTypes.length}", statement.span)
    }
  }

  if statement.kind.startsWith("named-destructuring") {
    for named of statement.namedBindings {
      localName := named.alias ?? named.name
      fieldType := memberType(state, valueType, named.name, named.span)
      if fieldType.kind == "unknown" { typeError(state, "Type \"" + typeName(valueType) + "\" has no field \"" + named.name + "\"", named.span) }
      if statement.kind.endsWith("-assignment") { validateDestructuringTarget(state, scope, localName, fieldType, named.span) }
      else { declareDestructuredBinding(state, scope, localName, fieldType, statement.bindingKind, named.span) }
    }
    return
  }

  for i of 0..<statement.bindings.length {
    name := statement.bindings[i]
    if name == "_" { continue }
    bindingType := if i < bindingTypes.length then bindingTypes[i] else unknownType()
    if statement.kind.endsWith("-assignment") { validateDestructuringTarget(state, scope, name, bindingType, statement.span) }
    else { declareDestructuredBinding(state, scope, name, bindingType, statement.bindingKind, statement.span) }
  }
}

function positionalDestructuringTypes(state: CheckerState, valueType: ResolvedType, span: SourceSpan): ResolvedType[] {
  let result: ResolvedType[] = []
  case valueType {
    tuple: TupleResolvedType -> { for element of tuple.elements { result.push(element) } }
    class_: ClassType -> {
      if declaration := declarationFor(state.result, class_.symbol) { case declaration {
        owner: ClassDeclaration -> {
          for field of owner.fields {
            if field.static_ { continue }
            for name of field.names { result.push(memberType(state, class_, name, span)) }
          }
        }
        _ -> { }
      } }
    }
    _ -> { typeError(state, "Positional destructuring requires a tuple or nominal object value, but got \"${typeName(valueType)}\"", span) }
  }
  return result
}

function declareDestructuredBinding(state: CheckerState, scope: Scope, name: string, type_: ResolvedType, bindingKind: string, span: SourceSpan): none {
  declareUserBinding(state, scope, Binding {
    name,
    kind: if bindingKind == "let" then "let" else "immutable-binding",
    type_, mutable: bindingKind == "let", span: checkerSemanticSpan(span), module: state.info!.path,
  }, span)
}

export function declareUserBinding(state: CheckerState, scope: Scope, binding: Binding, span: SourceSpan): none {
  if !declare(scope, binding) { typeError(state, "Binding '${binding.name}' is already declared in this scope", span) }
}

function validateDestructuringTarget(state: CheckerState, scope: Scope, name: string, valueType: ResolvedType, span: SourceSpan): none {
  target := lookup(scope, name)
  if target == none { typeError(state, "Destructuring assignment target \"${name}\" is not defined", span); return }
  validateAssignmentBinding(state, target!, span)
  if !isAssignableWithInterfaces(state.result, valueType, target!.type_) { typeError(state, "Cannot assign ${displayTypeName(valueType)} to ${displayTypeName(target!.type_)}", span) }
}

export function checkCase(state: CheckerState, statement: CaseStatement, scope: Scope, inLoop: bool = false): bool {
  subjectType := checkedCaseSubjectType(checkExpression(state, statement.subject, scope, none))
  statement.resolvedSubjectType = subjectType
  let armPatterns: CasePattern[][] = []
  let allArmsReturn = statement.arms.length > 0
  for arm of statement.arms {
    armPatterns.push(arm.patterns)
    armScope := Scope { parent: scope }
    checkCasePatterns(state, arm.patterns, subjectType, armScope)
    let armCompletes = true
    case arm.body {
      block: Block -> { armCompletes = checkBlock(state, block, armScope, inLoop) }
      expression: Expression -> { armCompletes = checkExpression(state, expression, armScope, none).kind != "never" }
    }
    if armCompletes { allArmsReturn = false }
  }
  exhaustive := casePatternsExhaustive(state, subjectType, armPatterns)
  statement.resolvedCompletes = if subjectType.kind == "never" then false else !(exhaustive && allArmsReturn)
  return statement.resolvedCompletes!
}

export function inferredReturn(state: CheckerState, block: Block): ResolvedType {
  for statement of block.statements {
    if return_ := statement as ReturnStatement {
      value := return_.value else { return noneType() }
      return value.resolvedType ?? unknownType()
    }
  }
  return noneType()
}

export function addClassFields(state: CheckerState, scope: Scope, owner: ClassType, staticOnly: bool = false): none {
  declaration := declarationFor(state.result, owner.symbol)
  if declaration == none { return }
  if class_ := declaration! as ClassDeclaration {
    for field of class_.fields {
      if staticOnly && !field.static_ { continue }
      for name of field.names { declare(scope, classFieldBinding(field, name, class_, field.resolvedType ?? unknownType(), state.info!.path)) }
    }
  }
}

// A class with instance `next(): bool` and `value(): T` methods is iterated as
// a Stream<T>. Member resolution reads method signatures directly, so the
// class may be declared after the loop that iterates it.
function forOfElement(state: CheckerState, iterable: ResolvedType, span: SourceSpan): ResolvedType {
  case iterable {
    class_: ClassType -> {
      next := resolveMember(state, class_, "next", span)
      value := resolveMember(state, class_, "value", span)
      if !next.instance || next.field || !value.instance || value.field { return unknownType() }
      case next.type_! {
        nextFunction: FunctionType -> {
          if nextFunction.params.length != 0 || !sameType(nextFunction.returnType, primitive("bool")) { return unknownType() }
        }
        _ -> { return unknownType() }
      }
      if valueFunction := value.type_! as FunctionType {
        if valueFunction.params.length == 0 { return valueFunction.returnType }
      }
      return unknownType()
    }
    _ -> { return iterableElement(iterable) }
  }
  return unknownType()
}
