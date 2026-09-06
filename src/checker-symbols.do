// Binding, symbol, builtin, annotation, and scope helpers.

import { resolveProvisionalAnnotation } from "./checker-annotations"

import { ArrayResolvedType, Binding, ClassType, FunctionParamType, FunctionType, MapResolvedType, RangeResolvedType, ResolvedType, Scope, SetResolvedType, Symbol, StreamResolvedType, UnionResolvedType, WeakResolvedType } from "./semantic"
import { AnalysisResult, ModuleInfo } from "./analyzer"
import { ArrayType, Block, ClassDeclaration, ConstDeclaration, EnumDeclaration, Expression, FunctionDeclaration, AstFunctionType, IfStatement, ImmutableBinding, Identifier, InterfaceDeclaration, LetDeclaration, NamedType, ObjectProperty, ReadonlyDeclaration, Statement, TypeAliasDeclaration, TypeAnnotation, UnionType, WithStatement, BreakStatement, CaseStatement, TypePattern, WeakType } from "./ast"
import { classType, enumType, functionType, interfaceType, jsonValueType, resultType, neverType, noneType, primitive, tupleType, unionType, typeParameter, unknownType } from "./checker-types"

import { symbolSpan, findModule } from "./checker-interfaces"
import { checkerSemanticSpan } from "./checker-validation"

export function builtinSourceLocationType(): ClassType {
  return classType("SourceLocation", Symbol {
    kind: "class",
    name: "SourceLocation",
    module: "<builtin>",
    exported: true,
    native_: true,
    nativeHeader: "doof_runtime.hpp",
    nativeCppName: "doof::SourceLocation",
  })
}

export function casePatternName(pattern: TypePattern): string {
  case pattern.type_ {
    named: NamedType -> {
      if named.name == "Success" || named.name == "Failure" { return named.name }
    }
    _ -> { }
  }
  return ""
}

export function decorateAnnotationWithResolved(annotation: TypeAnnotation, resolved: ResolvedType): none {
  case annotation {
    named: NamedType -> {
      named.resolvedType = optionalResolvedType(resolved)
      case resolved {
        class_: ClassType -> {
          for i of 0..<named.typeArgs.length {
            if i < class_.typeArgs.length { decorateAnnotationWithResolved(named.typeArgs[i], class_.typeArgs[i]) }
          }
        }
        _ -> { }
      }
    }
    array: ArrayType -> {
      array.resolvedType = optionalResolvedType(resolved)
      case resolved {
        arrayResolved: ArrayResolvedType -> { decorateAnnotationWithResolved(array.elementType, arrayResolved.elementType) }
        _ -> { }
      }
    }
    union: UnionType -> {
      union.resolvedType = optionalResolvedType(resolved)
      case resolved {
        unionResolved: UnionResolvedType -> {
          for i of 0..<union.types.length {
            if i < unionResolved.types.length { decorateAnnotationWithResolved(union.types[i], unionResolved.types[i]) }
          }
        }
        _ -> { }
      }
    }
    function_: AstFunctionType -> {
      function_.resolvedType = optionalResolvedType(resolved)
      case resolved {
        functionResolved: FunctionType -> {
          for i of 0..<function_.params.length {
            if i < functionResolved.params.length { decorateAnnotationWithResolved(function_.params[i].type_, functionResolved.params[i].type_) }
          }
          decorateAnnotationWithResolved(function_.returnType, functionResolved.returnType)
        }
        _ -> { }
      }
    }
    weak_: WeakType -> {
      weak_.resolvedType = optionalResolvedType(resolved)
      case resolved {
        weakResolved: WeakResolvedType -> { decorateAnnotationWithResolved(weak_.type_, weakResolved.inner) }
        _ -> { }
      }
    }
  }
}

// An unconditional loop completes normally only when its own body can break
// out. Breaks nested inside another loop belong to that inner loop and do not
// make the outer loop complete.
export function blockContainsLoopExit(block: Block): bool {
  for statement of block.statements {
    case statement {
      _: BreakStatement -> { return true }
      if_: IfStatement -> {
        if blockContainsLoopExit(if_.body) { return true }
        for branch of if_.elseIfs { if blockContainsLoopExit(branch.body) { return true } }
        if if_.else_ != none && blockContainsLoopExit(if_.else_!) { return true }
      }
      case_: CaseStatement -> {
        for arm of case_.arms {
          case arm.body {
            armBlock: Block -> { if blockContainsLoopExit(armBlock) { return true } }
            _ -> { }
          }
        }
      }
      with_: WithStatement -> { if blockContainsLoopExit(with_.body) { return true } }
      nested: Block -> { if blockContainsLoopExit(nested) { return true } }
      _ -> { }
    }
  }
  return false
}

export function optionalResolvedType(value: ResolvedType): ResolvedType | none { return value }

export function functionParameterIndex(parameters: FunctionParamType[], name: string): int {
  for i of 0..<parameters.length { if parameters[i].name == name { return i } }
  return -1
}

export function containsString(values: string[], value: string): bool {
  for existing of values { if existing == value { return true } }
  return false
}

export function hasObjectProperty(properties: ObjectProperty[], name: string): bool {
  for property of properties { if property.name == name { return true } }
  return false
}

export function predeclareModuleBindings(info: ModuleInfo, scope: Scope, result: AnalysisResult): none {
  for symbol of info.symbols {
    if symbol.kind == "function" || symbol.kind == "class" || symbol.kind == "struct" || symbol.kind == "interface" || symbol.kind == "enum" {
      declare(scope, Binding { name: symbol.name, kind: symbol.kind, type_: symbolType(symbol, info, result), mutable: false, span: checkerSemanticSpan(symbolSpan(info, symbol.name)), module: info.path, symbol })
    }
  }
  for imported of info.imports {
    if !imported.typeOnly && imported.symbol != none && isValueSymbol(imported.symbol!) {
      declare(scope, Binding { name: imported.localName, kind: "import", type_: symbolType(imported.symbol!, info, result), mutable: false, span: checkerSemanticSpan(symbolSpan(info, imported.localName)), module: info.path, symbol: imported.symbol })
    }
  }
}

export function isNamespaceImport(info: ModuleInfo, name: string): bool {
  for imported of info.namespaceImports { if imported.localName == name { return true } }
  return false
}

export function isTypeOnlyNamespaceImport(info: ModuleInfo, name: string): bool {
  for imported of info.namespaceImports { if imported.localName == name { return imported.typeOnly } }
  return false
}

export function namespaceMemberType(info: ModuleInfo, namespaceName: string, memberName: string, result: AnalysisResult): ResolvedType {
  symbol := namespaceMemberSymbol(info, namespaceName, memberName, result)
  if symbol == none { return unknownType() }
  source := findModule(result, symbol!.module)
  if source == none { return unknownType() }
  return symbolType(symbol!, source!, result)
}

export function namespaceMemberSymbol(info: ModuleInfo, namespaceName: string, memberName: string, result: AnalysisResult): Symbol | none {
  for imported of info.namespaceImports {
    if imported.localName != namespaceName { continue }
    if imported.typeOnly { return none }
    source := findModule(result, imported.sourceModule)
    if source == none { return none }
    for symbol of source!.exports {
      if symbol.name == memberName && isValueSymbol(symbol) { return symbol }
    }
  }
  return none
}

export function symbolType(symbol: Symbol, info: ModuleInfo, result: AnalysisResult): ResolvedType {
  if symbol.kind == "class" || symbol.kind == "struct" { return classType(declaredSymbolName(symbol), symbol) }
  if symbol.kind == "interface" { return interfaceType(declaredSymbolName(symbol), symbol) }
  if symbol.kind == "enum" { return enumType(declaredSymbolName(symbol), symbol) }
  declaration := declarationFor(result, symbol)
  if declaration == none { return unknownType() }
  case declaration! {
    fn: FunctionDeclaration -> {
      if fn.resolvedType != none {
        case fn.resolvedType! {
          resolved: FunctionType -> { return resolved }
          _ -> { }
        }
      }
      return methodSignature(fn, info, result)
    }
    alias: TypeAliasDeclaration -> { return resolveAnnotation(alias.type_, info, result) }
    const_: ConstDeclaration -> { if const_.resolvedType != none { return const_.resolvedType! } }
    readonly_: ReadonlyDeclaration -> { if readonly_.resolvedType != none { return readonly_.resolvedType! } }
    binding: ImmutableBinding -> { if binding.resolvedType != none { return binding.resolvedType! } }
    _ -> { return unknownType() }
  }
  return unknownType()
}

// Imported member lookup needs a declaration's signature without checking its
// body in the caller's module scope. This also keeps cross-module context
// objects usable when their implementation methods refer to local imports.
export function methodSignature(method: FunctionDeclaration, info: ModuleInfo, result: AnalysisResult, ownerTypeParams: string[] = []): ResolvedType {
  let typeParams: string[] = []
  for name of ownerTypeParams { typeParams.push(name) }
  for name of method.typeParams { typeParams.push(name) }
  return functionType(functionParametersFor(method, info, result, ownerTypeParams), if method.returnType == none then noneType() else resolveAnnotation(method.returnType!, info, result, typeParams), method.typeParams)
}

export function functionParametersFor(fn: FunctionDeclaration, info: ModuleInfo, result: AnalysisResult, ownerTypeParams: string[] = []): FunctionParamType[] {
  let typeParams: string[] = []
  for name of ownerTypeParams { typeParams.push(name) }
  for name of fn.typeParams { typeParams.push(name) }
  let resultTypes: FunctionParamType[] = []
  for parameter of fn.params {
    parameterType := if parameter.resolvedType != none then parameter.resolvedType! else if parameter.type_ == none then unknownType() else resolveAnnotation(parameter.type_!, info, result, typeParams)
    resultTypes.push(FunctionParamType { name: parameter.name, type_: parameterType, hasDefault: parameter.defaultValue != none })
  }
  return resultTypes
}

export function declare(scope: Scope, binding: Binding): bool {
  for existing of scope.bindings { if existing.name == binding.name { return false } }
  scope.bindings.push(binding)
  return true
}

// Parameters intentionally shadow implicit field and method bindings.
export function declareShadowing(scope: Scope, binding: Binding): bool {
  for index of 0..<scope.bindings.length {
    if scope.bindings[index].name == binding.name {
      if scope.bindings[index].kind != "field" && scope.bindings[index].kind != "method" { return false }
      scope.bindings[index] = binding
      return true
    }
  }
  scope.bindings.push(binding)
  return true
}

export function hasTypeParam(scope: Scope, name: string): bool {
  let current: Scope | none = scope
  while current != none {
    for typeParam of current!.typeParams { if typeParam == name { return true } }
    current = current!.parent
  }
  return false
}

export function typeParamConstraintName(scope: Scope, name: string): string {
  let current: Scope | none = scope
  while current != none {
    for index of 0..<current!.typeParams.length {
      if current!.typeParams[index] == name && index < current!.typeParamConstraintNames.length {
        return current!.typeParamConstraintNames[index]
      }
    }
    current = current!.parent
  }
  return ""
}

export function typeParamConstraint(scope: Scope, name: string): ResolvedType | none {
  let current: Scope | none = scope
  while current != none {
    for index of 0..<current!.typeParams.length {
      if current!.typeParams[index] == name && index < current!.typeParamConstraints.length {
        return current!.typeParamConstraints[index].type_
      }
    }
    current = current!.parent
  }
  return none
}

export function lookup(scope: Scope, name: string): Binding | none {
  let current: Scope | none = scope
  while current != none {
    for binding of current!.bindings { if binding.name == name { return binding } }
    current = current!.parent
  }
  return none
}

export function returnScope(scope: Scope): Scope | none {
  let current: Scope | none = scope
  while current != none {
    if current!.returnType != none { return current }
    current = current!.parent
  }
  return none
}

export function valueYieldScope(scope: Scope): Scope | none {
  let current: Scope | none = scope
  while current != none {
    if current!.inValueYieldBlock { return current }
    current = current!.parent
  }
  return none
}

export function currentThisType(scope: Scope): ResolvedType {
  let current: Scope | none = scope
  while current != none {
    if current!.thisType != none { return current!.thisType! }
    current = current!.parent
  }
  return unknownType()
}

export function iterableElement(iterable: ResolvedType): ResolvedType {
  case iterable {
    array: ArrayResolvedType -> { return array.elementType }
    map: MapResolvedType -> { return tupleType([map.keyType, map.valueType]) }
    set: SetResolvedType -> { return set.elementType }
    stream: StreamResolvedType -> { return stream.elementType }
    _: RangeResolvedType -> { return primitive("int") }
    _ -> { return unknownType() }
  }
  return unknownType()
}

export function isBuiltinCallable(name: string): bool {
  return name == "byte" || name == "string" || name == "int" || name == "long" || name == "float" || name == "double" || name == "bool" || name == "println" || name == "panic" || name == "assert" || name == "catchPanic" || name == "Success" || name == "Failure"
}

export function builtinCallable(name: string): ResolvedType {
  if name == "println" { return functionType([FunctionParamType { name: "value", type_: jsonValueType(), hasDefault: false }], noneType()) }
  if name == "panic" { return functionType([FunctionParamType { name: "message", type_: primitive("string"), hasDefault: false }], neverType()) }
  if name == "assert" {
    return functionType([
      FunctionParamType { name: "condition", type_: primitive("bool"), hasDefault: false },
      FunctionParamType { name: "message", type_: primitive("string"), hasDefault: false },
    ], noneType())
  }
  if name == "catchPanic" {
    successType := typeParameter("T")
    callbackType := functionType([], successType)
    return functionType([
      FunctionParamType { name: "f", type_: callbackType, hasDefault: false },
    ], resultType(successType, primitive("string")), ["T"])
  }
  if name == "string" {
    return functionType([FunctionParamType {
      name: "value",
      type_: unionType([
        primitive("byte"), primitive("int"), primitive("long"), primitive("float"),
        primitive("double"), primitive("string"), primitive("char"), primitive("bool"),
      ]),
      hasDefault: false,
    }], primitive("string"))
  }
  if name == "bool" {
    return functionType([FunctionParamType { name: "value", type_: primitive("bool"), hasDefault: false }], primitive("bool"))
  }
  result := primitive(name)
  let castInputs: ResolvedType[] = [
    primitive("byte"), primitive("int"), primitive("long"), primitive("float"), primitive("double"),
  ]
  if name == "int" { castInputs.push(primitive("char")) }
  return functionType([FunctionParamType { name: "value", type_: unionType(castInputs), hasDefault: false }], result)
}

export function isBuiltinPrintlnCall(callee: Expression): bool {
  case callee {
    identifier: Identifier -> {
      return identifier.name == "println" && identifier.resolvedBinding != none && identifier.resolvedBinding!.kind == "builtin"
    }
    _ -> { return false }
  }
}

export function symbolFor(info: ModuleInfo, name: string): Symbol | none {
  for symbol of info.symbols { if symbol.name == name { return symbol } }
  for imported of info.imports { if imported.localName == name { return imported.symbol } }
  return none
}

export function valueSymbolFor(info: ModuleInfo, name: string): Symbol | none {
  for symbol of info.symbols { if symbol.name == name && isValueSymbol(symbol) { return symbol } }
  for imported of info.imports {
    if imported.localName == name && !imported.typeOnly && imported.symbol != none && isValueSymbol(imported.symbol!) { return imported.symbol }
  }
  return none
}

export function valueUseDiagnostic(info: ModuleInfo, name: string): string {
  for imported of info.imports {
    if imported.localName != name { continue }
    if imported.typeOnly { return "Type-only import '" + name + "' cannot be used as a value" }
    if imported.symbol != none && !isValueSymbol(imported.symbol!) { return "Type '" + name + "' cannot be used as a value" }
  }
  for symbol of info.symbols { if symbol.name == name && !isValueSymbol(symbol) { return "Type '" + name + "' cannot be used as a value" } }
  return ""
}

export function isValueSymbol(symbol: Symbol): bool {
  return symbol.kind != "type-alias"
}

export function declaredSymbolName(symbol: Symbol): string {
  return if symbol.originalName == "" then symbol.name else symbol.originalName
}

export function declarationFor(result: AnalysisResult, symbol: Symbol): Statement | none {
  module := findModule(result, symbol.module)
  if module == none { return none }
  declarationName := declaredSymbolName(symbol)
  for statement of module!.program.statements {
    if statement.kind == "export-list" { continue }
    candidate := symbolName(statement)
    if candidate == declarationName { return statement }
  }
  return none
}

export function symbolName(statement: Statement): string {
  case statement {
    class_: ClassDeclaration -> { return class_.name }
    fn: FunctionDeclaration -> { return fn.name }
    interface_: InterfaceDeclaration -> { return interface_.name }
    enum_: EnumDeclaration -> { return enum_.name }
    alias: TypeAliasDeclaration -> { return alias.name }
    const_: ConstDeclaration -> { return const_.name }
    readonly_: ReadonlyDeclaration -> { return readonly_.name }
    binding: ImmutableBinding -> { return binding.name }
    let_: LetDeclaration -> { return let_.name }
    _ -> { return "" }
  }
  return ""
}

// Infer one generic argument by structurally matching a checked parameter
// pattern against the concrete argument type. Conflicting candidates are
// rejected by the caller before substitution.

export function resolveAnnotation(annotation: TypeAnnotation, info: ModuleInfo, result: AnalysisResult, typeParams: string[] = []): ResolvedType {
  return resolveProvisionalAnnotation(annotation, info, result, typeParams)
}
