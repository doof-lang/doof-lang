#include "std_time_duration.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::time::duration {

std::shared_ptr<Duration> Duration::ZERO = std::make_shared<Duration>(0LL);
std::shared_ptr<Duration> Duration::ofNanos(int64_t n) {
    return std::make_shared<Duration>(n);
}
std::shared_ptr<Duration> Duration::ofMicros(int64_t us) {
    return std::make_shared<Duration>((us * 1000LL));
}
std::shared_ptr<Duration> Duration::ofMillis(int64_t ms) {
    return std::make_shared<Duration>((ms * 1000000LL));
}
std::shared_ptr<Duration> Duration::ofSeconds(int64_t s) {
    return std::make_shared<Duration>((s * 1000000000LL));
}
std::shared_ptr<Duration> Duration::ofMinutes(int64_t m) {
    return std::make_shared<Duration>(((m * 60LL) * 1000000000LL));
}
std::shared_ptr<Duration> Duration::ofHours(int64_t h) {
    return std::make_shared<Duration>(((h * 3600LL) * 1000000000LL));
}
std::shared_ptr<Duration> Duration::ofDays(int64_t d) {
    return std::make_shared<Duration>(((d * 86400LL) * 1000000000LL));
}
doof::Result<std::shared_ptr<Duration>, std::string> Duration::parse(std::string s) {
    return parseDuration(s);
}
int64_t Duration::toNanos() {
    return this->nanos;
}
int64_t Duration::toMicros() {
    return (this->nanos / 1000LL);
}
int64_t Duration::toMillis() {
    return (this->nanos / 1000000LL);
}
double Duration::toSeconds() {
    return (static_cast<double>(this->nanos) / 1000000000.0);
}
double Duration::toMinutes() {
    return (static_cast<double>(this->nanos) / 60000000000.0);
}
double Duration::toHours() {
    return (static_cast<double>(this->nanos) / 3600000000000.0);
}
double Duration::toDays() {
    return (static_cast<double>(this->nanos) / 86400000000000.0);
}
bool Duration::isNegative() {
    return (this->nanos < 0LL);
}
bool Duration::isZero() {
    return (this->nanos == 0LL);
}
std::shared_ptr<Duration> Duration::abs() {
    return std::make_shared<Duration>(((this->nanos < 0LL) ? -this->nanos : this->nanos));
}
std::shared_ptr<Duration> Duration::negated() {
    return std::make_shared<Duration>(-this->nanos);
}
std::shared_ptr<Duration> Duration::plus(std::shared_ptr<Duration> other) {
    return std::make_shared<Duration>((this->nanos + other->nanos));
}
std::shared_ptr<Duration> Duration::minus(std::shared_ptr<Duration> other) {
    return std::make_shared<Duration>((this->nanos - other->nanos));
}
std::shared_ptr<Duration> Duration::multipliedBy(int64_t factor) {
    return std::make_shared<Duration>((this->nanos * factor));
}
std::shared_ptr<Duration> Duration::dividedBy(int64_t divisor) {
    return std::make_shared<Duration>((this->nanos / divisor));
}
int32_t Duration::compareTo(std::shared_ptr<Duration> other) {
    if (this->nanos < other->nanos) {
        return -1;
    }
    if (this->nanos > other->nanos) {
        return 1;
    }
    return 0;
}
bool Duration::isLessThan(std::shared_ptr<Duration> other) {
    return (this->nanos < other->nanos);
}
bool Duration::isGreaterThan(std::shared_ptr<Duration> other) {
    return (this->nanos > other->nanos);
}
bool Duration::equals(std::shared_ptr<Duration> other) {
    return (this->nanos == other->nanos);
}
std::string Duration::toISOString() {
    auto remaining = ((this->nanos < 0LL) ? -this->nanos : this->nanos);
    auto sign = ((this->nanos < 0LL) ? std::string("-") : std::string(""));
    auto days = (remaining / 86400000000000LL);
    (remaining = (remaining % 86400000000000LL));
    auto hours = (remaining / 3600000000000LL);
    (remaining = (remaining % 3600000000000LL));
    auto minutes = (remaining / 60000000000LL);
    (remaining = (remaining % 60000000000LL));
    auto seconds = (remaining / 1000000000LL);
    auto subsecNanos = (remaining % 1000000000LL);
    auto result = std::string("") + doof::to_string(sign) + std::string("P");
    if (days != 0LL) {
        (result = std::string("") + doof::to_string(result) + std::string("") + doof::to_string(days) + std::string("D"));
    }
    auto timePart = std::string("");
    if (hours != 0LL) {
        (timePart = std::string("") + doof::to_string(timePart) + std::string("") + doof::to_string(hours) + std::string("H"));
    }
    if (minutes != 0LL) {
        (timePart = std::string("") + doof::to_string(timePart) + std::string("") + doof::to_string(minutes) + std::string("M"));
    }
    if (subsecNanos != 0LL) {
        (timePart = std::string("") + doof::to_string(timePart) + std::string("") + doof::to_string(seconds) + std::string(".") + doof::to_string(doof::string_trimEnd(doof::string_padStart(doof::to_string(subsecNanos), 9, U'\u0030'), U'\u0030')) + std::string("S"));
    } else if ((seconds != 0LL) || (((days == 0LL) && (hours == 0LL)) && (minutes == 0LL))) {
        (timePart = std::string("") + doof::to_string(timePart) + std::string("") + doof::to_string(seconds) + std::string("S"));
    }
    if (static_cast<int32_t>(timePart.size()) > 0) {
        (result = std::string("") + doof::to_string(result) + std::string("T") + doof::to_string(timePart) + std::string(""));
    }
    return result;
}
doof::JsonObject Duration::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["nanos"] = doof::json_value(this->nanos);
    return _json;
}
doof::Result<std::shared_ptr<Duration>, std::string> Duration::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_nanos = _object->find("nanos");
    if (_iterator_nanos == _object->end()) { return doof::Failure<std::string>{"Missing required field \"nanos\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_nanos->second) : doof::json_is_number(_iterator_nanos->second)))) { return doof::Failure<std::string>{"Field \"nanos\" expected number but got " + std::string(doof::json_type_name(_iterator_nanos->second))}; }
    auto _field_nanos = (_lenient ? doof::json_as_long_lenient(_iterator_nanos->second) : doof::json_as_long(_iterator_nanos->second));
    return doof::Success<std::shared_ptr<Duration>>{std::make_shared<Duration>(_field_nanos)};
}
doof::Result<std::shared_ptr<Duration>, std::string> parseDuration(std::string s) {
    if (static_cast<int32_t>(s.size()) < 2) {
        return doof::Failure<std::string>{ std::string("Invalid duration format") };
    }
    auto index = 0;
    auto sign = 1LL;
    if (doof::string_at(s, index, "", 0) == U'\u002D') {
        (sign = -1LL);
        (index = (index + 1));
    } else if (doof::string_at(s, index, "", 0) == U'\u002B') {
        (index = (index + 1));
    }
    if ((index >= static_cast<int32_t>(s.size())) || (doof::string_at(s, index, "", 0) != U'\u0050')) {
        return doof::Failure<std::string>{ std::string("Duration must start with 'P'") };
    }
    (index = (index + 1));
    auto total = 0LL;
    auto inTime = false;
    auto sawComponent = false;
    auto lastOrder = 0;
    while (index < static_cast<int32_t>(s.size())) {
        if (doof::string_at(s, index, "", 0) == U'\u0054') {
            if (inTime) {
                return doof::Failure<std::string>{ std::string("Duration contains duplicate time marker") };
            }
            (inTime = true);
            (index = (index + 1));
            if (index >= static_cast<int32_t>(s.size())) {
                return doof::Failure<std::string>{ std::string("Duration time marker must be followed by a component") };
            }
            continue;
        }
        if (!isDigit(doof::string_at(s, index, "", 0))) {
            return doof::Failure<std::string>{ std::string("Duration component must start with a digit") };
        }
        auto whole = 0LL;
        while ((index < static_cast<int32_t>(s.size())) && isDigit(doof::string_at(s, index, "", 0))) {
            (whole = ((whole * 10LL) + static_cast<int64_t>(digitValue(doof::string_at(s, index, "", 0)))));
            (index = (index + 1));
        }
        auto fractionNanos = 0LL;
        auto hasFraction = false;
        if ((index < static_cast<int32_t>(s.size())) && (doof::string_at(s, index, "", 0) == U'\u002E')) {
            (hasFraction = true);
            (index = (index + 1));
            auto digits = 0;
            while ((index < static_cast<int32_t>(s.size())) && isDigit(doof::string_at(s, index, "", 0))) {
                if (digits >= 9) {
                    return doof::Failure<std::string>{ std::string("Duration fractional seconds must use at most 9 digits") };
                }
                (fractionNanos = ((fractionNanos * 10LL) + static_cast<int64_t>(digitValue(doof::string_at(s, index, "", 0)))));
                (digits = (digits + 1));
                (index = (index + 1));
            }
            if (digits == 0) {
                return doof::Failure<std::string>{ std::string("Duration fraction must contain digits") };
            }
            while (digits < 9) {
                (fractionNanos = (fractionNanos * 10LL));
                (digits = (digits + 1));
            }
        }
        if (index >= static_cast<int32_t>(s.size())) {
            return doof::Failure<std::string>{ std::string("Duration component missing designator") };
        }
        auto designator = doof::string_at(s, index, "", 0);
        (index = (index + 1));
        auto order = 0;
        auto multiplier = 0LL;
        if (designator == U'\u0044') {
            if (inTime || hasFraction) {
                return doof::Failure<std::string>{ std::string("Invalid duration day component") };
            }
            (order = 1);
            (multiplier = 86400000000000LL);
        } else if (designator == U'\u0048') {
            if (!inTime || hasFraction) {
                return doof::Failure<std::string>{ std::string("Invalid duration hour component") };
            }
            (order = 2);
            (multiplier = 3600000000000LL);
        } else if (designator == U'\u004D') {
            if (!inTime || hasFraction) {
                return doof::Failure<std::string>{ std::string("Invalid duration minute component") };
            }
            (order = 3);
            (multiplier = 60000000000LL);
        } else if (designator == U'\u0053') {
            if (!inTime) {
                return doof::Failure<std::string>{ std::string("Invalid duration second component") };
            }
            (order = 4);
            (multiplier = 1000000000LL);
        } else {
            return doof::Failure<std::string>{ std::string("Invalid duration component designator") };
        }
        if (order <= lastOrder) {
            return doof::Failure<std::string>{ std::string("Duration components must be in ISO order") };
        }
        (lastOrder = order);
        (total = (total + (whole * multiplier)));
        if (hasFraction) {
            (total = (total + fractionNanos));
        }
        (sawComponent = true);
    }
    if (!sawComponent) {
        return doof::Failure<std::string>{ std::string("Duration must contain at least one component") };
    }
    return doof::Success<std::shared_ptr<Duration>>{ Duration::ofNanos((total * sign)) };
}
bool isDigit(char32_t c) {
    return ((c >= U'\u0030') && (c <= U'\u0039'));
}
int32_t digitValue(char32_t c) {
    if (c == U'\u0030') {
        return 0;
    }
    if (c == U'\u0031') {
        return 1;
    }
    if (c == U'\u0032') {
        return 2;
    }
    if (c == U'\u0033') {
        return 3;
    }
    if (c == U'\u0034') {
        return 4;
    }
    if (c == U'\u0035') {
        return 5;
    }
    if (c == U'\u0036') {
        return 6;
    }
    if (c == U'\u0037') {
        return 7;
    }
    if (c == U'\u0038') {
        return 8;
    }
    return 9;
}

void Thread::sleep(std::shared_ptr<Duration> duration) {
    ::doof_time::thread_sleep_nanos(duration->toNanos());
}
doof::JsonObject Thread::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    return _json;
}
doof::Result<std::shared_ptr<Thread>, std::string> Thread::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    return doof::Success<std::shared_ptr<Thread>>{std::make_shared<Thread>()};
}
void _threadSleepNanos(int64_t nanos) {
    ::doof_time::thread_sleep_nanos(nanos);
}
}
