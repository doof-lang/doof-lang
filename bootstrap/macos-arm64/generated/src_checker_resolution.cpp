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
#line 44 "/src/checker-resolution.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolveType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 45 "/src/checker-resolution.do"
    {
        auto _case_subject = annotation;
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
            const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 47 "/src/checker-resolution.do"
            if (((named->name == std::string("none")) || (named->name == std::string("void"))) || (named->name == std::string("null"))) {
#line 48 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 48 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 49 "/src/checker-resolution.do"
                if ((named->name != std::string("none")) && doof::is_null(named->resolvedType)) {
#line 49 "/src/checker-resolution.do"
                    ::app_src_checker_common_::deprecatedNoneAlias(state, named->name, named->span, module->path);
                }
#line 50 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::noneType());
            }
#line 52 "/src/checker-resolution.do"
            if (named->name == std::string("never")) {
#line 53 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 53 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 54 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::neverType());
            }
#line 56 "/src/checker-resolution.do"
            if (named->name == std::string("JsonValue")) {
#line 57 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 57 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 58 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::jsonValueType());
            }
#line 60 "/src/checker-resolution.do"
            if (named->name == std::string("JsonObject")) {
#line 61 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 61 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 62 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::jsonObjectType());
            }
#line 64 "/src/checker-resolution.do"
            if (named->name == std::string("SourceLocation")) {
#line 65 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 65 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 66 "/src/checker-resolution.do"
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_symbols_::builtinSourceLocationType()));
            }
#line 68 "/src/checker-resolution.do"
            if (named->name == std::string("WeakReferenceError")) {
#line 69 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 69 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 70 "/src/checker-resolution.do"
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::weakReferenceErrorType()));
            }
#line 72 "/src/checker-resolution.do"
            if (named->name == std::string("Range")) {
#line 73 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 73 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 74 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::rangeType());
            }
#line 76 "/src/checker-resolution.do"
            if (::app_src_checker_symbols_::hasTypeParam(scope, named->name)) {
#line 77 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 77 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 78 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::typeParameter(named->name, ::app_src_checker_symbols_::typeParamConstraintName(scope, named->name), ::app_src_checker_symbols_::typeParamConstraint(scope, named->name)));
            }
#line 80 "/src/checker-resolution.do"
            if (named->name == std::string("Tuple")) {
#line 81 "/src/checker-resolution.do"
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> elements = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 82 "/src/checker-resolution.do"
                const auto& _iterable_2 = named->typeArgs;
                for (const auto& argument : *_iterable_2) {
#line 82 "/src/checker-resolution.do"
                    elements->push_back(resolveType(state, argument, module, scope));
                }
#line 83 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::tupleType(elements));
            }
#line 85 "/src/checker-resolution.do"
            if ((named->name == std::string("Map")) || (named->name == std::string("ReadonlyMap"))) {
#line 86 "/src/checker-resolution.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
#line 86 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires two type arguments")), named->span);
#line 86 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 87 "/src/checker-resolution.do"
                const auto key = resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 87), module, scope);
#line 88 "/src/checker-resolution.do"
                const auto value = resolveType(state, doof::array_at(named->typeArgs, 1, "src/checker-resolution", 88), module, scope);
#line 89 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::mapType(key, value, (named->name == std::string("ReadonlyMap"))));
            }
#line 91 "/src/checker-resolution.do"
            if ((named->name == std::string("Set")) || (named->name == std::string("ReadonlySet"))) {
#line 92 "/src/checker-resolution.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
#line 92 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires one type argument")), named->span);
#line 92 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 93 "/src/checker-resolution.do"
                const auto element = resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 93), module, scope);
#line 94 "/src/checker-resolution.do"
                if (!::app_src_checker_types_::isSupportedHashCollectionType(element)) {
#line 95 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, ((std::string("Set element type \"") + ::app_src_checker_types_::typeName(element)) + std::string("\" is not supported; set elements must be byte, string, int, long, char, bool, or enum")), std::visit([](auto&& _obj) { return _obj->span; }, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 95)));
                }
#line 97 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::setType(element, (named->name == std::string("ReadonlySet"))));
            }
#line 99 "/src/checker-resolution.do"
            if (named->name == std::string("Stream")) {
#line 100 "/src/checker-resolution.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
#line 100 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, std::string("Stream requires one type argument"), named->span);
#line 100 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 101 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::streamType(resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 101), module, scope)));
            }
#line 103 "/src/checker-resolution.do"
            if (named->name == std::string("Actor")) {
#line 104 "/src/checker-resolution.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
#line 104 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, std::string("Actor requires one type argument"), named->span);
#line 104 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 105 "/src/checker-resolution.do"
                const auto inner = resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 105), module, scope);
#line 106 "/src/checker-resolution.do"
                {
                    auto _case_subject = inner;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
                        const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 107 "/src/checker-resolution.do"
                        return decorateType(state, annotation, ::app_src_checker_types_::actorType(class_));
                }
                else {
#line 108 "/src/checker-resolution.do"
                        ::app_src_checker_common_::typeError(state, std::string("Actor requires a class type"), named->span);
#line 108 "/src/checker-resolution.do"
                        return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                }
                doof::unreachable();
            }
#line 111 "/src/checker-resolution.do"
            if (named->name == std::string("Promise")) {
#line 112 "/src/checker-resolution.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
#line 112 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, std::string("Promise requires one type argument"), named->span);
#line 112 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 113 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::promiseType(resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 113), module, scope)));
            }
#line 115 "/src/checker-resolution.do"
            if (named->name == std::string("Result")) {
#line 116 "/src/checker-resolution.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 2) {
#line 116 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, std::string("Result requires two type arguments"), named->span);
#line 116 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 117 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::resultType(resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 117), module, scope), resolveType(state, doof::array_at(named->typeArgs, 1, "src/checker-resolution", 117), module, scope)));
            }
#line 119 "/src/checker-resolution.do"
            if ((named->name == std::string("Success")) || (named->name == std::string("Failure"))) {
#line 120 "/src/checker-resolution.do"
                if (static_cast<int32_t>((named->typeArgs)->size()) != 1) {
#line 120 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, (named->name + std::string(" requires one type argument")), named->span);
#line 120 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 121 "/src/checker-resolution.do"
                const auto payload = resolveType(state, doof::array_at(named->typeArgs, 0, "src/checker-resolution", 121), module, scope);
#line 122 "/src/checker-resolution.do"
                if (named->name == std::string("Success")) {
#line 122 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::resultType(payload, ::app_src_checker_types_::unknownType()));
                }
#line 123 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::resultType(::app_src_checker_types_::unknownType(), payload));
            }
#line 125 "/src/checker-resolution.do"
            if ((((((((named->name == std::string("byte")) || (named->name == std::string("int"))) || (named->name == std::string("long"))) || (named->name == std::string("float"))) || (named->name == std::string("double"))) || (named->name == std::string("string"))) || (named->name == std::string("char"))) || (named->name == std::string("bool"))) {
#line 126 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 126 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 127 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::primitive(named->name));
            }
#line 129 "/src/checker-resolution.do"
            std::shared_ptr<::app_src_semantic_::Symbol> symbol = named->resolvedSymbol;
#line 130 "/src/checker-resolution.do"
            if (doof::is_null(symbol)) {
#line 130 "/src/checker-resolution.do"
                (symbol = ::app_src_checker_symbols_::symbolFor(module, named->name));
            }
#line 131 "/src/checker-resolution.do"
            if (doof::is_null(symbol)) {
#line 132 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Unknown type '") + named->name) + std::string("'")), named->span);
#line 133 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
            }
#line 135 "/src/checker-resolution.do"
            if (symbol->kind == std::string("type-alias")) {
#line 136 "/src/checker-resolution.do"
                const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
#line 137 "/src/checker-resolution.do"
                if (doof::is_null(declaration)) {
#line 137 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 138 "/src/checker-resolution.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject)) {
                        const auto& alias = std::get<std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>>(_case_subject);
#line 140 "/src/checker-resolution.do"
                        if (static_cast<int32_t>((named->typeArgs)->size()) != static_cast<int32_t>((alias->typeParams)->size())) {
#line 141 "/src/checker-resolution.do"
                            ::app_src_checker_common_::typeError(state, ((((alias->name + std::string(" requires ")) + doof::to_string(static_cast<int32_t>((alias->typeParams)->size()))) + std::string(" type argument")) + ((static_cast<int32_t>((alias->typeParams)->size()) == 1) ? std::string("") : std::string("s"))), named->span);
#line 142 "/src/checker-resolution.do"
                            return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                        }
#line 144 "/src/checker-resolution.do"
                        const auto aliasScope = std::make_shared<::app_src_semantic_::Scope>(scope, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 145 "/src/checker-resolution.do"
                        const auto& _iterable_4 = alias->typeParams;
                        for (const auto& typeParam : *_iterable_4) {
#line 145 "/src/checker-resolution.do"
                            aliasScope->typeParams->push_back(typeParam);
                        }
#line 146 "/src/checker-resolution.do"
                        auto resolvedAlias = resolveType(state, alias->type_, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), aliasScope);
#line 147 "/src/checker-resolution.do"
                        std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 148 "/src/checker-resolution.do"
                        const auto& _iterable_6 = named->typeArgs;
                        for (const auto& argument : *_iterable_6) {
#line 148 "/src/checker-resolution.do"
                            typeArgs->push_back(resolveType(state, argument, module, scope));
                        }
#line 149 "/src/checker-resolution.do"
                        validateTypeArgumentConstraints(state, alias->typeParams, alias->typeParamConstraints, typeArgs, named->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
#line 150 "/src/checker-resolution.do"
                        (resolvedAlias = ::app_src_checker_types_::substituteTypeParams(resolvedAlias, alias->typeParams, typeArgs));
#line 151 "/src/checker-resolution.do"
                        return decorateType(state, annotation, resolvedAlias);
                }
                else {
#line 153 "/src/checker-resolution.do"
                        return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                }
                doof::unreachable();
            }
#line 156 "/src/checker-resolution.do"
            if (symbol->kind == std::string("interface")) {
#line 157 "/src/checker-resolution.do"
                std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 158 "/src/checker-resolution.do"
                const auto& _iterable_8 = named->typeArgs;
                for (const auto& argument : *_iterable_8) {
#line 158 "/src/checker-resolution.do"
                    typeArgs->push_back(resolveType(state, argument, module, scope));
                }
#line 159 "/src/checker-resolution.do"
                const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
#line 160 "/src/checker-resolution.do"
                if (!doof::is_null(declaration)) {
#line 161 "/src/checker-resolution.do"
                    {
                        auto _case_subject = doof::unwrap_optional(declaration);
                        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                            const auto& interfaceDeclaration = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 163 "/src/checker-resolution.do"
                            if (!validateNominalTypeArity(state, interfaceDeclaration->name, static_cast<int32_t>((interfaceDeclaration->typeParams)->size()), static_cast<int32_t>((typeArgs)->size()), named->span)) {
#line 164 "/src/checker-resolution.do"
                                return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                            }
#line 166 "/src/checker-resolution.do"
                            validateTypeArgumentConstraints(state, interfaceDeclaration->typeParams, interfaceDeclaration->typeParamConstraints, typeArgs, named->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
                    }
                    else {
                    }
                    }
                }
#line 171 "/src/checker-resolution.do"
                const auto concreteInterface = ::app_src_checker_types_::interfaceType(::app_src_checker_symbols_::declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol), typeArgs);
#line 172 "/src/checker-resolution.do"
                if (::app_src_checker_interfaces_::concreteTypes(typeArgs)) {
#line 172 "/src/checker-resolution.do"
                    ::app_src_checker_interfaces_::registerConcreteInterfaceImplementations(state->result, concreteInterface);
                }
#line 173 "/src/checker-resolution.do"
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(concreteInterface));
            }
#line 175 "/src/checker-resolution.do"
            if (symbol->kind == std::string("enum")) {
#line 176 "/src/checker-resolution.do"
                if (rejectUnexpectedTypeArguments(state, named, module, scope)) {
#line 176 "/src/checker-resolution.do"
                    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
#line 177 "/src/checker-resolution.do"
                return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::enumType(::app_src_checker_symbols_::declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol))));
            }
#line 179 "/src/checker-resolution.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> typeArgs = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 180 "/src/checker-resolution.do"
            const auto& _iterable_10 = named->typeArgs;
            for (const auto& argument : *_iterable_10) {
#line 180 "/src/checker-resolution.do"
                typeArgs->push_back(resolveType(state, argument, module, scope));
            }
#line 181 "/src/checker-resolution.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, doof::unwrap_optional(symbol));
#line 182 "/src/checker-resolution.do"
            if (!doof::is_null(declaration)) {
#line 183 "/src/checker-resolution.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                        const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 185 "/src/checker-resolution.do"
                        if (!validateNominalTypeArity(state, classDeclaration->name, static_cast<int32_t>((classDeclaration->typeParams)->size()), static_cast<int32_t>((typeArgs)->size()), named->span)) {
#line 186 "/src/checker-resolution.do"
                            return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                        }
#line 188 "/src/checker-resolution.do"
                        validateTypeArgumentConstraints(state, classDeclaration->typeParams, classDeclaration->typeParamConstraints, typeArgs, named->span, ::app_src_checker_interfaces_::classModuleFor(state->result, doof::unwrap_optional(symbol)), scope);
                }
                else {
#line 191 "/src/checker-resolution.do"
                        ::app_src_checker_common_::typeError(state, ((std::string("Symbol '") + named->name) + std::string("' is not a type")), named->span);
#line 192 "/src/checker-resolution.do"
                        return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
                }
                }
            } else if ((symbol->kind != std::string("class")) && (symbol->kind != std::string("struct"))) {
#line 196 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Symbol '") + named->name) + std::string("' is not a type")), named->span);
#line 197 "/src/checker-resolution.do"
                return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
            }
#line 199 "/src/checker-resolution.do"
            return decorateType(state, annotation, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(::app_src_checker_types_::classType(::app_src_checker_symbols_::declaredSymbolName(doof::unwrap_optional(symbol)), doof::unwrap_optional(symbol), typeArgs)));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_ast_::ArrayType>>(_case_subject);
#line 201 "/src/checker-resolution.do"
            return decorateType(state, annotation, ::app_src_checker_types_::arrayType(resolveType(state, array->elementType, module, scope), array->readonly_));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_ast_::UnionType>>(_case_subject);
#line 203 "/src/checker-resolution.do"
            std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> members = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{});
#line 204 "/src/checker-resolution.do"
            const auto& _iterable_12 = union_->types;
            for (const auto& item : *_iterable_12) {
#line 204 "/src/checker-resolution.do"
                members->push_back(resolveType(state, item, module, scope));
            }
#line 205 "/src/checker-resolution.do"
            return decorateType(state, annotation, ::app_src_checker_types_::unionType(members));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_ast_::AstFunctionType>>(_case_subject);
#line 208 "/src/checker-resolution.do"
            std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>> params = std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{});
#line 209 "/src/checker-resolution.do"
            const auto& _iterable_14 = function_->params;
            for (const auto& parameter : *_iterable_14) {
#line 209 "/src/checker-resolution.do"
                params->push_back(std::make_shared<::app_src_semantic_::FunctionParamType>(parameter->name, resolveType(state, parameter->type_, module, scope), false));
            }
#line 210 "/src/checker-resolution.do"
            return decorateType(state, annotation, ::app_src_checker_types_::functionType(params, resolveType(state, function_->returnType, module, scope), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject)) {
            const auto& weak_ = std::get<std::shared_ptr<::app_src_ast_::WeakType>>(_case_subject);
#line 213 "/src/checker-resolution.do"
            const auto inner = resolveType(state, weak_->type_, module, scope);
#line 214 "/src/checker-resolution.do"
            if (!::app_src_checker_types_::isWeakReferenceTarget(inner)) {
#line 214 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Type \"") + ::app_src_checker_types_::typeName(inner)) + std::string("\" is not a valid weak reference target")), weak_->span);
            }
#line 215 "/src/checker-resolution.do"
            return decorateType(state, annotation, ::app_src_checker_types_::weakType(inner));
    }
    }
    doof::unreachable();
#line 218 "/src/checker-resolution.do"
    return decorateType(state, annotation, ::app_src_checker_types_::unknownType());
}
#line 221 "/src/checker-resolution.do"
bool rejectUnexpectedTypeArguments(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::NamedType>& named, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module, const std::shared_ptr<::app_src_semantic_::Scope>& scope) {
#line 222 "/src/checker-resolution.do"
    if (static_cast<int32_t>((named->typeArgs)->size()) == 0) {
#line 222 "/src/checker-resolution.do"
        return false;
    }
#line 223 "/src/checker-resolution.do"
    const auto& _iterable_16 = named->typeArgs;
    for (const auto& argument : *_iterable_16) {
#line 223 "/src/checker-resolution.do"
        resolveType(state, argument, module, scope);
    }
#line 224 "/src/checker-resolution.do"
    ::app_src_checker_common_::typeError(state, (named->name + std::string(" does not accept type arguments")), named->span);
#line 225 "/src/checker-resolution.do"
    return true;
}
#line 228 "/src/checker-resolution.do"
bool validateNominalTypeArity(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& name, int32_t expected, int32_t actual, ::app_src_ast_::SourceSpan span) {
#line 229 "/src/checker-resolution.do"
    if (expected == actual) {
#line 229 "/src/checker-resolution.do"
        return true;
    }
#line 230 "/src/checker-resolution.do"
    ::app_src_checker_common_::typeError(state, ((((((name + std::string(" requires ")) + doof::to_string(expected)) + std::string(" type argument")) + ((expected == 1) ? std::string("") : std::string("s"))) + std::string("; received ")) + doof::to_string(actual)), span);
#line 231 "/src/checker-resolution.do"
    return false;
}
#line 235 "/src/checker-resolution.do"
void validateTypeArgumentConstraints(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& constraints, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>& arguments, ::app_src_ast_::SourceSpan span, const std::shared_ptr<::app_src_analyzer_::ModuleInfo>& module, const std::shared_ptr<::app_src_semantic_::Scope>& outer) {
#line 236 "/src/checker-resolution.do"
    if (static_cast<int32_t>((names)->size()) != static_cast<int32_t>((arguments)->size())) {
#line 236 "/src/checker-resolution.do"
        return;
    }
#line 237 "/src/checker-resolution.do"
    const auto constraintScope = std::make_shared<::app_src_semantic_::Scope>(outer, std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::Binding>>>(std::vector<std::shared_ptr<::app_src_semantic_::Binding>>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<::app_src_semantic_::ResolvedTypeConstraint>>{}), std::monostate{}, std::monostate{}, std::string(""), false, false, std::monostate{}, false, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{}), false);
#line 238 "/src/checker-resolution.do"
    const auto& _iterable_18 = names;
    for (const auto& name : *_iterable_18) {
#line 239 "/src/checker-resolution.do"
        constraintScope->typeParams->push_back(name);
#line 240 "/src/checker-resolution.do"
        constraintScope->typeParamConstraintNames->push_back(std::string(""));
#line 241 "/src/checker-resolution.do"
        constraintScope->typeParamConstraints->push_back(std::make_shared<::app_src_semantic_::ResolvedTypeConstraint>(std::monostate{}));
    }
#line 243 "/src/checker-resolution.do"
    for (int32_t index = 0; index < static_cast<int32_t>((names)->size()); ++index) {
#line 244 "/src/checker-resolution.do"
        if ((index >= static_cast<int32_t>((constraints)->size())) || doof::is_null(doof::array_at(constraints, index, "src/checker-resolution", 244)->type_)) {
#line 244 "/src/checker-resolution.do"
            continue;
        }
#line 245 "/src/checker-resolution.do"
        {
            auto _case_subject = doof::array_at(arguments, index, "src/checker-resolution", 245);
            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
                const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
#line 246 "/src/checker-resolution.do"
                if (doof::is_null(parameter->constraint) && (parameter->constraintName == std::string(""))) {
#line 246 "/src/checker-resolution.do"
                    continue;
                }
        }
        else {
        }
        }
#line 249 "/src/checker-resolution.do"
        const auto annotation = doof::unwrap_optional(doof::array_at(constraints, index, "src/checker-resolution", 249)->type_);
#line 250 "/src/checker-resolution.do"
        {
            auto _case_subject = annotation;
            if (std::holds_alternative<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject)) {
                const auto& named = std::get<std::shared_ptr<::app_src_ast_::NamedType>>(_case_subject);
#line 252 "/src/checker-resolution.do"
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && (named->name == std::string("Reflectable"))) {
#line 253 "/src/checker-resolution.do"
                    {
                        auto _case_subject = doof::array_at(arguments, index, "src/checker-resolution", 253);
                        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
#line 254 "/src/checker-resolution.do"
                            memberType(state, doof::array_at(arguments, index, "src/checker-resolution", 254), std::string("metadata"), span, true);
                    }
                    else {
#line 255 "/src/checker-resolution.do"
                            reportConstraintViolation(state, doof::array_at(names, index, "src/checker-resolution", 255), doof::array_at(arguments, index, "src/checker-resolution", 255), std::string("Reflectable"), span);
                    }
                    }
#line 257 "/src/checker-resolution.do"
                    continue;
                }
#line 259 "/src/checker-resolution.do"
                if ((static_cast<int32_t>((named->typeArgs)->size()) == 0) && (named->name == std::string("JsonSerializable"))) {
#line 260 "/src/checker-resolution.do"
                    const auto result = memberType(state, doof::array_at(arguments, index, "src/checker-resolution", 260), std::string("fromJsonValue"), span, true);
#line 261 "/src/checker-resolution.do"
                    if (std::visit([](auto&& _obj) { return _obj->kind; }, result) == std::string("unknown")) {
#line 261 "/src/checker-resolution.do"
                        reportConstraintViolation(state, doof::array_at(names, index, "src/checker-resolution", 261), doof::array_at(arguments, index, "src/checker-resolution", 261), std::string("JsonSerializable"), span);
                    }
#line 262 "/src/checker-resolution.do"
                    continue;
                }
        }
        else {
        }
        }
#line 267 "/src/checker-resolution.do"
        const auto resolvedConstraint = resolveType(state, annotation, module, constraintScope);
#line 268 "/src/checker-resolution.do"
        const auto substitutedConstraint = ::app_src_checker_types_::substituteTypeParams(resolvedConstraint, names, arguments);
#line 269 "/src/checker-resolution.do"
        if (!::app_src_checker_types_::isAssignable(doof::array_at(arguments, index, "src/checker-resolution", 269), substitutedConstraint)) {
#line 270 "/src/checker-resolution.do"
            reportConstraintViolation(state, doof::array_at(names, index, "src/checker-resolution", 270), doof::array_at(arguments, index, "src/checker-resolution", 270), ::app_src_checker_types_::typeName(substitutedConstraint), span);
        }
    }
}
#line 275 "/src/checker-resolution.do"
void reportConstraintViolation(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& typeParam, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& argument, const std::string& constraint, ::app_src_ast_::SourceSpan span) {
#line 276 "/src/checker-resolution.do"
    ::app_src_checker_common_::typeError(state, ((((((std::string("Type \"") + ::app_src_checker_types_::typeName(argument)) + std::string("\" does not satisfy constraint \"")) + constraint) + std::string("\" for type parameter \"")) + typeParam) + std::string("\"")), span);
}
#line 279 "/src/checker-resolution.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> decorateType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType) {
#line 280 "/src/checker-resolution.do"
    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, annotation) = ::app_src_checker_symbols_::optionalResolvedType(resolvedType));
#line 281 "/src/checker-resolution.do"
    return resolvedType;
}
#line 288 "/src/checker-resolution.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> memberType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& object, const std::string& property, ::app_src_ast_::SourceSpan span, bool validateVisibility) {
#line 289 "/src/checker-resolution.do"
    if (::app_src_checker_types_::typeName(object) == std::string("string")) {
#line 290 "/src/checker-resolution.do"
        if (property == std::string("length")) {
#line 290 "/src/checker-resolution.do"
            return ::app_src_checker_types_::primitive(std::string("int"));
        }
#line 291 "/src/checker-resolution.do"
        if (((property == std::string("startsWith")) || (property == std::string("endsWith"))) || (property == std::string("contains"))) {
#line 291 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 292 "/src/checker-resolution.do"
        if (property == std::string("indexOf")) {
#line 292 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::primitive(std::string("int")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 293 "/src/checker-resolution.do"
        if (property == std::string("substring")) {
#line 293 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("start"), ::app_src_checker_types_::primitive(std::string("int")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("end"), ::app_src_checker_types_::primitive(std::string("int")), true)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 294 "/src/checker-resolution.do"
        if (property == std::string("replaceAll")) {
#line 294 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("oldValue"), ::app_src_checker_types_::primitive(std::string("string")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("newValue"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 295 "/src/checker-resolution.do"
        if (property == std::string("trim")) {
#line 295 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 296 "/src/checker-resolution.do"
        if (property == std::string("trimStart")) {
#line 296 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 297 "/src/checker-resolution.do"
        if (property == std::string("trimEnd")) {
#line 297 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("suffix"), ::app_src_checker_types_::primitive(std::string("char")), true)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 298 "/src/checker-resolution.do"
        if ((property == std::string("toLowerCase")) || (property == std::string("toUpperCase"))) {
#line 298 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 299 "/src/checker-resolution.do"
        if (property == std::string("repeat")) {
#line 299 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("count"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 300 "/src/checker-resolution.do"
        if (property == std::string("slice")) {
#line 300 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("start"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 301 "/src/checker-resolution.do"
        if (property == std::string("charAt")) {
#line 301 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("index"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::primitive(std::string("char")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 302 "/src/checker-resolution.do"
        if ((property == std::string("padStart")) || (property == std::string("padEnd"))) {
#line 302 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("length"), ::app_src_checker_types_::primitive(std::string("int")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("fill"), ::app_src_checker_types_::primitive(std::string("char")), true)}), ::app_src_checker_types_::primitive(std::string("string")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 303 "/src/checker-resolution.do"
        if (property == std::string("split")) {
#line 303 "/src/checker-resolution.do"
            return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("separator"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::arrayType(::app_src_checker_types_::primitive(std::string("string")), true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
    }
#line 305 "/src/checker-resolution.do"
    {
        auto _case_subject = object;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
            const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 307 "/src/checker-resolution.do"
            if (property == std::string("call")) {
#line 307 "/src/checker-resolution.do"
                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(function_);
            }
#line 308 "/src/checker-resolution.do"
            if (property == std::string("post")) {
#line 308 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(function_->params, ::app_src_checker_types_::promiseType(function_->returnType), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 309 "/src/checker-resolution.do"
            if (property == std::string("dispatch")) {
#line 310 "/src/checker-resolution.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, function_->returnType) != std::string("none")) {
#line 310 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, std::string("Method \"dispatch\" is only available on none-returning callbacks"), span);
#line 310 "/src/checker-resolution.do"
                    return ::app_src_checker_types_::unknownType();
                }
#line 311 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(function_->params, ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 313 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 316 "/src/checker-resolution.do"
            std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolved = std::monostate{};
#line 317 "/src/checker-resolution.do"
            const auto& _iterable_21 = union_->types;
            for (const auto& member : *_iterable_21) {
#line 318 "/src/checker-resolution.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, member) == std::string("none")) {
#line 318 "/src/checker-resolution.do"
                    continue;
                }
#line 319 "/src/checker-resolution.do"
                const auto memberValue = memberType(state, member, property, span, validateVisibility);
#line 320 "/src/checker-resolution.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, memberValue) == std::string("unknown")) {
#line 320 "/src/checker-resolution.do"
                    return ::app_src_checker_types_::unknownType();
                }
#line 321 "/src/checker-resolution.do"
                (resolved = doof::optional_value((doof::is_null(resolved) ? memberValue : ::app_src_checker_types_::joinTypes(doof::unwrap_optional(resolved), memberValue))));
            }
#line 323 "/src/checker-resolution.do"
            if (!doof::is_null(resolved)) {
#line 323 "/src/checker-resolution.do"
                return doof::unwrap_optional(resolved);
            }
#line 324 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 327 "/src/checker-resolution.do"
            if (property == std::string("length")) {
#line 327 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
#line 328 "/src/checker-resolution.do"
            if (array->readonly_ && ((((property == std::string("push")) || (property == std::string("reserve"))) || (property == std::string("pop"))) || (property == std::string("takeFirstCompleted")))) {
#line 329 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly array")), span);
#line 330 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 332 "/src/checker-resolution.do"
            if (property == std::string("push")) {
#line 332 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 333 "/src/checker-resolution.do"
            if (property == std::string("contains")) {
#line 333 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 334 "/src/checker-resolution.do"
            if (property == std::string("indexOf")) {
#line 334 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("int")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 335 "/src/checker-resolution.do"
            if (property == std::string("reserve")) {
#line 335 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("capacity"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 336 "/src/checker-resolution.do"
            if (property == std::string("pop")) {
#line 336 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::resultType(array->elementType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 337 "/src/checker-resolution.do"
            if (property == std::string("takeFirstCompleted")) {
#line 338 "/src/checker-resolution.do"
                {
                    auto _case_subject = array->elementType;
                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
                        const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 339 "/src/checker-resolution.do"
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::resultType(promise->valueType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                }
                else {
#line 340 "/src/checker-resolution.do"
                        return ::app_src_checker_types_::unknownType();
                }
                }
                doof::unreachable();
            }
#line 343 "/src/checker-resolution.do"
            if ((property == std::string("some")) || (property == std::string("every"))) {
#line 344 "/src/checker-resolution.do"
                const auto predicate = ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("it"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 345 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("predicate"), predicate, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 347 "/src/checker-resolution.do"
            if (property == std::string("filter")) {
#line 348 "/src/checker-resolution.do"
                const auto predicate = ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("it"), array->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 349 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("predicate"), predicate, false)}), ::app_src_checker_types_::arrayType(array->elementType, array->readonly_), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 351 "/src/checker-resolution.do"
            if (property == std::string("map")) {
#line 352 "/src/checker-resolution.do"
                const auto mapped = ::app_src_checker_types_::typeParameter(std::string("U"), std::string(""), std::monostate{});
#line 353 "/src/checker-resolution.do"
                const auto mapper = ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("it"), array->elementType, false)}), mapped, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 354 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("mapper"), mapper, false)}), ::app_src_checker_types_::arrayType(mapped, array->readonly_), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("U")}));
            }
#line 356 "/src/checker-resolution.do"
            if (property == std::string("slice")) {
#line 356 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("start"), ::app_src_checker_types_::primitive(std::string("int")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("end"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::arrayType(array->elementType, array->readonly_), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 357 "/src/checker-resolution.do"
            if (array->readonly_ && (((property == std::string("buildReadonly")) || (property == std::string("drainToReadonly"))) || (property == std::string("cloneReadonly")))) {
#line 358 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly array")), span);
#line 359 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 361 "/src/checker-resolution.do"
            if (property == std::string("buildReadonly")) {
#line 361 "/src/checker-resolution.do"
                ::app_src_checker_common_::deprecatedBuildReadonly(state, span);
#line 361 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(array->elementType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 362 "/src/checker-resolution.do"
            if ((property == std::string("drainToReadonly")) || (property == std::string("cloneReadonly"))) {
#line 362 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(array->elementType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 363 "/src/checker-resolution.do"
            if (property == std::string("cloneMutable")) {
#line 363 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(array->elementType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 364 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 367 "/src/checker-resolution.do"
            if (property == std::string("size")) {
#line 367 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
#line 368 "/src/checker-resolution.do"
            if (property == std::string("has")) {
#line 368 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 369 "/src/checker-resolution.do"
            if (property == std::string("get")) {
#line 369 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false)}), ::app_src_checker_types_::resultType(map->valueType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 370 "/src/checker-resolution.do"
            if (map->readonly_ && ((property == std::string("set")) || (property == std::string("delete")))) {
#line 371 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly map")), span);
#line 372 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 374 "/src/checker-resolution.do"
            if (property == std::string("set")) {
#line 374 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), map->valueType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 375 "/src/checker-resolution.do"
            if (property == std::string("delete")) {
#line 375 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("key"), map->keyType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 376 "/src/checker-resolution.do"
            if (property == std::string("keys")) {
#line 376 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(map->keyType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 377 "/src/checker-resolution.do"
            if (property == std::string("values")) {
#line 377 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(map->valueType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 378 "/src/checker-resolution.do"
            if (map->readonly_ && (((property == std::string("buildReadonly")) || (property == std::string("drainToReadonly"))) || (property == std::string("cloneReadonly")))) {
#line 379 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly map")), span);
#line 380 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 382 "/src/checker-resolution.do"
            if (property == std::string("buildReadonly")) {
#line 382 "/src/checker-resolution.do"
                ::app_src_checker_common_::deprecatedBuildReadonly(state, span);
#line 382 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::mapType(map->keyType, map->valueType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 383 "/src/checker-resolution.do"
            if ((property == std::string("drainToReadonly")) || (property == std::string("cloneReadonly"))) {
#line 383 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::mapType(map->keyType, map->valueType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 384 "/src/checker-resolution.do"
            if (property == std::string("cloneMutable")) {
#line 384 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::mapType(map->keyType, map->valueType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 385 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 388 "/src/checker-resolution.do"
            if (property == std::string("size")) {
#line 388 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
#line 389 "/src/checker-resolution.do"
            if (property == std::string("has")) {
#line 389 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), set->elementType, false)}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 390 "/src/checker-resolution.do"
            if (set->readonly_ && (property == std::string("add"))) {
#line 390 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, std::string("Method \"add\" is not available on readonly set"), span);
#line 390 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 391 "/src/checker-resolution.do"
            if (property == std::string("add")) {
#line 391 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), set->elementType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 392 "/src/checker-resolution.do"
            if (set->readonly_ && (property == std::string("delete"))) {
#line 392 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, std::string("Method \"delete\" is not available on readonly set"), span);
#line 392 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 393 "/src/checker-resolution.do"
            if (property == std::string("delete")) {
#line 393 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), set->elementType, false)}), ::app_src_checker_types_::noneType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 394 "/src/checker-resolution.do"
            if (property == std::string("values")) {
#line 394 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::arrayType(set->elementType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 395 "/src/checker-resolution.do"
            if (set->readonly_ && (((property == std::string("buildReadonly")) || (property == std::string("drainToReadonly"))) || (property == std::string("cloneReadonly")))) {
#line 396 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, ((std::string("Method \"") + property) + std::string("\" is not available on readonly set")), span);
#line 397 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 399 "/src/checker-resolution.do"
            if (property == std::string("buildReadonly")) {
#line 399 "/src/checker-resolution.do"
                ::app_src_checker_common_::deprecatedBuildReadonly(state, span);
#line 399 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::setType(set->elementType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 400 "/src/checker-resolution.do"
            if ((property == std::string("drainToReadonly")) || (property == std::string("cloneReadonly"))) {
#line 400 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::setType(set->elementType, true), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 401 "/src/checker-resolution.do"
            if (property == std::string("cloneMutable")) {
#line 401 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::setType(set->elementType, false), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 402 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 405 "/src/checker-resolution.do"
            if (property == std::string("value")) {
#line 405 "/src/checker-resolution.do"
                return result->valueType;
            }
#line 406 "/src/checker-resolution.do"
            if (property == std::string("error")) {
#line 406 "/src/checker-resolution.do"
                return result->errorType;
            }
#line 407 "/src/checker-resolution.do"
            if ((property == std::string("isSuccess")) || (property == std::string("isFailure"))) {
#line 407 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 408 "/src/checker-resolution.do"
            if (property == std::string("unwrapOr")) {
#line 409 "/src/checker-resolution.do"
                if (std::visit([](auto&& _obj) { return _obj->kind; }, result->valueType) == std::string("none")) {
#line 410 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, std::string("Method \"unwrapOr\" is not available on Result<void, E>"), span);
#line 411 "/src/checker-resolution.do"
                    return ::app_src_checker_types_::unknownType();
                }
#line 413 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("defaultValue"), result->valueType, false)}), result->valueType, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 417 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
            const auto& stream = std::get<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject);
#line 420 "/src/checker-resolution.do"
            if (property == std::string("next")) {
#line 420 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::primitive(std::string("bool")), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 421 "/src/checker-resolution.do"
            if (property == std::string("value")) {
#line 421 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), stream->elementType, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 422 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::RangeResolvedType>>(_case_subject)) {
#line 425 "/src/checker-resolution.do"
            if ((property == std::string("lowerBound")) || (property == std::string("upperBound"))) {
#line 425 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
#line 426 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 428 "/src/checker-resolution.do"
            return memberType(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), property, span, true);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
            const auto& promise = std::get<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject);
#line 430 "/src/checker-resolution.do"
            if (property == std::string("get")) {
#line 430 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::resultType(promise->valueType, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 431 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject)) {
            const auto& parameter = std::get<std::shared_ptr<::app_src_semantic_::TypeParameterType>>(_case_subject);
#line 434 "/src/checker-resolution.do"
            if (property == std::string("metadata")) {
#line 435 "/src/checker-resolution.do"
                if (parameter->constraintName != std::string("Reflectable")) {
#line 436 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, ((std::string("Static member \"metadata\" requires type parameter \"") + parameter->name) + std::string("\" to be constrained by Reflectable")), span);
#line 437 "/src/checker-resolution.do"
                    return ::app_src_checker_types_::unknownType();
                }
#line 439 "/src/checker-resolution.do"
                return ::app_src_checker_types_::classMetadataType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(parameter));
            }
#line 441 "/src/checker-resolution.do"
            if (property == std::string("fromJsonValue")) {
#line 442 "/src/checker-resolution.do"
                if (parameter->constraintName != std::string("JsonSerializable")) {
#line 443 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, ((std::string("Static member \"fromJsonValue\" requires type parameter \"") + parameter->name) + std::string("\" to be constrained by JsonSerializable")), span);
#line 444 "/src/checker-resolution.do"
                    return ::app_src_checker_types_::unknownType();
                }
#line 446 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(parameter), ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 451 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>>(_case_subject)) {
            const auto& metadata = std::get<std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>>(_case_subject);
#line 454 "/src/checker-resolution.do"
            if ((property == std::string("name")) || (property == std::string("description"))) {
#line 454 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("string"));
            }
#line 455 "/src/checker-resolution.do"
            if (property == std::string("methods")) {
#line 455 "/src/checker-resolution.do"
                return ::app_src_checker_types_::arrayType(::app_src_checker_types_::methodReflectionType(metadata->classType), false);
            }
#line 456 "/src/checker-resolution.do"
            if (property == std::string("defs")) {
#line 456 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{::app_src_checker_types_::jsonValueType(), ::app_src_checker_types_::noneType()}));
            }
#line 457 "/src/checker-resolution.do"
            if (property == std::string("invoke")) {
#line 458 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("instance"), metadata->classType, false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("methodName"), ::app_src_checker_types_::primitive(std::string("string")), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("params"), ::app_src_checker_types_::jsonValueType(), false)}), ::app_src_checker_types_::resultType(::app_src_checker_types_::jsonValueType(), ::app_src_checker_types_::jsonValueType()), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 464 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>(_case_subject)) {
            const auto& reflection = std::get<std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>(_case_subject);
#line 467 "/src/checker-resolution.do"
            if ((property == std::string("name")) || (property == std::string("description"))) {
#line 467 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("string"));
            }
#line 468 "/src/checker-resolution.do"
            if ((property == std::string("inputSchema")) || (property == std::string("outputSchema"))) {
#line 468 "/src/checker-resolution.do"
                return ::app_src_checker_types_::jsonValueType();
            }
#line 469 "/src/checker-resolution.do"
            if (property == std::string("invoke")) {
#line 470 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("instance"), reflection->classType, false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("params"), ::app_src_checker_types_::jsonValueType(), false)}), ::app_src_checker_types_::resultType(::app_src_checker_types_::jsonValueType(), ::app_src_checker_types_::jsonValueType()), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 475 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
            const auto& enum_ = std::get<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject);
#line 478 "/src/checker-resolution.do"
            if (property == std::string("name")) {
#line 478 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("string"));
            }
#line 479 "/src/checker-resolution.do"
            if (property == std::string("value")) {
#line 479 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("int"));
            }
#line 480 "/src/checker-resolution.do"
            if (property == std::string("fromName")) {
#line 481 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("string")), false)}), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{enum_, ::app_src_checker_types_::noneType()})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 486 "/src/checker-resolution.do"
            if (property == std::string("fromValue")) {
#line 487 "/src/checker-resolution.do"
                return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::primitive(std::string("int")), false)}), ::app_src_checker_types_::unionType(std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{enum_, ::app_src_checker_types_::noneType()})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
            }
#line 492 "/src/checker-resolution.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, enum_->symbol);
#line 493 "/src/checker-resolution.do"
            if (!doof::is_null(declaration)) {
#line 494 "/src/checker-resolution.do"
                {
                    auto _case_subject = doof::unwrap_optional(declaration);
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject)) {
                        const auto& enumDeclaration = std::get<std::shared_ptr<::app_src_ast_::EnumDeclaration>>(_case_subject);
#line 496 "/src/checker-resolution.do"
                        const auto& _iterable_23 = enumDeclaration->variants;
                        for (const auto& variant : *_iterable_23) {
#line 496 "/src/checker-resolution.do"
                            if (variant->name == property) {
#line 496 "/src/checker-resolution.do"
                                return doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(enum_);
                            }
                        }
                }
                else {
                }
                }
            }
#line 501 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 504 "/src/checker-resolution.do"
            if ((class_->name == std::string("SourceLocation")) && (class_->symbol->module == std::string("<builtin>"))) {
#line 505 "/src/checker-resolution.do"
                if ((property == std::string("fileName")) || (property == std::string("functionName"))) {
#line 505 "/src/checker-resolution.do"
                    return ::app_src_checker_types_::primitive(std::string("string"));
                }
#line 506 "/src/checker-resolution.do"
                if (property == std::string("line")) {
#line 506 "/src/checker-resolution.do"
                    return ::app_src_checker_types_::primitive(std::string("int"));
                }
#line 507 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 509 "/src/checker-resolution.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
#line 510 "/src/checker-resolution.do"
            if (doof::is_null(declaration)) {
#line 510 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 511 "/src/checker-resolution.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 513 "/src/checker-resolution.do"
                    if (property == std::string("metadata")) {
#line 514 "/src/checker-resolution.do"
                        if (static_cast<int32_t>((classDeclaration->typeParams)->size()) > 0) {
#line 515 "/src/checker-resolution.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Metadata is not available on generic type \"") + classDeclaration->name) + std::string("\"")), span);
#line 516 "/src/checker-resolution.do"
                            return ::app_src_checker_types_::unknownType();
                        }
#line 518 "/src/checker-resolution.do"
                        if (!::app_src_json_semantics_::canGenerateJsonSerialization(classDeclaration, jsonPrograms(state->result), nullptr) || !::app_src_json_semantics_::canGenerateJsonDeserialization(classDeclaration, jsonPrograms(state->result), nullptr)) {
#line 519 "/src/checker-resolution.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Type \"") + classDeclaration->name) + std::string("\" is not eligible for metadata because it does not support automatic JSON generation")), span);
#line 520 "/src/checker-resolution.do"
                            return ::app_src_checker_types_::unknownType();
                        }
#line 522 "/src/checker-resolution.do"
                        auto valid = true;
#line 523 "/src/checker-resolution.do"
                        const auto& _iterable_25 = classDeclaration->methods;
                        for (const auto& method : *_iterable_25) {
#line 524 "/src/checker-resolution.do"
                            if (method->private_ || method->static_) {
#line 524 "/src/checker-resolution.do"
                                continue;
                            }
#line 525 "/src/checker-resolution.do"
                            const auto& _iterable_27 = method->params;
                            for (const auto& parameter : *_iterable_27) {
#line 526 "/src/checker-resolution.do"
                                if ((!doof::is_null(parameter->resolvedType)) && !::app_src_json_semantics_::isGeneratedJsonType(doof::unwrap_optional(parameter->resolvedType), jsonPrograms(state->result), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
#line 527 "/src/checker-resolution.do"
                                    ::app_src_checker_common_::typeError(state, ((((std::string("Parameter \"") + parameter->name) + std::string("\" of method \"")) + method->name) + std::string("\" is not JSON-serializable")), parameter->span);
#line 528 "/src/checker-resolution.do"
                                    (valid = false);
                                }
                            }
#line 531 "/src/checker-resolution.do"
                            if (!doof::is_null(method->resolvedType)) {
#line 532 "/src/checker-resolution.do"
                                {
                                    auto _case_subject = doof::unwrap_optional(method->resolvedType);
                                    if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
                                        const auto& function_ = std::get<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject);
#line 534 "/src/checker-resolution.do"
                                        auto successType = function_->returnType;
#line 535 "/src/checker-resolution.do"
                                        {
                                            auto _case_subject = successType;
                                            if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
                                                const auto& result = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 536 "/src/checker-resolution.do"
                                                (successType = result->valueType);
                                        }
                                        else {
                                        }
                                        }
#line 539 "/src/checker-resolution.do"
                                        if ((std::visit([](auto&& _obj) { return _obj->kind; }, successType) != std::string("none")) && !::app_src_json_semantics_::isGeneratedJsonType(successType, jsonPrograms(state->result), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))) {
#line 540 "/src/checker-resolution.do"
                                            ::app_src_checker_common_::typeError(state, ((std::string("Return type of method \"") + method->name) + std::string("\" is not JSON-serializable")), method->span);
#line 541 "/src/checker-resolution.do"
                                            (valid = false);
                                        }
                                }
                                else {
                                }
                                }
                            }
                        }
#line 548 "/src/checker-resolution.do"
                        if (!valid) {
#line 548 "/src/checker-resolution.do"
                            return ::app_src_checker_types_::unknownType();
                        }
#line 549 "/src/checker-resolution.do"
                        (classDeclaration->needsMetadata = true);
#line 550 "/src/checker-resolution.do"
                        return ::app_src_checker_types_::classMetadataType(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(class_));
                    }
#line 552 "/src/checker-resolution.do"
                    if ((property == std::string("toJsonObject")) && ::app_src_json_semantics_::canGenerateJsonSerialization(classDeclaration, jsonPrograms(state->result), nullptr)) {
#line 553 "/src/checker-resolution.do"
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{}), ::app_src_checker_types_::jsonObjectType(), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
#line 555 "/src/checker-resolution.do"
                    if ((property == std::string("fromJsonValue")) && ::app_src_json_semantics_::canGenerateJsonDeserialization(classDeclaration, jsonPrograms(state->result), nullptr)) {
#line 556 "/src/checker-resolution.do"
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(object, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
#line 561 "/src/checker-resolution.do"
                    if ((property == std::string("toJsonObject")) || (property == std::string("fromJsonValue"))) {
#line 562 "/src/checker-resolution.do"
                        ::app_src_checker_common_::typeError(state, (((std::string("Type \"") + classDeclaration->name) + std::string("\" does not support automatic JSON ")) + ((property == std::string("toJsonObject")) ? std::string("serialization") : std::string("deserialization"))), span);
#line 563 "/src/checker-resolution.do"
                        return ::app_src_checker_types_::unknownType();
                    }
#line 565 "/src/checker-resolution.do"
                    const auto& _iterable_29 = classDeclaration->fields;
                    for (const auto& field : *_iterable_29) {
#line 566 "/src/checker-resolution.do"
                        const auto& _iterable_31 = field->names;
                        for (const auto& name : *_iterable_31) {
#line 567 "/src/checker-resolution.do"
                            if (name == property) {
#line 568 "/src/checker-resolution.do"
                                const auto fieldType = ((!doof::is_null(field->resolvedType)) ? doof::unwrap_optional(field->resolvedType) : ((!doof::is_null(field->type_)) ? resolveType(state, doof::unwrap_optional(field->type_), doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)) : ::app_src_checker_types_::unknownType()));
#line 569 "/src/checker-resolution.do"
                                if ((validateVisibility && field->private_) && (class_->symbol->module != state->info->path)) {
#line 570 "/src/checker-resolution.do"
                                    ::app_src_checker_common_::typeError(state, ((((std::string("Field '") + property) + std::string("' is private to module '")) + class_->symbol->module) + std::string("'")), span);
                                }
#line 572 "/src/checker-resolution.do"
                                return ::app_src_checker_types_::substituteTypeParams(fieldType, classDeclaration->typeParams, class_->typeArgs);
                            }
                        }
                    }
#line 576 "/src/checker-resolution.do"
                    const auto& _iterable_33 = classDeclaration->methods;
                    for (const auto& method : *_iterable_33) {
#line 577 "/src/checker-resolution.do"
                        if (method->name == property) {
#line 578 "/src/checker-resolution.do"
                            const auto methodType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_34 = method->resolvedType; if (doof::is_null(_coalesce_34)) return ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), state->result); return doof::unwrap_optional(_coalesce_34); }();
#line 579 "/src/checker-resolution.do"
                            if ((validateVisibility && method->private_) && (class_->symbol->module != state->info->path)) {
#line 580 "/src/checker-resolution.do"
                                ::app_src_checker_common_::typeError(state, ((((std::string("Method '") + property) + std::string("' is private to module '")) + class_->symbol->module) + std::string("'")), span);
                            }
#line 582 "/src/checker-resolution.do"
                            return ::app_src_checker_types_::substituteTypeParams(methodType, classDeclaration->typeParams, class_->typeArgs);
                        }
                    }
            }
            else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 587 "/src/checker-resolution.do"
                    const auto& _iterable_36 = interface_->fields;
                    for (const auto& field : *_iterable_36) {
#line 587 "/src/checker-resolution.do"
                        if (field->name == property) {
#line 587 "/src/checker-resolution.do"
                            return [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_37 = field->resolvedType; if (doof::is_null(_coalesce_37)) return resolveType(state, field->type_, doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)); return doof::unwrap_optional(_coalesce_37); }();
                        }
                    }
#line 588 "/src/checker-resolution.do"
                    const auto& _iterable_39 = interface_->methods;
                    for (const auto& method : *_iterable_39) {
#line 588 "/src/checker-resolution.do"
                        if (method->name == property) {
#line 588 "/src/checker-resolution.do"
                            return [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_40 = method->resolvedType; if (doof::is_null(_coalesce_40)) return ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, class_->symbol), state->result); return doof::unwrap_optional(_coalesce_40); }();
                        }
                    }
            }
            else {
            }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::EnumType>>(_case_subject)) {
#line 593 "/src/checker-resolution.do"
            return object;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interfaceType_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 595 "/src/checker-resolution.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, interfaceType_->symbol);
#line 596 "/src/checker-resolution.do"
            if (doof::is_null(declaration)) {
#line 596 "/src/checker-resolution.do"
                return ::app_src_checker_types_::unknownType();
            }
#line 597 "/src/checker-resolution.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 599 "/src/checker-resolution.do"
                    if (property == std::string("fromJsonValue")) {
#line 600 "/src/checker-resolution.do"
                        if (static_cast<int32_t>((interface_->typeParams)->size()) > 0) {
#line 601 "/src/checker-resolution.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Automatic JSON deserialization is not available on generic interface \"") + interface_->name) + std::string("\"")), span);
#line 602 "/src/checker-resolution.do"
                            return ::app_src_checker_types_::unknownType();
                        }
#line 604 "/src/checker-resolution.do"
                        if (static_cast<int32_t>((interfaceType_->symbol->implementations)->size()) == 0) {
#line 605 "/src/checker-resolution.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Cannot deserialize interface \"") + interface_->name) + std::string("\": no implementing classes found")), span);
#line 606 "/src/checker-resolution.do"
                            return ::app_src_checker_types_::unknownType();
                        }
#line 608 "/src/checker-resolution.do"
                        const auto discriminator = ::app_src_json_semantics_::interfaceJsonDiscriminator(interface_, jsonPrograms(state->result), nullptr);
#line 609 "/src/checker-resolution.do"
                        if (doof::is_null(discriminator)) {
#line 610 "/src/checker-resolution.do"
                            ::app_src_checker_common_::typeError(state, ((std::string("Cannot deserialize interface \"") + interface_->name) + std::string("\": all implementing classes must share a const string field with distinct values (e.g. const kind = \"variant\")")), span);
#line 611 "/src/checker-resolution.do"
                            return ::app_src_checker_types_::unknownType();
                        }
#line 613 "/src/checker-resolution.do"
                        (interface_->needsJson = true);
#line 614 "/src/checker-resolution.do"
                        return ::app_src_checker_types_::functionType(std::make_shared<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>(std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>{std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("value"), ::app_src_checker_types_::jsonValueType(), false), std::make_shared<::app_src_semantic_::FunctionParamType>(std::string("lenient"), ::app_src_checker_types_::primitive(std::string("bool")), true)}), ::app_src_checker_types_::resultType(object, ::app_src_checker_types_::primitive(std::string("string"))), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
                    }
#line 619 "/src/checker-resolution.do"
                    const auto& _iterable_42 = interface_->fields;
                    for (const auto& field : *_iterable_42) {
#line 620 "/src/checker-resolution.do"
                        if (field->name == property) {
#line 621 "/src/checker-resolution.do"
                            const auto fieldType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_43 = field->resolvedType; if (doof::is_null(_coalesce_43)) return resolveType(state, field->type_, doof::unwrap_optional(state->info), doof::unwrap_optional(state->moduleScope)); return doof::unwrap_optional(_coalesce_43); }();
#line 622 "/src/checker-resolution.do"
                            return ::app_src_checker_types_::substituteTypeParams(fieldType, interface_->typeParams, interfaceType_->typeArgs);
                        }
                    }
#line 625 "/src/checker-resolution.do"
                    const auto& _iterable_45 = interface_->methods;
                    for (const auto& method : *_iterable_45) {
#line 626 "/src/checker-resolution.do"
                        if (method->name == property) {
#line 627 "/src/checker-resolution.do"
                            const auto methodType = [&]() -> std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> { auto _coalesce_46 = method->resolvedType; if (doof::is_null(_coalesce_46)) return ::app_src_checker_symbols_::methodSignature(method, ::app_src_checker_interfaces_::classModuleFor(state->result, interfaceType_->symbol), state->result); return doof::unwrap_optional(_coalesce_46); }();
#line 628 "/src/checker-resolution.do"
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
#line 637 "/src/checker-resolution.do"
    return ::app_src_checker_types_::unknownType();
}
#line 640 "/src/checker-resolution.do"
std::shared_ptr<::app_src_semantic_::Binding> fieldAssignmentBinding(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& object, const std::string& property, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& fieldType) {
#line 641 "/src/checker-resolution.do"
    {
        auto _case_subject = object;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
            const auto& actor = std::get<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject);
#line 642 "/src/checker-resolution.do"
            return fieldAssignmentBinding(state, doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(actor->innerClass), property, fieldType);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 644 "/src/checker-resolution.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, class_->symbol);
#line 645 "/src/checker-resolution.do"
            if (doof::is_null(declaration)) {
#line 645 "/src/checker-resolution.do"
                return nullptr;
            }
#line 646 "/src/checker-resolution.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
                    const auto& classDeclaration = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 648 "/src/checker-resolution.do"
                    const auto& _iterable_48 = classDeclaration->fields;
                    for (const auto& field : *_iterable_48) {
#line 649 "/src/checker-resolution.do"
                        const auto& _iterable_50 = field->names;
                        for (const auto& name : *_iterable_50) {
#line 650 "/src/checker-resolution.do"
                            if (name == property) {
#line 651 "/src/checker-resolution.do"
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
#line 670 "/src/checker-resolution.do"
            const auto declaration = ::app_src_checker_symbols_::declarationFor(state->result, interfaceType_->symbol);
#line 671 "/src/checker-resolution.do"
            if (doof::is_null(declaration)) {
#line 671 "/src/checker-resolution.do"
                return nullptr;
            }
#line 672 "/src/checker-resolution.do"
            {
                auto _case_subject = doof::unwrap_optional(declaration);
                if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
                    const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 674 "/src/checker-resolution.do"
                    const auto& _iterable_52 = interface_->fields;
                    for (const auto& field : *_iterable_52) {
#line 675 "/src/checker-resolution.do"
                        if (field->name == property) {
#line 676 "/src/checker-resolution.do"
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
#line 695 "/src/checker-resolution.do"
    return nullptr;
}
#line 698 "/src/checker-resolution.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> jsonPrograms(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result) {
#line 699 "/src/checker-resolution.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> programs = std::make_shared<std::vector<std::shared_ptr<::app_src_ast_::Program>>>(std::vector<std::shared_ptr<::app_src_ast_::Program>>{});
#line 700 "/src/checker-resolution.do"
    const auto& _iterable_54 = result->modules;
    for (const auto& module : *_iterable_54) {
#line 700 "/src/checker-resolution.do"
        programs->push_back(module->program);
    }
#line 701 "/src/checker-resolution.do"
    return programs;
}
#line 704 "/src/checker-resolution.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> indexType(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& object, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& index, ::app_src_ast_::SourceSpan span) {
#line 705 "/src/checker-resolution.do"
    {
        auto _case_subject = object;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 707 "/src/checker-resolution.do"
            if (!::app_src_checker_types_::isAssignable(index, ::app_src_checker_types_::primitive(std::string("int"))) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
#line 707 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, std::string("Index must be an int"), span);
            }
#line 708 "/src/checker-resolution.do"
            return array->elementType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 711 "/src/checker-resolution.do"
            if (!::app_src_checker_types_::isAssignable(index, map->keyType) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
#line 711 "/src/checker-resolution.do"
                ::app_src_checker_common_::typeError(state, std::string("Invalid map key type"), span);
            }
#line 712 "/src/checker-resolution.do"
            return map->valueType;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
#line 714 "/src/checker-resolution.do"
            return ::app_src_checker_types_::unknownType();
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject)) {
            const auto& primitive_ = std::get<std::shared_ptr<::app_src_semantic_::PrimitiveType>>(_case_subject);
#line 716 "/src/checker-resolution.do"
            if (primitive_->name == std::string("string")) {
#line 717 "/src/checker-resolution.do"
                if (!::app_src_checker_types_::isAssignable(index, ::app_src_checker_types_::primitive(std::string("int"))) && (::app_src_checker_types_::typeName(index) != std::string("unknown"))) {
#line 717 "/src/checker-resolution.do"
                    ::app_src_checker_common_::typeError(state, std::string("Index must be an int"), span);
                }
#line 718 "/src/checker-resolution.do"
                return ::app_src_checker_types_::primitive(std::string("char"));
            }
    }
    else {
    }
    }
#line 723 "/src/checker-resolution.do"
    return ::app_src_checker_types_::unknownType();
}
#line 1 "<doof-generated>"
}
