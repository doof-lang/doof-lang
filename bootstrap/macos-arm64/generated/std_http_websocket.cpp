#include "std_http_websocket.hpp"
#include <cmath>
#include "std_blob_index.hpp"
#include "std_event_index.hpp"
#include "std_http_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::http::websocket {
using namespace ::std_::blob::index;
using namespace ::std_::event::index;
using namespace ::std_::http::types;

doof::JsonObject WebSocketOptions::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["eventCapacity"] = doof::json_value(this->eventCapacity);
    (*_json)["commandCapacity"] = doof::json_value(this->commandCapacity);
    (*_json)["headers"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->headers->size()); for (const auto& _element : *this->headers) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["timeoutMs"] = doof::json_value(this->timeoutMs);
    return _json;
}
doof::Result<std::shared_ptr<WebSocketOptions>, std::string> WebSocketOptions::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<int32_t> _field_eventCapacity;
    if (auto _iterator_eventCapacity = _object->find("eventCapacity"); _iterator_eventCapacity != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_eventCapacity->second) : doof::json_is_number(_iterator_eventCapacity->second)))) { return doof::Failure<std::string>{"Field \"eventCapacity\" expected number but got " + std::string(doof::json_type_name(_iterator_eventCapacity->second))}; }
        _field_eventCapacity = (_lenient ? doof::json_as_int_lenient(_iterator_eventCapacity->second) : doof::json_as_int(_iterator_eventCapacity->second));
    } else {
        _field_eventCapacity = 1024;
    }
    std::optional<int32_t> _field_commandCapacity;
    if (auto _iterator_commandCapacity = _object->find("commandCapacity"); _iterator_commandCapacity != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_commandCapacity->second) : doof::json_is_number(_iterator_commandCapacity->second)))) { return doof::Failure<std::string>{"Field \"commandCapacity\" expected number but got " + std::string(doof::json_type_name(_iterator_commandCapacity->second))}; }
        _field_commandCapacity = (_lenient ? doof::json_as_int_lenient(_iterator_commandCapacity->second) : doof::json_as_int(_iterator_commandCapacity->second));
    } else {
        _field_commandCapacity = 1024;
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>> _field_headers;
    if (auto _iterator_headers = _object->find("headers"); _iterator_headers != _object->end()) {
        if (!(doof::json_is_array(_iterator_headers->second))) { return doof::Failure<std::string>{"Field \"headers\" expected array but got " + std::string(doof::json_type_name(_iterator_headers->second))}; }
        _field_headers = [&]() { const auto* _array = doof::json_as_array(_iterator_headers->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::std_::http::types::HttpHeader::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_headers = std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{});
    }
    std::optional<int32_t> _field_timeoutMs;
    if (auto _iterator_timeoutMs = _object->find("timeoutMs"); _iterator_timeoutMs != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_timeoutMs->second) : doof::json_is_number(_iterator_timeoutMs->second)))) { return doof::Failure<std::string>{"Field \"timeoutMs\" expected number but got " + std::string(doof::json_type_name(_iterator_timeoutMs->second))}; }
        _field_timeoutMs = (_lenient ? doof::json_as_int_lenient(_iterator_timeoutMs->second) : doof::json_as_int(_iterator_timeoutMs->second));
    } else {
        _field_timeoutMs = 30000;
    }
    return doof::Success<std::shared_ptr<WebSocketOptions>>{std::make_shared<WebSocketOptions>(_field_eventCapacity.value(), _field_commandCapacity.value(), _field_headers.value(), _field_timeoutMs.value())};
}







doof::JsonObject WebSocketSendText::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["text"] = doof::json_value(this->text);
    (*_json)["coalesceKey"] = (this->coalesceKey.has_value() ? doof::json_value(this->coalesceKey.value()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<WebSocketSendText>, std::string> WebSocketSendText::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_text = _object->find("text");
    if (_iterator_text == _object->end()) { return doof::Failure<std::string>{"Missing required field \"text\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_text->second) : doof::json_is_string(_iterator_text->second)))) { return doof::Failure<std::string>{"Field \"text\" expected string but got " + std::string(doof::json_type_name(_iterator_text->second))}; }
    auto _field_text = (_lenient ? doof::json_as_string_lenient(_iterator_text->second) : doof::json_as_string(_iterator_text->second));
    std::optional<std::optional<std::string>> _field_coalesceKey;
    if (auto _iterator_coalesceKey = _object->find("coalesceKey"); _iterator_coalesceKey != _object->end()) {
        if (!(doof::json_is_null(_iterator_coalesceKey->second) || (_lenient ? doof::json_is_lenient_string(_iterator_coalesceKey->second) : doof::json_is_string(_iterator_coalesceKey->second)))) { return doof::Failure<std::string>{"Field \"coalesceKey\" expected string or null but got " + std::string(doof::json_type_name(_iterator_coalesceKey->second))}; }
        _field_coalesceKey = (doof::json_is_null(_iterator_coalesceKey->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_coalesceKey->second) : doof::json_as_string(_iterator_coalesceKey->second))});
    } else {
        _field_coalesceKey = std::optional<std::string>{std::nullopt};
    }
    return doof::Success<std::shared_ptr<WebSocketSendText>>{std::make_shared<WebSocketSendText>(_field_text, _field_coalesceKey.value())};
}

doof::JsonObject WebSocketSendBinary::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["bytes"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->bytes->size()); for (const auto& _element : *this->bytes) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    (*_json)["coalesceKey"] = (this->coalesceKey.has_value() ? doof::json_value(this->coalesceKey.value()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<WebSocketSendBinary>, std::string> WebSocketSendBinary::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_bytes = _object->find("bytes");
    if (_iterator_bytes == _object->end()) { return doof::Failure<std::string>{"Missing required field \"bytes\""}; }
    if (!(doof::json_is_array(_iterator_bytes->second))) { return doof::Failure<std::string>{"Field \"bytes\" expected array but got " + std::string(doof::json_type_name(_iterator_bytes->second))}; }
    auto _field_bytes = [&]() { const auto* _array = doof::json_as_array(_iterator_bytes->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    std::optional<std::optional<std::string>> _field_coalesceKey;
    if (auto _iterator_coalesceKey = _object->find("coalesceKey"); _iterator_coalesceKey != _object->end()) {
        if (!(doof::json_is_null(_iterator_coalesceKey->second) || (_lenient ? doof::json_is_lenient_string(_iterator_coalesceKey->second) : doof::json_is_string(_iterator_coalesceKey->second)))) { return doof::Failure<std::string>{"Field \"coalesceKey\" expected string or null but got " + std::string(doof::json_type_name(_iterator_coalesceKey->second))}; }
        _field_coalesceKey = (doof::json_is_null(_iterator_coalesceKey->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_coalesceKey->second) : doof::json_as_string(_iterator_coalesceKey->second))});
    } else {
        _field_coalesceKey = std::optional<std::string>{std::nullopt};
    }
    return doof::Success<std::shared_ptr<WebSocketSendBinary>>{std::make_shared<WebSocketSendBinary>(_field_bytes, _field_coalesceKey.value())};
}

doof::JsonObject WebSocketPing::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    return _json;
}
doof::Result<std::shared_ptr<WebSocketPing>, std::string> WebSocketPing::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    return doof::Success<std::shared_ptr<WebSocketPing>>{std::make_shared<WebSocketPing>()};
}

doof::JsonObject WebSocketCloseCommand::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["code"] = doof::json_value(this->code);
    (*_json)["reason"] = doof::json_value(this->reason);
    return _json;
}
doof::Result<std::shared_ptr<WebSocketCloseCommand>, std::string> WebSocketCloseCommand::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<int32_t> _field_code;
    if (auto _iterator_code = _object->find("code"); _iterator_code != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_code->second) : doof::json_is_number(_iterator_code->second)))) { return doof::Failure<std::string>{"Field \"code\" expected number but got " + std::string(doof::json_type_name(_iterator_code->second))}; }
        _field_code = (_lenient ? doof::json_as_int_lenient(_iterator_code->second) : doof::json_as_int(_iterator_code->second));
    } else {
        _field_code = 1000;
    }
    std::optional<std::string> _field_reason;
    if (auto _iterator_reason = _object->find("reason"); _iterator_reason != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_reason->second) : doof::json_is_string(_iterator_reason->second)))) { return doof::Failure<std::string>{"Field \"reason\" expected string but got " + std::string(doof::json_type_name(_iterator_reason->second))}; }
        _field_reason = (_lenient ? doof::json_as_string_lenient(_iterator_reason->second) : doof::json_as_string(_iterator_reason->second));
    } else {
        _field_reason = std::string("");
    }
    return doof::Success<std::shared_ptr<WebSocketCloseCommand>>{std::make_shared<WebSocketCloseCommand>(_field_code.value(), _field_reason.value())};
}

WebSocketState WebSocketConnection::state() {
    return nativeStateToPublic(this->native->state());
}
void WebSocketConnection::close() {
    const auto ignored = this->native->close(WEBSOCKET_CLOSE_NORMAL, std::string(""));
    this->commands->close();
    this->events->close();
}
doof::Result<std::shared_ptr<WebSocketConnection>, std::shared_ptr<::std_::http::types::HttpError>> connectWebSocket(std::string url, std::shared_ptr<WebSocketOptions> options) {
    if ((options->commandCapacity <= 0) || (options->eventCapacity <= 0)) {
        doof::panic(std::string("WebSocket channel capacities must be positive"));
    }
    const auto& _destructure_1 = ::std_::event::index::createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(options->eventCapacity, 0, -1, true);
    const auto eventSender = std::get<0>(_destructure_1);
    const auto events = std::get<1>(_destructure_1);
    const auto& _destructure_2 = ::std_::event::index::createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(options->commandCapacity, 0, -1, true);
    const auto commands = std::get<0>(_destructure_2);
    const auto commandReceiver = std::get<1>(_destructure_2);
    std::shared_ptr<WebSocketConnection> connection = nullptr;
    const auto nativeResult = ::NativeHttpWebSocketConnection::connect(url, renderHeaders(options->headers), options->timeoutMs, 1, options->eventCapacity);
    std::shared_ptr<::NativeHttpWebSocketConnection> native = nullptr;
    {
        auto _case_subject = nativeResult;
        if (std::holds_alternative<doof::Success<std::shared_ptr<::NativeHttpWebSocketConnection>>>(_case_subject)) {
            const auto& s = std::get<doof::Success<std::shared_ptr<::NativeHttpWebSocketConnection>>>(_case_subject);
            (native = s.value);
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
            const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
            commands->close();
            events->close();
            return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ parseWebSocketError(f.error) };
    }
    }
    const auto actualConnection = std::make_shared<WebSocketConnection>(url, events, commands, options, eventSender, commandReceiver, doof::unwrap_optional(native));
    (connection = actualConnection);
    actualConnection->native->attachChannels(actualConnection, eventSender, commandReceiver);
    emitLocalWebSocketEvent(actualConnection, doof::variant_promote<std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>>(std::make_shared<WebSocketOpen>(actualConnection)));
    actualConnection->native->start();
    return doof::Success<std::shared_ptr<WebSocketConnection>>{ actualConnection };
}
void emitLocalWebSocketEvent(std::shared_ptr<WebSocketConnection> connection, std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>> event) {
    const auto ignored = connection->eventSender->send(event, std::nullopt);
}
WebSocketState nativeStateToPublic(int32_t state) {
    return [&]() -> WebSocketState {
    auto _case_subject = state;
    if (_case_subject == 0) {
        return WebSocketState::Connecting;
    }
    if (_case_subject == 1) {
        return WebSocketState::Open;
    }
    if (_case_subject == 2) {
        return WebSocketState::Closing;
    }
    if (_case_subject == 3) {
        return WebSocketState::Closed;
    }
    if (true) {
        return WebSocketState::Error;
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
std::shared_ptr<::std_::http::types::HttpError> parseWebSocketError(std::string raw) {
    const auto firstSeparator = doof::string_indexOf(raw, std::string("|"));
    if (firstSeparator < 0) {
        return std::make_shared<::std_::http::types::HttpError>(std::string("transport"), std::string("0"), raw);
    }
    const auto remainder = doof::string_slice(raw, (firstSeparator + 1));
    const auto secondSeparator = doof::string_indexOf(remainder, std::string("|"));
    if (secondSeparator < 0) {
        return std::make_shared<::std_::http::types::HttpError>(doof::string_substring(raw, 0, firstSeparator), std::string("0"), remainder);
    }
    return std::make_shared<::std_::http::types::HttpError>(doof::string_substring(raw, 0, firstSeparator), doof::string_substring(remainder, 0, secondSeparator), doof::string_slice(remainder, (secondSeparator + 1)));
}
std::string renderHeaders(std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers) {
    auto text = std::string("");
    const auto& _iterable_3 = headers;
    for (const auto& header : *_iterable_3) {
        (text += std::string("") + doof::to_string(header->name) + std::string(": ") + doof::to_string(header->value) + std::string("\r\n"));
    }
    return text;
}
}
