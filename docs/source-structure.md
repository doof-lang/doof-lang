# Source Structure

Production code and focused tests live together under `src/`.

- `lexer.do`, `parser*.do`, `ast.do` — syntax and source spans
- `resolver.do`, `analyzer.do`, `semantic.do` — modules and symbol analysis
- `checker*.do`, `json-semantics.do` — type checking and semantic validation
- `emitter-*.do` — C++ types, expressions, statements, declarations, JSON,
  metadata, WebAssembly, module headers, monomorphization, and project planning
- `compiler.do` — checked graph to generated project orchestration
- `cli.do`, `project.do`, `package-*.do`, `dependency-policy.do` — command and
  package contracts
- `driver.do`, `native-build.do`, platform driver modules — filesystem,
  process, native toolchain, test, and application boundaries
- `*.test.do` — focused unit/component tests for the adjacent concern

Other maintained inputs:

- `runtime/doof_runtime.h` — canonical generated-program runtime
- `resources/std-catalog.json` — embedded exact standard-package catalog
- `tools/update-std-catalog.do` — catalog maintenance tool
- `tests/release-fixtures/` — native and platform acceptance packages
- `bootstrap/macos-arm64/generated/` — generated stage-0 trust root

Keep files focused and make ownership changes explicit in this document.

