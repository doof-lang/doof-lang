import { Assert } from "std/assert"
import { observeEnvironment, observeOpenEnvironmentArguments, observeTargetError, planObservedMacOSAppRun } from "./observe-command"

export function testObserveTargetValidationKeepsNativeTargetsSeparate(): none {
  Assert.equal(observeTargetError("native", false), "")
  Assert.equal(observeTargetError("macos-app", false), "")
  Assert.stringContains(observeTargetError("wasm", false), "native console")
  Assert.stringContains(observeTargetError("ios-app", true), "macOS applications")
}

export function testObserveLaunchEnvironmentIsExplicitAndForwardableToMacOSOpen(): none {
  environment := observeEnvironment(4317, true, 250, "/tmp/observer-ui", "/tmp/observer.url")
  Assert.equal(try! environment.get("DOOF_OBSERVE_PORT"), "4317")
  Assert.equal(try! environment.get("DOOF_OBSERVE_NO_OPEN"), "1")
  Assert.equal(try! environment.get("DOOF_OBSERVE_RETAIN_EVENTS"), "250")
  Assert.equal(try! environment.get("DOOF_OBSERVE_UI_ROOT"), "/tmp/observer-ui")
  Assert.equal(try! environment.get("DOOF_OBSERVE_URL_FILE"), "/tmp/observer.url")
  arguments := observeOpenEnvironmentArguments(environment)
  Assert.equal(arguments.length, 10)
  Assert.equal(arguments[0], "--env")
  Assert.stringContains(arguments[1], "DOOF_OBSERVE_")

  plan := planObservedMacOSAppRun("/tmp/Demo.app", "/tmp/project", environment)
  Assert.equal(plan.command, "open")
  Assert.equal(plan.arguments[0], "-n")
  Assert.equal(plan.arguments[plan.arguments.length - 1], "/tmp/Demo.app")
  Assert.equal(plan.directory, "/tmp/project")
}
