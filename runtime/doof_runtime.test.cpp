#include "doof_runtime.h"

#include <atomic>
#include <iostream>

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

    doof::configure_runtime_scheduler(options(1, 1));
    require(success(doof::submit_async<int>([] { return 1; })) == 1, "configured scheduler did not run");
    try {
        doof::configure_runtime_scheduler(options(1, 1));
        fail("configuration after scheduler startup was accepted");
    } catch (const doof::Panic&) {}
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

void test_null_carriers() {
    require(doof::is_null(doof::JsonValue{}), "JSON null was not recognized");
    require(!doof::is_null(doof::JsonValue{int32_t{1}}), "JSON value was treated as null");

    std::optional<int32_t> optional;
    require(doof::is_null(optional), "empty optional was not recognized");
    optional = 1;
    require(!doof::is_null(optional), "present optional was treated as null");
}

} // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        fail("expected one test mode");
    }
    const std::string mode = argv[1];
    if (mode == "limit") test_cpu_limit();
    else if (mode == "nested") test_nested_waits();
    else if (mode == "first-completed") test_first_completed_promise();
    else if (mode == "actor") test_actor_serialization();
    else if (mode == "actor-waits") test_actor_waits();
    else if (mode == "failures") test_failures();
    else if (mode == "application") test_application_domain();
    else if (mode == "release") test_token_release_and_retirement();
    else if (mode == "priority") test_reacquire_priority();
    else if (mode == "configuration") test_configuration();
    else if (mode == "collections") test_collection_indexing();
    else if (mode == "nulls") test_null_carriers();
    else fail("unknown test mode: " + mode);
    return 0;
}
