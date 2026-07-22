#include "src_checker_generics.hpp"
#include <cmath>
#include "src_semantic.hpp"
#include "src_analyzer.hpp"
#include "src_ast.hpp"
#include "src_checker_types.hpp"
#include "src_json_semantics.hpp"
#include "src_checker_actor_boundary.hpp"
#include "src_checker_actor_lifecycle.hpp"
#include "src_checker_symbols.hpp"
#include "src_checker_interfaces.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_checker_generics_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_interfaces_;
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferTypeArgument(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> pattern, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> actual, std::string name) {
    {
        auto _case_subject = pattern;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
            if (parameter->name == name) {
                return doof::optional_value(actual);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
                    return inferTypeArgument(array->elementType, concrete->elementType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
                    const auto key = inferTypeArgument(map->keyType, concrete->keyType, name);
                    if (!doof::is_null(key)) {
                        return key;
                    }
                    return inferTypeArgument(map->valueType, concrete->valueType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
                    return inferTypeArgument(set_->elementType, concrete->elementType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
                    return inferTypeArgument(stream->elementType, concrete->elementType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                    if ((class_->symbol->module != concrete->symbol->module) || (class_->symbol->name != concrete->symbol->name)) {
                        return std::monostate{};
                    }
                    for (int32_t i = 0; i < static_cast<int32_t>((class_->typeArgs)->size()); ++i) {
                        if (i < static_cast<int32_t>((concrete->typeArgs)->size())) {
                            const auto candidate = inferTypeArgument((*class_->typeArgs)[i], (*concrete->typeArgs)[i], name);
                            if (!doof::is_null(candidate)) {
                                return candidate;
                            }
                        }
                    }
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
                    for (int32_t i = 0; i < static_cast<int32_t>((interface_->typeArgs)->size()); ++i) {
                        if (i < static_cast<int32_t>((concrete->typeArgs)->size())) {
                            const auto candidate = inferTypeArgument((*interface_->typeArgs)[i], (*concrete->typeArgs)[i], name);
                            if (!doof::is_null(candidate)) {
                                return candidate;
                            }
                        }
                    }
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                    for (int32_t i = 0; i < static_cast<int32_t>((function_->params)->size()); ++i) {
                        if (i < static_cast<int32_t>((concrete->params)->size())) {
                            const auto candidate = inferTypeArgument((*function_->params)[i]->type_, (*concrete->params)[i]->type_, name);
                            if (!doof::is_null(candidate)) {
                                return candidate;
                            }
                        }
                    }
                    return inferTypeArgument(function_->returnType, concrete->returnType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                    const auto value = inferTypeArgument(result_->valueType, concrete->valueType, name);
                    if (!doof::is_null(value)) {
                        return value;
                    }
                    return inferTypeArgument(result_->errorType, concrete->errorType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
                    for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
                        if (i < static_cast<int32_t>((concrete->elements)->size())) {
                            const auto candidate = inferTypeArgument((*tuple->elements)[i], (*concrete->elements)[i], name);
                            if (!doof::is_null(candidate)) {
                                return candidate;
                            }
                        }
                    }
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
                    return inferTypeArgument(weak_->inner, concrete->inner, name);
            }
            else {
            }
            }
    }
    else {
    }
    }
    return std::monostate{};
}
std::shared_ptr<::app_src_ast_::FunctionDeclaration> functionDeclarationForCallee(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> callee, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> calleeType, std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    {
        auto _case_subject = callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if ((!doof::is_null(identifier->resolvedBinding)) && (!doof::is_null(identifier->resolvedBinding->symbol))) {
                const auto symbol = doof::unwrap_optional(identifier->resolvedBinding->symbol);
                const auto declaration = ::app_src_checker_symbols_::declarationFor(result, symbol);
                if (!doof::is_null(declaration)) {
                    {
                        auto _case_subject = doof::unwrap_optional(declaration);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
                            return fn;
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                            auto method = ::app_src_checker_interfaces_::findClassMethod(class_->methods, identifier->name, false);
                            if (!doof::is_null(method)) {
                                return method;
                            }
                            (method = ::app_src_checker_interfaces_::findClassMethod(class_->methods, identifier->name, true));
                            if (!doof::is_null(method)) {
                                return method;
                            }
                    }
                    else {
                    }
                    }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            const auto objectType = std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object);
            if (!doof::is_null(objectType)) {
                {
                    auto _case_subject = doof::unwrap_optional(objectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                        const auto declaration = ::app_src_checker_symbols_::declarationFor(result, class_->symbol);
                        if (!doof::is_null(declaration)) {
                            {
                                auto _case_subject = doof::unwrap_optional(declaration);
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                                    auto method = ::app_src_checker_interfaces_::findClassMethod(classDeclaration->methods, member->property, false);
                                    if (!doof::is_null(method)) {
                                        return method;
                                    }
                                    (method = ::app_src_checker_interfaces_::findClassMethod(classDeclaration->methods, member->property, true));
                                    if (!doof::is_null(method)) {
                                        return method;
                                    }
                            }
                            else {
                            }
                            }
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
                        const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
                        const auto declaration = ::app_src_checker_symbols_::declarationFor(result, actor->innerClass->symbol);
                        if (!doof::is_null(declaration)) {
                            {
                                auto _case_subject = doof::unwrap_optional(declaration);
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                                    const auto method = ::app_src_checker_interfaces_::findClassMethod(classDeclaration->methods, member->property, false);
                                    if (!doof::is_null(method)) {
                                        return method;
                                    }
                            }
                            else {
                            }
                            }
                        }
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                        const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
                        const auto declaration = ::app_src_checker_symbols_::declarationFor(result, interface_->symbol);
                        if (!doof::is_null(declaration)) {
                            {
                                auto _case_subject = doof::unwrap_optional(declaration);
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                                    const auto& interfaceDeclaration = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                                    const auto& _iterable_1 = interfaceDeclaration->methods;
                                    for (const auto& method : *_iterable_1) {
                                        if (method->name == member->property) {
                                            return method;
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
    else {
    }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::FunctionDeclaration> constructorForClass(std::shared_ptr<::app_src_semantic_::ClassType> class_, std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    const auto declaration = ::app_src_checker_symbols_::declarationFor(result, class_->symbol);
    if (doof::is_null(declaration)) {
        return nullptr;
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            const auto& _iterable_2 = classDeclaration->methods;
            for (const auto& method : *_iterable_2) {
                if (method->name == std::string("constructor")) {
                    return method;
                }
            }
    }
    else {
    }
    }
    return nullptr;
}
bool insideConstructorFactory(std::shared_ptr<::app_src_semantic_::Scope> scope, std::shared_ptr<::app_src_semantic_::ClassType> class_) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        if (current->functionName != std::string("")) {
            if (current->functionName != std::string("constructor")) {
                return false;
            }
            if (doof::is_null(current->thisType)) {
                return false;
            }
            {
                auto _case_subject = doof::unwrap_optional(current->thisType);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& owner = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                    return ((owner->symbol->module == class_->symbol->module) && (owner->symbol->name == class_->symbol->name));
            }
            else {
                    return false;
            }
            }
        }
        (current = current->parent);
    }
    return false;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> staticMemberOwner(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> objectType, std::string property, std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    {
        auto _case_subject = objectType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            const auto declaration = ::app_src_checker_symbols_::declarationFor(result, class_->symbol);
            if (!doof::is_null(declaration)) {
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                        if ((property == std::string("metadata")) && classDeclaration->needsMetadata) {
                            return classDeclaration;
                        }
                        if ((property == std::string("fromJsonValue")) && ::app_src_json_semantics_::canGenerateJsonDeserialization(classDeclaration, jsonPrograms(result))) {
                            return classDeclaration;
                        }
                        const auto& _iterable_3 = classDeclaration->methods;
                        for (const auto& method : *_iterable_3) {
                            if ((method->name == property) && method->static_) {
                                return classDeclaration;
                            }
                        }
                        const auto& _iterable_4 = classDeclaration->fields;
                        for (const auto& field : *_iterable_4) {
                            const auto& _iterable_5 = field->names;
                            for (const auto& name : *_iterable_5) {
                                if ((name == property) && field->static_) {
                                    return classDeclaration;
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
    return nullptr;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> jsonPrograms(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
    const auto& _iterable_6 = result->modules;
    for (const auto& module : *_iterable_6) {
        programs->push_back(module->program);
    }
    return programs;
}
}
