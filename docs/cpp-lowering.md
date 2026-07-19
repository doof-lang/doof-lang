# C++ Lowering Notes

Doof primitives map to fixed-width C++ values. Classes use shared ownership,
structs use value semantics, weak class references use `std::weak_ptr`, and
closed-world interfaces lower to variants of known implementors. Nullable and
union values use representation-appropriate optional/variant forms.

Functions, methods, statements, and expressions are emitted from checker-
decorated nodes. Whole-program monomorphization discovers concrete generic
functions, methods, classes, interfaces, and native adapters to a fixed point.
Generated headers own declaration ordering and dependency includes; sources own
definitions and executable entry wrappers.

Actors, promises, escaping mutable captures, `Result`, checked narrowing,
destructuring, JSON serialization, metadata/invoke, and WebAssembly wrappers
have dedicated lowering modules. Representation changes require focused emitter
tests and generated-C++ compile/runtime coverage in the release gate.

