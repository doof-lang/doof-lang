#include "src_checker_generics.hpp"

namespace app_src_checker_generics_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_interfaces_;
#line 41 "/src/checker-generics.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferTypeArgument(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& pattern, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& actual, const std::string& name) {
#line 42 "/src/checker-generics.do"
    {
        auto _case_subject = pattern;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
#line 43 "/src/checker-generics.do"
            if (parameter->name == name) {
#line 43 "/src/checker-generics.do"
                return doof::optional_value(actual);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 45 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 46 "/src/checker-generics.do"
                    return inferTypeArgument(array->elementType, concrete->elementType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 51 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 53 "/src/checker-generics.do"
                    const auto key = inferTypeArgument(map->keyType, concrete->keyType, name);
#line 54 "/src/checker-generics.do"
                    if (!doof::is_null(key)) {
#line 54 "/src/checker-generics.do"
                        return key;
                    }
#line 55 "/src/checker-generics.do"
                    return inferTypeArgument(map->valueType, concrete->valueType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 61 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 62 "/src/checker-generics.do"
                    return inferTypeArgument(set_->elementType, concrete->elementType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 67 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 68 "/src/checker-generics.do"
                    return inferTypeArgument(stream->elementType, concrete->elementType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 73 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 75 "/src/checker-generics.do"
                    if ((class_->symbol->module != concrete->symbol->module) || (class_->symbol->name != concrete->symbol->name)) {
#line 75 "/src/checker-generics.do"
                        return std::monostate{};
                    }
#line 76 "/src/checker-generics.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((class_->typeArgs)->size()); ++i) {
#line 77 "/src/checker-generics.do"
                        if (i < static_cast<int32_t>((concrete->typeArgs)->size())) {
#line 78 "/src/checker-generics.do"
                            const auto candidate = inferTypeArgument(doof::array_at(class_->typeArgs, i, "src/checker-generics", 78), doof::array_at(concrete->typeArgs, i, "src/checker-generics", 78), name);
#line 79 "/src/checker-generics.do"
                            if (!doof::is_null(candidate)) {
#line 79 "/src/checker-generics.do"
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
#line 87 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 89 "/src/checker-generics.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((interface_->typeArgs)->size()); ++i) {
#line 90 "/src/checker-generics.do"
                        if (i < static_cast<int32_t>((concrete->typeArgs)->size())) {
#line 91 "/src/checker-generics.do"
                            const auto candidate = inferTypeArgument(doof::array_at(interface_->typeArgs, i, "src/checker-generics", 91), doof::array_at(concrete->typeArgs, i, "src/checker-generics", 91), name);
#line 92 "/src/checker-generics.do"
                            if (!doof::is_null(candidate)) {
#line 92 "/src/checker-generics.do"
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
#line 100 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 102 "/src/checker-generics.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((function_->params)->size()); ++i) {
#line 103 "/src/checker-generics.do"
                        if (i < static_cast<int32_t>((concrete->params)->size())) {
#line 104 "/src/checker-generics.do"
                            const auto candidate = inferTypeArgument(doof::array_at(function_->params, i, "src/checker-generics", 104)->type_, doof::array_at(concrete->params, i, "src/checker-generics", 104)->type_, name);
#line 105 "/src/checker-generics.do"
                            if (!doof::is_null(candidate)) {
#line 105 "/src/checker-generics.do"
                                return candidate;
                            }
                        }
                    }
#line 108 "/src/checker-generics.do"
                    return inferTypeArgument(function_->returnType, concrete->returnType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 114 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 116 "/src/checker-generics.do"
                    const auto value = inferTypeArgument(result_->valueType, concrete->valueType, name);
#line 117 "/src/checker-generics.do"
                    if (!doof::is_null(value)) {
#line 117 "/src/checker-generics.do"
                        return value;
                    }
#line 118 "/src/checker-generics.do"
                    return inferTypeArgument(result_->errorType, concrete->errorType, name);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 124 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 126 "/src/checker-generics.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
#line 127 "/src/checker-generics.do"
                        if (i < static_cast<int32_t>((concrete->elements)->size())) {
#line 128 "/src/checker-generics.do"
                            const auto candidate = inferTypeArgument(doof::array_at(tuple->elements, i, "src/checker-generics", 128), doof::array_at(concrete->elements, i, "src/checker-generics", 128), name);
#line 129 "/src/checker-generics.do"
                            if (!doof::is_null(candidate)) {
#line 129 "/src/checker-generics.do"
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
#line 137 "/src/checker-generics.do"
            {
                auto _case_subject = actual;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                    const auto& concrete = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 138 "/src/checker-generics.do"
                    return inferTypeArgument(weak_->inner, concrete->inner, name);
            }
            else {
            }
            }
    }
    else {
    }
    }
#line 144 "/src/checker-generics.do"
    return std::monostate{};
}
#line 147 "/src/checker-generics.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> functionDeclarationForCallee(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& callee, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& calleeType, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 148 "/src/checker-generics.do"
    {
        auto _case_subject = callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 150 "/src/checker-generics.do"
            if ((!doof::is_null(identifier->resolvedBinding)) && (!doof::is_null(identifier->resolvedBinding->symbol))) {
#line 151 "/src/checker-generics.do"
                const auto symbol = doof::unwrap_optional(identifier->resolvedBinding->symbol);
#line 152 "/src/checker-generics.do"
                const auto declaration = ::app_src_checker_symbols_::declarationFor(result, symbol);
#line 153 "/src/checker-generics.do"
                if (!doof::is_null(declaration)) {
#line 154 "/src/checker-generics.do"
                    {
                        auto _case_subject = doof::unwrap_optional(declaration);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
                            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 155 "/src/checker-generics.do"
                            return fn;
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 157 "/src/checker-generics.do"
                            auto method = ::app_src_checker_interfaces_::findClassMethod(class_->methods, identifier->name, false);
#line 158 "/src/checker-generics.do"
                            if (!doof::is_null(method)) {
#line 158 "/src/checker-generics.do"
                                return method;
                            }
#line 159 "/src/checker-generics.do"
                            (method = ::app_src_checker_interfaces_::findClassMethod(class_->methods, identifier->name, true));
#line 160 "/src/checker-generics.do"
                            if (!doof::is_null(method)) {
#line 160 "/src/checker-generics.do"
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
#line 168 "/src/checker-generics.do"
            const auto objectType = std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object);
#line 169 "/src/checker-generics.do"
            if (!doof::is_null(objectType)) {
#line 170 "/src/checker-generics.do"
                {
                    auto _case_subject = doof::unwrap_optional(objectType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 172 "/src/checker-generics.do"
                        const auto declaration = ::app_src_checker_symbols_::declarationFor(result, class_->symbol);
#line 173 "/src/checker-generics.do"
                        if (!doof::is_null(declaration)) {
#line 174 "/src/checker-generics.do"
                            {
                                auto _case_subject = doof::unwrap_optional(declaration);
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 176 "/src/checker-generics.do"
                                    auto method = ::app_src_checker_interfaces_::findClassMethod(classDeclaration->methods, member->property, false);
#line 177 "/src/checker-generics.do"
                                    if (!doof::is_null(method)) {
#line 177 "/src/checker-generics.do"
                                        return method;
                                    }
#line 178 "/src/checker-generics.do"
                                    (method = ::app_src_checker_interfaces_::findClassMethod(classDeclaration->methods, member->property, true));
#line 179 "/src/checker-generics.do"
                                    if (!doof::is_null(method)) {
#line 179 "/src/checker-generics.do"
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
#line 186 "/src/checker-generics.do"
                        const auto declaration = ::app_src_checker_symbols_::declarationFor(result, actor->innerClass->symbol);
#line 187 "/src/checker-generics.do"
                        if (!doof::is_null(declaration)) {
#line 188 "/src/checker-generics.do"
                            {
                                auto _case_subject = doof::unwrap_optional(declaration);
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 190 "/src/checker-generics.do"
                                    const auto method = ::app_src_checker_interfaces_::findClassMethod(classDeclaration->methods, member->property, false);
#line 191 "/src/checker-generics.do"
                                    if (!doof::is_null(method)) {
#line 191 "/src/checker-generics.do"
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
#line 198 "/src/checker-generics.do"
                        const auto declaration = ::app_src_checker_symbols_::declarationFor(result, interface_->symbol);
#line 199 "/src/checker-generics.do"
                        if (!doof::is_null(declaration)) {
#line 200 "/src/checker-generics.do"
                            {
                                auto _case_subject = doof::unwrap_optional(declaration);
                                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                                    const auto& interfaceDeclaration = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 202 "/src/checker-generics.do"
                                    const auto& _iterable_6 = interfaceDeclaration->methods;
                                    for (const auto& method : *_iterable_6) {
#line 202 "/src/checker-generics.do"
                                        if (method->name == member->property) {
#line 202 "/src/checker-generics.do"
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
#line 214 "/src/checker-generics.do"
    return nullptr;
}
#line 217 "/src/checker-generics.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> constructorForClass(const std::shared_ptr<::app_src_semantic_::ClassType>& class_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 218 "/src/checker-generics.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(result, class_->symbol);
#line 219 "/src/checker-generics.do"
    if (doof::is_null(declaration)) {
#line 219 "/src/checker-generics.do"
        return nullptr;
    }
#line 220 "/src/checker-generics.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 222 "/src/checker-generics.do"
            const auto& _iterable_8 = classDeclaration->methods;
            for (const auto& method : *_iterable_8) {
#line 222 "/src/checker-generics.do"
                if (method->name == std::string("constructor")) {
#line 222 "/src/checker-generics.do"
                    return method;
                }
            }
    }
    else {
    }
    }
#line 226 "/src/checker-generics.do"
    return nullptr;
}
#line 229 "/src/checker-generics.do"
bool insideConstructorFactory(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::ClassType>& class_) {
#line 230 "/src/checker-generics.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 231 "/src/checker-generics.do"
    while (!doof::is_null(current)) {
#line 232 "/src/checker-generics.do"
        if (current->functionName != std::string("")) {
#line 233 "/src/checker-generics.do"
            if (current->functionName != std::string("constructor")) {
#line 233 "/src/checker-generics.do"
                return false;
            }
#line 234 "/src/checker-generics.do"
            if (doof::is_null(current->thisType)) {
#line 234 "/src/checker-generics.do"
                return false;
            }
#line 235 "/src/checker-generics.do"
            {
                auto _case_subject = doof::unwrap_optional(current->thisType);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& owner = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 236 "/src/checker-generics.do"
                    return ((owner->symbol->module == class_->symbol->module) && (owner->symbol->name == class_->symbol->name));
            }
            else {
#line 237 "/src/checker-generics.do"
                    return false;
            }
            }
            doof::unreachable();
        }
#line 240 "/src/checker-generics.do"
        (current = current->parent);
    }
#line 242 "/src/checker-generics.do"
    return false;
}
#line 245 "/src/checker-generics.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> staticMemberOwner(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& objectType, const std::string& property, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 246 "/src/checker-generics.do"
    {
        auto _case_subject = objectType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 248 "/src/checker-generics.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(result, class_->symbol);
#line 249 "/src/checker-generics.do"
            if (!doof::is_null(declaration)) {
#line 250 "/src/checker-generics.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 252 "/src/checker-generics.do"
                        if ((property == std::string("metadata")) && classDeclaration->needsMetadata) {
#line 252 "/src/checker-generics.do"
                            return classDeclaration;
                        }
#line 253 "/src/checker-generics.do"
                        if ((property == std::string("fromJsonValue")) && ::app_src_json_semantics_::canGenerateJsonDeserialization(classDeclaration, jsonPrograms(result), nullptr)) {
#line 253 "/src/checker-generics.do"
                            return classDeclaration;
                        }
#line 254 "/src/checker-generics.do"
                        const auto& _iterable_10 = classDeclaration->methods;
                        for (const auto& method : *_iterable_10) {
#line 254 "/src/checker-generics.do"
                            if ((method->name == property) && method->static_) {
#line 254 "/src/checker-generics.do"
                                return classDeclaration;
                            }
                        }
#line 255 "/src/checker-generics.do"
                        const auto& _iterable_12 = classDeclaration->fields;
                        for (const auto& field : *_iterable_12) {
#line 256 "/src/checker-generics.do"
                            const auto& _iterable_14 = field->names;
                            for (const auto& name : *_iterable_14) {
#line 256 "/src/checker-generics.do"
                                if ((name == property) && field->static_) {
#line 256 "/src/checker-generics.do"
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
#line 265 "/src/checker-generics.do"
    return nullptr;
}
#line 268 "/src/checker-generics.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> jsonPrograms(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 269 "/src/checker-generics.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
#line 270 "/src/checker-generics.do"
    const auto& _iterable_16 = result->modules;
    for (const auto& module : *_iterable_16) {
#line 270 "/src/checker-generics.do"
        programs->push_back(module->program);
    }
#line 271 "/src/checker-generics.do"
    return programs;
}
#line 1 "<doof-generated>"
}
