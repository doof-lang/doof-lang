// Manifest contract for optional, target-toolchain native capabilities.
import { join } from "std/path"

export class OptionalPkgConfigPackage {
  name: string
  define: string
  probeSource: string
  minimumVersion: string = ""
}

function stringField(object: SerialObject, name: string, context: string): Result<string, string> {
  value := object.get(name) else { return Failure(context + "." + name + " is required") }
  case value {
    text: string -> {
      if text == "" { return Failure(context + "." + name + " must not be empty") }
      return Success(text)
    }
    _ -> return Failure(context + "." + name + " must be a string")
  }
}

function identifier(value: string): bool {
  for index of 0..<value.length {
    character := value[index]
    letter := (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || character == '_'
    if !letter && !(index > 0 && character >= '0' && character <= '9') { return false }
  }
  return value != ""
}

/** Parses bounded package-local probes; does not resolve or acquire dependencies. */
export function parseOptionalPkgConfigPackages(
  fragment: SerialObject, manifestPath: string, root: string, fieldPath: string,
): Result<OptionalPkgConfigPackage[], string> {
  value := fragment.get("optionalPkgConfigPackages") else { return Success([]) }
  prefix := "Invalid doof.json at " + manifestPath + ": " + fieldPath + ".optionalPkgConfigPackages"
  values := value as readonly SerialValue[] else { return Failure(prefix + " must be an array") }
  let result: OptionalPkgConfigPackage[] = []
  for index of 0..<values.length {
    context := prefix + "[" + string(index) + "]"
    object := values[index] as SerialObject else { return Failure(context + " must be an object") }
    try name := stringField(object, "name", context)
    for position of 0..<name.length {
      character := name[position]
      if !((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') ||
        (character >= '0' && character <= '9') || character == '_' || character == '-' || character == '.' || character == '+') {
        return Failure(context + ".name must be a pkg-config package name, not an expression")
      }
    }
    if name.startsWith("-") { return Failure(context + ".name must not start with '-' ") }
    try define := stringField(object, "define", context)
    if !identifier(define) { return Failure(context + ".define must be a C identifier without a value") }
    try probe := stringField(object, "probeSource", context)
    path := join([root, probe])
    rootPrefix := if root.endsWith("/") then root else root + "/"
    if !path.startsWith(rootPrefix) || !path.endsWith(".cpp") {
      return Failure(context + ".probeSource must name a .cpp file within the package root")
    }
    let minimumVersion = ""
    if object.has("minimumVersion") {
      try version := stringField(object, "minimumVersion", context)
      for position of 0..<version.length {
        character := version[position]
        if !(character >= '0' && character <= '9') && character != '.' {
          return Failure(context + ".minimumVersion must contain only digits and dots")
        }
      }
      if version.startsWith(".") || version.endsWith(".") || version.contains("..") {
        return Failure(context + ".minimumVersion must be a dotted numeric version")
      }
      minimumVersion = version
    }
    result.push(OptionalPkgConfigPackage { name, define, probeSource: path, minimumVersion })
  }
  return Success(result)
}
