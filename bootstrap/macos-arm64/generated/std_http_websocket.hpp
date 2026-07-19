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
namespace std_::http::websocket { struct WebSocketConnection; }
namespace std_::http::websocket { struct WebSocketOpen; }
namespace std_::http::websocket { struct WebSocketText; }
namespace std_::http::websocket { struct WebSocketBinary; }
namespace std_::http::websocket { struct WebSocketWritable; }
namespace std_::http::websocket { struct WebSocketClose; }
namespace std_::http::websocket { struct WebSocketError; }
namespace std_::http::websocket { struct WebSocketSendText; }
namespace std_::http::websocket { struct WebSocketSendBinary; }
namespace std_::http::websocket { struct WebSocketPing; }
namespace std_::http::websocket { struct WebSocketCloseCommand; }
namespace std_::blob::index { struct BlobBuilder; }
namespace std_::http::types { struct HttpError; }
namespace std_::http::types { struct HttpHeader; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::http::websocket {
    struct WebSocketOptions;
    struct WebSocketOpen;
    struct WebSocketText;
    struct WebSocketBinary;
    struct WebSocketWritable;
    struct WebSocketClose;
    struct WebSocketError;
    struct WebSocketSendText;
    struct WebSocketSendBinary;
    struct WebSocketPing;
    struct WebSocketCloseCommand;
    struct WebSocketConnection;
}

#include "std_blob_index.hpp"
#include "std_event_index.hpp"
#include "std_http_types.hpp"

using WebSocketConnection = ::std_::http::websocket::WebSocketConnection;
using WebSocketOpen = ::std_::http::websocket::WebSocketOpen;
using WebSocketText = ::std_::http::websocket::WebSocketText;
using WebSocketBinary = ::std_::http::websocket::WebSocketBinary;
using WebSocketWritable = ::std_::http::websocket::WebSocketWritable;
using WebSocketClose = ::std_::http::websocket::WebSocketClose;
using WebSocketError = ::std_::http::websocket::WebSocketError;
using WebSocketSendText = ::std_::http::websocket::WebSocketSendText;
using WebSocketSendBinary = ::std_::http::websocket::WebSocketSendBinary;
using WebSocketPing = ::std_::http::websocket::WebSocketPing;
using WebSocketCloseCommand = ::std_::http::websocket::WebSocketCloseCommand;
#include "std/http/native_http_client.hpp"

namespace std_::http::websocket {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    enum class WebSocketState {
    Connecting,
    Open,
    Closing,
    Closed,
    Error
};
inline const char* WebSocketState_name(WebSocketState value) {
  switch (value) {
    case WebSocketState::Connecting: return "Connecting";
    case WebSocketState::Open: return "Open";
    case WebSocketState::Closing: return "Closing";
    case WebSocketState::Closed: return "Closed";
    case WebSocketState::Error: return "Error";
  }
  return "";
}
inline std::optional<WebSocketState> WebSocketState_fromName(std::string_view value) {
  if (value == "Connecting") return WebSocketState::Connecting;
  if (value == "Open") return WebSocketState::Open;
  if (value == "Closing") return WebSocketState::Closing;
  if (value == "Closed") return WebSocketState::Closed;
  if (value == "Error") return WebSocketState::Error;
  return std::nullopt;
}
inline std::optional<WebSocketState> WebSocketState_fromValue(int32_t value) {
  switch (static_cast<WebSocketState>(value)) {
    case WebSocketState::Connecting: return WebSocketState::Connecting;
    case WebSocketState::Open: return WebSocketState::Open;
    case WebSocketState::Closing: return WebSocketState::Closing;
    case WebSocketState::Closed: return WebSocketState::Closed;
    case WebSocketState::Error: return WebSocketState::Error;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, WebSocketState value) { return output << WebSocketState_name(value); }
    struct WebSocketOptions : public std::enable_shared_from_this<WebSocketOptions> {
    int32_t eventCapacity = 1024;
    int32_t commandCapacity = 1024;
    std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers;
    int32_t timeoutMs = 30000;
    WebSocketOptions(int32_t eventCapacity, int32_t commandCapacity, std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers, int32_t timeoutMs) : eventCapacity(eventCapacity), commandCapacity(commandCapacity), headers(headers), timeoutMs(timeoutMs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<WebSocketOptions>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct WebSocketOpen : public std::enable_shared_from_this<WebSocketOpen> {
    std::shared_ptr<WebSocketConnection> connection;
    WebSocketOpen(std::shared_ptr<WebSocketConnection> connection) : connection(connection) {}
};
    struct WebSocketText : public std::enable_shared_from_this<WebSocketText> {
    std::shared_ptr<WebSocketConnection> connection;
    std::string text;
    WebSocketText(std::shared_ptr<WebSocketConnection> connection, std::string text) : connection(connection), text(text) {}
};
    struct WebSocketBinary : public std::enable_shared_from_this<WebSocketBinary> {
    std::shared_ptr<WebSocketConnection> connection;
    std::shared_ptr<std::vector<uint8_t>> bytes;
    WebSocketBinary(std::shared_ptr<WebSocketConnection> connection, std::shared_ptr<std::vector<uint8_t>> bytes) : connection(connection), bytes(bytes) {}
};
    struct WebSocketWritable : public std::enable_shared_from_this<WebSocketWritable> {
    std::shared_ptr<WebSocketConnection> connection;
    WebSocketWritable(std::shared_ptr<WebSocketConnection> connection) : connection(connection) {}
};
    struct WebSocketClose : public std::enable_shared_from_this<WebSocketClose> {
    std::shared_ptr<WebSocketConnection> connection;
    int32_t code;
    std::string reason;
    bool wasClean;
    WebSocketClose(std::shared_ptr<WebSocketConnection> connection, int32_t code, std::string reason, bool wasClean) : connection(connection), code(code), reason(reason), wasClean(wasClean) {}
};
    struct WebSocketError : public std::enable_shared_from_this<WebSocketError> {
    std::shared_ptr<WebSocketConnection> connection;
    std::shared_ptr<::std_::http::types::HttpError> error;
    WebSocketError(std::shared_ptr<WebSocketConnection> connection, std::shared_ptr<::std_::http::types::HttpError> error) : connection(connection), error(error) {}
};
    struct WebSocketSendText : public std::enable_shared_from_this<WebSocketSendText> {
    std::string text;
    std::optional<std::string> coalesceKey = std::nullopt;
    WebSocketSendText(std::string text, std::optional<std::string> coalesceKey = std::nullopt) : text(text), coalesceKey(coalesceKey) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<WebSocketSendText>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct WebSocketSendBinary : public std::enable_shared_from_this<WebSocketSendBinary> {
    std::shared_ptr<std::vector<uint8_t>> bytes;
    std::optional<std::string> coalesceKey = std::nullopt;
    WebSocketSendBinary(std::shared_ptr<std::vector<uint8_t>> bytes, std::optional<std::string> coalesceKey = std::nullopt) : bytes(bytes), coalesceKey(coalesceKey) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<WebSocketSendBinary>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct WebSocketPing : public std::enable_shared_from_this<WebSocketPing> {
    WebSocketPing() {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<WebSocketPing>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct WebSocketCloseCommand : public std::enable_shared_from_this<WebSocketCloseCommand> {
    int32_t code = 1000;
    std::string reason = std::string("");
    WebSocketCloseCommand(int32_t code = 1000, std::string reason = std::string("")) : code(code), reason(reason) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<WebSocketCloseCommand>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct WebSocketConnection : public std::enable_shared_from_this<WebSocketConnection> {
    std::string url;
    std::shared_ptr<::std_::event::index::ChannelReceiver<std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>>> events;
    std::shared_ptr<::std_::event::index::ChannelSender<std::variant<std::shared_ptr<WebSocketSendText>, std::shared_ptr<WebSocketSendBinary>, std::shared_ptr<WebSocketPing>, std::shared_ptr<WebSocketCloseCommand>>>> commands;
    std::shared_ptr<WebSocketOptions> options;
    std::shared_ptr<::std_::event::index::ChannelSender<std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>>> eventSender;
    std::shared_ptr<::std_::event::index::ChannelReceiver<std::variant<std::shared_ptr<WebSocketSendText>, std::shared_ptr<WebSocketSendBinary>, std::shared_ptr<WebSocketPing>, std::shared_ptr<WebSocketCloseCommand>>>> commandReceiver;
    std::shared_ptr<::NativeHttpWebSocketConnection> native;
    WebSocketConnection(std::string url, std::shared_ptr<::std_::event::index::ChannelReceiver<std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>>> events, std::shared_ptr<::std_::event::index::ChannelSender<std::variant<std::shared_ptr<WebSocketSendText>, std::shared_ptr<WebSocketSendBinary>, std::shared_ptr<WebSocketPing>, std::shared_ptr<WebSocketCloseCommand>>>> commands, std::shared_ptr<WebSocketOptions> options, std::shared_ptr<::std_::event::index::ChannelSender<std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>>> eventSender, std::shared_ptr<::std_::event::index::ChannelReceiver<std::variant<std::shared_ptr<WebSocketSendText>, std::shared_ptr<WebSocketSendBinary>, std::shared_ptr<WebSocketPing>, std::shared_ptr<WebSocketCloseCommand>>>> commandReceiver, std::shared_ptr<::NativeHttpWebSocketConnection> native) : url(url), events(events), commands(commands), options(options), eventSender(eventSender), commandReceiver(commandReceiver), native(native) {}
    WebSocketState state();
    void close();
};
    using WebSocketEvent = std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>;
    using WebSocketCommand = std::variant<std::shared_ptr<WebSocketSendText>, std::shared_ptr<WebSocketSendBinary>, std::shared_ptr<WebSocketPing>, std::shared_ptr<WebSocketCloseCommand>>;
    doof::Result<std::shared_ptr<WebSocketConnection>, std::shared_ptr<::std_::http::types::HttpError>> connectWebSocket(std::string url, std::shared_ptr<WebSocketOptions> options = std::make_shared<WebSocketOptions>(1024, 1024, std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{}), 30000));
    void emitLocalWebSocketEvent(std::shared_ptr<WebSocketConnection> connection, std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>> event);
    WebSocketState nativeStateToPublic(int32_t state);
    std::shared_ptr<::std_::http::types::HttpError> parseWebSocketError(std::string raw);
    std::string renderHeaders(std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers);
}

namespace std_::http::websocket {
    inline const auto WEBSOCKET_CLOSE_NORMAL = 1000;
    inline const auto WEBSOCKET_CLOSE_GOING_AWAY = 1001;
    inline const auto WEBSOCKET_CLOSE_PROTOCOL_ERROR = 1002;
    inline const auto WEBSOCKET_CLOSE_UNSUPPORTED_DATA = 1003;
    inline const auto WEBSOCKET_CLOSE_INVALID_PAYLOAD = 1007;
    inline const auto WEBSOCKET_CLOSE_POLICY_VIOLATION = 1008;
    inline const auto WEBSOCKET_CLOSE_MESSAGE_TOO_BIG = 1009;
    inline const auto WEBSOCKET_CLOSE_INTERNAL_ERROR = 1011;
}
