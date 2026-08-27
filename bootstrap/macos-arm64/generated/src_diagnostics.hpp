#pragma once
#include "doof_runtime.hpp"
namespace app_src_semantic_ {
    struct SemanticLocation;
    struct SemanticSpan;
    struct Diagnostic;
}

namespace app_src_semantic_ {
    struct SemanticLocation {
    int32_t line;
    int32_t column;
    int32_t offset;
    SemanticLocation(int32_t line, int32_t column, int32_t offset) : line(line), column(column), offset(offset) {}
    SemanticLocation() {}
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
    std::string replacement;
    Diagnostic(std::string severity, std::string message, SemanticSpan span, std::string module, std::string replacement) : severity(severity), message(message), span(span), module(module), replacement(replacement) {}
};
}

namespace app_src_diagnostics_ {
    bool hasErrorDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics);
}
