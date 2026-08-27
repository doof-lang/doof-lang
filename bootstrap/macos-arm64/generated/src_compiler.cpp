#include "src_compiler.hpp"

namespace app_src_compiler_ {
using namespace ::app_src_analyzer_;
using namespace ::app_src_emitter_module_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_wasm_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_checker_;
using namespace ::app_src_diagnostics_;
using namespace ::app_src_resolver_;
using namespace ::app_src_semantic_;

std::shared_ptr<Compilation> compile(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, bool coverage) {
    return compileInternal(sources, entry, ::app_src_resolver_::noSourceLoader, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), std::string("executable"), coverage, true, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), std::string(""), false);
}
std::shared_ptr<Compilation> compileWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules, const std::string& emissionConfigurationFingerprint, bool physicalSourcePaths) {
    return compileInternal(sources, entry, loader, namespaceMappings, entryMode, coverage, true, reusableModules, emissionConfigurationFingerprint, physicalSourcePaths);
}
std::shared_ptr<Compilation> checkWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::string& entryMode) {
    return compileInternal(sources, entry, loader, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), entryMode, false, false, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), std::string(""), false);
}
std::shared_ptr<Compilation> compileInternal(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::string& entryMode, bool coverage, bool emit, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules, const std::string& emissionConfigurationFingerprint, bool physicalSourcePaths) {
    ::app_src_emitter_names_::configureModuleNamespaces(namespaceMappings);
    const auto analyzer = ::app_src_analyzer_::createAnalyzerWithLoader(sources, loader);
    const auto analysis = analyzer->analyze(entry);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
    const auto& _iterable_2 = analysis->diagnostics;
    for (const auto& diagnostic : *_iterable_2) {
        diagnostics->push_back(diagnostic);
    }
    if (!::app_src_diagnostics_::hasErrorDiagnostics(diagnostics)) {
        const auto checker = ::app_src_checker_::createChecker(analysis, entry, entryMode);
        std::shared_ptr<std::vector<std::string>> checkedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        std::shared_ptr<std::vector<std::string>> visitingPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_4 = analysis->modules;
        for (const auto& module : *_iterable_4) {
            checkModuleDependencies(module->path, analysis, checker, checkedPaths, visitingPaths, diagnostics);
        }
        const auto& _iterable_6 = ::app_src_checker_::validateDeepReadonlyFields(analysis);
        for (const auto& diagnostic : *_iterable_6) {
            diagnostics->push_back(diagnostic);
        }
        const auto& _iterable_8 = ::app_src_checker_::validateIsolationEffects(analysis);
        for (const auto& diagnostic : *_iterable_8) {
            diagnostics->push_back(diagnostic);
        }
    }
    if (::app_src_diagnostics_::hasErrorDiagnostics(diagnostics)) {
        return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
    }
    const auto& _iterable_10 = ::app_src_checker_::validateCheckedTypes(analysis);
    for (const auto& diagnostic : *_iterable_10) {
        diagnostics->push_back(diagnostic);
    }
    if (::app_src_diagnostics_::hasErrorDiagnostics(diagnostics)) {
        return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
    }
    if (!emit) {
        return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
    }
    const auto instantiations = ::app_src_emitter_monomorphize_::buildInstantiationPlan(analysis);
    if (instantiations->overflow) {
        auto trace = std::string("");
        const auto& _iterable_12 = instantiations->overflowTrace;
        for (const auto& item : *_iterable_12) {
            (trace = ((trace + ((trace == std::string("")) ? std::string("") : std::string(" -> "))) + item));
        }
        auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
        diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), (std::string("Generic instantiation did not converge after 256 concrete instantiations") + ((trace == std::string("")) ? std::string("") : (std::string(": ") + trace))), ::app_src_semantic_::SemanticSpan{zero, zero}, entry, std::string("")));
        return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
    }
    std::shared_ptr<::app_src_emitter_wasm_::WasmEmission> wasmEmission = nullptr;
    if (entryMode == std::string("wasm")) {
        auto _binding_value_13 = ::app_src_emitter_wasm_::emitWasmSupport(analysis, entry, instantiations);
        if (doof::is_failure(_binding_value_13)) {
            const auto message = doof::failure_error(_binding_value_13);
            auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
            diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, ::app_src_semantic_::SemanticSpan{zero, zero}, entry, std::string("")));
            return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
        }
        const auto wasm = doof::success_value(_binding_value_13);
        (wasmEmission = wasm);
    }
    const auto emission = ::app_src_emitter_module_::emitModuleGraph(analysis, entry, instantiations, entryMode, coverage, reusableModules, emissionConfigurationFingerprint, physicalSourcePaths);
    if (!doof::is_null(wasmEmission)) {
        (emission->wasmSupportSource = wasmEmission->source);
        (emission->wasmExportNames = wasmEmission->exportNames);
    }
    return std::make_shared<Compilation>(emission, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
}
void checkModuleDependencies(const std::string& path, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<::app_src_checker_::ModuleChecker>& checker, const std::shared_ptr<std::vector<std::string>>& checkedPaths, const std::shared_ptr<std::vector<std::string>>& visitingPaths, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
    if (containsPath(checkedPaths, path) || containsPath(visitingPaths, path)) {
        return;
    }
    const auto module = findAnalysisModule(analysis, path);
    if (doof::is_null(module)) {
        return;
    }
    visitingPaths->push_back(path);
    const auto& _iterable_15 = module->imports;
    for (const auto& imported : *_iterable_15) {
        checkModuleDependencies(imported->sourceModule, analysis, checker, checkedPaths, visitingPaths, diagnostics);
    }
    const auto& _iterable_17 = module->reExports;
    for (const auto& reExport : *_iterable_17) {
        checkModuleDependencies(reExport, analysis, checker, checkedPaths, visitingPaths, diagnostics);
    }
    auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(visitingPaths); if (doof::is_failure(_try_value)) doof::panic_at("src/compiler", 146, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    const auto checked = checker->check(path);
    const auto& _iterable_19 = checked->diagnostics;
    for (const auto& diagnostic : *_iterable_19) {
        diagnostics->push_back(diagnostic);
    }
    checkedPaths->push_back(path);
}
bool containsPath(const std::shared_ptr<std::vector<std::string>>& paths, const std::string& path) {
    const auto& _iterable_21 = paths;
    for (const auto& existing : *_iterable_21) {
        if (existing == path) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findAnalysisModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
    const auto& _iterable_23 = result->modules;
    for (const auto& module : *_iterable_23) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
}
