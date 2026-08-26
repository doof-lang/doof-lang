#include "src_emitter_context.hpp"

namespace app_src_emitter_context_ {
using namespace ::app_src_ast_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_semantic_;



#line 79 "/src/emitter-context.do"
std::string sourceLineDirective(::app_src_ast_::SourceSpan span, const std::shared_ptr<EmitContext>& context) {
#line 80 "/src/emitter-context.do"
    const auto path = ((context->sourcePath == std::string("")) ? context->modulePath : context->sourcePath);
#line 81 "/src/emitter-context.do"
    const auto escaped = doof::string_replaceAll(doof::string_replaceAll(path, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\""));
#line 82 "/src/emitter-context.do"
    return ((((std::string("#line ") + doof::to_string(span.start.line)) + std::string(" \"")) + escaped) + std::string("\"\n"));
}
#line 86 "/src/emitter-context.do"
std::string generatedLineDirective() {
    return std::string("#line 1 \"<doof-generated>\"\n");
}
#line 88 "/src/emitter-context.do"
void recordCoverageLine(const std::shared_ptr<EmitContext>& context, int32_t line) {
#line 89 "/src/emitter-context.do"
    const auto& _iterable_2 = context->coverageInstrumentedLines;
    for (const auto& existing : *_iterable_2) {
#line 89 "/src/emitter-context.do"
        if (existing == line) {
#line 89 "/src/emitter-context.do"
            return;
        }
    }
#line 90 "/src/emitter-context.do"
    context->coverageInstrumentedLines->push_back(line);
}
#line 93 "/src/emitter-context.do"
bool isCapturedMutable(const std::shared_ptr<EmitContext>& context, const std::string& name) {
#line 94 "/src/emitter-context.do"
    const auto& _iterable_4 = context->capturedMutables;
    for (const auto& captured : *_iterable_4) {
#line 94 "/src/emitter-context.do"
        if (captured == name) {
#line 94 "/src/emitter-context.do"
            return true;
        }
    }
#line 95 "/src/emitter-context.do"
    return false;
}
#line 98 "/src/emitter-context.do"
std::shared_ptr<EmitContext> createEmitContext(const std::shared_ptr<::app_src_ast_::Program>& program) {
#line 99 "/src/emitter-context.do"
    return createEmitContextForPrograms(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}));
}
#line 102 "/src/emitter-context.do"
std::shared_ptr<EmitContext> createEmitContextForPrograms(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs) {
#line 103 "/src/emitter-context.do"
    return std::make_shared<EmitContext>(std::string(""), std::string(""), programs, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>>(std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::shared_ptr<EmitModuleSurface>>>(std::vector<std::shared_ptr<EmitModuleSurface>>{}), std::make_shared<::app_src_json_semantics_::JsonEligibilityCache>(std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{}), std::make_shared<doof::ordered_map<std::string, bool>>(std::initializer_list<std::pair<std::string, bool>>{})), std::string(""), false, false, std::string(""), std::string(""), false, false, std::string(""), std::monostate{}, nullptr, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), nullptr, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), 0, false, false, false, -1, std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}));
}
#line 106 "/src/emitter-context.do"
std::shared_ptr<EmitContext> createEmitContextForModule(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& modulePath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& allPrograms) {
#line 107 "/src/emitter-context.do"
    auto programs = allPrograms;
#line 108 "/src/emitter-context.do"
    if (static_cast<int32_t>((programs)->size()) == 0) {
#line 108 "/src/emitter-context.do"
        (programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}));
    }
#line 109 "/src/emitter-context.do"
    const auto context = createEmitContextForPrograms(programs);
#line 110 "/src/emitter-context.do"
    (context->modulePath = modulePath);
#line 111 "/src/emitter-context.do"
    (context->sourcePath = modulePath);
#line 112 "/src/emitter-context.do"
    return context;
}
#line 1 "<doof-generated>"
}
