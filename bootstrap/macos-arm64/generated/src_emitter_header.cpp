#include "src_emitter_header.hpp"

namespace app_src_emitter_header_ {
using namespace ::app_src_ast_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_decl_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_literals_;
using namespace ::app_src_emitter_json_;
using namespace ::app_src_emitter_types_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_names_;
using namespace ::app_src_string_builder_;
using namespace ::app_src_emitter_monomorphize_;


std::shared_ptr<HeaderPlan> planHeader(const std::shared_ptr<::app_src_ast_::Program>& program, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& methods, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::ClassInstantiation>>>& classes) {
    const auto plan = std::make_shared<HeaderPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, false, false);
    const auto& _iterable_2 = program->statements;
    for (const auto& statement : *_iterable_2) {
        (static_cast<void>(collect(statement, plan, context, methods, classes)), std::monostate{});
    }
    const auto& _iterable_4 = plan->nativeNamespaces;
    for (const auto& namespace_ : *_iterable_4) {
        (static_cast<void>(collectNativeModuleTypeAliases(context->modulePath, namespace_, plan, context)), std::monostate{});
    }
    return plan;
}
void collectNativeModuleTypeAliases(const std::string& modulePath, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto& _iterable_10 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_10) {
        if (surface->path != modulePath) {
            continue;
        }
        const auto& _iterable_6 = surface->exports;
        for (const auto& symbol : *_iterable_6) {
            if (isNativeAliasType(symbol) && !surfaceTypeIsGeneric(surface, symbol->name)) {
                (static_cast<void>(addNativeSymbolAlias(symbol, namespace_, plan)), std::monostate{});
            }
        }
        const auto& _iterable_8 = surface->imports;
        for (const auto& imported : *_iterable_8) {
            if (((!doof::is_null(imported->symbol)) && isNativeAliasType(doof::unwrap_optional(imported->symbol))) && !surfaceSymbolIsGeneric(context, doof::unwrap_optional(imported->symbol))) {
                (static_cast<void>(addNativeSymbolAlias(doof::unwrap_optional(imported->symbol), namespace_, plan)), std::monostate{});
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
void collect(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& methods, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::ClassInstantiation>>>& classes) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, class_->name)), std::monostate{});
            if (class_->native_) {
                const auto rawInclude = ((class_->nativeHeader == std::string("")) ? (class_->name + std::string(".hpp")) : class_->nativeHeader);
                const auto include = ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, rawInclude);
                (static_cast<void>(addUnique(plan->nativeIncludes, include)), std::monostate{});
                const auto namespace_ = nativeNamespace(class_->nativeCppName);
                (static_cast<void>(addUnique(plan->nativeNamespaces, namespace_)), std::monostate{});
                (static_cast<void>(collectNativeClassAliases(class_, namespace_, plan, context)), std::monostate{});
            } else if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
                (static_cast<void>(plan->classForwardDeclarations->push_back(((std::string("struct ") + class_->name) + std::string(";\n")))), std::monostate{});
                std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>> concreteMethods = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{});
                const auto ownerKey = ::app_src_emitter_monomorphize_::classInstantiationKey(context->modulePath, class_->name, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
                const auto& _iterable_14 = methods;
                for (const auto& method : *_iterable_14) {
                    if (method->ownerKey == ownerKey) {
                        (static_cast<void>(concreteMethods->push_back(method)), std::monostate{});
                    }
                }
                const auto definition = ::app_src_emitter_decl_::emitClassDeclaration(class_, context, std::string(""), concreteMethods);
                if (classCanEmitBeforeModuleIncludes(class_)) {
                    (static_cast<void>(plan->earlyClassDefinitions->push_back(definition)), std::monostate{});
                } else {
                    (static_cast<void>(plan->classDefinitions->push_back(definition)), std::monostate{});
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, interface_->name)), std::monostate{});
            if (static_cast<int32_t>((interface_->typeParams)->size()) == 0) {
                if (!doof::is_null(interface_->resolvedSymbol)) {
                    const auto& _iterable_16 = interface_->resolvedSymbol->implementations;
                    for (const auto& implementation : *_iterable_16) {
                        if (implementation->native_) {
                            (static_cast<void>(addNativeClassForwardDeclaration(implementation, plan)), std::monostate{});
                        }
                    }
                }
                (static_cast<void>(plan->interfaceAliases->push_back(::app_src_emitter_decl_::emitInterfaceAlias(interface_, context, classes))), std::monostate{});
                const auto declaration = ::app_src_emitter_json_::emitInterfaceJsonDeclaration(interface_);
                if (declaration != std::string("")) {
                    (static_cast<void>(plan->functionSignatures->push_back(declaration)), std::monostate{});
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, enum_->name)), std::monostate{});
            (static_cast<void>(plan->enumDefinitions->push_back(emitEnumDeclaration(enum_, context))), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, alias->name)), std::monostate{});
            if (static_cast<int32_t>((alias->typeParams)->size()) == 0) {
                const auto emitted = emitTypeAlias(alias, context);
                if ((!doof::is_null(alias->resolvedType)) && !typeNeedsCompleteNominalDefinition(doof::unwrap_optional(alias->resolvedType))) {
                    (static_cast<void>(plan->earlyTypeAliases->push_back(emitted)), std::monostate{});
                    const auto spelling = ::app_src_emitter_types_::emitType(doof::unwrap_optional(alias->resolvedType), context->modulePath);
                    if (referenceOnlyVariant(spelling)) {
                        (static_cast<void>(plan->preferredTypeAliasNames->push_back(alias->name)), std::monostate{});
                        (static_cast<void>(plan->preferredTypeAliasSpellings->push_back(spelling)), std::monostate{});
                    }
                } else {
                    (static_cast<void>(plan->typeAliases->push_back(emitted)), std::monostate{});
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, const_->name)), std::monostate{});
            (static_cast<void>(collectModuleValueDeclaration(plan, (::app_src_emitter_decl_::emitDescriptionComment(const_->description, std::string("")) + emitModuleValueDeclaration(const_->name, doof::unwrap_optional(const_->resolvedType), context)), doof::unwrap_optional(const_->resolvedType))), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, readonly_->name)), std::monostate{});
            (static_cast<void>(collectModuleValueDeclaration(plan, (::app_src_emitter_decl_::emitDescriptionComment(readonly_->description, std::string("")) + emitModuleValueDeclaration(readonly_->name, doof::unwrap_optional(readonly_->resolvedType), context)), doof::unwrap_optional(readonly_->resolvedType))), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, binding->name)), std::monostate{});
            (static_cast<void>(collectModuleValueDeclaration(plan, emitModuleValueDeclaration(binding->name, doof::unwrap_optional(binding->resolvedType), context), doof::unwrap_optional(binding->resolvedType))), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, let_->name)), std::monostate{});
            (static_cast<void>(collectModuleValueDeclaration(plan, emitModuleValueDeclaration(let_->name, doof::unwrap_optional(let_->resolvedType), context), doof::unwrap_optional(let_->resolvedType))), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            (static_cast<void>(reserveHeaderNamespaceName(plan, ((fn->name == std::string("main")) ? std::string("doof_main") : fn->name))), std::monostate{});
            if (fn->native_) {
                if (fn->nativeHeader != std::string("")) {
                    (static_cast<void>(addUnique(plan->nativeIncludes, ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, fn->nativeHeader))), std::monostate{});
                }
                const auto namespace_ = nativeNamespace(fn->nativeCppName);
                (static_cast<void>(addUnique(plan->nativeNamespaces, namespace_)), std::monostate{});
                if (!doof::is_null(fn->resolvedType)) {
                    (static_cast<void>(collectNativeTypeAliases(doof::unwrap_optional(fn->resolvedType), namespace_, plan, context)), std::monostate{});
                }
                return;
            }
            if (fn->name == std::string("main")) {
                (plan->hasMain = true);
                (plan->mainReturnsInt = functionReturnsInt(fn));
                (plan->mainAcceptsArgs = (static_cast<int32_t>((fn->params)->size()) == 1));
                (static_cast<void>(plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string("doof_main"), context->modulePath, context))), std::monostate{});
            } else if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
            } else {
                (static_cast<void>(plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string(""), context->modulePath, context))), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
            (static_cast<void>(collect(export_->declaration, plan, context, methods, classes)), std::monostate{});
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
            (static_cast<void>(collectNativeTypeAliases(doof::unwrap_optional(field->resolvedType), namespace_, plan, context)), std::monostate{});
        }
    }
    const auto& _iterable_32 = class_->methods;
    for (const auto& method : *_iterable_32) {
        if (!doof::is_null(method->resolvedType)) {
            (static_cast<void>(collectNativeTypeAliases(doof::unwrap_optional(method->resolvedType), namespace_, plan, context)), std::monostate{});
        }
    }
}
void collectNativeTypeAliases(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if (!surfaceSymbolIsGeneric(context, class_->symbol)) {
                (static_cast<void>(addNativeSymbolAlias(class_->symbol, namespace_, plan)), std::monostate{});
            }
            const auto& _iterable_34 = class_->typeArgs;
            for (const auto& argument : *_iterable_34) {
                (static_cast<void>(collectNativeTypeAliases(argument, namespace_, plan, context)), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            (static_cast<void>(addNativeSymbolAlias(enum_->symbol, namespace_, plan)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            if (!surfaceSymbolIsGeneric(context, interface_->symbol)) {
                (static_cast<void>(addNativeSymbolAlias(interface_->symbol, namespace_, plan)), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            (static_cast<void>(collectNativeTypeAliases(array->elementType, namespace_, plan, context)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            (static_cast<void>(collectNativeTypeAliases(map->keyType, namespace_, plan, context)), std::monostate{});
            (static_cast<void>(collectNativeTypeAliases(map->valueType, namespace_, plan, context)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            (static_cast<void>(collectNativeTypeAliases(set_->elementType, namespace_, plan, context)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            (static_cast<void>(collectNativeTypeAliases(stream->elementType, namespace_, plan, context)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            (static_cast<void>(collectNativeTypeAliases(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), namespace_, plan, context)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            (static_cast<void>(collectNativeTypeAliases(promise->valueType, namespace_, plan, context)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            (static_cast<void>(collectNativeTypeAliases(result->valueType, namespace_, plan, context)), std::monostate{});
            (static_cast<void>(collectNativeTypeAliases(result->errorType, namespace_, plan, context)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            const auto& _iterable_36 = tuple->elements;
            for (const auto& element : *_iterable_36) {
                (static_cast<void>(collectNativeTypeAliases(element, namespace_, plan, context)), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            const auto& _iterable_38 = union_->types;
            for (const auto& member : *_iterable_38) {
                (static_cast<void>(collectNativeTypeAliases(member, namespace_, plan, context)), std::monostate{});
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
            (static_cast<void>(collectNativeTypeAliases(weak_->inner, namespace_, plan, context)), std::monostate{});
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            const auto& _iterable_40 = function_->params;
            for (const auto& parameter : *_iterable_40) {
                (static_cast<void>(collectNativeTypeAliases(parameter->type_, namespace_, plan, context)), std::monostate{});
            }
            (static_cast<void>(collectNativeTypeAliases(function_->returnType, namespace_, plan, context)), std::monostate{});
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
        (static_cast<void>(addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { struct ")) + symbol->name) + std::string("; }\n")))), std::monostate{});
    } else if (symbol->kind == std::string("enum")) {
        (static_cast<void>(addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { enum class ")) + symbol->name) + std::string("; }\n")))), std::monostate{});
    }
    const auto alias = ((((((std::string("using ") + symbol->name) + std::string(" = ::")) + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string("::")) + symbol->name) + std::string(";"));
    (static_cast<void>(addUnique(plan->nativeAliases, ((namespace_ == std::string("")) ? (alias + std::string("\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { ")) + alias) + std::string(" }\n"))))), std::monostate{});
}
std::string renderProjectedHeader(const std::shared_ptr<std::vector<std::shared_ptr<HeaderSection>>>& sections) {
    const auto compression = std::make_shared<HeaderCompressionState>(1);
    const auto& _iterable_44 = sections;
    for (const auto& section : *_iterable_44) {
        (static_cast<void>(compressRepeatedHeaderVariants(section->plan, compression)), std::monostate{});
    }
    const auto result = ::doof::StringBuilder::constructor();
    (static_cast<void>(result->append(std::string("#pragma once\n"))), std::monostate{});
    (static_cast<void>(result->append(std::string("#include \"doof_runtime.hpp\"\n"))), std::monostate{});
    auto emittedForward = false;
    const auto& _iterable_48 = sections;
    for (const auto& section : *_iterable_48) {
        const auto& _iterable_46 = section->plan->typeOnlyForwardDeclarations;
        for (const auto& declaration : *_iterable_46) {
            (static_cast<void>(result->append(declaration)), std::monostate{});
            (emittedForward = true);
        }
    }
    if (emittedForward) {
        (static_cast<void>(result->append(std::string("\n"))), std::monostate{});
    }
    const auto& _iterable_54 = sections;
    for (const auto& section : *_iterable_54) {
        if (((static_cast<int32_t>((section->plan->classForwardDeclarations)->size()) == 0) && (static_cast<int32_t>((section->plan->earlyModuleValueDeclarations)->size()) == 0)) && headerPlanEmitsNamespaceContent(section->plan)) {
            continue;
        }
        (static_cast<void>(result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")))), std::monostate{});
        const auto& _iterable_50 = section->plan->classForwardDeclarations;
        for (const auto& declaration : *_iterable_50) {
            (static_cast<void>(result->append((std::string("    ") + declaration))), std::monostate{});
        }
        const auto& _iterable_52 = section->plan->earlyModuleValueDeclarations;
        for (const auto& declaration : *_iterable_52) {
            (static_cast<void>(result->append((std::string("    ") + declaration))), std::monostate{});
        }
        (static_cast<void>(result->append(std::string("}\n\n"))), std::monostate{});
    }
    const auto& _iterable_58 = sections;
    for (const auto& section : *_iterable_58) {
        if (static_cast<int32_t>((section->plan->ephemeralTypeAliases)->size()) > 0) {
            (static_cast<void>(result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")))), std::monostate{});
            const auto& _iterable_56 = section->plan->ephemeralTypeAliases;
            for (const auto& alias : *_iterable_56) {
                (static_cast<void>(result->append((std::string("    ") + alias))), std::monostate{});
            }
            (static_cast<void>(result->append(std::string("}\n\n"))), std::monostate{});
        }
    }
    const auto& _iterable_62 = sections;
    for (const auto& section : *_iterable_62) {
        if (static_cast<int32_t>((section->plan->enumDefinitions)->size()) > 0) {
            (static_cast<void>(result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")))), std::monostate{});
            const auto& _iterable_60 = section->plan->enumDefinitions;
            for (const auto& definition : *_iterable_60) {
                (static_cast<void>(result->append((std::string("    ") + definition))), std::monostate{});
            }
            (static_cast<void>(result->append(std::string("}\n\n"))), std::monostate{});
        }
    }
    const auto& _iterable_66 = sections;
    for (const auto& section : *_iterable_66) {
        if (static_cast<int32_t>((section->plan->interfaceAliases)->size()) > 0) {
            (static_cast<void>(result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")))), std::monostate{});
            const auto& _iterable_64 = section->plan->interfaceAliases;
            for (const auto& alias : *_iterable_64) {
                (static_cast<void>(result->append((std::string("    ") + alias))), std::monostate{});
            }
            (static_cast<void>(result->append(std::string("}\n\n"))), std::monostate{});
        }
    }
    const auto& _iterable_70 = sections;
    for (const auto& section : *_iterable_70) {
        if (static_cast<int32_t>((section->plan->earlyTypeAliases)->size()) > 0) {
            (static_cast<void>(result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")))), std::monostate{});
            const auto& _iterable_68 = section->plan->earlyTypeAliases;
            for (const auto& alias : *_iterable_68) {
                (static_cast<void>(result->append((std::string("    ") + alias))), std::monostate{});
            }
            (static_cast<void>(result->append(std::string("}\n\n"))), std::monostate{});
        }
    }
    const auto& _iterable_74 = sections;
    for (const auto& section : *_iterable_74) {
        if (static_cast<int32_t>((section->plan->earlyClassDefinitions)->size()) > 0) {
            (static_cast<void>(result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")))), std::monostate{});
            const auto& _iterable_72 = section->plan->earlyClassDefinitions;
            for (const auto& definition : *_iterable_72) {
                (static_cast<void>(result->append((std::string("    ") + definition))), std::monostate{});
            }
            (static_cast<void>(result->append(std::string("}\n\n"))), std::monostate{});
        }
    }
    const auto& _iterable_80 = sections;
    for (const auto& section : *_iterable_80) {
        auto emittedNative = false;
        const auto& _iterable_76 = section->plan->nativeAliases;
        for (const auto& alias : *_iterable_76) {
            (static_cast<void>(result->append(alias)), std::monostate{});
            (emittedNative = true);
        }
        const auto& _iterable_78 = section->plan->nativeIncludes;
        for (const auto& include : *_iterable_78) {
            if (doof::string_startsWith(include, std::string("<"))) {
                (static_cast<void>(result->append(((std::string("#include ") + include) + std::string("\n")))), std::monostate{});
            } else {
                (static_cast<void>(result->append(((std::string("#include \"") + include) + std::string("\"\n")))), std::monostate{});
            }
            (emittedNative = true);
        }
        if (emittedNative) {
            (static_cast<void>(result->append(std::string("\n"))), std::monostate{});
        }
        (static_cast<void>(renderFinalSection(result, section)), std::monostate{});
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
    (static_cast<void>(result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")))), std::monostate{});
    const auto& _iterable_82 = plan->nativeAdapterSignatures;
    for (const auto& signature : *_iterable_82) {
        (static_cast<void>(result->append((std::string("    ") + signature))), std::monostate{});
    }
    const auto& _iterable_84 = plan->moduleValueDeclarations;
    for (const auto& declaration : *_iterable_84) {
        (static_cast<void>(result->append((std::string("    ") + declaration))), std::monostate{});
    }
    const auto& _iterable_86 = plan->classDefinitions;
    for (const auto& definition : *_iterable_86) {
        (static_cast<void>(result->append((std::string("    ") + definition))), std::monostate{});
    }
    const auto& _iterable_88 = plan->typeAliases;
    for (const auto& alias : *_iterable_88) {
        (static_cast<void>(result->append((std::string("    ") + alias))), std::monostate{});
    }
    const auto& _iterable_90 = plan->functionSignatures;
    for (const auto& signature : *_iterable_90) {
        (static_cast<void>(result->append((std::string("    ") + signature))), std::monostate{});
    }
    (static_cast<void>(result->append(std::string("}\n\n"))), std::monostate{});
}
bool headerPlanEmitsNamespaceContent(const std::shared_ptr<HeaderPlan>& plan) {
    return ((((((((((static_cast<int32_t>((plan->ephemeralTypeAliases)->size()) > 0) || (static_cast<int32_t>((plan->enumDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->interfaceAliases)->size()) > 0)) || (static_cast<int32_t>((plan->earlyClassDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->earlyTypeAliases)->size()) > 0)) || (static_cast<int32_t>((plan->nativeAdapterSignatures)->size()) > 0)) || (static_cast<int32_t>((plan->moduleValueDeclarations)->size()) > 0)) || (static_cast<int32_t>((plan->classDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->typeAliases)->size()) > 0)) || (static_cast<int32_t>((plan->functionSignatures)->size()) > 0));
}


void compressRepeatedHeaderVariants(const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<HeaderCompressionState>& state) {
    std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>> uses = std::make_shared<std::vector<std::shared_ptr<HeaderTypeUse>>>(std::vector<std::shared_ptr<HeaderTypeUse>>{});
    (static_cast<void>(collectHeaderTypeUses(plan->functionSignatures, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->nativeAdapterSignatures, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->earlyModuleValueDeclarations, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->moduleValueDeclarations, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->earlyClassDefinitions, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->classDefinitions, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->interfaceAliases, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->enumDefinitions, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->earlyTypeAliases, uses)), std::monostate{});
    (static_cast<void>(collectHeaderTypeUses(plan->typeAliases, uses)), std::monostate{});
    const auto& _iterable_92 = uses;
    for (const auto& use : *_iterable_92) {
        if (use->count < 2) {
            continue;
        }
        auto name = preferredHeaderTypeAlias(plan, use->spelling);
        if (name == std::string("")) {
            (name = nextHeaderTypeAliasName(plan, state));
            (static_cast<void>(plan->ephemeralTypeAliases->push_back(((((std::string("using ") + name) + std::string(" = ")) + use->spelling) + std::string(";\n")))), std::monostate{});
        }
        (static_cast<void>(replaceHeaderTypeUses(plan->functionSignatures, use->spelling, name)), std::monostate{});
        (static_cast<void>(replaceHeaderTypeUses(plan->nativeAdapterSignatures, use->spelling, name)), std::monostate{});
        (static_cast<void>(replaceHeaderTypeUses(plan->earlyModuleValueDeclarations, use->spelling, name)), std::monostate{});
        (static_cast<void>(replaceHeaderTypeUses(plan->moduleValueDeclarations, use->spelling, name)), std::monostate{});
        (static_cast<void>(replaceHeaderTypeUses(plan->earlyClassDefinitions, use->spelling, name)), std::monostate{});
        (static_cast<void>(replaceHeaderTypeUses(plan->classDefinitions, use->spelling, name)), std::monostate{});
        (static_cast<void>(replaceHeaderTypeUses(plan->interfaceAliases, use->spelling, name)), std::monostate{});
        (static_cast<void>(replaceHeaderTypeUses(plan->enumDefinitions, use->spelling, name)), std::monostate{});
        if (preferredHeaderTypeAlias(plan, use->spelling) == std::string("")) {
            (static_cast<void>(replaceHeaderTypeUses(plan->earlyTypeAliases, use->spelling, name)), std::monostate{});
            (static_cast<void>(replaceHeaderTypeUses(plan->typeAliases, use->spelling, name)), std::monostate{});
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
            (static_cast<void>(plan->reservedNamespaceNames->push_back(candidate)), std::monostate{});
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
    (static_cast<void>(plan->reservedNamespaceNames->push_back(emitted)), std::monostate{});
}
std::string preferredHeaderTypeAlias(const std::shared_ptr<HeaderPlan>& plan, const std::string& spelling) {
    for (int32_t index = 0; index < static_cast<int32_t>((plan->preferredTypeAliasSpellings)->size()); ++index) {
        if (doof::array_at(plan->preferredTypeAliasSpellings, index, "src/emitter-header", 492) == spelling) {
            return doof::array_at(plan->preferredTypeAliasNames, index, "src/emitter-header", 492);
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
                (static_cast<void>(addHeaderTypeUse(uses, spelling)), std::monostate{});
            }
            (offset = (end + 1));
        }
    }
}
int32_t matchingAngleEnd(const std::string& value, int32_t opening) {
    auto depth = 0;
    for (int32_t index = opening; index < static_cast<int32_t>(value.size()); ++index) {
        if (doof::string_at(value, index, "src/emitter-header", 517) == U'\u003C') {
            (depth += 1);
        } else if (doof::string_at(value, index, "src/emitter-header", 518) == U'\u003E') {
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
            if (doof::string_at(inner, index, "src/emitter-header", 533) == U'\u003C') {
                (depth += 1);
            } else if (doof::string_at(inner, index, "src/emitter-header", 534) == U'\u003E') {
                (depth -= 1);
            }
        }
        if (atEnd || ((doof::string_at(inner, index, "src/emitter-header", 536) == U'\u002C') && (depth == 0))) {
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
    (static_cast<void>(uses->push_back(std::make_shared<HeaderTypeUse>(spelling, 1))), std::monostate{});
}
void replaceHeaderTypeUses(const std::shared_ptr<std::vector<std::string>>& values, const std::string& spelling, const std::string& name) {
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        (doof::array_at(values, index, "src/emitter-header", 553) = doof::string_replaceAll(doof::array_at(values, index, "src/emitter-header", 553), spelling, name));
    }
}
void collectModuleValueDeclaration(const std::shared_ptr<HeaderPlan>& plan, const std::string& declaration, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
    if (moduleValueDeclarationNeedsIncludes(type_)) {
        (static_cast<void>(plan->moduleValueDeclarations->push_back(declaration)), std::monostate{});
    } else {
        (static_cast<void>(plan->earlyModuleValueDeclarations->push_back(declaration)), std::monostate{});
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
    (static_cast<void>(values->push_back(value)), std::monostate{});
}
void addNativeClassForwardDeclaration(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::shared_ptr<HeaderPlan>& plan) {
    const auto cppName = ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName);
    const auto namespace_ = nativeNamespace(cppName);
    const auto name = ((namespace_ == std::string("")) ? cppName : doof::string_substring(cppName, (static_cast<int32_t>(namespace_.size()) + 2), static_cast<int32_t>(cppName.size())));
    const auto declaration = ((namespace_ == std::string("")) ? ((std::string("class ") + name) + std::string(";\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { class ")) + name) + std::string("; }\n")));
    (static_cast<void>(addUnique(plan->typeOnlyForwardDeclarations, declaration)), std::monostate{});
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
        const auto variant = doof::array_at(declaration->variants, i, "src/emitter-header", 635);
        (result = (((result + ::app_src_emitter_decl_::emitDescriptionComment(variant->description, std::string("    "))) + std::string("    ")) + variant->name));
        if (declaration->backingKind == std::string("string")) {
            (result = ((result + std::string(" = ")) + doof::to_string(i)));
        } else if (!doof::is_null(variant->resolvedIntValue)) {
            (result = ((result + std::string(" = ")) + doof::to_string(doof::unwrap_optional(variant->resolvedIntValue))));
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
    (result = (((result + std::string("  }\n  doof::panic(std::string(\"Invalid ")) + declaration->name) + std::string(" enum value: \") + doof::to_string(static_cast<int32_t>(value)));\n}\n")));
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromName(std::string_view value) {\n")));
    const auto& _iterable_120 = declaration->variants;
    for (const auto& variant : *_iterable_120) {
        (result = (((((((result + std::string("  if (value == \"")) + variant->name) + std::string("\") return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
    (result = (result + std::string("  return std::nullopt;\n}\n")));
    if (declaration->backingKind == std::string("string")) {
        (result = (((((result + std::string("inline std::string ")) + declaration->name) + std::string("_value(")) + declaration->name) + std::string(" value) {\n  switch (value) {\n")));
        const auto& _iterable_123 = declaration->variants;
        for (const auto& variant : *_iterable_123) {
            (result = (((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return ")) + ::app_src_emitter_expr_literals_::quote([&]() -> std::string { auto _coalesce_121 = variant->resolvedStringValue; if (doof::is_null(_coalesce_121)) return std::string(""); return doof::unwrap_optional(_coalesce_121); }())) + std::string(";\n")));
        }
        (result = (((result + std::string("  }\n  doof::panic(std::string(\"Invalid ")) + declaration->name) + std::string(" enum value: \") + doof::to_string(static_cast<int32_t>(value)));\n}\n")));
        (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromValue(std::string_view value) {\n")));
        const auto& _iterable_126 = declaration->variants;
        for (const auto& variant : *_iterable_126) {
            (result = (((((((result + std::string("  if (value == ")) + ::app_src_emitter_expr_literals_::quote([&]() -> std::string { auto _coalesce_124 = variant->resolvedStringValue; if (doof::is_null(_coalesce_124)) return std::string(""); return doof::unwrap_optional(_coalesce_124); }())) + std::string(") return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
        }
        (result = (result + std::string("  return std::nullopt;\n}\n")));
    } else {
        (result = (((((result + std::string("inline int32_t ")) + declaration->name) + std::string("_value(")) + declaration->name) + std::string(" value) { return static_cast<int32_t>(value); }\n")));
        (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromValue(int32_t value) {\n")));
        const auto& _iterable_129 = declaration->variants;
        for (const auto& variant : *_iterable_129) {
            (result = (((((((result + std::string("  if (value == ")) + doof::to_string([&]() -> int32_t { auto _coalesce_127 = variant->resolvedIntValue; if (doof::is_null(_coalesce_127)) return 0; return doof::unwrap_optional(_coalesce_127); }())) + std::string(") return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
        }
        (result = (result + std::string("  return std::nullopt;\n}\n")));
    }
    (result = (((((((((result + std::string("inline std::shared_ptr<std::vector<")) + declaration->name) + std::string(">> ")) + declaration->name) + std::string("_values() { return std::make_shared<std::vector<")) + declaration->name) + std::string(">>(std::initializer_list<")) + declaration->name) + std::string(">{")));
    for (int32_t i = 0; i < static_cast<int32_t>((declaration->variants)->size()); ++i) {
        if (i > 0) {
            (result = (result + std::string(", ")));
        }
        (result = (((result + declaration->name) + std::string("::")) + doof::array_at(declaration->variants, i, "src/emitter-header", 670)->name));
    }
    (result = (result + std::string("}); }\n")));
    const auto valueRead = ((declaration->backingKind == std::string("string")) ? std::string("doof::json_as_string(value)") : std::string("doof::json_as_int(value)"));
    const auto typeCheck = ((declaration->backingKind == std::string("string")) ? std::string("doof::json_is_string(value)") : std::string("doof::json_is_integer(value)"));
    const auto expectedType = ((declaration->backingKind == std::string("string")) ? std::string("string") : std::string("integer"));
    (result = (((((((result + std::string("inline doof::JsonValue ")) + declaration->name) + std::string("_toJsonValue(")) + declaration->name) + std::string(" value) { return doof::json_value(")) + declaration->name) + std::string("_value(value)); }\n")));
    (result = (((((result + std::string("inline doof::Result<")) + declaration->name) + std::string(", std::string> ")) + declaration->name) + std::string("_fromJsonValue(const doof::JsonValue& value, bool) {\n")));
    (result = (((((((result + std::string("  if (!(")) + typeCheck) + std::string(")) return doof::Failure<std::string>{std::string(\"Expected ")) + expectedType) + std::string(" for enum ")) + declaration->name) + std::string(", got \") + doof::json_type_name(value)};\n")));
    (result = (((((result + std::string("  auto resolved = ")) + declaration->name) + std::string("_fromValue(")) + valueRead) + std::string(");\n")));
    auto validValues = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((declaration->variants)->size()); ++i) {
        if (i > 0) {
            (validValues = (validValues + std::string(", ")));
        }
        if (declaration->backingKind == std::string("string")) {
            (validValues = (((validValues + std::string("\"")) + [&]() -> std::string { auto _coalesce_131 = doof::array_at(declaration->variants, i, "src/emitter-header", 683)->resolvedStringValue; if (doof::is_null(_coalesce_131)) return std::string(""); return doof::unwrap_optional(_coalesce_131); }()) + std::string("\"")));
        } else {
            (validValues = (validValues + doof::to_string([&]() -> int32_t { auto _coalesce_132 = doof::array_at(declaration->variants, i, "src/emitter-header", 684)->resolvedIntValue; if (doof::is_null(_coalesce_132)) return 0; return doof::unwrap_optional(_coalesce_132); }())));
        }
    }
    (result = (((((((result + std::string("  if (!resolved.has_value()) return doof::Failure<std::string>{std::string(\"Unknown backing value for enum ")) + declaration->name) + std::string(": \") + doof::to_string(")) + valueRead) + std::string(") + ")) + ::app_src_emitter_expr_literals_::quote((std::string("; expected one of ") + validValues))) + std::string("};\n")));
    (result = (((result + std::string("  return doof::Success<")) + declaration->name) + std::string(">{resolved.value()};\n}\n")));
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
