#include "std_url_punycode_utf8.hpp"

namespace std_::url::punycode_utf8 {
using namespace ::std_::blob::index;
using namespace ::std_::url::punycode_error;
doof::Result<std::shared_ptr<std::vector<int32_t>>, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> decodePunycodeUtf8(const std::string& text) {
    const std::shared_ptr<std::vector<int32_t>> codepoints = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        const auto first = static_cast<int32_t>(doof::string_at(text, index, "", 0));
        if (first <= 127) {
            codepoints->push_back(first);
            (index += 1);
            continue;
        }
        if (((first >= 194) && (first <= 223)) && ((index + 1) < static_cast<int32_t>(text.size()))) {
            const auto second = static_cast<int32_t>(doof::string_at(text, (index + 1), "", 0));
            if (isContinuation(second)) {
                codepoints->push_back(((((first - 192) * 64) + second) - 128));
                (index += 2);
                continue;
            }
        }
        if (((first >= 224) && (first <= 239)) && ((index + 2) < static_cast<int32_t>(text.size()))) {
            const auto second = static_cast<int32_t>(doof::string_at(text, (index + 1), "", 0));
            const auto third = static_cast<int32_t>(doof::string_at(text, (index + 2), "", 0));
            const auto validSecond = ((isContinuation(second) && ((first != 224) || (second >= 160))) && ((first != 237) || (second <= 159)));
            if (validSecond && isContinuation(third)) {
                codepoints->push_back((((((first - 224) * 4096) + ((second - 128) * 64)) + third) - 128));
                (index += 3);
                continue;
            }
        }
        if (((first >= 240) && (first <= 244)) && ((index + 3) < static_cast<int32_t>(text.size()))) {
            const auto second = static_cast<int32_t>(doof::string_at(text, (index + 1), "", 0));
            const auto third = static_cast<int32_t>(doof::string_at(text, (index + 2), "", 0));
            const auto fourth = static_cast<int32_t>(doof::string_at(text, (index + 3), "", 0));
            const auto validSecond = ((isContinuation(second) && ((first != 240) || (second >= 144))) && ((first != 244) || (second <= 143)));
            if ((validSecond && isContinuation(third)) && isContinuation(fourth)) {
                codepoints->push_back(((((((first - 240) * 262144) + ((second - 128) * 4096)) + ((third - 128) * 64)) + fourth) - 128));
                (index += 4);
                continue;
            }
        }
        return ::std_::url::punycode_error::punycodeFailure__array_int(std::string("invalid-utf8"), index, ([&]() -> std::string { std::string _interpolation = "Invalid UTF-8 at byte "; _interpolation += doof::to_string(index); _interpolation += ""; return _interpolation; }()));
    }
    return doof::Success<std::shared_ptr<std::vector<int32_t>>>{ codepoints };
}
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> encodePunycodeUtf8(const std::shared_ptr<std::vector<int32_t>>& codepoints) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    const auto& _iterable_2 = codepoints;
    for (const auto& codepoint : *_iterable_2) {
        if (((codepoint < 0) || (codepoint > 1114111)) || ((codepoint >= 55296) && (codepoint <= 57343))) {
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), 0, std::string("Invalid Unicode code point"));
        }
        if (codepoint <= 127) {
            builder->writeByte(static_cast<uint8_t>(codepoint));
        } else if (codepoint <= 2047) {
            builder->writeByte(static_cast<uint8_t>((192 + (codepoint / 64))));
            builder->writeByte(static_cast<uint8_t>((128 + (codepoint % 64))));
        } else if (codepoint <= 65535) {
            builder->writeByte(static_cast<uint8_t>((224 + (codepoint / 4096))));
            builder->writeByte(static_cast<uint8_t>((128 + ((codepoint / 64) % 64))));
            builder->writeByte(static_cast<uint8_t>((128 + (codepoint % 64))));
        } else {
            builder->writeByte(static_cast<uint8_t>((240 + (codepoint / 262144))));
            builder->writeByte(static_cast<uint8_t>((128 + ((codepoint / 4096) % 64))));
            builder->writeByte(static_cast<uint8_t>((128 + ((codepoint / 64) % 64))));
            builder->writeByte(static_cast<uint8_t>((128 + (codepoint % 64))));
        }
    }
    const auto bytes = builder->build();
    const auto reader = ::doof_blob::NativeBlobReader::constructor(bytes, ::std_::blob::types::Endian::LittleEndian);
    return doof::Success<std::string>{ reader->readString(reader->length()) };
}
bool isContinuation(int32_t value) {
    return ((value >= 128) && (value <= 191));
}
}
