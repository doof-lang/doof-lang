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
namespace app_src_package_manifest_ { struct ExternalDependencyCommand; }
namespace app_src_package_manifest_ { struct PackageManifest; }
namespace std_::blob::index { struct BlobReader; }
namespace std_::os::index { struct ExecOptions; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_external_dependency_ {
    struct ExternalDependencyTarget;
}

#include "src_package_manifest.hpp"
#include "std_blob_index.hpp"
#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"

namespace app_src_external_dependency_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ExternalDependencyTarget : public std::enable_shared_from_this<ExternalDependencyTarget> {
    std::string nativeTarget;
    std::string sdkPath = std::string("");
    std::string targetTriple = std::string("");
    std::string configureHost = std::string("");
    int32_t jobs = 1;
    ExternalDependencyTarget(std::string nativeTarget, std::string sdkPath = std::string(""), std::string targetTriple = std::string(""), std::string configureHost = std::string(""), int32_t jobs = 1) : nativeTarget(nativeTarget), sdkPath(sdkPath), targetTriple(targetTriple), configureHost(configureHost), jobs(jobs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExternalDependencyTarget>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string externalPath(std::string directory, std::string name);
    doof::Result<void, std::string> ensureExternalDirectory(std::string path);
    doof::Result<void, std::string> removeExternalTree(std::string path);
    doof::Result<void, std::string> copyExternalPath(std::string sourcePath, std::string destinationPath);
    bool externalPathWithinRoot(std::string path, std::string root);
    doof::Result<std::string, std::string> commandOutput(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::shared_ptr<::std_::os::index::ExecOptions> options = std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, std::nullopt, nullptr));
    std::string externalCommandFingerprint(std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand> command);
    std::string externalSourceFingerprint(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency);
    std::string externalNativeFingerprint(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::shared_ptr<ExternalDependencyTarget> target);
    bool markerMatches(std::string path, std::string fingerprint);
    bool markerContentMatches(std::string path, std::string expected);
    void externalJsonSet(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string key, doof::JsonValue value);
    std::shared_ptr<std::vector<doof::JsonValue>> externalCommandsJson(std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand>>> commands);
    std::string externalSourceMarkerContent(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string fingerprint);
    std::string externalNativeMarkerContent(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::shared_ptr<ExternalDependencyTarget> target, std::string fingerprint);
    bool isEmptyExternalDirectory(std::string path);
    doof::Result<void, std::string> copyArchiveContents(std::string sourceRoot, std::string destination);
    doof::Result<std::string, std::string> strippedArchiveRoot(std::string extractRoot, int32_t count, std::string dependencyName);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> downloadExternalArchive(std::string url);
    doof::Result<void, std::string> acquireArchive(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string destination, std::string stagingRoot);
    doof::Result<void, std::string> acquireGit(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string destination, std::string stagingRoot);
    std::string applyExternalDependencySubstitutions(std::string value, std::string packageRoot, std::string destination, std::shared_ptr<ExternalDependencyTarget> target);
    doof::Result<void, std::string> runExternalCommands(std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string packageRoot, std::string destination, std::shared_ptr<ExternalDependencyTarget> target);
    doof::Result<void, std::string> acquirePackageExternalDependencies(std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::shared_ptr<ExternalDependencyTarget> target);
}

namespace app_src_external_dependency_ {
}
