# Type checker review TODO

Review date: 2026-09-06. Findings reproduced against the current working tree.

- [x] Validate statement-level `try` return channels and error compatibility, respecting native entry scripts and catch/function boundaries.
- [x] Apply deep readonly semantics to `try readonly` success bindings.
- [x] Require invariant writable interface field types.
- [x] Reject assignment to nonassignable members, including collection/string properties and methods.
- [x] Validate contextual byte literal bounds (0–255).
- [x] Propagate `with` body control-flow completion.
- [x] Complete `try` declaration checking: annotations, semantic decoration, and rejection of bound `none` payloads.
- [x] Address the known numeric generic-bound operator gap without allowing unsafe promotions or losing correlation with the type parameter.
- [x] Run focused regression tests serially, then the normal full test gate.

Each completed item must have focused regression coverage beside its compiler module. Update specifications and the repository language skill for clarified semantics. Preserve pre-existing working-tree changes; generated bootstrap refresh is outside this task.

## Implementation and compatibility notes

- `checker-try.do` owns Result propagation and success binding semantics.
- `checker-numeric.do` owns numeric capability and correlated promotion rules.
- Writable interface fields are invariant. Union field writes remain valid only
  when every alternative exposes the same mutable field type.
- Numeric-only bounds now list exact primitive alternatives: widening and runtime
  union values do not satisfy them. Explicitly convert or narrow before calling.
- Typed `try` declarations use the checked storage type in generated C++.
- Frontend semantic ABI is 14, invalidating cached pre-fix checking decisions.

Native regression: `tests/release-fixtures/type-checker-review/main.do`.

## Verification

- `dist/doof test src --filter testCheckerReview`: 16 focused regressions passed.
- `./scripts/test.sh`: 925 compiler tests passed, plus all four supporting gates.
- `./install.sh` built an isolated development compiler under
  `build/review-dev-home`.
- The rebuilt compiler successfully checked `src/driver.do` and compiled and
  ran the native fixture, including unsigned shifts and compound powers.
- `git diff --check` passed. No bootstrap refresh or release build was performed.
