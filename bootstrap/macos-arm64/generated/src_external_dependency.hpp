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
    std::string externalPath(const std::string& directory, const std::string& name);
    doof::Result<void, std::string> ensureExternalDirectory(const std::string& path);
    doof::Result<void, std::string> removeExternalTree(const std::string& path);
    doof::Result<void, std::string> copyExternalPath(const std::string& sourcePath, const std::string& destinationPath);
    bool externalPathWithinRoot(const std::string& path, const std::string& root);
    doof::Result<std::string, std::string> commandOutput(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::shared_ptr<::std_::os::index::ExecOptions>& options = std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, std::nullopt, nullptr));
    std::string externalCommandFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand>& command);
    std::string externalSourceFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency);
    std::string externalNativeFingerprint(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::shared_ptr<ExternalDependencyTarget>& target);
    bool markerMatches(const std::string& path, const std::string& fingerprint);
    bool markerContentMatches(const std::string& path, const std::string& expected);
    void externalJsonSet(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& key, const doof::JsonValue& value);
    std::shared_ptr<std::vector<doof::JsonValue>> externalCommandsJson(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependencyCommand>>>& commands);
    std::string externalSourceMarkerContent(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& fingerprint);
    std::string externalNativeMarkerContent(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::shared_ptr<ExternalDependencyTarget>& target, const std::string& fingerprint);
    bool isEmptyExternalDirectory(const std::string& path);
    doof::Result<void, std::string> copyArchiveContents(const std::string& sourceRoot, const std::string& destination);
    doof::Result<std::string, std::string> strippedArchiveRoot(const std::string& extractRoot, int32_t count, const std::string& dependencyName);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> downloadExternalArchive(const std::string& url);
    doof::Result<void, std::string> acquireArchive(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& destination, const std::string& stagingRoot);
    doof::Result<void, std::string> acquireGit(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& destination, const std::string& stagingRoot);
    std::string applyExternalDependencySubstitutions(const std::string& value, const std::string& packageRoot, const std::string& destination, const std::shared_ptr<ExternalDependencyTarget>& target);
    doof::Result<void, std::string> runExternalCommands(const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::string& packageRoot, const std::string& destination, const std::shared_ptr<ExternalDependencyTarget>& target);
    doof::Result<void, std::string> acquirePackageExternalDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::shared_ptr<ExternalDependencyTarget>& target);
}

namespace app_src_external_dependency_ {
}
