# Compiler Architecture

The compiler processes a closed source graph in four phases:

1. The lexer and parser produce a source-spanned AST.
2. The analyzer collects module symbols, resolves imports/re-exports, and
   decorates named types.
3. The checker builds scopes, resolves bindings, infers expression types,
   validates control flow/isolation, and decorates the AST in place.
4. The emitter consumes only the decorated graph and writes split C++17
   modules plus explicit runtime/native support inputs.

`compiler.do` coordinates the pure graph pipeline. `driver.do` owns CLI,
package acquisition, test, app, and general filesystem/process boundaries.
`emitter-project.do` combines generated modules with manifest-owned native
inputs. `native-build.do` creates stable compile/link tasks;
`native-build-driver.do` fingerprints their compiler arguments and discovered
header dependencies, persists versioned state, skips clean PCH/object/link
work, and executes dirty tasks with bounded parallelism.

Native entry scripts are lowered within the entry translation unit. Private
deferred binding storage and one generated runner preserve source order without
introducing a graph-wide initialization protocol. Reference modules and
WebAssembly libraries retain ordinary namespace-scope initialization.

The checker and emitter are split by concern. Shared semantic contracts live in
`semantic.do`, checker state/types modules, and the emit-readiness validation
walk. Unknown types, missing decorations, constraints, or dispatch targets
must suppress emission rather than trigger guessed lowering.

Control-flow lowering follows the same boundary. The checker decorates case
statements with whether normal execution can continue; the emitter uses that
fact to preserve proven exhaustiveness in C++ with the runtime's
`[[noreturn]]` unreachable guard. The emitter does not repeat exhaustiveness
analysis from patterns.

Closed-world information drives interface variants, generic specialization,
actor isolation validation, JSON/reflection generation, and stable module
namespaces. The runtime header supplies intrinsic values, collections, actors,
JSON, metrics, resource lookup, and other generated-code support.
