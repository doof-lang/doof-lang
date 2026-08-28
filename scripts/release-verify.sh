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
module_initialization_fixture="$fixtures_root/module-initialization"
interactive_run_fixture="$fixtures_root/interactive-run"
command_output_fixture="$fixtures_root/command-output"
script_fixture="$fixtures_root/manifestless-script/script.do"
wasm_fixture="$fixtures_root/manifestless-wasm/library.do"
wasm_test_fixture="$fixtures_root/wasm-test-runner"

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

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$module_initialization_fixture" -o "$verify_root/module-initialization"
run_binary "$release_root" "$verify_root/module-initialization/doof-release-module-initialization"

python3 "$repo_root/scripts/interactive-run.test.py" "$compiler" "$interactive_run_fixture" "$stdlib_root"
"$repo_root/scripts/command-output.test.sh" \
  "$compiler" "$command_output_fixture" "$test_fixture" "$stdlib_root"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$script_fixture" -o "$verify_root/manifestless-script"
run_binary "$release_root" "$verify_root/manifestless-script/doof"

DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" emit "$wasm_fixture" --target wasm -o "$verify_root/manifestless-wasm-emit"
grep -q "doof_export_add" "$verify_root/manifestless-wasm-emit/doof_wasm.cpp"
if command -v em++ >/dev/null 2>&1; then
  DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$wasm_fixture" --target wasm -o "$verify_root/manifestless-wasm"
  test -f "$verify_root/manifestless-wasm/doof.wasm"
  if test "$(uname -s)" = "Darwin" && xcrun --find swiftc >/dev/null 2>&1; then
    DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" test "$wasm_test_fixture" -o "$verify_root/wasm-test-runner"
  fi
fi

platform_fixture="$fixtures_root/platform-framework"
DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$platform_fixture" -o "$verify_root/platform-framework"
run_binary "$release_root" "$verify_root/platform-framework/doof-release-platform-framework"

ios_fixture="$fixtures_root/ios-app"
DOOF_STDLIB_ROOT="$stdlib_root" "$compiler" build "$ios_fixture" \
  -o "$verify_root/ios-app" --ios-destination simulator
test -x "$verify_root/ios-app/DoofCompilerIOS.app/DoofCompilerIOS"
test -f "$verify_root/ios-app/DoofCompilerIOS.app/Info.plist"

echo "Release gate passed: $release_root"
