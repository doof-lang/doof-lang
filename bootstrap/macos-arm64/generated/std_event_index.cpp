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
#line 54 "/std/event/index.do"
doof::Result<Backpressure, SendError> ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::send(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>> value, const std::optional<std::string>& key) {
#line 55 "/std/event/index.do"
    const auto code = (doof::is_null(key) ? _trySendChannelMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(this->native, value, false, std::string("")) : _trySendChannelMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(this->native, value, true, key.value()));
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
void ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::onReady(const doof::callback<void()>& handler) {
#line 66 "/std/event/index.do"
    this->native->registerSenderReady(handler);
}
#line 69 "/std/event/index.do"
void ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::onClosed(const doof::callback<void()>& handler) {
#line 70 "/std/event/index.do"
    this->native->registerSenderClosed(handler);
}
#line 73 "/std/event/index.do"
void ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::close() {
#line 74 "/std/event/index.do"
    this->native->tryClose();
}
#line 81 "/std/event/index.do"
void ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::onMessage(const doof::callback<void(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>)>& handler) {
#line 82 "/std/event/index.do"
    _registerChannelReceiverMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(this->native, handler);
}
#line 85 "/std/event/index.do"
void ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::onClosed(const doof::callback<void()>& handler) {
#line 86 "/std/event/index.do"
    this->native->registerReceiverClosed(handler);
}
#line 89 "/std/event/index.do"
void ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::close() {
#line 90 "/std/event/index.do"
    this->native->tryClose();
}
#line 81 "/std/event/index.do"
void ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::onMessage(const doof::callback<void(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>)>& handler) {
#line 82 "/std/event/index.do"
    _registerChannelReceiverMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(this->native, handler);
}
#line 85 "/std/event/index.do"
void ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::onClosed(const doof::callback<void()>& handler) {
#line 86 "/std/event/index.do"
    this->native->registerReceiverClosed(handler);
}
#line 89 "/std/event/index.do"
void ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::close() {
#line 90 "/std/event/index.do"
    this->native->tryClose();
}
#line 54 "/std/event/index.do"
doof::Result<Backpressure, SendError> ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::send(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>> value, const std::optional<std::string>& key) {
#line 55 "/std/event/index.do"
    const auto code = (doof::is_null(key) ? _trySendChannelMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(this->native, value, false, std::string("")) : _trySendChannelMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(this->native, value, true, key.value()));
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
void ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::onReady(const doof::callback<void()>& handler) {
#line 66 "/std/event/index.do"
    this->native->registerSenderReady(handler);
}
#line 69 "/std/event/index.do"
void ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::onClosed(const doof::callback<void()>& handler) {
#line 70 "/std/event/index.do"
    this->native->registerSenderClosed(handler);
}
#line 73 "/std/event/index.do"
void ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::close() {
#line 74 "/std/event/index.do"
    this->native->tryClose();
}
#line 94 "/std/event/index.do"
std::tuple<std::shared_ptr<ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>, std::shared_ptr<ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>> createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive) {
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
    return std::make_tuple(std::make_shared<ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>(native), std::make_shared<ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>(native));
}
#line 94 "/std/event/index.do"
std::tuple<std::shared_ptr<ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_>, std::shared_ptr<ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_>> createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive) {
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
    return std::make_tuple(std::make_shared<ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_>(native), std::make_shared<ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_>(native));
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
int32_t _trySendChannelMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(const std::shared_ptr<::doof_event::NativeChannel>& channel, std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>> value, bool hasKey, const std::string& key) {
    return ::doof_event::trySendChannelMessage(channel, value, hasKey, key);
}
void _registerChannelReceiverMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(const std::shared_ptr<::doof_event::NativeChannel>& channel, const doof::callback<void(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>)>& handler) {
    ::doof_event::registerChannelReceiverMessage(channel, handler);
}
void _registerChannelReceiverMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(const std::shared_ptr<::doof_event::NativeChannel>& channel, const doof::callback<void(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>)>& handler) {
    ::doof_event::registerChannelReceiverMessage(channel, handler);
}
int32_t _trySendChannelMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(const std::shared_ptr<::doof_event::NativeChannel>& channel, std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>> value, bool hasKey, const std::string& key) {
    return ::doof_event::trySendChannelMessage(channel, value, hasKey, key);
}
}
