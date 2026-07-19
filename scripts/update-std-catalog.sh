#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
compiler="$repo_root/dist/doof"
version=$(sed -n 's/.*"version"[[:space:]]*:[[:space:]]*"\([^"]*\)".*/\1/p' "$repo_root/doof.json" | head -n 1)

if [ ! -x "$compiler" ]; then
  DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/build.sh"
fi

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" run "$repo_root/tools/update-std-catalog.do" -- \
  "$stdlib_root" "$repo_root/resources/std-catalog.json" "$version"

