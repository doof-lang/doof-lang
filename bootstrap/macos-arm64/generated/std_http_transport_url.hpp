#pragma once
#include "doof_runtime.hpp"
namespace std_::http::types {
    struct HttpError;
}

namespace std_::url::punycode_error {
    struct PunycodeError;
}

namespace std_::http::types {
    struct HttpError : public std::enable_shared_from_this<HttpError> {
    std::string kind;
    std::string code;
    std::string message;
    HttpError(std::string kind, std::string code, std::string message) : kind(kind), code(code), message(message) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<HttpError>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
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

namespace std_::url::hostname {
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToAscii(const std::string& hostname);
}

namespace std_::http::transport_url {
    doof::Result<std::string, std::shared_ptr<::std_::http::types::HttpError>> prepareTransportUrl(const std::string& url);
    int32_t findAuthorityEnd(const std::string& url, int32_t start);
    int32_t findLastByteInRange(const std::string& text, int32_t target, int32_t start, int32_t end);
}
