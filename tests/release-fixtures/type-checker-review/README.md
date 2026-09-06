# Type checker review native regression

With a development compiler built from the current source, run:

```sh
doof run tests/release-fixtures/type-checker-review/main.do -o build/type-checker-review-native
```

This verifies concrete float/double and integer generic operators, correlated
compound-assignment promotion, typed `try` storage beyond the int range,
readonly success bindings, error propagation into a wider union, and `with`
return completion. It must print `type checker review native checks passed`.

The adjacent checker and emitter component tests under `src/` cover rejected
programs and semantic decoration. This fixture additionally compiles generated
C++ and checks its runtime behavior.
