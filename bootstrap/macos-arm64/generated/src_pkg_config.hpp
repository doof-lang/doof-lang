#pragma once
#include "doof_runtime.hpp"
namespace app_src_package_manifest_ {
    struct NativeBuildPlan;
}

namespace app_src_pkg_config_ {
    struct PkgConfigCommandResult;
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan : public std::enable_shared_from_this<NativeBuildPlan> {
    std::shared_ptr<std::vector<std::string>> includePaths;
    std::shared_ptr<std::vector<std::string>> sourceFiles;
    std::shared_ptr<std::vector<std::string>> libraryPaths;
    std::shared_ptr<std::vector<std::string>> extraCopyPaths;
    std::shared_ptr<std::vector<std::string>> linkLibraries;
    std::shared_ptr<std::vector<std::string>> frameworks;
    std::shared_ptr<std::vector<std::string>> pkgConfigPackages;
    std::shared_ptr<std::vector<std::string>> defines;
    std::shared_ptr<std::vector<std::string>> compilerFlags;
    std::shared_ptr<std::vector<std::string>> linkerFlags;
    NativeBuildPlan(std::shared_ptr<std::vector<std::string>> includePaths, std::shared_ptr<std::vector<std::string>> sourceFiles, std::shared_ptr<std::vector<std::string>> libraryPaths, std::shared_ptr<std::vector<std::string>> extraCopyPaths, std::shared_ptr<std::vector<std::string>> linkLibraries, std::shared_ptr<std::vector<std::string>> frameworks, std::shared_ptr<std::vector<std::string>> pkgConfigPackages, std::shared_ptr<std::vector<std::string>> defines, std::shared_ptr<std::vector<std::string>> compilerFlags, std::shared_ptr<std::vector<std::string>> linkerFlags) : includePaths(includePaths), sourceFiles(sourceFiles), libraryPaths(libraryPaths), extraCopyPaths(extraCopyPaths), linkLibraries(linkLibraries), frameworks(frameworks), pkgConfigPackages(pkgConfigPackages), defines(defines), compilerFlags(compilerFlags), linkerFlags(linkerFlags) {}
};
}

namespace app_src_pkg_config_ {
    struct PkgConfigCommandResult : public std::enable_shared_from_this<PkgConfigCommandResult> {
    int32_t exitCode;
    std::string output;
    std::string error;
    PkgConfigCommandResult(int32_t exitCode, std::string output, std::string error) : exitCode(exitCode), output(output), error(error) {}
};
}

namespace app_src_pkg_config_ {
    doof::Result<void, std::string> applyPkgConfigResult(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, const std::string& packageName, const std::string& mode, const std::shared_ptr<PkgConfigCommandResult>& result);
    std::shared_ptr<std::vector<std::string>> pkgConfigTokens(const std::string& output);
    void applyPkgConfigTokens(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, const std::shared_ptr<std::vector<std::string>>& tokens, const std::string& mode);
    void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value);
}
