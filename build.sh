#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
b5_root="$repo_root/build/b5"
b6_root="$repo_root/build/b6"
step_number=0
step_name="startup checks"

finish() {
  status=$?
  if [ "$status" -ne 0 ]; then
    echo "Build failed during: $step_name" >&2
  fi
  exit "$status"
}
trap finish EXIT

run_step() {
  step_number=$((step_number + 1))
  step_name=$1
  shift
  started_at=$(date +%s)
  echo "[$step_number/5] $step_name"
  "$@"
  elapsed=$(( $(date +%s) - started_at ))
  echo "[$step_number/5] Done: $step_name (${elapsed}s)"
}

if [ ! -d "$stdlib_root" ]; then
  echo "Doof stdlib not found at $stdlib_root" >&2
  echo "Set DOOF_STDLIB_ROOT to the directory containing std package folders." >&2
  exit 1
fi

run_step "Compile the checked-in bootstrap snapshot" \
  "$repo_root/scripts/bootstrap-compiler.sh"
stage0="$repo_root/build/bootstrap-stage0/doof"

rm -rf "$b5_root" "$b6_root" "$repo_root/dist"
mkdir -p "$b5_root" "$b6_root" "$repo_root/dist"

build_b5() {
  DOOF_STDLIB_ROOT="$stdlib_root" "$stage0" build "$repo_root" -o "$b5_root"
  test -x "$b5_root/doof"
}
run_step "Build B5 with the bootstrap compiler" build_b5

build_b6() {
  DOOF_STDLIB_ROOT="$stdlib_root" "$b5_root/doof" build "$repo_root" -o "$b6_root"
  test -x "$b6_root/doof"
}
run_step "Build B6 with B5" build_b6

run_step "Verify the B5/B6 fixed point" \
  "$repo_root/scripts/compare-generated.sh" "$b5_root" "$b6_root"

publish() {
  cp "$b6_root/doof" "$repo_root/dist/doof"
  cp "$repo_root/runtime/doof_runtime.h" "$repo_root/dist/doof_runtime.h"
  cp "$repo_root/resources/std-catalog.json" "$repo_root/dist/std-catalog.json"
}
run_step "Publish the verified compiler to dist/" publish

echo "Verified compiler: $repo_root/dist/doof"
