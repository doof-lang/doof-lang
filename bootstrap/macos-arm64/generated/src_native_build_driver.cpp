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
int64_t MAX_NATIVE_OUTPUT_BYTES = 262144LL;



#line 43 "/src/native-build-driver.do"
std::shared_ptr<NativeCommandResult> runBuildCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments) {
#line 47 "/src/native-build-driver.do"
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_NATIVE_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
#line 52 "/src/native-build-driver.do"
        return std::make_shared<NativeCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error, false);
    }
    const auto executed = doof::success_value(_binding_value_1);
#line 54 "/src/native-build-driver.do"
    return std::make_shared<NativeCommandResult>(executed->exitCode, executed->stdout_, std::string(""), executed->stdoutTruncated);
}
#line 61 "/src/native-build-driver.do"
void printBuildOutput(const std::shared_ptr<NativeCommandResult>& result) {
#line 62 "/src/native-build-driver.do"
    const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
#line 63 "/src/native-build-driver.do"
    const auto& _iterable_3 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_3) {
#line 64 "/src/native-build-driver.do"
        if (line == std::string("")) {
#line 64 "/src/native-build-driver.do"
            continue;
        }
#line 65 "/src/native-build-driver.do"
        doof::println(line);
    }
}
#line 70 "/src/native-build-driver.do"
std::string nativeCompilationSummary(int32_t fileCount) {
#line 71 "/src/native-build-driver.do"
    if (fileCount <= 0) {
#line 71 "/src/native-build-driver.do"
        return std::string("");
    }
#line 72 "/src/native-build-driver.do"
    return ((std::string("Compiling ") + doof::to_string(fileCount)) + ((fileCount == 1) ? std::string(" file") : std::string(" files")));
}
#line 76 "/src/native-build-driver.do"
std::string nativeCompilationProgress(int32_t fileCount) {
#line 77 "/src/native-build-driver.do"
    return ((fileCount <= 0) ? std::string("") : doof::string_repeat(std::string("."), fileCount));
}
#line 81 "/src/native-build-driver.do"
bool shouldPrintNativeCompilationMarker(NativeBuildOutputMode outputMode, int32_t exitCode) {
#line 82 "/src/native-build-driver.do"
    return ((outputMode == NativeBuildOutputMode::Progress) && (exitCode == 0));
}
#line 86 "/src/native-build-driver.do"
bool shouldPrintNativeCommandOutput(int32_t exitCode) {
#line 87 "/src/native-build-driver.do"
    return (exitCode != 0);
}

#line 94 "/src/native-build-driver.do"
std::shared_ptr<NativeCompilerBatchResult> NativeCompilerWorker::compile() {
#line 95 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<NativeCommandResult>>> outputs = std::make_shared<std::vector<std::shared_ptr<NativeCommandResult>>>(std::vector<std::shared_ptr<NativeCommandResult>>{});
#line 96 "/src/native-build-driver.do"
    const auto& _iterable_5 = this->tasks;
    for (const auto& task : *_iterable_5) {
#line 97 "/src/native-build-driver.do"
        const auto result = runBuildCommand(task->compiler, mutableArguments(task->arguments));
#line 98 "/src/native-build-driver.do"
        outputs->push_back(result);
#line 99 "/src/native-build-driver.do"
        if (shouldPrintNativeCompilationMarker(this->outputMode, result->exitCode)) {
#line 99 "/src/native-build-driver.do"
            ::doof::print_flushed(std::string("."));
        }
#line 100 "/src/native-build-driver.do"
        if (result->exitCode != 0) {
#line 101 "/src/native-build-driver.do"
            return std::make_shared<NativeCompilerBatchResult>(result->exitCode, doof::array_drainToReadonly(outputs, "", 0));
        }
    }
#line 104 "/src/native-build-driver.do"
    return std::make_shared<NativeCompilerBatchResult>(0, doof::array_drainToReadonly(outputs, "", 0));
}
#line 108 "/src/native-build-driver.do"
int32_t buildNativeProject(const std::string& compilerOverride, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project, ::app_src_native_build_::NativeBuildMode mode, const std::string& platform, NativeBuildOutputMode outputMode) {
#line 117 "/src/native-build-driver.do"
    const auto& _iterable_7 = project->nativeBuild->pkgConfigPackages;
    for (const auto& packageName : *_iterable_7) {
#line 118 "/src/native-build-driver.do"
        const auto& _iterable_9 = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("cflags"), std::string("libs")});
        for (const auto& mode : *_iterable_9) {
#line 119 "/src/native-build-driver.do"
            const auto pkgConfigResult = runBuildCommand(std::string("pkg-config"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{(std::string("--") + mode), packageName}));
#line 120 "/src/native-build-driver.do"
            const auto output = ::doof_blob::NativeBlobReader::constructor(pkgConfigResult->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((pkgConfigResult->output)->size())));
#line 121 "/src/native-build-driver.do"
            const auto applied = ::app_src_pkg_config_::applyPkgConfigResult(project->nativeBuild, packageName, mode, std::make_shared<::app_src_pkg_config_::PkgConfigCommandResult>(pkgConfigResult->exitCode, output, pkgConfigResult->error));
#line 126 "/src/native-build-driver.do"
            auto _binding_value_10 = applied;
            if (doof::is_failure(_binding_value_10)) {
                const auto error = doof::failure_error(_binding_value_10);
#line 126 "/src/native-build-driver.do"
                doof::println((std::string("error: ") + error));
#line 126 "/src/native-build-driver.do"
                return 1;
            }
        }
    }
#line 130 "/src/native-build-driver.do"
    const auto wasm = doof::string_endsWith(outputPath, std::string(".wasm"));
#line 131 "/src/native-build-driver.do"
    auto compiler = compilerOverride;
#line 132 "/src/native-build-driver.do"
    if ((compiler == std::string("")) && wasm) {
#line 132 "/src/native-build-driver.do"
        (compiler = std::string("em++"));
    }
#line 133 "/src/native-build-driver.do"
    if (compiler == std::string("")) {
#line 134 "/src/native-build-driver.do"
        const auto configured = envCompiler();
#line 135 "/src/native-build-driver.do"
        if (configured != std::string("")) {
#line 135 "/src/native-build-driver.do"
            (compiler = configured);
        }
    }
#line 137 "/src/native-build-driver.do"
    if (compiler == std::string("")) {
#line 137 "/src/native-build-driver.do"
        (compiler = ((platform == std::string("windows")) ? std::string("cl.exe") : std::string("c++")));
    }
#line 138 "/src/native-build-driver.do"
    const auto plan = ::app_src_native_build_::planNativeCompile(compiler, outputDirectory, outputPath, project->modules, project->nativeBuild, mode, platform, project->wasmExportNames, wasm);
#line 139 "/src/native-build-driver.do"
    return executeNativePlan(outputDirectory, plan, project, outputMode);
}
#line 142 "/src/native-build-driver.do"
std::string envCompiler() {
#line 143 "/src/native-build-driver.do"
    auto _binding_value_11 = ::std_::os::index::env(std::string("CXX"));
    if (doof::is_failure(_binding_value_11)) {
        const auto& value = _binding_value_11;
#line 143 "/src/native-build-driver.do"
        return std::string("");
    }
    const auto value = doof::success_value(_binding_value_11);
#line 144 "/src/native-build-driver.do"
    return value;
}
#line 147 "/src/native-build-driver.do"
int32_t executeNativePlan(const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project, NativeBuildOutputMode outputMode) {
#line 153 "/src/native-build-driver.do"
    const auto& _iterable_13 = plan->supportFiles;
    for (const auto& supportFile : *_iterable_13) {
#line 154 "/src/native-build-driver.do"
        ensureDirectory(parentDirectory(supportFile->outputPath));
#line 155 "/src/native-build-driver.do"
        writeTextIfChanged(supportFile->outputPath, supportFile->content);
    }
#line 157 "/src/native-build-driver.do"
    const auto statePath = joinOutput(outputDirectory, std::string(".doof-native-build-state.json"));
#line 158 "/src/native-build-driver.do"
    const auto previousState = readBuildState(statePath);
#line 159 "/src/native-build-driver.do"
    const auto previousTasks = indexNativeTaskStates(previousState);
#line 160 "/src/native-build-driver.do"
    const auto nextState = std::make_shared<::app_src_native_build_state_::NativeBuildState>(2, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 161 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities = std::make_shared<std::vector<std::shared_ptr<NativeCompilerIdentity>>>(std::vector<std::shared_ptr<NativeCompilerIdentity>>{});
#line 162 "/src/native-build-driver.do"
    auto truncationReported = false;
#line 163 "/src/native-build-driver.do"
    auto pchChanged = false;
#line 165 "/src/native-build-driver.do"
    if (!doof::is_null(plan->precompiledHeaderTask)) {
#line 166 "/src/native-build-driver.do"
        const auto pchTask = doof::unwrap_optional(plan->precompiledHeaderTask);
#line 167 "/src/native-build-driver.do"
        ensureDirectory(parentDirectory(pchTask->outputPath));
#line 168 "/src/native-build-driver.do"
        const auto pchFingerprint = taskFingerprint(pchTask, identities);
#line 169 "/src/native-build-driver.do"
        const auto pchPrevious = indexedNativeTaskState(previousTasks, pchTask->id);
#line 170 "/src/native-build-driver.do"
        if (!taskIsCurrent(pchPrevious, pchFingerprint, pchTask->auxiliaryOutputPaths)) {
#line 171 "/src/native-build-driver.do"
            (pchChanged = true);
#line 172 "/src/native-build-driver.do"
            const auto pchResult = runBuildCommand(pchTask->compiler, mutableArguments(pchTask->arguments));
#line 173 "/src/native-build-driver.do"
            if (pchResult->exitCode != 0) {
#line 174 "/src/native-build-driver.do"
                printBuildOutput(pchResult);
#line 175 "/src/native-build-driver.do"
                if (pchResult->truncated) {
#line 175 "/src/native-build-driver.do"
                    doof::println(((std::string("... native compiler output capture truncated after ") + doof::to_string(MAX_NATIVE_OUTPUT_BYTES)) + std::string(" bytes")));
#line 175 "/src/native-build-driver.do"
                    (truncationReported = true);
                }
#line 176 "/src/native-build-driver.do"
                doof::println((std::string("error: native compiler failed to build the precompiled runtime header with code ") + doof::to_string(pchResult->exitCode)));
#line 177 "/src/native-build-driver.do"
                return pchResult->exitCode;
            }
#line 179 "/src/native-build-driver.do"
            nextState->tasks->push_back(captureTaskState(pchTask, pchFingerprint));
        } else {
#line 180 "/src/native-build-driver.do"
            nextState->tasks->push_back(doof::unwrap_optional(pchPrevious));
        }
    }
#line 183 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>> dirtyTasks = std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>>(std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>{});
#line 184 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::string>> dirtyTaskIds = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 185 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::string>> taskFingerprints = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 186 "/src/native-build-driver.do"
    const auto& _iterable_15 = plan->compileTasks;
    for (const auto& task : *_iterable_15) {
#line 187 "/src/native-build-driver.do"
        const auto fingerprint = taskFingerprint(task, identities);
#line 188 "/src/native-build-driver.do"
        taskFingerprints->push_back(fingerprint);
#line 189 "/src/native-build-driver.do"
        const auto previous = indexedNativeTaskState(previousTasks, task->id);
#line 190 "/src/native-build-driver.do"
        if ((task->usesPrecompiledHeader && pchChanged) || !taskIsCurrent(previous, fingerprint, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
#line 191 "/src/native-build-driver.do"
            dirtyTasks->push_back(task);
#line 192 "/src/native-build-driver.do"
            dirtyTaskIds->push_back(task->id);
        }
    }
#line 196 "/src/native-build-driver.do"
    if ((outputMode == NativeBuildOutputMode::Progress) && (static_cast<int32_t>((dirtyTasks)->size()) > 0)) {
#line 197 "/src/native-build-driver.do"
        doof::println(nativeCompilationSummary(static_cast<int32_t>((dirtyTasks)->size())));
    }
#line 200 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>> workers = std::make_shared<std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>>(std::vector<std::shared_ptr<doof::Actor<NativeCompilerWorker>>>{});
#line 201 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>> promises = std::make_shared<std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>>(std::vector<doof::Promise<std::shared_ptr<NativeCompilerBatchResult>>>{});
#line 202 "/src/native-build-driver.do"
    const auto& _iterable_17 = dirtyTasks;
    for (const auto& task : *_iterable_17) {
#line 202 "/src/native-build-driver.do"
        ensureDirectory(parentDirectory(task->outputPath));
    }
#line 203 "/src/native-build-driver.do"
    const auto& _iterable_19 = ::app_src_native_build_::batchNativeCompileTasks(dirtyTasks, 4);
    for (const auto& batch : *_iterable_19) {
#line 204 "/src/native-build-driver.do"
        const auto worker = std::make_shared<doof::Actor<NativeCompilerWorker>>(NativeCompilerWorker{batch, outputMode});
#line 205 "/src/native-build-driver.do"
        workers->push_back(worker);
#line 206 "/src/native-build-driver.do"
        promises->push_back(worker->template call_async<std::shared_ptr<NativeCompilerBatchResult>>([](NativeCompilerWorker& _self) -> std::shared_ptr<NativeCompilerBatchResult> { return _self.compile(); }));
    }
#line 208 "/src/native-build-driver.do"
    auto compileExitCode = 0;
#line 209 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerBatchResult>>> batchResults = std::make_shared<std::vector<std::shared_ptr<NativeCompilerBatchResult>>>(std::vector<std::shared_ptr<NativeCompilerBatchResult>>{});
#line 210 "/src/native-build-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>((promises)->size()); ++index) {
#line 211 "/src/native-build-driver.do"
        auto _binding_value_21 = doof::array_at(promises, index, "src/native-build-driver", 211).get();
        if (doof::is_failure(_binding_value_21)) {
            const auto error = doof::failure_error(_binding_value_21);
#line 212 "/src/native-build-driver.do"
            const auto ignoredWorker = doof::array_at(workers, index, "src/native-build-driver", 212)->retire();
#line 213 "/src/native-build-driver.do"
            if ((outputMode == NativeBuildOutputMode::Progress) && (static_cast<int32_t>((dirtyTasks)->size()) > 0)) {
#line 213 "/src/native-build-driver.do"
                doof::println(std::string(""));
            }
#line 214 "/src/native-build-driver.do"
            doof::println((std::string("error: native compiler worker failed: ") + error));
#line 215 "/src/native-build-driver.do"
            return 1;
        }
        const auto batchResult = doof::success_value(_binding_value_21);
#line 217 "/src/native-build-driver.do"
        doof::array_at(workers, index, "src/native-build-driver", 217)->retire();
#line 218 "/src/native-build-driver.do"
        batchResults->push_back(batchResult);
    }
#line 220 "/src/native-build-driver.do"
    if ((outputMode == NativeBuildOutputMode::Progress) && (static_cast<int32_t>((dirtyTasks)->size()) > 0)) {
#line 220 "/src/native-build-driver.do"
        doof::println(std::string(""));
    }
#line 221 "/src/native-build-driver.do"
    const auto& _iterable_23 = batchResults;
    for (const auto& batchResult : *_iterable_23) {
#line 222 "/src/native-build-driver.do"
        const auto& _iterable_25 = batchResult->outputs;
        for (const auto& commandResult : *_iterable_25) {
#line 223 "/src/native-build-driver.do"
            if (shouldPrintNativeCommandOutput(commandResult->exitCode)) {
#line 224 "/src/native-build-driver.do"
                printBuildOutput(commandResult);
#line 225 "/src/native-build-driver.do"
                if (commandResult->truncated && !truncationReported) {
#line 225 "/src/native-build-driver.do"
                    doof::println(((std::string("... native compiler output capture truncated after ") + doof::to_string(MAX_NATIVE_OUTPUT_BYTES)) + std::string(" bytes")));
#line 225 "/src/native-build-driver.do"
                    (truncationReported = true);
                }
            }
        }
#line 228 "/src/native-build-driver.do"
        if ((compileExitCode == 0) && (batchResult->exitCode != 0)) {
#line 228 "/src/native-build-driver.do"
            (compileExitCode = batchResult->exitCode);
        }
    }
#line 230 "/src/native-build-driver.do"
    if (compileExitCode != 0) {
#line 230 "/src/native-build-driver.do"
        doof::println((std::string("error: native object compiler exited with code ") + doof::to_string(compileExitCode)));
#line 230 "/src/native-build-driver.do"
        return compileExitCode;
    }
#line 232 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::string>> objectPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 233 "/src/native-build-driver.do"
    if (!doof::is_null(plan->precompiledHeaderTask)) {
#line 234 "/src/native-build-driver.do"
        const auto& _iterable_27 = plan->precompiledHeaderTask->auxiliaryOutputPaths;
        for (const auto& path : *_iterable_27) {
#line 234 "/src/native-build-driver.do"
            objectPaths->push_back(path);
        }
    }
#line 236 "/src/native-build-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>((plan->compileTasks)->size()); ++index) {
#line 237 "/src/native-build-driver.do"
        const auto task = doof::array_at(plan->compileTasks, index, "src/native-build-driver", 237);
#line 238 "/src/native-build-driver.do"
        objectPaths->push_back(task->outputPath);
#line 239 "/src/native-build-driver.do"
        if (contains(dirtyTaskIds, task->id)) {
#line 239 "/src/native-build-driver.do"
            nextState->tasks->push_back(captureTaskState(task, doof::array_at(taskFingerprints, index, "src/native-build-driver", 239)));
        } else {
#line 240 "/src/native-build-driver.do"
            nextState->tasks->push_back(doof::unwrap_optional(indexedNativeTaskState(previousTasks, task->id)));
        }
    }
#line 243 "/src/native-build-driver.do"
    const auto linkId = (std::string("link:") + plan->outputPath);
#line 244 "/src/native-build-driver.do"
    const auto computedLinkFingerprint = linkFingerprint(plan->linker, plan->linkArguments, plan->outputPath, identities);
#line 245 "/src/native-build-driver.do"
    const auto linkPrevious = indexedNativeTaskState(previousTasks, linkId);
#line 246 "/src/native-build-driver.do"
    auto linkChanged = false;
#line 247 "/src/native-build-driver.do"
    if ((static_cast<int32_t>((dirtyTasks)->size()) > 0) || !taskIsCurrent(linkPrevious, computedLinkFingerprint, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
#line 248 "/src/native-build-driver.do"
        (linkChanged = true);
#line 249 "/src/native-build-driver.do"
        auto executedLinkArguments = plan->linkArguments;
#line 250 "/src/native-build-driver.do"
        if (isMsvcLinker(plan->linker)) {
#line 251 "/src/native-build-driver.do"
            const auto responsePath = msvcLinkResponsePath(outputDirectory);
#line 252 "/src/native-build-driver.do"
            writeTextIfChanged(responsePath, msvcLinkResponseFile(plan->linkArguments));
#line 253 "/src/native-build-driver.do"
            (executedLinkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{(std::string("@") + responsePath)}));
        }
#line 255 "/src/native-build-driver.do"
        const auto linkResult = runBuildCommand(plan->linker, executedLinkArguments);
#line 256 "/src/native-build-driver.do"
        if (linkResult->exitCode != 0) {
#line 257 "/src/native-build-driver.do"
            printBuildOutput(linkResult);
#line 258 "/src/native-build-driver.do"
            if (linkResult->truncated && !truncationReported) {
#line 258 "/src/native-build-driver.do"
                doof::println(((std::string("... native linker output capture truncated after ") + doof::to_string(MAX_NATIVE_OUTPUT_BYTES)) + std::string(" bytes")));
            }
#line 259 "/src/native-build-driver.do"
            doof::println((std::string("error: native linker exited with code ") + doof::to_string(linkResult->exitCode)));
#line 260 "/src/native-build-driver.do"
            return linkResult->exitCode;
        }
#line 262 "/src/native-build-driver.do"
        nextState->tasks->push_back(captureLinkState(plan->outputPath, computedLinkFingerprint, objectPaths));
    } else {
#line 263 "/src/native-build-driver.do"
        nextState->tasks->push_back(doof::unwrap_optional(linkPrevious));
    }
#line 265 "/src/native-build-driver.do"
    collectManagedOutputs(nextState->managedOutputs, outputDirectory, plan, project);
#line 266 "/src/native-build-driver.do"
    removeStaleOutputs(previousState->managedOutputs, nextState->managedOutputs, outputDirectory);
#line 267 "/src/native-build-driver.do"
    if (((pchChanged || (static_cast<int32_t>((dirtyTasks)->size()) > 0)) || linkChanged) || nativeManagedOutputsChanged(previousState->managedOutputs, nextState->managedOutputs)) {
#line 268 "/src/native-build-driver.do"
        writeBuildState(statePath, nextState);
    }
#line 270 "/src/native-build-driver.do"
    return 0;
}
#line 273 "/src/native-build-driver.do"
std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>> indexNativeTaskStates(const std::shared_ptr<::app_src_native_build_state_::NativeBuildState>& state) {
#line 274 "/src/native-build-driver.do"
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>> indexed = std::make_shared<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>{});
#line 275 "/src/native-build-driver.do"
    const auto& _iterable_30 = state->tasks;
    for (const auto& task : *_iterable_30) {
#line 275 "/src/native-build-driver.do"
        doof::map_set(indexed, task->id, task, "", 0);
    }
#line 276 "/src/native-build-driver.do"
    return indexed;
}
#line 279 "/src/native-build-driver.do"
std::shared_ptr<::app_src_native_build_state_::NativeTaskState> indexedNativeTaskState(const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>& indexed, const std::string& id) {
#line 283 "/src/native-build-driver.do"
    auto _binding_value_31 = doof::map_get(indexed, id, "", 0);
    if (doof::is_failure(_binding_value_31)) {
        const auto& task = _binding_value_31;
#line 283 "/src/native-build-driver.do"
        return nullptr;
    }
    const auto task = doof::success_value(_binding_value_31);
#line 284 "/src/native-build-driver.do"
    return task;
}
#line 287 "/src/native-build-driver.do"
std::string compilerIdentity(const std::string& command, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities) {
#line 288 "/src/native-build-driver.do"
    const auto& _iterable_33 = identities;
    for (const auto& identity : *_iterable_33) {
#line 288 "/src/native-build-driver.do"
        if (identity->command == command) {
#line 288 "/src/native-build-driver.do"
            return identity->signature;
        }
    }
#line 289 "/src/native-build-driver.do"
    const auto result = runBuildCommand(command, (::app_src_native_build_::isMsvcCompiler(command) ? std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("/\?")}) : std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--version")})));
#line 290 "/src/native-build-driver.do"
    auto description = command;
#line 291 "/src/native-build-driver.do"
    if (result->exitCode == 0) {
#line 291 "/src/native-build-driver.do"
        (description = ((description + std::string("\n")) + ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size())))));
    }
#line 292 "/src/native-build-driver.do"
    const auto signature = ::std_::crypto::index::sha256HexString(description);
#line 293 "/src/native-build-driver.do"
    identities->push_back(std::make_shared<NativeCompilerIdentity>(command, signature));
#line 294 "/src/native-build-driver.do"
    return signature;
}
#line 297 "/src/native-build-driver.do"
std::string taskFingerprint(const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities) {
#line 298 "/src/native-build-driver.do"
    auto value = ((task->id + std::string("\n")) + compilerIdentity(task->compiler, identities));
#line 299 "/src/native-build-driver.do"
    const auto& _iterable_35 = task->arguments;
    for (const auto& argument : *_iterable_35) {
#line 299 "/src/native-build-driver.do"
        (value = ((value + std::string("\n")) + argument));
    }
#line 300 "/src/native-build-driver.do"
    return ::std_::crypto::index::sha256HexString(value);
}
#line 303 "/src/native-build-driver.do"
std::string linkFingerprint(const std::string& linker, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities) {
#line 304 "/src/native-build-driver.do"
    auto value = (((std::string("link:") + outputPath) + std::string("\n")) + compilerIdentity(linker, identities));
#line 305 "/src/native-build-driver.do"
    const auto& _iterable_37 = arguments;
    for (const auto& argument : *_iterable_37) {
#line 305 "/src/native-build-driver.do"
        (value = ((value + std::string("\n")) + argument));
    }
#line 306 "/src/native-build-driver.do"
    return ::std_::crypto::index::sha256HexString(value);
}
#line 309 "/src/native-build-driver.do"
std::shared_ptr<::app_src_native_build_state_::NativeInputSignature> pathSignature(const std::string& path, bool contentHash) {
#line 310 "/src/native-build-driver.do"
    if (!::doof_fs::exists(path) || ::doof_fs::isDirectory(path)) {
#line 310 "/src/native-build-driver.do"
        return nullptr;
    }
#line 311 "/src/native-build-driver.do"
    auto _binding_value_38 = ::doof_fs::metadata(path);
    if (doof::is_failure(_binding_value_38)) {
        const auto& info = _binding_value_38;
#line 311 "/src/native-build-driver.do"
        return nullptr;
    }
    const auto info = doof::success_value(_binding_value_38);
#line 312 "/src/native-build-driver.do"
    const auto modifiedNanos = info->modifiedAt->toEpochNanos();
#line 313 "/src/native-build-driver.do"
    const auto signature = (contentHash ? ::std_::crypto::index::sha256Hex([&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 313, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }()) : ((doof::to_string(info->size) + std::string(":")) + doof::to_string(modifiedNanos)));
#line 314 "/src/native-build-driver.do"
    return std::make_shared<::app_src_native_build_state_::NativeInputSignature>(path, signature, contentHash, info->size, modifiedNanos);
}
#line 317 "/src/native-build-driver.do"
std::shared_ptr<::app_src_native_build_state_::NativeInputSignature> currentInputSignature(const std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>& previous) {
#line 318 "/src/native-build-driver.do"
    if (!::doof_fs::exists(previous->path) || ::doof_fs::isDirectory(previous->path)) {
#line 318 "/src/native-build-driver.do"
        return nullptr;
    }
#line 319 "/src/native-build-driver.do"
    auto _binding_value_39 = ::doof_fs::metadata(previous->path);
    if (doof::is_failure(_binding_value_39)) {
        const auto& info = _binding_value_39;
#line 319 "/src/native-build-driver.do"
        return nullptr;
    }
    const auto info = doof::success_value(_binding_value_39);
#line 320 "/src/native-build-driver.do"
    const auto modifiedNanos = info->modifiedAt->toEpochNanos();
#line 321 "/src/native-build-driver.do"
    if ((previous->size == info->size) && (previous->modifiedNanos == modifiedNanos)) {
#line 322 "/src/native-build-driver.do"
        return std::make_shared<::app_src_native_build_state_::NativeInputSignature>(previous->path, previous->signature, previous->contentHash, info->size, modifiedNanos);
    }
#line 327 "/src/native-build-driver.do"
    return pathSignature(previous->path, previous->contentHash);
}
#line 330 "/src/native-build-driver.do"
bool taskIsCurrent(const std::shared_ptr<::app_src_native_build_state_::NativeTaskState>& previous, const std::string& fingerprint, const std::shared_ptr<std::vector<std::string>>& auxiliaryOutputPaths) {
#line 335 "/src/native-build-driver.do"
    if (doof::is_null(previous) || !::doof_fs::exists(previous->outputPath)) {
#line 335 "/src/native-build-driver.do"
        return false;
    }
#line 336 "/src/native-build-driver.do"
    const auto& _iterable_41 = auxiliaryOutputPaths;
    for (const auto& path : *_iterable_41) {
#line 336 "/src/native-build-driver.do"
        if (!::doof_fs::exists(path) || ::doof_fs::isDirectory(path)) {
#line 336 "/src/native-build-driver.do"
            return false;
        }
    }
#line 337 "/src/native-build-driver.do"
    auto _binding_value_42 = ::doof_fs::metadata(previous->outputPath);
    if (doof::is_failure(_binding_value_42)) {
        const auto& info = _binding_value_42;
#line 337 "/src/native-build-driver.do"
        return false;
    }
    const auto info = doof::success_value(_binding_value_42);
#line 338 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>> currentInputs = std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{});
#line 339 "/src/native-build-driver.do"
    const auto& _iterable_44 = previous->inputs;
    for (const auto& input : *_iterable_44) {
#line 340 "/src/native-build-driver.do"
        const auto signature = currentInputSignature(input);
#line 341 "/src/native-build-driver.do"
        if (doof::is_null(signature)) {
#line 341 "/src/native-build-driver.do"
            return false;
        }
#line 342 "/src/native-build-driver.do"
        currentInputs->push_back(doof::unwrap_optional(signature));
    }
#line 344 "/src/native-build-driver.do"
    return nativeTaskStateIsCurrent(previous, fingerprint, info->size, info->modifiedAt->toEpochNanos(), currentInputs, true);
}
#line 348 "/src/native-build-driver.do"
bool nativeTaskStateIsCurrent(const std::shared_ptr<::app_src_native_build_state_::NativeTaskState>& previous, const std::string& fingerprint, int64_t outputSize, int64_t outputModifiedNanos, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>& currentInputs, bool auxiliaryOutputsCurrent) {
#line 356 "/src/native-build-driver.do"
    if (!auxiliaryOutputsCurrent) {
#line 356 "/src/native-build-driver.do"
        return false;
    }
#line 357 "/src/native-build-driver.do"
    if (doof::is_null(previous) || (previous->fingerprint != fingerprint)) {
#line 357 "/src/native-build-driver.do"
        return false;
    }
#line 358 "/src/native-build-driver.do"
    if ((previous->outputSize != outputSize) || (previous->outputModifiedNanos != outputModifiedNanos)) {
#line 358 "/src/native-build-driver.do"
        return false;
    }
#line 359 "/src/native-build-driver.do"
    if ((static_cast<int32_t>((previous->inputs)->size()) == 0) || (static_cast<int32_t>((previous->inputs)->size()) != static_cast<int32_t>((currentInputs)->size()))) {
#line 359 "/src/native-build-driver.do"
        return false;
    }
#line 360 "/src/native-build-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>((previous->inputs)->size()); ++index) {
#line 361 "/src/native-build-driver.do"
        const auto expected = doof::array_at(previous->inputs, index, "src/native-build-driver", 361);
#line 362 "/src/native-build-driver.do"
        const auto current = doof::array_at(currentInputs, index, "src/native-build-driver", 362);
#line 363 "/src/native-build-driver.do"
        if (((((expected->path != current->path) || (expected->signature != current->signature)) || (expected->contentHash != current->contentHash)) || (expected->size != current->size)) || (expected->modifiedNanos != current->modifiedNanos)) {
#line 364 "/src/native-build-driver.do"
            return false;
        }
    }
#line 366 "/src/native-build-driver.do"
    return true;
}
#line 369 "/src/native-build-driver.do"
std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureTaskState(const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task, const std::string& fingerprint) {
#line 370 "/src/native-build-driver.do"
    const auto info = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(task->outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 370, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 371 "/src/native-build-driver.do"
    const auto state = std::make_shared<::app_src_native_build_state_::NativeTaskState>(task->id, fingerprint, task->outputPath, info->size, info->modifiedAt->toEpochNanos(), std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{}));
#line 372 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::string>> paths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{task->sourcePath});
#line 373 "/src/native-build-driver.do"
    if ((task->dependencyFilePath != std::string("")) && ::doof_fs::exists(task->dependencyFilePath)) {
#line 374 "/src/native-build-driver.do"
        const auto dependencySource = [&]() -> std::string { auto _try_value = ::doof_fs::readText(task->dependencyFilePath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 374, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 375 "/src/native-build-driver.do"
        const auto dependencies = (doof::string_endsWith(doof::string_toLowerCase(task->dependencyFilePath), std::string(".json")) ? ::app_src_native_build_state_::parseMsvcDependencies(dependencySource) : ::app_src_native_build_state_::parseMakeDependencies(dependencySource));
#line 378 "/src/native-build-driver.do"
        const auto& _iterable_47 = dependencies;
        for (const auto& path : *_iterable_47) {
#line 378 "/src/native-build-driver.do"
            appendUnique(paths, path);
        }
    }
#line 380 "/src/native-build-driver.do"
    const auto& _iterable_49 = paths;
    for (const auto& path : *_iterable_49) {
#line 381 "/src/native-build-driver.do"
        const auto signature = pathSignature(path, true);
#line 382 "/src/native-build-driver.do"
        if (!doof::is_null(signature)) {
#line 382 "/src/native-build-driver.do"
            state->inputs->push_back(doof::unwrap_optional(signature));
        }
    }
#line 384 "/src/native-build-driver.do"
    return state;
}
#line 387 "/src/native-build-driver.do"
std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureLinkState(const std::string& outputPath, const std::string& fingerprint, const std::shared_ptr<std::vector<std::string>>& objectPaths) {
#line 388 "/src/native-build-driver.do"
    const auto info = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 388, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 389 "/src/native-build-driver.do"
    const auto state = std::make_shared<::app_src_native_build_state_::NativeTaskState>((std::string("link:") + outputPath), fingerprint, outputPath, info->size, info->modifiedAt->toEpochNanos(), std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>{}));
#line 390 "/src/native-build-driver.do"
    const auto& _iterable_51 = objectPaths;
    for (const auto& path : *_iterable_51) {
#line 391 "/src/native-build-driver.do"
        const auto signature = pathSignature(path, false);
#line 392 "/src/native-build-driver.do"
        if (!doof::is_null(signature)) {
#line 392 "/src/native-build-driver.do"
            state->inputs->push_back(doof::unwrap_optional(signature));
        }
    }
#line 394 "/src/native-build-driver.do"
    return state;
}
#line 397 "/src/native-build-driver.do"
std::shared_ptr<::app_src_native_build_state_::NativeBuildState> readBuildState(const std::string& path) {
#line 398 "/src/native-build-driver.do"
    if (!::doof_fs::exists(path)) {
#line 398 "/src/native-build-driver.do"
        return std::make_shared<::app_src_native_build_state_::NativeBuildState>(2, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
#line 399 "/src/native-build-driver.do"
    auto _binding_value_52 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_52)) {
        const auto& source = _binding_value_52;
#line 399 "/src/native-build-driver.do"
        return std::make_shared<::app_src_native_build_state_::NativeBuildState>(2, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    const auto source = doof::success_value(_binding_value_52);
#line 400 "/src/native-build-driver.do"
    const auto parsed = ::app_src_native_build_state_::parseNativeBuildState(source);
#line 401 "/src/native-build-driver.do"
    return (doof::is_null(parsed) ? std::make_shared<::app_src_native_build_state_::NativeBuildState>(2, std::make_shared<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>(std::vector<std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : doof::unwrap_optional(parsed));
}
#line 404 "/src/native-build-driver.do"
void writeBuildState(const std::string& path, const std::shared_ptr<::app_src_native_build_state_::NativeBuildState>& state) {
#line 405 "/src/native-build-driver.do"
    const auto temporaryPath = (path + std::string(".tmp"));
#line 406 "/src/native-build-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(temporaryPath, ::app_src_native_build_state_::renderNativeBuildState(state)); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 406, std::string("try! failed"));  }();
#line 407 "/src/native-build-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::rename(temporaryPath, path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 407, std::string("try! failed"));  }();
}
#line 410 "/src/native-build-driver.do"
void writeTextIfChanged(const std::string& path, const std::string& content) {
#line 411 "/src/native-build-driver.do"
    if (::doof_fs::exists(path)) {
#line 412 "/src/native-build-driver.do"
        auto _binding_value_53 = ::doof_fs::readText(path);
        if (doof::is_failure(_binding_value_53)) {
            const auto& previous = _binding_value_53;
#line 412 "/src/native-build-driver.do"
            [&]() -> void { auto _try_value = ::doof_fs::writeText(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 412, std::string("try! failed"));  }();
#line 412 "/src/native-build-driver.do"
            return;
        }
        const auto previous = doof::success_value(_binding_value_53);
#line 413 "/src/native-build-driver.do"
        if (!nativeSupportFileNeedsWrite(previous, content)) {
#line 413 "/src/native-build-driver.do"
            return;
        }
    }
#line 415 "/src/native-build-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 415, std::string("try! failed"));  }();
}
#line 419 "/src/native-build-driver.do"
bool nativeSupportFileNeedsWrite(const std::optional<std::string>& previous, const std::string& content) {
#line 420 "/src/native-build-driver.do"
    return (doof::is_null(previous) || (previous.value() != content));
}
#line 424 "/src/native-build-driver.do"
std::string msvcLinkResponseFile(const std::shared_ptr<std::vector<std::string>>& arguments) {
#line 425 "/src/native-build-driver.do"
    auto content = std::string("");
#line 426 "/src/native-build-driver.do"
    const auto& _iterable_55 = arguments;
    for (const auto& argument : *_iterable_55) {
#line 426 "/src/native-build-driver.do"
        (content = ((content + quoteMsvcResponseArgument(argument)) + std::string("\n")));
    }
#line 427 "/src/native-build-driver.do"
    return content;
}
#line 430 "/src/native-build-driver.do"
std::string quoteMsvcResponseArgument(const std::string& argument) {
#line 431 "/src/native-build-driver.do"
    auto quoted = std::string("\"");
#line 432 "/src/native-build-driver.do"
    auto backslashes = 0;
#line 433 "/src/native-build-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>(argument.size()); ++index) {
#line 434 "/src/native-build-driver.do"
        const auto value = doof::string_at(argument, index, "src/native-build-driver", 434);
#line 435 "/src/native-build-driver.do"
        if (value == U'\\') {
#line 435 "/src/native-build-driver.do"
            (backslashes += 1);
#line 435 "/src/native-build-driver.do"
            continue;
        }
#line 436 "/src/native-build-driver.do"
        if (value == U'\u0022') {
#line 437 "/src/native-build-driver.do"
            (quoted = ((quoted + doof::string_repeat(std::string("\\"), ((backslashes * 2) + 1))) + std::string("\"")));
        } else {
#line 439 "/src/native-build-driver.do"
            (quoted = ((quoted + doof::string_repeat(std::string("\\"), backslashes)) + doof::to_string(value)));
        }
#line 441 "/src/native-build-driver.do"
        (backslashes = 0);
    }
#line 443 "/src/native-build-driver.do"
    return ((quoted + doof::string_repeat(std::string("\\"), (backslashes * 2))) + std::string("\""));
}
#line 446 "/src/native-build-driver.do"
void collectManagedOutputs(const std::shared_ptr<std::vector<std::string>>& outputs, const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project) {
#line 447 "/src/native-build-driver.do"
    std::shared_ptr<doof::ordered_set<std::string>> indexed = std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{});
#line 448 "/src/native-build-driver.do"
    const auto& _iterable_58 = outputs;
    for (const auto& output : *_iterable_58) {
#line 448 "/src/native-build-driver.do"
        indexed->insert(output);
    }
#line 449 "/src/native-build-driver.do"
    collectManagedOutputsIndexed(outputs, indexed, outputDirectory, plan, project);
}
#line 452 "/src/native-build-driver.do"
void collectManagedOutputsIndexed(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project) {
#line 459 "/src/native-build-driver.do"
    appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, std::string("doof_runtime.hpp")));
#line 460 "/src/native-build-driver.do"
    const auto& _iterable_60 = plan->supportFiles;
    for (const auto& supportFile : *_iterable_60) {
#line 460 "/src/native-build-driver.do"
        appendManagedOutput(outputs, indexed, supportFile->outputPath);
    }
#line 461 "/src/native-build-driver.do"
    const auto& _iterable_62 = project->modules;
    for (const auto& module : *_iterable_62) {
#line 462 "/src/native-build-driver.do"
        appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, module->headerName));
#line 463 "/src/native-build-driver.do"
        appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, module->sourceName));
    }
#line 465 "/src/native-build-driver.do"
    const auto& _iterable_64 = project->supportFiles;
    for (const auto& supportFile : *_iterable_64) {
#line 465 "/src/native-build-driver.do"
        appendManagedOutput(outputs, indexed, joinOutput(outputDirectory, supportFile->relativePath));
    }
#line 466 "/src/native-build-driver.do"
    const auto& _iterable_66 = project->nativeCopies;
    for (const auto& nativeCopy : *_iterable_66) {
#line 467 "/src/native-build-driver.do"
        collectManagedNativeCopyOutputs(outputs, indexed, nativeCopy->sourcePath, joinOutput(outputDirectory, nativeCopy->relativePath));
    }
#line 469 "/src/native-build-driver.do"
    if (!doof::is_null(plan->precompiledHeaderTask)) {
#line 470 "/src/native-build-driver.do"
        appendManagedOutput(outputs, indexed, plan->precompiledHeaderTask->outputPath);
#line 471 "/src/native-build-driver.do"
        if (plan->precompiledHeaderTask->dependencyFilePath != std::string("")) {
#line 471 "/src/native-build-driver.do"
            appendManagedOutput(outputs, indexed, plan->precompiledHeaderTask->dependencyFilePath);
        }
#line 472 "/src/native-build-driver.do"
        const auto& _iterable_68 = plan->precompiledHeaderTask->auxiliaryOutputPaths;
        for (const auto& path : *_iterable_68) {
#line 472 "/src/native-build-driver.do"
            appendManagedOutput(outputs, indexed, path);
        }
    }
#line 474 "/src/native-build-driver.do"
    const auto& _iterable_70 = plan->compileTasks;
    for (const auto& task : *_iterable_70) {
#line 475 "/src/native-build-driver.do"
        appendManagedOutput(outputs, indexed, task->outputPath);
#line 476 "/src/native-build-driver.do"
        if (task->dependencyFilePath != std::string("")) {
#line 476 "/src/native-build-driver.do"
            appendManagedOutput(outputs, indexed, task->dependencyFilePath);
        }
#line 477 "/src/native-build-driver.do"
        const auto& _iterable_72 = task->auxiliaryOutputPaths;
        for (const auto& path : *_iterable_72) {
#line 477 "/src/native-build-driver.do"
            appendManagedOutput(outputs, indexed, path);
        }
    }
#line 479 "/src/native-build-driver.do"
    if (isMsvcLinker(plan->linker)) {
#line 479 "/src/native-build-driver.do"
        appendManagedOutput(outputs, indexed, msvcLinkResponsePath(outputDirectory));
    }
#line 480 "/src/native-build-driver.do"
    appendManagedOutput(outputs, indexed, plan->outputPath);
}
#line 483 "/src/native-build-driver.do"
void collectManagedNativeCopyOutputs(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& sourcePath, const std::string& outputPath) {
#line 484 "/src/native-build-driver.do"
    if (!::doof_fs::isDirectory(sourcePath)) {
#line 485 "/src/native-build-driver.do"
        appendManagedOutput(outputs, indexed, outputPath);
#line 486 "/src/native-build-driver.do"
        return;
    }
#line 488 "/src/native-build-driver.do"
    const auto& _iterable_74 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 488, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    for (const auto& entry : *_iterable_74) {
#line 489 "/src/native-build-driver.do"
        collectManagedNativeCopyOutputs(outputs, indexed, joinOutput(sourcePath, entry->name), joinOutput(outputPath, entry->name));
    }
}
#line 493 "/src/native-build-driver.do"
void removeStaleOutputs(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current, const std::string& outputDirectory) {
#line 494 "/src/native-build-driver.do"
    const auto& _iterable_76 = staleManagedOutputCandidates(previous, current, outputDirectory);
    for (const auto& path : *_iterable_76) {
#line 495 "/src/native-build-driver.do"
        if (::doof_fs::exists(path) && !::doof_fs::isDirectory(path)) {
#line 495 "/src/native-build-driver.do"
            [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 495, std::string("try! failed"));  }();
        }
    }
}
#line 500 "/src/native-build-driver.do"
std::shared_ptr<std::vector<std::string>> staleManagedOutputCandidates(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current, const std::string& outputDirectory) {
#line 501 "/src/native-build-driver.do"
    const auto prefix = (doof::string_endsWith(outputDirectory, std::string("/")) ? outputDirectory : (outputDirectory + std::string("/")));
#line 502 "/src/native-build-driver.do"
    std::shared_ptr<doof::ordered_set<std::string>> retained = std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{});
#line 503 "/src/native-build-driver.do"
    const auto& _iterable_78 = current;
    for (const auto& path : *_iterable_78) {
#line 503 "/src/native-build-driver.do"
        retained->insert(path);
    }
#line 504 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::string>> stale = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 505 "/src/native-build-driver.do"
    const auto& _iterable_80 = previous;
    for (const auto& path : *_iterable_80) {
#line 506 "/src/native-build-driver.do"
        if ((retained->count(path) > 0) || !doof::string_startsWith(path, prefix)) {
#line 506 "/src/native-build-driver.do"
            continue;
        }
#line 507 "/src/native-build-driver.do"
        stale->push_back(path);
    }
#line 509 "/src/native-build-driver.do"
    return stale;
}
#line 513 "/src/native-build-driver.do"
bool nativeManagedOutputsChanged(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current) {
#line 514 "/src/native-build-driver.do"
    if (static_cast<int32_t>((previous)->size()) != static_cast<int32_t>((current)->size())) {
#line 514 "/src/native-build-driver.do"
        return true;
    }
#line 515 "/src/native-build-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>((previous)->size()); ++index) {
#line 516 "/src/native-build-driver.do"
        if (doof::array_at(previous, index, "src/native-build-driver", 516) != doof::array_at(current, index, "src/native-build-driver", 516)) {
#line 516 "/src/native-build-driver.do"
            return true;
        }
    }
#line 518 "/src/native-build-driver.do"
    return false;
}
#line 521 "/src/native-build-driver.do"
std::shared_ptr<std::vector<std::string>> mutableArguments(const std::shared_ptr<std::vector<std::string>>& arguments) {
#line 522 "/src/native-build-driver.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 523 "/src/native-build-driver.do"
    const auto& _iterable_83 = arguments;
    for (const auto& argument : *_iterable_83) {
#line 523 "/src/native-build-driver.do"
        result->push_back(argument);
    }
#line 524 "/src/native-build-driver.do"
    return result;
}
#line 527 "/src/native-build-driver.do"
bool contains(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 528 "/src/native-build-driver.do"
    const auto& _iterable_85 = values;
    for (const auto& existing : *_iterable_85) {
#line 528 "/src/native-build-driver.do"
        if (existing == value) {
#line 528 "/src/native-build-driver.do"
            return true;
        }
    }
#line 529 "/src/native-build-driver.do"
    return false;
}
#line 532 "/src/native-build-driver.do"
void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 533 "/src/native-build-driver.do"
    if (!contains(values, value)) {
#line 533 "/src/native-build-driver.do"
        values->push_back(value);
    }
}
#line 536 "/src/native-build-driver.do"
void appendManagedOutput(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& value) {
#line 537 "/src/native-build-driver.do"
    if (indexed->count(value) > 0) {
#line 537 "/src/native-build-driver.do"
        return;
    }
#line 538 "/src/native-build-driver.do"
    indexed->insert(value);
#line 539 "/src/native-build-driver.do"
    outputs->push_back(value);
}
#line 542 "/src/native-build-driver.do"
std::string joinOutput(const std::string& directory, const std::string& name) {
#line 542 "/src/native-build-driver.do"
    return (doof::string_endsWith(directory, std::string("/")) ? (directory + name) : ((directory + std::string("/")) + name));
}
#line 543 "/src/native-build-driver.do"
std::string msvcLinkResponsePath(const std::string& outputDirectory) {
#line 543 "/src/native-build-driver.do"
    return joinOutput(outputDirectory, std::string(".doof-link.rsp"));
}
#line 544 "/src/native-build-driver.do"
bool isMsvcLinker(const std::string& linker) {
#line 545 "/src/native-build-driver.do"
    const auto normalized = doof::string_toLowerCase(doof::string_replaceAll(linker, std::string("\\"), std::string("/")));
#line 546 "/src/native-build-driver.do"
    return ((((normalized == std::string("link")) || (normalized == std::string("link.exe"))) || doof::string_endsWith(normalized, std::string("/link"))) || doof::string_endsWith(normalized, std::string("/link.exe")));
}
#line 548 "/src/native-build-driver.do"
std::string parentDirectory(const std::string& path) {
#line 549 "/src/native-build-driver.do"
    auto index = (static_cast<int32_t>(path.size()) - 1);
#line 550 "/src/native-build-driver.do"
    while ((index > 0) && (doof::string_at(path, index, "src/native-build-driver", 550) != U'\u002F')) {
#line 550 "/src/native-build-driver.do"
        (index -= 1);
    }
#line 551 "/src/native-build-driver.do"
    return ((index <= 0) ? std::string("/") : doof::string_substring(path, 0, index));
}
#line 554 "/src/native-build-driver.do"
void ensureDirectory(const std::string& path) {
#line 555 "/src/native-build-driver.do"
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
#line 555 "/src/native-build-driver.do"
        return;
    }
#line 556 "/src/native-build-driver.do"
    const auto parent = parentDirectory(path);
#line 557 "/src/native-build-driver.do"
    if (parent != path) {
#line 557 "/src/native-build-driver.do"
        ensureDirectory(parent);
    }
#line 558 "/src/native-build-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/native-build-driver", 558, std::string("try! failed"));  }();
}
#line 1 "<doof-generated>"
void printFlushed(const std::string& value) {
    ::doof::print_flushed(value);
}
}
