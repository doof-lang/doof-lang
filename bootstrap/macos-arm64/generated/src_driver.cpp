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
using namespace ::std_::blob::index;
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
int32_t MAX_PRINTED_DIAGNOSTICS = 20;
int64_t MAX_NATIVE_COMPILER_OUTPUT_BYTES = 262144LL;
int64_t MAX_COVERAGE_OUTPUT_BYTES = 16777216LL;
#line 70 "/src/driver.do"
::app_src_native_build_driver_::NativeBuildOutputMode nativeBuildOutputModeForCommand(const std::string& command) {
#line 71 "/src/driver.do"
    return ((command == std::string("run")) ? ::app_src_native_build_driver_::NativeBuildOutputMode::Silent : ::app_src_native_build_driver_::NativeBuildOutputMode::Progress);
}
#line 74 "/src/driver.do"
int32_t runProfileTarget(const std::shared_ptr<::app_src_cli_::CliRequest>& request, const std::string& targetPath, const std::string& binaryPath, const std::string& symbolsPath, const std::string& packageRoot, const std::string& buildDirectory, const std::string& traceName, bool consoleTarget) {
#line 84 "/src/driver.do"
    const auto symbolsPlan = ::app_src_profile_command_::planProfileSymbols(binaryPath, symbolsPath, packageRoot);
#line 85 "/src/driver.do"
    const auto symbolsResult = runNativeCommand(symbolsPlan->command, symbolsPlan->arguments, symbolsPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
#line 86 "/src/driver.do"
    if (symbolsResult->error != std::string("")) {
#line 86 "/src/driver.do"
        doof::println((std::string("error: ") + symbolsResult->error));
    }
#line 87 "/src/driver.do"
    if (symbolsResult->exitCode != 0) {
#line 88 "/src/driver.do"
        doof::println((std::string("error: could not create profiling symbols at ") + symbolsPath));
#line 89 "/src/driver.do"
        return symbolsResult->exitCode;
    }
#line 91 "/src/driver.do"
    const auto tracePath = ((request->traceOutput == std::string("")) ? ::app_src_project_::joinPath(::app_src_project_::joinPath(buildDirectory, std::string("profiles")), (((traceName + std::string("-")) + doof::to_string(::std_::time::temporal::Instant::now()->toEpochMillis())) + std::string(".trace"))) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->traceOutput); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 93, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
#line 94 "/src/driver.do"
    if (::doof_fs::exists(tracePath)) {
#line 95 "/src/driver.do"
        doof::println((std::string("error: profile trace already exists: ") + tracePath));
#line 96 "/src/driver.do"
        return 1;
    }
#line 98 "/src/driver.do"
    ensureOutputDirectory(::app_src_project_::parentPath(tracePath));
#line 99 "/src/driver.do"
    const auto plan = ::app_src_profile_command_::planProfileCapture(targetPath, request->programArguments, packageRoot, tracePath, request->profileTimeLimit, consoleTarget);
#line 103 "/src/driver.do"
    const auto result = runNativeCommand(plan->command, plan->arguments, plan->directory, true, ::std_::os::index::ProcessGroupMode::Inherited, 262144LL);
#line 104 "/src/driver.do"
    if (!::doof_fs::exists(tracePath)) {
#line 105 "/src/driver.do"
        if (result->error != std::string("")) {
#line 105 "/src/driver.do"
            doof::println((std::string("error: ") + result->error));
        }
#line 106 "/src/driver.do"
        doof::println((std::string("error: profiling did not produce a trace at ") + tracePath));
#line 107 "/src/driver.do"
        return 1;
    }
#line 109 "/src/driver.do"
    if (!request->profileNoOpen) {
#line 110 "/src/driver.do"
        const auto openPlan = ::app_src_profile_command_::planProfileOpen(tracePath, packageRoot);
#line 111 "/src/driver.do"
        const auto opened = runNativeCommand(openPlan->command, openPlan->arguments, openPlan->directory, false, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
#line 112 "/src/driver.do"
        if (opened->exitCode != 0) {
#line 113 "/src/driver.do"
            doof::println(((std::string("error: profile trace was saved at ") + tracePath) + std::string(" but could not be opened")));
#line 114 "/src/driver.do"
            return 1;
        }
    }
#line 117 "/src/driver.do"
    return 0;
}
#line 120 "/src/driver.do"
std::string hostPlatform() {
#line 121 "/src/driver.do"
    const auto value = ::std_::os::index::platform();
#line 122 "/src/driver.do"
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}

#line 132 "/src/driver.do"
std::shared_ptr<NativeCommandResult> runNativeCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::optional<std::string>& directory, bool inheritOutput, ::std_::os::index::ProcessGroupMode processGroupMode, int64_t maxOutputBytes) {
#line 141 "/src/driver.do"
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(directory, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, inheritOutput, processGroupMode, maxOutputBytes, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
#line 149 "/src/driver.do"
        return std::make_shared<NativeCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error, false);
    }
    const auto executed = doof::success_value(_binding_value_1);
#line 151 "/src/driver.do"
    std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
#line 152 "/src/driver.do"
    if (!inheritOutput) {
#line 152 "/src/driver.do"
        (output = executed->stdout_);
    }
#line 153 "/src/driver.do"
    return std::make_shared<NativeCommandResult>(executed->exitCode, output, std::string(""), executed->stdoutTruncated);
}
#line 160 "/src/driver.do"
int32_t printNativeCommandOutput(const std::shared_ptr<NativeCommandResult>& result, int32_t remainingLines) {
#line 161 "/src/driver.do"
    auto remaining = remainingLines;
#line 162 "/src/driver.do"
    const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
#line 165 "/src/driver.do"
    const auto& _iterable_3 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_3) {
#line 166 "/src/driver.do"
        if (line == std::string("")) {
#line 166 "/src/driver.do"
            continue;
        }
#line 167 "/src/driver.do"
        if (remaining <= 0) {
#line 167 "/src/driver.do"
            return 0;
        }
#line 168 "/src/driver.do"
        doof::println(line);
#line 169 "/src/driver.do"
        (remaining -= 1);
    }
#line 171 "/src/driver.do"
    return remaining;
}
#line 174 "/src/driver.do"
std::string driverWithExtension(const std::string& path) {
#line 175 "/src/driver.do"
    if (doof::string_endsWith(path, std::string(".do"))) {
#line 175 "/src/driver.do"
        return path;
    }
#line 176 "/src/driver.do"
    return (path + std::string(".do"));
}
#line 179 "/src/driver.do"
std::string driverLogicalPath(const std::string& path) {
#line 180 "/src/driver.do"
    const auto withExtension = driverWithExtension(path);
#line 181 "/src/driver.do"
    const auto sourceSuffix = driverSourceSuffix(withExtension);
#line 182 "/src/driver.do"
    if (sourceSuffix != withExtension) {
#line 182 "/src/driver.do"
        return sourceSuffix;
    }
#line 183 "/src/driver.do"
    if (doof::string_startsWith(withExtension, std::string("/"))) {
#line 184 "/src/driver.do"
        return withExtension;
    }
#line 186 "/src/driver.do"
    return (std::string("/") + withExtension);
}
#line 189 "/src/driver.do"
std::string driverSourceSuffix(const std::string& path) {
#line 190 "/src/driver.do"
    const auto marker = std::string("/src/");
#line 191 "/src/driver.do"
    auto index = 0;
#line 192 "/src/driver.do"
    while ((index + static_cast<int32_t>(marker.size())) <= static_cast<int32_t>(path.size())) {
#line 193 "/src/driver.do"
        if (doof::string_substring(path, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
#line 194 "/src/driver.do"
            return doof::string_substring(path, index, static_cast<int32_t>(path.size()));
        }
#line 196 "/src/driver.do"
        (index = (index + 1));
    }
#line 198 "/src/driver.do"
    return path;
}
#line 201 "/src/driver.do"
std::string driverOutputPath(const std::string& directory, const std::string& name) {
#line 202 "/src/driver.do"
    if (doof::string_endsWith(directory, std::string("/"))) {
#line 202 "/src/driver.do"
        return (directory + name);
    }
#line 203 "/src/driver.do"
    return ((directory + std::string("/")) + name);
}




std::shared_ptr<DriverSourceState> configuredDriverSourceState;
#line 264 "/src/driver.do"
std::string driverSourceDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions) {
#line 269 "/src/driver.do"
    const auto& _iterable_5 = localRoots;
    for (const auto& root : *_iterable_5) {
#line 270 "/src/driver.do"
        if (logicalPath == root->logicalPrefix) {
#line 270 "/src/driver.do"
            return root->diskRoot;
        }
#line 271 "/src/driver.do"
        const auto prefix = (root->logicalPrefix + std::string("/"));
#line 272 "/src/driver.do"
        if (doof::string_startsWith(logicalPath, prefix)) {
#line 273 "/src/driver.do"
            return ::app_src_project_::joinPath(root->diskRoot, doof::string_substring(logicalPath, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(logicalPath.size())));
        }
    }
#line 276 "/src/driver.do"
    const auto acquiredPath = ::app_src_module_acquisition_::acquiredModuleDiskPath(logicalPath, acquisitions);
#line 277 "/src/driver.do"
    if (!doof::is_null(acquiredPath)) {
#line 277 "/src/driver.do"
        return acquiredPath.value();
    }
#line 278 "/src/driver.do"
    return logicalPath;
}
#line 281 "/src/driver.do"
doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> loadDriverSource(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions) {
#line 286 "/src/driver.do"
    const auto diskPath = driverSourceDiskPath(logicalPath, localRoots, acquisitions);
#line 287 "/src/driver.do"
    if (!::doof_fs::exists(diskPath)) {
#line 287 "/src/driver.do"
        return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ nullptr };
    }
#line 288 "/src/driver.do"
    auto _binding_value_6 = ::doof_fs::readText(diskPath);
    if (doof::is_failure(_binding_value_6)) {
        const auto& source = _binding_value_6;
#line 289 "/src/driver.do"
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(logicalPath, ([&]() -> std::string { std::string _interpolation = "Could not read source file "; _interpolation += doof::to_string(diskPath); _interpolation += ""; return _interpolation; }())) };
    }
    const auto source = doof::success_value(_binding_value_6);
#line 291 "/src/driver.do"
    return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ std::make_shared<::app_src_semantic_::SourceFile>(logicalPath, source, diskPath) };
}
#line 294 "/src/driver.do"
doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> configuredDriverSource(const std::string& logicalPath) {
#line 295 "/src/driver.do"
    if (doof::string_startsWith(logicalPath, std::string("/std/"))) {
#line 296 "/src/driver.do"
        auto _binding_value_7 = ensureStdPackageAcquisition(logicalPath);
        if (doof::is_failure(_binding_value_7)) {
            const auto error = doof::failure_error(_binding_value_7);
#line 297 "/src/driver.do"
            return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(logicalPath, error) };
        }
    }
#line 300 "/src/driver.do"
    auto _try_value_8 = loadDriverSource(logicalPath, configuredDriverSourceState->localRoots, configuredDriverSourceState->acquisitions);
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{doof::variant_promote<std::shared_ptr<::app_src_semantic_::Diagnostic>>(doof::failure_error(_try_value_8))};
    const auto source = doof::success_value(_try_value_8);
#line 305 "/src/driver.do"
    if (!doof::is_null(source)) {
#line 306 "/src/driver.do"
        const auto package = acquiredPackageForLoadedSource(logicalPath, configuredDriverSourceState);
#line 307 "/src/driver.do"
        if (!doof::is_null(package)) {
#line 307 "/src/driver.do"
            auto _try_value_9 = registerReachedPackage(doof::unwrap_optional(package));
            if (doof::is_failure(_try_value_9)) return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{doof::variant_promote<std::shared_ptr<::app_src_semantic_::Diagnostic>>(doof::failure_error(_try_value_9))};
        }
    }
#line 309 "/src/driver.do"
    return doof::Success<std::shared_ptr<::app_src_semantic_::SourceFile>>{ source };
}
#line 312 "/src/driver.do"
std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquiredPackageForLoadedSource(const std::string& logicalPath, const std::shared_ptr<DriverSourceState>& state) {
#line 313 "/src/driver.do"
    const auto& _iterable_11 = state->localRoots;
    for (const auto& root : *_iterable_11) {
#line 314 "/src/driver.do"
        if ((logicalPath == root->logicalPrefix) || doof::string_startsWith(logicalPath, (root->logicalPrefix + std::string("/")))) {
#line 314 "/src/driver.do"
            return nullptr;
        }
    }
#line 316 "/src/driver.do"
    return ::app_src_module_acquisition_::acquiredPackageForModule(logicalPath, state->acquisitions);
}
#line 320 "/src/driver.do"
doof::Result<std::shared_ptr<::app_src_package_manifest_::PackageManifest>, std::string> parseDependencyManifestForTarget(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& nativePlatform, const std::string& rootTarget) {
#line 330 "/src/driver.do"
    const auto dependencyTarget = ((rootTarget == std::string("wasm")) ? std::string("wasm") : std::string(""));
#line 331 "/src/driver.do"
    return ::app_src_package_manifest_::parsePackageManifest(source, manifestPath, rootDirectory, nativePlatform, dependencyTarget);
}
#line 334 "/src/driver.do"
doof::Result<void, std::shared_ptr<::app_src_semantic_::Diagnostic>> registerReachedPackage(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition) {
#line 335 "/src/driver.do"
    const auto& _iterable_13 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_13) {
#line 336 "/src/driver.do"
        if ((reached->acquisition->logicalPrefix == acquisition->logicalPrefix) && (reached->acquisition->diskRoot == acquisition->diskRoot)) {
#line 337 "/src/driver.do"
            return doof::Success<void>{};
        }
    }
#line 341 "/src/driver.do"
    const auto manifestPath = ::app_src_module_acquisition_::acquiredManifestPath(acquisition);
#line 342 "/src/driver.do"
    auto _binding_value_14 = ::doof_fs::readText(manifestPath);
    if (doof::is_failure(_binding_value_14)) {
        const auto& manifestSource = _binding_value_14;
#line 343 "/src/driver.do"
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, ([&]() -> std::string { std::string _interpolation = "Could not read doof.json for acquired package "; _interpolation += doof::to_string(acquisition->logicalPrefix); _interpolation += " at "; _interpolation += doof::to_string(manifestPath); _interpolation += ""; return _interpolation; }())) };
    }
    const auto manifestSource = doof::success_value(_binding_value_14);
#line 348 "/src/driver.do"
    auto _binding_value_15 = parseDependencyManifestForTarget(manifestSource, manifestPath, acquisition->diskRoot, configuredDriverSourceState->nativePlatform, configuredDriverSourceState->rootManifest->target);
    if (doof::is_failure(_binding_value_15)) {
        const auto error = doof::failure_error(_binding_value_15);
#line 355 "/src/driver.do"
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, error) };
    }
    const auto manifest = doof::success_value(_binding_value_15);
#line 357 "/src/driver.do"
    if ((static_cast<int32_t>((manifest->packageResolutions)->size()) > 0) || (static_cast<int32_t>((manifest->externalResolutions)->size()) > 0)) {
#line 358 "/src/driver.do"
        return doof::Failure<std::shared_ptr<::app_src_semantic_::Diagnostic>>{ driverDiagnostic(manifestPath, std::string("resolutions are only allowed in the root doof.json")) };
    }
#line 360 "/src/driver.do"
    const auto source = acquiredSourceFor(acquisition);
#line 361 "/src/driver.do"
    configuredDriverSourceState->reachedPackages->push_back(std::make_shared<DriverReachedPackage>(acquisition, manifest, (doof::is_null(source) ? std::string("") : source->introducedBy), (doof::is_null(source) ? std::string("local") : source->sourceKind), (doof::is_null(source) ? std::string("") : source->sourceUrl), (doof::is_null(source) ? std::string("") : source->sourceRef), (doof::is_null(source) ? std::string("") : source->sourceCommit), (doof::is_null(source) ? std::string("") : source->requestedUrl), (doof::is_null(source) ? std::string("") : source->requestedRef), (doof::is_null(source) ? std::string("") : source->requestedCommit), (doof::is_null(source) ? true : source->mutable_)));
#line 373 "/src/driver.do"
    configuredDriverSourceState->namespaceMappings->push_back(std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(acquisition->logicalPrefix, manifest->name, driverPackageOutputRoot(acquisition->logicalPrefix)));
#line 378 "/src/driver.do"
    return doof::Success<void>{};
}
#line 381 "/src/driver.do"
std::shared_ptr<DriverAcquiredSource> acquiredSourceFor(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition) {
#line 382 "/src/driver.do"
    const auto& _iterable_17 = configuredDriverSourceState->acquiredSources;
    for (const auto& source : *_iterable_17) {
#line 383 "/src/driver.do"
        if ((source->acquisition->logicalPrefix == acquisition->logicalPrefix) && (source->acquisition->diskRoot == acquisition->diskRoot)) {
#line 384 "/src/driver.do"
            return source;
        }
    }
#line 387 "/src/driver.do"
    return nullptr;
}
#line 390 "/src/driver.do"
doof::Result<void, std::string> ensureStdPackageAcquisition(const std::string& logicalPath) {
#line 391 "/src/driver.do"
    if (!doof::is_null(::app_src_module_acquisition_::acquiredModuleDiskPath(logicalPath, configuredDriverSourceState->acquisitions))) {
#line 391 "/src/driver.do"
        return doof::Success<void>{};
    }
#line 392 "/src/driver.do"
    const auto remainder = doof::string_substring(logicalPath, 5, static_cast<int32_t>(logicalPath.size()));
#line 393 "/src/driver.do"
    const auto slash = doof::string_indexOf(remainder, std::string("/"));
#line 394 "/src/driver.do"
    const auto shortName = ((slash < 0) ? remainder : doof::string_substring(remainder, 0, slash));
#line 395 "/src/driver.do"
    const auto packageName = (std::string("std/") + shortName);
#line 396 "/src/driver.do"
    const auto package = ::app_src_std_catalog_::stdCatalogPackage(configuredDriverSourceState->stdCatalog, packageName);
#line 397 "/src/driver.do"
    if (doof::is_null(package)) {
#line 397 "/src/driver.do"
        return doof::Failure<std::string>{ (std::string("Unknown standard package ") + packageName) };
    }
#line 398 "/src/driver.do"
    auto _binding_value_18 = ::app_src_package_acquisition_::acquireExactGitPackage(std::make_shared<::app_src_package_acquisition_::ExactPackageSource>(package->name, package->name, package->url, package->ref, package->commit), configuredDriverSourceState->packageAcquisitionRoot);
    if (doof::is_failure(_binding_value_18)) {
        const auto error = doof::failure_error(_binding_value_18);
#line 401 "/src/driver.do"
        return doof::Failure<std::string>{ error };
    }
    const auto acquired = doof::success_value(_binding_value_18);
#line 402 "/src/driver.do"
    const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>((std::string("/") + packageName), acquired->rootDirectory);
#line 403 "/src/driver.do"
    configuredDriverSourceState->acquisitions->push_back(acquisition);
#line 404 "/src/driver.do"
    configuredDriverSourceState->acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, std::string(""), std::string("git"), package->url, package->ref, package->commit, std::string(""), std::string(""), std::string(""), false));
#line 408 "/src/driver.do"
    return doof::Success<void>{};
}
#line 412 "/src/driver.do"
doof::Result<void, std::string> ensureStdPackageReached(const std::string& packageName) {
#line 413 "/src/driver.do"
    const auto logicalPath = ((std::string("/") + packageName) + std::string("/index.do"));
#line 414 "/src/driver.do"
    auto _try_value_19 = ensureStdPackageAcquisition(logicalPath);
    if (doof::is_failure(_try_value_19)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_19))};
#line 415 "/src/driver.do"
    const auto acquisition = ::app_src_module_acquisition_::acquiredPackageForModule(logicalPath, configuredDriverSourceState->acquisitions);
#line 416 "/src/driver.do"
    if (doof::is_null(acquisition)) {
#line 416 "/src/driver.do"
        return doof::Failure<std::string>{ (std::string("Could not resolve required standard package ") + packageName) };
    }
#line 417 "/src/driver.do"
    auto _binding_value_20 = registerReachedPackage(doof::unwrap_optional(acquisition));
    if (doof::is_failure(_binding_value_20)) {
        const auto error = doof::failure_error(_binding_value_20);
#line 417 "/src/driver.do"
        return doof::Failure<std::string>{ error->message };
    }
#line 418 "/src/driver.do"
    return doof::Success<void>{};
}
#line 421 "/src/driver.do"
std::shared_ptr<::app_src_semantic_::Diagnostic> driverDiagnostic(const std::string& module, const std::string& message) {
#line 422 "/src/driver.do"
    auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
#line 423 "/src/driver.do"
    return std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, ::app_src_semantic_::SemanticSpan{zero, zero}, module, std::string(""));
}
#line 431 "/src/driver.do"
std::string driverSourceDiskRoot(const std::string& path) {
#line 432 "/src/driver.do"
    const auto marker = std::string("/src/");
#line 433 "/src/driver.do"
    auto index = 0;
#line 434 "/src/driver.do"
    while ((index + static_cast<int32_t>(marker.size())) <= static_cast<int32_t>(path.size())) {
#line 435 "/src/driver.do"
        if (doof::string_substring(path, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
#line 436 "/src/driver.do"
            return doof::string_substring(path, 0, ((index + static_cast<int32_t>(marker.size())) - 1));
        }
#line 438 "/src/driver.do"
        (index = (index + 1));
    }
#line 440 "/src/driver.do"
    return std::string("");
}
#line 443 "/src/driver.do"
doof::Result<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>, std::string> sourceLoaderForRequest(const std::string& entryPath, const std::string& stdlibRoot, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget) {
#line 451 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots = std::make_shared<std::vector<std::shared_ptr<DriverSourceRoot>>>(std::vector<std::shared_ptr<DriverSourceRoot>>{});
#line 452 "/src/driver.do"
    const auto rootLogicalPrefix = driverRootLogicalPrefix(rootManifest->name, rootManifest->rootDirectory);
#line 456 "/src/driver.do"
    localRoots->push_back(std::make_shared<DriverSourceRoot>(rootLogicalPrefix, rootManifest->rootDirectory));
#line 457 "/src/driver.do"
    const auto sourceRoot = driverSourceDiskRoot(entryPath);
#line 458 "/src/driver.do"
    if (sourceRoot != std::string("")) {
#line 459 "/src/driver.do"
        localRoots->push_back(std::make_shared<DriverSourceRoot>(std::string("/src"), sourceRoot));
    }
#line 461 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions = std::make_shared<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>(std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>{});
#line 462 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>> acquiredSources = std::make_shared<std::vector<std::shared_ptr<DriverAcquiredSource>>>(std::vector<std::shared_ptr<DriverAcquiredSource>>{});
#line 463 "/src/driver.do"
    if (stdlibRoot != std::string("")) {
#line 464 "/src/driver.do"
        const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>(std::string("/std"), [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(stdlibRoot); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 464, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
#line 465 "/src/driver.do"
        acquisitions->push_back(acquisition);
#line 466 "/src/driver.do"
        acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, driverLogicalPrefix(rootManifest->rootDirectory), std::string("local"), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), true));
    }
#line 470 "/src/driver.do"
    auto _binding_value_21 = ::std_::fs::index::readTextResource(std::string("std-catalog.json"));
    if (doof::is_failure(_binding_value_21)) {
        const auto& catalogSource = _binding_value_21;
#line 470 "/src/driver.do"
        return doof::Failure<std::string>{ std::string("Could not read embedded std-catalog.json") };
    }
    const auto catalogSource = doof::success_value(_binding_value_21);
#line 471 "/src/driver.do"
    auto _try_value_22 = ::app_src_std_catalog_::parseStdCatalog(catalogSource);
    if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_22))};
    const auto catalog = doof::success_value(_try_value_22);
#line 472 "/src/driver.do"
    const auto packageAcquisitionRoot = ::app_src_package_acquisition_::workspacePackageAcquisitionRoot(rootManifest->rootDirectory);
#line 473 "/src/driver.do"
    const auto platformName = ((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform);
#line 474 "/src/driver.do"
    auto _try_value_23 = configureDeclaredDependencies(rootManifest, std::string(""), rootManifest, packageAcquisitionRoot, platformName, acquisitions, acquiredSources);
    if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_23))};
#line 478 "/src/driver.do"
    (configuredDriverSourceState = std::make_shared<DriverSourceState>(localRoots, acquisitions, acquiredSources, std::make_shared<std::vector<std::shared_ptr<DriverReachedPackage>>>(std::vector<std::shared_ptr<DriverReachedPackage>>{}), namespaceMappings, ((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform), (doof::is_null(externalTarget) ? std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(((nativePlatform == std::string("")) ? hostPlatform() : nativePlatform), std::string(""), std::string(""), std::string(""), 1) : doof::unwrap_optional(externalTarget)), rootManifest, catalog, packageAcquisitionRoot));
#line 492 "/src/driver.do"
    return doof::Success<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>>{ configuredDriverSource };
}
#line 495 "/src/driver.do"
doof::Result<void, std::string> configureDeclaredDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& ownerPrefix, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& packageAcquisitionRoot, const std::string& nativePlatform, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions, const std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>>& acquiredSources) {
#line 504 "/src/driver.do"
    const auto& _iterable_25 = manifest->dependencies;
    for (const auto& requested : *_iterable_25) {
#line 505 "/src/driver.do"
        if (doof::string_startsWith(requested->name, std::string("std/"))) {
#line 505 "/src/driver.do"
            continue;
        }
#line 506 "/src/driver.do"
        const auto selected = ::app_src_dependency_policy_::selectedPackageSource(requested, rootManifest->packageResolutions);
#line 507 "/src/driver.do"
        const auto logicalPrefix = (std::string("/") + requested->name);
#line 508 "/src/driver.do"
        auto diskRoot = std::string("");
#line 509 "/src/driver.do"
        auto sourceKind = std::string("local");
#line 510 "/src/driver.do"
        auto sourceUrl = std::string("");
#line 511 "/src/driver.do"
        auto sourceRef = std::string("");
#line 512 "/src/driver.do"
        auto sourceCommit = std::string("");
#line 513 "/src/driver.do"
        auto mutable_ = false;
#line 514 "/src/driver.do"
        if (selected->path != std::string("")) {
#line 515 "/src/driver.do"
            (diskRoot = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(selected->path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 515, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
#line 516 "/src/driver.do"
            (mutable_ = true);
        } else {
#line 518 "/src/driver.do"
            auto _binding_value_26 = ::app_src_package_acquisition_::acquireExactGitPackage(std::make_shared<::app_src_package_acquisition_::ExactPackageSource>(selected->name, std::string(""), selected->url, selected->ref, selected->commit), packageAcquisitionRoot);
            if (doof::is_failure(_binding_value_26)) {
                const auto error = doof::failure_error(_binding_value_26);
#line 520 "/src/driver.do"
                return doof::Failure<std::string>{ error };
            }
            const auto acquired = doof::success_value(_binding_value_26);
#line 521 "/src/driver.do"
            (diskRoot = acquired->rootDirectory);
#line 522 "/src/driver.do"
            (sourceKind = std::string("git"));
#line 523 "/src/driver.do"
            (sourceUrl = ::app_src_std_catalog_::canonicalDependencyUrl(selected->url));
#line 524 "/src/driver.do"
            (sourceRef = selected->ref);
#line 525 "/src/driver.do"
            (sourceCommit = selected->commit);
        }
#line 527 "/src/driver.do"
        const auto& _iterable_28 = acquiredSources;
        for (const auto& existing : *_iterable_28) {
#line 528 "/src/driver.do"
            if ((((sourceUrl != std::string("")) && (existing->sourceUrl != std::string(""))) && (::app_src_std_catalog_::canonicalDependencyUrl(existing->sourceUrl) == sourceUrl)) && (existing->sourceCommit != sourceCommit)) {
#line 530 "/src/driver.do"
                return doof::Failure<std::string>{ ((std::string("Conflicting package revisions for ") + sourceUrl) + std::string("; add a root resolutions.packages entry")) };
            }
#line 532 "/src/driver.do"
            if (existing->acquisition->logicalPrefix == logicalPrefix) {
#line 533 "/src/driver.do"
                if (existing->acquisition->diskRoot != diskRoot) {
#line 534 "/src/driver.do"
                    return doof::Failure<std::string>{ ((std::string("Package import prefix ") + logicalPrefix) + std::string(" resolves to multiple packages")) };
                }
#line 536 "/src/driver.do"
                (diskRoot = std::string(""));
            }
        }
#line 539 "/src/driver.do"
        if (diskRoot == std::string("")) {
#line 539 "/src/driver.do"
            continue;
        }
#line 540 "/src/driver.do"
        const auto acquisition = std::make_shared<::app_src_module_acquisition_::ModuleAcquisition>(logicalPrefix, diskRoot);
#line 541 "/src/driver.do"
        acquisitions->push_back(acquisition);
#line 542 "/src/driver.do"
        acquiredSources->push_back(std::make_shared<DriverAcquiredSource>(acquisition, ownerPrefix, sourceKind, sourceUrl, sourceRef, sourceCommit, ((requested->url == std::string("")) ? std::string("") : ::app_src_std_catalog_::canonicalDependencyUrl(requested->url)), requested->ref, requested->commit, mutable_));
#line 547 "/src/driver.do"
        const auto dependencyManifestPath = ::app_src_module_acquisition_::acquiredManifestPath(acquisition);
#line 548 "/src/driver.do"
        auto _binding_value_29 = ::doof_fs::readText(dependencyManifestPath);
        if (doof::is_failure(_binding_value_29)) {
            const auto& dependencySource = _binding_value_29;
#line 549 "/src/driver.do"
            return doof::Failure<std::string>{ (std::string("Could not read dependency manifest ") + dependencyManifestPath) };
        }
        const auto dependencySource = doof::success_value(_binding_value_29);
#line 551 "/src/driver.do"
        auto _try_value_30 = parseDependencyManifestForTarget(dependencySource, dependencyManifestPath, diskRoot, nativePlatform, rootManifest->target);
        if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_30))};
        const auto dependencyManifest = doof::success_value(_try_value_30);
#line 558 "/src/driver.do"
        if (dependencyManifest->name == std::string("")) {
#line 558 "/src/driver.do"
            return doof::Failure<std::string>{ (std::string("Dependency package must declare a name: ") + dependencyManifestPath) };
        }
#line 559 "/src/driver.do"
        if ((static_cast<int32_t>((dependencyManifest->packageResolutions)->size()) > 0) || (static_cast<int32_t>((dependencyManifest->externalResolutions)->size()) > 0)) {
#line 560 "/src/driver.do"
            return doof::Failure<std::string>{ (std::string("resolutions are only allowed in the root doof.json: ") + dependencyManifestPath) };
        }
#line 562 "/src/driver.do"
        auto _try_value_31 = configureDeclaredDependencies(dependencyManifest, logicalPrefix, rootManifest, packageAcquisitionRoot, nativePlatform, acquisitions, acquiredSources);
        if (doof::is_failure(_try_value_31)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_31))};
    }
#line 567 "/src/driver.do"
    return doof::Success<void>{};
}
#line 570 "/src/driver.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> reachedPackageInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
#line 571 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>(std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>{std::make_shared<::app_src_dependency_policy_::ReachedPackageInput>(driverLogicalPrefix(rootManifest->rootDirectory), std::string(""), rootManifest, std::string("root"), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), std::string(""), false)});
#line 575 "/src/driver.do"
    const auto& _iterable_33 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_33) {
#line 576 "/src/driver.do"
        result->push_back(std::make_shared<::app_src_dependency_policy_::ReachedPackageInput>(reached->acquisition->logicalPrefix, reached->introducedBy, reached->manifest, reached->sourceKind, reached->sourceUrl, reached->sourceRef, reached->sourceCommit, reached->requestedUrl, reached->requestedRef, reached->requestedCommit, reached->mutable_));
    }
#line 590 "/src/driver.do"
    return result;
}
#line 593 "/src/driver.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>, std::string> resolvedDependencyInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
#line 594 "/src/driver.do"
    const auto packages = reachedPackageInputs(rootManifest);
#line 595 "/src/driver.do"
    auto _try_value_34 = ::app_src_dependency_policy_::resolveExternalInputs(packages, rootManifest);
    if (doof::is_failure(_try_value_34)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_34))};
    const auto externals = doof::success_value(_try_value_34);
#line 596 "/src/driver.do"
    auto _try_value_35 = ::app_src_dependency_policy_::validateDependencyPolicy(packages, externals, rootManifest);
    if (doof::is_failure(_try_value_35)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_35))};
#line 597 "/src/driver.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>>{ externals };
}
#line 600 "/src/driver.do"
doof::Result<void, std::string> acquireResolvedExternalInputs(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& inputs, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& target) {
#line 604 "/src/driver.do"
    const auto& _iterable_37 = inputs;
    for (const auto& input : *_iterable_37) {
#line 605 "/src/driver.do"
        const auto dependency = selectedExternalDependency(input);
#line 606 "/src/driver.do"
        const auto manifest = std::make_shared<::app_src_package_manifest_::PackageManifest>(input->owner->manifest->name, std::string("1.0"), input->owner->manifest->manifestPath, input->owner->manifest->rootDirectory, std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{dependency}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<::app_src_package_manifest_::DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::string(""), nullptr, nullptr, nullptr, nullptr);
#line 613 "/src/driver.do"
        auto _try_value_38 = ::app_src_external_dependency_::acquirePackageExternalDependencies(manifest, target);
        if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
    }
#line 615 "/src/driver.do"
    return doof::Success<void>{};
}
#line 618 "/src/driver.do"
std::shared_ptr<::app_src_package_manifest_::ExternalDependency> selectedExternalDependency(const std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>& input) {
#line 619 "/src/driver.do"
    const auto requested = input->dependency;
#line 620 "/src/driver.do"
    return std::make_shared<::app_src_package_manifest_::ExternalDependency>(requested->name, input->selectedKind, input->selectedUrl, requested->destination, input->selectedSha256, requested->stripComponents, requested->copyFiles, input->selectedRef, input->selectedCommit, requested->commands);
}
#line 634 "/src/driver.do"
doof::Result<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>, std::string> externalTargetForRequest(const std::string& target, const std::string& nativePlatform, const std::string& iosDestination, const std::string& iosMinimumVersion) {
#line 640 "/src/driver.do"
    if (target == std::string("wasm")) {
#line 641 "/src/driver.do"
        return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(std::string("wasm"), std::string(""), std::string("wasm32-unknown-emscripten"), std::string("wasm32-unknown-emscripten"), 1) };
    }
#line 647 "/src/driver.do"
    if (!doof::string_startsWith(nativePlatform, std::string("ios-"))) {
#line 648 "/src/driver.do"
        return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(nativePlatform, std::string(""), std::string(""), std::string(""), 1) };
    }
#line 650 "/src/driver.do"
    const auto sdkName = ((iosDestination == std::string("device")) ? std::string("iphoneos") : std::string("iphonesimulator"));
#line 651 "/src/driver.do"
    const auto sdkResult = runNativeCommand(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--sdk"), sdkName, std::string("--show-sdk-path")}), std::nullopt, false, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
#line 652 "/src/driver.do"
    if (sdkResult->exitCode != 0) {
#line 652 "/src/driver.do"
        return doof::Failure<std::string>{ ((std::string("Could not resolve the ") + sdkName) + std::string(" SDK for external dependencies")) };
    }
#line 653 "/src/driver.do"
    const auto sdkPath = doof::string_trim(::doof_blob::NativeBlobReader::constructor(sdkResult->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((sdkResult->output)->size()))));
#line 654 "/src/driver.do"
    const auto hostArchitecture = ::std_::os::index::architecture();
#line 655 "/src/driver.do"
    auto _try_value_39 = ::app_src_ios_app_::iosTargetTriple(iosMinimumVersion, iosDestination, hostArchitecture);
    if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_39))};
    const auto targetTriple = doof::success_value(_try_value_39);
#line 656 "/src/driver.do"
    const auto configureHost = ((iosDestination == std::string("device")) ? std::string("aarch64-apple-darwin") : (((hostArchitecture == std::string("x86_64")) || (hostArchitecture == std::string("x64"))) ? std::string("x86_64-apple-darwin") : std::string("aarch64-apple-darwin")));
#line 659 "/src/driver.do"
    return doof::Success<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>>{ std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(nativePlatform, sdkPath, targetTriple, configureHost, 1) };
}
#line 667 "/src/driver.do"
std::string driverLogicalPrefix(const std::string& path) {
#line 668 "/src/driver.do"
    const auto absolutePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 668, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 669 "/src/driver.do"
    const auto sourceSuffix = driverSourceSuffix(absolutePath);
#line 670 "/src/driver.do"
    if (sourceSuffix != absolutePath) {
#line 670 "/src/driver.do"
        return sourceSuffix;
    }
#line 671 "/src/driver.do"
    if (doof::string_startsWith(absolutePath, std::string("/"))) {
#line 671 "/src/driver.do"
        return absolutePath;
    }
#line 672 "/src/driver.do"
    return (std::string("/") + absolutePath);
}
#line 675 "/src/driver.do"
std::string driverRootLogicalPrefix(const std::string& packageName, const std::string& rootDirectory) {
#line 676 "/src/driver.do"
    if (doof::string_startsWith(packageName, std::string("std/"))) {
#line 676 "/src/driver.do"
        return (std::string("/") + packageName);
    }
#line 677 "/src/driver.do"
    return driverLogicalPrefix(rootDirectory);
}
#line 680 "/src/driver.do"
std::string driverRootLogicalPath(const std::string& path, const std::string& rootDirectory, const std::string& packageName) {
#line 681 "/src/driver.do"
    if (!doof::string_startsWith(packageName, std::string("std/"))) {
#line 681 "/src/driver.do"
        return driverLogicalPath(path);
    }
#line 682 "/src/driver.do"
    const auto prefix = driverRootLogicalPrefix(packageName, rootDirectory);
#line 683 "/src/driver.do"
    const auto absolutePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 683, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 684 "/src/driver.do"
    const auto absoluteRoot = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(rootDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 684, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 685 "/src/driver.do"
    if (absolutePath == absoluteRoot) {
#line 685 "/src/driver.do"
        return prefix;
    }
#line 686 "/src/driver.do"
    const auto rootPrefix = (doof::string_endsWith(absoluteRoot, std::string("/")) ? absoluteRoot : (absoluteRoot + std::string("/")));
#line 687 "/src/driver.do"
    if (doof::string_startsWith(absolutePath, rootPrefix)) {
#line 688 "/src/driver.do"
        return ((prefix + std::string("/")) + doof::string_substring(absolutePath, static_cast<int32_t>(rootPrefix.size()), static_cast<int32_t>(absolutePath.size())));
    }
#line 690 "/src/driver.do"
    return driverLogicalPath(absolutePath);
}
#line 693 "/src/driver.do"
std::string driverPackageOutputRoot(const std::string& logicalPrefix) {
#line 694 "/src/driver.do"
    auto start = 0;
#line 695 "/src/driver.do"
    while ((start < static_cast<int32_t>(logicalPrefix.size())) && (doof::string_at(logicalPrefix, start, "src/driver", 695) == U'\u002F')) {
#line 695 "/src/driver.do"
        (start = (start + 1));
    }
#line 696 "/src/driver.do"
    return doof::string_substring(logicalPrefix, start, static_cast<int32_t>(logicalPrefix.size()));
}
#line 699 "/src/driver.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> projectNativePackages(const std::string& projectRoot, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& projectManifest, const std::string& stdlibRoot) {
#line 700 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> packages = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>>(std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>{std::make_shared<::app_src_emitter_project_::NativePackageInput>(driverRootLogicalPrefix(projectManifest->name, projectRoot), std::string(""), projectManifest)});
#line 705 "/src/driver.do"
    if ((projectManifest->target == std::string("wasm")) && (stdlibRoot != std::string(""))) {
#line 706 "/src/driver.do"
        const auto jsonRoot = ::app_src_project_::joinPath(stdlibRoot, std::string("json"));
#line 707 "/src/driver.do"
        const auto jsonManifestPath = ::app_src_project_::joinPath(jsonRoot, std::string("doof.json"));
#line 708 "/src/driver.do"
        const auto jsonManifest = [&]() -> std::shared_ptr<::app_src_package_manifest_::PackageManifest> { auto _try_value = ::app_src_package_manifest_::parsePackageManifest([&]() -> std::string { auto _try_value = ::doof_fs::readText(jsonManifestPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 708, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }(), jsonManifestPath, jsonRoot, std::string("wasm"), std::string("")); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 708, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 709 "/src/driver.do"
        packages->push_back(std::make_shared<::app_src_emitter_project_::NativePackageInput>(std::string("/std/json"), std::string("std/json"), jsonManifest));
    }
#line 715 "/src/driver.do"
    const auto& _iterable_41 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_41) {
#line 716 "/src/driver.do"
        packages->push_back(std::make_shared<::app_src_emitter_project_::NativePackageInput>(reached->acquisition->logicalPrefix, driverPackageOutputRoot(reached->acquisition->logicalPrefix), reached->manifest));
    }
#line 722 "/src/driver.do"
    return packages;
}
#line 725 "/src/driver.do"
void ensureOutputDirectory(const std::string& path) {
#line 726 "/src/driver.do"
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
#line 726 "/src/driver.do"
        return;
    }
#line 727 "/src/driver.do"
    const auto parent = ::app_src_project_::parentPath(path);
#line 728 "/src/driver.do"
    if (parent != path) {
#line 728 "/src/driver.do"
        ensureOutputDirectory(parent);
    }
#line 729 "/src/driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 729, std::string("try! failed"));  }();
}
#line 732 "/src/driver.do"
void materializeNativeCopy(const std::string& sourcePath, const std::string& outputPath) {
#line 733 "/src/driver.do"
    if (::doof_fs::isDirectory(sourcePath)) {
#line 734 "/src/driver.do"
        ensureOutputDirectory(outputPath);
#line 735 "/src/driver.do"
        const auto& _iterable_43 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 735, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_43) {
#line 736 "/src/driver.do"
            materializeNativeCopy(::app_src_project_::joinPath(sourcePath, entry->name), ::app_src_project_::joinPath(outputPath, entry->name));
        }
#line 738 "/src/driver.do"
        return;
    }
#line 740 "/src/driver.do"
    ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
#line 741 "/src/driver.do"
    writeBlobIfChanged(outputPath, [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 741, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
}
#line 744 "/src/driver.do"
void writeTextIfChanged(const std::string& path, const std::string& content) {
#line 745 "/src/driver.do"
    if (::doof_fs::exists(path)) {
#line 746 "/src/driver.do"
        const auto existing = [&]() -> std::string { auto _try_value = ::doof_fs::readText(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 746, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 747 "/src/driver.do"
        if (existing == content) {
#line 747 "/src/driver.do"
            return;
        }
    }
#line 749 "/src/driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 749, std::string("try! failed"));  }();
}
#line 755 "/src/driver.do"
void materializeGeneratedText(const std::string& path, const std::string& content) {
#line 756 "/src/driver.do"
    ensureOutputDirectory(::app_src_project_::parentPath(path));
#line 757 "/src/driver.do"
    writeTextIfChanged(path, content);
}
#line 760 "/src/driver.do"
std::string frontendCachePath(const std::string& buildDirectory, const std::string& kind) {
#line 761 "/src/driver.do"
    return driverOutputPath(driverOutputPath(buildDirectory, std::string(".doof-cache/v1")), (kind + std::string(".json")));
}
#line 764 "/src/driver.do"
std::string frontendConfigurationFingerprint(const std::string& entry, const std::string& entryMode, const std::string& target, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& stdlibRoot, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget) {
#line 773 "/src/driver.do"
    const auto manifestSource = readTextOrEmpty(manifest->manifestPath);
#line 774 "/src/driver.do"
    return ::std_::crypto::index::sha256HexString((((((((((((((((((((((std::string("doof-frontend-cache-2:") + doof::to_string(::app_src_frontend_cache_::FRONTEND_SEMANTIC_ABI)) + std::string("\n")) + entry) + std::string("\n")) + entryMode) + std::string("\n")) + target) + std::string("\n")) + stdlibRoot) + std::string("\n")) + nativePlatform) + std::string("\n")) + externalTarget->nativeTarget) + std::string("\n")) + externalTarget->sdkPath) + std::string("\n")) + externalTarget->targetTriple) + std::string("\n")) + configuredDriverSourceState->stdCatalog->digest) + std::string("\n")) + manifestSource));
}
#line 782 "/src/driver.do"
std::string readTextOrEmpty(const std::string& path) {
#line 783 "/src/driver.do"
    auto _binding_value_44 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_44)) {
        const auto& source = _binding_value_44;
#line 783 "/src/driver.do"
        return std::string("");
    }
    const auto source = doof::success_value(_binding_value_44);
#line 784 "/src/driver.do"
    return source;
}
#line 787 "/src/driver.do"
std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> readFrontendState(const std::string& path) {
#line 788 "/src/driver.do"
    if (!::doof_fs::exists(path)) {
#line 788 "/src/driver.do"
        return nullptr;
    }
#line 789 "/src/driver.do"
    auto _binding_value_45 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_45)) {
        const auto& source = _binding_value_45;
#line 789 "/src/driver.do"
        return nullptr;
    }
    const auto source = doof::success_value(_binding_value_45);
#line 790 "/src/driver.do"
    return ::app_src_frontend_cache_::parseFrontendCacheState(source);
}
#line 793 "/src/driver.do"
bool frontendStateMatches(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& configurationFingerprint, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader) {
#line 798 "/src/driver.do"
    if (doof::is_null(state) || (state->configurationFingerprint != configurationFingerprint)) {
#line 798 "/src/driver.do"
        return false;
    }
#line 799 "/src/driver.do"
    const auto& _iterable_47 = state->fileInputs;
    for (const auto& input : *_iterable_47) {
#line 800 "/src/driver.do"
        auto _binding_value_48 = ::doof_fs::readText(input->path);
        if (doof::is_failure(_binding_value_48)) {
            const auto& source = _binding_value_48;
#line 800 "/src/driver.do"
            return false;
        }
        const auto source = doof::success_value(_binding_value_48);
#line 801 "/src/driver.do"
        if (::std_::crypto::index::sha256HexString(source) != input->sourceHash) {
#line 801 "/src/driver.do"
            return false;
        }
    }
#line 803 "/src/driver.do"
    const auto& _iterable_50 = state->probes;
    for (const auto& probe : *_iterable_50) {
#line 804 "/src/driver.do"
        auto _binding_value_51 = loader.call(probe->logicalPath);
        if (doof::is_failure(_binding_value_51)) {
            const auto& source = _binding_value_51;
#line 804 "/src/driver.do"
            return false;
        }
        const auto source = doof::success_value(_binding_value_51);
#line 805 "/src/driver.do"
        if (probe->missing) {
#line 806 "/src/driver.do"
            if (!doof::is_null(source)) {
#line 806 "/src/driver.do"
                return false;
            }
        } else {
#line 808 "/src/driver.do"
            if (doof::is_null(source) || (::std_::crypto::index::sha256HexString(source->source) != probe->sourceHash)) {
#line 808 "/src/driver.do"
                return false;
            }
        }
    }
#line 811 "/src/driver.do"
    return true;
}
#line 814 "/src/driver.do"
std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> frontendStateForCompilation(const std::shared_ptr<::app_src_compiler_::Compilation>& result, const std::string& configurationFingerprint, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
#line 819 "/src/driver.do"
    const auto state = std::make_shared<::app_src_frontend_cache_::FrontendCacheState>(2, configurationFingerprint, std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendSourceProbe>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendSourceProbe>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendModuleOutput>>>(std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendModuleOutput>>{}));
#line 820 "/src/driver.do"
    const auto& _iterable_53 = result->resolutionProbes;
    for (const auto& path : *_iterable_53) {
#line 821 "/src/driver.do"
        std::shared_ptr<::app_src_semantic_::SourceFile> matched = nullptr;
#line 822 "/src/driver.do"
        const auto& _iterable_55 = result->sourceFiles;
        for (const auto& source : *_iterable_55) {
#line 822 "/src/driver.do"
            if (source->path == path) {
#line 822 "/src/driver.do"
                (matched = source);
            }
        }
#line 823 "/src/driver.do"
        state->probes->push_back(std::make_shared<::app_src_frontend_cache_::FrontendSourceProbe>(path, (doof::is_null(matched) ? std::string("") : ::std_::crypto::index::sha256HexString(matched->source)), doof::is_null(matched)));
    }
#line 829 "/src/driver.do"
    addFrontendFileInput(state->fileInputs, rootManifest->manifestPath);
#line 830 "/src/driver.do"
    const auto& _iterable_57 = configuredDriverSourceState->reachedPackages;
    for (const auto& reached : *_iterable_57) {
#line 831 "/src/driver.do"
        addFrontendFileInput(state->fileInputs, reached->manifest->manifestPath);
    }
#line 833 "/src/driver.do"
    if (!doof::is_null(result->emission)) {
#line 834 "/src/driver.do"
        const auto& _iterable_59 = result->emission->modules;
        for (const auto& module : *_iterable_59) {
#line 835 "/src/driver.do"
            state->modules->push_back(std::make_shared<::app_src_frontend_cache_::FrontendModuleOutput>(module->modulePath, module->headerName, module->sourceName, module->fingerprint));
        }
    }
#line 841 "/src/driver.do"
    return state;
}
#line 844 "/src/driver.do"
std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> cachedModuleGraph(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory) {
#line 845 "/src/driver.do"
    if (static_cast<int32_t>((state->modules)->size()) == 0) {
#line 845 "/src/driver.do"
        return nullptr;
    }
#line 846 "/src/driver.do"
    const auto graph = std::make_shared<::app_src_emitter_module_::ModuleGraphEmission>(std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>{}), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 847 "/src/driver.do"
    const auto& _iterable_61 = state->modules;
    for (const auto& module : *_iterable_61) {
#line 848 "/src/driver.do"
        if (!::doof_fs::exists(driverOutputPath(outputDirectory, module->headerName)) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->sourceName))) {
#line 849 "/src/driver.do"
            return nullptr;
        }
#line 850 "/src/driver.do"
        graph->modules->push_back(std::make_shared<::app_src_emitter_module_::ModuleEmission>(module->modulePath, std::string(""), std::string(""), module->headerName, module->sourceName, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), true, module->fingerprint));
    }
#line 855 "/src/driver.do"
    return graph;
}
#line 859 "/src/driver.do"
bool frontendEmissionCacheSupported(const std::string& target) {
#line 860 "/src/driver.do"
    return ((target != std::string("wasm")) && (target != std::string("ios-app")));
}
#line 863 "/src/driver.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>> reusableEmissionKeys(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory) {
#line 867 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>> keys = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{});
#line 868 "/src/driver.do"
    if (doof::is_null(state)) {
#line 868 "/src/driver.do"
        return keys;
    }
#line 869 "/src/driver.do"
    const auto& _iterable_63 = state->modules;
    for (const auto& module : *_iterable_63) {
#line 870 "/src/driver.do"
        if (((module->fingerprint == std::string("")) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->headerName))) || !::doof_fs::exists(driverOutputPath(outputDirectory, module->sourceName))) {
#line 871 "/src/driver.do"
            continue;
        }
#line 872 "/src/driver.do"
        keys->push_back(std::make_shared<::app_src_emitter_module_::ModuleEmissionCacheKey>(module->modulePath, module->fingerprint));
    }
#line 874 "/src/driver.do"
    return keys;
}
#line 877 "/src/driver.do"
void addFrontendFileInput(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>>& inputs, const std::string& path) {
#line 878 "/src/driver.do"
    const auto& _iterable_65 = inputs;
    for (const auto& input : *_iterable_65) {
#line 878 "/src/driver.do"
        if (input->path == path) {
#line 878 "/src/driver.do"
            return;
        }
    }
#line 879 "/src/driver.do"
    auto _binding_value_66 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_66)) {
        const auto& source = _binding_value_66;
#line 879 "/src/driver.do"
        return;
    }
    const auto source = doof::success_value(_binding_value_66);
#line 880 "/src/driver.do"
    inputs->push_back(std::make_shared<::app_src_frontend_cache_::FrontendFileInput>(path, ::std_::crypto::index::sha256HexString(source)));
}
#line 883 "/src/driver.do"
void writeFrontendState(const std::string& path, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state) {
#line 884 "/src/driver.do"
    ensureOutputDirectory(::app_src_project_::parentPath(path));
#line 885 "/src/driver.do"
    const auto temporaryPath = (path + std::string(".tmp"));
#line 886 "/src/driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(temporaryPath, ::app_src_frontend_cache_::renderFrontendCacheState(state)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 886, std::string("try! failed"));  }();
#line 887 "/src/driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::rename(temporaryPath, path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 887, std::string("try! failed"));  }();
}
#line 890 "/src/driver.do"
void removeStaleFrontendOutputs(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& previous, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& current, const std::string& outputDirectory) {
#line 895 "/src/driver.do"
    if (doof::is_null(previous)) {
#line 895 "/src/driver.do"
        return;
    }
#line 896 "/src/driver.do"
    const auto prefix = (doof::string_endsWith(outputDirectory, std::string("/")) ? outputDirectory : (outputDirectory + std::string("/")));
#line 897 "/src/driver.do"
    const auto& _iterable_68 = previous->modules;
    for (const auto& old : *_iterable_68) {
#line 898 "/src/driver.do"
        auto retained = false;
#line 899 "/src/driver.do"
        const auto& _iterable_70 = current->modules;
        for (const auto& module : *_iterable_70) {
#line 900 "/src/driver.do"
            if (((module->modulePath == old->modulePath) && (module->headerName == old->headerName)) && (module->sourceName == old->sourceName)) {
#line 901 "/src/driver.do"
                (retained = true);
            }
        }
#line 904 "/src/driver.do"
        if (retained) {
#line 904 "/src/driver.do"
            continue;
        }
#line 905 "/src/driver.do"
        const auto& _iterable_72 = std::make_shared<std::vector<std::string>>(std::vector<std::string>{old->headerName, old->sourceName});
        for (const auto& name : *_iterable_72) {
#line 906 "/src/driver.do"
            const auto path = driverOutputPath(outputDirectory, name);
#line 907 "/src/driver.do"
            if ((doof::string_startsWith(path, prefix) && ::doof_fs::exists(path)) && !::doof_fs::isDirectory(path)) {
#line 907 "/src/driver.do"
                [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 907, std::string("try! failed"));  }();
            }
        }
    }
}
#line 912 "/src/driver.do"
void writeBlobIfChanged(const std::string& path, const std::shared_ptr<std::vector<uint8_t>>& content) {
#line 913 "/src/driver.do"
    if (::doof_fs::exists(path)) {
#line 914 "/src/driver.do"
        const auto existing = [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 914, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 915 "/src/driver.do"
        if (blobsEqual(existing, content)) {
#line 915 "/src/driver.do"
            return;
        }
    }
#line 917 "/src/driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(path, content); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 917, std::string("try! failed"));  }();
}
#line 920 "/src/driver.do"
bool blobsEqual(const std::shared_ptr<std::vector<uint8_t>>& left, const std::shared_ptr<std::vector<uint8_t>>& right) {
#line 921 "/src/driver.do"
    if (static_cast<int32_t>((left)->size()) != static_cast<int32_t>((right)->size())) {
#line 921 "/src/driver.do"
        return false;
    }
#line 922 "/src/driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>((left)->size()); ++index) {
#line 922 "/src/driver.do"
        if (doof::array_at(left, index, "src/driver", 922) != doof::array_at(right, index, "src/driver", 922)) {
#line 922 "/src/driver.do"
            return false;
        }
    }
#line 923 "/src/driver.do"
    return true;
}
#line 926 "/src/driver.do"
void materializeProject(const std::string& outputDirectory, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project) {
#line 927 "/src/driver.do"
    ensureOutputDirectory(outputDirectory);
#line 928 "/src/driver.do"
    const auto& _iterable_75 = project->modules;
    for (const auto& module : *_iterable_75) {
#line 929 "/src/driver.do"
        if (module->reused) {
#line 929 "/src/driver.do"
            continue;
        }
#line 930 "/src/driver.do"
        materializeGeneratedText(driverOutputPath(outputDirectory, module->headerName), module->header);
#line 931 "/src/driver.do"
        materializeGeneratedText(driverOutputPath(outputDirectory, module->sourceName), module->source);
    }
#line 933 "/src/driver.do"
    const auto& _iterable_77 = project->supportFiles;
    for (const auto& supportFile : *_iterable_77) {
#line 934 "/src/driver.do"
        const auto outputPath = driverOutputPath(outputDirectory, supportFile->relativePath);
#line 935 "/src/driver.do"
        ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
#line 936 "/src/driver.do"
        writeTextIfChanged(outputPath, supportFile->content);
    }
#line 938 "/src/driver.do"
    const auto& _iterable_79 = project->nativeCopies;
    for (const auto& nativeCopy : *_iterable_79) {
#line 939 "/src/driver.do"
        materializeNativeCopy(nativeCopy->sourcePath, driverOutputPath(outputDirectory, nativeCopy->relativePath));
    }
}
#line 946 "/src/driver.do"
void materializeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory) {
#line 947 "/src/driver.do"
    const auto& _iterable_81 = resources;
    for (const auto& resource : *_iterable_81) {
#line 948 "/src/driver.do"
        const auto destinationRoot = driverOutputPath(outputDirectory, resource->destination);
#line 949 "/src/driver.do"
        const auto outputPath = (::doof_fs::isDirectory(resource->sourcePath) ? destinationRoot : driverOutputPath(destinationRoot, ::app_src_project_::fileName(resource->sourcePath)));
#line 952 "/src/driver.do"
        materializeNativeCopy(resource->sourcePath, outputPath);
    }
}
#line 956 "/src/driver.do"
std::shared_ptr<::app_src_resource_state_::ResourceState> readResourceState(const std::string& path) {
#line 957 "/src/driver.do"
    if (!::doof_fs::exists(path)) {
#line 957 "/src/driver.do"
        return std::make_shared<::app_src_resource_state_::ResourceState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>(std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>{}));
    }
#line 958 "/src/driver.do"
    auto _binding_value_82 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_82)) {
        const auto& source = _binding_value_82;
#line 958 "/src/driver.do"
        return std::make_shared<::app_src_resource_state_::ResourceState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>(std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>{}));
    }
    const auto source = doof::success_value(_binding_value_82);
#line 959 "/src/driver.do"
    const auto parsed = ::app_src_resource_state_::parseResourceState(source);
#line 960 "/src/driver.do"
    return (doof::is_null(parsed) ? std::make_shared<::app_src_resource_state_::ResourceState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>(std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>{})) : doof::unwrap_optional(parsed));
}
#line 963 "/src/driver.do"
void materializeTrackedResource(const std::string& sourcePath, const std::string& outputPath, const std::shared_ptr<::app_src_resource_state_::ResourceState>& previous, const std::shared_ptr<::app_src_resource_state_::ResourceState>& next) {
#line 969 "/src/driver.do"
    if (::doof_fs::isDirectory(sourcePath)) {
#line 970 "/src/driver.do"
        ensureOutputDirectory(outputPath);
#line 971 "/src/driver.do"
        const auto& _iterable_84 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 971, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_84) {
#line 972 "/src/driver.do"
            materializeTrackedResource(::app_src_project_::joinPath(sourcePath, entry->name), ::app_src_project_::joinPath(outputPath, entry->name), previous, next);
        }
#line 974 "/src/driver.do"
        return;
    }
#line 976 "/src/driver.do"
    const auto sourceInfo = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 976, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 977 "/src/driver.do"
    const auto prior = ::app_src_resource_state_::findMaterializedResource(previous, sourcePath, outputPath);
#line 978 "/src/driver.do"
    if (::doof_fs::exists(outputPath) && !::doof_fs::isDirectory(outputPath)) {
#line 979 "/src/driver.do"
        const auto outputInfo = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 979, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 980 "/src/driver.do"
        if (::app_src_resource_state_::materializedResourceIsCurrent(prior, sourceInfo->size, sourceInfo->modifiedAt->toEpochNanos(), outputInfo->size, outputInfo->modifiedAt->toEpochNanos())) {
#line 987 "/src/driver.do"
            next->files->push_back(doof::unwrap_optional(prior));
#line 988 "/src/driver.do"
            return;
        }
    }
#line 991 "/src/driver.do"
    materializeNativeCopy(sourcePath, outputPath);
#line 992 "/src/driver.do"
    const auto outputInfo = [&]() -> std::shared_ptr<::std_::fs::types::FileInfo> { auto _try_value = ::doof_fs::metadata(outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 992, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 993 "/src/driver.do"
    next->files->push_back(std::make_shared<::app_src_resource_state_::MaterializedResource>(sourcePath, outputPath, sourceInfo->size, sourceInfo->modifiedAt->toEpochNanos(), outputInfo->size, outputInfo->modifiedAt->toEpochNanos()));
}
#line 1003 "/src/driver.do"
bool resourceOutputIsCurrent(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>& files, const std::string& outputPath) {
#line 1004 "/src/driver.do"
    const auto& _iterable_86 = files;
    for (const auto& file : *_iterable_86) {
#line 1004 "/src/driver.do"
        if (file->outputPath == outputPath) {
#line 1004 "/src/driver.do"
            return true;
        }
    }
#line 1005 "/src/driver.do"
    return false;
}
#line 1008 "/src/driver.do"
void synchronizeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory, const std::string& statePath) {
#line 1013 "/src/driver.do"
    const auto previous = readResourceState(statePath);
#line 1014 "/src/driver.do"
    const auto next = std::make_shared<::app_src_resource_state_::ResourceState>(1, std::make_shared<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>(std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>{}));
#line 1015 "/src/driver.do"
    const auto& _iterable_88 = resources;
    for (const auto& resource : *_iterable_88) {
#line 1016 "/src/driver.do"
        const auto destinationRoot = driverOutputPath(outputDirectory, resource->destination);
#line 1017 "/src/driver.do"
        const auto outputPath = (::doof_fs::isDirectory(resource->sourcePath) ? destinationRoot : driverOutputPath(destinationRoot, ::app_src_project_::fileName(resource->sourcePath)));
#line 1020 "/src/driver.do"
        materializeTrackedResource(resource->sourcePath, outputPath, previous, next);
    }
#line 1022 "/src/driver.do"
    const auto prefix = (doof::string_endsWith(outputDirectory, std::string("/")) ? outputDirectory : (outputDirectory + std::string("/")));
#line 1023 "/src/driver.do"
    const auto& _iterable_90 = previous->files;
    for (const auto& old : *_iterable_90) {
#line 1024 "/src/driver.do"
        if (((resourceOutputIsCurrent(next->files, old->outputPath) || !doof::string_startsWith(old->outputPath, prefix)) || !::doof_fs::exists(old->outputPath)) || ::doof_fs::isDirectory(old->outputPath)) {
#line 1025 "/src/driver.do"
            continue;
        }
#line 1026 "/src/driver.do"
        [&]() -> void { auto _try_value = ::doof_fs::remove(old->outputPath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1026, std::string("try! failed"));  }();
    }
#line 1028 "/src/driver.do"
    ensureOutputDirectory(::app_src_project_::parentPath(statePath));
#line 1029 "/src/driver.do"
    const auto temporaryPath = (statePath + std::string(".tmp"));
#line 1030 "/src/driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(temporaryPath, ::app_src_resource_state_::renderResourceState(next)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1030, std::string("try! failed"));  }();
#line 1031 "/src/driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::rename(temporaryPath, statePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1031, std::string("try! failed"));  }();
}
#line 1034 "/src/driver.do"
void materializeRuntimeHeader(const std::string& outputDirectory) {
#line 1037 "/src/driver.do"
    auto sourcePath = ::app_src_project_::environmentValue(std::string("DOOF_RUNTIME_HEADER"));
#line 1038 "/src/driver.do"
    const auto runtimeSource = ((sourcePath == std::string("")) ? ::std_::fs::index::readTextResource(std::string("doof_runtime.h")) : ::doof_fs::readText(sourcePath));
#line 1041 "/src/driver.do"
    writeTextIfChanged(driverOutputPath(outputDirectory, std::string("doof_runtime.hpp")), [&]() -> std::string { auto _try_value = runtimeSource; if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1041, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
}
#line 1044 "/src/driver.do"
std::string nativeBuildOutputName(const std::string& projectName, const std::string& nativePlatform) {
#line 1045 "/src/driver.do"
    const auto name = doof::string_replaceAll(doof::string_replaceAll(projectName, std::string("/"), std::string("-")), std::string("\\"), std::string("-"));
#line 1046 "/src/driver.do"
    if ((nativePlatform == std::string("windows")) && !doof::string_endsWith(doof::string_toLowerCase(name), std::string(".exe"))) {
#line 1046 "/src/driver.do"
        return (name + std::string(".exe"));
    }
#line 1047 "/src/driver.do"
    return name;
}
#line 1050 "/src/driver.do"
void printDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 1051 "/src/driver.do"
    const auto displayCount = ((static_cast<int32_t>((diagnostics)->size()) < MAX_PRINTED_DIAGNOSTICS) ? static_cast<int32_t>((diagnostics)->size()) : MAX_PRINTED_DIAGNOSTICS);
#line 1052 "/src/driver.do"
    for (int32_t index = 0; index < displayCount; ++index) {
#line 1053 "/src/driver.do"
        const auto diagnostic = doof::array_at(diagnostics, index, "src/driver", 1053);
#line 1054 "/src/driver.do"
        doof::println(((((((((diagnostic->module + std::string(":")) + doof::to_string(diagnostic->span.start.line)) + std::string(":")) + doof::to_string(diagnostic->span.start.column)) + std::string(": ")) + diagnostic->severity) + std::string(": ")) + diagnostic->message));
    }
#line 1059 "/src/driver.do"
    if (static_cast<int32_t>((diagnostics)->size()) > displayCount) {
#line 1060 "/src/driver.do"
        doof::println(((std::string("... ") + doof::to_string((static_cast<int32_t>((diagnostics)->size()) - displayCount))) + std::string(" more diagnostics omitted")));
    }
}
#line 1064 "/src/driver.do"
void collectTestFiles(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results, bool root) {
#line 1065 "/src/driver.do"
    if (!::doof_fs::isDirectory(path)) {
#line 1066 "/src/driver.do"
        if (doof::string_endsWith(path, std::string(".do"))) {
#line 1066 "/src/driver.do"
            results->push_back(path);
        }
#line 1067 "/src/driver.do"
        return;
    }
#line 1069 "/src/driver.do"
    if (!root && ::doof_fs::exists(::app_src_project_::joinPath(path, std::string("doof.json")))) {
#line 1069 "/src/driver.do"
        return;
    }
#line 1070 "/src/driver.do"
    const auto entries = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1070, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 1071 "/src/driver.do"
    const auto& _iterable_93 = entries;
    for (const auto& entry : *_iterable_93) {
#line 1072 "/src/driver.do"
        const auto entryPath = ::app_src_project_::joinPath(path, entry->name);
#line 1073 "/src/driver.do"
        if (entry->kind == ::std_::fs::types::EntryKind::Directory) {
#line 1074 "/src/driver.do"
            collectTestFiles(entryPath, results, false);
        } else if ((entry->kind == ::std_::fs::types::EntryKind::File) && doof::string_endsWith(entry->name, std::string(".test.do"))) {
#line 1076 "/src/driver.do"
            results->push_back(entryPath);
        }
    }
}
#line 1081 "/src/driver.do"
std::shared_ptr<std::vector<std::string>> sortedTestFiles(const std::shared_ptr<std::vector<std::string>>& values) {
#line 1082 "/src/driver.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 1083 "/src/driver.do"
    auto last = std::string("");
#line 1084 "/src/driver.do"
    for (int32_t count = 0; count < static_cast<int32_t>((values)->size()); ++count) {
#line 1085 "/src/driver.do"
        std::optional<std::string> candidate = std::nullopt;
#line 1086 "/src/driver.do"
        const auto& _iterable_96 = values;
        for (const auto& value : *_iterable_96) {
#line 1087 "/src/driver.do"
            if (((static_cast<int32_t>((result)->size()) == 0) || (value > last)) && (doof::is_null(candidate) || (value < candidate.value()))) {
#line 1087 "/src/driver.do"
                (candidate = value);
            }
        }
#line 1089 "/src/driver.do"
        if (!doof::is_null(candidate)) {
#line 1089 "/src/driver.do"
            result->push_back(candidate.value());
#line 1089 "/src/driver.do"
            (last = candidate.value());
        }
    }
#line 1091 "/src/driver.do"
    return result;
}
#line 1094 "/src/driver.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> sortedDiscoveredTests(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>& values) {
#line 1095 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>(std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>{});
#line 1096 "/src/driver.do"
    auto last = std::string("");
#line 1097 "/src/driver.do"
    for (int32_t count = 0; count < static_cast<int32_t>((values)->size()); ++count) {
#line 1098 "/src/driver.do"
        std::shared_ptr<::app_src_test_runner_::DiscoveredTest> candidate = nullptr;
#line 1099 "/src/driver.do"
        const auto& _iterable_99 = values;
        for (const auto& value : *_iterable_99) {
#line 1100 "/src/driver.do"
            if (((static_cast<int32_t>((result)->size()) == 0) || (value->id > last)) && (doof::is_null(candidate) || (value->id < candidate->id))) {
#line 1100 "/src/driver.do"
                (candidate = value);
            }
        }
#line 1102 "/src/driver.do"
        if (!doof::is_null(candidate)) {
#line 1102 "/src/driver.do"
            result->push_back(doof::unwrap_optional(candidate));
#line 1102 "/src/driver.do"
            (last = candidate->id);
        }
    }
#line 1104 "/src/driver.do"
    return result;
}
#line 1107 "/src/driver.do"
void mergeCoverageGroup(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& groupModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& groupHits, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& allModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& allHits) {
#line 1113 "/src/driver.do"
    for (int32_t groupIndex = 0; groupIndex < static_cast<int32_t>((groupModules)->size()); ++groupIndex) {
#line 1114 "/src/driver.do"
        const auto groupModule = doof::array_at(groupModules, groupIndex, "src/driver", 1114);
#line 1115 "/src/driver.do"
        const auto diskPath = driverSourceDiskPath(groupModule->modulePath, configuredDriverSourceState->localRoots, configuredDriverSourceState->acquisitions);
#line 1120 "/src/driver.do"
        auto targetIndex = -1;
#line 1121 "/src/driver.do"
        for (int32_t index = 0; index < static_cast<int32_t>((allModules)->size()); ++index) {
#line 1122 "/src/driver.do"
            if (doof::array_at(allModules, index, "src/driver", 1122)->modulePath == diskPath) {
#line 1122 "/src/driver.do"
                (targetIndex = index);
            }
        }
#line 1124 "/src/driver.do"
        if (targetIndex < 0) {
#line 1125 "/src/driver.do"
            std::shared_ptr<std::vector<int32_t>> lines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
#line 1126 "/src/driver.do"
            const auto& _iterable_103 = groupModule->instrumentedLines;
            for (const auto& line : *_iterable_103) {
#line 1126 "/src/driver.do"
                lines->push_back(line);
            }
#line 1127 "/src/driver.do"
            allModules->push_back(std::make_shared<::app_src_emitter_module_::CoverageModuleMetadata>(static_cast<int32_t>((allModules)->size()), diskPath, lines));
#line 1132 "/src/driver.do"
            allHits->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
#line 1133 "/src/driver.do"
            (targetIndex = (static_cast<int32_t>((allModules)->size()) - 1));
        }
#line 1135 "/src/driver.do"
        if (groupIndex < static_cast<int32_t>((groupHits)->size())) {
#line 1136 "/src/driver.do"
            const auto& _iterable_105 = doof::array_at(groupHits, groupIndex, "src/driver", 1136);
            for (const auto& line : *_iterable_105) {
#line 1137 "/src/driver.do"
                auto found = false;
#line 1138 "/src/driver.do"
                const auto& _iterable_107 = doof::array_at(allHits, targetIndex, "src/driver", 1138);
                for (const auto& existing : *_iterable_107) {
#line 1138 "/src/driver.do"
                    if (existing == line) {
#line 1138 "/src/driver.do"
                        (found = true);
                    }
                }
#line 1139 "/src/driver.do"
                if (!found) {
#line 1139 "/src/driver.do"
                    doof::array_at(allHits, targetIndex, "src/driver", 1139)->push_back(line);
                }
            }
        }
    }
}
#line 1145 "/src/driver.do"
void printCoverageSummary(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report) {
#line 1146 "/src/driver.do"
    doof::println(std::string("Coverage summary:"));
#line 1147 "/src/driver.do"
    const auto& _iterable_109 = report->files;
    for (const auto& file : *_iterable_109) {
#line 1148 "/src/driver.do"
        const auto percent = ((doof::to_string((file->percentTenths / 10)) + std::string(".")) + doof::to_string((file->percentTenths % 10)));
#line 1149 "/src/driver.do"
        doof::println(((((((((std::string("  ") + file->path) + std::string(": ")) + doof::to_string(file->covered)) + std::string("/")) + doof::to_string(file->total)) + std::string(" lines (")) + percent) + std::string("%)")));
    }
#line 1151 "/src/driver.do"
    const auto overall = ((doof::to_string((report->totalPercentTenths / 10)) + std::string(".")) + doof::to_string((report->totalPercentTenths % 10)));
#line 1152 "/src/driver.do"
    doof::println(((((((std::string("Overall: ") + doof::to_string(report->totalCovered)) + std::string("/")) + doof::to_string(report->totalLines)) + std::string(" lines (")) + overall) + std::string("%)")));
}
#line 1155 "/src/driver.do"
std::string coverageHtmlPath(const std::string& jsonPath) {
#line 1156 "/src/driver.do"
    if (doof::string_endsWith(jsonPath, std::string(".json"))) {
#line 1156 "/src/driver.do"
        return (doof::string_substring(jsonPath, 0, (static_cast<int32_t>(jsonPath.size()) - 5)) + std::string(".html"));
    }
#line 1157 "/src/driver.do"
    return (jsonPath + std::string(".html"));
}
#line 1160 "/src/driver.do"
std::string writeCoverageHtml(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report, const std::string& jsonPath, const std::string& rootDirectory) {
#line 1161 "/src/driver.do"
    const auto indexPath = coverageHtmlPath(jsonPath);
#line 1162 "/src/driver.do"
    const auto filesDirectory = (doof::string_substring(indexPath, 0, (static_cast<int32_t>(indexPath.size()) - 5)) + std::string("_files"));
#line 1163 "/src/driver.do"
    const auto filesDirectoryName = ::app_src_project_::fileName(filesDirectory);
#line 1164 "/src/driver.do"
    const auto& _iterable_111 = report->files;
    for (const auto& file : *_iterable_111) {
#line 1165 "/src/driver.do"
        const auto relativePage = ::app_src_test_runner_::coverageFileRelativePath(file->path);
#line 1166 "/src/driver.do"
        const auto pagePath = ::app_src_project_::joinPath(filesDirectory, relativePage);
#line 1167 "/src/driver.do"
        ensureOutputDirectory(::app_src_project_::parentPath(pagePath));
#line 1168 "/src/driver.do"
        auto depth = 1;
#line 1169 "/src/driver.do"
        for (int32_t index = 0; index < static_cast<int32_t>(relativePage.size()); ++index) {
#line 1169 "/src/driver.do"
            if (doof::string_at(relativePage, index, "src/driver", 1169) == U'\u002F') {
#line 1169 "/src/driver.do"
                (depth += 1);
            }
        }
#line 1170 "/src/driver.do"
        const auto indexHref = (doof::string_repeat(std::string("../"), depth) + ::app_src_project_::fileName(indexPath));
#line 1171 "/src/driver.do"
        const auto sourcePath = ::app_src_project_::joinPath(rootDirectory, file->path);
#line 1172 "/src/driver.do"
        auto source = std::string("");
#line 1173 "/src/driver.do"
        if (::doof_fs::exists(sourcePath)) {
#line 1173 "/src/driver.do"
            (source = [&]() -> std::string { auto _try_value = ::doof_fs::readText(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1173, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }());
        }
#line 1174 "/src/driver.do"
        [&]() -> void { auto _try_value = ::doof_fs::writeText(pagePath, ::app_src_test_runner_::renderCoverageFileHtml(file, source, indexHref)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1174, std::string("try! failed"));  }();
    }
#line 1176 "/src/driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(indexPath, ::app_src_test_runner_::renderCoverageHtml(report, filesDirectoryName)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1176, std::string("try! failed"));  }();
#line 1177 "/src/driver.do"
    return indexPath;
}
#line 1181 "/src/driver.do"
int32_t testRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request) {
#line 1182 "/src/driver.do"
    const auto target = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->entry); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1182, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 1183 "/src/driver.do"
    if (!::doof_fs::exists(target)) {
#line 1184 "/src/driver.do"
        doof::println((std::string("error: File not found: ") + target));
#line 1185 "/src/driver.do"
        return 1;
    }
#line 1187 "/src/driver.do"
    const auto rootDirectory = (::doof_fs::isDirectory(target) ? target : ::app_src_project_::parentPath(target));
#line 1188 "/src/driver.do"
    std::shared_ptr<std::vector<std::string>> testFiles = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 1189 "/src/driver.do"
    collectTestFiles(target, testFiles, true);
#line 1190 "/src/driver.do"
    (testFiles = sortedTestFiles(testFiles));
#line 1191 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> discovered = std::make_shared<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>(std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>{});
#line 1192 "/src/driver.do"
    const auto& _iterable_114 = testFiles;
    for (const auto& testFile : *_iterable_114) {
#line 1193 "/src/driver.do"
        auto _binding_value_115 = ::doof_fs::readText(testFile);
        if (doof::is_failure(_binding_value_115)) {
            const auto& source = _binding_value_115;
#line 1194 "/src/driver.do"
            doof::println((std::string("error: Could not read test file: ") + testFile));
#line 1195 "/src/driver.do"
            return 1;
        }
        const auto source = doof::success_value(_binding_value_115);
#line 1197 "/src/driver.do"
        const auto parser = std::make_shared<::app_src_parser_::Parser>(source, std::make_shared<std::vector<::app_src_lexer_::Token>>(std::vector<::app_src_lexer_::Token>{}), 0, false, false, std::string(""), 0, 0, 0);
#line 1198 "/src/driver.do"
        const auto parsed = [&]() -> doof::Result<std::shared_ptr<::app_src_ast_::Program>, std::string> { try { return doof::Success<std::shared_ptr<::app_src_ast_::Program>>{doof::callback<std::shared_ptr<::app_src_ast_::Program>()>([parser]() -> std::shared_ptr<::app_src_ast_::Program> { return parser->parse(); }).call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }();
#line 1199 "/src/driver.do"
        auto _binding_value_116 = parsed;
        if (doof::is_failure(_binding_value_116)) {
            const auto failure = doof::failure_error(_binding_value_116);
#line 1200 "/src/driver.do"
            if (parser->errorMessage == std::string("")) {
#line 1200 "/src/driver.do"
                doof::panic(failure);
            }
#line 1201 "/src/driver.do"
            doof::println(::app_src_test_runner_::formatParseFailure(testFile, source, parser->errorLine, parser->errorColumn, parser->errorMessage));
#line 1202 "/src/driver.do"
            return 1;
        }
        const auto program = doof::success_value(_binding_value_116);
#line 1204 "/src/driver.do"
        const auto discovery = ::app_src_test_runner_::discoverModuleTests(program, testFile, rootDirectory);
#line 1205 "/src/driver.do"
        const auto& _iterable_118 = discovery->errors;
        for (const auto& error : *_iterable_118) {
#line 1205 "/src/driver.do"
            doof::println(error);
        }
#line 1206 "/src/driver.do"
        if (static_cast<int32_t>((discovery->errors)->size()) > 0) {
#line 1206 "/src/driver.do"
            return 1;
        }
#line 1207 "/src/driver.do"
        const auto& _iterable_120 = discovery->tests;
        for (const auto& test : *_iterable_120) {
#line 1207 "/src/driver.do"
            discovered->push_back(test);
        }
    }
#line 1209 "/src/driver.do"
    (discovered = sortedDiscoveredTests(discovered));
#line 1210 "/src/driver.do"
    const auto selected = ::app_src_test_runner_::filterDiscoveredTests(discovered, request->filter);
#line 1211 "/src/driver.do"
    if (static_cast<int32_t>((selected)->size()) == 0) {
#line 1212 "/src/driver.do"
        const auto suffix = ((request->filter == std::string("")) ? std::string("") : ((std::string(" matching \"") + request->filter) + std::string("\"")));
#line 1213 "/src/driver.do"
        doof::println(((std::string("error: No tests found under ") + target) + suffix));
#line 1214 "/src/driver.do"
        return 1;
    }
#line 1216 "/src/driver.do"
    if (request->listOnly) {
#line 1217 "/src/driver.do"
        const auto& _iterable_122 = selected;
        for (const auto& test : *_iterable_122) {
#line 1217 "/src/driver.do"
            doof::println(test->id);
        }
#line 1218 "/src/driver.do"
        return 0;
    }
#line 1221 "/src/driver.do"
    auto passed = 0;
#line 1222 "/src/driver.do"
    auto failed = 0;
#line 1223 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>> coverageModules = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>{});
#line 1224 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> coverageHits = std::make_shared<std::vector<std::shared_ptr<std::vector<int32_t>>>>(std::vector<std::shared_ptr<std::vector<int32_t>>>{});
#line 1225 "/src/driver.do"
    const auto groups = ::app_src_test_runner_::groupTestsForCompilation(selected);
#line 1226 "/src/driver.do"
    const auto& _iterable_124 = groups;
    for (const auto& group : *_iterable_124) {
#line 1227 "/src/driver.do"
        const auto moduleTests = group->tests;
#line 1228 "/src/driver.do"
        const auto testFile = doof::array_at(moduleTests, 0, "src/driver", 1228)->modulePath;
#line 1229 "/src/driver.do"
        const auto project = ::app_src_project_::readProjectSpec(testFile, hostPlatform(), std::string(""));
#line 1230 "/src/driver.do"
        const auto buildRoot = ((request->outputDirectory == std::string("")) ? ::app_src_project_::joinPath(project->rootDirectory, project->buildDirectory) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->outputDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1232, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
#line 1233 "/src/driver.do"
        const auto coverageSuffix = (request->coverage ? std::string("-coverage") : std::string(""));
#line 1234 "/src/driver.do"
        const auto outputDirectory = ::app_src_project_::joinPath(::app_src_project_::joinPath(buildRoot, std::string(".doof-tests")), (group->outputName + coverageSuffix));
#line 1235 "/src/driver.do"
        const auto harnessPath = ::app_src_project_::joinPath(outputDirectory, std::string("__doof_tests__.do"));
#line 1236 "/src/driver.do"
        ensureOutputDirectory(outputDirectory);
#line 1237 "/src/driver.do"
        writeTextIfChanged(harnessPath, ::app_src_test_runner_::generateTestHarness(harnessPath, moduleTests));
#line 1239 "/src/driver.do"
        const auto stdlibRoot = ::app_src_project_::environmentValue(std::string("DOOF_STDLIB_ROOT"));
#line 1240 "/src/driver.do"
        const auto rootLogicalPrefix = driverRootLogicalPrefix(project->name, project->rootDirectory);
#line 1241 "/src/driver.do"
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(rootLogicalPrefix, project->name, std::string(""))});
#line 1246 "/src/driver.do"
        auto _binding_value_125 = sourceLoaderForRequest(harnessPath, stdlibRoot, namespaceMappings, project->manifest, std::string(""), nullptr);
        if (doof::is_failure(_binding_value_125)) {
            const auto error = doof::failure_error(_binding_value_125);
#line 1249 "/src/driver.do"
            doof::println((std::string("error: ") + error));
#line 1250 "/src/driver.do"
            return 1;
        }
        const auto loader = doof::success_value(_binding_value_125);
#line 1252 "/src/driver.do"
        const auto result = ::app_src_compiler_::compileWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), driverRootLogicalPath(harnessPath, project->rootDirectory, project->name), loader, namespaceMappings, std::string("executable"), request->coverage, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), std::string(""), false);
#line 1253 "/src/driver.do"
        if (static_cast<int32_t>((result->diagnostics)->size()) > 0) {
#line 1253 "/src/driver.do"
            printDiagnostics(result->diagnostics);
        }
#line 1254 "/src/driver.do"
        if (::app_src_diagnostics_::hasErrorDiagnostics(result->diagnostics)) {
#line 1254 "/src/driver.do"
            return 1;
        }
#line 1255 "/src/driver.do"
        if (doof::is_null(result->emission)) {
#line 1255 "/src/driver.do"
            doof::panic(std::string("test compiler produced no emission"));
        }
#line 1256 "/src/driver.do"
        const auto rootManifest = project->manifest;
#line 1257 "/src/driver.do"
        const auto testExternalTarget = std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(hostPlatform(), std::string(""), std::string(""), std::string(""), 1);
#line 1258 "/src/driver.do"
        auto _binding_value_126 = resolvedDependencyInputs(rootManifest);
        if (doof::is_failure(_binding_value_126)) {
            const auto error = doof::failure_error(_binding_value_126);
#line 1259 "/src/driver.do"
            doof::println((std::string("error: ") + error));
#line 1260 "/src/driver.do"
            return 1;
        }
        const auto externalInputs = doof::success_value(_binding_value_126);
#line 1262 "/src/driver.do"
        auto _binding_value_127 = acquireResolvedExternalInputs(externalInputs, testExternalTarget);
        if (doof::is_failure(_binding_value_127)) {
            const auto error = doof::failure_error(_binding_value_127);
#line 1263 "/src/driver.do"
            doof::println((std::string("error: ") + error));
#line 1264 "/src/driver.do"
            return 1;
        }
#line 1266 "/src/driver.do"
        const auto emission = ::app_src_emitter_project_::planProjectEmission(doof::unwrap_optional(result->emission), projectNativePackages(project->rootDirectory, rootManifest, std::string("")));
#line 1267 "/src/driver.do"
        if (request->coverage) {
#line 1267 "/src/driver.do"
            emission->nativeBuild->defines->push_back(std::string("DOOF_COVERAGE"));
        }
#line 1268 "/src/driver.do"
        materializeProject(outputDirectory, emission);
#line 1269 "/src/driver.do"
        materializeRuntimeHeader(outputDirectory);
#line 1270 "/src/driver.do"
        const auto binary = ::app_src_project_::joinPath(outputDirectory, std::string("doof-tests"));
#line 1271 "/src/driver.do"
        doof::println((std::string("BUILD ") + group->outputName));
#line 1272 "/src/driver.do"
        const auto buildExitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, binary, emission, ::app_src_native_build_::NativeBuildMode::Debug, hostPlatform(), ::app_src_native_build_driver_::NativeBuildOutputMode::Progress);
#line 1275 "/src/driver.do"
        if (buildExitCode != 0) {
#line 1275 "/src/driver.do"
            return buildExitCode;
        }
#line 1277 "/src/driver.do"
        const auto& _iterable_129 = moduleTests;
        for (const auto& test : *_iterable_129) {
#line 1278 "/src/driver.do"
            const auto testResult = runNativeCommand(binary, std::make_shared<std::vector<std::string>>(std::vector<std::string>{test->id}), project->rootDirectory, !request->coverage, ::std_::os::index::ProcessGroupMode::Isolated, (request->coverage ? MAX_COVERAGE_OUTPUT_BYTES : MAX_NATIVE_COMPILER_OUTPUT_BYTES));
#line 1286 "/src/driver.do"
            if (request->coverage) {
#line 1287 "/src/driver.do"
                if (testResult->truncated) {
#line 1288 "/src/driver.do"
                    doof::println((((std::string("error: coverage output exceeded ") + doof::to_string(MAX_COVERAGE_OUTPUT_BYTES)) + std::string(" bytes for ")) + test->id));
#line 1289 "/src/driver.do"
                    return 1;
                }
#line 1291 "/src/driver.do"
                const auto output = ::doof_blob::NativeBlobReader::constructor(testResult->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((testResult->output)->size())));
#line 1292 "/src/driver.do"
                std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> groupHits = std::make_shared<std::vector<std::shared_ptr<std::vector<int32_t>>>>(std::vector<std::shared_ptr<std::vector<int32_t>>>{});
#line 1293 "/src/driver.do"
                const auto& _iterable_131 = result->emission->coverageModules;
                for (const auto& ignored : *_iterable_131) {
#line 1293 "/src/driver.do"
                    groupHits->push_back(std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
                }
#line 1294 "/src/driver.do"
                ::app_src_test_runner_::mergeCoverageOutput(output, result->emission->coverageModules, groupHits);
#line 1295 "/src/driver.do"
                mergeCoverageGroup(result->emission->coverageModules, groupHits, coverageModules, coverageHits);
#line 1296 "/src/driver.do"
                if (testResult->exitCode != 0) {
#line 1297 "/src/driver.do"
                    const auto visibleOutput = ::app_src_test_runner_::stripCoverageLines(output);
#line 1298 "/src/driver.do"
                    if (visibleOutput != std::string("")) {
#line 1298 "/src/driver.do"
                        doof::println(visibleOutput);
                    }
                }
            }
#line 1301 "/src/driver.do"
            const auto exitCode = testResult->exitCode;
#line 1302 "/src/driver.do"
            if (exitCode == 0) {
#line 1303 "/src/driver.do"
                (passed = (passed + 1));
#line 1304 "/src/driver.do"
                doof::println((std::string("PASS ") + test->id));
            } else {
#line 1306 "/src/driver.do"
                (failed = (failed + 1));
#line 1307 "/src/driver.do"
                doof::println((std::string("FAIL ") + test->id));
            }
        }
    }
#line 1311 "/src/driver.do"
    doof::println(((((std::string("Tests finished: ") + doof::to_string(passed)) + std::string(" passed, ")) + doof::to_string(failed)) + std::string(" failed")));
#line 1312 "/src/driver.do"
    if (request->coverage && (static_cast<int32_t>((coverageModules)->size()) > 0)) {
#line 1313 "/src/driver.do"
        const auto report = ::app_src_test_runner_::buildCoverageReport(coverageModules, coverageHits, rootDirectory);
#line 1314 "/src/driver.do"
        printCoverageSummary(report);
#line 1315 "/src/driver.do"
        const auto outputPath = ((request->coverageOutput == std::string("")) ? ::app_src_project_::joinPath(::app_src_project_::joinPath(rootDirectory, std::string("build")), std::string("coverage/doof-test-coverage.json")) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->coverageOutput); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1317, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
#line 1318 "/src/driver.do"
        ensureOutputDirectory(::app_src_project_::parentPath(outputPath));
#line 1319 "/src/driver.do"
        [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath, ::app_src_test_runner_::renderCoverageJson(report)); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1319, std::string("try! failed"));  }();
#line 1320 "/src/driver.do"
        doof::println((std::string("Coverage report written to ") + outputPath));
#line 1321 "/src/driver.do"
        const auto htmlPath = writeCoverageHtml(report, outputPath, rootDirectory);
#line 1322 "/src/driver.do"
        doof::println((std::string("Coverage HTML report written to ") + htmlPath));
    }
#line 1324 "/src/driver.do"
    return ((failed == 0) ? 0 : 1);
}
#line 1327 "/src/driver.do"
int32_t emitRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request) {
#line 1328 "/src/driver.do"
    if ((request->command == std::string("profile")) && (hostPlatform() != std::string("macos"))) {
#line 1329 "/src/driver.do"
        doof::println(std::string("error: doof profile is currently supported only on macOS"));
#line 1330 "/src/driver.do"
        return 1;
    }
#line 1332 "/src/driver.do"
    auto project = ::app_src_project_::readProjectSpec(request->entry, hostPlatform(), request->targetOverride);
#line 1333 "/src/driver.do"
    const auto entryError = ::app_src_project_::projectEntryRequestError(project, request->entry);
#line 1334 "/src/driver.do"
    if (entryError != std::string("")) {
#line 1335 "/src/driver.do"
        doof::println((std::string("error: ") + entryError));
#line 1336 "/src/driver.do"
        return 1;
    }
#line 1338 "/src/driver.do"
    if ((request->command == std::string("profile")) && ((project->target == std::string("wasm")) || (!doof::is_null(project->iosApp)))) {
#line 1339 "/src/driver.do"
        doof::println(std::string("error: doof profile supports native console executables and macOS applications"));
#line 1340 "/src/driver.do"
        return 1;
    }
#line 1342 "/src/driver.do"
    const auto iosDestination = ((request->command == std::string("package")) ? std::string("device") : request->iosDestination);
#line 1343 "/src/driver.do"
    const auto nativePlatform = (doof::is_null(project->iosApp) ? hostPlatform() : (std::string("ios-") + iosDestination));
#line 1344 "/src/driver.do"
    if (!doof::is_null(project->iosApp)) {
#line 1344 "/src/driver.do"
        (project = ::app_src_project_::readProjectSpec(request->entry, nativePlatform, request->targetOverride));
    }
#line 1345 "/src/driver.do"
    const auto iosMinimumVersion = (doof::is_null(project->iosApp) ? std::string("") : project->iosApp->minimumDeploymentTarget);
#line 1346 "/src/driver.do"
    auto _binding_value_132 = externalTargetForRequest(project->target, nativePlatform, iosDestination, iosMinimumVersion);
    if (doof::is_failure(_binding_value_132)) {
        const auto error = doof::failure_error(_binding_value_132);
#line 1347 "/src/driver.do"
        doof::println((std::string("error: ") + error));
#line 1348 "/src/driver.do"
        return 1;
    }
    const auto externalTarget = doof::success_value(_binding_value_132);
#line 1350 "/src/driver.do"
    const auto rootManifest = project->manifest;
#line 1351 "/src/driver.do"
    const auto entryPath = ::app_src_project_::joinPath(project->rootDirectory, project->entry);
#line 1352 "/src/driver.do"
    const auto entry = driverRootLogicalPath(entryPath, project->rootDirectory, project->name);
#line 1353 "/src/driver.do"
    const auto stdlibRoot = ::app_src_project_::environmentValue(std::string("DOOF_STDLIB_ROOT"));
#line 1354 "/src/driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{std::make_shared<::app_src_emitter_names_::ModuleNamespaceMapping>(driverRootLogicalPrefix(project->name, project->rootDirectory), project->name, std::string(""))});
#line 1359 "/src/driver.do"
    auto _binding_value_133 = sourceLoaderForRequest(entryPath, stdlibRoot, namespaceMappings, rootManifest, nativePlatform, externalTarget);
    if (doof::is_failure(_binding_value_133)) {
        const auto error = doof::failure_error(_binding_value_133);
#line 1362 "/src/driver.do"
        doof::println((std::string("error: ") + error));
#line 1363 "/src/driver.do"
        return 1;
    }
    const auto loader = doof::success_value(_binding_value_133);
#line 1365 "/src/driver.do"
    if (project->target == std::string("wasm")) {
#line 1366 "/src/driver.do"
        auto _binding_value_134 = ensureStdPackageReached(std::string("std/json"));
        if (doof::is_failure(_binding_value_134)) {
            const auto error = doof::failure_error(_binding_value_134);
#line 1367 "/src/driver.do"
            doof::println((std::string("error: ") + error));
#line 1368 "/src/driver.do"
            return 1;
        }
    }
#line 1371 "/src/driver.do"
    const auto entryMode = ((project->target == std::string("wasm")) ? std::string("wasm") : (doof::is_null(project->iosApp) ? std::string("executable") : std::string("ios-app")));
#line 1372 "/src/driver.do"
    const auto buildDirectory = ((request->outputDirectory == std::string("")) ? ::app_src_project_::joinPath(project->rootDirectory, project->buildDirectory) : [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->outputDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1374, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
#line 1375 "/src/driver.do"
    const auto outputDirectory = ((request->command == std::string("package")) ? ::app_src_project_::joinPath(buildDirectory, std::string("release")) : ((request->command == std::string("profile")) ? ::app_src_project_::joinPath(buildDirectory, std::string("profile")) : buildDirectory));
#line 1378 "/src/driver.do"
    const auto cacheDirectory = ((request->command == std::string("profile")) ? outputDirectory : buildDirectory);
#line 1379 "/src/driver.do"
    const auto frontendConfiguration = frontendConfigurationFingerprint(entry, entryMode, project->target, rootManifest, stdlibRoot, nativePlatform, externalTarget);
#line 1382 "/src/driver.do"
    const auto checkCachePath = frontendCachePath(cacheDirectory, std::string("check"));
#line 1383 "/src/driver.do"
    if ((request->command == std::string("check")) && frontendStateMatches(readFrontendState(checkCachePath), frontendConfiguration, loader)) {
#line 1384 "/src/driver.do"
        return 0;
    }
#line 1386 "/src/driver.do"
    const auto emissionCachePath = frontendCachePath(cacheDirectory, std::string("emission"));
#line 1387 "/src/driver.do"
    const auto previousEmissionState = readFrontendState(emissionCachePath);
#line 1388 "/src/driver.do"
    auto reusedFrontend = false;
#line 1389 "/src/driver.do"
    auto result = std::make_shared<::app_src_compiler_::Compilation>(nullptr, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 1390 "/src/driver.do"
    const auto cachedGraph = [&]() -> std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> { if (((((request->command == std::string("emit")) || (request->command == std::string("build"))) || (request->command == std::string("run"))) || (request->command == std::string("profile")))) { return [&]() -> std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> { if (!frontendEmissionCacheSupported(project->target)) { return nullptr; } return [&]() -> std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> { if ((frontendStateMatches(previousEmissionState, frontendConfiguration, loader) && (!doof::is_null(previousEmissionState)))) { return cachedModuleGraph(doof::unwrap_optional(previousEmissionState), outputDirectory); } return nullptr; }(); }(); } return nullptr; }();
#line 1397 "/src/driver.do"
    if (!doof::is_null(cachedGraph)) {
#line 1398 "/src/driver.do"
        (result = std::make_shared<::app_src_compiler_::Compilation>(doof::unwrap_optional(cachedGraph), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
#line 1399 "/src/driver.do"
        (reusedFrontend = true);
    } else {
#line 1401 "/src/driver.do"
        (result = ((request->command == std::string("check")) ? ::app_src_compiler_::checkWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), entry, loader, entryMode) : ::app_src_compiler_::compileWithLoader(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>(std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>{}), entry, loader, namespaceMappings, entryMode, false, ((request->command == std::string("package")) ? std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}) : reusableEmissionKeys(previousEmissionState, outputDirectory)), frontendConfiguration, (request->command == std::string("profile")))));
    }
#line 1410 "/src/driver.do"
    const auto hasCompilationErrors = ::app_src_diagnostics_::hasErrorDiagnostics(result->diagnostics);
#line 1411 "/src/driver.do"
    if ((static_cast<int32_t>((result->diagnostics)->size()) > 0) && ((request->command != std::string("run")) || hasCompilationErrors)) {
#line 1412 "/src/driver.do"
        printDiagnostics(result->diagnostics);
    }
#line 1414 "/src/driver.do"
    if (hasCompilationErrors) {
#line 1414 "/src/driver.do"
        return 1;
    }
#line 1415 "/src/driver.do"
    if ((((request->command != std::string("check")) && (request->command != std::string("package"))) && !reusedFrontend) && (static_cast<int32_t>((result->diagnostics)->size()) == 0)) {
#line 1416 "/src/driver.do"
        writeFrontendState(checkCachePath, frontendStateForCompilation(result, frontendConfiguration, rootManifest));
    }
#line 1418 "/src/driver.do"
    if ((request->command == std::string("package")) && ::app_src_dependency_policy_::hasMutableStdPackageInputs(reachedPackageInputs(rootManifest))) {
#line 1419 "/src/driver.do"
        doof::println(std::string("warning: packaging with standard packages overridden by DOOF_STDLIB_ROOT; provenance.json will record them as mutable inputs"));
    }
#line 1421 "/src/driver.do"
    auto _binding_value_135 = resolvedDependencyInputs(rootManifest);
    if (doof::is_failure(_binding_value_135)) {
        const auto error = doof::failure_error(_binding_value_135);
#line 1422 "/src/driver.do"
        doof::println((std::string("error: ") + error));
#line 1423 "/src/driver.do"
        return 1;
    }
    const auto externalInputs = doof::success_value(_binding_value_135);
#line 1425 "/src/driver.do"
    if (request->command == std::string("check")) {
#line 1426 "/src/driver.do"
        if (static_cast<int32_t>((result->diagnostics)->size()) == 0) {
#line 1427 "/src/driver.do"
            writeFrontendState(checkCachePath, frontendStateForCompilation(result, frontendConfiguration, rootManifest));
        }
#line 1429 "/src/driver.do"
        return 0;
    }
#line 1431 "/src/driver.do"
    if (doof::is_null(result->emission)) {
#line 1431 "/src/driver.do"
        doof::panic(std::string("compiler produced no emission"));
    }
#line 1432 "/src/driver.do"
    auto _binding_value_136 = acquireResolvedExternalInputs(externalInputs, externalTarget);
    if (doof::is_failure(_binding_value_136)) {
        const auto error = doof::failure_error(_binding_value_136);
#line 1433 "/src/driver.do"
        doof::println((std::string("error: ") + error));
#line 1434 "/src/driver.do"
        return 1;
    }
#line 1437 "/src/driver.do"
    const auto emission = ::app_src_emitter_project_::planProjectEmission(doof::unwrap_optional(result->emission), projectNativePackages(project->rootDirectory, rootManifest, stdlibRoot));
#line 1441 "/src/driver.do"
    materializeProject(outputDirectory, emission);
#line 1442 "/src/driver.do"
    materializeRuntimeHeader(outputDirectory);
#line 1443 "/src/driver.do"
    writeTextIfChanged(driverOutputPath(outputDirectory, std::string("provenance.json")), ::app_src_provenance_::renderBuildProvenance(reachedPackageInputs(rootManifest), externalInputs, emission->nativeBuild, configuredDriverSourceState->stdCatalog));
#line 1449 "/src/driver.do"
    if ((!reusedFrontend && (request->command != std::string("package"))) && frontendEmissionCacheSupported(project->target)) {
#line 1450 "/src/driver.do"
        const auto nextEmissionState = frontendStateForCompilation(result, frontendConfiguration, rootManifest);
#line 1451 "/src/driver.do"
        removeStaleFrontendOutputs(previousEmissionState, nextEmissionState, outputDirectory);
#line 1452 "/src/driver.do"
        writeFrontendState(emissionCachePath, nextEmissionState);
    }
#line 1454 "/src/driver.do"
    if (!doof::is_null(project->iosApp)) {
#line 1455 "/src/driver.do"
        auto _binding_value_137 = ::app_src_ios_app_driver_::configureIOSNativeBuild(outputDirectory, doof::unwrap_optional(project->iosApp), iosDestination, emission->nativeBuild);
        if (doof::is_failure(_binding_value_137)) {
            const auto error = doof::failure_error(_binding_value_137);
#line 1456 "/src/driver.do"
            doof::println((std::string("error: ") + error));
#line 1457 "/src/driver.do"
            return 1;
        }
    }
#line 1460 "/src/driver.do"
    if (((request->command == std::string("build")) || (request->command == std::string("run"))) || (request->command == std::string("profile"))) {
#line 1461 "/src/driver.do"
        if ((request->command == std::string("run")) && (project->target == std::string("wasm"))) {
#line 1462 "/src/driver.do"
            doof::println(std::string("error: doof run is not supported for --target wasm; instantiate the generated .wasm from your host runtime"));
#line 1463 "/src/driver.do"
            return 1;
        }
#line 1465 "/src/driver.do"
        const auto executableName = ((project->target == std::string("wasm")) ? (nativeBuildOutputName(project->name, std::string("")) + std::string(".wasm")) : ((!doof::is_null(project->macosApp)) ? project->macosApp->executableName : ((!doof::is_null(project->iosApp)) ? project->iosApp->executableName : nativeBuildOutputName(project->name, nativePlatform))));
#line 1466 "/src/driver.do"
        const auto outputPath = driverOutputPath(outputDirectory, executableName);
#line 1467 "/src/driver.do"
        if (doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) {
#line 1468 "/src/driver.do"
            synchronizeExecutableResources(project->resources, outputDirectory, frontendCachePath(cacheDirectory, std::string("resources")));
        }
#line 1470 "/src/driver.do"
        const auto exitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, outputPath, emission, ((request->command == std::string("profile")) ? ::app_src_native_build_::NativeBuildMode::Profile : ::app_src_native_build_::NativeBuildMode::Debug), hostPlatform(), nativeBuildOutputModeForCommand(request->command));
#line 1475 "/src/driver.do"
        if (exitCode != 0) {
#line 1475 "/src/driver.do"
            return exitCode;
        }
#line 1476 "/src/driver.do"
        if (!doof::is_null(project->iosApp)) {
#line 1477 "/src/driver.do"
            auto _binding_value_138 = ::app_src_ios_app_driver_::assembleIOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->iosApp), iosDestination);
            if (doof::is_failure(_binding_value_138)) {
                const auto error = doof::failure_error(_binding_value_138);
#line 1478 "/src/driver.do"
                doof::println((std::string("error: ") + error));
#line 1479 "/src/driver.do"
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_138);
#line 1481 "/src/driver.do"
            if (request->command == std::string("build")) {
#line 1481 "/src/driver.do"
                return 0;
            }
#line 1482 "/src/driver.do"
            if (iosDestination == std::string("device")) {
#line 1483 "/src/driver.do"
                const auto signingWorkDirectory = driverOutputPath(outputDirectory, std::string(".doof-ios-signing-resolution"));
#line 1484 "/src/driver.do"
                auto _binding_value_139 = ::app_src_ios_device_::resolveIOSDeviceSigningOptions(project->iosApp->bundleId, request->iosSignIdentity, request->iosProvisioningProfile, signingWorkDirectory, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                if (doof::is_failure(_binding_value_139)) {
                    const auto error = doof::failure_error(_binding_value_139);
#line 1490 "/src/driver.do"
                    doof::println((std::string("error: ") + error));
#line 1491 "/src/driver.do"
                    return 1;
                }
                const auto signing = doof::success_value(_binding_value_139);
#line 1493 "/src/driver.do"
                auto _binding_value_140 = ::app_src_ios_device_::signIOSDeviceApp(appPath, project->iosApp->bundleId, signing, driverOutputPath(outputDirectory, std::string(".doof-ios-sign")));
                if (doof::is_failure(_binding_value_140)) {
                    const auto error = doof::failure_error(_binding_value_140);
#line 1499 "/src/driver.do"
                    doof::println((std::string("error: ") + error));
#line 1500 "/src/driver.do"
                    return 1;
                }
#line 1502 "/src/driver.do"
                auto _binding_value_141 = ::app_src_ios_device_::resolveIOSDeviceIdentifier(request->iosDevice, driverOutputPath(outputDirectory, std::string(".doof-ios-device-discovery")));
                if (doof::is_failure(_binding_value_141)) {
                    const auto error = doof::failure_error(_binding_value_141);
#line 1506 "/src/driver.do"
                    doof::println((std::string("error: ") + error));
#line 1507 "/src/driver.do"
                    return 1;
                }
                const auto deviceIdentifier = doof::success_value(_binding_value_141);
#line 1509 "/src/driver.do"
                const auto installPlan = ::app_src_run_command_::planIOSDeviceInstall(appPath, deviceIdentifier, project->rootDirectory);
#line 1510 "/src/driver.do"
                const auto installResult = runNativeCommand(installPlan->command, installPlan->arguments, installPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
#line 1511 "/src/driver.do"
                if (installResult->error != std::string("")) {
#line 1511 "/src/driver.do"
                    doof::println((std::string("error: ") + installResult->error));
                }
#line 1512 "/src/driver.do"
                if (installResult->exitCode != 0) {
#line 1512 "/src/driver.do"
                    return installResult->exitCode;
                }
#line 1513 "/src/driver.do"
                const auto launchPlan = ::app_src_run_command_::planIOSDeviceLaunch(project->iosApp->bundleId, deviceIdentifier, project->rootDirectory);
#line 1514 "/src/driver.do"
                const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
#line 1515 "/src/driver.do"
                if (launchResult->error != std::string("")) {
#line 1515 "/src/driver.do"
                    doof::println((std::string("error: ") + launchResult->error));
                }
#line 1516 "/src/driver.do"
                return launchResult->exitCode;
            }
#line 1518 "/src/driver.do"
            const auto installPlan = ::app_src_run_command_::planIOSSimulatorInstall(appPath, project->rootDirectory);
#line 1519 "/src/driver.do"
            const auto installResult = runNativeCommand(installPlan->command, installPlan->arguments, installPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
#line 1520 "/src/driver.do"
            if (installResult->error != std::string("")) {
#line 1520 "/src/driver.do"
                doof::println((std::string("error: ") + installResult->error));
            }
#line 1521 "/src/driver.do"
            if (installResult->exitCode != 0) {
#line 1521 "/src/driver.do"
                return installResult->exitCode;
            }
#line 1522 "/src/driver.do"
            const auto launchPlan = ::app_src_run_command_::planIOSSimulatorLaunch(project->iosApp->bundleId, project->rootDirectory);
#line 1523 "/src/driver.do"
            const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
#line 1524 "/src/driver.do"
            if (launchResult->error != std::string("")) {
#line 1524 "/src/driver.do"
                doof::println((std::string("error: ") + launchResult->error));
            }
#line 1525 "/src/driver.do"
            return launchResult->exitCode;
        }
#line 1527 "/src/driver.do"
        if (!doof::is_null(project->macosApp)) {
#line 1528 "/src/driver.do"
            auto _binding_value_142 = ::app_src_macos_app_driver_::assembleMacOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->macosApp), emission->nativeBuild->libraryPaths);
            if (doof::is_failure(_binding_value_142)) {
                const auto error = doof::failure_error(_binding_value_142);
#line 1529 "/src/driver.do"
                doof::println((std::string("error: ") + error));
#line 1530 "/src/driver.do"
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_142);
#line 1532 "/src/driver.do"
            if (request->command == std::string("build")) {
#line 1532 "/src/driver.do"
                return 0;
            }
#line 1533 "/src/driver.do"
            if (request->command == std::string("profile")) {
#line 1534 "/src/driver.do"
                return runProfileTarget(request, appPath, outputPath, (appPath + std::string(".dSYM")), project->rootDirectory, buildDirectory, executableName, false);
            }
#line 1539 "/src/driver.do"
            const auto launchPlan = ::app_src_run_command_::planMacOSAppRun(appPath, project->rootDirectory);
#line 1540 "/src/driver.do"
            const auto launchResult = runNativeCommand(launchPlan->command, launchPlan->arguments, launchPlan->directory, true, ::std_::os::index::ProcessGroupMode::Isolated, 262144LL);
#line 1541 "/src/driver.do"
            if (launchResult->error != std::string("")) {
#line 1541 "/src/driver.do"
                doof::println((std::string("error: ") + launchResult->error));
            }
#line 1542 "/src/driver.do"
            return launchResult->exitCode;
        }
#line 1544 "/src/driver.do"
        if (request->command == std::string("build")) {
#line 1544 "/src/driver.do"
            return 0;
        }
#line 1545 "/src/driver.do"
        if (request->command == std::string("profile")) {
#line 1546 "/src/driver.do"
            return runProfileTarget(request, outputPath, outputPath, (outputPath + std::string(".dSYM")), project->rootDirectory, buildDirectory, executableName, true);
        }
#line 1551 "/src/driver.do"
        const auto runPlan = ::app_src_run_command_::planNativeProgramRun(outputPath, request->programArguments, project->rootDirectory);
#line 1552 "/src/driver.do"
        const auto runResult = runNativeCommand(runPlan->command, runPlan->arguments, runPlan->directory, true, ::std_::os::index::ProcessGroupMode::Inherited, 262144LL);
#line 1553 "/src/driver.do"
        if (runResult->error != std::string("")) {
#line 1553 "/src/driver.do"
            doof::println((std::string("error: ") + runResult->error));
        }
#line 1554 "/src/driver.do"
        return runResult->exitCode;
    }
#line 1556 "/src/driver.do"
    if (request->command == std::string("package")) {
#line 1557 "/src/driver.do"
        if (doof::is_null(project->packageConfig)) {
#line 1557 "/src/driver.do"
            doof::panic(std::string("project package settings were not resolved"));
        }
#line 1558 "/src/driver.do"
        const auto distDirectory = ((request->distDirectory != std::string("")) ? [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->distDirectory); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1558, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }() : project->packageConfig->distDirectory);
#line 1559 "/src/driver.do"
        ensureOutputDirectory(distDirectory);
#line 1560 "/src/driver.do"
        const auto executableName = ((project->target == std::string("wasm")) ? (nativeBuildOutputName(project->name, std::string("")) + std::string(".wasm")) : ((!doof::is_null(project->macosApp)) ? project->macosApp->executableName : ((!doof::is_null(project->iosApp)) ? project->iosApp->executableName : nativeBuildOutputName(project->name, nativePlatform))));
#line 1561 "/src/driver.do"
        const auto outputPath = ((doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) ? driverOutputPath(distDirectory, executableName) : driverOutputPath(outputDirectory, executableName));
#line 1564 "/src/driver.do"
        const auto exitCode = ::app_src_native_build_driver_::buildNativeProject(request->compiler, outputDirectory, outputPath, emission, ::app_src_native_build_::NativeBuildMode::Release, hostPlatform(), ::app_src_native_build_driver_::NativeBuildOutputMode::Progress);
#line 1567 "/src/driver.do"
        if (exitCode != 0) {
#line 1567 "/src/driver.do"
            return exitCode;
        }
#line 1568 "/src/driver.do"
        if (doof::is_null(project->macosApp) && doof::is_null(project->iosApp)) {
#line 1569 "/src/driver.do"
            materializeExecutableResources(project->resources, distDirectory);
#line 1570 "/src/driver.do"
            return 0;
        }
#line 1572 "/src/driver.do"
        if (!doof::is_null(project->iosApp)) {
#line 1573 "/src/driver.do"
            auto _binding_value_143 = ::app_src_ios_app_driver_::assembleIOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->iosApp), iosDestination);
            if (doof::is_failure(_binding_value_143)) {
                const auto error = doof::failure_error(_binding_value_143);
#line 1574 "/src/driver.do"
                doof::println((std::string("error: ") + error));
#line 1575 "/src/driver.do"
                return 1;
            }
            const auto appPath = doof::success_value(_binding_value_143);
#line 1577 "/src/driver.do"
            if (doof::is_null(project->iosPackageConfig)) {
#line 1577 "/src/driver.do"
                doof::panic(std::string("iOS package settings were not resolved"));
            }
#line 1578 "/src/driver.do"
            const auto iosConfig = doof::unwrap_optional(project->iosPackageConfig);
#line 1579 "/src/driver.do"
            const auto environmentIdentity = ::app_src_project_::environmentValue(std::string("DOOF_IOS_SIGN_IDENTITY"));
#line 1580 "/src/driver.do"
            if (environmentIdentity != std::string("")) {
#line 1580 "/src/driver.do"
                (iosConfig->identity = environmentIdentity);
            }
#line 1581 "/src/driver.do"
            if (request->iosSignIdentity != std::string("")) {
#line 1581 "/src/driver.do"
                (iosConfig->identity = request->iosSignIdentity);
            }
#line 1582 "/src/driver.do"
            const auto environmentProfile = ::app_src_project_::environmentValue(std::string("DOOF_IOS_PROVISIONING_PROFILE"));
#line 1583 "/src/driver.do"
            if (environmentProfile != std::string("")) {
#line 1583 "/src/driver.do"
                (iosConfig->provisioningProfilePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(environmentProfile); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1583, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
            }
#line 1584 "/src/driver.do"
            if (request->iosProvisioningProfile != std::string("")) {
#line 1584 "/src/driver.do"
                (iosConfig->provisioningProfilePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->iosProvisioningProfile); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1584, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
            }
#line 1585 "/src/driver.do"
            const auto archivePath = driverOutputPath(distDirectory, ::app_src_ios_app_::iosPackageArchiveName(project->iosApp->executableName, project->iosApp->version));
#line 1586 "/src/driver.do"
            auto _binding_value_144 = ::app_src_ios_app_driver_::signAndArchiveIOSApp(appPath, archivePath, project->iosApp->bundleId, iosConfig, outputDirectory);
            if (doof::is_failure(_binding_value_144)) {
                const auto error = doof::failure_error(_binding_value_144);
#line 1587 "/src/driver.do"
                doof::println((std::string("error: ") + error));
#line 1588 "/src/driver.do"
                return 1;
            }
#line 1590 "/src/driver.do"
            doof::println((std::string("Package: ") + archivePath));
#line 1591 "/src/driver.do"
            return 0;
        }
#line 1593 "/src/driver.do"
        auto _binding_value_145 = ::app_src_macos_app_driver_::assembleMacOSApp(outputDirectory, outputPath, doof::unwrap_optional(project->macosApp), emission->nativeBuild->libraryPaths);
        if (doof::is_failure(_binding_value_145)) {
            const auto error = doof::failure_error(_binding_value_145);
#line 1594 "/src/driver.do"
            doof::println((std::string("error: ") + error));
#line 1595 "/src/driver.do"
            return 1;
        }
        const auto appPath = doof::success_value(_binding_value_145);
#line 1597 "/src/driver.do"
        const auto packageConfig = doof::unwrap_optional(project->packageConfig);
#line 1598 "/src/driver.do"
        if (request->macosSigning != std::string("")) {
#line 1598 "/src/driver.do"
            (packageConfig->signing = request->macosSigning);
        }
#line 1599 "/src/driver.do"
        const auto environmentIdentity = ::app_src_project_::environmentValue(std::string("DOOF_MACOS_SIGN_IDENTITY"));
#line 1600 "/src/driver.do"
        if (environmentIdentity != std::string("")) {
#line 1600 "/src/driver.do"
            (packageConfig->identity = environmentIdentity);
        }
#line 1601 "/src/driver.do"
        if (request->macosSignIdentity != std::string("")) {
#line 1601 "/src/driver.do"
            (packageConfig->identity = request->macosSignIdentity);
        }
#line 1602 "/src/driver.do"
        if (request->macosSandbox) {
#line 1602 "/src/driver.do"
            (packageConfig->sandbox = true);
        }
#line 1603 "/src/driver.do"
        if (request->macosEntitlements != std::string("")) {
#line 1603 "/src/driver.do"
            (packageConfig->entitlementsPath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(request->macosEntitlements); if (doof::is_failure(_try_value)) doof::panic_at("src/driver", 1603, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        }
#line 1604 "/src/driver.do"
        const auto archivePath = driverOutputPath(distDirectory, ::app_src_macos_app_::macOSPackageArchiveName(project->macosApp->executableName, project->macosApp->version));
#line 1605 "/src/driver.do"
        auto _binding_value_146 = ::app_src_macos_app_driver_::signAndArchiveMacOSApp(appPath, archivePath, packageConfig, outputDirectory);
        if (doof::is_failure(_binding_value_146)) {
            const auto error = doof::failure_error(_binding_value_146);
#line 1606 "/src/driver.do"
            doof::println((std::string("error: ") + error));
#line 1607 "/src/driver.do"
            return 1;
        }
#line 1609 "/src/driver.do"
        doof::println((std::string("Package: ") + archivePath));
#line 1610 "/src/driver.do"
        return 0;
    }
#line 1612 "/src/driver.do"
    return 0;
}
#line 1615 "/src/driver.do"
int32_t doof_main(const std::shared_ptr<std::vector<std::string>>& args) {
#line 1616 "/src/driver.do"
    const auto parsed = ::app_src_cli_::parseCli(args);
#line 1617 "/src/driver.do"
    if (parsed->help) {
#line 1618 "/src/driver.do"
        doof::println(::app_src_cli_::cliUsage());
#line 1619 "/src/driver.do"
        return 0;
    }
#line 1621 "/src/driver.do"
    if (parsed->error != std::string("")) {
#line 1622 "/src/driver.do"
        doof::println((std::string("error: ") + parsed->error));
#line 1623 "/src/driver.do"
        doof::println(::app_src_cli_::cliUsage());
#line 1624 "/src/driver.do"
        return 2;
    }
#line 1626 "/src/driver.do"
    if (parsed->request->command == std::string("test")) {
#line 1626 "/src/driver.do"
        return testRequest(doof::unwrap_optional(parsed->request));
    }
#line 1627 "/src/driver.do"
    return emitRequest(doof::unwrap_optional(parsed->request));
}
#line 1 "<doof-generated>"

void __doof_initialize_module() {
        configuredDriverSourceState = std::make_shared<DriverSourceState>(std::make_shared<std::vector<std::shared_ptr<DriverSourceRoot>>>(std::vector<std::shared_ptr<DriverSourceRoot>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>(std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>{}), std::make_shared<std::vector<std::shared_ptr<DriverAcquiredSource>>>(std::vector<std::shared_ptr<DriverAcquiredSource>>{}), std::make_shared<std::vector<std::shared_ptr<DriverReachedPackage>>>(std::vector<std::shared_ptr<DriverReachedPackage>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), std::string(""), std::make_shared<::app_src_external_dependency_::ExternalDependencyTarget>(std::string(""), std::string(""), std::string(""), std::string(""), 1), std::make_shared<::app_src_package_manifest_::PackageManifest>(std::string(""), std::string("1.0"), std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<::app_src_package_manifest_::DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::string(""), nullptr, nullptr, nullptr, nullptr), std::make_shared<::app_src_std_catalog_::StdCatalog>(1, std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_std_catalog_::StdCatalogPackage>>>(std::vector<std::shared_ptr<::app_src_std_catalog_::StdCatalogPackage>>{})), std::string(""));
}
}
#line 1 "<doof-generated>"

int main(int argc, char** argv) { try { auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ::app_src_analyzer_::__doof_initialize_module(); ::app_src_emitter_names_::__doof_initialize_module(); ::std_::time::duration::__doof_initialize_module(); ::std_::time::temporal::__doof_initialize_module(); ::app_src_external_dependency_::__doof_initialize_module(); ::app_src_package_acquisition_::__doof_initialize_module(); ::app_src_driver_::__doof_initialize_module(); std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); return app_src_driver_::doof_main(std::make_shared<std::vector<std::string>>(std::move(args))); } catch (const doof::Panic& _panic) { std::cerr << "panic: " << _panic.what() << std::endl; std::abort(); } catch (const std::exception& error) { std::cerr << "error: " << error.what() << std::endl; return 1; } }
