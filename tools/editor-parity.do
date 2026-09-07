// Native oracle for identical JSON fixtures exercised by the Wasm host tests.
import { readText } from "std/fs"
import { parseJsonValue, formatJsonValue } from "std/json"
import { SourceFile } from "../src/semantic"
import { analyze, diagnostics, query, format } from "../src/editor-wasm"

class Fixture {
  sources: SourceFile[]
  entry: string
  module: string
  operation: string
  offset: int = 0
  text: string = ""
}

function main(arguments: string[]): none {
  fixture := try! Fixture.fromJsonValue(try! parseJsonValue(try! readText(arguments[0])))
  issues := analyze(fixture.sources, fixture.entry)
  let values: JsonValue[] = []
  for issue of issues { values.push(issue.toJsonObject()) }
  response := query(fixture.operation, fixture.module, fixture.offset, fixture.text)
  let strict: JsonValue[] = []
  for issue of diagnostics(fixture.sources, fixture.entry) { strict.push(issue.toJsonObject()) }
  result: Map<string, JsonValue> := { "diagnostics": values, "strict": strict, "response": response.toJsonObject() }
  println(formatJsonValue(result))
}
