# Absence and union carrier review

The repeated failures came from selecting a C++ representation before applying
generic substitutions, and from separate lowering paths making different
decisions about the same checked type.

## Representation contract

| Checked type | C++ absence value |
| --- | --- |
| `none` as a stored value | `std::monostate{}` |
| A nullable class or collection with pointer storage | `nullptr` |
| A nullable primitive, enum, or struct | `std::nullopt` |
| A nullable variant | `std::monostate{}` |
| Weak storage | An empty value of its contextual weak carrier |
| `JsonValue` | `doof::json_value(nullptr)` |

A function returning `none` uses C++ `void`; this is separate from storing the
unit value in a collection, tuple, or variant.

## Corrections

- `emitNoneLiteral` applies the active generic substitution before choosing a
  carrier. Its union handling uses `naturalNullableUnionMember`, the same
  flattened classification used by type emission. This fixes AppKit's
  `OutlineData<Row>.rowAt` and nested optional specializations.
- Type-parameter substitution normalizes unions after substitution, so
  substituting an optional type into `T | none` preserves one canonical optional
  type for subsequent narrowing and representation decisions.
- Catch initialization calls the same absence helper and emits its result type
  contextually. Its former C++ string-prefix heuristic was removed.
- Array elements receive their checked element type. A bare `none` without an
  expected type uses its own checked unit type, fixing unit tuples as well.
- Generic `as` narrowing, `try?` lambda signatures, and `Success`/`Failure` object payloads use
  contextual type emission, matching their enclosing specialization.
- Applying deep readonly to a union normalizes the resulting arms. The reported
  `readonly scopes = if ... then [scope] else effect.rerollScopes` therefore
  becomes one readonly array type before emission.

These changes preserve the existing assignment rules; they do not make mutable
and readonly collection types freely interchangeable.

## Remaining audit finding

An inferred local with no readonly destination can still retain both mutable
and readonly array arms:

```doof
function choose(flag: bool, values: int[], frozen: readonly int[]): none {
  selected := if flag then values else frozen
}
```

Both semantic arms erase to the same C++ pointer type, producing an ambiguous
`std::variant<Array, Array>`. This separate case was reproduced and reported to
Quark. Resolving it requires a consistent policy for union arms that share a
runtime representation; applying readonly to every inferred join would change
the language's existing mutability rules.

## Verification

Focused regression functions use the `testGenericNoneLiteral` filter across
the affected modules. Native acceptance coverage is in
`tests/release-fixtures/nullable-carriers/main.do`, including successful and
absent values, row-index boundaries, and both readonly conditional branches.
