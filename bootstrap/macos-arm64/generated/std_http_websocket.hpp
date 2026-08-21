#pragma once
#include "doof_runtime.hpp"
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }
namespace std_::event::index { enum class Backpressure; }
namespace std_::event::index { enum class SendError; }
namespace std_::event::index { struct Timer; }
namespace std_::time::duration { struct Duration; }
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
namespace std_::http::websocket { enum class WebSocketState; }
namespace std_::http::websocket { struct WebSocketOptions; }
namespace std_::http::types { struct HttpError; }
namespace std_::http::types { struct HttpHeader; }

namespace std_::blob::index {
}

namespace std_::time::duration {
    struct Duration;
}

namespace std_::http::types {
    struct HttpHeader;
    struct HttpError;
}

namespace std_::event::index {
    struct Timer;
}

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
    extern int32_t WEBSOCKET_CLOSE_NORMAL;
    extern int32_t WEBSOCKET_CLOSE_GOING_AWAY;
    extern int32_t WEBSOCKET_CLOSE_PROTOCOL_ERROR;
    extern int32_t WEBSOCKET_CLOSE_UNSUPPORTED_DATA;
    extern int32_t WEBSOCKET_CLOSE_INVALID_PAYLOAD;
    extern int32_t WEBSOCKET_CLOSE_POLICY_VIOLATION;
    extern int32_t WEBSOCKET_CLOSE_MESSAGE_TOO_BIG;
    extern int32_t WEBSOCKET_CLOSE_INTERNAL_ERROR;
}

namespace std_::event::index {
    using __type1 = std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>;
    using __type2 = std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>;
}

namespace std_::blob::types {
    enum class Endian {
    BigEndian = 0,
    LittleEndian = 1
};
inline const char* Endian_name(Endian value) {
  switch (value) {
    case Endian::BigEndian: return "BigEndian";
    case Endian::LittleEndian: return "LittleEndian";
  }
  return "";
}
inline std::optional<Endian> Endian_fromName(std::string_view value) {
  if (value == "BigEndian") return Endian::BigEndian;
  if (value == "LittleEndian") return Endian::LittleEndian;
  return std::nullopt;
}
inline std::optional<Endian> Endian_fromValue(int32_t value) {
  switch (static_cast<Endian>(value)) {
    case Endian::BigEndian: return Endian::BigEndian;
    case Endian::LittleEndian: return Endian::LittleEndian;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, Endian value) { return output << Endian_name(value); }
    enum class TextEncoding {
    Utf8 = 0,
    Utf16LE = 1,
    Utf16BE = 2,
    Latin1 = 3,
    Windows1252 = 4,
    CP437 = 5,
    Ascii = 6
};
inline const char* TextEncoding_name(TextEncoding value) {
  switch (value) {
    case TextEncoding::Utf8: return "Utf8";
    case TextEncoding::Utf16LE: return "Utf16LE";
    case TextEncoding::Utf16BE: return "Utf16BE";
    case TextEncoding::Latin1: return "Latin1";
    case TextEncoding::Windows1252: return "Windows1252";
    case TextEncoding::CP437: return "CP437";
    case TextEncoding::Ascii: return "Ascii";
  }
  return "";
}
inline std::optional<TextEncoding> TextEncoding_fromName(std::string_view value) {
  if (value == "Utf8") return TextEncoding::Utf8;
  if (value == "Utf16LE") return TextEncoding::Utf16LE;
  if (value == "Utf16BE") return TextEncoding::Utf16BE;
  if (value == "Latin1") return TextEncoding::Latin1;
  if (value == "Windows1252") return TextEncoding::Windows1252;
  if (value == "CP437") return TextEncoding::CP437;
  if (value == "Ascii") return TextEncoding::Ascii;
  return std::nullopt;
}
inline std::optional<TextEncoding> TextEncoding_fromValue(int32_t value) {
  switch (static_cast<TextEncoding>(value)) {
    case TextEncoding::Utf8: return TextEncoding::Utf8;
    case TextEncoding::Utf16LE: return TextEncoding::Utf16LE;
    case TextEncoding::Utf16BE: return TextEncoding::Utf16BE;
    case TextEncoding::Latin1: return TextEncoding::Latin1;
    case TextEncoding::Windows1252: return TextEncoding::Windows1252;
    case TextEncoding::CP437: return TextEncoding::CP437;
    case TextEncoding::Ascii: return TextEncoding::Ascii;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, TextEncoding value) { return output << TextEncoding_name(value); }
    enum class EncodingError {
    InvalidData = 0,
    UnrepresentableCharacter = 1,
    OutputTooLarge = 2
};
inline const char* EncodingError_name(EncodingError value) {
  switch (value) {
    case EncodingError::InvalidData: return "InvalidData";
    case EncodingError::UnrepresentableCharacter: return "UnrepresentableCharacter";
    case EncodingError::OutputTooLarge: return "OutputTooLarge";
  }
  return "";
}
inline std::optional<EncodingError> EncodingError_fromName(std::string_view value) {
  if (value == "InvalidData") return EncodingError::InvalidData;
  if (value == "UnrepresentableCharacter") return EncodingError::UnrepresentableCharacter;
  if (value == "OutputTooLarge") return EncodingError::OutputTooLarge;
  return std::nullopt;
}
inline std::optional<EncodingError> EncodingError_fromValue(int32_t value) {
  switch (static_cast<EncodingError>(value)) {
    case EncodingError::InvalidData: return EncodingError::InvalidData;
    case EncodingError::UnrepresentableCharacter: return EncodingError::UnrepresentableCharacter;
    case EncodingError::OutputTooLarge: return EncodingError::OutputTooLarge;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, EncodingError value) { return output << EncodingError_name(value); }
}

namespace std_::event::index {
    enum class Backpressure {
    None,
    High
};
inline const char* Backpressure_name(Backpressure value) {
  switch (value) {
    case Backpressure::None: return "None";
    case Backpressure::High: return "High";
  }
  return "";
}
inline std::optional<Backpressure> Backpressure_fromName(std::string_view value) {
  if (value == "None") return Backpressure::None;
  if (value == "High") return Backpressure::High;
  return std::nullopt;
}
inline std::optional<Backpressure> Backpressure_fromValue(int32_t value) {
  switch (static_cast<Backpressure>(value)) {
    case Backpressure::None: return Backpressure::None;
    case Backpressure::High: return Backpressure::High;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, Backpressure value) { return output << Backpressure_name(value); }
    enum class SendError {
    Full,
    Closed
};
inline const char* SendError_name(SendError value) {
  switch (value) {
    case SendError::Full: return "Full";
    case SendError::Closed: return "Closed";
  }
  return "";
}
inline std::optional<SendError> SendError_fromName(std::string_view value) {
  if (value == "Full") return SendError::Full;
  if (value == "Closed") return SendError::Closed;
  return std::nullopt;
}
inline std::optional<SendError> SendError_fromValue(int32_t value) {
  switch (static_cast<SendError>(value)) {
    case SendError::Full: return SendError::Full;
    case SendError::Closed: return SendError::Closed;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, SendError value) { return output << SendError_name(value); }
}

namespace std_::http::websocket {
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
}

namespace std_::http::websocket {
    using WebSocketEvent = std::variant<std::shared_ptr<WebSocketOpen>, std::shared_ptr<WebSocketText>, std::shared_ptr<WebSocketBinary>, std::shared_ptr<WebSocketWritable>, std::shared_ptr<WebSocketClose>, std::shared_ptr<WebSocketError>>;
    using WebSocketCommand = std::variant<std::shared_ptr<WebSocketSendText>, std::shared_ptr<WebSocketSendBinary>, std::shared_ptr<WebSocketPing>, std::shared_ptr<WebSocketCloseCommand>>;
}

namespace std_::time::duration {
    // A signed elapsed duration with nanosecond precision.
struct Duration : public std::enable_shared_from_this<Duration> {
    int64_t nanos;
    static std::shared_ptr<Duration> ZERO;
    Duration(int64_t nanos) : nanos(nanos) {}
    static std::shared_ptr<Duration> ofNanos(int64_t n);
    static std::shared_ptr<Duration> ofMicros(int64_t us);
    static std::shared_ptr<Duration> ofMillis(int64_t ms);
    static std::shared_ptr<Duration> ofSeconds(int64_t s);
    static std::shared_ptr<Duration> ofMinutes(int64_t m);
    static std::shared_ptr<Duration> ofHours(int64_t h);
    static std::shared_ptr<Duration> ofDays(int64_t d);
    static doof::Result<std::shared_ptr<Duration>, std::string> parse(const std::string& s);
    int64_t toNanos();
    int64_t toMicros();
    int64_t toMillis();
    double toSeconds();
    double toMinutes();
    double toHours();
    double toDays();
    bool isNegative();
    bool isZero();
    std::shared_ptr<Duration> abs();
    std::shared_ptr<Duration> negated();
    std::shared_ptr<Duration> plus(const std::shared_ptr<Duration>& other);
    std::shared_ptr<Duration> minus(const std::shared_ptr<Duration>& other);
    std::shared_ptr<Duration> multipliedBy(int64_t factor);
    std::shared_ptr<Duration> dividedBy(int64_t divisor);
    int32_t compareTo(const std::shared_ptr<Duration>& other);
    bool isLessThan(const std::shared_ptr<Duration>& other);
    bool isGreaterThan(const std::shared_ptr<Duration>& other);
    bool equals(const std::shared_ptr<Duration>& other);
    std::string toISOString();
};
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

namespace std_::http::websocket {
    struct WebSocketOptions : public std::enable_shared_from_this<WebSocketOptions> {
    int32_t eventCapacity = 1024;
    int32_t commandCapacity = 1024;
    std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers;
    int32_t timeoutMs = 30000;
    WebSocketOptions(int32_t eventCapacity, int32_t commandCapacity, std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>> headers, int32_t timeoutMs) : eventCapacity(eventCapacity), commandCapacity(commandCapacity), headers(headers), timeoutMs(timeoutMs) {}
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
};
    struct WebSocketSendBinary : public std::enable_shared_from_this<WebSocketSendBinary> {
    std::shared_ptr<std::vector<uint8_t>> bytes;
    std::optional<std::string> coalesceKey = std::nullopt;
    WebSocketSendBinary(std::shared_ptr<std::vector<uint8_t>> bytes, std::optional<std::string> coalesceKey = std::nullopt) : bytes(bytes), coalesceKey(coalesceKey) {}
};
    struct WebSocketPing : public std::enable_shared_from_this<WebSocketPing> {
    WebSocketPing() {}
};
    struct WebSocketCloseCommand : public std::enable_shared_from_this<WebSocketCloseCommand> {
    int32_t code = 1000;
    std::string reason = std::string("");
    WebSocketCloseCommand(int32_t code = 1000, std::string reason = std::string("")) : code(code), reason(reason) {}
};
}

namespace doof_blob { using Endian = ::std_::blob::types::Endian; }
namespace doof_blob { using TextEncoding = ::std_::blob::types::TextEncoding; }
namespace doof_blob { using EncodingError = ::std_::blob::types::EncodingError; }
#include "native_blob.hpp"

namespace std_::http::transport_url {
    doof::Result<std::string, std::shared_ptr<::std_::http::types::HttpError>> prepareTransportUrl(const std::string& url);
}

namespace doof_event { using Backpressure = ::std_::event::index::Backpressure; }
namespace doof_event { using SendError = ::std_::event::index::SendError; }
namespace doof_event { using Timer = ::std_::event::index::Timer; }
namespace doof_event { using Duration = ::std_::time::duration::Duration; }
#include "native_event.hpp"

namespace std_::event::index {
    void _runMainEventLoop();
    int32_t _drainMainEventLoop();
    void _setMainEventWakeHandler(const doof::callback<void()>& handler);
    void _clearMainEventWakeHandler();
    template <typename T>
struct ChannelSender : public std::enable_shared_from_this<ChannelSender<T>> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelSender(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
    doof::Result<Backpressure, SendError> send(T value, const std::optional<std::string>& key = std::nullopt) {
        const auto code = (doof::is_null(key) ? ::doof_event::trySendChannelMessage<T>(this->native, value, false, std::string("")) : ::doof_event::trySendChannelMessage<T>(this->native, value, true, key.value()));
        return [&]() -> doof::Result<Backpressure, SendError> {
    auto _case_subject = code;
    if (_case_subject == 0) {
        return doof::Success<Backpressure>{ Backpressure::None };
    }
    if (_case_subject == 1) {
        return doof::Success<Backpressure>{ Backpressure::High };
    }
    if (_case_subject == 2) {
        return doof::Failure<SendError>{ SendError::Full };
    }
    if (true) {
        return doof::Failure<SendError>{ SendError::Closed };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
    }
    void onReady(const doof::callback<void()>& handler) {
        this->native->registerSenderReady(handler);
    }
    void onClosed(const doof::callback<void()>& handler) {
        this->native->registerSenderClosed(handler);
    }
    void close() {
        this->native->tryClose();
    }
};
    template <typename T>
struct ChannelReceiver : public std::enable_shared_from_this<ChannelReceiver<T>> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelReceiver(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
    void onMessage(const doof::callback<void(T)>& handler) {
        ::doof_event::registerChannelReceiverMessage<T>(this->native, handler);
    }
    void onClosed(const doof::callback<void()>& handler) {
        this->native->registerReceiverClosed(handler);
    }
    void close() {
        this->native->tryClose();
    }
};
    struct Timer : public std::enable_shared_from_this<Timer> {
    std::shared_ptr<::doof_event::NativeTimer> native;
    Timer(std::shared_ptr<::doof_event::NativeTimer> native) : native(native) {}
    bool cancel();
};
    std::tuple<std::shared_ptr<ChannelSender<__type1>>, std::shared_ptr<ChannelReceiver<__type1>>> createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(int32_t capacity = 256, int32_t highWater = 0, int32_t lowWater = -1, bool keepsAlive = true);
    std::tuple<std::shared_ptr<ChannelSender<__type2>>, std::shared_ptr<ChannelReceiver<__type2>>> createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(int32_t capacity = 256, int32_t highWater = 0, int32_t lowWater = -1, bool keepsAlive = true);
}

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
using WebSocketState = ::std_::http::websocket::WebSocketState;
using WebSocketOptions = ::std_::http::websocket::WebSocketOptions;
using WebSocketEvent = ::std_::http::websocket::WebSocketEvent;
using WebSocketCommand = ::std_::http::websocket::WebSocketCommand;
using HttpError = ::std_::http::types::HttpError;
using HttpHeader = ::std_::http::types::HttpHeader;
#include "std/http/native_http_client.hpp"

namespace std_::http::websocket {
    struct WebSocketConnection : public std::enable_shared_from_this<WebSocketConnection> {
    std::string url;
    std::shared_ptr<::std_::event::index::ChannelReceiver<WebSocketEvent>> events;
    std::shared_ptr<::std_::event::index::ChannelSender<WebSocketCommand>> commands;
    std::shared_ptr<WebSocketOptions> options;
    std::shared_ptr<::std_::event::index::ChannelSender<WebSocketEvent>> eventSender;
    std::shared_ptr<::std_::event::index::ChannelReceiver<WebSocketCommand>> commandReceiver;
    std::shared_ptr<::NativeHttpWebSocketConnection> native;
    WebSocketConnection(std::string url, std::shared_ptr<::std_::event::index::ChannelReceiver<WebSocketEvent>> events, std::shared_ptr<::std_::event::index::ChannelSender<WebSocketCommand>> commands, std::shared_ptr<WebSocketOptions> options, std::shared_ptr<::std_::event::index::ChannelSender<WebSocketEvent>> eventSender, std::shared_ptr<::std_::event::index::ChannelReceiver<WebSocketCommand>> commandReceiver, std::shared_ptr<::NativeHttpWebSocketConnection> native) : url(url), events(events), commands(commands), options(options), eventSender(eventSender), commandReceiver(commandReceiver), native(native) {}
    WebSocketState state();
    void close();
};
    doof::Result<std::shared_ptr<WebSocketConnection>, std::shared_ptr<::std_::http::types::HttpError>> connectWebSocket(const std::string& url, const std::shared_ptr<WebSocketOptions>& options = std::make_shared<WebSocketOptions>(1024, 1024, std::make_shared<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>(std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>{}), 30000));
    void emitLocalWebSocketEvent(const std::shared_ptr<WebSocketConnection>& connection, const WebSocketEvent& event);
    WebSocketState nativeStateToPublic(int32_t state);
    std::shared_ptr<::std_::http::types::HttpError> parseWebSocketError(const std::string& raw);
    std::string renderHeaders(const std::shared_ptr<std::vector<std::shared_ptr<::std_::http::types::HttpHeader>>>& headers);
}
