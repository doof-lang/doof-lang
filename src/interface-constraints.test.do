import { Assert } from "std/assert"
import { BoundReader, BoundBox, BoundOwner, readBound, keepBound } from "../tests/interface-constraints/readers"

class BoundCounter {
  let total: int = 0
  boundRead(increment: int = 99): int {
    total += increment
    return total
  }
}

struct BoundValue {
  total: int
  boundRead(increment: int = 99): int => total + increment
}

interface BoundFields {
  let boundCount: int
  readonly boundItems: int[]
  boundCallback: (value: int): int
}

class BoundFieldsValue {
  let boundCount: int = 1
  readonly boundItems: int[] = [3, 4]
  boundCallback: (value: int): int = (value: int): int => value + 4
}

function updateFields<T: BoundFields>(value: T): int {
  value.boundCount += 1
  return value.boundCallback{value: value.boundCount} + value.boundItems.length
}

function forwardBound<T: BoundReader<int>>(value: T): T => keepBound(value)

export function testInterfaceBoundNativeConcreteAndGenericOwners(): none {
  counter := BoundCounter {}
  Assert.equal(readBound(counter, 0), 2)
  Assert.equal(forwardBound(counter).total, 2)
  Assert.equal(BoundOwner(counter).read(), 5)
  Assert.equal(BoundOwner(counter).readOther(counter), 7)
  Assert.equal(readBound(BoundBox(11), 0), 11)
  Assert.equal(readBound(BoundValue { total: 10 }, 0), 12)
}

export function testInterfaceBoundNativeInterfaceAndCovariantReturn(): none {
  counter := BoundCounter {}
  reader: BoundReader<int> := counter
  Assert.equal(readBound(reader, 0), 2)
  wide: BoundReader<double> := counter
  Assert.equal(readBound(wide, 0.0), 4.0)
}

export function testInterfaceBoundNativeFieldsAndCallbacks(): none {
  fields := BoundFieldsValue {}
  Assert.equal(updateFields(fields), 8)
  Assert.equal(fields.boundCount, 2)
  view: BoundFields := fields
  Assert.equal(updateFields(view), 9)
  Assert.equal(fields.boundCount, 3)
}
