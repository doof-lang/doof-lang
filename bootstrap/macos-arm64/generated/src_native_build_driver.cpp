#include "src_native_build_driver.hpp"
#include <cmath>
#include "src_emitter_project.hpp"
#include "src_native_build.hpp"
#include "src_native_build_state.hpp"
#include "src_pkg_config.hpp"
#include "std_blob_index.hpp"
#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_os_index.hpp"
#include "std_http_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_native_build_driver_ {
using namespace ::app_src_emitter_project_;
using namespace ::app_src_native_build_;
using namespace ::app_src_native_build_state_;
using namespace ::app_src_pkg_config_;
using namespace ::std_::blob::index;
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::os::index;
int32_t MAX_NATIVE_OUTPUT_LINES = 40;
int64_t MAX_NATIVE_OUTPUT_BYTES = 262144LL;

doof::JsonObject NativeCommandResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["exitCode"] = doof::json_value(this->exitCode);
    (*_json)["output"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->output->size()); for (const auto& _element : *this->output) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    (*_json)["error"] = doof::json_value(this->error);
    (*_json)["truncated"] = doof::json_value(this->truncated);
    return _json;
}
doof::Result<std::shared_ptr<NativeCommandResult>, std::string> NativeCommandResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_exitCode = _object->find("exitCode");
    if (_iterator_exitCode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"exitCode\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_exitCode->second) : doof::json_is_number(_iterator_exitCode->second)))) { return doof::Failure<std::string>{"Field \"exitCode\" expected number but got " + std::string(doof::json_type_name(_iterator_exitCode->second))}; }
    auto _field_exitCode = (_lenient ? doof::json_as_int_lenient(_iterator_exitCode->second) : doof::json_as_int(_iterator_exitCode->second));
    std::optional<std::shared_ptr<std::vector<uint8_t>>> _field_output;
    if (auto _iterator_output = _object->find("output"); _iterator_output != _object->end()) {
        if (!(doof::json_is_array(_iterator_output->second))) { return doof::Failure<std::string>{"Field \"output\" expected array but got " + std::string(doof::json_type_name(_iterator_output->second))}; }
        _field_output = [&]() { const auto* _array = doof::json_as_array(_iterator_output->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    }
    std::optional<std::string> _field_error;
    if (auto _iterator_error = _object->find("error"); _iterator_error != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_error->second) : doof::json_is_string(_iterator_error->second)))) { return doof::Failure<std::string>{"Field \"error\" expected string but got " + std::string(doof::json_type_name(_iterator_error->second))}; }
        _field_error = (_lenient ? doof::json_as_string_lenient(_iterator_error->second) : doof::json_as_string(_iterator_error->second));
    } else {
        _field_error = std::string("");
    }
    auto _iterator_truncated = _object->find("truncated");
    if (_iterator_truncated == _object->end()) { return doof::Failure<std::string>{"Missing required field \"truncated\""}; }
    if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_truncated->second) : doof::json_is_boolean(_iterator_truncated->second)))) { return doof::Failure<std::string>{"Field \"truncated\" expected boolean but got " + std::string(doof::json_type_name(_iterator_truncated->second))}; }
    auto _field_truncated = (_lenient ? doof::json_as_bool_lenient(_iterator_truncated->second) : doof::json_as_bool(_iterator_truncated->second));
    return doof::Success<std::shared_ptr<NativeCommandResult>>{std::make_shared<NativeCommandResult>(_field_exitCode, _field_output.value(), _field_error.value(), _field_truncated)};
}

doof::JsonObject NativeCompilerBatchResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["exitCode"] = doof::json_value(this->exitCode);
    (*_json)["outputs"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->outputs->size()); for (const auto& _element : *this->outputs) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<NativeCompilerBatchResult>, std::string> NativeCompilerBatchResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_exitCode = _object->find("exitCode");
    if (_iterator_exitCode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"exitCode\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_exitCode->second) : doof::json_is_number(_iterator_exitCode->second)))) { return doof::Failure<std::string>{"Field \"exitCode\" expected number but got " + std::string(doof::json_type_name(_iterator_exitCode->second))}; }
    auto _field_exitCode = (_lenient ? doof::json_as_int_lenient(_iterator_exitCode->second) : doof::json_as_int(_iterator_exitCode->second));
    auto _iterator_outputs = _object->find("outputs");
    if (_iterator_outputs == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputs\""}; }
    if (!(doof::json_is_array(_iterator_outputs->second))) { return doof::Failure<std::string>{"Field \"outputs\" expected array but got " + std::string(doof::json_type_name(_iterator_outputs->second))}; }
    auto _field_outputs = [&]() { const auto* _array = doof::json_as_array(_iterator_outputs->second); auto _values = std::make_shared<std::vector<std::shared_ptr<NativeCommandResult>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(NativeCommandResult::fromJsonValue(_element, _lenient))); } return _values; }();
    return doof::Success<std::shared_ptr<NativeCompilerBatchResult>>{std::make_shared<NativeCompilerBatchResult>(_field_exitCode, _field_outputs)};
}

doof::JsonObject NativeCompilerIdentity::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["command"] = doof::json_value(this->command);
    (*_json)["signature"] = doof::json_value(this->signature);
    return _json;
}
doof::Result<std::shared_ptr<NativeCompilerIdentity>, std::string> NativeCompilerIdentity::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_command = _object->find("command");
    if (_iterator_command == _object->end()) { return doof::Failure<std::string>{"Missing required field \"command\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_command->second) : doof::json_is_string(_iterator_command->second)))) { return doof::Failure<std::string>{"Field \"command\" expected string but got " + std::string(doof::json_type_name(_iterator_command->second))}; }
    auto _field_command = (_lenient ? doof::json_as_string_lenient(_iterator_command->second) : doof::json_as_string(_iterator_command->second));
    auto _iterator_signature = _object->find("signature");
    if (_iterator_signature == _object->end()) { return doof::Failure<std::string>{"Missing required field \"signature\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_signature->second) : doof::json_is_string(_iterator_signature->second)))) { return doof::Failure<std::string>{"Field \"signature\" expected string but got " + std::string(doof::json_type_name(_iterator_signature->second))}; }
    auto _field_signature = (_lenient ? doof::json_as_string_lenient(_iterator_signature->second) : doof::json_as_string(_iterator_signature->second));
    return doof::Success<std::shared_ptr<NativeCompilerIdentity>>{std::make_shared<NativeCompilerIdentity>(_field_command, _field_signature)};
}
std::shared_ptr<NativeCommandResult> runBuildCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments) {
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, MAX_NATIVE_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return std::make_shared<NativeCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error, false);
    }
    const auto executed = doof::success_value(_binding_value_1);
    return std::make_shared<NativeCommandResult>(executed->exitCode, executed->stdout, std::string(""), executed->stdoutTruncated);
}
int32_t printBuildOutput(std::shared_ptr<NativeCommandResult> result, int32_t remainingLines) {
    auto remaining = remainingLines;
    const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
    const auto& _iterable_2 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_2) {
        if (line == std::string("")) {
            continue;
        }
        if (remaining <= 0) {
            return 0;
        }
        doof::println(line);
        (remaining -= 1);
    }
    return remaining;
}

std::shared_ptr<NativeCompilerBatchResult> NativeCompilerWorker::compile() {
    std::shared_ptr<std::vector<std::shared_ptr<NativeCommandResult>>> outputs = std::make_shared<std::vector<std::shared_ptr<NativeCommandResult>>>(std::vector<std::shared_ptr<NativeCommandResult>>{});
    const auto& _iterable_3 = this->tasks;
    for (const auto& task : *_iterable_3) {
        const auto result = runBuildCommand(task->compiler, mutableArguments(task->arguments));
        outputs->push_back(result);
        if (result->exitCode != 0) {
            return std::make_shared<NativeCompilerBatchResult>(result->exitCode, doof::array_buildReadonly(outputs, "", 0));
        }
    }
    return std::make_shared<NativeCompilerBatchResult>(0, doof::array_buildReadonly(outputs, "", 0));
}
doof::JsonObject NativeCompilerWorker::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["tasks"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->tasks->size()); for (const auto& _element : *this->tasks) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<NativeCompilerWorker>, std::string> NativeCompilerWorker::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_tasks = _object->find("tasks");
    if (_iterator_tasks == _object->end()) { return doof::Failure<std::string>{"Missing required field \"tasks\""}; }
    if (!(doof::json_is_array(_iterator_tasks->second))) { return doof::Failure<std::string>{"Field \"tasks\" expected array but got " + std::string(doof::json_type_name(_iterator_tasks->second))}; }
    auto _field_tasks = [&]() { const auto* _array = doof::json_as_array(_iterator_tasks->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_native_build_::NativeCompileTask::fromJsonValue(_element, _lenient))); } return _values; }();
    return doof::Success<std::shared_ptr<NativeCompilerWorker>>{std::make_shared<NativeCompilerWorker>(_field_tasks)};
}
int32_t buildNativeProject(std::string compilerOverride, std::string outputDirectory, std::string outputPath, std::shared_ptr<::app_src_emitter_project_::ProjectEmission> project, bool release, std::string platform) {
    const auto& _iterable_4 = project->nativeBuild->pkgConfigPackages;
    for (const auto& packageName : *_iterable_4) {
        const auto& _iterable_5 = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("cflags"), std::string("libs")});
        for (const auto& mode : *_iterable_5) {
            const auto pkgConfigResult = runBuildCommand(std::string("pkg-config"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{(std::string("--") + mode), packageName}));
            const auto output = ::doof_blob::NativeBlobReader::constructor(pkgConfigResult->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((pkgConfigResult->output)->size())));
            const auto applied = ::app_src_pkg_config_::applyPkgConfigResult(project->nativeBuild, packageName, mode, std::make_shared<::app_src_pkg_config_::PkgConfigCommandResult>(pkgConfigResult->exitCode, output, pkgConfigResult->error));
            auto _binding_value_6 = applied;
            if (doof::is_failure(_binding_value_6)) {
                const auto error = doof::failure_error(_binding_value_6);
                doof::println((std::string("error: ") + error));
                return 1;
            }
        }
    }
    const auto wasm = doof::string_endsWith(outputPath, std::string(".wasm"));
    auto compiler = compilerOverride;
    if ((compiler == std::string("")) && wasm) {
        (compiler = std::string("em++"));
    }
    if (compiler == std::string("")) {
        const auto configured = envCompiler();
        if (configured != std::string("")) {
            (compiler = configured);
        }
    }
    if (compiler == std::string("")) {
        (compiler = std::string("c++"));
    }
    const auto plan = ::app_src_native_build_::planNativeCompile(compiler, outputDirectory, outputPath, project->modules, project->nativeBuild, release, platform, project->wasmExportNames, wasm);
    return executeNativePlan(outputDirectory, plan, project);
}
std::string envCompiler() {
    auto _binding_value_7 = ::std_::os::index::env(std::string("CXX"));
    if (doof::is_failure(_binding_value_7)) {
        const auto& value = _binding_value_7;
        return std::string("");
    }
    const auto value = doof::success_value(_binding_value_7);
    return value;
}
int32_t executeNativePlan(std::string outputDirectory, std::shared_ptr<::app_src_native_build_::NativeCompilePlan> plan, std::shared_ptr<::app_src_emitter_project_::ProjectEmission> project) {
    const auto statePath = joinOutput(outputDirectory, std::string(".doof-native-build-state.json"));
    const auto previousState = readBuildState(statePath);
    const auto nextState = std::make_shared<::app_src_native_build_state_::NativeBuildState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities = std::make_shared<std::vector<std::shared_ptr<NativeCompilerIdentity>>>(std::vector<std::shared_ptr<NativeCompilerIdentity>>{});
    auto remainingOutputLines = MAX_NATIVE_OUTPUT_LINES;
    auto truncationReported = false;
    auto pchChanged = false;
    if (!doof::is_null(plan->precompiledHeaderTask)) {
        const auto pchTask = doof::unwrap_optional(plan->precompiledHeaderTask);
        ensureDirectory(parentDirectory(pchTask->outputPath));
        const auto pchFingerprint = taskFingerprint(pchTask, identities);
        const auto pchPrevious = ::app_src_native_build_state_::findNativeTaskState(previousState, pchTask->id);
        if (!taskIsCurrent(pchPrevious, pchFingerprint)) {
            (pchChanged = true);
            const auto pchResult = runBuildCommand(pchTask->compiler, mutableArguments(pchTask->arguments));
            (remainingOutputLines = printBuildOutput(pchResult, remainingOutputLines));
            if (pchResult->truncated) {
                doof::println(((std::string("... native compiler output capture truncated after ") + doof::to_string(MAX_NATIVE_OUTPUT_BYTES)) + std::string(" bytes")));
                (truncationReported = true);
            }
            if (pchResult->exitCode != 0) {
                doof::println((std::string("error: native compiler failed to build the precompiled runtime header with code ") + doof::to_string(pchResult->exitCode)));
                return pchResult->exitCode;
            }
            nextState->tasks->push_back(captureTaskState(pchTask, pchFingerprint));
        } else {
            nextState->tasks->push_back(doof::unwrap_optional(pchPrevious));
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>> dirtyTasks = std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>>(std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>{});
    std::shared_ptr<std::vector<std::string>> dirtyTaskIds = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> taskFingerprints = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_8 = plan->compileTasks;
    for (const auto& task : *_iterable_8) {
        const auto fingerprint = taskFingerprint(task, identities);
        taskFingerprints->push_back(fingerprint);
        const auto previous = ::app_src_native_build_state_::findNativeTaskState(previousState, task->id);
        if ((task->usesPrecompiledHeader && pchChanged) || !taskIsCurrent(previous, fingerprint)) {
            dirtyTasks->push_back(task);
            dirtyTaskIds->push_back(task->id);
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>> workers = std::make_shared<std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>>(std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>{});
    std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>> promises = std::make_shared<std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>>(std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>{});
    const auto& _iterable_9 = dirtyTasks;
    for (const auto& task : *_iterable_9) {
        ensureDirectory(parentDirectory(task->outputPath));
    }
    const auto& _iterable_10 = ::app_src_native_build_::batchNativeCompileTasks(dirtyTasks, 8);
    for (const auto& batch : *_iterable_10) {
        const auto worker = std::make_shared<doof::Actor<NativeCompilerWorker>>(NativeCompilerWorker{batch});
        workers->push_back(worker);
        promises->push_back(worker->template call_async<std::shared_ptr<NativeCompilerBatchResult>>([](NativeCompilerWorker& _self) -> std::shared_ptr<NativeCompilerBatchResult> { return _self.compile(); }));
    }
    auto compileExitCode = 0;
    for (int32_t index = 0; index < static_cast<int32_t>((promises)->size()); ++index) {
        auto _binding_value_11 = (*promises)[index].get();
        if (doof::is_failure(_binding_value_11)) {
            const auto error = doof::failure_error(_binding_value_11);
            const auto ignoredWorker = (*workers)[index]->retire();
            doof::println((std::string("error: native compiler worker failed: ") + error));
            return 1;
        }
        const auto batchResult = doof::success_value(_binding_value_11);
        (*workers)[index]->retire();
        const auto& _iterable_12 = batchResult->outputs;
        for (const auto& commandResult : *_iterable_12) {
            (remainingOutputLines = printBuildOutput(commandResult, remainingOutputLines));
            if (commandResult->truncated && !truncationReported) {
                doof::println(((std::string("... native compiler output capture truncated after ") + doof::to_string(MAX_NATIVE_OUTPUT_BYTES)) + std::string(" bytes")));
                (truncationReported = true);
            }
        }
        if ((compileExitCode == 0) && (batchResult->exitCode != 0)) {
            (compileExitCode = batchResult->exitCode);
        }
    }
    if ((remainingOutputLines == 0) && !truncationReported) {
        doof::println(((std::string("... native compiler output truncated after ") + doof::to_string(MAX_NATIVE_OUTPUT_LINES)) + std::string(" lines")));
    }
    if (compileExitCode != 0) {
        doof::println((std::string("error: native object compiler exited with code ") + doof::to_string(compileExitCode)));
        return compileExitCode;
    }
    std::shared_ptr<std::vector<std::string>> objectPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    for (int32_t index = 0; index < static_cast<int32_t>((plan->compileTasks)->size()); ++index) {
        const auto task = (*plan->compileTasks)[index];
        objectPaths->push_back(task->outputPath);
        if (contains(dirtyTaskIds, task->id)) {
            nextState->tasks->push_back(captureTaskState(task, (*taskFingerprints)[index]));
        } else {
            nextState->tasks->push_back(doof::unwrap_optional(::app_src_native_build_state_::findNativeTaskState(previousState, task->id)));
        }
    }
    const auto linkId = (std::string("link:") + plan->outputPath);
    const auto computedLinkFingerprint = linkFingerprint(plan->linker, plan->linkArguments, plan->outputPath, identities);
    const auto linkPrevious = ::app_src_native_build_state_::findNativeTaskState(previousState, linkId);
    if ((static_cast<int32_t>((dirtyTasks)->size()) > 0) || !taskIsCurrent(linkPrevious, computedLinkFingerprint)) {
        const auto linkResult = runBuildCommand(plan->linker, plan->linkArguments);
        const auto ignored = printBuildOutput(linkResult, remainingOutputLines);
        if (linkResult->truncated && !truncationReported) {
            doof::println(((std::string("... native linker output capture truncated after ") + doof::to_string(MAX_NATIVE_OUTPUT_BYTES)) + std::string(" bytes")));
        }
        if (linkResult->exitCode != 0) {
            doof::println((std::string("error: native linker exited with code ") + doof::to_string(linkResult->exitCode)));
            return linkResult->exitCode;
        }
        nextState->tasks->push_back(captureLinkState(plan->outputPath, computedLinkFingerprint, objectPaths));
    } else {
        nextState->tasks->push_back(doof::unwrap_optional(linkPrevious));
    }
    collectManagedOutputs(nextState->managedOutputs, outputDirectory, plan, project);
    removeStaleOutputs(previousState->managedOutputs, nextState->managedOutputs, outputDirectory);
    writeBuildState(statePath, nextState);
    return 0;
}
std::string compilerIdentity(std::string command, std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities) {
    const auto& _iterable_13 = identities;
    for (const auto& identity : *_iterable_13) {
        if (identity->command == command) {
            return identity->signature;
        }
    }
    const auto result = runBuildCommand(command, std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--version")}));
    auto description = command;
    if (result->exitCode == 0) {
        (description = ((description + std::string("\n")) + ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size())))));
    }
    const auto signature = ::std_::crypto::index::sha256HexString(description);
    identities->push_back(std::make_shared<NativeCompilerIdentity>(command, signature));
    return signature;
}
std::string taskFingerprint(std::shared_ptr<::app_src_native_build_::NativeCompileTask> task, std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities) {
    auto value = ((task->id + std::string("\n")) + compilerIdentity(task->compiler, identities));
    const auto& _iterable_14 = task->arguments;
    for (const auto& argument : *_iterable_14) {
        (value = ((value + std::string("\n")) + argument));
    }
    return ::std_::crypto::index::sha256HexString(value);
}
std::string linkFingerprint(std::string linker, std::shared_ptr<std::vector<std::string>> arguments, std::string outputPath, std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities) {
    auto value = (((std::string("link:") + outputPath) + std::string("\n")) + compilerIdentity(linker, identities));
    const auto& _iterable_15 = arguments;
    for (const auto& argument : *_iterable_15) {
        (value = ((value + std::string("\n")) + argument));
    }
    return ::std_::crypto::index::sha256HexString(value);
}
std::optional<std::string> pathSignature(std::string path, bool contentHash) {
    if (!::doof_fs::exists(path) || ::doof_fs::isDirectory(path)) {
        return std::nullopt;
    }
    if (contentHash) {
        return ::std_::crypto::index::sha256Hex([&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 232, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
    }
    auto _binding_value_16 = ::doof_fs::metadata(path);
    if (doof::is_failure(_binding_value_16)) {
        const auto& info = _binding_value_16;
        return std::nullopt;
    }
    const auto info = doof::success_value(_binding_value_16);
    return ((doof::to_string(info->size) + std::string(":")) + doof::to_string(info->modifiedAt->toEpochNanos()));
}
bool taskIsCurrent(std::shared_ptr<::app_src_native_build_state_::NativeTaskState> previous, std::string fingerprint) {
    if (doof::is_null(previous) || !::doof_fs::exists(previous->outputPath)) {
        return false;
    }
    auto _binding_value_17 = ::doof_fs::metadata(previous->outputPath);
    if (doof::is_failure(_binding_value_17)) {
        const auto& info = _binding_value_17;
        return false;
    }
    const auto info = doof::success_value(_binding_value_17);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>> currentInputs = std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{});
    const auto& _iterable_18 = previous->inputs;
    for (const auto& input : *_iterable_18) {
        const auto signature = pathSignature(input->path, input->contentHash);
        if (doof::is_null(signature)) {
            return false;
        }
        currentInputs->push_back(std::make_shared<::app_src_native_build_state_::NativeInputSignature>(input->path, signature.value(), input->contentHash));
    }
    return nativeTaskStateIsCurrent(previous, fingerprint, info->size, info->modifiedAt->toEpochNanos(), currentInputs);
}
bool nativeTaskStateIsCurrent(std::shared_ptr<::app_src_native_build_state_::NativeTaskState> previous, std::string fingerprint, int64_t outputSize, int64_t outputModifiedNanos, std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>> currentInputs) {
    if (doof::is_null(previous) || (previous->fingerprint != fingerprint)) {
        return false;
    }
    if ((previous->outputSize != outputSize) || (previous->outputModifiedNanos != outputModifiedNanos)) {
        return false;
    }
    if ((static_cast<int32_t>((previous->inputs)->size()) == 0) || (static_cast<int32_t>((previous->inputs)->size()) != static_cast<int32_t>((currentInputs)->size()))) {
        return false;
    }
    for (int32_t index = 0; index < static_cast<int32_t>((previous->inputs)->size()); ++index) {
        const auto expected = (*previous->inputs)[index];
        const auto current = (*currentInputs)[index];
        if (((expected->path != current->path) || (expected->signature != current->signature)) || (expected->contentHash != current->contentHash)) {
            return false;
        }
    }
    return true;
}
std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureTaskState(std::shared_ptr<::app_src_native_build_::NativeCompileTask> task, std::string fingerprint) {
    const auto info = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(task->outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 269, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    const auto state = std::make_shared<::app_src_native_build_state_::NativeTaskState>(task->id, fingerprint, task->outputPath, info->size, info->modifiedAt->toEpochNanos(), std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{}));
    std::shared_ptr<std::vector<std::string>> paths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{task->sourcePath});
    if ((task->dependencyFilePath != std::string("")) && ::doof_fs::exists(task->dependencyFilePath)) {
        const auto dependencySource = [&]() -> std::string { auto _try_value = ::doof_fs::readText(task->dependencyFilePath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 273, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        const auto& _iterable_19 = ::app_src_native_build_state_::parseMakeDependencies(dependencySource);
        for (const auto& path : *_iterable_19) {
            appendUnique(paths, path);
        }
    }
    const auto& _iterable_20 = paths;
    for (const auto& path : *_iterable_20) {
        const auto signature = pathSignature(path, true);
        if (!doof::is_null(signature)) {
            state->inputs->push_back(std::make_shared<::app_src_native_build_state_::NativeInputSignature>(path, signature.value(), true));
        }
    }
    return state;
}
std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureLinkState(std::string outputPath, std::string fingerprint, std::shared_ptr<std::vector<std::string>> objectPaths) {
    const auto info = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 284, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    const auto state = std::make_shared<::app_src_native_build_state_::NativeTaskState>((std::string("link:") + outputPath), fingerprint, outputPath, info->size, info->modifiedAt->toEpochNanos(), std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{}));
    const auto& _iterable_21 = objectPaths;
    for (const auto& path : *_iterable_21) {
        const auto signature = pathSignature(path, false);
        if (!doof::is_null(signature)) {
            state->inputs->push_back(std::make_shared<::app_src_native_build_state_::NativeInputSignature>(path, signature.value(), false));
        }
    }
    return state;
}
std::shared_ptr<::app_src_native_build_state_::NativeBuildState> readBuildState(std::string path) {
    if (!::doof_fs::exists(path)) {
        return std::make_shared<::app_src_native_build_state_::NativeBuildState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    auto _binding_value_22 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_22)) {
        const auto& source = _binding_value_22;
        return std::make_shared<::app_src_native_build_state_::NativeBuildState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    const auto source = doof::success_value(_binding_value_22);
    const auto parsed = ::app_src_native_build_state_::parseNativeBuildState(source);
    return (doof::is_null(parsed) ? std::make_shared<::app_src_native_build_state_::NativeBuildState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : doof::unwrap_optional(parsed));
}
void writeBuildState(std::string path, std::shared_ptr<::app_src_native_build_state_::NativeBuildState> state) {
    const auto temporaryPath = (path + std::string(".tmp"));
    [&]() -> void { auto _try_value = ::doof_fs::writeText(temporaryPath, ::app_src_native_build_state_::renderNativeBuildState(state)); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 302, std::string("try! failed"));  }();
    [&]() -> void { auto _try_value = ::doof_fs::rename(temporaryPath, path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 303, std::string("try! failed"));  }();
}
void collectManagedOutputs(std::shared_ptr<std::vector<std::string>> outputs, std::string outputDirectory, std::shared_ptr<::app_src_native_build_::NativeCompilePlan> plan, std::shared_ptr<::app_src_emitter_project_::ProjectEmission> project) {
    appendUnique(outputs, joinOutput(outputDirectory, std::string("doof_runtime.hpp")));
    const auto& _iterable_23 = project->modules;
    for (const auto& module : *_iterable_23) {
        appendUnique(outputs, joinOutput(outputDirectory, module->headerName));
        appendUnique(outputs, joinOutput(outputDirectory, module->sourceName));
    }
    const auto& _iterable_24 = project->supportFiles;
    for (const auto& supportFile : *_iterable_24) {
        appendUnique(outputs, joinOutput(outputDirectory, supportFile->relativePath));
    }
    const auto& _iterable_25 = project->nativeCopies;
    for (const auto& nativeCopy : *_iterable_25) {
        collectManagedNativeCopyOutputs(outputs, nativeCopy->sourcePath, joinOutput(outputDirectory, nativeCopy->relativePath));
    }
    if (!doof::is_null(plan->precompiledHeaderTask)) {
        appendUnique(outputs, plan->precompiledHeaderTask->outputPath);
        if (plan->precompiledHeaderTask->dependencyFilePath != std::string("")) {
            appendUnique(outputs, plan->precompiledHeaderTask->dependencyFilePath);
        }
    }
    const auto& _iterable_26 = plan->compileTasks;
    for (const auto& task : *_iterable_26) {
        appendUnique(outputs, task->outputPath);
        if (task->dependencyFilePath != std::string("")) {
            appendUnique(outputs, task->dependencyFilePath);
        }
    }
    appendUnique(outputs, plan->outputPath);
}
void collectManagedNativeCopyOutputs(std::shared_ptr<std::vector<std::string>> outputs, std::string sourcePath, std::string outputPath) {
    if (!::doof_fs::isDirectory(sourcePath)) {
        appendUnique(outputs, outputPath);
        return;
    }
    const auto& _iterable_27 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 332, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    for (const auto& entry : *_iterable_27) {
        collectManagedNativeCopyOutputs(outputs, joinOutput(sourcePath, entry->name), joinOutput(outputPath, entry->name));
    }
}
void removeStaleOutputs(std::shared_ptr<std::vector<std::string>> previous, std::shared_ptr<std::vector<std::string>> current, std::string outputDirectory) {
    const auto prefix = (doof::string_endsWith(outputDirectory, std::string("/")) ? outputDirectory : (outputDirectory + std::string("/")));
    const auto& _iterable_28 = previous;
    for (const auto& path : *_iterable_28) {
        if (((contains(current, path) || !doof::string_startsWith(path, prefix)) || !::doof_fs::exists(path)) || ::doof_fs::isDirectory(path)) {
            continue;
        }
        [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 341, std::string("try! failed"));  }();
    }
}
std::shared_ptr<std::vector<std::string>> mutableArguments(std::shared_ptr<std::vector<std::string>> arguments) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_29 = arguments;
    for (const auto& argument : *_iterable_29) {
        result->push_back(argument);
    }
    return result;
}
bool contains(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    const auto& _iterable_30 = values;
    for (const auto& existing : *_iterable_30) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}
void appendUnique(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    if (!contains(values, value)) {
        values->push_back(value);
    }
}
std::string joinOutput(std::string directory, std::string name) {
    return (doof::string_endsWith(directory, std::string("/")) ? (directory + name) : ((directory + std::string("/")) + name));
}
std::string parentDirectory(std::string path) {
    auto index = (static_cast<int32_t>(path.size()) - 1);
    while ((index > 0) && (path[index] != U'\u002F')) {
        (index -= 1);
    }
    return ((index <= 0) ? std::string("/") : doof::string_substring(path, 0, index));
}
void ensureDirectory(std::string path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return;
    }
    const auto parent = parentDirectory(path);
    if (parent != path) {
        ensureDirectory(parent);
    }
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 371, std::string("try! failed"));  }();
}
}
