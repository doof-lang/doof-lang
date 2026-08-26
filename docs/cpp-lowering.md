# C++ Lowering Notes

Generated definitions and executable statements carry C++ `#line` directives
for their originating Doof spans. Ordinary emitted snapshots use stable logical
module paths. Dedicated profile builds use the physical paths retained by the
filesystem source loader so native debug information can open the original
`.do` files. Compiler-owned entry wrappers and other glue reset attribution to
`<doof-generated>`. Manifest-native sources are compiled unchanged and retain
their native language debug mappings.

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
Each generated header is a consumer-projected, self-contained C++ worldview:
it renders the canonical declarations required by its matching source directly
in their defining namespaces and never includes another generated Doof header.
Sources include only their matching header and own definitions and executable
entry wrappers. Module storage declarations needed
by inline class-field or parameter defaults are emitted before their consumers,
including for Doof-private bindings. This generated C++ visibility is a lowering
detail and does not widen the binding's Doof module visibility.

`doof_runtime.hpp` is the first include in every generated header and owns the
standard-library baseline used by generated declarations. Native builds
precompile that runtime header, so generated headers do not repeat baseline
standard-library includes; feature-specific native headers remain responsible
for their own dependencies.

Named functions and methods borrow immutable parameters with `const&` when the
C++ carrier is reference-like or variant-heavy. Cheap scalar carriers,
direct-value structs, and unresolved generic parameters stay by value so Doof
value semantics are preserved. Function-valued callback signatures stay by
value because callbacks may queue or actor-dispatch arguments beyond the
caller's stack frame.

Consumer-projected headers preserve referenced, non-generic Doof type aliases
when their identity is present on checked annotations. Repeated anonymous
unions whose C++ alternatives are only `std::monostate` and `std::shared_ptr`
receive generated aliases such as `__type1`. Anonymous alias indices are unique
across the complete projected header, including across namespace sections. This keeps large
reference-only `std::variant` carriers single-spelled without hoisting variants
that require complete by-value nominal definitions.

Actors, promises, escaping mutable captures, `Result`, checked narrowing,
destructuring, JSON serialization, metadata/invoke, and WebAssembly wrappers
have dedicated lowering modules. Representation changes require focused emitter
tests and generated-C++ compile/runtime coverage in the release gate.

Declarative module bindings and static fields use direct typed storage. Scalar
constant expressions may initialize storage directly; strings, collections,
classes, and other constructed values are assigned by generated
`__doof_initialize_module` functions. Only modules with deferred assignments
emit such a function, and it contains assignments without a per-module state
machine. Native entry boundaries call those functions dependency-first after
installing `ActiveActorScope`. WebAssembly exposes the same graph protocol
through `doof_initialize`. Generated non-native structs have an internal
default constructor, and their literal-valued backing fields remain mutable in
C++; these representation details let ordered initialization assign whole
struct values while the Doof checker continues to enforce source immutability.

Native entries containing top-level statements retain a private
`__doof_run_script` function and checked script storage. The native boundary
runs declarative module initialization, then the script, then optional `main`.
