#pragma once
#include "doof_runtime.hpp"
namespace app_src_emitter_names_ {
    struct ModuleNamespaceMapping;
    extern std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>> configuredModuleNamespaceMappings;
    extern std::shared_ptr<doof::ordered_map<std::string, std::string>> cachedModuleNamespaces;
}

namespace app_src_emitter_names_ {
    struct ModuleNamespaceMapping : public std::enable_shared_from_this<ModuleNamespaceMapping> {
    std::string logicalPrefix;
    std::string packageName;
    std::string outputRoot;
    ModuleNamespaceMapping(std::string logicalPrefix, std::string packageName, std::string outputRoot) : logicalPrefix(logicalPrefix), packageName(packageName), outputRoot(outputRoot) {}
};
}

namespace app_src_emitter_names_ {
    void configureModuleNamespaces(const std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>>& mappings);
    std::string moduleStem(const std::string& path);
    std::string moduleNamespace(const std::string& path);
    std::string cacheModuleNamespace(const std::string& path);
    std::string moduleDiagnosticPath(const std::string& path, bool stripExtension);
    std::string moduleNativeHeaderPath(const std::string& modulePath, const std::string& headerPath);
    std::shared_ptr<ModuleNamespaceMapping> namespaceMappingForPath(const std::string& path);
    std::string namespacePath(const std::string& path);
    std::string namespaceComponent(const std::string& value);
    std::string moduleHeaderName(const std::string& path);
    std::string moduleSourceName(const std::string& path);
}
