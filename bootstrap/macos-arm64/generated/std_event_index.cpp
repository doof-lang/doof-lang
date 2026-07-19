#include "std_event_index.hpp"
#include <cmath>
#include "std_time_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::event::index {
using namespace ::std_::time::index;



bool Timer::cancel() {
    return this->native->cancel();
}
std::shared_ptr<Timer> setTimeout(std::shared_ptr<::std_::time::duration::Duration> delay, doof::callback<void()> handler, bool keepsAlive) {
    if (delay->isNegative()) {
        doof::panic(std::string("setTimeout delay must not be negative"));
    }
    const auto timerHandler = handler;
    return std::make_shared<Timer>(::doof_event::NativeTimer::createTimeout(delay->toNanos(), keepsAlive, doof::callback<void()>([timerHandler]() -> void { return timerHandler.call(); })));
}
std::shared_ptr<Timer> setInterval(std::shared_ptr<::std_::time::duration::Duration> interval, doof::callback<void()> handler, bool keepsAlive) {
    if (interval->toNanos() <= 0LL) {
        doof::panic(std::string("setInterval interval must be positive"));
    }
    const auto timerHandler = handler;
    return std::make_shared<Timer>(::doof_event::NativeTimer::createInterval(interval->toNanos(), keepsAlive, doof::callback<void()>([timerHandler]() -> void { return timerHandler.call(); })));
}
void runMainEventLoop() {
    _runMainEventLoop();
}
int32_t drainMainEventLoop() {
    return _drainMainEventLoop();
}
void setMainEventWakeHandler(doof::callback<void()> handler) {
    _setMainEventWakeHandler(handler);
}
void clearMainEventWakeHandler() {
    _clearMainEventWakeHandler();
}
std::tuple<std::shared_ptr<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>, std::shared_ptr<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>> createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive) {
    if (capacity <= 0) {
        doof::panic(std::string("Channel capacity must be positive"));
    }
    const auto actualHighWater = ((highWater == 0) ? capacity : highWater);
    const auto actualLowWater = ((lowWater < 0) ? (actualHighWater / 2) : lowWater);
    if ((actualHighWater <= 0) || (actualHighWater > capacity)) {
        doof::panic(std::string("Channel highWater must be between 1 and capacity"));
    }
    if ((actualLowWater < 0) || (actualLowWater > actualHighWater)) {
        doof::panic(std::string("Channel lowWater must be between 0 and highWater"));
    }
    const auto native = ::doof_event::NativeChannel::createChannel(capacity, actualHighWater, actualLowWater, keepsAlive);
    return std::make_tuple(std::make_shared<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>(native), std::make_shared<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>(native));
}
std::tuple<std::shared_ptr<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>, std::shared_ptr<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>> createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive) {
    if (capacity <= 0) {
        doof::panic(std::string("Channel capacity must be positive"));
    }
    const auto actualHighWater = ((highWater == 0) ? capacity : highWater);
    const auto actualLowWater = ((lowWater < 0) ? (actualHighWater / 2) : lowWater);
    if ((actualHighWater <= 0) || (actualHighWater > capacity)) {
        doof::panic(std::string("Channel highWater must be between 1 and capacity"));
    }
    if ((actualLowWater < 0) || (actualLowWater > actualHighWater)) {
        doof::panic(std::string("Channel lowWater must be between 0 and highWater"));
    }
    const auto native = ::doof_event::NativeChannel::createChannel(capacity, actualHighWater, actualLowWater, keepsAlive);
    return std::make_tuple(std::make_shared<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>(native), std::make_shared<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>(native));
}
void _runMainEventLoop() {
    ::doof_event::runMainEventLoop();
}
int32_t _drainMainEventLoop() {
    return ::doof_event::drainMainEventLoop();
}
void _setMainEventWakeHandler(doof::callback<void()> handler) {
    ::doof_event::setMainEventWakeCallback(handler);
}
void _clearMainEventWakeHandler() {
    ::doof_event::clearMainEventWakeHandler();
}
}
