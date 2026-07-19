#!/bin/sh
set -eu

if [ "$#" -ne 2 ]; then
  echo "usage: $0 LEFT_BUILD RIGHT_BUILD" >&2
  exit 2
fi

left_root=$1
right_root=$2
work_root=$(mktemp -d "${TMPDIR:-/tmp}/doof-fixed-point.XXXXXX")
trap 'rm -rf "$work_root"' EXIT HUP INT TERM

collect() {
  root=$1
  output=$2
  find "$root" -type f \( \
      -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o \
      -name '*.h' -o -name '*.hh' -o -name '*.hpp' -o \
      -name '*.m' -o -name '*.mm' \
    \) \
    ! -path '*/.doof-objects/*' \
    ! -path '*/.reckon/*' \
    | sed "s#^$root/##" \
    | LC_ALL=C sort > "$output"
}

collect "$left_root" "$work_root/left-files"
collect "$right_root" "$work_root/right-files"
diff -u "$work_root/left-files" "$work_root/right-files"

while IFS= read -r relative_path; do
  if ! cmp -s "$left_root/$relative_path" "$right_root/$relative_path"; then
    echo "Generated fixed-point mismatch: $relative_path" >&2
    exit 1
  fi
done < "$work_root/left-files"

count=$(wc -l < "$work_root/left-files" | tr -d ' ')
echo "Compared $count generated source artifacts byte-for-byte."

