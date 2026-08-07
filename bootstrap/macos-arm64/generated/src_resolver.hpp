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
    doof::JsonObject toJsonObject() const;
    static doof::Result<SemanticLocation, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct SourceFile : public std::enable_shared_from_this<SourceFile> {
    std::string path;
    std::string source;
    SourceFile(std::string path, std::string source) : path(path), source(source) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<SourceFile>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<SemanticSpan, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct Diagnostic : public std::enable_shared_from_this<Diagnostic> {
    std::string severity;
    std::string message;
    SemanticSpan span;
    std::string module;
    std::string replacement = std::string("");
    Diagnostic(std::string severity, std::string message, SemanticSpan span, std::string module, std::string replacement = std::string("")) : severity(severity), message(message), span(span), module(module), replacement(replacement) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Diagnostic>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_resolver_ {
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> noSourceLoader(const std::string& path);
    std::string withExtension(const std::string& path);
    std::string relativeBase(const std::string& importer, const std::string& specifier);
    std::string parentDirectory(const std::string& path);
}
