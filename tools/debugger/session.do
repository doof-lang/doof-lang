// One UI-independent, launch-owned session. All callbacks run on the host loop.
import { DebugLaunch } from "../../src/debug-command"
import { DebugTransport } from "./transport"
import { DapDecoder, frameMessage, textField, intField, boolField, objectField, arrayField } from "./protocol"
import { panicMessageFromVariables } from "./panic-presentation"
import { stringArrayStorage } from "./collection-presentation"
import { hasDoofSource } from "./frame-presentation"
import { DebugRow, SourceBreakpoint } from "./model"
import { exists } from "std/fs"
import { BlobReader } from "std/blob"
import { Instant, Duration, Thread } from "std/time"

class PendingRequest {
  seq: int
  command: string
  deadline: long
  callback: (body: JsonObject): none
  onError: ((message: string): none) | none = none
}

export class DebugSession {
  launch: DebugLaunch
  let state = "Ready"
  let status = "Ready to launch"
  let panicMessage = ""
  let output = ""
  let threads: DebugRow[] = []
  let frames: DebugRow[] = []
  let scopes: DebugRow[] = []
  let sourcePath = ""
  let sourceLine = 0
  let threadId = 0
  let frameId = 0
  let epoch = 0
  let revision = 0
  let exitCode = 0
  breakpoints: Map<string, SourceBreakpoint[]> = {}
  private let transport: DebugTransport | none = none
  private decoder: DapDecoder = DapDecoder {}
  private let sequence = 0
  private let pending: PendingRequest[] = []
  private let configured = false
  private let ending = false
  private let configurationPending = 0
  private let stoppingAt = 0L
  private let entryBreakpoint: SourceBreakpoint | none = none
  private let seekingEntry = true
  private let loaderStop = false
  private let stopReason = "Stopped"
  private let panicBreakpointId = 0
  private let frameSelectionRevision = 0

  isPanicStop(): bool => state == "Stopped" && stopReason == "Stopped: panic"

  start(command: string = "/usr/bin/xcrun", arguments: string[] = ["lldb-dap"]): none {
    if state != "Ready" { return }
    process := DebugTransport.start(command, arguments) else error { fail(error); return }
    transport = process
    sourcePath = launch.source
    if !breakpoints.has(launch.source) {
      entryBreakpoint = SourceBreakpoint { line: 1 }
    }
    state = "Starting"; status = "Starting LLDB-DAP"; revision += 1
    request("initialize", {
      clientID: "doof-debugger", clientName: "Doof Debugger", adapterID: "lldb",
      pathFormat: "path", linesStartAt1: true, columnsStartAt1: true,
      supportsRunInTerminalRequest: false, supportsVariableType: true,
    }, (body): none => {
      if !boolField(body, "supportsConfigurationDoneRequest") { fail("LLDB-DAP does not support launch configuration"); return }
      let args: JsonValue[] = []
      for argument of launch.arguments { args.push(argument) }
      request("launch", {
        program: launch.executable, cwd: launch.directory, args,
        stopOnEntry: true, disableASLR: false,
      }, (body): none => {})
    })
  }

  request(command: string, arguments: JsonObject, callback: (body: JsonObject): none, onError: ((message: string): none) | none = none): none {
    if transport == none || ending { return }
    sequence += 1
    pending.push(PendingRequest { seq: sequence, command, deadline: Instant.now().toEpochMillis() + 30000L, callback, onError })
    message: JsonObject := { seq: sequence, "type": "request", command, arguments }
    _ := transport!.send(frameMessage(message)) else error { fail(error) }
  }

  tick(): none {
    if transport == none { return }
    process := transport!
    process.flush()
    if stoppingAt > 0L && Instant.now().toEpochMillis() >= stoppingAt {
      process.close(); transport = none; stoppedSession(); return
    }
    // Bound work per UI tick even for a target continuously producing output.
    for i of 0..<4 {
      bytes := process.read(false)
      if bytes.length == 0 { break }
      messages := decoder.feed(bytes) else error { fail(error); return }
      for message of messages { receive(message) }
    }
    stderrBytes := process.read(true)
    if stderrBytes.length > 0 {
      reader := BlobReader(stderrBytes)
      appendOutput("[LLDB] " + reader.readTextLossy(stderrBytes.length))
    }
    if process.error() != "" { fail(process.error()); return }
    if !process.stdoutOpen() {
      _ := decoder.finish() else error { fail(error); return }
      if state != "Exited" && state != "Stopped session" && state != "Failed" && state != "Stopping" { fail("LLDB-DAP closed unexpectedly. Check Xcode and macOS debugging permissions.") }
      process.close(); transport = none; pending = []
      if stoppingAt > 0L { stoppedSession() }
      return
    }
    now := Instant.now().toEpochMillis()
    for item of pending {
      if now > item.deadline { fail("LLDB-DAP timed out during " + item.command); return }
    }
  }

  receive(message: JsonObject): none {
    kind := textField(message, "type")
    if kind == "response" {
      seq := intField(message, "request_seq")
      let found: PendingRequest | none = none
      let remaining: PendingRequest[] = []
      for item of pending { if item.seq == seq { found = item } else { remaining.push(item) } }
      pending = remaining
      item := found as PendingRequest else { return }
      if !boolField(message, "success") {
        error := item.command + ": " + textField(message, "message")
        if item.onError != none { item.onError!(error) }
        else if state == "Starting" { fail(error) }
        else { status = error; appendOutput("[Debugger] " + error + "\n"); revision += 1 }
        return
      }
      item.callback(objectField(message, "body"))
      return
    }
    if kind == "request" {
      if transport != none {
        sequence += 1
        response: JsonObject := { seq: sequence, "type": "response", request_seq: intField(message, "seq"),
          command: textField(message, "command"), success: false, message: "This debugger does not support terminal or reverse requests" }
        _ := transport!.send(frameMessage(response)) else error { fail(error) }
      }
      return
    }
    if kind != "event" { return }
    event := textField(message, "event")
    body := objectField(message, "body")
    if event == "initialized" {
      configurationPending = 2
      request("setFunctionBreakpoints", { breakpoints: [{ name: "doof::panic" }] }, (reply): none => {
        points := arrayField(reply, "breakpoints")
        if points.length != 1 { fail("Invalid panic breakpoint response"); return }
        if points.length > 0 {
          point := points[0] as JsonObject else { fail("Invalid panic breakpoint response"); return }
          panicBreakpointId = intField(point, "id")
          if !boolField(point, "verified") { appendOutput("[Debugger] Panic breakpoint is pending symbol resolution.\n") }
        }
        finishConfiguration()
      }, (message): none => { fail("Could not enable stop on panic: " + message) })
      for path, points of breakpoints { configurationPending += 1; sendBreakpoints(path, true) }
      if entryBreakpoint != none && !breakpoints.has(launch.source) {
        configurationPending += 1; sendBreakpoints(launch.source, true)
      }
      finishConfiguration()
    } else if event == "stopped" {
      panicMessage = ""
      reason := textField(body, "reason")
      description := textField(body, "description")
      loaderStop = seekingEntry && (reason == "entry" || description.contains("SIGSTOP"))
      epoch += 1; state = "Stopped"; status = "Stopped: " + reason
      if description != "" { status += " — " + description }
      for hit of arrayField(body, "hitBreakpointIds") {
        id := hit as long else { continue }
        if panicBreakpointId > 0 && int(id) == panicBreakpointId { status = "Stopped: panic" }
      }
      stopReason = status
      threadId = intField(body, "threadId")
      frames = []; scopes = []; revision += 1
      stopEpoch := epoch
      request("threads", {}, (reply): none => {
        if epoch != stopEpoch || state != "Stopped" { return }
        threads = rows(arrayField(reply, "threads"), "thread")
        if threadId == 0 && threads.length > 0 { threadId = intField(threads[0].data, "id") }
        selectThread(threadId)
        revision += 1
      })
    } else if event == "continued" {
      resumed()
    } else if event == "output" {
      appendOutput(textField(body, "output"))
    } else if event == "exited" {
      exitCode = intField(body, "exitCode")
      exited("Exited with status " + string(exitCode))
    } else if event == "terminated" {
      if state != "Exited" { exited("Session terminated") }
    }
  }

  private finishConfiguration(): none {
    configurationPending -= 1
    if configurationPending != 0 { return }
    configured = true
    request("configurationDone", {}, (reply): none => {})
  }

  toggleBreakpoint(path: string, line: int): none {
    if line < 1 || path == "" { return }
    previous := breakpoints.get(path) else { return setFirstBreakpoint(path, line) }
    let next: SourceBreakpoint[] = []
    let removed = false
    for point of previous {
      // Match the gutter position, including all requests relocated to one line.
      displayedLine := if point.verified && point.actualLine > 0 then point.actualLine else point.line
      if displayedLine == line { removed = true } else { next.push(point) }
    }
    if !removed { next.push(SourceBreakpoint { line }) }
    breakpoints.set(path, next)
    if configured { sendBreakpoints(path, false) }
    revision += 1
  }
  private setFirstBreakpoint(path: string, line: int): none {
    breakpoints.set(path, [SourceBreakpoint { line }])
    if configured { sendBreakpoints(path, false) }
    revision += 1
  }
  private sendBreakpoints(path: string, configuring: bool): none {
    // DAP replaces all breakpoints for a source. Merge the private startup
    // point into each request without exposing it to gutter rendering/toggling.
    let points: SourceBreakpoint[] = []
    users: SourceBreakpoint[] := if breakpoints.has(path) then try! breakpoints.get(path) else []
    for point of users { points.push(point) }
    if path == launch.source && entryBreakpoint != none { points.push(entryBreakpoint!) }
    let values: JsonValue[] = []
    for point of points { values.push({ line: point.line }) }
    request("setBreakpoints", { source: { path }, breakpoints: values }, (body): none => {
      answers := arrayField(body, "breakpoints")
      for index of 0..<points.length {
        if index < answers.length {
          answer := answers[index] as JsonObject else { continue }
          points[index].verified = boolField(answer, "verified")
          points[index].actualLine = intField(answer, "line")
          points[index].message = textField(answer, "message")
        }
      }
      if configuring { finishConfiguration() }
      revision += 1
    }, (message): none => {
      for point of points { point.verified = false; point.message = message }
      if configuring { finishConfiguration() }
      revision += 1
    })
  }

  selectThread(id: int): none {
    if state != "Stopped" || id == 0 { return }
    frameSelectionRevision += 1
    threadId = id; frames = []; scopes = []; frameId = 0; revision += 1
    stopEpoch := epoch
    request("stackTrace", { threadId: id, startFrame: 0, levels: 100 }, (body): none => {
      if epoch != stopEpoch || threadId != id || state != "Stopped" { return }
      frames = rows(arrayField(body, "stackFrames"), "frame")
      if frames.length > 0 {
        panicFrame := textField(frames[0].data, "name").startsWith("doof::panic(")
        if panicFrame {
          status = "Stopped: panic"; stopReason = status
        }
        framePath := textField(objectField(frames[0].data, "source"), "path")
        if seekingEntry && loaderStop && !framePath.endsWith(".do") {
          points: SourceBreakpoint[] := if breakpoints.has(launch.source) then try! breakpoints.get(launch.source) else []
          let hasVerified = entryBreakpoint != none && entryBreakpoint!.verified
          for point of points { if point.verified { hasVerified = true } }
          if hasVerified { loaderStop = false; seekingEntry = false; control("continue"); return }
        }
        let selected = frames[0]
        for frame of frames { if hasDoofSource(frame) { selected = frame; break } }
        selectedFrame := selected
        if panicFrame {
          loadPanicMessage(intField(frames[0].data, "id"), (): none => selectFrame(selectedFrame))
        } else { selectFrame(selectedFrame) }
        if hasDoofSource(selectedFrame) || panicFrame {
          seekingEntry = false
          if entryBreakpoint != none {
            entryBreakpoint = none
            sendBreakpoints(launch.source, false)
          }
        }
      }
      revision += 1
    })
  }
  private loadPanicMessage(runtimeFrame: int, done: (): none): none {
    stopEpoch := epoch
    selection := frameSelectionRevision
    // LLDB's scope references follow its selected frame. Read the runtime msg
    // before requesting caller scopes, or reference 1 may now mean caller locals.
    request("scopes", { frameId: runtimeFrame }, (reply): none => {
      if epoch != stopEpoch || selection != frameSelectionRevision || !isPanicStop() { return }
      for value of arrayField(reply, "scopes") {
        scope := value as JsonObject else { continue }
        if textField(scope, "name") != "Locals" && textField(scope, "presentationHint") != "locals" { continue }
        reference := intField(scope, "variablesReference")
        if reference == 0 { continue }
        request("variables", { variablesReference: reference, start: 0, count: 100 }, (variables): none => {
          if epoch != stopEpoch || selection != frameSelectionRevision || !isPanicStop() { return }
          panicMessage = panicMessageFromVariables(arrayField(variables, "variables"))
          revision += 1
          done()
        }, (message): none => { if epoch == stopEpoch && selection == frameSelectionRevision && isPanicStop() { done() } })
        return
      }
      done()
    }, (message): none => { if epoch == stopEpoch && selection == frameSelectionRevision && isPanicStop() { done() } })
  }

  selectFrame(row: DebugRow): none {
    if state != "Stopped" { return }
    frameSelectionRevision += 1
    id := intField(row.data, "id"); frameId = id; scopes = []
    source := textField(objectField(row.data, "source"), "path")
    available := source.startsWith("/") && exists(source)
    sourcePath = if available then source else launch.source
    sourceLine = if available then intField(row.data, "line") else 0
    status = stopReason
    if !available { status += " — no source for this native frame; showing entry source" }
    revision += 1
    stopEpoch := epoch
    request("scopes", { frameId: id }, (body): none => {
      if epoch != stopEpoch || frameId != id || state != "Stopped" { return }
      scopes = rows(arrayField(body, "scopes"), "scope")
      if scopes.length > 0 { expandVariable(scopes[0]) }
      revision += 1
    })
  }
  expandVariable(row: DebugRow): none {
    if state != "Stopped" { return }
    if row.loaded {
      storage := stringArrayStorage(row) else { return }
      if !storage.loaded { expandVariable(storage) }
      return
    }
    if row.loading { return }
    reference := intField(row.data, "variablesReference")
    if reference == 0 { return }
    row.loading = true
    stopEpoch := epoch; selectedFrame := frameId
    request("variables", { variablesReference: reference, start: 0, count: 200 }, (body): none => {
      if epoch != stopEpoch || frameId != selectedFrame || state != "Stopped" { return }
      row.loading = false; row.loaded = true
      row.children = rows(arrayField(body, "variables"), row.key)
      revision += 1
      storage := stringArrayStorage(row) else { return }
      expandVariable(storage)
    }, (message): none => {
      if epoch != stopEpoch || frameId != selectedFrame || state != "Stopped" { return }
      row.loading = false; row.loaded = false; status = message; revision += 1
    })
  }
  control(command: string): none {
    if command == "pause" {
      if state == "Running" { request(command, { threadId }, (body): none => {}) }
      return
    }
    if state != "Stopped" { return }
    state = "Resuming"; status = "Resuming…"; revision += 1
    request(command, { threadId }, (body): none => { if state == "Resuming" { resumed() } },
      (message): none => { state = "Stopped"; status = message; revision += 1 })
  }
  private resumed(): none {
    epoch += 1; state = "Running"; status = "Running"; frames = []; scopes = []; sourceLine = 0; revision += 1
  }
  private exited(message: string): none {
    epoch += 1; state = "Exited"; status = message; frames = []; scopes = []; sourceLine = 0; pending = []; revision += 1
  }
  appendOutput(text: string): none {
    output += text
    if output.length > 262144 { output = "[Earlier output truncated]\n" + output.substring(output.length - 196608, output.length) }
    revision += 1
  }
  fail(message: string): none {
    state = "Failed"; status = message; appendOutput("[Debugger] " + message + "\n")
    pending = []
    if transport != none { transport!.close(); transport = none }
  }
  stop(): none {
    if transport == none || stoppingAt > 0L { return }
    request("disconnect", { terminateDebuggee: true }, (body): none => {})
    stoppingAt = Instant.now().toEpochMillis() + 1500L
    state = "Stopping"; status = "Stopping session…"; revision += 1
  }
  private stoppedSession(): none {
    ending = true; pending = []; frames = []; scopes = []; sourceLine = 0
    state = "Stopped session"; status = "Session stopped"; revision += 1
  }
  shutdown(): none {
    stop()
    // Called only after AppKit has returned, never during a UI action.
    for i of 0..<80 {
      tick()
      if transport == none { break }
      Thread.sleep(Duration.ofMillis(20L))
    }
    if transport != none { transport!.close(); transport = none }
    stoppedSession()
  }

}

function rows(values: JsonValue[], prefix: string): DebugRow[] {
  let result: DebugRow[] = []
  for index of 0..<values.length {
    value := values[index] as JsonObject else { continue }
    let label = textField(value, "name")
    if prefix == "frame" {
      parts := label.split("(")
      if parts.length > 0 { label = parts[0] }
    }
    content := textField(value, "value")
    if content != "" { label += " = " + content }
    typeName := textField(value, "type")
    if typeName != "" && !typeName.contains("std::") { label += " : " + typeName }
    line := intField(value, "line")
    if line > 0 { label += " — line " + string(line) }

    result.push(DebugRow { key: prefix + "/" + string(index), label, data: value })
  }
  return result
}
