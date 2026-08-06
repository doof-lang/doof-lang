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
namespace app_src_compiler_ { struct Compilation; }
namespace app_src_cli_ { struct CliRequest; }
namespace app_src_external_dependency_ { struct ExternalDependencyTarget; }
namespace app_src_dependency_policy_ { struct ReachedPackageInput; }
namespace app_src_dependency_policy_ { struct ResolvedExternalInput; }
namespace app_src_emitter_project_ { struct NativePackageInput; }
namespace app_src_emitter_project_ { struct ProjectEmission; }
namespace app_src_emitter_names_ { struct ModuleNamespaceMapping; }
namespace app_src_emitter_module_ { struct ModuleEmission; }
namespace app_src_emitter_module_ { struct ModuleEmissionCacheKey; }
namespace app_src_emitter_module_ { struct ModuleGraphEmission; }
namespace app_src_frontend_cache_ { struct FrontendCacheState; }
namespace app_src_frontend_cache_ { struct FrontendFileInput; }
namespace app_src_frontend_cache_ { struct FrontendModuleOutput; }
namespace app_src_frontend_cache_ { struct FrontendSourceProbe; }
namespace app_src_module_acquisition_ { struct ModuleAcquisition; }
namespace app_src_package_manifest_ { struct ExternalDependency; }
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace app_src_package_manifest_ { struct PackageDependency; }
namespace app_src_package_manifest_ { struct PackageManifest; }
namespace app_src_package_manifest_ { struct PackageResource; }
namespace app_src_package_acquisition_ { struct ExactPackageSource; }
namespace app_src_parser_ { struct Parser; }
namespace app_src_resource_state_ { struct MaterializedResource; }
namespace app_src_resource_state_ { struct ResourceState; }
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct SemanticLocation; }
namespace app_src_semantic_ { struct SemanticSpan; }
namespace app_src_semantic_ { struct SourceFile; }
namespace app_src_std_catalog_ { struct StdCatalog; }
namespace app_src_emitter_module_ { struct CoverageModuleMetadata; }
namespace app_src_test_runner_ { struct CoverageReport; }
namespace app_src_test_runner_ { struct DiscoveredTest; }
namespace std_::blob::index { struct BlobReader; }
namespace std_::fs::types { enum class EntryKind; }
namespace std_::os::index { struct ExecOptions; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_driver_ {
    struct NativeCommandResult;
    struct DriverSourceRoot;
    struct DriverReachedPackage;
    struct DriverAcquiredSource;
    struct DriverSourceState;
    extern int32_t MAX_PRINTED_DIAGNOSTICS;
    extern int64_t MAX_NATIVE_COMPILER_OUTPUT_BYTES;
    extern int64_t MAX_COVERAGE_OUTPUT_BYTES;
}

#include "src_compiler.hpp"
#include "src_diagnostics.hpp"
#include "src_cli.hpp"
#include "src_external_dependency.hpp"
#include "src_dependency_policy.hpp"
#include "src_emitter_project.hpp"
#include "src_emitter_names.hpp"
#include "src_emitter_module.hpp"
#include "src_frontend_cache.hpp"
#include "src_module_acquisition.hpp"
#include "src_native_build_driver.hpp"
#include "src_package_manifest.hpp"
#include "src_package_acquisition.hpp"
#include "src_macos_app.hpp"
#include "src_macos_app_driver.hpp"
#include "src_ios_app.hpp"
#include "src_ios_app_driver.hpp"
#include "src_ios_device.hpp"
#include "src_parser.hpp"
#include "src_project.hpp"
#include "src_provenance.hpp"
#include "src_resource_state.hpp"
#include "src_resolver.hpp"
#include "src_run_command.hpp"
#include "src_semantic.hpp"
#include "src_std_catalog.hpp"
#include "src_test_runner.hpp"
#include "std_blob_index.hpp"
#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"

namespace app_src_driver_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct NativeCommandResult : public std::enable_shared_from_this<NativeCommandResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    std::string error = std::string("");
    bool truncated;
    NativeCommandResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> output, std::string error, bool truncated) : exitCode(exitCode), output(output), error(error), truncated(truncated) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCommandResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct DriverSourceRoot : public std::enable_shared_from_this<DriverSourceRoot> {
    std::string logicalPrefix;
    std::string diskRoot;
    DriverSourceRoot(std::string logicalPrefix, std::string diskRoot) : logicalPrefix(logicalPrefix), diskRoot(diskRoot) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DriverSourceRoot>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct DriverReachedPackage : public std::enable_shared_from_this<DriverReachedPackage> {
    std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    std::string introducedBy;
    std::string sourceKind;
    std::string sourceUrl = std::string("");
    std::string sourceRef = std::string("");
    std::string sourceCommit = std::string("");
    std::string requestedUrl = std::string("");
    std::string requestedRef = std::string("");
    std::string requestedCommit = std::string("");
    bool mutable_ = false;
    DriverReachedPackage(std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::string introducedBy, std::string sourceKind, std::string sourceUrl = std::string(""), std::string sourceRef = std::string(""), std::string sourceCommit = std::string(""), std::string requestedUrl = std::string(""), std::string requestedRef = std::string(""), std::string requestedCommit = std::string(""), bool mutable_ = false) : acquisition(acquisition), manifest(manifest), introducedBy(introducedBy), sourceKind(sourceKind), sourceUrl(sourceUrl), sourceRef(sourceRef), sourceCommit(sourceCommit), requestedUrl(requestedUrl), requestedRef(requestedRef), requestedCommit(requestedCommit), mutable_(mutable_) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DriverReachedPackage>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct DriverAcquiredSource : public std::enable_shared_from_this<DriverAcquiredSource> {
    std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition;
    std::string introducedBy;
    std::string sourceKind;
    std::string sourceUrl = std::string("");
    std::string sourceRef = std::string("");
    std::string sourceCommit = std::string("");
    std::string requestedUrl = std::string("");
    std::string requestedRef = std::string("");
    std::string requestedCommit = std::string("");
    bool mutable_ = false;
    DriverAcquiredSource(std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition, std::string introducedBy, std::string sourceKind, std::string sourceUrl = std::string(""), std::string sourceRef = std::string(""), std::string sourceCommit = std::string(""), std::string requestedUrl = std::string(""), std::string requestedRef = std::string(""), std::string requestedCommit = std::string(""), bool mutable_ = false) : acquisition(acquisition), introducedBy(introducedBy), sourceKind(sourceKind), sourceUrl(sourceUrl), sourceRef(sourceRef), sourceCommit(sourceCommit), requestedUrl(requestedUrl), requestedRef(requestedRef), requestedCommit(requestedCommit), mutable_(mutable_) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DriverAcquiredSource>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct DriverSourceState : public std::enable_shared_from_this<DriverSourceState> {
    std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions;
    std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>> acquiredSources;
    std::shared_ptr<std::vector<std::shared_ptr<DriverReachedPackage>>> reachedPackages;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings;
    std::string nativePlatform;
    std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget> externalTarget;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest;
    std::shared_ptr<::app_src_std_catalog_::StdCatalog> stdCatalog;
    std::string packageAcquisitionRoot;
    DriverSourceState(std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots, std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions, std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>> acquiredSources, std::shared_ptr<std::vector<std::shared_ptr<DriverReachedPackage>>> reachedPackages, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings, std::string nativePlatform, std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget> externalTarget, std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest, std::shared_ptr<::app_src_std_catalog_::StdCatalog> stdCatalog, std::string packageAcquisitionRoot) : localRoots(localRoots), acquisitions(acquisitions), acquiredSources(acquiredSources), reachedPackages(reachedPackages), namespaceMappings(namespaceMappings), nativePlatform(nativePlatform), externalTarget(externalTarget), rootManifest(rootManifest), stdCatalog(stdCatalog), packageAcquisitionRoot(packageAcquisitionRoot) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DriverSourceState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string hostPlatform();
    std::shared_ptr<NativeCommandResult> runNativeCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::optional<std::string>& directory = std::nullopt, bool inheritOutput = false, int64_t maxOutputBytes = 262144LL);
    int32_t printNativeCommandOutput(const std::shared_ptr<NativeCommandResult>& result, int32_t remainingLines);
    std::string driverWithExtension(const std::string& path);
    std::string driverLogicalPath(const std::string& path);
    std::string driverSourceSuffix(const std::string& path);
    std::string driverOutputPath(const std::string& directory, const std::string& name);
    std::string driverSourceDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions);
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> loadDriverSource(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions);
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> configuredDriverSource(const std::string& logicalPath);
    std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquiredPackageForLoadedSource(const std::string& logicalPath, const std::shared_ptr<DriverSourceState>& state);
    doof::Result<void, std::shared_ptr<::app_src_semantic_::Diagnostic>> registerReachedPackage(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition);
    std::shared_ptr<DriverAcquiredSource> acquiredSourceFor(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition);
    doof::Result<void, std::string> ensureStdPackageAcquisition(const std::string& logicalPath);
    doof::Result<void, std::string> ensureStdPackageReached(const std::string& packageName);
    std::shared_ptr<::app_src_semantic_::Diagnostic> driverDiagnostic(const std::string& module, const std::string& message);
    std::string driverSourceDiskRoot(const std::string& path);
    doof::Result<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>, std::string> sourceLoaderForRequest(const std::string& entryPath, const std::string& stdlibRoot, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& nativePlatform = std::string(""), const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget = nullptr);
    doof::Result<void, std::string> configureDeclaredDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& ownerPrefix, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& packageAcquisitionRoot, const std::string& nativePlatform, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions, const std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>>& acquiredSources);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> reachedPackageInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>, std::string> resolvedDependencyInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest);
    doof::Result<void, std::string> acquireResolvedExternalInputs(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& inputs, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& target);
    std::shared_ptr<::app_src_package_manifest_::ExternalDependency> selectedExternalDependency(const std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>& input);
    doof::Result<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>, std::string> externalTargetForRequest(const std::string& target, const std::string& nativePlatform, const std::string& iosDestination, const std::string& iosMinimumVersion);
    std::string driverLogicalPrefix(const std::string& path);
    std::string driverRootLogicalPrefix(const std::string& packageName, const std::string& rootDirectory);
    std::string driverRootLogicalPath(const std::string& path, const std::string& rootDirectory, const std::string& packageName);
    std::string driverPackageOutputRoot(const std::string& logicalPrefix);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> projectNativePackages(const std::string& projectRoot, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& projectManifest, const std::string& stdlibRoot = std::string(""));
    void ensureOutputDirectory(const std::string& path);
    void materializeNativeCopy(const std::string& sourcePath, const std::string& outputPath);
    void writeTextIfChanged(const std::string& path, const std::string& content);
    std::string frontendCachePath(const std::string& buildDirectory, const std::string& kind);
    std::string frontendConfigurationFingerprint(const std::string& entry, const std::string& entryMode, const std::string& target, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& stdlibRoot, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget);
    std::string readTextOrEmpty(const std::string& path);
    std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> readFrontendState(const std::string& path);
    bool frontendStateMatches(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& configurationFingerprint, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader);
    std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> frontendStateForCompilation(const std::shared_ptr<::app_src_compiler_::Compilation>& result, const std::string& configurationFingerprint, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest);
    std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> cachedModuleGraph(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>> reusableEmissionKeys(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory);
    void addFrontendFileInput(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>>& inputs, const std::string& path);
    void writeFrontendState(const std::string& path, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state);
    void removeStaleFrontendOutputs(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& previous, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& current, const std::string& outputDirectory);
    void writeBlobIfChanged(const std::string& path, const std::shared_ptr<std::vector<uint8_t>>& content);
    bool blobsEqual(const std::shared_ptr<std::vector<uint8_t>>& left, const std::shared_ptr<std::vector<uint8_t>>& right);
    void materializeProject(const std::string& outputDirectory, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project);
    void materializeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory);
    std::shared_ptr<::app_src_resource_state_::ResourceState> readResourceState(const std::string& path);
    void materializeTrackedResource(const std::string& sourcePath, const std::string& outputPath, const std::shared_ptr<::app_src_resource_state_::ResourceState>& previous, const std::shared_ptr<::app_src_resource_state_::ResourceState>& next);
    bool resourceOutputIsCurrent(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>& files, const std::string& outputPath);
    void synchronizeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory, const std::string& statePath);
    void materializeRuntimeHeader(const std::string& outputDirectory);
    std::string nativeBuildOutputName(const std::string& projectName, const std::string& nativePlatform);
    void printDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics);
    void collectTestFiles(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results, bool root = true);
    std::shared_ptr<std::vector<std::string>> sortedTestFiles(const std::shared_ptr<std::vector<std::string>>& values);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> sortedDiscoveredTests(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>& values);
    void mergeCoverageGroup(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& groupModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& groupHits, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& allModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& allHits);
    void printCoverageSummary(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report);
    std::string coverageHtmlPath(const std::string& jsonPath);
    std::string writeCoverageHtml(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report, const std::string& jsonPath, const std::string& rootDirectory);
    int32_t testRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request);
    int32_t emitRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request);
    int32_t doof_main(const std::shared_ptr<std::vector<std::string>>& args);
}

namespace app_src_driver_ {
}
