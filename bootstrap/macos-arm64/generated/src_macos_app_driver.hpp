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
    std::string outputPath(std::string directory, std::string name);
    std::string parentPath(std::string path);
    std::string fileName(std::string path);
    std::shared_ptr<MacOSCommandResult> runMacOSCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments);
    void ensureDirectory(std::string path);
    void copyPath(std::string sourcePath, std::string destinationPath);
    void removeTree(std::string path);
    std::string globBaseDirectory(std::string pattern);
    bool globMatches(std::string pattern, std::string value, int32_t patternIndex = 0, int32_t valueIndex = 0);
    void collectResourceFiles(std::string path, std::string baseDirectory, std::string pattern, std::shared_ptr<std::vector<std::string>> results);
    void materializeMacOSResources(std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> config, std::string resourcesDirectory);
    doof::Result<void, std::string> runRequiredCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string description);
    doof::Result<void, std::string> generateMacOSIcon(std::string iconPath, std::string destinationPath, std::string workRoot);
    doof::Result<std::string, std::string> commandText(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string description);
    doof::Result<std::string, std::string> resolveEmbeddedLibrary(std::string name, std::shared_ptr<std::vector<std::string>> libraryPaths, std::string buildDirectory);
    std::string firstNonemptyOutputLine(std::string output);
    doof::Result<std::string, std::string> readMachOInstallId(std::string path);
    doof::Result<std::string, std::string> frameworkBinary(std::string frameworkPath);
    std::string frameworkReference(std::string frameworkName, std::string installId, std::string bundledBinary, std::string bundledRoot);
    doof::Result<std::shared_ptr<EmbeddedCode>, std::string> planEmbeddedCode(std::string sourcePath, std::string frameworksDirectory);
    doof::Result<std::shared_ptr<std::vector<std::string>>, std::string> machODependencies(std::string path);
    bool isSystemMachODependency(std::string path);
    std::shared_ptr<EmbeddedCode> embeddedDependency(std::string dependency, std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>> embedded);
    doof::Result<void, std::string> rewriteEmbeddedDependencies(std::string codePath, std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>> embedded);
    doof::Result<void, std::string> ensureMachORPath(std::string codePath, std::string rpath);
    doof::Result<void, std::string> embedMacOSLibraries(std::string executablePath, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> config, std::shared_ptr<std::vector<std::string>> libraryPaths, std::string buildDirectory, std::string contentsDirectory);
    void collectNestedMacOSCode(std::string path, std::shared_ptr<std::vector<std::string>> results);
    doof::Result<std::string, std::string> assembleMacOSApp(std::string buildDirectory, std::string executablePath, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> config, std::shared_ptr<std::vector<std::string>> libraryPaths);
    doof::Result<std::string, std::string> developerIdIdentity(std::string configured);
    doof::Result<std::string, std::string> effectiveEntitlements(std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> config, std::string buildDirectory);
    doof::Result<void, std::string> signAndArchiveMacOSApp(std::string appPath, std::string archivePath, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> config, std::string buildDirectory);
}

namespace app_src_macos_app_driver_ {
}
