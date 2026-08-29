#include "src_frontend_cache.hpp"

namespace app_src_frontend_cache_ {
using namespace ::std_::json::index;
int32_t FRONTEND_CACHE_VERSION = 2;
int32_t FRONTEND_SEMANTIC_ABI = 10;

doof::JsonObject FrontendSourceProbe::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["logicalPath"] = doof::json_value(this->logicalPath);
    (*_json)["sourceHash"] = doof::json_value(this->sourceHash);
    (*_json)["missing"] = doof::json_value(this->missing);
    return _json;
}
doof::Result<std::shared_ptr<FrontendSourceProbe>, std::string> FrontendSourceProbe::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_logicalPath = _object->find("logicalPath");
    if (_iterator_logicalPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"logicalPath\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_logicalPath->second) : doof::json_is_string(_iterator_logicalPath->second)))) { return doof::Failure<std::string>{"Field \"logicalPath\" expected string but got " + std::string(doof::json_type_name(_iterator_logicalPath->second))}; }
    auto _field_logicalPath = (_lenient ? doof::json_as_string_lenient(_iterator_logicalPath->second) : doof::json_as_string(_iterator_logicalPath->second));
    std::optional<std::string> _field_sourceHash;
    if (auto _iterator_sourceHash = _object->find("sourceHash"); _iterator_sourceHash != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceHash->second) : doof::json_is_string(_iterator_sourceHash->second)))) { return doof::Failure<std::string>{"Field \"sourceHash\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceHash->second))}; }
        _field_sourceHash = (_lenient ? doof::json_as_string_lenient(_iterator_sourceHash->second) : doof::json_as_string(_iterator_sourceHash->second));
    } else {
        _field_sourceHash = std::string("");
    }
    std::optional<bool> _field_missing;
    if (auto _iterator_missing = _object->find("missing"); _iterator_missing != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_missing->second) : doof::json_is_boolean(_iterator_missing->second)))) { return doof::Failure<std::string>{"Field \"missing\" expected boolean but got " + std::string(doof::json_type_name(_iterator_missing->second))}; }
        _field_missing = (_lenient ? doof::json_as_bool_lenient(_iterator_missing->second) : doof::json_as_bool(_iterator_missing->second));
    } else {
        _field_missing = false;
    }
        return doof::Success<std::shared_ptr<FrontendSourceProbe>>{std::make_shared<FrontendSourceProbe>(_field_logicalPath, _field_sourceHash.value(), _field_missing.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject FrontendFileInput::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["path"] = doof::json_value(this->path);
    (*_json)["sourceHash"] = doof::json_value(this->sourceHash);
    return _json;
}
doof::Result<std::shared_ptr<FrontendFileInput>, std::string> FrontendFileInput::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_path = _object->find("path");
    if (_iterator_path == _object->end()) { return doof::Failure<std::string>{"Missing required field \"path\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
    auto _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    auto _iterator_sourceHash = _object->find("sourceHash");
    if (_iterator_sourceHash == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceHash\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceHash->second) : doof::json_is_string(_iterator_sourceHash->second)))) { return doof::Failure<std::string>{"Field \"sourceHash\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceHash->second))}; }
    auto _field_sourceHash = (_lenient ? doof::json_as_string_lenient(_iterator_sourceHash->second) : doof::json_as_string(_iterator_sourceHash->second));
        return doof::Success<std::shared_ptr<FrontendFileInput>>{std::make_shared<FrontendFileInput>(_field_path, _field_sourceHash)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject FrontendModuleOutput::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["modulePath"] = doof::json_value(this->modulePath);
    (*_json)["headerName"] = doof::json_value(this->headerName);
    (*_json)["sourceName"] = doof::json_value(this->sourceName);
    (*_json)["fingerprint"] = doof::json_value(this->fingerprint);
    return _json;
}
doof::Result<std::shared_ptr<FrontendModuleOutput>, std::string> FrontendModuleOutput::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_modulePath = _object->find("modulePath");
    if (_iterator_modulePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"modulePath\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_modulePath->second) : doof::json_is_string(_iterator_modulePath->second)))) { return doof::Failure<std::string>{"Field \"modulePath\" expected string but got " + std::string(doof::json_type_name(_iterator_modulePath->second))}; }
    auto _field_modulePath = (_lenient ? doof::json_as_string_lenient(_iterator_modulePath->second) : doof::json_as_string(_iterator_modulePath->second));
    auto _iterator_headerName = _object->find("headerName");
    if (_iterator_headerName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"headerName\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_headerName->second) : doof::json_is_string(_iterator_headerName->second)))) { return doof::Failure<std::string>{"Field \"headerName\" expected string but got " + std::string(doof::json_type_name(_iterator_headerName->second))}; }
    auto _field_headerName = (_lenient ? doof::json_as_string_lenient(_iterator_headerName->second) : doof::json_as_string(_iterator_headerName->second));
    auto _iterator_sourceName = _object->find("sourceName");
    if (_iterator_sourceName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceName\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceName->second) : doof::json_is_string(_iterator_sourceName->second)))) { return doof::Failure<std::string>{"Field \"sourceName\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceName->second))}; }
    auto _field_sourceName = (_lenient ? doof::json_as_string_lenient(_iterator_sourceName->second) : doof::json_as_string(_iterator_sourceName->second));
    std::optional<std::string> _field_fingerprint;
    if (auto _iterator_fingerprint = _object->find("fingerprint"); _iterator_fingerprint != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_fingerprint->second) : doof::json_is_string(_iterator_fingerprint->second)))) { return doof::Failure<std::string>{"Field \"fingerprint\" expected string but got " + std::string(doof::json_type_name(_iterator_fingerprint->second))}; }
        _field_fingerprint = (_lenient ? doof::json_as_string_lenient(_iterator_fingerprint->second) : doof::json_as_string(_iterator_fingerprint->second));
    } else {
        _field_fingerprint = std::string("");
    }
        return doof::Success<std::shared_ptr<FrontendModuleOutput>>{std::make_shared<FrontendModuleOutput>(_field_modulePath, _field_headerName, _field_sourceName, _field_fingerprint.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject FrontendCacheState::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["version"] = doof::json_value(this->version);
    (*_json)["configurationFingerprint"] = doof::json_value(this->configurationFingerprint);
    (*_json)["probes"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->probes->size()); for (const auto& _element : *this->probes) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["fileInputs"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->fileInputs->size()); for (const auto& _element : *this->fileInputs) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["modules"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->modules->size()); for (const auto& _element : *this->modules) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<FrontendCacheState>, std::string> FrontendCacheState::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<int32_t> _field_version;
    if (auto _iterator_version = _object->find("version"); _iterator_version != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_number(_iterator_version->second) : doof::json_is_number(_iterator_version->second)))) { return doof::Failure<std::string>{"Field \"version\" expected number but got " + std::string(doof::json_type_name(_iterator_version->second))}; }
        _field_version = (_lenient ? doof::json_as_int_lenient(_iterator_version->second) : doof::json_as_int(_iterator_version->second));
    } else {
        _field_version = 2;
    }
    auto _iterator_configurationFingerprint = _object->find("configurationFingerprint");
    if (_iterator_configurationFingerprint == _object->end()) { return doof::Failure<std::string>{"Missing required field \"configurationFingerprint\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_configurationFingerprint->second) : doof::json_is_string(_iterator_configurationFingerprint->second)))) { return doof::Failure<std::string>{"Field \"configurationFingerprint\" expected string but got " + std::string(doof::json_type_name(_iterator_configurationFingerprint->second))}; }
    auto _field_configurationFingerprint = (_lenient ? doof::json_as_string_lenient(_iterator_configurationFingerprint->second) : doof::json_as_string(_iterator_configurationFingerprint->second));
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<FrontendSourceProbe>>>> _field_probes;
    if (auto _iterator_probes = _object->find("probes"); _iterator_probes != _object->end()) {
            if (!(doof::json_is_array(_iterator_probes->second))) { return doof::Failure<std::string>{"Field \"probes\" expected array but got " + std::string(doof::json_type_name(_iterator_probes->second))}; }
        _field_probes = [&]() { const auto* _array = doof::json_as_array(_iterator_probes->second); auto _values = std::make_shared<std::vector<std::shared_ptr<FrontendSourceProbe>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(FrontendSourceProbe::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_probes = std::make_shared<std::vector<std::shared_ptr<FrontendSourceProbe>>>(std::vector<std::shared_ptr<FrontendSourceProbe>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<FrontendFileInput>>>> _field_fileInputs;
    if (auto _iterator_fileInputs = _object->find("fileInputs"); _iterator_fileInputs != _object->end()) {
            if (!(doof::json_is_array(_iterator_fileInputs->second))) { return doof::Failure<std::string>{"Field \"fileInputs\" expected array but got " + std::string(doof::json_type_name(_iterator_fileInputs->second))}; }
        _field_fileInputs = [&]() { const auto* _array = doof::json_as_array(_iterator_fileInputs->second); auto _values = std::make_shared<std::vector<std::shared_ptr<FrontendFileInput>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(FrontendFileInput::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_fileInputs = std::make_shared<std::vector<std::shared_ptr<FrontendFileInput>>>(std::vector<std::shared_ptr<FrontendFileInput>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<FrontendModuleOutput>>>> _field_modules;
    if (auto _iterator_modules = _object->find("modules"); _iterator_modules != _object->end()) {
            if (!(doof::json_is_array(_iterator_modules->second))) { return doof::Failure<std::string>{"Field \"modules\" expected array but got " + std::string(doof::json_type_name(_iterator_modules->second))}; }
        _field_modules = [&]() { const auto* _array = doof::json_as_array(_iterator_modules->second); auto _values = std::make_shared<std::vector<std::shared_ptr<FrontendModuleOutput>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(FrontendModuleOutput::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_modules = std::make_shared<std::vector<std::shared_ptr<FrontendModuleOutput>>>(std::vector<std::shared_ptr<FrontendModuleOutput>>{});
    }
        return doof::Success<std::shared_ptr<FrontendCacheState>>{std::make_shared<FrontendCacheState>(_field_version.value(), _field_configurationFingerprint, _field_probes.value(), _field_fileInputs.value(), _field_modules.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
std::shared_ptr<FrontendCacheState> parseFrontendCacheState(const std::string& source) {
    auto _binding_value_1 = ::doof_json::parse(source);
    if (doof::is_failure(_binding_value_1)) {
        const auto& value = _binding_value_1;
        return nullptr;
    }
    const auto value = doof::success_value(_binding_value_1);
    auto _binding_value_2 = FrontendCacheState::fromJsonValue(value, true);
    if (doof::is_failure(_binding_value_2)) {
        const auto& state = _binding_value_2;
        return nullptr;
    }
    const auto state = doof::success_value(_binding_value_2);
    if (state->version != FRONTEND_CACHE_VERSION) {
        return nullptr;
    }
    return state;
}
std::string renderFrontendCacheState(const std::shared_ptr<FrontendCacheState>& state) {
    return (::doof_json::format(doof::json_value(state->toJsonObject())) + std::string("\n"));
}
}
