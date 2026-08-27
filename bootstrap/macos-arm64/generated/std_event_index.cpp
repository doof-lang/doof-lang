#include "std_event_index.hpp"

namespace std_::event::index {



bool Timer::cancel() {
    return this->native->cancel();
}
std::shared_ptr<Timer> setTimeout(const std::shared_ptr<::std_::time::duration::Duration>& delay, const doof::callback<void()>& handler, bool keepsAlive) {
    if (delay->isNegative()) {
        doof::panic(std::string("setTimeout delay must not be negative"));
    }
    const auto timerHandler = handler;
    return std::make_shared<Timer>(::doof_event::NativeTimer::createTimeout(delay->toNanos(), keepsAlive, doof::callback<void()>([timerHandler]() -> void { return timerHandler.call(); })));
}
std::shared_ptr<Timer> setInterval(const std::shared_ptr<::std_::time::duration::Duration>& interval, const doof::callback<void()>& handler, bool keepsAlive) {
    if (interval->toNanos() <= 0LL) {
        doof::panic(std::string("setInterval interval must be positive"));
    }
    const auto timerHandler = handler;
    return std::make_shared<Timer>(::doof_event::NativeTimer::createInterval(interval->toNanos(), keepsAlive, doof::callback<void()>([timerHandler]() -> void { return timerHandler.call(); })));
}
void runMainEventLoop() {
    ::doof_event::runMainEventLoop();
}
int32_t drainMainEventLoop() {
    return ::doof_event::drainMainEventLoop();
}
void setMainEventWakeHandler(const doof::callback<void()>& handler) {
    ::doof_event::setMainEventWakeCallback(handler);
}
void clearMainEventWakeHandler() {
    ::doof_event::clearMainEventWakeHandler();
}
doof::Result<Backpressure, SendError> ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::send(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>> value, const std::optional<std::string>& key) {
    const auto code = (doof::is_null(key) ? _trySendChannelMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(this->native, value, false, std::string("")) : _trySendChannelMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(this->native, value, true, key.value()));
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
void ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::onReady(const doof::callback<void()>& handler) {
    this->native->registerSenderReady(handler);
}
void ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::onClosed(const doof::callback<void()>& handler) {
    this->native->registerSenderClosed(handler);
}
void ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::close() {
    this->native->tryClose();
}
void ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::onMessage(const doof::callback<void(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>>)>& handler) {
    _registerChannelReceiverMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(this->native, handler);
}
void ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::onClosed(const doof::callback<void()>& handler) {
    this->native->registerReceiverClosed(handler);
}
void ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::close() {
    this->native->tryClose();
}
void ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::onMessage(const doof::callback<void(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketOpen>, std::shared_ptr<::std_::http::websocket::WebSocketText>, std::shared_ptr<::std_::http::websocket::WebSocketBinary>, std::shared_ptr<::std_::http::websocket::WebSocketWritable>, std::shared_ptr<::std_::http::websocket::WebSocketClose>, std::shared_ptr<::std_::http::websocket::WebSocketError>>)>& handler) {
    _registerChannelReceiverMessage__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(this->native, handler);
}
void ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::onClosed(const doof::callback<void()>& handler) {
    this->native->registerReceiverClosed(handler);
}
void ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_::close() {
    this->native->tryClose();
}
doof::Result<Backpressure, SendError> ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::send(std::variant<std::shared_ptr<::std_::http::websocket::WebSocketSendText>, std::shared_ptr<::std_::http::websocket::WebSocketSendBinary>, std::shared_ptr<::std_::http::websocket::WebSocketPing>, std::shared_ptr<::std_::http::websocket::WebSocketCloseCommand>> value, const std::optional<std::string>& key) {
    const auto code = (doof::is_null(key) ? _trySendChannelMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(this->native, value, false, std::string("")) : _trySendChannelMessage__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(this->native, value, true, key.value()));
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
void ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::onReady(const doof::callback<void()>& handler) {
    this->native->registerSenderReady(handler);
}
void ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::onClosed(const doof::callback<void()>& handler) {
    this->native->registerSenderClosed(handler);
}
void ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_::close() {
    this->native->tryClose();
}
std::tuple<std::shared_ptr<ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>, std::shared_ptr<ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>> createChannel__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive) {
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
    return std::make_tuple(std::make_shared<ChannelSender__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>(native), std::make_shared<ChannelReceiver__union_std___http__websocket_WebSocketOpen__std___http__websocket_WebSocketText__std___http__websocket_WebSocketBinary__std___http__websocket_WebSocketWritable__std___http__websocket_WebSocketClose__std___http__websocket_WebSocketError_>(native));
}
std::tuple<std::shared_ptr<ChannelSender__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_>, std::shared_ptr<ChannelReceiver__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_>> createChannel__union_std___http__websocket_WebSocketSendText__std___http__websocket_WebSocketSendBinary__std___http__websocket_WebSocketPing__std___http__websocket_WebSocketCloseCommand_(int32_t capacity, int32_t highWater, int32_t lowWater, bool keepsAlive) {
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
