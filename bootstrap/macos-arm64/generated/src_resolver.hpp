#pragma once
#include "doof_runtime.hpp"
namespace app_src_semantic_ {
    struct SemanticLocation;
    struct SemanticSpan;
    struct Diagnostic;
    struct SourceFile;
}

namespace app_src_resolver_ {
    struct ModuleResolver;
}

namespace app_src_resolver_ {
    using SourceLoader = doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>;
}

namespace app_src_semantic_ {
    struct SemanticLocation {
    int32_t line;
    int32_t column;
    int32_t offset;
    SemanticLocation(int32_t line, int32_t column, int32_t offset) : line(line), column(column), offset(offset) {}
    SemanticLocation() {}
};
    struct SourceFile : public std::enable_shared_from_this<SourceFile> {
    std::string path;
    std::string source;
    std::string physicalPath = std::string("");
    SourceFile(std::string path, std::string source, std::string physicalPath = std::string("")) : path(path), source(source), physicalPath(physicalPath) {}
};
}

namespace app_src_resolver_ {
    struct ModuleResolver : public std::enable_shared_from_this<ModuleResolver> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources;
    doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader;
    std::shared_ptr<std::vector<std::string>> loadedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> failedPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    ModuleResolver(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader, std::shared_ptr<std::vector<std::string>> loadedPaths, std::shared_ptr<std::vector<std::string>> failedPaths, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) : sources(sources), loader(loader), loadedPaths(loadedPaths), failedPaths(failedPaths), diagnostics(diagnostics) {}
    std::shared_ptr<::app_src_semantic_::SourceFile> find(const std::string& path);
    bool failed(const std::string& path);
    std::string resolve(const std::string& importer, const std::string& specifier);
};
}

namespace app_src_semantic_ {
    struct SemanticSpan {
    SemanticLocation start;
    SemanticLocation end;
    SemanticSpan(SemanticLocation start, SemanticLocation end) : start(start), end(end) {}
    SemanticSpan() {}
};
    struct Diagnostic : public std::enable_shared_from_this<Diagnostic> {
    std::string severity;
    std::string message;
    SemanticSpan span;
    std::string module;
    std::string replacement = std::string("");
    Diagnostic(std::string severity, std::string message, SemanticSpan span, std::string module, std::string replacement = std::string("")) : severity(severity), message(message), span(span), module(module), replacement(replacement) {}
};
}

namespace app_src_resolver_ {
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> noSourceLoader(const std::string& path);
    std::string withExtension(const std::string& path);
    std::string relativeBase(const std::string& importer, const std::string& specifier);
    std::string parentDirectory(const std::string& path);
}
