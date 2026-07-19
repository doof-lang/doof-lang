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
namespace app_src_macos_app_ { struct MacOSAppConfig; }
namespace app_src_macos_app_ { struct MacOSAppResource; }
namespace app_src_macos_app_ { struct MacOSEmbeddedLibrary; }
namespace app_src_macos_app_ { struct MacOSPackageConfig; }
namespace app_src_ios_app_ { struct IOSAppConfig; }
namespace app_src_ios_app_ { struct IOSAppResource; }
namespace app_src_ios_app_ { struct IOSEmbeddedLibrary; }
namespace app_src_ios_app_ { struct IOSPackageConfig; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

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

#include "std_json_index.hpp"
#include "std_path_index.hpp"
#include "src_macos_app.hpp"
#include "src_ios_app.hpp"

namespace app_src_package_manifest_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
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
    std::string manifestJoinPath(std::string directory, std::string name);
    doof::JsonValue manifestJsonField(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name);
    bool manifestJsonHas(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name);
    doof::Result<std::shared_ptr<PackageManifest>, std::string> parsePackageManifest(std::string source, std::string manifestPath, std::string rootDirectory, std::string platform, std::string targetOverride = std::string(""));
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>, std::string> parsePackageDependencies(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>, std::string> parseResolutions(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string section);
    doof::Result<std::shared_ptr<DependencyPolicy>, std::string> parseDependencyPolicy(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath);
    doof::Result<void, std::string> appendPolicyStrings(std::shared_ptr<std::vector<std::string>> target, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name, std::string manifestPath, std::string fieldPath);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>, std::string> parseExternalDependencies(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory);
    doof::Result<std::string, std::string> requiredManifestString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name, std::string manifestPath, std::string fieldPath);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>, std::string> parseExternalDependencyCopyFiles(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string manifestPath, std::string fieldPath);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>, std::string> parseExternalDependencyCommands(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string manifestPath, std::string fieldPath);
    bool isSupportedExternalArchiveUrl(std::string url);
    bool isHexString(std::string value, int32_t length);
    std::shared_ptr<NativeBuildPlan> mergeNativeBuildPlans(std::shared_ptr<std::vector<std::shared_ptr<NativeBuildPlan>>> plans);
    doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> parseManifestNativeBuild(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory, std::string platform, std::string target);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseManifestResources(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory);
    doof::Result<std::string, std::string> parseManifestTarget(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath);
    doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>, std::string> parseMacOSApp(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory, std::string packageName, std::string packageVersion, std::string target);
    doof::Result<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>, std::string> parseIOSApp(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory, std::string packageName, std::string packageVersion, std::string target);
    doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>, std::string> parseMacOSPackage(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory);
    doof::Result<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>, std::string> parseIOSPackage(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory);
    doof::Result<std::string, std::string> optionalManifestString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string key, std::string fallback, std::string manifestPath, std::string fieldPath);
    doof::Result<std::string, std::string> firstManifestString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> first, std::string firstKey, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> second, std::string secondKey, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> third, std::string thirdKey, std::string fallback, std::string manifestPath, std::string fieldPath);
    std::string sanitizeBundleName(std::string value);
    bool manifestPathWithinRoot(std::string path, std::string rootDirectory);
    bool isManagedMacOSPlistKey(std::string key);
    bool isManagedIOSPlistKey(std::string key);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseResourceArray(doof::JsonValue value, std::string manifestPath, std::string rootDirectory, std::string fieldPath);
    doof::Result<std::string, std::string> normalizeResourceDestination(std::string destination, std::string manifestPath, std::string fieldPath);
    doof::Result<void, std::string> appendNativeFragment(std::shared_ptr<NativeBuildPlan> target, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> fragment, std::string manifestPath, std::string rootDirectory, std::string fieldPath);
    doof::Result<void, std::string> appendStringArrayField(std::shared_ptr<std::vector<std::string>> target, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name, std::string manifestPath, std::string fieldPath, std::string pathRoot);
    void appendNativeBuild(std::shared_ptr<NativeBuildPlan> target, std::shared_ptr<NativeBuildPlan> source);
    void appendUniqueValues(std::shared_ptr<std::vector<std::string>> target, std::shared_ptr<std::vector<std::string>> values);
    void appendUnique(std::shared_ptr<std::vector<std::string>> target, std::string value);
    doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> manifestObject(doof::JsonValue value, std::string manifestPath, std::string fieldPath);
    doof::Result<std::shared_ptr<std::vector<doof::JsonValue>>, std::string> manifestArray(doof::JsonValue value, std::string manifestPath, std::string fieldPath);
    doof::Result<std::string, std::string> manifestString(doof::JsonValue value, std::string manifestPath, std::string fieldPath);
}

namespace app_src_package_manifest_ {
}
