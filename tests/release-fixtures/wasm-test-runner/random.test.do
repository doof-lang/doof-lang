import { Assert } from "std/assert"
import isolated function randomWritesBoundedChunks(): bool from "random.hpp" as wasm_random_writes_bounded_chunks
import isolated function randomChecksMemoryBounds(): bool from "random.hpp" as wasm_random_checks_memory_bounds

export function testWasmRandomWritesBoundedChunks(): none {
  Assert.isTrue(randomWritesBoundedChunks())
}

export function testWasmRandomChecksMemoryBounds(): none {
  Assert.isTrue(randomChecksMemoryBounds())
}
