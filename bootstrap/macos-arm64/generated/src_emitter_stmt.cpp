#include "src_emitter_stmt.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_case_pattern.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_expr_literals.hpp"
#include "src_emitter_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_stmt_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_case_pattern_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_literals_;
using namespace ::app_src_emitter_types_;
std::string emitBlock(std::shared_ptr<::app_src_ast_::Block> block, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto result = std::string("");
    const auto& _iterable_1 = block->statements;
    for (const auto& statement : *_iterable_1) {
        (result = (result + emitStatement(statement, level, context)));
    }
    return result;
}
std::string emitStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    auto coverageMark = std::string("");
    if ((((context->coverageEnabled && (context->coverageModuleId >= 0)) && (level > 0)) && (doof::kind(statement) != std::string("block"))) && (doof::kind(statement) != std::string("mock-import-directive"))) {
        const auto line = doof::span(statement).start.line;
        (coverageMark = (((((ind + std::string("doof::coverage::cov_mark(")) + doof::to_string(context->coverageModuleId)) + std::string(", ")) + doof::to_string(line)) + std::string(");\n")));
        ::app_src_emitter_context_::recordCoverageLine(context, line);
    }
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MockImportDirective>>(_case_subject)) {
            return std::string("");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return (coverageMark + emitLocalDeclaration(ind, const_->name, const_->type_, doof::optional_value(doof::unwrap_optional(const_->resolvedType)), const_->value, context, true, false));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return (coverageMark + emitLocalDeclaration(ind, readonly_->name, readonly_->type_, doof::optional_value(doof::unwrap_optional(readonly_->resolvedType)), readonly_->value, context, true, false));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            if (!doof::is_null(binding->else_)) {
                return (coverageMark + emitBindingElse(binding, level, context));
            }
            return (coverageMark + emitLocalDeclaration(ind, binding->name, binding->type_, doof::optional_value(doof::unwrap_optional(binding->resolvedType)), binding->value, context, true, true));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return (coverageMark + emitLocalDeclaration(ind, let_->name, let_->type_, doof::optional_value(doof::unwrap_optional(let_->resolvedType)), let_->value, context, false, false));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
            return ((coverageMark + ind) + emitReturn(return_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject)) {
            const auto& yield_ = std::get<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject);
            if (!context->inValueYieldBlock) {
                doof::panic(std::string("yield statement is outside a value-producing block"));
            }
            return ((((coverageMark + ind) + std::string("return ")) + ::app_src_emitter_expr_::emitExpression(yield_->value, context, std::monostate{})) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
            return (((coverageMark + ind) + ::app_src_emitter_expr_::emitExpression(expression->expression, context, std::monostate{})) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
            return (coverageMark + emitIf(if_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
            return (coverageMark + emitCase(case_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
            return (coverageMark + emitWhile(while_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
            return (coverageMark + emitForOf(forOf, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
            return (coverageMark + emitFor(for_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
            return (coverageMark + emitWith(with_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
            return (coverageMark + emitDestructuring(destructuring, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            return (coverageMark + emitTry(try_, level, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
            const auto target = (::app_src_emitter_context_::isCapturedMutable(context, assignment->name) ? ((std::string("(*") + ::app_src_emitter_expr_::cppIdentifier(assignment->name)) + std::string(")")) : ::app_src_emitter_expr_::cppIdentifier(assignment->name));
            return (((((coverageMark + ind) + target) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NullLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), context, assignment->resolvedType)) + std::string(";\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BreakStatement>>(_case_subject)) {
            return ((coverageMark + ind) + std::string("break;\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ContinueStatement>>(_case_subject)) {
            return ((coverageMark + ind) + std::string("continue;\n"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            return emitBlock(block, level, context);
    }
    else {
            doof::panic((std::string("Unsupported statement in initial C++ emitter: ") + doof::kind(statement)));
    }
    }
    return std::string("");
}
std::string emitWith(std::shared_ptr<::app_src_ast_::WithStatement> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    const auto innerInd = indent((level + 1));
    auto output = (ind + std::string("{\n"));
    const auto& _iterable_2 = statement->bindings;
    for (const auto& binding : *_iterable_2) {
        if (doof::is_null(binding->resolvedType)) {
            doof::panic((std::string("With binding was not resolved before emission: ") + binding->name));
        }
        const auto resolvedType = doof::unwrap_optional(binding->resolvedType);
        const auto value = ::app_src_emitter_expr_::emitExpression(binding->value, context, doof::optional_value(resolvedType));
        auto declarationType = std::string("auto");
        {
            auto _case_subject = resolvedType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                (declarationType = ::app_src_emitter_types_::emitType(resolvedType, context->modulePath));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                if (::app_src_emitter_types_::usesVariantRepresentation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) {
                    (declarationType = ::app_src_emitter_types_::emitType(resolvedType, context->modulePath));
                }
        }
        else {
        }
        }
        (output = ((((((((output + innerInd) + std::string("const ")) + declarationType) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = ")) + value) + std::string(";\n")));
    }
    (output = (output + emitBlock(statement->body, (level + 1), context)));
    return ((output + ind) + std::string("}\n"));
}
std::string emitDestructuring(std::shared_ptr<::app_src_ast_::DestructuringStatement> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return emitDestructuringValue(statement, ::app_src_emitter_expr_::emitExpression(statement->value, context, std::monostate{}), doof::resolved_type(statement->value), level, context);
}
std::string emitDestructuringValue(std::shared_ptr<::app_src_ast_::DestructuringStatement> statement, std::string source, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> sourceType, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    (context->tryCounter = (context->tryCounter + 1));
    const auto temporaryName = (std::string("_destructure_") + doof::to_string(context->tryCounter));
    auto result = (((((ind + std::string("const auto& ")) + temporaryName) + std::string(" = ")) + source) + std::string(";\n"));
    if (doof::string_startsWith(statement->kind, std::string("array-destructuring"))) {
        const auto location = ((::app_src_emitter_expr_literals_::quote(context->modulePath) + std::string(", ")) + doof::to_string(statement->span.start.line));
        (result = ((((((((result + ind) + std::string("doof::array_require_min_size(")) + temporaryName) + std::string(", ")) + doof::to_string(static_cast<int32_t>((statement->bindings)->size()))) + std::string(", ")) + location) + std::string(");\n")));
    }
    if (doof::string_startsWith(statement->kind, std::string("named-destructuring"))) {
        const auto& _iterable_3 = statement->namedBindings;
        for (const auto& binding : *_iterable_3) {
            const auto value = emitDestructuredField(temporaryName, binding->name, sourceType, context);
            const auto localName = (doof::is_null(binding->alias) ? binding->name : doof::unwrap_optional(binding->alias));
            if (doof::string_endsWith(statement->kind, std::string("-assignment"))) {
                (result = (((((result + ind) + emitAssignmentTarget(localName, context)) + std::string(" = ")) + value) + std::string(";\n")));
            } else {
                const auto qualifier = ((statement->bindingKind == std::string("let")) ? std::string("auto") : std::string("const auto"));
                (result = (((((((result + ind) + qualifier) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(localName)) + std::string(" = ")) + value) + std::string(";\n")));
            }
        }
        return result;
    }
    std::shared_ptr<std::vector<std::string>> positionalFields = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    if (!doof::is_null(sourceType)) {
        {
            auto _case_subject = doof::unwrap_optional(sourceType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                (positionalFields = classFieldNames(class_, context));
        }
        else {
        }
        }
    }
    for (int32_t i = 0; i < static_cast<int32_t>((statement->bindings)->size()); ++i) {
        const auto name = (*statement->bindings)[i];
        if (name != std::string("_")) {
            const auto qualifier = ((statement->bindingKind == std::string("let")) ? std::string("auto") : std::string("const auto"));
            auto value = ((((std::string("std::get<") + doof::to_string(i)) + std::string(">(")) + temporaryName) + std::string(")"));
            if (!doof::is_null(sourceType)) {
                {
                    auto _case_subject = doof::unwrap_optional(sourceType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                        (value = ((((((((std::string("doof::array_at(") + temporaryName) + std::string(", ")) + doof::to_string(i)) + std::string(", ")) + ::app_src_emitter_expr_literals_::quote(context->modulePath)) + std::string(", ")) + doof::to_string(statement->span.start.line)) + std::string(")")));
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                        if (i < static_cast<int32_t>((positionalFields)->size())) {
                            (value = emitDestructuredField(temporaryName, (*positionalFields)[i], doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_), context));
                        }
                }
                else {
                }
                }
            }
            if (doof::string_endsWith(statement->kind, std::string("-assignment"))) {
                (result = (((((result + ind) + emitAssignmentTarget(name, context)) + std::string(" = ")) + value) + std::string(";\n")));
            } else {
                (result = (((((((result + ind) + qualifier) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + value) + std::string(";\n")));
            }
        }
    }
    return result;
}
std::string emitDestructuredField(std::string source, std::string field, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> sourceType, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (!doof::is_null(sourceType)) {
        {
            auto _case_subject = doof::unwrap_optional(sourceType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                const auto accessor = ((class_->symbol->kind == std::string("struct")) ? std::string(".") : std::string("->"));
                return ((source + accessor) + ::app_src_emitter_expr_::cppIdentifier(field));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + ::app_src_emitter_expr_::cppIdentifier(field)) + std::string("; }, ")) + source) + std::string(")"));
        }
        else {
        }
        }
    }
    return ((source + std::string(".")) + ::app_src_emitter_expr_::cppIdentifier(field));
}
std::shared_ptr<std::vector<std::string>> classFieldNames(std::shared_ptr<::app_src_semantic_::ClassType> class_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto declaration = findClassDeclaration(class_, context);
    if (doof::is_null(declaration)) {
        return result;
    }
    const auto& _iterable_4 = declaration->fields;
    for (const auto& field : *_iterable_4) {
        if (field->static_) {
            continue;
        }
        const auto& _iterable_5 = field->names;
        for (const auto& name : *_iterable_5) {
            result->push_back(name);
        }
    }
    return result;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> findClassDeclaration(std::shared_ptr<::app_src_semantic_::ClassType> class_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto& _iterable_6 = context->allPrograms;
    for (const auto& program : *_iterable_6) {
        const auto& _iterable_7 = program->statements;
        for (const auto& statement : *_iterable_7) {
            const auto candidate = statementClass(statement);
            if ((((!doof::is_null(candidate)) && (!doof::is_null(candidate->resolvedSymbol))) && (candidate->resolvedSymbol->module == class_->symbol->module)) && (candidate->name == class_->name)) {
                return candidate;
            }
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> statementClass(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return class_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return statementClass(export_->declaration);
    }
    else {
            return nullptr;
    }
    }
    return nullptr;
}
std::string emitAssignmentTarget(std::string name, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return (::app_src_emitter_context_::isCapturedMutable(context, name) ? ((std::string("(*") + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(")")) : ::app_src_emitter_expr_::cppIdentifier(name));
}
std::string emitBindingElse(std::shared_ptr<::app_src_ast_::ImmutableBinding> binding, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    if (doof::is_null(binding->else_)) {
        return emitLocalDeclaration(ind, binding->name, binding->type_, doof::optional_value(doof::unwrap_optional(binding->resolvedType)), binding->value, context, true, false);
    }
    (context->tryCounter = (context->tryCounter + 1));
    const auto temporaryName = (std::string("_binding_value_") + doof::to_string(context->tryCounter));
    if ((!doof::is_null(doof::resolved_type(binding->value))) && isSingleOptional(doof::unwrap_optional(doof::resolved_type(binding->value)))) {
        auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(binding->value, context, std::monostate{})) + std::string(";\n"));
        (output = ((((output + ind) + std::string("if (doof::is_null(")) + temporaryName) + std::string(")) {\n")));
        if (doof::is_null(binding->failureName) && (binding->name != std::string("_"))) {
            (output = ((((((output + indent((level + 1))) + std::string("const auto& ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = ")) + temporaryName) + std::string(";\n")));
        }
        (output = (output + emitBlock(doof::unwrap_optional(binding->else_), (level + 1), context)));
        (output = ((output + ind) + std::string("}\n")));
        if (binding->name == std::string("_")) {
            return output;
        }
        return ((((((output + ind) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = doof::unwrap_optional(")) + temporaryName) + std::string(");\n"));
    }
    auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(binding->value, context, std::monostate{})) + std::string(";\n"));
    (output = ((((output + ind) + std::string("if (doof::is_failure(")) + temporaryName) + std::string(")) {\n")));
    if ((!doof::is_null(binding->failureName)) && (doof::unwrap_optional(binding->failureName) != std::string("_"))) {
        (output = ((((((output + indent((level + 1))) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(doof::unwrap_optional(binding->failureName))) + std::string(" = doof::failure_error(")) + temporaryName) + std::string(");\n")));
    } else if (binding->name != std::string("_")) {
        (output = ((((((output + indent((level + 1))) + std::string("const auto& ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = ")) + temporaryName) + std::string(";\n")));
    }
    (output = (output + emitBlock(doof::unwrap_optional(binding->else_), (level + 1), context)));
    (output = ((output + ind) + std::string("}\n")));
    if (binding->name == std::string("_")) {
        return output;
    }
    return ((((((output + ind) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n"));
}
bool isSingleOptional(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType) {
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            auto hasNull = false;
            const auto& _iterable_8 = union_->types;
            for (const auto& member : *_iterable_8) {
                if (doof::kind(member) == std::string("null")) {
                    (hasNull = true);
                }
            }
            return hasNull;
    }
    else {
            return false;
    }
    }
    return false;
}
std::string emitTry(std::shared_ptr<::app_src_ast_::TryStatement> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    (context->tryCounter = (context->tryCounter + 1));
    const auto temporaryName = (std::string("_try_value_") + doof::to_string(context->tryCounter));
    std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NullLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value = doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NullLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(std::make_shared<::app_src_ast_::Identifier>(std::string("identifier"), std::string("<try>"), std::monostate{}, nullptr, statement->span));
    {
        auto _case_subject = statement->binding;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            (value = binding->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            (value = declaration->value);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
            (value = expression->expression);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
            (value = destructuring->value);
    }
    }
    if (context->catchVarName != std::string("")) {
        auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, std::monostate{})) + std::string(";\n"));
        (output = ((((output + ind) + std::string("if (doof::is_failure(")) + temporaryName) + std::string(")) { ")));
        const auto errorType = doof::resolved_type(value);
        auto hasErrorValue = true;
        if (!doof::is_null(errorType)) {
            {
                auto _case_subject = doof::unwrap_optional(errorType);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                    if (doof::kind(result->errorType) == std::string("void")) {
                        (hasErrorValue = false);
                    }
            }
            else {
            }
            }
        }
        if (hasErrorValue) {
            auto promoted = ((std::string("doof::failure_error(") + temporaryName) + std::string(")"));
            if (!doof::is_null(context->catchResultType)) {
                (promoted = ((((std::string("doof::variant_promote<") + ::app_src_emitter_types_::emitType(doof::unwrap_optional(context->catchResultType), context->modulePath)) + std::string(">(")) + promoted) + std::string(")")));
            }
            (output = ((((output + context->catchVarName) + std::string(" = ")) + promoted) + std::string("; ")));
        }
        (output = (output + std::string("break; }\n")));
        {
            auto _case_subject = statement->binding;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
                (output = ((((((output + ind) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(declaration->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
                (output = ((((((output + ind) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(declaration->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
                (output = ((((((output + ind) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
                (output = ((((((output + ind) + std::string("auto ")) + ::app_src_emitter_expr_::cppIdentifier(declaration->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
                (output = (output + emitTryDestructuring(destructuring, temporaryName, level, context)));
        }
        }
        return output;
    }
    if (context->currentReturnErrorType != std::string("")) {
        const auto errorType = context->currentReturnErrorType;
        auto output = (((((ind + std::string("auto ")) + temporaryName) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(value, context, std::monostate{})) + std::string(";\n"));
        (output = ((((((((output + ind) + std::string("if (doof::is_failure(")) + temporaryName) + std::string(")) return doof::Failure<")) + errorType) + std::string(">{doof::failure_error(")) + temporaryName) + std::string(")};\n")));
        {
            auto _case_subject = statement->binding;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
                (output = ((((((output + ind) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(declaration->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
                (output = ((((((output + ind) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(declaration->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
                (output = ((((((output + ind) + std::string("const auto ")) + ::app_src_emitter_expr_::cppIdentifier(binding->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
                (output = ((((((output + ind) + std::string("auto ")) + ::app_src_emitter_expr_::cppIdentifier(declaration->name)) + std::string(" = doof::success_value(")) + temporaryName) + std::string(");\n")));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
                (output = (output + emitTryDestructuring(destructuring, temporaryName, level, context)));
        }
        }
        return output;
    }
    doof::panic(std::string("try expression is outside a Result-returning function"));
    return std::string("");
}
std::string emitTryDestructuring(std::shared_ptr<::app_src_ast_::DestructuringStatement> statement, std::string temporaryName, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> successType = std::monostate{};
    if (!doof::is_null(doof::resolved_type(statement->value))) {
        {
            auto _case_subject = doof::unwrap_optional(doof::resolved_type(statement->value));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                (successType = doof::optional_value(result->valueType));
        }
        else {
        }
        }
    }
    return emitDestructuringValue(statement, ((std::string("doof::success_value(") + temporaryName) + std::string(")")), successType, level, context);
}
std::string emitLocalDeclaration(std::string ind, std::string name, std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NullLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> value, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, bool readonly_, bool shallowImmutable) {
    if (doof::is_null(resolvedType)) {
        doof::panic(std::string("Local declaration was not resolved before emission"));
    }
    auto typeText = (doof::is_null(annotation) ? std::string("auto") : ::app_src_emitter_types_::emitType(doof::unwrap_optional(resolvedType), context->modulePath));
    auto shallowStruct = false;
    {
        auto _case_subject = doof::unwrap_optional(resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            (shallowStruct = (shallowImmutable && (class_->symbol->kind == std::string("struct"))));
    }
    else {
    }
    }
    auto prefix = ((readonly_ && !shallowStruct) ? std::string("const ") : std::string(""));
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = resolvedType;
    auto valueText = ::app_src_emitter_expr_::emitExpression(value, context, expected);
    if (!readonly_ && ::app_src_emitter_context_::isCapturedMutable(context, name)) {
        return (((((((ind + std::string("auto ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = std::make_shared<")) + ::app_src_emitter_types_::emitType(doof::unwrap_optional(resolvedType), context->modulePath)) + std::string(">(")) + valueText) + std::string(");\n"));
    }
    return (((((((ind + prefix) + typeText) + std::string(" ")) + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string(" = ")) + valueText) + std::string(";\n"));
}
std::string emitCase(std::shared_ptr<::app_src_ast_::CaseStatement> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    const auto inner = indent((level + 1));
    const auto bodyIndent = indent((level + 2));
    const auto subject = std::string("_case_subject");
    auto result = (((((((ind + std::string("{\n")) + inner) + std::string("auto ")) + subject) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(statement->subject, context, std::monostate{})) + std::string(";\n"));
    auto previous = false;
    const auto subjectType = caseSubjectType(statement->subject);
    if (doof::is_null(subjectType)) {
        doof::panic(std::string("Case statement subject has no resolved type"));
    }
    const auto& _iterable_9 = statement->arms;
    for (const auto& arm : *_iterable_9) {
        const auto& _iterable_10 = arm->patterns;
        for (const auto& pattern : *_iterable_10) {
            auto condition = std::string("");
            auto binding = std::string("");
            auto isWildcard = false;
            {
                auto _case_subject = pattern;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject)) {
                    const auto& type_ = std::get<std::shared_ptr<::app_src_ast_::TypePattern>>(_case_subject);
                    const auto bindingName = ((type_->name == std::string("_")) ? std::string("") : ::app_src_emitter_expr_::cppIdentifier(type_->name));
                    const auto emitted = ::app_src_emitter_case_pattern_::emitCaseTypePattern(type_, ::app_src_emitter_types_::specializeEmitType(doof::unwrap_optional(subjectType), context), subject, bindingName, context->modulePath);
                    (condition = emitted->condition);
                    (binding = emitted->binding);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject)) {
                    const auto& value = std::get<std::shared_ptr<::app_src_ast_::ValuePattern>>(_case_subject);
                    (condition = ((subject + std::string(" == ")) + ::app_src_emitter_expr_::emitExpression(value->value, context, std::monostate{})));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject)) {
                    const auto& range = std::get<std::shared_ptr<::app_src_ast_::RangePattern>>(_case_subject);
                    (condition = emitRangePatternCondition(range, subject, context));
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WildcardPattern>>(_case_subject)) {
                    (isWildcard = true);
            }
            }
            if (isWildcard) {
                (result = (result + (previous ? (ind + std::string("else {\n")) : (inner + std::string("{\n")))));
            } else {
                (result = (result + (previous ? (((ind + std::string("else if (")) + condition) + std::string(") {\n")) : (((inner + std::string("if (")) + condition) + std::string(") {\n")))));
            }
            if (binding != std::string("")) {
                (result = ((result + bodyIndent) + binding));
            }
            {
                auto _case_subject = arm->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                    (result = (((result + emitBlock(block, (level + 2), context)) + ind) + std::string("}\n")));
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NullLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    doof::panic(std::string("Expression case arm reached statement emitter"));
            }
            }
            (previous = true);
            if (isWildcard) {
                return ((result + ind) + std::string("}\n"));
            }
        }
    }
    return ((result + ind) + std::string("}\n"));
}
std::string emitRangePatternCondition(std::shared_ptr<::app_src_ast_::RangePattern> pattern, std::string subject, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto condition = std::string("");
    if (!doof::is_null(pattern->start)) {
        (condition = ((subject + std::string(" >= ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(pattern->start), context, std::monostate{})));
    }
    if (!doof::is_null(pattern->end)) {
        const auto operator_ = (pattern->inclusive ? std::string(" <= ") : std::string(" < "));
        if (condition != std::string("")) {
            (condition = (condition + std::string(" && ")));
        }
        (condition = (((condition + subject) + operator_) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(pattern->end), context, std::monostate{})));
    }
    return condition;
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> caseSubjectType(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NullLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression) {
    if (!doof::is_null(doof::resolved_type(expression))) {
        return doof::resolved_type(expression);
    }
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (!doof::is_null(identifier->resolvedBinding)) {
                return doof::optional_value(identifier->resolvedBinding->type_);
            }
    }
    else {
    }
    }
    return std::monostate{};
}
std::string emitReturn(std::shared_ptr<::app_src_ast_::ReturnStatement> statement, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (doof::is_null(statement->value)) {
        return std::string("return;\n");
    }
    const auto expected = statement->resolvedExpectedType;
    return ((std::string("return ") + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(statement->value), context, expected)) + std::string(";\n"));
}
std::string emitIf(std::shared_ptr<::app_src_ast_::IfStatement> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    auto result = (((ind + std::string("if (")) + emitCondition(statement->condition, context)) + std::string(") {\n"));
    (result = (((result + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}")));
    const auto& _iterable_11 = statement->elseIfs;
    for (const auto& branch : *_iterable_11) {
        (result = (((result + std::string(" else if (")) + emitCondition(branch->condition, context)) + std::string(") {\n")));
        (result = (((result + emitBlock(branch->body, (level + 1), context)) + ind) + std::string("}")));
    }
    if (!doof::is_null(statement->else_)) {
        (result = ((((result + std::string(" else {\n")) + emitBlock(doof::unwrap_optional(statement->else_), (level + 1), context)) + ind) + std::string("}")));
    }
    return (result + std::string("\n"));
}
std::string emitWhile(std::shared_ptr<::app_src_ast_::WhileStatement> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    return ((((((ind + std::string("while (")) + emitCondition(statement->condition, context)) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
}
std::string emitForOf(std::shared_ptr<::app_src_ast_::ForOfStatement> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    const auto name = ((static_cast<int32_t>((statement->bindings)->size()) == 0) ? std::string("_item") : ::app_src_emitter_expr_::cppIdentifier((*statement->bindings)[0]));
    {
        auto _case_subject = statement->iterable;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& range = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
            if ((range->operator_ == std::string("..<")) || (range->operator_ == std::string(".."))) {
                const auto endOperator = ((range->operator_ == std::string("..<")) ? std::string(" < ") : std::string(" <= "));
                return ((((((((((((((ind + std::string("for (int32_t ")) + name) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(range->left, context, std::monostate{})) + std::string("; ")) + name) + endOperator) + ::app_src_emitter_expr_::emitExpression(range->right, context, std::monostate{})) + std::string("; ++")) + name) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
            }
    }
    else {
    }
    }
    const auto iterable = ::app_src_emitter_expr_::emitExpression(statement->iterable, context, std::monostate{});
    (context->tryCounter = (context->tryCounter + 1));
    const auto iterableName = (std::string("_iterable_") + doof::to_string(context->tryCounter));
    const auto iterableBinding = (((((ind + std::string("const auto& ")) + iterableName) + std::string(" = ")) + iterable) + std::string(";\n"));
    if (!doof::is_null(doof::resolved_type(statement->iterable))) {
        {
            auto _case_subject = doof::unwrap_optional(doof::resolved_type(statement->iterable));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
                return (((((((((iterableBinding + ind) + std::string("for (const auto& ")) + name) + std::string(" : ")) + iterableName) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                return (((((((((((((iterableBinding + ind) + std::string("while (std::visit([](auto&& _obj) { return _obj->next(); }, ")) + iterableName) + std::string(")) {\n")) + ind) + std::string("    const auto ")) + name) + std::string(" = std::visit([](auto&& _obj) { return _obj->value(); }, ")) + iterableName) + std::string(");\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
        }
        else {
        }
        }
    }
    if (static_cast<int32_t>((statement->bindings)->size()) > 1) {
        auto names = std::string("");
        for (int32_t i = 0; i < static_cast<int32_t>((statement->bindings)->size()); ++i) {
            if (i > 0) {
                (names = (names + std::string(", ")));
            }
            (names = (names + ::app_src_emitter_expr_::cppIdentifier((*statement->bindings)[i])));
        }
        return (((((((((iterableBinding + ind) + std::string("for (const auto& [")) + names) + std::string("] : *")) + iterableName) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
    }
    return (((((((((iterableBinding + ind) + std::string("for (const auto& ")) + name) + std::string(" : *")) + iterableName) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
}
std::string emitFor(std::shared_ptr<::app_src_ast_::ForStatement> statement, int32_t level, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto ind = indent(level);
    auto init = std::string("");
    if (!doof::is_null(statement->init)) {
        (init = doof::string_trim(emitStatement(doof::unwrap_optional(statement->init), 0, context)));
        if (doof::string_endsWith(init, std::string(";"))) {
            (init = doof::string_substring(init, 0, (static_cast<int32_t>(init.size()) - 1)));
        }
    }
    auto condition = std::string("true");
    if (!doof::is_null(statement->condition)) {
        (condition = emitCondition(doof::unwrap_optional(statement->condition), context));
    }
    auto update = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((statement->update)->size()); ++i) {
        if (i > 0) {
            (update = (update + std::string(", ")));
        }
        (update = (update + ::app_src_emitter_expr_::emitExpression((*statement->update)[i], context, std::monostate{})));
    }
    return ((((((((((ind + std::string("for (")) + init) + std::string("; ")) + condition) + std::string("; ")) + update) + std::string(") {\n")) + emitBlock(statement->body, (level + 1), context)) + ind) + std::string("}\n"));
}
std::string indent(int32_t level) {
    return doof::string_repeat(std::string("    "), level);
}
std::string emitCondition(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NullLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto value = ::app_src_emitter_expr_::emitExpression(expression, context, std::monostate{});
    if (doof::string_startsWith(value, std::string("(")) && doof::string_endsWith(value, std::string(")"))) {
        return doof::string_substring(value, 1, (static_cast<int32_t>(value.size()) - 1));
    }
    return value;
}
}
