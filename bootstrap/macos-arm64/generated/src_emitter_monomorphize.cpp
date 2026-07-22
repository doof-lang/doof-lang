#include "src_emitter_monomorphize.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_analyzer.hpp"
#include "src_checker_types.hpp"
#include "src_semantic.hpp"
#include "src_emitter_names.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_monomorphize_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_names_;




doof::JsonObject ImplementationRef::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["modulePath"] = doof::json_value(this->modulePath);
    (*_json)["typeName"] = doof::json_value(this->typeName);
    return _json;
}
doof::Result<std::shared_ptr<ImplementationRef>, std::string> ImplementationRef::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_modulePath = _object->find("modulePath");
    if (_iterator_modulePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"modulePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_modulePath->second) : doof::json_is_string(_iterator_modulePath->second)))) { return doof::Failure<std::string>{"Field \"modulePath\" expected string but got " + std::string(doof::json_type_name(_iterator_modulePath->second))}; }
    auto _field_modulePath = (_lenient ? doof::json_as_string_lenient(_iterator_modulePath->second) : doof::json_as_string(_iterator_modulePath->second));
    auto _iterator_typeName = _object->find("typeName");
    if (_iterator_typeName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"typeName\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_typeName->second) : doof::json_is_string(_iterator_typeName->second)))) { return doof::Failure<std::string>{"Field \"typeName\" expected string but got " + std::string(doof::json_type_name(_iterator_typeName->second))}; }
    auto _field_typeName = (_lenient ? doof::json_as_string_lenient(_iterator_typeName->second) : doof::json_as_string(_iterator_typeName->second));
    return doof::Success<std::shared_ptr<ImplementationRef>>{std::make_shared<ImplementationRef>(_field_modulePath, _field_typeName)};
}


std::shared_ptr<InstantiationPlan> buildInstantiationPlan(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    const auto plan = std::make_shared<InstantiationPlan>(std::make_shared<std::vector<std::shared_ptr<FunctionInstantiation>>>(std::vector<std::shared_ptr<FunctionInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<ClassInstantiation>>>(std::vector<std::shared_ptr<ClassInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<InterfaceInstantiation>>>(std::vector<std::shared_ptr<InterfaceInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<MethodInstantiation>>>(std::vector<std::shared_ptr<MethodInstantiation>>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    discoverNativeTemplateClasses(result, plan);
    const auto& _iterable_1 = result->modules;
    for (const auto& module : *_iterable_1) {
        const auto& _iterable_2 = module->program->statements;
        for (const auto& statement : *_iterable_2) {
            collectStatement(statement, module->path, result, plan, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
        }
    }
    auto functionIndex = 0;
    auto classIndex = 0;
    auto methodIndex = 0;
    while (((functionIndex < static_cast<int32_t>((plan->functions)->size())) || (classIndex < static_cast<int32_t>((plan->classes)->size()))) || (methodIndex < static_cast<int32_t>((plan->methods)->size()))) {
        if (((static_cast<int32_t>((plan->functions)->size()) + static_cast<int32_t>((plan->classes)->size())) + static_cast<int32_t>((plan->methods)->size())) > 256) {
            (plan->overflow = true);
            const auto& _iterable_3 = plan->currentTrace;
            for (const auto& item : *_iterable_3) {
                plan->overflowTrace->push_back(item);
            }
            return plan;
        }
        if (functionIndex < static_cast<int32_t>((plan->functions)->size())) {
            const auto instantiation = (*plan->functions)[functionIndex];
            (functionIndex = (functionIndex + 1));
            (plan->currentTrace = instantiation->trace);
            collectFunctionBody(instantiation->declaration, instantiation->modulePath, result, plan, instantiation->substitution->names, instantiation->substitution->arguments);
        }
        if (classIndex < static_cast<int32_t>((plan->classes)->size())) {
            const auto instantiation = (*plan->classes)[classIndex];
            (classIndex = (classIndex + 1));
            (plan->currentTrace = instantiation->trace);
            collectClassBody(instantiation->declaration, instantiation->modulePath, result, plan, instantiation->substitution->names, instantiation->substitution->arguments);
        }
        if (methodIndex < static_cast<int32_t>((plan->methods)->size())) {
            const auto instantiation = (*plan->methods)[methodIndex];
            (methodIndex = (methodIndex + 1));
            (plan->currentTrace = instantiation->trace);
            collectFunctionBody(instantiation->declaration, instantiation->modulePath, result, plan, instantiation->substitution->names, instantiation->substitution->arguments);
        }
    }
    discoverConcreteInterfaceImplementations(result, plan);
    return plan;
}
std::string functionInstantiationKey(std::string modulePath, std::string name, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs) {
    return ((((modulePath + std::string("::function::")) + name) + std::string("::")) + concreteTypeListKey(typeArgs));
}
std::string classInstantiationKey(std::string modulePath, std::string name, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs) {
    return ((((modulePath + std::string("::class::")) + name) + std::string("::")) + concreteTypeListKey(typeArgs));
}
std::string interfaceInstantiationKey(std::string modulePath, std::string name, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs) {
    return ((((modulePath + std::string("::interface::")) + name) + std::string("::")) + concreteTypeListKey(typeArgs));
}
std::string methodInstantiationKey(std::string ownerKey, std::string name, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs) {
    return ((((ownerKey + std::string("::method::")) + name) + std::string("::")) + concreteTypeListKey(typeArgs));
}
std::string concreteName(std::string name, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs) {
    auto result = name;
    const auto& _iterable_4 = typeArgs;
    for (const auto& argument : *_iterable_4) {
        (result = ((result + std::string("__")) + mangleType(argument)));
    }
    return result;
}
std::string findConcreteFunctionName(std::shared_ptr<InstantiationPlan> plan, std::string key) {
    const auto& _iterable_5 = plan->functions;
    for (const auto& instantiation : *_iterable_5) {
        if (instantiation->key == key) {
            return instantiation->emittedName;
        }
    }
    return std::string("");
}
std::string findConcreteClassName(std::shared_ptr<InstantiationPlan> plan, std::string key) {
    const auto& _iterable_6 = plan->classes;
    for (const auto& instantiation : *_iterable_6) {
        if (instantiation->key == key) {
            return instantiation->emittedName;
        }
    }
    return std::string("");
}
void collectFunctionBody(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string modulePath, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments) {
    const auto& _iterable_7 = fn->params;
    for (const auto& parameter : *_iterable_7) {
        if (!doof::is_null(parameter->resolvedType)) {
            collectType(specialize(doof::unwrap_optional(parameter->resolvedType), names, arguments), analysis, plan);
        }
        if (!doof::is_null(parameter->defaultValue)) {
            collectExpression(doof::unwrap_optional(parameter->defaultValue), modulePath, analysis, plan, names, arguments);
        }
    }
    if (!doof::is_null(fn->resolvedType)) {
        collectType(specialize(doof::unwrap_optional(fn->resolvedType), names, arguments), analysis, plan);
    }
    {
        auto _case_subject = fn->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            const auto& _iterable_8 = block->statements;
            for (const auto& statement : *_iterable_8) {
                collectStatement(statement, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
            collectExpression(expression, modulePath, analysis, plan, names, arguments);
    }
    }
}
void collectClassBody(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, std::string modulePath, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments) {
    const auto& _iterable_9 = class_->fields;
    for (const auto& field : *_iterable_9) {
        if (!doof::is_null(field->resolvedType)) {
            collectType(specialize(doof::unwrap_optional(field->resolvedType), names, arguments), analysis, plan);
        }
        if (!doof::is_null(field->defaultValue)) {
            collectExpression(doof::unwrap_optional(field->defaultValue), modulePath, analysis, plan, names, arguments);
        }
    }
    const auto& _iterable_10 = class_->methods;
    for (const auto& method : *_iterable_10) {
        if (static_cast<int32_t>((method->typeParams)->size()) == 0) {
            collectFunctionBody(method, modulePath, analysis, plan, names, arguments);
        }
    }
    if (!doof::is_null(class_->destructor_)) {
        collectBlock(doof::unwrap_optional(class_->destructor_), modulePath, analysis, plan, names, arguments);
    }
}
void collectStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::string modulePath, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            collectOptionalType(const_->resolvedType, names, arguments, analysis, plan);
            collectExpression(const_->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            collectOptionalType(readonly_->resolvedType, names, arguments, analysis, plan);
            collectExpression(readonly_->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            collectOptionalType(binding->resolvedType, names, arguments, analysis, plan);
            collectExpression(binding->value, modulePath, analysis, plan, names, arguments);
            if (!doof::is_null(binding->else_)) {
                collectBlock(doof::unwrap_optional(binding->else_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            collectOptionalType(let_->resolvedType, names, arguments, analysis, plan);
            collectExpression(let_->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            if (static_cast<int32_t>((fn->typeParams)->size()) == 0) {
                collectFunctionBody(fn, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
                collectClassBody(class_, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
            collectExpression(if_->condition, modulePath, analysis, plan, names, arguments);
            collectBlock(if_->body, modulePath, analysis, plan, names, arguments);
            const auto& _iterable_11 = if_->elseIfs;
            for (const auto& branch : *_iterable_11) {
                collectExpression(branch->condition, modulePath, analysis, plan, names, arguments);
                collectBlock(branch->body, modulePath, analysis, plan, names, arguments);
            }
            if (!doof::is_null(if_->else_)) {
                collectBlock(doof::unwrap_optional(if_->else_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
            collectExpression(case_->subject, modulePath, analysis, plan, names, arguments);
            const auto& _iterable_12 = case_->arms;
            for (const auto& arm : *_iterable_12) {
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                        collectBlock(block, modulePath, analysis, plan, names, arguments);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                        collectExpression(expression, modulePath, analysis, plan, names, arguments);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
            collectExpression(while_->condition, modulePath, analysis, plan, names, arguments);
            collectBlock(while_->body, modulePath, analysis, plan, names, arguments);
            if (!doof::is_null(while_->then_)) {
                collectBlock(doof::unwrap_optional(while_->then_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
            if (!doof::is_null(for_->init)) {
                collectStatement(doof::unwrap_optional(for_->init), modulePath, analysis, plan, names, arguments);
            }
            if (!doof::is_null(for_->condition)) {
                collectExpression(doof::unwrap_optional(for_->condition), modulePath, analysis, plan, names, arguments);
            }
            const auto& _iterable_13 = for_->update;
            for (const auto& update : *_iterable_13) {
                collectExpression(update, modulePath, analysis, plan, names, arguments);
            }
            collectBlock(for_->body, modulePath, analysis, plan, names, arguments);
            if (!doof::is_null(for_->then_)) {
                collectBlock(doof::unwrap_optional(for_->then_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
            collectExpression(forOf->iterable, modulePath, analysis, plan, names, arguments);
            collectBlock(forOf->body, modulePath, analysis, plan, names, arguments);
            if (!doof::is_null(forOf->then_)) {
                collectBlock(doof::unwrap_optional(forOf->then_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
            const auto& _iterable_14 = with_->bindings;
            for (const auto& binding : *_iterable_14) {
                collectExpression(binding->value, modulePath, analysis, plan, names, arguments);
            }
            collectBlock(with_->body, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
            if (!doof::is_null(return_->value)) {
                collectExpression(doof::unwrap_optional(return_->value), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject)) {
            const auto& yield_ = std::get<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject);
            collectExpression(yield_->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
            collectExpression(expression->expression, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
            collectExpression(destructuring->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(binding), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
                    const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(expression), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                    const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(destructuring), modulePath, analysis, plan, names, arguments);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
            collectExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            collectStatement(export_->declaration, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
            collectBlock(block, modulePath, analysis, plan, names, arguments);
    }
    else {
    }
    }
}
void collectBlock(std::shared_ptr<::app_src_ast_::Block> block, std::string modulePath, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments) {
    const auto& _iterable_15 = block->statements;
    for (const auto& statement : *_iterable_15) {
        collectStatement(statement, modulePath, analysis, plan, names, arguments);
    }
}
void collectExpression(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression, std::string modulePath, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments) {
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression))) {
        collectType(specialize(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression)), names, arguments), analysis, plan);
    }
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
            const auto& _iterable_16 = string_->interpolations;
            for (const auto& interpolation : *_iterable_16) {
                collectExpression(interpolation, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
            collectExpression(binary->left, modulePath, analysis, plan, names, arguments);
            collectExpression(binary->right, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
            collectExpression(unary->operand, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject);
            collectExpression(assignment->target, modulePath, analysis, plan, names, arguments);
            collectExpression(assignment->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            collectExpression(member->object, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
            collectExpression(index->object, modulePath, analysis, plan, names, arguments);
            collectExpression(index->index, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
            collectExpression(call->callee, modulePath, analysis, plan, names, arguments);
            const auto& _iterable_17 = call->args;
            for (const auto& argument : *_iterable_17) {
                collectExpression(argument->value, modulePath, analysis, plan, names, arguments);
            }
            if ((!doof::is_null(call->resolvedFunction)) && ((static_cast<int32_t>((call->resolvedFunction->typeParams)->size()) > 0) || call->resolvedFunction->native_)) {
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> concreteArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                const auto& _iterable_18 = call->resolvedGenericTypeArgs;
                for (const auto& argument : *_iterable_18) {
                    concreteArgs->push_back(specialize(argument, names, arguments));
                }
                if (!containsTypeParameters(concreteArgs)) {
                    auto recordedMethod = false;
                    {
                        auto _case_subject = call->callee;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
                            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
                                {
                                    auto _case_subject = specialize(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)), names, arguments);
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                                        const auto& ownerType = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                                        const auto owner = classDeclaration(analysis, ownerType->symbol->module, ownerType->symbol->name);
                                        if ((!doof::is_null(owner)) && (static_cast<int32_t>((call->resolvedFunction->typeParams)->size()) > 0)) {
                                            addMethod(plan, ownerType, doof::unwrap_optional(owner), doof::unwrap_optional(call->resolvedFunction), concreteArgs);
                                            (recordedMethod = true);
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
                    if (!recordedMethod) {
                        const auto targetModule = functionModule(call, modulePath);
                        addFunction(plan, targetModule, doof::unwrap_optional(call->resolvedFunction), concreteArgs);
                    }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
            const auto& _iterable_19 = array->elements;
            for (const auto& item : *_iterable_19) {
                collectExpression(item, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
            if (!doof::is_null(object->spread)) {
                collectExpression(doof::unwrap_optional(object->spread), modulePath, analysis, plan, names, arguments);
            }
            const auto& _iterable_20 = object->properties;
            for (const auto& property : *_iterable_20) {
                if (!doof::is_null(property->key)) {
                    collectExpression(doof::unwrap_optional(property->key), modulePath, analysis, plan, names, arguments);
                }
                if (!doof::is_null(property->value)) {
                    collectExpression(doof::unwrap_optional(property->value), modulePath, analysis, plan, names, arguments);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
            const auto& _iterable_21 = tuple->elements;
            for (const auto& item : *_iterable_21) {
                collectExpression(item, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
            const auto& _iterable_22 = lambda->params;
            for (const auto& parameter : *_iterable_22) {
                if (!doof::is_null(parameter->defaultValue)) {
                    collectExpression(doof::unwrap_optional(parameter->defaultValue), modulePath, analysis, plan, names, arguments);
                }
            }
            {
                auto _case_subject = lambda->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                    collectBlock(block, modulePath, analysis, plan, names, arguments);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                    collectExpression(inner, modulePath, analysis, plan, names, arguments);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
            collectExpression(if_->condition, modulePath, analysis, plan, names, arguments);
            collectExpression(if_->then_, modulePath, analysis, plan, names, arguments);
            collectExpression(if_->else_, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
            collectExpression(case_->subject, modulePath, analysis, plan, names, arguments);
            const auto& _iterable_23 = case_->arms;
            for (const auto& arm : *_iterable_23) {
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                        collectBlock(block, modulePath, analysis, plan, names, arguments);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                        collectExpression(bodyExpression, modulePath, analysis, plan, names, arguments);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
            const auto& _iterable_24 = construct->args;
            for (const auto& property : *_iterable_24) {
                if (!doof::is_null(property->value)) {
                    collectExpression(doof::unwrap_optional(property->value), modulePath, analysis, plan, names, arguments);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
            {
                auto _case_subject = async_->expression;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                    collectBlock(block, modulePath, analysis, plan, names, arguments);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
                    collectExpression(inner, modulePath, analysis, plan, names, arguments);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
            collectExpression(retire_->actor, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
            const auto& _iterable_25 = actor->args;
            for (const auto& argument : *_iterable_25) {
                collectExpression(argument, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
            collectBlock(yieldBlock->body, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
            collectBlock(catch_->body, modulePath, analysis, plan, names, arguments);
    }
    else {
    }
    }
}
void collectOptionalType(std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan) {
    if (!doof::is_null(type_)) {
        collectType(specialize(doof::unwrap_optional(type_), names, arguments), analysis, plan);
    }
}
void collectType(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            const auto& _iterable_26 = class_->typeArgs;
            for (const auto& argument : *_iterable_26) {
                collectType(argument, analysis, plan);
            }
            if ((static_cast<int32_t>((class_->typeArgs)->size()) > 0) && !containsTypeParameters(class_->typeArgs)) {
                const auto declaration = classDeclaration(analysis, class_->symbol->module, class_->symbol->name);
                if ((!doof::is_null(declaration)) && !declaration->native_) {
                    addClass(plan, class_->symbol->module, doof::unwrap_optional(declaration), class_->typeArgs);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto& _iterable_27 = interface_->typeArgs;
            for (const auto& argument : *_iterable_27) {
                collectType(argument, analysis, plan);
            }
            if ((static_cast<int32_t>((interface_->typeArgs)->size()) > 0) && !containsTypeParameters(interface_->typeArgs)) {
                addInterface(plan, interface_->symbol->module, interface_->name, interface_->typeArgs);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            collectType(array->elementType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            collectType(map->keyType, analysis, plan);
            collectType(map->valueType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            collectType(set_->elementType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            collectType(stream->elementType, analysis, plan);
            addInterface(plan, std::string(""), std::string("Stream"), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{stream->elementType}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            collectType(result->valueType, analysis, plan);
            collectType(result->errorType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            collectType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            collectType(promise->valueType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_28 = tuple->elements;
            for (const auto& element : *_iterable_28) {
                collectType(element, analysis, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_29 = union_->types;
            for (const auto& member : *_iterable_29) {
                collectType(member, analysis, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            collectType(weak_->inner, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_30 = function_->params;
            for (const auto& parameter : *_iterable_30) {
                collectType(parameter->type_, analysis, plan);
            }
            collectType(function_->returnType, analysis, plan);
    }
    else {
    }
    }
}
void addFunction(std::shared_ptr<InstantiationPlan> plan, std::string modulePath, std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs) {
    const auto key = functionInstantiationKey(modulePath, declaration->name, typeArgs);
    const auto& _iterable_31 = plan->functions;
    for (const auto& existing : *_iterable_31) {
        if (existing->key == key) {
            return;
        }
    }
    const auto emittedName = concreteName(declaration->name, typeArgs);
    plan->functions->push_back(std::make_shared<FunctionInstantiation>(key, modulePath, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(declaration->typeParams, typeArgs), emittedName, extendedTrace(plan->currentTrace, emittedName)));
}
void addClass(std::shared_ptr<InstantiationPlan> plan, std::string modulePath, std::shared_ptr<::app_src_ast_::ClassDeclaration> declaration, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs) {
    const auto key = classInstantiationKey(modulePath, declaration->name, typeArgs);
    if (containsString(plan->nativeTemplateClassKeys, nativeTemplateClassKey(modulePath, declaration->name))) {
        return;
    }
    const auto& _iterable_32 = plan->classes;
    for (const auto& existing : *_iterable_32) {
        if (existing->key == key) {
            return;
        }
    }
    const auto emittedName = concreteName(declaration->name, typeArgs);
    plan->classes->push_back(std::make_shared<ClassInstantiation>(key, modulePath, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(declaration->typeParams, typeArgs), emittedName, extendedTrace(plan->currentTrace, emittedName)));
}
std::string nativeTemplateClassKey(std::string modulePath, std::string name) {
    return ((modulePath + std::string("::")) + name);
}
void discoverNativeTemplateClasses(std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan) {
    const auto& _iterable_33 = analysis->modules;
    for (const auto& module : *_iterable_33) {
        const auto& _iterable_34 = module->program->statements;
        for (const auto& statement : *_iterable_34) {
            discoverNativeTemplateClassesInStatement(statement, plan);
        }
    }
}
void discoverNativeTemplateClassesInStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::shared_ptr<InstantiationPlan> plan) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (!class_->native_) {
                return;
            }
            const auto& _iterable_35 = class_->fields;
            for (const auto& field : *_iterable_35) {
                if (!doof::is_null(field->resolvedType)) {
                    collectNativeTemplateClasses(doof::unwrap_optional(field->resolvedType), plan);
                }
            }
            const auto& _iterable_36 = class_->methods;
            for (const auto& method : *_iterable_36) {
                if (!doof::is_null(method->resolvedType)) {
                    collectNativeTemplateClasses(doof::unwrap_optional(method->resolvedType), plan);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            if (fn->native_ && (!doof::is_null(fn->resolvedType))) {
                collectNativeTemplateClasses(doof::unwrap_optional(fn->resolvedType), plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            discoverNativeTemplateClassesInStatement(export_->declaration, plan);
    }
    else {
    }
    }
}
void collectNativeTemplateClasses(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<InstantiationPlan> plan) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if (!class_->symbol->native_ && (static_cast<int32_t>((class_->typeArgs)->size()) > 0)) {
                addString(plan->nativeTemplateClassKeys, nativeTemplateClassKey(class_->symbol->module, class_->name));
            }
            const auto& _iterable_37 = class_->typeArgs;
            for (const auto& argument : *_iterable_37) {
                collectNativeTemplateClasses(argument, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto& _iterable_38 = interface_->typeArgs;
            for (const auto& argument : *_iterable_38) {
                collectNativeTemplateClasses(argument, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            collectNativeTemplateClasses(array->elementType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            collectNativeTemplateClasses(map->keyType, plan);
            collectNativeTemplateClasses(map->valueType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            collectNativeTemplateClasses(set_->elementType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            collectNativeTemplateClasses(stream->elementType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            collectNativeTemplateClasses(result_->valueType, plan);
            collectNativeTemplateClasses(result_->errorType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            collectNativeTemplateClasses(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            collectNativeTemplateClasses(promise->valueType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_39 = tuple->elements;
            for (const auto& element : *_iterable_39) {
                collectNativeTemplateClasses(element, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_40 = union_->types;
            for (const auto& member : *_iterable_40) {
                collectNativeTemplateClasses(member, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            collectNativeTemplateClasses(weak_->inner, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_41 = function_->params;
            for (const auto& parameter : *_iterable_41) {
                collectNativeTemplateClasses(parameter->type_, plan);
            }
            collectNativeTemplateClasses(function_->returnType, plan);
    }
    else {
    }
    }
}
void addString(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    if (!containsString(values, value)) {
        values->push_back(value);
    }
}
bool containsString(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    const auto& _iterable_42 = values;
    for (const auto& existing : *_iterable_42) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}
void addInterface(std::shared_ptr<InstantiationPlan> plan, std::string modulePath, std::string name, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs) {
    if (containsTypeParameters(typeArgs)) {
        return;
    }
    const auto key = interfaceInstantiationKey(modulePath, name, typeArgs);
    const auto& _iterable_43 = plan->interfaces;
    for (const auto& existing : *_iterable_43) {
        if (existing->key == key) {
            return;
        }
    }
    plan->interfaces->push_back(std::make_shared<InterfaceInstantiation>(key, modulePath, name, std::make_shared<::app_src_semantic_::TypeSubstitution>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), typeArgs), concreteName(name, typeArgs), std::make_shared<std::vector<std::shared_ptr<ImplementationRef>>>(std::vector<std::shared_ptr<ImplementationRef>>{})));
}
void addMethod(std::shared_ptr<InstantiationPlan> plan, std::shared_ptr<::app_src_semantic_::ClassType> ownerType, std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> methodArgs) {
    if (static_cast<int32_t>((owner->typeParams)->size()) == 0) {
        return;
    }
    const auto ownerKey = classInstantiationKey(ownerType->symbol->module, ownerType->name, ownerType->typeArgs);
    const auto key = methodInstantiationKey(ownerKey, declaration->name, methodArgs);
    const auto& _iterable_44 = plan->methods;
    for (const auto& existing : *_iterable_44) {
        if (existing->key == key) {
            return;
        }
    }
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
    const auto& _iterable_45 = owner->typeParams;
    for (const auto& name : *_iterable_45) {
        names->push_back(name);
    }
    const auto& _iterable_46 = ownerType->typeArgs;
    for (const auto& argument : *_iterable_46) {
        arguments->push_back(argument);
    }
    const auto& _iterable_47 = declaration->typeParams;
    for (const auto& name : *_iterable_47) {
        names->push_back(name);
    }
    const auto& _iterable_48 = methodArgs;
    for (const auto& argument : *_iterable_48) {
        arguments->push_back(argument);
    }
    plan->methods->push_back(std::make_shared<MethodInstantiation>(key, ownerType->symbol->module, ownerKey, owner, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(names, arguments), concreteName(declaration->name, methodArgs), extendedTrace(plan->currentTrace, concreteName(((owner->name + std::string("__")) + declaration->name), methodArgs))));
}
std::shared_ptr<std::vector<std::string>> extendedTrace(std::shared_ptr<std::vector<std::string>> parent, std::string item) {
    std::shared_ptr<std::vector<std::string>> trace = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto start = ((static_cast<int32_t>((parent)->size()) > 11) ? (static_cast<int32_t>((parent)->size()) - 11) : 0);
    for (int32_t index = start; index < static_cast<int32_t>((parent)->size()); ++index) {
        trace->push_back((*parent)[index]);
    }
    trace->push_back(item);
    return trace;
}
void discoverConcreteInterfaceImplementations(std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::shared_ptr<InstantiationPlan> plan) {
    const auto& _iterable_49 = plan->interfaces;
    for (const auto& interface_ : *_iterable_49) {
        const auto& _iterable_50 = analysis->modules;
        for (const auto& module : *_iterable_50) {
            const auto& _iterable_51 = module->program->statements;
            for (const auto& statement : *_iterable_51) {
                std::shared_ptr<::app_src_ast_::ClassDeclaration> candidate = nullptr;
                {
                    auto _case_subject = statement;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                        (candidate = class_);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                        const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
                        {
                            auto _case_subject = export_->declaration;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                                (candidate = class_);
                        }
                        else {
                        }
                        }
                }
                else {
                }
                }
                if ((((!doof::is_null(candidate)) && (static_cast<int32_t>((candidate->typeParams)->size()) == 0)) && !candidate->struct_) && classImplementsConcreteInterface(doof::unwrap_optional(candidate), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), interface_, analysis)) {
                    addImplementation(interface_, module->path, candidate->name);
                }
            }
        }
        const auto& _iterable_52 = plan->classes;
        for (const auto& class_ : *_iterable_52) {
            if (class_->declaration->struct_) {
                continue;
            }
            if (classImplementsConcreteInterface(class_->declaration, class_->substitution->arguments, interface_, analysis)) {
                addImplementation(interface_, class_->modulePath, class_->emittedName);
            }
        }
    }
}
void addImplementation(std::shared_ptr<InterfaceInstantiation> interface_, std::string modulePath, std::string typeName_) {
    const auto& _iterable_53 = interface_->implementations;
    for (const auto& existing : *_iterable_53) {
        if ((existing->modulePath == modulePath) && (existing->typeName == typeName_)) {
            return;
        }
    }
    interface_->implementations->push_back(std::make_shared<ImplementationRef>(modulePath, typeName_));
}
bool classImplementsConcreteInterface(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> classArgs, std::shared_ptr<InterfaceInstantiation> interface_, std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis) {
    if (interface_->name == std::string("Stream")) {
        const auto& _iterable_54 = class_->implements_;
        for (const auto& implementation : *_iterable_54) {
            if (doof::is_null(implementation->resolvedType)) {
                continue;
            }
            {
                auto _case_subject = specialize(doof::unwrap_optional(implementation->resolvedType), class_->typeParams, classArgs);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                    const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
                    if (::app_src_checker_types_::sameType(stream->elementType, (*interface_->substitution->arguments)[0])) {
                        return true;
                    }
            }
            else {
            }
            }
        }
        const auto next = classMethod(class_, std::string("next"));
        const auto value = classMethod(class_, std::string("value"));
        if (((doof::is_null(next) || doof::is_null(value)) || doof::is_null(next->resolvedType)) || doof::is_null(value->resolvedType)) {
            return false;
        }
        const auto nextType = specialize(doof::unwrap_optional(next->resolvedType), class_->typeParams, classArgs);
        const auto valueType = specialize(doof::unwrap_optional(value->resolvedType), class_->typeParams, classArgs);
        {
            auto _case_subject = nextType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                if ((::app_src_checker_types_::typeName(fn->returnType) != std::string("bool")) || (static_cast<int32_t>((fn->params)->size()) != 0)) {
                    return false;
                }
        }
        else {
                return false;
        }
        }
        {
            auto _case_subject = valueType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                return ((static_cast<int32_t>((fn->params)->size()) == 0) && ::app_src_checker_types_::sameType(fn->returnType, (*interface_->substitution->arguments)[0]));
        }
        else {
                return false;
        }
        }
    }
    const auto declaration = interfaceDeclaration(analysis, interface_->modulePath, interface_->name);
    if (doof::is_null(declaration)) {
        return false;
    }
    const auto& _iterable_55 = declaration->fields;
    for (const auto& required : *_iterable_55) {
        const auto actual = classField(class_, required->name);
        if ((doof::is_null(actual) || doof::is_null(actual->resolvedType)) || doof::is_null(required->resolvedType)) {
            return false;
        }
        const auto actualType = specialize(doof::unwrap_optional(actual->resolvedType), class_->typeParams, classArgs);
        const auto requiredType = specialize(doof::unwrap_optional(required->resolvedType), declaration->typeParams, interface_->substitution->arguments);
        if (!::app_src_checker_types_::isAssignable(actualType, requiredType)) {
            return false;
        }
    }
    const auto& _iterable_56 = declaration->methods;
    for (const auto& required : *_iterable_56) {
        const auto actual = classMethod(class_, required->name);
        if ((doof::is_null(actual) || doof::is_null(actual->resolvedType)) || doof::is_null(required->resolvedType)) {
            return false;
        }
        const auto actualType = specialize(doof::unwrap_optional(actual->resolvedType), class_->typeParams, classArgs);
        const auto requiredType = specialize(doof::unwrap_optional(required->resolvedType), declaration->typeParams, interface_->substitution->arguments);
        if (!sameConcreteMethodType(actualType, requiredType)) {
            return false;
        }
    }
    return true;
}
std::shared_ptr<::app_src_ast_::ClassField> classField(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, std::string name) {
    const auto& _iterable_57 = class_->fields;
    for (const auto& field : *_iterable_57) {
        const auto& _iterable_58 = field->names;
        for (const auto& fieldName : *_iterable_58) {
            if (fieldName == name) {
                return field;
            }
        }
    }
    return nullptr;
}
bool sameConcreteMethodType(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> actual, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected) {
    {
        auto _case_subject = actual;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& actualFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            {
                auto _case_subject = expected;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                    const auto& expectedFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                    if (static_cast<int32_t>((actualFunction->params)->size()) != static_cast<int32_t>((expectedFunction->params)->size())) {
                        return false;
                    }
                    for (int32_t index = 0; index < static_cast<int32_t>((actualFunction->params)->size()); ++index) {
                        if (!::app_src_checker_types_::sameType((*actualFunction->params)[index]->type_, (*expectedFunction->params)[index]->type_)) {
                            return false;
                        }
                    }
                    return ::app_src_checker_types_::sameType(actualFunction->returnType, expectedFunction->returnType);
            }
            else {
                    return false;
            }
            }
    }
    else {
            return ::app_src_checker_types_::sameType(actual, expected);
    }
    }
    return false;
}
std::shared_ptr<::app_src_ast_::FunctionDeclaration> classMethod(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_, std::string name) {
    const auto& _iterable_59 = class_->methods;
    for (const auto& method : *_iterable_59) {
        if ((method->name == name) && !method->static_) {
            return method;
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::InterfaceDeclaration> interfaceDeclaration(std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::string modulePath, std::string name) {
    const auto& _iterable_60 = analysis->modules;
    for (const auto& module : *_iterable_60) {
        if (module->path != modulePath) {
            continue;
        }
        const auto& _iterable_61 = module->program->statements;
        for (const auto& statement : *_iterable_61) {
            {
                auto _case_subject = statement;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                    if (interface_->name == name) {
                        return interface_;
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                    const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
                    {
                        auto _case_subject = export_->declaration;
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
            else {
            }
            }
        }
    }
    return nullptr;
}
std::string functionModule(std::shared_ptr<::app_src_ast_::CallExpression> call, std::string fallback) {
    {
        auto _case_subject = call->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            if (!doof::is_null(identifier->resolvedBinding)) {
                if (!doof::is_null(identifier->resolvedBinding->symbol)) {
                    return identifier->resolvedBinding->symbol->module;
                }
                if (identifier->resolvedBinding->module != std::string("")) {
                    return identifier->resolvedBinding->module;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                        return class_->symbol->module;
                }
                else {
                }
                }
            }
    }
    else {
    }
    }
    return fallback;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> classDeclaration(std::shared_ptr<::app_src_analyzer_::AnalysisResult> analysis, std::string modulePath, std::string name) {
    const auto& _iterable_62 = analysis->modules;
    for (const auto& module : *_iterable_62) {
        if (module->path != modulePath) {
            continue;
        }
        const auto& _iterable_63 = module->program->statements;
        for (const auto& statement : *_iterable_63) {
            const auto declaration = classFromStatement(statement, name);
            if (!doof::is_null(declaration)) {
                return declaration;
            }
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_ast_::ClassDeclaration> classFromStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::string name) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            if (class_->name == name) {
                return class_;
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            return classFromStatement(export_->declaration, name);
    }
    else {
    }
    }
    return nullptr;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> specialize(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments) {
    if (static_cast<int32_t>((names)->size()) == 0) {
        return type_;
    }
    return ::app_src_checker_types_::substituteTypeParams(type_, names, arguments);
}
bool containsTypeParameters(std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> types) {
    const auto& _iterable_64 = types;
    for (const auto& type_ : *_iterable_64) {
        if (containsTypeParameter(type_)) {
            return true;
        }
    }
    return false;
}
bool containsTypeParameter(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            return containsTypeParameters(class_->typeArgs);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            return containsTypeParameters(interface_->typeArgs);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return containsTypeParameter(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            return (containsTypeParameter(map->keyType) || containsTypeParameter(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            return containsTypeParameter(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            return containsTypeParameter(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return (containsTypeParameter(result->valueType) || containsTypeParameter(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            return containsTypeParameter(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            return containsTypeParameter(promise->valueType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            return containsTypeParameters(tuple->elements);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            return containsTypeParameters(union_->types);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            return containsTypeParameter(weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_65 = function_->params;
            for (const auto& parameter : *_iterable_65) {
                if (containsTypeParameter(parameter->type_)) {
                    return true;
                }
            }
            return containsTypeParameter(function_->returnType);
    }
    else {
            return false;
    }
    }
    return false;
}
std::string concreteTypeListKey(std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> types) {
    auto result = std::string("");
    const auto& _iterable_66 = types;
    for (const auto& type_ : *_iterable_66) {
        (result = (((result + std::string("[")) + canonicalTypeKey(type_)) + std::string("]")));
    }
    return result;
}
std::string canonicalTypeKey(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            return ((((std::string("class:") + class_->symbol->module) + std::string(":")) + class_->name) + concreteTypeListKey(class_->typeArgs));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            return ((((std::string("interface:") + interface_->symbol->module) + std::string(":")) + interface_->name) + concreteTypeListKey(interface_->typeArgs));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return ((array->readonly_ ? std::string("readonly-array:") : std::string("array:")) + canonicalTypeKey(array->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            return ((((map->readonly_ ? std::string("readonly-map:") : std::string("map:")) + canonicalTypeKey(map->keyType)) + std::string(":")) + canonicalTypeKey(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            return ((set_->readonly_ ? std::string("readonly-set:") : std::string("set:")) + canonicalTypeKey(set_->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            return (std::string("stream:") + canonicalTypeKey(stream->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return (((std::string("result:") + canonicalTypeKey(result->valueType)) + std::string(":")) + canonicalTypeKey(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            return (std::string("actor:") + canonicalTypeKey(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            return (std::string("promise:") + canonicalTypeKey(promise->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            return (std::string("tuple:") + concreteTypeListKey(tuple->elements));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            return (std::string("union:") + concreteTypeListKey(union_->types));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            return (std::string("weak:") + canonicalTypeKey(weak_->inner));
    }
    else {
            return ::app_src_checker_types_::typeName(type_);
    }
    }
    return ::app_src_checker_types_::typeName(type_);
}
std::string mangleType(std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            return sanitize(((((::app_src_emitter_names_::moduleNamespace(class_->symbol->module) + std::string("_")) + class_->name) + std::string("_")) + concreteTypeListMangle(class_->typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            return sanitize(((((::app_src_emitter_names_::moduleNamespace(interface_->symbol->module) + std::string("_")) + interface_->name) + std::string("_")) + concreteTypeListMangle(interface_->typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return ((array->readonly_ ? std::string("readonly_array_") : std::string("array_")) + mangleType(array->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            return ((((map->readonly_ ? std::string("readonly_map_") : std::string("map_")) + mangleType(map->keyType)) + std::string("_")) + mangleType(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            return ((set_->readonly_ ? std::string("readonly_set_") : std::string("set_")) + mangleType(set_->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            return (std::string("stream_") + mangleType(stream->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return (((std::string("result_") + mangleType(result->valueType)) + std::string("_")) + mangleType(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            return (std::string("actor_") + mangleType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            return (std::string("promise_") + mangleType(promise->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            return (std::string("tuple_") + concreteTypeListMangle(tuple->elements));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            return (std::string("union_") + concreteTypeListMangle(union_->types));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            return (std::string("weak_") + mangleType(weak_->inner));
    }
    else {
            return sanitize(::app_src_checker_types_::typeName(type_));
    }
    }
    return std::string("type");
}
std::string concreteTypeListMangle(std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> types) {
    auto result = std::string("");
    const auto& _iterable_67 = types;
    for (const auto& type_ : *_iterable_67) {
        if (result != std::string("")) {
            (result = (result + std::string("_")));
        }
        (result = (result + mangleType(type_)));
    }
    return result;
}
std::string sanitize(std::string value) {
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("/"), std::string("_")), std::string("."), std::string("_")), std::string("<"), std::string("_")), std::string(">"), std::string("_")), std::string(","), std::string("_")), std::string(" "), std::string("_")), std::string("|"), std::string("_")), std::string("["), std::string("_")), std::string("]"), std::string("_")), std::string(":"), std::string("_")), std::string("("), std::string("_")), std::string(")"), std::string("_"));
}
}
