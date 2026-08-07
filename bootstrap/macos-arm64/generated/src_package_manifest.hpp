#pragma once
#include "doof_runtime.hpp"
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
    struct ExternalDependencyCopyFile;
    struct ExternalDependencyCommand;
    struct ExternalDependency;
    struct PackageDependency;
    struct DependencyResolution;
    struct DependencyPolicy;
    struct PackageManifest;
}

namespace app_src_macos_app_ {
    struct MacOSAppResource : public std::enable_shared_from_this<MacOSAppResource> {
    std::string sourcePath;
    std::string destination;
    MacOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSAppResource>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct MacOSEmbeddedLibrary : public std::enable_shared_from_this<MacOSEmbeddedLibrary> {
    std::string library = std::string("");
    std::string path = std::string("");
    MacOSEmbeddedLibrary(std::string library = std::string(""), std::string path = std::string("")) : library(library), path(path) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSEmbeddedLibrary>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct MacOSAppConfig : public std::enable_shared_from_this<MacOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath = std::string("");
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr;
    std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<MacOSAppResource>>>(std::vector<std::shared_ptr<MacOSAppResource>>{});
    std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>{});
    std::string category = std::string("public.app-category.developer-tools");
    std::string minimumSystemVersion = std::string("11.0");
    MacOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath = std::string(""), std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr, std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<MacOSAppResource>>>(std::vector<std::shared_ptr<MacOSAppResource>>{}), std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>{}), std::string category = std::string("public.app-category.developer-tools"), std::string minimumSystemVersion = std::string("11.0")) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), category(category), minimumSystemVersion(minimumSystemVersion) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSAppConfig>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct MacOSPackageConfig : public std::enable_shared_from_this<MacOSPackageConfig> {
    std::string distDirectory = std::string("");
    std::string signing = std::string("developer-id");
    std::string identity = std::string("");
    bool sandbox = false;
    std::string entitlementsPath = std::string("");
    MacOSPackageConfig(std::string distDirectory = std::string(""), std::string signing = std::string("developer-id"), std::string identity = std::string(""), bool sandbox = false, std::string entitlementsPath = std::string("")) : distDirectory(distDirectory), signing(signing), identity(identity), sandbox(sandbox), entitlementsPath(entitlementsPath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSPackageConfig>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_ios_app_ {
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
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan : public std::enable_shared_from_this<NativeBuildPlan> {
    std::shared_ptr<std::vector<std::string>> includePaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> sourceFiles = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> libraryPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> extraCopyPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> linkLibraries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> frameworks = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> pkgConfigPackages = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> defines = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> compilerFlags = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> linkerFlags = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    NativeBuildPlan(std::shared_ptr<std::vector<std::string>> includePaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> sourceFiles = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> libraryPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> extraCopyPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> linkLibraries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> frameworks = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> pkgConfigPackages = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> defines = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> compilerFlags = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> linkerFlags = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : includePaths(includePaths), sourceFiles(sourceFiles), libraryPaths(libraryPaths), extraCopyPaths(extraCopyPaths), linkLibraries(linkLibraries), frameworks(frameworks), pkgConfigPackages(pkgConfigPackages), defines(defines), compilerFlags(compilerFlags), linkerFlags(linkerFlags) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct PackageResource : public std::enable_shared_from_this<PackageResource> {
    std::string sourcePath;
    std::string destination;
    PackageResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<PackageResource>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ExternalDependencyCopyFile : public std::enable_shared_from_this<ExternalDependencyCopyFile> {
    std::string source;
    std::string destination;
    ExternalDependencyCopyFile(std::string source, std::string destination) : source(source), destination(destination) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExternalDependencyCopyFile>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ExternalDependencyCommand : public std::enable_shared_from_this<ExternalDependencyCommand> {
    std::string program;
    std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    std::string workingDirectory = std::string("");
    ExternalDependencyCommand(std::string program, std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), std::string workingDirectory = std::string("")) : program(program), args(args), env(env), workingDirectory(workingDirectory) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExternalDependencyCommand>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ExternalDependency : public std::enable_shared_from_this<ExternalDependency> {
    std::string name;
    std::string kind;
    std::string url;
    std::string destination;
    std::string sha256 = std::string("");
    int32_t stripComponents = 1;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> copyFiles = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{});
    std::string ref = std::string("");
    std::string commit = std::string("");
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> commands = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{});
    ExternalDependency(std::string name, std::string kind, std::string url, std::string destination, std::string sha256 = std::string(""), int32_t stripComponents = 1, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> copyFiles = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{}), std::string ref = std::string(""), std::string commit = std::string(""), std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> commands = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{})) : name(name), kind(kind), url(url), destination(destination), sha256(sha256), stripComponents(stripComponents), copyFiles(copyFiles), ref(ref), commit(commit), commands(commands) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExternalDependency>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct PackageDependency : public std::enable_shared_from_this<PackageDependency> {
    std::string name;
    std::string path = std::string("");
    std::string url = std::string("");
    std::string ref = std::string("");
    std::string commit = std::string("");
    PackageDependency(std::string name, std::string path = std::string(""), std::string url = std::string(""), std::string ref = std::string(""), std::string commit = std::string("")) : name(name), path(path), url(url), ref(ref), commit(commit) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<PackageDependency>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct DependencyResolution : public std::enable_shared_from_this<DependencyResolution> {
    std::string name;
    std::string kind = std::string("git");
    std::string url;
    std::string ref = std::string("");
    std::string commit = std::string("");
    std::string sha256 = std::string("");
    DependencyResolution(std::string name, std::string kind, std::string url, std::string ref = std::string(""), std::string commit = std::string(""), std::string sha256 = std::string("")) : name(name), kind(kind), url(url), ref(ref), commit(commit), sha256(sha256) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DependencyResolution>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct DependencyPolicy : public std::enable_shared_from_this<DependencyPolicy> {
    bool hasPackageSourceAllowlist = false;
    std::shared_ptr<std::vector<std::string>> allowedPackageSources = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    bool hasExternalSourceAllowlist = false;
    std::shared_ptr<std::vector<std::string>> allowedExternalSources = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    bool hasLinkLibraryAllowlist = false;
    std::shared_ptr<std::vector<std::string>> allowedLinkLibraries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    bool hasFrameworkAllowlist = false;
    std::shared_ptr<std::vector<std::string>> allowedFrameworks = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    bool hasPkgConfigAllowlist = false;
    std::shared_ptr<std::vector<std::string>> allowedPkgConfigPackages = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    DependencyPolicy(bool hasPackageSourceAllowlist = false, std::shared_ptr<std::vector<std::string>> allowedPackageSources = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), bool hasExternalSourceAllowlist = false, std::shared_ptr<std::vector<std::string>> allowedExternalSources = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), bool hasLinkLibraryAllowlist = false, std::shared_ptr<std::vector<std::string>> allowedLinkLibraries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), bool hasFrameworkAllowlist = false, std::shared_ptr<std::vector<std::string>> allowedFrameworks = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), bool hasPkgConfigAllowlist = false, std::shared_ptr<std::vector<std::string>> allowedPkgConfigPackages = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : hasPackageSourceAllowlist(hasPackageSourceAllowlist), allowedPackageSources(allowedPackageSources), hasExternalSourceAllowlist(hasExternalSourceAllowlist), allowedExternalSources(allowedExternalSources), hasLinkLibraryAllowlist(hasLinkLibraryAllowlist), allowedLinkLibraries(allowedLinkLibraries), hasFrameworkAllowlist(hasFrameworkAllowlist), allowedFrameworks(allowedFrameworks), hasPkgConfigAllowlist(hasPkgConfigAllowlist), allowedPkgConfigPackages(allowedPkgConfigPackages) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DependencyPolicy>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct PackageManifest : public std::enable_shared_from_this<PackageManifest> {
    std::string name;
    std::string version = std::string("1.0");
    std::string manifestPath;
    std::string rootDirectory;
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources = std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{});
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies = std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{});
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> externalDependencies = std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(std::vector<std::shared_ptr<ExternalDependency>>{});
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> packageResolutions = std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{});
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> externalResolutions = std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{});
    std::shared_ptr<DependencyPolicy> policy = std::make_shared<DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    std::shared_ptr<NativeBuildPlan> nativeBuild;
    std::string target = std::string("");
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp = nullptr;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp = nullptr;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig = nullptr;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig = nullptr;
    PackageManifest(std::string name, std::string version, std::string manifestPath, std::string rootDirectory, std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> externalDependencies, std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> packageResolutions, std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> externalResolutions, std::shared_ptr<DependencyPolicy> policy, std::shared_ptr<NativeBuildPlan> nativeBuild, std::string target = std::string(""), std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp = nullptr, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp = nullptr, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig = nullptr, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig = nullptr) : name(name), version(version), manifestPath(manifestPath), rootDirectory(rootDirectory), resources(resources), dependencies(dependencies), externalDependencies(externalDependencies), packageResolutions(packageResolutions), externalResolutions(externalResolutions), policy(policy), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<PackageManifest>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text);
    std::string formatJsonValue(const doof::JsonValue& value);
}

namespace std_::path::index {
    std::string join(const std::shared_ptr<std::vector<std::string>>& parts);
}

namespace app_src_package_manifest_ {
    std::string manifestJoinPath(const std::string& directory, const std::string& name);
    doof::JsonValue manifestJsonField(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name);
    bool manifestJsonHas(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name);
    doof::Result<std::shared_ptr<PackageManifest>, std::string> parsePackageManifest(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& targetOverride = std::string(""));
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>, std::string> parsePackageDependencies(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>, std::string> parseResolutions(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& section);
    doof::Result<std::shared_ptr<DependencyPolicy>, std::string> parseDependencyPolicy(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath);
    doof::Result<void, std::string> appendPolicyStrings(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>, std::string> parseExternalDependencies(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory);
    doof::Result<std::string, std::string> requiredManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>, std::string> parseExternalDependencyCopyFiles(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& manifestPath, const std::string& fieldPath);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>, std::string> parseExternalDependencyCommands(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& manifestPath, const std::string& fieldPath);
    bool isSupportedExternalArchiveUrl(const std::string& url);
    bool isHexString(const std::string& value, int32_t length);
    std::shared_ptr<NativeBuildPlan> mergeNativeBuildPlans(const std::shared_ptr<std::vector<std::shared_ptr<NativeBuildPlan>>>& plans);
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
