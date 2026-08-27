#include "src_emitter_expr_calls.hpp"

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
#line 14 "/src/emitter-expr-calls.do"
std::string emitCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 15 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 17 "/src/emitter-expr-calls.do"
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 18 "/src/emitter-expr-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
#line 20 "/src/emitter-expr-calls.do"
                        if (member->optional || member->force) {
#line 20 "/src/emitter-expr-calls.do"
                            return emitWeakMemberCall(expression, member, context);
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
#line 28 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 30 "/src/emitter-expr-calls.do"
            if (isBuiltinIdentifier(identifier, std::string("catchPanic")) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
#line 31 "/src/emitter-expr-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(expression->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 33 "/src/emitter-expr-calls.do"
                        const auto callback = ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 33)->value, context, std::monostate{});
#line 34 "/src/emitter-expr-calls.do"
                        const auto successType = ::app_src_emitter_types_::emitResultPayloadType(result->valueType, context->modulePath);
#line 35 "/src/emitter-expr-calls.do"
                        if (std::visit([](auto&& _obj) { return _obj->kind; }, result->valueType) == std::string("none")) {
#line 36 "/src/emitter-expr-calls.do"
                            return ((std::string("[&]() -> doof::Result<void, std::string> { try { ") + callback) + std::string(".call(); return doof::Success<void>{}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }()"));
                        }
#line 38 "/src/emitter-expr-calls.do"
                        return ((((((std::string("[&]() -> doof::Result<") + successType) + std::string(", std::string> { try { return doof::Success<")) + successType) + std::string(">{")) + callback) + std::string(".call()}; } catch (const doof::Panic& _panic) { return doof::Failure<std::string>{_panic.message()}; } }()"));
                }
                else {
#line 40 "/src/emitter-expr-calls.do"
                        doof::panic(std::string("catchPanic has no Result type"));
                }
                }
                doof::unreachable();
            }
    }
    else {
    }
    }
#line 46 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 48 "/src/emitter-expr-calls.do"
            if (((identifier->name == std::string("Success")) || (identifier->name == std::string("Failure"))) && isBuiltinIdentifier(identifier, identifier->name)) {
#line 49 "/src/emitter-expr-calls.do"
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resultType = std::monostate{};
#line 50 "/src/emitter-expr-calls.do"
                if (!doof::is_null(expected)) {
#line 50 "/src/emitter-expr-calls.do"
                    (resultType = doof::optional_value(doof::unwrap_optional(expected)));
                } else if (!doof::is_null(expression->resolvedType)) {
#line 51 "/src/emitter-expr-calls.do"
                    (resultType = doof::optional_value(doof::unwrap_optional(expression->resolvedType)));
                }
#line 52 "/src/emitter-expr-calls.do"
                if (doof::is_null(resultType)) {
#line 52 "/src/emitter-expr-calls.do"
                    doof::panic((identifier->name + std::string(" has no expected Result type")));
                }
#line 53 "/src/emitter-expr-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(resultType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 55 "/src/emitter-expr-calls.do"
                        if (static_cast<int32_t>((expression->args)->size()) == 0) {
#line 55 "/src/emitter-expr-calls.do"
                            return ((((std::string("doof::") + identifier->name) + std::string("<")) + ::app_src_emitter_types_::emitResultPayloadType(((identifier->name == std::string("Success")) ? result->valueType : result->errorType), context->modulePath)) + std::string(">{}"));
                        }
#line 56 "/src/emitter-expr-calls.do"
                        const auto valueType = ((identifier->name == std::string("Success")) ? result->valueType : result->errorType);
#line 57 "/src/emitter-expr-calls.do"
                        const auto value = ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 57)->value, context, doof::optional_value(valueType));
#line 58 "/src/emitter-expr-calls.do"
                        const auto payloadType = ::app_src_emitter_types_::emitResultPayloadType(valueType, context->modulePath);
#line 59 "/src/emitter-expr-calls.do"
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
#line 67 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 69 "/src/emitter-expr-calls.do"
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 70 "/src/emitter-expr-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                        const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 71 "/src/emitter-expr-calls.do"
                        return ::app_src_emitter_expr_actor_::emitSyncActorCall(expression, member, actor, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& resultType = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 73 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("isSuccess")) {
#line 73 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::is_success(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
                        }
#line 74 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("isFailure")) {
#line 74 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::is_failure(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
                        }
#line 75 "/src/emitter-expr-calls.do"
                        if ((member->property == std::string("unwrapOr")) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
#line 76 "/src/emitter-expr-calls.do"
                            const auto temporaryName = (std::string("_result_unwrap_") + doof::to_string(context->tryCounter));
#line 77 "/src/emitter-expr-calls.do"
                            (context->tryCounter += 1);
#line 78 "/src/emitter-expr-calls.do"
                            const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 79 "/src/emitter-expr-calls.do"
                            const auto fallback = ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 79)->value, context, doof::optional_value(resultType->valueType));
#line 80 "/src/emitter-expr-calls.do"
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
#line 89 "/src/emitter-expr-calls.do"
    auto nativeConstructorCall = false;
#line 90 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
#line 91 "/src/emitter-expr-calls.do"
            (nativeConstructorCall = true);
    }
    else {
    }
    }
#line 94 "/src/emitter-expr-calls.do"
    if ((nativeConstructorCall && (!doof::is_null(expression->resolvedConstructor))) && (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee)))) {
#line 95 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& owner = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 97 "/src/emitter-expr-calls.do"
                return emitConstructorFactoryCall(owner, doof::unwrap_optional(expression->resolvedConstructor), expression->args, context, expression->span);
        }
        else {
        }
        }
    }
#line 102 "/src/emitter-expr-calls.do"
    if ((nativeConstructorCall && isClassCallee(expression->callee)) && (!doof::is_null(expression->resolvedType))) {
#line 103 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 105 "/src/emitter-expr-calls.do"
                if (class_->symbol->native_) {
#line 106 "/src/emitter-expr-calls.do"
                    const auto nativeName = (std::string("::") + ((class_->symbol->nativeCppName == std::string("")) ? class_->symbol->name : class_->symbol->nativeCppName));
#line 107 "/src/emitter-expr-calls.do"
                    if (doof::is_null(expression->resolvedConstructor)) {
#line 107 "/src/emitter-expr-calls.do"
                        return ((std::string("std::make_shared<") + nativeName) + std::string(">()"));
                    }
#line 108 "/src/emitter-expr-calls.do"
                    auto result = (nativeName + std::string("::constructor("));
#line 109 "/src/emitter-expr-calls.do"
                    const auto constructorMethod = expression->resolvedConstructor;
#line 110 "/src/emitter-expr-calls.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 111 "/src/emitter-expr-calls.do"
                        if (i > 0) {
#line 111 "/src/emitter-expr-calls.do"
                            (result = (result + std::string(", ")));
                        }
#line 112 "/src/emitter-expr-calls.do"
                        std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expectedArgument = std::monostate{};
#line 113 "/src/emitter-expr-calls.do"
                        if ((!doof::is_null(constructorMethod)) && (i < static_cast<int32_t>((constructorMethod->params)->size()))) {
#line 113 "/src/emitter-expr-calls.do"
                            (expectedArgument = doof::array_at(constructorMethod->params, i, "src/emitter-expr-calls", 113)->resolvedType);
                        }
#line 114 "/src/emitter-expr-calls.do"
                        auto argumentText = ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-calls", 114)->value, context, expectedArgument);
#line 115 "/src/emitter-expr-calls.do"
                        (result = (result + argumentText));
                    }
#line 117 "/src/emitter-expr-calls.do"
                    if (!doof::is_null(constructorMethod)) {
#line 118 "/src/emitter-expr-calls.do"
                        for (int32_t i = static_cast<int32_t>((expression->args)->size()); i < static_cast<int32_t>((constructorMethod->params)->size()); ++i) {
#line 119 "/src/emitter-expr-calls.do"
                            if (result != (nativeName + std::string("::constructor("))) {
#line 119 "/src/emitter-expr-calls.do"
                                (result = (result + std::string(", ")));
                            }
#line 120 "/src/emitter-expr-calls.do"
                            if (doof::is_null(doof::array_at(constructorMethod->params, i, "src/emitter-expr-calls", 120)->defaultValue)) {
#line 120 "/src/emitter-expr-calls.do"
                                doof::panic(((std::string("Native constructor ") + class_->name) + std::string(" is missing a default argument")));
                            }
#line 121 "/src/emitter-expr-calls.do"
                            (result = (result + emitDefaultExpression(doof::unwrap_optional(doof::array_at(constructorMethod->params, i, "src/emitter-expr-calls", 121)->defaultValue), context, doof::array_at(constructorMethod->params, i, "src/emitter-expr-calls", 121)->resolvedType, expression->span)));
                        }
                    }
#line 124 "/src/emitter-expr-calls.do"
                    return (result + std::string(")"));
                }
#line 126 "/src/emitter-expr-calls.do"
                if ((!doof::is_null(expression->resolvedConstructor)) || isClassCallee(expression->callee)) {
#line 127 "/src/emitter-expr-calls.do"
                    auto cppName = (((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(class_->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(class_->symbol)) : ::app_src_emitter_expr_utils_::emittedSymbolName(class_->symbol));
#line 128 "/src/emitter-expr-calls.do"
                    const auto concrete = concreteClassName(class_, context);
#line 129 "/src/emitter-expr-calls.do"
                    if (concrete != std::string("")) {
#line 129 "/src/emitter-expr-calls.do"
                        (cppName = concrete);
                    }
#line 130 "/src/emitter-expr-calls.do"
                    auto values = std::string("");
#line 131 "/src/emitter-expr-calls.do"
                    auto namedConstruction = false;
#line 132 "/src/emitter-expr-calls.do"
                    const auto& _iterable_4 = expression->args;
                    for (const auto& argument : *_iterable_4) {
#line 132 "/src/emitter-expr-calls.do"
                        if (!doof::is_null(argument->name)) {
#line 132 "/src/emitter-expr-calls.do"
                            (namedConstruction = true);
                        }
                    }
#line 133 "/src/emitter-expr-calls.do"
                    if (!doof::is_null(expression->resolvedClass)) {
#line 134 "/src/emitter-expr-calls.do"
                        auto positionalIndex = 0;
#line 135 "/src/emitter-expr-calls.do"
                        const auto& _iterable_6 = expression->resolvedClass->fields;
                        for (const auto& field : *_iterable_6) {
#line 136 "/src/emitter-expr-calls.do"
                            if (field->static_ || field->const_) {
#line 136 "/src/emitter-expr-calls.do"
                                continue;
                            }
#line 137 "/src/emitter-expr-calls.do"
                            const auto& _iterable_8 = field->names;
                            for (const auto& name : *_iterable_8) {
#line 138 "/src/emitter-expr-calls.do"
                                if (values != std::string("")) {
#line 138 "/src/emitter-expr-calls.do"
                                    (values = (values + std::string(", ")));
                                }
#line 139 "/src/emitter-expr-calls.do"
                                const auto argument = [&]() -> std::shared_ptr<::app_src_ast_::CallArgument> { if (namedConstruction) { return callArgumentNamed(expression, name); } return [&]() -> std::shared_ptr<::app_src_ast_::CallArgument> { if ((positionalIndex < static_cast<int32_t>((expression->args)->size()))) { return doof::array_at(expression->args, positionalIndex, "src/emitter-expr-calls", 139); } return nullptr; }(); }();
#line 140 "/src/emitter-expr-calls.do"
                                if (!doof::is_null(argument)) {
#line 141 "/src/emitter-expr-calls.do"
                                    (values = (values + ::app_src_emitter_expr_utils_::emitExpectedExpression(argument->value, context, field->resolvedType)));
#line 142 "/src/emitter-expr-calls.do"
                                    if (!namedConstruction) {
#line 142 "/src/emitter-expr-calls.do"
                                        (positionalIndex = (positionalIndex + 1));
                                    }
                                } else if (!doof::is_null(field->defaultValue)) {
#line 143 "/src/emitter-expr-calls.do"
                                    (values = (values + emitDefaultExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType, expression->span)));
                                } else {
#line 144 "/src/emitter-expr-calls.do"
                                    doof::panic(((((std::string("Construction of '") + class_->name) + std::string("' is missing required field '")) + name) + std::string("'")));
                                }
                            }
                        }
                    } else {
#line 148 "/src/emitter-expr-calls.do"
                        for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 149 "/src/emitter-expr-calls.do"
                            if (i > 0) {
#line 149 "/src/emitter-expr-calls.do"
                                (values = (values + std::string(", ")));
                            }
#line 150 "/src/emitter-expr-calls.do"
                            (values = (values + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-calls", 150)->value, context, std::monostate{})));
                        }
                    }
#line 153 "/src/emitter-expr-calls.do"
                    return ((class_->symbol->kind == std::string("struct")) ? (((cppName + std::string("{")) + values) + std::string("}")) : ((((std::string("std::make_shared<") + cppName) + std::string(">(")) + values) + std::string(")")));
                }
        }
        else {
        }
        }
    }
#line 159 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 161 "/src/emitter-expr-calls.do"
            const auto arrayObjectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
#line 162 "/src/emitter-expr-calls.do"
            auto nominalReceiver = false;
#line 163 "/src/emitter-expr-calls.do"
            if (!doof::is_null(arrayObjectType)) {
#line 164 "/src/emitter-expr-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(arrayObjectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 165 "/src/emitter-expr-calls.do"
                        (nominalReceiver = true);
                }
                else {
                }
                }
            }
#line 169 "/src/emitter-expr-calls.do"
            if (member->property == std::string("length")) {
#line 170 "/src/emitter-expr-calls.do"
                if (!doof::is_null(arrayObjectType)) {
#line 171 "/src/emitter-expr-calls.do"
                    {
                        auto _case_subject = doof::unwrap_optional(arrayObjectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 172 "/src/emitter-expr-calls.do"
                            return ((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + ((class_->symbol->kind == std::string("struct")) ? std::string(".") : std::string("->"))) + std::string("length()"));
                    }
                    else {
                    }
                    }
                }
            }
#line 177 "/src/emitter-expr-calls.do"
            if (!doof::is_null(arrayObjectType)) {
#line 178 "/src/emitter-expr-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(arrayObjectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 180 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("fromJsonValue")) {
#line 180 "/src/emitter-expr-calls.do"
                            return emitInterfaceJsonCall(member, expression, context);
                        }
#line 181 "/src/emitter-expr-calls.do"
                        return emitVariantMemberCall(member, expression, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
#line 183 "/src/emitter-expr-calls.do"
                        return emitInterfaceCall(member, expression, context);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                        const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 184 "/src/emitter-expr-calls.do"
                        if (::app_src_emitter_types_::usesVariantRepresentation(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(union_))) {
#line 184 "/src/emitter-expr-calls.do"
                            return emitVariantMemberCall(member, expression, context);
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 186 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("takeFirstCompleted")) {
#line 186 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::promise_take_first_completed(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
                        }
#line 187 "/src/emitter-expr-calls.do"
                        if ((member->property == std::string("buildReadonly")) || (member->property == std::string("drainToReadonly"))) {
#line 187 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::array_drainToReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 188 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("cloneReadonly")) {
#line 188 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::array_cloneReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 189 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("cloneMutable")) {
#line 189 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::array_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 190 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("contains")) {
#line 190 "/src/emitter-expr-calls.do"
                            return ((((std::string("doof::array_contains(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 190)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 191 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("indexOf")) {
#line 191 "/src/emitter-expr-calls.do"
                            return ((((std::string("doof::array_indexOf(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 191)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 192 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("some")) {
#line 192 "/src/emitter-expr-calls.do"
                            return ((((std::string("doof::array_some(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 192)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 193 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("every")) {
#line 193 "/src/emitter-expr-calls.do"
                            return ((((std::string("doof::array_every(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 193)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 194 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("filter")) {
#line 194 "/src/emitter-expr-calls.do"
                            return ((((std::string("doof::array_filter(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 194)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 195 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("map")) {
#line 195 "/src/emitter-expr-calls.do"
                            return ((((std::string("doof::array_map(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 195)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                        const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 198 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("has")) {
#line 199 "/src/emitter-expr-calls.do"
                            (context->tryCounter = (context->tryCounter + 1));
#line 200 "/src/emitter-expr-calls.do"
                            const auto temporary = (std::string("_map_has_") + doof::to_string(context->tryCounter));
#line 201 "/src/emitter-expr-calls.do"
                            return ((((((((((std::string("[&]() -> bool { auto ") + temporary) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string("; return ")) + temporary) + std::string("->find(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 201)->value, context, std::monostate{})) + std::string(") != ")) + temporary) + std::string("->end(); }()"));
                        }
#line 203 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("set")) {
#line 203 "/src/emitter-expr-calls.do"
                            return ((((((std::string("doof::map_set(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 203)->value, context, doof::optional_value(map->keyType))) + std::string(", ")) + ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::array_at(expression->args, 1, "src/emitter-expr-calls", 203)->value, context, doof::optional_value(map->valueType))) + std::string(", \"\", 0)"));
                        }
#line 204 "/src/emitter-expr-calls.do"
                        if ((member->property == std::string("get")) && (static_cast<int32_t>((expression->args)->size()) > 0)) {
#line 204 "/src/emitter-expr-calls.do"
                            return ((((std::string("doof::map_get(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 204)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 205 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("keys")) {
#line 205 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::map_keys(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 206 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("values")) {
#line 206 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::map_values(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 207 "/src/emitter-expr-calls.do"
                        if ((member->property == std::string("buildReadonly")) || (member->property == std::string("drainToReadonly"))) {
#line 207 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::map_drainToReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 208 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("cloneReadonly")) {
#line 208 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::map_cloneReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 209 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("cloneMutable")) {
#line 209 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::map_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
#line 212 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("has")) {
#line 212 "/src/emitter-expr-calls.do"
                            return ((((std::string("(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string("->count(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 212)->value, context, std::monostate{})) + std::string(") > 0)"));
                        }
#line 213 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("add")) {
#line 213 "/src/emitter-expr-calls.do"
                            return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("->insert(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 213)->value, context, std::monostate{})) + std::string(")"));
                        }
#line 214 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("delete")) {
#line 214 "/src/emitter-expr-calls.do"
                            return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("->erase(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 214)->value, context, std::monostate{})) + std::string(")"));
                        }
#line 215 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("values")) {
#line 215 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::set_values(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 216 "/src/emitter-expr-calls.do"
                        if ((member->property == std::string("buildReadonly")) || (member->property == std::string("drainToReadonly"))) {
#line 216 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::set_drainToReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 217 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("cloneReadonly")) {
#line 217 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::set_cloneReadonly(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
#line 218 "/src/emitter-expr-calls.do"
                        if (member->property == std::string("cloneMutable")) {
#line 218 "/src/emitter-expr-calls.do"
                            return ((std::string("doof::set_cloneMutable(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
                        const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 221 "/src/emitter-expr-calls.do"
                        if ((member->property == std::string("fromName")) || (member->property == std::string("fromValue"))) {
#line 222 "/src/emitter-expr-calls.do"
                            const auto args = ((static_cast<int32_t>((expression->args)->size()) == 0) ? std::string("") : ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 222)->value, context, std::monostate{}));
#line 223 "/src/emitter-expr-calls.do"
                            return (((((::app_src_emitter_types_::emitContextType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), context) + std::string("_")) + member->property) + std::string("(")) + args) + std::string(")"));
                        }
                }
                else {
                }
                }
            }
#line 229 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("startsWith"))) {
#line 229 "/src/emitter-expr-calls.do"
                return emitBuiltinCall(std::string("doof::string_startsWith"), member->object, expression, context);
            }
#line 230 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("endsWith"))) {
#line 230 "/src/emitter-expr-calls.do"
                return emitBuiltinCall(std::string("doof::string_endsWith"), member->object, expression, context);
            }
#line 231 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("substring"))) {
#line 231 "/src/emitter-expr-calls.do"
                return emitBuiltinCall(std::string("doof::string_substring"), member->object, expression, context);
            }
#line 232 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("replaceAll"))) {
#line 232 "/src/emitter-expr-calls.do"
                return emitBuiltinCall(std::string("doof::string_replaceAll"), member->object, expression, context);
            }
#line 233 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("contains"))) {
#line 233 "/src/emitter-expr-calls.do"
                return emitBuiltinCall(std::string("doof::string_contains"), member->object, expression, context);
            }
#line 234 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("indexOf"))) {
#line 234 "/src/emitter-expr-calls.do"
                return emitBuiltinCall(std::string("doof::string_indexOf"), member->object, expression, context);
            }
#line 235 "/src/emitter-expr-calls.do"
            const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
#line 236 "/src/emitter-expr-calls.do"
            if (!doof::is_null(objectType)) {
#line 237 "/src/emitter-expr-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(objectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 239 "/src/emitter-expr-calls.do"
                        if ((member->property == std::string("slice")) && (static_cast<int32_t>((expression->args)->size()) == 2)) {
#line 240 "/src/emitter-expr-calls.do"
                            return ((((((std::string("doof::array_slice(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 240)->value, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 1, "src/emitter-expr-calls", 240)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
                        }
                }
                else {
                }
                }
            }
#line 246 "/src/emitter-expr-calls.do"
            if ((!nominalReceiver && (member->property == std::string("trim"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
#line 246 "/src/emitter-expr-calls.do"
                return ((std::string("doof::string_trim(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
#line 247 "/src/emitter-expr-calls.do"
            if ((!nominalReceiver && (member->property == std::string("trimStart"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
#line 247 "/src/emitter-expr-calls.do"
                return ((std::string("doof::string_trimStart(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
#line 248 "/src/emitter-expr-calls.do"
            if ((!nominalReceiver && (member->property == std::string("repeat"))) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
#line 248 "/src/emitter-expr-calls.do"
                return ((((std::string("doof::string_repeat(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 248)->value, context, std::monostate{})) + std::string(")"));
            }
#line 249 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("slice"))) {
#line 249 "/src/emitter-expr-calls.do"
                return ((((std::string("doof::string_slice(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 249)->value, context, std::monostate{})) + std::string(")"));
            }
#line 250 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("charAt"))) {
#line 250 "/src/emitter-expr-calls.do"
                return ((((std::string("doof::string_at(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 250)->value, context, std::monostate{})) + std::string(", \"\", 0)"));
            }
#line 251 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("padStart"))) {
#line 252 "/src/emitter-expr-calls.do"
                const auto fill = ((static_cast<int32_t>((expression->args)->size()) > 1) ? ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 1, "src/emitter-expr-calls", 252)->value, context, std::monostate{}) : std::string("U' '"));
#line 253 "/src/emitter-expr-calls.do"
                return ((((((std::string("doof::string_padStart(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 253)->value, context, std::monostate{})) + std::string(", ")) + fill) + std::string(")"));
            }
#line 255 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("padEnd"))) {
#line 256 "/src/emitter-expr-calls.do"
                const auto fill = ((static_cast<int32_t>((expression->args)->size()) > 1) ? ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 1, "src/emitter-expr-calls", 256)->value, context, std::monostate{}) : std::string("U' '"));
#line 257 "/src/emitter-expr-calls.do"
                return ((((((std::string("doof::string_padEnd(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 257)->value, context, std::monostate{})) + std::string(", ")) + fill) + std::string(")"));
            }
#line 259 "/src/emitter-expr-calls.do"
            if ((!nominalReceiver && (member->property == std::string("trimEnd"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
#line 259 "/src/emitter-expr-calls.do"
                return ((std::string("doof::string_trimEnd(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
#line 260 "/src/emitter-expr-calls.do"
            if ((!nominalReceiver && (member->property == std::string("trimEnd"))) && (static_cast<int32_t>((expression->args)->size()) == 1)) {
#line 260 "/src/emitter-expr-calls.do"
                return ((((std::string("doof::string_trimEnd(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 260)->value, context, std::monostate{})) + std::string(")"));
            }
#line 261 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("toLowerCase"))) {
#line 261 "/src/emitter-expr-calls.do"
                return ((std::string("doof::string_toLowerCase(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
#line 262 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("toUpperCase"))) {
#line 262 "/src/emitter-expr-calls.do"
                return ((std::string("doof::string_toUpperCase(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
#line 263 "/src/emitter-expr-calls.do"
            if (!nominalReceiver && (member->property == std::string("split"))) {
#line 263 "/src/emitter-expr-calls.do"
                return ((((std::string("doof::string_split(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, 0, "src/emitter-expr-calls", 263)->value, context, std::monostate{})) + std::string(")"));
            }
#line 264 "/src/emitter-expr-calls.do"
            if ((!nominalReceiver && (member->property == std::string("pop"))) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
#line 264 "/src/emitter-expr-calls.do"
                return ((std::string("doof::array_pop(") + ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{})) + std::string(")"));
            }
#line 265 "/src/emitter-expr-calls.do"
            if ((member->property == std::string("toJsonObject")) && (static_cast<int32_t>((expression->args)->size()) == 0)) {
#line 266 "/src/emitter-expr-calls.do"
                const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 267 "/src/emitter-expr-calls.do"
                const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
#line 268 "/src/emitter-expr-calls.do"
                if (!doof::is_null(objectType)) {
#line 269 "/src/emitter-expr-calls.do"
                    {
                        auto _case_subject = doof::unwrap_optional(objectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 270 "/src/emitter-expr-calls.do"
                            if (class_->symbol->kind == std::string("struct")) {
#line 270 "/src/emitter-expr-calls.do"
                                return (object + std::string(".toJsonObject()"));
                            }
                    }
                    else {
                    }
                    }
                }
#line 274 "/src/emitter-expr-calls.do"
                return (object + std::string("->toJsonObject()"));
            }
#line 276 "/src/emitter-expr-calls.do"
            if ((member->property == std::string("fromJsonValue")) && (!nominalReceiver || (!doof::is_null(member->resolvedStaticOwner)))) {
#line 277 "/src/emitter-expr-calls.do"
                const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 278 "/src/emitter-expr-calls.do"
                auto args = std::string("");
#line 279 "/src/emitter-expr-calls.do"
                for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 280 "/src/emitter-expr-calls.do"
                    if (i > 0) {
#line 280 "/src/emitter-expr-calls.do"
                        (args = (args + std::string(", ")));
                    }
#line 281 "/src/emitter-expr-calls.do"
                    (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-calls", 281)->value, context, std::monostate{})));
                }
#line 283 "/src/emitter-expr-calls.do"
                if (static_cast<int32_t>((expression->args)->size()) == 1) {
#line 283 "/src/emitter-expr-calls.do"
                    (args = (args + std::string(", false")));
                }
#line 284 "/src/emitter-expr-calls.do"
                const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
#line 285 "/src/emitter-expr-calls.do"
                if (!doof::is_null(objectType)) {
#line 286 "/src/emitter-expr-calls.do"
                    {
                        auto _case_subject = doof::unwrap_optional(objectType);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 287 "/src/emitter-expr-calls.do"
                            return (((object + std::string("_fromJsonValue(")) + args) + std::string(")"));
                    }
                    else {
                    }
                    }
                }
#line 291 "/src/emitter-expr-calls.do"
                return (((object + std::string("::fromJsonValue(")) + args) + std::string(")"));
            }
    }
    else {
    }
    }
#line 296 "/src/emitter-expr-calls.do"
    auto callee = ::app_src_emitter_expr_::emitExpression(expression->callee, context, std::monostate{});
#line 297 "/src/emitter-expr-calls.do"
    if (std::visit([](auto&& _obj) { return _obj->kind; }, expression->callee) == std::string("identifier")) {
#line 298 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = expression->callee;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 300 "/src/emitter-expr-calls.do"
                if (((!doof::is_null(identifier->resolvedBinding)) && (identifier->resolvedBinding->kind == std::string("builtin"))) && isBuiltinName(identifier->name)) {
#line 300 "/src/emitter-expr-calls.do"
                    (callee = builtinName(identifier->name));
                }
        }
        else {
        }
        }
    }
#line 305 "/src/emitter-expr-calls.do"
    std::shared_ptr<::app_src_semantic_::FunctionType> functionType = nullptr;
#line 306 "/src/emitter-expr-calls.do"
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee))) {
#line 307 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression->callee));
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 308 "/src/emitter-expr-calls.do"
                (functionType = resolved);
        }
        else {
        }
        }
    }
#line 312 "/src/emitter-expr-calls.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> concreteGenericArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 313 "/src/emitter-expr-calls.do"
    const auto& _iterable_12 = expression->resolvedGenericTypeArgs;
    for (const auto& argument : *_iterable_12) {
#line 313 "/src/emitter-expr-calls.do"
        concreteGenericArgs->push_back(::app_src_emitter_types_::specializeEmitType(argument, context));
    }
#line 314 "/src/emitter-expr-calls.do"
    if ((!doof::is_null(functionType)) && (static_cast<int32_t>((concreteGenericArgs)->size()) > 0)) {
#line 315 "/src/emitter-expr-calls.do"
        const auto substituted = ::app_src_checker_types_::substituteTypeParams(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(doof::unwrap_optional(functionType)), functionType->typeParams, concreteGenericArgs);
#line 316 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = substituted;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& specialized = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 317 "/src/emitter-expr-calls.do"
                (functionType = specialized);
        }
        else {
        }
        }
    }
#line 321 "/src/emitter-expr-calls.do"
    const auto functionDeclaration = expression->resolvedFunction;
#line 322 "/src/emitter-expr-calls.do"
    auto usesConcreteInstantiation = false;
#line 323 "/src/emitter-expr-calls.do"
    if ((!doof::is_null(functionDeclaration)) && (static_cast<int32_t>((functionDeclaration->typeParams)->size()) > 0)) {
#line 324 "/src/emitter-expr-calls.do"
        auto targetModule = context->modulePath;
#line 325 "/src/emitter-expr-calls.do"
        auto concreteMethodName = std::string("");
#line 326 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = expression->callee;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 328 "/src/emitter-expr-calls.do"
                if (!doof::is_null(identifier->resolvedBinding)) {
#line 329 "/src/emitter-expr-calls.do"
                    if (!doof::is_null(identifier->resolvedBinding->symbol)) {
#line 329 "/src/emitter-expr-calls.do"
                        (targetModule = identifier->resolvedBinding->symbol->module);
                    } else if (identifier->resolvedBinding->module != std::string("")) {
#line 330 "/src/emitter-expr-calls.do"
                        (targetModule = identifier->resolvedBinding->module);
                    }
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 334 "/src/emitter-expr-calls.do"
                if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 335 "/src/emitter-expr-calls.do"
                    {
                        auto _case_subject = ::app_src_emitter_types_::specializeEmitType(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)), context);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 337 "/src/emitter-expr-calls.do"
                            (targetModule = class_->symbol->module);
#line 338 "/src/emitter-expr-calls.do"
                            const auto ownerKey = ::app_src_emitter_monomorphize_::classInstantiationKey(class_->symbol->module, class_->name, class_->typeArgs);
#line 339 "/src/emitter-expr-calls.do"
                            const auto methodKey = ::app_src_emitter_monomorphize_::methodInstantiationKey(ownerKey, functionDeclaration->name, concreteGenericArgs);
#line 340 "/src/emitter-expr-calls.do"
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
#line 348 "/src/emitter-expr-calls.do"
        if (concreteMethodName != std::string("")) {
#line 349 "/src/emitter-expr-calls.do"
            (usesConcreteInstantiation = true);
#line 350 "/src/emitter-expr-calls.do"
            {
                auto _case_subject = expression->callee;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                    const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 351 "/src/emitter-expr-calls.do"
                    (callee = (doof::string_substring(callee, 0, (static_cast<int32_t>(callee.size()) - static_cast<int32_t>(member->property.size()))) + concreteMethodName));
            }
            else {
            }
            }
        } else {
#line 355 "/src/emitter-expr-calls.do"
            const auto key = ::app_src_emitter_monomorphize_::functionInstantiationKey(targetModule, functionDeclaration->name, concreteGenericArgs);
#line 356 "/src/emitter-expr-calls.do"
            const auto concreteName = concreteFunctionName(context, key);
#line 357 "/src/emitter-expr-calls.do"
            if (concreteName != std::string("")) {
#line 358 "/src/emitter-expr-calls.do"
                (usesConcreteInstantiation = true);
#line 359 "/src/emitter-expr-calls.do"
                (callee = (((targetModule != std::string("")) && (targetModule != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(targetModule)) + std::string("::")) + concreteName) : concreteName));
            }
        }
    }
#line 363 "/src/emitter-expr-calls.do"
    if ((((static_cast<int32_t>((concreteGenericArgs)->size()) > 0) && (!doof::is_null(functionDeclaration))) && (static_cast<int32_t>((functionDeclaration->typeParams)->size()) > 0)) && !usesConcreteInstantiation) {
#line 364 "/src/emitter-expr-calls.do"
        (callee = (callee + std::string("<")));
#line 365 "/src/emitter-expr-calls.do"
        for (int32_t i = 0; i < static_cast<int32_t>((concreteGenericArgs)->size()); ++i) {
#line 366 "/src/emitter-expr-calls.do"
            if (i > 0) {
#line 366 "/src/emitter-expr-calls.do"
                (callee = (callee + std::string(", ")));
            }
#line 367 "/src/emitter-expr-calls.do"
            (callee = (callee + ::app_src_emitter_types_::emitContextType(doof::array_at(concreteGenericArgs, i, "src/emitter-expr-calls", 367), context)));
        }
#line 369 "/src/emitter-expr-calls.do"
        (callee = (callee + std::string(">")));
    }
#line 371 "/src/emitter-expr-calls.do"
    auto invokesCallback = false;
#line 372 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = expression->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 374 "/src/emitter-expr-calls.do"
            (invokesCallback = ((!(((!doof::is_null(identifier->resolvedBinding)) && (identifier->resolvedBinding->kind == std::string("builtin"))) && isBuiltinName(identifier->name)) && (!doof::is_null(functionType))) && doof::is_null(functionDeclaration)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 376 "/src/emitter-expr-calls.do"
            (invokesCallback = (member->resolvedCallableField && (!doof::is_null(functionType))));
    }
    else {
#line 377 "/src/emitter-expr-calls.do"
            (invokesCallback = ((!doof::is_null(functionType)) && doof::is_null(functionDeclaration)));
    }
    }
#line 379 "/src/emitter-expr-calls.do"
    const auto callPrefix = (invokesCallback ? (callee + std::string(".call(")) : (callee + std::string("(")));
#line 380 "/src/emitter-expr-calls.do"
    auto result = callPrefix;
#line 381 "/src/emitter-expr-calls.do"
    auto named = false;
#line 382 "/src/emitter-expr-calls.do"
    const auto& _iterable_15 = expression->args;
    for (const auto& argument : *_iterable_15) {
#line 382 "/src/emitter-expr-calls.do"
        if (!doof::is_null(argument->name)) {
#line 382 "/src/emitter-expr-calls.do"
            (named = true);
        }
    }
#line 383 "/src/emitter-expr-calls.do"
    if (named && (!doof::is_null(functionDeclaration))) {
#line 384 "/src/emitter-expr-calls.do"
        for (int32_t i = 0; i < static_cast<int32_t>((functionDeclaration->params)->size()); ++i) {
#line 385 "/src/emitter-expr-calls.do"
            const auto parameter = doof::array_at(functionDeclaration->params, i, "src/emitter-expr-calls", 385);
#line 386 "/src/emitter-expr-calls.do"
            const auto argument = callArgumentNamed(expression, parameter->name);
#line 387 "/src/emitter-expr-calls.do"
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = parameter->resolvedType;
#line 388 "/src/emitter-expr-calls.do"
            if ((!doof::is_null(functionType)) && (i < static_cast<int32_t>((functionType->params)->size()))) {
#line 388 "/src/emitter-expr-calls.do"
                (expected = ::app_src_emitter_expr_utils_::optionalExpectedType(doof::array_at(functionType->params, i, "src/emitter-expr-calls", 388)->type_));
            }
#line 389 "/src/emitter-expr-calls.do"
            if ((!doof::is_null(argument)) || (!doof::is_null(parameter->defaultValue))) {
#line 390 "/src/emitter-expr-calls.do"
                if (result != callPrefix) {
#line 390 "/src/emitter-expr-calls.do"
                    (result = (result + std::string(", ")));
                }
#line 391 "/src/emitter-expr-calls.do"
                if (!doof::is_null(argument)) {
#line 391 "/src/emitter-expr-calls.do"
                    (result = (result + ::app_src_emitter_expr_utils_::emitExpectedExpression(argument->value, context, expected)));
                } else {
#line 392 "/src/emitter-expr-calls.do"
                    (result = (result + emitDefaultExpression(doof::unwrap_optional(parameter->defaultValue), context, expected, expression->span)));
                }
            }
        }
    } else if (named && (!doof::is_null(functionType))) {
#line 399 "/src/emitter-expr-calls.do"
        const auto& _iterable_18 = functionType->params;
        for (const auto& parameter : *_iterable_18) {
#line 400 "/src/emitter-expr-calls.do"
            const auto argument = callArgumentNamed(expression, parameter->name);
#line 401 "/src/emitter-expr-calls.do"
            if (!doof::is_null(argument)) {
#line 402 "/src/emitter-expr-calls.do"
                if (result != callPrefix) {
#line 402 "/src/emitter-expr-calls.do"
                    (result = (result + std::string(", ")));
                }
#line 403 "/src/emitter-expr-calls.do"
                (result = (result + ::app_src_emitter_expr_utils_::emitExpectedExpression(argument->value, context, ::app_src_emitter_expr_utils_::optionalExpectedType(parameter->type_))));
            }
        }
    } else {
#line 407 "/src/emitter-expr-calls.do"
        for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 408 "/src/emitter-expr-calls.do"
            if (i > 0) {
#line 408 "/src/emitter-expr-calls.do"
                (result = (result + std::string(", ")));
            }
#line 409 "/src/emitter-expr-calls.do"
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected = std::monostate{};
#line 410 "/src/emitter-expr-calls.do"
            if ((!doof::is_null(functionType)) && (i < static_cast<int32_t>((functionType->params)->size()))) {
#line 410 "/src/emitter-expr-calls.do"
                (expected = ::app_src_emitter_expr_utils_::optionalExpectedType(doof::array_at(functionType->params, i, "src/emitter-expr-calls", 410)->type_));
            }
#line 411 "/src/emitter-expr-calls.do"
            if ((doof::is_null(expected) && (!doof::is_null(functionDeclaration))) && (i < static_cast<int32_t>((functionDeclaration->params)->size()))) {
#line 411 "/src/emitter-expr-calls.do"
                (expected = doof::array_at(functionDeclaration->params, i, "src/emitter-expr-calls", 411)->resolvedType);
            }
#line 412 "/src/emitter-expr-calls.do"
            {
                auto _case_subject = expression->callee;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                    const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 413 "/src/emitter-expr-calls.do"
                    if (isBuiltinIdentifier(identifier, std::string("println")) || isBuiltinConversionIdentifier(identifier)) {
#line 413 "/src/emitter-expr-calls.do"
                        (expected = std::monostate{});
                    }
            }
            else {
            }
            }
#line 416 "/src/emitter-expr-calls.do"
            auto argument = ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::array_at(expression->args, i, "src/emitter-expr-calls", 416)->value, context, expected);
#line 417 "/src/emitter-expr-calls.do"
            (result = (result + argument));
        }
#line 419 "/src/emitter-expr-calls.do"
        if (!doof::is_null(functionDeclaration)) {
#line 420 "/src/emitter-expr-calls.do"
            for (int32_t i = static_cast<int32_t>((expression->args)->size()); i < static_cast<int32_t>((functionDeclaration->params)->size()); ++i) {
#line 421 "/src/emitter-expr-calls.do"
                const auto parameter = doof::array_at(functionDeclaration->params, i, "src/emitter-expr-calls", 421);
#line 422 "/src/emitter-expr-calls.do"
                if (!doof::is_null(parameter->defaultValue)) {
#line 423 "/src/emitter-expr-calls.do"
                    if (result != callPrefix) {
#line 423 "/src/emitter-expr-calls.do"
                        (result = (result + std::string(", ")));
                    }
#line 424 "/src/emitter-expr-calls.do"
                    (result = (result + emitDefaultExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType, expression->span)));
                }
            }
        }
    }
#line 429 "/src/emitter-expr-calls.do"
    return (result + std::string(")"));
}
#line 432 "/src/emitter-expr-calls.do"
std::string emitWeakMemberCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 433 "/src/emitter-expr-calls.do"
    (context->tryCounter = (context->tryCounter + 1));
#line 434 "/src/emitter-expr-calls.do"
    const auto storage = (std::string("_weak_storage_") + doof::to_string(context->tryCounter));
#line 435 "/src/emitter-expr-calls.do"
    const auto temporary = (std::string("_weak_value_") + doof::to_string(context->tryCounter));
#line 436 "/src/emitter-expr-calls.do"
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 437 "/src/emitter-expr-calls.do"
    auto nullable = false;
#line 438 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 439 "/src/emitter-expr-calls.do"
            (nullable = weakCallTargetAllowsNone(weak_->inner));
    }
    else {
    }
    }
#line 442 "/src/emitter-expr-calls.do"
    const auto weakValue = (nullable ? (storage + std::string(".value()")) : storage);
#line 443 "/src/emitter-expr-calls.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> originalReturn = std::monostate{};
#line 444 "/src/emitter-expr-calls.do"
    if (!doof::is_null(member->resolvedType)) {
#line 445 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = doof::unwrap_optional(member->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 445 "/src/emitter-expr-calls.do"
                (originalReturn = doof::optional_value(function_->returnType));
        }
        else {
        }
        }
    }
#line 447 "/src/emitter-expr-calls.do"
    const auto arguments = emitWeakCallArguments(expression, context);
#line 448 "/src/emitter-expr-calls.do"
    auto call = (((((temporary + std::string("->")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + arguments) + std::string(")"));
#line 449 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 451 "/src/emitter-expr-calls.do"
            if (weakCallTargetUsesVariant(weak_->inner)) {
#line 452 "/src/emitter-expr-calls.do"
                if (doof::is_null(originalReturn)) {
#line 452 "/src/emitter-expr-calls.do"
                    doof::panic(std::string("Weak union method call has no resolved return type"));
                }
#line 453 "/src/emitter-expr-calls.do"
                (call = ((((((((std::string("std::visit([&](auto&& _weak_item) -> ") + ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(originalReturn), context)) + std::string(" { return _weak_item->")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + arguments) + std::string("); }, ")) + temporary) + std::string(")")));
            }
    }
    else {
    }
    }
#line 458 "/src/emitter-expr-calls.do"
    if (member->force) {
#line 459 "/src/emitter-expr-calls.do"
        const auto resultType = doof::unwrap_optional(expression->resolvedType);
#line 460 "/src/emitter-expr-calls.do"
        const auto noneCheck = (nullable ? ((std::string("if (!") + storage) + std::string(".has_value()) doof::panic(\"Weak reference is none\"); ")) : std::string(""));
#line 461 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = resultType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 462 "/src/emitter-expr-calls.do"
                return ((((((((((((std::string("[&]() -> void { auto ") + storage) + std::string(" = ")) + object) + std::string("; ")) + noneCheck) + std::string("auto _weak_locked = doof::lock_weak(")) + weakValue) + std::string("); if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); auto ")) + temporary) + std::string(" = std::move(_weak_locked.value()); ")) + call) + std::string("; }()"));
        }
        else {
#line 463 "/src/emitter-expr-calls.do"
                return ((((((((((((((std::string("[&]() -> ") + ::app_src_emitter_types_::emitType(resultType, context->modulePath)) + std::string(" { auto ")) + storage) + std::string(" = ")) + object) + std::string("; ")) + noneCheck) + std::string("auto _weak_locked = doof::lock_weak(")) + weakValue) + std::string("); if (!_weak_locked.has_value()) doof::panic(\"Weak reference has expired\"); auto ")) + temporary) + std::string(" = std::move(_weak_locked.value()); return ")) + call) + std::string("; }()"));
        }
        }
        doof::unreachable();
    }
#line 466 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 468 "/src/emitter-expr-calls.do"
            const auto resultCpp = ::app_src_emitter_types_::emitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result), context->modulePath);
#line 469 "/src/emitter-expr-calls.do"
            const auto payloadCpp = ::app_src_emitter_types_::emitResultPayloadType(result->valueType, context->modulePath);
#line 470 "/src/emitter-expr-calls.do"
            const auto errorCpp = ::app_src_emitter_types_::emitResultPayloadType(result->errorType, context->modulePath);
#line 471 "/src/emitter-expr-calls.do"
            const auto failure = ((std::visit([](auto&& _obj) { return _obj->kind; }, result->errorType) == std::string("union")) ? (errorCpp + std::string("{::doof::WeakReferenceError{}}")) : std::string("::doof::WeakReferenceError{}"));
#line 472 "/src/emitter-expr-calls.do"
            const auto noneReturn = (nullable ? ((((((std::string("if (!") + storage) + std::string(".has_value()) return doof::Success<")) + payloadCpp) + std::string(">{")) + payloadCpp) + std::string("{}}; ")) : std::string(""));
#line 473 "/src/emitter-expr-calls.do"
            const auto prefix = ((((((((((((((((std::string("[&]() -> ") + resultCpp) + std::string(" { auto ")) + storage) + std::string(" = ")) + object) + std::string("; ")) + noneReturn) + std::string("auto _weak_locked = doof::lock_weak(")) + weakValue) + std::string("); if (!_weak_locked.has_value()) return doof::Failure<")) + errorCpp) + std::string(">{")) + failure) + std::string("}; auto ")) + temporary) + std::string(" = std::move(_weak_locked.value()); "));
#line 474 "/src/emitter-expr-calls.do"
            if (!doof::is_null(originalReturn)) {
#line 475 "/src/emitter-expr-calls.do"
                {
                    auto _case_subject = doof::unwrap_optional(originalReturn);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                        const auto& nested = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 477 "/src/emitter-expr-calls.do"
                        const auto nestedErrorCpp = ::app_src_emitter_types_::emitResultPayloadType(nested->errorType, context->modulePath);
#line 478 "/src/emitter-expr-calls.do"
                        const auto promotedError = ((std::visit([](auto&& _obj) { return _obj->kind; }, result->errorType) == std::string("union")) ? (errorCpp + std::string("{doof::failure_error(_weak_result)}")) : std::string("doof::failure_error(_weak_result)"));
#line 479 "/src/emitter-expr-calls.do"
                        if (std::visit([](auto&& _obj) { return _obj->kind; }, nested->valueType) == std::string("none")) {
#line 480 "/src/emitter-expr-calls.do"
                            return (((((((prefix + std::string("auto _weak_result = ")) + call) + std::string("; if (doof::is_failure(_weak_result)) return doof::Failure<")) + errorCpp) + std::string(">{")) + promotedError) + std::string("}; return doof::Success<void>{}; }()"));
                        }
#line 482 "/src/emitter-expr-calls.do"
                        return (((((((((((prefix + std::string("auto _weak_result = ")) + call) + std::string("; if (doof::is_failure(_weak_result)) return doof::Failure<")) + errorCpp) + std::string(">{")) + promotedError) + std::string("}; return doof::Success<")) + payloadCpp) + std::string(">{")) + payloadCpp) + std::string("{doof::success_value(_weak_result)}}; }()"));
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 484 "/src/emitter-expr-calls.do"
                        return ((prefix + call) + std::string("; return doof::Success<void>{}; }()"));
                }
                else {
                }
                }
            }
#line 488 "/src/emitter-expr-calls.do"
            return (((((((prefix + std::string("return doof::Success<")) + payloadCpp) + std::string(">{")) + payloadCpp) + std::string("{")) + call) + std::string("}}; }()"));
    }
    else {
#line 490 "/src/emitter-expr-calls.do"
            doof::panic(std::string("Optional weak method call must resolve to Result"));
    }
    }
    doof::unreachable();
#line 492 "/src/emitter-expr-calls.do"
    return std::string("");
}
#line 495 "/src/emitter-expr-calls.do"
bool weakCallTargetAllowsNone(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 496 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 497 "/src/emitter-expr-calls.do"
            const auto& _iterable_22 = union_->types;
            for (const auto& member : *_iterable_22) {
#line 497 "/src/emitter-expr-calls.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 497 "/src/emitter-expr-calls.do"
                    return true;
                }
            }
    }
    else {
    }
    }
#line 500 "/src/emitter-expr-calls.do"
    return false;
}
#line 503 "/src/emitter-expr-calls.do"
bool weakCallTargetUsesVariant(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 504 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 506 "/src/emitter-expr-calls.do"
            auto present = 0;
#line 507 "/src/emitter-expr-calls.do"
            const auto& _iterable_24 = union_->types;
            for (const auto& member : *_iterable_24) {
#line 507 "/src/emitter-expr-calls.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 507 "/src/emitter-expr-calls.do"
                    (present = (present + 1));
                }
            }
#line 508 "/src/emitter-expr-calls.do"
            return (present > 1);
    }
    else {
    }
    }
#line 512 "/src/emitter-expr-calls.do"
    return false;
}
#line 515 "/src/emitter-expr-calls.do"
std::string emitWeakCallArguments(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 516 "/src/emitter-expr-calls.do"
    auto result = std::string("");
#line 517 "/src/emitter-expr-calls.do"
    auto named = false;
#line 518 "/src/emitter-expr-calls.do"
    const auto& _iterable_26 = expression->args;
    for (const auto& argument : *_iterable_26) {
#line 518 "/src/emitter-expr-calls.do"
        if (!doof::is_null(argument->name)) {
#line 518 "/src/emitter-expr-calls.do"
            (named = true);
        }
    }
#line 519 "/src/emitter-expr-calls.do"
    if (!doof::is_null(expression->resolvedFunction)) {
#line 520 "/src/emitter-expr-calls.do"
        for (int32_t i = 0; i < static_cast<int32_t>((expression->resolvedFunction->params)->size()); ++i) {
#line 521 "/src/emitter-expr-calls.do"
            const auto parameter = doof::array_at(expression->resolvedFunction->params, i, "src/emitter-expr-calls", 521);
#line 522 "/src/emitter-expr-calls.do"
            const auto argument = [&]() -> std::shared_ptr<::app_src_ast_::CallArgument> { if (named) { return callArgumentNamed(expression, parameter->name); } return [&]() -> std::shared_ptr<::app_src_ast_::CallArgument> { if ((i < static_cast<int32_t>((expression->args)->size()))) { return doof::array_at(expression->args, i, "src/emitter-expr-calls", 522); } return nullptr; }(); }();
#line 523 "/src/emitter-expr-calls.do"
            if ((!doof::is_null(argument)) || (!doof::is_null(parameter->defaultValue))) {
#line 524 "/src/emitter-expr-calls.do"
                if (result != std::string("")) {
#line 524 "/src/emitter-expr-calls.do"
                    (result = (result + std::string(", ")));
                }
#line 525 "/src/emitter-expr-calls.do"
                if (!doof::is_null(argument)) {
#line 525 "/src/emitter-expr-calls.do"
                    (result = (result + ::app_src_emitter_expr_utils_::emitExpectedExpression(argument->value, context, parameter->resolvedType)));
                } else {
#line 526 "/src/emitter-expr-calls.do"
                    (result = (result + emitDefaultExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType, expression->span)));
                }
            }
        }
#line 529 "/src/emitter-expr-calls.do"
        return result;
    }
#line 531 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->args)->size()); ++i) {
#line 532 "/src/emitter-expr-calls.do"
        if (i > 0) {
#line 532 "/src/emitter-expr-calls.do"
            (result = (result + std::string(", ")));
        }
#line 533 "/src/emitter-expr-calls.do"
        (result = (result + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->args, i, "src/emitter-expr-calls", 533)->value, context, std::monostate{})));
    }
#line 535 "/src/emitter-expr-calls.do"
    return result;
}
#line 538 "/src/emitter-expr-calls.do"
bool isBuiltinConversionIdentifier(const std::shared_ptr<::app_src_ast_::Identifier>& identifier) {
#line 539 "/src/emitter-expr-calls.do"
    if (doof::is_null(identifier->resolvedBinding) || (identifier->resolvedBinding->kind != std::string("builtin"))) {
#line 539 "/src/emitter-expr-calls.do"
        return false;
    }
#line 540 "/src/emitter-expr-calls.do"
    const auto name = identifier->name;
#line 541 "/src/emitter-expr-calls.do"
    return ((((((((name == std::string("string")) || (name == std::string("byte"))) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double"))) || (name == std::string("char"))) || (name == std::string("bool")));
}
#line 544 "/src/emitter-expr-calls.do"
bool isBuiltinIdentifier(const std::shared_ptr<::app_src_ast_::Identifier>& identifier, const std::string& name) {
#line 545 "/src/emitter-expr-calls.do"
    return (((identifier->name == name) && (!doof::is_null(identifier->resolvedBinding))) && (identifier->resolvedBinding->kind == std::string("builtin")));
}
#line 548 "/src/emitter-expr-calls.do"
bool isClassCallee(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& callee) {
#line 549 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 551 "/src/emitter-expr-calls.do"
            if (doof::is_null(identifier->resolvedBinding)) {
#line 551 "/src/emitter-expr-calls.do"
                return false;
            }
#line 552 "/src/emitter-expr-calls.do"
            const auto binding = doof::unwrap_optional(identifier->resolvedBinding);
#line 553 "/src/emitter-expr-calls.do"
            if ((binding->kind == std::string("class")) || (binding->kind == std::string("struct"))) {
#line 553 "/src/emitter-expr-calls.do"
                return true;
            }
#line 556 "/src/emitter-expr-calls.do"
            if ((binding->kind == std::string("import")) && (!doof::is_null(binding->symbol))) {
#line 557 "/src/emitter-expr-calls.do"
                return ((binding->symbol->kind == std::string("class")) || (binding->symbol->kind == std::string("struct")));
            }
#line 559 "/src/emitter-expr-calls.do"
            return false;
    }
    else {
#line 561 "/src/emitter-expr-calls.do"
            return false;
    }
    }
    doof::unreachable();
}
#line 565 "/src/emitter-expr-calls.do"
std::shared_ptr<::app_src_ast_::CallArgument> callArgumentNamed(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::string& name) {
#line 566 "/src/emitter-expr-calls.do"
    const auto& _iterable_30 = expression->args;
    for (const auto& argument : *_iterable_30) {
#line 566 "/src/emitter-expr-calls.do"
        if (argument->name == name) {
#line 566 "/src/emitter-expr-calls.do"
            return argument;
        }
    }
#line 567 "/src/emitter-expr-calls.do"
    return nullptr;
}
#line 570 "/src/emitter-expr-calls.do"
std::string emitBuiltinCall(const std::string& name, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& object, const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 571 "/src/emitter-expr-calls.do"
    auto result = ((name + std::string("(")) + ::app_src_emitter_expr_::emitExpression(object, context, std::monostate{}));
#line 572 "/src/emitter-expr-calls.do"
    const auto& _iterable_32 = expression->args;
    for (const auto& argument : *_iterable_32) {
#line 572 "/src/emitter-expr-calls.do"
        (result = ((result + std::string(", ")) + ::app_src_emitter_expr_::emitExpression(argument->value, context, std::monostate{})));
    }
#line 573 "/src/emitter-expr-calls.do"
    return (result + std::string(")"));
}
#line 576 "/src/emitter-expr-calls.do"
std::string emitInterfaceCall(const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 577 "/src/emitter-expr-calls.do"
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 578 "/src/emitter-expr-calls.do"
    auto args = std::string("");
#line 579 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
#line 580 "/src/emitter-expr-calls.do"
        if (i > 0) {
#line 580 "/src/emitter-expr-calls.do"
            (args = (args + std::string(", ")));
        }
#line 581 "/src/emitter-expr-calls.do"
        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(call->args, i, "src/emitter-expr-calls", 581)->value, context, std::monostate{})));
    }
#line 583 "/src/emitter-expr-calls.do"
    return ((((((std::string("std::visit([&](auto&& _obj) { return _obj->") + ::app_src_emitter_expr_::cppIdentifier(member->property)) + std::string("(")) + args) + std::string("); }, ")) + object) + std::string(")"));
}
#line 586 "/src/emitter-expr-calls.do"
std::string emitVariantMemberCall(const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 587 "/src/emitter-expr-calls.do"
    const auto object = ::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{});
#line 588 "/src/emitter-expr-calls.do"
    const auto objectType = ::app_src_emitter_expr_utils_::decoratedExpressionType(member->object);
#line 589 "/src/emitter-expr-calls.do"
    if (doof::is_null(objectType)) {
#line 589 "/src/emitter-expr-calls.do"
        doof::panic(std::string("Variant member call has no resolved object type"));
    }
#line 590 "/src/emitter-expr-calls.do"
    if (doof::is_null(call->resolvedType)) {
#line 590 "/src/emitter-expr-calls.do"
        doof::panic(std::string("Variant member call has no resolved return type"));
    }
#line 591 "/src/emitter-expr-calls.do"
    auto args = std::string("");
#line 592 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
#line 593 "/src/emitter-expr-calls.do"
        if (i > 0) {
#line 593 "/src/emitter-expr-calls.do"
            (args = (args + std::string(", ")));
        }
#line 594 "/src/emitter-expr-calls.do"
        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(call->args, i, "src/emitter-expr-calls", 594)->value, context, std::monostate{})));
    }
#line 596 "/src/emitter-expr-calls.do"
    const auto invocation = (member->resolvedCallableField ? std::string(".call(") : std::string("("));
#line 597 "/src/emitter-expr-calls.do"
    return ((((((((std::string("std::visit([&](auto&& _obj) -> ") + ::app_src_emitter_types_::emitContextReturnType(doof::unwrap_optional(call->resolvedType), context)) + std::string(" { return _obj->")) + ::app_src_emitter_expr_::cppIdentifier(member->property)) + invocation) + args) + std::string("); }, ")) + ::app_src_emitter_expr_utils_::variantVisitValue(object, doof::unwrap_optional(objectType))) + std::string(")"));
}
#line 600 "/src/emitter-expr-calls.do"
std::string emitInterfaceJsonCall(const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 601 "/src/emitter-expr-calls.do"
    auto args = std::string("");
#line 602 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((call->args)->size()); ++i) {
#line 603 "/src/emitter-expr-calls.do"
        if (i > 0) {
#line 603 "/src/emitter-expr-calls.do"
            (args = (args + std::string(", ")));
        }
#line 604 "/src/emitter-expr-calls.do"
        (args = (args + ::app_src_emitter_expr_::emitExpression(doof::array_at(call->args, i, "src/emitter-expr-calls", 604)->value, context, std::monostate{})));
    }
#line 606 "/src/emitter-expr-calls.do"
    if (static_cast<int32_t>((call->args)->size()) == 1) {
#line 606 "/src/emitter-expr-calls.do"
        (args = (args + std::string(", false")));
    }
#line 607 "/src/emitter-expr-calls.do"
    return (((::app_src_emitter_expr_::emitExpression(member->object, context, std::monostate{}) + std::string("_fromJsonValue(")) + args) + std::string(")"));
}
#line 610 "/src/emitter-expr-calls.do"
std::string builtinName(const std::string& name) {
#line 611 "/src/emitter-expr-calls.do"
    if (name == std::string("println")) {
#line 611 "/src/emitter-expr-calls.do"
        return std::string("doof::println");
    }
#line 612 "/src/emitter-expr-calls.do"
    if (name == std::string("panic")) {
#line 612 "/src/emitter-expr-calls.do"
        return std::string("doof::panic");
    }
#line 613 "/src/emitter-expr-calls.do"
    if (name == std::string("assert")) {
#line 613 "/src/emitter-expr-calls.do"
        return std::string("doof::assert_");
    }
#line 614 "/src/emitter-expr-calls.do"
    if (name == std::string("string")) {
#line 614 "/src/emitter-expr-calls.do"
        return std::string("doof::to_string");
    }
#line 615 "/src/emitter-expr-calls.do"
    if (name == std::string("byte")) {
#line 615 "/src/emitter-expr-calls.do"
        return std::string("static_cast<uint8_t>");
    }
#line 616 "/src/emitter-expr-calls.do"
    if (name == std::string("int")) {
#line 616 "/src/emitter-expr-calls.do"
        return std::string("static_cast<int32_t>");
    }
#line 617 "/src/emitter-expr-calls.do"
    if (name == std::string("long")) {
#line 617 "/src/emitter-expr-calls.do"
        return std::string("static_cast<int64_t>");
    }
#line 618 "/src/emitter-expr-calls.do"
    if (name == std::string("float")) {
#line 618 "/src/emitter-expr-calls.do"
        return std::string("static_cast<float>");
    }
#line 619 "/src/emitter-expr-calls.do"
    if (name == std::string("double")) {
#line 619 "/src/emitter-expr-calls.do"
        return std::string("static_cast<double>");
    }
#line 620 "/src/emitter-expr-calls.do"
    if (name == std::string("char")) {
#line 620 "/src/emitter-expr-calls.do"
        return std::string("static_cast<char32_t>");
    }
#line 621 "/src/emitter-expr-calls.do"
    if (name == std::string("bool")) {
#line 621 "/src/emitter-expr-calls.do"
        return std::string("static_cast<bool>");
    }
#line 622 "/src/emitter-expr-calls.do"
    return name;
}
#line 625 "/src/emitter-expr-calls.do"
bool isBuiltinName(const std::string& name) {
#line 626 "/src/emitter-expr-calls.do"
    return ((((((((((((name == std::string("println")) || (name == std::string("panic"))) || (name == std::string("assert"))) || (name == std::string("catchPanic"))) || (name == std::string("string"))) || (name == std::string("byte"))) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double"))) || (name == std::string("char"))) || (name == std::string("bool")));
}
#line 629 "/src/emitter-expr-calls.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaredConstructor(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_) {
#line 630 "/src/emitter-expr-calls.do"
    const auto& _iterable_37 = class_->methods;
    for (const auto& method : *_iterable_37) {
#line 630 "/src/emitter-expr-calls.do"
        if (method->name == std::string("constructor")) {
#line 630 "/src/emitter-expr-calls.do"
            return method;
        }
    }
#line 631 "/src/emitter-expr-calls.do"
    return nullptr;
}
#line 634 "/src/emitter-expr-calls.do"
bool insideDeclaredConstructor(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 635 "/src/emitter-expr-calls.do"
    return ((context->currentClass == class_->name) && (context->currentFunctionName == std::string("constructor")));
}
#line 638 "/src/emitter-expr-calls.do"
std::string emitConstruct(const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 639 "/src/emitter-expr-calls.do"
    if ((expression->type_ == std::string("Success")) || (expression->type_ == std::string("Failure"))) {
#line 640 "/src/emitter-expr-calls.do"
        const auto resultType = expression->resolvedType;
#line 641 "/src/emitter-expr-calls.do"
        if (doof::is_null(resultType)) {
#line 641 "/src/emitter-expr-calls.do"
            doof::panic((expression->type_ + std::string(" has no resolved Result type")));
        }
#line 642 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = doof::unwrap_optional(resultType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 644 "/src/emitter-expr-calls.do"
                const auto valueType = ((expression->type_ == std::string("Success")) ? result->valueType : result->errorType);
#line 645 "/src/emitter-expr-calls.do"
                const auto propertyName = ((expression->type_ == std::string("Success")) ? std::string("value") : std::string("error"));
#line 646 "/src/emitter-expr-calls.do"
                const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->args, propertyName);
#line 647 "/src/emitter-expr-calls.do"
                const auto payloadType = ::app_src_emitter_types_::emitResultPayloadType(valueType, context->modulePath);
#line 648 "/src/emitter-expr-calls.do"
                if (doof::is_null(property) || doof::is_null(property->value)) {
#line 648 "/src/emitter-expr-calls.do"
                    return ((((std::string("doof::") + expression->type_) + std::string("<")) + payloadType) + std::string(">{ }"));
                }
#line 649 "/src/emitter-expr-calls.do"
                const auto value = ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::unwrap_optional(property->value), context, doof::optional_value(valueType));
#line 650 "/src/emitter-expr-calls.do"
                return ((((((std::string("doof::") + expression->type_) + std::string("<")) + payloadType) + std::string(">{ ")) + value) + std::string(" }"));
        }
        else {
        }
        }
#line 654 "/src/emitter-expr-calls.do"
        doof::panic((expression->type_ + std::string(" does not construct a Result")));
    }
#line 656 "/src/emitter-expr-calls.do"
    const auto class_ = expression->resolvedClass;
#line 657 "/src/emitter-expr-calls.do"
    if (doof::is_null(class_)) {
#line 657 "/src/emitter-expr-calls.do"
        doof::panic((std::string("Cannot construct unresolved class ") + expression->type_));
    }
#line 658 "/src/emitter-expr-calls.do"
    const auto constructedType = expression->resolvedConstructedType;
#line 659 "/src/emitter-expr-calls.do"
    if (doof::is_null(constructedType)) {
#line 659 "/src/emitter-expr-calls.do"
        doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has no resolved constructed type")));
    }
#line 660 "/src/emitter-expr-calls.do"
    std::shared_ptr<::app_src_semantic_::ClassType> owner = nullptr;
#line 661 "/src/emitter-expr-calls.do"
    {
        auto _case_subject = doof::unwrap_optional(constructedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 662 "/src/emitter-expr-calls.do"
            (owner = class_);
    }
    else {
#line 663 "/src/emitter-expr-calls.do"
            doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has a non-class constructed type")));
    }
    }
#line 665 "/src/emitter-expr-calls.do"
    const auto constructorMethod = declaredConstructor(doof::unwrap_optional(class_));
#line 666 "/src/emitter-expr-calls.do"
    const auto insideConstructor = insideDeclaredConstructor(doof::unwrap_optional(class_), context);
#line 667 "/src/emitter-expr-calls.do"
    if (((!doof::is_null(constructorMethod)) && !insideConstructor) && doof::is_null(expression->resolvedConstructor)) {
#line 668 "/src/emitter-expr-calls.do"
        doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has no resolved constructor")));
    }
#line 670 "/src/emitter-expr-calls.do"
    if (!doof::is_null(expression->resolvedConstructor)) {
#line 671 "/src/emitter-expr-calls.do"
        if (doof::is_null(constructorMethod)) {
#line 671 "/src/emitter-expr-calls.do"
            doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has unexpected constructor metadata")));
        }
#line 672 "/src/emitter-expr-calls.do"
        return emitNamedConstructorFactoryCall(doof::unwrap_optional(owner), doof::unwrap_optional(expression->resolvedConstructor), expression, context);
    }
#line 674 "/src/emitter-expr-calls.do"
    auto cppName = expression->type_;
#line 675 "/src/emitter-expr-calls.do"
    auto native = class_->native_;
#line 676 "/src/emitter-expr-calls.do"
    auto structValue = false;
#line 677 "/src/emitter-expr-calls.do"
    if (native) {
#line 677 "/src/emitter-expr-calls.do"
        (cppName = (std::string("::") + ((class_->nativeCppName == std::string("")) ? class_->name : class_->nativeCppName)));
    }
#line 678 "/src/emitter-expr-calls.do"
    if (!doof::is_null(expression->resolvedType)) {
#line 679 "/src/emitter-expr-calls.do"
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 681 "/src/emitter-expr-calls.do"
                (structValue = (resolved->symbol->kind == std::string("struct")));
#line 682 "/src/emitter-expr-calls.do"
                if (resolved->symbol->native_) {
#line 682 "/src/emitter-expr-calls.do"
                    (cppName = (std::string("::") + ((resolved->symbol->nativeCppName == std::string("")) ? resolved->symbol->name : resolved->symbol->nativeCppName)));
                } else if (((context->modulePath != std::string("")) && (resolved->symbol->module != std::string(""))) && (resolved->symbol->module != context->modulePath)) {
#line 683 "/src/emitter-expr-calls.do"
                    (cppName = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(resolved->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(resolved->symbol)));
                }
#line 684 "/src/emitter-expr-calls.do"
                const auto concrete = concreteClassName(resolved, context);
#line 685 "/src/emitter-expr-calls.do"
                if (concrete != std::string("")) {
#line 685 "/src/emitter-expr-calls.do"
                    (cppName = concrete);
                }
        }
        else {
        }
        }
    }
#line 690 "/src/emitter-expr-calls.do"
    auto values = std::string("");
#line 691 "/src/emitter-expr-calls.do"
    auto first = true;
#line 692 "/src/emitter-expr-calls.do"
    const auto& _iterable_39 = class_->fields;
    for (const auto& field : *_iterable_39) {
#line 693 "/src/emitter-expr-calls.do"
        if (field->static_ || field->const_) {
#line 693 "/src/emitter-expr-calls.do"
            continue;
        }
#line 694 "/src/emitter-expr-calls.do"
        const auto& _iterable_41 = field->names;
        for (const auto& name : *_iterable_41) {
#line 695 "/src/emitter-expr-calls.do"
            if (!first) {
#line 695 "/src/emitter-expr-calls.do"
                (values = (values + std::string(", ")));
            }
#line 696 "/src/emitter-expr-calls.do"
            (first = false);
#line 697 "/src/emitter-expr-calls.do"
            const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->args, name);
#line 698 "/src/emitter-expr-calls.do"
            auto value = std::string("");
#line 699 "/src/emitter-expr-calls.do"
            if (!doof::is_null(property)) {
#line 700 "/src/emitter-expr-calls.do"
                if (doof::is_null(property->value)) {
#line 700 "/src/emitter-expr-calls.do"
                    (value = ::app_src_emitter_expr_::cppIdentifier(name));
                } else {
#line 702 "/src/emitter-expr-calls.do"
                    {
                        auto _case_subject = doof::unwrap_optional(property->value);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
#line 704 "/src/emitter-expr-calls.do"
                            {
                                auto _case_subject = doof::unwrap_optional(field->resolvedType);
                                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 705 "/src/emitter-expr-calls.do"
                                    (value = ((((std::string("std::shared_ptr<") + class_->name) + std::string(">(this, [](")) + class_->name) + std::string("*) {})")));
                            }
                            else {
#line 706 "/src/emitter-expr-calls.do"
                                    (value = ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::unwrap_optional(property->value), context, field->resolvedType));
                            }
                            }
                    }
                    else {
#line 709 "/src/emitter-expr-calls.do"
                            (value = ::app_src_emitter_expr_utils_::emitExpectedExpression(doof::unwrap_optional(property->value), context, field->resolvedType));
                    }
                    }
                }
            } else if (!doof::is_null(field->defaultValue)) {
#line 712 "/src/emitter-expr-calls.do"
                (value = emitDefaultExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType, expression->span));
            } else {
#line 713 "/src/emitter-expr-calls.do"
                doof::panic(((((std::string("Construction of '") + expression->type_) + std::string("' is missing required field '")) + name) + std::string("'")));
            }
#line 716 "/src/emitter-expr-calls.do"
            if (((!doof::is_null(property)) && doof::is_null(property->value)) && ::app_src_emitter_expr_utils_::needsNullableVariantPromotion(property->resolvedType, field->resolvedType)) {
#line 716 "/src/emitter-expr-calls.do"
                (value = ::app_src_emitter_expr_utils_::emitNullableVariantPromotion(value, property->resolvedType, field->resolvedType, context->modulePath));
            } else if (((!doof::is_null(property)) && doof::is_null(property->value)) && ::app_src_emitter_expr_utils_::needsVariantPromotion(property->resolvedType, field->resolvedType)) {
#line 717 "/src/emitter-expr-calls.do"
                (value = ((((std::string("doof::variant_promote<") + ::app_src_emitter_types_::emitContextType(doof::unwrap_optional(field->resolvedType), context)) + std::string(">(")) + value) + std::string(")")));
            }
#line 718 "/src/emitter-expr-calls.do"
            (values = (values + value));
        }
    }
#line 721 "/src/emitter-expr-calls.do"
    if (native) {
#line 721 "/src/emitter-expr-calls.do"
        return ((((std::string("std::make_shared<") + cppName) + std::string(">(")) + values) + std::string(")"));
    }
#line 722 "/src/emitter-expr-calls.do"
    if (structValue) {
#line 722 "/src/emitter-expr-calls.do"
        return (((cppName + std::string("{")) + values) + std::string("}"));
    }
#line 723 "/src/emitter-expr-calls.do"
    return ((((std::string("std::make_shared<") + cppName) + std::string(">(")) + values) + std::string(")"));
}
#line 726 "/src/emitter-expr-calls.do"
std::string emitConstructorFactoryCall(const std::shared_ptr<::app_src_semantic_::ClassType>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& constructorMethod, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>>& args, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, ::app_src_ast_::SourceSpan callSiteSpan) {
#line 727 "/src/emitter-expr-calls.do"
    auto cppName = (owner->symbol->native_ ? (std::string("::") + ((owner->symbol->nativeCppName == std::string("")) ? owner->symbol->name : owner->symbol->nativeCppName)) : (((owner->symbol->module != std::string("")) && (owner->symbol->module != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(owner->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol)) : ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol)));
#line 728 "/src/emitter-expr-calls.do"
    const auto concrete = concreteClassName(owner, context);
#line 729 "/src/emitter-expr-calls.do"
    if (concrete != std::string("")) {
#line 729 "/src/emitter-expr-calls.do"
        (cppName = concrete);
    }
#line 730 "/src/emitter-expr-calls.do"
    auto result = (cppName + std::string("::constructor("));
#line 731 "/src/emitter-expr-calls.do"
    auto named = false;
#line 732 "/src/emitter-expr-calls.do"
    const auto& _iterable_43 = args;
    for (const auto& argument : *_iterable_43) {
#line 732 "/src/emitter-expr-calls.do"
        if (!doof::is_null(argument->name)) {
#line 732 "/src/emitter-expr-calls.do"
            (named = true);
        }
    }
#line 733 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((constructorMethod->params)->size()); ++i) {
#line 734 "/src/emitter-expr-calls.do"
        if (i > 0) {
#line 734 "/src/emitter-expr-calls.do"
            (result = (result + std::string(", ")));
        }
#line 735 "/src/emitter-expr-calls.do"
        const auto parameter = doof::array_at(constructorMethod->params, i, "src/emitter-expr-calls", 735);
#line 736 "/src/emitter-expr-calls.do"
        const auto argument = [&]() -> std::shared_ptr<::app_src_ast_::CallArgument> { if (named) { return callArgumentNamedFromArgs(args, parameter->name); } return [&]() -> std::shared_ptr<::app_src_ast_::CallArgument> { if ((i < static_cast<int32_t>((args)->size()))) { return doof::array_at(args, i, "src/emitter-expr-calls", 736); } return nullptr; }(); }();
#line 737 "/src/emitter-expr-calls.do"
        if (!doof::is_null(argument)) {
#line 737 "/src/emitter-expr-calls.do"
            (result = (result + ::app_src_emitter_expr_::emitExpression(argument->value, context, parameter->resolvedType)));
        } else {
#line 739 "/src/emitter-expr-calls.do"
            if (doof::is_null(parameter->defaultValue)) {
#line 739 "/src/emitter-expr-calls.do"
                doof::panic((((std::string("Constructor ") + owner->name) + std::string(" is missing argument ")) + parameter->name));
            }
#line 740 "/src/emitter-expr-calls.do"
            (result = (result + emitDefaultExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType, callSiteSpan)));
        }
    }
#line 743 "/src/emitter-expr-calls.do"
    return (result + std::string(")"));
}
#line 746 "/src/emitter-expr-calls.do"
std::shared_ptr<::app_src_ast_::CallArgument> callArgumentNamedFromArgs(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>>& args, const std::string& name) {
#line 747 "/src/emitter-expr-calls.do"
    const auto& _iterable_46 = args;
    for (const auto& argument : *_iterable_46) {
#line 747 "/src/emitter-expr-calls.do"
        if (argument->name == name) {
#line 747 "/src/emitter-expr-calls.do"
            return argument;
        }
    }
#line 748 "/src/emitter-expr-calls.do"
    return nullptr;
}
#line 751 "/src/emitter-expr-calls.do"
std::string emitNamedConstructorFactoryCall(const std::shared_ptr<::app_src_semantic_::ClassType>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& constructorMethod, const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 752 "/src/emitter-expr-calls.do"
    auto cppName = (owner->symbol->native_ ? (std::string("::") + ((owner->symbol->nativeCppName == std::string("")) ? owner->symbol->name : owner->symbol->nativeCppName)) : (((owner->symbol->module != std::string("")) && (owner->symbol->module != context->modulePath)) ? (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(owner->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol)) : ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol)));
#line 753 "/src/emitter-expr-calls.do"
    const auto concrete = concreteClassName(owner, context);
#line 754 "/src/emitter-expr-calls.do"
    if (concrete != std::string("")) {
#line 754 "/src/emitter-expr-calls.do"
        (cppName = concrete);
    }
#line 755 "/src/emitter-expr-calls.do"
    auto result = (cppName + std::string("::constructor("));
#line 756 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((constructorMethod->params)->size()); ++i) {
#line 757 "/src/emitter-expr-calls.do"
        if (i > 0) {
#line 757 "/src/emitter-expr-calls.do"
            (result = (result + std::string(", ")));
        }
#line 758 "/src/emitter-expr-calls.do"
        const auto parameter = doof::array_at(constructorMethod->params, i, "src/emitter-expr-calls", 758);
#line 759 "/src/emitter-expr-calls.do"
        const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->args, parameter->name);
#line 760 "/src/emitter-expr-calls.do"
        if (!doof::is_null(property)) {
#line 761 "/src/emitter-expr-calls.do"
            if (doof::is_null(property->value)) {
#line 761 "/src/emitter-expr-calls.do"
                (result = (result + ::app_src_emitter_expr_::cppIdentifier(property->name)));
            } else {
#line 762 "/src/emitter-expr-calls.do"
                (result = (result + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->value), context, parameter->resolvedType)));
            }
        } else if (!doof::is_null(parameter->defaultValue)) {
#line 764 "/src/emitter-expr-calls.do"
            (result = (result + emitDefaultExpression(doof::unwrap_optional(parameter->defaultValue), context, parameter->resolvedType, expression->span)));
        } else {
#line 765 "/src/emitter-expr-calls.do"
            doof::panic((((std::string("Constructor ") + owner->name) + std::string(" is missing argument ")) + parameter->name));
        }
    }
#line 767 "/src/emitter-expr-calls.do"
    return (result + std::string(")"));
}
#line 770 "/src/emitter-expr-calls.do"
std::string emitDefaultExpression(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected, ::app_src_ast_::SourceSpan callSiteSpan) {
#line 771 "/src/emitter-expr-calls.do"
    const auto previous = context->sourceLocationSpanOverride;
#line 772 "/src/emitter-expr-calls.do"
    (context->sourceLocationSpanOverride = std::make_shared<::app_src_emitter_context_::SourceLocationSpanOverride>(callSiteSpan));
#line 773 "/src/emitter-expr-calls.do"
    const auto result = ::app_src_emitter_expr_::emitExpression(expression, context, expected);
#line 774 "/src/emitter-expr-calls.do"
    (context->sourceLocationSpanOverride = previous);
#line 775 "/src/emitter-expr-calls.do"
    return result;
}
#line 778 "/src/emitter-expr-calls.do"
std::string concreteFunctionName(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& key) {
#line 779 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteFunctionKeys)->size()); ++i) {
#line 780 "/src/emitter-expr-calls.do"
        if (doof::array_at(context->concreteFunctionKeys, i, "src/emitter-expr-calls", 780) == key) {
#line 780 "/src/emitter-expr-calls.do"
            return doof::array_at(context->concreteFunctionNames, i, "src/emitter-expr-calls", 780);
        }
    }
#line 782 "/src/emitter-expr-calls.do"
    return std::string("");
}
#line 785 "/src/emitter-expr-calls.do"
std::string concreteMethodNameFor(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& key) {
#line 786 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteMethodKeys)->size()); ++i) {
#line 787 "/src/emitter-expr-calls.do"
        if (doof::array_at(context->concreteMethodKeys, i, "src/emitter-expr-calls", 787) == key) {
#line 787 "/src/emitter-expr-calls.do"
            return doof::array_at(context->concreteMethodNames, i, "src/emitter-expr-calls", 787);
        }
    }
#line 789 "/src/emitter-expr-calls.do"
    return std::string("");
}
#line 792 "/src/emitter-expr-calls.do"
std::string concreteClassName(const std::shared_ptr<::app_src_semantic_::ClassType>& class_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 793 "/src/emitter-expr-calls.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 794 "/src/emitter-expr-calls.do"
    const auto& _iterable_51 = class_->typeArgs;
    for (const auto& argument : *_iterable_51) {
#line 794 "/src/emitter-expr-calls.do"
        typeArgs->push_back(::app_src_emitter_types_::specializeEmitType(argument, context));
    }
#line 795 "/src/emitter-expr-calls.do"
    if (static_cast<int32_t>((typeArgs)->size()) == 0) {
#line 795 "/src/emitter-expr-calls.do"
        return std::string("");
    }
#line 796 "/src/emitter-expr-calls.do"
    const auto key = ::app_src_emitter_monomorphize_::classInstantiationKey(class_->symbol->module, class_->name, typeArgs);
#line 797 "/src/emitter-expr-calls.do"
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteClassKeys)->size()); ++i) {
#line 798 "/src/emitter-expr-calls.do"
        if (doof::array_at(context->concreteClassKeys, i, "src/emitter-expr-calls", 798) == key) {
#line 799 "/src/emitter-expr-calls.do"
            const auto name = doof::array_at(context->concreteClassNames, i, "src/emitter-expr-calls", 799);
#line 800 "/src/emitter-expr-calls.do"
            if ((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) {
#line 800 "/src/emitter-expr-calls.do"
                return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(class_->symbol->module)) + std::string("::")) + name);
            }
#line 801 "/src/emitter-expr-calls.do"
            return name;
        }
    }
#line 804 "/src/emitter-expr-calls.do"
    return std::string("");
}
#line 1 "<doof-generated>"
}
