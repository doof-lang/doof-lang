#pragma once
#include "doof_runtime.hpp"
namespace std_::http::types {
    struct HttpHeader;
    struct HttpError;
}

namespace std_::http::types {
    struct HttpHeader : public std::enable_shared_from_this<HttpHeader> {
    std::string name;
    std::string value;
    HttpHeader(std::string name, std::string value) : name(name), value(value) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<HttpHeader>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct HttpError : public std::enable_shared_from_this<HttpError> {
    std::string kind;
    std::string code;
    std::string message;
    HttpError(std::string kind, std::string code, std::string message) : kind(kind), code(code), message(message) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<HttpError>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}
