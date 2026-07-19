# Compiler Architecture

The compiler processes a closed source graph in four phases:

1. The lexer and parser produce a source-spanned AST.
2. The analyzer collects module symbols, resolves imports/re-exports, and
   decorates named types.
3. The checker builds scopes, resolves bindings, infers expression types,
   validates control flow/isolation, and decorates the AST in place.
4. The emitter consumes only the decorated graph and writes split C++17
   modules plus explicit runtime/native support inputs.

`compiler.do` coordinates the pure graph pipeline. `driver.do` owns filesystem,
process, package acquisition, native build, test, app, and CLI boundaries.
`emitter-project.do` combines generated modules with manifest-owned native
inputs; `native-build.do` creates bounded parallel compile/link tasks.

The checker and emitter are split by concern. Shared semantic contracts live in
`semantic.do`, checker state/types modules, and the emit-readiness validation
walk. Unknown types, missing decorations, constraints, or dispatch targets
must suppress emission rather than trigger guessed lowering.

Closed-world information drives interface variants, generic specialization,
actor isolation validation, JSON/reflection generation, and stable module
namespaces. The runtime header supplies intrinsic values, collections, actors,
JSON, metrics, resource lookup, and other generated-code support.

