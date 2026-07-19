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
namespace app_src_package_manifest_ { struct DependencyPolicy; }
namespace app_src_package_manifest_ { struct DependencyResolution; }
namespace app_src_package_manifest_ { struct ExternalDependency; }
namespace app_src_package_manifest_ { struct PackageDependency; }
namespace app_src_package_manifest_ { struct PackageManifest; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_dependency_policy_ {
    struct ReachedPackageInput;
    struct ResolvedExternalInput;
}

#include "src_package_manifest.hpp"
#include "src_std_catalog.hpp"

namespace app_src_dependency_policy_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ReachedPackageInput : public std::enable_shared_from_this<ReachedPackageInput> {
    std::string logicalPrefix;
    std::string introducedBy;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    std::string sourceKind;
    std::string sourceUrl = std::string("");
    std::string sourceRef = std::string("");
    std::string sourceCommit = std::string("");
    std::string requestedUrl = std::string("");
    std::string requestedRef = std::string("");
    std::string requestedCommit = std::string("");
    bool mutable_ = false;
    ReachedPackageInput(std::string logicalPrefix, std::string introducedBy, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::string sourceKind, std::string sourceUrl = std::string(""), std::string sourceRef = std::string(""), std::string sourceCommit = std::string(""), std::string requestedUrl = std::string(""), std::string requestedRef = std::string(""), std::string requestedCommit = std::string(""), bool mutable_ = false) : logicalPrefix(logicalPrefix), introducedBy(introducedBy), manifest(manifest), sourceKind(sourceKind), sourceUrl(sourceUrl), sourceRef(sourceRef), sourceCommit(sourceCommit), requestedUrl(requestedUrl), requestedRef(requestedRef), requestedCommit(requestedCommit), mutable_(mutable_) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ReachedPackageInput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ResolvedExternalInput : public std::enable_shared_from_this<ResolvedExternalInput> {
    std::shared_ptr<ReachedPackageInput> owner;
    std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency;
    std::string selectedKind;
    std::string selectedUrl;
    std::string selectedRef = std::string("");
    std::string selectedCommit = std::string("");
    std::string selectedSha256 = std::string("");
    bool overridden = false;
    ResolvedExternalInput(std::shared_ptr<ReachedPackageInput> owner, std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string selectedKind, std::string selectedUrl, std::string selectedRef = std::string(""), std::string selectedCommit = std::string(""), std::string selectedSha256 = std::string(""), bool overridden = false) : owner(owner), dependency(dependency), selectedKind(selectedKind), selectedUrl(selectedUrl), selectedRef(selectedRef), selectedCommit(selectedCommit), selectedSha256(selectedSha256), overridden(overridden) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ResolvedExternalInput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    bool hasMutableStdPackageInputs(std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>> packages);
    std::shared_ptr<::app_src_package_manifest_::DependencyResolution> resolutionForUrl(std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>> resolutions, std::string url);
    std::shared_ptr<::app_src_package_manifest_::PackageDependency> selectedPackageSource(std::shared_ptr<::app_src_package_manifest_::PackageDependency> dependency, std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>> resolutions);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>, std::string> resolveExternalInputs(std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>> packages, std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest);
    doof::Result<void, std::string> validateDependencyPolicy(std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>> packages, std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>> externals, std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest);
    std::shared_ptr<ResolvedExternalInput> resolvedExternalInput(std::shared_ptr<ReachedPackageInput> owner, std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::shared_ptr<::app_src_package_manifest_::DependencyResolution> resolution);
    bool sameSelectedExternal(std::shared_ptr<ResolvedExternalInput> left, std::shared_ptr<ResolvedExternalInput> right);
    bool containsCanonicalUrl(std::shared_ptr<std::vector<std::string>> values, std::string value);
    doof::Result<void, std::string> validateTransitiveNativePolicy(std::shared_ptr<ReachedPackageInput> package, std::shared_ptr<::app_src_package_manifest_::DependencyPolicy> policy);
}

namespace app_src_dependency_policy_ {
}
