# Compiler Documentation

The compiler documentation has three complementary views:

- [Source structure](source-structure.md) is the **vertical map**. Start there
  to find the module that owns a phase, data structure, side effect, or test.
- [Compiler architecture](compiler-architecture.md) is the **horizontal map**.
  Start there to follow a concept across parsing, analysis, checking, lowering,
  runtime support, and acceptance tests.
- [Checker and monomorphisation](checker-and-monomorphisation.md) is the
  **detailed semantic slice**. Start there to trace decorated calls, generic
  reachability, structural interfaces, JSON demand, and projected emission.

Neither document defines the language. User-visible syntax and semantics belong
in the [language specification](../spec/01-overview.md); the architecture docs
explain how this compiler implements that contract.

## Find the right document

| Question | Start here |
| --- | --- |
| Which source file should I change? | [Source structure](source-structure.md) |
| Which phases participate in a language feature? | [Compiler architecture](compiler-architecture.md) |
| How does a checked generic or interface use become concrete C++? | [Checker and monomorphisation](checker-and-monomorphisation.md) |
| What does Doof mean at the language level? | [Language specification](../spec/01-overview.md) |
| How does a checked value map to C++? | [C++ lowering](cpp-lowering.md) |
| How are packages, resources, and native inputs modeled? | [Packages](packages.md) |
| Where does a CLI command route? | [CLI](cli.md) |
| Where should a test live and how does the runner work? | [Testing](testing.md) |
| How is the compiler bootstrapped and released? | [Bootstrap and release](bootstrap-and-release.md) |
| What is knowingly incomplete? | [Known limitations](known-limitations.md) and [roadmap](../ROADMAP.md) |

## Change routes

Use these routes as starting points, not as permission to bypass an owning
phase:

| Change | Typical route |
| --- | --- |
| New syntax | `lexer.do` → the focused `parser-*.do` module → `ast.do` |
| New name or import rule | `resolver.do` / `analyzer.do` → `checker-symbols.do` |
| New type rule | `semantic.do` / `checker-types.do` → the focused checker module |
| New control-flow rule | `checker-statements.do` or `checker-expressions.do` → AST decoration → emitter |
| New expression lowering | `emitter-expr.do` → one focused `emitter-expr-*.do` module |
| New C++ representation | `emitter-types.do` → affected focused emitters → runtime if required |
| New package or native input | `package-manifest.do` → policy/acquisition → project emission → native planning/driver |
| New CLI behavior | `cli.do` → a pure planning module where possible → `driver.do` |

Every changed compiler module needs focused adjacent `*.test.do` coverage.
Language changes also update `spec/` and `.github/skills/doof-language/`.
Ownership or lowering changes update the vertical and horizontal maps above.
