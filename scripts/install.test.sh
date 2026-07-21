#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
stdlib_root=${1:-${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}}
helper="$repo_root/scripts/install-artifacts.sh"
artifact_root="$repo_root/dist"
fixture="$repo_root/tests/release-fixtures/runtime"
test_root=$(mktemp -d "${TMPDIR:-/tmp}/doof-install-test.XXXXXX")

finish() {
  status=$?
  rm -rf "$test_root"
  exit "$status"
}
trap finish EXIT

expect_failure() {
  if "$@" >"$test_root/failure-output" 2>&1; then
    echo "Expected command to fail: $*" >&2
    exit 1
  fi
}

expect_failure "$repo_root/install.sh" --prefix ""
expect_failure "$repo_root/install.sh" --prefix relative
expect_failure "$repo_root/install.sh" --prefix /
expect_failure "$repo_root/install.sh" --prefix

prefix="$test_root/prefix"
"$helper" "$artifact_root" "$prefix"

test -x "$prefix/libexec/doof/doof"
test "$(stat -f '%Lp' "$prefix/libexec/doof/doof")" = "755"
test "$(stat -f '%Lp' "$prefix/libexec/doof/doof_runtime.h")" = "644"
test "$(stat -f '%Lp' "$prefix/libexec/doof/std-catalog.json")" = "644"
test -L "$prefix/bin/doof"
test "$(readlink "$prefix/bin/doof")" = "../libexec/doof/doof"
test -L "$prefix/bin/doof_runtime.h"
test "$(readlink "$prefix/bin/doof_runtime.h")" = "../libexec/doof/doof_runtime.h"
test -L "$prefix/bin/std-catalog.json"
test "$(readlink "$prefix/bin/std-catalog.json")" = "../libexec/doof/std-catalog.json"

unlink "$prefix/bin/doof"
touch "$prefix/bin/doof"
"$helper" "$artifact_root" "$prefix"
test -L "$prefix/bin/doof"

blocked_prefix="$test_root/blocked"
mkdir -p "$blocked_prefix/bin/doof"
expect_failure "$helper" "$artifact_root" "$blocked_prefix"
if ! grep -q "cannot replace directory" "$test_root/failure-output"; then
  echo "Directory conflict did not produce an actionable diagnostic" >&2
  exit 1
fi

work_root="$test_root/work"
emit_root="$test_root/emitted"
mkdir -p "$work_root"
(
  cd "$work_root"
  DOOF_STDLIB_ROOT="$stdlib_root" "$prefix/bin/doof" emit "$fixture" -o "$emit_root"
)
cmp "$artifact_root/doof_runtime.h" "$emit_root/doof_runtime.hpp"

echo "Installer layout test passed: $prefix"
