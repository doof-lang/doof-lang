import { Assert } from "std/assert"
import {
  MacOSAppConfig, MacOSPackageConfig, macOSCodesignArguments, macOSGatekeeperArguments,
  macOSNotarizationMode, macOSNotaryLogArguments, macOSNotarySubmitArguments, macOSPackageArchiveName,
  parseMacOSNotarySubmission, renderMacOSInfoPlist,
} from "./macos-app"

export function testRendersMacOSInfoPlistAndCustomMetadata(): none {
  custom: Map<string, SerialValue> := {}
  custom.set("NSLocalNetworkUsageDescription", "Find nearby players & hosts.")
  services: SerialValue[] := ["_doof._tcp"]
  custom.set("NSBonjourServices", services.cloneReadonly())
  plist := renderMacOSInfoPlist(MacOSAppConfig {
    executableName: "DoofDemo",
    bundleId: "dev.doof.demo",
    displayName: "Doof & Demo",
    version: "1.2.3",
    iconPath: "/app/icon.png",
    infoPlist: custom.cloneReadonly(),
    category: "public.app-category.games",
    minimumSystemVersion: "12.0",
  })

  Assert.stringContains(plist, "<string>dev.doof.demo</string>")
  Assert.stringContains(plist, "<string>Doof &amp; Demo</string>")
  Assert.stringContains(plist, "<string>DoofDemo.icns</string>")
  Assert.stringContains(plist, "<key>NSBonjourServices</key>")
  Assert.stringContains(plist, "<array>")
}

export function testPlansMacOSPackageNamesAndSigningArguments(): none {
  Assert.equal(macOSPackageArchiveName("Demo", "1.0 beta"), "Demo-1.0-beta-macos.zip")
  arguments := macOSCodesignArguments("/tmp/Demo.app", "-", "ad-hoc", "/tmp/entitlements.plist")
  Assert.equal(arguments.contains("--timestamp=none"), true)
  Assert.equal(arguments.contains("--entitlements"), true)
  Assert.equal(arguments[arguments.length - 1], "/tmp/Demo.app")
}

export function testDeveloperIdReleaseSigningUsesHardenedRuntimeAndTimestamp(): none {
  arguments := macOSCodesignArguments("/tmp/Demo.app", "Developer ID Application: Example", "developer-id")
  Assert.equal(arguments.contains("runtime"), true)
  Assert.equal(arguments.contains("--timestamp"), true)
  Assert.equal(arguments.contains("--timestamp=none"), false)
}

export function testChoosesNotarizationModeFromSigningAndProfile(): none {
  Assert.equal(macOSNotarizationMode(MacOSPackageConfig { signing: "developer-id", notaryProfile: "doof-notary" }) == .Notarize, true)
  Assert.equal(macOSNotarizationMode(MacOSPackageConfig { signing: "developer-id" }) == .Unnotarized, true)
  Assert.equal(macOSNotarizationMode(MacOSPackageConfig { signing: "ad-hoc", notaryProfile: "doof-notary" }) == .SkipAdHoc, true)
}

export function testPlansNotaryAndGatekeeperCommands(): none {
  submit := macOSNotarySubmitArguments("/dist/Demo-1.0-macos.zip", "doof-notary")
  Assert.equal(submit[0], "notarytool")
  Assert.equal(submit[1], "submit")
  Assert.equal(submit[2], "/dist/Demo-1.0-macos.zip")
  Assert.equal(submit.contains("--wait"), true)
  Assert.equal(submit[submit.indexOf("--keychain-profile") + 1], "doof-notary")
  Assert.equal(submit[submit.indexOf("--output-format") + 1], "json")
  log := macOSNotaryLogArguments("abc-123", "doof-notary", "/build/log.json")
  Assert.equal(log[1], "log")
  Assert.equal(log[2], "abc-123")
  Assert.equal(log[log.length - 1], "/build/log.json")
  gatekeeper := macOSGatekeeperArguments("/build/Demo.app")
  Assert.equal(gatekeeper[gatekeeper.indexOf("--type") + 1], "execute")
  Assert.equal(gatekeeper[gatekeeper.length - 1], "/build/Demo.app")
}

export function testParsesAcceptedNotarySubmissionAfterProgressOutput(): none {
  submission := parseMacOSNotarySubmission(
    "Conducting pre-submission checks...\n{\"id\":\"abc-123\",\"status\":\"Accepted\",\"message\":\"Processing complete\"}\n",
  )!
  Assert.equal(submission.id, "abc-123")
  Assert.equal(submission.status, "Accepted")
  Assert.equal(submission.message, "Processing complete")
}

export function testReportsRejectedAndUnreadableNotaryResponses(): none {
  invalid := parseMacOSNotarySubmission("{\"id\":\"abc-123\",\"status\":\"Invalid\"}")!
  Assert.equal(invalid.status, "Invalid")
  Assert.stringContains(
    notaryFailure("Error: No Keychain password item found for profile: doof-notary"),
    "No Keychain password item found",
  )
  Assert.stringContains(notaryFailure("{\"id\":\"abc-123\"}"), "no status")
  Assert.stringContains(notaryFailure("{\"status\":"), "unreadable JSON")
}

function notaryFailure(response: string): string {
  return case parseMacOSNotarySubmission(response) {
    _: Success -> "",
    failure: Failure -> failure.error,
  }
}
