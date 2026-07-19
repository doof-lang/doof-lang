#include "src_compiler.hpp"
#include <cmath>
#include "src_analyzer.hpp"
#include "src_emitter_module.hpp"
#include "src_emitter_monomorphize.hpp"
#include "src_emitter_wasm.hpp"
#include "src_emitter_names.hpp"
#include "src_checker.hpp"
#include "src_resolver.hpp"
#include "src_semantic.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_compiler_ {
using namespace ::app_src_analyzer_;
using namespace ::app_src_emitter_module_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_wasm_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_checker_;
using namespace ::app_src_resolver_;
using namespace ::app_src_semantic_;

doof::JsonObject Compilation::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["emission"] = (this->emission ? doof::json_value(this->emission->toJsonObject()) : doof::json_value(nullptr));
    (*_json)["diagnostics"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->diagnostics->size()); for (const auto& _element : *this->diagnostics) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<Compilation>, std::string> Compilation::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_emission = _object->find("emission");
    if (_iterator_emission == _object->end()) { return doof::Failure<std::string>{"Missing required field \"emission\""}; }
    if (!(doof::json_is_null(_iterator_emission->second) || doof::json_is_object(_iterator_emission->second))) { return doof::Failure<std::string>{"Field \"emission\" expected object or null but got " + std::string(doof::json_type_name(_iterator_emission->second))}; }
    auto _field_emission = (doof::json_is_null(_iterator_emission->second) ? nullptr : doof::success_value(::app_src_emitter_module_::ModuleGraphEmission::fromJsonValue(_iterator_emission->second, _lenient)));
    auto _iterator_diagnostics = _object->find("diagnostics");
    if (_iterator_diagnostics == _object->end()) { return doof::Failure<std::string>{"Missing required field \"diagnostics\""}; }
    if (!(doof::json_is_array(_iterator_diagnostics->second))) { return doof::Failure<std::string>{"Field \"diagnostics\" expected array but got " + std::string(doof::json_type_name(_iterator_diagnostics->second))}; }
    auto _field_diagnostics = [&]() { const auto* _array = doof::json_as_array(_iterator_diagnostics->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_semantic_::Diagnostic::fromJsonValue(_element, _lenient))); } return _values; }();
    return doof::Success<std::shared_ptr<Compilation>>{std::make_shared<Compilation>(_field_emission, _field_diagnostics)};
}
std::shared_ptr<Compilation> compile(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, std::string entry, bool coverage) {
    return compileInternal(sources, entry, ::app_src_resolver_::noSourceLoader, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>{}), std::string("executable"), coverage);
}
std::shared_ptr<Compilation> compileWithLoader(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, std::string entry, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings, std::string entryMode, bool coverage) {
    return compileInternal(sources, entry, loader, namespaceMappings, entryMode, coverage);
}
std::shared_ptr<Compilation> compileInternal(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, std::string entry, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings, std::string entryMode, bool coverage) {
    ::app_src_emitter_names_::configureModuleNamespaces(namespaceMappings);
    const auto analysis = ::app_src_analyzer_::createAnalyzerWithLoader(sources, loader)->analyze(entry);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
    const auto& _iterable_1 = analysis->diagnostics;
    for (const auto& diagnostic : *_iterable_1) {
        diagnostics->push_back(diagnostic);
    }
    if (static_cast<int32_t>((diagnostics)->size()) == 0) {
        const auto checker = ::app_src_checker_::createChecker(analysis);
        std::shared_ptr<std::vector<std::string>> checkedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        std::shared_ptr<std::vector<std::string>> visitingPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_2 = analysis->modules;
        for (const auto& module : *_iterable_2) {
            checkModuleDependencies(module->path, analysis, checker, checkedPaths, visitingPaths, diagnostics);
        }
    }
    if (static_cast<int32_t>((diagnostics)->size()) > 0) {
        return std::make_shared<Compilation>(nullptr, diagnostics);
    }
    const auto& _iterable_3 = ::app_src_checker_::validateCheckedTypes(analysis);
    for (const auto& diagnostic : *_iterable_3) {
        diagnostics->push_back(diagnostic);
    }
    if (static_cast<int32_t>((diagnostics)->size()) > 0) {
        return std::make_shared<Compilation>(nullptr, diagnostics);
    }
    const auto instantiations = ::app_src_emitter_monomorphize_::buildInstantiationPlan(analysis);
    if (instantiations->overflow) {
        auto trace = std::string("");
        const auto& _iterable_4 = instantiations->overflowTrace;
        for (const auto& item : *_iterable_4) {
            (trace = ((trace + ((trace == std::string("")) ? std::string("") : std::string(" -> "))) + item));
        }
        auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
        diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), (std::string("Generic instantiation did not converge after 256 concrete instantiations") + ((trace == std::string("")) ? std::string("") : (std::string(": ") + trace))), ::app_src_semantic_::SemanticSpan{zero, zero}, entry));
        return std::make_shared<Compilation>(nullptr, diagnostics);
    }
    const auto emission = ::app_src_emitter_module_::emitModuleGraph(analysis, entry, instantiations, entryMode, coverage);
    if (entryMode == std::string("wasm")) {
        auto _binding_value_5 = ::app_src_emitter_wasm_::emitWasmSupport(analysis, entry);
        if (doof::is_failure(_binding_value_5)) {
            const auto message = doof::failure_error(_binding_value_5);
            auto zero = ::app_src_semantic_::SemanticLocation{0, 0, 0};
            diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, ::app_src_semantic_::SemanticSpan{zero, zero}, entry));
            return std::make_shared<Compilation>(nullptr, diagnostics);
        }
        const auto wasm = doof::success_value(_binding_value_5);
        (emission->wasmSupportSource = wasm->source);
        (emission->wasmExportNames = wasm->exportNames);
    }
    return std::make_shared<Compilation>(emission, diagnostics);
}
void checkModuleDependencies(std::string path, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<::app_src_checker_::ModuleChecker> checker, std::shared_ptr<std::vector<std::string>> checkedPaths, std::shared_ptr<std::vector<std::string>> visitingPaths, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) {
    if (containsPath(checkedPaths, path) || containsPath(visitingPaths, path)) {
        return;
    }
    const auto module = findAnalysisModule(analysis, path);
    if (doof::is_null(module)) {
        return;
    }
    visitingPaths->push_back(path);
    const auto& _iterable_6 = module->imports;
    for (const auto& imported : *_iterable_6) {
        checkModuleDependencies(imported->sourceModule, analysis, checker, checkedPaths, visitingPaths, diagnostics);
    }
    const auto& _iterable_7 = module->reExports;
    for (const auto& reExport : *_iterable_7) {
        checkModuleDependencies(reExport, analysis, checker, checkedPaths, visitingPaths, diagnostics);
    }
    auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(visitingPaths); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    const auto checked = checker->check(path);
    const auto& _iterable_8 = checked->diagnostics;
    for (const auto& diagnostic : *_iterable_8) {
        diagnostics->push_back(diagnostic);
    }
    checkedPaths->push_back(path);
}
bool containsPath(std::shared_ptr<std::vector<std::string>> paths, std::string path) {
    const auto& _iterable_9 = paths;
    for (const auto& existing : *_iterable_9) {
        if (existing == path) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findAnalysisModule(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path) {
    const auto& _iterable_10 = result->modules;
    for (const auto& module : *_iterable_10) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
}
