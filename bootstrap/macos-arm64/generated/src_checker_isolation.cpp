#include "src_checker_isolation.hpp"

namespace app_src_checker_isolation_ {
using namespace ::app_src_analyzer_;
using namespace ::app_src_semantic_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_checker_async_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_symbols_;




#line 43 "/src/checker-isolation.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> unwrapExport(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 44 "/src/checker-isolation.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 45 "/src/checker-isolation.do"
            return export_->declaration;
    }
    else {
#line 46 "/src/checker-isolation.do"
            return statement;
    }
    }
    doof::unreachable();
}
#line 50 "/src/checker-isolation.do"
std::shared_ptr<IsolationGraph> collectGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 51 "/src/checker-isolation.do"
    const auto graph = std::make_shared<IsolationGraph>(std::make_shared<std::vector<std::shared_ptr<IsolationNode>>>(std::vector<std::shared_ptr<IsolationNode>>{}));
#line 52 "/src/checker-isolation.do"
    const auto& _iterable_2 = result->modules;
    for (const auto& module : *_iterable_2) {
#line 53 "/src/checker-isolation.do"
        const auto& _iterable_4 = module->program->statements;
        for (const auto& raw : *_iterable_4) {
#line 54 "/src/checker-isolation.do"
            {
                auto _case_subject = unwrapExport(raw);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                    const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 55 "/src/checker-isolation.do"
                    graph->nodes->push_back(std::make_shared<IsolationNode>(fn, module->path, std::string(""), std::make_shared<std::vector<std::shared_ptr<IsolationCall>>>(std::vector<std::shared_ptr<IsolationCall>>{}), nullptr, nullptr));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 57 "/src/checker-isolation.do"
                    const auto& _iterable_6 = class_->methods;
                    for (const auto& method : *_iterable_6) {
#line 58 "/src/checker-isolation.do"
                        graph->nodes->push_back(std::make_shared<IsolationNode>(method, module->path, class_->name, std::make_shared<std::vector<std::shared_ptr<IsolationCall>>>(std::vector<std::shared_ptr<IsolationCall>>{}), nullptr, nullptr));
                    }
            }
            else {
            }
            }
        }
    }
#line 65 "/src/checker-isolation.do"
    return graph;
}
#line 68 "/src/checker-isolation.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
#line 69 "/src/checker-isolation.do"
    const auto& _iterable_8 = result->modules;
    for (const auto& module : *_iterable_8) {
#line 69 "/src/checker-isolation.do"
        if (module->path == path) {
#line 69 "/src/checker-isolation.do"
            return module;
        }
    }
#line 70 "/src/checker-isolation.do"
    return nullptr;
}
#line 73 "/src/checker-isolation.do"
bool sameSpan(::app_src_ast_::SourceSpan left, ::app_src_semantic_::SemanticSpan right) {
#line 74 "/src/checker-isolation.do"
    return ((left.start.offset == right.start.offset) && (left.end.offset == right.end.offset));
}
#line 77 "/src/checker-isolation.do"
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> moduleValueDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::Binding>& binding) {
#line 78 "/src/checker-isolation.do"
    if ((!doof::is_null(binding->symbol)) && ((binding->symbol->kind == std::string("const")) || (binding->symbol->kind == std::string("readonly")))) {
#line 79 "/src/checker-isolation.do"
        return ::app_src_checker_symbols_::declarationFor(result, doof::unwrap_optional(binding->symbol));
    }
#line 81 "/src/checker-isolation.do"
    const auto module = findModule(result, binding->module);
#line 82 "/src/checker-isolation.do"
    if (doof::is_null(module)) {
#line 82 "/src/checker-isolation.do"
        return std::monostate{};
    }
#line 83 "/src/checker-isolation.do"
    const auto& _iterable_10 = module->program->statements;
    for (const auto& raw : *_iterable_10) {
#line 84 "/src/checker-isolation.do"
        const auto statement = unwrapExport(raw);
#line 85 "/src/checker-isolation.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                const auto& value = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 86 "/src/checker-isolation.do"
                if (sameSpan(value->span, binding->span)) {
#line 86 "/src/checker-isolation.do"
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                const auto& value = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 87 "/src/checker-isolation.do"
                if (sameSpan(value->span, binding->span)) {
#line 87 "/src/checker-isolation.do"
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                const auto& value = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 88 "/src/checker-isolation.do"
                if (sameSpan(value->span, binding->span)) {
#line 88 "/src/checker-isolation.do"
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                const auto& value = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 89 "/src/checker-isolation.do"
                if (sameSpan(value->span, binding->span)) {
#line 89 "/src/checker-isolation.do"
                    return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(value);
                }
        }
        else {
        }
        }
    }
#line 93 "/src/checker-isolation.do"
    return std::monostate{};
}
#line 96 "/src/checker-isolation.do"
std::shared_ptr<IsolationReason> mutableModuleReason(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 97 "/src/checker-isolation.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 99 "/src/checker-isolation.do"
            if (doof::is_null(identifier->resolvedBinding)) {
#line 99 "/src/checker-isolation.do"
                return nullptr;
            }
#line 100 "/src/checker-isolation.do"
            const auto declaration = moduleValueDeclaration(result, doof::unwrap_optional(identifier->resolvedBinding));
#line 101 "/src/checker-isolation.do"
            if (doof::is_null(declaration)) {
#line 101 "/src/checker-isolation.do"
                return nullptr;
            }
#line 102 "/src/checker-isolation.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
#line 103 "/src/checker-isolation.do"
                    return nullptr;
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
#line 104 "/src/checker-isolation.do"
                    return std::make_shared<IsolationReason>(std::string("module"), identifier->name, identifier->span);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            }
            else {
#line 107 "/src/checker-isolation.do"
                    return nullptr;
            }
            }
#line 109 "/src/checker-isolation.do"
            const auto violation = ::app_src_checker_actor_boundary_::findActorBoundaryViolation(result, identifier->resolvedBinding->type_);
#line 110 "/src/checker-isolation.do"
            if (!doof::is_null(violation)) {
#line 111 "/src/checker-isolation.do"
                return std::make_shared<IsolationReason>(std::string("module"), identifier->name, identifier->span);
            }
    }
    else {
    }
    }
#line 116 "/src/checker-isolation.do"
    return nullptr;
}
#line 119 "/src/checker-isolation.do"
std::shared_ptr<IsolationReason> mutableStaticReason(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 120 "/src/checker-isolation.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 122 "/src/checker-isolation.do"
            if (doof::is_null(identifier->resolvedBinding) || (identifier->resolvedBinding->kind != std::string("field"))) {
#line 122 "/src/checker-isolation.do"
                return nullptr;
            }
#line 123 "/src/checker-isolation.do"
            const auto binding = doof::unwrap_optional(identifier->resolvedBinding);
#line 124 "/src/checker-isolation.do"
            const auto module = findModule(result, binding->module);
#line 125 "/src/checker-isolation.do"
            if (doof::is_null(module)) {
#line 125 "/src/checker-isolation.do"
                return nullptr;
            }
#line 126 "/src/checker-isolation.do"
            const auto& _iterable_12 = module->program->statements;
            for (const auto& raw : *_iterable_12) {
#line 127 "/src/checker-isolation.do"
                {
                    auto _case_subject = unwrapExport(raw);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 129 "/src/checker-isolation.do"
                        if (class_->name != binding->fieldOwner) {
#line 129 "/src/checker-isolation.do"
                            continue;
                        }
#line 130 "/src/checker-isolation.do"
                        return staticFieldReason(result, class_, identifier->name, identifier->span);
                }
                else {
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 137 "/src/checker-isolation.do"
            if (doof::is_null(member->resolvedStaticOwner)) {
#line 137 "/src/checker-isolation.do"
                return nullptr;
            }
#line 138 "/src/checker-isolation.do"
            return staticFieldReason(result, doof::unwrap_optional(member->resolvedStaticOwner), member->property, member->span);
    }
    else {
    }
    }
#line 142 "/src/checker-isolation.do"
    return nullptr;
}
#line 145 "/src/checker-isolation.do"
std::shared_ptr<IsolationReason> staticFieldReason(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::string& property, ::app_src_ast_::SourceSpan span) {
#line 146 "/src/checker-isolation.do"
    const auto& _iterable_14 = owner->fields;
    for (const auto& field : *_iterable_14) {
#line 147 "/src/checker-isolation.do"
        if (!field->static_ || field->const_) {
#line 147 "/src/checker-isolation.do"
            continue;
        }
#line 148 "/src/checker-isolation.do"
        const auto& _iterable_16 = field->names;
        for (const auto& name : *_iterable_16) {
#line 149 "/src/checker-isolation.do"
            if (name != property) {
#line 149 "/src/checker-isolation.do"
                continue;
            }
#line 150 "/src/checker-isolation.do"
            auto mutable_ = (field->let_ || doof::is_null(field->resolvedType));
#line 151 "/src/checker-isolation.do"
            if (!mutable_) {
#line 151 "/src/checker-isolation.do"
                (mutable_ = (!doof::is_null(::app_src_checker_actor_boundary_::findActorBoundaryViolation(result, doof::unwrap_optional(field->resolvedType)))));
            }
#line 152 "/src/checker-isolation.do"
            if (!mutable_) {
#line 152 "/src/checker-isolation.do"
                return nullptr;
            }
#line 153 "/src/checker-isolation.do"
            return std::make_shared<IsolationReason>(std::string("static"), ((owner->name + std::string(".")) + property), span);
        }
    }
#line 156 "/src/checker-isolation.do"
    return nullptr;
}
#line 159 "/src/checker-isolation.do"
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> allExpressions(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>& roots) {
#line 160 "/src/checker-isolation.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> result = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 161 "/src/checker-isolation.do"
    const auto& _iterable_18 = roots;
    for (const auto& root : *_iterable_18) {
#line 161 "/src/checker-isolation.do"
        collectExpressionTree(root, result);
    }
#line 162 "/src/checker-isolation.do"
    return result;
}
#line 165 "/src/checker-isolation.do"
void collectExpressionTree(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>& result) {
#line 166 "/src/checker-isolation.do"
    result->push_back(expression);
#line 167 "/src/checker-isolation.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> nested = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 168 "/src/checker-isolation.do"
    ::app_src_checker_actor_lifecycle_::collectNestedExpressions(expression, nested);
#line 169 "/src/checker-isolation.do"
    const auto& _iterable_20 = nested;
    for (const auto& child : *_iterable_20) {
#line 169 "/src/checker-isolation.do"
        collectExpressionTree(child, result);
    }
}
#line 172 "/src/checker-isolation.do"
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> functionExpressionRoots(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
#line 173 "/src/checker-isolation.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> roots = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 174 "/src/checker-isolation.do"
    const auto& _iterable_22 = fn->params;
    for (const auto& parameter : *_iterable_22) {
#line 174 "/src/checker-isolation.do"
        if (!doof::is_null(parameter->defaultValue)) {
#line 174 "/src/checker-isolation.do"
            roots->push_back(doof::unwrap_optional(parameter->defaultValue));
        }
    }
#line 175 "/src/checker-isolation.do"
    {
        auto _case_subject = fn->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 176 "/src/checker-isolation.do"
            ::app_src_checker_actor_lifecycle_::collectBlockExpressions(block, roots);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 177 "/src/checker-isolation.do"
            roots->push_back(expression);
    }
    }
#line 179 "/src/checker-isolation.do"
    return roots;
}
#line 182 "/src/checker-isolation.do"
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> functionExpressions(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
#line 183 "/src/checker-isolation.do"
    return allExpressions(functionExpressionRoots(fn));
}
#line 186 "/src/checker-isolation.do"
std::shared_ptr<IsolationNode> nodeForDeclaration(const std::shared_ptr<IsolationGraph>& graph, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration) {
#line 187 "/src/checker-isolation.do"
    const auto& _iterable_24 = graph->nodes;
    for (const auto& node : *_iterable_24) {
#line 187 "/src/checker-isolation.do"
        if (node->declaration == declaration) {
#line 187 "/src/checker-isolation.do"
            return node;
        }
    }
#line 188 "/src/checker-isolation.do"
    return nullptr;
}
#line 191 "/src/checker-isolation.do"
std::shared_ptr<std::vector<std::shared_ptr<IsolationNode>>> nodesForDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<IsolationGraph>& graph, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration) {
#line 192 "/src/checker-isolation.do"
    const auto direct = nodeForDeclaration(graph, declaration);
#line 193 "/src/checker-isolation.do"
    if (!doof::is_null(direct)) {
#line 193 "/src/checker-isolation.do"
        return std::make_shared<std::vector<std::shared_ptr<IsolationNode>>>(std::vector<std::shared_ptr<IsolationNode>>{doof::unwrap_optional(direct)});
    }
#line 194 "/src/checker-isolation.do"
    std::shared_ptr<std::vector<std::shared_ptr<IsolationNode>>> targets = std::make_shared<std::vector<std::shared_ptr<IsolationNode>>>(std::vector<std::shared_ptr<IsolationNode>>{});
#line 195 "/src/checker-isolation.do"
    const auto& _iterable_26 = result->modules;
    for (const auto& module : *_iterable_26) {
#line 196 "/src/checker-isolation.do"
        const auto& _iterable_28 = module->program->statements;
        for (const auto& raw : *_iterable_28) {
#line 197 "/src/checker-isolation.do"
            {
                auto _case_subject = unwrapExport(raw);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 199 "/src/checker-isolation.do"
                    auto ownsMethod = false;
#line 200 "/src/checker-isolation.do"
                    const auto& _iterable_30 = interface_->methods;
                    for (const auto& method : *_iterable_30) {
#line 201 "/src/checker-isolation.do"
                        if (((method->name == declaration->name) && (method->span.start.offset == declaration->span.start.offset)) && (method->span.end.offset == declaration->span.end.offset)) {
#line 202 "/src/checker-isolation.do"
                            (ownsMethod = true);
                        }
                    }
#line 205 "/src/checker-isolation.do"
                    if (!ownsMethod || doof::is_null(interface_->resolvedSymbol)) {
#line 205 "/src/checker-isolation.do"
                        continue;
                    }
#line 206 "/src/checker-isolation.do"
                    const auto& _iterable_32 = interface_->resolvedSymbol->implementations;
                    for (const auto& implementation : *_iterable_32) {
#line 207 "/src/checker-isolation.do"
                        const auto candidate = ::app_src_checker_symbols_::declarationFor(result, implementation);
#line 208 "/src/checker-isolation.do"
                        if (doof::is_null(candidate)) {
#line 208 "/src/checker-isolation.do"
                            continue;
                        }
#line 209 "/src/checker-isolation.do"
                        {
                            auto _case_subject = doof::unwrap_optional(candidate);
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 211 "/src/checker-isolation.do"
                                const auto& _iterable_34 = class_->methods;
                                for (const auto& method : *_iterable_34) {
#line 212 "/src/checker-isolation.do"
                                    if ((method->name == declaration->name) && (method->static_ == declaration->static_)) {
#line 213 "/src/checker-isolation.do"
                                        const auto node = nodeForDeclaration(graph, method);
#line 214 "/src/checker-isolation.do"
                                        if (!doof::is_null(node)) {
#line 214 "/src/checker-isolation.do"
                                            targets->push_back(doof::unwrap_optional(node));
                                        }
                                    }
                                }
                        }
                        else {
                        }
                        }
                    }
            }
            else {
            }
            }
        }
    }
#line 226 "/src/checker-isolation.do"
    return targets;
}
#line 229 "/src/checker-isolation.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> callDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_ast_::CallExpression>& call) {
#line 230 "/src/checker-isolation.do"
    if (!doof::is_null(call->resolvedFunction)) {
#line 230 "/src/checker-isolation.do"
        return call->resolvedFunction;
    }
#line 231 "/src/checker-isolation.do"
    {
        auto _case_subject = call->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 233 "/src/checker-isolation.do"
            if (doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 233 "/src/checker-isolation.do"
                return nullptr;
            }
#line 234 "/src/checker-isolation.do"
            {
                auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 236 "/src/checker-isolation.do"
                    const auto declaration = ::app_src_checker_symbols_::declarationFor(result, interface_->symbol);
#line 237 "/src/checker-isolation.do"
                    if (doof::is_null(declaration)) {
#line 237 "/src/checker-isolation.do"
                        return nullptr;
                    }
#line 238 "/src/checker-isolation.do"
                    {
                        auto _case_subject = doof::unwrap_optional(declaration);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                            const auto& interfaceDeclaration = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 240 "/src/checker-isolation.do"
                            const auto& _iterable_36 = interfaceDeclaration->methods;
                            for (const auto& method : *_iterable_36) {
#line 240 "/src/checker-isolation.do"
                                if (method->name == member->property) {
#line 240 "/src/checker-isolation.do"
                                    return method;
                                }
                            }
                    }
                    else {
                    }
                    }
            }
            else {
            }
            }
    }
    else {
    }
    }
#line 250 "/src/checker-isolation.do"
    return nullptr;
}
#line 253 "/src/checker-isolation.do"
void analyzeNode(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<IsolationGraph>& graph, const std::shared_ptr<IsolationNode>& node) {
#line 254 "/src/checker-isolation.do"
    if (node->declaration->bodyless && !node->declaration->isolated_) {
#line 255 "/src/checker-isolation.do"
        (node->directReason = std::make_shared<IsolationReason>(std::string("bodyless"), node->declaration->name, node->declaration->span));
#line 256 "/src/checker-isolation.do"
        return;
    }
#line 258 "/src/checker-isolation.do"
    const auto& _iterable_38 = functionExpressions(node->declaration);
    for (const auto& expression : *_iterable_38) {
#line 259 "/src/checker-isolation.do"
        if (doof::is_null(node->directReason)) {
#line 260 "/src/checker-isolation.do"
            (node->directReason = mutableModuleReason(result, expression));
#line 261 "/src/checker-isolation.do"
            if (doof::is_null(node->directReason)) {
#line 261 "/src/checker-isolation.do"
                (node->directReason = mutableStaticReason(result, expression));
            }
        }
#line 263 "/src/checker-isolation.do"
        {
            auto _case_subject = expression;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
                const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 265 "/src/checker-isolation.do"
                const auto declaration = callDeclaration(result, call);
#line 266 "/src/checker-isolation.do"
                if (!doof::is_null(declaration)) {
#line 267 "/src/checker-isolation.do"
                    node->calls->push_back(std::make_shared<IsolationCall>(doof::unwrap_optional(declaration), call->span));
                }
        }
        else {
        }
        }
    }
}
#line 275 "/src/checker-isolation.do"
void inferIsolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<IsolationGraph>& graph) {
#line 276 "/src/checker-isolation.do"
    const auto& _iterable_40 = graph->nodes;
    for (const auto& node : *_iterable_40) {
#line 277 "/src/checker-isolation.do"
        analyzeNode(result, graph, node);
#line 278 "/src/checker-isolation.do"
        (node->reason = node->directReason);
    }
#line 280 "/src/checker-isolation.do"
    auto changed = true;
#line 281 "/src/checker-isolation.do"
    while (changed) {
#line 282 "/src/checker-isolation.do"
        (changed = false);
#line 283 "/src/checker-isolation.do"
        const auto& _iterable_42 = graph->nodes;
        for (const auto& node : *_iterable_42) {
#line 284 "/src/checker-isolation.do"
            if (!doof::is_null(node->reason)) {
#line 284 "/src/checker-isolation.do"
                continue;
            }
#line 285 "/src/checker-isolation.do"
            const auto& _iterable_44 = node->calls;
            for (const auto& call : *_iterable_44) {
#line 286 "/src/checker-isolation.do"
                const auto& _iterable_46 = nodesForDeclaration(result, graph, call->declaration);
                for (const auto& target : *_iterable_46) {
#line 287 "/src/checker-isolation.do"
                    if (!doof::is_null(target->reason)) {
#line 288 "/src/checker-isolation.do"
                        (node->reason = std::make_shared<IsolationReason>(std::string("call"), target->declaration->name, call->span));
#line 289 "/src/checker-isolation.do"
                        (changed = true);
#line 290 "/src/checker-isolation.do"
                        break;
                    }
                }
#line 293 "/src/checker-isolation.do"
                if (!doof::is_null(node->reason)) {
#line 293 "/src/checker-isolation.do"
                    break;
                }
            }
        }
    }
#line 297 "/src/checker-isolation.do"
    const auto& _iterable_48 = graph->nodes;
    for (const auto& node : *_iterable_48) {
#line 297 "/src/checker-isolation.do"
        (node->declaration->resolvedIsolated = doof::is_null(node->reason));
    }
}
#line 300 "/src/checker-isolation.do"
std::string reasonText(const std::shared_ptr<IsolationReason>& reason) {
#line 301 "/src/checker-isolation.do"
    if (reason->kind == std::string("module")) {
#line 301 "/src/checker-isolation.do"
        return ((std::string("accesses mutable module binding \"") + reason->name) + std::string("\""));
    }
#line 302 "/src/checker-isolation.do"
    if (reason->kind == std::string("static")) {
#line 302 "/src/checker-isolation.do"
        return ((std::string("accesses mutable static field \"") + reason->name) + std::string("\""));
    }
#line 303 "/src/checker-isolation.do"
    if (reason->kind == std::string("call")) {
#line 303 "/src/checker-isolation.do"
        return ((std::string("calls non-isolated function \"") + reason->name) + std::string("\""));
    }
#line 304 "/src/checker-isolation.do"
    return ((std::string("uses bodyless function \"") + reason->name) + std::string("\" without an isolated contract"));
}
#line 307 "/src/checker-isolation.do"
::app_src_semantic_::SemanticSpan semanticSpan(::app_src_ast_::SourceSpan span) {
#line 308 "/src/checker-isolation.do"
    return ::app_src_semantic_::SemanticSpan{::app_src_semantic_::SemanticLocation{span.start.line, span.start.column, span.start.offset}, ::app_src_semantic_::SemanticLocation{span.end.line, span.end.column, span.end.offset}};
}
#line 314 "/src/checker-isolation.do"
void pushDiagnostic(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics, const std::string& module, ::app_src_ast_::SourceSpan span, const std::string& message) {
#line 315 "/src/checker-isolation.do"
    diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, semanticSpan(span), module, std::string("")));
}
#line 318 "/src/checker-isolation.do"
std::shared_ptr<IsolationReason> probeReason(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<IsolationGraph>& graph, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 319 "/src/checker-isolation.do"
    const auto& _iterable_50 = allExpressions(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{expression}));
    for (const auto& nested : *_iterable_50) {
#line 320 "/src/checker-isolation.do"
        auto reason = mutableModuleReason(result, nested);
#line 321 "/src/checker-isolation.do"
        if (doof::is_null(reason)) {
#line 321 "/src/checker-isolation.do"
            (reason = mutableStaticReason(result, nested));
        }
#line 322 "/src/checker-isolation.do"
        if (!doof::is_null(reason)) {
#line 322 "/src/checker-isolation.do"
            return reason;
        }
#line 323 "/src/checker-isolation.do"
        {
            auto _case_subject = nested;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
                const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 325 "/src/checker-isolation.do"
                const auto declaration = callDeclaration(result, call);
#line 326 "/src/checker-isolation.do"
                if (!doof::is_null(declaration)) {
#line 327 "/src/checker-isolation.do"
                    const auto& _iterable_52 = nodesForDeclaration(result, graph, doof::unwrap_optional(declaration));
                    for (const auto& target : *_iterable_52) {
#line 328 "/src/checker-isolation.do"
                        if (!doof::is_null(target->reason)) {
#line 329 "/src/checker-isolation.do"
                            return std::make_shared<IsolationReason>(std::string("call"), target->declaration->name, call->span);
                        }
                    }
                }
        }
        else {
        }
        }
    }
#line 337 "/src/checker-isolation.do"
    return nullptr;
}
#line 340 "/src/checker-isolation.do"
std::shared_ptr<IsolationReason> actorConstructionReason(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<IsolationGraph>& graph, const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& actor) {
#line 341 "/src/checker-isolation.do"
    if (doof::is_null(actor->resolvedType)) {
#line 341 "/src/checker-isolation.do"
        return nullptr;
    }
#line 342 "/src/checker-isolation.do"
    std::shared_ptr<::app_src_ast_::ClassDeclaration> class_ = nullptr;
#line 343 "/src/checker-isolation.do"
    {
        auto _case_subject = doof::unwrap_optional(actor->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actorType_ = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 345 "/src/checker-isolation.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(result, actorType_->innerClass->symbol);
#line 346 "/src/checker-isolation.do"
            if (!doof::is_null(declaration)) {
#line 347 "/src/checker-isolation.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& resolved = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 348 "/src/checker-isolation.do"
                        (class_ = resolved);
                }
                else {
                }
                }
            }
    }
    else {
    }
    }
#line 355 "/src/checker-isolation.do"
    if (doof::is_null(class_)) {
#line 355 "/src/checker-isolation.do"
        return nullptr;
    }
#line 356 "/src/checker-isolation.do"
    const auto& _iterable_54 = class_->methods;
    for (const auto& method : *_iterable_54) {
#line 357 "/src/checker-isolation.do"
        if (method->static_ && (method->name == std::string("constructor"))) {
#line 358 "/src/checker-isolation.do"
            const auto node = nodeForDeclaration(graph, method);
#line 359 "/src/checker-isolation.do"
            if ((!doof::is_null(node)) && (!doof::is_null(node->reason))) {
#line 360 "/src/checker-isolation.do"
                return std::make_shared<IsolationReason>(std::string("call"), method->name, actor->span);
            }
#line 362 "/src/checker-isolation.do"
            return nullptr;
        }
    }
#line 365 "/src/checker-isolation.do"
    auto positionalIndex = 0;
#line 366 "/src/checker-isolation.do"
    const auto& _iterable_56 = class_->fields;
    for (const auto& field : *_iterable_56) {
#line 367 "/src/checker-isolation.do"
        if (field->static_) {
#line 367 "/src/checker-isolation.do"
            continue;
        }
#line 368 "/src/checker-isolation.do"
        if ((positionalIndex >= static_cast<int32_t>((actor->args)->size())) && (!doof::is_null(field->defaultValue))) {
#line 369 "/src/checker-isolation.do"
            const auto reason = probeReason(result, graph, doof::unwrap_optional(field->defaultValue));
#line 370 "/src/checker-isolation.do"
            if (!doof::is_null(reason)) {
#line 370 "/src/checker-isolation.do"
                return reason;
            }
        }
#line 372 "/src/checker-isolation.do"
        (positionalIndex = (positionalIndex + 1));
    }
#line 374 "/src/checker-isolation.do"
    return nullptr;
}
#line 377 "/src/checker-isolation.do"
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> moduleExpressions(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module) {
#line 378 "/src/checker-isolation.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> roots = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 379 "/src/checker-isolation.do"
    const auto& _iterable_58 = module->program->statements;
    for (const auto& raw : *_iterable_58) {
#line 380 "/src/checker-isolation.do"
        const auto statement = unwrapExport(raw);
#line 381 "/src/checker-isolation.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 383 "/src/checker-isolation.do"
                const auto& _iterable_60 = functionExpressionRoots(fn);
                for (const auto& expression : *_iterable_60) {
#line 383 "/src/checker-isolation.do"
                    roots->push_back(expression);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 386 "/src/checker-isolation.do"
                const auto& _iterable_62 = class_->fields;
                for (const auto& field : *_iterable_62) {
#line 386 "/src/checker-isolation.do"
                    if (!doof::is_null(field->defaultValue)) {
#line 386 "/src/checker-isolation.do"
                        roots->push_back(doof::unwrap_optional(field->defaultValue));
                    }
                }
#line 387 "/src/checker-isolation.do"
                const auto& _iterable_64 = class_->methods;
                for (const auto& method : *_iterable_64) {
#line 388 "/src/checker-isolation.do"
                    const auto& _iterable_66 = functionExpressionRoots(method);
                    for (const auto& expression : *_iterable_66) {
#line 388 "/src/checker-isolation.do"
                        roots->push_back(expression);
                    }
                }
        }
        else {
#line 391 "/src/checker-isolation.do"
                ::app_src_checker_actor_lifecycle_::collectStatementExpressions(statement, roots);
        }
        }
    }
#line 394 "/src/checker-isolation.do"
    return allExpressions(roots);
}
#line 397 "/src/checker-isolation.do"
void validateModuleIsolationEffects(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<IsolationGraph>& graph, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 398 "/src/checker-isolation.do"
    const auto& _iterable_68 = graph->nodes;
    for (const auto& node : *_iterable_68) {
#line 399 "/src/checker-isolation.do"
        if (((node->module != module->path) || !node->declaration->isolated_) || doof::is_null(node->reason)) {
#line 399 "/src/checker-isolation.do"
            continue;
        }
#line 400 "/src/checker-isolation.do"
        const auto owner = ((node->owner == std::string("")) ? ((std::string("function \"") + node->declaration->name) + std::string("\"")) : ((((std::string("method \"") + node->owner) + std::string(".")) + node->declaration->name) + std::string("\"")));
#line 401 "/src/checker-isolation.do"
        const auto message = ((node->reason->kind == std::string("call")) ? ((((std::string("Isolated ") + owner) + std::string(" cannot call non-isolated function \"")) + node->reason->name) + std::string("\"")) : (((std::string("Isolated ") + owner) + std::string(" is not isolated: ")) + reasonText(doof::unwrap_optional(node->reason))));
#line 404 "/src/checker-isolation.do"
        pushDiagnostic(diagnostics, module->path, node->reason->span, message);
    }
#line 407 "/src/checker-isolation.do"
    const auto& _iterable_70 = moduleExpressions(module);
    for (const auto& expression : *_iterable_70) {
#line 408 "/src/checker-isolation.do"
        {
            auto _case_subject = expression;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
                const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
#line 410 "/src/checker-isolation.do"
                {
                    auto _case_subject = async_->expression;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
#line 412 "/src/checker-isolation.do"
                        ::app_src_checker_async_::validateAsyncBlock(result, async_, module->path, diagnostics);
#line 413 "/src/checker-isolation.do"
                        const auto reason = probeReason(result, graph, doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(async_));
#line 414 "/src/checker-isolation.do"
                        if (!doof::is_null(reason)) {
#line 415 "/src/checker-isolation.do"
                            pushDiagnostic(diagnostics, module->path, reason->span, (std::string("Async block is not isolated: ") + reasonText(doof::unwrap_optional(reason))));
                        }
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 420 "/src/checker-isolation.do"
                        auto actorCall = false;
#line 421 "/src/checker-isolation.do"
                        {
                            auto _case_subject = inner;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
                                const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 423 "/src/checker-isolation.do"
                                {
                                    auto _case_subject = call->callee;
                                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                                        const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 425 "/src/checker-isolation.do"
                                        if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 426 "/src/checker-isolation.do"
                                            {
                                                auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                                                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
#line 427 "/src/checker-isolation.do"
                                                    (actorCall = true);
                                            }
                                            else {
                                            }
                                            }
                                        }
                                }
                                else {
                                }
                                }
                        }
                        else {
                        }
                        }
#line 437 "/src/checker-isolation.do"
                        if (!actorCall) {
#line 438 "/src/checker-isolation.do"
                            const auto reason = probeReason(result, graph, inner);
#line 439 "/src/checker-isolation.do"
                            if (!doof::is_null(reason)) {
#line 440 "/src/checker-isolation.do"
                                pushDiagnostic(diagnostics, module->path, reason->span, (std::string("Async call is not isolated: ") + reasonText(doof::unwrap_optional(reason))));
                            }
                        }
                }
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
                const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 448 "/src/checker-isolation.do"
                {
                    auto _case_subject = call->callee;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                        const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 450 "/src/checker-isolation.do"
                        if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 451 "/src/checker-isolation.do"
                            {
                                auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
#line 453 "/src/checker-isolation.do"
                                    if (!doof::is_null(call->resolvedFunction)) {
#line 454 "/src/checker-isolation.do"
                                        const auto target = nodeForDeclaration(graph, doof::unwrap_optional(call->resolvedFunction));
#line 455 "/src/checker-isolation.do"
                                        if ((!doof::is_null(target)) && (!doof::is_null(target->reason))) {
#line 456 "/src/checker-isolation.do"
                                            pushDiagnostic(diagnostics, module->path, call->span, (((std::string("Actor method \"") + target->declaration->name) + std::string("\" is not isolated: ")) + reasonText(doof::unwrap_optional(target->reason))));
                                        }
                                    }
                            }
                            else {
                            }
                            }
                        }
                }
                else {
                }
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
                const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
#line 469 "/src/checker-isolation.do"
                const auto reason = actorConstructionReason(result, graph, actor);
#line 470 "/src/checker-isolation.do"
                if (!doof::is_null(reason)) {
#line 471 "/src/checker-isolation.do"
                    pushDiagnostic(diagnostics, module->path, actor->span, (((std::string("Actor<") + actor->className) + std::string("> construction is not isolated: ")) + reasonText(doof::unwrap_optional(reason))));
                }
        }
        else {
        }
        }
    }
}
#line 481 "/src/checker-isolation.do"
void validateIsolationEffects(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 482 "/src/checker-isolation.do"
    const auto graph = collectGraph(result);
#line 483 "/src/checker-isolation.do"
    inferIsolation(result, graph);
#line 484 "/src/checker-isolation.do"
    const auto& _iterable_72 = result->modules;
    for (const auto& module : *_iterable_72) {
#line 485 "/src/checker-isolation.do"
        validateModuleIsolationEffects(result, graph, module, diagnostics);
    }
}
#line 1 "<doof-generated>"
}
