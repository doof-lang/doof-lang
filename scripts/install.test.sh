#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
stdlib_root=${1:-${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}}
helper="$repo_root/scripts/install-artifacts.sh"
artifact_root="$repo_root/dist"
runtime_fixture="$repo_root/tests/release-fixtures/runtime"
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

file_mode() {
  if [ "$(uname -s)" = "Darwin" ]; then
    stat -f '%Lp' "$1"
  else
    stat -c '%a' "$1"
  fi
}

expect_failure "$helper" "$artifact_root" "" dev
grep -q 'Doof home cannot be empty' "$test_root/failure-output"
expect_failure "$helper" "$artifact_root" relative dev
grep -q 'Doof home must be an absolute path' "$test_root/failure-output"
expect_failure "$helper" "$artifact_root" / dev
grep -q 'refusing to use /' "$test_root/failure-output"
expect_failure "$helper" "$artifact_root" "$test_root/home" '../dev'
grep -q 'unsafe version name' "$test_root/failure-output"

missing_artifacts="$test_root/missing-artifacts"
mkdir -p "$missing_artifacts"
expect_failure "$helper" "$missing_artifacts" "$test_root/home" dev
grep -q 'missing executable compiler' "$test_root/failure-output"

install_fixture="$test_root/install-fixture"
mkdir -p "$install_fixture/scripts" "$install_fixture/tools" "$install_fixture/stdlib"
cp "$repo_root/install.sh" "$install_fixture/install.sh"
cp "$helper" "$install_fixture/scripts/install-artifacts.sh"
touch "$install_fixture/tools/stdlib-bundle.do"
chmod +x "$install_fixture/install.sh" "$install_fixture/scripts/install-artifacts.sh"

fake_compiler="$install_fixture/fake-doof"
printf '%s\n' \
  '#!/bin/sh' \
  'set -eu' \
  ': "${FAKE_DOOF_LOG:?}"' \
  'printf "%s\n" "$*" >> "$FAKE_DOOF_LOG"' \
  'case "${1:-}" in' \
  '  package)' \
  '    if [ "${FAKE_DOOF_PACKAGE_FAIL:-}" = 1 ]; then exit 7; fi' \
  '    artifact_root=""' \
  '    build_root=""' \
  '    while [ "$#" -gt 0 ]; do' \
  '      case "$1" in' \
  '        --distdir) artifact_root=$2; shift 2 ;;' \
  '        -o) build_root=$2; shift 2 ;;' \
  '        *) shift ;;' \
  '      esac' \
  '    done' \
  '    mkdir -p "$artifact_root" "$build_root"' \
  '    cp "$0" "$artifact_root/doof"' \
  '    chmod +x "$artifact_root/doof"' \
  '    printf runtime > "$artifact_root/doof_runtime.h"' \
  '    printf wasm-runner > "$artifact_root/doof_wasm_test_runner_apple.swift"' \
  '    touch "$build_root/reused"' \
  '    ;;' \
  '  run)' \
  '    if [ "${FAKE_DOOF_BUNDLE_FAIL:-}" = 1 ]; then exit 9; fi' \
  '    build_root=""' \
  '    output=""' \
  '    after_separator=false' \
  '    argument_index=0' \
  '    while [ "$#" -gt 0 ]; do' \
  '      if [ "$after_separator" = true ]; then' \
  '        argument_index=$((argument_index + 1))' \
  '        if [ "$argument_index" -eq 2 ]; then output=$1; fi' \
  '        shift' \
  '      else' \
  '        case "$1" in' \
  '          -o) build_root=$2; shift 2 ;;' \
  '          --) after_separator=true; shift ;;' \
  '          *) shift ;;' \
  '        esac' \
  '      fi' \
  '    done' \
  '    mkdir -p "$build_root" "$(dirname "$output")"' \
  '    printf stdlib-bundle > "$output"' \
  '    touch "$build_root/reused"' \
  '    ;;' \
  '  --help) ;;' \
  '  *) exit 64 ;;' \
  'esac' > "$fake_compiler"
chmod +x "$fake_compiler"

expect_failure env DOOF_HOME= DOOF_STDLIB_ROOT="$install_fixture/stdlib" \
  DOOF_DEV_COMPILER="$fake_compiler" FAKE_DOOF_LOG="$test_root/fake.log" \
  "$install_fixture/install.sh"
grep -q 'DOOF_HOME cannot be empty' "$test_root/failure-output"

expect_failure env DOOF_HOME=relative DOOF_STDLIB_ROOT="$install_fixture/stdlib" \
  DOOF_DEV_COMPILER="$fake_compiler" FAKE_DOOF_LOG="$test_root/fake.log" \
  "$install_fixture/install.sh"
grep -q 'DOOF_HOME must be an absolute path' "$test_root/failure-output"

expect_failure env DOOF_HOME="$test_root/no-seed-home" \
  DOOF_STDLIB_ROOT="$install_fixture/stdlib" FAKE_DOOF_LOG="$test_root/fake.log" \
  PATH=/usr/bin:/bin "$install_fixture/install.sh"
grep -q 'no seed Doof compiler found' "$test_root/failure-output"

mkdir -p "$install_fixture/dist"
cp "$fake_compiler" "$install_fixture/dist/doof"
fallback_home="$test_root/fallback-home"
env DOOF_HOME="$fallback_home" DOOF_STDLIB_ROOT="$install_fixture/stdlib" \
  FAKE_DOOF_LOG="$test_root/fake.log" PATH=/usr/bin:/bin \
  "$install_fixture/install.sh" >/dev/null
test -x "$fallback_home/bin/doof"
: > "$test_root/fake.log"

expect_failure env DOOF_HOME="$test_root/missing-stdlib-home" \
  DOOF_STDLIB_ROOT="$test_root/not-a-stdlib" DOOF_DEV_COMPILER="$fake_compiler" \
  FAKE_DOOF_LOG="$test_root/fake.log" "$install_fixture/install.sh"
grep -q 'Doof stdlib not found' "$test_root/failure-output"

failed_home="$test_root/failed-home"
mkdir -p "$failed_home/versions/dev"
printf old > "$failed_home/versions/dev/marker"
expect_failure env DOOF_HOME="$failed_home" DOOF_STDLIB_ROOT="$install_fixture/stdlib" \
  DOOF_DEV_COMPILER="$fake_compiler" FAKE_DOOF_LOG="$test_root/fake.log" \
  FAKE_DOOF_PACKAGE_FAIL=1 "$install_fixture/install.sh"
grep -q 'compiler package failed' "$test_root/failure-output"
test "$(cat "$failed_home/versions/dev/marker")" = old

expect_failure env DOOF_HOME="$failed_home" DOOF_STDLIB_ROOT="$install_fixture/stdlib" \
  DOOF_DEV_COMPILER="$fake_compiler" FAKE_DOOF_LOG="$test_root/fake.log" \
  FAKE_DOOF_BUNDLE_FAIL=1 "$install_fixture/install.sh"
grep -q 'stdlib bundle failed' "$test_root/failure-output"
test "$(cat "$failed_home/versions/dev/marker")" = old

mock_home="$test_root/mock-home"
mock_output=$(env DOOF_HOME="$mock_home" DOOF_STDLIB_ROOT="$install_fixture/stdlib" \
  DOOF_DEV_COMPILER="$fake_compiler" FAKE_DOOF_LOG="$test_root/fake.log" \
  "$install_fixture/install.sh")
printf '%s\n' "$mock_output" | grep -q "Installed development compiler: $mock_home/bin/doof"
printf '%s\n' "$mock_output" | grep -q "export PATH=\"$mock_home/bin:\$PATH\""
test -f "$install_fixture/build/dev-install/compiler/reused"
test -f "$install_fixture/build/dev-install/stdlib-bundle-tool/reused"

env DOOF_HOME="$mock_home" DOOF_STDLIB_ROOT="$install_fixture/stdlib" \
  DOOF_DEV_COMPILER="$fake_compiler" FAKE_DOOF_LOG="$test_root/fake.log" \
  "$install_fixture/install.sh" >/dev/null
test "$(grep -c '^package ' "$test_root/fake.log")" -eq 4
test "$(grep '^package ' "$test_root/fake.log" | sort -u | wc -l | tr -d ' ')" -eq 1

real_home="$test_root/real-home"
"$helper" "$artifact_root" "$real_home" dev

test -x "$real_home/versions/dev/doof"
test "$(file_mode "$real_home/versions/dev/doof")" = "755"
test "$(file_mode "$real_home/versions/dev/doof_runtime.h")" = "644"
test "$(file_mode "$real_home/versions/dev/doof_wasm_test_runner_apple.swift")" = "644"
test "$(file_mode "$real_home/versions/dev/doof-stdlib.tar")" = "644"
test -L "$real_home/current"
test "$(readlink "$real_home/current")" = "versions/dev"
test -L "$real_home/bin/doof"
test "$(readlink "$real_home/bin/doof")" = "../current/doof"
test -L "$real_home/bin/doof_runtime.h"
test "$(readlink "$real_home/bin/doof_runtime.h")" = "../current/doof_runtime.h"
test -L "$real_home/bin/doof_wasm_test_runner_apple.swift"
test "$(readlink "$real_home/bin/doof_wasm_test_runner_apple.swift")" = "../current/doof_wasm_test_runner_apple.swift"
test -L "$real_home/bin/doof-stdlib.tar"
test "$(readlink "$real_home/bin/doof-stdlib.tar")" = "../current/doof-stdlib.tar"

mkdir -p "$real_home/versions/1.0.0" "$real_home/packages"
printf released > "$real_home/versions/1.0.0/marker"
printf cached > "$real_home/packages/marker"
replacement_artifacts="$test_root/replacement-artifacts"
mkdir -p "$replacement_artifacts"
cp -R "$artifact_root/." "$replacement_artifacts/"
printf replacement-runtime > "$replacement_artifacts/doof_runtime.h"

failing_bin="$test_root/failing-bin"
mkdir -p "$failing_bin"
printf '%s\n' '#!/bin/sh' 'exit 77' > "$failing_bin/ln"
chmod +x "$failing_bin/ln"
expect_failure env PATH="$failing_bin:$PATH" \
  "$helper" "$replacement_artifacts" "$real_home" dev
cmp "$artifact_root/doof_runtime.h" "$real_home/versions/dev/doof_runtime.h"

"$helper" "$replacement_artifacts" "$real_home" dev
cmp "$replacement_artifacts/doof_runtime.h" "$real_home/versions/dev/doof_runtime.h"
test "$(cat "$real_home/versions/1.0.0/marker")" = released
test "$(cat "$real_home/packages/marker")" = cached

blocked_home="$test_root/blocked-home"
mkdir -p "$blocked_home/current"
expect_failure "$helper" "$artifact_root" "$blocked_home" dev
grep -q 'cannot replace directory' "$test_root/failure-output"
test ! -e "$blocked_home/versions/dev"

work_root="$test_root/work"
emit_root="$test_root/emitted"
mkdir -p "$work_root"
(
  cd "$work_root"
  env -u DOOF_STDLIB_ROOT "$real_home/bin/doof" emit "$runtime_fixture" -o "$emit_root"
)
cmp "$replacement_artifacts/doof_runtime.h" "$emit_root/doof_runtime.hpp"

echo "Installer workflow test passed: $real_home"
