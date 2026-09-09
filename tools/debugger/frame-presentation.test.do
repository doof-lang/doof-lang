import { Assert } from "std/assert"
import { frameName, frameLabel, sourceFrames } from "./frame-presentation"
import { DebugRow } from "./model"

export function testStackLabelsRemoveImplementationNamespaces(): none {
  Assert.equal(frameName("fixture::main_::doof_main(std::vector<std::string>)"), "main")
  Assert.equal(frameName("package::module::calculate(int)"), "calculate")
  Assert.equal(frameName("calculate"), "calculate")
  Assert.equal(frameLabel(DebugRow { key: "frame/0", label: "", data: { name: "p::doof_main()", line: 3 } }), "main · 3")
}

export function testStackHidesNativeAndUnavailableFrames(): none {
  native := DebugRow { key: "frame/0", label: "", data: { name: "start", line: 1749, source: { path: "/usr/lib/dyld" } } }
  unavailable := DebugRow { key: "frame/1", label: "", data: { name: "missing", line: 4, source: { path: "/this/does/not/exist.do" } } }
  Assert.equal(sourceFrames([native, unavailable]).length, 0)
}
