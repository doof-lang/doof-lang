# Doof Standard Library Overview

Standard packages use `std/<name>` import paths and need no `doof.json`
dependency entry. Each compiler release ships an indexed offline bundle that
is authoritative for standard package availability. `DOOF_STDLIB_ROOT`
deliberately overrides that bundle with local packages.

Prefer the installed bundle for application work. Set `DOOF_STDLIB_ROOT` only
when testing local stdlib changes, and point it at the directory whose immediate
children are package folders such as `fs/`, `http/`, and `time/`. In a stdlib
checkout, README and `docs/API.md` files explain intent while exported
declarations in `index.do` are the exact callable surface.

## Package Index

| Import | Purpose |
| --- | --- |
| `std/apple-intelligence` | Apple FoundationModels sessions and reflected tools |
| `std/archive` | In-memory ZIP plus raw deflate/inflate and CRC-32 |
| `std/assert` | Source-aware test assertions |
| `std/blob` | Binary readers/builders and text codecs |
| `std/cli` | Declarative command-line argument parsing to `JsonObject` |
| `std/console` | Synchronous native terminal prompts and numbered choices |
| `std/crypto` | Digests, HMAC, secret storage, encodings, UUID, JWT |
| `std/csv` | Strict CSV parsing and generation with source locations |
| `std/dom` | Typed live browser DOM, canvas, and WebGL APIs for Wasm |
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
| `std/parse` | Strict boolean and numeric string parsing with typed errors |
| `std/path` | POSIX path strings plus app/resource directory discovery |
| `std/postgres` | `libpq` PostgreSQL wrapper with prepared statements and row streams |
| `std/random` | Secure random doubles and integers/ranges |
| `std/regex` | Reusable PCRE2 regular expressions |
| `std/sqlite` | SQLite wrapper with prepared statements and row streams |
| `std/stream` | Lazy stream combinators and byte-to-line adaptation |
| `std/string` | Efficient string construction, joining, and line splitting |
| `std/time` | Durations, instants, calendars, zones, sleep, and stopwatch metrics |
| `std/ts` | Erasable TypeScript and TSX-to-JavaScript transformation |
| `std/url` | Lossless parsing of URL path, query, and authority components |
| `std/webshell` | WebKit app shell and JSON bridge for macOS/iOS |
| `std/xml` | Strict practical XML document parsing and generation |
| `std/zstd` | One-shot and streaming Zstandard compression |

## Selection Notes

- `std/path` manipulates path strings; `std/fs` touches the filesystem.
- `std/string` handles in-memory text composition. Use `std/csv` or `std/xml`
  when the format has quoting, escaping, or structural rules.
- `std/cli` parses existing argv tokens; `std/console` interactively reads a
  terminal. Keep interactive prompts out of non-interactive tools and tests.
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
- `std/dom` targets browser Wasm. `std/webshell` hosts HTML in native WebKit;
  `std/game` owns a native Metal-backed render loop.

## Cross-package conventions

- Most I/O, parsing, networking, database, and platform operations return
  `Result`; propagate expected failures with `try`, translate them at an API
  boundary, or handle them with declaration-`else`/`case`.
- Byte APIs use `readonly byte[]`. `std/blob` is the bridge between typed bytes
  and text; `std/fs`, HTTP bodies, compression, archives, crypto, and images all
  use compatible byte values.
- `JsonValue` is the interchange type for JSON, CLI decoding, JavaScript,
  reflected tools, and several app bridges. Prefer a typed class's generated
  `fromJsonValue` at application boundaries.
- Streams are pull-based and lazy. Consume them once, surface per-item failures,
  and keep owning handles alive until iteration ends.
- Directory and resource helpers can fail even when string manipulation cannot.
  Do not use `try!` for user-controlled paths or environmental failures.
