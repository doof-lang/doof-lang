# Testing

Test files end in `*.test.do`. The runner recursively discovers them without
crossing nested package manifests. Exported, zero-argument functions whose names
begin with `test` are test cases.

```doof
import { Assert } from "std/assert"

export function testAddsValues(): void {
  Assert.equal(2 + 2, 4)
}
```

Run the compiler suite with:

```sh
./scripts/test.sh
```

Run another package directly with:

```sh
dist/doof test path/to/package
dist/doof test path/to/package parser
dist/doof test path/to/package --list
dist/doof test path/to/package --coverage --coverage-output build/coverage/report.json
```

Each test file receives an isolated generated harness and process. Coverage
aggregates stable source-line markers and produces text, JSON, summary HTML,
and annotated per-file HTML output. Use `mock import` for root-scoped import
replacement where supported.

Focused semantic tests belong beside their source module. Native
representation, runtime, resource, package, and Apple-platform behavior belongs
in `tests/release-fixtures/` and `./scripts/release.sh`.

