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
namespace app_src_ios_app_ { struct IOSAppConfig; }
namespace app_src_ios_app_ { struct IOSPackageConfig; }
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace std_::blob::index { struct BlobReader; }
namespace std_::os::index { struct ExecOptions; }
namespace std_::time::temporal { struct Instant; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_ios_app_driver_ {
    struct IOSCommandResult;
}

#include "src_ios_app.hpp"
#include "src_ios_device.hpp"
#include "src_package_manifest.hpp"
#include "std_blob_index.hpp"
#include "std_fs_index.hpp"
#include "std_os_index.hpp"
#include "std_parse_index.hpp"
#include "std_path_index.hpp"
#include "std_time_index.hpp"

namespace app_src_ios_app_driver_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct IOSCommandResult : public std::enable_shared_from_this<IOSCommandResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    std::string error = std::string("");
    IOSCommandResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), std::string error = std::string("")) : exitCode(exitCode), output(output), error(error) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<IOSCommandResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string outputPath(const std::string& directory, const std::string& name);
    std::string parentPath(const std::string& path);
    std::string fileName(const std::string& path);
    std::string hostPlatform();
    std::shared_ptr<IOSCommandResult> runIOSCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments);
    doof::Result<std::string, std::string> commandText(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description);
    doof::Result<void, std::string> runRequiredCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description);
    void ensureDirectory(const std::string& path);
    void copyPath(const std::string& sourcePath, const std::string& destinationPath);
    void removeTree(const std::string& path);
    void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value);
    doof::Result<void, std::string> configureIOSNativeBuild(const std::string& outputDirectory, const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& destination, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native);
    std::string globBaseDirectory(const std::string& pattern);
    bool globMatches(const std::string& pattern, const std::string& value, int32_t patternIndex = 0, int32_t valueIndex = 0);
    void collectResourceFiles(const std::string& path, const std::string& baseDirectory, const std::string& pattern, const std::shared_ptr<std::vector<std::string>>& results);
    doof::Result<void, std::string> copyIOSResources(const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& appPath);
    doof::Result<void, std::string> compileIOSIcon(const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& appPath, const std::string& destination, const std::string& buildDirectory);
    doof::Result<std::string, std::string> assembleIOSApp(const std::string& buildDirectory, const std::string& executablePath, const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& destination = std::string("simulator"));
    void collectNestedCode(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results);
    doof::Result<void, std::string> signAndArchiveIOSApp(const std::string& appPath, const std::string& archivePath, const std::string& bundleId, const std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>& config, const std::string& buildDirectory);
}

namespace app_src_ios_app_driver_ {
}
