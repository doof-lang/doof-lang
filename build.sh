#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
release_build=false
case "${1:-}" in
  --release) release_build=true ;;
  "") ;;
  *) echo "usage: ./build.sh [--release]" >&2; exit 2 ;;
esac
if [ "$#" -gt 1 ]; then
  echo "usage: ./build.sh [--release]" >&2
  exit 2
fi
b5_root="$repo_root/build/b5"
b6_root="$repo_root/build/b6"
stdlib_bundle="$repo_root/build/doof-stdlib.tar"
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
  echo "[$step_number/6] $step_name"
  "$@"
  elapsed=$(( $(date +%s) - started_at ))
  echo "[$step_number/6] Done: $step_name (${elapsed}s)"
}

if [ ! -d "$stdlib_root" ]; then
  echo "Doof stdlib not found at $stdlib_root" >&2
  echo "Set DOOF_STDLIB_ROOT to the directory containing std package folders." >&2
  exit 1
fi

host_system=$(uname -s)
case "$host_system" in
  Darwin)
    bootstrap_driver="$repo_root/scripts/bootstrap-compiler.sh"
    stage0="$repo_root/build/bootstrap-stage0/doof"
    stdlib_bundle_targets="ios-device,ios-simulator,macos,wasm"
    ;;
  Linux)
    bootstrap_driver="$repo_root/scripts/bootstrap-compiler-linux.sh"
    stage0="$repo_root/build/bootstrap-stage0-linux/doof"
    stdlib_bundle_targets="linux,wasm"
    ;;
  *)
    echo "Unsupported build host: $host_system" >&2
    echo "Use macOS arm64, Linux, or scripts/bootstrap-compiler.ps1 on Windows." >&2
    exit 1
    ;;
esac

run_step "Compile the checked-in bootstrap snapshot" \
  "$bootstrap_driver"

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

build_final_stdlib_bundle() {
  rm -f "$stdlib_bundle"
  rm -rf "$repo_root/build/stdlib-bundle-tool"
  DOOF_STDLIB_ROOT="$stdlib_root" "$b6_root/doof" run "$repo_root/tools/stdlib-bundle.do" \
    -o "$repo_root/build/stdlib-bundle-tool" -- \
    "$stdlib_root" "$stdlib_bundle" "$stdlib_bundle_targets"
  test -f "$stdlib_bundle"
}
run_step "Build the final stdlib resource with B6" build_final_stdlib_bundle

publish_optimized() {
  release_root="$repo_root/build/compiler-release"
  DOOF_STDLIB_ROOT="$stdlib_root" "$b6_root/doof" package "$repo_root" \
    -o "$release_root" --distdir "$repo_root/dist"
  test -x "$repo_root/dist/doof"
  cp "$stdlib_bundle" "$repo_root/dist/doof-stdlib.tar"
}
run_step "Build and publish the optimized compiler to dist/" publish_optimized

echo "Verified compiler: $repo_root/dist/doof"
echo "Bundled standard library: $repo_root/dist/doof-stdlib.tar"
