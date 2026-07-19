#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
release_root="$repo_root/build/release-gate"
fixtures_root="$release_root/fixtures"
verify_root="$release_root/verify"
compiler="$repo_root/dist/doof"

run_binary() {
  directory=$1
  binary=$2
  (cd "$directory" && "$binary")
}

test -x "$compiler"
rm -rf "$release_root"
mkdir -p "$fixtures_root" "$verify_root" "$release_root/coverage"
cp -R "$repo_root/tests/release-fixtures/." "$fixtures_root/"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$repo_root/src" \
  --coverage --coverage-output "$release_root/coverage/compiler.json"

runtime_fixture="$fixtures_root/runtime"
native_fixture="$fixtures_root/native-interop"
stdlib_fixture="$fixtures_root/stdlib"
pkg_fixture="$fixtures_root/pkg-config"
test_fixture="$fixtures_root/test-runner"
local_fixture="$fixtures_root/local-dependency"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" check "$runtime_fixture"
DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" emit "$runtime_fixture" -o "$verify_root/emit"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$native_fixture" -o "$verify_root/native"
run_binary "$release_root" "$verify_root/native/doof-release-native-interop"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$stdlib_fixture" -o "$verify_root/stdlib"
run_binary "$release_root" "$verify_root/stdlib/doof-release-stdlib"

PKG_CONFIG_PATH="$pkg_fixture/pkgconfig" DOOF_STDLIB_ROOT="$stdlib_root" \
  "$compiler" build "$pkg_fixture" -o "$verify_root/pkg-config"
run_binary "$release_root" "$verify_root/pkg-config/doof-release-pkg-config"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$test_fixture" --list
DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$test_fixture" \
  --coverage --coverage-output "$release_root/coverage/fixture.json"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" package "$runtime_fixture" -o "$verify_root/runtime-package"
run_binary "$release_root" "$runtime_fixture/dist/doof-release-runtime"
test -f "$runtime_fixture/dist/release-resource.txt"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" package "$local_fixture" -o "$verify_root/local-package"
run_binary "$release_root" "$local_fixture/dist/doof-release-local-dependency"

platform_fixture="$fixtures_root/platform-framework"
DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$platform_fixture" -o "$verify_root/platform-framework"
run_binary "$release_root" "$verify_root/platform-framework/doof-release-platform-framework"

ios_fixture="$fixtures_root/ios-app"
DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$ios_fixture" \
  -o "$verify_root/ios-app" --ios-destination simulator
test -x "$verify_root/ios-app/DoofCompilerIOS.app/DoofCompilerIOS"
test -f "$verify_root/ios-app/DoofCompilerIOS.app/Info.plist"

echo "Release gate passed: $release_root"
