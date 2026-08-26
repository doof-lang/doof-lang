#include "src_checker_symbols.hpp"

namespace app_src_checker_symbols_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_validation_;
#line 42 "/src/checker-symbols.do"
std::shared_ptr<::app_src_semantic_::ClassType> builtinSourceLocationType() {
#line 43 "/src/checker-symbols.do"
    return ::app_src_checker_types_::classType(std::string("SourceLocation"), std::make_shared<::app_src_semantic_::Symbol>(std::string("class"), std::string("SourceLocation"), std::string("<builtin>"), true, std::string(""), true, std::string("doof_runtime.hpp"), std::string("doof::SourceLocation"), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>>(std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})), std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
}
#line 54 "/src/checker-symbols.do"
std::string casePatternName(const std::shared_ptr<::app_src_ast_::TypePattern>& pattern) {
#line 55 "/src/checker-symbols.do"
    {
        auto _case_subject = pattern->type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 57 "/src/checker-symbols.do"
            if ((named->name == std::string("Success")) || (named->name == std::string("Failure"))) {
#line 57 "/src/checker-symbols.do"
                return named->name;
            }
    }
    else {
    }
    }
#line 61 "/src/checker-symbols.do"
    return std::string("");
}
#line 64 "/src/checker-symbols.do"
void decorateAnnotationWithResolved(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolved) {
#line 65 "/src/checker-symbols.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 67 "/src/checker-symbols.do"
            (named->resolvedType = optionalResolvedType(resolved));
#line 68 "/src/checker-symbols.do"
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                    const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 70 "/src/checker-symbols.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((named->typeArgs)->size()); ++i) {
#line 71 "/src/checker-symbols.do"
                        if (i < static_cast<int32_t>((class_->typeArgs)->size())) {
#line 71 "/src/checker-symbols.do"
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
#line 78 "/src/checker-symbols.do"
            (array->resolvedType = optionalResolvedType(resolved));
#line 79 "/src/checker-symbols.do"
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                    const auto& arrayResolved = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 80 "/src/checker-symbols.do"
                    decorateAnnotationWithResolved(array->elementType, arrayResolved->elementType);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
#line 85 "/src/checker-symbols.do"
            (union_->resolvedType = optionalResolvedType(resolved));
#line 86 "/src/checker-symbols.do"
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
                    const auto& unionResolved = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 88 "/src/checker-symbols.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((union_->types)->size()); ++i) {
#line 89 "/src/checker-symbols.do"
                        if (i < static_cast<int32_t>((unionResolved->types)->size())) {
#line 89 "/src/checker-symbols.do"
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
#line 96 "/src/checker-symbols.do"
            (function_->resolvedType = optionalResolvedType(resolved));
#line 97 "/src/checker-symbols.do"
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                    const auto& functionResolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 99 "/src/checker-symbols.do"
                    for (int32_t i = 0; i < static_cast<int32_t>((function_->params)->size()); ++i) {
#line 100 "/src/checker-symbols.do"
                        if (i < static_cast<int32_t>((functionResolved->params)->size())) {
#line 100 "/src/checker-symbols.do"
                            decorateAnnotationWithResolved(doof::array_at(function_->params, i, "src/checker-symbols", 100)->type_, doof::array_at(functionResolved->params, i, "src/checker-symbols", 100)->type_);
                        }
                    }
#line 102 "/src/checker-symbols.do"
                    decorateAnnotationWithResolved(function_->returnType, functionResolved->returnType);
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
#line 108 "/src/checker-symbols.do"
            (weak_->resolvedType = optionalResolvedType(resolved));
#line 109 "/src/checker-symbols.do"
            {
                auto _case_subject = resolved;
                if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
                    const auto& weakResolved = std::get<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject);
#line 110 "/src/checker-symbols.do"
                    decorateAnnotationWithResolved(weak_->type_, weakResolved->inner);
            }
            else {
            }
            }
    }
    }
}
#line 120 "/src/checker-symbols.do"
bool blockContainsLoopExit(const std::shared_ptr<::app_src_ast_::Block>& block) {
#line 121 "/src/checker-symbols.do"
    const auto& _iterable_5 = block->statements;
    for (const auto& statement : *_iterable_5) {
#line 122 "/src/checker-symbols.do"
        {
            auto _case_subject = statement;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::BreakStatement>>(_case_subject)) {
#line 123 "/src/checker-symbols.do"
                return true;
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject)) {
                const auto& if_ = std::get<std::shared_ptr<::app_src_ast_::IfStatement>>(_case_subject);
#line 125 "/src/checker-symbols.do"
                if (blockContainsLoopExit(if_->body)) {
#line 125 "/src/checker-symbols.do"
                    return true;
                }
#line 126 "/src/checker-symbols.do"
                const auto& _iterable_7 = if_->elseIfs;
                for (const auto& branch : *_iterable_7) {
#line 126 "/src/checker-symbols.do"
                    if (blockContainsLoopExit(branch->body)) {
#line 126 "/src/checker-symbols.do"
                        return true;
                    }
                }
#line 127 "/src/checker-symbols.do"
                if ((!doof::is_null(if_->else_)) && blockContainsLoopExit(doof::unwrap_optional(if_->else_))) {
#line 127 "/src/checker-symbols.do"
                    return true;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject)) {
                const auto& case_ = std::get<std::shared_ptr<::app_src_ast_::CaseStatement>>(_case_subject);
#line 130 "/src/checker-symbols.do"
                const auto& _iterable_9 = case_->arms;
                for (const auto& arm : *_iterable_9) {
#line 131 "/src/checker-symbols.do"
                    {
                        auto _case_subject = arm->body;
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                            const auto& armBlock = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 132 "/src/checker-symbols.do"
                            if (blockContainsLoopExit(armBlock)) {
#line 132 "/src/checker-symbols.do"
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
#line 137 "/src/checker-symbols.do"
                if (blockContainsLoopExit(with_->body)) {
#line 137 "/src/checker-symbols.do"
                    return true;
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
                const auto& nested = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 138 "/src/checker-symbols.do"
                if (blockContainsLoopExit(nested)) {
#line 138 "/src/checker-symbols.do"
                    return true;
                }
        }
        else {
        }
        }
    }
#line 142 "/src/checker-symbols.do"
    return false;
}
#line 145 "/src/checker-symbols.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> optionalResolvedType(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& value) {
#line 145 "/src/checker-symbols.do"
    return doof::optional_value(value);
}
#line 147 "/src/checker-symbols.do"
int32_t functionParameterIndex(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>& parameters, const std::string& name) {
#line 148 "/src/checker-symbols.do"
    for (int32_t i = 0; i < static_cast<int32_t>((parameters)->size()); ++i) {
#line 148 "/src/checker-symbols.do"
        if (doof::array_at(parameters, i, "src/checker-symbols", 148)->name == name) {
#line 148 "/src/checker-symbols.do"
            return i;
        }
    }
#line 149 "/src/checker-symbols.do"
    return -1;
}
#line 152 "/src/checker-symbols.do"
bool containsString(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 153 "/src/checker-symbols.do"
    const auto& _iterable_12 = values;
    for (const auto& existing : *_iterable_12) {
#line 153 "/src/checker-symbols.do"
        if (existing == value) {
#line 153 "/src/checker-symbols.do"
            return true;
        }
    }
#line 154 "/src/checker-symbols.do"
    return false;
}
#line 157 "/src/checker-symbols.do"
bool hasObjectProperty(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::ObjectProperty>>>& properties, const std::string& name) {
#line 158 "/src/checker-symbols.do"
    const auto& _iterable_14 = properties;
    for (const auto& property : *_iterable_14) {
#line 158 "/src/checker-symbols.do"
        if (property->name == name) {
#line 158 "/src/checker-symbols.do"
            return true;
        }
    }
#line 159 "/src/checker-symbols.do"
    return false;
}
#line 162 "/src/checker-symbols.do"
void predeclareModuleBindings(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 163 "/src/checker-symbols.do"
    const auto& _iterable_16 = info->symbols;
    for (const auto& symbol : *_iterable_16) {
#line 164 "/src/checker-symbols.do"
        if (((((symbol->kind == std::string("function")) || (symbol->kind == std::string("class"))) || (symbol->kind == std::string("struct"))) || (symbol->kind == std::string("interface"))) || (symbol->kind == std::string("enum"))) {
#line 165 "/src/checker-symbols.do"
            declare(scope, std::make_shared<::app_src_semantic_::Binding>(symbol->name, symbol->kind, symbolType(symbol, info, result), false, ::app_src_checker_validation_::checkerSemanticSpan(::app_src_checker_interfaces_::symbolSpan(info, symbol->name)), info->path, symbol, std::string(""), std::string(""), std::string("")));
        }
    }
#line 168 "/src/checker-symbols.do"
    const auto& _iterable_18 = info->imports;
    for (const auto& imported : *_iterable_18) {
#line 169 "/src/checker-symbols.do"
        if ((!imported->typeOnly && (!doof::is_null(imported->symbol))) && isValueSymbol(doof::unwrap_optional(imported->symbol))) {
#line 170 "/src/checker-symbols.do"
            declare(scope, std::make_shared<::app_src_semantic_::Binding>(imported->localName, std::string("import"), symbolType(doof::unwrap_optional(imported->symbol), info, result), false, ::app_src_checker_validation_::checkerSemanticSpan(::app_src_checker_interfaces_::symbolSpan(info, imported->localName)), info->path, imported->symbol, std::string(""), std::string(""), std::string("")));
        }
    }
}
#line 175 "/src/checker-symbols.do"
bool isNamespaceImport(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
#line 176 "/src/checker-symbols.do"
    const auto& _iterable_20 = info->namespaceImports;
    for (const auto& imported : *_iterable_20) {
#line 176 "/src/checker-symbols.do"
        if (imported->localName == name) {
#line 176 "/src/checker-symbols.do"
            return true;
        }
    }
#line 177 "/src/checker-symbols.do"
    return false;
}
#line 180 "/src/checker-symbols.do"
bool isTypeOnlyNamespaceImport(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
#line 181 "/src/checker-symbols.do"
    const auto& _iterable_22 = info->namespaceImports;
    for (const auto& imported : *_iterable_22) {
#line 181 "/src/checker-symbols.do"
        if (imported->localName == name) {
#line 181 "/src/checker-symbols.do"
            return imported->typeOnly;
        }
    }
#line 182 "/src/checker-symbols.do"
    return false;
}
#line 185 "/src/checker-symbols.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> namespaceMemberType(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& namespaceName, const std::string& memberName, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 186 "/src/checker-symbols.do"
    const auto symbol = namespaceMemberSymbol(info, namespaceName, memberName, result);
#line 187 "/src/checker-symbols.do"
    if (doof::is_null(symbol)) {
#line 187 "/src/checker-symbols.do"
        return ::app_src_checker_types_::unknownType();
    }
#line 188 "/src/checker-symbols.do"
    const auto source = ::app_src_checker_interfaces_::findModule(result, symbol->module);
#line 189 "/src/checker-symbols.do"
    if (doof::is_null(source)) {
#line 189 "/src/checker-symbols.do"
        return ::app_src_checker_types_::unknownType();
    }
#line 190 "/src/checker-symbols.do"
    return symbolType(doof::unwrap_optional(symbol), doof::unwrap_optional(source), result);
}
#line 193 "/src/checker-symbols.do"
std::shared_ptr<::app_src_semantic_::Symbol> namespaceMemberSymbol(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& namespaceName, const std::string& memberName, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 194 "/src/checker-symbols.do"
    const auto& _iterable_24 = info->namespaceImports;
    for (const auto& imported : *_iterable_24) {
#line 195 "/src/checker-symbols.do"
        if (imported->localName != namespaceName) {
#line 195 "/src/checker-symbols.do"
            continue;
        }
#line 196 "/src/checker-symbols.do"
        if (imported->typeOnly) {
#line 196 "/src/checker-symbols.do"
            return nullptr;
        }
#line 197 "/src/checker-symbols.do"
        const auto source = ::app_src_checker_interfaces_::findModule(result, imported->sourceModule);
#line 198 "/src/checker-symbols.do"
        if (doof::is_null(source)) {
#line 198 "/src/checker-symbols.do"
            return nullptr;
        }
#line 199 "/src/checker-symbols.do"
        const auto& _iterable_26 = source->exports;
        for (const auto& symbol : *_iterable_26) {
#line 200 "/src/checker-symbols.do"
            if ((symbol->name == memberName) && isValueSymbol(symbol)) {
#line 200 "/src/checker-symbols.do"
                return symbol;
            }
        }
    }
#line 203 "/src/checker-symbols.do"
    return nullptr;
}
#line 206 "/src/checker-symbols.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> symbolType(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 207 "/src/checker-symbols.do"
    if ((symbol->kind == std::string("class")) || (symbol->kind == std::string("struct"))) {
#line 207 "/src/checker-symbols.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::classType(declaredSymbolName(symbol), symbol, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})));
    }
#line 208 "/src/checker-symbols.do"
    if (symbol->kind == std::string("interface")) {
#line 208 "/src/checker-symbols.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::interfaceType(declaredSymbolName(symbol), symbol, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})));
    }
#line 209 "/src/checker-symbols.do"
    if (symbol->kind == std::string("enum")) {
#line 209 "/src/checker-symbols.do"
        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::enumType(declaredSymbolName(symbol), symbol));
    }
#line 210 "/src/checker-symbols.do"
    const auto declaration = declarationFor(result, symbol);
#line 211 "/src/checker-symbols.do"
    if (doof::is_null(declaration)) {
#line 211 "/src/checker-symbols.do"
        return ::app_src_checker_types_::unknownType();
    }
#line 212 "/src/checker-symbols.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 214 "/src/checker-symbols.do"
            if (!doof::is_null(fn->resolvedType)) {
#line 215 "/src/checker-symbols.do"
                {
                    auto _case_subject = doof::unwrap_optional(fn->resolvedType);
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                        const auto& resolved = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 216 "/src/checker-symbols.do"
                        return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(resolved);
                }
                else {
                }
                }
            }
#line 220 "/src/checker-symbols.do"
            return ::app_src_checker_types_::functionType(functionParametersFor(fn, info, result), (doof::is_null(fn->returnType) ? ::app_src_checker_types_::noneType() : resolveAnnotation(doof::unwrap_optional(fn->returnType), info, result, fn->typeParams)), fn->typeParams);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 222 "/src/checker-symbols.do"
            return resolveAnnotation(alias->type_, info, result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 223 "/src/checker-symbols.do"
            if (!doof::is_null(const_->resolvedType)) {
#line 223 "/src/checker-symbols.do"
                return doof::unwrap_optional(const_->resolvedType);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 224 "/src/checker-symbols.do"
            if (!doof::is_null(readonly_->resolvedType)) {
#line 224 "/src/checker-symbols.do"
                return doof::unwrap_optional(readonly_->resolvedType);
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 225 "/src/checker-symbols.do"
            if (!doof::is_null(binding->resolvedType)) {
#line 225 "/src/checker-symbols.do"
                return doof::unwrap_optional(binding->resolvedType);
            }
    }
    else {
#line 226 "/src/checker-symbols.do"
            return ::app_src_checker_types_::unknownType();
    }
    }
#line 228 "/src/checker-symbols.do"
    return ::app_src_checker_types_::unknownType();
}
#line 234 "/src/checker-symbols.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> methodSignature(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 235 "/src/checker-symbols.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> parameters = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 236 "/src/checker-symbols.do"
    const auto& _iterable_28 = method->params;
    for (const auto& parameter : *_iterable_28) {
#line 237 "/src/checker-symbols.do"
        const auto parameterType = (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : resolveAnnotation(doof::unwrap_optional(parameter->type_), info, result, method->typeParams));
#line 238 "/src/checker-symbols.do"
        parameters->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, parameterType, (!doof::is_null(parameter->defaultValue))));
    }
#line 240 "/src/checker-symbols.do"
    return ::app_src_checker_types_::functionType(parameters, (doof::is_null(method->returnType) ? ::app_src_checker_types_::noneType() : resolveAnnotation(doof::unwrap_optional(method->returnType), info, result, method->typeParams)), method->typeParams);
}
#line 243 "/src/checker-symbols.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> functionParametersFor(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 244 "/src/checker-symbols.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> resultTypes = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 245 "/src/checker-symbols.do"
    const auto& _iterable_30 = fn->params;
    for (const auto& parameter : *_iterable_30) {
#line 246 "/src/checker-symbols.do"
        const auto parameterType = ((!doof::is_null(parameter->resolvedType)) ? doof::unwrap_optional(parameter->resolvedType) : (doof::is_null(parameter->type_) ? ::app_src_checker_types_::unknownType() : resolveAnnotation(doof::unwrap_optional(parameter->type_), info, result, fn->typeParams)));
#line 247 "/src/checker-symbols.do"
        resultTypes->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, parameterType, (!doof::is_null(parameter->defaultValue))));
    }
#line 249 "/src/checker-symbols.do"
    return resultTypes;
}
#line 252 "/src/checker-symbols.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolveAnnotation(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<std::vector<std::string>>& typeParams) {
#line 255 "/src/checker-symbols.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 257 "/src/checker-symbols.do"
            if (((named->name == std::string("none")) || (named->name == std::string("void"))) || (named->name == std::string("null"))) {
#line 257 "/src/checker-symbols.do"
                return ::app_src_checker_types_::noneType();
            }
#line 258 "/src/checker-symbols.do"
            if (named->name == std::string("never")) {
#line 258 "/src/checker-symbols.do"
                return ::app_src_checker_types_::neverType();
            }
#line 259 "/src/checker-symbols.do"
            if (named->name == std::string("JsonValue")) {
#line 259 "/src/checker-symbols.do"
                return ::app_src_checker_types_::jsonValueType();
            }
#line 260 "/src/checker-symbols.do"
            if (named->name == std::string("JsonObject")) {
#line 260 "/src/checker-symbols.do"
                return ::app_src_checker_types_::jsonObjectType();
            }
#line 261 "/src/checker-symbols.do"
            if (named->name == std::string("SourceLocation")) {
#line 261 "/src/checker-symbols.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(builtinSourceLocationType());
            }
#line 262 "/src/checker-symbols.do"
            if (named->name == std::string("WeakReferenceError")) {
#line 262 "/src/checker-symbols.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::weakReferenceErrorType());
            }
#line 263 "/src/checker-symbols.do"
            if (named->name == std::string("Range")) {
#line 263 "/src/checker-symbols.do"
                return ::app_src_checker_types_::rangeType();
            }
#line 264 "/src/checker-symbols.do"
            const auto& _iterable_32 = typeParams;
            for (const auto& typeParam : *_iterable_32) {
#line 264 "/src/checker-symbols.do"
                if (named->name == typeParam) {
#line 264 "/src/checker-symbols.do"
                    return ::app_src_checker_types_::typeParameter(named->name, std::string(""), std::monostate{});
                }
            }
#line 265 "/src/checker-symbols.do"
            if (named->name == std::string("Tuple")) {
#line 266 "/src/checker-symbols.do"
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> elements = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 267 "/src/checker-symbols.do"
                const auto& _iterable_34 = named->typeArgs;
                for (const auto& argument : *_iterable_34) {
#line 267 "/src/checker-symbols.do"
                    elements->push_back(resolveAnnotation(argument, info, result, typeParams));
                }
#line 268 "/src/checker-symbols.do"
                return ::app_src_checker_types_::tupleType(elements);
            }
#line 270 "/src/checker-symbols.do"
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
#line 271 "/src/checker-symbols.do"
                std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> key = ::app_src_checker_types_::unknownType();
#line 272 "/src/checker-symbols.do"
                std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> value = ::app_src_checker_types_::unknownType();
#line 273 "/src/checker-symbols.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) >= 2) {
#line 274 "/src/checker-symbols.do"
                    (key = resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 274), info, result, typeParams));
#line 275 "/src/checker-symbols.do"
                    (value = resolveAnnotation(doof::array_at(named->typeArgs, 1, "src/checker-symbols", 275), info, result, typeParams));
                }
#line 277 "/src/checker-symbols.do"
                return ::app_src_checker_types_::mapType(key, value, (named->name == std::string("ReadonlyMap")));
            }
#line 279 "/src/checker-symbols.do"
            if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
#line 280 "/src/checker-symbols.do"
                const auto element = ((static_cast<int32_t>((named->typeArgs)->size()) >= 1) ? resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 280), info, result, typeParams) : ::app_src_checker_types_::unknownType());
#line 281 "/src/checker-symbols.do"
                return ::app_src_checker_types_::setType(element, (named->name == std::string("ReadonlySet")));
            }
#line 283 "/src/checker-symbols.do"
            if ((named->name == std::string("Stream")) && (static_cast<int32_t>((named->typeArgs)->size()) >= 1)) {
#line 283 "/src/checker-symbols.do"
                return ::app_src_checker_types_::streamType(resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 283), info, result, typeParams));
            }
#line 284 "/src/checker-symbols.do"
            if ((named->name == std::string("Actor")) && (static_cast<int32_t>((named->typeArgs)->size()) == 1)) {
#line 285 "/src/checker-symbols.do"
                const auto inner = resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 285), info, result, typeParams);
#line 286 "/src/checker-symbols.do"
                {
                    auto _case_subject = inner;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 287 "/src/checker-symbols.do"
                        return ::app_src_checker_types_::actorType(class_);
                }
                else {
#line 288 "/src/checker-symbols.do"
                        return ::app_src_checker_types_::unknownType();
                }
                }
                doof::unreachable();
            }
#line 291 "/src/checker-symbols.do"
            if ((named->name == std::string("Promise")) && (static_cast<int32_t>((named->typeArgs)->size()) == 1)) {
#line 291 "/src/checker-symbols.do"
                return ::app_src_checker_types_::promiseType(resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 291), info, result, typeParams));
            }
#line 292 "/src/checker-symbols.do"
            if ((named->name == std::string("Result")) && (static_cast<int32_t>((named->typeArgs)->size()) >= 2)) {
#line 293 "/src/checker-symbols.do"
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> value = std::monostate{};
#line 294 "/src/checker-symbols.do"
                std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> error = std::monostate{};
#line 295 "/src/checker-symbols.do"
                auto index = 0;
#line 296 "/src/checker-symbols.do"
                const auto& _iterable_36 = named->typeArgs;
                for (const auto& typeArg : *_iterable_36) {
#line 297 "/src/checker-symbols.do"
                    if (index == 0) {
#line 297 "/src/checker-symbols.do"
                        (value = doof::optional_value(resolveAnnotation(typeArg, info, result, typeParams)));
                    }
#line 298 "/src/checker-symbols.do"
                    if (index == 1) {
#line 298 "/src/checker-symbols.do"
                        (error = doof::optional_value(resolveAnnotation(typeArg, info, result, typeParams)));
                    }
#line 299 "/src/checker-symbols.do"
                    (index = (index + 1));
                }
#line 301 "/src/checker-symbols.do"
                return ::app_src_checker_types_::resultType(doof::unwrap_optional(value), doof::unwrap_optional(error));
            }
#line 303 "/src/checker-symbols.do"
            if (((named->name == std::string("Success")) || (named->name == std::string("Failure"))) && (static_cast<int32_t>((named->typeArgs)->size()) == 1)) {
#line 304 "/src/checker-symbols.do"
                const auto payload = resolveAnnotation(doof::array_at(named->typeArgs, 0, "src/checker-symbols", 304), info, result, typeParams);
#line 305 "/src/checker-symbols.do"
                if (named->name == std::string("Success")) {
#line 305 "/src/checker-symbols.do"
                    return ::app_src_checker_types_::resultType(payload, ::app_src_checker_types_::unknownType());
                }
#line 306 "/src/checker-symbols.do"
                return ::app_src_checker_types_::resultType(::app_src_checker_types_::unknownType(), payload);
            }
#line 308 "/src/checker-symbols.do"
            if ((((((((named->name == std::string("byte")) || (named->name == std::string("int"))) || (named->name == std::string("long"))) || (named->name == std::string("float"))) || (named->name == std::string("double"))) || (named->name == std::string("string"))) || (named->name == std::string("char"))) || (named->name == std::string("bool"))) {
#line 308 "/src/checker-symbols.do"
                return ::app_src_checker_types_::primitive(named->name);
            }
#line 309 "/src/checker-symbols.do"
            const auto symbol = [&]() -> std::shared_ptr<::app_src_semantic_::Symbol> { auto _coalesce_37 = named->resolvedSymbol; if (doof::is_null(_coalesce_37)) return symbolFor(info, named->name); return doof::unwrap_optional(_coalesce_37); }();
#line 310 "/src/checker-symbols.do"
            if (doof::is_null(symbol)) {
#line 310 "/src/checker-symbols.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 311 "/src/checker-symbols.do"
            if (symbol->kind == std::string("type-alias")) {
#line 312 "/src/checker-symbols.do"
                const auto declaration = declarationFor(result, doof::unwrap_optional(symbol));
#line 313 "/src/checker-symbols.do"
                if (doof::is_null(declaration)) {
#line 313 "/src/checker-symbols.do"
                    return ::app_src_checker_types_::unknownType();
                }
#line 314 "/src/checker-symbols.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
                        const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 316 "/src/checker-symbols.do"
                        std::shared_ptr<std::vector<std::string>> aliasParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 317 "/src/checker-symbols.do"
                        const auto& _iterable_39 = typeParams;
                        for (const auto& outer : *_iterable_39) {
#line 317 "/src/checker-symbols.do"
                            aliasParams->push_back(outer);
                        }
#line 318 "/src/checker-symbols.do"
                        const auto& _iterable_41 = alias->typeParams;
                        for (const auto& parameter : *_iterable_41) {
#line 318 "/src/checker-symbols.do"
                            aliasParams->push_back(parameter);
                        }
#line 319 "/src/checker-symbols.do"
                        const auto resolvedAlias = resolveAnnotation(alias->type_, ::app_src_checker_interfaces_::classModuleFor(result, doof::unwrap_optional(symbol)), result, aliasParams);
#line 320 "/src/checker-symbols.do"
                        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 321 "/src/checker-symbols.do"
                        const auto& _iterable_43 = named->typeArgs;
                        for (const auto& argument : *_iterable_43) {
#line 321 "/src/checker-symbols.do"
                            arguments->push_back(resolveAnnotation(argument, info, result, typeParams));
                        }
#line 322 "/src/checker-symbols.do"
                        return ::app_src_checker_types_::substituteTypeParams(resolvedAlias, alias->typeParams, arguments);
                }
                else {
#line 324 "/src/checker-symbols.do"
                        return ::app_src_checker_types_::unknownType();
                }
                }
                doof::unreachable();
            }
#line 327 "/src/checker-symbols.do"
            if (symbol->kind == std::string("interface")) {
#line 328 "/src/checker-symbols.do"
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 329 "/src/checker-symbols.do"
                const auto& _iterable_45 = named->typeArgs;
                for (const auto& argument : *_iterable_45) {
#line 329 "/src/checker-symbols.do"
                    typeArgs->push_back(resolveAnnotation(argument, info, result, typeParams));
                }
#line 330 "/src/checker-symbols.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::interfaceType(declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol), typeArgs));
            }
#line 332 "/src/checker-symbols.do"
            if (symbol->kind == std::string("enum")) {
#line 332 "/src/checker-symbols.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::enumType(declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol)));
            }
#line 333 "/src/checker-symbols.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 334 "/src/checker-symbols.do"
            const auto& _iterable_47 = named->typeArgs;
            for (const auto& argument : *_iterable_47) {
#line 334 "/src/checker-symbols.do"
                typeArgs->push_back(resolveAnnotation(argument, info, result, typeParams));
            }
#line 335 "/src/checker-symbols.do"
            return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::classType(declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol), typeArgs));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
#line 337 "/src/checker-symbols.do"
            return ::app_src_checker_types_::arrayType(resolveAnnotation(array->elementType, info, result, typeParams), array->readonly_);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
#line 339 "/src/checker-symbols.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> members = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 340 "/src/checker-symbols.do"
            const auto& _iterable_49 = union_->types;
            for (const auto& item : *_iterable_49) {
#line 340 "/src/checker-symbols.do"
                members->push_back(resolveAnnotation(item, info, result, typeParams));
            }
#line 341 "/src/checker-symbols.do"
            return ::app_src_checker_types_::unionType(members);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
#line 344 "/src/checker-symbols.do"
            std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 345 "/src/checker-symbols.do"
            const auto& _iterable_51 = function_->params;
            for (const auto& parameter : *_iterable_51) {
#line 346 "/src/checker-symbols.do"
                params->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, resolveAnnotation(parameter->type_, info, result, typeParams), false));
            }
#line 348 "/src/checker-symbols.do"
            return ::app_src_checker_types_::functionType(params, resolveAnnotation(function_->returnType, info, result, typeParams), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
#line 350 "/src/checker-symbols.do"
            return ::app_src_checker_types_::weakType(resolveAnnotation(weak_->type_, info, result, typeParams));
    }
    }
    doof::unreachable();
#line 352 "/src/checker-symbols.do"
    return ::app_src_checker_types_::unknownType();
}
#line 355 "/src/checker-symbols.do"
bool declare(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::Binding>& binding) {
#line 356 "/src/checker-symbols.do"
    const auto& _iterable_53 = scope->bindings;
    for (const auto& existing : *_iterable_53) {
#line 356 "/src/checker-symbols.do"
        if (existing->name == binding->name) {
#line 356 "/src/checker-symbols.do"
            return false;
        }
    }
#line 357 "/src/checker-symbols.do"
    scope->bindings->push_back(binding);
#line 358 "/src/checker-symbols.do"
    return true;
}
#line 362 "/src/checker-symbols.do"
bool declareShadowing(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::shared_ptr<::app_src_semantic_::Binding>& binding) {
#line 363 "/src/checker-symbols.do"
    for (int32_t index = 0; index < static_cast<int32_t>((scope->bindings)->size()); ++index) {
#line 364 "/src/checker-symbols.do"
        if (doof::array_at(scope->bindings, index, "src/checker-symbols", 364)->name == binding->name) {
#line 365 "/src/checker-symbols.do"
            if ((doof::array_at(scope->bindings, index, "src/checker-symbols", 365)->kind != std::string("field")) && (doof::array_at(scope->bindings, index, "src/checker-symbols", 365)->kind != std::string("method"))) {
#line 365 "/src/checker-symbols.do"
                return false;
            }
#line 366 "/src/checker-symbols.do"
            (doof::array_at(scope->bindings, index, "src/checker-symbols", 366) = binding);
#line 367 "/src/checker-symbols.do"
            return true;
        }
    }
#line 370 "/src/checker-symbols.do"
    scope->bindings->push_back(binding);
#line 371 "/src/checker-symbols.do"
    return true;
}
#line 374 "/src/checker-symbols.do"
bool hasTypeParam(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
#line 375 "/src/checker-symbols.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 376 "/src/checker-symbols.do"
    while (!doof::is_null(current)) {
#line 377 "/src/checker-symbols.do"
        const auto& _iterable_56 = current->typeParams;
        for (const auto& typeParam : *_iterable_56) {
#line 377 "/src/checker-symbols.do"
            if (typeParam == name) {
#line 377 "/src/checker-symbols.do"
                return true;
            }
        }
#line 378 "/src/checker-symbols.do"
        (current = current->parent);
    }
#line 380 "/src/checker-symbols.do"
    return false;
}
#line 383 "/src/checker-symbols.do"
std::string typeParamConstraintName(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
#line 384 "/src/checker-symbols.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 385 "/src/checker-symbols.do"
    while (!doof::is_null(current)) {
#line 386 "/src/checker-symbols.do"
        for (int32_t index = 0; index < static_cast<int32_t>((current->typeParams)->size()); ++index) {
#line 387 "/src/checker-symbols.do"
            if ((doof::array_at(current->typeParams, index, "src/checker-symbols", 387) == name) && (index < static_cast<int32_t>((current->typeParamConstraintNames)->size()))) {
#line 388 "/src/checker-symbols.do"
                return doof::array_at(current->typeParamConstraintNames, index, "src/checker-symbols", 388);
            }
        }
#line 391 "/src/checker-symbols.do"
        (current = current->parent);
    }
#line 393 "/src/checker-symbols.do"
    return std::string("");
}
#line 396 "/src/checker-symbols.do"
std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> typeParamConstraint(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
#line 397 "/src/checker-symbols.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 398 "/src/checker-symbols.do"
    while (!doof::is_null(current)) {
#line 399 "/src/checker-symbols.do"
        for (int32_t index = 0; index < static_cast<int32_t>((current->typeParams)->size()); ++index) {
#line 400 "/src/checker-symbols.do"
            if ((doof::array_at(current->typeParams, index, "src/checker-symbols", 400) == name) && (index < static_cast<int32_t>((current->typeParamConstraints)->size()))) {
#line 401 "/src/checker-symbols.do"
                return doof::array_at(current->typeParamConstraints, index, "src/checker-symbols", 401)->type_;
            }
        }
#line 404 "/src/checker-symbols.do"
        (current = current->parent);
    }
#line 406 "/src/checker-symbols.do"
    return std::monostate{};
}
#line 409 "/src/checker-symbols.do"
std::shared_ptr<::app_src_semantic_::Binding> lookup(const std::shared_ptr<::app_src_semantic_::Scope>& scope, const std::string& name) {
#line 410 "/src/checker-symbols.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 411 "/src/checker-symbols.do"
    while (!doof::is_null(current)) {
#line 412 "/src/checker-symbols.do"
        const auto& _iterable_60 = current->bindings;
        for (const auto& binding : *_iterable_60) {
#line 412 "/src/checker-symbols.do"
            if (binding->name == name) {
#line 412 "/src/checker-symbols.do"
                return binding;
            }
        }
#line 413 "/src/checker-symbols.do"
        (current = current->parent);
    }
#line 415 "/src/checker-symbols.do"
    return nullptr;
}
#line 418 "/src/checker-symbols.do"
std::shared_ptr<::app_src_semantic_::Scope> returnScope(const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 419 "/src/checker-symbols.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 420 "/src/checker-symbols.do"
    while (!doof::is_null(current)) {
#line 421 "/src/checker-symbols.do"
        if (!doof::is_null(current->returnType)) {
#line 421 "/src/checker-symbols.do"
            return current;
        }
#line 422 "/src/checker-symbols.do"
        (current = current->parent);
    }
#line 424 "/src/checker-symbols.do"
    return nullptr;
}
#line 427 "/src/checker-symbols.do"
std::shared_ptr<::app_src_semantic_::Scope> valueYieldScope(const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 428 "/src/checker-symbols.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 429 "/src/checker-symbols.do"
    while (!doof::is_null(current)) {
#line 430 "/src/checker-symbols.do"
        if (current->inValueYieldBlock) {
#line 430 "/src/checker-symbols.do"
            return current;
        }
#line 431 "/src/checker-symbols.do"
        (current = current->parent);
    }
#line 433 "/src/checker-symbols.do"
    return nullptr;
}
#line 436 "/src/checker-symbols.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> currentThisType(const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 437 "/src/checker-symbols.do"
    std::shared_ptr<::app_src_semantic_::Scope> current = scope;
#line 438 "/src/checker-symbols.do"
    while (!doof::is_null(current)) {
#line 439 "/src/checker-symbols.do"
        if (!doof::is_null(current->thisType)) {
#line 439 "/src/checker-symbols.do"
            return doof::unwrap_optional(current->thisType);
        }
#line 440 "/src/checker-symbols.do"
        (current = current->parent);
    }
#line 442 "/src/checker-symbols.do"
    return ::app_src_checker_types_::unknownType();
}
#line 445 "/src/checker-symbols.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> iterableElement(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& iterable) {
#line 446 "/src/checker-symbols.do"
    {
        auto _case_subject = iterable;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 447 "/src/checker-symbols.do"
            return array->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 448 "/src/checker-symbols.do"
            return ::app_src_checker_types_::tupleType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{map->keyType, map->valueType}));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 449 "/src/checker-symbols.do"
            return set->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 450 "/src/checker-symbols.do"
            return stream->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
#line 451 "/src/checker-symbols.do"
            return ::app_src_checker_types_::primitive(std::string("int"));
    }
    else {
#line 452 "/src/checker-symbols.do"
            return ::app_src_checker_types_::unknownType();
    }
    }
    doof::unreachable();
#line 454 "/src/checker-symbols.do"
    return ::app_src_checker_types_::unknownType();
}
#line 457 "/src/checker-symbols.do"
bool isBuiltinCallable(const std::string& name) {
#line 458 "/src/checker-symbols.do"
    return (((((((((((((name == std::string("byte")) || (name == std::string("string"))) || (name == std::string("int"))) || (name == std::string("long"))) || (name == std::string("float"))) || (name == std::string("double"))) || (name == std::string("bool"))) || (name == std::string("println"))) || (name == std::string("panic"))) || (name == std::string("assert"))) || (name == std::string("catchPanic"))) || (name == std::string("Success"))) || (name == std::string("Failure")));
}
#line 461 "/src/checker-symbols.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> builtinCallable(const std::string& name) {
#line 462 "/src/checker-symbols.do"
    if (name == std::string("println")) {
#line 462 "/src/checker-symbols.do"
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
#line 463 "/src/checker-symbols.do"
    if (name == std::string("panic")) {
#line 463 "/src/checker-symbols.do"
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("message"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::neverType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
#line 464 "/src/checker-symbols.do"
    if (name == std::string("assert")) {
#line 465 "/src/checker-symbols.do"
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("condition"), ::app_src_checker_types_::primitive(std::string("bool")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("message"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
#line 470 "/src/checker-symbols.do"
    if (name == std::string("catchPanic")) {
#line 471 "/src/checker-symbols.do"
        const auto successType = ::app_src_checker_types_::typeParameter(std::string("T"), std::string(""), std::monostate{});
#line 472 "/src/checker-symbols.do"
        const auto callbackType = ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), successType, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 473 "/src/checker-symbols.do"
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("f"), callbackType, false)}), ::app_src_checker_types_::resultType(successType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("T")}));
    }
#line 477 "/src/checker-symbols.do"
    if (name == std::string("string")) {
#line 478 "/src/checker-symbols.do"
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{::app_src_checker_types_::primitive(std::string("byte")), ::app_src_checker_types_::primitive(std::string("int")), ::app_src_checker_types_::primitive(std::string("long")), ::app_src_checker_types_::primitive(std::string("float")), ::app_src_checker_types_::primitive(std::string("double")), ::app_src_checker_types_::primitive(std::string("string")), ::app_src_checker_types_::primitive(std::string("char")), ::app_src_checker_types_::primitive(std::string("bool"))})), false)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
#line 487 "/src/checker-symbols.do"
    if (name == std::string("bool")) {
#line 488 "/src/checker-symbols.do"
        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("bool")), false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
#line 490 "/src/checker-symbols.do"
    const auto result = ::app_src_checker_types_::primitive(name);
#line 491 "/src/checker-symbols.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> castInputs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{::app_src_checker_types_::primitive(std::string("byte")), ::app_src_checker_types_::primitive(std::string("int")), ::app_src_checker_types_::primitive(std::string("long")), ::app_src_checker_types_::primitive(std::string("float")), ::app_src_checker_types_::primitive(std::string("double"))});
#line 494 "/src/checker-symbols.do"
    if (name == std::string("int")) {
#line 494 "/src/checker-symbols.do"
        castInputs->push_back(::app_src_checker_types_::primitive(std::string("char")));
    }
#line 495 "/src/checker-symbols.do"
    return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::unionType(castInputs), false)}), result, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
#line 498 "/src/checker-symbols.do"
bool isBuiltinPrintlnCall(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& callee) {
#line 499 "/src/checker-symbols.do"
    {
        auto _case_subject = callee;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
            const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 501 "/src/checker-symbols.do"
            return (((identifier->name == std::string("println")) && (!doof::is_null(identifier->resolvedBinding))) && (identifier->resolvedBinding->kind == std::string("builtin")));
    }
    else {
#line 503 "/src/checker-symbols.do"
            return false;
    }
    }
    doof::unreachable();
}
#line 507 "/src/checker-symbols.do"
std::shared_ptr<::app_src_semantic_::Symbol> symbolFor(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
#line 508 "/src/checker-symbols.do"
    const auto& _iterable_62 = info->symbols;
    for (const auto& symbol : *_iterable_62) {
#line 508 "/src/checker-symbols.do"
        if (symbol->name == name) {
#line 508 "/src/checker-symbols.do"
            return symbol;
        }
    }
#line 509 "/src/checker-symbols.do"
    const auto& _iterable_64 = info->imports;
    for (const auto& imported : *_iterable_64) {
#line 509 "/src/checker-symbols.do"
        if (imported->localName == name) {
#line 509 "/src/checker-symbols.do"
            return imported->symbol;
        }
    }
#line 510 "/src/checker-symbols.do"
    return nullptr;
}
#line 513 "/src/checker-symbols.do"
std::shared_ptr<::app_src_semantic_::Symbol> valueSymbolFor(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
#line 514 "/src/checker-symbols.do"
    const auto& _iterable_66 = info->symbols;
    for (const auto& symbol : *_iterable_66) {
#line 514 "/src/checker-symbols.do"
        if ((symbol->name == name) && isValueSymbol(symbol)) {
#line 514 "/src/checker-symbols.do"
            return symbol;
        }
    }
#line 515 "/src/checker-symbols.do"
    const auto& _iterable_68 = info->imports;
    for (const auto& imported : *_iterable_68) {
#line 516 "/src/checker-symbols.do"
        if ((((imported->localName == name) && !imported->typeOnly) && (!doof::is_null(imported->symbol))) && isValueSymbol(doof::unwrap_optional(imported->symbol))) {
#line 516 "/src/checker-symbols.do"
            return imported->symbol;
        }
    }
#line 518 "/src/checker-symbols.do"
    return nullptr;
}
#line 521 "/src/checker-symbols.do"
std::string valueUseDiagnostic(const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& info, const std::string& name) {
#line 522 "/src/checker-symbols.do"
    const auto& _iterable_70 = info->imports;
    for (const auto& imported : *_iterable_70) {
#line 523 "/src/checker-symbols.do"
        if (imported->localName != name) {
#line 523 "/src/checker-symbols.do"
            continue;
        }
#line 524 "/src/checker-symbols.do"
        if (imported->typeOnly) {
#line 524 "/src/checker-symbols.do"
            return ((std::string("Type-only import '") + name) + std::string("' cannot be used as a value"));
        }
#line 525 "/src/checker-symbols.do"
        if ((!doof::is_null(imported->symbol)) && !isValueSymbol(doof::unwrap_optional(imported->symbol))) {
#line 525 "/src/checker-symbols.do"
            return ((std::string("Type '") + name) + std::string("' cannot be used as a value"));
        }
    }
#line 527 "/src/checker-symbols.do"
    const auto& _iterable_72 = info->symbols;
    for (const auto& symbol : *_iterable_72) {
#line 527 "/src/checker-symbols.do"
        if ((symbol->name == name) && !isValueSymbol(symbol)) {
#line 527 "/src/checker-symbols.do"
            return ((std::string("Type '") + name) + std::string("' cannot be used as a value"));
        }
    }
#line 528 "/src/checker-symbols.do"
    return std::string("");
}
#line 531 "/src/checker-symbols.do"
bool isValueSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 532 "/src/checker-symbols.do"
    return (symbol->kind != std::string("type-alias"));
}
#line 535 "/src/checker-symbols.do"
std::string declaredSymbolName(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 536 "/src/checker-symbols.do"
    return ((symbol->originalName == std::string("")) ? symbol->name : symbol->originalName);
}
#line 539 "/src/checker-symbols.do"
std::variant<std::monostate, std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> declarationFor(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol) {
#line 540 "/src/checker-symbols.do"
    const auto module = ::app_src_checker_interfaces_::findModule(result, symbol->module);
#line 541 "/src/checker-symbols.do"
    if (doof::is_null(module)) {
#line 541 "/src/checker-symbols.do"
        return std::monostate{};
    }
#line 542 "/src/checker-symbols.do"
    const auto declarationName = declaredSymbolName(symbol);
#line 543 "/src/checker-symbols.do"
    const auto& _iterable_74 = module->program->statements;
    for (const auto& statement : *_iterable_74) {
#line 544 "/src/checker-symbols.do"
        if (std::visit([](auto&& _obj) { return _obj->kind; }, statement) == std::string("export-list")) {
#line 544 "/src/checker-symbols.do"
            continue;
        }
#line 545 "/src/checker-symbols.do"
        const auto candidate = symbolName(statement);
#line 546 "/src/checker-symbols.do"
        if (candidate == declarationName) {
#line 546 "/src/checker-symbols.do"
            return doof::optional_value(statement);
        }
    }
#line 548 "/src/checker-symbols.do"
    return std::monostate{};
}
#line 551 "/src/checker-symbols.do"
std::string symbolName(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>& statement) {
#line 552 "/src/checker-symbols.do"
    {
        auto _case_subject = statement;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 553 "/src/checker-symbols.do"
            return class_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject)) {
            const auto& fn = std::get<std::shared_ptr<::app_src_ast_::FunctionDeclaration>>(_case_subject);
#line 554 "/src/checker-symbols.do"
            return fn->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 555 "/src/checker-symbols.do"
            return interface_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 556 "/src/checker-symbols.do"
            return enum_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
            const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 557 "/src/checker-symbols.do"
            return alias->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject)) {
            const auto& const_ = std::get<std::shared_ptr<::app_src_ast_::ConstDeclaration>>(_case_subject);
#line 558 "/src/checker-symbols.do"
            return const_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject)) {
            const auto& readonly_ = std::get<std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>>(_case_subject);
#line 559 "/src/checker-symbols.do"
            return readonly_->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject)) {
            const auto& binding = std::get<std::shared_ptr<::app_src_ast_::ImmutableBinding>>(_case_subject);
#line 560 "/src/checker-symbols.do"
            return binding->name;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject)) {
            const auto& let_ = std::get<std::shared_ptr<::app_src_ast_::LetDeclaration>>(_case_subject);
#line 561 "/src/checker-symbols.do"
            return let_->name;
    }
    else {
#line 562 "/src/checker-symbols.do"
            return std::string("");
    }
    }
    doof::unreachable();
#line 564 "/src/checker-symbols.do"
    return std::string("");
}
#line 1 "<doof-generated>"
}
