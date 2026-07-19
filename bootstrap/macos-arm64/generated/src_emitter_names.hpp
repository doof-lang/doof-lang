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
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_emitter_names_ {
    struct ModuleNamespaceMapping;
}

namespace app_src_emitter_names_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ModuleNamespaceMapping : public std::enable_shared_from_this<ModuleNamespaceMapping> {
    std::string logicalPrefix;
    std::string packageName;
    std::string outputRoot = std::string("");
    ModuleNamespaceMapping(std::string logicalPrefix, std::string packageName, std::string outputRoot = std::string("")) : logicalPrefix(logicalPrefix), packageName(packageName), outputRoot(outputRoot) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ModuleNamespaceMapping>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    void configureModuleNamespaces(std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>> mappings);
    std::string moduleStem(std::string path);
    std::string moduleNamespace(std::string path);
    std::string moduleDiagnosticPath(std::string path, bool stripExtension);
    std::string moduleNativeHeaderPath(std::string modulePath, std::string headerPath);
    std::shared_ptr<ModuleNamespaceMapping> namespaceMappingForPath(std::string path);
    std::string namespacePath(std::string path);
    std::string namespaceComponent(std::string value);
    std::string moduleHeaderName(std::string path);
    std::string moduleSourceName(std::string path);
}

namespace app_src_emitter_names_ {
}
