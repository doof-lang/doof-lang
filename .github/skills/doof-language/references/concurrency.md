# Doof Concurrency Reference

## Overview

Doof concurrency is actor-owned. An `Actor<T>` is a concurrent mutable domain
containing one mutable `T`. The main thread is the implicit root actor domain.

Core rules:

- Mutable state belongs to exactly one actor domain at a time.
- Immutable values may cross actor boundaries freely.
- Cross-domain mutable interaction happens through actor method calls.
- Actor method calls are synchronous by default.
- `async` supports actor method calls and isolated value-producing blocks.
- `retire actor` drains accepted work, stops the actor, and returns the inner
  state.

## Actors

```doof
class Counter {
    value: int

    increment(n: int): none {
        this.value = this.value + n
    }

    get(): int {
        return this.value
    }
}

counter := Actor<Counter>(0)
counter.increment(5)
now := counter.get()
```

Each actor processes one method call at a time. Actors are serial execution
domains rather than dedicated threads, so consecutive messages may run on
different shared runtime workers. A caller that does not use `async` blocks
until the method completes.

## Async Actor Calls

`async` enqueues an actor method call and returns `Promise<T>`:

```doof
worker := Actor<Counter>(0)
p := async worker.increment(10)
try! p.get()
```

Ordinary functions may be dispatched directly when they are inferred isolated
and their arguments satisfy actor-call boundary rules:

```doof
promise := async compute(input)
```

## Async Blocks

An async block runs outside the caller's actor domain and yields its result
through `Promise<T>`:

```doof
base := 20
promise := async {
    let values = [base + 1]
    values.push(22)
    yield values
}
values := try! promise.get()
```

Every reachable path must `yield`. Captures are copied and must come from
immutable bindings with deeply immutable, thread-safe types. Mutable locals and
fresh mutable values are allowed inside the block. The yielded graph may be
mutable because the temporary worker domain ends before the caller receives
it.

Actor, promise, callback, weak-reference, and stream handles cannot be captured
or occur recursively in the yielded graph. Async-block code may invoke only
transitively isolated code and cannot access mutable module/static state.

Nested async blocks and async calls on locally created actors are allowed, but
their handles must be consumed before yielding. Worker identity and timing are
deliberately unspecified.

The runtime uses a process-wide FIFO scheduler. Pending work is unbounded, but
CPU execution is limited to the host hardware-concurrency count by default
(falling back to one). The application/UI thread is outside this token limit.
One actor message at a time is eligible from each FIFO actor mailbox.

Worker waits in `Promise.get()`, synchronous actor calls, and actor retirement
automatically relinquish their CPU token. This lets nested work progress at a
one-token limit. Blocking native C++ integrations may use
`doof::CpuTokenRelease`; ordinary Doof code has no token-control API. Blocked
workers can be replaced by compensating threads, so blocked OS-thread count is
not hard-capped. Excess idle workers retire after 30 seconds by default.

Native hosts can configure the CPU limit, retained workers, and idle timeout
with `doof::RuntimeSchedulerOptions` and
`doof::configure_runtime_scheduler(...)` before the first scheduled job.

`isolated` is an enforced transitive effect. Isolated code cannot access mutable
module/static state or call non-isolated code. It may mutate `this`, parameters,
locals, and freshly created values. Ordinary functions are inferred isolated
when they meet the same rules. The modifier does not create worker-pool
execution by itself; use `async functionCall(args)` or an async block.

Bodyless native code needs an explicit trusted contract because the compiler
cannot inspect its implementation. Use `import isolated function` for native
free functions and `isolated` on native class methods.

## Retirement

`retire actor` enqueues a retirement request after already accepted work:

```doof
job := Actor<Counter>(0)
p := async job.increment(10)
try! p.get()

state: Counter := retire job
```

Retirement behavior:

1. The actor stops accepting new calls.
2. Already queued calls continue in order.
3. The actor stops when the retirement request reaches the front of the queue.
4. The inner `T` is returned to the retiring domain.
5. Later calls through aliases panic because the actor is retiring or retired.

Failures from earlier async actor calls are observed through their
`Promise<T>`. `retire` returns the inner state and does not aggregate prior
promise failures.

Actor references inside the returned state remain live actors with their own
domains. Retirement moves ordinary state, not actor domains.

There is no public `actor.stop()` lifecycle method. If the actor's inner class
defines `stop`, `actor.stop()` is an ordinary actor method call. Use
`retire actor` for lifecycle shutdown.

## Promises

```doof
class Promise<T> {
    function get(): Result<T, string>
}
```

`Promise<T>` is produced by async actor calls, isolated function calls, and
async blocks. `get()` blocks until the queued work completes, relinquishing a
runtime worker's CPU token during the wait, and reports thrown runtime failures
as `Result<T, string>`.

A mutable promise array can drive completion-order work:

```doof
while pending.length > 0 {
    value := pending.takeFirstCompleted() else error {
        panic(error)
    }
    consume(value)
}
```

`takeFirstCompleted()` blocks until any contained promise settles, removes that
promise, and returns the same `Result<T, string>` as its `get()` method. An
empty array returns `Failure<string>`. The wait is notification-driven rather
than polled and relinquishes a runtime-worker CPU token like `get()`.

## Actor Boundary Summary

| Type | To actor method |
|------|-----------------|
| Primitives | Allowed |
| Immutable objects/collections | Allowed |
| Mutable objects/collections | Rejected |
| `Actor<T>` | Rejected |
| `Promise<T>` | Rejected |

Actor references may be copied inside the domain that owns them. They may not be
passed into another actor method.

`Actor<T>(...)` construction is also a boundary. Explicit constructor arguments
must be boundary-safe, and omitted defaults or constructor factories must be
isolated so they cannot capture mutable module/static state into the new actor.

Interface-typed payloads are safe only when every known concrete implementation
is safe. A readonly interface field must be implemented by a readonly class
field; widening cannot be used to conceal mutable storage.

Calling a method through `Actor<T>` requires that method to be inferred
isolated, including all transitive helper calls.

## Actor-Affine Callbacks

Function values lower to actor-affine callbacks. A callback belongs to the actor
domain where it was created. Normal call syntax invokes the callback locally:

```doof
function apply(f: (x: int): int, x: int): int => f(x)
```

The explicit local form is:

```doof
function apply(f: (x: int): int, x: int): int => f.call(x)
```

Local callback calls are checked by the runtime and must execute inside the
owning actor domain. Use `callback.post(args)` to enqueue callback work back
onto the owning actor; it returns `Promise<R>` for callback return type `R`.
Root-domain callbacks post to the root application mailbox. The host decides
which thread drains that mailbox, which preserves UI runtime thread affinity.

Actor-affine callback values may cross actor method boundaries, but their
parameter and return payload types must also be boundary-safe. Function-typed
parameters in native imports lower to `doof::callback`; native C++ must choose
local call or posting behavior explicitly instead of receiving an erased
`std::function`.

## Common Pattern: Isolated Background Work

```doof
promise := async {
    yield compute()
}
answer := try! promise.get()
```

Use a temporary actor instead when the background work needs a persistent
mutable domain or sequential mailbox behavior.

## Common Pattern: Temporary Actor

```doof
class Computation {
    input: int

    run(): int {
        return this.input * this.input
    }
}

job := Actor<Computation>(42)
p := async job.run()
answer := try! p.get()
retire job
```
