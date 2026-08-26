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


#line 56 "/src/emitter-header.do"
std::shared_ptr<HeaderPlan> planHeader(const std::shared_ptr<::app_src_ast_::Program>& program, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 57 "/src/emitter-header.do"
    return planHeaders(std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{program}), context);
}
#line 60 "/src/emitter-header.do"
std::shared_ptr<HeaderPlan> planHeaders(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>>& programs, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 61 "/src/emitter-header.do"
    const auto plan = std::make_shared<HeaderPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, false, false);
#line 62 "/src/emitter-header.do"
    const auto& _iterable_2 = programs;
    for (const auto& program : *_iterable_2) {
#line 63 "/src/emitter-header.do"
        const auto& _iterable_4 = program->statements;
        for (const auto& statement : *_iterable_4) {
#line 63 "/src/emitter-header.do"
            collect(statement, plan, context);
        }
    }
#line 68 "/src/emitter-header.do"
    const auto& _iterable_6 = plan->nativeNamespaces;
    for (const auto& namespace_ : *_iterable_6) {
#line 69 "/src/emitter-header.do"
        collectNativeModuleTypeAliases(context->modulePath, namespace_, plan, context);
    }
#line 71 "/src/emitter-header.do"
    return plan;
}
#line 74 "/src/emitter-header.do"
void collectNativeModuleTypeAliases(const std::string& modulePath, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 75 "/src/emitter-header.do"
    const auto& _iterable_8 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_8) {
#line 76 "/src/emitter-header.do"
        if (surface->path != modulePath) {
#line 76 "/src/emitter-header.do"
            continue;
        }
#line 77 "/src/emitter-header.do"
        const auto& _iterable_10 = surface->exports;
        for (const auto& symbol : *_iterable_10) {
#line 78 "/src/emitter-header.do"
            if (isNativeAliasType(symbol) && !surfaceTypeIsGeneric(surface, symbol->name)) {
#line 79 "/src/emitter-header.do"
                addNativeSymbolAlias(symbol, namespace_, plan);
            }
        }
#line 82 "/src/emitter-header.do"
        const auto& _iterable_12 = surface->imports;
        for (const auto& imported : *_iterable_12) {
#line 83 "/src/emitter-header.do"
            if (((!doof::is_null(imported->symbol)) && isNativeAliasType(doof::unwrap_optional(imported->symbol))) && !surfaceSymbolIsGeneric(context, doof::unwrap_optional(imported->symbol))) {
#line 84 "/src/emitter-header.do"
                addNativeSymbolAlias(doof::unwrap_optional(imported->symbol), namespace_, plan);
            }
        }
#line 87 "/src/emitter-header.do"
        return;
    }
}
#line 91 "/src/emitter-header.do"
bool surfaceTypeIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitModuleSurface>& surface, const std::string& name) {
#line 92 "/src/emitter-header.do"
    const auto& _iterable_14 = surface->genericTypes;
    for (const auto& genericName : *_iterable_14) {
#line 92 "/src/emitter-header.do"
        if (genericName == name) {
#line 92 "/src/emitter-header.do"
            return true;
        }
    }
#line 93 "/src/emitter-header.do"
    return false;
}
#line 96 "/src/emitter-header.do"
bool isNativeAliasType(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 97 "/src/emitter-header.do"
    return (((((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("enum"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("type-alias")));
}
#line 100 "/src/emitter-header.do"
void collect(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 101 "/src/emitter-header.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 103 "/src/emitter-header.do"
            if (class_->native_) {
#line 104 "/src/emitter-header.do"
                const auto rawInclude = ((class_->nativeHeader == std::string("")) ? (class_->name + std::string(".hpp")) : class_->nativeHeader);
#line 105 "/src/emitter-header.do"
                const auto include = ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, rawInclude);
#line 106 "/src/emitter-header.do"
                addUnique(plan->nativeIncludes, include);
#line 107 "/src/emitter-header.do"
                const auto namespace_ = nativeNamespace(class_->nativeCppName);
#line 108 "/src/emitter-header.do"
                addUnique(plan->nativeNamespaces, namespace_);
#line 109 "/src/emitter-header.do"
                collectNativeClassAliases(class_, namespace_, plan, context);
            } else if ((static_cast<int32_t>((class_->typeParams)->size()) == 0) || isNativeTemplateClass(context, class_->name)) {
#line 111 "/src/emitter-header.do"
                if (static_cast<int32_t>((class_->typeParams)->size()) == 0) {
#line 111 "/src/emitter-header.do"
                    plan->classForwardDeclarations->push_back(((std::string("struct ") + class_->name) + std::string(";\n")));
                } else {
#line 112 "/src/emitter-header.do"
                    plan->classForwardDeclarations->push_back(emitTemplateClassForwardDeclaration(class_));
                }
#line 113 "/src/emitter-header.do"
                const auto definition = ::app_src_emitter_decl_::emitClassDeclaration(class_, context, std::string(""), std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{}));
#line 114 "/src/emitter-header.do"
                if (classCanEmitBeforeModuleIncludes(class_)) {
#line 114 "/src/emitter-header.do"
                    plan->earlyClassDefinitions->push_back(definition);
                } else {
#line 115 "/src/emitter-header.do"
                    plan->classDefinitions->push_back(definition);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 119 "/src/emitter-header.do"
            if (static_cast<int32_t>((interface_->typeParams)->size()) == 0) {
#line 120 "/src/emitter-header.do"
                if (!doof::is_null(interface_->resolvedSymbol)) {
#line 121 "/src/emitter-header.do"
                    const auto& _iterable_16 = interface_->resolvedSymbol->implementations;
                    for (const auto& implementation : *_iterable_16) {
#line 122 "/src/emitter-header.do"
                        if (implementation->native_) {
#line 122 "/src/emitter-header.do"
                            addNativeClassForwardDeclaration(implementation, plan);
                        }
                    }
                }
#line 125 "/src/emitter-header.do"
                plan->interfaceAliases->push_back(::app_src_emitter_decl_::emitInterfaceAlias(interface_, context));
#line 126 "/src/emitter-header.do"
                const auto declaration = ::app_src_emitter_json_::emitInterfaceJsonDeclaration(interface_);
#line 127 "/src/emitter-header.do"
                if (declaration != std::string("")) {
#line 127 "/src/emitter-header.do"
                    plan->functionSignatures->push_back(declaration);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 130 "/src/emitter-header.do"
            plan->enumDefinitions->push_back(emitEnumDeclaration(enum_, context));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 134 "/src/emitter-header.do"
            if (static_cast<int32_t>((alias->typeParams)->size()) == 0) {
#line 135 "/src/emitter-header.do"
                const auto emitted = emitTypeAlias(alias, context);
#line 136 "/src/emitter-header.do"
                if ((!doof::is_null(alias->resolvedType)) && !typeNeedsCompleteNominalDefinition(doof::unwrap_optional(alias->resolvedType))) {
#line 137 "/src/emitter-header.do"
                    plan->earlyTypeAliases->push_back(emitted);
#line 138 "/src/emitter-header.do"
                    const auto spelling = ::app_src_emitter_types_::emitType(doof::unwrap_optional(alias->resolvedType), context->modulePath);
#line 139 "/src/emitter-header.do"
                    if (referenceOnlyVariant(spelling)) {
#line 140 "/src/emitter-header.do"
                        plan->preferredTypeAliasNames->push_back(alias->name);
#line 141 "/src/emitter-header.do"
                        plan->preferredTypeAliasSpellings->push_back(spelling);
                    }
                } else {
#line 144 "/src/emitter-header.do"
                    plan->typeAliases->push_back(emitted);
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 148 "/src/emitter-header.do"
            collectModuleValueDeclaration(plan, (::app_src_emitter_decl_::emitDescriptionComment(const_->description, std::string("")) + emitModuleValueDeclaration(const_->name, doof::unwrap_optional(const_->resolvedType), context)), doof::unwrap_optional(const_->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 155 "/src/emitter-header.do"
            collectModuleValueDeclaration(plan, (::app_src_emitter_decl_::emitDescriptionComment(readonly_->description, std::string("")) + emitModuleValueDeclaration(readonly_->name, doof::unwrap_optional(readonly_->resolvedType), context)), doof::unwrap_optional(readonly_->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 162 "/src/emitter-header.do"
            collectModuleValueDeclaration(plan, emitModuleValueDeclaration(binding->name, doof::unwrap_optional(binding->resolvedType), context), doof::unwrap_optional(binding->resolvedType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 165 "/src/emitter-header.do"
            if (fn->native_) {
#line 166 "/src/emitter-header.do"
                if (fn->nativeHeader != std::string("")) {
#line 166 "/src/emitter-header.do"
                    addUnique(plan->nativeIncludes, ::app_src_emitter_names_::moduleNativeHeaderPath(context->modulePath, fn->nativeHeader));
                }
#line 167 "/src/emitter-header.do"
                const auto namespace_ = nativeNamespace(fn->nativeCppName);
#line 168 "/src/emitter-header.do"
                addUnique(plan->nativeNamespaces, namespace_);
#line 169 "/src/emitter-header.do"
                if (!doof::is_null(fn->resolvedType)) {
#line 169 "/src/emitter-header.do"
                    collectNativeTypeAliases(doof::unwrap_optional(fn->resolvedType), namespace_, plan, context);
                }
#line 170 "/src/emitter-header.do"
                return;
            }
#line 172 "/src/emitter-header.do"
            if (fn->name == std::string("main")) {
#line 173 "/src/emitter-header.do"
                (plan->hasMain = true);
#line 174 "/src/emitter-header.do"
                (plan->mainReturnsInt = functionReturnsInt(fn));
#line 175 "/src/emitter-header.do"
                (plan->mainAcceptsArgs = (static_cast<int32_t>((fn->params)->size()) == 1));
#line 176 "/src/emitter-header.do"
                plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string("doof_main"), context->modulePath, context));
            } else if (static_cast<int32_t>((fn->typeParams)->size()) > 0) {
            } else {
#line 181 "/src/emitter-header.do"
                plan->functionSignatures->push_back(::app_src_emitter_decl_::emitFunctionDeclaration(fn, std::string(""), context->modulePath, context));
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject)) {
            const auto& export_ = std::get<std::shared_ptr<::app_src_ast_::ExportDeclaration>>(_case_subject);
#line 184 "/src/emitter-header.do"
            collect(export_->declaration, plan, context);
    }
    else {
    }
    }
}
#line 192 "/src/emitter-header.do"
bool classCanEmitBeforeModuleIncludes(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_) {
#line 193 "/src/emitter-header.do"
    if (static_cast<int32_t>((class_->typeParams)->size()) > 0) {
#line 193 "/src/emitter-header.do"
        return false;
    }
#line 194 "/src/emitter-header.do"
    const auto& _iterable_18 = class_->fields;
    for (const auto& field : *_iterable_18) {
#line 195 "/src/emitter-header.do"
        if ((!field->static_ && (!doof::is_null(field->resolvedType))) && typeNeedsCompleteNominalDefinition(doof::unwrap_optional(field->resolvedType))) {
#line 195 "/src/emitter-header.do"
            return false;
        }
    }
#line 197 "/src/emitter-header.do"
    return true;
}
#line 200 "/src/emitter-header.do"
bool typeNeedsCompleteNominalDefinition(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 201 "/src/emitter-header.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 203 "/src/emitter-header.do"
            if ((class_->symbol->kind == std::string("struct")) || class_->symbol->native_) {
#line 203 "/src/emitter-header.do"
                return true;
            }
#line 204 "/src/emitter-header.do"
            const auto& _iterable_20 = class_->typeArgs;
            for (const auto& argument : *_iterable_20) {
#line 204 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(argument)) {
#line 204 "/src/emitter-header.do"
                    return true;
                }
            }
#line 205 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 207 "/src/emitter-header.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 209 "/src/emitter-header.do"
            const auto& _iterable_22 = interface_->typeArgs;
            for (const auto& argument : *_iterable_22) {
#line 209 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(argument)) {
#line 209 "/src/emitter-header.do"
                    return true;
                }
            }
#line 210 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 212 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 214 "/src/emitter-header.do"
            return (typeNeedsCompleteNominalDefinition(map->keyType) || typeNeedsCompleteNominalDefinition(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 216 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 217 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 219 "/src/emitter-header.do"
            return (typeNeedsCompleteNominalDefinition(result->valueType) || typeNeedsCompleteNominalDefinition(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 222 "/src/emitter-header.do"
            const auto& _iterable_24 = tuple->elements;
            for (const auto& element : *_iterable_24) {
#line 222 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(element)) {
#line 222 "/src/emitter-header.do"
                    return true;
                }
            }
#line 223 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 226 "/src/emitter-header.do"
            const auto& _iterable_26 = union_->types;
            for (const auto& member : *_iterable_26) {
#line 226 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(member)) {
#line 226 "/src/emitter-header.do"
                    return true;
                }
            }
#line 227 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 230 "/src/emitter-header.do"
            const auto& _iterable_28 = function_->params;
            for (const auto& parameter : *_iterable_28) {
#line 230 "/src/emitter-header.do"
                if (typeNeedsCompleteNominalDefinition(parameter->type_)) {
#line 230 "/src/emitter-header.do"
                    return true;
                }
            }
#line 231 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(function_->returnType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 233 "/src/emitter-header.do"
            return typeNeedsCompleteNominalDefinition(weak_->inner);
    }
    else {
#line 234 "/src/emitter-header.do"
            return false;
    }
    }
    doof::unreachable();
}
#line 238 "/src/emitter-header.do"
bool isNativeTemplateClass(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& name) {
#line 239 "/src/emitter-header.do"
    const auto key = ((context->modulePath + std::string("::")) + name);
#line 240 "/src/emitter-header.do"
    const auto& _iterable_30 = context->nativeTemplateClassKeys;
    for (const auto& existing : *_iterable_30) {
#line 240 "/src/emitter-header.do"
        if (existing == key) {
#line 240 "/src/emitter-header.do"
            return true;
        }
    }
#line 241 "/src/emitter-header.do"
    return false;
}
#line 244 "/src/emitter-header.do"
std::string emitTemplateClassForwardDeclaration(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_) {
#line 245 "/src/emitter-header.do"
    auto result = std::string("template <");
#line 246 "/src/emitter-header.do"
    for (int32_t index = 0; index < static_cast<int32_t>((class_->typeParams)->size()); ++index) {
#line 247 "/src/emitter-header.do"
        if (index > 0) {
#line 247 "/src/emitter-header.do"
            (result = (result + std::string(", ")));
        }
#line 248 "/src/emitter-header.do"
        (result = ((result + std::string("typename ")) + doof::array_at(class_->typeParams, index, "src/emitter-header", 248)));
    }
#line 250 "/src/emitter-header.do"
    return (((result + std::string(">\n    struct ")) + class_->name) + std::string(";\n"));
}
#line 253 "/src/emitter-header.do"
void collectNativeClassAliases(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& class_, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 254 "/src/emitter-header.do"
    const auto& _iterable_33 = class_->fields;
    for (const auto& field : *_iterable_33) {
#line 254 "/src/emitter-header.do"
        if (!doof::is_null(field->resolvedType)) {
#line 254 "/src/emitter-header.do"
            collectNativeTypeAliases(doof::unwrap_optional(field->resolvedType), namespace_, plan, context);
        }
    }
#line 255 "/src/emitter-header.do"
    const auto& _iterable_35 = class_->methods;
    for (const auto& method : *_iterable_35) {
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
            const auto& _iterable_37 = class_->typeArgs;
            for (const auto& argument : *_iterable_37) {
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
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 274 "/src/emitter-header.do"
            collectNativeTypeAliases(result->valueType, namespace_, plan, context);
#line 275 "/src/emitter-header.do"
            collectNativeTypeAliases(result->errorType, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 277 "/src/emitter-header.do"
            const auto& _iterable_39 = tuple->elements;
            for (const auto& element : *_iterable_39) {
#line 277 "/src/emitter-header.do"
                collectNativeTypeAliases(element, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 278 "/src/emitter-header.do"
            const auto& _iterable_41 = union_->types;
            for (const auto& member : *_iterable_41) {
#line 278 "/src/emitter-header.do"
                collectNativeTypeAliases(member, namespace_, plan, context);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 279 "/src/emitter-header.do"
            collectNativeTypeAliases(weak_->inner, namespace_, plan, context);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 281 "/src/emitter-header.do"
            const auto& _iterable_43 = function_->params;
            for (const auto& parameter : *_iterable_43) {
#line 281 "/src/emitter-header.do"
                collectNativeTypeAliases(parameter->type_, namespace_, plan, context);
            }
#line 282 "/src/emitter-header.do"
            collectNativeTypeAliases(function_->returnType, namespace_, plan, context);
    }
    else {
    }
    }
}
#line 288 "/src/emitter-header.do"
bool surfaceSymbolIsGeneric(const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 289 "/src/emitter-header.do"
    const auto& _iterable_45 = context->moduleSurfaces;
    for (const auto& surface : *_iterable_45) {
#line 290 "/src/emitter-header.do"
        if (surface->path == symbol->module) {
#line 290 "/src/emitter-header.do"
            return surfaceTypeIsGeneric(surface, symbol->name);
        }
    }
#line 292 "/src/emitter-header.do"
    return false;
}
#line 295 "/src/emitter-header.do"
void addNativeSymbolAlias(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& namespace_, const std::shared_ptr<HeaderPlan>& plan) {
#line 296 "/src/emitter-header.do"
    if (symbol->native_ || (symbol->module == std::string(""))) {
#line 296 "/src/emitter-header.do"
        return;
    }
#line 297 "/src/emitter-header.do"
    if ((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) {
#line 298 "/src/emitter-header.do"
        addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { struct ")) + symbol->name) + std::string("; }\n")));
    } else if (symbol->kind == std::string("enum")) {
#line 300 "/src/emitter-header.do"
        addUnique(plan->typeOnlyForwardDeclarations, ((((std::string("namespace ") + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string(" { enum class ")) + symbol->name) + std::string("; }\n")));
    }
#line 302 "/src/emitter-header.do"
    const auto alias = ((((((std::string("using ") + symbol->name) + std::string(" = ::")) + ::app_src_emitter_names_::moduleNamespace(symbol->module)) + std::string("::")) + symbol->name) + std::string(";"));
#line 303 "/src/emitter-header.do"
    addUnique(plan->nativeAliases, ((namespace_ == std::string("")) ? (alias + std::string("\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { ")) + alias) + std::string(" }\n"))));
}
#line 306 "/src/emitter-header.do"
std::string renderHeader(const std::shared_ptr<HeaderPlan>& plan, const std::string& guardName) {
#line 307 "/src/emitter-header.do"
    return renderProjectedHeader(std::make_shared<std::vector<std::shared_ptr<HeaderSection>>>(std::vector<std::shared_ptr<HeaderSection>>{std::make_shared<HeaderSection>(guardName, plan)}));
}
#line 310 "/src/emitter-header.do"
std::string renderProjectedHeader(const std::shared_ptr<std::vector<std::shared_ptr<HeaderSection>>>& sections) {
#line 311 "/src/emitter-header.do"
    const auto compression = std::make_shared<HeaderCompressionState>(1);
#line 312 "/src/emitter-header.do"
    const auto& _iterable_47 = sections;
    for (const auto& section : *_iterable_47) {
#line 312 "/src/emitter-header.do"
        compressRepeatedHeaderVariants(section->plan, compression);
    }
#line 313 "/src/emitter-header.do"
    const auto result = ::doof::StringBuilder::constructor();
#line 314 "/src/emitter-header.do"
    result->append(std::string("#pragma once\n"));
#line 318 "/src/emitter-header.do"
    result->append(std::string("#include \"doof_runtime.hpp\"\n"));
#line 319 "/src/emitter-header.do"
    auto emittedForward = false;
#line 320 "/src/emitter-header.do"
    const auto& _iterable_49 = sections;
    for (const auto& section : *_iterable_49) {
#line 321 "/src/emitter-header.do"
        const auto& _iterable_51 = section->plan->typeOnlyForwardDeclarations;
        for (const auto& declaration : *_iterable_51) {
#line 321 "/src/emitter-header.do"
            result->append(declaration);
#line 321 "/src/emitter-header.do"
            (emittedForward = true);
        }
    }
#line 323 "/src/emitter-header.do"
    if (emittedForward) {
#line 323 "/src/emitter-header.do"
        result->append(std::string("\n"));
    }
#line 326 "/src/emitter-header.do"
    const auto& _iterable_53 = sections;
    for (const auto& section : *_iterable_53) {
#line 327 "/src/emitter-header.do"
        if (((static_cast<int32_t>((section->plan->classForwardDeclarations)->size()) == 0) && (static_cast<int32_t>((section->plan->earlyModuleValueDeclarations)->size()) == 0)) && headerPlanEmitsNamespaceContent(section->plan)) {
#line 329 "/src/emitter-header.do"
            continue;
        }
#line 330 "/src/emitter-header.do"
        result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 331 "/src/emitter-header.do"
        const auto& _iterable_55 = section->plan->classForwardDeclarations;
        for (const auto& declaration : *_iterable_55) {
#line 331 "/src/emitter-header.do"
            result->append((std::string("    ") + declaration));
        }
#line 334 "/src/emitter-header.do"
        const auto& _iterable_57 = section->plan->earlyModuleValueDeclarations;
        for (const auto& declaration : *_iterable_57) {
#line 334 "/src/emitter-header.do"
            result->append((std::string("    ") + declaration));
        }
#line 335 "/src/emitter-header.do"
        result->append(std::string("}\n\n"));
    }
#line 339 "/src/emitter-header.do"
    const auto& _iterable_59 = sections;
    for (const auto& section : *_iterable_59) {
#line 340 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->ephemeralTypeAliases)->size()) > 0) {
#line 341 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 342 "/src/emitter-header.do"
            const auto& _iterable_61 = section->plan->ephemeralTypeAliases;
            for (const auto& alias : *_iterable_61) {
#line 342 "/src/emitter-header.do"
                result->append((std::string("    ") + alias));
            }
#line 343 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 349 "/src/emitter-header.do"
    const auto& _iterable_63 = sections;
    for (const auto& section : *_iterable_63) {
#line 350 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->enumDefinitions)->size()) > 0) {
#line 351 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 352 "/src/emitter-header.do"
            const auto& _iterable_65 = section->plan->enumDefinitions;
            for (const auto& definition : *_iterable_65) {
#line 352 "/src/emitter-header.do"
                result->append((std::string("    ") + definition));
            }
#line 353 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 356 "/src/emitter-header.do"
    const auto& _iterable_67 = sections;
    for (const auto& section : *_iterable_67) {
#line 357 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->interfaceAliases)->size()) > 0) {
#line 358 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 359 "/src/emitter-header.do"
            const auto& _iterable_69 = section->plan->interfaceAliases;
            for (const auto& alias : *_iterable_69) {
#line 359 "/src/emitter-header.do"
                result->append((std::string("    ") + alias));
            }
#line 360 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 363 "/src/emitter-header.do"
    const auto& _iterable_71 = sections;
    for (const auto& section : *_iterable_71) {
#line 364 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->earlyTypeAliases)->size()) > 0) {
#line 365 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 366 "/src/emitter-header.do"
            const auto& _iterable_73 = section->plan->earlyTypeAliases;
            for (const auto& alias : *_iterable_73) {
#line 366 "/src/emitter-header.do"
                result->append((std::string("    ") + alias));
            }
#line 367 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 370 "/src/emitter-header.do"
    const auto& _iterable_75 = sections;
    for (const auto& section : *_iterable_75) {
#line 371 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->earlyClassDefinitions)->size()) > 0) {
#line 372 "/src/emitter-header.do"
            result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 373 "/src/emitter-header.do"
            const auto& _iterable_77 = section->plan->earlyClassDefinitions;
            for (const auto& definition : *_iterable_77) {
#line 373 "/src/emitter-header.do"
                result->append((std::string("    ") + definition));
            }
#line 374 "/src/emitter-header.do"
            result->append(std::string("}\n\n"));
        }
    }
#line 381 "/src/emitter-header.do"
    const auto& _iterable_79 = sections;
    for (const auto& section : *_iterable_79) {
#line 382 "/src/emitter-header.do"
        auto emittedNative = false;
#line 383 "/src/emitter-header.do"
        const auto& _iterable_81 = section->plan->nativeAliases;
        for (const auto& alias : *_iterable_81) {
#line 383 "/src/emitter-header.do"
            result->append(alias);
#line 383 "/src/emitter-header.do"
            (emittedNative = true);
        }
#line 384 "/src/emitter-header.do"
        const auto& _iterable_83 = section->plan->nativeIncludes;
        for (const auto& include : *_iterable_83) {
#line 385 "/src/emitter-header.do"
            if (doof::string_startsWith(include, std::string("<"))) {
#line 385 "/src/emitter-header.do"
                result->append(((std::string("#include ") + include) + std::string("\n")));
            } else {
#line 386 "/src/emitter-header.do"
                result->append(((std::string("#include \"") + include) + std::string("\"\n")));
            }
#line 387 "/src/emitter-header.do"
            (emittedNative = true);
        }
#line 389 "/src/emitter-header.do"
        if (emittedNative) {
#line 389 "/src/emitter-header.do"
            result->append(std::string("\n"));
        }
#line 390 "/src/emitter-header.do"
        renderFinalSection(result, section);
    }
#line 392 "/src/emitter-header.do"
    const auto& _iterable_85 = sections;
    for (const auto& section : *_iterable_85) {
#line 393 "/src/emitter-header.do"
        if (static_cast<int32_t>((section->plan->genericFunctionDefinitions)->size()) == 0) {
#line 393 "/src/emitter-header.do"
            continue;
        }
#line 394 "/src/emitter-header.do"
        result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 395 "/src/emitter-header.do"
        const auto& _iterable_87 = section->plan->genericFunctionDefinitions;
        for (const auto& definition : *_iterable_87) {
#line 395 "/src/emitter-header.do"
            result->append(definition);
        }
#line 396 "/src/emitter-header.do"
        result->append(std::string("}\n"));
    }
#line 398 "/src/emitter-header.do"
    auto rendered = result->drainToString();
#line 399 "/src/emitter-header.do"
    while (doof::string_endsWith(rendered, std::string("\n\n"))) {
#line 399 "/src/emitter-header.do"
        (rendered = doof::string_substring(rendered, 0, (static_cast<int32_t>(rendered.size()) - 1)));
    }
#line 400 "/src/emitter-header.do"
    return rendered;
}
#line 403 "/src/emitter-header.do"
void renderFinalSection(const std::shared_ptr<::doof::StringBuilder>& result, const std::shared_ptr<HeaderSection>& section) {
#line 404 "/src/emitter-header.do"
    const auto plan = section->plan;
#line 405 "/src/emitter-header.do"
    if (((((static_cast<int32_t>((plan->nativeAdapterSignatures)->size()) == 0) && (static_cast<int32_t>((plan->moduleValueDeclarations)->size()) == 0)) && (static_cast<int32_t>((plan->classDefinitions)->size()) == 0)) && (static_cast<int32_t>((plan->typeAliases)->size()) == 0)) && (static_cast<int32_t>((plan->functionSignatures)->size()) == 0)) {
#line 409 "/src/emitter-header.do"
        return;
    }
#line 410 "/src/emitter-header.do"
    result->append(((std::string("namespace ") + section->namespaceName) + std::string(" {\n")));
#line 412 "/src/emitter-header.do"
    const auto& _iterable_89 = plan->nativeAdapterSignatures;
    for (const auto& signature : *_iterable_89) {
#line 412 "/src/emitter-header.do"
        result->append((std::string("    ") + signature));
    }
#line 413 "/src/emitter-header.do"
    const auto& _iterable_91 = plan->moduleValueDeclarations;
    for (const auto& declaration : *_iterable_91) {
#line 413 "/src/emitter-header.do"
        result->append((std::string("    ") + declaration));
    }
#line 414 "/src/emitter-header.do"
    const auto& _iterable_93 = plan->classDefinitions;
    for (const auto& definition : *_iterable_93) {
#line 414 "/src/emitter-header.do"
        result->append((std::string("    ") + definition));
    }
#line 415 "/src/emitter-header.do"
    const auto& _iterable_95 = plan->typeAliases;
    for (const auto& alias : *_iterable_95) {
#line 415 "/src/emitter-header.do"
        result->append((std::string("    ") + alias));
    }
#line 416 "/src/emitter-header.do"
    const auto& _iterable_97 = plan->functionSignatures;
    for (const auto& signature : *_iterable_97) {
#line 416 "/src/emitter-header.do"
        result->append((std::string("    ") + signature));
    }
#line 417 "/src/emitter-header.do"
    result->append(std::string("}\n\n"));
}
#line 420 "/src/emitter-header.do"
bool headerPlanEmitsNamespaceContent(const std::shared_ptr<HeaderPlan>& plan) {
#line 421 "/src/emitter-header.do"
    return (((((((((((static_cast<int32_t>((plan->ephemeralTypeAliases)->size()) > 0) || (static_cast<int32_t>((plan->enumDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->interfaceAliases)->size()) > 0)) || (static_cast<int32_t>((plan->earlyClassDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->earlyTypeAliases)->size()) > 0)) || (static_cast<int32_t>((plan->nativeAdapterSignatures)->size()) > 0)) || (static_cast<int32_t>((plan->moduleValueDeclarations)->size()) > 0)) || (static_cast<int32_t>((plan->classDefinitions)->size()) > 0)) || (static_cast<int32_t>((plan->typeAliases)->size()) > 0)) || (static_cast<int32_t>((plan->functionSignatures)->size()) > 0)) || (static_cast<int32_t>((plan->genericFunctionDefinitions)->size()) > 0));
}


#line 447 "/src/emitter-header.do"
void compressRepeatedHeaderVariants(const std::shared_ptr<HeaderPlan>& plan, const std::shared_ptr<HeaderCompressionState>& state) {
#line 448 "/src/emitter-header.do"
    std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>> uses = std::make_shared<std::vector<std::shared_ptr<HeaderTypeUse>>>(std::vector<std::shared_ptr<HeaderTypeUse>>{});
#line 449 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->functionSignatures, uses);
#line 450 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->nativeAdapterSignatures, uses);
#line 451 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->genericFunctionDefinitions, uses);
#line 452 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->earlyModuleValueDeclarations, uses);
#line 453 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->moduleValueDeclarations, uses);
#line 454 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->earlyClassDefinitions, uses);
#line 455 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->classDefinitions, uses);
#line 456 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->interfaceAliases, uses);
#line 457 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->enumDefinitions, uses);
#line 458 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->earlyTypeAliases, uses);
#line 459 "/src/emitter-header.do"
    collectHeaderTypeUses(plan->typeAliases, uses);
#line 461 "/src/emitter-header.do"
    const auto& _iterable_99 = uses;
    for (const auto& use : *_iterable_99) {
#line 462 "/src/emitter-header.do"
        if (use->count < 2) {
#line 462 "/src/emitter-header.do"
            continue;
        }
#line 463 "/src/emitter-header.do"
        auto name = preferredHeaderTypeAlias(plan, use->spelling);
#line 464 "/src/emitter-header.do"
        if (name == std::string("")) {
#line 465 "/src/emitter-header.do"
            (name = (std::string("__type") + doof::to_string(state->nextAnonymousTypeIndex)));
#line 466 "/src/emitter-header.do"
            (state->nextAnonymousTypeIndex += 1);
#line 467 "/src/emitter-header.do"
            plan->ephemeralTypeAliases->push_back(((((std::string("using ") + name) + std::string(" = ")) + use->spelling) + std::string(";\n")));
        }
#line 469 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->functionSignatures, use->spelling, name);
#line 470 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->nativeAdapterSignatures, use->spelling, name);
#line 471 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->genericFunctionDefinitions, use->spelling, name);
#line 472 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->earlyModuleValueDeclarations, use->spelling, name);
#line 473 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->moduleValueDeclarations, use->spelling, name);
#line 474 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->earlyClassDefinitions, use->spelling, name);
#line 475 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->classDefinitions, use->spelling, name);
#line 476 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->interfaceAliases, use->spelling, name);
#line 477 "/src/emitter-header.do"
        replaceHeaderTypeUses(plan->enumDefinitions, use->spelling, name);
#line 480 "/src/emitter-header.do"
        if (preferredHeaderTypeAlias(plan, use->spelling) == std::string("")) {
#line 481 "/src/emitter-header.do"
            replaceHeaderTypeUses(plan->earlyTypeAliases, use->spelling, name);
#line 482 "/src/emitter-header.do"
            replaceHeaderTypeUses(plan->typeAliases, use->spelling, name);
        }
    }
}
#line 487 "/src/emitter-header.do"
std::string preferredHeaderTypeAlias(const std::shared_ptr<HeaderPlan>& plan, const std::string& spelling) {
#line 488 "/src/emitter-header.do"
    for (int32_t index = 0; index < static_cast<int32_t>((plan->preferredTypeAliasSpellings)->size()); ++index) {
#line 489 "/src/emitter-header.do"
        if (doof::array_at(plan->preferredTypeAliasSpellings, index, "src/emitter-header", 489) == spelling) {
#line 489 "/src/emitter-header.do"
            return doof::array_at(plan->preferredTypeAliasNames, index, "src/emitter-header", 489);
        }
    }
#line 491 "/src/emitter-header.do"
    return std::string("");
}
#line 494 "/src/emitter-header.do"
void collectHeaderTypeUses(const std::shared_ptr<std::vector<std::string>>& values, const std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>>& uses) {
#line 495 "/src/emitter-header.do"
    const auto& _iterable_102 = values;
    for (const auto& value : *_iterable_102) {
#line 496 "/src/emitter-header.do"
        auto offset = 0;
#line 497 "/src/emitter-header.do"
        const auto prefix = std::string("std::variant<");
#line 498 "/src/emitter-header.do"
        while (offset < static_cast<int32_t>(value.size())) {
#line 499 "/src/emitter-header.do"
            const auto relative = doof::string_indexOf(doof::string_substring(value, offset, static_cast<int32_t>(value.size())), prefix);
#line 500 "/src/emitter-header.do"
            if (relative < 0) {
#line 500 "/src/emitter-header.do"
                break;
            }
#line 501 "/src/emitter-header.do"
            const auto start = (offset + relative);
#line 502 "/src/emitter-header.do"
            const auto end = matchingAngleEnd(value, ((start + static_cast<int32_t>(prefix.size())) - 1));
#line 503 "/src/emitter-header.do"
            if (end < 0) {
#line 503 "/src/emitter-header.do"
                break;
            }
#line 504 "/src/emitter-header.do"
            const auto spelling = doof::string_substring(value, start, (end + 1));
#line 505 "/src/emitter-header.do"
            if (referenceOnlyVariant(spelling)) {
#line 505 "/src/emitter-header.do"
                addHeaderTypeUse(uses, spelling);
            }
#line 506 "/src/emitter-header.do"
            (offset = (end + 1));
        }
    }
}
#line 511 "/src/emitter-header.do"
int32_t matchingAngleEnd(const std::string& value, int32_t opening) {
#line 512 "/src/emitter-header.do"
    auto depth = 0;
#line 513 "/src/emitter-header.do"
    for (int32_t index = opening; index < static_cast<int32_t>(value.size()); ++index) {
#line 514 "/src/emitter-header.do"
        if (doof::string_at(value, index, "src/emitter-header", 514) == U'\u003C') {
#line 514 "/src/emitter-header.do"
            (depth += 1);
        } else if (doof::string_at(value, index, "src/emitter-header", 515) == U'\u003E') {
#line 516 "/src/emitter-header.do"
            (depth -= 1);
#line 517 "/src/emitter-header.do"
            if (depth == 0) {
#line 517 "/src/emitter-header.do"
                return index;
            }
        }
    }
#line 520 "/src/emitter-header.do"
    return -1;
}
#line 523 "/src/emitter-header.do"
bool referenceOnlyVariant(const std::string& spelling) {
#line 524 "/src/emitter-header.do"
    const auto inner = doof::string_substring(spelling, 13, (static_cast<int32_t>(spelling.size()) - 1));
#line 525 "/src/emitter-header.do"
    auto memberStart = 0;
#line 526 "/src/emitter-header.do"
    auto depth = 0;
#line 527 "/src/emitter-header.do"
    for (int32_t index = 0; index <= static_cast<int32_t>(inner.size()); ++index) {
#line 528 "/src/emitter-header.do"
        const auto atEnd = (index == static_cast<int32_t>(inner.size()));
#line 529 "/src/emitter-header.do"
        if (!atEnd) {
#line 530 "/src/emitter-header.do"
            if (doof::string_at(inner, index, "src/emitter-header", 530) == U'\u003C') {
#line 530 "/src/emitter-header.do"
                (depth += 1);
            } else if (doof::string_at(inner, index, "src/emitter-header", 531) == U'\u003E') {
#line 531 "/src/emitter-header.do"
                (depth -= 1);
            }
        }
#line 533 "/src/emitter-header.do"
        if (atEnd || ((doof::string_at(inner, index, "src/emitter-header", 533) == U'\u002C') && (depth == 0))) {
#line 534 "/src/emitter-header.do"
            const auto member = doof::string_trim(doof::string_substring(inner, memberStart, index));
#line 535 "/src/emitter-header.do"
            if ((member != std::string("std::monostate")) && !(doof::string_startsWith(member, std::string("std::shared_ptr<")) && doof::string_endsWith(member, std::string(">")))) {
#line 535 "/src/emitter-header.do"
                return false;
            }
#line 536 "/src/emitter-header.do"
            (memberStart = (index + 1));
        }
    }
#line 539 "/src/emitter-header.do"
    return true;
}
#line 542 "/src/emitter-header.do"
void addHeaderTypeUse(const std::shared_ptr<std::vector<std::shared_ptr<HeaderTypeUse>>>& uses, const std::string& spelling) {
#line 543 "/src/emitter-header.do"
    const auto& _iterable_106 = uses;
    for (const auto& use : *_iterable_106) {
#line 544 "/src/emitter-header.do"
        if (use->spelling == spelling) {
#line 544 "/src/emitter-header.do"
            (use->count += 1);
#line 544 "/src/emitter-header.do"
            return;
        }
    }
#line 546 "/src/emitter-header.do"
    uses->push_back(std::make_shared<HeaderTypeUse>(spelling, 1));
}
#line 549 "/src/emitter-header.do"
void replaceHeaderTypeUses(const std::shared_ptr<std::vector<std::string>>& values, const std::string& spelling, const std::string& name) {
#line 550 "/src/emitter-header.do"
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
#line 550 "/src/emitter-header.do"
        (doof::array_at(values, index, "src/emitter-header", 550) = doof::string_replaceAll(doof::array_at(values, index, "src/emitter-header", 550), spelling, name));
    }
}
#line 553 "/src/emitter-header.do"
void collectModuleValueDeclaration(const std::shared_ptr<HeaderPlan>& plan, const std::string& declaration, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 554 "/src/emitter-header.do"
    if (moduleValueDeclarationNeedsIncludes(type_)) {
#line 554 "/src/emitter-header.do"
        plan->moduleValueDeclarations->push_back(declaration);
    } else {
#line 555 "/src/emitter-header.do"
        plan->earlyModuleValueDeclarations->push_back(declaration);
    }
}
#line 562 "/src/emitter-header.do"
bool moduleValueDeclarationNeedsIncludes(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 563 "/src/emitter-header.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 565 "/src/emitter-header.do"
            if ((class_->symbol->kind == std::string("struct")) || class_->symbol->native_) {
#line 565 "/src/emitter-header.do"
                return true;
            }
#line 566 "/src/emitter-header.do"
            const auto& _iterable_109 = class_->typeArgs;
            for (const auto& argument : *_iterable_109) {
#line 566 "/src/emitter-header.do"
                if (moduleValueDeclarationNeedsIncludes(argument)) {
#line 566 "/src/emitter-header.do"
                    return true;
                }
            }
#line 567 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 569 "/src/emitter-header.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
#line 570 "/src/emitter-header.do"
            return true;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 571 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(array->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 573 "/src/emitter-header.do"
            return (moduleValueDeclarationNeedsIncludes(map->keyType) || moduleValueDeclarationNeedsIncludes(map->valueType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 575 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(set_->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 576 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(stream->elementType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 578 "/src/emitter-header.do"
            return (moduleValueDeclarationNeedsIncludes(result->valueType) || moduleValueDeclarationNeedsIncludes(result->errorType));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 581 "/src/emitter-header.do"
            const auto& _iterable_111 = tuple->elements;
            for (const auto& element : *_iterable_111) {
#line 581 "/src/emitter-header.do"
                if (moduleValueDeclarationNeedsIncludes(element)) {
#line 581 "/src/emitter-header.do"
                    return true;
                }
            }
#line 582 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 585 "/src/emitter-header.do"
            const auto& _iterable_113 = union_->types;
            for (const auto& member : *_iterable_113) {
#line 585 "/src/emitter-header.do"
                if (moduleValueDeclarationNeedsIncludes(member)) {
#line 585 "/src/emitter-header.do"
                    return true;
                }
            }
#line 586 "/src/emitter-header.do"
            return false;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 588 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(weak_->inner);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 590 "/src/emitter-header.do"
            const auto& _iterable_115 = function_->params;
            for (const auto& parameter : *_iterable_115) {
#line 590 "/src/emitter-header.do"
                if (moduleValueDeclarationNeedsIncludes(parameter->type_)) {
#line 590 "/src/emitter-header.do"
                    return true;
                }
            }
#line 591 "/src/emitter-header.do"
            return moduleValueDeclarationNeedsIncludes(function_->returnType);
    }
    else {
#line 593 "/src/emitter-header.do"
            return false;
    }
    }
    doof::unreachable();
#line 595 "/src/emitter-header.do"
    return false;
}
#line 598 "/src/emitter-header.do"
std::string emitModuleValueDeclaration(const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 599 "/src/emitter-header.do"
    return ((((std::string("extern ") + ::app_src_emitter_types_::emitContextType(type_, context)) + std::string(" ")) + name) + std::string(";\n"));
}
#line 602 "/src/emitter-header.do"
void addUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 603 "/src/emitter-header.do"
    const auto& _iterable_117 = values;
    for (const auto& existing : *_iterable_117) {
#line 603 "/src/emitter-header.do"
        if (existing == value) {
#line 603 "/src/emitter-header.do"
            return;
        }
    }
#line 604 "/src/emitter-header.do"
    values->push_back(value);
}
#line 610 "/src/emitter-header.do"
void addNativeClassForwardDeclaration(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::shared_ptr<HeaderPlan>& plan) {
#line 611 "/src/emitter-header.do"
    const auto cppName = ((symbol->nativeCppName == std::string("")) ? symbol->name : symbol->nativeCppName);
#line 612 "/src/emitter-header.do"
    const auto namespace_ = nativeNamespace(cppName);
#line 613 "/src/emitter-header.do"
    const auto name = ((namespace_ == std::string("")) ? cppName : doof::string_substring(cppName, (static_cast<int32_t>(namespace_.size()) + 2), static_cast<int32_t>(cppName.size())));
#line 614 "/src/emitter-header.do"
    const auto declaration = ((namespace_ == std::string("")) ? ((std::string("class ") + name) + std::string(";\n")) : ((((std::string("namespace ") + namespace_) + std::string(" { class ")) + name) + std::string("; }\n")));
#line 615 "/src/emitter-header.do"
    addUnique(plan->typeOnlyForwardDeclarations, declaration);
}
#line 618 "/src/emitter-header.do"
std::string nativeNamespace(const std::string& cppName) {
#line 619 "/src/emitter-header.do"
    auto separator = -1;
#line 620 "/src/emitter-header.do"
    for (int32_t i = 0; i < static_cast<int32_t>(cppName.size()); ++i) {
#line 621 "/src/emitter-header.do"
        if (((i + 1) < static_cast<int32_t>(cppName.size())) && (doof::string_substring(cppName, i, (i + 2)) == std::string("::"))) {
#line 622 "/src/emitter-header.do"
            (separator = i);
        }
    }
#line 625 "/src/emitter-header.do"
    if (separator < 0) {
#line 625 "/src/emitter-header.do"
        return std::string("");
    }
#line 626 "/src/emitter-header.do"
    return doof::string_substring(cppName, 0, separator);
}
#line 629 "/src/emitter-header.do"
std::string emitEnumDeclaration(const std::shared_ptr<::app_src_ast_::EnumDeclaration>& declaration, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 630 "/src/emitter-header.do"
    auto result = (((::app_src_emitter_decl_::emitDescriptionComment(declaration->description, std::string("")) + std::string("enum class ")) + declaration->name) + std::string(" {\n"));
#line 631 "/src/emitter-header.do"
    for (int32_t i = 0; i < static_cast<int32_t>((declaration->variants)->size()); ++i) {
#line 632 "/src/emitter-header.do"
        const auto variant = doof::array_at(declaration->variants, i, "src/emitter-header", 632);
#line 633 "/src/emitter-header.do"
        (result = (((result + ::app_src_emitter_decl_::emitDescriptionComment(variant->description, std::string("    "))) + std::string("    ")) + variant->name));
#line 634 "/src/emitter-header.do"
        if (!doof::is_null(variant->value)) {
#line 634 "/src/emitter-header.do"
            (result = ((result + std::string(" = ")) + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(variant->value), context, std::monostate{})));
        }
#line 635 "/src/emitter-header.do"
        if ((i + 1) < static_cast<int32_t>((declaration->variants)->size())) {
#line 635 "/src/emitter-header.do"
            (result = (result + std::string(",")));
        }
#line 636 "/src/emitter-header.do"
        (result = (result + std::string("\n")));
    }
#line 638 "/src/emitter-header.do"
    (result = (result + std::string("};\n")));
#line 639 "/src/emitter-header.do"
    (result = (((((result + std::string("inline const char* ")) + declaration->name) + std::string("_name(")) + declaration->name) + std::string(" value) {\n")));
#line 640 "/src/emitter-header.do"
    (result = (result + std::string("  switch (value) {\n")));
#line 641 "/src/emitter-header.do"
    const auto& _iterable_121 = declaration->variants;
    for (const auto& variant : *_iterable_121) {
#line 642 "/src/emitter-header.do"
        (result = (((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return \"")) + variant->name) + std::string("\";\n")));
    }
#line 644 "/src/emitter-header.do"
    (result = (result + std::string("  }\n  return \"\";\n}\n")));
#line 645 "/src/emitter-header.do"
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromName(std::string_view value) {\n")));
#line 646 "/src/emitter-header.do"
    const auto& _iterable_123 = declaration->variants;
    for (const auto& variant : *_iterable_123) {
#line 647 "/src/emitter-header.do"
        (result = (((((((result + std::string("  if (value == \"")) + variant->name) + std::string("\") return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
#line 649 "/src/emitter-header.do"
    (result = (result + std::string("  return std::nullopt;\n}\n")));
#line 650 "/src/emitter-header.do"
    (result = (((((result + std::string("inline std::optional<")) + declaration->name) + std::string("> ")) + declaration->name) + std::string("_fromValue(int32_t value) {\n")));
#line 651 "/src/emitter-header.do"
    (result = (((result + std::string("  switch (static_cast<")) + declaration->name) + std::string(">(value)) {\n")));
#line 652 "/src/emitter-header.do"
    const auto& _iterable_125 = declaration->variants;
    for (const auto& variant : *_iterable_125) {
#line 653 "/src/emitter-header.do"
        (result = (((((((((result + std::string("    case ")) + declaration->name) + std::string("::")) + variant->name) + std::string(": return ")) + declaration->name) + std::string("::")) + variant->name) + std::string(";\n")));
    }
#line 655 "/src/emitter-header.do"
    (result = (result + std::string("    default: return std::nullopt;\n  }\n}\n")));
#line 656 "/src/emitter-header.do"
    return (((((result + std::string("inline std::ostream& operator<<(std::ostream& output, ")) + declaration->name) + std::string(" value) { return output << ")) + declaration->name) + std::string("_name(value); }\n"));
}
#line 659 "/src/emitter-header.do"
std::string emitTypeAlias(const std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>& alias, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 660 "/src/emitter-header.do"
    if (doof::is_null(alias->resolvedType)) {
#line 660 "/src/emitter-header.do"
        doof::panic(((std::string("Type alias ") + alias->name) + std::string(" was not checked before emission")));
    }
#line 661 "/src/emitter-header.do"
    return (((((::app_src_emitter_decl_::emitDescriptionComment(alias->description, std::string("")) + std::string("using ")) + alias->name) + std::string(" = ")) + ::app_src_emitter_types_::emitType(doof::unwrap_optional(alias->resolvedType), context->modulePath)) + std::string(";\n"));
}
#line 664 "/src/emitter-header.do"
bool functionReturnsInt(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
#line 665 "/src/emitter-header.do"
    {
        auto _case_subject = doof::unwrap_optional(fn->resolvedType);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 667 "/src/emitter-header.do"
            {
                auto _case_subject = function_->returnType;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                    const auto& primitive = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 668 "/src/emitter-header.do"
                    return (primitive->name == std::string("int"));
            }
            else {
#line 669 "/src/emitter-header.do"
                    return false;
            }
            }
            doof::unreachable();
    }
    else {
#line 672 "/src/emitter-header.do"
            return false;
    }
    }
    doof::unreachable();
#line 674 "/src/emitter-header.do"
    return false;
}
#line 1 "<doof-generated>"
}
