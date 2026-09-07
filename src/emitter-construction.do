// Class construction across call, named, and contextual object syntax.
// Checked owner/constructor decorations select the target; shared value lowering
// owns stored-field order, defaults, specialization, and factory arguments.
import { ActorCreationExpression, CheckedConstruction, CallArgument, CallExpression, ConstructExpression, Expression, ObjectLiteral, ObjectProperty, SourceSpan, ThisExpression } from "./ast"
import { ClassType, InterfaceType, ResolvedType, ResultResolvedType, TypeSubstitution } from "./semantic"
import { EmitContext } from "./emitter-context"
import { cppIdentifier, emitExpression } from "./emitter-expr"
import { emitPropertyValue, emittedSymbolName, exprModuleNamespaceFor, findProperty } from "./emitter-expr-utils"
import { emitContextReturnType, specializeEmitType } from "./emitter-types"
import { classInstantiationKey } from "./emitter-monomorphize"

import { callArgumentNamed, emitDefaultExpression, hasNamedArguments } from "./emitter-call-arguments"

class ConstructionInputs {
  args: CallArgument[] = []
  properties: ObjectProperty[] = []
  named: bool
  span: SourceSpan
  construct: ConstructExpression | none = none
  spreadName: string = ""
  // Explicit named construction retains its existing raw-this field bridge.
  // Positional arguments and contextual properties use ordinary expression lowering.
  aliasThis: bool = false
}

function emitConstructionValues(plan: CheckedConstruction, inputs: ConstructionInputs, context: EmitContext): string {
  let values = ""
  for index of 0..<plan.signature.params.length {
    parameter := plan.signature.params[index]
    if index > 0 { values = values + ", " }
    expected := specializeEmitType(parameter.type_, context)
    values = values + emitConstructionValue(inputs, parameter.name, index, expected, plan.defaults[index].value,
      plan.owner, plan.owner.symbol.typeParams, "Construction of '" + plan.owner.name + "' is missing required field '" + parameter.name + "'", context)
  }
  return values
}

function emitConstructionValue(inputs: ConstructionInputs, name: string, index: int, expected: ResolvedType, defaultValue: Expression | none, owner: ClassType, ownerTypeParams: string[], missingMessage: string, context: EmitContext): string {
  property := findProperty(inputs.properties, name)
  if property != none {
    if inputs.aliasThis && property!.value != none {
      case property!.value! {
        _: ThisExpression -> {
          case expected {
            class_: ClassType -> { return "std::shared_ptr<" + class_.name + ">(this, [](" + class_.name + "*) {})" }
            _ -> { }
          }
        }
        _ -> { }
      }
    }
    return emitPropertyValue(property!, context, expected)
  }
  argument := if inputs.named then callArgumentNamed(inputs.args, name) else if index < inputs.args.length then inputs.args[index] else none
  if argument != none { return emitExpression(argument!.value, context, expected) }
  if inputs.construct != none && hasSpreadField(inputs.construct!, name) {
    return emitConstructionSpreadField(inputs.construct!, inputs.spreadName, name, context)
  }
  if defaultValue != none { return emitOwnerDefaultExpression(defaultValue!, context, expected, inputs.span, owner, ownerTypeParams) }
  panic(missingMessage)
}

export function emitClassCall(expression: CallExpression, context: EmitContext): string | none {
  if expression.resolvedConstruction == none { return none }
  plan := expression.resolvedConstruction!
  if plan.factory != expression.resolvedConstructor { panic("Construction has no resolved constructor consistent with its checked plan") }
  inputs := ConstructionInputs { args: expression.args, named: hasNamedArguments(expression.args), span: expression.span }
  return emitPlannedConstruction(plan, inputs, context)
}

function emitPlannedConstruction(plan: CheckedConstruction, inputs: ConstructionInputs, context: EmitContext): string {
  values := emitConstructionValues(plan, inputs, context)
  name := constructionClassName(plan.owner, context)
  if plan.factory != none { return name + "::constructor(" + values + ")" }
  return emitClassAllocation(name, plan.owner.symbol.kind == "struct", values)
}

export function emitActorConstruction(expression: ActorCreationExpression, context: EmitContext): string {
  if expression.resolvedConstruction == none { panic("Actor construction has no checked plan") }
  plan := expression.resolvedConstruction!
  let args: CallArgument[] = []
  for value of expression.args { args.push(CallArgument { name: none, value, span: value.span }) }
  inputs := ConstructionInputs { args, named: false, span: expression.span }
  values := emitConstructionValues(plan, inputs, context)
  name := constructionClassName(plan.owner, context)
  value := if plan.factory != none then name + "::constructor(" + values + ")" else name + "{" + values + "}"
  return "std::make_shared<doof::Actor<" + name + ">>(" + value + ")"
}

export function emitConstruct(expression: ConstructExpression, context: EmitContext): string {
  if expression.type_ == "Success" || expression.type_ == "Failure" {
    resultType := expression.resolvedType
    if resultType == none { panic(expression.type_ + " has no resolved Result type") }
    case resultType! {
      result: ResultResolvedType -> {
        valueType := if expression.type_ == "Success" then result.valueType else result.errorType
        propertyName := if expression.type_ == "Success" then "value" else "error"
        property := findProperty(expression.args, propertyName)
        payloadType := emitContextReturnType(valueType, context)
        if property == none { return "doof::" + expression.type_ + "<" + payloadType + ">{ }" }
        value := emitPropertyValue(property!, context, valueType)
        return "doof::" + expression.type_ + "<" + payloadType + ">{ " + value + " }"
      }
      _ -> { }
    }
    panic(expression.type_ + " does not construct a Result")
  }
  if expression.resolvedConstruction == none { panic("Construction of '" + expression.type_ + "' has no checked plan") }
  plan := expression.resolvedConstruction!
  if plan.factory != expression.resolvedConstructor { panic("Construction of '" + expression.type_ + "' has no resolved constructor consistent with its checked plan") }
  spreadName := constructionSpreadTemporary(expression, context)
  inputs := ConstructionInputs { properties: expression.args, named: true, span: expression.span, construct: expression, spreadName, aliasThis: plan.factory == none }
  result := emitPlannedConstruction(plan, inputs, context)
  return wrapConstructionSpread(expression, spreadName, result, context)
}

function constructionSpreadTemporary(expression: ConstructExpression, context: EmitContext): string {
  if expression.spread == none { return "" }
  context.tryCounter = context.tryCounter + 1
  return "_construct_spread_" + string(context.tryCounter)
}

function hasSpreadField(expression: ConstructExpression, name: string): bool {
  for field of expression.spreadFields { if field == name { return true } }
  return false
}

function emitConstructionSpreadField(expression: ConstructExpression, temporary: string, name: string, context: EmitContext): string {
  if expression.resolvedSpreadType == none { panic("Construction spread has no resolved type") }
  case expression.resolvedSpreadType! {
    class_: ClassType -> {
      accessor := if class_.symbol.kind == "struct" then "." else "->"
      return temporary + accessor + cppIdentifier(name)
    }
    _: InterfaceType -> { return "std::visit([](auto&& _obj) { return _obj->" + cppIdentifier(name) + "; }, " + temporary + ")" }
    _ -> { panic("Construction spread has unsupported resolved type") }
  }
}

function wrapConstructionSpread(expression: ConstructExpression, temporary: string, result: string, context: EmitContext): string {
  if expression.spread == none { return result }
  return "[&]() { const auto& " + temporary + " = " + emitExpression(expression.spread!, context, expression.resolvedSpreadType) + "; return " + result + "; }()"
}

function emitOwnerDefaultExpression(
  expression: Expression,
  context: EmitContext,
  expected: ResolvedType,
  callSiteSpan: SourceSpan,
  owner: ClassType,
  ownerTypeParams: string[] = [],
): string {
  specializedOwner := specializeEmitType(owner, context)
  let ownerArguments: ResolvedType[] = []
  case specializedOwner {
    class_: ClassType -> { ownerArguments = class_.typeArgs }
    _ -> { panic("Constructor owner did not remain a class after specialization") }
  }
  previousSubstitution := context.substitution
  names := if ownerTypeParams.length == 0 then owner.symbol.typeParams else ownerTypeParams
  context.substitution = TypeSubstitution { names, arguments: ownerArguments }
  result := emitDefaultExpression(expression, context, expected, callSiteSpan)
  context.substitution = previousSubstitution
  return result
}

export function emitClassObject(expression: ObjectLiteral, context: EmitContext, resolved: ClassType): string {
  if expression.resolvedConstruction == none { panic("Object literal has no checked construction plan") }
  inputs := ConstructionInputs { properties: expression.properties, named: true, span: expression.span }
  return emitPlannedConstruction(expression.resolvedConstruction!, inputs, context)
}

function concreteClassName(class_: ClassType, context: EmitContext): string {
  let typeArgs: ResolvedType[] = []
  for argument of class_.typeArgs { typeArgs.push(specializeEmitType(argument, context)) }
  if typeArgs.length == 0 { return "" }
  key := classInstantiationKey(class_.symbol.module, class_.name, typeArgs)
  for i of 0..<context.concreteClassKeys.length {
    if context.concreteClassKeys[i] == key {
      name := context.concreteClassNames[i]
      if class_.symbol.module != "" && class_.symbol.module != context.modulePath { return "::" + exprModuleNamespaceFor(class_.symbol.module, context.names) + "::" + name }
      return name
    }
  }
  return ""
}

function constructionClassName(owner: ClassType, context: EmitContext): string {
  concrete := concreteClassName(owner, context)
  if concrete != "" { return concrete }
  if owner.symbol.native_ { return "::" + (if owner.symbol.nativeCppName == "" then owner.symbol.name else owner.symbol.nativeCppName) }
  if owner.symbol.module != "" && owner.symbol.module != context.modulePath {
    return "::" + exprModuleNamespaceFor(owner.symbol.module, context.names) + "::" + emittedSymbolName(owner.symbol)
  }
  return emittedSymbolName(owner.symbol)
}

function emitClassAllocation(name: string, structValue: bool, values: string): string {
  return if structValue then name + "{" + values + "}" else "std::make_shared<" + name + ">(" + values + ")"
}
