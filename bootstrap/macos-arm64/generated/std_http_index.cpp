#include "std_http_index.hpp"

namespace std_::http::index {
using namespace ::std_::blob::index;
using namespace ::std_::stream::index;
using namespace ::std_::json::index;
using namespace ::std_::http::types;
using namespace ::std_::http::transport_url;

bool BodyChunkStream::next() {
    if (this->consumed) {
        return false;
    }
    (this->consumed = true);
    return true;
}
std::shared_ptr<std::vector<uint8_t>> BodyChunkStream::value() {
    return this->chunk;
}



std::optional<std::string> HttpRequest::header(const std::string& name) {
    const auto lowerName = doof::string_toLowerCase(name);
    const auto& _iterable_2 = this->headers;
    for (const auto& entry : *_iterable_2) {
        if (doof::string_toLowerCase(entry->name) == lowerName) {
            return entry->value;
        }
    }
    return std::nullopt;
}

bool HttpResponse::ok() {
    return ((this->status >= 200) && (this->status < 300));
}
std::optional<std::string> HttpResponse::header(const std::string& name) {
    const auto lowerName = doof::string_toLowerCase(name);
    const auto& _iterable_4 = this->headers;
    for (const auto& entry : *_iterable_4) {
        if (doof::string_toLowerCase(entry->name) == lowerName) {
            return entry->value;
        }
    }
    return std::nullopt;
}
std::shared_ptr<std::vector<uint8_t>> HttpResponse::getBlob() {
    return this->body;
}
std::string HttpResponse::getText() {
    const auto reader = ::doof_blob::NativeBlobReader::constructor(this->body, ::std_::blob::types::Endian::LittleEndian);
    return reader->readString(reader->remaining());
}
Stream__string HttpResponse::getLineStream() {
    return ::std_::stream::index::blobStreamToLineStream(std::make_shared<BodyChunkStream>(this->body, false));
}
doof::Result<doof::JsonValue, std::string> HttpResponse::getJsonValue() {
    return ::doof_json::parse(this->getText());
}

std::shared_ptr<HttpClient> createClient() {
    return std::make_shared<HttpClient>(std::make_shared<::NativeHttpClient>());
}
std::shared_ptr<HttpRequest> newRequest(const std::string& method, const std::string& url) {
    return std::make_shared<HttpRequest>(method, url, std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{}), nullptr, 30000, true);
}
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> get(const std::shared_ptr<HttpClient>& client, const std::string& url) {
    return send(client, newRequest(std::string("GET"), url));
}
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> postJsonValue(const std::shared_ptr<HttpClient>& client, const std::string& url, const doof::JsonValue& body) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeString(::doof_json::format(body));
    const auto headers = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{std::make_shared<::std_::http::types::HttpHeader>(std::string("Content-Type"), std::string("application/json"))});
    return send(client, std::make_shared<HttpRequest>(std::string("POST"), url, headers, builder->build(), 30000, true));
}
std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> parseCookieHeader(const std::string& header) {
    const std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> cookies = std::make_shared<std::vector<std::shared_ptr<Cookie>>>(std::vector<std::shared_ptr<Cookie>>{});
    const auto parts = doof::string_split(header, std::string(";"));
    const auto& _iterable_6 = parts;
    for (const auto& part : *_iterable_6) {
        const auto separator = doof::string_indexOf(part, std::string("="));
        if (separator <= 0) {
            continue;
        }
        const auto name = doof::string_trim(doof::string_substring(part, 0, separator));
        if (name == std::string("")) {
            continue;
        }
        cookies->push_back(std::make_shared<Cookie>(name, doof::string_trim(doof::string_slice(part, (separator + 1)))));
    }
    return doof::array_drainToReadonly(cookies, "", 0);
}
std::string renderCookieHeader(const std::shared_ptr<std::vector<std::shared_ptr<Cookie>>>& cookies) {
    auto text = std::string("");
    auto first = true;
    const auto& _iterable_8 = cookies;
    for (const auto& cookie : *_iterable_8) {
        if (cookie->name == std::string("")) {
            continue;
        }
        if (first) {
            (first = false);
        } else {
            (text += std::string("; "));
        }
        (text += ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(cookie->name); _interpolation += "="; _interpolation += doof::to_string(cookie->value); _interpolation += ""; return _interpolation; }()));
    }
    return text;
}
std::shared_ptr<SetCookie> parseSetCookieHeader(const std::string& header) {
    const auto parts = doof::string_split(header, std::string(";"));
    if (static_cast<int32_t>((parts)->size()) == 0) {
        return nullptr;
    }
    const auto firstPart = doof::string_trim(doof::array_at(parts, 0, "index", 225));
    const auto firstSeparator = doof::string_indexOf(firstPart, std::string("="));
    if (firstSeparator <= 0) {
        return nullptr;
    }
    const auto name = doof::string_trim(doof::string_substring(firstPart, 0, firstSeparator));
    if (name == std::string("")) {
        return nullptr;
    }
    std::optional<std::string> domain = std::nullopt;
    std::optional<std::string> path = std::nullopt;
    std::optional<std::string> expires = std::nullopt;
    std::optional<std::string> maxAge = std::nullopt;
    auto secure = false;
    auto httpOnly = false;
    std::optional<std::string> sameSite = std::nullopt;
    auto index = 1;
    while (index < static_cast<int32_t>((parts)->size())) {
        const auto attribute = doof::string_trim(doof::array_at(parts, index, "index", 246));
        (index += 1);
        if (attribute == std::string("")) {
            continue;
        }
        const auto separator = doof::string_indexOf(attribute, std::string("="));
        auto attributeName = attribute;
        auto attributeValue = std::string("");
        if (separator >= 0) {
            (attributeName = doof::string_trim(doof::string_substring(attribute, 0, separator)));
            (attributeValue = doof::string_trim(doof::string_slice(attribute, (separator + 1))));
        }
        const auto lowerName = doof::string_toLowerCase(attributeName);
        if (lowerName == std::string("domain")) {
            (domain = attributeValue);
        } else if (lowerName == std::string("path")) {
            (path = attributeValue);
        } else if (lowerName == std::string("expires")) {
            (expires = attributeValue);
        } else if (lowerName == std::string("max-age")) {
            (maxAge = attributeValue);
        } else if (lowerName == std::string("secure")) {
            (secure = true);
        } else if (lowerName == std::string("httponly")) {
            (httpOnly = true);
        } else if (lowerName == std::string("samesite")) {
            (sameSite = attributeValue);
        }
    }
    return std::make_shared<SetCookie>(name, doof::string_trim(doof::string_slice(firstPart, (firstSeparator + 1))), domain, path, expires, maxAge, secure, httpOnly, sameSite);
}
std::string renderSetCookieHeader(const std::shared_ptr<SetCookie>& cookie) {
    auto text = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(cookie->name); _interpolation += "="; _interpolation += doof::to_string(cookie->value); _interpolation += ""; return _interpolation; }());
    const auto expires = cookie->expires;
    if (!doof::is_null(expires)) {
        (text += ([&]() -> std::string { std::string _interpolation = "; Expires="; _interpolation += doof::to_string(expires.value()); _interpolation += ""; return _interpolation; }()));
    }
    const auto maxAge = cookie->maxAge;
    if (!doof::is_null(maxAge)) {
        (text += ([&]() -> std::string { std::string _interpolation = "; Max-Age="; _interpolation += doof::to_string(maxAge.value()); _interpolation += ""; return _interpolation; }()));
    }
    const auto domain = cookie->domain;
    if (!doof::is_null(domain)) {
        (text += ([&]() -> std::string { std::string _interpolation = "; Domain="; _interpolation += doof::to_string(domain.value()); _interpolation += ""; return _interpolation; }()));
    }
    const auto path = cookie->path;
    if (!doof::is_null(path)) {
        (text += ([&]() -> std::string { std::string _interpolation = "; Path="; _interpolation += doof::to_string(path.value()); _interpolation += ""; return _interpolation; }()));
    }
    const auto sameSite = cookie->sameSite;
    if (!doof::is_null(sameSite)) {
        (text += ([&]() -> std::string { std::string _interpolation = "; SameSite="; _interpolation += doof::to_string(sameSite.value()); _interpolation += ""; return _interpolation; }()));
    }
    if (cookie->secure) {
        (text += std::string("; Secure"));
    }
    if (cookie->httpOnly) {
        (text += std::string("; HttpOnly"));
    }
    return text;
}
std::optional<std::string> cookieValue(const std::shared_ptr<std::vector<std::shared_ptr<Cookie>>>& cookies, const std::string& name) {
    const auto& _iterable_10 = cookies;
    for (const auto& cookie : *_iterable_10) {
        if (cookie->name == name) {
            return cookie->value;
        }
    }
    return std::nullopt;
}
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> send(const std::shared_ptr<HttpClient>& client, const std::shared_ptr<HttpRequest>& request) {
    auto _binding_value_11 = ::std_::http::transport_url::prepareTransportUrl(request->url);
    if (doof::is_failure(_binding_value_11)) {
        const auto error = doof::failure_error(_binding_value_11);
        return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ error };
    }
    const auto transportUrl = doof::success_value(_binding_value_11);
    const auto nativeResult = client->native->perform(request->method, transportUrl, renderHeaders(request->headers), request->body, request->timeoutMs, request->followRedirects);
    return [&]() -> doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> {
    auto _case_subject = nativeResult;
    if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
        const auto& s = std::get<doof::Success<int32_t>>(_case_subject);
        return doof::Success<std::shared_ptr<HttpResponse>>{ std::make_shared<HttpResponse>(s.value, client->native->responseStatusText(), parseHeaders(client->native->responseHeadersText()), client->native->responseBody()) };
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
        return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ parseError(f.error) };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
std::string renderHeaders(const std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>& headers) {
    auto text = std::string("");
    const auto& _iterable_13 = headers;
    for (const auto& header : *_iterable_13) {
        (text += ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(header->name); _interpolation += ": "; _interpolation += doof::to_string(header->value); _interpolation += "\r\n"; return _interpolation; }()));
    }
    return text;
}
std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> parseHeaders(const std::string& headerText) {
    const std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{});
    const auto lines = doof::string_split(headerText, std::string("\r\n"));
    const auto& _iterable_15 = lines;
    for (const auto& line : *_iterable_15) {
        if (line == std::string("")) {
            continue;
        }
        const auto separator = doof::string_indexOf(line, std::string(":"));
        if (separator <= 0) {
            continue;
        }
        headers->push_back(std::make_shared<::std_::http::types::HttpHeader>(doof::string_trim(doof::string_substring(line, 0, separator)), doof::string_trim(doof::string_slice(line, (separator + 1)))));
    }
    return doof::array_drainToReadonly(headers, "", 0);
}
std::shared_ptr<::std_::http::types::HttpError> parseError(const std::string& raw) {
    const auto firstSeparator = doof::string_indexOf(raw, std::string("|"));
    if (firstSeparator < 0) {
        return std::make_shared<::std_::http::types::HttpError>(std::string("transport"), std::string("0"), raw);
    }
    const auto remainder = doof::string_slice(raw, (firstSeparator + 1));
    const auto secondSeparator = doof::string_indexOf(remainder, std::string("|"));
    if (secondSeparator < 0) {
        return std::make_shared<::std_::http::types::HttpError>(doof::string_substring(raw, 0, firstSeparator), std::string("0"), remainder);
    }
    const auto kind = doof::string_substring(raw, 0, firstSeparator);
    const auto codeText = doof::string_substring(remainder, 0, secondSeparator);
    const auto message = doof::string_slice(remainder, (secondSeparator + 1));
    return std::make_shared<::std_::http::types::HttpError>(kind, codeText, message);
}
}
