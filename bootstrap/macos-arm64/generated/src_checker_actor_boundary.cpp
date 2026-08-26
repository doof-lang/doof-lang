#include "src_checker_actor_boundary.hpp"

namespace app_src_checker_actor_boundary_ {
using namespace ::app_src_analyzer_;
using namespace ::app_src_semantic_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;

#line 21 "/src/checker-actor-boundary.do"
std::shared_ptr<ActorBoundaryViolation> findActorBoundaryViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 22 "/src/checker-actor-boundary.do"
    return findViolation(result, type_, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
#line 25 "/src/checker-actor-boundary.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateDeepReadonlyFields(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 26 "/src/checker-actor-boundary.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>(std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>{});
#line 27 "/src/checker-actor-boundary.do"
    const auto& _iterable_2 = result->modules;
    for (const auto& module : *_iterable_2) {
#line 28 "/src/checker-actor-boundary.do"
        const auto& _iterable_4 = module->program->statements;
        for (const auto& raw : *_iterable_4) {
#line 29 "/src/checker-actor-boundary.do"
            {
                auto _case_subject = unwrapExport(raw);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 31 "/src/checker-actor-boundary.do"
                    const auto& _iterable_6 = class_->fields;
                    for (const auto& field : *_iterable_6) {
#line 32 "/src/checker-actor-boundary.do"
                        if (!field->readonly_ || doof::is_null(field->resolvedType)) {
#line 32 "/src/checker-actor-boundary.do"
                            continue;
                        }
#line 33 "/src/checker-actor-boundary.do"
                        const auto violation = findViolation(result, doof::unwrap_optional(field->resolvedType), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 34 "/src/checker-actor-boundary.do"
                        if (doof::is_null(violation)) {
#line 34 "/src/checker-actor-boundary.do"
                            continue;
                        }
#line 35 "/src/checker-actor-boundary.do"
                        const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : doof::array_at(field->names, 0, "src/checker-actor-boundary", 35));
#line 36 "/src/checker-actor-boundary.do"
                        diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), (((((std::string("Readonly field \"") + class_->name) + std::string(".")) + name) + std::string("\" must be deeply immutable: ")) + violation->reason), semanticSpan(field->span), module->path, std::string("")));
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 45 "/src/checker-actor-boundary.do"
                    const auto& _iterable_8 = interface_->fields;
                    for (const auto& field : *_iterable_8) {
#line 46 "/src/checker-actor-boundary.do"
                        if (!field->readonly_ || doof::is_null(field->resolvedType)) {
#line 46 "/src/checker-actor-boundary.do"
                            continue;
                        }
#line 47 "/src/checker-actor-boundary.do"
                        const auto violation = findViolation(result, doof::unwrap_optional(field->resolvedType), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 48 "/src/checker-actor-boundary.do"
                        if (doof::is_null(violation)) {
#line 48 "/src/checker-actor-boundary.do"
                            continue;
                        }
#line 49 "/src/checker-actor-boundary.do"
                        diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), (((((std::string("Readonly field \"") + interface_->name) + std::string(".")) + field->name) + std::string("\" must be deeply immutable: ")) + violation->reason), semanticSpan(field->span), module->path, std::string("")));
                    }
            }
            else {
            }
            }
        }
    }
#line 61 "/src/checker-actor-boundary.do"
    return diagnostics;
}
#line 64 "/src/checker-actor-boundary.do"
std::shared_ptr<ActorBoundaryViolation> findViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::string>>& seen) {
#line 65 "/src/checker-actor-boundary.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
#line 66 "/src/checker-actor-boundary.do"
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 67 "/src/checker-actor-boundary.do"
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 68 "/src/checker-actor-boundary.do"
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnknownType>>(_case_subject)) {
#line 69 "/src/checker-actor-boundary.do"
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
#line 70 "/src/checker-actor-boundary.do"
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 71 "/src/checker-actor-boundary.do"
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
#line 72 "/src/checker-actor-boundary.do"
            return std::make_shared<ActorBoundaryViolation>(std::string("Actor<T> references cannot cross actor boundaries"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
#line 73 "/src/checker-actor-boundary.do"
            return std::make_shared<ActorBoundaryViolation>(std::string("Promise<T> values cannot cross actor boundaries"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 74 "/src/checker-actor-boundary.do"
            return findViolation(result, weak_->inner, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 76 "/src/checker-actor-boundary.do"
            if (!array->readonly_) {
#line 76 "/src/checker-actor-boundary.do"
                return std::make_shared<ActorBoundaryViolation>(((std::string("array type \"") + ::app_src_checker_types_::typeName(type_)) + std::string("\" is mutable")));
            }
#line 77 "/src/checker-actor-boundary.do"
            return findViolation(result, array->elementType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 80 "/src/checker-actor-boundary.do"
            if (!map->readonly_) {
#line 80 "/src/checker-actor-boundary.do"
                return std::make_shared<ActorBoundaryViolation>(((std::string("map type \"") + ::app_src_checker_types_::typeName(type_)) + std::string("\" is mutable")));
            }
#line 81 "/src/checker-actor-boundary.do"
            const auto keyViolation = findViolation(result, map->keyType, seen);
#line 82 "/src/checker-actor-boundary.do"
            if (!doof::is_null(keyViolation)) {
#line 82 "/src/checker-actor-boundary.do"
                return keyViolation;
            }
#line 83 "/src/checker-actor-boundary.do"
            return findViolation(result, map->valueType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 86 "/src/checker-actor-boundary.do"
            if (!set_->readonly_) {
#line 86 "/src/checker-actor-boundary.do"
                return std::make_shared<ActorBoundaryViolation>(((std::string("set type \"") + ::app_src_checker_types_::typeName(type_)) + std::string("\" is mutable")));
            }
#line 87 "/src/checker-actor-boundary.do"
            return findViolation(result, set_->elementType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 89 "/src/checker-actor-boundary.do"
            return std::make_shared<ActorBoundaryViolation>(((std::string("stream type \"") + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(stream))) + std::string("\" is mutable")));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 91 "/src/checker-actor-boundary.do"
            const auto valueViolation = findViolation(result, result_->valueType, seen);
#line 92 "/src/checker-actor-boundary.do"
            if (!doof::is_null(valueViolation)) {
#line 92 "/src/checker-actor-boundary.do"
                return valueViolation;
            }
#line 93 "/src/checker-actor-boundary.do"
            return findViolation(result, result_->errorType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 96 "/src/checker-actor-boundary.do"
            const auto& _iterable_10 = tuple->elements;
            for (const auto& element : *_iterable_10) {
#line 97 "/src/checker-actor-boundary.do"
                const auto violation = findViolation(result, element, seen);
#line 98 "/src/checker-actor-boundary.do"
                if (!doof::is_null(violation)) {
#line 98 "/src/checker-actor-boundary.do"
                    return violation;
                }
            }
#line 100 "/src/checker-actor-boundary.do"
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 103 "/src/checker-actor-boundary.do"
            const auto& _iterable_12 = union_->types;
            for (const auto& member : *_iterable_12) {
#line 104 "/src/checker-actor-boundary.do"
                const auto violation = findViolation(result, member, seen);
#line 105 "/src/checker-actor-boundary.do"
                if (!doof::is_null(violation)) {
#line 105 "/src/checker-actor-boundary.do"
                    return violation;
                }
            }
#line 107 "/src/checker-actor-boundary.do"
            return nullptr;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 110 "/src/checker-actor-boundary.do"
            const auto& _iterable_14 = function_->params;
            for (const auto& parameter : *_iterable_14) {
#line 111 "/src/checker-actor-boundary.do"
                const auto violation = findViolation(result, parameter->type_, seen);
#line 112 "/src/checker-actor-boundary.do"
                if (!doof::is_null(violation)) {
#line 113 "/src/checker-actor-boundary.do"
                    return std::make_shared<ActorBoundaryViolation>((((std::string("callback parameter \"") + parameter->name) + std::string("\" cannot cross actor boundaries: ")) + violation->reason));
                }
            }
#line 116 "/src/checker-actor-boundary.do"
            return findViolation(result, function_->returnType, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 118 "/src/checker-actor-boundary.do"
            return findClassViolation(result, class_, seen);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 119 "/src/checker-actor-boundary.do"
            return findInterfaceViolation(result, interface_, seen);
    }
    }
#line 121 "/src/checker-actor-boundary.do"
    return nullptr;
}
#line 124 "/src/checker-actor-boundary.do"
std::shared_ptr<ActorBoundaryViolation> findClassViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::ClassType>& type_, const std::shared_ptr<std::vector<std::string>>& seen) {
#line 125 "/src/checker-actor-boundary.do"
    const auto key = (((std::string("class:") + type_->symbol->module) + std::string(":")) + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(type_)));
#line 126 "/src/checker-actor-boundary.do"
    if (containsString(seen, key)) {
#line 126 "/src/checker-actor-boundary.do"
        return nullptr;
    }
#line 127 "/src/checker-actor-boundary.do"
    std::shared_ptr<std::vector<std::string>> nextSeen = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 128 "/src/checker-actor-boundary.do"
    const auto& _iterable_16 = seen;
    for (const auto& item : *_iterable_16) {
#line 128 "/src/checker-actor-boundary.do"
        nextSeen->push_back(item);
    }
#line 129 "/src/checker-actor-boundary.do"
    nextSeen->push_back(key);
#line 130 "/src/checker-actor-boundary.do"
    const auto declaration = classDeclaration(result, type_->symbol->module, type_->symbol->name);
#line 131 "/src/checker-actor-boundary.do"
    if (doof::is_null(declaration)) {
#line 131 "/src/checker-actor-boundary.do"
        return nullptr;
    }
#line 132 "/src/checker-actor-boundary.do"
    const auto& _iterable_18 = declaration->fields;
    for (const auto& field : *_iterable_18) {
#line 133 "/src/checker-actor-boundary.do"
        if (field->static_) {
#line 133 "/src/checker-actor-boundary.do"
            continue;
        }
#line 134 "/src/checker-actor-boundary.do"
        if (field->let_) {
#line 135 "/src/checker-actor-boundary.do"
            const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : doof::array_at(field->names, 0, "src/checker-actor-boundary", 135));
#line 136 "/src/checker-actor-boundary.do"
            return std::make_shared<ActorBoundaryViolation>(((std::string("field \"") + name) + std::string("\" is mutable")));
        }
#line 138 "/src/checker-actor-boundary.do"
        const auto fieldType = field->resolvedType;
#line 139 "/src/checker-actor-boundary.do"
        if (doof::is_null(fieldType)) {
#line 139 "/src/checker-actor-boundary.do"
            continue;
        }
#line 140 "/src/checker-actor-boundary.do"
        const auto effective = ::app_src_checker_types_::substituteTypeParams(doof::unwrap_optional(fieldType), declaration->typeParams, type_->typeArgs);
#line 141 "/src/checker-actor-boundary.do"
        const auto violation = findViolation(result, effective, nextSeen);
#line 142 "/src/checker-actor-boundary.do"
        if (!doof::is_null(violation)) {
#line 143 "/src/checker-actor-boundary.do"
            const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : doof::array_at(field->names, 0, "src/checker-actor-boundary", 143));
#line 144 "/src/checker-actor-boundary.do"
            return std::make_shared<ActorBoundaryViolation>((((std::string("field \"") + name) + std::string("\" cannot cross actor boundaries: ")) + violation->reason));
        }
    }
#line 147 "/src/checker-actor-boundary.do"
    return nullptr;
}
#line 150 "/src/checker-actor-boundary.do"
std::shared_ptr<ActorBoundaryViolation> findInterfaceViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::InterfaceType>& type_, const std::shared_ptr<std::vector<std::string>>& seen) {
#line 151 "/src/checker-actor-boundary.do"
    const auto key = (((std::string("interface:") + type_->symbol->module) + std::string(":")) + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(type_)));
#line 152 "/src/checker-actor-boundary.do"
    if (containsString(seen, key)) {
#line 152 "/src/checker-actor-boundary.do"
        return nullptr;
    }
#line 153 "/src/checker-actor-boundary.do"
    std::shared_ptr<std::vector<std::string>> nextSeen = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 154 "/src/checker-actor-boundary.do"
    const auto& _iterable_20 = seen;
    for (const auto& item : *_iterable_20) {
#line 154 "/src/checker-actor-boundary.do"
        nextSeen->push_back(item);
    }
#line 155 "/src/checker-actor-boundary.do"
    nextSeen->push_back(key);
#line 156 "/src/checker-actor-boundary.do"
    const auto declaration = interfaceDeclaration(result, type_->symbol->module, type_->symbol->name);
#line 157 "/src/checker-actor-boundary.do"
    if (doof::is_null(declaration)) {
#line 157 "/src/checker-actor-boundary.do"
        return nullptr;
    }
#line 158 "/src/checker-actor-boundary.do"
    const auto& _iterable_22 = declaration->fields;
    for (const auto& field : *_iterable_22) {
#line 159 "/src/checker-actor-boundary.do"
        if (field->let_) {
#line 159 "/src/checker-actor-boundary.do"
            return std::make_shared<ActorBoundaryViolation>(((std::string("field \"") + field->name) + std::string("\" is mutable")));
        }
#line 160 "/src/checker-actor-boundary.do"
        if (doof::is_null(field->resolvedType)) {
#line 160 "/src/checker-actor-boundary.do"
            continue;
        }
#line 161 "/src/checker-actor-boundary.do"
        const auto effective = ::app_src_checker_types_::substituteTypeParams(doof::unwrap_optional(field->resolvedType), declaration->typeParams, type_->typeArgs);
#line 162 "/src/checker-actor-boundary.do"
        const auto violation = findViolation(result, effective, nextSeen);
#line 163 "/src/checker-actor-boundary.do"
        if (!doof::is_null(violation)) {
#line 164 "/src/checker-actor-boundary.do"
            return std::make_shared<ActorBoundaryViolation>((((std::string("field \"") + field->name) + std::string("\" cannot cross actor boundaries: ")) + violation->reason));
        }
    }
#line 167 "/src/checker-actor-boundary.do"
    if (!doof::is_null(declaration->resolvedSymbol)) {
#line 168 "/src/checker-actor-boundary.do"
        const auto& _iterable_24 = declaration->resolvedSymbol->implementations;
        for (const auto& implementation : *_iterable_24) {
#line 169 "/src/checker-actor-boundary.do"
            const auto implementationType = ::app_src_checker_types_::classType(implementation->name, implementation, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
#line 170 "/src/checker-actor-boundary.do"
            const auto violation = findClassViolation(result, implementationType, nextSeen);
#line 171 "/src/checker-actor-boundary.do"
            if (!doof::is_null(violation)) {
#line 172 "/src/checker-actor-boundary.do"
                return std::make_shared<ActorBoundaryViolation>((((std::string("implementation \"") + implementation->name) + std::string("\" cannot cross actor boundaries: ")) + violation->reason));
            }
        }
    }
#line 178 "/src/checker-actor-boundary.do"
    return nullptr;
}
#line 181 "/src/checker-actor-boundary.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> classDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& modulePath, const std::string& name) {
#line 182 "/src/checker-actor-boundary.do"
    const auto module = findModule(result, modulePath);
#line 183 "/src/checker-actor-boundary.do"
    if (doof::is_null(module)) {
#line 183 "/src/checker-actor-boundary.do"
        return nullptr;
    }
#line 184 "/src/checker-actor-boundary.do"
    const auto& _iterable_26 = module->program->statements;
    for (const auto& statement : *_iterable_26) {
#line 185 "/src/checker-actor-boundary.do"
        {
            auto _case_subject = unwrapExport(statement);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 186 "/src/checker-actor-boundary.do"
                if (class_->name == name) {
#line 186 "/src/checker-actor-boundary.do"
                    return class_;
                }
        }
        else {
        }
        }
    }
#line 190 "/src/checker-actor-boundary.do"
    return nullptr;
}
#line 193 "/src/checker-actor-boundary.do"
std::shared_ptr<::app_src_ast_::InterfaceDeclaration> interfaceDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& modulePath, const std::string& name) {
#line 194 "/src/checker-actor-boundary.do"
    const auto module = findModule(result, modulePath);
#line 195 "/src/checker-actor-boundary.do"
    if (doof::is_null(module)) {
#line 195 "/src/checker-actor-boundary.do"
        return nullptr;
    }
#line 196 "/src/checker-actor-boundary.do"
    const auto& _iterable_28 = module->program->statements;
    for (const auto& statement : *_iterable_28) {
#line 197 "/src/checker-actor-boundary.do"
        {
            auto _case_subject = unwrapExport(statement);
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 198 "/src/checker-actor-boundary.do"
                if (interface_->name == name) {
#line 198 "/src/checker-actor-boundary.do"
                    return interface_;
                }
        }
        else {
        }
        }
    }
#line 202 "/src/checker-actor-boundary.do"
    return nullptr;
}
#line 205 "/src/checker-actor-boundary.do"
std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> unwrapExport(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 206 "/src/checker-actor-boundary.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 207 "/src/checker-actor-boundary.do"
            return export_->declaration;
    }
    else {
#line 208 "/src/checker-actor-boundary.do"
            return statement;
    }
    }
    doof::unreachable();
}
#line 212 "/src/checker-actor-boundary.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
#line 213 "/src/checker-actor-boundary.do"
    const auto& _iterable_30 = result->modules;
    for (const auto& module : *_iterable_30) {
#line 213 "/src/checker-actor-boundary.do"
        if (module->path == path) {
#line 213 "/src/checker-actor-boundary.do"
            return module;
        }
    }
#line 214 "/src/checker-actor-boundary.do"
    return nullptr;
}
#line 217 "/src/checker-actor-boundary.do"
bool containsString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 218 "/src/checker-actor-boundary.do"
    const auto& _iterable_32 = values;
    for (const auto& item : *_iterable_32) {
#line 218 "/src/checker-actor-boundary.do"
        if (item == value) {
#line 218 "/src/checker-actor-boundary.do"
            return true;
        }
    }
#line 219 "/src/checker-actor-boundary.do"
    return false;
}
#line 222 "/src/checker-actor-boundary.do"
::app_src_semantic_::SemanticSpan semanticSpan(::app_src_ast_::SourceSpan span) {
#line 223 "/src/checker-actor-boundary.do"
    return ::app_src_semantic_::SemanticSpan{::app_src_semantic_::SemanticLocation{span.start.line, span.start.column, span.start.offset}, ::app_src_semantic_::SemanticLocation{span.end.line, span.end.column, span.end.offset}};
}
#line 1 "<doof-generated>"
}
