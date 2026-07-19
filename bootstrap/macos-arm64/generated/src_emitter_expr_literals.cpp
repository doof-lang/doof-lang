#include "src_emitter_expr_literals.hpp"
#include <cmath>
#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_expr_utils.hpp"
#include "src_emitter_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_expr_literals_ {
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
std::string emitNullLiteral(std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected) {
    if (doof::is_null(expected)) {
        return std::string("nullptr");
    }
    {
        auto _case_subject = doof::unwrap_optional(expected);
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if (((class_->name == std::string("Expression")) || (class_->name == std::string("Statement"))) || (class_->name == std::string("TypeAnnotation"))) {
                return std::string("std::monostate{}");
            }
            return std::string("nullptr");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
            return std::string("doof::json_value(nullptr)");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NullType>>(_case_subject)) {
            return std::string("std::monostate{}");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            auto nonNull = 0;
            const auto& _iterable_1 = union_->types;
            for (const auto& member : *_iterable_1) {
                if (doof::kind(member) != std::string("null")) {
                    (nonNull = (nonNull + 1));
                }
            }
            if (nonNull == 1) {
                const auto& _iterable_2 = union_->types;
                for (const auto& member : *_iterable_2) {
                    {
                        auto _case_subject = member;
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
                            return std::string("std::nullopt");
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                            if (((class_->name == std::string("Expression")) || (class_->name == std::string("Statement"))) || (class_->name == std::string("TypeAnnotation"))) {
                                return std::string("std::monostate{}");
                            }
                            if (class_->symbol->kind == std::string("struct")) {
                                return std::string("std::nullopt");
                            }
                            return std::string("nullptr");
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                            return std::string("nullptr");
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                            return std::string("nullptr");
                    }
                    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                            return std::string("nullptr");
                    }
                    else {
                    }
                    }
                }
            }
            return std::string("std::monostate{}");
    }
    else {
            return std::string("nullptr");
    }
    }
    return std::string("nullptr");
}
std::string emitChar(char32_t value) {
    if (value == U'\0') {
        return std::string("U'\\0'");
    }
    if (value == U'\\') {
        return std::string("U'\\\\'");
    }
    if (value == U'\'') {
        return std::string("U'\\''");
    }
    if (value == U'\n') {
        return std::string("U'\\n'");
    }
    if (value == U'\r') {
        return std::string("U'\\r'");
    }
    if (value == U'\t') {
        return std::string("U'\\t'");
    }
    const auto code = static_cast<int32_t>(value);
    if (code <= 65535) {
        return (((((std::string("U'\\u") + hexDigit((code / 4096))) + hexDigit(((code / 256) % 16))) + hexDigit(((code / 16) % 16))) + hexDigit((code % 16))) + std::string("'"));
    }
    return (((((((((std::string("U'\\U") + hexDigit(((code / 268435456) % 16))) + hexDigit(((code / 16777216) % 16))) + hexDigit(((code / 1048576) % 16))) + hexDigit(((code / 65536) % 16))) + hexDigit(((code / 4096) % 16))) + hexDigit(((code / 256) % 16))) + hexDigit(((code / 16) % 16))) + hexDigit((code % 16))) + std::string("'"));
}
std::string hexDigit(int32_t value) {
    const auto digits = std::string("0123456789ABCDEF");
    return doof::string_substring(digits, value, (value + 1));
}
std::string emitArray(std::shared_ptr<::app_src_ast_::ArrayLiteral> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected) {
    const auto arrayType = expression->resolvedType;
    if (!doof::is_null(arrayType)) {
        {
            auto _case_subject = doof::unwrap_optional(arrayType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
                const auto elementType = ::app_src_emitter_types_::emitType(array->elementType, context->modulePath);
                auto values = std::string("");
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
                    if (i > 0) {
                        (values = (values + std::string(", ")));
                    }
                    (values = (values + ::app_src_emitter_expr_::emitExpression((*expression->elements)[i], context, std::monostate{})));
                }
                return ((((((std::string("std::make_shared<std::vector<") + elementType) + std::string(">>(std::vector<")) + elementType) + std::string(">{")) + values) + std::string("})"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
                const auto elementType = ::app_src_emitter_types_::emitType(set_->elementType, context->modulePath);
                auto values = std::string("");
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
                    if (i > 0) {
                        (values = (values + std::string(", ")));
                    }
                    (values = (values + ::app_src_emitter_expr_::emitExpression((*expression->elements)[i], context, std::monostate{})));
                }
                return ((((((std::string("std::make_shared<doof::ordered_set<") + elementType) + std::string(">>(doof::ordered_set<")) + elementType) + std::string(">{")) + values) + std::string("})"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                auto values = std::string("");
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
                    if (i > 0) {
                        (values = (values + std::string(", ")));
                    }
                    (values = (((values + std::string("doof::json_value(")) + ::app_src_emitter_expr_::emitExpression((*expression->elements)[i], context, std::monostate{})) + std::string(")")));
                }
                return ((std::string("doof::json_value(std::make_shared<std::vector<doof::JsonValue>>(std::initializer_list<doof::JsonValue>{") + values) + std::string("}))"));
        }
        else {
        }
        }
    }
    doof::panic((((std::string("Array literal has no checked array type in ") + context->modulePath) + std::string("::")) + context->currentFunctionName));
    return std::string("nullptr");
}
std::string emitObject(std::shared_ptr<::app_src_ast_::ObjectLiteral> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> expected) {
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                const auto value = ::app_src_emitter_expr_utils_::findProperty(expression->properties, std::string("value"));
                const auto error = ::app_src_emitter_expr_utils_::findProperty(expression->properties, std::string("error"));
                if (!doof::is_null(value)) {
                    const auto emitted = (doof::is_null(value->value) ? ::app_src_emitter_expr_::cppIdentifier(value->name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(value->value), context, doof::optional_value(result->valueType)));
                    return ((((std::string("doof::Success<") + ::app_src_emitter_types_::emitType(result->valueType, context->modulePath)) + std::string(">{ ")) + emitted) + std::string(" }"));
                }
                if (!doof::is_null(error)) {
                    const auto emitted = (doof::is_null(error->value) ? ::app_src_emitter_expr_::cppIdentifier(error->name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(error->value), context, doof::optional_value(result->errorType)));
                    return ((((std::string("doof::Failure<") + ::app_src_emitter_types_::emitType(result->errorType, context->modulePath)) + std::string(">{ ")) + emitted) + std::string(" }"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                return emitClassObject(expression, context, class_);
        }
        else {
        }
        }
    }
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
                const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
                return emitMapObject(expression, context, map);
        }
        else {
        }
        }
    }
    auto values = std::string("");
    auto first = true;
    const auto& _iterable_3 = expression->properties;
    for (const auto& property : *_iterable_3) {
        if (!first) {
            (values = (values + std::string(", ")));
        }
        (first = false);
        const auto key = quote(property->name);
        const auto value = (doof::is_null(property->value) ? std::string("doof::json_value(nullptr)") : ((std::string("doof::json_value(") + ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->value), context, std::monostate{})) + std::string(")")));
        (values = (((((values + std::string("{")) + key) + std::string(", ")) + value) + std::string("}")));
    }
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                return ((std::string("doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{") + values) + std::string("}))"));
        }
        else {
        }
        }
    }
    return ((std::string("doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{") + values) + std::string("}))"));
}
std::string emitClassObject(std::shared_ptr<::app_src_ast_::ObjectLiteral> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_semantic_::ClassType> resolved) {
    const auto class_ = expression->resolvedClass;
    if (doof::is_null(class_)) {
        doof::panic((std::string("Object literal has no resolved class in ") + context->modulePath));
    }
    auto cppName = ::app_src_emitter_expr_utils_::emittedSymbolName(resolved->symbol);
    if ((resolved->symbol->module != std::string("")) && (resolved->symbol->module != context->modulePath)) {
        (cppName = (((std::string("::") + ::app_src_emitter_expr_utils_::exprModuleNamespaceFor(resolved->symbol->module)) + std::string("::")) + cppName));
    }
    auto values = std::string("");
    auto first = true;
    const auto& _iterable_4 = class_->fields;
    for (const auto& field : *_iterable_4) {
        if (field->static_) {
            continue;
        }
        const auto& _iterable_5 = field->names;
        for (const auto& name : *_iterable_5) {
            if (!first) {
                (values = (values + std::string(", ")));
            }
            (first = false);
            const auto property = ::app_src_emitter_expr_utils_::findProperty(expression->properties, name);
            auto value = std::string("{}");
            if (!doof::is_null(property)) {
                (value = (doof::is_null(property->value) ? ::app_src_emitter_expr_::cppIdentifier(name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->value), context, field->resolvedType)));
                if (doof::is_null(property->value) && ::app_src_emitter_expr_utils_::needsNullableVariantPromotion(doof::resolved_type(property), field->resolvedType)) {
                    (value = ::app_src_emitter_expr_utils_::emitNullableVariantPromotion(value, doof::resolved_type(property), field->resolvedType, context->modulePath));
                }
            } else if (!doof::is_null(field->defaultValue)) {
                (value = ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(field->defaultValue), context, field->resolvedType));
            }
            (values = (values + value));
        }
    }
    if (resolved->symbol->kind == std::string("struct")) {
        return (((cppName + std::string("{")) + values) + std::string("}"));
    }
    return ((((std::string("std::make_shared<") + cppName) + std::string(">(")) + values) + std::string(")"));
}
std::string emitMapObject(std::shared_ptr<::app_src_ast_::ObjectLiteral> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context, std::shared_ptr<::app_src_semantic_::MapResolvedType> map) {
    auto values = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((expression->properties)->size()); ++i) {
        if (i > 0) {
            (values = (values + std::string(", ")));
        }
        const auto property = (*expression->properties)[i];
        const auto value = (doof::is_null(property->value) ? std::string("{}") : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->value), context, doof::optional_value(map->valueType)));
        const auto key = (doof::is_null(property->key) ? quote(property->name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->key), context, doof::optional_value(map->keyType)));
        (values = (((((values + std::string("{")) + key) + std::string(", ")) + value) + std::string("}")));
    }
    const auto keyType = ::app_src_emitter_types_::emitType(map->keyType, context->modulePath);
    const auto valueType = ::app_src_emitter_types_::emitType(map->valueType, context->modulePath);
    return ((((((((((std::string("std::make_shared<doof::ordered_map<") + keyType) + std::string(", ")) + valueType) + std::string(">>(std::initializer_list<std::pair<")) + keyType) + std::string(", ")) + valueType) + std::string(">>{")) + values) + std::string("})"));
}
std::string emitTuple(std::shared_ptr<::app_src_ast_::TupleLiteral> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    auto values = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
        if (i > 0) {
            (values = (values + std::string(", ")));
        }
        (values = (values + ::app_src_emitter_expr_::emitExpression((*expression->elements)[i], context, std::monostate{})));
    }
    return ((std::string("std::make_tuple(") + values) + std::string(")"));
}
std::string emitString(std::shared_ptr<::app_src_ast_::StringLiteral> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context) {
    if (static_cast<int32_t>((expression->interpolations)->size()) == 0) {
        return ((std::string("std::string(") + quote((*expression->parts)[0])) + std::string(")"));
    }
    auto result = ((std::string("std::string(") + quote((*expression->parts)[0])) + std::string(")"));
    for (int32_t i = 0; i < static_cast<int32_t>((expression->interpolations)->size()); ++i) {
        (result = (((result + std::string(" + doof::to_string(")) + ::app_src_emitter_expr_::emitExpression((*expression->interpolations)[i], context, std::monostate{})) + std::string(")")));
        const auto partIndex = ((i * 2) + 2);
        if (partIndex < static_cast<int32_t>((expression->parts)->size())) {
            (result = (((result + std::string(" + std::string(")) + quote((*expression->parts)[partIndex])) + std::string(")")));
        }
    }
    return result;
}
std::string quote(std::string value) {
    const auto escaped = doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\"")), std::string("\n"), std::string("\\n")), std::string("\r"), std::string("\\r")), std::string("\t"), std::string("\\t"));
    return ((std::string("\"") + escaped) + std::string("\""));
}
}
