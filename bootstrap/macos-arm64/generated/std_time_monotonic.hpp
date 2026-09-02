#pragma once
#include "doof_runtime.hpp"
namespace std_::time::monotonic { struct MonotonicInstant; }
namespace std_::time::duration { struct Duration; }

namespace std_::time::duration {
    struct Duration;
}

namespace std_::time::monotonic {
    struct MonotonicInstant;
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

namespace std_::time::monotonic {
    // A process-local time point from a monotonic clock.
struct MonotonicInstant : public std::enable_shared_from_this<MonotonicInstant> {
    int64_t ticksNanos;
    MonotonicInstant(int64_t ticksNanos) : ticksNanos(ticksNanos) {}
    static std::shared_ptr<MonotonicInstant> now();
    std::shared_ptr<MonotonicInstant> plus(const std::shared_ptr<::std_::time::duration::Duration>& duration);
    std::shared_ptr<MonotonicInstant> minus(const std::shared_ptr<::std_::time::duration::Duration>& duration);
    std::shared_ptr<::std_::time::duration::Duration> durationUntil(const std::shared_ptr<MonotonicInstant>& other);
    std::shared_ptr<::std_::time::duration::Duration> durationSince(const std::shared_ptr<MonotonicInstant>& other);
    int32_t compareTo(const std::shared_ptr<MonotonicInstant>& other);
    bool isBefore(const std::shared_ptr<MonotonicInstant>& other);
    bool isAfter(const std::shared_ptr<MonotonicInstant>& other);
    bool equals(const std::shared_ptr<MonotonicInstant>& other);
};
}

namespace doof_time { using MonotonicInstant = ::std_::time::monotonic::MonotonicInstant; }
namespace doof_time { using Duration = ::std_::time::duration::Duration; }
#include "doof_time.hpp"
