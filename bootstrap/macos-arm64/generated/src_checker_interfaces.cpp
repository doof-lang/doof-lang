#include "src_checker_interfaces.hpp"

namespace app_src_checker_interfaces_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_symbols_;
#line 40 "/src/checker-interfaces.do"
::app_src_ast_::SourceSpan symbolSpan(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
#line 41 "/src/checker-interfaces.do"
    const auto& _iterable_2 = info->program->statements;
    for (const auto& statement : *_iterable_2) {
#line 41 "/src/checker-interfaces.do"
        if (::app_src_checker_symbols_::symbolName(statement) == name) {
#line 41 "/src/checker-interfaces.do"
            return std::visit([](auto&& _obj) { return _obj->span; }, statement);
        }
    }
#line 42 "/src/checker-interfaces.do"
    return info->program->span;
}
#line 45 "/src/checker-interfaces.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path) {
#line 46 "/src/checker-interfaces.do"
    const auto& _iterable_4 = result->modules;
    for (const auto& module : *_iterable_4) {
#line 46 "/src/checker-interfaces.do"
        if (module->path == path) {
#line 46 "/src/checker-interfaces.do"
            return module;
        }
    }
#line 47 "/src/checker-interfaces.do"
    return nullptr;
}
#line 54 "/src/checker-interfaces.do"
void discoverInterfaceImplementations(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 55 "/src/checker-interfaces.do"
    const auto& _iterable_6 = result->modules;
    for (const auto& interfaceModule : *_iterable_6) {
#line 56 "/src/checker-interfaces.do"
        const auto& _iterable_8 = interfaceModule->symbols;
        for (const auto& interfaceSymbol : *_iterable_8) {
#line 57 "/src/checker-interfaces.do"
            if (interfaceSymbol->kind != std::string("interface")) {
#line 57 "/src/checker-interfaces.do"
                continue;
            }
#line 58 "/src/checker-interfaces.do"
            const auto& _iterable_10 = result->modules;
            for (const auto& classModule : *_iterable_10) {
#line 59 "/src/checker-interfaces.do"
                const auto& _iterable_12 = classModule->symbols;
                for (const auto& classSymbol : *_iterable_12) {
#line 60 "/src/checker-interfaces.do"
                    if (classSymbol->kind != std::string("class")) {
#line 60 "/src/checker-interfaces.do"
                        continue;
                    }
#line 61 "/src/checker-interfaces.do"
                    if (classSatisfiesInterface(result, classSymbol, interfaceSymbol)) {
#line 62 "/src/checker-interfaces.do"
                        if (!containsImplementation(interfaceSymbol->implementations, classSymbol)) {
#line 63 "/src/checker-interfaces.do"
                            interfaceSymbol->implementations->push_back(classSymbol);
                        }
                    }
                }
            }
        }
    }
}
#line 72 "/src/checker-interfaces.do"
bool containsImplementation(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>& implementations, const std::shared_ptr<::app_src_semantic_::Symbol>& candidate) {
#line 73 "/src/checker-interfaces.do"
    const auto& _iterable_14 = implementations;
    for (const auto& implementation : *_iterable_14) {
#line 74 "/src/checker-interfaces.do"
        if ((implementation->module == candidate->module) && (implementation->name == candidate->name)) {
#line 74 "/src/checker-interfaces.do"
            return true;
        }
    }
#line 76 "/src/checker-interfaces.do"
    return false;
}
#line 79 "/src/checker-interfaces.do"
void addImplementedInterfaceType(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& name) {
#line 80 "/src/checker-interfaces.do"
    const auto& _iterable_16 = symbol->implementedInterfaceTypes;
    for (const auto& existing : *_iterable_16) {
#line 80 "/src/checker-interfaces.do"
        if (existing == name) {
#line 80 "/src/checker-interfaces.do"
            return;
        }
    }
#line 81 "/src/checker-interfaces.do"
    symbol->implementedInterfaceTypes->push_back(name);
}
#line 87 "/src/checker-interfaces.do"
void registerConcreteInterfaceImplementations(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::InterfaceType>& interface_) {
#line 88 "/src/checker-interfaces.do"
    const auto& _iterable_18 = result->modules;
    for (const auto& module : *_iterable_18) {
#line 89 "/src/checker-interfaces.do"
        const auto& _iterable_20 = module->symbols;
        for (const auto& symbol : *_iterable_20) {
#line 90 "/src/checker-interfaces.do"
            if (symbol->kind != std::string("class")) {
#line 90 "/src/checker-interfaces.do"
                continue;
            }
#line 91 "/src/checker-interfaces.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(result, symbol);
#line 92 "/src/checker-interfaces.do"
            if (doof::is_null(declaration)) {
#line 92 "/src/checker-interfaces.do"
                continue;
            }
#line 93 "/src/checker-interfaces.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 95 "/src/checker-interfaces.do"
                    if ((static_cast<int32_t>((class_->typeParams)->size()) == 0) && classSatisfiesConcreteInterface(result, class_, ::app_src_checker_types_::classType(class_->name, symbol, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})), interface_)) {
#line 96 "/src/checker-interfaces.do"
                        addImplementedInterfaceType(symbol, ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(interface_)));
                    }
            }
            else {
            }
            }
        }
    }
}
#line 105 "/src/checker-interfaces.do"
bool concreteTypes(const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& types) {
#line 106 "/src/checker-interfaces.do"
    const auto& _iterable_22 = types;
    for (const auto& type_ : *_iterable_22) {
#line 107 "/src/checker-interfaces.do"
        {
            auto _case_subject = type_;
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
#line 108 "/src/checker-interfaces.do"
                return false;
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 109 "/src/checker-interfaces.do"
                if (!concreteTypes(class_->typeArgs)) {
#line 109 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
                const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 110 "/src/checker-interfaces.do"
                if (!concreteTypes(interface_->typeArgs)) {
#line 110 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 111 "/src/checker-interfaces.do"
                if (!concreteTypes(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{array->elementType}))) {
#line 111 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 112 "/src/checker-interfaces.do"
                if (!concreteTypes(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{map->keyType, map->valueType}))) {
#line 112 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 113 "/src/checker-interfaces.do"
                if (!concreteTypes(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{set_->elementType}))) {
#line 113 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
                const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 114 "/src/checker-interfaces.do"
                if (!concreteTypes(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{stream->elementType}))) {
#line 114 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 115 "/src/checker-interfaces.do"
                if (!concreteTypes(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{result_->valueType, result_->errorType}))) {
#line 115 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
                const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 116 "/src/checker-interfaces.do"
                if (!concreteTypes(tuple->elements)) {
#line 116 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 117 "/src/checker-interfaces.do"
                if (!concreteTypes(union_->types)) {
#line 117 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 118 "/src/checker-interfaces.do"
                if (!concreteTypes(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{weak_->inner}))) {
#line 118 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 120 "/src/checker-interfaces.do"
                const auto& _iterable_24 = function_->params;
                for (const auto& parameter : *_iterable_24) {
#line 120 "/src/checker-interfaces.do"
                    if (!concreteTypes(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{parameter->type_}))) {
#line 120 "/src/checker-interfaces.do"
                        return false;
                    }
                }
#line 121 "/src/checker-interfaces.do"
                if (!concreteTypes(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{function_->returnType}))) {
#line 121 "/src/checker-interfaces.do"
                    return false;
                }
        }
        else {
        }
        }
    }
#line 126 "/src/checker-interfaces.do"
    return true;
}
#line 129 "/src/checker-interfaces.do"
bool classSatisfiesConcreteInterface(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::shared_ptr<::app_src_semantic_::ClassType>& classType_, const std::shared_ptr<::app_src_semantic_::InterfaceType>& interfaceType_) {
#line 130 "/src/checker-interfaces.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(result, interfaceType_->symbol);
#line 131 "/src/checker-interfaces.do"
    if (doof::is_null(declaration)) {
#line 131 "/src/checker-interfaces.do"
        return false;
    }
#line 132 "/src/checker-interfaces.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 134 "/src/checker-interfaces.do"
            const auto& _iterable_26 = interface_->fields;
            for (const auto& required : *_iterable_26) {
#line 135 "/src/checker-interfaces.do"
                const auto actualField = findClassField(class_->fields, required->name);
#line 136 "/src/checker-interfaces.do"
                if ((doof::is_null(actualField) || actualField->private_) || doof::is_null(actualField->type_)) {
#line 136 "/src/checker-interfaces.do"
                    return false;
                }
#line 137 "/src/checker-interfaces.do"
                if (required->readonly_ && !actualField->readonly_) {
#line 137 "/src/checker-interfaces.do"
                    return false;
                }
#line 138 "/src/checker-interfaces.do"
                if (required->let_ && !actualField->let_) {
#line 138 "/src/checker-interfaces.do"
                    return false;
                }
#line 139 "/src/checker-interfaces.do"
                const auto actualBase = (doof::is_null(actualField->resolvedType) ? ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(actualField->type_), classModuleFor(result, classType_->symbol), result, class_->typeParams) : doof::unwrap_optional(actualField->resolvedType));
#line 140 "/src/checker-interfaces.do"
                const auto requiredBase = (doof::is_null(required->resolvedType) ? ::app_src_checker_symbols_::resolveAnnotation(required->type_, classModuleFor(result, interfaceType_->symbol), result, interface_->typeParams) : doof::unwrap_optional(required->resolvedType));
#line 141 "/src/checker-interfaces.do"
                const auto actual = ::app_src_checker_types_::substituteTypeParams(actualBase, class_->typeParams, classType_->typeArgs);
#line 142 "/src/checker-interfaces.do"
                const auto expected = ::app_src_checker_types_::substituteTypeParams(requiredBase, interface_->typeParams, interfaceType_->typeArgs);
#line 143 "/src/checker-interfaces.do"
                if (!::app_src_checker_types_::isAssignable(actual, expected)) {
#line 143 "/src/checker-interfaces.do"
                    return false;
                }
            }
#line 145 "/src/checker-interfaces.do"
            const auto& _iterable_28 = interface_->methods;
            for (const auto& requiredMethod : *_iterable_28) {
#line 146 "/src/checker-interfaces.do"
                const auto actualMethod = findClassMethod(class_->methods, requiredMethod->name, requiredMethod->static_);
#line 147 "/src/checker-interfaces.do"
                if (doof::is_null(actualMethod) || actualMethod->private_) {
#line 147 "/src/checker-interfaces.do"
                    return false;
                }
#line 148 "/src/checker-interfaces.do"
                const auto actualBase = (doof::is_null(actualMethod->resolvedType) ? ::app_src_checker_symbols_::methodSignature(doof::unwrap_optional(actualMethod), classModuleFor(result, classType_->symbol), result) : doof::unwrap_optional(actualMethod->resolvedType));
#line 149 "/src/checker-interfaces.do"
                const auto requiredBase = (doof::is_null(requiredMethod->resolvedType) ? ::app_src_checker_symbols_::methodSignature(requiredMethod, classModuleFor(result, interfaceType_->symbol), result) : doof::unwrap_optional(requiredMethod->resolvedType));
#line 150 "/src/checker-interfaces.do"
                const auto actual = ::app_src_checker_types_::substituteTypeParams(actualBase, class_->typeParams, classType_->typeArgs);
#line 151 "/src/checker-interfaces.do"
                const auto expected = ::app_src_checker_types_::substituteTypeParams(requiredBase, interface_->typeParams, interfaceType_->typeArgs);
#line 152 "/src/checker-interfaces.do"
                if (!sameConcreteMethodType(actual, expected)) {
#line 152 "/src/checker-interfaces.do"
                    return false;
                }
            }
#line 154 "/src/checker-interfaces.do"
            return true;
    }
    else {
#line 156 "/src/checker-interfaces.do"
            return false;
    }
    }
    doof::unreachable();
#line 158 "/src/checker-interfaces.do"
    return false;
}
#line 161 "/src/checker-interfaces.do"
bool classSatisfiesInterface(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::Symbol>& classSymbol, const std::shared_ptr<::app_src_semantic_::Symbol>& interfaceSymbol) {
#line 162 "/src/checker-interfaces.do"
    const auto classDeclaration = ::app_src_checker_symbols_::declarationFor(result, classSymbol);
#line 163 "/src/checker-interfaces.do"
    const auto interfaceDeclaration = ::app_src_checker_symbols_::declarationFor(result, interfaceSymbol);
#line 164 "/src/checker-interfaces.do"
    if (doof::is_null(classDeclaration) || doof::is_null(interfaceDeclaration)) {
#line 164 "/src/checker-interfaces.do"
        return false;
    }
#line 165 "/src/checker-interfaces.do"
    {
        auto _case_subject = doof::unwrap_optional(classDeclaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 167 "/src/checker-interfaces.do"
            {
                auto _case_subject = doof::unwrap_optional(interfaceDeclaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 169 "/src/checker-interfaces.do"
                    const auto& _iterable_30 = interface_->fields;
                    for (const auto& required : *_iterable_30) {
#line 170 "/src/checker-interfaces.do"
                        const auto classField = findClassField(class_->fields, required->name);
#line 171 "/src/checker-interfaces.do"
                        if (doof::is_null(classField) || classField->private_) {
#line 171 "/src/checker-interfaces.do"
                            return false;
                        }
#line 172 "/src/checker-interfaces.do"
                        if (required->readonly_ && !classField->readonly_) {
#line 172 "/src/checker-interfaces.do"
                            return false;
                        }
#line 173 "/src/checker-interfaces.do"
                        if (required->let_ && !classField->let_) {
#line 173 "/src/checker-interfaces.do"
                            return false;
                        }
#line 174 "/src/checker-interfaces.do"
                        const auto actual = (doof::is_null(classField->resolvedType) ? ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(classField->type_), classModuleFor(result, classSymbol), result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : doof::unwrap_optional(classField->resolvedType));
#line 175 "/src/checker-interfaces.do"
                        const auto expected = (doof::is_null(required->resolvedType) ? ::app_src_checker_symbols_::resolveAnnotation(required->type_, classModuleFor(result, interfaceSymbol), result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : doof::unwrap_optional(required->resolvedType));
#line 176 "/src/checker-interfaces.do"
                        if (!::app_src_checker_types_::isAssignable(actual, expected)) {
#line 176 "/src/checker-interfaces.do"
                            return false;
                        }
                    }
#line 178 "/src/checker-interfaces.do"
                    const auto& _iterable_32 = interface_->methods;
                    for (const auto& requiredMethod : *_iterable_32) {
#line 179 "/src/checker-interfaces.do"
                        const auto classMethod = findClassMethod(class_->methods, requiredMethod->name, requiredMethod->static_);
#line 180 "/src/checker-interfaces.do"
                        if ((doof::is_null(classMethod) || classMethod->private_) || (static_cast<int32_t>((classMethod->params)->size()) != static_cast<int32_t>((requiredMethod->params)->size()))) {
#line 180 "/src/checker-interfaces.do"
                            return false;
                        }
#line 181 "/src/checker-interfaces.do"
                        if (!sameFunctionSignature(doof::unwrap_optional(classMethod), requiredMethod, result, classSymbol, interfaceSymbol)) {
#line 181 "/src/checker-interfaces.do"
                            return false;
                        }
                    }
#line 183 "/src/checker-interfaces.do"
                    return true;
            }
            else {
#line 185 "/src/checker-interfaces.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 188 "/src/checker-interfaces.do"
            return false;
    }
    }
    doof::unreachable();
#line 190 "/src/checker-interfaces.do"
    return false;
}
#line 193 "/src/checker-interfaces.do"
bool sameConcreteMethodType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& actual, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 194 "/src/checker-interfaces.do"
    {
        auto _case_subject = actual;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& actualFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 196 "/src/checker-interfaces.do"
            {
                auto _case_subject = expected;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                    const auto& expectedFunction = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 198 "/src/checker-interfaces.do"
                    if (static_cast<int32_t>((actualFunction->params)->size()) != static_cast<int32_t>((expectedFunction->params)->size())) {
#line 198 "/src/checker-interfaces.do"
                        return false;
                    }
#line 199 "/src/checker-interfaces.do"
                    for (int32_t index = 0; index < static_cast<int32_t>((actualFunction->params)->size()); ++index) {
#line 200 "/src/checker-interfaces.do"
                        if (!::app_src_checker_types_::sameType(doof::array_at(actualFunction->params, index, "src/checker-interfaces", 200)->type_, doof::array_at(expectedFunction->params, index, "src/checker-interfaces", 200)->type_)) {
#line 200 "/src/checker-interfaces.do"
                            return false;
                        }
                    }
#line 202 "/src/checker-interfaces.do"
                    return ::app_src_checker_types_::sameType(actualFunction->returnType, expectedFunction->returnType);
            }
            else {
#line 204 "/src/checker-interfaces.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 207 "/src/checker-interfaces.do"
            return ::app_src_checker_types_::sameType(actual, expected);
    }
    }
    doof::unreachable();
#line 209 "/src/checker-interfaces.do"
    return false;
}
#line 212 "/src/checker-interfaces.do"
std::shared_ptr<::app_src_ast_::ClassField> findClassField(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ClassField>>>& fields, const std::string& name) {
#line 213 "/src/checker-interfaces.do"
    const auto& _iterable_35 = fields;
    for (const auto& field : *_iterable_35) {
#line 213 "/src/checker-interfaces.do"
        const auto& _iterable_37 = field->names;
        for (const auto& fieldName : *_iterable_37) {
#line 213 "/src/checker-interfaces.do"
            if (fieldName == name) {
#line 213 "/src/checker-interfaces.do"
                return field;
            }
        }
    }
#line 214 "/src/checker-interfaces.do"
    return nullptr;
}
#line 217 "/src/checker-interfaces.do"
std::shared_ptr<::app_src_ast_::FunctionDeclaration> findClassMethod(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>>& methods, const std::string& name, bool static_) {
#line 218 "/src/checker-interfaces.do"
    const auto& _iterable_39 = methods;
    for (const auto& method : *_iterable_39) {
#line 218 "/src/checker-interfaces.do"
        if ((method->name == name) && (method->static_ == static_)) {
#line 218 "/src/checker-interfaces.do"
            return method;
        }
    }
#line 219 "/src/checker-interfaces.do"
    return nullptr;
}
#line 222 "/src/checker-interfaces.do"
bool sameFunctionSignature(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& classMethod, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& interfaceMethod, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::Symbol>& classSymbol, const std::shared_ptr<::app_src_semantic_::Symbol>& interfaceSymbol) {
#line 223 "/src/checker-interfaces.do"
    const auto classModule = classModuleFor(result, classSymbol);
#line 224 "/src/checker-interfaces.do"
    const auto interfaceModule = classModuleFor(result, interfaceSymbol);
#line 225 "/src/checker-interfaces.do"
    for (int32_t i = 0; i < static_cast<int32_t>((classMethod->params)->size()); ++i) {
#line 226 "/src/checker-interfaces.do"
        const auto actualParameterType = (doof::is_null(doof::array_at(classMethod->params, i, "src/checker-interfaces", 226)->resolvedType) ? ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(doof::array_at(classMethod->params, i, "src/checker-interfaces", 226)->type_), classModule, result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : doof::unwrap_optional(doof::array_at(classMethod->params, i, "src/checker-interfaces", 226)->resolvedType));
#line 227 "/src/checker-interfaces.do"
        const auto interfaceType_ = (doof::is_null(doof::array_at(interfaceMethod->params, i, "src/checker-interfaces", 227)->resolvedType) ? ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(doof::array_at(interfaceMethod->params, i, "src/checker-interfaces", 227)->type_), interfaceModule, result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : doof::unwrap_optional(doof::array_at(interfaceMethod->params, i, "src/checker-interfaces", 227)->resolvedType));
#line 228 "/src/checker-interfaces.do"
        if (!::app_src_checker_types_::sameType(actualParameterType, interfaceType_)) {
#line 228 "/src/checker-interfaces.do"
            return false;
        }
    }
#line 230 "/src/checker-interfaces.do"
    const auto classReturn = (doof::is_null(classMethod->returnType) ? ::app_src_checker_types_::noneType() : ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(classMethod->returnType), classModule, result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
#line 231 "/src/checker-interfaces.do"
    const auto interfaceReturn = (doof::is_null(interfaceMethod->returnType) ? ::app_src_checker_types_::noneType() : ::app_src_checker_symbols_::resolveAnnotation(doof::unwrap_optional(interfaceMethod->returnType), interfaceModule, result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
#line 232 "/src/checker-interfaces.do"
    return ::app_src_checker_types_::isAssignable(classReturn, interfaceReturn);
}
#line 235 "/src/checker-interfaces.do"
std::shared_ptr<::app_src_analyzer_::ModuleInfo> classModuleFor(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 236 "/src/checker-interfaces.do"
    const auto module = findModule(result, symbol->module);
#line 237 "/src/checker-interfaces.do"
    if (doof::is_null(module)) {
#line 237 "/src/checker-interfaces.do"
        doof::panic((std::string("Missing module for symbol ") + symbol->name));
    }
#line 238 "/src/checker-interfaces.do"
    return doof::unwrap_optional(module);
}
#line 1 "<doof-generated>"
}
