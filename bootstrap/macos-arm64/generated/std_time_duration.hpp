#pragma once
#include "doof_runtime.hpp"
namespace std_::time::duration { struct Duration; }
namespace std_::time::duration { struct Thread; }

namespace std_::time::duration {
    struct Duration;
    struct Thread;
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Duration>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    // Utilities for the current operating-system thread.
struct Thread : public std::enable_shared_from_this<Thread> {
    Thread() {}
    static void sleep(const std::shared_ptr<Duration>& duration);
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Thread>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace doof_time { using Duration = ::std_::time::duration::Duration; }
namespace doof_time { using Thread = ::std_::time::duration::Thread; }
#include "doof_time.hpp"

namespace std_::time::duration {
    void _threadSleepNanos(int64_t nanos);
    doof::Result<std::shared_ptr<Duration>, std::string> parseDuration(const std::string& s);
    bool isDigit(char32_t c);
    int32_t digitValue(char32_t c);
}
