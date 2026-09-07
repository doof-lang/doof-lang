import { SemanticTypeIdentities } from "./semantic-type-identities"
// Checked-AST traversal stops at ordered dependency events. Summaries own only
// immutable scalar data, never symbols, resolved types or AST nodes.
import {
  ArrayType, AstFunctionType, Block, ClassDeclaration, ConstDeclaration, EnumDeclaration, ExportDeclaration, Expression, FunctionDeclaration, Identifier,
  ImmutableBinding, InterfaceDeclaration, MemberExpression, NamedType, ReadonlyDeclaration, Statement, TypeAliasDeclaration,
  TypeAnnotation, UnionType, WeakType,
} from "./ast"
import { interfaceInstantiationKey } from "./emitter-monomorphize"
import { collectBlockExpressions, collectNestedExpressions } from "./ast-walk"
import {
  ActorType, ArrayResolvedType, ClassType, EnumType, FunctionType, InterfaceType, MapResolvedType, PromiseType,
  ResolvedType, ResultResolvedType, SetResolvedType, StreamResolvedType, Symbol, TupleResolvedType, UnionResolvedType, WeakResolvedType,
} from "./semantic"


export class SymbolDependency {
  readonly modulePath: string
  readonly name: string
  readonly key: string
  readonly nativeHeader: string
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

export function dependencyForSymbol(symbol: Symbol): SymbolDependency {
  name := if symbol.originalName == "" then symbol.name else symbol.originalName
  return SymbolDependency {
    modulePath: symbol.module,
    name,
    key: symbol.module + "::" + symbol.kind + "::" + name,
    nativeHeader: if symbol.native_ then symbol.nativeHeader else "",
  }
}

function recordSymbol(symbol: Symbol, index: DependencyBuilder): none {
  if symbol.module == "" { return }
  dependency := dependencyForSymbol(symbol)
  if index.symbols.has(dependency.key) { return }
  index.symbols.add(dependency.key)
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
    if current.resolvedType != none { collectDependencyType(current.resolvedType!, index) }
    case current {
      identifier: Identifier -> {
        if identifier.resolvedBinding != none && identifier.resolvedBinding!.symbol != none {
          recordSymbol(identifier.resolvedBinding!.symbol!, index)
        }
      }
      member: MemberExpression -> {
        if member.resolvedNamespaceSymbol != none {
          recordSymbol(member.resolvedNamespaceSymbol!, index)
        }
        if member.resolvedStaticOwner != none && member.resolvedStaticOwner!.resolvedSymbol != none {
          recordSymbol(member.resolvedStaticOwner!.resolvedSymbol!, index)
        }
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
  if index.identities != none { index.identities!.prepare(type_) }
  case type_ {
    class_: ClassType -> {
      recordSymbol(class_.symbol, index)
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


export function collectDependencySurface(
  statement: Statement,
  index: DependencyBuilder,
  foreign: bool,
): none {
  case statement {
    export_: ExportDeclaration -> { collectDependencySurface(export_.declaration, index, foreign) }
    fn: FunctionDeclaration -> {
      if fn.resolvedType != none { collectDependencyType(fn.resolvedType!, index) }
      if fn.returnType != none { collectAnnotationAliases(fn.returnType!, index) }
      for parameter of fn.params {
        if parameter.resolvedType != none { collectDependencyType(parameter.resolvedType!, index) }
        if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, index) }
        if parameter.defaultValue != none { collectDependencyExpression(parameter.defaultValue!, index) }
      }
      if !foreign { collectFunctionBody(fn, index) }
    }
    class_: ClassDeclaration -> {
      for field of class_.fields {
        if field.resolvedType != none { collectDependencyType(field.resolvedType!, index) }
        if field.type_ != none { collectAnnotationAliases(field.type_!, index) }
        if field.defaultValue != none { collectDependencyExpression(field.defaultValue!, index) }
      }
      for method of class_.methods {
        if method.resolvedType != none { collectDependencyType(method.resolvedType!, index) }
        if method.returnType != none { collectAnnotationAliases(method.returnType!, index) }
        for parameter of method.params {
          if parameter.resolvedType != none { collectDependencyType(parameter.resolvedType!, index) }
          if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, index) }
          if parameter.defaultValue != none { collectDependencyExpression(parameter.defaultValue!, index) }
        }
        if !foreign { collectFunctionBody(method, index) }
      }
      if class_.resolvedSymbol != none {
        for implementation of class_.resolvedSymbol!.implementations {
          recordSymbol(implementation, index)
        }
      }
    }
    interface_: InterfaceDeclaration -> {
      for field of interface_.fields {
        if field.resolvedType != none { collectDependencyType(field.resolvedType!, index) }
        collectAnnotationAliases(field.type_, index)
      }
      for method of interface_.methods {
        if method.resolvedType != none { collectDependencyType(method.resolvedType!, index) }
        if method.returnType != none { collectAnnotationAliases(method.returnType!, index) }
        for parameter of method.params { if parameter.type_ != none { collectAnnotationAliases(parameter.type_!, index) } }
      }
      if interface_.resolvedSymbol != none {
        for implementation of interface_.resolvedSymbol!.implementations {
          recordSymbol(implementation, index)
        }
      }
    }
    alias: TypeAliasDeclaration -> {
      if alias.resolvedType != none { collectDependencyType(alias.resolvedType!, index) }
      collectAnnotationAliases(alias.type_, index)
    }
    const_: ConstDeclaration -> {
      if const_.resolvedType != none { collectDependencyType(const_.resolvedType!, index) }
      if const_.type_ != none { collectAnnotationAliases(const_.type_!, index) }
    }
    readonly_: ReadonlyDeclaration -> {
      if readonly_.resolvedType != none { collectDependencyType(readonly_.resolvedType!, index) }
      if readonly_.type_ != none { collectAnnotationAliases(readonly_.type_!, index) }
    }
    binding: ImmutableBinding -> {
      if binding.resolvedType != none { collectDependencyType(binding.resolvedType!, index) }
      if binding.type_ != none { collectAnnotationAliases(binding.type_!, index) }
    }
    enum_: EnumDeclaration -> {
      for variant of enum_.variants { if variant.value != none { collectDependencyExpression(variant.value!, index) } }
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
      if named.resolvedSymbol != none && named.resolvedSymbol!.kind == "type-alias" {
        recordSymbol(named.resolvedSymbol!, index)
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

