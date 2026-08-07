#pragma once
#include "doof_runtime.hpp"
namespace app_src_module_acquisition_ {
    struct ModuleAcquisition;
}

namespace app_src_module_acquisition_ {
    struct ModuleAcquisition : public std::enable_shared_from_this<ModuleAcquisition> {
    std::string logicalPrefix;
    std::string diskRoot;
    ModuleAcquisition(std::string logicalPrefix, std::string diskRoot) : logicalPrefix(logicalPrefix), diskRoot(diskRoot) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ModuleAcquisition>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_module_acquisition_ {
    std::shared_ptr<ModuleAcquisition> acquiredPackageForModule(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions);
    std::optional<std::string> acquiredModuleDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions);
    std::string acquiredManifestPath(const std::shared_ptr<ModuleAcquisition>& acquisition);
    bool acquisitionMatches(const std::string& prefix, const std::string& logicalPath);
    std::shared_ptr<ModuleAcquisition> selectedAcquisition(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions);
    std::string acquisitionJoinPath(const std::string& directory, const std::string& suffix);
}
