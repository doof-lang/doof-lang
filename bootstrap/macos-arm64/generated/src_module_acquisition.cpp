#include "src_module_acquisition.hpp"

namespace app_src_module_acquisition_ {

#line 15 "/src/module-acquisition.do"
std::shared_ptr<ModuleAcquisition> acquiredPackageForModule(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions) {
#line 16 "/src/module-acquisition.do"
    const auto selected = selectedAcquisition(logicalPath, acquisitions);
#line 17 "/src/module-acquisition.do"
    if (doof::is_null(selected)) {
#line 17 "/src/module-acquisition.do"
        return nullptr;
    }
#line 19 "/src/module-acquisition.do"
    auto suffix = doof::string_substring(logicalPath, static_cast<int32_t>(selected->logicalPrefix.size()), static_cast<int32_t>(logicalPath.size()));
#line 20 "/src/module-acquisition.do"
    while (doof::string_startsWith(suffix, std::string("/"))) {
#line 20 "/src/module-acquisition.do"
        (suffix = doof::string_substring(suffix, 1, static_cast<int32_t>(suffix.size())));
    }
#line 21 "/src/module-acquisition.do"
    if (suffix == std::string("")) {
#line 21 "/src/module-acquisition.do"
        return selected;
    }
#line 23 "/src/module-acquisition.do"
    auto separator = -1;
#line 24 "/src/module-acquisition.do"
    auto index = 0;
#line 25 "/src/module-acquisition.do"
    while (index < static_cast<int32_t>(suffix.size())) {
#line 26 "/src/module-acquisition.do"
        if (doof::string_at(suffix, index, "src/module-acquisition", 26) == U'\u002F') {
#line 27 "/src/module-acquisition.do"
            (separator = index);
#line 28 "/src/module-acquisition.do"
            break;
        }
#line 30 "/src/module-acquisition.do"
        (index = (index + 1));
    }
#line 32 "/src/module-acquisition.do"
    if (separator < 0) {
#line 32 "/src/module-acquisition.do"
        return selected;
    }
#line 33 "/src/module-acquisition.do"
    const auto packageName = doof::string_substring(suffix, 0, separator);
#line 34 "/src/module-acquisition.do"
    if (packageName == std::string("")) {
#line 34 "/src/module-acquisition.do"
        return selected;
    }
#line 35 "/src/module-acquisition.do"
    return std::make_shared<ModuleAcquisition>(acquisitionJoinPath(selected->logicalPrefix, packageName), acquisitionJoinPath(selected->diskRoot, packageName));
}
#line 42 "/src/module-acquisition.do"
std::optional<std::string> acquiredModuleDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions) {
#line 43 "/src/module-acquisition.do"
    const auto selected = selectedAcquisition(logicalPath, acquisitions);
#line 44 "/src/module-acquisition.do"
    if (doof::is_null(selected)) {
#line 44 "/src/module-acquisition.do"
        return std::nullopt;
    }
#line 46 "/src/module-acquisition.do"
    auto suffix = doof::string_substring(logicalPath, static_cast<int32_t>(selected->logicalPrefix.size()), static_cast<int32_t>(logicalPath.size()));
#line 47 "/src/module-acquisition.do"
    if (doof::string_startsWith(suffix, std::string("/"))) {
#line 47 "/src/module-acquisition.do"
        (suffix = doof::string_substring(suffix, 1, static_cast<int32_t>(suffix.size())));
    }
#line 48 "/src/module-acquisition.do"
    return acquisitionJoinPath(selected->diskRoot, suffix);
}
#line 52 "/src/module-acquisition.do"
std::string acquiredManifestPath(const std::shared_ptr<ModuleAcquisition>& acquisition) {
#line 53 "/src/module-acquisition.do"
    return acquisitionJoinPath(acquisition->diskRoot, std::string("doof.json"));
}
#line 56 "/src/module-acquisition.do"
bool acquisitionMatches(const std::string& prefix, const std::string& logicalPath) {
#line 57 "/src/module-acquisition.do"
    return ((logicalPath == prefix) || doof::string_startsWith(logicalPath, (prefix + std::string("/"))));
}
#line 60 "/src/module-acquisition.do"
std::shared_ptr<ModuleAcquisition> selectedAcquisition(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions) {
#line 61 "/src/module-acquisition.do"
    std::shared_ptr<ModuleAcquisition> selected = nullptr;
#line 62 "/src/module-acquisition.do"
    const auto& _iterable_2 = acquisitions;
    for (const auto& acquisition : *_iterable_2) {
#line 63 "/src/module-acquisition.do"
        if (acquisitionMatches(acquisition->logicalPrefix, logicalPath)) {
#line 64 "/src/module-acquisition.do"
            if (doof::is_null(selected) || (static_cast<int32_t>(acquisition->logicalPrefix.size()) > static_cast<int32_t>(selected->logicalPrefix.size()))) {
#line 65 "/src/module-acquisition.do"
                (selected = acquisition);
            }
        }
    }
#line 69 "/src/module-acquisition.do"
    return selected;
}
#line 72 "/src/module-acquisition.do"
std::string acquisitionJoinPath(const std::string& directory, const std::string& suffix) {
#line 73 "/src/module-acquisition.do"
    if (suffix == std::string("")) {
#line 73 "/src/module-acquisition.do"
        return directory;
    }
#line 74 "/src/module-acquisition.do"
    if (doof::string_endsWith(directory, std::string("/"))) {
#line 74 "/src/module-acquisition.do"
        return (directory + suffix);
    }
#line 75 "/src/module-acquisition.do"
    return ((directory + std::string("/")) + suffix);
}
#line 1 "<doof-generated>"
}
