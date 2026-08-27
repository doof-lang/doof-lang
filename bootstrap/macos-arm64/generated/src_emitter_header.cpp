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


#line 58 "/src/emitter-header.do"
std::shared_ptr<HeaderPlan> planHeader(const std::shared_ptr<::app_src_ast_::Program>& program, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& methods) {
#line 59 "/src/emitter-header.do"
    return planHeaders(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}), context, methods);
}
#line 62 "/src/emitter-header.do"
std::shared_ptr<HeaderPlan> planHeaders(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& methods) {
#line 63 "/src/emitter-header.do"
    const auto plan = std::make_shared<HeaderPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, false, false);
#line 64 "/src/emitter-header.do"
    const auto& _iterable_2 = programs;
    for (const auto& program : *_iterable_2) {
#line 65 "/src/emitter-header.do"
        const auto& _iterable_4 = program->statements;
        for (const auto& statement : *_iterable_4) {
#line 65 "/src/emitter-header.do"
            collect(statement, plan, context, methods);
        }
    }
#line 70 "/src/emitter-header.do"
    const auto& _iterable_6 = plan->nativeNamespaces;
    for (const auto& namespace_ : *_iterable_6) {
#line 71 "/src/emitter-header.do"
        collectNativeModuleTypeAliases(context->modulePath, namespace_, plan, context);
    }
#line 73 "/src/emitter-header.do"
    return plan;
}
#line 76 "/src/emitter-header.do"
void collectNativeModuleTypeAliases(const std::string& modulePath, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 77 "/src/emitter-header.do"
    const auto& _iterable_8 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_8) {
#line 78 "/src/emitter-header.do"
        if (surface->path != modulePath) {
#line 78 "/src/emitter-header.do"
            continue;
        }
#line 79 "/src/emitter-header.do"
        const auto& _iterable_10 = surface->exports;
        for (const auto& symbol : *_iterable_10) {
#line 80 "/src/emitter-header.do"
            if (isNativeAliasType(symbol) && !surfaceTypeIsGeneric(surface, symbol->name)) {
#line 81 "/src/emitter-header.do"
                addNativeSymbolAlias(symbol, namespace_, plan);
            }
        }
#line 84 "/src/emitter-header.do"
        const auto& _iterable_12 = surface->imports;
        for (const auto& imported : *_iterable_12) {
#line 85 "/src/emitter-header.do"
            if (((!doof::is_null(imported->symbol)) && isNativeAliasType(doof::unwrap_optional(imported->symbol))) && !surfaceSymbolIsGeneric(context, doof::unwrap_optional(imported->symbol))) {
#line 86 "/src/emitter-header.do"
                addNativeSymbolAlias(doof::unwrap_optional(imported->symbol), namespace_, plan);
            }
        }
#line 89 "/src/emitter-header.do"
        return;
    }
}
#line 93 "/src/emitter-header.do"
bool surfaceTypeIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>& surface, const std::string& name) {
#line 94 "/src/emitter-header.do"
    const auto& _iterable_14 = surface->genericTypes;
    for (const auto& genericName : *_iterable_14) {
#line 94 "/src/emitter-header.do"
        if (genericName == name) {
#line 94 "/src/emitter-header.do"
            return true;
        }
    }
#line 95 "/src/emitter-header.do"
    return false;
}
#line 98 "/src/emitter-header.do"
bool isNativeAliasType(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 99 "/src/emitter-header.do"
    return (((((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("enum"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("type-alias")));
}
#line 102 "/src/emitter-header.do"
void collect(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& methods) {
#line 103 "/src/emitter-header.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 105 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, class_->name);
#line 106 "/src/emitter-header.do"
            if (class_->native_) {
#line 107 "/src/emitter-header.do"
                const auto rawInclude = ((class_->nativeHeader == std::string("")) ? (class_->name + std::string(".hpp")) : class_->nativeHeader);
#line 108 "/src/emitter-header.do"
                const auto include = ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, rawInclude);
#line 109 "/src/emitter-header.do"
                addUnique(plan->nativeIncludes, include);
#line 110 "/src/emitter-header.do"
                const auto namespace_ = nativeNamespace(class_->nativeCppName);
#line 111 "/src/emitter-header.do"
                addUnique(plan->nativeNamespaces, namespace_);
#line 112 "/src/emitter-header.do"
                collectNativeClassAliases(class_, namespace_, plan, context);
            } else if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
#line 114 "/src/emitter-header.do"
                plan->classForwardDeclarations->push_back(((std::string("struct ") + class_->name) + std::string(";\n")));
#line 115 "/src/emitter-header.do"
                std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>> concreteMethods = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{});
#line 116 "/src/emitter-header.do"
                const auto ownerKey = ::app_src_emitter_monomorphize_::classInstantiationKey(context->modulePath, class_->name, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
#line 117 "/src/emitter-header.do"
                const auto& _iterable_16 = methods;
                for (const auto& method : *_iterable_16) {
#line 117 "/src/emitter-header.do"
                    if (method->ownerKey == ownerKey) {
#line 117 "/src/emitter-header.do"
                        concreteMethods->push_back(method);
                    }
                }
#line 118 "/src/emitter-header.do"
                const auto definition = ::app_src_emitter_decl_::emitClassDeclaration(class_, context, std::string(""), concreteMethods);
#line 119 "/src/emitter-header.do"
                if (classCanEmitBeforeModuleIncludes(class_)) {
#line 119 "/src/emitter-header.do"
                    plan->earlyClassDefinitions->push_back(definition);
                } else {
#line 120 "/src/emitter-header.do"
                    plan->classDefinitions->push_back(definition);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 124 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, interface_->name);
#line 125 "/src/emitter-header.do"
            if (static_cast<int32_t>((interface_->typeParams)->size()) == 0) {
#line 126 "/src/emitter-header.do"
                if (!doof::is_null(interface_->resolvedSymbol)) {
#line 127 "/src/emitter-header.do"
                    const auto& _iterable_18 = interface_->resolvedSymbol->implementations;
                    for (const auto& implementation : *_iterable_18) {
#line 128 "/src/emitter-header.do"
                        if (implementation->native_) {
#line 128 "/src/emitter-header.do"
                            addNativeClassForwardDeclaration(implementation, plan);
                        }
                    }
                }
#line 131 "/src/emitter-header.do"
                plan->interfaceAliases->push_back(::app_src_emitter_decl_::emitInterfaceAlias(interface_, context));
#line 132 "/src/emitter-header.do"
                const auto declaration = ::app_src_emitter_json_::emitInterfaceJsonDeclaration(interface_);
#line 133 "/src/emitter-header.do"
                if (declaration != std::string("")) {
#line 133 "/src/emitter-header.do"
                    plan->functionSignatures->push_back(declaration);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 136 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, enum_->name);
#line 136 "/src/emitter-header.do"
            plan->enumDefinitions->push_back(emitEnumDeclaration(enum_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 140 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, alias->name);
#line 141 "/src/emitter-header.do"
            if (static_cast<int32_t>((alias->typeParams)->size()) == 0) {
#line 142 "/src/emitter-header.do"
                const auto emitted = emitTypeAlias(alias, context);
#line 143 "/src/emitter-header.do"
                if ((!doof::is_null(alias->resolvedType)) && !typeNeedsCompleteNominalDefinition(doof::unwrap_optional(alias->resolvedType))) {
#line 144 "/src/emitter-header.do"
                    plan->earlyTypeAliases->push_back(emitted);
#line 145 "/src/emitter-header.do"
                    const auto spelling = ::app_src_emitter_types_::emitType(doof::unwrap_optional(alias->resolvedType), context->modulePath);
#line 146 "/src/emitter-header.do"
                    if (referenceOnlyVariant(spelling)) {
#line 147 "/src/emitter-header.do"
                        plan->preferredTypeAliasNames->push_back(alias->name);
#line 148 "/src/emitter-header.do"
                        plan->preferredTypeAliasSpellings->push_back(spelling);
                    }
                } else {
#line 151 "/src/emitter-header.do"
                    plan->typeAliases->push_back(emitted);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 155 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, const_->name);
#line 156 "/src/emitter-header.do"
            collectModuleValueDeclaration(plan, (::app_src_emitter_decl_::emitDescriptionComment(const_->description, std::string("")) + emitModuleValueDeclaration(const_->name, doof::unwrap_optional(const_->resolvedType), context)), doof::unwrap_optional(const_->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 163 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, readonly_->name);
#line 164 "/src/emitter-header.do"
            collectModuleValueDeclaration(plan, (::app_src_emitter_decl_::emitDescriptionComment(readonly_->description, std::string("")) + emitModuleValueDeclaration(readonly_->name, doof::unwrap_optional(readonly_->resolvedType), context)), doof::unwrap_optional(readonly_->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 171 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, binding->name);
#line 172 "/src/emitter-header.do"
            collectModuleValueDeclaration(plan, emitModuleValueDeclaration(binding->name, doof::unwrap_optional(binding->resolvedType), context), doof::unwrap_optional(binding->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 175 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, let_->name);
#line 176 "/src/emitter-header.do"
            collectModuleValueDeclaration(plan, emitModuleValueDeclaration(let_->name, doof::unwrap_optional(let_->resolvedType), context), doof::unwrap_optional(let_->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 179 "/src/emitter-header.do"
            reserveHeaderNamespaceName(plan, ((fn->name == std::string("main")) ? std::string("doof_main") : fn->name));
#line 180 "/src/emitter-header.do"
            if (fn->native_) {
#line 181 "/src/emitter-header.do"
                if (fn->nativeHeader != std::string("")) {
#line 181 "/src/emitter-header.do"
                    addUnique(plan->nativeIncludes, ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, fn->nativeHeader));
                }
#line 182 "/src/emitter-header.do"
                const auto namespace_ = nativeNamespace(fn->nativeCppName);
#line 183 "/src/emitter-header.do"
                addUnique(plan->nativeNamespaces, namespace_);
#line 184 "/src/emitter-header.do"
                if (!doof::is_null(fn->resolvedType)) {
#line 184 "/src/emitter-header.do"
                    collectNativeTypeAliases(doof::unwrap_optional(fn->resolvedType), namespace_, plan, context);
                }
#line 185 "/src/emitter-header.do"
                return;
            }
#line 187 "/src/emitter-header.do"
            if (fn->name == std::string("main")) {
#line 188 "/src/emitter-header.do"
                (plan->hasMain = true);
#line 189 "/src/emitter-header.do"
                (plan->mainReturnsInt = functionReturnsInt(fn));
#line 190 "/src/emitter-header.do"
                (plan->mainAcceptsArgs = (static_cast<int32_t>((fn->params)->size()) == 1));
#line 191 "/src/emitter-header.do"
                plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string("doof_main"), context->modulePath, context));
            } else if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
            } else {
#line 196 "/src/emitter-header.do"
                plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string(""), context->modulePath, context));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 199 "/src/emitter-header.do"
            collect(export_->declaration, plan, context, methods);
    }
    else {
    }
    }
}
#line 207 "/src/emitter-header.do"
bool classCanEmitBeforeModuleIncludes(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_) {
#line 208 "/src/emitter-header.do"
    if (static_cast<int32_t>((class_->typeParams)->size()) > 0) {
#line 208 "/src/emitter-header.do"
        return false;
    }
#line 209 "/src/emitter-header.do"
    const auto& _iterable_20 = class_->fields;
    for (const auto& field : *_iterable_20) {
#line 210 "/src/emitter-header.do"
        if ((!field->static_ && (!doof::is_null(field->resolvedType))) && typeNeedsCompleteNominalDefinition(doof::unwrap_optional(field->resolvedType))) {
#line 210 "/src/emitter-header.do"
            return false;
        }
    }
#line 212 "/src/emitter-header.do"
    return true;
}
#line 215 "/src/emitter-header.do"
bool typeNeedsCompleteNominalDefinition(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 216 "/src/emitter-header.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 218 "/src/emitter-header.do"
            if ((class_->symbol->kind == std::string("struct")) || class_->symbol->native_) {
#line 218 "/src/emitter-header.do"
                return true;
            }
#line 219 "/src/emitter-header.do"
            const auto& _iterable_22 = class_->typeArgs;
            for (const auto& argument : *_iterable_22) {
#line 219 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(argument)) {
#line 219 "/src/emitter-header.do"
                    return true;
                }
            }
#line 220 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 222 "/src/emitter-header.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 224 "/src/emitter-header.do"
            const auto& _iterable_24 = interface_->typeArgs;
            for (const auto& argument : *_iterable_24) {
#line 224 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(argument)) {
#line 224 "/src/emitter-header.do"
                    return true;
                }
            }
#line 225 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 227 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 229 "/src/emitter-header.do"
            return (typeNeedsCompleteNominalDefinition(map->keyType) || typeNeedsCompleteNominalDefinition(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 231 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 232 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 234 "/src/emitter-header.do"
            return (typeNeedsCompleteNominalDefinition(result->valueType) || typeNeedsCompleteNominalDefinition(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 237 "/src/emitter-header.do"
            const auto& _iterable_26 = tuple->elements;
            for (const auto& element : *_iterable_26) {
#line 237 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(element)) {
#line 237 "/src/emitter-header.do"
                    return true;
                }
            }
#line 238 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 241 "/src/emitter-header.do"
            const auto& _iterable_28 = union_->types;
            for (const auto& member : *_iterable_28) {
#line 241 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(member)) {
#line 241 "/src/emitter-header.do"
                    return true;
                }
            }
#line 242 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 245 "/src/emitter-header.do"
            const auto& _iterable_30 = function_->params;
            for (const auto& parameter : *_iterable_30) {
#line 245 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(parameter->type_)) {
#line 245 "/src/emitter-header.do"
                    return true;
                }
            }
#line 246 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(function_->returnType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 248 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(weak_->inner);
    }
    else {
#line 249 "/src/emitter-header.do"
            return false;
    }
    }
    doof::unreachable();
}
#line 253 "/src/emitter-header.do"
void collectNativeClassAliases(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 254 "/src/emitter-header.do"
    const auto& _iterable_32 = class_->fields;
    for (const auto& field : *_iterable_32) {
#line 254 "/src/emitter-header.do"
        if (!doof::is_null(field->resolvedType)) {
#line 254 "/src/emitter-header.do"
            collectNativeTypeAliases(doof::unwrap_optional(field->resolvedType), namespace_, plan, context);
        }
    }
#line 255 "/src/emitter-header.do"
    const auto& _iterable_34 = class_->methods;
    for (const auto& method : *_iterable_34) {
#line 255 "/src/emitter-header.do"
        if (!doof::is_null(method->resolvedType)) {
#line 255 "/src/emitter-header.do"
            collectNativeTypeAliases(doof::unwrap_optional(method->resolvedType), namespace_, plan, context);
        }
    }
}
#line 258 "/src/emitter-header.do"
void collectNativeTypeAliases(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 259 "/src/emitter-header.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 261 "/src/emitter-header.do"
            if (!surfaceSymbolIsGeneric(context, class_->symbol)) {
#line 261 "/src/emitter-header.do"
                addNativeSymbolAlias(class_->symbol, namespace_, plan);
            }
#line 262 "/src/emitter-header.do"
            const auto& _iterable_36 = class_->typeArgs;
            for (const auto& argument : *_iterable_36) {
#line 262 "/src/emitter-header.do"
                collectNativeTypeAliases(argument, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 264 "/src/emitter-header.do"
            addNativeSymbolAlias(enum_->symbol, namespace_, plan);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 265 "/src/emitter-header.do"
            if (!surfaceSymbolIsGeneric(context, interface_->symbol)) {
#line 265 "/src/emitter-header.do"
                addNativeSymbolAlias(interface_->symbol, namespace_, plan);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 266 "/src/emitter-header.do"
            collectNativeTypeAliases(array->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 268 "/src/emitter-header.do"
            collectNativeTypeAliases(map->keyType, namespace_, plan, context);
#line 269 "/src/emitter-header.do"
            collectNativeTypeAliases(map->valueType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 271 "/src/emitter-header.do"
            collectNativeTypeAliases(set_->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 272 "/src/emitter-header.do"
            collectNativeTypeAliases(stream->elementType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 273 "/src/emitter-header.do"
            collectNativeTypeAliases(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 274 "/src/emitter-header.do"
            collectNativeTypeAliases(promise->valueType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 276 "/src/emitter-header.do"
            collectNativeTypeAliases(result->valueType, namespace_, plan, context);
#line 277 "/src/emitter-header.do"
            collectNativeTypeAliases(result->errorType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 279 "/src/emitter-header.do"
            const auto& _iterable_38 = tuple->elements;
            for (const auto& element : *_iterable_38) {
#line 279 "/src/emitter-header.do"
                collectNativeTypeAliases(element, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 280 "/src/emitter-header.do"
            const auto& _iterable_40 = union_->types;
            for (const auto& member : *_iterable_40) {
#line 280 "/src/emitter-header.do"
                collectNativeTypeAliases(member, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 281 "/src/emitter-header.do"
            collectNativeTypeAliases(weak_->inner, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 283 "/src/emitter-header.do"
            const auto& _iterable_42 = function_->params;
            for (const auto& parameter : *_iterable_42) {
#line 283 "/src/emitter-header.do"
                collectNativeTypeAliases(parameter->type_, namespace_, plan, context);
            }
#line 284 "/src/emitter-header.do"
            collectNativeTypeAliases(function_->returnType, namespace_, plan, context);
    }
    else {
    }
    }
}
#line 290 "/src/emitter-header.do"
bool surfaceSymbolIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 291 "/src/emitter-header.do"
    const auto& _iterable_44 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_44) {
#line 292 "/src/emitter-header.do"
        if (surface->path == symbol->module) {
#line 292 "/src/emitter-header.do"
            return surfaceTypeIsGeneric(surface, symbol->name);
        }
    }
#line 294 "/src/emitter-header.do"
    return false;
}
#line 297 "/src/emitter-header.do"
void addNativeSymbolAlias(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan) {
#line 298 "/src/emitter-header.do"
    if (symbol->native_ || (symbol->module == std::string(""))) {
#line 298 "/src/emitter-header.do"
        return;
    }
#line 299 "/src/emitter-header.do"
    if ((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) {
#line 300 "/src/emitter-header.do"
        addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { struct ")) + symbol->name) + std::string("; }\n")));
    } else if (symbol->kind == std::string("enum")) {
#line 302 "/src/emitter-header.do"
        addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { enum class ")) + symbol->name) + std::string("; }\n")));
    }
#line 304 "/src/emitter-header.do"
    const auto alias = ((((((std::string("using ") + symbol->name) + std::string(" = ::")) + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string("::")) + symbol->name) + std::string(";"));
#line 305 "/src/emitter-header.do"
    addUnique(plan->nativeAliases, ((namespace_ == std::string("")) ? (alias + std::string("\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { ")) + alias) + std::string(" }\n"))));
}
#line 308 "/src/emitter-header.do"
std::string renderHeader(const std::shared_ptr<HeaderPlan>& plan, const std::string& guardName) {
#line 309 "/src/emitter-header.do"
    return renderProjectedHeader(std::make_shared<std::vector<std::shared_ptr<HeaderSection>>>(std::vector<std::shared_ptr<HeaderSection>>{std::make_shared<HeaderSection>(guardName, plan)}));
}
#line 312 "/src/emitter-header.do"
std::string renderProjectedHeader(const std::shared_ptr<std::vector<std::shared_ptr<HeaderSection>>>& sections) {
#line 313 "/src/emitter-header.do"
    const auto compression = std::make_shared<HeaderCompressionState>(1);
#line 314 "/src/emitter-header.do"
    const auto& _iterable_46 = sections;
    for (const auto& section : *_iterable_46) {
#line 314 "/src/emitter-header.do"
        compressRepeatedHeaderVariants(section->plan, compression);
    }
#line 315 "/src/emitter-header.do"
    const auto result = ::doof::StringBuilder::constructor();
#line 316 "/src/emitter-header.do"
    result->append(std::string("#pragma once\n"));
#line 320 "/src/emitter-header.do"
    result->append(std::string("#include \"doof_runtime.hpp\"\n"));
#line 321 "/src/emitter-header.do"
    auto emittedForward = false;
#line 322 "/src/emitter-header.do"
    const auto& _iterable_48 = sections;
    for (const auto& section : *_iterable_48) {
#line 323 "/src/emitter-header.do"
        const auto& _iterable_50 = section->plan->typeOnlyForwardDeclarations;
        for (const auto& declaration : *_iterable_50) {
#line 323 "/src/emitter-header.do"
            result->append(declaration);
#line 323 "/src/emitter-header.do"
            (emittedForward = true);
        }
    }
#line 325 "/src/emitter-header.do"
    if (emittedForward) {
#line 325 "/src/emitter-header.do"
        result->append(std::string("\n"));
    }
#line 328 "/src/emitter-header.do"
    const auto& _iterable_52 = sections;
    for (const auto& section : *_iterable_52) {
#line 329 "/src/emitter-header.do"
        if (((static_cast<int32_t>((section->plan->classForwardDeclarations)->size()) == 0) && (static_cast<int32_t>((section->plan->earlyModuleValueDeclarations)->size()) == 0)) && headerPlanEmitsNamespaceContent(section->plan)) {
#line 331 "/src/emitter-header.do"
            continue;
        }
#line 332 "/src/emitter-header.do"
        result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 333 "/src/emitter-header.do"
        const auto& _iterable_54 = section->plan->classForwardDeclarations;
        for (const auto& declaration : *_iterable_54) {
#line 333 "/src/emitter-header.do"
            result->append((std::string("    ") + declaration));
        }
#line 337 "/src/emitter-header.do"
        const auto& _iterable_56 = section->plan->earlyModuleValueDeclarations;
        for (const auto& declaration : *_iterable_56) {
#line 337 "/src/emitter-header.do"
            result->append((std::string("    ") + declaration));
        }
#line 338 "/src/emitter-header.do"
        result->append(std::string("}\n\n"));
    }
#line 342 "/src/emitter-header.do"
    const auto& _iterable_58 = sections;
    for (const auto& section : *_iterable_58) {
#line 343 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->ephemeralTypeAliases)->size()) > 0) {
#line 344 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 345 "/src/emitter-header.do"
            const auto& _iterable_60 = section->plan->ephemeralTypeAliases;
            for (const auto& alias : *_iterable_60) {
#line 345 "/src/emitter-header.do"
                result->append((std::string("    ") + alias));
            }
#line 346 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 352 "/src/emitter-header.do"
    const auto& _iterable_62 = sections;
    for (const auto& section : *_iterable_62) {
#line 353 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->enumDefinitions)->size()) > 0) {
#line 354 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 355 "/src/emitter-header.do"
            const auto& _iterable_64 = section->plan->enumDefinitions;
            for (const auto& definition : *_iterable_64) {
#line 355 "/src/emitter-header.do"
                result->append((std::string("    ") + definition));
            }
#line 356 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 359 "/src/emitter-header.do"
    const auto& _iterable_66 = sections;
    for (const auto& section : *_iterable_66) {
#line 360 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->interfaceAliases)->size()) > 0) {
#line 361 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 362 "/src/emitter-header.do"
            const auto& _iterable_68 = section->plan->interfaceAliases;
            for (const auto& alias : *_iterable_68) {
#line 362 "/src/emitter-header.do"
                result->append((std::string("    ") + alias));
            }
#line 363 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 366 "/src/emitter-header.do"
    const auto& _iterable_70 = sections;
    for (const auto& section : *_iterable_70) {
#line 367 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->earlyTypeAliases)->size()) > 0) {
#line 368 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 369 "/src/emitter-header.do"
            const auto& _iterable_72 = section->plan->earlyTypeAliases;
            for (const auto& alias : *_iterable_72) {
#line 369 "/src/emitter-header.do"
                result->append((std::string("    ") + alias));
            }
#line 370 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 373 "/src/emitter-header.do"
    const auto& _iterable_74 = sections;
    for (const auto& section : *_iterable_74) {
#line 374 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->earlyClassDefinitions)->size()) > 0) {
#line 375 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 376 "/src/emitter-header.do"
            const auto& _iterable_76 = section->plan->earlyClassDefinitions;
            for (const auto& definition : *_iterable_76) {
#line 376 "/src/emitter-header.do"
                result->append((std::string("    ") + definition));
            }
#line 377 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 384 "/src/emitter-header.do"
    const auto& _iterable_78 = sections;
    for (const auto& section : *_iterable_78) {
#line 385 "/src/emitter-header.do"
        auto emittedNative = false;
#line 386 "/src/emitter-header.do"
        const auto& _iterable_80 = section->plan->nativeAliases;
        for (const auto& alias : *_iterable_80) {
#line 386 "/src/emitter-header.do"
            result->append(alias);
#line 386 "/src/emitter-header.do"
            (emittedNative = true);
        }
#line 387 "/src/emitter-header.do"
        const auto& _iterable_82 = section->plan->nativeIncludes;
        for (const auto& include : *_iterable_82) {
#line 388 "/src/emitter-header.do"
            if (doof::string_startsWith(include, std::string("<"))) {
#line 388 "/src/emitter-header.do"
                result->append(((std::string("#include ") + include) + std::string("\n")));
            } else {
#line 389 "/src/emitter-header.do"
                result->append(((std::string("#include \"") + include) + std::string("\"\n")));
            }
#line 390 "/src/emitter-header.do"
            (emittedNative = true);
        }
#line 392 "/src/emitter-header.do"
        if (emittedNative) {
#line 392 "/src/emitter-header.do"
            result->append(std::string("\n"));
        }
#line 393 "/src/emitter-header.do"
        renderFinalSection(result, section);
    }
#line 395 "/src/emitter-header.do"
    const auto& _iterable_84 = sections;
    for (const auto& section : *_iterable_84) {
#line 396 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->genericFunctionDefinitions)->size()) == 0) {
#line 396 "/src/emitter-header.do"
            continue;
        }
#line 397 "/src/emitter-header.do"
        result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 398 "/src/emitter-header.do"
        const auto& _iterable_86 = section->plan->genericFunctionDefinitions;
        for (const auto& definition : *_iterable_86) {
#line 398 "/src/emitter-header.do"
            result->append(definition);
        }
#line 399 "/src/emitter-header.do"
        result->append(std::string("}\n"));
    }
#line 401 "/src/emitter-header.do"
    auto rendered = result->drainToString();
#line 402 "/src/emitter-header.do"
    while (doof::string_endsWith(rendered, std::string("\n\n"))) {
#line 402 "/src/emitter-header.do"
        (rendered = doof::string_substring(rendered, 0, (static_cast<int32_t>(rendered.size()) - 1)));
    }
#line 403 "/src/emitter-header.do"
    return rendered;
}
#line 406 "/src/emitter-header.do"
void renderFinalSection(const std::shared_ptr<::doof::StringBuilder>& result, const std::shared_ptr<HeaderSection>& section) {
#line 407 "/src/emitter-header.do"
    const auto plan = section->plan;
#line 408 "/src/emitter-header.do"
    if (((((static_cast<int32_t>((plan->nativeAdapterSignatures)->size()) == 0) && (static_cast<int32_t>((plan->moduleValueDeclarations)->size()) == 0)) && (static_cast<int32_t>((plan->classDefinitions)->size()) == 0)) && (static_cast<int32_t>((plan->typeAliases)->size()) == 0)) && (static_cast<int32_t>((plan->functionSignatures)->size()) == 0)) {
#line 412 "/src/emitter-header.do"
        return;
    }
#line 413 "/src/emitter-header.do"
    result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 415 "/src/emitter-header.do"
    const auto& _iterable_88 = plan->nativeAdapterSignatures;
    for (const auto& signature : *_iterable_88) {
#line 415 "/src/emitter-header.do"
        result->append((std::string("    ") + signature));
    }
#line 416 "/src/emitter-header.do"
    const auto& _iterable_90 = plan->moduleValueDeclarations;
    for (const auto& declaration : *_iterable_90) {
#line 416 "/src/emitter-header.do"
        result->append((std::string("    ") + declaration));
    }
#line 417 "/src/emitter-header.do"
    const auto& _iterable_92 = plan->classDefinitions;
    for (const auto& definition : *_iterable_92) {
#line 417 "/src/emitter-header.do"
        result->append((std::string("    ") + definition));
    }
#line 418 "/src/emitter-header.do"
    const auto& _iterable_94 = plan->typeAliases;
    for (const auto& alias : *_iterable_94) {
#line 418 "/src/emitter-header.do"
        result->append((std::string("    ") + alias));
    }
#line 419 "/src/emitter-header.do"
    const auto& _iterable_96 = plan->functionSignatures;
    for (const auto& signature : *_iterable_96) {
#line 419 "/src/emitter-header.do"
        result->append((std::string("    ") + signature));
    }
#line 420 "/src/emitter-header.do"
    result->append(std::string("}\n\n"));
}
#line 423 "/src/emitter-header.do"
bool headerPlanEmitsNamespaceContent(const std::shared_ptr<HeaderPlan>& plan) {
#line 424 "/src/emitter-header.do"
    return (((((((((((static_cast<int32_t>((plan->ephemeralTypeAliases)->size()) > 0) || (static_cast<int32_t>((plan->enumDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->interfaceAliases)->size()) > 0)) || (static_cast<int32_t>((plan->earlyClassDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->earlyTypeAliases)->size()) > 0)) || (static_cast<int32_t>((plan->nativeAdapterSignatures)->size()) > 0)) || (static_cast<int32_t>((plan->moduleValueDeclarations)->size()) > 0)) || (static_cast<int32_t>((plan->classDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->typeAliases)->size()) > 0)) || (static_cast<int32_t>((plan->functionSignatures)->size()) > 0)) || (static_cast<int32_t>((plan->genericFunctionDefinitions)->size()) > 0));
}


#line 450 "/src/emitter-header.do"
void compressRepeatedHeaderVariants(const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<HeaderCompressionState>& state) {
#line 451 "/src/emitter-header.do"
    std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>> uses = std::make_shared<std::vector<std::shared_ptr<HeaderTypeUse>>>(std::vector<std::shared_ptr<HeaderTypeUse>>{});
#line 452 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->functionSignatures, uses);
#line 453 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->nativeAdapterSignatures, uses);
#line 454 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->genericFunctionDefinitions, uses);
#line 455 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->earlyModuleValueDeclarations, uses);
#line 456 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->moduleValueDeclarations, uses);
#line 457 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->earlyClassDefinitions, uses);
#line 458 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->classDefinitions, uses);
#line 459 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->interfaceAliases, uses);
#line 460 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->enumDefinitions, uses);
#line 461 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->earlyTypeAliases, uses);
#line 462 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->typeAliases, uses);
#line 464 "/src/emitter-header.do"
    const auto& _iterable_98 = uses;
    for (const auto& use : *_iterable_98) {
#line 465 "/src/emitter-header.do"
        if (use->count < 2) {
#line 465 "/src/emitter-header.do"
            continue;
        }
#line 466 "/src/emitter-header.do"
        auto name = preferredHeaderTypeAlias(plan, use->spelling);
#line 467 "/src/emitter-header.do"
        if (name == std::string("")) {
#line 468 "/src/emitter-header.do"
            (name = nextHeaderTypeAliasName(plan, state));
#line 469 "/src/emitter-header.do"
            plan->ephemeralTypeAliases->push_back(((((std::string("using ") + name) + std::string(" = ")) + use->spelling) + std::string(";\n")));
        }
#line 471 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->functionSignatures, use->spelling, name);
#line 472 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->nativeAdapterSignatures, use->spelling, name);
#line 473 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->genericFunctionDefinitions, use->spelling, name);
#line 474 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->earlyModuleValueDeclarations, use->spelling, name);
#line 475 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->moduleValueDeclarations, use->spelling, name);
#line 476 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->earlyClassDefinitions, use->spelling, name);
#line 477 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->classDefinitions, use->spelling, name);
#line 478 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->interfaceAliases, use->spelling, name);
#line 479 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->enumDefinitions, use->spelling, name);
#line 482 "/src/emitter-header.do"
        if (preferredHeaderTypeAlias(plan, use->spelling) == std::string("")) {
#line 483 "/src/emitter-header.do"
            replaceHeaderTypeUses(plan->earlyTypeAliases, use->spelling, name);
#line 484 "/src/emitter-header.do"
            replaceHeaderTypeUses(plan->typeAliases, use->spelling, name);
        }
    }
}
#line 489 "/src/emitter-header.do"
std::string nextHeaderTypeAliasName(const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<HeaderCompressionState>& state) {
#line 490 "/src/emitter-header.do"
    while (true) {
#line 491 "/src/emitter-header.do"
        const auto candidate = (std::string("doof_header_type_") + doof::to_string(state->nextAnonymousTypeIndex));
#line 492 "/src/emitter-header.do"
        (state->nextAnonymousTypeIndex += 1);
#line 493 "/src/emitter-header.do"
        auto occupied = false;
#line 494 "/src/emitter-header.do"
        const auto& _iterable_100 = plan->reservedNamespaceNames;
        for (const auto& existing : *_iterable_100) {
#line 494 "/src/emitter-header.do"
            if (existing == candidate) {
#line 494 "/src/emitter-header.do"
                (occupied = true);
#line 494 "/src/emitter-header.do"
                break;
            }
        }
#line 495 "/src/emitter-header.do"
        if (!occupied) {
#line 496 "/src/emitter-header.do"
            plan->reservedNamespaceNames->push_back(candidate);
#line 497 "/src/emitter-header.do"
            return candidate;
        }
    }
#line 500 "/src/emitter-header.do"
    return std::string("");
}
#line 503 "/src/emitter-header.do"
void reserveHeaderNamespaceName(const std::shared_ptr<HeaderPlan>& plan, const std::string& name) {
#line 504 "/src/emitter-header.do"
    const auto emitted = ::app_src_emitter_expr_::cppIdentifier(name);
#line 505 "/src/emitter-header.do"
    const auto& _iterable_102 = plan->reservedNamespaceNames;
    for (const auto& existing : *_iterable_102) {
#line 505 "/src/emitter-header.do"
        if (existing == emitted) {
#line 505 "/src/emitter-header.do"
            return;
        }
    }
#line 506 "/src/emitter-header.do"
    plan->reservedNamespaceNames->push_back(emitted);
}
#line 509 "/src/emitter-header.do"
std::string preferredHeaderTypeAlias(const std::shared_ptr<HeaderPlan>& plan, const std::string& spelling) {
#line 510 "/src/emitter-header.do"
    for (int32_t index = 0; index < static_cast<int32_t>((plan->preferredTypeAliasSpellings)->size()); ++index) {
#line 511 "/src/emitter-header.do"
        if (doof::array_at(plan->preferredTypeAliasSpellings, index, "src/emitter-header", 511) == spelling) {
#line 511 "/src/emitter-header.do"
            return doof::array_at(plan->preferredTypeAliasNames, index, "src/emitter-header", 511);
        }
    }
#line 513 "/src/emitter-header.do"
    return std::string("");
}
#line 516 "/src/emitter-header.do"
void collectHeaderTypeUses(const std::shared_ptr<std::vector<std::string>>& values, const std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>>& uses) {
#line 517 "/src/emitter-header.do"
    const auto& _iterable_105 = values;
    for (const auto& value : *_iterable_105) {
#line 518 "/src/emitter-header.do"
        auto offset = 0;
#line 519 "/src/emitter-header.do"
        const auto prefix = std::string("std::variant<");
#line 520 "/src/emitter-header.do"
        while (offset < static_cast<int32_t>(value.size())) {
#line 521 "/src/emitter-header.do"
            const auto relative = doof::string_indexOf(doof::string_substring(value, offset, static_cast<int32_t>(value.size())), prefix);
#line 522 "/src/emitter-header.do"
            if (relative < 0) {
#line 522 "/src/emitter-header.do"
                break;
            }
#line 523 "/src/emitter-header.do"
            const auto start = (offset + relative);
#line 524 "/src/emitter-header.do"
            const auto end = matchingAngleEnd(value, ((start + static_cast<int32_t>(prefix.size())) - 1));
#line 525 "/src/emitter-header.do"
            if (end < 0) {
#line 525 "/src/emitter-header.do"
                break;
            }
#line 526 "/src/emitter-header.do"
            const auto spelling = doof::string_substring(value, start, (end + 1));
#line 527 "/src/emitter-header.do"
            if (referenceOnlyVariant(spelling)) {
#line 527 "/src/emitter-header.do"
                addHeaderTypeUse(uses, spelling);
            }
#line 528 "/src/emitter-header.do"
            (offset = (end + 1));
        }
    }
}
#line 533 "/src/emitter-header.do"
int32_t matchingAngleEnd(const std::string& value, int32_t opening) {
#line 534 "/src/emitter-header.do"
    auto depth = 0;
#line 535 "/src/emitter-header.do"
    for (int32_t index = opening; index < static_cast<int32_t>(value.size()); ++index) {
#line 536 "/src/emitter-header.do"
        if (doof::string_at(value, index, "src/emitter-header", 536) == U'\u003C') {
#line 536 "/src/emitter-header.do"
            (depth += 1);
        } else if (doof::string_at(value, index, "src/emitter-header", 537) == U'\u003E') {
#line 538 "/src/emitter-header.do"
            (depth -= 1);
#line 539 "/src/emitter-header.do"
            if (depth == 0) {
#line 539 "/src/emitter-header.do"
                return index;
            }
        }
    }
#line 542 "/src/emitter-header.do"
    return -1;
}
#line 545 "/src/emitter-header.do"
bool referenceOnlyVariant(const std::string& spelling) {
#line 546 "/src/emitter-header.do"
    const auto inner = doof::string_substring(spelling, 13, (static_cast<int32_t>(spelling.size()) - 1));
#line 547 "/src/emitter-header.do"
    auto memberStart = 0;
#line 548 "/src/emitter-header.do"
    auto depth = 0;
#line 549 "/src/emitter-header.do"
    for (int32_t index = 0; index <= static_cast<int32_t>(inner.size()); ++index) {
#line 550 "/src/emitter-header.do"
        const auto atEnd = (index == static_cast<int32_t>(inner.size()));
#line 551 "/src/emitter-header.do"
        if (!atEnd) {
#line 552 "/src/emitter-header.do"
            if (doof::string_at(inner, index, "src/emitter-header", 552) == U'\u003C') {
#line 552 "/src/emitter-header.do"
                (depth += 1);
            } else if (doof::string_at(inner, index, "src/emitter-header", 553) == U'\u003E') {
#line 553 "/src/emitter-header.do"
                (depth -= 1);
            }
        }
#line 555 "/src/emitter-header.do"
        if (atEnd || ((doof::string_at(inner, index, "src/emitter-header", 555) == U'\u002C') && (depth == 0))) {
#line 556 "/src/emitter-header.do"
            const auto member = doof::string_trim(doof::string_substring(inner, memberStart, index));
#line 557 "/src/emitter-header.do"
            if ((member != std::string("std::monostate")) && !(doof::string_startsWith(member, std::string("std::shared_ptr<")) && doof::string_endsWith(member, std::string(">")))) {
#line 557 "/src/emitter-header.do"
                return false;
            }
#line 558 "/src/emitter-header.do"
            (memberStart = (index + 1));
        }
    }
#line 561 "/src/emitter-header.do"
    return true;
}
#line 564 "/src/emitter-header.do"
void addHeaderTypeUse(const std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>>& uses, const std::string& spelling) {
#line 565 "/src/emitter-header.do"
    const auto& _iterable_109 = uses;
    for (const auto& use : *_iterable_109) {
#line 566 "/src/emitter-header.do"
        if (use->spelling == spelling) {
#line 566 "/src/emitter-header.do"
            (use->count += 1);
#line 566 "/src/emitter-header.do"
            return;
        }
    }
#line 568 "/src/emitter-header.do"
    uses->push_back(std::make_shared<HeaderTypeUse>(spelling, 1));
}
#line 571 "/src/emitter-header.do"
void replaceHeaderTypeUses(const std::shared_ptr<std::vector<std::string>>& values, const std::string& spelling, const std::string& name) {
#line 572 "/src/emitter-header.do"
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
#line 572 "/src/emitter-header.do"
        (doof::array_at(values, index, "src/emitter-header", 572) = doof::string_replaceAll(doof::array_at(values, index, "src/emitter-header", 572), spelling, name));
    }
}
#line 575 "/src/emitter-header.do"
void collectModuleValueDeclaration(const std::shared_ptr<HeaderPlan>& plan, const std::string& declaration, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 576 "/src/emitter-header.do"
    if (moduleValueDeclarationNeedsIncludes(type_)) {
#line 576 "/src/emitter-header.do"
        plan->moduleValueDeclarations->push_back(declaration);
    } else {
#line 577 "/src/emitter-header.do"
        plan->earlyModuleValueDeclarations->push_back(declaration);
    }
}
#line 584 "/src/emitter-header.do"
bool moduleValueDeclarationNeedsIncludes(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 585 "/src/emitter-header.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 587 "/src/emitter-header.do"
            if ((class_->symbol->kind == std::string("struct")) || class_->symbol->native_) {
#line 587 "/src/emitter-header.do"
                return true;
            }
#line 588 "/src/emitter-header.do"
            const auto& _iterable_112 = class_->typeArgs;
            for (const auto& argument : *_iterable_112) {
#line 588 "/src/emitter-header.do"
                if (moduleValueDeclarationNeedsIncludes(argument)) {
#line 588 "/src/emitter-header.do"
                    return true;
                }
            }
#line 589 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 591 "/src/emitter-header.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 592 "/src/emitter-header.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 593 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 595 "/src/emitter-header.do"
            return (moduleValueDeclarationNeedsIncludes(map->keyType) || moduleValueDeclarationNeedsIncludes(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 597 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 598 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 600 "/src/emitter-header.do"
            return (moduleValueDeclarationNeedsIncludes(result->valueType) || moduleValueDeclarationNeedsIncludes(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 603 "/src/emitter-header.do"
            const auto& _iterable_114 = tuple->elements;
            for (const auto& element : *_iterable_114) {
#line 603 "/src/emitter-header.do"
                if (moduleValueDeclarationNeedsIncludes(element)) {
#line 603 "/src/emitter-header.do"
                    return true;
                }
            }
#line 604 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 607 "/src/emitter-header.do"
            const auto& _iterable_116 = union_->types;
            for (const auto& member : *_iterable_116) {
#line 607 "/src/emitter-header.do"
                if (moduleValueDeclarationNeedsIncludes(member)) {
#line 607 "/src/emitter-header.do"
                    return true;
                }
            }
#line 608 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 610 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 612 "/src/emitter-header.do"
            const auto& _iterable_118 = function_->params;
            for (const auto& parameter : *_iterable_118) {
#line 612 "/src/emitter-header.do"
                if (moduleValueDeclarationNeedsIncludes(parameter->type_)) {
#line 612 "/src/emitter-header.do"
                    return true;
                }
            }
#line 613 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(function_->returnType);
    }
    else {
#line 615 "/src/emitter-header.do"
            return false;
    }
    }
    doof::unreachable();
#line 617 "/src/emitter-header.do"
    return false;
}
#line 620 "/src/emitter-header.do"
std::string emitModuleValueDeclaration(const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 621 "/src/emitter-header.do"
    return ((((std::string("extern ") + ::app_src_emitter_types_::emitContextType(type_, context)) + std::string(" ")) + name) + std::string(";\n"));
}
#line 624 "/src/emitter-header.do"
void addUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 625 "/src/emitter-header.do"
    const auto& _iterable_120 = values;
    for (const auto& existing : *_iterable_120) {
#line 625 "/src/emitter-header.do"
        if (existing == value) {
#line 625 "/src/emitter-header.do"
            return;
        }
    }
#line 626 "/src/emitter-header.do"
    values->push_back(value);
}
#line 632 "/src/emitter-header.do"
void addNativeClassForwardDeclaration(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::shared_ptr<HeaderPlan>& plan) {
#line 633 "/src/emitter-header.do"
    const auto cppName = ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName);
#line 634 "/src/emitter-header.do"
    const auto namespace_ = nativeNamespace(cppName);
#line 635 "/src/emitter-header.do"
    const auto name = ((namespace_ == std::string("")) ? cppName : doof::string_substring(cppName, (static_cast<int32_t>(namespace_.size()) + 2), static_cast<int32_t>(cppName.size())));
#line 636 "/src/emitter-header.do"
    const auto declaration = ((namespace_ == std::string("")) ? ((std::string("class ") + name) + std::string(";\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { class ")) + name) + std::string("; }\n")));
#line 637 "/src/emitter-header.do"
    addUnique(plan->typeOnlyForwardDeclarations, declaration);
}
#line 640 "/src/emitter-header.do"
std::string nativeNamespace(const std::string& cppName) {
#line 641 "/src/emitter-header.do"
    auto separator = -1;
#line 642 "/src/emitter-header.do"
    for (int32_t i = 0; i < static_cast<int32_t>(cppName.size()); ++i) {
#line 643 "/src/emitter-header.do"
        if (((i + 1) < static_cast<int32_t>(cppName.size())) && (doof::string_substring(cppName, i, (i + 2)) == std::string("::"))) {
#line 644 "/src/emitter-header.do"
            (separator = i);
        }
    }
#line 647 "/src/emitter-header.do"
    if (separator < 0) {
#line 647 "/src/emitter-header.do"
        return std::string("");
    }
#line 648 "/src/emitter-header.do"
    return doof::string_substring(cppName, 0, separator);
}
#line 651 "/src/emitter-header.do"
std::string emitEnumDeclaration(const std::shared_ptr<::app_src_ast_::EnumDeclaration>& declaration, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 652 "/src/emitter-header.do"
    auto result = (((::app_src_emitter_decl_::emitDescriptionComment(declaration->description, std::string("")) + std::string("enum class ")) + declaration->name) + std::string(" {\n"));
#line 653 "/src/emitter-header.do"
    for (int32_t i = 0; i < static_cast<int32_t>((declaration->variants)->size()); ++i) {
#line 654 "/src/emitter-header.do"
        const auto variant = doof::array_at(declaration->variants, i, "src/emitter-header", 654);
#line 655 "/src/emitter-header.do"
        (result = (((result + ::app_src_emitter_decl_::emitDescriptionComment(variant->description, std::string("    "))) + std::string("    ")) + variant->name));
#line 656 "/src/emitter-header.do"
        if (!doof::is_null(variant->value)) {
#line 656 "/src/emitter-header.do"
            (result = ((result + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(variant->value), context, std::monostate{})));
        }
#line 657 "/src/emitter-header.do"
        if ((i + 1) < static_cast<int32_t>((declaration->variants)->size())) {
#line 657 "/src/emitter-header.do"
            (result = (result + std::string(",")));
        }
#line 658 "/src/emitter-header.do"
        (result = (result + std::string("\n")));
    }
#line 660 "/src/emitter-header.do"
    (result = (result + std::string("};\n")));
#line 661 "/src/emitter-header.do"
    (result = (((((result + std::string("inline const char* ")) + declaration->name) + std::string("_name(")) + declaration->name) + std::string(" value) {\n")));
#line 662 "/src/emitter-header.do"
    (result = (result + std::string("  switch (value) {\n")));
#line 663 "/src/emitter-header.do"
    const auto& _iterable_124 = declaration->variants;
    for (const auto& variant : *_iterable_124) {
#line 664 "/src/emitter-header.do"
        (result = (((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return \"")) + variant->name) + std::string("\";\n")));
    }
#line 666 "/src/emitter-header.do"
    (result = (result + std::string("  }\n  return \"\";\n}\n")));
#line 667 "/src/emitter-header.do"
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromName(std::string_view value) {\n")));
#line 668 "/src/emitter-header.do"
    const auto& _iterable_126 = declaration->variants;
    for (const auto& variant : *_iterable_126) {
#line 669 "/src/emitter-header.do"
        (result = (((((((result + std::string("  if (value == \"")) + variant->name) + std::string("\") return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
#line 671 "/src/emitter-header.do"
    (result = (result + std::string("  return std::nullopt;\n}\n")));
#line 672 "/src/emitter-header.do"
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromValue(int32_t value) {\n")));
#line 673 "/src/emitter-header.do"
    (result = (((result + std::string("  switch (static_cast<")) + declaration->name) + std::string(">(value)) {\n")));
#line 674 "/src/emitter-header.do"
    const auto& _iterable_128 = declaration->variants;
    for (const auto& variant : *_iterable_128) {
#line 675 "/src/emitter-header.do"
        (result = (((((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
#line 677 "/src/emitter-header.do"
    (result = (result + std::string("    default: return std::nullopt;\n  }\n}\n")));
#line 678 "/src/emitter-header.do"
    return (((((result + std::string("inline std::ostream& operator<<(std::ostream& output, ")) + declaration->name) + std::string(" value) { return output << ")) + declaration->name) + std::string("_name(value); }\n"));
}
#line 681 "/src/emitter-header.do"
std::string emitTypeAlias(const std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>& alias, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 682 "/src/emitter-header.do"
    if (doof::is_null(alias->resolvedType)) {
#line 682 "/src/emitter-header.do"
        doof::panic(((std::string("Type alias ") + alias->name) + std::string(" was not checked before emission")));
    }
#line 683 "/src/emitter-header.do"
    return (((((::app_src_emitter_decl_::emitDescriptionComment(alias->description, std::string("")) + std::string("using ")) + alias->name) + std::string(" = ")) + ::app_src_emitter_types_::emitType(doof::unwrap_optional(alias->resolvedType), context->modulePath)) + std::string(";\n"));
}
#line 686 "/src/emitter-header.do"
bool functionReturnsInt(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
#line 687 "/src/emitter-header.do"
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 689 "/src/emitter-header.do"
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 690 "/src/emitter-header.do"
                    return (primitive->name == std::string("int"));
            }
            else {
#line 691 "/src/emitter-header.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 694 "/src/emitter-header.do"
            return false;
    }
    }
    doof::unreachable();
#line 696 "/src/emitter-header.do"
    return false;
}
#line 1 "<doof-generated>"
}
