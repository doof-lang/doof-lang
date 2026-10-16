#pragma once

#if defined(DOOF_OBSERVE)
// Winsock must precede any Windows headers transitively included by the C++ library.
#include "doof_observer_platform.hpp"
#endif

// doof_runtime.hpp — Runtime support for transpiled Doof code
// Canonical source template and generated header for the Doof runtime.

#include <algorithm>
#include <atomic>
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

namespace doof {

#if defined(DOOF_OBSERVE)
namespace observe {
void publish_metric(const std::string& name, int64_t value);
}
#endif

class Never;
[[noreturn]] inline Never panic(const std::string& msg);

inline int32_t hardware_concurrency() {
    const auto detected = std::thread::hardware_concurrency();
    return static_cast<int32_t>(detected == 0 ? 1 : detected);
}

// ============================================================================
// Metrics — process-local counters
// ============================================================================

namespace metrics {

inline std::unordered_map<std::string, int64_t> counters;
inline std::mutex counters_mutex;

inline void increment_counter(const std::string& name, int64_t value) {
    int64_t total = 0;
    {
        std::lock_guard<std::mutex> lock(counters_mutex);
        total = (counters[name] += value);
    }
#if defined(DOOF_OBSERVE)
    try { observe::publish_metric(name, total); } catch (...) { /* observation is best effort */ }
#endif
}

inline std::vector<std::pair<std::string, int64_t>> snapshot_pairs() {
    std::vector<std::pair<std::string, int64_t>> snapshot;
    {
        std::lock_guard<std::mutex> lock(counters_mutex);
        snapshot.reserve(counters.size());
        for (const auto& item : counters) {
            snapshot.push_back(item);
        }
    }
    std::sort(snapshot.begin(), snapshot.end(), [](const auto& left, const auto& right) {
        return left.first < right.first;
    });
    return snapshot;
}

inline std::string snapshot_prometheus() {
    const auto snapshot = snapshot_pairs();
    std::ostringstream output;
    for (const auto& item : snapshot) {
        output << item.first << " " << item.second << "\n";
    }
    return output.str();
}

} // namespace metrics

#if defined(DOOF_OBSERVE)
#include "doof_observer.hpp"
#endif

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
// initially constructed. Copy/move operations keep variants containing Never
// usable when another arm is active; there is no live Never value to copy.
// The conversion surface keeps unreachable expressions well-typed in C++.
class Never final {
public:
    explicit Never() = delete;
    Never(const Never&) = default;
    Never(Never&&) = default;
    Never& operator=(const Never&) = default;
    Never& operator=(Never&&) = default;

    template <typename T>
    [[noreturn]] operator T() const {
        std::abort();
    }
};

[[noreturn]] inline Never panic(const std::string& msg) {
    throw Panic(msg);
}

// The executable entry wrapper calls this only after a Panic has escaped all
// Doof code. Keep it named so native debuggers can distinguish an unhandled
// panic from a panic that catchPanic recovers.
#if defined(_MSC_VER)
#define DOOF_NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#define DOOF_NOINLINE __attribute__((noinline))
#else
#define DOOF_NOINLINE
#endif

[[noreturn]] DOOF_NOINLINE inline void unhandled_panic(const Panic& panic) {
    std::cerr << "panic: " << panic.what() << std::endl;
#if defined(DOOF_OBSERVE)
    // Flush the final diagnostic to connected observers before abort skips atexit.
    try {
        if (observe::running.load()) {
            observe::publish_event("panic", "{\"message\":\"" + observe::json_escape(panic.message()) + "\"}");
            observe::stop_server();
        }
    } catch (...) { /* observation must not mask the panic */ }
#endif
    std::abort();
}

#undef DOOF_NOINLINE

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

// The sole alternative of an interface with no implementing classes. No value
// of such an interface can exist, so code that reaches into one is unreachable;
// the placeholder only gives parameters, fields, and locals a C++ type.
struct NoImplementations {
    bool operator==(const NoImplementations&) const { return true; }
    bool operator!=(const NoImplementations&) const { return false; }
};

template <typename R>
[[noreturn]] R no_implementations(const char* interfaceName) {
    panic(std::string("interface ") + interfaceName + " has no implementing classes");
}

inline void assert_(bool condition, const std::string& message) {
    if (!condition) {
        panic("Assertion failed: " + message);
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

struct WeakReferenceError {
    bool operator==(const WeakReferenceError&) const { return true; }
};

template <typename T>
std::optional<std::shared_ptr<T>> lock_weak(const std::weak_ptr<T>& value) {
    auto locked = value.lock();
    if (!locked) return std::nullopt;
    return locked;
}

template <typename... T>
std::optional<std::variant<std::shared_ptr<T>...>> lock_weak(const std::variant<std::weak_ptr<T>...>& value) {
    using Locked = std::variant<std::shared_ptr<T>...>;
    return std::visit([](const auto& weak) -> std::optional<Locked> {
        auto locked = weak.lock();
        if (!locked) return std::nullopt;
        return Locked{std::move(locked)};
    }, value);
}

namespace detail {
enum class TryEnqueueResult {
    Accepted,
    Full,
    Retired,
};

class CallbackDomain : public std::enable_shared_from_this<CallbackDomain> {
public:
    virtual ~CallbackDomain() = default;
    virtual void enqueue_callback(std::function<void()> task) = 0;
    // Accept one callback post without blocking. A full mailbox or a domain
    // that no longer accepts work rejects the task instead of waiting or
    // panicking.
    virtual TryEnqueueResult try_enqueue_callback(std::function<void()> task) = 0;
    // Accepted completions reserve a future mailbox delivery across retirement.
    virtual void reserve_completion() {}
    virtual void cancel_completion() {}
    virtual void enqueue_completion(std::function<void()> task) {
        enqueue_callback(std::move(task));
    }
    // Queue the release of state owned by this domain. Releases never block
    // and do not count against mailbox capacity; false means the domain no
    // longer accepts work and the caller must release the state itself.
    virtual bool enqueue_release(std::function<void()> task) = 0;
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

// Isolated jobs have no owning domain. Callbacks created there keep their
// existing unowned behavior, but are marked so they cannot be registered as
// deferred completion receivers that would outlive the job.
inline thread_local bool active_isolated_task = false;

class IsolatedTaskScope {
    bool previous_;
public:
    IsolatedTaskScope() : previous_(active_isolated_task) {
        active_isolated_task = true;
    }

    ~IsolatedTaskScope() {
        active_isolated_task = previous_;
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

    // Only non-blocking posts observe the application mailbox capacity; every
    // other delivery to the application domain stays unbounded.
    TryEnqueueResult try_enqueue_callback(std::function<void()> task) override;

    bool enqueue_release(std::function<void()> task) override {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            releases_.push(std::move(task));
        }
        notify_ready();
        return true;
    }

    // Release root-owned state that other domains dropped. Every dispatch
    // below runs queued releases first, so pumping the mailbox also releases;
    // native command-line entrypoints drain them once more after main.
    int32_t drain_releases() {
        int32_t released = 0;
        while (true) {
            std::function<void()> task;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (releases_.empty()) {
                    return released;
                }
                task = std::move(releases_.front());
                releases_.pop();
            }

            ActiveActorScope active(this);
            task();
            ++released;
        }
    }

    int32_t drain_ready() {
        int32_t dispatched = 0;
        while (true) {
            drain_releases();
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
        while (true) {
            drain_releases();
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                ready_.wait(lock, [this] {
                    return !releases_.empty() || !mailbox_.empty() || keep_alive_count_ == 0;
                });
                if (mailbox_.empty()) {
                    if (!releases_.empty()) continue;
                    return false;
                }
                task = std::move(mailbox_.front());
                mailbox_.pop();
            }

            ActiveActorScope active(this);
            task();
            return true;
        }
    }

    // Native command-line entrypoints drain only registered promise
    // completions after main; other keep-alive sources (channels, timers)
    // still require the host or `runMainEventLoop` to pump the mailbox.
    bool dispatch_pending_completion() {
        while (true) {
            drain_releases();
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex_);
                ready_.wait(lock, [this] {
                    return !releases_.empty() || !mailbox_.empty() || pending_completion_count_ == 0;
                });
                if (pending_completion_count_ == 0) {
                    return false;
                }
                if (mailbox_.empty()) continue;
                task = std::move(mailbox_.front());
                mailbox_.pop();
            }

            ActiveActorScope active(this);
            task();
            return true;
        }
    }

    void add_pending_completion() {
        std::lock_guard<std::mutex> lock(mutex_);
        ++pending_completion_count_;
        ++keep_alive_count_;
    }

    void remove_pending_completion() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            --pending_completion_count_;
            --keep_alive_count_;
        }
        notify_ready();
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
    std::queue<std::function<void()>> releases_;
    int64_t keep_alive_count_ = 0;
    int64_t pending_completion_count_ = 0;
    std::function<void()> wake_handler_;
};
} // namespace detail

inline detail::CallbackDomain* current_actor_domain() {
    return detail::active_actor_domain;
}

// ============================================================================
// Wait-for graph — blocking-wait cycle detection between serial domains
// ============================================================================

namespace detail {

// Set by the producer of an awaited result before it can begin another wait,
// so a satisfied waiter that has not yet woken never contributes a false cycle.
struct WaitSignal {
    std::atomic<bool> satisfied{false};

    void satisfy() { satisfied.store(true, std::memory_order_release); }
    bool is_satisfied() const { return satisfied.load(std::memory_order_acquire); }
};

// Static initialization runs on the thread that owns the application mailbox.
inline const std::thread::id application_thread_id = std::this_thread::get_id();

// The temporary domain of the isolated async job running on this thread.
inline thread_local const void* active_task_node = nullptr;

class ActiveTaskScope {
    const void* previous_;
public:
    explicit ActiveTaskScope(const void* node) : previous_(active_task_node) {
        active_task_node = node;
    }

    ~ActiveTaskScope() {
        active_task_node = previous_;
    }
};

// The serial domain that a blocking wait on this thread stalls. Threads that
// are neither actors, isolated jobs, nor the application thread are untracked:
// nothing can wait on them, so they never appear inside a cycle.
inline const void* current_wait_node() {
    if (active_actor_domain) return active_actor_domain;
    if (active_task_node) return active_task_node;
    if (std::this_thread::get_id() == application_thread_id) return &ApplicationDomain::shared();
    return nullptr;
}

// Each serial domain blocks on at most one target at a time. A wait whose
// target chain leads back to the waiter can never be satisfied, so it panics
// with the chain instead of hanging. Waits on several producers at once (such
// as takeFirstCompleted) are not tracked.
class WaitGraph {
    struct Edge {
        const void* target;
        std::shared_ptr<WaitSignal> signal;
        const char* kind;
    };

    std::mutex mutex_;
    std::unordered_map<const void*, Edge> edges_;

public:
    static WaitGraph& shared() {
        static auto* graph = new WaitGraph();
        return *graph;
    }

    // Records waiter -> target unless the wait is already satisfied or untracked.
    bool enter(const void* waiter, const void* target, std::shared_ptr<WaitSignal> signal, const char* kind) {
        if (!waiter || !target || !signal) return false;
        std::string cycle;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (signal->is_satisfied()) return false;
            cycle = kind;
            const void* node = target;
            for (std::size_t hops = 0; node != waiter; ++hops) {
                auto edge = edges_.find(node);
                if (edge == edges_.end() || edge->second.signal->is_satisfied() || hops > edges_.size()) {
                    edges_[waiter] = Edge{target, std::move(signal), kind};
                    return true;
                }
                cycle += " -> ";
                cycle += edge->second.kind;
                node = edge->second.target;
            }
        }
        doof::panic("deadlock: blocking wait would never complete (" + cycle + ")");
    }

    void leave(const void* waiter) {
        std::lock_guard<std::mutex> lock(mutex_);
        edges_.erase(waiter);
    }
};

class WaitScope {
    const void* waiter_ = nullptr;
public:
    WaitScope(const void* target, std::shared_ptr<WaitSignal> signal, const char* kind) {
        const void* waiter = current_wait_node();
        if (WaitGraph::shared().enter(waiter, target, std::move(signal), kind)) waiter_ = waiter;
    }

    WaitScope(const WaitScope&) = delete;
    WaitScope& operator=(const WaitScope&) = delete;

    ~WaitScope() {
        if (waiter_) WaitGraph::shared().leave(waiter_);
    }
};

} // namespace detail

// ============================================================================
// Runtime scheduler — bounded CPU execution for async and actor work
// ============================================================================

struct RuntimeSchedulerOptions {
    std::size_t maximum_cpu_parallelism;
    std::size_t retained_worker_count;
    std::chrono::milliseconds excess_worker_idle_timeout;
    // Senders block once an actor holds this many accepted calls and posts.
    // Completion deliveries and retirement requests are never bounded.
    std::size_t actor_mailbox_capacity;
    // Async-block and isolated-call submissions that have not yet started.
    std::size_t async_queue_capacity;
    // Queued application-domain messages at which `tryPost` reports "full".
    // Other application deliveries never observe this capacity.
    std::size_t application_mailbox_capacity;

    RuntimeSchedulerOptions()
        : maximum_cpu_parallelism([] {
              const auto detected = std::thread::hardware_concurrency();
              return static_cast<std::size_t>(detected == 0 ? 1 : detected);
          }()),
          retained_worker_count(maximum_cpu_parallelism),
          excess_worker_idle_timeout(std::chrono::seconds(30)),
          actor_mailbox_capacity(65536),
          async_queue_capacity(65536),
          application_mailbox_capacity(65536) {}
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
    std::size_t pending_async_jobs_ = 0;
    std::condition_variable async_space_;
    std::atomic<std::size_t> actor_mailbox_capacity_{RuntimeSchedulerOptions().actor_mailbox_capacity};
    std::atomic<std::size_t> application_mailbox_capacity_{RuntimeSchedulerOptions().application_mailbox_capacity};

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
        if (options.actor_mailbox_capacity == 0) {
            doof::panic("runtime scheduler actor mailbox capacity must be at least 1");
        }
        if (options.async_queue_capacity == 0) {
            doof::panic("runtime scheduler async queue capacity must be at least 1");
        }
        if (options.application_mailbox_capacity == 0) {
            doof::panic("runtime scheduler application mailbox capacity must be at least 1");
        }

        std::lock_guard<std::mutex> lock(mutex_);
        if (started_) {
            doof::panic("runtime scheduler cannot be configured after work has started");
        }
        options_ = options;
        actor_mailbox_capacity_.store(options.actor_mailbox_capacity);
        application_mailbox_capacity_.store(options.application_mailbox_capacity);
    }

    std::size_t actor_mailbox_capacity() const {
        return actor_mailbox_capacity_.load();
    }

    std::size_t application_mailbox_capacity() const {
        return application_mailbox_capacity_.load();
    }

    // Reserve one not-yet-started async submission. A full queue blocks the
    // submitter with its CPU token released, so started work keeps draining it.
    void acquire_async_slot() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            started_ = true;
            if (pending_async_jobs_ < options_.async_queue_capacity) {
                ++pending_async_jobs_;
                return;
            }
        }
        const bool released = relinquish_current_worker_token();
        {
            std::unique_lock<std::mutex> lock(mutex_);
            async_space_.wait(lock, [this] { return pending_async_jobs_ < options_.async_queue_capacity; });
            ++pending_async_jobs_;
        }
        if (released) reacquire_current_worker_token();
    }

    void release_async_slot() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            --pending_async_jobs_;
        }
        async_space_.notify_one();
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

// The capacity counts every queued application message, so completions and
// other deliveries waiting to run also hold back new non-blocking posts.
inline TryEnqueueResult ApplicationDomain::try_enqueue_callback(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (mailbox_.size() >= RuntimeScheduler::shared().application_mailbox_capacity()) {
            return TryEnqueueResult::Full;
        }
        mailbox_.push(std::move(task));
    }
    notify_ready();
    return TryEnqueueResult::Accepted;
}

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

template <typename T> struct Success;
template <typename E> struct Failure;

template <typename Signature>
class callback;

namespace detail {
template <typename R, typename... Args>
R call_callback_unchecked(const doof::callback<R(Args...)>& cb, Args... args);

// Closure state holds captures of its owning domain, but callback copies may
// cross into other domains. When the last copy drops elsewhere, the state is
// released on its owner so captured destructors run where they were created.
// A retired or expired actor owner can no longer run work; its captures were
// created by isolated actor code, so releasing them here is safe. Unowned
// state (isolated jobs, untracked native threads) is released in place.
template <typename State>
struct CallbackStateRelease {
    CallbackDomain* owner = nullptr;
    std::weak_ptr<CallbackDomain> lifetime;

    void operator()(State* state) const {
        if (!owner || current_wait_node() == static_cast<const void*>(owner)) {
            delete state;
            return;
        }
        auto release = [state] { delete state; };
        if (ApplicationDomain::is_application_domain(owner)) {
            ApplicationDomain::shared().enqueue_release(std::move(release));
            return;
        }
        auto locked = lifetime.lock();
        if (locked && locked->enqueue_release(std::move(release))) return;
        delete state;
    }
};
}

template <typename R, typename... Args>
class callback<R(Args...)> {
    // Copies retain the same callable identity and mutable closure state.
    std::shared_ptr<std::function<R(Args...)>> fn_;
    detail::CallbackDomain* owner_ = nullptr;
    std::weak_ptr<detail::CallbackDomain> owner_lifetime_;
    bool isolated_ = false;

public:
    callback() = default;

    template <
        typename F,
        typename = std::enable_if_t<!std::is_same_v<std::decay_t<F>, callback>>
    >
    callback(F&& f)
        : owner_(doof::current_actor_domain()),
          owner_lifetime_(owner_ ? owner_->weak_from_this() : std::weak_ptr<detail::CallbackDomain>{}),
          isolated_(!owner_ && detail::active_isolated_task) {
        using State = std::function<R(Args...)>;
        fn_ = std::shared_ptr<State>(
            new State(std::forward<F>(f)),
            detail::CallbackStateRelease<State>{owner_, owner_lifetime_});
    }

    explicit operator bool() const {
        return fn_ && static_cast<bool>(*fn_);
    }

    bool operator==(const callback& other) const { return fn_ == other.fn_; }
    bool operator!=(const callback& other) const { return !(*this == other); }

    R call(Args... args) const {
        auto fn = fn_; // A callback may clear its owning native property while running.
        if (!fn || !*fn) {
            doof::panic("callback invoked before initialization");
        }
        if (owner_ != doof::current_actor_domain()) {
            doof::panic("callback invoked outside owning actor domain");
        }
        if constexpr (std::is_void_v<R>) {
            (*fn)(std::forward<Args>(args)...);
        } else {
            return (*fn)(std::forward<Args>(args)...);
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

    // Spelled as the variant because Result is declared after callbacks.
    std::variant<doof::Success<doof::Promise<R>>, doof::Failure<std::string>> tryPost(Args... args) const;

    void dispatch(Args... args) const {
        static_assert(std::is_void_v<R>, "callback.dispatch is only available for void callbacks");
        if (!static_cast<bool>(*this)) {
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
    template <typename T> friend class Promise;
    template <typename CR, typename... CArgs>
    friend CR detail::call_callback_unchecked(const doof::callback<CR(CArgs...)>& cb, CArgs... args);

    R call_unchecked(Args... args) const {
        auto fn = fn_;
        if (!fn || !*fn) {
            doof::panic("callback invoked before initialization");
        }
        if constexpr (std::is_void_v<R>) {
            (*fn)(std::forward<Args>(args)...);
        } else {
            return (*fn)(std::forward<Args>(args)...);
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
// Key hashing — Map keys and Set elements
// ============================================================================

// Hash consistent with Doof `==` for every checker-approved key type: scalars,
// strings, and enums by value; class and interface references by identity;
// tuples, optionals, unions, and structs by their members. Generated structs
// expose `doof_hash_value()` over the fields their `operator==` compares.
inline void key_hash_combine(std::size_t& seed, std::size_t value) {
    seed ^= value + static_cast<std::size_t>(0x9e3779b97f4a7c15ULL) + (seed << 6) + (seed >> 2);
}

template <typename T, typename = void>
struct key_hash {
    std::size_t operator()(const T& value) const { return std::hash<T>{}(value); }
};

template <typename T>
struct key_hash<T, std::void_t<decltype(std::declval<const T&>().doof_hash_value())>> {
    std::size_t operator()(const T& value) const { return value.doof_hash_value(); }
};

template <typename... Ts>
struct key_hash<std::tuple<Ts...>, void> {
    std::size_t operator()(const std::tuple<Ts...>& value) const {
        std::size_t seed = sizeof...(Ts);
        std::apply([&seed](const auto&... item) {
            (key_hash_combine(seed, key_hash<std::decay_t<decltype(item)>>{}(item)), ...);
        }, value);
        return seed;
    }
};

template <typename T>
struct key_hash<std::optional<T>, void> {
    std::size_t operator()(const std::optional<T>& value) const {
        std::size_t seed = value.has_value() ? 1 : 0;
        if (value) key_hash_combine(seed, key_hash<T>{}(*value));
        return seed;
    }
};

template <typename... Ts>
struct key_hash<std::variant<Ts...>, void> {
    std::size_t operator()(const std::variant<Ts...>& value) const {
        std::size_t seed = value.index();
        std::visit([&seed](const auto& item) {
            key_hash_combine(seed, key_hash<std::decay_t<decltype(item)>>{}(item));
        }, value);
        return seed;
    }
};

template <>
struct key_hash<NoImplementations, void> {
    std::size_t operator()(const NoImplementations&) const { return 0; }
};

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
    std::unordered_map<K, size_type, key_hash<K>> index_;
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
    std::unordered_map<T, size_type, key_hash<T>> index_;
};

template <typename T>
ordered_set(std::initializer_list<T>) -> ordered_set<T>;

// For-of iterates a private copy of the elements present at loop entry, so
// mutating or reassigning the collection in the body cannot invalidate the
// loop or cause elements to be skipped or revisited. Ordered collections copy
// only their storage; the loop never needs their lookup index.
template <typename T>
std::vector<T> iteration_snapshot(const std::shared_ptr<std::vector<T>>& values) {
    return *values;
}

template <typename K, typename V>
std::vector<std::pair<K, V>> iteration_snapshot(const std::shared_ptr<ordered_map<K, V>>& entries) {
    return std::vector<std::pair<K, V>>(entries->begin(), entries->end());
}

template <typename T>
std::vector<T> iteration_snapshot(const std::shared_ptr<ordered_set<T>>& values) {
    return std::vector<T>(values->begin(), values->end());
}

// ============================================================================
// Intrinsic Result arms and their ordinary variant alias
// ============================================================================

// The arms are intrinsic structs: equality compares the payload field, as
// generated struct equality does, and stays dependent until it is used.
template <typename T> struct Success {
    T value;
    template <typename _DoofOther = Success>
    bool operator==(const _DoofOther& other) const { return value == other.value; }
    template <typename _DoofOther = Success>
    bool operator!=(const _DoofOther& other) const { return !(*this == other); }
};
template <> struct Success<void> {
    bool operator==(const Success&) const { return true; }
    bool operator!=(const Success&) const { return false; }
};
template <typename E> struct Failure {
    E error;
    template <typename _DoofOther = Failure>
    bool operator==(const _DoofOther& other) const { return error == other.error; }
    template <typename _DoofOther = Failure>
    bool operator!=(const _DoofOther& other) const { return !(*this == other); }
};
template <> struct Failure<void> {
    bool operator==(const Failure&) const { return true; }
    bool operator!=(const Failure&) const { return false; }
};

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
// SerialValue — first-class JSON runtime value
// ============================================================================

struct SerialValue;

using SerialArray = std::shared_ptr<std::vector<SerialValue>>;
using SerialBytes = std::shared_ptr<std::vector<uint8_t>>;
using SerialObject = std::shared_ptr<ordered_map<std::string, SerialValue>>;
using SerialStorage = std::variant<std::monostate, bool, int32_t, int64_t, float, double, std::string, SerialArray, SerialBytes, SerialObject>;

struct SerialValue : SerialStorage {
    using SerialStorage::SerialStorage;

    SerialValue() : SerialStorage(std::monostate{}) {}
    SerialValue(std::nullptr_t) : SerialStorage(std::monostate{}) {}
    SerialValue(const char* v) : SerialStorage(std::string(v)) {}
};

template <typename T>
inline SerialValue serial_value(T&& value) {
    return SerialValue(std::forward<T>(value));
}

inline const SerialStorage& serial_storage(const SerialValue& value) {
    return static_cast<const SerialStorage&>(value);
}

inline SerialStorage& serial_storage(SerialValue& value) {
    return static_cast<SerialStorage&>(value);
}

inline bool serial_is_null(const SerialValue& value) {
    return std::holds_alternative<std::monostate>(serial_storage(value));
}

inline bool serial_is_boolean(const SerialValue& value) {
    return std::holds_alternative<bool>(serial_storage(value));
}

inline bool serial_is_number(const SerialValue& value) {
    return std::holds_alternative<int32_t>(serial_storage(value))
        || std::holds_alternative<int64_t>(serial_storage(value))
        || std::holds_alternative<float>(serial_storage(value))
        || std::holds_alternative<double>(serial_storage(value));
}

// JSON has a single number kind, so integral targets accept any number whose
// value is whole and inside the target range, whatever representation parsing
// chose. Out-of-range or fractional values never truncate or wrap.
inline bool serial_fits_integer(const SerialValue& value, int64_t minimum, int64_t maximum) {
    const auto& storage = serial_storage(value);
    if (const auto* result = std::get_if<int32_t>(&storage)) return *result >= minimum && *result <= maximum;
    if (const auto* result = std::get_if<int64_t>(&storage)) return *result >= minimum && *result <= maximum;
    double number = 0.0;
    if (const auto* result = std::get_if<float>(&storage)) number = static_cast<double>(*result);
    else if (const auto* result = std::get_if<double>(&storage)) number = *result;
    else return false;
    if (!std::isfinite(number) || std::trunc(number) != number) return false;
    // Every whole double in [-2^63, 2^63) converts to int64_t exactly.
    if (number < -9223372036854775808.0 || number >= 9223372036854775808.0) return false;
    const auto whole = static_cast<int64_t>(number);
    return whole >= minimum && whole <= maximum;
}

inline bool serial_fits_byte(const SerialValue& value) { return serial_fits_integer(value, 0, 255); }

inline bool serial_fits_int(const SerialValue& value) {
    return serial_fits_integer(value, std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
}

inline bool serial_fits_long(const SerialValue& value) {
    return serial_fits_integer(value, std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
}

inline bool serial_is_integer(const SerialValue& value) {
    return std::holds_alternative<int32_t>(serial_storage(value)) ||
           std::holds_alternative<int64_t>(serial_storage(value));
}

inline bool serial_is_string(const SerialValue& value) {
    return std::holds_alternative<std::string>(serial_storage(value));
}

inline bool serial_is_bytes(const SerialValue& value) {
    return std::holds_alternative<SerialBytes>(serial_storage(value));
}

inline bool serial_is_array(const SerialValue& value) {
    return std::holds_alternative<SerialArray>(serial_storage(value));
}

inline bool serial_is_object(const SerialValue& value) {
    return std::holds_alternative<SerialObject>(serial_storage(value));
}

inline const char* serial_type_name(const SerialValue& value) {
    if (serial_is_null(value)) return "null";
    if (serial_is_boolean(value)) return "boolean";
    if (serial_is_number(value)) return "number";
    if (serial_is_string(value) || serial_is_bytes(value)) return "string";
    if (serial_is_array(value)) return "array";
    if (serial_is_object(value)) return "object";
    return "unknown";
}

inline const SerialArray::element_type* serial_as_array(const SerialValue& value) {
    const auto* array = std::get_if<SerialArray>(&serial_storage(value));
    if (array == nullptr || !*array) return nullptr;
    return array->get();
}

inline std::string serial_bytes_to_base64(const SerialBytes& bytes) {
    static constexpr char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (bytes == nullptr) return "";
    std::string result;
    result.reserve((bytes->size() + 2) / 3 * 4);
    for (size_t index = 0; index < bytes->size(); index += 3) {
        const uint32_t first = (*bytes)[index];
        const uint32_t second = index + 1 < bytes->size() ? (*bytes)[index + 1] : 0;
        const uint32_t third = index + 2 < bytes->size() ? (*bytes)[index + 2] : 0;
        const size_t remaining = bytes->size() - index;
        result.push_back(alphabet[(first >> 2) & 0x3F]);
        result.push_back(alphabet[((first & 0x03) << 4) | ((second >> 4) & 0x0F)]);
        result.push_back(remaining > 1 ? alphabet[((second & 0x0F) << 2) | ((third >> 6) & 0x03)] : '=');
        result.push_back(remaining > 2 ? alphabet[third & 0x3F] : '=');
    }
    return result;
}

inline const SerialObject::element_type* serial_as_object(const SerialValue& value) {
    const auto* object = std::get_if<SerialObject>(&serial_storage(value));
    if (object == nullptr || !*object) return nullptr;
    return object->get();
}

inline SerialValue serial_error(int32_t code, std::string message) {
    auto object = std::make_shared<ordered_map<std::string, SerialValue>>();
    (*object)["code"] = serial_value(code);
    (*object)["message"] = serial_value(std::move(message));
    return serial_value(std::move(object));
}

inline bool serial_as_bool(const SerialValue& value) {
    const auto* result = std::get_if<bool>(&serial_storage(value));
    if (result == nullptr) panic("Expected boolean");
    return *result;
}

inline int32_t serial_as_int(const SerialValue& value) {
    if (!serial_fits_int(value)) panic("Expected a whole number in int range");
    if (const auto* result = std::get_if<int32_t>(&serial_storage(value))) return *result;
    if (const auto* result = std::get_if<int64_t>(&serial_storage(value))) return static_cast<int32_t>(*result);
    if (const auto* result = std::get_if<float>(&serial_storage(value))) return static_cast<int32_t>(*result);
    return static_cast<int32_t>(std::get<double>(serial_storage(value)));
}

inline int64_t serial_as_long(const SerialValue& value) {
    if (!serial_fits_long(value)) panic("Expected a whole number in long range");
    if (const auto* result = std::get_if<int32_t>(&serial_storage(value))) return *result;
    if (const auto* result = std::get_if<int64_t>(&serial_storage(value))) return *result;
    if (const auto* result = std::get_if<float>(&serial_storage(value))) return static_cast<int64_t>(*result);
    return static_cast<int64_t>(std::get<double>(serial_storage(value)));
}

inline float serial_as_float(const SerialValue& value) {
    if (const auto* result = std::get_if<int32_t>(&serial_storage(value))) return static_cast<float>(*result);
    if (const auto* result = std::get_if<int64_t>(&serial_storage(value))) return static_cast<float>(*result);
    if (const auto* result = std::get_if<float>(&serial_storage(value))) return *result;
    if (const auto* result = std::get_if<double>(&serial_storage(value))) return static_cast<float>(*result);
    panic("Expected number");
}

inline double serial_as_double(const SerialValue& value) {
    if (const auto* result = std::get_if<int32_t>(&serial_storage(value))) return static_cast<double>(*result);
    if (const auto* result = std::get_if<int64_t>(&serial_storage(value))) return static_cast<double>(*result);
    if (const auto* result = std::get_if<float>(&serial_storage(value))) return static_cast<double>(*result);
    if (const auto* result = std::get_if<double>(&serial_storage(value))) return *result;
    panic("Expected number");
}

inline const std::string& serial_as_string(const SerialValue& value) {
    const auto* result = std::get_if<std::string>(&serial_storage(value));
    if (result == nullptr) panic("Expected string");
    return *result;
}

inline SerialObject serial_object(const SerialValue& value) {
    const auto* object = std::get_if<SerialObject>(&serial_storage(value));
    if (object == nullptr || !*object) panic("Expected object");
    return *object;
}

inline bool serial_is_lenient_boolean(const SerialValue& value) {
    if (serial_is_boolean(value) || serial_is_number(value)) return true;
    if (!serial_is_string(value)) return false;
    std::string lowered = serial_as_string(value);
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return lowered == "true" || lowered == "false" || lowered == "1" || lowered == "0";
}

inline bool serial_is_lenient_number(const SerialValue& value) {
    return serial_is_number(value) || serial_is_boolean(value);
}

inline bool serial_fits_byte_lenient(const SerialValue& value) { return serial_is_boolean(value) || serial_fits_byte(value); }
inline bool serial_fits_int_lenient(const SerialValue& value) { return serial_is_boolean(value) || serial_fits_int(value); }
inline bool serial_fits_long_lenient(const SerialValue& value) { return serial_is_boolean(value) || serial_fits_long(value); }

inline bool serial_is_lenient_string(const SerialValue& value) {
    return serial_is_null(value) || serial_is_string(value) || serial_is_boolean(value) || serial_is_number(value);
}

inline bool serial_as_bool_lenient(const SerialValue& value) {
    if (serial_is_boolean(value)) return serial_as_bool(value);
    if (const auto* result = std::get_if<int32_t>(&serial_storage(value))) return *result != 0;
    if (const auto* result = std::get_if<int64_t>(&serial_storage(value))) return *result != 0;
    if (const auto* result = std::get_if<float>(&serial_storage(value))) return *result != 0.0f;
    if (const auto* result = std::get_if<double>(&serial_storage(value))) return *result != 0.0;
    if (serial_is_string(value)) {
        std::string lowered = serial_as_string(value);
        std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        });
        if (lowered == "true" || lowered == "1") return true;
        if (lowered == "false" || lowered == "0") return false;
    }
    panic("Expected lenient boolean");
}

inline int32_t serial_as_int_lenient(const SerialValue& value) {
    if (serial_is_boolean(value)) return serial_as_bool(value) ? 1 : 0;
    return serial_as_int(value);
}

inline int64_t serial_as_long_lenient(const SerialValue& value) {
    if (serial_is_boolean(value)) return serial_as_bool(value) ? 1 : 0;
    return serial_as_long(value);
}

inline float serial_as_float_lenient(const SerialValue& value) {
    if (serial_is_boolean(value)) return serial_as_bool(value) ? 1.0f : 0.0f;
    return serial_as_float(value);
}

inline double serial_as_double_lenient(const SerialValue& value) {
    if (serial_is_boolean(value)) return serial_as_bool(value) ? 1.0 : 0.0;
    return serial_as_double(value);
}

inline std::string serial_as_string_lenient(const SerialValue& value) {
    if (serial_is_null(value)) return std::string();
    if (serial_is_string(value)) return serial_as_string(value);
    if (serial_is_boolean(value)) return serial_as_bool(value) ? "true" : "false";
    if (const auto* result = std::get_if<int32_t>(&serial_storage(value))) return std::to_string(*result);
    if (const auto* result = std::get_if<int64_t>(&serial_storage(value))) return std::to_string(*result);
    if (const auto* result = std::get_if<float>(&serial_storage(value))) {
        std::ostringstream oss;
        oss << *result;
        return oss.str();
    }
    if (const auto* result = std::get_if<double>(&serial_storage(value))) {
        std::ostringstream oss;
        oss << *result;
        return oss.str();
    }
    panic("Expected lenient string");
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

inline char32_t char_from_utf8(const std::string& value) {
    const auto decoded = utf8_single_code_point(value);
    if (!decoded.has_value()) panic("Expected one valid UTF-8 character");
    return *decoded;
}

inline bool serial_is_char(const SerialValue& value, bool lenient) {
    if (lenient) {
        if (!serial_is_lenient_string(value)) return false;
        return utf8_single_code_point(serial_as_string_lenient(value)).has_value();
    }
    return serial_is_string(value) && utf8_single_code_point(serial_as_string(value)).has_value();
}

inline char32_t serial_as_char(const SerialValue& value, bool lenient) {
    const auto decoded = utf8_single_code_point(lenient ? serial_as_string_lenient(value) : serial_as_string(value));
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

template <typename F>
auto serial_decode_at(const std::string& path, F&& decode) -> decltype(decode()) {
    try {
        return decode();
    } catch (const JsonDecodeError& error) {
        throw JsonDecodeError(path + ": " + error.message());
    }
}

template <typename T>
T serial_decode_value(Result<T, std::string> result) {
    if (is_failure(result)) throw JsonDecodeError(failure_error(result));
    return std::move(success_value(result));
}

// Encodes one class arm of a flattened union through its own toSerialObject,
// and none as null. Generated code encodes other arms by their Doof type.
template <typename Item>
SerialValue serial_union_arm(const Item& item) {
    if constexpr (std::is_same_v<Item, std::monostate>) {
        return SerialValue(nullptr);
    } else if constexpr (std::is_same_v<Item, NoImplementations>) {
        return no_implementations<SerialValue>("union member");
    } else {
        return serial_value(item->toSerialObject());
    }
}

// Encodes a flattened union whose present arms are all classes.
template <typename... Arms>
SerialValue serial_union_value(const std::variant<Arms...>& value) {
    return std::visit([](const auto& item) -> SerialValue { return serial_union_arm(item); }, value);
}

// ============================================================================
// String utilities
// ============================================================================

// Unreachable payloads still participate in template instantiation.
[[noreturn]] inline std::string to_string(const Never&) {
    panic("Cannot format an uninhabited never value");
}

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

    void appendLine(const std::string& value) {
        value_.append(value);
        value_.push_back('\n');
    }

    int32_t length() const {
        return static_cast<int32_t>(value_.size());
    }

    void reserve(int32_t capacity) {
        if (capacity > 0) {
            value_.reserve(static_cast<size_t>(capacity));
        }
    }

    void clear() {
        value_.clear();
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

inline std::string string_padding(int32_t minimum_bytes, char32_t fill) {
    std::string result;
    const std::string encoded = char_to_utf8(fill);
    while (result.size() < static_cast<size_t>(minimum_bytes)) result += encoded;
    return result;
}

inline std::string string_padStart(const std::string& s, int32_t length, char32_t fill) {
    if (length <= static_cast<int32_t>(s.size())) return s;
    return string_padding(length - static_cast<int32_t>(s.size()), fill) + s;
}

inline std::string string_padEnd(const std::string& s, int32_t length, char32_t fill) {
    if (length <= static_cast<int32_t>(s.size())) return s;
    return s + string_padding(length - static_cast<int32_t>(s.size()), fill);
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
    size_t pos = s.find(search);
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
inline bool is_null(std::monostate) { return true; }

inline bool is_null(const SerialValue& value) {
    return serial_is_null(value);
}

template <typename T>
bool is_null(const std::shared_ptr<T>& value) {
    return value == nullptr;
}

template <typename T>
bool is_null(const std::optional<T>& value) {
    return !value.has_value();
}

template <typename T>
bool is_null(const std::weak_ptr<T>& value) {
    // An expired reference still has an owner and remains a weak-reference arm.
    const std::weak_ptr<T> empty;
    return !value.owner_before(empty) && !empty.owner_before(value);
}

template <typename... T>
bool is_null(const std::variant<std::weak_ptr<T>...>& value) {
    return std::visit([](const auto& weak) { return is_null(weak); }, value);
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

template <typename T>
struct is_std_variant : std::false_type {};

template <typename... T>
struct is_std_variant<std::variant<T...>> : std::true_type {};

// Marks an interface carrier whose alternatives a union splices in place.
template <typename Interface>
struct arms {};

// Marks an interface carrier whose alternatives a weak union splices as weak_ptrs.
template <typename Interface>
struct weak_arms {};

namespace union_detail {

template <typename Variant, typename T>
struct append;

template <typename... Present, typename T>
struct append<std::variant<Present...>, T> {
    using type = std::conditional_t<(std::is_same_v<Present, T> || ...), std::variant<Present...>, std::variant<Present..., T>>;
};

template <typename Variant, typename... Members>
struct build {
    using type = Variant;
};

template <typename Variant, typename Member, typename... Rest>
struct build<Variant, Member, Rest...> : build<typename append<Variant, Member>::type, Rest...> {};

template <typename Variant, typename... Alternatives, typename... Rest>
struct build<Variant, arms<std::variant<Alternatives...>>, Rest...> : build<Variant, Alternatives..., Rest...> {};

template <typename Strong>
struct weak_arm {
    // Only an implementationless interface's placeholder arm lands here.
    using type = std::weak_ptr<Strong>;
};

template <typename T>
struct weak_arm<std::shared_ptr<T>> {
    using type = std::weak_ptr<T>;
};

template <typename Variant, typename... Alternatives, typename... Rest>
struct build<Variant, weak_arms<std::variant<Alternatives...>>, Rest...> : build<Variant, typename weak_arm<Alternatives>::type..., Rest...> {};

} // namespace union_detail

// A union carrier with interface members flattened into their implementing
// alternatives, in member order and without duplicates. A weak reference
// splices `weak_arms<Interface>`, holding a weak_ptr for each implementor.
template <typename... Members>
using union_t = typename union_detail::build<std::variant<>, Members...>::type;

// A union arm may itself be a variant carrier (such as a Result), so checked
// narrowing descends into nested arms. Interface members are already flat.
template <typename Target, typename... Source>
bool variant_is(const std::variant<Source...>& value) {
    return std::visit([](const auto& item) -> bool {
        using Item = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<Item, Target> || is_variant_alternative<Item, Target>::value) {
            return true;
        } else if constexpr (is_std_variant<Item>::value) {
            return variant_is<Target>(item);
        } else {
            return false;
        }
    }, value);
}

template <typename Target, typename... Source>
Target variant_narrow(const std::variant<Source...>& value) {
    return std::visit([](const auto& item) -> Target {
        using Item = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<Item, Target> || is_variant_alternative<Item, Target>::value) {
            return item;
        } else if constexpr (is_std_variant<Item>::value) {
            return variant_narrow<Target>(item);
        } else {
            throw std::runtime_error("variant does not hold a requested alternative");
        }
    }, value);
}

template <typename Target, typename... Source>
Target variant_promote(const std::variant<Source...>& value) {
    // A Result or another variant can itself be one checked target arm.
    if constexpr (is_variant_alternative<std::variant<Source...>, Target>::value) {
        return Target{value};
    } else {
        return std::visit([](const auto& item) -> Target { return item; }, value);
    }
}

template <typename Target, typename Source>
Target variant_promote(const Source& value) {
    return Target{value};
}

// Stores a strong or weak value into an optional weak variant: each present
// arm becomes its own weak_ptr arm, and none stays absent.
template <typename Target, typename T>
Target weak_promote(const std::shared_ptr<T>& value) {
    return value == nullptr ? Target{} : Target{std::weak_ptr<T>(value)};
}

template <typename Target, typename T>
Target weak_promote(const std::weak_ptr<T>& value) {
    return Target{value};
}

template <typename Target, typename... Source>
Target weak_promote(const std::variant<Source...>& value) {
    return std::visit([](const auto& item) -> Target {
        using Item = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<Item, std::monostate>) {
            return Target{};
        } else if constexpr (std::is_same_v<Item, NoImplementations>) {
            return no_implementations<Target>("weak reference target");
        } else {
            return weak_promote<Target>(item);
        }
    }, value);
}

template <typename Target, typename Source>
Target weak_promote(const std::optional<Source>& value) {
    return value.has_value() ? weak_promote<Target>(value.value()) : Target{};
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

template <typename T>
std::weak_ptr<T> unwrap_optional(const std::weak_ptr<T>& value) {
    return value;
}

template <typename... T>
const std::variant<std::weak_ptr<T>...>& unwrap_optional(const std::variant<std::weak_ptr<T>...>& value) {
    return value;
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

namespace detail {
// Array callbacks declare `index` as their final parameter. Named function
// values may omit it, so the call shape follows the callback's arity.
template <typename F, typename Args, typename = void>
struct accepts_index : std::false_type {};

template <typename F, typename... Args>
struct accepts_index<F, std::tuple<Args...>, std::void_t<decltype(std::declval<const F&>().call(std::declval<Args>()..., std::declval<int32_t>()))>> : std::true_type {};

template <typename F, typename... Args>
decltype(auto) call_with_index(const F& fn, int32_t index, Args&&... args) {
    if constexpr (accepts_index<F, std::tuple<Args&&...>>::value) {
        return fn.call(std::forward<Args>(args)..., index);
    } else {
        return fn.call(std::forward<Args>(args)...);
    }
}

template <typename F, typename T>
using element_callback_result_t = std::decay_t<decltype(call_with_index(std::declval<const F&>(), 0, std::declval<const T&>()))>;
} // namespace detail

template <typename T, typename Predicate>
bool array_some(const std::shared_ptr<std::vector<T>>& arr, const Predicate& predicate, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in some()");
    }
    const auto size = static_cast<int32_t>(arr->size());
    for (int32_t i = 0; i < size; i++) {
        if (detail::call_with_index(predicate, i, (*arr)[static_cast<size_t>(i)])) {
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
    const auto size = static_cast<int32_t>(arr->size());
    for (int32_t i = 0; i < size; i++) {
        if (!detail::call_with_index(predicate, i, (*arr)[static_cast<size_t>(i)])) {
            return false;
        }
    }
    return true;
}

template <typename T, typename Predicate>
int32_t array_find_index(const std::shared_ptr<std::vector<T>>& arr, const Predicate& predicate, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in find()");
    }
    const auto size = static_cast<int32_t>(arr->size());
    for (int32_t i = 0; i < size; i++) {
        if (detail::call_with_index(predicate, i, (*arr)[static_cast<size_t>(i)])) {
            return i;
        }
    }
    return -1;
}

template <typename T, typename Predicate>
std::shared_ptr<std::vector<T>> array_filter(const std::shared_ptr<std::vector<T>>& arr, const Predicate& predicate, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in filter()");
    }
    auto result = std::make_shared<std::vector<T>>();
    result->reserve(arr->size());
    const auto size = static_cast<int32_t>(arr->size());
    for (int32_t i = 0; i < size; i++) {
        const auto& item = (*arr)[static_cast<size_t>(i)];
        if (detail::call_with_index(predicate, i, item)) {
            result->push_back(item);
        }
    }
    return result;
}

template <typename T, typename Mapper>
auto array_map(const std::shared_ptr<std::vector<T>>& arr, const Mapper& mapper, const char* file, int32_t line)
    -> std::shared_ptr<std::vector<detail::element_callback_result_t<Mapper, T>>> {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in map()");
    }
    auto result = std::make_shared<std::vector<detail::element_callback_result_t<Mapper, T>>>();
    result->reserve(arr->size());
    const auto size = static_cast<int32_t>(arr->size());
    for (int32_t i = 0; i < size; i++) {
        result->push_back(detail::call_with_index(mapper, i, (*arr)[static_cast<size_t>(i)]));
    }
    return result;
}

template <typename T, typename Action>
void array_forEach(const std::shared_ptr<std::vector<T>>& arr, const Action& action, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in forEach()");
    }
    // Iterate a snapshot of the length; the callback may append to the array.
    const auto size = static_cast<int32_t>(arr->size());
    for (int32_t i = 0; i < size && i < static_cast<int32_t>(arr->size()); i++) {
        detail::call_with_index(action, i, (*arr)[static_cast<size_t>(i)]);
    }
}

template <typename T, typename U, typename Reducer>
U array_reduce(const std::shared_ptr<std::vector<T>>& arr, U initial, const Reducer& reducer, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in reduce()");
    }
    U acc = std::move(initial);
    const auto size = static_cast<int32_t>(arr->size());
    for (int32_t i = 0; i < size; i++) {
        acc = detail::call_with_index(reducer, i, acc, (*arr)[static_cast<size_t>(i)]);
    }
    return acc;
}

template <typename T, typename U, typename Reducer>
U array_reduceRight(const std::shared_ptr<std::vector<T>>& arr, U initial, const Reducer& reducer, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to iterate null array in reduceRight()");
    }
    U acc = std::move(initial);
    for (int32_t i = static_cast<int32_t>(arr->size()) - 1; i >= 0; i--) {
        acc = detail::call_with_index(reducer, i, acc, (*arr)[static_cast<size_t>(i)]);
    }
    return acc;
}

// Stable in-place sort. `compare` orders a before b when it returns a
// negative value.
template <typename T, typename Comparer>
void array_sort(const std::shared_ptr<std::vector<T>>& arr, const Comparer& compare, const char* file, int32_t line) {
    if (!arr) {
        panic_at(file, line, "Attempted to sort null array");
    }
    std::stable_sort(arr->begin(), arr->end(), [&compare](const T& a, const T& b) { return compare.call(a, b) < 0; });
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

// The exclusive upper bound of an inclusive range ending at the maximum int
// would overflow. The checker rejects a constant end there; this catches the
// rest at run time, both for Range values and for inline for-of loops.
inline int32_t inclusive_range_end(int32_t end, const char* file, int32_t line) {
    if (end == std::numeric_limits<int32_t>::max()) {
        panic_at(file, line, "Inclusive range cannot end at the maximum int (" + std::to_string(end) + ")");
    }
    return end;
}

inline Range range(int32_t start, int32_t end, const char* file, int32_t line) {
    return Range{start, inclusive_range_end(end, file, line) + 1};
}

inline Range range_exclusive(int32_t start, int32_t end) {
    return Range{start, end};
}

// ============================================================================
// Promise<T> — async result wrapper
// ============================================================================

namespace detail {

// A reservation keeps both the destination and the application loop alive.
// Its destructor rolls back registration failures, or releases keep-alive only
// after the queued invocation (and its captured values) has finished.
class CompletionReservation {
    CallbackDomain* domain_;
    std::shared_ptr<CallbackDomain> lifetime_;
    bool posted_ = false;

public:
    CompletionReservation(CallbackDomain* domain, std::shared_ptr<CallbackDomain> lifetime)
        : domain_(domain), lifetime_(std::move(lifetime)) {
        domain_->reserve_completion();
        ApplicationDomain::shared().add_pending_completion();
    }
    ~CompletionReservation() {
        if (!posted_) domain_->cancel_completion();
        ApplicationDomain::shared().remove_pending_completion();
    }
    void post(std::function<void()> task) {
        domain_->enqueue_completion(std::move(task));
        posted_ = true;
    }
};

// All copies of a Promise share this claim and completion state. Producers
// publish directly: registration needs neither polling nor a waiting worker.
template <typename T>
class PromiseState {
    std::mutex mutex_;
    std::condition_variable ready_;
    bool settled_ = false;
    bool claimed_ = false;
    std::optional<doof::Success<T>> value_;
    std::exception_ptr error_;
    std::function<void()> continuation_;
    const void* producer_ = nullptr;
    std::shared_ptr<WaitSignal> signal_ = std::make_shared<WaitSignal>();

    void check_unclaimed() const {
        if (claimed_) doof::panic("promise result already claimed");
    }

    void wait() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (settled_) return;
        }
        WaitScope blocked(producer_, signal_, "promise wait");
        CpuTokenRelease release;
        std::unique_lock<std::mutex> lock(mutex_);
        ready_.wait(lock, [this] { return settled_; });
        // The lock is destroyed before the CPU token is reacquired.
    }

public:
    // The serial domain (actor, isolated job, or application) that settles
    // this promise, recorded for deadlock detection. Unset means untracked.
    explicit PromiseState(const void* producer = nullptr) : producer_(producer) {}

    void set_producer(const void* producer) { producer_ = producer; }

    bool ready() {
        std::lock_guard<std::mutex> lock(mutex_);
        check_unclaimed();
        return settled_;
    }

    void claim(std::function<void()> continuation = {}) {
        std::function<void()> dispatch;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            check_unclaimed();
            claimed_ = true;
            if (settled_) dispatch = std::move(continuation);
            else continuation_ = std::move(continuation);
        }
        if (dispatch) dispatch();
    }

    template <typename F>
    void complete(F&& produce) {
        std::optional<doof::Success<T>> value;
        std::exception_ptr error;
        try {
            if constexpr (std::is_void_v<T>) {
                produce();
                value.emplace();
            } else {
                value.emplace(doof::Success<T>{produce()});
            }
        } catch (...) {
            error = std::current_exception();
        }
        std::function<void()> dispatch;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (settled_) doof::panic("promise completed more than once");
            try {
                if (value) value_.emplace(std::move(*value));
            } catch (...) {
                error = std::current_exception();
            }
            error_ = std::move(error);
            settled_ = true;
            signal_->satisfy();
            dispatch = std::move(continuation_);
        }
        ready_.notify_all();
        PromiseCompletionNotifier::shared().notify();
        if (dispatch) dispatch();
    }

    doof::Result<T, std::string> take() {
        wait();
        // Only the claimant can take the payload. Clear retained storage so an
        // alias of the consumed promise cannot keep the mutable result alive.
        auto error = std::move(error_);
        try {
            if (error) std::rethrow_exception(error);
            auto value = std::move(*value_);
            value_.reset();
            return value;
        } catch (const doof::Panic&) {
            value_.reset();
            throw;
        } catch (const std::exception& e) {
            value_.reset();
            return doof::Failure<std::string>{e.what()};
        } catch (...) {
            value_.reset();
            return doof::Failure<std::string>{"unknown error"};
        }
    }
};

} // namespace detail

template <typename T>
class Promise {
    std::shared_ptr<detail::PromiseState<T>> state_;
public:
    explicit Promise(std::shared_ptr<detail::PromiseState<T>> state) : state_(std::move(state)) {}

    bool ready() const { return state_->ready(); }

    doof::Result<T, std::string> get() const {
        state_->claim();
        return state_->take();
    }

    void onComplete(const doof::callback<void(doof::Result<T, std::string>)>& cb) const {
        if (!cb) doof::panic("completion callback invoked before initialization");
        if (cb.isolated_) doof::panic("completion callbacks created in isolated async work cannot receive deferred delivery");
        auto domain = cb.owner_ ? cb.owner_ : &detail::ApplicationDomain::shared();
        std::shared_ptr<detail::CallbackDomain> lifetime;
        if (!detail::ApplicationDomain::is_application_domain(domain)) {
            lifetime = cb.owner_lifetime_.lock();
            if (!lifetime) doof::panic("completion callback requires a live actor domain");
        }
        auto reservation = std::make_shared<detail::CompletionReservation>(domain, std::move(lifetime));
        auto state = state_;
        state->claim([state, cb, reservation] {
            reservation->post([state, cb, reservation] {
                try {
                    detail::call_callback_unchecked(cb, state->take());
                } catch (const doof::Panic& panic) {
                    // Terminal delivery has no successor promise to receive a
                    // panic. Report it at the process boundary in this domain.
                    doof::unhandled_panic(panic);
                } catch (const std::exception& error) {
                    doof::unhandled_panic(doof::Panic(error.what()));
                } catch (...) {
                    doof::unhandled_panic(doof::Panic("unknown completion callback error"));
                }
            });
        });
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
    auto& scheduler = doof::detail::RuntimeScheduler::shared();
    scheduler.acquire_async_slot();
    auto state = std::make_shared<doof::detail::PromiseState<R>>();
    // The job's promise state doubles as its temporary domain's identity.
    const void* node = state.get();
    state->set_producer(node);
    auto task = std::make_shared<std::decay_t<F>>(std::forward<F>(f));
    scheduler.submit([state, task, node]() mutable {
        doof::detail::RuntimeScheduler::shared().release_async_slot();
        doof::detail::IsolatedTaskScope isolated;
        doof::detail::ActiveTaskScope active(node);
        state->complete([&]() -> R { return (*task)(); });
    });
    return doof::Promise<R>(std::move(state));
}

template <typename R, typename... Args>
doof::Promise<R> callback<R(Args...)>::post(Args... args) const {
    if (!static_cast<bool>(*this)) {
        doof::panic("callback posted before initialization");
    }
    auto owner = owner_ ? owner_ : &doof::detail::ApplicationDomain::shared();

    auto state = std::make_shared<doof::detail::PromiseState<R>>(static_cast<const void*>(owner));
    auto self = *this;
    auto packedArgs = std::make_tuple(std::forward<Args>(args)...);
    owner->enqueue_callback([self, state, packedArgs = std::move(packedArgs)]() mutable {
        state->complete([&]() -> R {
            return std::apply([&](auto&&... unpacked) -> R {
                return doof::detail::call_callback_unchecked(self, std::forward<decltype(unpacked)>(unpacked)...);
            }, std::move(packedArgs));
        });
    });
    return doof::Promise<R>(std::move(state));
}

// Like post, but never blocks: a full owner mailbox reports "full", and an
// owner that is retiring, retired, or gone reports "retired". A rejected
// post leaves no queued work and its unused promise state is dropped.
template <typename R, typename... Args>
doof::Result<doof::Promise<R>, std::string> callback<R(Args...)>::tryPost(Args... args) const {
    if (!static_cast<bool>(*this)) {
        doof::panic("callback posted before initialization");
    }
    std::shared_ptr<doof::detail::CallbackDomain> retained;
    doof::detail::CallbackDomain* owner = &doof::detail::ApplicationDomain::shared();
    if (owner_ && !doof::detail::ApplicationDomain::is_application_domain(owner_)) {
        // Keep the actor alive while the message is offered to it.
        retained = owner_lifetime_.lock();
        if (!retained) {
            return doof::Failure<std::string>{"retired"};
        }
        owner = retained.get();
    }

    auto state = std::make_shared<doof::detail::PromiseState<R>>(static_cast<const void*>(owner));
    auto self = *this;
    auto packedArgs = std::make_tuple(std::forward<Args>(args)...);
    auto accepted = owner->try_enqueue_callback([self, state, packedArgs = std::move(packedArgs)]() mutable {
        state->complete([&]() -> R {
            return std::apply([&](auto&&... unpacked) -> R {
                return doof::detail::call_callback_unchecked(self, std::forward<decltype(unpacked)>(unpacked)...);
            }, std::move(packedArgs));
        });
    });
    switch (accepted) {
    case doof::detail::TryEnqueueResult::Accepted:
        return doof::Success<doof::Promise<R>>{doof::Promise<R>(std::move(state))};
    case doof::detail::TryEnqueueResult::Full:
        return doof::Failure<std::string>{"full"};
    case doof::detail::TryEnqueueResult::Retired:
        break;
    }
    return doof::Failure<std::string>{"retired"};
}

// ============================================================================
// Actor<T> — serial message queue actor
// ============================================================================

template <typename T>
class Actor : public detail::CallbackDomain {
    // Calls and posts count against the mailbox capacity. Completion
    // deliveries were reserved at registration and retirement is a lifecycle
    // request, so neither can block a producer.
    struct Message {
        std::function<void()> run;
        bool bounded;
    };

    // Actor state remains reachable only through this actor until retirement,
    // but class methods require shared ownership for Doof's `this` lowering.
    std::shared_ptr<T> instance_;
    std::queue<Message> mailbox_;
    std::mutex mutex_;
    std::condition_variable space_;
    bool accepting_ = true;
    bool scheduled_ = false;
    std::size_t pending_completions_ = 0;
    std::size_t bounded_messages_ = 0;
    std::vector<std::shared_ptr<detail::WaitSignal>> capacity_waiters_;
    std::function<void()> retirement_;

    // Matches the domain pointer that ActiveActorScope publishes for this actor.
    const void* wait_node() const {
        return static_cast<const detail::CallbackDomain*>(this);
    }

    void finish_retirement_locked() {
        if (pending_completions_ == 0 && retirement_) {
            mailbox_.push(Message{std::move(retirement_), false});
            retirement_ = {};
            schedule_locked();
        }
    }

    void release_capacity_waiters_locked() {
        if (capacity_waiters_.empty()) return;
        for (auto& waiter : capacity_waiters_) waiter->satisfy();
        capacity_waiters_.clear();
        space_.notify_all();
    }

    // Blocked senders observe retirement instead of waiting for space.
    void stop_accepting_locked() {
        accepting_ = false;
        release_capacity_waiters_locked();
    }

    // Accept one call or post. A full mailbox blocks the sender with its CPU
    // token released; that capacity wait is a wait on this actor's progress.
    void push_bounded(std::function<void()> run) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (accepting_ && bounded_messages_ >= detail::RuntimeScheduler::shared().actor_mailbox_capacity()) {
            auto signal = std::make_shared<detail::WaitSignal>();
            capacity_waiters_.push_back(signal);
            lock.unlock();
            {
                detail::WaitScope blocked(wait_node(), signal, "actor mailbox capacity");
                CpuTokenRelease release;
                std::unique_lock<std::mutex> waiting(mutex_);
                space_.wait(waiting, [&] { return signal->is_satisfied(); });
            }
            lock.lock();
        }
        if (!accepting_) doof::panic("actor is retiring or retired");
        mailbox_.push(Message{std::move(run), true});
        ++bounded_messages_;
        schedule_locked();
    }

    template <typename Future>
    void wait_on_actor(Future& future, const std::shared_ptr<detail::WaitSignal>& signal, const char* kind) {
        if (future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) return;
        detail::WaitScope blocked(wait_node(), signal, kind);
        doof::wait_with_cpu_token_released(future);
    }

    void schedule_locked() {
        if (scheduled_ || mailbox_.empty()) {
            return;
        }
        scheduled_ = true;
        auto self = std::static_pointer_cast<Actor<T>>(this->shared_from_this());
        doof::detail::RuntimeScheduler::shared().submit([self] {
            self->run_one();
        });
    }

    void run_one() {
        std::function<void()> task;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto message = std::move(mailbox_.front());
            mailbox_.pop();
            task = std::move(message.run);
            if (message.bounded) {
                --bounded_messages_;
                release_capacity_waiters_locked();
            }
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
    explicit Actor(std::shared_ptr<T> instance)
        : instance_(std::move(instance)) {}

    template <typename... Args>
    explicit Actor(Args&&... args)
        : instance_(std::make_shared<T>(std::forward<Args>(args)...)) {}

    // Synchronous call — enqueue and block until complete. The completion
    // signal is raised before the result is published so the waiter's edge
    // disappears before this actor can start another wait.
    template <typename R, typename F>
    R call_sync(F&& f) {
        auto signal = std::make_shared<detail::WaitSignal>();
        if constexpr (std::is_void_v<R>) {
            auto prom = std::make_shared<std::promise<void>>();
            auto fut = prom->get_future();
            push_bounded([this, f = std::forward<F>(f), prom, signal]() {
                try {
                    f(*instance_);
                    signal->satisfy();
                    prom->set_value();
                } catch (...) {
                    signal->satisfy();
                    prom->set_exception(std::current_exception());
                }
            });
            wait_on_actor(fut, signal, "synchronous actor call");
            return fut.get();
        } else {
            auto prom = std::make_shared<std::promise<R>>();
            auto fut = prom->get_future();
            push_bounded([this, f = std::forward<F>(f), prom, signal]() {
                try {
                    auto value = f(*instance_);
                    signal->satisfy();
                    prom->set_value(std::move(value));
                } catch (...) {
                    signal->satisfy();
                    prom->set_exception(std::current_exception());
                }
            });
            wait_on_actor(fut, signal, "synchronous actor call");
            return fut.get();
        }
    }

    // Asynchronous call — enqueue and return a Promise
    template <typename R, typename F>
    doof::Promise<R> call_async(F&& f) {
        auto state = std::make_shared<doof::detail::PromiseState<R>>(wait_node());
        push_bounded([this, f = std::forward<F>(f), state]() mutable {
            state->complete([&]() -> R { return f(*instance_); });
        });
        return doof::Promise<R>(std::move(state));
    }

    bool enqueue_release(std::function<void()> task) override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!accepting_) return false;
        mailbox_.push(Message{std::move(task), false});
        schedule_locked();
        return true;
    }

    void reserve_completion() override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!accepting_) doof::panic("actor is retiring or retired");
        ++pending_completions_;
    }

    void cancel_completion() override {
        std::lock_guard<std::mutex> lock(mutex_);
        --pending_completions_;
        finish_retirement_locked();
    }

    void enqueue_completion(std::function<void()> task) override {
        std::lock_guard<std::mutex> lock(mutex_);
        mailbox_.push(Message{std::move(task), false});
        --pending_completions_;
        finish_retirement_locked();
        schedule_locked();
    }

    void enqueue_callback(std::function<void()> task) override {
        push_bounded(std::move(task));
    }

    detail::TryEnqueueResult try_enqueue_callback(std::function<void()> task) override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!accepting_) return detail::TryEnqueueResult::Retired;
        if (bounded_messages_ >= detail::RuntimeScheduler::shared().actor_mailbox_capacity()) {
            return detail::TryEnqueueResult::Full;
        }
        mailbox_.push(Message{std::move(task), true});
        ++bounded_messages_;
        schedule_locked();
        return detail::TryEnqueueResult::Accepted;
    }

    // Retire the actor — drain accepted work, stop, and return owned state.
    std::shared_ptr<T> retire() {
        auto prom = std::make_shared<std::promise<std::shared_ptr<T>>>();
        auto fut = prom->get_future();
        auto signal = std::make_shared<detail::WaitSignal>();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!accepting_) doof::panic("actor is already retiring or retired");
            stop_accepting_locked();
            retirement_ = [this, prom, signal]() {
                try {
                    if (!instance_) doof::panic("actor is already retired");
                    auto state = std::move(instance_);
                    signal->satisfy();
                    prom->set_value(std::move(state));
                } catch (...) {
                    signal->satisfy();
                    prom->set_exception(std::current_exception());
                }
            };
            finish_retirement_locked();
        }
        wait_on_actor(fut, signal, "actor retirement");
        std::shared_ptr<T> value = fut.get();
        return value;
    }

    // Stop accepting work and drain the already accepted mailbox.
    void stop() {
        auto prom = std::make_shared<std::promise<void>>();
        auto fut = prom->get_future();
        auto signal = std::make_shared<detail::WaitSignal>();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!accepting_) {
                return;
            }
            stop_accepting_locked();
            retirement_ = [prom, signal] {
                signal->satisfy();
                prom->set_value();
            };
            finish_retirement_locked();
        }
        wait_on_actor(fut, signal, "actor stop");
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
    using result_type = doof::Result<doof::SerialValue, doof::SerialValue>;

    std::function<result_type(T&, const doof::SerialValue&)> call;

    MethodInvoker() = default;

    template <typename F>
    MethodInvoker(F&& f) : call(std::forward<F>(f)) {}

    result_type operator()(T& instance, const doof::SerialValue& params) const {
        return call(instance, params);
    }

    result_type operator()(const std::shared_ptr<T>& instance, const doof::SerialValue& params) const {
        if (instance == nullptr) {
            return doof::Failure<doof::SerialValue>{doof::serial_error(400, std::string("Cannot invoke method on null instance"))};
        }
        return call(*instance, params);
    }
};

/** Per-method reflection entry with an invoke callable. */
template <typename T>
struct MethodReflection {
    std::string name;
    std::string description;
    doof::SerialValue inputSchema;
    doof::SerialValue outputSchema;
    doof::MethodInvoker<T> invoke;
};

/** Structured metadata for a class — contains name, description, methods, and schema $defs. */
template <typename T>
struct ClassMetadata {
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<doof::MethodReflection<T>>> methods;
    std::optional<doof::SerialValue> defs;

    doof::Result<doof::SerialValue, doof::SerialValue> invoke(
        T& instance,
        const std::string& methodName,
        const doof::SerialValue& params
    ) const {
        if (methods != nullptr) {
            for (const auto& method : *methods) {
                if (method.name == methodName) {
                    return method.invoke(instance, params);
                }
            }
        }
        return doof::Failure<doof::SerialValue>{doof::serial_error(400, std::string("Unknown method: ") + methodName)};
    }

    doof::Result<doof::SerialValue, doof::SerialValue> invoke(
        const std::shared_ptr<T>& instance,
        const std::string& methodName,
        const doof::SerialValue& params
    ) const {
        if (instance == nullptr) {
            return doof::Failure<doof::SerialValue>{doof::serial_error(400, std::string("Cannot invoke method on null instance"))};
        }
        return invoke(*instance, methodName, params);
    }
};

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
