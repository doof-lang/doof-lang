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
namespace app_src_emitter_module_ { struct ModuleEmission; }
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_native_build_ {
    struct NativeCompileTask;
    struct NativeCompilePlan;
}

#include "src_emitter_module.hpp"
#include "src_package_manifest.hpp"
#include "std_crypto_index.hpp"

namespace app_src_native_build_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct NativeCompileTask : public std::enable_shared_from_this<NativeCompileTask> {
    std::string id;
    std::string compiler;
    std::string sourcePath;
    std::string outputPath;
    std::string dependencyFilePath = std::string("");
    bool usesPrecompiledHeader = false;
    std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    NativeCompileTask(std::string id, std::string compiler, std::string sourcePath, std::string outputPath, std::string dependencyFilePath = std::string(""), bool usesPrecompiledHeader = false, std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : id(id), compiler(compiler), sourcePath(sourcePath), outputPath(outputPath), dependencyFilePath(dependencyFilePath), usesPrecompiledHeader(usesPrecompiledHeader), arguments(arguments) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompileTask>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilePlan : public std::enable_shared_from_this<NativeCompilePlan> {
    std::string compiler;
    std::string linker;
    std::shared_ptr<NativeCompileTask> precompiledHeaderTask = nullptr;
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{});
    std::shared_ptr<std::vector<std::string>> linkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::string outputPath;
    NativeCompilePlan(std::string compiler, std::string linker, std::shared_ptr<NativeCompileTask> precompiledHeaderTask, std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks, std::shared_ptr<std::vector<std::string>> linkArguments, std::string outputPath) : compiler(compiler), linker(linker), precompiledHeaderTask(precompiledHeaderTask), compileTasks(compileTasks), linkArguments(linkArguments), outputPath(outputPath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilePlan>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    using NativeCompileTaskBatch = std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>;
    bool isMsvcCompiler(const std::string& compiler);
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>> batchNativeCompileTasks(const std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>& tasks, int32_t maximumWorkers = 8);
    std::shared_ptr<NativeCompilePlan> planNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, bool release = false, const std::string& platform = std::string(""), const std::shared_ptr<std::vector<std::string>>& wasmExportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), bool wasm = false);
    std::shared_ptr<NativeCompilePlan> planMsvcNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, bool release);
    void appendMsvcObjectArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& sourcePath, const std::string& outputPath, const std::string& dependencyFilePath, bool cSource);
    void appendReleaseLinkerArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& platform, bool swiftLink);
    void appendLinkerOption(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& option, bool swiftLink);
    std::string replaceSourceExtension(const std::string& path, const std::string& extension);
    std::shared_ptr<std::vector<std::string>> copyArguments(const std::shared_ptr<std::vector<std::string>>& source);
    std::shared_ptr<std::vector<std::string>> copyNativeCompileArguments(const std::shared_ptr<std::vector<std::string>>& source, bool cSource);
    bool isCSource(const std::string& path);
    bool isSwiftSource(const std::string& path);
    bool hasSwiftSource(const std::shared_ptr<std::vector<std::string>>& paths);
    std::shared_ptr<std::vector<std::string>> swiftObjectArguments(const std::string& sourcePath, const std::string& objectPath);
    std::string deriveCCompiler(const std::string& compiler);
    std::string wasmExportList(const std::shared_ptr<std::vector<std::string>>& names);
    void appendObjectArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& sourcePath, const std::string& outputPath);
    bool usesClangPrecompiledHeader(const std::string& compiler, const std::string& platform);
    std::string resolveBuildPath(const std::string& outputDirectory, const std::string& path);
}

namespace app_src_native_build_ {
}
