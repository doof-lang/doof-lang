#include "src_json_semantics.hpp"

namespace app_src_json_semantics_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;



#line 31 "/src/json-semantics.do"
std::shared_ptr<JsonDiscriminator> interfaceJsonDiscriminator(const std::shared_ptr<::app_src_ast_::InterfaceDeclaration>& owner, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<JsonEligibilityCache>& cache) {
#line 36 "/src/json-semantics.do"
    if (doof::is_null(owner->resolvedSymbol) || (static_cast<int32_t>((owner->resolvedSymbol->implementations)->size()) == 0)) {
#line 36 "/src/json-semantics.do"
        return nullptr;
    }
#line 37 "/src/json-semantics.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>> implementations = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>>(std::vector<std::shared_ptr<::app_src_ast_::ClassDeclaration>>{});
#line 38 "/src/json-semantics.do"
    const auto& _iterable_2 = owner->resolvedSymbol->implementations;
    for (const auto& symbol : *_iterable_2) {
#line 39 "/src/json-semantics.do"
        const auto declaration = findJsonClassDeclaration(programs, symbol);
#line 40 "/src/json-semantics.do"
        if (doof::is_null(declaration) || !canGenerateJsonDeserialization(doof::unwrap_optional(declaration), programs, cache)) {
#line 40 "/src/json-semantics.do"
            return nullptr;
        }
#line 41 "/src/json-semantics.do"
        implementations->push_back(doof::unwrap_optional(declaration));
    }
#line 43 "/src/json-semantics.do"
    if (static_cast<int32_t>((implementations)->size()) == 0) {
#line 43 "/src/json-semantics.do"
        return nullptr;
    }
#line 44 "/src/json-semantics.do"
    const auto& _iterable_4 = doof::array_at(implementations, 0, "src/json-semantics", 44)->fields;
    for (const auto& candidate : *_iterable_4) {
#line 45 "/src/json-semantics.do"
        if (((candidate->static_ || !candidate->const_) || (static_cast<int32_t>((candidate->names)->size()) != 1)) || doof::is_null(candidate->defaultValue)) {
#line 45 "/src/json-semantics.do"
            continue;
        }
#line 46 "/src/json-semantics.do"
        {
            auto _case_subject = doof::unwrap_optional(candidate->defaultValue);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
                const auto& firstValue = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 48 "/src/json-semantics.do"
                const auto discriminator = std::make_shared<JsonDiscriminator>(doof::array_at(candidate->names, 0, "src/json-semantics", 48), std::make_shared<std::vector<std::shared_ptr<JsonDiscriminatorEntry>>>(std::vector<std::shared_ptr<JsonDiscriminatorEntry>>{}));
#line 49 "/src/json-semantics.do"
                const auto& _iterable_6 = implementations;
                for (const auto& implementation : *_iterable_6) {
#line 50 "/src/json-semantics.do"
                    const auto matching = fixedStringField(implementation, discriminator->fieldName);
#line 51 "/src/json-semantics.do"
                    if (doof::is_null(matching) || discriminatorHasValue(discriminator, matching.value())) {
#line 51 "/src/json-semantics.do"
                        (discriminator->entries = std::make_shared<std::vector<std::shared_ptr<JsonDiscriminatorEntry>>>(std::vector<std::shared_ptr<JsonDiscriminatorEntry>>{}));
#line 51 "/src/json-semantics.do"
                        break;
                    }
#line 52 "/src/json-semantics.do"
                    discriminator->entries->push_back(std::make_shared<JsonDiscriminatorEntry>(matching.value(), implementation));
                }
#line 54 "/src/json-semantics.do"
                if (static_cast<int32_t>((discriminator->entries)->size()) == static_cast<int32_t>((implementations)->size())) {
#line 54 "/src/json-semantics.do"
                    return discriminator;
                }
        }
        else {
        }
        }
    }
#line 59 "/src/json-semantics.do"
    return nullptr;
}
#line 62 "/src/json-semantics.do"
std::optional<std::string> fixedStringField(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::string& name) {
#line 63 "/src/json-semantics.do"
    const auto& _iterable_8 = owner->fields;
    for (const auto& field : *_iterable_8) {
#line 64 "/src/json-semantics.do"
        if ((field->static_ || !field->const_) || doof::is_null(field->defaultValue)) {
#line 64 "/src/json-semantics.do"
            continue;
        }
#line 65 "/src/json-semantics.do"
        auto matches = false;
#line 66 "/src/json-semantics.do"
        const auto& _iterable_10 = field->names;
        for (const auto& fieldName : *_iterable_10) {
#line 66 "/src/json-semantics.do"
            if (fieldName == name) {
#line 66 "/src/json-semantics.do"
                (matches = true);
            }
        }
#line 67 "/src/json-semantics.do"
        if (!matches) {
#line 67 "/src/json-semantics.do"
            continue;
        }
#line 68 "/src/json-semantics.do"
        {
            auto _case_subject = doof::unwrap_optional(field->defaultValue);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
                const auto& value = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 69 "/src/json-semantics.do"
                return value->value;
        }
        else {
#line 70 "/src/json-semantics.do"
                return std::nullopt;
        }
        }
        doof::unreachable();
    }
#line 73 "/src/json-semantics.do"
    return std::nullopt;
}
#line 76 "/src/json-semantics.do"
bool discriminatorHasValue(const std::shared_ptr<JsonDiscriminator>& discriminator, const std::string& value) {
#line 77 "/src/json-semantics.do"
    const auto& _iterable_12 = discriminator->entries;
    for (const auto& entry : *_iterable_12) {
#line 77 "/src/json-semantics.do"
        if (entry->value == value) {
#line 77 "/src/json-semantics.do"
            return true;
        }
    }
#line 78 "/src/json-semantics.do"
    return false;
}
#line 81 "/src/json-semantics.do"
bool canGenerateJsonSerialization(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<JsonEligibilityCache>& cache) {
#line 86 "/src/json-semantics.do"
    const auto key = jsonOwnerKey(owner);
#line 87 "/src/json-semantics.do"
    if ((!doof::is_null(cache)) && [&]() -> bool { auto _map_has_13 = cache->serialization; return _map_has_13->find(key) != _map_has_13->end(); }()) {
#line 87 "/src/json-semantics.do"
        return [&]() -> bool { auto _try_value = doof::map_get(cache->serialization, key, "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/json-semantics", 87, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    }
#line 88 "/src/json-semantics.do"
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 89 "/src/json-semantics.do"
    const auto result = canGenerateJsonSerializationInner(owner, programs, visited);
#line 90 "/src/json-semantics.do"
    if (!doof::is_null(cache)) {
#line 90 "/src/json-semantics.do"
        doof::map_set(cache->serialization, key, result, "", 0);
    }
#line 91 "/src/json-semantics.do"
    return result;
}
#line 94 "/src/json-semantics.do"
bool canGenerateJsonSerializationInner(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 95 "/src/json-semantics.do"
    if ((owner->native_ || (static_cast<int32_t>((owner->typeParams)->size()) > 0)) || hasDedicatedConstructor(owner)) {
#line 95 "/src/json-semantics.do"
        return false;
    }
#line 96 "/src/json-semantics.do"
    if (markJsonOwnerVisited(owner, visited)) {
#line 96 "/src/json-semantics.do"
        return true;
    }
#line 97 "/src/json-semantics.do"
    const auto& _iterable_15 = owner->fields;
    for (const auto& field : *_iterable_15) {
#line 98 "/src/json-semantics.do"
        if (field->static_) {
#line 98 "/src/json-semantics.do"
            continue;
        }
#line 99 "/src/json-semantics.do"
        if (!isGeneratedJsonSerializationField(field, programs, visited)) {
#line 99 "/src/json-semantics.do"
            return false;
        }
    }
#line 101 "/src/json-semantics.do"
    return true;
}
#line 104 "/src/json-semantics.do"
bool canGenerateJsonDeserialization(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<JsonEligibilityCache>& cache) {
#line 109 "/src/json-semantics.do"
    const auto key = jsonOwnerKey(owner);
#line 110 "/src/json-semantics.do"
    if ((!doof::is_null(cache)) && [&]() -> bool { auto _map_has_16 = cache->deserialization; return _map_has_16->find(key) != _map_has_16->end(); }()) {
#line 110 "/src/json-semantics.do"
        return [&]() -> bool { auto _try_value = doof::map_get(cache->deserialization, key, "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/json-semantics", 110, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
    }
#line 111 "/src/json-semantics.do"
    std::shared_ptr<std::vector<std::string>> visited = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 112 "/src/json-semantics.do"
    const auto result = canGenerateJsonDeserializationInner(owner, programs, visited);
#line 113 "/src/json-semantics.do"
    if (!doof::is_null(cache)) {
#line 113 "/src/json-semantics.do"
        doof::map_set(cache->deserialization, key, result, "", 0);
    }
#line 114 "/src/json-semantics.do"
    return result;
}
#line 117 "/src/json-semantics.do"
bool canGenerateJsonDeserializationInner(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 118 "/src/json-semantics.do"
    if ((owner->native_ || (static_cast<int32_t>((owner->typeParams)->size()) > 0)) || hasDedicatedConstructor(owner)) {
#line 118 "/src/json-semantics.do"
        return false;
    }
#line 119 "/src/json-semantics.do"
    if (markJsonOwnerVisited(owner, visited)) {
#line 119 "/src/json-semantics.do"
        return true;
    }
#line 120 "/src/json-semantics.do"
    const auto& _iterable_18 = owner->fields;
    for (const auto& field : *_iterable_18) {
#line 121 "/src/json-semantics.do"
        if (field->static_) {
#line 121 "/src/json-semantics.do"
            continue;
        }
#line 122 "/src/json-semantics.do"
        if (!isGeneratedJsonDeserializationField(field, programs, visited)) {
#line 122 "/src/json-semantics.do"
            return false;
        }
    }
#line 124 "/src/json-semantics.do"
    return true;
}
#line 127 "/src/json-semantics.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> nullableJsonMember(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 128 "/src/json-semantics.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 129 "/src/json-semantics.do"
            return nullableJsonMemberUnchecked(union_);
    }
    else {
#line 130 "/src/json-semantics.do"
            return std::monostate{};
    }
    }
    doof::unreachable();
#line 132 "/src/json-semantics.do"
    return std::monostate{};
}
#line 135 "/src/json-semantics.do"
bool isGeneratedJsonType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 136 "/src/json-semantics.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
#line 137 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 138 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 139 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 140 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 142 "/src/json-semantics.do"
            if (class_->symbol->native_ || (static_cast<int32_t>((class_->typeArgs)->size()) > 0)) {
#line 142 "/src/json-semantics.do"
                return false;
            }
#line 143 "/src/json-semantics.do"
            const auto declaration = findJsonClassDeclaration(programs, class_->symbol);
#line 144 "/src/json-semantics.do"
            if (doof::is_null(declaration)) {
#line 144 "/src/json-semantics.do"
                return (static_cast<int32_t>((programs)->size()) == 0);
            }
#line 145 "/src/json-semantics.do"
            return canGenerateJsonDeserializationInner(doof::unwrap_optional(declaration), programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 147 "/src/json-semantics.do"
            return isGeneratedJsonType(array->elementType, programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 149 "/src/json-semantics.do"
            {
                auto _case_subject = map->keyType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& key = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 150 "/src/json-semantics.do"
                    return ((key->name == std::string("string")) && isGeneratedJsonType(map->valueType, programs, visited));
            }
            else {
#line 151 "/src/json-semantics.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 155 "/src/json-semantics.do"
            const auto& _iterable_20 = tuple->elements;
            for (const auto& element : *_iterable_20) {
#line 156 "/src/json-semantics.do"
                if (!isGeneratedJsonType(element, programs, visited)) {
#line 156 "/src/json-semantics.do"
                    return false;
                }
            }
#line 158 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 161 "/src/json-semantics.do"
            const auto inner = nullableJsonMemberUnchecked(union_);
#line 162 "/src/json-semantics.do"
            return ((!doof::is_null(inner)) && isGeneratedJsonType(doof::unwrap_optional(inner), programs, visited));
    }
    else {
#line 164 "/src/json-semantics.do"
            return false;
    }
    }
    doof::unreachable();
#line 166 "/src/json-semantics.do"
    return false;
}
#line 169 "/src/json-semantics.do"
bool isGeneratedJsonSerializationType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 170 "/src/json-semantics.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 172 "/src/json-semantics.do"
            if (class_->symbol->native_ || (static_cast<int32_t>((class_->typeArgs)->size()) > 0)) {
#line 172 "/src/json-semantics.do"
                return false;
            }
#line 173 "/src/json-semantics.do"
            const auto declaration = findJsonClassDeclaration(programs, class_->symbol);
#line 174 "/src/json-semantics.do"
            if (doof::is_null(declaration)) {
#line 174 "/src/json-semantics.do"
                return (static_cast<int32_t>((programs)->size()) == 0);
            }
#line 175 "/src/json-semantics.do"
            return canGenerateJsonSerializationInner(doof::unwrap_optional(declaration), programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 178 "/src/json-semantics.do"
            if (std::visit([](auto&& _obj) { return _obj->kind; }, array->elementType) == std::string("json-value")) {
#line 178 "/src/json-semantics.do"
                return true;
            }
#line 179 "/src/json-semantics.do"
            return isGeneratedJsonSerializationType(array->elementType, programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 182 "/src/json-semantics.do"
            {
                auto _case_subject = map->keyType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& key = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 183 "/src/json-semantics.do"
                    return ((key->name == std::string("string")) && isGeneratedJsonSerializationType(map->valueType, programs, visited));
            }
            else {
#line 184 "/src/json-semantics.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 188 "/src/json-semantics.do"
            const auto& _iterable_22 = tuple->elements;
            for (const auto& element : *_iterable_22) {
#line 189 "/src/json-semantics.do"
                if (!isGeneratedJsonSerializationType(element, programs, visited)) {
#line 189 "/src/json-semantics.do"
                    return false;
                }
            }
#line 191 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 194 "/src/json-semantics.do"
            const auto inner = nullableJsonMemberUnchecked(union_);
#line 195 "/src/json-semantics.do"
            if (doof::is_null(inner)) {
#line 195 "/src/json-semantics.do"
                return false;
            }
#line 196 "/src/json-semantics.do"
            {
                auto _case_subject = doof::unwrap_optional(inner);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 197 "/src/json-semantics.do"
                    return isGeneratedJsonSerializationType(doof::unwrap_optional(inner), programs, visited);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 198 "/src/json-semantics.do"
                    return isGeneratedJsonSerializationType(doof::unwrap_optional(inner), programs, visited);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 199 "/src/json-semantics.do"
                    return isGeneratedJsonSerializationType(doof::unwrap_optional(inner), programs, visited);
            }
            else {
#line 200 "/src/json-semantics.do"
                    return isGeneratedJsonType(doof::unwrap_optional(inner), programs, visited);
            }
            }
            doof::unreachable();
    }
    else {
    }
    }
#line 205 "/src/json-semantics.do"
    if (isGeneratedJsonType(type_, programs, visited)) {
#line 205 "/src/json-semantics.do"
        return true;
    }
#line 206 "/src/json-semantics.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 207 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 209 "/src/json-semantics.do"
            {
                auto _case_subject = map->keyType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& key = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 210 "/src/json-semantics.do"
                    return ((key->name == std::string("string")) && (std::visit([](auto&& _obj) { return _obj->kind; }, map->valueType) == std::string("json-value")));
            }
            else {
#line 211 "/src/json-semantics.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 214 "/src/json-semantics.do"
            return false;
    }
    }
    doof::unreachable();
#line 216 "/src/json-semantics.do"
    return false;
}
#line 219 "/src/json-semantics.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> nullableJsonMemberUnchecked(const std::shared_ptr<::app_src_semantic_::UnionResolvedType>& union_) {
#line 220 "/src/json-semantics.do"
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> value = std::monostate{};
#line 221 "/src/json-semantics.do"
    auto nullCount = 0;
#line 222 "/src/json-semantics.do"
    const auto& _iterable_24 = union_->types;
    for (const auto& member : *_iterable_24) {
#line 223 "/src/json-semantics.do"
        {
            auto _case_subject = member;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 224 "/src/json-semantics.do"
                (nullCount = (nullCount + 1));
        }
        else {
#line 226 "/src/json-semantics.do"
                if (!doof::is_null(value)) {
#line 226 "/src/json-semantics.do"
                    return std::monostate{};
                }
#line 227 "/src/json-semantics.do"
                (value = doof::optional_value(member));
        }
        }
    }
#line 231 "/src/json-semantics.do"
    if ((doof::is_null(value) || (nullCount != 1)) || (static_cast<int32_t>((union_->types)->size()) != 2)) {
#line 231 "/src/json-semantics.do"
        return std::monostate{};
    }
#line 232 "/src/json-semantics.do"
    return value;
}
#line 238 "/src/json-semantics.do"
bool isGeneratedJsonDeserializationField(const std::shared_ptr<::app_src_ast_::ClassField>& field, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 239 "/src/json-semantics.do"
    if (field->weak_) {
#line 239 "/src/json-semantics.do"
        return false;
    }
#line 240 "/src/json-semantics.do"
    if (!doof::is_null(field->resolvedType)) {
#line 240 "/src/json-semantics.do"
        return isGeneratedJsonType(doof::unwrap_optional(field->resolvedType), programs, visited);
    }
#line 241 "/src/json-semantics.do"
    if (!doof::is_null(field->type_)) {
#line 241 "/src/json-semantics.do"
        return isGeneratedJsonDeserializationAnnotation(doof::unwrap_optional(field->type_), programs, visited);
    }
#line 242 "/src/json-semantics.do"
    if (doof::is_null(field->defaultValue)) {
#line 242 "/src/json-semantics.do"
        return false;
    }
#line 243 "/src/json-semantics.do"
    {
        auto _case_subject = doof::unwrap_optional(field->defaultValue);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IntLiteral>>(_case_subject)) {
#line 244 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LongLiteral>>(_case_subject)) {
#line 245 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FloatLiteral>>(_case_subject)) {
#line 246 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DoubleLiteral>>(_case_subject)) {
#line 247 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
#line 248 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CharLiteral>>(_case_subject)) {
#line 249 "/src/json-semantics.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BoolLiteral>>(_case_subject)) {
#line 250 "/src/json-semantics.do"
            return true;
    }
    else {
#line 251 "/src/json-semantics.do"
            return false;
    }
    }
    doof::unreachable();
#line 253 "/src/json-semantics.do"
    return false;
}
#line 256 "/src/json-semantics.do"
bool isGeneratedJsonSerializationField(const std::shared_ptr<::app_src_ast_::ClassField>& field, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 257 "/src/json-semantics.do"
    if (field->weak_) {
#line 257 "/src/json-semantics.do"
        return false;
    }
#line 258 "/src/json-semantics.do"
    if (!doof::is_null(field->resolvedType)) {
#line 258 "/src/json-semantics.do"
        return isGeneratedJsonSerializationType(doof::unwrap_optional(field->resolvedType), programs, visited);
    }
#line 259 "/src/json-semantics.do"
    if (!doof::is_null(field->type_)) {
#line 259 "/src/json-semantics.do"
        return isGeneratedJsonSerializationAnnotation(doof::unwrap_optional(field->type_), programs, visited);
    }
#line 260 "/src/json-semantics.do"
    return isGeneratedJsonDeserializationField(field, programs, visited);
}
#line 263 "/src/json-semantics.do"
bool isGeneratedJsonDeserializationAnnotation(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 264 "/src/json-semantics.do"
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, annotation))) {
#line 264 "/src/json-semantics.do"
        return isGeneratedJsonType(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, annotation)), programs, visited);
    }
#line 265 "/src/json-semantics.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 267 "/src/json-semantics.do"
            if (((((((((named->name == std::string("byte")) || (named->name == std::string("int"))) || (named->name == std::string("long"))) || (named->name == std::string("float"))) || (named->name == std::string("double"))) || (named->name == std::string("string"))) || (named->name == std::string("char"))) || (named->name == std::string("bool"))) || (named->name == std::string("JsonValue"))) {
#line 269 "/src/json-semantics.do"
                return true;
            }
#line 270 "/src/json-semantics.do"
            if (named->name == std::string("Tuple")) {
#line 271 "/src/json-semantics.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) == 0) {
#line 271 "/src/json-semantics.do"
                    return false;
                }
#line 272 "/src/json-semantics.do"
                const auto& _iterable_26 = named->typeArgs;
                for (const auto& element : *_iterable_26) {
#line 273 "/src/json-semantics.do"
                    if (!isGeneratedJsonDeserializationAnnotation(element, programs, visited)) {
#line 273 "/src/json-semantics.do"
                        return false;
                    }
                }
#line 275 "/src/json-semantics.do"
                return true;
            }
#line 277 "/src/json-semantics.do"
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
#line 278 "/src/json-semantics.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
#line 278 "/src/json-semantics.do"
                    return false;
                }
#line 279 "/src/json-semantics.do"
                {
                    auto _case_subject = doof::array_at(named->typeArgs, 0, "src/json-semantics", 279);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& key = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 280 "/src/json-semantics.do"
                        return ((key->name == std::string("string")) && isGeneratedJsonDeserializationAnnotation(doof::array_at(named->typeArgs, 1, "src/json-semantics", 280), programs, visited));
                }
                else {
#line 281 "/src/json-semantics.do"
                        return false;
                }
                }
                doof::unreachable();
            }
#line 284 "/src/json-semantics.do"
            if (((static_cast<int32_t>((named->typeArgs)->size()) != 0) || doof::is_null(named->resolvedSymbol)) || named->resolvedSymbol->native_) {
#line 284 "/src/json-semantics.do"
                return false;
            }
#line 285 "/src/json-semantics.do"
            if (named->resolvedSymbol->kind == std::string("enum")) {
#line 285 "/src/json-semantics.do"
                return true;
            }
#line 286 "/src/json-semantics.do"
            if ((named->resolvedSymbol->kind != std::string("class")) && (named->resolvedSymbol->kind != std::string("struct"))) {
#line 286 "/src/json-semantics.do"
                return false;
            }
#line 287 "/src/json-semantics.do"
            const auto declaration = findJsonClassDeclaration(programs, doof::unwrap_optional(named->resolvedSymbol));
#line 288 "/src/json-semantics.do"
            if (doof::is_null(declaration)) {
#line 288 "/src/json-semantics.do"
                return (static_cast<int32_t>((programs)->size()) == 0);
            }
#line 289 "/src/json-semantics.do"
            return canGenerateJsonDeserializationInner(doof::unwrap_optional(declaration), programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
#line 292 "/src/json-semantics.do"
            return isGeneratedJsonDeserializationAnnotation(array->elementType, programs, visited);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
#line 295 "/src/json-semantics.do"
            if (static_cast<int32_t>((union_->types)->size()) != 2) {
#line 295 "/src/json-semantics.do"
                return false;
            }
#line 296 "/src/json-semantics.do"
            auto hasNull = false;
#line 297 "/src/json-semantics.do"
            auto hasPrimitive = false;
#line 298 "/src/json-semantics.do"
            const auto& _iterable_28 = union_->types;
            for (const auto& member : *_iterable_28) {
#line 299 "/src/json-semantics.do"
                {
                    auto _case_subject = member;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 301 "/src/json-semantics.do"
                        if (named->name == std::string("null")) {
#line 301 "/src/json-semantics.do"
                            (hasNull = true);
                        } else if ((named->name != std::string("JsonValue")) && isGeneratedJsonDeserializationAnnotation(member, programs, visited)) {
#line 302 "/src/json-semantics.do"
                            (hasPrimitive = true);
                        } else {
#line 303 "/src/json-semantics.do"
                            return false;
                        }
                }
                else {
#line 305 "/src/json-semantics.do"
                        return false;
                }
                }
            }
#line 308 "/src/json-semantics.do"
            return (hasNull && hasPrimitive);
    }
    else {
#line 310 "/src/json-semantics.do"
            return false;
    }
    }
    doof::unreachable();
#line 312 "/src/json-semantics.do"
    return false;
}
#line 315 "/src/json-semantics.do"
bool isGeneratedJsonSerializationAnnotation(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 316 "/src/json-semantics.do"
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, annotation))) {
#line 316 "/src/json-semantics.do"
        return isGeneratedJsonSerializationType(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, annotation)), programs, visited);
    }
#line 317 "/src/json-semantics.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 319 "/src/json-semantics.do"
            if (named->name == std::string("Tuple")) {
#line 320 "/src/json-semantics.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) == 0) {
#line 320 "/src/json-semantics.do"
                    return false;
                }
#line 321 "/src/json-semantics.do"
                const auto& _iterable_30 = named->typeArgs;
                for (const auto& element : *_iterable_30) {
#line 322 "/src/json-semantics.do"
                    if (!isGeneratedJsonSerializationAnnotation(element, programs, visited)) {
#line 322 "/src/json-semantics.do"
                        return false;
                    }
                }
#line 324 "/src/json-semantics.do"
                return true;
            }
#line 326 "/src/json-semantics.do"
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
#line 327 "/src/json-semantics.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
#line 327 "/src/json-semantics.do"
                    return false;
                }
#line 328 "/src/json-semantics.do"
                {
                    auto _case_subject = doof::array_at(named->typeArgs, 0, "src/json-semantics", 328);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& key = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 329 "/src/json-semantics.do"
                        return ((key->name == std::string("string")) && isGeneratedJsonSerializationAnnotation(doof::array_at(named->typeArgs, 1, "src/json-semantics", 329), programs, visited));
                }
                else {
#line 330 "/src/json-semantics.do"
                        return false;
                }
                }
                doof::unreachable();
            }
#line 333 "/src/json-semantics.do"
            if ((!doof::is_null(named->resolvedSymbol)) && ((named->resolvedSymbol->kind == std::string("class")) || (named->resolvedSymbol->kind == std::string("struct")))) {
#line 334 "/src/json-semantics.do"
                const auto declaration = findJsonClassDeclaration(programs, doof::unwrap_optional(named->resolvedSymbol));
#line 335 "/src/json-semantics.do"
                if (doof::is_null(declaration)) {
#line 335 "/src/json-semantics.do"
                    return (static_cast<int32_t>((programs)->size()) == 0);
                }
#line 336 "/src/json-semantics.do"
                return canGenerateJsonSerializationInner(doof::unwrap_optional(declaration), programs, visited);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
#line 340 "/src/json-semantics.do"
            return isGeneratedJsonSerializationAnnotation(array->elementType, programs, visited);
    }
    else {
    }
    }
#line 344 "/src/json-semantics.do"
    if (isGeneratedJsonDeserializationAnnotation(annotation, programs, visited)) {
#line 344 "/src/json-semantics.do"
        return true;
    }
#line 345 "/src/json-semantics.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 347 "/src/json-semantics.do"
            if (named->name == std::string("null")) {
#line 347 "/src/json-semantics.do"
                return true;
            }
#line 348 "/src/json-semantics.do"
            if (((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) && (static_cast<int32_t>((named->typeArgs)->size()) == 2)) {
#line 349 "/src/json-semantics.do"
                {
                    auto _case_subject = doof::array_at(named->typeArgs, 0, "src/json-semantics", 349);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                        const auto& key = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 351 "/src/json-semantics.do"
                        {
                            auto _case_subject = doof::array_at(named->typeArgs, 1, "src/json-semantics", 351);
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                                const auto& value = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 352 "/src/json-semantics.do"
                                return ((key->name == std::string("string")) && (value->name == std::string("JsonValue")));
                        }
                        else {
#line 353 "/src/json-semantics.do"
                                return false;
                        }
                        }
                        doof::unreachable();
                }
                else {
#line 356 "/src/json-semantics.do"
                        return false;
                }
                }
                doof::unreachable();
            }
#line 359 "/src/json-semantics.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
#line 362 "/src/json-semantics.do"
            {
                auto _case_subject = array->elementType;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                    const auto& element = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 363 "/src/json-semantics.do"
                    return (element->name == std::string("JsonValue"));
            }
            else {
#line 364 "/src/json-semantics.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 367 "/src/json-semantics.do"
            return false;
    }
    }
    doof::unreachable();
#line 369 "/src/json-semantics.do"
    return false;
}
#line 372 "/src/json-semantics.do"
bool markJsonOwnerVisited(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<std::vector<std::string>>& visited) {
#line 373 "/src/json-semantics.do"
    const auto key = jsonOwnerKey(owner);
#line 374 "/src/json-semantics.do"
    const auto& _iterable_32 = visited;
    for (const auto& existing : *_iterable_32) {
#line 374 "/src/json-semantics.do"
        if (existing == key) {
#line 374 "/src/json-semantics.do"
            return true;
        }
    }
#line 375 "/src/json-semantics.do"
    visited->push_back(key);
#line 376 "/src/json-semantics.do"
    return false;
}
#line 379 "/src/json-semantics.do"
std::string jsonOwnerKey(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner) {
#line 380 "/src/json-semantics.do"
    const auto module = (doof::is_null(owner->resolvedSymbol) ? std::string("") : owner->resolvedSymbol->module);
#line 381 "/src/json-semantics.do"
    return ((module + std::string("::")) + owner->name);
}
#line 384 "/src/json-semantics.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> findJsonClassDeclaration(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 385 "/src/json-semantics.do"
    const auto& _iterable_34 = programs;
    for (const auto& program : *_iterable_34) {
#line 386 "/src/json-semantics.do"
        const auto& _iterable_36 = program->statements;
        for (const auto& statement : *_iterable_36) {
#line 387 "/src/json-semantics.do"
            const auto declaration = jsonClassDeclaration(statement);
#line 388 "/src/json-semantics.do"
            if (doof::is_null(declaration) || doof::is_null(declaration->resolvedSymbol)) {
#line 388 "/src/json-semantics.do"
                continue;
            }
#line 389 "/src/json-semantics.do"
            if ((declaration->resolvedSymbol->module == symbol->module) && (declaration->name == symbol->name)) {
#line 389 "/src/json-semantics.do"
                return declaration;
            }
        }
    }
#line 392 "/src/json-semantics.do"
    return nullptr;
}
#line 395 "/src/json-semantics.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> jsonClassDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 396 "/src/json-semantics.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 397 "/src/json-semantics.do"
            return class_;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 398 "/src/json-semantics.do"
            return jsonClassDeclaration(export_->declaration);
    }
    else {
#line 399 "/src/json-semantics.do"
            return nullptr;
    }
    }
    doof::unreachable();
#line 401 "/src/json-semantics.do"
    return nullptr;
}
#line 404 "/src/json-semantics.do"
bool hasDedicatedConstructor(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner) {
#line 405 "/src/json-semantics.do"
    const auto& _iterable_38 = owner->methods;
    for (const auto& method : *_iterable_38) {
#line 406 "/src/json-semantics.do"
        if (method->static_ && (method->name == std::string("constructor"))) {
#line 406 "/src/json-semantics.do"
            return true;
        }
    }
#line 408 "/src/json-semantics.do"
    return false;
}
#line 1 "<doof-generated>"
}
