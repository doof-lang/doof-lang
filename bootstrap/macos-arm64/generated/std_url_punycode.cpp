#include "std_url_punycode.hpp"

namespace std_::url::punycode {
using namespace ::std_::url::punycode_error;
using namespace ::std_::url::punycode_utf8;
int64_t BASE = 36LL;
int64_t TMIN = 1LL;
int64_t TMAX = 26LL;
int64_t SKEW = 38LL;
int64_t DAMP = 700LL;
int64_t INITIAL_BIAS = 72LL;
int64_t INITIAL_N = 128LL;
int64_t MAX_INT = 2147483647LL;
#line 13 "/std/url/punycode.do"
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> encodePunycodeLabel(const std::string& text) {
#line 14 "/std/url/punycode.do"
    auto _try_value_1 = ::std_::url::punycode_utf8::decodePunycodeUtf8(text);
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>{doof::variant_promote<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>(doof::failure_error(_try_value_1))};
    const auto input = doof::success_value(_try_value_1);
#line 15 "/std/url/punycode.do"
    const std::shared_ptr<std::vector<int32_t>> output = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
#line 17 "/std/url/punycode.do"
    const auto& _iterable_3 = input;
    for (const auto& codepoint : *_iterable_3) {
#line 18 "/std/url/punycode.do"
        if (codepoint < 128) {
#line 19 "/std/url/punycode.do"
            output->push_back(codepoint);
        }
    }
#line 23 "/std/url/punycode.do"
    auto handled = static_cast<int32_t>((output)->size());
#line 24 "/std/url/punycode.do"
    const auto basicCount = handled;
#line 25 "/std/url/punycode.do"
    if (basicCount > 0) {
#line 26 "/std/url/punycode.do"
        output->push_back(static_cast<int32_t>(U'\u002D'));
    }
#line 29 "/std/url/punycode.do"
    auto n = INITIAL_N;
#line 30 "/std/url/punycode.do"
    auto delta = 0LL;
#line 31 "/std/url/punycode.do"
    auto bias = INITIAL_BIAS;
#line 33 "/std/url/punycode.do"
    while (handled < static_cast<int32_t>((input)->size())) {
#line 34 "/std/url/punycode.do"
        auto nextCodepoint = 1114112LL;
#line 35 "/std/url/punycode.do"
        const auto& _iterable_5 = input;
        for (const auto& codepoint : *_iterable_5) {
#line 36 "/std/url/punycode.do"
            const auto value = static_cast<int64_t>(codepoint);
#line 37 "/std/url/punycode.do"
            if ((value >= n) && (nextCodepoint > value)) {
#line 38 "/std/url/punycode.do"
                (nextCodepoint = value);
            }
        }
#line 42 "/std/url/punycode.do"
        const auto distance = (nextCodepoint - n);
#line 43 "/std/url/punycode.do"
        const auto points = (static_cast<int64_t>(handled) + 1LL);
#line 44 "/std/url/punycode.do"
        if (distance > ((MAX_INT - delta) / points)) {
#line 45 "/std/url/punycode.do"
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), handled, std::string("Punycode encoding overflow"));
        }
#line 47 "/std/url/punycode.do"
        (delta += (distance * points));
#line 48 "/std/url/punycode.do"
        (n = nextCodepoint);
#line 50 "/std/url/punycode.do"
        const auto& _iterable_7 = input;
        for (const auto& codepoint : *_iterable_7) {
#line 51 "/std/url/punycode.do"
            const auto value = static_cast<int64_t>(codepoint);
#line 52 "/std/url/punycode.do"
            if (value < n) {
#line 53 "/std/url/punycode.do"
                if (delta == MAX_INT) {
#line 54 "/std/url/punycode.do"
                    return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), handled, std::string("Punycode encoding overflow"));
                }
#line 56 "/std/url/punycode.do"
                (delta += 1LL);
            }
#line 59 "/std/url/punycode.do"
            if (value == n) {
#line 60 "/std/url/punycode.do"
                auto q = delta;
#line 61 "/std/url/punycode.do"
                auto k = BASE;
#line 62 "/std/url/punycode.do"
                while (true) {
#line 63 "/std/url/punycode.do"
                    const auto thresholdValue = threshold(k, bias);
#line 64 "/std/url/punycode.do"
                    if (q < thresholdValue) {
#line 65 "/std/url/punycode.do"
                        break;
                    }
#line 67 "/std/url/punycode.do"
                    output->push_back(encodeDigit((thresholdValue + ((q - thresholdValue) % (BASE - thresholdValue)))));
#line 68 "/std/url/punycode.do"
                    (q = ((q - thresholdValue) / (BASE - thresholdValue)));
#line 69 "/std/url/punycode.do"
                    (k += BASE);
                }
#line 71 "/std/url/punycode.do"
                output->push_back(encodeDigit(q));
#line 72 "/std/url/punycode.do"
                (bias = adapt(delta, points, (handled == basicCount)));
#line 73 "/std/url/punycode.do"
                (delta = 0LL);
#line 74 "/std/url/punycode.do"
                (handled += 1);
            }
        }
#line 78 "/std/url/punycode.do"
        if ((delta == MAX_INT) || (n == MAX_INT)) {
#line 79 "/std/url/punycode.do"
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), handled, std::string("Punycode encoding overflow"));
        }
#line 81 "/std/url/punycode.do"
        (delta += 1LL);
#line 82 "/std/url/punycode.do"
        (n += 1LL);
    }
#line 85 "/std/url/punycode.do"
    return ::std_::url::punycode_utf8::encodePunycodeUtf8(output);
}
#line 88 "/std/url/punycode.do"
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> decodePunycodeLabel(const std::string& text) {
#line 89 "/std/url/punycode.do"
    const std::shared_ptr<std::vector<int32_t>> output = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
#line 90 "/std/url/punycode.do"
    const auto delimiter = findLastByte(text, static_cast<int32_t>(U'\u002D'));
#line 91 "/std/url/punycode.do"
    auto inputIndex = 0;
#line 93 "/std/url/punycode.do"
    if (delimiter >= 0) {
#line 94 "/std/url/punycode.do"
        auto index = 0;
#line 95 "/std/url/punycode.do"
        while (index < delimiter) {
#line 96 "/std/url/punycode.do"
            const auto value = static_cast<int32_t>(doof::string_at(text, index, "", 0));
#line 97 "/std/url/punycode.do"
            if (value >= 128) {
#line 98 "/std/url/punycode.do"
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), index, std::string("Punycode basic section must be ASCII"));
            }
#line 100 "/std/url/punycode.do"
            output->push_back(value);
#line 101 "/std/url/punycode.do"
            (index += 1);
        }
#line 103 "/std/url/punycode.do"
        (inputIndex = (delimiter + 1));
    }
#line 106 "/std/url/punycode.do"
    auto n = INITIAL_N;
#line 107 "/std/url/punycode.do"
    auto insertion = 0LL;
#line 108 "/std/url/punycode.do"
    auto bias = INITIAL_BIAS;
#line 110 "/std/url/punycode.do"
    while (inputIndex < static_cast<int32_t>(text.size())) {
#line 111 "/std/url/punycode.do"
        const auto oldInsertion = insertion;
#line 112 "/std/url/punycode.do"
        auto weight = 1LL;
#line 113 "/std/url/punycode.do"
        auto k = BASE;
#line 115 "/std/url/punycode.do"
        while (true) {
#line 116 "/std/url/punycode.do"
            if (inputIndex >= static_cast<int32_t>(text.size())) {
#line 117 "/std/url/punycode.do"
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), inputIndex, std::string("Truncated Punycode input"));
            }
#line 120 "/std/url/punycode.do"
            const auto digit = decodeDigit(static_cast<int32_t>(doof::string_at(text, inputIndex, "", 0)));
#line 121 "/std/url/punycode.do"
            if (0 > digit) {
#line 122 "/std/url/punycode.do"
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), inputIndex, std::string("Invalid Punycode digit"));
            }
#line 124 "/std/url/punycode.do"
            (inputIndex += 1);
#line 126 "/std/url/punycode.do"
            const auto digitValue = static_cast<int64_t>(digit);
#line 127 "/std/url/punycode.do"
            if (digitValue > ((MAX_INT - insertion) / weight)) {
#line 128 "/std/url/punycode.do"
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), (inputIndex - 1), std::string("Punycode decoding overflow"));
            }
#line 130 "/std/url/punycode.do"
            (insertion += (digitValue * weight));
#line 132 "/std/url/punycode.do"
            const auto limit = threshold(k, bias);
#line 133 "/std/url/punycode.do"
            if (digitValue < limit) {
#line 134 "/std/url/punycode.do"
                break;
            }
#line 136 "/std/url/punycode.do"
            const auto factor = (BASE - limit);
#line 137 "/std/url/punycode.do"
            if (weight > (MAX_INT / factor)) {
#line 138 "/std/url/punycode.do"
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), (inputIndex - 1), std::string("Punycode decoding overflow"));
            }
#line 140 "/std/url/punycode.do"
            (weight *= factor);
#line 141 "/std/url/punycode.do"
            (k += BASE);
        }
#line 144 "/std/url/punycode.do"
        const auto outputSize = (static_cast<int64_t>(static_cast<int32_t>((output)->size())) + 1LL);
#line 145 "/std/url/punycode.do"
        (bias = adapt((insertion - oldInsertion), outputSize, (oldInsertion == 0LL)));
#line 146 "/std/url/punycode.do"
        const auto increment = (insertion / outputSize);
#line 147 "/std/url/punycode.do"
        if (increment > (1114111LL - n)) {
#line 148 "/std/url/punycode.do"
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), inputIndex, std::string("Decoded code point is outside Unicode"));
        }
#line 150 "/std/url/punycode.do"
        (n += increment);
#line 151 "/std/url/punycode.do"
        (insertion %= outputSize);
#line 153 "/std/url/punycode.do"
        if ((n >= 55296LL) && (n <= 57343LL)) {
#line 154 "/std/url/punycode.do"
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), inputIndex, std::string("Decoded Punycode contains a surrogate"));
        }
#line 157 "/std/url/punycode.do"
        insertCodepoint(output, static_cast<int32_t>(insertion), static_cast<int32_t>(n));
#line 158 "/std/url/punycode.do"
        (insertion += 1LL);
    }
#line 161 "/std/url/punycode.do"
    return ::std_::url::punycode_utf8::encodePunycodeUtf8(output);
}
#line 164 "/std/url/punycode.do"
int64_t threshold(int64_t k, int64_t bias) {
#line 165 "/std/url/punycode.do"
    if (k <= (bias + TMIN)) {
#line 166 "/std/url/punycode.do"
        return TMIN;
    }
#line 168 "/std/url/punycode.do"
    if (k >= (bias + TMAX)) {
#line 169 "/std/url/punycode.do"
        return TMAX;
    }
#line 171 "/std/url/punycode.do"
    return (k - bias);
}
#line 174 "/std/url/punycode.do"
int64_t adapt(int64_t deltaValue, int64_t pointCount, bool firstTime) {
#line 175 "/std/url/punycode.do"
    auto delta = (firstTime ? (deltaValue / DAMP) : (deltaValue / 2LL));
#line 176 "/std/url/punycode.do"
    (delta += (delta / pointCount));
#line 177 "/std/url/punycode.do"
    auto k = 0LL;
#line 178 "/std/url/punycode.do"
    while (delta > (((BASE - TMIN) * TMAX) / 2LL)) {
#line 179 "/std/url/punycode.do"
        (delta = (delta / (BASE - TMIN)));
#line 180 "/std/url/punycode.do"
        (k += BASE);
    }
#line 182 "/std/url/punycode.do"
    return (k + ((((BASE - TMIN) + 1LL) * delta) / (delta + SKEW)));
}
#line 185 "/std/url/punycode.do"
int32_t encodeDigit(int64_t digit) {
#line 186 "/std/url/punycode.do"
    if (digit < 26LL) {
#line 187 "/std/url/punycode.do"
        return (static_cast<int32_t>(U'\u0061') + static_cast<int32_t>(digit));
    }
#line 189 "/std/url/punycode.do"
    return (static_cast<int32_t>(U'\u0030') + static_cast<int32_t>((digit - 26LL)));
}
#line 192 "/std/url/punycode.do"
int32_t decodeDigit(int32_t value) {
#line 193 "/std/url/punycode.do"
    if ((value >= static_cast<int32_t>(U'\u0061')) && (value <= static_cast<int32_t>(U'\u007A'))) {
#line 194 "/std/url/punycode.do"
        return (value - static_cast<int32_t>(U'\u0061'));
    }
#line 196 "/std/url/punycode.do"
    if ((value >= static_cast<int32_t>(U'\u0041')) && (value <= static_cast<int32_t>(U'\u005A'))) {
#line 197 "/std/url/punycode.do"
        return (value - static_cast<int32_t>(U'\u0041'));
    }
#line 199 "/std/url/punycode.do"
    if ((value >= static_cast<int32_t>(U'\u0030')) && (value <= static_cast<int32_t>(U'\u0039'))) {
#line 200 "/std/url/punycode.do"
        return ((26 + value) - static_cast<int32_t>(U'\u0030'));
    }
#line 202 "/std/url/punycode.do"
    return -1;
}
#line 205 "/std/url/punycode.do"
void insertCodepoint(const std::shared_ptr<std::vector<int32_t>>& values, int32_t index, int32_t value) {
#line 206 "/std/url/punycode.do"
    values->push_back(value);
#line 207 "/std/url/punycode.do"
    auto cursor = (static_cast<int32_t>((values)->size()) - 1);
#line 208 "/std/url/punycode.do"
    while (cursor > index) {
#line 209 "/std/url/punycode.do"
        (doof::array_at(values, cursor, "punycode", 209) = doof::array_at(values, (cursor - 1), "punycode", 209));
#line 210 "/std/url/punycode.do"
        (cursor -= 1);
    }
#line 212 "/std/url/punycode.do"
    (doof::array_at(values, index, "punycode", 212) = value);
}
#line 215 "/std/url/punycode.do"
int32_t findLastByte(const std::string& text, int32_t target) {
#line 216 "/std/url/punycode.do"
    auto found = -1;
#line 217 "/std/url/punycode.do"
    auto index = 0;
#line 218 "/std/url/punycode.do"
    while (index < static_cast<int32_t>(text.size())) {
#line 219 "/std/url/punycode.do"
        if (static_cast<int32_t>(doof::string_at(text, index, "", 0)) == target) {
#line 220 "/std/url/punycode.do"
            (found = index);
        }
#line 222 "/std/url/punycode.do"
        (index += 1);
    }
#line 224 "/std/url/punycode.do"
    return found;
}
#line 1 "<doof-generated>"
}
