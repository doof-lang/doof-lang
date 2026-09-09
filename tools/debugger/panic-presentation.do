import { textField } from "./protocol"
import { parseJsonValue } from "std/json"

export function panicMessageFromVariables(values: JsonValue[]): string {
  for value of values {
    variable := value as JsonObject else { continue }
    if textField(variable, "name") == "msg" { return readablePanicText(textField(variable, "value")) }
  }
  return ""
}

function readablePanicText(value: string): string {
  let text = value
  // LLDB may summarize a string reference as 0xADDRESS "message".
  parts := value.split(" ")
  if parts.length > 1 && parts[0].startsWith("0x") && parts[0].length > 2 {
    let address = true
    for i of 2..<parts[0].length {
      ch := parts[0][i]
      if !((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F')) { address = false }
    }
    remainder := value.substring(parts[0].length, value.length).trim()
    if address && remainder.startsWith("\"") { text = remainder }
  }
  decoded := parseJsonValue(text) else { return text }
  message := decoded as string else { return text }
  return message
}
