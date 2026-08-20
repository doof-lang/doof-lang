#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
script="$repo_root/scripts/refresh-bootstrap.sh"
test_root=$(mktemp -d "${TMPDIR:-/tmp}/doof-refresh-bootstrap-test.XXXXXX")

finish() {
  status=$?
  rm -rf "$test_root"
  exit "$status"
}
trap finish EXIT HUP INT TERM

sh -n "$script"
"$script" --help > "$test_root/help"
grep -q '^usage: .*refresh-bootstrap.sh \[--help\]$' "$test_root/help"
grep -q 'DOOF_REFRESH_MAX_GENERATIONS' "$test_root/help"
grep -q 'DOOF_REFRESH_SEED_COMPILER' "$test_root/help"

if "$script" --unknown > "$test_root/unknown" 2>&1; then
  echo "Expected refresh-bootstrap.sh to reject an unknown option." >&2
  exit 1
fi
grep -q '^usage: .*refresh-bootstrap.sh \[--help\]$' "$test_root/unknown"

if DOOF_REFRESH_MAX_GENERATIONS=1 "$script" > "$test_root/generations" 2>&1; then
  echo "Expected refresh-bootstrap.sh to reject a one-generation limit." >&2
  exit 1
fi
grep -q 'must be an integer greater than one' "$test_root/generations"

if DOOF_REFRESH_SEED_COMPILER="$test_root/missing" "$script" > "$test_root/seed" 2>&1; then
  echo "Expected refresh-bootstrap.sh to reject a non-executable seed compiler." >&2
  exit 1
fi
grep -q 'DOOF_REFRESH_SEED_COMPILER is not executable' "$test_root/seed"

echo "Bootstrap refresh script tests passed"
