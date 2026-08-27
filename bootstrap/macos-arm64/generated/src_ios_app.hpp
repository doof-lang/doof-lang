#pragma once
#include "doof_runtime.hpp"
namespace app_src_ios_app_ {
    struct IOSAppResource;
    struct IOSEmbeddedLibrary;
    struct IOSAppConfig;
    struct IOSPackageConfig;
}

namespace app_src_ios_app_ {
    struct IOSAppResource : public std::enable_shared_from_this<IOSAppResource> {
    std::string sourcePath;
    std::string destination;
    IOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct IOSEmbeddedLibrary : public std::enable_shared_from_this<IOSEmbeddedLibrary> {
    std::string library;
    std::string path;
    IOSEmbeddedLibrary(std::string library, std::string path) : library(library), path(path) {}
};
    struct IOSAppConfig : public std::enable_shared_from_this<IOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath;
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist;
    std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>> embeddedLibraries;
    std::string minimumDeploymentTarget;
    IOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist, std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>> embeddedLibraries, std::string minimumDeploymentTarget) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), minimumDeploymentTarget(minimumDeploymentTarget) {}
};
    struct IOSPackageConfig : public std::enable_shared_from_this<IOSPackageConfig> {
    std::string identity;
    std::string provisioningProfilePath;
    IOSPackageConfig(std::string identity, std::string provisioningProfilePath) : identity(identity), provisioningProfilePath(provisioningProfilePath) {}
};
}

namespace app_src_ios_app_ {
    std::string iosPackageArchiveName(const std::string& executableName, const std::string& version);
    doof::Result<std::string, std::string> iosExactApplicationIdentifier(const std::string& profileApplicationIdentifier, const std::string& bundleId);
    doof::Result<std::string, std::string> iosTargetTriple(const std::string& minimumDeploymentTarget, const std::string& destination, const std::string& architecture);
    std::shared_ptr<std::vector<std::string>> iosCodesignArguments(const std::string& targetPath, const std::string& identity, const std::string& entitlementsPath);
    std::string renderIOSInfoPlist(const std::shared_ptr<IOSAppConfig>& config);
    std::string renderIOSMainSource(const std::string& executableName);
    std::string renderIOSIconSetContents();
    std::string objectiveCIdentifier(const std::string& value);
    std::string escapeObjectiveCString(const std::string& value);
    std::string plistString(const std::string& key, const std::string& value);
    std::string plistIndent(int32_t depth);
    std::string renderPlistValue(const doof::JsonValue& value, int32_t depth);
    std::string escapePlistText(const std::string& value);
}
