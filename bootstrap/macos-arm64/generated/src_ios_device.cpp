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





std::variant<std::monostate, doof::JsonValue> jsonObjectField(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
    if (![&]() -> bool { auto _map_has_1 = object; return _map_has_1->find(name) != _map_has_1->end(); }()) {
        return std::monostate{};
    }
    auto _binding_value_2 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_2)) {
        const auto& value = _binding_value_2;
        return std::monostate{};
    }
    const auto value = doof::success_value(_binding_value_2);
    return value;
}
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> jsonObjectValue(const std::variant<std::monostate, doof::JsonValue>& value) {
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
    doof::unreachable();
}
std::shared_ptr<std::vector<doof::JsonValue>> jsonArrayValue(const std::variant<std::monostate, doof::JsonValue>& value) {
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
    doof::unreachable();
}
std::string jsonStringValue(const std::variant<std::monostate, doof::JsonValue>& value) {
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
    doof::unreachable();
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>, std::string> parseConnectedIOSDevices(const std::string& rawJson) {
    auto _binding_value_3 = ::doof_json::parse(rawJson);
    if (doof::is_failure(_binding_value_3)) {
        const auto error = doof::failure_error(_binding_value_3);
        return doof::Failure<std::string>{ error };
    }
    const auto parsed = doof::success_value(_binding_value_3);
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
    const auto& _iterable_5 = values;
    for (const auto& value : *_iterable_5) {
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
doof::Result<std::string, std::string> selectIOSDeviceIdentifier(const std::string& overrideIdentifier, const std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>& devices) {
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
            (choices += (((doof::array_at(devices, index, "src/ios-device", 117)->name + std::string(" (")) + doof::array_at(devices, index, "src/ios-device", 117)->identifier) + std::string(")")));
        }
        return doof::Failure<std::string>{ ((std::string("Multiple connected iOS devices found (") + choices) + std::string("). Pass --ios-device to select one.")) };
    }
    return doof::Success<std::string>{ doof::array_at(devices, 0, "src/ios-device", 121)->identifier };
}
bool isHexFingerprint(const std::string& value) {
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
std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> parseCodesignIdentities(const std::string& output) {
    std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities = std::make_shared<std::vector<std::shared_ptr<IOSCodesignIdentity>>>(std::vector<std::shared_ptr<IOSCodesignIdentity>>{});
    const auto& _iterable_9 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_9) {
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
std::string provisionedBundleId(const std::string& applicationIdentifier) {
    const auto separator = doof::string_indexOf(applicationIdentifier, std::string("."));
    if (separator < 0) {
        return std::string("");
    }
    return doof::string_substring(applicationIdentifier, (separator + 1), static_cast<int32_t>(applicationIdentifier.size()));
}
bool profileMatchesBundleId(const std::string& applicationIdentifier, const std::string& bundleId) {
    const auto provisioned = provisionedBundleId(applicationIdentifier);
    return (((provisioned == bundleId) || (provisioned == std::string("*"))) || (doof::string_endsWith(provisioned, std::string(".*")) && doof::string_startsWith(bundleId, doof::string_substring(provisioned, 0, (static_cast<int32_t>(provisioned.size()) - 1)))));
}
int32_t provisioningSpecificity(const std::string& applicationIdentifier, const std::string& bundleId) {
    const auto provisioned = provisionedBundleId(applicationIdentifier);
    if (provisioned == bundleId) {
        return 2;
    }
    if ((provisioned == std::string("*")) || doof::string_endsWith(provisioned, std::string(".*"))) {
        return 1;
    }
    return 0;
}
bool betterProvisioningProfile(const std::shared_ptr<IOSProvisioningProfile>& candidate, const std::shared_ptr<IOSProvisioningProfile>& current, const std::string& bundleId, int64_t nowEpochMs) {
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
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> selectProvisioningProfile(const std::string& bundleId, const std::shared_ptr<std::vector<std::shared_ptr<IOSProvisioningProfile>>>& profiles, int64_t nowEpochMs) {
    std::shared_ptr<IOSProvisioningProfile> selected = nullptr;
    const auto& _iterable_11 = profiles;
    for (const auto& profile : *_iterable_11) {
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
doof::Result<std::string, std::string> selectSigningIdentity(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities) {
    if (static_cast<int32_t>((profile->certFingerprints)->size()) == 0) {
        return doof::Failure<std::string>{ ((std::string("Provisioning profile \"") + profile->profilePath) + std::string("\" does not include DeveloperCertificates. Pass --ios-sign-identity.")) };
    }
    const auto& _iterable_15 = identities;
    for (const auto& identity : *_iterable_15) {
        const auto& _iterable_13 = profile->certFingerprints;
        for (const auto& fingerprint : *_iterable_13) {
            if (identity->fingerprint == fingerprint) {
                return doof::Success<std::string>{ identity->name };
            }
        }
    }
    return doof::Failure<std::string>{ ((std::string("Could not auto-detect a signing identity for profile \"") + profile->profilePath) + std::string("\". Pass --ios-sign-identity.")) };
}
doof::Result<std::string, std::string> resolveIOSAdHocSigningIdentity(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities, const std::string& configuredIdentity) {
    if (configuredIdentity != std::string("")) {
        return doof::Success<std::string>{ configuredIdentity };
    }
    std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> matching = std::make_shared<std::vector<std::shared_ptr<IOSCodesignIdentity>>>(std::vector<std::shared_ptr<IOSCodesignIdentity>>{});
    const auto& _iterable_17 = identities;
    for (const auto& identity : *_iterable_17) {
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
            (names += doof::array_at(matching, index, "src/ios-device", 242)->name);
        }
        return doof::Failure<std::string>{ ((((std::string("Multiple Apple Distribution identities are included in provisioning profile \"") + profile->profilePath) + std::string("\" (")) + names) + std::string("). Pass --ios-sign-identity.")) };
    }
    return doof::Success<std::string>{ doof::array_at(matching, 0, "src/ios-device", 249)->name };
}
doof::Result<void, std::string> validateIOSAdHocSigning(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities, const std::string& identityName, const std::string& bundleId, int64_t nowEpochMs) {
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
    const auto& _iterable_20 = identities;
    for (const auto& identity : *_iterable_20) {
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
std::string devicePath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
void ensureDirectory(const std::string& path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return;
    }
    const auto parent = ::std_::path::index::dirname(path);
    if (parent != path) {
        ensureDirectory(parent);
    }
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 308, std::string("try! failed"));  }();
}
void removeTree(const std::string& path) {
    if (!::doof_fs::exists(path)) {
        return;
    }
    if (::doof_fs::isDirectory(path)) {
        const auto& _iterable_22 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 314, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_22) {
            removeTree(devicePath(path, entry->name));
        }
    }
    [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 316, std::string("try! failed"));  }();
}
std::shared_ptr<IOSDeviceCommandResult> runDeviceCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments) {
    auto _binding_value_23 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_IOS_DEVICE_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_23)) {
        const auto error = doof::failure_error(_binding_value_23);
        return std::make_shared<IOSDeviceCommandResult>(-1, std::string(""), error);
    }
    const auto executed = doof::success_value(_binding_value_23);
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(executed->stdout_, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((executed->stdout_)->size()))));
    return std::make_shared<IOSDeviceCommandResult>(executed->exitCode, output, std::string(""));
}
doof::Result<std::string, std::string> deviceCommandText(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description) {
    const auto result = runDeviceCommand(command, arguments);
    const auto output = ((result->error != std::string("")) ? result->error : result->output);
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ ((description + std::string(" failed")) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
    return doof::Success<std::string>{ output };
}
doof::Result<void, std::string> decodeProvisioningProfile(const std::string& profilePath, const std::string& decodedPath) {
    const auto securityResult = runDeviceCommand(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("cms"), std::string("-D"), std::string("-i"), profilePath}));
    if (securityResult->exitCode == 0) {
        [&]() -> void { auto _try_value = ::doof_fs::writeText(decodedPath, securityResult->output); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 341, std::string("try! failed"));  }();
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
std::string resolveUserPath(const std::string& path) {
    if (path == std::string("~")) {
        return [&]() -> std::string { auto _try_value = ::std_::path::index::homeDirectory(); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 359, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    }
    if (doof::string_startsWith(path, std::string("~/"))) {
        return devicePath([&]() -> std::string { auto _try_value = ::std_::path::index::homeDirectory(); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 360, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }(), doof::string_substring(path, 2, static_cast<int32_t>(path.size())));
    }
    return [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 361, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
}
void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    if (!doof::array_contains(values, value, "", 0)) {
        values->push_back(value);
    }
}
doof::Result<std::string, std::string> certificateFingerprint(const std::string& certificateData) {
    auto _binding_value_24 = ::doof_crypto::decode_base64(certificateData);
    if (doof::is_failure(_binding_value_24)) {
        const auto error = doof::failure_error(_binding_value_24);
        return doof::Failure<std::string>{ error };
    }
    const auto decoded = doof::success_value(_binding_value_24);
    const auto fingerprint = doof::string_toUpperCase(::std_::crypto::index::sha1Hex(decoded));
    if (!isHexFingerprint(fingerprint)) {
        return doof::Failure<std::string>{ std::string("Could not parse provisioning profile certificate fingerprint") };
    }
    return doof::Success<std::string>{ fingerprint };
}
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> parseProvisioningProfile(const std::string& profilePath, const std::string& workDirectory) {
    ensureDirectory(workDirectory);
    const auto decodedPath = devicePath(workDirectory, std::string("profile.plist"));
    auto _try_value_25 = decodeProvisioningProfile(profilePath, decodedPath);
    if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_25))};
    auto _try_value_26 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements.application-identifier"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile application identifier"));
    if (doof::is_failure(_try_value_26)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_26))};
    const auto applicationIdentifier = doof::success_value(_try_value_26);
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
                auto _case_subject = ::doof_parse::parseInt(success.value);
                if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
                    const auto& parsedCount = std::get<doof::Success<int32_t>>(_case_subject);
                    (provisionedDeviceCount = parsedCount.value);
            }
            else if (std::holds_alternative<doof::Failure<::std_::parse::types::ParsingError>>(_case_subject)) {
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
                auto _case_subject = ::doof_parse::parseInt(success.value);
                if (std::holds_alternative<doof::Success<int32_t>>(_case_subject)) {
                    const auto& parsedCount = std::get<doof::Success<int32_t>>(_case_subject);
                    (certificateCount = parsedCount.value);
            }
            else if (std::holds_alternative<doof::Failure<::std_::parse::types::ParsingError>>(_case_subject)) {
            }
            }
    }
    else if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
    }
    }
    for (int32_t index = 0; index < certificateCount; ++index) {
        auto _binding_value_27 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), (std::string("DeveloperCertificates.") + doof::to_string(index)), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile certificate"));
        if (doof::is_failure(_binding_value_27)) {
            const auto& encoded = _binding_value_27;
            continue;
        }
        const auto encoded = doof::success_value(_binding_value_27);
        if (encoded == std::string("")) {
            continue;
        }
        auto _binding_value_28 = certificateFingerprint(encoded);
        if (doof::is_failure(_binding_value_28)) {
            const auto& fingerprint = _binding_value_28;
            continue;
        }
        const auto fingerprint = doof::success_value(_binding_value_28);
        appendUnique(certFingerprints, fingerprint);
    }
    return doof::Success<std::shared_ptr<IOSProvisioningProfile>>{ std::make_shared<IOSProvisioningProfile>(profilePath, applicationIdentifier, certFingerprints, expirationEpochMs, provisionedDeviceCount, provisionsAllDevices, getTaskAllow) };
}
std::shared_ptr<std::vector<std::string>> collectProvisioningProfilePaths(const std::shared_ptr<std::vector<std::string>>& profileDirectories) {
    const auto directories = ((static_cast<int32_t>((profileDirectories)->size()) > 0) ? profileDirectories : std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("~/Library/Developer/Xcode/UserData/Provisioning Profiles"), std::string("~/Library/MobileDevice/Provisioning Profiles")}));
    std::shared_ptr<std::vector<std::string>> paths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_33 = directories;
    for (const auto& directory : *_iterable_33) {
        const auto expanded = resolveUserPath(directory);
        if (!::doof_fs::isDirectory(expanded)) {
            continue;
        }
        const auto& _iterable_31 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(expanded); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 474, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_31) {
            if (doof::string_endsWith(entry->name, std::string(".mobileprovision"))) {
                appendUnique(paths, devicePath(expanded, entry->name));
            }
        }
    }
    return paths;
}
doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> autoResolveProvisioningProfile(const std::string& bundleId, const std::string& workDirectory, const std::shared_ptr<std::vector<std::string>>& profileDirectories) {
    std::shared_ptr<std::vector<std::shared_ptr<IOSProvisioningProfile>>> profiles = std::make_shared<std::vector<std::shared_ptr<IOSProvisioningProfile>>>(std::vector<std::shared_ptr<IOSProvisioningProfile>>{});
    const auto& _iterable_36 = collectProvisioningProfilePaths(profileDirectories);
    for (const auto& profilePath : *_iterable_36) {
        auto _binding_value_34 = parseProvisioningProfile(profilePath, workDirectory);
        if (doof::is_failure(_binding_value_34)) {
            const auto& profile = _binding_value_34;
            continue;
        }
        const auto profile = doof::success_value(_binding_value_34);
        profiles->push_back(profile);
    }
    return selectProvisioningProfile(bundleId, profiles, ::std_::time::temporal::Instant::now()->toEpochMillis());
}
doof::Result<std::shared_ptr<IOSDeviceSigningOptions>, std::string> resolveIOSDeviceSigningOptions(const std::string& bundleId, const std::string& signIdentityOverride, const std::string& provisioningProfileOverride, const std::string& workDirectory, const std::shared_ptr<std::vector<std::string>>& profileDirectories) {
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS device signing is only supported on macOS") };
    }
    const auto profilePath = ((provisioningProfileOverride == std::string("")) ? std::string("") : resolveUserPath(provisioningProfileOverride));
    if ((profilePath != std::string("")) && (signIdentityOverride != std::string(""))) {
        return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(signIdentityOverride, profilePath) };
    }
    const auto profile = ((profilePath == std::string("")) ? autoResolveProvisioningProfile(bundleId, workDirectory, profileDirectories) : parseProvisioningProfile(profilePath, workDirectory));
    auto _binding_value_37 = profile;
    if (doof::is_failure(_binding_value_37)) {
        const auto error = doof::failure_error(_binding_value_37);
        return doof::Failure<std::string>{ error };
    }
    const auto selectedProfile = doof::success_value(_binding_value_37);
    if (signIdentityOverride != std::string("")) {
        return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(signIdentityOverride, selectedProfile->profilePath) };
    }
    auto _try_value_38 = deviceCommandText(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("find-identity"), std::string("-v"), std::string("-p"), std::string("codesigning")}), std::string("listing code-signing identities"));
    if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
    const auto identitiesOutput = doof::success_value(_try_value_38);
    auto _try_value_39 = selectSigningIdentity(selectedProfile, parseCodesignIdentities(identitiesOutput));
    if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_39))};
    const auto identity = doof::success_value(_try_value_39);
    return doof::Success<std::shared_ptr<IOSDeviceSigningOptions>>{ std::make_shared<IOSDeviceSigningOptions>(identity, selectedProfile->profilePath) };
}
doof::Result<std::string, std::string> resolveIOSDeviceIdentifier(const std::string& overrideIdentifier, const std::string& workDirectory) {
    if (overrideIdentifier != std::string("")) {
        return doof::Success<std::string>{ overrideIdentifier };
    }
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS device discovery is only supported on macOS") };
    }
    ensureDirectory(workDirectory);
    const auto devicesPath = devicePath(workDirectory, std::string("devices.json"));
    if (::doof_fs::exists(devicesPath)) {
        [&]() -> void { auto _try_value = ::doof_fs::remove(devicesPath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 536, std::string("try! failed"));  }();
    }
    auto _binding_value_40 = deviceCommandText(std::string("xcrun"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("devicectl"), std::string("list"), std::string("devices"), std::string("--json-output"), devicesPath}), std::string("listing connected iOS devices"));
    if (doof::is_failure(_binding_value_40)) {
        const auto error = doof::failure_error(_binding_value_40);
        return doof::Failure<std::string>{ error };
    }
    const auto result = doof::success_value(_binding_value_40);
    auto _binding_value_41 = ::doof_fs::readText(devicesPath);
    if (doof::is_failure(_binding_value_41)) {
        const auto& rawJson = _binding_value_41;
        return doof::Failure<std::string>{ std::string("Could not read devicectl device output") };
    }
    const auto rawJson = doof::success_value(_binding_value_41);
    auto _binding_value_42 = parseConnectedIOSDevices(rawJson);
    if (doof::is_failure(_binding_value_42)) {
        const auto error = doof::failure_error(_binding_value_42);
        return doof::Failure<std::string>{ error };
    }
    const auto devices = doof::success_value(_binding_value_42);
    if (::doof_fs::exists(devicesPath)) {
        [&]() -> void { auto _try_value = ::doof_fs::remove(devicesPath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 543, std::string("try! failed"));  }();
    }
    return selectIOSDeviceIdentifier(std::string(""), devices);
}
void collectNestedIOSCode(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results) {
    if (!::doof_fs::exists(path)) {
        return;
    }
    if (::doof_fs::isDirectory(path)) {
        if (doof::string_endsWith(path, std::string(".framework")) || doof::string_endsWith(path, std::string(".appex"))) {
            results->push_back(path);
            return;
        }
        const auto& _iterable_44 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 551, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_44) {
            collectNestedIOSCode(devicePath(path, entry->name), results);
        }
        return;
    }
    if (doof::string_endsWith(path, std::string(".dylib")) || doof::string_endsWith(path, std::string(".so"))) {
        results->push_back(path);
    }
}
doof::Result<void, std::string> signIOSDeviceApp(const std::string& appPath, const std::string& bundleId, const std::shared_ptr<IOSDeviceSigningOptions>& options, const std::string& workDirectory) {
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("iOS device signing is only supported on macOS") };
    }
    if (!::doof_fs::exists(options->provisioningProfilePath)) {
        return doof::Failure<std::string>{ (std::string("Provisioning profile not found: ") + options->provisioningProfilePath) };
    }
    removeTree(workDirectory);
    ensureDirectory(workDirectory);
    const auto decodedPath = devicePath(workDirectory, std::string("profile.plist"));
    const auto entitlementsPath = devicePath(workDirectory, std::string("entitlements.plist"));
    auto _try_value_45 = decodeProvisioningProfile(options->provisioningProfilePath, decodedPath);
    if (doof::is_failure(_try_value_45)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_45))};
    auto _try_value_46 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements.application-identifier"), std::string("raw"), std::string("-o"), std::string("-"), decodedPath}), std::string("reading provisioning profile application identifier"));
    if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_46))};
    const auto applicationIdentifier = doof::success_value(_try_value_46);
    if (!profileMatchesBundleId(applicationIdentifier, bundleId)) {
        removeTree(workDirectory);
        return doof::Failure<std::string>{ ((((std::string("Provisioning profile application-identifier \"") + applicationIdentifier) + std::string("\" does not match bundle id \"")) + bundleId) + std::string("\"")) };
    }
    auto _try_value_47 = deviceCommandText(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("Entitlements"), std::string("xml1"), std::string("-o"), entitlementsPath, decodedPath}), std::string("extracting iOS signing entitlements"));
    if (doof::is_failure(_try_value_47)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_47))};
    const auto ignored = doof::success_value(_try_value_47);
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(devicePath(appPath, std::string("embedded.mobileprovision")), [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(options->provisioningProfilePath); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 588, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }()); if (doof::is_failure(_try_value)) doof::panic_at("src/ios-device", 588, std::string("try! failed"));  }();
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    collectNestedIOSCode(devicePath(appPath, std::string("Frameworks")), nested);
    collectNestedIOSCode(devicePath(appPath, std::string("PlugIns")), nested);
    const auto& _iterable_50 = nested;
    for (const auto& path : *_iterable_50) {
        auto _try_value_48 = deviceCommandText(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(path, options->signIdentity, std::string("")), std::string("signing nested iOS code"));
        if (doof::is_failure(_try_value_48)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_48))};
        const auto nestedIgnored = doof::success_value(_try_value_48);
    }
    auto _try_value_51 = deviceCommandText(std::string("codesign"), ::app_src_ios_app_::iosCodesignArguments(appPath, options->signIdentity, entitlementsPath), std::string("signing the iOS app"));
    if (doof::is_failure(_try_value_51)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_51))};
    const auto appIgnored = doof::success_value(_try_value_51);
    removeTree(workDirectory);
    return doof::Success<void>{};
}
}
