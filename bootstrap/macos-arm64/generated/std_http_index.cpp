#include "std_http_index.hpp"

namespace std_::http::index {
using namespace ::std_::blob::index;
using namespace ::std_::stream::index;
using namespace ::std_::json::index;
using namespace ::std_::http::types;
using namespace ::std_::http::transport_url;

#line 51 "/std/http/index.do"
bool BodyChunkStream::next() {
#line 52 "/std/http/index.do"
    if (this->consumed) {
#line 53 "/std/http/index.do"
        return false;
    }
#line 56 "/std/http/index.do"
    (this->consumed = true);
#line 57 "/std/http/index.do"
    return true;
}
#line 60 "/std/http/index.do"
std::shared_ptr<std::vector<uint8_t>> BodyChunkStream::value() {
    return this->chunk;
}



#line 88 "/std/http/index.do"
std::optional<std::string> HttpRequest::header(const std::string& name) {
#line 89 "/std/http/index.do"
    const auto lowerName = doof::string_toLowerCase(name);
#line 90 "/std/http/index.do"
    const auto& _iterable_2 = this->headers;
    for (const auto& entry : *_iterable_2) {
#line 91 "/std/http/index.do"
        if (doof::string_toLowerCase(entry->name) == lowerName) {
#line 92 "/std/http/index.do"
            return entry->value;
        }
    }
#line 95 "/std/http/index.do"
    return std::nullopt;
}

#line 105 "/std/http/index.do"
bool HttpResponse::ok() {
#line 106 "/std/http/index.do"
    return ((this->status >= 200) && (this->status < 300));
}
#line 109 "/std/http/index.do"
std::optional<std::string> HttpResponse::header(const std::string& name) {
#line 110 "/std/http/index.do"
    const auto lowerName = doof::string_toLowerCase(name);
#line 111 "/std/http/index.do"
    const auto& _iterable_4 = this->headers;
    for (const auto& entry : *_iterable_4) {
#line 112 "/std/http/index.do"
        if (doof::string_toLowerCase(entry->name) == lowerName) {
#line 113 "/std/http/index.do"
            return entry->value;
        }
    }
#line 116 "/std/http/index.do"
    return std::nullopt;
}
#line 119 "/std/http/index.do"
std::shared_ptr<std::vector<uint8_t>> HttpResponse::getBlob() {
#line 120 "/std/http/index.do"
    return this->body;
}
#line 123 "/std/http/index.do"
std::string HttpResponse::getText() {
#line 124 "/std/http/index.do"
    const auto reader = ::doof_blob::NativeBlobReader::constructor(this->body, ::std_::blob::types::Endian::LittleEndian);
#line 125 "/std/http/index.do"
    return reader->readString(reader->remaining());
}
#line 128 "/std/http/index.do"
Stream__string HttpResponse::getLineStream() {
#line 129 "/std/http/index.do"
    return ::std_::stream::index::blobStreamToLineStream(std::make_shared<BodyChunkStream>(this->body, false));
}
#line 134 "/std/http/index.do"
doof::Result<doof::JsonValue, std::string> HttpResponse::getJsonValue() {
#line 135 "/std/http/index.do"
    return ::doof_json::parse(this->getText());
}

#line 143 "/std/http/index.do"
std::shared_ptr<HttpClient> createClient() {
#line 144 "/std/http/index.do"
    return std::make_shared<HttpClient>(std::make_shared<::NativeHttpClient>());
}
#line 149 "/std/http/index.do"
std::shared_ptr<HttpRequest> newRequest(const std::string& method, const std::string& url) {
#line 150 "/std/http/index.do"
    return std::make_shared<HttpRequest>(method, url, std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{}), nullptr, 30000, true);
}
#line 157 "/std/http/index.do"
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> get(const std::shared_ptr<HttpClient>& client, const std::string& url) {
#line 158 "/std/http/index.do"
    return send(client, newRequest(std::string("GET"), url));
}
#line 161 "/std/http/index.do"
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> postJsonValue(const std::shared_ptr<HttpClient>& client, const std::string& url, const doof::JsonValue& body) {
#line 162 "/std/http/index.do"
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
#line 163 "/std/http/index.do"
    builder->writeString(::doof_json::format(body));
#line 164 "/std/http/index.do"
    const auto headers = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{std::make_shared<::std_::http::types::HttpHeader>(std::string("Content-Type"), std::string("application/json"))});
#line 169 "/std/http/index.do"
    return send(client, std::make_shared<HttpRequest>(std::string("POST"), url, headers, builder->build(), 30000, true));
}
#line 179 "/std/http/index.do"
std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> parseCookieHeader(const std::string& header) {
#line 180 "/std/http/index.do"
    const std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> cookies = std::make_shared<std::vector<std::shared_ptr<Cookie>>>(std::vector<std::shared_ptr<Cookie>>{});
#line 181 "/std/http/index.do"
    const auto parts = doof::string_split(header, std::string(";"));
#line 182 "/std/http/index.do"
    const auto& _iterable_6 = parts;
    for (const auto& part : *_iterable_6) {
#line 183 "/std/http/index.do"
        const auto separator = doof::string_indexOf(part, std::string("="));
#line 184 "/std/http/index.do"
        if (separator <= 0) {
#line 185 "/std/http/index.do"
            continue;
        }
#line 188 "/std/http/index.do"
        const auto name = doof::string_trim(doof::string_substring(part, 0, separator));
#line 189 "/std/http/index.do"
        if (name == std::string("")) {
#line 190 "/std/http/index.do"
            continue;
        }
#line 193 "/std/http/index.do"
        cookies->push_back(std::make_shared<Cookie>(name, doof::string_trim(doof::string_slice(part, (separator + 1)))));
    }
#line 198 "/std/http/index.do"
    return doof::array_drainToReadonly(cookies, "", 0);
}
#line 201 "/std/http/index.do"
std::string renderCookieHeader(const std::shared_ptr<std::vector<std::shared_ptr<Cookie>>>& cookies) {
#line 202 "/std/http/index.do"
    auto text = std::string("");
#line 203 "/std/http/index.do"
    auto first = true;
#line 204 "/std/http/index.do"
    const auto& _iterable_8 = cookies;
    for (const auto& cookie : *_iterable_8) {
#line 205 "/std/http/index.do"
        if (cookie->name == std::string("")) {
#line 206 "/std/http/index.do"
            continue;
        }
#line 209 "/std/http/index.do"
        if (first) {
#line 210 "/std/http/index.do"
            (first = false);
        } else {
#line 212 "/std/http/index.do"
            (text += std::string("; "));
        }
#line 214 "/std/http/index.do"
        (text += ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(cookie->name); _interpolation += "="; _interpolation += doof::to_string(cookie->value); _interpolation += ""; return _interpolation; }()));
    }
#line 216 "/std/http/index.do"
    return text;
}
#line 219 "/std/http/index.do"
std::shared_ptr<SetCookie> parseSetCookieHeader(const std::string& header) {
#line 220 "/std/http/index.do"
    const auto parts = doof::string_split(header, std::string(";"));
#line 221 "/std/http/index.do"
    if (static_cast<int32_t>((parts)->size()) == 0) {
#line 222 "/std/http/index.do"
        return nullptr;
    }
#line 225 "/std/http/index.do"
    const auto firstPart = doof::string_trim(doof::array_at(parts, 0, "index", 225));
#line 226 "/std/http/index.do"
    const auto firstSeparator = doof::string_indexOf(firstPart, std::string("="));
#line 227 "/std/http/index.do"
    if (firstSeparator <= 0) {
#line 228 "/std/http/index.do"
        return nullptr;
    }
#line 231 "/std/http/index.do"
    const auto name = doof::string_trim(doof::string_substring(firstPart, 0, firstSeparator));
#line 232 "/std/http/index.do"
    if (name == std::string("")) {
#line 233 "/std/http/index.do"
        return nullptr;
    }
#line 236 "/std/http/index.do"
    std::optional<std::string> domain = std::nullopt;
#line 237 "/std/http/index.do"
    std::optional<std::string> path = std::nullopt;
#line 238 "/std/http/index.do"
    std::optional<std::string> expires = std::nullopt;
#line 239 "/std/http/index.do"
    std::optional<std::string> maxAge = std::nullopt;
#line 240 "/std/http/index.do"
    auto secure = false;
#line 241 "/std/http/index.do"
    auto httpOnly = false;
#line 242 "/std/http/index.do"
    std::optional<std::string> sameSite = std::nullopt;
#line 244 "/std/http/index.do"
    auto index = 1;
#line 245 "/std/http/index.do"
    while (index < static_cast<int32_t>((parts)->size())) {
#line 246 "/std/http/index.do"
        const auto attribute = doof::string_trim(doof::array_at(parts, index, "index", 246));
#line 247 "/std/http/index.do"
        (index += 1);
#line 248 "/std/http/index.do"
        if (attribute == std::string("")) {
#line 249 "/std/http/index.do"
            continue;
        }
#line 252 "/std/http/index.do"
        const auto separator = doof::string_indexOf(attribute, std::string("="));
#line 253 "/std/http/index.do"
        auto attributeName = attribute;
#line 254 "/std/http/index.do"
        auto attributeValue = std::string("");
#line 255 "/std/http/index.do"
        if (separator >= 0) {
#line 256 "/std/http/index.do"
            (attributeName = doof::string_trim(doof::string_substring(attribute, 0, separator)));
#line 257 "/std/http/index.do"
            (attributeValue = doof::string_trim(doof::string_slice(attribute, (separator + 1))));
        }
#line 260 "/std/http/index.do"
        const auto lowerName = doof::string_toLowerCase(attributeName);
#line 261 "/std/http/index.do"
        if (lowerName == std::string("domain")) {
#line 262 "/std/http/index.do"
            (domain = attributeValue);
        } else if (lowerName == std::string("path")) {
#line 264 "/std/http/index.do"
            (path = attributeValue);
        } else if (lowerName == std::string("expires")) {
#line 266 "/std/http/index.do"
            (expires = attributeValue);
        } else if (lowerName == std::string("max-age")) {
#line 268 "/std/http/index.do"
            (maxAge = attributeValue);
        } else if (lowerName == std::string("secure")) {
#line 270 "/std/http/index.do"
            (secure = true);
        } else if (lowerName == std::string("httponly")) {
#line 272 "/std/http/index.do"
            (httpOnly = true);
        } else if (lowerName == std::string("samesite")) {
#line 274 "/std/http/index.do"
            (sameSite = attributeValue);
        }
    }
#line 278 "/std/http/index.do"
    return std::make_shared<SetCookie>(name, doof::string_trim(doof::string_slice(firstPart, (firstSeparator + 1))), domain, path, expires, maxAge, secure, httpOnly, sameSite);
}
#line 291 "/std/http/index.do"
std::string renderSetCookieHeader(const std::shared_ptr<SetCookie>& cookie) {
#line 292 "/std/http/index.do"
    auto text = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(cookie->name); _interpolation += "="; _interpolation += doof::to_string(cookie->value); _interpolation += ""; return _interpolation; }());
#line 293 "/std/http/index.do"
    const auto expires = cookie->expires;
#line 294 "/std/http/index.do"
    if (!doof::is_null(expires)) {
#line 295 "/std/http/index.do"
        (text += ([&]() -> std::string { std::string _interpolation = "; Expires="; _interpolation += doof::to_string(expires.value()); _interpolation += ""; return _interpolation; }()));
    }
#line 297 "/std/http/index.do"
    const auto maxAge = cookie->maxAge;
#line 298 "/std/http/index.do"
    if (!doof::is_null(maxAge)) {
#line 299 "/std/http/index.do"
        (text += ([&]() -> std::string { std::string _interpolation = "; Max-Age="; _interpolation += doof::to_string(maxAge.value()); _interpolation += ""; return _interpolation; }()));
    }
#line 301 "/std/http/index.do"
    const auto domain = cookie->domain;
#line 302 "/std/http/index.do"
    if (!doof::is_null(domain)) {
#line 303 "/std/http/index.do"
        (text += ([&]() -> std::string { std::string _interpolation = "; Domain="; _interpolation += doof::to_string(domain.value()); _interpolation += ""; return _interpolation; }()));
    }
#line 305 "/std/http/index.do"
    const auto path = cookie->path;
#line 306 "/std/http/index.do"
    if (!doof::is_null(path)) {
#line 307 "/std/http/index.do"
        (text += ([&]() -> std::string { std::string _interpolation = "; Path="; _interpolation += doof::to_string(path.value()); _interpolation += ""; return _interpolation; }()));
    }
#line 309 "/std/http/index.do"
    const auto sameSite = cookie->sameSite;
#line 310 "/std/http/index.do"
    if (!doof::is_null(sameSite)) {
#line 311 "/std/http/index.do"
        (text += ([&]() -> std::string { std::string _interpolation = "; SameSite="; _interpolation += doof::to_string(sameSite.value()); _interpolation += ""; return _interpolation; }()));
    }
#line 313 "/std/http/index.do"
    if (cookie->secure) {
#line 314 "/std/http/index.do"
        (text += std::string("; Secure"));
    }
#line 316 "/std/http/index.do"
    if (cookie->httpOnly) {
#line 317 "/std/http/index.do"
        (text += std::string("; HttpOnly"));
    }
#line 319 "/std/http/index.do"
    return text;
}
#line 322 "/std/http/index.do"
std::optional<std::string> cookieValue(const std::shared_ptr<std::vector<std::shared_ptr<Cookie>>>& cookies, const std::string& name) {
#line 323 "/std/http/index.do"
    const auto& _iterable_10 = cookies;
    for (const auto& cookie : *_iterable_10) {
#line 324 "/std/http/index.do"
        if (cookie->name == name) {
#line 325 "/std/http/index.do"
            return cookie->value;
        }
    }
#line 328 "/std/http/index.do"
    return std::nullopt;
}
#line 331 "/std/http/index.do"
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> send(const std::shared_ptr<HttpClient>& client, const std::shared_ptr<HttpRequest>& request) {
#line 332 "/std/http/index.do"
    auto _binding_value_11 = ::std_::http::transport_url::prepareTransportUrl(request->url);
    if (doof::is_failure(_binding_value_11)) {
        const auto error = doof::failure_error(_binding_value_11);
#line 333 "/std/http/index.do"
        return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ error };
    }
    const auto transportUrl = doof::success_value(_binding_value_11);
#line 335 "/std/http/index.do"
    const auto nativeResult = client->native->perform(request->method, transportUrl, renderHeaders(request->headers), request->body, request->timeoutMs, request->followRedirects);
#line 344 "/std/http/index.do"
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
#line 359 "/std/http/index.do"
std::string renderHeaders(const std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>& headers) {
#line 360 "/std/http/index.do"
    auto text = std::string("");
#line 361 "/std/http/index.do"
    const auto& _iterable_13 = headers;
    for (const auto& header : *_iterable_13) {
#line 362 "/std/http/index.do"
        (text += ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(header->name); _interpolation += ": "; _interpolation += doof::to_string(header->value); _interpolation += "\r\n"; return _interpolation; }()));
    }
#line 364 "/std/http/index.do"
    return text;
}
#line 367 "/std/http/index.do"
std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> parseHeaders(const std::string& headerText) {
#line 368 "/std/http/index.do"
    const std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{});
#line 369 "/std/http/index.do"
    const auto lines = doof::string_split(headerText, std::string("\r\n"));
#line 370 "/std/http/index.do"
    const auto& _iterable_15 = lines;
    for (const auto& line : *_iterable_15) {
#line 371 "/std/http/index.do"
        if (line == std::string("")) {
#line 372 "/std/http/index.do"
            continue;
        }
#line 375 "/std/http/index.do"
        const auto separator = doof::string_indexOf(line, std::string(":"));
#line 376 "/std/http/index.do"
        if (separator <= 0) {
#line 377 "/std/http/index.do"
            continue;
        }
#line 380 "/std/http/index.do"
        headers->push_back(std::make_shared<::std_::http::types::HttpHeader>(doof::string_trim(doof::string_substring(line, 0, separator)), doof::string_trim(doof::string_slice(line, (separator + 1)))));
    }
#line 385 "/std/http/index.do"
    return doof::array_drainToReadonly(headers, "", 0);
}
#line 388 "/std/http/index.do"
std::shared_ptr<::std_::http::types::HttpError> parseError(const std::string& raw) {
#line 389 "/std/http/index.do"
    const auto firstSeparator = doof::string_indexOf(raw, std::string("|"));
#line 390 "/std/http/index.do"
    if (firstSeparator < 0) {
#line 391 "/std/http/index.do"
        return std::make_shared<::std_::http::types::HttpError>(std::string("transport"), std::string("0"), raw);
    }
#line 398 "/std/http/index.do"
    const auto remainder = doof::string_slice(raw, (firstSeparator + 1));
#line 399 "/std/http/index.do"
    const auto secondSeparator = doof::string_indexOf(remainder, std::string("|"));
#line 400 "/std/http/index.do"
    if (secondSeparator < 0) {
#line 401 "/std/http/index.do"
        return std::make_shared<::std_::http::types::HttpError>(doof::string_substring(raw, 0, firstSeparator), std::string("0"), remainder);
    }
#line 408 "/std/http/index.do"
    const auto kind = doof::string_substring(raw, 0, firstSeparator);
#line 409 "/std/http/index.do"
    const auto codeText = doof::string_substring(remainder, 0, secondSeparator);
#line 410 "/std/http/index.do"
    const auto message = doof::string_slice(remainder, (secondSeparator + 1));
#line 412 "/std/http/index.do"
    return std::make_shared<::std_::http::types::HttpError>(kind, codeText, message);
}
#line 1 "<doof-generated>"
}
