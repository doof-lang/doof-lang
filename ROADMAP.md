# Compiler Roadmap

Acceptance-oriented follow-up work for the compiler. Current user-visible gaps
are summarized in [known limitations](docs/known-limitations.md); proposed
language features are in
[proposed language feature designs](docs/proposed-language-feature-designs.md).

## Packages and builds

- Complete local and remote Doof dependency selection and cache acquisition.
- Let compiler development use the bundled standard library without a mutable
  `DOOF_STDLIB_ROOT` or `../doof-stdlib` checkout.
- Emit stable, versioned `doof-build.json` and provenance handoff documents for
  external build consumers.
- Grow an invalid-program corpus that locks diagnostic categories, spans,
  recovery, and emission suppression.
- Version the runtime/support-artifact contract and record content hashes in
  release provenance.

## Language and tooling breadth

- Finish interface-qualified reflection and the remaining
  collection/default-inference cases.
- Add configurable run/test timeouts.
- Add incremental native fingerprints and discovered-header dependencies.
- Add the remaining CLI convenience and instrumentation options.

## Platforms

- Add Linux source-snapshot rebuilding and native Linux `doof observe`
  acceptance.
- Make Windows verification a required release gate, with Windows release
  fixtures, before claiming Windows support. Windows x64 archives are
  currently published only when the optional remote build is configured.
- Complete iOS embedded-library packaging and signing-order verification.
- Support a guest filesystem in the Wasm test host.
