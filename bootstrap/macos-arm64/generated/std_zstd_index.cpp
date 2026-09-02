#include "std_zstd_index.hpp"

namespace std_::zstd::index {

std::shared_ptr<ZstdCompressStream> ZstdCompressStream::constructor(const Stream__readonly_array_byte& source, int32_t level) {
    return std::make_shared<ZstdCompressStream>(source, level, ::doof_zstd::NativeZstdEncoder::create(level), std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), false, false, std::nullopt);
}
std::shared_ptr<ZstdCompressStream> ZstdCompressStream::withLevel(const Stream__readonly_array_byte& source, int32_t level) {
    return ZstdCompressStream::constructor(source, level);
}
bool ZstdCompressStream::next() {
    if (!doof::is_null(this->failed)) {
        doof::panic(doof::unwrap_optional(this->failed));
    }
    while (true) {
        if (!this->sourceDone) {
            if (std::visit([&](auto&& _obj) { return _obj->next(); }, this->source)) {
                std::shared_ptr<std::vector<uint8_t>> compressed = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
                {
                    auto _case_subject = this->native->update(std::visit([&](auto&& _obj) { return _obj->value(); }, this->source));
                    if (std::holds_alternative<doof::Success<std::shared_ptr<std::vector<uint8_t>>>>(_case_subject)) {
                        const auto& s = std::get<doof::Success<std::shared_ptr<std::vector<uint8_t>>>>(_case_subject);
                        (compressed = s.value);
                }
                else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
                        const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
                        (this->failed = f.error);
                        doof::panic(f.error);
                }
                }
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
        std::shared_ptr<std::vector<uint8_t>> finalChunk = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
        {
            auto _case_subject = this->native->finish();
            if (std::holds_alternative<doof::Success<std::shared_ptr<std::vector<uint8_t>>>>(_case_subject)) {
                const auto& s = std::get<doof::Success<std::shared_ptr<std::vector<uint8_t>>>>(_case_subject);
                (finalChunk = s.value);
        }
        else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
                const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
                (this->failed = f.error);
                doof::panic(f.error);
        }
        }
        if (static_cast<int32_t>((finalChunk)->size()) == 0) {
            return false;
        }
        (this->currentValue = finalChunk);
        return true;
    }
}
std::shared_ptr<std::vector<uint8_t>> ZstdCompressStream::value() {
    return this->currentValue;
}
}
