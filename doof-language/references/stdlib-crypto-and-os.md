# Standard CLI, Crypto, Logging, Math, Random, and OS APIs

## `std/cli`

```doof
import { CliSpec, CliArgs, CliError } from "std/cli"
```

Build a mutable fluent schema with `CliSpec.create(program, description)`, then
add `flag`, `option`, and `positional` entries. `parse(args)` returns a flat
`JsonObject` in `CliArgs.value`: flags are booleans, ordinary options are
strings, repeatable options are string arrays, and free positionals are stored
under `_`. Decode that object with a configuration class's
`fromJsonValue(value, true)`; `std/cli` does not convert numeric strings.

Parsing supports long/short options, `--name=value`, attached short values,
`--no-name`, and `--`. Errors contain both an actionable message and usage.

## `std/crypto`

```doof
import {
  SecretBytes, sha1, sha1String, sha1Hex, sha1HexString,
  sha256, sha256String, sha256Hex, sha256HexString, blobStreamToSha256,
  hmacSha256, hmacSha256Hex, hmacSha256Base64Url, timingSafeEqual,
  encodeHex, decodeHex, encodeBase64, decodeBase64,
  encodeBase64Url, decodeBase64Url, uuidV4,
  parseJwt, verifyJwtHs256, Jwt, JwtError,
} from "std/crypto"
```

- `SecretBytes.random(length)` and `SecretBytes.steal(data)` own sensitive
  bytes. `wipe()` clears native storage; `bytes()` returns an ordinary copy.
- HMAC and HS256 verification require `SecretBytes`; do not pass keys through
  strings. `randomBytes(length)` is an alias returning `SecretBytes`.
- `timingSafeEqual` avoids data-dependent early exit.
- Base64 decoders return `Result<readonly byte[], string>`; URL encoding is
  unpadded. `decodeHex` rejects odd length and non-hex characters.
- `parseJwt` only parses three segments. `verifyJwtHs256(token, key)` also
  requires `alg == "HS256"` and verifies the signature.

## `std/log`

```doof
import { ConsoleLogger, RollingFileLogger, LogLevel, Logger, setLogger, debug, info, warn, error, fatal } from "std/log"
```

Install one global `Logger` with `setLogger`. Without one, ordinary log calls
are no-ops; `fatal` still panics after attempting to log. Every `LogEntry`
contains level, message, structured `Map<string, LogValue>`, `@caller` source,
and `Instant` timestamp. Context values are primitive scalar values or `null`.

`ConsoleLogger` writes filtered lines to stderr. `RollingFileLogger(path, level,
maxBytes, maxAge, maxFiles)` rotates by size or age and exposes `flush()`.

## `std/math`

Exports `PI`, `TAU`, `E`; generic native math functions including trigonometry,
roots/powers/logs, rounding, classification, `abs`, `min`, `max`, and `clamp`;
and helpers `radians`, `degrees`, `lerp`, `approxEqual`, `mod`, and
`wrapRadians`.

## `std/random`

```doof
import { random, randomInt } from "std/random"
```

`random()` returns a secure random `double` in `[0, 1)`. `randomInt(limit)`
returns `0..<limit`; `randomInt(range)` respects inclusive/exclusive range
bounds. Empty ranges panic. This API is deliberately not seedable; use an
application-owned generator when deterministic tests or simulations matter.

## `std/os`

```doof
import { env, pid, platform, architecture, ExecOptions, Exec, ExecResult, run } from "std/os"
```

`env` returns `Result<string, string>`; `pid`, `platform`, and `architecture`
return process metadata. Use `Exec.spawn(command, args, options)` for streaming
control or `run(...)` for buffered completion.

`ExecOptions` controls `cwd`, environment overrides/inheritance, stdin,
stderr merging, inherited output, per-stream `maxOutputBytes`, and a
`Duration | null` timeout. `Exec` exposes stdout/stderr byte streams, stdin
writing/closing, `isRunning`, `wait`, and `terminate`. A timeout is enforced by
`run()` and `wait()`, not by an individual blocking stream read. Merge stderr
when only stdout will be drained to avoid pipe backpressure deadlocks.
