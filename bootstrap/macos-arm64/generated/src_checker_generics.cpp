#include "src_checker_generics.hpp"

namespace app_src_checker_generics_ {
using namespace ::app_src_semantic_;
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> inferTypeArgument(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& pattern, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& actual, const std::string& name) {
    {
        auto _case_subject = pattern;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
            if (parameter->name == name) {
                return doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actual);
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
                            const auto candidate = inferTypeArgument(doof::array_at(class_->typeArgs, i, "src/checker-generics", 42), doof::array_at(concrete->typeArgs, i, "src/checker-generics", 42), name);
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
                            const auto candidate = inferTypeArgument(doof::array_at(interface_->typeArgs, i, "src/checker-generics", 55), doof::array_at(concrete->typeArgs, i, "src/checker-generics", 55), name);
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
                            const auto candidate = inferTypeArgument(doof::array_at(function_->params, i, "src/checker-generics", 68)->type_, doof::array_at(concrete->params, i, "src/checker-generics", 68)->type_, name);
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
                            const auto candidate = inferTypeArgument(doof::array_at(tuple->elements, i, "src/checker-generics", 92), doof::array_at(concrete->elements, i, "src/checker-generics", 92), name);
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
}
