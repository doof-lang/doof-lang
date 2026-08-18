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
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> encodePunycodeLabel(const std::string& text) {
    auto _try_value_1 = ::std_::url::punycode_utf8::decodePunycodeUtf8(text);
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>{doof::variant_promote<std::shared_ptr<::std_::url::punycode_error::PunycodeError>>(doof::failure_error(_try_value_1))};
    const auto input = doof::success_value(_try_value_1);
    const std::shared_ptr<std::vector<int32_t>> output = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    const auto& _iterable_2 = input;
    for (const auto& codepoint : *_iterable_2) {
        if (codepoint < 128) {
            output->push_back(codepoint);
        }
    }
    auto handled = static_cast<int32_t>((output)->size());
    const auto basicCount = handled;
    if (basicCount > 0) {
        output->push_back(static_cast<int32_t>(U'\u002D'));
    }
    auto n = INITIAL_N;
    auto delta = 0LL;
    auto bias = INITIAL_BIAS;
    while (handled < static_cast<int32_t>((input)->size())) {
        auto nextCodepoint = 1114112LL;
        const auto& _iterable_3 = input;
        for (const auto& codepoint : *_iterable_3) {
            const auto value = static_cast<int64_t>(codepoint);
            if ((value >= n) && (nextCodepoint > value)) {
                (nextCodepoint = value);
            }
        }
        const auto distance = (nextCodepoint - n);
        const auto points = (static_cast<int64_t>(handled) + 1LL);
        if (distance > ((MAX_INT - delta) / points)) {
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), handled, std::string("Punycode encoding overflow"));
        }
        (delta += (distance * points));
        (n = nextCodepoint);
        const auto& _iterable_4 = input;
        for (const auto& codepoint : *_iterable_4) {
            const auto value = static_cast<int64_t>(codepoint);
            if (value < n) {
                if (delta == MAX_INT) {
                    return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), handled, std::string("Punycode encoding overflow"));
                }
                (delta += 1LL);
            }
            if (value == n) {
                auto q = delta;
                auto k = BASE;
                while (true) {
                    const auto thresholdValue = threshold(k, bias);
                    if (q < thresholdValue) {
                        break;
                    }
                    output->push_back(encodeDigit((thresholdValue + ((q - thresholdValue) % (BASE - thresholdValue)))));
                    (q = ((q - thresholdValue) / (BASE - thresholdValue)));
                    (k += BASE);
                }
                output->push_back(encodeDigit(q));
                (bias = adapt(delta, points, (handled == basicCount)));
                (delta = 0LL);
                (handled += 1);
            }
        }
        if ((delta == MAX_INT) || (n == MAX_INT)) {
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), handled, std::string("Punycode encoding overflow"));
        }
        (delta += 1LL);
        (n += 1LL);
    }
    return ::std_::url::punycode_utf8::encodePunycodeUtf8(output);
}
doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> decodePunycodeLabel(const std::string& text) {
    const std::shared_ptr<std::vector<int32_t>> output = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    const auto delimiter = findLastByte(text, static_cast<int32_t>(U'\u002D'));
    auto inputIndex = 0;
    if (delimiter >= 0) {
        auto index = 0;
        while (index < delimiter) {
            const auto value = static_cast<int32_t>(doof::string_at(text, index, "", 0));
            if (value >= 128) {
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), index, std::string("Punycode basic section must be ASCII"));
            }
            output->push_back(value);
            (index += 1);
        }
        (inputIndex = (delimiter + 1));
    }
    auto n = INITIAL_N;
    auto insertion = 0LL;
    auto bias = INITIAL_BIAS;
    while (inputIndex < static_cast<int32_t>(text.size())) {
        const auto oldInsertion = insertion;
        auto weight = 1LL;
        auto k = BASE;
        while (true) {
            if (inputIndex >= static_cast<int32_t>(text.size())) {
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), inputIndex, std::string("Truncated Punycode input"));
            }
            const auto digit = decodeDigit(static_cast<int32_t>(doof::string_at(text, inputIndex, "", 0)));
            if (0 > digit) {
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), inputIndex, std::string("Invalid Punycode digit"));
            }
            (inputIndex += 1);
            const auto digitValue = static_cast<int64_t>(digit);
            if (digitValue > ((MAX_INT - insertion) / weight)) {
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), (inputIndex - 1), std::string("Punycode decoding overflow"));
            }
            (insertion += (digitValue * weight));
            const auto limit = threshold(k, bias);
            if (digitValue < limit) {
                break;
            }
            const auto factor = (BASE - limit);
            if (weight > (MAX_INT / factor)) {
                return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), (inputIndex - 1), std::string("Punycode decoding overflow"));
            }
            (weight *= factor);
            (k += BASE);
        }
        const auto outputSize = (static_cast<int64_t>(static_cast<int32_t>((output)->size())) + 1LL);
        (bias = adapt((insertion - oldInsertion), outputSize, (oldInsertion == 0LL)));
        const auto increment = (insertion / outputSize);
        if (increment > (1114111LL - n)) {
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("overflow"), inputIndex, std::string("Decoded code point is outside Unicode"));
        }
        (n += increment);
        (insertion %= outputSize);
        if ((n >= 55296LL) && (n <= 57343LL)) {
            return ::std_::url::punycode_error::punycodeFailure__string(std::string("invalid-punycode"), inputIndex, std::string("Decoded Punycode contains a surrogate"));
        }
        insertCodepoint(output, static_cast<int32_t>(insertion), static_cast<int32_t>(n));
        (insertion += 1LL);
    }
    return ::std_::url::punycode_utf8::encodePunycodeUtf8(output);
}
int64_t threshold(int64_t k, int64_t bias) {
    if (k <= (bias + TMIN)) {
        return TMIN;
    }
    if (k >= (bias + TMAX)) {
        return TMAX;
    }
    return (k - bias);
}
int64_t adapt(int64_t deltaValue, int64_t pointCount, bool firstTime) {
    auto delta = (firstTime ? (deltaValue / DAMP) : (deltaValue / 2LL));
    (delta += (delta / pointCount));
    auto k = 0LL;
    while (delta > (((BASE - TMIN) * TMAX) / 2LL)) {
        (delta = (delta / (BASE - TMIN)));
        (k += BASE);
    }
    return (k + ((((BASE - TMIN) + 1LL) * delta) / (delta + SKEW)));
}
int32_t encodeDigit(int64_t digit) {
    if (digit < 26LL) {
        return (static_cast<int32_t>(U'\u0061') + static_cast<int32_t>(digit));
    }
    return (static_cast<int32_t>(U'\u0030') + static_cast<int32_t>((digit - 26LL)));
}
int32_t decodeDigit(int32_t value) {
    if ((value >= static_cast<int32_t>(U'\u0061')) && (value <= static_cast<int32_t>(U'\u007A'))) {
        return (value - static_cast<int32_t>(U'\u0061'));
    }
    if ((value >= static_cast<int32_t>(U'\u0041')) && (value <= static_cast<int32_t>(U'\u005A'))) {
        return (value - static_cast<int32_t>(U'\u0041'));
    }
    if ((value >= static_cast<int32_t>(U'\u0030')) && (value <= static_cast<int32_t>(U'\u0039'))) {
        return ((26 + value) - static_cast<int32_t>(U'\u0030'));
    }
    return -1;
}
void insertCodepoint(const std::shared_ptr<std::vector<int32_t>>& values, int32_t index, int32_t value) {
    values->push_back(value);
    auto cursor = (static_cast<int32_t>((values)->size()) - 1);
    while (cursor > index) {
        (doof::array_at(values, cursor, "punycode", 209) = doof::array_at(values, (cursor - 1), "punycode", 209));
        (cursor -= 1);
    }
    (doof::array_at(values, index, "punycode", 212) = value);
}
int32_t findLastByte(const std::string& text, int32_t target) {
    auto found = -1;
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        if (static_cast<int32_t>(doof::string_at(text, index, "", 0)) == target) {
            (found = index);
        }
        (index += 1);
    }
    return found;
}
}
