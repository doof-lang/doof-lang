#include "src_emitter_expr_calls.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_checker_types.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_expr_utils.hpp"
#include "src_emitter_types.hpp"
#include "src_emitter_monomorphize.hpp"
#include "src_emitter_expr_actor.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_expr_calls_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_expr_actor_;
std::string emitCall(std::shared_ptr<::app_src_ast_::CallExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected) {
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (isBuiltinIdentifier(identifier, std::string("catchPanic")) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
                {
                    auto _case_subject = doof::unwrap_optional(expression->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                        const auto callback = ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{});
                        const auto successType = ::app_src_emitter_types_::emitResultPayloadType(result->valueType, context->modulePath);
                        if (std::visit([](auto&& _obj) { return _obj->kind; }, result->valueType) == std::string("none")) {
                            return ((std::string("[&]() -> doof::Result<void, std::string> { try { ") + callback) + std::string(".call(); return doof::Success<void>{}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }()"));
                        }
                        return ((((((std::string("[&]() -> doof::Result<") + successType) + std::string(", std::string> { try { return doof::Success<")) + successType) + std::string(">{")) + callback) + std::string(".call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }()"));
                }
                else {
                        doof::panic(std::string("catchPanic has no Result type"));
                }
                }
            }
    }
    else {
    }
    }
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (((identifier->name == std::string("Success")) || (identifier->name == std::string("Failure"))) && isBuiltinIdentifier(identifier, identifier->name)) {
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resultType = std::monostate{};
                if (!doof::is_null(expected)) {
                    (resultType = doof::optional_value(doof::unwrap_optional(expected)));
                } else if (!doof::is_null(expression->resolvedType)) {
                    (resultType = doof::optional_value(doof::unwrap_optional(expression->resolvedType)));
                }
                if (doof::is_null(resultType)) {
                    doof::panic((identifier->name + std::string(" has no expected Result type")));
                }
                {
                    auto _case_subject = doof::unwrap_optional(resultType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                        if (static_cast<int32_t>((expression->args)->size()) == 0) {
                            return ((((std::string("doof::") + identifier->name) + std::string("<")) + ::app_src_emitter_types_::emitResultPayloadType(((identifier->name == std::string("Success")) ? result->valueType : result->errorType), context->modulePath)) + std::string(">{}"));
                        }
                        const auto valueType = ((identifier->name == std::string("Success")) ? result->valueType : result->errorType);
                        const auto value = ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, doof::optional_value(valueType));
                        const auto payloadType = ::app_src_emitter_types_::emitResultPayloadType(valueType, context->modulePath);
                        return ((((((std::string("doof::") + identifier->name) + std::string("<")) + payloadType) + std::string(">{ ")) + value) + std::string(" }"));
                }
                else {
                }
                }
            }
    }
    else {
    }
    }
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                        const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
                        return ::app_src_emitter_expr_actor_::emitSyncActorCall(expression, member, actor, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& resultType = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                        if (member->property == std::string("isSuccess")) {
                            return ((std::string("doof::is_success(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
                        }
                        if (member->property == std::string("isFailure")) {
                            return ((std::string("doof::is_failure(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
                        }
                        if ((member->property == std::string("unwrapOr")) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
                            const auto temporaryName = (std::string("_result_unwrap_") + doof::to_string(context->tryCounter));
                            (context->tryCounter += 1);
                            const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
                            const auto fallback = ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, doof::optional_value(resultType->valueType));
                            return ((((((((((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(resultType->valueType, context->modulePath)) + std::string(" { auto ")) + temporaryName) + std::string(" = ")) + object) + std::string("; if (doof::is_failure(")) + temporaryName) + std::string(")) return ")) + fallback) + std::string("; return std::move(doof::success_value(")) + temporaryName) + std::string(")); }()"));
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
    auto nativeConstructorCall = false;
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            (nativeConstructorCall = true);
    }
    else {
    }
    }
    if ((nativeConstructorCall && (!doof::is_null(expression->resolvedConstructor))) && (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee)))) {
        {
            auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& owner = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                return emitConstructorFactoryCall(owner, doof::unwrap_optional(expression->resolvedConstructor), expression->args, context, expression->span);
        }
        else {
        }
        }
    }
    if ((nativeConstructorCall && isClassCallee(expression->callee)) && (!doof::is_null(expression->resolvedType))) {
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                if (class_->symbol->native_) {
                    const auto nativeName = (std::string("::") + ((class_->symbol->nativeCppName == std::string("")) ? class_->symbol->name : class_->symbol->nativeCppName));
                    if (doof::is_null(expression->resolvedConstructor)) {
                        return ((std::string("std::make_shared<") + nativeName) + std::string(">()"));
                    }
                    auto result = (nativeName + std::string("::constructor("));
                    const auto constructorMethod = expression->resolvedConstructor;
                    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
                        if (i > 0) {
                            (result = (result + std::string(", ")));
                        }
                        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedArgument = std::monostate{};
                        if ((!doof::is_null(constructorMethod)) && (i < static_cast<int32_t>((constructorMethod->params)->size()))) {
                            (expectedArgument = (*constructorMethod->params)[i]->resolvedType);
                        }
                        auto argumentText = ::app_src_emitter_expr_::emitExpression((*expression->args)[i]->value, context, expectedArgument);
                        (result = (result + argumentText));
                    }
                    if (!doof::is_null(constructorMethod)) {
                        for (int32_t i = static_cast<int32_t>((expression->args)->size()); i < static_cast<int32_t>((constructorMethod->params)->size()); ++i) {
                            if (result != (nativeName + std::string("::constructor("))) {
                                (result = (result + std::string(", ")));
                            }
                            if (doof::is_null((*constructorMethod->params)[i]->defaultValue)) {
                                doof::panic(((std::string("Native constructor ") + class_->name) + std::string(" is missing a default argument")));
                            }
                            (result = (result + emitDefaultExpression(doof::unwrap_optional((*constructorMethod->params)[i]->defaultValue), context, (*constructorMethod->params)[i]->resolvedType, expression->span)));
                        }
                    }
                    return (result + std::string(")"));
                }
                if ((!doof::is_null(expression->resolvedConstructor)) || isClassCallee(expression->callee)) {
                    auto cppName = (((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(class_->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(class_->symbol)) : ::app_src_emitter_expr_utils_::emittedSymbolName(class_->symbol));
                    const auto concrete = concreteClassName(class_, context);
                    if (concrete != std::string("")) {
                        (cppName = concrete);
                    }
                    auto values = std::string("");
                    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
                        if (i > 0) {
                            (values = (values + std::string(", ")));
                        }
                        (values = (values + ::app_src_emitter_expr_::emitExpression((*expression->args)[i]->value, context, std::monostate{})));
                    }
                    if (!doof::is_null(expression->resolvedClass)) {
                        auto fieldIndex = 0;
                        const auto& _iterable_1 = expression->resolvedClass->fields;
                        for (const auto& field : *_iterable_1) {
                            if (field->static_ || field->const_) {
                                continue;
                            }
                            const auto& _iterable_2 = field->names;
                            for (const auto& name : *_iterable_2) {
                                if (fieldIndex >= static_cast<int32_t>((expression->args)->size())) {
                                    if (values != std::string("")) {
                                        (values = (values + std::string(", ")));
                                    }
                                    if (doof::is_null(field->defaultValue)) {
                                        doof::panic(((((std::string("Construction of '") + class_->name) + std::string("' is missing required field '")) + name) + std::string("'")));
                                    }
                                    (values = (values + emitDefaultExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType, expression->span)));
                                }
                                (fieldIndex = (fieldIndex + 1));
                            }
                        }
                    }
                    return ((class_->symbol->kind == std::string("struct")) ? (((cppName + std::string("{")) + values) + std::string("}")) : ((((std::string("std::make_shared<") + cppName) + std::string(">(")) + values) + std::string(")")));
                }
        }
        else {
        }
        }
    }
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            const auto arrayObjectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
            auto nominalReceiver = false;
            if (!doof::is_null(arrayObjectType)) {
                {
                    auto _case_subject = doof::unwrap_optional(arrayObjectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        (nominalReceiver = true);
                }
                else {
                }
                }
            }
            if (member->property == std::string("length")) {
                if (!doof::is_null(arrayObjectType)) {
                    {
                        auto _case_subject = doof::unwrap_optional(arrayObjectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            return ((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + ((class_->symbol->kind == std::string("struct")) ? std::string(".") : std::string("->"))) + std::string("length()"));
                    }
                    else {
                    }
                    }
                }
            }
            if (!doof::is_null(arrayObjectType)) {
                {
                    auto _case_subject = doof::unwrap_optional(arrayObjectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                        if (member->property == std::string("fromJsonValue")) {
                            return emitInterfaceJsonCall(member, expression, context);
                        }
                        return emitVariantMemberCall(member, expression, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                        return emitInterfaceCall(member, expression, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                        const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                        if (::app_src_emitter_types_::usesVariantRepresentation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) {
                            return emitVariantMemberCall(member, expression, context);
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                        if (member->property == std::string("buildReadonly")) {
                            return ((std::string("doof::array_buildReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneMutable")) {
                            return ((std::string("doof::array_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("contains")) {
                            return ((((std::string("doof::array_contains(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("indexOf")) {
                            return ((((std::string("doof::array_indexOf(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("some")) {
                            return ((((std::string("doof::array_some(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("every")) {
                            return ((((std::string("doof::array_every(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("filter")) {
                            return ((((std::string("doof::array_filter(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("map")) {
                            return ((((std::string("doof::array_map(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                        const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
                        if (member->property == std::string("has")) {
                            return ((((((std::string("(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string("->find(")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(") != ")) + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string("->end())"));
                        }
                        if (member->property == std::string("set")) {
                            return ((((((std::string("doof::map_set(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_utils_::emitExpectedExpression((*expression->args)[0]->value, context, doof::optional_value(map->keyType))) + std::string(", ")) + ::app_src_emitter_expr_utils_::emitExpectedExpression((*expression->args)[1]->value, context, doof::optional_value(map->valueType))) + std::string(", \"\", 0)"));
                        }
                        if ((member->property == std::string("get")) && (static_cast<int32_t>((expression->args)->size()) > 0)) {
                            return ((((std::string("doof::map_get(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("keys")) {
                            return ((std::string("doof::map_keys(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("values")) {
                            return ((std::string("doof::map_values(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("buildReadonly")) {
                            return ((std::string("doof::map_buildReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneMutable")) {
                            return ((std::string("doof::map_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                        if (member->property == std::string("has")) {
                            return ((((std::string("(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string("->count(")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(") > 0)"));
                        }
                        if (member->property == std::string("add")) {
                            return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("->insert(")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(")"));
                        }
                        if (member->property == std::string("delete")) {
                            return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("->erase(")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(")"));
                        }
                        if (member->property == std::string("values")) {
                            return ((std::string("doof::set_values(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("buildReadonly")) {
                            return ((std::string("doof::set_buildReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                        if (member->property == std::string("cloneMutable")) {
                            return ((std::string("doof::set_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
                        const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
                        if ((member->property == std::string("fromName")) || (member->property == std::string("fromValue"))) {
                            const auto args = ((static_cast<int32_t>((expression->args)->size()) == 0) ? std::string("") : ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{}));
                            return (((((::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context) + std::string("_")) + member->property) + std::string("(")) + args) + std::string(")"));
                        }
                }
                else {
                }
                }
            }
            if (!nominalReceiver && (member->property == std::string("startsWith"))) {
                return emitBuiltinCall(std::string("doof::string_startsWith"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("endsWith"))) {
                return emitBuiltinCall(std::string("doof::string_endsWith"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("substring"))) {
                return emitBuiltinCall(std::string("doof::string_substring"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("replaceAll"))) {
                return emitBuiltinCall(std::string("doof::string_replaceAll"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("contains"))) {
                return emitBuiltinCall(std::string("doof::string_contains"), member->object, expression, context);
            }
            if (!nominalReceiver && (member->property == std::string("indexOf"))) {
                return emitBuiltinCall(std::string("doof::string_indexOf"), member->object, expression, context);
            }
            const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
            if (!doof::is_null(objectType)) {
                {
                    auto _case_subject = doof::unwrap_optional(objectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                        if ((member->property == std::string("slice")) && (static_cast<int32_t>((expression->args)->size()) == 2)) {
                            return ((((((std::string("doof::array_slice(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[1]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else {
                }
                }
            }
            if ((!nominalReceiver && (member->property == std::string("trim"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                return ((std::string("doof::string_trim(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("trimStart"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                return ((std::string("doof::string_trimStart(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("repeat"))) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
                return ((((std::string("doof::string_repeat(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("slice"))) {
                return ((((std::string("doof::string_slice(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("charAt"))) {
                return ((((std::string("doof::string_at(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", \"\", 0)"));
            }
            if (!nominalReceiver && (member->property == std::string("padStart"))) {
                const auto fill = ((static_cast<int32_t>((expression->args)->size()) > 1) ? ::app_src_emitter_expr_::emitExpression((*expression->args)[1]->value, context, std::monostate{}) : std::string("' '"));
                return ((((((std::string("doof::string_padStart(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(", ")) + fill) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("trimEnd"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                return ((std::string("doof::string_trimEnd(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("trimEnd"))) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
                return ((((std::string("doof::string_trimEnd(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("toLowerCase"))) {
                return ((std::string("doof::string_toLowerCase(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("toUpperCase"))) {
                return ((std::string("doof::string_toUpperCase(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if (!nominalReceiver && (member->property == std::string("split"))) {
                return ((((std::string("doof::string_split(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(")"));
            }
            if ((!nominalReceiver && (member->property == std::string("pop"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                return ((std::string("doof::array_pop(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
            if ((member->property == std::string("toJsonObject")) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
                const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
                const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
                if (!doof::is_null(objectType)) {
                    {
                        auto _case_subject = doof::unwrap_optional(objectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            if (class_->symbol->kind == std::string("struct")) {
                                return (object + std::string(".toJsonObject()"));
                            }
                    }
                    else {
                    }
                    }
                }
                return (object + std::string("->toJsonObject()"));
            }
            {
                auto _case_subject = member->object;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                    const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
                    if ((member->property == std::string("parse")) && isBuiltinTypeNamespace(identifier)) {
                        return ((((std::string("doof::parse_") + identifier->name) + std::string("(")) + ::app_src_emitter_expr_::emitExpression((*expression->args)[0]->value, context, std::monostate{})) + std::string(")"));
                    }
            }
            else {
            }
            }
            if ((member->property == std::string("fromJsonValue")) && (!nominalReceiver || (!doof::is_null(member->resolvedStaticOwner)))) {
                const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
                auto args = std::string("");
                for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
                    if (i > 0) {
                        (args = (args + std::string(", ")));
                    }
                    (args = (args + ::app_src_emitter_expr_::emitExpression((*expression->args)[i]->value, context, std::monostate{})));
                }
                const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
                if (!doof::is_null(objectType)) {
                    {
                        auto _case_subject = doof::unwrap_optional(objectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                            return (((object + std::string("_fromJsonValue(")) + args) + std::string(")"));
                    }
                    else {
                    }
                    }
                }
                return (((object + std::string("::fromJsonValue(")) + args) + std::string(")"));
            }
    }
    else {
    }
    }
    auto callee = ::app_src_emitter_expr_::emitExpression(expression->callee, context, std::monostate{});
    if (std::visit([](auto&& _obj) { return _obj->kind; }, expression->callee) == std::string("identifier")) {
        {
            auto _case_subject = expression->callee;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
                if (((!doof::is_null(identifier->resolvedBinding)) && (identifier->resolvedBinding->kind == std::string("builtin"))) && isBuiltinName(identifier->name)) {
                    (callee = builtinName(identifier->name));
                }
        }
        else {
        }
        }
    }
    std::shared_ptr<::app_src_semantic_::FunctionType> functionType = nullptr;
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee))) {
        {
            auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                (functionType = resolved);
        }
        else {
        }
        }
    }
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> concreteGenericArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    const auto& _iterable_3 = expression->resolvedGenericTypeArgs;
    for (const auto& argument : *_iterable_3) {
        concreteGenericArgs->push_back(::app_src_emitter_types_::specializeEmitType(argument, context));
    }
    if ((!doof::is_null(functionType)) && (static_cast<int32_t>((concreteGenericArgs)->size()) > 0)) {
        const auto substituted = ::app_src_checker_types_::substituteTypeParams(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(functionType)), functionType->typeParams, concreteGenericArgs);
        {
            auto _case_subject = substituted;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& specialized = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                (functionType = specialized);
        }
        else {
        }
        }
    }
    const auto functionDeclaration = expression->resolvedFunction;
    auto usesConcreteInstantiation = false;
    if ((!doof::is_null(functionDeclaration)) && (static_cast<int32_t>((functionDeclaration->typeParams)->size()) > 0)) {
        auto targetModule = context->modulePath;
        auto concreteMethodName = std::string("");
        {
            auto _case_subject = expression->callee;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
                if (!doof::is_null(identifier->resolvedBinding)) {
                    if (!doof::is_null(identifier->resolvedBinding->symbol)) {
                        (targetModule = identifier->resolvedBinding->symbol->module);
                    } else if (identifier->resolvedBinding->module != std::string("")) {
                        (targetModule = identifier->resolvedBinding->module);
                    }
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
                    {
                        auto _case_subject = ::app_src_emitter_types_::specializeEmitType(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)), context);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            (targetModule = class_->symbol->module);
                            const auto ownerKey = ::app_src_emitter_monomorphize_::classInstantiationKey(class_->symbol->module, class_->name, class_->typeArgs);
                            const auto methodKey = ::app_src_emitter_monomorphize_::methodInstantiationKey(ownerKey, functionDeclaration->name, concreteGenericArgs);
                            (concreteMethodName = concreteMethodNameFor(context, methodKey));
                    }
                    else {
                    }
                    }
                }
        }
        else {
        }
        }
        if (concreteMethodName != std::string("")) {
            (usesConcreteInstantiation = true);
            {
                auto _case_subject = expression->callee;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                    const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                    (callee = (doof::string_substring(callee, 0, (static_cast<int32_t>(callee.size()) - static_cast<int32_t>(member->property.size()))) + concreteMethodName));
            }
            else {
            }
            }
        } else {
            const auto key = ::app_src_emitter_monomorphize_::functionInstantiationKey(targetModule, functionDeclaration->name, concreteGenericArgs);
            const auto concreteName = concreteFunctionName(context, key);
            if (concreteName != std::string("")) {
                (usesConcreteInstantiation = true);
                (callee = (((targetModule != std::string("")) && (targetModule != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(targetModule)) + std::string("::")) + concreteName) : concreteName));
            }
        }
    }
    if ((((static_cast<int32_t>((concreteGenericArgs)->size()) > 0) && (!doof::is_null(functionDeclaration))) && (static_cast<int32_t>((functionDeclaration->typeParams)->size()) > 0)) && !usesConcreteInstantiation) {
        (callee = (callee + std::string("<")));
        for (int32_t i = 0; i < static_cast<int32_t>((concreteGenericArgs)->size()); ++i) {
            if (i > 0) {
                (callee = (callee + std::string(", ")));
            }
            (callee = (callee + ::app_src_emitter_types_::emitContextType((*concreteGenericArgs)[i], context)));
        }
        (callee = (callee + std::string(">")));
    }
    auto invokesCallback = false;
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            (invokesCallback = ((!(((!doof::is_null(identifier->resolvedBinding)) && (identifier->resolvedBinding->kind == std::string("builtin"))) && isBuiltinName(identifier->name)) && (!doof::is_null(functionType))) && doof::is_null(functionDeclaration)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            (invokesCallback = (member->resolvedCallableField && (!doof::is_null(functionType))));
    }
    else {
            (invokesCallback = ((!doof::is_null(functionType)) && doof::is_null(functionDeclaration)));
    }
    }
    const auto callPrefix = (invokesCallback ? (callee + std::string(".call(")) : (callee + std::string("(")));
    auto result = callPrefix;
    auto named = false;
    const auto& _iterable_4 = expression->args;
    for (const auto& argument : *_iterable_4) {
        if (!doof::is_null(argument->name)) {
            (named = true);
        }
    }
    if (named && (!doof::is_null(functionDeclaration))) {
        for (int32_t i = 0; i < static_cast<int32_t>((functionDeclaration->params)->size()); ++i) {
            const auto parameter = (*functionDeclaration->params)[i];
            const auto argument = callArgumentNamed(expression, parameter->name);
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = parameter->resolvedType;
            if ((!doof::is_null(functionType)) && (i < static_cast<int32_t>((functionType->params)->size()))) {
                (expected = ::app_src_emitter_expr_utils_::optionalExpectedType((*functionType->params)[i]->type_));
            }
            if ((!doof::is_null(argument)) || (!doof::is_null(parameter->defaultValue))) {
                if (result != callPrefix) {
                    (result = (result + std::string(", ")));
                }
                if (!doof::is_null(argument)) {
                    (result = (result + ::app_src_emitter_expr_utils_::emitExpectedExpression(argument->value, context, expected)));
                } else {
                    (result = (result + emitDefaultExpression(doof::unwrap_optional(parameter->defaultValue), context, expected, expression->span)));
                }
            }
        }
    } else if (named && (!doof::is_null(functionType))) {
        const auto& _iterable_5 = functionType->params;
        for (const auto& parameter : *_iterable_5) {
            const auto argument = callArgumentNamed(expression, parameter->name);
            if (!doof::is_null(argument)) {
                if (result != callPrefix) {
                    (result = (result + std::string(", ")));
                }
                (result = (result + ::app_src_emitter_expr_utils_::emitExpectedExpression(argument->value, context, ::app_src_emitter_expr_utils_::optionalExpectedType(parameter->type_))));
            }
        }
    } else {
        for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
            if (i > 0) {
                (result = (result + std::string(", ")));
            }
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
            if ((!doof::is_null(functionType)) && (i < static_cast<int32_t>((functionType->params)->size()))) {
                (expected = ::app_src_emitter_expr_utils_::optionalExpectedType((*functionType->params)[i]->type_));
            }
            if ((doof::is_null(expected) && (!doof::is_null(functionDeclaration))) && (i < static_cast<int32_t>((functionDeclaration->params)->size()))) {
                (expected = (*functionDeclaration->params)[i]->resolvedType);
            }
            {
                auto _case_subject = expression->callee;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                    const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
                    if (isBuiltinIdentifier(identifier, std::string("println")) || isBuiltinConversionIdentifier(identifier)) {
                        (expected = std::monostate{});
                    }
            }
            else {
            }
            }
            auto argument = ::app_src_emitter_expr_utils_::emitExpectedExpression((*expression->args)[i]->value, context, expected);
            (result = (result + argument));
        }
        if (!doof::is_null(functionDeclaration)) {
            for (int32_t i = static_cast<int32_t>((expression->args)->size()); i < static_cast<int32_t>((functionDeclaration->params)->size()); ++i) {
                const auto parameter = (*functionDeclaration->params)[i];
                if (!doof::is_null(parameter->defaultValue)) {
                    if (result != callPrefix) {
                        (result = (result + std::string(", ")));
                    }
                    (result = (result + emitDefaultExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType, expression->span)));
                }
            }
        }
    }
    return (result + std::string(")"));
}
bool isBuiltinTypeNamespace(std::shared_ptr<::app_src_ast_::Identifier> identifier) {
    if (doof::is_null(identifier->resolvedBinding) || (identifier->resolvedBinding->kind != std::string("builtin-type-namespace"))) {
        return false;
    }
    const auto name = identifier->name;
    return (((((name == std::string("byte")) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double")));
}
bool isBuiltinConversionIdentifier(std::shared_ptr<::app_src_ast_::Identifier> identifier) {
    if (doof::is_null(identifier->resolvedBinding) || (identifier->resolvedBinding->kind != std::string("builtin"))) {
        return false;
    }
    const auto name = identifier->name;
    return ((((((((name == std::string("string")) || (name == std::string("byte"))) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double"))) || (name == std::string("char"))) || (name == std::string("bool")));
}
bool isBuiltinIdentifier(std::shared_ptr<::app_src_ast_::Identifier> identifier, std::string name) {
    return (((identifier->name == name) && (!doof::is_null(identifier->resolvedBinding))) && (identifier->resolvedBinding->kind == std::string("builtin")));
}
bool isClassCallee(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> callee) {
    {
        auto _case_subject = callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (doof::is_null(identifier->resolvedBinding)) {
                return false;
            }
            const auto binding = doof::unwrap_optional(identifier->resolvedBinding);
            if ((binding->kind == std::string("class")) || (binding->kind == std::string("struct"))) {
                return true;
            }
            if ((binding->kind == std::string("import")) && (!doof::is_null(binding->symbol))) {
                return ((binding->symbol->kind == std::string("class")) || (binding->symbol->kind == std::string("struct")));
            }
            return false;
    }
    else {
            return false;
    }
    }
}
std::shared_ptr<::app_src_ast_::CallArgument> callArgumentNamed(std::shared_ptr<::app_src_ast_::CallExpression> expression, std::string name) {
    const auto& _iterable_6 = expression->args;
    for (const auto& argument : *_iterable_6) {
        if (argument->name == name) {
            return argument;
        }
    }
    return nullptr;
}
std::string emitBuiltinCall(std::string name, std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> object, std::shared_ptr<::app_src_ast_::CallExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto result = ((name + std::string("(")) + ::app_src_emitter_expr_::emitExpression(object, context, std::monostate{}));
    const auto& _iterable_7 = expression->args;
    for (const auto& argument : *_iterable_7) {
        (result = ((result + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(argument->value, context, std::monostate{})));
    }
    return (result + std::string(")"));
}
std::string emitInterfaceCall(std::shared_ptr<::app_src_ast_::MemberExpression> member, std::shared_ptr<::app_src_ast_::CallExpression> call, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
    auto args = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
        if (i > 0) {
            (args = (args + std::string(", ")));
        }
        (args = (args + ::app_src_emitter_expr_::emitExpression((*call->args)[i]->value, context, std::monostate{})));
    }
    return ((((((std::string("std::visit([&](auto&& _obj) { return _obj->") + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }, ")) + object) + std::string(")"));
}
std::string emitVariantMemberCall(std::shared_ptr<::app_src_ast_::MemberExpression> member, std::shared_ptr<::app_src_ast_::CallExpression> call, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
    const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
    if (doof::is_null(objectType)) {
        doof::panic(std::string("Variant member call has no resolved object type"));
    }
    auto args = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
        if (i > 0) {
            (args = (args + std::string(", ")));
        }
        (args = (args + ::app_src_emitter_expr_::emitExpression((*call->args)[i]->value, context, std::monostate{})));
    }
    const auto invocation = (member->resolvedCallableField ? std::string(".call(") : std::string("("));
    return ((((((std::string("std::visit([&](auto&& _obj) { return _obj->") + ::app_src_emitter_expr_::cppIdentifier(member->property)) + invocation) + args) + std::string("); }, ")) + ::app_src_emitter_expr_utils_::variantVisitValue(object, doof::unwrap_optional(objectType))) + std::string(")"));
}
std::string emitInterfaceJsonCall(std::shared_ptr<::app_src_ast_::MemberExpression> member, std::shared_ptr<::app_src_ast_::CallExpression> call, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto args = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
        if (i > 0) {
            (args = (args + std::string(", ")));
        }
        (args = (args + ::app_src_emitter_expr_::emitExpression((*call->args)[i]->value, context, std::monostate{})));
    }
    return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("_fromJsonValue(")) + args) + std::string(")"));
}
std::string builtinName(std::string name) {
    if (name == std::string("println")) {
        return std::string("doof::println");
    }
    if (name == std::string("panic")) {
        return std::string("doof::panic");
    }
    if (name == std::string("assert")) {
        return std::string("doof::assert_");
    }
    if (name == std::string("string")) {
        return std::string("doof::to_string");
    }
    if (name == std::string("byte")) {
        return std::string("static_cast<uint8_t>");
    }
    if (name == std::string("int")) {
        return std::string("static_cast<int32_t>");
    }
    if (name == std::string("long")) {
        return std::string("static_cast<int64_t>");
    }
    if (name == std::string("float")) {
        return std::string("static_cast<float>");
    }
    if (name == std::string("double")) {
        return std::string("static_cast<double>");
    }
    if (name == std::string("char")) {
        return std::string("static_cast<char32_t>");
    }
    if (name == std::string("bool")) {
        return std::string("static_cast<bool>");
    }
    return name;
}
bool isBuiltinName(std::string name) {
    return ((((((((((((name == std::string("println")) || (name == std::string("panic"))) || (name == std::string("assert"))) || (name == std::string("catchPanic"))) || (name == std::string("string"))) || (name == std::string("byte"))) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double"))) || (name == std::string("char"))) || (name == std::string("bool")));
}
std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaredConstructor(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_) {
    const auto& _iterable_8 = class_->methods;
    for (const auto& method : *_iterable_8) {
        if (method->name == std::string("constructor")) {
            return method;
        }
    }
    return nullptr;
}
bool insideDeclaredConstructor(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    return ((context->currentClass == class_->name) && (context->currentFunctionName == std::string("constructor")));
}
std::string emitConstruct(std::shared_ptr<::app_src_ast_::ConstructExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if ((expression->type_ == std::string("Success")) || (expression->type_ == std::string("Failure"))) {
        const auto resultType = expression->resolvedType;
        if (doof::is_null(resultType)) {
            doof::panic((expression->type_ + std::string(" has no resolved Result type")));
        }
        {
            auto _case_subject = doof::unwrap_optional(resultType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                const auto valueType = ((expression->type_ == std::string("Success")) ? result->valueType : result->errorType);
                const auto propertyName = ((expression->type_ == std::string("Success")) ? std::string("value") : std::string("error"));
                const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->args, propertyName);
                const auto payloadType = ::app_src_emitter_types_::emitResultPayloadType(valueType, context->modulePath);
                if (doof::is_null(property) || doof::is_null(property->value)) {
                    return ((((std::string("doof::") + expression->type_) + std::string("<")) + payloadType) + std::string(">{ }"));
                }
                const auto value = ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::unwrap_optional(property->value), context, doof::optional_value(valueType));
                return ((((((std::string("doof::") + expression->type_) + std::string("<")) + payloadType) + std::string(">{ ")) + value) + std::string(" }"));
        }
        else {
        }
        }
        doof::panic((expression->type_ + std::string(" does not construct a Result")));
    }
    const auto class_ = expression->resolvedClass;
    if (doof::is_null(class_)) {
        doof::panic((std::string("Cannot construct unresolved class ") + expression->type_));
    }
    const auto constructedType = expression->resolvedConstructedType;
    if (doof::is_null(constructedType)) {
        doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has no resolved constructed type")));
    }
    std::shared_ptr<::app_src_semantic_::ClassType> owner = nullptr;
    {
        auto _case_subject = doof::unwrap_optional(constructedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            (owner = class_);
    }
    else {
            doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has a non-class constructed type")));
    }
    }
    const auto constructorMethod = declaredConstructor(doof::unwrap_optional(class_));
    const auto insideConstructor = insideDeclaredConstructor(doof::unwrap_optional(class_), context);
    if (((!doof::is_null(constructorMethod)) && !insideConstructor) && doof::is_null(expression->resolvedConstructor)) {
        doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has no resolved constructor")));
    }
    if (!doof::is_null(expression->resolvedConstructor)) {
        if (doof::is_null(constructorMethod)) {
            doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has unexpected constructor metadata")));
        }
        return emitNamedConstructorFactoryCall(doof::unwrap_optional(owner), doof::unwrap_optional(expression->resolvedConstructor), expression, context);
    }
    auto cppName = expression->type_;
    auto native = class_->native_;
    auto structValue = false;
    if (native) {
        (cppName = (std::string("::") + ((class_->nativeCppName == std::string("")) ? class_->name : class_->nativeCppName)));
    }
    if (!doof::is_null(expression->resolvedType)) {
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                (structValue = (resolved->symbol->kind == std::string("struct")));
                if (resolved->symbol->native_) {
                    (cppName = (std::string("::") + ((resolved->symbol->nativeCppName == std::string("")) ? resolved->symbol->name : resolved->symbol->nativeCppName)));
                } else if (((context->modulePath != std::string("")) && (resolved->symbol->module != std::string(""))) && (resolved->symbol->module != context->modulePath)) {
                    (cppName = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(resolved->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(resolved->symbol)));
                }
                const auto concrete = concreteClassName(resolved, context);
                if (concrete != std::string("")) {
                    (cppName = concrete);
                }
        }
        else {
        }
        }
    }
    auto values = std::string("");
    auto first = true;
    const auto& _iterable_9 = class_->fields;
    for (const auto& field : *_iterable_9) {
        if (field->static_ || field->const_) {
            continue;
        }
        const auto& _iterable_10 = field->names;
        for (const auto& name : *_iterable_10) {
            if (!first) {
                (values = (values + std::string(", ")));
            }
            (first = false);
            const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->args, name);
            auto value = std::string("");
            if (!doof::is_null(property)) {
                if (doof::is_null(property->value)) {
                    (value = ::app_src_emitter_expr_::cppIdentifier(name));
                } else {
                    {
                        auto _case_subject = doof::unwrap_optional(property->value);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
                            {
                                auto _case_subject = doof::unwrap_optional(field->resolvedType);
                                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                                    (value = ((((std::string("std::shared_ptr<") + class_->name) + std::string(">(this, [](")) + class_->name) + std::string("*) {})")));
                            }
                            else {
                                    (value = ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::unwrap_optional(property->value), context, field->resolvedType));
                            }
                            }
                    }
                    else {
                            (value = ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::unwrap_optional(property->value), context, field->resolvedType));
                    }
                    }
                }
            } else if (!doof::is_null(field->defaultValue)) {
                (value = emitDefaultExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType, expression->span));
            } else {
                doof::panic(((((std::string("Construction of '") + expression->type_) + std::string("' is missing required field '")) + name) + std::string("'")));
            }
            if (((!doof::is_null(property)) && doof::is_null(property->value)) && ::app_src_emitter_expr_utils_::needsNullableVariantPromotion(property->resolvedType, field->resolvedType)) {
                (value = ::app_src_emitter_expr_utils_::emitNullableVariantPromotion(value, property->resolvedType, field->resolvedType, context->modulePath));
            } else if (((!doof::is_null(property)) && doof::is_null(property->value)) && ::app_src_emitter_expr_utils_::needsVariantPromotion(property->resolvedType, field->resolvedType)) {
                (value = ((((std::string("doof::variant_promote<") + ::app_src_emitter_types_::emitContextType(doof::unwrap_optional(field->resolvedType), context)) + std::string(">(")) + value) + std::string(")")));
            }
            (values = (values + value));
        }
    }
    if (native) {
        return ((((std::string("std::make_shared<") + cppName) + std::string(">(")) + values) + std::string(")"));
    }
    if (structValue) {
        return (((cppName + std::string("{")) + values) + std::string("}"));
    }
    return ((((std::string("std::make_shared<") + cppName) + std::string(">(")) + values) + std::string(")"));
}
std::string emitConstructorFactoryCall(std::shared_ptr<::app_src_semantic_::ClassType> owner, std::shared_ptr<::app_src_ast_::FunctionDeclaration> constructorMethod, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>> args, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, ::app_src_ast_::SourceSpan callSiteSpan) {
    auto cppName = (owner->symbol->native_ ? (std::string("::") + ((owner->symbol->nativeCppName == std::string("")) ? owner->symbol->name : owner->symbol->nativeCppName)) : (((owner->symbol->module != std::string("")) && (owner->symbol->module != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(owner->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol)) : ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol)));
    const auto concrete = concreteClassName(owner, context);
    if (concrete != std::string("")) {
        (cppName = concrete);
    }
    auto result = (cppName + std::string("::constructor("));
    for (int32_t i = 0; i < static_cast<int32_t>((args)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedType = std::monostate{};
        if (i < static_cast<int32_t>((constructorMethod->params)->size())) {
            (expectedType = (*constructorMethod->params)[i]->resolvedType);
        }
        (result = (result + ::app_src_emitter_expr_::emitExpression((*args)[i]->value, context, expectedType)));
    }
    for (int32_t i = static_cast<int32_t>((args)->size()); i < static_cast<int32_t>((constructorMethod->params)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        if (doof::is_null((*constructorMethod->params)[i]->defaultValue)) {
            doof::panic((((std::string("Constructor ") + owner->name) + std::string(" is missing argument ")) + (*constructorMethod->params)[i]->name));
        }
        (result = (result + emitDefaultExpression(doof::unwrap_optional((*constructorMethod->params)[i]->defaultValue), context, (*constructorMethod->params)[i]->resolvedType, callSiteSpan)));
    }
    return (result + std::string(")"));
}
std::string emitNamedConstructorFactoryCall(std::shared_ptr<::app_src_semantic_::ClassType> owner, std::shared_ptr<::app_src_ast_::FunctionDeclaration> constructorMethod, std::shared_ptr<::app_src_ast_::ConstructExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto cppName = (owner->symbol->native_ ? (std::string("::") + ((owner->symbol->nativeCppName == std::string("")) ? owner->symbol->name : owner->symbol->nativeCppName)) : (((owner->symbol->module != std::string("")) && (owner->symbol->module != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(owner->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol)) : ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol)));
    const auto concrete = concreteClassName(owner, context);
    if (concrete != std::string("")) {
        (cppName = concrete);
    }
    auto result = (cppName + std::string("::constructor("));
    for (int32_t i = 0; i < static_cast<int32_t>((constructorMethod->params)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        const auto parameter = (*constructorMethod->params)[i];
        const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->args, parameter->name);
        if (!doof::is_null(property)) {
            if (doof::is_null(property->value)) {
                (result = (result + ::app_src_emitter_expr_::cppIdentifier(property->name)));
            } else {
                (result = (result + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->value), context, parameter->resolvedType)));
            }
        } else if (!doof::is_null(parameter->defaultValue)) {
            (result = (result + emitDefaultExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType, expression->span)));
        } else {
            doof::panic((((std::string("Constructor ") + owner->name) + std::string(" is missing argument ")) + parameter->name));
        }
    }
    return (result + std::string(")"));
}
std::string emitDefaultExpression(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected, ::app_src_ast_::SourceSpan callSiteSpan) {
    const auto previous = context->sourceLocationSpanOverride;
    (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(callSiteSpan));
    const auto result = ::app_src_emitter_expr_::emitExpression(expression, context, expected);
    (context->sourceLocationSpanOverride = previous);
    return result;
}
std::string concreteFunctionName(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string key) {
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteFunctionKeys)->size()); ++i) {
        if ((*context->concreteFunctionKeys)[i] == key) {
            return (*context->concreteFunctionNames)[i];
        }
    }
    return std::string("");
}
std::string concreteMethodNameFor(std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::string key) {
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteMethodKeys)->size()); ++i) {
        if ((*context->concreteMethodKeys)[i] == key) {
            return (*context->concreteMethodNames)[i];
        }
    }
    return std::string("");
}
std::string concreteClassName(std::shared_ptr<::app_src_semantic_::ClassType> class_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    const auto& _iterable_11 = class_->typeArgs;
    for (const auto& argument : *_iterable_11) {
        typeArgs->push_back(::app_src_emitter_types_::specializeEmitType(argument, context));
    }
    if (static_cast<int32_t>((typeArgs)->size()) == 0) {
        return std::string("");
    }
    const auto boundaryKey = ((class_->symbol->module + std::string("::")) + class_->name);
    const auto& _iterable_12 = context->nativeTemplateClassKeys;
    for (const auto& existing : *_iterable_12) {
        if (existing == boundaryKey) {
            auto name = ::app_src_emitter_expr_utils_::emittedSymbolName(class_->symbol);
            if ((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) {
                (name = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(class_->symbol->module)) + std::string("::")) + name));
            }
            (name = (name + std::string("<")));
            for (int32_t i = 0; i < static_cast<int32_t>((typeArgs)->size()); ++i) {
                if (i > 0) {
                    (name = (name + std::string(", ")));
                }
                (name = (name + ::app_src_emitter_types_::emitContextType((*typeArgs)[i], context)));
            }
            return (name + std::string(">"));
        }
    }
    const auto key = ::app_src_emitter_monomorphize_::classInstantiationKey(class_->symbol->module, class_->name, typeArgs);
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteClassKeys)->size()); ++i) {
        if ((*context->concreteClassKeys)[i] == key) {
            const auto name = (*context->concreteClassNames)[i];
            if ((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) {
                return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(class_->symbol->module)) + std::string("::")) + name);
            }
            return name;
        }
    }
    return std::string("");
}
}
