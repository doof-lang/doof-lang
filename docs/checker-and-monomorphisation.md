# Checker and Monomorphisation Horizontal Slices

This document follows checked meaning from source syntax to concrete C++.
It complements the broad [compiler architecture](compiler-architecture.md)
map and the file-by-file [source structure](source-structure.md) index. The
language contract remains in the [type-system specification](../spec/02-type-system.md).

The production path is:

```text
compiler.compileInternal
  -> analyzer.analyze
  -> createChecker
  -> ModuleChecker.check for every module, dependency first
  -> graph-wide actor and isolation validation
  -> validateCheckedTypes
  -> buildInstantiationPlan
  -> emitWasmSupport when requested
  -> emitModuleGraph
```

Direct calls to `createAnalyzer`, `createChecker`, `buildInstantiationPlan`, or
`emitModuleGraph` are test seams. They are useful for focused tests, but they do
not individually reproduce the production pipeline. In particular, a direct
`ModuleChecker.check` checks one module, and direct emission assumes its input
graph has already passed the complete decoration gate.

## The phase contract

The checker and monomorphiser do different jobs. Keeping that distinction
sharp prevents a second type checker from growing in the backend.

| Question | Authoritative owner | Persisted result |
| --- | --- | --- |
| What declaration or binding does this syntax name? | analyzer and `checker-symbols.do` | `Symbol` or `Binding` decorations |
| What type does an annotation or expression have? | `checker-resolution.do` and the focused expression/statement checker | `resolvedType` decorations |
| Which callable or constructor was selected, and where is it defined? | `checker-calls.do` and `checker-generics.do` | `resolvedFunction`, `resolvedFunctionModule`, `resolvedConstructor`, and `resolvedClass` |
| What concrete generic arguments did this call infer? | `checker-calls.do` and `checker-generics.do` | `resolvedGenericTypeArgs` |
| Is one type assignable to another? | `checker-types.do` for pure type relations; `checker-interfaces.do` for graph-aware structural relations | a checker decision; symbol registries cache closed-world facts |
| Which concrete declarations are reached? | `emitter-monomorphize.do` | `InstantiationPlan` |
| Which declarations must a consumer header see? | `emitter-worldview.do` | `WorldviewPlan` |
| How is a checked operation represented in C++? | focused emitter modules | generated header/source text |

`checker-validation.do` is the boundary guard. It walks the complete analyzed
graph after checking and rejects missing or unknown types, unresolved bindings,
and required construction attachments. Emission may panic when that internal
contract is violated, but ordinary source errors must have become diagnostics
before this point.

The guard is deliberately stricter than “every expression has a type.” A new
semantic choice needed during lowering requires all four changes:

1. Add a dedicated slot to `ast.do` or `semantic.do`.
2. Populate it in the owning analyzer or checker module.
3. Require it in `checker-validation.do`.
4. Consume it without re-resolving syntax in the emitter.

## Slice: an ordinary generic function call

For `identity<int>(value)` or an inferred `identity(value)`, the implementation
crosses these layers:

1. `parser-expressions.do` records syntactic `typeArgs` and arguments on a
   `CallExpression`.
2. The analyzer establishes import and defining `Symbol` identity;
   `checker-symbols.do` decorates identifiers and namespace members with that
   identity.
3. `checker-calls.do` checks the callee and arguments. It obtains the selected
   declaration through `functionDeclarationForCallee` in
   `checker-generics.do`.
4. Explicit arguments are resolved, or `inferTypeArgument` structurally
   matches parameter types against argument types. Conflicting candidates are
   rejected rather than silently selecting one.
5. Constraints are validated by `validateTypeArgumentConstraints`.
6. The call retains the selected declaration in `resolvedFunction`, its
   defining path in `resolvedFunctionModule`, and the complete substitution in
   `resolvedGenericTypeArgs`. This is equally true for local identifiers,
   named imports, and namespace members. The effective function type and call
   result are obtained with `substituteTypeParams`.
7. `checker-validation.do` verifies the syntactic and resolved type arguments.
8. `buildInstantiationPlan` scans the checked graph. A concrete generic call
   adds a `FunctionInstantiation`, keyed directly from
   `resolvedFunctionModule`, declaration name, and canonical concrete type
   keys. It does not rediscover ownership from callee syntax.
9. The fixed-point loop scans the specialized body. Calls and nominal types
   reached from that body can append more work.
10. `emitter-module.do` registers key-to-name mappings in each `EmitContext`,
    declares the concrete function in the projected header, and emits its body
    in the defining module.
11. `emitter-expr-calls.do` recomputes the same instantiation key from checked
    call data and emits the registered concrete name. A missing registry entry
    is an internal compiler error.

Inference is a checker concern. Reachability is a monomorphiser concern. C++
overload resolution is not used to finish either job.

## Slice: a generic class or struct

For `Box<int>`:

1. `checker-resolution.do` resolves the nominal symbol, validates arity and
   constraints, and creates a `ClassType` containing the concrete `typeArgs`.
2. Construction checking records `resolvedClass`, `resolvedConstructor`, and
   `resolvedConstructedType` where applicable. Field values are checked against
   owner-substituted field types.
3. Any checked occurrence of the concrete nominal type reaches `collectType`
   in `emitter-monomorphize.do`, which creates a `ClassInstantiation` for a
   Doof-owned generic declaration. Native-owned generic types stay native.
4. Scanning that instantiation substitutes owner parameters through fields,
   defaults, ordinary methods, and the destructor. Generic methods are queued
   only from concrete call sites.
5. Header and definition emission install the owner substitution in
   `EmitContext.substitution`. All focused emitters see specialized types
   through that context.

Concrete C++ names are allocated per generated C++ scope. A readable mangled
base is used first; deterministic numeric suffixes resolve collisions between
nominal types that share the same short spelling.

## Slice: a generic method

A generic method has two substitutions:

```text
owner substitution:  Box<T> used as Box<int>
method substitution: map<U>(...) called as map<string>(...)
```

`MethodInstantiation` retains both by concatenating the owner's parameter
names and arguments with the method's names and arguments. Its key contains
the concrete owner key, method name, and method arguments. This prevents
`Box<int>.map<string>` and `Box<bool>.map<string>` from sharing a body with the
wrong owner substitution.

Implicit method calls and explicit member calls enter discovery differently:

- an identifier binding of kind `method` uses its owner symbol and the active
  owner substitution;
- a member call uses the specialized receiver `ClassType`.

Both paths must select the same `MethodInstantiation` key later used by
`emitter-expr-calls.do`.

## Slice: structural interfaces

Interfaces combine checker-time assignability with backend-time closed-world
layout, so there are two related products:

- `isAssignableWithInterfaces` answers whether a checked type is assignable
  to an interface type, substituting both class and interface arguments;
- `InterfaceInstantiation.implementations` lists the concrete alternatives to
  place in the generated C++ variant.

For a non-generic interface, `discoverInterfaceImplementations` eagerly
compares class and interface symbols and caches matching class symbols in
`Symbol.implementations`. This cache supports pure nominal assignability and
closed-world discovery, but it is not a second conformance definition.

For a concrete generic interface such as `Reader<int>`, annotation resolution
may cache matches for ordinary classes in `implementedInterfaceTypes`.
Assignment, arguments, returns, construction, literals, and constraints all
use `isAssignableWithInterfaces`, which directly checks a concrete
`ClassType` against a concrete `InterfaceType`. Correctness therefore does not
depend on eagerly registering a generic declaration: `Box<int>` is checked
with `Box`'s `T := int` substitution at the use site.

`classSatisfiesInterface` and concrete generic conformance both delegate to
`classSatisfiesConcreteInterface`. The operation substitutes owner and
interface parameters before comparing members. Required method parameter
types are invariant; returns are covariant through graph-aware assignability.
An inferred class field participates only after it has a resolved type. An
unresolved inferred field is a non-match, never a forced optional or a panic.

After generic reachability converges, the monomorphiser builds each concrete
interface variant. It calls the same concrete conformance operation for
reached ordinary classes and reached generic class instantiations, keeping
checker acceptance and C++ variant membership aligned.

`Stream<T>` is intrinsic. Class symbols retain stream element patterns and
`isAssignable` substitutes class arguments before comparing an actual stream
element type. The monomorphiser has matching intrinsic implementation logic
when it builds concrete stream variants.

The conformance recursion carries a visited class/interface-pair set. This
allows nested structural return types without non-termination while retaining
the conservative rule that an unresolved declaration or field cannot prove a
match.

## Slice: generated JSON and metadata demand

JSON eligibility and JSON code demand are intentionally separate:

1. `json-semantics.do` defines whether a checked type can support automatic
   serialization or deserialization.
2. Checker member resolution advertises only synthetic methods that can be
   generated and marks metadata needs on declarations.
3. The monomorphisation walk observes checked member uses:
   `toJsonObject`, `fromJsonValue`, and `metadata`.
4. `InstantiationPlan` records direction-specific class keys in
   `jsonSerializationKeys` and `jsonDeserializationKeys`. Demand is propagated
   recursively through supported field, collection, tuple, and union types.
5. WebAssembly wrapper planning adds entry-parameter deserialization and
   result serialization demand to the same plan before ordinary graph
   emission.
6. `emitter-json.do` emits only the requested directions. Metadata emission
   uses the same checked types when it constructs schemas and invocation
   adapters.

This demand analysis belongs beside generic reachability because both are
closed-world fixed-plan inputs to every projected header. It does not make
JSON eligibility a backend semantic decision.

## Slice: instantiation plan to projected modules

The instantiation plan is global, while generated files are per source module:

1. `emitModuleGraph` builds or accepts the one graph-wide `InstantiationPlan`.
2. `planWorldview` starts from each consumer module's checked symbol and type
   uses and computes a declaration closure in defining namespaces.
3. Concrete interface keys from both checked types and the global plan keep
   required interface aliases and implementors visible in the consumer
   header.
4. `planHeader` orders the selected declaration surface. Concrete functions,
   classes, methods, and interfaces are then added for the defining section.
5. Source emission writes only definitions owned by that source module.
6. The global plan contributes to every module fingerprint because changing a
   closed-world implementor or specialization set can change a consumer's
   header even when that consumer's source text is unchanged.

Worldview planning is not reachability analysis for executable generic bodies;
monomorphisation is not header dependency projection. They traverse some of
the same checked nodes but produce different products.

## Whole-graph and whole-AST passes

Several post-parse walks are active, not legacy alternatives:

| Walk | Purpose | Side effects or product |
| --- | --- | --- |
| analyzer visitors | symbols, imports, named type identity | analysis graph and AST type-symbol decoration |
| expression/statement checker | lexical meaning and types | bindings, types, call targets, control-flow facts |
| actor lifecycle walker | conservative straight-line use after retire | diagnostics |
| async capture walker | capture names and worker-boundary validation | `resolvedCaptureNames` and diagnostics |
| isolation graph walker | transitive mutable-global effects | graph diagnostics |
| checker validation walker | emission-readiness proof | diagnostics only |
| monomorphisation walker | concrete generic and JSON demand reachability | `InstantiationPlan` |
| worldview walker | consumer declaration closure | `WorldviewPlan` |
| focused emitter walkers | C++ rendering and local capture details | generated text |

`ast-walk.do` owns the shared shallow statement/expression child collectors.
Actor lifecycle, async capture, isolation, and worldview planning consume
those primitives but retain their separate worklists, stopping rules, and
semantic products. New syntax with expression children must update
`ast-walk.do` and its focused traversal test once, rather than synchronizing a
checker copy with an emitter copy.

The monomorphisation and validation walkers cannot be replaced by the shallow
collector alone. They also visit type annotations, declaration surfaces,
patterns, defaults, and specialized types, and they perform pass-specific work
at each node.

## August 2026 audit resolution

The audit removed the known divergent and legacy paths:

- namespace-qualified generic calls now carry and consume the checker-resolved
  defining module;
- generic class instances use the same substituted structural-interface check
  as ordinary classes;
- unresolved inferred fields conservatively fail conformance without aborting
  checking;
- generic and non-generic interface method returns share covariant matching;
- checker and worldview consumers share `ast-walk.do`; and
- the uncalled `ModuleAnalyzer.keepStatementTypes` visibility shim was removed.

The frontend semantic ABI was bumped with these changes so stale cached
decorations and emission plans cannot cross this boundary. The reviewed
source-only bootstrap snapshot was regenerated from two consecutive matching
compiler generations and passed the release gate before and after replacement.

## Change checklist

When changing checking or specialization:

1. Identify the checker owner and the exact AST/semantic decoration produced.
2. Cover named imports, renamed imports, namespace imports, implicit methods,
   explicit members, constructors, and native declarations where the feature
   can reach them.
3. Cover the feature inside defaults, case value/range patterns, `as`, lambdas,
   async blocks, yield/catch blocks, and nested generic bodies as applicable.
4. Add or extend the `checker-validation.do` requirement before consuming a
   new decoration in emission.
5. For generics, cover explicit and inferred calls, generic owners, generic
   methods, cross-module calls, and a fixed-point chain.
6. For interfaces, cover the generic/non-generic matrix described above and
   ensure checker acceptance matches the emitted variant alternatives.
7. Run a focused exact test, then `./scripts/test.sh` serially.
8. If lowering or bootstrap output changes, follow the bootstrap fixed-point
   workflow rather than editing generated C++.
