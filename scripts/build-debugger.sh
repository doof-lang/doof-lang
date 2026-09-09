#!/bin/sh
# Build once per toolchain installation, never on doof debug's launch path.
set -eu
if [ "$#" -ne 3 ]; then
  echo 'usage: build-debugger.sh <compiler> <stdlib-root> <artifact-root>' >&2
  exit 2
fi
[ "$(uname -s)" = Darwin ] || exit 0
repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
compiler=$1
stdlib_root=$2
artifact_root=$3
output_root="$repo_root/build/debugger-app"
env DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$repo_root/tools/debugger" -o "$output_root"
test -x "$output_root/DoofDebugger.app/Contents/MacOS/DoofDebugger"
mkdir -p "$artifact_root"
rm -rf "$artifact_root/Doof Debugger.app"
cp -R "$output_root/DoofDebugger.app" "$artifact_root/Doof Debugger.app"
