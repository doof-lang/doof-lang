// Lowering of values that can be absent at several layers (see absence-types).
//
// Postfix '!' panics at the first absent layer, postfix '?' returns none at the
// first absent layer, and declaration-else runs its handler. Each layer reads
// the present value of the layer outside it from one evaluated temporary, and
// tests short-circuit so inner layers are only read once outer ones are present.

import { AbsenceLayer, absenceLayers } from "./absence-types"
import { PrimitiveType, ResolvedType, ResultResolvedType } from "./semantic"
import { EmitContext } from "./emitter-context"
import { emitCarrierConversion } from "./emitter-carrier-values"
import { carrierOf } from "./emitter-carriers"
import { emitNoneLiteral, quote } from "./emitter-expr-literals"
import { moduleDiagnosticPath } from "./emitter-names"
import { emitContextType, specializeEmitType, usesVariantRepresentation } from "./emitter-types"

export function emitterAbsenceLayers(type_: ResolvedType, context: EmitContext): AbsenceLayer[] {
  return absenceLayers(specializeEmitType(type_, context))
}

/** The present value of `layer`, read from the expression for its source. */
function layerValue(source: string, layer: AbsenceLayer, context: EmitContext): string {
  if layer.failure { return "doof::success_value(" + source + ")" }
  // Removing none from a variant with one remaining arm yields that arm, not
  // the one-arm variant returned by the general runtime helper.
  if usesVariantRepresentation(layer.source) && !usesVariantRepresentation(layer.present) {
    return "std::get<" + emitContextType(layer.present, context) + ">(" + source + ")"
  }
  return "doof::unwrap_optional(" + source + ")"
}

function layerAbsent(source: string, layer: AbsenceLayer): string {
  return if layer.failure then "doof::is_failure(" + source + ")" else "doof::is_null(" + source + ")"
}

/** Expressions for each layer's source, then the present value, from `name`. */
function layerSources(name: string, layers: AbsenceLayer[], context: EmitContext): string[] {
  let sources: string[] = [name]
  for layer of layers { sources.push(layerValue(sources[sources.length - 1], layer, context)) }
  return sources
}

/** A short-circuiting test that is true when any layer of `name` is absent. */
export function emitAbsentTest(name: string, layers: AbsenceLayer[], context: EmitContext): string {
  sources := layerSources(name, layers, context)
  let test = ""
  for i of 0..<layers.length {
    if i > 0 { test = test + " || " }
    test = test + layerAbsent(sources[i], layers[i])
  }
  return test
}

/** The present value of `name` once every layer is known to be present. */
export function emitPresentValue(name: string, layers: AbsenceLayer[], context: EmitContext): string {
  sources := layerSources(name, layers, context)
  return sources[sources.length - 1]
}

/**
 * The declaration-else error: the Failure's error, or none when an outer or
 * inner none made the value absent.
 */
export function emitAbsentError(name: string, layers: AbsenceLayer[], errorType: ResolvedType, context: EmitContext): string {
  sources := layerSources(name, layers, context)
  noneValue := emitNoneLiteral(errorType, context)
  let body = ""
  for i of 0..<layers.length {
    layer := layers[i]
    if layer.failure {
      case layer.source {
        result: ResultResolvedType -> {
          error := emitCarrierConversion("doof::failure_error(" + sources[i] + ")", result.errorType, errorType, context)
          body = body + "if (doof::is_failure(" + sources[i] + ")) return " + error + "; "
        }
        _ -> { }
      }
    } else {
      body = body + "if (doof::is_null(" + sources[i] + ")) return " + noneValue + "; "
    }
  }
  return "[&]() -> " + emitContextType(errorType, context) + " { " + body + "return " + noneValue + "; }()"
}

/** Postfix '!': panics at the first absent layer. */
export function emitForced(operand: string, operandType: ResolvedType, line: int, context: EmitContext): string {
  layers := emitterAbsenceLayers(operandType, context)
  if layers.length == 0 { return operand }
  sources := layerSources("_forced_value", layers, context)
  sourcePath := quote(moduleDiagnosticPath(context.modulePath, true, context.names))
  let body = "auto _forced_value = " + operand + "; "
  for i of 0..<layers.length {
    layer := layers[i]
    let message = "std::string(\"! failed: value is none\")"
    if layer.failure {
      message = "std::string(\"! failed\")"
      case layer.source {
        result: ResultResolvedType -> {
          case result.errorType {
            primitive: PrimitiveType -> {
              if primitive.name == "string" { message = message + " + std::string(\": \") + doof::failure_error(" + sources[i] + ")" }
            }
            _ -> { }
          }
        }
        _ -> { }
      }
    }
    body = body + "if (" + layerAbsent(sources[i], layer) + ") doof::panic_at(" + sourcePath + ", " + string(line) + ", " + message + "); "
  }
  present := layers[layers.length - 1].present
  if carrierOf(present, .Payload).kind == .Void { return "[&]() -> std::monostate { " + body + "return {}; }()" }
  return "[&]() -> " + emitContextType(present, context) + " { " + body + "return std::move(" + sources[sources.length - 1] + "); }()"
}

/** Postfix '?': none at the first absent layer, otherwise the present value. */
export function emitOptional(operand: string, operandType: ResolvedType, resultType: ResolvedType, context: EmitContext): string {
  layers := emitterAbsenceLayers(operandType, context)
  outType := specializeEmitType(resultType, context)
  sources := layerSources("_optional_value", layers, context)
  noneValue := emitNoneLiteral(outType, context)
  let body = "auto _optional_value = " + operand + "; "
  for i of 0..<layers.length { body = body + "if (" + layerAbsent(sources[i], layers[i]) + ") return " + noneValue + "; " }
  present := emitCarrierConversion("std::move(" + sources[sources.length - 1] + ")", layers[layers.length - 1].present, outType, context)
  return "[&]() -> " + emitContextType(outType, context) + " { " + body + "return " + present + "; }()"
}
