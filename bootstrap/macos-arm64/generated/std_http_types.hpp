#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::http::types {
    struct HttpHeader;
    struct HttpError;
}

namespace std_::http::types {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
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

namespace std_::http::types {
}
