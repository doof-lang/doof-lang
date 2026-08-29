// Interface implementation discovery and structural conformance.

import {
  ActorType, ArrayResolvedType, Binding, CheckResult, ClassType, EnumType, InterfaceType,
  Diagnostic, FunctionParamType, FunctionType,
  JsonValueResolvedType, MapResolvedType, NoneType, PrimitiveType, PromiseType, ResolvedType, ResultResolvedType, Scope, SemanticLocation, SemanticSpan, SetResolvedType, Symbol,
  StreamResolvedType, TupleResolvedType, UnionResolvedType, UnknownType, TypeParameterType, WeakResolvedType,
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
  YieldStatement, CaseArm, CaseExpression, CasePattern, CaseStatement, TypePattern, ValuePattern, WildcardPattern,
  TryStatement,
  AsyncExpression, RetireExpression, ActorCreationExpression, Parameter,
} from "./ast"
import {
  actorType, applyDeepReadonly, arrayType, classType, enumType, functionType, interfaceType, isAssignable, isNumeric, joinTypes,
  isJsonValueType, jsonObjectType, jsonValueType, mapType, resultType, streamType,
  noneType, numericResult, primitive, promiseType, sameType, tupleType, typeName, unionType,
  substituteTypeParams, typeParameter, unknownType,
} from "./checker-types"
import { canGenerateJsonDeserialization, canGenerateJsonSerialization } from "./json-semantics"
import { findActorBoundaryViolation } from "./checker-actor-boundary"
import { collectRetiredActorBindings, reportRetiredActorUses } from "./checker-actor-lifecycle"


import { methodSignature, resolveAnnotation, declarationFor, symbolName } from "./checker-symbols"

export function symbolSpan(info: ModuleInfo, name: string): SourceSpan {
  for statement of info.program.statements { if symbolName(statement) == name { return statement.span } }
  return info.program.span
}

export function findModule(result: AnalysisResult, path: string): ModuleInfo | none {
  for module of result.modules { if module.path == path { return module } }
  return none
}

// Interface lowering is closed-world: every class in the analyzed graph is a
// candidate, including classes that do not spell an explicit `implements` list.
// Populate this map before checking expressions so ordinary assignment and
// return compatibility can use the same structural result as emission.
export function discoverInterfaceImplementations(result: AnalysisResult): none {
  for interfaceModule of result.modules {
    for interfaceSymbol of interfaceModule.symbols {
      if interfaceSymbol.kind != "interface" { continue }
      for classModule of result.modules {
        for classSymbol of classModule.symbols {
          if classSymbol.kind != "class" { continue }
          if classSatisfiesInterface(result, classSymbol, interfaceSymbol) {
            if !containsImplementation(interfaceSymbol.implementations, classSymbol) {
              interfaceSymbol.implementations.push(classSymbol)
            }
          }
        }
      }
    }
  }
}

export function containsImplementation(implementations: Symbol[], candidate: Symbol): bool {
  for implementation of implementations {
    if implementation.module == candidate.module && implementation.name == candidate.name { return true }
  }
  return false
}

export function addImplementedInterfaceType(symbol: Symbol, name: string): none {
  for existing of symbol.implementedInterfaceTypes { if existing == name { return } }
  symbol.implementedInterfaceTypes.push(name)
}

// Concrete generic interfaces remain structural. Record matching ordinary
// classes as soon as a concrete interface use is resolved so subsequent
// assignment and call compatibility can use the normal assignability path.
export function registerConcreteInterfaceImplementations(result: AnalysisResult, interface_: InterfaceType): none {
  for module of result.modules {
    for symbol of module.symbols {
      if symbol.kind != "class" { continue }
      declaration := declarationFor(result, symbol)
      if declaration == none { continue }
      case declaration! {
        class_: ClassDeclaration -> {
          if class_.typeParams.length == 0 && classSatisfiesConcreteInterface(result, class_, classType(class_.name, symbol), interface_) {
            addImplementedInterfaceType(symbol, typeName(interface_))
          }
        }
        _ -> { }
      }
    }
  }
}

export function concreteTypes(types: ResolvedType[]): bool {
  for type_ of types {
    case type_ {
      _: TypeParameterType -> { return false }
      class_: ClassType -> { if !concreteTypes(class_.typeArgs) { return false } }
      interface_: InterfaceType -> { if !concreteTypes(interface_.typeArgs) { return false } }
      array: ArrayResolvedType -> { if !concreteTypes([array.elementType]) { return false } }
      map: MapResolvedType -> { if !concreteTypes([map.keyType, map.valueType]) { return false } }
      set_: SetResolvedType -> { if !concreteTypes([set_.elementType]) { return false } }
      stream: StreamResolvedType -> { if !concreteTypes([stream.elementType]) { return false } }
      result_: ResultResolvedType -> { if !concreteTypes([result_.valueType, result_.errorType]) { return false } }
      tuple: TupleResolvedType -> { if !concreteTypes(tuple.elements) { return false } }
      union_: UnionResolvedType -> { if !concreteTypes(union_.types) { return false } }
      weak_: WeakResolvedType -> { if !concreteTypes([weak_.inner]) { return false } }
      function_: FunctionType -> {
        for parameter of function_.params { if !concreteTypes([parameter.type_]) { return false } }
        if !concreteTypes([function_.returnType]) { return false }
      }
      _ -> { }
    }
  }
  return true
}

export function classSatisfiesConcreteInterface(result: AnalysisResult, class_: ClassDeclaration, classType_: ClassType, interfaceType_: InterfaceType): bool {
  return classSatisfiesConcreteInterfaceSeen(result, class_, classType_, interfaceType_, [])
}

function classSatisfiesConcreteInterfaceSeen(result: AnalysisResult, class_: ClassDeclaration, classType_: ClassType, interfaceType_: InterfaceType, seen: string[]): bool {
  key := concreteInterfacePairKey(classType_, interfaceType_)
  if containsString(seen, key) { return true }
  let next = [key]
  for existing of seen { next.push(existing) }
  declaration := declarationFor(result, interfaceType_.symbol)
  if declaration == none { return false }
  case declaration! {
    interface_: InterfaceDeclaration -> {
      for required of interface_.fields {
        actualField := findClassField(class_.fields, required.name)
        if actualField == none || actualField!.private_ { return false }
        if required.readonly_ && !actualField!.readonly_ { return false }
        if required.let_ && !actualField!.let_ { return false }
        actualBase := resolvedClassFieldType(result, actualField!, classType_.symbol, class_.typeParams)
        if actualBase == none { return false }
        requiredBase := if required.resolvedType == none then resolveAnnotation(required.type_, classModuleFor(result, interfaceType_.symbol), result, interface_.typeParams) else required.resolvedType!
        actual := substituteTypeParams(actualBase!, class_.typeParams, classType_.typeArgs)
        expected := substituteTypeParams(requiredBase, interface_.typeParams, interfaceType_.typeArgs)
        if !isAssignableWithInterfacesSeen(result, actual, expected, next) { return false }
      }
      for requiredMethod of interface_.methods {
        actualMethod := findClassMethod(class_.methods, requiredMethod.name, requiredMethod.static_)
        if actualMethod == none || actualMethod!.private_ { return false }
        actualBase := if actualMethod!.resolvedType == none then methodSignature(actualMethod!, classModuleFor(result, classType_.symbol), result) else actualMethod!.resolvedType!
        requiredBase := if requiredMethod.resolvedType == none then methodSignature(requiredMethod, classModuleFor(result, interfaceType_.symbol), result) else requiredMethod.resolvedType!
        actual := substituteTypeParams(actualBase, class_.typeParams, classType_.typeArgs)
        expected := substituteTypeParams(requiredBase, interface_.typeParams, interfaceType_.typeArgs)
        if !compatibleConcreteMethodType(result, actual, expected, next) { return false }
      }
      return true
    }
    _ -> { return false }
  }
  return false
}

export function classSatisfiesInterface(result: AnalysisResult, classSymbol: Symbol, interfaceSymbol: Symbol): bool {
  classDeclaration := declarationFor(result, classSymbol)
  interfaceDeclaration := declarationFor(result, interfaceSymbol)
  if classDeclaration == none || interfaceDeclaration == none { return false }
  case classDeclaration! {
    class_: ClassDeclaration -> {
      case interfaceDeclaration! {
        interface_: InterfaceDeclaration -> {
          return classSatisfiesConcreteInterface(
            result,
            class_,
            classType(class_.name, classSymbol),
            interfaceType(interface_.name, interfaceSymbol),
          )
        }
        _ -> { }
      }
    }
    _ -> { }
  }
  return false
}

export function isAssignableWithInterfaces(result: AnalysisResult, value: ResolvedType, target: ResolvedType): bool {
  return isAssignableWithInterfacesSeen(result, value, target, [])
}

function isAssignableWithInterfacesSeen(result: AnalysisResult, value: ResolvedType, target: ResolvedType, seen: string[]): bool {
  if isAssignable(value, target) { return true }
  case value {
    union_: UnionResolvedType -> {
      for member of union_.types {
        if !isAssignableWithInterfacesSeen(result, member, target, seen) { return false }
      }
      return true
    }
    function_: FunctionType -> {
      case target {
        targetFunction: FunctionType -> { return compatibleConcreteMethodType(result, function_, targetFunction, seen) }
        _ -> { }
      }
    }
    class_: ClassType -> {
      case target {
        interface_: InterfaceType -> {
          declaration := declarationFor(result, class_.symbol)
          if declaration == none { return false }
          case declaration! {
            owner: ClassDeclaration -> { return classSatisfiesConcreteInterfaceSeen(result, owner, class_, interface_, seen) }
            _ -> { }
          }
        }
        _ -> { }
      }
    }
    _ -> { }
  }
  case target {
    union_: UnionResolvedType -> {
      for member of union_.types {
        if isAssignableWithInterfacesSeen(result, value, member, seen) { return true }
      }
    }
    _ -> { }
  }
  return false
}

function compatibleConcreteMethodType(result: AnalysisResult, actual: ResolvedType, expected: ResolvedType, seen: string[]): bool {
  case actual {
    actualFunction: FunctionType -> {
      case expected {
        expectedFunction: FunctionType -> {
          if actualFunction.params.length != expectedFunction.params.length { return false }
          for index of 0..<actualFunction.params.length {
            if !sameType(actualFunction.params[index].type_, expectedFunction.params[index].type_) { return false }
          }
          return isAssignableWithInterfacesSeen(result, actualFunction.returnType, expectedFunction.returnType, seen)
        }
        _ -> { return false }
      }
    }
    _ -> { return sameType(actual, expected) }
  }
  return false
}

function resolvedClassFieldType(result: AnalysisResult, field: ClassField, symbol: Symbol, typeParams: string[]): ResolvedType | none {
  if field.resolvedType != none { return field.resolvedType }
  if field.type_ == none { return none }
  return resolveAnnotation(field.type_!, classModuleFor(result, symbol), result, typeParams)
}

function concreteInterfacePairKey(class_: ClassType, interface_: InterfaceType): string {
  return class_.symbol.module + "::" + typeName(class_) + "->" + interface_.symbol.module + "::" + typeName(interface_)
}

function containsString(values: string[], value: string): bool {
  for existing of values { if existing == value { return true } }
  return false
}

export function findClassField(fields: ClassField[], name: string): ClassField | none {
  for field of fields { for fieldName of field.names { if fieldName == name { return field } } }
  return none
}

export function findClassMethod(methods: FunctionDeclaration[], name: string, static_: bool): FunctionDeclaration | none {
  for method of methods { if method.name == name && method.static_ == static_ { return method } }
  return none
}

export function classModuleFor(result: AnalysisResult, symbol: Symbol): ModuleInfo {
  module := findModule(result, symbol.module)
  if module == none { panic("Missing module for symbol " + symbol.name) }
  return module!
}
