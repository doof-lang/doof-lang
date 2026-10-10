#!/bin/sh
# Hermetic metadata provider for native dependency detection tests.
set -eu
root=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
case "$2" in
  absent) exit 1 ;;
  old-version) case "$1" in --atleast-version=*) exit 1 ;; esac ;;
  fixture) [ -f "$root/metadata-present" ] || exit 1 ;;
esac
case "$1" in
  --atleast-version=*) exit 0 ;;
  --cflags)
    case "$2" in
      missing-header) printf '%s\n' "-I$root/empty" ;;
      *) printf '%s\n' "-I$root/include" ;;
    esac ;;
  --libs)
    case "$2" in
      wrong-library) printf '%s\n' '-ldoof_nonexistent_optional_fixture_library' ;;
      *) exit 0 ;;
    esac ;;
  *) exit 1 ;;
esac
