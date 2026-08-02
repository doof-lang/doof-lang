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
namespace app_src_macos_app_ { struct MacOSAppConfig; }
namespace app_src_macos_app_ { struct MacOSPackageConfig; }
namespace std_::blob::index { struct BlobReader; }
namespace std_::os::index { struct ExecOptions; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_macos_app_driver_ {
    struct MacOSCommandResult;
    struct EmbeddedCode;
}

#include "src_macos_app.hpp"
#include "std_blob_index.hpp"
#include "std_fs_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"

namespace app_src_macos_app_driver_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct MacOSCommandResult : public std::enable_shared_from_this<MacOSCommandResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    std::string error = std::string("");
    MacOSCommandResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), std::string error = std::string("")) : exitCode(exitCode), output(output), error(error) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSCommandResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct EmbeddedCode : public std::enable_shared_from_this<EmbeddedCode> {
    std::string sourcePath;
    std::string bundledRoot;
    std::string bundledPath;
    std::string bundleReference;
    std::string installId = std::string("");
    EmbeddedCode(std::string sourcePath, std::string bundledRoot, std::string bundledPath, std::string bundleReference, std::string installId = std::string("")) : sourcePath(sourcePath), bundledRoot(bundledRoot), bundledPath(bundledPath), bundleReference(bundleReference), installId(installId) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<EmbeddedCode>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string hostPlatform();
    std::string outputPath(const std::string& directory, const std::string& name);
    std::string parentPath(const std::string& path);
    std::string fileName(const std::string& path);
    std::shared_ptr<MacOSCommandResult> runMacOSCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments);
    void ensureDirectory(const std::string& path);
    void copyPath(const std::string& sourcePath, const std::string& destinationPath);
    void removeTree(const std::string& path);
    std::string globBaseDirectory(const std::string& pattern);
    bool globMatches(const std::string& pattern, const std::string& value, int32_t patternIndex = 0, int32_t valueIndex = 0);
    void collectResourceFiles(const std::string& path, const std::string& baseDirectory, const std::string& pattern, const std::shared_ptr<std::vector<std::string>>& results);
    void materializeMacOSResources(const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::string& resourcesDirectory);
    doof::Result<void, std::string> runRequiredCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description);
    doof::Result<void, std::string> generateMacOSIcon(const std::string& iconPath, const std::string& destinationPath, const std::string& workRoot);
    doof::Result<std::string, std::string> commandText(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description);
    doof::Result<std::string, std::string> resolveEmbeddedLibrary(const std::string& name, const std::shared_ptr<std::vector<std::string>>& libraryPaths, const std::string& buildDirectory);
    std::string firstNonemptyOutputLine(const std::string& output);
    doof::Result<std::string, std::string> readMachOInstallId(const std::string& path);
    doof::Result<std::string, std::string> frameworkBinary(const std::string& frameworkPath);
    std::string frameworkReference(const std::string& frameworkName, const std::string& installId, const std::string& bundledBinary, const std::string& bundledRoot);
    doof::Result<std::shared_ptr<EmbeddedCode>, std::string> planEmbeddedCode(const std::string& sourcePath, const std::string& frameworksDirectory);
    doof::Result<std::shared_ptr<std::vector<std::string>>, std::string> machODependencies(const std::string& path);
    bool isSystemMachODependency(const std::string& path);
    std::shared_ptr<EmbeddedCode> embeddedDependency(const std::string& dependency, const std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>>& embedded);
    doof::Result<void, std::string> rewriteEmbeddedDependencies(const std::string& codePath, const std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>>& embedded);
    doof::Result<void, std::string> ensureMachORPath(const std::string& codePath, const std::string& rpath);
    doof::Result<void, std::string> embedMacOSLibraries(const std::string& executablePath, const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::shared_ptr<std::vector<std::string>>& libraryPaths, const std::string& buildDirectory, const std::string& contentsDirectory);
    void collectNestedMacOSCode(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results);
    doof::Result<std::string, std::string> assembleMacOSApp(const std::string& buildDirectory, const std::string& executablePath, const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::shared_ptr<std::vector<std::string>>& libraryPaths);
    doof::Result<std::string, std::string> developerIdIdentity(const std::string& configured);
    doof::Result<std::string, std::string> effectiveEntitlements(const std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>& config, const std::string& buildDirectory);
    doof::Result<void, std::string> signAndArchiveMacOSApp(const std::string& appPath, const std::string& archivePath, const std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>& config, const std::string& buildDirectory);
}

namespace app_src_macos_app_driver_ {
}
