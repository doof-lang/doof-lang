#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
prefix=/usr/local

usage() {
  echo "usage: ./install.sh [--prefix <absolute-path>]"
}

if [ "$#" -gt 0 ]; then
  if [ "$1" != "--prefix" ]; then
    usage >&2
    exit 2
  fi
  if [ "$#" -ne 2 ]; then
    echo "install.sh: --prefix requires exactly one value" >&2
    usage >&2
    exit 2
  fi
  prefix=$2
fi

if [ -z "$prefix" ]; then
  echo "install.sh: install prefix cannot be empty" >&2
  exit 2
fi
case "$prefix" in
  /*) ;;
  *)
    echo "install.sh: install prefix must be an absolute path: $prefix" >&2
    exit 2
    ;;
esac
while [ "$prefix" != "/" ] && [ "${prefix%/}" != "$prefix" ]; do
  prefix=${prefix%/}
done
if [ "$prefix" = "/" ]; then
  echo "install.sh: refusing to install with / as the prefix" >&2
  exit 2
fi

DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/build.sh"
DOOF_STDLIB_ROOT="$stdlib_root" "$repo_root/scripts/test.sh"

echo "Installing verified compiler under $prefix (sudo required)..."
sudo "$repo_root/scripts/install-artifacts.sh" "$repo_root/dist" "$prefix"

"$prefix/bin/doof" --help >/dev/null
echo "Installed compiler: $prefix/bin/doof"
