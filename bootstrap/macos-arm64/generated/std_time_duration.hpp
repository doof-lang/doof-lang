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
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::time::duration {
    struct Duration;
    struct Thread;
}

#include "doof_time.hpp"

namespace std_::time::duration {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    void _threadSleepNanos(int64_t nanos);
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
    static doof::Result<std::shared_ptr<Duration>, std::string> parse(std::string s);
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
    std::shared_ptr<Duration> plus(std::shared_ptr<Duration> other);
    std::shared_ptr<Duration> minus(std::shared_ptr<Duration> other);
    std::shared_ptr<Duration> multipliedBy(int64_t factor);
    std::shared_ptr<Duration> dividedBy(int64_t divisor);
    int32_t compareTo(std::shared_ptr<Duration> other);
    bool isLessThan(std::shared_ptr<Duration> other);
    bool isGreaterThan(std::shared_ptr<Duration> other);
    bool equals(std::shared_ptr<Duration> other);
    std::string toISOString();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Duration>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    // Utilities for the current operating-system thread.
struct Thread : public std::enable_shared_from_this<Thread> {
    Thread() {}
    static void sleep(std::shared_ptr<Duration> duration);
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Thread>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    doof::Result<std::shared_ptr<Duration>, std::string> parseDuration(std::string s);
    bool isDigit(char32_t c);
    int32_t digitValue(char32_t c);
}

namespace std_::time::duration {
}
