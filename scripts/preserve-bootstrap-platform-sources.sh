#!/bin/sh
set -eu

if [ "$#" -ne 2 ]; then
  echo "usage: $0 <existing-snapshot> <candidate-snapshot>" >&2
  exit 2
fi

snapshot_root=$1
candidate_root=$2

find "$snapshot_root" -type f | LC_ALL=C sort | while IFS= read -r source; do
  case "$(basename "$source")" in
    *_apple.c|*_apple.cc|*_apple.cpp|*_apple.h|*_apple.hh|*_apple.hpp|*_apple.m|*_apple.mm|\
    *_macos.c|*_macos.cc|*_macos.cpp|*_macos.h|*_macos.hh|*_macos.hpp|*_macos.m|*_macos.mm|\
    *_ios.c|*_ios.cc|*_ios.cpp|*_ios.h|*_ios.hh|*_ios.hpp|*_ios.m|*_ios.mm|\
    *_linux.c|*_linux.cc|*_linux.cpp|*_linux.h|*_linux.hh|*_linux.hpp|*_linux.m|*_linux.mm|\
    *_windows.c|*_windows.cc|*_windows.cpp|*_windows.h|*_windows.hh|*_windows.hpp|*_windows.m|*_windows.mm|\
    *_wasm.c|*_wasm.cc|*_wasm.cpp|*_wasm.h|*_wasm.hh|*_wasm.hpp|*_wasm.m|*_wasm.mm|\
    *_curl.c|*_curl.cc|*_curl.cpp|*_curl.h|*_curl.hh|*_curl.hpp)
      relative_path=${source#"$snapshot_root/"}
      # Preserve foreign alternatives only for modules reached by the new
      # compiler. This lets removed dependencies (for example std/http) leave
      # the bootstrap snapshot instead of keeping an orphaned native source.
      if [ -d "$(dirname -- "$candidate_root/$relative_path")" ] && \
         [ ! -f "$candidate_root/$relative_path" ]; then
        mkdir -p "$(dirname -- "$candidate_root/$relative_path")"
        cp "$source" "$candidate_root/$relative_path"
      fi
      ;;
  esac
done
