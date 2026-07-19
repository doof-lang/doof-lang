# Doof Standard Library Overview

Standard packages use `std/<name>` import paths and need no `doof.json`
dependency entry. Each compiler release embeds an immutable catalog containing
the origin and exact commit of every package. `DOOF_STDLIB_ROOT` deliberately
overrides that catalog with mutable local packages; package output warns about
the override and provenance records it as mutable input.

## Package Index

| Import | Purpose |
| --- | --- |
| `std/apple-intelligence` | Apple FoundationModels sessions and reflected tools |
| `std/archive` | In-memory ZIP plus raw deflate/inflate and CRC-32 |
| `std/assert` | Source-aware test assertions |
| `std/blob` | Binary readers/builders and text codecs |
| `std/cli` | Declarative command-line argument parsing to `JsonObject` |
| `std/crypto` | Digests, HMAC, secret storage, encodings, UUID, JWT |
| `std/event` | Bounded channels, main-loop integration, and timers |
| `std/fs` | Files, directories, metadata, resources, and streams |
| `std/game` | Metal-backed game/app host, rendering, input, UI, assets, sound |
| `std/gzip` | One-shot and streaming gzip compression |
| `std/http` | Outbound HTTP, cookie utilities, and client WebSockets |
| `std/http-router` | Route patterns, fluent routing, static files, WebSocket routes |
| `std/http-server` | Inbound HTTP/1.1 and server WebSockets |
| `std/image` | Mutable RGBA images, views, resize, composite, encode/decode |
| `std/js` | Persistent QuickJS-NG engine with a JSON boundary |
| `std/json` | Parse and format `JsonValue`/`JsonObject` |
| `std/log` | Structured global logging with console and rolling-file sinks |
| `std/math` | Math constants, native functions, and numeric helpers |
| `std/multiplayer` | Apple local peer discovery, invitations, and messages |
| `std/os` | Environment/process information and child processes |
| `std/path` | POSIX path strings plus app/resource directory discovery |
| `std/postgres` | `libpq` PostgreSQL wrapper with prepared statements and row streams |
| `std/random` | Secure random doubles and integers/ranges |
| `std/regex` | Reusable PCRE2 regular expressions |
| `std/sqlite` | SQLite wrapper with prepared statements and row streams |
| `std/stream` | Lazy stream combinators and byte-to-line adaptation |
| `std/time` | Durations, instants, calendars, zones, sleep, and stopwatch metrics |
| `std/ts` | Erasable TypeScript and TSX-to-JavaScript transformation |
| `std/url` | Lossless parsing of URL path, query, and authority components |
| `std/webshell` | WebKit app shell and JSON bridge for macOS/iOS |
| `std/zstd` | One-shot and streaming Zstandard compression |

## Selection Notes

- `std/path` manipulates path strings; `std/fs` touches the filesystem.
- `std/url` parses already-separated URL components; it is not a full URL
  resolver. `std/http-router` consumes its `Path` type.
- `std/http` is the outbound client. Use `std/http-server` for listeners and
  `std/http-router` for dispatch and static files.
- `std/archive` handles ZIP containers and raw deflate. Use `std/gzip` or
  `std/zstd` for their framed compression formats.
- `std/random` returns ordinary random values. Use `std/crypto.SecretBytes` for
  keys and other sensitive bytes.
- `std/js` executes JavaScript; `std/ts` transforms TypeScript/TSX source but
  does not type-check or execute it.
