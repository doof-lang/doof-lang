import Foundation
import JavaScriptCore

guard CommandLine.arguments.count == 3 else {
    FileHandle.standardError.write(Data("usage: doof-wasm-test-runner module.wasm test-id\n".utf8))
    exit(2)
}

let modulePath = CommandLine.arguments[1]
let testID = CommandLine.arguments[2]
let moduleData: Data
do {
    moduleData = try Data(contentsOf: URL(fileURLWithPath: modulePath))
} catch {
    FileHandle.standardError.write(Data("could not read \(modulePath): \(error)\n".utf8))
    exit(2)
}

guard let context = JSContext() else {
    FileHandle.standardError.write(Data("could not create JavaScriptCore context\n".utf8))
    exit(2)
}

var reportedException: String?
context.exceptionHandler = { _, exception in
    reportedException = exception?.toString()
}

let hostWrite: @convention(block) (Int32, String) -> Void = { descriptor, text in
    let handle = descriptor == 2 ? FileHandle.standardError : FileHandle.standardOutput
    handle.write(Data(text.utf8))
}
context.setObject(hostWrite, forKeyedSubscript: "__doofHostWrite" as NSString)
context.setObject(moduleData.base64EncodedString(), forKeyedSubscript: "__doofModuleBase64" as NSString)
context.setObject(testID, forKeyedSubscript: "__doofTestID" as NSString)
context.setObject(modulePath, forKeyedSubscript: "__doofModulePath" as NSString)

let source = #"""
(() => {
  function decodeBase64(text) {
    const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const outputLength = Math.floor(text.length * 3 / 4) - (text.endsWith("==") ? 2 : text.endsWith("=") ? 1 : 0);
    const output = new Uint8Array(outputLength);
    let outputIndex = 0;
    for (let index = 0; index < text.length; index += 4) {
      const a = alphabet.indexOf(text[index]);
      const b = alphabet.indexOf(text[index + 1]);
      const c = text[index + 2] === "=" ? 0 : alphabet.indexOf(text[index + 2]);
      const d = text[index + 3] === "=" ? 0 : alphabet.indexOf(text[index + 3]);
      const value = (a << 18) | (b << 12) | (c << 6) | d;
      if (outputIndex < output.length) output[outputIndex++] = (value >> 16) & 255;
      if (outputIndex < output.length) output[outputIndex++] = (value >> 8) & 255;
      if (outputIndex < output.length) output[outputIndex++] = value & 255;
    }
    return output;
  }

  function encodeUtf8(text) {
    const bytes = [];
    for (let index = 0; index < text.length; ++index) {
      let code = text.charCodeAt(index);
      if (code >= 0xd800 && code <= 0xdbff && index + 1 < text.length) {
        const low = text.charCodeAt(++index);
        code = 0x10000 + ((code - 0xd800) << 10) + (low - 0xdc00);
      }
      if (code <= 0x7f) bytes.push(code);
      else if (code <= 0x7ff) bytes.push(0xc0 | code >> 6, 0x80 | code & 0x3f);
      else if (code <= 0xffff) bytes.push(0xe0 | code >> 12, 0x80 | code >> 6 & 0x3f, 0x80 | code & 0x3f);
      else bytes.push(0xf0 | code >> 18, 0x80 | code >> 12 & 0x3f, 0x80 | code >> 6 & 0x3f, 0x80 | code & 0x3f);
    }
    return bytes;
  }

  function decodeUtf8(bytes) {
    let result = "";
    for (let index = 0; index < bytes.length;) {
      const first = bytes[index++];
      let code;
      if (first < 0x80) code = first;
      else if (first < 0xe0) code = (first & 0x1f) << 6 | bytes[index++] & 0x3f;
      else if (first < 0xf0) code = (first & 0x0f) << 12 | (bytes[index++] & 0x3f) << 6 | bytes[index++] & 0x3f;
      else code = (first & 0x07) << 18 | (bytes[index++] & 0x3f) << 12 | (bytes[index++] & 0x3f) << 6 | bytes[index++] & 0x3f;
      if (code <= 0xffff) result += String.fromCharCode(code);
      else {
        code -= 0x10000;
        result += String.fromCharCode(0xd800 | code >> 10, 0xdc00 | code & 0x3ff);
      }
    }
    return result;
  }

  const args = [__doofModulePath, __doofTestID].map(value => encodeUtf8(value + "\0"));
  let memory;
  let exitCode = 0;
  const exited = {};
  const wasi = {
    args_sizes_get(argc, argvBufferSize) {
      const view = new DataView(memory.buffer);
      view.setUint32(argc, args.length, true);
      view.setUint32(argvBufferSize, args.reduce((sum, value) => sum + value.length, 0), true);
      return 0;
    },
    args_get(argv, argvBuffer) {
      const view = new DataView(memory.buffer);
      const bytes = new Uint8Array(memory.buffer);
      let cursor = argvBuffer;
      for (let index = 0; index < args.length; ++index) {
        view.setUint32(argv + index * 4, cursor, true);
        bytes.set(args[index], cursor);
        cursor += args[index].length;
      }
      return 0;
    },
    environ_sizes_get(count, bufferSize) {
      const view = new DataView(memory.buffer);
      view.setUint32(count, 0, true);
      view.setUint32(bufferSize, 0, true);
      return 0;
    },
    environ_get() { return 0; },
    fd_close() { return 0; },
    fd_seek(fd, offset, whence, newOffset) {
      const view = new DataView(memory.buffer);
      view.setUint32(newOffset, 0, true);
      view.setUint32(newOffset + 4, 0, true);
      return 0;
    },
    fd_read(fd, iovs, iovsLength, read) {
      new DataView(memory.buffer).setUint32(read, 0, true);
      return 0;
    },
    fd_write(fd, iovs, iovsLength, written) {
      const view = new DataView(memory.buffer);
      const bytes = new Uint8Array(memory.buffer);
      let text = "";
      let count = 0;
      for (let index = 0; index < iovsLength; ++index) {
        const pointer = view.getUint32(iovs + index * 8, true);
        const length = view.getUint32(iovs + index * 8 + 4, true);
        text += decodeUtf8(bytes.subarray(pointer, pointer + length));
        count += length;
      }
      view.setUint32(written, count, true);
      __doofHostWrite(fd, text);
      return 0;
    },
    proc_exit(code) {
      exitCode = code;
      throw exited;
    }
  };

  try {
    const module = new WebAssembly.Module(decodeBase64(__doofModuleBase64));
    const instance = new WebAssembly.Instance(module, { wasi_snapshot_preview1: wasi });
    memory = instance.exports.memory;
    instance.exports._start();
  } catch (error) {
    if (error !== exited) {
      __doofHostWrite(2, "wasm trap: " + String(error) + "\n");
      exitCode = 1;
    }
  }
  return exitCode;
})()
"""#

guard let result = context.evaluateScript(source) else {
    FileHandle.standardError.write(Data("JavaScriptCore returned no result\n".utf8))
    exit(2)
}
if let exception = reportedException {
    FileHandle.standardError.write(Data("JavaScriptCore exception: \(exception)\n".utf8))
    exit(2)
}
exit(result.toInt32())
