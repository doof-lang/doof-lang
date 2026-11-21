# Building Runnable Applications

How `doof.json` turns Doof sources into a command-line executable, a macOS or
iOS app bundle, or a WebAssembly library, and how `doof build`, `run`, and
`package` use it. `docs/packages.md`, `docs/cli.md`, and `spec/11-modules.md`
are authoritative; `src/package-manifest.do` and `src/project.do` are the
parsers.

## Project discovery

- A package is a directory containing `doof.json`. Commands walk up from the
  given path to the nearest manifest; `<path>` defaults to `.`.
- Passing a directory (or nothing) builds `build.entry` (default `main.do`).
  Passing an explicit `.do` file overrides `build.entry`.
- Without a manifest, commands need an explicit `.do` file:
  `doof run tool.do`, or `doof tool.do args...` / a `#!/usr/bin/env doof`
  shebang for scripts.
- The entry module is executable when it declares `main()` (any of
  `(): none`, `(): int`, `(arguments: string[]): none|int`) or has top-level
  statements (a script entry, with implicit `arguments`). It must not export
  `main`.

## Minimal command-line application

```json
{
  "name": "greeter",
  "version": "0.1.0",
  "build": { "entry": "main.do" }
}
```

```doof check main.do
function main(arguments: string[]): int {
    if arguments.length == 0 {
        println("usage: greeter <name>")
        return 2
    }
    println("Hello, ${arguments[0]}!")
    return 0
}
```

```bash
doof run . -- Ada          # build (debug) and launch from the package root
doof build .               # build/greeter
doof package .             # optimized dist/greeter plus resources
```

- The executable is named after `name` (`/` and `\` become `-`; Windows adds
  `.exe`). With no `name`, the package directory name is used.
- `doof build` writes generated C++, objects, and the executable to
  `build.buildDir` (default `build`); `-o <dir>` overrides it.
- `doof run` builds silently, then launches with the package root as the
  working directory. Arguments after `--` reach the program verbatim.
- `doof package` uses a separate release graph (`build/release`) with
  optimization and LTO, and writes the artifact to `build.package.distDir`
  (default `dist`) or `--distdir`.
- `doof test <path>` ignores `main` and runs exported test functions from
  `*.test.do` files; see the testing reference.

## Manifest field reference

Only these keys are read. **Unknown keys are silently ignored**, so a typo
such as `"distDirectory"` (instead of `build.package.distDir`) or a top-level
`"entry"` (instead of `build.entry`) quietly has no effect.

| Key | Meaning |
| --- | --- |
| `name` | Package name: executable name, generated C++ namespace, default bundle id/title |
| `version` | Default `"1.0"`; used for app bundle versions and package archive names |
| `build.entry` | Entry module, default `"main.do"` |
| `build.buildDir` | Build directory, default `"build"`; also holds `.doof.lock` |
| `target` or `build.target` | `"macos-app"`, `"ios-app"`, or `"wasm"`; omit for a console executable. `--target` overrides |
| `resources` or `build.resources` | Files copied beside the executable or into the app bundle (below) |
| `dependencies` | `{ "<prefix>": { "path": "../dir" } }` local Doof packages only |
| `build.native` | Native C/C++ inputs and per-platform fragments (below) |
| `executable` / `build.executable` | App bundle executable name (app targets only; default `name`) |
| `id` / `build.id` | App bundle identifier shorthand |
| `title` / `build.title` | App display name shorthand |
| `icon` / `build.icon` | PNG app icon inside the package |
| `build.macosApp` | macOS bundle settings (below) |
| `build.iosApp` | iOS bundle settings (below) |
| `build.package` | `distDir`, plus `macos` / `ios` signing settings |
| `observe.ui` | Directory with `index.html` that replaces the `doof observe` UI |

Rejected legacy keys with explicit diagnostics: `externalDependencies`,
`resolutions`, `policy`, dependency `url`/`ref`/`commit`, and
`build.stdlib`. Standard packages (`std/...`) never need a dependency entry.

## Dependencies

```json
{
  "name": "app",
  "dependencies": {
    "shared-models": { "path": "../shared-models" }
  }
}
```

```doof
import { User } from "shared-models/user"
```

The key becomes the import prefix. Doof never fetches remote packages; prepare
third-party inputs outside the compiler and reference them by local path.

## Resources

Resources are copied beside a console executable (in `build/`, or `dist/` for
`package`), or into an app bundle's resources directory. Read them at runtime
with `std/fs` `readTextResource` / `readBlobResource` /
`readResourceBlockStream`, or get a filesystem path with
`std/path.resourcePath`. These resolve the same way in development builds and
packaged apps, independent of the working directory.

Each entry is a string or `{ "from": ..., "to": ... }`. `from` must stay
inside the package. A string keeps its package-relative path: a file or
directory lands at the same path below the resource root. In the object
form, `to` is a **destination directory** relative to the resource root
(`"."` or `""` means the root).

| Entry | Lands at |
| --- | --- |
| `"config/defaults.json"` (a file) | `config/defaults.json` |
| `"templates"` (a directory) | `templates/...` |
| `{ "from": "art/logo.png", "to": "." }` | `logo.png` |
| `{ "from": "web", "to": "site" }` | `site/...` (directory contents) |

```json
{
  "name": "report-tool",
  "resources": ["templates", "config/defaults.json"]
}
```

```doof check
import { readTextResource } from "std/fs"
import { parseJsonObject } from "std/json"

function main(): none {
    defaults := parseJsonObject(readTextResource("config/defaults.json")!)!
    header := readTextResource("templates/header.txt")!
}
```

App bundle resources (macOS/iOS) also accept `*` / `**` globs. Matches keep
their path relative to the glob's base directory, below `to`, or below that
base directory's own path for a string glob (`"web/*.html"` lands in `web/`).
A pattern matching nothing is an error. Duplicate destinations are rejected.

`doof run` resynchronizes edited, added, or removed resources before each launch.

## Native inputs (`build.native`)

```json
{
  "name": "native-app",
  "build": {
    "native": {
      "includePaths": ["native"],
      "sourceFiles": ["native/clock.cpp"],
      "extraCopyPaths": ["native/clock.hpp"],
      "defines": ["APP_FEATURE=1"],
      "compilerFlags": [],
      "linkerFlags": [],
      "libraryPaths": [],
      "linkLibraries": ["z"],
      "pkgConfigPackages": ["libpng"],
      "macos": { "frameworks": ["CoreFoundation"] },
      "linux": { "linkLibraries": ["pthread"] },
      "windows": { "linkLibraries": ["ws2_32"] }
    }
  }
}
```

- Paths (`includePaths`, `sourceFiles`, `libraryPaths`, `extraCopyPaths`) are
  package-relative. `extraCopyPaths` copies headers that `import class ... from
  "./x.hpp"` needs into the build directory.
- Platform fragments (`macos`, `linux`, `windows`, `iosSimulator`, `iosDevice`,
  `wasm`) append to the base lists for the matching target.
- `pkgConfigPackages` are mandatory; use `optionalPkgConfigPackages`
  (`name`, `define`, `probeSource`, optional `minimumVersion`) for optional
  capabilities. See the modules-and-interop reference.
- `build.native.vendor` (building a bundled `vendor/` tree) is reserved for
  standard packages.

## macOS application (`"target": "macos-app"`)

```json
{
  "name": "notes",
  "version": "1.2.0",
  "target": "macos-app",
  "executable": "Notes",
  "icon": "assets/icon.png",
  "resources": [{ "from": "assets/help", "to": "help" }],
  "build": {
    "macosApp": {
      "bundleId": "com.example.notes",
      "displayName": "Notes",
      "category": "public.app-category.productivity",
      "minimumSystemVersion": "12.0",
      "infoPlist": { "NSAppleEventsUsageDescription": "Automates exports." },
      "embeddedLibraries": [{ "library": "libpng16.16.dylib" }]
    },
    "package": {
      "macos": {
        "signing": "developer-id",
        "sandbox": true,
        "entitlements": "notes.entitlements",
        "notaryProfile": "notes-notary"
      }
    }
  }
}
```

- `doof build .` assembles `build/Notes.app`; `doof run .` builds and launches
  it. Use `std/appkit` (`runApp(window)`) for the UI.
- Defaults: executable = `name`, `bundleId` = `dev.doof.<sanitized name>`,
  `displayName` = `name`, `version` = package `version`, `category` =
  `public.app-category.developer-tools`, `minimumSystemVersion` = `11.0`.
- Top-level `executable`, `id`, `title`, `icon` take precedence over the nested
  `bundleId` / `displayName` / `icon`.
- `icon` must be a PNG inside the package; Doof generates the `.icns`.
- `infoPlist` adds custom keys. Doof-managed keys (`CFBundleIdentifier`,
  `CFBundleExecutable`, `CFBundleShortVersionString`, `LSMinimumSystemVersion`,
  `NSPrincipalClass`, and so on) are rejected.
- `embeddedLibraries` entries take exactly one of `library` (a linked library
  file name to copy into `Contents/Frameworks`) or `path` (a package-local
  `.dylib`, `.so`, or `.framework`).
- `doof package .` signs (default `developer-id`; `ad-hoc` for local use),
  verifies, and writes `dist/Notes-1.2.0-macos.zip`. CLI flags
  `--macos-signing`, `--macos-sign-identity`, `--macos-sandbox`,
  `--macos-entitlements`, and `--macos-notary-profile` override the manifest.
- With `developer-id` signing and a `notaryProfile`, the package is submitted
  to Apple's notary service, must be `Accepted`, is stapled, passes a
  Gatekeeper (`spctl`) assessment, and the zip is rebuilt with the ticket.
  Create the profile once with `xcrun notarytool store-credentials
  notes-notary`; `DOOF_MACOS_NOTARY_PROFILE` also sets it. Without a profile
  the app is signed but unnotarized and `doof package` warns that Gatekeeper
  will block downloaded copies. Ad-hoc bundles are never notarized.

## iOS application (`"target": "ios-app"`)

```json
{
  "name": "field-notes",
  "version": "1.0.0",
  "target": "ios-app",
  "executable": "FieldNotes",
  "build": {
    "iosApp": {
      "bundleId": "com.example.fieldnotes",
      "displayName": "Field Notes",
      "minimumDeploymentTarget": "16.0"
    },
    "package": {
      "ios": { "identity": "Apple Development", "provisioningProfile": "profiles/dev.mobileprovision" }
    }
  }
}
```

```bash
doof run . --ios-destination simulator
doof run . --ios-destination device --ios-device "My iPhone"
doof package . --ios-destination device
```

- Uses `std/uikit` (`runApp(screen)`); the compiler generates the app shell.
- `iosApp` supports `bundleId`, `displayName`, `version`, `icon`,
  `minimumDeploymentTarget` (default `16.0`), `infoPlist`, and
  `embeddedLibraries`, with the same precedence and managed-key rules as macOS.
- Device builds and packages need a signing identity and provisioning profile:
  `build.package.ios`, `DOOF_IOS_SIGN_IDENTITY` /
  `DOOF_IOS_PROVISIONING_PROFILE`, or `--ios-sign-identity` /
  `--ios-provisioning-profile` (CLI wins).

## WebAssembly library (`"target": "wasm"`)

```json
{ "name": "pricing", "build": { "target": "wasm", "entry": "lib.do" } }
```

The entry is a declarative library. Exported top-level functions become
`doof_export_<name>` JSON-over-C-ABI exports, and the build produces
`build/pricing.wasm`. Script statements and `main` arguments are unavailable.
Without a manifest, use `doof build lib.do --target wasm`. Requires `em++`.

## Several executables in one package

A manifest has one `build.entry`. Build other entry modules by passing the
file explicitly; they share the manifest's dependencies, resources, and native
inputs:

```bash
doof run tools/migrate.do
doof build tools/seed.do
```

## Troubleshooting

- A manifest setting seems to have no effect: check the key spelling and
  nesting against the table above, since unknown keys are ignored.
- `Invalid doof.json at ...: <field> must stay within the package root`:
  resource `from`, `icon`, `distDir`, entitlements, and profiles cannot point
  outside the package.
- Missing resource at runtime: inspect `build/` (or the bundle's
  `Contents/Resources`). A `{from, to}` file lands at `<to>/<file name>`, not
  at `to` itself.
- Another command is holding the lock (`build/.doof.lock`): commands for the
  same project serialize and wait. Never delete the lock file.
