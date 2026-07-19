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
namespace app_src_package_manifest_ { struct ExternalDependency; }
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace app_src_package_manifest_ { struct PackageManifest; }
namespace app_src_package_manifest_ { struct PackageResource; }
namespace app_src_macos_app_ { struct MacOSAppConfig; }
namespace app_src_macos_app_ { struct MacOSPackageConfig; }
namespace app_src_ios_app_ { struct IOSAppConfig; }
namespace app_src_ios_app_ { struct IOSPackageConfig; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_project_ {
    struct ProjectSpec;
}

#include "std_fs_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "src_package_manifest.hpp"
#include "src_macos_app.hpp"
#include "src_ios_app.hpp"

namespace app_src_project_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ProjectSpec : public std::enable_shared_from_this<ProjectSpec> {
    std::string rootDirectory;
    std::string manifestPath;
    std::string name;
    std::string entry;
    std::string buildDirectory;
    bool hasManifest;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>> externalDependencies;
    std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild;
    std::string target = std::string("");
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp = nullptr;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp = nullptr;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig = nullptr;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig = nullptr;
    ProjectSpec(std::string rootDirectory, std::string manifestPath, std::string name, std::string entry, std::string buildDirectory, bool hasManifest, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>> externalDependencies, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::string target = std::string(""), std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp = nullptr, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp = nullptr, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig = nullptr, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig = nullptr) : rootDirectory(rootDirectory), manifestPath(manifestPath), name(name), entry(entry), buildDirectory(buildDirectory), hasManifest(hasManifest), manifest(manifest), resources(resources), externalDependencies(externalDependencies), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ProjectSpec>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string projectManifestPath(std::string path);
    std::string environmentValue(std::string name);
    std::string fileName(std::string path);
    std::string parentPath(std::string path);
    std::string joinPath(std::string directory, std::string name);
    std::shared_ptr<ProjectSpec> readProjectSpec(std::string requestedPath, std::string platform = std::string(""), std::string targetOverride = std::string(""));
}

namespace app_src_project_ {
}
