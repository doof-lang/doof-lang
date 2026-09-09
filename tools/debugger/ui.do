import {
  Column, Row, Button, Checkbox, Text, TextArea, SourceView, SplitView, OutlineView,
  Toolbar, ToolbarItem, ToolbarFlexibleSpace, Window, openFile,
  Menu, MenuItem, StandardApplicationMenu, StandardEditMenu, StandardWindowMenu, setAppMenus,
} from "std/appkit"
import { sourceHighlights, sourceIdentifiers } from "./source-presentation"
import { collectionChildren, variableLabel } from "./collection-presentation"
import { frameLabel, sourceFrames } from "./frame-presentation"
import { visibleVariables, visibleScopes, isGlobalScope } from "./variable-presentation"
import { FileDialogOptions, SourceHighlight } from "std/appkit"
import { DebugSession } from "./session"
import { DebugRow } from "./model"
import { intField } from "./protocol"
import { readText } from "std/fs"

export class DebuggerUI {
  session: DebugSession
  private let source: SourceView | none = none
  private let threadList: OutlineView<DebugRow> | none = none
  private let frameList: OutlineView<DebugRow> | none = none
  private let variableList: OutlineView<DebugRow> | none = none
  private let highlights: SourceHighlight[] = []
  private let highlightsDirty = false
  private let identifiers: Set<string> = []
  private let showInternals = false
  private let pendingVariableExpansion = ""
  private let displayedPath = ""
  private let displayedLine = 0
  private let sourceText = ""
  private let sourceNotice = ""
  private let lastRevision = -1
  private let sourceAvailable = true
  private let expandedFrame = -1
  private let expandedEpoch = -1

  window(): Window {
    source = SourceView((line): none => session.toggleBreakpoint(displayedPath, line))
    threadList = OutlineView<DebugRow>([], (row): string => row.key, (row): DebugRow[] => [], (row): string => row.label,
      (row): none => { if row != none { session.selectThread(intField(row!.data, "id")) } }, false, "Threads")
    frameList = OutlineView<DebugRow>([], (row): string => row.key, (row): DebugRow[] => [], (row): string => frameLabel(row),
      (row): none => { if row != none { session.selectFrame(row!) } }, false, "Call stack")
    variableList = OutlineView<DebugRow>([], (row): string => row.key, (row): DebugRow[] => visibleVariables(collectionChildren(row, showInternals), identifiers, showInternals, isGlobalScope(row)), (row): string => variableLabel(row, showInternals),
      (row): none => { if row != none { pendingVariableExpansion = row!.key; session.expandVariable(row!) } }, false, "Variables")
    threadList!.asView().node.style.grow = 0.0
    threadList!.asView().node.style.minHeight = 52.0
    threadList!.asView().node.style.flexBasis = 52.0
    toolbar := <Toolbar displayMode=.IconOnly>
      <ToolbarItem id="continue" label="Continue" toolTip="Continue execution" symbol="play.fill" enabled=>session.state == "Stopped" onClick=>session.control("continue")/>
      <ToolbarItem id="pause" label="Pause" symbol="pause.fill" enabled=>session.state == "Running" onClick=>session.control("pause")/>
      <ToolbarItem id="over" label="Step Over" toolTip="Step over the current line" symbol="arrow.turn.down.right" enabled=>session.state == "Stopped" onClick=>session.control("next")/>
      <ToolbarItem id="into" label="Step Into" toolTip="Step into the current call" symbol="arrow.down" enabled=>session.state == "Stopped" onClick=>session.control("stepIn")/>
      <ToolbarItem id="out" label="Step Out" toolTip="Finish the current function" symbol="arrow.up" enabled=>session.state == "Stopped" onClick=>session.control("stepOut")/>
      <ToolbarFlexibleSpace/>
      <ToolbarItem id="stop" label="Stop" symbol="stop.fill" enabled=>session.state == "Running" || session.state == "Stopped" || session.state == "Starting" onClick=>session.stop()/>
    </Toolbar>
    setAppMenus([
      StandardApplicationMenu(), StandardEditMenu(),
      <Menu title="Debug">
        <MenuItem title="Continue" enabled=>session.state == "Stopped" onSelect=>session.control("continue")/>
        <MenuItem title="Step Over" enabled=>session.state == "Stopped" onSelect=>session.control("next")/>
        <MenuItem title="Step Into" enabled=>session.state == "Stopped" onSelect=>session.control("stepIn")/>
        <MenuItem title="Step Out" enabled=>session.state == "Stopped" onSelect=>session.control("stepOut")/>
      </Menu>, StandardWindowMenu(),
    ])
    return <Window title="Doof Debugger" width=1440 height=900 toolbar={toolbar}>
      <SplitView weights={[0.8, 3.3, 0.9]}>
        <Column grow=1.0>
          <Text value="Threads" fontSize=11.0 semibold=true secondary=true/>
          {threadList!}
          <Text value="Call stack" fontSize=11.0 semibold=true secondary=true/>
          <Text value="No Doof source frames" fontSize=11.0 secondary=true hidden=>session.state != "Stopped" || sourceFrames(session.frames).length != 0/>
          {frameList!}
        </Column>
        <Column grow=3.0>
          <Row>
            <Column grow=1.0><Text value=>sourceTitle() semibold=true/></Column>
            <Button title="Open…" onClick=>openSource()/>
          </Row>
          <Column hidden=>!session.isPanicStop()>
            <Text value="Paused on panic" fontSize=15.0 semibold=true/>
            <Text value=>session.panicMessage hidden=>session.panicMessage == ""/>
          </Column>
          <Text value=>sourceNotice hidden=>sourceNotice == "" fontSize=11.0 secondary=true/>
          {source!}
        </Column>
        <Column grow=1.0>
          <Text value="Variables" fontSize=11.0 semibold=true secondary=true/>
          <Checkbox title="Show internals" checked=>showInternals onChange={(value): none => { showInternals = value; session.revision += 1; refresh() }}/>
          {variableList!}
        </Column>
      </SplitView>
      <TextArea label="Program output" value=>session.output enabled=false minHeight=100.0/>
      <Text value=>session.status fontSize=11.0 secondary=true/>
    </Window>
  }

  private sourceTitle(): string {
    parts := displayedPath.split("/")
    name := if parts.length > 0 then parts[parts.length-1] else "Source"
    return name + if displayedLine > 0 then "  ·  Line " + string(displayedLine) else ""
  }

  private openSource(): none {
    paths := openFile(FileDialogOptions { title: "Open Doof source" })
    if paths.length > 0 { session.sourcePath = paths[0]; session.sourceLine = 0; session.revision += 1 }
  }

  refresh(): none {
    if lastRevision == session.revision { return }
    lastRevision = session.revision
    threadList!.reload(session.threads)
    frames := sourceFrames(session.frames)
    frameList!.reload(frames)
    for frame of frames { if intField(frame.data, "id") == session.frameId { frameList!.select(frame.key); break } }
    changedPath := displayedPath != session.sourcePath
    reveal := changedPath || displayedLine != session.sourceLine
    if changedPath {
      displayedPath = session.sourcePath
      sourceNotice = ""
      sourceAvailable = true
      loaded := readText(displayedPath) else {
        sourceAvailable = false; sourceText = ""; sourceNotice = "Source unavailable: " + displayedPath
        source!.setLines([], [], 0); return
      }
      sourceText = loaded
      highlights = if displayedPath.endsWith(".do") then sourceHighlights(loaded) else []
      identifiers = sourceIdentifiers(loaded)
      highlightsDirty = true
    }
    scopes := visibleScopes(session.scopes, showInternals, identifiers)
    variableList!.reload(scopes)
    selectedVariable := variableList!.selected()
    if selectedVariable != none && selectedVariable!.key == pendingVariableExpansion &&
      collectionChildren(selectedVariable!, showInternals).length > 0 {
      variableList!.expand(pendingVariableExpansion)
      pendingVariableExpansion = ""
    }
    if scopes.length > 0 && scopes[0].children.length > 0 &&
      (expandedFrame != session.frameId || expandedEpoch != session.epoch) {
      variableList!.expand(scopes[0].key)
      expandedFrame = session.frameId; expandedEpoch = session.epoch
    }
    if !sourceAvailable { return }
    displayedLine = session.sourceLine
    let lines: string[] = []
    for line of sourceText.split("\n") { lines.push(line) }
    let markers: int[] = []
    for line of lines { markers.push(0) }
    points := session.breakpoints.get(displayedPath) else { return updateSource(lines, markers, reveal) }
    for point of points {
      line := if point.verified && point.actualLine > 0 then point.actualLine else point.line
      if line > 0 && line <= markers.length { markers[line-1] = if point.verified then 2 else 1 }
    }
    updateSource(lines, markers, reveal)
  }
  private updateSource(lines: string[], markers: int[], reveal: bool): none {
    current := if displayedLine <= lines.length then displayedLine else 0
    source!.setLines(lines, markers, current, reveal)
    if highlightsDirty { source!.setHighlights(highlights); highlightsDirty = false }
  }
}
