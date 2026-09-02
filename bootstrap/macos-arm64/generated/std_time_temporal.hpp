#pragma once
#include "doof_runtime.hpp"
namespace std_::parse::types { enum class ParsingError; }
namespace std_::time::temporal { struct Instant; }
namespace std_::time::temporal { struct DateTime; }
namespace std_::time::temporal { struct TimeZone; }
namespace std_::time::temporal { struct ZonedDateTime; }
namespace std_::time::temporal { struct Date; }
namespace std_::time::temporal { struct Time; }
namespace std_::time::temporal { enum class DayOfWeek; }
namespace std_::time::temporal { enum class Month; }
namespace std_::time::duration { struct Duration; }

namespace std_::time::duration {
    struct Duration;
}

namespace std_::parse::index {
}

namespace std_::time::temporal {
    struct Instant;
    struct Date;
    struct Time;
    struct DateTime;
    struct TimeZone;
    struct ZonedDateTime;
}

namespace std_::parse::types {
    enum class ParsingError {
    InvalidFormat = 0,
    Overflow = 1,
    Underflow = 2,
    EmptyInput = 3,
    InvalidRadix = 4,
    NonFinite = 5
};
inline const char* ParsingError_name(ParsingError value) {
  switch (value) {
    case ParsingError::InvalidFormat: return "InvalidFormat";
    case ParsingError::Overflow: return "Overflow";
    case ParsingError::Underflow: return "Underflow";
    case ParsingError::EmptyInput: return "EmptyInput";
    case ParsingError::InvalidRadix: return "InvalidRadix";
    case ParsingError::NonFinite: return "NonFinite";
  }
  doof::panic(std::string("Invalid ParsingError enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<ParsingError> ParsingError_fromName(std::string_view value) {
  if (value == "InvalidFormat") return ParsingError::InvalidFormat;
  if (value == "Overflow") return ParsingError::Overflow;
  if (value == "Underflow") return ParsingError::Underflow;
  if (value == "EmptyInput") return ParsingError::EmptyInput;
  if (value == "InvalidRadix") return ParsingError::InvalidRadix;
  if (value == "NonFinite") return ParsingError::NonFinite;
  return std::nullopt;
}
inline int32_t ParsingError_value(ParsingError value) { return static_cast<int32_t>(value); }
inline std::optional<ParsingError> ParsingError_fromValue(int32_t value) {
  if (value == 0) return ParsingError::InvalidFormat;
  if (value == 1) return ParsingError::Overflow;
  if (value == 2) return ParsingError::Underflow;
  if (value == 3) return ParsingError::EmptyInput;
  if (value == 4) return ParsingError::InvalidRadix;
  if (value == 5) return ParsingError::NonFinite;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<ParsingError>> ParsingError_values() { return std::make_shared<std::vector<ParsingError>>(std::initializer_list<ParsingError>{ParsingError::InvalidFormat, ParsingError::Overflow, ParsingError::Underflow, ParsingError::EmptyInput, ParsingError::InvalidRadix, ParsingError::NonFinite}); }
inline doof::JsonValue ParsingError_toJsonValue(ParsingError value) { return doof::json_value(ParsingError_value(value)); }
inline doof::Result<ParsingError, std::string> ParsingError_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum ParsingError, got ") + doof::json_type_name(value)};
  auto resolved = ParsingError_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum ParsingError: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2, 3, 4, 5"};
  return doof::Success<ParsingError>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, ParsingError value) { return output << ParsingError_name(value); }
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
  doof::panic(std::string("Invalid DayOfWeek enum value: ") + doof::to_string(static_cast<int32_t>(value)));
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
inline int32_t DayOfWeek_value(DayOfWeek value) { return static_cast<int32_t>(value); }
inline std::optional<DayOfWeek> DayOfWeek_fromValue(int32_t value) {
  if (value == 1) return DayOfWeek::Monday;
  if (value == 2) return DayOfWeek::Tuesday;
  if (value == 3) return DayOfWeek::Wednesday;
  if (value == 4) return DayOfWeek::Thursday;
  if (value == 5) return DayOfWeek::Friday;
  if (value == 6) return DayOfWeek::Saturday;
  if (value == 7) return DayOfWeek::Sunday;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<DayOfWeek>> DayOfWeek_values() { return std::make_shared<std::vector<DayOfWeek>>(std::initializer_list<DayOfWeek>{DayOfWeek::Monday, DayOfWeek::Tuesday, DayOfWeek::Wednesday, DayOfWeek::Thursday, DayOfWeek::Friday, DayOfWeek::Saturday, DayOfWeek::Sunday}); }
inline doof::JsonValue DayOfWeek_toJsonValue(DayOfWeek value) { return doof::json_value(DayOfWeek_value(value)); }
inline doof::Result<DayOfWeek, std::string> DayOfWeek_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum DayOfWeek, got ") + doof::json_type_name(value)};
  auto resolved = DayOfWeek_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum DayOfWeek: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 1, 2, 3, 4, 5, 6, 7"};
  return doof::Success<DayOfWeek>{resolved.value()};
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
  doof::panic(std::string("Invalid Month enum value: ") + doof::to_string(static_cast<int32_t>(value)));
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
inline int32_t Month_value(Month value) { return static_cast<int32_t>(value); }
inline std::optional<Month> Month_fromValue(int32_t value) {
  if (value == 1) return Month::January;
  if (value == 2) return Month::February;
  if (value == 3) return Month::March;
  if (value == 4) return Month::April;
  if (value == 5) return Month::May;
  if (value == 6) return Month::June;
  if (value == 7) return Month::July;
  if (value == 8) return Month::August;
  if (value == 9) return Month::September;
  if (value == 10) return Month::October;
  if (value == 11) return Month::November;
  if (value == 12) return Month::December;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<Month>> Month_values() { return std::make_shared<std::vector<Month>>(std::initializer_list<Month>{Month::January, Month::February, Month::March, Month::April, Month::May, Month::June, Month::July, Month::August, Month::September, Month::October, Month::November, Month::December}); }
inline doof::JsonValue Month_toJsonValue(Month value) { return doof::json_value(Month_value(value)); }
inline doof::Result<Month, std::string> Month_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum Month, got ") + doof::json_type_name(value)};
  auto resolved = Month_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum Month: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12"};
  return doof::Success<Month>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, Month value) { return output << Month_name(value); }
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
    static doof::Result<std::shared_ptr<Time>, std::string> create(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond);
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
    static doof::Result<std::shared_ptr<DateTime>, std::string> fromParts(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, int32_t nanosecond);
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

namespace doof_parse { using ParsingError = ::std_::parse::types::ParsingError; }
#include "native_parse.hpp"

namespace doof_time { using Instant = ::std_::time::temporal::Instant; }
namespace doof_time { using DateTime = ::std_::time::temporal::DateTime; }
namespace doof_time { using TimeZone = ::std_::time::temporal::TimeZone; }
namespace doof_time { using ZonedDateTime = ::std_::time::temporal::ZonedDateTime; }
namespace doof_time { using Date = ::std_::time::temporal::Date; }
namespace doof_time { using Time = ::std_::time::temporal::Time; }
namespace doof_time { using DayOfWeek = ::std_::time::temporal::DayOfWeek; }
namespace doof_time { using Month = ::std_::time::temporal::Month; }
namespace doof_time { using Duration = ::std_::time::duration::Duration; }
#include "doof_time.hpp"

namespace std_::time::temporal {
    std::string httpWeekdayName(DayOfWeek day);
    std::string httpMonthName(int32_t month);
    std::optional<int32_t> httpMonthNumber(const std::string& text);
}
