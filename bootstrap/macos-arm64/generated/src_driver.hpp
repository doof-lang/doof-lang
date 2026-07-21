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
namespace app_src_cli_ { struct CliRequest; }
namespace app_src_external_dependency_ { struct ExternalDependencyTarget; }
namespace app_src_dependency_policy_ { struct ReachedPackageInput; }
namespace app_src_dependency_policy_ { struct ResolvedExternalInput; }
namespace app_src_emitter_project_ { struct NativePackageInput; }
namespace app_src_emitter_project_ { struct ProjectEmission; }
namespace app_src_emitter_names_ { struct ModuleNamespaceMapping; }
namespace app_src_module_acquisition_ { struct ModuleAcquisition; }
namespace app_src_native_build_ { struct NativeCompileTask; }
namespace app_src_package_manifest_ { struct ExternalDependency; }
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace app_src_package_manifest_ { struct PackageDependency; }
namespace app_src_package_manifest_ { struct PackageManifest; }
namespace app_src_package_manifest_ { struct PackageResource; }
namespace app_src_package_acquisition_ { struct ExactPackageSource; }
namespace app_src_parser_ { struct Parser; }
namespace app_src_pkg_config_ { struct PkgConfigCommandResult; }
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
    struct NativeCompilerBatchResult;
    struct NativeCompilerWorker;
    struct DriverSourceRoot;
    struct DriverReachedPackage;
    struct DriverAcquiredSource;
    struct DriverSourceState;
}

#include "src_compiler.hpp"
#include "src_diagnostics.hpp"
#include "src_cli.hpp"
#include "src_external_dependency.hpp"
#include "src_dependency_policy.hpp"
#include "src_emitter_project.hpp"
#include "src_emitter_names.hpp"
#include "src_module_acquisition.hpp"
#include "src_native_build.hpp"
#include "src_package_manifest.hpp"
#include "src_package_acquisition.hpp"
#include "src_macos_app.hpp"
#include "src_macos_app_driver.hpp"
#include "src_ios_app.hpp"
#include "src_ios_app_driver.hpp"
#include "src_ios_device.hpp"
#include "src_parser.hpp"
#include "src_pkg_config.hpp"
#include "src_project.hpp"
#include "src_provenance.hpp"
#include "src_resolver.hpp"
#include "src_run_command.hpp"
#include "src_semantic.hpp"
#include "src_std_catalog.hpp"
#include "src_test_runner.hpp"
#include "std_blob_index.hpp"
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
    struct NativeCompilerBatchResult : public std::enable_shared_from_this<NativeCompilerBatchResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<std::shared_ptr<NativeCommandResult>>> outputs;
    NativeCompilerBatchResult(int32_t exitCode, std::shared_ptr<std::vector<std::shared_ptr<NativeCommandResult>>> outputs) : exitCode(exitCode), outputs(outputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilerBatchResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilerWorker : public std::enable_shared_from_this<NativeCompilerWorker> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>> tasks;
    NativeCompilerWorker(std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>> tasks) : tasks(tasks) {}
    std::shared_ptr<NativeCompilerBatchResult> compile();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilerWorker>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    std::shared_ptr<NativeCommandResult> runNativeCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::optional<std::string> directory = std::nullopt, bool inheritOutput = false, int64_t maxOutputBytes = 262144LL);
    int32_t printNativeCommandOutput(std::shared_ptr<NativeCommandResult> result, int32_t remainingLines);
    std::string driverWithExtension(std::string path);
    std::string driverLogicalPath(std::string path);
    std::string driverSourceSuffix(std::string path);
    std::string driverOutputPath(std::string directory, std::string name);
    std::string driverSourceDiskPath(std::string logicalPath, std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots, std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions);
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> loadDriverSource(std::string logicalPath, std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots, std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions);
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> configuredDriverSource(std::string logicalPath);
    std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquiredPackageForLoadedSource(std::string logicalPath, std::shared_ptr<DriverSourceState> state);
    doof::Result<void, std::shared_ptr<::app_src_semantic_::Diagnostic>> registerReachedPackage(std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition);
    std::shared_ptr<DriverAcquiredSource> acquiredSourceFor(std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition);
    doof::Result<void, std::string> ensureStdPackageAcquisition(std::string logicalPath);
    doof::Result<void, std::string> ensureStdPackageReached(std::string packageName);
    std::shared_ptr<::app_src_semantic_::Diagnostic> driverDiagnostic(std::string module, std::string message);
    std::string driverSourceDiskRoot(std::string path);
    doof::Result<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>, std::string> sourceLoaderForRequest(std::string entryPath, std::string stdlibRoot, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings, std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest, std::string nativePlatform = std::string(""), std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget> externalTarget = nullptr);
    doof::Result<void, std::string> configureDeclaredDependencies(std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::string ownerPrefix, std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest, std::string packageAcquisitionRoot, std::string nativePlatform, std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions, std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>> acquiredSources);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> reachedPackageInputs(std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>, std::string> resolvedDependencyInputs(std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest);
    doof::Result<void, std::string> acquireResolvedExternalInputs(std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> inputs, std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget> target);
    std::shared_ptr<::app_src_package_manifest_::ExternalDependency> selectedExternalDependency(std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput> input);
    doof::Result<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>, std::string> externalTargetForRequest(std::string target, std::string nativePlatform, std::string iosDestination, std::string iosMinimumVersion);
    std::string driverLogicalPrefix(std::string path);
    std::string driverRootLogicalPrefix(std::string packageName, std::string rootDirectory);
    std::string driverRootLogicalPath(std::string path, std::string rootDirectory, std::string packageName);
    std::string driverPackageOutputRoot(std::string logicalPrefix);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> projectNativePackages(std::string projectRoot, std::shared_ptr<::app_src_package_manifest_::PackageManifest> projectManifest, std::string stdlibRoot = std::string(""));
    void ensureOutputDirectory(std::string path);
    void materializeNativeCopy(std::string sourcePath, std::string outputPath);
    void materializeProject(std::string outputDirectory, std::shared_ptr<::app_src_emitter_project_::ProjectEmission> project);
    void materializeExecutableResources(std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>> resources, std::string outputDirectory);
    void materializeRuntimeHeader(std::string outputDirectory);
    std::string buildOutputName(std::string projectName);
    int32_t buildProject(std::shared_ptr<::app_src_cli_::CliRequest> request, std::string outputDirectory, std::string outputPath, std::shared_ptr<::app_src_emitter_project_::ProjectEmission> project, bool release = false);
    void printDiagnostics(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void collectTestFiles(std::string path, std::shared_ptr<std::vector<std::string>> results, bool root = true);
    std::shared_ptr<std::vector<std::string>> sortedTestFiles(std::shared_ptr<std::vector<std::string>> values);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> sortedDiscoveredTests(std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> values);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> selectedModuleTests(std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> tests, std::string modulePath);
    std::string safeTestOutputName(std::string displayPath);
    void mergeCoverageGroup(std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> groupModules, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> groupHits, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> allModules, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> allHits);
    void printCoverageSummary(std::shared_ptr<::app_src_test_runner_::CoverageReport> report);
    std::string coverageHtmlPath(std::string jsonPath);
    std::string writeCoverageHtml(std::shared_ptr<::app_src_test_runner_::CoverageReport> report, std::string jsonPath, std::string rootDirectory);
    int32_t testRequest(std::shared_ptr<::app_src_cli_::CliRequest> request);
    int32_t emitRequest(std::shared_ptr<::app_src_cli_::CliRequest> request);
    int32_t doof_main(std::shared_ptr<std::vector<std::string>> args);
}

namespace app_src_driver_ {
}
