import { Assert } from "std/assert"
import { DebugLaunch } from "../../src/debug-command"
import { DebugSession } from "./session"
import { SourceBreakpoint } from "./model"

function session(): DebugSession {
  return DebugSession { launch: DebugLaunch { executable: "/tmp/app", source: "/tmp/main.do", directory: "/tmp", symbols: "/tmp/app.dSYM" } }
}

export function testSessionBreakpointsToggleBeforeLaunch(): none {
  s := session()
  s.toggleBreakpoint("/tmp/main.do", 4)
  Assert.equal((try! s.breakpoints.get("/tmp/main.do")).length, 1)
  s.toggleBreakpoint("/tmp/main.do", 4)
  Assert.equal((try! s.breakpoints.get("/tmp/main.do")).length, 0)
  s.toggleBreakpoint("/tmp/main.do", 0)
  Assert.equal((try! s.breakpoints.get("/tmp/main.do")).length, 0)
}

export function testSessionBreakpointsToggleDisplayedLine(): none {
  s := session()
  path := "/tmp/main.do"
  otherPath := "/tmp/other.do"
  // Several requested lines can resolve to the same visible marker.
  s.breakpoints.set(path, [
    SourceBreakpoint { line: 4, actualLine: 6, verified: true },
    SourceBreakpoint { line: 5, actualLine: 6, verified: true },
    SourceBreakpoint { line: 9 },
  ])
  s.breakpoints.set(otherPath, [SourceBreakpoint { line: 6 }])
  s.toggleBreakpoint(path, 6)
  remaining := try! s.breakpoints.get(path)
  Assert.equal(remaining.length, 1)
  Assert.equal(remaining[0].line, 9)
  Assert.equal((try! s.breakpoints.get(otherPath)).length, 1)

  // An unmarked requested line adds a new point, retaining its relocated peer.
  s.breakpoints.set(path, [SourceBreakpoint { line: 4, actualLine: 6, verified: true }])
  s.toggleBreakpoint(path, 4)
  Assert.equal((try! s.breakpoints.get(path)).length, 2)
  s.toggleBreakpoint(path, 4)
  Assert.equal((try! s.breakpoints.get(path)).length, 1)
  Assert.equal((try! s.breakpoints.get(path))[0].actualLine, 6)

  // Unverified or missing resolved locations render at the requested line.
  s.breakpoints.set(path, [
    SourceBreakpoint { line: 4, actualLine: 6, verified: false },
    SourceBreakpoint { line: 8, actualLine: 0, verified: true },
  ])
  s.toggleBreakpoint(path, 4)
  Assert.equal((try! s.breakpoints.get(path)).length, 1)
  s.toggleBreakpoint(path, 8)
  Assert.equal((try! s.breakpoints.get(path)).length, 0)
}

export function testSessionContinuedInvalidatesStoppedState(): none {
  s := session()
  s.state = "Stopped"
  s.sourceLine = 4
  previous := s.epoch
  s.receive({ "type": "event", event: "continued", body: {} })
  Assert.equal(s.state, "Running")
  Assert.equal(s.epoch, previous + 1)
  Assert.equal(s.sourceLine, 0)
  s.receive({ "type": "event", event: "exited", body: { exitCode: 7 } })
  Assert.equal(s.exitCode, 7)
  Assert.equal(s.state, "Exited")
}

export function testSessionMissingAdapterHasActionableFailure(): none {
  s := session()
  s.start("/this/path/does/not/exist", [])
  Assert.equal(s.state, "Failed")
  Assert.stringContains(s.status, "LLDB-DAP")
  s.shutdown()
}

export function testSessionOutputIsBounded(): none {
  s := session()
  let text = "abcd"
  for i of 0..<17 { text += text }
  s.appendOutput(text)
  Assert.equal(s.output.length < 262144, true)
  Assert.stringContains(s.output, "truncated")
}
