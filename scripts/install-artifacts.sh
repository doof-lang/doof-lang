#!/bin/sh
set -eu

if [ "$#" -ne 2 ]; then
  echo "usage: install-artifacts.sh <artifact-directory> <absolute-prefix>" >&2
  exit 2
fi

artifact_root=$1
prefix=$2

if [ -z "$prefix" ]; then
  echo "install-artifacts.sh: install prefix cannot be empty" >&2
  exit 2
fi
case "$prefix" in
  /*) ;;
  *)
    echo "install-artifacts.sh: install prefix must be an absolute path: $prefix" >&2
    exit 2
    ;;
esac
while [ "$prefix" != "/" ] && [ "${prefix%/}" != "$prefix" ]; do
  prefix=${prefix%/}
done
if [ "$prefix" = "/" ]; then
  echo "install-artifacts.sh: refusing to install with / as the prefix" >&2
  exit 2
fi

if [ ! -x "$artifact_root/doof" ]; then
  echo "install-artifacts.sh: missing executable compiler: $artifact_root/doof" >&2
  exit 1
fi
for resource in doof_runtime.h std-catalog.json; do
  if [ ! -f "$artifact_root/$resource" ]; then
    echo "install-artifacts.sh: missing compiler resource: $artifact_root/$resource" >&2
    exit 1
  fi
done

bundle_root="$prefix/libexec/doof"
bin_root="$prefix/bin"
command_path="$bin_root/doof"

for managed_path in \
  "$bundle_root/doof" \
  "$bundle_root/doof_runtime.h" \
  "$bundle_root/std-catalog.json" \
  "$bin_root/doof" \
  "$bin_root/doof_runtime.h" \
  "$bin_root/std-catalog.json"
do
  if [ -d "$managed_path" ]; then
    echo "install-artifacts.sh: cannot replace directory at $managed_path" >&2
    exit 1
  fi
done

install -d "$bundle_root" "$bin_root"
install -m 0755 "$artifact_root/doof" "$bundle_root/doof"
install -m 0644 "$artifact_root/doof_runtime.h" "$bundle_root/doof_runtime.h"
install -m 0644 "$artifact_root/std-catalog.json" "$bundle_root/std-catalog.json"
ln -sfn ../libexec/doof/doof "$command_path"
ln -sfn ../libexec/doof/doof_runtime.h "$bin_root/doof_runtime.h"
ln -sfn ../libexec/doof/std-catalog.json "$bin_root/std-catalog.json"
