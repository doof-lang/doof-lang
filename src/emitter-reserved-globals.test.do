import { Assert } from "std/assert"
import { isReservedCGlobal } from "./emitter-reserved-globals"

export function testCGlobalsFromStandardAndPosixHeadersAreReserved(): none {
  for name of ["j1", "y0", "sin", "time", "index", "exit", "printf", "tm", "stat", "read", "socket", "random"] {
    Assert.isTrue(isReservedCGlobal(name))
  }
}

export function testOrdinaryPackageNamesAreNotReserved(): none {
  for name of ["geometry", "json", "app", "std_", "time_", "Time"] {
    Assert.isFalse(isReservedCGlobal(name))
  }
}
