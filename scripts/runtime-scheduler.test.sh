#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
test_root=$(mktemp -d "${TMPDIR:-/tmp}/doof-runtime-scheduler-test.XXXXXX")

finish() {
  status=$?
  rm -rf "$test_root"
  exit "$status"
}
trap finish EXIT

c++ -std=c++17 -O0 -pthread \
  "$repo_root/runtime/doof_runtime.test.cpp" \
  -o "$test_root/runtime-scheduler-test"

for mode in limit nested first-completed actor actor-waits failures application release priority configuration collections nulls string-builder string-padding; do
  "$test_root/runtime-scheduler-test" "$mode"
done

echo "Runtime scheduler tests passed"
