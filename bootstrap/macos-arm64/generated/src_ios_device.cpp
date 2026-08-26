#include "src_ios_device.hpp"

namespace app_src_ios_device_ {
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::parse::index;
using namespace ::std_::path::index;
using namespace ::app_src_ios_app_;
using namespace ::std_::blob::index;
int64_t MAX_IOS_DEVICE_COMMAND_OUTPUT_BYTES = 262144LL;





#line 50 "/src/ios-device.do"
std::variant<std::monostate, doof::JsonValue> jsonObjectField(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
#line 51 "/src/ios-device.do"
    if (![&]() -> bool { auto _map_has_1 = object; return _map_has_1->find(name) != _map_has_1->end(); }()) {
#line 51 "/src/ios-device.do"
        return std::monostate{};
    }
#line 52 "/src/ios-device.do"
    auto _binding_value_2 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_2)) {
        const auto& value = _binding_value_2;
#line 52 "/src/ios-device.do"
        return std::monostate{};
    }
    const auto value = doof::success_value(_binding_value_2);
#line 53 "/src/ios-device.do"
    return value;
}
#line 56 "/src/ios-device.do"
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> jsonObjectValue(const std::variant<std::monostate, doof::JsonValue>& value) {
#line 57 "/src/ios-device.do"
    if (doof::is_null(value)) {
#line 57 "/src/ios-device.do"
        return nullptr;
    }
#line 58 "/src/ios-device.do"
    {
        auto _case_subject = std::get<doof::JsonValue>(value);
        if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
#line 59 "/src/ios-device.do"
            return object;
    }
    else {
#line 60 "/src/ios-device.do"
            return nullptr;
    }
    }
    doof::unreachable();
}
#line 64 "/src/ios-device.do"
std::shared_ptr<std::vector<doof::JsonValue>> jsonArrayValue(const std::variant<std::monostate, doof::JsonValue>& value) {
#line 65 "/src/ios-device.do"
    if (doof::is_null(value)) {
#line 65 "/src/ios-device.do"
        return std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    }
#line 66 "/src/ios-device.do"
    {
        auto _case_subject = std::get<doof::JsonValue>(value);
        if (doof::json_is_array(_case_subject)) {
            const auto array = std::get<doof::JsonArray>(doof::json_storage(_case_subject));
#line 67 "/src/ios-device.do"
            return array;
    }
    else {
#line 68 "/src/ios-device.do"
            return std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    }
    }
    doof::unreachable();
}
#line 72 "/src/ios-device.do"
std::string jsonStringValue(const std::variant<std::monostate, doof::JsonValue>& value) {
#line 73 "/src/ios-device.do"
    if (doof::is_null(value)) {
#line 73 "/src/ios-device.do"
        return std::string("");
    }
#line 74 "/src/ios-device.do"
    {
        auto _case_subject = std::get<doof::JsonValue>(value);
        if (doof::json_is_string(_case_subject)) {
            const auto text = doof::json_as_string(_case_subject);
#line 75 "/src/ios-device.do"
            return text;
    }
    else {
#line 76 "/src/ios-device.do"
            return std::string("");
    }
    }
    doof::unreachable();
}
#line 81 "/src/ios-device.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>, std::string> parseConnectedIOSDevices(const std::string& rawJson) {
#line 82 "/src/ios-device.do"
    auto _binding_value_3 = ::doof_json::parse(rawJson);
    if (doof::is_failure(_binding_value_3)) {
        const auto error = doof::failure_error(_binding_value_3);
#line 82 "/src/ios-device.do"
        return doof::Failure<std::string>{ error };
    }
    const auto parsed = doof::success_value(_binding_value_3);
#line 83 "/src/ios-device.do"
    const auto root = jsonObjectValue(parsed);
#line 84 "/src/ios-device.do"
    if (doof::is_null(root)) {
#line 84 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("Invalid devicectl device JSON: expected an object") };
    }
#line 85 "/src/ios-device.do"
    const auto result = jsonObjectValue(jsonObjectField(doof::unwrap_optional(root), std::string("result")));
#line 86 "/src/ios-device.do"
    if (doof::is_null(result)) {
#line 86 "/src/ios-device.do"
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>>{ std::make_shared<std::vector<std::shared_ptr<IOSDevice>>>(std::vector<std::shared_ptr<IOSDevice>>{}) };
    }
#line 87 "/src/ios-device.do"
    const auto values = jsonArrayValue(jsonObjectField(doof::unwrap_optional(result), std::string("devices")));
#line 88 "/src/ios-device.do"
    std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>> devices = std::make_shared<std::vector<std::shared_ptr<IOSDevice>>>(std::vector<std::shared_ptr<IOSDevice>>{});
#line 89 "/src/ios-device.do"
    const auto& _iterable_5 = values;
    for (const auto& value : *_iterable_5) {
#line 90 "/src/ios-device.do"
        const auto device = jsonObjectValue(value);
#line 91 "/src/ios-device.do"
        if (doof::is_null(device)) {
#line 91 "/src/ios-device.do"
            continue;
        }
#line 92 "/src/ios-device.do"
        const auto identifier = jsonStringValue(jsonObjectField(doof::unwrap_optional(device), std::string("identifier")));
#line 93 "/src/ios-device.do"
        const auto deviceProperties = jsonObjectValue(jsonObjectField(doof::unwrap_optional(device), std::string("deviceProperties")));
#line 94 "/src/ios-device.do"
        const auto hardwareProperties = jsonObjectValue(jsonObjectField(doof::unwrap_optional(device), std::string("hardwareProperties")));
#line 95 "/src/ios-device.do"
        const auto connectionProperties = jsonObjectValue(jsonObjectField(doof::unwrap_optional(device), std::string("connectionProperties")));
#line 96 "/src/ios-device.do"
        const auto name = (doof::is_null(deviceProperties) ? std::string("") : jsonStringValue(jsonObjectField(doof::unwrap_optional(deviceProperties), std::string("name"))));
#line 97 "/src/ios-device.do"
        const auto platformName = (doof::is_null(hardwareProperties) ? std::string("") : jsonStringValue(jsonObjectField(doof::unwrap_optional(hardwareProperties), std::string("platform"))));
#line 98 "/src/ios-device.do"
        const auto reality = (doof::is_null(hardwareProperties) ? std::string("") : jsonStringValue(jsonObjectField(doof::unwrap_optional(hardwareProperties), std::string("reality"))));
#line 99 "/src/ios-device.do"
        const auto tunnelState = (doof::is_null(connectionProperties) ? std::string("") : jsonStringValue(jsonObjectField(doof::unwrap_optional(connectionProperties), std::string("tunnelState"))));
#line 100 "/src/ios-device.do"
        if (((identifier == std::string("")) || (platformName != std::string("iOS"))) || (tunnelState != std::string("connected"))) {
#line 100 "/src/ios-device.do"
            continue;
        }
#line 101 "/src/ios-device.do"
        if ((reality != std::string("")) && (reality != std::string("physical"))) {
#line 101 "/src/ios-device.do"
            continue;
        }
#line 102 "/src/ios-device.do"
        devices->push_back(std::make_shared<IOSDevice>(identifier, ((name == std::string("")) ? identifier : name)));
    }
#line 104 "/src/ios-device.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>>{ devices };
}
#line 108 "/src/ios-device.do"
doof::Result<std::string, std::string> selectIOSDeviceIdentifier(const std::string& overrideIdentifier, const std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>& devices) {
#line 109 "/src/ios-device.do"
    if (overrideIdentifier != std::string("")) {
#line 109 "/src/ios-device.do"
        return doof::Success<std::string>{ overrideIdentifier };
    }
#line 110 "/src/ios-device.do"
    if (static_cast<int32_t>((devices)->size()) == 0) {
#line 111 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("Could not auto-detect a connected iOS device. Connect a device or pass --ios-device.") };
    }
#line 113 "/src/ios-device.do"
    if (static_cast<int32_t>((devices)->size()) > 1) {
#line 114 "/src/ios-device.do"
        auto choices = std::string("");
#line 115 "/src/ios-device.do"
        for (int32_t index = 0; index < static_cast<int32_t>((devices)->size()); ++index) {
#line 116 "/src/ios-device.do"
            if (index > 0) {
#line 116 "/src/ios-device.do"
                (choices += std::string(", "));
            }
#line 117 "/src/ios-device.do"
            (choices += (((doof::array_at(devices, index, "src/ios-device", 117)->name + std::string(" (")) + doof::array_at(devices, index, "src/ios-device", 117)->identifier) + std::string(")")));
        }
#line 119 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((std::string("Multiple connected iOS devices found (") + choices) + std::string("). Pass --ios-device to select one.")) };
    }
#line 121 "/src/ios-device.do"
    return doof::Success<std::string>{ doof::array_at(devices, 0, "src/ios-device", 121)->identifier };
}
#line 124 "/src/ios-device.do"
bool isHexFingerprint(const std::string& value) {
#line 125 "/src/ios-device.do"
    if (static_cast<int32_t>(value.size()) != 40) {
#line 125 "/src/ios-device.do"
        return false;
    }
#line 126 "/src/ios-device.do"
    const auto hex = std::string("0123456789ABCDEF");
#line 127 "/src/ios-device.do"
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
#line 128 "/src/ios-device.do"
        if (!doof::string_contains(hex, doof::string_toUpperCase(doof::string_substring(value, index, (index + 1))))) {
#line 128 "/src/ios-device.do"
            return false;
        }
    }
#line 130 "/src/ios-device.do"
    return true;
}
#line 134 "/src/ios-device.do"
std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> parseCodesignIdentities(const std::string& output) {
#line 135 "/src/ios-device.do"
    std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities = std::make_shared<std::vector<std::shared_ptr<IOSCodesignIdentity>>>(std::vector<std::shared_ptr<IOSCodesignIdentity>>{});
#line 136 "/src/ios-device.do"
    const auto& _iterable_9 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_9) {
#line 137 "/src/ios-device.do"
        const auto closeParen = doof::string_indexOf(line, std::string(")"));
#line 138 "/src/ios-device.do"
        if (closeParen < 0) {
#line 138 "/src/ios-device.do"
            continue;
        }
#line 139 "/src/ios-device.do"
        const auto remainder = doof::string_trim(doof::string_substring(line, (closeParen + 1), static_cast<int32_t>(line.size())));
#line 140 "/src/ios-device.do"
        const auto separator = doof::string_indexOf(remainder, std::string(" "));
#line 141 "/src/ios-device.do"
        if (separator < 0) {
#line 141 "/src/ios-device.do"
            continue;
        }
#line 142 "/src/ios-device.do"
        const auto fingerprint = doof::string_toUpperCase(doof::string_substring(remainder, 0, separator));
#line 143 "/src/ios-device.do"
        const auto quotedName = doof::string_trim(doof::string_substring(remainder, (separator + 1), static_cast<int32_t>(remainder.size())));
#line 144 "/src/ios-device.do"
        if (((!isHexFingerprint(fingerprint) || (static_cast<int32_t>(quotedName.size()) < 2)) || !doof::string_startsWith(quotedName, std::string("\""))) || !doof::string_endsWith(quotedName, std::string("\""))) {
#line 144 "/src/ios-device.do"
            continue;
        }
#line 145 "/src/ios-device.do"
        identities->push_back(std::make_shared<IOSCodesignIdentity>(fingerprint, doof::string_substring(quotedName, 1, (static_cast<int32_t>(quotedName.size()) - 1))));
    }
#line 150 "/src/ios-device.do"
    return identities;
}
#line 153 "/src/ios-device.do"
std::string provisionedBundleId(const std::string& applicationIdentifier) {
#line 154 "/src/ios-device.do"
    const auto separator = doof::string_indexOf(applicationIdentifier, std::string("."));
#line 155 "/src/ios-device.do"
    if (separator < 0) {
#line 155 "/src/ios-device.do"
        return std::string("");
    }
#line 156 "/src/ios-device.do"
    return doof::string_substring(applicationIdentifier, (separator + 1), static_cast<int32_t>(applicationIdentifier.size()));
}
#line 159 "/src/ios-device.do"
bool profileMatchesBundleId(const std::string& applicationIdentifier, const std::string& bundleId) {
#line 160 "/src/ios-device.do"
    const auto provisioned = provisionedBundleId(applicationIdentifier);
#line 161 "/src/ios-device.do"
    return (((provisioned == bundleId) || (provisioned == std::string("*"))) || (doof::string_endsWith(provisioned, std::string(".*")) && doof::string_startsWith(bundleId, doof::string_substring(provisioned, 0, (static_cast<int32_t>(provisioned.size()) - 1)))));
}
#line 165 "/src/ios-device.do"
int32_t provisioningSpecificity(const std::string& applicationIdentifier, const std::string& bundleId) {
#line 166 "/src/ios-device.do"
    const auto provisioned = provisionedBundleId(applicationIdentifier);
#line 167 "/src/ios-device.do"
    if (provisioned == bundleId) {
#line 167 "/src/ios-device.do"
        return 2;
    }
#line 168 "/src/ios-device.do"
    if ((provisioned == std::string("*")) || doof::string_endsWith(provisioned, std::string(".*"))) {
#line 168 "/src/ios-device.do"
        return 1;
    }
#line 169 "/src/ios-device.do"
    return 0;
}
#line 172 "/src/ios-device.do"
bool betterProvisioningProfile(const std::shared_ptr<IOSProvisioningProfile>& candidate, const std::shared_ptr<IOSProvisioningProfile>& current, const std::string& bundleId, int64_t nowEpochMs) {
#line 178 "/src/ios-device.do"
    const auto candidateSpecificity = provisioningSpecificity(candidate->applicationIdentifier, bundleId);
#line 179 "/src/ios-device.do"
    const auto currentSpecificity = provisioningSpecificity(current->applicationIdentifier, bundleId);
#line 180 "/src/ios-device.do"
    if (candidateSpecificity != currentSpecificity) {
#line 180 "/src/ios-device.do"
        return (candidateSpecificity > currentSpecificity);
    }
#line 181 "/src/ios-device.do"
    const auto candidateActive = (candidate->expirationEpochMs > nowEpochMs);
#line 182 "/src/ios-device.do"
    const auto currentActive = (current->expirationEpochMs > nowEpochMs);
#line 183 "/src/ios-device.do"
    if (candidateActive != currentActive) {
#line 183 "/src/ios-device.do"
        return candidateActive;
    }
#line 184 "/src/ios-device.do"
    return (candidate->expirationEpochMs > current->expirationEpochMs);
}
#line 188 "/src/ios-device.do"
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> selectProvisioningProfile(const std::string& bundleId, const std::shared_ptr<std::vector<std::shared_ptr<IOSProvisioningProfile>>>& profiles, int64_t nowEpochMs) {
#line 193 "/src/ios-device.do"
    std::shared_ptr<IOSProvisioningProfile> selected = nullptr;
#line 194 "/src/ios-device.do"
    const auto& _iterable_11 = profiles;
    for (const auto& profile : *_iterable_11) {
#line 195 "/src/ios-device.do"
        if (!profileMatchesBundleId(profile->applicationIdentifier, bundleId)) {
#line 195 "/src/ios-device.do"
            continue;
        }
#line 196 "/src/ios-device.do"
        if (doof::is_null(selected) || betterProvisioningProfile(profile, doof::unwrap_optional(selected), bundleId, nowEpochMs)) {
#line 196 "/src/ios-device.do"
            (selected = profile);
        }
    }
#line 198 "/src/ios-device.do"
    if (doof::is_null(selected)) {
#line 199 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((std::string("Could not auto-detect a provisioning profile for bundle id \"") + bundleId) + std::string("\". Pass --ios-provisioning-profile.")) };
    }
#line 201 "/src/ios-device.do"
    return doof::Success<std::shared_ptr<IOSProvisioningProfile>>{ doof::unwrap_optional(selected) };
}
#line 205 "/src/ios-device.do"
doof::Result<std::string, std::string> selectSigningIdentity(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities) {
#line 209 "/src/ios-device.do"
    if (static_cast<int32_t>((profile->certFingerprints)->size()) == 0) {
#line 210 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((std::string("Provisioning profile \"") + profile->profilePath) + std::string("\" does not include DeveloperCertificates. Pass --ios-sign-identity.")) };
    }
#line 212 "/src/ios-device.do"
    const auto& _iterable_13 = identities;
    for (const auto& identity : *_iterable_13) {
#line 213 "/src/ios-device.do"
        const auto& _iterable_15 = profile->certFingerprints;
        for (const auto& fingerprint : *_iterable_15) {
#line 214 "/src/ios-device.do"
            if (identity->fingerprint == fingerprint) {
#line 214 "/src/ios-device.do"
                return doof::Success<std::string>{ identity->name };
            }
        }
    }
#line 217 "/src/ios-device.do"
    return doof::Failure<std::string>{ ((std::string("Could not auto-detect a signing identity for profile \"") + profile->profilePath) + std::string("\". Pass --ios-sign-identity.")) };
}
#line 221 "/src/ios-device.do"
doof::Result<std::string, std::string> resolveIOSAdHocSigningIdentity(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities, const std::string& configuredIdentity) {
#line 226 "/src/ios-device.do"
    if (configuredIdentity != std::string("")) {
#line 226 "/src/ios-device.do"
        return doof::Success<std::string>{ configuredIdentity };
    }
#line 227 "/src/ios-device.do"
    std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> matching = std::make_shared<std::vector<std::shared_ptr<IOSCodesignIdentity>>>(std::vector<std::shared_ptr<IOSCodesignIdentity>>{});
#line 228 "/src/ios-device.do"
    const auto& _iterable_17 = identities;
    for (const auto& identity : *_iterable_17) {
#line 229 "/src/ios-device.do"
        const auto distribution = (doof::string_startsWith(identity->name, std::string("Apple Distribution:")) || doof::string_startsWith(identity->name, std::string("iPhone Distribution:")));
#line 230 "/src/ios-device.do"
        if (distribution && doof::array_contains(profile->certFingerprints, identity->fingerprint, "", 0)) {
#line 230 "/src/ios-device.do"
            matching->push_back(identity);
        }
    }
#line 232 "/src/ios-device.do"
    if (static_cast<int32_t>((matching)->size()) == 0) {
#line 233 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((std::string("No installed Apple Distribution identity is included in provisioning profile \"") + profile->profilePath) + std::string("\"")) };
    }
#line 238 "/src/ios-device.do"
    if (static_cast<int32_t>((matching)->size()) > 1) {
#line 239 "/src/ios-device.do"
        auto names = std::string("");
#line 240 "/src/ios-device.do"
        for (int32_t index = 0; index < static_cast<int32_t>((matching)->size()); ++index) {
#line 241 "/src/ios-device.do"
            if (index > 0) {
#line 241 "/src/ios-device.do"
                (names += std::string(", "));
            }
#line 242 "/src/ios-device.do"
            (names += doof::array_at(matching, index, "src/ios-device", 242)->name);
        }
#line 244 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((((std::string("Multiple Apple Distribution identities are included in provisioning profile \"") + profile->profilePath) + std::string("\" (")) + names) + std::string("). Pass --ios-sign-identity.")) };
    }
#line 249 "/src/ios-device.do"
    return doof::Success<std::string>{ doof::array_at(matching, 0, "src/ios-device", 249)->name };
}
#line 253 "/src/ios-device.do"
doof::Result<void, std::string> validateIOSAdHocSigning(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities, const std::string& identityName, const std::string& bundleId, int64_t nowEpochMs) {
#line 260 "/src/ios-device.do"
    if (!profileMatchesBundleId(profile->applicationIdentifier, bundleId)) {
#line 261 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((((std::string("Provisioning profile application-identifier \"") + profile->applicationIdentifier) + std::string("\" does not match bundle id \"")) + bundleId) + std::string("\"")) };
    }
#line 266 "/src/ios-device.do"
    if (profile->expirationEpochMs <= nowEpochMs) {
#line 267 "/src/ios-device.do"
        return doof::Failure<std::string>{ (std::string("Provisioning profile is expired: ") + profile->profilePath) };
    }
#line 269 "/src/ios-device.do"
    if (profile->provisionsAllDevices) {
#line 270 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("Enterprise provisioning profiles cannot be used for Ad Hoc packaging") };
    }
#line 272 "/src/ios-device.do"
    if (profile->getTaskAllow) {
#line 273 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("Development provisioning profiles cannot be used for Ad Hoc packaging") };
    }
#line 275 "/src/ios-device.do"
    if (profile->provisionedDeviceCount == 0) {
#line 276 "/src/ios-device.do"
        return doof::Failure<std::string>{ (std::string("Ad Hoc provisioning profile contains no registered devices: ") + profile->profilePath) };
    }
#line 278 "/src/ios-device.do"
    if (!doof::string_startsWith(identityName, std::string("Apple Distribution:")) && !doof::string_startsWith(identityName, std::string("iPhone Distribution:"))) {
#line 279 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((std::string("iOS Ad Hoc packaging requires an Apple Distribution signing identity, got \"") + identityName) + std::string("\"")) };
    }
#line 281 "/src/ios-device.do"
    std::shared_ptr<IOSCodesignIdentity> selected = nullptr;
#line 282 "/src/ios-device.do"
    const auto& _iterable_20 = identities;
    for (const auto& identity : *_iterable_20) {
#line 283 "/src/ios-device.do"
        if (identity->name == identityName) {
#line 283 "/src/ios-device.do"
            (selected = identity);
#line 283 "/src/ios-device.do"
            break;
        }
    }
#line 285 "/src/ios-device.do"
    if (doof::is_null(selected)) {
#line 286 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((std::string("Configured iOS signing identity is not currently valid: \"") + identityName) + std::string("\"")) };
    }
#line 288 "/src/ios-device.do"
    if (!doof::array_contains(profile->certFingerprints, selected->fingerprint, "", 0)) {
#line 289 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((((std::string("Configured iOS signing identity \"") + identityName) + std::string("\" is not included in provisioning profile \"")) + profile->profilePath) + std::string("\"")) };
    }
#line 294 "/src/ios-device.do"
    return doof::Success<void>{};
}
#line 297 "/src/ios-device.do"
std::string hostPlatform() {
#line 298 "/src/ios-device.do"
    const auto value = ::std_::os::index::platform();
#line 299 "/src/ios-device.do"
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}
#line 302 "/src/ios-device.do"
std::string devicePath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
#line 304 "/src/ios-device.do"
void ensureDirectory(const std::string& path) {
#line 305 "/src/ios-device.do"
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
#line 305 "/src/ios-device.do"
        return;
    }
#line 306 "/src/ios-device.do"
    const auto parent = ::std_::path::index::dirname(path);
#line 307 "/src/ios-device.do"
    if (parent != path) {
#line 307 "/src/ios-device.do"
        ensureDirectory(parent);
    }
#line 308 "/src/ios-device.do"
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 308, std::string("try! failed"));  }();
}
#line 311 "/src/ios-device.do"
void removeTree(const std::string& path) {
#line 312 "/src/ios-device.do"
    if (!::doof_fs::exists(path)) {
#line 312 "/src/ios-device.do"
        return;
    }
#line 313 "/src/ios-device.do"
    if (::doof_fs::isDirectory(path)) {
#line 314 "/src/ios-device.do"
        const auto& _iterable_22 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 314, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_22) {
#line 314 "/src/ios-device.do"
            removeTree(devicePath(path, entry->name));
        }
    }
#line 316 "/src/ios-device.do"
    [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 316, std::string("try! failed"));  }();
}
#line 319 "/src/ios-device.do"
std::shared_ptr<IOSDeviceCommandResult> runDeviceCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments) {
#line 320 "/src/ios-device.do"
    auto _binding_value_23 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_IOS_DEVICE_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_23)) {
        const auto error = doof::failure_error(_binding_value_23);
#line 324 "/src/ios-device.do"
        return std::make_shared<IOSDeviceCommandResult>(-1, std::string(""), error);
    }
    const auto executed = doof::success_value(_binding_value_23);
#line 325 "/src/ios-device.do"
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(executed->stdout_, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((executed->stdout_)->size()))));
#line 326 "/src/ios-device.do"
    return std::make_shared<IOSDeviceCommandResult>(executed->exitCode, output, std::string(""));
}
#line 329 "/src/ios-device.do"
doof::Result<std::string, std::string> deviceCommandText(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description) {
#line 330 "/src/ios-device.do"
    const auto result = runDeviceCommand(command, arguments);
#line 331 "/src/ios-device.do"
    const auto output = ((result->error != std::string("")) ? result->error : result->output);
#line 332 "/src/ios-device.do"
    if (result->exitCode != 0) {
#line 333 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((description + std::string(" failed")) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
#line 335 "/src/ios-device.do"
    return doof::Success<std::string>{ output };
}
#line 338 "/src/ios-device.do"
doof::Result<void, std::string> decodeProvisioningProfile(const std::string& profilePath, const std::string& decodedPath) {
#line 339 "/src/ios-device.do"
    const auto securityResult = runDeviceCommand(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("cms"), std::string("-D"), std::string("-i"), profilePath}));
#line 340 "/src/ios-device.do"
    if (securityResult->exitCode == 0) {
#line 341 "/src/ios-device.do"
        [&]() -> void { auto _try_value = ::doof_fs::writeText(decodedPath, securityResult->output); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 341, std::string("try! failed"));  }();
#line 342 "/src/ios-device.do"
        return doof::Success<void>{};
    }
#line 344 "/src/ios-device.do"
    const auto opensslResult = runDeviceCommand(std::string("openssl"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("smime"), std::string("-inform"), std::string("der"), std::string("-verify"), std::string("-noverify"), std::string("-in"), profilePath, std::string("-out"), decodedPath}));
#line 347 "/src/ios-device.do"
    if (opensslResult->exitCode != 0) {
#line 348 "/src/ios-device.do"
        const auto output = ((securityResult->error != std::string("")) ? securityResult->error : securityResult->output);
#line 349 "/src/ios-device.do"
        const auto fallbackOutput = ((opensslResult->error != std::string("")) ? opensslResult->error : opensslResult->output);
#line 350 "/src/ios-device.do"
        return doof::Failure<std::string>{ (std::string("decoding provisioning profile failed") + ((fallbackOutput != std::string("")) ? (std::string(":\n") + fallbackOutput) : ((output != std::string("")) ? (std::string(":\n") + output) : std::string("")))) };
    }
#line 355 "/src/ios-device.do"
    return doof::Success<void>{};
}
#line 358 "/src/ios-device.do"
std::string resolveUserPath(const std::string& path) {
#line 359 "/src/ios-device.do"
    if (path == std::string("~")) {
#line 359 "/src/ios-device.do"
        return [&]() -> std::string { auto _try_value = ::std_::path::index::homeDirectory(); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 359, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    }
#line 360 "/src/ios-device.do"
    if (doof::string_startsWith(path, std::string("~/"))) {
#line 360 "/src/ios-device.do"
        return devicePath([&]() -> std::string { auto _try_value = ::std_::path::index::homeDirectory(); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 360, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }(), doof::string_substring(path, 2, static_cast<int32_t>(path.size())));
    }
#line 361 "/src/ios-device.do"
    return [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 361, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
}
#line 364 "/src/ios-device.do"
void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 365 "/src/ios-device.do"
    if (!doof::array_contains(values, value, "", 0)) {
#line 365 "/src/ios-device.do"
        values->push_back(value);
    }
}
#line 368 "/src/ios-device.do"
doof::Result<std::string, std::string> certificateFingerprint(const std::string& certificateData) {
#line 369 "/src/ios-device.do"
    auto _binding_value_24 = ::doof_crypto::decode_base64(certificateData);
    if (doof::is_failure(_binding_value_24)) {
        const auto error = doof::failure_error(_binding_value_24);
#line 369 "/src/ios-device.do"
        return doof::Failure<std::string>{ error };
    }
    const auto decoded = doof::success_value(_binding_value_24);
#line 370 "/src/ios-device.do"
    const auto fingerprint = doof::string_toUpperCase(::std_::crypto::index::sha1Hex(decoded));
#line 371 "/src/ios-device.do"
    if (!isHexFingerprint(fingerprint)) {
#line 371 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("Could not parse provisioning profile certificate fingerprint") };
    }
#line 372 "/src/ios-device.do"
    return doof::Success<std::string>{ fingerprint };
}
#line 375 "/src/ios-device.do"
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> parseProvisioningProfile(const std::string& profilePath, const std::string& workDirectory) {
#line 376 "/src/ios-device.do"
    ensureDirectory(workDirectory);
#line 377 "/src/ios-device.do"
    const auto decodedPath = devicePath(workDirectory, std::string("profile.plist"));
#line 378 "/src/ios-device.do"
    auto _try_value_25 = decodeProvisioningProfile(profilePath, decodedPath);
    if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_25))};
#line 379 "/src/ios-device.do"
    auto _try_value_26 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements.application-identifier"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile application identifier"));
    if (doof::is_failure(_try_value_26)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_26))};
    const auto applicationIdentifier = doof::success_value(_try_value_26);
#line 383 "/src/ios-device.do"
    if (applicationIdentifier == std::string("")) {
#line 384 "/src/ios-device.do"
        return doof::Failure<std::string>{ (std::string("Provisioning profile missing Entitlements.application-identifier: ") + profilePath) };
    }
#line 386 "/src/ios-device.do"
    const auto expirationResult = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("ExpirationDate"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile expiration date"));
#line 390 "/src/ios-device.do"
    auto expirationText = std::string("");
#line 391 "/src/ios-device.do"
    {
        auto _case_subject = expirationResult;
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
#line 392 "/src/ios-device.do"
            (expirationText = success.value);
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
#line 395 "/src/ios-device.do"
    auto expirationEpochMs = 0LL;
#line 396 "/src/ios-device.do"
    if (expirationText != std::string("")) {
#line 397 "/src/ios-device.do"
        {
            auto _case_subject = ::std_::time::temporal::Instant::parse(expirationText);
            if (std::holds_alternative<doof::Success<std::shared_ptr<::std_::time::temporal::Instant>>>(_case_subject)) {
                const auto& success = std::get<doof::Success<std::shared_ptr<::std_::time::temporal::Instant>>>(_case_subject);
#line 398 "/src/ios-device.do"
                (expirationEpochMs = success.value->toEpochMillis());
        }
        else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        }
        }
    }
#line 402 "/src/ios-device.do"
    auto provisionedDeviceCount = 0;
#line 403 "/src/ios-device.do"
    {
        auto _case_subject = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("ProvisionedDevices"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile device count"));
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
#line 408 "/src/ios-device.do"
            {
                auto _case_subject = ::doof_parse::parseInt(success.value);
                if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
                    const auto& parsedCount = std::get<doof::Success<int32_t>>(_case_subject);
#line 409 "/src/ios-device.do"
                    (provisionedDeviceCount = parsedCount.value);
            }
            else if (std::holds_alternative<doof::Failure<::std_::parse::types::ParsingError>>(_case_subject)) {
            }
            }
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
#line 415 "/src/ios-device.do"
    auto provisionsAllDevices = false;
#line 416 "/src/ios-device.do"
    {
        auto _case_subject = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("ProvisionsAllDevices"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading enterprise provisioning flag"));
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
#line 420 "/src/ios-device.do"
            (provisionsAllDevices = (success.value == std::string("true")));
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
#line 423 "/src/ios-device.do"
    auto getTaskAllow = false;
#line 424 "/src/ios-device.do"
    {
        auto _case_subject = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements.get-task-allow"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading development provisioning flag"));
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
#line 428 "/src/ios-device.do"
            (getTaskAllow = (success.value == std::string("true")));
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
#line 431 "/src/ios-device.do"
    std::shared_ptr<std::vector<std::string>> certFingerprints = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 432 "/src/ios-device.do"
    auto certificateCount = 0;
#line 433 "/src/ios-device.do"
    {
        auto _case_subject = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("DeveloperCertificates"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile certificate count"));
        if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
            const auto& success = std::get<doof::Success<std::string>>(_case_subject);
#line 438 "/src/ios-device.do"
            {
                auto _case_subject = ::doof_parse::parseInt(success.value);
                if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
                    const auto& parsedCount = std::get<doof::Success<int32_t>>(_case_subject);
#line 439 "/src/ios-device.do"
                    (certificateCount = parsedCount.value);
            }
            else if (std::holds_alternative<doof::Failure<::std_::parse::types::ParsingError>>(_case_subject)) {
            }
            }
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
#line 445 "/src/ios-device.do"
    for (int32_t index = 0; index < certificateCount; ++index) {
#line 446 "/src/ios-device.do"
        auto _binding_value_28 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), (std::string("DeveloperCertificates.") + doof::to_string(index)), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile certificate"));
        if (doof::is_failure(_binding_value_28)) {
            const auto& encoded = _binding_value_28;
#line 449 "/src/ios-device.do"
            continue;
        }
        const auto encoded = doof::success_value(_binding_value_28);
#line 450 "/src/ios-device.do"
        if (encoded == std::string("")) {
#line 450 "/src/ios-device.do"
            continue;
        }
#line 451 "/src/ios-device.do"
        auto _binding_value_29 = certificateFingerprint(encoded);
        if (doof::is_failure(_binding_value_29)) {
            const auto& fingerprint = _binding_value_29;
#line 451 "/src/ios-device.do"
            continue;
        }
        const auto fingerprint = doof::success_value(_binding_value_29);
#line 452 "/src/ios-device.do"
        appendUnique(certFingerprints, fingerprint);
    }
#line 454 "/src/ios-device.do"
    return doof::Success<std::shared_ptr<IOSProvisioningProfile>>{ std::make_shared<IOSProvisioningProfile>(profilePath, applicationIdentifier, certFingerprints, expirationEpochMs, provisionedDeviceCount, provisionsAllDevices, getTaskAllow) };
}
#line 465 "/src/ios-device.do"
std::shared_ptr<std::vector<std::string>> collectProvisioningProfilePaths(const std::shared_ptr<std::vector<std::string>>& profileDirectories) {
#line 466 "/src/ios-device.do"
    const auto directories = ((static_cast<int32_t>((profileDirectories)->size()) > 0) ? profileDirectories : std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("~/Library/Developer/Xcode/UserData/Provisioning Profiles"), std::string("~/Library/MobileDevice/Provisioning Profiles")}));
#line 470 "/src/ios-device.do"
    std::shared_ptr<std::vector<std::string>> paths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 471 "/src/ios-device.do"
    const auto& _iterable_31 = directories;
    for (const auto& directory : *_iterable_31) {
#line 472 "/src/ios-device.do"
        const auto expanded = resolveUserPath(directory);
#line 473 "/src/ios-device.do"
        if (!::doof_fs::isDirectory(expanded)) {
#line 473 "/src/ios-device.do"
            continue;
        }
#line 474 "/src/ios-device.do"
        const auto& _iterable_33 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(expanded); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 474, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_33) {
#line 475 "/src/ios-device.do"
            if (doof::string_endsWith(entry->name, std::string(".mobileprovision"))) {
#line 475 "/src/ios-device.do"
                appendUnique(paths, devicePath(expanded, entry->name));
            }
        }
    }
#line 478 "/src/ios-device.do"
    return paths;
}
#line 481 "/src/ios-device.do"
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> autoResolveProvisioningProfile(const std::string& bundleId, const std::string& workDirectory, const std::shared_ptr<std::vector<std::string>>& profileDirectories) {
#line 486 "/src/ios-device.do"
    std::shared_ptr<std::vector<std::shared_ptr<IOSProvisioningProfile>>> profiles = std::make_shared<std::vector<std::shared_ptr<IOSProvisioningProfile>>>(std::vector<std::shared_ptr<IOSProvisioningProfile>>{});
#line 487 "/src/ios-device.do"
    const auto& _iterable_35 = collectProvisioningProfilePaths(profileDirectories);
    for (const auto& profilePath : *_iterable_35) {
#line 488 "/src/ios-device.do"
        auto _binding_value_36 = parseProvisioningProfile(profilePath, workDirectory);
        if (doof::is_failure(_binding_value_36)) {
            const auto& profile = _binding_value_36;
#line 488 "/src/ios-device.do"
            continue;
        }
        const auto profile = doof::success_value(_binding_value_36);
#line 489 "/src/ios-device.do"
        profiles->push_back(profile);
    }
#line 491 "/src/ios-device.do"
    return selectProvisioningProfile(bundleId, profiles, ::std_::time::temporal::Instant::now()->toEpochMillis());
}
#line 495 "/src/ios-device.do"
doof::Result<std::shared_ptr<IOSDeviceSigningOptions>, std::string> resolveIOSDeviceSigningOptions(const std::string& bundleId, const std::string& signIdentityOverride, const std::string& provisioningProfileOverride, const std::string& workDirectory, const std::shared_ptr<std::vector<std::string>>& profileDirectories) {
#line 502 "/src/ios-device.do"
    if (hostPlatform() != std::string("macos")) {
#line 502 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("iOS device signing is only supported on macOS") };
    }
#line 503 "/src/ios-device.do"
    const auto profilePath = ((provisioningProfileOverride == std::string("")) ? std::string("") : resolveUserPath(provisioningProfileOverride));
#line 504 "/src/ios-device.do"
    if ((profilePath != std::string("")) && (signIdentityOverride != std::string(""))) {
#line 505 "/src/ios-device.do"
        return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(signIdentityOverride, profilePath) };
    }
#line 510 "/src/ios-device.do"
    const auto profile = ((profilePath == std::string("")) ? autoResolveProvisioningProfile(bundleId, workDirectory, profileDirectories) : parseProvisioningProfile(profilePath, workDirectory));
#line 513 "/src/ios-device.do"
    auto _binding_value_37 = profile;
    if (doof::is_failure(_binding_value_37)) {
        const auto error = doof::failure_error(_binding_value_37);
#line 513 "/src/ios-device.do"
        return doof::Failure<std::string>{ error };
    }
    const auto selectedProfile = doof::success_value(_binding_value_37);
#line 514 "/src/ios-device.do"
    if (signIdentityOverride != std::string("")) {
#line 515 "/src/ios-device.do"
        return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(signIdentityOverride, selectedProfile->profilePath) };
    }
#line 520 "/src/ios-device.do"
    auto _try_value_38 = deviceCommandText(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("find-identity"), std::string("-v"), std::string("-p"), std::string("codesigning")}), std::string("listing code-signing identities"));
    if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
    const auto identitiesOutput = doof::success_value(_try_value_38);
#line 523 "/src/ios-device.do"
    auto _try_value_39 = selectSigningIdentity(selectedProfile, parseCodesignIdentities(identitiesOutput));
    if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_39))};
    const auto identity = doof::success_value(_try_value_39);
#line 524 "/src/ios-device.do"
    return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(identity, selectedProfile->profilePath) };
}
#line 531 "/src/ios-device.do"
doof::Result<std::string, std::string> resolveIOSDeviceIdentifier(const std::string& overrideIdentifier, const std::string& workDirectory) {
#line 532 "/src/ios-device.do"
    if (overrideIdentifier != std::string("")) {
#line 532 "/src/ios-device.do"
        return doof::Success<std::string>{ overrideIdentifier };
    }
#line 533 "/src/ios-device.do"
    if (hostPlatform() != std::string("macos")) {
#line 533 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("iOS device discovery is only supported on macOS") };
    }
#line 534 "/src/ios-device.do"
    ensureDirectory(workDirectory);
#line 535 "/src/ios-device.do"
    const auto devicesPath = devicePath(workDirectory, std::string("devices.json"));
#line 536 "/src/ios-device.do"
    if (::doof_fs::exists(devicesPath)) {
#line 536 "/src/ios-device.do"
        [&]() -> void { auto _try_value = ::doof_fs::remove(devicesPath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 536, std::string("try! failed"));  }();
    }
#line 537 "/src/ios-device.do"
    auto _binding_value_40 = deviceCommandText(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("list"), std::string("devices"), std::string("--json-output"), devicesPath}), std::string("listing connected iOS devices"));
    if (doof::is_failure(_binding_value_40)) {
        const auto error = doof::failure_error(_binding_value_40);
#line 540 "/src/ios-device.do"
        return doof::Failure<std::string>{ error };
    }
    const auto result = doof::success_value(_binding_value_40);
#line 541 "/src/ios-device.do"
    auto _binding_value_41 = ::doof_fs::readText(devicesPath);
    if (doof::is_failure(_binding_value_41)) {
        const auto& rawJson = _binding_value_41;
#line 541 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("Could not read devicectl device output") };
    }
    const auto rawJson = doof::success_value(_binding_value_41);
#line 542 "/src/ios-device.do"
    auto _binding_value_42 = parseConnectedIOSDevices(rawJson);
    if (doof::is_failure(_binding_value_42)) {
        const auto error = doof::failure_error(_binding_value_42);
#line 542 "/src/ios-device.do"
        return doof::Failure<std::string>{ error };
    }
    const auto devices = doof::success_value(_binding_value_42);
#line 543 "/src/ios-device.do"
    if (::doof_fs::exists(devicesPath)) {
#line 543 "/src/ios-device.do"
        [&]() -> void { auto _try_value = ::doof_fs::remove(devicesPath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 543, std::string("try! failed"));  }();
    }
#line 544 "/src/ios-device.do"
    return selectIOSDeviceIdentifier(std::string(""), devices);
}
#line 547 "/src/ios-device.do"
void collectNestedIOSCode(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results) {
#line 548 "/src/ios-device.do"
    if (!::doof_fs::exists(path)) {
#line 548 "/src/ios-device.do"
        return;
    }
#line 549 "/src/ios-device.do"
    if (::doof_fs::isDirectory(path)) {
#line 550 "/src/ios-device.do"
        if (doof::string_endsWith(path, std::string(".framework")) || doof::string_endsWith(path, std::string(".appex"))) {
#line 550 "/src/ios-device.do"
            results->push_back(path);
#line 550 "/src/ios-device.do"
            return;
        }
#line 551 "/src/ios-device.do"
        const auto& _iterable_44 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 551, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_44) {
#line 551 "/src/ios-device.do"
            collectNestedIOSCode(devicePath(path, entry->name), results);
        }
#line 552 "/src/ios-device.do"
        return;
    }
#line 554 "/src/ios-device.do"
    if (doof::string_endsWith(path, std::string(".dylib")) || doof::string_endsWith(path, std::string(".so"))) {
#line 554 "/src/ios-device.do"
        results->push_back(path);
    }
}
#line 558 "/src/ios-device.do"
doof::Result<void, std::string> signIOSDeviceApp(const std::string& appPath, const std::string& bundleId, const std::shared_ptr<IOSDeviceSigningOptions>& options, const std::string& workDirectory) {
#line 564 "/src/ios-device.do"
    if (hostPlatform() != std::string("macos")) {
#line 564 "/src/ios-device.do"
        return doof::Failure<std::string>{ std::string("iOS device signing is only supported on macOS") };
    }
#line 565 "/src/ios-device.do"
    if (!::doof_fs::exists(options->provisioningProfilePath)) {
#line 566 "/src/ios-device.do"
        return doof::Failure<std::string>{ (std::string("Provisioning profile not found: ") + options->provisioningProfilePath) };
    }
#line 568 "/src/ios-device.do"
    removeTree(workDirectory);
#line 569 "/src/ios-device.do"
    ensureDirectory(workDirectory);
#line 570 "/src/ios-device.do"
    const auto decodedPath = devicePath(workDirectory, std::string("profile.plist"));
#line 571 "/src/ios-device.do"
    const auto entitlementsPath = devicePath(workDirectory, std::string("entitlements.plist"));
#line 572 "/src/ios-device.do"
    auto _try_value_45 = decodeProvisioningProfile(options->provisioningProfilePath, decodedPath);
    if (doof::is_failure(_try_value_45)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_45))};
#line 573 "/src/ios-device.do"
    auto _try_value_46 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements.application-identifier"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile application identifier"));
    if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_46))};
    const auto applicationIdentifier = doof::success_value(_try_value_46);
#line 577 "/src/ios-device.do"
    if (!profileMatchesBundleId(applicationIdentifier, bundleId)) {
#line 578 "/src/ios-device.do"
        removeTree(workDirectory);
#line 579 "/src/ios-device.do"
        return doof::Failure<std::string>{ ((((std::string("Provisioning profile application-identifier \"") + applicationIdentifier) + std::string("\" does not match bundle id \"")) + bundleId) + std::string("\"")) };
    }
#line 584 "/src/ios-device.do"
    auto _try_value_47 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements"), std::string("xml1"), std::string("-o"), entitlementsPath, decodedPath}), std::string("extracting iOS signing entitlements"));
    if (doof::is_failure(_try_value_47)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_47))};
    const auto ignored = doof::success_value(_try_value_47);
#line 588 "/src/ios-device.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(devicePath(appPath, std::string("embedded.mobileprovision")), [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(options->provisioningProfilePath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 588, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }()); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 588, std::string("try! failed"));  }();
#line 589 "/src/ios-device.do"
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 590 "/src/ios-device.do"
    collectNestedIOSCode(devicePath(appPath, std::string("Frameworks")), nested);
#line 591 "/src/ios-device.do"
    collectNestedIOSCode(devicePath(appPath, std::string("PlugIns")), nested);
#line 592 "/src/ios-device.do"
    const auto& _iterable_49 = nested;
    for (const auto& path : *_iterable_49) {
#line 593 "/src/ios-device.do"
        auto _try_value_50 = deviceCommandText(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(path, options->signIdentity, std::string("")), std::string("signing nested iOS code"));
        if (doof::is_failure(_try_value_50)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_50))};
        const auto nestedIgnored = doof::success_value(_try_value_50);
    }
#line 597 "/src/ios-device.do"
    auto _try_value_51 = deviceCommandText(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(appPath, options->signIdentity, entitlementsPath), std::string("signing the iOS app"));
    if (doof::is_failure(_try_value_51)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_51))};
    const auto appIgnored = doof::success_value(_try_value_51);
#line 600 "/src/ios-device.do"
    removeTree(workDirectory);
#line 601 "/src/ios-device.do"
    return doof::Success<void>{};
}
#line 1 "<doof-generated>"
}
