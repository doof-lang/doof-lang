#include "std_time_stopwatch.hpp"
#include <cmath>
#include "std_time_duration.hpp"
#include "std_time_temporal.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::time::stopwatch {
using namespace ::std_::time::duration;
using namespace ::std_::time::temporal;

doof::JsonObject TimerError::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["message"] = doof::json_value(this->message);
    return _json;
}
doof::Result<std::shared_ptr<TimerError>, std::string> TimerError::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_message = _object->find("message");
    if (_iterator_message == _object->end()) { return doof::Failure<std::string>{"Missing required field \"message\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_message->second) : doof::json_is_string(_iterator_message->second)))) { return doof::Failure<std::string>{"Field \"message\" expected string but got " + std::string(doof::json_type_name(_iterator_message->second))}; }
    auto _field_message = (_lenient ? doof::json_as_string_lenient(_iterator_message->second) : doof::json_as_string(_iterator_message->second));
    return doof::Success<std::shared_ptr<TimerError>>{std::make_shared<TimerError>(_field_kind, _field_name, _field_message)};
}

doof::JsonObject TimerStats::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["count"] = doof::json_value(this->count);
    (*_json)["total"] = doof::json_value(this->total->toJsonObject());
    (*_json)["mean"] = doof::json_value(this->mean->toJsonObject());
    (*_json)["min"] = doof::json_value(this->min->toJsonObject());
    (*_json)["max"] = doof::json_value(this->max->toJsonObject());
    (*_json)["p95"] = doof::json_value(this->p95->toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<TimerStats>, std::string> TimerStats::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_count = _object->find("count");
    if (_iterator_count == _object->end()) { return doof::Failure<std::string>{"Missing required field \"count\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_count->second) : doof::json_is_number(_iterator_count->second)))) { return doof::Failure<std::string>{"Field \"count\" expected number but got " + std::string(doof::json_type_name(_iterator_count->second))}; }
    auto _field_count = (_lenient ? doof::json_as_int_lenient(_iterator_count->second) : doof::json_as_int(_iterator_count->second));
    auto _iterator_total = _object->find("total");
    if (_iterator_total == _object->end()) { return doof::Failure<std::string>{"Missing required field \"total\""}; }
    if (!(doof::json_is_object(_iterator_total->second))) { return doof::Failure<std::string>{"Field \"total\" expected object but got " + std::string(doof::json_type_name(_iterator_total->second))}; }
    auto _field_total = doof::success_value(::std_::time::duration::Duration::fromJsonValue(_iterator_total->second, _lenient));
    auto _iterator_mean = _object->find("mean");
    if (_iterator_mean == _object->end()) { return doof::Failure<std::string>{"Missing required field \"mean\""}; }
    if (!(doof::json_is_object(_iterator_mean->second))) { return doof::Failure<std::string>{"Field \"mean\" expected object but got " + std::string(doof::json_type_name(_iterator_mean->second))}; }
    auto _field_mean = doof::success_value(::std_::time::duration::Duration::fromJsonValue(_iterator_mean->second, _lenient));
    auto _iterator_min = _object->find("min");
    if (_iterator_min == _object->end()) { return doof::Failure<std::string>{"Missing required field \"min\""}; }
    if (!(doof::json_is_object(_iterator_min->second))) { return doof::Failure<std::string>{"Field \"min\" expected object but got " + std::string(doof::json_type_name(_iterator_min->second))}; }
    auto _field_min = doof::success_value(::std_::time::duration::Duration::fromJsonValue(_iterator_min->second, _lenient));
    auto _iterator_max = _object->find("max");
    if (_iterator_max == _object->end()) { return doof::Failure<std::string>{"Missing required field \"max\""}; }
    if (!(doof::json_is_object(_iterator_max->second))) { return doof::Failure<std::string>{"Field \"max\" expected object but got " + std::string(doof::json_type_name(_iterator_max->second))}; }
    auto _field_max = doof::success_value(::std_::time::duration::Duration::fromJsonValue(_iterator_max->second, _lenient));
    auto _iterator_p95 = _object->find("p95");
    if (_iterator_p95 == _object->end()) { return doof::Failure<std::string>{"Missing required field \"p95\""}; }
    if (!(doof::json_is_object(_iterator_p95->second))) { return doof::Failure<std::string>{"Field \"p95\" expected object but got " + std::string(doof::json_type_name(_iterator_p95->second))}; }
    auto _field_p95 = doof::success_value(::std_::time::duration::Duration::fromJsonValue(_iterator_p95->second, _lenient));
    return doof::Success<std::shared_ptr<TimerStats>>{std::make_shared<TimerStats>(_field_name, _field_count, _field_total, _field_mean, _field_min, _field_max, _field_p95)};
}

doof::JsonObject TimerSummary::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["entries"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->entries->size()); for (const auto& _element : *this->entries) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<TimerSummary>, std::string> TimerSummary::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_entries = _object->find("entries");
    if (_iterator_entries == _object->end()) { return doof::Failure<std::string>{"Missing required field \"entries\""}; }
    if (!(doof::json_is_array(_iterator_entries->second))) { return doof::Failure<std::string>{"Field \"entries\" expected array but got " + std::string(doof::json_type_name(_iterator_entries->second))}; }
    auto _field_entries = [&]() { const auto* _array = doof::json_as_array(_iterator_entries->second); auto _values = std::make_shared<std::vector<std::shared_ptr<TimerStats>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(TimerStats::fromJsonValue(_element, _lenient))); } return _values; }();
    return doof::Success<std::shared_ptr<TimerSummary>>{std::make_shared<TimerSummary>(_field_entries)};
}

void TimerBucket::record(std::shared_ptr<::std_::time::duration::Duration> duration) {
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
    return ::std_::time::duration::Duration::ofNanos((*this->durations)[index]);
}
void TimerBucket::insertSorted(int64_t nanos) {
    this->durations->push_back(nanos);
    auto index = (static_cast<int32_t>((this->durations)->size()) - 1);
    while ((index > 0) && ((*this->durations)[(index - 1)] > nanos)) {
        ((*this->durations)[index] = (*this->durations)[(index - 1)]);
        (index -= 1);
    }
    ((*this->durations)[index] = nanos);
}
doof::JsonObject TimerBucket::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["count"] = doof::json_value(this->count);
    (*_json)["totalNanos"] = doof::json_value(this->totalNanos);
    (*_json)["minNanos"] = doof::json_value(this->minNanos);
    (*_json)["maxNanos"] = doof::json_value(this->maxNanos);
    (*_json)["durations"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->durations->size()); for (const auto& _element : *this->durations) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<TimerBucket>, std::string> TimerBucket::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<int32_t> _field_count;
    if (auto _iterator_count = _object->find("count"); _iterator_count != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_count->second) : doof::json_is_number(_iterator_count->second)))) { return doof::Failure<std::string>{"Field \"count\" expected number but got " + std::string(doof::json_type_name(_iterator_count->second))}; }
        _field_count = (_lenient ? doof::json_as_int_lenient(_iterator_count->second) : doof::json_as_int(_iterator_count->second));
    } else {
        _field_count = int32_t{0};
    }
    std::optional<int64_t> _field_totalNanos;
    if (auto _iterator_totalNanos = _object->find("totalNanos"); _iterator_totalNanos != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_totalNanos->second) : doof::json_is_number(_iterator_totalNanos->second)))) { return doof::Failure<std::string>{"Field \"totalNanos\" expected number but got " + std::string(doof::json_type_name(_iterator_totalNanos->second))}; }
        _field_totalNanos = (_lenient ? doof::json_as_long_lenient(_iterator_totalNanos->second) : doof::json_as_long(_iterator_totalNanos->second));
    } else {
        _field_totalNanos = int64_t{0LL};
    }
    std::optional<int64_t> _field_minNanos;
    if (auto _iterator_minNanos = _object->find("minNanos"); _iterator_minNanos != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_minNanos->second) : doof::json_is_number(_iterator_minNanos->second)))) { return doof::Failure<std::string>{"Field \"minNanos\" expected number but got " + std::string(doof::json_type_name(_iterator_minNanos->second))}; }
        _field_minNanos = (_lenient ? doof::json_as_long_lenient(_iterator_minNanos->second) : doof::json_as_long(_iterator_minNanos->second));
    } else {
        _field_minNanos = int64_t{0LL};
    }
    std::optional<int64_t> _field_maxNanos;
    if (auto _iterator_maxNanos = _object->find("maxNanos"); _iterator_maxNanos != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_maxNanos->second) : doof::json_is_number(_iterator_maxNanos->second)))) { return doof::Failure<std::string>{"Field \"maxNanos\" expected number but got " + std::string(doof::json_type_name(_iterator_maxNanos->second))}; }
        _field_maxNanos = (_lenient ? doof::json_as_long_lenient(_iterator_maxNanos->second) : doof::json_as_long(_iterator_maxNanos->second));
    } else {
        _field_maxNanos = int64_t{0LL};
    }
    std::optional<std::shared_ptr<std::vector<int64_t>>> _field_durations;
    if (auto _iterator_durations = _object->find("durations"); _iterator_durations != _object->end()) {
        if (!(doof::json_is_array(_iterator_durations->second))) { return doof::Failure<std::string>{"Field \"durations\" expected array but got " + std::string(doof::json_type_name(_iterator_durations->second))}; }
        _field_durations = [&]() { const auto* _array = doof::json_as_array(_iterator_durations->second); auto _values = std::make_shared<std::vector<int64_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_long_lenient(_element) : doof::json_as_long(_element))); } return _values; }();
    } else {
        _field_durations = std::shared_ptr<std::vector<int64_t>>{std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{})};
    }
    return doof::Success<std::shared_ptr<TimerBucket>>{std::make_shared<TimerBucket>(_field_count.value(), _field_totalNanos.value(), _field_minNanos.value(), _field_maxNanos.value(), _field_durations.value())};
}

std::shared_ptr<StopwatchSpan> Stopwatch::measure(std::string name) {
    return std::make_shared<StopwatchSpan>(std::shared_ptr<Stopwatch>(this, [](Stopwatch*) {}), name, ::std_::time::temporal::Instant::now(), false, nullptr);
}
int32_t Stopwatch::count(std::string name) {
    auto _binding_value_1 = bucketFor(name);
    if (doof::is_null(_binding_value_1)) {
        const auto& bucket = _binding_value_1;
        return 0;
    }
    const auto bucket = doof::unwrap_optional(_binding_value_1);
    return bucket->count;
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::total(std::string name) {
    auto _try_value_2 = requireBucket(name);
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::shared_ptr<TimerError>>{doof::failure_error(_try_value_2)};
    const auto bucket = doof::success_value(_try_value_2);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->total() };
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::mean(std::string name) {
    auto _try_value_3 = requireBucket(name);
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::shared_ptr<TimerError>>{doof::failure_error(_try_value_3)};
    const auto bucket = doof::success_value(_try_value_3);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->mean() };
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::min(std::string name) {
    auto _try_value_4 = requireBucket(name);
    if (doof::is_failure(_try_value_4)) return doof::Failure<std::shared_ptr<TimerError>>{doof::failure_error(_try_value_4)};
    const auto bucket = doof::success_value(_try_value_4);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->min() };
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::max(std::string name) {
    auto _try_value_5 = requireBucket(name);
    if (doof::is_failure(_try_value_5)) return doof::Failure<std::shared_ptr<TimerError>>{doof::failure_error(_try_value_5)};
    const auto bucket = doof::success_value(_try_value_5);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->max() };
}
doof::Result<std::shared_ptr<::std_::time::duration::Duration>, std::shared_ptr<TimerError>> Stopwatch::p95(std::string name) {
    auto _try_value_6 = requireBucket(name);
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::shared_ptr<TimerError>>{doof::failure_error(_try_value_6)};
    const auto bucket = doof::success_value(_try_value_6);
    return doof::Success<std::shared_ptr<::std_::time::duration::Duration>>{ bucket->p95() };
}
std::shared_ptr<TimerSummary> Stopwatch::summary() {
    const std::shared_ptr<std::vector<std::shared_ptr<TimerStats>>> entries = std::make_shared<std::vector<std::shared_ptr<TimerStats>>>(std::vector<std::shared_ptr<TimerStats>>{});
    const auto& _iterable_7 = this->timers;
    for (const auto& [name, bucket] : *_iterable_7) {
        entries->push_back(std::make_shared<TimerStats>(name, bucket->count, bucket->total(), bucket->mean(), bucket->min(), bucket->max(), bucket->p95()));
    }
    return std::make_shared<TimerSummary>(doof::array_buildReadonly(entries, "", 0));
}
void Stopwatch::record(std::string name, std::shared_ptr<::std_::time::duration::Duration> duration) {
    auto bucket = (doof::is_null(bucketFor(name)) ? std::make_shared<TimerBucket>(0, 0LL, 0LL, 0LL, std::make_shared<std::vector<int64_t>>(std::vector<int64_t>{})) : doof::unwrap_optional(bucketFor(name)));
    if (!(this->timers->find(name) != this->timers->end())) {
        doof::map_set(this->timers, name, bucket, "", 0);
    }
    bucket->record(duration);
}
std::shared_ptr<TimerBucket> Stopwatch::bucketFor(std::string name) {
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
doof::Result<std::shared_ptr<TimerBucket>, std::shared_ptr<TimerError>> Stopwatch::requireBucket(std::string name) {
    auto _binding_value_8 = bucketFor(name);
    if (doof::is_null(_binding_value_8)) {
        const auto& bucket = _binding_value_8;
        return doof::Failure<std::shared_ptr<TimerError>>{ missingTimer(name) };
    }
    const auto bucket = doof::unwrap_optional(_binding_value_8);
    return doof::Success<std::shared_ptr<TimerBucket>>{ bucket };
}
doof::JsonObject Stopwatch::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["timers"] = [&]() { auto _object_value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *this->timers) { (*_object_value)[_entry.first] = doof::json_value(_entry.second->toJsonObject()); } return doof::json_value(_object_value); }();
    return _json;
}
doof::Result<std::shared_ptr<Stopwatch>, std::string> Stopwatch::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>>> _field_timers;
    if (auto _iterator_timers = _object->find("timers"); _iterator_timers != _object->end()) {
        if (!(doof::json_is_object(_iterator_timers->second))) { return doof::Failure<std::string>{"Field \"timers\" expected object but got " + std::string(doof::json_type_name(_iterator_timers->second))}; }
        _field_timers = [&]() { const auto* _object_value = doof::json_as_object(_iterator_timers->second); auto _values = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = doof::success_value(TimerBucket::fromJsonValue(_entry.second, _lenient)); } return _values; }();
    } else {
        _field_timers = std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>>{std::make_shared<doof::ordered_map<std::string, std::shared_ptr<TimerBucket>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<TimerBucket>>>{})};
    }
    return doof::Success<std::shared_ptr<Stopwatch>>{std::make_shared<Stopwatch>(_field_timers.value())};
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
doof::JsonObject StopwatchSpan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["stopwatch"] = doof::json_value(this->stopwatch->toJsonObject());
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["startedAt"] = doof::json_value(this->startedAt->toJsonObject());
    (*_json)["finished"] = doof::json_value(this->finished);
    (*_json)["finishedDuration"] = (this->finishedDuration ? doof::json_value(this->finishedDuration->toJsonObject()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<StopwatchSpan>, std::string> StopwatchSpan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_stopwatch = _object->find("stopwatch");
    if (_iterator_stopwatch == _object->end()) { return doof::Failure<std::string>{"Missing required field \"stopwatch\""}; }
    if (!(doof::json_is_object(_iterator_stopwatch->second))) { return doof::Failure<std::string>{"Field \"stopwatch\" expected object but got " + std::string(doof::json_type_name(_iterator_stopwatch->second))}; }
    auto _field_stopwatch = doof::success_value(Stopwatch::fromJsonValue(_iterator_stopwatch->second, _lenient));
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_startedAt = _object->find("startedAt");
    if (_iterator_startedAt == _object->end()) { return doof::Failure<std::string>{"Missing required field \"startedAt\""}; }
    if (!(doof::json_is_object(_iterator_startedAt->second))) { return doof::Failure<std::string>{"Field \"startedAt\" expected object but got " + std::string(doof::json_type_name(_iterator_startedAt->second))}; }
    auto _field_startedAt = doof::success_value(::std_::time::temporal::Instant::fromJsonValue(_iterator_startedAt->second, _lenient));
    std::optional<bool> _field_finished;
    if (auto _iterator_finished = _object->find("finished"); _iterator_finished != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_finished->second) : doof::json_is_boolean(_iterator_finished->second)))) { return doof::Failure<std::string>{"Field \"finished\" expected boolean but got " + std::string(doof::json_type_name(_iterator_finished->second))}; }
        _field_finished = (_lenient ? doof::json_as_bool_lenient(_iterator_finished->second) : doof::json_as_bool(_iterator_finished->second));
    } else {
        _field_finished = bool{false};
    }
    std::optional<std::shared_ptr<::std_::time::duration::Duration>> _field_finishedDuration;
    if (auto _iterator_finishedDuration = _object->find("finishedDuration"); _iterator_finishedDuration != _object->end()) {
        if (!(doof::json_is_null(_iterator_finishedDuration->second) || doof::json_is_object(_iterator_finishedDuration->second))) { return doof::Failure<std::string>{"Field \"finishedDuration\" expected object or null but got " + std::string(doof::json_type_name(_iterator_finishedDuration->second))}; }
        _field_finishedDuration = (doof::json_is_null(_iterator_finishedDuration->second) ? nullptr : doof::success_value(::std_::time::duration::Duration::fromJsonValue(_iterator_finishedDuration->second, _lenient)));
    } else {
        _field_finishedDuration = std::shared_ptr<::std_::time::duration::Duration>{nullptr};
    }
    return doof::Success<std::shared_ptr<StopwatchSpan>>{std::make_shared<StopwatchSpan>(_field_stopwatch, _field_name, _field_startedAt, _field_finished.value(), _field_finishedDuration.value())};
}
std::shared_ptr<TimerError> missingTimer(std::string name) {
    return std::make_shared<TimerError>(std::string("MissingTimer"), name, std::string("No timings recorded for '") + doof::to_string(name) + std::string("'"));
}
}
