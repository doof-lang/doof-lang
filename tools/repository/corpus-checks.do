// Command-level language corpora: rejected sample programs and checked spec examples.
import { join as joinStrings } from "std/string"
import { exists } from "std/fs"
import { erase, execute, files, path, read, require, text, write } from "./common"

readonly expectErrorPrefix = "// expect-error: "
readonly checkedFence = "```doof check"

// Expected diagnostics are `// expect-error: <line>:<column> <message>` comments.
// Each is normalized to `<line>:<column>: <message>` for comparison.
export function expectedDiagnostics(source: string): Result<string[], string> {
  result: string[] := []
  for line of source.split("\n") {
    trimmed := line.trim()
    if !trimmed.startsWith(expectErrorPrefix) { continue }
    body := trimmed.substring(expectErrorPrefix.length).trim()
    space := body.indexOf(" ")
    try require(space > 0 && body.substring(0, space).contains(":"), "Malformed expect-error comment: " + trimmed)
    result.push(body.substring(0, space) + ": " + body.substring(space + 1).trim())
  }
  try require(result.length > 0, "Rejected sample declares no expect-error comments")
  return Success(result)
}

// Reported error lines have the form `<file>:<line>:<column>: error: <message>`.
export function reportedDiagnostics(output: string, file: string): string[] {
  result: string[] := []
  prefix := file + ":"
  for line of output.split("\n") {
    if !line.startsWith(prefix) { continue }
    rest := line.substring(prefix.length)
    marker := rest.indexOf(": error: ")
    if marker < 0 { continue }
    result.push(rest.substring(0, marker) + ": " + rest.substring(marker + ": error: ".length).trimEnd())
  }
  return result
}

export function diagnosticMismatch(expected: string[], reported: string[]): string {
  if expected.length == reported.length {
    let same = true
    for i of 0..<expected.length { if expected[i] != reported[i] { same = false } }
    if same { return "" }
  }
  return "expected:\n  " + joinStrings(expected.cloneReadonly(), "\n  ") + "\nreported:\n  " + joinStrings(reported.cloneReadonly(), "\n  ")
}

export class SpecExample {
  file: string
  line: int
  source: string
}

// Only fences opened with exactly "```doof check" are compile-checked; other
// `doof` fences may be fragments, signatures, or deliberately invalid code.
export function checkedSpecExamples(file: string, markdown: string): Result<SpecExample[], string> {
  result: SpecExample[] := []
  lines := markdown.split("\n")
  let i = 0
  while i < lines.length {
    if lines[i].trimEnd() != checkedFence { i += 1; continue }
    start := i + 2
    body: string[] := []
    i += 1
    while i < lines.length && !lines[i].startsWith("```") { body.push(lines[i]); i += 1 }
    try require(i < lines.length, file + ":" + string(start) + ": unterminated doof check fence")
    result.push(SpecExample { file, line: start, source: joinStrings(body.cloneReadonly(), "\n") + "\n" })
    i += 1
  }
  return Success(result)
}

export function falseNegativeChecks(root: string, compiler: string, stdlib: string): Result<none, string> {
  corpus := path(root, "tests/analyzer-false-negatives")
  work := path(root, "build/false-negatives")
  try erase(work)
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib }
  failures: string[] := []
  try names := files(corpus)
  let count = 0
  for name of names {
    if !name.endsWith(".do") || name.contains("/") { continue }
    count += 1
    sample := path(corpus, name)
    try source := read(sample)
    try expected := expectedDiagnostics(source)
    try checked := execute(compiler, ["check", sample], environment)
    reported := reportedDiagnostics(text(checked.stdout), sample)
    if checked.exitCode == 0 { failures.push(name + ": unexpectedly accepted"); continue }
    mismatch := diagnosticMismatch(expected, reported)
    if mismatch != "" { failures.push(name + ": diagnostics changed\n" + mismatch); continue }
    output := path(work, name)
    try emitted := execute(compiler, ["emit", sample, "-o", output], environment)
    if emitted.exitCode == 0 || exists(output) { failures.push(name + ": emission was not suppressed") }
  }
  try require(count > 0, "No rejected samples found in " + corpus)
  try require(failures.length == 0, "Rejected-sample corpus failed:\n" + joinStrings(failures.cloneReadonly(), "\n"))
  println("Rejected-sample corpus: " + string(count) + " samples rejected as expected")
  return Success()
}

export function specExampleChecks(root: string, compiler: string, stdlib: string): Result<none, string> {
  spec := path(root, "spec")
  work := path(root, "build/spec-examples")
  try erase(work)
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib }
  failures: string[] := []
  try names := files(spec)
  let count = 0
  for name of names {
    if !name.endsWith(".md") { continue }
    try markdown := read(path(spec, name))
    try examples := checkedSpecExamples("spec/" + name, markdown)
    for example of examples {
      count += 1
      location := example.file + ":" + string(example.line)
      sample := path(work, name.substring(0, name.length - 3) + "-" + string(example.line) + ".do")
      try write(sample, example.source)
      try checked := execute(compiler, ["check", sample], environment)
      if checked.exitCode != 0 { failures.push(location + ": example does not check\n" + text(checked.stdout).trimEnd()) }
    }
  }
  try require(count > 0, "No doof check examples found in " + spec)
  try require(failures.length == 0, "Spec examples failed:\n" + joinStrings(failures.cloneReadonly(), "\n"))
  println("Spec examples: " + string(count) + " checked")
  return Success()
}
