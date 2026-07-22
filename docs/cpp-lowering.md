# C++ Lowering Notes

Doof primitives map to fixed-width C++ values. Classes use shared ownership,
structs use value semantics, weak class references use `std::weak_ptr`, and
closed-world interfaces lower to variants of known implementors. Nullable and
union values use representation-appropriate optional/variant forms.

Functions, methods, statements, and expressions are emitted from checker-
decorated nodes. Whole-program monomorphization discovers concrete generic
functions, methods, classes, interfaces, and native adapters to a fixed point.
Builtin calls and builtin type namespaces are selected from resolved binding
kinds rather than identifier spelling. Contextual dot shorthand is validated
against a declared enum variant or static class member before lowering.
Renamed nominal imports emit from resolved symbol identity. Shared members on
union values and construction-time union promotion are driven by decorated
source and target types; compiler source declaration names have no special
lowering behavior. Before visiting a nullable multi-arm union, lowering removes
the `monostate` absence arm through the standard forced-nullable boundary so the
generated visitor is valid for every remaining C++ alternative. Runtime-backed
builtin types use the same native-symbol metadata as declared native types.
Generated headers own declaration ordering and dependency includes; sources own
definitions and executable entry wrappers.

Actors, promises, escaping mutable captures, `Result`, checked narrowing,
destructuring, JSON serialization, metadata/invoke, and WebAssembly wrappers
have dedicated lowering modules. Representation changes require focused emitter
tests and generated-C++ compile/runtime coverage in the release gate.
