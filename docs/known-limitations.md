# Known Limitations

The official compiler is intentionally shipping before every former parity
goal is complete.

- Clean bootstrap is supported on macOS arm64 and Windows x64; Windows still
  uses separate PowerShell bootstrap and developer-environment commands.
- The experimental Linux stage-0 driver is not yet a clean-bootstrap or CI
  release gate; the shared snapshot and target-native dependencies still need
  a verified Linux refresh.
- Compiler development requires a mutable stdlib checkout through
  `DOOF_STDLIB_ROOT` or `../doof-stdlib`.
- Third-party source acquisition and vendoring are intentionally outside the
  compiler; projects must prepare those inputs themselves.
- Diagnostic behavior has focused tests but no exhaustive invalid-program
  compatibility corpus.
- Some JSON union/interface cases, interface reflection, recorded mocks,
  timeouts, and iOS embedded-library packaging remain incomplete.

See [ROADMAP.md](../ROADMAP.md) for acceptance-oriented follow-up work.
