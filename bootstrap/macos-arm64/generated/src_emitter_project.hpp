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
namespace app_src_emitter_module_ { struct ModuleGraphEmission; }
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace app_src_package_manifest_ { struct PackageManifest; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_emitter_project_ {
    struct NativePackageInput;
    struct ProjectNativeCopy;
    struct ProjectSupportFile;
    struct ProjectEmission;
}

#include "src_emitter_module.hpp"
#include "src_package_manifest.hpp"

namespace app_src_emitter_project_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct NativePackageInput : public std::enable_shared_from_this<NativePackageInput> {
    std::string logicalPrefix;
    std::string outputRoot;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    NativePackageInput(std::string logicalPrefix, std::string outputRoot, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest) : logicalPrefix(logicalPrefix), outputRoot(outputRoot), manifest(manifest) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativePackageInput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ProjectNativeCopy : public std::enable_shared_from_this<ProjectNativeCopy> {
    std::string sourcePath;
    std::string relativePath;
    ProjectNativeCopy(std::string sourcePath, std::string relativePath) : sourcePath(sourcePath), relativePath(relativePath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ProjectNativeCopy>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ProjectSupportFile : public std::enable_shared_from_this<ProjectSupportFile> {
    std::string relativePath;
    std::string content;
    ProjectSupportFile(std::string relativePath, std::string content) : relativePath(relativePath), content(content) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ProjectSupportFile>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ProjectEmission : public std::enable_shared_from_this<ProjectEmission> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules;
    std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> supportFiles = std::make_shared<std::vector<std::shared_ptr<ProjectSupportFile>>>(std::vector<std::shared_ptr<ProjectSupportFile>>{});
    std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> nativeCopies = std::make_shared<std::vector<std::shared_ptr<ProjectNativeCopy>>>(std::vector<std::shared_ptr<ProjectNativeCopy>>{});
    std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild;
    std::shared_ptr<std::vector<std::string>> wasmExportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    ProjectEmission(std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules, std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> supportFiles, std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> nativeCopies, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::shared_ptr<std::vector<std::string>> wasmExportNames) : modules(modules), supportFiles(supportFiles), nativeCopies(nativeCopies), nativeBuild(nativeBuild), wasmExportNames(wasmExportNames) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ProjectEmission>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<ProjectEmission> planProjectEmission(std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> graph, std::shared_ptr<std::vector<std::shared_ptr<NativePackageInput>>> packages);
    void planPackageSupportFiles(std::shared_ptr<ProjectEmission> project, std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> graph, std::shared_ptr<NativePackageInput> package_);
    void planPackageNativeBuild(std::shared_ptr<ProjectEmission> project, std::shared_ptr<NativePackageInput> package_);
    std::string addNativeCopy(std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> copies, std::shared_ptr<NativePackageInput> package_, std::string sourcePath);
    std::optional<std::string> logicalSuffix(std::string path, std::string prefix);
    std::string diskSuffix(std::string path, std::string root);
    std::string replaceDoExtension(std::string path);
    std::string projectJoinPath(std::string directory, std::string suffix);
    std::string projectParentPath(std::string path);
    void addSupportFile(std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> files, std::shared_ptr<ProjectSupportFile> file);
    void appendUniqueValues(std::shared_ptr<std::vector<std::string>> target, std::shared_ptr<std::vector<std::string>> values);
    void appendUnique(std::shared_ptr<std::vector<std::string>> target, std::string value);
}

namespace app_src_emitter_project_ {
}
