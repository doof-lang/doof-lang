#!/bin/sh
set -eu

if [ "$#" -ne 4 ]; then
  echo "usage: $0 COMPILER COMMAND_FIXTURE TEST_FIXTURE STDLIB_ROOT" >&2
  exit 2
fi

compiler=$1
command_fixture=$2
test_fixture=$3
stdlib_root=$4
output_root=$(mktemp -d "${TMPDIR:-/tmp}/doof-command-output.XXXXXX")
trap 'rm -rf "$output_root"' EXIT

assert_contains() {
  value=$1
  expected=$2
  case "$value" in
    *"$expected"*) ;;
    *)
      echo "expected output to contain: $expected" >&2
      echo "$value" >&2
      exit 1
      ;;
  esac
}

assert_not_contains() {
  value=$1
  unexpected=$2
  case "$value" in
    *"$unexpected"*)
      echo "expected output not to contain: $unexpected" >&2
      echo "$value" >&2
      exit 1
      ;;
    *) ;;
  esac
}

run_fixture="$output_root/run-fixture"
test_run_fixture="$output_root/test-fixture"
cp -R "$command_fixture" "$run_fixture"
cp -R "$test_fixture" "$test_run_fixture"
rm -rf "$test_run_fixture/build"

run_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" run "$run_fixture" -o "$output_root/run-build" 2>&1)
if [ "$run_output" != "program-output 7" ]; then
  echo "successful doof run included compiler output" >&2
  echo "$run_output" >&2
  exit 1
fi

build_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$run_fixture" -o "$output_root/build" 2>&1)
assert_contains "$build_output" "Compiling "
warm_build_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$run_fixture" -o "$output_root/build" 2>&1)
if [ -n "$warm_build_output" ]; then
  echo "warm doof build unexpectedly reported compilation" >&2
  echo "$warm_build_output" >&2
  exit 1
fi

package_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" package "$run_fixture" -o "$output_root/package" 2>&1)
assert_contains "$package_output" "Compiling "

cp "$run_fixture/native-failure.hpp" "$run_fixture/native.hpp"
set +e
failed_run_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" run "$run_fixture" -o "$output_root/run-build" 2>&1)
failed_run_status=$?
set -e
if [ "$failed_run_status" -eq 0 ]; then
  echo "native compilation failure unexpectedly launched doof run" >&2
  exit 1
fi
assert_contains "$failed_run_output" "expected native compilation failure"
assert_not_contains "$failed_run_output" "program-output 7"

cp "$command_fixture/native.hpp" "$run_fixture/native.hpp"
cp "$run_fixture/main-frontend-failure.do.txt" "$run_fixture/main.do"
set +e
frontend_failure_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" run "$run_fixture" -o "$output_root/run-build" 2>&1)
frontend_failure_status=$?
set -e
if [ "$frontend_failure_status" -eq 0 ]; then
  echo "frontend compilation failure unexpectedly launched doof run" >&2
  exit 1
fi
assert_contains "$frontend_failure_output" "missingName"
assert_not_contains "$frontend_failure_output" "program-output should not run"

first_test_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$test_run_fixture" 2>&1)
assert_contains "$first_test_output" "Compiling "
warm_test_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$test_run_fixture" 2>&1)
assert_not_contains "$warm_test_output" "Compiling "
filtered_test_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$test_run_fixture" --filter testAddsValues 2>&1)
assert_not_contains "$filtered_test_output" "Compiling "
assert_contains "$filtered_test_output" "Testing 1 test"
assert_contains "$filtered_test_output" "Tests finished: 1 passed, 0 failed"
cp "$test_run_fixture/math.test.changed" "$test_run_fixture/math.test.do"
changed_test_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$test_run_fixture" 2>&1)
assert_contains "$changed_test_output" "Compiling 1 file"
assert_contains "$changed_test_output" "1/1"
assert_not_contains "$changed_test_output" "PASS "

cp "$test_run_fixture/math.test.failure" "$test_run_fixture/math.test.do"
set +e
failed_test_output=$(DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$test_run_fixture" 2>&1)
failed_test_status=$?
set -e
if [ "$failed_test_status" -eq 0 ]; then
  echo "failing test run unexpectedly succeeded" >&2
  exit 1
fi
assert_contains "$failed_test_output" "failure-context"
assert_contains "$failed_test_output" "FAIL math.test.do::testReportsFailure"
assert_not_contains "$failed_test_output" "PASS "

echo "Command output policy test passed"
