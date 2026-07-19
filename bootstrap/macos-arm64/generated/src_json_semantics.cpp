#include "src_json_semantics.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_json_semantics_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;


std::shared_ptr<JsonDiscriminator> interfaceJsonDiscriminator(std::shared_ptr<::app_src_ast_::InterfaceDeclaration> owner, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs) {
    if (doof::is_null(owner->resolvedSymbol) || (static_cast<int32_t>((owner->resolvedSymbol->implementations)->size()) == 0)) {
        return nullptr;
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>> implementations = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>{});
    const auto& _iterable_1 = owner->resolvedSymbol->implementations;
    for (const auto& symbol : *_iterable_1) {
        const auto declaration = findJsonClassDeclaration(programs, symbol);
        if (doof::is_null(declaration) || !canGenerateJsonDeserialization(doof::unwrap_optional(declaration), programs)) {
            return nullptr;
        }
        implementations->push_back(doof::unwrap_optional(declaration));
    }
    if (static_cast<int32_t>((implementations)->size()) == 0) {
        return nullptr;
    }
    const auto& _iterable_2 = (*implementations)[0]->fields;
    for (const auto& candidate : *_iterable_2) {
        if (((candidate->static_ || !candidate->const_) || (static_cast<int32_t>((candidate->names)->size()) != 1)) || doof::is_null(candidate->defaultValue)) {
            continue;
        }
        {
            auto _case_subject = doof::unwrap_optional(candidate->defaultValue);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
                const auto& firstValue = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
                const auto discriminator = std::make_shared<JsonDiscriminator>((*candidate->names)[0], std::make_shared<std::vector<std::shared_ptr<JsonDiscriminatorEntry>>>(std::vector<std::shared_ptr<JsonDiscriminatorEntry>>{}));
                const auto& _iterable_3 = implementations;
                for (const auto& implementation : *_iterable_3) {
                    const auto matching = fixedStringField(implementation, discriminator->fieldName);
                    if (doof::is_null(matching) || discriminatorHasValue(discriminator, matching.value())) {
                        (discriminator->entries = std::make_shared<std::vector<std::shared_ptr<JsonDiscriminatorEntry>>>(std::vector<std::shared_ptr<JsonDiscriminatorEntry>>{}));
                        break;
                    }
                    discriminator->entries->push_back(std::make_shared<JsonDiscriminatorEntry>(matching.value(), implementation));
                }
                if (static_cast<int32_t>((discriminator->entries)->size()) == static_cast<int32_t>((implementations)->size())) {
                    return discriminator;
                }
        }
        else {
        }
        }
    }
    return nullptr;
}
std::optional<std::string> fixedStringField(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::string name) {
    const auto& _iterable_4 = owner->fields;
    for (const auto& field : *_iterable_4) {
        if ((field->static_ || !field->const_) || doof::is_null(field->defaultValue)) {
            continue;
        }
        auto matches = false;
        const auto& _iterable_5 = field->names;
        for (const auto& fieldName : *_iterable_5) {
            if (fieldName == name) {
                (matches = true);
            }
        }
        if (!matches) {
            continue;
        }
        {
            auto _case_subject = doof::unwrap_optional(field->defaultValue);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
                const auto& value = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
                return value->value;
        }
        else {
                return std::nullopt;
        }
        }
    }
    return std::nullopt;
}
bool discriminatorHasValue(std::shared_ptr<JsonDiscriminator> discriminator, std::string value) {
    const auto& _iterable_6 = discriminator->entries;
    for (const auto& entry : *_iterable_6) {
        if (entry->value == value) {
            return true;
        }
    }
    return false;
}
bool canGenerateJsonSerialization(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs) {
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    return canGenerateJsonSerializationInner(owner, programs, visited);
}
bool canGenerateJsonSerializationInner(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<std::vector<std::string>> visited) {
    if ((owner->native_ || (static_cast<int32_t>((owner->typeParams)->size()) > 0)) || hasDedicatedConstructor(owner)) {
        return false;
    }
    if (markJsonOwnerVisited(owner, visited)) {
        return true;
    }
    const auto& _iterable_7 = owner->fields;
    for (const auto& field : *_iterable_7) {
        if (field->static_) {
            continue;
        }
        if (!isGeneratedJsonSerializationField(field, programs, visited)) {
            return false;
        }
    }
    return true;
}
bool canGenerateJsonDeserialization(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs) {
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    return canGenerateJsonDeserializationInner(owner, programs, visited);
}
bool canGenerateJsonDeserializationInner(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<std::vector<std::string>> visited) {
    if ((owner->native_ || (static_cast<int32_t>((owner->typeParams)->size()) > 0)) || hasDedicatedConstructor(owner)) {
        return false;
    }
    if (markJsonOwnerVisited(owner, visited)) {
        return true;
    }
    const auto& _iterable_8 = owner->fields;
    for (const auto& field : *_iterable_8) {
        if (field->static_) {
            continue;
        }
        if (!isGeneratedJsonDeserializationField(field, programs, visited)) {
            return false;
        }
    }
    return true;
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> nullableJsonMember(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            return nullableJsonMemberUnchecked(union_);
    }
    else {
            return std::monostate{};
    }
    }
    return std::monostate{};
}
bool isGeneratedJsonType(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<std::vector<std::string>> visited) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NullType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if (class_->symbol->native_ || (static_cast<int32_t>((class_->typeArgs)->size()) > 0)) {
                return false;
            }
            const auto declaration = findJsonClassDeclaration(programs, class_->symbol);
            if (doof::is_null(declaration)) {
                return (static_cast<int32_t>((programs)->size()) == 0);
            }
            return canGenerateJsonDeserializationInner(doof::unwrap_optional(declaration), programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return isGeneratedJsonType(array->elementType, programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            {
                auto _case_subject = map->keyType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& key = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
                    return ((key->name == std::string("string")) && isGeneratedJsonType(map->valueType, programs, visited));
            }
            else {
                    return false;
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_9 = tuple->elements;
            for (const auto& element : *_iterable_9) {
                if (!isGeneratedJsonType(element, programs, visited)) {
                    return false;
                }
            }
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto inner = nullableJsonMemberUnchecked(union_);
            return ((!doof::is_null(inner)) && isGeneratedJsonType(doof::unwrap_optional(inner), programs, visited));
    }
    else {
            return false;
    }
    }
    return false;
}
bool isGeneratedJsonSerializationType(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<std::vector<std::string>> visited) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if (class_->symbol->native_ || (static_cast<int32_t>((class_->typeArgs)->size()) > 0)) {
                return false;
            }
            const auto declaration = findJsonClassDeclaration(programs, class_->symbol);
            if (doof::is_null(declaration)) {
                return (static_cast<int32_t>((programs)->size()) == 0);
            }
            return canGenerateJsonSerializationInner(doof::unwrap_optional(declaration), programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            if (doof::kind(array->elementType) == std::string("json-value")) {
                return true;
            }
            return isGeneratedJsonSerializationType(array->elementType, programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            {
                auto _case_subject = map->keyType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& key = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
                    return ((key->name == std::string("string")) && isGeneratedJsonSerializationType(map->valueType, programs, visited));
            }
            else {
                    return false;
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_10 = tuple->elements;
            for (const auto& element : *_iterable_10) {
                if (!isGeneratedJsonSerializationType(element, programs, visited)) {
                    return false;
                }
            }
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto inner = nullableJsonMemberUnchecked(union_);
            if (doof::is_null(inner)) {
                return false;
            }
            {
                auto _case_subject = doof::unwrap_optional(inner);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    return isGeneratedJsonSerializationType(doof::unwrap_optional(inner), programs, visited);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                    return isGeneratedJsonSerializationType(doof::unwrap_optional(inner), programs, visited);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                    return isGeneratedJsonSerializationType(doof::unwrap_optional(inner), programs, visited);
            }
            else {
                    return isGeneratedJsonType(doof::unwrap_optional(inner), programs, visited);
            }
            }
    }
    else {
    }
    }
    if (isGeneratedJsonType(type_, programs, visited)) {
        return true;
    }
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NullType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            {
                auto _case_subject = map->keyType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& key = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
                    return ((key->name == std::string("string")) && (doof::kind(map->valueType) == std::string("json-value")));
            }
            else {
                    return false;
            }
            }
    }
    else {
            return false;
    }
    }
    return false;
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> nullableJsonMemberUnchecked(std::shared_ptr<::app_src_semantic_::UnionResolvedType> union_) {
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> value = std::monostate{};
    auto nullCount = 0;
    const auto& _iterable_11 = union_->types;
    for (const auto& member : *_iterable_11) {
        {
            auto _case_subject = member;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NullType>>(_case_subject)) {
                (nullCount = (nullCount + 1));
        }
        else {
                if (!doof::is_null(value)) {
                    return std::monostate{};
                }
                (value = doof::optional_value(member));
        }
        }
    }
    if ((doof::is_null(value) || (nullCount != 1)) || (static_cast<int32_t>((union_->types)->size()) != 2)) {
        return std::monostate{};
    }
    return value;
}
bool isGeneratedJsonDeserializationField(std::shared_ptr<::app_src_ast_::ClassField> field, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<std::vector<std::string>> visited) {
    if (field->weak_) {
        return false;
    }
    if (!doof::is_null(field->resolvedType)) {
        return isGeneratedJsonType(doof::unwrap_optional(field->resolvedType), programs, visited);
    }
    if (!doof::is_null(field->type_)) {
        return isGeneratedJsonDeserializationAnnotation(doof::unwrap_optional(field->type_), programs, visited);
    }
    if (doof::is_null(field->defaultValue)) {
        return false;
    }
    {
        auto _case_subject = doof::unwrap_optional(field->defaultValue);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
            return true;
    }
    else {
            return false;
    }
    }
    return false;
}
bool isGeneratedJsonSerializationField(std::shared_ptr<::app_src_ast_::ClassField> field, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<std::vector<std::string>> visited) {
    if (field->weak_) {
        return false;
    }
    if (!doof::is_null(field->resolvedType)) {
        return isGeneratedJsonSerializationType(doof::unwrap_optional(field->resolvedType), programs, visited);
    }
    if (!doof::is_null(field->type_)) {
        return isGeneratedJsonSerializationAnnotation(doof::unwrap_optional(field->type_), programs, visited);
    }
    return isGeneratedJsonDeserializationField(field, programs, visited);
}
bool isGeneratedJsonDeserializationAnnotation(std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<std::vector<std::string>> visited) {
    if (!doof::is_null(doof::resolved_type(annotation))) {
        return isGeneratedJsonType(doof::unwrap_optional(doof::resolved_type(annotation)), programs, visited);
    }
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (((((((((named->name == std::string("byte")) || (named->name == std::string("int"))) || (named->name == std::string("long"))) || (named->name == std::string("float"))) || (named->name == std::string("double"))) || (named->name == std::string("string"))) || (named->name == std::string("char"))) || (named->name == std::string("bool"))) || (named->name == std::string("JsonValue"))) {
                return true;
            }
            if (named->name == std::string("Tuple")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) == 0) {
                    return false;
                }
                const auto& _iterable_12 = named->typeArgs;
                for (const auto& element : *_iterable_12) {
                    if (!isGeneratedJsonDeserializationAnnotation(element, programs, visited)) {
                        return false;
                    }
                }
                return true;
            }
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
                    return false;
                }
                {
                    auto _case_subject = (*named->typeArgs)[0];
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& key = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                        return ((key->name == std::string("string")) && isGeneratedJsonDeserializationAnnotation((*named->typeArgs)[1], programs, visited));
                }
                else {
                        return false;
                }
                }
            }
            if (((static_cast<int32_t>((named->typeArgs)->size()) != 0) || doof::is_null(named->resolvedSymbol)) || named->resolvedSymbol->native_) {
                return false;
            }
            if (doof::kind(named->resolvedSymbol) == std::string("enum")) {
                return true;
            }
            if ((doof::kind(named->resolvedSymbol) != std::string("class")) && (doof::kind(named->resolvedSymbol) != std::string("struct"))) {
                return false;
            }
            const auto declaration = findJsonClassDeclaration(programs, doof::unwrap_optional(named->resolvedSymbol));
            if (doof::is_null(declaration)) {
                return (static_cast<int32_t>((programs)->size()) == 0);
            }
            return canGenerateJsonDeserializationInner(doof::unwrap_optional(declaration), programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            return isGeneratedJsonDeserializationAnnotation(array->elementType, programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
            if (static_cast<int32_t>((union_->types)->size()) != 2) {
                return false;
            }
            auto hasNull = false;
            auto hasPrimitive = false;
            const auto& _iterable_13 = union_->types;
            for (const auto& member : *_iterable_13) {
                {
                    auto _case_subject = member;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                        if (named->name == std::string("null")) {
                            (hasNull = true);
                        } else if ((named->name != std::string("JsonValue")) && isGeneratedJsonDeserializationAnnotation(member, programs, visited)) {
                            (hasPrimitive = true);
                        } else {
                            return false;
                        }
                }
                else {
                        return false;
                }
                }
            }
            return (hasNull && hasPrimitive);
    }
    else {
            return false;
    }
    }
    return false;
}
bool isGeneratedJsonSerializationAnnotation(std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<std::vector<std::string>> visited) {
    if (!doof::is_null(doof::resolved_type(annotation))) {
        return isGeneratedJsonSerializationType(doof::unwrap_optional(doof::resolved_type(annotation)), programs, visited);
    }
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (named->name == std::string("Tuple")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) == 0) {
                    return false;
                }
                const auto& _iterable_14 = named->typeArgs;
                for (const auto& element : *_iterable_14) {
                    if (!isGeneratedJsonSerializationAnnotation(element, programs, visited)) {
                        return false;
                    }
                }
                return true;
            }
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
                    return false;
                }
                {
                    auto _case_subject = (*named->typeArgs)[0];
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& key = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                        return ((key->name == std::string("string")) && isGeneratedJsonSerializationAnnotation((*named->typeArgs)[1], programs, visited));
                }
                else {
                        return false;
                }
                }
            }
            if ((!doof::is_null(named->resolvedSymbol)) && ((doof::kind(named->resolvedSymbol) == std::string("class")) || (doof::kind(named->resolvedSymbol) == std::string("struct")))) {
                const auto declaration = findJsonClassDeclaration(programs, doof::unwrap_optional(named->resolvedSymbol));
                if (doof::is_null(declaration)) {
                    return (static_cast<int32_t>((programs)->size()) == 0);
                }
                return canGenerateJsonSerializationInner(doof::unwrap_optional(declaration), programs, visited);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            return isGeneratedJsonSerializationAnnotation(array->elementType, programs, visited);
    }
    else {
    }
    }
    if (isGeneratedJsonDeserializationAnnotation(annotation, programs, visited)) {
        return true;
    }
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (named->name == std::string("null")) {
                return true;
            }
            if (((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) && (static_cast<int32_t>((named->typeArgs)->size()) == 2)) {
                {
                    auto _case_subject = (*named->typeArgs)[0];
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& key = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                        {
                            auto _case_subject = (*named->typeArgs)[1];
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                                const auto& value = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                                return ((key->name == std::string("string")) && (value->name == std::string("JsonValue")));
                        }
                        else {
                                return false;
                        }
                        }
                }
                else {
                        return false;
                }
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            {
                auto _case_subject = array->elementType;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                    const auto& element = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                    return (element->name == std::string("JsonValue"));
            }
            else {
                    return false;
            }
            }
    }
    else {
            return false;
    }
    }
    return false;
}
bool markJsonOwnerVisited(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<std::vector<std::string>> visited) {
    const auto module = (doof::is_null(owner->resolvedSymbol) ? std::string("") : owner->resolvedSymbol->module);
    const auto key = ((module + std::string("::")) + owner->name);
    const auto& _iterable_15 = visited;
    for (const auto& existing : *_iterable_15) {
        if (existing == key) {
            return true;
        }
    }
    visited->push_back(key);
    return false;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> findJsonClassDeclaration(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs, std::shared_ptr<::app_src_semantic_::Symbol> symbol) {
    const auto& _iterable_16 = programs;
    for (const auto& program : *_iterable_16) {
        const auto& _iterable_17 = program->statements;
        for (const auto& statement : *_iterable_17) {
            const auto declaration = jsonClassDeclaration(statement);
            if (doof::is_null(declaration) || doof::is_null(declaration->resolvedSymbol)) {
                continue;
            }
            if ((declaration->resolvedSymbol->module == symbol->module) && (declaration->name == symbol->name)) {
                return declaration;
            }
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> jsonClassDeclaration(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return class_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return jsonClassDeclaration(export_->declaration);
    }
    else {
            return nullptr;
    }
    }
    return nullptr;
}
bool hasDedicatedConstructor(std::shared_ptr<::app_src_ast_::ClassDeclaration> owner) {
    const auto& _iterable_18 = owner->methods;
    for (const auto& method : *_iterable_18) {
        if (method->static_ && (method->name == std::string("constructor"))) {
            return true;
        }
    }
    return false;
}
}
