#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
snapshot_root="$repo_root/bootstrap/macos-arm64/generated"
output_root="$repo_root/build/bootstrap-stage0"
object_root="$output_root/objects"
include_response="$output_root/clang-includes.rsp"
object_response="$output_root/clang-objects.rsp"
source_list="$output_root/sources"

if [ "$(uname -s)" != "Darwin" ] || [ "$(uname -m)" != "arm64" ]; then
  echo "The checked-in stage-0 snapshot supports macOS arm64 only." >&2
  exit 1
fi

if [ ! -d "$snapshot_root" ]; then
  echo "Missing bootstrap snapshot: $snapshot_root" >&2
  exit 1
fi

rm -rf "$output_root"
mkdir -p "$object_root"

echo "  Discovering bootstrap headers and sources..."
: > "$include_response"
find "$snapshot_root" -type f \( -name '*.h' -o -name '*.hpp' -o -name '*.hh' \) -exec dirname {} \; \
  | LC_ALL=C sort -u \
  | while IFS= read -r directory; do printf '%s\n' "-I$directory"; done \
  >> "$include_response"
find "$snapshot_root" -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.m' -o -name '*.mm' \) \
  | LC_ALL=C sort \
  > "$source_list"

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
