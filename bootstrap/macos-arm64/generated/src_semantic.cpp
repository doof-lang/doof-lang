#include "src_semantic.hpp"

namespace app_src_semantic_ {

doof::JsonObject SemanticLocation::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["line"] = doof::json_value(this->line);
    (*_json)["column"] = doof::json_value(this->column);
    (*_json)["offset"] = doof::json_value(this->offset);
    return _json;
}
doof::Result<SemanticLocation, std::string> SemanticLocation::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
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
        return doof::Success<SemanticLocation>{SemanticLocation{_field_line, _field_column, _field_offset}};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject SemanticSpan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["start"] = doof::json_value(this->start.toJsonObject());
    (*_json)["end"] = doof::json_value(this->end.toJsonObject());
    return _json;
}
doof::Result<SemanticSpan, std::string> SemanticSpan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_start = _object->find("start");
    if (_iterator_start == _object->end()) { return doof::Failure<std::string>{"Missing required field \"start\""}; }
        if (!(doof::json_is_object(_iterator_start->second))) { return doof::Failure<std::string>{"Field \"start\" expected object but got " + std::string(doof::json_type_name(_iterator_start->second))}; }
    auto _field_start = doof::json_decode_value(SemanticLocation::fromJsonValue(_iterator_start->second, _lenient));
    auto _iterator_end = _object->find("end");
    if (_iterator_end == _object->end()) { return doof::Failure<std::string>{"Missing required field \"end\""}; }
        if (!(doof::json_is_object(_iterator_end->second))) { return doof::Failure<std::string>{"Field \"end\" expected object but got " + std::string(doof::json_type_name(_iterator_end->second))}; }
    auto _field_end = doof::json_decode_value(SemanticLocation::fromJsonValue(_iterator_end->second, _lenient));
        return doof::Success<SemanticSpan>{SemanticSpan{_field_start, _field_end}};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject Diagnostic::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["severity"] = doof::json_value(this->severity);
    (*_json)["message"] = doof::json_value(this->message);
    (*_json)["span"] = doof::json_value(this->span.toJsonObject());
    (*_json)["module"] = doof::json_value(this->module);
    (*_json)["replacement"] = doof::json_value(this->replacement);
    return _json;
}
doof::Result<std::shared_ptr<Diagnostic>, std::string> Diagnostic::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_severity = _object->find("severity");
    if (_iterator_severity == _object->end()) { return doof::Failure<std::string>{"Missing required field \"severity\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_severity->second) : doof::json_is_string(_iterator_severity->second)))) { return doof::Failure<std::string>{"Field \"severity\" expected string but got " + std::string(doof::json_type_name(_iterator_severity->second))}; }
    auto _field_severity = (_lenient ? doof::json_as_string_lenient(_iterator_severity->second) : doof::json_as_string(_iterator_severity->second));
    auto _iterator_message = _object->find("message");
    if (_iterator_message == _object->end()) { return doof::Failure<std::string>{"Missing required field \"message\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_message->second) : doof::json_is_string(_iterator_message->second)))) { return doof::Failure<std::string>{"Field \"message\" expected string but got " + std::string(doof::json_type_name(_iterator_message->second))}; }
    auto _field_message = (_lenient ? doof::json_as_string_lenient(_iterator_message->second) : doof::json_as_string(_iterator_message->second));
    auto _iterator_span = _object->find("span");
    if (_iterator_span == _object->end()) { return doof::Failure<std::string>{"Missing required field \"span\""}; }
        if (!(doof::json_is_object(_iterator_span->second))) { return doof::Failure<std::string>{"Field \"span\" expected object but got " + std::string(doof::json_type_name(_iterator_span->second))}; }
    auto _field_span = doof::json_decode_value(SemanticSpan::fromJsonValue(_iterator_span->second, _lenient));
    auto _iterator_module = _object->find("module");
    if (_iterator_module == _object->end()) { return doof::Failure<std::string>{"Missing required field \"module\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_module->second) : doof::json_is_string(_iterator_module->second)))) { return doof::Failure<std::string>{"Field \"module\" expected string but got " + std::string(doof::json_type_name(_iterator_module->second))}; }
    auto _field_module = (_lenient ? doof::json_as_string_lenient(_iterator_module->second) : doof::json_as_string(_iterator_module->second));
    std::optional<std::string> _field_replacement;
    if (auto _iterator_replacement = _object->find("replacement"); _iterator_replacement != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_replacement->second) : doof::json_is_string(_iterator_replacement->second)))) { return doof::Failure<std::string>{"Field \"replacement\" expected string but got " + std::string(doof::json_type_name(_iterator_replacement->second))}; }
        _field_replacement = (_lenient ? doof::json_as_string_lenient(_iterator_replacement->second) : doof::json_as_string(_iterator_replacement->second));
    } else {
        _field_replacement = std::string("");
    }
        return doof::Success<std::shared_ptr<Diagnostic>>{std::make_shared<Diagnostic>(_field_severity, _field_message, _field_span, _field_module, _field_replacement.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}



doof::JsonObject NamespaceBinding::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["localName"] = doof::json_value(this->localName);
    (*_json)["sourceModule"] = doof::json_value(this->sourceModule);
    (*_json)["typeOnly"] = doof::json_value(this->typeOnly);
    return _json;
}
doof::Result<std::shared_ptr<NamespaceBinding>, std::string> NamespaceBinding::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_localName = _object->find("localName");
    if (_iterator_localName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"localName\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_localName->second) : doof::json_is_string(_iterator_localName->second)))) { return doof::Failure<std::string>{"Field \"localName\" expected string but got " + std::string(doof::json_type_name(_iterator_localName->second))}; }
    auto _field_localName = (_lenient ? doof::json_as_string_lenient(_iterator_localName->second) : doof::json_as_string(_iterator_localName->second));
    auto _iterator_sourceModule = _object->find("sourceModule");
    if (_iterator_sourceModule == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceModule\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceModule->second) : doof::json_is_string(_iterator_sourceModule->second)))) { return doof::Failure<std::string>{"Field \"sourceModule\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceModule->second))}; }
    auto _field_sourceModule = (_lenient ? doof::json_as_string_lenient(_iterator_sourceModule->second) : doof::json_as_string(_iterator_sourceModule->second));
    auto _iterator_typeOnly = _object->find("typeOnly");
    if (_iterator_typeOnly == _object->end()) { return doof::Failure<std::string>{"Missing required field \"typeOnly\""}; }
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_typeOnly->second) : doof::json_is_boolean(_iterator_typeOnly->second)))) { return doof::Failure<std::string>{"Field \"typeOnly\" expected boolean but got " + std::string(doof::json_type_name(_iterator_typeOnly->second))}; }
    auto _field_typeOnly = (_lenient ? doof::json_as_bool_lenient(_iterator_typeOnly->second) : doof::json_as_bool(_iterator_typeOnly->second));
        return doof::Success<std::shared_ptr<NamespaceBinding>>{std::make_shared<NamespaceBinding>(_field_localName, _field_sourceModule, _field_typeOnly)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject SourceFile::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["path"] = doof::json_value(this->path);
    (*_json)["source"] = doof::json_value(this->source);
    return _json;
}
doof::Result<std::shared_ptr<SourceFile>, std::string> SourceFile::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_path = _object->find("path");
    if (_iterator_path == _object->end()) { return doof::Failure<std::string>{"Missing required field \"path\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
    auto _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    auto _iterator_source = _object->find("source");
    if (_iterator_source == _object->end()) { return doof::Failure<std::string>{"Missing required field \"source\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_source->second) : doof::json_is_string(_iterator_source->second)))) { return doof::Failure<std::string>{"Field \"source\" expected string but got " + std::string(doof::json_type_name(_iterator_source->second))}; }
    auto _field_source = (_lenient ? doof::json_as_string_lenient(_iterator_source->second) : doof::json_as_string(_iterator_source->second));
        return doof::Success<std::shared_ptr<SourceFile>>{std::make_shared<SourceFile>(_field_path, _field_source)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject PrimitiveType::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["name"] = doof::json_value(this->name);
    return _json;
}
doof::Result<std::shared_ptr<PrimitiveType>, std::string> PrimitiveType::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_kind;
    if (auto _iterator_kind = _object->find("kind"); _iterator_kind != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
        _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    } else {
        _field_kind = std::string("primitive");
    }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
        return doof::Success<std::shared_ptr<PrimitiveType>>{std::make_shared<PrimitiveType>(_field_kind.value(), _field_name)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}












doof::JsonObject RangeResolvedType::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    return _json;
}
doof::Result<std::shared_ptr<RangeResolvedType>, std::string> RangeResolvedType::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_kind;
    if (auto _iterator_kind = _object->find("kind"); _iterator_kind != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
        _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    } else {
        _field_kind = std::string("range");
    }
        return doof::Success<std::shared_ptr<RangeResolvedType>>{std::make_shared<RangeResolvedType>(_field_kind.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject JsonValueResolvedType::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    return _json;
}
doof::Result<std::shared_ptr<JsonValueResolvedType>, std::string> JsonValueResolvedType::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_kind;
    if (auto _iterator_kind = _object->find("kind"); _iterator_kind != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
        _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    } else {
        _field_kind = std::string("json-value");
    }
        return doof::Success<std::shared_ptr<JsonValueResolvedType>>{std::make_shared<JsonValueResolvedType>(_field_kind.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}





doof::JsonObject NoneType::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    return _json;
}
doof::Result<std::shared_ptr<NoneType>, std::string> NoneType::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_kind;
    if (auto _iterator_kind = _object->find("kind"); _iterator_kind != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
        _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    } else {
        _field_kind = std::string("none");
    }
        return doof::Success<std::shared_ptr<NoneType>>{std::make_shared<NoneType>(_field_kind.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject NeverType::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    return _json;
}
doof::Result<std::shared_ptr<NeverType>, std::string> NeverType::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_kind;
    if (auto _iterator_kind = _object->find("kind"); _iterator_kind != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
        _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    } else {
        _field_kind = std::string("never");
    }
        return doof::Success<std::shared_ptr<NeverType>>{std::make_shared<NeverType>(_field_kind.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject UnknownType::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    return _json;
}
doof::Result<std::shared_ptr<UnknownType>, std::string> UnknownType::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::string> _field_kind;
    if (auto _iterator_kind = _object->find("kind"); _iterator_kind != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
        _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    } else {
        _field_kind = std::string("unknown");
    }
        return doof::Success<std::shared_ptr<UnknownType>>{std::make_shared<UnknownType>(_field_kind.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}








doof::JsonObject CheckResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["diagnostics"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->diagnostics->size()); for (const auto& _element : *this->diagnostics) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<CheckResult>, std::string> CheckResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<Diagnostic>>>> _field_diagnostics;
    if (auto _iterator_diagnostics = _object->find("diagnostics"); _iterator_diagnostics != _object->end()) {
            if (!(doof::json_is_array(_iterator_diagnostics->second))) { return doof::Failure<std::string>{"Field \"diagnostics\" expected array but got " + std::string(doof::json_type_name(_iterator_diagnostics->second))}; }
        _field_diagnostics = [&]() { const auto* _array = doof::json_as_array(_iterator_diagnostics->second); auto _values = std::make_shared<std::vector<std::shared_ptr<Diagnostic>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(Diagnostic::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_diagnostics = std::make_shared<std::vector<std::shared_ptr<Diagnostic>>>(std::vector<std::shared_ptr<Diagnostic>>{});
    }
        return doof::Success<std::shared_ptr<CheckResult>>{std::make_shared<CheckResult>(_field_diagnostics.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
}
