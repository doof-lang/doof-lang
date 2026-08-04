#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
if [ -d "$repo_root/bootstrap/generated" ]; then
  snapshot_root="$repo_root/bootstrap/generated"
else
  snapshot_root="$repo_root/bootstrap/macos-arm64/generated"
fi
output_root="$repo_root/build/bootstrap-stage0"
object_root="$output_root/objects"
include_response="$output_root/clang-includes.rsp"
object_response="$output_root/clang-objects.rsp"
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

if [ "$list_sources" = false ] && { [ "$(uname -s)" != "Darwin" ] || [ "$(uname -m)" != "arm64" ]; }; then
  echo "The checked-in stage-0 snapshot supports macOS arm64 only." >&2
  exit 1
fi

if [ ! -d "$snapshot_root" ]; then
  echo "Missing bootstrap snapshot: $snapshot_root" >&2
  exit 1
fi

collect_sources() {
  find "$snapshot_root" -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.m' -o -name '*.mm' \) \
    | LC_ALL=C sort \
    | while IFS= read -r source; do
      case "$(basename "$source")" in
        *_windows.c|*_windows.cc|*_windows.cpp|*_windows.m|*_windows.mm|\
        *_linux.c|*_linux.cc|*_linux.cpp|*_linux.m|*_linux.mm|\
        *_ios.c|*_ios.cc|*_ios.cpp|*_ios.m|*_ios.mm)
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

rm -rf "$output_root"
mkdir -p "$object_root"

echo "  Discovering bootstrap headers and sources..."
: > "$include_response"
find "$snapshot_root" -type f \( -name '*.h' -o -name '*.hpp' -o -name '*.hh' \) -exec dirname {} \; \
  | LC_ALL=C sort -u \
  | while IFS= read -r directory; do printf '%s\n' "-I$directory"; done \
  >> "$include_response"
collect_sources > "$source_list"

if [ ! -s "$source_list" ]; then
  echo "Bootstrap snapshot contains no compilable sources." >&2
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
echo "  Compiling $source_count generated source files with $jobs parallel Apple Clang jobs..."
index=0
while IFS= read -r source; do
  index=$((index + 1))
  printf '%s\0%s\0' "$source" "$object_root/$index.o"
done < "$source_list" \
  | xargs -0 -n 2 -P "$jobs" sh -c '
      xcrun clang++ -std=c++17 -O2 -DNDEBUG -pthread \
        @"$1" -c "$2" -o "$3" && printf "."
    ' sh "$include_response"
printf '\n'

find "$object_root" -type f -name '*.o' | LC_ALL=C sort > "$object_response"
object_count=$(wc -l < "$object_response" | tr -d ' ')
if [ "$object_count" -ne "$source_count" ]; then
  echo "Bootstrap compilation produced $object_count of $source_count expected objects." >&2
  exit 1
fi

echo "  Linking $object_count bootstrap objects..."
xcrun clang++ \
  -std=c++17 -O2 -DNDEBUG -pthread \
  -framework Foundation -framework CoreFoundation \
  @"$object_response" \
  -o "$output_root/doof"

cp "$repo_root/runtime/doof_runtime.h" "$output_root/doof_runtime.h"
cp "$repo_root/resources/std-catalog.json" "$output_root/std-catalog.json"
echo "  Stage-0 compiler is ready."
