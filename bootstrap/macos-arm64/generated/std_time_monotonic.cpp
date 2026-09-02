#include "std_time_monotonic.hpp"

namespace std_::time::monotonic {
using namespace ::std_::time::duration;

std::shared_ptr<MonotonicInstant> MonotonicInstant::now() {
    return std::make_shared<MonotonicInstant>(::doof_time::monotonic_nanos());
}
std::shared_ptr<MonotonicInstant> MonotonicInstant::plus(const std::shared_ptr<::std_::time::duration::Duration>& duration) {
    return std::make_shared<MonotonicInstant>((this->ticksNanos + duration->toNanos()));
}
std::shared_ptr<MonotonicInstant> MonotonicInstant::minus(const std::shared_ptr<::std_::time::duration::Duration>& duration) {
    return std::make_shared<MonotonicInstant>((this->ticksNanos - duration->toNanos()));
}
std::shared_ptr<::std_::time::duration::Duration> MonotonicInstant::durationUntil(const std::shared_ptr<MonotonicInstant>& other) {
    return ::std_::time::duration::Duration::ofNanos((other->ticksNanos - this->ticksNanos));
}
std::shared_ptr<::std_::time::duration::Duration> MonotonicInstant::durationSince(const std::shared_ptr<MonotonicInstant>& other) {
    return ::std_::time::duration::Duration::ofNanos((this->ticksNanos - other->ticksNanos));
}
int32_t MonotonicInstant::compareTo(const std::shared_ptr<MonotonicInstant>& other) {
    if (this->ticksNanos < other->ticksNanos) {
        return -1;
    }
    if (this->ticksNanos > other->ticksNanos) {
        return 1;
    }
    return 0;
}
bool MonotonicInstant::isBefore(const std::shared_ptr<MonotonicInstant>& other) {
    return (this->ticksNanos < other->ticksNanos);
}
bool MonotonicInstant::isAfter(const std::shared_ptr<MonotonicInstant>& other) {
    return (this->ticksNanos > other->ticksNanos);
}
bool MonotonicInstant::equals(const std::shared_ptr<MonotonicInstant>& other) {
    return (this->ticksNanos == other->ticksNanos);
}
}
