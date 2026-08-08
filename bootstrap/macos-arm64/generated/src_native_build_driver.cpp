#include "src_native_build_driver.hpp"

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
    (*_json)["quietSourcePath"] = doof::json_value(this->quietSourcePath);
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
    std::optional<std::string> _field_quietSourcePath;
    if (auto _iterator_quietSourcePath = _object->find("quietSourcePath"); _iterator_quietSourcePath != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_quietSourcePath->second) : doof::json_is_string(_iterator_quietSourcePath->second)))) { return doof::Failure<std::string>{"Field \"quietSourcePath\" expected string but got " + std::string(doof::json_type_name(_iterator_quietSourcePath->second))}; }
        _field_quietSourcePath = (_lenient ? doof::json_as_string_lenient(_iterator_quietSourcePath->second) : doof::json_as_string(_iterator_quietSourcePath->second));
    } else {
        _field_quietSourcePath = std::string("");
    }
    return doof::Success<std::shared_ptr<NativeCommandResult>>{std::make_shared<NativeCommandResult>(_field_exitCode, _field_output.value(), _field_error.value(), _field_truncated, _field_quietSourcePath.value())};
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
std::shared_ptr<NativeCommandResult> runBuildCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& quietSourcePath) {
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_NATIVE_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return std::make_shared<NativeCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error, false, std::string(""));
    }
    const auto executed = doof::success_value(_binding_value_1);
    return std::make_shared<NativeCommandResult>(executed->exitCode, executed->stdout_, std::string(""), executed->stdoutTruncated, quietSourcePath);
}
bool isMsvcSourceEcho(const std::string& line, const std::string& sourcePath) {
    if (sourcePath == std::string("")) {
        return false;
    }
    const auto normalizedLine = doof::string_replaceAll(doof::string_trim(line), std::string("\\"), std::string("/"));
    const auto normalizedSource = doof::string_replaceAll(sourcePath, std::string("\\"), std::string("/"));
    auto slash = -1;
    for (int32_t index = 0; index < static_cast<int32_t>(normalizedSource.size()); ++index) {
        if (doof::string_at(normalizedSource, index, "src/native-build-driver", 64) == U'\u002F') {
            (slash = index);
        }
    }
    const auto sourceName = ((slash < 0) ? normalizedSource : doof::string_substring(normalizedSource, (slash + 1), static_cast<int32_t>(normalizedSource.size())));
    return ((normalizedLine == normalizedSource) || (normalizedLine == sourceName));
}
int32_t printBuildOutput(const std::shared_ptr<NativeCommandResult>& result, int32_t remainingLines) {
    auto remaining = remainingLines;
    const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
    const auto& _iterable_2 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_2) {
        if (line == std::string("")) {
            continue;
        }
        if (isMsvcSourceEcho(line, result->quietSourcePath)) {
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
        const auto result = runBuildCommand(task->compiler, mutableArguments(task->arguments), (::app_src_native_build_::isMsvcCompiler(task->compiler) ? task->sourcePath : std::string("")));
        outputs->push_back(result);
        if (result->exitCode != 0) {
            return std::make_shared<NativeCompilerBatchResult>(result->exitCode, doof::array_drainToReadonly(outputs, "", 0));
        }
    }
    return std::make_shared<NativeCompilerBatchResult>(0, doof::array_drainToReadonly(outputs, "", 0));
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
int32_t buildNativeProject(const std::string& compilerOverride, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project, bool release, const std::string& platform) {
    const auto& _iterable_4 = project->nativeBuild->pkgConfigPackages;
    for (const auto& packageName : *_iterable_4) {
        const auto& _iterable_5 = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("cflags"), std::string("libs")});
        for (const auto& mode : *_iterable_5) {
            const auto pkgConfigResult = runBuildCommand(std::string("pkg-config"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{(std::string("--") + mode), packageName}), std::string(""));
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
        (compiler = ((platform == std::string("windows")) ? std::string("cl.exe") : std::string("c++")));
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
int32_t executeNativePlan(const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project) {
    const auto& _iterable_8 = plan->supportFiles;
    for (const auto& supportFile : *_iterable_8) {
        ensureDirectory(parentDirectory(supportFile->outputPath));
        writeTextIfChanged(supportFile->outputPath, supportFile->content);
    }
    const auto statePath = joinOutput(outputDirectory, std::string(".doof-native-build-state.json"));
    const auto previousState = readBuildState(statePath);
    const auto previousTasks = indexNativeTaskStates(previousState);
    const auto nextState = std::make_shared<::app_src_native_build_state_::NativeBuildState>(2, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities = std::make_shared<std::vector<std::shared_ptr<NativeCompilerIdentity>>>(std::vector<std::shared_ptr<NativeCompilerIdentity>>{});
    auto remainingOutputLines = MAX_NATIVE_OUTPUT_LINES;
    auto truncationReported = false;
    auto pchChanged = false;
    if (!doof::is_null(plan->precompiledHeaderTask)) {
        const auto pchTask = doof::unwrap_optional(plan->precompiledHeaderTask);
        ensureDirectory(parentDirectory(pchTask->outputPath));
        const auto pchFingerprint = taskFingerprint(pchTask, identities);
        const auto pchPrevious = indexedNativeTaskState(previousTasks, pchTask->id);
        if (!taskIsCurrent(pchPrevious, pchFingerprint, pchTask->auxiliaryOutputPaths)) {
            (pchChanged = true);
            const auto pchResult = runBuildCommand(pchTask->compiler, mutableArguments(pchTask->arguments), std::string(""));
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
    const auto& _iterable_9 = plan->compileTasks;
    for (const auto& task : *_iterable_9) {
        const auto fingerprint = taskFingerprint(task, identities);
        taskFingerprints->push_back(fingerprint);
        const auto previous = indexedNativeTaskState(previousTasks, task->id);
        if ((task->usesPrecompiledHeader && pchChanged) || !taskIsCurrent(previous, fingerprint, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
            dirtyTasks->push_back(task);
            dirtyTaskIds->push_back(task->id);
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>> workers = std::make_shared<std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>>(std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>{});
    std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>> promises = std::make_shared<std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>>(std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>{});
    const auto& _iterable_10 = dirtyTasks;
    for (const auto& task : *_iterable_10) {
        ensureDirectory(parentDirectory(task->outputPath));
    }
    const auto& _iterable_11 = ::app_src_native_build_::batchNativeCompileTasks(dirtyTasks, 4);
    for (const auto& batch : *_iterable_11) {
        const auto worker = std::make_shared<doof::Actor<NativeCompilerWorker>>(NativeCompilerWorker{batch});
        workers->push_back(worker);
        promises->push_back(worker->template call_async<std::shared_ptr<NativeCompilerBatchResult>>([](NativeCompilerWorker& _self) -> std::shared_ptr<NativeCompilerBatchResult> { return _self.compile(); }));
    }
    auto compileExitCode = 0;
    for (int32_t index = 0; index < static_cast<int32_t>((promises)->size()); ++index) {
        auto _binding_value_12 = doof::array_at(promises, index, "src/native-build-driver", 195).get();
        if (doof::is_failure(_binding_value_12)) {
            const auto error = doof::failure_error(_binding_value_12);
            const auto ignoredWorker = doof::array_at(workers, index, "src/native-build-driver", 196)->retire();
            doof::println((std::string("error: native compiler worker failed: ") + error));
            return 1;
        }
        const auto batchResult = doof::success_value(_binding_value_12);
        doof::array_at(workers, index, "src/native-build-driver", 200)->retire();
        const auto& _iterable_13 = batchResult->outputs;
        for (const auto& commandResult : *_iterable_13) {
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
    if (!doof::is_null(plan->precompiledHeaderTask)) {
        const auto& _iterable_14 = plan->precompiledHeaderTask->auxiliaryOutputPaths;
        for (const auto& path : *_iterable_14) {
            objectPaths->push_back(path);
        }
    }
    for (int32_t index = 0; index < static_cast<int32_t>((plan->compileTasks)->size()); ++index) {
        const auto task = doof::array_at(plan->compileTasks, index, "src/native-build-driver", 215);
        objectPaths->push_back(task->outputPath);
        if (contains(dirtyTaskIds, task->id)) {
            nextState->tasks->push_back(captureTaskState(task, doof::array_at(taskFingerprints, index, "src/native-build-driver", 217)));
        } else {
            nextState->tasks->push_back(doof::unwrap_optional(indexedNativeTaskState(previousTasks, task->id)));
        }
    }
    const auto linkId = (std::string("link:") + plan->outputPath);
    const auto computedLinkFingerprint = linkFingerprint(plan->linker, plan->linkArguments, plan->outputPath, identities);
    const auto linkPrevious = indexedNativeTaskState(previousTasks, linkId);
    auto linkChanged = false;
    if ((static_cast<int32_t>((dirtyTasks)->size()) > 0) || !taskIsCurrent(linkPrevious, computedLinkFingerprint, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
        (linkChanged = true);
        const auto linkResult = runBuildCommand(plan->linker, plan->linkArguments, std::string(""));
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
    if (((pchChanged || (static_cast<int32_t>((dirtyTasks)->size()) > 0)) || linkChanged) || nativeManagedOutputsChanged(previousState->managedOutputs, nextState->managedOutputs)) {
        writeBuildState(statePath, nextState);
    }
    return 0;
}
std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>> indexNativeTaskStates(const std::shared_ptr<::app_src_native_build_state_::NativeBuildState>& state) {
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>> indexed = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>{});
    const auto& _iterable_15 = state->tasks;
    for (const auto& task : *_iterable_15) {
        doof::map_set(indexed, task->id, task, "", 0);
    }
    return indexed;
}
std::shared_ptr<::app_src_native_build_state_::NativeTaskState> indexedNativeTaskState(const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>& indexed, const std::string& id) {
    auto _binding_value_16 = doof::map_get(indexed, id, "", 0);
    if (doof::is_failure(_binding_value_16)) {
        const auto& task = _binding_value_16;
        return nullptr;
    }
    const auto task = doof::success_value(_binding_value_16);
    return task;
}
std::string compilerIdentity(const std::string& command, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities) {
    const auto& _iterable_17 = identities;
    for (const auto& identity : *_iterable_17) {
        if (identity->command == command) {
            return identity->signature;
        }
    }
    const auto result = runBuildCommand(command, (::app_src_native_build_::isMsvcCompiler(command) ? std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("/?")}) : std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--version")})), std::string(""));
    auto description = command;
    if (result->exitCode == 0) {
        (description = ((description + std::string("\n")) + ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size())))));
    }
    const auto signature = ::std_::crypto::index::sha256HexString(description);
    identities->push_back(std::make_shared<NativeCompilerIdentity>(command, signature));
    return signature;
}
std::string taskFingerprint(const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities) {
    auto value = ((task->id + std::string("\n")) + compilerIdentity(task->compiler, identities));
    const auto& _iterable_18 = task->arguments;
    for (const auto& argument : *_iterable_18) {
        (value = ((value + std::string("\n")) + argument));
    }
    return ::std_::crypto::index::sha256HexString(value);
}
std::string linkFingerprint(const std::string& linker, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities) {
    auto value = (((std::string("link:") + outputPath) + std::string("\n")) + compilerIdentity(linker, identities));
    const auto& _iterable_19 = arguments;
    for (const auto& argument : *_iterable_19) {
        (value = ((value + std::string("\n")) + argument));
    }
    return ::std_::crypto::index::sha256HexString(value);
}
std::shared_ptr<::app_src_native_build_state_::NativeInputSignature> pathSignature(const std::string& path, bool contentHash) {
    if (!::doof_fs::exists(path) || ::doof_fs::isDirectory(path)) {
        return nullptr;
    }
    auto _binding_value_20 = ::doof_fs::metadata(path);
    if (doof::is_failure(_binding_value_20)) {
        const auto& info = _binding_value_20;
        return nullptr;
    }
    const auto info = doof::success_value(_binding_value_20);
    const auto modifiedNanos = info->modifiedAt->toEpochNanos();
    const auto signature = (contentHash ? ::std_::crypto::index::sha256Hex([&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 282, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }()) : ((doof::to_string(info->size) + std::string(":")) + doof::to_string(modifiedNanos)));
    return std::make_shared<::app_src_native_build_state_::NativeInputSignature>(path, signature, contentHash, info->size, modifiedNanos);
}
std::shared_ptr<::app_src_native_build_state_::NativeInputSignature> currentInputSignature(const std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>& previous) {
    if (!::doof_fs::exists(previous->path) || ::doof_fs::isDirectory(previous->path)) {
        return nullptr;
    }
    auto _binding_value_21 = ::doof_fs::metadata(previous->path);
    if (doof::is_failure(_binding_value_21)) {
        const auto& info = _binding_value_21;
        return nullptr;
    }
    const auto info = doof::success_value(_binding_value_21);
    const auto modifiedNanos = info->modifiedAt->toEpochNanos();
    if ((previous->size == info->size) && (previous->modifiedNanos == modifiedNanos)) {
        return std::make_shared<::app_src_native_build_state_::NativeInputSignature>(previous->path, previous->signature, previous->contentHash, info->size, modifiedNanos);
    }
    return pathSignature(previous->path, previous->contentHash);
}
bool taskIsCurrent(const std::shared_ptr<::app_src_native_build_state_::NativeTaskState>& previous, const std::string& fingerprint, const std::shared_ptr<std::vector<std::string>>& auxiliaryOutputPaths) {
    if (doof::is_null(previous) || !::doof_fs::exists(previous->outputPath)) {
        return false;
    }
    const auto& _iterable_22 = auxiliaryOutputPaths;
    for (const auto& path : *_iterable_22) {
        if (!::doof_fs::exists(path) || ::doof_fs::isDirectory(path)) {
            return false;
        }
    }
    auto _binding_value_23 = ::doof_fs::metadata(previous->outputPath);
    if (doof::is_failure(_binding_value_23)) {
        const auto& info = _binding_value_23;
        return false;
    }
    const auto info = doof::success_value(_binding_value_23);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>> currentInputs = std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{});
    const auto& _iterable_24 = previous->inputs;
    for (const auto& input : *_iterable_24) {
        const auto signature = currentInputSignature(input);
        if (doof::is_null(signature)) {
            return false;
        }
        currentInputs->push_back(doof::unwrap_optional(signature));
    }
    return nativeTaskStateIsCurrent(previous, fingerprint, info->size, info->modifiedAt->toEpochNanos(), currentInputs, true);
}
bool nativeTaskStateIsCurrent(const std::shared_ptr<::app_src_native_build_state_::NativeTaskState>& previous, const std::string& fingerprint, int64_t outputSize, int64_t outputModifiedNanos, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>& currentInputs, bool auxiliaryOutputsCurrent) {
    if (!auxiliaryOutputsCurrent) {
        return false;
    }
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
        const auto expected = doof::array_at(previous->inputs, index, "src/native-build-driver", 330);
        const auto current = doof::array_at(currentInputs, index, "src/native-build-driver", 331);
        if (((((expected->path != current->path) || (expected->signature != current->signature)) || (expected->contentHash != current->contentHash)) || (expected->size != current->size)) || (expected->modifiedNanos != current->modifiedNanos)) {
            return false;
        }
    }
    return true;
}
std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureTaskState(const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task, const std::string& fingerprint) {
    const auto info = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(task->outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 339, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    const auto state = std::make_shared<::app_src_native_build_state_::NativeTaskState>(task->id, fingerprint, task->outputPath, info->size, info->modifiedAt->toEpochNanos(), std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{}));
    std::shared_ptr<std::vector<std::string>> paths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{task->sourcePath});
    if ((task->dependencyFilePath != std::string("")) && ::doof_fs::exists(task->dependencyFilePath)) {
        const auto dependencySource = [&]() -> std::string { auto _try_value = ::doof_fs::readText(task->dependencyFilePath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 343, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        const auto dependencies = (doof::string_endsWith(doof::string_toLowerCase(task->dependencyFilePath), std::string(".json")) ? ::app_src_native_build_state_::parseMsvcDependencies(dependencySource) : ::app_src_native_build_state_::parseMakeDependencies(dependencySource));
        const auto& _iterable_25 = dependencies;
        for (const auto& path : *_iterable_25) {
            appendUnique(paths, path);
        }
    }
    const auto& _iterable_26 = paths;
    for (const auto& path : *_iterable_26) {
        const auto signature = pathSignature(path, true);
        if (!doof::is_null(signature)) {
            state->inputs->push_back(doof::unwrap_optional(signature));
        }
    }
    return state;
}
std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureLinkState(const std::string& outputPath, const std::string& fingerprint, const std::shared_ptr<std::vector<std::string>>& objectPaths) {
    const auto info = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 357, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    const auto state = std::make_shared<::app_src_native_build_state_::NativeTaskState>((std::string("link:") + outputPath), fingerprint, outputPath, info->size, info->modifiedAt->toEpochNanos(), std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{}));
    const auto& _iterable_27 = objectPaths;
    for (const auto& path : *_iterable_27) {
        const auto signature = pathSignature(path, false);
        if (!doof::is_null(signature)) {
            state->inputs->push_back(doof::unwrap_optional(signature));
        }
    }
    return state;
}
std::shared_ptr<::app_src_native_build_state_::NativeBuildState> readBuildState(const std::string& path) {
    if (!::doof_fs::exists(path)) {
        return std::make_shared<::app_src_native_build_state_::NativeBuildState>(2, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    auto _binding_value_28 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_28)) {
        const auto& source = _binding_value_28;
        return std::make_shared<::app_src_native_build_state_::NativeBuildState>(2, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    const auto source = doof::success_value(_binding_value_28);
    const auto parsed = ::app_src_native_build_state_::parseNativeBuildState(source);
    return (doof::is_null(parsed) ? std::make_shared<::app_src_native_build_state_::NativeBuildState>(2, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : doof::unwrap_optional(parsed));
}
void writeBuildState(const std::string& path, const std::shared_ptr<::app_src_native_build_state_::NativeBuildState>& state) {
    const auto temporaryPath = (path + std::string(".tmp"));
    [&]() -> void { auto _try_value = ::doof_fs::writeText(temporaryPath, ::app_src_native_build_state_::renderNativeBuildState(state)); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 375, std::string("try! failed"));  }();
    [&]() -> void { auto _try_value = ::doof_fs::rename(temporaryPath, path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 376, std::string("try! failed"));  }();
}
void writeTextIfChanged(const std::string& path, const std::string& content) {
    if (::doof_fs::exists(path)) {
        auto _binding_value_29 = ::doof_fs::readText(path);
        if (doof::is_failure(_binding_value_29)) {
            const auto& previous = _binding_value_29;
            [&]() -> void { auto _try_value = ::doof_fs::writeText(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 381, std::string("try! failed"));  }();
            return;
        }
        const auto previous = doof::success_value(_binding_value_29);
        if (!nativeSupportFileNeedsWrite(previous, content)) {
            return;
        }
    }
    [&]() -> void { auto _try_value = ::doof_fs::writeText(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 384, std::string("try! failed"));  }();
}
bool nativeSupportFileNeedsWrite(const std::optional<std::string>& previous, const std::string& content) {
    return (doof::is_null(previous) || (previous.value() != content));
}
void collectManagedOutputs(const std::shared_ptr<std::vector<std::string>>& outputs, const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project) {
    std::shared_ptr<doof::ordered_set<std::string>> indexed = std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{});
    const auto& _iterable_30 = outputs;
    for (const auto& output : *_iterable_30) {
        indexed->insert(output);
    }
    collectManagedOutputsIndexed(outputs, indexed, outputDirectory, plan, project);
}
void collectManagedOutputsIndexed(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project) {
    appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, std::string("doof_runtime.hpp")));
    const auto& _iterable_31 = plan->supportFiles;
    for (const auto& supportFile : *_iterable_31) {
        appendManagedOutput(outputs, indexed, supportFile->outputPath);
    }
    const auto& _iterable_32 = project->modules;
    for (const auto& module : *_iterable_32) {
        appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, module->headerName));
        appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, module->sourceName));
    }
    const auto& _iterable_33 = project->supportFiles;
    for (const auto& supportFile : *_iterable_33) {
        appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, supportFile->relativePath));
    }
    const auto& _iterable_34 = project->nativeCopies;
    for (const auto& nativeCopy : *_iterable_34) {
        collectManagedNativeCopyOutputs(outputs, indexed, nativeCopy->sourcePath, joinOutput(outputDirectory, nativeCopy->relativePath));
    }
    if (!doof::is_null(plan->precompiledHeaderTask)) {
        appendManagedOutput(outputs, indexed, plan->precompiledHeaderTask->outputPath);
        if (plan->precompiledHeaderTask->dependencyFilePath != std::string("")) {
            appendManagedOutput(outputs, indexed, plan->precompiledHeaderTask->dependencyFilePath);
        }
        const auto& _iterable_35 = plan->precompiledHeaderTask->auxiliaryOutputPaths;
        for (const auto& path : *_iterable_35) {
            appendManagedOutput(outputs, indexed, path);
        }
    }
    const auto& _iterable_36 = plan->compileTasks;
    for (const auto& task : *_iterable_36) {
        appendManagedOutput(outputs, indexed, task->outputPath);
        if (task->dependencyFilePath != std::string("")) {
            appendManagedOutput(outputs, indexed, task->dependencyFilePath);
        }
        const auto& _iterable_37 = task->auxiliaryOutputPaths;
        for (const auto& path : *_iterable_37) {
            appendManagedOutput(outputs, indexed, path);
        }
    }
    appendManagedOutput(outputs, indexed, plan->outputPath);
}
void collectManagedNativeCopyOutputs(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& sourcePath, const std::string& outputPath) {
    if (!::doof_fs::isDirectory(sourcePath)) {
        appendManagedOutput(outputs, indexed, outputPath);
        return;
    }
    const auto& _iterable_38 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 433, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    for (const auto& entry : *_iterable_38) {
        collectManagedNativeCopyOutputs(outputs, indexed, joinOutput(sourcePath, entry->name), joinOutput(outputPath, entry->name));
    }
}
void removeStaleOutputs(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current, const std::string& outputDirectory) {
    const auto& _iterable_39 = staleManagedOutputCandidates(previous, current, outputDirectory);
    for (const auto& path : *_iterable_39) {
        if (::doof_fs::exists(path) && !::doof_fs::isDirectory(path)) {
            [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 440, std::string("try! failed"));  }();
        }
    }
}
std::shared_ptr<std::vector<std::string>> staleManagedOutputCandidates(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current, const std::string& outputDirectory) {
    const auto prefix = (doof::string_endsWith(outputDirectory, std::string("/")) ? outputDirectory : (outputDirectory + std::string("/")));
    std::shared_ptr<doof::ordered_set<std::string>> retained = std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{});
    const auto& _iterable_40 = current;
    for (const auto& path : *_iterable_40) {
        retained->insert(path);
    }
    std::shared_ptr<std::vector<std::string>> stale = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_41 = previous;
    for (const auto& path : *_iterable_41) {
        if ((retained->count(path) > 0) || !doof::string_startsWith(path, prefix)) {
            continue;
        }
        stale->push_back(path);
    }
    return stale;
}
bool nativeManagedOutputsChanged(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current) {
    if (static_cast<int32_t>((previous)->size()) != static_cast<int32_t>((current)->size())) {
        return true;
    }
    for (int32_t index = 0; index < static_cast<int32_t>((previous)->size()); ++index) {
        if (doof::array_at(previous, index, "src/native-build-driver", 461) != doof::array_at(current, index, "src/native-build-driver", 461)) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<std::vector<std::string>> mutableArguments(const std::shared_ptr<std::vector<std::string>>& arguments) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_42 = arguments;
    for (const auto& argument : *_iterable_42) {
        result->push_back(argument);
    }
    return result;
}
bool contains(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    const auto& _iterable_43 = values;
    for (const auto& existing : *_iterable_43) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}
void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    if (!contains(values, value)) {
        values->push_back(value);
    }
}
void appendManagedOutput(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& value) {
    if (indexed->count(value) > 0) {
        return;
    }
    indexed->insert(value);
    outputs->push_back(value);
}
std::string joinOutput(const std::string& directory, const std::string& name) {
    return (doof::string_endsWith(directory, std::string("/")) ? (directory + name) : ((directory + std::string("/")) + name));
}
std::string parentDirectory(const std::string& path) {
    auto index = (static_cast<int32_t>(path.size()) - 1);
    while ((index > 0) && (doof::string_at(path, index, "src/native-build-driver", 490) != U'\u002F')) {
        (index -= 1);
    }
    return ((index <= 0) ? std::string("/") : doof::string_substring(path, 0, index));
}
void ensureDirectory(const std::string& path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return;
    }
    const auto parent = parentDirectory(path);
    if (parent != path) {
        ensureDirectory(parent);
    }
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 498, std::string("try! failed"));  }();
}
}
