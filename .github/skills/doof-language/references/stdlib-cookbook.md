# Doof Standard Library Cookbook

Use these recipes as composition patterns, not as substitutes for the
package-family references. Imports from `std/<name>` do not belong in
`doof.json`; only application dependencies and resources do.

## Recipes

- Error propagation and translation
- Typed CLI and interactive console input
- Packaged resources
- String building, CSV, and XML
- Streaming file transforms
- HTTP clients, servers, and routing
- SQLite typed rows
- Bounded child processes
- Streaming compression
- Time and timezone values
- Boundary-focused tests

## Choose an error strategy first

Use `try` when the callee's error type already matches the enclosing function.
Translate errors where package boundaries differ, and reserve `try!` for startup
invariants, tests, and other failures that truly make continued execution
invalid.

```doof
import { parseJsonValue } from "std/json"

class Config {
  readonly host: string
  readonly port: int
}

function decodeConfig(text: string): Result<Config, string> {
  try value := parseJsonValue(text)
  try config := Config.fromJsonValue(value)
  return Success { value: config }
}
```

When one operation returns a different error type, add useful context at that
boundary instead of flattening every error in advance.

```doof
import { readText } from "std/fs"

function loadConfig(path: string): Result<Config, string> {
  text := readText(path) else error {
    return Failure { error: "cannot read ${path}: ${error}" }
  }
  return decodeConfig(text)
}
```

## Build a typed command-line tool

Let `std/cli` validate argv shape, decode its flat `JsonObject` into a class,
then use `std/parse` for numeric strings. Print both the error and generated
usage for argv mistakes.

```doof
import { CliSpec } from "std/cli"
import { parseInt } from "std/parse"

class RawOptions {
  readonly verbose: bool = false
  readonly port: string = "8080"
  readonly input: string
}

function main(args: string[]): int {
  spec := CliSpec.create("serve", "Serve one input file.")
    .flag("verbose", "v", "Print request details")
    .option("port", "p", "PORT", "Listening port", false, "8080")
    .positional("input", "Input file")

  parsed := spec.parse(args) else error {
    println(error.message)
    println(error.usage)
    return 2
  }
  options := RawOptions.fromJsonValue(parsed.value, true) else error {
    println("invalid options: ${error}")
    return 2
  }
  port := parseInt(options.port) else error {
    println("--port must be a decimal integer: ${error}")
    return 2
  }

  if options.verbose {
    println("serving ${options.input} on ${port}")
  }
  return 0
}
```

Use `std/console.prompt` or `choose` only for an intentionally interactive
native program. EOF is a normal failure to handle, and `choose` returns a
zero-based index even though it displays one-based choices.

```doof
import { choose, prompt } from "std/console"

name := prompt("Name?") else error {
  println(error.message)
  return
}
color := choose("Color?", ["Red", "Green", "Blue"]) else error {
  println(error.message)
  return
}
println("${name} selected option ${color}")
```

## Load packaged resources safely

Declare resources in the application's `doof.json`, then read them through the
resource functions. This works in development and in packaged applications;
do not build a resource path relative to the current working directory.

```json
{
  "name": "example-app",
  "resources": ["templates", "config/defaults.json"]
}
```

```doof
import { readTextResource } from "std/fs"
import { parseJsonObject } from "std/json"

text := try! readTextResource("config/defaults.json")
defaults := try! parseJsonObject(text)
```

Use `std/path.resourcePath` when an API needs a filesystem path rather than
contents. It rejects normalized paths that escape the resource directory.

## Construct and split text without quadratic copying

Use `StringBuilder` inside loops, optionally reserve an estimated UTF-8 byte
capacity, and drain it when finished. Use `splitLines` when complete input is
already in memory; use `std/fs.readLineStream` for large files.

```doof
import { StringBuilder, join, splitLines } from "std/string"

builder := StringBuilder()
builder.reserve(1024)
for name of ["Ada", "Grace", "Linus"] {
  builder.appendLine("hello, ${name}")
}
report := builder.drainToString()

labels := join(["red", "green", "blue"], ", ")
lines := splitLines(report)
```

## Parse and write CSV

Use the CSV model instead of manual splitting: quoted fields can contain
delimiters and newlines. Report its byte index and one-based line/column to the
caller.

```doof
import { CsvDocument, CsvRow, parseCsv, stringifyCsv } from "std/csv"

input := "name,note\r\nAda,\"hello, world\""
document := parseCsv(input) else error {
  println("CSV ${error.line}:${error.column}: ${error.message}")
  return
}
println(document.row(1).field(1))

output := try! stringifyCsv(CsvDocument {
  rows: readonly [
    CsvRow { fields: readonly ["name", "score"] },
    CsvRow { fields: readonly ["Ada", "10"] },
  ]
})
```

## Read practical XML

Use `childElements()` to ignore comments/text while walking structure and
`textContent()` when mixed text and CDATA should be combined. Use checked
`attribute(name)` rather than assuming an attribute exists.

```doof
import { parseXml } from "std/xml"

document := parseXml("<catalog><book id=\"1\"><title>Doof</title></book></catalog>") else error {
  println("XML ${error.line}:${error.column}: ${error.message}")
  return
}

for book of document.root.childElements() {
  id := book.attribute("id") else error {
    println(error)
    continue
  }
  title := book.childElements()[0].textContent()
  println("${id}: ${title}")
}
```

The package deliberately rejects DOCTYPE, custom/numeric entities, processing
instructions, and namespace resolution. Choose a fuller XML implementation if
the input requires those features.

## Stream a large text transformation

`Chain` transformations are lazy. Passing the chain to `writeLineStream`
consumes it once without loading the complete input or output into memory.

```doof
import { readLineStream, writeLineStream } from "std/fs"
import { Chain } from "std/stream"

source := try! readLineStream("input.log")
selected := Chain<string> { source }
  .filter(=> it.contains("ERROR"))
  .map(=> it.trim())

try! writeLineStream("errors.log", selected)
```

Keep the resource behind a stream alive until iteration finishes. Database row
streams additionally contain `Result` items, so both creating and consuming the
stream can fail.

## Call an HTTP JSON API

Reuse one client, distinguish transport failure from HTTP status, then parse
and type-check the payload.

```doof
import { HttpClient, createClient, get } from "std/http"

class User {
  readonly id: int
  readonly name: string
}

function fetchUser(client: HttpClient, id: int): Result<User, string> {
  response := get(client, "https://example.test/users/${id}") else error {
    return Failure { error: error.message }
  }
  if !response.ok() {
    return Failure { error: "HTTP ${response.status}: ${response.statusText}" }
  }
  try json := response.getJsonValue()
  return User.fromJsonValue(json)
}

client := createClient()
user := try! fetchUser(client, 42)
```

HTTP 4xx and 5xx are successful transport results, so always inspect status.
Set request timeouts and redirect policy explicitly when defaults do not match
the operation.

## Serve routed HTTP

The server delivers each request through a bounded channel. Route it, respond
exactly once, and run the main event loop. A handler that never responds will
eventually produce a 504 according to `responseTimeoutMillis`.

```doof
import { createChannel, runMainEventLoop } from "std/event"
import { Request, Response, Server, ServerOptions } from "std/http-server"
import { Router, RouteMatch } from "std/http-router"

router := Router()
  .get("/health", (match: RouteMatch, request: Request): Response =>
    Response.jsonValue(200, { status: "ok" })
  )
  .get("/users/:id", (match: RouteMatch, request: Request): Response =>
    Response.jsonValue(200, { id: match.get("id") })
  )

(requests, receiver) := createChannel<Request>{
  capacity: 128,
  keepsAlive: true,
}
receiver.onMessage((request: Request): none => {
  response := router.handle(request) ?? Response.text(404, "not found")
  try! request.respond(response)
})

server := try! Server.listen{
  options: ServerOptions { host: "127.0.0.1", port: 8080 },
  requests,
}
println("listening on http://${server.host}:${server.port}")
runMainEventLoop()
try! server.close()
```

Use `Router.staticFiles` rather than joining decoded URL segments manually; its
path mapping rejects traversal and decoded separators. Choose channel capacity,
body limits, and timeouts from the service's load and memory budget.

## Query SQLite into typed values

Prepare reusable statements and remember that `query` is fallible twice: once
when creating the stream and once for each streamed row.

```doof
import {
  SqliteError, SqliteValue, open, close, executeSql,
  prepare, query, toJsonRow,
} from "std/sqlite"

class Todo {
  readonly id: long
  readonly title: string
}

function loadTodos(path: string): Result<Todo[], SqliteError> {
  try database := open(path)
  try statement := prepare(database, "SELECT id, title FROM todos ORDER BY id")
  try rows := query(statement)
  todos: Todo[] := []

  for item of rows {
    try row := item
    todo := Todo.fromJsonValue(toJsonRow(row), true) else error {
      try close(database)
      return Failure {
        error: SqliteError {
          stage: "read",
          code: 0,
          message: error,
          sql: none,
        }
      }
    }
    todos.push(todo)
  }

  try close(database)
  return Success { value: todos }
}
```

For a transaction spanning several calls, roll back on every failure path.
Prepared statements and row streams are connection-bound; close only after the
stream is fully consumed. PostgreSQL follows the same overall shape but uses
`$1`, `$2`, ... placeholders and requires libpq.

## Run a child process with bounded output

Pass the executable and argv separately; `std/os` does not invoke a shell.
Bound captured output for untrusted or potentially noisy children and set a
timeout. Merge stderr when consuming only one live stream.

```doof
import { ExecOptions, run } from "std/os"
import { Duration } from "std/time"

result := run(
  "/usr/bin/git",
  ["status", "--short"],
  ExecOptions {
    timeout: Duration.ofSeconds(10L),
    maxOutputBytes: 1_048_576L,
  },
) else error {
  println("git failed to run: ${error}")
  return
}

if result.exitCode != 0 {
  println("git exited with ${result.exitCode}")
}
if result.stdoutTruncated || result.stderrTruncated {
  println("child output was truncated")
}
```

## Compress files without unnecessary buffering

For small payloads, combine `readBlob`/`writeBlob` with the one-shot gzip or
zstd functions. For large payloads, feed `readBlockStream` through a compression
stream into `writeBlobStream`.

```doof
import { readBlockStream, writeBlobStream } from "std/fs"
import { GzipStream } from "std/gzip"

chunks := try! readBlockStream("archive.bin")
try! writeBlobStream("archive.bin.gz", GzipStream(chunks))
```

Use matching formats: `std/archive` handles ZIP and raw deflate,
`std/gzip` handles gzip framing, and `std/zstd` handles Zstandard frames.

## Treat time values by meaning

Use `Instant` for a moment in UTC, `Duration` for elapsed time, `DateTime` for a
timezone-free wall clock, and `ZonedDateTime` when both local fields and a zone
matter. Preserve either the instant or the local time deliberately during zone
changes.

```doof
import { DateTime, Duration, Instant, TimeZone } from "std/time"

deadline := Instant.now().plus(Duration.ofSeconds(30L))
sydney := try! TimeZone.lookup("Australia/Sydney")
localStart := try! DateTime.parse("2026-08-29T09:00:00")
meeting := localStart.atZone(sydney)

println(deadline.toISOString())
println(meeting.toISOString())
```

`Thread.sleep` blocks an OS thread. Use `std/event` timers when the application
already owns an event loop and work should remain responsive.

## Test code at the package boundary

- Use `std/assert` for value-rich diagnostics and leave its `@caller` argument
  implicit.
- Inject a console reader or mock an imported dependency instead of reading the
  real terminal, network, clock, or database in a unit test.
- Prefer in-memory SQLite (`open(":memory:")`) and deterministic byte/text
  fixtures.
- Test malformed JSON/CSV/XML, non-2xx HTTP status, stream item failures,
  truncation, timeouts, and resource-not-found behavior alongside happy paths.
