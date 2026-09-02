# C++ Lowering Notes

Generated definitions and executable statements carry C++ `#line` directives
for their originating Doof spans. Ordinary emitted snapshots use stable logical
module paths. Dedicated profile builds use the physical paths retained by the
filesystem source loader so native debug information can open the original
`.do` files. Compiler-owned entry wrappers and other glue reset attribution to
`<doof-generated>`. Manifest-native sources are compiled unchanged and retain
their native language debug mappings. The reviewed bootstrap snapshot is the
one exception: its refresh pipeline removes emitted `#line` directives after
fixed-point verification so source-line-only changes do not churn the trust
root. This canonicalization does not change ordinary compiler emission.

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

Enum declarations remain C++ `enum class` identities. Integer-backed enums use
their checked backing integers as enumerator values. String-backed enums use
declaration ordinals internally and generated typed name/value lookup helpers;
wire serialization never exposes those internal ordinals. Formatting calls the
name helper, while JSON and JSON Schema consume checked backing values. A
single `Enum | none` lowers uniformly to `std::optional<Enum>` so all ordinary
narrowing forms yield `Enum`, not a residual optional variant.

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
entry wrappers. Generated headers contain declarations and dependency-free
constructors, not executable Doof defaults or method/destructor bodies. Module
storage declarations needed by generated definitions are emitted even for
Doof-private bindings; this generated C++ visibility is a lowering detail and
does not widen the binding's Doof module visibility.

Every reached Doof-owned generic, including a generic method on a non-generic
class, is closed-world monomorphized. Only runtime- and native-owned C++
templates survive lowering. Native headers may define templates or overloads
that consume concrete monomorphized Doof representations, but an ABI requiring
an exact open C++ template identity must define that template natively. Concrete
names use compact type spellings; when two nominally distinct specializations
produce the same spelling in one C++ scope, later names receive deterministic
numeric suffixes such as `_2` and `_3`.

Doof parameter and field defaults are materialized at generated Doof call and
construction sites. They are not emitted as C++ default arguments, so native
C++ callers of generated declarations must pass every argument explicitly.

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
receive generated aliases such as `doof_header_type_1`. Anonymous alias names
are unique after C++ identifier escaping across the complete projected header,
including user declarations, concrete specializations, and namespace sections. This keeps large
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
