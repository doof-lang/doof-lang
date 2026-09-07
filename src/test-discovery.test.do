import { Assert as EditorAssert } from "std/assert"
import { Parser as EditorParser } from "./parser"
import { discoverModuleTests } from "./test-discovery"

export function testEditorDiscoveryUsesCompilerExportConvention(): none {
  program := EditorParser { source: "export function testOne(): none {}\nfunction testHidden(): none {}" }.parse()
  discovered := discoverModuleTests(program, "/project/main.test.do", "/project")
  EditorAssert.equal(discovered.tests.length, 1)
  EditorAssert.equal(discovered.tests[0].id, "main.test.do::testOne")
}

export function testEditorDiscoveryRetainsWholeFunctionRanges(): none {
  source := "// é\r\nexport function testOne(): none {\r\n  text := \"🌟\"\r\n}\r\nfunction helper(): none {}\r\nexport { helper as testAlias }"
  discovered := discoverModuleTests(EditorParser { source }.parse(), "/project/main.test.do", "/project")
  EditorAssert.equal(discovered.tests.length, 2)
  first := discovered.tests[0]
  EditorAssert.equal(source.substring(first.startOffset, first.endOffset), "function testOne(): none {\r\n  text := \"🌟\"\r\n}")
  alias := discovered.tests[1]
  EditorAssert.equal(source.substring(alias.startOffset, alias.endOffset), "function helper(): none {}")
  EditorAssert.isTrue(first.endOffset < alias.startOffset)
}
