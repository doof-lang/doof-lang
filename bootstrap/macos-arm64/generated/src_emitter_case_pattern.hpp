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
    struct TypePattern;
}

namespace app_src_emitter_case_pattern_ {
    struct CaseTypePatternEmission;
}

namespace app_src_semantic_ {
    using doof_header_type_1 = std::variant<std::monostate, std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_ast_ {
    using doof_header_type_2 = std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
}

namespace app_src_emitter_types_ {
    using doof_header_type_3 = std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
}

namespace app_src_emitter_case_pattern_ {
    using doof_header_type_4 = std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
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
    std::string originalName;
    bool native_;
    std::string nativeHeader;
    std::string nativeCppName;
    std::shared_ptr<std::vector<std::shared_ptr<Symbol>>> implementations;
    std::shared_ptr<std::vector<std::string>> implementedInterfaceTypes;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<ResolvedType>> streamElementTypes;
    Symbol(std::string kind, std::string name, std::string module, bool exported, std::string originalName, bool native_, std::string nativeHeader, std::string nativeCppName, std::shared_ptr<std::vector<std::shared_ptr<Symbol>>> implementations, std::shared_ptr<std::vector<std::string>> implementedInterfaceTypes, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<ResolvedType>> streamElementTypes) : kind(kind), name(name), module(module), exported(exported), originalName(originalName), native_(native_), nativeHeader(nativeHeader), nativeCppName(nativeCppName), implementations(implementations), implementedInterfaceTypes(implementedInterfaceTypes), typeParams(typeParams), streamElementTypes(streamElementTypes) {}
};
    struct PrimitiveType : public std::enable_shared_from_this<PrimitiveType> {
    std::string kind;
    std::string name;
    PrimitiveType(std::string kind, std::string name) : kind(kind), name(name) {}
};
    struct ClassType : public std::enable_shared_from_this<ClassType> {
    std::string kind;
    std::string name;
    std::shared_ptr<Symbol> symbol;
    std::shared_ptr<std::vector<ResolvedType>> typeArgs;
    ClassType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol, std::shared_ptr<std::vector<ResolvedType>> typeArgs) : kind(kind), name(name), symbol(symbol), typeArgs(typeArgs) {}
};
    struct EnumType : public std::enable_shared_from_this<EnumType> {
    std::string kind;
    std::string name;
    std::shared_ptr<Symbol> symbol;
    EnumType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol) : kind(kind), name(name), symbol(symbol) {}
};
    struct InterfaceType : public std::enable_shared_from_this<InterfaceType> {
    std::string kind;
    std::string name;
    std::shared_ptr<Symbol> symbol;
    std::shared_ptr<std::vector<ResolvedType>> typeArgs;
    InterfaceType(std::string kind, std::string name, std::shared_ptr<Symbol> symbol, std::shared_ptr<std::vector<ResolvedType>> typeArgs) : kind(kind), name(name), symbol(symbol), typeArgs(typeArgs) {}
};
    struct FunctionType : public std::enable_shared_from_this<FunctionType> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionParamType>>> params;
    ResolvedType returnType;
    std::shared_ptr<std::vector<std::string>> typeParams;
    FunctionType(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<FunctionParamType>>> params, ResolvedType returnType, std::shared_ptr<std::vector<std::string>> typeParams) : kind(kind), params(params), returnType(returnType), typeParams(typeParams) {}
};
    struct FunctionParamType : public std::enable_shared_from_this<FunctionParamType> {
    std::string name;
    ResolvedType type_;
    bool hasDefault;
    FunctionParamType(std::string name, ResolvedType type_, bool hasDefault) : name(name), type_(type_), hasDefault(hasDefault) {}
};
    struct ActorType : public std::enable_shared_from_this<ActorType> {
    std::string kind;
    std::shared_ptr<ClassType> innerClass;
    ActorType(std::string kind, std::shared_ptr<ClassType> innerClass) : kind(kind), innerClass(innerClass) {}
};
    struct PromiseType : public std::enable_shared_from_this<PromiseType> {
    std::string kind;
    ResolvedType valueType;
    PromiseType(std::string kind, ResolvedType valueType) : kind(kind), valueType(valueType) {}
};
    struct ArrayResolvedType : public std::enable_shared_from_this<ArrayResolvedType> {
    std::string kind;
    ResolvedType elementType;
    bool readonly_;
    ArrayResolvedType(std::string kind, ResolvedType elementType, bool readonly_) : kind(kind), elementType(elementType), readonly_(readonly_) {}
};
    struct MapResolvedType : public std::enable_shared_from_this<MapResolvedType> {
    std::string kind;
    ResolvedType keyType;
    ResolvedType valueType;
    bool readonly_;
    MapResolvedType(std::string kind, ResolvedType keyType, ResolvedType valueType, bool readonly_) : kind(kind), keyType(keyType), valueType(valueType), readonly_(readonly_) {}
};
    struct SetResolvedType : public std::enable_shared_from_this<SetResolvedType> {
    std::string kind;
    ResolvedType elementType;
    bool readonly_;
    SetResolvedType(std::string kind, ResolvedType elementType, bool readonly_) : kind(kind), elementType(elementType), readonly_(readonly_) {}
};
    struct StreamResolvedType : public std::enable_shared_from_this<StreamResolvedType> {
    std::string kind;
    ResolvedType elementType;
    StreamResolvedType(std::string kind, ResolvedType elementType) : kind(kind), elementType(elementType) {}
};
    struct RangeResolvedType : public std::enable_shared_from_this<RangeResolvedType> {
    std::string kind;
    RangeResolvedType(std::string kind) : kind(kind) {}
};
    struct JsonValueResolvedType : public std::enable_shared_from_this<JsonValueResolvedType> {
    std::string kind;
    JsonValueResolvedType(std::string kind) : kind(kind) {}
};
    struct ResultResolvedType : public std::enable_shared_from_this<ResultResolvedType> {
    std::string kind;
    ResolvedType valueType;
    ResolvedType errorType;
    ResultResolvedType(std::string kind, ResolvedType valueType, ResolvedType errorType) : kind(kind), valueType(valueType), errorType(errorType) {}
};
    struct TupleResolvedType : public std::enable_shared_from_this<TupleResolvedType> {
    std::string kind;
    std::shared_ptr<std::vector<ResolvedType>> elements;
    TupleResolvedType(std::string kind, std::shared_ptr<std::vector<ResolvedType>> elements) : kind(kind), elements(elements) {}
};
    struct UnionResolvedType : public std::enable_shared_from_this<UnionResolvedType> {
    std::string kind;
    std::shared_ptr<std::vector<ResolvedType>> types;
    UnionResolvedType(std::string kind, std::shared_ptr<std::vector<ResolvedType>> types) : kind(kind), types(types) {}
};
    struct WeakResolvedType : public std::enable_shared_from_this<WeakResolvedType> {
    std::string kind;
    ResolvedType inner;
    WeakResolvedType(std::string kind, ResolvedType inner) : kind(kind), inner(inner) {}
};
    struct NoneType : public std::enable_shared_from_this<NoneType> {
    std::string kind;
    NoneType(std::string kind) : kind(kind) {}
};
    struct NeverType : public std::enable_shared_from_this<NeverType> {
    std::string kind;
    NeverType(std::string kind) : kind(kind) {}
};
    struct UnknownType : public std::enable_shared_from_this<UnknownType> {
    std::string kind;
    UnknownType(std::string kind) : kind(kind) {}
};
    struct TypeParameterType : public std::enable_shared_from_this<TypeParameterType> {
    std::string kind;
    std::string name;
    std::string constraintName;
    doof_header_type_1 constraint;
    TypeParameterType(std::string kind, std::string name, std::string constraintName, doof_header_type_1 constraint) : kind(kind), name(name), constraintName(constraintName), constraint(constraint) {}
};
    struct ClassMetadataResolvedType : public std::enable_shared_from_this<ClassMetadataResolvedType> {
    std::string kind;
    ResolvedType classType;
    ClassMetadataResolvedType(std::string kind, ResolvedType classType) : kind(kind), classType(classType) {}
};
    struct MethodReflectionResolvedType : public std::enable_shared_from_this<MethodReflectionResolvedType> {
    std::string kind;
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
};
}

namespace app_src_emitter_case_pattern_ {
    struct CaseTypePatternEmission : public std::enable_shared_from_this<CaseTypePatternEmission> {
    std::string condition;
    std::string binding;
    CaseTypePatternEmission(std::string condition, std::string binding) : condition(condition), binding(binding) {}
};
}

namespace app_src_ast_ {
    struct SourceSpan {
    AstLocation start;
    AstLocation end;
    SourceSpan(AstLocation start, AstLocation end) : start(start), end(end) {}
    SourceSpan() {}
};
    struct NamedType : public std::enable_shared_from_this<NamedType> {
    std::string kind;
    std::string name;
    std::shared_ptr<std::vector<TypeAnnotation>> typeArgs;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol;
    doof_header_type_2 resolvedType;
    SourceSpan span;
    NamedType(std::string kind, std::string name, std::shared_ptr<std::vector<TypeAnnotation>> typeArgs, std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol, doof_header_type_2 resolvedType, SourceSpan span) : kind(kind), name(name), typeArgs(typeArgs), resolvedSymbol(resolvedSymbol), resolvedType(resolvedType), span(span) {}
};
    struct ArrayType : public std::enable_shared_from_this<ArrayType> {
    std::string kind;
    TypeAnnotation elementType;
    bool readonly_;
    doof_header_type_2 resolvedType;
    SourceSpan span;
    ArrayType(std::string kind, TypeAnnotation elementType, bool readonly_, doof_header_type_2 resolvedType, SourceSpan span) : kind(kind), elementType(elementType), readonly_(readonly_), resolvedType(resolvedType), span(span) {}
};
    struct UnionType : public std::enable_shared_from_this<UnionType> {
    std::string kind;
    std::shared_ptr<std::vector<TypeAnnotation>> types;
    doof_header_type_2 resolvedType;
    SourceSpan span;
    UnionType(std::string kind, std::shared_ptr<std::vector<TypeAnnotation>> types, doof_header_type_2 resolvedType, SourceSpan span) : kind(kind), types(types), resolvedType(resolvedType), span(span) {}
};
    struct AstFunctionType : public std::enable_shared_from_this<AstFunctionType> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionTypeParam>>> params;
    TypeAnnotation returnType;
    doof_header_type_2 resolvedType;
    SourceSpan span;
    AstFunctionType(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<FunctionTypeParam>>> params, TypeAnnotation returnType, doof_header_type_2 resolvedType, SourceSpan span) : kind(kind), params(params), returnType(returnType), resolvedType(resolvedType), span(span) {}
};
    struct WeakType : public std::enable_shared_from_this<WeakType> {
    std::string kind;
    TypeAnnotation type_;
    doof_header_type_2 resolvedType;
    SourceSpan span;
    WeakType(std::string kind, TypeAnnotation type_, doof_header_type_2 resolvedType, SourceSpan span) : kind(kind), type_(type_), resolvedType(resolvedType), span(span) {}
};
    struct FunctionTypeParam : public std::enable_shared_from_this<FunctionTypeParam> {
    std::string name;
    TypeAnnotation type_;
    SourceSpan span;
    FunctionTypeParam(std::string name, TypeAnnotation type_, SourceSpan span) : name(name), type_(type_), span(span) {}
};
    struct TypePattern : public std::enable_shared_from_this<TypePattern> {
    std::string kind;
    std::string name;
    TypeAnnotation type_;
    doof_header_type_2 resolvedType;
    SourceSpan span;
    TypePattern(std::string kind, std::string name, TypeAnnotation type_, doof_header_type_2 resolvedType, SourceSpan span) : kind(kind), name(name), type_(type_), resolvedType(resolvedType), span(span) {}
};
}

namespace app_src_emitter_types_ {
    std::string emitResultPayloadType(const doof_header_type_3& resolvedType, const std::string& currentModulePath);
    std::string emitType(const doof_header_type_3& resolvedType, const std::string& currentModulePath);
    bool usesVariantRepresentation(const doof_header_type_3& type_);
    bool usesNullableSingleValueRepresentation(const doof_header_type_3& type_);
}

namespace app_src_emitter_case_pattern_ {
    std::shared_ptr<CaseTypePatternEmission> emitCaseTypePattern(const std::shared_ptr<::app_src_ast_::TypePattern>& pattern, const doof_header_type_4& subjectType, const std::string& subject, const std::string& bindingName, const std::string& currentModulePath);
    std::shared_ptr<CaseTypePatternEmission> emitResultPattern(const std::shared_ptr<::app_src_ast_::TypePattern>& pattern, const std::shared_ptr<::app_src_semantic_::ResultResolvedType>& result, const std::string& subject, const std::string& bindingName, const std::string& currentModulePath);
    std::shared_ptr<CaseTypePatternEmission> emitJsonValuePattern(const doof_header_type_4& patternType, const std::string& subject, const std::string& bindingName);
}
