#include "src_ios_device.hpp"
#include <cmath>
#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "std_time_index.hpp"
#include "src_ios_app.hpp"
#include "std_blob_index.hpp"
#include "std_http_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_ios_device_ {
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
using namespace ::std_::time::index;
using namespace ::app_src_ios_app_;
using namespace ::std_::blob::index;
const auto MAX_IOS_DEVICE_COMMAND_OUTPUT_BYTES = 262144LL;

doof::JsonObject IOSDevice::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["identifier"] = doof::json_value(this->identifier);
    (*_json)["name"] = doof::json_value(this->name);
    return _json;
}
doof::Result<std::shared_ptr<IOSDevice>, std::string> IOSDevice::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_identifier = _object->find("identifier");
    if (_iterator_identifier == _object->end()) { return doof::Failure<std::string>{"Missing required field \"identifier\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_identifier->second) : doof::json_is_string(_iterator_identifier->second)))) { return doof::Failure<std::string>{"Field \"identifier\" expected string but got " + std::string(doof::json_type_name(_iterator_identifier->second))}; }
    auto _field_identifier = (_lenient ? doof::json_as_string_lenient(_iterator_identifier->second) : doof::json_as_string(_iterator_identifier->second));
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    return doof::Success<std::shared_ptr<IOSDevice>>{std::make_shared<IOSDevice>(_field_identifier, _field_name)};
}

doof::JsonObject IOSCodesignIdentity::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["fingerprint"] = doof::json_value(this->fingerprint);
    (*_json)["name"] = doof::json_value(this->name);
    return _json;
}
doof::Result<std::shared_ptr<IOSCodesignIdentity>, std::string> IOSCodesignIdentity::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_fingerprint = _object->find("fingerprint");
    if (_iterator_fingerprint == _object->end()) { return doof::Failure<std::string>{"Missing required field \"fingerprint\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_fingerprint->second) : doof::json_is_string(_iterator_fingerprint->second)))) { return doof::Failure<std::string>{"Field \"fingerprint\" expected string but got " + std::string(doof::json_type_name(_iterator_fingerprint->second))}; }
    auto _field_fingerprint = (_lenient ? doof::json_as_string_lenient(_iterator_fingerprint->second) : doof::json_as_string(_iterator_fingerprint->second));
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    return doof::Success<std::shared_ptr<IOSCodesignIdentity>>{std::make_shared<IOSCodesignIdentity>(_field_fingerprint, _field_name)};
}

doof::JsonObject IOSProvisioningProfile::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["profilePath"] = doof::json_value(this->profilePath);
    (*_json)["applicationIdentifier"] = doof::json_value(this->applicationIdentifier);
    (*_json)["certFingerprints"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->certFingerprints->size()); for (const auto& _element : *this->certFingerprints) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["expirationEpochMs"] = doof::json_value(this->expirationEpochMs);
    (*_json)["provisionedDeviceCount"] = doof::json_value(this->provisionedDeviceCount);
    (*_json)["provisionsAllDevices"] = doof::json_value(this->provisionsAllDevices);
    (*_json)["getTaskAllow"] = doof::json_value(this->getTaskAllow);
    return _json;
}
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> IOSProvisioningProfile::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_profilePath = _object->find("profilePath");
    if (_iterator_profilePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"profilePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_profilePath->second) : doof::json_is_string(_iterator_profilePath->second)))) { return doof::Failure<std::string>{"Field \"profilePath\" expected string but got " + std::string(doof::json_type_name(_iterator_profilePath->second))}; }
    auto _field_profilePath = (_lenient ? doof::json_as_string_lenient(_iterator_profilePath->second) : doof::json_as_string(_iterator_profilePath->second));
    auto _iterator_applicationIdentifier = _object->find("applicationIdentifier");
    if (_iterator_applicationIdentifier == _object->end()) { return doof::Failure<std::string>{"Missing required field \"applicationIdentifier\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_applicationIdentifier->second) : doof::json_is_string(_iterator_applicationIdentifier->second)))) { return doof::Failure<std::string>{"Field \"applicationIdentifier\" expected string but got " + std::string(doof::json_type_name(_iterator_applicationIdentifier->second))}; }
    auto _field_applicationIdentifier = (_lenient ? doof::json_as_string_lenient(_iterator_applicationIdentifier->second) : doof::json_as_string(_iterator_applicationIdentifier->second));
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_certFingerprints;
    if (auto _iterator_certFingerprints = _object->find("certFingerprints"); _iterator_certFingerprints != _object->end()) {
        if (!(doof::json_is_array(_iterator_certFingerprints->second))) { return doof::Failure<std::string>{"Field \"certFingerprints\" expected array but got " + std::string(doof::json_type_name(_iterator_certFingerprints->second))}; }
        _field_certFingerprints = [&]() { const auto* _array = doof::json_as_array(_iterator_certFingerprints->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_certFingerprints = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    auto _iterator_expirationEpochMs = _object->find("expirationEpochMs");
    if (_iterator_expirationEpochMs == _object->end()) { return doof::Failure<std::string>{"Missing required field \"expirationEpochMs\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_expirationEpochMs->second) : doof::json_is_number(_iterator_expirationEpochMs->second)))) { return doof::Failure<std::string>{"Field \"expirationEpochMs\" expected number but got " + std::string(doof::json_type_name(_iterator_expirationEpochMs->second))}; }
    auto _field_expirationEpochMs = (_lenient ? doof::json_as_long_lenient(_iterator_expirationEpochMs->second) : doof::json_as_long(_iterator_expirationEpochMs->second));
    std::optional<int32_t> _field_provisionedDeviceCount;
    if (auto _iterator_provisionedDeviceCount = _object->find("provisionedDeviceCount"); _iterator_provisionedDeviceCount != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_provisionedDeviceCount->second) : doof::json_is_number(_iterator_provisionedDeviceCount->second)))) { return doof::Failure<std::string>{"Field \"provisionedDeviceCount\" expected number but got " + std::string(doof::json_type_name(_iterator_provisionedDeviceCount->second))}; }
        _field_provisionedDeviceCount = (_lenient ? doof::json_as_int_lenient(_iterator_provisionedDeviceCount->second) : doof::json_as_int(_iterator_provisionedDeviceCount->second));
    } else {
        _field_provisionedDeviceCount = int32_t{0};
    }
    std::optional<bool> _field_provisionsAllDevices;
    if (auto _iterator_provisionsAllDevices = _object->find("provisionsAllDevices"); _iterator_provisionsAllDevices != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_provisionsAllDevices->second) : doof::json_is_boolean(_iterator_provisionsAllDevices->second)))) { return doof::Failure<std::string>{"Field \"provisionsAllDevices\" expected boolean but got " + std::string(doof::json_type_name(_iterator_provisionsAllDevices->second))}; }
        _field_provisionsAllDevices = (_lenient ? doof::json_as_bool_lenient(_iterator_provisionsAllDevices->second) : doof::json_as_bool(_iterator_provisionsAllDevices->second));
    } else {
        _field_provisionsAllDevices = bool{false};
    }
    std::optional<bool> _field_getTaskAllow;
    if (auto _iterator_getTaskAllow = _object->find("getTaskAllow"); _iterator_getTaskAllow != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_getTaskAllow->second) : doof::json_is_boolean(_iterator_getTaskAllow->second)))) { return doof::Failure<std::string>{"Field \"getTaskAllow\" expected boolean but got " + std::string(doof::json_type_name(_iterator_getTaskAllow->second))}; }
        _field_getTaskAllow = (_lenient ? doof::json_as_bool_lenient(_iterator_getTaskAllow->second) : doof::json_as_bool(_iterator_getTaskAllow->second));
    } else {
        _field_getTaskAllow = bool{false};
    }
    return doof::Success<std::shared_ptr<IOSProvisioningProfile>>{std::make_shared<IOSProvisioningProfile>(_field_profilePath, _field_applicationIdentifier, _field_certFingerprints.value(), _field_expirationEpochMs, _field_provisionedDeviceCount.value(), _field_provisionsAllDevices.value(), _field_getTaskAllow.value())};
}

doof::JsonObject IOSDeviceSigningOptions::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["signIdentity"] = doof::json_value(this->signIdentity);
    (*_json)["provisioningProfilePath"] = doof::json_value(this->provisioningProfilePath);
    return _json;
}
doof::Result<std::shared_ptr<IOSDeviceSigningOptions>, std::string> IOSDeviceSigningOptions::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_signIdentity = _object->find("signIdentity");
    if (_iterator_signIdentity == _object->end()) { return doof::Failure<std::string>{"Missing required field \"signIdentity\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_signIdentity->second) : doof::json_is_string(_iterator_signIdentity->second)))) { return doof::Failure<std::string>{"Field \"signIdentity\" expected string but got " + std::string(doof::json_type_name(_iterator_signIdentity->second))}; }
    auto _field_signIdentity = (_lenient ? doof::json_as_string_lenient(_iterator_signIdentity->second) : doof::json_as_string(_iterator_signIdentity->second));
    auto _iterator_provisioningProfilePath = _object->find("provisioningProfilePath");
    if (_iterator_provisioningProfilePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"provisioningProfilePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_provisioningProfilePath->second) : doof::json_is_string(_iterator_provisioningProfilePath->second)))) { return doof::Failure<std::string>{"Field \"provisioningProfilePath\" expected string but got " + std::string(doof::json_type_name(_iterator_provisioningProfilePath->second))}; }
    auto _field_provisioningProfilePath = (_lenient ? doof::json_as_string_lenient(_iterator_provisioningProfilePath->second) : doof::json_as_string(_iterator_provisioningProfilePath->second));
    return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{std::make_shared<IOSDeviceSigningOptions>(_field_signIdentity, _field_provisioningProfilePath)};
}

doof::JsonObject IOSDeviceCommandResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["exitCode"] = doof::json_value(this->exitCode);
    (*_json)["output"] = doof::json_value(this->output);
    (*_json)["error"] = doof::json_value(this->error);
    return _json;
}
doof::Result<std::shared_ptr<IOSDeviceCommandResult>, std::string> IOSDeviceCommandResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_exitCode = _object->find("exitCode");
    if (_iterator_exitCode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"exitCode\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_exitCode->second) : doof::json_is_number(_iterator_exitCode->second)))) { return doof::Failure<std::string>{"Field \"exitCode\" expected number but got " + std::string(doof::json_type_name(_iterator_exitCode->second))}; }
    auto _field_exitCode = (_lenient ? doof::json_as_int_lenient(_iterator_exitCode->second) : doof::json_as_int(_iterator_exitCode->second));
    std::optional<std::string> _field_output;
    if (auto _iterator_output = _object->find("output"); _iterator_output != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_output->second) : doof::json_is_string(_iterator_output->second)))) { return doof::Failure<std::string>{"Field \"output\" expected string but got " + std::string(doof::json_type_name(_iterator_output->second))}; }
        _field_output = (_lenient ? doof::json_as_string_lenient(_iterator_output->second) : doof::json_as_string(_iterator_output->second));
    } else {
        _field_output = std::string{std::string("")};
    }
    std::optional<std::string> _field_error;
    if (auto _iterator_error = _object->find("error"); _iterator_error != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_error->second) : doof::json_is_string(_iterator_error->second)))) { return doof::Failure<std::string>{"Field \"error\" expected string but got " + std::string(doof::json_type_name(_iterator_error->second))}; }
        _field_error = (_lenient ? doof::json_as_string_lenient(_iterator_error->second) : doof::json_as_string(_iterator_error->second));
    } else {
        _field_error = std::string{std::string("")};
    }
    return doof::Success<std::shared_ptr<IOSDeviceCommandResult>>{std::make_shared<IOSDeviceCommandResult>(_field_exitCode, _field_output.value(), _field_error.value())};
}
std::variant<std::monostate, doof::JsonValue> jsonObjectField(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name) {
    if (!(object->find(name) != object->end())) {
        return std::monostate{};
    }
    auto _binding_value_1 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_1)) {
        const auto& value = _binding_value_1;
        return std::monostate{};
    }
    const auto value = doof::success_value(_binding_value_1);
    return value;
}
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> jsonObjectValue(std::variant<std::monostate, doof::JsonValue> value) {
    if (doof::is_null(value)) {
        return nullptr;
    }
    {
        auto _case_subject = std::get<doof::JsonValue>(value);
        if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
            return object;
    }
    else {
            return nullptr;
    }
    }
}
std::shared_ptr<std::vector<doof::JsonValue>> jsonArrayValue(std::variant<std::monostate, doof::JsonValue> value) {
    if (doof::is_null(value)) {
        return std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    }
    {
        auto _case_subject = std::get<doof::JsonValue>(value);
        if (doof::json_is_array(_case_subject)) {
            const auto array = std::get<doof::JsonArray>(doof::json_storage(_case_subject));
            return array;
    }
    else {
            return std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    }
    }
}
std::string jsonStringValue(std::variant<std::monostate, doof::JsonValue> value) {
    if (doof::is_null(value)) {
        return std::string("");
    }
    {
        auto _case_subject = std::get<doof::JsonValue>(value);
        if (doof::json_is_string(_case_subject)) {
            const auto text = doof::json_as_string(_case_subject);
            return text;
    }
    else {
            return std::string("");
    }
    }
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>, std::string> parseConnectedIOSDevices(std::string rawJson) {
    auto _binding_value_2 = ::std_::json::index::parseJsonValue(rawJson);
    if (doof::is_failure(_binding_value_2)) {
        const auto error = doof::failure_error(_binding_value_2);
        return doof::Failure<std::string>{ error };
    }
    const auto parsed = doof::success_value(_binding_value_2);
    const auto root = jsonObjectValue(parsed);
    if (doof::is_null(root)) {
        return doof::Failure<std::string>{ std::string("Invalid devicectl device JSON: expected an object") };
    }
    const auto result = jsonObjectValue(jsonObjectField(doof::unwrap_optional(root), std::string("result")));
    if (doof::is_null(result)) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>>{ std::make_shared<std::vector<std::shared_ptr<IOSDevice>>>(std::vector<std::shared_ptr<IOSDevice>>{}) };
    }
    const auto values = jsonArrayValue(jsonObjectField(doof::unwrap_optional(result), std::string("devices")));
    std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>> devices = std::make_shared<std::vector<std::shared_ptr<IOSDevice>>>(std::vector<std::shared_ptr<IOSDevice>>{});
    const auto& _iterable_3 = values;
    for (const auto& value : *_iterable_3) {
        const auto device = jsonObjectValue(value);
        if (doof::is_null(device)) {
            continue;
        }
        const auto identifier = jsonStringValue(jsonObjectField(doof::unwrap_optional(device), std::string("identifier")));
        const auto deviceProperties = jsonObjectValue(jsonObjectField(doof::unwrap_optional(device), std::string("deviceProperties")));
        const auto hardwareProperties = jsonObjectValue(jsonObjectField(doof::unwrap_optional(device), std::string("hardwareProperties")));
        const auto connectionProperties = jsonObjectValue(jsonObjectField(doof::unwrap_optional(device), std::string("connectionProperties")));
        const auto name = (doof::is_null(deviceProperties) ? std::string("") : jsonStringValue(jsonObjectField(doof::unwrap_optional(deviceProperties), std::string("name"))));
        const auto platformName = (doof::is_null(hardwareProperties) ? std::string("") : jsonStringValue(jsonObjectField(doof::unwrap_optional(hardwareProperties), std::string("platform"))));
        const auto reality = (doof::is_null(hardwareProperties) ? std::string("") : jsonStringValue(jsonObjectField(doof::unwrap_optional(hardwareProperties), std::string("reality"))));
        const auto tunnelState = (doof::is_null(connectionProperties) ? std::string("") : jsonStringValue(jsonObjectField(doof::unwrap_optional(connectionProperties), std::string("tunnelState"))));
        if (((identifier == std::string("")) || (platformName != std::string("iOS"))) || (tunnelState != std::string("connected"))) {
            continue;
        }
        if ((reality != std::string("")) && (reality != std::string("physical"))) {
            continue;
        }
        devices->push_back(std::make_shared<IOSDevice>(identifier, ((name == std::string("")) ? identifier : name)));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>>{ devices };
}
doof::Result<std::string, std::string> selectIOSDeviceIdentifier(std::string overrideIdentifier, std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>> devices) {
    if (overrideIdentifier != std::string("")) {
        return doof::Success<std::string>{ overrideIdentifier };
    }
    if (static_cast<int32_t>((devices)->size()) == 0) {
        return doof::Failure<std::string>{ std::string("Could not auto-detect a connected iOS device. Connect a device or pass --ios-device.") };
    }
    if (static_cast<int32_t>((devices)->size()) > 1) {
        auto choices = std::string("");
        for (int32_t index = 0; index < static_cast<int32_t>((devices)->size()); ++index) {
            if (index > 0) {
                (choices += std::string(", "));
            }
            (choices += ((((*devices)[index]->name + std::string(" (")) + (*devices)[index]->identifier) + std::string(")")));
        }
        return doof::Failure<std::string>{ ((std::string("Multiple connected iOS devices found (") + choices) + std::string("). Pass --ios-device to select one.")) };
    }
    return doof::Success<std::string>{ (*devices)[0]->identifier };
}
bool isHexFingerprint(std::string value) {
    if (static_cast<int32_t>(value.size()) != 40) {
        return false;
    }
    const auto hex = std::string("0123456789ABCDEF");
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
        if (!doof::string_contains(hex, doof::string_toUpperCase(doof::string_substring(value, index, (index + 1))))) {
            return false;
        }
    }
    return true;
}
std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> parseCodesignIdentities(std::string output) {
    std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities = std::make_shared<std::vector<std::shared_ptr<IOSCodesignIdentity>>>(std::vector<std::shared_ptr<IOSCodesignIdentity>>{});
    const auto& _iterable_4 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_4) {
        const auto closeParen = doof::string_indexOf(line, std::string(")"));
        if (closeParen < 0) {
            continue;
        }
        const auto remainder = doof::string_trim(doof::string_substring(line, (closeParen + 1), static_cast<int32_t>(line.size())));
        const auto separator = doof::string_indexOf(remainder, std::string(" "));
        if (separator < 0) {
            continue;
        }
        const auto fingerprint = doof::string_toUpperCase(doof::string_substring(remainder, 0, separator));
        const auto quotedName = doof::string_trim(doof::string_substring(remainder, (separator + 1), static_cast<int32_t>(remainder.size())));
        if (((!isHexFingerprint(fingerprint) || (static_cast<int32_t>(quotedName.size()) < 2)) || !doof::string_startsWith(quotedName, std::string("\""))) || !doof::string_endsWith(quotedName, std::string("\""))) {
            continue;
        }
        identities->push_back(std::make_shared<IOSCodesignIdentity>(fingerprint, doof::string_substring(quotedName, 1, (static_cast<int32_t>(quotedName.size()) - 1))));
    }
    return identities;
}
std::string provisionedBundleId(std::string applicationIdentifier) {
    const auto separator = doof::string_indexOf(applicationIdentifier, std::string("."));
    if (separator < 0) {
        return std::string("");
    }
    return doof::string_substring(applicationIdentifier, (separator + 1), static_cast<int32_t>(applicationIdentifier.size()));
}
bool profileMatchesBundleId(std::string applicationIdentifier, std::string bundleId) {
    const auto provisioned = provisionedBundleId(applicationIdentifier);
    return (((provisioned == bundleId) || (provisioned == std::string("*"))) || (doof::string_endsWith(provisioned, std::string(".*")) && doof::string_startsWith(bundleId, doof::string_substring(provisioned, 0, (static_cast<int32_t>(provisioned.size()) - 1)))));
}
int32_t provisioningSpecificity(std::string applicationIdentifier, std::string bundleId) {
    const auto provisioned = provisionedBundleId(applicationIdentifier);
    if (provisioned == bundleId) {
        return 2;
    }
    if ((provisioned == std::string("*")) || doof::string_endsWith(provisioned, std::string(".*"))) {
        return 1;
    }
    return 0;
}
bool betterProvisioningProfile(std::shared_ptr<IOSProvisioningProfile> candidate, std::shared_ptr<IOSProvisioningProfile> current, std::string bundleId, int64_t nowEpochMs) {
    const auto candidateSpecificity = provisioningSpecificity(candidate->applicationIdentifier, bundleId);
    const auto currentSpecificity = provisioningSpecificity(current->applicationIdentifier, bundleId);
    if (candidateSpecificity != currentSpecificity) {
        return (candidateSpecificity > currentSpecificity);
    }
    const auto candidateActive = (candidate->expirationEpochMs > nowEpochMs);
    const auto currentActive = (current->expirationEpochMs > nowEpochMs);
    if (candidateActive != currentActive) {
        return candidateActive;
    }
    return (candidate->expirationEpochMs > current->expirationEpochMs);
}
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> selectProvisioningProfile(std::string bundleId, std::shared_ptr<std::vector<std::shared_ptr<IOSProvisioningProfile>>> profiles, int64_t nowEpochMs) {
    std::shared_ptr<IOSProvisioningProfile> selected = nullptr;
    const auto& _iterable_5 = profiles;
    for (const auto& profile : *_iterable_5) {
        if (!profileMatchesBundleId(profile->applicationIdentifier, bundleId)) {
            continue;
        }
        if (doof::is_null(selected) || betterProvisioningProfile(profile, doof::unwrap_optional(selected), bundleId, nowEpochMs)) {
            (selected = profile);
        }
    }
    if (doof::is_null(selected)) {
        return doof::Failure<std::string>{ ((std::string("Could not auto-detect a provisioning profile for bundle id \"") + bundleId) + std::string("\". Pass --ios-provisioning-profile.")) };
    }
    return doof::Success<std::shared_ptr<IOSProvisioningProfile>>{ doof::unwrap_optional(selected) };
}
doof::Result<std::string, std::string> selectSigningIdentity(std::shared_ptr<IOSProvisioningProfile> profile, std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities) {
    if (static_cast<int32_t>((profile->certFingerprints)->size()) == 0) {
        return doof::Failure<std::string>{ ((std::string("Provisioning profile \"") + profile->profilePath) + std::string("\" does not include DeveloperCertificates. Pass --ios-sign-identity.")) };
    }
    const auto& _iterable_6 = identities;
    for (const auto& identity : *_iterable_6) {
        const auto& _iterable_7 = profile->certFingerprints;
        for (const auto& fingerprint : *_iterable_7) {
            if (identity->fingerprint == fingerprint) {
                return doof::Success<std::string>{ identity->name };
            }
        }
    }
    return doof::Failure<std::string>{ ((std::string("Could not auto-detect a signing identity for profile \"") + profile->profilePath) + std::string("\". Pass --ios-sign-identity.")) };
}
doof::Result<std::string, std::string> resolveIOSAdHocSigningIdentity(std::shared_ptr<IOSProvisioningProfile> profile, std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities, std::string configuredIdentity) {
    if (configuredIdentity != std::string("")) {
        return doof::Success<std::string>{ configuredIdentity };
    }
    std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> matching = std::make_shared<std::vector<std::shared_ptr<IOSCodesignIdentity>>>(std::vector<std::shared_ptr<IOSCodesignIdentity>>{});
    const auto& _iterable_8 = identities;
    for (const auto& identity : *_iterable_8) {
        const auto distribution = (doof::string_startsWith(identity->name, std::string("Apple Distribution:")) || doof::string_startsWith(identity->name, std::string("iPhone Distribution:")));
        if (distribution && doof::array_contains(profile->certFingerprints, identity->fingerprint, "", 0)) {
            matching->push_back(identity);
        }
    }
    if (static_cast<int32_t>((matching)->size()) == 0) {
        return doof::Failure<std::string>{ ((std::string("No installed Apple Distribution identity is included in provisioning profile \"") + profile->profilePath) + std::string("\"")) };
    }
    if (static_cast<int32_t>((matching)->size()) > 1) {
        auto names = std::string("");
        for (int32_t index = 0; index < static_cast<int32_t>((matching)->size()); ++index) {
            if (index > 0) {
                (names += std::string(", "));
            }
            (names += (*matching)[index]->name);
        }
        return doof::Failure<std::string>{ ((((std::string("Multiple Apple Distribution identities are included in provisioning profile \"") + profile->profilePath) + std::string("\" (")) + names) + std::string("). Pass --ios-sign-identity.")) };
    }
    return doof::Success<std::string>{ (*matching)[0]->name };
}
doof::Result<void, std::string> validateIOSAdHocSigning(std::shared_ptr<IOSProvisioningProfile> profile, std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities, std::string identityName, std::string bundleId, int64_t nowEpochMs) {
    if (!profileMatchesBundleId(profile->applicationIdentifier, bundleId)) {
        return doof::Failure<std::string>{ ((((std::string("Provisioning profile application-identifier \"") + profile->applicationIdentifier) + std::string("\" does not match bundle id \"")) + bundleId) + std::string("\"")) };
    }
    if (profile->expirationEpochMs <= nowEpochMs) {
        return doof::Failure<std::string>{ (std::string("Provisioning profile is expired: ") + profile->profilePath) };
    }
    if (profile->provisionsAllDevices) {
        return doof::Failure<std::string>{ std::string("Enterprise provisioning profiles cannot be used for Ad Hoc packaging") };
    }
    if (profile->getTaskAllow) {
        return doof::Failure<std::string>{ std::string("Development provisioning profiles cannot be used for Ad Hoc packaging") };
    }
    if (profile->provisionedDeviceCount == 0) {
        return doof::Failure<std::string>{ (std::string("Ad Hoc provisioning profile contains no registered devices: ") + profile->profilePath) };
    }
    if (!doof::string_startsWith(identityName, std::string("Apple Distribution:")) && !doof::string_startsWith(identityName, std::string("iPhone Distribution:"))) {
        return doof::Failure<std::string>{ ((std::string("iOS Ad Hoc packaging requires an Apple Distribution signing identity, got \"") + identityName) + std::string("\"")) };
    }
    std::shared_ptr<IOSCodesignIdentity> selected = nullptr;
    const auto& _iterable_9 = identities;
    for (const auto& identity : *_iterable_9) {
        if (identity->name == identityName) {
            (selected = identity);
            break;
        }
    }
    if (doof::is_null(selected)) {
        return doof::Failure<std::string>{ ((std::string("Configured iOS signing identity is not currently valid: \"") + identityName) + std::string("\"")) };
    }
    if (!doof::array_contains(profile->certFingerprints, selected->fingerprint, "", 0)) {
        return doof::Failure<std::string>{ ((((std::string("Configured iOS signing identity \"") + identityName) + std::string("\" is not included in provisioning profile \"")) + profile->profilePath) + std::string("\"")) };
    }
    return doof::Success<void>{};
}
std::string hostPlatform() {
    const auto value = ::std_::os::index::platform();
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}
std::string devicePath(std::string directory, std::string name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
void ensureDirectory(std::string path) {
    if ((path == std::string("")) || ::std_::fs::index::exists(path)) {
        return;
    }
    const auto parent = ::std_::path::index::dirname(path);
    if (parent != path) {
        ensureDirectory(parent);
    }
    [&]() -> void { auto _try_value = ::std_::fs::index::mkdir(path); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
}
void removeTree(std::string path) {
    if (!::std_::fs::index::exists(path)) {
        return;
    }
    if (::std_::fs::index::isDirectory(path)) {
        const auto& _iterable_10 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::std_::fs::index::readDir(path); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_10) {
            removeTree(devicePath(path, entry->name));
        }
    }
    [&]() -> void { auto _try_value = ::std_::fs::index::remove(path); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
}
std::shared_ptr<IOSDeviceCommandResult> runDeviceCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments) {
    auto _binding_value_11 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, MAX_IOS_DEVICE_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_11)) {
        const auto error = doof::failure_error(_binding_value_11);
        return std::make_shared<IOSDeviceCommandResult>(-1, std::string(""), error);
    }
    const auto executed = doof::success_value(_binding_value_11);
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(executed->stdout, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((executed->stdout)->size()))));
    return std::make_shared<IOSDeviceCommandResult>(executed->exitCode, output, std::string(""));
}
doof::Result<std::string, std::string> deviceCommandText(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string description) {
    const auto result = runDeviceCommand(command, arguments);
    const auto output = ((result->error != std::string("")) ? result->error : result->output);
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ ((description + std::string(" failed")) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
    return doof::Success<std::string>{ output };
}
doof::Result<void, std::string> decodeProvisioningProfile(std::string profilePath, std::string decodedPath) {
    const auto securityResult = runDeviceCommand(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("cms"), std::string("-D"), std::string("-i"), profilePath}));
    if (securityResult->exitCode == 0) {
        [&]() -> void { auto _try_value = ::std_::fs::index::writeText(decodedPath, securityResult->output); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
        return doof::Success<void>{};
    }
    const auto opensslResult = runDeviceCommand(std::string("openssl"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("smime"), std::string("-inform"), std::string("der"), std::string("-verify"), std::string("-noverify"), std::string("-in"), profilePath, std::string("-out"), decodedPath}));
    if (opensslResult->exitCode != 0) {
        const auto output = ((securityResult->error != std::string("")) ? securityResult->error : securityResult->output);
        const auto fallbackOutput = ((opensslResult->error != std::string("")) ? opensslResult->error : opensslResult->output);
        return doof::Failure<std::string>{ (std::string("decoding provisioning profile failed") + ((fallbackOutput != std::string("")) ? (std::string(":\n") + fallbackOutput) : ((output != std::string("")) ? (std::string(":\n") + output) : std::string("")))) };
    }
    return doof::Success<void>{};
}
std::string resolveUserPath(std::string path) {
    if (path == std::string("~")) {
        return [&]() -> std::string { auto _try_value = ::std_::path::index::homeDirectory(); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    }
    if (doof::string_startsWith(path, std::string("~/"))) {
        return devicePath([&]() -> std::string { auto _try_value = ::std_::path::index::homeDirectory(); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }(), doof::string_substring(path, 2, static_cast<int32_t>(path.size())));
    }
    return [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
}
void appendUnique(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    if (!doof::array_contains(values, value, "", 0)) {
        values->push_back(value);
    }
}
doof::Result<std::string, std::string> certificateFingerprint(std::string certificateData) {
    auto _binding_value_12 = ::std_::crypto::index::decodeBase64(certificateData);
    if (doof::is_failure(_binding_value_12)) {
        const auto error = doof::failure_error(_binding_value_12);
        return doof::Failure<std::string>{ error };
    }
    const auto decoded = doof::success_value(_binding_value_12);
    const auto fingerprint = doof::string_toUpperCase(::std_::crypto::index::sha1Hex(decoded));
    if (!isHexFingerprint(fingerprint)) {
        return doof::Failure<std::string>{ std::string("Could not parse provisioning profile certificate fingerprint") };
    }
    return doof::Success<std::string>{ fingerprint };
}
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> parseProvisioningProfile(std::string profilePath, std::string workDirectory) {
    ensureDirectory(workDirectory);
    const auto decodedPath = devicePath(workDirectory, std::string("profile.plist"));
    auto _try_value_13 = decodeProvisioningProfile(profilePath, decodedPath);
    if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::failure_error(_try_value_13)};
    auto _try_value_14 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements.application-identifier"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile application identifier"));
    if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::failure_error(_try_value_14)};
    const auto applicationIdentifier = doof::success_value(_try_value_14);
    if (applicationIdentifier == std::string("")) {
        return doof::Failure<std::string>{ (std::string("Provisioning profile missing Entitlements.application-identifier: ") + profilePath) };
    }
    const auto expirationResult = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("ExpirationDate"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile expiration date"));
    auto expirationText = std::string("");
    {
        auto _case_subject = expirationResult;
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
            (expirationText = success.value);
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
    auto expirationEpochMs = 0LL;
    if (expirationText != std::string("")) {
        {
            auto _case_subject = ::std_::time::temporal::Instant::parse(expirationText);
            if (std::holds_alternative<doof::Success<std::shared_ptr<::std_::time::temporal::Instant>>>(_case_subject)) {
                const auto& success = std::get<doof::Success<std::shared_ptr<::std_::time::temporal::Instant>>>(_case_subject);
                (expirationEpochMs = success.value->toEpochMillis());
        }
        else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        }
        }
    }
    auto provisionedDeviceCount = 0;
    {
        auto _case_subject = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("ProvisionedDevices"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile device count"));
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
            {
                auto _case_subject = doof::parse_int(success.value);
                if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
                    const auto& parsedCount = std::get<doof::Success<int32_t>>(_case_subject);
                    (provisionedDeviceCount = parsedCount.value);
            }
            else if (std::holds_alternative<doof::Failure<doof::ParseError>>(_case_subject)) {
            }
            }
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
    auto provisionsAllDevices = false;
    {
        auto _case_subject = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("ProvisionsAllDevices"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading enterprise provisioning flag"));
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
            (provisionsAllDevices = (success.value == std::string("true")));
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
    auto getTaskAllow = false;
    {
        auto _case_subject = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements.get-task-allow"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading development provisioning flag"));
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
            (getTaskAllow = (success.value == std::string("true")));
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
    std::shared_ptr<std::vector<std::string>> certFingerprints = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto certificateCount = 0;
    {
        auto _case_subject = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("DeveloperCertificates"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile certificate count"));
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
            {
                auto _case_subject = doof::parse_int(success.value);
                if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
                    const auto& parsedCount = std::get<doof::Success<int32_t>>(_case_subject);
                    (certificateCount = parsedCount.value);
            }
            else if (std::holds_alternative<doof::Failure<doof::ParseError>>(_case_subject)) {
            }
            }
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
    for (int32_t index = 0; index < certificateCount; ++index) {
        auto _binding_value_15 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), (std::string("DeveloperCertificates.") + doof::to_string(index)), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile certificate"));
        if (doof::is_failure(_binding_value_15)) {
            const auto& encoded = _binding_value_15;
            continue;
        }
        const auto encoded = doof::success_value(_binding_value_15);
        if (encoded == std::string("")) {
            continue;
        }
        auto _binding_value_16 = certificateFingerprint(encoded);
        if (doof::is_failure(_binding_value_16)) {
            const auto& fingerprint = _binding_value_16;
            continue;
        }
        const auto fingerprint = doof::success_value(_binding_value_16);
        appendUnique(certFingerprints, fingerprint);
    }
    return doof::Success<std::shared_ptr<IOSProvisioningProfile>>{ std::make_shared<IOSProvisioningProfile>(profilePath, applicationIdentifier, certFingerprints, expirationEpochMs, provisionedDeviceCount, provisionsAllDevices, getTaskAllow) };
}
std::shared_ptr<std::vector<std::string>> collectProvisioningProfilePaths(std::shared_ptr<std::vector<std::string>> profileDirectories) {
    const auto directories = ((static_cast<int32_t>((profileDirectories)->size()) > 0) ? profileDirectories : std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("~/Library/Developer/Xcode/UserData/Provisioning Profiles"), std::string("~/Library/MobileDevice/Provisioning Profiles")}));
    std::shared_ptr<std::vector<std::string>> paths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_17 = directories;
    for (const auto& directory : *_iterable_17) {
        const auto expanded = resolveUserPath(directory);
        if (!::std_::fs::index::isDirectory(expanded)) {
            continue;
        }
        const auto& _iterable_18 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::std_::fs::index::readDir(expanded); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_18) {
            if (doof::string_endsWith(entry->name, std::string(".mobileprovision"))) {
                appendUnique(paths, devicePath(expanded, entry->name));
            }
        }
    }
    return paths;
}
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> autoResolveProvisioningProfile(std::string bundleId, std::string workDirectory, std::shared_ptr<std::vector<std::string>> profileDirectories) {
    std::shared_ptr<std::vector<std::shared_ptr<IOSProvisioningProfile>>> profiles = std::make_shared<std::vector<std::shared_ptr<IOSProvisioningProfile>>>(std::vector<std::shared_ptr<IOSProvisioningProfile>>{});
    const auto& _iterable_19 = collectProvisioningProfilePaths(profileDirectories);
    for (const auto& profilePath : *_iterable_19) {
        auto _binding_value_20 = parseProvisioningProfile(profilePath, workDirectory);
        if (doof::is_failure(_binding_value_20)) {
            const auto& profile = _binding_value_20;
            continue;
        }
        const auto profile = doof::success_value(_binding_value_20);
        profiles->push_back(profile);
    }
    return selectProvisioningProfile(bundleId, profiles, ::std_::time::temporal::Instant::now()->toEpochMillis());
}
doof::Result<std::shared_ptr<IOSDeviceSigningOptions>, std::string> resolveIOSDeviceSigningOptions(std::string bundleId, std::string signIdentityOverride, std::string provisioningProfileOverride, std::string workDirectory, std::shared_ptr<std::vector<std::string>> profileDirectories) {
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS device signing is only supported on macOS") };
    }
    const auto profilePath = ((provisioningProfileOverride == std::string("")) ? std::string("") : resolveUserPath(provisioningProfileOverride));
    if ((profilePath != std::string("")) && (signIdentityOverride != std::string(""))) {
        return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(signIdentityOverride, profilePath) };
    }
    const auto profile = ((profilePath == std::string("")) ? autoResolveProvisioningProfile(bundleId, workDirectory, profileDirectories) : parseProvisioningProfile(profilePath, workDirectory));
    auto _binding_value_21 = profile;
    if (doof::is_failure(_binding_value_21)) {
        const auto error = doof::failure_error(_binding_value_21);
        return doof::Failure<std::string>{ error };
    }
    const auto selectedProfile = doof::success_value(_binding_value_21);
    if (signIdentityOverride != std::string("")) {
        return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(signIdentityOverride, selectedProfile->profilePath) };
    }
    auto _try_value_22 = deviceCommandText(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("find-identity"), std::string("-v"), std::string("-p"), std::string("codesigning")}), std::string("listing code-signing identities"));
    if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::failure_error(_try_value_22)};
    const auto identitiesOutput = doof::success_value(_try_value_22);
    auto _try_value_23 = selectSigningIdentity(selectedProfile, parseCodesignIdentities(identitiesOutput));
    if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::failure_error(_try_value_23)};
    const auto identity = doof::success_value(_try_value_23);
    return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(identity, selectedProfile->profilePath) };
}
doof::Result<std::string, std::string> resolveIOSDeviceIdentifier(std::string overrideIdentifier, std::string workDirectory) {
    if (overrideIdentifier != std::string("")) {
        return doof::Success<std::string>{ overrideIdentifier };
    }
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS device discovery is only supported on macOS") };
    }
    ensureDirectory(workDirectory);
    const auto devicesPath = devicePath(workDirectory, std::string("devices.json"));
    if (::std_::fs::index::exists(devicesPath)) {
        [&]() -> void { auto _try_value = ::std_::fs::index::remove(devicesPath); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    }
    auto _binding_value_24 = deviceCommandText(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("list"), std::string("devices"), std::string("--json-output"), devicesPath}), std::string("listing connected iOS devices"));
    if (doof::is_failure(_binding_value_24)) {
        const auto error = doof::failure_error(_binding_value_24);
        return doof::Failure<std::string>{ error };
    }
    const auto result = doof::success_value(_binding_value_24);
    auto _binding_value_25 = ::std_::fs::index::readText(devicesPath);
    if (doof::is_failure(_binding_value_25)) {
        const auto& rawJson = _binding_value_25;
        return doof::Failure<std::string>{ std::string("Could not read devicectl device output") };
    }
    const auto rawJson = doof::success_value(_binding_value_25);
    auto _binding_value_26 = parseConnectedIOSDevices(rawJson);
    if (doof::is_failure(_binding_value_26)) {
        const auto error = doof::failure_error(_binding_value_26);
        return doof::Failure<std::string>{ error };
    }
    const auto devices = doof::success_value(_binding_value_26);
    if (::std_::fs::index::exists(devicesPath)) {
        [&]() -> void { auto _try_value = ::std_::fs::index::remove(devicesPath); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    }
    return selectIOSDeviceIdentifier(std::string(""), devices);
}
void collectNestedIOSCode(std::string path, std::shared_ptr<std::vector<std::string>> results) {
    if (!::std_::fs::index::exists(path)) {
        return;
    }
    if (::std_::fs::index::isDirectory(path)) {
        if (doof::string_endsWith(path, std::string(".framework")) || doof::string_endsWith(path, std::string(".appex"))) {
            results->push_back(path);
            return;
        }
        const auto& _iterable_27 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::std_::fs::index::readDir(path); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_27) {
            collectNestedIOSCode(devicePath(path, entry->name), results);
        }
        return;
    }
    if (doof::string_endsWith(path, std::string(".dylib")) || doof::string_endsWith(path, std::string(".so"))) {
        results->push_back(path);
    }
}
doof::Result<void, std::string> signIOSDeviceApp(std::string appPath, std::string bundleId, std::shared_ptr<IOSDeviceSigningOptions> options, std::string workDirectory) {
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS device signing is only supported on macOS") };
    }
    if (!::std_::fs::index::exists(options->provisioningProfilePath)) {
        return doof::Failure<std::string>{ (std::string("Provisioning profile not found: ") + options->provisioningProfilePath) };
    }
    removeTree(workDirectory);
    ensureDirectory(workDirectory);
    const auto decodedPath = devicePath(workDirectory, std::string("profile.plist"));
    const auto entitlementsPath = devicePath(workDirectory, std::string("entitlements.plist"));
    auto _try_value_28 = decodeProvisioningProfile(options->provisioningProfilePath, decodedPath);
    if (doof::is_failure(_try_value_28)) return doof::Failure<std::string>{doof::failure_error(_try_value_28)};
    auto _try_value_29 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements.application-identifier"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile application identifier"));
    if (doof::is_failure(_try_value_29)) return doof::Failure<std::string>{doof::failure_error(_try_value_29)};
    const auto applicationIdentifier = doof::success_value(_try_value_29);
    if (!profileMatchesBundleId(applicationIdentifier, bundleId)) {
        removeTree(workDirectory);
        return doof::Failure<std::string>{ ((((std::string("Provisioning profile application-identifier \"") + applicationIdentifier) + std::string("\" does not match bundle id \"")) + bundleId) + std::string("\"")) };
    }
    auto _try_value_30 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements"), std::string("xml1"), std::string("-o"), entitlementsPath, decodedPath}), std::string("extracting iOS signing entitlements"));
    if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::failure_error(_try_value_30)};
    const auto ignored = doof::success_value(_try_value_30);
    [&]() -> void { auto _try_value = ::std_::fs::index::writeBlob(devicePath(appPath, std::string("embedded.mobileprovision")), [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::std_::fs::index::readBlob(options->provisioningProfilePath); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }()); if (doof::is_failure(_try_value)) doof::panic("try! failed");  }();
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    collectNestedIOSCode(devicePath(appPath, std::string("Frameworks")), nested);
    collectNestedIOSCode(devicePath(appPath, std::string("PlugIns")), nested);
    const auto& _iterable_31 = nested;
    for (const auto& path : *_iterable_31) {
        auto _try_value_32 = deviceCommandText(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(path, options->signIdentity, std::string("")), std::string("signing nested iOS code"));
        if (doof::is_failure(_try_value_32)) return doof::Failure<std::string>{doof::failure_error(_try_value_32)};
        const auto nestedIgnored = doof::success_value(_try_value_32);
    }
    auto _try_value_33 = deviceCommandText(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(appPath, options->signIdentity, entitlementsPath), std::string("signing the iOS app"));
    if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::failure_error(_try_value_33)};
    const auto appIgnored = doof::success_value(_try_value_33);
    removeTree(workDirectory);
    return doof::Success<void>{};
}
}
