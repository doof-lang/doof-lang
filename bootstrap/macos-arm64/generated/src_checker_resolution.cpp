#include "src_checker_resolution.hpp"
#include <cmath>
#include "src_semantic.hpp"
#include "src_analyzer.hpp"
#include "src_ast.hpp"
#include "src_checker_types.hpp"
#include "src_json_semantics.hpp"
#include "src_checker_actor_boundary.hpp"
#include "src_checker_actor_lifecycle.hpp"
#include "src_checker_state.hpp"
#include "src_checker_common.hpp"
#include "src_checker_symbols.hpp"
#include "src_checker_interfaces.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_checker_resolution_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_json_semantics_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_common_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_interfaces_;
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolveType(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::shared_ptr<::app_src_analyzer_::ModuleInfo> module, std::shared_ptr<::app_src_semantic_::Scope> scope) {
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
            if (named->name == std::string("void")) {
                return decorateType(state, annotation, ::app_src_checker_types_::voidType());
            }
            if (named->name == std::string("null")) {
                return decorateType(state, annotation, ::app_src_checker_types_::nullType());
            }
            if (named->name == std::string("JsonValue")) {
                return decorateType(state, annotation, ::app_src_checker_types_::jsonValueType());
            }
            if (named->name == std::string("JsonObject")) {
                return decorateType(state, annotation, ::app_src_checker_types_::jsonObjectType());
            }
            if (named->name == std::string("SourceLocation")) {
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_symbols_::builtinSourceLocationType()));
            }
            if (named->name == std::string("Range")) {
                return decorateType(state, annotation, ::app_src_checker_types_::rangeType());
            }
            if (::app_src_checker_symbols_::hasTypeParam(scope, named->name)) {
                return decorateType(state, annotation, ::app_src_checker_types_::typeParameter(named->name, ::app_src_checker_symbols_::typeParamConstraintName(scope, named->name), ::app_src_checker_symbols_::typeParamConstraint(scope, named->name)));
            }
            if (named->name == std::string("Tuple")) {
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> elements = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                const auto& _iterable_1 = named->typeArgs;
                for (const auto& argument : *_iterable_1) {
                    elements->push_back(resolveType(state, argument, module, scope));
                }
                return decorateType(state, annotation, ::app_src_checker_types_::tupleType(elements));
            }
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires two type arguments")), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                const auto key = resolveType(state, (*named->typeArgs)[0], module, scope);
                const auto value = resolveType(state, (*named->typeArgs)[1], module, scope);
                return decorateType(state, annotation, ::app_src_checker_types_::mapType(key, value, (named->name == std::string("ReadonlyMap"))));
            }
            if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires one type argument")), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                const auto element = resolveType(state, (*named->typeArgs)[0], module, scope);
                if (!::app_src_checker_types_::isSupportedHashCollectionType(element)) {
                    ::app_src_checker_common_::typeError(state, ((std::string("Set element type \"") + ::app_src_checker_types_::typeName(element)) + std::string("\" is not supported; set elements must be byte, string, int, long, char, bool, or enum")), doof::span((*named->typeArgs)[0]));
                }
                return decorateType(state, annotation, ::app_src_checker_types_::setType(element, (named->name == std::string("ReadonlySet"))));
            }
            if (named->name == std::string("Stream")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, std::string("Stream requires one type argument"), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::streamType(resolveType(state, (*named->typeArgs)[0], module, scope)));
            }
            if (named->name == std::string("Actor")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, std::string("Actor requires one type argument"), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                const auto inner = resolveType(state, (*named->typeArgs)[0], module, scope);
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
            }
            if (named->name == std::string("Promise")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, std::string("Promise requires one type argument"), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::promiseType(resolveType(state, (*named->typeArgs)[0], module, scope)));
            }
            if (named->name == std::string("Result")) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
                    ::app_src_checker_common_::typeError(state, std::string("Result requires two type arguments"), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                return decorateType(state, annotation, ::app_src_checker_types_::resultType(resolveType(state, (*named->typeArgs)[0], module, scope), resolveType(state, (*named->typeArgs)[1], module, scope)));
            }
            if ((named->name == std::string("Success")) || (named->name == std::string("Failure"))) {
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires one type argument")), named->span);
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                const auto payload = resolveType(state, (*named->typeArgs)[0], module, scope);
                if (named->name == std::string("Success")) {
                    return decorateType(state, annotation, ::app_src_checker_types_::resultType(payload, ::app_src_checker_types_::unknownType()));
                }
                return decorateType(state, annotation, ::app_src_checker_types_::resultType(::app_src_checker_types_::unknownType(), payload));
            }
            if ((((((((named->name == std::string("byte")) || (named->name == std::string("int"))) || (named->name == std::string("long"))) || (named->name == std::string("float"))) || (named->name == std::string("double"))) || (named->name == std::string("string"))) || (named->name == std::string("char"))) || (named->name == std::string("bool"))) {
                return decorateType(state, annotation, ::app_src_checker_types_::primitive(named->name));
            }
            std::shared_ptr<::app_src_semantic_::Symbol> symbol = named->resolvedSymbol;
            if (doof::is_null(symbol)) {
                (symbol = ::app_src_checker_symbols_::symbolFor(module, named->name));
            }
            if (doof::is_null(symbol)) {
                return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
            }
            if (doof::kind(symbol) == std::string("type-alias")) {
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
                        const auto aliasScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
                        const auto& _iterable_2 = alias->typeParams;
                        for (const auto& typeParam : *_iterable_2) {
                            aliasScope->typeParams->push_back(typeParam);
                        }
                        auto resolvedAlias = resolveType(state, alias->type_, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), aliasScope);
                        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                        const auto& _iterable_3 = named->typeArgs;
                        for (const auto& argument : *_iterable_3) {
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
            }
            if (doof::kind(symbol) == std::string("interface")) {
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
                const auto& _iterable_4 = named->typeArgs;
                for (const auto& argument : *_iterable_4) {
                    typeArgs->push_back(resolveType(state, argument, module, scope));
                }
                const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
                if (!doof::is_null(declaration)) {
                    {
                        auto _case_subject = doof::unwrap_optional(declaration);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                            const auto& interfaceDeclaration = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                            validateTypeArgumentConstraints(state, interfaceDeclaration->typeParams, interfaceDeclaration->typeParamConstraints, typeArgs, named->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
                    }
                    else {
                    }
                    }
                }
                const auto concreteInterface = ::app_src_checker_types_::interfaceType(named->name, doof::unwrap_optional(symbol), typeArgs);
                if (::app_src_checker_interfaces_::concreteTypes(typeArgs)) {
                    ::app_src_checker_interfaces_::registerConcreteInterfaceImplementations(state->result, concreteInterface);
                }
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(concreteInterface));
            }
            if (doof::kind(symbol) == std::string("enum")) {
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::enumType(named->name, doof::unwrap_optional(symbol))));
            }
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
            const auto& _iterable_5 = named->typeArgs;
            for (const auto& argument : *_iterable_5) {
                typeArgs->push_back(resolveType(state, argument, module, scope));
            }
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
            if (!doof::is_null(declaration)) {
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
                        validateTypeArgumentConstraints(state, classDeclaration->typeParams, classDeclaration->typeParamConstraints, typeArgs, named->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
                }
                else {
                }
                }
            }
            return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::classType(named->name, doof::unwrap_optional(symbol), typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
            return decorateType(state, annotation, ::app_src_checker_types_::arrayType(resolveType(state, array->elementType, module, scope), array->readonly_));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> members = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
            const auto& _iterable_6 = union_->types;
            for (const auto& item : *_iterable_6) {
                members->push_back(resolveType(state, item, module, scope));
            }
            return decorateType(state, annotation, ::app_src_checker_types_::unionType(members));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
            std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
            const auto& _iterable_7 = function_->params;
            for (const auto& parameter : *_iterable_7) {
                params->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, resolveType(state, parameter->type_, module, scope), false));
            }
            return decorateType(state, annotation, ::app_src_checker_types_::functionType(params, resolveType(state, function_->returnType, module, scope), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
            return decorateType(state, annotation, ::app_src_checker_types_::weakType(resolveType(state, weak_->type_, module, scope)));
    }
    }
    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
}
void validateTypeArgumentConstraints(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments, ::app_src_ast_::SourceSpan span, std::shared_ptr<::app_src_analyzer_::ModuleInfo> module, std::shared_ptr<::app_src_semantic_::Scope> outer) {
    if (static_cast<int32_t>((names)->size()) != static_cast<int32_t>((arguments)->size())) {
        return;
    }
    const auto constraintScope = std::make_shared<::app_src_semantic_::Scope>(outer, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}));
    const auto& _iterable_8 = names;
    for (const auto& name : *_iterable_8) {
        constraintScope->typeParams->push_back(name);
        constraintScope->typeParamConstraintNames->push_back(std::string(""));
        constraintScope->typeParamConstraints->push_back(std::make_shared<::app_src_semantic_::ResolvedTypeConstraint>(std::monostate{}));
    }
    for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
        if ((index >= static_cast<int32_t>((constraints)->size())) || doof::is_null((*constraints)[index]->type_)) {
            continue;
        }
        {
            auto _case_subject = (*arguments)[index];
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
                if (doof::is_null(parameter->constraint) && (parameter->constraintName == std::string(""))) {
                    continue;
                }
        }
        else {
        }
        }
        const auto annotation = doof::unwrap_optional((*constraints)[index]->type_);
        {
            auto _case_subject = annotation;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && (named->name == std::string("Reflectable"))) {
                    {
                        auto _case_subject = (*arguments)[index];
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                            memberType(state, (*arguments)[index], std::string("metadata"), span);
                    }
                    else {
                            reportConstraintViolation(state, (*names)[index], (*arguments)[index], std::string("Reflectable"), span);
                    }
                    }
                    continue;
                }
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && (named->name == std::string("JsonSerializable"))) {
                    const auto result = memberType(state, (*arguments)[index], std::string("fromJsonValue"), span);
                    if (doof::kind(result) == std::string("unknown")) {
                        reportConstraintViolation(state, (*names)[index], (*arguments)[index], std::string("JsonSerializable"), span);
                    }
                    continue;
                }
        }
        else {
        }
        }
        const auto resolvedConstraint = resolveType(state, annotation, module, constraintScope);
        const auto substitutedConstraint = ::app_src_checker_types_::substituteTypeParams(resolvedConstraint, names, arguments);
        if (!::app_src_checker_types_::isAssignable((*arguments)[index], substitutedConstraint)) {
            reportConstraintViolation(state, (*names)[index], (*arguments)[index], ::app_src_checker_types_::typeName(substitutedConstraint), span);
        }
    }
}
void reportConstraintViolation(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::string typeParam, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> argument, std::string constraint, ::app_src_ast_::SourceSpan span) {
    ::app_src_checker_common_::typeError(state, ((((((std::string("Type \"") + ::app_src_checker_types_::typeName(argument)) + std::string("\" does not satisfy constraint \"")) + constraint) + std::string("\" for type parameter \"")) + typeParam) + std::string("\"")), span);
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> decorateType(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType) {
    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, annotation) = ::app_src_checker_symbols_::optionalResolvedType(resolvedType));
    return resolvedType;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> memberType(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> object, std::string property, ::app_src_ast_::SourceSpan span) {
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
        if (property == std::string("padStart")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("length"), ::app_src_checker_types_::primitive(std::string("int")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("fill"), ::app_src_checker_types_::primitive(std::string("char")), true)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        if (property == std::string("split")) {
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("separator"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::arrayType(::app_src_checker_types_::primitive(std::string("string")), false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
    }
    {
        auto _case_subject = object;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
            if (property == std::string("call")) {
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(function_);
            }
            if (property == std::string("post")) {
                return ::app_src_checker_types_::functionType(function_->params, ::app_src_checker_types_::promiseType(function_->returnType), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("dispatch")) {
                if (doof::kind(function_->returnType) != std::string("void")) {
                    ::app_src_checker_common_::typeError(state, std::string("Method \"dispatch\" is only available on void-returning callbacks"), span);
                    return ::app_src_checker_types_::unknownType();
                }
                return ::app_src_checker_types_::functionType(function_->params, ::app_src_checker_types_::voidType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolved = std::monostate{};
            const auto& _iterable_9 = union_->types;
            for (const auto& member : *_iterable_9) {
                const auto memberValue = memberType(state, member, property, span);
                if (doof::kind(memberValue) == std::string("unknown")) {
                    continue;
                }
                (resolved = doof::optional_value((doof::is_null(resolved) ? memberValue : ::app_src_checker_types_::joinTypes(doof::unwrap_optional(resolved), memberValue))));
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
            if (property == std::string("push")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::voidType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("contains")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("indexOf")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("int")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("reserve")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("capacity"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::voidType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("pop")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::resultType(array->elementType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
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
            if (property == std::string("buildReadonly")) {
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
            if (property == std::string("set")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), map->valueType, false)}), ::app_src_checker_types_::voidType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("keys")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(map->keyType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("values")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(map->valueType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("buildReadonly")) {
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
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), set->elementType, false)}), ::app_src_checker_types_::voidType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (set->readonly_ && (property == std::string("delete"))) {
                ::app_src_checker_common_::typeError(state, std::string("Method \"delete\" is not available on readonly set"), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("delete")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), set->elementType, false)}), ::app_src_checker_types_::voidType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("values")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(set->elementType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (set->readonly_ && (property == std::string("buildReadonly"))) {
                ::app_src_checker_common_::typeError(state, std::string("Method \"buildReadonly\" is not available on readonly set"), span);
                return ::app_src_checker_types_::unknownType();
            }
            if (property == std::string("buildReadonly")) {
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
                if (doof::kind(result->valueType) == std::string("void")) {
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
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
            if ((property == std::string("lowerBound")) || (property == std::string("upperBound"))) {
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
            return memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), property, span);
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
                return ::app_src_checker_types_::classMetadataType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(parameter));
            }
            if (property == std::string("fromJsonValue")) {
                if (parameter->constraintName != std::string("JsonSerializable")) {
                    ::app_src_checker_common_::typeError(state, ((std::string("Static member \"fromJsonValue\" requires type parameter \"") + parameter->name) + std::string("\" to be constrained by JsonSerializable")), span);
                    return ::app_src_checker_types_::unknownType();
                }
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(parameter), ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
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
                return ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{::app_src_checker_types_::jsonValueType(), ::app_src_checker_types_::nullType()}));
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
            if (property == std::string("name")) {
                return ::app_src_checker_types_::primitive(std::string("string"));
            }
            if (property == std::string("value")) {
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
            if (property == std::string("fromName")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{enum_, ::app_src_checker_types_::nullType()})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            if (property == std::string("fromValue")) {
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{enum_, ::app_src_checker_types_::nullType()})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, enum_->symbol);
            if (!doof::is_null(declaration)) {
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                        const auto& enumDeclaration = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
                        const auto& _iterable_10 = enumDeclaration->variants;
                        for (const auto& variant : *_iterable_10) {
                            if (variant->name == property) {
                                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_);
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
                        if (!::app_src_json_semantics_::canGenerateJsonSerialization(classDeclaration, jsonPrograms(state->result)) || !::app_src_json_semantics_::canGenerateJsonDeserialization(classDeclaration, jsonPrograms(state->result))) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Type \"") + classDeclaration->name) + std::string("\" is not eligible for metadata because it does not support automatic JSON generation")), span);
                            return ::app_src_checker_types_::unknownType();
                        }
                        auto valid = true;
                        const auto& _iterable_11 = classDeclaration->methods;
                        for (const auto& method : *_iterable_11) {
                            if (method->private_ || method->static_) {
                                continue;
                            }
                            const auto& _iterable_12 = method->params;
                            for (const auto& parameter : *_iterable_12) {
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
                                        if ((doof::kind(successType) != std::string("void")) && !::app_src_json_semantics_::isGeneratedJsonType(successType, jsonPrograms(state->result), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
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
                        return ::app_src_checker_types_::classMetadataType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_));
                    }
                    if ((property == std::string("toJsonObject")) && ::app_src_json_semantics_::canGenerateJsonSerialization(classDeclaration, jsonPrograms(state->result))) {
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::jsonObjectType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
                    if ((property == std::string("fromJsonValue")) && ::app_src_json_semantics_::canGenerateJsonDeserialization(classDeclaration, jsonPrograms(state->result))) {
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(object, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
                    if ((property == std::string("toJsonObject")) || (property == std::string("fromJsonValue"))) {
                        ::app_src_checker_common_::typeError(state, (((std::string("Type \"") + classDeclaration->name) + std::string("\" does not support automatic JSON ")) + ((property == std::string("toJsonObject")) ? std::string("serialization") : std::string("deserialization"))), span);
                        return ::app_src_checker_types_::unknownType();
                    }
                    const auto& _iterable_13 = classDeclaration->fields;
                    for (const auto& field : *_iterable_13) {
                        const auto& _iterable_14 = field->names;
                        for (const auto& name : *_iterable_14) {
                            if (name == property) {
                                const auto fieldType = ((!doof::is_null(field->resolvedType)) ? doof::unwrap_optional(field->resolvedType) : ((!doof::is_null(field->type_)) ? resolveType(state, doof::unwrap_optional(field->type_), doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)) : ::app_src_checker_types_::unknownType()));
                                return ::app_src_checker_types_::substituteTypeParams(fieldType, classDeclaration->typeParams, class_->typeArgs);
                            }
                        }
                    }
                    const auto& _iterable_15 = classDeclaration->methods;
                    for (const auto& method : *_iterable_15) {
                        if (method->name == property) {
                            const auto methodType = (doof::is_null(method->resolvedType) ? ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), state->result) : doof::unwrap_optional(method->resolvedType));
                            return ::app_src_checker_types_::substituteTypeParams(methodType, classDeclaration->typeParams, class_->typeArgs);
                        }
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
                    const auto& _iterable_16 = interface_->fields;
                    for (const auto& field : *_iterable_16) {
                        if (field->name == property) {
                            return (doof::is_null(field->resolvedType) ? resolveType(state, field->type_, doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)) : doof::unwrap_optional(field->resolvedType));
                        }
                    }
                    const auto& _iterable_17 = interface_->methods;
                    for (const auto& method : *_iterable_17) {
                        if (method->name == property) {
                            return (doof::is_null(method->resolvedType) ? ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), state->result) : doof::unwrap_optional(method->resolvedType));
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
                        const auto discriminator = ::app_src_json_semantics_::interfaceJsonDiscriminator(interface_, jsonPrograms(state->result));
                        if (doof::is_null(discriminator)) {
                            ::app_src_checker_common_::typeError(state, ((std::string("Cannot deserialize interface \"") + interface_->name) + std::string("\": all implementing classes must share a const string field with distinct values (e.g. const kind = \"variant\")")), span);
                            return ::app_src_checker_types_::unknownType();
                        }
                        (interface_->needsJson = true);
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(object, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
                    const auto& _iterable_18 = interface_->fields;
                    for (const auto& field : *_iterable_18) {
                        if (field->name == property) {
                            const auto fieldType = (doof::is_null(field->resolvedType) ? resolveType(state, field->type_, doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)) : doof::unwrap_optional(field->resolvedType));
                            return ::app_src_checker_types_::substituteTypeParams(fieldType, interface_->typeParams, interfaceType_->typeArgs);
                        }
                    }
                    const auto& _iterable_19 = interface_->methods;
                    for (const auto& method : *_iterable_19) {
                        if (method->name == property) {
                            const auto methodType = (doof::is_null(method->resolvedType) ? ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, interfaceType_->symbol), state->result) : doof::unwrap_optional(method->resolvedType));
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
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> jsonPrograms(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
    const auto& _iterable_20 = result->modules;
    for (const auto& module : *_iterable_20) {
        programs->push_back(module->program);
    }
    return programs;
}
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> indexType(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> object, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NullType>, std::shared_ptr<::app_src_semantic_::VoidType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> index, ::app_src_ast_::SourceSpan span) {
    {
        auto _case_subject = object;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
            if (!::app_src_checker_types_::isAssignable(index, ::app_src_checker_types_::primitive(std::string("int"))) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
                ::app_src_checker_common_::typeError(state, std::string("Index must be an int"), span);
            }
            return array->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
            if (!::app_src_checker_types_::isAssignable(index, map->keyType) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
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
                if (!::app_src_checker_types_::isAssignable(index, ::app_src_checker_types_::primitive(std::string("int"))) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
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
