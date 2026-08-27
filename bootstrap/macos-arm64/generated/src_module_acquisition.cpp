#include "src_module_acquisition.hpp"

namespace app_src_module_acquisition_ {

std::shared_ptr<ModuleAcquisition> acquiredPackageForModule(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions) {
    const auto selected = selectedAcquisition(logicalPath, acquisitions);
    if (doof::is_null(selected)) {
        return nullptr;
    }
    auto suffix = doof::string_substring(logicalPath, static_cast<int32_t>(selected->logicalPrefix.size()), static_cast<int32_t>(logicalPath.size()));
    while (doof::string_startsWith(suffix, std::string("/"))) {
        (suffix = doof::string_substring(suffix, 1, static_cast<int32_t>(suffix.size())));
    }
    if (suffix == std::string("")) {
        return selected;
    }
    auto separator = -1;
    auto index = 0;
    while (index < static_cast<int32_t>(suffix.size())) {
        if (doof::string_at(suffix, index, "src/module-acquisition", 26) == U'\u002F') {
            (separator = index);
            break;
        }
        (index = (index + 1));
    }
    if (separator < 0) {
        return selected;
    }
    const auto packageName = doof::string_substring(suffix, 0, separator);
    if (packageName == std::string("")) {
        return selected;
    }
    return std::make_shared<ModuleAcquisition>(acquisitionJoinPath(selected->logicalPrefix, packageName), acquisitionJoinPath(selected->diskRoot, packageName));
}
std::optional<std::string> acquiredModuleDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions) {
    const auto selected = selectedAcquisition(logicalPath, acquisitions);
    if (doof::is_null(selected)) {
        return std::nullopt;
    }
    auto suffix = doof::string_substring(logicalPath, static_cast<int32_t>(selected->logicalPrefix.size()), static_cast<int32_t>(logicalPath.size()));
    if (doof::string_startsWith(suffix, std::string("/"))) {
        (suffix = doof::string_substring(suffix, 1, static_cast<int32_t>(suffix.size())));
    }
    return acquisitionJoinPath(selected->diskRoot, suffix);
}
std::string acquiredManifestPath(const std::shared_ptr<ModuleAcquisition>& acquisition) {
    return acquisitionJoinPath(acquisition->diskRoot, std::string("doof.json"));
}
bool acquisitionMatches(const std::string& prefix, const std::string& logicalPath) {
    return ((logicalPath == prefix) || doof::string_startsWith(logicalPath, (prefix + std::string("/"))));
}
std::shared_ptr<ModuleAcquisition> selectedAcquisition(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions) {
    std::shared_ptr<ModuleAcquisition> selected = nullptr;
    const auto& _iterable_2 = acquisitions;
    for (const auto& acquisition : *_iterable_2) {
        if (acquisitionMatches(acquisition->logicalPrefix, logicalPath)) {
            if (doof::is_null(selected) || (static_cast<int32_t>(acquisition->logicalPrefix.size()) > static_cast<int32_t>(selected->logicalPrefix.size()))) {
                (selected = acquisition);
            }
        }
    }
    return selected;
}
std::string acquisitionJoinPath(const std::string& directory, const std::string& suffix) {
    if (suffix == std::string("")) {
        return directory;
    }
    if (doof::string_endsWith(directory, std::string("/"))) {
        return (directory + suffix);
    }
    return ((directory + std::string("/")) + suffix);
}
}
