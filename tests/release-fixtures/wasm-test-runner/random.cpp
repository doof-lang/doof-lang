#include "random.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

extern "C" int wasi_random_get(void*, uint32_t)
    __attribute__((import_module("wasi_snapshot_preview1"), import_name("random_get")));

bool wasm_random_writes_bounded_chunks() {
    // Cross the native transfer boundary and retain sentinels on both sides.
    std::vector<uint8_t> first(65538, 0xa5), second(65536, 0);
    if (wasi_random_get(first.data() + 1, 65536) != 0 ||
        wasi_random_get(second.data(), 65536) != 0) return false;
    if (first.front() != 0xa5 || first.back() != 0xa5) return false;
    if (std::equal(second.begin(), second.end(), first.begin() + 1)) return false;
    // Exercise a multi-chunk request as well as the exact boundary above.
    std::vector<uint8_t> large(65537, 0);
    if (wasi_random_get(large.data(), uint32_t(large.size())) != 0) return false;
    return std::any_of(large.begin(), large.end(), [](uint8_t b) { return b != 0; });
}

bool wasm_random_checks_memory_bounds() {
    const uint32_t end = uint32_t(__builtin_wasm_memory_size(0) * 65536);
    std::array<uint8_t, 4> unchanged{1, 2, 3, 4};
    if (wasi_random_get(unchanged.data(), 0) != 0 ||
        unchanged != std::array<uint8_t, 4>{1, 2, 3, 4}) return false;
    if (wasi_random_get(reinterpret_cast<void*>(uintptr_t(end)), 0) != 0) return false;
    if (wasi_random_get(reinterpret_cast<void*>(uintptr_t(end)), 1) != 21) return false;
    if (wasi_random_get(reinterpret_cast<void*>(uintptr_t(end - 1)), 2) != 21) return false;
    if (wasi_random_get(reinterpret_cast<void*>(uintptr_t(0xffffffff)), 2) != 21) return false;
    return wasi_random_get(unchanged.data(), 0xffffffff) == 21;
}
