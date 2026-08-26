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












#line 125 "/std/http/websocket.do"
WebSocketState WebSocketConnection::state() {
#line 126 "/std/http/websocket.do"
    return nativeStateToPublic(this->native->state());
}
#line 129 "/std/http/websocket.do"
void WebSocketConnection::close() {
#line 130 "/std/http/websocket.do"
    const auto ignored = this->native->close(WEBSOCKET_CLOSE_NORMAL, std::string(""));
#line 131 "/std/http/websocket.do"
    this->commands->close();
#line 132 "/std/http/websocket.do"
    this->events->close();
}
#line 136 "/std/http/websocket.do"
doof::Result<std::shared_ptr<WebSocketConnection>, std::shared_ptr<::std_::http::types::HttpError>> connectWebSocket(const std::string& url, const std::shared_ptr<WebSocketOptions>& options) {
#line 140 "/std/http/websocket.do"
    if ((options->commandCapacity <= 0) || (options->eventCapacity <= 0)) {
#line 141 "/std/http/websocket.do"
        doof::panic(std::string("WebSocket channel capacities must be positive"));
    }
#line 144 "/std/http/websocket.do"
    auto _binding_value_1 = ::std_::http::transport_url::prepareTransportUrl(url);
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
#line 145 "/std/http/websocket.do"
        return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ error };
    }
    const auto transportUrl = doof::success_value(_binding_value_1);
#line 148 "/std/http/websocket.do"
    const auto& _destructure_2 = ::std_::event::index::createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(options->eventCapacity, 0, -1, true);
    const auto eventSender = std::get<0>(_destructure_2);
    const auto events = std::get<1>(_destructure_2);
#line 152 "/std/http/websocket.do"
    const auto& _destructure_3 = ::std_::event::index::createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(options->commandCapacity, 0, -1, true);
    const auto commands = std::get<0>(_destructure_3);
    const auto commandReceiver = std::get<1>(_destructure_3);
#line 157 "/std/http/websocket.do"
    std::shared_ptr<WebSocketConnection> connection = nullptr;
#line 158 "/std/http/websocket.do"
    const auto nativeResult = ::NativeHttpWebSocketConnection::connect(transportUrl, renderHeaders(options->headers), options->timeoutMs, 1, options->eventCapacity);
#line 166 "/std/http/websocket.do"
    std::shared_ptr<::NativeHttpWebSocketConnection> native = nullptr;
#line 167 "/std/http/websocket.do"
    {
        auto _case_subject = nativeResult;
        if (std::holds_alternative<doof::Success<std::shared_ptr<::NativeHttpWebSocketConnection>>>(_case_subject)) {
            const auto& s = std::get<doof::Success<std::shared_ptr<::NativeHttpWebSocketConnection>>>(_case_subject);
#line 169 "/std/http/websocket.do"
            (native = s.value);
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
            const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
#line 172 "/std/http/websocket.do"
            commands->close();
#line 173 "/std/http/websocket.do"
            events->close();
#line 174 "/std/http/websocket.do"
            return doof::Failure<std::shared_ptr<::std_::http::types::HttpError>>{ parseWebSocketError(f.error) };
    }
    }
#line 178 "/std/http/websocket.do"
    const auto actualConnection = std::make_shared<WebSocketConnection>(url, events, commands, options, eventSender, commandReceiver, doof::unwrap_optional(native));
#line 187 "/std/http/websocket.do"
    (connection = actualConnection);
#line 189 "/std/http/websocket.do"
    actualConnection->native->attachChannels(actualConnection, eventSender, commandReceiver);
#line 191 "/std/http/websocket.do"
    emitLocalWebSocketEvent(actualConnection, doof::variant_promote<std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>>(std::make_shared<WebSocketOpen>(actualConnection)));
#line 194 "/std/http/websocket.do"
    actualConnection->native->start();
#line 196 "/std/http/websocket.do"
    return doof::Success<std::shared_ptr<WebSocketConnection>>{ actualConnection };
}
#line 199 "/std/http/websocket.do"
void emitLocalWebSocketEvent(const std::shared_ptr<WebSocketConnection>& connection, const std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>& event) {
#line 203 "/std/http/websocket.do"
    const auto ignored = connection->eventSender->send(event, std::nullopt);
}
#line 206 "/std/http/websocket.do"
WebSocketState nativeStateToPublic(int32_t state) {
#line 207 "/std/http/websocket.do"
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
#line 216 "/std/http/websocket.do"
std::shared_ptr<::std_::http::types::HttpError> parseWebSocketError(const std::string& raw) {
#line 217 "/std/http/websocket.do"
    const auto firstSeparator = doof::string_indexOf(raw, std::string("|"));
#line 218 "/std/http/websocket.do"
    if (firstSeparator < 0) {
#line 219 "/std/http/websocket.do"
        return std::make_shared<::std_::http::types::HttpError>(std::string("transport"), std::string("0"), raw);
    }
#line 226 "/std/http/websocket.do"
    const auto remainder = doof::string_slice(raw, (firstSeparator + 1));
#line 227 "/std/http/websocket.do"
    const auto secondSeparator = doof::string_indexOf(remainder, std::string("|"));
#line 228 "/std/http/websocket.do"
    if (secondSeparator < 0) {
#line 229 "/std/http/websocket.do"
        return std::make_shared<::std_::http::types::HttpError>(doof::string_substring(raw, 0, firstSeparator), std::string("0"), remainder);
    }
#line 236 "/std/http/websocket.do"
    return std::make_shared<::std_::http::types::HttpError>(doof::string_substring(raw, 0, firstSeparator), doof::string_substring(remainder, 0, secondSeparator), doof::string_slice(remainder, (secondSeparator + 1)));
}
#line 243 "/std/http/websocket.do"
std::string renderHeaders(const std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>& headers) {
#line 244 "/std/http/websocket.do"
    auto text = std::string("");
#line 245 "/std/http/websocket.do"
    const auto& _iterable_5 = headers;
    for (const auto& header : *_iterable_5) {
#line 246 "/std/http/websocket.do"
        (text += ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(header->name); _interpolation += ": "; _interpolation += doof::to_string(header->value); _interpolation += "\r\n"; return _interpolation; }()));
    }
#line 248 "/std/http/websocket.do"
    return text;
}
#line 1 "<doof-generated>"
}
