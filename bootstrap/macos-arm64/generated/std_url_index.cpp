#include "std_url_index.hpp"

namespace std_::url::index {
using namespace ::std_::blob::index;

doof::JsonObject UrlError::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["index"] = doof::json_value(this->index);
    (*_json)["message"] = doof::json_value(this->message);
    return _json;
}
doof::Result<std::shared_ptr<UrlError>, std::string> UrlError::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
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
        return doof::Success<std::shared_ptr<UrlError>>{std::make_shared<UrlError>(_field_kind, _field_index, _field_message)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

bool Path::isEmpty() {
    return (static_cast<int32_t>((this->segments)->size()) == 0);
}
int32_t Path::segmentCount() {
    return static_cast<int32_t>((this->segments)->size());
}
std::string Path::segment(int32_t index) {
    return doof::array_at(this->segments, index, "index", 29);
}
doof::JsonObject Path::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["absolute"] = doof::json_value(this->absolute);
    (*_json)["segments"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->segments->size()); for (const auto& _element : *this->segments) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<Path>, std::string> Path::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_absolute = _object->find("absolute");
    if (_iterator_absolute == _object->end()) { return doof::Failure<std::string>{"Missing required field \"absolute\""}; }
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_absolute->second) : doof::json_is_boolean(_iterator_absolute->second)))) { return doof::Failure<std::string>{"Field \"absolute\" expected boolean but got " + std::string(doof::json_type_name(_iterator_absolute->second))}; }
    auto _field_absolute = (_lenient ? doof::json_as_bool_lenient(_iterator_absolute->second) : doof::json_as_bool(_iterator_absolute->second));
    auto _iterator_segments = _object->find("segments");
    if (_iterator_segments == _object->end()) { return doof::Failure<std::string>{"Missing required field \"segments\""}; }
        if (!(doof::json_is_array(_iterator_segments->second))) { return doof::Failure<std::string>{"Field \"segments\" expected array but got " + std::string(doof::json_type_name(_iterator_segments->second))}; }
    auto _field_segments = [&]() { const auto* _array = doof::json_as_array(_iterator_segments->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
        return doof::Success<std::shared_ptr<Path>>{std::make_shared<Path>(_field_absolute, _field_segments)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

bool Authority::hasUserinfo() {
    return (!doof::is_null(this->userinfo));
}
bool Authority::hasPort() {
    return (!doof::is_null(this->port));
}
doof::JsonObject Authority::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["userinfo"] = (this->userinfo.has_value() ? doof::json_value(this->userinfo.value()) : doof::json_value(nullptr));
    (*_json)["host"] = doof::json_value(this->host);
    (*_json)["port"] = (this->port.has_value() ? doof::json_value(this->port.value()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<Authority>, std::string> Authority::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_userinfo = _object->find("userinfo");
    if (_iterator_userinfo == _object->end()) { return doof::Failure<std::string>{"Missing required field \"userinfo\""}; }
        if (!(doof::json_is_null(_iterator_userinfo->second) || (_lenient ? doof::json_is_lenient_string(_iterator_userinfo->second) : doof::json_is_string(_iterator_userinfo->second)))) { return doof::Failure<std::string>{"Field \"userinfo\" expected string or null but got " + std::string(doof::json_type_name(_iterator_userinfo->second))}; }
    auto _field_userinfo = (doof::json_is_null(_iterator_userinfo->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_userinfo->second) : doof::json_as_string(_iterator_userinfo->second))});
    auto _iterator_host = _object->find("host");
    if (_iterator_host == _object->end()) { return doof::Failure<std::string>{"Missing required field \"host\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_host->second) : doof::json_is_string(_iterator_host->second)))) { return doof::Failure<std::string>{"Field \"host\" expected string but got " + std::string(doof::json_type_name(_iterator_host->second))}; }
    auto _field_host = (_lenient ? doof::json_as_string_lenient(_iterator_host->second) : doof::json_as_string(_iterator_host->second));
    auto _iterator_port = _object->find("port");
    if (_iterator_port == _object->end()) { return doof::Failure<std::string>{"Missing required field \"port\""}; }
        if (!(doof::json_is_null(_iterator_port->second) || (_lenient ? doof::json_is_lenient_string(_iterator_port->second) : doof::json_is_string(_iterator_port->second)))) { return doof::Failure<std::string>{"Field \"port\" expected string or null but got " + std::string(doof::json_type_name(_iterator_port->second))}; }
    auto _field_port = (doof::json_is_null(_iterator_port->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_port->second) : doof::json_as_string(_iterator_port->second))});
        return doof::Success<std::shared_ptr<Authority>>{std::make_shared<Authority>(_field_userinfo, _field_host, _field_port)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

bool QueryParam::hasValue() {
    return (!doof::is_null(this->value));
}
doof::JsonObject QueryParam::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["value"] = (this->value.has_value() ? doof::json_value(this->value.value()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<QueryParam>, std::string> QueryParam::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_value = _object->find("value");
    if (_iterator_value == _object->end()) { return doof::Failure<std::string>{"Missing required field \"value\""}; }
        if (!(doof::json_is_null(_iterator_value->second) || (_lenient ? doof::json_is_lenient_string(_iterator_value->second) : doof::json_is_string(_iterator_value->second)))) { return doof::Failure<std::string>{"Field \"value\" expected string or null but got " + std::string(doof::json_type_name(_iterator_value->second))}; }
    auto _field_value = (doof::json_is_null(_iterator_value->second) ? std::optional<std::string>{std::nullopt} : std::optional<std::string>{(_lenient ? doof::json_as_string_lenient(_iterator_value->second) : doof::json_as_string(_iterator_value->second))});
        return doof::Success<std::shared_ptr<QueryParam>>{std::make_shared<QueryParam>(_field_name, _field_value)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

bool QueryParams::isEmpty() {
    return (static_cast<int32_t>((this->entries)->size()) == 0);
}
int32_t QueryParams::size() {
    return static_cast<int32_t>((this->entries)->size());
}
bool QueryParams::has(const std::string& name) {
    const auto& _iterable_1 = this->entries;
    for (const auto& entry : *_iterable_1) {
        if (entry->name == name) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<QueryParam> QueryParams::first(const std::string& name) {
    const auto& _iterable_2 = this->entries;
    for (const auto& entry : *_iterable_2) {
        if (entry->name == name) {
            return entry;
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> QueryParams::all(const std::string& name) {
    const std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> matches = std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{});
    const auto& _iterable_3 = this->entries;
    for (const auto& entry : *_iterable_3) {
        if (entry->name == name) {
            matches->push_back(entry);
        }
    }
    return doof::array_drainToReadonly(matches, "", 0);
}
doof::JsonObject QueryParams::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["entries"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->entries->size()); for (const auto& _element : *this->entries) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<QueryParams>, std::string> QueryParams::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_entries = _object->find("entries");
    if (_iterator_entries == _object->end()) { return doof::Failure<std::string>{"Missing required field \"entries\""}; }
        if (!(doof::json_is_array(_iterator_entries->second))) { return doof::Failure<std::string>{"Field \"entries\" expected array but got " + std::string(doof::json_type_name(_iterator_entries->second))}; }
    auto _field_entries = [&]() { const auto* _array = doof::json_as_array(_iterator_entries->second); auto _values = std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::json_decode_value(QueryParam::fromJsonValue(_element, _lenient))); } return _values; }();
        return doof::Success<std::shared_ptr<QueryParams>>{std::make_shared<QueryParams>(_field_entries)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
doof::Result<std::shared_ptr<Path>, std::shared_ptr<UrlError>> parsePath(const std::string& text) {
    if (static_cast<int32_t>(text.size()) == 0) {
        return doof::Success<std::shared_ptr<Path>>{ std::make_shared<Path>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) };
    }
    const auto rawSegments = doof::string_split(text, std::string("/"));
    const std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto firstSegment = (doof::string_startsWith(text, std::string("/")) ? 1 : 0);
    for (int32_t index = firstSegment; index < static_cast<int32_t>((rawSegments)->size()); ++index) {
        const auto rawSegment = doof::array_at(rawSegments, index, "index", 100);
        auto _try_value_4 = decodeComponent(rawSegment, false);
        if (doof::is_failure(_try_value_4)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_4))};
        const auto segment = doof::success_value(_try_value_4);
        segments->push_back(segment);
    }
    return doof::Success<std::shared_ptr<Path>>{ std::make_shared<Path>(doof::string_startsWith(text, std::string("/")), doof::array_drainToReadonly(segments, "", 0)) };
}
doof::Result<std::shared_ptr<Authority>, std::shared_ptr<UrlError>> parseAuthority(const std::string& text) {
    std::optional<std::string> userinfo = std::nullopt;
    auto hostPort = text;
    const auto atIndex = findLastChar(text, U'\u0040');
    if (atIndex >= 0) {
        auto _try_value_5 = decodeComponent(doof::string_substring(text, 0, atIndex), false);
        if (doof::is_failure(_try_value_5)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_5))};
        const auto decodedUserinfo = doof::success_value(_try_value_5);
        (userinfo = decodedUserinfo);
        (hostPort = doof::string_slice(text, (atIndex + 1)));
    }
    auto hostText = hostPort;
    std::optional<std::string> port = std::nullopt;
    if (doof::string_startsWith(hostPort, std::string("["))) {
        const auto closeIndex = findChar(hostPort, U'\u005D');
        if (closeIndex < 0) {
            return invalidAuthority(0, std::string("Missing closing bracket in authority host"));
        }
        (hostText = doof::string_substring(hostPort, 0, (closeIndex + 1)));
        if ((closeIndex + 1) < static_cast<int32_t>(hostPort.size())) {
            if (doof::string_at(hostPort, (closeIndex + 1), "", 0) != U'\u003A') {
                return invalidAuthority((closeIndex + 1), std::string("Invalid bracketed authority host"));
            }
            (port = doof::string_slice(hostPort, (closeIndex + 2)));
        }
    } else {
        const auto portSeparator = findSingleChar(hostPort, U'\u003A');
        if (portSeparator >= 0) {
            (hostText = doof::string_substring(hostPort, 0, portSeparator));
            (port = doof::string_slice(hostPort, (portSeparator + 1)));
        }
    }
    auto _try_value_6 = decodeComponent(hostText, false);
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_6))};
    const auto host = doof::success_value(_try_value_6);
    return doof::Success<std::shared_ptr<Authority>>{ std::make_shared<Authority>(userinfo, host, port) };
}
doof::Result<std::shared_ptr<QueryParams>, std::shared_ptr<UrlError>> parseQueryParams(const std::string& text) {
    if (static_cast<int32_t>(text.size()) == 0) {
        return doof::Success<std::shared_ptr<QueryParams>>{ std::make_shared<QueryParams>(std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{})) };
    }
    const std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> entries = std::make_shared<std::vector<std::shared_ptr<QueryParam>>>(std::vector<std::shared_ptr<QueryParam>>{});
    const auto rawEntries = doof::string_split(text, std::string("&"));
    const auto& _iterable_7 = rawEntries;
    for (const auto& rawEntry : *_iterable_7) {
        if (static_cast<int32_t>(rawEntry.size()) == 0) {
            continue;
        }
        const auto separator = doof::string_indexOf(rawEntry, std::string("="));
        if (separator < 0) {
            auto _try_value_8 = decodeComponent(rawEntry, true);
            if (doof::is_failure(_try_value_8)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_8))};
            const auto name = doof::success_value(_try_value_8);
            entries->push_back(std::make_shared<QueryParam>(name, std::nullopt));
            continue;
        }
        auto _try_value_9 = decodeComponent(doof::string_substring(rawEntry, 0, separator), true);
        if (doof::is_failure(_try_value_9)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_9))};
        const auto name = doof::success_value(_try_value_9);
        auto _try_value_10 = decodeComponent(doof::string_slice(rawEntry, (separator + 1)), true);
        if (doof::is_failure(_try_value_10)) return doof::Failure<std::shared_ptr<UrlError>>{doof::variant_promote<std::shared_ptr<UrlError>>(doof::failure_error(_try_value_10))};
        const auto value = doof::success_value(_try_value_10);
        entries->push_back(std::make_shared<QueryParam>(name, value));
    }
    return doof::Success<std::shared_ptr<QueryParams>>{ std::make_shared<QueryParams>(doof::array_drainToReadonly(entries, "", 0)) };
}
doof::Result<std::string, std::shared_ptr<UrlError>> decodeComponent(const std::string& text, bool plusAsSpace) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    auto rawStart = 0;
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        const auto current = doof::string_at(text, index, "", 0);
        if (current == U'\u0025') {
            if (rawStart < index) {
                builder->writeString(doof::string_substring(text, rawStart, index));
            }
            if ((index + 2) >= static_cast<int32_t>(text.size())) {
                return invalidPercentEncoding(index);
            }
            const auto high = hexValue(doof::string_at(text, (index + 1), "", 0));
            const auto low = hexValue(doof::string_at(text, (index + 2), "", 0));
            if ((high < 0) || (low < 0)) {
                return invalidPercentEncoding(index);
            }
            builder->writeByte(static_cast<uint8_t>(((high * 16) + low)));
            (index += 3);
            (rawStart = index);
            continue;
        }
        if (plusAsSpace && (current == U'\u002B')) {
            if (rawStart < index) {
                builder->writeString(doof::string_substring(text, rawStart, index));
            }
            builder->writeString(std::string(" "));
            (index += 1);
            (rawStart = index);
            continue;
        }
        (index += 1);
    }
    if (rawStart < static_cast<int32_t>(text.size())) {
        builder->writeString(doof::string_substring(text, rawStart, static_cast<int32_t>(text.size())));
    }
    const auto bytes = builder->build();
    const auto reader = ::doof_blob::NativeBlobReader::constructor(bytes, ::std_::blob::types::Endian::LittleEndian);
    return doof::Success<std::string>{ reader->readString(reader->length()) };
}
int32_t findChar(const std::string& text, char32_t target) {
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        if (doof::string_at(text, index, "", 0) == target) {
            return index;
        }
        (index += 1);
    }
    return -1;
}
int32_t findLastChar(const std::string& text, char32_t target) {
    auto found = -1;
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        if (doof::string_at(text, index, "", 0) == target) {
            (found = index);
        }
        (index += 1);
    }
    return found;
}
int32_t findSingleChar(const std::string& text, char32_t target) {
    auto found = -1;
    auto index = 0;
    while (index < static_cast<int32_t>(text.size())) {
        if (doof::string_at(text, index, "", 0) == target) {
            if (found >= 0) {
                return -1;
            }
            (found = index);
        }
        (index += 1);
    }
    return found;
}
int32_t hexValue(char32_t value) {
    if ((value >= U'\u0030') && (value <= U'\u0039')) {
        return (static_cast<int32_t>(value) - static_cast<int32_t>(U'\u0030'));
    }
    if ((value >= U'\u0061') && (value <= U'\u0066')) {
        return ((10 + static_cast<int32_t>(value)) - static_cast<int32_t>(U'\u0061'));
    }
    if ((value >= U'\u0041') && (value <= U'\u0046')) {
        return ((10 + static_cast<int32_t>(value)) - static_cast<int32_t>(U'\u0041'));
    }
    return -1;
}
doof::Result<std::string, std::shared_ptr<UrlError>> invalidPercentEncoding(int32_t index) {
    return doof::Failure<std::shared_ptr<UrlError>>{ std::make_shared<UrlError>(std::string("invalid-percent-encoding"), index, ([&]() -> std::string { std::string _interpolation = "Invalid percent encoding at byte "; _interpolation += doof::to_string(index); _interpolation += ""; return _interpolation; }())) };
}
doof::Result<std::shared_ptr<Authority>, std::shared_ptr<UrlError>> invalidAuthority(int32_t index, const std::string& message) {
    return doof::Failure<std::shared_ptr<UrlError>>{ std::make_shared<UrlError>(std::string("invalid-authority"), index, message) };
}
}
