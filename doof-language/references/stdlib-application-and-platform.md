# Standard Application, Scripting, and Apple Platform APIs

## `std/apple-intelligence`

```doof
import { AppleIntelligenceSession } from "std/apple-intelligence"
```

Creates a persistent Apple FoundationModels `LanguageModelSession` with
instructions and multi-turn `respond(prompt)`. `transcriptText()` returns the
native JSON string; `transcriptJson()` parses it to `JsonValue`.

`addTool(name, description, inputSchema, invoke)` registers a JSON tool.
`addTools<T: Reflectable>(tools)` derives tool names, descriptions, schemas, and
invocation from Doof description metadata. It requires macOS 26+, its SDK,
Apple Silicon, Apple Intelligence, and the Apple Swift/Clang toolchain.

## `std/js`

```doof
import { JsEngine, JsError, JsJsonHandler } from "std/js"
```

`JsEngine` is an isolated persistent QuickJS-NG context. Use `exec(source)` for
side effects, `eval(source)` for a `JsonValue`, `callJson(name, args)` to invoke
a global, and `bindJson(name, handler)` to expose a synchronous Doof callback.
The boundary rejects non-JSON values, cycles, and non-finite numbers.

Constructor defaults are 64 MiB memory, 1 MiB stack, and 1000 ms timeout;
override them explicitly for trusted workloads that need more.

## `std/ts`

```doof
import { transpile, transpileTsx, TsError, TsxOptions } from "std/ts"
```

`transpile` removes erasable TypeScript while preserving byte positions with
spaces. It does not type-check, resolve imports, downlevel JavaScript, or read
`tsconfig.json`. Constructs requiring runtime emission (such as enums,
namespaces, and parameter properties) fail with `unsupported-syntax`.

`transpileTsx` emits the automatic JSX runtime, defaulting to React and allowing
`jsxImportSource` override. It preserves user-code line endings but not columns
or byte offsets and does not emit source maps.

## `std/webshell`

```doof
import {
  initWebShellApp, WebShellApp, WebShellOptions,
  installWebShellDialogs, configureWebShellMenus,
  installWebShellNotifications, installWebShellClipboard,
} from "std/webshell"
```

Hosts bundled HTML in native WebKit on macOS/iOS. `app.bind(name, handler)`
exposes `Result<JsonValue, string>` handlers to JavaScript as
`doof.call(name, params)`; `app.postEvent` feeds `doof.on` listeners and queues
events until the page is ready. `run()` is single-use and must own the macOS
main thread.

Optional installers expose native open/save dialogs, local notifications, and
plain-text clipboard through the bridge. macOS menus emit `menuCommand` events;
iOS accepts their configuration as a no-op. iOS save dialogs are not currently
implemented.

## `std/multiplayer`

```doof
import {
  MultiplayerConfig, MultiplayerRole, MultiplayerSession,
  MultiplayerEvent, MultiplayerEventKind, createMultiplayerSession,
} from "std/multiplayer"
```

The current Apple Multipeer Connectivity backend discovers local peers,
invites/connects them, and sends reliable UTF-8 messages. Configure a Bonjour
`serviceType`, protocol id/version, display name, host/client role, and event
capacity. `session.events` is a `ChannelReceiver<MultiplayerEvent>`; use
`onEvent`, `start`, `invite`, `send`, and `stop`. Events cover discovery,
invitations, connections, messages, validated protocol hellos, and errors.

## `std/game`

`std/game` is a macOS/iOS Metal-backed game and rich-app toolkit. Its major API
groups are:

- `initGameApp`, `GameApp`, `GameAppOptions`, and requested/continuous rendering
- `Renderer`, render-pass descriptors, cameras, matrices, colors, depth/blend,
  textures, shaders, and static/batched meshes
- keyboard, mouse/touch, controller, gestures, and queryable input state
- transforms, scene nodes, collision primitives, particles, skies, and helpers
- OBJ/glTF/GLB loading, bitmap fonts/text, retained panels/labels/buttons
- reusable decoded `Sound` plus sfxr-style generated effects

Use package-resource loaders for bundled assets. `Camera.screen()` uses logical
top-left coordinates; mesh helpers use counter-clockwise front faces. iOS uses
the generated UIKit app shell and maps single touch through mouse APIs; hardware
keyboard input is not currently exposed there.
