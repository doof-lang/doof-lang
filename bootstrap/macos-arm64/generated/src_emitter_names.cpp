#include "src_emitter_names.hpp"

namespace app_src_emitter_names_ {

std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>> configuredModuleNamespaceMappings;
std::shared_ptr<doof::ordered_map<std::string, std::string>> cachedModuleNamespaces;
void configureModuleNamespaces(const std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>>& mappings) {
    (configuredModuleNamespaceMappings = mappings);
    (cachedModuleNamespaces = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}));
}
std::string moduleStem(const std::string& path) {
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
std::string moduleNamespace(const std::string& path) {
    auto _binding_value_1 = doof::map_get(cachedModuleNamespaces, path, "", 0);
    if (doof::is_failure(_binding_value_1)) {
        const auto& cached = _binding_value_1;
        return cacheModuleNamespace(path);
    }
    const auto cached = doof::success_value(_binding_value_1);
    return cached;
}
std::string cacheModuleNamespace(const std::string& path) {
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
        doof::map_set(cachedModuleNamespaces, path, namespace_, "", 0);
        return namespace_;
    }
    const auto namespace_ = ((std::string("app_") + moduleStem(path)) + std::string("_"));
    doof::map_set(cachedModuleNamespaces, path, namespace_, "", 0);
    return namespace_;
}
std::string moduleDiagnosticPath(const std::string& path, bool stripExtension) {
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
std::string moduleNativeHeaderPath(const std::string& modulePath, const std::string& headerPath) {
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
    const auto components = doof::array_cloneMutable(doof::string_split(relativeModulePath, std::string("/")), "", 0);
    if (static_cast<int32_t>((components)->size()) > 0) {
        const auto ignoredModuleName = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic_at("src/emitter-names", 95, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    }
    const auto& _iterable_3 = doof::string_split(doof::string_replaceAll(headerPath, std::string("\\"), std::string("/")), std::string("/"));
    for (const auto& component : *_iterable_3) {
        if ((component == std::string("")) || (component == std::string("."))) {
            continue;
        }
        if (component == std::string("..")) {
            if (static_cast<int32_t>((components)->size()) == 0) {
                return headerPath;
            }
            const auto ignoredParent = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic_at("src/emitter-names", 100, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
        } else {
            components->push_back(component);
        }
    }
    auto result = mapping->outputRoot;
    const auto& _iterable_5 = components;
    for (const auto& component : *_iterable_5) {
        if (result != std::string("")) {
            (result = (result + std::string("/")));
        }
        (result = (result + component));
    }
    return result;
}
std::shared_ptr<ModuleNamespaceMapping> namespaceMappingForPath(const std::string& path) {
    std::shared_ptr<ModuleNamespaceMapping> selected = nullptr;
    const auto& _iterable_7 = configuredModuleNamespaceMappings;
    for (const auto& mapping : *_iterable_7) {
        if ((path == mapping->logicalPrefix) || doof::string_startsWith(path, (mapping->logicalPrefix + std::string("/")))) {
            if (doof::is_null(selected) || (static_cast<int32_t>(mapping->logicalPrefix.size()) > static_cast<int32_t>(selected->logicalPrefix.size()))) {
                (selected = mapping);
            }
        }
    }
    return selected;
}
std::string namespacePath(const std::string& path) {
    const auto components = doof::string_split(doof::string_replaceAll(path, std::string("\\"), std::string("/")), std::string("/"));
    auto result = std::string("");
    const auto& _iterable_9 = components;
    for (const auto& component : *_iterable_9) {
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
std::string namespaceComponent(const std::string& value) {
    const auto result = doof::string_replaceAll(doof::string_replaceAll(value, std::string("-"), std::string("_")), std::string("."), std::string("_"));
    if (((result == std::string("std")) || (result == std::string("doof"))) || (result == std::string("main"))) {
        return (result + std::string("_"));
    }
    return result;
}
std::string moduleHeaderName(const std::string& path) {
    return (moduleStem(path) + std::string(".hpp"));
}
std::string moduleSourceName(const std::string& path) {
    return (moduleStem(path) + std::string(".cpp"));
}

void __doof_initialize_module() {
        configuredModuleNamespaceMappings = std::make_shared<std::vector<std::shared_ptr<ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<ModuleNamespaceMapping>>{});
        cachedModuleNamespaces = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
}
}
