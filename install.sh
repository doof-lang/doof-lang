#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
stdlib_root=${DOOF_STDLIB_ROOT:-"$repo_root/../doof-stdlib"}
if [ "${DOOF_HOME+x}" = x ]; then
  doof_home=$DOOF_HOME
else
  doof_home="$HOME/.doof"
fi
work_root="$repo_root/build/dev-install"
package_root="$work_root/compiler"
bundle_tool_root="$work_root/stdlib-bundle-tool"
artifact_root="$work_root/artifacts"

usage() {
  echo "usage: ./install.sh"
}

if [ "$#" -ne 0 ]; then
  usage >&2
  exit 2
fi

if [ -z "$doof_home" ]; then
  echo "install.sh: DOOF_HOME cannot be empty" >&2
  exit 2
fi
case "$doof_home" in
  /*) ;;
  *)
    echo "install.sh: DOOF_HOME must be an absolute path: $doof_home" >&2
    exit 2
    ;;
esac
while [ "$doof_home" != "/" ] && [ "${doof_home%/}" != "$doof_home" ]; do
  doof_home=${doof_home%/}
done
if [ "$doof_home" = "/" ]; then
  echo "install.sh: refusing to use / as DOOF_HOME" >&2
  exit 2
fi

if [ ! -d "$stdlib_root" ]; then
  echo "install.sh: Doof stdlib not found at $stdlib_root" >&2
  echo "Set DOOF_STDLIB_ROOT to the directory containing the std package folders." >&2
  exit 1
fi

seed_compiler=""
if [ -n "${DOOF_DEV_COMPILER:-}" ]; then
  case "$DOOF_DEV_COMPILER" in
    */*) seed_compiler=$DOOF_DEV_COMPILER ;;
    *) seed_compiler=$(command -v "$DOOF_DEV_COMPILER" 2>/dev/null || true) ;;
  esac
  if [ -z "$seed_compiler" ] || [ ! -x "$seed_compiler" ]; then
    echo "install.sh: DOOF_DEV_COMPILER is not executable: $DOOF_DEV_COMPILER" >&2
    exit 1
  fi
elif command -v doof >/dev/null 2>&1; then
  seed_compiler=$(command -v doof)
elif [ -x "$repo_root/dist/doof" ]; then
  seed_compiler="$repo_root/dist/doof"
else
  echo "install.sh: no seed Doof compiler found" >&2
  echo "Set DOOF_DEV_COMPILER, add doof to PATH, or run ./build.sh once." >&2
  exit 1
fi

host_system=$(uname -s)
case "$host_system" in
  Darwin) stdlib_bundle_targets="ios-device,ios-simulator,macos,wasm" ;;
  Linux) stdlib_bundle_targets="linux,wasm" ;;
  *)
    echo "install.sh: unsupported development install host: $host_system" >&2
    exit 1
    ;;
esac

mkdir -p "$artifact_root"
rm -f \
  "$artifact_root/doof" \
  "$artifact_root/doof_runtime.h" \
  "$artifact_root/doof_wasm_test_runner_apple.swift" \
  "$artifact_root/doof-stdlib.tar"

echo "Packaging the development compiler with $seed_compiler..."
if ! env DOOF_STDLIB_ROOT="$stdlib_root" "$seed_compiler" package "$repo_root" \
  -o "$package_root" --distdir "$artifact_root"
then
  echo "install.sh: compiler package failed; the existing installation was not changed" >&2
  exit 1
fi

echo "Bundling the development standard library..."
if ! env DOOF_STDLIB_ROOT="$stdlib_root" "$seed_compiler" run "$repo_root/tools/stdlib-bundle.do" \
  -o "$bundle_tool_root" -- \
  "$stdlib_root" "$artifact_root/doof-stdlib.tar" "$stdlib_bundle_targets"
then
  echo "install.sh: stdlib bundle failed; the existing installation was not changed" >&2
  exit 1
fi

"$repo_root/scripts/install-artifacts.sh" "$artifact_root" "$doof_home" dev

installed_compiler="$doof_home/bin/doof"
"$installed_compiler" --help >/dev/null

echo "Installed development compiler: $installed_compiler"
active_compiler=$(command -v doof 2>/dev/null || true)
if [ "$active_compiler" != "$installed_compiler" ]; then
  echo "Add the development compiler to the front of PATH:"
  if [ "${DOOF_HOME+x}" != x ]; then
    echo '  export PATH="$HOME/.doof/bin:$PATH"'
  else
    printf '  export PATH="%s/bin:$PATH"\n' "$doof_home"
  fi
fi
