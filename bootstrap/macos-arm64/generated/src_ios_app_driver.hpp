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
    std::string outputPath(std::string directory, std::string name);
    std::string parentPath(std::string path);
    std::string fileName(std::string path);
    std::string hostPlatform();
    std::shared_ptr<IOSCommandResult> runIOSCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments);
    doof::Result<std::string, std::string> commandText(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string description);
    doof::Result<void, std::string> runRequiredCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string description);
    void ensureDirectory(std::string path);
    void copyPath(std::string sourcePath, std::string destinationPath);
    void removeTree(std::string path);
    void appendUnique(std::shared_ptr<std::vector<std::string>> values, std::string value);
    doof::Result<void, std::string> configureIOSNativeBuild(std::string outputDirectory, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> config, std::string destination, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> native);
    std::string globBaseDirectory(std::string pattern);
    bool globMatches(std::string pattern, std::string value, int32_t patternIndex = 0, int32_t valueIndex = 0);
    void collectResourceFiles(std::string path, std::string baseDirectory, std::string pattern, std::shared_ptr<std::vector<std::string>> results);
    doof::Result<void, std::string> copyIOSResources(std::shared_ptr<::app_src_ios_app_::IOSAppConfig> config, std::string appPath);
    doof::Result<void, std::string> compileIOSIcon(std::shared_ptr<::app_src_ios_app_::IOSAppConfig> config, std::string appPath, std::string destination, std::string buildDirectory);
    doof::Result<std::string, std::string> assembleIOSApp(std::string buildDirectory, std::string executablePath, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> config, std::string destination = std::string("simulator"));
    void collectNestedCode(std::string path, std::shared_ptr<std::vector<std::string>> results);
    doof::Result<void, std::string> signAndArchiveIOSApp(std::string appPath, std::string archivePath, std::string bundleId, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> config, std::string buildDirectory);
}

namespace app_src_ios_app_driver_ {
}
