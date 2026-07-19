#include "src_module_acquisition.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_module_acquisition_ {

doof::JsonObject ModuleAcquisition::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["logicalPrefix"] = doof::json_value(this->logicalPrefix);
    (*_json)["diskRoot"] = doof::json_value(this->diskRoot);
    return _json;
}
doof::Result<std::shared_ptr<ModuleAcquisition>, std::string> ModuleAcquisition::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_logicalPrefix = _object->find("logicalPrefix");
    if (_iterator_logicalPrefix == _object->end()) { return doof::Failure<std::string>{"Missing required field \"logicalPrefix\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_logicalPrefix->second) : doof::json_is_string(_iterator_logicalPrefix->second)))) { return doof::Failure<std::string>{"Field \"logicalPrefix\" expected string but got " + std::string(doof::json_type_name(_iterator_logicalPrefix->second))}; }
    auto _field_logicalPrefix = (_lenient ? doof::json_as_string_lenient(_iterator_logicalPrefix->second) : doof::json_as_string(_iterator_logicalPrefix->second));
    auto _iterator_diskRoot = _object->find("diskRoot");
    if (_iterator_diskRoot == _object->end()) { return doof::Failure<std::string>{"Missing required field \"diskRoot\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_diskRoot->second) : doof::json_is_string(_iterator_diskRoot->second)))) { return doof::Failure<std::string>{"Field \"diskRoot\" expected string but got " + std::string(doof::json_type_name(_iterator_diskRoot->second))}; }
    auto _field_diskRoot = (_lenient ? doof::json_as_string_lenient(_iterator_diskRoot->second) : doof::json_as_string(_iterator_diskRoot->second));
    return doof::Success<std::shared_ptr<ModuleAcquisition>>{std::make_shared<ModuleAcquisition>(_field_logicalPrefix, _field_diskRoot)};
}
std::shared_ptr<ModuleAcquisition> acquiredPackageForModule(std::string logicalPath, std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>> acquisitions) {
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
        if (suffix[index] == U'\u002F') {
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
std::optional<std::string> acquiredModuleDiskPath(std::string logicalPath, std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>> acquisitions) {
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
std::string acquiredManifestPath(std::shared_ptr<ModuleAcquisition> acquisition) {
    return acquisitionJoinPath(acquisition->diskRoot, std::string("doof.json"));
}
bool acquisitionMatches(std::string prefix, std::string logicalPath) {
    return ((logicalPath == prefix) || doof::string_startsWith(logicalPath, (prefix + std::string("/"))));
}
std::shared_ptr<ModuleAcquisition> selectedAcquisition(std::string logicalPath, std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>> acquisitions) {
    std::shared_ptr<ModuleAcquisition> selected = nullptr;
    const auto& _iterable_1 = acquisitions;
    for (const auto& acquisition : *_iterable_1) {
        if (acquisitionMatches(acquisition->logicalPrefix, logicalPath)) {
            if (doof::is_null(selected) || (static_cast<int32_t>(acquisition->logicalPrefix.size()) > static_cast<int32_t>(selected->logicalPrefix.size()))) {
                (selected = acquisition);
            }
        }
    }
    return selected;
}
std::string acquisitionJoinPath(std::string directory, std::string suffix) {
    if (suffix == std::string("")) {
        return directory;
    }
    if (doof::string_endsWith(directory, std::string("/"))) {
        return (directory + suffix);
    }
    return ((directory + std::string("/")) + suffix);
}
}
