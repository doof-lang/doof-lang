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
    struct ExternalDependencyCopyFile : public std::enable_shared_from_this<ExternalDependencyCopyFile> {
    std::string source;
    std::string destination;
    ExternalDependencyCopyFile(std::string source, std::string destination) : source(source), destination(destination) {}
};
    struct ExternalDependencyCommand : public std::enable_shared_from_this<ExternalDependencyCommand> {
    std::string program;
    std::shared_ptr<std::vector<std::string>> args;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env;
    std::string workingDirectory;
    ExternalDependencyCommand(std::string program, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<doof::ordered_map<std::string, std::string>> env, std::string workingDirectory) : program(program), args(args), env(env), workingDirectory(workingDirectory) {}
};
    struct ExternalDependency : public std::enable_shared_from_this<ExternalDependency> {
    std::string name;
    std::string kind;
    std::string url;
    std::string destination;
    std::string sha256;
    int32_t stripComponents;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> copyFiles;
    std::string ref;
    std::string commit;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> commands;
    ExternalDependency(std::string name, std::string kind, std::string url, std::string destination, std::string sha256, int32_t stripComponents, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> copyFiles, std::string ref, std::string commit, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> commands) : name(name), kind(kind), url(url), destination(destination), sha256(sha256), stripComponents(stripComponents), copyFiles(copyFiles), ref(ref), commit(commit), commands(commands) {}
};
    struct PackageDependency : public std::enable_shared_from_this<PackageDependency> {
    std::string name;
    std::string path;
    std::string url;
    std::string ref;
    std::string commit;
    PackageDependency(std::string name, std::string path, std::string url, std::string ref, std::string commit) : name(name), path(path), url(url), ref(ref), commit(commit) {}
};
    struct DependencyResolution : public std::enable_shared_from_this<DependencyResolution> {
    std::string name;
    std::string kind;
    std::string url;
    std::string ref;
    std::string commit;
    std::string sha256;
    DependencyResolution(std::string name, std::string kind, std::string url, std::string ref, std::string commit, std::string sha256) : name(name), kind(kind), url(url), ref(ref), commit(commit), sha256(sha256) {}
};
    struct DependencyPolicy : public std::enable_shared_from_this<DependencyPolicy> {
    bool hasPackageSourceAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedPackageSources;
    bool hasExternalSourceAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedExternalSources;
    bool hasLinkLibraryAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedLinkLibraries;
    bool hasFrameworkAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedFrameworks;
    bool hasPkgConfigAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedPkgConfigPackages;
    DependencyPolicy(bool hasPackageSourceAllowlist, std::shared_ptr<std::vector<std::string>> allowedPackageSources, bool hasExternalSourceAllowlist, std::shared_ptr<std::vector<std::string>> allowedExternalSources, bool hasLinkLibraryAllowlist, std::shared_ptr<std::vector<std::string>> allowedLinkLibraries, bool hasFrameworkAllowlist, std::shared_ptr<std::vector<std::string>> allowedFrameworks, bool hasPkgConfigAllowlist, std::shared_ptr<std::vector<std::string>> allowedPkgConfigPackages) : hasPackageSourceAllowlist(hasPackageSourceAllowlist), allowedPackageSources(allowedPackageSources), hasExternalSourceAllowlist(hasExternalSourceAllowlist), allowedExternalSources(allowedExternalSources), hasLinkLibraryAllowlist(hasLinkLibraryAllowlist), allowedLinkLibraries(allowedLinkLibraries), hasFrameworkAllowlist(hasFrameworkAllowlist), allowedFrameworks(allowedFrameworks), hasPkgConfigAllowlist(hasPkgConfigAllowlist), allowedPkgConfigPackages(allowedPkgConfigPackages) {}
};
    struct PackageManifest : public std::enable_shared_from_this<PackageManifest> {
    std::string name;
    std::string version;
    std::string manifestPath;
    std::string rootDirectory;
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> externalDependencies;
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> packageResolutions;
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> externalResolutions;
    std::shared_ptr<DependencyPolicy> policy;
    std::shared_ptr<NativeBuildPlan> nativeBuild;
    std::string target;
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig;
    PackageManifest(std::string name, std::string version, std::string manifestPath, std::string rootDirectory, std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> externalDependencies, std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> packageResolutions, std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> externalResolutions, std::shared_ptr<DependencyPolicy> policy, std::shared_ptr<NativeBuildPlan> nativeBuild, std::string target, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig) : name(name), version(version), manifestPath(manifestPath), rootDirectory(rootDirectory), resources(resources), dependencies(dependencies), externalDependencies(externalDependencies), packageResolutions(packageResolutions), externalResolutions(externalResolutions), policy(policy), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
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
    std::string sourceUrl;
    std::string sourceRef;
    std::string sourceCommit;
    std::string requestedUrl;
    std::string requestedRef;
    std::string requestedCommit;
    bool mutable_;
    ReachedPackageInput(std::string logicalPrefix, std::string introducedBy, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::string sourceKind, std::string sourceUrl, std::string sourceRef, std::string sourceCommit, std::string requestedUrl, std::string requestedRef, std::string requestedCommit, bool mutable_) : logicalPrefix(logicalPrefix), introducedBy(introducedBy), manifest(manifest), sourceKind(sourceKind), sourceUrl(sourceUrl), sourceRef(sourceRef), sourceCommit(sourceCommit), requestedUrl(requestedUrl), requestedRef(requestedRef), requestedCommit(requestedCommit), mutable_(mutable_) {}
};
    struct ResolvedExternalInput : public std::enable_shared_from_this<ResolvedExternalInput> {
    std::shared_ptr<ReachedPackageInput> owner;
    std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency;
    std::string selectedKind;
    std::string selectedUrl;
    std::string selectedRef;
    std::string selectedCommit;
    std::string selectedSha256;
    bool overridden;
    ResolvedExternalInput(std::shared_ptr<ReachedPackageInput> owner, std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string selectedKind, std::string selectedUrl, std::string selectedRef, std::string selectedCommit, std::string selectedSha256, bool overridden) : owner(owner), dependency(dependency), selectedKind(selectedKind), selectedUrl(selectedUrl), selectedRef(selectedRef), selectedCommit(selectedCommit), selectedSha256(selectedSha256), overridden(overridden) {}
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
