export class DebugRow {
  key: string
  label: string
  data: JsonObject = {}
  let children: DebugRow[] = []
  let loaded: bool = false
  let loading: bool = false
}
export class SourceBreakpoint {
  line: int
  let actualLine: int = 0
  let verified: bool = false
  let message: string = "Pending"
}
