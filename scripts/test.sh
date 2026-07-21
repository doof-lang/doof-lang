#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}

if [ ! -x "$repo_root/dist/doof" ]; then
  DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/build.sh"
fi

DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/dist/doof" test "$repo_root/src"

DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/scripts/install.test.sh" "$stdlib_root"
