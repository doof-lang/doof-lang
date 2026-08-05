#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
image=${DOOF_ALPINE_IMAGE:-doof-bootstrap-alpine:test}
alpine_version=${DOOF_ALPINE_VERSION:-3.22}
memory=${DOOF_ALPINE_MEMORY:-4g}

if ! command -v container >/dev/null 2>&1; then
  echo "Apple container CLI not found. Install Apple container and start it with 'container system start'." >&2
  exit 1
fi

echo "Building Alpine $alpine_version bootstrap test image..."
container build \
  --build-arg "ALPINE_VERSION=$alpine_version" \
  --file "$repo_root/tests/bootstrap-alpine/Containerfile" \
  --tag "$image" \
  "$repo_root/tests/bootstrap-alpine"

echo "Compiling the read-only bootstrap source mount..."
container run --rm \
  --memory "$memory" \
  --mount "type=bind,source=$repo_root,target=/work/doof,readonly" \
  --workdir /work/doof \
  --env "DOOF_BOOTSTRAP_OUTPUT_ROOT=/tmp/doof-bootstrap-stage0-linux" \
  --env "DOOF_BOOTSTRAP_FORCE_INCLUDE=/work/doof/tests/bootstrap-alpine/musl-bootstrap-compat.hpp" \
  --env "DOOF_BOOTSTRAP_LINK_FLAGS=-lbsd" \
  --env "DOOF_BUILD_JOBS=${DOOF_BUILD_JOBS:-2}" \
  "$image" \
  /bin/sh -c './scripts/bootstrap-compiler-linux.sh && /tmp/doof-bootstrap-stage0-linux/doof --help >/tmp/doof-help.txt && grep -q "^usage: doof " /tmp/doof-help.txt'

echo "Alpine bootstrap compile, link, and smoke test passed."
