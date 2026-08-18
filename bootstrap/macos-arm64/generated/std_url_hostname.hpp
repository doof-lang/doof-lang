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

namespace std_::url::punycode {
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> encodePunycodeLabel(const std::string& text);
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> decodePunycodeLabel(const std::string& text);
}

namespace std_::url::hostname {
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToAscii(const std::string& hostname);
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToUnicode(const std::string& hostname);
    bool containsNonAscii(const std::string& text);
    bool isBracketedHost(const std::string& hostname);
    std::shared_ptr<::std_::url::punycode_error::PunycodeError> offsetError(const std::shared_ptr<::std_::url::punycode_error::PunycodeError>& error, int32_t offset);
}
