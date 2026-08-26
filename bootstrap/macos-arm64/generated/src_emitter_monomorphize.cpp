#include "src_emitter_monomorphize.hpp"

namespace app_src_emitter_monomorphize_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_names_;






#line 82 "/src/emitter-monomorphize.do"
std::shared_ptr<InstantiationPlan> buildInstantiationPlan(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 83 "/src/emitter-monomorphize.do"
    const auto plan = std::make_shared<InstantiationPlan>(std::make_shared<std::vector<std::shared_ptr<FunctionInstantiation>>>(std::vector<std::shared_ptr<FunctionInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<ClassInstantiation>>>(std::vector<std::shared_ptr<ClassInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<InterfaceInstantiation>>>(std::vector<std::shared_ptr<InterfaceInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<MethodInstantiation>>>(std::vector<std::shared_ptr<MethodInstantiation>>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 84 "/src/emitter-monomorphize.do"
    discoverNativeTemplateClasses(result, plan);
#line 85 "/src/emitter-monomorphize.do"
    const auto& _iterable_2 = result->modules;
    for (const auto& module : *_iterable_2) {
#line 86 "/src/emitter-monomorphize.do"
        const auto& _iterable_4 = module->program->statements;
        for (const auto& statement : *_iterable_4) {
#line 86 "/src/emitter-monomorphize.do"
            collectStatement(statement, module->path, result, plan, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
        }
    }
#line 89 "/src/emitter-monomorphize.do"
    auto functionIndex = 0;
#line 90 "/src/emitter-monomorphize.do"
    auto classIndex = 0;
#line 91 "/src/emitter-monomorphize.do"
    auto methodIndex = 0;
#line 92 "/src/emitter-monomorphize.do"
    while (((functionIndex < static_cast<int32_t>((plan->functions)->size())) || (classIndex < static_cast<int32_t>((plan->classes)->size()))) || (methodIndex < static_cast<int32_t>((plan->methods)->size()))) {
#line 93 "/src/emitter-monomorphize.do"
        if (((static_cast<int32_t>((plan->functions)->size()) + static_cast<int32_t>((plan->classes)->size())) + static_cast<int32_t>((plan->methods)->size())) > 256) {
#line 94 "/src/emitter-monomorphize.do"
            (plan->overflow = true);
#line 95 "/src/emitter-monomorphize.do"
            const auto& _iterable_6 = plan->currentTrace;
            for (const auto& item : *_iterable_6) {
#line 95 "/src/emitter-monomorphize.do"
                plan->overflowTrace->push_back(item);
            }
#line 96 "/src/emitter-monomorphize.do"
            return plan;
        }
#line 98 "/src/emitter-monomorphize.do"
        if (functionIndex < static_cast<int32_t>((plan->functions)->size())) {
#line 99 "/src/emitter-monomorphize.do"
            const auto instantiation = doof::array_at(plan->functions, functionIndex, "src/emitter-monomorphize", 99);
#line 100 "/src/emitter-monomorphize.do"
            (functionIndex = (functionIndex + 1));
#line 101 "/src/emitter-monomorphize.do"
            (plan->currentTrace = instantiation->trace);
#line 102 "/src/emitter-monomorphize.do"
            collectFunctionBody(instantiation->declaration, instantiation->modulePath, result, plan, instantiation->substitution->names, instantiation->substitution->arguments);
        }
#line 105 "/src/emitter-monomorphize.do"
        if (classIndex < static_cast<int32_t>((plan->classes)->size())) {
#line 106 "/src/emitter-monomorphize.do"
            const auto instantiation = doof::array_at(plan->classes, classIndex, "src/emitter-monomorphize", 106);
#line 107 "/src/emitter-monomorphize.do"
            (classIndex = (classIndex + 1));
#line 108 "/src/emitter-monomorphize.do"
            (plan->currentTrace = instantiation->trace);
#line 109 "/src/emitter-monomorphize.do"
            collectClassBody(instantiation->declaration, instantiation->modulePath, result, plan, instantiation->substitution->names, instantiation->substitution->arguments);
        }
#line 112 "/src/emitter-monomorphize.do"
        if (methodIndex < static_cast<int32_t>((plan->methods)->size())) {
#line 113 "/src/emitter-monomorphize.do"
            const auto instantiation = doof::array_at(plan->methods, methodIndex, "src/emitter-monomorphize", 113);
#line 114 "/src/emitter-monomorphize.do"
            (methodIndex = (methodIndex + 1));
#line 115 "/src/emitter-monomorphize.do"
            (plan->currentTrace = instantiation->trace);
#line 116 "/src/emitter-monomorphize.do"
            collectFunctionBody(instantiation->declaration, instantiation->modulePath, result, plan, instantiation->substitution->names, instantiation->substitution->arguments);
        }
    }
#line 120 "/src/emitter-monomorphize.do"
    discoverConcreteInterfaceImplementations(result, plan);
#line 121 "/src/emitter-monomorphize.do"
    return plan;
}
#line 124 "/src/emitter-monomorphize.do"
std::string functionInstantiationKey(const std::string& modulePath, const std::string& name, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 125 "/src/emitter-monomorphize.do"
    return ((((modulePath + std::string("::function::")) + name) + std::string("::")) + concreteTypeListKey(typeArgs));
}
#line 128 "/src/emitter-monomorphize.do"
std::string classInstantiationKey(const std::string& modulePath, const std::string& name, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 129 "/src/emitter-monomorphize.do"
    return ((((modulePath + std::string("::class::")) + name) + std::string("::")) + concreteTypeListKey(typeArgs));
}
#line 132 "/src/emitter-monomorphize.do"
std::string interfaceInstantiationKey(const std::string& modulePath, const std::string& name, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 133 "/src/emitter-monomorphize.do"
    return ((((modulePath + std::string("::interface::")) + name) + std::string("::")) + concreteTypeListKey(typeArgs));
}
#line 136 "/src/emitter-monomorphize.do"
std::string methodInstantiationKey(const std::string& ownerKey, const std::string& name, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 137 "/src/emitter-monomorphize.do"
    return ((((ownerKey + std::string("::method::")) + name) + std::string("::")) + concreteTypeListKey(typeArgs));
}
#line 140 "/src/emitter-monomorphize.do"
std::string concreteName(const std::string& name, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 141 "/src/emitter-monomorphize.do"
    auto result = name;
#line 142 "/src/emitter-monomorphize.do"
    const auto& _iterable_8 = typeArgs;
    for (const auto& argument : *_iterable_8) {
#line 142 "/src/emitter-monomorphize.do"
        (result = ((result + std::string("__")) + mangleType(argument)));
    }
#line 143 "/src/emitter-monomorphize.do"
    return result;
}
#line 146 "/src/emitter-monomorphize.do"
std::string findConcreteFunctionName(const std::shared_ptr<InstantiationPlan>& plan, const std::string& key) {
#line 147 "/src/emitter-monomorphize.do"
    const auto& _iterable_10 = plan->functions;
    for (const auto& instantiation : *_iterable_10) {
#line 147 "/src/emitter-monomorphize.do"
        if (instantiation->key == key) {
#line 147 "/src/emitter-monomorphize.do"
            return instantiation->emittedName;
        }
    }
#line 148 "/src/emitter-monomorphize.do"
    return std::string("");
}
#line 151 "/src/emitter-monomorphize.do"
std::string findConcreteClassName(const std::shared_ptr<InstantiationPlan>& plan, const std::string& key) {
#line 152 "/src/emitter-monomorphize.do"
    const auto& _iterable_12 = plan->classes;
    for (const auto& instantiation : *_iterable_12) {
#line 152 "/src/emitter-monomorphize.do"
        if (instantiation->key == key) {
#line 152 "/src/emitter-monomorphize.do"
            return instantiation->emittedName;
        }
    }
#line 153 "/src/emitter-monomorphize.do"
    return std::string("");
}
#line 156 "/src/emitter-monomorphize.do"
void collectFunctionBody(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& modulePath, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 157 "/src/emitter-monomorphize.do"
    const auto& _iterable_14 = fn->params;
    for (const auto& parameter : *_iterable_14) {
#line 158 "/src/emitter-monomorphize.do"
        if (!doof::is_null(parameter->resolvedType)) {
#line 158 "/src/emitter-monomorphize.do"
            collectType(specialize(doof::unwrap_optional(parameter->resolvedType), names, arguments), analysis, plan);
        }
#line 159 "/src/emitter-monomorphize.do"
        if (!doof::is_null(parameter->defaultValue)) {
#line 159 "/src/emitter-monomorphize.do"
            collectExpression(doof::unwrap_optional(parameter->defaultValue), modulePath, analysis, plan, names, arguments);
        }
    }
#line 161 "/src/emitter-monomorphize.do"
    if (!doof::is_null(fn->resolvedType)) {
#line 161 "/src/emitter-monomorphize.do"
        collectType(specialize(doof::unwrap_optional(fn->resolvedType), names, arguments), analysis, plan);
    }
#line 162 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = fn->body;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 163 "/src/emitter-monomorphize.do"
            const auto& _iterable_16 = block->statements;
            for (const auto& statement : *_iterable_16) {
#line 163 "/src/emitter-monomorphize.do"
                collectStatement(statement, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
            const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 164 "/src/emitter-monomorphize.do"
            collectExpression(expression, modulePath, analysis, plan, names, arguments);
    }
    }
}
#line 168 "/src/emitter-monomorphize.do"
void collectClassBody(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& modulePath, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 169 "/src/emitter-monomorphize.do"
    const auto& _iterable_18 = class_->fields;
    for (const auto& field : *_iterable_18) {
#line 170 "/src/emitter-monomorphize.do"
        if (!doof::is_null(field->resolvedType)) {
#line 170 "/src/emitter-monomorphize.do"
            collectType(specialize(doof::unwrap_optional(field->resolvedType), names, arguments), analysis, plan);
        }
#line 171 "/src/emitter-monomorphize.do"
        if (!doof::is_null(field->defaultValue)) {
#line 171 "/src/emitter-monomorphize.do"
            collectExpression(doof::unwrap_optional(field->defaultValue), modulePath, analysis, plan, names, arguments);
        }
    }
#line 173 "/src/emitter-monomorphize.do"
    const auto& _iterable_20 = class_->methods;
    for (const auto& method : *_iterable_20) {
#line 176 "/src/emitter-monomorphize.do"
        if (static_cast<int32_t>((method->typeParams)->size()) == 0) {
#line 176 "/src/emitter-monomorphize.do"
            collectFunctionBody(method, modulePath, analysis, plan, names, arguments);
        }
    }
#line 178 "/src/emitter-monomorphize.do"
    if (!doof::is_null(class_->destructor_)) {
#line 178 "/src/emitter-monomorphize.do"
        collectBlock(doof::unwrap_optional(class_->destructor_), modulePath, analysis, plan, names, arguments);
    }
}
#line 181 "/src/emitter-monomorphize.do"
void collectStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::string& modulePath, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 182 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 183 "/src/emitter-monomorphize.do"
            collectOptionalType(const_->resolvedType, names, arguments, analysis, plan);
#line 183 "/src/emitter-monomorphize.do"
            collectExpression(const_->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 184 "/src/emitter-monomorphize.do"
            collectOptionalType(readonly_->resolvedType, names, arguments, analysis, plan);
#line 184 "/src/emitter-monomorphize.do"
            collectExpression(readonly_->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 186 "/src/emitter-monomorphize.do"
            collectOptionalType(binding->resolvedType, names, arguments, analysis, plan);
#line 187 "/src/emitter-monomorphize.do"
            collectExpression(binding->value, modulePath, analysis, plan, names, arguments);
#line 188 "/src/emitter-monomorphize.do"
            if (!doof::is_null(binding->else_)) {
#line 188 "/src/emitter-monomorphize.do"
                collectBlock(doof::unwrap_optional(binding->else_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 190 "/src/emitter-monomorphize.do"
            collectOptionalType(let_->resolvedType, names, arguments, analysis, plan);
#line 190 "/src/emitter-monomorphize.do"
            collectExpression(let_->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 191 "/src/emitter-monomorphize.do"
            if (static_cast<int32_t>((fn->typeParams)->size()) == 0) {
#line 191 "/src/emitter-monomorphize.do"
                collectFunctionBody(fn, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 192 "/src/emitter-monomorphize.do"
            if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
#line 192 "/src/emitter-monomorphize.do"
                collectClassBody(class_, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
#line 194 "/src/emitter-monomorphize.do"
            collectExpression(if_->condition, modulePath, analysis, plan, names, arguments);
#line 194 "/src/emitter-monomorphize.do"
            collectBlock(if_->body, modulePath, analysis, plan, names, arguments);
#line 195 "/src/emitter-monomorphize.do"
            const auto& _iterable_22 = if_->elseIfs;
            for (const auto& branch : *_iterable_22) {
#line 195 "/src/emitter-monomorphize.do"
                collectExpression(branch->condition, modulePath, analysis, plan, names, arguments);
#line 195 "/src/emitter-monomorphize.do"
                collectBlock(branch->body, modulePath, analysis, plan, names, arguments);
            }
#line 196 "/src/emitter-monomorphize.do"
            if (!doof::is_null(if_->else_)) {
#line 196 "/src/emitter-monomorphize.do"
                collectBlock(doof::unwrap_optional(if_->else_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
#line 199 "/src/emitter-monomorphize.do"
            collectExpression(case_->subject, modulePath, analysis, plan, names, arguments);
#line 200 "/src/emitter-monomorphize.do"
            const auto& _iterable_24 = case_->arms;
            for (const auto& arm : *_iterable_24) {
#line 201 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 202 "/src/emitter-monomorphize.do"
                        collectBlock(block, modulePath, analysis, plan, names, arguments);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto expression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 203 "/src/emitter-monomorphize.do"
                        collectExpression(expression, modulePath, analysis, plan, names, arguments);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject)) {
            const auto& while_ = std::get<std::shared_ptr<::app_src_ast_::WhileStatement>>(_case_subject);
#line 207 "/src/emitter-monomorphize.do"
            collectExpression(while_->condition, modulePath, analysis, plan, names, arguments);
#line 207 "/src/emitter-monomorphize.do"
            collectBlock(while_->body, modulePath, analysis, plan, names, arguments);
#line 207 "/src/emitter-monomorphize.do"
            if (!doof::is_null(while_->then_)) {
#line 207 "/src/emitter-monomorphize.do"
                collectBlock(doof::unwrap_optional(while_->then_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject)) {
            const auto& for_ = std::get<std::shared_ptr<::app_src_ast_::ForStatement>>(_case_subject);
#line 209 "/src/emitter-monomorphize.do"
            if (!doof::is_null(for_->init)) {
#line 209 "/src/emitter-monomorphize.do"
                collectStatement(doof::unwrap_optional(for_->init), modulePath, analysis, plan, names, arguments);
            }
#line 210 "/src/emitter-monomorphize.do"
            if (!doof::is_null(for_->condition)) {
#line 210 "/src/emitter-monomorphize.do"
                collectExpression(doof::unwrap_optional(for_->condition), modulePath, analysis, plan, names, arguments);
            }
#line 211 "/src/emitter-monomorphize.do"
            const auto& _iterable_26 = for_->update;
            for (const auto& update : *_iterable_26) {
#line 211 "/src/emitter-monomorphize.do"
                collectExpression(update, modulePath, analysis, plan, names, arguments);
            }
#line 212 "/src/emitter-monomorphize.do"
            collectBlock(for_->body, modulePath, analysis, plan, names, arguments);
#line 212 "/src/emitter-monomorphize.do"
            if (!doof::is_null(for_->then_)) {
#line 212 "/src/emitter-monomorphize.do"
                collectBlock(doof::unwrap_optional(for_->then_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject)) {
            const auto& forOf = std::get<std::shared_ptr<::app_src_ast_::ForOfStatement>>(_case_subject);
#line 214 "/src/emitter-monomorphize.do"
            collectExpression(forOf->iterable, modulePath, analysis, plan, names, arguments);
#line 214 "/src/emitter-monomorphize.do"
            collectBlock(forOf->body, modulePath, analysis, plan, names, arguments);
#line 214 "/src/emitter-monomorphize.do"
            if (!doof::is_null(forOf->then_)) {
#line 214 "/src/emitter-monomorphize.do"
                collectBlock(doof::unwrap_optional(forOf->then_), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
            const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
#line 216 "/src/emitter-monomorphize.do"
            const auto& _iterable_28 = with_->bindings;
            for (const auto& binding : *_iterable_28) {
#line 216 "/src/emitter-monomorphize.do"
                collectExpression(binding->value, modulePath, analysis, plan, names, arguments);
            }
#line 217 "/src/emitter-monomorphize.do"
            collectBlock(with_->body, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject)) {
            const auto& return_ = std::get<std::shared_ptr<::app_src_ast_::ReturnStatement>>(_case_subject);
#line 219 "/src/emitter-monomorphize.do"
            if (!doof::is_null(return_->value)) {
#line 219 "/src/emitter-monomorphize.do"
                collectExpression(doof::unwrap_optional(return_->value), modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject)) {
            const auto& yield_ = std::get<std::shared_ptr<::app_src_ast_::YieldStatement>>(_case_subject);
#line 220 "/src/emitter-monomorphize.do"
            collectExpression(yield_->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
            const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 221 "/src/emitter-monomorphize.do"
            collectExpression(expression->expression, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
            const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 222 "/src/emitter-monomorphize.do"
            collectExpression(destructuring->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject)) {
            const auto& try_ = std::get<std::shared_ptr<::app_src_ast_::TryStatement>>(_case_subject);
#line 224 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = try_->binding;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 225 "/src/emitter-monomorphize.do"
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 226 "/src/emitter-monomorphize.do"
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
                    const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 227 "/src/emitter-monomorphize.do"
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(binding), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
                    const auto& declaration = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 228 "/src/emitter-monomorphize.do"
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(declaration), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject)) {
                    const auto& expression = std::get<std::shared_ptr<::app_src_ast_::ExpressionStatement>>(_case_subject);
#line 229 "/src/emitter-monomorphize.do"
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(expression), modulePath, analysis, plan, names, arguments);
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject)) {
                    const auto& destructuring = std::get<std::shared_ptr<::app_src_ast_::DestructuringStatement>>(_case_subject);
#line 230 "/src/emitter-monomorphize.do"
                    collectStatement(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>>(destructuring), modulePath, analysis, plan, names, arguments);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>>(_case_subject);
#line 233 "/src/emitter-monomorphize.do"
            collectExpression(doof::variant_promote<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(assignment->value), modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 234 "/src/emitter-monomorphize.do"
            collectStatement(export_->declaration, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 235 "/src/emitter-monomorphize.do"
            collectBlock(block, modulePath, analysis, plan, names, arguments);
    }
    else {
    }
    }
}
#line 240 "/src/emitter-monomorphize.do"
void collectBlock(const std::shared_ptr<::app_src_ast_::Block>& block, const std::string& modulePath, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 241 "/src/emitter-monomorphize.do"
    const auto& _iterable_30 = block->statements;
    for (const auto& statement : *_iterable_30) {
#line 241 "/src/emitter-monomorphize.do"
        collectStatement(statement, modulePath, analysis, plan, names, arguments);
    }
}
#line 244 "/src/emitter-monomorphize.do"
void collectExpression(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::string& modulePath, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 245 "/src/emitter-monomorphize.do"
    if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression))) {
#line 245 "/src/emitter-monomorphize.do"
        collectType(specialize(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, expression)), names, arguments), analysis, plan);
    }
#line 246 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = expression;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject)) {
            const auto& string_ = std::get<std::shared_ptr<::app_src_ast_::StringLiteral>>(_case_subject);
#line 247 "/src/emitter-monomorphize.do"
            const auto& _iterable_32 = string_->interpolations;
            for (const auto& interpolation : *_iterable_32) {
#line 247 "/src/emitter-monomorphize.do"
                collectExpression(interpolation, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject)) {
            const auto& binary = std::get<std::shared_ptr<::app_src_ast_::BinaryExpression>>(_case_subject);
#line 248 "/src/emitter-monomorphize.do"
            collectExpression(binary->left, modulePath, analysis, plan, names, arguments);
#line 248 "/src/emitter-monomorphize.do"
            collectExpression(binary->right, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject)) {
            const auto& unary = std::get<std::shared_ptr<::app_src_ast_::UnaryExpression>>(_case_subject);
#line 249 "/src/emitter-monomorphize.do"
            collectExpression(unary->operand, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject)) {
            const auto& assignment = std::get<std::shared_ptr<::app_src_ast_::AssignmentExpression>>(_case_subject);
#line 250 "/src/emitter-monomorphize.do"
            collectExpression(assignment->target, modulePath, analysis, plan, names, arguments);
#line 250 "/src/emitter-monomorphize.do"
            collectExpression(assignment->value, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 252 "/src/emitter-monomorphize.do"
            collectExpression(member->object, modulePath, analysis, plan, names, arguments);
#line 253 "/src/emitter-monomorphize.do"
            collectJsonMemberDemand(member, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject)) {
            const auto& index = std::get<std::shared_ptr<::app_src_ast_::IndexExpression>>(_case_subject);
#line 255 "/src/emitter-monomorphize.do"
            collectExpression(index->object, modulePath, analysis, plan, names, arguments);
#line 255 "/src/emitter-monomorphize.do"
            collectExpression(index->index, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject)) {
            const auto& call = std::get<std::shared_ptr<::app_src_ast_::CallExpression>>(_case_subject);
#line 257 "/src/emitter-monomorphize.do"
            collectExpression(call->callee, modulePath, analysis, plan, names, arguments);
#line 258 "/src/emitter-monomorphize.do"
            const auto& _iterable_34 = call->args;
            for (const auto& argument : *_iterable_34) {
#line 258 "/src/emitter-monomorphize.do"
                collectExpression(argument->value, modulePath, analysis, plan, names, arguments);
            }
#line 259 "/src/emitter-monomorphize.do"
            if ((!doof::is_null(call->resolvedFunction)) && ((static_cast<int32_t>((call->resolvedFunction->typeParams)->size()) > 0) || call->resolvedFunction->native_)) {
#line 260 "/src/emitter-monomorphize.do"
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> concreteArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 261 "/src/emitter-monomorphize.do"
                const auto& _iterable_36 = call->resolvedGenericTypeArgs;
                for (const auto& argument : *_iterable_36) {
#line 261 "/src/emitter-monomorphize.do"
                    concreteArgs->push_back(specialize(argument, names, arguments));
                }
#line 262 "/src/emitter-monomorphize.do"
                if (!containsTypeParameters(concreteArgs)) {
#line 263 "/src/emitter-monomorphize.do"
                    auto recordedMethod = false;
#line 264 "/src/emitter-monomorphize.do"
                    {
                        auto _case_subject = call->callee;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
                            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 266 "/src/emitter-monomorphize.do"
                            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 267 "/src/emitter-monomorphize.do"
                                {
                                    auto _case_subject = specialize(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)), names, arguments);
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                                        const auto& ownerType = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 269 "/src/emitter-monomorphize.do"
                                        const auto owner = classDeclaration(analysis, ownerType->symbol->module, ownerType->symbol->name);
#line 270 "/src/emitter-monomorphize.do"
                                        if ((!doof::is_null(owner)) && (static_cast<int32_t>((call->resolvedFunction->typeParams)->size()) > 0)) {
#line 271 "/src/emitter-monomorphize.do"
                                            if (static_cast<int32_t>((owner->typeParams)->size()) == 0) {
#line 272 "/src/emitter-monomorphize.do"
                                                collectTemplateMethodBody(plan, ownerType, doof::unwrap_optional(call->resolvedFunction), concreteArgs, analysis);
                                            } else {
#line 274 "/src/emitter-monomorphize.do"
                                                addMethod(plan, ownerType, doof::unwrap_optional(owner), doof::unwrap_optional(call->resolvedFunction), concreteArgs);
                                            }
#line 276 "/src/emitter-monomorphize.do"
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
#line 285 "/src/emitter-monomorphize.do"
                    if (!recordedMethod) {
#line 286 "/src/emitter-monomorphize.do"
                        const auto targetModule = functionModule(call, modulePath);
#line 287 "/src/emitter-monomorphize.do"
                        addFunction(plan, targetModule, doof::unwrap_optional(call->resolvedFunction), concreteArgs);
                    }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 292 "/src/emitter-monomorphize.do"
            const auto& _iterable_38 = array->elements;
            for (const auto& item : *_iterable_38) {
#line 292 "/src/emitter-monomorphize.do"
                collectExpression(item, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 294 "/src/emitter-monomorphize.do"
            if (!doof::is_null(object->spread)) {
#line 294 "/src/emitter-monomorphize.do"
                collectExpression(doof::unwrap_optional(object->spread), modulePath, analysis, plan, names, arguments);
            }
#line 295 "/src/emitter-monomorphize.do"
            const auto& _iterable_40 = object->properties;
            for (const auto& property : *_iterable_40) {
#line 296 "/src/emitter-monomorphize.do"
                if (!doof::is_null(property->key)) {
#line 296 "/src/emitter-monomorphize.do"
                    collectExpression(doof::unwrap_optional(property->key), modulePath, analysis, plan, names, arguments);
                }
#line 297 "/src/emitter-monomorphize.do"
                if (!doof::is_null(property->value)) {
#line 297 "/src/emitter-monomorphize.do"
                    collectExpression(doof::unwrap_optional(property->value), modulePath, analysis, plan, names, arguments);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
#line 300 "/src/emitter-monomorphize.do"
            const auto& _iterable_42 = tuple->elements;
            for (const auto& item : *_iterable_42) {
#line 300 "/src/emitter-monomorphize.do"
                collectExpression(item, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
#line 302 "/src/emitter-monomorphize.do"
            const auto& _iterable_44 = lambda->params;
            for (const auto& parameter : *_iterable_44) {
#line 302 "/src/emitter-monomorphize.do"
                if (!doof::is_null(parameter->defaultValue)) {
#line 302 "/src/emitter-monomorphize.do"
                    collectExpression(doof::unwrap_optional(parameter->defaultValue), modulePath, analysis, plan, names, arguments);
                }
            }
#line 303 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = lambda->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 304 "/src/emitter-monomorphize.do"
                    collectBlock(block, modulePath, analysis, plan, names, arguments);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 305 "/src/emitter-monomorphize.do"
                    collectExpression(inner, modulePath, analysis, plan, names, arguments);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
#line 308 "/src/emitter-monomorphize.do"
            collectExpression(if_->condition, modulePath, analysis, plan, names, arguments);
#line 308 "/src/emitter-monomorphize.do"
            collectExpression(if_->then_, modulePath, analysis, plan, names, arguments);
#line 308 "/src/emitter-monomorphize.do"
            collectExpression(if_->else_, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
#line 310 "/src/emitter-monomorphize.do"
            collectExpression(case_->subject, modulePath, analysis, plan, names, arguments);
#line 311 "/src/emitter-monomorphize.do"
            const auto& _iterable_46 = case_->arms;
            for (const auto& arm : *_iterable_46) {
#line 312 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 313 "/src/emitter-monomorphize.do"
                        collectBlock(block, modulePath, analysis, plan, names, arguments);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 314 "/src/emitter-monomorphize.do"
                        collectExpression(bodyExpression, modulePath, analysis, plan, names, arguments);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
#line 318 "/src/emitter-monomorphize.do"
            const auto& _iterable_48 = construct->args;
            for (const auto& property : *_iterable_48) {
#line 318 "/src/emitter-monomorphize.do"
                if (!doof::is_null(property->value)) {
#line 318 "/src/emitter-monomorphize.do"
                    collectExpression(doof::unwrap_optional(property->value), modulePath, analysis, plan, names, arguments);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
#line 320 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = async_->expression;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 321 "/src/emitter-monomorphize.do"
                    collectBlock(block, modulePath, analysis, plan, names, arguments);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 322 "/src/emitter-monomorphize.do"
                    collectExpression(inner, modulePath, analysis, plan, names, arguments);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
#line 325 "/src/emitter-monomorphize.do"
            collectExpression(retire_->actor, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
#line 326 "/src/emitter-monomorphize.do"
            const auto& _iterable_50 = actor->args;
            for (const auto& argument : *_iterable_50) {
#line 326 "/src/emitter-monomorphize.do"
                collectExpression(argument, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
#line 327 "/src/emitter-monomorphize.do"
            collectBlock(yieldBlock->body, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
#line 328 "/src/emitter-monomorphize.do"
            collectBlock(catch_->body, modulePath, analysis, plan, names, arguments);
    }
    else {
    }
    }
}
#line 333 "/src/emitter-monomorphize.do"
void collectTemplateMethodBody(const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<::app_src_semantic_::ClassType>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 334 "/src/emitter-monomorphize.do"
    const auto ownerKey = ((owner->symbol->module + std::string("::class::")) + owner->symbol->name);
#line 335 "/src/emitter-monomorphize.do"
    const auto key = methodInstantiationKey(ownerKey, method->name, typeArgs);
#line 336 "/src/emitter-monomorphize.do"
    if (containsString(plan->visitedTemplateMethodKeys, key)) {
#line 336 "/src/emitter-monomorphize.do"
        return;
    }
#line 337 "/src/emitter-monomorphize.do"
    plan->visitedTemplateMethodKeys->push_back(key);
#line 338 "/src/emitter-monomorphize.do"
    collectFunctionBody(method, owner->symbol->module, analysis, plan, method->typeParams, typeArgs);
}
#line 341 "/src/emitter-monomorphize.do"
void collectJsonMemberDemand(const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 342 "/src/emitter-monomorphize.do"
    if (doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 342 "/src/emitter-monomorphize.do"
        return;
    }
#line 343 "/src/emitter-monomorphize.do"
    const auto receiver = specialize(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)), names, arguments);
#line 344 "/src/emitter-monomorphize.do"
    if (member->property == std::string("toJsonObject")) {
#line 345 "/src/emitter-monomorphize.do"
        addJsonSerializationDemand(plan, receiver, analysis);
#line 346 "/src/emitter-monomorphize.do"
        return;
    }
#line 348 "/src/emitter-monomorphize.do"
    if (member->property == std::string("fromJsonValue")) {
#line 349 "/src/emitter-monomorphize.do"
        {
            auto _case_subject = receiver;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 350 "/src/emitter-monomorphize.do"
                addInterfaceJsonDeserializationDemand(plan, interface_, analysis);
        }
        else {
#line 351 "/src/emitter-monomorphize.do"
                addJsonDeserializationDemand(plan, receiver, analysis);
        }
        }
#line 353 "/src/emitter-monomorphize.do"
        return;
    }
#line 355 "/src/emitter-monomorphize.do"
    if (member->property != std::string("metadata")) {
#line 355 "/src/emitter-monomorphize.do"
        return;
    }
#line 356 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = receiver;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 358 "/src/emitter-monomorphize.do"
            const auto owner = classDeclaration(analysis, class_->symbol->module, class_->symbol->name);
#line 359 "/src/emitter-monomorphize.do"
            if (doof::is_null(owner)) {
#line 359 "/src/emitter-monomorphize.do"
                return;
            }
#line 360 "/src/emitter-monomorphize.do"
            const auto& _iterable_52 = owner->methods;
            for (const auto& method : *_iterable_52) {
#line 361 "/src/emitter-monomorphize.do"
                if (method->private_ || method->static_) {
#line 361 "/src/emitter-monomorphize.do"
                    continue;
                }
#line 362 "/src/emitter-monomorphize.do"
                const auto& _iterable_54 = method->params;
                for (const auto& parameter : *_iterable_54) {
#line 363 "/src/emitter-monomorphize.do"
                    if (!doof::is_null(parameter->resolvedType)) {
#line 364 "/src/emitter-monomorphize.do"
                        addJsonDeserializationDemand(plan, specialize(doof::unwrap_optional(parameter->resolvedType), names, arguments), analysis);
                    }
                }
#line 367 "/src/emitter-monomorphize.do"
                if (doof::is_null(method->resolvedType)) {
#line 367 "/src/emitter-monomorphize.do"
                    continue;
                }
#line 368 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = specialize(doof::unwrap_optional(method->resolvedType), names, arguments);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                        const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 370 "/src/emitter-monomorphize.do"
                        {
                            auto _case_subject = function_->returnType;
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 371 "/src/emitter-monomorphize.do"
                                addJsonSerializationDemand(plan, result->valueType, analysis);
                        }
                        else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(_case_subject)) {
                                const auto returnType = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(_case_subject);
#line 372 "/src/emitter-monomorphize.do"
                                addJsonSerializationDemand(plan, returnType, analysis);
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
#line 383 "/src/emitter-monomorphize.do"
void addJsonSerializationDemand(const std::shared_ptr<InstantiationPlan>& plan, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 384 "/src/emitter-monomorphize.do"
    addJsonDemand(plan, type_, analysis, true);
}
#line 387 "/src/emitter-monomorphize.do"
void addJsonDeserializationDemand(const std::shared_ptr<InstantiationPlan>& plan, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 388 "/src/emitter-monomorphize.do"
    addJsonDemand(plan, type_, analysis, false);
}
#line 391 "/src/emitter-monomorphize.do"
void addJsonDemand(const std::shared_ptr<InstantiationPlan>& plan, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, bool serialization) {
#line 392 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 394 "/src/emitter-monomorphize.do"
            if ((static_cast<int32_t>((class_->typeArgs)->size()) > 0) || class_->symbol->native_) {
#line 394 "/src/emitter-monomorphize.do"
                return;
            }
#line 395 "/src/emitter-monomorphize.do"
            const auto owner = classDeclaration(analysis, class_->symbol->module, class_->symbol->name);
#line 396 "/src/emitter-monomorphize.do"
            if (doof::is_null(owner)) {
#line 396 "/src/emitter-monomorphize.do"
                return;
            }
#line 397 "/src/emitter-monomorphize.do"
            const auto key = ((class_->symbol->module + std::string("::")) + class_->symbol->name);
#line 398 "/src/emitter-monomorphize.do"
            const auto keys = (serialization ? plan->jsonSerializationKeys : plan->jsonDeserializationKeys);
#line 399 "/src/emitter-monomorphize.do"
            if (containsString(keys, key)) {
#line 399 "/src/emitter-monomorphize.do"
                return;
            }
#line 400 "/src/emitter-monomorphize.do"
            keys->push_back(key);
#line 401 "/src/emitter-monomorphize.do"
            const auto& _iterable_56 = owner->fields;
            for (const auto& field : *_iterable_56) {
#line 402 "/src/emitter-monomorphize.do"
                if (field->static_ || doof::is_null(field->resolvedType)) {
#line 402 "/src/emitter-monomorphize.do"
                    continue;
                }
#line 403 "/src/emitter-monomorphize.do"
                addJsonDemand(plan, doof::unwrap_optional(field->resolvedType), analysis, serialization);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 406 "/src/emitter-monomorphize.do"
            addJsonDemand(plan, array->elementType, analysis, serialization);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 407 "/src/emitter-monomorphize.do"
            addJsonDemand(plan, map->valueType, analysis, serialization);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 408 "/src/emitter-monomorphize.do"
            const auto& _iterable_58 = tuple->elements;
            for (const auto& element : *_iterable_58) {
#line 408 "/src/emitter-monomorphize.do"
                addJsonDemand(plan, element, analysis, serialization);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 409 "/src/emitter-monomorphize.do"
            const auto& _iterable_60 = union_->types;
            for (const auto& member : *_iterable_60) {
#line 409 "/src/emitter-monomorphize.do"
                addJsonDemand(plan, member, analysis, serialization);
            }
    }
    else {
    }
    }
}
#line 414 "/src/emitter-monomorphize.do"
void addInterfaceJsonDeserializationDemand(const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<::app_src_semantic_::InterfaceType>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 415 "/src/emitter-monomorphize.do"
    const auto declaration = interfaceDeclaration(analysis, type_->symbol->module, type_->symbol->name);
#line 416 "/src/emitter-monomorphize.do"
    if (doof::is_null(declaration) || doof::is_null(declaration->resolvedSymbol)) {
#line 416 "/src/emitter-monomorphize.do"
        return;
    }
#line 417 "/src/emitter-monomorphize.do"
    const auto& _iterable_62 = declaration->resolvedSymbol->implementations;
    for (const auto& implementation : *_iterable_62) {
#line 418 "/src/emitter-monomorphize.do"
        addJsonDeserializationDemand(plan, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::ClassType>(std::string("class"), implementation->name, implementation, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}))), analysis);
    }
}
#line 422 "/src/emitter-monomorphize.do"
void collectOptionalType(const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan) {
#line 423 "/src/emitter-monomorphize.do"
    if (!doof::is_null(type_)) {
#line 423 "/src/emitter-monomorphize.do"
        collectType(specialize(doof::unwrap_optional(type_), names, arguments), analysis, plan);
    }
}
#line 426 "/src/emitter-monomorphize.do"
void collectType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan) {
#line 427 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 429 "/src/emitter-monomorphize.do"
            const auto& _iterable_64 = class_->typeArgs;
            for (const auto& argument : *_iterable_64) {
#line 429 "/src/emitter-monomorphize.do"
                collectType(argument, analysis, plan);
            }
#line 430 "/src/emitter-monomorphize.do"
            if ((static_cast<int32_t>((class_->typeArgs)->size()) > 0) && !containsTypeParameters(class_->typeArgs)) {
#line 431 "/src/emitter-monomorphize.do"
                const auto declaration = classDeclaration(analysis, class_->symbol->module, class_->symbol->name);
#line 432 "/src/emitter-monomorphize.do"
                if ((!doof::is_null(declaration)) && !declaration->native_) {
#line 432 "/src/emitter-monomorphize.do"
                    addClass(plan, class_->symbol->module, doof::unwrap_optional(declaration), class_->typeArgs);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 436 "/src/emitter-monomorphize.do"
            const auto& _iterable_66 = interface_->typeArgs;
            for (const auto& argument : *_iterable_66) {
#line 436 "/src/emitter-monomorphize.do"
                collectType(argument, analysis, plan);
            }
#line 437 "/src/emitter-monomorphize.do"
            if ((static_cast<int32_t>((interface_->typeArgs)->size()) > 0) && !containsTypeParameters(interface_->typeArgs)) {
#line 437 "/src/emitter-monomorphize.do"
                addInterface(plan, interface_->symbol->module, interface_->name, interface_->typeArgs);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 439 "/src/emitter-monomorphize.do"
            collectType(array->elementType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 440 "/src/emitter-monomorphize.do"
            collectType(map->keyType, analysis, plan);
#line 440 "/src/emitter-monomorphize.do"
            collectType(map->valueType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 441 "/src/emitter-monomorphize.do"
            collectType(set_->elementType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 442 "/src/emitter-monomorphize.do"
            collectType(stream->elementType, analysis, plan);
#line 442 "/src/emitter-monomorphize.do"
            addInterface(plan, std::string(""), std::string("Stream"), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{stream->elementType}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 443 "/src/emitter-monomorphize.do"
            collectType(result->valueType, analysis, plan);
#line 443 "/src/emitter-monomorphize.do"
            collectType(result->errorType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 444 "/src/emitter-monomorphize.do"
            collectType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 445 "/src/emitter-monomorphize.do"
            collectType(promise->valueType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 446 "/src/emitter-monomorphize.do"
            const auto& _iterable_68 = tuple->elements;
            for (const auto& element : *_iterable_68) {
#line 446 "/src/emitter-monomorphize.do"
                collectType(element, analysis, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 447 "/src/emitter-monomorphize.do"
            const auto& _iterable_70 = union_->types;
            for (const auto& member : *_iterable_70) {
#line 447 "/src/emitter-monomorphize.do"
                collectType(member, analysis, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 448 "/src/emitter-monomorphize.do"
            collectType(weak_->inner, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 450 "/src/emitter-monomorphize.do"
            const auto& _iterable_72 = function_->params;
            for (const auto& parameter : *_iterable_72) {
#line 450 "/src/emitter-monomorphize.do"
                collectType(parameter->type_, analysis, plan);
            }
#line 451 "/src/emitter-monomorphize.do"
            collectType(function_->returnType, analysis, plan);
    }
    else {
    }
    }
}
#line 457 "/src/emitter-monomorphize.do"
void addFunction(const std::shared_ptr<InstantiationPlan>& plan, const std::string& modulePath, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 458 "/src/emitter-monomorphize.do"
    const auto key = functionInstantiationKey(modulePath, declaration->name, typeArgs);
#line 459 "/src/emitter-monomorphize.do"
    const auto& _iterable_74 = plan->functions;
    for (const auto& existing : *_iterable_74) {
#line 459 "/src/emitter-monomorphize.do"
        if (existing->key == key) {
#line 459 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 460 "/src/emitter-monomorphize.do"
    const auto emittedName = concreteName(declaration->name, typeArgs);
#line 461 "/src/emitter-monomorphize.do"
    plan->functions->push_back(std::make_shared<FunctionInstantiation>(key, modulePath, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(declaration->typeParams, typeArgs), emittedName, extendedTrace(plan->currentTrace, emittedName)));
}
#line 464 "/src/emitter-monomorphize.do"
void addClass(const std::shared_ptr<InstantiationPlan>& plan, const std::string& modulePath, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& declaration, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 465 "/src/emitter-monomorphize.do"
    const auto key = classInstantiationKey(modulePath, declaration->name, typeArgs);
#line 466 "/src/emitter-monomorphize.do"
    if (containsString(plan->nativeTemplateClassKeys, nativeTemplateClassKey(modulePath, declaration->name))) {
#line 466 "/src/emitter-monomorphize.do"
        return;
    }
#line 467 "/src/emitter-monomorphize.do"
    const auto& _iterable_76 = plan->classes;
    for (const auto& existing : *_iterable_76) {
#line 467 "/src/emitter-monomorphize.do"
        if (existing->key == key) {
#line 467 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 468 "/src/emitter-monomorphize.do"
    const auto emittedName = concreteName(declaration->name, typeArgs);
#line 469 "/src/emitter-monomorphize.do"
    plan->classes->push_back(std::make_shared<ClassInstantiation>(key, modulePath, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(declaration->typeParams, typeArgs), emittedName, extendedTrace(plan->currentTrace, emittedName)));
}
#line 472 "/src/emitter-monomorphize.do"
std::string nativeTemplateClassKey(const std::string& modulePath, const std::string& name) {
    return ((modulePath + std::string("::")) + name);
}
#line 474 "/src/emitter-monomorphize.do"
void discoverNativeTemplateClasses(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan) {
#line 475 "/src/emitter-monomorphize.do"
    const auto& _iterable_78 = analysis->modules;
    for (const auto& module : *_iterable_78) {
#line 476 "/src/emitter-monomorphize.do"
        const auto& _iterable_80 = module->program->statements;
        for (const auto& statement : *_iterable_80) {
#line 476 "/src/emitter-monomorphize.do"
            discoverNativeTemplateClassesInStatement(statement, plan);
        }
    }
}
#line 480 "/src/emitter-monomorphize.do"
void discoverNativeTemplateClassesInStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<InstantiationPlan>& plan) {
#line 481 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 483 "/src/emitter-monomorphize.do"
            if (!class_->native_) {
#line 483 "/src/emitter-monomorphize.do"
                return;
            }
#line 484 "/src/emitter-monomorphize.do"
            const auto& _iterable_82 = class_->fields;
            for (const auto& field : *_iterable_82) {
#line 484 "/src/emitter-monomorphize.do"
                if (!doof::is_null(field->resolvedType)) {
#line 484 "/src/emitter-monomorphize.do"
                    collectNativeTemplateClasses(doof::unwrap_optional(field->resolvedType), plan);
                }
            }
#line 485 "/src/emitter-monomorphize.do"
            const auto& _iterable_84 = class_->methods;
            for (const auto& method : *_iterable_84) {
#line 485 "/src/emitter-monomorphize.do"
                if (!doof::is_null(method->resolvedType)) {
#line 485 "/src/emitter-monomorphize.do"
                    collectNativeTemplateClasses(doof::unwrap_optional(method->resolvedType), plan);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 487 "/src/emitter-monomorphize.do"
            if (fn->native_ && (!doof::is_null(fn->resolvedType))) {
#line 487 "/src/emitter-monomorphize.do"
                collectNativeTemplateClasses(doof::unwrap_optional(fn->resolvedType), plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 488 "/src/emitter-monomorphize.do"
            discoverNativeTemplateClassesInStatement(export_->declaration, plan);
    }
    else {
    }
    }
}
#line 493 "/src/emitter-monomorphize.do"
void collectNativeTemplateClasses(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<InstantiationPlan>& plan) {
#line 494 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 496 "/src/emitter-monomorphize.do"
            if (!class_->symbol->native_ && (static_cast<int32_t>((class_->typeArgs)->size()) > 0)) {
#line 496 "/src/emitter-monomorphize.do"
                addString(plan->nativeTemplateClassKeys, nativeTemplateClassKey(class_->symbol->module, class_->name));
            }
#line 497 "/src/emitter-monomorphize.do"
            const auto& _iterable_86 = class_->typeArgs;
            for (const auto& argument : *_iterable_86) {
#line 497 "/src/emitter-monomorphize.do"
                collectNativeTemplateClasses(argument, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 499 "/src/emitter-monomorphize.do"
            const auto& _iterable_88 = interface_->typeArgs;
            for (const auto& argument : *_iterable_88) {
#line 499 "/src/emitter-monomorphize.do"
                collectNativeTemplateClasses(argument, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 500 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(array->elementType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 501 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(map->keyType, plan);
#line 501 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(map->valueType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 502 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(set_->elementType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 503 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(stream->elementType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 504 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(result_->valueType, plan);
#line 504 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(result_->errorType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 505 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 506 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(promise->valueType, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 507 "/src/emitter-monomorphize.do"
            const auto& _iterable_90 = tuple->elements;
            for (const auto& element : *_iterable_90) {
#line 507 "/src/emitter-monomorphize.do"
                collectNativeTemplateClasses(element, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 508 "/src/emitter-monomorphize.do"
            const auto& _iterable_92 = union_->types;
            for (const auto& member : *_iterable_92) {
#line 508 "/src/emitter-monomorphize.do"
                collectNativeTemplateClasses(member, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 509 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(weak_->inner, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 511 "/src/emitter-monomorphize.do"
            const auto& _iterable_94 = function_->params;
            for (const auto& parameter : *_iterable_94) {
#line 511 "/src/emitter-monomorphize.do"
                collectNativeTemplateClasses(parameter->type_, plan);
            }
#line 512 "/src/emitter-monomorphize.do"
            collectNativeTemplateClasses(function_->returnType, plan);
    }
    else {
    }
    }
}
#line 518 "/src/emitter-monomorphize.do"
void addString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 519 "/src/emitter-monomorphize.do"
    if (!containsString(values, value)) {
#line 519 "/src/emitter-monomorphize.do"
        values->push_back(value);
    }
}
#line 522 "/src/emitter-monomorphize.do"
bool containsString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 523 "/src/emitter-monomorphize.do"
    const auto& _iterable_96 = values;
    for (const auto& existing : *_iterable_96) {
#line 523 "/src/emitter-monomorphize.do"
        if (existing == value) {
#line 523 "/src/emitter-monomorphize.do"
            return true;
        }
    }
#line 524 "/src/emitter-monomorphize.do"
    return false;
}
#line 527 "/src/emitter-monomorphize.do"
void addInterface(const std::shared_ptr<InstantiationPlan>& plan, const std::string& modulePath, const std::string& name, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 528 "/src/emitter-monomorphize.do"
    if (containsTypeParameters(typeArgs)) {
#line 528 "/src/emitter-monomorphize.do"
        return;
    }
#line 529 "/src/emitter-monomorphize.do"
    const auto key = interfaceInstantiationKey(modulePath, name, typeArgs);
#line 530 "/src/emitter-monomorphize.do"
    const auto& _iterable_98 = plan->interfaces;
    for (const auto& existing : *_iterable_98) {
#line 530 "/src/emitter-monomorphize.do"
        if (existing->key == key) {
#line 530 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 531 "/src/emitter-monomorphize.do"
    plan->interfaces->push_back(std::make_shared<InterfaceInstantiation>(key, modulePath, name, std::make_shared<::app_src_semantic_::TypeSubstitution>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), typeArgs), concreteName(name, typeArgs), std::make_shared<std::vector<std::shared_ptr<ImplementationRef>>>(std::vector<std::shared_ptr<ImplementationRef>>{})));
}
#line 534 "/src/emitter-monomorphize.do"
void addMethod(const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<::app_src_semantic_::ClassType>& ownerType, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& methodArgs) {
#line 538 "/src/emitter-monomorphize.do"
    if (static_cast<int32_t>((owner->typeParams)->size()) == 0) {
#line 538 "/src/emitter-monomorphize.do"
        return;
    }
#line 539 "/src/emitter-monomorphize.do"
    const auto ownerKey = classInstantiationKey(ownerType->symbol->module, ownerType->name, ownerType->typeArgs);
#line 540 "/src/emitter-monomorphize.do"
    const auto key = methodInstantiationKey(ownerKey, declaration->name, methodArgs);
#line 541 "/src/emitter-monomorphize.do"
    const auto& _iterable_100 = plan->methods;
    for (const auto& existing : *_iterable_100) {
#line 541 "/src/emitter-monomorphize.do"
        if (existing->key == key) {
#line 541 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 542 "/src/emitter-monomorphize.do"
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 543 "/src/emitter-monomorphize.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 544 "/src/emitter-monomorphize.do"
    const auto& _iterable_102 = owner->typeParams;
    for (const auto& name : *_iterable_102) {
#line 544 "/src/emitter-monomorphize.do"
        names->push_back(name);
    }
#line 545 "/src/emitter-monomorphize.do"
    const auto& _iterable_104 = ownerType->typeArgs;
    for (const auto& argument : *_iterable_104) {
#line 545 "/src/emitter-monomorphize.do"
        arguments->push_back(argument);
    }
#line 546 "/src/emitter-monomorphize.do"
    const auto& _iterable_106 = declaration->typeParams;
    for (const auto& name : *_iterable_106) {
#line 546 "/src/emitter-monomorphize.do"
        names->push_back(name);
    }
#line 547 "/src/emitter-monomorphize.do"
    const auto& _iterable_108 = methodArgs;
    for (const auto& argument : *_iterable_108) {
#line 547 "/src/emitter-monomorphize.do"
        arguments->push_back(argument);
    }
#line 548 "/src/emitter-monomorphize.do"
    plan->methods->push_back(std::make_shared<MethodInstantiation>(key, ownerType->symbol->module, ownerKey, owner, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(names, arguments), concreteName(declaration->name, methodArgs), extendedTrace(plan->currentTrace, concreteName(((owner->name + std::string("__")) + declaration->name), methodArgs))));
}
#line 555 "/src/emitter-monomorphize.do"
std::shared_ptr<std::vector<std::string>> extendedTrace(const std::shared_ptr<std::vector<std::string>>& parent, const std::string& item) {
#line 556 "/src/emitter-monomorphize.do"
    std::shared_ptr<std::vector<std::string>> trace = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 558 "/src/emitter-monomorphize.do"
    auto start = ((static_cast<int32_t>((parent)->size()) > 11) ? (static_cast<int32_t>((parent)->size()) - 11) : 0);
#line 559 "/src/emitter-monomorphize.do"
    for (int32_t index = start; index < static_cast<int32_t>((parent)->size()); ++index) {
#line 559 "/src/emitter-monomorphize.do"
        trace->push_back(doof::array_at(parent, index, "src/emitter-monomorphize", 559));
    }
#line 560 "/src/emitter-monomorphize.do"
    trace->push_back(item);
#line 561 "/src/emitter-monomorphize.do"
    return trace;
}
#line 564 "/src/emitter-monomorphize.do"
void discoverConcreteInterfaceImplementations(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan) {
#line 565 "/src/emitter-monomorphize.do"
    const auto& _iterable_111 = plan->interfaces;
    for (const auto& interface_ : *_iterable_111) {
#line 566 "/src/emitter-monomorphize.do"
        const auto& _iterable_113 = analysis->modules;
        for (const auto& module : *_iterable_113) {
#line 567 "/src/emitter-monomorphize.do"
            const auto& _iterable_115 = module->program->statements;
            for (const auto& statement : *_iterable_115) {
#line 568 "/src/emitter-monomorphize.do"
                std::shared_ptr<::app_src_ast_::ClassDeclaration> candidate = nullptr;
#line 569 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = statement;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 570 "/src/emitter-monomorphize.do"
                        (candidate = class_);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                        const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 572 "/src/emitter-monomorphize.do"
                        {
                            auto _case_subject = export_->declaration;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 573 "/src/emitter-monomorphize.do"
                                (candidate = class_);
                        }
                        else {
                        }
                        }
                }
                else {
                }
                }
#line 579 "/src/emitter-monomorphize.do"
                if ((((!doof::is_null(candidate)) && (static_cast<int32_t>((candidate->typeParams)->size()) == 0)) && !candidate->struct_) && classImplementsConcreteInterface(doof::unwrap_optional(candidate), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), interface_, analysis)) {
#line 580 "/src/emitter-monomorphize.do"
                    addImplementation(interface_, module->path, candidate->name);
                }
            }
        }
#line 584 "/src/emitter-monomorphize.do"
        const auto& _iterable_117 = plan->classes;
        for (const auto& class_ : *_iterable_117) {
#line 585 "/src/emitter-monomorphize.do"
            if (class_->declaration->struct_) {
#line 585 "/src/emitter-monomorphize.do"
                continue;
            }
#line 586 "/src/emitter-monomorphize.do"
            if (classImplementsConcreteInterface(class_->declaration, class_->substitution->arguments, interface_, analysis)) {
#line 587 "/src/emitter-monomorphize.do"
                addImplementation(interface_, class_->modulePath, class_->emittedName);
            }
        }
    }
}
#line 593 "/src/emitter-monomorphize.do"
void addImplementation(const std::shared_ptr<InterfaceInstantiation>& interface_, const std::string& modulePath, const std::string& typeName_) {
#line 594 "/src/emitter-monomorphize.do"
    const auto& _iterable_119 = interface_->implementations;
    for (const auto& existing : *_iterable_119) {
#line 594 "/src/emitter-monomorphize.do"
        if ((existing->modulePath == modulePath) && (existing->typeName == typeName_)) {
#line 594 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 595 "/src/emitter-monomorphize.do"
    interface_->implementations->push_back(std::make_shared<ImplementationRef>(modulePath, typeName_));
}
#line 598 "/src/emitter-monomorphize.do"
bool classImplementsConcreteInterface(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& classArgs, const std::shared_ptr<InterfaceInstantiation>& interface_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 599 "/src/emitter-monomorphize.do"
    if (interface_->name == std::string("Stream")) {
#line 600 "/src/emitter-monomorphize.do"
        const auto& _iterable_121 = class_->implements_;
        for (const auto& implementation : *_iterable_121) {
#line 601 "/src/emitter-monomorphize.do"
            if (doof::is_null(implementation->resolvedType)) {
#line 601 "/src/emitter-monomorphize.do"
                continue;
            }
#line 602 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = specialize(doof::unwrap_optional(implementation->resolvedType), class_->typeParams, classArgs);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                    const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 603 "/src/emitter-monomorphize.do"
                    if (::app_src_checker_types_::sameType(stream->elementType, doof::array_at(interface_->substitution->arguments, 0, "src/emitter-monomorphize", 603))) {
#line 603 "/src/emitter-monomorphize.do"
                        return true;
                    }
            }
            else {
            }
            }
        }
#line 607 "/src/emitter-monomorphize.do"
        const auto next = classMethod(class_, std::string("next"));
#line 608 "/src/emitter-monomorphize.do"
        const auto value = classMethod(class_, std::string("value"));
#line 609 "/src/emitter-monomorphize.do"
        if (((doof::is_null(next) || doof::is_null(value)) || doof::is_null(next->resolvedType)) || doof::is_null(value->resolvedType)) {
#line 609 "/src/emitter-monomorphize.do"
            return false;
        }
#line 610 "/src/emitter-monomorphize.do"
        const auto nextType = specialize(doof::unwrap_optional(next->resolvedType), class_->typeParams, classArgs);
#line 611 "/src/emitter-monomorphize.do"
        const auto valueType = specialize(doof::unwrap_optional(value->resolvedType), class_->typeParams, classArgs);
#line 612 "/src/emitter-monomorphize.do"
        {
            auto _case_subject = nextType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 613 "/src/emitter-monomorphize.do"
                if ((::app_src_checker_types_::typeName(fn->returnType) != std::string("bool")) || (static_cast<int32_t>((fn->params)->size()) != 0)) {
#line 613 "/src/emitter-monomorphize.do"
                    return false;
                }
        }
        else {
#line 614 "/src/emitter-monomorphize.do"
                return false;
        }
        }
#line 616 "/src/emitter-monomorphize.do"
        {
            auto _case_subject = valueType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 617 "/src/emitter-monomorphize.do"
                return ((static_cast<int32_t>((fn->params)->size()) == 0) && ::app_src_checker_types_::sameType(fn->returnType, doof::array_at(interface_->substitution->arguments, 0, "src/emitter-monomorphize", 617)));
        }
        else {
#line 618 "/src/emitter-monomorphize.do"
                return false;
        }
        }
        doof::unreachable();
    }
#line 621 "/src/emitter-monomorphize.do"
    const auto declaration = interfaceDeclaration(analysis, interface_->modulePath, interface_->name);
#line 622 "/src/emitter-monomorphize.do"
    if (doof::is_null(declaration)) {
#line 622 "/src/emitter-monomorphize.do"
        return false;
    }
#line 623 "/src/emitter-monomorphize.do"
    const auto& _iterable_123 = declaration->fields;
    for (const auto& required : *_iterable_123) {
#line 624 "/src/emitter-monomorphize.do"
        const auto actual = classField(class_, required->name);
#line 625 "/src/emitter-monomorphize.do"
        if ((doof::is_null(actual) || doof::is_null(actual->resolvedType)) || doof::is_null(required->resolvedType)) {
#line 625 "/src/emitter-monomorphize.do"
            return false;
        }
#line 626 "/src/emitter-monomorphize.do"
        const auto actualType = specialize(doof::unwrap_optional(actual->resolvedType), class_->typeParams, classArgs);
#line 627 "/src/emitter-monomorphize.do"
        const auto requiredType = specialize(doof::unwrap_optional(required->resolvedType), declaration->typeParams, interface_->substitution->arguments);
#line 628 "/src/emitter-monomorphize.do"
        if (!::app_src_checker_types_::isAssignable(actualType, requiredType)) {
#line 628 "/src/emitter-monomorphize.do"
            return false;
        }
    }
#line 630 "/src/emitter-monomorphize.do"
    const auto& _iterable_125 = declaration->methods;
    for (const auto& required : *_iterable_125) {
#line 631 "/src/emitter-monomorphize.do"
        const auto actual = classMethod(class_, required->name);
#line 632 "/src/emitter-monomorphize.do"
        if ((doof::is_null(actual) || doof::is_null(actual->resolvedType)) || doof::is_null(required->resolvedType)) {
#line 632 "/src/emitter-monomorphize.do"
            return false;
        }
#line 633 "/src/emitter-monomorphize.do"
        const auto actualType = specialize(doof::unwrap_optional(actual->resolvedType), class_->typeParams, classArgs);
#line 634 "/src/emitter-monomorphize.do"
        const auto requiredType = specialize(doof::unwrap_optional(required->resolvedType), declaration->typeParams, interface_->substitution->arguments);
#line 635 "/src/emitter-monomorphize.do"
        if (!sameConcreteMethodType(actualType, requiredType)) {
#line 635 "/src/emitter-monomorphize.do"
            return false;
        }
    }
#line 637 "/src/emitter-monomorphize.do"
    return true;
}
#line 640 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::ClassField> classField(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& name) {
#line 641 "/src/emitter-monomorphize.do"
    const auto& _iterable_127 = class_->fields;
    for (const auto& field : *_iterable_127) {
#line 641 "/src/emitter-monomorphize.do"
        const auto& _iterable_129 = field->names;
        for (const auto& fieldName : *_iterable_129) {
#line 641 "/src/emitter-monomorphize.do"
            if (fieldName == name) {
#line 641 "/src/emitter-monomorphize.do"
                return field;
            }
        }
    }
#line 642 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 645 "/src/emitter-monomorphize.do"
bool sameConcreteMethodType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& actual, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 646 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = actual;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& actualFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 648 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = expected;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                    const auto& expectedFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 650 "/src/emitter-monomorphize.do"
                    if (static_cast<int32_t>((actualFunction->params)->size()) != static_cast<int32_t>((expectedFunction->params)->size())) {
#line 650 "/src/emitter-monomorphize.do"
                        return false;
                    }
#line 651 "/src/emitter-monomorphize.do"
                    for (int32_t index = 0; index < static_cast<int32_t>((actualFunction->params)->size()); ++index) {
#line 652 "/src/emitter-monomorphize.do"
                        if (!::app_src_checker_types_::sameType(doof::array_at(actualFunction->params, index, "src/emitter-monomorphize", 652)->type_, doof::array_at(expectedFunction->params, index, "src/emitter-monomorphize", 652)->type_)) {
#line 652 "/src/emitter-monomorphize.do"
                            return false;
                        }
                    }
#line 654 "/src/emitter-monomorphize.do"
                    return ::app_src_checker_types_::sameType(actualFunction->returnType, expectedFunction->returnType);
            }
            else {
#line 656 "/src/emitter-monomorphize.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 659 "/src/emitter-monomorphize.do"
            return ::app_src_checker_types_::sameType(actual, expected);
    }
    }
    doof::unreachable();
#line 661 "/src/emitter-monomorphize.do"
    return false;
}
#line 664 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> classMethod(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& name) {
#line 665 "/src/emitter-monomorphize.do"
    const auto& _iterable_132 = class_->methods;
    for (const auto& method : *_iterable_132) {
#line 665 "/src/emitter-monomorphize.do"
        if ((method->name == name) && !method->static_) {
#line 665 "/src/emitter-monomorphize.do"
            return method;
        }
    }
#line 666 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 669 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::InterfaceDeclaration> interfaceDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::string& modulePath, const std::string& name) {
#line 670 "/src/emitter-monomorphize.do"
    const auto& _iterable_134 = analysis->modules;
    for (const auto& module : *_iterable_134) {
#line 671 "/src/emitter-monomorphize.do"
        if (module->path != modulePath) {
#line 671 "/src/emitter-monomorphize.do"
            continue;
        }
#line 672 "/src/emitter-monomorphize.do"
        const auto& _iterable_136 = module->program->statements;
        for (const auto& statement : *_iterable_136) {
#line 673 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = statement;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 674 "/src/emitter-monomorphize.do"
                    if (interface_->name == name) {
#line 674 "/src/emitter-monomorphize.do"
                        return interface_;
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                    const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 676 "/src/emitter-monomorphize.do"
                    {
                        auto _case_subject = export_->declaration;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 677 "/src/emitter-monomorphize.do"
                            if (interface_->name == name) {
#line 677 "/src/emitter-monomorphize.do"
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
#line 685 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 688 "/src/emitter-monomorphize.do"
std::string functionModule(const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::string& fallback) {
#line 689 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = call->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 691 "/src/emitter-monomorphize.do"
            if (!doof::is_null(identifier->resolvedBinding)) {
#line 692 "/src/emitter-monomorphize.do"
                if (!doof::is_null(identifier->resolvedBinding->symbol)) {
#line 692 "/src/emitter-monomorphize.do"
                    return identifier->resolvedBinding->symbol->module;
                }
#line 693 "/src/emitter-monomorphize.do"
                if (identifier->resolvedBinding->module != std::string("")) {
#line 693 "/src/emitter-monomorphize.do"
                    return identifier->resolvedBinding->module;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 697 "/src/emitter-monomorphize.do"
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 698 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 699 "/src/emitter-monomorphize.do"
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
#line 706 "/src/emitter-monomorphize.do"
    return fallback;
}
#line 709 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> classDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::string& modulePath, const std::string& name) {
#line 710 "/src/emitter-monomorphize.do"
    const auto& _iterable_138 = analysis->modules;
    for (const auto& module : *_iterable_138) {
#line 711 "/src/emitter-monomorphize.do"
        if (module->path != modulePath) {
#line 711 "/src/emitter-monomorphize.do"
            continue;
        }
#line 712 "/src/emitter-monomorphize.do"
        const auto& _iterable_140 = module->program->statements;
        for (const auto& statement : *_iterable_140) {
#line 713 "/src/emitter-monomorphize.do"
            const auto declaration = classFromStatement(statement, name);
#line 714 "/src/emitter-monomorphize.do"
            if (!doof::is_null(declaration)) {
#line 714 "/src/emitter-monomorphize.do"
                return declaration;
            }
        }
    }
#line 717 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 720 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> classFromStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::string& name) {
#line 721 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 722 "/src/emitter-monomorphize.do"
            if (class_->name == name) {
#line 722 "/src/emitter-monomorphize.do"
                return class_;
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 723 "/src/emitter-monomorphize.do"
            return classFromStatement(export_->declaration, name);
    }
    else {
    }
    }
#line 726 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 729 "/src/emitter-monomorphize.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> specialize(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 730 "/src/emitter-monomorphize.do"
    if (static_cast<int32_t>((names)->size()) == 0) {
#line 730 "/src/emitter-monomorphize.do"
        return type_;
    }
#line 731 "/src/emitter-monomorphize.do"
    return ::app_src_checker_types_::substituteTypeParams(type_, names, arguments);
}
#line 734 "/src/emitter-monomorphize.do"
bool containsTypeParameters(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& types) {
#line 735 "/src/emitter-monomorphize.do"
    const auto& _iterable_142 = types;
    for (const auto& type_ : *_iterable_142) {
#line 735 "/src/emitter-monomorphize.do"
        if (containsTypeParameter(type_)) {
#line 735 "/src/emitter-monomorphize.do"
            return true;
        }
    }
#line 736 "/src/emitter-monomorphize.do"
    return false;
}
#line 739 "/src/emitter-monomorphize.do"
bool containsTypeParameter(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 740 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
#line 741 "/src/emitter-monomorphize.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 742 "/src/emitter-monomorphize.do"
            return containsTypeParameters(class_->typeArgs);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 743 "/src/emitter-monomorphize.do"
            return containsTypeParameters(interface_->typeArgs);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 744 "/src/emitter-monomorphize.do"
            return containsTypeParameter(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 745 "/src/emitter-monomorphize.do"
            return (containsTypeParameter(map->keyType) || containsTypeParameter(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 746 "/src/emitter-monomorphize.do"
            return containsTypeParameter(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 747 "/src/emitter-monomorphize.do"
            return containsTypeParameter(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 748 "/src/emitter-monomorphize.do"
            return (containsTypeParameter(result->valueType) || containsTypeParameter(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 749 "/src/emitter-monomorphize.do"
            return containsTypeParameter(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 750 "/src/emitter-monomorphize.do"
            return containsTypeParameter(promise->valueType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 751 "/src/emitter-monomorphize.do"
            return containsTypeParameters(tuple->elements);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 752 "/src/emitter-monomorphize.do"
            return containsTypeParameters(union_->types);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 753 "/src/emitter-monomorphize.do"
            return containsTypeParameter(weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 755 "/src/emitter-monomorphize.do"
            const auto& _iterable_144 = function_->params;
            for (const auto& parameter : *_iterable_144) {
#line 755 "/src/emitter-monomorphize.do"
                if (containsTypeParameter(parameter->type_)) {
#line 755 "/src/emitter-monomorphize.do"
                    return true;
                }
            }
#line 756 "/src/emitter-monomorphize.do"
            return containsTypeParameter(function_->returnType);
    }
    else {
#line 758 "/src/emitter-monomorphize.do"
            return false;
    }
    }
    doof::unreachable();
#line 760 "/src/emitter-monomorphize.do"
    return false;
}
#line 763 "/src/emitter-monomorphize.do"
std::string concreteTypeListKey(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& types) {
#line 764 "/src/emitter-monomorphize.do"
    auto result = std::string("");
#line 765 "/src/emitter-monomorphize.do"
    const auto& _iterable_146 = types;
    for (const auto& type_ : *_iterable_146) {
#line 765 "/src/emitter-monomorphize.do"
        (result = (((result + std::string("[")) + canonicalTypeKey(type_)) + std::string("]")));
    }
#line 766 "/src/emitter-monomorphize.do"
    return result;
}
#line 769 "/src/emitter-monomorphize.do"
std::string canonicalTypeKey(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 770 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 771 "/src/emitter-monomorphize.do"
            return ((((std::string("class:") + class_->symbol->module) + std::string(":")) + class_->name) + concreteTypeListKey(class_->typeArgs));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 772 "/src/emitter-monomorphize.do"
            return ((((std::string("interface:") + interface_->symbol->module) + std::string(":")) + interface_->name) + concreteTypeListKey(interface_->typeArgs));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 773 "/src/emitter-monomorphize.do"
            return ((array->readonly_ ? std::string("readonly-array:") : std::string("array:")) + canonicalTypeKey(array->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 774 "/src/emitter-monomorphize.do"
            return ((((map->readonly_ ? std::string("readonly-map:") : std::string("map:")) + canonicalTypeKey(map->keyType)) + std::string(":")) + canonicalTypeKey(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 775 "/src/emitter-monomorphize.do"
            return ((set_->readonly_ ? std::string("readonly-set:") : std::string("set:")) + canonicalTypeKey(set_->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 776 "/src/emitter-monomorphize.do"
            return (std::string("stream:") + canonicalTypeKey(stream->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 777 "/src/emitter-monomorphize.do"
            return (((std::string("result:") + canonicalTypeKey(result->valueType)) + std::string(":")) + canonicalTypeKey(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 778 "/src/emitter-monomorphize.do"
            return (std::string("actor:") + canonicalTypeKey(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 779 "/src/emitter-monomorphize.do"
            return (std::string("promise:") + canonicalTypeKey(promise->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 780 "/src/emitter-monomorphize.do"
            return (std::string("tuple:") + concreteTypeListKey(tuple->elements));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 781 "/src/emitter-monomorphize.do"
            return (std::string("union:") + concreteTypeListKey(union_->types));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 782 "/src/emitter-monomorphize.do"
            return (std::string("weak:") + canonicalTypeKey(weak_->inner));
    }
    else {
#line 783 "/src/emitter-monomorphize.do"
            return ::app_src_checker_types_::typeName(type_);
    }
    }
    doof::unreachable();
#line 785 "/src/emitter-monomorphize.do"
    return ::app_src_checker_types_::typeName(type_);
}
#line 788 "/src/emitter-monomorphize.do"
std::string mangleType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 789 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 790 "/src/emitter-monomorphize.do"
            return sanitize(((((::app_src_emitter_names_::moduleNamespace(class_->symbol->module) + std::string("_")) + class_->name) + std::string("_")) + concreteTypeListMangle(class_->typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 791 "/src/emitter-monomorphize.do"
            return sanitize(((((::app_src_emitter_names_::moduleNamespace(interface_->symbol->module) + std::string("_")) + interface_->name) + std::string("_")) + concreteTypeListMangle(interface_->typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 792 "/src/emitter-monomorphize.do"
            return ((array->readonly_ ? std::string("readonly_array_") : std::string("array_")) + mangleType(array->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 793 "/src/emitter-monomorphize.do"
            return ((((map->readonly_ ? std::string("readonly_map_") : std::string("map_")) + mangleType(map->keyType)) + std::string("_")) + mangleType(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 794 "/src/emitter-monomorphize.do"
            return ((set_->readonly_ ? std::string("readonly_set_") : std::string("set_")) + mangleType(set_->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 795 "/src/emitter-monomorphize.do"
            return (std::string("stream_") + mangleType(stream->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 796 "/src/emitter-monomorphize.do"
            return (((std::string("result_") + mangleType(result->valueType)) + std::string("_")) + mangleType(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 797 "/src/emitter-monomorphize.do"
            return (std::string("actor_") + mangleType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 798 "/src/emitter-monomorphize.do"
            return (std::string("promise_") + mangleType(promise->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 799 "/src/emitter-monomorphize.do"
            return (std::string("tuple_") + concreteTypeListMangle(tuple->elements));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 800 "/src/emitter-monomorphize.do"
            return (std::string("union_") + concreteTypeListMangle(union_->types));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 801 "/src/emitter-monomorphize.do"
            return (std::string("weak_") + mangleType(weak_->inner));
    }
    else {
#line 802 "/src/emitter-monomorphize.do"
            return sanitize(::app_src_checker_types_::typeName(type_));
    }
    }
    doof::unreachable();
#line 804 "/src/emitter-monomorphize.do"
    return std::string("type");
}
#line 807 "/src/emitter-monomorphize.do"
std::string concreteTypeListMangle(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& types) {
#line 808 "/src/emitter-monomorphize.do"
    auto result = std::string("");
#line 809 "/src/emitter-monomorphize.do"
    const auto& _iterable_148 = types;
    for (const auto& type_ : *_iterable_148) {
#line 810 "/src/emitter-monomorphize.do"
        if (result != std::string("")) {
#line 810 "/src/emitter-monomorphize.do"
            (result = (result + std::string("_")));
        }
#line 811 "/src/emitter-monomorphize.do"
        (result = (result + mangleType(type_)));
    }
#line 813 "/src/emitter-monomorphize.do"
    return result;
}
#line 816 "/src/emitter-monomorphize.do"
std::string sanitize(const std::string& value) {
#line 817 "/src/emitter-monomorphize.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("/"), std::string("_")), std::string("."), std::string("_")), std::string("<"), std::string("_")), std::string(">"), std::string("_")), std::string(","), std::string("_")), std::string(" "), std::string("_")), std::string("|"), std::string("_")), std::string("["), std::string("_")), std::string("]"), std::string("_")), std::string(":"), std::string("_")), std::string("("), std::string("_")), std::string(")"), std::string("_"));
}
#line 1 "<doof-generated>"
}
