#include "std_url_punycode_error.hpp"

namespace std_::url::punycode_error {

doof::JsonObject PunycodeError::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["index"] = doof::json_value(this->index);
    (*_json)["message"] = doof::json_value(this->message);
    return _json;
}
doof::Result<std::shared_ptr<PunycodeError>, std::string> PunycodeError::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_index = _object->find("index");
    if (_iterator_index == _object->end()) { return doof::Failure<std::string>{"Missing required field \"index\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_index->second) : doof::json_is_number(_iterator_index->second)))) { return doof::Failure<std::string>{"Field \"index\" expected number but got " + std::string(doof::json_type_name(_iterator_index->second))}; }
    auto _field_index = (_lenient ? doof::json_as_int_lenient(_iterator_index->second) : doof::json_as_int(_iterator_index->second));
    auto _iterator_message = _object->find("message");
    if (_iterator_message == _object->end()) { return doof::Failure<std::string>{"Missing required field \"message\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_message->second) : doof::json_is_string(_iterator_message->second)))) { return doof::Failure<std::string>{"Field \"message\" expected string but got " + std::string(doof::json_type_name(_iterator_message->second))}; }
    auto _field_message = (_lenient ? doof::json_as_string_lenient(_iterator_message->second) : doof::json_as_string(_iterator_message->second));
        return doof::Success<std::shared_ptr<PunycodeError>>{std::make_shared<PunycodeError>(_field_kind, _field_index, _field_message)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
doof::Result<std::string, std::shared_ptr<PunycodeError>> punycodeFailure__string(const std::string& kind, int32_t index, const std::string& message) {
    return doof::Failure<std::shared_ptr<PunycodeError>>{ std::make_shared<PunycodeError>(kind, index, message) };
}
doof::Result<std::shared_ptr<std::vector<int32_t>>, std::shared_ptr<PunycodeError>> punycodeFailure__array_int(const std::string& kind, int32_t index, const std::string& message) {
    return doof::Failure<std::shared_ptr<PunycodeError>>{ std::make_shared<PunycodeError>(kind, index, message) };
}
}
