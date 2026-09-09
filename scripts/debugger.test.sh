#!/bin/sh
# Native macOS launch contract + LLDB-DAP integration. No GUI needed.
set -eu
repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
[ "$(uname -s)" = Darwin ] || exit 0
compiler=${1:-"$repo_root/dist/doof"}
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
work="$repo_root/build/debugger-integration"
mkdir -p "$work/Capture.app/Contents/MacOS"
cat > "$work/Capture.app/Contents/MacOS/DoofDebugger" <<'CAPTURE'
#!/bin/sh
set -eu
cp "$1" "$DOOF_DEBUG_TEST_LAUNCH"
CAPTURE
chmod +x "$work/Capture.app/Contents/MacOS/DoofDebugger"
export DOOF_DEBUG_TEST_LAUNCH="$work/launch.json"
export DOOF_DEBUG_FIXTURE_ENV=debug-environment
export DOOF_STDLIB_ROOT="$stdlib_root"
DOOF_DEBUGGER_APP="$work/Capture.app" "$compiler" debug "$repo_root/tests/debugger-fixture" -o "$work/target" -- 'argument space' '工具'
"$compiler" test "$repo_root/tools/debugger" --filter testRealLldbSession
export DOOF_DEBUG_TEST_LAUNCH="$work/panic-launch.json"
export DOOF_DEBUG_PANIC_TEST_LAUNCH="$DOOF_DEBUG_TEST_LAUNCH"
DOOF_DEBUGGER_APP="$work/Capture.app" "$compiler" debug "$repo_root/tests/debugger-panic-fixture" -o "$work/panic-target"
"$compiler" test "$repo_root/tools/debugger" --filter testRealLldbPanic

# Exercise the external-client route without any installed native debugger app.
export DOOF_DEBUG_DRIVER_COMPILER="$compiler"
export DOOF_DEBUG_DRIVER_FIXTURE="$repo_root/tests/debugger-fixture"
export DOOF_DEBUG_DRIVER_DESCRIPTOR="$work/external 工具 launch.json"
export DOOF_DEBUG_DRIVER_OUTPUT="$work/external-target"
DOOF_DEBUGGER_APP="$work/does-not-exist.app" "$compiler" test "$repo_root/src" --filter testDebugDriverExternalLaunchIntegration
