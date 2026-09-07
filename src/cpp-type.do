import { ModuleNames } from "./emitter-names"
// Interned C++ representation nodes. IDs belong to one compilation registry.
// Native template names and std::variant remain ordinary C++ in the output.
import { StringBuilder } from "./string-builder"

export class CppType {
  readonly id: int
  readonly kind: string
  readonly name: string
  readonly owner: string
  readonly arguments: readonly CppType[]
}

// Forks share these immutable nodes and strings, never mutable lookup tables.
export class CppTypeSnapshot {
  readonly names: ModuleNames = ModuleNames {}
  readonly nodes: readonly Map<string, CppType> = {}
  readonly rendered: readonly Map<string, string> = {}
}

export class CppTypeRegistry {
  names: ModuleNames = ModuleNames {}
  base: CppTypeSnapshot = CppTypeSnapshot {}
  private nodes: Map<string, CppType> = {}
  private rendered: Map<string, string> = {}

  intern(kind: string, name: string = "", arguments: CppType[] = [], owner: string = ""): CppType {
    key := StringBuilder()
    key.append(kind + ":" + string(name.length) + ":" + name + ":" + string(owner.length) + ":" + owner)
    for argument of arguments { key.append(":" + string(argument.id)) }
    identity := key.drainToString()
    existing := nodes.get(identity) else {
      inherited := try? base.nodes.get(identity)
      if inherited != none { return inherited! }
      node := CppType { id: base.nodes.size + nodes.size, kind, name, owner, arguments: arguments.cloneReadonly() }
      nodes.set(identity, node)
      return node
    }
    return existing
  }

  atom(name: string, owner: string = ""): CppType {
    key := "atom:" + string(name.length) + ":" + name + ":" + string(owner.length) + ":" + owner
    existing := nodes.get(key) else {
      inherited := try? base.nodes.get(key)
      if inherited != none { return inherited! }
      node := CppType { id: base.nodes.size + nodes.size, kind: "atom", name, owner, arguments: [] }
      nodes.set(key, node)
      return node
    }
    return existing
  }

  render(type_: CppType, namespace: string): string {
    key := string(type_.id) + ":" + namespace
    text := rendered.get(key) else {
      inherited := try? base.rendered.get(key)
      if inherited != none { return inherited! }
      value := renderCppType(type_, namespace)
      rendered.set(key, value)
      return value
    }
    return text
  }
  // Copy once at the preparation boundary. Later registry writes cannot alter it.
  snapshot(): CppTypeSnapshot {
    allNodes := base.nodes.cloneMutable()
    for key, value of nodes { allNodes.set(key, value) }
    allRendered := base.rendered.cloneMutable()
    for key, value of rendered { allRendered.set(key, value) }
    return CppTypeSnapshot { names, nodes: allNodes.drainToReadonly(), rendered: allRendered.drainToReadonly() }
  }

  templateType(name: string, arguments: CppType[]): CppType => intern("template", name, arguments)
}

export function isReferenceVariant(type_: CppType): bool {
  if type_.kind != "template" || type_.name != "std::variant" { return false }
  for member of type_.arguments {
    if member.kind == "atom" && member.name == "std::monostate" { continue }
    if member.kind == "template" && member.name == "std::shared_ptr" { continue }
    return false
  }
  return true
}

export function renderCppType(type_: CppType, namespace: string = "", aliases: Map<int, string> = {}, rendered: Map<int, string> | none = none): string {
  if aliases.has(type_.id) { return try! aliases.get(type_.id) }
  if rendered != none && rendered!.has(type_.id) { return try! rendered!.get(type_.id) }
  value := renderCanonicalCppType(type_, namespace, aliases, rendered)
  if rendered != none { rendered!.set(type_.id, value) }
  return value
}

function renderCanonicalCppType(type_: CppType, namespace: string, aliases: Map<int, string>, rendered: Map<int, string> | none): string {
  if type_.kind == "atom" {
    if type_.owner == "" || namespace == "" || namespace == type_.owner { return type_.name }
    return "::" + type_.owner + "::" + type_.name
  }
  if type_.kind == "borrow" { return "const " + renderCppType(type_.arguments[0], namespace, aliases, rendered) + "&" }
  result := StringBuilder()
  if type_.kind == "callback" {
    result.append("doof::callback<" + renderCppType(type_.arguments[0], namespace, aliases, rendered) + "(")
    for index of 1..<type_.arguments.length {
      if index > 1 { result.append(", ") }
      result.append(renderCppType(type_.arguments[index], namespace, aliases, rendered))
    }
    result.append(")>")
  } else {
    result.append(type_.name + "<")
    for index of 0..<type_.arguments.length {
      if index > 0 { result.append(", ") }
      result.append(renderCppType(type_.arguments[index], namespace, aliases, rendered))
    }
    result.append(">")
  }
  return result.drainToString()
}
