import { Assert } from "std/assert"
import { join } from "std/string"
import { checkedSpecExamples, diagnosticMismatch, expectedDiagnostics, rejectionMismatch, reportedDiagnostics } from "./corpus-checks"

export function testCorpusExpectedDiagnostics(): none {
  source := "// Invalid: two bounds.\n// expect-error: 5:5 Range bounds; got \"string\"\n  // expect-error: 5:10  Second  \nfunction f(): none {}\n"
  Assert.equal(join(expectedDiagnostics(source)!.cloneReadonly(), "|"), join(["5:5: Range bounds; got \"string\"", "5:10: Second"], "|"))
}
export function testCorpusExpectedDiagnosticsRejectsMissingAndMalformed(): none {
  let missing = false
  case expectedDiagnostics("function f(): none {}\n") {
    failure: Failure -> { missing = failure.error.contains("no expect-error") }
    success: Success -> {}
  }
  Assert.isTrue(missing)
  let malformed = false
  case expectedDiagnostics("// expect-error: Break outside loop\n") {
    failure: Failure -> { malformed = failure.error.contains("Malformed expect-error") }
    success: Success -> {}
  }
  Assert.isTrue(malformed)
}
export function testCorpusReportedDiagnosticsKeepOnlySampleErrors(): none {
  output := "/root/a.do:3:5: error: Break is only valid inside a loop\n/root/a.do:4:1: warning: Unused\n/root/b.do:1:1: error: Other file\nnote: context\n/root/a.do:7:2: error: Second\n"
  Assert.equal(join(reportedDiagnostics(output, "/root/a.do").cloneReadonly(), "|"), join(["3:5: Break is only valid inside a loop", "7:2: Second"], "|"))
}
export function testCorpusDiagnosticMismatch(): none {
  Assert.equal(diagnosticMismatch(["1:1: A"], ["1:1: A"]), "")
  Assert.stringContains(diagnosticMismatch(["1:1: A"], ["1:2: A"]), "reported:\n  1:2: A")
  Assert.stringContains(diagnosticMismatch(["1:1: A"], ["1:1: A", "2:1: B"]), "2:1: B")
}
export function testCorpusCheckedSpecExamplesSelectsOnlyMarkedFences(): none {
  markdown := "# Title\n\n```doof\nfragment(\n```\n\n```doof check\nx := 1\ny := 2\n```\n\n```doof check\nz := 3\n```\n"
  examples := checkedSpecExamples("spec/a.md", markdown)!
  Assert.equal(examples.length, 2)
  Assert.equal(examples[0].line, 8)
  Assert.equal(examples[0].source, "x := 1\ny := 2\n")
  Assert.equal(examples[1].line, 13)
  Assert.equal(examples[1].file, "spec/a.md")
}
export function testCorpusCheckedSpecExamplesWrapsBodyFences(): none {
  markdown := "```doof check body\nx := 1\nprintln(x)\n```\n\n```doof checkbody\nignored := 1\n```\n"
  examples := checkedSpecExamples("spec/a.md", markdown)!
  Assert.equal(examples.length, 1)
  Assert.equal(examples[0].line, 2)
  Assert.equal(examples[0].source, "function example(): none {\nx := 1\nprintln(x)\n}\n")
}
export function testCorpusCheckedSpecExamplesRejectsUnterminatedFence(): none {
  let rejected = false
  case checkedSpecExamples("spec/a.md", "```doof check\nx := 1\n") {
    failure: Failure -> { rejected = failure.error.contains("spec/a.md:2: unterminated") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
}
export function testCorpusRejectedSpecExamplesRecordMarkedLines(): none {
  markdown := "```doof reject\nx := 1\ny: string := 2  // ❌ Error\n```\n\n```doof reject body\nlet z = 1\nz = \"a\"  // ❌\n```\n"
  examples := checkedSpecExamples("spec/a.md", markdown)!
  Assert.equal(examples.length, 2)
  Assert.isTrue(examples[0].rejected)
  Assert.equal(examples[0].markedLines.length, 1)
  Assert.equal(examples[0].markedLines[0], 2)
  Assert.isTrue(examples[1].rejected)
  Assert.equal(examples[1].markedLines[0], 3)
  Assert.equal(examples[1].source, "function example(): none {\nlet z = 1\nz = \"a\"  // ❌\n}\n")
}
export function testCorpusRejectedSpecExampleRequiresMarker(): none {
  let rejected = false
  case checkedSpecExamples("spec/a.md", "```doof reject\nx := 1\n```\n") {
    failure: Failure -> { rejected = failure.error.contains("spec/a.md:2: doof reject fence has no line marked") }
    success: Success -> {}
  }
  Assert.isTrue(rejected)
}
export function testCorpusRejectionMismatch(): none {
  Assert.equal(rejectionMismatch([2, 4], ["2:5: First", "4:1: Second", "4:9: Cascade"]), "")
  Assert.equal(rejectionMismatch([2, 4], ["2:5: First"]), "line 4 is marked but reported no error")
  Assert.equal(rejectionMismatch([2], ["2:5: First", "3:1: Extra"]), "unmarked error 3:1: Extra")
}
