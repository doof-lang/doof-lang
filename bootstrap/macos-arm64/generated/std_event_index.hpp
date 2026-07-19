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
namespace std_::time::duration { struct Duration; }
namespace std_::time::duration { struct Thread; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }
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

namespace std_::event::index {
    struct Timer;
}

#include "std_time_index.hpp"

namespace doof_event { using Duration = ::std_::time::duration::Duration; }
namespace doof_event { using Thread = ::std_::time::duration::Thread; }
#include "native_event.hpp"

namespace std_::event::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
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
    void _runMainEventLoop();
    int32_t _drainMainEventLoop();
    void _setMainEventWakeHandler(doof::callback<void()> handler);
    void _clearMainEventWakeHandler();
    template <typename T>
struct ChannelSender : public std::enable_shared_from_this<ChannelSender<T>> {
    std::shared_ptr<::doof_event::NativeChannel> native;
    ChannelSender(std::shared_ptr<::doof_event::NativeChannel> native) : native(native) {}
    doof::Result<Backpressure, SendError> send(T value, std::optional<std::string> key = std::nullopt) {
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
    void onReady(doof::callback<void()> handler) {
        this->native->registerSenderReady(handler);
    }
    void onClosed(doof::callback<void()> handler) {
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
    void onMessage(doof::callback<void(T)> handler) {
        ::doof_event::registerChannelReceiverMessage<T>(this->native, handler);
    }
    void onClosed(doof::callback<void()> handler) {
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
    std::shared_ptr<Timer> setTimeout(std::shared_ptr<::std_::time::duration::Duration> delay, doof::callback<void()> handler, bool keepsAlive = true);
    std::shared_ptr<Timer> setInterval(std::shared_ptr<::std_::time::duration::Duration> interval, doof::callback<void()> handler, bool keepsAlive = true);
    void runMainEventLoop();
    int32_t drainMainEventLoop();
    void setMainEventWakeHandler(doof::callback<void()> handler);
    void clearMainEventWakeHandler();
    std::tuple<std::shared_ptr<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>, std::shared_ptr<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>> createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(int32_t capacity = 256, int32_t highWater = 0, int32_t lowWater = -1, bool keepsAlive = true);
    std::tuple<std::shared_ptr<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>, std::shared_ptr<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>> createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(int32_t capacity = 256, int32_t highWater = 0, int32_t lowWater = -1, bool keepsAlive = true);
}

namespace std_::event::index {
}
