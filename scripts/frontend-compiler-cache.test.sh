#!/bin/sh
set -eu

# Use two different compiler builds to exercise replacement at one install path.
if [ "$#" -ne 2 ]; then
  echo "usage: sh scripts/frontend-compiler-cache.test.sh <old-compiler> <new-compiler>" >&2
  exit 2
fi
repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
work_root=$(mktemp -d "${TMPDIR:-/tmp}/doof-compiler-cache.XXXXXX")
trap 'rm -rf "$work_root"' EXIT HUP INT TERM
export DOOF_STDLIB_ROOT=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
export DOOF_RUNTIME_HEADER="$repo_root/runtime/doof_runtime.h"
printf 'function main(): int => 7\n' > "$work_root/main.do"
cp "$1" "$work_root/doof"
chmod +x "$work_root/doof"
"$work_root/doof" emit "$work_root/main.do" -o "$work_root/out"
cp "$work_root/out/.doof-cache/v1/check.json" "$work_root/old-check.json"
for source in "$work_root/out/"*.cpp; do
  printf '\n// compiler-cache-retained-marker\n' >> "$source"
done
"$work_root/doof" emit "$work_root/main.do" -o "$work_root/out"
if ! grep -q compiler-cache-retained-marker "$work_root/out/"*.cpp; then
  echo "unchanged compiler did not reuse emission" >&2
  exit 1
fi
cp "$2" "$work_root/doof"
chmod +x "$work_root/doof"
"$work_root/doof" check "$work_root/main.do" -o "$work_root/out"
if cmp -s "$work_root/old-check.json" "$work_root/out/.doof-cache/v1/check.json"; then
  echo "replacement compiler reused checked state" >&2
  exit 1
fi
"$work_root/doof" emit "$work_root/main.do" -o "$work_root/out"
if grep -q compiler-cache-retained-marker "$work_root/out/"*.cpp; then
  echo "replacement compiler reused stale emission" >&2
  exit 1
fi
# Identical executable bytes retain their identity even at another path.
for source in "$work_root/out/"*.cpp; do
  printf '\n// compiler-cache-retained-marker\n' >> "$source"
done
cp "$work_root/doof" "$work_root/renamed-doof"
"$work_root/renamed-doof" emit "$work_root/main.do" -o "$work_root/out"
if ! grep -q compiler-cache-retained-marker "$work_root/out/"*.cpp; then
  echo "identical compiler copy did not reuse emission" >&2
  exit 1
fi
echo "Compiler replacement cache tests passed"
