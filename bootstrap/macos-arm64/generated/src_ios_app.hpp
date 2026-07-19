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
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_ios_app_ {
    struct IOSAppResource;
    struct IOSEmbeddedLibrary;
    struct IOSAppConfig;
    struct IOSPackageConfig;
}

namespace app_src_ios_app_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct IOSAppResource : public std::enable_shared_from_this<IOSAppResource> {
    std::string sourcePath;
    std::string destination;
    IOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSAppResource>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct IOSEmbeddedLibrary : public std::enable_shared_from_this<IOSEmbeddedLibrary> {
    std::string library = std::string("");
    std::string path = std::string("");
    IOSEmbeddedLibrary(std::string library = std::string(""), std::string path = std::string("")) : library(library), path(path) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSEmbeddedLibrary>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct IOSAppConfig : public std::enable_shared_from_this<IOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath = std::string("");
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr;
    std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<IOSAppResource>>>(std::vector<std::shared_ptr<IOSAppResource>>{});
    std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<IOSEmbeddedLibrary>>{});
    std::string minimumDeploymentTarget = std::string("16.0");
    IOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath = std::string(""), std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr, std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<IOSAppResource>>>(std::vector<std::shared_ptr<IOSAppResource>>{}), std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<IOSEmbeddedLibrary>>{}), std::string minimumDeploymentTarget = std::string("16.0")) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), minimumDeploymentTarget(minimumDeploymentTarget) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSAppConfig>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct IOSPackageConfig : public std::enable_shared_from_this<IOSPackageConfig> {
    std::string identity = std::string("");
    std::string provisioningProfilePath = std::string("");
    IOSPackageConfig(std::string identity = std::string(""), std::string provisioningProfilePath = std::string("")) : identity(identity), provisioningProfilePath(provisioningProfilePath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSPackageConfig>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string iosPackageArchiveName(std::string executableName, std::string version);
    doof::Result<std::string, std::string> iosExactApplicationIdentifier(std::string profileApplicationIdentifier, std::string bundleId);
    doof::Result<std::string, std::string> iosTargetTriple(std::string minimumDeploymentTarget, std::string destination, std::string architecture);
    std::shared_ptr<std::vector<std::string>> iosCodesignArguments(std::string targetPath, std::string identity, std::string entitlementsPath = std::string(""));
    std::string renderIOSInfoPlist(std::shared_ptr<IOSAppConfig> config);
    std::string renderIOSMainSource(std::string executableName);
    std::string renderIOSIconSetContents();
    std::string objectiveCIdentifier(std::string value);
    std::string escapeObjectiveCString(std::string value);
    std::string plistString(std::string key, std::string value);
    std::string plistIndent(int32_t depth);
    std::string renderPlistValue(doof::JsonValue value, int32_t depth);
    std::string escapePlistText(std::string value);
}

namespace app_src_ios_app_ {
}
