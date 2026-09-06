#include "src_emitter_construction.hpp"

namespace app_src_emitter_construction_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_monomorphize_;
using namespace ::app_src_emitter_call_arguments_;

std::string emitConstructionValues(const std::shared_ptr<::app_src_ast_::CheckedConstruction>& plan, const std::shared_ptr<ConstructionInputs>& inputs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto values = std::string("");
    for (int32_t index = 0; index < static_cast<int32_t>((plan->signature->params)->size()); ++index) {
        const auto parameter = doof::array_at(plan->signature->params, index, "src/emitter-construction", 29);
        if (index > 0) {
            static_cast<void>((values = (values + std::string(", "))));
        }
        const auto expected = ::app_src_emitter_types_::specializeEmitType(parameter->type_, context);
        static_cast<void>((values = (values + emitConstructionValue(inputs, parameter->name, index, expected, doof::array_at(plan->defaults, index, "src/emitter-construction", 32)->value, plan->owner, plan->owner->symbol->typeParams, ((((std::string("Construction of '") + plan->owner->name) + std::string("' is missing required field '")) + parameter->name) + std::string("'")), context))));
    }
    return values;
}
std::string emitConstructionValue(const std::shared_ptr<ConstructionInputs>& inputs, const std::string& name, int32_t index, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected, const std::variant<std::monostate, std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& defaultValue, const std::shared_ptr<::app_src_semantic_::ClassType>& owner, const std::shared_ptr<std::vector<std::string>>& ownerTypeParams, const std::string& missingMessage, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto property = ::app_src_emitter_expr_utils_::findProperty(inputs->properties, name);
    if (!doof::is_null(property)) {
        if (inputs->aliasThis && (!doof::is_null(property->value))) {
            {
                auto _case_subject = doof::unwrap_optional(property->value);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
                    {
                        auto _case_subject = expected;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            return ((((std::string("std::shared_ptr<") + class_->name) + std::string(">(this, [](")) + class_->name) + std::string("*) {})"));
                    }
                    else {
                    }
                    }
            }
            else {
            }
            }
        }
        return ::app_src_emitter_expr_utils_::emitPropertyValue(doof::unwrap_optional(property), context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(expected));
    }
    const auto argument = [&]() -> std::shared_ptr<::app_src_ast_::CallArgument> { if (inputs->named) { return ::app_src_emitter_call_arguments_::callArgumentNamed(inputs->args, name); } return [&]() -> std::shared_ptr<::app_src_ast_::CallArgument> { if (index < static_cast<int32_t>((inputs->args)->size())) { return doof::array_at(inputs->args, index, "src/emitter-construction", 54); } return nullptr; }(); }();
    if (!doof::is_null(argument)) {
        return ::app_src_emitter_expr_::emitExpression(argument->value, context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(expected));
    }
    if ((!doof::is_null(inputs->construct)) && hasSpreadField(doof::unwrap_optional(inputs->construct), name)) {
        return emitConstructionSpreadField(doof::unwrap_optional(inputs->construct), inputs->spreadName, name, context);
    }
    if (!doof::is_null(defaultValue)) {
        return emitOwnerDefaultExpression(doof::unwrap_optional(defaultValue), context, expected, inputs->span, owner, ownerTypeParams);
    }
    doof::panic(missingMessage);
}
std::optional<std::string> emitClassCall(const std::shared_ptr<::app_src_ast_::CallExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expression->resolvedConstruction)) {
        return std::nullopt;
    }
    const auto plan = doof::unwrap_optional(expression->resolvedConstruction);
    if (plan->factory != expression->resolvedConstructor) {
        doof::panic(std::string("Construction has no resolved constructor consistent with its checked plan"));
    }
    const auto inputs = std::make_shared<ConstructionInputs>(expression->args, std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>>(std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>{}), ::app_src_emitter_call_arguments_::hasNamedArguments(expression->args), expression->span, nullptr, std::string(""), false);
    return emitPlannedConstruction(plan, inputs, context);
}
std::string emitPlannedConstruction(const std::shared_ptr<::app_src_ast_::CheckedConstruction>& plan, const std::shared_ptr<ConstructionInputs>& inputs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto values = emitConstructionValues(plan, inputs, context);
    const auto name = constructionClassName(plan->owner, context);
    if (!doof::is_null(plan->factory)) {
        return (((name + std::string("::constructor(")) + values) + std::string(")"));
    }
    return emitClassAllocation(name, (plan->owner->symbol->kind == std::string("struct")), values);
}
std::string emitActorConstruction(const std::shared_ptr<::app_src_ast_::ActorCreationExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expression->resolvedConstruction)) {
        doof::panic(std::string("Actor construction has no checked plan"));
    }
    const auto plan = doof::unwrap_optional(expression->resolvedConstruction);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>> args = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>>(std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>{});
    const auto& _iterable_3 = expression->args;
    for (const auto& value : *_iterable_3) {
        args->push_back(std::make_shared<::app_src_ast_::CallArgument>(std::nullopt, value, std::visit([](auto&& _obj) { return _obj->span; }, value)));
    }
    const auto inputs = std::make_shared<ConstructionInputs>(args, std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>>(std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>{}), false, expression->span, nullptr, std::string(""), false);
    const auto values = emitConstructionValues(plan, inputs, context);
    const auto name = constructionClassName(plan->owner, context);
    const auto value = ((!doof::is_null(plan->factory)) ? (((name + std::string("::constructor(")) + values) + std::string(")")) : (((name + std::string("{")) + values) + std::string("}")));
    return ((((std::string("std::make_shared<doof::Actor<") + name) + std::string(">>(")) + value) + std::string(")"));
}
std::string emitConstruct(const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if ((expression->type_ == std::string("Success")) || (expression->type_ == std::string("Failure"))) {
        const auto resultType = expression->resolvedType;
        if (doof::is_null(resultType)) {
            doof::panic((expression->type_ + std::string(" has no resolved Result type")));
        }
        {
            auto _case_subject = doof::unwrap_optional(resultType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                const auto valueType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (expression->type_ == std::string("Success")) { return result->valueType; } return result->errorType; }();
                const auto propertyName = ((expression->type_ == std::string("Success")) ? std::string("value") : std::string("error"));
                const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->args, propertyName);
                const auto payloadType = ::app_src_emitter_types_::emitContextReturnType(valueType, context);
                if (doof::is_null(property)) {
                    return ((((std::string("doof::") + expression->type_) + std::string("<")) + payloadType) + std::string(">{ }"));
                }
                const auto value = ::app_src_emitter_expr_utils_::emitPropertyValue(doof::unwrap_optional(property), context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(valueType));
                return ((((((std::string("doof::") + expression->type_) + std::string("<")) + payloadType) + std::string(">{ ")) + value) + std::string(" }"));
        }
        else {
        }
        }
        doof::panic((expression->type_ + std::string(" does not construct a Result")));
    }
    if (doof::is_null(expression->resolvedConstruction)) {
        doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has no checked plan")));
    }
    const auto plan = doof::unwrap_optional(expression->resolvedConstruction);
    if (plan->factory != expression->resolvedConstructor) {
        doof::panic(((std::string("Construction of '") + expression->type_) + std::string("' has no resolved constructor consistent with its checked plan")));
    }
    const auto spreadName = constructionSpreadTemporary(expression, context);
    const auto inputs = std::make_shared<ConstructionInputs>(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>>(std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>{}), expression->args, true, expression->span, expression, spreadName, doof::is_null(plan->factory));
    const auto result = emitPlannedConstruction(plan, inputs, context);
    return wrapConstructionSpread(expression, spreadName, result, context);
}
std::string constructionSpreadTemporary(const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expression->spread)) {
        return std::string("");
    }
    static_cast<void>((context->tryCounter = (context->tryCounter + 1)));
    return (std::string("_construct_spread_") + doof::to_string(context->tryCounter));
}
bool hasSpreadField(const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::string& name) {
    const auto& _iterable_5 = expression->spreadFields;
    for (const auto& field : *_iterable_5) {
        if (field == name) {
            return true;
        }
    }
    return false;
}
std::string emitConstructionSpreadField(const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::string& temporary, const std::string& name, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expression->resolvedSpreadType)) {
        doof::panic(std::string("Construction spread has no resolved type"));
    }
    {
        auto _case_subject = doof::unwrap_optional(expression->resolvedSpreadType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            const auto accessor = ((class_->symbol->kind == std::string("struct")) ? std::string(".") : std::string("->"));
            return ((temporary + accessor) + ::app_src_emitter_expr_::cppIdentifier(name));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            return ((((std::string("std::visit([](auto&& _obj) { return _obj->") + ::app_src_emitter_expr_::cppIdentifier(name)) + std::string("; }, ")) + temporary) + std::string(")"));
    }
    else {
            doof::panic(std::string("Construction spread has unsupported resolved type"));
    }
    }
    doof::unreachable();
}
std::string wrapConstructionSpread(const std::shared_ptr<::app_src_ast_::ConstructExpression>& expression, const std::string& temporary, const std::string& result, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expression->spread)) {
        return result;
    }
    return ((((((std::string("[&]() { const auto& ") + temporary) + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(expression->spread), context, expression->resolvedSpreadType)) + std::string("; return ")) + result) + std::string("; }()"));
}
std::string emitOwnerDefaultExpression(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected, ::app_src_ast_::SourceSpan callSiteSpan, const std::shared_ptr<::app_src_semantic_::ClassType>& owner, const std::shared_ptr<std::vector<std::string>>& ownerTypeParams) {
    const auto specializedOwner = ::app_src_emitter_types_::specializeEmitType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(owner), context);
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> ownerArguments = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    {
        auto _case_subject = specializedOwner;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            static_cast<void>((ownerArguments = class_->typeArgs));
    }
    else {
            doof::panic(std::string("Constructor owner did not remain a class after specialization"));
    }
    }
    const auto previousSubstitution = context->substitution;
    const auto names = ((static_cast<int32_t>((ownerTypeParams)->size()) == 0) ? owner->symbol->typeParams : ownerTypeParams);
    static_cast<void>((context->substitution = std::make_shared<::app_src_semantic_::TypeSubstitution>(names, ownerArguments)));
    const auto result = ::app_src_emitter_call_arguments_::emitDefaultExpression(expression, context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(expected), callSiteSpan);
    static_cast<void>((context->substitution = previousSubstitution));
    return result;
}
std::string emitClassObject(const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::ClassType>& resolved) {
    if (doof::is_null(expression->resolvedConstruction)) {
        doof::panic(std::string("Object literal has no checked construction plan"));
    }
    const auto inputs = std::make_shared<ConstructionInputs>(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>>(std::vector<std::shared_ptr<::app_src_ast_::CallArgument>>{}), expression->properties, true, expression->span, nullptr, std::string(""), false);
    return emitPlannedConstruction(doof::unwrap_optional(expression->resolvedConstruction), inputs, context);
}
std::string concreteClassName(const std::shared_ptr<::app_src_semantic_::ClassType>& class_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    const auto& _iterable_7 = class_->typeArgs;
    for (const auto& argument : *_iterable_7) {
        typeArgs->push_back(::app_src_emitter_types_::specializeEmitType(argument, context));
    }
    if (static_cast<int32_t>((typeArgs)->size()) == 0) {
        return std::string("");
    }
    const auto key = ::app_src_emitter_monomorphize_::classInstantiationKey(class_->symbol->module, class_->name, typeArgs);
    for (int32_t i = 0; i < static_cast<int32_t>((context->concreteClassKeys)->size()); ++i) {
        if (doof::array_at(context->concreteClassKeys, i, "src/emitter-construction", 179) == key) {
            const auto name = doof::array_at(context->concreteClassNames, i, "src/emitter-construction", 180);
            if ((class_->symbol->module != std::string("")) && (class_->symbol->module != context->modulePath)) {
                return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(class_->symbol->module)) + std::string("::")) + name);
            }
            return name;
        }
    }
    return std::string("");
}
std::string constructionClassName(const std::shared_ptr<::app_src_semantic_::ClassType>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto concrete = concreteClassName(owner, context);
    if (concrete != std::string("")) {
        return concrete;
    }
    if (owner->symbol->native_) {
        return (std::string("::") + ((owner->symbol->nativeCppName == std::string("")) ? owner->symbol->name : owner->symbol->nativeCppName));
    }
    if ((owner->symbol->module != std::string("")) && (owner->symbol->module != context->modulePath)) {
        return (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(owner->symbol->module)) + std::string("::")) + ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol));
    }
    return ::app_src_emitter_expr_utils_::emittedSymbolName(owner->symbol);
}
std::string emitClassAllocation(const std::string& name, bool structValue, const std::string& values) {
    return (structValue ? (((name + std::string("{")) + values) + std::string("}")) : ((((std::string("std::make_shared<") + name) + std::string(">(")) + values) + std::string(")")));
}
}
