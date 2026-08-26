#include "std_event_index.hpp"

namespace std_::event::index {



#line 123 "/std/event/index.do"
bool Timer::cancel() {
#line 124 "/std/event/index.do"
    return this->native->cancel();
}
#line 128 "/std/event/index.do"
std::shared_ptr<Timer> setTimeout(const std::shared_ptr<::std_::time::duration::Duration>& delay, const doof::callback<void()>& handler, bool keepsAlive) {
#line 133 "/std/event/index.do"
    if (delay->isNegative()) {
#line 134 "/std/event/index.do"
        doof::panic(std::string("setTimeout delay must not be negative"));
    }
#line 137 "/std/event/index.do"
    const auto timerHandler = handler;
#line 138 "/std/event/index.do"
    return std::make_shared<Timer>(::doof_event::NativeTimer::createTimeout(delay->toNanos(), keepsAlive, doof::callback<void()>([timerHandler]() -> void { return timerHandler.call(); })));
}
#line 141 "/std/event/index.do"
std::shared_ptr<Timer> setInterval(const std::shared_ptr<::std_::time::duration::Duration>& interval, const doof::callback<void()>& handler, bool keepsAlive) {
#line 146 "/std/event/index.do"
    if (interval->toNanos() <= 0LL) {
#line 147 "/std/event/index.do"
        doof::panic(std::string("setInterval interval must be positive"));
    }
#line 150 "/std/event/index.do"
    const auto timerHandler = handler;
#line 151 "/std/event/index.do"
    return std::make_shared<Timer>(::doof_event::NativeTimer::createInterval(interval->toNanos(), keepsAlive, doof::callback<void()>([timerHandler]() -> void { return timerHandler.call(); })));
}
#line 158 "/std/event/index.do"
void runMainEventLoop() {
#line 159 "/std/event/index.do"
    ::doof_event::runMainEventLoop();
}
#line 165 "/std/event/index.do"
int32_t drainMainEventLoop() {
#line 166 "/std/event/index.do"
    return ::doof_event::drainMainEventLoop();
}
#line 169 "/std/event/index.do"
void setMainEventWakeHandler(const doof::callback<void()>& handler) {
#line 170 "/std/event/index.do"
    ::doof_event::setMainEventWakeCallback(handler);
}
#line 173 "/std/event/index.do"
void clearMainEventWakeHandler() {
#line 174 "/std/event/index.do"
    ::doof_event::clearMainEventWakeHandler();
}
#line 1 "<doof-generated>"
#line 94 "/std/event/index.do"
std::tuple<std::shared_ptr<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>, std::shared_ptr<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>> createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive) {
#line 100 "/std/event/index.do"
    if (capacity <= 0) {
#line 101 "/std/event/index.do"
        doof::panic(std::string("Channel capacity must be positive"));
    }
#line 103 "/std/event/index.do"
    const auto actualHighWater = ((highWater == 0) ? capacity : highWater);
#line 104 "/std/event/index.do"
    const auto actualLowWater = ((lowWater < 0) ? (actualHighWater / 2) : lowWater);
#line 106 "/std/event/index.do"
    if ((actualHighWater <= 0) || (actualHighWater > capacity)) {
#line 107 "/std/event/index.do"
        doof::panic(std::string("Channel highWater must be between 1 and capacity"));
    }
#line 109 "/std/event/index.do"
    if ((actualLowWater < 0) || (actualLowWater > actualHighWater)) {
#line 110 "/std/event/index.do"
        doof::panic(std::string("Channel lowWater must be between 0 and highWater"));
    }
#line 113 "/std/event/index.do"
    const auto native = ::doof_event::NativeChannel::createChannel(capacity, actualHighWater, actualLowWater, keepsAlive);
#line 114 "/std/event/index.do"
    return std::make_tuple(std::make_shared<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>(native), std::make_shared<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>>>(native));
}
#line 94 "/std/event/index.do"
std::tuple<std::shared_ptr<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>, std::shared_ptr<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>> createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive) {
#line 100 "/std/event/index.do"
    if (capacity <= 0) {
#line 101 "/std/event/index.do"
        doof::panic(std::string("Channel capacity must be positive"));
    }
#line 103 "/std/event/index.do"
    const auto actualHighWater = ((highWater == 0) ? capacity : highWater);
#line 104 "/std/event/index.do"
    const auto actualLowWater = ((lowWater < 0) ? (actualHighWater / 2) : lowWater);
#line 106 "/std/event/index.do"
    if ((actualHighWater <= 0) || (actualHighWater > capacity)) {
#line 107 "/std/event/index.do"
        doof::panic(std::string("Channel highWater must be between 1 and capacity"));
    }
#line 109 "/std/event/index.do"
    if ((actualLowWater < 0) || (actualLowWater > actualHighWater)) {
#line 110 "/std/event/index.do"
        doof::panic(std::string("Channel lowWater must be between 0 and highWater"));
    }
#line 113 "/std/event/index.do"
    const auto native = ::doof_event::NativeChannel::createChannel(capacity, actualHighWater, actualLowWater, keepsAlive);
#line 114 "/std/event/index.do"
    return std::make_tuple(std::make_shared<ChannelSender<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>(native), std::make_shared<ChannelReceiver<std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>>>(native));
}
void _runMainEventLoop() {
    ::doof_event::runMainEventLoop();
}
int32_t _drainMainEventLoop() {
    return ::doof_event::drainMainEventLoop();
}
void _setMainEventWakeHandler(const doof::callback<void()>& handler) {
    ::doof_event::setMainEventWakeCallback(handler);
}
void _clearMainEventWakeHandler() {
    ::doof_event::clearMainEventWakeHandler();
}
}
