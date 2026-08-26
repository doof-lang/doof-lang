#include "std_url_punycode_utf8.hpp"

namespace std_::url::punycode_utf8 {
using namespace ::std_::blob::index;
using namespace ::std_::url::punycode_error;
#line 5 "/std/url/punycode_utf8.do"
doof::Result<std::shared_ptr<std::vector<int32_t>>, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> decodePunycodeUtf8(const std::string& text) {
#line 6 "/std/url/punycode_utf8.do"
    const std::shared_ptr<std::vector<int32_t>> codepoints = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
#line 7 "/std/url/punycode_utf8.do"
    auto index = 0;
#line 9 "/std/url/punycode_utf8.do"
    while (index < static_cast<int32_t>(text.size())) {
#line 10 "/std/url/punycode_utf8.do"
        const auto first = static_cast<int32_t>(doof::string_at(text, index, "", 0));
#line 11 "/std/url/punycode_utf8.do"
        if (first <= 127) {
#line 12 "/std/url/punycode_utf8.do"
            codepoints->push_back(first);
#line 13 "/std/url/punycode_utf8.do"
            (index += 1);
#line 14 "/std/url/punycode_utf8.do"
            continue;
        }
#line 17 "/std/url/punycode_utf8.do"
        if (((first >= 194) && (first <= 223)) && ((index + 1) < static_cast<int32_t>(text.size()))) {
#line 18 "/std/url/punycode_utf8.do"
            const auto second = static_cast<int32_t>(doof::string_at(text, (index + 1), "", 0));
#line 19 "/std/url/punycode_utf8.do"
            if (isContinuation(second)) {
#line 20 "/std/url/punycode_utf8.do"
                codepoints->push_back(((((first - 192) * 64) + second) - 128));
#line 21 "/std/url/punycode_utf8.do"
                (index += 2);
#line 22 "/std/url/punycode_utf8.do"
                continue;
            }
        }
#line 26 "/std/url/punycode_utf8.do"
        if (((first >= 224) && (first <= 239)) && ((index + 2) < static_cast<int32_t>(text.size()))) {
#line 27 "/std/url/punycode_utf8.do"
            const auto second = static_cast<int32_t>(doof::string_at(text, (index + 1), "", 0));
#line 28 "/std/url/punycode_utf8.do"
            const auto third = static_cast<int32_t>(doof::string_at(text, (index + 2), "", 0));
#line 29 "/std/url/punycode_utf8.do"
            const auto validSecond = ((isContinuation(second) && ((first != 224) || (second >= 160))) && ((first != 237) || (second <= 159)));
#line 32 "/std/url/punycode_utf8.do"
            if (validSecond && isContinuation(third)) {
#line 33 "/std/url/punycode_utf8.do"
                codepoints->push_back((((((first - 224) * 4096) + ((second - 128) * 64)) + third) - 128));
#line 34 "/std/url/punycode_utf8.do"
                (index += 3);
#line 35 "/std/url/punycode_utf8.do"
                continue;
            }
        }
#line 39 "/std/url/punycode_utf8.do"
        if (((first >= 240) && (first <= 244)) && ((index + 3) < static_cast<int32_t>(text.size()))) {
#line 40 "/std/url/punycode_utf8.do"
            const auto second = static_cast<int32_t>(doof::string_at(text, (index + 1), "", 0));
#line 41 "/std/url/punycode_utf8.do"
            const auto third = static_cast<int32_t>(doof::string_at(text, (index + 2), "", 0));
#line 42 "/std/url/punycode_utf8.do"
            const auto fourth = static_cast<int32_t>(doof::string_at(text, (index + 3), "", 0));
#line 43 "/std/url/punycode_utf8.do"
            const auto validSecond = ((isContinuation(second) && ((first != 240) || (second >= 144))) && ((first != 244) || (second <= 143)));
#line 46 "/std/url/punycode_utf8.do"
            if ((validSecond && isContinuation(third)) && isContinuation(fourth)) {
#line 47 "/std/url/punycode_utf8.do"
                codepoints->push_back(((((((first - 240) * 262144) + ((second - 128) * 4096)) + ((third - 128) * 64)) + fourth) - 128));
#line 51 "/std/url/punycode_utf8.do"
                (index += 4);
#line 52 "/std/url/punycode_utf8.do"
                continue;
            }
        }
#line 56 "/std/url/punycode_utf8.do"
        return ::std_::url::punycode_error::punycodeFailure__array_int(std::string("invalid-utf8"), index, ([&]() -> std::string { std::string _interpolation = "Invalid UTF-8 at byte "; _interpolation += doof::to_string(index); _interpolation += ""; return _interpolation; }()));
    }
#line 59 "/std/url/punycode_utf8.do"
    return doof::Success<std::shared_ptr<std::vector<int32_t>>>{ codepoints };
}
#line 62 "/std/url/punycode_utf8.do"
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> encodePunycodeUtf8(const std::shared_ptr<std::vector<int32_t>>& codepoints) {
#line 63 "/std/url/punycode_utf8.do"
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
#line 64 "/std/url/punycode_utf8.do"
    const auto& _iterable_2 = codepoints;
    for (const auto& codepoint : *_iterable_2) {
#line 65 "/std/url/punycode_utf8.do"
        if (((codepoint < 0) || (codepoint > 1114111)) || ((codepoint >= 55296) && (codepoint <= 57343))) {
#line 66 "/std/url/punycode_utf8.do"
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), 0, std::string("Invalid Unicode code point"));
        }
#line 68 "/std/url/punycode_utf8.do"
        if (codepoint <= 127) {
#line 69 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>(codepoint));
        } else if (codepoint <= 2047) {
#line 71 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((192 + (codepoint / 64))));
#line 72 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((128 + (codepoint % 64))));
        } else if (codepoint <= 65535) {
#line 74 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((224 + (codepoint / 4096))));
#line 75 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((128 + ((codepoint / 64) % 64))));
#line 76 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((128 + (codepoint % 64))));
        } else {
#line 78 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((240 + (codepoint / 262144))));
#line 79 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((128 + ((codepoint / 4096) % 64))));
#line 80 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((128 + ((codepoint / 64) % 64))));
#line 81 "/std/url/punycode_utf8.do"
            builder->writeByte(static_cast<uint8_t>((128 + (codepoint % 64))));
        }
    }
#line 84 "/std/url/punycode_utf8.do"
    const auto bytes = builder->build();
#line 85 "/std/url/punycode_utf8.do"
    const auto reader = ::doof_blob::NativeBlobReader::constructor(bytes, ::std_::blob::types::Endian::LittleEndian);
#line 86 "/std/url/punycode_utf8.do"
    return doof::Success<std::string>{ reader->readString(reader->length()) };
}
#line 89 "/std/url/punycode_utf8.do"
bool isContinuation(int32_t value) {
    return ((value >= 128) && (value <= 191));
}
#line 1 "<doof-generated>"
}
