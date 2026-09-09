export import class DebugTransport from "native_transport.hpp" {
  static start(command: string, arguments: string[]): Result<DebugTransport, string>
  send(text: string): Result<none, string>
  flush(): none
  read(stderrStream: bool): readonly byte[]
  running(): bool
  stdoutOpen(): bool
  error(): string
  close(): none
}
