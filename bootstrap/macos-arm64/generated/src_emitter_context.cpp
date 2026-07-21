#include "src_emitter_context.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_context_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;

doof::JsonObject EmitModuleSurface::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["path"] = doof::json_value(this->path);
    (*_json)["exports"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->exports->size()); for (const auto& _element : *this->exports) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["imports"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->imports->size()); for (const auto& _element : *this->imports) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["genericTypes"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->genericTypes->size()); for (const auto& _element : *this->genericTypes) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["genericFunctions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->genericFunctions->size()); for (const auto& _element : *this->genericFunctions) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<EmitModuleSurface>, std::string> EmitModuleSurface::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_path = _object->find("path");
    if (_iterator_path == _object->end()) { return doof::Failure<std::string>{"Missing required field \"path\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
    auto _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>> _field_exports;
    if (auto _iterator_exports = _object->find("exports"); _iterator_exports != _object->end()) {
        if (!(doof::json_is_array(_iterator_exports->second))) { return doof::Failure<std::string>{"Field \"exports\" expected array but got " + std::string(doof::json_type_name(_iterator_exports->second))}; }
        _field_exports = [&]() { const auto* _array = doof::json_as_array(_iterator_exports->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_semantic_::Symbol::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_exports = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>> _field_imports;
    if (auto _iterator_imports = _object->find("imports"); _iterator_imports != _object->end()) {
        if (!(doof::json_is_array(_iterator_imports->second))) { return doof::Failure<std::string>{"Field \"imports\" expected array but got " + std::string(doof::json_type_name(_iterator_imports->second))}; }
        _field_imports = [&]() { const auto* _array = doof::json_as_array(_iterator_imports->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_semantic_::ImportBinding::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_imports = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_genericTypes;
    if (auto _iterator_genericTypes = _object->find("genericTypes"); _iterator_genericTypes != _object->end()) {
        if (!(doof::json_is_array(_iterator_genericTypes->second))) { return doof::Failure<std::string>{"Field \"genericTypes\" expected array but got " + std::string(doof::json_type_name(_iterator_genericTypes->second))}; }
        _field_genericTypes = [&]() { const auto* _array = doof::json_as_array(_iterator_genericTypes->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_genericTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_genericFunctions;
    if (auto _iterator_genericFunctions = _object->find("genericFunctions"); _iterator_genericFunctions != _object->end()) {
        if (!(doof::json_is_array(_iterator_genericFunctions->second))) { return doof::Failure<std::string>{"Field \"genericFunctions\" expected array but got " + std::string(doof::json_type_name(_iterator_genericFunctions->second))}; }
        _field_genericFunctions = [&]() { const auto* _array = doof::json_as_array(_iterator_genericFunctions->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_genericFunctions = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    return doof::Success<std::shared_ptr<EmitModuleSurface>>{std::make_shared<EmitModuleSurface>(_field_path, _field_exports.value(), _field_imports.value(), _field_genericTypes.value(), _field_genericFunctions.value())};
}

doof::JsonObject SourceLocationSpanOverride::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<SourceLocationSpanOverride>, std::string> SourceLocationSpanOverride::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(::app_src_ast_::SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<SourceLocationSpanOverride>>{std::make_shared<SourceLocationSpanOverride>(_field_span)};
}

void recordCoverageLine(std::shared_ptr<EmitContext> context, int32_t line) {
    const auto& _iterable_1 = context->coverageInstrumentedLines;
    for (const auto& existing : *_iterable_1) {
        if (existing == line) {
            return;
        }
    }
    context->coverageInstrumentedLines->push_back(line);
}
bool isCapturedMutable(std::shared_ptr<EmitContext> context, std::string name) {
    const auto& _iterable_2 = context->capturedMutables;
    for (const auto& captured : *_iterable_2) {
        if (captured == name) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<EmitContext> createEmitContext(std::shared_ptr<::app_src_ast_::Program> program) {
    return createEmitContextForPrograms(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}));
}
std::shared_ptr<EmitContext> createEmitContextForPrograms(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs) {
    return std::make_shared<EmitContext>(std::string(""), programs, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<EmitModuleSurface>>>(std::vector<std::shared_ptr<EmitModuleSurface>>{}), std::string(""), false, false, std::string(""), std::string(""), false, std::string(""), std::monostate{}, nullptr, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), nullptr, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), 0, false, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
}
std::shared_ptr<EmitContext> createEmitContextForModule(std::shared_ptr<::app_src_ast_::Program> program, std::string modulePath, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> allPrograms) {
    auto programs = allPrograms;
    if (static_cast<int32_t>((programs)->size()) == 0) {
        (programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}));
    }
    const auto context = createEmitContextForPrograms(programs);
    (context->modulePath = modulePath);
    return context;
}
}
