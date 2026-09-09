import { Assert } from "std/assert"
import { safeModulePath } from "./extension"
export function testRepositoryEditorBundlePaths(): none {
  Assert.isTrue(safeModulePath("json/index.do"))
  for value of ["../x.do", "/x.do", "json//x.do", "json/./x.do", "json/../x.do", "json\\x.do", "index.cpp", ""] { Assert.isFalse(safeModulePath(value)) }
}
