#include "src_emitter_module.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_analyzer.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_decl.hpp"
#include "src_emitter_json.hpp"
#include "src_emitter_metadata.hpp"
#include "src_emitter_header.hpp"
#include "src_emitter_monomorphize.hpp"
#include "src_emitter_names.hpp"
#include "src_semantic.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_module_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_decl_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_metadata_;
using namespace ::app_src_emitter_header_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_semantic_;

doof::JsonObject ModulePlan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["path"] = doof::json_value(this->path);
    (*_json)["namespaceName"] = doof::json_value(this->namespaceName);
    (*_json)["headerName"] = doof::json_value(this->headerName);
    (*_json)["sourceName"] = doof::json_value(this->sourceName);
    (*_json)["includes"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->includes->size()); for (const auto& _element : *this->includes) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<ModulePlan>, std::string> ModulePlan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_path = _object->find("path");
    if (_iterator_path == _object->end()) { return doof::Failure<std::string>{"Missing required field \"path\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
    auto _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    auto _iterator_namespaceName = _object->find("namespaceName");
    if (_iterator_namespaceName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"namespaceName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_namespaceName->second) : doof::json_is_string(_iterator_namespaceName->second)))) { return doof::Failure<std::string>{"Field \"namespaceName\" expected string but got " + std::string(doof::json_type_name(_iterator_namespaceName->second))}; }
    auto _field_namespaceName = (_lenient ? doof::json_as_string_lenient(_iterator_namespaceName->second) : doof::json_as_string(_iterator_namespaceName->second));
    auto _iterator_headerName = _object->find("headerName");
    if (_iterator_headerName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"headerName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_headerName->second) : doof::json_is_string(_iterator_headerName->second)))) { return doof::Failure<std::string>{"Field \"headerName\" expected string but got " + std::string(doof::json_type_name(_iterator_headerName->second))}; }
    auto _field_headerName = (_lenient ? doof::json_as_string_lenient(_iterator_headerName->second) : doof::json_as_string(_iterator_headerName->second));
    auto _iterator_sourceName = _object->find("sourceName");
    if (_iterator_sourceName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceName->second) : doof::json_is_string(_iterator_sourceName->second)))) { return doof::Failure<std::string>{"Field \"sourceName\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceName->second))}; }
    auto _field_sourceName = (_lenient ? doof::json_as_string_lenient(_iterator_sourceName->second) : doof::json_as_string(_iterator_sourceName->second));
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_includes;
    if (auto _iterator_includes = _object->find("includes"); _iterator_includes != _object->end()) {
        if (!(doof::json_is_array(_iterator_includes->second))) { return doof::Failure<std::string>{"Field \"includes\" expected array but got " + std::string(doof::json_type_name(_iterator_includes->second))}; }
        _field_includes = [&]() { const auto* _array = doof::json_as_array(_iterator_includes->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_includes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    return doof::Success<std::shared_ptr<ModulePlan>>{std::make_shared<ModulePlan>(_field_path, _field_namespaceName, _field_headerName, _field_sourceName, _field_includes.value())};
}

doof::JsonObject ModuleGraphPlan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["modules"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->modules->size()); for (const auto& _element : *this->modules) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<ModuleGraphPlan>, std::string> ModuleGraphPlan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ModulePlan>>>> _field_modules;
    if (auto _iterator_modules = _object->find("modules"); _iterator_modules != _object->end()) {
        if (!(doof::json_is_array(_iterator_modules->second))) { return doof::Failure<std::string>{"Field \"modules\" expected array but got " + std::string(doof::json_type_name(_iterator_modules->second))}; }
        _field_modules = [&]() { const auto* _array = doof::json_as_array(_iterator_modules->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(ModulePlan::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_modules = std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(std::vector<std::shared_ptr<ModulePlan>>{});
    }
    return doof::Success<std::shared_ptr<ModuleGraphPlan>>{std::make_shared<ModuleGraphPlan>(_field_modules.value())};
}
std::shared_ptr<ModuleGraphPlan> planModuleGraph(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    const auto plan = std::make_shared<ModuleGraphPlan>(std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(std::vector<std::shared_ptr<ModulePlan>>{}));
    const auto& _iterable_1 = result->modules;
    for (const auto& info : *_iterable_1) {
        const auto module = std::make_shared<ModulePlan>(info->path, ::app_src_emitter_names_::moduleNamespace(info->path), ::app_src_emitter_names_::moduleHeaderName(info->path), ::app_src_emitter_names_::moduleSourceName(info->path), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        const auto& _iterable_2 = info->imports;
        for (const auto& imported : *_iterable_2) {
            addInclude(module, imported->sourceModule);
        }
        const auto& _iterable_3 = info->namespaceImports;
        for (const auto& imported : *_iterable_3) {
            addInclude(module, imported->sourceModule);
        }
        const auto& _iterable_4 = info->reExports;
        for (const auto& reExport : *_iterable_4) {
            addInclude(module, reExport);
        }
        plan->modules->push_back(module);
    }
    return plan;
}
void addInclude(std::shared_ptr<ModulePlan> module, std::string sourceModule) {
    const auto includeName = ::app_src_emitter_names_::moduleHeaderName(sourceModule);
    const auto& _iterable_5 = module->includes;
    for (const auto& existing : *_iterable_5) {
        if (existing == includeName) {
            return;
        }
    }
    module->includes->push_back(includeName);
}

doof::JsonObject ModuleEmission::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["modulePath"] = doof::json_value(this->modulePath);
    (*_json)["header"] = doof::json_value(this->header);
    (*_json)["source"] = doof::json_value(this->source);
    (*_json)["headerName"] = doof::json_value(this->headerName);
    (*_json)["sourceName"] = doof::json_value(this->sourceName);
    (*_json)["coverageModuleId"] = doof::json_value(this->coverageModuleId);
    (*_json)["instrumentedLines"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->instrumentedLines->size()); for (const auto& _element : *this->instrumentedLines) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<ModuleEmission>, std::string> ModuleEmission::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_modulePath = _object->find("modulePath");
    if (_iterator_modulePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"modulePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_modulePath->second) : doof::json_is_string(_iterator_modulePath->second)))) { return doof::Failure<std::string>{"Field \"modulePath\" expected string but got " + std::string(doof::json_type_name(_iterator_modulePath->second))}; }
    auto _field_modulePath = (_lenient ? doof::json_as_string_lenient(_iterator_modulePath->second) : doof::json_as_string(_iterator_modulePath->second));
    auto _iterator_header = _object->find("header");
    if (_iterator_header == _object->end()) { return doof::Failure<std::string>{"Missing required field \"header\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_header->second) : doof::json_is_string(_iterator_header->second)))) { return doof::Failure<std::string>{"Field \"header\" expected string but got " + std::string(doof::json_type_name(_iterator_header->second))}; }
    auto _field_header = (_lenient ? doof::json_as_string_lenient(_iterator_header->second) : doof::json_as_string(_iterator_header->second));
    auto _iterator_source = _object->find("source");
    if (_iterator_source == _object->end()) { return doof::Failure<std::string>{"Missing required field \"source\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_source->second) : doof::json_is_string(_iterator_source->second)))) { return doof::Failure<std::string>{"Field \"source\" expected string but got " + std::string(doof::json_type_name(_iterator_source->second))}; }
    auto _field_source = (_lenient ? doof::json_as_string_lenient(_iterator_source->second) : doof::json_as_string(_iterator_source->second));
    auto _iterator_headerName = _object->find("headerName");
    if (_iterator_headerName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"headerName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_headerName->second) : doof::json_is_string(_iterator_headerName->second)))) { return doof::Failure<std::string>{"Field \"headerName\" expected string but got " + std::string(doof::json_type_name(_iterator_headerName->second))}; }
    auto _field_headerName = (_lenient ? doof::json_as_string_lenient(_iterator_headerName->second) : doof::json_as_string(_iterator_headerName->second));
    auto _iterator_sourceName = _object->find("sourceName");
    if (_iterator_sourceName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceName->second) : doof::json_is_string(_iterator_sourceName->second)))) { return doof::Failure<std::string>{"Field \"sourceName\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceName->second))}; }
    auto _field_sourceName = (_lenient ? doof::json_as_string_lenient(_iterator_sourceName->second) : doof::json_as_string(_iterator_sourceName->second));
    std::optional<int32_t> _field_coverageModuleId;
    if (auto _iterator_coverageModuleId = _object->find("coverageModuleId"); _iterator_coverageModuleId != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_coverageModuleId->second) : doof::json_is_number(_iterator_coverageModuleId->second)))) { return doof::Failure<std::string>{"Field \"coverageModuleId\" expected number but got " + std::string(doof::json_type_name(_iterator_coverageModuleId->second))}; }
        _field_coverageModuleId = (_lenient ? doof::json_as_int_lenient(_iterator_coverageModuleId->second) : doof::json_as_int(_iterator_coverageModuleId->second));
    } else {
        _field_coverageModuleId = -1;
    }
    std::optional<std::shared_ptr<std::vector<int32_t>>> _field_instrumentedLines;
    if (auto _iterator_instrumentedLines = _object->find("instrumentedLines"); _iterator_instrumentedLines != _object->end()) {
        if (!(doof::json_is_array(_iterator_instrumentedLines->second))) { return doof::Failure<std::string>{"Field \"instrumentedLines\" expected array but got " + std::string(doof::json_type_name(_iterator_instrumentedLines->second))}; }
        _field_instrumentedLines = [&]() { const auto* _array = doof::json_as_array(_iterator_instrumentedLines->second); auto _values = std::make_shared<std::vector<int32_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_instrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    }
    return doof::Success<std::shared_ptr<ModuleEmission>>{std::make_shared<ModuleEmission>(_field_modulePath, _field_header, _field_source, _field_headerName, _field_sourceName, _field_coverageModuleId.value(), _field_instrumentedLines.value())};
}

doof::JsonObject CoverageModuleMetadata::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["moduleId"] = doof::json_value(this->moduleId);
    (*_json)["modulePath"] = doof::json_value(this->modulePath);
    (*_json)["instrumentedLines"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->instrumentedLines->size()); for (const auto& _element : *this->instrumentedLines) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<CoverageModuleMetadata>, std::string> CoverageModuleMetadata::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_moduleId = _object->find("moduleId");
    if (_iterator_moduleId == _object->end()) { return doof::Failure<std::string>{"Missing required field \"moduleId\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_moduleId->second) : doof::json_is_number(_iterator_moduleId->second)))) { return doof::Failure<std::string>{"Field \"moduleId\" expected number but got " + std::string(doof::json_type_name(_iterator_moduleId->second))}; }
    auto _field_moduleId = (_lenient ? doof::json_as_int_lenient(_iterator_moduleId->second) : doof::json_as_int(_iterator_moduleId->second));
    auto _iterator_modulePath = _object->find("modulePath");
    if (_iterator_modulePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"modulePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_modulePath->second) : doof::json_is_string(_iterator_modulePath->second)))) { return doof::Failure<std::string>{"Field \"modulePath\" expected string but got " + std::string(doof::json_type_name(_iterator_modulePath->second))}; }
    auto _field_modulePath = (_lenient ? doof::json_as_string_lenient(_iterator_modulePath->second) : doof::json_as_string(_iterator_modulePath->second));
    std::optional<std::shared_ptr<std::vector<int32_t>>> _field_instrumentedLines;
    if (auto _iterator_instrumentedLines = _object->find("instrumentedLines"); _iterator_instrumentedLines != _object->end()) {
        if (!(doof::json_is_array(_iterator_instrumentedLines->second))) { return doof::Failure<std::string>{"Field \"instrumentedLines\" expected array but got " + std::string(doof::json_type_name(_iterator_instrumentedLines->second))}; }
        _field_instrumentedLines = [&]() { const auto* _array = doof::json_as_array(_iterator_instrumentedLines->second); auto _values = std::make_shared<std::vector<int32_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_instrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    }
    return doof::Success<std::shared_ptr<CoverageModuleMetadata>>{std::make_shared<CoverageModuleMetadata>(_field_moduleId, _field_modulePath, _field_instrumentedLines.value())};
}

doof::JsonObject ModuleGraphEmission::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["modules"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->modules->size()); for (const auto& _element : *this->modules) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["coverageModules"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->coverageModules->size()); for (const auto& _element : *this->coverageModules) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["wasmSupportSource"] = doof::json_value(this->wasmSupportSource);
    (*_json)["wasmExportNames"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->wasmExportNames->size()); for (const auto& _element : *this->wasmExportNames) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<ModuleGraphEmission>, std::string> ModuleGraphEmission::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ModuleEmission>>>> _field_modules;
    if (auto _iterator_modules = _object->find("modules"); _iterator_modules != _object->end()) {
        if (!(doof::json_is_array(_iterator_modules->second))) { return doof::Failure<std::string>{"Field \"modules\" expected array but got " + std::string(doof::json_type_name(_iterator_modules->second))}; }
        _field_modules = [&]() { const auto* _array = doof::json_as_array(_iterator_modules->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(ModuleEmission::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_modules = std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(std::vector<std::shared_ptr<ModuleEmission>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<CoverageModuleMetadata>>>> _field_coverageModules;
    if (auto _iterator_coverageModules = _object->find("coverageModules"); _iterator_coverageModules != _object->end()) {
        if (!(doof::json_is_array(_iterator_coverageModules->second))) { return doof::Failure<std::string>{"Field \"coverageModules\" expected array but got " + std::string(doof::json_type_name(_iterator_coverageModules->second))}; }
        _field_coverageModules = [&]() { const auto* _array = doof::json_as_array(_iterator_coverageModules->second); auto _values = std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(CoverageModuleMetadata::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_coverageModules = std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(std::vector<std::shared_ptr<CoverageModuleMetadata>>{});
    }
    std::optional<std::string> _field_wasmSupportSource;
    if (auto _iterator_wasmSupportSource = _object->find("wasmSupportSource"); _iterator_wasmSupportSource != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_wasmSupportSource->second) : doof::json_is_string(_iterator_wasmSupportSource->second)))) { return doof::Failure<std::string>{"Field \"wasmSupportSource\" expected string but got " + std::string(doof::json_type_name(_iterator_wasmSupportSource->second))}; }
        _field_wasmSupportSource = (_lenient ? doof::json_as_string_lenient(_iterator_wasmSupportSource->second) : doof::json_as_string(_iterator_wasmSupportSource->second));
    } else {
        _field_wasmSupportSource = std::string("");
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_wasmExportNames;
    if (auto _iterator_wasmExportNames = _object->find("wasmExportNames"); _iterator_wasmExportNames != _object->end()) {
        if (!(doof::json_is_array(_iterator_wasmExportNames->second))) { return doof::Failure<std::string>{"Field \"wasmExportNames\" expected array but got " + std::string(doof::json_type_name(_iterator_wasmExportNames->second))}; }
        _field_wasmExportNames = [&]() { const auto* _array = doof::json_as_array(_iterator_wasmExportNames->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_wasmExportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    return doof::Success<std::shared_ptr<ModuleGraphEmission>>{std::make_shared<ModuleGraphEmission>(_field_modules.value(), _field_coverageModules.value(), _field_wasmSupportSource.value(), _field_wasmExportNames.value())};
}

std::shared_ptr<ModuleEmission> CxxModuleEmitter::emit(std::shared_ptr<::app_src_ast_::Program> program, std::shared_ptr<std::vector<std::string>> moduleIncludes, std::string entryMode) {
    const auto context = ((this->modulePath == std::string("")) ? ::app_src_emitter_context_::createEmitContext(program) : ::app_src_emitter_context_::createEmitContextForModule(program, this->modulePath, this->allPrograms));
    (context->namespaceImports = this->namespaceImports);
    (context->imports = this->imports);
    (context->moduleSurfaces = this->moduleSurfaces);
    if (this->coverageModuleId >= 0) {
        (context->coverageEnabled = true);
        (context->coverageModuleId = this->coverageModuleId);
    }
    if (!doof::is_null(this->instantiations)) {
        configureInstantiationRegistry(context, doof::unwrap_optional(this->instantiations));
    }
    const auto plan = ::app_src_emitter_header_::planHeader(program, context);
    if (!doof::is_null(this->instantiations)) {
        addConcreteHeaderDeclarations(plan, context, doof::unwrap_optional(this->instantiations));
    }
    return emitPlanned(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}), context, plan, entryMode, moduleIncludes);
}
std::shared_ptr<ModuleEmission> CxxModuleEmitter::emitPlanned(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan, std::string entryMode, std::shared_ptr<std::vector<std::string>> moduleIncludes) {
    const auto headerName = ((this->headerNameOverride == std::string("")) ? (this->moduleName + std::string(".hpp")) : this->headerNameOverride);
    const auto sourceName = ((this->sourceNameOverride == std::string("")) ? (this->moduleName + std::string(".cpp")) : this->sourceNameOverride);
    const auto namespaceName = ((this->namespaceNameOverride == std::string("")) ? (this->moduleName + std::string("_")) : this->namespaceNameOverride);
    (plan->moduleIncludes = moduleIncludes);
    const auto header = ::app_src_emitter_header_::renderHeader(plan, namespaceName);
    auto source = ((std::string("#include \"") + headerName) + std::string("\"\n#include <cmath>\n"));
    const auto& _iterable_6 = moduleIncludes;
    for (const auto& include : *_iterable_6) {
        (source = (((source + std::string("#include \"")) + include) + std::string("\"\n")));
    }
    if (!doof::is_null(this->instantiations)) {
        (source = (source + concreteImplementationIncludes(context, doof::unwrap_optional(this->instantiations), moduleIncludes)));
    }
    (source = (source + std::string("\n")));
    (source = (((source + std::string("namespace ")) + namespaceName) + std::string(" {\n")));
    (source = (source + emitImportedNamespaces(context)));
    const auto& _iterable_7 = programs;
    for (const auto& program : *_iterable_7) {
        const auto& _iterable_8 = program->statements;
        for (const auto& statement : *_iterable_8) {
            (source = (source + emitSourceStatement(statement, context)));
        }
    }
    if (!doof::is_null(this->instantiations)) {
        (source = (source + emitConcreteFunctions(context, doof::unwrap_optional(this->instantiations))));
    }
    (source = (source + std::string("}\n")));
    const auto nativeMethods = emitNativeClassMethods(programs, context);
    if (nativeMethods != std::string("")) {
        (source = ((((source + std::string("\nusing namespace ::")) + namespaceName) + std::string(";\n\n")) + nativeMethods));
    }
    if ((entryMode == std::string("executable")) && plan->hasMain) {
        (source = (source + emitMainWrapper(namespaceName, plan)));
    }
    if ((entryMode == std::string("ios-app")) && plan->hasMain) {
        (source = (source + emitAppEntryWrapper(namespaceName, plan)));
    }
    return std::make_shared<ModuleEmission>(context->modulePath, header, source, headerName, sourceName, context->coverageModuleId, sortedCoverageLines(context->coverageInstrumentedLines));
}
std::string concreteImplementationIncludes(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> plan, std::shared_ptr<std::vector<std::string>> existingIncludes) {
    std::shared_ptr<std::vector<std::string>> includes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_9 = plan->interfaces;
    for (const auto& interface_ : *_iterable_9) {
        if ((interface_->name != std::string("Stream")) && (interface_->modulePath != context->modulePath)) {
            continue;
        }
        const auto& _iterable_10 = interface_->implementations;
        for (const auto& implementation : *_iterable_10) {
            if (implementation->modulePath == context->modulePath) {
                continue;
            }
            const auto include = ::app_src_emitter_names_::moduleHeaderName(implementation->modulePath);
            if (!containsString(existingIncludes, include)) {
                addNamespace(includes, include);
            }
        }
    }
    auto result = std::string("");
    const auto& _iterable_11 = includes;
    for (const auto& include : *_iterable_11) {
        (result = (((result + std::string("#include \"")) + include) + std::string("\"\n")));
    }
    return result;
}
bool containsString(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    const auto& _iterable_12 = values;
    for (const auto& existing : *_iterable_12) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}
std::string emitImportedNamespaces(std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    std::shared_ptr<std::vector<std::string>> namespaces = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_13 = context->imports;
    for (const auto& imported : *_iterable_13) {
        const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(imported->sourceModule);
        addNamespace(namespaces, namespace_);
    }
    const auto& _iterable_14 = context->namespaceImports;
    for (const auto& imported : *_iterable_14) {
        const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(imported->sourceModule);
        addNamespace(namespaces, namespace_);
    }
    auto result = std::string("");
    const auto& _iterable_15 = namespaces;
    for (const auto& namespace_ : *_iterable_15) {
        (result = (((result + std::string("using namespace ::")) + namespace_) + std::string(";\n")));
    }
    return result;
}
void addNamespace(std::shared_ptr<std::vector<std::string>> namespaces, std::string namespace_) {
    const auto& _iterable_16 = namespaces;
    for (const auto& existing : *_iterable_16) {
        if (existing == namespace_) {
            return;
        }
    }
    namespaces->push_back(namespace_);
}
std::shared_ptr<ModuleGraphEmission> emitModuleGraph(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string entry, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> instantiations, std::string entryMode, bool coverage) {
    const auto graph = std::make_shared<ModuleGraphEmission>(std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(std::vector<std::shared_ptr<ModuleEmission>>{}), std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(std::vector<std::shared_ptr<CoverageModuleMetadata>>{}), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto concretePlan = (doof::is_null(instantiations) ? ::app_src_emitter_monomorphize_::buildInstantiationPlan(result) : doof::unwrap_optional(instantiations));
    const auto plan = planModuleGraph(result);
    auto nextCoverageModuleId = 0;
    const auto& _iterable_17 = plan->modules;
    for (const auto& module : *_iterable_17) {
        const auto info = findGraphModule(result, module->path);
        if (doof::is_null(info)) {
            continue;
        }
        auto coverageModuleId = -1;
        if (coverage && isCoverageEligible(module->path)) {
            (coverageModuleId = nextCoverageModuleId);
            (nextCoverageModuleId += 1);
        }
        const auto emitter = std::make_shared<CxxModuleEmitter>(module->namespaceName, module->headerName, module->sourceName, module->namespaceName, module->path, allPrograms(result), infoNamespaceImports(result, module->path), infoImports(result, module->path), emitModuleSurfaces(result), concretePlan, coverageModuleId);
        const auto emitted = emitter->emit(info->program, module->includes, ((module->path == entry) ? entryMode : std::string("none")));
        graph->modules->push_back(emitted);
        if (coverageModuleId >= 0) {
            graph->coverageModules->push_back(std::make_shared<CoverageModuleMetadata>(coverageModuleId, module->path, emitted->instrumentedLines));
        }
    }
    return graph;
}
bool isCoverageEligible(std::string modulePath) {
    return ((!doof::string_endsWith(modulePath, std::string(".test.do")) && !doof::string_contains(modulePath, std::string("/.doof-tests/"))) && !doof::string_startsWith(modulePath, std::string("/std/")));
}
std::shared_ptr<std::vector<int32_t>> sortedCoverageLines(std::shared_ptr<std::vector<int32_t>> lines) {
    std::shared_ptr<std::vector<int32_t>> result = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    auto last = -1;
    for (int32_t count = 0; count < static_cast<int32_t>((lines)->size()); ++count) {
        std::optional<int32_t> candidate = std::nullopt;
        const auto& _iterable_18 = lines;
        for (const auto& line : *_iterable_18) {
            if ((line > last) && (doof::is_null(candidate) || (line < candidate.value()))) {
                (candidate = line);
            }
        }
        if (!doof::is_null(candidate)) {
            result->push_back(candidate.value());
            (last = candidate.value());
        }
    }
    return result;
}
void configureInstantiationRegistry(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> plan) {
    const auto& _iterable_19 = plan->nativeTemplateClassKeys;
    for (const auto& key : *_iterable_19) {
        context->nativeTemplateClassKeys->push_back(key);
    }
    const auto& _iterable_20 = plan->functions;
    for (const auto& instantiation : *_iterable_20) {
        context->concreteFunctionKeys->push_back(instantiation->key);
        context->concreteFunctionNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_21 = plan->classes;
    for (const auto& instantiation : *_iterable_21) {
        context->concreteClassKeys->push_back(instantiation->key);
        context->concreteClassNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_22 = plan->methods;
    for (const auto& instantiation : *_iterable_22) {
        context->concreteMethodKeys->push_back(instantiation->key);
        context->concreteMethodNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_23 = plan->interfaces;
    for (const auto& instantiation : *_iterable_23) {
        context->concreteInterfaceKeys->push_back(instantiation->key);
        context->concreteInterfaceNames->push_back(instantiation->emittedName);
    }
}
void addConcreteHeaderDeclarations(std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> instantiations) {
    const auto& _iterable_24 = instantiations->interfaces;
    for (const auto& interface_ : *_iterable_24) {
        if ((interface_->name != std::string("Stream")) && (interface_->modulePath != context->modulePath)) {
            continue;
        }
        auto alternatives = std::string("");
        const auto& _iterable_25 = interface_->implementations;
        for (const auto& implementation : *_iterable_25) {
            if (alternatives != std::string("")) {
                (alternatives = (alternatives + std::string(", ")));
            }
            auto typeName = implementation->typeName;
            if (implementation->modulePath != context->modulePath) {
                const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(implementation->modulePath);
                plan->typeOnlyForwardDeclarations->push_back(((((std::string("namespace ") + namespace_) + std::string(" { struct ")) + implementation->typeName) + std::string("; }\n")));
                (typeName = (((std::string("::") + namespace_) + std::string("::")) + typeName));
            }
            (alternatives = (((alternatives + std::string("std::shared_ptr<")) + typeName) + std::string(">")));
        }
        if (alternatives == std::string("")) {
            (alternatives = std::string("std::monostate"));
        }
        plan->interfaceAliases->push_back(((((std::string("using ") + interface_->emittedName) + std::string(" = std::variant<")) + alternatives) + std::string(">;\n")));
    }
    const auto& _iterable_26 = instantiations->classes;
    for (const auto& instantiation : *_iterable_26) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        const auto& _iterable_27 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_27) {
            addConcreteTypeForwardDeclarations(plan, context, argument);
        }
        plan->classForwardDeclarations->push_back(((std::string("struct ") + instantiation->emittedName) + std::string(";\n")));
        (context->substitution = instantiation->substitution);
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{});
        const auto& _iterable_28 = instantiations->methods;
        for (const auto& method : *_iterable_28) {
            if (method->ownerKey == instantiation->key) {
                methods->push_back(method);
            }
        }
        plan->classDefinitions->push_back(::app_src_emitter_decl_::emitClassDeclaration(instantiation->declaration, context, instantiation->emittedName, methods));
        clearInstantiation(context);
    }
    const auto& _iterable_29 = instantiations->functions;
    for (const auto& instantiation : *_iterable_29) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        const auto& _iterable_30 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_30) {
            addConcreteTypeForwardDeclarations(plan, context, argument);
        }
        (context->substitution = instantiation->substitution);
        const auto signature = ::app_src_emitter_decl_::emitFunctionDeclaration(instantiation->declaration, instantiation->emittedName, context->modulePath, context);
        if (instantiation->declaration->native_) {
            plan->nativeAdapterSignatures->push_back(signature);
        } else {
            plan->functionSignatures->push_back(signature);
        }
        clearInstantiation(context);
    }
}
void addConcreteTypeForwardDeclarations(std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if ((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) {
                const auto declaration = ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(class_->symbol->module)) + std::string(" { struct ")) + class_->name) + std::string("; }\n"));
                if (!containsString(plan->typeOnlyForwardDeclarations, declaration)) {
                    plan->typeOnlyForwardDeclarations->push_back(declaration);
                }
            }
            const auto& _iterable_31 = class_->typeArgs;
            for (const auto& argument : *_iterable_31) {
                addConcreteTypeForwardDeclarations(plan, context, argument);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto& _iterable_32 = interface_->typeArgs;
            for (const auto& argument : *_iterable_32) {
                addConcreteTypeForwardDeclarations(plan, context, argument);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, map->keyType);
            addConcreteTypeForwardDeclarations(plan, context, map->valueType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, result_->valueType);
            addConcreteTypeForwardDeclarations(plan, context, result_->errorType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_33 = tuple->elements;
            for (const auto& element : *_iterable_33) {
                addConcreteTypeForwardDeclarations(plan, context, element);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_34 = union_->types;
            for (const auto& member : *_iterable_34) {
                addConcreteTypeForwardDeclarations(plan, context, member);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_35 = function_->params;
            for (const auto& parameter : *_iterable_35) {
                addConcreteTypeForwardDeclarations(plan, context, parameter->type_);
            }
            addConcreteTypeForwardDeclarations(plan, context, function_->returnType);
    }
    else {
    }
    }
}
std::string emitConcreteFunctions(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> instantiations) {
    auto result = std::string("");
    const auto& _iterable_36 = instantiations->functions;
    for (const auto& instantiation : *_iterable_36) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        (context->substitution = instantiation->substitution);
        if (instantiation->declaration->native_) {
            (result = (result + ::app_src_emitter_decl_::emitNativeFunctionAdapterDefinition(instantiation->declaration, instantiation->emittedName, context)));
        } else {
            (result = (result + ::app_src_emitter_decl_::emitFunctionDefinition(instantiation->declaration, context, instantiation->emittedName)));
        }
        clearInstantiation(context);
    }
    return result;
}
void withInstantiation(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments) {
    (context->substitution = std::make_shared<::app_src_semantic_::TypeSubstitution>(names, arguments));
}
void clearInstantiation(std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    (context->substitution = nullptr);
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> emitModuleSurfaces(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> surfaces = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>(std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>{});
    const auto& _iterable_37 = result->modules;
    for (const auto& module : *_iterable_37) {
        std::shared_ptr<std::vector<std::string>> genericTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        std::shared_ptr<std::vector<std::string>> genericFunctions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_38 = module->program->statements;
        for (const auto& statement : *_iterable_38) {
            collectGenericSurfaceSymbols(statement, genericTypes, genericFunctions);
        }
        surfaces->push_back(std::make_shared<::app_src_emitter_context_::EmitModuleSurface>(module->path, module->exports, module->imports, genericTypes, genericFunctions));
    }
    return surfaces;
}
void collectGenericSurfaceSymbols(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<std::vector<std::string>> typeNames, std::shared_ptr<std::vector<std::string>> functionNames) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (static_cast<int32_t>((class_->typeParams)->size()) > 0) {
                typeNames->push_back(class_->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            if (static_cast<int32_t>((interface_->typeParams)->size()) > 0) {
                typeNames->push_back(interface_->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            if (static_cast<int32_t>((alias->typeParams)->size()) > 0) {
                typeNames->push_back(alias->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            if (static_cast<int32_t>((function_->typeParams)->size()) > 0) {
                functionNames->push_back(function_->name);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            collectGenericSurfaceSymbols(export_->declaration, typeNames, functionNames);
    }
    else {
    }
    }
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
    const auto& _iterable_39 = result->modules;
    for (const auto& module : *_iterable_39) {
        programs->push_back(module->program);
    }
    return programs;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> infoNamespaceImports(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path) {
    const auto& _iterable_40 = result->modules;
    for (const auto& module : *_iterable_40) {
        if (module->path == path) {
            return module->namespaceImports;
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{});
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> infoImports(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path) {
    const auto& _iterable_41 = result->modules;
    for (const auto& module : *_iterable_41) {
        if (module->path == path) {
            return module->imports;
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{});
}
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findGraphModule(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path) {
    const auto& _iterable_42 = result->modules;
    for (const auto& module : *_iterable_42) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
std::shared_ptr<ModuleEmission> emitModule(std::shared_ptr<::app_src_ast_::Program> program, std::string moduleName) {
    std::shared_ptr<std::vector<std::string>> emptyIncludes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    return std::make_shared<CxxModuleEmitter>(moduleName, std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>(std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>{}), nullptr, -1)->emit(program, emptyIncludes, std::string("executable"));
}
std::string emitSourceStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
                return std::string("");
            }
            return ::app_src_emitter_decl_::emitFunctionDefinition(fn, context, ((fn->name == std::string("main")) ? std::string("doof_main") : fn->name));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (class_->native_) {
                return std::string("");
            }
            auto result = (std::string("\n") + ::app_src_emitter_decl_::emitStaticClassFieldDefinitions(class_, context));
            if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
                const auto& _iterable_43 = class_->methods;
                for (const auto& method : *_iterable_43) {
                    (result = (result + ::app_src_emitter_decl_::emitClassMethodDefinition(class_, method, context)));
                }
            }
            (result = (result + ::app_src_emitter_json_::emitGeneratedJsonMethods(class_, context)));
            (result = (result + ::app_src_emitter_metadata_::emitMetadataDefinition(class_, context)));
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            return ::app_src_emitter_json_::emitInterfaceJsonDefinition(interface_, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return (const_->exported ? std::string("") : ::app_src_emitter_decl_::emitValueDeclaration(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(const_), context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return (readonly_->exported ? std::string("") : ::app_src_emitter_decl_::emitValueDeclaration(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(readonly_), context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return ::app_src_emitter_decl_::emitValueDeclaration(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(binding), context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return ::app_src_emitter_decl_::emitValueDeclaration(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(let_), context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return emitSourceStatement(export_->declaration, context);
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
std::string emitNativeClassMethods(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto result = std::string("");
    const auto& _iterable_44 = programs;
    for (const auto& program : *_iterable_44) {
        const auto& _iterable_45 = program->statements;
        for (const auto& statement : *_iterable_45) {
            (result = (result + emitNativeClassMethodsForStatement(statement, context)));
        }
    }
    return result;
}
std::string emitNativeClassMethodsForStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (!class_->native_) {
                return std::string("");
            }
            auto result = std::string("");
            const auto& _iterable_46 = class_->methods;
            for (const auto& method : *_iterable_46) {
                if (!method->bodyless) {
                    (result = (result + ::app_src_emitter_decl_::emitClassMethodDefinition(class_, method, context)));
                }
            }
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return emitNativeClassMethodsForStatement(export_->declaration, context);
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
std::string emitMainWrapper(std::string moduleName, std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan) {
    const auto signature = (plan->mainAcceptsArgs ? std::string("int main(int argc, char** argv)") : std::string("int main()"));
    const auto argumentSetup = (plan->mainAcceptsArgs ? std::string("std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); ") : std::string(""));
    const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))")) : (moduleName + std::string("::doof_main()")));
    const auto success = (plan->mainReturnsInt ? ((std::string("return ") + call) + std::string(";")) : (call + std::string("; return 0;")));
    const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
    const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
    return ((((((((std::string("\n") + signature) + std::string(" { try { ")) + actorSetup) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" }\n"));
}
std::string emitAppEntryWrapper(std::string moduleName, std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan) {
    const auto argumentSetup = (plan->mainAcceptsArgs ? std::string("std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); ") : std::string("(void)argc; (void)argv; "));
    const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))")) : (moduleName + std::string("::doof_main()")));
    const auto success = (plan->mainReturnsInt ? ((std::string("return ") + call) + std::string(";")) : (call + std::string("; return 0;")));
    const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
    const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
    return ((((((std::string("\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { ") + actorSetup) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" }\n"));
}
}
