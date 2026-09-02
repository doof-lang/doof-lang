#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}

run_step() {
  label=$1
  shift
  echo "[tests] $label"
  if "$@"; then
    return 0
  else
    status=$?
    echo "[tests] FAILED: $label" >&2
    return "$status"
  fi
}

if [ ! -x "$repo_root/dist/doof" ]; then
  run_step "Build the compiler test prerequisite" \
    env DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/build.sh"
fi

run_step "1/5 Compiler unit and component tests" \
  env DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/dist/doof" test "$repo_root/src"
run_step "2/5 Build host dispatch tests" sh "$repo_root/scripts/build.test.sh"
run_step "3/5 Runtime scheduler tests" "$repo_root/scripts/runtime-scheduler.test.sh"
run_step "4/5 Bootstrap refresh script tests" "$repo_root/scripts/refresh-bootstrap.test.sh"
run_step "5/5 Installer layout tests" \
  env DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/scripts/install.test.sh" "$stdlib_root"
