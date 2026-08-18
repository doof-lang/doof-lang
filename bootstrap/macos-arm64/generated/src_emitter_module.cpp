#include "src_emitter_module.hpp"

namespace app_src_emitter_module_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_decl_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_metadata_;
using namespace ::app_src_emitter_stmt_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_header_;
using namespace ::app_src_emitter_worldview_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_names_;
using namespace ::std_::crypto::index;
using namespace ::app_src_semantic_;

doof::JsonObject ModulePlan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["path"] = doof::json_value(this->path);
    (*_json)["namespaceName"] = doof::json_value(this->namespaceName);
    (*_json)["headerName"] = doof::json_value(this->headerName);
    (*_json)["sourceName"] = doof::json_value(this->sourceName);
    return _json;
}
doof::Result<std::shared_ptr<ModulePlan>, std::string> ModulePlan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
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
        return doof::Success<std::shared_ptr<ModulePlan>>{std::make_shared<ModulePlan>(_field_path, _field_namespaceName, _field_headerName, _field_sourceName)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject ModuleGraphPlan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["modules"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->modules->size()); for (const auto& _element : *this->modules) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<ModuleGraphPlan>, std::string> ModuleGraphPlan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ModulePlan>>>> _field_modules;
    if (auto _iterator_modules = _object->find("modules"); _iterator_modules != _object->end()) {
            if (!(doof::json_is_array(_iterator_modules->second))) { return doof::Failure<std::string>{"Field \"modules\" expected array but got " + std::string(doof::json_type_name(_iterator_modules->second))}; }
        _field_modules = [&]() { const auto* _array = doof::json_as_array(_iterator_modules->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(ModulePlan::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_modules = std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(std::vector<std::shared_ptr<ModulePlan>>{});
    }
        return doof::Success<std::shared_ptr<ModuleGraphPlan>>{std::make_shared<ModuleGraphPlan>(_field_modules.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
std::shared_ptr<ModuleGraphPlan> planModuleGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    const auto plan = std::make_shared<ModuleGraphPlan>(std::make_shared<std::vector<std::shared_ptr<ModulePlan>>>(std::vector<std::shared_ptr<ModulePlan>>{}));
    const auto& _iterable_1 = result->modules;
    for (const auto& info : *_iterable_1) {
        const auto module = std::make_shared<ModulePlan>(info->path, ::app_src_emitter_names_::moduleNamespace(info->path), ::app_src_emitter_names_::moduleHeaderName(info->path), ::app_src_emitter_names_::moduleSourceName(info->path));
        plan->modules->push_back(module);
    }
    return plan;
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
    (*_json)["reused"] = doof::json_value(this->reused);
    (*_json)["fingerprint"] = doof::json_value(this->fingerprint);
    return _json;
}
doof::Result<std::shared_ptr<ModuleEmission>, std::string> ModuleEmission::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
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
    std::optional<bool> _field_reused;
    if (auto _iterator_reused = _object->find("reused"); _iterator_reused != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_reused->second) : doof::json_is_boolean(_iterator_reused->second)))) { return doof::Failure<std::string>{"Field \"reused\" expected boolean but got " + std::string(doof::json_type_name(_iterator_reused->second))}; }
        _field_reused = (_lenient ? doof::json_as_bool_lenient(_iterator_reused->second) : doof::json_as_bool(_iterator_reused->second));
    } else {
        _field_reused = false;
    }
    std::optional<std::string> _field_fingerprint;
    if (auto _iterator_fingerprint = _object->find("fingerprint"); _iterator_fingerprint != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_fingerprint->second) : doof::json_is_string(_iterator_fingerprint->second)))) { return doof::Failure<std::string>{"Field \"fingerprint\" expected string but got " + std::string(doof::json_type_name(_iterator_fingerprint->second))}; }
        _field_fingerprint = (_lenient ? doof::json_as_string_lenient(_iterator_fingerprint->second) : doof::json_as_string(_iterator_fingerprint->second));
    } else {
        _field_fingerprint = std::string("");
    }
        return doof::Success<std::shared_ptr<ModuleEmission>>{std::make_shared<ModuleEmission>(_field_modulePath, _field_header, _field_source, _field_headerName, _field_sourceName, _field_coverageModuleId.value(), _field_instrumentedLines.value(), _field_reused.value(), _field_fingerprint.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject ModuleEmissionCacheKey::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["modulePath"] = doof::json_value(this->modulePath);
    (*_json)["fingerprint"] = doof::json_value(this->fingerprint);
    return _json;
}
doof::Result<std::shared_ptr<ModuleEmissionCacheKey>, std::string> ModuleEmissionCacheKey::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_modulePath = _object->find("modulePath");
    if (_iterator_modulePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"modulePath\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_modulePath->second) : doof::json_is_string(_iterator_modulePath->second)))) { return doof::Failure<std::string>{"Field \"modulePath\" expected string but got " + std::string(doof::json_type_name(_iterator_modulePath->second))}; }
    auto _field_modulePath = (_lenient ? doof::json_as_string_lenient(_iterator_modulePath->second) : doof::json_as_string(_iterator_modulePath->second));
    auto _iterator_fingerprint = _object->find("fingerprint");
    if (_iterator_fingerprint == _object->end()) { return doof::Failure<std::string>{"Missing required field \"fingerprint\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_fingerprint->second) : doof::json_is_string(_iterator_fingerprint->second)))) { return doof::Failure<std::string>{"Field \"fingerprint\" expected string but got " + std::string(doof::json_type_name(_iterator_fingerprint->second))}; }
    auto _field_fingerprint = (_lenient ? doof::json_as_string_lenient(_iterator_fingerprint->second) : doof::json_as_string(_iterator_fingerprint->second));
        return doof::Success<std::shared_ptr<ModuleEmissionCacheKey>>{std::make_shared<ModuleEmissionCacheKey>(_field_modulePath, _field_fingerprint)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject CoverageModuleMetadata::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["moduleId"] = doof::json_value(this->moduleId);
    (*_json)["modulePath"] = doof::json_value(this->modulePath);
    (*_json)["instrumentedLines"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->instrumentedLines->size()); for (const auto& _element : *this->instrumentedLines) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<CoverageModuleMetadata>, std::string> CoverageModuleMetadata::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
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
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
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
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ModuleEmission>>>> _field_modules;
    if (auto _iterator_modules = _object->find("modules"); _iterator_modules != _object->end()) {
            if (!(doof::json_is_array(_iterator_modules->second))) { return doof::Failure<std::string>{"Field \"modules\" expected array but got " + std::string(doof::json_type_name(_iterator_modules->second))}; }
        _field_modules = [&]() { const auto* _array = doof::json_as_array(_iterator_modules->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(ModuleEmission::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_modules = std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(std::vector<std::shared_ptr<ModuleEmission>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<CoverageModuleMetadata>>>> _field_coverageModules;
    if (auto _iterator_coverageModules = _object->find("coverageModules"); _iterator_coverageModules != _object->end()) {
            if (!(doof::json_is_array(_iterator_coverageModules->second))) { return doof::Failure<std::string>{"Field \"coverageModules\" expected array but got " + std::string(doof::json_type_name(_iterator_coverageModules->second))}; }
        _field_coverageModules = [&]() { const auto* _array = doof::json_as_array(_iterator_coverageModules->second); auto _values = std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(CoverageModuleMetadata::fromJsonValue(_element, _lenient))); } return _values; }();
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
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

std::shared_ptr<ModuleEmission> CxxModuleEmitter::emit(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& entryMode) {
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
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>> sections = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>>(std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>{});
    std::shared_ptr<::app_src_emitter_header_::HeaderPlan> plan = nullptr;
    auto views = this->worldviewModules;
    if (static_cast<int32_t>((views)->size()) == 0) {
        (views = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{std::make_shared<::app_src_emitter_worldview_::WorldviewModule>(this->modulePath, program)}));
    }
    const auto& _iterable_2 = views;
    for (const auto& view : *_iterable_2) {
        const auto sectionContext = ::app_src_emitter_context_::createEmitContextForModule(view->program, view->path, this->allPrograms);
        (sectionContext->imports = surfaceImports(this->moduleSurfaces, view->path));
        (sectionContext->moduleSurfaces = this->moduleSurfaces);
        if (!doof::is_null(this->instantiations)) {
            configureInstantiationRegistry(sectionContext, doof::unwrap_optional(this->instantiations));
        }
        const auto sectionPlan = ::app_src_emitter_header_::planHeader(view->program, sectionContext);
        if (!doof::is_null(this->instantiations)) {
            addConcreteHeaderDeclarations(sectionPlan, sectionContext, doof::unwrap_optional(this->instantiations), view->program, this->worldviewInterfaceKeys);
        }
        const auto sectionNamespace = ((view->path == this->modulePath) ? ((this->namespaceNameOverride != std::string("")) ? this->namespaceNameOverride : ((this->modulePath == std::string("")) ? (this->moduleName + std::string("_")) : ::app_src_emitter_names_::moduleNamespace(view->path))) : ::app_src_emitter_names_::moduleNamespace(view->path));
        sections->push_back(std::make_shared<::app_src_emitter_header_::HeaderSection>(sectionNamespace, sectionPlan));
        if (view->path == this->modulePath) {
            (plan = sectionPlan);
        }
    }
    if (doof::is_null(plan)) {
        doof::panic((std::string("worldview omitted root module ") + this->modulePath));
    }
    (context->scriptEntry = (((entryMode == std::string("executable")) || (entryMode == std::string("ios-app"))) && hasScriptStatements(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}))));
    return emitPlanned(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}), context, doof::unwrap_optional(plan), sections, entryMode);
}
std::shared_ptr<ModuleEmission> CxxModuleEmitter::emitPlanned(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_header_::HeaderSection>>>& sections, const std::string& entryMode) {
    const auto headerName = ((this->headerNameOverride == std::string("")) ? (this->moduleName + std::string(".hpp")) : this->headerNameOverride);
    const auto sourceName = ((this->sourceNameOverride == std::string("")) ? (this->moduleName + std::string(".cpp")) : this->sourceNameOverride);
    const auto namespaceName = ((this->namespaceNameOverride == std::string("")) ? (this->moduleName + std::string("_")) : this->namespaceNameOverride);
    const auto header = ::app_src_emitter_header_::renderProjectedHeader(sections);
    auto source = ((std::string("#include \"") + headerName) + std::string("\"\n"));
    (source = (source + std::string("\n")));
    const auto& _iterable_3 = this->initializationModuleNamespaces;
    for (const auto& namespace_ : *_iterable_3) {
        (source = (((source + std::string("namespace ")) + namespace_) + std::string(" { void __doof_initialize_module(); }\n")));
    }
    if (static_cast<int32_t>((this->initializationModuleNamespaces)->size()) > 0) {
        (source = (source + std::string("\n")));
    }
    (source = (((source + std::string("namespace ")) + namespaceName) + std::string(" {\n")));
    (source = (source + emitImportedNamespaces(context, this->worldviewModules)));
    if (context->scriptEntry) {
        (source = (source + emitScriptStorage(programs, context)));
    }
    const auto& _iterable_4 = programs;
    for (const auto& program : *_iterable_4) {
        const auto& _iterable_5 = program->statements;
        for (const auto& statement : *_iterable_5) {
            if (!(context->scriptEntry && (!doof::is_null(scriptGlobalDeclaration(statement))))) {
                (source = (source + emitSourceStatement(statement, context)));
            }
        }
    }
    (source = (source + emitModuleInitializer(programs, context, !context->scriptEntry)));
    if (context->scriptEntry) {
        (source = (source + emitScriptRunner(programs, context)));
    }
    if (!doof::is_null(this->instantiations)) {
        (source = (source + emitConcreteFunctions(context, doof::unwrap_optional(this->instantiations))));
    }
    (source = (source + std::string("}\n")));
    const auto nativeMethods = emitNativeClassMethods(programs, context);
    if (nativeMethods != std::string("")) {
        (source = ((((source + std::string("\nusing namespace ::")) + namespaceName) + std::string(";\n\n")) + nativeMethods));
    }
    const auto initializationCall = emitGraphInitializationCall(this->initializationModuleNamespaces);
    if ((entryMode == std::string("executable")) && (plan->hasMain || context->scriptEntry)) {
        (source = (source + emitMainWrapper(namespaceName, plan, context->scriptEntry, initializationCall)));
    }
    if ((entryMode == std::string("ios-app")) && (plan->hasMain || context->scriptEntry)) {
        (source = (source + emitAppEntryWrapper(namespaceName, plan, context->scriptEntry, initializationCall)));
    }
    return std::make_shared<ModuleEmission>(context->modulePath, header, source, headerName, sourceName, context->coverageModuleId, sortedCoverageLines(context->coverageInstrumentedLines), false, std::string(""));
}
bool hasScriptStatements(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs) {
    const auto& _iterable_6 = programs;
    for (const auto& program : *_iterable_6) {
        const auto& _iterable_7 = program->statements;
        for (const auto& statement : *_iterable_7) {
            if (!isModuleDeclaration(statement)) {
                return true;
            }
        }
    }
    return false;
}
bool isValueDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            return true;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool isModuleDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    if (isValueDeclaration(statement)) {
        return true;
    }
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImportDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportList>>(_case_subject)) {
            return true;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> scriptGlobalDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    if (isValueDeclaration(statement)) {
        return doof::optional_value(statement);
    }
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
            }
            else {
            }
            }
    }
    else {
    }
    }
    return std::monostate{};
}
std::string scriptDeclarationName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return value->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return value->name;
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> scriptDeclarationType(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else {
            return std::monostate{};
    }
    }
    doof::unreachable();
    return std::monostate{};
}
bool scriptDeclarationMutable(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            return true;
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
std::string emitScriptStorage(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto source = std::string("\n");
    const auto& _iterable_8 = programs;
    for (const auto& program : *_iterable_8) {
        const auto& _iterable_9 = program->statements;
        for (const auto& statement : *_iterable_9) {
            const auto declaration = scriptGlobalDeclaration(statement);
            if (doof::is_null(declaration)) {
                continue;
            }
            const auto name = scriptDeclarationName(doof::unwrap_optional(declaration));
            const auto type_ = scriptDeclarationType(doof::unwrap_optional(declaration));
            if (((name == std::string("")) || (name == std::string("_"))) || doof::is_null(type_)) {
                continue;
            }
            const auto cppName = ::app_src_emitter_expr_::cppIdentifier(name);
            const auto typeText = ::app_src_emitter_types_::emitContextType(doof::unwrap_optional(type_), context);
            (source = (((((source + std::string("std::optional<")) + typeText) + std::string("> __doof_script_storage_")) + cppName) + std::string(";\n")));
            const auto returnType = (scriptDeclarationMutable(doof::unwrap_optional(declaration)) ? (typeText + std::string("&")) : ((std::string("const ") + typeText) + std::string("&")));
            (source = ((((((((((source + returnType) + std::string(" __doof_script_get_")) + cppName) + std::string("() { if (!__doof_script_storage_")) + cppName) + std::string(".has_value()) doof::panic(\"Entry binding '")) + name) + std::string("' was accessed before initialization\"); return *__doof_script_storage_")) + cppName) + std::string("; }\n")));
        }
    }
    return (source + std::string("\n"));
}
std::string emitScriptRunner(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto previousTryPanics = context->tryPanics;
    (context->tryPanics = true);
    auto source = std::string("\nvoid __doof_run_script(std::shared_ptr<std::vector<std::string>> arguments) {\n");
    const auto& _iterable_10 = programs;
    for (const auto& program : *_iterable_10) {
        const auto& _iterable_11 = program->statements;
        for (const auto& statement : *_iterable_11) {
            const auto declaration = scriptGlobalDeclaration(statement);
            if (!doof::is_null(declaration)) {
                (source = (source + ::app_src_emitter_stmt_::emitStatement(statement, 1, context)));
                const auto name = scriptDeclarationName(doof::unwrap_optional(declaration));
                if ((name != std::string("")) && (name != std::string("_"))) {
                    (source = (((((source + std::string("    __doof_script_storage_")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(".emplace(")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(");\n")));
                }
            } else if (!isModuleDeclaration(statement)) {
                (source = (source + ::app_src_emitter_stmt_::emitStatement(statement, 1, context)));
            }
        }
    }
    (context->tryPanics = previousTryPanics);
    return (source + std::string("}\n"));
}
bool containsString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    const auto& _iterable_12 = values;
    for (const auto& existing : *_iterable_12) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}
std::string emitImportedNamespaces(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>& worldviewModules) {
    std::shared_ptr<std::vector<std::string>> namespaces = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_13 = context->imports;
    for (const auto& imported : *_iterable_13) {
        if (!worldviewContainsModule(worldviewModules, imported->sourceModule)) {
            continue;
        }
        const auto namespace_ = ::app_src_emitter_names_::moduleNamespace(imported->sourceModule);
        addNamespace(namespaces, namespace_);
    }
    const auto& _iterable_14 = context->namespaceImports;
    for (const auto& imported : *_iterable_14) {
        if (!worldviewContainsModule(worldviewModules, imported->sourceModule)) {
            continue;
        }
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
bool worldviewContainsModule(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>& modules, const std::string& path) {
    const auto& _iterable_16 = modules;
    for (const auto& module : *_iterable_16) {
        if (module->path == path) {
            return true;
        }
    }
    return false;
}
void addNamespace(const std::shared_ptr<std::vector<std::string>>& namespaces, const std::string& namespace_) {
    const auto& _iterable_17 = namespaces;
    for (const auto& existing : *_iterable_17) {
        if (existing == namespace_) {
            return;
        }
    }
    namespaces->push_back(namespace_);
}
std::shared_ptr<ModuleGraphEmission> emitModuleGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::shared_ptr<ModuleEmissionCacheKey>>>& reusableModules, const std::string& configurationFingerprint) {
    const auto graph = std::make_shared<ModuleGraphEmission>(std::make_shared<std::vector<std::shared_ptr<ModuleEmission>>>(std::vector<std::shared_ptr<ModuleEmission>>{}), std::make_shared<std::vector<std::shared_ptr<CoverageModuleMetadata>>>(std::vector<std::shared_ptr<CoverageModuleMetadata>>{}), std::string(""), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto concretePlan = [&]() -> std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan> { auto _coalesce_18 = instantiations; if (doof::is_null(_coalesce_18)) return ::app_src_emitter_monomorphize_::buildInstantiationPlan(result); return doof::unwrap_optional(_coalesce_18); }();
    const auto plan = planModuleGraph(result);
    const auto initializationOrder = planModuleInitializationOrder(result, entry, entryMode);
    const auto graphPrograms = allPrograms(result);
    const auto graphSurfaces = emitModuleSurfaces(result);
    auto nextCoverageModuleId = 0;
    const auto& _iterable_19 = plan->modules;
    for (const auto& module : *_iterable_19) {
        const auto info = findGraphModule(result, module->path);
        if (doof::is_null(info)) {
            continue;
        }
        auto coverageModuleId = -1;
        if (coverage && isCoverageEligible(module->path)) {
            (coverageModuleId = nextCoverageModuleId);
            (nextCoverageModuleId += 1);
        }
        const auto fingerprint = moduleEmissionFingerprint(result, doof::unwrap_optional(info), concretePlan, module->path, entry, entryMode, coverage, initializationOrder, configurationFingerprint);
        if (!coverage && reusableModuleMatches(reusableModules, module->path, fingerprint)) {
            graph->modules->push_back(std::make_shared<ModuleEmission>(module->path, std::string(""), std::string(""), module->headerName, module->sourceName, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), true, fingerprint));
            continue;
        }
        const auto emitter = std::make_shared<CxxModuleEmitter>(module->namespaceName, module->headerName, module->sourceName, module->namespaceName, module->path, graphPrograms, infoNamespaceImports(result, module->path), infoImports(result, module->path), graphSurfaces, std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), concretePlan, coverageModuleId, ((module->path == entry) ? moduleInitializationNamespaces(initializationOrder) : std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
        const auto worldview = ::app_src_emitter_worldview_::planWorldview(result, module->path, concretePlan);
        (emitter->worldviewModules = worldview->modules);
        (emitter->worldviewInterfaceKeys = worldview->interfaceKeys);
        const auto emitted = emitter->emit(info->program, ((module->path == entry) ? entryMode : std::string("none")));
        (emitted->fingerprint = fingerprint);
        graph->modules->push_back(emitted);
        if (coverageModuleId >= 0) {
            graph->coverageModules->push_back(std::make_shared<CoverageModuleMetadata>(coverageModuleId, module->path, emitted->instrumentedLines));
        }
    }
    return graph;
}
bool reusableModuleMatches(const std::shared_ptr<std::vector<std::shared_ptr<ModuleEmissionCacheKey>>>& keys, const std::string& path, const std::string& fingerprint) {
    const auto& _iterable_20 = keys;
    for (const auto& key : *_iterable_20) {
        if ((key->modulePath == path) && (key->fingerprint == fingerprint)) {
            return true;
        }
    }
    return false;
}
std::string moduleEmissionFingerprint(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::string& path, const std::string& entry, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::string>>& initializationOrder, const std::string& configurationFingerprint) {
    auto value = (((((((std::string("doof-module-emission-2\n") + configurationFingerprint) + std::string("\n")) + path) + std::string("\n")) + entryMode) + std::string("\n")) + doof::to_string(coverage));
    std::shared_ptr<std::vector<std::string>> reachable = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    collectModuleDependencyClosure(result, path, reachable);
    const auto& _iterable_21 = result->modules;
    for (const auto& candidate : *_iterable_21) {
        if (containsString(reachable, candidate->path)) {
            (value = ((((value + std::string("\nsource:")) + candidate->path) + std::string(":")) + candidate->sourceHash));
        }
    }
    const auto& _iterable_22 = instantiations->functions;
    for (const auto& item : *_iterable_22) {
        (value = ((value + std::string("\nfunction:")) + item->key));
    }
    const auto& _iterable_23 = instantiations->classes;
    for (const auto& item : *_iterable_23) {
        (value = ((value + std::string("\nclass:")) + item->key));
    }
    const auto& _iterable_24 = instantiations->methods;
    for (const auto& item : *_iterable_24) {
        (value = ((value + std::string("\nmethod:")) + item->key));
    }
    const auto& _iterable_25 = instantiations->interfaces;
    for (const auto& item : *_iterable_25) {
        (value = ((value + std::string("\ninterface:")) + item->key));
        const auto& _iterable_26 = item->implementations;
        for (const auto& implementation : *_iterable_26) {
            (value = ((((value + std::string(":")) + implementation->modulePath) + std::string(":")) + implementation->typeName));
        }
    }
    const auto& _iterable_27 = instantiations->nativeTemplateClassKeys;
    for (const auto& key : *_iterable_27) {
        (value = ((value + std::string("\nnative:")) + key));
    }
    if (path == entry) {
        const auto& _iterable_28 = initializationOrder;
        for (const auto& initialized : *_iterable_28) {
            (value = ((value + std::string("\ninitialize:")) + initialized));
        }
    }
    return ::std_::crypto::index::sha256HexString(value);
}
void collectModuleDependencyClosure(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path, const std::shared_ptr<std::vector<std::string>>& reachable) {
    if (containsString(reachable, path)) {
        return;
    }
    reachable->push_back(path);
    const auto module = findGraphModule(result, path);
    if (doof::is_null(module)) {
        return;
    }
    const auto& _iterable_29 = module->imports;
    for (const auto& imported : *_iterable_29) {
        collectModuleDependencyClosure(result, imported->sourceModule, reachable);
    }
    const auto& _iterable_30 = module->namespaceImports;
    for (const auto& imported : *_iterable_30) {
        collectModuleDependencyClosure(result, imported->sourceModule, reachable);
    }
    const auto& _iterable_31 = module->reExports;
    for (const auto& reExport : *_iterable_31) {
        collectModuleDependencyClosure(result, reExport, reachable);
    }
}
bool isCoverageEligible(const std::string& modulePath) {
    return ((!doof::string_endsWith(modulePath, std::string(".test.do")) && !doof::string_contains(modulePath, std::string("/.doof-tests/"))) && !doof::string_startsWith(modulePath, std::string("/std/")));
}
std::shared_ptr<std::vector<int32_t>> sortedCoverageLines(const std::shared_ptr<std::vector<int32_t>>& lines) {
    std::shared_ptr<std::vector<int32_t>> result = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    auto last = -1;
    for (int32_t count = 0; count < static_cast<int32_t>((lines)->size()); ++count) {
        std::optional<int32_t> candidate = std::nullopt;
        const auto& _iterable_32 = lines;
        for (const auto& line : *_iterable_32) {
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
void configureInstantiationRegistry(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& plan) {
    const auto& _iterable_33 = plan->nativeTemplateClassKeys;
    for (const auto& key : *_iterable_33) {
        context->nativeTemplateClassKeys->push_back(key);
    }
    const auto& _iterable_34 = plan->functions;
    for (const auto& instantiation : *_iterable_34) {
        context->concreteFunctionKeys->push_back(instantiation->key);
        context->concreteFunctionNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_35 = plan->classes;
    for (const auto& instantiation : *_iterable_35) {
        context->concreteClassKeys->push_back(instantiation->key);
        context->concreteClassNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_36 = plan->methods;
    for (const auto& instantiation : *_iterable_36) {
        context->concreteMethodKeys->push_back(instantiation->key);
        context->concreteMethodNames->push_back(instantiation->emittedName);
    }
    const auto& _iterable_37 = plan->interfaces;
    for (const auto& instantiation : *_iterable_37) {
        context->concreteInterfaceKeys->push_back(instantiation->key);
        context->concreteInterfaceNames->push_back(instantiation->emittedName);
    }
}
void addConcreteHeaderDeclarations(const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::shared_ptr<::app_src_ast_::Program>& program, const std::shared_ptr<std::vector<std::string>>& interfaceKeys) {
    const auto& _iterable_38 = instantiations->interfaces;
    for (const auto& interface_ : *_iterable_38) {
        if (!containsString(interfaceKeys, interface_->key)) {
            continue;
        }
        if ((interface_->name != std::string("Stream")) && (interface_->modulePath != context->modulePath)) {
            continue;
        }
        if ((interface_->name != std::string("Stream")) && !programDeclares(program, interface_->name)) {
            continue;
        }
        auto alternatives = std::string("");
        const auto& _iterable_39 = interface_->implementations;
        for (const auto& implementation : *_iterable_39) {
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
    const auto& _iterable_40 = instantiations->classes;
    for (const auto& instantiation : *_iterable_40) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        if (!programDeclares(program, instantiation->declaration->name)) {
            continue;
        }
        const auto& _iterable_41 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_41) {
            addConcreteTypeForwardDeclarations(plan, context, argument);
        }
        plan->classForwardDeclarations->push_back(((std::string("struct ") + instantiation->emittedName) + std::string(";\n")));
        (context->substitution = instantiation->substitution);
        std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>> methods = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{});
        const auto& _iterable_42 = instantiations->methods;
        for (const auto& method : *_iterable_42) {
            if (method->ownerKey == instantiation->key) {
                methods->push_back(method);
            }
        }
        plan->classDefinitions->push_back(::app_src_emitter_decl_::emitClassDeclaration(instantiation->declaration, context, instantiation->emittedName, methods));
        clearInstantiation(context);
    }
    const auto& _iterable_43 = instantiations->functions;
    for (const auto& instantiation : *_iterable_43) {
        if (instantiation->modulePath != context->modulePath) {
            continue;
        }
        if (!programDeclares(program, instantiation->declaration->name)) {
            continue;
        }
        const auto& _iterable_44 = instantiation->substitution->arguments;
        for (const auto& argument : *_iterable_44) {
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
bool programDeclares(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& name) {
    const auto& _iterable_45 = program->statements;
    for (const auto& statement : *_iterable_45) {
        if (headerDeclarationName(statement) == name) {
            return true;
        }
    }
    return false;
}
std::string headerDeclarationName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return headerDeclarationName(export_->declaration);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return class_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            return interface_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            return fn->name;
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
void addConcreteTypeForwardDeclarations(const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
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
            const auto& _iterable_46 = class_->typeArgs;
            for (const auto& argument : *_iterable_46) {
                addConcreteTypeForwardDeclarations(plan, context, argument);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto& _iterable_47 = interface_->typeArgs;
            for (const auto& argument : *_iterable_47) {
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
            const auto& _iterable_48 = tuple->elements;
            for (const auto& element : *_iterable_48) {
                addConcreteTypeForwardDeclarations(plan, context, element);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_49 = union_->types;
            for (const auto& member : *_iterable_49) {
                addConcreteTypeForwardDeclarations(plan, context, member);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            addConcreteTypeForwardDeclarations(plan, context, weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_50 = function_->params;
            for (const auto& parameter : *_iterable_50) {
                addConcreteTypeForwardDeclarations(plan, context, parameter->type_);
            }
            addConcreteTypeForwardDeclarations(plan, context, function_->returnType);
    }
    else {
    }
    }
}
std::string emitConcreteFunctions(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations) {
    auto result = std::string("");
    const auto& _iterable_51 = instantiations->functions;
    for (const auto& instantiation : *_iterable_51) {
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
void withInstantiation(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
    (context->substitution = std::make_shared<::app_src_semantic_::TypeSubstitution>(names, arguments));
}
void clearInstantiation(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    (context->substitution = nullptr);
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> emitModuleSurfaces(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>> surfaces = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>(std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>{});
    const auto& _iterable_52 = result->modules;
    for (const auto& module : *_iterable_52) {
        std::shared_ptr<std::vector<std::string>> genericTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        std::shared_ptr<std::vector<std::string>> genericFunctions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_53 = module->program->statements;
        for (const auto& statement : *_iterable_53) {
            collectGenericSurfaceSymbols(statement, genericTypes, genericFunctions);
        }
        surfaces->push_back(std::make_shared<::app_src_emitter_context_::EmitModuleSurface>(module->path, module->exports, module->imports, genericTypes, genericFunctions));
    }
    return surfaces;
}
void collectGenericSurfaceSymbols(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<std::vector<std::string>>& typeNames, const std::shared_ptr<std::vector<std::string>>& functionNames) {
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
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
    const auto& _iterable_54 = result->modules;
    for (const auto& module : *_iterable_54) {
        programs->push_back(module->program);
    }
    return programs;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> surfaceImports(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>& surfaces, const std::string& path) {
    const auto& _iterable_55 = surfaces;
    for (const auto& surface : *_iterable_55) {
        if (surface->path == path) {
            return surface->imports;
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{});
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> infoNamespaceImports(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
    const auto& _iterable_56 = result->modules;
    for (const auto& module : *_iterable_56) {
        if (module->path == path) {
            return module->namespaceImports;
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{});
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> infoImports(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
    const auto& _iterable_57 = result->modules;
    for (const auto& module : *_iterable_57) {
        if (module->path == path) {
            return module->imports;
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{});
}
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findGraphModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
    const auto& _iterable_58 = result->modules;
    for (const auto& module : *_iterable_58) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::string>> planModuleInitializationOrder(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::string& entryMode) {
    std::shared_ptr<std::vector<std::string>> order = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> visiting = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    visitInitializationModule(result, entry, entry, entryMode, visiting, visited, order);
    return order;
}
void visitInitializationModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path, const std::string& entry, const std::string& entryMode, const std::shared_ptr<std::vector<std::string>>& visiting, const std::shared_ptr<std::vector<std::string>>& visited, const std::shared_ptr<std::vector<std::string>>& order) {
    if (containsString(visited, path) || containsString(visiting, path)) {
        return;
    }
    const auto info = findGraphModule(result, path);
    if (doof::is_null(info)) {
        return;
    }
    visiting->push_back(path);
    const auto& _iterable_59 = info->imports;
    for (const auto& imported : *_iterable_59) {
        if (!imported->typeOnly) {
            visitInitializationModule(result, imported->sourceModule, entry, entryMode, visiting, visited, order);
        }
    }
    const auto& _iterable_60 = info->namespaceImports;
    for (const auto& imported : *_iterable_60) {
        if (!imported->typeOnly) {
            visitInitializationModule(result, imported->sourceModule, entry, entryMode, visiting, visited, order);
        }
    }
    const auto& _iterable_61 = info->reExports;
    for (const auto& reExport : *_iterable_61) {
        visitInitializationModule(result, reExport, entry, entryMode, visiting, visited, order);
    }
    auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(visiting); if (doof::is_failure(_try_value)) doof::panic_at("src/emitter-module", 675, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    visited->push_back(path);
    const auto scriptEntry = (((path == entry) && ((entryMode == std::string("executable")) || (entryMode == std::string("ios-app")))) && hasScriptStatements(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{info->program})));
    if (!scriptEntry && moduleHasDeferredInitialization(info->program)) {
        order->push_back(path);
    }
}
std::shared_ptr<std::vector<std::string>> moduleInitializationNamespaces(const std::shared_ptr<std::vector<std::string>>& paths) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_62 = paths;
    for (const auto& path : *_iterable_62) {
        result->push_back(::app_src_emitter_names_::moduleNamespace(path));
    }
    return result;
}
std::shared_ptr<ModuleEmission> emitModule(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& moduleName) {
    return std::make_shared<CxxModuleEmitter>(moduleName, std::string(""), std::string(""), std::string(""), std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>>(std::vector<std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>>(std::vector<std::shared_ptr<::app_src_emitter_worldview_::WorldviewModule>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), nullptr, -1, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))->emit(program, std::string("executable"));
}
std::string emitSourceStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
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
                const auto& _iterable_63 = class_->methods;
                for (const auto& method : *_iterable_63) {
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
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(const_), const_->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(readonly_), readonly_->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(binding), binding->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return emitModuleStorage(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(let_), let_->value, context);
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
std::string emitModuleStorage(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto initializer = (isCxxConstantInitializer(value) ? ::app_src_emitter_expr_::emitExpression(value, context, moduleValueType(declaration)) : std::string(""));
    return ::app_src_emitter_decl_::emitModuleValueStorage(declaration, context, initializer);
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> moduleValueType(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration) {
    {
        auto _case_subject = declaration;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return value->resolvedType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return value->resolvedType;
    }
    }
    doof::unreachable();
    return std::monostate{};
}
bool isCxxConstantInitializer(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value) {
    {
        auto _case_subject = value;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
            return (dot->resolvedShorthandOwnerKind == std::string("enum"));
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
bool moduleHasDeferredInitialization(const std::shared_ptr<::app_src_ast_::Program>& program) {
    const auto& _iterable_64 = program->statements;
    for (const auto& statement : *_iterable_64) {
        if (statementHasDeferredInitialization(statement)) {
            return true;
        }
    }
    return false;
}
bool statementHasDeferredInitialization(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return !isCxxConstantInitializer(value->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (class_->native_ || (static_cast<int32_t>((class_->typeParams)->size()) > 0)) {
                return false;
            }
            const auto& _iterable_65 = class_->fields;
            for (const auto& field : *_iterable_65) {
                if (field->static_ && (!doof::is_null(field->defaultValue))) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return statementHasDeferredInitialization(export_->declaration);
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
std::string emitModuleInitializer(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, bool includeValues) {
    auto assignments = std::string("");
    if (includeValues) {
        const auto& _iterable_66 = programs;
        for (const auto& program : *_iterable_66) {
            const auto& _iterable_67 = program->statements;
            for (const auto& statement : *_iterable_67) {
                (assignments = (assignments + emitModuleInitializerStatement(statement, context)));
            }
        }
    }
    if (assignments == std::string("")) {
        return std::string("");
    }
    return ((std::string("\nvoid __doof_initialize_module() {\n") + assignments) + std::string("}\n"));
}
std::string emitModuleInitializerStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return emitModuleValueAssignment(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>>(value), value->value, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            auto result = std::string("");
            if (class_->native_ || (static_cast<int32_t>((class_->typeParams)->size()) > 0)) {
                return result;
            }
            const auto& _iterable_68 = class_->fields;
            for (const auto& field : *_iterable_68) {
                if (!field->static_ || doof::is_null(field->defaultValue)) {
                    continue;
                }
                const auto& _iterable_69 = field->names;
                for (const auto& name : *_iterable_69) {
                    (result = (((((((result + std::string("        ")) + class_->name) + std::string("::")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType)) + std::string(";\n")));
                }
            }
            return result;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return emitModuleInitializerStatement(export_->declaration, context);
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
std::string emitModuleValueAssignment(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& declaration, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (isCxxConstantInitializer(value)) {
        return std::string("");
    }
    const auto name = scriptDeclarationName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration));
    if ((name == std::string("")) || (name == std::string("_"))) {
        return std::string("");
    }
    return ((((std::string("        ") + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, moduleValueType(declaration))) + std::string(";\n"));
}
std::string emitGraphInitializationCall(const std::shared_ptr<std::vector<std::string>>& namespaces) {
    auto result = std::string("");
    const auto& _iterable_70 = namespaces;
    for (const auto& namespace_ : *_iterable_70) {
        (result = (((result + std::string("::")) + namespace_) + std::string("::__doof_initialize_module(); ")));
    }
    return result;
}
std::string emitNativeClassMethods(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto result = std::string("");
    const auto& _iterable_71 = programs;
    for (const auto& program : *_iterable_71) {
        const auto& _iterable_72 = program->statements;
        for (const auto& statement : *_iterable_72) {
            (result = (result + emitNativeClassMethodsForStatement(statement, context)));
        }
    }
    return result;
}
std::string emitNativeClassMethodsForStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (!class_->native_) {
                return std::string("");
            }
            auto result = std::string("");
            const auto& _iterable_73 = class_->methods;
            for (const auto& method : *_iterable_73) {
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
std::string emitMainWrapper(const std::string& moduleName, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, bool hasScript, const std::string& initializationCall) {
    if (!hasScript) {
        const auto signature = (plan->mainAcceptsArgs ? std::string("int main(int argc, char** argv)") : std::string("int main()"));
        const auto argumentSetup = (plan->mainAcceptsArgs ? std::string("std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); ") : std::string(""));
        const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))")) : (moduleName + std::string("::doof_main()")));
        const auto success = (plan->mainReturnsInt ? ((std::string("return ") + call) + std::string(";")) : (call + std::string("; return 0;")));
        const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
        const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
        return (((((((((std::string("\n") + signature) + std::string(" { try { ")) + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
    }
    const auto needsArguments = (plan->mainAcceptsArgs || hasScript);
    const auto signature = (needsArguments ? std::string("int main(int argc, char** argv)") : std::string("int main()"));
    const auto argumentSetup = (needsArguments ? std::string("std::vector<std::string> raw_arguments; for (int i = 1; i < argc; ++i) raw_arguments.emplace_back(argv[i]); auto arguments = std::make_shared<std::vector<std::string>>(std::move(raw_arguments)); ") : std::string(""));
    const auto scriptCall = (hasScript ? (moduleName + std::string("::__doof_run_script(arguments); ")) : std::string(""));
    const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(arguments)")) : (moduleName + std::string("::doof_main()")));
    const auto success = (!plan->hasMain ? (scriptCall + std::string("return 0;")) : (plan->mainReturnsInt ? (((scriptCall + std::string("return ")) + call) + std::string(";")) : ((scriptCall + call) + std::string("; return 0;"))));
    const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
    const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
    return (((((((((std::string("\n") + signature) + std::string(" { try { ")) + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
}
std::string emitAppEntryWrapper(const std::string& moduleName, const std::shared_ptr<::app_src_emitter_header_::HeaderPlan>& plan, bool hasScript, const std::string& initializationCall) {
    if (!hasScript) {
        const auto argumentSetup = (plan->mainAcceptsArgs ? std::string("std::vector<std::string> args; for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]); ") : std::string("(void)argc; (void)argv; "));
        const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(std::make_shared<std::vector<std::string>>(std::move(args)))")) : (moduleName + std::string("::doof_main()")));
        const auto success = (plan->mainReturnsInt ? ((std::string("return ") + call) + std::string(";")) : (call + std::string("; return 0;")));
        const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
        const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
        return (((((((std::string("\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { ") + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
    }
    const auto needsArguments = (plan->mainAcceptsArgs || hasScript);
    const auto argumentSetup = (needsArguments ? std::string("std::vector<std::string> raw_arguments; for (int i = 1; i < argc; ++i) raw_arguments.emplace_back(argv[i]); auto arguments = std::make_shared<std::vector<std::string>>(std::move(raw_arguments)); ") : std::string("(void)argc; (void)argv; "));
    const auto scriptCall = (hasScript ? (moduleName + std::string("::__doof_run_script(arguments); ")) : std::string(""));
    const auto call = (plan->mainAcceptsArgs ? (moduleName + std::string("::doof_main(arguments)")) : (moduleName + std::string("::doof_main()")));
    const auto success = (!plan->hasMain ? (scriptCall + std::string("return 0;")) : (plan->mainReturnsInt ? (((scriptCall + std::string("return ")) + call) + std::string(";")) : ((scriptCall + call) + std::string("; return 0;"))));
    const auto panicHandler = std::string("catch (const doof::Panic& _panic) { std::cerr << \"panic: \" << _panic.what() << std::endl; std::abort(); }");
    const auto actorSetup = std::string("auto& __doof_application_domain = doof::detail::ApplicationDomain::shared(); doof::detail::ActiveActorScope __doof_application_scope(&__doof_application_domain); ");
    return (((((((std::string("\nextern \"C\" int doof_entry_main(int argc, char** argv) { try { ") + actorSetup) + initializationCall) + argumentSetup) + success) + std::string(" } ")) + panicHandler) + std::string(" catch (const std::exception& error) { std::cerr << \"error: \" << error.what() << std::endl; return 1; } }\n"));
}
}
