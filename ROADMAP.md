# Compiler Roadmap

The Doof implementation is the official compiler. These gaps are tracked work,
not a dependency on the retired implementation.

## Replacement follow-through

- Complete local and remote Doof dependency selection, cache acquisition, and
  standard-package fallback without a required `DOOF_STDLIB_ROOT` override.
- Emit stable, versioned `doof-build.json` and provenance handoff documents for
  external build consumers.
- Grow an invalid-program corpus that locks diagnostic categories, spans,
  recovery, and emission suppression.
- Version the runtime/support-artifact contract and record content hashes in
  release provenance.

## Language and tooling breadth

- Finish named-union JSON dispatch, interface-qualified reflection, and the
  remaining collection/default-inference cases.
- Complete recorded mock functions/classes and configurable run/test timeouts.
- Add incremental native fingerprints and discovered-header dependencies.
- Add the remaining CLI convenience and instrumentation options.

## Platforms

- The checked-in bootstrap currently supports macOS arm64 only.
- Add a verified Linux bootstrap snapshot and CI release gate before claiming
  Linux clean-bootstrap support.
- Add MSVC planning, discovery, and Windows release fixtures before claiming
  Windows support.
- Complete iOS embedded-library packaging and signing-order verification.

