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
namespace std_::time::temporal { struct Instant; }
namespace std_::time::temporal { struct DateTime; }
namespace std_::time::temporal { struct TimeZone; }
namespace std_::time::temporal { struct ZonedDateTime; }
namespace std_::time::temporal { struct Date; }
namespace std_::time::temporal { struct Time; }
namespace std_::time::temporal { enum class DayOfWeek; }
namespace std_::time::duration { struct Duration; }
namespace std_::time::duration { struct Thread; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::time::temporal {
    struct Instant;
    struct Date;
    struct Time;
    struct DateTime;
    struct TimeZone;
    struct ZonedDateTime;
}

#include "std_time_duration.hpp"

namespace doof_time { using Instant = ::std_::time::temporal::Instant; }
namespace doof_time { using DateTime = ::std_::time::temporal::DateTime; }
namespace doof_time { using TimeZone = ::std_::time::temporal::TimeZone; }
namespace doof_time { using ZonedDateTime = ::std_::time::temporal::ZonedDateTime; }
namespace doof_time { using Date = ::std_::time::temporal::Date; }
namespace doof_time { using Time = ::std_::time::temporal::Time; }
namespace doof_time { using DayOfWeek = ::std_::time::temporal::DayOfWeek; }
namespace doof_time { using Duration = ::std_::time::duration::Duration; }
namespace doof_time { using Thread = ::std_::time::duration::Thread; }
#include "doof_time.hpp"

namespace std_::time::temporal {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
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
    enum class Month {
    January = 1,
    February = 2,
    March = 3,
    April = 4,
    May = 5,
    June = 6,
    July = 7,
    August = 8,
    September = 9,
    October = 10,
    November = 11,
    December = 12
};
inline const char* Month_name(Month value) {
  switch (value) {
    case Month::January: return "January";
    case Month::February: return "February";
    case Month::March: return "March";
    case Month::April: return "April";
    case Month::May: return "May";
    case Month::June: return "June";
    case Month::July: return "July";
    case Month::August: return "August";
    case Month::September: return "September";
    case Month::October: return "October";
    case Month::November: return "November";
    case Month::December: return "December";
  }
  return "";
}
inline std::optional<Month> Month_fromName(std::string_view value) {
  if (value == "January") return Month::January;
  if (value == "February") return Month::February;
  if (value == "March") return Month::March;
  if (value == "April") return Month::April;
  if (value == "May") return Month::May;
  if (value == "June") return Month::June;
  if (value == "July") return Month::July;
  if (value == "August") return Month::August;
  if (value == "September") return Month::September;
  if (value == "October") return Month::October;
  if (value == "November") return Month::November;
  if (value == "December") return Month::December;
  return std::nullopt;
}
inline std::optional<Month> Month_fromValue(int32_t value) {
  switch (static_cast<Month>(value)) {
    case Month::January: return Month::January;
    case Month::February: return Month::February;
    case Month::March: return Month::March;
    case Month::April: return Month::April;
    case Month::May: return Month::May;
    case Month::June: return Month::June;
    case Month::July: return Month::July;
    case Month::August: return Month::August;
    case Month::September: return Month::September;
    case Month::October: return Month::October;
    case Month::November: return Month::November;
    case Month::December: return Month::December;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, Month value) { return output << Month_name(value); }
    int64_t _systemNanosEpoch();
    doof::Result<std::shared_ptr<Instant>, std::string> _parseInstant(std::string s);
    std::shared_ptr<DateTime> _instantToDateTime(int64_t nanos);
    std::shared_ptr<ZonedDateTime> _instantToZonedDateTime(int64_t nanos, std::shared_ptr<TimeZone> zone);
    std::string _formatInstant(int64_t nanos);
    doof::Result<std::shared_ptr<Date>, std::string> _validateDate(int32_t year, int32_t month, int32_t day);
    std::shared_ptr<Date> _systemDateUTC();
    std::shared_ptr<Date> _systemDateInZone(std::shared_ptr<TimeZone> zone);
    doof::Result<std::shared_ptr<Date>, std::string> _parseDate(std::string s);
    DayOfWeek _dateToDayOfWeek(int32_t year, int32_t month, int32_t day);
    int32_t _dateToDayOfYear(int32_t year, int32_t month, int32_t day);
    bool _isLeapYear(int32_t year);
    int32_t _daysInMonth(int32_t year, int32_t month);
    std::shared_ptr<Date> _dateAddDays(int32_t year, int32_t month, int32_t day, int32_t n);
    std::shared_ptr<Date> _dateAddMonths(int32_t year, int32_t month, int32_t day, int32_t n);
    std::shared_ptr<Date> _dateAddYears(int32_t year, int32_t month, int32_t day, int32_t n);
    int32_t _dateDiff(int32_t y1, int32_t m1, int32_t d1, int32_t y2, int32_t m2, int32_t d2);
    doof::Result<std::shared_ptr<Time>, std::string> _validateTime(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond);
    doof::Result<std::shared_ptr<Time>, std::string> _parseTime(std::string s);
    std::shared_ptr<Time> _timeAddNanos(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond, int64_t nanos);
    doof::Result<std::shared_ptr<DateTime>, std::string> _parseDateTime(std::string s);
    std::shared_ptr<DateTime> _dateTimePlusNanos(std::shared_ptr<Date> date, std::shared_ptr<Time> time, int64_t nanos);
    std::shared_ptr<Instant> _dateTimeToInstant(std::shared_ptr<Date> date, std::shared_ptr<Time> time);
    std::shared_ptr<Instant> _dateTimeToInstantInZone(std::shared_ptr<Date> date, std::shared_ptr<Time> time, std::shared_ptr<TimeZone> zone);
    std::shared_ptr<ZonedDateTime> _dateTimeAtZone(std::shared_ptr<DateTime> dateTime, std::shared_ptr<TimeZone> zone);
    doof::Result<std::shared_ptr<TimeZone>, std::string> _lookupTimeZone(std::string id);
    std::shared_ptr<TimeZone> _systemTimeZone();
    int32_t _zoneOffsetAt(std::string id, int64_t epochSeconds);
    bool _zoneDSTAt(std::string id, int64_t epochSeconds);
    // A point in UTC time with nanosecond precision.
struct Instant : public std::enable_shared_from_this<Instant> {
    int64_t epochNanos;
    static std::shared_ptr<Instant> EPOCH;
    Instant(int64_t epochNanos) : epochNanos(epochNanos) {}
    static std::shared_ptr<Instant> now();
    static std::shared_ptr<Instant> ofEpochNanos(int64_t nanos);
    static std::shared_ptr<Instant> ofEpochMillis(int64_t ms);
    static std::shared_ptr<Instant> ofEpochSeconds(int64_t s);
    static doof::Result<std::shared_ptr<Instant>, std::string> parse(std::string s);
    int64_t toEpochNanos();
    int64_t toEpochMillis();
    int64_t toEpochSeconds();
    std::shared_ptr<Instant> plus(std::shared_ptr<::std_::time::duration::Duration> d);
    std::shared_ptr<Instant> minus(std::shared_ptr<::std_::time::duration::Duration> d);
    std::shared_ptr<::std_::time::duration::Duration> durationUntil(std::shared_ptr<Instant> other);
    std::shared_ptr<::std_::time::duration::Duration> durationSince(std::shared_ptr<Instant> other);
    int32_t compareTo(std::shared_ptr<Instant> other);
    bool isBefore(std::shared_ptr<Instant> other);
    bool isAfter(std::shared_ptr<Instant> other);
    bool equals(std::shared_ptr<Instant> other);
    std::shared_ptr<DateTime> toDateTime();
    std::shared_ptr<ZonedDateTime> toZonedDateTime(std::shared_ptr<TimeZone> zone);
    std::string toISOString();
    static doof::Result<std::shared_ptr<Instant>, std::string> parseHttpDate(std::string s);
    std::string toHttpDate();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Instant>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    static std::shared_ptr<Date> today(std::shared_ptr<TimeZone> zone);
    static doof::Result<std::shared_ptr<Date>, std::string> parse(std::string s);
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
    int32_t daysUntil(std::shared_ptr<Date> other);
    int32_t compareTo(std::shared_ptr<Date> other);
    bool isBefore(std::shared_ptr<Date> other);
    bool isAfter(std::shared_ptr<Date> other);
    bool equals(std::shared_ptr<Date> other);
    std::string toISOString();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Date>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    static doof::Result<std::shared_ptr<Time>, std::string> parse(std::string s);
    std::shared_ptr<Time> plusHours(int32_t n);
    std::shared_ptr<Time> plusMinutes(int32_t n);
    std::shared_ptr<Time> plusSeconds(int32_t n);
    std::shared_ptr<Time> plusNanos(int64_t n);
    int32_t compareTo(std::shared_ptr<Time> other);
    bool isBefore(std::shared_ptr<Time> other);
    bool isAfter(std::shared_ptr<Time> other);
    bool equals(std::shared_ptr<Time> other);
    std::string toISOString();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Time>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    // A combined calendar date and time-of-day. No timezone.
struct DateTime : public std::enable_shared_from_this<DateTime> {
    std::shared_ptr<Date> date;
    std::shared_ptr<Time> time;
    DateTime(std::shared_ptr<Date> date, std::shared_ptr<Time> time) : date(date), time(time) {}
    static std::shared_ptr<DateTime> create(std::shared_ptr<Date> date, std::shared_ptr<Time> time);
    static doof::Result<std::shared_ptr<DateTime>, std::string> fromParts(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second = 0, int32_t nanosecond = 0);
    static std::shared_ptr<DateTime> nowUTC();
    static doof::Result<std::shared_ptr<DateTime>, std::string> parse(std::string s);
    std::shared_ptr<DateTime> plusDays(int32_t n);
    std::shared_ptr<DateTime> minusDays(int32_t n);
    std::shared_ptr<DateTime> plusHours(int32_t n);
    std::shared_ptr<DateTime> plusMinutes(int32_t n);
    std::shared_ptr<DateTime> plusSeconds(int32_t n);
    std::shared_ptr<DateTime> plus(std::shared_ptr<::std_::time::duration::Duration> d);
    std::shared_ptr<DateTime> minus(std::shared_ptr<::std_::time::duration::Duration> d);
    std::shared_ptr<Instant> toInstantUTC();
    std::shared_ptr<Instant> toInstant(std::shared_ptr<TimeZone> zone);
    std::shared_ptr<ZonedDateTime> atZone(std::shared_ptr<TimeZone> zone);
    int32_t compareTo(std::shared_ptr<DateTime> other);
    bool isBefore(std::shared_ptr<DateTime> other);
    bool isAfter(std::shared_ptr<DateTime> other);
    bool equals(std::shared_ptr<DateTime> other);
    std::string toISOString();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DateTime>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    // An IANA timezone identifier (e.g. "America/New_York", "UTC").
struct TimeZone : public std::enable_shared_from_this<TimeZone> {
    std::string id;
    static std::shared_ptr<TimeZone> UTC;
    TimeZone(std::string id) : id(id) {}
    static doof::Result<std::shared_ptr<TimeZone>, std::string> lookup(std::string id);
    static std::shared_ptr<TimeZone> local();
    int32_t offsetSecondsAt(std::shared_ptr<Instant> instant);
    bool isDSTAt(std::shared_ptr<Instant> instant);
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<TimeZone>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    // A DateTime with an explicit TimeZone.
struct ZonedDateTime : public std::enable_shared_from_this<ZonedDateTime> {
    std::shared_ptr<DateTime> dateTime;
    std::shared_ptr<TimeZone> zone;
    ZonedDateTime(std::shared_ptr<DateTime> dateTime, std::shared_ptr<TimeZone> zone) : dateTime(dateTime), zone(zone) {}
    static std::shared_ptr<ZonedDateTime> now(std::shared_ptr<TimeZone> zone);
    static std::shared_ptr<ZonedDateTime> nowUTC();
    std::shared_ptr<Date> date();
    std::shared_ptr<Time> time();
    int32_t offsetSeconds();
    std::shared_ptr<Instant> toInstant();
    std::shared_ptr<ZonedDateTime> withZoneSameInstant(std::shared_ptr<TimeZone> newZone);
    std::shared_ptr<ZonedDateTime> withZoneSameLocal(std::shared_ptr<TimeZone> newZone);
    std::shared_ptr<DateTime> toDateTime();
    std::shared_ptr<ZonedDateTime> toUTC();
    int32_t compareTo(std::shared_ptr<ZonedDateTime> other);
    bool isBefore(std::shared_ptr<ZonedDateTime> other);
    bool isAfter(std::shared_ptr<ZonedDateTime> other);
    std::string toISOString();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ZonedDateTime>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string httpWeekdayName(DayOfWeek day);
    std::string httpMonthName(int32_t month);
    std::optional<int32_t> httpMonthNumber(std::string text);
}

namespace std_::time::temporal {
}
