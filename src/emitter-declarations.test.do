import { Assert } from "std/assert"

import { createAnalyzer } from "./analyzer"
import { DeclarationIndex, declarationName, indexDeclarations, indexedClass, indexedDeclaration, indexedEnum, indexedInterface, indexedModule } from "./emitter-declarations"
import { SourceFile } from "./semantic"

function analyzeSameNamedEnums(): DeclarationIndex {
  analysis := createAnalyzer([
    SourceFile { path: "/main.do", source: "import { Mode as Level } from \"./level\"\nimport { Mode, Shape, Named } from \"./text\"\nfunction main(): int => 0" },
    SourceFile { path: "/level.do", source: "export enum Mode { Low, High }" },
    SourceFile { path: "/text.do", source: "export enum Mode { Quiet = \"quiet\" }\nexport class Shape { sides: int }\nexport interface Named { name: string }\nfunction helper(): int => 1" },
  ]).analyze("/main.do")
  return indexDeclarations(analysis)
}

export function testIndexesEveryProgramAndModule(): none {
  index := analyzeSameNamedEnums()
  Assert.equal(index.programs.length, 3)
  Assert.isTrue(indexedModule(index, "/text.do") != none)
  Assert.isTrue(indexedModule(index, "/missing.do") == none)
}

export function testSameNamedEnumsStayDistinctByModule(): none {
  index := analyzeSameNamedEnums()
  level := indexedEnum(index, "/level.do", "Mode") else { panic("missing /level.do Mode") }
  text := indexedEnum(index, "/text.do", "Mode") else { panic("missing /text.do Mode") }
  Assert.equal(level.variants[0].name, "Low")
  Assert.equal(text.variants[0].name, "Quiet")
  Assert.isTrue(indexedEnum(index, "/main.do", "Mode") == none)
}

export function testTypedLookupsUnwrapExportsAndRejectOtherKinds(): none {
  index := analyzeSameNamedEnums()
  shape := indexedClass(index, "/text.do", "Shape") else { panic("missing Shape") }
  Assert.equal(shape.name, "Shape")
  Assert.isTrue(indexedInterface(index, "/text.do", "Named") != none)
  Assert.isTrue(indexedClass(index, "/text.do", "Named") == none)
  Assert.isTrue(indexedEnum(index, "/text.do", "Shape") == none)
  Assert.isTrue(indexedClass(index, "/text.do", "Missing") == none)
}

export function testDeclarationKeepsExportWrapperAndNamesPrivateDeclarations(): none {
  index := analyzeSameNamedEnums()
  exported := indexedDeclaration(index, "/text.do", "Shape") else { panic("missing Shape statement") }
  Assert.equal(declarationName(exported), "Shape")
  helper := indexedDeclaration(index, "/text.do", "helper") else { panic("missing helper") }
  Assert.equal(declarationName(helper), "helper")
}
