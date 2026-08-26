#include "std_time_stopwatch.hpp"

namespace std_::time::stopwatch {
using namespace ::std_::time::duration;
using namespace ::std_::time::temporal;




#line 31 "/std/time/stopwatch.do"
void TimerBucket::record(const std::shared_ptr<::std_::time::duration::Duration>& duration) {
#line 32 "/std/time/stopwatch.do"
    auto nanos = duration->toNanos();
#line 33 "/std/time/stopwatch.do"
    if (this->count == 0) {
#line 34 "/std/time/stopwatch.do"
        (this->minNanos = nanos);
#line 35 "/std/time/stopwatch.do"
        (this->maxNanos = nanos);
    } else {
#line 37 "/std/time/stopwatch.do"
        if (nanos < this->minNanos) {
#line 37 "/std/time/stopwatch.do"
            (this->minNanos = nanos);
        }
#line 38 "/std/time/stopwatch.do"
        if (nanos > this->maxNanos) {
#line 38 "/std/time/stopwatch.do"
            (this->maxNanos = nanos);
        }
    }
#line 41 "/std/time/stopwatch.do"
    (this->count += 1);
#line 42 "/std/time/stopwatch.do"
    (this->totalNanos += nanos);
#line 43 "/std/time/stopwatch.do"
    insertSorted(nanos);
}
#line 46 "/std/time/stopwatch.do"
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::total() {
    return ::std_::time::duration::Duration::ofNanos(this->totalNanos);
}
#line 47 "/std/time/stopwatch.do"
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::mean() {
    return ::std_::time::duration::Duration::ofNanos((this->totalNanos / static_cast<int64_t>(this->count)));
}
#line 48 "/std/time/stopwatch.do"
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::min() {
    return ::std_::time::duration::Duration::ofNanos(this->minNanos);
}
#line 49 "/std/time/stopwatch.do"
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::max() {
    return ::std_::time::duration::Duration::ofNanos(this->maxNanos);
}
#line 51 "/std/time/stopwatch.do"
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::p95() {
#line 52 "/std/time/stopwatch.do"
    auto index = ((((this->count * 95) + 99) / 100) - 1);
#line 53 "/std/time/stopwatch.do"
    return ::std_::time::duration::Duration::ofNanos(doof::array_at(this->durations, index, "stopwatch", 53));
}
#line 56 "/std/time/stopwatch.do"
void TimerBucket::insertSorted(int64_t nanos) {
#line 57 "/std/time/stopwatch.do"
    this->durations->push_back(nanos);
#line 58 "/std/time/stopwatch.do"
    auto index = (static_cast<int32_t>((this->durations)->size()) - 1);
#line 60 "/std/time/stopwatch.do"
    while ((index > 0) && (doof::array_at(this->durations, (index - 1), "stopwatch", 60) > nanos)) {
#line 61 "/std/time/stopwatch.do"
        (doof::array_at(this->durations, index, "stopwatch", 61) = doof::array_at(this->durations, (index - 1), "stopwatch", 61));
#line 62 "/std/time/stopwatch.do"
        (index -= 1);
    }
#line 65 "/std/time/stopwatch.do"
    (doof::array_at(this->durations, index, "stopwatch", 65) = nanos);
}

#line 72 "/std/time/stopwatch.do"
std::shared_ptr<StopwatchSpan> Stopwatch::measure(const std::string& name) {
#line 73 "/std/time/stopwatch.do"
    return std::make_shared<StopwatchSpan>(std::shared_ptr<Stopwatch>(this, [](Stopwatch*) {}), name, ::std_::time::temporal::Instant::now(), false, nullptr);
}
#line 80 "/std/time/stopwatch.do"
int32_t Stopwatch::count(const std::string& name) {
#line 81 "/std/time/stopwatch.do"
    auto _binding_value_1 = bucketFor(name);
    if (doof::is_null(_binding_value_1)) {
        const auto& bucket = _binding_value_1;
#line 81 "/std/time/stopwatch.do"
        return 0;
    }
    const auto bucket = doof::unwrap_optional(_binding_value_1);
#line 82 "/std/time/stopwatch.do"
    return bucket->count;
}
#line 85 "/std/time/stopwatch.do"
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::total(const std::string& name) {
#line 86 "/std/time/stopwatch.do"
    auto _try_value_2 = requireBucket(name);
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_2))};
    const auto bucket = doof::success_value(_try_value_2);
#line 87 "/std/time/stopwatch.do"
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->total() };
}
#line 90 "/std/time/stopwatch.do"
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::mean(const std::string& name) {
#line 91 "/std/time/stopwatch.do"
    auto _try_value_3 = requireBucket(name);
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_3))};
    const auto bucket = doof::success_value(_try_value_3);
#line 92 "/std/time/stopwatch.do"
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->mean() };
}
#line 95 "/std/time/stopwatch.do"
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::min(const std::string& name) {
#line 96 "/std/time/stopwatch.do"
    auto _try_value_4 = requireBucket(name);
    if (doof::is_failure(_try_value_4)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_4))};
    const auto bucket = doof::success_value(_try_value_4);
#line 97 "/std/time/stopwatch.do"
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->min() };
}
#line 100 "/std/time/stopwatch.do"
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::max(const std::string& name) {
#line 101 "/std/time/stopwatch.do"
    auto _try_value_5 = requireBucket(name);
    if (doof::is_failure(_try_value_5)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_5))};
    const auto bucket = doof::success_value(_try_value_5);
#line 102 "/std/time/stopwatch.do"
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->max() };
}
#line 105 "/std/time/stopwatch.do"
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::p95(const std::string& name) {
#line 106 "/std/time/stopwatch.do"
    auto _try_value_6 = requireBucket(name);
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_6))};
    const auto bucket = doof::success_value(_try_value_6);
#line 107 "/std/time/stopwatch.do"
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->p95() };
}
#line 110 "/std/time/stopwatch.do"
std::shared_ptr<TimerSummary> Stopwatch::summary() {
#line 111 "/std/time/stopwatch.do"
    const std::shared_ptr<std::vector<std::shared_ptr<TimerStats>>> entries = std::make_shared<std::vector<std::shared_ptr<TimerStats>>>(std::vector<std::shared_ptr<TimerStats>>{});
#line 113 "/std/time/stopwatch.do"
    const auto& _iterable_8 = this->timers;
    for (const auto& [name, bucket] : *_iterable_8) {
#line 114 "/std/time/stopwatch.do"
        entries->push_back(std::make_shared<TimerStats>(name, bucket->count, bucket->total(), bucket->mean(), bucket->min(), bucket->max(), bucket->p95()));
    }
#line 125 "/std/time/stopwatch.do"
    return std::make_shared<TimerSummary>(doof::array_drainToReadonly(entries, "", 0));
}
#line 130 "/std/time/stopwatch.do"
void Stopwatch::record(const std::string& name, const std::shared_ptr<::std_::time::duration::Duration>& duration) {
#line 131 "/std/time/stopwatch.do"
    auto bucket = [&]() -> std::shared_ptr<TimerBucket> { auto _coalesce_9 = bucketFor(name); if (doof::is_null(_coalesce_9)) return std::make_shared<TimerBucket>(0, 0LL, 0LL, 0LL, std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{})); return doof::unwrap_optional(_coalesce_9); }();
#line 132 "/std/time/stopwatch.do"
    if (![&]() -> bool { auto _map_has_10 = this->timers; return _map_has_10->find(name) != _map_has_10->end(); }()) {
#line 133 "/std/time/stopwatch.do"
        doof::map_set(this->timers, name, bucket, "", 0);
    }
#line 135 "/std/time/stopwatch.do"
    bucket->record(duration);
}
#line 138 "/std/time/stopwatch.do"
std::shared_ptr<TimerBucket> Stopwatch::bucketFor(const std::string& name) {
#line 139 "/std/time/stopwatch.do"
    return [&]() -> std::shared_ptr<TimerBucket> {
    auto _case_subject = doof::map_get(this->timers, name, "", 0);
    if (std::holds_alternative<doof::Success<std::shared_ptr<TimerBucket>>>(_case_subject)) {
        const auto& s = std::get<doof::Success<std::shared_ptr<TimerBucket>>>(_case_subject);
        return s.value;
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        return nullptr;
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
#line 145 "/std/time/stopwatch.do"
doof::Result<std::shared_ptr<TimerBucket>, std::shared_ptr<TimerError>> Stopwatch::requireBucket(const std::string& name) {
#line 146 "/std/time/stopwatch.do"
    auto _binding_value_11 = bucketFor(name);
    if (doof::is_null(_binding_value_11)) {
        const auto& bucket = _binding_value_11;
#line 147 "/std/time/stopwatch.do"
        return doof::Failure<std::shared_ptr<TimerError>>{ missingTimer(name) };
    }
    const auto bucket = doof::unwrap_optional(_binding_value_11);
#line 149 "/std/time/stopwatch.do"
    return doof::Success<std::shared_ptr<TimerBucket>>{ bucket };
}

#line 160 "/std/time/stopwatch.do"
std::shared_ptr<::std_::time::duration::Duration> StopwatchSpan::finish() {
#line 161 "/std/time/stopwatch.do"
    if (this->finished) {
#line 162 "/std/time/stopwatch.do"
        return doof::unwrap_optional(this->finishedDuration);
    }
#line 165 "/std/time/stopwatch.do"
    auto elapsed = this->startedAt->durationUntil(::std_::time::temporal::Instant::now());
#line 166 "/std/time/stopwatch.do"
    this->stopwatch->record(this->name, elapsed);
#line 167 "/std/time/stopwatch.do"
    (this->finished = true);
#line 168 "/std/time/stopwatch.do"
    (this->finishedDuration = elapsed);
#line 169 "/std/time/stopwatch.do"
    return elapsed;
}
#line 177 "/std/time/stopwatch.do"
std::shared_ptr<TimerError> missingTimer(const std::string& name) {
#line 178 "/std/time/stopwatch.do"
    return std::make_shared<TimerError>(std::string("MissingTimer"), name, ([&]() -> std::string { std::string _interpolation = "No timings recorded for '"; _interpolation += doof::to_string(name); _interpolation += "'"; return _interpolation; }()));
}
#line 1 "<doof-generated>"
}
