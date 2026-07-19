#include "std_os_index.hpp"
#include <cmath>
#include "std_time_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_stream_index.hpp"

namespace std_::os::index {
using namespace ::std_::time::index;
doof::Result<std::string, std::string> env(std::string name) {
    return _env(name);
}
int32_t pid() {
    return _pid();
}
std::string platform() {
    return _platform();
}
std::string architecture() {
    return _architecture();
}

doof::JsonObject ExecOptions::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["cwd"] = (this->cwd.has_value() ? doof::json_value(this->cwd.value()) : doof::json_value(nullptr));
    (*_json)["env"] = [&]() { auto _object_value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *this->env) { (*_object_value)[_entry.first] = doof::json_value(_entry.second); } return doof::json_value(_object_value); }();
    (*_json)["inheritEnv"] = doof::json_value(this->inheritEnv);
    (*_json)["withStdin"] = doof::json_value(this->withStdin);
    (*_json)["mergeStderrIntoStdout"] = doof::json_value(this->mergeStderrIntoStdout);
    (*_json)["inheritOutput"] = doof::json_value(this->inheritOutput);
    (*_json)["maxOutputBytes"] = (this->maxOutputBytes.has_value() ? doof::json_value(this->maxOutputBytes.value()) : doof::json_value(nullptr));
    (*_json)["timeout"] = (this->timeout ? doof::json_value(this->timeout->toJsonObject()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<ExecOptions>, std::string> ExecOptions::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::optional<std::string>> _field_cwd;
    if (auto _iterator_cwd = _object->find("cwd"); _iterator_cwd != _object->end()) {
        if (!(doof::json_is_null(_iterator_cwd->second) || (_lenient ? doof::json_is_lenient_string(_iterator_cwd->second) : doof::json_is_string(_iterator_cwd->second)))) { return doof::Failure<std::string>{"Field \"cwd\" expected string or null but got " + std::string(doof::json_type_name(_iterator_cwd->second))}; }
        _field_cwd = (doof::json_is_null(_iterator_cwd->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_cwd->second) : doof::json_as_string(_iterator_cwd->second))});
    } else {
        _field_cwd = std::optional<std::string>{std::nullopt};
    }
    std::optional<std::shared_ptr<doof::ordered_map<std::string, std::string>>> _field_env;
    if (auto _iterator_env = _object->find("env"); _iterator_env != _object->end()) {
        if (!(doof::json_is_object(_iterator_env->second))) { return doof::Failure<std::string>{"Field \"env\" expected object but got " + std::string(doof::json_type_name(_iterator_env->second))}; }
        _field_env = [&]() { const auto* _object_value = doof::json_as_object(_iterator_env->second); auto _values = std::make_shared<doof::ordered_map<std::string, std::string>>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = (_lenient ? doof::json_as_string_lenient(_entry.second) : doof::json_as_string(_entry.second)); } return _values; }();
    } else {
        _field_env = std::shared_ptr<doof::ordered_map<std::string, std::string>>{std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{})};
    }
    std::optional<bool> _field_inheritEnv;
    if (auto _iterator_inheritEnv = _object->find("inheritEnv"); _iterator_inheritEnv != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_inheritEnv->second) : doof::json_is_boolean(_iterator_inheritEnv->second)))) { return doof::Failure<std::string>{"Field \"inheritEnv\" expected boolean but got " + std::string(doof::json_type_name(_iterator_inheritEnv->second))}; }
        _field_inheritEnv = (_lenient ? doof::json_as_bool_lenient(_iterator_inheritEnv->second) : doof::json_as_bool(_iterator_inheritEnv->second));
    } else {
        _field_inheritEnv = bool{true};
    }
    std::optional<bool> _field_withStdin;
    if (auto _iterator_withStdin = _object->find("withStdin"); _iterator_withStdin != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_withStdin->second) : doof::json_is_boolean(_iterator_withStdin->second)))) { return doof::Failure<std::string>{"Field \"withStdin\" expected boolean but got " + std::string(doof::json_type_name(_iterator_withStdin->second))}; }
        _field_withStdin = (_lenient ? doof::json_as_bool_lenient(_iterator_withStdin->second) : doof::json_as_bool(_iterator_withStdin->second));
    } else {
        _field_withStdin = bool{true};
    }
    std::optional<bool> _field_mergeStderrIntoStdout;
    if (auto _iterator_mergeStderrIntoStdout = _object->find("mergeStderrIntoStdout"); _iterator_mergeStderrIntoStdout != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_mergeStderrIntoStdout->second) : doof::json_is_boolean(_iterator_mergeStderrIntoStdout->second)))) { return doof::Failure<std::string>{"Field \"mergeStderrIntoStdout\" expected boolean but got " + std::string(doof::json_type_name(_iterator_mergeStderrIntoStdout->second))}; }
        _field_mergeStderrIntoStdout = (_lenient ? doof::json_as_bool_lenient(_iterator_mergeStderrIntoStdout->second) : doof::json_as_bool(_iterator_mergeStderrIntoStdout->second));
    } else {
        _field_mergeStderrIntoStdout = bool{false};
    }
    std::optional<bool> _field_inheritOutput;
    if (auto _iterator_inheritOutput = _object->find("inheritOutput"); _iterator_inheritOutput != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_inheritOutput->second) : doof::json_is_boolean(_iterator_inheritOutput->second)))) { return doof::Failure<std::string>{"Field \"inheritOutput\" expected boolean but got " + std::string(doof::json_type_name(_iterator_inheritOutput->second))}; }
        _field_inheritOutput = (_lenient ? doof::json_as_bool_lenient(_iterator_inheritOutput->second) : doof::json_as_bool(_iterator_inheritOutput->second));
    } else {
        _field_inheritOutput = bool{false};
    }
    std::optional<std::optional<int64_t>> _field_maxOutputBytes;
    if (auto _iterator_maxOutputBytes = _object->find("maxOutputBytes"); _iterator_maxOutputBytes != _object->end()) {
        if (!(doof::json_is_null(_iterator_maxOutputBytes->second) || (_lenient ? doof::json_is_lenient_number(_iterator_maxOutputBytes->second) : doof::json_is_number(_iterator_maxOutputBytes->second)))) { return doof::Failure<std::string>{"Field \"maxOutputBytes\" expected number or null but got " + std::string(doof::json_type_name(_iterator_maxOutputBytes->second))}; }
        _field_maxOutputBytes = (doof::json_is_null(_iterator_maxOutputBytes->second) ? std::optional<int64_t>{std::nullopt} : std::optional<int64_t>{(_lenient ? doof::json_as_long_lenient(_iterator_maxOutputBytes->second) : doof::json_as_long(_iterator_maxOutputBytes->second))});
    } else {
        _field_maxOutputBytes = std::optional<int64_t>{std::nullopt};
    }
    std::optional<std::shared_ptr<::std_::time::duration::Duration>> _field_timeout;
    if (auto _iterator_timeout = _object->find("timeout"); _iterator_timeout != _object->end()) {
        if (!(doof::json_is_null(_iterator_timeout->second) || doof::json_is_object(_iterator_timeout->second))) { return doof::Failure<std::string>{"Field \"timeout\" expected object or null but got " + std::string(doof::json_type_name(_iterator_timeout->second))}; }
        _field_timeout = (doof::json_is_null(_iterator_timeout->second) ? nullptr : doof::success_value(::std_::time::duration::Duration::fromJsonValue(_iterator_timeout->second, _lenient)));
    } else {
        _field_timeout = std::shared_ptr<::std_::time::duration::Duration>{nullptr};
    }
    return doof::Success<std::shared_ptr<ExecOptions>>{std::make_shared<ExecOptions>(_field_cwd.value(), _field_env.value(), _field_inheritEnv.value(), _field_withStdin.value(), _field_mergeStderrIntoStdout.value(), _field_inheritOutput.value(), _field_maxOutputBytes.value(), _field_timeout.value())};
}
doof::Result<std::shared_ptr<::NativeExecProcess>, std::string> spawnNative(std::string command, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<ExecOptions> options) {
    const std::shared_ptr<std::vector<std::string>> envKeys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const std::shared_ptr<std::vector<std::string>> envValues = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_1 = options->env;
    for (const auto& [key, value] : *_iterable_1) {
        envKeys->push_back(key);
        envValues->push_back(value);
    }
    std::optional<int64_t> timeoutNanos = std::nullopt;
    if (!doof::is_null(options->timeout)) {
        (timeoutNanos = options->timeout->toNanos());
    }
    return ::NativeExecProcess::spawn(command, args, options->cwd, envKeys, envValues, options->inheritEnv, options->withStdin, options->mergeStderrIntoStdout, options->inheritOutput, options->maxOutputBytes, timeoutNanos);
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

doof::Result<std::shared_ptr<Exec>, std::string> Exec::spawn(std::string command, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<ExecOptions> options) {
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
doof::Result<void, std::string> Exec::writeStdinText(std::string value) {
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

doof::JsonObject ExecResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["exitCode"] = doof::json_value(this->exitCode);
    (*_json)["stdout"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->stdout->size()); for (const auto& _element : *this->stdout) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    (*_json)["stderr"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->stderr->size()); for (const auto& _element : *this->stderr) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    (*_json)["stdoutTruncated"] = doof::json_value(this->stdoutTruncated);
    (*_json)["stderrTruncated"] = doof::json_value(this->stderrTruncated);
    return _json;
}
doof::Result<std::shared_ptr<ExecResult>, std::string> ExecResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_exitCode = _object->find("exitCode");
    if (_iterator_exitCode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"exitCode\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_exitCode->second) : doof::json_is_number(_iterator_exitCode->second)))) { return doof::Failure<std::string>{"Field \"exitCode\" expected number but got " + std::string(doof::json_type_name(_iterator_exitCode->second))}; }
    auto _field_exitCode = (_lenient ? doof::json_as_int_lenient(_iterator_exitCode->second) : doof::json_as_int(_iterator_exitCode->second));
    auto _iterator_stdout = _object->find("stdout");
    if (_iterator_stdout == _object->end()) { return doof::Failure<std::string>{"Missing required field \"stdout\""}; }
    if (!(doof::json_is_array(_iterator_stdout->second))) { return doof::Failure<std::string>{"Field \"stdout\" expected array but got " + std::string(doof::json_type_name(_iterator_stdout->second))}; }
    auto _field_stdout = [&]() { const auto* _array = doof::json_as_array(_iterator_stdout->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    auto _iterator_stderr = _object->find("stderr");
    if (_iterator_stderr == _object->end()) { return doof::Failure<std::string>{"Missing required field \"stderr\""}; }
    if (!(doof::json_is_array(_iterator_stderr->second))) { return doof::Failure<std::string>{"Field \"stderr\" expected array but got " + std::string(doof::json_type_name(_iterator_stderr->second))}; }
    auto _field_stderr = [&]() { const auto* _array = doof::json_as_array(_iterator_stderr->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    std::optional<bool> _field_stdoutTruncated;
    if (auto _iterator_stdoutTruncated = _object->find("stdoutTruncated"); _iterator_stdoutTruncated != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_stdoutTruncated->second) : doof::json_is_boolean(_iterator_stdoutTruncated->second)))) { return doof::Failure<std::string>{"Field \"stdoutTruncated\" expected boolean but got " + std::string(doof::json_type_name(_iterator_stdoutTruncated->second))}; }
        _field_stdoutTruncated = (_lenient ? doof::json_as_bool_lenient(_iterator_stdoutTruncated->second) : doof::json_as_bool(_iterator_stdoutTruncated->second));
    } else {
        _field_stdoutTruncated = bool{false};
    }
    std::optional<bool> _field_stderrTruncated;
    if (auto _iterator_stderrTruncated = _object->find("stderrTruncated"); _iterator_stderrTruncated != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_stderrTruncated->second) : doof::json_is_boolean(_iterator_stderrTruncated->second)))) { return doof::Failure<std::string>{"Field \"stderrTruncated\" expected boolean but got " + std::string(doof::json_type_name(_iterator_stderrTruncated->second))}; }
        _field_stderrTruncated = (_lenient ? doof::json_as_bool_lenient(_iterator_stderrTruncated->second) : doof::json_as_bool(_iterator_stderrTruncated->second));
    } else {
        _field_stderrTruncated = bool{false};
    }
    return doof::Success<std::shared_ptr<ExecResult>>{std::make_shared<ExecResult>(_field_exitCode, _field_stdout, _field_stderr, _field_stdoutTruncated.value(), _field_stderrTruncated.value())};
}
doof::Result<std::shared_ptr<ExecResult>, std::string> run(std::string command, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<ExecOptions> options) {
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
        return doof::Success<std::shared_ptr<ExecResult>>{ std::make_shared<ExecResult>(s.value->exitCode(), s.value->stdout(), s.value->stderr(), s.value->stdoutTruncated(), s.value->stderrTruncated()) };
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
        return doof::Failure<std::string>{ f.error };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
doof::Result<std::string, std::string> _env(std::string name) {
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
