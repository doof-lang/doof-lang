#pragma once
#include "doof_runtime.hpp"
namespace std_::time::duration {
    struct Duration;
}

namespace std_::time::monotonic {
    struct MonotonicInstant;
}

namespace std_::time::stopwatch {
    struct TimerError;
    struct TimerStats;
    struct TimerSummary;
    struct TimerBucket;
    struct Stopwatch;
    struct StopwatchSpan;
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

namespace std_::time::stopwatch {
    struct TimerError : public std::enable_shared_from_this<TimerError> {
    std::string kind;
    std::string name;
    std::string message;
    TimerError(std::string kind, std::string name, std::string message) : kind(kind), name(name), message(message) {}
};
    struct TimerStats : public std::enable_shared_from_this<TimerStats> {
    std::string name;
    int32_t count;
    std::shared_ptr<::std_::time::duration::Duration> total;
    std::shared_ptr<::std_::time::duration::Duration> mean;
    std::shared_ptr<::std_::time::duration::Duration> min;
    std::shared_ptr<::std_::time::duration::Duration> max;
    std::shared_ptr<::std_::time::duration::Duration> p95;
    TimerStats(std::string name, int32_t count, std::shared_ptr<::std_::time::duration::Duration> total, std::shared_ptr<::std_::time::duration::Duration> mean, std::shared_ptr<::std_::time::duration::Duration> min, std::shared_ptr<::std_::time::duration::Duration> max, std::shared_ptr<::std_::time::duration::Duration> p95) : name(name), count(count), total(total), mean(mean), min(min), max(max), p95(p95) {}
};
    struct TimerSummary : public std::enable_shared_from_this<TimerSummary> {
    std::shared_ptr<std::vector<std::shared_ptr<TimerStats>>> entries;
    TimerSummary(std::shared_ptr<std::vector<std::shared_ptr<TimerStats>>> entries) : entries(entries) {}
};
    struct TimerBucket : public std::enable_shared_from_this<TimerBucket> {
    int32_t count;
    int64_t totalNanos;
    int64_t minNanos;
    int64_t maxNanos;
    std::shared_ptr<std::vector<int64_t>> durations;
    TimerBucket(int32_t count, int64_t totalNanos, int64_t minNanos, int64_t maxNanos, std::shared_ptr<std::vector<int64_t>> durations) : count(count), totalNanos(totalNanos), minNanos(minNanos), maxNanos(maxNanos), durations(durations) {}
    void record(const std::shared_ptr<::std_::time::duration::Duration>& duration);
    std::shared_ptr<::std_::time::duration::Duration> total();
    std::shared_ptr<::std_::time::duration::Duration> mean();
    std::shared_ptr<::std_::time::duration::Duration> min();
    std::shared_ptr<::std_::time::duration::Duration> max();
    std::shared_ptr<::std_::time::duration::Duration> p95();
    void insertSorted(int64_t nanos);
};
    struct Stopwatch : public std::enable_shared_from_this<Stopwatch> {
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>> timers;
    Stopwatch(std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>> timers) : timers(timers) {}
    std::shared_ptr<StopwatchSpan> measure(const std::string& name);
    int32_t count(const std::string& name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> total(const std::string& name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> mean(const std::string& name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> min(const std::string& name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> max(const std::string& name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> p95(const std::string& name);
    std::shared_ptr<TimerSummary> summary();
    void record(const std::string& name, const std::shared_ptr<::std_::time::duration::Duration>& duration);
    std::shared_ptr<TimerBucket> bucketFor(const std::string& name);
    doof::Result<std::shared_ptr<TimerBucket>, std::shared_ptr<TimerError>> requireBucket(const std::string& name);
};
    struct StopwatchSpan : public std::enable_shared_from_this<StopwatchSpan> {
    std::shared_ptr<Stopwatch> stopwatch;
    std::string name;
    std::shared_ptr<::std_::time::monotonic::MonotonicInstant> startedAt;
    bool finished;
    std::shared_ptr<::std_::time::duration::Duration> finishedDuration;
    StopwatchSpan(std::shared_ptr<Stopwatch> stopwatch, std::string name, std::shared_ptr<::std_::time::monotonic::MonotonicInstant> startedAt, bool finished, std::shared_ptr<::std_::time::duration::Duration> finishedDuration) : stopwatch(stopwatch), name(name), startedAt(startedAt), finished(finished), finishedDuration(finishedDuration) {}
    std::shared_ptr<::std_::time::duration::Duration> finish();
    ~StopwatchSpan();
};
}

namespace std_::time::stopwatch {
    std::shared_ptr<TimerError> missingTimer(const std::string& name);
}
