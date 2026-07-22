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
namespace app_src_emitter_project_ { struct ProjectEmission; }
namespace app_src_native_build_ { struct NativeCompilePlan; }
namespace app_src_native_build_ { struct NativeCompileTask; }
namespace app_src_native_build_state_ { struct NativeBuildState; }
namespace app_src_native_build_state_ { struct NativeInputSignature; }
namespace app_src_native_build_state_ { struct NativeTaskState; }
namespace app_src_pkg_config_ { struct PkgConfigCommandResult; }
namespace std_::blob::index { struct BlobReader; }
namespace std_::os::index { struct ExecOptions; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_native_build_driver_ {
    struct NativeCommandResult;
    struct NativeCompilerBatchResult;
    struct NativeCompilerIdentity;
    struct NativeCompilerWorker;
}

#include "src_emitter_project.hpp"
#include "src_native_build.hpp"
#include "src_native_build_state.hpp"
#include "src_pkg_config.hpp"
#include "std_blob_index.hpp"
#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_os_index.hpp"

namespace app_src_native_build_driver_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct NativeCommandResult : public std::enable_shared_from_this<NativeCommandResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    std::string error = std::string("");
    bool truncated;
    NativeCommandResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> output, std::string error, bool truncated) : exitCode(exitCode), output(output), error(error), truncated(truncated) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCommandResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilerBatchResult : public std::enable_shared_from_this<NativeCompilerBatchResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<std::shared_ptr<NativeCommandResult>>> outputs;
    NativeCompilerBatchResult(int32_t exitCode, std::shared_ptr<std::vector<std::shared_ptr<NativeCommandResult>>> outputs) : exitCode(exitCode), outputs(outputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilerBatchResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilerIdentity : public std::enable_shared_from_this<NativeCompilerIdentity> {
    std::string command;
    std::string signature;
    NativeCompilerIdentity(std::string command, std::string signature) : command(command), signature(signature) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilerIdentity>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilerWorker : public std::enable_shared_from_this<NativeCompilerWorker> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>> tasks;
    NativeCompilerWorker(std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>> tasks) : tasks(tasks) {}
    std::shared_ptr<NativeCompilerBatchResult> compile();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilerWorker>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<NativeCommandResult> runBuildCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments);
    int32_t printBuildOutput(std::shared_ptr<NativeCommandResult> result, int32_t remainingLines);
    int32_t buildNativeProject(std::string compilerOverride, std::string outputDirectory, std::string outputPath, std::shared_ptr<::app_src_emitter_project_::ProjectEmission> project, bool release, std::string platform);
    std::string envCompiler();
    int32_t executeNativePlan(std::string outputDirectory, std::shared_ptr<::app_src_native_build_::NativeCompilePlan> plan, std::shared_ptr<::app_src_emitter_project_::ProjectEmission> project);
    std::string compilerIdentity(std::string command, std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities);
    std::string taskFingerprint(std::shared_ptr<::app_src_native_build_::NativeCompileTask> task, std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities);
    std::string linkFingerprint(std::string linker, std::shared_ptr<std::vector<std::string>> arguments, std::string outputPath, std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>> identities);
    std::optional<std::string> pathSignature(std::string path, bool contentHash);
    bool taskIsCurrent(std::shared_ptr<::app_src_native_build_state_::NativeTaskState> previous, std::string fingerprint);
    bool nativeTaskStateIsCurrent(std::shared_ptr<::app_src_native_build_state_::NativeTaskState> previous, std::string fingerprint, int64_t outputSize, int64_t outputModifiedNanos, std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>> currentInputs);
    std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureTaskState(std::shared_ptr<::app_src_native_build_::NativeCompileTask> task, std::string fingerprint);
    std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureLinkState(std::string outputPath, std::string fingerprint, std::shared_ptr<std::vector<std::string>> objectPaths);
    std::shared_ptr<::app_src_native_build_state_::NativeBuildState> readBuildState(std::string path);
    void writeBuildState(std::string path, std::shared_ptr<::app_src_native_build_state_::NativeBuildState> state);
    void collectManagedOutputs(std::shared_ptr<std::vector<std::string>> outputs, std::string outputDirectory, std::shared_ptr<::app_src_native_build_::NativeCompilePlan> plan, std::shared_ptr<::app_src_emitter_project_::ProjectEmission> project);
    void collectManagedNativeCopyOutputs(std::shared_ptr<std::vector<std::string>> outputs, std::string sourcePath, std::string outputPath);
    void removeStaleOutputs(std::shared_ptr<std::vector<std::string>> previous, std::shared_ptr<std::vector<std::string>> current, std::string outputDirectory);
    std::shared_ptr<std::vector<std::string>> mutableArguments(std::shared_ptr<std::vector<std::string>> arguments);
    bool contains(std::shared_ptr<std::vector<std::string>> values, std::string value);
    void appendUnique(std::shared_ptr<std::vector<std::string>> values, std::string value);
    std::string joinOutput(std::string directory, std::string name);
    std::string parentDirectory(std::string path);
    void ensureDirectory(std::string path);
}

namespace app_src_native_build_driver_ {
}
