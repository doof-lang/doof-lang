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
dist/doof test path/to/package --target wasm
```

Selected test files without `mock import` share one generated harness and
native executable. Every test function still runs in a fresh process, but all
modules in that shared graph perform module-level initialization in each test
process. A test file that declares `mock import` receives its own isolated
harness and executable so its substitutions cannot affect another root.

On macOS, a package with `build.target = "wasm"` or an explicit `--target wasm`
builds the generated harness as a standalone Emscripten Wasm command. Each test
runs in a fresh process, JavaScriptCore context, and WebAssembly instance, so
the native runner's module-initialization and failure-isolation contract is
preserved. The bundled Apple host implements command arguments, an empty
environment, standard output/error, and process exit. Guest filesystem access
is not yet supported. This path requires `em++` and `xcrun swiftc` on the host.

Test processes run through a bounded queue of at most four workers. Progress is shown
as a fixed-width completed/total bar; successful cases stay quiet, while failed
cases replay their captured output and print their test id.

Generated files are written only when their contents change. Native builds
persist dependency-aware object, precompiled-header, and link state under the
output directory, so an unchanged warm test run performs no native compiler or
linker work. Coverage uses a separate build directory and state. `--list`
performs static discovery only and never invokes the compiler toolchain.

Coverage aggregates stable source-line markers and produces text, JSON,
summary HTML, and annotated per-file HTML output.

Focused semantic tests belong beside their source module. Native
representation, runtime, resource, package, and Apple-platform behavior belongs
in `tests/release-fixtures/` and `./scripts/release.sh`.
