#include "std_time_temporal.hpp"

namespace std_::time::temporal {
using namespace ::std_::parse::index;
using namespace ::std_::time::duration;

std::shared_ptr<Instant> Instant::EPOCH;
#line 13 "/std/time/temporal.do"
std::shared_ptr<Instant> Instant::now() {
#line 14 "/std/time/temporal.do"
    return std::make_shared<Instant>(::doof_time::system_nanos_epoch());
}
#line 17 "/std/time/temporal.do"
std::shared_ptr<Instant> Instant::ofEpochNanos(int64_t nanos) {
    return std::make_shared<Instant>(nanos);
}
#line 18 "/std/time/temporal.do"
std::shared_ptr<Instant> Instant::ofEpochMillis(int64_t ms) {
    return std::make_shared<Instant>((ms * 1000000LL));
}
#line 19 "/std/time/temporal.do"
std::shared_ptr<Instant> Instant::ofEpochSeconds(int64_t s) {
    return std::make_shared<Instant>((s * 1000000000LL));
}
#line 22 "/std/time/temporal.do"
doof::Result<std::shared_ptr<Instant>, std::string> Instant::parse(const std::string& s) {
#line 23 "/std/time/temporal.do"
    return ::doof_time::parse_instant(s);
}
#line 30 "/std/time/temporal.do"
int64_t Instant::toEpochNanos() {
    return this->epochNanos;
}
#line 31 "/std/time/temporal.do"
int64_t Instant::toEpochMillis() {
    return (this->epochNanos / 1000000LL);
}
#line 32 "/std/time/temporal.do"
int64_t Instant::toEpochSeconds() {
    return (this->epochNanos / 1000000000LL);
}
#line 36 "/std/time/temporal.do"
std::shared_ptr<Instant> Instant::plus(const std::shared_ptr<::std_::time::duration::Duration>& d) {
    return std::make_shared<Instant>((this->epochNanos + d->toNanos()));
}
#line 37 "/std/time/temporal.do"
std::shared_ptr<Instant> Instant::minus(const std::shared_ptr<::std_::time::duration::Duration>& d) {
    return std::make_shared<Instant>((this->epochNanos - d->toNanos()));
}
#line 38 "/std/time/temporal.do"
std::shared_ptr<::std_::time::duration::Duration> Instant::durationUntil(const std::shared_ptr<Instant>& other) {
    return ::std_::time::duration::Duration::ofNanos((other->epochNanos - this->epochNanos));
}
#line 39 "/std/time/temporal.do"
std::shared_ptr<::std_::time::duration::Duration> Instant::durationSince(const std::shared_ptr<Instant>& other) {
    return ::std_::time::duration::Duration::ofNanos((this->epochNanos - other->epochNanos));
}
#line 43 "/std/time/temporal.do"
int32_t Instant::compareTo(const std::shared_ptr<Instant>& other) {
#line 44 "/std/time/temporal.do"
    if (this->epochNanos < other->epochNanos) {
#line 44 "/std/time/temporal.do"
        return -1;
    }
#line 45 "/std/time/temporal.do"
    if (this->epochNanos > other->epochNanos) {
#line 45 "/std/time/temporal.do"
        return 1;
    }
#line 46 "/std/time/temporal.do"
    return 0;
}
#line 49 "/std/time/temporal.do"
bool Instant::isBefore(const std::shared_ptr<Instant>& other) {
    return (this->epochNanos < other->epochNanos);
}
#line 50 "/std/time/temporal.do"
bool Instant::isAfter(const std::shared_ptr<Instant>& other) {
    return (this->epochNanos > other->epochNanos);
}
#line 51 "/std/time/temporal.do"
bool Instant::equals(const std::shared_ptr<Instant>& other) {
    return (this->epochNanos == other->epochNanos);
}
#line 55 "/std/time/temporal.do"
std::shared_ptr<DateTime> Instant::toDateTime() {
    return ::doof_time::instant_to_datetime(this->epochNanos);
}
#line 56 "/std/time/temporal.do"
std::shared_ptr<ZonedDateTime> Instant::toZonedDateTime(const std::shared_ptr<TimeZone>& zone) {
    return ::doof_time::instant_to_zoned_datetime(this->epochNanos, zone);
}
#line 61 "/std/time/temporal.do"
std::string Instant::toISOString() {
    return ::doof_time::format_instant(this->epochNanos);
}
#line 64 "/std/time/temporal.do"
doof::Result<std::shared_ptr<Instant>, std::string> Instant::parseHttpDate(const std::string& s) {
#line 65 "/std/time/temporal.do"
    if (static_cast<int32_t>(s.size()) != 29) {
#line 66 "/std/time/temporal.do"
        return doof::Failure<std::string>{ std::string("HTTP date must use IMF-fixdate format") };
    }
#line 68 "/std/time/temporal.do"
    if (((((((doof::string_substring(s, 3, 5) != std::string(", ")) || (doof::string_at(s, 7, "", 0) != U'\u0020')) || (doof::string_at(s, 11, "", 0) != U'\u0020')) || (doof::string_at(s, 16, "", 0) != U'\u0020')) || (doof::string_at(s, 19, "", 0) != U'\u003A')) || (doof::string_at(s, 22, "", 0) != U'\u003A')) || (doof::string_slice(s, 25) != std::string(" GMT"))) {
#line 71 "/std/time/temporal.do"
        return doof::Failure<std::string>{ std::string("HTTP date must use IMF-fixdate format") };
    }
#line 74 "/std/time/temporal.do"
    auto _binding_value_1 = [&]() -> std::optional<int32_t> { auto _try_value = ::doof_parse::parseInt(doof::string_substring(s, 5, 7)); if (doof::is_failure(_try_value)) doof::panic_at("temporal", 74, std::string("try? failed")); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_1)) {
        const auto& day = _binding_value_1;
#line 75 "/std/time/temporal.do"
        return doof::Failure<std::string>{ std::string("HTTP date day is invalid") };
    }
    const auto day = doof::unwrap_optional(_binding_value_1);
#line 77 "/std/time/temporal.do"
    auto _binding_value_2 = httpMonthNumber(doof::string_substring(s, 8, 11));
    if (doof::is_null(_binding_value_2)) {
        const auto& month = _binding_value_2;
#line 78 "/std/time/temporal.do"
        return doof::Failure<std::string>{ std::string("HTTP date month is invalid") };
    }
    const auto month = doof::unwrap_optional(_binding_value_2);
#line 80 "/std/time/temporal.do"
    auto _binding_value_3 = [&]() -> std::optional<int32_t> { auto _try_value = ::doof_parse::parseInt(doof::string_substring(s, 12, 16)); if (doof::is_failure(_try_value)) doof::panic_at("temporal", 80, std::string("try? failed")); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_3)) {
        const auto& year = _binding_value_3;
#line 81 "/std/time/temporal.do"
        return doof::Failure<std::string>{ std::string("HTTP date year is invalid") };
    }
    const auto year = doof::unwrap_optional(_binding_value_3);
#line 83 "/std/time/temporal.do"
    auto _binding_value_4 = [&]() -> std::optional<int32_t> { auto _try_value = ::doof_parse::parseInt(doof::string_substring(s, 17, 19)); if (doof::is_failure(_try_value)) doof::panic_at("temporal", 83, std::string("try? failed")); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_4)) {
        const auto& hour = _binding_value_4;
#line 84 "/std/time/temporal.do"
        return doof::Failure<std::string>{ std::string("HTTP date hour is invalid") };
    }
    const auto hour = doof::unwrap_optional(_binding_value_4);
#line 86 "/std/time/temporal.do"
    auto _binding_value_5 = [&]() -> std::optional<int32_t> { auto _try_value = ::doof_parse::parseInt(doof::string_substring(s, 20, 22)); if (doof::is_failure(_try_value)) doof::panic_at("temporal", 86, std::string("try? failed")); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_5)) {
        const auto& minute = _binding_value_5;
#line 87 "/std/time/temporal.do"
        return doof::Failure<std::string>{ std::string("HTTP date minute is invalid") };
    }
    const auto minute = doof::unwrap_optional(_binding_value_5);
#line 89 "/std/time/temporal.do"
    auto _binding_value_6 = [&]() -> std::optional<int32_t> { auto _try_value = ::doof_parse::parseInt(doof::string_substring(s, 23, 25)); if (doof::is_failure(_try_value)) doof::panic_at("temporal", 89, std::string("try? failed")); return std::move(doof::success_value(_try_value)); }();
    if (doof::is_null(_binding_value_6)) {
        const auto& second = _binding_value_6;
#line 90 "/std/time/temporal.do"
        return doof::Failure<std::string>{ std::string("HTTP date second is invalid") };
    }
    const auto second = doof::unwrap_optional(_binding_value_6);
#line 92 "/std/time/temporal.do"
    auto _try_value_7 = Date::create(year, month, day);
    if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_7))};
    const auto date = doof::success_value(_try_value_7);
#line 93 "/std/time/temporal.do"
    auto _try_value_8 = Time::create(hour, minute, second, 0);
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
    const auto time = doof::success_value(_try_value_8);
#line 94 "/std/time/temporal.do"
    return doof::Success<std::shared_ptr<Instant>>{ DateTime::create(date, time)->toInstantUTC() };
}
#line 98 "/std/time/temporal.do"
std::string Instant::toHttpDate() {
#line 99 "/std/time/temporal.do"
    const auto dateTime = this->toDateTime();
#line 100 "/std/time/temporal.do"
    return ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(httpWeekdayName(dateTime->date->dayOfWeek())); _interpolation += ", "; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(dateTime->date->day), 2, U'\u0030')); _interpolation += " "; _interpolation += doof::to_string(httpMonthName(dateTime->date->month)); _interpolation += " "; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(dateTime->date->year), 4, U'\u0030')); _interpolation += " "; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(dateTime->time->hour), 2, U'\u0030')); _interpolation += ":"; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(dateTime->time->minute), 2, U'\u0030')); _interpolation += ":"; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(dateTime->time->second), 2, U'\u0030')); _interpolation += " GMT"; return _interpolation; }());
}

std::shared_ptr<Date> Date::MIN;
std::shared_ptr<Date> Date::MAX;
#line 111 "/std/time/temporal.do"
doof::Result<std::shared_ptr<Date>, std::string> Date::create(int32_t year, int32_t month, int32_t day) {
#line 112 "/std/time/temporal.do"
    return ::doof_time::validate_date(year, month, day);
}
#line 116 "/std/time/temporal.do"
std::shared_ptr<Date> Date::todayUTC() {
    return ::doof_time::system_date_utc();
}
#line 119 "/std/time/temporal.do"
std::shared_ptr<Date> Date::today(const std::shared_ptr<TimeZone>& zone) {
    return ::doof_time::system_date_in_zone(zone);
}
#line 122 "/std/time/temporal.do"
doof::Result<std::shared_ptr<Date>, std::string> Date::parse(const std::string& s) {
#line 123 "/std/time/temporal.do"
    return ::doof_time::parse_date(s);
}
#line 131 "/std/time/temporal.do"
DayOfWeek Date::dayOfWeek() {
    return ::doof_time::date_to_day_of_week(this->year, this->month, this->day);
}
#line 132 "/std/time/temporal.do"
int32_t Date::dayOfYear() {
    return ::doof_time::date_to_day_of_year(this->year, this->month, this->day);
}
#line 133 "/std/time/temporal.do"
bool Date::isLeapYear() {
    return ::doof_time::is_leap_year(this->year);
}
#line 134 "/std/time/temporal.do"
int32_t Date::daysInMonth() {
    return ::doof_time::days_in_month(this->year, this->month);
}
#line 138 "/std/time/temporal.do"
std::shared_ptr<Date> Date::plusDays(int32_t n) {
    return ::doof_time::date_add_days(this->year, this->month, this->day, n);
}
#line 139 "/std/time/temporal.do"
std::shared_ptr<Date> Date::minusDays(int32_t n) {
    return ::doof_time::date_add_days(this->year, this->month, this->day, -n);
}
#line 140 "/std/time/temporal.do"
std::shared_ptr<Date> Date::plusMonths(int32_t n) {
    return ::doof_time::date_add_months(this->year, this->month, this->day, n);
}
#line 141 "/std/time/temporal.do"
std::shared_ptr<Date> Date::minusMonths(int32_t n) {
    return ::doof_time::date_add_months(this->year, this->month, this->day, -n);
}
#line 142 "/std/time/temporal.do"
std::shared_ptr<Date> Date::plusYears(int32_t n) {
    return ::doof_time::date_add_years(this->year, this->month, this->day, n);
}
#line 143 "/std/time/temporal.do"
std::shared_ptr<Date> Date::minusYears(int32_t n) {
    return ::doof_time::date_add_years(this->year, this->month, this->day, -n);
}
#line 146 "/std/time/temporal.do"
int32_t Date::daysUntil(const std::shared_ptr<Date>& other) {
    return ::doof_time::date_diff(this->year, this->month, this->day, other->year, other->month, other->day);
}
#line 150 "/std/time/temporal.do"
int32_t Date::compareTo(const std::shared_ptr<Date>& other) {
#line 151 "/std/time/temporal.do"
    if (this->year != other->year) {
#line 151 "/std/time/temporal.do"
        return ((this->year < other->year) ? -1 : 1);
    }
#line 152 "/std/time/temporal.do"
    if (this->month != other->month) {
#line 152 "/std/time/temporal.do"
        return ((this->month < other->month) ? -1 : 1);
    }
#line 153 "/std/time/temporal.do"
    if (this->day != other->day) {
#line 153 "/std/time/temporal.do"
        return ((this->day < other->day) ? -1 : 1);
    }
#line 154 "/std/time/temporal.do"
    return 0;
}
#line 157 "/std/time/temporal.do"
bool Date::isBefore(const std::shared_ptr<Date>& other) {
    return (this->compareTo(other) < 0);
}
#line 158 "/std/time/temporal.do"
bool Date::isAfter(const std::shared_ptr<Date>& other) {
    return (this->compareTo(other) > 0);
}
#line 159 "/std/time/temporal.do"
bool Date::equals(const std::shared_ptr<Date>& other) {
    return (((this->year == other->year) && (this->month == other->month)) && (this->day == other->day));
}
#line 164 "/std/time/temporal.do"
std::string Date::toISOString() {
    return ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(this->year), 4, U'\u0030')); _interpolation += "-"; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(this->month), 2, U'\u0030')); _interpolation += "-"; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(this->day), 2, U'\u0030')); _interpolation += ""; return _interpolation; }());
}

std::shared_ptr<Time> Time::MIDNIGHT;
std::shared_ptr<Time> Time::NOON;
#line 176 "/std/time/temporal.do"
doof::Result<std::shared_ptr<Time>, std::string> Time::create(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond) {
#line 177 "/std/time/temporal.do"
    return ::doof_time::validate_time(hour, minute, second, nanosecond);
}
#line 181 "/std/time/temporal.do"
doof::Result<std::shared_ptr<Time>, std::string> Time::parse(const std::string& s) {
#line 182 "/std/time/temporal.do"
    return ::doof_time::parse_time(s);
}
#line 190 "/std/time/temporal.do"
std::shared_ptr<Time> Time::plusHours(int32_t n) {
    return ::doof_time::time_add_nanos(this->hour, this->minute, this->second, this->nanosecond, (static_cast<int64_t>(n) * 3600000000000LL));
}
#line 191 "/std/time/temporal.do"
std::shared_ptr<Time> Time::plusMinutes(int32_t n) {
    return ::doof_time::time_add_nanos(this->hour, this->minute, this->second, this->nanosecond, (static_cast<int64_t>(n) * 60000000000LL));
}
#line 192 "/std/time/temporal.do"
std::shared_ptr<Time> Time::plusSeconds(int32_t n) {
    return ::doof_time::time_add_nanos(this->hour, this->minute, this->second, this->nanosecond, (static_cast<int64_t>(n) * 1000000000LL));
}
#line 193 "/std/time/temporal.do"
std::shared_ptr<Time> Time::plusNanos(int64_t n) {
    return ::doof_time::time_add_nanos(this->hour, this->minute, this->second, this->nanosecond, n);
}
#line 197 "/std/time/temporal.do"
int32_t Time::compareTo(const std::shared_ptr<Time>& other) {
#line 198 "/std/time/temporal.do"
    if (this->hour != other->hour) {
#line 198 "/std/time/temporal.do"
        return ((this->hour < other->hour) ? -1 : 1);
    }
#line 199 "/std/time/temporal.do"
    if (this->minute != other->minute) {
#line 199 "/std/time/temporal.do"
        return ((this->minute < other->minute) ? -1 : 1);
    }
#line 200 "/std/time/temporal.do"
    if (this->second != other->second) {
#line 200 "/std/time/temporal.do"
        return ((this->second < other->second) ? -1 : 1);
    }
#line 201 "/std/time/temporal.do"
    if (this->nanosecond != other->nanosecond) {
#line 201 "/std/time/temporal.do"
        return ((this->nanosecond < other->nanosecond) ? -1 : 1);
    }
#line 202 "/std/time/temporal.do"
    return 0;
}
#line 205 "/std/time/temporal.do"
bool Time::isBefore(const std::shared_ptr<Time>& other) {
    return (this->compareTo(other) < 0);
}
#line 206 "/std/time/temporal.do"
bool Time::isAfter(const std::shared_ptr<Time>& other) {
    return (this->compareTo(other) > 0);
}
#line 207 "/std/time/temporal.do"
bool Time::equals(const std::shared_ptr<Time>& other) {
    return ((((this->hour == other->hour) && (this->minute == other->minute)) && (this->second == other->second)) && (this->nanosecond == other->nanosecond));
}
#line 214 "/std/time/temporal.do"
std::string Time::toISOString() {
#line 215 "/std/time/temporal.do"
    auto base = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(this->hour), 2, U'\u0030')); _interpolation += ":"; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(this->minute), 2, U'\u0030')); _interpolation += ":"; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(this->second), 2, U'\u0030')); _interpolation += ""; return _interpolation; }());
#line 216 "/std/time/temporal.do"
    if (this->nanosecond == 0) {
#line 216 "/std/time/temporal.do"
        return base;
    }
#line 217 "/std/time/temporal.do"
    return ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(base); _interpolation += "."; _interpolation += doof::to_string(doof::string_trimEnd(doof::string_padStart(doof::to_string(this->nanosecond), 9, U'\u0030'), U'\u0030')); _interpolation += ""; return _interpolation; }());
}

#line 227 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::create(const std::shared_ptr<Date>& date, const std::shared_ptr<Time>& time) {
    return std::make_shared<DateTime>(date, time);
}
#line 229 "/std/time/temporal.do"
doof::Result<std::shared_ptr<DateTime>, std::string> DateTime::fromParts(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, int32_t nanosecond) {
#line 233 "/std/time/temporal.do"
    auto _try_value_9 = Date::create(year, month, day);
    if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
    const auto d = doof::success_value(_try_value_9);
#line 234 "/std/time/temporal.do"
    auto _try_value_10 = Time::create(hour, minute, second, nanosecond);
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_10))};
    const auto t = doof::success_value(_try_value_10);
#line 235 "/std/time/temporal.do"
    return doof::Success<std::shared_ptr<DateTime>>{ std::make_shared<DateTime>(d, t) };
}
#line 238 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::nowUTC() {
    return Instant::now()->toDateTime();
}
#line 241 "/std/time/temporal.do"
doof::Result<std::shared_ptr<DateTime>, std::string> DateTime::parse(const std::string& s) {
#line 242 "/std/time/temporal.do"
    return ::doof_time::parse_datetime(s);
}
#line 247 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::plusDays(int32_t n) {
    return std::make_shared<DateTime>(this->date->plusDays(n), time);
}
#line 248 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::minusDays(int32_t n) {
    return std::make_shared<DateTime>(this->date->minusDays(n), time);
}
#line 249 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::plusHours(int32_t n) {
    return ::doof_time::datetime_plus_nanos(this->date, this->time, (static_cast<int64_t>(n) * 3600000000000LL));
}
#line 250 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::plusMinutes(int32_t n) {
    return ::doof_time::datetime_plus_nanos(this->date, this->time, (static_cast<int64_t>(n) * 60000000000LL));
}
#line 251 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::plusSeconds(int32_t n) {
    return ::doof_time::datetime_plus_nanos(this->date, this->time, (static_cast<int64_t>(n) * 1000000000LL));
}
#line 252 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::plus(const std::shared_ptr<::std_::time::duration::Duration>& d) {
    return ::doof_time::datetime_plus_nanos(this->date, this->time, d->toNanos());
}
#line 253 "/std/time/temporal.do"
std::shared_ptr<DateTime> DateTime::minus(const std::shared_ptr<::std_::time::duration::Duration>& d) {
    return ::doof_time::datetime_plus_nanos(this->date, this->time, -d->toNanos());
}
#line 258 "/std/time/temporal.do"
std::shared_ptr<Instant> DateTime::toInstantUTC() {
    return ::doof_time::datetime_to_instant(this->date, this->time);
}
#line 261 "/std/time/temporal.do"
std::shared_ptr<Instant> DateTime::toInstant(const std::shared_ptr<TimeZone>& zone) {
    return ::doof_time::datetime_to_instant_in_zone(this->date, this->time, zone);
}
#line 263 "/std/time/temporal.do"
std::shared_ptr<ZonedDateTime> DateTime::atZone(const std::shared_ptr<TimeZone>& zone) {
    return ::doof_time::datetime_at_zone(this->shared_from_this(), zone);
}
#line 267 "/std/time/temporal.do"
int32_t DateTime::compareTo(const std::shared_ptr<DateTime>& other) {
#line 268 "/std/time/temporal.do"
    auto dc = this->date->compareTo(other->date);
#line 269 "/std/time/temporal.do"
    if (dc != 0) {
#line 269 "/std/time/temporal.do"
        return dc;
    }
#line 270 "/std/time/temporal.do"
    return this->time->compareTo(other->time);
}
#line 273 "/std/time/temporal.do"
bool DateTime::isBefore(const std::shared_ptr<DateTime>& other) {
    return (this->compareTo(other) < 0);
}
#line 274 "/std/time/temporal.do"
bool DateTime::isAfter(const std::shared_ptr<DateTime>& other) {
    return (this->compareTo(other) > 0);
}
#line 275 "/std/time/temporal.do"
bool DateTime::equals(const std::shared_ptr<DateTime>& other) {
    return (this->date->equals(other->date) && this->time->equals(other->time));
}
#line 280 "/std/time/temporal.do"
std::string DateTime::toISOString() {
    return ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(this->date->toISOString()); _interpolation += "T"; _interpolation += doof::to_string(this->time->toISOString()); _interpolation += ""; return _interpolation; }());
}

std::shared_ptr<TimeZone> TimeZone::UTC;
#line 289 "/std/time/temporal.do"
doof::Result<std::shared_ptr<TimeZone>, std::string> TimeZone::lookup(const std::string& id) {
    return ::doof_time::lookup_timezone(id);
}
#line 294 "/std/time/temporal.do"
std::shared_ptr<TimeZone> TimeZone::local() {
    return ::doof_time::system_timezone();
}
#line 299 "/std/time/temporal.do"
int32_t TimeZone::offsetSecondsAt(const std::shared_ptr<Instant>& instant) {
    return ::doof_time::zone_offset_at(this->id, instant->toEpochSeconds());
}
#line 302 "/std/time/temporal.do"
bool TimeZone::isDSTAt(const std::shared_ptr<Instant>& instant) {
    return ::doof_time::zone_dst_at(this->id, instant->toEpochSeconds());
}

#line 311 "/std/time/temporal.do"
std::shared_ptr<ZonedDateTime> ZonedDateTime::now(const std::shared_ptr<TimeZone>& zone) {
    return Instant::now()->toZonedDateTime(zone);
}
#line 312 "/std/time/temporal.do"
std::shared_ptr<ZonedDateTime> ZonedDateTime::nowUTC() {
    return Instant::now()->toZonedDateTime(TimeZone::UTC);
}
#line 316 "/std/time/temporal.do"
std::shared_ptr<Date> ZonedDateTime::date() {
    return this->dateTime->date;
}
#line 317 "/std/time/temporal.do"
std::shared_ptr<Time> ZonedDateTime::time() {
    return this->dateTime->time;
}
#line 318 "/std/time/temporal.do"
int32_t ZonedDateTime::offsetSeconds() {
    return this->zone->offsetSecondsAt(this->toInstant());
}
#line 322 "/std/time/temporal.do"
std::shared_ptr<Instant> ZonedDateTime::toInstant() {
    return this->dateTime->toInstant(this->zone);
}
#line 323 "/std/time/temporal.do"
std::shared_ptr<ZonedDateTime> ZonedDateTime::withZoneSameInstant(const std::shared_ptr<TimeZone>& newZone) {
    return this->toInstant()->toZonedDateTime(newZone);
}
#line 325 "/std/time/temporal.do"
std::shared_ptr<ZonedDateTime> ZonedDateTime::withZoneSameLocal(const std::shared_ptr<TimeZone>& newZone) {
    return std::make_shared<ZonedDateTime>(dateTime, newZone);
}
#line 327 "/std/time/temporal.do"
std::shared_ptr<DateTime> ZonedDateTime::toDateTime() {
    return this->dateTime;
}
#line 328 "/std/time/temporal.do"
std::shared_ptr<ZonedDateTime> ZonedDateTime::toUTC() {
    return this->withZoneSameInstant(TimeZone::UTC);
}
#line 332 "/std/time/temporal.do"
int32_t ZonedDateTime::compareTo(const std::shared_ptr<ZonedDateTime>& other) {
    return this->toInstant()->compareTo(other->toInstant());
}
#line 335 "/std/time/temporal.do"
bool ZonedDateTime::isBefore(const std::shared_ptr<ZonedDateTime>& other) {
    return this->toInstant()->isBefore(other->toInstant());
}
#line 336 "/std/time/temporal.do"
bool ZonedDateTime::isAfter(const std::shared_ptr<ZonedDateTime>& other) {
    return this->toInstant()->isAfter(other->toInstant());
}
#line 341 "/std/time/temporal.do"
std::string ZonedDateTime::toISOString() {
#line 342 "/std/time/temporal.do"
    auto offset = this->offsetSeconds();
#line 343 "/std/time/temporal.do"
    if (offset == 0) {
#line 344 "/std/time/temporal.do"
        return ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(this->dateTime->toISOString()); _interpolation += "Z"; return _interpolation; }());
    }
#line 347 "/std/time/temporal.do"
    auto sign = ((offset < 0) ? std::string("-") : std::string("+"));
#line 348 "/std/time/temporal.do"
    auto abs = ((offset < 0) ? -offset : offset);
#line 349 "/std/time/temporal.do"
    auto h = (abs / 3600);
#line 350 "/std/time/temporal.do"
    auto m = ((abs % 3600) / 60);
#line 351 "/std/time/temporal.do"
    auto suffix = ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(sign); _interpolation += ""; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(h), 2, U'\u0030')); _interpolation += ":"; _interpolation += doof::to_string(doof::string_padStart(doof::to_string(m), 2, U'\u0030')); _interpolation += ""; return _interpolation; }());
#line 352 "/std/time/temporal.do"
    return ([&]() -> std::string { std::string _interpolation = ""; _interpolation += doof::to_string(this->dateTime->toISOString()); _interpolation += ""; _interpolation += doof::to_string(suffix); _interpolation += ""; return _interpolation; }());
}
#line 381 "/std/time/temporal.do"
std::string httpWeekdayName(DayOfWeek day) {
#line 382 "/std/time/temporal.do"
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
#line 393 "/std/time/temporal.do"
std::string httpMonthName(int32_t month) {
#line 394 "/std/time/temporal.do"
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
#line 411 "/std/time/temporal.do"
std::optional<int32_t> httpMonthNumber(const std::string& text) {
#line 412 "/std/time/temporal.do"
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
#line 1 "<doof-generated>"

void __doof_initialize_module() {
        Instant::EPOCH = std::make_shared<Instant>(0LL);
        Date::MIN = std::make_shared<Date>(1, 1, 1);
        Date::MAX = std::make_shared<Date>(9999, 12, 31);
        Time::MIDNIGHT = std::make_shared<Time>(0, 0, 0, 0);
        Time::NOON = std::make_shared<Time>(12, 0, 0, 0);
        TimeZone::UTC = std::make_shared<TimeZone>(std::string("UTC"));
}
int64_t _systemNanosEpoch() {
    return ::doof_time::system_nanos_epoch();
}
doof::Result<std::shared_ptr<Instant>, std::string> _parseInstant(const std::string& s) {
    return ::doof_time::parse_instant(s);
}
std::shared_ptr<DateTime> _instantToDateTime(int64_t nanos) {
    return ::doof_time::instant_to_datetime(nanos);
}
std::shared_ptr<ZonedDateTime> _instantToZonedDateTime(int64_t nanos, const std::shared_ptr<TimeZone>& zone) {
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
std::shared_ptr<Date> _systemDateInZone(const std::shared_ptr<TimeZone>& zone) {
    return ::doof_time::system_date_in_zone(zone);
}
doof::Result<std::shared_ptr<Date>, std::string> _parseDate(const std::string& s) {
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
doof::Result<std::shared_ptr<Time>, std::string> _parseTime(const std::string& s) {
    return ::doof_time::parse_time(s);
}
std::shared_ptr<Time> _timeAddNanos(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond, int64_t nanos) {
    return ::doof_time::time_add_nanos(hour, minute, second, nanosecond, nanos);
}
doof::Result<std::shared_ptr<DateTime>, std::string> _parseDateTime(const std::string& s) {
    return ::doof_time::parse_datetime(s);
}
std::shared_ptr<DateTime> _dateTimePlusNanos(const std::shared_ptr<Date>& date, const std::shared_ptr<Time>& time, int64_t nanos) {
    return ::doof_time::datetime_plus_nanos(date, time, nanos);
}
std::shared_ptr<Instant> _dateTimeToInstant(const std::shared_ptr<Date>& date, const std::shared_ptr<Time>& time) {
    return ::doof_time::datetime_to_instant(date, time);
}
std::shared_ptr<Instant> _dateTimeToInstantInZone(const std::shared_ptr<Date>& date, const std::shared_ptr<Time>& time, const std::shared_ptr<TimeZone>& zone) {
    return ::doof_time::datetime_to_instant_in_zone(date, time, zone);
}
std::shared_ptr<ZonedDateTime> _dateTimeAtZone(const std::shared_ptr<DateTime>& dateTime, const std::shared_ptr<TimeZone>& zone) {
    return ::doof_time::datetime_at_zone(dateTime, zone);
}
doof::Result<std::shared_ptr<TimeZone>, std::string> _lookupTimeZone(const std::string& id) {
    return ::doof_time::lookup_timezone(id);
}
std::shared_ptr<TimeZone> _systemTimeZone() {
    return ::doof_time::system_timezone();
}
int32_t _zoneOffsetAt(const std::string& id, int64_t epochSeconds) {
    return ::doof_time::zone_offset_at(id, epochSeconds);
}
bool _zoneDSTAt(const std::string& id, int64_t epochSeconds) {
    return ::doof_time::zone_dst_at(id, epochSeconds);
}
}
