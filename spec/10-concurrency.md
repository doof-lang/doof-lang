# Concurrency

## Overview

Doof's concurrency model is built around actor-owned mutable domains.

An `Actor<T>` is a concurrent domain containing one mutable `T`. The main thread
is the implicit root actor domain. Mutable state belongs to exactly one actor
domain at a time. Immutable values may be shared freely across actor domains,
as may actor and promise handles, which are synchronized by the runtime.

Cross-domain mutable interaction happens only through actor method calls.
Fields of the wrapped class cannot be read or written directly through an
`Actor<T>` handle, including readonly fields and fields containing callbacks.
Use an actor method to read or update state. A method accesses its own fields
normally through `this`; after `retire` returns the inner `T`, its fields are
ordinary local state again.

---

## Actors

Actors wrap classes:

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
counter.increment(1)
```

Each actor processes method calls sequentially. An actor is a serial execution
domain, not a thread identity: consecutive messages may execute on different
runtime worker threads, but messages for one actor never overlap.

---

## Actor Calls

Actor calls are synchronous by default:

```doof check
class Counter {
    let value: int
    increment(n: int): none { this.value = this.value + n }
    get(): int => this.value
}

counter := Actor<Counter>(0)
counter.increment(5)
n := counter.get()
```

The caller blocks until the actor method completes.

Actor calls may be asynchronous:

```doof check
class Counter {
    let value: int
    increment(n: int): none { this.value = this.value + n }
    get(): int => this.value
}

counter := Actor<Counter>(0)
p := async counter.increment(10)
p.get()!
```

`async actor.method(args)` returns `Promise<T>`, where `T` is the actor method's
return type.

The receiver and argument expressions of a synchronous or `async` actor call
are evaluated in the caller's domain, left to right, before the message is
queued. Only their values cross the boundary, so `counter.increment(counter.get())`
is two consecutive messages rather than a call from inside the actor. Omitted
parameters take their defaults when the message runs, as in a local call on the
actor's state.

`async` is also valid with a value-producing block:

```doof check body
input := 21
promise := async {
    let values = [input * 2]
    values.push(43)
    yield values
}
values := promise.get()!
```

`async { ... }` executes outside the caller's actor domain and returns
`Promise<T>`, where `T` is the yielded type. Every reachable path must `yield`.
The runtime owns scheduling policy; programs must not rely on a fresh thread,
thread affinity, or a particular worker.

Values captured from the enclosing scope are copied into the task. A capture
must use an immutable binding and its type must be deeply immutable and safe to
cross a thread boundary. Actor and promise handles may be captured; callback,
weak-reference, and stream handles cannot. Mutable locals and freshly constructed mutable
graphs are allowed inside the task.

Async-block code is isolated. It may call only transitively isolated functions,
methods, constructors, and native contracts, and cannot access mutable
module/static state.

An async block may yield an owned mutable object or collection. Its worker has
no persistent mutable domain after completion, so ownership transfers to the
promise consumer. Callback, weak-reference, and stream handles cannot occur
recursively in the yielded graph; actor and promise handles may.

Nested async blocks and actor calls are allowed inside the block, including
calls through captured actor handles.

`async functionCall(args)` schedules an ordinary function call when the
function is inferred isolated. Arguments must satisfy the same boundary rules
as actor-call arguments, and the result must be transferable from a temporary
worker domain:

```doof check
function compute(n: int): int => n * 2

input := 21
promise := async compute(input)
println(promise.get()!)  // 42
```

As with actor calls, the receiver and argument expressions are evaluated in the
caller's domain before the call is submitted; only `compute` itself runs on the
worker.

The direct form is rejected when `compute` reaches mutable module/static state
or other non-isolated code. Use an async block when the worker needs local
setup, multiple operations, or an owned mutable intermediate graph.

### Runtime scheduling

Async blocks and eligible actor messages enter a process-wide FIFO scheduler.
CPU execution is bounded by a runtime CPU-token limit; accepted actor messages
and pending async submissions are bounded as described under
[Queue capacity](#queue-capacity). The default limit is the host's reported hardware concurrency, falling
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
one, the retained count cannot exceed it, the idle timeout cannot be
negative, and both queue capacities must be at least one.

### Queue capacity

Actor mailboxes and pending async submissions are bounded. Once an actor holds
its capacity of accepted calls and posts, a synchronous call, `async` actor
call, or `callback.post` to that actor blocks until the actor dequeues a
message. Once the process-wide count of async blocks and isolated calls that
were submitted but have not started reaches its capacity, the submitter blocks
until one starts. Both waits relinquish a runtime worker's CPU token. An `async`
expression can therefore block its caller while the destination is full.

Deliveries for accepted `onComplete` registrations and retirement requests are
never blocked by capacity. The application mailbox is not bounded.

Each capacity defaults to 65,536. Native hosts may change them through the
`actor_mailbox_capacity` and `async_queue_capacity` fields of
`doof::RuntimeSchedulerOptions`.

### Deadlock detection

Each actor, the application thread, and each running async block is a serial
domain. While a domain blocks in a synchronous actor call, an actor retirement,
a wait for actor mailbox capacity, or a `Promise.get()`, the runtime records that
it waits on the producing domain: the actor, the async block, or the posted
callback's owning domain. A wait that would close a cycle of waiting domains can
never complete. The waiter that would close the cycle panics instead of hanging,
and the message names the chain of waits:

```text
deadlock: blocking wait would never complete (synchronous actor call -> synchronous actor call)
```

Cycles include an actor calling itself synchronously through its own handle,
two actors calling each other synchronously, an actor retiring itself, and an
actor sending to its own full mailbox. The panic is an ordinary Doof panic, and
the other domains in the cycle continue with their queued work.

Detection is a safety net rather than a liveness guarantee. It does not cover
livelock, waits on several promises through `takeFirstCompleted()`, the async
submission queue, or native blocking outside runtime waits.

---

## Actor Boundaries

Actor methods are actor boundaries. Values crossing an actor boundary must not
create shared mutable state.

Allowed:

- primitives;
- deeply immutable objects and collections;
- `Actor<T>` handles;
- `Promise<T>` values;
- actor-affine callbacks whose parameter and return types are allowed.

Rejected:

- mutable objects and collections;
- streams.

Actor and promise handles are synchronized runtime handles, so sharing them
does not share mutable state: actor state stays behind its mailbox, and a
promise result still has exactly one consumer. Readonly fields and bindings may
hold them, and immutable messages can carry them:

```doof check
class Sink {
    let total: int = 0
    add(amount: int): none { this.total += amount }
    read(): int => this.total
}

class Envelope {
    readonly sink: Actor<Sink>
    readonly amount: int
}

class Relay {
    forward(envelope: Envelope): none { envelope.sink.add(envelope.amount) }
}

sink := Actor<Sink>()
relay := Actor<Relay>()
relay.forward(Envelope { sink, amount: 2 })
task := async {
    sink.add(1)
    yield none
}
task.get()!
println(sink.read())  // 3
```

Sharing a handle shares its lifecycle. Any holder of an actor handle may call
or `retire` it; after retirement has been requested, a second retirement or a
call through any handle panics. Any holder of a promise may consume it; the
first claim wins and later claims panic with `promise result already claimed`.

Actor construction is also a boundary. Every explicit `Actor<T>(...)`
constructor argument must be boundary-safe. Mutable arguments are rejected even
when the caller will not reassign its binding, because Doof does not currently
have uniqueness or move types that could prove ownership transfer.

For interface-typed values, boundary safety must hold for every known concrete
implementation. A readonly interface field must be implemented by a readonly
class field, so widening cannot hide mutable storage at the boundary.

A widened value no longer records its implementation's type arguments. An
implementation type parameter forwarded to the interface (`class Box<T>
implements Holder<T>`) takes the interface's argument; any other implementation
type parameter is unbound and is safe only when its constraint is
boundary-safe. An unconstrained parameter may stand for a mutable graph, so a
field typed by it makes the interface unsafe:

```doof reject
interface Holder {
    describe(): string
}

class Generic<T> implements Holder {
    readonly payload: T
    describe(): string => "generic"
}

class Worker {
    take(holder: Holder): none { }
}

worker := Actor<Worker>()
worker.take(Generic<int> { payload: 1 })  // ❌ Holder may hide Generic<int[]>
```

The same rule applies to async captures and results, where an unbound parameter
may also hide a callback, weak reference, or stream.

Omitted field defaults and static constructor factories used by actor creation
must be isolated. They may construct fresh mutable actor state, but they must not
capture mutable module or static state into the new domain.

---

## Retirement

`retire actor` stops an actor and returns its inner state:

```doof check
class Job {
    let runs: int = 0
    run(): none { this.runs += 1 }
}

job := Actor<Job>()
state: Job := retire job
println(state.runs)  // 0
```

The type transformation is:

```text
Actor<T> -> T
```

Retirement is queue ordered:

```doof check
class Job {
    let runs: int = 0
    run(): none { this.runs += 1 }
}

job := Actor<Job>()
p := async job.run()
state := retire job
println(state.runs)  // 1
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
4. Completions registered to this actor before the request are also drained;
   retirement waits for their producers and queued callbacks before stopping.
5. The actor's inner `T` is returned to the retiring domain.
6. Calls through any handle, in any domain, after retirement has been
   requested are logic errors and panic at runtime. Senders blocked on mailbox
   capacity are released with the same panic.

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
    get(): Result<T, string>
    onComplete(callback: (result: Result<T, string>) => none): none
}
```

`get()` blocks until the queued actor method completes. On a runtime worker the
wait relinquishes its CPU token; application and other non-worker threads are
unaffected. Native runtime exceptions are reported as `Failure<string>`; Doof
panics remain panics.

A promise has exactly one consumer across all copies and aliases, including
copies held by other domains. Calling
`get()` claims the result before waiting. Calling `onComplete()` claims it when
the callback is registered. A second `get()` or valid `onComplete()` registration
panics with `promise result already claimed`.
This rule also applies to promises of `none` and failed operations. Dropping an
unconsumed promise does not cancel the operation.

### Completion callbacks

`onComplete` registers terminal delivery and returns immediately:

```doof check
promise := async { yield [1, 2, 3] }
promise.onComplete((result) => {
    values := result else error { println(error); return }
    values.push(4)
    println(values.length)
})
```

The callback receives `Result<T, string>` and returns `none`; `onComplete`
returns `none`, with no successor promise. If `T` is itself a `Result`, the
outer result is preserved rather than flattened. `Promise<none>` delivers
`Success()` or `Failure<string>` through the same callback shape.

Delivery is always queued on the callback's owning actor domain, including when
the promise has already settled or registration occurs in that domain. It never
runs inline on the registering or completing stack. The callback runs after the
current message in its domain finishes. Registration and completion may race;
an accepted callback is queued exactly once. Queue ordering follows enqueue
order, not registration order among different promises.

An owned mutable async result transfers to the callback domain as its sole
receiver. This is a dedicated promise transfer, not a relaxation of ordinary
callback-post or actor-call payload restrictions.

Registration retains the destination actor until delivery completes. An actor
that is already retiring or retired rejects registration; rejection leaves an
otherwise unclaimed promise available. Retirement waits for registrations
already accepted, then transfers the actor state. As with other blocking actor
operations, callers must avoid dependency cycles (for example, blocking a
domain that a reserved completion needs to make progress).

Root callbacks execute through the application mailbox. Generated native
command-line entrypoints pump that mailbox after normal `main` or script
completion until every registered completion has been delivered, preserving
the integer exit code. Other keep-alive sources, such as event channels and
timers, do not hold the process open after `main`; they still require an
explicit event loop. Application/UI hosts retain responsibility for pumping
their mailbox. Callbacks created inside isolated async work belong to a
temporary domain and cannot be registered for deferred completion; create the
callback in the receiving actor or root domain instead.

An operation's Doof panic remains a panic rather than being delivered as a
`Failure`. Because terminal delivery has no successor promise, an unhandled
producer panic or callback panic is reported through `unhandled_panic` in the
destination domain and terminates the process. Use explicit Results for
recoverable failures; a callback can use `catchPanic` locally when appropriate.

### Completion-order waiting

A mutable array of promises can consume whichever operation completes first:

```doof check
pending: Promise<int>[] := [async { yield 1 }, async { yield 2 }]
result: Result<int, string> := pending.takeFirstCompleted()
println(pending.length)  // 1
```

`takeFirstCompleted()` blocks until one promise settles, removes that promise
from `pending`, and returns the same result that its `get()` method would
produce. Calling it on an empty array returns `Failure<string>`. Completion
waiting does not poll and relinquishes a runtime-worker CPU token in the same
way as `get()`.

The selected promise is consumed across all aliases. Arrays containing a
promise already claimed through another alias cause a logic-error panic when
that entry is inspected; do not mix registered completions into a pending array.

---

## Actor-Affine Callbacks

Function values are actor-affine callbacks. A callback belongs to the actor
domain in which it was created. Normal call syntax:

```doof check
callback := (n: int): int => n + 1
println(callback(1))
```

lowers to a checked local callback call. The explicit spelling is:

```doof check
callback := (n: int): int => n + 1
println(callback.call(1))
```

Local callback calls execute immediately and are valid only in the owning actor
domain. Calling a callback from another actor domain is a runtime logic error.

Callbacks can also be posted back to their owning actor domain:

```doof check
callback := (n: int): int => n + 1
promise := callback.post(1)
promise.onComplete((result) => println(result!))
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

A callback's captures stay in its owning domain. A crossing callback may
capture mutable objects, because another domain can hold, pass on, or `post`
it, but never run it. The runtime also releases closure state on its owner:
when the last copy of a callback is dropped in another domain, releasing its
captures is queued back to the owning domain, so captured destructors run
where the captures were created:

```doof check
let counter: int[] = []

class Tracked {
    let uses: int = 0
    destructor { counter.push(this.uses) }
}

class Registry {
    let saved: ((): int) | none = none
    keep(listener: (): int): none { this.saved = listener }
    clear(): none { this.saved = none }
}

registry := Actor<Registry>()
tracked := Tracked {}
registry.keep((): int => tracked.uses)  // ✅ OK - the capture stays in the root domain
registry.clear()  // the Tracked destructor still runs on the root domain
```

Releases owned by the root domain run whenever the application mailbox is
pumped, before any queued callback. Native command-line entrypoints run the
remaining releases once more after `main` returns. Root-owned closure state
dropped after that point is never released. A retiring or retired actor runs no
more work, so closure state it owns is released by the domain that drops it.
That is safe, because objects created in an actor domain have isolated
destructors. Callbacks created in isolated async work have no owning domain and
are released in place.

---

## Isolated Functions

Isolation is an inferred transitive effect. A function or method is isolated
when it does not access mutable module/static state and calls only isolated
code. Mutation through `this`, parameters, locals, and freshly created values is
allowed because those references already belong to the current domain.

`isolated` is an enforced promise:

```doof reject
shared := [0]

isolated function invalid(): none {
    shared.push(1) // ❌ accesses mutable module state
}
```

Ordinary functions without the modifier are still inferred isolated when their
bodies satisfy the rules. Recursive call groups are isolated when no member
accesses mutable global state or reaches a non-isolated callee. Bodyless/native
functions must explicitly declare `isolated` to provide that contract. Native
free functions use `import isolated function name(...): Type from "header"`;
native class methods place `isolated` before `static` or the method name.

The call graph includes every method a call may reach. A call through a union
receiver reaches each member's method, and a call through an interface or a
constrained type parameter reaches every known implementation. Constructing a
class, whether by `T { ... }`, `T(...)`, a contextual object or positional
literal, or `Actor<T>(...)`, runs its static `constructor` factory or the field
defaults it omits, so those count as calls made by the constructing code:

```doof reject
let counter: int[] = []

class Touches {
    touch(): none { counter.push(1) }
}

class Quiet {
    touch(): none { }
}

class Thing {
    n: int = counter.length
}

isolated function poke(target: Touches | Quiet): none {
    target.touch()  // ❌ Touches.touch accesses mutable module state
}

isolated function make(): int => Thing {}.n  // ❌ the omitted default reads counter
isolated function given(): int => Thing { n: 1 }.n  // ✅ OK - no default runs
```

A `destructor` runs in the domain that drops the object's last reference.
Objects stay in the domain that creates them unless they cross a boundary, so
constructing a class also counts its destructor as a call made by the
constructing code. `T.fromSerialValue(...)` counts as constructing every class
the decoded value can hold: it evaluates their omitted field defaults and commits
to their destructors.

A value that crosses into another domain may be released there instead. Every
class an actor method argument, `Actor<T>(...)` argument, `async` call argument,
or async block capture can own, through its fields, containers, unions, and
interface implementations, must therefore have an isolated destructor. The
error is reported where the value crosses. Callback captures are exempt,
because the runtime releases closure state on its owning domain (see
[Actor-Affine Callbacks](#actor-affine-callbacks)). Code that keeps such objects
in the root domain may still use destructors that touch module state:

```doof reject
let counter: int[] = []

class Tracked {
    let uses: int = 0
    destructor { counter.push(this.uses) }
}

class Token {
    id: int
    destructor { counter.push(this.id) }
}

class Worker {
    hold(token: Token): int => token.id
}

isolated function track(): none {
    tracked := Tracked {} // ❌ releasing it runs the destructor here
}

function trackLocally(): none {
    tracked := Tracked {} // ✅ OK - root-domain code may touch counter
}

function send(worker: Actor<Worker>): int {
    return worker.hold(Token { id: 1 }) // ❌ the actor may release the Token
}
```

A `for` loop over a class stream calls the iterable's `next()` and `value()`
methods. A `Stream<T>` value may hold an instance of any class convertible to
`Stream<T>`, so iterating it, or calling `next()` or `value()` on it, reaches
those methods of every such class:

```doof reject
let counter: int[] = []

class Counter implements Stream<int> {
    let current: int

    next(): bool {
        counter.push(this.current) // reached by both loops below
        this.current = this.current + 1
        return this.current < 3
    }

    value(): int => this.current
}

isolated function direct(): none {
    for value of Counter(0) { } // ❌ calls Counter.next
}

isolated function converted(values: Stream<int>): none {
    for value of values { } // ❌ values may be a Counter
}
```

Source class methods use the same modifier order without a `function` keyword:
`isolated run(): none` and `isolated static create(): Worker`. The modifier is
valid on both instance and static methods.

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
- Runtime CPU execution is bounded; blocked workers are not hard-capped.
- Actor mailboxes and pending async submissions are bounded; a full
  destination blocks the sender.
- Blocking-wait cycles panic as deadlocks instead of hanging.
- `retire actor` drains accepted work and returns the actor state.
- Immutable values and actor and promise handles may cross domains.
- Mutable state transfers through actor retirement or a single-consumer owned
  async result, including delivery through `onComplete`.
