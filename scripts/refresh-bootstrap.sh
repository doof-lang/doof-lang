#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
refresh_root="$repo_root/build/bootstrap-refresh"
max_generations=${DOOF_REFRESH_MAX_GENERATIONS:-6}
seed_compiler=${DOOF_REFRESH_SEED_COMPILER:-}

usage() {
  echo "usage: $0 [--help]"
  echo
  echo "Build to a verified fixed point, refresh the source-only bootstrap snapshot,"
  echo "and run the complete release gate before and after the snapshot update."
  echo
  echo "environment:"
  echo "  DOOF_STDLIB_ROOT              standard-library package root"
  echo "  DOOF_REFRESH_MAX_GENERATIONS  convergence limit (default: 6)"
  echo "  DOOF_REFRESH_SEED_COMPILER    explicit compiler for self-hosting surface transitions"
}

case "${1:-}" in
  --help|-h)
    usage
    exit 0
    ;;
  "")
    ;;
  *)
    usage >&2
    exit 2
    ;;
esac
if [ "$#" -gt 1 ]; then
  usage >&2
  exit 2
fi

case "$max_generations" in
  ''|*[!0-9]*|0|1)
    echo "DOOF_REFRESH_MAX_GENERATIONS must be an integer greater than one (got '$max_generations')." >&2
    exit 2
    ;;
esac

if [ ! -d "$stdlib_root" ]; then
  echo "Doof stdlib not found at $stdlib_root" >&2
  echo "Set DOOF_STDLIB_ROOT to the directory containing std package folders." >&2
  exit 1
fi
if [ -d "$repo_root/bootstrap/generated" ]; then
  snapshot_root="$repo_root/bootstrap/generated"
else
  snapshot_root="$repo_root/bootstrap/macos-arm64/generated"
fi
if [ ! -d "$snapshot_root" ]; then
  echo "Missing bootstrap snapshot: $snapshot_root" >&2
  exit 1
fi
if ! command -v rsync >/dev/null 2>&1; then
  echo "Bootstrap refresh requires rsync." >&2
  exit 1
fi

rollback_snapshot=false
snapshot_backup="$refresh_root/original-snapshot"

finish() {
  status=$?
  trap - EXIT HUP INT TERM
  if [ "$status" -ne 0 ] && [ "$rollback_snapshot" = true ]; then
    echo "Refresh failed; restoring the original bootstrap snapshot." >&2
    rsync -a --delete "$snapshot_backup/" "$snapshot_root/"
  fi
  exit "$status"
}
trap finish EXIT HUP INT TERM

if [ -n "$seed_compiler" ]; then
  if [ ! -x "$seed_compiler" ]; then
    echo "DOOF_REFRESH_SEED_COMPILER is not executable: $seed_compiler" >&2
    exit 1
  fi
  echo "[1/5] Use the explicit self-hosting transition seed"
  stage_compiler="$seed_compiler"
else
  echo "[1/5] Compile the checked-in bootstrap snapshot"
  "$repo_root/scripts/bootstrap-compiler.sh"
  stage_compiler="$repo_root/build/bootstrap-stage0/doof"
  test -x "$stage_compiler"
fi

rm -rf "$refresh_root"
mkdir -p "$refresh_root"

echo "[2/5] Advance compiler generations to a fixed point"
generation=1
previous_root=""
fixed_root=""
while [ "$generation" -le "$max_generations" ]; do
  generation_root="$refresh_root/generation-$generation"
  echo "  Building generation $generation..."
  DOOF_STDLIB_ROOT="$stdlib_root" "$stage_compiler" build "$repo_root" -o "$generation_root"
  test -x "$generation_root/doof"

  if [ -n "$previous_root" ]; then
    if "$repo_root/scripts/compare-generated.sh" "$previous_root" "$generation_root"; then
      fixed_root="$generation_root"
      echo "  Fixed point reached at generations $((generation - 1))/$generation."
      break
    fi
  fi

  previous_root="$generation_root"
  stage_compiler="$generation_root/doof"
  generation=$((generation + 1))
done

if [ -z "$fixed_root" ]; then
  echo "Compiler did not reach a fixed point within $max_generations generations." >&2
  exit 1
fi

echo "[3/5] Verify the fixed-point compiler before changing the trust root"
rm -rf "$repo_root/dist"
mkdir -p "$repo_root/dist"
cp "$fixed_root/doof" "$repo_root/dist/doof"
cp "$repo_root/runtime/doof_runtime.h" "$repo_root/dist/doof_runtime.h"
cp "$repo_root/resources/std-catalog.json" "$repo_root/dist/std-catalog.json"
DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/scripts/release-verify.sh"

echo "[4/5] Refresh the source-only bootstrap snapshot"
candidate_root="$refresh_root/candidate-snapshot"
mkdir -p "$candidate_root" "$snapshot_backup"

rsync -a \
  --exclude='.doof-cache/***' \
  --exclude='.doof-objects/***' \
  --exclude='.reckon/***' \
  --exclude='/doof_runtime.h' \
  --include='*/' \
  --include='*.c' --include='*.cc' --include='*.cpp' \
  --include='*.h' --include='*.hh' --include='*.hpp' \
  --include='*.m' --include='*.mm' \
  --exclude='*' \
  "$fixed_root/" "$candidate_root/"

# A host build emits only its selected target-native sources. Preserve foreign
# host alternatives already reviewed into the shared cross-platform snapshot.
find "$snapshot_root" -type f | LC_ALL=C sort | while IFS= read -r source; do
  case "$(basename "$source")" in
    *_windows.c|*_windows.cc|*_windows.cpp|*_windows.h|*_windows.hh|*_windows.hpp|*_windows.m|*_windows.mm|\
    *_linux.c|*_linux.cc|*_linux.cpp|*_linux.h|*_linux.hh|*_linux.hpp|*_linux.m|*_linux.mm)
      relative_path=${source#"$snapshot_root/"}
      if [ ! -f "$candidate_root/$relative_path" ]; then
        mkdir -p "$(dirname -- "$candidate_root/$relative_path")"
        cp "$source" "$candidate_root/$relative_path"
      fi
      ;;
  esac
done

# Keep source-location mappings in ordinary compiler output, but omit them from
# the reviewed trust root. Source line changes should not create bootstrap
# snapshot churn unrelated to the generated C++ semantics.
"$repo_root/scripts/canonicalize-bootstrap-snapshot.sh" "$candidate_root"

source_count=$(find "$candidate_root" -type f | wc -l | tr -d ' ')
if [ "$source_count" -eq 0 ]; then
  echo "Verified compiler produced no bootstrap source artifacts." >&2
  exit 1
fi
unexpected=$(find "$candidate_root" -type f ! \( \
  -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o \
  -name '*.h' -o -name '*.hh' -o -name '*.hpp' -o \
  -name '*.m' -o -name '*.mm' \
\) -print -quit)
if [ -n "$unexpected" ]; then
  echo "Bootstrap candidate contains a non-source artifact: $unexpected" >&2
  exit 1
fi
if grep -R -F -l "$repo_root" "$candidate_root" >/dev/null 2>&1 || \
   grep -R -F -l "$stdlib_root" "$candidate_root" >/dev/null 2>&1; then
  echo "Bootstrap candidate contains an absolute developer path." >&2
  exit 1
fi

rsync -a --delete "$snapshot_root/" "$snapshot_backup/"
rollback_snapshot=true
rsync -a --delete "$candidate_root/" "$snapshot_root/"
echo "  Refreshed $source_count source artifacts."

echo "[5/5] Run the release gate from the refreshed snapshot"
DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/scripts/release.sh"
rollback_snapshot=false

echo "Bootstrap refresh passed: $snapshot_root"
