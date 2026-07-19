#include "std_fs_types.hpp"
#include <cmath>
#include "std_time_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::fs::types {
using namespace ::std_::time::index;

doof::JsonObject FileInfo::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["kind"] = doof::json_value(EntryKind_name(this->kind));
    (*_json)["size"] = doof::json_value(this->size);
    (*_json)["modifiedAt"] = doof::json_value(this->modifiedAt->toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<FileInfo>, std::string> FileInfo::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!(doof::json_is_string(_iterator_kind->second))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = EntryKind_fromName(doof::json_as_string(_iterator_kind->second)).value();
    auto _iterator_size = _object->find("size");
    if (_iterator_size == _object->end()) { return doof::Failure<std::string>{"Missing required field \"size\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_size->second) : doof::json_is_number(_iterator_size->second)))) { return doof::Failure<std::string>{"Field \"size\" expected number but got " + std::string(doof::json_type_name(_iterator_size->second))}; }
    auto _field_size = (_lenient ? doof::json_as_long_lenient(_iterator_size->second) : doof::json_as_long(_iterator_size->second));
    auto _iterator_modifiedAt = _object->find("modifiedAt");
    if (_iterator_modifiedAt == _object->end()) { return doof::Failure<std::string>{"Missing required field \"modifiedAt\""}; }
    if (!(doof::json_is_object(_iterator_modifiedAt->second))) { return doof::Failure<std::string>{"Field \"modifiedAt\" expected object but got " + std::string(doof::json_type_name(_iterator_modifiedAt->second))}; }
    auto _field_modifiedAt = doof::success_value(::std_::time::temporal::Instant::fromJsonValue(_iterator_modifiedAt->second, _lenient));
    return doof::Success<std::shared_ptr<FileInfo>>{std::make_shared<FileInfo>(_field_name, _field_kind, _field_size, _field_modifiedAt)};
}
}
