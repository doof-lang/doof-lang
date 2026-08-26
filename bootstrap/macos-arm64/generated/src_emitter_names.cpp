#include "src_emitter_names.hpp"

namespace app_src_emitter_names_ {

std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>> configuredModuleNamespaceMappings;
std::shared_ptr<doof::ordered_map<std::string, std::string>> cachedModuleNamespaces;
#line 18 "/src/emitter-names.do"
void configureModuleNamespaces(const std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>>& mappings) {
#line 19 "/src/emitter-names.do"
    (configuredModuleNamespaceMappings = mappings);
#line 20 "/src/emitter-names.do"
    (cachedModuleNamespaces = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}));
}
#line 23 "/src/emitter-names.do"
std::string moduleStem(const std::string& path) {
#line 24 "/src/emitter-names.do"
    auto normalized = doof::string_replaceAll(path, std::string("\\"), std::string("/"));
#line 25 "/src/emitter-names.do"
    const auto mapping = namespaceMappingForPath(normalized);
#line 26 "/src/emitter-names.do"
    if (!doof::is_null(mapping)) {
#line 27 "/src/emitter-names.do"
        auto relativePath = doof::string_substring(normalized, static_cast<int32_t>(mapping->logicalPrefix.size()), static_cast<int32_t>(normalized.size()));
#line 28 "/src/emitter-names.do"
        while (doof::string_startsWith(relativePath, std::string("/"))) {
#line 29 "/src/emitter-names.do"
            (relativePath = doof::string_substring(relativePath, 1, static_cast<int32_t>(relativePath.size())));
        }
#line 31 "/src/emitter-names.do"
        (normalized = mapping->packageName);
#line 32 "/src/emitter-names.do"
        if (relativePath != std::string("")) {
#line 32 "/src/emitter-names.do"
            (normalized = ((normalized + std::string("/")) + relativePath));
        }
    }
#line 37 "/src/emitter-names.do"
    const auto withoutRoot = (doof::string_startsWith(normalized, std::string("/")) ? doof::string_substring(normalized, 1, 1000000) : normalized);
#line 38 "/src/emitter-names.do"
    const auto result = doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(withoutRoot, std::string("/"), std::string("_")), std::string(".do"), std::string("")), std::string("-"), std::string("_")), std::string("."), std::string("_"));
#line 40 "/src/emitter-names.do"
    return ((result == std::string("")) ? std::string("module") : result);
}
#line 43 "/src/emitter-names.do"
std::string moduleNamespace(const std::string& path) {
#line 44 "/src/emitter-names.do"
    auto _binding_value_1 = doof::map_get(cachedModuleNamespaces, path, "", 0);
    if (doof::is_failure(_binding_value_1)) {
        const auto& cached = _binding_value_1;
#line 44 "/src/emitter-names.do"
        return cacheModuleNamespace(path);
    }
    const auto cached = doof::success_value(_binding_value_1);
#line 45 "/src/emitter-names.do"
    return cached;
}
#line 48 "/src/emitter-names.do"
std::string cacheModuleNamespace(const std::string& path) {
#line 49 "/src/emitter-names.do"
    const auto mapping = namespaceMappingForPath(path);
#line 50 "/src/emitter-names.do"
    if (!doof::is_null(mapping)) {
#line 51 "/src/emitter-names.do"
        auto relativePath = doof::string_substring(path, static_cast<int32_t>(mapping->logicalPrefix.size()), static_cast<int32_t>(path.size()));
#line 52 "/src/emitter-names.do"
        while (doof::string_startsWith(relativePath, std::string("/"))) {
#line 53 "/src/emitter-names.do"
            (relativePath = doof::string_substring(relativePath, 1, static_cast<int32_t>(relativePath.size())));
        }
#line 55 "/src/emitter-names.do"
        if (doof::string_endsWith(relativePath, std::string(".do"))) {
#line 56 "/src/emitter-names.do"
            (relativePath = doof::string_substring(relativePath, 0, (static_cast<int32_t>(relativePath.size()) - 3)));
        }
#line 58 "/src/emitter-names.do"
        auto namespace_ = namespacePath(mapping->packageName);
#line 59 "/src/emitter-names.do"
        if (relativePath != std::string("")) {
#line 59 "/src/emitter-names.do"
            (namespace_ = ((namespace_ + std::string("::")) + namespacePath(relativePath)));
        }
#line 60 "/src/emitter-names.do"
        doof::map_set(cachedModuleNamespaces, path, namespace_, "", 0);
#line 61 "/src/emitter-names.do"
        return namespace_;
    }
#line 63 "/src/emitter-names.do"
    const auto namespace_ = ((std::string("app_") + moduleStem(path)) + std::string("_"));
#line 64 "/src/emitter-names.do"
    doof::map_set(cachedModuleNamespaces, path, namespace_, "", 0);
#line 65 "/src/emitter-names.do"
    return namespace_;
}
#line 69 "/src/emitter-names.do"
std::string moduleDiagnosticPath(const std::string& path, bool stripExtension) {
#line 70 "/src/emitter-names.do"
    auto normalized = doof::string_replaceAll(path, std::string("\\"), std::string("/"));
#line 71 "/src/emitter-names.do"
    const auto mapping = namespaceMappingForPath(normalized);
#line 72 "/src/emitter-names.do"
    if (!doof::is_null(mapping)) {
#line 73 "/src/emitter-names.do"
        (normalized = doof::string_substring(normalized, static_cast<int32_t>(mapping->logicalPrefix.size()), static_cast<int32_t>(normalized.size())));
    }
#line 75 "/src/emitter-names.do"
    while (doof::string_startsWith(normalized, std::string("/"))) {
#line 76 "/src/emitter-names.do"
        (normalized = doof::string_substring(normalized, 1, static_cast<int32_t>(normalized.size())));
    }
#line 78 "/src/emitter-names.do"
    if (stripExtension && doof::string_endsWith(normalized, std::string(".do"))) {
#line 79 "/src/emitter-names.do"
        (normalized = doof::string_substring(normalized, 0, (static_cast<int32_t>(normalized.size()) - 3)));
    }
#line 81 "/src/emitter-names.do"
    return ((normalized == std::string("")) ? std::string("<module>") : normalized);
}
#line 85 "/src/emitter-names.do"
std::string moduleNativeHeaderPath(const std::string& modulePath, const std::string& headerPath) {
#line 86 "/src/emitter-names.do"
    if (!doof::string_startsWith(headerPath, std::string("./")) && !doof::string_startsWith(headerPath, std::string("../"))) {
#line 86 "/src/emitter-names.do"
        return headerPath;
    }
#line 87 "/src/emitter-names.do"
    const auto mapping = namespaceMappingForPath(modulePath);
#line 88 "/src/emitter-names.do"
    if (doof::is_null(mapping)) {
#line 88 "/src/emitter-names.do"
        return headerPath;
    }
#line 90 "/src/emitter-names.do"
    auto relativeModulePath = doof::string_substring(modulePath, static_cast<int32_t>(mapping->logicalPrefix.size()), static_cast<int32_t>(modulePath.size()));
#line 91 "/src/emitter-names.do"
    while (doof::string_startsWith(relativeModulePath, std::string("/"))) {
#line 92 "/src/emitter-names.do"
        (relativeModulePath = doof::string_substring(relativeModulePath, 1, static_cast<int32_t>(relativeModulePath.size())));
    }
#line 94 "/src/emitter-names.do"
    const auto components = doof::array_cloneMutable(doof::string_split(relativeModulePath, std::string("/")), "", 0);
#line 95 "/src/emitter-names.do"
    if (static_cast<int32_t>((components)->size()) > 0) {
#line 95 "/src/emitter-names.do"
        const auto ignoredModuleName = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic_at("src/emitter-names", 95, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    }
#line 96 "/src/emitter-names.do"
    const auto& _iterable_3 = doof::string_split(doof::string_replaceAll(headerPath, std::string("\\"), std::string("/")), std::string("/"));
    for (const auto& component : *_iterable_3) {
#line 97 "/src/emitter-names.do"
        if ((component == std::string("")) || (component == std::string("."))) {
#line 97 "/src/emitter-names.do"
            continue;
        }
#line 98 "/src/emitter-names.do"
        if (component == std::string("..")) {
#line 99 "/src/emitter-names.do"
            if (static_cast<int32_t>((components)->size()) == 0) {
#line 99 "/src/emitter-names.do"
                return headerPath;
            }
#line 100 "/src/emitter-names.do"
            const auto ignoredParent = [&]() -> std::string { auto _try_value = doof::array_pop(components); if (doof::is_failure(_try_value)) doof::panic_at("src/emitter-names", 100, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
        } else {
#line 102 "/src/emitter-names.do"
            components->push_back(component);
        }
    }
#line 106 "/src/emitter-names.do"
    auto result = mapping->outputRoot;
#line 107 "/src/emitter-names.do"
    const auto& _iterable_5 = components;
    for (const auto& component : *_iterable_5) {
#line 108 "/src/emitter-names.do"
        if (result != std::string("")) {
#line 108 "/src/emitter-names.do"
            (result = (result + std::string("/")));
        }
#line 109 "/src/emitter-names.do"
        (result = (result + component));
    }
#line 111 "/src/emitter-names.do"
    return result;
}
#line 114 "/src/emitter-names.do"
std::shared_ptr<ModuleNamespaceMapping> namespaceMappingForPath(const std::string& path) {
#line 115 "/src/emitter-names.do"
    std::shared_ptr<ModuleNamespaceMapping> selected = nullptr;
#line 116 "/src/emitter-names.do"
    const auto& _iterable_7 = configuredModuleNamespaceMappings;
    for (const auto& mapping : *_iterable_7) {
#line 117 "/src/emitter-names.do"
        if ((path == mapping->logicalPrefix) || doof::string_startsWith(path, (mapping->logicalPrefix + std::string("/")))) {
#line 118 "/src/emitter-names.do"
            if (doof::is_null(selected) || (static_cast<int32_t>(mapping->logicalPrefix.size()) > static_cast<int32_t>(selected->logicalPrefix.size()))) {
#line 119 "/src/emitter-names.do"
                (selected = mapping);
            }
        }
    }
#line 123 "/src/emitter-names.do"
    return selected;
}
#line 126 "/src/emitter-names.do"
std::string namespacePath(const std::string& path) {
#line 127 "/src/emitter-names.do"
    const auto components = doof::string_split(doof::string_replaceAll(path, std::string("\\"), std::string("/")), std::string("/"));
#line 128 "/src/emitter-names.do"
    auto result = std::string("");
#line 129 "/src/emitter-names.do"
    const auto& _iterable_9 = components;
    for (const auto& component : *_iterable_9) {
#line 130 "/src/emitter-names.do"
        if (component == std::string("")) {
#line 130 "/src/emitter-names.do"
            continue;
        }
#line 131 "/src/emitter-names.do"
        const auto sanitized = namespaceComponent(component);
#line 132 "/src/emitter-names.do"
        if (result == std::string("")) {
#line 132 "/src/emitter-names.do"
            (result = sanitized);
        } else {
#line 133 "/src/emitter-names.do"
            (result = ((result + std::string("::")) + sanitized));
        }
    }
#line 135 "/src/emitter-names.do"
    return ((result == std::string("")) ? std::string("module") : result);
}
#line 138 "/src/emitter-names.do"
std::string namespaceComponent(const std::string& value) {
#line 139 "/src/emitter-names.do"
    const auto result = doof::string_replaceAll(doof::string_replaceAll(value, std::string("-"), std::string("_")), std::string("."), std::string("_"));
#line 140 "/src/emitter-names.do"
    if (((result == std::string("std")) || (result == std::string("doof"))) || (result == std::string("main"))) {
#line 140 "/src/emitter-names.do"
        return (result + std::string("_"));
    }
#line 141 "/src/emitter-names.do"
    return result;
}
#line 144 "/src/emitter-names.do"
std::string moduleHeaderName(const std::string& path) {
#line 145 "/src/emitter-names.do"
    return (moduleStem(path) + std::string(".hpp"));
}
#line 148 "/src/emitter-names.do"
std::string moduleSourceName(const std::string& path) {
#line 149 "/src/emitter-names.do"
    return (moduleStem(path) + std::string(".cpp"));
}
#line 1 "<doof-generated>"

void __doof_initialize_module() {
        configuredModuleNamespaceMappings = std::make_shared<std::vector<std::shared_ptr<ModuleNamespaceMapping>>>(std::vector<std::shared_ptr<ModuleNamespaceMapping>>{});
        cachedModuleNamespaces = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
}
}
