#include "src_emitter_names.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_names_ {

doof::JsonObject ModuleNamespaceMapping::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["logicalPrefix"] = doof::json_value(this->logicalPrefix);
    (*_json)["packageName"] = doof::json_value(this->packageName);
    (*_json)["outputRoot"] = doof::json_value(this->outputRoot);
    return _json;
}
doof::Result<std::shared_ptr<ModuleNamespaceMapping>, std::string> ModuleNamespaceMapping::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_logicalPrefix = _object->find("logicalPrefix");
    if (_iterator_logicalPrefix == _object->end()) { return doof::Failure<std::string>{"Missing required field \"logicalPrefix\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_logicalPrefix->second) : doof::json_is_string(_iterator_logicalPrefix->second)))) { return doof::Failure<std::string>{"Field \"logicalPrefix\" expected string but got " + std::string(doof::json_type_name(_iterator_logicalPrefix->second))}; }
    auto _field_logicalPrefix = (_lenient ? doof::json_as_string_lenient(_iterator_logicalPrefix->second) : doof::json_as_string(_iterator_logicalPrefix->second));
    auto _iterator_packageName = _object->find("packageName");
    if (_iterator_packageName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"packageName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_packageName->second) : doof::json_is_string(_iterator_packageName->second)))) { return doof::Failure<std::string>{"Field \"packageName\" expected string but got " + std::string(doof::json_type_name(_iterator_packageName->second))}; }
    auto _field_packageName = (_lenient ? doof::json_as_string_lenient(_iterator_packageName->second) : doof::json_as_string(_iterator_packageName->second));
    std::optional<std::string> _field_outputRoot;
    if (auto _iterator_outputRoot = _object->find("outputRoot"); _iterator_outputRoot != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_outputRoot->second) : doof::json_is_string(_iterator_outputRoot->second)))) { return doof::Failure<std::string>{"Field \"outputRoot\" expected string but got " + std::string(doof::json_type_name(_iterator_outputRoot->second))}; }
        _field_outputRoot = (_lenient ? doof::json_as_string_lenient(_iterator_outputRoot->second) : doof::json_as_string(_iterator_outputRoot->second));
    } else {
        _field_outputRoot = std::string{std::string("")};
    }
    return doof::Success<std::shared_ptr<ModuleNamespaceMapping>>{std::make_shared<ModuleNamespaceMapping>(_field_logicalPrefix, _field_packageName, _field_outputRoot.value())};
}
auto configuredModuleNamespaceMappings = std::make_shared<std::vector<std::shared_ptr<ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<ModuleNamespaceMapping>>{});
void configureModuleNamespaces(std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>> mappings) {
    (configuredModuleNamespaceMappings = mappings);
}
std::string moduleStem(std::string path) {
    auto normalized = doof::string_replaceAll(path, std::string("\\"), std::string("/"));
    const auto mapping = namespaceMappingForPath(normalized);
    if (!doof::is_null(mapping)) {
        auto relativePath = doof::string_substring(normalized, static_cast<int32_t>(mapping->logicalPrefix.size()), static_cast<int32_t>(normalized.size()));
        while (doof::string_startsWith(relativePath, std::string("/"))) {
            (relativePath = doof::string_substring(relativePath, 1, static_cast<int32_t>(relativePath.size())));
        }
        (normalized = mapping->packageName);
        if (relativePath != std::string("")) {
            (normalized = ((normalized + std::string("/")) + relativePath));
        }
    }
    const auto withoutRoot = (doof::string_startsWith(normalized, std::string("/")) ? doof::string_substring(normalized, 1, 1000000) : normalized);
    const auto result = doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(withoutRoot, std::string("/"), std::string("_")), std::string(".do"), std::string("")), std::string("-"), std::string("_")), std::string("."), std::string("_"));
    return ((result == std::string("")) ? std::string("module") : result);
}
std::string moduleNamespace(std::string path) {
    const auto mapping = namespaceMappingForPath(path);
    if (!doof::is_null(mapping)) {
        auto relativePath = doof::string_substring(path, static_cast<int32_t>(mapping->logicalPrefix.size()), static_cast<int32_t>(path.size()));
        while (doof::string_startsWith(relativePath, std::string("/"))) {
            (relativePath = doof::string_substring(relativePath, 1, static_cast<int32_t>(relativePath.size())));
        }
        if (doof::string_endsWith(relativePath, std::string(".do"))) {
            (relativePath = doof::string_substring(relativePath, 0, (static_cast<int32_t>(relativePath.size()) - 3)));
        }
        auto namespace_ = namespacePath(mapping->packageName);
        if (relativePath != std::string("")) {
            (namespace_ = ((namespace_ + std::string("::")) + namespacePath(relativePath)));
        }
        return namespace_;
    }
    return ((std::string("app_") + moduleStem(path)) + std::string("_"));
}
std::string moduleDiagnosticPath(std::string path, bool stripExtension) {
    auto normalized = doof::string_replaceAll(path, std::string("\\"), std::string("/"));
    const auto mapping = namespaceMappingForPath(normalized);
    if (!doof::is_null(mapping)) {
        (normalized = doof::string_substring(normalized, static_cast<int32_t>(mapping->logicalPrefix.size()), static_cast<int32_t>(normalized.size())));
    }
    while (doof::string_startsWith(normalized, std::string("/"))) {
        (normalized = doof::string_substring(normalized, 1, static_cast<int32_t>(normalized.size())));
    }
    if (stripExtension && doof::string_endsWith(normalized, std::string(".do"))) {
        (normalized = doof::string_substring(normalized, 0, (static_cast<int32_t>(normalized.size()) - 3)));
    }
    return ((normalized == std::string("")) ? std::string("<module>") : normalized);
}
std::string moduleNativeHeaderPath(std::string modulePath, std::string headerPath) {
    if (!doof::string_startsWith(headerPath, std::string("./")) && !doof::string_startsWith(headerPath, std::string("../"))) {
        return headerPath;
    }
    const auto mapping = namespaceMappingForPath(modulePath);
    if (doof::is_null(mapping)) {
        return headerPath;
    }
    auto relativeModulePath = doof::string_substring(modulePath, static_cast<int32_t>(mapping->logicalPrefix.size()), static_cast<int32_t>(modulePath.size()));
    while (doof::string_startsWith(relativeModulePath, std::string("/"))) {
        (relativeModulePath = doof::string_substring(relativeModulePath, 1, static_cast<int32_t>(relativeModulePath.size())));
    }
    const auto components = doof::string_split(relativeModulePath, std::string("/"));
    if (static_cast<int32_t>((components)->size()) > 0) {
        const auto ignoredModuleName = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    }
    const auto& _iterable_1 = doof::string_split(doof::string_replaceAll(headerPath, std::string("\\"), std::string("/")), std::string("/"));
    for (const auto& component : *_iterable_1) {
        if ((component == std::string("")) || (component == std::string("."))) {
            continue;
        }
        if (component == std::string("..")) {
            if (static_cast<int32_t>((components)->size()) == 0) {
                return headerPath;
            }
            const auto ignoredParent = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        } else {
            components->push_back(component);
        }
    }
    auto result = mapping->outputRoot;
    const auto& _iterable_2 = components;
    for (const auto& component : *_iterable_2) {
        if (result != std::string("")) {
            (result = (result + std::string("/")));
        }
        (result = (result + component));
    }
    return result;
}
std::shared_ptr<ModuleNamespaceMapping> namespaceMappingForPath(std::string path) {
    std::shared_ptr<ModuleNamespaceMapping> selected = nullptr;
    const auto& _iterable_3 = configuredModuleNamespaceMappings;
    for (const auto& mapping : *_iterable_3) {
        if ((path == mapping->logicalPrefix) || doof::string_startsWith(path, (mapping->logicalPrefix + std::string("/")))) {
            if (doof::is_null(selected) || (static_cast<int32_t>(mapping->logicalPrefix.size()) > static_cast<int32_t>(selected->logicalPrefix.size()))) {
                (selected = mapping);
            }
        }
    }
    return selected;
}
std::string namespacePath(std::string path) {
    const auto components = doof::string_split(doof::string_replaceAll(path, std::string("\\"), std::string("/")), std::string("/"));
    auto result = std::string("");
    const auto& _iterable_4 = components;
    for (const auto& component : *_iterable_4) {
        if (component == std::string("")) {
            continue;
        }
        const auto sanitized = namespaceComponent(component);
        if (result == std::string("")) {
            (result = sanitized);
        } else {
            (result = ((result + std::string("::")) + sanitized));
        }
    }
    return ((result == std::string("")) ? std::string("module") : result);
}
std::string namespaceComponent(std::string value) {
    const auto result = doof::string_replaceAll(doof::string_replaceAll(value, std::string("-"), std::string("_")), std::string("."), std::string("_"));
    if (((result == std::string("std")) || (result == std::string("doof"))) || (result == std::string("main"))) {
        return (result + std::string("_"));
    }
    return result;
}
std::string moduleHeaderName(std::string path) {
    return (moduleStem(path) + std::string(".hpp"));
}
std::string moduleSourceName(std::string path) {
    return (moduleStem(path) + std::string(".cpp"));
}
}
