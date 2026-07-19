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
namespace std_::time::temporal { struct Instant; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::time::stopwatch {
    struct TimerError;
    struct TimerStats;
    struct TimerSummary;
    struct TimerBucket;
    struct Stopwatch;
    struct StopwatchSpan;
}

#include "std_time_duration.hpp"
#include "std_time_temporal.hpp"

namespace std_::time::stopwatch {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct TimerError : public std::enable_shared_from_this<TimerError> {
    std::string kind;
    std::string name;
    std::string message;
    TimerError(std::string kind, std::string name, std::string message) : kind(kind), name(name), message(message) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<TimerError>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<TimerStats>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct TimerSummary : public std::enable_shared_from_this<TimerSummary> {
    std::shared_ptr<std::vector<std::shared_ptr<TimerStats>>> entries;
    TimerSummary(std::shared_ptr<std::vector<std::shared_ptr<TimerStats>>> entries) : entries(entries) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<TimerSummary>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct TimerBucket : public std::enable_shared_from_this<TimerBucket> {
    int32_t count = 0;
    int64_t totalNanos = 0LL;
    int64_t minNanos = 0LL;
    int64_t maxNanos = 0LL;
    std::shared_ptr<std::vector<int64_t>> durations = std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{});
    TimerBucket(int32_t count = 0, int64_t totalNanos = 0LL, int64_t minNanos = 0LL, int64_t maxNanos = 0LL, std::shared_ptr<std::vector<int64_t>> durations = std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{})) : count(count), totalNanos(totalNanos), minNanos(minNanos), maxNanos(maxNanos), durations(durations) {}
    void record(std::shared_ptr<::std_::time::duration::Duration> duration);
    std::shared_ptr<::std_::time::duration::Duration> total();
    std::shared_ptr<::std_::time::duration::Duration> mean();
    std::shared_ptr<::std_::time::duration::Duration> min();
    std::shared_ptr<::std_::time::duration::Duration> max();
    std::shared_ptr<::std_::time::duration::Duration> p95();
    void insertSorted(int64_t nanos);
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<TimerBucket>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct Stopwatch : public std::enable_shared_from_this<Stopwatch> {
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>> timers = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<TimerBucket>>>{});
    Stopwatch(std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>> timers = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<TimerBucket>>>{})) : timers(timers) {}
    std::shared_ptr<StopwatchSpan> measure(std::string name);
    int32_t count(std::string name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> total(std::string name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> mean(std::string name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> min(std::string name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> max(std::string name);
    doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> p95(std::string name);
    std::shared_ptr<TimerSummary> summary();
    void record(std::string name, std::shared_ptr<::std_::time::duration::Duration> duration);
    std::shared_ptr<TimerBucket> bucketFor(std::string name);
    doof::Result<std::shared_ptr<TimerBucket>, std::shared_ptr<TimerError>> requireBucket(std::string name);
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Stopwatch>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct StopwatchSpan : public std::enable_shared_from_this<StopwatchSpan> {
    std::shared_ptr<Stopwatch> stopwatch;
    std::string name;
    std::shared_ptr<::std_::time::temporal::Instant> startedAt;
    bool finished = false;
    std::shared_ptr<::std_::time::duration::Duration> finishedDuration = nullptr;
    StopwatchSpan(std::shared_ptr<Stopwatch> stopwatch, std::string name, std::shared_ptr<::std_::time::temporal::Instant> startedAt, bool finished = false, std::shared_ptr<::std_::time::duration::Duration> finishedDuration = nullptr) : stopwatch(stopwatch), name(name), startedAt(startedAt), finished(finished), finishedDuration(finishedDuration) {}
    std::shared_ptr<::std_::time::duration::Duration> finish();
    ~StopwatchSpan() {
        this->finish();
    }
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<StopwatchSpan>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<TimerError> missingTimer(std::string name);
}

namespace std_::time::stopwatch {
}
