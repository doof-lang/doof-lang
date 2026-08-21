#pragma once
#include "doof_runtime.hpp"
namespace app_src_semantic_ {
    struct SemanticLocation;
    struct SemanticSpan;
    struct Diagnostic;
    struct Symbol;
    struct ImportBinding;
    struct NamespaceBinding;
    struct SourceFile;
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
    struct TypeSubstitution;
    struct Binding;
    struct Scope;
    struct ResolvedTypeConstraint;
    struct CheckResult;
}

namespace app_src_semantic_ {
    using __type1 = std::variant<std::monostate, std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_semantic_ {
    using ResolvedType = std::variant<std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_semantic_ {
    struct SemanticLocation {
    int32_t line;
    int32_t column;
    int32_t offset;
    SemanticLocation(int32_t line, int32_t column, int32_t offset) : line(line), column(column), offset(offset) {}
    SemanticLocation() {}
};
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
    std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<ResolvedType>> streamElementTypes = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{});
    Symbol(std::string kind, std::string name, std::string module, bool exported, std::string originalName = std::string(""), bool native_ = false, std::string nativeHeader = std::string(""), std::string nativeCppName = std::string(""), std::shared_ptr<std::vector<std::shared_ptr<Symbol>>> implementations = std::make_shared<std::vector<std::shared_ptr<Symbol>>>(std::vector<std::shared_ptr<Symbol>>{}), std::shared_ptr<std::vector<std::string>> implementedInterfaceTypes = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<ResolvedType>> streamElementTypes = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{})) : kind(kind), name(name), module(module), exported(exported), originalName(originalName), native_(native_), nativeHeader(nativeHeader), nativeCppName(nativeCppName), implementations(implementations), implementedInterfaceTypes(implementedInterfaceTypes), typeParams(typeParams), streamElementTypes(streamElementTypes) {}
};
    struct ImportBinding : public std::enable_shared_from_this<ImportBinding> {
    std::string localName;
    std::string sourceName;
    std::string sourceModule;
    bool typeOnly;
    std::shared_ptr<Symbol> symbol = nullptr;
    ImportBinding(std::string localName, std::string sourceName, std::string sourceModule, bool typeOnly, std::shared_ptr<Symbol> symbol = nullptr) : localName(localName), sourceName(sourceName), sourceModule(sourceModule), typeOnly(typeOnly), symbol(symbol) {}
};
    struct NamespaceBinding : public std::enable_shared_from_this<NamespaceBinding> {
    std::string localName;
    std::string sourceModule;
    bool typeOnly;
    NamespaceBinding(std::string localName, std::string sourceModule, bool typeOnly) : localName(localName), sourceModule(sourceModule), typeOnly(typeOnly) {}
};
    struct SourceFile : public std::enable_shared_from_this<SourceFile> {
    std::string path;
    std::string source;
    SourceFile(std::string path, std::string source) : path(path), source(source) {}
};
    struct PrimitiveType : public std::enable_shared_from_this<PrimitiveType> {
    std::string kind = std::string("primitive");
    std::string name;
    PrimitiveType(std::string kind, std::string name) : kind(kind), name(name) {}
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
};
    struct JsonValueResolvedType : public std::enable_shared_from_this<JsonValueResolvedType> {
    std::string kind = std::string("json-value");
    JsonValueResolvedType(std::string kind = std::string("json-value")) : kind(kind) {}
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
};
    struct NeverType : public std::enable_shared_from_this<NeverType> {
    std::string kind = std::string("never");
    NeverType(std::string kind = std::string("never")) : kind(kind) {}
};
    struct UnknownType : public std::enable_shared_from_this<UnknownType> {
    std::string kind = std::string("unknown");
    UnknownType(std::string kind = std::string("unknown")) : kind(kind) {}
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
    struct TypeSubstitution : public std::enable_shared_from_this<TypeSubstitution> {
    std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<ResolvedType>> arguments = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{});
    TypeSubstitution(std::shared_ptr<std::vector<std::string>> names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<ResolvedType>> arguments = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{})) : names(names), arguments(arguments) {}
};
    struct Scope : public std::enable_shared_from_this<Scope> {
    std::shared_ptr<Scope> parent;
    std::shared_ptr<std::vector<std::shared_ptr<Binding>>> bindings = std::make_shared<std::vector<std::shared_ptr<Binding>>>(std::vector<std::shared_ptr<Binding>>{});
    std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> typeParamConstraintNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::shared_ptr<ResolvedTypeConstraint>>> typeParamConstraints = std::make_shared<std::vector<std::shared_ptr<ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<ResolvedTypeConstraint>>{});
    __type1 returnType = std::monostate{};
    __type1 thisType = std::monostate{};
    std::string functionName = std::string("");
    bool inValueYieldBlock = false;
    __type1 yieldType = std::monostate{};
    bool capturesTryErrors = false;
    std::shared_ptr<std::vector<ResolvedType>> catchErrorTypes = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{});
    bool tryPanics = false;
    Scope(std::shared_ptr<Scope> parent, std::shared_ptr<std::vector<std::shared_ptr<Binding>>> bindings = std::make_shared<std::vector<std::shared_ptr<Binding>>>(std::vector<std::shared_ptr<Binding>>{}), std::shared_ptr<std::vector<std::string>> typeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> typeParamConstraintNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::shared_ptr<ResolvedTypeConstraint>>> typeParamConstraints = std::make_shared<std::vector<std::shared_ptr<ResolvedTypeConstraint>>>(std::vector<std::shared_ptr<ResolvedTypeConstraint>>{}), __type1 returnType = std::monostate{}, __type1 thisType = std::monostate{}, std::string functionName = std::string(""), bool inValueYieldBlock = false, __type1 yieldType = std::monostate{}, bool capturesTryErrors = false, std::shared_ptr<std::vector<ResolvedType>> catchErrorTypes = std::make_shared<std::vector<ResolvedType>>(std::vector<ResolvedType>{}), bool tryPanics = false) : parent(parent), bindings(bindings), typeParams(typeParams), typeParamConstraintNames(typeParamConstraintNames), typeParamConstraints(typeParamConstraints), returnType(returnType), thisType(thisType), functionName(functionName), inValueYieldBlock(inValueYieldBlock), yieldType(yieldType), capturesTryErrors(capturesTryErrors), catchErrorTypes(catchErrorTypes), tryPanics(tryPanics) {}
};
    struct ResolvedTypeConstraint : public std::enable_shared_from_this<ResolvedTypeConstraint> {
    __type1 type_ = std::monostate{};
    ResolvedTypeConstraint(__type1 type_ = std::monostate{}) : type_(type_) {}
};
    struct CheckResult : public std::enable_shared_from_this<CheckResult> {
    std::shared_ptr<std::vector<std::shared_ptr<Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<Diagnostic>>>(std::vector<std::shared_ptr<Diagnostic>>{});
    CheckResult(std::shared_ptr<std::vector<std::shared_ptr<Diagnostic>>> diagnostics = std::make_shared<std::vector<std::shared_ptr<Diagnostic>>>(std::vector<std::shared_ptr<Diagnostic>>{})) : diagnostics(diagnostics) {}
};
}

namespace app_src_semantic_ {
    struct SemanticSpan {
    SemanticLocation start;
    SemanticLocation end;
    SemanticSpan(SemanticLocation start, SemanticLocation end) : start(start), end(end) {}
    SemanticSpan() {}
};
    struct Diagnostic : public std::enable_shared_from_this<Diagnostic> {
    std::string severity;
    std::string message;
    SemanticSpan span;
    std::string module;
    std::string replacement = std::string("");
    Diagnostic(std::string severity, std::string message, SemanticSpan span, std::string module, std::string replacement = std::string("")) : severity(severity), message(message), span(span), module(module), replacement(replacement) {}
};
    struct Binding : public std::enable_shared_from_this<Binding> {
    std::string name;
    std::string kind;
    ResolvedType type_;
    bool mutable_;
    SemanticSpan span;
    std::string module;
    std::shared_ptr<Symbol> symbol = nullptr;
    std::string casePattern = std::string("");
    std::string fieldMode = std::string("");
    std::string fieldOwner = std::string("");
    Binding(std::string name, std::string kind, ResolvedType type_, bool mutable_, SemanticSpan span, std::string module, std::shared_ptr<Symbol> symbol = nullptr, std::string casePattern = std::string(""), std::string fieldMode = std::string(""), std::string fieldOwner = std::string("")) : name(name), kind(kind), type_(type_), mutable_(mutable_), span(span), module(module), symbol(symbol), casePattern(casePattern), fieldMode(fieldMode), fieldOwner(fieldOwner) {}
};
}
