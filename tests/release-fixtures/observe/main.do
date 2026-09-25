import { info, LogEntry, Logger, setLogger } from "std/log"
import { Duration, Thread } from "std/time"

class Thing { }

class CountingLogger implements Logger {
  log(entry: LogEntry): none { metricsIncrement("application_log_sink_total", 1L) }
}

function main(args: string[]): int {
  thing := Thing {}
  info("tap without application sink")
  setLogger(CountingLogger {})
  info("<script>alert('observer')</script>", { "request": 7 })
  metricsIncrement("requests_total", 3L)
  if args.contains("--exit") { return 23 }
  if args.contains("--stream") {
    println("OBSERVE_STREAM_FIRST_READY")
    Thread.sleep(Duration.ofSeconds(2L))
    for index of 0..<8 {
      info("stream event " + string(index))
      metricsIncrement("requests_total", 1L)
    }
    println("OBSERVE_STREAM_BURST_READY")
    Thread.sleep(Duration.ofSeconds(5L))
    return 0
  }
  Thread.sleep(Duration.ofSeconds(30L))
  return 0
}
