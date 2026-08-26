#include "std_os_index.hpp"

namespace std_::os::index {
#line 49 "/std/os/index.do"
doof::Result<std::string, std::string> env(const std::string& name) {
#line 50 "/std/os/index.do"
    return ::doof_os::env(name);
}
#line 53 "/std/os/index.do"
int32_t pid() {
#line 54 "/std/os/index.do"
    return ::doof_os::pid();
}
#line 57 "/std/os/index.do"
std::string platform() {
#line 58 "/std/os/index.do"
    return ::doof_os::platform();
}
#line 61 "/std/os/index.do"
std::string architecture() {
#line 62 "/std/os/index.do"
    return ::doof_os::architecture();
}

#line 77 "/std/os/index.do"
doof::Result<std::shared_ptr<::NativeExecProcess>, std::string> spawnNative(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options) {
#line 78 "/std/os/index.do"
    const std::shared_ptr<std::vector<std::string>> envKeys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 79 "/std/os/index.do"
    const std::shared_ptr<std::vector<std::string>> envValues = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 80 "/std/os/index.do"
    const auto& _iterable_2 = options->env;
    for (const auto& [key, value] : *_iterable_2) {
#line 81 "/std/os/index.do"
        envKeys->push_back(key);
#line 82 "/std/os/index.do"
        envValues->push_back(value);
    }
#line 85 "/std/os/index.do"
    std::optional<int64_t> timeoutNanos = std::nullopt;
#line 86 "/std/os/index.do"
    if (!doof::is_null(options->timeout)) {
#line 87 "/std/os/index.do"
        (timeoutNanos = options->timeout->toNanos());
    }
#line 90 "/std/os/index.do"
    return ::NativeExecProcess::spawn(command, args, options->cwd, envKeys, envValues, options->inheritEnv, options->withStdin, options->mergeStderrIntoStdout, options->inheritOutput, (options->processGroupMode == ProcessGroupMode::Isolated), options->maxOutputBytes, timeoutNanos);
}

#line 110 "/std/os/index.do"
bool ExecStdoutStream::next() {
#line 111 "/std/os/index.do"
    const auto chunk = this->process->nextStdoutChunk();
#line 112 "/std/os/index.do"
    if (doof::is_null(chunk)) {
#line 113 "/std/os/index.do"
        return false;
    }
#line 115 "/std/os/index.do"
    (this->currentValue = doof::unwrap_optional(chunk));
#line 116 "/std/os/index.do"
    return true;
}
#line 119 "/std/os/index.do"
std::shared_ptr<std::vector<uint8_t>> ExecStdoutStream::value() {
    return this->currentValue;
}

#line 126 "/std/os/index.do"
bool ExecStderrStream::next() {
#line 127 "/std/os/index.do"
    const auto chunk = this->process->nextStderrChunk();
#line 128 "/std/os/index.do"
    if (doof::is_null(chunk)) {
#line 129 "/std/os/index.do"
        return false;
    }
#line 131 "/std/os/index.do"
    (this->currentValue = doof::unwrap_optional(chunk));
#line 132 "/std/os/index.do"
    return true;
}
#line 135 "/std/os/index.do"
std::shared_ptr<std::vector<uint8_t>> ExecStderrStream::value() {
    return this->currentValue;
}

#line 141 "/std/os/index.do"
doof::Result<std::shared_ptr<Exec>, std::string> Exec::spawn(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options) {
#line 142 "/std/os/index.do"
    return [&]() -> doof::Result<std::shared_ptr<Exec>, std::string> {
    auto _case_subject = spawnNative(command, args, options);
    if (std::holds_alternative<doof::Success<std::shared_ptr<::NativeExecProcess>>>(_case_subject)) {
        const auto& s = std::get<doof::Success<std::shared_ptr<::NativeExecProcess>>>(_case_subject);
        return doof::Success<std::shared_ptr<Exec>>{ std::make_shared<Exec>(s.value) };
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
        return doof::Failure<std::string>{ f.error };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
#line 154 "/std/os/index.do"
Stream__readonly_array_byte Exec::stdoutStream() {
#line 155 "/std/os/index.do"
    return std::make_shared<ExecStdoutStream>(this->native, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}));
}
#line 160 "/std/os/index.do"
Stream__readonly_array_byte Exec::stderrStream() {
#line 161 "/std/os/index.do"
    return std::make_shared<ExecStderrStream>(this->native, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}));
}
#line 166 "/std/os/index.do"
std::shared_ptr<std::vector<uint8_t>> Exec::nextStdoutChunk() {
#line 167 "/std/os/index.do"
    return this->native->nextStdoutChunk();
}
#line 170 "/std/os/index.do"
std::shared_ptr<std::vector<uint8_t>> Exec::nextStderrChunk() {
#line 171 "/std/os/index.do"
    return this->native->nextStderrChunk();
}
#line 174 "/std/os/index.do"
doof::Result<void, std::string> Exec::writeStdinText(const std::string& value) {
#line 175 "/std/os/index.do"
    return this->native->writeStdinText(value);
}
#line 178 "/std/os/index.do"
doof::Result<void, std::string> Exec::closeStdin() {
#line 179 "/std/os/index.do"
    return this->native->closeStdin();
}
#line 182 "/std/os/index.do"
bool Exec::isRunning() {
#line 183 "/std/os/index.do"
    return this->native->isRunning();
}
#line 186 "/std/os/index.do"
doof::Result<int32_t, std::string> Exec::wait() {
#line 187 "/std/os/index.do"
    return this->native->wait();
}
#line 190 "/std/os/index.do"
doof::Result<void, std::string> Exec::terminate(int32_t signal) {
#line 191 "/std/os/index.do"
    return this->native->terminate(signal);
}
#line 194 "/std/os/index.do"
bool Exec::stdoutOpen() {
#line 195 "/std/os/index.do"
    return this->native->stdoutOpen();
}
#line 198 "/std/os/index.do"
bool Exec::stderrOpen() {
#line 199 "/std/os/index.do"
    return this->native->stderrOpen();
}

#line 211 "/std/os/index.do"
doof::Result<std::shared_ptr<ExecResult>, std::string> run(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options) {
#line 212 "/std/os/index.do"
    std::shared_ptr<::NativeExecProcess> proc = nullptr;
#line 213 "/std/os/index.do"
    {
        auto _case_subject = spawnNative(command, args, options);
        if (std::holds_alternative<doof::Success<std::shared_ptr<::NativeExecProcess>>>(_case_subject)) {
            const auto& s = std::get<doof::Success<std::shared_ptr<::NativeExecProcess>>>(_case_subject);
#line 215 "/std/os/index.do"
            (proc = s.value);
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
            const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
#line 218 "/std/os/index.do"
            return doof::Failure<std::string>{ f.error };
    }
    }
#line 224 "/std/os/index.do"
    doof::assert_((!doof::is_null(proc)), std::string("expected Exec.spawn success case to initialize proc"));
#line 226 "/std/os/index.do"
    return [&]() -> doof::Result<std::shared_ptr<ExecResult>, std::string> {
    auto _case_subject = proc->runToCompletion();
    if (std::holds_alternative<doof::Success<std::shared_ptr<::NativeRunResult>>>(_case_subject)) {
        const auto& s = std::get<doof::Success<std::shared_ptr<::NativeRunResult>>>(_case_subject);
        return doof::Success<std::shared_ptr<ExecResult>>{ std::make_shared<ExecResult>(s.value->exitCode(), s.value->stdout(), s.value->stderr(), s.value->stdoutTruncated(), s.value->stderrTruncated()) };
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
        return doof::Failure<std::string>{ f.error };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
#line 1 "<doof-generated>"
doof::Result<std::string, std::string> _env(const std::string& name) {
    return ::doof_os::env(name);
}
int32_t _pid() {
    return ::doof_os::pid();
}
std::string _platform() {
    return ::doof_os::platform();
}
std::string _architecture() {
    return ::doof_os::architecture();
}
}
