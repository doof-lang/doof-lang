#include "doof_runtime.hpp"

#include <atomic>
#include <iostream>

namespace {
void require(bool value, const char* message) {
    if (!value) throw std::runtime_error(message);
}

template <typename F>
void expect_panic(F&& operation, const std::string& message) {
    try { operation(); }
    catch (const doof::Panic& panic) {
        require(panic.message().find(message) != std::string::npos, "wrong panic diagnostic");
        return;
    }
    throw std::runtime_error("expected a panic");
}

template <typename Predicate>
void wait_until(Predicate predicate) {
    auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (!predicate()) {
        require(std::chrono::steady_clock::now() < deadline, "timed out");
        std::this_thread::yield();
    }
}

using IntResult = doof::Result<int, std::string>;
using IntCallback = doof::callback<void(IntResult)>;

void drain() {
    while (doof::detail::ApplicationDomain::shared().wait_and_dispatch_one()) {}
}

void delivery_and_consumption() {
    auto& app = doof::detail::ApplicationDomain::shared();
    const auto thread = std::this_thread::get_id();
    for (bool already_ready : {false, true}) {
        auto state = std::make_shared<doof::detail::PromiseState<int>>();
        doof::Promise<int> promise(state);
        auto alias = promise;
        int calls = 0;
        IntCallback callback([&](IntResult result) {
            require(doof::success_value(result) == 42, "result changed");
            require(doof::current_actor_domain() == &app, "wrong callback domain");
            require(std::this_thread::get_id() == thread, "root callback ran on worker");
            ++calls;
        });
        if (already_ready) state->complete([] { return 42; });
        promise.onComplete(callback);
        require(calls == 0, "completion ran inline");
        expect_panic([&] { alias.get(); }, "already claimed");
        expect_panic([&] { alias.onComplete(callback); }, "already claimed");
        if (!already_ready) {
            require(app.drain_ready() == 0, "pending promise queued before completion");
            state->complete([] { return 42; });
        }
        require(calls == 0, "producer ran callback inline");
        drain();
        require(calls == 1, "completion was lost or duplicated");
    }

    auto value = doof::submit_async<int>([] { return 7; });
    auto alias = value;
    require(doof::success_value(value.get()) == 7, "get result changed");
    expect_panic([&] { alias.get(); }, "already claimed");
    expect_panic([&] { alias.onComplete(IntCallback([](IntResult) {})); }, "already claimed");
    auto array = std::make_shared<std::vector<doof::Promise<int>>>();
    array->push_back(alias);
    expect_panic([&] { doof::promise_take_first_completed(array); }, "already claimed");

    auto pending = doof::submit_async<int>([] { return 9; });
    array->clear();
    array->push_back(pending);
    require(doof::success_value(doof::promise_take_first_completed(array)) == 9, "array result changed");
    expect_panic([&] { pending.get(); }, "already claimed");
    require(array->empty(), "array did not remove consumer");
    drain(); // Failed registrations must not leak a keep-alive reservation.
}

void payloads_and_failures() {
    int calls = 0;
    doof::submit_async<void>([] {}).onComplete(doof::callback<void(doof::Result<void, std::string>)>([&](auto result) {
        require(doof::is_success(result), "none success failed");
        ++calls;
    }));
    doof::submit_async<int>([]() -> int { throw std::runtime_error("failed"); }).onComplete(IntCallback([&](auto result) {
        require(doof::failure_error(result) == "failed", "native failure changed");
        ++calls;
    }));
    doof::submit_async<void>([] { throw 42; }).onComplete(doof::callback<void(doof::Result<void, std::string>)>([&](auto result) {
        require(doof::failure_error(result) == "unknown error", "unknown failure changed");
        ++calls;
    }));
    using Nested = doof::Result<IntResult, std::string>;
    doof::submit_async<IntResult>([]() -> IntResult { return doof::Failure<std::string>{"domain error"}; })
        .onComplete(doof::callback<void(Nested)>([&](auto result) {
            require(doof::failure_error(doof::success_value(result)) == "domain error", "nested result flattened");
            ++calls;
        }));

    // Both owned mutable graphs and native move-only values must be delivered
    // without a retained second copy in the consumed promise's storage.
    using Values = std::shared_ptr<std::vector<int>>;
    auto values = doof::submit_async<Values>([] { return std::make_shared<std::vector<int>>(1, 3); });
    std::weak_ptr<std::vector<int>> weak;
    values.onComplete(doof::callback<void(doof::Result<Values, std::string>)>([&](auto result) {
        auto& items = doof::success_value(result);
        weak = items;
        items->push_back(4);
        require(items->size() == 2, "mutable transfer failed");
        ++calls;
    }));
    doof::submit_async<std::unique_ptr<int>>([] { return std::make_unique<int>(5); })
        .onComplete(doof::callback<void(doof::Result<std::unique_ptr<int>, std::string>)>([&](auto result) {
            require(*doof::success_value(result) == 5, "move-only result changed");
            ++calls;
        }));
    drain();
    require(calls == 6, "payload callback missing");
    require(weak.expired(), "consumed promise retained mutable result");

    auto state = std::make_shared<doof::detail::PromiseState<int>>();
    doof::Promise<int> promise(state);
    auto waiter = std::async(std::launch::async, [promise] { return promise.get(); });
    wait_until([&] {
        try { promise.ready(); return false; }
        catch (const doof::Panic&) { return true; }
    });
    expect_panic([&] { promise.onComplete(IntCallback([](IntResult) {})); }, "already claimed");
    state->complete([] { return 11; });
    require(doof::success_value(waiter.get()) == 11, "blocking get lost claim");
}

struct ActorState { int value = 0; };

void actor_delivery_and_retirement() {
    auto actor = std::make_shared<doof::Actor<ActorState>>();
    auto callback = actor->call_sync<IntCallback>([&](ActorState& state) {
        return IntCallback([&state, domain = actor.get()](IntResult result) {
            require(doof::current_actor_domain() == domain, "completion missed owning actor");
            state.value += doof::success_value(result);
        });
    });
    auto source = std::make_shared<doof::detail::PromiseState<int>>();
    doof::Promise<int> promise(source);
    promise.onComplete(callback);
    expect_panic([&] { promise.onComplete(callback); }, "already claimed");
    auto retired = std::async(std::launch::async, [actor] { return actor->retire(); });
    wait_until([&] {
        try { actor->call_sync<void>([](ActorState&) {}); return false; }
        catch (const doof::Panic&) { return true; }
    });
    require(retired.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready, "retired before reserved delivery");
    source->complete([] { return 17; });
    require(retired.get()->value == 17, "retirement failed to drain completion");
    auto late = doof::submit_async<int>([] { return 1; });
    expect_panic([&] { late.onComplete(callback); }, "retiring or retired");
    require(doof::success_value(late.get()) == 1, "failed registration consumed promise");
    drain();

    auto owner = std::make_shared<doof::Actor<ActorState>>();
    std::weak_ptr<doof::Actor<ActorState>> weak = owner;
    auto cb = owner->call_sync<IntCallback>([](ActorState& state) {
        return IntCallback([&state](IntResult result) { state.value = doof::success_value(result); });
    });
    auto completion = std::make_shared<doof::detail::PromiseState<int>>();
    doof::Promise<int>(completion).onComplete(cb);
    owner.reset();
    require(!weak.expired(), "registration failed to retain actor");
    completion->complete([] { return 2; });
    drain();
    wait_until([&] { return weak.expired(); });
    expect_panic([&] { doof::submit_async<int>([] { return 0; }).onComplete(cb); }, "live actor domain");

    auto isolated = doof::submit_async<int>([] {
        auto p = doof::submit_async<int>([] { return 1; });
        expect_panic([&] { p.onComplete(IntCallback([](IntResult) {})); }, "isolated async work");
        return doof::success_value(p.get());
    });
    require(doof::success_value(isolated.get()) == 1, "isolated callback guard consumed promise");

    // The completion guard must not change ordinary unowned callback behavior
    // in isolated work: dispatch stays inline and post targets the root domain.
    int dispatched = 0;
    auto posted = doof::submit_async<doof::Promise<int>>([&dispatched] {
        doof::callback<void()> local([&dispatched] { ++dispatched; });
        local.dispatch();
        return doof::callback<int()>([] { return 5; }).post();
    });
    auto posted_result = doof::success_value(posted.get());
    require(dispatched == 1, "isolated dispatch no longer ran inline");
    drain();
    require(doof::success_value(posted_result.get()) == 5, "isolated post no longer reached root");

    auto serial = std::make_shared<doof::Actor<ActorState>>();
    serial->call_sync<void>([](ActorState& state) {
        auto ready = std::make_shared<doof::detail::PromiseState<int>>();
        ready->complete([] { return 23; });
        doof::Promise<int>(ready).onComplete(IntCallback([&state](IntResult result) {
            require(state.value == 1, "same-actor completion ran inline");
            state.value = doof::success_value(result);
        }));
        require(state.value == 0, "registration reentered actor");
        state.value = 1;
    });
    require(serial->retire()->value == 23, "same-actor ready delivery missing");
    drain();
}

void registration_races() {
    int calls = 0;
    for (int i = 0; i < 300; ++i) {
        auto state = std::make_shared<doof::detail::PromiseState<int>>();
        doof::Promise<int> promise(state);
        std::thread producer([state, i] { state->complete([i] { return i; }); });
        promise.onComplete(IntCallback([&, i](IntResult result) {
            require(doof::success_value(result) == i, "racing completion value changed");
            ++calls;
        }));
        producer.join();
    }
    drain();
    require(calls == 300, "registration/completion race lost or duplicated callback");

    for (int i = 0; i < 100; ++i) {
        auto promise = doof::submit_async<int>([] { return 1; });
        IntCallback cb([&](IntResult) { ++calls; });
        std::atomic<int> winners{0};
        std::atomic<int> rejected{0};
        auto compete = [&] {
            try { promise.onComplete(cb); ++winners; }
            catch (const doof::Panic&) { ++rejected; }
        };
        std::thread first(compete), second(compete);
        first.join(); second.join();
        require(winners == 1 && rejected == 1, "aliases registered multiple consumers");
    }
    drain();
    require(calls == 400, "competing consumers lost or duplicated delivery");
}

void entrypoint_drain_ignores_other_keep_alive_sources() {
    auto& app = doof::detail::ApplicationDomain::shared();
    // An open channel or timer must not hold a command-line process past main.
    app.add_keep_alive_source(true);
    auto state = std::make_shared<doof::detail::PromiseState<int>>();
    int calls = 0;
    doof::Promise<int>(state).onComplete(IntCallback([&](IntResult) { ++calls; }));
    std::thread producer([state] { state->complete([] { return 3; }); });
    while (app.dispatch_pending_completion()) {}
    producer.join();
    require(calls == 1, "entrypoint drain missed a pending completion");
    require(!app.dispatch_pending_completion(), "entrypoint drain waited on unrelated keep-alive");
    app.remove_keep_alive_source(true);
}
} // namespace

int main(int argc, char** argv) {
    doof::RuntimeSchedulerOptions options;
    options.maximum_cpu_parallelism = 2;
    options.retained_worker_count = 2;
    options.excess_worker_idle_timeout = std::chrono::milliseconds(50);
    doof::configure_runtime_scheduler(options);
    auto& app = doof::detail::ApplicationDomain::shared();
    doof::detail::ActiveActorScope scope(&app);
    if (argc > 1) {
        const bool producer = std::string(argv[1]) == "producer-panic";
        auto promise = doof::submit_async<int>([producer] { if (producer) doof::panic("producer panic"); return 1; });
        promise.onComplete(IntCallback([](IntResult) { doof::panic("callback panic"); }));
        drain();
        return 2;
    }
    delivery_and_consumption();
    payloads_and_failures();
    actor_delivery_and_retirement();
    registration_races();
    entrypoint_drain_ignores_other_keep_alive_sources();
    require(!app.wait_and_dispatch_one(), "completion keep-alive leaked");
    std::cout << "promise completion tests passed\n";
}
