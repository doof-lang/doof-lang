#include "src_ast.hpp"
#include <cmath>
#include "src_semantic.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_ast_ {
using namespace ::app_src_semantic_;

doof::JsonObject AstLocation::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["line"] = doof::json_value(this->line);
    (*_json)["column"] = doof::json_value(this->column);
    (*_json)["offset"] = doof::json_value(this->offset);
    return _json;
}
doof::Result<AstLocation, std::string> AstLocation::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_line = _object->find("line");
    if (_iterator_line == _object->end()) { return doof::Failure<std::string>{"Missing required field \"line\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_line->second) : doof::json_is_number(_iterator_line->second)))) { return doof::Failure<std::string>{"Field \"line\" expected number but got " + std::string(doof::json_type_name(_iterator_line->second))}; }
    auto _field_line = (_lenient ? doof::json_as_int_lenient(_iterator_line->second) : doof::json_as_int(_iterator_line->second));
    auto _iterator_column = _object->find("column");
    if (_iterator_column == _object->end()) { return doof::Failure<std::string>{"Missing required field \"column\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_column->second) : doof::json_is_number(_iterator_column->second)))) { return doof::Failure<std::string>{"Field \"column\" expected number but got " + std::string(doof::json_type_name(_iterator_column->second))}; }
    auto _field_column = (_lenient ? doof::json_as_int_lenient(_iterator_column->second) : doof::json_as_int(_iterator_column->second));
    auto _iterator_offset = _object->find("offset");
    if (_iterator_offset == _object->end()) { return doof::Failure<std::string>{"Missing required field \"offset\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_offset->second) : doof::json_is_number(_iterator_offset->second)))) { return doof::Failure<std::string>{"Field \"offset\" expected number but got " + std::string(doof::json_type_name(_iterator_offset->second))}; }
    auto _field_offset = (_lenient ? doof::json_as_int_lenient(_iterator_offset->second) : doof::json_as_int(_iterator_offset->second));
    return doof::Success<AstLocation>{AstLocation{_field_line, _field_column, _field_offset}};
}

doof::JsonObject SourceSpan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["start"] = doof::json_value(this->start.toJsonObject());
    (*_json)["end"] = doof::json_value(this->end.toJsonObject());
    return _json;
}
doof::Result<SourceSpan, std::string> SourceSpan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_start = _object->find("start");
    if (_iterator_start == _object->end()) { return doof::Failure<std::string>{"Missing required field \"start\""}; }
    if (!(doof::json_is_object(_iterator_start->second))) { return doof::Failure<std::string>{"Field \"start\" expected object but got " + std::string(doof::json_type_name(_iterator_start->second))}; }
    auto _field_start = doof::success_value(AstLocation::fromJsonValue(_iterator_start->second, _lenient));
    auto _iterator_end = _object->find("end");
    if (_iterator_end == _object->end()) { return doof::Failure<std::string>{"Missing required field \"end\""}; }
    if (!(doof::json_is_object(_iterator_end->second))) { return doof::Failure<std::string>{"Field \"end\" expected object but got " + std::string(doof::json_type_name(_iterator_end->second))}; }
    auto _field_end = doof::success_value(AstLocation::fromJsonValue(_iterator_end->second, _lenient));
    return doof::Success<SourceSpan>{SourceSpan{_field_start, _field_end}};
}
























































doof::JsonObject WildcardPattern::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<WildcardPattern>, std::string> WildcardPattern::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<WildcardPattern>>{std::make_shared<WildcardPattern>(_field_kind, _field_span)};
}









doof::JsonObject BreakStatement::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["label"] = (this->label.has_value() ? doof::json_value(this->label.value()) : doof::json_value(nullptr));
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<BreakStatement>, std::string> BreakStatement::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_label = _object->find("label");
    if (_iterator_label == _object->end()) { return doof::Failure<std::string>{"Missing required field \"label\""}; }
    if (!(doof::json_is_null(_iterator_label->second) || (_lenient ? doof::json_is_lenient_string(_iterator_label->second) : doof::json_is_string(_iterator_label->second)))) { return doof::Failure<std::string>{"Field \"label\" expected string or null but got " + std::string(doof::json_type_name(_iterator_label->second))}; }
    auto _field_label = (doof::json_is_null(_iterator_label->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_label->second) : doof::json_as_string(_iterator_label->second))});
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<BreakStatement>>{std::make_shared<BreakStatement>(_field_kind, _field_label, _field_span)};
}

doof::JsonObject ContinueStatement::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["label"] = (this->label.has_value() ? doof::json_value(this->label.value()) : doof::json_value(nullptr));
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<ContinueStatement>, std::string> ContinueStatement::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_label = _object->find("label");
    if (_iterator_label == _object->end()) { return doof::Failure<std::string>{"Missing required field \"label\""}; }
    if (!(doof::json_is_null(_iterator_label->second) || (_lenient ? doof::json_is_lenient_string(_iterator_label->second) : doof::json_is_string(_iterator_label->second)))) { return doof::Failure<std::string>{"Field \"label\" expected string or null but got " + std::string(doof::json_type_name(_iterator_label->second))}; }
    auto _field_label = (doof::json_is_null(_iterator_label->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_label->second) : doof::json_as_string(_iterator_label->second))});
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<ContinueStatement>>{std::make_shared<ContinueStatement>(_field_kind, _field_label, _field_span)};
}



doof::JsonObject DestructureBinding::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["alias"] = (this->alias.has_value() ? doof::json_value(this->alias.value()) : doof::json_value(nullptr));
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<DestructureBinding>, std::string> DestructureBinding::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    std::optional<std::optional<std::string>> _field_alias;
    if (auto _iterator_alias = _object->find("alias"); _iterator_alias != _object->end()) {
        if (!(doof::json_is_null(_iterator_alias->second) || (_lenient ? doof::json_is_lenient_string(_iterator_alias->second) : doof::json_is_string(_iterator_alias->second)))) { return doof::Failure<std::string>{"Field \"alias\" expected string or null but got " + std::string(doof::json_type_name(_iterator_alias->second))}; }
        _field_alias = (doof::json_is_null(_iterator_alias->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_alias->second) : doof::json_as_string(_iterator_alias->second))});
    } else {
        _field_alias = std::optional<std::string>{std::nullopt};
    }
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<DestructureBinding>>{std::make_shared<DestructureBinding>(_field_name, _field_alias.value(), _field_span)};
}









doof::JsonObject NamedImport::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["alias"] = (this->alias.has_value() ? doof::json_value(this->alias.value()) : doof::json_value(nullptr));
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<NamedImport>, std::string> NamedImport::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_alias = _object->find("alias");
    if (_iterator_alias == _object->end()) { return doof::Failure<std::string>{"Missing required field \"alias\""}; }
    if (!(doof::json_is_null(_iterator_alias->second) || (_lenient ? doof::json_is_lenient_string(_iterator_alias->second) : doof::json_is_string(_iterator_alias->second)))) { return doof::Failure<std::string>{"Field \"alias\" expected string or null but got " + std::string(doof::json_type_name(_iterator_alias->second))}; }
    auto _field_alias = (doof::json_is_null(_iterator_alias->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_alias->second) : doof::json_as_string(_iterator_alias->second))});
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<NamedImport>>{std::make_shared<NamedImport>(_field_kind, _field_name, _field_alias, _field_span)};
}

doof::JsonObject NamespaceImport::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["alias"] = doof::json_value(this->alias);
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<NamespaceImport>, std::string> NamespaceImport::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_alias = _object->find("alias");
    if (_iterator_alias == _object->end()) { return doof::Failure<std::string>{"Missing required field \"alias\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_alias->second) : doof::json_is_string(_iterator_alias->second)))) { return doof::Failure<std::string>{"Field \"alias\" expected string but got " + std::string(doof::json_type_name(_iterator_alias->second))}; }
    auto _field_alias = (_lenient ? doof::json_as_string_lenient(_iterator_alias->second) : doof::json_as_string(_iterator_alias->second));
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<NamespaceImport>>{std::make_shared<NamespaceImport>(_field_kind, _field_alias, _field_span)};
}


doof::JsonObject MockImportMapping::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["dependency"] = doof::json_value(this->dependency);
    (*_json)["replacement"] = doof::json_value(this->replacement);
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<MockImportMapping>, std::string> MockImportMapping::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_dependency = _object->find("dependency");
    if (_iterator_dependency == _object->end()) { return doof::Failure<std::string>{"Missing required field \"dependency\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_dependency->second) : doof::json_is_string(_iterator_dependency->second)))) { return doof::Failure<std::string>{"Field \"dependency\" expected string but got " + std::string(doof::json_type_name(_iterator_dependency->second))}; }
    auto _field_dependency = (_lenient ? doof::json_as_string_lenient(_iterator_dependency->second) : doof::json_as_string(_iterator_dependency->second));
    auto _iterator_replacement = _object->find("replacement");
    if (_iterator_replacement == _object->end()) { return doof::Failure<std::string>{"Missing required field \"replacement\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_replacement->second) : doof::json_is_string(_iterator_replacement->second)))) { return doof::Failure<std::string>{"Field \"replacement\" expected string but got " + std::string(doof::json_type_name(_iterator_replacement->second))}; }
    auto _field_replacement = (_lenient ? doof::json_as_string_lenient(_iterator_replacement->second) : doof::json_as_string(_iterator_replacement->second));
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<MockImportMapping>>{std::make_shared<MockImportMapping>(_field_dependency, _field_replacement, _field_span)};
}

doof::JsonObject MockImportDirective::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["sourcePattern"] = doof::json_value(this->sourcePattern);
    (*_json)["mappings"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->mappings->size()); for (const auto& _element : *this->mappings) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<MockImportDirective>, std::string> MockImportDirective::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_sourcePattern = _object->find("sourcePattern");
    if (_iterator_sourcePattern == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourcePattern\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourcePattern->second) : doof::json_is_string(_iterator_sourcePattern->second)))) { return doof::Failure<std::string>{"Field \"sourcePattern\" expected string but got " + std::string(doof::json_type_name(_iterator_sourcePattern->second))}; }
    auto _field_sourcePattern = (_lenient ? doof::json_as_string_lenient(_iterator_sourcePattern->second) : doof::json_as_string(_iterator_sourcePattern->second));
    auto _iterator_mappings = _object->find("mappings");
    if (_iterator_mappings == _object->end()) { return doof::Failure<std::string>{"Missing required field \"mappings\""}; }
    if (!(doof::json_is_array(_iterator_mappings->second))) { return doof::Failure<std::string>{"Field \"mappings\" expected array but got " + std::string(doof::json_type_name(_iterator_mappings->second))}; }
    auto _field_mappings = [&]() { const auto* _array = doof::json_as_array(_iterator_mappings->second); auto _values = std::make_shared<std::vector<std::shared_ptr<MockImportMapping>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(MockImportMapping::fromJsonValue(_element, _lenient))); } return _values; }();
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<MockImportDirective>>{std::make_shared<MockImportDirective>(_field_kind, _field_sourcePattern, _field_mappings, _field_span)};
}


doof::JsonObject ExportSpecifier::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["alias"] = (this->alias.has_value() ? doof::json_value(this->alias.value()) : doof::json_value(nullptr));
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<ExportSpecifier>, std::string> ExportSpecifier::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_alias = _object->find("alias");
    if (_iterator_alias == _object->end()) { return doof::Failure<std::string>{"Missing required field \"alias\""}; }
    if (!(doof::json_is_null(_iterator_alias->second) || (_lenient ? doof::json_is_lenient_string(_iterator_alias->second) : doof::json_is_string(_iterator_alias->second)))) { return doof::Failure<std::string>{"Field \"alias\" expected string or null but got " + std::string(doof::json_type_name(_iterator_alias->second))}; }
    auto _field_alias = (doof::json_is_null(_iterator_alias->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_alias->second) : doof::json_as_string(_iterator_alias->second))});
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<ExportSpecifier>>{std::make_shared<ExportSpecifier>(_field_name, _field_alias, _field_span)};
}

doof::JsonObject ExportList::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["specifiers"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->specifiers->size()); for (const auto& _element : *this->specifiers) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["source"] = (this->source.has_value() ? doof::json_value(this->source.value()) : doof::json_value(nullptr));
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<ExportList>, std::string> ExportList::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_specifiers = _object->find("specifiers");
    if (_iterator_specifiers == _object->end()) { return doof::Failure<std::string>{"Missing required field \"specifiers\""}; }
    if (!(doof::json_is_array(_iterator_specifiers->second))) { return doof::Failure<std::string>{"Field \"specifiers\" expected array but got " + std::string(doof::json_type_name(_iterator_specifiers->second))}; }
    auto _field_specifiers = [&]() { const auto* _array = doof::json_as_array(_iterator_specifiers->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ExportSpecifier>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(ExportSpecifier::fromJsonValue(_element, _lenient))); } return _values; }();
    auto _iterator_source = _object->find("source");
    if (_iterator_source == _object->end()) { return doof::Failure<std::string>{"Missing required field \"source\""}; }
    if (!(doof::json_is_null(_iterator_source->second) || (_lenient ? doof::json_is_lenient_string(_iterator_source->second) : doof::json_is_string(_iterator_source->second)))) { return doof::Failure<std::string>{"Field \"source\" expected string or null but got " + std::string(doof::json_type_name(_iterator_source->second))}; }
    auto _field_source = (doof::json_is_null(_iterator_source->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_source->second) : doof::json_as_string(_iterator_source->second))});
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
    if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::success_value(SourceSpan::fromJsonValue(_iterator_span->second, _lenient));
    return doof::Success<std::shared_ptr<ExportList>>{std::make_shared<ExportList>(_field_kind, _field_specifiers, _field_source, _field_span)};
}

}
