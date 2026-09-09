import { Assert } from "std/assert"
import { DebugRow } from "./model"
import { isStringArray, stringArrayStorage, collectionChildren, variableLabel } from "./collection-presentation"

export function testStringArrayPresentationFlattensStorageAndPreservesRawRows(): none {
  element := DebugRow { key: "a/p/0", label: "[0] = \"工具\"", data: { name: "[0]", value: "\"工具\"" } }
  pointer := DebugRow { key: "a/p", label: "pointer = 0x123", data: { name: "pointer", variablesReference: 2 }, children: [element] }
  array := DebugRow { key: "a", label: "arguments = 0x456", data: {
    name: "arguments", "type": "const std::__1::shared_ptr<std::__1::vector<std::__1::basic_string<char> > > &", value: "0x456 size=1 strong=1 weak=0",
  }, children: [pointer] }
  Assert.equal(isStringArray(array), true)
  Assert.equal(variableLabel(array, false), "arguments : string[] · 1 item")
  Assert.equal(variableLabel(array, true), array.label)
  Assert.equal(collectionChildren(array, false)[0], element)
  Assert.equal(collectionChildren(array, true)[0], pointer)
  Assert.equal(array.children[0], pointer)
}

export function testStringArrayPresentationHandlesEmptyUnknownAndOtherTypes(): none {
  array := DebugRow { key: "a", label: "native", data: { name: "values", "type": "std::shared_ptr<std::vector<std::string> >", value: "size=0" } }
  Assert.equal(variableLabel(array, false), "values : string[] · 0 items")
  Assert.equal(collectionChildren(array, false).length, 0)
  broken := DebugRow { key: "b", label: "native", data: { name: "values", "type": "std::shared_ptr<std::vector<std::string> >", value: "size=error: unreadable" } }
  Assert.equal(variableLabel(broken, false), "values : string[]")
  for typeName of ["std::shared_ptr<std::vector<int>>", "std::shared_ptr<std::vector<std::string_view>>", "UserStringArray", "std::string"] {
    row := DebugRow { key: "other", label: "original", data: { "type": typeName } }
    Assert.equal(isStringArray(row), false)
    Assert.equal(variableLabel(row, false), "original")
  }
}
