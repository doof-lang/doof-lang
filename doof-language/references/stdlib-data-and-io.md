# Standard Data, Filesystem, Stream, URL, and Event APIs

## `std/blob`

```doof
import { BlobBuilder, BlobReader, EncodingError, Endian, TextEncoding, decodeUtf8 } from "std/blob"
```

`BlobBuilder` and `BlobReader` provide cursor-based typed binary I/O. Both
default to little endian and support byte, signed byte, bool, short, unsigned
short, int, unsigned int, long, float, double, raw bytes, and UTF-8 strings.
They also support `align(width)`; the builder can `writeZeroes`, while the
reader can `peekByte` and `skip`.

`TextEncoding` supports `Utf8`, `Utf16LE`, `Utf16BE`, `Latin1`,
`Windows1252`, `CP437`, and `Ascii`. Use fallible `writeText`/`readText` when
loss is unacceptable, or `writeTextLossy`/`readTextLossy` for replacement
behavior. `build()` returns `readonly byte[]` and resets the builder.

## `std/fs`

```doof
import {
  FileInfo, IoError, readText, readBlob, writeText, writeBlob,
  appendText, appendBlob, metadata, readDir, mkdir, remove, rename, copy,
  readTextResource, readBlobResource, readResourceDir,
  readBlockStream, readLineStream, readResourceBlockStream,
  writeBlobStream, writeLineStream,
} from "std/fs"
```

Fallible operations return `Result<..., IoError>`. `FileInfo` contains `name`,
`kind: EntryKind`, `size: long`, and `modifiedAt: Instant`. `exists`, `isFile`,
and `isDirectory` are boolean probes. Resource variants resolve through
`std/path.resourcePath` and read bundled `doof.json` resources.

`readBlockStream`/`readBlobStream` yield byte chunks; `readLineStream` decodes
UTF-8 lines across chunk boundaries. Resource equivalents are available.
`writeBlobStream` and `writeLineStream` consume streams without buffering the
whole input.

## `std/json`

```doof
import { parseJsonValue, parseJsonObject, formatJsonValue } from "std/json"
```

- `parseJsonValue(text): Result<JsonValue, string>` parses any JSON value.
- `parseJsonObject(text): Result<JsonObject, string>` rejects non-object roots.
- `formatJsonValue(value): string` emits compact JSON.

Integral numbers become `int` or `long` when representable; fractional and
exponent forms become `double`. Parse errors include line and column.

## `std/path`

```doof
import {
  absolute, homeDirectory, tempDirectory, dataDirectory, cacheDirectory,
  currentWorkingDirectory, setCurrentWorkingDirectory,
  resourcesDirectory, resourcePath,
  join, dirname, basename, stem, extension, isAbsolute,
} from "std/path"
```

`join(parts: string[])` and the basename/dirname/stem/extension helpers operate
on POSIX path strings and normalize `.` and `..` without filesystem access.
Directory discovery and `absolute` return `Result<string, string>` where the OS
can fail. `dataDirectory(appId)` and `cacheDirectory(appId)` optionally append
an application id. `resourcesDirectory` and `resourcePath` locate resources in
both development and packaged applications.

## `std/stream`

```doof
import { Chain, blobStreamToLineStream } from "std/stream"
```

`Chain<T>` implements `Stream<T>` and provides lazy `filter`, `map`, and `take`,
plus terminal `collect`. `blobStreamToLineStream` incrementally decodes UTF-8
byte chunks, correctly handling `\n`, `\r`, `\r\n`, split lines, and a final
unterminated line.

## `std/url`

```doof
import { parsePath, parseAuthority, parseQueryParams, Path, Authority, QueryParams, UrlError } from "std/url"
```

This package parses already-separated URL components; it does not parse,
resolve, normalize, or rebuild complete URLs.

- `parsePath` preserves absolute/relative form, duplicate separators, trailing
  separators, and `.`/`..`; percent-decoded `/` stays within its segment.
- `parseQueryParams` preserves order, duplicate names, and the difference
  between a missing value and an empty value. It decodes `+` as space.
- `parseAuthority` returns decoded `userinfo`, `host`, and optional `port`,
  including bracketed IPv6 hosts.

## `std/event`

```doof
import {
  Backpressure, SendError, ChannelSender, ChannelReceiver, createChannel,
  Timer, setTimeout, setInterval, runMainEventLoop, drainMainEventLoop,
} from "std/event"
```

`createChannel<T>{capacity, highWater, lowWater, keepsAlive}` returns a one-way
`Tuple<ChannelSender<T>, ChannelReceiver<T>>`. `send(value, key?)` is
nonblocking and returns `Backpressure.None`/`.High` or `SendError.Full`/`.Closed`.
A repeated non-null key replaces the queued value in place. Register
`onMessage`, `onReady`, and `onClosed` handlers before pumping the main loop.

`setTimeout` and `setInterval` accept `Duration`, a handler, and optional
`keepsAlive`. `Timer.cancel()` reports whether it canceled an active timer.
`runMainEventLoop()` blocks until no keep-alive work remains;
`drainMainEventLoop()` runs ready handlers without blocking. Native UI/game
hosts can install a wake handler and own the thread that drains the loop.
