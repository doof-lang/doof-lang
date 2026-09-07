// Expression dispatcher for the Doof C++ emitter.
//
// Construct-specific lowering lives in focused modules.  This file owns the
// single decorated-AST dispatch point and the public identifier helper used
// by statement and declaration emission.

import { CarrierPosition } from "./emitter-carriers"
import { emitCarrierConversion } from "./emitter-carrier-values"
import { ActorCreationExpression, ArrayLiteral, AsExpression, AssignmentExpression, AsyncExpression, BinaryExpression, BoolLiteral, CallExpression, CallerExpression, CaseExpression, CatchExpression, CharLiteral, ConstructExpression, DoubleLiteral, DotShorthand, Expression, FloatLiteral, Identifier, IfExpression, IndexExpression, IntLiteral, LambdaExpression, LongLiteral, MemberExpression, NoneLiteral, ObjectLiteral, RetireExpression, StringLiteral, ThisExpression, TupleLiteral, UnaryExpression, YieldBlockExpression } from "./ast"
import { ClassType, JsonValueResolvedType, NoneType, PrimitiveType, ResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitAs, emitAssignment, emitBinary, emitIdentifier, emitIndex, emitMember, emitUnary, cppIdentifier as emitCppIdentifier } from "./emitter-expr-ops"
import { emitCall } from "./emitter-expr-calls"
import { emitConstruct } from "./emitter-construction"
import { emitArray, emitChar, emitNoneLiteral, emitObject, emitString, emitTuple } from "./emitter-expr-literals"
import { emitCaseExpression, emitCatchExpression, emitDotShorthand, emitIfExpression, emitYieldBlockExpression } from "./emitter-expr-control"
import { emitLambdaExpression } from "./emitter-expr-lambda"
import { decoratedExpressionType } from "./emitter-expr-utils"
import { specializeEmitType } from "./emitter-types"
import { emitActorCreation, emitAsyncExpression, emitRetireActor } from "./emitter-expr-actor"
import { moduleDiagnosticPath } from "./emitter-names"

export function emitExpression(expression: Expression, context: EmitContext, expected: ResolvedType | none = none): string {
  let value = ""
  let sourcePosition: CarrierPosition = .Value
  case expression {
    int_: IntLiteral -> { value = string(int_.value) }
    long_: LongLiteral -> { value = string(long_.value) + "LL" }
    float_: FloatLiteral -> { value = decimalLiteral(if float_.raw == "" then string(float_.value) else float_.raw) + "f" }
    double_: DoubleLiteral -> { value = decimalLiteral(if double_.raw == "" then string(double_.value) else double_.raw) }
    string_: StringLiteral -> { value = emitString(string_, context) }
    char_: CharLiteral -> { value = emitChar(char_.value) }
    bool_: BoolLiteral -> { value = if bool_.value then "true" else "false" }
    none_: NoneLiteral -> { value = emitNoneLiteral(if expected == none then none_.resolvedType else expected, context) }
    caller: CallerExpression -> {
      functionName := if context.currentFunctionName == "" then "<module>" else context.currentFunctionName
      span := if context.sourceLocationSpanOverride == none then caller.span else context.sourceLocationSpanOverride!.span
      fileName := moduleDiagnosticPath(context.modulePath, true, context.names)
      value = "std::make_shared<doof::SourceLocation>(std::string(\"" + fileName + "\"), " + string(span.start.line) + ", std::string(\"" + functionName + "\"))"
    }
    identifier: Identifier -> { value = emitIdentifier(identifier, context) }
    binary: BinaryExpression -> { value = emitBinary(binary, context) }
    unary: UnaryExpression -> { value = emitUnary(unary, context) }
    as_: AsExpression -> { value = emitAs(as_, context) }
    assignment: AssignmentExpression -> { value = emitAssignment(assignment, context) }
    member: MemberExpression -> { value = emitMember(member, context) }
    index: IndexExpression -> { value = emitIndex(index, context) }
    call: CallExpression -> { value = emitCall(call, context, expected); sourcePosition = .Return }
    array: ArrayLiteral -> { value = emitArray(array, context, expected) }
    object: ObjectLiteral -> { value = emitObject(object, context, expected) }
    tuple: TupleLiteral -> { value = emitTuple(tuple, context) }
    lambda: LambdaExpression -> { value = emitLambdaExpression(lambda, context, expected) }
    if_: IfExpression -> { value = emitIfExpression(if_, context, expected) }
    case_: CaseExpression -> { value = emitCaseExpression(case_, context, expected) }
    yieldBlock: YieldBlockExpression -> { value = emitYieldBlockExpression(yieldBlock, context, expected) }
    catch_: CatchExpression -> { value = emitCatchExpression(catch_, context) }
    construct: ConstructExpression -> { value = emitConstruct(construct, context) }
    async_: AsyncExpression -> { value = emitAsyncExpression(async_, context) }
    retire_: RetireExpression -> { value = emitRetireActor(retire_, context) }
    actor: ActorCreationExpression -> { value = emitActorCreation(actor, context) }
    dot: DotShorthand -> { value = emitDotShorthand(dot, context) }
    this_: ThisExpression -> {
      let structThis = false
      if this_.resolvedType != none {
        case this_.resolvedType! {
          class_: ClassType -> { structThis = class_.symbol.kind == "struct" }
          _ -> { }
        }
      }
      if structThis { value = "*this" }
      else { value = "this->shared_from_this()" }
    }
    _ -> { panic("Unsupported expression in initial C++ emitter: " + expression.kind) }
  }
  checkedSource := decoratedExpressionType(expression)
  sourceType := if checkedSource == none then none else specializeEmitType(checkedSource!, context)
  targetType := if expected == none then none else specializeEmitType(expected!, context)
  // The none literal branch already constructs the checked target carrier.
  if expression.kind == "none-literal" { return value }
  value = emitJsonValuePromotion(expression, value, sourceType, targetType)
  if sourceType != none {
    return emitCarrierConversion(value, sourceType!, if targetType == none then sourceType! else targetType!, context, sourcePosition)
  }
  return value
}

/** Calls need no result carrier when discarded; other values are explicitly ignored. */
export function emitDiscardedExpression(expression: Expression, context: EmitContext): string {
  case expression {
    call: CallExpression -> { return emitCall(call, context) }
    _ -> { return "static_cast<void>(" + emitExpression(expression, context) + ")" }
  }
}

// Literal collection emitters already construct JsonValue directly. Other
// expressions need an explicit runtime wrapper when contextual typing widens a
// primitive or an exact JSON carrier into JsonValue.
function emitJsonValuePromotion(expression: Expression, value: string, source: ResolvedType | none, expected: ResolvedType | none): string {
  if source == none || expected == none { return value }
  case expected! {
    _: JsonValueResolvedType -> { }
    _ -> { return value }
  }
  case source! {
    _: JsonValueResolvedType -> { return value }
    _: NoneType -> { return value }
    primitive: PrimitiveType -> {
      if primitive.name == "byte" || primitive.name == "char" { return "doof::json_value(static_cast<int32_t>(" + value + "))" }
    }
    _ -> { }
  }
  case expression {
    _: ArrayLiteral -> { return value }
    _: ObjectLiteral -> { return value }
    _ -> { }
  }
  return "doof::json_value(" + value + ")"
}

export function cppIdentifier(name: string): string { return emitCppIdentifier(name) }

function decimalLiteral(value: string): string {
  if value.contains(".") || value.contains("e") || value.contains("E") { return value }
  return value + ".0"
}
