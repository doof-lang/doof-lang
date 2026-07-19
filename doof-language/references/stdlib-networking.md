# Standard HTTP Client, Server, and Router APIs

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

`connectWebSocket(url, options)` returns a `WebSocketConnection` with bounded
`events: ChannelReceiver<WebSocketEvent>` and
`commands: ChannelSender<WebSocketCommand>`. Events cover open, text, binary,
writable, close, and errors; commands cover text/binary send, ping, and close.

## `std/http-server`

```doof
import { Request, Response, Server, ServerOptions } from "std/http-server"
import { createChannel, runMainEventLoop } from "std/event"
```

Create a `ChannelSender<Request>` and pass it to `Server.listen{options,
requests}`. Attach the application handler to the receiver and complete every
request with `request.respond(response)` or
`request.upgradeToWebSocket(connection)`. A full/closed channel produces 503;
an uncompleted request reaches `responseTimeoutMillis` and produces 504.

`Request` exposes method/path/headers plus `getBlob`, `getText`, and
`getJsonValue`. `Response.empty`, `.blob`, `.text`, `.html`, `.jsonValue`, and
`.stream` create immutable responses. Streams use chunked transfer encoding.
Compression policy supports zstd and gzip, preferring zstd when both are
accepted.

`ServerOptions` includes host, port, body limit, idle timeout, response timeout,
and maximum requests per connection. HTTP/1.1 keep-alive and sequential
requests are supported. The WebSocket API uses the same paired-channel shape as
the outbound client and applies inbound backpressure to socket reads.

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
returns `null` when no path matches and a 405 response with `Allow` when only
the method fails. Normal HTTP handlers do not receive WebSocket upgrades.

Use `pathToFileSystemPath(root, path)` or
`RouteMatch.remainingFileSystemPath(root)` when mapping URLs to disk: these
reject decoded traversal and separators. Static-file helpers provide MIME
types, conservative cache control, ETags, Last-Modified, GET/HEAD handling, and
conditional 304 responses.
