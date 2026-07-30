export function producePromise(value: int): Promise<int> {
  return async {
    yield value + 1
  }
}
