import { Assert } from "std/assert"
import { DebugRow } from "./model"
import { isInternalVariable, visibleVariables, visibleScopes, isSystemGlobal } from "./variable-presentation"
import { sourceIdentifiers } from "./source-presentation"

export function testVariablesHideGeneratedBindingsButPreserveUserNames(): none {
  identifiers := sourceIdentifiers("let _iterable_9 = 1; let _count = 2")
  Assert.equal(isInternalVariable("_iterable_2", identifiers), true)
  Assert.equal(isInternalVariable("_discard_2_0", identifiers), true)
  Assert.equal(isInternalVariable("_case_subject", identifiers), true)
  Assert.equal(isInternalVariable("_iterable_9", identifiers), false)
  Assert.equal(isInternalVariable("_count", identifiers), false)
  Assert.equal(isInternalVariable("_iterable_cache", identifiers), false)
  Assert.equal(isInternalVariable("_iterable_", identifiers), false)
  Assert.equal(isInternalVariable("count", identifiers), false)
  hidden := DebugRow { key: "scope/0/0", label: "internal", data: { name: "_iterable_2" } }
  user := DebugRow { key: "scope/0/1", label: "count", data: { name: "count", variablesReference: 12 } }
  rows := [hidden, user]
  visible := visibleVariables(rows, identifiers, false)
  Assert.equal(visible.length, 1)
  Assert.equal(visible[0], user)
  Assert.equal(visibleVariables(rows, identifiers, true).length, 2)
  Assert.equal(rows.length, 2)
}

export function testRegisterScopeIsHiddenUnlessInternalsAreRequested(): none {
  locals := DebugRow { key: "scope/0", label: "Locals", data: { name: "Locals" } }
  registers := DebugRow { key: "scope/1", label: "Registers", data: { name: "Registers", presentationHint: "registers" } }
  Assert.equal(visibleScopes([locals, registers], false).length, 1)
  Assert.equal(visibleScopes([locals, registers], true).length, 2)
}

export function testSystemGlobalsAreHiddenWithoutHidingApplicationGlobals(): none {
  for name of ["std::__1::ios_base::showpoint", "std::locale::none", "doof::detail::active_actor_domain", "::std::locale::none", "__cxxabiv1::value"] {
    Assert.equal(isSystemGlobal(name), true)
  }
  for name of ["app::main_::counter", "doof_app::config", "std_app::setting", "std_::setting", "doof_::setting", "_userGlobal", "counter"] {
    Assert.equal(isSystemGlobal(name), false)
  }
  system := DebugRow { key: "scope/1/0", label: "system", data: { name: "std::__1::locale::none" } }
  application := DebugRow { key: "scope/1/1", label: "application", data: { name: "app::main_::message", "type": "std::string" } }
  filtered := visibleVariables([system, application], [], false, true)
  Assert.equal(filtered.length, 1)
  Assert.equal(filtered[0], application)
  Assert.equal(visibleVariables([system, application], [], true, true).length, 2)
  Assert.equal(visibleVariables([system], [], false).length, 1)
}

export function testEmptyFilteredGlobalsDisappearOnlyAfterLoading(): none {
  globalScope := DebugRow { key: "scope/1", label: "Globals", data: { name: "Globals" } }
  Assert.equal(visibleScopes([globalScope], false).length, 1)
  globalScope.loading = true
  Assert.equal(visibleScopes([globalScope], false).length, 1)
  globalScope.loading = false
  globalScope.children = [DebugRow { key: "scope/1/0", label: "system", data: { name: "doof::detail::value" } }]
  globalScope.loaded = true
  Assert.equal(visibleScopes([globalScope], false).length, 0)
  Assert.equal(visibleScopes([globalScope], true).length, 1)
  globalScope.children.push(DebugRow { key: "scope/1/1", label: "user", data: { name: "app::main_::counter" } })
  Assert.equal(visibleScopes([globalScope], false).length, 1)
}
