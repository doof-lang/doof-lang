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
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct SourceFile; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_resolver_ {
    struct ModuleResolver;
}

#include "src_semantic.hpp"

namespace app_src_resolver_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ModuleResolver : public std::enable_shared_from_this<ModuleResolver> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources;
    doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader;
    std::shared_ptr<std::vector<std::string>> loadedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> failedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    ModuleResolver(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader, std::shared_ptr<std::vector<std::string>> loadedPaths, std::shared_ptr<std::vector<std::string>> failedPaths, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) : sources(sources), loader(loader), loadedPaths(loadedPaths), failedPaths(failedPaths), diagnostics(diagnostics) {}
    std::shared_ptr<::app_src_semantic_::SourceFile> find(std::string path);
    bool failed(std::string path);
    std::string resolve(std::string importer, std::string specifier);
};
    using SourceLoader = doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>;
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> noSourceLoader(std::string path);
    std::string withExtension(std::string path);
    std::string relativeBase(std::string importer, std::string specifier);
    std::string parentDirectory(std::string path);
}

namespace app_src_resolver_ {
}
