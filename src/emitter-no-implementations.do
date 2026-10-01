// Interfaces without implementing classes.
//
// An interface lowers to a closed-world variant of its implementing classes.
// With none (no implementers at all, or only generic implementers that are
// never instantiated) the variant's sole alternative is doof::NoImplementations
// and no value of the interface can exist. Helpers declared against the
// interface still check and emit; member access on such a value lowers to an
// unreachable panic of the checked result type instead of a visitor that
// could not compile.
import { ExportDeclaration, InterfaceDeclaration } from "./ast"
import type { Statement } from "./ast"
import { InterfaceType, ResolvedType } from "./semantic"
import { substituteTypeParams } from "./checker-types"
import { EmitContext } from "./emitter-context"
import { interfaceInstantiationKey } from "./emitter-monomorphize"
import { emitContextReturnType, specializeEmitType } from "./emitter-types"
import { quote } from "./emitter-expr-literals"

/** The interface a receiver type lowers to when it has no implementations. */
export function implementationlessInterface(receiver: ResolvedType | none, context: EmitContext): InterfaceType | none {
  if receiver == none { return none }
  case specializeEmitType(receiver!, context) {
    interface_: InterfaceType -> {
      if interface_.typeArgs.length > 0 {
        key := interfaceInstantiationKey(interface_.symbol.module, interface_.name, interface_.typeArgs)
        return if context.implementationlessInterfaceKeys.contains(key) then interface_ else none
      }
      for implementation of interface_.symbol.implementations {
        if implementation.native_ || implementation.typeParams.length == 0 { return none }
        if context.instantiatedClassOwners.contains(implementation.module + "::" + implementation.name) { return none }
      }
      return interface_
    }
    _ -> { return none }
  }
}

/** Evaluates the receiver for its effects, then panics as `resultType`. */
export function emitNoImplementationsAccess(receiver: string, interface_: InterfaceType, resultType: ResolvedType | none, context: EmitContext): string {
  result := if resultType == none then "void" else emitContextReturnType(resultType!, context)
  return "(static_cast<void>(" + receiver + "), doof::no_implementations<" + result + ">(" + quote(interface_.name) + "))"
}

/** The declared type of an interface field, for accesses without a decorated result type. */
export function interfaceFieldType(interface_: InterfaceType, field: string, context: EmitContext): ResolvedType | none {
  for program of context.allPrograms {
    for statement of program.statements {
      declaration := interfaceDeclarationIn(statement) else { continue }
      symbol := declaration.resolvedSymbol else { continue }
      if symbol.module != interface_.symbol.module || symbol.name != interface_.symbol.name { continue }
      for candidate of declaration.fields {
        if candidate.name != field || candidate.resolvedType == none { continue }
        if declaration.typeParams.length == 0 { return candidate.resolvedType }
        return substituteTypeParams(candidate.resolvedType!, declaration.typeParams, interface_.typeArgs)
      }
      return none
    }
  }
  return none
}

function interfaceDeclarationIn(statement: Statement): InterfaceDeclaration | none {
  case statement {
    interface_: InterfaceDeclaration -> { return interface_ }
    export_: ExportDeclaration -> { return interfaceDeclarationIn(export_.declaration) }
    _ -> { return none }
  }
}
