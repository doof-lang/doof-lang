import { Button, Text, TextArea, Window, runApp, quitApp } from "std/appkit"
import { readText, exists } from "std/fs"
import { parseJsonValue } from "std/json"
import { setInterval } from "std/event"
import { Duration } from "std/time"
import { DebugLaunch, debugLaunchError } from "../../src/debug-command"
import { DebugSession } from "./session"
import { DebuggerUI } from "./ui"

function loadLaunch(arguments: string[]): Result<DebugLaunch, string> {
  if arguments.length != 1 { return Failure("Start a session with doof debug <entry.do or package-directory>.") }
  text := readText(arguments[0]) else error { return Failure("Cannot read debugger launch: " + string(error)) }
  try value := parseJsonValue(text)
  try launch := DebugLaunch.fromJsonValue(value)
  error := debugLaunchError(launch)
  if error != "" { return Failure(error) }
  if !exists(launch.executable) { return Failure("Debug executable is missing: " + launch.executable) }
  return Success(launch)
}

function welcome(message: string = ""): int {
  window := <Window title="Doof Debugger" width=620 height=320>
    <Text value="Debug a Doof program"/>
    <Text value="Start from your project directory in Terminal:"/>
    <TextArea label="Command" value="doof debug .\n\nOr: doof debug path/to/main.do -- program-arguments" enabled=false minHeight=90.0/>
    <Text value={message} hidden={message == ""}/>
    <Button title="Close" onClick=>quitApp()/>
  </Window>
  window.show()
  runApp()
  window.content.dispose()
  return if message == "" then 0 else 1
}

function main(arguments: string[]): int {
  if arguments.length == 0 { return welcome() }
  launch := loadLaunch(arguments) else error {
    return welcome(error)
  }
  session := DebugSession { launch }
  ui := DebuggerUI { session }
  window := ui.window()
  window.show()
  session.start()
  ui.refresh()
  timer := setInterval(Duration.ofMillis(25L), (): none => { session.tick(); ui.refresh() }, false)
  runApp()
  timer.cancel()
  session.shutdown()
  window.content.dispose()
  return 0
}
