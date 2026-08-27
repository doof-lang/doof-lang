#!/bin/sh
set -eu

usage() {
  echo "usage: $0 SNAPSHOT_ROOT" >&2
}

if [ "$#" -ne 1 ]; then
  usage
  exit 2
fi

snapshot_root=$1
if [ ! -d "$snapshot_root" ]; then
  echo "Bootstrap snapshot root is not a directory: $snapshot_root" >&2
  exit 1
fi

find "$snapshot_root" -type f \( \
    -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o \
    -name '*.h' -o -name '*.hh' -o -name '*.hpp' -o \
    -name '*.m' -o -name '*.mm' \
  \) | LC_ALL=C sort | while IFS= read -r source; do
  temporary="$source.doof-canonicalize.$$"
  sed '/^#line /d' "$source" > "$temporary"
  cat "$temporary" > "$source"
  rm -f "$temporary"
done

if find "$snapshot_root" -type f \( \
    -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o \
    -name '*.h' -o -name '*.hh' -o -name '*.hpp' -o \
    -name '*.m' -o -name '*.mm' \
  \) -exec grep -l '^#line ' {} + | grep -q .; then
  echo "Bootstrap snapshot still contains a generated #line directive." >&2
  exit 1
fi
