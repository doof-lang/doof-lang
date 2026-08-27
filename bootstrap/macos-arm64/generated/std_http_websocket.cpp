#include "std_http_websocket.hpp"

namespace std_::http::websocket {
using namespace ::std_::blob::index;
using namespace ::std_::event::index;
using namespace ::std_::http::types;
using namespace ::std_::http::transport_url;
int32_t WEBSOCKET_CLOSE_NORMAL = 1000;
int32_t WEBSOCKET_CLOSE_GOING_AWAY = 1001;
int32_t WEBSOCKET_CLOSE_PROTOCOL_ERROR = 1002;
int32_t WEBSOCKET_CLOSE_UNSUPPORTED_DATA = 1003;
int32_t WEBSOCKET_CLOSE_INVALID_PAYLOAD = 1007;
int32_t WEBSOCKET_CLOSE_POLICY_VIOLATION = 1008;
int32_t WEBSOCKET_CLOSE_MESSAGE_TOO_BIG = 1009;
int32_t WEBSOCKET_CLOSE_INTERNAL_ERROR = 1011;












WebSocketState WebSocketConnection::state() {
    return nativeStateToPublic(this->native->state());
}
void WebSocketConnection::close() {
    const auto ignored = this->native->close(WEBSOCKET_CLOSE_NORMAL, std::string(""));
    this->commands->close();
    this->events->close();
}
doof::Result<std::shared_ptr<WebSocketConnection>, std::shared_ptr<::std_::http::types::HttpError>> connectWebSocket(const std::string& url, const std::shared_ptr<WebSocketOptions>& options) {
    if ((options->commandCapacity <= 0) || (options->eventCapacity <= 0)) {
        doof::panic(std::string("WebSocket channel capacities must be positive"));
    }
    auto _binding_value_1 = ::std_::http::transport_url::prepareTransportUrl(url);
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ error };
    }
    const auto transportUrl = doof::success_value(_binding_value_1);
    const auto& _destructure_2 = ::std_::event::index::createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(options->eventCapacity, 0, -1, true);
    const auto eventSender = std::get<0>(_destructure_2);
    const auto events = std::get<1>(_destructure_2);
    const auto& _destructure_3 = ::std_::event::index::createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(options->commandCapacity, 0, -1, true);
    const auto commands = std::get<0>(_destructure_3);
    const auto commandReceiver = std::get<1>(_destructure_3);
    std::shared_ptr<WebSocketConnection> connection = nullptr;
    const auto nativeResult = ::NativeHttpWebSocketConnection::connect(transportUrl, renderHeaders(options->headers), options->timeoutMs, 1, options->eventCapacity);
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
void emitLocalWebSocketEvent(const std::shared_ptr<WebSocketConnection>& connection, const std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>& event) {
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
std::shared_ptr<::std_::http::types::HttpError> parseWebSocketError(const std::string& raw) {
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
std::string renderHeaders(const std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>& headers) {
    auto text = std::string("");
    const auto& _iterable_5 = headers;
    for (const auto& header : *_iterable_5) {
        (text += ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(header->name); _interpolation += ": "; _interpolation += doof::to_string(header->value); _interpolation += "\r\n"; return _interpolation; }()));
    }
    return text;
}
}
