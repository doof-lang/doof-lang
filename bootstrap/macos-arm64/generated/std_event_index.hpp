#pragma once
#include "doof_runtime.hpp"
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

namespace std_::time::duration {
    struct Duration;
}

namespace std_::event::index {
    struct Timer;
    struct ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_;
    struct ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_;
    struct ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_;
    struct ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_;
}

namespace std_::event::index {
    using doof_header_type_1 = std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>;
    using doof_header_type_2 = std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>;
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

namespace doof_event { using Backpressure = ::std_::event::index::Backpressure; }
namespace doof_event { using SendError = ::std_::event::index::SendError; }
namespace doof_event { using Timer = ::std_::event::index::Timer; }
namespace doof_event { using Duration = ::std_::time::duration::Duration; }
#include "native_event.hpp"

namespace std_::event::index {
    int32_t _trySendChannelMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(const std::shared_ptr<::doof_event::NativeChannel>& channel, doof_header_type_1 value, bool hasKey, const std::string& key);
    void _registerChannelReceiverMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(const std::shared_ptr<::doof_event::NativeChannel>& channel, const doof::callback<void(doof_header_type_2)>& handler);
    void _registerChannelReceiverMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(const std::shared_ptr<::doof_event::NativeChannel>& channel, const doof::callback<void(doof_header_type_1)>& handler);
    int32_t _trySendChannelMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(const std::shared_ptr<::doof_event::NativeChannel>& channel, doof_header_type_2 value, bool hasKey, const std::string& key);
    struct Timer : public std::enable_shared_from_this<Timer> {
    std::shared_ptr<::doof_event::NativeTimer> native;
    Timer(std::shared_ptr<::doof_event::NativeTimer> native) : native(native) {}
    bool cancel();
};
    struct ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_ : public std::enable_shared_from_this<ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
    doof::Result<Backpressure, SendError> send(doof_header_type_1 value, const std::optional<std::string>& key);
    void onReady(const doof::callback<void()>& handler);
    void onClosed(const doof::callback<void()>& handler);
    void close();
};
    struct ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_ : public std::enable_shared_from_this<ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
    void onMessage(const doof::callback<void(doof_header_type_2)>& handler);
    void onClosed(const doof::callback<void()>& handler);
    void close();
};
    struct ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_ : public std::enable_shared_from_this<ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
    void onMessage(const doof::callback<void(doof_header_type_1)>& handler);
    void onClosed(const doof::callback<void()>& handler);
    void close();
};
    struct ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_ : public std::enable_shared_from_this<ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
    doof::Result<Backpressure, SendError> send(doof_header_type_2 value, const std::optional<std::string>& key);
    void onReady(const doof::callback<void()>& handler);
    void onClosed(const doof::callback<void()>& handler);
    void close();
};
    std::shared_ptr<Timer> setTimeout(const std::shared_ptr<::std_::time::duration::Duration>& delay, const doof::callback<void()>& handler, bool keepsAlive);
    std::shared_ptr<Timer> setInterval(const std::shared_ptr<::std_::time::duration::Duration>& interval, const doof::callback<void()>& handler, bool keepsAlive);
    void runMainEventLoop();
    int32_t drainMainEventLoop();
    void setMainEventWakeHandler(const doof::callback<void()>& handler);
    void clearMainEventWakeHandler();
    std::tuple<std::shared_ptr<ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>, std::shared_ptr<ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>> createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive);
    std::tuple<std::shared_ptr<ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_>, std::shared_ptr<ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_>> createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive);
}
