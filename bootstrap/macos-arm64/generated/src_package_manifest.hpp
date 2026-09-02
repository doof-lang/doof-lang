#pragma once
#include "doof_runtime.hpp"
namespace std_::json::index {
}

namespace app_src_macos_app_ {
    struct MacOSAppResource;
    struct MacOSEmbeddedLibrary;
    struct MacOSAppConfig;
    struct MacOSPackageConfig;
}

namespace app_src_ios_app_ {
    struct IOSAppResource;
    struct IOSEmbeddedLibrary;
    struct IOSAppConfig;
    struct IOSPackageConfig;
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan;
    struct PackageResource;
    struct StdlibPreparationCommand;
    struct PackageDependency;
    struct PackageManifest;
}

namespace app_src_macos_app_ {
    struct MacOSAppResource : public std::enable_shared_from_this<MacOSAppResource> {
    std::string sourcePath;
    std::string destination;
    MacOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct MacOSEmbeddedLibrary : public std::enable_shared_from_this<MacOSEmbeddedLibrary> {
    std::string library;
    std::string path;
    MacOSEmbeddedLibrary(std::string library, std::string path) : library(library), path(path) {}
};
    struct MacOSAppConfig : public std::enable_shared_from_this<MacOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath;
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist;
    std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries;
    std::string category;
    std::string minimumSystemVersion;
    MacOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist, std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries, std::string category, std::string minimumSystemVersion) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), category(category), minimumSystemVersion(minimumSystemVersion) {}
};
    struct MacOSPackageConfig : public std::enable_shared_from_this<MacOSPackageConfig> {
    std::string distDirectory;
    std::string signing;
    std::string identity;
    bool sandbox;
    std::string entitlementsPath;
    MacOSPackageConfig(std::string distDirectory, std::string signing, std::string identity, bool sandbox, std::string entitlementsPath) : distDirectory(distDirectory), signing(signing), identity(identity), sandbox(sandbox), entitlementsPath(entitlementsPath) {}
};
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
    struct PackageResource : public std::enable_shared_from_this<PackageResource> {
    std::string sourcePath;
    std::string destination;
    PackageResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct StdlibPreparationCommand : public std::enable_shared_from_this<StdlibPreparationCommand> {
    std::string program;
    std::shared_ptr<std::vector<std::string>> args;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env;
    std::string workingDirectory;
    StdlibPreparationCommand(std::string program, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<doof::ordered_map<std::string, std::string>> env, std::string workingDirectory) : program(program), args(args), env(env), workingDirectory(workingDirectory) {}
};
    struct PackageDependency : public std::enable_shared_from_this<PackageDependency> {
    std::string name;
    std::string path;
    PackageDependency(std::string name, std::string path) : name(name), path(path) {}
};
    struct PackageManifest : public std::enable_shared_from_this<PackageManifest> {
    std::string name;
    std::string version;
    std::string manifestPath;
    std::string rootDirectory;
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies;
    std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>> stdlibPreparation;
    std::shared_ptr<NativeBuildPlan> nativeBuild;
    std::string target;
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig;
    PackageManifest(std::string name, std::string version, std::string manifestPath, std::string rootDirectory, std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies, std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>> stdlibPreparation, std::shared_ptr<NativeBuildPlan> nativeBuild, std::string target, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig) : name(name), version(version), manifestPath(manifestPath), rootDirectory(rootDirectory), resources(resources), dependencies(dependencies), stdlibPreparation(stdlibPreparation), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
};
}

#include "std/json/native_json.hpp"

namespace std_::path::index {
    std::string join(const std::shared_ptr<std::vector<std::string>>& parts);
}

namespace app_src_package_manifest_ {
    std::string manifestJoinPath(const std::string& directory, const std::string& name);
    doof::JsonValue manifestJsonField(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name);
    bool manifestJsonHas(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name);
    doof::Result<std::shared_ptr<PackageManifest>, std::string> parsePackageManifest(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& targetOverride);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>, std::string> parsePackageDependencies(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>>, std::string> parseStdlibPreparation(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath);
    doof::Result<std::string, std::string> requiredManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>>, std::string> parsePreparationCommands(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> parseManifestNativeBuild(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& target);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseManifestResources(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory);
    doof::Result<std::string, std::string> parseManifestTarget(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath);
    doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>, std::string> parseMacOSApp(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& packageName, const std::string& packageVersion, const std::string& target);
    doof::Result<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>, std::string> parseIOSApp(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& packageName, const std::string& packageVersion, const std::string& target);
    doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>, std::string> parseMacOSPackage(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory);
    doof::Result<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>, std::string> parseIOSPackage(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory);
    doof::Result<std::string, std::string> optionalManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& key, const std::string& fallback, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<std::string, std::string> firstManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& first, const std::string& firstKey, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& second, const std::string& secondKey, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& third, const std::string& thirdKey, const std::string& fallback, const std::string& manifestPath, const std::string& fieldPath);
    std::string sanitizeBundleName(const std::string& value);
    bool manifestPathWithinRoot(const std::string& path, const std::string& rootDirectory);
    bool isManagedMacOSPlistKey(const std::string& key);
    bool isManagedIOSPlistKey(const std::string& key);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseResourceArray(const doof::JsonValue& value, const std::string& manifestPath, const std::string& rootDirectory, const std::string& fieldPath);
    doof::Result<std::string, std::string> normalizeResourceDestination(const std::string& destination, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<void, std::string> appendNativeFragment(const std::shared_ptr<NativeBuildPlan>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& fragment, const std::string& manifestPath, const std::string& rootDirectory, const std::string& fieldPath);
    doof::Result<void, std::string> appendStringArrayField(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath, const std::string& pathRoot);
    void appendNativeBuild(const std::shared_ptr<NativeBuildPlan>& target, const std::shared_ptr<NativeBuildPlan>& source);
    void appendUniqueValues(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<std::vector<std::string>>& values);
    void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value);
    doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> manifestObject(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<std::shared_ptr<std::vector<doof::JsonValue>>, std::string> manifestArray(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<std::string, std::string> manifestString(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath);
}
