#pragma once
#include "doof_runtime.hpp"
namespace app_src_semantic_ {
    struct Symbol;
    struct PrimitiveType;
    struct ClassType;
    struct EnumType;
    struct InterfaceType;
    struct FunctionType;
    struct FunctionParamType;
    struct ActorType;
    struct PromiseType;
    struct ArrayResolvedType;
    struct MapResolvedType;
    struct SetResolvedType;
    struct StreamResolvedType;
    struct RangeResolvedType;
    struct JsonValueResolvedType;
    struct ResultResolvedType;
    struct TupleResolvedType;
    struct UnionResolvedType;
    struct WeakResolvedType;
    struct NoneType;
    struct NeverType;
    struct UnknownType;
    struct TypeParameterType;
    struct ClassMetadataResolvedType;
    struct MethodReflectionResolvedType;
}

namespace app_src_ast_ {
    struct AstLocation;
    struct SourceSpan;
    struct NamedType;
    struct ArrayType;
    struct UnionType;
    struct AstFunctionType;
    struct WeakType;
    struct FunctionTypeParam;
}

namespace app_src_semantic_ {
    using __type1 = std::variant<std::monostate, std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_ast_ {
    using __type2 = std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
}

namespace app_src_checker_types_ {
    using __type3 = std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
}

namespace app_src_semantic_ {
    using ResolvedType = std::variant<std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_ast_ {
    using TypeAnnotation = std::variant<std::shared_ptr<NamedType>, std::shared_ptr<ArrayType>, std::shared_ptr<UnionType>, std::shared_ptr<AstFunctionType>, std::shared_ptr<WeakType>>;
}

namespace app_src_semantic_ {
    struct Symbol : public std::enable_shared_from_this<Symbol> {
    std::string kind;
    std::string name;
    std::string module;
    bool exported;
    std::string originalName = std::string("");
    bool native_ = false;
    std::string nativeHeader = std::string("");
    std::string nativeCppName = std::string("");
    std::shared_ptr<std::vector<std::shared_ptr<Symbol>>> implementations = std::make_shared<std::vector<std::shared_ptr<Symbol>>>(std::vector<std::shared_ptr<Symbol>>{});
    std::shared_ptr<std::vector<std::string>> implementedInterfaceTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    Symbol(std::string kind, std::string name, std::string module, bool exported, std::string originalName = std::string(""), bool native_ = false, std::string nativeHeader = std::string(""), std::string nativeCppName = std::string(""), std::shared_ptr<std::vector<std::shared_ptr<Symbol>>> implementations = std::make_shared<std::vector<std::shared_ptr<Symbol>>>(std::vector<std::shared_ptr<Symbol>>{}), std::shared_ptr<std::vector<std::string>> implementedInterfaceTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : kind(kind), name(name), module(module), exported(exported), originalName(originalName), native_(native_), nativeHeader(nativeHeader), nativeCppName(nativeCppName), implementations(implementations), implementedInterfaceTypes(implementedInterfaceTypes) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Symbol>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct PrimitiveType : public std::enable_shared_from_this<PrimitiveType> {
    std::string kind = std::string("primitive");
    std::string name;
    PrimitiveType(std::string kind, std::string name) : kind(kind), name(name) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<PrimitiveType>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ClassType : public std::enable_shared_from_this<ClassType> {
    std::string kind = std::string("class");
    std::string name;
    std::shared_ptr<Symbol> symbol;
    std::shared_ptr<std::vector<ResolvedType>> typeArgs = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{});
    ClassType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol, std::shared_ptr<std::vector<ResolvedType>> typeArgs = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{})) : kind(kind), name(name), symbol(symbol), typeArgs(typeArgs) {}
};
    struct EnumType : public std::enable_shared_from_this<EnumType> {
    std::string kind = std::string("enum");
    std::string name;
    std::shared_ptr<Symbol> symbol;
    EnumType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol) : kind(kind), name(name), symbol(symbol) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<EnumType>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct InterfaceType : public std::enable_shared_from_this<InterfaceType> {
    std::string kind = std::string("interface");
    std::string name;
    std::shared_ptr<Symbol> symbol;
    std::shared_ptr<std::vector<ResolvedType>> typeArgs = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{});
    InterfaceType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol, std::shared_ptr<std::vector<ResolvedType>> typeArgs = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{})) : kind(kind), name(name), symbol(symbol), typeArgs(typeArgs) {}
};
    struct FunctionType : public std::enable_shared_from_this<FunctionType> {
    std::string kind = std::string("function");
    std::shared_ptr<std::vector<std::shared_ptr<FunctionParamType>>> params;
    ResolvedType returnType;
    std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    FunctionType(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<FunctionParamType>>> params, ResolvedType returnType, std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : kind(kind), params(params), returnType(returnType), typeParams(typeParams) {}
};
    struct FunctionParamType : public std::enable_shared_from_this<FunctionParamType> {
    std::string name;
    ResolvedType type_;
    bool hasDefault;
    FunctionParamType(std::string name, ResolvedType type_, bool hasDefault) : name(name), type_(type_), hasDefault(hasDefault) {}
};
    struct ActorType : public std::enable_shared_from_this<ActorType> {
    std::string kind = std::string("actor");
    std::shared_ptr<ClassType> innerClass;
    ActorType(std::string kind, std::shared_ptr<ClassType> innerClass) : kind(kind), innerClass(innerClass) {}
};
    struct PromiseType : public std::enable_shared_from_this<PromiseType> {
    std::string kind = std::string("promise");
    ResolvedType valueType;
    PromiseType(std::string kind, ResolvedType valueType) : kind(kind), valueType(valueType) {}
};
    struct ArrayResolvedType : public std::enable_shared_from_this<ArrayResolvedType> {
    std::string kind = std::string("array");
    ResolvedType elementType;
    bool readonly_;
    ArrayResolvedType(std::string kind, ResolvedType elementType, bool readonly_) : kind(kind), elementType(elementType), readonly_(readonly_) {}
};
    struct MapResolvedType : public std::enable_shared_from_this<MapResolvedType> {
    std::string kind = std::string("map");
    ResolvedType keyType;
    ResolvedType valueType;
    bool readonly_;
    MapResolvedType(std::string kind, ResolvedType keyType, ResolvedType valueType, bool readonly_) : kind(kind), keyType(keyType), valueType(valueType), readonly_(readonly_) {}
};
    struct SetResolvedType : public std::enable_shared_from_this<SetResolvedType> {
    std::string kind = std::string("set");
    ResolvedType elementType;
    bool readonly_;
    SetResolvedType(std::string kind, ResolvedType elementType, bool readonly_) : kind(kind), elementType(elementType), readonly_(readonly_) {}
};
    struct StreamResolvedType : public std::enable_shared_from_this<StreamResolvedType> {
    std::string kind = std::string("stream");
    ResolvedType elementType;
    StreamResolvedType(std::string kind, ResolvedType elementType) : kind(kind), elementType(elementType) {}
};
    struct RangeResolvedType : public std::enable_shared_from_this<RangeResolvedType> {
    std::string kind = std::string("range");
    RangeResolvedType(std::string kind = std::string("range")) : kind(kind) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<RangeResolvedType>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct JsonValueResolvedType : public std::enable_shared_from_this<JsonValueResolvedType> {
    std::string kind = std::string("json-value");
    JsonValueResolvedType(std::string kind = std::string("json-value")) : kind(kind) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<JsonValueResolvedType>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ResultResolvedType : public std::enable_shared_from_this<ResultResolvedType> {
    std::string kind = std::string("result");
    ResolvedType valueType;
    ResolvedType errorType;
    ResultResolvedType(std::string kind, ResolvedType valueType, ResolvedType errorType) : kind(kind), valueType(valueType), errorType(errorType) {}
};
    struct TupleResolvedType : public std::enable_shared_from_this<TupleResolvedType> {
    std::string kind = std::string("tuple");
    std::shared_ptr<std::vector<ResolvedType>> elements;
    TupleResolvedType(std::string kind, std::shared_ptr<std::vector<ResolvedType>> elements) : kind(kind), elements(elements) {}
};
    struct UnionResolvedType : public std::enable_shared_from_this<UnionResolvedType> {
    std::string kind = std::string("union");
    std::shared_ptr<std::vector<ResolvedType>> types;
    UnionResolvedType(std::string kind, std::shared_ptr<std::vector<ResolvedType>> types) : kind(kind), types(types) {}
};
    struct WeakResolvedType : public std::enable_shared_from_this<WeakResolvedType> {
    std::string kind = std::string("weak");
    ResolvedType inner;
    WeakResolvedType(std::string kind, ResolvedType inner) : kind(kind), inner(inner) {}
};
    struct NoneType : public std::enable_shared_from_this<NoneType> {
    std::string kind = std::string("none");
    NoneType(std::string kind = std::string("none")) : kind(kind) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NoneType>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NeverType : public std::enable_shared_from_this<NeverType> {
    std::string kind = std::string("never");
    NeverType(std::string kind = std::string("never")) : kind(kind) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NeverType>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct UnknownType : public std::enable_shared_from_this<UnknownType> {
    std::string kind = std::string("unknown");
    UnknownType(std::string kind = std::string("unknown")) : kind(kind) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<UnknownType>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct TypeParameterType : public std::enable_shared_from_this<TypeParameterType> {
    std::string kind = std::string("type-parameter");
    std::string name;
    std::string constraintName = std::string("");
    __type1 constraint = std::monostate{};
    TypeParameterType(std::string kind, std::string name, std::string constraintName = std::string(""), __type1 constraint = std::monostate{}) : kind(kind), name(name), constraintName(constraintName), constraint(constraint) {}
};
    struct ClassMetadataResolvedType : public std::enable_shared_from_this<ClassMetadataResolvedType> {
    std::string kind = std::string("class-metadata");
    ResolvedType classType;
    ClassMetadataResolvedType(std::string kind, ResolvedType classType) : kind(kind), classType(classType) {}
};
    struct MethodReflectionResolvedType : public std::enable_shared_from_this<MethodReflectionResolvedType> {
    std::string kind = std::string("method-reflection");
    ResolvedType classType;
    MethodReflectionResolvedType(std::string kind, ResolvedType classType) : kind(kind), classType(classType) {}
};
}

namespace app_src_ast_ {
    struct AstLocation {
    int32_t line;
    int32_t column;
    int32_t offset;
    AstLocation(int32_t line, int32_t column, int32_t offset) : line(line), column(column), offset(offset) {}
    AstLocation() {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<AstLocation, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_ast_ {
    struct SourceSpan {
    AstLocation start;
    AstLocation end;
    SourceSpan(AstLocation start, AstLocation end) : start(start), end(end) {}
    SourceSpan() {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<SourceSpan, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NamedType : public std::enable_shared_from_this<NamedType> {
    std::string kind;
    std::string name;
    std::shared_ptr<std::vector<TypeAnnotation>> typeArgs;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol = nullptr;
    __type2 resolvedType = std::monostate{};
    SourceSpan span;
    NamedType(std::string kind, std::string name, std::shared_ptr<std::vector<TypeAnnotation>> typeArgs, std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol, __type2 resolvedType, SourceSpan span) : kind(kind), name(name), typeArgs(typeArgs), resolvedSymbol(resolvedSymbol), resolvedType(resolvedType), span(span) {}
};
    struct ArrayType : public std::enable_shared_from_this<ArrayType> {
    std::string kind;
    TypeAnnotation elementType;
    bool readonly_;
    __type2 resolvedType = std::monostate{};
    SourceSpan span;
    ArrayType(std::string kind, TypeAnnotation elementType, bool readonly_, __type2 resolvedType, SourceSpan span) : kind(kind), elementType(elementType), readonly_(readonly_), resolvedType(resolvedType), span(span) {}
};
    struct UnionType : public std::enable_shared_from_this<UnionType> {
    std::string kind;
    std::shared_ptr<std::vector<TypeAnnotation>> types;
    __type2 resolvedType = std::monostate{};
    SourceSpan span;
    UnionType(std::string kind, std::shared_ptr<std::vector<TypeAnnotation>> types, __type2 resolvedType, SourceSpan span) : kind(kind), types(types), resolvedType(resolvedType), span(span) {}
};
    struct AstFunctionType : public std::enable_shared_from_this<AstFunctionType> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionTypeParam>>> params;
    TypeAnnotation returnType;
    __type2 resolvedType = std::monostate{};
    SourceSpan span;
    AstFunctionType(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<FunctionTypeParam>>> params, TypeAnnotation returnType, __type2 resolvedType, SourceSpan span) : kind(kind), params(params), returnType(returnType), resolvedType(resolvedType), span(span) {}
};
    struct WeakType : public std::enable_shared_from_this<WeakType> {
    std::string kind = std::string("weak-type");
    TypeAnnotation type_;
    __type2 resolvedType = std::monostate{};
    SourceSpan span;
    WeakType(std::string kind, TypeAnnotation type_, __type2 resolvedType, SourceSpan span) : kind(kind), type_(type_), resolvedType(resolvedType), span(span) {}
};
    struct FunctionTypeParam : public std::enable_shared_from_this<FunctionTypeParam> {
    std::string name;
    TypeAnnotation type_;
    SourceSpan span;
    FunctionTypeParam(std::string name, TypeAnnotation type_, SourceSpan span) : name(name), type_(type_), span(span) {}
};
}

namespace app_src_checker_types_ {
    __type3 primitive(const std::string& name);
    __type3 unknownType();
    __type3 noneType();
    __type3 neverType();
    __type3 arrayType(const __type3& element, bool readonly_ = false);
    __type3 mapType(const __type3& key, const __type3& value, bool readonly_ = false);
    __type3 setType(const __type3& element, bool readonly_ = false);
    __type3 streamType(const __type3& element);
    __type3 rangeType();
    __type3 jsonValueType();
    bool isJsonValueType(const __type3& resolvedType);
    __type3 jsonObjectType();
    __type3 classMetadataType(const __type3& classType_);
    __type3 methodReflectionType(const __type3& classType_);
    __type3 resultType(const __type3& value, const __type3& error);
    __type3 actorType(const std::shared_ptr<::app_src_semantic_::ClassType>& innerClass);
    __type3 promiseType(const __type3& valueType);
    __type3 weakType(const __type3& inner);
    __type3 tupleType(const std::shared_ptr<std::vector<__type3>>& elements);
    __type3 unionType(const std::shared_ptr<std::vector<__type3>>& types);
    void pushUniqueType(const std::shared_ptr<std::vector<__type3>>& types, const __type3& candidate);
    __type3 functionType(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::FunctionParamType>>>& params, const __type3& returnType, const std::shared_ptr<std::vector<std::string>>& typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    __type3 applyDeepReadonly(const __type3& type_);
    __type3 substituteTypeParams(const __type3& type_, const std::shared_ptr<std::vector<std::string>>& names, const std::shared_ptr<std::vector<__type3>>& arguments);
    __type3 typeParameter(const std::string& name, const std::string& constraintName = std::string(""), const std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& constraint = std::monostate{});
    std::shared_ptr<::app_src_semantic_::ClassType> classType(const std::string& name, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::shared_ptr<std::vector<__type3>>& typeArgs = std::make_shared<std::vector<__type3>>(std::vector<__type3>{}));
    std::shared_ptr<::app_src_semantic_::EnumType> enumType(const std::string& name, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol);
    std::shared_ptr<::app_src_semantic_::InterfaceType> interfaceType(const std::string& name, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::shared_ptr<std::vector<__type3>>& typeArgs = std::make_shared<std::vector<__type3>>(std::vector<__type3>{}));
    std::string typeName(const __type3& resolvedType);
    bool sameType(const __type3& left, const __type3& right);
    bool isAssignable(const __type3& value, const __type3& target);
    bool sameTypeArguments(const std::shared_ptr<std::vector<__type3>>& left, const std::shared_ptr<std::vector<__type3>>& right);
    bool isJsonValueAssignable(const __type3& value);
    __type3 joinTypes(const __type3& left, const __type3& right);
    bool isNumeric(const __type3& resolvedType);
    bool isStringInterpolatable(const __type3& type_);
    bool isSupportedHashCollectionType(const __type3& type_);
    __type3 numericResult(const __type3& left, const __type3& right);
    __type3 typeFromAnnotation(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation);
}
