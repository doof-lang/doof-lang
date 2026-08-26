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

#line 24 "/src/compiler.do"
std::shared_ptr<Compilation> compile(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, bool coverage) {
#line 25 "/src/compiler.do"
    return compileInternal(sources, entry, ::app_src_resolver_::noSourceLoader, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), std::string("executable"), coverage, true, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), std::string(""), false);
}
#line 28 "/src/compiler.do"
std::shared_ptr<Compilation> compileWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules, const std::string& emissionConfigurationFingerprint, bool physicalSourcePaths) {
#line 39 "/src/compiler.do"
    return compileInternal(sources, entry, loader, namespaceMappings, entryMode, coverage, true, reusableModules, emissionConfigurationFingerprint, physicalSourcePaths);
}
#line 46 "/src/compiler.do"
std::shared_ptr<Compilation> checkWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::string& entryMode) {
#line 52 "/src/compiler.do"
    return compileInternal(sources, entry, loader, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), entryMode, false, false, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>{}), std::string(""), false);
}
#line 55 "/src/compiler.do"
std::shared_ptr<Compilation> compileInternal(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::string& entryMode, bool coverage, bool emit, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules, const std::string& emissionConfigurationFingerprint, bool physicalSourcePaths) {
#line 67 "/src/compiler.do"
    ::app_src_emitter_names_::configureModuleNamespaces(namespaceMappings);
#line 68 "/src/compiler.do"
    const auto analyzer = ::app_src_analyzer_::createAnalyzerWithLoader(sources, loader);
#line 69 "/src/compiler.do"
    const auto analysis = analyzer->analyze(entry);
#line 70 "/src/compiler.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
#line 71 "/src/compiler.do"
    const auto& _iterable_2 = analysis->diagnostics;
    for (const auto& diagnostic : *_iterable_2) {
#line 71 "/src/compiler.do"
        diagnostics->push_back(diagnostic);
    }
#line 73 "/src/compiler.do"
    if (!::app_src_diagnostics_::hasErrorDiagnostics(diagnostics)) {
#line 74 "/src/compiler.do"
        const auto checker = ::app_src_checker_::createChecker(analysis, entry, entryMode);
#line 75 "/src/compiler.do"
        std::shared_ptr<std::vector<std::string>> checkedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 76 "/src/compiler.do"
        std::shared_ptr<std::vector<std::string>> visitingPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 77 "/src/compiler.do"
        const auto& _iterable_4 = analysis->modules;
        for (const auto& module : *_iterable_4) {
#line 78 "/src/compiler.do"
            checkModuleDependencies(module->path, analysis, checker, checkedPaths, visitingPaths, diagnostics);
        }
#line 80 "/src/compiler.do"
        const auto& _iterable_6 = ::app_src_checker_::validateDeepReadonlyFields(analysis);
        for (const auto& diagnostic : *_iterable_6) {
#line 80 "/src/compiler.do"
            diagnostics->push_back(diagnostic);
        }
#line 81 "/src/compiler.do"
        const auto& _iterable_8 = ::app_src_checker_::validateIsolationEffects(analysis);
        for (const auto& diagnostic : *_iterable_8) {
#line 81 "/src/compiler.do"
            diagnostics->push_back(diagnostic);
        }
    }
#line 84 "/src/compiler.do"
    if (::app_src_diagnostics_::hasErrorDiagnostics(diagnostics)) {
#line 85 "/src/compiler.do"
        return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
    }
#line 87 "/src/compiler.do"
    const auto& _iterable_10 = ::app_src_checker_::validateCheckedTypes(analysis);
    for (const auto& diagnostic : *_iterable_10) {
#line 87 "/src/compiler.do"
        diagnostics->push_back(diagnostic);
    }
#line 88 "/src/compiler.do"
    if (::app_src_diagnostics_::hasErrorDiagnostics(diagnostics)) {
#line 89 "/src/compiler.do"
        return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
    }
#line 91 "/src/compiler.do"
    if (!emit) {
#line 91 "/src/compiler.do"
        return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
    }
#line 92 "/src/compiler.do"
    const auto instantiations = ::app_src_emitter_monomorphize_::buildInstantiationPlan(analysis);
#line 93 "/src/compiler.do"
    if (instantiations->overflow) {
#line 94 "/src/compiler.do"
        auto trace = std::string("");
#line 95 "/src/compiler.do"
        const auto& _iterable_12 = instantiations->overflowTrace;
        for (const auto& item : *_iterable_12) {
#line 95 "/src/compiler.do"
            (trace = ((trace + ((trace == std::string("")) ? std::string("") : std::string(" -> "))) + item));
        }
#line 96 "/src/compiler.do"
        auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
#line 97 "/src/compiler.do"
        diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), (std::string("Generic instantiation did not converge after 256 concrete instantiations") + ((trace == std::string("")) ? std::string("") : (std::string(": ") + trace))), ::app_src_semantic_::SemanticSpan{zero, zero}, entry, std::string("")));
#line 103 "/src/compiler.do"
        return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
    }
#line 105 "/src/compiler.do"
    std::shared_ptr<::app_src_emitter_wasm_::WasmEmission> wasmEmission = nullptr;
#line 106 "/src/compiler.do"
    if (entryMode == std::string("wasm")) {
#line 107 "/src/compiler.do"
        auto _binding_value_13 = ::app_src_emitter_wasm_::emitWasmSupport(analysis, entry, instantiations);
        if (doof::is_failure(_binding_value_13)) {
            const auto message = doof::failure_error(_binding_value_13);
#line 108 "/src/compiler.do"
            auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
#line 109 "/src/compiler.do"
            diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, ::app_src_semantic_::SemanticSpan{zero, zero}, entry, std::string("")));
#line 110 "/src/compiler.do"
            return std::make_shared<Compilation>(nullptr, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
        }
        const auto wasm = doof::success_value(_binding_value_13);
#line 112 "/src/compiler.do"
        (wasmEmission = wasm);
    }
#line 114 "/src/compiler.do"
    const auto emission = ::app_src_emitter_module_::emitModuleGraph(analysis, entry, instantiations, entryMode, coverage, reusableModules, emissionConfigurationFingerprint, physicalSourcePaths);
#line 118 "/src/compiler.do"
    if (!doof::is_null(wasmEmission)) {
#line 119 "/src/compiler.do"
        (emission->wasmSupportSource = wasmEmission->source);
#line 120 "/src/compiler.do"
        (emission->wasmExportNames = wasmEmission->exportNames);
    }
#line 122 "/src/compiler.do"
    return std::make_shared<Compilation>(emission, diagnostics, analyzer->resolver->sources, analyzer->resolver->loadedPaths);
}
#line 128 "/src/compiler.do"
void checkModuleDependencies(const std::string& path, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<::app_src_checker_::ModuleChecker>& checker, const std::shared_ptr<std::vector<std::string>>& checkedPaths, const std::shared_ptr<std::vector<std::string>>& visitingPaths, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 136 "/src/compiler.do"
    if (containsPath(checkedPaths, path) || containsPath(visitingPaths, path)) {
#line 136 "/src/compiler.do"
        return;
    }
#line 137 "/src/compiler.do"
    const auto module = findAnalysisModule(analysis, path);
#line 138 "/src/compiler.do"
    if (doof::is_null(module)) {
#line 138 "/src/compiler.do"
        return;
    }
#line 139 "/src/compiler.do"
    visitingPaths->push_back(path);
#line 140 "/src/compiler.do"
    const auto& _iterable_15 = module->imports;
    for (const auto& imported : *_iterable_15) {
#line 141 "/src/compiler.do"
        checkModuleDependencies(imported->sourceModule, analysis, checker, checkedPaths, visitingPaths, diagnostics);
    }
#line 143 "/src/compiler.do"
    const auto& _iterable_17 = module->reExports;
    for (const auto& reExport : *_iterable_17) {
#line 144 "/src/compiler.do"
        checkModuleDependencies(reExport, analysis, checker, checkedPaths, visitingPaths, diagnostics);
    }
#line 146 "/src/compiler.do"
    auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(visitingPaths); if (doof::is_failure(_try_value)) doof::panic_at("src/compiler", 146, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 147 "/src/compiler.do"
    const auto checked = checker->check(path);
#line 148 "/src/compiler.do"
    const auto& _iterable_19 = checked->diagnostics;
    for (const auto& diagnostic : *_iterable_19) {
#line 148 "/src/compiler.do"
        diagnostics->push_back(diagnostic);
    }
#line 149 "/src/compiler.do"
    checkedPaths->push_back(path);
}
#line 152 "/src/compiler.do"
bool containsPath(const std::shared_ptr<std::vector<std::string>>& paths, const std::string& path) {
#line 153 "/src/compiler.do"
    const auto& _iterable_21 = paths;
    for (const auto& existing : *_iterable_21) {
#line 153 "/src/compiler.do"
        if (existing == path) {
#line 153 "/src/compiler.do"
            return true;
        }
    }
#line 154 "/src/compiler.do"
    return false;
}
#line 157 "/src/compiler.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findAnalysisModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
#line 158 "/src/compiler.do"
    const auto& _iterable_23 = result->modules;
    for (const auto& module : *_iterable_23) {
#line 158 "/src/compiler.do"
        if (module->path == path) {
#line 158 "/src/compiler.do"
            return module;
        }
    }
#line 159 "/src/compiler.do"
    return nullptr;
}
#line 1 "<doof-generated>"
}
