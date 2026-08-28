#include "src_driver.hpp"

namespace app_src_analyzer_ { void __doof_initialize_module(); }
namespace app_src_emitter_names_ { void __doof_initialize_module(); }
namespace std_::time::duration { void __doof_initialize_module(); }
namespace std_::time::temporal { void __doof_initialize_module(); }
namespace app_src_external_dependency_ { void __doof_initialize_module(); }
namespace app_src_package_acquisition_ { void __doof_initialize_module(); }
namespace app_src_driver_ { void __doof_initialize_module(); }

namespace app_src_driver_ {
using namespace ::app_src_compiler_;
using namespace ::app_src_diagnostics_;
using namespace ::app_src_cli_;
using namespace ::app_src_external_dependency_;
using namespace ::app_src_dependency_policy_;
using namespace ::app_src_emitter_project_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_emitter_module_;
using namespace ::app_src_frontend_cache_;
using namespace ::app_src_module_acquisition_;
using namespace ::app_src_native_build_driver_;
using namespace ::app_src_native_build_;
using namespace ::app_src_package_manifest_;
using namespace ::app_src_package_acquisition_;
using namespace ::app_src_macos_app_;
using namespace ::app_src_macos_app_driver_;
using namespace ::app_src_ios_app_;
using namespace ::app_src_ios_app_driver_;
using namespace ::app_src_ios_device_;
using namespace ::app_src_parser_;
using namespace ::app_src_project_;
using namespace ::app_src_provenance_;
using namespace ::app_src_profile_command_;
using namespace ::app_src_resource_state_;
using namespace ::app_src_resolver_;
using namespace ::app_src_run_command_;
using namespace ::app_src_semantic_;
using namespace ::app_src_std_catalog_;
using namespace ::app_src_test_runner_;
using namespace ::app_src_progress_;
using namespace ::app_src_wasm_test_runner_;
using namespace ::std_::blob::index;
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
int32_t MAX_PRINTED_DIAGNOSTICS = 20;
int64_t MAX_NATIVE_COMPILER_OUTPUT_BYTES = 262144LL;
int64_t MAX_COVERAGE_OUTPUT_BYTES = 16777216LL;
::app_src_native_build_driver_::NativeBuildOutputMode nativeBuildOutputModeForCommand(const std::string& command) {
    return ((command == std::string("run")) ? ::app_src_native_build_driver_::NativeBuildOutputMode::Silent : ::app_src_native_build_driver_::NativeBuildOutputMode::Progress);
}
int32_t runProfileTarget(const std::shared_ptr<::app_src_cli_::CliRequest>& request, const std::string& targetPath, const std::string& binaryPath, const std::string& symbolsPath, const std::string& packageRoot, const std::string& buildDirectory, const std::string& traceName, bool consoleTarget) {
    const auto symbolsPlan = ::app_src_profile_command_::planProfileSymbols(binaryPath, symbolsPath, packageRoot);
    const auto symbolsResult = runNativeCommand(symbolsPlan->command, symbolsPlan->arguments, symbolsPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
    if (symbolsResult->error != std::string("")) {
        doof::println((std::string("error: ") + symbolsResult->error));
    }
    if (symbolsResult->exitCode != 0) {
        doof::println((std::string("error: could not create profiling symbols at ") + symbolsPath));
        return symbolsResult->exitCode;
    }
    const auto tracePath = ((request->traceOutput == std::string("")) ? ::app_src_project_::joinPath(::app_src_project_::joinPath(buildDirectory, std::string("profiles")), (((traceName + std::string("-")) + doof::to_string(::std_::time::temporal::Instant::now()->toEpochMillis())) + std::string(".trace"))) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->traceOutput); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 97, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
    if (::doof_fs::exists(tracePath)) {
        doof::println((std::string("error: profile trace already exists: ") + tracePath));
        return 1;
    }
    ensureOutputDirectory(::app_src_project_::parentPath(tracePath));
    const auto plan = ::app_src_profile_command_::planProfileCapture(targetPath, request->programArguments, packageRoot, tracePath, request->profileTimeLimit, consoleTarget);
    const auto result = runNativeCommand(plan->command, plan->arguments, plan->directory, true, ::std_::os::index::ProcessGroupMode::Inherited, 262144LL);
    if (!::doof_fs::exists(tracePath)) {
        if (result->error != std::string("")) {
            doof::println((std::string("error: ") + result->error));
        }
        doof::println((std::string("error: profiling did not produce a trace at ") + tracePath));
        return 1;
    }
    if (!request->profileNoOpen) {
        const auto openPlan = ::app_src_profile_command_::planProfileOpen(tracePath, packageRoot);
        const auto opened = runNativeCommand(openPlan->command, openPlan->arguments, openPlan->directory, false, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
        if (opened->exitCode != 0) {
            doof::println(((std::string("error: profile trace was saved at ") + tracePath) + std::string(" but could not be opened")));
            return 1;
        }
    }
    return 0;
}
std::string hostPlatform() {
    const auto value = ::std_::os::index::platform();
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}




std::shared_ptr<TestWorkerCompletion> TestProcessWorker::runTest(int32_t workerIndex, const std::string& id) {
    auto command = this->command;
    auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{id});
    if (this->wasmModule != std::string("")) {
        const auto invocation = ::app_src_wasm_test_runner_::planAppleWasmTestRun(this->command, this->wasmModule, id);
        (command = invocation->command);
        (arguments = invocation->arguments);
    }
    const auto result = runNativeCommand(command, arguments, this->directory, false, ::std_::os::index::ProcessGroupMode::Isolated, this->maxOutputBytes);
    return std::make_shared<TestWorkerCompletion>(workerIndex, std::make_shared<TestExecutionResult>(id, result));
}
std::shared_ptr<NativeCommandResult> runNativeCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::optional<std::string>& directory, bool inheritOutput, ::std_::os::index::ProcessGroupMode processGroupMode, int64_t maxOutputBytes) {
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(directory, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, inheritOutput, processGroupMode, maxOutputBytes, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return std::make_shared<NativeCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error, false);
    }
    const auto executed = doof::success_value(_binding_value_1);
    std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    if (!inheritOutput) {
        (output = executed->stdout_);
    }
    return std::make_shared<NativeCommandResult>(executed->exitCode, output, std::string(""), executed->stdoutTruncated);
}
int32_t printNativeCommandOutput(const std::shared_ptr<NativeCommandResult>& result, int32_t remainingLines) {
    auto remaining = remainingLines;
    const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
    const auto& _iterable_3 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_3) {
        if (line == std::string("")) {
            continue;
        }
        if (remaining <= 0) {
            return 0;
        }
        doof::println(line);
        (remaining -= 1);
    }
    return remaining;
}
std::string driverWithExtension(const std::string& path) {
    if (doof::string_endsWith(path, std::string(".do"))) {
        return path;
    }
    return (path + std::string(".do"));
}
std::string driverLogicalPath(const std::string& path) {
    const auto withExtension = driverWithExtension(path);
    const auto sourceSuffix = driverSourceSuffix(withExtension);
    if (sourceSuffix != withExtension) {
        return sourceSuffix;
    }
    if (doof::string_startsWith(withExtension, std::string("/"))) {
        return withExtension;
    }
    return (std::string("/") + withExtension);
}
std::string driverSourceSuffix(const std::string& path) {
    const auto marker = std::string("/src/");
    auto index = 0;
    while ((index + static_cast<int32_t>(marker.size())) <= static_cast<int32_t>(path.size())) {
        if (doof::string_substring(path, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
            return doof::string_substring(path, index, static_cast<int32_t>(path.size()));
        }
        (index = (index + 1));
    }
    return path;
}
std::string driverOutputPath(const std::string& directory, const std::string& name) {
    if (doof::string_endsWith(directory, std::string("/"))) {
        return (directory + name);
    }
    return ((directory + std::string("/")) + name);
}




std::shared_ptr<DriverSourceState> configuredDriverSourceState;
std::string driverSourceDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions) {
    const auto& _iterable_5 = localRoots;
    for (const auto& root : *_iterable_5) {
        if (logicalPath == root->logicalPrefix) {
            return root->diskRoot;
        }
        const auto prefix = (root->logicalPrefix + std::string("/"));
        if (doof::string_startsWith(logicalPath, prefix)) {
            return ::app_src_project_::joinPath(root->diskRoot, doof::string_substring(logicalPath, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(logicalPath.size())));
        }
    }
    const auto acquiredPath = ::app_src_module_acquisition_::acquiredModuleDiskPath(logicalPath, acquisitions);
    if (!doof::is_null(acquiredPath)) {
        return acquiredPath.value();
    }
    return logicalPath;
}
doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> loadDriverSource(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions) {
    const auto diskPath = driverSourceDiskPath(logicalPath, localRoots, acquisitions);
    if (!::doof_fs::exists(diskPath)) {
        return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ nullptr };
    }
    auto _binding_value_6 = ::doof_fs::readText(diskPath);
    if (doof::is_failure(_binding_value_6)) {
        const auto& source = _binding_value_6;
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(logicalPath, ([&]() -> std::string { std::string _interpolation = "Could not read source file "; _interpolation += doof::to_string(diskPath); _interpolation += ""; return _interpolation; }())) };
    }
    const auto source = doof::success_value(_binding_value_6);
    return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ std::make_shared<::app_src_semantic_::SourceFile>(logicalPath, source, diskPath) };
}
doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> configuredDriverSource(const std::string& logicalPath) {
    if (doof::string_startsWith(logicalPath, std::string("/std/"))) {
        auto _binding_value_7 = ensureStdPackageAcquisition(logicalPath);
        if (doof::is_failure(_binding_value_7)) {
            const auto error = doof::failure_error(_binding_value_7);
            return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(logicalPath, error) };
        }
    }
    auto _try_value_8 = loadDriverSource(logicalPath, configuredDriverSourceState->localRoots, configuredDriverSourceState->acquisitions);
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{doof::variant_promote<std::shared_ptr<::app_src_semantic_::Diagnostic>>(doof::failure_error(_try_value_8))};
    const auto source = doof::success_value(_try_value_8);
    if (!doof::is_null(source)) {
        const auto package = acquiredPackageForLoadedSource(logicalPath, configuredDriverSourceState);
        if (!doof::is_null(package)) {
            auto _try_value_9 = registerReachedPackage(doof::unwrap_optional(package));
            if (doof::is_failure(_try_value_9)) return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{doof::variant_promote<std::shared_ptr<::app_src_semantic_::Diagnostic>>(doof::failure_error(_try_value_9))};
        }
    }
    return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ source };
}
std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquiredPackageForLoadedSource(const std::string& logicalPath, const std::shared_ptr<DriverSourceState>& state) {
    const auto& _iterable_11 = state->localRoots;
    for (const auto& root : *_iterable_11) {
        if ((logicalPath == root->logicalPrefix) || doof::string_startsWith(logicalPath, (root->logicalPrefix + std::string("/")))) {
            return nullptr;
        }
    }
    return ::app_src_module_acquisition_::acquiredPackageForModule(logicalPath, state->acquisitions);
}
doof::Result<std::shared_ptr<::app_src_package_manifest_::PackageManifest>, std::string> parseDependencyManifestForTarget(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& nativePlatform, const std::string& rootTarget) {
    const auto dependencyTarget = ((rootTarget == std::string("wasm")) ? std::string("wasm") : std::string(""));
    return ::app_src_package_manifest_::parsePackageManifest(source, manifestPath, rootDirectory, nativePlatform, dependencyTarget);
}
doof::Result<void, std::shared_ptr<::app_src_semantic_::Diagnostic>> registerReachedPackage(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition) {
    const auto& _iterable_13 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_13) {
        if ((reached->acquisition->logicalPrefix == acquisition->logicalPrefix) && (reached->acquisition->diskRoot == acquisition->diskRoot)) {
            return doof::Success<void>{};
        }
    }
    const auto manifestPath = ::app_src_module_acquisition_::acquiredManifestPath(acquisition);
    auto _binding_value_14 = ::doof_fs::readText(manifestPath);
    if (doof::is_failure(_binding_value_14)) {
        const auto& manifestSource = _binding_value_14;
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, ([&]() -> std::string { std::string _interpolation = "Could not read doof.json for acquired package "; _interpolation += doof::to_string(acquisition->logicalPrefix); _interpolation += " at "; _interpolation += doof::to_string(manifestPath); _interpolation += ""; return _interpolation; }())) };
    }
    const auto manifestSource = doof::success_value(_binding_value_14);
    auto _binding_value_15 = parseDependencyManifestForTarget(manifestSource, manifestPath, acquisition->diskRoot, configuredDriverSourceState->nativePlatform, configuredDriverSourceState->rootManifest->target);
    if (doof::is_failure(_binding_value_15)) {
        const auto error = doof::failure_error(_binding_value_15);
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, error) };
    }
    const auto manifest = doof::success_value(_binding_value_15);
    if ((static_cast<int32_t>((manifest->packageResolutions)->size()) > 0) || (static_cast<int32_t>((manifest->externalResolutions)->size()) > 0)) {
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, std::string("resolutions are only allowed in the root doof.json")) };
    }
    const auto source = acquiredSourceFor(acquisition);
    configuredDriverSourceState->reachedPackages->push_back(std::make_shared<DriverReachedPackage>(acquisition, manifest, (doof::is_null(source) ? std::string("") : source->introducedBy), (doof::is_null(source) ? std::string("local") : source->sourceKind), (doof::is_null(source) ? std::string("") : source->sourceUrl), (doof::is_null(source) ? std::string("") : source->sourceRef), (doof::is_null(source) ? std::string("") : source->sourceCommit), (doof::is_null(source) ? std::string("") : source->requestedUrl), (doof::is_null(source) ? std::string("") : source->requestedRef), (doof::is_null(source) ? std::string("") : source->requestedCommit), (doof::is_null(source) ? true : source->mutable_)));
    configuredDriverSourceState->namespaceMappings->push_back(std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(acquisition->logicalPrefix, manifest->name, driverPackageOutputRoot(acquisition->logicalPrefix)));
    return doof::Success<void>{};
}
std::shared_ptr<DriverAcquiredSource> acquiredSourceFor(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition) {
    const auto& _iterable_17 = configuredDriverSourceState->acquiredSources;
    for (const auto& source : *_iterable_17) {
        if ((source->acquisition->logicalPrefix == acquisition->logicalPrefix) && (source->acquisition->diskRoot == acquisition->diskRoot)) {
            return source;
        }
    }
    return nullptr;
}
doof::Result<void, std::string> ensureStdPackageAcquisition(const std::string& logicalPath) {
    if (!doof::is_null(::app_src_module_acquisition_::acquiredModuleDiskPath(logicalPath, configuredDriverSourceState->acquisitions))) {
        return doof::Success<void>{};
    }
    const auto remainder = doof::string_substring(logicalPath, 5, static_cast<int32_t>(logicalPath.size()));
    const auto slash = doof::string_indexOf(remainder, std::string("/"));
    const auto shortName = ((slash < 0) ? remainder : doof::string_substring(remainder, 0, slash));
    const auto packageName = (std::string("std/") + shortName);
    const auto package = ::app_src_std_catalog_::stdCatalogPackage(configuredDriverSourceState->stdCatalog, packageName);
    if (doof::is_null(package)) {
        return doof::Failure<std::string>{ (std::string("Unknown standard package ") + packageName) };
    }
    auto _binding_value_18 = ::app_src_package_acquisition_::acquireExactGitPackage(std::make_shared<::app_src_package_acquisition_::ExactPackageSource>(package->name, package->name, package->url, package->ref, package->commit), configuredDriverSourceState->packageAcquisitionRoot);
    if (doof::is_failure(_binding_value_18)) {
        const auto error = doof::failure_error(_binding_value_18);
        return doof::Failure<std::string>{ error };
    }
    const auto acquired = doof::success_value(_binding_value_18);
    const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>((std::string("/") + packageName), acquired->rootDirectory);
    configuredDriverSourceState->acquisitions->push_back(acquisition);
    configuredDriverSourceState->acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, std::string(""), std::string("git"), package->url, package->ref, package->commit, std::string(""), std::string(""), std::string(""), false));
    return doof::Success<void>{};
}
doof::Result<void, std::string> ensureStdPackageReached(const std::string& packageName) {
    const auto logicalPath = ((std::string("/") + packageName) + std::string("/index.do"));
    auto _try_value_19 = ensureStdPackageAcquisition(logicalPath);
    if (doof::is_failure(_try_value_19)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_19))};
    const auto acquisition = ::app_src_module_acquisition_::acquiredPackageForModule(logicalPath, configuredDriverSourceState->acquisitions);
    if (doof::is_null(acquisition)) {
        return doof::Failure<std::string>{ (std::string("Could not resolve required standard package ") + packageName) };
    }
    auto _binding_value_20 = registerReachedPackage(doof::unwrap_optional(acquisition));
    if (doof::is_failure(_binding_value_20)) {
        const auto error = doof::failure_error(_binding_value_20);
        return doof::Failure<std::string>{ error->message };
    }
    return doof::Success<void>{};
}
std::shared_ptr<::app_src_semantic_::Diagnostic> driverDiagnostic(const std::string& module, const std::string& message) {
    auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
    return std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, ::app_src_semantic_::SemanticSpan{zero, zero}, module, std::string(""));
}
std::string driverSourceDiskRoot(const std::string& path) {
    const auto marker = std::string("/src/");
    auto index = 0;
    while ((index + static_cast<int32_t>(marker.size())) <= static_cast<int32_t>(path.size())) {
        if (doof::string_substring(path, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
            return doof::string_substring(path, 0, ((index + static_cast<int32_t>(marker.size())) - 1));
        }
        (index = (index + 1));
    }
    return std::string("");
}
doof::Result<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>, std::string> sourceLoaderForRequest(const std::string& entryPath, const std::string& stdlibRoot, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget) {
    std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots = std::make_shared<std::vector<std::shared_ptr<DriverSourceRoot>>>(std::vector<std::shared_ptr<DriverSourceRoot>>{});
    const auto rootLogicalPrefix = driverRootLogicalPrefix(rootManifest->name, rootManifest->rootDirectory);
    localRoots->push_back(std::make_shared<DriverSourceRoot>(rootLogicalPrefix, rootManifest->rootDirectory));
    const auto sourceRoot = driverSourceDiskRoot(entryPath);
    if (sourceRoot != std::string("")) {
        localRoots->push_back(std::make_shared<DriverSourceRoot>(std::string("/src"), sourceRoot));
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions = std::make_shared<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>(std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>{});
    std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>> acquiredSources = std::make_shared<std::vector<std::shared_ptr<DriverAcquiredSource>>>(std::vector<std::shared_ptr<DriverAcquiredSource>>{});
    if (stdlibRoot != std::string("")) {
        const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>(std::string("/std"), [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(stdlibRoot); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 497, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        acquisitions->push_back(acquisition);
        acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, driverLogicalPrefix(rootManifest->rootDirectory), std::string("local"), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), true));
    }
    auto _binding_value_21 = ::std_::fs::index::readTextResource(std::string("std-catalog.json"));
    if (doof::is_failure(_binding_value_21)) {
        const auto& catalogSource = _binding_value_21;
        return doof::Failure<std::string>{ std::string("Could not read embedded std-catalog.json") };
    }
    const auto catalogSource = doof::success_value(_binding_value_21);
    auto _try_value_22 = ::app_src_std_catalog_::parseStdCatalog(catalogSource);
    if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_22))};
    const auto catalog = doof::success_value(_try_value_22);
    const auto packageAcquisitionRoot = ::app_src_package_acquisition_::workspacePackageAcquisitionRoot(rootManifest->rootDirectory);
    const auto platformName = ((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform);
    auto _try_value_23 = configureDeclaredDependencies(rootManifest, std::string(""), rootManifest, packageAcquisitionRoot, platformName, acquisitions, acquiredSources);
    if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_23))};
    (configuredDriverSourceState = std::make_shared<DriverSourceState>(localRoots, acquisitions, acquiredSources, std::make_shared<std::vector<std::shared_ptr<DriverReachedPackage>>>(std::vector<std::shared_ptr<DriverReachedPackage>>{}), namespaceMappings, ((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform), (doof::is_null(externalTarget) ? std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform), std::string(""), std::string(""), std::string(""), 1) : doof::unwrap_optional(externalTarget)), rootManifest, catalog, packageAcquisitionRoot));
    return doof::Success<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>>{ configuredDriverSource };
}
doof::Result<void, std::string> configureDeclaredDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& ownerPrefix, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& packageAcquisitionRoot, const std::string& nativePlatform, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions, const std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>>& acquiredSources) {
    const auto& _iterable_25 = manifest->dependencies;
    for (const auto& requested : *_iterable_25) {
        if (doof::string_startsWith(requested->name, std::string("std/"))) {
            continue;
        }
        const auto selected = ::app_src_dependency_policy_::selectedPackageSource(requested, rootManifest->packageResolutions);
        const auto logicalPrefix = (std::string("/") + requested->name);
        auto diskRoot = std::string("");
        auto sourceKind = std::string("local");
        auto sourceUrl = std::string("");
        auto sourceRef = std::string("");
        auto sourceCommit = std::string("");
        auto mutable_ = false;
        if (selected->path != std::string("")) {
            (diskRoot = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(selected->path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 548, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
            (mutable_ = true);
        } else {
            auto _binding_value_26 = ::app_src_package_acquisition_::acquireExactGitPackage(std::make_shared<::app_src_package_acquisition_::ExactPackageSource>(selected->name, std::string(""), selected->url, selected->ref, selected->commit), packageAcquisitionRoot);
            if (doof::is_failure(_binding_value_26)) {
                const auto error = doof::failure_error(_binding_value_26);
                return doof::Failure<std::string>{ error };
            }
            const auto acquired = doof::success_value(_binding_value_26);
            (diskRoot = acquired->rootDirectory);
            (sourceKind = std::string("git"));
            (sourceUrl = ::app_src_std_catalog_::canonicalDependencyUrl(selected->url));
            (sourceRef = selected->ref);
            (sourceCommit = selected->commit);
        }
        const auto& _iterable_28 = acquiredSources;
        for (const auto& existing : *_iterable_28) {
            if ((((sourceUrl != std::string("")) && (existing->sourceUrl != std::string(""))) && (::app_src_std_catalog_::canonicalDependencyUrl(existing->sourceUrl) == sourceUrl)) && (existing->sourceCommit != sourceCommit)) {
                return doof::Failure<std::string>{ ((std::string("Conflicting package revisions for ") + sourceUrl) + std::string("; add a root resolutions.packages entry")) };
            }
            if (existing->acquisition->logicalPrefix == logicalPrefix) {
                if (existing->acquisition->diskRoot != diskRoot) {
                    return doof::Failure<std::string>{ ((std::string("Package import prefix ") + logicalPrefix) + std::string(" resolves to multiple packages")) };
                }
                (diskRoot = std::string(""));
            }
        }
        if (diskRoot == std::string("")) {
            continue;
        }
        const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>(logicalPrefix, diskRoot);
        acquisitions->push_back(acquisition);
        acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, ownerPrefix, sourceKind, sourceUrl, sourceRef, sourceCommit, ((requested->url == std::string("")) ? std::string("") : ::app_src_std_catalog_::canonicalDependencyUrl(requested->url)), requested->ref, requested->commit, mutable_));
        const auto dependencyManifestPath = ::app_src_module_acquisition_::acquiredManifestPath(acquisition);
        auto _binding_value_29 = ::doof_fs::readText(dependencyManifestPath);
        if (doof::is_failure(_binding_value_29)) {
            const auto& dependencySource = _binding_value_29;
            return doof::Failure<std::string>{ (std::string("Could not read dependency manifest ") + dependencyManifestPath) };
        }
        const auto dependencySource = doof::success_value(_binding_value_29);
        auto _try_value_30 = parseDependencyManifestForTarget(dependencySource, dependencyManifestPath, diskRoot, nativePlatform, rootManifest->target);
        if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_30))};
        const auto dependencyManifest = doof::success_value(_try_value_30);
        if (dependencyManifest->name == std::string("")) {
            return doof::Failure<std::string>{ (std::string("Dependency package must declare a name: ") + dependencyManifestPath) };
        }
        if ((static_cast<int32_t>((dependencyManifest->packageResolutions)->size()) > 0) || (static_cast<int32_t>((dependencyManifest->externalResolutions)->size()) > 0)) {
            return doof::Failure<std::string>{ (std::string("resolutions are only allowed in the root doof.json: ") + dependencyManifestPath) };
        }
        auto _try_value_31 = configureDeclaredDependencies(dependencyManifest, logicalPrefix, rootManifest, packageAcquisitionRoot, nativePlatform, acquisitions, acquiredSources);
        if (doof::is_failure(_try_value_31)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_31))};
    }
    return doof::Success<void>{};
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> reachedPackageInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>(std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>{std::make_shared<::app_src_dependency_policy_::ReachedPackageInput>(driverLogicalPrefix(rootManifest->rootDirectory), std::string(""), rootManifest, std::string("root"), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), false)});
    const auto& _iterable_33 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_33) {
        result->push_back(std::make_shared<::app_src_dependency_policy_::ReachedPackageInput>(reached->acquisition->logicalPrefix, reached->introducedBy, reached->manifest, reached->sourceKind, reached->sourceUrl, reached->sourceRef, reached->sourceCommit, reached->requestedUrl, reached->requestedRef, reached->requestedCommit, reached->mutable_));
    }
    return result;
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>, std::string> resolvedDependencyInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
    const auto packages = reachedPackageInputs(rootManifest);
    auto _try_value_34 = ::app_src_dependency_policy_::resolveExternalInputs(packages, rootManifest);
    if (doof::is_failure(_try_value_34)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_34))};
    const auto externals = doof::success_value(_try_value_34);
    auto _try_value_35 = ::app_src_dependency_policy_::validateDependencyPolicy(packages, externals, rootManifest);
    if (doof::is_failure(_try_value_35)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_35))};
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>>{ externals };
}
doof::Result<void, std::string> acquireResolvedExternalInputs(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& inputs, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& target) {
    const auto& _iterable_37 = inputs;
    for (const auto& input : *_iterable_37) {
        const auto dependency = selectedExternalDependency(input);
        const auto manifest = std::make_shared<::app_src_package_manifest_::PackageManifest>(input->owner->manifest->name, std::string("1.0"), input->owner->manifest->manifestPath, input->owner->manifest->rootDirectory, std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{dependency}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<::app_src_package_manifest_::DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::string(""), nullptr, nullptr, nullptr, nullptr);
        auto _try_value_38 = ::app_src_external_dependency_::acquirePackageExternalDependencies(manifest, target);
        if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
    }
    return doof::Success<void>{};
}
std::shared_ptr<::app_src_package_manifest_::ExternalDependency> selectedExternalDependency(const std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>& input) {
    const auto requested = input->dependency;
    return std::make_shared<::app_src_package_manifest_::ExternalDependency>(requested->name, input->selectedKind, input->selectedUrl, requested->destination, input->selectedSha256, requested->stripComponents, requested->copyFiles, input->selectedRef, input->selectedCommit, requested->commands);
}
doof::Result<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>, std::string> externalTargetForRequest(const std::string& target, const std::string& nativePlatform, const std::string& iosDestination, const std::string& iosMinimumVersion) {
    if (target == std::string("wasm")) {
        return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(std::string("wasm"), std::string(""), std::string("wasm32-unknown-emscripten"), std::string("wasm32-unknown-emscripten"), 1) };
    }
    if (!doof::string_startsWith(nativePlatform, std::string("ios-"))) {
        return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(nativePlatform, std::string(""), std::string(""), std::string(""), 1) };
    }
    const auto sdkName = ((iosDestination == std::string("device")) ? std::string("iphoneos") : std::string("iphonesimulator"));
    const auto sdkResult = runNativeCommand(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--sdk"), sdkName, std::string("--show-sdk-path")}), std::nullopt, false, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
    if (sdkResult->exitCode != 0) {
        return doof::Failure<std::string>{ ((std::string("Could not resolve the ") + sdkName) + std::string(" SDK for external dependencies")) };
    }
    const auto sdkPath = doof::string_trim(::doof_blob::NativeBlobReader::constructor(sdkResult->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((sdkResult->output)->size()))));
    const auto hostArchitecture = ::std_::os::index::architecture();
    auto _try_value_39 = ::app_src_ios_app_::iosTargetTriple(iosMinimumVersion, iosDestination, hostArchitecture);
    if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_39))};
    const auto targetTriple = doof::success_value(_try_value_39);
    const auto configureHost = ((iosDestination == std::string("device")) ? std::string("aarch64-apple-darwin") : (((hostArchitecture == std::string("x86_64")) || (hostArchitecture == std::string("x64"))) ? std::string("x86_64-apple-darwin") : std::string("aarch64-apple-darwin")));
    return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(nativePlatform, sdkPath, targetTriple, configureHost, 1) };
}
std::string driverLogicalPrefix(const std::string& path) {
    const auto absolutePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 701, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    const auto sourceSuffix = driverSourceSuffix(absolutePath);
    if (sourceSuffix != absolutePath) {
        return sourceSuffix;
    }
    if (doof::string_startsWith(absolutePath, std::string("/"))) {
        return absolutePath;
    }
    return (std::string("/") + absolutePath);
}
std::string driverRootLogicalPrefix(const std::string& packageName, const std::string& rootDirectory) {
    if (doof::string_startsWith(packageName, std::string("std/"))) {
        return (std::string("/") + packageName);
    }
    return driverLogicalPrefix(rootDirectory);
}
std::string driverRootLogicalPath(const std::string& path, const std::string& rootDirectory, const std::string& packageName) {
    if (!doof::string_startsWith(packageName, std::string("std/"))) {
        return driverLogicalPath(path);
    }
    const auto prefix = driverRootLogicalPrefix(packageName, rootDirectory);
    const auto absolutePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 716, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    const auto absoluteRoot = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(rootDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 717, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    if (absolutePath == absoluteRoot) {
        return prefix;
    }
    const auto rootPrefix = (doof::string_endsWith(absoluteRoot, std::string("/")) ? absoluteRoot : (absoluteRoot + std::string("/")));
    if (doof::string_startsWith(absolutePath, rootPrefix)) {
        return ((prefix + std::string("/")) + doof::string_substring(absolutePath, static_cast<int32_t>(rootPrefix.size()), static_cast<int32_t>(absolutePath.size())));
    }
    return driverLogicalPath(absolutePath);
}
std::string driverPackageOutputRoot(const std::string& logicalPrefix) {
    auto start = 0;
    while ((start < static_cast<int32_t>(logicalPrefix.size())) && (doof::string_at(logicalPrefix, start, "src/driver", 728) == U'\u002F')) {
        (start = (start + 1));
    }
    return doof::string_substring(logicalPrefix, start, static_cast<int32_t>(logicalPrefix.size()));
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> projectNativePackages(const std::string& projectRoot, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& projectManifest, const std::string& stdlibRoot) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> packages = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>>(std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>{std::make_shared<::app_src_emitter_project_::NativePackageInput>(driverRootLogicalPrefix(projectManifest->name, projectRoot), std::string(""), projectManifest)});
    if ((projectManifest->target == std::string("wasm")) && (stdlibRoot != std::string(""))) {
        const auto jsonRoot = ::app_src_project_::joinPath(stdlibRoot, std::string("json"));
        const auto jsonManifestPath = ::app_src_project_::joinPath(jsonRoot, std::string("doof.json"));
        const auto jsonManifest = [&]() -> std::shared_ptr<::app_src_package_manifest_::PackageManifest> { auto _try_value = ::app_src_package_manifest_::parsePackageManifest([&]() -> std::string { auto _try_value = ::doof_fs::readText(jsonManifestPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 741, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }(), jsonManifestPath, jsonRoot, std::string("wasm"), std::string("")); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 741, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
        packages->push_back(std::make_shared<::app_src_emitter_project_::NativePackageInput>(std::string("/std/json"), std::string("std/json"), jsonManifest));
    }
    const auto& _iterable_41 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_41) {
        packages->push_back(std::make_shared<::app_src_emitter_project_::NativePackageInput>(reached->acquisition->logicalPrefix, driverPackageOutputRoot(reached->acquisition->logicalPrefix), reached->manifest));
    }
    return packages;
}
void ensureOutputDirectory(const std::string& path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return;
    }
    const auto parent = ::app_src_project_::parentPath(path);
    if (parent != path) {
        ensureOutputDirectory(parent);
    }
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 762, std::string("try! failed"));  }();
}
void materializeNativeCopy(const std::string& sourcePath, const std::string& outputPath) {
    if (::doof_fs::isDirectory(sourcePath)) {
        ensureOutputDirectory(outputPath);
        const auto& _iterable_43 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 768, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_43) {
            materializeNativeCopy(::app_src_project_::joinPath(sourcePath, entry->name), ::app_src_project_::joinPath(outputPath, entry->name));
        }
        return;
    }
    ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
    writeBlobIfChanged(outputPath, [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 774, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
}
void writeTextIfChanged(const std::string& path, const std::string& content) {
    if (::doof_fs::exists(path)) {
        const auto existing = [&]() -> std::string { auto _try_value = ::doof_fs::readText(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 779, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        if (existing == content) {
            return;
        }
    }
    [&]() -> void { auto _try_value = ::doof_fs::writeText(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 782, std::string("try! failed"));  }();
}
void materializeGeneratedText(const std::string& path, const std::string& content) {
    ensureOutputDirectory(::app_src_project_::parentPath(path));
    writeTextIfChanged(path, content);
}
std::string frontendCachePath(const std::string& buildDirectory, const std::string& kind) {
    return driverOutputPath(driverOutputPath(buildDirectory, std::string(".doof-cache/v1")), (kind + std::string(".json")));
}
std::string frontendConfigurationFingerprint(const std::string& entry, const std::string& entryMode, const std::string& target, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& stdlibRoot, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget) {
    const auto manifestSource = readTextOrEmpty(manifest->manifestPath);
    return ::std_::crypto::index::sha256HexString((((((((((((((((((((((std::string("doof-frontend-cache-2:") + doof::to_string(::app_src_frontend_cache_::FRONTEND_SEMANTIC_ABI)) + std::string("\n")) + entry) + std::string("\n")) + entryMode) + std::string("\n")) + target) + std::string("\n")) + stdlibRoot) + std::string("\n")) + nativePlatform) + std::string("\n")) + externalTarget->nativeTarget) + std::string("\n")) + externalTarget->sdkPath) + std::string("\n")) + externalTarget->targetTriple) + std::string("\n")) + configuredDriverSourceState->stdCatalog->digest) + std::string("\n")) + manifestSource));
}
std::string readTextOrEmpty(const std::string& path) {
    auto _binding_value_44 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_44)) {
        const auto& source = _binding_value_44;
        return std::string("");
    }
    const auto source = doof::success_value(_binding_value_44);
    return source;
}
std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> readFrontendState(const std::string& path) {
    if (!::doof_fs::exists(path)) {
        return nullptr;
    }
    auto _binding_value_45 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_45)) {
        const auto& source = _binding_value_45;
        return nullptr;
    }
    const auto source = doof::success_value(_binding_value_45);
    return ::app_src_frontend_cache_::parseFrontendCacheState(source);
}
bool frontendStateMatches(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& configurationFingerprint, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader) {
    if (doof::is_null(state) || (state->configurationFingerprint != configurationFingerprint)) {
        return false;
    }
    const auto& _iterable_47 = state->fileInputs;
    for (const auto& input : *_iterable_47) {
        auto _binding_value_48 = ::doof_fs::readText(input->path);
        if (doof::is_failure(_binding_value_48)) {
            const auto& source = _binding_value_48;
            return false;
        }
        const auto source = doof::success_value(_binding_value_48);
        if (::std_::crypto::index::sha256HexString(source) != input->sourceHash) {
            return false;
        }
    }
    const auto& _iterable_50 = state->probes;
    for (const auto& probe : *_iterable_50) {
        auto _binding_value_51 = loader.call(probe->logicalPath);
        if (doof::is_failure(_binding_value_51)) {
            const auto& source = _binding_value_51;
            return false;
        }
        const auto source = doof::success_value(_binding_value_51);
        if (probe->missing) {
            if (!doof::is_null(source)) {
                return false;
            }
        } else {
            if (doof::is_null(source) || (::std_::crypto::index::sha256HexString(source->source) != probe->sourceHash)) {
                return false;
            }
        }
    }
    return true;
}
std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> frontendStateForCompilation(const std::shared_ptr<::app_src_compiler_::Compilation>& result, const std::string& configurationFingerprint, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
    const auto state = std::make_shared<::app_src_frontend_cache_::FrontendCacheState>(2, configurationFingerprint, std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendSourceProbe>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendSourceProbe>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendModuleOutput>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendModuleOutput>>{}));
    const auto& _iterable_53 = result->resolutionProbes;
    for (const auto& path : *_iterable_53) {
        std::shared_ptr<::app_src_semantic_::SourceFile> matched = nullptr;
        const auto& _iterable_55 = result->sourceFiles;
        for (const auto& source : *_iterable_55) {
            if (source->path == path) {
                (matched = source);
            }
        }
        state->probes->push_back(std::make_shared<::app_src_frontend_cache_::FrontendSourceProbe>(path, (doof::is_null(matched) ? std::string("") : ::std_::crypto::index::sha256HexString(matched->source)), doof::is_null(matched)));
    }
    addFrontendFileInput(state->fileInputs, rootManifest->manifestPath);
    const auto& _iterable_57 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_57) {
        addFrontendFileInput(state->fileInputs, reached->manifest->manifestPath);
    }
    if (!doof::is_null(result->emission)) {
        const auto& _iterable_59 = result->emission->modules;
        for (const auto& module : *_iterable_59) {
            state->modules->push_back(std::make_shared<::app_src_frontend_cache_::FrontendModuleOutput>(module->modulePath, module->headerName, module->sourceName, module->fingerprint));
        }
    }
    return state;
}
std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> cachedModuleGraph(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory) {
    if (static_cast<int32_t>((state->modules)->size()) == 0) {
        return nullptr;
    }
    const auto graph = std::make_shared<::app_src_emitter_module_::ModuleGraphEmission>(std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>{}), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto& _iterable_61 = state->modules;
    for (const auto& module : *_iterable_61) {
        if (!::doof_fs::exists(driverOutputPath(outputDirectory, module->headerName)) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->sourceName))) {
            return nullptr;
        }
        graph->modules->push_back(std::make_shared<::app_src_emitter_module_::ModuleEmission>(module->modulePath, std::string(""), std::string(""), module->headerName, module->sourceName, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), true, module->fingerprint));
    }
    return graph;
}
bool frontendEmissionCacheSupported(const std::string& target) {
    return ((target != std::string("wasm")) && (target != std::string("ios-app")));
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>> reusableEmissionKeys(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>> keys = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{});
    if (doof::is_null(state)) {
        return keys;
    }
    const auto& _iterable_63 = state->modules;
    for (const auto& module : *_iterable_63) {
        if (((module->fingerprint == std::string("")) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->headerName))) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->sourceName))) {
            continue;
        }
        keys->push_back(std::make_shared<::app_src_emitter_module_::ModuleEmissionCacheKey>(module->modulePath, module->fingerprint));
    }
    return keys;
}
void addFrontendFileInput(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>>& inputs, const std::string& path) {
    const auto& _iterable_65 = inputs;
    for (const auto& input : *_iterable_65) {
        if (input->path == path) {
            return;
        }
    }
    auto _binding_value_66 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_66)) {
        const auto& source = _binding_value_66;
        return;
    }
    const auto source = doof::success_value(_binding_value_66);
    inputs->push_back(std::make_shared<::app_src_frontend_cache_::FrontendFileInput>(path, ::std_::crypto::index::sha256HexString(source)));
}
void writeFrontendState(const std::string& path, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state) {
    ensureOutputDirectory(::app_src_project_::parentPath(path));
    const auto temporaryPath = (path + std::string(".tmp"));
    [&]() -> void { auto _try_value = ::doof_fs::writeText(temporaryPath, ::app_src_frontend_cache_::renderFrontendCacheState(state)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 919, std::string("try! failed"));  }();
    [&]() -> void { auto _try_value = ::doof_fs::rename(temporaryPath, path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 920, std::string("try! failed"));  }();
}
void removeStaleFrontendOutputs(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& previous, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& current, const std::string& outputDirectory) {
    if (doof::is_null(previous)) {
        return;
    }
    const auto prefix = (doof::string_endsWith(outputDirectory, std::string("/")) ? outputDirectory : (outputDirectory + std::string("/")));
    const auto& _iterable_68 = previous->modules;
    for (const auto& old : *_iterable_68) {
        auto retained = false;
        const auto& _iterable_70 = current->modules;
        for (const auto& module : *_iterable_70) {
            if (((module->modulePath == old->modulePath) && (module->headerName == old->headerName)) && (module->sourceName == old->sourceName)) {
                (retained = true);
            }
        }
        if (retained) {
            continue;
        }
        const auto& _iterable_72 = std::make_shared<std::vector<std::string>>(std::vector<std::string>{old->headerName, old->sourceName});
        for (const auto& name : *_iterable_72) {
            const auto path = driverOutputPath(outputDirectory, name);
            if ((doof::string_startsWith(path, prefix) && ::doof_fs::exists(path)) && !::doof_fs::isDirectory(path)) {
                [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 940, std::string("try! failed"));  }();
            }
        }
    }
}
void writeBlobIfChanged(const std::string& path, const std::shared_ptr<std::vector<uint8_t>>& content) {
    if (::doof_fs::exists(path)) {
        const auto existing = [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 947, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        if (blobsEqual(existing, content)) {
            return;
        }
    }
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 950, std::string("try! failed"));  }();
}
bool blobsEqual(const std::shared_ptr<std::vector<uint8_t>>& left, const std::shared_ptr<std::vector<uint8_t>>& right) {
    if (static_cast<int32_t>((left)->size()) != static_cast<int32_t>((right)->size())) {
        return false;
    }
    for (int32_t index = 0; index < static_cast<int32_t>((left)->size()); ++index) {
        if (doof::array_at(left, index, "src/driver", 955) != doof::array_at(right, index, "src/driver", 955)) {
            return false;
        }
    }
    return true;
}
void materializeProject(const std::string& outputDirectory, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project) {
    ensureOutputDirectory(outputDirectory);
    const auto& _iterable_75 = project->modules;
    for (const auto& module : *_iterable_75) {
        if (module->reused) {
            continue;
        }
        materializeGeneratedText(driverOutputPath(outputDirectory, module->headerName), module->header);
        materializeGeneratedText(driverOutputPath(outputDirectory, module->sourceName), module->source);
    }
    const auto& _iterable_77 = project->supportFiles;
    for (const auto& supportFile : *_iterable_77) {
        const auto outputPath = driverOutputPath(outputDirectory, supportFile->relativePath);
        ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
        writeTextIfChanged(outputPath, supportFile->content);
    }
    const auto& _iterable_79 = project->nativeCopies;
    for (const auto& nativeCopy : *_iterable_79) {
        materializeNativeCopy(nativeCopy->sourcePath, driverOutputPath(outputDirectory, nativeCopy->relativePath));
    }
}
void materializeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory) {
    const auto& _iterable_81 = resources;
    for (const auto& resource : *_iterable_81) {
        const auto destinationRoot = driverOutputPath(outputDirectory, resource->destination);
        const auto outputPath = (::doof_fs::isDirectory(resource->sourcePath) ? destinationRoot : driverOutputPath(destinationRoot, ::app_src_project_::fileName(resource->sourcePath)));
        materializeNativeCopy(resource->sourcePath, outputPath);
    }
}
std::shared_ptr<::app_src_resource_state_::ResourceState> readResourceState(const std::string& path) {
    if (!::doof_fs::exists(path)) {
        return std::make_shared<::app_src_resource_state_::ResourceState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>(std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>{}));
    }
    auto _binding_value_82 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_82)) {
        const auto& source = _binding_value_82;
        return std::make_shared<::app_src_resource_state_::ResourceState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>(std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>{}));
    }
    const auto source = doof::success_value(_binding_value_82);
    const auto parsed = ::app_src_resource_state_::parseResourceState(source);
    return (doof::is_null(parsed) ? std::make_shared<::app_src_resource_state_::ResourceState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>(std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>{})) : doof::unwrap_optional(parsed));
}
void materializeTrackedResource(const std::string& sourcePath, const std::string& outputPath, const std::shared_ptr<::app_src_resource_state_::ResourceState>& previous, const std::shared_ptr<::app_src_resource_state_::ResourceState>& next) {
    if (::doof_fs::isDirectory(sourcePath)) {
        ensureOutputDirectory(outputPath);
        const auto& _iterable_84 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1004, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_84) {
            materializeTrackedResource(::app_src_project_::joinPath(sourcePath, entry->name), ::app_src_project_::joinPath(outputPath, entry->name), previous, next);
        }
        return;
    }
    const auto sourceInfo = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1009, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    const auto prior = ::app_src_resource_state_::findMaterializedResource(previous, sourcePath, outputPath);
    if (::doof_fs::exists(outputPath) && !::doof_fs::isDirectory(outputPath)) {
        const auto outputInfo = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1012, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        if (::app_src_resource_state_::materializedResourceIsCurrent(prior, sourceInfo->size, sourceInfo->modifiedAt->toEpochNanos(), outputInfo->size, outputInfo->modifiedAt->toEpochNanos())) {
            next->files->push_back(doof::unwrap_optional(prior));
            return;
        }
    }
    materializeNativeCopy(sourcePath, outputPath);
    const auto outputInfo = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1025, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    next->files->push_back(std::make_shared<::app_src_resource_state_::MaterializedResource>(sourcePath, outputPath, sourceInfo->size, sourceInfo->modifiedAt->toEpochNanos(), outputInfo->size, outputInfo->modifiedAt->toEpochNanos()));
}
bool resourceOutputIsCurrent(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>& files, const std::string& outputPath) {
    const auto& _iterable_86 = files;
    for (const auto& file : *_iterable_86) {
        if (file->outputPath == outputPath) {
            return true;
        }
    }
    return false;
}
void synchronizeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory, const std::string& statePath) {
    const auto previous = readResourceState(statePath);
    const auto next = std::make_shared<::app_src_resource_state_::ResourceState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>(std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>{}));
    const auto& _iterable_88 = resources;
    for (const auto& resource : *_iterable_88) {
        const auto destinationRoot = driverOutputPath(outputDirectory, resource->destination);
        const auto outputPath = (::doof_fs::isDirectory(resource->sourcePath) ? destinationRoot : driverOutputPath(destinationRoot, ::app_src_project_::fileName(resource->sourcePath)));
        materializeTrackedResource(resource->sourcePath, outputPath, previous, next);
    }
    const auto prefix = (doof::string_endsWith(outputDirectory, std::string("/")) ? outputDirectory : (outputDirectory + std::string("/")));
    const auto& _iterable_90 = previous->files;
    for (const auto& old : *_iterable_90) {
        if (((resourceOutputIsCurrent(next->files, old->outputPath) || !doof::string_startsWith(old->outputPath, prefix)) || !::doof_fs::exists(old->outputPath)) || ::doof_fs::isDirectory(old->outputPath)) {
            continue;
        }
        [&]() -> void { auto _try_value = ::doof_fs::remove(old->outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1059, std::string("try! failed"));  }();
    }
    ensureOutputDirectory(::app_src_project_::parentPath(statePath));
    const auto temporaryPath = (statePath + std::string(".tmp"));
    [&]() -> void { auto _try_value = ::doof_fs::writeText(temporaryPath, ::app_src_resource_state_::renderResourceState(next)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1063, std::string("try! failed"));  }();
    [&]() -> void { auto _try_value = ::doof_fs::rename(temporaryPath, statePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1064, std::string("try! failed"));  }();
}
void materializeRuntimeHeader(const std::string& outputDirectory) {
    auto sourcePath = ::app_src_project_::environmentValue(std::string("DOOF_RUNTIME_HEADER"));
    const auto runtimeSource = ((sourcePath == std::string("")) ? ::std_::fs::index::readTextResource(std::string("doof_runtime.h")) : ::doof_fs::readText(sourcePath));
    writeTextIfChanged(driverOutputPath(outputDirectory, std::string("doof_runtime.hpp")), [&]() -> std::string { auto _try_value = runtimeSource; if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1074, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
}
doof::Result<std::string, std::string> buildAppleWasmTestRunner(const std::string& buildRoot) {
    const auto runnerDirectory = ::app_src_project_::joinPath(::app_src_project_::joinPath(buildRoot, std::string(".doof-tests")), std::string("apple-wasm-runner"));
    ensureOutputDirectory(runnerDirectory);
    const auto sourcePath = ::app_src_project_::joinPath(runnerDirectory, std::string("doof-wasm-test-runner.swift"));
    const auto runnerPath = ::app_src_project_::joinPath(runnerDirectory, std::string("doof-wasm-test-runner"));
    const auto fingerprintPath = ::app_src_project_::joinPath(runnerDirectory, std::string("source.sha256"));
    auto _binding_value_91 = ::std_::fs::index::readTextResource(std::string("doof_wasm_test_runner_apple.swift"));
    if (doof::is_failure(_binding_value_91)) {
        const auto& source = _binding_value_91;
        return doof::Failure<std::string>{ std::string("Could not read embedded doof_wasm_test_runner_apple.swift") };
    }
    const auto source = doof::success_value(_binding_value_91);
    writeTextIfChanged(sourcePath, source);
    const auto fingerprint = ::std_::crypto::index::sha256HexString(source);
    if (::doof_fs::exists(runnerPath) && ::doof_fs::exists(fingerprintPath)) {
        const auto previousFingerprint = [&]() -> std::string { auto _try_value = ::doof_fs::readText(fingerprintPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1089, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        if (doof::string_trim(previousFingerprint) == fingerprint) {
            return doof::Success<std::string>{ runnerPath };
        }
    }
    const auto plan = ::app_src_wasm_test_runner_::planAppleWasmTestRunnerBuild(sourcePath, runnerPath);
    const auto built = runNativeCommand(plan->command, plan->arguments, runnerDirectory, false, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
    if (built->exitCode != 0) {
        const auto output = ((built->error != std::string("")) ? built->error : doof::string_trim(::doof_blob::NativeBlobReader::constructor(built->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((built->output)->size())))));
        return doof::Failure<std::string>{ (std::string("Could not build the Apple JavaScriptCore Wasm test runner") + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
    [&]() -> void { auto _try_value = ::doof_fs::writeText(fingerprintPath, (fingerprint + std::string("\n"))); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1100, std::string("try! failed"));  }();
    return doof::Success<std::string>{ runnerPath };
}
std::string nativeBuildOutputName(const std::string& projectName, const std::string& nativePlatform) {
    const auto name = doof::string_replaceAll(doof::string_replaceAll(projectName, std::string("/"), std::string("-")), std::string("\\"), std::string("-"));
    if ((nativePlatform == std::string("windows")) && !doof::string_endsWith(doof::string_toLowerCase(name), std::string(".exe"))) {
        return (name + std::string(".exe"));
    }
    return name;
}
void printDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
    const auto displayCount = ((static_cast<int32_t>((diagnostics)->size()) < MAX_PRINTED_DIAGNOSTICS) ? static_cast<int32_t>((diagnostics)->size()) : MAX_PRINTED_DIAGNOSTICS);
    for (int32_t index = 0; index < displayCount; ++index) {
        const auto diagnostic = doof::array_at(diagnostics, index, "src/driver", 1113);
        doof::println(((((((((diagnostic->module + std::string(":")) + doof::to_string(diagnostic->span.start.line)) + std::string(":")) + doof::to_string(diagnostic->span.start.column)) + std::string(": ")) + diagnostic->severity) + std::string(": ")) + diagnostic->message));
    }
    if (static_cast<int32_t>((diagnostics)->size()) > displayCount) {
        doof::println(((std::string("... ") + doof::to_string((static_cast<int32_t>((diagnostics)->size()) - displayCount))) + std::string(" more diagnostics omitted")));
    }
}
void collectTestFiles(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results, bool root) {
    if (!::doof_fs::isDirectory(path)) {
        if (doof::string_endsWith(path, std::string(".do"))) {
            results->push_back(path);
        }
        return;
    }
    if (!root && ::doof_fs::exists(::app_src_project_::joinPath(path, std::string("doof.json")))) {
        return;
    }
    const auto entries = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1130, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
    const auto& _iterable_94 = entries;
    for (const auto& entry : *_iterable_94) {
        const auto entryPath = ::app_src_project_::joinPath(path, entry->name);
        if (entry->kind == ::std_::fs::types::EntryKind::Directory) {
            collectTestFiles(entryPath, results, false);
        } else if ((entry->kind == ::std_::fs::types::EntryKind::File) && doof::string_endsWith(entry->name, std::string(".test.do"))) {
            results->push_back(entryPath);
        }
    }
}
std::shared_ptr<std::vector<std::string>> sortedTestFiles(const std::shared_ptr<std::vector<std::string>>& values) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto last = std::string("");
    for (int32_t count = 0; count < static_cast<int32_t>((values)->size()); ++count) {
        std::optional<std::string> candidate = std::nullopt;
        const auto& _iterable_97 = values;
        for (const auto& value : *_iterable_97) {
            if (((static_cast<int32_t>((result)->size()) == 0) || (value > last)) && (doof::is_null(candidate) || (value < candidate.value()))) {
                (candidate = value);
            }
        }
        if (!doof::is_null(candidate)) {
            result->push_back(candidate.value());
            (last = candidate.value());
        }
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> sortedDiscoveredTests(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>& values) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>(std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>{});
    auto last = std::string("");
    for (int32_t count = 0; count < static_cast<int32_t>((values)->size()); ++count) {
        std::shared_ptr<::app_src_test_runner_::DiscoveredTest> candidate = nullptr;
        const auto& _iterable_100 = values;
        for (const auto& value : *_iterable_100) {
            if (((static_cast<int32_t>((result)->size()) == 0) || (value->id > last)) && (doof::is_null(candidate) || (value->id < candidate->id))) {
                (candidate = value);
            }
        }
        if (!doof::is_null(candidate)) {
            result->push_back(doof::unwrap_optional(candidate));
            (last = candidate->id);
        }
    }
    return result;
}
void mergeCoverageGroup(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& groupModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& groupHits, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& allModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& allHits) {
    for (int32_t groupIndex = 0; groupIndex < static_cast<int32_t>((groupModules)->size()); ++groupIndex) {
        const auto groupModule = doof::array_at(groupModules, groupIndex, "src/driver", 1174);
        const auto diskPath = driverSourceDiskPath(groupModule->modulePath, configuredDriverSourceState->localRoots, configuredDriverSourceState->acquisitions);
        auto targetIndex = -1;
        for (int32_t index = 0; index < static_cast<int32_t>((allModules)->size()); ++index) {
            if (doof::array_at(allModules, index, "src/driver", 1182)->modulePath == diskPath) {
                (targetIndex = index);
            }
        }
        if (targetIndex < 0) {
            std::shared_ptr<std::vector<int32_t>> lines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
            const auto& _iterable_104 = groupModule->instrumentedLines;
            for (const auto& line : *_iterable_104) {
                lines->push_back(line);
            }
            allModules->push_back(std::make_shared<::app_src_emitter_module_::CoverageModuleMetadata>(static_cast<int32_t>((allModules)->size()), diskPath, lines));
            allHits->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
            (targetIndex = (static_cast<int32_t>((allModules)->size()) - 1));
        }
        if (groupIndex < static_cast<int32_t>((groupHits)->size())) {
            const auto& _iterable_106 = doof::array_at(groupHits, groupIndex, "src/driver", 1196);
            for (const auto& line : *_iterable_106) {
                auto found = false;
                const auto& _iterable_108 = doof::array_at(allHits, targetIndex, "src/driver", 1198);
                for (const auto& existing : *_iterable_108) {
                    if (existing == line) {
                        (found = true);
                    }
                }
                if (!found) {
                    doof::array_at(allHits, targetIndex, "src/driver", 1199)->push_back(line);
                }
            }
        }
    }
}
void printCoverageSummary(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report) {
    doof::println(std::string("Coverage summary:"));
    const auto& _iterable_110 = report->files;
    for (const auto& file : *_iterable_110) {
        const auto percent = ((doof::to_string((file->percentTenths / 10)) + std::string(".")) + doof::to_string((file->percentTenths % 10)));
        doof::println(((((((((std::string("  ") + file->path) + std::string(": ")) + doof::to_string(file->covered)) + std::string("/")) + doof::to_string(file->total)) + std::string(" lines (")) + percent) + std::string("%)")));
    }
    const auto overall = ((doof::to_string((report->totalPercentTenths / 10)) + std::string(".")) + doof::to_string((report->totalPercentTenths % 10)));
    doof::println(((((((std::string("Overall: ") + doof::to_string(report->totalCovered)) + std::string("/")) + doof::to_string(report->totalLines)) + std::string(" lines (")) + overall) + std::string("%)")));
}
std::string coverageHtmlPath(const std::string& jsonPath) {
    if (doof::string_endsWith(jsonPath, std::string(".json"))) {
        return (doof::string_substring(jsonPath, 0, (static_cast<int32_t>(jsonPath.size()) - 5)) + std::string(".html"));
    }
    return (jsonPath + std::string(".html"));
}
std::string writeCoverageHtml(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report, const std::string& jsonPath, const std::string& rootDirectory) {
    const auto indexPath = coverageHtmlPath(jsonPath);
    const auto filesDirectory = (doof::string_substring(indexPath, 0, (static_cast<int32_t>(indexPath.size()) - 5)) + std::string("_files"));
    const auto filesDirectoryName = ::app_src_project_::fileName(filesDirectory);
    const auto& _iterable_112 = report->files;
    for (const auto& file : *_iterable_112) {
        const auto relativePage = ::app_src_test_runner_::coverageFileRelativePath(file->path);
        const auto pagePath = ::app_src_project_::joinPath(filesDirectory, relativePage);
        ensureOutputDirectory(::app_src_project_::parentPath(pagePath));
        auto depth = 1;
        for (int32_t index = 0; index < static_cast<int32_t>(relativePage.size()); ++index) {
            if (doof::string_at(relativePage, index, "src/driver", 1229) == U'\u002F') {
                (depth += 1);
            }
        }
        const auto indexHref = (doof::string_repeat(std::string("../"), depth) + ::app_src_project_::fileName(indexPath));
        const auto sourcePath = ::app_src_project_::joinPath(rootDirectory, file->path);
        auto source = std::string("");
        if (::doof_fs::exists(sourcePath)) {
            (source = [&]() -> std::string { auto _try_value = ::doof_fs::readText(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1233, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
        }
        [&]() -> void { auto _try_value = ::doof_fs::writeText(pagePath, ::app_src_test_runner_::renderCoverageFileHtml(file, source, indexHref)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1234, std::string("try! failed"));  }();
    }
    [&]() -> void { auto _try_value = ::doof_fs::writeText(indexPath, ::app_src_test_runner_::renderCoverageHtml(report, filesDirectoryName)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1236, std::string("try! failed"));  }();
    return indexPath;
}
int32_t testRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request) {
    const auto target = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->entry); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1242, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    if (!::doof_fs::exists(target)) {
        doof::println((std::string("error: File not found: ") + target));
        return 1;
    }
    const auto rootDirectory = (::doof_fs::isDirectory(target) ? target : ::app_src_project_::parentPath(target));
    std::shared_ptr<std::vector<std::string>> testFiles = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    collectTestFiles(target, testFiles, true);
    (testFiles = sortedTestFiles(testFiles));
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> discovered = std::make_shared<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>(std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>{});
    const auto& _iterable_115 = testFiles;
    for (const auto& testFile : *_iterable_115) {
        auto _binding_value_116 = ::doof_fs::readText(testFile);
        if (doof::is_failure(_binding_value_116)) {
            const auto& source = _binding_value_116;
            doof::println((std::string("error: Could not read test file: ") + testFile));
            return 1;
        }
        const auto source = doof::success_value(_binding_value_116);
        const auto parser = std::make_shared<::app_src_parser_::Parser>(source, std::make_shared<std::vector<::app_src_lexer_::Token>>(std::vector<::app_src_lexer_::Token>{}), 0, false, false, std::string(""), 0, 0, 0);
        const auto parsed = [&]() -> doof::Result<std::shared_ptr<::app_src_ast_::Program>, std::string> { try { return doof::Success<std::shared_ptr<::app_src_ast_::Program>>{doof::callback<std::shared_ptr<::app_src_ast_::Program>()>([parser]() -> std::shared_ptr<::app_src_ast_::Program> { return parser->parse(); }).call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }();
        auto _binding_value_117 = parsed;
        if (doof::is_failure(_binding_value_117)) {
            const auto failure = doof::failure_error(_binding_value_117);
            if (parser->errorMessage == std::string("")) {
                doof::panic(failure);
            }
            doof::println(::app_src_test_runner_::formatParseFailure(testFile, source, parser->errorLine, parser->errorColumn, parser->errorMessage));
            return 1;
        }
        const auto program = doof::success_value(_binding_value_117);
        const auto discovery = ::app_src_test_runner_::discoverModuleTests(program, testFile, rootDirectory);
        const auto& _iterable_119 = discovery->errors;
        for (const auto& error : *_iterable_119) {
            doof::println(error);
        }
        if (static_cast<int32_t>((discovery->errors)->size()) > 0) {
            return 1;
        }
        const auto& _iterable_121 = discovery->tests;
        for (const auto& test : *_iterable_121) {
            discovered->push_back(test);
        }
    }
    (discovered = sortedDiscoveredTests(discovered));
    const auto selected = ::app_src_test_runner_::filterDiscoveredTests(discovered, request->filter);
    if (static_cast<int32_t>((selected)->size()) == 0) {
        const auto suffix = ((request->filter == std::string("")) ? std::string("") : ((std::string(" matching \"") + request->filter) + std::string("\"")));
        doof::println(((std::string("error: No tests found under ") + target) + suffix));
        return 1;
    }
    if (request->listOnly) {
        const auto& _iterable_123 = selected;
        for (const auto& test : *_iterable_123) {
            doof::println(test->id);
        }
        return 0;
    }
    auto passed = 0;
    auto failed = 0;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> coverageModules = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>{});
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> coverageHits = std::make_shared<std::vector<std::shared_ptr<std::vector<int32_t>>>>(std::vector<std::shared_ptr<std::vector<int32_t>>>{});
    auto appleWasmRunner = std::string("");
    const auto groups = ::app_src_test_runner_::groupTestsForCompilation(selected);
    const auto& _iterable_125 = groups;
    for (const auto& group : *_iterable_125) {
        const auto moduleTests = group->tests;
        const auto testFile = doof::array_at(moduleTests, 0, "src/driver", 1289)->modulePath;
        const auto project = ::app_src_project_::readProjectSpec(testFile, hostPlatform(), request->targetOverride);
        const auto wasmTests = (project->target == std::string("wasm"));
        if (wasmTests && (hostPlatform() != std::string("macos"))) {
            doof::println(std::string("error: doof test --target wasm currently requires macOS and JavaScriptCore"));
            return 1;
        }
        const auto buildRoot = ((request->outputDirectory == std::string("")) ? ::app_src_project_::joinPath(project->rootDirectory, project->buildDirectory) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->outputDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1298, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        const auto coverageSuffix = (request->coverage ? std::string("-coverage") : std::string(""));
        const auto targetSuffix = (wasmTests ? std::string("-wasm") : std::string(""));
        const auto outputDirectory = ::app_src_project_::joinPath(::app_src_project_::joinPath(buildRoot, std::string(".doof-tests")), ((group->outputName + targetSuffix) + coverageSuffix));
        const auto harnessPath = ::app_src_project_::joinPath(outputDirectory, std::string("__doof_tests__.do"));
        ensureOutputDirectory(outputDirectory);
        writeTextIfChanged(harnessPath, ::app_src_test_runner_::generateTestHarness(harnessPath, moduleTests));
        const auto stdlibRoot = ::app_src_project_::environmentValue(std::string("DOOF_STDLIB_ROOT"));
        const auto rootLogicalPrefix = driverRootLogicalPrefix(project->name, project->rootDirectory);
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(rootLogicalPrefix, project->name, std::string(""))});
        auto testExternalTarget = std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(hostPlatform(), std::string(""), std::string(""), std::string(""), 1);
        if (wasmTests) {
            auto _binding_value_126 = externalTargetForRequest(std::string("wasm"), hostPlatform(), std::string(""), std::string(""));
            if (doof::is_failure(_binding_value_126)) {
                const auto error = doof::failure_error(_binding_value_126);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            const auto resolvedTarget = doof::success_value(_binding_value_126);
            (testExternalTarget = resolvedTarget);
        }
        auto _binding_value_127 = sourceLoaderForRequest(harnessPath, stdlibRoot, namespaceMappings, project->manifest, hostPlatform(), testExternalTarget);
        if (doof::is_failure(_binding_value_127)) {
            const auto error = doof::failure_error(_binding_value_127);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        const auto loader = doof::success_value(_binding_value_127);
        const auto result = ::app_src_compiler_::compileWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), driverRootLogicalPath(harnessPath, project->rootDirectory, project->name), loader, namespaceMappings, std::string("executable"), request->coverage, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), std::string(""), false);
        if (static_cast<int32_t>((result->diagnostics)->size()) > 0) {
            printDiagnostics(result->diagnostics);
        }
        if (::app_src_diagnostics_::hasErrorDiagnostics(result->diagnostics)) {
            return 1;
        }
        if (doof::is_null(result->emission)) {
            doof::panic(std::string("test compiler produced no emission"));
        }
        const auto rootManifest = project->manifest;
        auto _binding_value_128 = resolvedDependencyInputs(rootManifest);
        if (doof::is_failure(_binding_value_128)) {
            const auto error = doof::failure_error(_binding_value_128);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        const auto externalInputs = doof::success_value(_binding_value_128);
        auto _binding_value_129 = acquireResolvedExternalInputs(externalInputs, testExternalTarget);
        if (doof::is_failure(_binding_value_129)) {
            const auto error = doof::failure_error(_binding_value_129);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        const auto emission = ::app_src_emitter_project_::planProjectEmission(doof::unwrap_optional(result->emission), projectNativePackages(project->rootDirectory, rootManifest, std::string("")));
        if (request->coverage) {
            emission->nativeBuild->defines->push_back(std::string("DOOF_COVERAGE"));
        }
        materializeProject(outputDirectory, emission);
        materializeRuntimeHeader(outputDirectory);
        const auto binary = ::app_src_project_::joinPath(outputDirectory, (wasmTests ? std::string("doof-tests.wasm") : std::string("doof-tests")));
        doof::println((std::string("BUILD ") + group->outputName));
        const auto buildExitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, binary, emission, ::app_src_native_build_::NativeBuildMode::Debug, hostPlatform(), ::app_src_native_build_driver_::NativeBuildOutputMode::Progress, wasmTests);
        if (buildExitCode != 0) {
            return buildExitCode;
        }
        if (wasmTests && (appleWasmRunner == std::string(""))) {
            auto _binding_value_130 = buildAppleWasmTestRunner(buildRoot);
            if (doof::is_failure(_binding_value_130)) {
                const auto error = doof::failure_error(_binding_value_130);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            const auto builtRunner = doof::success_value(_binding_value_130);
            (appleWasmRunner = builtRunner);
        }
        doof::println(((std::string("Testing ") + doof::to_string(static_cast<int32_t>((moduleTests)->size()))) + ((static_cast<int32_t>((moduleTests)->size()) == 1) ? std::string(" test") : std::string(" tests"))));
        ::doof::print_flushed(::app_src_progress_::renderProgressBar(0, static_cast<int32_t>((moduleTests)->size()), 24));
        std::shared_ptr<std::vector<std::shared_ptr<doof::Actor<TestProcessWorker>>>> testWorkers = std::make_shared<std::vector<std::shared_ptr<doof::Actor<TestProcessWorker>>>>(std::vector<std::shared_ptr<doof::Actor<TestProcessWorker>>>{});
        std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<TestWorkerCompletion>>>> pendingTests = std::make_shared<std::vector<doof::Promise<std::shared_ptr<TestWorkerCompletion>>>>(std::vector<doof::Promise<std::shared_ptr<TestWorkerCompletion>>>{});
        const auto maxTestOutput = (request->coverage ? MAX_COVERAGE_OUTPUT_BYTES : MAX_NATIVE_COMPILER_OUTPUT_BYTES);
        auto nextTestIndex = 0;
        for (int32_t workerIndex = 0; workerIndex < ::app_src_progress_::boundedWorkerCount(static_cast<int32_t>((moduleTests)->size()), 4); ++workerIndex) {
            const auto worker = std::make_shared<doof::Actor<TestProcessWorker>>(TestProcessWorker{(wasmTests ? appleWasmRunner : binary), (wasmTests ? binary : std::string("")), project->rootDirectory, maxTestOutput});
            testWorkers->push_back(worker);
            const auto test = doof::array_at(moduleTests, nextTestIndex, "src/driver", 1374);
            pendingTests->push_back(worker->template call_async<std::shared_ptr<TestWorkerCompletion>>([=](TestProcessWorker& _self) -> std::shared_ptr<TestWorkerCompletion> { return _self.runTest(workerIndex, test->id); }));
            (nextTestIndex += 1);
        }
        auto completedTests = 0;
        std::shared_ptr<std::vector<std::shared_ptr<TestExecutionResult>>> executionResults = std::make_shared<std::vector<std::shared_ptr<TestExecutionResult>>>(std::vector<std::shared_ptr<TestExecutionResult>>{});
        while (static_cast<int32_t>((pendingTests)->size()) > 0) {
            auto _binding_value_132 = doof::promise_take_first_completed(pendingTests);
            if (doof::is_failure(_binding_value_132)) {
                const auto error = doof::failure_error(_binding_value_132);
                const auto& _iterable_134 = testWorkers;
                for (const auto& worker : *_iterable_134) {
                    const auto ignoredWorker = worker->retire();
                }
                doof::println(std::string(""));
                doof::println((std::string("error: test worker failed: ") + error));
                return 1;
            }
            const auto workerResult = doof::success_value(_binding_value_132);
            executionResults->push_back(workerResult->test);
            (completedTests += 1);
            ::doof::print_flushed((std::string("\r") + ::app_src_progress_::renderProgressBar(completedTests, static_cast<int32_t>((moduleTests)->size()), 24)));
            if (nextTestIndex < static_cast<int32_t>((moduleTests)->size())) {
                const auto test = doof::array_at(moduleTests, nextTestIndex, "src/driver", 1391);
                pendingTests->push_back(doof::array_at(testWorkers, workerResult->workerIndex, "src/driver", 1392)->template call_async<std::shared_ptr<TestWorkerCompletion>>([=](TestProcessWorker& _self) -> std::shared_ptr<TestWorkerCompletion> { return _self.runTest(workerResult->workerIndex, test->id); }));
                (nextTestIndex += 1);
            }
        }
        const auto& _iterable_136 = testWorkers;
        for (const auto& worker : *_iterable_136) {
            worker->retire();
        }
        doof::println(std::string(""));
        const auto& _iterable_138 = moduleTests;
        for (const auto& test : *_iterable_138) {
            const auto execution = findTestExecutionResult(executionResults, test->id);
            if (doof::is_null(execution)) {
                doof::panic((std::string("test worker returned no result for ") + test->id));
            }
            const auto testResult = execution->command;
            if (request->coverage) {
                if (testResult->truncated) {
                    doof::println((((std::string("error: coverage output exceeded ") + doof::to_string(MAX_COVERAGE_OUTPUT_BYTES)) + std::string(" bytes for ")) + test->id));
                    return 1;
                }
                const auto output = ::doof_blob::NativeBlobReader::constructor(testResult->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((testResult->output)->size())));
                std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> groupHits = std::make_shared<std::vector<std::shared_ptr<std::vector<int32_t>>>>(std::vector<std::shared_ptr<std::vector<int32_t>>>{});
                const auto& _iterable_140 = result->emission->coverageModules;
                for (const auto& ignored : *_iterable_140) {
                    groupHits->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
                }
                ::app_src_test_runner_::mergeCoverageOutput(output, result->emission->coverageModules, groupHits);
                mergeCoverageGroup(result->emission->coverageModules, groupHits, coverageModules, coverageHits);
                if (testResult->exitCode != 0) {
                    const auto visibleOutput = ::app_src_test_runner_::stripCoverageLines(output);
                    if (visibleOutput != std::string("")) {
                        doof::println(visibleOutput);
                    }
                }
            } else if (testResult->exitCode != 0) {
                const auto ignored = printNativeCommandOutput(testResult, MAX_PRINTED_DIAGNOSTICS);
                if (testResult->truncated) {
                    doof::println(((std::string("... test output capture truncated after ") + doof::to_string(MAX_NATIVE_COMPILER_OUTPUT_BYTES)) + std::string(" bytes")));
                }
            }
            const auto exitCode = testResult->exitCode;
            if (exitCode == 0) {
                (passed = (passed + 1));
            } else {
                (failed = (failed + 1));
                doof::println((std::string("FAIL ") + test->id));
            }
        }
    }
    doof::println(((((std::string("Tests finished: ") + doof::to_string(passed)) + std::string(" passed, ")) + doof::to_string(failed)) + std::string(" failed")));
    if (request->coverage && (static_cast<int32_t>((coverageModules)->size()) > 0)) {
        const auto report = ::app_src_test_runner_::buildCoverageReport(coverageModules, coverageHits, rootDirectory);
        printCoverageSummary(report);
        const auto outputPath = ((request->coverageOutput == std::string("")) ? ::app_src_project_::joinPath(::app_src_project_::joinPath(rootDirectory, std::string("build")), std::string("coverage/doof-test-coverage.json")) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->coverageOutput); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1436, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
        [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath, ::app_src_test_runner_::renderCoverageJson(report)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1438, std::string("try! failed"));  }();
        doof::println((std::string("Coverage report written to ") + outputPath));
        const auto htmlPath = writeCoverageHtml(report, outputPath, rootDirectory);
        doof::println((std::string("Coverage HTML report written to ") + htmlPath));
    }
    return ((failed == 0) ? 0 : 1);
}
std::shared_ptr<TestExecutionResult> findTestExecutionResult(const std::shared_ptr<std::vector<std::shared_ptr<TestExecutionResult>>>& results, const std::string& id) {
    const auto& _iterable_142 = results;
    for (const auto& result : *_iterable_142) {
        if (result->id == id) {
            return result;
        }
    }
    return nullptr;
}
int32_t emitRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request) {
    if ((request->command == std::string("profile")) && (hostPlatform() != std::string("macos"))) {
        doof::println(std::string("error: doof profile is currently supported only on macOS"));
        return 1;
    }
    auto project = ::app_src_project_::readProjectSpec(request->entry, hostPlatform(), request->targetOverride);
    const auto entryError = ::app_src_project_::projectEntryRequestError(project, request->entry);
    if (entryError != std::string("")) {
        doof::println((std::string("error: ") + entryError));
        return 1;
    }
    if ((request->command == std::string("profile")) && ((project->target == std::string("wasm")) || (!doof::is_null(project->iosApp)))) {
        doof::println(std::string("error: doof profile supports native console executables and macOS applications"));
        return 1;
    }
    const auto iosDestination = ((request->command == std::string("package")) ? std::string("device") : request->iosDestination);
    const auto nativePlatform = (doof::is_null(project->iosApp) ? hostPlatform() : (std::string("ios-") + iosDestination));
    if (!doof::is_null(project->iosApp)) {
        (project = ::app_src_project_::readProjectSpec(request->entry, nativePlatform, request->targetOverride));
    }
    const auto iosMinimumVersion = (doof::is_null(project->iosApp) ? std::string("") : project->iosApp->minimumDeploymentTarget);
    auto _binding_value_143 = externalTargetForRequest(project->target, nativePlatform, iosDestination, iosMinimumVersion);
    if (doof::is_failure(_binding_value_143)) {
        const auto error = doof::failure_error(_binding_value_143);
        doof::println((std::string("error: ") + error));
        return 1;
    }
    const auto externalTarget = doof::success_value(_binding_value_143);
    const auto rootManifest = project->manifest;
    const auto entryPath = ::app_src_project_::joinPath(project->rootDirectory, project->entry);
    const auto entry = driverRootLogicalPath(entryPath, project->rootDirectory, project->name);
    const auto stdlibRoot = ::app_src_project_::environmentValue(std::string("DOOF_STDLIB_ROOT"));
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(driverRootLogicalPrefix(project->name, project->rootDirectory), project->name, std::string(""))});
    auto _binding_value_144 = sourceLoaderForRequest(entryPath, stdlibRoot, namespaceMappings, rootManifest, nativePlatform, externalTarget);
    if (doof::is_failure(_binding_value_144)) {
        const auto error = doof::failure_error(_binding_value_144);
        doof::println((std::string("error: ") + error));
        return 1;
    }
    const auto loader = doof::success_value(_binding_value_144);
    if (project->target == std::string("wasm")) {
        auto _binding_value_145 = ensureStdPackageReached(std::string("std/json"));
        if (doof::is_failure(_binding_value_145)) {
            const auto error = doof::failure_error(_binding_value_145);
            doof::println((std::string("error: ") + error));
            return 1;
        }
    }
    const auto entryMode = ((project->target == std::string("wasm")) ? std::string("wasm") : (doof::is_null(project->iosApp) ? std::string("executable") : std::string("ios-app")));
    const auto buildDirectory = ((request->outputDirectory == std::string("")) ? ::app_src_project_::joinPath(project->rootDirectory, project->buildDirectory) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->outputDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1498, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
    const auto outputDirectory = ((request->command == std::string("package")) ? ::app_src_project_::joinPath(buildDirectory, std::string("release")) : ((request->command == std::string("profile")) ? ::app_src_project_::joinPath(buildDirectory, std::string("profile")) : buildDirectory));
    const auto cacheDirectory = ((request->command == std::string("profile")) ? outputDirectory : buildDirectory);
    const auto frontendConfiguration = frontendConfigurationFingerprint(entry, entryMode, project->target, rootManifest, stdlibRoot, nativePlatform, externalTarget);
    const auto checkCachePath = frontendCachePath(cacheDirectory, std::string("check"));
    if ((request->command == std::string("check")) && frontendStateMatches(readFrontendState(checkCachePath), frontendConfiguration, loader)) {
        return 0;
    }
    const auto emissionCachePath = frontendCachePath(cacheDirectory, std::string("emission"));
    const auto previousEmissionState = readFrontendState(emissionCachePath);
    auto reusedFrontend = false;
    auto result = std::make_shared<::app_src_compiler_::Compilation>(nullptr, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto cachedGraph = [&]() -> std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> { if (((((request->command == std::string("emit")) || (request->command == std::string("build"))) || (request->command == std::string("run"))) || (request->command == std::string("profile")))) { return [&]() -> std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> { if (!frontendEmissionCacheSupported(project->target)) { return nullptr; } return [&]() -> std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> { if ((frontendStateMatches(previousEmissionState, frontendConfiguration, loader) && (!doof::is_null(previousEmissionState)))) { return cachedModuleGraph(doof::unwrap_optional(previousEmissionState), outputDirectory); } return nullptr; }(); }(); } return nullptr; }();
    if (!doof::is_null(cachedGraph)) {
        (result = std::make_shared<::app_src_compiler_::Compilation>(doof::unwrap_optional(cachedGraph), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
        (reusedFrontend = true);
    } else {
        (result = ((request->command == std::string("check")) ? ::app_src_compiler_::checkWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), entry, loader, entryMode) : ::app_src_compiler_::compileWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), entry, loader, namespaceMappings, entryMode, false, ((request->command == std::string("package")) ? std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}) : reusableEmissionKeys(previousEmissionState, outputDirectory)), frontendConfiguration, (request->command == std::string("profile")))));
    }
    const auto hasCompilationErrors = ::app_src_diagnostics_::hasErrorDiagnostics(result->diagnostics);
    if ((static_cast<int32_t>((result->diagnostics)->size()) > 0) && ((request->command != std::string("run")) || hasCompilationErrors)) {
        printDiagnostics(result->diagnostics);
    }
    if (hasCompilationErrors) {
        return 1;
    }
    if ((((request->command != std::string("check")) && (request->command != std::string("package"))) && !reusedFrontend) && (static_cast<int32_t>((result->diagnostics)->size()) == 0)) {
        writeFrontendState(checkCachePath, frontendStateForCompilation(result, frontendConfiguration, rootManifest));
    }
    if ((request->command == std::string("package")) && ::app_src_dependency_policy_::hasMutableStdPackageInputs(reachedPackageInputs(rootManifest))) {
        doof::println(std::string("warning: packaging with standard packages overridden by DOOF_STDLIB_ROOT; provenance.json will record them as mutable inputs"));
    }
    auto _binding_value_146 = resolvedDependencyInputs(rootManifest);
    if (doof::is_failure(_binding_value_146)) {
        const auto error = doof::failure_error(_binding_value_146);
        doof::println((std::string("error: ") + error));
        return 1;
    }
    const auto externalInputs = doof::success_value(_binding_value_146);
    if (request->command == std::string("check")) {
        if (static_cast<int32_t>((result->diagnostics)->size()) == 0) {
            writeFrontendState(checkCachePath, frontendStateForCompilation(result, frontendConfiguration, rootManifest));
        }
        return 0;
    }
    if (doof::is_null(result->emission)) {
        doof::panic(std::string("compiler produced no emission"));
    }
    auto _binding_value_147 = acquireResolvedExternalInputs(externalInputs, externalTarget);
    if (doof::is_failure(_binding_value_147)) {
        const auto error = doof::failure_error(_binding_value_147);
        doof::println((std::string("error: ") + error));
        return 1;
    }
    const auto emission = ::app_src_emitter_project_::planProjectEmission(doof::unwrap_optional(result->emission), projectNativePackages(project->rootDirectory, rootManifest, stdlibRoot));
    materializeProject(outputDirectory, emission);
    materializeRuntimeHeader(outputDirectory);
    writeTextIfChanged(driverOutputPath(outputDirectory, std::string("provenance.json")), ::app_src_provenance_::renderBuildProvenance(reachedPackageInputs(rootManifest), externalInputs, emission->nativeBuild, configuredDriverSourceState->stdCatalog));
    if ((!reusedFrontend && (request->command != std::string("package"))) && frontendEmissionCacheSupported(project->target)) {
        const auto nextEmissionState = frontendStateForCompilation(result, frontendConfiguration, rootManifest);
        removeStaleFrontendOutputs(previousEmissionState, nextEmissionState, outputDirectory);
        writeFrontendState(emissionCachePath, nextEmissionState);
    }
    if (!doof::is_null(project->iosApp)) {
        auto _binding_value_148 = ::app_src_ios_app_driver_::configureIOSNativeBuild(outputDirectory, doof::unwrap_optional(project->iosApp), iosDestination, emission->nativeBuild);
        if (doof::is_failure(_binding_value_148)) {
            const auto error = doof::failure_error(_binding_value_148);
            doof::println((std::string("error: ") + error));
            return 1;
        }
    }
    if (((request->command == std::string("build")) || (request->command == std::string("run"))) || (request->command == std::string("profile"))) {
        if ((request->command == std::string("run")) && (project->target == std::string("wasm"))) {
            doof::println(std::string("error: doof run is not supported for --target wasm; instantiate the generated .wasm from your host runtime"));
            return 1;
        }
        const auto executableName = ((project->target == std::string("wasm")) ? (nativeBuildOutputName(project->name, std::string("")) + std::string(".wasm")) : ((!doof::is_null(project->macosApp)) ? project->macosApp->executableName : ((!doof::is_null(project->iosApp)) ? project->iosApp->executableName : nativeBuildOutputName(project->name, nativePlatform))));
        const auto outputPath = driverOutputPath(outputDirectory, executableName);
        if (doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) {
            synchronizeExecutableResources(project->resources, outputDirectory, frontendCachePath(cacheDirectory, std::string("resources")));
        }
        const auto exitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, outputPath, emission, ((request->command == std::string("profile")) ? ::app_src_native_build_::NativeBuildMode::Profile : ::app_src_native_build_::NativeBuildMode::Debug), hostPlatform(), nativeBuildOutputModeForCommand(request->command), false);
        if (exitCode != 0) {
            return exitCode;
        }
        if (!doof::is_null(project->iosApp)) {
            auto _binding_value_149 = ::app_src_ios_app_driver_::assembleIOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->iosApp), iosDestination);
            if (doof::is_failure(_binding_value_149)) {
                const auto error = doof::failure_error(_binding_value_149);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_149);
            if (request->command == std::string("build")) {
                return 0;
            }
            if (iosDestination == std::string("device")) {
                const auto signingWorkDirectory = driverOutputPath(outputDirectory, std::string(".doof-ios-signing-resolution"));
                auto _binding_value_150 = ::app_src_ios_device_::resolveIOSDeviceSigningOptions(project->iosApp->bundleId, request->iosSignIdentity, request->iosProvisioningProfile, signingWorkDirectory, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                if (doof::is_failure(_binding_value_150)) {
                    const auto error = doof::failure_error(_binding_value_150);
                    doof::println((std::string("error: ") + error));
                    return 1;
                }
                const auto signing = doof::success_value(_binding_value_150);
                auto _binding_value_151 = ::app_src_ios_device_::signIOSDeviceApp(appPath, project->iosApp->bundleId, signing, driverOutputPath(outputDirectory, std::string(".doof-ios-sign")));
                if (doof::is_failure(_binding_value_151)) {
                    const auto error = doof::failure_error(_binding_value_151);
                    doof::println((std::string("error: ") + error));
                    return 1;
                }
                auto _binding_value_152 = ::app_src_ios_device_::resolveIOSDeviceIdentifier(request->iosDevice, driverOutputPath(outputDirectory, std::string(".doof-ios-device-discovery")));
                if (doof::is_failure(_binding_value_152)) {
                    const auto error = doof::failure_error(_binding_value_152);
                    doof::println((std::string("error: ") + error));
                    return 1;
                }
                const auto deviceIdentifier = doof::success_value(_binding_value_152);
                const auto installPlan = ::app_src_run_command_::planIOSDeviceInstall(appPath, deviceIdentifier, project->rootDirectory);
                const auto installResult = runNativeCommand(installPlan->command, installPlan->arguments, installPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
                if (installResult->error != std::string("")) {
                    doof::println((std::string("error: ") + installResult->error));
                }
                if (installResult->exitCode != 0) {
                    return installResult->exitCode;
                }
                const auto launchPlan = ::app_src_run_command_::planIOSDeviceLaunch(project->iosApp->bundleId, deviceIdentifier, project->rootDirectory);
                const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
                if (launchResult->error != std::string("")) {
                    doof::println((std::string("error: ") + launchResult->error));
                }
                return launchResult->exitCode;
            }
            const auto installPlan = ::app_src_run_command_::planIOSSimulatorInstall(appPath, project->rootDirectory);
            const auto installResult = runNativeCommand(installPlan->command, installPlan->arguments, installPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
            if (installResult->error != std::string("")) {
                doof::println((std::string("error: ") + installResult->error));
            }
            if (installResult->exitCode != 0) {
                return installResult->exitCode;
            }
            const auto launchPlan = ::app_src_run_command_::planIOSSimulatorLaunch(project->iosApp->bundleId, project->rootDirectory);
            const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
            if (launchResult->error != std::string("")) {
                doof::println((std::string("error: ") + launchResult->error));
            }
            return launchResult->exitCode;
        }
        if (!doof::is_null(project->macosApp)) {
            auto _binding_value_153 = ::app_src_macos_app_driver_::assembleMacOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->macosApp), emission->nativeBuild->libraryPaths);
            if (doof::is_failure(_binding_value_153)) {
                const auto error = doof::failure_error(_binding_value_153);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_153);
            if (request->command == std::string("build")) {
                return 0;
            }
            if (request->command == std::string("profile")) {
                return runProfileTarget(request, appPath, outputPath, (appPath + std::string(".dSYM")), project->rootDirectory, buildDirectory, executableName, false);
            }
            const auto launchPlan = ::app_src_run_command_::planMacOSAppRun(appPath, project->rootDirectory);
            const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
            if (launchResult->error != std::string("")) {
                doof::println((std::string("error: ") + launchResult->error));
            }
            return launchResult->exitCode;
        }
        if (request->command == std::string("build")) {
            return 0;
        }
        if (request->command == std::string("profile")) {
            return runProfileTarget(request, outputPath, outputPath, (outputPath + std::string(".dSYM")), project->rootDirectory, buildDirectory, executableName, true);
        }
        const auto runPlan = ::app_src_run_command_::planNativeProgramRun(outputPath, request->programArguments, project->rootDirectory);
        const auto runResult = runNativeCommand(runPlan->command, runPlan->arguments, runPlan->directory, true, ::std_::os::index::ProcessGroupMode::Inherited, 262144LL);
        if (runResult->error != std::string("")) {
            doof::println((std::string("error: ") + runResult->error));
        }
        return runResult->exitCode;
    }
    if (request->command == std::string("package")) {
        if (doof::is_null(project->packageConfig)) {
            doof::panic(std::string("project package settings were not resolved"));
        }
        const auto distDirectory = ((request->distDirectory != std::string("")) ? [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->distDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1682, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }() : project->packageConfig->distDirectory);
        ensureOutputDirectory(distDirectory);
        const auto executableName = ((project->target == std::string("wasm")) ? (nativeBuildOutputName(project->name, std::string("")) + std::string(".wasm")) : ((!doof::is_null(project->macosApp)) ? project->macosApp->executableName : ((!doof::is_null(project->iosApp)) ? project->iosApp->executableName : nativeBuildOutputName(project->name, nativePlatform))));
        const auto outputPath = ((doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) ? driverOutputPath(distDirectory, executableName) : driverOutputPath(outputDirectory, executableName));
        const auto exitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, outputPath, emission, ::app_src_native_build_::NativeBuildMode::Release, hostPlatform(), ::app_src_native_build_driver_::NativeBuildOutputMode::Progress, false);
        if (exitCode != 0) {
            return exitCode;
        }
        if (doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) {
            materializeExecutableResources(project->resources, distDirectory);
            return 0;
        }
        if (!doof::is_null(project->iosApp)) {
            auto _binding_value_154 = ::app_src_ios_app_driver_::assembleIOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->iosApp), iosDestination);
            if (doof::is_failure(_binding_value_154)) {
                const auto error = doof::failure_error(_binding_value_154);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_154);
            if (doof::is_null(project->iosPackageConfig)) {
                doof::panic(std::string("iOS package settings were not resolved"));
            }
            const auto iosConfig = doof::unwrap_optional(project->iosPackageConfig);
            const auto environmentIdentity = ::app_src_project_::environmentValue(std::string("DOOF_IOS_SIGN_IDENTITY"));
            if (environmentIdentity != std::string("")) {
                (iosConfig->identity = environmentIdentity);
            }
            if (request->iosSignIdentity != std::string("")) {
                (iosConfig->identity = request->iosSignIdentity);
            }
            const auto environmentProfile = ::app_src_project_::environmentValue(std::string("DOOF_IOS_PROVISIONING_PROFILE"));
            if (environmentProfile != std::string("")) {
                (iosConfig->provisioningProfilePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(environmentProfile); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1707, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
            }
            if (request->iosProvisioningProfile != std::string("")) {
                (iosConfig->provisioningProfilePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->iosProvisioningProfile); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1708, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
            }
            const auto archivePath = driverOutputPath(distDirectory, ::app_src_ios_app_::iosPackageArchiveName(project->iosApp->executableName, project->iosApp->version));
            auto _binding_value_155 = ::app_src_ios_app_driver_::signAndArchiveIOSApp(appPath, archivePath, project->iosApp->bundleId, iosConfig, outputDirectory);
            if (doof::is_failure(_binding_value_155)) {
                const auto error = doof::failure_error(_binding_value_155);
                doof::println((std::string("error: ") + error));
                return 1;
            }
            doof::println((std::string("Package: ") + archivePath));
            return 0;
        }
        auto _binding_value_156 = ::app_src_macos_app_driver_::assembleMacOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->macosApp), emission->nativeBuild->libraryPaths);
        if (doof::is_failure(_binding_value_156)) {
            const auto error = doof::failure_error(_binding_value_156);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        const auto appPath = doof::success_value(_binding_value_156);
        const auto packageConfig = doof::unwrap_optional(project->packageConfig);
        if (request->macosSigning != std::string("")) {
            (packageConfig->signing = request->macosSigning);
        }
        const auto environmentIdentity = ::app_src_project_::environmentValue(std::string("DOOF_MACOS_SIGN_IDENTITY"));
        if (environmentIdentity != std::string("")) {
            (packageConfig->identity = environmentIdentity);
        }
        if (request->macosSignIdentity != std::string("")) {
            (packageConfig->identity = request->macosSignIdentity);
        }
        if (request->macosSandbox) {
            (packageConfig->sandbox = true);
        }
        if (request->macosEntitlements != std::string("")) {
            (packageConfig->entitlementsPath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->macosEntitlements); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1727, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        }
        const auto archivePath = driverOutputPath(distDirectory, ::app_src_macos_app_::macOSPackageArchiveName(project->macosApp->executableName, project->macosApp->version));
        auto _binding_value_157 = ::app_src_macos_app_driver_::signAndArchiveMacOSApp(appPath, archivePath, packageConfig, outputDirectory);
        if (doof::is_failure(_binding_value_157)) {
            const auto error = doof::failure_error(_binding_value_157);
            doof::println((std::string("error: ") + error));
            return 1;
        }
        doof::println((std::string("Package: ") + archivePath));
        return 0;
    }
    return 0;
}
int32_t doof_main(const std::shared_ptr<std::vector<std::string>>& args) {
    const auto parsed = ::app_src_cli_::parseCli(args);
    if (parsed->help) {
        doof::println(::app_src_cli_::cliUsage());
        return 0;
    }
    if (parsed->error != std::string("")) {
        doof::println((std::string("error: ") + parsed->error));
        doof::println(::app_src_cli_::cliUsage());
        return 2;
    }
    if (parsed->request->command == std::string("test")) {
        return testRequest(doof::unwrap_optional(parsed->request));
    }
    return emitRequest(doof::unwrap_optional(parsed->request));
}

void __doof_initialize_module() {
        configuredDriverSourceState = std::make_shared<DriverSourceState>(std::make_shared<std::vector<std::shared_ptr<DriverSourceRoot>>>(std::vector<std::shared_ptr<DriverSourceRoot>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>(std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>{}), std::make_shared<std::vector<std::shared_ptr<DriverAcquiredSource>>>(std::vector<std::shared_ptr<DriverAcquiredSource>>{}), std::make_shared<std::vector<std::shared_ptr<DriverReachedPackage>>>(std::vector<std::shared_ptr<DriverReachedPackage>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), std::string(""), std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(std::string(""), std::string(""), std::string(""), std::string(""), 1), std::make_shared<::app_src_package_manifest_::PackageManifest>(std::string(""), std::string("1.0"), std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<::app_src_package_manifest_::DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::string(""), nullptr, nullptr, nullptr, nullptr), std::make_shared<::app_src_std_catalog_::StdCatalog>(1, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_std_catalog_::StdCatalogPackage>>>(std::vector<std::shared_ptr<::app_src_std_catalog_::StdCatalogPackage>>{})), std::string(""));
}
void printFlushed(const std::string& value) {
    ::doof::print_flushed(value);
}
}

int main(int argc, char** argv) { try { auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ::app_src_analyzer_::__doof_initialize_module(); ::app_src_emitter_names_::__doof_initialize_module(); ::std_::time::duration::__doof_initialize_module(); ::std_::time::temporal::__doof_initialize_module(); ::app_src_external_dependency_::__doof_initialize_module(); ::app_src_package_acquisition_::__doof_initialize_module(); ::app_src_driver_::__doof_initialize_module(); std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); return app_src_driver_::doof_main(std::make_shared<std::vector<std::string>>(std::move(args))); } catch (const doof::Panic& _panic) { std::cerr << "panic: " << _panic.what() << std::endl; std::abort(); } catch (const std::exception& error) { std::cerr << "error: " << error.what() << std::endl; return 1; } }
