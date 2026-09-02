#pragma once
#include "doof_runtime.hpp"
namespace app_src_emitter_module_ {
    struct ModuleEmission;
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan;
}

namespace app_src_native_build_ {
    struct NativeCompileTask;
    struct NativeBuildSupportFile;
    struct NativeCompilePlan;
}

namespace app_src_native_build_ {
    enum class NativeBuildMode {
    Debug = 0,
    Release = 1,
    Profile = 2
};
inline const char* NativeBuildMode_name(NativeBuildMode value) {
  switch (value) {
    case NativeBuildMode::Debug: return "Debug";
    case NativeBuildMode::Release: return "Release";
    case NativeBuildMode::Profile: return "Profile";
  }
  doof::panic(std::string("Invalid NativeBuildMode enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<NativeBuildMode> NativeBuildMode_fromName(std::string_view value) {
  if (value == "Debug") return NativeBuildMode::Debug;
  if (value == "Release") return NativeBuildMode::Release;
  if (value == "Profile") return NativeBuildMode::Profile;
  return std::nullopt;
}
inline int32_t NativeBuildMode_value(NativeBuildMode value) { return static_cast<int32_t>(value); }
inline std::optional<NativeBuildMode> NativeBuildMode_fromValue(int32_t value) {
  if (value == 0) return NativeBuildMode::Debug;
  if (value == 1) return NativeBuildMode::Release;
  if (value == 2) return NativeBuildMode::Profile;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<NativeBuildMode>> NativeBuildMode_values() { return std::make_shared<std::vector<NativeBuildMode>>(std::initializer_list<NativeBuildMode>{NativeBuildMode::Debug, NativeBuildMode::Release, NativeBuildMode::Profile}); }
inline doof::JsonValue NativeBuildMode_toJsonValue(NativeBuildMode value) { return doof::json_value(NativeBuildMode_value(value)); }
inline doof::Result<NativeBuildMode, std::string> NativeBuildMode_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum NativeBuildMode, got ") + doof::json_type_name(value)};
  auto resolved = NativeBuildMode_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum NativeBuildMode: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2"};
  return doof::Success<NativeBuildMode>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, NativeBuildMode value) { return output << NativeBuildMode_name(value); }
}

namespace app_src_emitter_module_ {
    struct ModuleEmission : public std::enable_shared_from_this<ModuleEmission> {
    std::string modulePath;
    std::string header;
    std::string source;
    std::string headerName;
    std::string sourceName;
    int32_t coverageModuleId;
    std::shared_ptr<std::vector<int32_t>> instrumentedLines;
    bool reused;
    std::string fingerprint;
    ModuleEmission(std::string modulePath, std::string header, std::string source, std::string headerName, std::string sourceName, int32_t coverageModuleId, std::shared_ptr<std::vector<int32_t>> instrumentedLines, bool reused, std::string fingerprint) : modulePath(modulePath), header(header), source(source), headerName(headerName), sourceName(sourceName), coverageModuleId(coverageModuleId), instrumentedLines(instrumentedLines), reused(reused), fingerprint(fingerprint) {}
};
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan : public std::enable_shared_from_this<NativeBuildPlan> {
    std::shared_ptr<std::vector<std::string>> includePaths;
    std::shared_ptr<std::vector<std::string>> sourceFiles;
    std::shared_ptr<std::vector<std::string>> libraryPaths;
    std::shared_ptr<std::vector<std::string>> extraCopyPaths;
    std::shared_ptr<std::vector<std::string>> linkLibraries;
    std::shared_ptr<std::vector<std::string>> frameworks;
    std::shared_ptr<std::vector<std::string>> pkgConfigPackages;
    std::shared_ptr<std::vector<std::string>> defines;
    std::shared_ptr<std::vector<std::string>> compilerFlags;
    std::shared_ptr<std::vector<std::string>> linkerFlags;
    NativeBuildPlan(std::shared_ptr<std::vector<std::string>> includePaths, std::shared_ptr<std::vector<std::string>> sourceFiles, std::shared_ptr<std::vector<std::string>> libraryPaths, std::shared_ptr<std::vector<std::string>> extraCopyPaths, std::shared_ptr<std::vector<std::string>> linkLibraries, std::shared_ptr<std::vector<std::string>> frameworks, std::shared_ptr<std::vector<std::string>> pkgConfigPackages, std::shared_ptr<std::vector<std::string>> defines, std::shared_ptr<std::vector<std::string>> compilerFlags, std::shared_ptr<std::vector<std::string>> linkerFlags) : includePaths(includePaths), sourceFiles(sourceFiles), libraryPaths(libraryPaths), extraCopyPaths(extraCopyPaths), linkLibraries(linkLibraries), frameworks(frameworks), pkgConfigPackages(pkgConfigPackages), defines(defines), compilerFlags(compilerFlags), linkerFlags(linkerFlags) {}
};
}

namespace app_src_native_build_ {
    struct NativeCompileTask : public std::enable_shared_from_this<NativeCompileTask> {
    std::string id;
    std::string compiler;
    std::string sourcePath;
    std::string outputPath;
    std::string dependencyFilePath;
    std::shared_ptr<std::vector<std::string>> auxiliaryOutputPaths;
    bool usesPrecompiledHeader;
    std::shared_ptr<std::vector<std::string>> arguments;
    NativeCompileTask(std::string id, std::string compiler, std::string sourcePath, std::string outputPath, std::string dependencyFilePath, std::shared_ptr<std::vector<std::string>> auxiliaryOutputPaths, bool usesPrecompiledHeader, std::shared_ptr<std::vector<std::string>> arguments) : id(id), compiler(compiler), sourcePath(sourcePath), outputPath(outputPath), dependencyFilePath(dependencyFilePath), auxiliaryOutputPaths(auxiliaryOutputPaths), usesPrecompiledHeader(usesPrecompiledHeader), arguments(arguments) {}
};
    struct NativeBuildSupportFile : public std::enable_shared_from_this<NativeBuildSupportFile> {
    std::string outputPath;
    std::string content;
    NativeBuildSupportFile(std::string outputPath, std::string content) : outputPath(outputPath), content(content) {}
};
    struct NativeCompilePlan : public std::enable_shared_from_this<NativeCompilePlan> {
    std::string compiler;
    std::string linker;
    std::shared_ptr<std::vector<std::shared_ptr<NativeBuildSupportFile>>> supportFiles;
    std::shared_ptr<NativeCompileTask> precompiledHeaderTask;
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks;
    std::shared_ptr<std::vector<std::string>> linkArguments;
    std::string outputPath;
    NativeCompilePlan(std::string compiler, std::string linker, std::shared_ptr<std::vector<std::shared_ptr<NativeBuildSupportFile>>> supportFiles, std::shared_ptr<NativeCompileTask> precompiledHeaderTask, std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks, std::shared_ptr<std::vector<std::string>> linkArguments, std::string outputPath) : compiler(compiler), linker(linker), supportFiles(supportFiles), precompiledHeaderTask(precompiledHeaderTask), compileTasks(compileTasks), linkArguments(linkArguments), outputPath(outputPath) {}
};
}

namespace std_::crypto::index {
    std::string sha1HexString(const std::string& text);
}

namespace app_src_native_build_ {
    bool isMsvcCompiler(const std::string& compiler);
    std::shared_ptr<NativeCompilePlan> planNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, NativeBuildMode mode, const std::string& platform, const std::shared_ptr<std::vector<std::string>>& wasmExportNames, bool wasm, bool wasmCommand);
    std::shared_ptr<NativeCompilePlan> planMsvcNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, NativeBuildMode mode);
    std::string msvcPchHeaderSource();
    void appendMsvcObjectArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& sourcePath, const std::string& outputPath, const std::string& dependencyFilePath, bool cSource);
    void appendOptimizedLinkerArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& platform, bool swiftLink, bool stripSymbols);
    void appendLinkerOption(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& option, bool swiftLink);
    std::string replaceSourceExtension(const std::string& path, const std::string& extension);
    std::shared_ptr<std::vector<std::string>> copyArguments(const std::shared_ptr<std::vector<std::string>>& source);
    std::shared_ptr<std::vector<std::string>> copyNativeCompileArguments(const std::shared_ptr<std::vector<std::string>>& source, bool cSource);
    bool isCSource(const std::string& path);
    bool isSwiftSource(const std::string& path);
    bool hasSwiftSource(const std::shared_ptr<std::vector<std::string>>& paths);
    std::shared_ptr<std::vector<std::string>> swiftObjectArguments(const std::string& sourcePath, const std::string& objectPath, NativeBuildMode mode);
    std::string deriveCCompiler(const std::string& compiler);
    std::string wasmExportList(const std::shared_ptr<std::vector<std::string>>& names);
    void appendObjectArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& sourcePath, const std::string& outputPath);
    bool usesClangPrecompiledHeader(const std::string& compiler, const std::string& platform);
    std::string resolveBuildPath(const std::string& outputDirectory, const std::string& path);
}
