#include "src_emitter_expr_literals.hpp"

namespace app_src_emitter_expr_literals_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
#line 10 "/src/emitter-expr-literals.do"
std::string emitNoneLiteral(const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 11 "/src/emitter-expr-literals.do"
    if (doof::is_null(expected)) {
#line 11 "/src/emitter-expr-literals.do"
        return std::string("nullptr");
    }
#line 12 "/src/emitter-expr-literals.do"
    {
        auto _case_subject = doof::unwrap_optional(expected);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 14 "/src/emitter-expr-literals.do"
            return std::string("nullptr");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 16 "/src/emitter-expr-literals.do"
            return std::string("doof::json_value(nullptr)");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NoneType>>(_case_subject)) {
#line 17 "/src/emitter-expr-literals.do"
            return std::string("std::monostate{}");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
#line 18 "/src/emitter-expr-literals.do"
            return (::app_src_emitter_types_::emitType(doof::unwrap_optional(expected), context->modulePath) + std::string("{}"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 20 "/src/emitter-expr-literals.do"
            auto nonNone = 0;
#line 21 "/src/emitter-expr-literals.do"
            const auto& _iterable_2 = union_->types;
            for (const auto& member : *_iterable_2) {
#line 21 "/src/emitter-expr-literals.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) != std::string("none")) {
#line 21 "/src/emitter-expr-literals.do"
                    (nonNone = (nonNone + 1));
                }
            }
#line 22 "/src/emitter-expr-literals.do"
            if (nonNone == 1) {
#line 23 "/src/emitter-expr-literals.do"
                const auto& _iterable_4 = union_->types;
                for (const auto& member : *_iterable_4) {
#line 24 "/src/emitter-expr-literals.do"
                    {
                        auto _case_subject = member;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
#line 25 "/src/emitter-expr-literals.do"
                            return std::string("std::nullopt");
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 27 "/src/emitter-expr-literals.do"
                            if (class_->symbol->kind == std::string("struct")) {
#line 27 "/src/emitter-expr-literals.do"
                                return std::string("std::nullopt");
                            }
#line 28 "/src/emitter-expr-literals.do"
                            return std::string("nullptr");
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
#line 30 "/src/emitter-expr-literals.do"
                            return std::string("nullptr");
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
#line 31 "/src/emitter-expr-literals.do"
                            return std::string("nullptr");
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
#line 32 "/src/emitter-expr-literals.do"
                            return std::string("nullptr");
                    }
                    else {
                    }
                    }
                }
            }
#line 37 "/src/emitter-expr-literals.do"
            return std::string("std::monostate{}");
    }
    else {
#line 39 "/src/emitter-expr-literals.do"
            return std::string("nullptr");
    }
    }
    doof::unreachable();
#line 41 "/src/emitter-expr-literals.do"
    return std::string("nullptr");
}
#line 44 "/src/emitter-expr-literals.do"
std::string emitChar(char32_t value) {
#line 45 "/src/emitter-expr-literals.do"
    if (value == U'\0') {
#line 45 "/src/emitter-expr-literals.do"
        return std::string("U'\\0'");
    }
#line 46 "/src/emitter-expr-literals.do"
    if (value == U'\\') {
#line 46 "/src/emitter-expr-literals.do"
        return std::string("U'\\\\'");
    }
#line 47 "/src/emitter-expr-literals.do"
    if (value == U'\'') {
#line 47 "/src/emitter-expr-literals.do"
        return std::string("U'\\''");
    }
#line 48 "/src/emitter-expr-literals.do"
    if (value == U'\n') {
#line 48 "/src/emitter-expr-literals.do"
        return std::string("U'\\n'");
    }
#line 49 "/src/emitter-expr-literals.do"
    if (value == U'\r') {
#line 49 "/src/emitter-expr-literals.do"
        return std::string("U'\\r'");
    }
#line 50 "/src/emitter-expr-literals.do"
    if (value == U'\t') {
#line 50 "/src/emitter-expr-literals.do"
        return std::string("U'\\t'");
    }
#line 51 "/src/emitter-expr-literals.do"
    const auto code = static_cast<int32_t>(value);
#line 52 "/src/emitter-expr-literals.do"
    if (code <= 65535) {
#line 53 "/src/emitter-expr-literals.do"
        return (((((std::string("U'\\u") + hexDigit((code / 4096))) + hexDigit(((code / 256) % 16))) + hexDigit(((code / 16) % 16))) + hexDigit((code % 16))) + std::string("'"));
    }
#line 55 "/src/emitter-expr-literals.do"
    return (((((((((std::string("U'\\U") + hexDigit(((code / 268435456) % 16))) + hexDigit(((code / 16777216) % 16))) + hexDigit(((code / 1048576) % 16))) + hexDigit(((code / 65536) % 16))) + hexDigit(((code / 4096) % 16))) + hexDigit(((code / 256) % 16))) + hexDigit(((code / 16) % 16))) + hexDigit((code % 16))) + std::string("'"));
}
#line 58 "/src/emitter-expr-literals.do"
std::string hexDigit(int32_t value) {
#line 59 "/src/emitter-expr-literals.do"
    const auto digits = std::string("0123456789ABCDEF");
#line 60 "/src/emitter-expr-literals.do"
    return doof::string_substring(digits, value, (value + 1));
}
#line 63 "/src/emitter-expr-literals.do"
std::string emitArray(const std::shared_ptr<::app_src_ast_::ArrayLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 64 "/src/emitter-expr-literals.do"
    const auto arrayType = expression->resolvedType;
#line 65 "/src/emitter-expr-literals.do"
    if (!doof::is_null(arrayType)) {
#line 66 "/src/emitter-expr-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(arrayType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 68 "/src/emitter-expr-literals.do"
                const auto elementType = ::app_src_emitter_types_::emitType(array->elementType, context->modulePath);
#line 69 "/src/emitter-expr-literals.do"
                auto values = std::string("");
#line 70 "/src/emitter-expr-literals.do"
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
#line 71 "/src/emitter-expr-literals.do"
                    if (i > 0) {
#line 71 "/src/emitter-expr-literals.do"
                        (values = (values + std::string(", ")));
                    }
#line 72 "/src/emitter-expr-literals.do"
                    (values = (values + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->elements, i, "src/emitter-expr-literals", 72), context, std::monostate{})));
                }
#line 74 "/src/emitter-expr-literals.do"
                return ((((((std::string("std::make_shared<std::vector<") + elementType) + std::string(">>(std::vector<")) + elementType) + std::string(">{")) + values) + std::string("})"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 77 "/src/emitter-expr-literals.do"
                const auto elementType = ::app_src_emitter_types_::emitType(set_->elementType, context->modulePath);
#line 78 "/src/emitter-expr-literals.do"
                auto values = std::string("");
#line 79 "/src/emitter-expr-literals.do"
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
#line 80 "/src/emitter-expr-literals.do"
                    if (i > 0) {
#line 80 "/src/emitter-expr-literals.do"
                        (values = (values + std::string(", ")));
                    }
#line 81 "/src/emitter-expr-literals.do"
                    (values = (values + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->elements, i, "src/emitter-expr-literals", 81), context, std::monostate{})));
                }
#line 83 "/src/emitter-expr-literals.do"
                return ((((((std::string("std::make_shared<doof::ordered_set<") + elementType) + std::string(">>(doof::ordered_set<")) + elementType) + std::string(">{")) + values) + std::string("})"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 86 "/src/emitter-expr-literals.do"
                auto values = std::string("");
#line 87 "/src/emitter-expr-literals.do"
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
#line 88 "/src/emitter-expr-literals.do"
                    if (i > 0) {
#line 88 "/src/emitter-expr-literals.do"
                        (values = (values + std::string(", ")));
                    }
#line 89 "/src/emitter-expr-literals.do"
                    (values = (((values + std::string("doof::json_value(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->elements, i, "src/emitter-expr-literals", 89), context, std::monostate{})) + std::string(")")));
                }
#line 91 "/src/emitter-expr-literals.do"
                return ((std::string("doof::json_value(std::make_shared<std::vector<doof::JsonValue>>(std::initializer_list<doof::JsonValue>{") + values) + std::string("}))"));
        }
        else {
        }
        }
    }
#line 96 "/src/emitter-expr-literals.do"
    doof::panic((((std::string("Array literal has no checked array type in ") + context->modulePath) + std::string("::")) + context->currentFunctionName));
#line 97 "/src/emitter-expr-literals.do"
    return std::string("nullptr");
}
#line 100 "/src/emitter-expr-literals.do"
std::string emitObject(const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
#line 101 "/src/emitter-expr-literals.do"
    if (!doof::is_null(expression->resolvedType)) {
#line 102 "/src/emitter-expr-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 103 "/src/emitter-expr-literals.do"
                return emitClassObject(expression, context, class_);
        }
        else {
        }
        }
    }
#line 107 "/src/emitter-expr-literals.do"
    if (!doof::is_null(expected)) {
#line 108 "/src/emitter-expr-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 110 "/src/emitter-expr-literals.do"
                const auto value = ::app_src_emitter_expr_utils_::findProperty(expression->properties, std::string("value"));
#line 111 "/src/emitter-expr-literals.do"
                const auto error = ::app_src_emitter_expr_utils_::findProperty(expression->properties, std::string("error"));
#line 112 "/src/emitter-expr-literals.do"
                if (!doof::is_null(value)) {
#line 113 "/src/emitter-expr-literals.do"
                    const auto emitted = (doof::is_null(value->value) ? ::app_src_emitter_expr_::cppIdentifier(value->name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(value->value), context, doof::optional_value(result->valueType)));
#line 114 "/src/emitter-expr-literals.do"
                    return ((((std::string("doof::Success<") + ::app_src_emitter_types_::emitResultPayloadType(result->valueType, context->modulePath)) + std::string(">{ ")) + emitted) + std::string(" }"));
                }
#line 116 "/src/emitter-expr-literals.do"
                if (!doof::is_null(error)) {
#line 117 "/src/emitter-expr-literals.do"
                    const auto emitted = (doof::is_null(error->value) ? ::app_src_emitter_expr_::cppIdentifier(error->name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(error->value), context, doof::optional_value(result->errorType)));
#line 118 "/src/emitter-expr-literals.do"
                    return ((((std::string("doof::Failure<") + ::app_src_emitter_types_::emitResultPayloadType(result->errorType, context->modulePath)) + std::string(">{ ")) + emitted) + std::string(" }"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 121 "/src/emitter-expr-literals.do"
                return emitClassObject(expression, context, class_);
        }
        else {
        }
        }
    }
#line 125 "/src/emitter-expr-literals.do"
    if (!doof::is_null(expected)) {
#line 126 "/src/emitter-expr-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 127 "/src/emitter-expr-literals.do"
                return emitMapObject(expression, context, map);
        }
        else {
        }
        }
    }
#line 131 "/src/emitter-expr-literals.do"
    auto values = std::string("");
#line 132 "/src/emitter-expr-literals.do"
    auto first = true;
#line 133 "/src/emitter-expr-literals.do"
    const auto& _iterable_9 = expression->properties;
    for (const auto& property : *_iterable_9) {
#line 134 "/src/emitter-expr-literals.do"
        if (!first) {
#line 134 "/src/emitter-expr-literals.do"
            (values = (values + std::string(", ")));
        }
#line 135 "/src/emitter-expr-literals.do"
        (first = false);
#line 136 "/src/emitter-expr-literals.do"
        const auto key = quote(property->name);
#line 137 "/src/emitter-expr-literals.do"
        const auto value = (doof::is_null(property->value) ? std::string("doof::json_value(nullptr)") : ((std::string("doof::json_value(") + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->value), context, std::monostate{})) + std::string(")")));
#line 138 "/src/emitter-expr-literals.do"
        (values = (((((values + std::string("{")) + key) + std::string(", ")) + value) + std::string("}")));
    }
#line 140 "/src/emitter-expr-literals.do"
    if (!doof::is_null(expected)) {
#line 141 "/src/emitter-expr-literals.do"
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
#line 142 "/src/emitter-expr-literals.do"
                return ((std::string("doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{") + values) + std::string("}))"));
        }
        else {
        }
        }
    }
#line 146 "/src/emitter-expr-literals.do"
    return ((std::string("doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{") + values) + std::string("}))"));
}
#line 149 "/src/emitter-expr-literals.do"
std::string emitClassObject(const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::ClassType>& resolved) {
#line 150 "/src/emitter-expr-literals.do"
    const auto class_ = expression->resolvedClass;
#line 151 "/src/emitter-expr-literals.do"
    if (doof::is_null(class_)) {
#line 151 "/src/emitter-expr-literals.do"
        doof::panic((std::string("Object literal has no resolved class in ") + context->modulePath));
    }
#line 152 "/src/emitter-expr-literals.do"
    auto cppName = ::app_src_emitter_expr_utils_::emittedSymbolName(resolved->symbol);
#line 153 "/src/emitter-expr-literals.do"
    if ((resolved->symbol->module != std::string("")) && (resolved->symbol->module != context->modulePath)) {
#line 153 "/src/emitter-expr-literals.do"
        (cppName = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(resolved->symbol->module)) + std::string("::")) + cppName));
    }
#line 154 "/src/emitter-expr-literals.do"
    auto values = std::string("");
#line 155 "/src/emitter-expr-literals.do"
    auto first = true;
#line 156 "/src/emitter-expr-literals.do"
    const auto& _iterable_11 = class_->fields;
    for (const auto& field : *_iterable_11) {
#line 157 "/src/emitter-expr-literals.do"
        if (field->static_) {
#line 157 "/src/emitter-expr-literals.do"
            continue;
        }
#line 158 "/src/emitter-expr-literals.do"
        const auto& _iterable_13 = field->names;
        for (const auto& name : *_iterable_13) {
#line 159 "/src/emitter-expr-literals.do"
            if (!first) {
#line 159 "/src/emitter-expr-literals.do"
                (values = (values + std::string(", ")));
            }
#line 160 "/src/emitter-expr-literals.do"
            (first = false);
#line 161 "/src/emitter-expr-literals.do"
            const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->properties, name);
#line 162 "/src/emitter-expr-literals.do"
            auto value = std::string("{}");
#line 163 "/src/emitter-expr-literals.do"
            if (!doof::is_null(property)) {
#line 164 "/src/emitter-expr-literals.do"
                (value = (doof::is_null(property->value) ? ::app_src_emitter_expr_::cppIdentifier(name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->value), context, field->resolvedType)));
#line 165 "/src/emitter-expr-literals.do"
                if (doof::is_null(property->value) && ::app_src_emitter_expr_utils_::needsNullableVariantPromotion(property->resolvedType, field->resolvedType)) {
#line 165 "/src/emitter-expr-literals.do"
                    (value = ::app_src_emitter_expr_utils_::emitNullableVariantPromotion(value, property->resolvedType, field->resolvedType, context->modulePath));
                }
            } else if (!doof::is_null(field->defaultValue)) {
#line 167 "/src/emitter-expr-literals.do"
                (value = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType));
            }
#line 169 "/src/emitter-expr-literals.do"
            (values = (values + value));
        }
    }
#line 172 "/src/emitter-expr-literals.do"
    if (resolved->symbol->kind == std::string("struct")) {
#line 172 "/src/emitter-expr-literals.do"
        return (((cppName + std::string("{")) + values) + std::string("}"));
    }
#line 173 "/src/emitter-expr-literals.do"
    return ((((std::string("std::make_shared<") + cppName) + std::string(">(")) + values) + std::string(")"));
}
#line 176 "/src/emitter-expr-literals.do"
std::string emitMapObject(const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::MapResolvedType>& map) {
#line 177 "/src/emitter-expr-literals.do"
    auto values = std::string("");
#line 178 "/src/emitter-expr-literals.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->properties)->size()); ++i) {
#line 179 "/src/emitter-expr-literals.do"
        if (i > 0) {
#line 179 "/src/emitter-expr-literals.do"
            (values = (values + std::string(", ")));
        }
#line 180 "/src/emitter-expr-literals.do"
        const auto property = doof::array_at(expression->properties, i, "src/emitter-expr-literals", 180);
#line 181 "/src/emitter-expr-literals.do"
        const auto value = (doof::is_null(property->value) ? std::string("{}") : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->value), context, doof::optional_value(map->valueType)));
#line 182 "/src/emitter-expr-literals.do"
        const auto key = (doof::is_null(property->key) ? quote(property->name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->key), context, doof::optional_value(map->keyType)));
#line 183 "/src/emitter-expr-literals.do"
        (values = (((((values + std::string("{")) + key) + std::string(", ")) + value) + std::string("}")));
    }
#line 185 "/src/emitter-expr-literals.do"
    const auto keyType = ::app_src_emitter_types_::emitType(map->keyType, context->modulePath);
#line 186 "/src/emitter-expr-literals.do"
    const auto valueType = ::app_src_emitter_types_::emitType(map->valueType, context->modulePath);
#line 187 "/src/emitter-expr-literals.do"
    return ((((((((((std::string("std::make_shared<doof::ordered_map<") + keyType) + std::string(", ")) + valueType) + std::string(">>(std::initializer_list<std::pair<")) + keyType) + std::string(", ")) + valueType) + std::string(">>{")) + values) + std::string("})"));
}
#line 190 "/src/emitter-expr-literals.do"
std::string emitTuple(const std::shared_ptr<::app_src_ast_::TupleLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 191 "/src/emitter-expr-literals.do"
    auto values = std::string("");
#line 192 "/src/emitter-expr-literals.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
#line 193 "/src/emitter-expr-literals.do"
        if (i > 0) {
#line 193 "/src/emitter-expr-literals.do"
            (values = (values + std::string(", ")));
        }
#line 194 "/src/emitter-expr-literals.do"
        (values = (values + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->elements, i, "src/emitter-expr-literals", 194), context, std::monostate{})));
    }
#line 196 "/src/emitter-expr-literals.do"
    return ((std::string("std::make_tuple(") + values) + std::string(")"));
}
#line 199 "/src/emitter-expr-literals.do"
std::string emitString(const std::shared_ptr<::app_src_ast_::StringLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
#line 200 "/src/emitter-expr-literals.do"
    if (static_cast<int32_t>((expression->interpolations)->size()) == 0) {
#line 200 "/src/emitter-expr-literals.do"
        return ((std::string("std::string(") + quote(doof::array_at(expression->parts, 0, "src/emitter-expr-literals", 200))) + std::string(")"));
    }
#line 201 "/src/emitter-expr-literals.do"
    auto result = ((std::string("([&]() -> std::string { std::string _interpolation = ") + quote(doof::array_at(expression->parts, 0, "src/emitter-expr-literals", 201))) + std::string("; "));
#line 202 "/src/emitter-expr-literals.do"
    for (int32_t i = 0; i < static_cast<int32_t>((expression->interpolations)->size()); ++i) {
#line 203 "/src/emitter-expr-literals.do"
        (result = (((result + std::string("_interpolation += doof::to_string(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->interpolations, i, "src/emitter-expr-literals", 203), context, std::monostate{})) + std::string("); ")));
#line 204 "/src/emitter-expr-literals.do"
        const auto partIndex = ((i * 2) + 2);
#line 205 "/src/emitter-expr-literals.do"
        if (partIndex < static_cast<int32_t>((expression->parts)->size())) {
#line 205 "/src/emitter-expr-literals.do"
            (result = (((result + std::string("_interpolation += ")) + quote(doof::array_at(expression->parts, partIndex, "src/emitter-expr-literals", 205))) + std::string("; ")));
        }
    }
#line 207 "/src/emitter-expr-literals.do"
    return (result + std::string("return _interpolation; }())"));
}
#line 210 "/src/emitter-expr-literals.do"
std::string quote(const std::string& value) {
#line 211 "/src/emitter-expr-literals.do"
    const auto escaped = doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\"")), std::string("\?"), std::string("\\\?")), std::string("\n"), std::string("\\n")), std::string("\r"), std::string("\\r")), std::string("\t"), std::string("\\t"));
#line 213 "/src/emitter-expr-literals.do"
    return ((std::string("\"") + escaped) + std::string("\""));
}
#line 1 "<doof-generated>"
}
