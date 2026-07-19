# Bootstrap and Release

The repository is bootstrapped from a reviewed generated-C++ snapshot rather
than another compiler implementation or a committed executable.

`./build.sh` performs three compiler generations:

1. Apple Clang compiles `bootstrap/macos-arm64/generated/` into stage 0.
2. Stage 0 compiles the current Doof sources into B5.
3. B5 compiles the same graph into B6.

The gate compares every generated C/C++/Objective-C++ header and source from B5
and B6 byte-for-byte. Only a matching B6 is copied to `dist/doof`.

Bootstrap snapshots are source-only and must not contain binaries, objects,
PCH files, build databases, or absolute developer paths. Refresh them only
from a verified Doof compiler using the final repository layout, then
run the complete release gate and review the generated diff.

`./scripts/release.sh` adds compiler coverage and CLI/native/resource/package
fixtures, plus macOS framework and iOS simulator acceptance checks. Release
artifacts and all mutable state remain below ignored `build/` and `dist/`.

The first supported clean-bootstrap host is macOS arm64 with Xcode Command Line
Tools. `DOOF_STDLIB_ROOT` or adjacent `../doof-stdlib` package checkouts are
currently required when rebuilding or testing source.

