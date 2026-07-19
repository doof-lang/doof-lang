# Known Limitations

The official compiler is intentionally shipping before every former parity
goal is complete.

- Clean bootstrap is currently supported only on macOS arm64.
- Compiler development requires a mutable stdlib checkout through
  `DOOF_STDLIB_ROOT` or `../doof-stdlib`.
- External build handoff/provenance contracts are not yet complete for every
  package and target combination.
- Diagnostic behavior has focused tests but no exhaustive invalid-program
  compatibility corpus.
- Some JSON union/interface cases, interface reflection, recorded mocks,
  timeouts, incremental builds, Windows/MSVC support, and iOS embedded-library
  packaging remain incomplete.

See [ROADMAP.md](../ROADMAP.md) for acceptance-oriented follow-up work.

