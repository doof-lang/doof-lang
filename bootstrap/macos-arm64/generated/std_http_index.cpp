#include "std_http_index.hpp"
#include <cmath>
#include "std_blob_index.hpp"
#include "std_stream_index.hpp"
#include "std_json_index.hpp"
#include "std_http_types.hpp"
#include "std_http_websocket.hpp"
#include "std_fs_index.hpp"
#include "std_os_index.hpp"

namespace std_::http::index {
using namespace ::std_::blob::index;
using namespace ::std_::stream::index;
using namespace ::std_::json::index;
using namespace ::std_::http::types;

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
doof::JsonObject BodyChunkStream::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["chunk"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->chunk->size()); for (const auto& _element : *this->chunk) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    (*_json)["consumed"] = doof::json_value(this->consumed);
    return _json;
}
doof::Result<std::shared_ptr<BodyChunkStream>, std::string> BodyChunkStream::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<uint8_t>>> _field_chunk;
    if (auto _iterator_chunk = _object->find("chunk"); _iterator_chunk != _object->end()) {
        if (!(doof::json_is_array(_iterator_chunk->second))) { return doof::Failure<std::string>{"Field \"chunk\" expected array but got " + std::string(doof::json_type_name(_iterator_chunk->second))}; }
        _field_chunk = [&]() { const auto* _array = doof::json_as_array(_iterator_chunk->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_chunk = std::shared_ptr<std::vector<uint8_t>>{std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{})};
    }
    std::optional<bool> _field_consumed;
    if (auto _iterator_consumed = _object->find("consumed"); _iterator_consumed != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_consumed->second) : doof::json_is_boolean(_iterator_consumed->second)))) { return doof::Failure<std::string>{"Field \"consumed\" expected boolean but got " + std::string(doof::json_type_name(_iterator_consumed->second))}; }
        _field_consumed = (_lenient ? doof::json_as_bool_lenient(_iterator_consumed->second) : doof::json_as_bool(_iterator_consumed->second));
    } else {
        _field_consumed = bool{false};
    }
    return doof::Success<std::shared_ptr<BodyChunkStream>>{std::make_shared<BodyChunkStream>(_field_chunk.value(), _field_consumed.value())};
}

doof::JsonObject Cookie::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["value"] = doof::json_value(this->value);
    return _json;
}
doof::Result<std::shared_ptr<Cookie>, std::string> Cookie::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_value = _object->find("value");
    if (_iterator_value == _object->end()) { return doof::Failure<std::string>{"Missing required field \"value\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_value->second) : doof::json_is_string(_iterator_value->second)))) { return doof::Failure<std::string>{"Field \"value\" expected string but got " + std::string(doof::json_type_name(_iterator_value->second))}; }
    auto _field_value = (_lenient ? doof::json_as_string_lenient(_iterator_value->second) : doof::json_as_string(_iterator_value->second));
    return doof::Success<std::shared_ptr<Cookie>>{std::make_shared<Cookie>(_field_name, _field_value)};
}

doof::JsonObject SetCookie::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["value"] = doof::json_value(this->value);
    (*_json)["domain"] = (this->domain.has_value() ? doof::json_value(this->domain.value()) : doof::json_value(nullptr));
    (*_json)["path"] = (this->path.has_value() ? doof::json_value(this->path.value()) : doof::json_value(nullptr));
    (*_json)["expires"] = (this->expires.has_value() ? doof::json_value(this->expires.value()) : doof::json_value(nullptr));
    (*_json)["maxAge"] = (this->maxAge.has_value() ? doof::json_value(this->maxAge.value()) : doof::json_value(nullptr));
    (*_json)["secure"] = doof::json_value(this->secure);
    (*_json)["httpOnly"] = doof::json_value(this->httpOnly);
    (*_json)["sameSite"] = (this->sameSite.has_value() ? doof::json_value(this->sameSite.value()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<SetCookie>, std::string> SetCookie::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_value = _object->find("value");
    if (_iterator_value == _object->end()) { return doof::Failure<std::string>{"Missing required field \"value\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_value->second) : doof::json_is_string(_iterator_value->second)))) { return doof::Failure<std::string>{"Field \"value\" expected string but got " + std::string(doof::json_type_name(_iterator_value->second))}; }
    auto _field_value = (_lenient ? doof::json_as_string_lenient(_iterator_value->second) : doof::json_as_string(_iterator_value->second));
    std::optional<std::optional<std::string>> _field_domain;
    if (auto _iterator_domain = _object->find("domain"); _iterator_domain != _object->end()) {
        if (!(doof::json_is_null(_iterator_domain->second) || (_lenient ? doof::json_is_lenient_string(_iterator_domain->second) : doof::json_is_string(_iterator_domain->second)))) { return doof::Failure<std::string>{"Field \"domain\" expected string or null but got " + std::string(doof::json_type_name(_iterator_domain->second))}; }
        _field_domain = (doof::json_is_null(_iterator_domain->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_domain->second) : doof::json_as_string(_iterator_domain->second))});
    } else {
        _field_domain = std::optional<std::string>{std::nullopt};
    }
    std::optional<std::optional<std::string>> _field_path;
    if (auto _iterator_path = _object->find("path"); _iterator_path != _object->end()) {
        if (!(doof::json_is_null(_iterator_path->second) || (_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string or null but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
        _field_path = (doof::json_is_null(_iterator_path->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second))});
    } else {
        _field_path = std::optional<std::string>{std::nullopt};
    }
    std::optional<std::optional<std::string>> _field_expires;
    if (auto _iterator_expires = _object->find("expires"); _iterator_expires != _object->end()) {
        if (!(doof::json_is_null(_iterator_expires->second) || (_lenient ? doof::json_is_lenient_string(_iterator_expires->second) : doof::json_is_string(_iterator_expires->second)))) { return doof::Failure<std::string>{"Field \"expires\" expected string or null but got " + std::string(doof::json_type_name(_iterator_expires->second))}; }
        _field_expires = (doof::json_is_null(_iterator_expires->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_expires->second) : doof::json_as_string(_iterator_expires->second))});
    } else {
        _field_expires = std::optional<std::string>{std::nullopt};
    }
    std::optional<std::optional<std::string>> _field_maxAge;
    if (auto _iterator_maxAge = _object->find("maxAge"); _iterator_maxAge != _object->end()) {
        if (!(doof::json_is_null(_iterator_maxAge->second) || (_lenient ? doof::json_is_lenient_string(_iterator_maxAge->second) : doof::json_is_string(_iterator_maxAge->second)))) { return doof::Failure<std::string>{"Field \"maxAge\" expected string or null but got " + std::string(doof::json_type_name(_iterator_maxAge->second))}; }
        _field_maxAge = (doof::json_is_null(_iterator_maxAge->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_maxAge->second) : doof::json_as_string(_iterator_maxAge->second))});
    } else {
        _field_maxAge = std::optional<std::string>{std::nullopt};
    }
    std::optional<bool> _field_secure;
    if (auto _iterator_secure = _object->find("secure"); _iterator_secure != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_secure->second) : doof::json_is_boolean(_iterator_secure->second)))) { return doof::Failure<std::string>{"Field \"secure\" expected boolean but got " + std::string(doof::json_type_name(_iterator_secure->second))}; }
        _field_secure = (_lenient ? doof::json_as_bool_lenient(_iterator_secure->second) : doof::json_as_bool(_iterator_secure->second));
    } else {
        _field_secure = bool{false};
    }
    std::optional<bool> _field_httpOnly;
    if (auto _iterator_httpOnly = _object->find("httpOnly"); _iterator_httpOnly != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_httpOnly->second) : doof::json_is_boolean(_iterator_httpOnly->second)))) { return doof::Failure<std::string>{"Field \"httpOnly\" expected boolean but got " + std::string(doof::json_type_name(_iterator_httpOnly->second))}; }
        _field_httpOnly = (_lenient ? doof::json_as_bool_lenient(_iterator_httpOnly->second) : doof::json_as_bool(_iterator_httpOnly->second));
    } else {
        _field_httpOnly = bool{false};
    }
    std::optional<std::optional<std::string>> _field_sameSite;
    if (auto _iterator_sameSite = _object->find("sameSite"); _iterator_sameSite != _object->end()) {
        if (!(doof::json_is_null(_iterator_sameSite->second) || (_lenient ? doof::json_is_lenient_string(_iterator_sameSite->second) : doof::json_is_string(_iterator_sameSite->second)))) { return doof::Failure<std::string>{"Field \"sameSite\" expected string or null but got " + std::string(doof::json_type_name(_iterator_sameSite->second))}; }
        _field_sameSite = (doof::json_is_null(_iterator_sameSite->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_sameSite->second) : doof::json_as_string(_iterator_sameSite->second))});
    } else {
        _field_sameSite = std::optional<std::string>{std::nullopt};
    }
    return doof::Success<std::shared_ptr<SetCookie>>{std::make_shared<SetCookie>(_field_name, _field_value, _field_domain.value(), _field_path.value(), _field_expires.value(), _field_maxAge.value(), _field_secure.value(), _field_httpOnly.value(), _field_sameSite.value())};
}

std::optional<std::string> HttpRequest::header(std::string name) {
    const auto lowerName = doof::string_toLowerCase(name);
    const auto& _iterable_1 = this->headers;
    for (const auto& entry : *_iterable_1) {
        if (doof::string_toLowerCase(entry->name) == lowerName) {
            return entry->value;
        }
    }
    return std::nullopt;
}
doof::JsonObject HttpRequest::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["method"] = doof::json_value(this->method);
    (*_json)["url"] = doof::json_value(this->url);
    (*_json)["headers"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->headers->size()); for (const auto& _element : *this->headers) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["body"] = (this->body ? [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->body->size()); for (const auto& _element : *this->body) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }() : doof::json_value(nullptr));
    (*_json)["timeoutMs"] = doof::json_value(this->timeoutMs);
    (*_json)["followRedirects"] = doof::json_value(this->followRedirects);
    return _json;
}
doof::Result<std::shared_ptr<HttpRequest>, std::string> HttpRequest::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_method = _object->find("method");
    if (_iterator_method == _object->end()) { return doof::Failure<std::string>{"Missing required field \"method\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_method->second) : doof::json_is_string(_iterator_method->second)))) { return doof::Failure<std::string>{"Field \"method\" expected string but got " + std::string(doof::json_type_name(_iterator_method->second))}; }
    auto _field_method = (_lenient ? doof::json_as_string_lenient(_iterator_method->second) : doof::json_as_string(_iterator_method->second));
    auto _iterator_url = _object->find("url");
    if (_iterator_url == _object->end()) { return doof::Failure<std::string>{"Missing required field \"url\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_url->second) : doof::json_is_string(_iterator_url->second)))) { return doof::Failure<std::string>{"Field \"url\" expected string but got " + std::string(doof::json_type_name(_iterator_url->second))}; }
    auto _field_url = (_lenient ? doof::json_as_string_lenient(_iterator_url->second) : doof::json_as_string(_iterator_url->second));
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>> _field_headers;
    if (auto _iterator_headers = _object->find("headers"); _iterator_headers != _object->end()) {
        if (!(doof::json_is_array(_iterator_headers->second))) { return doof::Failure<std::string>{"Field \"headers\" expected array but got " + std::string(doof::json_type_name(_iterator_headers->second))}; }
        _field_headers = [&]() { const auto* _array = doof::json_as_array(_iterator_headers->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::std_::http::types::HttpHeader::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_headers = std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>{std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{})};
    }
    std::optional<std::shared_ptr<std::vector<uint8_t>>> _field_body;
    if (auto _iterator_body = _object->find("body"); _iterator_body != _object->end()) {
        if (!(doof::json_is_null(_iterator_body->second) || doof::json_is_array(_iterator_body->second))) { return doof::Failure<std::string>{"Field \"body\" expected array or null but got " + std::string(doof::json_type_name(_iterator_body->second))}; }
        _field_body = (doof::json_is_null(_iterator_body->second) ? nullptr : [&]() { const auto* _array = doof::json_as_array(_iterator_body->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }());
    } else {
        _field_body = std::shared_ptr<std::vector<uint8_t>>{nullptr};
    }
    std::optional<int32_t> _field_timeoutMs;
    if (auto _iterator_timeoutMs = _object->find("timeoutMs"); _iterator_timeoutMs != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_timeoutMs->second) : doof::json_is_number(_iterator_timeoutMs->second)))) { return doof::Failure<std::string>{"Field \"timeoutMs\" expected number but got " + std::string(doof::json_type_name(_iterator_timeoutMs->second))}; }
        _field_timeoutMs = (_lenient ? doof::json_as_int_lenient(_iterator_timeoutMs->second) : doof::json_as_int(_iterator_timeoutMs->second));
    } else {
        _field_timeoutMs = int32_t{30000};
    }
    std::optional<bool> _field_followRedirects;
    if (auto _iterator_followRedirects = _object->find("followRedirects"); _iterator_followRedirects != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_followRedirects->second) : doof::json_is_boolean(_iterator_followRedirects->second)))) { return doof::Failure<std::string>{"Field \"followRedirects\" expected boolean but got " + std::string(doof::json_type_name(_iterator_followRedirects->second))}; }
        _field_followRedirects = (_lenient ? doof::json_as_bool_lenient(_iterator_followRedirects->second) : doof::json_as_bool(_iterator_followRedirects->second));
    } else {
        _field_followRedirects = bool{true};
    }
    return doof::Success<std::shared_ptr<HttpRequest>>{std::make_shared<HttpRequest>(_field_method, _field_url, _field_headers.value(), _field_body.value(), _field_timeoutMs.value(), _field_followRedirects.value())};
}

bool HttpResponse::ok() {
    return ((this->status >= 200) && (this->status < 300));
}
std::optional<std::string> HttpResponse::header(std::string name) {
    const auto lowerName = doof::string_toLowerCase(name);
    const auto& _iterable_2 = this->headers;
    for (const auto& entry : *_iterable_2) {
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
    return ::std_::json::index::parseJsonValue(this->getText());
}
doof::JsonObject HttpResponse::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["status"] = doof::json_value(this->status);
    (*_json)["statusText"] = doof::json_value(this->statusText);
    (*_json)["headers"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->headers->size()); for (const auto& _element : *this->headers) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["body"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->body->size()); for (const auto& _element : *this->body) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<HttpResponse>, std::string> HttpResponse::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_status = _object->find("status");
    if (_iterator_status == _object->end()) { return doof::Failure<std::string>{"Missing required field \"status\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_status->second) : doof::json_is_number(_iterator_status->second)))) { return doof::Failure<std::string>{"Field \"status\" expected number but got " + std::string(doof::json_type_name(_iterator_status->second))}; }
    auto _field_status = (_lenient ? doof::json_as_int_lenient(_iterator_status->second) : doof::json_as_int(_iterator_status->second));
    auto _iterator_statusText = _object->find("statusText");
    if (_iterator_statusText == _object->end()) { return doof::Failure<std::string>{"Missing required field \"statusText\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_statusText->second) : doof::json_is_string(_iterator_statusText->second)))) { return doof::Failure<std::string>{"Field \"statusText\" expected string but got " + std::string(doof::json_type_name(_iterator_statusText->second))}; }
    auto _field_statusText = (_lenient ? doof::json_as_string_lenient(_iterator_statusText->second) : doof::json_as_string(_iterator_statusText->second));
    auto _iterator_headers = _object->find("headers");
    if (_iterator_headers == _object->end()) { return doof::Failure<std::string>{"Missing required field \"headers\""}; }
    if (!(doof::json_is_array(_iterator_headers->second))) { return doof::Failure<std::string>{"Field \"headers\" expected array but got " + std::string(doof::json_type_name(_iterator_headers->second))}; }
    auto _field_headers = [&]() { const auto* _array = doof::json_as_array(_iterator_headers->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::std_::http::types::HttpHeader::fromJsonValue(_element, _lenient))); } return _values; }();
    auto _iterator_body = _object->find("body");
    if (_iterator_body == _object->end()) { return doof::Failure<std::string>{"Missing required field \"body\""}; }
    if (!(doof::json_is_array(_iterator_body->second))) { return doof::Failure<std::string>{"Field \"body\" expected array but got " + std::string(doof::json_type_name(_iterator_body->second))}; }
    auto _field_body = [&]() { const auto* _array = doof::json_as_array(_iterator_body->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    return doof::Success<std::shared_ptr<HttpResponse>>{std::make_shared<HttpResponse>(_field_status, _field_statusText, _field_headers, _field_body)};
}

std::shared_ptr<HttpClient> createClient() {
    return std::make_shared<HttpClient>(std::make_shared<::NativeHttpClient>());
}
std::shared_ptr<HttpRequest> newRequest(std::string method, std::string url) {
    return std::make_shared<HttpRequest>(method, url, std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{}), nullptr, 30000, true);
}
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> get(std::shared_ptr<HttpClient> client, std::string url) {
    return send(client, newRequest(std::string("GET"), url));
}
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> postJsonValue(std::shared_ptr<HttpClient> client, std::string url, doof::JsonValue body) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeString(::std_::json::index::formatJsonValue(body));
    const auto headers = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{std::make_shared<::std_::http::types::HttpHeader>(std::string("Content-Type"), std::string("application/json"))});
    return send(client, std::make_shared<HttpRequest>(std::string("POST"), url, headers, builder->build(), 30000, true));
}
std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> parseCookieHeader(std::string header) {
    const std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> cookies = std::make_shared<std::vector<std::shared_ptr<Cookie>>>(std::vector<std::shared_ptr<Cookie>>{});
    const auto parts = doof::string_split(header, std::string(";"));
    const auto& _iterable_3 = parts;
    for (const auto& part : *_iterable_3) {
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
    return doof::array_buildReadonly(cookies, "", 0);
}
std::string renderCookieHeader(std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> cookies) {
    auto text = std::string("");
    auto first = true;
    const auto& _iterable_4 = cookies;
    for (const auto& cookie : *_iterable_4) {
        if (cookie->name == std::string("")) {
            continue;
        }
        if (first) {
            (first = false);
        } else {
            (text += std::string("; "));
        }
        (text += std::string("") + doof::to_string(cookie->name) + std::string("=") + doof::to_string(cookie->value) + std::string(""));
    }
    return text;
}
std::shared_ptr<SetCookie> parseSetCookieHeader(std::string header) {
    const auto parts = doof::string_split(header, std::string(";"));
    if (static_cast<int32_t>((parts)->size()) == 0) {
        return nullptr;
    }
    const auto firstPart = doof::string_trim((*parts)[0]);
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
        const auto attribute = doof::string_trim((*parts)[index]);
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
std::string renderSetCookieHeader(std::shared_ptr<SetCookie> cookie) {
    auto text = std::string("") + doof::to_string(cookie->name) + std::string("=") + doof::to_string(cookie->value) + std::string("");
    const auto expires = cookie->expires;
    if (!doof::is_null(expires)) {
        (text += std::string("; Expires=") + doof::to_string(expires.value()) + std::string(""));
    }
    const auto maxAge = cookie->maxAge;
    if (!doof::is_null(maxAge)) {
        (text += std::string("; Max-Age=") + doof::to_string(maxAge.value()) + std::string(""));
    }
    const auto domain = cookie->domain;
    if (!doof::is_null(domain)) {
        (text += std::string("; Domain=") + doof::to_string(domain.value()) + std::string(""));
    }
    const auto path = cookie->path;
    if (!doof::is_null(path)) {
        (text += std::string("; Path=") + doof::to_string(path.value()) + std::string(""));
    }
    const auto sameSite = cookie->sameSite;
    if (!doof::is_null(sameSite)) {
        (text += std::string("; SameSite=") + doof::to_string(sameSite.value()) + std::string(""));
    }
    if (cookie->secure) {
        (text += std::string("; Secure"));
    }
    if (cookie->httpOnly) {
        (text += std::string("; HttpOnly"));
    }
    return text;
}
std::optional<std::string> cookieValue(std::shared_ptr<std::vector<std::shared_ptr<Cookie>>> cookies, std::string name) {
    const auto& _iterable_5 = cookies;
    for (const auto& cookie : *_iterable_5) {
        if (cookie->name == name) {
            return cookie->value;
        }
    }
    return std::nullopt;
}
doof::Result<std::shared_ptr<HttpResponse>, std::shared_ptr<::std_::http::types::HttpError>> send(std::shared_ptr<HttpClient> client, std::shared_ptr<HttpRequest> request) {
    const auto nativeResult = client->native->perform(request->method, request->url, renderHeaders(request->headers), request->body, request->timeoutMs, request->followRedirects);
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
std::string renderHeaders(std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers) {
    auto text = std::string("");
    const auto& _iterable_6 = headers;
    for (const auto& header : *_iterable_6) {
        (text += std::string("") + doof::to_string(header->name) + std::string(": ") + doof::to_string(header->value) + std::string("\r\n"));
    }
    return text;
}
std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> parseHeaders(std::string headerText) {
    const std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{});
    const auto lines = doof::string_split(headerText, std::string("\r\n"));
    const auto& _iterable_7 = lines;
    for (const auto& line : *_iterable_7) {
        if (line == std::string("")) {
            continue;
        }
        const auto separator = doof::string_indexOf(line, std::string(":"));
        if (separator <= 0) {
            continue;
        }
        headers->push_back(std::make_shared<::std_::http::types::HttpHeader>(doof::string_trim(doof::string_substring(line, 0, separator)), doof::string_trim(doof::string_slice(line, (separator + 1)))));
    }
    return doof::array_buildReadonly(headers, "", 0);
}
std::shared_ptr<::std_::http::types::HttpError> parseError(std::string raw) {
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
