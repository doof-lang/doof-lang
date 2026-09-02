#!/bin/sh
set -eu

if [ "$#" -ne 3 ]; then
  echo "usage: install-artifacts.sh <artifact-directory> <doof-home> <version-name>" >&2
  exit 2
fi

artifact_root=$1
doof_home=$2
version_name=$3

if [ -z "$doof_home" ]; then
  echo "install-artifacts.sh: Doof home cannot be empty" >&2
  exit 2
fi
case "$doof_home" in
  /*) ;;
  *)
    echo "install-artifacts.sh: Doof home must be an absolute path: $doof_home" >&2
    exit 2
    ;;
esac
while [ "$doof_home" != "/" ] && [ "${doof_home%/}" != "$doof_home" ]; do
  doof_home=${doof_home%/}
done
if [ "$doof_home" = "/" ]; then
  echo "install-artifacts.sh: refusing to use / as Doof home" >&2
  exit 2
fi

case "$version_name" in
  ""|.|..|*[!A-Za-z0-9._-]*)
    echo "install-artifacts.sh: unsafe version name: $version_name" >&2
    exit 2
    ;;
esac

if [ ! -x "$artifact_root/doof" ]; then
  echo "install-artifacts.sh: missing executable compiler: $artifact_root/doof" >&2
  exit 1
fi
for resource in doof_runtime.h doof_wasm_test_runner_apple.swift doof-stdlib.tar; do
  if [ ! -f "$artifact_root/$resource" ]; then
    echo "install-artifacts.sh: missing compiler resource: $artifact_root/$resource" >&2
    exit 1
  fi
done

versions_root="$doof_home/versions"
version_root="$versions_root/$version_name"
current_path="$doof_home/current"
bin_root="$doof_home/bin"

for managed_link in \
  "$current_path" \
  "$bin_root/doof" \
  "$bin_root/doof_runtime.h" \
  "$bin_root/doof_wasm_test_runner_apple.swift" \
  "$bin_root/doof-stdlib.tar"
do
  if [ -d "$managed_link" ] && [ ! -L "$managed_link" ]; then
    echo "install-artifacts.sh: cannot replace directory at $managed_link" >&2
    exit 1
  fi
done

install -d "$versions_root" "$bin_root"
staging_root=$(mktemp -d "$versions_root/.${version_name}.new.XXXXXX")
backup_root="$versions_root/.${version_name}.old.$$"
version_replaced=false
has_backup=false

finish() {
  status=$?
  trap - EXIT HUP INT TERM
  if [ -d "$staging_root" ]; then
    rm -rf "$staging_root"
  fi
  if [ "$status" -ne 0 ]; then
    if [ "$version_replaced" = true ]; then
      rm -rf "$version_root"
    fi
    if [ "$has_backup" = true ]; then
      if [ -e "$version_root" ] || [ -L "$version_root" ]; then
        rm -rf "$version_root"
      fi
      mv "$backup_root" "$version_root"
      has_backup=false
    fi
  fi
  if [ "$has_backup" = true ]; then
    rm -rf "$backup_root"
  fi
  exit "$status"
}
trap finish EXIT HUP INT TERM

install -m 0755 "$artifact_root/doof" "$staging_root/doof"
install -m 0644 "$artifact_root/doof_runtime.h" "$staging_root/doof_runtime.h"
install -m 0644 "$artifact_root/doof_wasm_test_runner_apple.swift" "$staging_root/doof_wasm_test_runner_apple.swift"
install -m 0644 "$artifact_root/doof-stdlib.tar" "$staging_root/doof-stdlib.tar"

if [ -e "$version_root" ] || [ -L "$version_root" ]; then
  if [ -e "$backup_root" ] || [ -L "$backup_root" ]; then
    echo "install-artifacts.sh: temporary backup path already exists: $backup_root" >&2
    exit 1
  fi
  mv "$version_root" "$backup_root"
  has_backup=true
fi
mv "$staging_root" "$version_root"
version_replaced=true

ln -sfn "versions/$version_name" "$current_path"
ln -sfn ../current/doof "$bin_root/doof"
ln -sfn ../current/doof_runtime.h "$bin_root/doof_runtime.h"
ln -sfn ../current/doof_wasm_test_runner_apple.swift "$bin_root/doof_wasm_test_runner_apple.swift"
ln -sfn ../current/doof-stdlib.tar "$bin_root/doof-stdlib.tar"
