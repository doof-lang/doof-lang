#include "doof_runtime.hpp"

#include <atomic>
#include <iostream>

static_assert(std::is_same_v<decltype(doof::panic(std::declval<const std::string&>())), doof::Never>);
static_assert(!std::is_default_constructible_v<doof::Never>);
static_assert(!std::is_aggregate_v<doof::Never>);
static_assert(std::is_copy_constructible_v<doof::Result<doof::Never, std::string>>);
static_assert(std::is_move_constructible_v<doof::Result<doof::Never, std::string>>);

// Interface members splice their alternatives into one flat, deduplicated variant.
using UnionShape = std::variant<std::shared_ptr<int>, std::shared_ptr<double>>;
static_assert(std::is_same_v<doof::union_t<std::monostate, doof::arms<UnionShape>>, std::variant<std::monostate, std::shared_ptr<int>, std::shared_ptr<double>>>);
static_assert(std::is_same_v<doof::union_t<doof::arms<UnionShape>, std::shared_ptr<double>, std::string>, std::variant<std::shared_ptr<int>, std::shared_ptr<double>, std::string>>);
static_assert(std::is_same_v<decltype(doof::unwrap_optional(std::declval<doof::union_t<std::monostate, doof::arms<UnionShape>>>())), UnionShape>);
static_assert(std::is_same_v<doof::union_t<doof::weak_arms<UnionShape>, std::weak_ptr<std::string>>, std::variant<std::weak_ptr<int>, std::weak_ptr<double>, std::weak_ptr<std::string>>>);
static_assert(std::is_same_v<decltype(doof::lock_weak(std::declval<doof::union_t<doof::weak_arms<UnionShape>>>()))::value_type, UnionShape>);

namespace {

[[noreturn]] void fail(const std::string& message) {
    std::cerr << "runtime scheduler test failed: " << message << "\n";
    std::exit(1);
}

void require(bool condition, const std::string& message) {
    if (!condition) {
        fail(message);
    }
}

template <typename Predicate>
void wait_until(Predicate predicate, const std::string& message) {
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (!predicate()) {
        if (std::chrono::steady_clock::now() >= deadline) {
            fail(message);
        }
        std::this_thread::yield();
    }
}

template <typename T>
T success(doof::Promise<T> promise) {
    auto result = promise.get();
    require(doof::is_success(result), "promise unexpectedly failed");
    return doof::success_value(result);
}

doof::RuntimeSchedulerOptions options(
    std::size_t maximum,
    std::size_t retained,
    std::chrono::milliseconds timeout = std::chrono::milliseconds(50)) {
    doof::RuntimeSchedulerOptions value;
    value.maximum_cpu_parallelism = maximum;
    value.retained_worker_count = retained;
    value.excess_worker_idle_timeout = timeout;
    return value;
}

void test_cpu_limit() {
    doof::configure_runtime_scheduler(options(2, 2));
    std::atomic<int> active{0};
    std::atomic<int> maximum{0};
    std::atomic<int> started{0};
    std::promise<void> release;
    auto gate = release.get_future().share();
    std::vector<doof::Promise<int>> promises;

    for (int i = 0; i < 12; ++i) {
        promises.push_back(doof::submit_async<int>([&, i] {
            const int now = active.fetch_add(1) + 1;
            int observed = maximum.load();
            while (observed < now && !maximum.compare_exchange_weak(observed, now)) {}
            started.fetch_add(1);
            gate.wait();
            active.fetch_sub(1);
            return i;
        }));
    }

    wait_until([&] { return started.load() == 2; }, "two CPU-limited jobs did not start");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    require(started.load() == 2, "more jobs started than the CPU limit permits");
    const auto snapshot = doof::detail::RuntimeScheduler::shared().snapshot();
    require(snapshot.active_cpu_tokens == 2, "active token count did not reach the configured limit");
    require(snapshot.pending_jobs == 10, "excess async work was not left pending");

    release.set_value();
    for (int i = 0; i < 12; ++i) {
        require(success(std::move(promises[i])) == i, "async result changed while queued");
    }
    require(maximum.load() == 2, "observed CPU execution exceeded or missed the configured limit");
}

void test_nested_waits() {
    doof::configure_runtime_scheduler(options(1, 1));
    auto move_only = doof::submit_async<int>(
        [value = std::make_unique<int>(40)] { return *value; });
    require(success(std::move(move_only)) == 40, "move-only async task was not accepted");

    auto outer = doof::submit_async<int>([] {
        auto inner = doof::submit_async<int>([] { return 41; });
        auto result = inner.get();
        if (!doof::is_success(result)) {
            return -1;
        }
        return doof::success_value(result) + 1;
    });
    require(success(std::move(outer)) == 42, "nested async wait deadlocked or returned the wrong value");

    // A worker waiting for the first completion lends its token to nested work.
    auto first = doof::submit_async<int>([] {
        auto inner = std::make_shared<std::vector<doof::Promise<int>>>();
        inner->push_back(doof::submit_async<int>([] { return 6; }));
        auto result = doof::promise_take_first_completed(inner);
        return doof::is_success(result) ? doof::success_value(result) : -1;
    });
    require(success(std::move(first)) == 6, "nested first-completed wait deadlocked or returned the wrong value");
}

void test_first_completed_promise() {
    doof::configure_runtime_scheduler(options(2, 2));
    std::promise<void> release_first;
    auto first_gate = release_first.get_future().share();
    auto promises = std::make_shared<std::vector<doof::Promise<int>>>();
    promises->push_back(doof::submit_async<int>([first_gate] {
        first_gate.wait();
        return 1;
    }));
    promises->push_back(doof::submit_async<int>([] { return 2; }));

    auto second = doof::promise_take_first_completed(promises);
    require(doof::is_success(second), "first completed promise unexpectedly failed");
    require(doof::success_value(second) == 2, "promise completion order was ignored");
    require(promises->size() == 1, "completed promise was not removed from the array");

    release_first.set_value();
    auto first = doof::promise_take_first_completed(promises);
    require(doof::is_success(first), "remaining promise unexpectedly failed");
    require(doof::success_value(first) == 1, "remaining promise value changed");
    require(promises->empty(), "remaining completed promise was not removed");

    auto empty = doof::promise_take_first_completed(promises);
    require(doof::is_failure(empty), "empty promise array did not return a failure");

    // Completions of promises outside the array never wake the waiter.
    std::promise<void> release_watched;
    auto watched_gate = release_watched.get_future().share();
    promises->push_back(doof::submit_async<int>([watched_gate] {
        watched_gate.wait();
        return 3;
    }));
    const auto before_unrelated = doof::detail::first_completed_wakeups.load();
    std::thread unrelated([&release_watched] {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        for (int i = 0; i < 200; ++i) {
            require(success(doof::submit_async<int>([i] { return i; })) == i, "unrelated promise result changed");
        }
        release_watched.set_value();
    });
    auto watched = doof::promise_take_first_completed(promises);
    unrelated.join();
    require(doof::is_success(watched) && doof::success_value(watched) == 3, "watched promise result changed");
    const auto unrelated_wakeups = doof::detail::first_completed_wakeups.load() - before_unrelated;
    require(unrelated_wakeups <= 2,
            "unrelated completions woke the waiter " + std::to_string(unrelated_wakeups) + " times");

    // Draining reports every result once, and each extraction wakes at most
    // about once instead of once per completion anywhere in the process.
    constexpr int drained = 64;
    std::promise<void> release_drain;
    auto drain_gate = release_drain.get_future().share();
    for (int i = 0; i < drained; ++i) {
        promises->push_back(doof::submit_async<int>([drain_gate, i] {
            drain_gate.wait();
            return i;
        }));
    }
    const auto before_drain = doof::detail::first_completed_wakeups.load();
    release_drain.set_value();
    std::vector<bool> seen(drained, false);
    for (int i = 0; i < drained; ++i) {
        auto result = doof::promise_take_first_completed(promises);
        require(doof::is_success(result), "drained promise unexpectedly failed");
        const int value = doof::success_value(result);
        require(value >= 0 && value < drained && !seen[value], "drained promise result repeated or changed");
        seen[value] = true;
    }
    require(promises->empty(), "drained promises were not all removed");
    const auto drain_wakeups = doof::detail::first_completed_wakeups.load() - before_drain;
    require(drain_wakeups <= drained + drained / 4,
            "draining woke waiters " + std::to_string(drain_wakeups) + " times for " + std::to_string(drained) + " promises");

    // A claimed promise panics and leaves no registration on earlier promises.
    std::promise<void> release_claimed;
    auto claimed_gate = release_claimed.get_future().share();
    auto pending = doof::submit_async<int>([claimed_gate] {
        claimed_gate.wait();
        return 4;
    });
    auto claimed = doof::submit_async<int>([] { return 5; });
    require(success(claimed) == 5, "claimed promise result changed");
    promises->push_back(pending);
    promises->push_back(claimed);
    try {
        (void)doof::promise_take_first_completed(promises);
        fail("a claimed promise in the array did not panic");
    } catch (const doof::Panic& panic) {
        require(panic.message() == "promise result already claimed", "claimed promise panic changed");
    }
    require(promises->size() == 2, "a panicking extraction removed a promise");
    release_claimed.set_value();
    require(success(pending) == 4, "promise registered before the panic was not released");
    promises->clear();
}

struct ActorState {
    int value = 0;
    std::vector<int> order;
};

void test_actor_serialization() {
    doof::configure_runtime_scheduler(options(2, 2));
    auto actor = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    std::atomic<int> active{0};
    std::atomic<int> maximum{0};
    std::vector<doof::Promise<int>> calls;

    for (int i = 0; i < 64; ++i) {
        calls.push_back(actor->call_async<int>([&, i](ActorState& state) {
            const int now = active.fetch_add(1) + 1;
            int observed = maximum.load();
            while (observed < now && !maximum.compare_exchange_weak(observed, now)) {}
            state.order.push_back(i);
            state.value += 1;
            active.fetch_sub(1);
            return state.value;
        }));
    }

    for (int i = 0; i < 64; ++i) {
        require(success(std::move(calls[i])) == i + 1, "actor result order changed");
    }
    auto state = actor->retire();
    require(maximum.load() == 1, "messages for one actor overlapped");
    require(state->order.size() == 64, "actor lost accepted messages");
    for (int i = 0; i < 64; ++i) {
        require(state->order[static_cast<std::size_t>(i)] == i, "actor FIFO order changed");
    }
}

void test_actor_batching() {
    doof::configure_runtime_scheduler(options(1, 1));
    auto busy = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto other = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    std::atomic<int> sequence{0};
    std::promise<void> open;
    auto gate = open.get_future().share();
    std::atomic<bool> started{false};

    // With the only CPU token held by `busy`, queue far more than one batch
    // behind it, then one message for `other`.
    constexpr int flooded = 200;
    std::vector<doof::Promise<int>> calls;
    calls.push_back(busy->call_async<int>([gate, &started, &sequence](ActorState& state) {
        started.store(true);
        gate.wait();
        state.order.push_back(0);
        return sequence.fetch_add(1);
    }));
    wait_until([&] { return started.load(); }, "first batched message did not start");
    for (int i = 1; i < flooded; ++i) {
        calls.push_back(busy->call_async<int>([i, &sequence](ActorState& state) {
            state.order.push_back(i);
            return sequence.fetch_add(1);
        }));
    }
    auto interleaved = other->call_async<int>([&sequence](ActorState&) { return sequence.fetch_add(1); });
    open.set_value();

    const int otherPosition = success(std::move(interleaved));
    for (auto& call : calls) (void)success(std::move(call));
    auto state = busy->retire();
    other->retire();
    require(state->order.size() == static_cast<std::size_t>(flooded), "batched actor lost messages");
    for (int i = 0; i < flooded; ++i) {
        require(state->order[static_cast<std::size_t>(i)] == i, "batched actor FIFO order changed");
    }
    require(otherPosition < flooded - 1, "a flooded actor kept its CPU token past one batch");

    // Far fewer messages than one batch, but each outlasts the time budget,
    // so the actor still gives its token back after the first of them.
    auto slow = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto waiting = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    std::atomic<int> slowSequence{0};
    std::promise<void> release;
    auto released = release.get_future().share();
    std::atomic<bool> holding{false};
    std::vector<doof::Promise<int>> slowCalls;
    slowCalls.push_back(slow->call_async<int>([released, &holding, &slowSequence](ActorState&) {
        holding.store(true);
        released.wait();
        return slowSequence.fetch_add(1);
    }));
    wait_until([&] { return holding.load(); }, "first slow message did not start");
    constexpr int slowCount = 10;
    for (int i = 1; i < slowCount; ++i) {
        slowCalls.push_back(slow->call_async<int>([&slowSequence](ActorState&) {
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            return slowSequence.fetch_add(1);
        }));
    }
    auto behindSlow = waiting->call_async<int>([&slowSequence](ActorState&) { return slowSequence.fetch_add(1); });
    release.set_value();
    const int waitingPosition = success(std::move(behindSlow));
    for (auto& call : slowCalls) (void)success(std::move(call));
    slow->retire();
    waiting->retire();
    require(waitingPosition <= 2, "slow messages held the CPU token past the batch time budget");
}

void test_actor_waits() {
    doof::configure_runtime_scheduler(options(1, 1));
    auto outer = doof::submit_async<int>([] {
        auto actor = std::make_shared<doof::Actor<ActorState>>(ActorState{});
        const int value = actor->call_sync<int>([](ActorState& state) {
            state.value = 7;
            return state.value;
        });
        auto state = actor->retire();
        return value + state->value;
    });
    require(success(std::move(outer)) == 14, "synchronous actor wait or retirement deadlocked");
}

void test_failures() {
    doof::configure_runtime_scheduler(options(1, 1));
    auto failed = doof::submit_async<int>([]() -> int {
        throw std::runtime_error("async failure");
    });
    auto failure = failed.get();
    require(doof::is_failure(failure), "async exception did not become a Promise failure");
    require(doof::failure_error(failure) == "async failure", "async failure message changed");

    auto panicked = doof::submit_async<int>([]() -> int {
        doof::panic("panic failure");
    });
    try {
        (void)panicked.get();
        fail("Doof panic was converted into an ordinary Promise failure");
    } catch (const doof::Panic& panic) {
        require(panic.message() == "panic failure", "Doof panic message changed");
    }

    auto actor = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto actor_failure = actor->call_async<int>([](ActorState&) -> int {
        throw std::runtime_error("actor failure");
    });
    auto actor_result = actor_failure.get();
    require(doof::is_failure(actor_result), "actor exception did not become a Promise failure");
    require(doof::failure_error(actor_result) == "actor failure", "actor failure message changed");
    actor->retire();
}

void test_application_domain() {
    doof::configure_runtime_scheduler(options(1, 1));
    auto& application = doof::detail::ApplicationDomain::shared();
    doof::detail::ActiveActorScope scope(&application);
    std::atomic<bool> called{false};
    doof::callback<int()> callback([&] {
        called.store(true);
        require(doof::current_actor_domain() == &application, "root callback ran outside the application domain");
        return 9;
    });

    auto posted = doof::submit_async<doof::Promise<int>>([callback] {
        return callback.post();
    });
    auto callback_promise = success(std::move(posted));
    require(!called.load(), "root callback ran on a scheduler worker");
    require(application.drain_ready() == 1, "application mailbox did not contain the root callback");
    require(called.load(), "draining the application mailbox did not invoke the callback");
    require(success(std::move(callback_promise)) == 9, "root callback result changed");
}

// Records the domain that releases a callback's captured state.
struct ReleaseProbe {
    std::atomic<bool>* released;
    std::atomic<const void*>* domain;

    ReleaseProbe(std::atomic<bool>* released, std::atomic<const void*>* domain)
        : released(released), domain(domain) {}
    ReleaseProbe(const ReleaseProbe&) = delete;

    ~ReleaseProbe() {
        domain->store(doof::current_actor_domain());
        released->store(true);
    }
};

void test_callback_release_domain() {
    doof::configure_runtime_scheduler(options(2, 2));
    auto& application = doof::detail::ApplicationDomain::shared();
    doof::detail::ActiveActorScope scope(&application);
    std::atomic<bool> released{false};
    std::atomic<const void*> domain{nullptr};

    // A root callback whose last copy drops inside an actor is released on the root.
    {
        auto probe = std::make_shared<ReleaseProbe>(&released, &domain);
        doof::callback<int()> root([probe] { return 1; });
        probe.reset();
        auto actor = std::make_shared<doof::Actor<ActorState>>(ActorState{});
        auto dropped = actor->call_async<int>([root = std::move(root)](ActorState&) mutable {
            root = {};
            return 0;
        });
        require(success(std::move(dropped)) == 0, "actor did not drop the root callback");
        actor->retire();
        require(!released.load(), "root callback captures were released inside the actor");
        require(application.drain_ready() == 0, "a callback release counted as a dispatched callback");
        require(released.load(), "pumping the application mailbox did not release the root callback");
        require(domain.load() == &application, "root callback captures were released outside the application domain");
    }

    // An actor callback whose last copy drops on the root is released on the actor.
    {
        released.store(false);
        domain.store(nullptr);
        auto actor = std::make_shared<doof::Actor<ActorState>>(ActorState{});
        auto made = actor->call_sync<doof::callback<int()>>([&](ActorState&) {
            auto probe = std::make_shared<ReleaseProbe>(&released, &domain);
            return doof::callback<int()>([probe] { return 2; });
        });
        made = {};
        wait_until([&] { return released.load(); }, "actor callback was not released");
        require(domain.load() == static_cast<const void*>(static_cast<doof::detail::CallbackDomain*>(actor.get())),
            "actor callback captures were released outside the actor");
        actor->retire();
    }

    // A retired owner can no longer run work, so its callbacks release in place.
    {
        released.store(false);
        domain.store(nullptr);
        auto actor = std::make_shared<doof::Actor<ActorState>>(ActorState{});
        auto made = actor->call_sync<doof::callback<int()>>([&](ActorState&) {
            auto probe = std::make_shared<ReleaseProbe>(&released, &domain);
            return doof::callback<int()>([probe] { return 3; });
        });
        actor->retire();
        made = {};
        require(released.load(), "retired actor callback was not released in place");
        require(domain.load() == &application, "retired actor callback was not released by the dropping domain");
    }
}

void test_token_release_and_retirement() {
    doof::configure_runtime_scheduler(options(1, 0, std::chrono::milliseconds(20)));
    std::promise<void> allow_reacquire;
    auto reacquire_gate = allow_reacquire.get_future().share();
    std::promise<void> second_started;
    auto second_started_future = second_started.get_future();
    std::atomic<bool> outer_resumed{false};

    auto first = doof::submit_async<int>([&] {
        doof::CpuTokenRelease outer;
        {
            doof::CpuTokenRelease nested;
            auto second = doof::submit_async<int>([&] {
                second_started.set_value();
                return 2;
            });
            require(success(std::move(second)) == 2, "nested release prevented compensating work");
        }
        reacquire_gate.wait();
        outer.reacquire();
        outer_resumed.store(true);
        return 1;
    });

    second_started_future.wait();
    allow_reacquire.set_value();
    require(success(std::move(first)) == 1, "released token was not reacquired");
    require(outer_resumed.load(), "explicit token reacquisition did not resume the task");

    wait_until([] {
        return doof::detail::RuntimeScheduler::shared().snapshot().live_worker_threads == 0;
    }, "excess workers did not retire after the configured idle timeout");
}

void test_reacquire_priority() {
    doof::configure_runtime_scheduler(options(1, 0, std::chrono::milliseconds(20)));
    std::promise<void> let_first_reacquire;
    auto first_gate = let_first_reacquire.get_future().share();
    std::promise<void> second_started;
    auto second_started_future = second_started.get_future();
    std::promise<void> finish_second;
    auto second_gate = finish_second.get_future().share();
    std::atomic<bool> first_resumed{false};
    std::atomic<bool> third_saw_resume{false};

    auto first = doof::submit_async<int>([&] {
        doof::CpuTokenRelease release;
        first_gate.wait();
        release.reacquire();
        first_resumed.store(true);
        return 1;
    });
    auto second = doof::submit_async<int>([&] {
        second_started.set_value();
        second_gate.wait();
        return 2;
    });

    second_started_future.wait();
    let_first_reacquire.set_value();
    wait_until([] {
        return doof::detail::RuntimeScheduler::shared().snapshot().reacquire_waiters == 1;
    }, "released task did not wait to reacquire its token");

    auto third = doof::submit_async<int>([&] {
        third_saw_resume.store(first_resumed.load());
        return 3;
    });
    finish_second.set_value();

    require(success(std::move(first)) == 1, "priority waiter did not complete");
    require(success(std::move(second)) == 2, "token-holding task did not complete");
    require(success(std::move(third)) == 3, "queued task did not complete");
    require(third_saw_resume.load(), "fresh work claimed a token before a reacquiring task");
}

void test_targeted_wakeups() {
    doof::configure_runtime_scheduler(options(4, 4));
    auto& scheduler = doof::detail::RuntimeScheduler::shared();

    // A burst of claimable jobs must reach every token even though each
    // submission notifies only one idle worker.
    for (int round = 0; round < 2; ++round) {
        std::atomic<int> started{0};
        std::vector<doof::Promise<int>> burst;
        for (int i = 0; i < 4; ++i) {
            burst.push_back(doof::submit_async<int>([&started, i] {
                started.fetch_add(1);
                wait_until([&] { return started.load() == 4; }, "burst jobs did not all run concurrently");
                return i;
            }));
        }
        for (int i = 0; i < 4; ++i) {
            require(success(std::move(burst[i])) == i, "burst job result changed");
        }
    }
    wait_until([&] { return scheduler.snapshot().idle_worker_threads == 4; }, "burst workers did not become idle");

    // Sequential jobs wake one idle worker each instead of every idle worker.
    const auto before = scheduler.snapshot().idle_worker_wakeups;
    constexpr int jobs = 200;
    for (int i = 0; i < jobs; ++i) {
        require(success(doof::submit_async<int>([i] { return i; })) == i, "sequential job result changed");
    }
    const auto woken = scheduler.snapshot().idle_worker_wakeups - before;
    require(woken >= jobs / 2, "sequential jobs ran without waking idle workers");
    require(woken <= jobs + jobs / 4,
            "idle workers were woken " + std::to_string(woken) + " times for " + std::to_string(jobs) + " jobs");
    require(scheduler.snapshot().live_worker_threads == 4, "sequential jobs started extra workers");
}

void test_configuration() {
    try {
        doof::configure_runtime_scheduler(options(0, 0));
        fail("zero CPU parallelism was accepted");
    } catch (const doof::Panic&) {}

    try {
        doof::configure_runtime_scheduler(options(1, 2));
        fail("retained workers above the CPU limit were accepted");
    } catch (const doof::Panic&) {}

    auto negative_timeout = options(1, 1);
    negative_timeout.excess_worker_idle_timeout = std::chrono::milliseconds(-1);
    try {
        doof::configure_runtime_scheduler(negative_timeout);
        fail("negative idle timeout was accepted");
    } catch (const doof::Panic&) {}

    auto zero_mailbox = options(1, 1);
    zero_mailbox.actor_mailbox_capacity = 0;
    try {
        doof::configure_runtime_scheduler(zero_mailbox);
        fail("zero actor mailbox capacity was accepted");
    } catch (const doof::Panic&) {}

    auto zero_queue = options(1, 1);
    zero_queue.async_queue_capacity = 0;
    try {
        doof::configure_runtime_scheduler(zero_queue);
        fail("zero async queue capacity was accepted");
    } catch (const doof::Panic&) {}

    auto zero_application = options(1, 1);
    zero_application.application_mailbox_capacity = 0;
    try {
        doof::configure_runtime_scheduler(zero_application);
        fail("zero application mailbox capacity was accepted");
    } catch (const doof::Panic&) {}

    doof::configure_runtime_scheduler(options(1, 1));
    require(success(doof::submit_async<int>([] { return 1; })) == 1, "configured scheduler did not run");
    try {
        doof::configure_runtime_scheduler(options(1, 1));
        fail("configuration after scheduler startup was accepted");
    } catch (const doof::Panic&) {}
}

template <typename F>
std::string panic_message(F&& f) {
    try {
        f();
    } catch (const doof::Panic& panic) {
        return panic.message();
    }
    fail("expected a Doof panic");
}

void require_deadlock(const std::string& message, const std::string& chain) {
    require(message.find("deadlock: blocking wait would never complete") != std::string::npos,
        "deadlock panic message changed: " + message);
    require(message.find(chain) != std::string::npos, "deadlock chain was not reported: " + message);
}

void test_deadlock_detection() {
    doof::configure_runtime_scheduler(options(2, 2));

    // An actor waiting on its own mailbox can never be served.
    auto self = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    require_deadlock(panic_message([&] {
        self->call_sync<int>([self](ActorState&) {
            return self->call_sync<int>([](ActorState& state) { return state.value; });
        });
    }), "(synchronous actor call)");
    require(self->call_sync<int>([](ActorState& state) { return state.value + 1; }) == 1,
        "actor did not recover after a detected self-deadlock");

    // Two actors calling each other synchronously close a two-node cycle.
    auto first = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto second = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    require_deadlock(panic_message([&] {
        first->call_sync<int>([second, first](ActorState&) {
            return second->call_sync<int>([first](ActorState&) {
                return first->call_sync<int>([](ActorState& state) { return state.value; });
            });
        });
    }), "synchronous actor call -> synchronous actor call");

    // A promise is a wait on its producer: an actor awaiting a callback posted
    // to the application thread that is itself blocked on that actor.
    auto poster = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    doof::callback<int()> root([] { return 3; });
    require_deadlock(panic_message([&] {
        poster->call_sync<int>([root](ActorState&) {
            auto result = root.post().get();
            return doof::is_success(result) ? doof::success_value(result) : -1;
        });
    }), "promise wait");
    // Whichever side closes the cycle panics; the posted callback remains queued.
    require(doof::detail::ApplicationDomain::shared().drain_ready() == 1, "posted root callback was lost");

    // Retiring an actor from its own message waits on its own mailbox.
    auto retiring = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto retired = retiring->call_async<int>([retiring](ActorState&) {
        retiring->retire();
        return 0;
    });
    auto retired_result = panic_message([&] { (void)retired.get(); });
    require_deadlock(retired_result, "(actor retirement)");

    // A doomed wait panics before its request is queued, so the request never
    // runs against the caller's unwound frame and the actor keeps its state.
    auto guarded = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    require_deadlock(panic_message([&] {
        guarded->call_sync<void>([guarded](ActorState&) {
            std::string operand(256, 'x');
            guarded->call_sync<void>([&operand](ActorState& state) {
                state.value += static_cast<int>(operand.size());
            });
        });
    }), "(synchronous actor call)");
    require(guarded->call_sync<int>([](ActorState& state) { return state.value; }) == 0,
        "a deadlocked synchronous call was still queued");

    auto left = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto right = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    require_deadlock(panic_message([&] {
        left->call_sync<int>([left, right](ActorState&) {
            return right->call_sync<int>([left](ActorState&) {
                return left->call_sync<int>([](ActorState& state) { return ++state.value; });
            });
        });
    }), "synchronous actor call -> synchronous actor call");
    require(left->call_sync<int>([](ActorState& state) { return state.value; }) == 0,
        "the call closing a deadlock cycle was still queued");

    // Retiring an actor from its own message panics and leaves it running.
    auto self_retiring = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    require_deadlock(panic_message([&] {
        self_retiring->call_sync<int>([self_retiring](ActorState& state) {
            state.value = 7;
            self_retiring->retire();
            return 0;
        });
    }), "(actor retirement)");
    require(self_retiring->call_sync<int>([](ActorState& state) { return state.value + 1; }) == 8,
        "self-retirement stopped the actor");
    require(self_retiring->retire()->value == 7, "self-retirement dropped the actor state");

    // Waits that are satisfied before the waiter wakes must not form cycles.
    auto ping = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto pong = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    std::vector<doof::Promise<int>> rounds;
    for (int i = 0; i < 50; ++i) {
        rounds.push_back(doof::submit_async<int>([ping, pong] {
            return ping->call_sync<int>([pong](ActorState& state) {
                state.value += 1;
                return pong->call_sync<int>([](ActorState& other) { return ++other.value; });
            });
        }));
        rounds.push_back(doof::submit_async<int>([ping, pong] {
            return pong->call_sync<int>([](ActorState& state) { return ++state.value; })
                + ping->call_sync<int>([](ActorState& state) { return state.value; });
        }));
    }
    for (auto& round : rounds) (void)success(std::move(round));
    require(ping->retire()->value == 50 && pong->retire()->value == 100, "acyclic actor traffic was lost");
}

void test_actor_mailbox_capacity() {
    auto configured = options(2, 2);
    configured.actor_mailbox_capacity = 2;
    doof::configure_runtime_scheduler(configured);

    std::promise<void> release;
    auto gate = release.get_future().share();
    auto actor = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    std::atomic<bool> running{false};
    auto blocker = actor->call_async<int>([gate, &running](ActorState&) {
        running.store(true);
        gate.wait();
        return 0;
    });
    // A running message no longer occupies mailbox capacity.
    wait_until([&] { return running.load(); }, "blocking actor message did not start");
    (void)actor->call_async<int>([](ActorState& state) { return ++state.value; });
    std::atomic<int> accepted{1};
    std::thread sender([&] {
        for (int i = 0; i < 3; ++i) {
            (void)actor->call_async<int>([](ActorState& state) { return ++state.value; });
            accepted.fetch_add(1);
        }
    });
    wait_until([&] { return accepted.load() == 2; }, "second queued call was not accepted");
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    require(accepted.load() == 2, "sender was not blocked by a full actor mailbox");

    release.set_value();
    sender.join();
    (void)success(std::move(blocker));
    require(actor->retire()->value == 4, "calls accepted after mailbox capacity freed were lost");

    // An actor filling its own mailbox can never drain it.
    auto looping = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto filled = looping->call_async<int>([looping](ActorState&) {
        for (int i = 0; i < 3; ++i) {
            (void)looping->call_async<int>([](ActorState& state) { return ++state.value; });
        }
        return 0;
    });
    require_deadlock(panic_message([&] { (void)filled.get(); }), "(actor mailbox capacity)");

    // Retirement releases blocked senders with a lifecycle panic.
    std::promise<void> hold;
    auto held = hold.get_future().share();
    auto closing = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    std::atomic<bool> busy_running{false};
    auto busy = closing->call_async<int>([held, &busy_running](ActorState&) {
        busy_running.store(true);
        held.wait();
        return 0;
    });
    wait_until([&] { return busy_running.load(); }, "retiring actor message did not start");
    (void)closing->call_async<int>([](ActorState&) { return 0; });
    (void)closing->call_async<int>([](ActorState&) { return 0; });
    std::string rejected;
    std::thread late([&] {
        rejected = panic_message([&] { (void)closing->call_async<int>([](ActorState&) { return 0; }); });
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    std::thread retirer([&] { closing->retire(); });
    late.join();
    require(rejected == "actor is retiring or retired", "blocked sender was not released by retirement: " + rejected);
    hold.set_value();
    retirer.join();
    (void)success(std::move(busy));
}

template <typename T>
doof::Promise<T> accepted_post(doof::Result<doof::Promise<T>, std::string> posted, const std::string& message) {
    require(doof::is_success(posted), message);
    return std::move(std::get<doof::Success<doof::Promise<T>>>(posted).value);
}

template <typename T>
std::string rejected_post(const doof::Result<doof::Promise<T>, std::string>& posted) {
    if (!doof::is_failure(posted)) return "accepted";
    return std::get<doof::Failure<std::string>>(posted).error;
}

void test_try_post() {
    auto configured = options(2, 2);
    configured.actor_mailbox_capacity = 1;
    configured.application_mailbox_capacity = 2;
    doof::configure_runtime_scheduler(configured);
    auto& application = doof::detail::ApplicationDomain::shared();

    // Root posts observe the application capacity and never block.
    {
        doof::detail::ActiveActorScope scope(&application);
        doof::callback<int(int)> root([](int n) { return n + 1; });
        auto first = accepted_post(root.tryPost(1), "first root post was rejected");
        auto second = accepted_post(root.tryPost(2), "second root post was rejected");
        require(rejected_post(root.tryPost(3)) == "full", "root post beyond capacity was accepted");
        require(application.drain_ready() == 2, "rejected root post was queued");
        require(success(std::move(first)) == 2 && success(std::move(second)) == 3, "root post results changed");
        auto third = accepted_post(root.tryPost(4), "root post after draining was rejected");
        require(application.drain_ready() == 1 && success(std::move(third)) == 5, "drained root post did not run");
    }

    // Actor posts observe the actor mailbox capacity without blocking.
    auto actor = std::make_shared<doof::Actor<ActorState>>(ActorState{});
    auto owned = actor->call_sync<doof::callback<int(int)>>([](ActorState& state) {
        return doof::callback<int(int)>([&state](int n) { return state.value += n; });
    });
    auto notify = actor->call_sync<doof::callback<void(int)>>([](ActorState&) {
        return doof::callback<void(int)>([](int) {});
    });
    std::promise<void> release;
    auto gate = release.get_future().share();
    std::atomic<bool> running{false};
    auto blocker = actor->call_async<int>([gate, &running](ActorState&) {
        running.store(true);
        gate.wait();
        return 0;
    });
    wait_until([&] { return running.load(); }, "blocking actor message did not start");
    auto queued = accepted_post(owned.tryPost(5), "actor post within capacity was rejected");
    require(rejected_post(owned.tryPost(6)) == "full", "actor post beyond capacity was accepted");
    release.set_value();
    (void)success(std::move(blocker));
    require(success(std::move(queued)) == 5, "accepted actor post did not run once");
    auto after = accepted_post(owned.tryPost(2), "actor post after draining was rejected");
    require(success(std::move(after)) == 7, "rejected actor post ran");

    // tryDispatch follows the same capacity rules without a promise.
    auto dispatched = std::make_shared<std::atomic<int>>(0);
    auto counter = actor->call_sync<doof::callback<void(int)>>([dispatched](ActorState&) {
        return doof::callback<void(int)>([dispatched](int n) { dispatched->fetch_add(n); });
    });
    std::promise<void> reopen;
    auto reopened = reopen.get_future().share();
    running.store(false);
    auto held = actor->call_async<int>([reopened, &running](ActorState&) {
        running.store(true);
        reopened.wait();
        return 0;
    });
    wait_until([&] { return running.load(); }, "second blocking actor message did not start");
    require(counter.tryDispatch(3) == doof::detail::TryEnqueueResult::Accepted, "dispatch within capacity was rejected");
    require(counter.tryDispatch(4) == doof::detail::TryEnqueueResult::Full, "dispatch beyond capacity was accepted");
    reopen.set_value();
    (void)success(std::move(held));
    wait_until([&] { return dispatched->load() == 3; }, "accepted dispatch did not run");
    (void)actor->call_sync<int>([](ActorState&) { return 0; });
    require(dispatched->load() == 3, "rejected dispatch ran");

    // Retiring, retired, and released owners report retirement instead of panicking.
    actor->retire();
    require(rejected_post(owned.tryPost(1)) == "retired", "post to a retired actor was not rejected");
    require(counter.tryDispatch(1) == doof::detail::TryEnqueueResult::Retired, "dispatch to a retired actor was not rejected");
    actor.reset();
    require(rejected_post(owned.tryPost(1)) == "retired", "post to a released actor was not rejected");
    require(counter.tryDispatch(1) == doof::detail::TryEnqueueResult::Retired, "dispatch to a released actor was not rejected");

    // Blocking post and dispatch treat a destroyed owner as retired.
    require(panic_message([&] { (void)owned.post(1); }) == "actor is retiring or retired",
        "post to a destroyed actor did not panic as retired");
    require(panic_message([&] { notify.dispatch(1); }) == "actor is retiring or retired",
        "dispatch to a destroyed actor did not panic as retired");
}

void test_async_queue_capacity() {
    auto configured = options(1, 1);
    configured.async_queue_capacity = 1;
    doof::configure_runtime_scheduler(configured);

    std::promise<void> release;
    auto gate = release.get_future().share();
    std::atomic<bool> started{false};
    auto running = doof::submit_async<int>([&, gate] {
        started.store(true);
        gate.wait();
        return 1;
    });
    wait_until([&] { return started.load(); }, "first async job did not start");
    auto queued = doof::submit_async<int>([] { return 2; });
    std::atomic<bool> submitted{false};
    std::optional<doof::Promise<int>> third;
    std::thread submitter([&] {
        third.emplace(doof::submit_async<int>([] { return 3; }));
        submitted.store(true);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    require(!submitted.load(), "submission was accepted beyond the async queue capacity");
    release.set_value();
    submitter.join();
    require(success(std::move(running)) + success(std::move(queued)) + success(std::move(*third)) == 6,
        "bounded async submissions lost results");

    // Started jobs release their slot, so nested submissions keep progressing.
    auto nested = doof::submit_async<int>([] {
        int total = 0;
        for (int i = 0; i < 8; ++i) total += success(doof::submit_async<int>([i] { return i; }));
        return total;
    });
    require(success(std::move(nested)) == 28, "nested bounded submissions deadlocked");
}

void test_collection_indexing() {
    auto settled = std::make_shared<std::vector<bool>>(std::vector<bool>{false, true});
    require(!doof::array_at(settled, 0, "runtime-test", 1), "boolean array read changed");
    require(doof::array_at(settled, 1, "runtime-test", 1), "true boolean array read changed");
    doof::array_at(settled, 0, "runtime-test", 1) = true;
    require(doof::array_at(settled, 0, "runtime-test", 1), "boolean array write changed");

    auto values = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{1});
    doof::array_at(values, 0, "runtime-test", 1) = 2;
    require(doof::array_at(values, 0, "runtime-test", 1) == 2, "ordinary array indexing changed");
}

struct HashKeyStruct {
    int32_t id;
    std::string label;
    template <typename _DoofOther = HashKeyStruct>
    bool operator==(const _DoofOther& other) const { return id == other.id && label == other.label; }
    template <typename _DoofSelf = HashKeyStruct>
    std::size_t doof_hash_value() const {
        const _DoofSelf& self = *this;
        std::size_t seed = 0;
        doof::key_hash_combine(seed, doof::key_hash<int32_t>{}(self.id));
        doof::key_hash_combine(seed, doof::key_hash<std::string>{}(self.label));
        return seed;
    }
};

void test_key_hashing() {
    using Key = std::tuple<int32_t, std::optional<HashKeyStruct>, std::variant<std::monostate, std::string, std::shared_ptr<int>>>;
    auto node = std::make_shared<int>(1);
    doof::ordered_set<Key> keys;
    keys.insert(Key{1, HashKeyStruct{2, "a"}, std::string("x")});
    keys.insert(Key{1, HashKeyStruct{2, "a"}, std::string("x")});
    keys.insert(Key{1, std::nullopt, std::monostate{}});
    keys.insert(Key{1, std::nullopt, node});
    keys.insert(Key{1, std::nullopt, std::make_shared<int>(1)});
    require(keys.size() == 4, "composite keys did not follow member equality and reference identity");
    require(keys.count(Key{1, HashKeyStruct{2, "a"}, std::string("x")}) == 1, "equal composite key was not found");
    require(keys.count(Key{1, std::nullopt, node}) == 1, "identity key was not found by the same reference");
    require(doof::key_hash<HashKeyStruct>{}(HashKeyStruct{2, "a"}) == doof::key_hash<HashKeyStruct>{}(HashKeyStruct{2, "a"}), "equal structs hashed differently");
    require(doof::key_hash<std::variant<int32_t, std::string>>{}(0) != doof::key_hash<std::variant<int32_t, std::string>>{}(std::string()), "union arms did not contribute their index");
}

struct UnionJsonArm {
    doof::SerialObject toSerialObject() const {
        auto object = std::make_shared<doof::ordered_map<std::string, doof::SerialValue>>();
        (*object)["kind"] = doof::serial_value(std::string("arm"));
        return object;
    }
};

void test_serial_integers() {
    using doof::SerialValue;
    using UnionJson = std::variant<std::monostate, std::shared_ptr<UnionJsonArm>>;
    require(doof::serial_is_null(doof::serial_union_value(UnionJson{})), "an absent union arm did not encode as null");
    auto encodedArm = doof::serial_union_value(UnionJson{std::make_shared<UnionJsonArm>()});
    require(doof::serial_is_object(encodedArm) && doof::serial_as_string(doof::serial_object(encodedArm)->find("kind")->second) == "arm", "a union class arm did not encode through its own object");
    require(doof::serial_fits_int(SerialValue{int32_t{3}}), "int storage did not fit int");
    require(doof::serial_fits_int(SerialValue{3.0}), "whole double did not fit int");
    require(doof::serial_fits_int(SerialValue{-2147483648.0}), "int minimum did not fit int");
    require(!doof::serial_fits_int(SerialValue{1.5}), "fraction fitted int");
    require(!doof::serial_fits_int(SerialValue{int64_t{2147483648LL}}), "int overflow fitted int");
    require(!doof::serial_fits_int(SerialValue{std::nan("")}), "NaN fitted int");
    require(!doof::serial_fits_int(SerialValue{std::string("3")}), "string fitted int");
    require(doof::serial_fits_long(SerialValue{int64_t{5000000000LL}}), "long storage did not fit long");
    require(doof::serial_fits_long(SerialValue{-9223372036854775808.0}), "long minimum did not fit long");
    require(!doof::serial_fits_long(SerialValue{9223372036854775808.0}), "2^63 fitted long");
    require(!doof::serial_fits_long(SerialValue{std::numeric_limits<double>::infinity()}), "infinity fitted long");
    require(doof::serial_fits_byte(SerialValue{255.0}) && !doof::serial_fits_byte(SerialValue{int32_t{256}}), "byte range was not exact");
    require(!doof::serial_fits_byte(SerialValue{int32_t{-1}}), "negative fitted byte");
    require(doof::serial_as_int(SerialValue{3.0}) == 3, "whole double did not read as int");
    require(doof::serial_as_long(SerialValue{int32_t{-4}}) == -4, "int storage did not read as long");
    require(doof::serial_fits_int_lenient(SerialValue{true}) && !doof::serial_fits_int_lenient(SerialValue{0.5}), "lenient int fit changed");
}

void test_null_carriers() {
    require(doof::is_null(std::monostate{}), "stored unit was not recognized");
    require(doof::is_null(doof::SerialValue{}), "JSON null was not recognized");
    require(!doof::is_null(doof::SerialValue{int32_t{1}}), "JSON value was treated as null");

    std::optional<int32_t> optional;
    require(doof::is_null(optional), "empty optional was not recognized");
    optional = 1;
    require(!doof::is_null(optional), "present optional was treated as null");

    std::weak_ptr<int> weak;
    require(doof::is_null(weak), "empty weak reference was not recognized");
    auto owner = std::make_shared<int>(7);
    weak = owner;
    require(!doof::is_null(weak), "live weak reference was treated as null");
    require(doof::unwrap_optional(weak).lock() == owner, "weak unwrap lost its referent");
    owner.reset();
    require(weak.expired(), "test weak reference should have expired");
    require(!doof::is_null(weak), "expired weak reference lost its distinct failure state");
    auto unwrapped = doof::unwrap_optional(weak);
    require(!unwrapped.owner_before(weak) && !weak.owner_before(unwrapped), "weak unwrap lost its expired owner");
    std::variant<std::weak_ptr<int>, std::weak_ptr<double>> weakUnion;
    require(doof::is_null(weakUnion), "empty weak union was not recognized");
    weakUnion = weak;
    require(!doof::is_null(weakUnion), "expired weak union was treated as absent");
    require(!doof::is_null(doof::unwrap_optional(weakUnion)), "weak union unwrap lost ownership");

    using Nested = std::variant<int, std::string>;
    using Wider = std::variant<std::monostate, Nested, double>;
    auto nested = doof::variant_promote<Wider>(Nested{7});
    require(std::holds_alternative<Nested>(nested), "variant target arm was flattened");
    require(std::get<int>(std::get<Nested>(nested)) == 7, "nested variant payload was lost");
    auto flat = doof::variant_promote<std::variant<std::monostate, int, std::string>>(Nested{7});
    require(std::get<int>(flat) == 7, "ordinary variant widening stopped working");

    using WeakShape = std::optional<doof::union_t<doof::weak_arms<UnionShape>>>;
    auto held = std::make_shared<double>(2.0);
    auto stored = doof::weak_promote<WeakShape>(UnionShape{held});
    require(stored.has_value() && std::get<std::weak_ptr<double>>(stored.value()).lock() == held, "a strong interface value lost its weak arm");
    require(!doof::weak_promote<WeakShape>(std::variant<std::monostate, std::shared_ptr<int>>{}).has_value(), "absent strong union stored as present");
    require(!doof::weak_promote<WeakShape>(std::shared_ptr<int>{}).has_value(), "null class reference stored as present");
}

void test_string_builder() {
    auto builder = doof::StringBuilder::constructor();
    require(builder->length() == 0, "new string builder was not empty");

    builder->reserve(64);
    builder->appendLine("alpha");
    builder->appendLine("");
    builder->append("omega");
    require(builder->length() == 12, "string builder length was incorrect");
    require(builder->drainToString() == "alpha\n\nomega", "string builder output was incorrect");
    require(builder->length() == 0, "draining did not empty the string builder");

    builder->append("discarded");
    builder->clear();
    require(builder->length() == 0, "clearing did not empty the string builder");
    require(builder->drainToString().empty(), "cleared string builder produced output");
}

void test_string_padding() {
    require(doof::char_from_utf8("é") == U'é', "two-byte UTF-8 character was not decoded");
    require(doof::char_from_utf8("🙂") == U'🙂', "four-byte UTF-8 character was not decoded");
    require(doof::string_padStart("7", 3, U'0') == "007", "ASCII start padding was incorrect");
    require(doof::string_padEnd("7", 3, U'0') == "700", "ASCII end padding was incorrect");
    require(doof::string_padStart("7", 3, U'é') == "é7", "Unicode start padding was not UTF-8 encoded");
    require(doof::string_padEnd("7", 3, U'🙂') == "7🙂", "Unicode end padding did not stop after reaching the byte target");
    require(doof::string_padEnd("7", 2, U'é') == "7é", "Unicode padding did not cross a partial fill boundary");
    require(doof::string_padStart("done", 4, U'x') == "done", "equal-length start padding changed the string");
    require(doof::string_padEnd("done", 2, U'x') == "done", "shorter end padding changed the string");
}

void test_runtime_metrics() {
    require(doof::metrics::snapshot_prometheus().empty(), "new metric registry was not empty");
    doof::metrics::increment_counter("beta_total", 2);
    doof::metrics::increment_counter("alpha_total", 1);
    doof::metrics::increment_counter("alpha_total", -3);

    std::vector<std::thread> workers;
    for (int worker = 0; worker < 8; ++worker) {
        workers.emplace_back([] {
            for (int iteration = 0; iteration < 1000; ++iteration) {
                doof::metrics::increment_counter("concurrent_total", 1);
            }
        });
    }
    for (auto& worker : workers) {
        worker.join();
    }

    require(
        doof::metrics::snapshot_prometheus() ==
            "alpha_total -2\n"
            "beta_total 2\n"
            "concurrent_total 8000\n",
        "metric snapshot was not accumulated, sorted, or thread-safe");
}

#if defined(DOOF_OBSERVE)
std::string observer_get(
    const std::string& url,
    const std::string& path,
    const std::string& method = "GET",
    const std::string& extra_headers = "") {
    const auto port_start = url.find(':', std::string("http://").size()) + 1;
    const auto path_start = url.find('/', port_start);
    const auto port = std::stoi(url.substr(port_start, path_start - port_start));
    const auto client = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    require(client != doof::observe::invalid_socket, "observer test socket could not be created");
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(static_cast<uint16_t>(port));
    require(::connect(client, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == 0,
            "observer test could not connect to loopback server");
    const std::string request = method + " " + path + " HTTP/1.1\r\nHost: 127.0.0.1\r\n" +
        extra_headers + "Connection: close\r\n\r\n";
    require(doof::observe::send_all(client, request), "observer test request could not be sent");
    std::string response;
    std::array<char, 4096> buffer{};
    for (;;) {
        const auto count = ::recv(client, buffer.data(), static_cast<int>(buffer.size()), 0);
        if (count <= 0) break;
        response.append(buffer.data(), static_cast<std::size_t>(count));
    }
    doof::observe::close_socket(client);
    return response;
}

std::string observer_sse(const std::string& url, const std::string& path, uint64_t last_id) {
    const auto port_start = url.find(':', std::string("http://").size()) + 1;
    const auto path_start = url.find('/', port_start);
    const auto port = std::stoi(url.substr(port_start, path_start - port_start));
    const auto client = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    require(client != doof::observe::invalid_socket, "observer SSE test socket could not be created");
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(static_cast<uint16_t>(port));
    require(::connect(client, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == 0,
            "observer SSE test could not connect to loopback server");
    const std::string request = "GET " + path + " HTTP/1.1\r\nHost: 127.0.0.1\r\nLast-Event-ID: " +
        std::to_string(last_id) + "\r\nConnection: close\r\n\r\n";
    require(doof::observe::send_all(client, request), "observer SSE request could not be sent");
    std::string response;
    std::array<char, 4096> buffer{};
    while (response.find("fourth") == std::string::npos) {
        const auto count = ::recv(client, buffer.data(), static_cast<int>(buffer.size()), 0);
        if (count <= 0) break;
        response.append(buffer.data(), static_cast<std::size_t>(count));
    }
    doof::observe::close_socket(client);
    return response;
}

void test_runtime_observer_resilience() {
    const auto url = doof::observe::start_server();
    const auto port_start = url.find(':', std::string("http://").size()) + 1;
    const auto path_start = url.find('/', port_start);
    const auto port = std::stoi(url.substr(port_start, path_start - port_start));
    const auto client = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    require(client != doof::observe::invalid_socket, "slow observer client socket could not be created");
    doof::observe::configure_client_timeout(client);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(static_cast<uint16_t>(port));
    require(::connect(client, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == 0,
            "slow observer client could not connect");
    const std::string request = "GET " + url.substr(path_start) +
        "api/v1/events HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n";
    require(doof::observe::send_all(client, request), "slow observer request could not be sent");
    std::array<char, 4096> buffer{};
    const auto greeting_size = ::recv(client, buffer.data(), static_cast<int>(buffer.size()), 0);
    require(greeting_size > 0, "slow observer client did not receive a stream greeting");

    auto producer = std::async(std::launch::async, [] {
        for (int index = 0; index < 1000; ++index) {
            doof::observe::publish_event("log", "{\"message\":\"" + std::string(16000, 'x') + "\"}");
        }
    });
    require(producer.wait_for(std::chrono::seconds(2)) == std::future_status::ready,
            "a slow SSE client backpressured telemetry producers");
    producer.get();

    doof::observe::close_socket(client);
    uint64_t last_id = 0;
    {
        std::lock_guard<std::mutex> lock(doof::observe::events_mutex);
        last_id = doof::observe::next_event_id - 1;
    }
    const auto clean_client = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    require(clean_client != doof::observe::invalid_socket, "shutdown observer client socket could not be created");
    doof::observe::configure_client_timeout(clean_client);
    require(::connect(clean_client, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == 0,
            "shutdown observer client could not connect");
    const std::string clean_request = "GET " + url.substr(path_start) +
        "api/v1/events HTTP/1.1\r\nHost: 127.0.0.1\r\nLast-Event-ID: " +
        std::to_string(last_id) + "\r\nConnection: close\r\n\r\n";
    require(doof::observe::send_all(clean_client, clean_request), "shutdown observer request could not be sent");
    require(::recv(clean_client, buffer.data(), static_cast<int>(buffer.size()), 0) > 0,
            "shutdown observer client did not receive a stream greeting");
    auto stopper = std::async(std::launch::async, [] { doof::observe::stop_server(); });
    std::string shutdown_stream;
    while (shutdown_stream.find("event: shutdown") == std::string::npos) {
        const auto received = ::recv(clean_client, buffer.data(), static_cast<int>(buffer.size()), 0);
        if (received <= 0) break;
        shutdown_stream.append(buffer.data(), static_cast<std::size_t>(received));
    }
    doof::observe::close_socket(clean_client);
    require(shutdown_stream.find("event: shutdown") != std::string::npos,
            "clean observer shutdown was not delivered to an SSE client");
    require(stopper.wait_for(std::chrono::seconds(5)) == std::future_status::ready,
            "observer shutdown did not finish after clients disconnected");
    stopper.get();
    require(!doof::observe::running.load() && doof::observe::active_clients.load() == 0,
            "observer did not stop and release slow client connections");
    {
        std::lock_guard<std::mutex> lock(doof::observe::events_mutex);
        require(!doof::observe::events.empty() && doof::observe::events.back().type == "shutdown",
                "observer shutdown event was not published");
    }
}

void test_runtime_observer() {
    require(doof::observe::parse_after_query("after=42") == 42 &&
            doof::observe::parse_after_query("after=42junk") == 0,
            "observer snapshot cursor query was not validated");
    for (int iteration = 0; iteration < 100; ++iteration) {
        doof::observe::publish_metric("coalesced_total", iteration);
    }
    doof::observe::flush_metric_events();
    {
        std::lock_guard<std::mutex> lock(doof::observe::events_mutex);
        require(doof::observe::events.size() == 1, "metric burst did not coalesce into one event");
        require(doof::observe::events.front().type == "metrics" &&
                doof::observe::events.front().data.find("\"value\":99") != std::string::npos,
                "coalesced metric event omitted the final value");
    }
    doof::metrics::increment_counter("observer_requests_total", 7);
    doof::observe::publish_event("log", "{\"message\":\"first\"}");
    doof::observe::publish_event("log", "{\"message\":\"second\"}");
    doof::observe::publish_event("log", "{\"message\":\"third\"}");
    doof::observe::publish_event("log", "{\"message\":\"fourth\"}");
    const auto url = doof::observe::start_server();
    require(url.find("http://127.0.0.1:") == 0, "observer did not publish a loopback URL");
    const auto path_start = url.find('/', std::string("http://").size());
    const auto root = url.substr(path_start);
    const auto snapshot = observer_get(url, root + "api/v1/snapshot");
    require(snapshot.find("HTTP/1.1 200 OK") != std::string::npos, "observer snapshot was not served");
    require(snapshot.find("\"name\":\"observer_requests_total\",\"value\":7") != std::string::npos,
            "observer snapshot omitted runtime metrics");
    require(snapshot.find("\"version\":1") != std::string::npos && snapshot.find("\"logs\":[") != std::string::npos,
            "observer snapshot omitted versioned session or retained logs");
    require(snapshot.find("Access-Control-Allow-Origin") == std::string::npos,
            "observer unexpectedly enabled cross-origin access");
    const auto dashboard = observer_get(url, root);
    require(dashboard.find("Content-Security-Policy: default-src 'none'") != std::string::npos,
            "observer dashboard omitted its content security policy");
    require(dashboard.find("observer_requests_total") != std::string::npos,
            "observer dashboard omitted runtime metrics");
    const auto denied = observer_get(url, "/api/v1/snapshot");
    require(denied.find("HTTP/1.1 404 Not Found") != std::string::npos,
            "observer endpoint was reachable without its session token");
#if defined(__APPLE__)
    require(doof::observe::listener_v6 != doof::observe::invalid_socket,
            "observer did not start its macOS IPv6 loopback listener");
#endif
    if (doof::observe::listener_v6 != doof::observe::invalid_socket) {
        const auto port_start = url.find(':', std::string("http://").size()) + 1;
        const auto port = std::stoi(url.substr(port_start, path_start - port_start));
        const auto ipv6_client = ::socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        require(ipv6_client != doof::observe::invalid_socket, "IPv6 observer client socket could not be created");
        sockaddr_in6 ipv6_address{};
        ipv6_address.sin6_family = AF_INET6;
        ipv6_address.sin6_addr = in6addr_loopback;
        ipv6_address.sin6_port = htons(static_cast<uint16_t>(port));
        require(::connect(ipv6_client, reinterpret_cast<sockaddr*>(&ipv6_address), sizeof(ipv6_address)) == 0,
                "observer did not bind the IPv6 loopback listener");
        const std::string ipv6_request = "GET " + root +
            "api/v1/snapshot HTTP/1.1\r\nHost: [::1]\r\nConnection: close\r\n\r\n";
        require(doof::observe::send_all(ipv6_client, ipv6_request), "IPv6 observer request could not be sent");
        std::array<char, 4096> ipv6_buffer{};
        const auto ipv6_count = ::recv(ipv6_client, ipv6_buffer.data(), static_cast<int>(ipv6_buffer.size()), 0);
        require(ipv6_count > 0 && std::string(ipv6_buffer.data(), static_cast<std::size_t>(ipv6_count))
                .find("HTTP/1.1 200 OK") != std::string::npos,
                "observer did not serve an authenticated IPv6 loopback request");
        doof::observe::close_socket(ipv6_client);
    }
    const auto wrong_method = observer_get(url, root + "api/v1/snapshot", "POST");
    require(wrong_method.find("HTTP/1.1 405 Method Not Allowed") != std::string::npos,
            "observer accepted a mutating HTTP method");
    const auto oversized = observer_get(url, root + "api/v1/snapshot", "GET", "X-Long: " + std::string(9000, 'x') + "\r\n");
    require(oversized.find("HTTP/1.1 413 Content Too Large") != std::string::npos,
            "observer accepted oversized request headers");
    const auto stream = observer_sse(url, root + "api/v1/events", 1);
    require(stream.find("Content-Type: text/event-stream") != std::string::npos,
            "observer event endpoint was not an SSE stream");
    require(stream.find("event: hello") != std::string::npos,
            "observer stream omitted its protocol greeting");
    require(stream.find("event: gap") != std::string::npos,
            "observer did not signal an event retention gap");
    require(stream.find("event: log") != std::string::npos && stream.find("fourth") != std::string::npos,
            "observer did not replay retained events");
}

void test_runtime_observer_custom_ui() {
    const auto url = doof::observe::start_server();
    if (const char* url_file = std::getenv("DOOF_OBSERVE_URL_FILE")) {
        std::ifstream input(url_file);
        std::string published;
        std::getline(input, published);
        require(published == url, "detached app URL discovery file did not contain the session URL");
#if !defined(_WIN32)
        const auto permissions = std::filesystem::status(url_file).permissions();
        require((permissions & std::filesystem::perms::group_read) == std::filesystem::perms::none &&
                (permissions & std::filesystem::perms::others_read) == std::filesystem::perms::none,
                "observer URL discovery file was readable by another account");
#endif
    }
    const auto path_start = url.find('/', std::string("http://").size());
    const auto root = url.substr(path_start);
    const auto index = observer_get(url, root);
    require(index.find("Bespoke Doof Observe") != std::string::npos,
            "observer did not serve the package's custom index page");
    require(index.find("script-src 'self'") != std::string::npos,
            "custom observer UI omitted its restrictive CSP");
    const auto css = observer_get(url, root + "custom.css");
    require(css.find("Content-Type: text/css") != std::string::npos,
            "custom observer CSS had the wrong MIME type");
    const auto js = observer_get(url, root + "custom.js");
    require(js.find("Content-Type: text/javascript") != std::string::npos,
            "custom observer JavaScript had the wrong MIME type");
    const auto missing = observer_get(url, root + "missing.js");
    require(missing.find("HTTP/1.1 404 Not Found") != std::string::npos,
            "missing custom asset did not return 404");
    const auto traversal = observer_get(url, root + "../doof.json");
    require(traversal.find("HTTP/1.1 404 Not Found") != std::string::npos,
            "custom asset traversal escaped the UI root");
    const auto snapshot = observer_get(url, root + "api/v1/snapshot");
    require(snapshot.find("\"version\":1") != std::string::npos,
            "custom UI changed the observer API");
}
#endif

} // namespace

int main(int argc, char** argv) {
    {
        doof::callback<int()> first([count = 0]() mutable { return ++count; });
        auto copy = first;
        doof::callback<int()> other([] { return 1; });
        require(first == copy && first != other, "callback identity was not preserved");
        require(first.call() == 1 && copy.call() == 2, "callback copies lost shared closure state");
        auto captured = std::make_shared<int>(7);
        std::weak_ptr<int> weak = captured;
        doof::callback<void()> selfClearing;
        selfClearing = doof::callback<void()>([captured, &selfClearing] {
            selfClearing = {};
            require(*captured == 7, "clearing a running callback released its captures early");
        });
        captured.reset();
        selfClearing.call();
        require(weak.expired(), "completed callback retained its captures");
    }
    {
        const auto below = doof::range(2147483645, 2147483646, "main.do", 3);
        require(below.upperBound == 2147483647, "inclusive range below the maximum int lost its end");
        require(doof::inclusive_range_end(5, "main.do", 3) == 5, "inclusive range end changed an ordinary bound");
        try {
            (void)doof::range(0, 2147483647, "main.do", 4);
            fail("inclusive range ending at the maximum int did not panic");
        } catch (const doof::Panic& panic) {
            require(panic.message() == "main.do:4: Inclusive range cannot end at the maximum int (2147483647)", "inclusive range panic message changed");
        }
    }
    if (argc != 2) {
        fail("expected one test mode");
    }
    const std::string mode = argv[1];
    if (mode == "limit") test_cpu_limit();
    else if (mode == "nested") test_nested_waits();
    else if (mode == "first-completed") test_first_completed_promise();
    else if (mode == "actor") test_actor_serialization();
    else if (mode == "actor-waits") test_actor_waits();
    else if (mode == "actor-batching") test_actor_batching();
    else if (mode == "failures") test_failures();
    else if (mode == "application") test_application_domain();
    else if (mode == "callback-release") test_callback_release_domain();
    else if (mode == "release") test_token_release_and_retirement();
    else if (mode == "priority") test_reacquire_priority();
    else if (mode == "wakeups") test_targeted_wakeups();
    else if (mode == "configuration") test_configuration();
    else if (mode == "deadlock") test_deadlock_detection();
    else if (mode == "mailbox-capacity") test_actor_mailbox_capacity();
    else if (mode == "async-capacity") test_async_queue_capacity();
    else if (mode == "try-post") test_try_post();
    else if (mode == "collections") { test_collection_indexing(); test_key_hashing(); }
    else if (mode == "nulls") test_null_carriers();
    else if (mode == "serial-integers") test_serial_integers();
    else if (mode == "string-builder") test_string_builder();
    else if (mode == "string-padding") test_string_padding();
    else if (mode == "metrics") test_runtime_metrics();
#if defined(DOOF_OBSERVE)
    else if (mode == "observer" || mode == "observer-custom" || mode == "observer-resilience") {
#if defined(_WIN32)
        _putenv_s("DOOF_OBSERVE_NO_OPEN", "1");
#else
        ::setenv("DOOF_OBSERVE_NO_OPEN", "1", 1);
#endif
        if (mode == "observer") test_runtime_observer();
        else if (mode == "observer-custom") test_runtime_observer_custom_ui();
        else test_runtime_observer_resilience();
    }
#endif
    else fail("unknown test mode: " + mode);
    return 0;
}
