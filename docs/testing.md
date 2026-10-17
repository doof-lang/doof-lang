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
dist/doof test path/to/package --filter parser
dist/doof test path/to/package --exact-filter parser.test.do::testDiagnosesMalformedTypedTags
dist/doof test path/to/package --list [--json]
dist/doof test path/to/package --coverage --coverage-output build/coverage/report.json
dist/doof test path/to/package --target wasm
```

`--filter` selects test ids containing the text; `--exact-filter` selects one
exact id. `--selection-json <file>` selects the exact ids in a JSON array and
cannot be combined with either filter. `--report-json <file>` writes structured
results, and `--list --json` prints discovery as JSON.

Selected test files without `mock import` share one generated harness and
native executable. Every test function still runs in a fresh process, but all
modules in that shared graph perform module-level initialization in each test
process. A test file that declares `mock import` receives its own isolated
harness and executable so its substitutions cannot affect another root.

Separate compiler invocations for one project queue on its `build/.doof.lock`
(or configured `build.buildDir`). The lock covers compilation and all test
workers, including coverage and custom output directories. `--list` remains
read-only and does not wait. Parallel workers inside the owning invocation
continue to run normally.

After rebuilding the compiler, `tools/run.sh process-test` runs the POSIX
process regression for waiting builds and tests, cancellation of a waiter,
independent projects, and lock ownership through test-worker execution.

On macOS, a package with `build.target = "wasm"` or an explicit `--target wasm`
builds the generated harness as a standalone Emscripten Wasm command. Each test
runs in a fresh process, JavaScriptCore context, and WebAssembly instance, so
the native runner's module-initialization and failure-isolation contract is
preserved. The bundled Apple host implements command arguments, an empty
environment, standard output/error, process exit, and cryptographically secure
WASI `random_get` using Apple Security. Random requests validate guest memory
bounds and transfer bytes in bounded chunks; invalid addresses and RNG failures
return WASI errors. Guest filesystem access
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

## Language corpora

`./scripts/test.sh` also runs two command-level corpora (on their own,
`tools/run.sh corpus-test`):

- `tests/analyzer-false-negatives/` holds invalid programs. Each must be
  rejected with exactly the `// expect-error: <line>:<column> <message>`
  diagnostics it declares, and `doof emit` must write no output for it. See
  that directory's README.
- Code fences opened with ` ```doof check ` in `spec/` and in the Doof
  language skill (`.github/skills/doof-language/`) are written to standalone
  files under `build/spec-examples/<chapter>/` or
  `build/skill-examples/<page>/` and must pass `doof check`. A fence
  opened with ` ```doof check math.do ` (any mode may end with a relative
  `.do` path) is written under that name, and every chapter file is written
  before any is checked, so examples can import one another. Fences opened with
  ` ```doof check body ` hold statements and are checked inside a generated
  `function example(): none { ... }`, which shifts reported lines by one.
  Fences opened with ` ```doof reject ` (or ` ```doof reject body `) show invalid
  code: `doof check` must fail, every code line containing ❌ must report an
  error, and no other line may. A comment-only line with ❌ is a heading.
  A checked file with top-level statements is a native entry script, so
  examples may run statements directly. Plain ` ```doof ` fences are not
  checked; keep them for signature outlines (bodiless members) and examples
  that need a package manifest. Make every other example complete so it can
  use one of the checked forms.

Focused semantic tests belong beside their source module. Native
representation, runtime, resource, package, and Apple-platform behavior belongs
in `tests/release-fixtures/` and `./scripts/release.sh`.
