#include "std_time_temporal.hpp"
#include <cmath>
#include "std_time_duration.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::time::temporal {
using namespace ::std_::time::duration;

std::shared_ptr<Instant> Instant::EPOCH = std::make_shared<Instant>(0LL);
std::shared_ptr<Instant> Instant::now() {
    return std::make_shared<Instant>(_systemNanosEpoch());
}
std::shared_ptr<Instant> Instant::ofEpochNanos(int64_t nanos) {
    return std::make_shared<Instant>(nanos);
}
std::shared_ptr<Instant> Instant::ofEpochMillis(int64_t ms) {
    return std::make_shared<Instant>((ms * 1000000LL));
}
std::shared_ptr<Instant> Instant::ofEpochSeconds(int64_t s) {
    return std::make_shared<Instant>((s * 1000000000LL));
}
doof::Result<std::shared_ptr<Instant>, std::string> Instant::parse(std::string s) {
    return _parseInstant(s);
}
int64_t Instant::toEpochNanos() {
    return this->epochNanos;
}
int64_t Instant::toEpochMillis() {
    return (this->epochNanos / 1000000LL);
}
int64_t Instant::toEpochSeconds() {
    return (this->epochNanos / 1000000000LL);
}
std::shared_ptr<Instant> Instant::plus(std::shared_ptr<::std_::time::duration::Duration> d) {
    return std::make_shared<Instant>((this->epochNanos + d->toNanos()));
}
std::shared_ptr<Instant> Instant::minus(std::shared_ptr<::std_::time::duration::Duration> d) {
    return std::make_shared<Instant>((this->epochNanos - d->toNanos()));
}
std::shared_ptr<::std_::time::duration::Duration> Instant::durationUntil(std::shared_ptr<Instant> other) {
    return ::std_::time::duration::Duration::ofNanos((other->epochNanos - this->epochNanos));
}
std::shared_ptr<::std_::time::duration::Duration> Instant::durationSince(std::shared_ptr<Instant> other) {
    return ::std_::time::duration::Duration::ofNanos((this->epochNanos - other->epochNanos));
}
int32_t Instant::compareTo(std::shared_ptr<Instant> other) {
    if (this->epochNanos < other->epochNanos) {
        return -1;
    }
    if (this->epochNanos > other->epochNanos) {
        return 1;
    }
    return 0;
}
bool Instant::isBefore(std::shared_ptr<Instant> other) {
    return (this->epochNanos < other->epochNanos);
}
bool Instant::isAfter(std::shared_ptr<Instant> other) {
    return (this->epochNanos > other->epochNanos);
}
bool Instant::equals(std::shared_ptr<Instant> other) {
    return (this->epochNanos == other->epochNanos);
}
std::shared_ptr<DateTime> Instant::toDateTime() {
    return _instantToDateTime(this->epochNanos);
}
std::shared_ptr<ZonedDateTime> Instant::toZonedDateTime(std::shared_ptr<TimeZone> zone) {
    return _instantToZonedDateTime(this->epochNanos, zone);
}
std::string Instant::toISOString() {
    return _formatInstant(this->epochNanos);
}
doof::Result<std::shared_ptr<Instant>, std::string> Instant::parseHttpDate(std::string s) {
    if (static_cast<int32_t>(s.size()) != 29) {
        return doof::Failure<std::string>{ std::string("HTTP date must use IMF-fixdate format") };
    }
    if (((((((doof::string_substring(s, 3, 5) != std::string(", ")) || (doof::string_at(s, 7, "", 0) != U'\u0020')) || (doof::string_at(s, 11, "", 0) != U'\u0020')) || (doof::string_at(s, 16, "", 0) != U'\u0020')) || (doof::string_at(s, 19, "", 0) != U'\u003A')) || (doof::string_at(s, 22, "", 0) != U'\u003A')) || (doof::string_slice(s, 25) != std::string(" GMT"))) {
        return doof::Failure<std::string>{ std::string("HTTP date must use IMF-fixdate format") };
    }
    auto _binding_value_1 = [&]() -> std::optional<int32_t> { auto _try_value = doof::parse_int(doof::string_substring(s, 5, 7)); if (doof::is_failure(_try_value)) doof::panic("try? failed"); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_1)) {
        const auto& day = _binding_value_1;
        return doof::Failure<std::string>{ std::string("HTTP date day is invalid") };
    }
    const auto day = doof::unwrap_optional(_binding_value_1);
    auto _binding_value_2 = httpMonthNumber(doof::string_substring(s, 8, 11));
    if (doof::is_null(_binding_value_2)) {
        const auto& month = _binding_value_2;
        return doof::Failure<std::string>{ std::string("HTTP date month is invalid") };
    }
    const auto month = doof::unwrap_optional(_binding_value_2);
    auto _binding_value_3 = [&]() -> std::optional<int32_t> { auto _try_value = doof::parse_int(doof::string_substring(s, 12, 16)); if (doof::is_failure(_try_value)) doof::panic("try? failed"); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_3)) {
        const auto& year = _binding_value_3;
        return doof::Failure<std::string>{ std::string("HTTP date year is invalid") };
    }
    const auto year = doof::unwrap_optional(_binding_value_3);
    auto _binding_value_4 = [&]() -> std::optional<int32_t> { auto _try_value = doof::parse_int(doof::string_substring(s, 17, 19)); if (doof::is_failure(_try_value)) doof::panic("try? failed"); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_4)) {
        const auto& hour = _binding_value_4;
        return doof::Failure<std::string>{ std::string("HTTP date hour is invalid") };
    }
    const auto hour = doof::unwrap_optional(_binding_value_4);
    auto _binding_value_5 = [&]() -> std::optional<int32_t> { auto _try_value = doof::parse_int(doof::string_substring(s, 20, 22)); if (doof::is_failure(_try_value)) doof::panic("try? failed"); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_5)) {
        const auto& minute = _binding_value_5;
        return doof::Failure<std::string>{ std::string("HTTP date minute is invalid") };
    }
    const auto minute = doof::unwrap_optional(_binding_value_5);
    auto _binding_value_6 = [&]() -> std::optional<int32_t> { auto _try_value = doof::parse_int(doof::string_substring(s, 23, 25)); if (doof::is_failure(_try_value)) doof::panic("try? failed"); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_6)) {
        const auto& second = _binding_value_6;
        return doof::Failure<std::string>{ std::string("HTTP date second is invalid") };
    }
    const auto second = doof::unwrap_optional(_binding_value_6);
    auto _try_value_7 = Date::create(year, month, day);
    if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::failure_error(_try_value_7)};
    const auto date = doof::success_value(_try_value_7);
    auto _try_value_8 = Time::create(hour, minute, second, 0);
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::failure_error(_try_value_8)};
    const auto time = doof::success_value(_try_value_8);
    return doof::Success<std::shared_ptr<Instant>>{ DateTime::create(date, time)->toInstantUTC() };
}
std::string Instant::toHttpDate() {
    const auto dateTime = this->toDateTime();
    return std::string("") + doof::to_string(httpWeekdayName(dateTime->date->dayOfWeek())) + std::string(", ") + doof::to_string(doof::string_padStart(doof::to_string(dateTime->date->day), 2, U'\u0030')) + std::string(" ") + doof::to_string(httpMonthName(dateTime->date->month)) + std::string(" ") + doof::to_string(doof::string_padStart(doof::to_string(dateTime->date->year), 4, U'\u0030')) + std::string(" ") + doof::to_string(doof::string_padStart(doof::to_string(dateTime->time->hour), 2, U'\u0030')) + std::string(":") + doof::to_string(doof::string_padStart(doof::to_string(dateTime->time->minute), 2, U'\u0030')) + std::string(":") + doof::to_string(doof::string_padStart(doof::to_string(dateTime->time->second), 2, U'\u0030')) + std::string(" GMT");
}
doof::JsonObject Instant::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["epochNanos"] = doof::json_value(this->epochNanos);
    return _json;
}
doof::Result<std::shared_ptr<Instant>, std::string> Instant::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_epochNanos = _object->find("epochNanos");
    if (_iterator_epochNanos == _object->end()) { return doof::Failure<std::string>{"Missing required field \"epochNanos\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_epochNanos->second) : doof::json_is_number(_iterator_epochNanos->second)))) { return doof::Failure<std::string>{"Field \"epochNanos\" expected number but got " + std::string(doof::json_type_name(_iterator_epochNanos->second))}; }
    auto _field_epochNanos = (_lenient ? doof::json_as_long_lenient(_iterator_epochNanos->second) : doof::json_as_long(_iterator_epochNanos->second));
    return doof::Success<std::shared_ptr<Instant>>{std::make_shared<Instant>(_field_epochNanos)};
}

std::shared_ptr<Date> Date::MIN = std::make_shared<Date>(1, 1, 1);
std::shared_ptr<Date> Date::MAX = std::make_shared<Date>(9999, 12, 31);
doof::Result<std::shared_ptr<Date>, std::string> Date::create(int32_t year, int32_t month, int32_t day) {
    return _validateDate(year, month, day);
}
std::shared_ptr<Date> Date::todayUTC() {
    return _systemDateUTC();
}
std::shared_ptr<Date> Date::today(std::shared_ptr<TimeZone> zone) {
    return _systemDateInZone(zone);
}
doof::Result<std::shared_ptr<Date>, std::string> Date::parse(std::string s) {
    return _parseDate(s);
}
DayOfWeek Date::dayOfWeek() {
    return _dateToDayOfWeek(this->year, this->month, this->day);
}
int32_t Date::dayOfYear() {
    return _dateToDayOfYear(this->year, this->month, this->day);
}
bool Date::isLeapYear() {
    return _isLeapYear(this->year);
}
int32_t Date::daysInMonth() {
    return _daysInMonth(this->year, this->month);
}
std::shared_ptr<Date> Date::plusDays(int32_t n) {
    return _dateAddDays(this->year, this->month, this->day, n);
}
std::shared_ptr<Date> Date::minusDays(int32_t n) {
    return _dateAddDays(this->year, this->month, this->day, -n);
}
std::shared_ptr<Date> Date::plusMonths(int32_t n) {
    return _dateAddMonths(this->year, this->month, this->day, n);
}
std::shared_ptr<Date> Date::minusMonths(int32_t n) {
    return _dateAddMonths(this->year, this->month, this->day, -n);
}
std::shared_ptr<Date> Date::plusYears(int32_t n) {
    return _dateAddYears(this->year, this->month, this->day, n);
}
std::shared_ptr<Date> Date::minusYears(int32_t n) {
    return _dateAddYears(this->year, this->month, this->day, -n);
}
int32_t Date::daysUntil(std::shared_ptr<Date> other) {
    return _dateDiff(this->year, this->month, this->day, other->year, other->month, other->day);
}
int32_t Date::compareTo(std::shared_ptr<Date> other) {
    if (this->year != other->year) {
        return ((this->year < other->year) ? -1 : 1);
    }
    if (this->month != other->month) {
        return ((this->month < other->month) ? -1 : 1);
    }
    if (this->day != other->day) {
        return ((this->day < other->day) ? -1 : 1);
    }
    return 0;
}
bool Date::isBefore(std::shared_ptr<Date> other) {
    return (this->compareTo(other) < 0);
}
bool Date::isAfter(std::shared_ptr<Date> other) {
    return (this->compareTo(other) > 0);
}
bool Date::equals(std::shared_ptr<Date> other) {
    return (((this->year == other->year) && (this->month == other->month)) && (this->day == other->day));
}
std::string Date::toISOString() {
    return std::string("") + doof::to_string(doof::string_padStart(doof::to_string(this->year), 4, U'\u0030')) + std::string("-") + doof::to_string(doof::string_padStart(doof::to_string(this->month), 2, U'\u0030')) + std::string("-") + doof::to_string(doof::string_padStart(doof::to_string(this->day), 2, U'\u0030')) + std::string("");
}
doof::JsonObject Date::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["year"] = doof::json_value(this->year);
    (*_json)["month"] = doof::json_value(this->month);
    (*_json)["day"] = doof::json_value(this->day);
    return _json;
}
doof::Result<std::shared_ptr<Date>, std::string> Date::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_year = _object->find("year");
    if (_iterator_year == _object->end()) { return doof::Failure<std::string>{"Missing required field \"year\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_year->second) : doof::json_is_number(_iterator_year->second)))) { return doof::Failure<std::string>{"Field \"year\" expected number but got " + std::string(doof::json_type_name(_iterator_year->second))}; }
    auto _field_year = (_lenient ? doof::json_as_int_lenient(_iterator_year->second) : doof::json_as_int(_iterator_year->second));
    auto _iterator_month = _object->find("month");
    if (_iterator_month == _object->end()) { return doof::Failure<std::string>{"Missing required field \"month\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_month->second) : doof::json_is_number(_iterator_month->second)))) { return doof::Failure<std::string>{"Field \"month\" expected number but got " + std::string(doof::json_type_name(_iterator_month->second))}; }
    auto _field_month = (_lenient ? doof::json_as_int_lenient(_iterator_month->second) : doof::json_as_int(_iterator_month->second));
    auto _iterator_day = _object->find("day");
    if (_iterator_day == _object->end()) { return doof::Failure<std::string>{"Missing required field \"day\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_day->second) : doof::json_is_number(_iterator_day->second)))) { return doof::Failure<std::string>{"Field \"day\" expected number but got " + std::string(doof::json_type_name(_iterator_day->second))}; }
    auto _field_day = (_lenient ? doof::json_as_int_lenient(_iterator_day->second) : doof::json_as_int(_iterator_day->second));
    return doof::Success<std::shared_ptr<Date>>{std::make_shared<Date>(_field_year, _field_month, _field_day)};
}

std::shared_ptr<Time> Time::MIDNIGHT = std::make_shared<Time>(0, 0, 0, 0);
std::shared_ptr<Time> Time::NOON = std::make_shared<Time>(12, 0, 0, 0);
doof::Result<std::shared_ptr<Time>, std::string> Time::create(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond) {
    return _validateTime(hour, minute, second, nanosecond);
}
doof::Result<std::shared_ptr<Time>, std::string> Time::parse(std::string s) {
    return _parseTime(s);
}
std::shared_ptr<Time> Time::plusHours(int32_t n) {
    return _timeAddNanos(this->hour, this->minute, this->second, this->nanosecond, (static_cast<int64_t>(n) * 3600000000000LL));
}
std::shared_ptr<Time> Time::plusMinutes(int32_t n) {
    return _timeAddNanos(this->hour, this->minute, this->second, this->nanosecond, (static_cast<int64_t>(n) * 60000000000LL));
}
std::shared_ptr<Time> Time::plusSeconds(int32_t n) {
    return _timeAddNanos(this->hour, this->minute, this->second, this->nanosecond, (static_cast<int64_t>(n) * 1000000000LL));
}
std::shared_ptr<Time> Time::plusNanos(int64_t n) {
    return _timeAddNanos(this->hour, this->minute, this->second, this->nanosecond, n);
}
int32_t Time::compareTo(std::shared_ptr<Time> other) {
    if (this->hour != other->hour) {
        return ((this->hour < other->hour) ? -1 : 1);
    }
    if (this->minute != other->minute) {
        return ((this->minute < other->minute) ? -1 : 1);
    }
    if (this->second != other->second) {
        return ((this->second < other->second) ? -1 : 1);
    }
    if (this->nanosecond != other->nanosecond) {
        return ((this->nanosecond < other->nanosecond) ? -1 : 1);
    }
    return 0;
}
bool Time::isBefore(std::shared_ptr<Time> other) {
    return (this->compareTo(other) < 0);
}
bool Time::isAfter(std::shared_ptr<Time> other) {
    return (this->compareTo(other) > 0);
}
bool Time::equals(std::shared_ptr<Time> other) {
    return ((((this->hour == other->hour) && (this->minute == other->minute)) && (this->second == other->second)) && (this->nanosecond == other->nanosecond));
}
std::string Time::toISOString() {
    auto base = std::string("") + doof::to_string(doof::string_padStart(doof::to_string(this->hour), 2, U'\u0030')) + std::string(":") + doof::to_string(doof::string_padStart(doof::to_string(this->minute), 2, U'\u0030')) + std::string(":") + doof::to_string(doof::string_padStart(doof::to_string(this->second), 2, U'\u0030')) + std::string("");
    if (this->nanosecond == 0) {
        return base;
    }
    return std::string("") + doof::to_string(base) + std::string(".") + doof::to_string(doof::string_trimEnd(doof::string_padStart(doof::to_string(this->nanosecond), 9, U'\u0030'), U'\u0030')) + std::string("");
}
doof::JsonObject Time::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["hour"] = doof::json_value(this->hour);
    (*_json)["minute"] = doof::json_value(this->minute);
    (*_json)["second"] = doof::json_value(this->second);
    (*_json)["nanosecond"] = doof::json_value(this->nanosecond);
    return _json;
}
doof::Result<std::shared_ptr<Time>, std::string> Time::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_hour = _object->find("hour");
    if (_iterator_hour == _object->end()) { return doof::Failure<std::string>{"Missing required field \"hour\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_hour->second) : doof::json_is_number(_iterator_hour->second)))) { return doof::Failure<std::string>{"Field \"hour\" expected number but got " + std::string(doof::json_type_name(_iterator_hour->second))}; }
    auto _field_hour = (_lenient ? doof::json_as_int_lenient(_iterator_hour->second) : doof::json_as_int(_iterator_hour->second));
    auto _iterator_minute = _object->find("minute");
    if (_iterator_minute == _object->end()) { return doof::Failure<std::string>{"Missing required field \"minute\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_minute->second) : doof::json_is_number(_iterator_minute->second)))) { return doof::Failure<std::string>{"Field \"minute\" expected number but got " + std::string(doof::json_type_name(_iterator_minute->second))}; }
    auto _field_minute = (_lenient ? doof::json_as_int_lenient(_iterator_minute->second) : doof::json_as_int(_iterator_minute->second));
    auto _iterator_second = _object->find("second");
    if (_iterator_second == _object->end()) { return doof::Failure<std::string>{"Missing required field \"second\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_second->second) : doof::json_is_number(_iterator_second->second)))) { return doof::Failure<std::string>{"Field \"second\" expected number but got " + std::string(doof::json_type_name(_iterator_second->second))}; }
    auto _field_second = (_lenient ? doof::json_as_int_lenient(_iterator_second->second) : doof::json_as_int(_iterator_second->second));
    auto _iterator_nanosecond = _object->find("nanosecond");
    if (_iterator_nanosecond == _object->end()) { return doof::Failure<std::string>{"Missing required field \"nanosecond\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_nanosecond->second) : doof::json_is_number(_iterator_nanosecond->second)))) { return doof::Failure<std::string>{"Field \"nanosecond\" expected number but got " + std::string(doof::json_type_name(_iterator_nanosecond->second))}; }
    auto _field_nanosecond = (_lenient ? doof::json_as_int_lenient(_iterator_nanosecond->second) : doof::json_as_int(_iterator_nanosecond->second));
    return doof::Success<std::shared_ptr<Time>>{std::make_shared<Time>(_field_hour, _field_minute, _field_second, _field_nanosecond)};
}

std::shared_ptr<DateTime> DateTime::create(std::shared_ptr<Date> date, std::shared_ptr<Time> time) {
    return std::make_shared<DateTime>(date, time);
}
doof::Result<std::shared_ptr<DateTime>, std::string> DateTime::fromParts(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, int32_t nanosecond) {
    auto _try_value_9 = Date::create(year, month, day);
    if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::failure_error(_try_value_9)};
    const auto d = doof::success_value(_try_value_9);
    auto _try_value_10 = Time::create(hour, minute, second, nanosecond);
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::failure_error(_try_value_10)};
    const auto t = doof::success_value(_try_value_10);
    return doof::Success<std::shared_ptr<DateTime>>{ std::make_shared<DateTime>(d, t) };
}
std::shared_ptr<DateTime> DateTime::nowUTC() {
    return Instant::now()->toDateTime();
}
doof::Result<std::shared_ptr<DateTime>, std::string> DateTime::parse(std::string s) {
    return _parseDateTime(s);
}
std::shared_ptr<DateTime> DateTime::plusDays(int32_t n) {
    return std::make_shared<DateTime>(this->date->plusDays(n), time);
}
std::shared_ptr<DateTime> DateTime::minusDays(int32_t n) {
    return std::make_shared<DateTime>(this->date->minusDays(n), time);
}
std::shared_ptr<DateTime> DateTime::plusHours(int32_t n) {
    return _dateTimePlusNanos(this->date, this->time, (static_cast<int64_t>(n) * 3600000000000LL));
}
std::shared_ptr<DateTime> DateTime::plusMinutes(int32_t n) {
    return _dateTimePlusNanos(this->date, this->time, (static_cast<int64_t>(n) * 60000000000LL));
}
std::shared_ptr<DateTime> DateTime::plusSeconds(int32_t n) {
    return _dateTimePlusNanos(this->date, this->time, (static_cast<int64_t>(n) * 1000000000LL));
}
std::shared_ptr<DateTime> DateTime::plus(std::shared_ptr<::std_::time::duration::Duration> d) {
    return _dateTimePlusNanos(this->date, this->time, d->toNanos());
}
std::shared_ptr<DateTime> DateTime::minus(std::shared_ptr<::std_::time::duration::Duration> d) {
    return _dateTimePlusNanos(this->date, this->time, -d->toNanos());
}
std::shared_ptr<Instant> DateTime::toInstantUTC() {
    return _dateTimeToInstant(this->date, this->time);
}
std::shared_ptr<Instant> DateTime::toInstant(std::shared_ptr<TimeZone> zone) {
    return _dateTimeToInstantInZone(this->date, this->time, zone);
}
std::shared_ptr<ZonedDateTime> DateTime::atZone(std::shared_ptr<TimeZone> zone) {
    return _dateTimeAtZone(this->shared_from_this(), zone);
}
int32_t DateTime::compareTo(std::shared_ptr<DateTime> other) {
    auto dc = this->date->compareTo(other->date);
    if (dc != 0) {
        return dc;
    }
    return this->time->compareTo(other->time);
}
bool DateTime::isBefore(std::shared_ptr<DateTime> other) {
    return (this->compareTo(other) < 0);
}
bool DateTime::isAfter(std::shared_ptr<DateTime> other) {
    return (this->compareTo(other) > 0);
}
bool DateTime::equals(std::shared_ptr<DateTime> other) {
    return (this->date->equals(other->date) && this->time->equals(other->time));
}
std::string DateTime::toISOString() {
    return std::string("") + doof::to_string(this->date->toISOString()) + std::string("T") + doof::to_string(this->time->toISOString()) + std::string("");
}
doof::JsonObject DateTime::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["date"] = doof::json_value(this->date->toJsonObject());
    (*_json)["time"] = doof::json_value(this->time->toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<DateTime>, std::string> DateTime::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_date = _object->find("date");
    if (_iterator_date == _object->end()) { return doof::Failure<std::string>{"Missing required field \"date\""}; }
    if (!(doof::json_is_object(_iterator_date->second))) { return doof::Failure<std::string>{"Field \"date\" expected object but got " + std::string(doof::json_type_name(_iterator_date->second))}; }
    auto _field_date = doof::success_value(Date::fromJsonValue(_iterator_date->second, _lenient));
    auto _iterator_time = _object->find("time");
    if (_iterator_time == _object->end()) { return doof::Failure<std::string>{"Missing required field \"time\""}; }
    if (!(doof::json_is_object(_iterator_time->second))) { return doof::Failure<std::string>{"Field \"time\" expected object but got " + std::string(doof::json_type_name(_iterator_time->second))}; }
    auto _field_time = doof::success_value(Time::fromJsonValue(_iterator_time->second, _lenient));
    return doof::Success<std::shared_ptr<DateTime>>{std::make_shared<DateTime>(_field_date, _field_time)};
}

std::shared_ptr<TimeZone> TimeZone::UTC = std::make_shared<TimeZone>(std::string("UTC"));
doof::Result<std::shared_ptr<TimeZone>, std::string> TimeZone::lookup(std::string id) {
    return _lookupTimeZone(id);
}
std::shared_ptr<TimeZone> TimeZone::local() {
    return _systemTimeZone();
}
int32_t TimeZone::offsetSecondsAt(std::shared_ptr<Instant> instant) {
    return _zoneOffsetAt(this->id, instant->toEpochSeconds());
}
bool TimeZone::isDSTAt(std::shared_ptr<Instant> instant) {
    return _zoneDSTAt(this->id, instant->toEpochSeconds());
}
doof::JsonObject TimeZone::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["id"] = doof::json_value(this->id);
    return _json;
}
doof::Result<std::shared_ptr<TimeZone>, std::string> TimeZone::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_id = _object->find("id");
    if (_iterator_id == _object->end()) { return doof::Failure<std::string>{"Missing required field \"id\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_id->second) : doof::json_is_string(_iterator_id->second)))) { return doof::Failure<std::string>{"Field \"id\" expected string but got " + std::string(doof::json_type_name(_iterator_id->second))}; }
    auto _field_id = (_lenient ? doof::json_as_string_lenient(_iterator_id->second) : doof::json_as_string(_iterator_id->second));
    return doof::Success<std::shared_ptr<TimeZone>>{std::make_shared<TimeZone>(_field_id)};
}

std::shared_ptr<ZonedDateTime> ZonedDateTime::now(std::shared_ptr<TimeZone> zone) {
    return Instant::now()->toZonedDateTime(zone);
}
std::shared_ptr<ZonedDateTime> ZonedDateTime::nowUTC() {
    return Instant::now()->toZonedDateTime(TimeZone::UTC);
}
std::shared_ptr<Date> ZonedDateTime::date() {
    return this->dateTime->date;
}
std::shared_ptr<Time> ZonedDateTime::time() {
    return this->dateTime->time;
}
int32_t ZonedDateTime::offsetSeconds() {
    return this->zone->offsetSecondsAt(this->toInstant());
}
std::shared_ptr<Instant> ZonedDateTime::toInstant() {
    return this->dateTime->toInstant(this->zone);
}
std::shared_ptr<ZonedDateTime> ZonedDateTime::withZoneSameInstant(std::shared_ptr<TimeZone> newZone) {
    return this->toInstant()->toZonedDateTime(newZone);
}
std::shared_ptr<ZonedDateTime> ZonedDateTime::withZoneSameLocal(std::shared_ptr<TimeZone> newZone) {
    return std::make_shared<ZonedDateTime>(dateTime, newZone);
}
std::shared_ptr<DateTime> ZonedDateTime::toDateTime() {
    return this->dateTime;
}
std::shared_ptr<ZonedDateTime> ZonedDateTime::toUTC() {
    return this->withZoneSameInstant(TimeZone::UTC);
}
int32_t ZonedDateTime::compareTo(std::shared_ptr<ZonedDateTime> other) {
    return this->toInstant()->compareTo(other->toInstant());
}
bool ZonedDateTime::isBefore(std::shared_ptr<ZonedDateTime> other) {
    return this->toInstant()->isBefore(other->toInstant());
}
bool ZonedDateTime::isAfter(std::shared_ptr<ZonedDateTime> other) {
    return this->toInstant()->isAfter(other->toInstant());
}
std::string ZonedDateTime::toISOString() {
    auto offset = this->offsetSeconds();
    if (offset == 0) {
        return std::string("") + doof::to_string(this->dateTime->toISOString()) + std::string("Z");
    }
    auto sign = ((offset < 0) ? std::string("-") : std::string("+"));
    auto abs = ((offset < 0) ? -offset : offset);
    auto h = (abs / 3600);
    auto m = ((abs % 3600) / 60);
    auto suffix = std::string("") + doof::to_string(sign) + std::string("") + doof::to_string(doof::string_padStart(doof::to_string(h), 2, U'\u0030')) + std::string(":") + doof::to_string(doof::string_padStart(doof::to_string(m), 2, U'\u0030')) + std::string("");
    return std::string("") + doof::to_string(this->dateTime->toISOString()) + std::string("") + doof::to_string(suffix) + std::string("");
}
doof::JsonObject ZonedDateTime::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["dateTime"] = doof::json_value(this->dateTime->toJsonObject());
    (*_json)["zone"] = doof::json_value(this->zone->toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<ZonedDateTime>, std::string> ZonedDateTime::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_dateTime = _object->find("dateTime");
    if (_iterator_dateTime == _object->end()) { return doof::Failure<std::string>{"Missing required field \"dateTime\""}; }
    if (!(doof::json_is_object(_iterator_dateTime->second))) { return doof::Failure<std::string>{"Field \"dateTime\" expected object but got " + std::string(doof::json_type_name(_iterator_dateTime->second))}; }
    auto _field_dateTime = doof::success_value(DateTime::fromJsonValue(_iterator_dateTime->second, _lenient));
    auto _iterator_zone = _object->find("zone");
    if (_iterator_zone == _object->end()) { return doof::Failure<std::string>{"Missing required field \"zone\""}; }
    if (!(doof::json_is_object(_iterator_zone->second))) { return doof::Failure<std::string>{"Field \"zone\" expected object but got " + std::string(doof::json_type_name(_iterator_zone->second))}; }
    auto _field_zone = doof::success_value(TimeZone::fromJsonValue(_iterator_zone->second, _lenient));
    return doof::Success<std::shared_ptr<ZonedDateTime>>{std::make_shared<ZonedDateTime>(_field_dateTime, _field_zone)};
}
std::string httpWeekdayName(DayOfWeek day) {
    return [&]() -> std::string {
    auto _case_subject = day;
    if (_case_subject == DayOfWeek::Monday) {
        return std::string("Mon");
    }
    if (_case_subject == DayOfWeek::Tuesday) {
        return std::string("Tue");
    }
    if (_case_subject == DayOfWeek::Wednesday) {
        return std::string("Wed");
    }
    if (_case_subject == DayOfWeek::Thursday) {
        return std::string("Thu");
    }
    if (_case_subject == DayOfWeek::Friday) {
        return std::string("Fri");
    }
    if (_case_subject == DayOfWeek::Saturday) {
        return std::string("Sat");
    }
    if (_case_subject == DayOfWeek::Sunday) {
        return std::string("Sun");
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
std::string httpMonthName(int32_t month) {
    return [&]() -> std::string {
    auto _case_subject = month;
    if (_case_subject == static_cast<int32_t>(Month::January)) {
        return std::string("Jan");
    }
    if (_case_subject == static_cast<int32_t>(Month::February)) {
        return std::string("Feb");
    }
    if (_case_subject == static_cast<int32_t>(Month::March)) {
        return std::string("Mar");
    }
    if (_case_subject == static_cast<int32_t>(Month::April)) {
        return std::string("Apr");
    }
    if (_case_subject == static_cast<int32_t>(Month::May)) {
        return std::string("May");
    }
    if (_case_subject == static_cast<int32_t>(Month::June)) {
        return std::string("Jun");
    }
    if (_case_subject == static_cast<int32_t>(Month::July)) {
        return std::string("Jul");
    }
    if (_case_subject == static_cast<int32_t>(Month::August)) {
        return std::string("Aug");
    }
    if (_case_subject == static_cast<int32_t>(Month::September)) {
        return std::string("Sep");
    }
    if (_case_subject == static_cast<int32_t>(Month::October)) {
        return std::string("Oct");
    }
    if (_case_subject == static_cast<int32_t>(Month::November)) {
        return std::string("Nov");
    }
    if (_case_subject == static_cast<int32_t>(Month::December)) {
        return std::string("Dec");
    }
    if (true) {
        return std::string("Jan");
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
std::optional<int32_t> httpMonthNumber(std::string text) {
    return [&]() -> std::optional<int32_t> {
    auto _case_subject = text;
    if (_case_subject == std::string("Jan")) {
        return static_cast<int32_t>(Month::January);
    }
    if (_case_subject == std::string("Feb")) {
        return static_cast<int32_t>(Month::February);
    }
    if (_case_subject == std::string("Mar")) {
        return static_cast<int32_t>(Month::March);
    }
    if (_case_subject == std::string("Apr")) {
        return static_cast<int32_t>(Month::April);
    }
    if (_case_subject == std::string("May")) {
        return static_cast<int32_t>(Month::May);
    }
    if (_case_subject == std::string("Jun")) {
        return static_cast<int32_t>(Month::June);
    }
    if (_case_subject == std::string("Jul")) {
        return static_cast<int32_t>(Month::July);
    }
    if (_case_subject == std::string("Aug")) {
        return static_cast<int32_t>(Month::August);
    }
    if (_case_subject == std::string("Sep")) {
        return static_cast<int32_t>(Month::September);
    }
    if (_case_subject == std::string("Oct")) {
        return static_cast<int32_t>(Month::October);
    }
    if (_case_subject == std::string("Nov")) {
        return static_cast<int32_t>(Month::November);
    }
    if (_case_subject == std::string("Dec")) {
        return static_cast<int32_t>(Month::December);
    }
    if (true) {
        return std::nullopt;
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
int64_t _systemNanosEpoch() {
    return ::doof_time::system_nanos_epoch();
}
doof::Result<std::shared_ptr<Instant>, std::string> _parseInstant(std::string s) {
    return ::doof_time::parse_instant(s);
}
std::shared_ptr<DateTime> _instantToDateTime(int64_t nanos) {
    return ::doof_time::instant_to_datetime(nanos);
}
std::shared_ptr<ZonedDateTime> _instantToZonedDateTime(int64_t nanos, std::shared_ptr<TimeZone> zone) {
    return ::doof_time::instant_to_zoned_datetime(nanos, zone);
}
std::string _formatInstant(int64_t nanos) {
    return ::doof_time::format_instant(nanos);
}
doof::Result<std::shared_ptr<Date>, std::string> _validateDate(int32_t year, int32_t month, int32_t day) {
    return ::doof_time::validate_date(year, month, day);
}
std::shared_ptr<Date> _systemDateUTC() {
    return ::doof_time::system_date_utc();
}
std::shared_ptr<Date> _systemDateInZone(std::shared_ptr<TimeZone> zone) {
    return ::doof_time::system_date_in_zone(zone);
}
doof::Result<std::shared_ptr<Date>, std::string> _parseDate(std::string s) {
    return ::doof_time::parse_date(s);
}
DayOfWeek _dateToDayOfWeek(int32_t year, int32_t month, int32_t day) {
    return ::doof_time::date_to_day_of_week(year, month, day);
}
int32_t _dateToDayOfYear(int32_t year, int32_t month, int32_t day) {
    return ::doof_time::date_to_day_of_year(year, month, day);
}
bool _isLeapYear(int32_t year) {
    return ::doof_time::is_leap_year(year);
}
int32_t _daysInMonth(int32_t year, int32_t month) {
    return ::doof_time::days_in_month(year, month);
}
std::shared_ptr<Date> _dateAddDays(int32_t year, int32_t month, int32_t day, int32_t n) {
    return ::doof_time::date_add_days(year, month, day, n);
}
std::shared_ptr<Date> _dateAddMonths(int32_t year, int32_t month, int32_t day, int32_t n) {
    return ::doof_time::date_add_months(year, month, day, n);
}
std::shared_ptr<Date> _dateAddYears(int32_t year, int32_t month, int32_t day, int32_t n) {
    return ::doof_time::date_add_years(year, month, day, n);
}
int32_t _dateDiff(int32_t y1, int32_t m1, int32_t d1, int32_t y2, int32_t m2, int32_t d2) {
    return ::doof_time::date_diff(y1, m1, d1, y2, m2, d2);
}
doof::Result<std::shared_ptr<Time>, std::string> _validateTime(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond) {
    return ::doof_time::validate_time(hour, minute, second, nanosecond);
}
doof::Result<std::shared_ptr<Time>, std::string> _parseTime(std::string s) {
    return ::doof_time::parse_time(s);
}
std::shared_ptr<Time> _timeAddNanos(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond, int64_t nanos) {
    return ::doof_time::time_add_nanos(hour, minute, second, nanosecond, nanos);
}
doof::Result<std::shared_ptr<DateTime>, std::string> _parseDateTime(std::string s) {
    return ::doof_time::parse_datetime(s);
}
std::shared_ptr<DateTime> _dateTimePlusNanos(std::shared_ptr<Date> date, std::shared_ptr<Time> time, int64_t nanos) {
    return ::doof_time::datetime_plus_nanos(date, time, nanos);
}
std::shared_ptr<Instant> _dateTimeToInstant(std::shared_ptr<Date> date, std::shared_ptr<Time> time) {
    return ::doof_time::datetime_to_instant(date, time);
}
std::shared_ptr<Instant> _dateTimeToInstantInZone(std::shared_ptr<Date> date, std::shared_ptr<Time> time, std::shared_ptr<TimeZone> zone) {
    return ::doof_time::datetime_to_instant_in_zone(date, time, zone);
}
std::shared_ptr<ZonedDateTime> _dateTimeAtZone(std::shared_ptr<DateTime> dateTime, std::shared_ptr<TimeZone> zone) {
    return ::doof_time::datetime_at_zone(dateTime, zone);
}
doof::Result<std::shared_ptr<TimeZone>, std::string> _lookupTimeZone(std::string id) {
    return ::doof_time::lookup_timezone(id);
}
std::shared_ptr<TimeZone> _systemTimeZone() {
    return ::doof_time::system_timezone();
}
int32_t _zoneOffsetAt(std::string id, int64_t epochSeconds) {
    return ::doof_time::zone_offset_at(id, epochSeconds);
}
bool _zoneDSTAt(std::string id, int64_t epochSeconds) {
    return ::doof_time::zone_dst_at(id, epochSeconds);
}
}
