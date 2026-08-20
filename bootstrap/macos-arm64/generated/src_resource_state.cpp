#include "src_resource_state.hpp"

namespace app_src_resource_state_ {
using namespace ::std_::json::index;
int32_t RESOURCE_STATE_VERSION = 1;

doof::JsonObject MaterializedResource::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["sourcePath"] = doof::json_value(this->sourcePath);
    (*_json)["outputPath"] = doof::json_value(this->outputPath);
    (*_json)["sourceSize"] = doof::json_value(this->sourceSize);
    (*_json)["sourceModifiedNanos"] = doof::json_value(this->sourceModifiedNanos);
    (*_json)["outputSize"] = doof::json_value(this->outputSize);
    (*_json)["outputModifiedNanos"] = doof::json_value(this->outputModifiedNanos);
    return _json;
}
doof::Result<std::shared_ptr<MaterializedResource>, std::string> MaterializedResource::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_sourcePath = _object->find("sourcePath");
    if (_iterator_sourcePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourcePath\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourcePath->second) : doof::json_is_string(_iterator_sourcePath->second)))) { return doof::Failure<std::string>{"Field \"sourcePath\" expected string but got " + std::string(doof::json_type_name(_iterator_sourcePath->second))}; }
    auto _field_sourcePath = (_lenient ? doof::json_as_string_lenient(_iterator_sourcePath->second) : doof::json_as_string(_iterator_sourcePath->second));
    auto _iterator_outputPath = _object->find("outputPath");
    if (_iterator_outputPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputPath\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_outputPath->second) : doof::json_is_string(_iterator_outputPath->second)))) { return doof::Failure<std::string>{"Field \"outputPath\" expected string but got " + std::string(doof::json_type_name(_iterator_outputPath->second))}; }
    auto _field_outputPath = (_lenient ? doof::json_as_string_lenient(_iterator_outputPath->second) : doof::json_as_string(_iterator_outputPath->second));
    auto _iterator_sourceSize = _object->find("sourceSize");
    if (_iterator_sourceSize == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceSize\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_sourceSize->second) : doof::json_is_number(_iterator_sourceSize->second)))) { return doof::Failure<std::string>{"Field \"sourceSize\" expected number but got " + std::string(doof::json_type_name(_iterator_sourceSize->second))}; }
    auto _field_sourceSize = (_lenient ? doof::json_as_long_lenient(_iterator_sourceSize->second) : doof::json_as_long(_iterator_sourceSize->second));
    auto _iterator_sourceModifiedNanos = _object->find("sourceModifiedNanos");
    if (_iterator_sourceModifiedNanos == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceModifiedNanos\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_sourceModifiedNanos->second) : doof::json_is_number(_iterator_sourceModifiedNanos->second)))) { return doof::Failure<std::string>{"Field \"sourceModifiedNanos\" expected number but got " + std::string(doof::json_type_name(_iterator_sourceModifiedNanos->second))}; }
    auto _field_sourceModifiedNanos = (_lenient ? doof::json_as_long_lenient(_iterator_sourceModifiedNanos->second) : doof::json_as_long(_iterator_sourceModifiedNanos->second));
    auto _iterator_outputSize = _object->find("outputSize");
    if (_iterator_outputSize == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputSize\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_outputSize->second) : doof::json_is_number(_iterator_outputSize->second)))) { return doof::Failure<std::string>{"Field \"outputSize\" expected number but got " + std::string(doof::json_type_name(_iterator_outputSize->second))}; }
    auto _field_outputSize = (_lenient ? doof::json_as_long_lenient(_iterator_outputSize->second) : doof::json_as_long(_iterator_outputSize->second));
    auto _iterator_outputModifiedNanos = _object->find("outputModifiedNanos");
    if (_iterator_outputModifiedNanos == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputModifiedNanos\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_outputModifiedNanos->second) : doof::json_is_number(_iterator_outputModifiedNanos->second)))) { return doof::Failure<std::string>{"Field \"outputModifiedNanos\" expected number but got " + std::string(doof::json_type_name(_iterator_outputModifiedNanos->second))}; }
    auto _field_outputModifiedNanos = (_lenient ? doof::json_as_long_lenient(_iterator_outputModifiedNanos->second) : doof::json_as_long(_iterator_outputModifiedNanos->second));
        return doof::Success<std::shared_ptr<MaterializedResource>>{std::make_shared<MaterializedResource>(_field_sourcePath, _field_outputPath, _field_sourceSize, _field_sourceModifiedNanos, _field_outputSize, _field_outputModifiedNanos)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::JsonObject ResourceState::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["version"] = doof::json_value(this->version);
    (*_json)["files"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->files->size()); for (const auto& _element : *this->files) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<ResourceState>, std::string> ResourceState::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<int32_t> _field_version;
    if (auto _iterator_version = _object->find("version"); _iterator_version != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_number(_iterator_version->second) : doof::json_is_number(_iterator_version->second)))) { return doof::Failure<std::string>{"Field \"version\" expected number but got " + std::string(doof::json_type_name(_iterator_version->second))}; }
        _field_version = (_lenient ? doof::json_as_int_lenient(_iterator_version->second) : doof::json_as_int(_iterator_version->second));
    } else {
        _field_version = 1;
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<MaterializedResource>>>> _field_files;
    if (auto _iterator_files = _object->find("files"); _iterator_files != _object->end()) {
            if (!(doof::json_is_array(_iterator_files->second))) { return doof::Failure<std::string>{"Field \"files\" expected array but got " + std::string(doof::json_type_name(_iterator_files->second))}; }
        _field_files = [&]() { const auto* _array = doof::json_as_array(_iterator_files->second); auto _values = std::make_shared<std::vector<std::shared_ptr<MaterializedResource>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(MaterializedResource::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_files = std::make_shared<std::vector<std::shared_ptr<MaterializedResource>>>(std::vector<std::shared_ptr<MaterializedResource>>{});
    }
        return doof::Success<std::shared_ptr<ResourceState>>{std::make_shared<ResourceState>(_field_version.value(), _field_files.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
std::shared_ptr<ResourceState> parseResourceState(const std::string& source) {
    auto _binding_value_1 = ::doof_json::parse(source);
    if (doof::is_failure(_binding_value_1)) {
        const auto& value = _binding_value_1;
        return nullptr;
    }
    const auto value = doof::success_value(_binding_value_1);
    auto _binding_value_2 = ResourceState::fromJsonValue(value, true);
    if (doof::is_failure(_binding_value_2)) {
        const auto& state = _binding_value_2;
        return nullptr;
    }
    const auto state = doof::success_value(_binding_value_2);
    if (state->version != RESOURCE_STATE_VERSION) {
        return nullptr;
    }
    return state;
}
std::string renderResourceState(const std::shared_ptr<ResourceState>& state) {
    return (::doof_json::format(doof::json_value(state->toJsonObject())) + std::string("\n"));
}
std::shared_ptr<MaterializedResource> findMaterializedResource(const std::shared_ptr<ResourceState>& state, const std::string& sourcePath, const std::string& outputPath) {
    const auto& _iterable_4 = state->files;
    for (const auto& file : *_iterable_4) {
        if ((file->sourcePath == sourcePath) && (file->outputPath == outputPath)) {
            return file;
        }
    }
    return nullptr;
}
bool materializedResourceIsCurrent(const std::shared_ptr<MaterializedResource>& previous, int64_t sourceSize, int64_t sourceModifiedNanos, int64_t outputSize, int64_t outputModifiedNanos) {
    if (doof::is_null(previous)) {
        return false;
    }
    return ((((previous->sourceSize == sourceSize) && (previous->sourceModifiedNanos == sourceModifiedNanos)) && (previous->outputSize == outputSize)) && (previous->outputModifiedNanos == outputModifiedNanos));
}
}
