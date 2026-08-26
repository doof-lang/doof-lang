#include "std_time_duration.hpp"

namespace std_::time::duration {

std::shared_ptr<Duration> Duration::ZERO;
#line 7 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::ofNanos(int64_t n) {
    return std::make_shared<Duration>(n);
}
#line 8 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::ofMicros(int64_t us) {
    return std::make_shared<Duration>((us * 1000LL));
}
#line 9 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::ofMillis(int64_t ms) {
    return std::make_shared<Duration>((ms * 1000000LL));
}
#line 10 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::ofSeconds(int64_t s) {
    return std::make_shared<Duration>((s * 1000000000LL));
}
#line 11 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::ofMinutes(int64_t m) {
    return std::make_shared<Duration>(((m * 60LL) * 1000000000LL));
}
#line 12 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::ofHours(int64_t h) {
    return std::make_shared<Duration>(((h * 3600LL) * 1000000000LL));
}
#line 13 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::ofDays(int64_t d) {
    return std::make_shared<Duration>(((d * 86400LL) * 1000000000LL));
}
#line 16 "/std/time/duration.do"
doof::Result<std::shared_ptr<Duration>, std::string> Duration::parse(const std::string& s) {
#line 17 "/std/time/duration.do"
    return parseDuration(s);
}
#line 24 "/std/time/duration.do"
int64_t Duration::toNanos() {
    return this->nanos;
}
#line 25 "/std/time/duration.do"
int64_t Duration::toMicros() {
    return (this->nanos / 1000LL);
}
#line 26 "/std/time/duration.do"
int64_t Duration::toMillis() {
    return (this->nanos / 1000000LL);
}
#line 27 "/std/time/duration.do"
double Duration::toSeconds() {
    return (static_cast<double>(this->nanos) / 1000000000.0);
}
#line 28 "/std/time/duration.do"
double Duration::toMinutes() {
    return (static_cast<double>(this->nanos) / 60000000000.0);
}
#line 29 "/std/time/duration.do"
double Duration::toHours() {
    return (static_cast<double>(this->nanos) / 3600000000000.0);
}
#line 30 "/std/time/duration.do"
double Duration::toDays() {
    return (static_cast<double>(this->nanos) / 86400000000000.0);
}
#line 32 "/std/time/duration.do"
bool Duration::isNegative() {
    return (this->nanos < 0LL);
}
#line 33 "/std/time/duration.do"
bool Duration::isZero() {
    return (this->nanos == 0LL);
}
#line 34 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::abs() {
    return std::make_shared<Duration>(((this->nanos < 0LL) ? -this->nanos : this->nanos));
}
#line 35 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::negated() {
    return std::make_shared<Duration>(-this->nanos);
}
#line 39 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::plus(const std::shared_ptr<Duration>& other) {
    return std::make_shared<Duration>((this->nanos + other->nanos));
}
#line 40 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::minus(const std::shared_ptr<Duration>& other) {
    return std::make_shared<Duration>((this->nanos - other->nanos));
}
#line 41 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::multipliedBy(int64_t factor) {
    return std::make_shared<Duration>((this->nanos * factor));
}
#line 42 "/std/time/duration.do"
std::shared_ptr<Duration> Duration::dividedBy(int64_t divisor) {
    return std::make_shared<Duration>((this->nanos / divisor));
}
#line 46 "/std/time/duration.do"
int32_t Duration::compareTo(const std::shared_ptr<Duration>& other) {
#line 47 "/std/time/duration.do"
    if (this->nanos < other->nanos) {
#line 47 "/std/time/duration.do"
        return -1;
    }
#line 48 "/std/time/duration.do"
    if (this->nanos > other->nanos) {
#line 48 "/std/time/duration.do"
        return 1;
    }
#line 49 "/std/time/duration.do"
    return 0;
}
#line 52 "/std/time/duration.do"
bool Duration::isLessThan(const std::shared_ptr<Duration>& other) {
    return (this->nanos < other->nanos);
}
#line 53 "/std/time/duration.do"
bool Duration::isGreaterThan(const std::shared_ptr<Duration>& other) {
    return (this->nanos > other->nanos);
}
#line 54 "/std/time/duration.do"
bool Duration::equals(const std::shared_ptr<Duration>& other) {
    return (this->nanos == other->nanos);
}
#line 59 "/std/time/duration.do"
std::string Duration::toISOString() {
#line 60 "/std/time/duration.do"
    auto remaining = ((this->nanos < 0LL) ? -this->nanos : this->nanos);
#line 61 "/std/time/duration.do"
    auto sign = ((this->nanos < 0LL) ? std::string("-") : std::string(""));
#line 63 "/std/time/duration.do"
    auto days = (remaining / 86400000000000LL);
#line 64 "/std/time/duration.do"
    (remaining = (remaining % 86400000000000LL));
#line 65 "/std/time/duration.do"
    auto hours = (remaining / 3600000000000LL);
#line 66 "/std/time/duration.do"
    (remaining = (remaining % 3600000000000LL));
#line 67 "/std/time/duration.do"
    auto minutes = (remaining / 60000000000LL);
#line 68 "/std/time/duration.do"
    (remaining = (remaining % 60000000000LL));
#line 69 "/std/time/duration.do"
    auto seconds = (remaining / 1000000000LL);
#line 70 "/std/time/duration.do"
    auto subsecNanos = (remaining % 1000000000LL);
#line 72 "/std/time/duration.do"
    auto result = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(sign); _interpolation += "P"; return _interpolation; }());
#line 73 "/std/time/duration.do"
    if (days != 0LL) {
#line 74 "/std/time/duration.do"
        (result = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(result); _interpolation += ""; _interpolation += doof::to_string(days); _interpolation += "D"; return _interpolation; }()));
    }
#line 77 "/std/time/duration.do"
    auto timePart = std::string("");
#line 78 "/std/time/duration.do"
    if (hours != 0LL) {
#line 79 "/std/time/duration.do"
        (timePart = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(timePart); _interpolation += ""; _interpolation += doof::to_string(hours); _interpolation += "H"; return _interpolation; }()));
    }
#line 81 "/std/time/duration.do"
    if (minutes != 0LL) {
#line 82 "/std/time/duration.do"
        (timePart = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(timePart); _interpolation += ""; _interpolation += doof::to_string(minutes); _interpolation += "M"; return _interpolation; }()));
    }
#line 84 "/std/time/duration.do"
    if (subsecNanos != 0LL) {
#line 85 "/std/time/duration.do"
        (timePart = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(timePart); _interpolation += ""; _interpolation += doof::to_string(seconds); _interpolation += "."; _interpolation += doof::to_string(doof::string_trimEnd(doof::string_padStart(doof::to_string(subsecNanos), 9, U'\u0030'), U'\u0030')); _interpolation += "S"; return _interpolation; }()));
    } else if ((seconds != 0LL) || (((days == 0LL) && (hours == 0LL)) && (minutes == 0LL))) {
#line 87 "/std/time/duration.do"
        (timePart = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(timePart); _interpolation += ""; _interpolation += doof::to_string(seconds); _interpolation += "S"; return _interpolation; }()));
    }
#line 90 "/std/time/duration.do"
    if (static_cast<int32_t>(timePart.size()) > 0) {
#line 91 "/std/time/duration.do"
        (result = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(result); _interpolation += "T"; _interpolation += doof::to_string(timePart); _interpolation += ""; return _interpolation; }()));
    }
#line 94 "/std/time/duration.do"
    return result;
}
#line 98 "/std/time/duration.do"
doof::Result<std::shared_ptr<Duration>, std::string> parseDuration(const std::string& s) {
#line 99 "/std/time/duration.do"
    if (static_cast<int32_t>(s.size()) < 2) {
#line 100 "/std/time/duration.do"
        return doof::Failure<std::string>{ std::string("Invalid duration format") };
    }
#line 103 "/std/time/duration.do"
    auto index = 0;
#line 104 "/std/time/duration.do"
    auto sign = 1LL;
#line 105 "/std/time/duration.do"
    if (doof::string_at(s, index, "", 0) == U'\u002D') {
#line 106 "/std/time/duration.do"
        (sign = -1LL);
#line 107 "/std/time/duration.do"
        (index = (index + 1));
    } else if (doof::string_at(s, index, "", 0) == U'\u002B') {
#line 109 "/std/time/duration.do"
        (index = (index + 1));
    }
#line 112 "/std/time/duration.do"
    if ((index >= static_cast<int32_t>(s.size())) || (doof::string_at(s, index, "", 0) != U'\u0050')) {
#line 113 "/std/time/duration.do"
        return doof::Failure<std::string>{ std::string("Duration must start with 'P'") };
    }
#line 115 "/std/time/duration.do"
    (index = (index + 1));
#line 117 "/std/time/duration.do"
    auto total = 0LL;
#line 118 "/std/time/duration.do"
    auto inTime = false;
#line 119 "/std/time/duration.do"
    auto sawComponent = false;
#line 120 "/std/time/duration.do"
    auto lastOrder = 0;
#line 122 "/std/time/duration.do"
    while (index < static_cast<int32_t>(s.size())) {
#line 123 "/std/time/duration.do"
        if (doof::string_at(s, index, "", 0) == U'\u0054') {
#line 124 "/std/time/duration.do"
            if (inTime) {
#line 125 "/std/time/duration.do"
                return doof::Failure<std::string>{ std::string("Duration contains duplicate time marker") };
            }
#line 127 "/std/time/duration.do"
            (inTime = true);
#line 128 "/std/time/duration.do"
            (index = (index + 1));
#line 129 "/std/time/duration.do"
            if (index >= static_cast<int32_t>(s.size())) {
#line 130 "/std/time/duration.do"
                return doof::Failure<std::string>{ std::string("Duration time marker must be followed by a component") };
            }
#line 132 "/std/time/duration.do"
            continue;
        }
#line 135 "/std/time/duration.do"
        if (!isDigit(doof::string_at(s, index, "", 0))) {
#line 136 "/std/time/duration.do"
            return doof::Failure<std::string>{ std::string("Duration component must start with a digit") };
        }
#line 139 "/std/time/duration.do"
        auto whole = 0LL;
#line 140 "/std/time/duration.do"
        while ((index < static_cast<int32_t>(s.size())) && isDigit(doof::string_at(s, index, "", 0))) {
#line 141 "/std/time/duration.do"
            (whole = ((whole * 10LL) + static_cast<int64_t>(digitValue(doof::string_at(s, index, "", 0)))));
#line 142 "/std/time/duration.do"
            (index = (index + 1));
        }
#line 145 "/std/time/duration.do"
        auto fractionNanos = 0LL;
#line 146 "/std/time/duration.do"
        auto hasFraction = false;
#line 147 "/std/time/duration.do"
        if ((index < static_cast<int32_t>(s.size())) && (doof::string_at(s, index, "", 0) == U'\u002E')) {
#line 148 "/std/time/duration.do"
            (hasFraction = true);
#line 149 "/std/time/duration.do"
            (index = (index + 1));
#line 150 "/std/time/duration.do"
            auto digits = 0;
#line 151 "/std/time/duration.do"
            while ((index < static_cast<int32_t>(s.size())) && isDigit(doof::string_at(s, index, "", 0))) {
#line 152 "/std/time/duration.do"
                if (digits >= 9) {
#line 153 "/std/time/duration.do"
                    return doof::Failure<std::string>{ std::string("Duration fractional seconds must use at most 9 digits") };
                }
#line 155 "/std/time/duration.do"
                (fractionNanos = ((fractionNanos * 10LL) + static_cast<int64_t>(digitValue(doof::string_at(s, index, "", 0)))));
#line 156 "/std/time/duration.do"
                (digits = (digits + 1));
#line 157 "/std/time/duration.do"
                (index = (index + 1));
            }
#line 159 "/std/time/duration.do"
            if (digits == 0) {
#line 160 "/std/time/duration.do"
                return doof::Failure<std::string>{ std::string("Duration fraction must contain digits") };
            }
#line 162 "/std/time/duration.do"
            while (digits < 9) {
#line 163 "/std/time/duration.do"
                (fractionNanos = (fractionNanos * 10LL));
#line 164 "/std/time/duration.do"
                (digits = (digits + 1));
            }
        }
#line 168 "/std/time/duration.do"
        if (index >= static_cast<int32_t>(s.size())) {
#line 169 "/std/time/duration.do"
            return doof::Failure<std::string>{ std::string("Duration component missing designator") };
        }
#line 172 "/std/time/duration.do"
        auto designator = doof::string_at(s, index, "", 0);
#line 173 "/std/time/duration.do"
        (index = (index + 1));
#line 175 "/std/time/duration.do"
        auto order = 0;
#line 176 "/std/time/duration.do"
        auto multiplier = 0LL;
#line 177 "/std/time/duration.do"
        if (designator == U'\u0044') {
#line 178 "/std/time/duration.do"
            if (inTime || hasFraction) {
#line 179 "/std/time/duration.do"
                return doof::Failure<std::string>{ std::string("Invalid duration day component") };
            }
#line 181 "/std/time/duration.do"
            (order = 1);
#line 182 "/std/time/duration.do"
            (multiplier = 86400000000000LL);
        } else if (designator == U'\u0048') {
#line 184 "/std/time/duration.do"
            if (!inTime || hasFraction) {
#line 185 "/std/time/duration.do"
                return doof::Failure<std::string>{ std::string("Invalid duration hour component") };
            }
#line 187 "/std/time/duration.do"
            (order = 2);
#line 188 "/std/time/duration.do"
            (multiplier = 3600000000000LL);
        } else if (designator == U'\u004D') {
#line 190 "/std/time/duration.do"
            if (!inTime || hasFraction) {
#line 191 "/std/time/duration.do"
                return doof::Failure<std::string>{ std::string("Invalid duration minute component") };
            }
#line 193 "/std/time/duration.do"
            (order = 3);
#line 194 "/std/time/duration.do"
            (multiplier = 60000000000LL);
        } else if (designator == U'\u0053') {
#line 196 "/std/time/duration.do"
            if (!inTime) {
#line 197 "/std/time/duration.do"
                return doof::Failure<std::string>{ std::string("Invalid duration second component") };
            }
#line 199 "/std/time/duration.do"
            (order = 4);
#line 200 "/std/time/duration.do"
            (multiplier = 1000000000LL);
        } else {
#line 202 "/std/time/duration.do"
            return doof::Failure<std::string>{ std::string("Invalid duration component designator") };
        }
#line 205 "/std/time/duration.do"
        if (order <= lastOrder) {
#line 206 "/std/time/duration.do"
            return doof::Failure<std::string>{ std::string("Duration components must be in ISO order") };
        }
#line 208 "/std/time/duration.do"
        (lastOrder = order);
#line 210 "/std/time/duration.do"
        (total = (total + (whole * multiplier)));
#line 211 "/std/time/duration.do"
        if (hasFraction) {
#line 212 "/std/time/duration.do"
            (total = (total + fractionNanos));
        }
#line 214 "/std/time/duration.do"
        (sawComponent = true);
    }
#line 217 "/std/time/duration.do"
    if (!sawComponent) {
#line 218 "/std/time/duration.do"
        return doof::Failure<std::string>{ std::string("Duration must contain at least one component") };
    }
#line 221 "/std/time/duration.do"
    return doof::Success<std::shared_ptr<Duration>>{ Duration::ofNanos((total * sign)) };
}
#line 224 "/std/time/duration.do"
bool isDigit(char32_t c) {
    return ((c >= U'\u0030') && (c <= U'\u0039'));
}
#line 226 "/std/time/duration.do"
int32_t digitValue(char32_t c) {
#line 227 "/std/time/duration.do"
    if (c == U'\u0030') {
#line 227 "/std/time/duration.do"
        return 0;
    }
#line 228 "/std/time/duration.do"
    if (c == U'\u0031') {
#line 228 "/std/time/duration.do"
        return 1;
    }
#line 229 "/std/time/duration.do"
    if (c == U'\u0032') {
#line 229 "/std/time/duration.do"
        return 2;
    }
#line 230 "/std/time/duration.do"
    if (c == U'\u0033') {
#line 230 "/std/time/duration.do"
        return 3;
    }
#line 231 "/std/time/duration.do"
    if (c == U'\u0034') {
#line 231 "/std/time/duration.do"
        return 4;
    }
#line 232 "/std/time/duration.do"
    if (c == U'\u0035') {
#line 232 "/std/time/duration.do"
        return 5;
    }
#line 233 "/std/time/duration.do"
    if (c == U'\u0036') {
#line 233 "/std/time/duration.do"
        return 6;
    }
#line 234 "/std/time/duration.do"
    if (c == U'\u0037') {
#line 234 "/std/time/duration.do"
        return 7;
    }
#line 235 "/std/time/duration.do"
    if (c == U'\u0038') {
#line 235 "/std/time/duration.do"
        return 8;
    }
#line 236 "/std/time/duration.do"
    return 9;
}

#line 242 "/std/time/duration.do"
void Thread::sleep(const std::shared_ptr<Duration>& duration) {
#line 243 "/std/time/duration.do"
    ::doof_time::thread_sleep_nanos(duration->toNanos());
}
#line 1 "<doof-generated>"

void __doof_initialize_module() {
        Duration::ZERO = std::make_shared<Duration>(0LL);
}
void _threadSleepNanos(int64_t nanos) {
    ::doof_time::thread_sleep_nanos(nanos);
}
}
