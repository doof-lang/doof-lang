#!/bin/sh
# Standalone release installer. Also owns the shared local artifact transaction.
set -eu

install_artifacts() (
  set -eu
  [ "$#" -eq 3 ] || { echo 'usage: install-artifacts.sh <artifact-directory> <doof-home> <version-name>' >&2; exit 2; }
  artifact_root=$1
  doof_home=$2
  version_name=$3
  [ -n "$doof_home" ] || { echo 'Doof home cannot be empty' >&2; exit 2; }
  case "$doof_home" in /*) ;; *) echo 'Doof home must be an absolute path' >&2; exit 2 ;; esac
  while [ "$doof_home" != / ] && [ "${doof_home%/}" != "$doof_home" ]; do doof_home=${doof_home%/}; done
  case "$doof_home" in */../*|*/..|*/./*|*/.) echo 'Doof home must not contain dot path components' >&2; exit 2 ;; esac
  [ "$doof_home" != / ] || { echo 'refusing to use / as Doof home' >&2; exit 2; }
  case "$version_name" in ''|.|..|*[!A-Za-z0-9._-]*) echo 'unsafe version name' >&2; exit 2 ;; esac
  [ -x "$artifact_root/doof" ] || { echo 'missing executable compiler' >&2; exit 1; }
  for resource in doof_runtime.h doof_wasm_test_runner_apple.swift doof-stdlib.tar; do
    [ -f "$artifact_root/$resource" ] || { echo "missing compiler resource: $resource" >&2; exit 1; }
  done
  for directory in "$doof_home/versions" "$doof_home/bin"; do
    [ ! -L "$directory" ] || { echo "managed directory cannot be a symlink: $directory" >&2; exit 1; }
  done
  for name in current bin/doof bin/doof_runtime.h bin/doof_wasm_test_runner_apple.swift bin/doof-stdlib.tar 'bin/Doof Debugger.app'; do
    if [ -d "$doof_home/$name" ] && [ ! -L "$doof_home/$name" ]; then
      echo "cannot replace directory: $doof_home/$name" >&2; exit 1
    fi
  done
  mkdir -p "$doof_home/versions" "$doof_home/bin"
  lock="$doof_home/.install-lock"
  mkdir "$lock" 2>/dev/null || { echo 'cannot acquire install lock: another installation is running or DOOF_HOME is not writable' >&2; exit 1; }
  transaction=$(mktemp -d "$doof_home/versions/.install.XXXXXX")
  version_root="$doof_home/versions/$version_name"
  replaced=false
  activated=false
  committed=false
  finish_install() {
    status=$?
    trap - EXIT HUP INT TERM
    if [ "$committed" != true ]; then
      if [ "$activated" = true ]; then
        rm -f "$doof_home/current"
        if [ -e "$transaction/old-current" ] || [ -L "$transaction/old-current" ]; then mv "$transaction/old-current" "$doof_home/current"; fi
      fi
      if [ "$replaced" = true ]; then rm -rf "$version_root"; fi
      if [ -d "$transaction/old-version" ]; then mv "$transaction/old-version" "$version_root"; fi
      if [ -f "$transaction/links-started" ]; then
        for name in doof doof_runtime.h doof_wasm_test_runner_apple.swift doof-stdlib.tar 'Doof Debugger.app'; do
          rm -f "$doof_home/bin/$name"
          if [ -e "$transaction/links/$name" ] || [ -L "$transaction/links/$name" ]; then mv "$transaction/links/$name" "$doof_home/bin/$name"; fi
        done
      fi
    fi
    rm -rf "$transaction"
    rmdir "$lock"
    exit "$status"
  }
  trap finish_install EXIT
  trap 'exit 130' HUP INT TERM
  mkdir "$transaction/new" "$transaction/links"
  for name in doof doof_runtime.h doof_wasm_test_runner_apple.swift doof-stdlib.tar; do
    cp "$artifact_root/$name" "$transaction/new/$name"
  done
  if [ -d "$artifact_root/Doof Debugger.app" ]; then cp -R "$artifact_root/Doof Debugger.app" "$transaction/new/Doof Debugger.app"; fi
  chmod 755 "$transaction/new/doof"
  chmod 644 "$transaction/new/doof_runtime.h" "$transaction/new/doof_wasm_test_runner_apple.swift" "$transaction/new/doof-stdlib.tar"
  "$transaction/new/doof" --help >/dev/null
  if [ -d "$transaction/new/Doof Debugger.app" ]; then
    [ -x "$transaction/new/Doof Debugger.app/Contents/MacOS/DoofDebugger" ] || { echo 'invalid debugger application' >&2; exit 1; }
  fi
  if [ -e "$version_root" ] || [ -L "$version_root" ]; then
    [ ! -L "$version_root" ] || { echo 'version directory cannot be a symlink' >&2; exit 1; }
    mv "$version_root" "$transaction/old-version"
  fi
  mv "$transaction/new" "$version_root"
  replaced=true
  # Save every link before changing any, including dangling links.
  for name in doof doof_runtime.h doof_wasm_test_runner_apple.swift doof-stdlib.tar 'Doof Debugger.app'; do
    if [ -e "$doof_home/bin/$name" ] || [ -L "$doof_home/bin/$name" ]; then cp -P "$doof_home/bin/$name" "$transaction/links/$name"; fi
  done
  touch "$transaction/links-started"
  for name in doof doof_runtime.h doof_wasm_test_runner_apple.swift doof-stdlib.tar 'Doof Debugger.app'; do
    if [ "$name" != 'Doof Debugger.app' ] || [ -d "$version_root/$name" ]; then
      ln -sfn "../current/$name" "$doof_home/bin/$name"
    elif [ -L "$doof_home/bin/$name" ]; then rm "$doof_home/bin/$name"; fi
  done
  if [ -e "$doof_home/current" ] || [ -L "$doof_home/current" ]; then cp -P "$doof_home/current" "$transaction/old-current"; fi
  ln -s "versions/$version_name" "$transaction/new-current"
  # BSD mv -h replaces the symlink itself instead of following its directory target.
  if [ "$(uname -s)" = Darwin ]; then mv -fh "$transaction/new-current" "$doof_home/current"; else mv -fT "$transaction/new-current" "$doof_home/current"; fi
  activated=true
  "$doof_home/bin/doof" --help >/dev/null
  committed=true
)

stable_version() {
  printf '%s\n' "$1" | LC_ALL=C grep -Eq '^(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)$'
}

install_release() (
  version=''
  case "${1:-}" in
    --version) [ "$#" -eq 2 ] || { echo 'usage: install.sh [--version MAJOR.MINOR.PATCH]' >&2; exit 2; }; version=$2; stable_version "$version" || { echo 'invalid release version' >&2; exit 2; } ;;
    '') [ "$#" -eq 0 ] || exit 2 ;;
    *) echo 'usage: install.sh [--version MAJOR.MINOR.PATCH]' >&2; exit 2 ;;
  esac
  [ "$(uname -s)/$(uname -m)" = Darwin/arm64 ] || { echo 'Doof releases currently support macOS arm64 only' >&2; exit 1; }
  doof_home=${DOOF_HOME-"$HOME/.doof"}
  case "$doof_home" in /*) ;; *) echo 'DOOF_HOME must be a nonempty absolute path' >&2; exit 2 ;; esac
  case "$doof_home" in /|//|///) echo 'DOOF_HOME cannot be /' >&2; exit 2 ;; esac
  for tool in curl unzip zipinfo shasum; do command -v "$tool" >/dev/null || { echo "Required tool not found: $tool" >&2; exit 1; }; done
  download=$(mktemp -d "${TMPDIR:-/tmp}/doof-download.XXXXXX")
  trap 'rm -rf "$download"' EXIT
  trap 'exit 130' HUP INT TERM
  github=https://github.com/doof-lang/doof-lang
  if [ -z "$version" ]; then
    resolved=$(curl --proto '=https' --proto-redir '=https' --tlsv1.2 --connect-timeout 15 --max-time 300 -fsSL --retry 3 -o /dev/null -w '%{url_effective}' "$github/releases/latest")
    case "$resolved" in "$github/releases/tag/v"*) version=${resolved#"$github/releases/tag/v"} ;; *) echo 'could not resolve latest stable Doof release' >&2; exit 1 ;; esac
    stable_version "$version" || { echo 'latest release does not have a stable version tag' >&2; exit 1; }
  fi
  archive="doof-$version-macos-arm64.zip"
  base="$github/releases/download/v$version"
  for name in "$archive" SHA256SUMS; do
    curl --proto '=https' --proto-redir '=https' --tlsv1.2 --connect-timeout 15 --max-time 300 -fsSL --retry 3 "$base/$name" -o "$download/$name"
  done
  awk -v name="$archive" '$2 == name && length($1) == 64 && $1 !~ /[^0-9a-f]/ {print $1 "  " $2; count++} END {if(count != 1) exit 1}' "$download/SHA256SUMS" > "$download/checksum"
  (cd "$download" && shasum -a 256 -c checksum)
  zipinfo -1 "$download/$archive" > "$download/entries"
  [ -s "$download/entries" ] || { echo 'empty release archive' >&2; exit 1; }
  while IFS= read -r entry; do
    case "$entry" in ''|/*|*\\*|../*|*/../*|*/..|..|./*|*/./*) echo 'unsafe archive path' >&2; exit 1 ;; esac
    case "$entry" in *[!A-Za-z0-9._/\ -]*) echo 'unsupported archive filename' >&2; exit 1 ;; esac
  done < "$download/entries"
  # Release payloads contain only ordinary files/directories, never links or devices.
  zipinfo -l "$download/$archive" > "$download/modes"
  if LC_ALL=C grep -Eq '^[lbcps][-rwxstST?]{9}' "$download/modes"; then echo 'unsafe archive entry type' >&2; exit 1; fi
  mkdir "$download/artifacts"
  unzip -q "$download/$archive" -d "$download/artifacts"
  artifacts="$download/artifacts"
  [ -x "$artifacts/doof" ] || { echo 'missing executable compiler' >&2; exit 1; }
  [ -x "$artifacts/Doof Debugger.app/Contents/MacOS/DoofDebugger" ] || { echo 'missing debugger application' >&2; exit 1; }
  [ "$("$artifacts/doof" --version)" = "doof $version" ] || { echo 'downloaded compiler version mismatch' >&2; exit 1; }
  printf 'function main(): int => 0\n' > "$download/smoke.do"
  env -u DOOF_STDLIB_ROOT -u DOOF_RUNTIME_HEADER "$artifacts/doof" emit "$download/smoke.do" -o "$download/smoke" >/dev/null
  install_artifacts "$artifacts" "$doof_home" "$version"
  echo "Installed doof $version: $doof_home/bin/doof"
  printf 'Add to PATH: export PATH="%s/bin:$PATH"\n' "$doof_home"
)

if [ "${DOOF_INSTALL_LIBRARY_ONLY:-}" != 1 ]; then install_release "$@"; fi
