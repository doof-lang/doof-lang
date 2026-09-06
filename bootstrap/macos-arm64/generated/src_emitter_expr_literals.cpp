#include "src_emitter_expr_literals.hpp"

namespace app_src_emitter_expr_literals_ {
using namespace ::app_src_emitter_carrier_values_;
using namespace ::app_src_emitter_construction_;
using namespace ::app_src_ast_;
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_expr_;
using namespace ::app_src_emitter_expr_utils_;
using namespace ::app_src_emitter_types_;
std::string emitNoneLiteral(const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (doof::is_null(expected)) {
        doof::panic((std::string("None literal has no checked type in ") + context->modulePath));
    }
    return ::app_src_emitter_carrier_values_::emitCarrierAbsence(doof::unwrap_optional(expected), context);
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
std::string emitArray(const std::shared_ptr<::app_src_ast_::ArrayLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    const auto arrayType = expression->resolvedType;
    if (!doof::is_null(arrayType)) {
        {
            auto _case_subject = doof::unwrap_optional(arrayType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
                const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
                const auto elementType = ::app_src_emitter_types_::emitContextType(array->elementType, context);
                auto values = std::string("");
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
                    if (i > 0) {
                        static_cast<void>((values = (values + std::string(", "))));
                    }
                    static_cast<void>((values = (values + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->elements, i, "src/emitter-expr-literals", 45), context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(array->elementType)))));
                }
                return ((((((std::string("std::make_shared<std::vector<") + elementType) + std::string(">>(std::vector<")) + elementType) + std::string(">{")) + values) + std::string("})"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
                const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
                const auto elementType = ::app_src_emitter_types_::emitContextType(set_->elementType, context);
                auto values = std::string("");
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
                    if (i > 0) {
                        static_cast<void>((values = (values + std::string(", "))));
                    }
                    static_cast<void>((values = (values + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->elements, i, "src/emitter-expr-literals", 54), context, std::monostate{}))));
                }
                return ((((((std::string("std::make_shared<doof::ordered_set<") + elementType) + std::string(">>(doof::ordered_set<")) + elementType) + std::string(">{")) + values) + std::string("})"));
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>>(_case_subject)) {
                auto values = std::string("");
                for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
                    if (i > 0) {
                        static_cast<void>((values = (values + std::string(", "))));
                    }
                    static_cast<void>((values = (((values + std::string("doof::json_value(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->elements, i, "src/emitter-expr-literals", 62), context, std::monostate{})) + std::string(")"))));
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
std::string emitObject(const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& expected) {
    if (!doof::is_null(expression->resolvedType)) {
        {
            auto _case_subject = doof::unwrap_optional(expression->resolvedType);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                return ::app_src_emitter_construction_::emitClassObject(expression, context, class_);
        }
        else {
        }
        }
    }
    if (!doof::is_null(expected)) {
        {
            auto _case_subject = doof::unwrap_optional(expected);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                const auto value = ::app_src_emitter_expr_utils_::findProperty(expression->properties, std::string("value"));
                const auto error = ::app_src_emitter_expr_utils_::findProperty(expression->properties, std::string("error"));
                if (!doof::is_null(value)) {
                    const auto emitted = ::app_src_emitter_expr_utils_::emitPropertyValue(doof::unwrap_optional(value), context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result->valueType));
                    return ((((std::string("doof::Success<") + ::app_src_emitter_types_::emitContextReturnType(result->valueType, context)) + std::string(">{ ")) + emitted) + std::string(" }"));
                }
                if (!doof::is_null(error)) {
                    const auto emitted = ::app_src_emitter_expr_utils_::emitPropertyValue(doof::unwrap_optional(error), context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(result->errorType));
                    return ((((std::string("doof::Failure<") + ::app_src_emitter_types_::emitContextReturnType(result->errorType, context)) + std::string(">{ ")) + emitted) + std::string(" }"));
                }
        }
        else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                return ::app_src_emitter_construction_::emitClassObject(expression, context, class_);
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
    const auto& _iterable_5 = expression->properties;
    for (const auto& property : *_iterable_5) {
        if (!first) {
            static_cast<void>((values = (values + std::string(", "))));
        }
        static_cast<void>((first = false));
        const auto key = quote(property->name);
        const auto value = ((std::string("doof::json_value(") + ::app_src_emitter_expr_utils_::emitPropertyValue(property, context, std::monostate{})) + std::string(")"));
        static_cast<void>((values = (((((values + std::string("{")) + key) + std::string(", ")) + value) + std::string("}"))));
    }
    return ((std::string("doof::json_value(std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{") + values) + std::string("}))"));
}
std::string emitMapObject(const std::shared_ptr<::app_src_ast_::ObjectLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::shared_ptr<::app_src_semantic_::MapResolvedType>& map) {
    auto values = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((expression->properties)->size()); ++i) {
        if (i > 0) {
            static_cast<void>((values = (values + std::string(", "))));
        }
        const auto property = doof::array_at(expression->properties, i, "src/emitter-expr-literals", 120);
        const auto value = ::app_src_emitter_expr_utils_::emitPropertyValue(property, context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(map->valueType));
        const auto key = (doof::is_null(property->key) ? quote(property->name) : ::app_src_emitter_expr_::emitExpression(doof::unwrap_optional(property->key), context, doof::variant_promote<std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(map->keyType)));
        static_cast<void>((values = (((((values + std::string("{")) + key) + std::string(", ")) + value) + std::string("}"))));
    }
    const auto keyType = ::app_src_emitter_types_::emitContextType(map->keyType, context);
    const auto valueType = ::app_src_emitter_types_::emitContextType(map->valueType, context);
    return ((((((((((std::string("std::make_shared<doof::ordered_map<") + keyType) + std::string(", ")) + valueType) + std::string(">>(std::initializer_list<std::pair<")) + keyType) + std::string(", ")) + valueType) + std::string(">>{")) + values) + std::string("})"));
}
std::string emitTuple(const std::shared_ptr<::app_src_ast_::TupleLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    auto values = std::string("");
    for (int32_t i = 0; i < static_cast<int32_t>((expression->elements)->size()); ++i) {
        if (i > 0) {
            static_cast<void>((values = (values + std::string(", "))));
        }
        static_cast<void>((values = (values + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->elements, i, "src/emitter-expr-literals", 134), context, std::monostate{}))));
    }
    return ((std::string("std::make_tuple(") + values) + std::string(")"));
}
std::string emitString(const std::shared_ptr<::app_src_ast_::StringLiteral>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    if (static_cast<int32_t>((expression->interpolations)->size()) == 0) {
        return emitStringConstant(doof::array_at(expression->parts, 0, "src/emitter-expr-literals", 140));
    }
    auto result = ((std::string("([&]() -> std::string { std::string _interpolation = ") + emitInterpolationPart(doof::array_at(expression->parts, 0, "src/emitter-expr-literals", 141))) + std::string("; "));
    for (int32_t i = 0; i < static_cast<int32_t>((expression->interpolations)->size()); ++i) {
        static_cast<void>((result = (((result + std::string("_interpolation += doof::to_string(")) + ::app_src_emitter_expr_::emitExpression(doof::array_at(expression->interpolations, i, "src/emitter-expr-literals", 143), context, std::monostate{})) + std::string("); "))));
        const auto partIndex = ((i * 2) + 2);
        if (partIndex < static_cast<int32_t>((expression->parts)->size())) {
            static_cast<void>((result = (((result + std::string("_interpolation += ")) + emitInterpolationPart(doof::array_at(expression->parts, partIndex, "src/emitter-expr-literals", 145))) + std::string("; "))));
        }
    }
    return (result + std::string("return _interpolation; }())"));
}
std::string emitInterpolationPart(const std::string& value) {
    if (doof::string_contains(value, doof::to_string(U'\0'))) {
        return emitStringConstant(value);
    }
    return quote(value);
}
std::string emitStringConstant(const std::string& value) {
    const auto literal = quote(value);
    const auto nul = doof::to_string(U'\0');
    if (doof::string_contains(value, nul)) {
        return ((((std::string("std::string(") + literal) + std::string(", ")) + doof::to_string(static_cast<int32_t>(value.size()))) + std::string(")"));
    }
    return ((std::string("std::string(") + literal) + std::string(")"));
}
std::string quote(const std::string& value) {
    const auto nul = doof::to_string(U'\0');
    const auto escaped = doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(value, std::string("\\"), std::string("\\\\")), std::string("\""), std::string("\\\"")), std::string("\?"), std::string("\\\?")), std::string("\n"), std::string("\\n")), std::string("\r"), std::string("\\r")), std::string("\t"), std::string("\\t")), nul, std::string("\\000"));
    return ((std::string("\"") + escaped) + std::string("\""));
}
}
