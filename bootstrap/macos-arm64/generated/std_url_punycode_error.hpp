#pragma once
#include "doof_runtime.hpp"
namespace std_::url::punycode_error {
    struct PunycodeError;
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
