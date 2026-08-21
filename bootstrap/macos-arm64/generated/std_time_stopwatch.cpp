#include "std_time_stopwatch.hpp"

namespace std_::time::stopwatch {
using namespace ::std_::time::duration;
using namespace ::std_::time::temporal;




void TimerBucket::record(const std::shared_ptr<::std_::time::duration::Duration>& duration) {
    auto nanos = duration->toNanos();
    if (this->count == 0) {
        (this->minNanos = nanos);
        (this->maxNanos = nanos);
    } else {
        if (nanos < this->minNanos) {
            (this->minNanos = nanos);
        }
        if (nanos > this->maxNanos) {
            (this->maxNanos = nanos);
        }
    }
    (this->count += 1);
    (this->totalNanos += nanos);
    insertSorted(nanos);
}
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::total() {
    return ::std_::time::duration::Duration::ofNanos(this->totalNanos);
}
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::mean() {
    return ::std_::time::duration::Duration::ofNanos((this->totalNanos / static_cast<int64_t>(this->count)));
}
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::min() {
    return ::std_::time::duration::Duration::ofNanos(this->minNanos);
}
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::max() {
    return ::std_::time::duration::Duration::ofNanos(this->maxNanos);
}
std::shared_ptr<::std_::time::duration::Duration> TimerBucket::p95() {
    auto index = ((((this->count * 95) + 99) / 100) - 1);
    return ::std_::time::duration::Duration::ofNanos(doof::array_at(this->durations, index, "stopwatch", 53));
}
void TimerBucket::insertSorted(int64_t nanos) {
    this->durations->push_back(nanos);
    auto index = (static_cast<int32_t>((this->durations)->size()) - 1);
    while ((index > 0) && (doof::array_at(this->durations, (index - 1), "stopwatch", 60) > nanos)) {
        (doof::array_at(this->durations, index, "stopwatch", 61) = doof::array_at(this->durations, (index - 1), "stopwatch", 61));
        (index -= 1);
    }
    (doof::array_at(this->durations, index, "stopwatch", 65) = nanos);
}

std::shared_ptr<StopwatchSpan> Stopwatch::measure(const std::string& name) {
    return std::make_shared<StopwatchSpan>(std::shared_ptr<Stopwatch>(this, [](Stopwatch*) {}), name, ::std_::time::temporal::Instant::now(), false, nullptr);
}
int32_t Stopwatch::count(const std::string& name) {
    auto _binding_value_1 = bucketFor(name);
    if (doof::is_null(_binding_value_1)) {
        const auto& bucket = _binding_value_1;
        return 0;
    }
    const auto bucket = doof::unwrap_optional(_binding_value_1);
    return bucket->count;
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::total(const std::string& name) {
    auto _try_value_2 = requireBucket(name);
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_2))};
    const auto bucket = doof::success_value(_try_value_2);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->total() };
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::mean(const std::string& name) {
    auto _try_value_3 = requireBucket(name);
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_3))};
    const auto bucket = doof::success_value(_try_value_3);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->mean() };
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::min(const std::string& name) {
    auto _try_value_4 = requireBucket(name);
    if (doof::is_failure(_try_value_4)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_4))};
    const auto bucket = doof::success_value(_try_value_4);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->min() };
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::max(const std::string& name) {
    auto _try_value_5 = requireBucket(name);
    if (doof::is_failure(_try_value_5)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_5))};
    const auto bucket = doof::success_value(_try_value_5);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->max() };
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::p95(const std::string& name) {
    auto _try_value_6 = requireBucket(name);
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::shared_ptr<TimerError>>{doof::variant_promote<std::shared_ptr<TimerError>>(doof::failure_error(_try_value_6))};
    const auto bucket = doof::success_value(_try_value_6);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->p95() };
}
std::shared_ptr<TimerSummary> Stopwatch::summary() {
    const std::shared_ptr<std::vector<std::shared_ptr<TimerStats>>> entries = std::make_shared<std::vector<std::shared_ptr<TimerStats>>>(std::vector<std::shared_ptr<TimerStats>>{});
    const auto& _iterable_8 = this->timers;
    for (const auto& [name, bucket] : *_iterable_8) {
        entries->push_back(std::make_shared<TimerStats>(name, bucket->count, bucket->total(), bucket->mean(), bucket->min(), bucket->max(), bucket->p95()));
    }
    return std::make_shared<TimerSummary>(doof::array_drainToReadonly(entries, "", 0));
}
void Stopwatch::record(const std::string& name, const std::shared_ptr<::std_::time::duration::Duration>& duration) {
    auto bucket = [&]() -> std::shared_ptr<TimerBucket> { auto _coalesce_9 = bucketFor(name); if (doof::is_null(_coalesce_9)) return std::make_shared<TimerBucket>(0, 0LL, 0LL, 0LL, std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{})); return doof::unwrap_optional(_coalesce_9); }();
    if (![&]() -> bool { auto _map_has_10 = this->timers; return _map_has_10->find(name) != _map_has_10->end(); }()) {
        doof::map_set(this->timers, name, bucket, "", 0);
    }
    bucket->record(duration);
}
std::shared_ptr<TimerBucket> Stopwatch::bucketFor(const std::string& name) {
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
doof::Result<std::shared_ptr<TimerBucket>, std::shared_ptr<TimerError>> Stopwatch::requireBucket(const std::string& name) {
    auto _binding_value_11 = bucketFor(name);
    if (doof::is_null(_binding_value_11)) {
        const auto& bucket = _binding_value_11;
        return doof::Failure<std::shared_ptr<TimerError>>{ missingTimer(name) };
    }
    const auto bucket = doof::unwrap_optional(_binding_value_11);
    return doof::Success<std::shared_ptr<TimerBucket>>{ bucket };
}

std::shared_ptr<::std_::time::duration::Duration> StopwatchSpan::finish() {
    if (this->finished) {
        return doof::unwrap_optional(this->finishedDuration);
    }
    auto elapsed = this->startedAt->durationUntil(::std_::time::temporal::Instant::now());
    this->stopwatch->record(this->name, elapsed);
    (this->finished = true);
    (this->finishedDuration = elapsed);
    return elapsed;
}
std::shared_ptr<TimerError> missingTimer(const std::string& name) {
    return std::make_shared<TimerError>(std::string("MissingTimer"), name, ([&]() -> std::string { std::string _interpolation = "No timings recorded for '"; _interpolation += doof::to_string(name); _interpolation += "'"; return _interpolation; }()));
}
}
