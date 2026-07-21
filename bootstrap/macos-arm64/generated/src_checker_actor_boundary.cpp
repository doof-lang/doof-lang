#include "src_checker_actor_boundary.hpp"
#include <cmath>
#include "src_analyzer.hpp"
#include "src_semantic.hpp"
#include "src_ast.hpp"
#include "src_checker_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_checker_actor_boundary_ {
using namespace ::app_src_analyzer_;
using namespace ::app_src_semantic_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;

doof::JsonObject ActorBoundaryViolation::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["reason"] = doof::json_value(this->reason);
    return _json;
}
doof::Result<std::shared_ptr<ActorBoundaryViolation>, std::string> ActorBoundaryViolation::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_reason = _object->find("reason");
    if (_iterator_reason == _object->end()) { return doof::Failure<std::string>{"Missing required field \"reason\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_reason->second) : doof::json_is_string(_iterator_reason->second)))) { return doof::Failure<std::string>{"Field \"reason\" expected string but got " + std::string(doof::json_type_name(_iterator_reason->second))}; }
    auto _field_reason = (_lenient ? doof::json_as_string_lenient(_iterator_reason->second) : doof::json_as_string(_iterator_reason->second));
    return doof::Success<std::shared_ptr<ActorBoundaryViolation>>{std::make_shared<ActorBoundaryViolation>(_field_reason)};
}
std::shared_ptr<ActorBoundaryViolation> findActorBoundaryViolation(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    return findViolation(result, type_, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
std::shared_ptr<ActorBoundaryViolation> findViolation(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<std::vector<std::string>> seen) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            return std::make_shared<ActorBoundaryViolation>(std::string("Actor<T> references cannot cross actor boundaries"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            return std::make_shared<ActorBoundaryViolation>(std::string("Promise<T> values cannot cross actor boundaries"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            return findViolation(result, weak_->inner, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            if (!array->readonly_) {
                return std::make_shared<ActorBoundaryViolation>(((std::string("array type \"") + ::app_src_checker_types_::typeName(type_)) + std::string("\" is mutable")));
            }
            return findViolation(result, array->elementType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            if (!map->readonly_) {
                return std::make_shared<ActorBoundaryViolation>(((std::string("map type \"") + ::app_src_checker_types_::typeName(type_)) + std::string("\" is mutable")));
            }
            const auto keyViolation = findViolation(result, map->keyType, seen);
            if (!doof::is_null(keyViolation)) {
                return keyViolation;
            }
            return findViolation(result, map->valueType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            if (!set_->readonly_) {
                return std::make_shared<ActorBoundaryViolation>(((std::string("set type \"") + ::app_src_checker_types_::typeName(type_)) + std::string("\" is mutable")));
            }
            return findViolation(result, set_->elementType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            return std::make_shared<ActorBoundaryViolation>(((std::string("stream type \"") + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(stream))) + std::string("\" is mutable")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            const auto valueViolation = findViolation(result, result_->valueType, seen);
            if (!doof::is_null(valueViolation)) {
                return valueViolation;
            }
            return findViolation(result, result_->errorType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_1 = tuple->elements;
            for (const auto& element : *_iterable_1) {
                const auto violation = findViolation(result, element, seen);
                if (!doof::is_null(violation)) {
                    return violation;
                }
            }
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_2 = union_->types;
            for (const auto& member : *_iterable_2) {
                const auto violation = findViolation(result, member, seen);
                if (!doof::is_null(violation)) {
                    return violation;
                }
            }
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_3 = function_->params;
            for (const auto& parameter : *_iterable_3) {
                const auto violation = findViolation(result, parameter->type_, seen);
                if (!doof::is_null(violation)) {
                    return std::make_shared<ActorBoundaryViolation>((((std::string("callback parameter \"") + parameter->name) + std::string("\" cannot cross actor boundaries: ")) + violation->reason));
                }
            }
            return findViolation(result, function_->returnType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            return findClassViolation(result, class_, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            return findInterfaceViolation(result, interface_, seen);
    }
    }
    return nullptr;
}
std::shared_ptr<ActorBoundaryViolation> findClassViolation(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::shared_ptr<::app_src_semantic_::ClassType> type_, std::shared_ptr<std::vector<std::string>> seen) {
    const auto key = (((std::string("class:") + type_->symbol->module) + std::string(":")) + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(type_)));
    if (containsString(seen, key)) {
        return nullptr;
    }
    std::shared_ptr<std::vector<std::string>> nextSeen = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_4 = seen;
    for (const auto& item : *_iterable_4) {
        nextSeen->push_back(item);
    }
    nextSeen->push_back(key);
    const auto declaration = classDeclaration(result, type_->symbol->module, type_->symbol->name);
    if (doof::is_null(declaration)) {
        return nullptr;
    }
    const auto& _iterable_5 = declaration->fields;
    for (const auto& field : *_iterable_5) {
        if (!field->readonly_) {
            const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : (*field->names)[0]);
            return std::make_shared<ActorBoundaryViolation>(((std::string("field \"") + name) + std::string("\" is mutable")));
        }
        const auto fieldType = field->resolvedType;
        if (doof::is_null(fieldType)) {
            continue;
        }
        const auto effective = ::app_src_checker_types_::substituteTypeParams(doof::unwrap_optional(fieldType), declaration->typeParams, type_->typeArgs);
        const auto violation = findViolation(result, effective, nextSeen);
        if (!doof::is_null(violation)) {
            const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : (*field->names)[0]);
            return std::make_shared<ActorBoundaryViolation>((((std::string("field \"") + name) + std::string("\" cannot cross actor boundaries: ")) + violation->reason));
        }
    }
    return nullptr;
}
std::shared_ptr<ActorBoundaryViolation> findInterfaceViolation(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::shared_ptr<::app_src_semantic_::InterfaceType> type_, std::shared_ptr<std::vector<std::string>> seen) {
    const auto key = (((std::string("interface:") + type_->symbol->module) + std::string(":")) + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(type_)));
    if (containsString(seen, key)) {
        return nullptr;
    }
    std::shared_ptr<std::vector<std::string>> nextSeen = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_6 = seen;
    for (const auto& item : *_iterable_6) {
        nextSeen->push_back(item);
    }
    nextSeen->push_back(key);
    const auto declaration = interfaceDeclaration(result, type_->symbol->module, type_->symbol->name);
    if (doof::is_null(declaration)) {
        return nullptr;
    }
    const auto& _iterable_7 = declaration->fields;
    for (const auto& field : *_iterable_7) {
        if (!field->readonly_) {
            return std::make_shared<ActorBoundaryViolation>(((std::string("field \"") + field->name) + std::string("\" is mutable")));
        }
        if (doof::is_null(field->resolvedType)) {
            continue;
        }
        const auto effective = ::app_src_checker_types_::substituteTypeParams(doof::unwrap_optional(field->resolvedType), declaration->typeParams, type_->typeArgs);
        const auto violation = findViolation(result, effective, nextSeen);
        if (!doof::is_null(violation)) {
            return std::make_shared<ActorBoundaryViolation>((((std::string("field \"") + field->name) + std::string("\" cannot cross actor boundaries: ")) + violation->reason));
        }
    }
    if (!doof::is_null(declaration->resolvedSymbol)) {
        const auto& _iterable_8 = declaration->resolvedSymbol->implementations;
        for (const auto& implementation : *_iterable_8) {
            const auto implementationType = ::app_src_checker_types_::classType(implementation->name, implementation, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
            const auto violation = findClassViolation(result, implementationType, nextSeen);
            if (!doof::is_null(violation)) {
                return std::make_shared<ActorBoundaryViolation>((((std::string("implementation \"") + implementation->name) + std::string("\" cannot cross actor boundaries: ")) + violation->reason));
            }
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> classDeclaration(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string modulePath, std::string name) {
    const auto module = findModule(result, modulePath);
    if (doof::is_null(module)) {
        return nullptr;
    }
    const auto& _iterable_9 = module->program->statements;
    for (const auto& statement : *_iterable_9) {
        {
            auto _case_subject = unwrapExport(statement);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                if (class_->name == name) {
                    return class_;
                }
        }
        else {
        }
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::InterfaceDeclaration> interfaceDeclaration(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string modulePath, std::string name) {
    const auto module = findModule(result, modulePath);
    if (doof::is_null(module)) {
        return nullptr;
    }
    const auto& _iterable_10 = module->program->statements;
    for (const auto& statement : *_iterable_10) {
        {
            auto _case_subject = unwrapExport(statement);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                if (interface_->name == name) {
                    return interface_;
                }
        }
        else {
        }
        }
    }
    return nullptr;
}
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> unwrapExport(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return export_->declaration;
    }
    else {
            return statement;
    }
    }
}
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path) {
    const auto& _iterable_11 = result->modules;
    for (const auto& module : *_iterable_11) {
        if (module->path == path) {
            return module;
        }
    }
    return nullptr;
}
bool containsString(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    const auto& _iterable_12 = values;
    for (const auto& item : *_iterable_12) {
        if (item == value) {
            return true;
        }
    }
    return false;
}
}
