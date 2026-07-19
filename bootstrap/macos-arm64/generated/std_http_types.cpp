#include "std_http_types.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::http::types {

doof::JsonObject HttpHeader::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["value"] = doof::json_value(this->value);
    return _json;
}
doof::Result<std::shared_ptr<HttpHeader>, std::string> HttpHeader::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_value = _object->find("value");
    if (_iterator_value == _object->end()) { return doof::Failure<std::string>{"Missing required field \"value\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_value->second) : doof::json_is_string(_iterator_value->second)))) { return doof::Failure<std::string>{"Field \"value\" expected string but got " + std::string(doof::json_type_name(_iterator_value->second))}; }
    auto _field_value = (_lenient ? doof::json_as_string_lenient(_iterator_value->second) : doof::json_as_string(_iterator_value->second));
    return doof::Success<std::shared_ptr<HttpHeader>>{std::make_shared<HttpHeader>(_field_name, _field_value)};
}

doof::JsonObject HttpError::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["code"] = doof::json_value(this->code);
    (*_json)["message"] = doof::json_value(this->message);
    return _json;
}
doof::Result<std::shared_ptr<HttpError>, std::string> HttpError::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_code = _object->find("code");
    if (_iterator_code == _object->end()) { return doof::Failure<std::string>{"Missing required field \"code\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_code->second) : doof::json_is_string(_iterator_code->second)))) { return doof::Failure<std::string>{"Field \"code\" expected string but got " + std::string(doof::json_type_name(_iterator_code->second))}; }
    auto _field_code = (_lenient ? doof::json_as_string_lenient(_iterator_code->second) : doof::json_as_string(_iterator_code->second));
    auto _iterator_message = _object->find("message");
    if (_iterator_message == _object->end()) { return doof::Failure<std::string>{"Missing required field \"message\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_message->second) : doof::json_is_string(_iterator_message->second)))) { return doof::Failure<std::string>{"Field \"message\" expected string but got " + std::string(doof::json_type_name(_iterator_message->second))}; }
    auto _field_message = (_lenient ? doof::json_as_string_lenient(_iterator_message->second) : doof::json_as_string(_iterator_message->second));
    return doof::Success<std::shared_ptr<HttpError>>{std::make_shared<HttpError>(_field_kind, _field_code, _field_message)};
}
}
