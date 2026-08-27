#include "src_emitter_stmt.hpp"

namespace app_src_emitter_stmt_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_case_pattern_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_literals_;
using namespace ::app_src_emitter_types_;
#line 23 "/src/emitter-stmt.do"
std::string emitBlock(const std::shared_ptr<::app_src_ast_::Block>& block, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 24 "/src/emitter-stmt.do"
    auto result = std::string("");
#line 25 "/src/emitter-stmt.do"
    const auto& _iterable_2 = block->statements;
    for (const auto& statement : *_iterable_2) {
#line 26 "/src/emitter-stmt.do"
        (result = (result + emitStatement(statement, level, context)));
    }
#line 28 "/src/emitter-stmt.do"
    return result;
}
#line 31 "/src/emitter-stmt.do"
std::string emitStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 32 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 33 "/src/emitter-stmt.do"
    auto sourceMark = std::string("");
#line 34 "/src/emitter-stmt.do"
    if (((level > 0) && (std::visit([](auto&& _obj) { return _obj->kind; }, statement) != std::string("block"))) && (std::visit([](auto&& _obj) { return _obj->kind; }, statement) != std::string("mock-import-directive"))) {
#line 35 "/src/emitter-stmt.do"
        (sourceMark = ::app_src_emitter_context_::sourceLineDirective(std::visit([](auto&& _obj) { return _obj->span; }, statement), context));
    }
#line 37 "/src/emitter-stmt.do"
    auto coverageMark = std::string("");
#line 38 "/src/emitter-stmt.do"
    if ((((context->coverageEnabled && (context->coverageModuleId >= 0)) && (level > 0)) && (std::visit([](auto&& _obj) { return _obj->kind; }, statement) != std::string("block"))) && (std::visit([](auto&& _obj) { return _obj->kind; }, statement) != std::string("mock-import-directive"))) {
#line 39 "/src/emitter-stmt.do"
        const auto line = std::visit([](auto&& _obj) { return _obj->span; }, statement).start.line;
#line 40 "/src/emitter-stmt.do"
        (coverageMark = (((((ind + std::string("doof::coverage::cov_mark(")) + doof::to_string(context->coverageModuleId)) + std::string(", ")) + doof::to_string(line)) + std::string(");\n")));
#line 41 "/src/emitter-stmt.do"
        ::app_src_emitter_context_::recordCoverageLine(context, line);
    }
#line 43 "/src/emitter-stmt.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
#line 44 "/src/emitter-stmt.do"
            return std::string("");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 45 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitLocalDeclaration(ind, const_->name, const_->type_, doof::optional_value(doof::unwrap_optional(const_->resolvedType)), const_->value, context, true, false));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 46 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitLocalDeclaration(ind, readonly_->name, readonly_->type_, doof::optional_value(doof::unwrap_optional(readonly_->resolvedType)), readonly_->value, context, true, false));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 48 "/src/emitter-stmt.do"
            if (!doof::is_null(binding->else_)) {
#line 48 "/src/emitter-stmt.do"
                return ((sourceMark + coverageMark) + emitBindingElse(binding, level, context));
            }
#line 49 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitLocalDeclaration(ind, binding->name, binding->type_, doof::optional_value(doof::unwrap_optional(binding->resolvedType)), binding->value, context, true, true));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 51 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitLocalDeclaration(ind, let_->name, let_->type_, doof::optional_value(doof::unwrap_optional(let_->resolvedType)), let_->value, context, false, false));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
#line 52 "/src/emitter-stmt.do"
            return (((sourceMark + coverageMark) + ind) + emitReturn(return_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject)) {
            const auto& yield_ = std::get<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject);
#line 54 "/src/emitter-stmt.do"
            if (!context->inValueYieldBlock) {
#line 54 "/src/emitter-stmt.do"
                doof::panic(std::string("yield statement is outside a value-producing block"));
            }
#line 55 "/src/emitter-stmt.do"
            if (context->valueYieldReturnsVoid) {
#line 56 "/src/emitter-stmt.do"
                return ((((((sourceMark + coverageMark) + ind) + ::app_src_emitter_expr_::emitExpression(yield_->value, context, std::monostate{})) + std::string(";\n")) + ind) + std::string("return;\n"));
            }
#line 58 "/src/emitter-stmt.do"
            return (((((sourceMark + coverageMark) + ind) + std::string("return ")) + ::app_src_emitter_expr_::emitExpression(yield_->value, context, std::monostate{})) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 60 "/src/emitter-stmt.do"
            return ((((sourceMark + coverageMark) + ind) + ::app_src_emitter_expr_::emitExpression(expression->expression, context, std::monostate{})) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
#line 61 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitIf(if_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
#line 62 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitCase(case_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
#line 63 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitWhile(while_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
#line 64 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitForOf(forOf, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
#line 65 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitFor(for_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
#line 66 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitWith(with_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 67 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitDestructuring(destructuring, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
#line 68 "/src/emitter-stmt.do"
            return ((sourceMark + coverageMark) + emitTry(try_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
#line 70 "/src/emitter-stmt.do"
            const auto target = (::app_src_emitter_context_::isCapturedMutable(context, assignment->name) ? ((std::string("(*") + ::app_src_emitter_expr_::cppIdentifier(assignment->name)) + std::string(")")) : ::app_src_emitter_expr_::cppIdentifier(assignment->name));
#line 73 "/src/emitter-stmt.do"
            return ((((((sourceMark + coverageMark) + ind) + target) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), context, assignment->resolvedType)) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BreakStatement>>(_case_subject)) {
#line 75 "/src/emitter-stmt.do"
            return (((sourceMark + coverageMark) + ind) + std::string("break;\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ContinueStatement>>(_case_subject)) {
#line 76 "/src/emitter-stmt.do"
            return (((sourceMark + coverageMark) + ind) + std::string("continue;\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 77 "/src/emitter-stmt.do"
            return emitBlock(block, level, context);
    }
    else {
#line 78 "/src/emitter-stmt.do"
            doof::panic((std::string("Unsupported statement in initial C++ emitter: ") + std::visit([](auto&& _obj) { return _obj->kind; }, statement)));
    }
    }
    doof::unreachable();
#line 80 "/src/emitter-stmt.do"
    return std::string("");
}
#line 84 "/src/emitter-stmt.do"
std::string emitWith(const std::shared_ptr<::app_src_ast_::WithStatement>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 85 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 86 "/src/emitter-stmt.do"
    const auto innerInd = indent((level + 1));
#line 87 "/src/emitter-stmt.do"
    auto output = (ind + std::string("{\n"));
#line 88 "/src/emitter-stmt.do"
    const auto& _iterable_4 = statement->bindings;
    for (const auto& binding : *_iterable_4) {
#line 89 "/src/emitter-stmt.do"
        if (doof::is_null(binding->resolvedType)) {
#line 89 "/src/emitter-stmt.do"
            doof::panic((std::string("With binding was not resolved before emission: ") + binding->name));
        }
#line 90 "/src/emitter-stmt.do"
        const auto resolvedType = doof::unwrap_optional(binding->resolvedType);
#line 91 "/src/emitter-stmt.do"
        const auto value = ::app_src_emitter_expr_::emitExpression(binding->value, context, doof::optional_value(resolvedType));
#line 92 "/src/emitter-stmt.do"
        auto declarationType = std::string("auto");
#line 93 "/src/emitter-stmt.do"
        {
            auto _case_subject = resolvedType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 94 "/src/emitter-stmt.do"
                (declarationType = ::app_src_emitter_types_::emitType(resolvedType, context->modulePath));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 96 "/src/emitter-stmt.do"
                if (::app_src_emitter_types_::usesVariantRepresentation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) {
#line 96 "/src/emitter-stmt.do"
                    (declarationType = ::app_src_emitter_types_::emitType(resolvedType, context->modulePath));
                }
        }
        else {
        }
        }
#line 100 "/src/emitter-stmt.do"
        auto bindingName = ::app_src_emitter_expr_::cppIdentifier(binding->name);
#line 101 "/src/emitter-stmt.do"
        if (binding->name == std::string("_")) {
#line 102 "/src/emitter-stmt.do"
            (context->tryCounter = (context->tryCounter + 1));
#line 103 "/src/emitter-stmt.do"
            (bindingName = (std::string("_with_discard_") + doof::to_string(context->tryCounter)));
        }
#line 105 "/src/emitter-stmt.do"
        (output = ((((((((output + innerInd) + std::string("const ")) + declarationType) + std::string(" ")) + bindingName) + std::string(" = ")) + value) + std::string(";\n")));
    }
#line 107 "/src/emitter-stmt.do"
    (output = (output + emitBlock(statement->body, (level + 1), context)));
#line 108 "/src/emitter-stmt.do"
    return ((output + ind) + std::string("}\n"));
}
#line 111 "/src/emitter-stmt.do"
std::string emitDestructuring(const std::shared_ptr<::app_src_ast_::DestructuringStatement>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 112 "/src/emitter-stmt.do"
    return emitDestructuringValue(statement, ::app_src_emitter_expr_::emitExpression(statement->value, context, std::monostate{}), std::visit([](auto&& _obj) { return _obj->resolvedType; }, statement->value), level, context);
}
#line 116 "/src/emitter-stmt.do"
std::string emitDestructuringValue(const std::shared_ptr<::app_src_ast_::DestructuringStatement>& statement, const std::string& source, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& sourceType, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 117 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 118 "/src/emitter-stmt.do"
    (context->tryCounter = (context->tryCounter + 1));
#line 119 "/src/emitter-stmt.do"
    const auto temporaryName = (std::string("_destructure_") + doof::to_string(context->tryCounter));
#line 120 "/src/emitter-stmt.do"
    auto result = (((((ind + std::string("const auto& ")) + temporaryName) + std::string(" = ")) + source) + std::string(";\n"));
#line 121 "/src/emitter-stmt.do"
    if (doof::string_startsWith(statement->kind, std::string("array-destructuring"))) {
#line 122 "/src/emitter-stmt.do"
        const auto location = ((::app_src_emitter_expr_literals_::quote(context->modulePath) + std::string(", ")) + doof::to_string(statement->span.start.line));
#line 123 "/src/emitter-stmt.do"
        (result = ((((((((result + ind) + std::string("doof::array_require_min_size(")) + temporaryName) + std::string(", ")) + doof::to_string(static_cast<int32_t>((statement->bindings)->size()))) + std::string(", ")) + location) + std::string(");\n")));
    }
#line 125 "/src/emitter-stmt.do"
    if (doof::string_startsWith(statement->kind, std::string("named-destructuring"))) {
#line 126 "/src/emitter-stmt.do"
        const auto& _iterable_6 = statement->namedBindings;
        for (const auto& binding : *_iterable_6) {
#line 127 "/src/emitter-stmt.do"
            const auto value = emitDestructuredField(temporaryName, binding->name, sourceType, context);
#line 128 "/src/emitter-stmt.do"
            const auto localName = [&]() -> std::string { auto _coalesce_7 = binding->alias; if (doof::is_null(_coalesce_7)) return binding->name; return doof::unwrap_optional(_coalesce_7); }();
#line 129 "/src/emitter-stmt.do"
            if (doof::string_endsWith(statement->kind, std::string("-assignment"))) {
#line 129 "/src/emitter-stmt.do"
                (result = (((((result + ind) + emitAssignmentTarget(localName, context)) + std::string(" = ")) + value) + std::string(";\n")));
            } else {
#line 131 "/src/emitter-stmt.do"
                const auto qualifier = ((statement->bindingKind == std::string("let")) ? std::string("auto") : std::string("const auto"));
#line 132 "/src/emitter-stmt.do"
                (result = (((((((result + ind) + qualifier) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(localName)) + std::string(" = ")) + value) + std::string(";\n")));
            }
        }
#line 135 "/src/emitter-stmt.do"
        return result;
    }
#line 138 "/src/emitter-stmt.do"
    std::shared_ptr<std::vector<std::string>> positionalFields = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 139 "/src/emitter-stmt.do"
    if (!doof::is_null(sourceType)) {
#line 139 "/src/emitter-stmt.do"
        {
            auto _case_subject = doof::unwrap_optional(sourceType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 140 "/src/emitter-stmt.do"
                (positionalFields = classFieldNames(class_, context));
        }
        else {
        }
        }
    }
#line 143 "/src/emitter-stmt.do"
    for (int32_t i = 0; i < static_cast<int32_t>((statement->bindings)->size()); ++i) {
#line 144 "/src/emitter-stmt.do"
        const auto name = doof::array_at(statement->bindings, i, "src/emitter-stmt", 144);
#line 145 "/src/emitter-stmt.do"
        if (name != std::string("_")) {
#line 146 "/src/emitter-stmt.do"
            const auto qualifier = ((statement->bindingKind == std::string("let")) ? std::string("auto") : std::string("const auto"));
#line 147 "/src/emitter-stmt.do"
            auto value = ((((std::string("std::get<") + doof::to_string(i)) + std::string(">(")) + temporaryName) + std::string(")"));
#line 148 "/src/emitter-stmt.do"
            if (!doof::is_null(sourceType)) {
#line 149 "/src/emitter-stmt.do"
                {
                    auto _case_subject = doof::unwrap_optional(sourceType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 150 "/src/emitter-stmt.do"
                        (value = ((((((((std::string("doof::array_at(") + temporaryName) + std::string(", ")) + doof::to_string(i)) + std::string(", ")) + ::app_src_emitter_expr_literals_::quote(context->modulePath)) + std::string(", ")) + doof::to_string(statement->span.start.line)) + std::string(")")));
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 153 "/src/emitter-stmt.do"
                        if (i < static_cast<int32_t>((positionalFields)->size())) {
#line 153 "/src/emitter-stmt.do"
                            (value = emitDestructuredField(temporaryName, doof::array_at(positionalFields, i, "src/emitter-stmt", 153), doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), context));
                        }
                }
                else {
                }
                }
            }
#line 158 "/src/emitter-stmt.do"
            if (doof::string_endsWith(statement->kind, std::string("-assignment"))) {
#line 159 "/src/emitter-stmt.do"
                (result = (((((result + ind) + emitAssignmentTarget(name, context)) + std::string(" = ")) + value) + std::string(";\n")));
            } else {
#line 161 "/src/emitter-stmt.do"
                (result = (((((((result + ind) + qualifier) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + value) + std::string(";\n")));
            }
        }
    }
#line 165 "/src/emitter-stmt.do"
    return result;
}
#line 168 "/src/emitter-stmt.do"
std::string emitDestructuredField(const std::string& source, const std::string& field, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& sourceType, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 169 "/src/emitter-stmt.do"
    if (!doof::is_null(sourceType)) {
#line 169 "/src/emitter-stmt.do"
        {
            auto _case_subject = doof::unwrap_optional(sourceType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 171 "/src/emitter-stmt.do"
                const auto accessor = ((class_->symbol->kind == std::string("struct")) ? std::string(".") : std::string("->"));
#line 172 "/src/emitter-stmt.do"
                return ((source + accessor) + ::app_src_emitter_expr_::cppIdentifier(field));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 174 "/src/emitter-stmt.do"
                return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + ::app_src_emitter_expr_::cppIdentifier(field)) + std::string("; }, ")) + source) + std::string(")"));
        }
        else {
        }
        }
    }
#line 177 "/src/emitter-stmt.do"
    return ((source + std::string(".")) + ::app_src_emitter_expr_::cppIdentifier(field));
}
#line 180 "/src/emitter-stmt.do"
std::shared_ptr<std::vector<std::string>> classFieldNames(const std::shared_ptr<::app_src_semantic_::ClassType>& class_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 181 "/src/emitter-stmt.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 182 "/src/emitter-stmt.do"
    const auto declaration = findClassDeclaration(class_, context);
#line 183 "/src/emitter-stmt.do"
    if (doof::is_null(declaration)) {
#line 183 "/src/emitter-stmt.do"
        return result;
    }
#line 184 "/src/emitter-stmt.do"
    const auto& _iterable_10 = declaration->fields;
    for (const auto& field : *_iterable_10) {
#line 185 "/src/emitter-stmt.do"
        if (field->static_) {
#line 185 "/src/emitter-stmt.do"
            continue;
        }
#line 186 "/src/emitter-stmt.do"
        const auto& _iterable_12 = field->names;
        for (const auto& name : *_iterable_12) {
#line 186 "/src/emitter-stmt.do"
            result->push_back(name);
        }
    }
#line 188 "/src/emitter-stmt.do"
    return result;
}
#line 191 "/src/emitter-stmt.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> findClassDeclaration(const std::shared_ptr<::app_src_semantic_::ClassType>& class_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 192 "/src/emitter-stmt.do"
    const auto& _iterable_14 = context->allPrograms;
    for (const auto& program : *_iterable_14) {
#line 192 "/src/emitter-stmt.do"
        const auto& _iterable_16 = program->statements;
        for (const auto& statement : *_iterable_16) {
#line 193 "/src/emitter-stmt.do"
            const auto candidate = statementClass(statement);
#line 194 "/src/emitter-stmt.do"
            if ((((!doof::is_null(candidate)) && (!doof::is_null(candidate->resolvedSymbol))) && (candidate->resolvedSymbol->module == class_->symbol->module)) && (candidate->name == class_->name)) {
#line 194 "/src/emitter-stmt.do"
                return candidate;
            }
        }
    }
#line 196 "/src/emitter-stmt.do"
    return nullptr;
}
#line 199 "/src/emitter-stmt.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> statementClass(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 200 "/src/emitter-stmt.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 201 "/src/emitter-stmt.do"
            return class_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 202 "/src/emitter-stmt.do"
            return statementClass(export_->declaration);
    }
    else {
#line 203 "/src/emitter-stmt.do"
            return nullptr;
    }
    }
    doof::unreachable();
#line 205 "/src/emitter-stmt.do"
    return nullptr;
}
#line 208 "/src/emitter-stmt.do"
std::string emitAssignmentTarget(const std::string& name, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 209 "/src/emitter-stmt.do"
    return (::app_src_emitter_context_::isCapturedMutable(context, name) ? ((std::string("(*") + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(")")) : ::app_src_emitter_expr_::cppIdentifier(name));
}
#line 212 "/src/emitter-stmt.do"
std::string emitBindingElse(const std::shared_ptr<::app_src_ast_::ImmutableBinding>& binding, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 213 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 214 "/src/emitter-stmt.do"
    if (doof::is_null(binding->else_)) {
#line 214 "/src/emitter-stmt.do"
        return emitLocalDeclaration(ind, binding->name, binding->type_, doof::optional_value(doof::unwrap_optional(binding->resolvedType)), binding->value, context, true, true);
    }
#line 215 "/src/emitter-stmt.do"
    (context->tryCounter = (context->tryCounter + 1));
#line 216 "/src/emitter-stmt.do"
    const auto temporaryName = (std::string("_binding_value_") + doof::to_string(context->tryCounter));
#line 217 "/src/emitter-stmt.do"
    if ((!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, binding->value))) && isSingleOptional(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, binding->value)))) {
#line 218 "/src/emitter-stmt.do"
        auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(binding->value, context, std::monostate{})) + std::string(";\n"));
#line 219 "/src/emitter-stmt.do"
        (output = ((((output + ind) + std::string("if (doof::is_null(")) + temporaryName) + std::string(")) {\n")));
#line 220 "/src/emitter-stmt.do"
        if (doof::is_null(binding->failureName) && (binding->name != std::string("_"))) {
#line 220 "/src/emitter-stmt.do"
            (output = ((((((output + indent((level + 1))) + std::string("const auto& ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = ")) + temporaryName) + std::string(";\n")));
        }
#line 221 "/src/emitter-stmt.do"
        (output = (output + emitBlock(doof::unwrap_optional(binding->else_), (level + 1), context)));
#line 222 "/src/emitter-stmt.do"
        (output = ((output + ind) + std::string("}\n")));
#line 223 "/src/emitter-stmt.do"
        if (binding->name == std::string("_")) {
#line 223 "/src/emitter-stmt.do"
            return output;
        }
#line 224 "/src/emitter-stmt.do"
        return (output + emitExtractedLocal(ind, binding->name, doof::unwrap_optional(binding->resolvedType), ((std::string("doof::unwrap_optional(") + temporaryName) + std::string(")")), true, true));
    }
#line 226 "/src/emitter-stmt.do"
    auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(binding->value, context, std::monostate{})) + std::string(";\n"));
#line 227 "/src/emitter-stmt.do"
    (output = ((((output + ind) + std::string("if (doof::is_failure(")) + temporaryName) + std::string(")) {\n")));
#line 228 "/src/emitter-stmt.do"
    if ((!doof::is_null(binding->failureName)) && (doof::unwrap_optional(binding->failureName) != std::string("_"))) {
#line 229 "/src/emitter-stmt.do"
        (output = ((((((output + indent((level + 1))) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(doof::unwrap_optional(binding->failureName))) + std::string(" = doof::failure_error(")) + temporaryName) + std::string(");\n")));
    } else if (binding->name != std::string("_")) {
#line 231 "/src/emitter-stmt.do"
        (output = ((((((output + indent((level + 1))) + std::string("const auto& ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = ")) + temporaryName) + std::string(";\n")));
    }
#line 233 "/src/emitter-stmt.do"
    (output = (output + emitBlock(doof::unwrap_optional(binding->else_), (level + 1), context)));
#line 234 "/src/emitter-stmt.do"
    (output = ((output + ind) + std::string("}\n")));
#line 235 "/src/emitter-stmt.do"
    if (binding->name == std::string("_")) {
#line 235 "/src/emitter-stmt.do"
        return output;
    }
#line 236 "/src/emitter-stmt.do"
    return (output + emitExtractedLocal(ind, binding->name, doof::unwrap_optional(binding->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, true));
}
#line 239 "/src/emitter-stmt.do"
bool isSingleOptional(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType) {
#line 240 "/src/emitter-stmt.do"
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 242 "/src/emitter-stmt.do"
            auto hasNone = false;
#line 243 "/src/emitter-stmt.do"
            const auto& _iterable_18 = union_->types;
            for (const auto& member : *_iterable_18) {
#line 244 "/src/emitter-stmt.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 244 "/src/emitter-stmt.do"
                    (hasNone = true);
                }
            }
#line 249 "/src/emitter-stmt.do"
            return hasNone;
    }
    else {
#line 251 "/src/emitter-stmt.do"
            return false;
    }
    }
    doof::unreachable();
#line 253 "/src/emitter-stmt.do"
    return false;
}
#line 256 "/src/emitter-stmt.do"
std::string emitTry(const std::shared_ptr<::app_src_ast_::TryStatement>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 257 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 258 "/src/emitter-stmt.do"
    (context->tryCounter = (context->tryCounter + 1));
#line 259 "/src/emitter-stmt.do"
    const auto temporaryName = (std::string("_try_value_") + doof::to_string(context->tryCounter));
#line 260 "/src/emitter-stmt.do"
    std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::Identifier>(std::string("identifier"), std::string("<try>"), std::monostate{}, nullptr, statement->span));
#line 261 "/src/emitter-stmt.do"
    {
        auto _case_subject = statement->binding;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 262 "/src/emitter-stmt.do"
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 263 "/src/emitter-stmt.do"
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 264 "/src/emitter-stmt.do"
            (value = binding->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 265 "/src/emitter-stmt.do"
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 266 "/src/emitter-stmt.do"
            (value = expression->expression);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 267 "/src/emitter-stmt.do"
            (value = destructuring->value);
    }
    }
#line 269 "/src/emitter-stmt.do"
    if (context->catchVarName != std::string("")) {
#line 270 "/src/emitter-stmt.do"
        auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, std::monostate{})) + std::string(";\n"));
#line 271 "/src/emitter-stmt.do"
        (output = ((((output + ind) + std::string("if (doof::is_failure(")) + temporaryName) + std::string(")) { ")));
#line 272 "/src/emitter-stmt.do"
        const auto errorType = std::visit([](auto&& _obj) { return _obj->resolvedType; }, value);
#line 273 "/src/emitter-stmt.do"
        auto hasErrorValue = true;
#line 274 "/src/emitter-stmt.do"
        if (!doof::is_null(errorType)) {
#line 275 "/src/emitter-stmt.do"
            {
                auto _case_subject = doof::unwrap_optional(errorType);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 276 "/src/emitter-stmt.do"
                    if (std::visit([](auto&& _obj) { return _obj->kind; }, result->errorType) == std::string("none")) {
#line 276 "/src/emitter-stmt.do"
                        (hasErrorValue = false);
                    }
            }
            else {
            }
            }
        }
#line 280 "/src/emitter-stmt.do"
        if (hasErrorValue) {
#line 281 "/src/emitter-stmt.do"
            auto promoted = ((std::string("doof::failure_error(") + temporaryName) + std::string(")"));
#line 282 "/src/emitter-stmt.do"
            if (!doof::is_null(context->catchResultType)) {
#line 283 "/src/emitter-stmt.do"
                (promoted = ((((std::string("doof::variant_promote<") + ::app_src_emitter_types_::emitType(doof::unwrap_optional(context->catchResultType), context->modulePath)) + std::string(">(")) + promoted) + std::string(")")));
            }
#line 285 "/src/emitter-stmt.do"
            (output = ((((output + context->catchVarName) + std::string(" = ")) + promoted) + std::string("; ")));
        }
#line 287 "/src/emitter-stmt.do"
        (output = (output + std::string("break; }\n")));
#line 288 "/src/emitter-stmt.do"
        {
            auto _case_subject = statement->binding;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 289 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 290 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 291 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, binding->name, doof::unwrap_optional(binding->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, true)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 292 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), false, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 294 "/src/emitter-stmt.do"
                (output = (output + emitTryDestructuring(destructuring, temporaryName, level, context)));
        }
        }
#line 296 "/src/emitter-stmt.do"
        return output;
    }
#line 298 "/src/emitter-stmt.do"
    if (context->currentReturnErrorType != std::string("")) {
#line 299 "/src/emitter-stmt.do"
        const auto errorType = context->currentReturnErrorType;
#line 300 "/src/emitter-stmt.do"
        auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, std::monostate{})) + std::string(";\n"));
#line 301 "/src/emitter-stmt.do"
        (output = ((((((((((output + ind) + std::string("if (doof::is_failure(")) + temporaryName) + std::string(")) return doof::Failure<")) + errorType) + std::string(">{doof::variant_promote<")) + errorType) + std::string(">(doof::failure_error(")) + temporaryName) + std::string("))};\n")));
#line 302 "/src/emitter-stmt.do"
        {
            auto _case_subject = statement->binding;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 304 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 307 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 310 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, binding->name, doof::unwrap_optional(binding->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, true)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 313 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), false, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 316 "/src/emitter-stmt.do"
                (output = (output + emitTryDestructuring(destructuring, temporaryName, level, context)));
        }
        }
#line 318 "/src/emitter-stmt.do"
        return output;
    }
#line 320 "/src/emitter-stmt.do"
    if (context->tryPanics) {
#line 321 "/src/emitter-stmt.do"
        auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, std::monostate{})) + std::string(";\n"));
#line 322 "/src/emitter-stmt.do"
        auto failureMessage = std::string("std::string(\"try failed\")");
#line 323 "/src/emitter-stmt.do"
        {
            auto _case_subject = resultValueType(value);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 324 "/src/emitter-stmt.do"
                {
                    auto _case_subject = result->errorType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                        const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 325 "/src/emitter-stmt.do"
                        if (primitive->name == std::string("string")) {
#line 325 "/src/emitter-stmt.do"
                            (failureMessage = (((failureMessage + std::string(" + std::string(\": \") + doof::failure_error(")) + temporaryName) + std::string(")")));
                        }
                }
                else {
                }
                }
        }
        else {
        }
        }
#line 330 "/src/emitter-stmt.do"
        (output = ((((((((((output + ind) + std::string("if (doof::is_failure(")) + temporaryName) + std::string(")) doof::panic_at(")) + ::app_src_emitter_expr_literals_::quote(context->modulePath)) + std::string(", ")) + doof::to_string(statement->span.start.line)) + std::string(", ")) + failureMessage) + std::string(");\n")));
#line 331 "/src/emitter-stmt.do"
        {
            auto _case_subject = statement->binding;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 332 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 333 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 334 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, binding->name, doof::unwrap_optional(binding->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), true, true)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 335 "/src/emitter-stmt.do"
                (output = (output + emitExtractedLocal(ind, declaration->name, doof::unwrap_optional(declaration->resolvedType), ((std::string("doof::success_value(") + temporaryName) + std::string(")")), false, false)));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 337 "/src/emitter-stmt.do"
                (output = (output + emitTryDestructuring(destructuring, temporaryName, level, context)));
        }
        }
#line 339 "/src/emitter-stmt.do"
        return output;
    }
#line 341 "/src/emitter-stmt.do"
    doof::panic(std::string("try expression is outside a Result-returning function"));
#line 342 "/src/emitter-stmt.do"
    return std::string("");
}
#line 345 "/src/emitter-stmt.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resultValueType(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
    return std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression);
}
#line 347 "/src/emitter-stmt.do"
std::string emitTryDestructuring(const std::shared_ptr<::app_src_ast_::DestructuringStatement>& statement, const std::string& temporaryName, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 348 "/src/emitter-stmt.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> successType = std::monostate{};
#line 349 "/src/emitter-stmt.do"
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, statement->value))) {
#line 349 "/src/emitter-stmt.do"
        {
            auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, statement->value));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 350 "/src/emitter-stmt.do"
                (successType = doof::optional_value(result->valueType));
        }
        else {
        }
        }
    }
#line 353 "/src/emitter-stmt.do"
    return emitDestructuringValue(statement, ((std::string("doof::success_value(") + temporaryName) + std::string(")")), successType, level, context);
}
#line 356 "/src/emitter-stmt.do"
std::string emitLocalDeclaration(const std::string& ind, const std::string& name, const std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& value, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, bool readonly_, bool shallowImmutable) {
#line 357 "/src/emitter-stmt.do"
    if (doof::is_null(resolvedType)) {
#line 357 "/src/emitter-stmt.do"
        doof::panic(std::string("Local declaration was not resolved before emission"));
    }
#line 358 "/src/emitter-stmt.do"
    auto typeText = (doof::is_null(annotation) ? std::string("auto") : ::app_src_emitter_types_::emitContextType(doof::unwrap_optional(resolvedType), context));
#line 359 "/src/emitter-stmt.do"
    const auto prefix = localConstPrefix(doof::unwrap_optional(resolvedType), readonly_, shallowImmutable);
#line 360 "/src/emitter-stmt.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = resolvedType;
#line 361 "/src/emitter-stmt.do"
    auto valueText = ::app_src_emitter_expr_::emitExpression(value, context, expected);
#line 362 "/src/emitter-stmt.do"
    if (!readonly_ && ::app_src_emitter_context_::isCapturedMutable(context, name)) {
#line 363 "/src/emitter-stmt.do"
        return (((((((ind + std::string("auto ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = std::make_shared<")) + ::app_src_emitter_types_::emitContextType(doof::unwrap_optional(resolvedType), context)) + std::string(">(")) + valueText) + std::string(");\n"));
    }
#line 365 "/src/emitter-stmt.do"
    return (((((((ind + prefix) + typeText) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + valueText) + std::string(";\n"));
}
#line 369 "/src/emitter-stmt.do"
std::string emitExtractedLocal(const std::string& ind, const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::string& value, bool readonly_, bool shallowImmutable) {
#line 370 "/src/emitter-stmt.do"
    return ((((((ind + localConstPrefix(resolvedType, readonly_, shallowImmutable)) + std::string("auto ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + value) + std::string(";\n"));
}
#line 373 "/src/emitter-stmt.do"
std::string localConstPrefix(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, bool readonly_, bool shallowImmutable) {
#line 374 "/src/emitter-stmt.do"
    if (!readonly_) {
#line 374 "/src/emitter-stmt.do"
        return std::string("");
    }
#line 375 "/src/emitter-stmt.do"
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 376 "/src/emitter-stmt.do"
            if (shallowImmutable && (class_->symbol->kind == std::string("struct"))) {
#line 376 "/src/emitter-stmt.do"
                return std::string("");
            }
    }
    else {
    }
    }
#line 379 "/src/emitter-stmt.do"
    return std::string("const ");
}
#line 382 "/src/emitter-stmt.do"
std::string emitCase(const std::shared_ptr<::app_src_ast_::CaseStatement>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 383 "/src/emitter-stmt.do"
    if (doof::is_null(statement->resolvedCompletes)) {
#line 383 "/src/emitter-stmt.do"
        doof::panic(std::string("Case statement has no resolved control-flow completion"));
    }
#line 384 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 385 "/src/emitter-stmt.do"
    const auto inner = indent((level + 1));
#line 386 "/src/emitter-stmt.do"
    const auto bodyIndent = indent((level + 2));
#line 387 "/src/emitter-stmt.do"
    const auto subject = std::string("_case_subject");
#line 388 "/src/emitter-stmt.do"
    auto result = (((((((ind + std::string("{\n")) + inner) + std::string("auto ")) + subject) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(statement->subject, context, std::monostate{})) + std::string(";\n"));
#line 389 "/src/emitter-stmt.do"
    auto previous = false;
#line 390 "/src/emitter-stmt.do"
    const auto subjectType = caseSubjectType(statement->subject);
#line 391 "/src/emitter-stmt.do"
    if (doof::is_null(subjectType)) {
#line 391 "/src/emitter-stmt.do"
        doof::panic(std::string("Case statement subject has no resolved type"));
    }
#line 393 "/src/emitter-stmt.do"
    const auto& _iterable_20 = statement->arms;
    for (const auto& arm : *_iterable_20) {
#line 394 "/src/emitter-stmt.do"
        const auto& _iterable_22 = arm->patterns;
        for (const auto& pattern : *_iterable_22) {
#line 395 "/src/emitter-stmt.do"
            auto condition = std::string("");
#line 396 "/src/emitter-stmt.do"
            auto binding = std::string("");
#line 397 "/src/emitter-stmt.do"
            auto isWildcard = false;
#line 398 "/src/emitter-stmt.do"
            {
                auto _case_subject = pattern;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                    const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
#line 400 "/src/emitter-stmt.do"
                    const auto bindingName = ((type_->name == std::string("_")) ? std::string("") : ::app_src_emitter_expr_::cppIdentifier(type_->name));
#line 401 "/src/emitter-stmt.do"
                    const auto emitted = ::app_src_emitter_case_pattern_::emitCaseTypePattern(type_, ::app_src_emitter_types_::specializeEmitType(doof::unwrap_optional(subjectType), context), subject, bindingName, context->modulePath);
#line 402 "/src/emitter-stmt.do"
                    (condition = emitted->condition);
#line 403 "/src/emitter-stmt.do"
                    (binding = emitted->binding);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
#line 405 "/src/emitter-stmt.do"
                    (condition = ((subject + std::string(" == ")) + ::app_src_emitter_expr_::emitExpression(value->value, context, std::monostate{})));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject)) {
                    const auto& range = std::get<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject);
#line 406 "/src/emitter-stmt.do"
                    (condition = emitRangePatternCondition(range, subject, context));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
#line 407 "/src/emitter-stmt.do"
                    (isWildcard = true);
            }
            }
#line 410 "/src/emitter-stmt.do"
            if (isWildcard) {
#line 411 "/src/emitter-stmt.do"
                (result = (result + (previous ? (ind + std::string("else {\n")) : (inner + std::string("{\n")))));
            } else {
#line 413 "/src/emitter-stmt.do"
                (result = (result + (previous ? (((ind + std::string("else if (")) + condition) + std::string(") {\n")) : (((inner + std::string("if (")) + condition) + std::string(") {\n")))));
            }
#line 415 "/src/emitter-stmt.do"
            if (binding != std::string("")) {
#line 415 "/src/emitter-stmt.do"
                (result = ((result + bodyIndent) + binding));
            }
#line 416 "/src/emitter-stmt.do"
            {
                auto _case_subject = arm->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 417 "/src/emitter-stmt.do"
                    (result = (((result + emitBlock(block, (level + 2), context)) + ind) + std::string("}\n")));
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
#line 418 "/src/emitter-stmt.do"
                    doof::panic(std::string("Expression case arm reached statement emitter"));
            }
            }
#line 420 "/src/emitter-stmt.do"
            (previous = true);
#line 421 "/src/emitter-stmt.do"
            if (isWildcard) {
#line 422 "/src/emitter-stmt.do"
                (result = ((result + ind) + std::string("}\n")));
#line 423 "/src/emitter-stmt.do"
                return (result + emitCaseContinuationGuard(statement, ind));
            }
        }
    }
#line 427 "/src/emitter-stmt.do"
    return (((result + ind) + std::string("}\n")) + emitCaseContinuationGuard(statement, ind));
}
#line 434 "/src/emitter-stmt.do"
std::string emitCaseContinuationGuard(const std::shared_ptr<::app_src_ast_::CaseStatement>& statement, const std::string& ind) {
#line 435 "/src/emitter-stmt.do"
    return (doof::unwrap_optional(statement->resolvedCompletes) ? std::string("") : (ind + std::string("doof::unreachable();\n")));
}
#line 438 "/src/emitter-stmt.do"
std::string emitRangePatternCondition(const std::shared_ptr<::app_src_ast_::RangePattern>& pattern, const std::string& subject, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 439 "/src/emitter-stmt.do"
    auto condition = std::string("");
#line 440 "/src/emitter-stmt.do"
    if (!doof::is_null(pattern->start)) {
#line 440 "/src/emitter-stmt.do"
        (condition = ((subject + std::string(" >= ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(pattern->start), context, std::monostate{})));
    }
#line 441 "/src/emitter-stmt.do"
    if (!doof::is_null(pattern->end)) {
#line 442 "/src/emitter-stmt.do"
        const auto operator_ = (pattern->inclusive ? std::string(" <= ") : std::string(" < "));
#line 443 "/src/emitter-stmt.do"
        if (condition != std::string("")) {
#line 443 "/src/emitter-stmt.do"
            (condition = (condition + std::string(" && ")));
        }
#line 444 "/src/emitter-stmt.do"
        (condition = (((condition + subject) + operator_) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(pattern->end), context, std::monostate{})));
    }
#line 446 "/src/emitter-stmt.do"
    return condition;
}
#line 449 "/src/emitter-stmt.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> caseSubjectType(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression) {
#line 450 "/src/emitter-stmt.do"
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression))) {
#line 450 "/src/emitter-stmt.do"
        return std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression);
    }
#line 451 "/src/emitter-stmt.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 453 "/src/emitter-stmt.do"
            if (!doof::is_null(identifier->resolvedBinding)) {
#line 453 "/src/emitter-stmt.do"
                return doof::optional_value(identifier->resolvedBinding->type_);
            }
    }
    else {
    }
    }
#line 457 "/src/emitter-stmt.do"
    return std::monostate{};
}
#line 460 "/src/emitter-stmt.do"
std::string emitReturn(const std::shared_ptr<::app_src_ast_::ReturnStatement>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 461 "/src/emitter-stmt.do"
    if (doof::is_null(statement->value)) {
#line 461 "/src/emitter-stmt.do"
        return std::string("return;\n");
    }
#line 462 "/src/emitter-stmt.do"
    const auto expected = statement->resolvedExpectedType;
#line 463 "/src/emitter-stmt.do"
    if ((!doof::is_null(expected)) && (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(expected)) == std::string("none"))) {
#line 464 "/src/emitter-stmt.do"
        if (std::visit([](auto&& _obj) { return _obj->kind; }, doof::unwrap_optional(statement->value)) == std::string("none-literal")) {
#line 464 "/src/emitter-stmt.do"
            return std::string("return;\n");
        }
#line 465 "/src/emitter-stmt.do"
        return (::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(statement->value), context, expected) + std::string(";\nreturn;\n"));
    }
#line 467 "/src/emitter-stmt.do"
    return ((std::string("return ") + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(statement->value), context, expected)) + std::string(";\n"));
}
#line 470 "/src/emitter-stmt.do"
std::string emitIf(const std::shared_ptr<::app_src_ast_::IfStatement>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 471 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 472 "/src/emitter-stmt.do"
    auto result = (((ind + std::string("if (")) + emitCondition(statement->condition, context)) + std::string(") {\n"));
#line 473 "/src/emitter-stmt.do"
    (result = (((result + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}")));
#line 474 "/src/emitter-stmt.do"
    const auto& _iterable_24 = statement->elseIfs;
    for (const auto& branch : *_iterable_24) {
#line 475 "/src/emitter-stmt.do"
        (result = (((result + std::string(" else if (")) + emitCondition(branch->condition, context)) + std::string(") {\n")));
#line 476 "/src/emitter-stmt.do"
        (result = (((result + emitBlock(branch->body, (level + 1), context)) + ind) + std::string("}")));
    }
#line 478 "/src/emitter-stmt.do"
    if (!doof::is_null(statement->else_)) {
#line 479 "/src/emitter-stmt.do"
        (result = ((((result + std::string(" else {\n")) + emitBlock(doof::unwrap_optional(statement->else_), (level + 1), context)) + ind) + std::string("}")));
    }
#line 481 "/src/emitter-stmt.do"
    return (result + std::string("\n"));
}
#line 484 "/src/emitter-stmt.do"
std::string emitWhile(const std::shared_ptr<::app_src_ast_::WhileStatement>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 485 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 486 "/src/emitter-stmt.do"
    return ((((((ind + std::string("while (")) + emitCondition(statement->condition, context)) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
}
#line 490 "/src/emitter-stmt.do"
std::string emitForOf(const std::shared_ptr<::app_src_ast_::ForOfStatement>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 491 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 492 "/src/emitter-stmt.do"
    (context->tryCounter = (context->tryCounter + 1));
#line 493 "/src/emitter-stmt.do"
    const auto loopId = context->tryCounter;
#line 494 "/src/emitter-stmt.do"
    const auto name = ((static_cast<int32_t>((statement->bindings)->size()) == 0) ? std::string("_item") : discardableCppName(doof::array_at(statement->bindings, 0, "src/emitter-stmt", 494), loopId, 0));
#line 495 "/src/emitter-stmt.do"
    {
        auto _case_subject = statement->iterable;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& range = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 497 "/src/emitter-stmt.do"
            if ((range->operator_ == std::string("..<")) || (range->operator_ == std::string(".."))) {
#line 498 "/src/emitter-stmt.do"
                const auto endOperator = ((range->operator_ == std::string("..<")) ? std::string(" < ") : std::string(" <= "));
#line 499 "/src/emitter-stmt.do"
                return ((((((((((((((ind + std::string("for (int32_t ")) + name) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(range->left, context, std::monostate{})) + std::string("; ")) + name) + endOperator) + ::app_src_emitter_expr_::emitExpression(range->right, context, std::monostate{})) + std::string("; ++")) + name) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
            }
    }
    else {
    }
    }
#line 505 "/src/emitter-stmt.do"
    const auto iterable = ::app_src_emitter_expr_::emitExpression(statement->iterable, context, std::monostate{});
#line 506 "/src/emitter-stmt.do"
    (context->tryCounter = (context->tryCounter + 1));
#line 507 "/src/emitter-stmt.do"
    const auto iterableName = (std::string("_iterable_") + doof::to_string(context->tryCounter));
#line 508 "/src/emitter-stmt.do"
    const auto iterableBinding = (((((ind + std::string("const auto& ")) + iterableName) + std::string(" = ")) + iterable) + std::string(";\n"));
#line 509 "/src/emitter-stmt.do"
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, statement->iterable))) {
#line 510 "/src/emitter-stmt.do"
        {
            auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, statement->iterable));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
#line 512 "/src/emitter-stmt.do"
                return (((((((((iterableBinding + ind) + std::string("for (const auto& ")) + name) + std::string(" : ")) + iterableName) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
#line 516 "/src/emitter-stmt.do"
                return (((((((((((((iterableBinding + ind) + std::string("while (std::visit([](auto&& _obj) { return _obj->next(); }, ")) + iterableName) + std::string(")) {\n")) + ind) + std::string("    const auto ")) + name) + std::string(" = std::visit([](auto&& _obj) { return _obj->value(); }, ")) + iterableName) + std::string(");\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
        }
        else {
        }
        }
    }
#line 523 "/src/emitter-stmt.do"
    if (static_cast<int32_t>((statement->bindings)->size()) > 1) {
#line 524 "/src/emitter-stmt.do"
        auto names = std::string("");
#line 525 "/src/emitter-stmt.do"
        for (int32_t i = 0; i < static_cast<int32_t>((statement->bindings)->size()); ++i) {
#line 526 "/src/emitter-stmt.do"
            if (i > 0) {
#line 526 "/src/emitter-stmt.do"
                (names = (names + std::string(", ")));
            }
#line 527 "/src/emitter-stmt.do"
            (names = (names + discardableCppName(doof::array_at(statement->bindings, i, "src/emitter-stmt", 527), loopId, i)));
        }
#line 529 "/src/emitter-stmt.do"
        return (((((((((iterableBinding + ind) + std::string("for (const auto& [")) + names) + std::string("] : *")) + iterableName) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
    }
#line 532 "/src/emitter-stmt.do"
    return (((((((((iterableBinding + ind) + std::string("for (const auto& ")) + name) + std::string(" : *")) + iterableName) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
}
#line 536 "/src/emitter-stmt.do"
std::string discardableCppName(const std::string& name, int32_t scopeId, int32_t position) {
#line 537 "/src/emitter-stmt.do"
    if (name == std::string("_")) {
#line 537 "/src/emitter-stmt.do"
        return (((std::string("_discard_") + doof::to_string(scopeId)) + std::string("_")) + doof::to_string(position));
    }
#line 538 "/src/emitter-stmt.do"
    return ::app_src_emitter_expr_::cppIdentifier(name);
}
#line 541 "/src/emitter-stmt.do"
std::string emitFor(const std::shared_ptr<::app_src_ast_::ForStatement>& statement, int32_t level, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 542 "/src/emitter-stmt.do"
    const auto ind = indent(level);
#line 543 "/src/emitter-stmt.do"
    auto init = std::string("");
#line 544 "/src/emitter-stmt.do"
    if (!doof::is_null(statement->init)) {
#line 545 "/src/emitter-stmt.do"
        (init = doof::string_trim(emitStatement(doof::unwrap_optional(statement->init), 0, context)));
#line 546 "/src/emitter-stmt.do"
        if (doof::string_endsWith(init, std::string(";"))) {
#line 546 "/src/emitter-stmt.do"
            (init = doof::string_substring(init, 0, (static_cast<int32_t>(init.size()) - 1)));
        }
    }
#line 548 "/src/emitter-stmt.do"
    auto condition = std::string("true");
#line 549 "/src/emitter-stmt.do"
    if (!doof::is_null(statement->condition)) {
#line 549 "/src/emitter-stmt.do"
        (condition = emitCondition(doof::unwrap_optional(statement->condition), context));
    }
#line 550 "/src/emitter-stmt.do"
    auto update = std::string("");
#line 551 "/src/emitter-stmt.do"
    for (int32_t i = 0; i < static_cast<int32_t>((statement->update)->size()); ++i) {
#line 552 "/src/emitter-stmt.do"
        if (i > 0) {
#line 552 "/src/emitter-stmt.do"
            (update = (update + std::string(", ")));
        }
#line 553 "/src/emitter-stmt.do"
        (update = (update + ::app_src_emitter_expr_::emitExpression(doof::array_at(statement->update, i, "src/emitter-stmt", 553), context, std::monostate{})));
    }
#line 555 "/src/emitter-stmt.do"
    return ((((((((((ind + std::string("for (")) + init) + std::string("; ")) + condition) + std::string("; ")) + update) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
}
#line 559 "/src/emitter-stmt.do"
std::string indent(int32_t level) {
#line 560 "/src/emitter-stmt.do"
    return doof::string_repeat(std::string("    "), level);
}
#line 563 "/src/emitter-stmt.do"
std::string emitCondition(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 564 "/src/emitter-stmt.do"
    const auto value = ::app_src_emitter_expr_::emitExpression(expression, context, std::monostate{});
#line 565 "/src/emitter-stmt.do"
    if (doof::string_startsWith(value, std::string("(")) && doof::string_endsWith(value, std::string(")"))) {
#line 566 "/src/emitter-stmt.do"
        return doof::string_substring(value, 1, (static_cast<int32_t>(value.size()) - 1));
    }
#line 568 "/src/emitter-stmt.do"
    return value;
}
#line 1 "<doof-generated>"
}
