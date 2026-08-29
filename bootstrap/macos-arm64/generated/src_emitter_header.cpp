#include "src_emitter_header.hpp"

namespace app_src_emitter_header_ {
using namespace ::app_src_ast_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_decl_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_string_builder_;
using namespace ::app_src_emitter_monomorphize_;


std::shared_ptr<HeaderPlan> planHeader(const std::shared_ptr<::app_src_ast_::Program>& program, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& methods) {
    const auto plan = std::make_shared<HeaderPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, false, false);
    const auto& _iterable_2 = program->statements;
    for (const auto& statement : *_iterable_2) {
        collect(statement, plan, context, methods);
    }
    const auto& _iterable_4 = plan->nativeNamespaces;
    for (const auto& namespace_ : *_iterable_4) {
        collectNativeModuleTypeAliases(context->modulePath, namespace_, plan, context);
    }
    return plan;
}
void collectNativeModuleTypeAliases(const std::string& modulePath, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto& _iterable_6 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_6) {
        if (surface->path != modulePath) {
            continue;
        }
        const auto& _iterable_8 = surface->exports;
        for (const auto& symbol : *_iterable_8) {
            if (isNativeAliasType(symbol) && !surfaceTypeIsGeneric(surface, symbol->name)) {
                addNativeSymbolAlias(symbol, namespace_, plan);
            }
        }
        const auto& _iterable_10 = surface->imports;
        for (const auto& imported : *_iterable_10) {
            if (((!doof::is_null(imported->symbol)) && isNativeAliasType(doof::unwrap_optional(imported->symbol))) && !surfaceSymbolIsGeneric(context, doof::unwrap_optional(imported->symbol))) {
                addNativeSymbolAlias(doof::unwrap_optional(imported->symbol), namespace_, plan);
            }
        }
        return;
    }
}
bool surfaceTypeIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>& surface, const std::string& name) {
    const auto& _iterable_12 = surface->genericTypes;
    for (const auto& genericName : *_iterable_12) {
        if (genericName == name) {
            return true;
        }
    }
    return false;
}
bool isNativeAliasType(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
    return (((((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("enum"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("type-alias")));
}
void collect(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& methods) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            reserveHeaderNamespaceName(plan, class_->name);
            if (class_->native_) {
                const auto rawInclude = ((class_->nativeHeader == std::string("")) ? (class_->name + std::string(".hpp")) : class_->nativeHeader);
                const auto include = ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, rawInclude);
                addUnique(plan->nativeIncludes, include);
                const auto namespace_ = nativeNamespace(class_->nativeCppName);
                addUnique(plan->nativeNamespaces, namespace_);
                collectNativeClassAliases(class_, namespace_, plan, context);
            } else if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
                plan->classForwardDeclarations->push_back(((std::string("struct ") + class_->name) + std::string(";\n")));
                std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>> concreteMethods = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{});
                const auto ownerKey = ::app_src_emitter_monomorphize_::classInstantiationKey(context->modulePath, class_->name, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
                const auto& _iterable_14 = methods;
                for (const auto& method : *_iterable_14) {
                    if (method->ownerKey == ownerKey) {
                        concreteMethods->push_back(method);
                    }
                }
                const auto definition = ::app_src_emitter_decl_::emitClassDeclaration(class_, context, std::string(""), concreteMethods);
                if (classCanEmitBeforeModuleIncludes(class_)) {
                    plan->earlyClassDefinitions->push_back(definition);
                } else {
                    plan->classDefinitions->push_back(definition);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            reserveHeaderNamespaceName(plan, interface_->name);
            if (static_cast<int32_t>((interface_->typeParams)->size()) == 0) {
                if (!doof::is_null(interface_->resolvedSymbol)) {
                    const auto& _iterable_16 = interface_->resolvedSymbol->implementations;
                    for (const auto& implementation : *_iterable_16) {
                        if (implementation->native_) {
                            addNativeClassForwardDeclaration(implementation, plan);
                        }
                    }
                }
                plan->interfaceAliases->push_back(::app_src_emitter_decl_::emitInterfaceAlias(interface_, context));
                const auto declaration = ::app_src_emitter_json_::emitInterfaceJsonDeclaration(interface_);
                if (declaration != std::string("")) {
                    plan->functionSignatures->push_back(declaration);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            reserveHeaderNamespaceName(plan, enum_->name);
            plan->enumDefinitions->push_back(emitEnumDeclaration(enum_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            reserveHeaderNamespaceName(plan, alias->name);
            if (static_cast<int32_t>((alias->typeParams)->size()) == 0) {
                const auto emitted = emitTypeAlias(alias, context);
                if ((!doof::is_null(alias->resolvedType)) && !typeNeedsCompleteNominalDefinition(doof::unwrap_optional(alias->resolvedType))) {
                    plan->earlyTypeAliases->push_back(emitted);
                    const auto spelling = ::app_src_emitter_types_::emitType(doof::unwrap_optional(alias->resolvedType), context->modulePath);
                    if (referenceOnlyVariant(spelling)) {
                        plan->preferredTypeAliasNames->push_back(alias->name);
                        plan->preferredTypeAliasSpellings->push_back(spelling);
                    }
                } else {
                    plan->typeAliases->push_back(emitted);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            reserveHeaderNamespaceName(plan, const_->name);
            collectModuleValueDeclaration(plan, (::app_src_emitter_decl_::emitDescriptionComment(const_->description, std::string("")) + emitModuleValueDeclaration(const_->name, doof::unwrap_optional(const_->resolvedType), context)), doof::unwrap_optional(const_->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            reserveHeaderNamespaceName(plan, readonly_->name);
            collectModuleValueDeclaration(plan, (::app_src_emitter_decl_::emitDescriptionComment(readonly_->description, std::string("")) + emitModuleValueDeclaration(readonly_->name, doof::unwrap_optional(readonly_->resolvedType), context)), doof::unwrap_optional(readonly_->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            reserveHeaderNamespaceName(plan, binding->name);
            collectModuleValueDeclaration(plan, emitModuleValueDeclaration(binding->name, doof::unwrap_optional(binding->resolvedType), context), doof::unwrap_optional(binding->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            reserveHeaderNamespaceName(plan, let_->name);
            collectModuleValueDeclaration(plan, emitModuleValueDeclaration(let_->name, doof::unwrap_optional(let_->resolvedType), context), doof::unwrap_optional(let_->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            reserveHeaderNamespaceName(plan, ((fn->name == std::string("main")) ? std::string("doof_main") : fn->name));
            if (fn->native_) {
                if (fn->nativeHeader != std::string("")) {
                    addUnique(plan->nativeIncludes, ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, fn->nativeHeader));
                }
                const auto namespace_ = nativeNamespace(fn->nativeCppName);
                addUnique(plan->nativeNamespaces, namespace_);
                if (!doof::is_null(fn->resolvedType)) {
                    collectNativeTypeAliases(doof::unwrap_optional(fn->resolvedType), namespace_, plan, context);
                }
                return;
            }
            if (fn->name == std::string("main")) {
                (plan->hasMain = true);
                (plan->mainReturnsInt = functionReturnsInt(fn));
                (plan->mainAcceptsArgs = (static_cast<int32_t>((fn->params)->size()) == 1));
                plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string("doof_main"), context->modulePath, context));
            } else if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
            } else {
                plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string(""), context->modulePath, context));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            collect(export_->declaration, plan, context, methods);
    }
    else {
    }
    }
}
bool classCanEmitBeforeModuleIncludes(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_) {
    if (static_cast<int32_t>((class_->typeParams)->size()) > 0) {
        return false;
    }
    const auto& _iterable_18 = class_->fields;
    for (const auto& field : *_iterable_18) {
        if ((!field->static_ && (!doof::is_null(field->resolvedType))) && typeNeedsCompleteNominalDefinition(doof::unwrap_optional(field->resolvedType))) {
            return false;
        }
    }
    return true;
}
bool typeNeedsCompleteNominalDefinition(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if ((class_->symbol->kind == std::string("struct")) || class_->symbol->native_) {
                return true;
            }
            const auto& _iterable_20 = class_->typeArgs;
            for (const auto& argument : *_iterable_20) {
                if (typeNeedsCompleteNominalDefinition(argument)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto& _iterable_22 = interface_->typeArgs;
            for (const auto& argument : *_iterable_22) {
                if (typeNeedsCompleteNominalDefinition(argument)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return typeNeedsCompleteNominalDefinition(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            return (typeNeedsCompleteNominalDefinition(map->keyType) || typeNeedsCompleteNominalDefinition(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            return typeNeedsCompleteNominalDefinition(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            return typeNeedsCompleteNominalDefinition(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return (typeNeedsCompleteNominalDefinition(result->valueType) || typeNeedsCompleteNominalDefinition(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_24 = tuple->elements;
            for (const auto& element : *_iterable_24) {
                if (typeNeedsCompleteNominalDefinition(element)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_26 = union_->types;
            for (const auto& member : *_iterable_26) {
                if (typeNeedsCompleteNominalDefinition(member)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_28 = function_->params;
            for (const auto& parameter : *_iterable_28) {
                if (typeNeedsCompleteNominalDefinition(parameter->type_)) {
                    return true;
                }
            }
            return typeNeedsCompleteNominalDefinition(function_->returnType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            return typeNeedsCompleteNominalDefinition(weak_->inner);
    }
    else {
            return false;
    }
    }
    doof::unreachable();
}
void collectNativeClassAliases(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto& _iterable_30 = class_->fields;
    for (const auto& field : *_iterable_30) {
        if (!doof::is_null(field->resolvedType)) {
            collectNativeTypeAliases(doof::unwrap_optional(field->resolvedType), namespace_, plan, context);
        }
    }
    const auto& _iterable_32 = class_->methods;
    for (const auto& method : *_iterable_32) {
        if (!doof::is_null(method->resolvedType)) {
            collectNativeTypeAliases(doof::unwrap_optional(method->resolvedType), namespace_, plan, context);
        }
    }
}
void collectNativeTypeAliases(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if (!surfaceSymbolIsGeneric(context, class_->symbol)) {
                addNativeSymbolAlias(class_->symbol, namespace_, plan);
            }
            const auto& _iterable_34 = class_->typeArgs;
            for (const auto& argument : *_iterable_34) {
                collectNativeTypeAliases(argument, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            addNativeSymbolAlias(enum_->symbol, namespace_, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            if (!surfaceSymbolIsGeneric(context, interface_->symbol)) {
                addNativeSymbolAlias(interface_->symbol, namespace_, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            collectNativeTypeAliases(array->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            collectNativeTypeAliases(map->keyType, namespace_, plan, context);
            collectNativeTypeAliases(map->valueType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            collectNativeTypeAliases(set_->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            collectNativeTypeAliases(stream->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            collectNativeTypeAliases(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            collectNativeTypeAliases(promise->valueType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            collectNativeTypeAliases(result->valueType, namespace_, plan, context);
            collectNativeTypeAliases(result->errorType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_36 = tuple->elements;
            for (const auto& element : *_iterable_36) {
                collectNativeTypeAliases(element, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_38 = union_->types;
            for (const auto& member : *_iterable_38) {
                collectNativeTypeAliases(member, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            collectNativeTypeAliases(weak_->inner, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_40 = function_->params;
            for (const auto& parameter : *_iterable_40) {
                collectNativeTypeAliases(parameter->type_, namespace_, plan, context);
            }
            collectNativeTypeAliases(function_->returnType, namespace_, plan, context);
    }
    else {
    }
    }
}
bool surfaceSymbolIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
    const auto& _iterable_42 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_42) {
        if (surface->path == symbol->module) {
            return surfaceTypeIsGeneric(surface, symbol->name);
        }
    }
    return false;
}
void addNativeSymbolAlias(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan) {
    if (symbol->native_ || (symbol->module == std::string(""))) {
        return;
    }
    if ((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) {
        addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { struct ")) + symbol->name) + std::string("; }\n")));
    } else if (symbol->kind == std::string("enum")) {
        addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { enum class ")) + symbol->name) + std::string("; }\n")));
    }
    const auto alias = ((((((std::string("using ") + symbol->name) + std::string(" = ::")) + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string("::")) + symbol->name) + std::string(";"));
    addUnique(plan->nativeAliases, ((namespace_ == std::string("")) ? (alias + std::string("\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { ")) + alias) + std::string(" }\n"))));
}
std::string renderProjectedHeader(const std::shared_ptr<std::vector<std::shared_ptr<HeaderSection>>>& sections) {
    const auto compression = std::make_shared<HeaderCompressionState>(1);
    const auto& _iterable_44 = sections;
    for (const auto& section : *_iterable_44) {
        compressRepeatedHeaderVariants(section->plan, compression);
    }
    const auto result = ::doof::StringBuilder::constructor();
    result->append(std::string("#pragma once\n"));
    result->append(std::string("#include \"doof_runtime.hpp\"\n"));
    auto emittedForward = false;
    const auto& _iterable_46 = sections;
    for (const auto& section : *_iterable_46) {
        const auto& _iterable_48 = section->plan->typeOnlyForwardDeclarations;
        for (const auto& declaration : *_iterable_48) {
            result->append(declaration);
            (emittedForward = true);
        }
    }
    if (emittedForward) {
        result->append(std::string("\n"));
    }
    const auto& _iterable_50 = sections;
    for (const auto& section : *_iterable_50) {
        if (((static_cast<int32_t>((section->plan->classForwardDeclarations)->size()) == 0) && (static_cast<int32_t>((section->plan->earlyModuleValueDeclarations)->size()) == 0)) && headerPlanEmitsNamespaceContent(section->plan)) {
            continue;
        }
        result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
        const auto& _iterable_52 = section->plan->classForwardDeclarations;
        for (const auto& declaration : *_iterable_52) {
            result->append((std::string("    ") + declaration));
        }
        const auto& _iterable_54 = section->plan->earlyModuleValueDeclarations;
        for (const auto& declaration : *_iterable_54) {
            result->append((std::string("    ") + declaration));
        }
        result->append(std::string("}\n\n"));
    }
    const auto& _iterable_56 = sections;
    for (const auto& section : *_iterable_56) {
        if (static_cast<int32_t>((section->plan->ephemeralTypeAliases)->size()) > 0) {
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
            const auto& _iterable_58 = section->plan->ephemeralTypeAliases;
            for (const auto& alias : *_iterable_58) {
                result->append((std::string("    ") + alias));
            }
            result->append(std::string("}\n\n"));
        }
    }
    const auto& _iterable_60 = sections;
    for (const auto& section : *_iterable_60) {
        if (static_cast<int32_t>((section->plan->enumDefinitions)->size()) > 0) {
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
            const auto& _iterable_62 = section->plan->enumDefinitions;
            for (const auto& definition : *_iterable_62) {
                result->append((std::string("    ") + definition));
            }
            result->append(std::string("}\n\n"));
        }
    }
    const auto& _iterable_64 = sections;
    for (const auto& section : *_iterable_64) {
        if (static_cast<int32_t>((section->plan->interfaceAliases)->size()) > 0) {
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
            const auto& _iterable_66 = section->plan->interfaceAliases;
            for (const auto& alias : *_iterable_66) {
                result->append((std::string("    ") + alias));
            }
            result->append(std::string("}\n\n"));
        }
    }
    const auto& _iterable_68 = sections;
    for (const auto& section : *_iterable_68) {
        if (static_cast<int32_t>((section->plan->earlyTypeAliases)->size()) > 0) {
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
            const auto& _iterable_70 = section->plan->earlyTypeAliases;
            for (const auto& alias : *_iterable_70) {
                result->append((std::string("    ") + alias));
            }
            result->append(std::string("}\n\n"));
        }
    }
    const auto& _iterable_72 = sections;
    for (const auto& section : *_iterable_72) {
        if (static_cast<int32_t>((section->plan->earlyClassDefinitions)->size()) > 0) {
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
            const auto& _iterable_74 = section->plan->earlyClassDefinitions;
            for (const auto& definition : *_iterable_74) {
                result->append((std::string("    ") + definition));
            }
            result->append(std::string("}\n\n"));
        }
    }
    const auto& _iterable_76 = sections;
    for (const auto& section : *_iterable_76) {
        auto emittedNative = false;
        const auto& _iterable_78 = section->plan->nativeAliases;
        for (const auto& alias : *_iterable_78) {
            result->append(alias);
            (emittedNative = true);
        }
        const auto& _iterable_80 = section->plan->nativeIncludes;
        for (const auto& include : *_iterable_80) {
            if (doof::string_startsWith(include, std::string("<"))) {
                result->append(((std::string("#include ") + include) + std::string("\n")));
            } else {
                result->append(((std::string("#include \"") + include) + std::string("\"\n")));
            }
            (emittedNative = true);
        }
        if (emittedNative) {
            result->append(std::string("\n"));
        }
        renderFinalSection(result, section);
    }
    auto rendered = result->drainToString();
    while (doof::string_endsWith(rendered, std::string("\n\n"))) {
        (rendered = doof::string_substring(rendered, 0, (static_cast<int32_t>(rendered.size()) - 1)));
    }
    return rendered;
}
void renderFinalSection(const std::shared_ptr<::doof::StringBuilder>& result, const std::shared_ptr<HeaderSection>& section) {
    const auto plan = section->plan;
    if (((((static_cast<int32_t>((plan->nativeAdapterSignatures)->size()) == 0) && (static_cast<int32_t>((plan->moduleValueDeclarations)->size()) == 0)) && (static_cast<int32_t>((plan->classDefinitions)->size()) == 0)) && (static_cast<int32_t>((plan->typeAliases)->size()) == 0)) && (static_cast<int32_t>((plan->functionSignatures)->size()) == 0)) {
        return;
    }
    result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
    const auto& _iterable_82 = plan->nativeAdapterSignatures;
    for (const auto& signature : *_iterable_82) {
        result->append((std::string("    ") + signature));
    }
    const auto& _iterable_84 = plan->moduleValueDeclarations;
    for (const auto& declaration : *_iterable_84) {
        result->append((std::string("    ") + declaration));
    }
    const auto& _iterable_86 = plan->classDefinitions;
    for (const auto& definition : *_iterable_86) {
        result->append((std::string("    ") + definition));
    }
    const auto& _iterable_88 = plan->typeAliases;
    for (const auto& alias : *_iterable_88) {
        result->append((std::string("    ") + alias));
    }
    const auto& _iterable_90 = plan->functionSignatures;
    for (const auto& signature : *_iterable_90) {
        result->append((std::string("    ") + signature));
    }
    result->append(std::string("}\n\n"));
}
bool headerPlanEmitsNamespaceContent(const std::shared_ptr<HeaderPlan>& plan) {
    return ((((((((((static_cast<int32_t>((plan->ephemeralTypeAliases)->size()) > 0) || (static_cast<int32_t>((plan->enumDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->interfaceAliases)->size()) > 0)) || (static_cast<int32_t>((plan->earlyClassDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->earlyTypeAliases)->size()) > 0)) || (static_cast<int32_t>((plan->nativeAdapterSignatures)->size()) > 0)) || (static_cast<int32_t>((plan->moduleValueDeclarations)->size()) > 0)) || (static_cast<int32_t>((plan->classDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->typeAliases)->size()) > 0)) || (static_cast<int32_t>((plan->functionSignatures)->size()) > 0));
}


void compressRepeatedHeaderVariants(const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<HeaderCompressionState>& state) {
    std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>> uses = std::make_shared<std::vector<std::shared_ptr<HeaderTypeUse>>>(std::vector<std::shared_ptr<HeaderTypeUse>>{});
    collectHeaderTypeUses(plan->functionSignatures, uses);
    collectHeaderTypeUses(plan->nativeAdapterSignatures, uses);
    collectHeaderTypeUses(plan->earlyModuleValueDeclarations, uses);
    collectHeaderTypeUses(plan->moduleValueDeclarations, uses);
    collectHeaderTypeUses(plan->earlyClassDefinitions, uses);
    collectHeaderTypeUses(plan->classDefinitions, uses);
    collectHeaderTypeUses(plan->interfaceAliases, uses);
    collectHeaderTypeUses(plan->enumDefinitions, uses);
    collectHeaderTypeUses(plan->earlyTypeAliases, uses);
    collectHeaderTypeUses(plan->typeAliases, uses);
    const auto& _iterable_92 = uses;
    for (const auto& use : *_iterable_92) {
        if (use->count < 2) {
            continue;
        }
        auto name = preferredHeaderTypeAlias(plan, use->spelling);
        if (name == std::string("")) {
            (name = nextHeaderTypeAliasName(plan, state));
            plan->ephemeralTypeAliases->push_back(((((std::string("using ") + name) + std::string(" = ")) + use->spelling) + std::string(";\n")));
        }
        replaceHeaderTypeUses(plan->functionSignatures, use->spelling, name);
        replaceHeaderTypeUses(plan->nativeAdapterSignatures, use->spelling, name);
        replaceHeaderTypeUses(plan->earlyModuleValueDeclarations, use->spelling, name);
        replaceHeaderTypeUses(plan->moduleValueDeclarations, use->spelling, name);
        replaceHeaderTypeUses(plan->earlyClassDefinitions, use->spelling, name);
        replaceHeaderTypeUses(plan->classDefinitions, use->spelling, name);
        replaceHeaderTypeUses(plan->interfaceAliases, use->spelling, name);
        replaceHeaderTypeUses(plan->enumDefinitions, use->spelling, name);
        if (preferredHeaderTypeAlias(plan, use->spelling) == std::string("")) {
            replaceHeaderTypeUses(plan->earlyTypeAliases, use->spelling, name);
            replaceHeaderTypeUses(plan->typeAliases, use->spelling, name);
        }
    }
}
std::string nextHeaderTypeAliasName(const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<HeaderCompressionState>& state) {
    while (true) {
        const auto candidate = (std::string("doof_header_type_") + doof::to_string(state->nextAnonymousTypeIndex));
        (state->nextAnonymousTypeIndex += 1);
        auto occupied = false;
        const auto& _iterable_94 = plan->reservedNamespaceNames;
        for (const auto& existing : *_iterable_94) {
            if (existing == candidate) {
                (occupied = true);
                break;
            }
        }
        if (!occupied) {
            plan->reservedNamespaceNames->push_back(candidate);
            return candidate;
        }
    }
    return std::string("");
}
void reserveHeaderNamespaceName(const std::shared_ptr<HeaderPlan>& plan, const std::string& name) {
    const auto emitted = ::app_src_emitter_expr_::cppIdentifier(name);
    const auto& _iterable_96 = plan->reservedNamespaceNames;
    for (const auto& existing : *_iterable_96) {
        if (existing == emitted) {
            return;
        }
    }
    plan->reservedNamespaceNames->push_back(emitted);
}
std::string preferredHeaderTypeAlias(const std::shared_ptr<HeaderPlan>& plan, const std::string& spelling) {
    for (int32_t index = 0; index < static_cast<int32_t>((plan->preferredTypeAliasSpellings)->size()); ++index) {
        if (doof::array_at(plan->preferredTypeAliasSpellings, index, "src/emitter-header", 491) == spelling) {
            return doof::array_at(plan->preferredTypeAliasNames, index, "src/emitter-header", 491);
        }
    }
    return std::string("");
}
void collectHeaderTypeUses(const std::shared_ptr<std::vector<std::string>>& values, const std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>>& uses) {
    const auto& _iterable_99 = values;
    for (const auto& value : *_iterable_99) {
        auto offset = 0;
        const auto prefix = std::string("std::variant<");
        while (offset < static_cast<int32_t>(value.size())) {
            const auto relative = doof::string_indexOf(doof::string_substring(value, offset, static_cast<int32_t>(value.size())), prefix);
            if (relative < 0) {
                break;
            }
            const auto start = (offset + relative);
            const auto end = matchingAngleEnd(value, ((start + static_cast<int32_t>(prefix.size())) - 1));
            if (end < 0) {
                break;
            }
            const auto spelling = doof::string_substring(value, start, (end + 1));
            if (referenceOnlyVariant(spelling)) {
                addHeaderTypeUse(uses, spelling);
            }
            (offset = (end + 1));
        }
    }
}
int32_t matchingAngleEnd(const std::string& value, int32_t opening) {
    auto depth = 0;
    for (int32_t index = opening; index < static_cast<int32_t>(value.size()); ++index) {
        if (doof::string_at(value, index, "src/emitter-header", 516) == U'\u003C') {
            (depth += 1);
        } else if (doof::string_at(value, index, "src/emitter-header", 517) == U'\u003E') {
            (depth -= 1);
            if (depth == 0) {
                return index;
            }
        }
    }
    return -1;
}
bool referenceOnlyVariant(const std::string& spelling) {
    const auto inner = doof::string_substring(spelling, 13, (static_cast<int32_t>(spelling.size()) - 1));
    auto memberStart = 0;
    auto depth = 0;
    for (int32_t index = 0; index <= static_cast<int32_t>(inner.size()); ++index) {
        const auto atEnd = (index == static_cast<int32_t>(inner.size()));
        if (!atEnd) {
            if (doof::string_at(inner, index, "src/emitter-header", 532) == U'\u003C') {
                (depth += 1);
            } else if (doof::string_at(inner, index, "src/emitter-header", 533) == U'\u003E') {
                (depth -= 1);
            }
        }
        if (atEnd || ((doof::string_at(inner, index, "src/emitter-header", 535) == U'\u002C') && (depth == 0))) {
            const auto member = doof::string_trim(doof::string_substring(inner, memberStart, index));
            if ((member != std::string("std::monostate")) && !(doof::string_startsWith(member, std::string("std::shared_ptr<")) && doof::string_endsWith(member, std::string(">")))) {
                return false;
            }
            (memberStart = (index + 1));
        }
    }
    return true;
}
void addHeaderTypeUse(const std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>>& uses, const std::string& spelling) {
    const auto& _iterable_103 = uses;
    for (const auto& use : *_iterable_103) {
        if (use->spelling == spelling) {
            (use->count += 1);
            return;
        }
    }
    uses->push_back(std::make_shared<HeaderTypeUse>(spelling, 1));
}
void replaceHeaderTypeUses(const std::shared_ptr<std::vector<std::string>>& values, const std::string& spelling, const std::string& name) {
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        (doof::array_at(values, index, "src/emitter-header", 552) = doof::string_replaceAll(doof::array_at(values, index, "src/emitter-header", 552), spelling, name));
    }
}
void collectModuleValueDeclaration(const std::shared_ptr<HeaderPlan>& plan, const std::string& declaration, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
    if (moduleValueDeclarationNeedsIncludes(type_)) {
        plan->moduleValueDeclarations->push_back(declaration);
    } else {
        plan->earlyModuleValueDeclarations->push_back(declaration);
    }
}
bool moduleValueDeclarationNeedsIncludes(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if ((class_->symbol->kind == std::string("struct")) || class_->symbol->native_) {
                return true;
            }
            const auto& _iterable_106 = class_->typeArgs;
            for (const auto& argument : *_iterable_106) {
                if (moduleValueDeclarationNeedsIncludes(argument)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return moduleValueDeclarationNeedsIncludes(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            return (moduleValueDeclarationNeedsIncludes(map->keyType) || moduleValueDeclarationNeedsIncludes(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            return moduleValueDeclarationNeedsIncludes(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            return moduleValueDeclarationNeedsIncludes(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            return (moduleValueDeclarationNeedsIncludes(result->valueType) || moduleValueDeclarationNeedsIncludes(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_108 = tuple->elements;
            for (const auto& element : *_iterable_108) {
                if (moduleValueDeclarationNeedsIncludes(element)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_110 = union_->types;
            for (const auto& member : *_iterable_110) {
                if (moduleValueDeclarationNeedsIncludes(member)) {
                    return true;
                }
            }
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            return moduleValueDeclarationNeedsIncludes(weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_112 = function_->params;
            for (const auto& parameter : *_iterable_112) {
                if (moduleValueDeclarationNeedsIncludes(parameter->type_)) {
                    return true;
                }
            }
            return moduleValueDeclarationNeedsIncludes(function_->returnType);
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
std::string emitModuleValueDeclaration(const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    return ((((std::string("extern ") + ::app_src_emitter_types_::emitContextType(type_, context)) + std::string(" ")) + name) + std::string(";\n"));
}
void addUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    const auto& _iterable_114 = values;
    for (const auto& existing : *_iterable_114) {
        if (existing == value) {
            return;
        }
    }
    values->push_back(value);
}
void addNativeClassForwardDeclaration(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::shared_ptr<HeaderPlan>& plan) {
    const auto cppName = ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName);
    const auto namespace_ = nativeNamespace(cppName);
    const auto name = ((namespace_ == std::string("")) ? cppName : doof::string_substring(cppName, (static_cast<int32_t>(namespace_.size()) + 2), static_cast<int32_t>(cppName.size())));
    const auto declaration = ((namespace_ == std::string("")) ? ((std::string("class ") + name) + std::string(";\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { class ")) + name) + std::string("; }\n")));
    addUnique(plan->typeOnlyForwardDeclarations, declaration);
}
std::string nativeNamespace(const std::string& cppName) {
    auto separator = -1;
    for (int32_t i = 0; i < static_cast<int32_t>(cppName.size()); ++i) {
        if (((i + 1) < static_cast<int32_t>(cppName.size())) && (doof::string_substring(cppName, i, (i + 2)) == std::string("::"))) {
            (separator = i);
        }
    }
    if (separator < 0) {
        return std::string("");
    }
    return doof::string_substring(cppName, 0, separator);
}
std::string emitEnumDeclaration(const std::shared_ptr<::app_src_ast_::EnumDeclaration>& declaration, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto result = (((::app_src_emitter_decl_::emitDescriptionComment(declaration->description, std::string("")) + std::string("enum class ")) + declaration->name) + std::string(" {\n"));
    for (int32_t i = 0; i < static_cast<int32_t>((declaration->variants)->size()); ++i) {
        const auto variant = doof::array_at(declaration->variants, i, "src/emitter-header", 634);
        (result = (((result + ::app_src_emitter_decl_::emitDescriptionComment(variant->description, std::string("    "))) + std::string("    ")) + variant->name));
        if (!doof::is_null(variant->value)) {
            (result = ((result + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(variant->value), context, std::monostate{})));
        }
        if ((i + 1) < static_cast<int32_t>((declaration->variants)->size())) {
            (result = (result + std::string(",")));
        }
        (result = (result + std::string("\n")));
    }
    (result = (result + std::string("};\n")));
    (result = (((((result + std::string("inline const char* ")) + declaration->name) + std::string("_name(")) + declaration->name) + std::string(" value) {\n")));
    (result = (result + std::string("  switch (value) {\n")));
    const auto& _iterable_118 = declaration->variants;
    for (const auto& variant : *_iterable_118) {
        (result = (((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return \"")) + variant->name) + std::string("\";\n")));
    }
    (result = (result + std::string("  }\n  return \"\";\n}\n")));
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromName(std::string_view value) {\n")));
    const auto& _iterable_120 = declaration->variants;
    for (const auto& variant : *_iterable_120) {
        (result = (((((((result + std::string("  if (value == \"")) + variant->name) + std::string("\") return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
    (result = (result + std::string("  return std::nullopt;\n}\n")));
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromValue(int32_t value) {\n")));
    (result = (((result + std::string("  switch (static_cast<")) + declaration->name) + std::string(">(value)) {\n")));
    const auto& _iterable_122 = declaration->variants;
    for (const auto& variant : *_iterable_122) {
        (result = (((((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
    (result = (result + std::string("    default: return std::nullopt;\n  }\n}\n")));
    return (((((result + std::string("inline std::ostream& operator<<(std::ostream& output, ")) + declaration->name) + std::string(" value) { return output << ")) + declaration->name) + std::string("_name(value); }\n"));
}
std::string emitTypeAlias(const std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>& alias, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(alias->resolvedType)) {
        doof::panic(((std::string("Type alias ") + alias->name) + std::string(" was not checked before emission")));
    }
    return (((((::app_src_emitter_decl_::emitDescriptionComment(alias->description, std::string("")) + std::string("using ")) + alias->name) + std::string(" = ")) + ::app_src_emitter_types_::emitType(doof::unwrap_optional(alias->resolvedType), context->modulePath)) + std::string(";\n"));
}
bool functionReturnsInt(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
                    return (primitive->name == std::string("int"));
            }
            else {
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
            return false;
    }
    }
    doof::unreachable();
    return false;
}
}
