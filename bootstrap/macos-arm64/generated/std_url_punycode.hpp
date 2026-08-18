#pragma once
#include "doof_runtime.hpp"
namespace std_::url::punycode_error {
    struct PunycodeError;
}

namespace std_::url::punycode {
    extern int64_t BASE;
    extern int64_t TMIN;
    extern int64_t TMAX;
    extern int64_t SKEW;
    extern int64_t DAMP;
    extern int64_t INITIAL_BIAS;
    extern int64_t INITIAL_N;
    extern int64_t MAX_INT;
}

namespace std_::url::punycode_error {
    struct PunycodeError : public std::enable_shared_from_this<PunycodeError> {
    std::string kind;
    int32_t index;
    std::string message;
    PunycodeError(std::string kind, int32_t index, std::string message) : kind(kind), index(index), message(message) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<PunycodeError>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace std_::url::punycode_error {
    doof::Result<std::string, std::shared_ptr<PunycodeError>> punycodeFailure__string(const std::string& kind, int32_t index, const std::string& message);
    doof::Result<std::shared_ptr<std::vector<int32_t>>, std::shared_ptr<PunycodeError>> punycodeFailure__array_int(const std::string& kind, int32_t index, const std::string& message);
}

namespace std_::url::punycode_utf8 {
    doof::Result<std::shared_ptr<std::vector<int32_t>>, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> decodePunycodeUtf8(const std::string& text);
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> encodePunycodeUtf8(const std::shared_ptr<std::vector<int32_t>>& codepoints);
}

namespace std_::url::punycode {
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> encodePunycodeLabel(const std::string& text);
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> decodePunycodeLabel(const std::string& text);
    int64_t threshold(int64_t k, int64_t bias);
    int64_t adapt(int64_t deltaValue, int64_t pointCount, bool firstTime);
    int32_t encodeDigit(int64_t digit);
    int32_t decodeDigit(int32_t value);
    void insertCodepoint(const std::shared_ptr<std::vector<int32_t>>& values, int32_t index, int32_t value);
    int32_t findLastByte(const std::string& text, int32_t target);
}
