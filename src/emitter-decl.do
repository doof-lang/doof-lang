// Function and top-level declaration rendering for the Doof emitter.
//
// Function signatures are shared by header planning and source rendering so
// the two halves cannot silently drift apart.

import {
  Block, ClassDeclaration, ClassField, ConstDeclaration, Expression, FunctionDeclaration, InterfaceDeclaration,
  ImmutableBinding, LetDeclaration, ReadonlyDeclaration,
} from "./ast"
import {
  ActorType, ArrayResolvedType, ClassType, FunctionType, PromiseType, ResolvedType, ResultResolvedType, SetResolvedType, Symbol, TupleResolvedType,
  UnionResolvedType, UnknownType, NoneType, WeakResolvedType,
} from "./semantic"
import { EmitContext, recordCoverageLine, sourceLineDirective } from "./emitter-context"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { emitBlock } from "./emitter-stmt"
import { borrowParameterType, emitClassInnerType, emitContextReturnType, emitContextType, emitParameterType, emitReturnType, specializeEmitType } from "./emitter-types"
import { scanCapturedMutablesInBlock, scanCapturedMutablesInExpression } from "./emitter-expr-lambda"
import { moduleNamespace } from "./emitter-names"
import { ClassInstantiation, MethodInstantiation } from "./emitter-monomorphize"
import { emitGeneratedJsonDeclarations } from "./emitter-json"
import { emitMetadataDeclaration } from "./emitter-metadata"

export function emitFunctionSignature(fn: FunctionDeclaration, name: string = "", modulePath: string = "", context: EmitContext | none = none, ownerTypeParams: string[] = []): string {
  let functionType = checkedFunctionType(fn)
  if context != none {
    case specializeEmitType(functionType, context!) {
      specialized: FunctionType -> { functionType = specialized }
      _ -> { }
    }
  }
  functionName := cppIdentifier(if name == "" then fn.name else name)
  let genericParams: string[] = []
  for typeParam of ownerTypeParams { genericParams.push(typeParam) }
  for typeParam of fn.typeParams { genericParams.push(typeParam) }
  returnType := if context == none then emitReturnType(functionType.returnType, modulePath) else emitContextReturnType(functionType.returnType, context!)
  ensureKnown(functionType.returnType, fn.name + " return type")
  let result = (if functionType.returnType.kind == "never" then "[[noreturn]] " else "") + returnType + " " + functionName + "("
  for i of 0..<fn.params.length {
    if i > 0 { result = result + ", " }
    parameterType := fn.params[i].resolvedType ?? functionType.params[i].type_
    parameterText := if context == none
      then emitParameterType(parameterType, modulePath)
      else borrowParameterType(parameterType, emitContextType(parameterType, context!))
    ensureKnown(parameterType, fn.name + " parameter " + fn.params[i].name)
    result = result + parameterText + " " + cppIdentifier(fn.params[i].name)
  }
  return result + ")"
}

export function emitFunctionDefinition(fn: FunctionDeclaration, context: EmitContext, name: string = ""): string {
  if fn.bodyless { return "" }
  if fn.typeParams.length > 0 && context.substitution == none {
    panic("Generic function " + fn.name + " reached emission without a concrete instantiation")
  }
  previousReturnErrorType := context.currentReturnErrorType
  previousFunctionName := context.currentFunctionName
  previousCapturedMutables := context.capturedMutables
  context.currentFunctionName = fn.name
  context.capturedMutables = []
  case fn.body {
    expression: Expression -> { context.capturedMutables = scanCapturedMutablesInExpression(expression) }
    block: Block -> { context.capturedMutables = scanCapturedMutablesInBlock(block) }
  }
  case fn.resolvedType! {
    function_: FunctionType -> {
      case function_.returnType {
        result: ResultResolvedType -> { context.currentReturnErrorType = emitContextType(result.errorType, context) }
        _ -> { context.currentReturnErrorType = "" }
      }
    }
    _ -> { context.currentReturnErrorType = "" }
  }
  let result = sourceLineDirective(fn.span, context) + emitCallableDescription(fn, "") + emitFunctionSignature(fn, name, context.modulePath, context) + " {\n"
  case fn.body {
    expression: Expression -> {
      result = result + emitExpressionCoverageMark(expression, context)
      returnType := functionReturnType(fn)
      if returnType != none && returnType!.kind == "none" { result = result + "    " + emitExpression(expression, context, returnType) + ";\n" }
      else if returnType != none && returnType!.kind == "never" { result = result + "    " + emitExpression(expression, context, returnType) + ";\n    doof::panic(\"never function returned\");\n" }
      else { result = result + "    return " + emitExpression(expression, context, returnType) + ";\n" }
    }
    block: Block -> {
      result = result + emitBlock(block, 1, context)
      returnType := functionReturnType(fn)
      if returnType != none && returnType!.kind == "never" { result = result + "    doof::panic(\"never function returned\");\n" }
    }
  }
  context.currentReturnErrorType = previousReturnErrorType
  context.currentFunctionName = previousFunctionName
  context.capturedMutables = previousCapturedMutables
  return result + "}\n"
}

export function emitFunctionDeclaration(fn: FunctionDeclaration, name: string = "", modulePath: string = "", context: EmitContext | none = none): string {
  if fn.typeParams.length > 0 && (context == none || context!.substitution == none) {
    panic("Generic function " + fn.name + " reached declaration emission without a concrete instantiation")
  }
  return emitCallableDescription(fn, "") + emitFunctionSignature(fn, name, modulePath, context) + ";\n"
}

// A generic native import is a Doof generic declaration, not a promise that
// the mapped C++ target is a template. Each concrete Doof instantiation calls
// the native overload set with concrete arguments and lets C++ perform normal
// overload resolution or template deduction.
export function emitNativeFunctionAdapterDefinition(fn: FunctionDeclaration, emittedName: string, context: EmitContext): string {
  signature := emitFunctionSignature(fn, emittedName, context.modulePath, context)
  nativeName := if fn.nativeCppName == "" then fn.name else fn.nativeCppName
  let call = "::" + nativeName + "("
  for i of 0..<fn.params.length {
    if i > 0 { call = call + ", " }
    call = call + cppIdentifier(fn.params[i].name)
  }
  call = call + ")"
  returnType := specializeEmitType(checkedFunctionType(fn).returnType, context)
  if returnType.kind == "none" { return signature + " {\n    " + call + ";\n}\n" }
  if returnType.kind == "never" { return signature + " {\n    " + call + ";\n    doof::panic(\"native never function returned\");\n}\n" }
  return signature + " {\n    return " + call + ";\n}\n"
}

/** Emits default-initialized direct storage for a module binding. */
export function emitModuleValueStorage(
  statement: ConstDeclaration | ReadonlyDeclaration | ImmutableBinding | LetDeclaration,
  context: EmitContext,
  initializer: string = "",
): string {
  let name = ""
  let type_: ResolvedType | none = none
  case statement {
    value: ConstDeclaration -> { name = value.name; type_ = value.resolvedType }
    value: ReadonlyDeclaration -> { name = value.name; type_ = value.resolvedType }
    value: ImmutableBinding -> { name = value.name; type_ = value.resolvedType }
    value: LetDeclaration -> { name = value.name; type_ = value.resolvedType }
  }
  if name == "" || name == "_" || type_ == none { return "" }
  return emitContextType(type_!, context) + " " + cppIdentifier(name) +
    (if initializer == "" then "" else " = " + initializer) + ";\n"
}

function checkedFunctionType(fn: FunctionDeclaration): FunctionType {
  case fn.resolvedType! {
    resolved: FunctionType -> { return resolved }
    _ -> { panic("Function " + fn.name + " was not checked before emission") }
  }
  return FunctionType { params: [], returnType: NoneType {} }
}

function functionReturnType(fn: FunctionDeclaration): ResolvedType | none {
  case fn.resolvedType! {
    function_: FunctionType -> { return function_.returnType }
    _ -> { return none }
  }
  return none
}

function ensureKnown(resolvedType: ResolvedType, owner: string): none {
  case resolvedType {
    _: UnknownType -> { panic("Cannot emit unresolved type for " + owner) }
    array: ArrayResolvedType -> { ensureKnown(array.elementType, owner + " element") }
    set_: SetResolvedType -> { ensureKnown(set_.elementType, owner + " element") }
    tuple: TupleResolvedType -> {
      for i of 0..<tuple.elements.length { ensureKnown(tuple.elements[i], owner + " tuple element") }
    }
    union_: UnionResolvedType -> {
      for member of union_.types { ensureKnown(member, owner + " union member") }
    }
    function_: FunctionType -> {
      for parameter of function_.params { ensureKnown(parameter.type_, owner + " callback parameter") }
      ensureKnown(function_.returnType, owner + " callback return")
    }
    actor: ActorType -> { ensureKnown(actor.innerClass, owner + " actor state") }
    promise: PromiseType -> { ensureKnown(promise.valueType, owner + " promise value") }
    weak_: WeakResolvedType -> { ensureKnown(weak_.inner, owner + " weak target") }
    _ -> { }
  }
}

export function emitClassDeclaration(decl: ClassDeclaration, context: EmitContext, emittedName: string = "", concreteMethods: MethodInstantiation[] = []): string {
  if decl.native_ { return "" }
  if decl.typeParams.length > 0 && context.substitution == none {
    panic("Generic class " + decl.name + " reached emission without a concrete instantiation")
  }
  className := if emittedName == "" then decl.name else emittedName
  let inheritance = if decl.struct_ then "" else " : public std::enable_shared_from_this<" + className + ">"
  let result = emitDescriptionComment(decl.description, "") + "struct " + className + inheritance + " {\n"
  for field of decl.fields {
    for index of 0..<field.names.length {
      name := field.names[index]
      description := if index < field.descriptions.length then field.descriptions[index] else ""
      effectiveType := fieldTypeForEmission(field)
      fieldType := fieldTypeTextForEmission(field, effectiveType, context)
      ensureKnown(effectiveType, decl.name + "." + name)
      result = result + emitDescriptionComment(description, "    ")
      // Doof enforces literal-valued fields semantically. Struct backing fields
      // remain assignable so ordered module initialization can assign a fully
      // constructed struct into its default-created static storage.
      result = result + "    " + (if field.static_ then "static " else if field.const_ && !decl.struct_ then "const " else "") + fieldType + " " + cppIdentifier(name)
      if field.defaultValue != none && !field.static_ && field.const_ {
        defaultText := emitExpression(field.defaultValue!, context, effectiveType)
        result = result + " = " + defaultText
      }
      result = result + ";\n"
    }
  }
  if hasInstanceFields(decl) {
    // Doof call sites materialize every omitted field. The synthesized C++
    // constructor therefore has an explicit parameter for every stored field.
    result = result + "    " + className + "("
    let firstParameter = true
    for field of decl.fields {
      if field.static_ || field.const_ { continue }
      for name of field.names {
        if !firstParameter { result = result + ", " }
        firstParameter = false
        effectiveType := fieldTypeForEmission(field)
        fieldType := fieldTypeTextForEmission(field, effectiveType, context)
        result = result + fieldType + " " + cppIdentifier(name)
      }
    }
    result = result + ") : "
    let firstInitializer = true
    for field of decl.fields {
      if field.static_ || field.const_ { continue }
      for name of field.names {
        if !firstInitializer { result = result + ", " }
        firstInitializer = false
        result = result + cppIdentifier(name) + "(" + cppIdentifier(name) + ")"
      }
    }
    result = result + " {}\n"
    if decl.struct_ {
      result = result + "    " + className + "() {}\n"
    }
  } else if !decl.struct_ {
    result = result + "    " + className + "() {}\n"
  }
  for method of decl.methods {
    if method.typeParams.length > 0 {
      for instantiation of concreteMethods {
        if instantiation.declaration.name != method.name { continue }
        previousSubstitution := context.substitution
        context.substitution = instantiation.substitution
        staticPrefix := if method.static_ then "static " else ""
        result = result + emitCallableDescription(method, "    ") + "    " + staticPrefix + emitFunctionSignature(method, instantiation.emittedName, context.modulePath, context, decl.typeParams) + ";\n"
        context.substitution = previousSubstitution
      }
    } else {
      staticPrefix := if method.static_ then "static " else ""
      result = result + emitCallableDescription(method, "    ") + "    " + staticPrefix + emitFunctionSignature(method, "", context.modulePath, context, decl.typeParams) + ";\n"
    }
  }
  if decl.destructor_ != none {
    result = result + "    ~" + className + "();\n"
  }
  if decl.struct_ {
    // Keep field comparisons dependent until equality is used: merely
    // declaring a struct with a non-comparable native field must remain valid.
    result = result + "    template <typename _DoofOther = " + className + ">\n    bool operator==(const _DoofOther& _doof_other) const { return "
    let comparison = ""
    for field of decl.fields {
      if field.static_ { continue }
      for name of field.names {
        if comparison != "" { comparison = comparison + " && " }
        member := cppIdentifier(name)
        comparison = comparison + "(this->" + member + " == _doof_other." + member + ")"
      }
    }
    result = result + (if comparison == "" then "true" else comparison) + "; }\n"
    result = result + "    template <typename _DoofOther = " + className + ">\n    bool operator!=(const _DoofOther& _doof_other) const { return !(*this == _doof_other); }\n"
  }
  result = result + emitGeneratedJsonDeclarations(decl, context)
  result = result + emitMetadataDeclaration(decl)
  return result + "};\n"
}

function fieldTypeForEmission(field: ClassField): ResolvedType {
  if field.resolvedType == none { panic("Class field was not resolved before emission") }
  return field.resolvedType!
}

function fieldTypeTextForEmission(field: ClassField, resolvedType: ResolvedType, context: EmitContext): string {
  if field.weak_ {
    specialized := specializeEmitType(resolvedType, context)
    case specialized {
      weak_: WeakResolvedType -> { return emitContextType(weak_, context) }
      class_: ClassType -> { return "std::weak_ptr<" + emitClassInnerType(class_, context.modulePath) + ">" }
      _ -> { return "std::weak_ptr<" + emitContextType(specialized, context) + ">" }
    }
  }
  typeText := emitContextType(resolvedType, context)
  if field.defaultValue == none { return typeText }
  defaultText := emitExpression(field.defaultValue!, context, resolvedType)
  if defaultText == "std::monostate{}" && typeText.startsWith("std::variant<") && !typeText.startsWith("std::variant<std::monostate") {
    return "std::variant<std::monostate, " + typeText.substring(13, 1000000)
  }
  return typeText
}

function hasInstanceFields(decl: ClassDeclaration): bool {
  for field of decl.fields { if !field.static_ && !field.const_ { return true } }
  return false
}

export function emitStaticClassFieldDefinitions(owner: ClassDeclaration, context: EmitContext, emittedOwnerName: string = ""): string {
  if owner.native_ || (owner.typeParams.length > 0 && context.substitution == none) { return "" }
  ownerName := if emittedOwnerName == "" then owner.name else emittedOwnerName
  let result = ""
  for field of owner.fields {
    if !field.static_ || field.defaultValue == none { continue }
    for name of field.names {
      resolvedType := fieldTypeForEmission(field)
      result = result + fieldTypeTextForEmission(field, resolvedType, context) + " " + ownerName + "::" + cppIdentifier(name) + ";\n"
    }
  }
  return result
}

/** Renders declaration descriptions as stable C++ line comments. */
export function emitDescriptionComment(description: string, indent: string): string {
  if description == "" { return "" }
  return indent + "// " + description.replaceAll("\n", "\n" + indent + "// ") + "\n"
}

function emitCallableDescription(fn: FunctionDeclaration, indent: string): string {
  let result = emitDescriptionComment(fn.description, indent)
  for parameter of fn.params {
    if parameter.description != "" {
      result = result + indent + "// @param " + parameter.name + " " + parameter.description.replaceAll("\n", " ") + "\n"
    }
  }
  return result
}

export function emitInterfaceAlias(decl: InterfaceDeclaration, context: EmitContext, classes: ClassInstantiation[] = []): string {
  if decl.resolvedSymbol == none { panic("Interface " + decl.name + " was not analyzed") }
  implementations := decl.resolvedSymbol!.implementations
  if implementations.length == 0 { panic("Interface " + decl.name + " has no implementing classes") }
  let result = emitDescriptionComment(decl.description, "") + "using " + decl.name + " = std::variant<"
  let first = true
  for symbol of implementations {
    if symbol.typeParams.length > 0 && !symbol.native_ {
      for instantiation of classes {
        if instantiation.modulePath != symbol.module || instantiation.declaration.name != symbol.name { continue }
        if !first { result = result + ", " }
        first = false
        concreteName := if symbol.module == context.modulePath
          then instantiation.emittedName
          else "::" + moduleNamespace(symbol.module) + "::" + instantiation.emittedName
        result = result + "std::shared_ptr<" + concreteName + ">"
      }
    } else {
      if !first { result = result + ", " }
      first = false
      className := if symbol.native_ then "::" + (if symbol.nativeCppName == "" then symbol.name else symbol.nativeCppName) else ownedClassName(symbol, context.modulePath)
      result = result + "std::shared_ptr<" + className + ">"
    }
  }
  if first { result = result + "std::monostate" }
  return result + ">;\n"
}

function ownedClassName(symbol: Symbol, currentModulePath: string): string {
  if symbol.module == currentModulePath || currentModulePath == "" { return if symbol.originalName == "" then symbol.name else symbol.originalName }
  return "::" + moduleNamespace(symbol.module) + "::" + (if symbol.originalName == "" then symbol.name else symbol.originalName)
}

export function emitClassMethodDefinition(owner: ClassDeclaration, method: FunctionDeclaration, context: EmitContext, emittedOwnerName: string = "", emittedMethodName: string = ""): string {
  if method.bodyless || (method.typeParams.length > 0 && context.substitution == none) { return "" }
  previous := context.currentClass
  previousNative := context.currentClassNative
  previousStruct := context.currentClassStruct
  previousReturnErrorType := context.currentReturnErrorType
  previousFunctionName := context.currentFunctionName
  previousFunctionStatic := context.currentFunctionStatic
  previousCapturedMutables := context.capturedMutables
  context.currentClass = owner.name
  context.currentClassNative = owner.native_
  context.currentClassStruct = owner.struct_
  context.currentFunctionName = method.name
  context.currentFunctionStatic = method.static_
  context.capturedMutables = []
  case method.body {
    expression: Expression -> { context.capturedMutables = scanCapturedMutablesInExpression(expression) }
    block: Block -> { context.capturedMutables = scanCapturedMutablesInBlock(block) }
  }
  case method.resolvedType! {
    function_: FunctionType -> {
      case function_.returnType {
        result: ResultResolvedType -> { context.currentReturnErrorType = emitContextType(result.errorType, context) }
        _ -> { context.currentReturnErrorType = "" }
      }
    }
    _ -> { context.currentReturnErrorType = "" }
  }
  ownerName := if emittedOwnerName != "" then emittedOwnerName else if owner.native_ then (if owner.nativeCppName == "" then owner.name else owner.nativeCppName) else owner.name
  methodName := if emittedMethodName == "" then cppIdentifier(method.name) else emittedMethodName
  let result = sourceLineDirective(method.span, context) + emitFunctionSignature(method, ownerName + "::" + methodName, context.modulePath, context) + " {\n"
  case method.body {
    expression: Expression -> {
      result = result + emitExpressionCoverageMark(expression, context)
      result = result + "    return " + emitExpression(expression, context, functionReturnType(method)) + ";\n"
    }
    block: Block -> { result = result + emitBlock(block, 1, context) }
  }
  context.currentClass = previous
  context.currentClassNative = previousNative
  context.currentClassStruct = previousStruct
  context.currentReturnErrorType = previousReturnErrorType
  context.currentFunctionName = previousFunctionName
  context.currentFunctionStatic = previousFunctionStatic
  context.capturedMutables = previousCapturedMutables
  return result + "}\n"
}

export function emitClassDestructorDefinition(owner: ClassDeclaration, context: EmitContext, emittedOwnerName: string = ""): string {
  if owner.destructor_ == none || owner.native_ { return "" }
  ownerName := if emittedOwnerName == "" then owner.name else emittedOwnerName
  previous := context.currentClass
  previousNative := context.currentClassNative
  previousStruct := context.currentClassStruct
  context.currentClass = owner.name
  context.currentClassNative = false
  context.currentClassStruct = owner.struct_
  result := ownerName + "::~" + ownerName + "() {\n" + emitBlock(owner.destructor_!, 1, context) + "}\n"
  context.currentClass = previous
  context.currentClassNative = previousNative
  context.currentClassStruct = previousStruct
  return result
}

function emitExpressionCoverageMark(expression: Expression, context: EmitContext): string {
  if !context.coverageEnabled || context.coverageModuleId < 0 { return "" }
  line := expression.span.start.line
  recordCoverageLine(context, line)
  return "    doof::coverage::cov_mark(" + string(context.coverageModuleId) + ", " + string(line) + ");\n"
}
