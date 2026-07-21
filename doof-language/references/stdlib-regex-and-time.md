# `std/regex` and `std/time`

## `std/regex`

```doof
import { Regex, Match, RegexFlag, RegexError } from "std/regex"
```

PCRE2 patterns are compiled once with `Regex.compile(pattern, flags = [])` and
reused through `test`, `find`, `findAll`, `replaceFirst`, and `replaceAll`.
Flags are `.IgnoreCase`, `.Multiline`, `.DotAll`, and `.Extended`.

`Match.value` is the full match; `range` contains byte offsets. `captures` and
`captureRanges` start with capture group 1. `capture(name)` and
`captureRange(name)` return named captures or `none`. Replacements support
`$1`-style backreferences. Compile failures return `RegexError` with stage,
pattern, flags, and the native diagnostic.

## `std/time`

```doof
import {
  Duration, Instant, Thread, Stopwatch, StopwatchSpan,
  Date, Time, DateTime, TimeZone, ZonedDateTime, DayOfWeek, Month,
} from "std/time"
```

- `Duration` is a signed nanosecond duration with unit factories, arithmetic,
  comparison, ISO-8601 parsing/formatting, and unit conversion.
- `Instant` is a UTC nanosecond timestamp with `now`, epoch conversion,
  RFC-3339 and HTTP-date parsing/formatting, duration arithmetic, and calendar
  conversion.
- `Thread.sleep(duration)` blocks the current OS thread; zero/negative values
  return immediately.
- `Stopwatch.measure(name)` creates an auto-finishing `with` span or a manual
  span. Query `count`, `total`, `mean`, `min`, `max`, `p95`, or `summary`.
- `Date`, `Time`, and `DateTime` model timezone-free calendar values. Month/year
  date arithmetic clamps invalid days; time arithmetic wraps within 24 hours.
- `TimeZone.lookup(id)`, `.local()`, and `.UTC` use IANA zones. Offset and DST
  queries accept an `Instant`.
- `ZonedDateTime.withZoneSameInstant` preserves the moment;
  `withZoneSameLocal` preserves wall-clock fields.

Parsing and checked construction return `Result<..., string>`. `DayOfWeek` is
Monday-first (`1..7`); `Month` runs January through December.

```doof
started := Instant.now()
Thread.sleep(Duration.ofMillis(10L))
elapsed := started.durationUntil(Instant.now())
println(elapsed.toISOString())
```
