# Standard Networking APIs

## `std/http`

`std/http` is the outbound client. Apple targets use Foundation transports;
other targets use the pinned curl backend through the same API.

```doof
import {
  createClient, get, postJsonValue, send,
  HttpClient, HttpRequest, HttpResponse, HttpHeader, HttpError,
} from "std/http"
```

Reuse one `HttpClient`. `get`, `postJsonValue`, and `send` return
`Result<HttpResponse, HttpError>`; HTTP 4xx/5xx statuses are successful
transport results. `HttpRequest` controls method, URL, headers, bytes, timeout,
and redirects. Responses provide `ok`, case-insensitive `header`, `getBlob`,
`getText`, `getLineStream`, and `getJsonValue`.

Cookie utilities include `Cookie`, `SetCookie`, `parseCookieHeader`,
`renderCookieHeader`, `parseSetCookieHeader`, `renderSetCookieHeader`, and
`cookieValue`. They operate on explicit header values and do not maintain a jar.

`connectWebSocket(url, onEvent, options)` returns
`Result<WebSocketConnection, HttpError>`. Open, text, binary, writable, close,
and error events are posted to `onEvent` in order on the actor that created it.
Write with `sendText`, `sendBinary`, `ping`, and `close` on the connection.
Native reads pause once `WebSocketOptions.eventCapacity` events are posted but
unhandled; sends fail with a backpressure error once `outboundCapacity` writes
are queued, and `WebSocketWritable` reports the queue drained. An open
connection keeps `runMainEventLoop()` running.

## `std/http-server`

```doof
import { Request, Response, Server, ServerOptions } from "std/http-server"
import { runMainEventLoop } from "std/event"
```

Pass a request handler to `Server.listen{options, onRequest}`. The server
`tryPost`s each `Request` to it, so the handler runs in arrival order on the
actor that created it; create it inside an actor to serve requests there.
Complete every request with `request.respond(response)` or
`request.upgradeToWebSocket(connection)`. A full mailbox or retired owner
produces 503; an uncompleted request reaches `responseTimeoutMillis` and
produces 504. An open server keeps `runMainEventLoop()` running until `close()`.

`Request` exposes method/path/headers plus `getBlob`, `getText`, and
`getJsonValue`. `Response.empty`, `.blob`, `.text`, `.html`, `.jsonValue`, and
`.stream` create immutable responses. Streams use chunked transfer encoding.
Compression policy supports zstd and gzip, preferring zstd when both are
accepted.

`ServerOptions` includes host, port, body limit, idle timeout, response timeout,
and maximum requests per connection. HTTP/1.1 keep-alive and sequential
requests are supported. `createWebSocketConnection(onEvent, options)` builds
the connection passed to `upgradeToWebSocket`; it uses the same event-handler
shape as the outbound client and pauses socket reads at `eventCapacity`.

## `std/http-router`

```doof
import { Router, RouteMatch, compileRoutePattern, matchRoute, matchRoutePrefix } from "std/http-router"
```

Patterns contain static and named segments such as `/users/:id`.
`matchRoute` matches the whole `std/url.Path`; `matchRoutePrefix` also returns a
relative remaining path for sub-routing. Named parameters are retained in
`RouteMatch`.

`Router` provides HTTP verb helpers, any-method `route` prefix matching,
method-specific prefix routes, WebSocket routes, and `staticFiles`. `handle`
returns `none` when no path matches and a 405 response with `Allow` when only
the method fails. Normal HTTP handlers do not receive WebSocket upgrades.

Use `pathToFileSystemPath(root, path)` or
`RouteMatch.remainingFileSystemPath(root)` when mapping URLs to disk: these
reject decoded traversal and separators. Static-file helpers provide MIME
types, conservative cache control, ETags, Last-Modified, GET/HEAD handling, and
conditional 304 responses.

## `std/ssh`

```doof
import { connect, SshClient, SshConnectOptions, SshCommandResult, SftpClient } from "std/ssh"
```

- `connect` is `isolated` and blocking; call it from async or actor work, not
  a UI thread. It returns `Result<SshClient, string>`.
- Host-key verification is mandatory: supply `knownHostsPath` and/or
  `hostKeySha256` (64 hex digits). Authenticate with a password or
  `privateKeyPath`.
- `wait` (default ten seconds) retries only TCP availability; handshake,
  verification, and authentication failures return immediately.
- `client.run(command)` returns `SshCommandResult` with `exitStatus`, `stdout`,
  and `stderr`.
- `client.sftp()` opens the one shared SFTP session: `writeFile`, bounded
  `readFile` (16 MiB default), `listDirectory`, `makeDirectory`, `removeFile`,
  `removeDirectory`, and `rename`. Close it before the SSH client.
- Agent authentication, forwarding, and interactive channels are not provided.

## `std/wol`

```doof
import { wakeOnLan } from "std/wol"

wakeOnLan("aa:bb:cc:dd:ee:ff", "192.168.1.255")!
```

`wakeOnLan(mac, broadcast = "255.255.255.255", port = 9)` returns
`Result<none, string>`. Success confirms only local delivery of the datagram.
