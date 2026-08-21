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
};
    struct HttpError : public std::enable_shared_from_this<HttpError> {
    std::string kind;
    std::string code;
    std::string message;
    HttpError(std::string kind, std::string code, std::string message) : kind(kind), code(code), message(message) {}
};
}
