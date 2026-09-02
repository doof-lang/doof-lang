#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
script="$repo_root/scripts/refresh-bootstrap.sh"
canonicalizer="$repo_root/scripts/canonicalize-bootstrap-snapshot.sh"
platform_source_preserver="$repo_root/scripts/preserve-bootstrap-platform-sources.sh"
bootstrap_compiler="$repo_root/scripts/bootstrap-compiler.sh"
test_root=$(mktemp -d "${TMPDIR:-/tmp}/doof-refresh-bootstrap-test.XXXXXX")

finish() {
  status=$?
  rm -rf "$test_root"
  exit "$status"
}
trap finish EXIT HUP INT TERM

sh -n "$script"
sh -n "$canonicalizer"
sh -n "$platform_source_preserver"
bootstrap_sources="$test_root/bootstrap-sources"
"$bootstrap_compiler" --list-sources > "$bootstrap_sources"
grep -q '^std/gzip/vendor/zlib/adler32\.c$' "$bootstrap_sources"
grep -q '^src_driver\.cpp$' "$bootstrap_sources"
if grep -Eq '_(linux|windows|ios|curl)\.(c|cc|cpp|m|mm)$' "$bootstrap_sources"; then
  echo "Expected the macOS bootstrap compiler to exclude unsupported platform sources." >&2
  exit 1
fi

compile_tasks="$test_root/compile-tasks"
"$bootstrap_compiler" --list-compile-tasks > "$compile_tasks"
grep -q "^clang$(printf '\t')std/gzip/vendor/zlib/adler32\.c$" "$compile_tasks"
grep -q "^clang++$(printf '\t')src_driver\.cpp$" "$compile_tasks"

compiler_probes="$test_root/compiler-probes"
"$bootstrap_compiler" --list-compile-tasks native.c generated.cpp platform.mm > "$compiler_probes"
grep -q "^clang$(printf '\t')native\.c$" "$compiler_probes"
grep -q "^clang++$(printf '\t')generated\.cpp$" "$compiler_probes"
grep -q "^clang++$(printf '\t')platform\.mm$" "$compiler_probes"
"$script" --help > "$test_root/help"
grep -q '^usage: .*refresh-bootstrap.sh \[--help\]$' "$test_root/help"
grep -q 'DOOF_REFRESH_MAX_GENERATIONS' "$test_root/help"
grep -q 'DOOF_REFRESH_SEED_COMPILER' "$test_root/help"
grep -q 'strict stdlib bundle preflight' "$test_root/help"
grep -q -- "--exclude='.doof-build/\*\*\*'" "$script"
grep -q '^echo "\[2/6\] Preflight the standard-library release inputs"$' "$script"
grep -q '^  if \[ -f "\$preflight_bundle" \]; then$' "$script"
grep -q 'prepared vendored sources and required licenses' "$script"

if "$script" --unknown > "$test_root/unknown" 2>&1; then
  echo "Expected refresh-bootstrap.sh to reject an unknown option." >&2
  exit 1
fi
grep -q '^usage: .*refresh-bootstrap.sh \[--help\]$' "$test_root/unknown"

if DOOF_REFRESH_MAX_GENERATIONS=1 "$script" > "$test_root/generations" 2>&1; then
  echo "Expected refresh-bootstrap.sh to reject a one-generation limit." >&2
  exit 1
fi
grep -q 'must be an integer greater than one' "$test_root/generations"

if DOOF_REFRESH_SEED_COMPILER="$test_root/missing" "$script" > "$test_root/seed" 2>&1; then
  echo "Expected refresh-bootstrap.sh to reject a non-executable seed compiler." >&2
  exit 1
fi
grep -q 'DOOF_REFRESH_SEED_COMPILER is not executable' "$test_root/seed"

fixture_root="$test_root/snapshot"
mkdir -p "$fixture_root/nested"
cat > "$fixture_root/nested/module.cpp" <<'EOF'
#include "module.hpp"
#line 7 "/src/module.do"
int answer() { return 42; }
#line 1 "<doof-generated>"
EOF
cat > "$fixture_root/nested/module.hpp" <<'EOF'
#pragma once
#line 3 "/src/module.do"
int answer();
EOF
cat > "$fixture_root/notes.txt" <<'EOF'
#line 9 "documentation-example"
EOF

"$canonicalizer" "$fixture_root"
if grep '^#line ' "$fixture_root/nested/module.cpp" "$fixture_root/nested/module.hpp" >/dev/null 2>&1; then
  echo "Expected bootstrap canonicalization to remove generated #line directives." >&2
  exit 1
fi
grep -q '^#include "module.hpp"$' "$fixture_root/nested/module.cpp"
grep -q '^int answer() { return 42; }$' "$fixture_root/nested/module.cpp"
grep -q '^#pragma once$' "$fixture_root/nested/module.hpp"
grep -q '^#line 9 "documentation-example"$' "$fixture_root/notes.txt"

platform_snapshot="$test_root/platform-snapshot"
platform_candidate="$test_root/platform-candidate"
mkdir -p "$platform_snapshot/std/http" "$platform_candidate/std/http"
printf '%s\n' apple > "$platform_snapshot/std/http/native_http_client_apple.mm"
printf '%s\n' curl > "$platform_snapshot/std/http/native_http_client_curl.cpp"
printf '%s\n' windows > "$platform_snapshot/std/http/native_http_client_windows.cpp"
printf '%s\n' neutral > "$platform_snapshot/std/http/native_http_client.cpp"
printf '%s\n' generated-curl > "$platform_candidate/std/http/native_http_client_curl.cpp"

sh "$platform_source_preserver" "$platform_snapshot" "$platform_candidate"
grep -q '^apple$' "$platform_candidate/std/http/native_http_client_apple.mm"
grep -q '^generated-curl$' "$platform_candidate/std/http/native_http_client_curl.cpp"
grep -q '^windows$' "$platform_candidate/std/http/native_http_client_windows.cpp"
test ! -e "$platform_candidate/std/http/native_http_client.cpp"

if "$canonicalizer" "$test_root/missing-snapshot" > "$test_root/canonicalizer-error" 2>&1; then
  echo "Expected bootstrap canonicalization to reject a missing snapshot root." >&2
  exit 1
fi
grep -q 'Bootstrap snapshot root is not a directory' "$test_root/canonicalizer-error"

echo "Bootstrap refresh script tests passed"
