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
    extern int64_t MAX_IOS_DEVICE_COMMAND_OUTPUT_BYTES;
}

#include "std_crypto_index.hpp"
#include "std_fs_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_parse_index.hpp"
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
    std::variant<std::monostate, doof::JsonValue> jsonObjectField(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name);
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> jsonObjectValue(const std::variant<std::monostate, doof::JsonValue>& value);
    std::shared_ptr<std::vector<doof::JsonValue>> jsonArrayValue(const std::variant<std::monostate, doof::JsonValue>& value);
    std::string jsonStringValue(const std::variant<std::monostate, doof::JsonValue>& value);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>, std::string> parseConnectedIOSDevices(const std::string& rawJson);
    doof::Result<std::string, std::string> selectIOSDeviceIdentifier(const std::string& overrideIdentifier, const std::shared_ptr<std::vector<std::shared_ptr<IOSDevice>>>& devices);
    bool isHexFingerprint(const std::string& value);
    std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>> parseCodesignIdentities(const std::string& output);
    std::string provisionedBundleId(const std::string& applicationIdentifier);
    bool profileMatchesBundleId(const std::string& applicationIdentifier, const std::string& bundleId);
    int32_t provisioningSpecificity(const std::string& applicationIdentifier, const std::string& bundleId);
    bool betterProvisioningProfile(const std::shared_ptr<IOSProvisioningProfile>& candidate, const std::shared_ptr<IOSProvisioningProfile>& current, const std::string& bundleId, int64_t nowEpochMs);
    doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> selectProvisioningProfile(const std::string& bundleId, const std::shared_ptr<std::vector<std::shared_ptr<IOSProvisioningProfile>>>& profiles, int64_t nowEpochMs);
    doof::Result<std::string, std::string> selectSigningIdentity(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities);
    doof::Result<std::string, std::string> resolveIOSAdHocSigningIdentity(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities, const std::string& configuredIdentity);
    doof::Result<void, std::string> validateIOSAdHocSigning(const std::shared_ptr<IOSProvisioningProfile>& profile, const std::shared_ptr<std::vector<std::shared_ptr<IOSCodesignIdentity>>>& identities, const std::string& identityName, const std::string& bundleId, int64_t nowEpochMs);
    std::string hostPlatform();
    std::string devicePath(const std::string& directory, const std::string& name);
    void ensureDirectory(const std::string& path);
    void removeTree(const std::string& path);
    std::shared_ptr<IOSDeviceCommandResult> runDeviceCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments);
    doof::Result<std::string, std::string> deviceCommandText(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description);
    doof::Result<void, std::string> decodeProvisioningProfile(const std::string& profilePath, const std::string& decodedPath);
    std::string resolveUserPath(const std::string& path);
    void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value);
    doof::Result<std::string, std::string> certificateFingerprint(const std::string& certificateData);
    doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> parseProvisioningProfile(const std::string& profilePath, const std::string& workDirectory);
    std::shared_ptr<std::vector<std::string>> collectProvisioningProfilePaths(const std::shared_ptr<std::vector<std::string>>& profileDirectories);
    doof::Result<std::shared_ptr<IOSProvisioningProfile>, std::string> autoResolveProvisioningProfile(const std::string& bundleId, const std::string& workDirectory, const std::shared_ptr<std::vector<std::string>>& profileDirectories);
    doof::Result<std::shared_ptr<IOSDeviceSigningOptions>, std::string> resolveIOSDeviceSigningOptions(const std::string& bundleId, const std::string& signIdentityOverride, const std::string& provisioningProfileOverride, const std::string& workDirectory, const std::shared_ptr<std::vector<std::string>>& profileDirectories = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    doof::Result<std::string, std::string> resolveIOSDeviceIdentifier(const std::string& overrideIdentifier, const std::string& workDirectory);
    void collectNestedIOSCode(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results);
    doof::Result<void, std::string> signIOSDeviceApp(const std::string& appPath, const std::string& bundleId, const std::shared_ptr<IOSDeviceSigningOptions>& options, const std::string& workDirectory);
}

namespace app_src_ios_device_ {
}
