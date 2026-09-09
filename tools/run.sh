#!/bin/sh
set -eu
root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
case "${1:-}" in
  dev) seed=${DOOF_DEV_COMPILER:-} ;;
  *) seed=${DOOF_SEED_COMPILER:-} ;;
esac
if [ -z "$seed" ]; then seed=$(command -v doof 2>/dev/null || true); fi
if [ -z "$seed" ] && [ -x "$root/dist/doof" ]; then seed="$root/dist/doof"; fi
[ -n "$seed" ] || { echo 'No installed Doof; use install.sh or a release source snapshot.' >&2; exit 1; }
DOOF_STDLIB_ROOT=${DOOF_STDLIB_ROOT:-"$root/../doof-stdlib"}
export DOOF_STDLIB_ROOT
exec "$seed" run "$root/tools/repository" -o "$root/build/repository-tool" -- "$root" "$@"
