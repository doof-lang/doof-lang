# Doof Concurrency Reference

## Overview

Doof concurrency is actor-owned. An `Actor<T>` is a concurrent mutable domain
containing one mutable `T`. The main thread is the implicit root actor domain.

Core rules:

- Mutable state belongs to exactly one actor domain at a time.
- Immutable values may cross actor boundaries freely, and so may `Actor<T>` and
  `Promise<T>` handles, which the runtime synchronizes.
- Cross-domain mutable interaction happens through actor method calls. Direct field reads/writes through `Actor<T>` are rejected, including readonly and callback fields; use a method. Fields on the inner state returned by `retire` are accessible normally.
- Actor method calls are synchronous by default.
- The receiver and arguments of an actor call or `async` call are evaluated in
  the caller's domain before the work is queued; omitted parameters take their
  defaults on the callee side.
- `async` supports actor method calls and isolated value-producing blocks.
- `retire actor` drains accepted work, stops the actor, and returns the inner
  state.

## Actors

```doof check
class Counter {
    let value: int

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

```doof check
class Counter {
    let value: int
    increment(n: int): int { value += n; return value }
}

worker := Actor<Counter>(0)
p := async worker.increment(10)
p.get()!
```

Ordinary functions may be dispatched directly when they are inferred isolated
and their arguments satisfy actor-call boundary rules. Like async-block
captures, the receiver and arguments cannot contain weak-reference or stream
handles:

```doof check
isolated function compute(input: int): int => input * 2

function main(): none {
    promise := async compute(21)
}
```

## Async Blocks

An async block runs outside the caller's actor domain and yields its result
through `Promise<T>`:

```doof check body
base := 20
promise := async {
    let values = [base + 1]
    values.push(22)
    yield values
}
values := promise.get()!
```

Every reachable path must `yield`. Captures are copied and must come from
immutable bindings with deeply immutable, thread-safe types. Mutable locals and
fresh mutable values are allowed inside the block. The yielded graph may be
mutable because the temporary worker domain ends before the caller receives
it.

Actor and promise handles may be captured and yielded. Callbacks may be
captured but not yielded; a captured callback stays affine to its creator, so
the block may `post`, `tryPost`, or `dispatch` it back but a direct call panics
at runtime. Weak-reference and stream handles cannot be captured or occur
recursively in the yielded graph. Async-block code may invoke only transitively isolated code
and cannot access mutable module/static state.

Nested async blocks and actor calls, including calls through captured actor
handles, are allowed. Worker identity and timing are deliberately unspecified.

The runtime uses a process-wide FIFO scheduler. CPU execution is limited to the
host hardware-concurrency count by default (falling back to one). The
application/UI thread is outside this token limit. One actor message at a time
is eligible from each FIFO actor mailbox.

Actor mailboxes and not-yet-started async submissions are bounded (65,536 each
by default). A sender to a full actor blocks, so an `async` actor call or
`callback.post` can block its caller; a submitter blocks while the async queue
is full. `onComplete` deliveries and retirement are never blocked by capacity,
and the application mailbox never blocks senders. `callback.tryPost` never
blocks: it reports `"full"` when the owning actor's mailbox, or the
application mailbox (65,536 queued messages by default), is at capacity.

Blocking waits (synchronous actor calls, retirement, mailbox-capacity waits, and
`Promise.get()`) are tracked between serial domains. A wait that would close a
cycle panics with `deadlock: blocking wait would never complete (...)` instead
of hanging; for example an actor synchronously calling itself, two actors
calling each other synchronously, an actor retiring itself, or an actor
sending to its own full mailbox. The cycle is detected before the call or
retirement is queued, so the panicking request never runs and a self-retiring
actor keeps running with its state. Livelock and `takeFirstCompleted()` waits are not detected.

Worker waits in `Promise.get()`, synchronous actor calls, and actor retirement
automatically relinquish their CPU token. This lets nested work progress at a
one-token limit. Blocking native C++ integrations may use
`doof::CpuTokenRelease`; ordinary Doof code has no token-control API. Blocked
workers can be replaced by compensating threads, so blocked OS-thread count is
not hard-capped. Excess idle workers retire after 30 seconds by default.

Native hosts can configure the CPU limit, retained workers, idle timeout,
`actor_mailbox_capacity`, and `async_queue_capacity` with `doof::RuntimeSchedulerOptions` and
`doof::configure_runtime_scheduler(...)` before the first scheduled job.

`isolated` is an enforced transitive effect. Isolated code cannot access mutable
module/static state or call non-isolated code. It may mutate `this`, parameters,
locals, and freshly created values. Ordinary functions are inferred isolated
when they meet the same rules. The modifier does not create worker-pool
execution by itself; use `async functionCall(args)` or an async block.

Calls through a union receiver reach every member's method, and calls through a
constrained type parameter reach the constraint's implementations. Constructing a
class runs its static `constructor` factory or the field defaults it omits, and
later its `destructor` in the domain that releases it, so those count as calls
made by the constructing code. A `for` loop over a class stream calls its
`next()` and `value()` methods; one over a `Stream<T>` value reaches every class
convertible to that `Stream<T>`. `T.fromSerialValue(...)` counts as constructing
every class the decoded value can hold. A value passed to an actor method,
`Actor<T>(...)`, or an `async` call, or captured by an async block, may be
released in that domain, so every class it can own needs an isolated destructor.
Callback captures are exempt because they are released on the callback's owner.
Root-domain objects that never cross may use destructors that touch module state.

Bodyless native code needs an explicit trusted contract because the compiler
cannot inspect its implementation. Use `import isolated function` for native
free functions and `isolated` on native class methods.

Source class methods omit `function`: use `isolated run(): none` for an
instance method and `isolated static create(): Worker` for a static method.

## Retirement

`retire actor` enqueues a retirement request after already accepted work:

```doof check
class Counter {
    let value: int
    increment(n: int): int { value += n; return value }
}

job := Actor<Counter>(0)
p := async job.increment(10)
p.get()!

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
    get(): Result<T, string>
    onComplete(callback: (result: Result<T, string>): none): none
}
```

`Promise<T>` is produced by async actor calls, isolated function calls, and
async blocks. `get()` blocks until the queued work completes, relinquishing a
runtime worker's CPU token during the wait, and reports thrown runtime failures
as `Result<T, string>`.

Promises have a single consumer across all aliases: choose `get()`,
`onComplete(callback)`, or `takeFirstCompleted()`. The claim happens before
waiting or when registering; reuse panics, even for `none` or failed results.

Use `onComplete` for nonblocking terminal delivery:

```doof check
promise := async { yield [1, 2, 3] }
promise.onComplete((result) => {
    values := result else error { println(error); return }
    values.push(4)
})
```

The callback takes the full `Result<T, string>`, returns `none`, and is always
queued on its creation domain, even for an already completed promise. The
method returns `none`; nested Results are not flattened. Owned mutable async
results transfer to that domain. Registration retains the actor; retirement
drains previously registered completions and rejects new registrations.
Avoid blocking dependency cycles while retiring actors.

Native command-line entrypoints deliver pending completions after normal
main/script completion, preserving the exit code. Timers and other event
sources do not keep the process alive past `main` without an explicit event loop. UI/application hosts pump their own
mailboxes. Callbacks created in temporary isolated async work belong to that
work alone: calling one anywhere else panics, and `post`, `tryPost`,
`tryDispatch`, and `onComplete` registration reject it. Create callbacks that
must outlive the work in a persistent actor or root domain.
Doof panics are not Failure values: an unhandled producer or terminal callback
panic terminates through the runtime's process panic boundary.

A mutable promise array can drive completion-order work:

```doof check
isolated function compute(input: int): int => input * 2
function consume(value: int): none { println(value) }

pending: Promise<int>[] := [async compute(1), async compute(2)]
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
| Streams | Rejected |
| `Actor<T>` | Allowed |
| `Promise<T>` | Allowed |
| Callbacks with allowed payload types | Allowed |

Readonly fields and bindings may hold actor and promise handles, so immutable
messages can carry a reply-to actor. Sharing a handle shares its lifecycle: any
holder may `retire` an actor, after which a second retirement or any call
through any handle panics. Any holder may consume a promise; the first claim
wins and later claims panic with `promise result already claimed`.

`Actor<T>(...)` construction is also a boundary. Explicit constructor arguments
must be boundary-safe, and omitted defaults or constructor factories must be
isolated so they cannot capture mutable module/static state into the new actor.

Interface-typed payloads are safe only when every known concrete implementation
is safe. A readonly interface field must be implemented by a readonly class
field; widening cannot be used to conceal mutable storage.
A widened value forgets its implementation's type arguments, so an
implementation field typed by an unconstrained type parameter (`class G<T>
implements I { readonly payload: T }`) makes `I` unsafe. Bind the parameter
through the interface (`implements I<T>`) or constrain it to a boundary-safe
type. A `readonly` field typed by a type parameter is deeply immutable only for
deeply immutable instantiations: `G<int>` may cross, `G<int[]>` may not.
Every type argument of a crossing class must be boundary-safe even when no field
mentions it, because native code may carry it: a native-backed `Handle<int[]>`
cannot cross, `Handle<readonly int[]>` can. A callback crosses only when every
parameter and its return type are boundary-safe: an actor cannot receive a
`(values: int[]): none` callback to post a mutable array back through it.

Native `import class` objects are opaque and treated as mutable: they cannot
cross actor or async boundaries or sit in readonly fields and bindings. Declare
`import isolated class` only for a synchronized native handle (internally
locked, safe from several domains at once) that never hands a received value to
another domain unless its Doof type is boundary-safe. Otherwise hold the native
object in a plain (non-`readonly`) field.

Calling a method through `Actor<T>` requires that method to be inferred
isolated, including all transitive helper calls.

## Actor-Affine Callbacks

Function values lower to actor-affine callbacks. A callback belongs to the actor
domain where it was created. Normal call syntax invokes the callback locally:

```doof check
function apply(f: (x: int): int, x: int): int => f(x)
```

The explicit local form is:

```doof check
function apply(f: (x: int): int, x: int): int => f.call(x)
```

Local callback calls are checked by the runtime and must execute inside the
owning actor domain. Use `callback.post(args)` to enqueue callback work back
onto the owning actor; it returns `Promise<R>` for callback return type `R`.
Root-domain callbacks post to the root application mailbox. The host decides
which thread drains that mailbox, which preserves UI runtime thread affinity.

`callback.tryPost(args)` is the non-blocking form. It returns
`Result<Promise<R>, string>`: on success the promise behaves like `post`'s;
otherwise nothing is queued and the error is `"full"` (owner mailbox at
capacity) or `"retired"` (owning actor retiring, retired, or gone). Plain
`post` blocks on a full mailbox and panics with `actor is retiring or retired`
for a retired owner. Use `tryPost` for
producers that shed load rather than block:

```doof check
function track(promise: Promise<int>): none {}
function reject(): none {}
function stop(): none {}

callback := (n: int): int => n + 1
case callback.tryPost(1) {
    s: Success -> track(s.value),
    f: Failure -> { if f.error == "full" { reject() } else { stop() } },
}
```

Actor-affine callback values may cross actor method boundaries, but their
parameter and return payload types must also be boundary-safe. Captures may be
mutable: they stay in the owning domain, which is the only one that can run the
callback. When another domain drops the last copy, the runtime queues the
release of its closure state back to the owner, so captured destructors run
there. Root-owned releases run when the application mailbox is pumped, and
once more after native `main` returns. Function-typed
parameters in native imports lower to `doof::callback`; native C++ must choose
local call or posting behavior explicitly instead of receiving an erased
`std::function`.

## Common Pattern: Isolated Background Work

```doof check
isolated function compute(): int => 42

function main(): none {
    promise := async {
        yield compute()
    }
    answer := promise.get()!
}
```

Use a temporary actor instead when the background work needs a persistent
mutable domain or sequential mailbox behavior.

## Common Pattern: Temporary Actor

```doof check
class Computation {
    input: int

    run(): int {
        return this.input * this.input
    }
}

job := Actor<Computation>(42)
p := async job.run()
answer := p.get()!
retire job
```
