# Standard Compression, Archive, and Image APIs

## `std/archive`

```doof
import { ZipEntry, ZipCompression, ArchiveEntryKind, readZip, writeZip, crc32, deflate, inflate } from "std/archive"
```

`readZip(data)` parses an in-memory ZIP into `ZipEntry[]`; `writeZip(entries)`
builds one. Entries carry names, bytes, kind, and compression selection. The
implementation supports stored and deflated entries. `deflate` and `inflate`
operate on raw deflate payloads without zlib/gzip framing; `inflate` is
fallible. `crc32` computes the ZIP-compatible checksum.

## `std/gzip`

```doof
import { gzip, gunzip, GzipStream } from "std/gzip"
```

`gzip(data)` returns a complete gzip frame. `gunzip(data)` returns
`Result<readonly byte[], string>` for invalid/truncated input.
`GzipStream(source)` incrementally compresses a `Stream<readonly byte[]>`.

## `std/zstd`

```doof
import { zstdCompress, zstdCompressWithLevel, zstdDecompress, ZstdCompressStream } from "std/zstd"
```

All one-shot operations return `Result<readonly byte[], string>`.
`zstdCompressWithLevel(data, level)` uses the upstream default for `0` and
clamps unsupported levels. `ZstdCompressStream(source)` and
`ZstdCompressStream.withLevel(source, level)` provide incremental compression.

## `std/image`

```doof
import {
  Image, ImageView, PixelBytes, PixelAlphaMode,
  ImageFormat, ImageResampling, ImageEncodeOptions,
  ImageError, ImageErrorKind,
} from "std/image"
```

The Apple backend uses a stable in-memory representation: tightly packed 8-bit
RGBA, sRGB, premultiplied alpha, and top-left origin. It supports macOS, iOS
Simulator, and iOS Device.

- `PixelBytes(width, height, bytes, alphaMode)` is an immutable validated copy.
- `Image.create`, `fromPixelBytes`, `loadFile`, and `loadBlob` return managed,
  mutable images.
- `view(x, y, width, height)` creates a non-copying retained `ImageView`; nested
  views write through. Invalid or empty bounds fail rather than clamp.
- `pixelBytes(alphaMode?)` snapshots pixels; `.Straight` converts to/from
  ordinary non-premultiplied RGBA.
- `resize` returns an independent image using `.Nearest`, `.Linear`, or
  `.HighQuality` resampling.
- `copyFrom` replaces pixels and `sourceOver` alpha-composites. Destination
  clipping permits negative coordinates and overlapping self-blits are safe.
- `saveBlob`/`saveFile` require an explicit `.Png`, `.Jpeg`, `.Heic`, `.Tiff`,
  or single-frame `.Gif` format. `quality` applies to JPEG/HEIC.

Fallible operations return `Result<..., ImageError>` with a categorized kind
and actionable message. File extensions do not select an encoder.
