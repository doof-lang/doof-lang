#pragma once

// doof_runtime.hpp — Runtime support for transpiled Doof code
// Source template for the generated doof_runtime.hpp header.

#include <algorithm>
#include <chrono>
#include <cerrno>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <condition_variable>
#include <cmath>
#include <exception>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <queue>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <unordered_map>
#include <variant>
#include <vector>

/* __DOOF_OBSERVER_PLATFORM_SUPPORT__ */

namespace doof {

[[noreturn]] inline void panic(const std::string& msg);

// ============================================================================
// Metrics — process-local counters
// ============================================================================

namespace metrics {

inline std::unordered_map<std::string, int64_t> _counters;
inline std::mutex _counters_mutex;

inline void increment_counter(const std::string& key, int64_t value) {
    std::lock_guard<std::mutex> lock(_counters_mutex);
    _counters[key] += value;
}

inline std::vector<std::pair<std::string, int64_t>> snapshot_pairs() {
    std::vector<std::pair<std::string, int64_t>> snapshot;
    {
        std::lock_guard<std::mutex> lock(_counters_mutex);
        snapshot.reserve(_counters.size());
        for (const auto& item : _counters) {
            snapshot.push_back(item);
        }
    }

    std::sort(snapshot.begin(), snapshot.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    return snapshot;
}

inline std::string snapshot_prometheus() {
    const auto snapshot = snapshot_pairs();
    std::ostringstream out;
    for (const auto& item : snapshot) {
        out << item.first << " " << item.second << "\n";
    }
    return out.str();
}

} // namespace metrics

/* __DOOF_OBSERVER_RUNTIME_SUPPORT__ */

// ============================================================================
// Panic — unrecoverable error
// ============================================================================

class Panic final {
    std::string message_;
public:
    explicit Panic(std::string msg) : message_(std::move(msg)) {}
    const char* what() const noexcept { return message_.c_str(); }
    const std::string& message() const noexcept { return message_; }
};

// Runtime carrier for Doof's uninhabited `never` type. No value can be
// constructed; the conversion surface exists only so unreachable expressions
// remain well-typed when C++ checks their surrounding Doof value context.
class Never final {
public:
    Never() = delete;
    Never(const Never&) = delete;
    Never& operator=(const Never&) = delete;

    template <typename T>
    [[noreturn]] operator T() const {
        std::abort();
    }
};

[[noreturn]] inline void panic(const std::string& msg) {
    throw Panic(msg);
}

[[noreturn]] inline void panic_at(const char* file, int32_t line, const std::string& msg) {
    panic(std::string(file) + ":" + std::to_string(line) + ": " + msg);
}

[[noreturn]] inline void unreachable() {
#if defined(_MSC_VER)
    __assume(false);
    std::abort();
#elif defined(__GNUC__) || defined(__clang__)
    __builtin_unreachable();
#else
    std::abort();
#endif
}

inline void assert_(bool condition, const std::string& message) {
    if (!condition) {
        panic("Assertion failed: " + message);
    }
}

inline void assert_at(const char* file, int32_t line, bool condition, const std::string& message) {
    if (!condition) {
        panic_at(file, line, "Assertion failed: " + message);
    }
}

struct SourceLocation {
    const std::string fileName;
    const int32_t line;
    const std::string functionName;

    SourceLocation(std::string fileNameValue, int32_t lineValue, std::string functionNameValue = "<module>")
        : fileName(std::move(fileNameValue)),
          line(lineValue),
          functionName(std::move(functionNameValue)) {}
};

namespace detail {
class CallbackDomain {
public:
    virtual ~CallbackDomain() = default;
    virtual void enqueue_callback(std::function<void()> task) = 0;
};

inline thread_local CallbackDomain* active_actor_domain = nullptr;

class ActiveActorScope {
    CallbackDomain* previous_;
public:
    explicit ActiveActorScope(CallbackDomain* actor)
        : previous_(active_actor_domain) {
        active_actor_domain = actor;
    }

    ~ActiveActorScope() {
        active_actor_domain = previous_;
    }
};

class ApplicationDomain final : public CallbackDomain {
public:
    static ApplicationDomain& shared() {
        static ApplicationDomain domain;
        return domain;
    }

    static bool is_application_domain(CallbackDomain* domain) {
        return domain == &shared();
    }

    void enqueue_callback(std::function<void()> task) override {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            mailbox_.push(std::move(task));
        }
        notify_ready();
    }

    int32_t drain_ready() {
        int32_t dispatched = 0;
        while (true) {
            std::function<void()> task;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (mailbox_.empty()) {
                    return dispatched;
                }
                task = std::move(mailbox_.front());
                mailbox_.pop();
            }

            ActiveActorScope active(this);
            task();
            ++dispatched;
        }
    }

    bool wait_and_dispatch_one() {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            ready_.wait(lock, [this] {
                return !mailbox_.empty() || keep_alive_count_ == 0;
            });
            if (mailbox_.empty()) {
                return false;
            }
            task = std::move(mailbox_.front());
            mailbox_.pop();
        }

        ActiveActorScope active(this);
        task();
        return true;
    }

    void add_keep_alive_source(bool keeps_alive) {
        if (!keeps_alive) {
            return;
        }
        std::lock_guard<std::mutex> lock(mutex_);
        ++keep_alive_count_;
    }

    void remove_keep_alive_source(bool keeps_alive) {
        if (!keeps_alive) {
            return;
        }
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (keep_alive_count_ > 0) {
                --keep_alive_count_;
            }
        }
        notify_ready();
    }

    void set_wake_handler(std::function<void()> handler) {
        std::lock_guard<std::mutex> lock(mutex_);
        wake_handler_ = std::move(handler);
    }

private:
    ApplicationDomain() = default;

    void notify_ready() {
        std::function<void()> wake_handler;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            wake_handler = wake_handler_;
        }

        ready_.notify_all();
        if (wake_handler) {
            wake_handler();
        }
    }

    std::mutex mutex_;
    std::condition_variable ready_;
    std::queue<std::function<void()>> mailbox_;
    int64_t keep_alive_count_ = 0;
    std::function<void()> wake_handler_;
};
} // namespace detail

inline detail::CallbackDomain* current_actor_domain() {
    return detail::active_actor_domain;
}

// ============================================================================
// Runtime scheduler — bounded CPU execution for async and actor work
// ============================================================================

struct RuntimeSchedulerOptions {
    std::size_t maximum_cpu_parallelism;
    std::size_t retained_worker_count;
    std::chrono::milliseconds excess_worker_idle_timeout;

    RuntimeSchedulerOptions()
        : maximum_cpu_parallelism([] {
              const auto detected = std::thread::hardware_concurrency();
              return static_cast<std::size_t>(detected == 0 ? 1 : detected);
          }()),
          retained_worker_count(maximum_cpu_parallelism),
          excess_worker_idle_timeout(std::chrono::seconds(30)) {}
};

namespace detail {

struct RuntimeSchedulerSnapshot {
    std::size_t active_cpu_tokens;
    std::size_t live_worker_threads;
    std::size_t idle_worker_threads;
    std::size_t pending_jobs;
    std::size_t reacquire_waiters;
};

class RuntimeScheduler {
    std::mutex mutex_;
    std::condition_variable ready_;
    std::queue<std::function<void()>> jobs_;
    RuntimeSchedulerOptions options_;
    bool started_ = false;
    std::size_t active_cpu_tokens_ = 0;
    std::size_t live_worker_threads_ = 0;
    std::size_t starting_worker_threads_ = 0;
    std::size_t idle_worker_threads_ = 0;
    std::size_t reacquire_waiters_ = 0;

    // Keep these initialized inline in-class. Apple Clang otherwise emits a
    // strong TLS wrapper in every generated translation unit.
    inline static thread_local RuntimeScheduler* current_worker_scheduler_ = nullptr;
    inline static thread_local bool current_worker_holds_token_ = false;

    bool can_claim_job_locked() const {
        return !jobs_.empty()
            && active_cpu_tokens_ < options_.maximum_cpu_parallelism
            && reacquire_waiters_ == 0;
    }

    void start_workers_locked() {
        if (jobs_.empty() || reacquire_waiters_ != 0) {
            return;
        }

        const auto token_capacity = options_.maximum_cpu_parallelism - active_cpu_tokens_;
        const auto desired = std::min(token_capacity, jobs_.size());
        while (idle_worker_threads_ + starting_worker_threads_ < desired) {
            ++live_worker_threads_;
            ++starting_worker_threads_;
            try {
                std::thread([this] { worker_loop(); }).detach();
            } catch (...) {
                --starting_worker_threads_;
                --live_worker_threads_;
                throw;
            }
        }
        ready_.notify_all();
    }

    void worker_loop() {
        std::unique_lock<std::mutex> lock(mutex_);
        --starting_worker_threads_;

        while (true) {
            ++idle_worker_threads_;
            if (live_worker_threads_ > options_.retained_worker_count) {
                const bool ready = ready_.wait_for(
                    lock,
                    options_.excess_worker_idle_timeout,
                    [this] { return can_claim_job_locked(); });
                if (!ready
                    && live_worker_threads_ > options_.retained_worker_count
                    && !can_claim_job_locked()) {
                    --idle_worker_threads_;
                    --live_worker_threads_;
                    ready_.notify_all();
                    return;
                }
            } else {
                ready_.wait(lock, [this] { return can_claim_job_locked(); });
            }
            --idle_worker_threads_;

            if (!can_claim_job_locked()) {
                continue;
            }

            auto job = std::move(jobs_.front());
            jobs_.pop();
            ++active_cpu_tokens_;
            start_workers_locked();

            current_worker_scheduler_ = this;
            current_worker_holds_token_ = true;
            lock.unlock();
            try {
                job();
            } catch (...) {
                // Every language-facing submission boundary records failures.
                // Keep an unexpected native exception from destroying a worker.
            }
            lock.lock();

            if (!current_worker_holds_token_) {
                ++reacquire_waiters_;
                ready_.wait(lock, [this] {
                    return active_cpu_tokens_ < options_.maximum_cpu_parallelism;
                });
                --reacquire_waiters_;
                ++active_cpu_tokens_;
                current_worker_holds_token_ = true;
            }

            --active_cpu_tokens_;
            current_worker_holds_token_ = false;
            current_worker_scheduler_ = nullptr;
            start_workers_locked();
            ready_.notify_all();
        }
    }

public:
    static RuntimeScheduler& shared() {
        // The scheduler intentionally has process lifetime. Detached workers may
        // still reference it while ordinary program shutdown is in progress.
        static auto* scheduler = new RuntimeScheduler();
        return *scheduler;
    }

    void configure(const RuntimeSchedulerOptions& options) {
        if (options.maximum_cpu_parallelism == 0) {
            doof::panic("runtime scheduler maximum CPU parallelism must be at least 1");
        }
        if (options.retained_worker_count > options.maximum_cpu_parallelism) {
            doof::panic("runtime scheduler retained worker count cannot exceed maximum CPU parallelism");
        }
        if (options.excess_worker_idle_timeout.count() < 0) {
            doof::panic("runtime scheduler excess-worker idle timeout cannot be negative");
        }

        std::lock_guard<std::mutex> lock(mutex_);
        if (started_) {
            doof::panic("runtime scheduler cannot be configured after work has started");
        }
        options_ = options;
    }

    void submit(std::function<void()> job) {
        std::lock_guard<std::mutex> lock(mutex_);
        started_ = true;
        jobs_.push(std::move(job));
        start_workers_locked();
    }

    bool relinquish_current_worker_token() {
        if (current_worker_scheduler_ != this || !current_worker_holds_token_) {
            return false;
        }

        {
            std::lock_guard<std::mutex> lock(mutex_);
            --active_cpu_tokens_;
            current_worker_holds_token_ = false;
            start_workers_locked();
        }
        ready_.notify_all();
        return true;
    }

    void reacquire_current_worker_token() {
        if (current_worker_scheduler_ != this || current_worker_holds_token_) {
            return;
        }

        std::unique_lock<std::mutex> lock(mutex_);
        ++reacquire_waiters_;
        ready_.wait(lock, [this] {
            return active_cpu_tokens_ < options_.maximum_cpu_parallelism;
        });
        --reacquire_waiters_;
        ++active_cpu_tokens_;
        current_worker_holds_token_ = true;
        ready_.notify_all();
    }

    RuntimeSchedulerSnapshot snapshot() {
        std::lock_guard<std::mutex> lock(mutex_);
        return RuntimeSchedulerSnapshot {
            active_cpu_tokens_,
            live_worker_threads_,
            idle_worker_threads_,
            jobs_.size(),
            reacquire_waiters_,
        };
    }
};

} // namespace detail

inline void configure_runtime_scheduler(const RuntimeSchedulerOptions& options) {
    detail::RuntimeScheduler::shared().configure(options);
}

class CpuTokenRelease {
    detail::RuntimeScheduler* scheduler_ = nullptr;
    bool released_ = false;

public:
    CpuTokenRelease()
        : scheduler_(&detail::RuntimeScheduler::shared()),
          released_(scheduler_->relinquish_current_worker_token()) {}

    CpuTokenRelease(const CpuTokenRelease&) = delete;
    CpuTokenRelease& operator=(const CpuTokenRelease&) = delete;

    CpuTokenRelease(CpuTokenRelease&& other) noexcept
        : scheduler_(other.scheduler_), released_(other.released_) {
        other.released_ = false;
    }

    CpuTokenRelease& operator=(CpuTokenRelease&&) = delete;

    void reacquire() {
        if (!released_) {
            return;
        }
        scheduler_->reacquire_current_worker_token();
        released_ = false;
    }

    ~CpuTokenRelease() {
        reacquire();
    }
};

template <typename Future>
void wait_with_cpu_token_released(Future& future) {
    if (future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
        return;
    }
    CpuTokenRelease release;
    future.wait();
}

namespace detail {

// Promise producers publish one monotonically increasing generation after
// settling a future. Consumers can then wait for any promise in a collection
// without polling or occupying one scheduler task per promise.
class PromiseCompletionNotifier {
    std::mutex mutex_;
    std::condition_variable ready_;
    std::uint64_t generation_ = 0;

public:
    static PromiseCompletionNotifier& shared() {
        static auto* notifier = new PromiseCompletionNotifier();
        return *notifier;
    }

    std::uint64_t generation() {
        std::lock_guard<std::mutex> lock(mutex_);
        return generation_;
    }

    void notify() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            ++generation_;
        }
        ready_.notify_all();
    }

    void wait_for_change(std::uint64_t observed) {
        CpuTokenRelease release;
        std::unique_lock<std::mutex> lock(mutex_);
        ready_.wait(lock, [this, observed] { return generation_ != observed; });
    }
};

} // namespace detail

template <typename T>
class Promise;

template <typename Signature>
class callback;

namespace detail {
template <typename R, typename... Args>
R call_callback_unchecked(const doof::callback<R(Args...)>& cb, Args... args);
}

template <typename R, typename... Args>
class callback<R(Args...)> {
    std::function<R(Args...)> fn_;
    detail::CallbackDomain* owner_ = nullptr;

public:
    callback() = default;

    template <
        typename F,
        typename = std::enable_if_t<!std::is_same_v<std::decay_t<F>, callback>>
    >
    callback(F&& f)
        : fn_(std::forward<F>(f)),
          owner_(doof::current_actor_domain()) {}

    explicit operator bool() const {
        return static_cast<bool>(fn_);
    }

    R call(Args... args) const {
        if (!fn_) {
            doof::panic("callback invoked before initialization");
        }
        if (owner_ != doof::current_actor_domain()) {
            doof::panic("callback invoked outside owning actor domain");
        }
        if constexpr (std::is_void_v<R>) {
            fn_(std::forward<Args>(args)...);
        } else {
            return fn_(std::forward<Args>(args)...);
        }
    }

    std::function<R(Args...)> as_local_std_function() const {
        auto self = *this;
        return [self](Args... args) -> R {
            if constexpr (std::is_void_v<R>) {
                self.call(std::forward<Args>(args)...);
            } else {
                return self.call(std::forward<Args>(args)...);
            }
        };
    }

    doof::Promise<R> post(Args... args) const;

    void dispatch(Args... args) const {
        static_assert(std::is_void_v<R>, "callback.dispatch is only available for void callbacks");
        if (!fn_) {
            doof::panic("callback dispatched before initialization");
        }

        if (!owner_) {
            detail::call_callback_unchecked(*this, std::forward<Args>(args)...);
            return;
        }

        auto self = *this;
        auto packedArgs = std::make_tuple(std::forward<Args>(args)...);
        owner_->enqueue_callback([self, packedArgs = std::move(packedArgs)]() mutable {
            std::apply([&](auto&&... unpacked) {
                self.call(std::forward<decltype(unpacked)>(unpacked)...);
            }, std::move(packedArgs));
        });
    }

private:
    template <typename CR, typename... CArgs>
    friend CR detail::call_callback_unchecked(const doof::callback<CR(CArgs...)>& cb, CArgs... args);

    R call_unchecked(Args... args) const {
        if (!fn_) {
            doof::panic("callback invoked before initialization");
        }
        if constexpr (std::is_void_v<R>) {
            fn_(std::forward<Args>(args)...);
        } else {
            return fn_(std::forward<Args>(args)...);
        }
    }
};

namespace detail {
template <typename R, typename... Args>
R call_callback_unchecked(const doof::callback<R(Args...)>& cb, Args... args) {
    return cb.call_unchecked(std::forward<Args>(args)...);
}
}

[[noreturn]] inline void panic_ordered_collection_invariant(
    const char* collection,
    const char* context,
    const std::string& detail
) {
    std::ostringstream message;
    message << collection << " invariant failed";
    if (context && context[0] != '\0') {
        message << " in " << context;
    }
    message << ": " << detail;
    panic(message.str());
}

// ============================================================================
// Ordered collections — insertion-order preserving Map/Set runtime types
// ============================================================================

template <typename K, typename V>
class ordered_map {
public:
    using value_type = std::pair<K, V>;
    using storage_type = std::vector<value_type>;
    using iterator = typename storage_type::iterator;
    using const_iterator = typename storage_type::const_iterator;
    using size_type = typename storage_type::size_type;

    ordered_map() = default;

    ordered_map(std::initializer_list<value_type> init) {
        for (const auto& entry : init) {
            insert_or_assign(entry.first, entry.second);
        }
        validate_invariants("ordered_map::initializer_list");
    }

    ordered_map(const ordered_map& other)
        : entries_(other.entries_) {
        rebuild_index();
        validate_invariants("ordered_map::copy_ctor");
    }

    ordered_map& operator=(const ordered_map& other) {
        if (this != &other) {
            entries_ = other.entries_;
            rebuild_index();
            validate_invariants("ordered_map::copy_assign");
        }
        return *this;
    }

    ordered_map(ordered_map&&) = default;
    ordered_map& operator=(ordered_map&&) = default;

    iterator begin() {
        validate_invariants("ordered_map::begin");
        return entries_.begin();
    }
    iterator end() {
        validate_invariants("ordered_map::end");
        return entries_.end();
    }
    const_iterator begin() const {
        validate_invariants("ordered_map::begin const");
        return entries_.begin();
    }
    const_iterator end() const {
        validate_invariants("ordered_map::end const");
        return entries_.end();
    }
    const_iterator cbegin() const {
        validate_invariants("ordered_map::cbegin");
        return entries_.cbegin();
    }
    const_iterator cend() const {
        validate_invariants("ordered_map::cend");
        return entries_.cend();
    }

    [[nodiscard]] bool empty() const { return entries_.empty(); }
    [[nodiscard]] size_type size() const { return entries_.size(); }

    void clear() {
        entries_.clear();
        index_.clear();
        validate_invariants("ordered_map::clear");
    }

    iterator find(const K& key) {
        validate_invariants("ordered_map::find");
        const auto pos = index_.find(key);
        if (pos == index_.end()) {
            return entries_.end();
        }
        return entries_.begin() + static_cast<typename storage_type::difference_type>(pos->second);
    }

    const_iterator find(const K& key) const {
        validate_invariants("ordered_map::find const");
        const auto pos = index_.find(key);
        if (pos == index_.end()) {
            return entries_.end();
        }
        return entries_.begin() + static_cast<typename storage_type::difference_type>(pos->second);
    }

    [[nodiscard]] size_type count(const K& key) const {
        validate_invariants("ordered_map::count");
        return index_.count(key);
    }

    V& operator[](const K& key) {
        validate_invariants("ordered_map::operator[] pre");
        const auto pos = index_.find(key);
        if (pos != index_.end()) {
            return entries_[pos->second].second;
        }

        const auto newIndex = entries_.size();
        entries_.push_back(value_type{key, V{}});
        try {
            index_.emplace(entries_.back().first, newIndex);
        } catch (...) {
            entries_.pop_back();
            throw;
        }
        validate_invariants("ordered_map::operator[] post");
        return entries_.back().second;
    }

    void insert_or_assign(const K& key, const V& value) {
        validate_invariants("ordered_map::insert_or_assign pre");
        const auto pos = index_.find(key);
        if (pos != index_.end()) {
            entries_[pos->second].second = value;
            validate_invariants("ordered_map::insert_or_assign update");
            return;
        }

        const auto newIndex = entries_.size();
        entries_.push_back(value_type{key, value});
        try {
            index_.emplace(entries_.back().first, newIndex);
        } catch (...) {
            entries_.pop_back();
            throw;
        }
        validate_invariants("ordered_map::insert_or_assign insert");
    }

    size_type erase(const K& key) {
        validate_invariants("ordered_map::erase pre");
        const auto pos = index_.find(key);
        if (pos == index_.end()) {
            return 0;
        }

        const auto index = pos->second;
        index_.erase(pos);
        entries_.erase(entries_.begin() + static_cast<typename storage_type::difference_type>(index));
        for (size_type current = index; current < entries_.size(); ++current) {
            index_[entries_[current].first] = current;
        }
        validate_invariants("ordered_map::erase post");
        return 1;
    }

    void validate_invariants(const char* context = "ordered_map") const {
#if defined(DOOF_RUNTIME_VALIDATE_ORDERED_COLLECTIONS)
        if (index_.size() != entries_.size()) {
            panic_ordered_collection_invariant("ordered_map", context, "index size does not match entry count");
        }
        for (size_type index = 0; index < entries_.size(); ++index) {
            const auto pos = index_.find(entries_[index].first);
            if (pos == index_.end()) {
                panic_ordered_collection_invariant("ordered_map", context, "entry key missing from index");
            }
            if (pos->second != index) {
                panic_ordered_collection_invariant("ordered_map", context, "entry key mapped to stale position");
            }
        }
        for (const auto& [key, index] : index_) {
            if (index >= entries_.size()) {
                panic_ordered_collection_invariant("ordered_map", context, "index points past end of entries");
            }
            if (!(entries_[index].first == key)) {
                panic_ordered_collection_invariant("ordered_map", context, "index points at mismatched entry key");
            }
        }
#else
        (void)context;
#endif
    }

private:
    void rebuild_index() {
        index_.clear();
        for (size_type index = 0; index < entries_.size(); ++index) {
            index_[entries_[index].first] = index;
        }
    }

    storage_type entries_;
    std::unordered_map<K, size_type> index_;
};

template <typename K, typename V>
ordered_map(std::initializer_list<std::pair<K, V>>) -> ordered_map<K, V>;

template <typename T>
class ordered_set {
public:
    using value_type = T;
    using storage_type = std::vector<T>;
    using iterator = typename storage_type::iterator;
    using const_iterator = typename storage_type::const_iterator;
    using size_type = typename storage_type::size_type;

    ordered_set() = default;

    ordered_set(std::initializer_list<T> init) {
        for (const auto& value : init) {
            insert(value);
        }
        validate_invariants("ordered_set::initializer_list");
    }

    ordered_set(const ordered_set& other)
        : values_(other.values_) {
        rebuild_index();
        validate_invariants("ordered_set::copy_ctor");
    }

    ordered_set& operator=(const ordered_set& other) {
        if (this != &other) {
            values_ = other.values_;
            rebuild_index();
            validate_invariants("ordered_set::copy_assign");
        }
        return *this;
    }

    ordered_set(ordered_set&&) = default;
    ordered_set& operator=(ordered_set&&) = default;

    iterator begin() {
        validate_invariants("ordered_set::begin");
        return values_.begin();
    }
    iterator end() {
        validate_invariants("ordered_set::end");
        return values_.end();
    }
    const_iterator begin() const {
        validate_invariants("ordered_set::begin const");
        return values_.begin();
    }
    const_iterator end() const {
        validate_invariants("ordered_set::end const");
        return values_.end();
    }
    const_iterator cbegin() const {
        validate_invariants("ordered_set::cbegin");
        return values_.cbegin();
    }
    const_iterator cend() const {
        validate_invariants("ordered_set::cend");
        return values_.cend();
    }

    [[nodiscard]] bool empty() const { return values_.empty(); }
    [[nodiscard]] size_type size() const { return values_.size(); }

    void clear() {
        values_.clear();
        index_.clear();
        validate_invariants("ordered_set::clear");
    }

    iterator find(const T& value) {
        validate_invariants("ordered_set::find");
        const auto pos = index_.find(value);
        if (pos == index_.end()) {
            return values_.end();
        }
        return values_.begin() + static_cast<typename storage_type::difference_type>(pos->second);
    }

    const_iterator find(const T& value) const {
        validate_invariants("ordered_set::find const");
        const auto pos = index_.find(value);
        if (pos == index_.end()) {
            return values_.end();
        }
        return values_.begin() + static_cast<typename storage_type::difference_type>(pos->second);
    }

    [[nodiscard]] size_type count(const T& value) const {
        validate_invariants("ordered_set::count");
        return index_.count(value);
    }

    bool insert(const T& value) {
        validate_invariants("ordered_set::insert pre");
        if (index_.count(value) > 0) {
            return false;
        }

        index_[value] = values_.size();
        values_.push_back(value);
        validate_invariants("ordered_set::insert post");
        return true;
    }

    size_type erase(const T& value) {
        validate_invariants("ordered_set::erase pre");
        const auto pos = index_.find(value);
        if (pos == index_.end()) {
            return 0;
        }

        const auto index = pos->second;
        index_.erase(pos);
        values_.erase(values_.begin() + static_cast<typename storage_type::difference_type>(index));
        for (size_type current = index; current < values_.size(); ++current) {
            index_[values_[current]] = current;
        }
        validate_invariants("ordered_set::erase post");
        return 1;
    }

    void validate_invariants(const char* context = "ordered_set") const {
#if defined(DOOF_RUNTIME_VALIDATE_ORDERED_COLLECTIONS)
        if (index_.size() != values_.size()) {
            panic_ordered_collection_invariant("ordered_set", context, "index size does not match value count");
        }
        for (size_type index = 0; index < values_.size(); ++index) {
            const auto pos = index_.find(values_[index]);
            if (pos == index_.end()) {
                panic_ordered_collection_invariant("ordered_set", context, "value missing from index");
            }
            if (pos->second != index) {
                panic_ordered_collection_invariant("ordered_set", context, "value mapped to stale position");
            }
        }
        for (const auto& [value, index] : index_) {
            if (index >= values_.size()) {
                panic_ordered_collection_invariant("ordered_set", context, "index points past end of values");
            }
            if (!(values_[index] == value)) {
                panic_ordered_collection_invariant("ordered_set", context, "index points at mismatched value");
            }
        }
#else
        (void)context;
#endif
    }

private:
    void rebuild_index() {
        index_.clear();
        for (size_type index = 0; index < values_.size(); ++index) {
            index_[values_[index]] = index;
        }
    }

    storage_type values_;
    std::unordered_map<T, size_type> index_;
};

template <typename T>
ordered_set(std::initializer_list<T>) -> ordered_set<T>;

// ============================================================================
// Intrinsic Result arms and their ordinary variant alias
// ============================================================================

template <typename T> struct Success { T value; };
template <> struct Success<void> {};
template <typename E> struct Failure { E error; };
template <> struct Failure<void> {};

template <typename T, typename E>
using Result = std::variant<Success<T>, Failure<E>>;

template <typename T, typename E>
inline bool is_success(const Result<T, E>& result) { return std::holds_alternative<Success<T>>(result); }
template <typename T, typename E>
inline bool is_failure(const Result<T, E>& result) { return std::holds_alternative<Failure<E>>(result); }
template <typename T, typename E>
inline T& success_value(Result<T, E>& result) { return std::get<Success<T>>(result).value; }
template <typename T, typename E>
inline const T& success_value(const Result<T, E>& result) { return std::get<Success<T>>(result).value; }
template <typename T, typename E>
inline E& failure_error(Result<T, E>& result) { return std::get<Failure<E>>(result).error; }
template <typename T, typename E>
inline const E& failure_error(const Result<T, E>& result) { return std::get<Failure<E>>(result).error; }

template <typename T>
struct StreamBase {
    virtual ~StreamBase() = default;
    virtual bool next() = 0;
    virtual T value() = 0;
};

template <typename Target, typename Source>
inline std::optional<Target> checked_numeric_as(Source value) {
    static_assert(std::is_arithmetic_v<Target>, "checked_numeric_as target must be numeric");
    static_assert(std::is_arithmetic_v<Source>, "checked_numeric_as source must be numeric");

    if constexpr (std::is_same_v<Target, Source>) {
        return value;
    } else if constexpr (std::is_integral_v<Source> && std::is_integral_v<Target>) {
        if constexpr (std::is_signed_v<Source> == std::is_signed_v<Target>) {
            if constexpr (std::numeric_limits<Target>::digits >= std::numeric_limits<Source>::digits) {
                return static_cast<Target>(value);
            } else {
                if (value < static_cast<Source>(std::numeric_limits<Target>::lowest())
                    || value > static_cast<Source>(std::numeric_limits<Target>::max())) {
                    return std::nullopt;
                }
            }
        } else if constexpr (std::is_signed_v<Source>) {
            if (value < 0) return std::nullopt;
            using UnsignedSource = std::make_unsigned_t<Source>;
            if (static_cast<UnsignedSource>(value) > std::numeric_limits<Target>::max()) {
                return std::nullopt;
            }
        } else {
            using UnsignedTarget = std::make_unsigned_t<Target>;
            if (value > static_cast<UnsignedTarget>(std::numeric_limits<Target>::max())) {
                return std::nullopt;
            }
        }
        return static_cast<Target>(value);
    } else if constexpr (std::is_floating_point_v<Source> && std::is_integral_v<Target>) {
        if (!std::isfinite(value) || std::trunc(value) != value) return std::nullopt;
        if (value < static_cast<Source>(std::numeric_limits<Target>::lowest())
            || value > static_cast<Source>(std::numeric_limits<Target>::max())) {
            return std::nullopt;
        }
        return static_cast<Target>(value);
    } else if constexpr (std::is_integral_v<Source> && std::is_floating_point_v<Target>) {
        const auto narrowed = static_cast<Target>(value);
        if (!std::isfinite(narrowed)) return std::nullopt;
        if (static_cast<Source>(narrowed) != value) return std::nullopt;
        return narrowed;
    } else {
        if constexpr (sizeof(Target) >= sizeof(Source)) {
            return static_cast<Target>(value);
        }

        const auto narrowed = static_cast<Target>(value);
        if (std::isnan(value)) {
            return std::isnan(narrowed) ? std::optional<Target>(narrowed) : std::nullopt;
        }
        if (!std::isfinite(value)) {
            return (std::isinf(narrowed) && ((value > 0) == (narrowed > 0)))
                ? std::optional<Target>(narrowed)
                : std::nullopt;
        }
        if (static_cast<Source>(narrowed) != value) return std::nullopt;
        return narrowed;
    }
}

// ============================================================================
// JsonValue — first-class JSON runtime value
// ============================================================================

struct JsonValue;

using JsonArray = std::shared_ptr<std::vector<JsonValue>>;
using JsonObject = std::shared_ptr<ordered_map<std::string, JsonValue>>;
using JsonStorage = std::variant<std::monostate, bool, int32_t, int64_t, float, double, std::string, JsonArray, JsonObject>;

struct JsonValue : JsonStorage {
    using JsonStorage::JsonStorage;

    JsonValue() : JsonStorage(std::monostate{}) {}
    JsonValue(std::nullptr_t) : JsonStorage(std::monostate{}) {}
    JsonValue(const char* v) : JsonStorage(std::string(v)) {}
};

template <typename T>
inline JsonValue json_value(T&& value) {
    return JsonValue(std::forward<T>(value));
}

inline const JsonStorage& json_storage(const JsonValue& value) {
    return static_cast<const JsonStorage&>(value);
}

inline JsonStorage& json_storage(JsonValue& value) {
    return static_cast<JsonStorage&>(value);
}

inline bool json_is_null(const JsonValue& value) {
    return std::holds_alternative<std::monostate>(json_storage(value));
}

inline bool json_is_boolean(const JsonValue& value) {
    return std::holds_alternative<bool>(json_storage(value));
}

inline bool json_is_number(const JsonValue& value) {
    return std::holds_alternative<int32_t>(json_storage(value))
        || std::holds_alternative<int64_t>(json_storage(value))
        || std::holds_alternative<float>(json_storage(value))
        || std::holds_alternative<double>(json_storage(value));
}

inline bool json_is_string(const JsonValue& value) {
    return std::holds_alternative<std::string>(json_storage(value));
}

inline bool json_is_array(const JsonValue& value) {
    return std::holds_alternative<JsonArray>(json_storage(value));
}

inline bool json_is_object(const JsonValue& value) {
    return std::holds_alternative<JsonObject>(json_storage(value));
}

inline const char* json_type_name(const JsonValue& value) {
    if (json_is_null(value)) return "null";
    if (json_is_boolean(value)) return "boolean";
    if (json_is_number(value)) return "number";
    if (json_is_string(value)) return "string";
    if (json_is_array(value)) return "array";
    if (json_is_object(value)) return "object";
    return "unknown";
}

inline const JsonArray::element_type* json_as_array(const JsonValue& value) {
    const auto* array = std::get_if<JsonArray>(&json_storage(value));
    if (array == nullptr || !*array) return nullptr;
    return array->get();
}

inline const JsonObject::element_type* json_as_object(const JsonValue& value) {
    const auto* object = std::get_if<JsonObject>(&json_storage(value));
    if (object == nullptr || !*object) return nullptr;
    return object->get();
}

inline JsonValue json_error(int32_t code, std::string message) {
    auto object = std::make_shared<ordered_map<std::string, JsonValue>>();
    (*object)["code"] = json_value(code);
    (*object)["message"] = json_value(std::move(message));
    return json_value(std::move(object));
}

inline bool json_as_bool(const JsonValue& value) {
    const auto* result = std::get_if<bool>(&json_storage(value));
    if (result == nullptr) panic("Expected JSON boolean");
    return *result;
}

inline int32_t json_as_int(const JsonValue& value) {
    if (const auto* result = std::get_if<int32_t>(&json_storage(value))) return *result;
    if (const auto* result = std::get_if<int64_t>(&json_storage(value))) return static_cast<int32_t>(*result);
    if (const auto* result = std::get_if<float>(&json_storage(value))) return static_cast<int32_t>(*result);
    if (const auto* result = std::get_if<double>(&json_storage(value))) return static_cast<int32_t>(*result);
    panic("Expected JSON number");
}

inline int64_t json_as_long(const JsonValue& value) {
    if (const auto* result = std::get_if<int32_t>(&json_storage(value))) return *result;
    if (const auto* result = std::get_if<int64_t>(&json_storage(value))) return *result;
    if (const auto* result = std::get_if<float>(&json_storage(value))) return static_cast<int64_t>(*result);
    if (const auto* result = std::get_if<double>(&json_storage(value))) return static_cast<int64_t>(*result);
    panic("Expected JSON number");
}

inline float json_as_float(const JsonValue& value) {
    if (const auto* result = std::get_if<int32_t>(&json_storage(value))) return static_cast<float>(*result);
    if (const auto* result = std::get_if<int64_t>(&json_storage(value))) return static_cast<float>(*result);
    if (const auto* result = std::get_if<float>(&json_storage(value))) return *result;
    if (const auto* result = std::get_if<double>(&json_storage(value))) return static_cast<float>(*result);
    panic("Expected JSON number");
}

inline double json_as_double(const JsonValue& value) {
    if (const auto* result = std::get_if<int32_t>(&json_storage(value))) return static_cast<double>(*result);
    if (const auto* result = std::get_if<int64_t>(&json_storage(value))) return static_cast<double>(*result);
    if (const auto* result = std::get_if<float>(&json_storage(value))) return static_cast<double>(*result);
    if (const auto* result = std::get_if<double>(&json_storage(value))) return *result;
    panic("Expected JSON number");
}

inline const std::string& json_as_string(const JsonValue& value) {
    const auto* result = std::get_if<std::string>(&json_storage(value));
    if (result == nullptr) panic("Expected JSON string");
    return *result;
}

inline JsonObject json_object(const JsonValue& value) {
    const auto* object = std::get_if<JsonObject>(&json_storage(value));
    if (object == nullptr || !*object) panic("Expected JSON object");
    return *object;
}

inline bool json_is_lenient_boolean(const JsonValue& value) {
    if (json_is_boolean(value) || json_is_number(value)) return true;
    if (!json_is_string(value)) return false;
    std::string lowered = json_as_string(value);
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return lowered == "true" || lowered == "false" || lowered == "1" || lowered == "0";
}

inline bool json_is_lenient_number(const JsonValue& value) {
    return json_is_number(value) || json_is_boolean(value);
}

inline bool json_is_lenient_string(const JsonValue& value) {
    return json_is_null(value) || json_is_string(value) || json_is_boolean(value) || json_is_number(value);
}

inline bool json_as_bool_lenient(const JsonValue& value) {
    if (json_is_boolean(value)) return json_as_bool(value);
    if (const auto* result = std::get_if<int32_t>(&json_storage(value))) return *result != 0;
    if (const auto* result = std::get_if<int64_t>(&json_storage(value))) return *result != 0;
    if (const auto* result = std::get_if<float>(&json_storage(value))) return *result != 0.0f;
    if (const auto* result = std::get_if<double>(&json_storage(value))) return *result != 0.0;
    if (json_is_string(value)) {
        std::string lowered = json_as_string(value);
        std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        });
        if (lowered == "true" || lowered == "1") return true;
        if (lowered == "false" || lowered == "0") return false;
    }
    panic("Expected lenient JSON boolean");
}

inline int32_t json_as_int_lenient(const JsonValue& value) {
    if (json_is_boolean(value)) return json_as_bool(value) ? 1 : 0;
    return json_as_int(value);
}

inline int64_t json_as_long_lenient(const JsonValue& value) {
    if (json_is_boolean(value)) return json_as_bool(value) ? 1 : 0;
    return json_as_long(value);
}

inline float json_as_float_lenient(const JsonValue& value) {
    if (json_is_boolean(value)) return json_as_bool(value) ? 1.0f : 0.0f;
    return json_as_float(value);
}

inline double json_as_double_lenient(const JsonValue& value) {
    if (json_is_boolean(value)) return json_as_bool(value) ? 1.0 : 0.0;
    return json_as_double(value);
}

inline std::string json_as_string_lenient(const JsonValue& value) {
    if (json_is_null(value)) return std::string();
    if (json_is_string(value)) return json_as_string(value);
    if (json_is_boolean(value)) return json_as_bool(value) ? "true" : "false";
    if (const auto* result = std::get_if<int32_t>(&json_storage(value))) return std::to_string(*result);
    if (const auto* result = std::get_if<int64_t>(&json_storage(value))) return std::to_string(*result);
    if (const auto* result = std::get_if<float>(&json_storage(value))) {
        std::ostringstream oss;
        oss << *result;
        return oss.str();
    }
    if (const auto* result = std::get_if<double>(&json_storage(value))) {
        std::ostringstream oss;
        oss << *result;
        return oss.str();
    }
    panic("Expected lenient JSON string");
}

inline std::optional<char32_t> utf8_single_code_point(const std::string& text) {
    if (text.empty()) return std::nullopt;
    const auto byte = [&text](size_t index) { return static_cast<uint8_t>(text[index]); };
    const uint8_t first = byte(0);
    char32_t value = 0;
    size_t length = 0;
    if (first <= 0x7f) {
        value = first;
        length = 1;
    } else if (first >= 0xc2 && first <= 0xdf) {
        value = first & 0x1f;
        length = 2;
    } else if (first >= 0xe0 && first <= 0xef) {
        value = first & 0x0f;
        length = 3;
    } else if (first >= 0xf0 && first <= 0xf4) {
        value = first & 0x07;
        length = 4;
    } else {
        return std::nullopt;
    }
    if (text.size() != length) return std::nullopt;
    for (size_t index = 1; index < length; ++index) {
        const uint8_t continuation = byte(index);
        if ((continuation & 0xc0) != 0x80) return std::nullopt;
        value = (value << 6) | (continuation & 0x3f);
    }
    if ((length == 2 && value < 0x80)
        || (length == 3 && value < 0x800)
        || (length == 4 && value < 0x10000)
        || value > 0x10ffff
        || (value >= 0xd800 && value <= 0xdfff)) {
        return std::nullopt;
    }
    return value;
}

inline std::string char_to_utf8(char32_t value) {
    if (value > 0x10ffff || (value >= 0xd800 && value <= 0xdfff)) {
        panic("Invalid Unicode code point");
    }
    std::string result;
    if (value <= 0x7f) {
        result.push_back(static_cast<char>(value));
    } else if (value <= 0x7ff) {
        result.push_back(static_cast<char>(0xc0 | (value >> 6)));
        result.push_back(static_cast<char>(0x80 | (value & 0x3f)));
    } else if (value <= 0xffff) {
        result.push_back(static_cast<char>(0xe0 | (value >> 12)));
        result.push_back(static_cast<char>(0x80 | ((value >> 6) & 0x3f)));
        result.push_back(static_cast<char>(0x80 | (value & 0x3f)));
    } else {
        result.push_back(static_cast<char>(0xf0 | (value >> 18)));
        result.push_back(static_cast<char>(0x80 | ((value >> 12) & 0x3f)));
        result.push_back(static_cast<char>(0x80 | ((value >> 6) & 0x3f)));
        result.push_back(static_cast<char>(0x80 | (value & 0x3f)));
    }
    return result;
}

inline bool json_is_char(const JsonValue& value, bool lenient) {
    if (lenient) {
        if (!json_is_lenient_string(value)) return false;
        return utf8_single_code_point(json_as_string_lenient(value)).has_value();
    }
    return json_is_string(value) && utf8_single_code_point(json_as_string(value)).has_value();
}

inline char32_t json_as_char(const JsonValue& value, bool lenient) {
    const auto decoded = utf8_single_code_point(lenient ? json_as_string_lenient(value) : json_as_string(value));
    if (!decoded.has_value()) panic("Expected one Unicode character");
    return decoded.value();
}

class JsonDecodeError final {
public:
    explicit JsonDecodeError(std::string message) : message_(std::move(message)) {}
    const std::string& message() const noexcept { return message_; }

private:
    std::string message_;
};

template <typename T>
T json_decode_value(Result<T, std::string> result) {
    if (is_failure(result)) throw JsonDecodeError(failure_error(result));
    return std::move(success_value(result));
}

template <typename T>
T json_decode_optional(std::optional<T> value, std::string message) {
    if (!value.has_value()) throw JsonDecodeError(std::move(message));
    return std::move(value.value());
}


// ============================================================================
// String utilities
// ============================================================================

// Convert any streamable value to string
template <typename T>
inline std::string to_string(const T& val) {
    if constexpr (std::is_same_v<T, std::string>) {
        return val;
    } else if constexpr (std::is_same_v<T, const char*>) {
        return std::string(val);
    } else if constexpr (std::is_same_v<T, bool>) {
        return val ? "true" : "false";
    } else if constexpr (std::is_same_v<T, uint8_t>) {
        return std::to_string(static_cast<uint32_t>(val));
    } else if constexpr (std::is_same_v<T, char32_t>) {
        return char_to_utf8(val);
    } else {
        std::ostringstream oss;
        oss << val;
        return oss.str();
    }
}

template <typename T>
inline std::string to_string(const std::shared_ptr<std::vector<T>>& val) {
    if (!val) return "null";
    std::string result = "[";
    for (size_t i = 0; i < val->size(); ++i) {
        if (i > 0) result += ", ";
        result += to_string((*val)[i]);
    }
    result += "]";
    return result;
}

template <typename K, typename V>
inline std::string to_string(const std::shared_ptr<ordered_map<K, V>>& val) {
    if (!val) return "null";
    std::string result = "{";
    bool first = true;
    for (const auto& entry : *val) {
        if (!first) result += ", ";
        first = false;
        result += to_string(entry.first) + ": " + to_string(entry.second);
    }
    result += "}";
    return result;
}

template <typename T>
inline std::string to_string(const std::shared_ptr<ordered_set<T>>& val) {
    if (!val) return "null";
    std::string result = "{";
    bool first = true;
    for (const auto& item : *val) {
        if (!first) result += ", ";
        first = false;
        result += to_string(item);
    }
    result += "}";
    return result;
}

template <typename... Ts, std::size_t... Is>
inline std::string tuple_to_string_impl(const std::tuple<Ts...>& val, std::index_sequence<Is...>) {
    std::string result = "(";
    ((result += (Is == 0 ? "" : ", ") + to_string(std::get<Is>(val))), ...);
    result += ")";
    return result;
}

template <typename... Ts>
inline std::string to_string(const std::tuple<Ts...>& val) {
    return tuple_to_string_impl(val, std::index_sequence_for<Ts...>{});
}

template <typename T, typename E>
inline std::string to_string(const Result<T, E>& val) {
    if (is_success(val)) {
        return "Success(" + to_string(success_value(val)) + ")";
    }
    return "Failure(" + to_string(failure_error(val)) + ")";
}

template <typename E>
inline std::string to_string(const Result<void, E>& val) {
    if (is_success(val)) {
        return "Success()";
    }
    return "Failure(" + to_string(failure_error(val)) + ")";
}

template <typename T>
inline std::string to_string(const std::optional<T>& val) {
    return val.has_value() ? to_string(*val) : std::string("null");
}

inline std::string to_string(std::monostate) {
    return "null";
}

template <typename... Ts>
inline std::string to_string(const std::variant<Ts...>& val) {
    return std::visit([](const auto& inner) -> std::string {
        using Inner = std::decay_t<decltype(inner)>;
        if constexpr (std::is_same_v<Inner, std::monostate>) {
            return std::string("null");
        }
        return to_string(inner);
    }, val);
}

// Mutable append-only storage for compiler and library code that produces
// large strings incrementally. drainToString() transfers ownership of the completed
// string, leaving the builder empty and reusable.
class StringBuilder {
public:
    static std::shared_ptr<StringBuilder> constructor() {
        return std::make_shared<StringBuilder>();
    }

    void append(const std::string& value) {
        value_.append(value);
    }

    std::string drainToString() {
        std::string result = std::move(value_);
        value_.clear();
        return result;
    }

private:
    std::string value_;
};

// Variadic string concatenation for string interpolation
inline std::string concat() { return ""; }

template <typename T>
inline std::string concat(const T& val) {
    return to_string(val);
}

template <typename T, typename... Args>
inline std::string concat(const T& first, const Args&... rest) {
    return to_string(first) + concat(rest...);
}

// ============================================================================
// String methods
// ============================================================================

inline int32_t string_indexOf(const std::string& s, const std::string& search) {
    auto pos = s.find(search);
    return pos == std::string::npos ? -1 : static_cast<int32_t>(pos);
}

inline bool string_contains(const std::string& s, const std::string& search) {
    return s.find(search) != std::string::npos;
}

inline bool string_startsWith(const std::string& s, const std::string& prefix) {
    return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

inline bool string_endsWith(const std::string& s, const std::string& suffix) {
    return s.size() >= suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline std::string string_substring(const std::string& s, int32_t start, int32_t end) {
    if (start < 0) start = 0;
    if (end > static_cast<int32_t>(s.size())) end = static_cast<int32_t>(s.size());
    if (start >= end) return "";
    return s.substr(static_cast<size_t>(start), static_cast<size_t>(end - start));
}

inline std::string string_slice(const std::string& s, int32_t start) {
    if (start < 0) start = 0;
    if (start >= static_cast<int32_t>(s.size())) return "";
    return s.substr(static_cast<size_t>(start));
}

inline std::string string_padStart(const std::string& s, int32_t length, char fill) {
    if (length <= static_cast<int32_t>(s.size())) return s;
    return std::string(static_cast<size_t>(length - static_cast<int32_t>(s.size())), fill) + s;
}

inline std::string string_trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, end - start + 1);
}

inline std::string string_trimStart(const std::string& s) {
    auto start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    return s.substr(start);
}

inline std::string string_trimEnd(const std::string& s) {
    auto end = s.find_last_not_of(" \t\n\r\f\v");
    if (end == std::string::npos) return "";
    return s.substr(0, end + 1);
}

inline std::string string_trimEnd(const std::string& s, char fill) {
    auto end = s.find_last_not_of(fill);
    if (end == std::string::npos) return "";
    return s.substr(0, end + 1);
}

inline std::string string_toUpperCase(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

inline std::string string_toLowerCase(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

inline std::string string_replace(const std::string& s, const std::string& search, const std::string& replacement) {
    if (search.empty()) return s;
    auto pos = s.find(search);
    if (pos == std::string::npos) return s;
    std::string result = s;
    result.replace(pos, search.size(), replacement);
    return result;
}

inline std::string string_replaceAll(const std::string& s, const std::string& search, const std::string& replacement) {
    if (search.empty()) return s;
    std::string result = s;
    size_t pos = 0;
    while ((pos = result.find(search, pos)) != std::string::npos) {
        result.replace(pos, search.size(), replacement);
        pos += replacement.size();
    }
    return result;
}

inline std::shared_ptr<std::vector<std::string>> string_split(const std::string& s, const std::string& delimiter) {
    auto result = std::make_shared<std::vector<std::string>>();
    if (delimiter.empty()) {
        for (char c : s) result->push_back(std::string(1, c));
        return result;
    }
    size_t start = 0;
    size_t pos;
    while ((pos = s.find(delimiter, start)) != std::string::npos) {
        result->push_back(s.substr(start, pos - start));
        start = pos + delimiter.size();
    }
    result->push_back(s.substr(start));
    return result;
}

inline char32_t string_at(const std::string& s, int32_t index, const char* file, int32_t line) {
    if (index < 0 || index >= static_cast<int32_t>(s.size())) {
        panic_at(file, line, "Index out of bounds: " + to_string(index));
    }
    return static_cast<char32_t>(static_cast<unsigned char>(s[static_cast<size_t>(index)]));
}

inline std::string string_repeat(const std::string& s, int32_t count) {
    if (count <= 0) return "";
    std::string result;
    result.reserve(s.size() * static_cast<size_t>(count));
    for (int32_t i = 0; i < count; ++i) result += s;
    return result;
}

// Representation-dependent helpers used by generated code. Operations whose
// receiver representation is statically known are lowered directly instead.
inline bool is_null(const JsonValue& value) {
    return json_is_null(value);
}

template <typename T>
bool is_null(const std::shared_ptr<T>& value) {
    return value == nullptr;
}

template <typename T>
bool is_null(const std::optional<T>& value) {
    return !value.has_value();
}

template <typename... T>
bool is_null(const std::variant<std::monostate, T...>& value) {
    return std::holds_alternative<std::monostate>(value);
}

template <typename Candidate, typename Variant>
struct is_variant_alternative : std::is_same<Candidate, Variant> {};

template <typename Candidate, typename... Alternatives>
struct is_variant_alternative<Candidate, std::variant<Alternatives...>>
    : std::bool_constant<(std::is_same_v<Candidate, Alternatives> || ...)> {};

template <typename Target, typename... Source>
bool variant_is(const std::variant<Source...>& value) {
    return std::visit([](const auto& item) {
        using Item = std::decay_t<decltype(item)>;
        return is_variant_alternative<Item, Target>::value;
    }, value);
}

template <typename Target, typename... Source>
Target variant_narrow(const std::variant<Source...>& value) {
    return std::visit([](const auto& item) -> Target {
        using Item = std::decay_t<decltype(item)>;
        if constexpr (is_variant_alternative<Item, Target>::value) {
            return item;
        } else {
            throw std::runtime_error("variant does not hold a requested alternative");
        }
    }, value);
}

template <typename Target, typename... Source>
Target variant_promote(const std::variant<Source...>& value) {
    return std::visit([](const auto& item) -> Target { return item; }, value);
}

template <typename Target, typename Source>
Target variant_promote(const Source& value) {
    return Target{value};
}

template <typename... T>
const std::variant<std::monostate, T...>& optional_value(const std::variant<std::monostate, T...>& value) {
    return value;
}

template <typename... T>
std::variant<std::monostate, T...> optional_value(const std::variant<T...>& value) {
    return std::visit([](const auto& item) -> std::variant<std::monostate, T...> { return item; }, value);
}

template <typename... T>
std::variant<T...> unwrap_optional(const std::variant<std::monostate, T...>& value) {
    return std::visit([](const auto& item) -> std::variant<T...> {
        using Item = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<Item, std::monostate>) {
            throw std::runtime_error("unexpected null optional");
        } else {
            return item;
        }
    }, value);
}

template <typename T>
std::shared_ptr<T> unwrap_optional(const std::shared_ptr<T>& value) {
    return value;
}

template <typename T>
T unwrap_optional(const std::optional<T>& value) {
    return value.value();
}

// ============================================================================
// Collection helpers
// ============================================================================

// Wrap a value in a shared_ptr (used for collection literals with CTAD)
template <typename T>
std::shared_ptr<std::decay_t<T>> share(T&& val) {
    return std::make_shared<std::decay_t<T>>(std::forward<T>(val));
}

template <typename T>
typename std::vector<T>::reference array_at(const std::shared_ptr<std::vector<T>>& arr, int32_t index, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to index null array");
    }
    if (index < 0 || index >= static_cast<int32_t>(arr->size())) {
        panic_at(file, line, "Index out of bounds: " + to_string(index));
    }
    return (*arr)[static_cast<size_t>(index)];
}

template <typename T>
void array_require_min_size(const std::shared_ptr<std::vector<T>>& arr, int32_t count, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to destructure null array");
    }
    const auto size = static_cast<int32_t>(arr->size());
    if (size < count) {
        panic_at(file, line, "Array destructuring expected at least " + to_string(count) + " elements, got " + to_string(size));
    }
}

template <typename T>
void array_reserve(const std::shared_ptr<std::vector<T>>& arr, int32_t capacity) {
    if (!arr) {
        panic("Attempted to reserve capacity on a null array");
    }
    if (capacity > 0) {
        arr->reserve(static_cast<size_t>(capacity));
    }
}

template <typename T>
Result<T, std::string> array_pop(const std::shared_ptr<std::vector<T>>& arr) {
    if (!arr) {
        return Failure<std::string>{"Attempted to pop from null array"};
    }
    if (arr->empty()) {
        return Failure<std::string>{"Attempted to pop from empty array"};
    }
    T value = arr->back();
    arr->pop_back();
    return Success<T>{std::move(value)};
}

template <typename T>
bool array_contains(const std::shared_ptr<std::vector<T>>& arr, const T& element, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to search null array");
    }
    return std::find(arr->begin(), arr->end(), element) != arr->end();
}

template <typename T>
int32_t array_indexOf(const std::shared_ptr<std::vector<T>>& arr, const T& element, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to search null array");
    }
    const auto size = static_cast<int32_t>(arr->size());
    for (int32_t i = 0; i < size; i++) {
        if ((*arr)[static_cast<size_t>(i)] == element) {
            return i;
        }
    }
    return -1;
}

template <typename T, typename Predicate>
bool array_some(const std::shared_ptr<std::vector<T>>& arr, const Predicate& predicate, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in some()");
    }
    for (const auto& item : *arr) {
        if (predicate.call(item)) {
            return true;
        }
    }
    return false;
}

template <typename T, typename Predicate>
bool array_every(const std::shared_ptr<std::vector<T>>& arr, const Predicate& predicate, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in every()");
    }
    for (const auto& item : *arr) {
        if (!predicate.call(item)) {
            return false;
        }
    }
    return true;
}

template <typename T, typename Predicate>
std::shared_ptr<std::vector<T>> array_filter(const std::shared_ptr<std::vector<T>>& arr, const Predicate& predicate, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in filter()");
    }
    auto result = std::make_shared<std::vector<T>>();
    result->reserve(arr->size());
    for (const auto& item : *arr) {
        if (predicate.call(item)) {
            result->push_back(item);
        }
    }
    return result;
}

template <typename T, typename Mapper>
auto array_map(const std::shared_ptr<std::vector<T>>& arr, const Mapper& mapper, const char* file, int32_t line)
    -> std::shared_ptr<std::vector<std::decay_t<decltype(std::declval<const Mapper&>().call(std::declval<const T&>()))>>> {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in map()");
    }
    using U = std::decay_t<decltype(std::declval<const Mapper&>().call(std::declval<const T&>()))>;
    auto result = std::make_shared<std::vector<U>>();
    result->reserve(arr->size());
    for (const auto& item : *arr) {
        result->push_back(mapper.call(item));
    }
    return result;
}

template <typename T>
std::shared_ptr<std::vector<T>> array_slice(const std::shared_ptr<std::vector<T>>& arr, int32_t start, int32_t end, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to slice null array");
    }

    const int32_t size = static_cast<int32_t>(arr->size());
    if (start < 0) start = 0;
    if (end < 0) end = 0;
    if (start > size) start = size;
    if (end > size) end = size;
    if (start >= end) {
        return std::make_shared<std::vector<T>>();
    }

    using Diff = typename std::vector<T>::difference_type;
    return std::make_shared<std::vector<T>>(
        arr->begin() + static_cast<Diff>(start),
        arr->begin() + static_cast<Diff>(end)
    );
}

template <typename T>
std::shared_ptr<std::vector<T>> array_drainToReadonly(const std::shared_ptr<std::vector<T>>& arr, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to drainToReadonly from null array");
    }
    // Move-drain: transfer contents to a new allocation; original vector is left empty.
    auto result = std::make_shared<std::vector<T>>(std::move(*arr));
    arr->clear();
    return result;
}

template <typename T>
std::shared_ptr<std::vector<T>> array_buildReadonly(const std::shared_ptr<std::vector<T>>& arr, const char* file, int32_t line) {
    return array_drainToReadonly(arr, file, line);
}

template <typename T>
std::shared_ptr<std::vector<T>> array_cloneReadonly(const std::shared_ptr<std::vector<T>>& arr, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to cloneReadonly from null array");
    }
    return std::make_shared<std::vector<T>>(*arr);
}

template <typename T>
std::shared_ptr<std::vector<T>> array_cloneMutable(const std::shared_ptr<std::vector<T>>& arr, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to cloneMutable from null array");
    }
    return std::make_shared<std::vector<T>>(*arr);
}

// Map helpers — bridge Doof's Map methods to ordered_map
template <typename K, typename V>
doof::Result<V, std::string> map_get(const std::shared_ptr<ordered_map<K, V>>& m, const K& key, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to access null map");
    }
    m->validate_invariants("map_get");
    auto it = m->find(key);
    if (it != m->end()) return doof::Success<V>{it->second};
    return doof::Failure<std::string>{"Map key not found"};
}

template <typename K, typename V>
V& map_at(const std::shared_ptr<ordered_map<K, V>>& m, const K& key, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to index null map");
    }
    m->validate_invariants("map_at");
    auto it = m->find(key);
    if (it == m->end()) {
        panic_at(file, line, "Map key not found");
    }
    return it->second;
}

template <typename K, typename V>
V& map_index(const std::shared_ptr<ordered_map<K, V>>& m, const K& key, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to index null map");
    }
    m->validate_invariants("map_index");
    return (*m)[key];
}

template <typename K, typename V>
void map_set(const std::shared_ptr<ordered_map<K, V>>& m, const K& key, const V& value, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to mutate null map");
    }
    m->insert_or_assign(key, value);
}

template <typename K, typename V>
std::shared_ptr<std::vector<K>> map_keys(const std::shared_ptr<ordered_map<K, V>>& m, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to read keys from null map");
    }
    m->validate_invariants("map_keys");
    auto result = std::make_shared<std::vector<K>>();
    result->reserve(m->size());
    for (const auto& [k, v] : *m) result->push_back(k);
    return result;
}

template <typename K, typename V>
std::shared_ptr<std::vector<V>> map_values(const std::shared_ptr<ordered_map<K, V>>& m, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to read values from null map");
    }
    m->validate_invariants("map_values");
    auto result = std::make_shared<std::vector<V>>();
    result->reserve(m->size());
    for (const auto& [k, v] : *m) result->push_back(v);
    return result;
}

template <typename K, typename V>
std::shared_ptr<ordered_map<K, V>> map_drainToReadonly(const std::shared_ptr<ordered_map<K, V>>& m, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to drainToReadonly from null map");
    }
    m->validate_invariants("map_drainToReadonly source");
    auto result = std::make_shared<ordered_map<K, V>>(std::move(*m));
    m->clear();
    result->validate_invariants("map_drainToReadonly result");
    return result;
}

template <typename K, typename V>
std::shared_ptr<ordered_map<K, V>> map_buildReadonly(const std::shared_ptr<ordered_map<K, V>>& m, const char* file, int32_t line) {
    return map_drainToReadonly(m, file, line);
}

template <typename K, typename V>
std::shared_ptr<ordered_map<K, V>> map_cloneReadonly(const std::shared_ptr<ordered_map<K, V>>& m, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to cloneReadonly from null map");
    }
    m->validate_invariants("map_cloneReadonly");
    return std::make_shared<ordered_map<K, V>>(*m);
}

template <typename K, typename V>
std::shared_ptr<ordered_map<K, V>> map_cloneMutable(const std::shared_ptr<ordered_map<K, V>>& m, const char* file, int32_t line) {
    if (!m) {
        panic_at(file, line, "Attempted to cloneMutable from null map");
    }
    m->validate_invariants("map_cloneMutable");
    return std::make_shared<ordered_map<K, V>>(*m);
}

template <typename T>
std::shared_ptr<std::vector<T>> set_values(const std::shared_ptr<ordered_set<T>>& s, const char* file, int32_t line) {
    if (!s) {
        panic_at(file, line, "Attempted to read values from null set");
    }
    s->validate_invariants("set_values");
    auto result = std::make_shared<std::vector<T>>();
    result->reserve(s->size());
    for (const auto& value : *s) result->push_back(value);
    return result;
}

template <typename T>
std::shared_ptr<ordered_set<T>> set_drainToReadonly(const std::shared_ptr<ordered_set<T>>& s, const char* file, int32_t line) {
    if (!s) {
        panic_at(file, line, "Attempted to drainToReadonly from null set");
    }
    s->validate_invariants("set_drainToReadonly source");
    auto result = std::make_shared<ordered_set<T>>(std::move(*s));
    s->clear();
    result->validate_invariants("set_drainToReadonly result");
    return result;
}

template <typename T>
std::shared_ptr<ordered_set<T>> set_buildReadonly(const std::shared_ptr<ordered_set<T>>& s, const char* file, int32_t line) {
    return set_drainToReadonly(s, file, line);
}

template <typename T>
std::shared_ptr<ordered_set<T>> set_cloneReadonly(const std::shared_ptr<ordered_set<T>>& s, const char* file, int32_t line) {
    if (!s) {
        panic_at(file, line, "Attempted to cloneReadonly from null set");
    }
    s->validate_invariants("set_cloneReadonly");
    return std::make_shared<ordered_set<T>>(*s);
}

template <typename T>
std::shared_ptr<ordered_set<T>> set_cloneMutable(const std::shared_ptr<ordered_set<T>>& s, const char* file, int32_t line) {
    if (!s) {
        panic_at(file, line, "Attempted to cloneMutable from null set");
    }
    s->validate_invariants("set_cloneMutable");
    return std::make_shared<ordered_set<T>>(*s);
}

// ============================================================================
// Print utilities
// ============================================================================

template <typename T>
inline void println(const T& val) {
    if constexpr (std::is_same_v<T, std::string>) {
        std::cout << val << std::endl;
    } else if constexpr (std::is_same_v<T, const char*>) {
        std::cout << val << std::endl;
    } else {
        std::cout << to_string(val) << std::endl;
    }
}

inline void println() {
    std::cout << std::endl;
}

template <typename T>
inline void print(const T& val) {
    if constexpr (std::is_same_v<T, std::string>) {
        std::cout << val;
    } else if constexpr (std::is_same_v<T, const char*>) {
        std::cout << val;
    } else {
        std::cout << to_string(val);
    }
}

template <typename T>
inline void print_flushed(const T& val) {
    print(val);
    std::cout.flush();
}

// ============================================================================
// Range utilities
// ============================================================================

struct Range {
    int32_t lowerBound;
    int32_t upperBound;

    struct Iterator {
        int32_t current;

        int32_t operator*() const { return current; }
        Iterator& operator++() {
            ++current;
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() const {
        bool rev = lowerBound > upperBound;
        if (rev) return Iterator{lowerBound};
        return Iterator{lowerBound};
    }
    Iterator end() const {
        bool rev = lowerBound > upperBound;
        if (rev) return Iterator{lowerBound};
        return Iterator{upperBound};
    }
};

inline Range range(int32_t start, int32_t end) {
    return Range{start, end + 1};
}

inline Range range_exclusive(int32_t start, int32_t end) {
    return Range{start, end};
}

// ============================================================================
// Promise<T> — async result wrapper
// ============================================================================

template <typename T>
class Promise {
    std::shared_future<T> future_;
public:
    explicit Promise(std::future<T>&& f) : future_(f.share()) {}
    explicit Promise(std::shared_future<T> f) : future_(std::move(f)) {}

    bool ready() const {
        return future_.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready;
    }

    doof::Result<T, std::string> get() const {
        try {
            doof::wait_with_cpu_token_released(future_);
            return doof::Success<T>{future_.get()};
        } catch (const doof::Panic&) {
            throw;
        } catch (const std::exception& e) {
            return doof::Failure<std::string>{std::string(e.what())};
        } catch (...) {
            return doof::Failure<std::string>{std::string("unknown error")};
        }
    }
};

// Specialization for void
template <>
class Promise<void> {
    std::shared_future<void> future_;
public:
    explicit Promise(std::future<void>&& f) : future_(f.share()) {}
    explicit Promise(std::shared_future<void> f) : future_(std::move(f)) {}

    bool ready() const {
        return future_.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready;
    }

    doof::Result<void, std::string> get() const {
        try {
            doof::wait_with_cpu_token_released(future_);
            future_.get();
            return doof::Success<void>{};
        } catch (const doof::Panic&) {
            throw;
        } catch (const std::exception& e) {
            return doof::Failure<std::string>{std::string(e.what())};
        } catch (...) {
            return doof::Failure<std::string>{std::string("unknown error")};
        }
    }
};

template <typename T>
doof::Result<T, std::string> promise_take_first_completed(
    const std::shared_ptr<std::vector<doof::Promise<T>>>& promises) {
    if (promises->empty()) {
        return doof::Failure<std::string>{std::string("cannot take a completed promise from an empty array")};
    }
    while (true) {
        const auto observed = doof::detail::PromiseCompletionNotifier::shared().generation();
        for (std::size_t index = 0; index < promises->size(); ++index) {
            if (!(*promises)[index].ready()) {
                continue;
            }
            auto promise = std::move((*promises)[index]);
            promises->erase(promises->begin() + static_cast<std::ptrdiff_t>(index));
            return promise.get();
        }
        doof::detail::PromiseCompletionNotifier::shared().wait_for_change(observed);
    }
}

// Central async-task submission boundary. CPU execution is bounded by the
// runtime scheduler, while waits may relinquish their token so nested work
// cannot starve.
template <typename R, typename F>
doof::Promise<R> submit_async(F&& f) {
    auto prom = std::make_shared<std::promise<R>>();
    auto fut = prom->get_future();
    auto task = std::make_shared<std::decay_t<F>>(std::forward<F>(f));
    doof::detail::RuntimeScheduler::shared().submit([prom, task]() mutable {
        try {
            if constexpr (std::is_void_v<R>) {
                (*task)();
                prom->set_value();
            } else {
                prom->set_value((*task)());
            }
        } catch (...) {
            prom->set_exception(std::current_exception());
        }
        doof::detail::PromiseCompletionNotifier::shared().notify();
    });
    return doof::Promise<R>(std::move(fut));
}

template <typename R, typename... Args>
doof::Promise<R> callback<R(Args...)>::post(Args... args) const {
    if (!fn_) {
        doof::panic("callback posted before initialization");
    }
    auto owner = owner_ ? owner_ : &doof::detail::ApplicationDomain::shared();

    auto prom = std::make_shared<std::promise<R>>();
    auto fut = prom->get_future();
    auto self = *this;
    auto packedArgs = std::make_tuple(std::forward<Args>(args)...);
    owner->enqueue_callback([self, prom, packedArgs = std::move(packedArgs)]() mutable {
        try {
            if constexpr (std::is_void_v<R>) {
                std::apply([&](auto&&... unpacked) {
                    doof::detail::call_callback_unchecked(self, std::forward<decltype(unpacked)>(unpacked)...);
                }, std::move(packedArgs));
                prom->set_value();
            } else {
                prom->set_value(std::apply([&](auto&&... unpacked) -> R {
                    return doof::detail::call_callback_unchecked(self, std::forward<decltype(unpacked)>(unpacked)...);
                }, std::move(packedArgs)));
            }
        } catch (...) {
            prom->set_exception(std::current_exception());
        }
        doof::detail::PromiseCompletionNotifier::shared().notify();
    });
    return doof::Promise<R>(std::move(fut));
}

// ============================================================================
// Actor<T> — serial message queue actor
// ============================================================================

template <typename T>
class Actor : public std::enable_shared_from_this<Actor<T>>, public detail::CallbackDomain {
    // Actor state remains reachable only through this actor until retirement,
    // but class methods require shared ownership for Doof's `this` lowering.
    std::shared_ptr<T> instance_;
    std::queue<std::function<void()>> mailbox_;
    std::mutex mutex_;
    bool accepting_ = true;
    bool scheduled_ = false;

    void schedule_locked() {
        if (scheduled_ || mailbox_.empty()) {
            return;
        }
        scheduled_ = true;
        auto self = this->shared_from_this();
        doof::detail::RuntimeScheduler::shared().submit([self] {
            self->run_one();
        });
    }

    void run_one() {
        std::function<void()> task;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            task = std::move(mailbox_.front());
            mailbox_.pop();
        }

        try {
            doof::detail::ActiveActorScope active(this);
            task();
        } catch (...) {
            // Language-facing actor and callback submissions capture their own
            // failures. Preserve mailbox progress if native code enqueues a
            // task that unexpectedly throws.
        }

        std::lock_guard<std::mutex> lock(mutex_);
        scheduled_ = false;
        schedule_locked();
    }

public:
    template <typename... Args>
    explicit Actor(Args&&... args)
        : instance_(std::make_shared<T>(std::forward<Args>(args)...)) {}

    // Synchronous call — enqueue and block until complete
    template <typename R, typename F>
    R call_sync(F&& f) {
        if constexpr (std::is_void_v<R>) {
            auto prom = std::make_shared<std::promise<void>>();
            auto fut = prom->get_future();
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (!accepting_) doof::panic("actor is retiring or retired");
                mailbox_.push([this, f = std::forward<F>(f), prom]() {
                    try {
                        f(*instance_);
                        prom->set_value();
                    } catch (...) {
                        prom->set_exception(std::current_exception());
                    }
                });
                schedule_locked();
            }
            doof::wait_with_cpu_token_released(fut);
            return fut.get();
        } else {
            auto prom = std::make_shared<std::promise<R>>();
            auto fut = prom->get_future();
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (!accepting_) doof::panic("actor is retiring or retired");
                mailbox_.push([this, f = std::forward<F>(f), prom]() {
                    try {
                        prom->set_value(f(*instance_));
                    } catch (...) {
                        prom->set_exception(std::current_exception());
                    }
                });
                schedule_locked();
            }
            doof::wait_with_cpu_token_released(fut);
            return fut.get();
        }
    }

    // Asynchronous call — enqueue and return a Promise
    template <typename R, typename F>
    doof::Promise<R> call_async(F&& f) {
        auto prom = std::make_shared<std::promise<R>>();
        auto fut = prom->get_future();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!accepting_) doof::panic("actor is retiring or retired");
            if constexpr (std::is_void_v<R>) {
                mailbox_.push([this, f = std::forward<F>(f), prom]() {
                    try {
                        f(*instance_);
                        prom->set_value();
                    } catch (...) {
                        prom->set_exception(std::current_exception());
                    }
                    doof::detail::PromiseCompletionNotifier::shared().notify();
                });
            } else {
                mailbox_.push([this, f = std::forward<F>(f), prom]() {
                    try {
                        prom->set_value(f(*instance_));
                    } catch (...) {
                        prom->set_exception(std::current_exception());
                    }
                    doof::detail::PromiseCompletionNotifier::shared().notify();
                });
            }
            schedule_locked();
        }
        return doof::Promise<R>(std::move(fut));
    }

    void enqueue_callback(std::function<void()> task) override {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!accepting_) doof::panic("actor is retiring or retired");
            mailbox_.push(std::move(task));
            schedule_locked();
        }
    }

    // Retire the actor — drain accepted work, stop, and return owned state.
    std::shared_ptr<T> retire() {
        auto prom = std::make_shared<std::promise<std::shared_ptr<T>>>();
        auto fut = prom->get_future();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!accepting_) doof::panic("actor is already retiring or retired");
            accepting_ = false;
            mailbox_.push([this, prom]() {
                try {
                    if (!instance_) doof::panic("actor is already retired");
                    prom->set_value(std::move(instance_));
                } catch (...) {
                    prom->set_exception(std::current_exception());
                }
            });
            schedule_locked();
        }
        doof::wait_with_cpu_token_released(fut);
        std::shared_ptr<T> value = fut.get();
        return value;
    }

    // Stop accepting work and drain the already accepted mailbox.
    void stop() {
        auto prom = std::make_shared<std::promise<void>>();
        auto fut = prom->get_future();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!accepting_) {
                return;
            }
            accepting_ = false;
            mailbox_.push([prom] {
                prom->set_value();
            });
            schedule_locked();
        }
        doof::wait_with_cpu_token_released(fut);
        fut.get();
    }

    ~Actor() {
        // Queued scheduler closures retain the actor until its mailbox drains.
        // Destruction therefore observes no accepted work requiring a join.
        accepting_ = false;
    }
};

template <typename T>
struct metadata_inner { using type = T; };

template <typename T>
struct metadata_inner<std::shared_ptr<T>> { using type = T; };

template <typename T>
using metadata_inner_t = typename metadata_inner<std::decay_t<T>>::type;

} // namespace doof

// ============================================================================
// Metadata reflection types (outside namespace for class-scoped usage)
// ============================================================================

namespace doof {

/** Per-method reflection entry with an invoke lambda. */
template <typename T>
struct MethodInvoker {
    using result_type = doof::Result<doof::JsonValue, doof::JsonValue>;

    std::function<result_type(T&, const doof::JsonValue&)> call;

    MethodInvoker() = default;

    template <typename F>
    MethodInvoker(F&& f) : call(std::forward<F>(f)) {}

    result_type operator()(T& instance, const doof::JsonValue& params) const {
        return call(instance, params);
    }

    result_type operator()(const std::shared_ptr<T>& instance, const doof::JsonValue& params) const {
        if (instance == nullptr) {
            return doof::Failure<doof::JsonValue>{doof::json_error(400, std::string("Cannot invoke method on null instance"))};
        }
        return call(*instance, params);
    }
};

/** Per-method reflection entry with an invoke callable. */
template <typename T>
struct MethodReflection {
    std::string name;
    std::string description;
    doof::JsonValue inputSchema;
    doof::JsonValue outputSchema;
    doof::MethodInvoker<T> invoke;
};

/** Structured metadata for a class — contains name, description, methods, and schema $defs. */
template <typename T>
struct ClassMetadata {
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<doof::MethodReflection<T>>> methods;
    std::optional<doof::JsonValue> defs;

    doof::Result<doof::JsonValue, doof::JsonValue> invoke(
        T& instance,
        const std::string& methodName,
        const doof::JsonValue& params
    ) const {
        if (methods != nullptr) {
            for (const auto& method : *methods) {
                if (method.name == methodName) {
                    return method.invoke(instance, params);
                }
            }
        }
        return doof::Failure<doof::JsonValue>{doof::json_error(400, std::string("Unknown method: ") + methodName)};
    }

    doof::Result<doof::JsonValue, doof::JsonValue> invoke(
        const std::shared_ptr<T>& instance,
        const std::string& methodName,
        const doof::JsonValue& params
    ) const {
        if (instance == nullptr) {
            return doof::Failure<doof::JsonValue>{doof::json_error(400, std::string("Cannot invoke method on null instance"))};
        }
        return invoke(*instance, methodName, params);
    }
};

template <typename T>
const doof::ClassMetadata<metadata_inner_t<T>>& metadata_for(const T&) {
    return metadata_inner_t<T>::_metadata;
}

template <typename T>
const doof::ClassMetadata<metadata_inner_t<T>>& metadata_for_type() {
    return metadata_inner_t<T>::_metadata;
}

} // namespace doof

// ============================================================================
// Line coverage (activated with -DDOOF_COVERAGE)
// ============================================================================

#ifdef DOOF_COVERAGE
#include <unordered_set>

namespace doof {
namespace coverage {

struct LineHit {
    int module_id;
    int line;
    bool operator==(const LineHit& o) const noexcept {
        return module_id == o.module_id && line == o.line;
    }
};

struct LineHitHash {
    std::size_t operator()(const LineHit& h) const noexcept {
        return std::hash<long long>{}(
            (static_cast<long long>(h.module_id) << 32) |
            static_cast<unsigned int>(static_cast<unsigned>(h.line)));
    }
};

inline std::unordered_set<LineHit, LineHitHash> _coverage_hits;
inline std::mutex _coverage_hits_mutex;
inline std::once_flag _coverage_registration_once;

inline void _cov_dump();

inline void _cov_ensure_registered() {
    std::call_once(_coverage_registration_once, []() {
        std::atexit(_cov_dump);
    });
}

inline void cov_mark(int module_id, int line) {
    _cov_ensure_registered();
    std::lock_guard<std::mutex> lock(_coverage_hits_mutex);
    _coverage_hits.insert(LineHit{module_id, line});
}

inline void _cov_dump() {
    std::lock_guard<std::mutex> lock(_coverage_hits_mutex);
    for (const auto& h : _coverage_hits) {
        std::cout << "__COV__ " << h.module_id << " " << h.line << "\n";
    }
    std::cout.flush();
}

} // namespace coverage
} // namespace doof
#endif
