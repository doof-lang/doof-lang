#include "src_emitter_worldview.hpp"

namespace app_src_emitter_worldview_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_worldview_walk_;
using namespace ::app_src_semantic_;





#line 56 "/src/emitter-worldview.do"
std::shared_ptr<WorldviewPlan> planWorldview(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& rootPath, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::shared_ptr<WorldviewGraphIndex>& graphIndex) {
#line 62 "/src/emitter-worldview.do"
    const auto index = std::make_shared<WorldviewIndex>((doof::is_null(graphIndex) ? indexWorldviewGraph(result) : doof::unwrap_optional(graphIndex)), std::make_shared<doof::ordered_map<std::string, std::shared_ptr<WorldviewSelection>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<WorldviewSelection>>>{}), std::make_shared<std::vector<std::shared_ptr<WorldviewSelection>>>(std::vector<std::shared_ptr<WorldviewSelection>>{}), std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{}), std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{}), std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{}));
#line 63 "/src/emitter-worldview.do"
    const auto root = findModule(index, rootPath);
#line 64 "/src/emitter-worldview.do"
    if (doof::is_null(root)) {
#line 64 "/src/emitter-worldview.do"
        return std::make_shared<WorldviewPlan>(std::make_shared<std::vector<std::shared_ptr<WorldviewModule>>>(std::vector<std::shared_ptr<WorldviewModule>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
#line 68 "/src/emitter-worldview.do"
    const auto& _iterable_2 = root->program->statements;
    for (const auto& statement : *_iterable_2) {
#line 69 "/src/emitter-worldview.do"
        collectStatementSurface(statement, rootPath, index, false);
#line 70 "/src/emitter-worldview.do"
        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> expressions = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 71 "/src/emitter-worldview.do"
        ::app_src_emitter_worldview_walk_::collectWorldviewStatementExpressions(statement, expressions);
#line 72 "/src/emitter-worldview.do"
        const auto& _iterable_4 = expressions;
        for (const auto& expression : *_iterable_4) {
#line 72 "/src/emitter-worldview.do"
            collectExpressionTree(expression, rootPath, index);
        }
    }
#line 77 "/src/emitter-worldview.do"
    const auto& _iterable_6 = root->symbols;
    for (const auto& symbol : *_iterable_6) {
#line 78 "/src/emitter-worldview.do"
        if (symbol->native_ && (symbol->nativeHeader != std::string(""))) {
#line 79 "/src/emitter-worldview.do"
            collectSymbol(symbol, rootPath, index);
        }
    }
#line 84 "/src/emitter-worldview.do"
    const auto& _iterable_8 = root->exports;
    for (const auto& symbol : *_iterable_8) {
#line 85 "/src/emitter-worldview.do"
        if ((symbol->module != std::string("")) && (symbol->module != rootPath)) {
#line 86 "/src/emitter-worldview.do"
            collectSymbol(symbol, rootPath, index);
        }
    }
#line 90 "/src/emitter-worldview.do"
    if (!doof::is_null(instantiations)) {
#line 91 "/src/emitter-worldview.do"
        const auto& _iterable_10 = instantiations->interfaces;
        for (const auto& interface_ : *_iterable_10) {
#line 92 "/src/emitter-worldview.do"
            if (!(index->interfaceKeySet->count(interface_->key) > 0)) {
#line 92 "/src/emitter-worldview.do"
                continue;
            }
#line 93 "/src/emitter-worldview.do"
            const auto& _iterable_12 = interface_->implementations;
            for (const auto& implementation : *_iterable_12) {
#line 94 "/src/emitter-worldview.do"
                auto name = implementation->typeName;
#line 95 "/src/emitter-worldview.do"
                const auto& _iterable_14 = instantiations->classes;
                for (const auto& class_ : *_iterable_14) {
#line 96 "/src/emitter-worldview.do"
                    if ((class_->modulePath == implementation->modulePath) && (class_->emittedName == implementation->typeName)) {
#line 97 "/src/emitter-worldview.do"
                        (name = class_->declaration->name);
#line 98 "/src/emitter-worldview.do"
                        break;
                    }
                }
#line 101 "/src/emitter-worldview.do"
                const auto module = findModule(index, implementation->modulePath);
#line 102 "/src/emitter-worldview.do"
                if (doof::is_null(module)) {
#line 102 "/src/emitter-worldview.do"
                    continue;
                }
#line 103 "/src/emitter-worldview.do"
                const auto symbol = findSymbol(index, implementation->modulePath, name);
#line 104 "/src/emitter-worldview.do"
                if (!doof::is_null(symbol)) {
#line 104 "/src/emitter-worldview.do"
                    collectSymbol(doof::unwrap_optional(symbol), rootPath, index);
                }
            }
        }
    }
#line 109 "/src/emitter-worldview.do"
    const auto plan = std::make_shared<WorldviewPlan>(std::make_shared<std::vector<std::shared_ptr<WorldviewModule>>>(std::vector<std::shared_ptr<WorldviewModule>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 110 "/src/emitter-worldview.do"
    (plan->interfaceKeys = index->interfaceKeys);
#line 114 "/src/emitter-worldview.do"
    const auto& _iterable_16 = result->modules;
    for (const auto& info : *_iterable_16) {
#line 115 "/src/emitter-worldview.do"
        if ((info->path != rootPath) && (!doof::is_null(findSelection(index, info->path)))) {
#line 116 "/src/emitter-worldview.do"
            appendWorldviewModule(index, info->path, rootPath, plan);
        }
    }
#line 119 "/src/emitter-worldview.do"
    appendWorldviewModule(index, rootPath, rootPath, plan);
#line 120 "/src/emitter-worldview.do"
    return plan;
}
#line 123 "/src/emitter-worldview.do"
void appendWorldviewModule(const std::shared_ptr<WorldviewIndex>& index, const std::string& path, const std::string& rootPath, const std::shared_ptr<WorldviewPlan>& plan) {
#line 129 "/src/emitter-worldview.do"
    if ((index->visitedPaths->count(path) > 0) || (index->visitingPaths->count(path) > 0)) {
#line 129 "/src/emitter-worldview.do"
        return;
    }
#line 130 "/src/emitter-worldview.do"
    const auto info = findModule(index, path);
#line 131 "/src/emitter-worldview.do"
    if (doof::is_null(info)) {
#line 131 "/src/emitter-worldview.do"
        return;
    }
#line 132 "/src/emitter-worldview.do"
    const auto selection = findSelection(index, path);
#line 133 "/src/emitter-worldview.do"
    if ((path != rootPath) && (doof::is_null(selection) || (static_cast<int32_t>((selection->statements)->size()) == 0))) {
#line 133 "/src/emitter-worldview.do"
        return;
    }
#line 134 "/src/emitter-worldview.do"
    index->visitingPaths->insert(path);
#line 135 "/src/emitter-worldview.do"
    const auto& _iterable_18 = info->imports;
    for (const auto& imported : *_iterable_18) {
#line 136 "/src/emitter-worldview.do"
        if (imported->sourceModule != rootPath) {
#line 137 "/src/emitter-worldview.do"
            appendWorldviewModule(index, imported->sourceModule, rootPath, plan);
        }
    }
#line 140 "/src/emitter-worldview.do"
    const auto& _iterable_20 = info->reExports;
    for (const auto& reExport : *_iterable_20) {
#line 141 "/src/emitter-worldview.do"
        if (reExport != rootPath) {
#line 141 "/src/emitter-worldview.do"
            appendWorldviewModule(index, reExport, rootPath, plan);
        }
    }
#line 143 "/src/emitter-worldview.do"
    index->visitingPaths->erase(path);
#line 144 "/src/emitter-worldview.do"
    if (index->visitedPaths->count(path) > 0) {
#line 144 "/src/emitter-worldview.do"
        return;
    }
#line 145 "/src/emitter-worldview.do"
    index->visitedPaths->insert(path);
#line 146 "/src/emitter-worldview.do"
    if (path == rootPath) {
#line 147 "/src/emitter-worldview.do"
        plan->modules->push_back(std::make_shared<WorldviewModule>(path, info->program));
    } else {
#line 149 "/src/emitter-worldview.do"
        const auto ordered = orderedSelectionStatements(doof::unwrap_optional(info), doof::unwrap_optional(selection));
#line 150 "/src/emitter-worldview.do"
        plan->modules->push_back(std::make_shared<WorldviewModule>(path, std::make_shared<::app_src_ast_::Program>(info->program->kind, ordered, info->program->span)));
    }
}
#line 157 "/src/emitter-worldview.do"
void addInterfaceKey(const std::shared_ptr<WorldviewIndex>& index, const std::string& value) {
#line 158 "/src/emitter-worldview.do"
    if (index->interfaceKeySet->count(value) > 0) {
#line 158 "/src/emitter-worldview.do"
        return;
    }
#line 159 "/src/emitter-worldview.do"
    index->interfaceKeySet->insert(value);
#line 160 "/src/emitter-worldview.do"
    index->interfaceKeys->push_back(value);
}
#line 163 "/src/emitter-worldview.do"
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>> orderedSelectionStatements(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<WorldviewSelection>& selection) {
#line 164 "/src/emitter-worldview.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>> ordered = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>{});
#line 165 "/src/emitter-worldview.do"
    std::shared_ptr<doof::ordered_set<std::string>> selectedNames = std::make_shared<doof::ordered_set<std::string>>(doof::ordered_set<std::string>{});
#line 166 "/src/emitter-worldview.do"
    const auto& _iterable_22 = selection->statements;
    for (const auto& selected : *_iterable_22) {
#line 166 "/src/emitter-worldview.do"
        selectedNames->insert(statementName(selected));
    }
#line 167 "/src/emitter-worldview.do"
    const auto& _iterable_24 = info->program->statements;
    for (const auto& candidate : *_iterable_24) {
#line 168 "/src/emitter-worldview.do"
        const auto name = statementName(candidate);
#line 169 "/src/emitter-worldview.do"
        if ((name != std::string("")) && (selectedNames->count(name) > 0)) {
#line 169 "/src/emitter-worldview.do"
            ordered->push_back(candidate);
        }
    }
#line 171 "/src/emitter-worldview.do"
    return ordered;
}
#line 174 "/src/emitter-worldview.do"
void collectExpressionTree(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::string& rootPath, const std::shared_ptr<WorldviewIndex>& index) {
#line 182 "/src/emitter-worldview.do"
    auto expressions = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{expression});
#line 183 "/src/emitter-worldview.do"
    auto cursor = 0;
#line 184 "/src/emitter-worldview.do"
    while (cursor < static_cast<int32_t>((expressions)->size())) {
#line 185 "/src/emitter-worldview.do"
        const auto current = doof::array_at(expressions, cursor, "src/emitter-worldview", 185);
#line 186 "/src/emitter-worldview.do"
        (cursor = (cursor + 1));
#line 187 "/src/emitter-worldview.do"
        if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, current))) {
#line 187 "/src/emitter-worldview.do"
            collectType(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, current)), rootPath, index);
        }
#line 188 "/src/emitter-worldview.do"
        {
            auto _case_subject = current;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 190 "/src/emitter-worldview.do"
                if ((!doof::is_null(identifier->resolvedBinding)) && (!doof::is_null(identifier->resolvedBinding->symbol))) {
#line 191 "/src/emitter-worldview.do"
                    collectSymbol(doof::unwrap_optional(identifier->resolvedBinding->symbol), rootPath, index);
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 195 "/src/emitter-worldview.do"
                if (!doof::is_null(member->resolvedNamespaceSymbol)) {
#line 196 "/src/emitter-worldview.do"
                    collectSymbol(doof::unwrap_optional(member->resolvedNamespaceSymbol), rootPath, index);
                }
#line 198 "/src/emitter-worldview.do"
                if ((!doof::is_null(member->resolvedStaticOwner)) && (!doof::is_null(member->resolvedStaticOwner->resolvedSymbol))) {
#line 199 "/src/emitter-worldview.do"
                    collectSymbol(doof::unwrap_optional(member->resolvedStaticOwner->resolvedSymbol), rootPath, index);
                }
        }
        else {
        }
        }
#line 204 "/src/emitter-worldview.do"
        ::app_src_emitter_worldview_walk_::collectWorldviewNestedExpressions(current, expressions);
    }
}
#line 208 "/src/emitter-worldview.do"
void collectType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& rootPath, const std::shared_ptr<WorldviewIndex>& index) {
#line 213 "/src/emitter-worldview.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 215 "/src/emitter-worldview.do"
            collectSymbol(class_->symbol, rootPath, index);
#line 216 "/src/emitter-worldview.do"
            const auto& _iterable_26 = class_->typeArgs;
            for (const auto& argument : *_iterable_26) {
#line 216 "/src/emitter-worldview.do"
                collectType(argument, rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 218 "/src/emitter-worldview.do"
            collectSymbol(enum_->symbol, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 220 "/src/emitter-worldview.do"
            collectSymbol(interface_->symbol, rootPath, index);
#line 221 "/src/emitter-worldview.do"
            if (static_cast<int32_t>((interface_->typeArgs)->size()) > 0) {
#line 222 "/src/emitter-worldview.do"
                addInterfaceKey(index, ::app_src_emitter_monomorphize_::interfaceInstantiationKey(interface_->symbol->module, interface_->name, interface_->typeArgs));
            }
#line 224 "/src/emitter-worldview.do"
            const auto& _iterable_28 = interface_->symbol->implementations;
            for (const auto& implementation : *_iterable_28) {
#line 225 "/src/emitter-worldview.do"
                collectSymbol(implementation, rootPath, index);
            }
#line 227 "/src/emitter-worldview.do"
            const auto& _iterable_30 = interface_->typeArgs;
            for (const auto& argument : *_iterable_30) {
#line 227 "/src/emitter-worldview.do"
                collectType(argument, rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 229 "/src/emitter-worldview.do"
            collectType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 230 "/src/emitter-worldview.do"
            collectType(promise->valueType, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 231 "/src/emitter-worldview.do"
            collectType(array->elementType, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 233 "/src/emitter-worldview.do"
            collectType(map->keyType, rootPath, index);
#line 234 "/src/emitter-worldview.do"
            collectType(map->valueType, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 236 "/src/emitter-worldview.do"
            collectType(set_->elementType, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 238 "/src/emitter-worldview.do"
            addInterfaceKey(index, ::app_src_emitter_monomorphize_::interfaceInstantiationKey(std::string(""), std::string("Stream"), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{stream->elementType})));
#line 239 "/src/emitter-worldview.do"
            collectType(stream->elementType, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 242 "/src/emitter-worldview.do"
            collectType(result_->valueType, rootPath, index);
#line 243 "/src/emitter-worldview.do"
            collectType(result_->errorType, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 245 "/src/emitter-worldview.do"
            const auto& _iterable_32 = tuple->elements;
            for (const auto& element : *_iterable_32) {
#line 245 "/src/emitter-worldview.do"
                collectType(element, rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 246 "/src/emitter-worldview.do"
            const auto& _iterable_34 = union_->types;
            for (const auto& member : *_iterable_34) {
#line 246 "/src/emitter-worldview.do"
                collectType(member, rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 247 "/src/emitter-worldview.do"
            collectType(weak_->inner, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 249 "/src/emitter-worldview.do"
            const auto& _iterable_36 = function_->params;
            for (const auto& parameter : *_iterable_36) {
#line 249 "/src/emitter-worldview.do"
                collectType(parameter->type_, rootPath, index);
            }
#line 250 "/src/emitter-worldview.do"
            collectType(function_->returnType, rootPath, index);
    }
    else {
    }
    }
}
#line 256 "/src/emitter-worldview.do"
void collectSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& rootPath, const std::shared_ptr<WorldviewIndex>& index) {
#line 261 "/src/emitter-worldview.do"
    if (symbol->module == std::string("")) {
#line 261 "/src/emitter-worldview.do"
        return;
    }
#line 262 "/src/emitter-worldview.do"
    const auto name = ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
#line 263 "/src/emitter-worldview.do"
    const auto key = ((((symbol->module + std::string("::")) + symbol->kind) + std::string("::")) + name);
#line 264 "/src/emitter-worldview.do"
    if (index->selectedKeys->count(key) > 0) {
#line 264 "/src/emitter-worldview.do"
        return;
    }
#line 265 "/src/emitter-worldview.do"
    index->selectedKeys->insert(key);
#line 266 "/src/emitter-worldview.do"
    if (symbol->module == rootPath) {
#line 267 "/src/emitter-worldview.do"
        collectNativeHeaderClosure(symbol, rootPath, index);
#line 268 "/src/emitter-worldview.do"
        return;
    }
#line 270 "/src/emitter-worldview.do"
    const auto declaration = declarationFor(index, symbol->module, name);
#line 271 "/src/emitter-worldview.do"
    if (doof::is_null(declaration)) {
#line 271 "/src/emitter-worldview.do"
        return;
    }
#line 272 "/src/emitter-worldview.do"
    const auto selection = selectionFor(index, symbol->module);
#line 273 "/src/emitter-worldview.do"
    selection->statements->push_back(doof::unwrap_optional(declaration));
#line 274 "/src/emitter-worldview.do"
    collectStatementSurface(doof::unwrap_optional(declaration), rootPath, index, true);
#line 278 "/src/emitter-worldview.do"
    collectNativeHeaderClosure(symbol, rootPath, index);
}
#line 281 "/src/emitter-worldview.do"
void collectNativeHeaderClosure(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& rootPath, const std::shared_ptr<WorldviewIndex>& index) {
#line 286 "/src/emitter-worldview.do"
    if (symbol->native_ && (symbol->nativeHeader != std::string(""))) {
#line 287 "/src/emitter-worldview.do"
        const auto module = findModule(index, symbol->module);
#line 288 "/src/emitter-worldview.do"
        if (!doof::is_null(module)) {
#line 289 "/src/emitter-worldview.do"
            const auto& _iterable_38 = module->symbols;
            for (const auto& sibling : *_iterable_38) {
#line 290 "/src/emitter-worldview.do"
                if (sibling->native_ && (sibling->nativeHeader == symbol->nativeHeader)) {
#line 291 "/src/emitter-worldview.do"
                    collectSymbol(sibling, rootPath, index);
                }
            }
#line 297 "/src/emitter-worldview.do"
            const auto& _iterable_40 = module->imports;
            for (const auto& imported : *_iterable_40) {
#line 298 "/src/emitter-worldview.do"
                if ((!doof::is_null(imported->symbol)) && isNominalSurfaceSymbol(doof::unwrap_optional(imported->symbol))) {
#line 299 "/src/emitter-worldview.do"
                    collectSymbol(doof::unwrap_optional(imported->symbol), rootPath, index);
                }
            }
#line 302 "/src/emitter-worldview.do"
            const auto& _iterable_42 = module->exports;
            for (const auto& exported : *_iterable_42) {
#line 303 "/src/emitter-worldview.do"
                if (isNominalSurfaceSymbol(exported)) {
#line 303 "/src/emitter-worldview.do"
                    collectSymbol(exported, rootPath, index);
                }
            }
#line 305 "/src/emitter-worldview.do"
            const auto& _iterable_44 = module->reExports;
            for (const auto& reExportPath : *_iterable_44) {
#line 306 "/src/emitter-worldview.do"
                const auto reExported = findModule(index, reExportPath);
#line 307 "/src/emitter-worldview.do"
                if (doof::is_null(reExported)) {
#line 307 "/src/emitter-worldview.do"
                    continue;
                }
#line 308 "/src/emitter-worldview.do"
                const auto& _iterable_46 = reExported->exports;
                for (const auto& exported : *_iterable_46) {
#line 309 "/src/emitter-worldview.do"
                    if (isNominalSurfaceSymbol(exported)) {
#line 309 "/src/emitter-worldview.do"
                        collectSymbol(exported, rootPath, index);
                    }
                }
            }
        }
    }
}
#line 316 "/src/emitter-worldview.do"
bool isNominalSurfaceSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 317 "/src/emitter-worldview.do"
    return (((((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("enum"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("type-alias")));
}
#line 321 "/src/emitter-worldview.do"
void collectStatementSurface(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::string& rootPath, const std::shared_ptr<WorldviewIndex>& index, bool foreign) {
#line 327 "/src/emitter-worldview.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 328 "/src/emitter-worldview.do"
            collectStatementSurface(export_->declaration, rootPath, index, foreign);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 330 "/src/emitter-worldview.do"
            if (!doof::is_null(fn->resolvedType)) {
#line 330 "/src/emitter-worldview.do"
                collectType(doof::unwrap_optional(fn->resolvedType), rootPath, index);
            }
#line 331 "/src/emitter-worldview.do"
            if (!doof::is_null(fn->returnType)) {
#line 331 "/src/emitter-worldview.do"
                collectAnnotationAliases(doof::unwrap_optional(fn->returnType), rootPath, index);
            }
#line 332 "/src/emitter-worldview.do"
            const auto& _iterable_48 = fn->params;
            for (const auto& parameter : *_iterable_48) {
#line 333 "/src/emitter-worldview.do"
                if (!doof::is_null(parameter->resolvedType)) {
#line 333 "/src/emitter-worldview.do"
                    collectType(doof::unwrap_optional(parameter->resolvedType), rootPath, index);
                }
#line 334 "/src/emitter-worldview.do"
                if (!doof::is_null(parameter->type_)) {
#line 334 "/src/emitter-worldview.do"
                    collectAnnotationAliases(doof::unwrap_optional(parameter->type_), rootPath, index);
                }
#line 335 "/src/emitter-worldview.do"
                if (!doof::is_null(parameter->defaultValue)) {
#line 335 "/src/emitter-worldview.do"
                    collectExpressionTree(doof::unwrap_optional(parameter->defaultValue), rootPath, index);
                }
            }
#line 337 "/src/emitter-worldview.do"
            if (!foreign) {
#line 337 "/src/emitter-worldview.do"
                collectFunctionBody(fn, rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 340 "/src/emitter-worldview.do"
            const auto& _iterable_50 = class_->fields;
            for (const auto& field : *_iterable_50) {
#line 341 "/src/emitter-worldview.do"
                if (!doof::is_null(field->resolvedType)) {
#line 341 "/src/emitter-worldview.do"
                    collectType(doof::unwrap_optional(field->resolvedType), rootPath, index);
                }
#line 342 "/src/emitter-worldview.do"
                if (!doof::is_null(field->type_)) {
#line 342 "/src/emitter-worldview.do"
                    collectAnnotationAliases(doof::unwrap_optional(field->type_), rootPath, index);
                }
#line 343 "/src/emitter-worldview.do"
                if (!doof::is_null(field->defaultValue)) {
#line 343 "/src/emitter-worldview.do"
                    collectExpressionTree(doof::unwrap_optional(field->defaultValue), rootPath, index);
                }
            }
#line 345 "/src/emitter-worldview.do"
            const auto& _iterable_52 = class_->methods;
            for (const auto& method : *_iterable_52) {
#line 346 "/src/emitter-worldview.do"
                if (!doof::is_null(method->resolvedType)) {
#line 346 "/src/emitter-worldview.do"
                    collectType(doof::unwrap_optional(method->resolvedType), rootPath, index);
                }
#line 347 "/src/emitter-worldview.do"
                if (!doof::is_null(method->returnType)) {
#line 347 "/src/emitter-worldview.do"
                    collectAnnotationAliases(doof::unwrap_optional(method->returnType), rootPath, index);
                }
#line 348 "/src/emitter-worldview.do"
                const auto& _iterable_54 = method->params;
                for (const auto& parameter : *_iterable_54) {
#line 349 "/src/emitter-worldview.do"
                    if (!doof::is_null(parameter->resolvedType)) {
#line 349 "/src/emitter-worldview.do"
                        collectType(doof::unwrap_optional(parameter->resolvedType), rootPath, index);
                    }
#line 350 "/src/emitter-worldview.do"
                    if (!doof::is_null(parameter->type_)) {
#line 350 "/src/emitter-worldview.do"
                        collectAnnotationAliases(doof::unwrap_optional(parameter->type_), rootPath, index);
                    }
#line 351 "/src/emitter-worldview.do"
                    if (!doof::is_null(parameter->defaultValue)) {
#line 351 "/src/emitter-worldview.do"
                        collectExpressionTree(doof::unwrap_optional(parameter->defaultValue), rootPath, index);
                    }
                }
#line 353 "/src/emitter-worldview.do"
                if (!foreign) {
#line 353 "/src/emitter-worldview.do"
                    collectFunctionBody(method, rootPath, index);
                }
            }
#line 355 "/src/emitter-worldview.do"
            if (!doof::is_null(class_->resolvedSymbol)) {
#line 356 "/src/emitter-worldview.do"
                const auto& _iterable_56 = class_->resolvedSymbol->implementations;
                for (const auto& implementation : *_iterable_56) {
#line 357 "/src/emitter-worldview.do"
                    collectSymbol(implementation, rootPath, index);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 362 "/src/emitter-worldview.do"
            const auto& _iterable_58 = interface_->fields;
            for (const auto& field : *_iterable_58) {
#line 363 "/src/emitter-worldview.do"
                if (!doof::is_null(field->resolvedType)) {
#line 363 "/src/emitter-worldview.do"
                    collectType(doof::unwrap_optional(field->resolvedType), rootPath, index);
                }
#line 364 "/src/emitter-worldview.do"
                collectAnnotationAliases(field->type_, rootPath, index);
            }
#line 366 "/src/emitter-worldview.do"
            const auto& _iterable_60 = interface_->methods;
            for (const auto& method : *_iterable_60) {
#line 367 "/src/emitter-worldview.do"
                if (!doof::is_null(method->resolvedType)) {
#line 367 "/src/emitter-worldview.do"
                    collectType(doof::unwrap_optional(method->resolvedType), rootPath, index);
                }
#line 368 "/src/emitter-worldview.do"
                if (!doof::is_null(method->returnType)) {
#line 368 "/src/emitter-worldview.do"
                    collectAnnotationAliases(doof::unwrap_optional(method->returnType), rootPath, index);
                }
#line 369 "/src/emitter-worldview.do"
                const auto& _iterable_62 = method->params;
                for (const auto& parameter : *_iterable_62) {
#line 369 "/src/emitter-worldview.do"
                    if (!doof::is_null(parameter->type_)) {
#line 369 "/src/emitter-worldview.do"
                        collectAnnotationAliases(doof::unwrap_optional(parameter->type_), rootPath, index);
                    }
                }
            }
#line 371 "/src/emitter-worldview.do"
            if (!doof::is_null(interface_->resolvedSymbol)) {
#line 372 "/src/emitter-worldview.do"
                const auto& _iterable_64 = interface_->resolvedSymbol->implementations;
                for (const auto& implementation : *_iterable_64) {
#line 373 "/src/emitter-worldview.do"
                    collectSymbol(implementation, rootPath, index);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 378 "/src/emitter-worldview.do"
            if (!doof::is_null(alias->resolvedType)) {
#line 378 "/src/emitter-worldview.do"
                collectType(doof::unwrap_optional(alias->resolvedType), rootPath, index);
            }
#line 379 "/src/emitter-worldview.do"
            collectAnnotationAliases(alias->type_, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 382 "/src/emitter-worldview.do"
            if (!doof::is_null(const_->resolvedType)) {
#line 382 "/src/emitter-worldview.do"
                collectType(doof::unwrap_optional(const_->resolvedType), rootPath, index);
            }
#line 383 "/src/emitter-worldview.do"
            if (!doof::is_null(const_->type_)) {
#line 383 "/src/emitter-worldview.do"
                collectAnnotationAliases(doof::unwrap_optional(const_->type_), rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 386 "/src/emitter-worldview.do"
            if (!doof::is_null(readonly_->resolvedType)) {
#line 386 "/src/emitter-worldview.do"
                collectType(doof::unwrap_optional(readonly_->resolvedType), rootPath, index);
            }
#line 387 "/src/emitter-worldview.do"
            if (!doof::is_null(readonly_->type_)) {
#line 387 "/src/emitter-worldview.do"
                collectAnnotationAliases(doof::unwrap_optional(readonly_->type_), rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 390 "/src/emitter-worldview.do"
            if (!doof::is_null(binding->resolvedType)) {
#line 390 "/src/emitter-worldview.do"
                collectType(doof::unwrap_optional(binding->resolvedType), rootPath, index);
            }
#line 391 "/src/emitter-worldview.do"
            if (!doof::is_null(binding->type_)) {
#line 391 "/src/emitter-worldview.do"
                collectAnnotationAliases(doof::unwrap_optional(binding->type_), rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 394 "/src/emitter-worldview.do"
            const auto& _iterable_66 = enum_->variants;
            for (const auto& variant : *_iterable_66) {
#line 394 "/src/emitter-worldview.do"
                if (!doof::is_null(variant->value)) {
#line 394 "/src/emitter-worldview.do"
                    collectExpressionTree(doof::unwrap_optional(variant->value), rootPath, index);
                }
            }
    }
    else {
    }
    }
}
#line 400 "/src/emitter-worldview.do"
void collectAnnotationAliases(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::string& rootPath, const std::shared_ptr<WorldviewIndex>& index) {
#line 405 "/src/emitter-worldview.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 407 "/src/emitter-worldview.do"
            if ((!doof::is_null(named->resolvedSymbol)) && (named->resolvedSymbol->kind == std::string("type-alias"))) {
#line 408 "/src/emitter-worldview.do"
                collectSymbol(doof::unwrap_optional(named->resolvedSymbol), rootPath, index);
            }
#line 410 "/src/emitter-worldview.do"
            const auto& _iterable_68 = named->typeArgs;
            for (const auto& argument : *_iterable_68) {
#line 410 "/src/emitter-worldview.do"
                collectAnnotationAliases(argument, rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
#line 412 "/src/emitter-worldview.do"
            collectAnnotationAliases(array->elementType, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
#line 413 "/src/emitter-worldview.do"
            const auto& _iterable_70 = union_->types;
            for (const auto& member : *_iterable_70) {
#line 413 "/src/emitter-worldview.do"
                collectAnnotationAliases(member, rootPath, index);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
#line 415 "/src/emitter-worldview.do"
            const auto& _iterable_72 = function_->params;
            for (const auto& parameter : *_iterable_72) {
#line 415 "/src/emitter-worldview.do"
                collectAnnotationAliases(parameter->type_, rootPath, index);
            }
#line 416 "/src/emitter-worldview.do"
            collectAnnotationAliases(function_->returnType, rootPath, index);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
#line 418 "/src/emitter-worldview.do"
            collectAnnotationAliases(weak_->type_, rootPath, index);
    }
    }
}
#line 422 "/src/emitter-worldview.do"
void collectFunctionBody(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& rootPath, const std::shared_ptr<WorldviewIndex>& index) {
#line 427 "/src/emitter-worldview.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> expressions = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 428 "/src/emitter-worldview.do"
    {
        auto _case_subject = fn->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 429 "/src/emitter-worldview.do"
            ::app_src_emitter_worldview_walk_::collectWorldviewBlockExpressions(block, expressions);
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 430 "/src/emitter-worldview.do"
            expressions->push_back(expression);
    }
    }
#line 432 "/src/emitter-worldview.do"
    const auto& _iterable_74 = expressions;
    for (const auto& expression : *_iterable_74) {
#line 432 "/src/emitter-worldview.do"
        collectExpressionTree(expression, rootPath, index);
    }
}
#line 435 "/src/emitter-worldview.do"
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> declarationFor(const std::shared_ptr<WorldviewIndex>& index, const std::string& modulePath, const std::string& name) {
#line 436 "/src/emitter-worldview.do"
    auto _binding_value_75 = doof::map_get(index->graph->declarations, declarationKey(modulePath, name), "", 0);
    if (doof::is_failure(_binding_value_75)) {
        const auto& declaration = _binding_value_75;
#line 436 "/src/emitter-worldview.do"
        return std::monostate{};
    }
    const auto declaration = doof::success_value(_binding_value_75);
#line 437 "/src/emitter-worldview.do"
    return doof::optional_value(declaration);
}
#line 440 "/src/emitter-worldview.do"
std::string statementName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 441 "/src/emitter-worldview.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 442 "/src/emitter-worldview.do"
            return statementName(export_->declaration);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 443 "/src/emitter-worldview.do"
            return class_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 444 "/src/emitter-worldview.do"
            return fn->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 445 "/src/emitter-worldview.do"
            return interface_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 446 "/src/emitter-worldview.do"
            return enum_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 447 "/src/emitter-worldview.do"
            return alias->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 448 "/src/emitter-worldview.do"
            return const_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 449 "/src/emitter-worldview.do"
            return readonly_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 450 "/src/emitter-worldview.do"
            return binding->name;
    }
    else {
#line 451 "/src/emitter-worldview.do"
            return std::string("");
    }
    }
    doof::unreachable();
#line 453 "/src/emitter-worldview.do"
    return std::string("");
}
#line 456 "/src/emitter-worldview.do"
std::shared_ptr<WorldviewGraphIndex> indexWorldviewGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 457 "/src/emitter-worldview.do"
    const auto index = std::make_shared<WorldviewGraphIndex>(std::make_shared<doof::ordered_map<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<::app_src_analyzer_::ModuleInfo>>>{}), std::make_shared<doof::ordered_map<std::string, std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>(std::initializer_list<std::pair<std::string, std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>{}), std::make_shared<doof::ordered_map<std::string, std::shared_ptr<::app_src_semantic_::Symbol>>>(std::initializer_list<std::pair<std::string, std::shared_ptr<::app_src_semantic_::Symbol>>>{}));
#line 458 "/src/emitter-worldview.do"
    const auto& _iterable_77 = result->modules;
    for (const auto& module : *_iterable_77) {
#line 459 "/src/emitter-worldview.do"
        if (![&]() -> bool { auto _map_has_78 = index->modules; return _map_has_78->find(module->path) != _map_has_78->end(); }()) {
#line 459 "/src/emitter-worldview.do"
            doof::map_set(index->modules, module->path, module, "", 0);
        }
#line 460 "/src/emitter-worldview.do"
        const auto& _iterable_80 = module->program->statements;
        for (const auto& statement : *_iterable_80) {
#line 461 "/src/emitter-worldview.do"
            const auto name = statementName(statement);
#line 462 "/src/emitter-worldview.do"
            const auto key = declarationKey(module->path, name);
#line 463 "/src/emitter-worldview.do"
            if ((name != std::string("")) && ![&]() -> bool { auto _map_has_81 = index->declarations; return _map_has_81->find(key) != _map_has_81->end(); }()) {
#line 463 "/src/emitter-worldview.do"
                doof::map_set(index->declarations, key, statement, "", 0);
            }
        }
#line 465 "/src/emitter-worldview.do"
        const auto& _iterable_83 = module->symbols;
        for (const auto& symbol : *_iterable_83) {
#line 466 "/src/emitter-worldview.do"
            const auto name = ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
#line 467 "/src/emitter-worldview.do"
            const auto key = declarationKey(module->path, name);
#line 468 "/src/emitter-worldview.do"
            if (![&]() -> bool { auto _map_has_84 = index->symbols; return _map_has_84->find(key) != _map_has_84->end(); }()) {
#line 468 "/src/emitter-worldview.do"
                doof::map_set(index->symbols, key, symbol, "", 0);
            }
        }
    }
#line 471 "/src/emitter-worldview.do"
    return index;
}
#line 474 "/src/emitter-worldview.do"
std::string declarationKey(const std::string& modulePath, const std::string& name) {
#line 475 "/src/emitter-worldview.do"
    return ((modulePath + std::string("\n")) + name);
}
#line 478 "/src/emitter-worldview.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(const std::shared_ptr<WorldviewIndex>& index, const std::string& path) {
#line 479 "/src/emitter-worldview.do"
    auto _binding_value_85 = doof::map_get(index->graph->modules, path, "", 0);
    if (doof::is_failure(_binding_value_85)) {
        const auto& module = _binding_value_85;
#line 479 "/src/emitter-worldview.do"
        return nullptr;
    }
    const auto module = doof::success_value(_binding_value_85);
#line 480 "/src/emitter-worldview.do"
    return module;
}
#line 483 "/src/emitter-worldview.do"
std::shared_ptr<::app_src_semantic_::Symbol> findSymbol(const std::shared_ptr<WorldviewIndex>& index, const std::string& modulePath, const std::string& name) {
#line 484 "/src/emitter-worldview.do"
    auto _binding_value_86 = doof::map_get(index->graph->symbols, declarationKey(modulePath, name), "", 0);
    if (doof::is_failure(_binding_value_86)) {
        const auto& symbol = _binding_value_86;
#line 484 "/src/emitter-worldview.do"
        return nullptr;
    }
    const auto symbol = doof::success_value(_binding_value_86);
#line 485 "/src/emitter-worldview.do"
    return symbol;
}
#line 488 "/src/emitter-worldview.do"
std::shared_ptr<WorldviewSelection> selectionFor(const std::shared_ptr<WorldviewIndex>& index, const std::string& path) {
#line 489 "/src/emitter-worldview.do"
    const auto existing = findSelection(index, path);
#line 490 "/src/emitter-worldview.do"
    if (!doof::is_null(existing)) {
#line 490 "/src/emitter-worldview.do"
        return doof::unwrap_optional(existing);
    }
#line 491 "/src/emitter-worldview.do"
    const auto selection = std::make_shared<WorldviewSelection>(path, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>{}));
#line 492 "/src/emitter-worldview.do"
    doof::map_set(index->selections, path, selection, "", 0);
#line 493 "/src/emitter-worldview.do"
    index->selectionOrder->push_back(selection);
#line 494 "/src/emitter-worldview.do"
    return selection;
}
#line 497 "/src/emitter-worldview.do"
std::shared_ptr<WorldviewSelection> findSelection(const std::shared_ptr<WorldviewIndex>& index, const std::string& path) {
#line 498 "/src/emitter-worldview.do"
    auto _binding_value_87 = doof::map_get(index->selections, path, "", 0);
    if (doof::is_failure(_binding_value_87)) {
        const auto& selection = _binding_value_87;
#line 498 "/src/emitter-worldview.do"
        return nullptr;
    }
    const auto selection = doof::success_value(_binding_value_87);
#line 499 "/src/emitter-worldview.do"
    return selection;
}
#line 1 "<doof-generated>"
}
