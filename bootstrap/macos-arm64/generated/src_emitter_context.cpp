#include "src_emitter_context.hpp"

namespace app_src_emitter_context_ {
using namespace ::app_src_ast_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_semantic_;



std::string sourceLineDirective(::app_src_ast_::SourceSpan span, const std::shared_ptr<EmitContext>& context) {
    const auto path = ((context->sourcePath == std::string("")) ? context->modulePath : context->sourcePath);
    const auto escaped = doof::string_replaceAll(doof::string_replaceAll(path, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\""));
    return ((((std::string("#line ") + doof::to_string(span.start.line)) + std::string(" \"")) + escaped) + std::string("\"\n"));
}
std::string generatedLineDirective() {
    return std::string("#line 1 \"<doof-generated>\"\n");
}
void recordCoverageLine(const std::shared_ptr<EmitContext>& context, int32_t line) {
    const auto& _iterable_2 = context->coverageInstrumentedLines;
    for (const auto& existing : *_iterable_2) {
        if (existing == line) {
            return;
        }
    }
    context->coverageInstrumentedLines->push_back(line);
}
bool isCapturedMutable(const std::shared_ptr<EmitContext>& context, const std::string& name) {
    const auto& _iterable_4 = context->capturedMutables;
    for (const auto& captured : *_iterable_4) {
        if (captured == name) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<EmitContext> createEmitContextForModule(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& modulePath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& allPrograms) {
    auto programs = allPrograms;
    if (static_cast<int32_t>((programs)->size()) == 0) {
        (programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}));
    }
    const auto context = std::make_shared<EmitContext>(std::string(""), std::string(""), programs, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::shared_ptr<EmitModuleSurface>>>(std::vector<std::shared_ptr<EmitModuleSurface>>{}), std::make_shared<::app_src_json_semantics_::JsonEligibilityCache>(std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{}), std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{})), std::string(""), false, false, std::string(""), std::string(""), false, false, std::string(""), std::monostate{}, nullptr, nullptr, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), 0, false, false, false, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
    (context->modulePath = modulePath);
    (context->sourcePath = modulePath);
    return context;
}
}
