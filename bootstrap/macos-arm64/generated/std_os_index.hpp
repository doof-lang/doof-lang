#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::time::duration { struct Duration; }
namespace std_::time::duration { struct Thread; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::os::index {
    struct ExecOptions;
    struct ExecStdoutStream;
    struct ExecStderrStream;
    struct Exec;
    struct ExecResult;
}

#include "std_time_index.hpp"

namespace doof_os { using Duration = ::std_::time::duration::Duration; }
namespace doof_os { using Thread = ::std_::time::duration::Thread; }
#include "native_os.hpp"

namespace std_::os::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<ExecStdoutStream>, std::shared_ptr<ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    doof::Result<std::string, std::string> _env(std::string name);
    int32_t _pid();
    std::string _platform();
    std::string _architecture();
    struct ExecOptions : public std::enable_shared_from_this<ExecOptions> {
    std::optional<std::string> cwd = std::nullopt;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    bool inheritEnv = true;
    bool withStdin = true;
    bool mergeStderrIntoStdout = false;
    bool inheritOutput = false;
    std::optional<int64_t> maxOutputBytes = std::nullopt;
    std::shared_ptr<::std_::time::duration::Duration> timeout = nullptr;
    ExecOptions(std::optional<std::string> cwd = std::nullopt, std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), bool inheritEnv = true, bool withStdin = true, bool mergeStderrIntoStdout = false, bool inheritOutput = false, std::optional<int64_t> maxOutputBytes = std::nullopt, std::shared_ptr<::std_::time::duration::Duration> timeout = nullptr) : cwd(cwd), env(env), inheritEnv(inheritEnv), withStdin(withStdin), mergeStderrIntoStdout(mergeStderrIntoStdout), inheritOutput(inheritOutput), maxOutputBytes(maxOutputBytes), timeout(timeout) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExecOptions>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ExecStdoutStream : public std::enable_shared_from_this<ExecStdoutStream> {
    std::shared_ptr<::NativeExecProcess> process;
    std::shared_ptr<std::vector<uint8_t>> currentValue = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    ExecStdoutStream(std::shared_ptr<::NativeExecProcess> process, std::shared_ptr<std::vector<uint8_t>> currentValue = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{})) : process(process), currentValue(currentValue) {}
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
    struct ExecStderrStream : public std::enable_shared_from_this<ExecStderrStream> {
    std::shared_ptr<::NativeExecProcess> process;
    std::shared_ptr<std::vector<uint8_t>> currentValue = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    ExecStderrStream(std::shared_ptr<::NativeExecProcess> process, std::shared_ptr<std::vector<uint8_t>> currentValue = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{})) : process(process), currentValue(currentValue) {}
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
    struct Exec : public std::enable_shared_from_this<Exec> {
    std::shared_ptr<::NativeExecProcess> native;
    Exec(std::shared_ptr<::NativeExecProcess> native) : native(native) {}
    static doof::Result<std::shared_ptr<Exec>, std::string> spawn(std::string command, std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<ExecOptions> options = std::make_shared<ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, std::nullopt, nullptr));
    Stream__readonly_array_byte stdoutStream();
    Stream__readonly_array_byte stderrStream();
    std::shared_ptr<std::vector<uint8_t>> nextStdoutChunk();
    std::shared_ptr<std::vector<uint8_t>> nextStderrChunk();
    doof::Result<void, std::string> writeStdinText(std::string value);
    doof::Result<void, std::string> closeStdin();
    bool isRunning();
    doof::Result<int32_t, std::string> wait();
    doof::Result<void, std::string> terminate(int32_t signal = 15);
    bool stdoutOpen();
    bool stderrOpen();
};
    struct ExecResult : public std::enable_shared_from_this<ExecResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> stdout;
    std::shared_ptr<std::vector<uint8_t>> stderr;
    bool stdoutTruncated = false;
    bool stderrTruncated = false;
    ExecResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> stdout, std::shared_ptr<std::vector<uint8_t>> stderr, bool stdoutTruncated = false, bool stderrTruncated = false) : exitCode(exitCode), stdout(stdout), stderr(stderr), stdoutTruncated(stdoutTruncated), stderrTruncated(stderrTruncated) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExecResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    doof::Result<std::string, std::string> env(std::string name);
    int32_t pid();
    std::string platform();
    std::string architecture();
    doof::Result<std::shared_ptr<::NativeExecProcess>, std::string> spawnNative(std::string command, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<ExecOptions> options);
    doof::Result<std::shared_ptr<ExecResult>, std::string> run(std::string command, std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<ExecOptions> options = std::make_shared<ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, std::nullopt, nullptr));
}

namespace std_::os::index {
}
