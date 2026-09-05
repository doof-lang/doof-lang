#include "src_checker_resolution.hpp"

namespace app_src_checker_resolution_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_interfaces_;
using namespace ::app_src_checker_validation_;
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolveType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (((named->name == std::string("none")) || (named->name == std::string("void"))) || (named->name == std::string("null"))) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                if ((named->name != std::string("none")) && doof::is_null(named->resolvedType)) {
                    ::app_src_checker_common_::deprecatedNoneAlias(state, named->name, named->span, module->path);
                }
                return decorateType(state, annotation, ::app_src_checker_types_::noneType());
            }
            if (named->name == std::string("never")) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::neverType());
            }
            if (named->name == std::string("JsonValue")) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::jsonValueType());
            }
            if (named->name == std::string("JsonObject")) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::jsonObjectType());
            }
            if (named->name == std::string("SourceLocation")) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_symbols_::builtinSourceLocationType()));
            }
            if (named->name == std::string("WeakReferenceError")) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::weakReferenceErrorType()));
            }
            if (named->name == std::string("Range")) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::rangeType());
            }
            if (::app_src_checker_symbols_::hasTypeParam(scope, named->name)) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::typeParameter(named->name, ::app_src_checker_symbols_::typeParamConstraintName(scope, named->name), ::app_src_checker_symbols_::typeParamConstraint(scope, named->name)));
            }
            if (named->name == std::string("Tuple")) {
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> elements = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                const auto& _iterable_2 = named->typeArgs;
                for (const auto& argument : *_iterable_2) {
                    elements->push_back(resolveType(state, argument, module, scope));
                }
                return decorateType(state, annotation, ::app_src_checker_types_::tupleType(elements));
            }
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires two type arguments")), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                const auto key = resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 87), module, scope);
                const auto value = resolveType(state, doof::array_at(named->typeArgs, 1, "src/checker-resolution", 88), module, scope);
                return decorateType(state, annotation, ::app_src_checker_types_::mapType(key, value, (named->name == std::string("ReadonlyMap"))));
            }
            if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires one type argument")), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                const auto element = resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 93), module, scope);
                if (!::app_src_checker_types_::isSupportedHashCollectionType(element)) {
                    ::app_src_checker_common_::typeError(state, ((std::string("Set element type \"") + ::app_src_checker_types_::typeName(element)) + std::string("\" is not supported; set elements must be byte, string, int, long, char, bool, or enum")), std::visit([](auto&& _obj) { return _obj->span; }, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 95)));
                }
                return decorateType(state, annotation, ::app_src_checker_types_::setType(element, (named->name == std::string("ReadonlySet"))));
            }
            if (named->name == std::string("Stream")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, std::string("Stream requires one type argument"), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::streamType(resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 101), module, scope)));
            }
            if (named->name == std::string("Actor")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, std::string("Actor requires one type argument"), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                const auto inner = resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 105), module, scope);
                {
                    auto _case_subject = inner;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
                        return decorateType(state, annotation, ::app_src_checker_types_::actorType(class_));
                }
                else {
                        ::app_src_checker_common_::typeError(state, std::string("Actor requires a class type"), named->span);
                        return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                }
                doof::unreachable();
            }
            if (named->name == std::string("Promise")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, std::string("Promise requires one type argument"), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::promiseType(resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 113), module, scope)));
            }
            if (named->name == std::string("Result")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
                    ::app_src_checker_common_::typeError(state, std::string("Result requires two type arguments"), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::resultType(resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 117), module, scope), resolveType(state, doof::array_at(named->typeArgs, 1, "src/checker-resolution", 117), module, scope)));
            }
            if ((named->name == std::string("Success")) || (named->name == std::string("Failure"))) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires one type argument")), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                const auto payload = resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 121), module, scope);
                if (named->name == std::string("Success")) {
                    return decorateType(state, annotation, ::app_src_checker_types_::resultType(payload, ::app_src_checker_types_::unknownType()));
                }
                return decorateType(state, annotation, ::app_src_checker_types_::resultType(::app_src_checker_types_::unknownType(), payload));
            }
            if ((((((((named->name == std::string("byte")) || (named->name == std::string("int"))) || (named->name == std::string("long"))) || (named->name == std::string("float"))) || (named->name == std::string("double"))) || (named->name == std::string("string"))) || (named->name == std::string("char"))) || (named->name == std::string("bool"))) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::primitive(named->name));
            }
            std::shared_ptr<::app_src_semantic_::Symbol> symbol = named->resolvedSymbol;
            if (doof::is_null(symbol)) {
                (symbol = ::app_src_checker_symbols_::symbolFor(module, named->name));
            }
            if (doof::is_null(symbol)) {
                ::app_src_checker_common_::typeError(state, ((std::string("Unknown type '") + named->name) + std::string("'")), named->span);
                return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
            }
            if (symbol->kind == std::string("type-alias")) {
                const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
                if (doof::is_null(declaration)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
                        const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
                        if (static_cast<int32_t>((named->typeArgs)->size()) != static_cast<int32_t>((alias->typeParams)->size())) {
                            ::app_src_checker_common_::typeError(state, ((((alias->name + std::string(" requires ")) + doof::to_string(static_cast<int32_t>((alias->typeParams)->size()))) + std::string(" type argument")) + ((static_cast<int32_t>((alias->typeParams)->size()) == 1) ? std::string("") : std::string("s"))), named->span);
                            return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                        }
                        const auto aliasScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false, std::nullopt);
                        const auto& _iterable_4 = alias->typeParams;
                        for (const auto& typeParam : *_iterable_4) {
                            aliasScope->typeParams->push_back(typeParam);
                        }
                        auto resolvedAlias = resolveType(state, alias->type_, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), aliasScope);
                        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                        const auto& _iterable_6 = named->typeArgs;
                        for (const auto& argument : *_iterable_6) {
                            typeArgs->push_back(resolveType(state, argument, module, scope));
                        }
                        validateTypeArgumentConstraints(state, alias->typeParams, alias->typeParamConstraints, typeArgs, named->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
                        (resolvedAlias = ::app_src_checker_types_::substituteTypeParams(resolvedAlias, alias->typeParams, typeArgs));
                        return decorateType(state, annotation, resolvedAlias);
                }
                else {
                        return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                }
                doof::unreachable();
            }
            if (symbol->kind == std::string("interface")) {
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                const auto& _iterable_8 = named->typeArgs;
                for (const auto& argument : *_iterable_8) {
                    typeArgs->push_back(resolveType(state, argument, module, scope));
                }
                const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
                if (!doof::is_null(declaration)) {
                    {
                        auto _case_subject = doof::unwrap_optional(declaration);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                            const auto& interfaceDeclaration = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                            if (!validateNominalTypeArity(state, interfaceDeclaration->name, static_cast<int32_t>((interfaceDeclaration->typeParams)->size()), static_cast<int32_t>((typeArgs)->size()), named->span)) {
                                return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                            }
                            validateTypeArgumentConstraints(state, interfaceDeclaration->typeParams, interfaceDeclaration->typeParamConstraints, typeArgs, named->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
                    }
                    else {
                    }
                    }
                }
                const auto concreteInterface = ::app_src_checker_types_::interfaceType(::app_src_checker_symbols_::declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol), typeArgs);
                if (::app_src_checker_interfaces_::concreteTypes(typeArgs)) {
                    ::app_src_checker_interfaces_::registerConcreteInterfaceImplementations(state->result, concreteInterface);
                }
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(concreteInterface));
            }
            if (symbol->kind == std::string("enum")) {
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::enumType(::app_src_checker_symbols_::declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol))));
            }
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
            const auto& _iterable_10 = named->typeArgs;
            for (const auto& argument : *_iterable_10) {
                typeArgs->push_back(resolveType(state, argument, module, scope));
            }
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
            if (!doof::is_null(declaration)) {
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                        if (!validateNominalTypeArity(state, classDeclaration->name, static_cast<int32_t>((classDeclaration->typeParams)->size()), static_cast<int32_t>((typeArgs)->size()), named->span)) {
                            return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                        }
                        validateTypeArgumentConstraints(state, classDeclaration->typeParams, classDeclaration->typeParamConstraints, typeArgs, named->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
                }
                else {
                        ::app_src_checker_common_::typeError(state, ((std::string("Symbol '") + named->name) + std::string("' is not a type")), named->span);
                        return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                }
            } else if ((symbol->kind != std::string("class")) && (symbol->kind != std::string("struct"))) {
                ::app_src_checker_common_::typeError(state, ((std::string("Symbol '") + named->name) + std::string("' is not a type")), named->span);
                return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
            }
            return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::classType(::app_src_checker_symbols_::declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol), typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            return decorateType(state, annotation, ::app_src_checker_types_::arrayType(resolveType(state, array->elementType, module, scope), array->readonly_));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> members = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
            const auto& _iterable_12 = union_->types;
            for (const auto& item : *_iterable_12) {
                members->push_back(resolveType(state, item, module, scope));
            }
            return decorateType(state, annotation, ::app_src_checker_types_::unionType(members));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
            std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
            const auto& _iterable_14 = function_->params;
            for (const auto& parameter : *_iterable_14) {
                params->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, resolveType(state, parameter->type_, module, scope), false));
            }
            return decorateType(state, annotation, ::app_src_checker_types_::functionType(params, resolveType(state, function_->returnType, module, scope), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
            const auto inner = resolveType(state, weak_->type_, module, scope);
            if (!::app_src_checker_types_::isWeakReferenceTarget(inner)) {
                ::app_src_checker_common_::typeError(state, ((std::string("Type \"") + ::app_src_checker_types_::typeName(inner)) + std::string("\" is not a valid weak reference target")), weak_->span);
            }
            return decorateType(state, annotation, ::app_src_checker_types_::weakType(inner));
    }
    }
    doof::unreachable();
    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
}
bool rejectUnexpectedTypeArguments(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::NamedType>& named, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
    if (static_cast<int32_t>((named->typeArgs)->size()) == 0) {
        return false;
    }
    const auto& _iterable_16 = named->typeArgs;
    for (const auto& argument : *_iterable_16) {
        resolveType(state, argument, module, scope);
    }
    ::app_src_checker_common_::typeError(state, (named->name + std::string(" does not accept type arguments")), named->span);
    return true;
}
bool validateNominalTypeArity(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& name, int32_t expected, int32_t actual, ::app_src_ast_::SourceSpan span) {
    if (expected == actual) {
        return true;
    }
    ::app_src_checker_common_::typeError(state, ((((((name + std::string(" requires ")) + doof::to_string(expected)) + std::string(" type argument")) + ((expected == 1) ? std::string("") : std::string("s"))) + std::string("; received ")) + doof::to_string(actual)), span);
    return false;
}
void validateTypeArgumentConstraints(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& constraints, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments, ::app_src_ast_::SourceSpan span, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module, const std::shared_ptr<::app_src_semantic_::Scope>& outer) {
    if (static_cast<int32_t>((names)->size()) != static_cast<int32_t>((arguments)->size())) {
        return;
    }
    const auto constraintScope = std::make_shared<::app_src_semantic_::Scope>(outer, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false, std::nullopt);
    const auto& _iterable_18 = names;
    for (const auto& name : *_iterable_18) {
        constraintScope->typeParams->push_back(name);
        constraintScope->typeParamConstraintNames->push_back(std::string(""));
        constraintScope->typeParamConstraints->push_back(std::make_shared<::app_src_semantic_::ResolvedTypeConstraint>(std::monostate{}));
    }
    for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
        if ((index >= static_cast<int32_t>((constraints)->size())) || doof::is_null(doof::array_at(constraints, index, "src/checker-resolution", 244)->type_)) {
            continue;
        }
        {
            auto _case_subject = doof::array_at(arguments, index, "src/checker-resolution", 245);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
                if (doof::is_null(parameter->constraint) && (parameter->constraintName == std::string(""))) {
                    continue;
                }
        }
        else {
        }
        }
        const auto annotation = doof::unwrap_optional(doof::array_at(constraints, index, "src/checker-resolution", 249)->type_);
        {
            auto _case_subject = annotation;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && (named->name == std::string("Reflectable"))) {
                    {
                        auto _case_subject = doof::array_at(arguments, index, "src/checker-resolution", 253);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            memberType(state, doof::array_at(arguments, index, "src/checker-resolution", 254), std::string("metadata"), span, true);
                    }
                    else {
                            reportConstraintViolation(state, doof::array_at(names, index, "src/checker-resolution", 255), doof::array_at(arguments, index, "src/checker-resolution", 255), std::string("Reflectable"), span);
                    }
                    }
                    continue;
                }
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && (named->name == std::string("JsonSerializable"))) {
                    const auto result = memberType(state, doof::array_at(arguments, index, "src/checker-resolution", 260), std::string("fromJsonValue"), span, true);
                    if (std::visit([](auto&& _obj) { return _obj->kind; }, result) == std::string("unknown")) {
                        reportConstraintViolation(state, doof::array_at(names, index, "src/checker-resolution", 261), doof::array_at(arguments, index, "src/checker-resolution", 261), std::string("JsonSerializable"), span);
                    }
                    continue;
                }
        }
        else {
        }
        }
        const auto resolvedConstraint = resolveType(state, annotation, module, constraintScope);
        const auto substitutedConstraint = ::app_src_checker_types_::substituteTypeParams(resolvedConstraint, names, arguments);
        if (!::app_src_checker_interfaces_::isAssignableWithInterfaces(state->result, doof::array_at(arguments, index, "src/checker-resolution", 269), substitutedConstraint)) {
            reportConstraintViolation(state, doof::array_at(names, index, "src/checker-resolution", 270), doof::array_at(arguments, index, "src/checker-resolution", 270), ::app_src_checker_types_::typeName(substitutedConstraint), span);
        }
    }
}
void reportConstraintViolation(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& typeParam, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& argument, const std::string& constraint, ::app_src_ast_::SourceSpan span) {
    ::app_src_checker_common_::typeError(state, ((((((std::string("Type \"") + ::app_src_checker_types_::typeName(argument)) + std::string("\" does not satisfy constraint \"")) + constraint) + std::string("\" for type parameter \"")) + typeParam) + std::string("\"")), span);
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> decorateType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType) {
    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, annotation) = ::app_src_checker_symbols_::optionalResolvedType(resolvedType));
    return resolvedType;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> memberType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& object, const std::string& property, ::app_src_ast_::SourceSpan span, bool validateVisibility) {
    if (::app_src_checker_types_::typeName(object) == std::string("string")) {
        if (property == std::string("length")) {
            return ::app_src_checker_types_::primitive(std::string("int"));
        }
        if (((property == std::string("startsWith")) || (property == std::string("endsWith"))) || (property == std::string("contains"))) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("indexOf")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::primitive(std::string("int")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("substring")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("start"), ::app_src_checker_types_::primitive(std::string("int")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("end"), ::app_src_checker_types_::primitive(std::string("int")), true)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("replaceAll")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("oldValue"), ::app_src_checker_types_::primitive(std::string("string")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("newValue"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("trim")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("trimStart")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("trimEnd")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("suffix"), ::app_src_checker_types_::primitive(std::string("char")), true)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if ((property == std::string("toLowerCase")) || (property == std::string("toUpperCase"))) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("repeat")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("count"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("slice")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("start"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("charAt")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("index"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::primitive(std::string("char")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if ((property == std::string("padStart")) || (property == std::string("padEnd"))) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("length"), ::app_src_checker_types_::primitive(std::string("int")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("fill"), ::app_src_checker_types_::primitive(std::string("char")), true)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("split")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("separator"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::arrayType(::app_src_checker_types_::primitive(std::string("string")), true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
    }
    {
        auto _case_subject = object;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            if (property == std::string("call")) {
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(function_);
            }
            if (property == std::string("post")) {
                return ::app_src_checker_types_::functionType(function_->params, ::app_src_checker_types_::promiseType(function_->returnType), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("dispatch")) {
                if (std::visit([](auto&& _obj) { return _obj->kind; }, function_->returnType) != std::string("none")) {
                    ::app_src_checker_common_::typeError(state, std::string("Method \"dispatch\" is only available on none-returning callbacks"), span);
                    return ::app_src_checker_types_::unknownType();
                }
                return ::app_src_checker_types_::functionType(function_->params, ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolved = std::monostate{};
            const auto& _iterable_21 = union_->types;
            for (const auto& member : *_iterable_21) {
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
                    continue;
                }
                const auto memberValue = memberType(state, member, property, span, validateVisibility);
                if (std::visit([](auto&& _obj) { return _obj->kind; }, memberValue) == std::string("unknown")) {
                    return ::app_src_checker_types_::unknownType();
                }
                (resolved = doof::optional_value([&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if (doof::is_null(resolved)) { return memberValue; } return ::app_src_checker_types_::joinTypes(doof::unwrap_optional(resolved), memberValue); }()));
            }
            if (!doof::is_null(resolved)) {
                return doof::unwrap_optional(resolved);
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            if (property == std::string("length")) {
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
            if (array->readonly_ && ((((property == std::string("push")) || (property == std::string("reserve"))) || (property == std::string("pop"))) || (property == std::string("takeFirstCompleted")))) {
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly array")), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("push")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("contains")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("indexOf")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("int")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("reserve")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("capacity"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("pop")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::resultType(array->elementType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("takeFirstCompleted")) {
                {
                    auto _case_subject = array->elementType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
                        const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::resultType(promise->valueType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                }
                else {
                        return ::app_src_checker_types_::unknownType();
                }
                }
                doof::unreachable();
            }
            if ((property == std::string("some")) || (property == std::string("every"))) {
                const auto predicate = ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("it"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("predicate"), predicate, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("filter")) {
                const auto predicate = ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("it"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("predicate"), predicate, false)}), ::app_src_checker_types_::arrayType(array->elementType, array->readonly_), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("map")) {
                const auto mapped = ::app_src_checker_types_::typeParameter(std::string("U"), std::string(""), std::monostate{});
                const auto mapper = ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("it"), array->elementType, false)}), mapped, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("mapper"), mapper, false)}), ::app_src_checker_types_::arrayType(mapped, array->readonly_), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("U")}));
            }
            if (property == std::string("slice")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("start"), ::app_src_checker_types_::primitive(std::string("int")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("end"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::arrayType(array->elementType, array->readonly_), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (array->readonly_ && (((property == std::string("buildReadonly")) || (property == std::string("drainToReadonly"))) || (property == std::string("cloneReadonly")))) {
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly array")), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("buildReadonly")) {
                ::app_src_checker_common_::deprecatedBuildReadonly(state, span);
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(array->elementType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if ((property == std::string("drainToReadonly")) || (property == std::string("cloneReadonly"))) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(array->elementType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("cloneMutable")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(array->elementType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            if (property == std::string("size")) {
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
            if (property == std::string("has")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("get")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false)}), ::app_src_checker_types_::resultType(map->valueType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (map->readonly_ && ((property == std::string("set")) || (property == std::string("delete")))) {
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly map")), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("set")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), map->valueType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("delete")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("keys")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(map->keyType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("values")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(map->valueType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (map->readonly_ && (((property == std::string("buildReadonly")) || (property == std::string("drainToReadonly"))) || (property == std::string("cloneReadonly")))) {
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly map")), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("buildReadonly")) {
                ::app_src_checker_common_::deprecatedBuildReadonly(state, span);
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::mapType(map->keyType, map->valueType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if ((property == std::string("drainToReadonly")) || (property == std::string("cloneReadonly"))) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::mapType(map->keyType, map->valueType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("cloneMutable")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::mapType(map->keyType, map->valueType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
            if (property == std::string("size")) {
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
            if (property == std::string("has")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), set->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (set->readonly_ && (property == std::string("add"))) {
                ::app_src_checker_common_::typeError(state, std::string("Method \"add\" is not available on readonly set"), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("add")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), set->elementType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (set->readonly_ && (property == std::string("delete"))) {
                ::app_src_checker_common_::typeError(state, std::string("Method \"delete\" is not available on readonly set"), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("delete")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), set->elementType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("values")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(set->elementType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (set->readonly_ && (((property == std::string("buildReadonly")) || (property == std::string("drainToReadonly"))) || (property == std::string("cloneReadonly")))) {
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly set")), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("buildReadonly")) {
                ::app_src_checker_common_::deprecatedBuildReadonly(state, span);
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::setType(set->elementType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if ((property == std::string("drainToReadonly")) || (property == std::string("cloneReadonly"))) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::setType(set->elementType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("cloneMutable")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::setType(set->elementType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
            if (property == std::string("value")) {
                return result->valueType;
            }
            if (property == std::string("error")) {
                return result->errorType;
            }
            if ((property == std::string("isSuccess")) || (property == std::string("isFailure"))) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("unwrapOr")) {
                if (std::visit([](auto&& _obj) { return _obj->kind; }, result->valueType) == std::string("none")) {
                    ::app_src_checker_common_::typeError(state, std::string("Method \"unwrapOr\" is not available on Result<void, E>"), span);
                    return ::app_src_checker_types_::unknownType();
                }
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("defaultValue"), result->valueType, false)}), result->valueType, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
            if (property == std::string("next")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("value")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), stream->elementType, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
            for (int32_t i = 0; i < static_cast<int32_t>((tuple->elements)->size()); ++i) {
                if (property == (std::string("_") + doof::to_string((i + 1)))) {
                    return doof::array_at(tuple->elements, i, "src/checker-resolution", 426);
                }
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
            if ((property == std::string("lowerBound")) || (property == std::string("upperBound"))) {
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            return memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), property, span, true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
            if (property == std::string("get")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::resultType(promise->valueType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
            if (property == std::string("metadata")) {
                if (parameter->constraintName != std::string("Reflectable")) {
                    ::app_src_checker_common_::typeError(state, ((std::string("Static member \"metadata\" requires type parameter \"") + parameter->name) + std::string("\" to be constrained by Reflectable")), span);
                    return ::app_src_checker_types_::unknownType();
                }
                return ::app_src_checker_types_::classMetadataType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(parameter));
            }
            if (property == std::string("fromJsonValue")) {
                if (parameter->constraintName != std::string("JsonSerializable")) {
                    ::app_src_checker_common_::typeError(state, ((std::string("Static member \"fromJsonValue\" requires type parameter \"") + parameter->name) + std::string("\" to be constrained by JsonSerializable")), span);
                    return ::app_src_checker_types_::unknownType();
                }
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(parameter), ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>>(_case_subject)) {
            const auto& metadata = std::get<std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>>(_case_subject);
            if ((property == std::string("name")) || (property == std::string("description"))) {
                return ::app_src_checker_types_::primitive(std::string("string"));
            }
            if (property == std::string("methods")) {
                return ::app_src_checker_types_::arrayType(::app_src_checker_types_::methodReflectionType(metadata->classType), false);
            }
            if (property == std::string("defs")) {
                return ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{::app_src_checker_types_::jsonValueType(), ::app_src_checker_types_::noneType()}));
            }
            if (property == std::string("invoke")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("instance"), metadata->classType, false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("methodName"), ::app_src_checker_types_::primitive(std::string("string")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("params"), ::app_src_checker_types_::jsonValueType(), false)}), ::app_src_checker_types_::resultType(::app_src_checker_types_::jsonValueType(), ::app_src_checker_types_::jsonValueType()), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>(_case_subject)) {
            const auto& reflection = std::get<std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>(_case_subject);
            if ((property == std::string("name")) || (property == std::string("description"))) {
                return ::app_src_checker_types_::primitive(std::string("string"));
            }
            if ((property == std::string("inputSchema")) || (property == std::string("outputSchema"))) {
                return ::app_src_checker_types_::jsonValueType();
            }
            if (property == std::string("invoke")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("instance"), reflection->classType, false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("params"), ::app_src_checker_types_::jsonValueType(), false)}), ::app_src_checker_types_::resultType(::app_src_checker_types_::jsonValueType(), ::app_src_checker_types_::jsonValueType()), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, enum_->symbol);
            std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> backingType = ::app_src_checker_types_::primitive(std::string("int"));
            if (!doof::is_null(declaration)) {
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                        const auto& enumDeclaration = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
                        if (enumDeclaration->backingKind == std::string("string")) {
                            (backingType = ::app_src_checker_types_::primitive(std::string("string")));
                        }
                }
                else {
                }
                }
            }
            if (property == std::string("name")) {
                return ::app_src_checker_types_::primitive(std::string("string"));
            }
            if (property == std::string("value")) {
                return backingType;
            }
            if (property == std::string("toJsonValue")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::jsonValueType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("values")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("fromName")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{enum_, ::app_src_checker_types_::noneType()})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("fromValue")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), backingType, false)}), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{enum_, ::app_src_checker_types_::noneType()})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("fromJsonValue")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_), ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (!doof::is_null(declaration)) {
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                        const auto& enumDeclaration = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
                        const auto& _iterable_24 = enumDeclaration->variants;
                        for (const auto& variant : *_iterable_24) {
                            if (variant->name == property) {
                                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_);
                            }
                        }
                }
                else {
                }
                }
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            if ((class_->name == std::string("SourceLocation")) && (class_->symbol->module == std::string("<builtin>"))) {
                if ((property == std::string("fileName")) || (property == std::string("functionName"))) {
                    return ::app_src_checker_types_::primitive(std::string("string"));
                }
                if (property == std::string("line")) {
                    return ::app_src_checker_types_::primitive(std::string("int"));
                }
                return ::app_src_checker_types_::unknownType();
            }
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
            if (doof::is_null(declaration)) {
                return ::app_src_checker_types_::unknownType();
            }
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                    if (property == std::string("metadata")) {
                        if (static_cast<int32_t>((classDeclaration->typeParams)->size()) > 0) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Metadata is not available on generic type \"") + classDeclaration->name) + std::string("\"")), span);
                            return ::app_src_checker_types_::unknownType();
                        }
                        if (!::app_src_json_semantics_::canGenerateJsonSerialization(classDeclaration, jsonPrograms(state->result), nullptr) || !::app_src_json_semantics_::canGenerateJsonDeserialization(classDeclaration, jsonPrograms(state->result), nullptr)) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Type \"") + classDeclaration->name) + std::string("\" is not eligible for metadata because it does not support automatic JSON generation")), span);
                            return ::app_src_checker_types_::unknownType();
                        }
                        auto valid = true;
                        const auto& _iterable_28 = classDeclaration->methods;
                        for (const auto& method : *_iterable_28) {
                            if (method->private_ || method->static_) {
                                continue;
                            }
                            const auto& _iterable_26 = method->params;
                            for (const auto& parameter : *_iterable_26) {
                                if ((!doof::is_null(parameter->resolvedType)) && !::app_src_json_semantics_::isGeneratedJsonType(doof::unwrap_optional(parameter->resolvedType), jsonPrograms(state->result), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
                                    ::app_src_checker_common_::typeError(state, ((((std::string("Parameter \"") + parameter->name) + std::string("\" of method \"")) + method->name) + std::string("\" is not JSON-serializable")), parameter->span);
                                    (valid = false);
                                }
                            }
                            if (!doof::is_null(method->resolvedType)) {
                                {
                                    auto _case_subject = doof::unwrap_optional(method->resolvedType);
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                                        const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
                                        auto successType = function_->returnType;
                                        {
                                            auto _case_subject = successType;
                                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                                                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
                                                (successType = result->valueType);
                                        }
                                        else {
                                        }
                                        }
                                        if ((std::visit([](auto&& _obj) { return _obj->kind; }, successType) != std::string("none")) && !::app_src_json_semantics_::isGeneratedJsonType(successType, jsonPrograms(state->result), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
                                            ::app_src_checker_common_::typeError(state, ((std::string("Return type of method \"") + method->name) + std::string("\" is not JSON-serializable")), method->span);
                                            (valid = false);
                                        }
                                }
                                else {
                                }
                                }
                            }
                        }
                        if (!valid) {
                            return ::app_src_checker_types_::unknownType();
                        }
                        (classDeclaration->needsMetadata = true);
                        return ::app_src_checker_types_::classMetadataType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_));
                    }
                    if ((property == std::string("toJsonObject")) && ::app_src_json_semantics_::canGenerateJsonSerialization(classDeclaration, jsonPrograms(state->result), nullptr)) {
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::jsonObjectType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
                    if ((property == std::string("fromJsonValue")) && ::app_src_json_semantics_::canGenerateJsonDeserialization(classDeclaration, jsonPrograms(state->result), nullptr)) {
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(object, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
                    if ((property == std::string("toJsonObject")) || (property == std::string("fromJsonValue"))) {
                        ::app_src_checker_common_::typeError(state, (((std::string("Type \"") + classDeclaration->name) + std::string("\" does not support automatic JSON ")) + ((property == std::string("toJsonObject")) ? std::string("serialization") : std::string("deserialization"))), span);
                        return ::app_src_checker_types_::unknownType();
                    }
                    const auto& _iterable_32 = classDeclaration->fields;
                    for (const auto& field : *_iterable_32) {
                        const auto& _iterable_30 = field->names;
                        for (const auto& name : *_iterable_30) {
                            if (name == property) {
                                const auto fieldType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if ((!doof::is_null(field->resolvedType))) { return doof::unwrap_optional(field->resolvedType); } return [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { if ((!doof::is_null(field->type_))) { return resolveType(state, doof::unwrap_optional(field->type_), doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)); } return ::app_src_checker_types_::unknownType(); }(); }();
                                if ((validateVisibility && field->private_) && (class_->symbol->module != state->info->path)) {
                                    ::app_src_checker_common_::typeError(state, ((((std::string("Field '") + property) + std::string("' is private to module '")) + class_->symbol->module) + std::string("'")), span);
                                }
                                return ::app_src_checker_types_::substituteTypeParams(fieldType, classDeclaration->typeParams, class_->typeArgs);
                            }
                        }
                    }
                    const auto& _iterable_35 = classDeclaration->methods;
                    for (const auto& method : *_iterable_35) {
                        if (method->name == property) {
                            const auto methodType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_33 = method->resolvedType; if (doof::is_null(_coalesce_33)) return ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), state->result); return doof::unwrap_optional(_coalesce_33); }();
                            if ((validateVisibility && method->private_) && (class_->symbol->module != state->info->path)) {
                                ::app_src_checker_common_::typeError(state, ((((std::string("Method '") + property) + std::string("' is private to module '")) + class_->symbol->module) + std::string("'")), span);
                            }
                            return ::app_src_checker_types_::substituteTypeParams(methodType, classDeclaration->typeParams, class_->typeArgs);
                        }
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                    const auto& _iterable_38 = interface_->fields;
                    for (const auto& field : *_iterable_38) {
                        if (field->name == property) {
                            return [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_36 = field->resolvedType; if (doof::is_null(_coalesce_36)) return resolveType(state, field->type_, doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)); return doof::unwrap_optional(_coalesce_36); }();
                        }
                    }
                    const auto& _iterable_41 = interface_->methods;
                    for (const auto& method : *_iterable_41) {
                        if (method->name == property) {
                            return [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_39 = method->resolvedType; if (doof::is_null(_coalesce_39)) return ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), state->result); return doof::unwrap_optional(_coalesce_39); }();
                        }
                    }
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            return object;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interfaceType_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, interfaceType_->symbol);
            if (doof::is_null(declaration)) {
                return ::app_src_checker_types_::unknownType();
            }
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                    if (property == std::string("fromJsonValue")) {
                        if (static_cast<int32_t>((interface_->typeParams)->size()) > 0) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Automatic JSON deserialization is not available on generic interface \"") + interface_->name) + std::string("\"")), span);
                            return ::app_src_checker_types_::unknownType();
                        }
                        if (static_cast<int32_t>((interfaceType_->symbol->implementations)->size()) == 0) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Cannot deserialize interface \"") + interface_->name) + std::string("\": no implementing classes found")), span);
                            return ::app_src_checker_types_::unknownType();
                        }
                        const auto discriminator = ::app_src_json_semantics_::interfaceJsonDiscriminator(interface_, jsonPrograms(state->result), nullptr);
                        if (doof::is_null(discriminator)) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Cannot deserialize interface \"") + interface_->name) + std::string("\": all implementing classes must share a const string field with distinct values (e.g. const kind = \"variant\")")), span);
                            return ::app_src_checker_types_::unknownType();
                        }
                        (interface_->needsJson = true);
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(object, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
                    const auto& _iterable_44 = interface_->fields;
                    for (const auto& field : *_iterable_44) {
                        if (field->name == property) {
                            const auto fieldType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_42 = field->resolvedType; if (doof::is_null(_coalesce_42)) return resolveType(state, field->type_, doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)); return doof::unwrap_optional(_coalesce_42); }();
                            return ::app_src_checker_types_::substituteTypeParams(fieldType, interface_->typeParams, interfaceType_->typeArgs);
                        }
                    }
                    const auto& _iterable_47 = interface_->methods;
                    for (const auto& method : *_iterable_47) {
                        if (method->name == property) {
                            const auto methodType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_45 = method->resolvedType; if (doof::is_null(_coalesce_45)) return ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, interfaceType_->symbol), state->result); return doof::unwrap_optional(_coalesce_45); }();
                            return ::app_src_checker_types_::substituteTypeParams(methodType, interface_->typeParams, interfaceType_->typeArgs);
                        }
                    }
            }
            else {
            }
            }
    }
    else {
    }
    }
    return ::app_src_checker_types_::unknownType();
}
std::shared_ptr<::app_src_semantic_::Binding> fieldAssignmentBinding(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& object, const std::string& property, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& fieldType) {
    {
        auto _case_subject = object;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            return fieldAssignmentBinding(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), property, fieldType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
            if (doof::is_null(declaration)) {
                return nullptr;
            }
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                    const auto& _iterable_51 = classDeclaration->fields;
                    for (const auto& field : *_iterable_51) {
                        const auto& _iterable_49 = field->names;
                        for (const auto& name : *_iterable_49) {
                            if (name == property) {
                                return std::make_shared<::app_src_semantic_::Binding>(name, std::string("field"), fieldType, field->let_, ::app_src_checker_validation_::checkerSemanticSpan(field->span), class_->symbol->module, class_->symbol, std::string(""), (field->readonly_ ? std::string("readonly") : (field->const_ ? std::string("const") : (field->let_ ? std::string("let") : std::string("implicit")))), classDeclaration->name);
                            }
                        }
                    }
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interfaceType_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, interfaceType_->symbol);
            if (doof::is_null(declaration)) {
                return nullptr;
            }
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                    const auto& _iterable_53 = interface_->fields;
                    for (const auto& field : *_iterable_53) {
                        if (field->name == property) {
                            return std::make_shared<::app_src_semantic_::Binding>(property, std::string("field"), fieldType, field->let_, ::app_src_checker_validation_::checkerSemanticSpan(field->span), interfaceType_->symbol->module, interfaceType_->symbol, std::string(""), (field->readonly_ ? std::string("readonly") : (field->let_ ? std::string("let") : std::string("implicit"))), interface_->name);
                        }
                    }
            }
            else {
            }
            }
    }
    else {
    }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> jsonPrograms(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
    const auto& _iterable_55 = result->modules;
    for (const auto& module : *_iterable_55) {
        programs->push_back(module->program);
    }
    return programs;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> indexType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& object, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& index, ::app_src_ast_::SourceSpan span) {
    {
        auto _case_subject = object;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            if (!::app_src_checker_interfaces_::isAssignableWithInterfaces(state->result, index, ::app_src_checker_types_::primitive(std::string("int"))) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
                ::app_src_checker_common_::typeError(state, std::string("Index must be an int"), span);
            }
            return array->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            if (!::app_src_checker_interfaces_::isAssignableWithInterfaces(state->result, index, map->keyType) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
                ::app_src_checker_common_::typeError(state, std::string("Invalid map key type"), span);
            }
            return map->valueType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive_ = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
            if (primitive_->name == std::string("string")) {
                if (!::app_src_checker_interfaces_::isAssignableWithInterfaces(state->result, index, ::app_src_checker_types_::primitive(std::string("int"))) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
                    ::app_src_checker_common_::typeError(state, std::string("Index must be an int"), span);
                }
                return ::app_src_checker_types_::primitive(std::string("char"));
            }
    }
    else {
    }
    }
    return ::app_src_checker_types_::unknownType();
}
}
