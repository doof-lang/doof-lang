// DAP framing is byte based; JSON strings and UTF-8 code points may span reads.
import { BlobBuilder, BlobReader, decodeUtf8 } from "std/blob"
import { formatJsonValue, parseJsonObject } from "std/json"

export function bytesOf(text: string): readonly byte[] {
  builder := BlobBuilder()
  builder.writeString(text)
  return builder.build()
}

export function frameMessage(message: JsonObject): string {
  body := formatJsonValue(message)
  return "Content-Length: " + string(bytesOf(body).length) + "\r\n\r\n" + body
}

export class DapDecoder {
  private let buffer: byte[] = []
  private let expected = -1

  feed(bytes: readonly byte[]): Result<JsonObject[], string> {
    if buffer.length + bytes.length > 8388608 { return Failure("DAP buffer exceeded 8 MiB") }
    for item of bytes { buffer.push(item) }
    let messages: JsonObject[] = []
    while true {
      if expected < 0 {
        let end = -1
        if buffer.length >= 4 {
          for i of 0..<(buffer.length - 3) {
            if buffer[i] == 13 && buffer[i+1] == 10 && buffer[i+2] == 13 && buffer[i+3] == 10 { end = i; break }
          }
        }
        if end < 0 {
          if buffer.length > 8192 { return Failure("DAP header exceeded 8 KiB") }
          break
        }
        if end > 8192 { return Failure("DAP header exceeded 8 KiB") }
        header := decodeUtf8(slice(0, end).drainToReadonly()) else { return Failure("Invalid DAP header encoding") }
        for line of header.split("\r\n") {
          if line.toLowerCase().startsWith("content-length:") {
            if expected >= 0 { return Failure("Duplicate DAP Content-Length") }
            digits := line.substring(15, line.length).trim()
            if digits == "" { return Failure("Missing DAP Content-Length value") }
            let length = 0
            for index of 0..<digits.length {
              digit := digits[index]
              if digit < '0' || digit > '9' { return Failure("Invalid DAP Content-Length") }
              length = length * 10 + int(digit) - int('0')
              if length > 8388608 { return Failure("DAP message exceeded 8 MiB") }
            }
            expected = length
          }
        }
        if expected < 0 { return Failure("Missing DAP Content-Length") }
        discard(end + 4)
      }
      if buffer.length < expected { break }
      body := decodeUtf8(slice(0, expected).drainToReadonly()) else { return Failure("Invalid UTF-8 DAP body") }
      message := parseJsonObject(body) else error { return Failure("Invalid DAP JSON: " + error) }
      messages.push(message)
      discard(expected)
      expected = -1
    }
    return Success(messages)
  }

  finish(): Result<none, string> {
    if buffer.length > 0 || expected >= 0 { return Failure("LLDB-DAP closed during a message") }
    return Success(none)
  }

  private slice(start: int, end: int): byte[] {
    let result: byte[] = []
    for i of start..<end { result.push(buffer[i]) }
    return result
  }
  private discard(count: int): none { buffer = slice(count, buffer.length) }
}

export function field(object: JsonObject, name: string): JsonValue {
  value := object.get(name) else { return none }
  return value
}
export function textField(object: JsonObject, name: string): string {
  value := field(object, name) as string else { return "" }
  return value
}
export function intField(object: JsonObject, name: string): int {
  value := field(object, name)
  case value {
    n: long -> return int(n),
    n: double -> return int(n),
    _ -> return 0,
  }
}
export function boolField(object: JsonObject, name: string): bool {
  value := field(object, name) as bool else { return false }
  return value
}
export function objectField(object: JsonObject, name: string): JsonObject {
  value := field(object, name) as JsonObject else { return {} }
  return value
}
export function arrayField(object: JsonObject, name: string): JsonValue[] {
  value := field(object, name) as JsonValue[] else { return [] }
  return value
}
