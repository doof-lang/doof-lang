#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
test_root=$(mktemp -d "${TMPDIR:-/tmp}/doof-build-dispatch-test.XXXXXX")

finish() {
  status=$?
  rm -rf "$test_root"
  exit "$status"
}
trap finish EXIT HUP INT TERM

fixture_repo="$test_root/repo"
fixture_stdlib="$test_root/doof-stdlib"
fixture_bin="$test_root/bin"
mkdir -p "$fixture_repo/scripts" "$fixture_stdlib" "$fixture_bin"
cp "$repo_root/build.sh" "$fixture_repo/build.sh"

printf '%s\n' '#!/bin/sh' 'printf "%s\n" "$DOOF_TEST_UNAME"' > "$fixture_bin/uname"
printf '%s\n' '#!/bin/sh' 'printf "%s\n" macos > "$DOOF_DISPATCH_LOG"' 'exit 23' > "$fixture_repo/scripts/bootstrap-compiler.sh"
printf '%s\n' '#!/bin/sh' 'printf "%s\n" linux > "$DOOF_DISPATCH_LOG"' 'exit 23' > "$fixture_repo/scripts/bootstrap-compiler-linux.sh"
chmod +x "$fixture_bin/uname" "$fixture_repo/scripts/bootstrap-compiler.sh" "$fixture_repo/scripts/bootstrap-compiler-linux.sh"

assert_dispatch() {
  host=$1
  expected=$2
  log="$test_root/$host.log"
  if PATH="$fixture_bin:$PATH" DOOF_TEST_UNAME="$host" DOOF_DISPATCH_LOG="$log" DOOF_STDLIB_ROOT="$fixture_stdlib" \
      sh "$fixture_repo/build.sh" > "$test_root/$host.out" 2>&1; then
    echo "Expected the stub $host bootstrap driver to stop the build." >&2
    exit 1
  fi
  test "$(cat "$log")" = "$expected"
}

assert_dispatch Darwin macos
assert_dispatch Linux linux

unsupported_log="$test_root/unsupported.log"
if PATH="$fixture_bin:$PATH" DOOF_TEST_UNAME=FreeBSD DOOF_DISPATCH_LOG="$unsupported_log" DOOF_STDLIB_ROOT="$fixture_stdlib" \
    sh "$fixture_repo/build.sh" > "$test_root/unsupported.out" 2>&1; then
  echo "Expected build.sh to reject an unsupported host." >&2
  exit 1
fi
grep -q '^Unsupported build host: FreeBSD$' "$test_root/unsupported.out"
test ! -e "$unsupported_log"

echo "Build host dispatch tests passed"
