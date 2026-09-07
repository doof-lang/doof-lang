// Stable generated names for the Doof module graph.
//
// These names are derived from logical source paths, never from traversal
// order, so later split-module emission can preserve an ABI across builds.

/** Maps a logical source prefix to the owning package's public C++ namespace. */
export class ModuleNamespaceMapping {
  logicalPrefix: string
  packageName: string
  // Native files are materialized below this project-relative directory.
  outputRoot: string = ""
}

export class ModuleNames {
  readonly mappings: readonly ModuleNamespaceMapping[] = []
  readonly namespaces: readonly Map<string, string> = {}
}

export function prepareModuleNames(mappings: ModuleNamespaceMapping[], paths: string[] = []): ModuleNames {
  // Copy mapping records as well as the container before publishing the snapshot.
  records: ModuleNamespaceMapping[] := []
  for mapping of mappings {
    records.push(ModuleNamespaceMapping { logicalPrefix: mapping.logicalPrefix, packageName: mapping.packageName, outputRoot: mapping.outputRoot })
  }
  base := ModuleNames { mappings: records.drainToReadonly() }
  namespaces: Map<string, string> := {}
  for path of paths { namespaces.set(path, computeModuleNamespace(path, base)) }
  return ModuleNames { mappings: base.mappings, namespaces: namespaces.drainToReadonly() }
}

export function moduleStem(path: string, names: ModuleNames = ModuleNames {}): string {
  let normalized = path.replaceAll("\\", "/")
  mapping := namespaceMappingForPath(normalized, names)
  if mapping != none {
    let relativePath = normalized.substring(mapping!.logicalPrefix.length, normalized.length)
    while relativePath.startsWith("/") {
      relativePath = relativePath.substring(1, relativePath.length)
    }
    normalized = mapping!.packageName
    if relativePath != "" { normalized = normalized + "/" + relativePath }
  }
  // Keep this path-only until the Doof runtime grows string split and
  // indexing helpers. A bounded substring removes the logical root without
  // depending on string length inference in the Doof checker.
  withoutRoot := if normalized.startsWith("/") then normalized.substring(1, 1000000) else normalized
  result := withoutRoot.replaceAll("/", "_").replaceAll(".do", "")
    .replaceAll("-", "_").replaceAll(".", "_")
  return if result == "" then "module" else result
}

export function moduleNamespace(path: string, names: ModuleNames = ModuleNames {}): string {
  cached := names.namespaces.get(path) else { return computeModuleNamespace(path, names) }
  return cached
}

function computeModuleNamespace(path: string, names: ModuleNames = ModuleNames {}): string {
  mapping := namespaceMappingForPath(path, names)
  if mapping != none {
    let relativePath = path.substring(mapping!.logicalPrefix.length, path.length)
    while relativePath.startsWith("/") {
      relativePath = relativePath.substring(1, relativePath.length)
    }
    if relativePath.endsWith(".do") {
      relativePath = relativePath.substring(0, relativePath.length - 3)
    }
    let namespace = namespacePath(mapping!.packageName)
    if relativePath != "" { namespace = namespace + "::" + namespacePath(relativePath) }
    return namespace
  }
  namespace := "app_" + moduleStem(path, names) + "_"
  return namespace
}

/** Formats source paths embedded in runtime diagnostics and @caller values. */
export function moduleDiagnosticPath(path: string, stripExtension: bool, names: ModuleNames = ModuleNames {}): string {
  let normalized = path.replaceAll("\\", "/")
  mapping := namespaceMappingForPath(normalized, names)
  if mapping != none {
    normalized = normalized.substring(mapping!.logicalPrefix.length, normalized.length)
  }
  while normalized.startsWith("/") {
    normalized = normalized.substring(1, normalized.length)
  }
  if stripExtension && normalized.endsWith(".do") {
    normalized = normalized.substring(0, normalized.length - 3)
  }
  return if normalized == "" then "<module>" else normalized
}

/** Resolves a quoted source-relative native header into the emitted package tree. */
export function moduleNativeHeaderPath(modulePath: string, headerPath: string, names: ModuleNames = ModuleNames {}): string {
  if !headerPath.startsWith("./") && !headerPath.startsWith("../") { return headerPath }
  mapping := namespaceMappingForPath(modulePath, names)
  if mapping == none { return headerPath }

  let relativeModulePath = modulePath.substring(mapping!.logicalPrefix.length, modulePath.length)
  while relativeModulePath.startsWith("/") {
    relativeModulePath = relativeModulePath.substring(1, relativeModulePath.length)
  }
  components := relativeModulePath.split("/").cloneMutable()
  if components.length > 0 { ignoredModuleName := try! components.pop() }
  for component of headerPath.replaceAll("\\", "/").split("/") {
    if component == "" || component == "." { continue }
    if component == ".." {
      if components.length == 0 { return headerPath }
      ignoredParent := try! components.pop()
    } else {
      components.push(component)
    }
  }

  let result = mapping!.outputRoot
  for component of components {
    if result != "" { result = result + "/" }
    result = result + component
  }
  return result
}

function namespaceMappingForPath(path: string, names: ModuleNames = ModuleNames {}): ModuleNamespaceMapping | none {
  let selected: ModuleNamespaceMapping | none = none
  for mapping of names.mappings {
    if path == mapping.logicalPrefix || path.startsWith(mapping.logicalPrefix + "/") {
      if selected == none || mapping.logicalPrefix.length > selected!.logicalPrefix.length {
        selected = mapping
      }
    }
  }
  return selected
}

function namespacePath(path: string): string {
  components := path.replaceAll("\\", "/").split("/")
  let result = ""
  for component of components {
    if component == "" { continue }
    sanitized := namespaceComponent(component)
    if result == "" { result = sanitized }
    else { result = result + "::" + sanitized }
  }
  return if result == "" then "module" else result
}

function namespaceComponent(value: string): string {
  result := value.replaceAll("-", "_").replaceAll(".", "_")
  if result == "std" || result == "doof" || result == "main" { return result + "_" }
  return cppIdentifier(result)
}

export function moduleHeaderName(path: string, names: ModuleNames = ModuleNames {}): string {
  return moduleStem(path, names) + ".hpp"
}

export function moduleSourceName(path: string, names: ModuleNames = ModuleNames {}): string {
  return moduleStem(path, names) + ".cpp"
}

// One keyword policy for namespace components and emitted value identifiers.
export function cppIdentifier(name: string): string {
  if isCppKeyword(name) { return name + "_" }
  if name == "stdin" { return "stdin_" }
  if name == "stdout" { return "stdout_" }
  if name == "stderr" { return "stderr_" }
  return name
}

function isCppKeyword(name: string): bool {
  // Most identifiers are not keywords; only compare words of the same length.
  case name.length {
    2 -> {
      return name == "do" || name == "if" || name == "or"
    }
    3 -> {
      return name == "and" || name == "asm" || name == "for" || name == "int" ||
        name == "new" || name == "not" || name == "try" || name == "xor"
    }
    4 -> {
      return name == "auto" || name == "bool" || name == "case" || name == "char" ||
        name == "else" || name == "enum" || name == "goto" || name == "long" ||
        name == "this" || name == "true" || name == "void"
    }
    5 -> {
      return name == "bitor" || name == "break" || name == "catch" || name == "class" ||
        name == "compl" || name == "const" || name == "false" || name == "float" ||
        name == "or_eq" || name == "short" || name == "throw" || name == "union" ||
        name == "using" || name == "while"
    }
    6 -> {
      return name == "and_eq" || name == "bitand" || name == "delete" || name == "double" ||
        name == "export" || name == "extern" || name == "friend" || name == "inline" ||
        name == "not_eq" || name == "public" || name == "return" || name == "signed" ||
        name == "sizeof" || name == "static" || name == "struct" || name == "switch" ||
        name == "typeid" || name == "xor_eq"
    }
    7 -> {
      return name == "alignas" || name == "alignof" || name == "char8_t" || name == "concept" ||
        name == "default" || name == "mutable" || name == "nullptr" || name == "private" ||
        name == "typedef" || name == "virtual" || name == "wchar_t"
    }
    8 -> {
      return name == "char16_t" || name == "char32_t" || name == "continue" || name == "co_await" ||
        name == "co_yield" || name == "decltype" || name == "explicit" || name == "noexcept" ||
        name == "operator" || name == "register" || name == "requires" || name == "template" ||
        name == "typename" || name == "unsigned" || name == "volatile"
    }
    9 -> {
      return name == "consteval" || name == "constexpr" || name == "constinit" || name == "co_return" ||
        name == "namespace" || name == "protected"
    }
    10 -> {
      return name == "const_cast"
    }
    12 -> {
      return name == "dynamic_cast" || name == "thread_local"
    }
    13 -> {
      return name == "static_assert"
    }
    16 -> {
      return name == "reinterpret_cast"
    }
    _ -> { return false }
  }
}
