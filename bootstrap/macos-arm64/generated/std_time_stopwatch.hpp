#pragma once
#include "doof_runtime.hpp"
namespace std_::time::duration {
    struct Duration;
}

namespace std_::time::temporal {
    struct Instant;
    struct Date;
    struct Time;
    struct DateTime;
    struct TimeZone;
    struct ZonedDateTime;
}

namespace std_::time::stopwatch {
    struct TimerError;
    struct TimerStats;
    struct TimerSummary;
    struct TimerBucket;
    struct Stopwatch;
    struct StopwatchSpan;
}

namespace std_::time::temporal {
    enum class DayOfWeek {
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
    Sunday = 7
};
inline const char* DayOfWeek_name(DayOfWeek value) {
  switch (value) {
    case DayOfWeek::Monday: return "Monday";
    case DayOfWeek::Tuesday: return "Tuesday";
    case DayOfWeek::Wednesday: return "Wednesday";
    case DayOfWeek::Thursday: return "Thursday";
    case DayOfWeek::Friday: return "Friday";
    case DayOfWeek::Saturday: return "Saturday";
    case DayOfWeek::Sunday: return "Sunday";
  }
  return "";
}
inline std::optional<DayOfWeek> DayOfWeek_fromName(std::string_view value) {
  if (value == "Monday") return DayOfWeek::Monday;
  if (value == "Tuesday") return DayOfWeek::Tuesday;
  if (value == "Wednesday") return DayOfWeek::Wednesday;
  if (value == "Thursday") return DayOfWeek::Thursday;
  if (value == "Friday") return DayOfWeek::Friday;
  if (value == "Saturday") return DayOfWeek::Saturday;
  if (value == "Sunday") return DayOfWeek::Sunday;
  return std::nullopt;
}
inline std::optional<DayOfWeek> DayOfWeek_fromValue(int32_t value) {
  switch (static_cast<DayOfWeek>(value)) {
    case DayOfWeek::Monday: return DayOfWeek::Monday;
    case DayOfWeek::Tuesday: return DayOfWeek::Tuesday;
    case DayOfWeek::Wednesday: return DayOfWeek::Wednesday;
    case DayOfWeek::Thursday: return DayOfWeek::Thursday;
    case DayOfWeek::Friday: return DayOfWeek::Friday;
    case DayOfWeek::Saturday: return DayOfWeek::Saturday;
    case DayOfWeek::Sunday: return DayOfWeek::Sunday;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, DayOfWeek value) { return output << DayOfWeek_name(value); }
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

namespace std_::time::temporal {
    // A point in UTC time with nanosecond precision.
struct Instant : public std::enable_shared_from_this<Instant> {
    int64_t epochNanos;
    static std::shared_ptr<Instant> EPOCH;
    Instant(int64_t epochNanos) : epochNanos(epochNanos) {}
    static std::shared_ptr<Instant> now();
    static std::shared_ptr<Instant> ofEpochNanos(int64_t nanos);
    static std::shared_ptr<Instant> ofEpochMillis(int64_t ms);
    static std::shared_ptr<Instant> ofEpochSeconds(int64_t s);
    static doof::Result<std::shared_ptr<Instant>, std::string> parse(const std::string& s);
    int64_t toEpochNanos();
    int64_t toEpochMillis();
    int64_t toEpochSeconds();
    std::shared_ptr<Instant> plus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<Instant> minus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<::std_::time::duration::Duration> durationUntil(const std::shared_ptr<Instant>& other);
    std::shared_ptr<::std_::time::duration::Duration> durationSince(const std::shared_ptr<Instant>& other);
    int32_t compareTo(const std::shared_ptr<Instant>& other);
    bool isBefore(const std::shared_ptr<Instant>& other);
    bool isAfter(const std::shared_ptr<Instant>& other);
    bool equals(const std::shared_ptr<Instant>& other);
    std::shared_ptr<DateTime> toDateTime();
    std::shared_ptr<ZonedDateTime> toZonedDateTime(const std::shared_ptr<TimeZone>& zone);
    std::string toISOString();
    static doof::Result<std::shared_ptr<Instant>, std::string> parseHttpDate(const std::string& s);
    std::string toHttpDate();
};
    // A calendar date (year, month, day) with no time-of-day or timezone.
struct Date : public std::enable_shared_from_this<Date> {
    int32_t year;
    int32_t month;
    int32_t day;
    static std::shared_ptr<Date> MIN;
    static std::shared_ptr<Date> MAX;
    Date(int32_t year, int32_t month, int32_t day) : year(year), month(month), day(day) {}
    static doof::Result<std::shared_ptr<Date>, std::string> create(int32_t year, int32_t month, int32_t day);
    static std::shared_ptr<Date> todayUTC();
    static std::shared_ptr<Date> today(const std::shared_ptr<TimeZone>& zone);
    static doof::Result<std::shared_ptr<Date>, std::string> parse(const std::string& s);
    DayOfWeek dayOfWeek();
    int32_t dayOfYear();
    bool isLeapYear();
    int32_t daysInMonth();
    std::shared_ptr<Date> plusDays(int32_t n);
    std::shared_ptr<Date> minusDays(int32_t n);
    std::shared_ptr<Date> plusMonths(int32_t n);
    std::shared_ptr<Date> minusMonths(int32_t n);
    std::shared_ptr<Date> plusYears(int32_t n);
    std::shared_ptr<Date> minusYears(int32_t n);
    int32_t daysUntil(const std::shared_ptr<Date>& other);
    int32_t compareTo(const std::shared_ptr<Date>& other);
    bool isBefore(const std::shared_ptr<Date>& other);
    bool isAfter(const std::shared_ptr<Date>& other);
    bool equals(const std::shared_ptr<Date>& other);
    std::string toISOString();
};
    // A time-of-day with nanosecond precision. No date or timezone.
struct Time : public std::enable_shared_from_this<Time> {
    int32_t hour;
    int32_t minute;
    int32_t second;
    int32_t nanosecond;
    static std::shared_ptr<Time> MIDNIGHT;
    static std::shared_ptr<Time> NOON;
    Time(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond) : hour(hour), minute(minute), second(second), nanosecond(nanosecond) {}
    static doof::Result<std::shared_ptr<Time>, std::string> create(int32_t hour, int32_t minute, int32_t second = 0, int32_t nanosecond = 0);
    static doof::Result<std::shared_ptr<Time>, std::string> parse(const std::string& s);
    std::shared_ptr<Time> plusHours(int32_t n);
    std::shared_ptr<Time> plusMinutes(int32_t n);
    std::shared_ptr<Time> plusSeconds(int32_t n);
    std::shared_ptr<Time> plusNanos(int64_t n);
    int32_t compareTo(const std::shared_ptr<Time>& other);
    bool isBefore(const std::shared_ptr<Time>& other);
    bool isAfter(const std::shared_ptr<Time>& other);
    bool equals(const std::shared_ptr<Time>& other);
    std::string toISOString();
};
    // A combined calendar date and time-of-day. No timezone.
struct DateTime : public std::enable_shared_from_this<DateTime> {
    std::shared_ptr<Date> date;
    std::shared_ptr<Time> time;
    DateTime(std::shared_ptr<Date> date, std::shared_ptr<Time> time) : date(date), time(time) {}
    static std::shared_ptr<DateTime> create(const std::shared_ptr<Date>& date, const std::shared_ptr<Time>& time);
    static doof::Result<std::shared_ptr<DateTime>, std::string> fromParts(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second = 0, int32_t nanosecond = 0);
    static std::shared_ptr<DateTime> nowUTC();
    static doof::Result<std::shared_ptr<DateTime>, std::string> parse(const std::string& s);
    std::shared_ptr<DateTime> plusDays(int32_t n);
    std::shared_ptr<DateTime> minusDays(int32_t n);
    std::shared_ptr<DateTime> plusHours(int32_t n);
    std::shared_ptr<DateTime> plusMinutes(int32_t n);
    std::shared_ptr<DateTime> plusSeconds(int32_t n);
    std::shared_ptr<DateTime> plus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<DateTime> minus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<Instant> toInstantUTC();
    std::shared_ptr<Instant> toInstant(const std::shared_ptr<TimeZone>& zone);
    std::shared_ptr<ZonedDateTime> atZone(const std::shared_ptr<TimeZone>& zone);
    int32_t compareTo(const std::shared_ptr<DateTime>& other);
    bool isBefore(const std::shared_ptr<DateTime>& other);
    bool isAfter(const std::shared_ptr<DateTime>& other);
    bool equals(const std::shared_ptr<DateTime>& other);
    std::string toISOString();
};
    // An IANA timezone identifier (e.g. "America/New_York", "UTC").
struct TimeZone : public std::enable_shared_from_this<TimeZone> {
    std::string id;
    static std::shared_ptr<TimeZone> UTC;
    TimeZone(std::string id) : id(id) {}
    static doof::Result<std::shared_ptr<TimeZone>, std::string> lookup(const std::string& id);
    static std::shared_ptr<TimeZone> local();
    int32_t offsetSecondsAt(const std::shared_ptr<Instant>& instant);
    bool isDSTAt(const std::shared_ptr<Instant>& instant);
};
    // A DateTime with an explicit TimeZone.
struct ZonedDateTime : public std::enable_shared_from_this<ZonedDateTime> {
    std::shared_ptr<DateTime> dateTime;
    std::shared_ptr<TimeZone> zone;
    ZonedDateTime(std::shared_ptr<DateTime> dateTime, std::shared_ptr<TimeZone> zone) : dateTime(dateTime), zone(zone) {}
    static std::shared_ptr<ZonedDateTime> now(const std::shared_ptr<TimeZone>& zone);
    static std::shared_ptr<ZonedDateTime> nowUTC();
    std::shared_ptr<Date> date();
    std::shared_ptr<Time> time();
    int32_t offsetSeconds();
    std::shared_ptr<Instant> toInstant();
    std::shared_ptr<ZonedDateTime> withZoneSameInstant(const std::shared_ptr<TimeZone>& newZone);
    std::shared_ptr<ZonedDateTime> withZoneSameLocal(const std::shared_ptr<TimeZone>& newZone);
    std::shared_ptr<DateTime> toDateTime();
    std::shared_ptr<ZonedDateTime> toUTC();
    int32_t compareTo(const std::shared_ptr<ZonedDateTime>& other);
    bool isBefore(const std::shared_ptr<ZonedDateTime>& other);
    bool isAfter(const std::shared_ptr<ZonedDateTime>& other);
    std::string toISOString();
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
    int32_t count = 0;
    int64_t totalNanos = 0LL;
    int64_t minNanos = 0LL;
    int64_t maxNanos = 0LL;
    std::shared_ptr<std::vector<int64_t>> durations = std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{});
    TimerBucket(int32_t count = 0, int64_t totalNanos = 0LL, int64_t minNanos = 0LL, int64_t maxNanos = 0LL, std::shared_ptr<std::vector<int64_t>> durations = std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{})) : count(count), totalNanos(totalNanos), minNanos(minNanos), maxNanos(maxNanos), durations(durations) {}
    void record(const std::shared_ptr<::std_::time::duration::Duration>& duration);
    std::shared_ptr<::std_::time::duration::Duration> total();
    std::shared_ptr<::std_::time::duration::Duration> mean();
    std::shared_ptr<::std_::time::duration::Duration> min();
    std::shared_ptr<::std_::time::duration::Duration> max();
    std::shared_ptr<::std_::time::duration::Duration> p95();
    void insertSorted(int64_t nanos);
};
    struct Stopwatch : public std::enable_shared_from_this<Stopwatch> {
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>> timers = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<TimerBucket>>>{});
    Stopwatch(std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>> timers = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<TimerBucket>>>{})) : timers(timers) {}
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
    std::shared_ptr<::std_::time::temporal::Instant> startedAt;
    bool finished = false;
    std::shared_ptr<::std_::time::duration::Duration> finishedDuration = nullptr;
    StopwatchSpan(std::shared_ptr<Stopwatch> stopwatch, std::string name, std::shared_ptr<::std_::time::temporal::Instant> startedAt, bool finished = false, std::shared_ptr<::std_::time::duration::Duration> finishedDuration = nullptr) : stopwatch(stopwatch), name(name), startedAt(startedAt), finished(finished), finishedDuration(finishedDuration) {}
    std::shared_ptr<::std_::time::duration::Duration> finish();
    ~StopwatchSpan() {
        this->finish();
    }
};
}

namespace std_::time::stopwatch {
    std::shared_ptr<TimerError> missingTimer(const std::string& name);
}
