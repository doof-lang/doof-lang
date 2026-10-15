// Lambda lowering and capture analysis for the Doof C++ emitter.
//
// Escaping closures must own mutable local state. Before a callable body is
// emitted, captured `let` bindings are identified so their declarations can be
// boxed in shared_ptr. Lambda capture lists then copy both ordinary immutable
// values and those boxes into the actor-affine doof::callback wrapper.

import { emitExpressionReturn } from "./emitter-expr-utils"
import { Block, ConstructExpression, Expression, Identifier, LambdaExpression, ObjectLiteral, ThisExpression } from "./ast"
import { Binding, ClassType, FunctionType, ResolvedType, ResultResolvedType, NoneType } from "./semantic"
import { EmitContext, isCapturedMutable } from "./emitter-context"
import { collectBlockExpressions, collectNestedExpressions } from "./ast-walk"
import { cppIdentifier } from "./emitter-expr"
import { emitBlock } from "./emitter-stmt"
import { emitContextReturnType, emitContextType, specializeEmitType } from "./emitter-types"

export function emitLambdaExpression(expression: LambdaExpression, context: EmitContext, expected: ResolvedType | none = none): string {
  let functionType = lambdaFunctionType(expression)
  if expected != none {
    case expected! {
      expectedFunction: FunctionType -> { functionType = expectedFunction }
      _ -> { }
    }
  }
  let params = ""
  for i of 0..<expression.params.length {
    if i > 0 { params = params + ", " }
    parameter := expression.params[i]
    if parameter.resolvedType == none { panic("Lambda parameter was not resolved before emission") }
    parameterName := if parameter.name == "_" then "_discard_parameter_" + string(i) else cppIdentifier(parameter.name)
    params = params + emitContextType(functionType.params[i].type_, context) + " " + parameterName
  }

  captureNames := lambdaCaptureNames(expression)
  structCaptures := lambdaStructCaptures(expression, context)
  let mutableClosure = false
  let captures = ""
  if captureNames.length > 0 {
    captures = ""
    for i of 0..<captureNames.length {
      if i > 0 { captures = captures + ", " }
      capture := captureNames[i]
      // A retained callback must keep its enclosing class alive. Capturing
      // C++ `this` alone leaves a dangling pointer after the last external
      // shared_ptr is released (notably when a Wasm export returns before a
      // host callback runs). Keep the ordinary `this` spelling for body
      // emission and pair it with an owning init-capture.
      if capture == "this" && context.currentClass != "" && !context.currentClassStruct {
        captures = captures + "this, _doof_captured_self = shared_from_this()"
      } else if structCaptures.contains(capture) {
        // Init-capture makes an owned value copy even when an enclosing
        // closure or binding exposes the source as const. Doof's checker
        // enforces binding/field immutability; C++ must permit struct methods.
        captures = captures + capture + " = " + capture
        mutableClosure = true
      } else {
        captures = captures + capture
      }
    }
  }

  previousReturnErrorType := context.currentReturnErrorType
  previousFunctionName := context.currentFunctionName
  previousTryPanics := context.tryPanics
  context.currentFunctionName = previousFunctionName + ".<lambda>"
  context.tryPanics = false
  case functionType.returnType {
    result: ResultResolvedType -> { context.currentReturnErrorType = emitContextType(result.errorType, context) }
    _ -> { context.currentReturnErrorType = "" }
  }

  returnType := emitContextReturnType(functionType.returnType, context)
  let lambda = "[" + captures + "](" + params + ")" + (if mutableClosure then " mutable" else "") + " -> " + returnType + " {"
  case expression.body {
    block: Block -> {
      lambda = lambda + "\n" + emitBlock(block, 1, context)
      if specializeEmitType(functionType.returnType, context).kind == "never" {
        lambda = lambda + "    doof::panic(\"never function returned\");\n"
      }
      lambda = lambda + "}"
    }
    body: Expression -> { lambda = lambda + " " + emitExpressionReturn(body, context, functionType.returnType) + " }" }
  }

  context.currentReturnErrorType = previousReturnErrorType
  context.currentFunctionName = previousFunctionName
  context.tryPanics = previousTryPanics
  return emitContextType(functionType, context) + "(" + lambda + ")"
}

function lambdaStructCaptures(expression: LambdaExpression, context: EmitContext): string[] {
  let result: string[] = []
  let expressions: Expression[] = [expression]
  let cursor = 0
  while cursor < expressions.length {
    current := expressions[cursor]
    cursor += 1
    case current {
      identifier: Identifier -> { addStructCapture(identifier.name, identifier.resolvedBinding, context, result) }
      object: ObjectLiteral -> {
        for property of object.properties {
          if property.value == none { addStructCapture(property.name, property.resolvedBinding, context, result) }
        }
      }
      construct: ConstructExpression -> {
        for property of construct.args {
          if property.value == none { addStructCapture(property.name, property.resolvedBinding, context, result) }
        }
      }
      _ -> { }
    }
    collectNestedExpressions(current, expressions)
  }
  return result
}

function addStructCapture(name: string, binding: Binding | none, context: EmitContext, result: string[]): none {
  if binding == none || isCapturedMutable(context, name) { return }
  case specializeEmitType(binding!.type_, context) {
    class_: ClassType -> { if class_.symbol.kind == "struct" { addUnique(result, cppIdentifier(name)) } }
    _ -> { }
  }
}

// Finds mutable bindings whose storage must outlive the current stack frame.
// Each lambda is evaluated against its own body span, so a mutable local used
// only by its containing lambda remains an ordinary local while one captured by
// a nested lambda is boxed.
export function scanCapturedMutablesInBlock(body: Block): string[] {
  let roots: Expression[] = []
  collectBlockExpressions(body, roots)
  let result: string[] = []
  scanExpressionsForLambdas(roots, result)
  return result
}

export function scanCapturedMutablesInExpression(body: Expression): string[] {
  let result: string[] = []
  scanExpressionsForLambdas([body], result)
  return result
}

function lambdaFunctionType(expression: LambdaExpression): FunctionType {
  if expression.resolvedType != none {
    case expression.resolvedType! {
      function_: FunctionType -> { return function_ }
      _ -> { }
    }
  }
  panic("Lambda has no resolved function type")
  return FunctionType { params: [], returnType: NoneType {} }
}

function lambdaCaptureNames(expression: LambdaExpression): string[] {
  let result: string[] = []
  collectLambdaCaptures(expression, result, false)
  let captures: string[] = []
  for name of result {
    let parameter = false
    for item of expression.params { if cppIdentifier(item.name) == name { parameter = true } }
    if !parameter { captures.push(name) }
  }
  return captures
}

// Every lambda reachable from these roots contributes the outer mutable
// bindings it reads, including lambdas nested inside other lambdas.
function scanExpressionsForLambdas(expressions: Expression[], result: string[]): none {
  let cursor = 0
  while cursor < expressions.length {
    current := expressions[cursor]
    cursor += 1
    case current {
      lambda: LambdaExpression -> { collectLambdaCaptures(lambda, result, true) }
      _ -> { }
    }
    collectNestedExpressions(current, expressions)
  }
}

// Bindings declared inside the lambda body are its own locals, not captures.
function collectLambdaCaptures(lambda: LambdaExpression, result: string[], mutableOnly: bool): none {
  let expressions: Expression[] = []
  let bodyStart = 0
  let bodyEnd = 0
  case lambda.body {
    block: Block -> {
      bodyStart = block.span.start.offset
      bodyEnd = block.span.end.offset
      collectBlockExpressions(block, expressions)
    }
    body: Expression -> {
      bodyStart = body.span.start.offset
      bodyEnd = body.span.end.offset
      expressions.push(body)
    }
  }
  let cursor = 0
  while cursor < expressions.length {
    current := expressions[cursor]
    cursor += 1
    case current {
      identifier: Identifier -> { collectIdentifierCapture(identifier, bodyStart, bodyEnd, result, mutableOnly) }
      _: ThisExpression -> { if !mutableOnly { addUnique(result, "this") } }
      object: ObjectLiteral -> {
        for property of object.properties {
          if property.key == none && property.value == none && property.resolvedBinding != none {
            collectBindingCapture(property.name, property.resolvedBinding!, bodyStart, bodyEnd, result, mutableOnly)
          }
        }
      }
      construct: ConstructExpression -> {
        for property of construct.args {
          if property.value == none && property.resolvedBinding != none {
            collectBindingCapture(property.name, property.resolvedBinding!, bodyStart, bodyEnd, result, mutableOnly)
          }
        }
      }
      _ -> { }
    }
    collectNestedExpressions(current, expressions)
  }
}

function collectIdentifierCapture(identifier: Identifier, bodyStart: int, bodyEnd: int, result: string[], mutableOnly: bool): none {
  if identifier.resolvedBinding == none { return }
  collectBindingCapture(identifier.name, identifier.resolvedBinding!, bodyStart, bodyEnd, result, mutableOnly)
}

function collectBindingCapture(name: string, binding: Binding, bodyStart: int, bodyEnd: int, result: string[], mutableOnly: bool): none {
  if binding.kind == "field" {
    if !mutableOnly { addUnique(result, "this") }
    return
  }
  if binding.kind == "method" {
    if !mutableOnly { addUnique(result, "this") }
    return
  }
  // Namespace-scope storage remains live without a C++ lambda capture. In
  // particular, module `let` bindings have no analyzer Symbol because they
  // are private, but they must not be boxed like automatic mutable locals.
  if binding.kind == "module-let" || binding.kind == "script-global" || binding.kind == "script-arguments" { return }
  if binding.symbol != none || binding.kind == "builtin" || binding.kind == "import" { return }
  bindingStart := binding.span.start.offset
  if bindingStart >= bodyStart && bindingStart <= bodyEnd { return }
  if mutableOnly && !binding.mutable { return }
  addUnique(result, cppIdentifier(name))
}

function addUnique(values: string[], value: string): none {
  for existing of values { if existing == value { return } }
  values.push(value)
}
