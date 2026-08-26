#include "src_emitter_expr.hpp"

namespace app_src_emitter_expr_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_ops_;
using namespace ::app_src_emitter_expr_calls_;
using namespace ::app_src_emitter_expr_literals_;
using namespace ::app_src_emitter_expr_control_;
using namespace ::app_src_emitter_expr_lambda_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_emitter_expr_actor_;
using namespace ::app_src_emitter_names_;
#line 20 "/src/emitter-expr.do"
std::string emitExpression(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 21 "/src/emitter-expr.do"
    auto value = std::string("");
#line 22 "/src/emitter-expr.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            const auto& int_ = std::get<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject);
#line 23 "/src/emitter-expr.do"
            (value = doof::to_string(int_->value));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
            const auto& long_ = std::get<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject);
#line 24 "/src/emitter-expr.do"
            (value = (doof::to_string(long_->value) + std::string("LL")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
            const auto& float_ = std::get<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject);
#line 25 "/src/emitter-expr.do"
            (value = (decimalLiteral(((float_->raw == std::string("")) ? doof::to_string(float_->value) : float_->raw)) + std::string("f")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
            const auto& double_ = std::get<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject);
#line 26 "/src/emitter-expr.do"
            (value = decimalLiteral(((double_->raw == std::string("")) ? doof::to_string(double_->value) : double_->raw)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 27 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_literals_::emitString(string_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
            const auto& char_ = std::get<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject);
#line 28 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_literals_::emitChar(char_->value));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
            const auto& bool_ = std::get<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject);
#line 29 "/src/emitter-expr.do"
            (value = (bool_->value ? std::string("true") : std::string("false")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject)) {
            const auto& none_ = std::get<std::shared_ptr<::app_src_ast_::NoneLiteral>>(_case_subject);
#line 30 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_literals_::emitNoneLiteral(expected, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallerExpression>>(_case_subject)) {
            const auto& caller = std::get<std::shared_ptr<::app_src_ast_::CallerExpression>>(_case_subject);
#line 32 "/src/emitter-expr.do"
            const auto functionName = ((context->currentFunctionName == std::string("")) ? std::string("<module>") : context->currentFunctionName);
#line 33 "/src/emitter-expr.do"
            auto span = (doof::is_null(context->sourceLocationSpanOverride) ? caller->span : context->sourceLocationSpanOverride->span);
#line 34 "/src/emitter-expr.do"
            const auto fileName = ::app_src_emitter_names_::moduleDiagnosticPath(context->modulePath, true);
#line 35 "/src/emitter-expr.do"
            (value = ((((((std::string("std::make_shared<doof::SourceLocation>(std::string(\"") + fileName) + std::string("\"), ")) + doof::to_string(span.start.line)) + std::string(", std::string(\"")) + functionName) + std::string("\"))")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 37 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_ops_::emitIdentifier(identifier, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 38 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_ops_::emitBinary(binary, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 39 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_ops_::emitUnary(unary, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject)) {
            const auto& as_ = std::get<std::shared_ptr<::app_src_ast_::AsExpression>>(_case_subject);
#line 40 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_ops_::emitAs(as_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject);
#line 41 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_ops_::emitAssignment(assignment, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 42 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_ops_::emitMember(member, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
#line 43 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_ops_::emitIndex(index, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 44 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_calls_::emitCall(call, context, expected));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 45 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_literals_::emitArray(array, context, expected));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 46 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_literals_::emitObject(object, context, expected));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
#line 47 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_literals_::emitTuple(tuple, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
#line 48 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_lambda_::emitLambdaExpression(lambda, context, expected));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
#line 49 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_control_::emitIfExpression(if_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
#line 50 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_control_::emitCaseExpression(case_, context, expected));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
#line 51 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_control_::emitYieldBlockExpression(yieldBlock, context, expected));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
#line 52 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_control_::emitCatchExpression(catch_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
#line 53 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_calls_::emitConstruct(construct, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
#line 54 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_actor_::emitAsyncExpression(async_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
#line 55 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_actor_::emitRetireActor(retire_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
#line 56 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_actor_::emitActorCreation(actor, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject)) {
            const auto& dot = std::get<std::shared_ptr<::app_src_ast_::DotShorthand>>(_case_subject);
#line 57 "/src/emitter-expr.do"
            (value = ::app_src_emitter_expr_control_::emitDotShorthand(dot, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
            const auto& this_ = std::get<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject);
#line 59 "/src/emitter-expr.do"
            auto structThis = false;
#line 60 "/src/emitter-expr.do"
            if (!doof::is_null(this_->resolvedType)) {
#line 61 "/src/emitter-expr.do"
                {
                    auto _case_subject = doof::unwrap_optional(this_->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 62 "/src/emitter-expr.do"
                        (structThis = (class_->symbol->kind == std::string("struct")));
                }
                else {
                }
                }
            }
#line 66 "/src/emitter-expr.do"
            if (structThis) {
#line 66 "/src/emitter-expr.do"
                (value = std::string("*this"));
            } else if (context->currentClassNative) {
#line 67 "/src/emitter-expr.do"
                (value = std::string("this->shared_from_this()"));
            } else {
#line 68 "/src/emitter-expr.do"
                (value = std::string("this->shared_from_this()"));
            }
    }
    else {
#line 70 "/src/emitter-expr.do"
            doof::panic((std::string("Unsupported expression in initial C++ emitter: ") + std::visit([](auto&& _obj) { return _obj->kind; }, expression)));
    }
    }
#line 72 "/src/emitter-expr.do"
    const auto sourceType = ::app_src_emitter_expr_utils_::decoratedExpressionType(expression);
#line 73 "/src/emitter-expr.do"
    (value = emitJsonValuePromotion(expression, value, sourceType, expected));
#line 74 "/src/emitter-expr.do"
    if (::app_src_emitter_expr_utils_::needsNullableVariantPromotion(sourceType, expected)) {
#line 75 "/src/emitter-expr.do"
        return ::app_src_emitter_expr_utils_::emitNullableVariantPromotion(value, sourceType, expected, context->modulePath);
    }
#line 77 "/src/emitter-expr.do"
    if (::app_src_emitter_expr_utils_::needsVariantPromotion(sourceType, expected)) {
#line 78 "/src/emitter-expr.do"
        return ((((std::string("doof::variant_promote<") + ::app_src_emitter_types_::emitType(doof::unwrap_optional(expected), context->modulePath)) + std::string(">(")) + value) + std::string(")"));
    }
#line 80 "/src/emitter-expr.do"
    return value;
}
#line 86 "/src/emitter-expr.do"
std::string emitJsonValuePromotion(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::string& value, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& source, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 87 "/src/emitter-expr.do"
    if (doof::is_null(source) || doof::is_null(expected)) {
#line 87 "/src/emitter-expr.do"
        return value;
    }
#line 88 "/src/emitter-expr.do"
    {
        auto _case_subject = doof::unwrap_optional(expected);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
    }
    else {
#line 90 "/src/emitter-expr.do"
            return value;
    }
    }
#line 92 "/src/emitter-expr.do"
    {
        auto _case_subject = doof::unwrap_optional(source);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 93 "/src/emitter-expr.do"
            return value;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 94 "/src/emitter-expr.do"
            return value;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 96 "/src/emitter-expr.do"
            if ((primitive->name == std::string("byte")) || (primitive->name == std::string("char"))) {
#line 96 "/src/emitter-expr.do"
                return ((std::string("doof::json_value(static_cast<int32_t>(") + value) + std::string("))"));
            }
    }
    else {
    }
    }
#line 100 "/src/emitter-expr.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
#line 101 "/src/emitter-expr.do"
            return value;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
#line 102 "/src/emitter-expr.do"
            return value;
    }
    else {
    }
    }
#line 105 "/src/emitter-expr.do"
    return ((std::string("doof::json_value(") + value) + std::string(")"));
}
#line 108 "/src/emitter-expr.do"
std::string cppIdentifier(const std::string& name) {
#line 108 "/src/emitter-expr.do"
    return ::app_src_emitter_expr_ops_::cppIdentifier(name);
}
#line 110 "/src/emitter-expr.do"
std::string decimalLiteral(const std::string& value) {
#line 111 "/src/emitter-expr.do"
    if ((doof::string_contains(value, std::string(".")) || doof::string_contains(value, std::string("e"))) || doof::string_contains(value, std::string("E"))) {
#line 111 "/src/emitter-expr.do"
        return value;
    }
#line 112 "/src/emitter-expr.do"
    return (value + std::string(".0"));
}
#line 1 "<doof-generated>"
}
