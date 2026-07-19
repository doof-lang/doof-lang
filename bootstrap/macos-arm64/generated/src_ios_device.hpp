#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::os::index { struct ExecOptions; }
namespace std_::time::temporal { struct Instant; }
namespace std_::blob::index { struct BlobReader; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_ios_device_ {
    struct IOSDevice;
    struct IOSCodesignIdentity;
    struct IOSProvisioningProfile;
    struct IOSDeviceSigningOptions;
    struct IOSDeviceCommandResult;
}

#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "std_time_index.hpp"
#include "src_ios_app.hpp"
#include "std_blob_index.hpp"

namespace app_src_ios_device_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct IOSDevice : public std::enable_shared_from_this<IOSDevice> {
    std::string identifier;
    std::string name;
    IOSDevice(std::string identifier, std::string name) : identifier(identifier), name(name) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSDevice>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct IOSCodesignIdentity : public std::enable_shared_from_this<IOSCodesignIdentity> {
    std::string fingerprint;
    std::string name;
    IOSCodesignIdentity(std::string fingerprint, std::string name) : fingerprint(fingerprint), name(name) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSCodesignIdentity>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct IOSProvisioningProfile : public std::enable_shared_from_this<IOSProvisioningProfile> {
    std::string profilePath;
    std::string applicationIdentifier;
    std::shared_ptr<std::vector<std::string>> certFingerprints = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    int64_t expirationEpochMs;
    int32_t provisionedDeviceCount = 0;
    bool provisionsAllDevices = false;
    bool getTaskAllow = false;
    IOSProvisioningProfile(std::string profilePath, std::string applicationIdentifier, std::shared_ptr<std::vector<std::string>> certFingerprints, int64_t expirationEpochMs, int32_t provisionedDeviceCount = 0, bool provisionsAllDevices = false, bool getTaskAllow = false) : profilePath(profilePath), applicationIdentifier(applicationIdentifier), certFingerprints(certFingerprints), expirationEpochMs(expirationEpochMs), provisionedDeviceCount(provisionedDeviceCount), provisionsAllDevices(provisionsAllDevices), getTaskAllow(getTaskAllow) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct IOSDeviceSigningOptions : public std::enable_shared_from_this<IOSDeviceSigningOptions> {
    std::string signIdentity;
    std::string provisioningProfilePath;
    IOSDeviceSigningOptions(std::string signIdentity, std::string provisioningProfilePath) : signIdentity(signIdentity), provisioningProfilePath(provisioningProfilePath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSDeviceSigningOptions>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct IOSDeviceCommandResult : public std::enable_shared_from_this<IOSDeviceCommandResult> {
    int32_t exitCode;
    std::string output = std::string("");
    std::string error = std::string("");
    IOSDeviceCommandResult(int32_t exitCode, std::string output = std::string(""), std::string error = std::string("")) : exitCode(exitCode), output(output), error(error) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSDeviceCommandResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::variant<std::monostate, doof::JsonValue> jsonObjectField(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name);
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> jsonObjectValue(std::variant<std::monostate, doof::JsonValue> value);
    std::shared_ptr<std::vector<doof::JsonValue>> jsonArrayValue(std::variant<std::monostate, doof::JsonValue> value);
    std::string jsonStringValue(std::variant<std::monostate, doof::JsonValue> value);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>, std::string> parseConnectedIOSDevices(std::string rawJson);
    doof::Result<std::string, std::string> selectIOSDeviceIdentifier(std::string overrideIdentifier, std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>> devices);
    bool isHexFingerprint(std::string value);
    std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> parseCodesignIdentities(std::string output);
    std::string provisionedBundleId(std::string applicationIdentifier);
    bool profileMatchesBundleId(std::string applicationIdentifier, std::string bundleId);
    int32_t provisioningSpecificity(std::string applicationIdentifier, std::string bundleId);
    bool betterProvisioningProfile(std::shared_ptr<IOSProvisioningProfile> candidate, std::shared_ptr<IOSProvisioningProfile> current, std::string bundleId, int64_t nowEpochMs);
    doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> selectProvisioningProfile(std::string bundleId, std::shared_ptr<std::vector<std::shared_ptr<IOSProvisioningProfile>>> profiles, int64_t nowEpochMs);
    doof::Result<std::string, std::string> selectSigningIdentity(std::shared_ptr<IOSProvisioningProfile> profile, std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities);
    doof::Result<std::string, std::string> resolveIOSAdHocSigningIdentity(std::shared_ptr<IOSProvisioningProfile> profile, std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities, std::string configuredIdentity);
    doof::Result<void, std::string> validateIOSAdHocSigning(std::shared_ptr<IOSProvisioningProfile> profile, std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> identities, std::string identityName, std::string bundleId, int64_t nowEpochMs);
    std::string hostPlatform();
    std::string devicePath(std::string directory, std::string name);
    void ensureDirectory(std::string path);
    void removeTree(std::string path);
    std::shared_ptr<IOSDeviceCommandResult> runDeviceCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments);
    doof::Result<std::string, std::string> deviceCommandText(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string description);
    doof::Result<void, std::string> decodeProvisioningProfile(std::string profilePath, std::string decodedPath);
    std::string resolveUserPath(std::string path);
    void appendUnique(std::shared_ptr<std::vector<std::string>> values, std::string value);
    doof::Result<std::string, std::string> certificateFingerprint(std::string certificateData);
    doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> parseProvisioningProfile(std::string profilePath, std::string workDirectory);
    std::shared_ptr<std::vector<std::string>> collectProvisioningProfilePaths(std::shared_ptr<std::vector<std::string>> profileDirectories);
    doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> autoResolveProvisioningProfile(std::string bundleId, std::string workDirectory, std::shared_ptr<std::vector<std::string>> profileDirectories);
    doof::Result<std::shared_ptr<IOSDeviceSigningOptions>, std::string> resolveIOSDeviceSigningOptions(std::string bundleId, std::string signIdentityOverride, std::string provisioningProfileOverride, std::string workDirectory, std::shared_ptr<std::vector<std::string>> profileDirectories = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    doof::Result<std::string, std::string> resolveIOSDeviceIdentifier(std::string overrideIdentifier, std::string workDirectory);
    void collectNestedIOSCode(std::string path, std::shared_ptr<std::vector<std::string>> results);
    doof::Result<void, std::string> signIOSDeviceApp(std::string appPath, std::string bundleId, std::shared_ptr<IOSDeviceSigningOptions> options, std::string workDirectory);
}

namespace app_src_ios_device_ {
}
