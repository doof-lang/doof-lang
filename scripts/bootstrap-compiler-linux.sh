#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
if [ -d "$repo_root/bootstrap/generated" ]; then
  snapshot_root="$repo_root/bootstrap/generated"
else
  snapshot_root="$repo_root/bootstrap/macos-arm64/generated"
fi
output_root=${DOOF_BOOTSTRAP_OUTPUT_ROOT:-"$repo_root/build/bootstrap-stage0-linux"}
object_root="$output_root/objects"
include_response="$output_root/cxx-includes.rsp"
object_response="$output_root/cxx-objects.rsp"
source_list="$output_root/sources"
list_sources=false

if [ "${1:-}" = "--list-sources" ]; then
  list_sources=true
  shift
fi
if [ "$#" -ne 0 ]; then
  echo "usage: $0 [--list-sources]" >&2
  exit 2
fi

if [ "$list_sources" = false ] && [ "$(uname -s)" != "Linux" ]; then
  echo "The Linux stage-0 bootstrap must run on Linux." >&2
  exit 1
fi

if [ ! -d "$snapshot_root" ]; then
  echo "Missing bootstrap snapshot: $snapshot_root" >&2
  exit 1
fi

collect_sources() {
  find "$snapshot_root" -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' \) \
    | LC_ALL=C sort \
    | while IFS= read -r source; do
      case "$(basename "$source")" in
        *_apple.c|*_apple.cc|*_apple.cpp|\
        *_macos.c|*_macos.cc|*_macos.cpp|\
        *_ios.c|*_ios.cc|*_ios.cpp|\
        *_windows.c|*_windows.cc|*_windows.cpp)
          continue
          ;;
      esac
      printf '%s\n' "$source"
    done
}

if [ "$list_sources" = true ]; then
  collect_sources | sed "s#^$snapshot_root/##"
  exit 0
fi

cxx=${CXX:-c++}
if ! command -v "$cxx" >/dev/null 2>&1; then
  echo "C++ compiler not found: $cxx" >&2
  exit 1
fi
rm -rf "$output_root"
mkdir -p "$object_root"

echo "  Discovering Linux bootstrap headers and sources..."
: > "$include_response"
find "$snapshot_root" -type f \( -name '*.h' -o -name '*.hpp' -o -name '*.hh' \) -exec dirname {} \; \
  | LC_ALL=C sort -u \
  | while IFS= read -r directory; do printf '%s\n' "-I$directory"; done \
  >> "$include_response"
collect_sources > "$source_list"

curl_link_flags=""
if grep -q '/native_http_client_curl\.cpp$' "$source_list"; then
  if ! command -v pkg-config >/dev/null 2>&1 || ! pkg-config --exists libcurl; then
    echo "Linux bootstrap requires pkg-config metadata for libcurl." >&2
    echo "Install pkg-config and the libcurl development package." >&2
    exit 1
  fi
  for flag in $(pkg-config --cflags libcurl); do
    printf '%s\n' "$flag" >> "$include_response"
  done
  curl_link_flags=$(pkg-config --libs libcurl)
fi

if [ ! -s "$source_list" ]; then
  echo "Bootstrap snapshot contains no compilable Linux sources." >&2
  exit 1
fi

jobs=${DOOF_BUILD_JOBS:-$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)}
case "$jobs" in
  ''|*[!0-9]*|0)
    echo "DOOF_BUILD_JOBS must be a positive integer (got '$jobs')." >&2
    exit 1
    ;;
esac

source_count=$(wc -l < "$source_list" | tr -d ' ')
echo "  Compiling $source_count generated source files with $jobs parallel $cxx jobs..."
index=0
while IFS= read -r source; do
  index=$((index + 1))
  printf '%s\0%s\0' "$source" "$object_root/$index.o"
done < "$source_list" \
  | xargs -0 -n 2 -P "$jobs" sh -c '
      compiler=$1
      includes=$2
      source=$3
      object=$4
      "$compiler" -std=c++17 -O2 -DNDEBUG -pthread \
        @"$includes" -c "$source" -o "$object" && printf "."
    ' sh "$cxx" "$include_response"
printf '\n'

find "$object_root" -type f -name '*.o' | LC_ALL=C sort > "$object_response"
object_count=$(wc -l < "$object_response" | tr -d ' ')
if [ "$object_count" -ne "$source_count" ]; then
  echo "Bootstrap compilation produced $object_count of $source_count expected objects." >&2
  exit 1
fi

echo "  Linking $object_count bootstrap objects..."
# DOOF_BOOTSTRAP_LINK_FLAGS is intentionally shell-split so callers can supply
# a conventional list such as "-lbsd -ldl" for their libc/toolchain.
# shellcheck disable=SC2086
"$cxx" -std=c++17 -O2 -DNDEBUG -pthread @"$object_response" $curl_link_flags ${DOOF_BOOTSTRAP_LINK_FLAGS:-} -o "$output_root/doof"

cp "$repo_root/runtime/doof_runtime.h" "$output_root/doof_runtime.h"
cp "$repo_root/runtime/doof_wasm_test_runner_apple.swift" "$output_root/doof_wasm_test_runner_apple.swift"
echo "  Linux stage-0 compiler is ready: $output_root/doof"
