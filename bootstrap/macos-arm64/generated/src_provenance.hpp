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

namespace app_src_std_catalog_ {
    struct StdCatalogPackage;
    struct StdCatalog;
}

namespace app_src_dependency_policy_ {
    struct ReachedPackageInput;
    struct ResolvedExternalInput;
}

namespace app_src_macos_app_ {
    struct MacOSAppResource : public std::enable_shared_from_this<MacOSAppResource> {
    std::string sourcePath;
    std::string destination;
    MacOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct MacOSEmbeddedLibrary : public std::enable_shared_from_this<MacOSEmbeddedLibrary> {
    std::string library = std::string("");
    std::string path = std::string("");
    MacOSEmbeddedLibrary(std::string library = std::string(""), std::string path = std::string("")) : library(library), path(path) {}
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
};
    struct MacOSPackageConfig : public std::enable_shared_from_this<MacOSPackageConfig> {
    std::string distDirectory = std::string("");
    std::string signing = std::string("developer-id");
    std::string identity = std::string("");
    bool sandbox = false;
    std::string entitlementsPath = std::string("");
    MacOSPackageConfig(std::string distDirectory = std::string(""), std::string signing = std::string("developer-id"), std::string identity = std::string(""), bool sandbox = false, std::string entitlementsPath = std::string("")) : distDirectory(distDirectory), signing(signing), identity(identity), sandbox(sandbox), entitlementsPath(entitlementsPath) {}
};
}

namespace app_src_ios_app_ {
    struct IOSAppResource : public std::enable_shared_from_this<IOSAppResource> {
    std::string sourcePath;
    std::string destination;
    IOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct IOSEmbeddedLibrary : public std::enable_shared_from_this<IOSEmbeddedLibrary> {
    std::string library = std::string("");
    std::string path = std::string("");
    IOSEmbeddedLibrary(std::string library = std::string(""), std::string path = std::string("")) : library(library), path(path) {}
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
};
    struct IOSPackageConfig : public std::enable_shared_from_this<IOSPackageConfig> {
    std::string identity = std::string("");
    std::string provisioningProfilePath = std::string("");
    IOSPackageConfig(std::string identity = std::string(""), std::string provisioningProfilePath = std::string("")) : identity(identity), provisioningProfilePath(provisioningProfilePath) {}
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
};
    struct PackageResource : public std::enable_shared_from_this<PackageResource> {
    std::string sourcePath;
    std::string destination;
    PackageResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct ExternalDependencyCopyFile : public std::enable_shared_from_this<ExternalDependencyCopyFile> {
    std::string source;
    std::string destination;
    ExternalDependencyCopyFile(std::string source, std::string destination) : source(source), destination(destination) {}
};
    struct ExternalDependencyCommand : public std::enable_shared_from_this<ExternalDependencyCommand> {
    std::string program;
    std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    std::string workingDirectory = std::string("");
    ExternalDependencyCommand(std::string program, std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), std::string workingDirectory = std::string("")) : program(program), args(args), env(env), workingDirectory(workingDirectory) {}
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
};
    struct PackageDependency : public std::enable_shared_from_this<PackageDependency> {
    std::string name;
    std::string path = std::string("");
    std::string url = std::string("");
    std::string ref = std::string("");
    std::string commit = std::string("");
    PackageDependency(std::string name, std::string path = std::string(""), std::string url = std::string(""), std::string ref = std::string(""), std::string commit = std::string("")) : name(name), path(path), url(url), ref(ref), commit(commit) {}
};
    struct DependencyResolution : public std::enable_shared_from_this<DependencyResolution> {
    std::string name;
    std::string kind = std::string("git");
    std::string url;
    std::string ref = std::string("");
    std::string commit = std::string("");
    std::string sha256 = std::string("");
    DependencyResolution(std::string name, std::string kind, std::string url, std::string ref = std::string(""), std::string commit = std::string(""), std::string sha256 = std::string("")) : name(name), kind(kind), url(url), ref(ref), commit(commit), sha256(sha256) {}
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
};
}

namespace app_src_std_catalog_ {
    struct StdCatalogPackage : public std::enable_shared_from_this<StdCatalogPackage> {
    std::string name;
    std::string url;
    std::string ref;
    std::string version;
    std::string commit;
    StdCatalogPackage(std::string name, std::string url, std::string ref, std::string version, std::string commit) : name(name), url(url), ref(ref), version(version), commit(commit) {}
};
    struct StdCatalog : public std::enable_shared_from_this<StdCatalog> {
    int32_t schemaVersion;
    std::string compilerVersion;
    std::string digest;
    std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> packages;
    StdCatalog(int32_t schemaVersion, std::string compilerVersion, std::string digest, std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> packages) : schemaVersion(schemaVersion), compilerVersion(compilerVersion), digest(digest), packages(packages) {}
};
}

namespace app_src_dependency_policy_ {
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
};
}

#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text);
    std::string formatJsonValue(const doof::JsonValue& value);
}

namespace app_src_std_catalog_ {
    std::string canonicalDependencyUrl(const std::string& value);
}

namespace app_src_provenance_ {
    std::string renderBuildProvenance(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>& packages, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& externals, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& nativeBuild, const std::shared_ptr<::app_src_std_catalog_::StdCatalog>& catalog);
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenancePackage(const std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>& package);
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenanceExternal(const std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>& input);
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenanceNative(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& nativeBuild);
    std::shared_ptr<std::vector<doof::JsonValue>> provenanceStrings(const std::shared_ptr<std::vector<std::string>>& values);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> sortedProvenancePackages(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>& values);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> sortedProvenanceExternals(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& values);
    void provenanceSet(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const doof::JsonValue& value);
}
