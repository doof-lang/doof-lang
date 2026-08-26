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
    template <typename T>
    struct ChannelSender;
    template <typename T>
    struct ChannelReceiver;
    struct Timer;
}

namespace std_::event::index {
    using __type1 = std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>;
    using __type2 = std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>;
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
    void _runMainEventLoop();
    int32_t _drainMainEventLoop();
    void _setMainEventWakeHandler(const doof::callback<void()>& handler);
    void _clearMainEventWakeHandler();
    template <typename T>
struct ChannelSender : public std::enable_shared_from_this<ChannelSender<T>> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelSender(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
#line 54 "/std/event/index.do"
    doof::Result<Backpressure, SendError> send(T value, const std::optional<std::string>& key = std::nullopt) {
#line 55 "/std/event/index.do"
        const auto code = (doof::is_null(key) ? ::doof_event::trySendChannelMessage<T>(this->native, value, false, std::string("")) : ::doof_event::trySendChannelMessage<T>(this->native, value, true, key.value()));
#line 57 "/std/event/index.do"
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
#line 65 "/std/event/index.do"
    void onReady(const doof::callback<void()>& handler) {
#line 66 "/std/event/index.do"
        this->native->registerSenderReady(handler);
    }
#line 69 "/std/event/index.do"
    void onClosed(const doof::callback<void()>& handler) {
#line 70 "/std/event/index.do"
        this->native->registerSenderClosed(handler);
    }
#line 73 "/std/event/index.do"
    void close() {
#line 74 "/std/event/index.do"
        this->native->tryClose();
    }
};
    template <typename T>
struct ChannelReceiver : public std::enable_shared_from_this<ChannelReceiver<T>> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelReceiver(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
#line 81 "/std/event/index.do"
    void onMessage(const doof::callback<void(T)>& handler) {
#line 82 "/std/event/index.do"
        ::doof_event::registerChannelReceiverMessage<T>(this->native, handler);
    }
#line 85 "/std/event/index.do"
    void onClosed(const doof::callback<void()>& handler) {
#line 86 "/std/event/index.do"
        this->native->registerReceiverClosed(handler);
    }
#line 89 "/std/event/index.do"
    void close() {
#line 90 "/std/event/index.do"
        this->native->tryClose();
    }
};
    struct Timer : public std::enable_shared_from_this<Timer> {
    std::shared_ptr<::doof_event::NativeTimer> native;
    Timer(std::shared_ptr<::doof_event::NativeTimer> native) : native(native) {}
    bool cancel();
};
    std::shared_ptr<Timer> setTimeout(const std::shared_ptr<::std_::time::duration::Duration>& delay, const doof::callback<void()>& handler, bool keepsAlive = true);
    std::shared_ptr<Timer> setInterval(const std::shared_ptr<::std_::time::duration::Duration>& interval, const doof::callback<void()>& handler, bool keepsAlive = true);
    void runMainEventLoop();
    int32_t drainMainEventLoop();
    void setMainEventWakeHandler(const doof::callback<void()>& handler);
    void clearMainEventWakeHandler();
    std::tuple<std::shared_ptr<ChannelSender<__type1>>, std::shared_ptr<ChannelReceiver<__type1>>> createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(int32_t capacity = 256, int32_t highWater = 0, int32_t lowWater = -1, bool keepsAlive = true);
    std::tuple<std::shared_ptr<ChannelSender<__type2>>, std::shared_ptr<ChannelReceiver<__type2>>> createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(int32_t capacity = 256, int32_t highWater = 0, int32_t lowWater = -1, bool keepsAlive = true);
}
