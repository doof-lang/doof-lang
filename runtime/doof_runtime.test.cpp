#include "doof_runtime.hpp"

#include <atomic>
#include <iostream>

static_assert(std::is_same_v<decltype(doof::panic(std::declval<const std::string&>())), doof::Never>);
static_assert(!std::is_default_constructible_v<doof::Never>);
static_assert(!std::is_aggregate_v<doof::Never>);
static_assert(std::is_copy_constructible_v<doof::Result<doof::Never, std::string>>);
static_assert(std::is_move_constructible_v<doof::Result<doof::Never, std::string>>);

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
