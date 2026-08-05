# Known Limitations

The official compiler is intentionally shipping before every former parity
goal is complete.

- Clean bootstrap is supported on macOS arm64 and Windows x64; Windows still
  uses separate PowerShell bootstrap and developer-environment commands.
- The experimental Alpine bootstrap test compiles the complete 96-file
  neutral/Linux source graph, but linking is blocked until `std/http` and its
  WebSocket support provide Linux native implementations.
- Compiler development requires a mutable stdlib checkout through
  `DOOF_STDLIB_ROOT` or `../doof-stdlib`.
- External build handoff/provenance contracts are not yet complete for every
  package and target combination.
- Diagnostic behavior has focused tests but no exhaustive invalid-program
  compatibility corpus.
- Some JSON union/interface cases, interface reflection, recorded mocks,
  timeouts, and iOS embedded-library packaging remain incomplete.

See [ROADMAP.md](../ROADMAP.md) for acceptance-oriented follow-up work.
