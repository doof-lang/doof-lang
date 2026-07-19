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
namespace std_::blob::index { struct BlobReader; }
namespace std_::blob::index { struct BlobBuilder; }
namespace std_::http::types { struct HttpError; }
namespace std_::http::types { struct HttpHeader; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::http::index {
    struct BodyChunkStream;
    struct Cookie;
    struct SetCookie;
    struct HttpRequest;
    struct HttpResponse;
    struct HttpClient;
}

#include "std_blob_index.hpp"
#include "std_stream_index.hpp"
#include "std_json_index.hpp"
#include "std_http_types.hpp"
#include "std_http_websocket.hpp"

#include "std/http/native_http_client.hpp"

namespace std_::http::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct BodyChunkStream : public std::enable_shared_from_this<BodyChunkStream> {
    std::shared_ptr<std::vector<uint8_t>> chunk = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    bool consumed = false;
    BodyChunkStream(std::shared_ptr<std::vector<uint8_t>> chunk = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), bool consumed = false) : chunk(chunk), consumed(consumed) {}
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<BodyChunkStream>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct Cookie : public std::enable_shared_from_this<Cookie> {
    std::string name;
    std::string value;
    Cookie(std::string name, std::string value) : name(name), value(value) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Cookie>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct SetCookie : public std::enable_shared_from_this<SetCookie> {
    std::string name;
    std::string value;
    std::optional<std::string> domain = std::nullopt;
    std::optional<std::string> path = std::nullopt;
    std::optional<std::string> expires = std::nullopt;
    std::optional<std::string> maxAge = std::nullopt;
    bool secure = false;
    bool httpOnly = false;
    std::optional<std::string> sameSite = std::nullopt;
    SetCookie(std::string name, std::string value, std::optional<std::string> domain = std::nullopt, std::optional<std::string> path = std::nullopt, std::optional<std::string> expires = std::nullopt, std::optional<std::string> maxAge = std::nullopt, bool secure = false, bool httpOnly = false, std::optional<std::string> sameSite = std::nullopt) : name(name), value(value), domain(domain), path(path), expires(expires), maxAge(maxAge), secure(secure), httpOnly(httpOnly), sameSite(sameSite) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<SetCookie>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct HttpRequest : public std::enable_shared_from_this<HttpRequest> {
    std::string method;
    std::string url;
    std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers;
    std::shared_ptr<std::vector<uint8_t>> body = nullptr;
    int32_t timeoutMs = 30000;
    bool followRedirects = true;
    HttpRequest(std::string method, std::string url, std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers, std::shared_ptr<std::vector<uint8_t>> body, int32_t timeoutMs, bool followRedirects) : method(method), url(url), headers(headers), body(body), timeoutMs(timeoutMs), followRedirects(followRedirects) {}
    std::optional<std::string> header(std::string name);
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<HttpRequest>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct HttpResponse : public std::enable_shared_from_this<HttpResponse> {
    int32_t status;
    std::string statusText;
    std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers;
    std::shared_ptr<std::vector<uint8_t>> body;
    HttpResponse(int32_t status, std::string statusText, std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers, std::shared_ptr<std::vector<uint8_t>> body) : status(status), statusText(statusText), headers(headers), body(body) {}
    bool ok();
    std::optional<std::string> header(std::string name);
    std::shared_ptr<std::vector<uint8_t>> getBlob();
    std::string getText();
    Stream__string getLineStream();
    doof::Result<doof::JsonValue, std::string> getJsonValue();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<HttpResponse>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct HttpClient : public std::enable_shared_from_this<HttpClient> {
    std::shared_ptr<::NativeHttpClient> native;
    HttpClient(std::shared_ptr<::NativeHttpClient> native) : native(native) {}
};
    std::shared_ptr<HttpClient> createClient();
    std::shared_ptr<HttpRequest> newRequest(std::string method, std::string url);
    doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> get(std::shared_ptr<HttpClient> client, std::string url);
    doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> postJsonValue(std::shared_ptr<HttpClient> client, std::string url, doof::JsonValue body);
    std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> parseCookieHeader(std::string header);
    std::string renderCookieHeader(std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> cookies);
    std::shared_ptr<SetCookie> parseSetCookieHeader(std::string header);
    std::string renderSetCookieHeader(std::shared_ptr<SetCookie> cookie);
    std::optional<std::string> cookieValue(std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> cookies, std::string name);
    doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> send(std::shared_ptr<HttpClient> client, std::shared_ptr<HttpRequest> request);
    std::string renderHeaders(std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers);
    std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> parseHeaders(std::string headerText);
    std::shared_ptr<::std_::http::types::HttpError> parseError(std::string raw);
}

namespace std_::http::index {
}
