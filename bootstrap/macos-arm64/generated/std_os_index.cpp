#include "std_os_index.hpp"

namespace std_::os::index {
doof::Result<std::string, std::string> env(const std::string& name) {
    return ::doof_os::env(name);
}
int32_t pid() {
    return ::doof_os::pid();
}
std::string platform() {
    return ::doof_os::platform();
}
std::string architecture() {
    return ::doof_os::architecture();
}

doof::Result<std::shared_ptr<::NativeExecProcess>, std::string> spawnNative(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options) {
    const std::shared_ptr<std::vector<std::string>> envKeys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const std::shared_ptr<std::vector<std::string>> envValues = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_2 = options->env;
    for (const auto& [key, value] : *_iterable_2) {
        envKeys->push_back(key);
        envValues->push_back(value);
    }
    std::optional<int64_t> timeoutNanos = std::nullopt;
    if (!doof::is_null(options->timeout)) {
        (timeoutNanos = options->timeout->toNanos());
    }
    return ::NativeExecProcess::spawn(command, args, options->cwd, envKeys, envValues, options->inheritEnv, options->withStdin, options->mergeStderrIntoStdout, options->inheritOutput, (options->processGroupMode == ProcessGroupMode::Isolated), options->maxOutputBytes, timeoutNanos);
}

bool ExecStdoutStream::next() {
    const auto chunk = this->process->nextStdoutChunk();
    if (doof::is_null(chunk)) {
        return false;
    }
    (this->currentValue = doof::unwrap_optional(chunk));
    return true;
}
std::shared_ptr<std::vector<uint8_t>> ExecStdoutStream::value() {
    return this->currentValue;
}

bool ExecStderrStream::next() {
    const auto chunk = this->process->nextStderrChunk();
    if (doof::is_null(chunk)) {
        return false;
    }
    (this->currentValue = doof::unwrap_optional(chunk));
    return true;
}
std::shared_ptr<std::vector<uint8_t>> ExecStderrStream::value() {
    return this->currentValue;
}

doof::Result<std::shared_ptr<Exec>, std::string> Exec::spawn(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options) {
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
Stream__readonly_array_byte Exec::stdoutStream() {
    return std::make_shared<ExecStdoutStream>(this->native, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}));
}
Stream__readonly_array_byte Exec::stderrStream() {
    return std::make_shared<ExecStderrStream>(this->native, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}));
}
std::shared_ptr<std::vector<uint8_t>> Exec::nextStdoutChunk() {
    return this->native->nextStdoutChunk();
}
std::shared_ptr<std::vector<uint8_t>> Exec::nextStderrChunk() {
    return this->native->nextStderrChunk();
}
doof::Result<void, std::string> Exec::writeStdinText(const std::string& value) {
    return this->native->writeStdinText(value);
}
doof::Result<void, std::string> Exec::closeStdin() {
    return this->native->closeStdin();
}
bool Exec::isRunning() {
    return this->native->isRunning();
}
doof::Result<int32_t, std::string> Exec::wait() {
    return this->native->wait();
}
doof::Result<void, std::string> Exec::terminate(int32_t signal) {
    return this->native->terminate(signal);
}
bool Exec::stdoutOpen() {
    return this->native->stdoutOpen();
}
bool Exec::stderrOpen() {
    return this->native->stderrOpen();
}

doof::Result<std::shared_ptr<ExecResult>, std::string> run(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options) {
    std::shared_ptr<::NativeExecProcess> proc = nullptr;
    {
        auto _case_subject = spawnNative(command, args, options);
        if (std::holds_alternative<doof::Success<std::shared_ptr<::NativeExecProcess>>>(_case_subject)) {
            const auto& s = std::get<doof::Success<std::shared_ptr<::NativeExecProcess>>>(_case_subject);
            (proc = s.value);
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
            const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
            return doof::Failure<std::string>{ f.error };
    }
    }
    doof::assert_((!doof::is_null(proc)), std::string("expected Exec.spawn success case to initialize proc"));
    return [&]() -> doof::Result<std::shared_ptr<ExecResult>, std::string> {
    auto _case_subject = proc->runToCompletion();
    if (std::holds_alternative<doof::Success<std::shared_ptr<::NativeRunResult>>>(_case_subject)) {
        const auto& s = std::get<doof::Success<std::shared_ptr<::NativeRunResult>>>(_case_subject);
        return doof::Success<std::shared_ptr<ExecResult>>{ std::make_shared<ExecResult>(s.value->exitCode(), s.value->standardOutput(), s.value->standardError(), s.value->stdoutTruncated(), s.value->stderrTruncated()) };
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
        return doof::Failure<std::string>{ f.error };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
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
