#include "src_emitter_monomorphize.hpp"

namespace app_src_emitter_monomorphize_ {
using namespace ::app_src_ast_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_names_;






#line 83 "/src/emitter-monomorphize.do"
std::shared_ptr<InstantiationPlan> buildInstantiationPlan(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 84 "/src/emitter-monomorphize.do"
    const auto plan = std::make_shared<InstantiationPlan>(std::make_shared<std::vector<std::shared_ptr<FunctionInstantiation>>>(std::vector<std::shared_ptr<FunctionInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<ClassInstantiation>>>(std::vector<std::shared_ptr<ClassInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<InterfaceInstantiation>>>(std::vector<std::shared_ptr<InterfaceInstantiation>>{}), std::make_shared<std::vector<std::shared_ptr<MethodInstantiation>>>(std::vector<std::shared_ptr<MethodInstantiation>>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
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
                                            if (!owner->native_) {
#line 271 "/src/emitter-monomorphize.do"
                                                addMethod(plan, ownerType, doof::unwrap_optional(owner), doof::unwrap_optional(call->resolvedFunction), concreteArgs);
                                            }
#line 272 "/src/emitter-monomorphize.do"
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
#line 281 "/src/emitter-monomorphize.do"
                    if (!recordedMethod) {
#line 282 "/src/emitter-monomorphize.do"
                        const auto targetModule = functionModule(call, modulePath);
#line 283 "/src/emitter-monomorphize.do"
                        addFunction(plan, targetModule, doof::unwrap_optional(call->resolvedFunction), concreteArgs);
                    }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayLiteral>>(_case_subject);
#line 288 "/src/emitter-monomorphize.do"
            const auto& _iterable_38 = array->elements;
            for (const auto& item : *_iterable_38) {
#line 288 "/src/emitter-monomorphize.do"
                collectExpression(item, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject)) {
            const auto& object = std::get<std::shared_ptr<::app_src_ast_::ObjectLiteral>>(_case_subject);
#line 290 "/src/emitter-monomorphize.do"
            if (!doof::is_null(object->spread)) {
#line 290 "/src/emitter-monomorphize.do"
                collectExpression(doof::unwrap_optional(object->spread), modulePath, analysis, plan, names, arguments);
            }
#line 291 "/src/emitter-monomorphize.do"
            const auto& _iterable_40 = object->properties;
            for (const auto& property : *_iterable_40) {
#line 292 "/src/emitter-monomorphize.do"
                if (!doof::is_null(property->key)) {
#line 292 "/src/emitter-monomorphize.do"
                    collectExpression(doof::unwrap_optional(property->key), modulePath, analysis, plan, names, arguments);
                }
#line 293 "/src/emitter-monomorphize.do"
                if (!doof::is_null(property->value)) {
#line 293 "/src/emitter-monomorphize.do"
                    collectExpression(doof::unwrap_optional(property->value), modulePath, analysis, plan, names, arguments);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_ast_::TupleLiteral>>(_case_subject);
#line 296 "/src/emitter-monomorphize.do"
            const auto& _iterable_42 = tuple->elements;
            for (const auto& item : *_iterable_42) {
#line 296 "/src/emitter-monomorphize.do"
                collectExpression(item, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject)) {
            const auto& lambda = std::get<std::shared_ptr<::app_src_ast_::LambdaExpression>>(_case_subject);
#line 298 "/src/emitter-monomorphize.do"
            const auto& _iterable_44 = lambda->params;
            for (const auto& parameter : *_iterable_44) {
#line 298 "/src/emitter-monomorphize.do"
                if (!doof::is_null(parameter->defaultValue)) {
#line 298 "/src/emitter-monomorphize.do"
                    collectExpression(doof::unwrap_optional(parameter->defaultValue), modulePath, analysis, plan, names, arguments);
                }
            }
#line 299 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = lambda->body;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 300 "/src/emitter-monomorphize.do"
                    collectBlock(block, modulePath, analysis, plan, names, arguments);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 301 "/src/emitter-monomorphize.do"
                    collectExpression(inner, modulePath, analysis, plan, names, arguments);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject)) {
            const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfExpression>>(_case_subject);
#line 304 "/src/emitter-monomorphize.do"
            collectExpression(if_->condition, modulePath, analysis, plan, names, arguments);
#line 304 "/src/emitter-monomorphize.do"
            collectExpression(if_->then_, modulePath, analysis, plan, names, arguments);
#line 304 "/src/emitter-monomorphize.do"
            collectExpression(if_->else_, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject)) {
            const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseExpression>>(_case_subject);
#line 306 "/src/emitter-monomorphize.do"
            collectExpression(case_->subject, modulePath, analysis, plan, names, arguments);
#line 307 "/src/emitter-monomorphize.do"
            const auto& _iterable_46 = case_->arms;
            for (const auto& arm : *_iterable_46) {
#line 308 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = arm->body;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                        const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 309 "/src/emitter-monomorphize.do"
                        collectBlock(block, modulePath, analysis, plan, names, arguments);
                }
                else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                        const auto bodyExpression = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 310 "/src/emitter-monomorphize.do"
                        collectExpression(bodyExpression, modulePath, analysis, plan, names, arguments);
                }
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject)) {
            const auto& construct = std::get<std::shared_ptr<::app_src_ast_::ConstructExpression>>(_case_subject);
#line 314 "/src/emitter-monomorphize.do"
            const auto& _iterable_48 = construct->args;
            for (const auto& property : *_iterable_48) {
#line 314 "/src/emitter-monomorphize.do"
                if (!doof::is_null(property->value)) {
#line 314 "/src/emitter-monomorphize.do"
                    collectExpression(doof::unwrap_optional(property->value), modulePath, analysis, plan, names, arguments);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject)) {
            const auto& async_ = std::get<std::shared_ptr<::app_src_ast_::AsyncExpression>>(_case_subject);
#line 316 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = async_->expression;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                    const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 317 "/src/emitter-monomorphize.do"
                    collectBlock(block, modulePath, analysis, plan, names, arguments);
            }
            else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
                    const auto inner = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject);
#line 318 "/src/emitter-monomorphize.do"
                    collectExpression(inner, modulePath, analysis, plan, names, arguments);
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject)) {
            const auto& retire_ = std::get<std::shared_ptr<::app_src_ast_::RetireExpression>>(_case_subject);
#line 321 "/src/emitter-monomorphize.do"
            collectExpression(retire_->actor, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_ast_::ActorCreationExpression>>(_case_subject);
#line 322 "/src/emitter-monomorphize.do"
            const auto& _iterable_50 = actor->args;
            for (const auto& argument : *_iterable_50) {
#line 322 "/src/emitter-monomorphize.do"
                collectExpression(argument, modulePath, analysis, plan, names, arguments);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject)) {
            const auto& yieldBlock = std::get<std::shared_ptr<::app_src_ast_::YieldBlockExpression>>(_case_subject);
#line 323 "/src/emitter-monomorphize.do"
            collectBlock(yieldBlock->body, modulePath, analysis, plan, names, arguments);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject)) {
            const auto& catch_ = std::get<std::shared_ptr<::app_src_ast_::CatchExpression>>(_case_subject);
#line 324 "/src/emitter-monomorphize.do"
            collectBlock(catch_->body, modulePath, analysis, plan, names, arguments);
    }
    else {
    }
    }
}
#line 329 "/src/emitter-monomorphize.do"
void collectJsonMemberDemand(const std::shared_ptr<::app_src_ast_::MemberExpression>& member, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 330 "/src/emitter-monomorphize.do"
    if (doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 330 "/src/emitter-monomorphize.do"
        return;
    }
#line 331 "/src/emitter-monomorphize.do"
    const auto receiver = specialize(doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object)), names, arguments);
#line 332 "/src/emitter-monomorphize.do"
    if (member->property == std::string("toJsonObject")) {
#line 333 "/src/emitter-monomorphize.do"
        addJsonSerializationDemand(plan, receiver, analysis);
#line 334 "/src/emitter-monomorphize.do"
        return;
    }
#line 336 "/src/emitter-monomorphize.do"
    if (member->property == std::string("fromJsonValue")) {
#line 337 "/src/emitter-monomorphize.do"
        {
            auto _case_subject = receiver;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 338 "/src/emitter-monomorphize.do"
                addInterfaceJsonDeserializationDemand(plan, interface_, analysis);
        }
        else {
#line 339 "/src/emitter-monomorphize.do"
                addJsonDeserializationDemand(plan, receiver, analysis);
        }
        }
#line 341 "/src/emitter-monomorphize.do"
        return;
    }
#line 343 "/src/emitter-monomorphize.do"
    if (member->property != std::string("metadata")) {
#line 343 "/src/emitter-monomorphize.do"
        return;
    }
#line 344 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = receiver;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 346 "/src/emitter-monomorphize.do"
            const auto owner = classDeclaration(analysis, class_->symbol->module, class_->symbol->name);
#line 347 "/src/emitter-monomorphize.do"
            if (doof::is_null(owner)) {
#line 347 "/src/emitter-monomorphize.do"
                return;
            }
#line 348 "/src/emitter-monomorphize.do"
            const auto& _iterable_52 = owner->methods;
            for (const auto& method : *_iterable_52) {
#line 349 "/src/emitter-monomorphize.do"
                if (method->private_ || method->static_) {
#line 349 "/src/emitter-monomorphize.do"
                    continue;
                }
#line 350 "/src/emitter-monomorphize.do"
                const auto& _iterable_54 = method->params;
                for (const auto& parameter : *_iterable_54) {
#line 351 "/src/emitter-monomorphize.do"
                    if (!doof::is_null(parameter->resolvedType)) {
#line 352 "/src/emitter-monomorphize.do"
                        addJsonDeserializationDemand(plan, specialize(doof::unwrap_optional(parameter->resolvedType), names, arguments), analysis);
                    }
                }
#line 355 "/src/emitter-monomorphize.do"
                if (doof::is_null(method->resolvedType)) {
#line 355 "/src/emitter-monomorphize.do"
                    continue;
                }
#line 356 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = specialize(doof::unwrap_optional(method->resolvedType), names, arguments);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                        const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 358 "/src/emitter-monomorphize.do"
                        {
                            auto _case_subject = function_->returnType;
                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 359 "/src/emitter-monomorphize.do"
                                addJsonSerializationDemand(plan, result->valueType, analysis);
                        }
                        else if (doof::variant_is<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(_case_subject)) {
                                const auto returnType = doof::variant_narrow<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(_case_subject);
#line 360 "/src/emitter-monomorphize.do"
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
#line 371 "/src/emitter-monomorphize.do"
void addJsonSerializationDemand(const std::shared_ptr<InstantiationPlan>& plan, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 372 "/src/emitter-monomorphize.do"
    addJsonDemand(plan, type_, analysis, true);
}
#line 375 "/src/emitter-monomorphize.do"
void addJsonDeserializationDemand(const std::shared_ptr<InstantiationPlan>& plan, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 376 "/src/emitter-monomorphize.do"
    addJsonDemand(plan, type_, analysis, false);
}
#line 379 "/src/emitter-monomorphize.do"
void addJsonDemand(const std::shared_ptr<InstantiationPlan>& plan, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, bool serialization) {
#line 380 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 382 "/src/emitter-monomorphize.do"
            if ((static_cast<int32_t>((class_->typeArgs)->size()) > 0) || class_->symbol->native_) {
#line 382 "/src/emitter-monomorphize.do"
                return;
            }
#line 383 "/src/emitter-monomorphize.do"
            const auto owner = classDeclaration(analysis, class_->symbol->module, class_->symbol->name);
#line 384 "/src/emitter-monomorphize.do"
            if (doof::is_null(owner)) {
#line 384 "/src/emitter-monomorphize.do"
                return;
            }
#line 385 "/src/emitter-monomorphize.do"
            const auto key = ((class_->symbol->module + std::string("::")) + class_->symbol->name);
#line 386 "/src/emitter-monomorphize.do"
            const auto keys = (serialization ? plan->jsonSerializationKeys : plan->jsonDeserializationKeys);
#line 387 "/src/emitter-monomorphize.do"
            if (containsString(keys, key)) {
#line 387 "/src/emitter-monomorphize.do"
                return;
            }
#line 388 "/src/emitter-monomorphize.do"
            keys->push_back(key);
#line 389 "/src/emitter-monomorphize.do"
            const auto& _iterable_56 = owner->fields;
            for (const auto& field : *_iterable_56) {
#line 390 "/src/emitter-monomorphize.do"
                if (field->static_ || doof::is_null(field->resolvedType)) {
#line 390 "/src/emitter-monomorphize.do"
                    continue;
                }
#line 391 "/src/emitter-monomorphize.do"
                addJsonDemand(plan, doof::unwrap_optional(field->resolvedType), analysis, serialization);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 394 "/src/emitter-monomorphize.do"
            addJsonDemand(plan, array->elementType, analysis, serialization);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 395 "/src/emitter-monomorphize.do"
            addJsonDemand(plan, map->valueType, analysis, serialization);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 396 "/src/emitter-monomorphize.do"
            const auto& _iterable_58 = tuple->elements;
            for (const auto& element : *_iterable_58) {
#line 396 "/src/emitter-monomorphize.do"
                addJsonDemand(plan, element, analysis, serialization);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 397 "/src/emitter-monomorphize.do"
            const auto& _iterable_60 = union_->types;
            for (const auto& member : *_iterable_60) {
#line 397 "/src/emitter-monomorphize.do"
                addJsonDemand(plan, member, analysis, serialization);
            }
    }
    else {
    }
    }
}
#line 402 "/src/emitter-monomorphize.do"
void addInterfaceJsonDeserializationDemand(const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<::app_src_semantic_::InterfaceType>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 403 "/src/emitter-monomorphize.do"
    const auto declaration = interfaceDeclaration(analysis, type_->symbol->module, type_->symbol->name);
#line 404 "/src/emitter-monomorphize.do"
    if (doof::is_null(declaration) || doof::is_null(declaration->resolvedSymbol)) {
#line 404 "/src/emitter-monomorphize.do"
        return;
    }
#line 405 "/src/emitter-monomorphize.do"
    const auto& _iterable_62 = declaration->resolvedSymbol->implementations;
    for (const auto& implementation : *_iterable_62) {
#line 406 "/src/emitter-monomorphize.do"
        addJsonDeserializationDemand(plan, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(std::make_shared<::app_src_semantic_::ClassType>(std::string("class"), implementation->name, implementation, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}))), analysis);
    }
}
#line 410 "/src/emitter-monomorphize.do"
void collectOptionalType(const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan) {
#line 411 "/src/emitter-monomorphize.do"
    if (!doof::is_null(type_)) {
#line 411 "/src/emitter-monomorphize.do"
        collectType(specialize(doof::unwrap_optional(type_), names, arguments), analysis, plan);
    }
}
#line 414 "/src/emitter-monomorphize.do"
void collectType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan) {
#line 415 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 417 "/src/emitter-monomorphize.do"
            const auto& _iterable_64 = class_->typeArgs;
            for (const auto& argument : *_iterable_64) {
#line 417 "/src/emitter-monomorphize.do"
                collectType(argument, analysis, plan);
            }
#line 418 "/src/emitter-monomorphize.do"
            if ((static_cast<int32_t>((class_->typeArgs)->size()) > 0) && !containsTypeParameters(class_->typeArgs)) {
#line 419 "/src/emitter-monomorphize.do"
                const auto declaration = classDeclaration(analysis, class_->symbol->module, class_->symbol->name);
#line 420 "/src/emitter-monomorphize.do"
                if ((!doof::is_null(declaration)) && !declaration->native_) {
#line 420 "/src/emitter-monomorphize.do"
                    addClass(plan, class_->symbol->module, doof::unwrap_optional(declaration), class_->typeArgs);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 424 "/src/emitter-monomorphize.do"
            const auto& _iterable_66 = interface_->typeArgs;
            for (const auto& argument : *_iterable_66) {
#line 424 "/src/emitter-monomorphize.do"
                collectType(argument, analysis, plan);
            }
#line 425 "/src/emitter-monomorphize.do"
            if ((static_cast<int32_t>((interface_->typeArgs)->size()) > 0) && !containsTypeParameters(interface_->typeArgs)) {
#line 425 "/src/emitter-monomorphize.do"
                addInterface(plan, interface_->symbol->module, interface_->name, interface_->typeArgs);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 427 "/src/emitter-monomorphize.do"
            collectType(array->elementType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 428 "/src/emitter-monomorphize.do"
            collectType(map->keyType, analysis, plan);
#line 428 "/src/emitter-monomorphize.do"
            collectType(map->valueType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 429 "/src/emitter-monomorphize.do"
            collectType(set_->elementType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 430 "/src/emitter-monomorphize.do"
            collectType(stream->elementType, analysis, plan);
#line 430 "/src/emitter-monomorphize.do"
            addInterface(plan, std::string(""), std::string("Stream"), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{stream->elementType}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 431 "/src/emitter-monomorphize.do"
            collectType(result->valueType, analysis, plan);
#line 431 "/src/emitter-monomorphize.do"
            collectType(result->errorType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 432 "/src/emitter-monomorphize.do"
            collectType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 433 "/src/emitter-monomorphize.do"
            collectType(promise->valueType, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 434 "/src/emitter-monomorphize.do"
            const auto& _iterable_68 = tuple->elements;
            for (const auto& element : *_iterable_68) {
#line 434 "/src/emitter-monomorphize.do"
                collectType(element, analysis, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 435 "/src/emitter-monomorphize.do"
            const auto& _iterable_70 = union_->types;
            for (const auto& member : *_iterable_70) {
#line 435 "/src/emitter-monomorphize.do"
                collectType(member, analysis, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 436 "/src/emitter-monomorphize.do"
            collectType(weak_->inner, analysis, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 438 "/src/emitter-monomorphize.do"
            const auto& _iterable_72 = function_->params;
            for (const auto& parameter : *_iterable_72) {
#line 438 "/src/emitter-monomorphize.do"
                collectType(parameter->type_, analysis, plan);
            }
#line 439 "/src/emitter-monomorphize.do"
            collectType(function_->returnType, analysis, plan);
    }
    else {
    }
    }
}
#line 445 "/src/emitter-monomorphize.do"
void addFunction(const std::shared_ptr<InstantiationPlan>& plan, const std::string& modulePath, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 446 "/src/emitter-monomorphize.do"
    const auto key = functionInstantiationKey(modulePath, declaration->name, typeArgs);
#line 447 "/src/emitter-monomorphize.do"
    const auto& _iterable_74 = plan->functions;
    for (const auto& existing : *_iterable_74) {
#line 447 "/src/emitter-monomorphize.do"
        if (existing->key == key) {
#line 447 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 448 "/src/emitter-monomorphize.do"
    const auto emittedName = allocateConcreteName(plan, (std::string("module:") + modulePath), concreteName(declaration->name, typeArgs));
#line 449 "/src/emitter-monomorphize.do"
    plan->functions->push_back(std::make_shared<FunctionInstantiation>(key, modulePath, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(declaration->typeParams, typeArgs), emittedName, extendedTrace(plan->currentTrace, emittedName)));
}
#line 452 "/src/emitter-monomorphize.do"
void addClass(const std::shared_ptr<InstantiationPlan>& plan, const std::string& modulePath, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& declaration, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 453 "/src/emitter-monomorphize.do"
    const auto key = classInstantiationKey(modulePath, declaration->name, typeArgs);
#line 454 "/src/emitter-monomorphize.do"
    const auto& _iterable_76 = plan->classes;
    for (const auto& existing : *_iterable_76) {
#line 454 "/src/emitter-monomorphize.do"
        if (existing->key == key) {
#line 454 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 455 "/src/emitter-monomorphize.do"
    const auto emittedName = allocateConcreteName(plan, (std::string("module:") + modulePath), concreteName(declaration->name, typeArgs));
#line 456 "/src/emitter-monomorphize.do"
    plan->classes->push_back(std::make_shared<ClassInstantiation>(key, modulePath, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(declaration->typeParams, typeArgs), emittedName, extendedTrace(plan->currentTrace, emittedName)));
}
#line 459 "/src/emitter-monomorphize.do"
bool containsString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 460 "/src/emitter-monomorphize.do"
    const auto& _iterable_78 = values;
    for (const auto& existing : *_iterable_78) {
#line 460 "/src/emitter-monomorphize.do"
        if (existing == value) {
#line 460 "/src/emitter-monomorphize.do"
            return true;
        }
    }
#line 461 "/src/emitter-monomorphize.do"
    return false;
}
#line 464 "/src/emitter-monomorphize.do"
void addInterface(const std::shared_ptr<InstantiationPlan>& plan, const std::string& modulePath, const std::string& name, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& typeArgs) {
#line 465 "/src/emitter-monomorphize.do"
    if (containsTypeParameters(typeArgs)) {
#line 465 "/src/emitter-monomorphize.do"
        return;
    }
#line 466 "/src/emitter-monomorphize.do"
    const auto key = interfaceInstantiationKey(modulePath, name, typeArgs);
#line 467 "/src/emitter-monomorphize.do"
    const auto& _iterable_80 = plan->interfaces;
    for (const auto& existing : *_iterable_80) {
#line 467 "/src/emitter-monomorphize.do"
        if (existing->key == key) {
#line 467 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 468 "/src/emitter-monomorphize.do"
    const auto emittedName = allocateConcreteName(plan, (std::string("module:") + modulePath), concreteName(name, typeArgs));
#line 469 "/src/emitter-monomorphize.do"
    plan->interfaces->push_back(std::make_shared<InterfaceInstantiation>(key, modulePath, name, std::make_shared<::app_src_semantic_::TypeSubstitution>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), typeArgs), emittedName, std::make_shared<std::vector<std::shared_ptr<ImplementationRef>>>(std::vector<std::shared_ptr<ImplementationRef>>{})));
}
#line 472 "/src/emitter-monomorphize.do"
void addMethod(const std::shared_ptr<InstantiationPlan>& plan, const std::shared_ptr<::app_src_semantic_::ClassType>& ownerType, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& declaration, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& methodArgs) {
#line 473 "/src/emitter-monomorphize.do"
    const auto ownerKey = ((static_cast<int32_t>((owner->typeParams)->size()) == 0) ? classInstantiationKey(ownerType->symbol->module, owner->name, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})) : classInstantiationKey(ownerType->symbol->module, owner->name, ownerType->typeArgs));
#line 476 "/src/emitter-monomorphize.do"
    auto ownerEmittedName = owner->name;
#line 477 "/src/emitter-monomorphize.do"
    if (static_cast<int32_t>((owner->typeParams)->size()) > 0) {
#line 478 "/src/emitter-monomorphize.do"
        const auto& _iterable_82 = plan->classes;
        for (const auto& existing : *_iterable_82) {
#line 478 "/src/emitter-monomorphize.do"
            if (existing->key == ownerKey) {
#line 478 "/src/emitter-monomorphize.do"
                (ownerEmittedName = existing->emittedName);
            }
        }
    }
#line 480 "/src/emitter-monomorphize.do"
    const auto key = methodInstantiationKey(ownerKey, declaration->name, methodArgs);
#line 481 "/src/emitter-monomorphize.do"
    const auto& _iterable_84 = plan->methods;
    for (const auto& existing : *_iterable_84) {
#line 481 "/src/emitter-monomorphize.do"
        if (existing->key == key) {
#line 481 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 482 "/src/emitter-monomorphize.do"
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 483 "/src/emitter-monomorphize.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 484 "/src/emitter-monomorphize.do"
    const auto& _iterable_86 = owner->typeParams;
    for (const auto& name : *_iterable_86) {
#line 484 "/src/emitter-monomorphize.do"
        names->push_back(name);
    }
#line 485 "/src/emitter-monomorphize.do"
    const auto& _iterable_88 = ownerType->typeArgs;
    for (const auto& argument : *_iterable_88) {
#line 485 "/src/emitter-monomorphize.do"
        arguments->push_back(argument);
    }
#line 486 "/src/emitter-monomorphize.do"
    const auto& _iterable_90 = declaration->typeParams;
    for (const auto& name : *_iterable_90) {
#line 486 "/src/emitter-monomorphize.do"
        names->push_back(name);
    }
#line 487 "/src/emitter-monomorphize.do"
    const auto& _iterable_92 = methodArgs;
    for (const auto& argument : *_iterable_92) {
#line 487 "/src/emitter-monomorphize.do"
        arguments->push_back(argument);
    }
#line 488 "/src/emitter-monomorphize.do"
    const auto emittedName = allocateConcreteName(plan, (std::string("owner:") + ownerKey), concreteName(declaration->name, methodArgs));
#line 489 "/src/emitter-monomorphize.do"
    plan->methods->push_back(std::make_shared<MethodInstantiation>(key, ownerType->symbol->module, ownerKey, owner, declaration, std::make_shared<::app_src_semantic_::TypeSubstitution>(names, arguments), ownerEmittedName, emittedName, extendedTrace(plan->currentTrace, ((ownerEmittedName + std::string("__")) + emittedName))));
}
#line 497 "/src/emitter-monomorphize.do"
std::string allocateConcreteName(const std::shared_ptr<InstantiationPlan>& plan, const std::string& scope, const std::string& base) {
#line 498 "/src/emitter-monomorphize.do"
    auto candidate = base;
#line 499 "/src/emitter-monomorphize.do"
    auto suffix = 2;
#line 500 "/src/emitter-monomorphize.do"
    while (concreteNameAllocated(plan, scope, candidate)) {
#line 501 "/src/emitter-monomorphize.do"
        (candidate = ((base + std::string("_")) + doof::to_string(suffix)));
#line 502 "/src/emitter-monomorphize.do"
        (suffix = (suffix + 1));
    }
#line 504 "/src/emitter-monomorphize.do"
    plan->concreteNameScopes->push_back(scope);
#line 505 "/src/emitter-monomorphize.do"
    plan->concreteNames->push_back(candidate);
#line 506 "/src/emitter-monomorphize.do"
    return candidate;
}
#line 509 "/src/emitter-monomorphize.do"
bool concreteNameAllocated(const std::shared_ptr<InstantiationPlan>& plan, const std::string& scope, const std::string& name) {
#line 510 "/src/emitter-monomorphize.do"
    for (int32_t index = 0; index < static_cast<int32_t>((plan->concreteNames)->size()); ++index) {
#line 511 "/src/emitter-monomorphize.do"
        if ((doof::array_at(plan->concreteNameScopes, index, "src/emitter-monomorphize", 511) == scope) && (doof::array_at(plan->concreteNames, index, "src/emitter-monomorphize", 511) == name)) {
#line 511 "/src/emitter-monomorphize.do"
            return true;
        }
    }
#line 513 "/src/emitter-monomorphize.do"
    return false;
}
#line 516 "/src/emitter-monomorphize.do"
std::shared_ptr<std::vector<std::string>> extendedTrace(const std::shared_ptr<std::vector<std::string>>& parent, const std::string& item) {
#line 517 "/src/emitter-monomorphize.do"
    std::shared_ptr<std::vector<std::string>> trace = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 519 "/src/emitter-monomorphize.do"
    auto start = ((static_cast<int32_t>((parent)->size()) > 11) ? (static_cast<int32_t>((parent)->size()) - 11) : 0);
#line 520 "/src/emitter-monomorphize.do"
    for (int32_t index = start; index < static_cast<int32_t>((parent)->size()); ++index) {
#line 520 "/src/emitter-monomorphize.do"
        trace->push_back(doof::array_at(parent, index, "src/emitter-monomorphize", 520));
    }
#line 521 "/src/emitter-monomorphize.do"
    trace->push_back(item);
#line 522 "/src/emitter-monomorphize.do"
    return trace;
}
#line 525 "/src/emitter-monomorphize.do"
void discoverConcreteInterfaceImplementations(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<InstantiationPlan>& plan) {
#line 526 "/src/emitter-monomorphize.do"
    const auto& _iterable_96 = plan->interfaces;
    for (const auto& interface_ : *_iterable_96) {
#line 527 "/src/emitter-monomorphize.do"
        const auto& _iterable_98 = analysis->modules;
        for (const auto& module : *_iterable_98) {
#line 528 "/src/emitter-monomorphize.do"
            const auto& _iterable_100 = module->program->statements;
            for (const auto& statement : *_iterable_100) {
#line 529 "/src/emitter-monomorphize.do"
                std::shared_ptr<::app_src_ast_::ClassDeclaration> candidate = nullptr;
#line 530 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = statement;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 531 "/src/emitter-monomorphize.do"
                        (candidate = class_);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                        const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 533 "/src/emitter-monomorphize.do"
                        {
                            auto _case_subject = export_->declaration;
                            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                                const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 534 "/src/emitter-monomorphize.do"
                                (candidate = class_);
                        }
                        else {
                        }
                        }
                }
                else {
                }
                }
#line 540 "/src/emitter-monomorphize.do"
                if ((((!doof::is_null(candidate)) && (static_cast<int32_t>((candidate->typeParams)->size()) == 0)) && !candidate->struct_) && classImplementsConcreteInterface(doof::unwrap_optional(candidate), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), interface_, analysis)) {
#line 541 "/src/emitter-monomorphize.do"
                    addImplementation(interface_, module->path, candidate->name);
                }
            }
        }
#line 545 "/src/emitter-monomorphize.do"
        const auto& _iterable_102 = plan->classes;
        for (const auto& class_ : *_iterable_102) {
#line 546 "/src/emitter-monomorphize.do"
            if (class_->declaration->struct_) {
#line 546 "/src/emitter-monomorphize.do"
                continue;
            }
#line 547 "/src/emitter-monomorphize.do"
            if (classImplementsConcreteInterface(class_->declaration, class_->substitution->arguments, interface_, analysis)) {
#line 548 "/src/emitter-monomorphize.do"
                addImplementation(interface_, class_->modulePath, class_->emittedName);
            }
        }
    }
}
#line 554 "/src/emitter-monomorphize.do"
void addImplementation(const std::shared_ptr<InterfaceInstantiation>& interface_, const std::string& modulePath, const std::string& typeName_) {
#line 555 "/src/emitter-monomorphize.do"
    const auto& _iterable_104 = interface_->implementations;
    for (const auto& existing : *_iterable_104) {
#line 555 "/src/emitter-monomorphize.do"
        if ((existing->modulePath == modulePath) && (existing->typeName == typeName_)) {
#line 555 "/src/emitter-monomorphize.do"
            return;
        }
    }
#line 556 "/src/emitter-monomorphize.do"
    interface_->implementations->push_back(std::make_shared<ImplementationRef>(modulePath, typeName_));
}
#line 559 "/src/emitter-monomorphize.do"
bool classImplementsConcreteInterface(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& classArgs, const std::shared_ptr<InterfaceInstantiation>& interface_, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis) {
#line 560 "/src/emitter-monomorphize.do"
    if (interface_->name == std::string("Stream")) {
#line 561 "/src/emitter-monomorphize.do"
        const auto& _iterable_106 = class_->implements_;
        for (const auto& implementation : *_iterable_106) {
#line 562 "/src/emitter-monomorphize.do"
            if (doof::is_null(implementation->resolvedType)) {
#line 562 "/src/emitter-monomorphize.do"
                continue;
            }
#line 563 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = specialize(doof::unwrap_optional(implementation->resolvedType), class_->typeParams, classArgs);
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                    const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 564 "/src/emitter-monomorphize.do"
                    if (::app_src_checker_types_::sameType(stream->elementType, doof::array_at(interface_->substitution->arguments, 0, "src/emitter-monomorphize", 564))) {
#line 564 "/src/emitter-monomorphize.do"
                        return true;
                    }
            }
            else {
            }
            }
        }
#line 568 "/src/emitter-monomorphize.do"
        const auto next = classMethod(class_, std::string("next"));
#line 569 "/src/emitter-monomorphize.do"
        const auto value = classMethod(class_, std::string("value"));
#line 570 "/src/emitter-monomorphize.do"
        if (((doof::is_null(next) || doof::is_null(value)) || doof::is_null(next->resolvedType)) || doof::is_null(value->resolvedType)) {
#line 570 "/src/emitter-monomorphize.do"
            return false;
        }
#line 571 "/src/emitter-monomorphize.do"
        const auto nextType = specialize(doof::unwrap_optional(next->resolvedType), class_->typeParams, classArgs);
#line 572 "/src/emitter-monomorphize.do"
        const auto valueType = specialize(doof::unwrap_optional(value->resolvedType), class_->typeParams, classArgs);
#line 573 "/src/emitter-monomorphize.do"
        {
            auto _case_subject = nextType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 574 "/src/emitter-monomorphize.do"
                if ((::app_src_checker_types_::typeName(fn->returnType) != std::string("bool")) || (static_cast<int32_t>((fn->params)->size()) != 0)) {
#line 574 "/src/emitter-monomorphize.do"
                    return false;
                }
        }
        else {
#line 575 "/src/emitter-monomorphize.do"
                return false;
        }
        }
#line 577 "/src/emitter-monomorphize.do"
        {
            auto _case_subject = valueType;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& fn = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 578 "/src/emitter-monomorphize.do"
                return ((static_cast<int32_t>((fn->params)->size()) == 0) && ::app_src_checker_types_::sameType(fn->returnType, doof::array_at(interface_->substitution->arguments, 0, "src/emitter-monomorphize", 578)));
        }
        else {
#line 579 "/src/emitter-monomorphize.do"
                return false;
        }
        }
        doof::unreachable();
    }
#line 582 "/src/emitter-monomorphize.do"
    const auto declaration = interfaceDeclaration(analysis, interface_->modulePath, interface_->name);
#line 583 "/src/emitter-monomorphize.do"
    if (doof::is_null(declaration)) {
#line 583 "/src/emitter-monomorphize.do"
        return false;
    }
#line 584 "/src/emitter-monomorphize.do"
    const auto& _iterable_108 = declaration->fields;
    for (const auto& required : *_iterable_108) {
#line 585 "/src/emitter-monomorphize.do"
        const auto actual = classField(class_, required->name);
#line 586 "/src/emitter-monomorphize.do"
        if ((doof::is_null(actual) || doof::is_null(actual->resolvedType)) || doof::is_null(required->resolvedType)) {
#line 586 "/src/emitter-monomorphize.do"
            return false;
        }
#line 587 "/src/emitter-monomorphize.do"
        const auto actualType = specialize(doof::unwrap_optional(actual->resolvedType), class_->typeParams, classArgs);
#line 588 "/src/emitter-monomorphize.do"
        const auto requiredType = specialize(doof::unwrap_optional(required->resolvedType), declaration->typeParams, interface_->substitution->arguments);
#line 589 "/src/emitter-monomorphize.do"
        if (!::app_src_checker_types_::isAssignable(actualType, requiredType)) {
#line 589 "/src/emitter-monomorphize.do"
            return false;
        }
    }
#line 591 "/src/emitter-monomorphize.do"
    const auto& _iterable_110 = declaration->methods;
    for (const auto& required : *_iterable_110) {
#line 592 "/src/emitter-monomorphize.do"
        const auto actual = classMethod(class_, required->name);
#line 593 "/src/emitter-monomorphize.do"
        if ((doof::is_null(actual) || doof::is_null(actual->resolvedType)) || doof::is_null(required->resolvedType)) {
#line 593 "/src/emitter-monomorphize.do"
            return false;
        }
#line 594 "/src/emitter-monomorphize.do"
        const auto actualType = specialize(doof::unwrap_optional(actual->resolvedType), class_->typeParams, classArgs);
#line 595 "/src/emitter-monomorphize.do"
        const auto requiredType = specialize(doof::unwrap_optional(required->resolvedType), declaration->typeParams, interface_->substitution->arguments);
#line 596 "/src/emitter-monomorphize.do"
        if (!sameConcreteMethodType(actualType, requiredType)) {
#line 596 "/src/emitter-monomorphize.do"
            return false;
        }
    }
#line 598 "/src/emitter-monomorphize.do"
    return true;
}
#line 601 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::ClassField> classField(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& name) {
#line 602 "/src/emitter-monomorphize.do"
    const auto& _iterable_112 = class_->fields;
    for (const auto& field : *_iterable_112) {
#line 602 "/src/emitter-monomorphize.do"
        const auto& _iterable_114 = field->names;
        for (const auto& fieldName : *_iterable_114) {
#line 602 "/src/emitter-monomorphize.do"
            if (fieldName == name) {
#line 602 "/src/emitter-monomorphize.do"
                return field;
            }
        }
    }
#line 603 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 606 "/src/emitter-monomorphize.do"
bool sameConcreteMethodType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& actual, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 607 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = actual;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& actualFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 609 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = expected;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                    const auto& expectedFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 611 "/src/emitter-monomorphize.do"
                    if (static_cast<int32_t>((actualFunction->params)->size()) != static_cast<int32_t>((expectedFunction->params)->size())) {
#line 611 "/src/emitter-monomorphize.do"
                        return false;
                    }
#line 612 "/src/emitter-monomorphize.do"
                    for (int32_t index = 0; index < static_cast<int32_t>((actualFunction->params)->size()); ++index) {
#line 613 "/src/emitter-monomorphize.do"
                        if (!::app_src_checker_types_::sameType(doof::array_at(actualFunction->params, index, "src/emitter-monomorphize", 613)->type_, doof::array_at(expectedFunction->params, index, "src/emitter-monomorphize", 613)->type_)) {
#line 613 "/src/emitter-monomorphize.do"
                            return false;
                        }
                    }
#line 615 "/src/emitter-monomorphize.do"
                    return ::app_src_checker_types_::sameType(actualFunction->returnType, expectedFunction->returnType);
            }
            else {
#line 617 "/src/emitter-monomorphize.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 620 "/src/emitter-monomorphize.do"
            return ::app_src_checker_types_::sameType(actual, expected);
    }
    }
    doof::unreachable();
#line 622 "/src/emitter-monomorphize.do"
    return false;
}
#line 625 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> classMethod(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& name) {
#line 626 "/src/emitter-monomorphize.do"
    const auto& _iterable_117 = class_->methods;
    for (const auto& method : *_iterable_117) {
#line 626 "/src/emitter-monomorphize.do"
        if ((method->name == name) && !method->static_) {
#line 626 "/src/emitter-monomorphize.do"
            return method;
        }
    }
#line 627 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 630 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::InterfaceDeclaration> interfaceDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::string& modulePath, const std::string& name) {
#line 631 "/src/emitter-monomorphize.do"
    const auto& _iterable_119 = analysis->modules;
    for (const auto& module : *_iterable_119) {
#line 632 "/src/emitter-monomorphize.do"
        if (module->path != modulePath) {
#line 632 "/src/emitter-monomorphize.do"
            continue;
        }
#line 633 "/src/emitter-monomorphize.do"
        const auto& _iterable_121 = module->program->statements;
        for (const auto& statement : *_iterable_121) {
#line 634 "/src/emitter-monomorphize.do"
            {
                auto _case_subject = statement;
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 635 "/src/emitter-monomorphize.do"
                    if (interface_->name == name) {
#line 635 "/src/emitter-monomorphize.do"
                        return interface_;
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
                    const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 637 "/src/emitter-monomorphize.do"
                    {
                        auto _case_subject = export_->declaration;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 638 "/src/emitter-monomorphize.do"
                            if (interface_->name == name) {
#line 638 "/src/emitter-monomorphize.do"
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
#line 646 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 649 "/src/emitter-monomorphize.do"
std::string functionModule(const std::shared_ptr<::app_src_ast_::CallExpression>& call, const std::string& fallback) {
#line 650 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = call->callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 652 "/src/emitter-monomorphize.do"
            if (!doof::is_null(identifier->resolvedBinding)) {
#line 653 "/src/emitter-monomorphize.do"
                if (!doof::is_null(identifier->resolvedBinding->symbol)) {
#line 653 "/src/emitter-monomorphize.do"
                    return identifier->resolvedBinding->symbol->module;
                }
#line 654 "/src/emitter-monomorphize.do"
                if (identifier->resolvedBinding->module != std::string("")) {
#line 654 "/src/emitter-monomorphize.do"
                    return identifier->resolvedBinding->module;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject)) {
            const auto& member = std::get<std::shared_ptr<::app_src_ast_::MemberExpression>>(_case_subject);
#line 658 "/src/emitter-monomorphize.do"
            if (!doof::is_null(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object))) {
#line 659 "/src/emitter-monomorphize.do"
                {
                    auto _case_subject = doof::unwrap_optional(std::visit([](auto&& _obj) { return _obj->resolvedType; }, member->object));
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 660 "/src/emitter-monomorphize.do"
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
#line 667 "/src/emitter-monomorphize.do"
    return fallback;
}
#line 670 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> classDeclaration(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::string& modulePath, const std::string& name) {
#line 671 "/src/emitter-monomorphize.do"
    const auto& _iterable_123 = analysis->modules;
    for (const auto& module : *_iterable_123) {
#line 672 "/src/emitter-monomorphize.do"
        if (module->path != modulePath) {
#line 672 "/src/emitter-monomorphize.do"
            continue;
        }
#line 673 "/src/emitter-monomorphize.do"
        const auto& _iterable_125 = module->program->statements;
        for (const auto& statement : *_iterable_125) {
#line 674 "/src/emitter-monomorphize.do"
            const auto declaration = classFromStatement(statement, name);
#line 675 "/src/emitter-monomorphize.do"
            if (!doof::is_null(declaration)) {
#line 675 "/src/emitter-monomorphize.do"
                return declaration;
            }
        }
    }
#line 678 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 681 "/src/emitter-monomorphize.do"
std::shared_ptr<::app_src_ast_::ClassDeclaration> classFromStatement(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::string& name) {
#line 682 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 683 "/src/emitter-monomorphize.do"
            if (class_->name == name) {
#line 683 "/src/emitter-monomorphize.do"
                return class_;
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 684 "/src/emitter-monomorphize.do"
            return classFromStatement(export_->declaration, name);
    }
    else {
    }
    }
#line 687 "/src/emitter-monomorphize.do"
    return nullptr;
}
#line 690 "/src/emitter-monomorphize.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> specialize(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments) {
#line 691 "/src/emitter-monomorphize.do"
    if (static_cast<int32_t>((names)->size()) == 0) {
#line 691 "/src/emitter-monomorphize.do"
        return type_;
    }
#line 692 "/src/emitter-monomorphize.do"
    return ::app_src_checker_types_::substituteTypeParams(type_, names, arguments);
}
#line 695 "/src/emitter-monomorphize.do"
bool containsTypeParameters(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& types) {
#line 696 "/src/emitter-monomorphize.do"
    const auto& _iterable_127 = types;
    for (const auto& type_ : *_iterable_127) {
#line 696 "/src/emitter-monomorphize.do"
        if (containsTypeParameter(type_)) {
#line 696 "/src/emitter-monomorphize.do"
            return true;
        }
    }
#line 697 "/src/emitter-monomorphize.do"
    return false;
}
#line 700 "/src/emitter-monomorphize.do"
bool containsTypeParameter(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 701 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
#line 702 "/src/emitter-monomorphize.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 703 "/src/emitter-monomorphize.do"
            return containsTypeParameters(class_->typeArgs);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 704 "/src/emitter-monomorphize.do"
            return containsTypeParameters(interface_->typeArgs);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 705 "/src/emitter-monomorphize.do"
            return containsTypeParameter(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 706 "/src/emitter-monomorphize.do"
            return (containsTypeParameter(map->keyType) || containsTypeParameter(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 707 "/src/emitter-monomorphize.do"
            return containsTypeParameter(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 708 "/src/emitter-monomorphize.do"
            return containsTypeParameter(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 709 "/src/emitter-monomorphize.do"
            return (containsTypeParameter(result->valueType) || containsTypeParameter(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 710 "/src/emitter-monomorphize.do"
            return containsTypeParameter(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 711 "/src/emitter-monomorphize.do"
            return containsTypeParameter(promise->valueType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 712 "/src/emitter-monomorphize.do"
            return containsTypeParameters(tuple->elements);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 713 "/src/emitter-monomorphize.do"
            return containsTypeParameters(union_->types);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 714 "/src/emitter-monomorphize.do"
            return containsTypeParameter(weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 716 "/src/emitter-monomorphize.do"
            const auto& _iterable_129 = function_->params;
            for (const auto& parameter : *_iterable_129) {
#line 716 "/src/emitter-monomorphize.do"
                if (containsTypeParameter(parameter->type_)) {
#line 716 "/src/emitter-monomorphize.do"
                    return true;
                }
            }
#line 717 "/src/emitter-monomorphize.do"
            return containsTypeParameter(function_->returnType);
    }
    else {
#line 719 "/src/emitter-monomorphize.do"
            return false;
    }
    }
    doof::unreachable();
#line 721 "/src/emitter-monomorphize.do"
    return false;
}
#line 724 "/src/emitter-monomorphize.do"
std::string concreteTypeListKey(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& types) {
#line 725 "/src/emitter-monomorphize.do"
    auto result = std::string("");
#line 726 "/src/emitter-monomorphize.do"
    const auto& _iterable_131 = types;
    for (const auto& type_ : *_iterable_131) {
#line 726 "/src/emitter-monomorphize.do"
        (result = (((result + std::string("[")) + canonicalTypeKey(type_)) + std::string("]")));
    }
#line 727 "/src/emitter-monomorphize.do"
    return result;
}
#line 730 "/src/emitter-monomorphize.do"
std::string canonicalTypeKey(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 731 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 732 "/src/emitter-monomorphize.do"
            return ((((std::string("class:") + class_->symbol->module) + std::string(":")) + class_->name) + concreteTypeListKey(class_->typeArgs));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 733 "/src/emitter-monomorphize.do"
            return (((std::string("enum:") + enum_->symbol->module) + std::string(":")) + enum_->name);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 734 "/src/emitter-monomorphize.do"
            return ((((std::string("interface:") + interface_->symbol->module) + std::string(":")) + interface_->name) + concreteTypeListKey(interface_->typeArgs));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 735 "/src/emitter-monomorphize.do"
            return ((array->readonly_ ? std::string("readonly-array:") : std::string("array:")) + canonicalTypeKey(array->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 736 "/src/emitter-monomorphize.do"
            return ((((map->readonly_ ? std::string("readonly-map:") : std::string("map:")) + canonicalTypeKey(map->keyType)) + std::string(":")) + canonicalTypeKey(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 737 "/src/emitter-monomorphize.do"
            return ((set_->readonly_ ? std::string("readonly-set:") : std::string("set:")) + canonicalTypeKey(set_->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 738 "/src/emitter-monomorphize.do"
            return (std::string("stream:") + canonicalTypeKey(stream->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 739 "/src/emitter-monomorphize.do"
            return (((std::string("result:") + canonicalTypeKey(result->valueType)) + std::string(":")) + canonicalTypeKey(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 740 "/src/emitter-monomorphize.do"
            return (std::string("actor:") + canonicalTypeKey(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 741 "/src/emitter-monomorphize.do"
            return (std::string("promise:") + canonicalTypeKey(promise->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 742 "/src/emitter-monomorphize.do"
            return (std::string("tuple:") + concreteTypeListKey(tuple->elements));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 743 "/src/emitter-monomorphize.do"
            return (std::string("union:") + concreteTypeListKey(union_->types));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 744 "/src/emitter-monomorphize.do"
            return (std::string("weak:") + canonicalTypeKey(weak_->inner));
    }
    else {
#line 745 "/src/emitter-monomorphize.do"
            return ::app_src_checker_types_::typeName(type_);
    }
    }
    doof::unreachable();
#line 747 "/src/emitter-monomorphize.do"
    return ::app_src_checker_types_::typeName(type_);
}
#line 750 "/src/emitter-monomorphize.do"
std::string mangleType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 751 "/src/emitter-monomorphize.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 752 "/src/emitter-monomorphize.do"
            return sanitize(((((::app_src_emitter_names_::moduleNamespace(class_->symbol->module) + std::string("_")) + class_->name) + std::string("_")) + concreteTypeListMangle(class_->typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 753 "/src/emitter-monomorphize.do"
            return sanitize(((((::app_src_emitter_names_::moduleNamespace(interface_->symbol->module) + std::string("_")) + interface_->name) + std::string("_")) + concreteTypeListMangle(interface_->typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 754 "/src/emitter-monomorphize.do"
            return ((array->readonly_ ? std::string("readonly_array_") : std::string("array_")) + mangleType(array->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 755 "/src/emitter-monomorphize.do"
            return ((((map->readonly_ ? std::string("readonly_map_") : std::string("map_")) + mangleType(map->keyType)) + std::string("_")) + mangleType(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 756 "/src/emitter-monomorphize.do"
            return ((set_->readonly_ ? std::string("readonly_set_") : std::string("set_")) + mangleType(set_->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 757 "/src/emitter-monomorphize.do"
            return (std::string("stream_") + mangleType(stream->elementType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 758 "/src/emitter-monomorphize.do"
            return (((std::string("result_") + mangleType(result->valueType)) + std::string("_")) + mangleType(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 759 "/src/emitter-monomorphize.do"
            return (std::string("actor_") + mangleType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 760 "/src/emitter-monomorphize.do"
            return (std::string("promise_") + mangleType(promise->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 761 "/src/emitter-monomorphize.do"
            return (std::string("tuple_") + concreteTypeListMangle(tuple->elements));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 762 "/src/emitter-monomorphize.do"
            return (std::string("union_") + concreteTypeListMangle(union_->types));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 763 "/src/emitter-monomorphize.do"
            return (std::string("weak_") + mangleType(weak_->inner));
    }
    else {
#line 764 "/src/emitter-monomorphize.do"
            return sanitize(::app_src_checker_types_::typeName(type_));
    }
    }
    doof::unreachable();
#line 766 "/src/emitter-monomorphize.do"
    return std::string("type");
}
#line 769 "/src/emitter-monomorphize.do"
std::string concreteTypeListMangle(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& types) {
#line 770 "/src/emitter-monomorphize.do"
    auto result = std::string("");
#line 771 "/src/emitter-monomorphize.do"
    const auto& _iterable_133 = types;
    for (const auto& type_ : *_iterable_133) {
#line 772 "/src/emitter-monomorphize.do"
        if (result != std::string("")) {
#line 772 "/src/emitter-monomorphize.do"
            (result = (result + std::string("_")));
        }
#line 773 "/src/emitter-monomorphize.do"
        (result = (result + mangleType(type_)));
    }
#line 775 "/src/emitter-monomorphize.do"
    return result;
}
#line 778 "/src/emitter-monomorphize.do"
std::string sanitize(const std::string& value) {
#line 779 "/src/emitter-monomorphize.do"
    return doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("/"), std::string("_")), std::string("."), std::string("_")), std::string("<"), std::string("_")), std::string(">"), std::string("_")), std::string(","), std::string("_")), std::string(" "), std::string("_")), std::string("|"), std::string("_")), std::string("["), std::string("_")), std::string("]"), std::string("_")), std::string(":"), std::string("_")), std::string("("), std::string("_")), std::string(")"), std::string("_"));
}
#line 1 "<doof-generated>"
}
