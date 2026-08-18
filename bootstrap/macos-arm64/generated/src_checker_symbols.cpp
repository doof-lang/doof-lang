#include "src_checker_symbols.hpp"

namespace app_src_checker_symbols_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_validation_;
std::shared_ptr<::app_src_semantic_::ClassType> builtinSourceLocationType() {
    return ::app_src_checker_types_::classType(std::string("SourceLocation"), std::make_shared<::app_src_semantic_::Symbol>(std::string("class"), std::string("SourceLocation"), std::string("<builtin>"), true, std::string(""), true, std::string("doof_runtime.hpp"), std::string("doof::SourceLocation"), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
}
std::string casePatternName(const std::shared_ptr<::app_src_ast_::TypePattern>& pattern) {
    {
        auto _case_subject = pattern->type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if ((named->name == std::string("Success")) || (named->name == std::string("Failure"))) {
                return named->name;
            }
    }
    else {
    }
    }
    return std::string("");
}
void decorateAnnotationWithResolved(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolved) {
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            (named->resolvedType = optionalResolvedType(resolved));
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                    for (int32_t i = 0; i < static_cast<int32_t>((named->typeArgs)->size()); ++i) {
                        if (i < static_cast<int32_t>((class_->typeArgs)->size())) {
                            decorateAnnotationWithResolved(doof::array_at(named->typeArgs, i, "src/checker-symbols", 71), doof::array_at(class_->typeArgs, i, "src/checker-symbols", 71));
                        }
                    }
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            (array->resolvedType = optionalResolvedType(resolved));
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                    const auto& arrayResolved = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
                    decorateAnnotationWithResolved(array->elementType, arrayResolved->elementType);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
            (union_->resolvedType = optionalResolvedType(resolved));
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                    const auto& unionResolved = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
                    for (int32_t i = 0; i < static_cast<int32_t>((union_->types)->size()); ++i) {
                        if (i < static_cast<int32_t>((unionResolved->types)->size())) {
                            decorateAnnotationWithResolved(doof::array_at(union_->types, i, "src/checker-symbols", 89), doof::array_at(unionResolved->types, i, "src/checker-symbols", 89));
                        }
                    }
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
            (function_->resolvedType = optionalResolvedType(resolved));
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                    const auto& functionResolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                    for (int32_t i = 0; i < static_cast<int32_t>((function_->params)->size()); ++i) {
                        if (i < static_cast<int32_t>((functionResolved->params)->size())) {
                            decorateAnnotationWithResolved(doof::array_at(function_->params, i, "src/checker-symbols", 100)->type_, doof::array_at(functionResolved->params, i, "src/checker-symbols", 100)->type_);
                        }
                    }
                    decorateAnnotationWithResolved(function_->returnType, functionResolved->returnType);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
            (weak_->resolvedType = optionalResolvedType(resolved));
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                    const auto& weakResolved = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
                    decorateAnnotationWithResolved(weak_->type_, weakResolved->inner);
            }
            else {
            }
            }
    }
    }
}
bool blockContainsLoopExit(const std::shared_ptr<::app_src_ast_::Block>& block) {
    const auto& _iterable_1 = block->statements;
    for (const auto& statement : *_iterable_1) {
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BreakStatement>>(_case_subject)) {
                return true;
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
                const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
                if (blockContainsLoopExit(if_->body)) {
                    return true;
                }
                const auto& _iterable_2 = if_->elseIfs;
                for (const auto& branch : *_iterable_2) {
                    if (blockContainsLoopExit(branch->body)) {
                        return true;
                    }
                }
                if ((!doof::is_null(if_->else_)) && blockContainsLoopExit(doof::unwrap_optional(if_->else_))) {
                    return true;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
                const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
                const auto& _iterable_3 = case_->arms;
                for (const auto& arm : *_iterable_3) {
                    {
                        auto _case_subject = arm->body;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                            const auto& armBlock = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                            if (blockContainsLoopExit(armBlock)) {
                                return true;
                            }
                    }
                    else {
                    }
                    }
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject)) {
                const auto& with_ = std::get<std::shared_ptr<::app_src_ast_::WithStatement>>(_case_subject);
                if (blockContainsLoopExit(with_->body)) {
                    return true;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                const auto& nested = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
                if (blockContainsLoopExit(nested)) {
                    return true;
                }
        }
        else {
        }
        }
    }
    return false;
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> optionalResolvedType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& value) {
    return doof::optional_value(value);
}
int32_t functionParameterIndex(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>& parameters, const std::string& name) {
    for (int32_t i = 0; i < static_cast<int32_t>((parameters)->size()); ++i) {
        if (doof::array_at(parameters, i, "src/checker-symbols", 148)->name == name) {
            return i;
        }
    }
    return -1;
}
bool containsString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    const auto& _iterable_4 = values;
    for (const auto& existing : *_iterable_4) {
        if (existing == value) {
            return true;
        }
    }
    return false;
}
bool hasObjectProperty(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>>& properties, const std::string& name) {
    const auto& _iterable_5 = properties;
    for (const auto& property : *_iterable_5) {
        if (property->name == name) {
            return true;
        }
    }
    return false;
}
void predeclareModuleBindings(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    const auto& _iterable_6 = info->symbols;
    for (const auto& symbol : *_iterable_6) {
        if (((((symbol->kind == std::string("function")) || (symbol->kind == std::string("class"))) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("enum"))) {
            declare(scope, std::make_shared<::app_src_semantic_::Binding>(symbol->name, symbol->kind, symbolType(symbol, info, result), false, ::app_src_checker_validation_::checkerSemanticSpan(::app_src_checker_interfaces_::symbolSpan(info, symbol->name)), info->path, symbol, std::string(""), std::string(""), std::string("")));
        }
    }
    const auto& _iterable_7 = info->imports;
    for (const auto& imported : *_iterable_7) {
        if ((!imported->typeOnly && (!doof::is_null(imported->symbol))) && isValueSymbol(doof::unwrap_optional(imported->symbol))) {
            declare(scope, std::make_shared<::app_src_semantic_::Binding>(imported->localName, std::string("import"), symbolType(doof::unwrap_optional(imported->symbol), info, result), false, ::app_src_checker_validation_::checkerSemanticSpan(::app_src_checker_interfaces_::symbolSpan(info, imported->localName)), info->path, imported->symbol, std::string(""), std::string(""), std::string("")));
        }
    }
}
bool isNamespaceImport(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
    const auto& _iterable_8 = info->namespaceImports;
    for (const auto& imported : *_iterable_8) {
        if (imported->localName == name) {
            return true;
        }
    }
    return false;
}
bool isTypeOnlyNamespaceImport(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
    const auto& _iterable_9 = info->namespaceImports;
    for (const auto& imported : *_iterable_9) {
        if (imported->localName == name) {
            return imported->typeOnly;
        }
    }
    return false;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> namespaceMemberType(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& namespaceName, const std::string& memberName, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    const auto symbol = namespaceMemberSymbol(info, namespaceName, memberName, result);
    if (doof::is_null(symbol)) {
        return ::app_src_checker_types_::unknownType();
    }
    const auto source = ::app_src_checker_interfaces_::findModule(result, symbol->module);
    if (doof::is_null(source)) {
        return ::app_src_checker_types_::unknownType();
    }
    return symbolType(doof::unwrap_optional(symbol), doof::unwrap_optional(source), result);
}
std::shared_ptr<::app_src_semantic_::Symbol> namespaceMemberSymbol(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& namespaceName, const std::string& memberName, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    const auto& _iterable_10 = info->namespaceImports;
    for (const auto& imported : *_iterable_10) {
        if (imported->localName != namespaceName) {
            continue;
        }
        if (imported->typeOnly) {
            return nullptr;
        }
        const auto source = ::app_src_checker_interfaces_::findModule(result, imported->sourceModule);
        if (doof::is_null(source)) {
            return nullptr;
        }
        const auto& _iterable_11 = source->exports;
        for (const auto& symbol : *_iterable_11) {
            if ((symbol->name == memberName) && isValueSymbol(symbol)) {
                return symbol;
            }
        }
    }
    return nullptr;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> symbolType(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    if ((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) {
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::classType(declaredSymbolName(symbol), symbol, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})));
    }
    if (symbol->kind == std::string("interface")) {
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::interfaceType(declaredSymbolName(symbol), symbol, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})));
    }
    if (symbol->kind == std::string("enum")) {
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::enumType(declaredSymbolName(symbol), symbol));
    }
    const auto declaration = declarationFor(result, symbol);
    if (doof::is_null(declaration)) {
        return ::app_src_checker_types_::unknownType();
    }
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            if (!doof::is_null(fn->resolvedType)) {
                {
                    auto _case_subject = doof::unwrap_optional(fn->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                        const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(resolved);
                }
                else {
                }
                }
            }
            return ::app_src_checker_types_::functionType(functionParametersFor(fn, info, result), (doof::is_null(fn->returnType) ? ::app_src_checker_types_::noneType() : resolveAnnotation(doof::unwrap_optional(fn->returnType), info, result, fn->typeParams)), fn->typeParams);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            return resolveAnnotation(alias->type_, info, result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            if (!doof::is_null(const_->resolvedType)) {
                return doof::unwrap_optional(const_->resolvedType);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            if (!doof::is_null(readonly_->resolvedType)) {
                return doof::unwrap_optional(readonly_->resolvedType);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            if (!doof::is_null(binding->resolvedType)) {
                return doof::unwrap_optional(binding->resolvedType);
            }
    }
    else {
            return ::app_src_checker_types_::unknownType();
    }
    }
    return ::app_src_checker_types_::unknownType();
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> methodSignature(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> parameters = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
    const auto& _iterable_12 = method->params;
    for (const auto& parameter : *_iterable_12) {
        const auto parameterType = (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : resolveAnnotation(doof::unwrap_optional(parameter->type_), info, result, method->typeParams));
        parameters->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, parameterType, (!doof::is_null(parameter->defaultValue))));
    }
    return ::app_src_checker_types_::functionType(parameters, (doof::is_null(method->returnType) ? ::app_src_checker_types_::noneType() : resolveAnnotation(doof::unwrap_optional(method->returnType), info, result, method->typeParams)), method->typeParams);
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> functionParametersFor(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> resultTypes = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
    const auto& _iterable_13 = fn->params;
    for (const auto& parameter : *_iterable_13) {
        const auto parameterType = ((!doof::is_null(parameter->resolvedType)) ? doof::unwrap_optional(parameter->resolvedType) : (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : resolveAnnotation(doof::unwrap_optional(parameter->type_), info, result, fn->typeParams)));
        resultTypes->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, parameterType, (!doof::is_null(parameter->defaultValue))));
    }
    return resultTypes;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolveAnnotation(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<std::vector<std::string>>& typeParams) {
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (((named->name == std::string("none")) || (named->name == std::string("void"))) || (named->name == std::string("null"))) {
                return ::app_src_checker_types_::noneType();
            }
            if (named->name == std::string("never")) {
                return ::app_src_checker_types_::neverType();
            }
            if (named->name == std::string("JsonValue")) {
                return ::app_src_checker_types_::jsonValueType();
            }
            if (named->name == std::string("JsonObject")) {
                return ::app_src_checker_types_::jsonObjectType();
            }
            if (named->name == std::string("SourceLocation")) {
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(builtinSourceLocationType());
            }
            if (named->name == std::string("Range")) {
                return ::app_src_checker_types_::rangeType();
            }
            const auto& _iterable_14 = typeParams;
            for (const auto& typeParam : *_iterable_14) {
                if (named->name == typeParam) {
                    return ::app_src_checker_types_::typeParameter(named->name, std::string(""), std::monostate{});
                }
            }
            if (named->name == std::string("Tuple")) {
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> elements = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                const auto& _iterable_15 = named->typeArgs;
                for (const auto& argument : *_iterable_15) {
                    elements->push_back(resolveAnnotation(argument, info, result, typeParams));
                }
                return ::app_src_checker_types_::tupleType(elements);
            }
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
                std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> key = ::app_src_checker_types_::unknownType();
                std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> value = ::app_src_checker_types_::unknownType();
                if (static_cast<int32_t>((named->typeArgs)->size()) >= 2) {
                    (key = resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 273), info, result, typeParams));
                    (value = resolveAnnotation(doof::array_at(named->typeArgs, 1, "src/checker-symbols", 274), info, result, typeParams));
                }
                return ::app_src_checker_types_::mapType(key, value, (named->name == std::string("ReadonlyMap")));
            }
            if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
                const auto element = ((static_cast<int32_t>((named->typeArgs)->size()) >= 1) ? resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 279), info, result, typeParams) : ::app_src_checker_types_::unknownType());
                return ::app_src_checker_types_::setType(element, (named->name == std::string("ReadonlySet")));
            }
            if ((named->name == std::string("Stream")) && (static_cast<int32_t>((named->typeArgs)->size()) >= 1)) {
                return ::app_src_checker_types_::streamType(resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 282), info, result, typeParams));
            }
            if ((named->name == std::string("Actor")) && (static_cast<int32_t>((named->typeArgs)->size()) == 1)) {
                const auto inner = resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 284), info, result, typeParams);
                {
                    auto _case_subject = inner;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                        return ::app_src_checker_types_::actorType(class_);
                }
                else {
                        return ::app_src_checker_types_::unknownType();
                }
                }
                doof::unreachable();
            }
            if ((named->name == std::string("Promise")) && (static_cast<int32_t>((named->typeArgs)->size()) == 1)) {
                return ::app_src_checker_types_::promiseType(resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 290), info, result, typeParams));
            }
            if ((named->name == std::string("Result")) && (static_cast<int32_t>((named->typeArgs)->size()) >= 2)) {
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> value = std::monostate{};
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> error = std::monostate{};
                auto index = 0;
                const auto& _iterable_16 = named->typeArgs;
                for (const auto& typeArg : *_iterable_16) {
                    if (index == 0) {
                        (value = doof::optional_value(resolveAnnotation(typeArg, info, result, typeParams)));
                    }
                    if (index == 1) {
                        (error = doof::optional_value(resolveAnnotation(typeArg, info, result, typeParams)));
                    }
                    (index = (index + 1));
                }
                return ::app_src_checker_types_::resultType(doof::unwrap_optional(value), doof::unwrap_optional(error));
            }
            if (((named->name == std::string("Success")) || (named->name == std::string("Failure"))) && (static_cast<int32_t>((named->typeArgs)->size()) == 1)) {
                const auto payload = resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 303), info, result, typeParams);
                if (named->name == std::string("Success")) {
                    return ::app_src_checker_types_::resultType(payload, ::app_src_checker_types_::unknownType());
                }
                return ::app_src_checker_types_::resultType(::app_src_checker_types_::unknownType(), payload);
            }
            if ((((((((named->name == std::string("byte")) || (named->name == std::string("int"))) || (named->name == std::string("long"))) || (named->name == std::string("float"))) || (named->name == std::string("double"))) || (named->name == std::string("string"))) || (named->name == std::string("char"))) || (named->name == std::string("bool"))) {
                return ::app_src_checker_types_::primitive(named->name);
            }
            const auto symbol = [&]() -> std::shared_ptr<::app_src_semantic_::Symbol> { auto _coalesce_17 = named->resolvedSymbol; if (doof::is_null(_coalesce_17)) return symbolFor(info, named->name); return doof::unwrap_optional(_coalesce_17); }();
            if (doof::is_null(symbol)) {
                return ::app_src_checker_types_::unknownType();
            }
            if (symbol->kind == std::string("type-alias")) {
                const auto declaration = declarationFor(result, doof::unwrap_optional(symbol));
                if (doof::is_null(declaration)) {
                    return ::app_src_checker_types_::unknownType();
                }
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
                        const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
                        std::shared_ptr<std::vector<std::string>> aliasParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
                        const auto& _iterable_18 = typeParams;
                        for (const auto& outer : *_iterable_18) {
                            aliasParams->push_back(outer);
                        }
                        const auto& _iterable_19 = alias->typeParams;
                        for (const auto& parameter : *_iterable_19) {
                            aliasParams->push_back(parameter);
                        }
                        const auto resolvedAlias = resolveAnnotation(alias->type_, ::app_src_checker_interfaces_::classModuleFor(result, doof::unwrap_optional(symbol)), result, aliasParams);
                        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                        const auto& _iterable_20 = named->typeArgs;
                        for (const auto& argument : *_iterable_20) {
                            arguments->push_back(resolveAnnotation(argument, info, result, typeParams));
                        }
                        return ::app_src_checker_types_::substituteTypeParams(resolvedAlias, alias->typeParams, arguments);
                }
                else {
                        return ::app_src_checker_types_::unknownType();
                }
                }
                doof::unreachable();
            }
            if (symbol->kind == std::string("interface")) {
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                const auto& _iterable_21 = named->typeArgs;
                for (const auto& argument : *_iterable_21) {
                    typeArgs->push_back(resolveAnnotation(argument, info, result, typeParams));
                }
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::interfaceType(declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol), typeArgs));
            }
            if (symbol->kind == std::string("enum")) {
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::enumType(declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol)));
            }
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
            const auto& _iterable_22 = named->typeArgs;
            for (const auto& argument : *_iterable_22) {
                typeArgs->push_back(resolveAnnotation(argument, info, result, typeParams));
            }
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::classType(declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol), typeArgs));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            return ::app_src_checker_types_::arrayType(resolveAnnotation(array->elementType, info, result, typeParams), array->readonly_);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> members = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
            const auto& _iterable_23 = union_->types;
            for (const auto& item : *_iterable_23) {
                members->push_back(resolveAnnotation(item, info, result, typeParams));
            }
            return ::app_src_checker_types_::unionType(members);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
            std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
            const auto& _iterable_24 = function_->params;
            for (const auto& parameter : *_iterable_24) {
                params->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, resolveAnnotation(parameter->type_, info, result, typeParams), false));
            }
            return ::app_src_checker_types_::functionType(params, resolveAnnotation(function_->returnType, info, result, typeParams), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
            return ::app_src_checker_types_::weakType(resolveAnnotation(weak_->type_, info, result, typeParams));
    }
    }
    doof::unreachable();
    return ::app_src_checker_types_::unknownType();
}
bool declare(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::Binding>& binding) {
    const auto& _iterable_25 = scope->bindings;
    for (const auto& existing : *_iterable_25) {
        if (existing->name == binding->name) {
            return false;
        }
    }
    scope->bindings->push_back(binding);
    return true;
}
bool declareShadowing(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::Binding>& binding) {
    for (int32_t index = 0; index < static_cast<int32_t>((scope->bindings)->size()); ++index) {
        if (doof::array_at(scope->bindings, index, "src/checker-symbols", 363)->name == binding->name) {
            if ((doof::array_at(scope->bindings, index, "src/checker-symbols", 364)->kind != std::string("field")) && (doof::array_at(scope->bindings, index, "src/checker-symbols", 364)->kind != std::string("method"))) {
                return false;
            }
            (doof::array_at(scope->bindings, index, "src/checker-symbols", 365) = binding);
            return true;
        }
    }
    scope->bindings->push_back(binding);
    return true;
}
bool hasTypeParam(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        const auto& _iterable_26 = current->typeParams;
        for (const auto& typeParam : *_iterable_26) {
            if (typeParam == name) {
                return true;
            }
        }
        (current = current->parent);
    }
    return false;
}
std::string typeParamConstraintName(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        for (int32_t index = 0; index < static_cast<int32_t>((current->typeParams)->size()); ++index) {
            if ((doof::array_at(current->typeParams, index, "src/checker-symbols", 386) == name) && (index < static_cast<int32_t>((current->typeParamConstraintNames)->size()))) {
                return doof::array_at(current->typeParamConstraintNames, index, "src/checker-symbols", 387);
            }
        }
        (current = current->parent);
    }
    return std::string("");
}
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> typeParamConstraint(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        for (int32_t index = 0; index < static_cast<int32_t>((current->typeParams)->size()); ++index) {
            if ((doof::array_at(current->typeParams, index, "src/checker-symbols", 399) == name) && (index < static_cast<int32_t>((current->typeParamConstraints)->size()))) {
                return doof::array_at(current->typeParamConstraints, index, "src/checker-symbols", 400)->type_;
            }
        }
        (current = current->parent);
    }
    return std::monostate{};
}
std::shared_ptr<::app_src_semantic_::Binding> lookup(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        const auto& _iterable_27 = current->bindings;
        for (const auto& binding : *_iterable_27) {
            if (binding->name == name) {
                return binding;
            }
        }
        (current = current->parent);
    }
    return nullptr;
}
std::shared_ptr<::app_src_semantic_::Scope> returnScope(const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        if (!doof::is_null(current->returnType)) {
            return current;
        }
        (current = current->parent);
    }
    return nullptr;
}
std::shared_ptr<::app_src_semantic_::Scope> valueYieldScope(const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        if (current->inValueYieldBlock) {
            return current;
        }
        (current = current->parent);
    }
    return nullptr;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> currentThisType(const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
    while (!doof::is_null(current)) {
        if (!doof::is_null(current->thisType)) {
            return doof::unwrap_optional(current->thisType);
        }
        (current = current->parent);
    }
    return ::app_src_checker_types_::unknownType();
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> iterableElement(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& iterable) {
    {
        auto _case_subject = iterable;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            return array->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            return ::app_src_checker_types_::tupleType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{map->keyType, map->valueType}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            return set->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            return stream->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
            return ::app_src_checker_types_::primitive(std::string("int"));
    }
    else {
            return ::app_src_checker_types_::unknownType();
    }
    }
    doof::unreachable();
    return ::app_src_checker_types_::unknownType();
}
bool isBuiltinCallable(const std::string& name) {
    return (((((((((((((name == std::string("byte")) || (name == std::string("string"))) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double"))) || (name == std::string("bool"))) || (name == std::string("println"))) || (name == std::string("panic"))) || (name == std::string("assert"))) || (name == std::string("catchPanic"))) || (name == std::string("Success"))) || (name == std::string("Failure")));
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> builtinCallable(const std::string& name) {
    if (name == std::string("println")) {
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    if (name == std::string("panic")) {
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("message"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::neverType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    if (name == std::string("assert")) {
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("condition"), ::app_src_checker_types_::primitive(std::string("bool")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("message"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    if (name == std::string("catchPanic")) {
        const auto successType = ::app_src_checker_types_::typeParameter(std::string("T"), std::string(""), std::monostate{});
        const auto callbackType = ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), successType, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("f"), callbackType, false)}), ::app_src_checker_types_::resultType(successType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("T")}));
    }
    const auto result = ::app_src_checker_types_::primitive(name);
    return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false)}), result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
bool isBuiltinPrintlnCall(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& callee) {
    {
        auto _case_subject = callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
            return (((identifier->name == std::string("println")) && (!doof::is_null(identifier->resolvedBinding))) && (identifier->resolvedBinding->kind == std::string("builtin")));
    }
    else {
            return false;
    }
    }
    doof::unreachable();
}
std::shared_ptr<::app_src_semantic_::Symbol> symbolFor(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
    const auto& _iterable_28 = info->symbols;
    for (const auto& symbol : *_iterable_28) {
        if (symbol->name == name) {
            return symbol;
        }
    }
    const auto& _iterable_29 = info->imports;
    for (const auto& imported : *_iterable_29) {
        if (imported->localName == name) {
            return imported->symbol;
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_semantic_::Symbol> valueSymbolFor(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
    const auto& _iterable_30 = info->symbols;
    for (const auto& symbol : *_iterable_30) {
        if ((symbol->name == name) && isValueSymbol(symbol)) {
            return symbol;
        }
    }
    const auto& _iterable_31 = info->imports;
    for (const auto& imported : *_iterable_31) {
        if ((((imported->localName == name) && !imported->typeOnly) && (!doof::is_null(imported->symbol))) && isValueSymbol(doof::unwrap_optional(imported->symbol))) {
            return imported->symbol;
        }
    }
    return nullptr;
}
std::string valueUseDiagnostic(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
    const auto& _iterable_32 = info->imports;
    for (const auto& imported : *_iterable_32) {
        if (imported->localName != name) {
            continue;
        }
        if (imported->typeOnly) {
            return ((std::string("Type-only import '") + name) + std::string("' cannot be used as a value"));
        }
        if ((!doof::is_null(imported->symbol)) && !isValueSymbol(doof::unwrap_optional(imported->symbol))) {
            return ((std::string("Type '") + name) + std::string("' cannot be used as a value"));
        }
    }
    const auto& _iterable_33 = info->symbols;
    for (const auto& symbol : *_iterable_33) {
        if ((symbol->name == name) && !isValueSymbol(symbol)) {
            return ((std::string("Type '") + name) + std::string("' cannot be used as a value"));
        }
    }
    return std::string("");
}
bool isValueSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
    return (symbol->kind != std::string("type-alias"));
}
std::string declaredSymbolName(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
    return ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
}
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> declarationFor(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
    const auto module = ::app_src_checker_interfaces_::findModule(result, symbol->module);
    if (doof::is_null(module)) {
        return std::monostate{};
    }
    const auto declarationName = declaredSymbolName(symbol);
    const auto& _iterable_34 = module->program->statements;
    for (const auto& statement : *_iterable_34) {
        if (std::visit([](auto&& _obj) { return _obj->kind; }, statement) == std::string("export-list")) {
            continue;
        }
        const auto candidate = symbolName(statement);
        if (candidate == declarationName) {
            return doof::optional_value(statement);
        }
    }
    return std::monostate{};
}
std::string symbolName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
            return class_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
            return fn->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
            return interface_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
            return enum_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
            return alias->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
            return const_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
            return readonly_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
            return binding->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
            return let_->name;
    }
    else {
            return std::string("");
    }
    }
    doof::unreachable();
    return std::string("");
}
}
