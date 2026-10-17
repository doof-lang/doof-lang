// Command-level language corpora: rejected sample programs and checked spec examples.
import { join as joinStrings } from "std/string"
import { exists } from "std/fs"
import { parseInt } from "std/parse"
import { erase, execute, files, path, read, require, text, write } from "./common"

readonly expectErrorPrefix = "// expect-error: "
readonly fencePrefix = "```doof "
readonly rejectionMarker = "❌"

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
  rejected: bool = false
  // Extracted-file line numbers carrying the rejection marker.
  markedLines: int[] = []
  // Named examples share a per-chapter directory so they can import each other.
  fileName: string = ""
}

class FenceMode {
  rejected: bool
  wrapped: bool
  fileName: string
}

// A checked fence opens with "```doof check" or "```doof reject", then an
// optional "body", then an optional relative ".do" file name.
function fenceMode(file: string, line: int, opener: string): Result<FenceMode | none, string> {
  if !opener.startsWith(fencePrefix) { return Success(none) }
  words := opener.substring(fencePrefix.length).split(" ")
  if words[0] != "check" && words[0] != "reject" { return Success(none) }
  let index = 1
  wrapped := index < words.length && words[index] == "body"
  if wrapped { index += 1 }
  let fileName = ""
  if index < words.length {
    fileName = words[index]
    index += 1
    location := file + ":" + string(line) + ": "
    try require(fileName.endsWith(".do") && !fileName.startsWith("/") && !fileName.contains(".."), location + "example file name must be a relative .do path: " + fileName)
  }
  try require(index == words.length, file + ":" + string(line) + ": malformed doof example fence: " + opener)
  return Success(FenceMode { rejected: words[0] == "reject", wrapped, fileName })
}

// Checked fences open with "```doof check" or "```doof reject"; other `doof`
// fences are signature outlines and are not checked. A body fence holds
// statements and is checked inside a function whose header occupies the first
// line of the extracted file. A reject fence must fail `doof check`, with
// errors on exactly its code lines marked ❌. A named fence such as
// "```doof check math.do" is written under that name beside the chapter's
// other named examples before any of them is checked.
export function checkedSpecExamples(file: string, markdown: string): Result<SpecExample[], string> {
  result: SpecExample[] := []
  lines := markdown.split("\n")
  let i = 0
  while i < lines.length {
    try parsed := fenceMode(file, i + 1, lines[i].trimEnd())
    mode := parsed else { i += 1; continue }
    start := i + 2
    body: string[] := []
    markedLines: int[] := []
    i += 1
    while i < lines.length && !lines[i].startsWith("```") {
      // A comment-only line may head a group of invalid lines without being one.
      if lines[i].contains(rejectionMarker) && !lines[i].trim().startsWith("//") { markedLines.push(body.length + if mode.wrapped then 2 else 1) }
      body.push(lines[i])
      i += 1
    }
    try require(i < lines.length, file + ":" + string(start) + ": unterminated doof example fence")
    try require(!mode.rejected || markedLines.length > 0, file + ":" + string(start) + ": doof reject fence has no line marked " + rejectionMarker)
    for existing of result {
      try require(mode.fileName == "" || existing.fileName != mode.fileName, file + ":" + string(start) + ": duplicate example file name " + mode.fileName)
    }
    source := joinStrings(body.cloneReadonly(), "\n") + "\n"
    result.push(SpecExample {
      file, line: start, source: if mode.wrapped then "function example(): none {\n" + source + "}\n" else source,
      rejected: mode.rejected, markedLines, fileName: mode.fileName,
    })
    i += 1
  }
  return Success(result)
}

// A rejected example must report errors on exactly its marked lines.
export function rejectionMismatch(markedLines: int[], reported: string[]): string {
  reportedLines: int[] := []
  for diagnostic of reported {
    line := parseInt(diagnostic.substring(0, diagnostic.indexOf(":"))) else { continue }
    if !reportedLines.contains(line) { reportedLines.push(line) }
  }
  problems: string[] := []
  for line of markedLines { if !reportedLines.contains(line) { problems.push("line " + string(line) + " is marked but reported no error") } }
  for diagnostic of reported {
    line := parseInt(diagnostic.substring(0, diagnostic.indexOf(":"))) else { continue }
    if !markedLines.contains(line) { problems.push("unmarked error " + diagnostic) }
  }
  return joinStrings(problems.cloneReadonly(), "\n")
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
  try markdownExampleChecks(root, compiler, stdlib, "spec", "build/spec-examples", "Spec examples")
  return markdownExampleChecks(root, compiler, stdlib, ".github/skills/doof-language", "build/skill-examples", "Skill examples")
}

// Checks every marked fence in the Markdown files under `source` (relative to
// root). Each Markdown file's examples share a directory under `output`.
function markdownExampleChecks(root: string, compiler: string, stdlib: string, source: string, output: string, label: string): Result<none, string> {
  corpus := path(root, source)
  work := path(root, output)
  try erase(work)
  environment: Map<string, string> := { DOOF_STDLIB_ROOT: stdlib }
  failures: string[] := []
  try names := files(corpus)
  let count = 0
  let rejectedCount = 0
  for name of names {
    if !name.endsWith(".md") { continue }
    try markdown := read(path(corpus, name))
    try examples := checkedSpecExamples(source + "/" + name, markdown)
    chapter := name.substring(0, name.length - 3)
    samples: string[] := []
    for example of examples {
      sample := path(path(work, chapter), if example.fileName == "" then "example-" + string(example.line) + ".do" else example.fileName)
      try write(sample, example.source)
      samples.push(sample)
    }
    for index of 0..<examples.length {
      example := examples[index]
      sample := samples[index]
      count += 1
      location := example.file + ":" + string(example.line)
      try checked := execute(compiler, ["check", sample], environment)
      checkOutput := text(checked.stdout).trimEnd()
      if !example.rejected {
        if checked.exitCode != 0 { failures.push(location + ": example does not check\n" + checkOutput) }
        continue
      }
      rejectedCount += 1
      if checked.exitCode == 0 { failures.push(location + ": rejected example was accepted"); continue }
      mismatch := rejectionMismatch(example.markedLines, reportedDiagnostics(checkOutput, sample))
      if mismatch != "" { failures.push(location + ": rejected example errors do not match its " + rejectionMarker + " lines (extracted-file lines)\n" + mismatch + "\n" + checkOutput) }
    }
  }
  try require(count > 0, "No doof check examples found in " + corpus)
  try require(failures.length == 0, label + " failed:\n" + joinStrings(failures.cloneReadonly(), "\n"))
  println(label + ": " + string(count) + " checked (" + string(rejectedCount) + " rejected as marked)")
  return Success()
}
