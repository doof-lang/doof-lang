# Concurrency

## Overview

Doof's concurrency model is built around actor-owned mutable domains.

An `Actor<T>` is a concurrent domain containing one mutable `T`. The main thread
is the implicit root actor domain. Mutable state belongs to exactly one actor
domain at a time. Immutable values may be shared freely across actor domains.

Cross-domain mutable interaction happens only through actor method calls.

---

## Actors

Actors wrap classes:

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
```

Each actor processes method calls sequentially. An actor is a serial execution
domain, not a thread identity: consecutive messages may execute on different
runtime worker threads, but messages for one actor never overlap.

---

## Actor Calls

Actor calls are synchronous by default:

```doof
counter.increment(5)
n := counter.get()
```

The caller blocks until the actor method completes.

Actor calls may be asynchronous:

```doof
p := async counter.increment(10)
try! p.get()
```

`async actor.method(args)` returns `Promise<T>`, where `T` is the actor method's
return type.

`async` is also valid with a value-producing block:

```doof
input := 21
promise := async {
    let values = [input * 2]
    values.push(43)
    yield values
}
values := try! promise.get()
```

`async { ... }` executes outside the caller's actor domain and returns
`Promise<T>`, where `T` is the yielded type. Every reachable path must `yield`.
The runtime owns scheduling policy; programs must not rely on a fresh thread,
thread affinity, or a particular worker.

Values captured from the enclosing scope are copied into the task. A capture
must use an immutable binding and its type must be deeply immutable and safe to
cross a thread boundary. Actor, promise, callback, weak-reference, and stream
handles cannot be captured. Mutable locals and freshly constructed mutable
graphs are allowed inside the task.

Async-block code is isolated. It may call only transitively isolated functions,
methods, constructors, and native contracts, and cannot access mutable
module/static state.

An async block may yield an owned mutable object or collection. Its worker has
no persistent mutable domain after completion, so ownership transfers to the
promise consumer. Actor, promise, callback, weak-reference, and stream handles
cannot occur recursively in the yielded graph.

Nested async blocks and async calls on actors created inside the block are
allowed. Handles from those operations must be consumed before yielding the
outer result.

`async functionCall(args)` schedules an ordinary function call when the
function is inferred isolated. Arguments must satisfy the same boundary rules
as actor-call arguments, and the result must be transferable from a temporary
worker domain:

```doof
promise := async compute(input)
```

The direct form is rejected when `compute` reaches mutable module/static state
or other non-isolated code. Use an async block when the worker needs local
setup, multiple operations, or an owned mutable intermediate graph.

### Runtime scheduling

Async blocks and eligible actor messages enter a process-wide FIFO scheduler.
Pending work is unbounded, while CPU execution is bounded by a runtime CPU-token
limit. The default limit is the host's reported hardware concurrency, falling
back to one. The application thread, including a UI thread when present, does
not consume a CPU token.

Actor mailboxes remain FIFO and admit at most one message per actor to the ready
queue. After that message completes, the next accepted message becomes
eligible. A worker retains one job until completion even if the job temporarily
relinquishes its CPU token while blocked.

`Promise.get()`, synchronous actor calls, and actor retirement waits
automatically relinquish a worker's token until the wait completes. This allows
nested async or actor work to progress even when all CPU tokens were occupied.
Native C++ integrations may use `doof::CpuTokenRelease` around their own
blocking operations and may call `reacquire()` before the release object's
scope ends. This interface is native-only and does not add a Doof scheduling
primitive.

Blocked workers do not count against the CPU limit. The scheduler may create
compensating worker threads when ready work and a free token exist, so the total
number of blocked OS threads is not hard-capped. Excess idle workers retire;
the default retained count equals the CPU-token limit and the default excess
idle timeout is 30 seconds.

Native hosts may call `doof::configure_runtime_scheduler` with
`doof::RuntimeSchedulerOptions` before the first scheduled job. Configuration
after scheduling begins is a runtime logic error. The maximum must be at least
one, the retained count cannot exceed it, and the idle timeout cannot be
negative.

---

## Actor Boundaries

Actor methods are actor boundaries. Values crossing an actor boundary must not
create shared mutable state.

Allowed:

- primitives;
- deeply immutable objects and collections.

Rejected:

- mutable objects and collections;
- `Actor<T>` references;
- `Promise<T>` values.

Actor references may be copied within the domain that owns them. They may not be
passed into another actor method.

Actor construction is also a boundary. Every explicit `Actor<T>(...)`
constructor argument must be boundary-safe. Mutable arguments are rejected even
when the caller will not reassign its binding, because Doof does not currently
have uniqueness or move types that could prove ownership transfer.

For interface-typed values, boundary safety must hold for every known concrete
implementation. A readonly interface field must be implemented by a readonly
class field, so widening cannot hide mutable storage at the boundary.

Omitted field defaults and static constructor factories used by actor creation
must be isolated. They may construct fresh mutable actor state, but they must not
capture mutable module or static state into the new domain.

---

## Retirement

`retire actor` stops an actor and returns its inner state:

```doof
job := Actor<Job>()
state: Job := retire job
```

The type transformation is:

```text
Actor<T> -> T
```

Retirement is queue ordered:

```doof
p := async job.run()
state := retire job
```

The actor observes:

```text
run
retire
```

Retirement behavior:

1. A retirement request is enqueued.
2. The actor enters the retiring state and stops accepting new calls.
3. Already queued calls continue in order.
4. When the retirement request is reached, the actor stops.
5. The actor's inner `T` is returned to the retiring domain.
6. Calls through aliases after retirement has been requested are logic errors
   and panic at runtime.

Failures from earlier async actor calls belong to their `Promise<T>` handles.
`retire` returns `T` and does not aggregate or rethrow earlier promise failures.

Actor references inside retired state remain live actor domains. Retirement moves
ordinary state, not actor domains.

There is no public `actor.stop()` lifecycle method. If an actor's inner class
defines a method named `stop`, `actor.stop()` is an ordinary actor method call,
not a lifecycle operation. Use `retire actor` to stop an actor domain.

---

## Promises

Promises represent asynchronous actor-call, isolated-function-call, or
async-block completion:

```doof
class Promise<T> {
    function get(): Result<T, string>
}
```

`get()` blocks until the queued actor method completes. On a runtime worker the
wait relinquishes its CPU token; application and other non-worker threads are
unaffected. Runtime failures are reported as `Failure<string>`.

A mutable array of promises can consume whichever operation completes first:

```doof
result: Result<T, string> := pending.takeFirstCompleted()
```

`takeFirstCompleted()` blocks until one promise settles, removes that promise
from `pending`, and returns the same result that its `get()` method would
produce. Calling it on an empty array returns `Failure<string>`. Completion
waiting does not poll and relinquishes a runtime-worker CPU token in the same
way as `get()`.

---

## Actor-Affine Callbacks

Function values are actor-affine callbacks. A callback belongs to the actor
domain in which it was created. Normal call syntax:

```doof
callback(args)
```

lowers to a checked local callback call. The explicit spelling is:

```doof
callback.call(args)
```

Local callback calls execute immediately and are valid only in the owning actor
domain. Calling a callback from another actor domain is a runtime logic error.

Callbacks can also be posted back to their owning actor domain:

```doof
promise := callback.post(args)
```

`post` enqueues the callback invocation on the owning actor and returns
`Promise<R>`, where `R` is the callback return type. A posted callback does not
run on the caller's stack. A callback created in the root application domain is
posted to the root mailbox. The host or generated entrypoint decides which
thread drains that mailbox, so UI runtimes can preserve strict thread affinity.

Function-typed parameters in native imports also lower to `doof::callback`; the
compiler does not assume whether bodiless C++ will call locally, store, or
schedule the callback.

Actor-affine callback values may cross actor method boundaries. Their parameter
and return payload types are still validated with the actor boundary rules,
because posted callback arguments and results cross actor domains.

---

## Isolated Functions

Isolation is an inferred transitive effect. A function or method is isolated
when it does not access mutable module/static state and calls only isolated
code. Mutation through `this`, parameters, locals, and freshly created values is
allowed because those references already belong to the current domain.

`isolated` is an enforced promise:

```doof
shared := [0]

isolated function invalid(): none {
    shared.push(1) // error: accesses mutable module state
}
```

Ordinary functions without the modifier are still inferred isolated when their
bodies satisfy the rules. Recursive call groups are isolated when no member
accesses mutable global state or reaches a non-isolated callee. Bodyless/native
functions must explicitly declare `isolated` to provide that contract. Native
free functions use `import isolated function name(...): Type from "header"`;
native class methods place `isolated` before `static` or the method name.

An ordinary class method may be non-isolated for local use. Calling a method
through `Actor<T>` requires its inferred effect to be isolated and is rejected
otherwise. This prevents actor code from reaching root-domain mutable globals
either directly or through helper calls.

`isolated` does not schedule work by itself. Use an async block to execute
isolated work outside the current actor domain.

---

## Summary

- Actors are persistent serial mutable domains scheduled on shared workers;
  async blocks are temporary isolated execution domains.
- Actor construction and actor method calls enforce domain boundaries.
- Actor-dispatched methods cannot reach mutable module/static state.
- Actor calls are synchronous unless marked `async`.
- `async` supports actor calls, isolated function calls, and value-producing
  isolated blocks.
- Runtime CPU execution is bounded; pending work and blocked workers are not
  hard-capped.
- `retire actor` drains accepted work and returns the actor state.
- Immutable values may cross domains.
- Mutable state crosses domains only by retiring its owning actor.
