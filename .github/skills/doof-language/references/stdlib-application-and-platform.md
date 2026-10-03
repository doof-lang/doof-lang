# Standard Application, Scripting, and Apple Platform APIs

## `std/dom`

```doof
import { button, div, input, canvas, domDocument } from "std/dom"
```

For browser-Wasm applications, typed-tag constructors create live DOM elements
immediately. Place known handles with `appendTo`, `insertBefore`, `insertAfter`,
`replace`, and `unmount`; mutate them with fluent setters. String children are
always text nodes. Form controls expose typed properties and snapshot events;
callbacks may call `preventDefault` and propagation controls.

`canvas` exposes retained 2D and WebGL 2 contexts. WebGL shaders/programs,
buffers, textures, and matrices use opaque typed handles; compilation/linking
is fallible. The browser host must load the package's `doof-dom.js` adapter and
invoke exported Wasm entry points through it.

## `std/apple-intelligence`

```doof
import { AppleIntelligenceSession } from "std/apple-intelligence"
```

Creates a persistent Apple FoundationModels `LanguageModelSession` with
instructions and multi-turn `respond(prompt)`. `transcriptText()` returns the
native JSON string; `transcriptJson()` parses it to `SerialValue`.

`addTool(name, description, inputSchema, invoke)` registers a JSON tool.
`addTools<T: Reflectable>(tools)` derives tool names, descriptions, schemas, and
invocation from Doof description metadata. It requires macOS 26+, its SDK,
Apple Silicon, Apple Intelligence, and the Apple Swift/Clang toolchain.

## `std/js`

```doof
import { JsEngine, JsError, JsJsonHandler } from "std/js"
```

`JsEngine` is an isolated persistent QuickJS-NG context. Use `exec(source)` for
side effects, `eval(source)` for a `SerialValue`, `callJson(name, args)` to invoke
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
exposes `Result<SerialValue, string>` handlers to JavaScript as
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

## `std/appkit`

```doof
import { Button, Text, TextField, Window, runApp } from "std/appkit"

function main(): none {
  let count = 0
  window := <Window title="Counter" width=420 height=260>
    <Text value={(): string => "Count: ${count}"}/>
    <TextField label="Name" onChange={(name): none => println(name)}/>
    <Button title="Increment" onClick={(): none => { count += 1 }}/>
  </Window>
  window.show()
  runApp()
}
```

Native macOS interfaces built from typed tags. AppKit owns windows, controls,
focus, menus, dialogs, scrolling, and accessibility; `std/layout` owns view
geometry. Direct `Window` children form a column with 16-point padding and
8-point gaps; `Row`/`Column` accept `gap` and `grow`. Reactive text, enabled,
checked, and visibility state resynchronize after native actions and queued
`std/event` work. The package also provides tables and outline views, a code
editor, sheets and alerts, file dialogs (`openFile`, `saveFile`), toolbars, and
standard application menus. Objective-C and AppKit types stay private.

## `std/uikit`

```doof
import { Screen, Text, runApp } from "std/uikit"
```

UIKit screens for iPhone and iPad using the same retained-view, reactive-value,
and `std/layout` conventions as `std/appkit`. It provides `Screen`,
`BarButton`, `View`, `Row`, `Column`, `ScrollView`, `Spacer`, `Text`, `Button`,
and `TextEditor` with highlights and completions. Document import/export and
alerts on `Screen` are callback-based because UIKit presentation is
asynchronous. Build with `doof build app.do --target ios-app --ios-destination
simulator`; `runApp(screen)` attaches to the generated iOS shell.

## `std/layout`

```doof
import { LayoutEdges, LayoutNode, LayoutRect, LayoutStyle, layout } from "std/layout"
```

A renderer-independent, flex-inspired layout engine. Build a `LayoutNode` tree
with `LayoutStyle` (row/column direction, grow/shrink, gap, padding, absolute
positioning, constraints, alignment, overflow, `flexWrap`), call `layout(root, viewport)`
whenever styles, content, or the viewport change, then read `bounds()` for
painting and hit-testing. `measureLayout(root, constraints)` reports preferred
size without assigning rectangles; `scrollTo`/`scrollBy` update scroll placement
without rerunning flex sizing. It draws nothing and borrows Flexbox concepts
without promising browser-identical CSS behavior.

`LayoutStyle { flexWrap: .Wrap }` enables row or column wrapping; the default is
`.NoWrap`. `FlexWrap` exports those two values. Line breaks use initial sizes,
min/max constraints, margins, and `gap` before grow/shrink; flex distribution
and justification then apply per line. `gap` also separates lines. Lines use
natural cross sizes and start at the top/left, with children aligned or stretched
within each line. Reverse directions reverse the main axis within each line.
Flex factors are relative weights; tiny positive totals still participate.
`measureLayout` reports wrapped cross sizes under a bounded main axis; an
unbounded main axis forms one line. Measured children and nested wrapping
containers resolve cross sizes at their assigned main sizes, so callbacks may
run more than once and should return stable results for identical constraints.
Use a nonzero basis or preferred main size for useful wrapping breakpoints;
zero bases fit before growth. Column wrapping needs a bounded height. The
standard-library workspace provides `layout/samples/wrapping` for printed
geometry and `game/samples/layout` for a resizable wrapping card grid. Set
`DOOF_STDLIB_ROOT` to the workspace when running samples against local changes.
Wrap-reverse, align-content, and separate row/column gaps are not supported.
