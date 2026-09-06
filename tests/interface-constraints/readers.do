export interface BoundReader<V> {
  boundRead(increment: int = 2): V
}

export class BoundBox<V> {
  value: V
  boundRead(increment: int = 99): V => value
}

export function readBound<V, T: BoundReader<V>>(reader: T, fallback: V): V {
  return reader.boundRead()
}

export function keepBound<T: BoundReader<int>>(reader: T): T => reader

export class BoundOwner<T: BoundReader<int>> {
  reader: T
  read(): int => reader.boundRead{increment: 3}
  readOther<U: BoundReader<int>>(other: U): int => other.boundRead()
}
