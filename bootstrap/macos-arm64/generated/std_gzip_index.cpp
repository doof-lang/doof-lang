#include "std_gzip_index.hpp"

namespace std_::gzip::index {
int32_t normalizeBlockSize(int32_t blockSize) {
    if (blockSize > 0) {
        return blockSize;
    }
    return 65536;
}

std::shared_ptr<GzipStream> GzipStream::constructor(const Stream__readonly_array_byte& source) {
    return std::make_shared<GzipStream>(source, ::doof_gzip::NativeGzipEncoder::create(), std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), false, false);
}
bool GzipStream::next() {
    while (true) {
        if (!this->sourceDone) {
            if (std::visit([&](auto&& _obj) { return _obj->next(); }, this->source)) {
                const auto compressed = this->native->update(std::visit([&](auto&& _obj) { return _obj->value(); }, this->source));
                if (static_cast<int32_t>((compressed)->size()) > 0) {
                    (this->currentValue = compressed);
                    return true;
                }
                continue;
            }
            (this->sourceDone = true);
        }
        if (this->finished) {
            return false;
        }
        (this->finished = true);
        const auto finalChunk = this->native->finish();
        if (static_cast<int32_t>((finalChunk)->size()) == 0) {
            return false;
        }
        (this->currentValue = finalChunk);
        return true;
    }
}
std::shared_ptr<std::vector<uint8_t>> GzipStream::value() {
    return this->currentValue;
}
}
