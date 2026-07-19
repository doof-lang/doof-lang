#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}

DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/build.sh"
DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/scripts/release-verify.sh"
