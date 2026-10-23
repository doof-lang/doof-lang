# Known Limitations

These are the known, intentional gaps in the current compiler.

- Published toolchains support macOS arm64 and static Linux arm64/x64 musl.
  Standalone source-snapshot builds support macOS arm64 only. A Windows x64
  archive is produced only when optional remote Windows verification is
  configured. Other native compiler target backends remain maintained.
- Compiler development requires a mutable stdlib checkout through
  `DOOF_STDLIB_ROOT` or `../doof-stdlib`.
- Third-party source acquisition and vendoring are intentionally outside the
  compiler; projects must prepare those inputs themselves.
- Diagnostic behavior has focused tests but no exhaustive invalid-program
  compatibility corpus.
- Interface-qualified reflection, configurable run/test timeouts, and iOS
  embedded-library packaging remain incomplete.
- `mock import` substitutes whole modules; there are no mock function or class
  declarations and no recorded calls.
- The Wasm test host supports arguments, an empty environment, and
  stdout/stderr, but no guest filesystem.
- `doof observe` has native acceptance coverage on macOS only.

See [ROADMAP.md](../ROADMAP.md) for acceptance-oriented follow-up work.
