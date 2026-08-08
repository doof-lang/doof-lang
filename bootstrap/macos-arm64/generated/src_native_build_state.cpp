#include "src_native_build_state.hpp"

namespace app_src_native_build_state_ {
using namespace ::std_::json::index;
int32_t NATIVE_BUILD_STATE_VERSION = 2;

doof::JsonObject NativeInputSignature::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["path"] = doof::json_value(this->path);
    (*_json)["signature"] = doof::json_value(this->signature);
    (*_json)["contentHash"] = doof::json_value(this->contentHash);
    (*_json)["size"] = doof::json_value(this->size);
    (*_json)["modifiedNanos"] = doof::json_value(this->modifiedNanos);
    return _json;
}
doof::Result<std::shared_ptr<NativeInputSignature>, std::string> NativeInputSignature::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_path = _object->find("path");
    if (_iterator_path == _object->end()) { return doof::Failure<std::string>{"Missing required field \"path\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
    auto _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    auto _iterator_signature = _object->find("signature");
    if (_iterator_signature == _object->end()) { return doof::Failure<std::string>{"Missing required field \"signature\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_signature->second) : doof::json_is_string(_iterator_signature->second)))) { return doof::Failure<std::string>{"Field \"signature\" expected string but got " + std::string(doof::json_type_name(_iterator_signature->second))}; }
    auto _field_signature = (_lenient ? doof::json_as_string_lenient(_iterator_signature->second) : doof::json_as_string(_iterator_signature->second));
    std::optional<bool> _field_contentHash;
    if (auto _iterator_contentHash = _object->find("contentHash"); _iterator_contentHash != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_contentHash->second) : doof::json_is_boolean(_iterator_contentHash->second)))) { return doof::Failure<std::string>{"Field \"contentHash\" expected boolean but got " + std::string(doof::json_type_name(_iterator_contentHash->second))}; }
        _field_contentHash = (_lenient ? doof::json_as_bool_lenient(_iterator_contentHash->second) : doof::json_as_bool(_iterator_contentHash->second));
    } else {
        _field_contentHash = true;
    }
    std::optional<int64_t> _field_size;
    if (auto _iterator_size = _object->find("size"); _iterator_size != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_size->second) : doof::json_is_number(_iterator_size->second)))) { return doof::Failure<std::string>{"Field \"size\" expected number but got " + std::string(doof::json_type_name(_iterator_size->second))}; }
        _field_size = (_lenient ? doof::json_as_long_lenient(_iterator_size->second) : doof::json_as_long(_iterator_size->second));
    } else {
        _field_size = -1LL;
    }
    std::optional<int64_t> _field_modifiedNanos;
    if (auto _iterator_modifiedNanos = _object->find("modifiedNanos"); _iterator_modifiedNanos != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_modifiedNanos->second) : doof::json_is_number(_iterator_modifiedNanos->second)))) { return doof::Failure<std::string>{"Field \"modifiedNanos\" expected number but got " + std::string(doof::json_type_name(_iterator_modifiedNanos->second))}; }
        _field_modifiedNanos = (_lenient ? doof::json_as_long_lenient(_iterator_modifiedNanos->second) : doof::json_as_long(_iterator_modifiedNanos->second));
    } else {
        _field_modifiedNanos = -1LL;
    }
    return doof::Success<std::shared_ptr<NativeInputSignature>>{std::make_shared<NativeInputSignature>(_field_path, _field_signature, _field_contentHash.value(), _field_size.value(), _field_modifiedNanos.value())};
}

doof::JsonObject NativeTaskState::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["id"] = doof::json_value(this->id);
    (*_json)["fingerprint"] = doof::json_value(this->fingerprint);
    (*_json)["outputPath"] = doof::json_value(this->outputPath);
    (*_json)["outputSize"] = doof::json_value(this->outputSize);
    (*_json)["outputModifiedNanos"] = doof::json_value(this->outputModifiedNanos);
    (*_json)["inputs"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->inputs->size()); for (const auto& _element : *this->inputs) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<NativeTaskState>, std::string> NativeTaskState::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_id = _object->find("id");
    if (_iterator_id == _object->end()) { return doof::Failure<std::string>{"Missing required field \"id\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_id->second) : doof::json_is_string(_iterator_id->second)))) { return doof::Failure<std::string>{"Field \"id\" expected string but got " + std::string(doof::json_type_name(_iterator_id->second))}; }
    auto _field_id = (_lenient ? doof::json_as_string_lenient(_iterator_id->second) : doof::json_as_string(_iterator_id->second));
    auto _iterator_fingerprint = _object->find("fingerprint");
    if (_iterator_fingerprint == _object->end()) { return doof::Failure<std::string>{"Missing required field \"fingerprint\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_fingerprint->second) : doof::json_is_string(_iterator_fingerprint->second)))) { return doof::Failure<std::string>{"Field \"fingerprint\" expected string but got " + std::string(doof::json_type_name(_iterator_fingerprint->second))}; }
    auto _field_fingerprint = (_lenient ? doof::json_as_string_lenient(_iterator_fingerprint->second) : doof::json_as_string(_iterator_fingerprint->second));
    auto _iterator_outputPath = _object->find("outputPath");
    if (_iterator_outputPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputPath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_outputPath->second) : doof::json_is_string(_iterator_outputPath->second)))) { return doof::Failure<std::string>{"Field \"outputPath\" expected string but got " + std::string(doof::json_type_name(_iterator_outputPath->second))}; }
    auto _field_outputPath = (_lenient ? doof::json_as_string_lenient(_iterator_outputPath->second) : doof::json_as_string(_iterator_outputPath->second));
    auto _iterator_outputSize = _object->find("outputSize");
    if (_iterator_outputSize == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputSize\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_outputSize->second) : doof::json_is_number(_iterator_outputSize->second)))) { return doof::Failure<std::string>{"Field \"outputSize\" expected number but got " + std::string(doof::json_type_name(_iterator_outputSize->second))}; }
    auto _field_outputSize = (_lenient ? doof::json_as_long_lenient(_iterator_outputSize->second) : doof::json_as_long(_iterator_outputSize->second));
    auto _iterator_outputModifiedNanos = _object->find("outputModifiedNanos");
    if (_iterator_outputModifiedNanos == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputModifiedNanos\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_outputModifiedNanos->second) : doof::json_is_number(_iterator_outputModifiedNanos->second)))) { return doof::Failure<std::string>{"Field \"outputModifiedNanos\" expected number but got " + std::string(doof::json_type_name(_iterator_outputModifiedNanos->second))}; }
    auto _field_outputModifiedNanos = (_lenient ? doof::json_as_long_lenient(_iterator_outputModifiedNanos->second) : doof::json_as_long(_iterator_outputModifiedNanos->second));
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<NativeInputSignature>>>> _field_inputs;
    if (auto _iterator_inputs = _object->find("inputs"); _iterator_inputs != _object->end()) {
        if (!(doof::json_is_array(_iterator_inputs->second))) { return doof::Failure<std::string>{"Field \"inputs\" expected array but got " + std::string(doof::json_type_name(_iterator_inputs->second))}; }
        _field_inputs = [&]() { const auto* _array = doof::json_as_array(_iterator_inputs->second); auto _values = std::make_shared<std::vector<std::shared_ptr<NativeInputSignature>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(NativeInputSignature::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_inputs = std::make_shared<std::vector<std::shared_ptr<NativeInputSignature>>>(std::vector<std::shared_ptr<NativeInputSignature>>{});
    }
    return doof::Success<std::shared_ptr<NativeTaskState>>{std::make_shared<NativeTaskState>(_field_id, _field_fingerprint, _field_outputPath, _field_outputSize, _field_outputModifiedNanos, _field_inputs.value())};
}

doof::JsonObject NativeBuildState::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["version"] = doof::json_value(this->version);
    (*_json)["tasks"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->tasks->size()); for (const auto& _element : *this->tasks) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["managedOutputs"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->managedOutputs->size()); for (const auto& _element : *this->managedOutputs) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<NativeBuildState>, std::string> NativeBuildState::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<int32_t> _field_version;
    if (auto _iterator_version = _object->find("version"); _iterator_version != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_version->second) : doof::json_is_number(_iterator_version->second)))) { return doof::Failure<std::string>{"Field \"version\" expected number but got " + std::string(doof::json_type_name(_iterator_version->second))}; }
        _field_version = (_lenient ? doof::json_as_int_lenient(_iterator_version->second) : doof::json_as_int(_iterator_version->second));
    } else {
        _field_version = 2;
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<NativeTaskState>>>> _field_tasks;
    if (auto _iterator_tasks = _object->find("tasks"); _iterator_tasks != _object->end()) {
        if (!(doof::json_is_array(_iterator_tasks->second))) { return doof::Failure<std::string>{"Field \"tasks\" expected array but got " + std::string(doof::json_type_name(_iterator_tasks->second))}; }
        _field_tasks = [&]() { const auto* _array = doof::json_as_array(_iterator_tasks->second); auto _values = std::make_shared<std::vector<std::shared_ptr<NativeTaskState>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(NativeTaskState::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_tasks = std::make_shared<std::vector<std::shared_ptr<NativeTaskState>>>(std::vector<std::shared_ptr<NativeTaskState>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_managedOutputs;
    if (auto _iterator_managedOutputs = _object->find("managedOutputs"); _iterator_managedOutputs != _object->end()) {
        if (!(doof::json_is_array(_iterator_managedOutputs->second))) { return doof::Failure<std::string>{"Field \"managedOutputs\" expected array but got " + std::string(doof::json_type_name(_iterator_managedOutputs->second))}; }
        _field_managedOutputs = [&]() { const auto* _array = doof::json_as_array(_iterator_managedOutputs->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_managedOutputs = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    return doof::Success<std::shared_ptr<NativeBuildState>>{std::make_shared<NativeBuildState>(_field_version.value(), _field_tasks.value(), _field_managedOutputs.value())};
}
std::shared_ptr<NativeBuildState> parseNativeBuildState(const std::string& source) {
    auto _binding_value_1 = ::doof_json::parse(source);
    if (doof::is_failure(_binding_value_1)) {
        const auto& value = _binding_value_1;
        return nullptr;
    }
    const auto value = doof::success_value(_binding_value_1);
    auto _binding_value_2 = NativeBuildState::fromJsonValue(value, true);
    if (doof::is_failure(_binding_value_2)) {
        const auto& state = _binding_value_2;
        return nullptr;
    }
    const auto state = doof::success_value(_binding_value_2);
    if (state->version != NATIVE_BUILD_STATE_VERSION) {
        return nullptr;
    }
    return state;
}
std::string renderNativeBuildState(const std::shared_ptr<NativeBuildState>& state) {
    return (::doof_json::format(doof::json_value(state->toJsonObject())) + std::string("\n"));
}
std::shared_ptr<NativeTaskState> findNativeTaskState(const std::shared_ptr<NativeBuildState>& state, const std::string& id) {
    const auto& _iterable_3 = state->tasks;
    for (const auto& task : *_iterable_3) {
        if (task->id == id) {
            return task;
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::string>> parseMakeDependencies(const std::string& source) {
    const auto flattened = doof::string_replaceAll(doof::string_replaceAll(source, std::string("\\\r\n"), std::string(" ")), std::string("\\\n"), std::string(" "));
    auto colon = -1;
    auto escaped = false;
    for (int32_t index = 0; index < static_cast<int32_t>(flattened.size()); ++index) {
        const auto char_ = doof::string_at(flattened, index, "src/native-build-state", 54);
        if (!escaped && (char_ == U'\u003A')) {
            (colon = index);
            break;
        }
        if ((char_ == U'\\') && !escaped) {
            (escaped = true);
        } else {
            (escaped = false);
        }
    }
    if (colon < 0) {
        return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto current = std::string("");
    (escaped = false);
    for (int32_t index = (colon + 1); index < static_cast<int32_t>(flattened.size()); ++index) {
        const auto char_ = doof::string_at(flattened, index, "src/native-build-state", 63);
        if (escaped) {
            (current = (current + doof::to_string(char_)));
            (escaped = false);
            continue;
        }
        if (char_ == U'\\') {
            (escaped = true);
            continue;
        }
        if ((((char_ == U'\u0020') || (char_ == U'\t')) || (char_ == U'\r')) || (char_ == U'\n')) {
            if (current != std::string("")) {
                appendUnique(result, current);
                (current = std::string(""));
            }
            continue;
        }
        (current = (current + doof::to_string(char_)));
    }
    if (escaped) {
        (current = (current + std::string("\\")));
    }
    if (current != std::string("")) {
        appendUnique(result, current);
    }
    return result;
}
std::shared_ptr<std::vector<std::string>> parseMsvcDependencies(const std::string& source) {
    auto _binding_value_4 = ::doof_json::parse(source);
    if (doof::is_failure(_binding_value_4)) {
        const auto& parsed = _binding_value_4;
        return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    const auto parsed = doof::success_value(_binding_value_4);
    auto _binding_value_5 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = parsed; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_5)) {
        const auto& root = _binding_value_5;
        return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    const auto root = doof::success_value(_binding_value_5);
    auto _binding_value_6 = doof::map_get(root, std::string("Data"), "", 0);
    if (doof::is_failure(_binding_value_6)) {
        const auto& dataValue = _binding_value_6;
        return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    const auto dataValue = doof::success_value(_binding_value_6);
    auto _binding_value_7 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = dataValue; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_7)) {
        const auto& data = _binding_value_7;
        return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    const auto data = doof::success_value(_binding_value_7);
    auto _binding_value_8 = doof::map_get(data, std::string("Includes"), "", 0);
    if (doof::is_failure(_binding_value_8)) {
        const auto& includesValue = _binding_value_8;
        return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    const auto includesValue = doof::success_value(_binding_value_8);
    auto _binding_value_9 = [&]() -> doof::Result<std::shared_ptr<std::vector<doof::JsonValue>>, std::string> { auto _as_value = includesValue; if (doof::json_is_array(_as_value)) return doof::Success<std::shared_ptr<std::vector<doof::JsonValue>>>{std::get<doof::JsonArray>(doof::json_storage(_as_value))}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_9)) {
        const auto& includes = _binding_value_9;
        return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    const auto includes = doof::success_value(_binding_value_9);
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_10 = includes;
    for (const auto& value : *_iterable_10) {
        auto _binding_value_11 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = value; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
        if (doof::is_failure(_binding_value_11)) {
            const auto& path = _binding_value_11;
            continue;
        }
        const auto path = doof::success_value(_binding_value_11);
        appendUnique(result, path);
    }
    return result;
}
void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    const auto& _iterable_12 = values;
    for (const auto& existing : *_iterable_12) {
        if (existing == value) {
            return;
        }
    }
    values->push_back(value);
}
}
