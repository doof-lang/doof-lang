import { SemanticTypeIdentities } from "./semantic-type-identities"
// Checked-AST traversal stops at ordered dependency events. Summaries own only
// immutable scalar data, never symbols, resolved types or AST nodes.
import {
  ActorCreationExpression, ArrayType, AstFunctionType, Block, CallExpression, ClassDeclaration, ConstDeclaration, ConstructExpression, EnumDeclaration,
  Expression, FunctionDeclaration, Identifier, ImmutableBinding, InterfaceDeclaration, MemberExpression, NamedType, ObjectLiteral,
  ReadonlyDeclaration, Statement, TupleLiteral, TypeAliasDeclaration,
  TypeAnnotation, UnionType, WeakType,
} from "./ast"
import { interfaceInstantiationKey } from "./emitter-monomorphize"
import { collectBlockExpressions, collectNestedExpressions } from "./ast-walk"
import { substituteTypeParams } from "./checker-types"
import {
  ActorType, ArrayResolvedType, ClassType, EnumType, FunctionType, InterfaceType, MapResolvedType, PromiseType,
  ResolvedType, ResultResolvedType, SuccessResolvedType, FailureResolvedType, SetResolvedType, StreamResolvedType, Symbol, TupleResolvedType, UnionResolvedType, WeakResolvedType,
} from "./semantic"


export class SymbolDependency {
  readonly modulePath: string
  readonly name: string
  readonly key: string
  readonly nativeHeader: string
  readonly forwardOnly: bool = false
}

export class InterfaceDependency {
  readonly key: string
}

export type DependencyEvent = SymbolDependency | InterfaceDependency

export class DependencySummary {
  readonly events: readonly DependencyEvent[]
}

export class DependencyBuilder {
  identities: SemanticTypeIdentities | none = none
  events: DependencyEvent[] = []
  symbols: Set<string> = []
  interfaces: Set<string> = []

  finish(): DependencySummary {
    return DependencySummary { events: events.drainToReadonly() }
  }
}

export function dependencyForSymbol(symbol: Symbol, forwardOnly: bool = false): SymbolDependency {
  name := if symbol.originalName == "" then symbol.name else symbol.originalName
  return SymbolDependency {
    modulePath: symbol.module,
    name,
    key: symbol.module + "::" + symbol.kind + "::" + name,
    nativeHeader: if symbol.native_ then symbol.nativeHeader else "",
    forwardOnly,
  }
}

function recordSymbol(symbol: Symbol, index: DependencyBuilder, forwardOnly: bool = false): none {
  if symbol.module == "" { return }
  dependency := dependencyForSymbol(symbol, forwardOnly)
  eventKey := dependency.key + (if forwardOnly then "::forward" else "::definition")
  if index.symbols.has(eventKey) { return }
  index.symbols.add(eventKey)
  index.events.push(dependency)
}

function recordInterface(index: DependencyBuilder, key: string): none {
  if index.interfaces.has(key) { return }
  index.interfaces.add(key)
  index.events.push(InterfaceDependency { key })
}

export function summarizeDeclaration(statement: Statement, identities: SemanticTypeIdentities | none = none): DependencySummary {
  builder := DependencyBuilder { identities }
  collectDependencySurface(statement, builder, true)
  return builder.finish()
}

export function collectDependencyExpression(
  expression: Expression,
  index: DependencyBuilder,
): none {
  // Reuse one growing worklist for the whole expression tree. The previous
  // recursive form allocated a temporary child array for every AST node,
  // which dominates worldview planning for expression-heavy modules.
  let expressions = [expression]
  let cursor = 0
  while cursor < expressions.length {
    current := expressions[cursor]
    cursor = cursor + 1
    if resolvedType := current.resolvedType { collectDependencyType(resolvedType, index) }
    case current {
      identifier: Identifier -> {
        if resolvedBinding := identifier.resolvedBinding && resolvedBinding.symbol != none {
          recordSymbol(resolvedBinding.symbol!, index)
        }
      }
      member: MemberExpression -> {
        if resolvedStaticOwner := member.resolvedStaticOwner && resolvedStaticOwner.resolvedSymbol != none {
          recordSymbol(resolvedStaticOwner.resolvedSymbol!, index)
        }
        if resolvedType := member.object.resolvedType { collectCompleteDependencyType(resolvedType, index) }
      }
      call: CallExpression -> {
        if resolvedConstruction := call.resolvedConstruction { collectCompleteDependencyType(resolvedConstruction.owner, index) }
        // A generic call converts its arguments to the specialized parameter
        // types, such as `Source<int>` for `drain<T>(source: Source<T>)`.
        if call.resolvedGenericTypeArgs.length > 0 && call.callee.resolvedType != none {
          if generic := call.callee.resolvedType! as FunctionType {
            if generic.typeParams.length == call.resolvedGenericTypeArgs.length {
              collectDependencyType(substituteTypeParams(generic, generic.typeParams, call.resolvedGenericTypeArgs), index)
            }
          }
        }
      }
      object: ObjectLiteral -> {
        if resolvedConstruction := object.resolvedConstruction { collectCompleteDependencyType(resolvedConstruction.owner, index) }
      }
      tuple: TupleLiteral -> {
        if resolvedConstruction := tuple.resolvedConstruction { collectCompleteDependencyType(resolvedConstruction.owner, index) }
      }
      construct: ConstructExpression -> {
        if resolvedConstruction := construct.resolvedConstruction { collectCompleteDependencyType(resolvedConstruction.owner, index) }
      }
      actor: ActorCreationExpression -> {
        if resolvedConstruction := actor.resolvedConstruction { collectCompleteDependencyType(resolvedConstruction.owner, index) }
      }
      _ -> { }
    }
    collectNestedExpressions(current, expressions)
  }
}

export function collectDependencyType(
  type_: ResolvedType,
  index: DependencyBuilder,
): none {
  index.identities?.prepare(type_)
  case type_ {
    class_: ClassType -> {
      forwardOnly := class_.symbol.kind == "class" && !class_.symbol.native_ && class_.typeArgs.length == 0
      recordSymbol(class_.symbol, index, forwardOnly)
      for argument of class_.typeArgs { collectDependencyType(argument, index) }
    }
    enum_: EnumType -> { recordSymbol(enum_.symbol, index) }
    interface_: InterfaceType -> {
      recordSymbol(interface_.symbol, index)
      if interface_.typeArgs.length > 0 {
        recordInterface(index, interfaceInstantiationKey(interface_.symbol.module, interface_.name, interface_.typeArgs))
      }
      for implementation of interface_.symbol.implementations {
        recordSymbol(implementation, index)
      }
      for argument of interface_.typeArgs { collectDependencyType(argument, index) }
    }
    actor: ActorType -> { collectDependencyType(actor.innerClass, index) }
    promise: PromiseType -> { collectDependencyType(promise.valueType, index) }
    array: ArrayResolvedType -> { collectDependencyType(array.elementType, index) }
    map: MapResolvedType -> {
      collectDependencyType(map.keyType, index)
      collectDependencyType(map.valueType, index)
    }
    set_: SetResolvedType -> { collectDependencyType(set_.elementType, index) }
    stream: StreamResolvedType -> {
      recordInterface(index, interfaceInstantiationKey("", "Stream", [stream.elementType]))
      collectDependencyType(stream.elementType, index)
    }
    result_: ResultResolvedType -> {
      collectDependencyType(result_.valueType, index)
      collectDependencyType(result_.errorType, index)
    }
    success: SuccessResolvedType -> { collectDependencyType(success.valueType, index) }
    failure: FailureResolvedType -> { collectDependencyType(failure.errorType, index) }
    tuple: TupleResolvedType -> { for element of tuple.elements { collectDependencyType(element, index) } }
    union_: UnionResolvedType -> { for member of union_.types { collectDependencyType(member, index) } }
    weak_: WeakResolvedType -> { collectDependencyType(weak_.inner, index) }
    function_: FunctionType -> {
      for parameter of function_.params { collectDependencyType(parameter.type_, index) }
      collectDependencyType(function_.returnType, index)
    }
    _ -> { }
  }
}

// Operations that inspect or construct a type need complete definitions for
// every nominal alternative the generated C++ operation can visit.
export function collectCompleteDependencyType(type_: ResolvedType, index: DependencyBuilder): none {
  index.identities?.prepare(type_)
  case type_ {
    class_: ClassType -> {
      recordSymbol(class_.symbol, index)
      for argument of class_.typeArgs { collectCompleteDependencyType(argument, index) }
    }
    enum_: EnumType -> { recordSymbol(enum_.symbol, index) }
    interface_: InterfaceType -> {
      recordSymbol(interface_.symbol, index)
      if interface_.typeArgs.length > 0 {
        recordInterface(index, interfaceInstantiationKey(interface_.symbol.module, interface_.name, interface_.typeArgs))
      }
      for implementation of interface_.symbol.implementations { recordSymbol(implementation, index) }
      for argument of interface_.typeArgs { collectCompleteDependencyType(argument, index) }
    }
    actor: ActorType -> { collectCompleteDependencyType(actor.innerClass, index) }
    promise: PromiseType -> { collectCompleteDependencyType(promise.valueType, index) }
    array: ArrayResolvedType -> { collectCompleteDependencyType(array.elementType, index) }
    map: MapResolvedType -> {
      collectCompleteDependencyType(map.keyType, index)
      collectCompleteDependencyType(map.valueType, index)
    }
    set_: SetResolvedType -> { collectCompleteDependencyType(set_.elementType, index) }
    stream: StreamResolvedType -> {
      recordInterface(index, interfaceInstantiationKey("", "Stream", [stream.elementType]))
      collectCompleteDependencyType(stream.elementType, index)
    }
    result_: ResultResolvedType -> {
      collectCompleteDependencyType(result_.valueType, index)
      collectCompleteDependencyType(result_.errorType, index)
    }
    success: SuccessResolvedType -> { collectCompleteDependencyType(success.valueType, index) }
    failure: FailureResolvedType -> { collectCompleteDependencyType(failure.errorType, index) }
    tuple: TupleResolvedType -> { for element of tuple.elements { collectCompleteDependencyType(element, index) } }
    union_: UnionResolvedType -> { for member of union_.types { collectCompleteDependencyType(member, index) } }
    weak_: WeakResolvedType -> { collectCompleteDependencyType(weak_.inner, index) }
    function_: FunctionType -> {
      for parameter of function_.params { collectCompleteDependencyType(parameter.type_, index) }
      collectCompleteDependencyType(function_.returnType, index)
    }
    _ -> { }
  }
}


export function collectDependencySurface(
  statement: Statement,
  index: DependencyBuilder,
  foreign: bool,
): none {
  case statement {
    fn: FunctionDeclaration -> {
      if resolvedType := fn.resolvedType { collectDependencyType(resolvedType, index) }
      if returnType := fn.returnType { collectAnnotationAliases(returnType, index) }
      for parameter of fn.params {
        if resolvedType := parameter.resolvedType { collectDependencyType(resolvedType, index) }
        if type_ := parameter.type_ { collectAnnotationAliases(type_, index) }
        if defaultValue := parameter.defaultValue { collectDependencyExpression(defaultValue, index) }
      }
      if !foreign { collectFunctionBody(fn, index) }
    }
    class_: ClassDeclaration -> {
      for field of class_.fields {
        if resolvedType := field.resolvedType { collectDependencyType(resolvedType, index) }
        if type_ := field.type_ { collectAnnotationAliases(type_, index) }
        if defaultValue := field.defaultValue { collectDependencyExpression(defaultValue, index) }
      }
      for method of class_.methods {
        if resolvedType := method.resolvedType { collectDependencyType(resolvedType, index) }
        if returnType := method.returnType { collectAnnotationAliases(returnType, index) }
        for parameter of method.params {
          if resolvedType := parameter.resolvedType { collectDependencyType(resolvedType, index) }
          if type_ := parameter.type_ { collectAnnotationAliases(type_, index) }
          if defaultValue := parameter.defaultValue { collectDependencyExpression(defaultValue, index) }
        }
        if !foreign { collectFunctionBody(method, index) }
      }
      if !foreign && class_.destructor_ != none {
        let expressions: Expression[] = []
        collectBlockExpressions(class_.destructor_!, expressions)
        for expression of expressions { collectDependencyExpression(expression, index) }
      }
      if resolvedSymbol := class_.resolvedSymbol {
        for implementation of resolvedSymbol.implementations {
          recordSymbol(implementation, index)
        }
      }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields {
        if resolvedType := field.resolvedType { collectDependencyType(resolvedType, index) }
        collectAnnotationAliases(field.type_, index)
      }
      for field of interface_.staticFields {
        if resolvedType := field.resolvedType { collectDependencyType(resolvedType, index) }
        collectAnnotationAliases(field.type_, index)
      }
      for method of interface_.methods {
        if resolvedType := method.resolvedType { collectDependencyType(resolvedType, index) }
        if returnType := method.returnType { collectAnnotationAliases(returnType, index) }
        for parameter of method.params { if type_ := parameter.type_ { collectAnnotationAliases(type_, index) } }
      }
      for method of interface_.staticMethods {
        if resolvedType := method.resolvedType { collectDependencyType(resolvedType, index) }
        if returnType := method.returnType { collectAnnotationAliases(returnType, index) }
        for parameter of method.params { if type_ := parameter.type_ { collectAnnotationAliases(type_, index) } }
      }
      if resolvedSymbol := interface_.resolvedSymbol {
        for implementation of resolvedSymbol.implementations {
          recordSymbol(implementation, index)
        }
      }
    }
    alias: TypeAliasDeclaration -> {
      if resolvedType := alias.resolvedType { collectDependencyType(resolvedType, index) }
      collectAnnotationAliases(alias.type_, index)
    }
    const_: ConstDeclaration -> {
      if resolvedType := const_.resolvedType { collectDependencyType(resolvedType, index) }
      if type_ := const_.type_ { collectAnnotationAliases(type_, index) }
    }
    readonly_: ReadonlyDeclaration -> {
      if resolvedType := readonly_.resolvedType { collectDependencyType(resolvedType, index) }
      if type_ := readonly_.type_ { collectAnnotationAliases(type_, index) }
    }
    binding: ImmutableBinding -> {
      if resolvedType := binding.resolvedType { collectDependencyType(resolvedType, index) }
      if type_ := binding.type_ { collectAnnotationAliases(type_, index) }
    }
    enum_: EnumDeclaration -> {
      for variant of enum_.variants { if value := variant.value { collectDependencyExpression(value, index) } }
    }
    _ -> { }
  }
}

function collectAnnotationAliases(
  annotation: TypeAnnotation,
  index: DependencyBuilder,
): none {
  case annotation {
    named: NamedType -> {
      if resolvedSymbol := named.resolvedSymbol && resolvedSymbol.kind == "type-alias" {
        recordSymbol(resolvedSymbol, index)
      }
      for argument of named.typeArgs { collectAnnotationAliases(argument, index) }
    }
    array: ArrayType -> { collectAnnotationAliases(array.elementType, index) }
    union_: UnionType -> { for member of union_.types { collectAnnotationAliases(member, index) } }
    function_: AstFunctionType -> {
      for parameter of function_.params { collectAnnotationAliases(parameter.type_, index) }
      collectAnnotationAliases(function_.returnType, index)
    }
    weak_: WeakType -> { collectAnnotationAliases(weak_.type_, index) }
  }
}

function collectFunctionBody(
  fn: FunctionDeclaration,
  index: DependencyBuilder,
): none {
  let expressions: Expression[] = []
  case fn.body {
    block: Block -> { collectBlockExpressions(block, expressions) }
    expression: Expression -> { expressions.push(expression) }
  }
  for expression of expressions { collectDependencyExpression(expression, index) }
}
