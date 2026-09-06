// Graph-wide decorated-AST validation before emission.

import { ActorType, ArrayResolvedType, ClassType, Diagnostic, FunctionType, MapResolvedType, PromiseType, ResolvedType, ResultResolvedType, SemanticLocation, SemanticSpan, SetResolvedType, StreamResolvedType, TupleResolvedType, UnionResolvedType, UnknownType, TypeParameterType, WeakResolvedType } from "./semantic"
import { AnalysisResult } from "./analyzer"
import { CheckedConstruction, ArrayLiteral, ArrayType, AsExpression, AssignmentExpression, BinaryExpression, Block, CallExpression, ClassDeclaration, ConstructExpression, ConstDeclaration, DestructuringStatement, EnumDeclaration, ExportDeclaration, Expression, ExpressionStatement, ForOfStatement, ForStatement, FunctionDeclaration, AstFunctionType, IfExpression, IfStatement, ImmutableBinding, Identifier, IndexExpression, InterfaceDeclaration, LetDeclaration, LambdaExpression, MemberExpression, NamedType, ObjectLiteral, ReadonlyDeclaration, ReturnStatement, SourceSpan, Statement, StringLiteral, TupleLiteral, TypeAliasDeclaration, TypeAnnotation, UnaryExpression, UnionType, WhileStatement, WithStatement, YieldStatement, YieldBlockExpression, YieldBlockAssignmentStatement, CatchExpression, CaseExpression, CasePattern, CaseStatement, RangePattern, TypePattern, ValuePattern, WildcardPattern, TryStatement, AsyncExpression, RetireExpression, ActorCreationExpression, WeakType, TypeParameterConstraint } from "./ast"

import { unionMutabilityConflict } from "./checker-types"
import { optionalResolvedType } from "./checker-symbols"

export function validateCheckedTypes(result: AnalysisResult): Diagnostic[] {
  let diagnostics: Diagnostic[] = []
  for module of result.modules {
    for statement of module.program.statements { validateStatement(statement, module.path, diagnostics) }
  }
  return diagnostics
}

export function validateStatement(statement: Statement, module: string, diagnostics: Diagnostic[]): none {
  case statement {
    const_: ConstDeclaration -> { validateValue(const_, const_.resolvedType, const_.type_, module, diagnostics); validateExpression(const_.value, module, diagnostics) }
    readonly_: ReadonlyDeclaration -> { validateValue(readonly_, readonly_.resolvedType, readonly_.type_, module, diagnostics); validateExpression(readonly_.value, module, diagnostics) }
    binding: ImmutableBinding -> {
      validateValue(binding, binding.resolvedType, binding.type_, module, diagnostics)
      validateExpression(binding.value, module, diagnostics)
      if binding.else_ != none { validateBlock(binding.else_!, module, diagnostics) }
    }
    let_: LetDeclaration -> { validateValue(let_, let_.resolvedType, let_.type_, module, diagnostics); validateExpression(let_.value, module, diagnostics) }
    fn: FunctionDeclaration -> { validateFunction(fn, module, diagnostics) }
    class_: ClassDeclaration -> {
      if class_.resolvedSymbol == none { addValidationError(module, class_.span, "Class '" + class_.name + "' has no resolved symbol", diagnostics) }
      validateTypeParameterConstraints(class_.typeParamConstraints, module, diagnostics)
      for implementation of class_.implements_ { validateTypeAnnotation(implementation, module, diagnostics) }
      for field of class_.fields {
        if field.type_ != none { validateTypeAnnotation(field.type_!, module, diagnostics) }
        validateResolved(field.resolvedType, field.span, module, "field " + class_.name, diagnostics)
        if field.defaultValue != none { validateExpression(field.defaultValue!, module, diagnostics) }
      }
      for method of class_.methods { validateFunction(method, module, diagnostics) }
    }
    interface_: InterfaceDeclaration -> {
      if interface_.resolvedSymbol == none { addValidationError(module, interface_.span, "Interface '" + interface_.name + "' has no resolved symbol", diagnostics) }
      validateTypeParameterConstraints(interface_.typeParamConstraints, module, diagnostics)
      for field of interface_.fields {
        validateTypeAnnotation(field.type_, module, diagnostics)
        validateResolved(field.resolvedType, field.span, module, "interface field " + interface_.name, diagnostics)
      }
      for method of interface_.methods { validateFunction(method, module, diagnostics) }
    }
    enum_: EnumDeclaration -> {
      for variant of enum_.variants {
        if variant.value != none { validateExpression(variant.value!, module, diagnostics) }
        if enum_.backingKind == "string" {
          if variant.resolvedStringValue == none { addValidationError(module, variant.span, "Enum variant '" + enum_.name + "." + variant.name + "' has no resolved string backing value", diagnostics) }
        } else if variant.resolvedIntValue == none {
          addValidationError(module, variant.span, "Enum variant '" + enum_.name + "." + variant.name + "' has no resolved integer backing value", diagnostics)
        }
      }
    }
    alias: TypeAliasDeclaration -> {
      validateTypeParameterConstraints(alias.typeParamConstraints, module, diagnostics)
      validateTypeAnnotation(alias.type_, module, diagnostics)
      validateResolved(alias.resolvedType, alias.span, module, "type alias " + alias.name, diagnostics)
    }
    if_: IfStatement -> {
      validateExpression(if_.condition, module, diagnostics); validateBlock(if_.body, module, diagnostics)
      for branch of if_.elseIfs { validateExpression(branch.condition, module, diagnostics); validateBlock(branch.body, module, diagnostics) }
      if if_.else_ != none { validateBlock(if_.else_!, module, diagnostics) }
    }
    case_: CaseStatement -> {
      if case_.resolvedCompletes == none { addValidationError(module, case_.span, "Case statement has no resolved control-flow completion", diagnostics) }
      validateExpression(case_.subject, module, diagnostics)
      for arm of case_.arms {
        for pattern of arm.patterns { validatePattern(pattern, module, diagnostics) }
        case arm.body {
          block: Block -> { validateBlock(block, module, diagnostics) }
          expression: Expression -> { validateExpression(expression, module, diagnostics) }
        }
      }
    }
    while_: WhileStatement -> { validateExpression(while_.condition, module, diagnostics); validateBlock(while_.body, module, diagnostics); if while_.then_ != none { validateBlock(while_.then_!, module, diagnostics) } }
    for_: ForStatement -> {
      if for_.init != none { validateStatement(for_.init!, module, diagnostics) }
      if for_.condition != none { validateExpression(for_.condition!, module, diagnostics) }
      for update of for_.update { validateExpression(update, module, diagnostics) }
      validateBlock(for_.body, module, diagnostics); if for_.then_ != none { validateBlock(for_.then_!, module, diagnostics) }
    }
    forOf: ForOfStatement -> { validateExpression(forOf.iterable, module, diagnostics); validateBlock(forOf.body, module, diagnostics); if forOf.then_ != none { validateBlock(forOf.then_!, module, diagnostics) } }
    with_: WithStatement -> {
      for binding of with_.bindings {
        if binding.type_ != none { validateTypeAnnotation(binding.type_!, module, diagnostics) }
        validateResolved(binding.resolvedType, binding.span, module, "with binding " + binding.name, diagnostics)
        validateExpression(binding.value, module, diagnostics)
      }
      validateBlock(with_.body, module, diagnostics)
    }
    return_: ReturnStatement -> { if return_.value != none { validateExpression(return_.value!, module, diagnostics) } }
    yield_: YieldStatement -> { validateExpression(yield_.value, module, diagnostics) }
    assignment: YieldBlockAssignmentStatement -> { validateExpression(assignment.value, module, diagnostics); validateResolved(assignment.resolvedType, assignment.span, module, "yield-block assignment", diagnostics) }
    expression: ExpressionStatement -> { validateExpression(expression.expression, module, diagnostics) }
    destructuring: DestructuringStatement -> { validateExpression(destructuring.value, module, diagnostics) }
    try_: TryStatement -> {
      case try_.binding {
        declaration: ConstDeclaration -> { validateStatement(declaration, module, diagnostics) }
        declaration: ReadonlyDeclaration -> { validateStatement(declaration, module, diagnostics) }
        binding: ImmutableBinding -> { validateStatement(binding, module, diagnostics) }
        declaration: LetDeclaration -> { validateStatement(declaration, module, diagnostics) }
        expression: ExpressionStatement -> { validateStatement(expression, module, diagnostics) }
        destructuring: DestructuringStatement -> { validateStatement(destructuring, module, diagnostics) }
      }
    }
    export_: ExportDeclaration -> { validateStatement(export_.declaration, module, diagnostics) }
    block: Block -> { validateBlock(block, module, diagnostics) }
    _ -> { }
  }
}

export function validateValue(statement: Statement, resolvedType: ResolvedType | none, annotation: TypeAnnotation | none, module: string, diagnostics: Diagnostic[]): none {
  if annotation != none { validateTypeAnnotation(annotation!, module, diagnostics) }
  validateResolved(resolvedType, statement.span, module, "value", diagnostics)
}

export function validateFunction(fn: FunctionDeclaration, module: string, diagnostics: Diagnostic[]): none {
  validateResolved(fn.resolvedType, fn.span, module, "function " + fn.name, diagnostics)
  validateTypeParameterConstraints(fn.typeParamConstraints, module, diagnostics)
  if fn.returnType != none { validateTypeAnnotation(fn.returnType!, module, diagnostics) }
  for parameter of fn.params {
    if parameter.type_ != none { validateTypeAnnotation(parameter.type_!, module, diagnostics) }
    validateResolved(parameter.resolvedType, parameter.span, module, "parameter " + parameter.name, diagnostics)
    if parameter.defaultValue != none { validateExpression(parameter.defaultValue!, module, diagnostics) }
  }
  case fn.body {
    block: Block -> { validateBlock(block, module, diagnostics) }
    expression: Expression -> { validateExpression(expression, module, diagnostics) }
  }
}

function validateTypeParameterConstraints(constraints: TypeParameterConstraint[], module: string, diagnostics: Diagnostic[]): none {
  for constraint of constraints {
    if constraint.type_ == none { continue }
    case constraint.type_! {
      named: NamedType -> {
        if named.typeArgs.length == 0 && (named.name == "JsonSerializable" || named.name == "Reflectable") { continue }
      }
      _ -> { }
    }
    validateTypeAnnotation(constraint.type_!, module, diagnostics)
  }
}

export function validateBlock(block: Block, module: string, diagnostics: Diagnostic[]): none {
  for statement of block.statements { validateStatement(statement, module, diagnostics) }
}

export function validatePattern(pattern: CasePattern, module: string, diagnostics: Diagnostic[]): none {
  case pattern {
    type_: TypePattern -> { validateTypeAnnotation(type_.type_, module, diagnostics); validateResolved(type_.resolvedType, type_.span, module, "case pattern", diagnostics) }
    value: ValuePattern -> { validateExpression(value.value, module, diagnostics) }
    range: RangePattern -> {
      if range.start != none { validateExpression(range.start!, module, diagnostics) }
      if range.end != none { validateExpression(range.end!, module, diagnostics) }
    }
    _: WildcardPattern -> { }
  }
}

export function validateExpression(expression: Expression, module: string, diagnostics: Diagnostic[]): none {
  validateResolved(expression.resolvedType, expression.span, module, "expression " + expression.kind, diagnostics)
  case expression {
    string_: StringLiteral -> { for interpolation of string_.interpolations { validateExpression(interpolation, module, diagnostics) } }
    binary: BinaryExpression -> { validateExpression(binary.left, module, diagnostics); validateExpression(binary.right, module, diagnostics) }
    unary: UnaryExpression -> { validateExpression(unary.operand, module, diagnostics) }
    assignment: AssignmentExpression -> { validateExpression(assignment.target, module, diagnostics); validateExpression(assignment.value, module, diagnostics) }
    member: MemberExpression -> {
      if member.resolvedMember == none {
        if member.resolvedType != none && member.resolvedType!.kind != "never" {
          addValidationError(module, member.span, "Member '" + member.property + "' has no checked member selection", diagnostics)
        }
      } else {
        validateResolved(member.resolvedMember!.type_, member.span, module, "member selection", diagnostics)
        if member.resolvedMember!.function_ != none && member.resolvedMember!.modulePath == "" {
          addValidationError(module, member.span, "Resolved member target has no defining module", diagnostics)
        }
      }
      if member.resolvedNamespaceAccess {
        if member.resolvedNamespaceSymbol == none {
          addValidationError(module, member.span, "Namespace member '" + member.property + "' has no resolved symbol", diagnostics)
        }
      } else { validateExpression(member.object, module, diagnostics) }
    }
    index: IndexExpression -> { validateExpression(index.object, module, diagnostics); validateExpression(index.index, module, diagnostics) }
    call: CallExpression -> {
      validateExpression(call.callee, module, diagnostics)
      if call.resolvedClass != none || call.resolvedConstruction != none {
        validateConstructionPlan(call.resolvedConstruction, call.span, module, diagnostics)
      }
      case call.callee {
        member: MemberExpression -> {
          if member.resolvedMember != none && call.resolvedFunction != member.resolvedMember!.function_ {
            addValidationError(module, call.span, "Call target does not match checked member selection", diagnostics)
          }
        }
        _ -> { }
      }
      if call.resolvedFunction != none && call.resolvedFunctionModule == "" {
        addValidationError(module, call.span, "Resolved call target has no defining module", diagnostics)
      }
      for argument of call.typeArgs { validateTypeAnnotation(argument, module, diagnostics) }
      for argument of call.resolvedGenericTypeArgs { validateResolved(optionalResolvedType(argument), call.span, module, "generic call argument", diagnostics) }
      for argument of call.args { validateExpression(argument.value, module, diagnostics) }
    }
    array: ArrayLiteral -> { for item of array.elements { validateExpression(item, module, diagnostics) } }
    object: ObjectLiteral -> {
      if object.resolvedClass != none { validateConstructionPlan(object.resolvedConstruction, object.span, module, diagnostics) }
      if object.spread != none { validateExpression(object.spread!, module, diagnostics) }
      for property of object.properties {
        validateResolved(property.resolvedType, property.span, module, "object property", diagnostics)
        if property.key != none { validateExpression(property.key!, module, diagnostics) }
        if property.value != none { validateExpression(property.value!, module, diagnostics) }
      }
      if object.resolvedType != none {
        case object.resolvedType! {
          _: ClassType -> {
            if object.resolvedClass == none { addValidationError(module, object.span, "Class object literal has no resolved class", diagnostics) }
          }
          _ -> { }
        }
      }
    }
    tuple: TupleLiteral -> { for item of tuple.elements { validateExpression(item, module, diagnostics) } }
    lambda: LambdaExpression -> {
      if lambda.returnType != none { validateTypeAnnotation(lambda.returnType!, module, diagnostics) }
      for parameter of lambda.params {
        if parameter.type_ != none { validateTypeAnnotation(parameter.type_!, module, diagnostics) }
        validateResolved(parameter.resolvedType, parameter.span, module, "lambda parameter", diagnostics)
        if parameter.defaultValue != none { validateExpression(parameter.defaultValue!, module, diagnostics) }
      }
      case lambda.body {
        block: Block -> { validateBlock(block, module, diagnostics) }
        expression: Expression -> { validateExpression(expression, module, diagnostics) }
      }
    }
    if_: IfExpression -> { validateExpression(if_.condition, module, diagnostics); validateExpression(if_.then_, module, diagnostics); validateExpression(if_.else_, module, diagnostics) }
    case_: CaseExpression -> {
      validateExpression(case_.subject, module, diagnostics); validateResolved(case_.resolvedType, case_.span, module, "case expression", diagnostics)
      for arm of case_.arms {
        for pattern of arm.patterns { validatePattern(pattern, module, diagnostics) }
        case arm.body {
          block: Block -> { validateBlock(block, module, diagnostics) }
          bodyExpression: Expression -> { validateExpression(bodyExpression, module, diagnostics) }
        }
      }
    }
    yieldBlock: YieldBlockExpression -> { validateBlock(yieldBlock.body, module, diagnostics) }
    catch_: CatchExpression -> { validateBlock(catch_.body, module, diagnostics) }
    construct: ConstructExpression -> {
      if construct.spread != none {
        validateExpression(construct.spread!, module, diagnostics)
        validateResolved(construct.resolvedSpreadType, construct.spread!.span, module, "construction spread", diagnostics)
      }
      if construct.type_ != "Success" && construct.type_ != "Failure" {
        validateResolved(construct.resolvedConstructedType, construct.span, module, "constructed type", diagnostics)
        if construct.resolvedClass == none { addValidationError(module, construct.span, "Construction of '" + construct.type_ + "' has no resolved class", diagnostics) }
        validateConstructionPlan(construct.resolvedConstruction, construct.span, module, diagnostics)
        if construct.resolvedConstruction != none && construct.resolvedConstruction!.factory != construct.resolvedConstructor {
          addValidationError(module, construct.span, "Construction of '" + construct.type_ + "' has no resolved constructor consistent with its checked plan", diagnostics)
        }
      }
      if construct.resolvedConstructor != none {
        validateResolved(construct.resolvedConstructor!.resolvedType, construct.span, module, "constructor " + construct.type_, diagnostics)
      }
      for argument of construct.typeArgs { validateTypeAnnotation(argument, module, diagnostics) }
      for property of construct.args {
        validateResolved(property.resolvedType, property.span, module, "constructor property", diagnostics)
        if property.value != none { validateExpression(property.value!, module, diagnostics) }
        else if construct.type_ != "Success" && construct.type_ != "Failure" && property.resolvedBinding == none {
          addValidationError(module, property.span, "Constructor shorthand property '" + property.name + "' has no resolved binding", diagnostics)
        }
      }
    }
    async_: AsyncExpression -> {
      case async_.expression {
        block: Block -> { validateBlock(block, module, diagnostics) }
        inner: Expression -> { validateExpression(inner, module, diagnostics) }
      }
    }
    retire_: RetireExpression -> { validateExpression(retire_.actor, module, diagnostics) }
    actor: ActorCreationExpression -> {
      validateConstructionPlan(actor.resolvedConstruction, actor.span, module, diagnostics)
      if actor.resolvedConstructor != none { validateResolved(actor.resolvedConstructor!.resolvedType, actor.span, module, "actor constructor", diagnostics) }
      for argument of actor.args { validateExpression(argument, module, diagnostics) }
    }
    as_: AsExpression -> { validateExpression(as_.expression, module, diagnostics); validateTypeAnnotation(as_.targetType, module, diagnostics) }
    identifier: Identifier -> {
      if identifier.resolvedBinding == none { addValidationError(module, identifier.span, "Identifier '" + identifier.name + "' has no resolved binding", diagnostics) }
      else { validateResolved(identifier.resolvedBinding!.type_, identifier.span, module, "binding " + identifier.name, diagnostics) }
    }
    _ -> { }
  }
}

function validateConstructionPlan(plan: CheckedConstruction | none, span: SourceSpan, module: string, diagnostics: Diagnostic[]): none {
  if plan == none { addValidationError(module, span, "Construction has no checked plan", diagnostics); return }
  validateResolved(plan!.owner, span, module, "construction owner", diagnostics)
  validateResolved(plan!.signature, span, module, "construction signature", diagnostics)
  if plan!.defaults.length != plan!.signature.params.length {
    addValidationError(module, span, "Construction defaults do not match checked parameters", diagnostics)
  }
}

export function validateTypeAnnotation(annotation: TypeAnnotation, module: string, diagnostics: Diagnostic[]): none {
  case annotation {
    named: NamedType -> {
      validateResolved(named.resolvedType, named.span, module, "type annotation", diagnostics)
      for argument of named.typeArgs { validateTypeAnnotation(argument, module, diagnostics) }
    }
    array: ArrayType -> {
      validateResolved(array.resolvedType, array.span, module, "type annotation", diagnostics)
      validateTypeAnnotation(array.elementType, module, diagnostics)
    }
    union: UnionType -> {
      validateResolved(union.resolvedType, union.span, module, "type annotation", diagnostics)
      for member of union.types { validateTypeAnnotation(member, module, diagnostics) }
    }
    function_: AstFunctionType -> {
      validateResolved(function_.resolvedType, function_.span, module, "type annotation", diagnostics)
      for parameter of function_.params { validateTypeAnnotation(parameter.type_, module, diagnostics) }
      validateTypeAnnotation(function_.returnType, module, diagnostics)
    }
    weak_: WeakType -> {
      validateResolved(weak_.resolvedType, weak_.span, module, "type annotation", diagnostics)
      validateTypeAnnotation(weak_.type_, module, diagnostics)
    }
  }
}

export function validateResolved(resolvedType: ResolvedType | none, span: SourceSpan, module: string, owner: string, diagnostics: Diagnostic[]): none {
  if resolvedType == none { addValidationError(module, span, "Missing resolved type for " + owner, diagnostics); return }
  case resolvedType! {
    _: UnknownType -> { addValidationError(module, span, "Unknown resolved type for " + owner, diagnostics) }
    class_: ClassType -> { for argument of class_.typeArgs { validateResolved(argument, span, module, owner + " type argument", diagnostics) } }
    array: ArrayResolvedType -> { validateResolved(array.elementType, span, module, owner + " element", diagnostics) }
    map: MapResolvedType -> { validateResolved(map.keyType, span, module, owner + " key", diagnostics); validateResolved(map.valueType, span, module, owner + " value", diagnostics) }
    set_: SetResolvedType -> { validateResolved(set_.elementType, span, module, owner + " element", diagnostics) }
    stream: StreamResolvedType -> { validateResolved(stream.elementType, span, module, owner + " element", diagnostics) }
    result: ResultResolvedType -> { validateResolved(result.valueType, span, module, owner + " success", diagnostics); validateResolved(result.errorType, span, module, owner + " error", diagnostics) }
    actor: ActorType -> { validateResolved(optionalResolvedType(actor.innerClass), span, module, owner + " actor state", diagnostics) }
    promise: PromiseType -> { validateResolved(promise.valueType, span, module, owner + " promise value", diagnostics) }
    weak_: WeakResolvedType -> { validateResolved(weak_.inner, span, module, owner + " weak target", diagnostics) }
    tuple: TupleResolvedType -> { for item of tuple.elements { validateResolved(item, span, module, owner + " tuple element", diagnostics) } }
    union_: UnionResolvedType -> {
      conflict := unionMutabilityConflict(union_)
      if conflict != none { addValidationError(module, span, conflict!, diagnostics) }
      if union_.types.length == 0 { addValidationError(module, span, "Empty resolved union for " + owner, diagnostics) }
      for member of union_.types { validateResolved(member, span, module, owner + " union member", diagnostics) }
    }
    function_: FunctionType -> {
      for parameter of function_.params { validateResolved(parameter.type_, span, module, owner + " parameter", diagnostics) }
      validateResolved(function_.returnType, span, module, owner + " return", diagnostics)
    }
    parameter: TypeParameterType -> { if parameter.constraint != none { validateResolved(parameter.constraint, span, module, owner + " constraint", diagnostics) } }
    _ -> { }
  }
}

export function addValidationError(module: string, span: SourceSpan, message: string, diagnostics: Diagnostic[]): none {
  diagnostics.push(Diagnostic { severity: "error", message: message + " at " + string(span.start.line) + ":" + string(span.start.column), span: checkerSemanticSpan(span), module })
}

export function checkerSemanticSpan(span: SourceSpan): SemanticSpan {
  return SemanticSpan {
    start: SemanticLocation { line: span.start.line, column: span.start.column, offset: span.start.offset },
    end: SemanticLocation { line: span.end.line, column: span.end.column, offset: span.end.offset },
  }
}
