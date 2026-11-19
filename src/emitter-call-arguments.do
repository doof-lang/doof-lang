// Shared ordinary and visitor-dispatched call argument lowering.
// Target selection and generic signature specialization belong to the caller.
import { CallArgument, CallExpression, Expression, Identifier, MemberExpression, SourceSpan } from "./ast"
import { ClassType, InterfaceType, FunctionType, ResolvedType, TypeSubstitution } from "./semantic"
import { EmitContext, SourceLocationSpanOverride } from "./emitter-context"
import { emitExpression } from "./emitter-expr"
import { optionalExpectedType } from "./emitter-expr-utils"
import { specializeEmitType } from "./emitter-types"

export function callArgumentNamed(args: CallArgument[], name: string): CallArgument | none {
  for argument of args { if argument.name == name { return argument } }
  return none
}

export function hasNamedArguments(args: CallArgument[]): bool {
  for argument of args { if argument.name != none { return true } }
  return false
}

export function emitDispatchCallArguments(expression: CallExpression, context: EmitContext): string {
  let signature: FunctionType | none = none
  if resolvedType := expression.callee.resolvedType {
    case specializeEmitType(resolvedType, context) {
      fn: FunctionType -> { signature = fn }
      _ -> { }
    }
  }
  return emitCallArguments(expression, context, signature)
}

export function emitCallArguments(expression: CallExpression, context: EmitContext, signature: FunctionType | none): string {
  let result = ""
  named := hasNamedArguments(expression.args)
  declaration := expression.resolvedFunction
  let count = expression.args.length
  if function_ := declaration { count = function_.params.length }
  else if named && signature != none { count = signature!.params.length }
  for i of 0..<count {
    let name = ""
    let expected: ResolvedType | none = none
    let defaultValue: Expression | none = none
    if function_ := declaration && i < function_.params.length {
      parameter := function_.params[i]
      name = parameter.name
      expected = parameter.resolvedType
      defaultValue = parameter.defaultValue
    }
    if signatureType := signature && i < signatureType.params.length {
      parameter := signatureType.params[i]
      if declaration == none { name = parameter.name }
      expected = optionalExpectedType(parameter.type_)
    }
    if builtinUsesArgumentType(expression) { expected = none }
    argument := if named then callArgumentNamed(expression.args, name) else if i < expression.args.length then expression.args[i] else none
    if argument != none || defaultValue != none {
      if result != "" { result = result + ", " }
      if present := argument { result = result + emitExpression(present.value, context, expected) }
      else { result = result + emitCallDefault(expression, defaultValue!, expected, context) }
    }
  }
  return result
}

// Default ASTs belong to the generic declaration. Specialize their internals,
// not just the expected argument type, before lowering literals and nested calls.
function emitCallDefault(call: CallExpression, value: Expression, expected: ResolvedType | none, context: EmitContext): string {
  previous := context.substitution
  let names: string[] = []
  let arguments: ResolvedType[] = []
  if substitution := previous {
    for i of 0..<substitution.names.length {
      names.push(substitution.names[i])
      arguments.push(substitution.arguments[i])
    }
  }
  // Member checking retained the effective owner, including weak receivers and
  // interface contracts. Defaults belong to that owner's declaration scope.
  if member := call.callee as MemberExpression {
    if resolvedMember := member.resolvedMember && resolvedMember.owner != none {
      owner := specializeEmitType(resolvedMember.owner!, context)
      let ownerNames: string[] = []
      let ownerArguments: ResolvedType[] = []
      case owner {
        class_: ClassType -> { ownerNames = class_.symbol.typeParams; ownerArguments = class_.typeArgs }
        interface_: InterfaceType -> { ownerNames = interface_.symbol.typeParams; ownerArguments = interface_.typeArgs }
        _ -> { }
      }
      for i of 0..<ownerNames.length {
        if i < ownerArguments.length { addDefaultSubstitution(names, arguments, ownerNames[i], ownerArguments[i]) }
      }
    }
  }
  if declaration := call.resolvedFunction {
    for i of 0..<declaration.typeParams.length {
      if i < call.resolvedGenericTypeArgs.length {
        addDefaultSubstitution(names, arguments, declaration.typeParams[i], specializeEmitType(call.resolvedGenericTypeArgs[i], context))
      }
    }
  }
  if names.length > 0 { context.substitution = TypeSubstitution { names, arguments } }
  result := emitDefaultExpression(value, context, expected, call.span)
  context.substitution = previous
  return result
}

function addDefaultSubstitution(names: string[], arguments: ResolvedType[], name: string, type_: ResolvedType): none {
  for i of 0..<names.length {
    if names[i] == name { arguments[i] = type_; return }
  }
  names.push(name)
  arguments.push(type_)
}

function builtinUsesArgumentType(expression: CallExpression): bool {
  case expression.callee {
    identifier: Identifier -> {
      if identifier.resolvedBinding == none || identifier.resolvedBinding!.kind != "builtin" { return false }
      name := identifier.name
      return name == "println" || name == "string" || name == "byte" || name == "int" || name == "long" || name == "float" || name == "double" || name == "char" || name == "bool"
    }
    _ -> { return false }
  }
}

export function emitDefaultExpression(expression: Expression, context: EmitContext, expected: ResolvedType | none, callSiteSpan: SourceSpan): string {
  previous := context.sourceLocationSpanOverride
  context.sourceLocationSpanOverride = SourceLocationSpanOverride { span: callSiteSpan }
  result := emitExpression(expression, context, expected)
  context.sourceLocationSpanOverride = previous
  return result
}
