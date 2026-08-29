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

namespace app_src_resolver_ {
    struct ModuleResolver;
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
    struct IntLiteral;
    struct LongLiteral;
    struct FloatLiteral;
    struct DoubleLiteral;
    struct StringLiteral;
    struct CharLiteral;
    struct BoolLiteral;
    struct NoneLiteral;
    struct Identifier;
    struct BinaryExpression;
    struct UnaryExpression;
    struct AssignmentExpression;
    struct MemberExpression;
    struct IndexExpression;
    struct CallArgument;
    struct CallExpression;
    struct ArrayLiteral;
    struct ObjectProperty;
    struct ObjectLiteral;
    struct TupleLiteral;
    struct LambdaExpression;
    struct IfExpression;
    struct ConstructExpression;
    struct DotShorthand;
    struct ThisExpression;
    struct CallerExpression;
    struct AsyncExpression;
    struct RetireExpression;
    struct AsExpression;
    struct ActorCreationExpression;
    struct YieldBlockExpression;
    struct CatchExpression;
    struct Parameter;
    struct Block;
    struct ConstDeclaration;
    struct ReadonlyDeclaration;
    struct ImmutableBinding;
    struct LetDeclaration;
    struct FunctionDeclaration;
    struct TypeParameterConstraint;
    struct ReturnStatement;
    struct YieldStatement;
    struct YieldBlockAssignmentStatement;
    struct IfStatement;
    struct CaseExpression;
    struct CaseStatement;
    struct CaseArm;
    struct CaseExpressionArm;
    struct TypePattern;
    struct WildcardPattern;
    struct ValuePattern;
    struct RangePattern;
    struct IfBranch;
    struct WhileStatement;
    struct ForStatement;
    struct ForOfStatement;
    struct WithBinding;
    struct WithStatement;
    struct BreakStatement;
    struct ContinueStatement;
    struct ExpressionStatement;
    struct DestructuringStatement;
    struct DestructureBinding;
    struct TryStatement;
    struct ClassDeclaration;
    struct ClassField;
    struct InterfaceDeclaration;
    struct InterfaceField;
    struct EnumDeclaration;
    struct EnumVariant;
    struct TypeAliasDeclaration;
    struct NamedImport;
    struct NamespaceImport;
    struct ImportDeclaration;
    struct MockImportMapping;
    struct MockImportDirective;
    struct ExportDeclaration;
    struct ExportSpecifier;
    struct ExportList;
    struct Program;
}

namespace app_src_analyzer_ {
    struct ModuleInfo;
    struct AnalysisResult;
    struct ModuleParseResult;
    struct ModuleAnalyzer;
}

namespace app_src_emitter_names_ {
    struct ModuleNamespaceMapping;
}

namespace app_src_emitter_monomorphize_ {
    struct FunctionInstantiation;
    struct ClassInstantiation;
    struct InterfaceInstantiation;
    struct ImplementationRef;
    struct MethodInstantiation;
    struct InstantiationPlan;
}

namespace app_src_emitter_module_ {
    struct ModuleEmission;
    struct ModuleEmissionCacheKey;
    struct CoverageModuleMetadata;
    struct ModuleGraphEmission;
}

namespace app_src_emitter_wasm_ {
    struct WasmEmission;
}

namespace app_src_checker_state_ {
    struct CheckerState;
}

namespace app_src_checker_ {
    struct ModuleChecker;
}

namespace app_src_compiler_ {
    struct Compilation;
}

namespace app_src_semantic_ {
    using doof_header_type_1 = std::variant<std::monostate, std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_ast_ {
    using doof_header_type_2 = std::variant<std::monostate, std::shared_ptr<NamedType>, std::shared_ptr<ArrayType>, std::shared_ptr<UnionType>, std::shared_ptr<AstFunctionType>, std::shared_ptr<WeakType>>;
    using doof_header_type_3 = std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
    using doof_header_type_4 = std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
    using doof_header_type_5 = std::variant<std::monostate, std::shared_ptr<IntLiteral>, std::shared_ptr<LongLiteral>, std::shared_ptr<FloatLiteral>, std::shared_ptr<DoubleLiteral>, std::shared_ptr<StringLiteral>, std::shared_ptr<CharLiteral>, std::shared_ptr<BoolLiteral>, std::shared_ptr<NoneLiteral>, std::shared_ptr<Identifier>, std::shared_ptr<BinaryExpression>, std::shared_ptr<UnaryExpression>, std::shared_ptr<AssignmentExpression>, std::shared_ptr<MemberExpression>, std::shared_ptr<IndexExpression>, std::shared_ptr<CallExpression>, std::shared_ptr<ArrayLiteral>, std::shared_ptr<ObjectLiteral>, std::shared_ptr<TupleLiteral>, std::shared_ptr<LambdaExpression>, std::shared_ptr<IfExpression>, std::shared_ptr<CaseExpression>, std::shared_ptr<ConstructExpression>, std::shared_ptr<DotShorthand>, std::shared_ptr<ThisExpression>, std::shared_ptr<CallerExpression>, std::shared_ptr<AsyncExpression>, std::shared_ptr<RetireExpression>, std::shared_ptr<AsExpression>, std::shared_ptr<ActorCreationExpression>, std::shared_ptr<YieldBlockExpression>, std::shared_ptr<CatchExpression>>;
    using doof_header_type_6 = std::variant<std::shared_ptr<IntLiteral>, std::shared_ptr<LongLiteral>, std::shared_ptr<FloatLiteral>, std::shared_ptr<DoubleLiteral>, std::shared_ptr<StringLiteral>, std::shared_ptr<CharLiteral>, std::shared_ptr<BoolLiteral>, std::shared_ptr<NoneLiteral>, std::shared_ptr<Identifier>, std::shared_ptr<BinaryExpression>, std::shared_ptr<UnaryExpression>, std::shared_ptr<AssignmentExpression>, std::shared_ptr<MemberExpression>, std::shared_ptr<IndexExpression>, std::shared_ptr<CallExpression>, std::shared_ptr<ArrayLiteral>, std::shared_ptr<ObjectLiteral>, std::shared_ptr<TupleLiteral>, std::shared_ptr<LambdaExpression>, std::shared_ptr<IfExpression>, std::shared_ptr<CaseExpression>, std::shared_ptr<ConstructExpression>, std::shared_ptr<DotShorthand>, std::shared_ptr<ThisExpression>, std::shared_ptr<CallerExpression>, std::shared_ptr<AsyncExpression>, std::shared_ptr<RetireExpression>, std::shared_ptr<AsExpression>, std::shared_ptr<ActorCreationExpression>, std::shared_ptr<YieldBlockExpression>, std::shared_ptr<CatchExpression>, std::shared_ptr<Block>>;
    using doof_header_type_7 = std::variant<std::monostate, std::shared_ptr<ConstDeclaration>, std::shared_ptr<ReadonlyDeclaration>, std::shared_ptr<ImmutableBinding>, std::shared_ptr<LetDeclaration>, std::shared_ptr<FunctionDeclaration>, std::shared_ptr<ClassDeclaration>, std::shared_ptr<InterfaceDeclaration>, std::shared_ptr<EnumDeclaration>, std::shared_ptr<TypeAliasDeclaration>, std::shared_ptr<ImportDeclaration>, std::shared_ptr<MockImportDirective>, std::shared_ptr<ExportDeclaration>, std::shared_ptr<ExportList>, std::shared_ptr<IfStatement>, std::shared_ptr<CaseStatement>, std::shared_ptr<WhileStatement>, std::shared_ptr<ForStatement>, std::shared_ptr<ForOfStatement>, std::shared_ptr<WithStatement>, std::shared_ptr<ReturnStatement>, std::shared_ptr<YieldStatement>, std::shared_ptr<BreakStatement>, std::shared_ptr<ContinueStatement>, std::shared_ptr<ExpressionStatement>, std::shared_ptr<DestructuringStatement>, std::shared_ptr<TryStatement>, std::shared_ptr<YieldBlockAssignmentStatement>, std::shared_ptr<Block>>;
    using doof_header_type_8 = std::variant<std::shared_ptr<ConstDeclaration>, std::shared_ptr<ReadonlyDeclaration>, std::shared_ptr<ImmutableBinding>, std::shared_ptr<LetDeclaration>, std::shared_ptr<ExpressionStatement>, std::shared_ptr<DestructuringStatement>>;
}

namespace app_src_analyzer_ {
    using doof_header_type_9 = std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>;
}

namespace app_src_semantic_ {
    using ResolvedType = std::variant<std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_resolver_ {
    using SourceLoader = doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>;
}

namespace app_src_ast_ {
    using TypeAnnotation = std::variant<std::shared_ptr<NamedType>, std::shared_ptr<ArrayType>, std::shared_ptr<UnionType>, std::shared_ptr<AstFunctionType>, std::shared_ptr<WeakType>>;
    using Expression = std::variant<std::shared_ptr<IntLiteral>, std::shared_ptr<LongLiteral>, std::shared_ptr<FloatLiteral>, std::shared_ptr<DoubleLiteral>, std::shared_ptr<StringLiteral>, std::shared_ptr<CharLiteral>, std::shared_ptr<BoolLiteral>, std::shared_ptr<NoneLiteral>, std::shared_ptr<Identifier>, std::shared_ptr<BinaryExpression>, std::shared_ptr<UnaryExpression>, std::shared_ptr<AssignmentExpression>, std::shared_ptr<MemberExpression>, std::shared_ptr<IndexExpression>, std::shared_ptr<CallExpression>, std::shared_ptr<ArrayLiteral>, std::shared_ptr<ObjectLiteral>, std::shared_ptr<TupleLiteral>, std::shared_ptr<LambdaExpression>, std::shared_ptr<IfExpression>, std::shared_ptr<CaseExpression>, std::shared_ptr<ConstructExpression>, std::shared_ptr<DotShorthand>, std::shared_ptr<ThisExpression>, std::shared_ptr<CallerExpression>, std::shared_ptr<AsyncExpression>, std::shared_ptr<RetireExpression>, std::shared_ptr<AsExpression>, std::shared_ptr<ActorCreationExpression>, std::shared_ptr<YieldBlockExpression>, std::shared_ptr<CatchExpression>>;
    using CasePattern = std::variant<std::shared_ptr<TypePattern>, std::shared_ptr<WildcardPattern>, std::shared_ptr<ValuePattern>, std::shared_ptr<RangePattern>>;
    using ImportSpecifier = std::variant<std::shared_ptr<NamedImport>, std::shared_ptr<NamespaceImport>>;
    using Statement = std::variant<std::shared_ptr<ConstDeclaration>, std::shared_ptr<ReadonlyDeclaration>, std::shared_ptr<ImmutableBinding>, std::shared_ptr<LetDeclaration>, std::shared_ptr<FunctionDeclaration>, std::shared_ptr<ClassDeclaration>, std::shared_ptr<InterfaceDeclaration>, std::shared_ptr<EnumDeclaration>, std::shared_ptr<TypeAliasDeclaration>, std::shared_ptr<ImportDeclaration>, std::shared_ptr<MockImportDirective>, std::shared_ptr<ExportDeclaration>, std::shared_ptr<ExportList>, std::shared_ptr<IfStatement>, std::shared_ptr<CaseStatement>, std::shared_ptr<WhileStatement>, std::shared_ptr<ForStatement>, std::shared_ptr<ForOfStatement>, std::shared_ptr<WithStatement>, std::shared_ptr<ReturnStatement>, std::shared_ptr<YieldStatement>, std::shared_ptr<BreakStatement>, std::shared_ptr<ContinueStatement>, std::shared_ptr<ExpressionStatement>, std::shared_ptr<DestructuringStatement>, std::shared_ptr<TryStatement>, std::shared_ptr<YieldBlockAssignmentStatement>, std::shared_ptr<Block>>;
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
    struct ImportBinding : public std::enable_shared_from_this<ImportBinding> {
    std::string localName;
    std::string sourceName;
    std::string sourceModule;
    bool typeOnly;
    std::shared_ptr<Symbol> symbol;
    ImportBinding(std::string localName, std::string sourceName, std::string sourceModule, bool typeOnly, std::shared_ptr<Symbol> symbol) : localName(localName), sourceName(sourceName), sourceModule(sourceModule), typeOnly(typeOnly), symbol(symbol) {}
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
    std::string physicalPath;
    SourceFile(std::string path, std::string source, std::string physicalPath) : path(path), source(source), physicalPath(physicalPath) {}
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
    struct TypeSubstitution : public std::enable_shared_from_this<TypeSubstitution> {
    std::shared_ptr<std::vector<std::string>> names;
    std::shared_ptr<std::vector<ResolvedType>> arguments;
    TypeSubstitution(std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<ResolvedType>> arguments) : names(names), arguments(arguments) {}
};
    struct Scope : public std::enable_shared_from_this<Scope> {
    std::shared_ptr<Scope> parent;
    std::shared_ptr<std::vector<std::shared_ptr<Binding>>> bindings;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::string>> typeParamConstraintNames;
    std::shared_ptr<std::vector<std::shared_ptr<ResolvedTypeConstraint>>> typeParamConstraints;
    doof_header_type_1 returnType;
    doof_header_type_1 thisType;
    std::string functionName;
    bool staticContext;
    bool inValueYieldBlock;
    doof_header_type_1 yieldType;
    bool capturesTryErrors;
    std::shared_ptr<std::vector<ResolvedType>> catchErrorTypes;
    bool tryPanics;
    Scope(std::shared_ptr<Scope> parent, std::shared_ptr<std::vector<std::shared_ptr<Binding>>> bindings, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::string>> typeParamConstraintNames, std::shared_ptr<std::vector<std::shared_ptr<ResolvedTypeConstraint>>> typeParamConstraints, doof_header_type_1 returnType, doof_header_type_1 thisType, std::string functionName, bool staticContext, bool inValueYieldBlock, doof_header_type_1 yieldType, bool capturesTryErrors, std::shared_ptr<std::vector<ResolvedType>> catchErrorTypes, bool tryPanics) : parent(parent), bindings(bindings), typeParams(typeParams), typeParamConstraintNames(typeParamConstraintNames), typeParamConstraints(typeParamConstraints), returnType(returnType), thisType(thisType), functionName(functionName), staticContext(staticContext), inValueYieldBlock(inValueYieldBlock), yieldType(yieldType), capturesTryErrors(capturesTryErrors), catchErrorTypes(catchErrorTypes), tryPanics(tryPanics) {}
};
    struct ResolvedTypeConstraint : public std::enable_shared_from_this<ResolvedTypeConstraint> {
    doof_header_type_1 type_;
    ResolvedTypeConstraint(doof_header_type_1 type_) : type_(type_) {}
};
    struct CheckResult : public std::enable_shared_from_this<CheckResult> {
    std::shared_ptr<std::vector<std::shared_ptr<Diagnostic>>> diagnostics;
    CheckResult(std::shared_ptr<std::vector<std::shared_ptr<Diagnostic>>> diagnostics) : diagnostics(diagnostics) {}
};
}

namespace app_src_resolver_ {
    struct ModuleResolver : public std::enable_shared_from_this<ModuleResolver> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources;
    doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader;
    std::shared_ptr<std::vector<std::string>> loadedPaths;
    std::shared_ptr<std::vector<std::string>> failedPaths;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    ModuleResolver(std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sources, doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)> loader, std::shared_ptr<std::vector<std::string>> loadedPaths, std::shared_ptr<std::vector<std::string>> failedPaths, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) : sources(sources), loader(loader), loadedPaths(loadedPaths), failedPaths(failedPaths), diagnostics(diagnostics) {}
    std::shared_ptr<::app_src_semantic_::SourceFile> find(const std::string& path);
    bool failed(const std::string& path);
    std::string resolve(const std::string& importer, const std::string& specifier);
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
    struct TypeParameterConstraint : public std::enable_shared_from_this<TypeParameterConstraint> {
    doof_header_type_2 type_;
    TypeParameterConstraint(doof_header_type_2 type_) : type_(type_) {}
};
}

namespace app_src_analyzer_ {
    struct ModuleInfo : public std::enable_shared_from_this<ModuleInfo> {
    std::string path;
    std::string physicalPath;
    std::string sourceHash;
    std::shared_ptr<::app_src_ast_::Program> program;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> symbols;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> exports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> namespaceImports;
    std::shared_ptr<std::vector<std::string>> reExports;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> mockImportDirectives;
    std::optional<std::string> mockRootPath;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    ModuleInfo(std::string path, std::string physicalPath, std::string sourceHash, std::shared_ptr<::app_src_ast_::Program> program, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> symbols, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Symbol>>> exports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::ImportBinding>>> imports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::NamespaceBinding>>> namespaceImports, std::shared_ptr<std::vector<std::string>> reExports, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::MockImportDirective>>> mockImportDirectives, std::optional<std::string> mockRootPath, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) : path(path), physicalPath(physicalPath), sourceHash(sourceHash), program(program), symbols(symbols), exports(exports), imports(imports), namespaceImports(namespaceImports), reExports(reExports), mockImportDirectives(mockImportDirectives), mockRootPath(mockRootPath), diagnostics(diagnostics) {}
};
    struct AnalysisResult : public std::enable_shared_from_this<AnalysisResult> {
    std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> modules;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    AnalysisResult(std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> modules, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics) : modules(modules), diagnostics(diagnostics) {}
};
    struct ModuleParseResult : public std::enable_shared_from_this<ModuleParseResult> {
    std::string path;
    std::string physicalPath;
    std::string source;
    std::optional<std::string> inheritedMockRootPath;
    std::shared_ptr<::app_src_ast_::Program> program;
    std::string errorMessage;
    int32_t errorLine;
    int32_t errorColumn;
    int32_t errorOffset;
    ModuleParseResult(std::string path, std::string physicalPath, std::string source, std::optional<std::string> inheritedMockRootPath, std::shared_ptr<::app_src_ast_::Program> program, std::string errorMessage, int32_t errorLine, int32_t errorColumn, int32_t errorOffset) : path(path), physicalPath(physicalPath), source(source), inheritedMockRootPath(inheritedMockRootPath), program(program), errorMessage(errorMessage), errorLine(errorLine), errorColumn(errorColumn), errorOffset(errorOffset) {}
};
    struct ModuleAnalyzer : public std::enable_shared_from_this<ModuleAnalyzer> {
    std::shared_ptr<::app_src_resolver_::ModuleResolver> resolver;
    std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> modules;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    std::shared_ptr<std::vector<std::string>> inProgress;
    std::shared_ptr<std::vector<std::string>> resolvedPaths;
    ModuleAnalyzer(std::shared_ptr<::app_src_resolver_::ModuleResolver> resolver, std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>> modules, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics, std::shared_ptr<std::vector<std::string>> inProgress, std::shared_ptr<std::vector<std::string>> resolvedPaths) : resolver(resolver), modules(modules), diagnostics(diagnostics), inProgress(inProgress), resolvedPaths(resolvedPaths) {}
    std::shared_ptr<AnalysisResult> analyze(const std::string& entry);
    void queueModuleParse(const std::string& path, const std::optional<std::string>& inheritedMockRootPath, const std::shared_ptr<std::vector<std::string>>& scheduled, const std::shared_ptr<std::vector<doof::Promise<std::shared_ptr<ModuleParseResult>>>>& pending);
    void parseReachableModules(const std::string& entryPath);
    void orderModules(const std::string& entryPath);
    void appendModuleOrder(const std::string& path, const std::shared_ptr<std::vector<std::shared_ptr<ModuleInfo>>>& ordered, const std::shared_ptr<std::vector<std::string>>& visited);
    std::shared_ptr<ModuleInfo> resolveModule(const std::string& path);
    void collectSymbols(const std::shared_ptr<ModuleInfo>& info);
    void decorateDeclarationSymbol(const doof_header_type_9& statement, const std::shared_ptr<::app_src_semantic_::Symbol>& symbol);
    std::shared_ptr<::app_src_semantic_::Symbol> symbolFor(const doof_header_type_9& statement, const std::string& module);
    std::shared_ptr<::app_src_semantic_::Symbol> exportedSymbol(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& exportedName);
    void resolveImports(const std::shared_ptr<ModuleInfo>& info);
    void resolveExportLists(const std::shared_ptr<ModuleInfo>& info);
    void resolveNamedTypes(const std::shared_ptr<ModuleInfo>& info);
    void visitStatementTypes(const doof_header_type_9& statement, const std::shared_ptr<ModuleInfo>& info);
    void visitFunctionTypes(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& ownerTypeParams);
    void visitTypeParameterConstraints(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>>& constraints, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& typeParams);
    void visitType(const std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>>& annotation, const std::shared_ptr<ModuleInfo>& info, const std::shared_ptr<std::vector<std::string>>& typeParams);
    bool containsTypeParam(const std::shared_ptr<std::vector<std::string>>& typeParams, const std::string& name);
    std::shared_ptr<ModuleInfo> findModule(const std::string& path);
    void keepStatementTypes(const std::shared_ptr<::app_src_ast_::Block>& block, const std::shared_ptr<::app_src_ast_::ExportDeclaration>& export_, const std::shared_ptr<::app_src_ast_::ImportDeclaration>& import_, const std::shared_ptr<::app_src_ast_::MockImportDirective>& mockImport, const std::shared_ptr<::app_src_ast_::IfStatement>& if_, const std::shared_ptr<::app_src_ast_::CaseStatement>& case_, const std::shared_ptr<::app_src_ast_::WhileStatement>& while_, const std::shared_ptr<::app_src_ast_::ForStatement>& for_, const std::shared_ptr<::app_src_ast_::ForOfStatement>& forOf, const std::shared_ptr<::app_src_ast_::WithStatement>& with_, const std::shared_ptr<::app_src_ast_::ReturnStatement>& return_, const std::shared_ptr<::app_src_ast_::YieldStatement>& yield_, const std::shared_ptr<::app_src_ast_::BreakStatement>& break_, const std::shared_ptr<::app_src_ast_::ContinueStatement>& continue_, const std::shared_ptr<::app_src_ast_::ExpressionStatement>& expression, const std::shared_ptr<::app_src_ast_::DestructuringStatement>& destructuring);
    std::string resolveImportPath(const std::shared_ptr<ModuleInfo>& info, const std::string& specifier);
    std::optional<std::string> findMockReplacement(const std::shared_ptr<ModuleInfo>& root, const std::string& sourcePath, const std::string& dependencySpecifier);
    void validateMockImportDirectives(const std::shared_ptr<ModuleInfo>& info, const std::optional<std::string>& inheritedMockRootPath);
};
}

namespace app_src_emitter_names_ {
    struct ModuleNamespaceMapping : public std::enable_shared_from_this<ModuleNamespaceMapping> {
    std::string logicalPrefix;
    std::string packageName;
    std::string outputRoot;
    ModuleNamespaceMapping(std::string logicalPrefix, std::string packageName, std::string outputRoot) : logicalPrefix(logicalPrefix), packageName(packageName), outputRoot(outputRoot) {}
};
}

namespace app_src_emitter_monomorphize_ {
    struct FunctionInstantiation : public std::enable_shared_from_this<FunctionInstantiation> {
    std::string key;
    std::string modulePath;
    std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration;
    std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution;
    std::string emittedName;
    std::shared_ptr<std::vector<std::string>> trace;
    FunctionInstantiation(std::string key, std::string modulePath, std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration, std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution, std::string emittedName, std::shared_ptr<std::vector<std::string>> trace) : key(key), modulePath(modulePath), declaration(declaration), substitution(substitution), emittedName(emittedName), trace(trace) {}
};
    struct ClassInstantiation : public std::enable_shared_from_this<ClassInstantiation> {
    std::string key;
    std::string modulePath;
    std::shared_ptr<::app_src_ast_::ClassDeclaration> declaration;
    std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution;
    std::string emittedName;
    std::shared_ptr<std::vector<std::string>> trace;
    ClassInstantiation(std::string key, std::string modulePath, std::shared_ptr<::app_src_ast_::ClassDeclaration> declaration, std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution, std::string emittedName, std::shared_ptr<std::vector<std::string>> trace) : key(key), modulePath(modulePath), declaration(declaration), substitution(substitution), emittedName(emittedName), trace(trace) {}
};
    struct InterfaceInstantiation : public std::enable_shared_from_this<InterfaceInstantiation> {
    std::string key;
    std::string modulePath;
    std::string name;
    std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution;
    std::string emittedName;
    std::shared_ptr<std::vector<std::shared_ptr<ImplementationRef>>> implementations;
    InterfaceInstantiation(std::string key, std::string modulePath, std::string name, std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution, std::string emittedName, std::shared_ptr<std::vector<std::shared_ptr<ImplementationRef>>> implementations) : key(key), modulePath(modulePath), name(name), substitution(substitution), emittedName(emittedName), implementations(implementations) {}
};
    struct ImplementationRef : public std::enable_shared_from_this<ImplementationRef> {
    std::string modulePath;
    std::string typeName;
    ImplementationRef(std::string modulePath, std::string typeName) : modulePath(modulePath), typeName(typeName) {}
};
    struct MethodInstantiation : public std::enable_shared_from_this<MethodInstantiation> {
    std::string key;
    std::string modulePath;
    std::string ownerKey;
    std::shared_ptr<::app_src_ast_::ClassDeclaration> owner;
    std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration;
    std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution;
    std::string ownerEmittedName;
    std::string emittedName;
    std::shared_ptr<std::vector<std::string>> trace;
    MethodInstantiation(std::string key, std::string modulePath, std::string ownerKey, std::shared_ptr<::app_src_ast_::ClassDeclaration> owner, std::shared_ptr<::app_src_ast_::FunctionDeclaration> declaration, std::shared_ptr<::app_src_semantic_::TypeSubstitution> substitution, std::string ownerEmittedName, std::string emittedName, std::shared_ptr<std::vector<std::string>> trace) : key(key), modulePath(modulePath), ownerKey(ownerKey), owner(owner), declaration(declaration), substitution(substitution), ownerEmittedName(ownerEmittedName), emittedName(emittedName), trace(trace) {}
};
    struct InstantiationPlan : public std::enable_shared_from_this<InstantiationPlan> {
    std::shared_ptr<std::vector<std::shared_ptr<FunctionInstantiation>>> functions;
    std::shared_ptr<std::vector<std::shared_ptr<ClassInstantiation>>> classes;
    std::shared_ptr<std::vector<std::shared_ptr<InterfaceInstantiation>>> interfaces;
    std::shared_ptr<std::vector<std::shared_ptr<MethodInstantiation>>> methods;
    bool overflow;
    std::shared_ptr<std::vector<std::string>> overflowTrace;
    std::shared_ptr<std::vector<std::string>> currentTrace;
    std::shared_ptr<std::vector<std::string>> jsonSerializationKeys;
    std::shared_ptr<std::vector<std::string>> jsonDeserializationKeys;
    std::shared_ptr<std::vector<std::string>> concreteNameScopes;
    std::shared_ptr<std::vector<std::string>> concreteNames;
    InstantiationPlan(std::shared_ptr<std::vector<std::shared_ptr<FunctionInstantiation>>> functions, std::shared_ptr<std::vector<std::shared_ptr<ClassInstantiation>>> classes, std::shared_ptr<std::vector<std::shared_ptr<InterfaceInstantiation>>> interfaces, std::shared_ptr<std::vector<std::shared_ptr<MethodInstantiation>>> methods, bool overflow, std::shared_ptr<std::vector<std::string>> overflowTrace, std::shared_ptr<std::vector<std::string>> currentTrace, std::shared_ptr<std::vector<std::string>> jsonSerializationKeys, std::shared_ptr<std::vector<std::string>> jsonDeserializationKeys, std::shared_ptr<std::vector<std::string>> concreteNameScopes, std::shared_ptr<std::vector<std::string>> concreteNames) : functions(functions), classes(classes), interfaces(interfaces), methods(methods), overflow(overflow), overflowTrace(overflowTrace), currentTrace(currentTrace), jsonSerializationKeys(jsonSerializationKeys), jsonDeserializationKeys(jsonDeserializationKeys), concreteNameScopes(concreteNameScopes), concreteNames(concreteNames) {}
};
}

namespace app_src_emitter_module_ {
    struct ModuleEmission : public std::enable_shared_from_this<ModuleEmission> {
    std::string modulePath;
    std::string header;
    std::string source;
    std::string headerName;
    std::string sourceName;
    int32_t coverageModuleId;
    std::shared_ptr<std::vector<int32_t>> instrumentedLines;
    bool reused;
    std::string fingerprint;
    ModuleEmission(std::string modulePath, std::string header, std::string source, std::string headerName, std::string sourceName, int32_t coverageModuleId, std::shared_ptr<std::vector<int32_t>> instrumentedLines, bool reused, std::string fingerprint) : modulePath(modulePath), header(header), source(source), headerName(headerName), sourceName(sourceName), coverageModuleId(coverageModuleId), instrumentedLines(instrumentedLines), reused(reused), fingerprint(fingerprint) {}
};
    struct ModuleEmissionCacheKey : public std::enable_shared_from_this<ModuleEmissionCacheKey> {
    std::string modulePath;
    std::string fingerprint;
    ModuleEmissionCacheKey(std::string modulePath, std::string fingerprint) : modulePath(modulePath), fingerprint(fingerprint) {}
};
    struct CoverageModuleMetadata : public std::enable_shared_from_this<CoverageModuleMetadata> {
    int32_t moduleId;
    std::string modulePath;
    std::shared_ptr<std::vector<int32_t>> instrumentedLines;
    CoverageModuleMetadata(int32_t moduleId, std::string modulePath, std::shared_ptr<std::vector<int32_t>> instrumentedLines) : moduleId(moduleId), modulePath(modulePath), instrumentedLines(instrumentedLines) {}
};
    struct ModuleGraphEmission : public std::enable_shared_from_this<ModuleGraphEmission> {
    std::shared_ptr<std::vector<std::shared_ptr<ModuleEmission>>> modules;
    std::shared_ptr<std::vector<std::shared_ptr<CoverageModuleMetadata>>> coverageModules;
    std::string wasmSupportSource;
    std::shared_ptr<std::vector<std::string>> wasmExportNames;
    ModuleGraphEmission(std::shared_ptr<std::vector<std::shared_ptr<ModuleEmission>>> modules, std::shared_ptr<std::vector<std::shared_ptr<CoverageModuleMetadata>>> coverageModules, std::string wasmSupportSource, std::shared_ptr<std::vector<std::string>> wasmExportNames) : modules(modules), coverageModules(coverageModules), wasmSupportSource(wasmSupportSource), wasmExportNames(wasmExportNames) {}
};
}

namespace app_src_emitter_wasm_ {
    struct WasmEmission : public std::enable_shared_from_this<WasmEmission> {
    std::string source;
    std::shared_ptr<std::vector<std::string>> exportNames;
    WasmEmission(std::string source, std::shared_ptr<std::vector<std::string>> exportNames) : source(source), exportNames(exportNames) {}
};
}

namespace app_src_checker_state_ {
    struct CheckerState : public std::enable_shared_from_this<CheckerState> {
    std::shared_ptr<::app_src_analyzer_::AnalysisResult> result;
    std::string entry;
    std::string entryMode;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    std::shared_ptr<::app_src_analyzer_::ModuleInfo> info;
    std::shared_ptr<::app_src_semantic_::Scope> moduleScope;
    bool allowsCaller;
    CheckerState(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string entry, std::string entryMode, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics, std::shared_ptr<::app_src_analyzer_::ModuleInfo> info, std::shared_ptr<::app_src_semantic_::Scope> moduleScope, bool allowsCaller) : result(result), entry(entry), entryMode(entryMode), diagnostics(diagnostics), info(info), moduleScope(moduleScope), allowsCaller(allowsCaller) {}
};
}

namespace app_src_checker_ {
    struct ModuleChecker : public std::enable_shared_from_this<ModuleChecker> {
    std::shared_ptr<::app_src_checker_state_::CheckerState> state;
    ModuleChecker(std::shared_ptr<::app_src_checker_state_::CheckerState> state) : state(state) {}
    std::shared_ptr<::app_src_semantic_::CheckResult> check(const std::string& entry);
};
}

namespace app_src_compiler_ {
    struct Compilation : public std::enable_shared_from_this<Compilation> {
    std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> emission;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sourceFiles;
    std::shared_ptr<std::vector<std::string>> resolutionProbes;
    Compilation(std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> emission, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sourceFiles, std::shared_ptr<std::vector<std::string>> resolutionProbes) : emission(emission), diagnostics(diagnostics), sourceFiles(sourceFiles), resolutionProbes(resolutionProbes) {}
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
    std::string replacement;
    Diagnostic(std::string severity, std::string message, SemanticSpan span, std::string module, std::string replacement) : severity(severity), message(message), span(span), module(module), replacement(replacement) {}
};
    struct Binding : public std::enable_shared_from_this<Binding> {
    std::string name;
    std::string kind;
    ResolvedType type_;
    bool mutable_;
    SemanticSpan span;
    std::string module;
    std::shared_ptr<Symbol> symbol;
    std::string casePattern;
    std::string fieldMode;
    std::string fieldOwner;
    Binding(std::string name, std::string kind, ResolvedType type_, bool mutable_, SemanticSpan span, std::string module, std::shared_ptr<Symbol> symbol, std::string casePattern, std::string fieldMode, std::string fieldOwner) : name(name), kind(kind), type_(type_), mutable_(mutable_), span(span), module(module), symbol(symbol), casePattern(casePattern), fieldMode(fieldMode), fieldOwner(fieldOwner) {}
};
}

namespace app_src_resolver_ {
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> noSourceLoader(const std::string& path);
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
    doof_header_type_3 resolvedType;
    SourceSpan span;
    NamedType(std::string kind, std::string name, std::shared_ptr<std::vector<TypeAnnotation>> typeArgs, std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), typeArgs(typeArgs), resolvedSymbol(resolvedSymbol), resolvedType(resolvedType), span(span) {}
};
    struct ArrayType : public std::enable_shared_from_this<ArrayType> {
    std::string kind;
    TypeAnnotation elementType;
    bool readonly_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ArrayType(std::string kind, TypeAnnotation elementType, bool readonly_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), elementType(elementType), readonly_(readonly_), resolvedType(resolvedType), span(span) {}
};
    struct UnionType : public std::enable_shared_from_this<UnionType> {
    std::string kind;
    std::shared_ptr<std::vector<TypeAnnotation>> types;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    UnionType(std::string kind, std::shared_ptr<std::vector<TypeAnnotation>> types, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), types(types), resolvedType(resolvedType), span(span) {}
};
    struct AstFunctionType : public std::enable_shared_from_this<AstFunctionType> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionTypeParam>>> params;
    TypeAnnotation returnType;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    AstFunctionType(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<FunctionTypeParam>>> params, TypeAnnotation returnType, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), params(params), returnType(returnType), resolvedType(resolvedType), span(span) {}
};
    struct WeakType : public std::enable_shared_from_this<WeakType> {
    std::string kind;
    TypeAnnotation type_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    WeakType(std::string kind, TypeAnnotation type_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), type_(type_), resolvedType(resolvedType), span(span) {}
};
    struct FunctionTypeParam : public std::enable_shared_from_this<FunctionTypeParam> {
    std::string name;
    TypeAnnotation type_;
    SourceSpan span;
    FunctionTypeParam(std::string name, TypeAnnotation type_, SourceSpan span) : name(name), type_(type_), span(span) {}
};
    struct IntLiteral : public std::enable_shared_from_this<IntLiteral> {
    std::string kind;
    int32_t value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    IntLiteral(std::string kind, int32_t value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), resolvedType(resolvedType), span(span) {}
};
    struct LongLiteral : public std::enable_shared_from_this<LongLiteral> {
    std::string kind;
    int64_t value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    LongLiteral(std::string kind, int64_t value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), resolvedType(resolvedType), span(span) {}
};
    struct FloatLiteral : public std::enable_shared_from_this<FloatLiteral> {
    std::string kind;
    float value;
    std::string raw;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    FloatLiteral(std::string kind, float value, std::string raw, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), raw(raw), resolvedType(resolvedType), span(span) {}
};
    struct DoubleLiteral : public std::enable_shared_from_this<DoubleLiteral> {
    std::string kind;
    double value;
    std::string raw;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    DoubleLiteral(std::string kind, double value, std::string raw, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), raw(raw), resolvedType(resolvedType), span(span) {}
};
    struct StringLiteral : public std::enable_shared_from_this<StringLiteral> {
    std::string kind;
    std::string value;
    std::shared_ptr<std::vector<std::string>> parts;
    std::shared_ptr<std::vector<Expression>> interpolations;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    StringLiteral(std::string kind, std::string value, std::shared_ptr<std::vector<std::string>> parts, std::shared_ptr<std::vector<Expression>> interpolations, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), parts(parts), interpolations(interpolations), resolvedType(resolvedType), span(span) {}
};
    struct CharLiteral : public std::enable_shared_from_this<CharLiteral> {
    std::string kind;
    char32_t value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CharLiteral(std::string kind, char32_t value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), resolvedType(resolvedType), span(span) {}
};
    struct BoolLiteral : public std::enable_shared_from_this<BoolLiteral> {
    std::string kind;
    bool value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    BoolLiteral(std::string kind, bool value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), value(value), resolvedType(resolvedType), span(span) {}
};
    struct NoneLiteral : public std::enable_shared_from_this<NoneLiteral> {
    std::string kind;
    std::string sourceSpelling;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    NoneLiteral(std::string kind, std::string sourceSpelling, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), sourceSpelling(sourceSpelling), resolvedType(resolvedType), span(span) {}
};
    struct Identifier : public std::enable_shared_from_this<Identifier> {
    std::string kind;
    std::string name;
    doof_header_type_3 resolvedType;
    std::shared_ptr<::app_src_semantic_::Binding> resolvedBinding;
    SourceSpan span;
    Identifier(std::string kind, std::string name, doof_header_type_3 resolvedType, std::shared_ptr<::app_src_semantic_::Binding> resolvedBinding, SourceSpan span) : kind(kind), name(name), resolvedType(resolvedType), resolvedBinding(resolvedBinding), span(span) {}
};
    struct BinaryExpression : public std::enable_shared_from_this<BinaryExpression> {
    std::string kind;
    std::string operator_;
    Expression left;
    Expression right;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    BinaryExpression(std::string kind, std::string operator_, Expression left, Expression right, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), operator_(operator_), left(left), right(right), resolvedType(resolvedType), span(span) {}
};
    struct UnaryExpression : public std::enable_shared_from_this<UnaryExpression> {
    std::string kind;
    std::string operator_;
    Expression operand;
    bool prefix;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    UnaryExpression(std::string kind, std::string operator_, Expression operand, bool prefix, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), operator_(operator_), operand(operand), prefix(prefix), resolvedType(resolvedType), span(span) {}
};
    struct AssignmentExpression : public std::enable_shared_from_this<AssignmentExpression> {
    std::string kind;
    std::string operator_;
    Expression target;
    Expression value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    AssignmentExpression(std::string kind, std::string operator_, Expression target, Expression value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), operator_(operator_), target(target), value(value), resolvedType(resolvedType), span(span) {}
};
    struct MemberExpression : public std::enable_shared_from_this<MemberExpression> {
    std::string kind;
    Expression object;
    std::string property;
    bool optional;
    bool force;
    std::shared_ptr<ClassDeclaration> resolvedStaticOwner;
    bool resolvedNamespaceAccess;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedNamespaceSymbol;
    bool resolvedCallableField;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    MemberExpression(std::string kind, Expression object, std::string property, bool optional, bool force, std::shared_ptr<ClassDeclaration> resolvedStaticOwner, bool resolvedNamespaceAccess, std::shared_ptr<::app_src_semantic_::Symbol> resolvedNamespaceSymbol, bool resolvedCallableField, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), object(object), property(property), optional(optional), force(force), resolvedStaticOwner(resolvedStaticOwner), resolvedNamespaceAccess(resolvedNamespaceAccess), resolvedNamespaceSymbol(resolvedNamespaceSymbol), resolvedCallableField(resolvedCallableField), resolvedType(resolvedType), span(span) {}
};
    struct IndexExpression : public std::enable_shared_from_this<IndexExpression> {
    std::string kind;
    Expression object;
    Expression index;
    bool optional;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    IndexExpression(std::string kind, Expression object, Expression index, bool optional, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), object(object), index(index), optional(optional), resolvedType(resolvedType), span(span) {}
};
    struct CallArgument : public std::enable_shared_from_this<CallArgument> {
    std::optional<std::string> name;
    Expression value;
    SourceSpan span;
    CallArgument(std::optional<std::string> name, Expression value, SourceSpan span) : name(name), value(value), span(span) {}
};
    struct CallExpression : public std::enable_shared_from_this<CallExpression> {
    std::string kind;
    Expression callee;
    std::shared_ptr<std::vector<std::shared_ptr<CallArgument>>> args;
    std::shared_ptr<std::vector<TypeAnnotation>> typeArgs;
    std::shared_ptr<std::vector<doof_header_type_4>> resolvedGenericTypeArgs;
    std::shared_ptr<FunctionDeclaration> resolvedFunction;
    std::shared_ptr<FunctionDeclaration> resolvedConstructor;
    std::shared_ptr<ClassDeclaration> resolvedClass;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CallExpression(std::string kind, Expression callee, std::shared_ptr<std::vector<std::shared_ptr<CallArgument>>> args, std::shared_ptr<std::vector<TypeAnnotation>> typeArgs, std::shared_ptr<std::vector<doof_header_type_4>> resolvedGenericTypeArgs, std::shared_ptr<FunctionDeclaration> resolvedFunction, std::shared_ptr<FunctionDeclaration> resolvedConstructor, std::shared_ptr<ClassDeclaration> resolvedClass, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), callee(callee), args(args), typeArgs(typeArgs), resolvedGenericTypeArgs(resolvedGenericTypeArgs), resolvedFunction(resolvedFunction), resolvedConstructor(resolvedConstructor), resolvedClass(resolvedClass), resolvedType(resolvedType), span(span) {}
};
    struct ArrayLiteral : public std::enable_shared_from_this<ArrayLiteral> {
    std::string kind;
    std::shared_ptr<std::vector<Expression>> elements;
    bool readonly_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ArrayLiteral(std::string kind, std::shared_ptr<std::vector<Expression>> elements, bool readonly_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), elements(elements), readonly_(readonly_), resolvedType(resolvedType), span(span) {}
};
    struct ObjectProperty : public std::enable_shared_from_this<ObjectProperty> {
    std::string name;
    doof_header_type_5 key;
    doof_header_type_5 value;
    doof_header_type_3 resolvedType;
    std::shared_ptr<::app_src_semantic_::Binding> resolvedBinding;
    SourceSpan span;
    ObjectProperty(std::string name, doof_header_type_5 key, doof_header_type_5 value, doof_header_type_3 resolvedType, std::shared_ptr<::app_src_semantic_::Binding> resolvedBinding, SourceSpan span) : name(name), key(key), value(value), resolvedType(resolvedType), resolvedBinding(resolvedBinding), span(span) {}
};
    struct ObjectLiteral : public std::enable_shared_from_this<ObjectLiteral> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<ObjectProperty>>> properties;
    doof_header_type_5 spread;
    std::shared_ptr<ClassDeclaration> resolvedClass;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ObjectLiteral(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<ObjectProperty>>> properties, doof_header_type_5 spread, std::shared_ptr<ClassDeclaration> resolvedClass, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), properties(properties), spread(spread), resolvedClass(resolvedClass), resolvedType(resolvedType), span(span) {}
};
    struct TupleLiteral : public std::enable_shared_from_this<TupleLiteral> {
    std::string kind;
    std::shared_ptr<std::vector<Expression>> elements;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    TupleLiteral(std::string kind, std::shared_ptr<std::vector<Expression>> elements, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), elements(elements), resolvedType(resolvedType), span(span) {}
};
    struct LambdaExpression : public std::enable_shared_from_this<LambdaExpression> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<Parameter>>> params;
    doof_header_type_2 returnType;
    doof_header_type_6 body;
    bool parameterless;
    bool trailing;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    LambdaExpression(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<Parameter>>> params, doof_header_type_2 returnType, doof_header_type_6 body, bool parameterless, bool trailing, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), params(params), returnType(returnType), body(body), parameterless(parameterless), trailing(trailing), resolvedType(resolvedType), span(span) {}
};
    struct IfExpression : public std::enable_shared_from_this<IfExpression> {
    std::string kind;
    Expression condition;
    Expression then_;
    Expression else_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    IfExpression(std::string kind, Expression condition, Expression then_, Expression else_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), condition(condition), then_(then_), else_(else_), resolvedType(resolvedType), span(span) {}
};
    struct ConstructExpression : public std::enable_shared_from_this<ConstructExpression> {
    std::string kind;
    std::string type_;
    std::shared_ptr<std::vector<TypeAnnotation>> typeArgs;
    std::shared_ptr<std::vector<std::shared_ptr<ObjectProperty>>> args;
    bool named;
    std::shared_ptr<ClassDeclaration> resolvedClass;
    std::shared_ptr<FunctionDeclaration> resolvedConstructor;
    doof_header_type_3 resolvedConstructedType;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ConstructExpression(std::string kind, std::string type_, std::shared_ptr<std::vector<TypeAnnotation>> typeArgs, std::shared_ptr<std::vector<std::shared_ptr<ObjectProperty>>> args, bool named, std::shared_ptr<ClassDeclaration> resolvedClass, std::shared_ptr<FunctionDeclaration> resolvedConstructor, doof_header_type_3 resolvedConstructedType, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), type_(type_), typeArgs(typeArgs), args(args), named(named), resolvedClass(resolvedClass), resolvedConstructor(resolvedConstructor), resolvedConstructedType(resolvedConstructedType), resolvedType(resolvedType), span(span) {}
};
    struct DotShorthand : public std::enable_shared_from_this<DotShorthand> {
    std::string kind;
    std::string name;
    std::string resolvedShorthandOwnerName;
    std::string resolvedShorthandOwnerKind;
    std::string resolvedShorthandOwnerModule;
    bool resolvedShorthandOwnerNative;
    std::string resolvedShorthandOwnerCppName;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    DotShorthand(std::string kind, std::string name, std::string resolvedShorthandOwnerName, std::string resolvedShorthandOwnerKind, std::string resolvedShorthandOwnerModule, bool resolvedShorthandOwnerNative, std::string resolvedShorthandOwnerCppName, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), resolvedShorthandOwnerName(resolvedShorthandOwnerName), resolvedShorthandOwnerKind(resolvedShorthandOwnerKind), resolvedShorthandOwnerModule(resolvedShorthandOwnerModule), resolvedShorthandOwnerNative(resolvedShorthandOwnerNative), resolvedShorthandOwnerCppName(resolvedShorthandOwnerCppName), resolvedType(resolvedType), span(span) {}
};
    struct ThisExpression : public std::enable_shared_from_this<ThisExpression> {
    std::string kind;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ThisExpression(std::string kind, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), resolvedType(resolvedType), span(span) {}
};
    struct CallerExpression : public std::enable_shared_from_this<CallerExpression> {
    std::string kind;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CallerExpression(std::string kind, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), resolvedType(resolvedType), span(span) {}
};
    struct AsyncExpression : public std::enable_shared_from_this<AsyncExpression> {
    std::string kind;
    doof_header_type_6 expression;
    std::shared_ptr<std::vector<std::string>> resolvedCaptureNames;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    AsyncExpression(std::string kind, doof_header_type_6 expression, std::shared_ptr<std::vector<std::string>> resolvedCaptureNames, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), expression(expression), resolvedCaptureNames(resolvedCaptureNames), resolvedType(resolvedType), span(span) {}
};
    struct RetireExpression : public std::enable_shared_from_this<RetireExpression> {
    std::string kind;
    Expression actor;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    RetireExpression(std::string kind, Expression actor, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), actor(actor), resolvedType(resolvedType), span(span) {}
};
    struct AsExpression : public std::enable_shared_from_this<AsExpression> {
    std::string kind;
    Expression expression;
    TypeAnnotation targetType;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    AsExpression(std::string kind, Expression expression, TypeAnnotation targetType, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), expression(expression), targetType(targetType), resolvedType(resolvedType), span(span) {}
};
    struct ActorCreationExpression : public std::enable_shared_from_this<ActorCreationExpression> {
    std::string kind;
    std::string className;
    std::shared_ptr<std::vector<Expression>> args;
    std::shared_ptr<FunctionDeclaration> resolvedConstructor;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    ActorCreationExpression(std::string kind, std::string className, std::shared_ptr<std::vector<Expression>> args, std::shared_ptr<FunctionDeclaration> resolvedConstructor, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), className(className), args(args), resolvedConstructor(resolvedConstructor), resolvedType(resolvedType), span(span) {}
};
    struct YieldBlockExpression : public std::enable_shared_from_this<YieldBlockExpression> {
    std::string kind;
    std::shared_ptr<Block> body;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    YieldBlockExpression(std::string kind, std::shared_ptr<Block> body, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), body(body), resolvedType(resolvedType), span(span) {}
};
    struct CatchExpression : public std::enable_shared_from_this<CatchExpression> {
    std::string kind;
    std::shared_ptr<Block> body;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CatchExpression(std::string kind, std::shared_ptr<Block> body, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), body(body), resolvedType(resolvedType), span(span) {}
};
    struct Parameter : public std::enable_shared_from_this<Parameter> {
    std::string name;
    std::string description;
    doof_header_type_2 type_;
    doof_header_type_5 defaultValue;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    Parameter(std::string name, std::string description, doof_header_type_2 type_, doof_header_type_5 defaultValue, doof_header_type_3 resolvedType, SourceSpan span) : name(name), description(description), type_(type_), defaultValue(defaultValue), resolvedType(resolvedType), span(span) {}
};
    struct Block : public std::enable_shared_from_this<Block> {
    std::string kind;
    std::shared_ptr<std::vector<Statement>> statements;
    SourceSpan span;
    Block(std::string kind, std::shared_ptr<std::vector<Statement>> statements, SourceSpan span) : kind(kind), statements(statements), span(span) {}
};
    struct ConstDeclaration : public std::enable_shared_from_this<ConstDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    doof_header_type_2 type_;
    Expression value;
    bool exported;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    ConstDeclaration(std::string kind, std::string name, std::string description, doof_header_type_2 type_, Expression value, bool exported, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), name(name), description(description), type_(type_), value(value), exported(exported), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct ReadonlyDeclaration : public std::enable_shared_from_this<ReadonlyDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    doof_header_type_2 type_;
    Expression value;
    bool exported;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    ReadonlyDeclaration(std::string kind, std::string name, std::string description, doof_header_type_2 type_, Expression value, bool exported, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), name(name), description(description), type_(type_), value(value), exported(exported), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct ImmutableBinding : public std::enable_shared_from_this<ImmutableBinding> {
    std::string kind;
    std::string name;
    doof_header_type_2 type_;
    Expression value;
    bool exported;
    std::shared_ptr<Block> else_;
    std::optional<std::string> failureName;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    ImmutableBinding(std::string kind, std::string name, doof_header_type_2 type_, Expression value, bool exported, std::shared_ptr<Block> else_, std::optional<std::string> failureName, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), name(name), type_(type_), value(value), exported(exported), else_(else_), failureName(failureName), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct LetDeclaration : public std::enable_shared_from_this<LetDeclaration> {
    std::string kind;
    std::string name;
    doof_header_type_2 type_;
    Expression value;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    LetDeclaration(std::string kind, std::string name, doof_header_type_2 type_, Expression value, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), name(name), type_(type_), value(value), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct FunctionDeclaration : public std::enable_shared_from_this<FunctionDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints;
    std::shared_ptr<std::vector<std::shared_ptr<Parameter>>> params;
    doof_header_type_2 returnType;
    doof_header_type_6 body;
    bool exported;
    bool static_;
    bool isolated_;
    bool resolvedIsolated;
    bool private_;
    bool bodyless;
    bool native_;
    std::string nativeHeader;
    std::string nativeCppName;
    std::optional<SourceSpan> legacyMethodFunctionSpan;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    FunctionDeclaration(std::string kind, std::string name, std::string description, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints, std::shared_ptr<std::vector<std::shared_ptr<Parameter>>> params, doof_header_type_2 returnType, doof_header_type_6 body, bool exported, bool static_, bool isolated_, bool resolvedIsolated, bool private_, bool bodyless, bool native_, std::string nativeHeader, std::string nativeCppName, std::optional<SourceSpan> legacyMethodFunctionSpan, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), description(description), typeParams(typeParams), typeParamConstraints(typeParamConstraints), params(params), returnType(returnType), body(body), exported(exported), static_(static_), isolated_(isolated_), resolvedIsolated(resolvedIsolated), private_(private_), bodyless(bodyless), native_(native_), nativeHeader(nativeHeader), nativeCppName(nativeCppName), legacyMethodFunctionSpan(legacyMethodFunctionSpan), resolvedType(resolvedType), span(span) {}
};
    struct ReturnStatement : public std::enable_shared_from_this<ReturnStatement> {
    std::string kind;
    doof_header_type_5 value;
    doof_header_type_3 resolvedExpectedType;
    SourceSpan span;
    ReturnStatement(std::string kind, doof_header_type_5 value, doof_header_type_3 resolvedExpectedType, SourceSpan span) : kind(kind), value(value), resolvedExpectedType(resolvedExpectedType), span(span) {}
};
    struct YieldStatement : public std::enable_shared_from_this<YieldStatement> {
    std::string kind;
    Expression value;
    SourceSpan span;
    YieldStatement(std::string kind, Expression value, SourceSpan span) : kind(kind), value(value), span(span) {}
};
    struct YieldBlockAssignmentStatement : public std::enable_shared_from_this<YieldBlockAssignmentStatement> {
    std::string kind;
    std::string name;
    std::shared_ptr<YieldBlockExpression> value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    YieldBlockAssignmentStatement(std::string kind, std::string name, std::shared_ptr<YieldBlockExpression> value, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), value(value), resolvedType(resolvedType), span(span) {}
};
    struct IfStatement : public std::enable_shared_from_this<IfStatement> {
    std::string kind;
    Expression condition;
    std::shared_ptr<Block> body;
    std::shared_ptr<std::vector<std::shared_ptr<IfBranch>>> elseIfs;
    std::shared_ptr<Block> else_;
    SourceSpan span;
    IfStatement(std::string kind, Expression condition, std::shared_ptr<Block> body, std::shared_ptr<std::vector<std::shared_ptr<IfBranch>>> elseIfs, std::shared_ptr<Block> else_, SourceSpan span) : kind(kind), condition(condition), body(body), elseIfs(elseIfs), else_(else_), span(span) {}
};
    struct CaseExpression : public std::enable_shared_from_this<CaseExpression> {
    std::string kind;
    Expression subject;
    std::shared_ptr<std::vector<std::shared_ptr<CaseExpressionArm>>> arms;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    CaseExpression(std::string kind, Expression subject, std::shared_ptr<std::vector<std::shared_ptr<CaseExpressionArm>>> arms, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), subject(subject), arms(arms), resolvedType(resolvedType), span(span) {}
};
    struct CaseStatement : public std::enable_shared_from_this<CaseStatement> {
    std::string kind;
    Expression subject;
    std::shared_ptr<std::vector<std::shared_ptr<CaseArm>>> arms;
    std::optional<bool> resolvedCompletes;
    SourceSpan span;
    CaseStatement(std::string kind, Expression subject, std::shared_ptr<std::vector<std::shared_ptr<CaseArm>>> arms, std::optional<bool> resolvedCompletes, SourceSpan span) : kind(kind), subject(subject), arms(arms), resolvedCompletes(resolvedCompletes), span(span) {}
};
    struct CaseArm : public std::enable_shared_from_this<CaseArm> {
    std::string kind;
    std::shared_ptr<std::vector<CasePattern>> patterns;
    doof_header_type_6 body;
    SourceSpan span;
    CaseArm(std::string kind, std::shared_ptr<std::vector<CasePattern>> patterns, doof_header_type_6 body, SourceSpan span) : kind(kind), patterns(patterns), body(body), span(span) {}
};
    struct CaseExpressionArm : public std::enable_shared_from_this<CaseExpressionArm> {
    std::string kind;
    std::shared_ptr<std::vector<CasePattern>> patterns;
    doof_header_type_6 body;
    SourceSpan span;
    CaseExpressionArm(std::string kind, std::shared_ptr<std::vector<CasePattern>> patterns, doof_header_type_6 body, SourceSpan span) : kind(kind), patterns(patterns), body(body), span(span) {}
};
    struct TypePattern : public std::enable_shared_from_this<TypePattern> {
    std::string kind;
    std::string name;
    TypeAnnotation type_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    TypePattern(std::string kind, std::string name, TypeAnnotation type_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), type_(type_), resolvedType(resolvedType), span(span) {}
};
    struct WildcardPattern : public std::enable_shared_from_this<WildcardPattern> {
    std::string kind;
    SourceSpan span;
    WildcardPattern(std::string kind, SourceSpan span) : kind(kind), span(span) {}
};
    struct ValuePattern : public std::enable_shared_from_this<ValuePattern> {
    std::string kind;
    Expression value;
    SourceSpan span;
    ValuePattern(std::string kind, Expression value, SourceSpan span) : kind(kind), value(value), span(span) {}
};
    struct RangePattern : public std::enable_shared_from_this<RangePattern> {
    std::string kind;
    doof_header_type_5 start;
    doof_header_type_5 end;
    bool inclusive;
    SourceSpan span;
    RangePattern(std::string kind, doof_header_type_5 start, doof_header_type_5 end, bool inclusive, SourceSpan span) : kind(kind), start(start), end(end), inclusive(inclusive), span(span) {}
};
    struct IfBranch : public std::enable_shared_from_this<IfBranch> {
    Expression condition;
    std::shared_ptr<Block> body;
    SourceSpan span;
    IfBranch(Expression condition, std::shared_ptr<Block> body, SourceSpan span) : condition(condition), body(body), span(span) {}
};
    struct WhileStatement : public std::enable_shared_from_this<WhileStatement> {
    std::string kind;
    Expression condition;
    std::shared_ptr<Block> body;
    std::optional<std::string> label;
    std::shared_ptr<Block> then_;
    SourceSpan span;
    WhileStatement(std::string kind, Expression condition, std::shared_ptr<Block> body, std::optional<std::string> label, std::shared_ptr<Block> then_, SourceSpan span) : kind(kind), condition(condition), body(body), label(label), then_(then_), span(span) {}
};
    struct ForStatement : public std::enable_shared_from_this<ForStatement> {
    std::string kind;
    doof_header_type_7 init;
    doof_header_type_5 condition;
    std::shared_ptr<std::vector<Expression>> update;
    std::shared_ptr<Block> body;
    std::optional<std::string> label;
    std::shared_ptr<Block> then_;
    SourceSpan span;
    ForStatement(std::string kind, doof_header_type_7 init, doof_header_type_5 condition, std::shared_ptr<std::vector<Expression>> update, std::shared_ptr<Block> body, std::optional<std::string> label, std::shared_ptr<Block> then_, SourceSpan span) : kind(kind), init(init), condition(condition), update(update), body(body), label(label), then_(then_), span(span) {}
};
    struct ForOfStatement : public std::enable_shared_from_this<ForOfStatement> {
    std::string kind;
    std::shared_ptr<std::vector<std::string>> bindings;
    Expression iterable;
    std::shared_ptr<Block> body;
    std::optional<std::string> label;
    std::shared_ptr<Block> then_;
    SourceSpan span;
    ForOfStatement(std::string kind, std::shared_ptr<std::vector<std::string>> bindings, Expression iterable, std::shared_ptr<Block> body, std::optional<std::string> label, std::shared_ptr<Block> then_, SourceSpan span) : kind(kind), bindings(bindings), iterable(iterable), body(body), label(label), then_(then_), span(span) {}
};
    struct WithBinding : public std::enable_shared_from_this<WithBinding> {
    std::string name;
    doof_header_type_2 type_;
    Expression value;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    WithBinding(std::string name, doof_header_type_2 type_, Expression value, doof_header_type_3 resolvedType, SourceSpan span) : name(name), type_(type_), value(value), resolvedType(resolvedType), span(span) {}
};
    struct WithStatement : public std::enable_shared_from_this<WithStatement> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<WithBinding>>> bindings;
    std::shared_ptr<Block> body;
    SourceSpan span;
    WithStatement(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<WithBinding>>> bindings, std::shared_ptr<Block> body, SourceSpan span) : kind(kind), bindings(bindings), body(body), span(span) {}
};
    struct BreakStatement : public std::enable_shared_from_this<BreakStatement> {
    std::string kind;
    std::optional<std::string> label;
    SourceSpan span;
    BreakStatement(std::string kind, std::optional<std::string> label, SourceSpan span) : kind(kind), label(label), span(span) {}
};
    struct ContinueStatement : public std::enable_shared_from_this<ContinueStatement> {
    std::string kind;
    std::optional<std::string> label;
    SourceSpan span;
    ContinueStatement(std::string kind, std::optional<std::string> label, SourceSpan span) : kind(kind), label(label), span(span) {}
};
    struct ExpressionStatement : public std::enable_shared_from_this<ExpressionStatement> {
    std::string kind;
    Expression expression;
    SourceSpan span;
    ExpressionStatement(std::string kind, Expression expression, SourceSpan span) : kind(kind), expression(expression), span(span) {}
};
    struct DestructuringStatement : public std::enable_shared_from_this<DestructuringStatement> {
    std::string kind;
    std::shared_ptr<std::vector<std::string>> bindings;
    std::shared_ptr<std::vector<std::shared_ptr<DestructureBinding>>> namedBindings;
    std::string bindingKind;
    Expression value;
    SourceSpan span;
    DestructuringStatement(std::string kind, std::shared_ptr<std::vector<std::string>> bindings, std::shared_ptr<std::vector<std::shared_ptr<DestructureBinding>>> namedBindings, std::string bindingKind, Expression value, SourceSpan span) : kind(kind), bindings(bindings), namedBindings(namedBindings), bindingKind(bindingKind), value(value), span(span) {}
};
    struct DestructureBinding : public std::enable_shared_from_this<DestructureBinding> {
    std::string name;
    std::optional<std::string> alias;
    SourceSpan span;
    DestructureBinding(std::string name, std::optional<std::string> alias, SourceSpan span) : name(name), alias(alias), span(span) {}
};
    struct TryStatement : public std::enable_shared_from_this<TryStatement> {
    std::string kind;
    doof_header_type_8 binding;
    SourceSpan span;
    TryStatement(std::string kind, doof_header_type_8 binding, SourceSpan span) : kind(kind), binding(binding), span(span) {}
};
    struct ClassDeclaration : public std::enable_shared_from_this<ClassDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    bool struct_;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints;
    std::shared_ptr<std::vector<std::shared_ptr<NamedType>>> implements_;
    std::shared_ptr<std::vector<std::shared_ptr<ClassField>>> fields;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionDeclaration>>> methods;
    std::shared_ptr<Block> destructor_;
    bool exported;
    bool private_;
    bool native_;
    std::string nativeHeader;
    std::string nativeCppName;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol;
    bool needsMetadata;
    SourceSpan span;
    ClassDeclaration(std::string kind, std::string name, std::string description, bool struct_, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints, std::shared_ptr<std::vector<std::shared_ptr<NamedType>>> implements_, std::shared_ptr<std::vector<std::shared_ptr<ClassField>>> fields, std::shared_ptr<std::vector<std::shared_ptr<FunctionDeclaration>>> methods, std::shared_ptr<Block> destructor_, bool exported, bool private_, bool native_, std::string nativeHeader, std::string nativeCppName, std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol, bool needsMetadata, SourceSpan span) : kind(kind), name(name), description(description), struct_(struct_), typeParams(typeParams), typeParamConstraints(typeParamConstraints), implements_(implements_), fields(fields), methods(methods), destructor_(destructor_), exported(exported), private_(private_), native_(native_), nativeHeader(nativeHeader), nativeCppName(nativeCppName), resolvedSymbol(resolvedSymbol), needsMetadata(needsMetadata), span(span) {}
};
    struct ClassField : public std::enable_shared_from_this<ClassField> {
    std::string kind;
    std::shared_ptr<std::vector<std::string>> names;
    std::shared_ptr<std::vector<std::string>> descriptions;
    doof_header_type_2 type_;
    doof_header_type_5 defaultValue;
    bool static_;
    bool const_;
    bool let_;
    bool readonly_;
    bool weak_;
    bool private_;
    doof_header_type_3 resolvedType;
    bool moduleInitializerChecked;
    SourceSpan span;
    ClassField(std::string kind, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::string>> descriptions, doof_header_type_2 type_, doof_header_type_5 defaultValue, bool static_, bool const_, bool let_, bool readonly_, bool weak_, bool private_, doof_header_type_3 resolvedType, bool moduleInitializerChecked, SourceSpan span) : kind(kind), names(names), descriptions(descriptions), type_(type_), defaultValue(defaultValue), static_(static_), const_(const_), let_(let_), readonly_(readonly_), weak_(weak_), private_(private_), resolvedType(resolvedType), moduleInitializerChecked(moduleInitializerChecked), span(span) {}
};
    struct InterfaceDeclaration : public std::enable_shared_from_this<InterfaceDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints;
    std::shared_ptr<std::vector<std::shared_ptr<InterfaceField>>> fields;
    std::shared_ptr<std::vector<std::shared_ptr<FunctionDeclaration>>> methods;
    bool exported;
    std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol;
    bool needsJson;
    SourceSpan span;
    InterfaceDeclaration(std::string kind, std::string name, std::string description, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints, std::shared_ptr<std::vector<std::shared_ptr<InterfaceField>>> fields, std::shared_ptr<std::vector<std::shared_ptr<FunctionDeclaration>>> methods, bool exported, std::shared_ptr<::app_src_semantic_::Symbol> resolvedSymbol, bool needsJson, SourceSpan span) : kind(kind), name(name), description(description), typeParams(typeParams), typeParamConstraints(typeParamConstraints), fields(fields), methods(methods), exported(exported), resolvedSymbol(resolvedSymbol), needsJson(needsJson), span(span) {}
};
    struct InterfaceField : public std::enable_shared_from_this<InterfaceField> {
    std::string kind;
    std::string name;
    std::string description;
    TypeAnnotation type_;
    bool let_;
    bool readonly_;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    InterfaceField(std::string kind, std::string name, std::string description, TypeAnnotation type_, bool let_, bool readonly_, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), description(description), type_(type_), let_(let_), readonly_(readonly_), resolvedType(resolvedType), span(span) {}
};
    struct EnumDeclaration : public std::enable_shared_from_this<EnumDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<std::shared_ptr<EnumVariant>>> variants;
    bool exported;
    SourceSpan span;
    EnumDeclaration(std::string kind, std::string name, std::string description, std::shared_ptr<std::vector<std::shared_ptr<EnumVariant>>> variants, bool exported, SourceSpan span) : kind(kind), name(name), description(description), variants(variants), exported(exported), span(span) {}
};
    struct EnumVariant : public std::enable_shared_from_this<EnumVariant> {
    std::string kind;
    std::string name;
    std::string description;
    doof_header_type_5 value;
    SourceSpan span;
    EnumVariant(std::string kind, std::string name, std::string description, doof_header_type_5 value, SourceSpan span) : kind(kind), name(name), description(description), value(value), span(span) {}
};
    struct TypeAliasDeclaration : public std::enable_shared_from_this<TypeAliasDeclaration> {
    std::string kind;
    std::string name;
    std::string description;
    std::shared_ptr<std::vector<std::string>> typeParams;
    std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints;
    TypeAnnotation type_;
    bool exported;
    doof_header_type_3 resolvedType;
    SourceSpan span;
    TypeAliasDeclaration(std::string kind, std::string name, std::string description, std::shared_ptr<std::vector<std::string>> typeParams, std::shared_ptr<std::vector<std::shared_ptr<TypeParameterConstraint>>> typeParamConstraints, TypeAnnotation type_, bool exported, doof_header_type_3 resolvedType, SourceSpan span) : kind(kind), name(name), description(description), typeParams(typeParams), typeParamConstraints(typeParamConstraints), type_(type_), exported(exported), resolvedType(resolvedType), span(span) {}
};
    struct NamedImport : public std::enable_shared_from_this<NamedImport> {
    std::string kind;
    std::string name;
    std::optional<std::string> alias;
    SourceSpan span;
    NamedImport(std::string kind, std::string name, std::optional<std::string> alias, SourceSpan span) : kind(kind), name(name), alias(alias), span(span) {}
};
    struct NamespaceImport : public std::enable_shared_from_this<NamespaceImport> {
    std::string kind;
    std::string alias;
    SourceSpan span;
    NamespaceImport(std::string kind, std::string alias, SourceSpan span) : kind(kind), alias(alias), span(span) {}
};
    struct ImportDeclaration : public std::enable_shared_from_this<ImportDeclaration> {
    std::string kind;
    std::shared_ptr<std::vector<ImportSpecifier>> specifiers;
    std::string source;
    bool typeOnly;
    SourceSpan span;
    ImportDeclaration(std::string kind, std::shared_ptr<std::vector<ImportSpecifier>> specifiers, std::string source, bool typeOnly, SourceSpan span) : kind(kind), specifiers(specifiers), source(source), typeOnly(typeOnly), span(span) {}
};
    struct MockImportMapping : public std::enable_shared_from_this<MockImportMapping> {
    std::string dependency;
    std::string replacement;
    SourceSpan span;
    MockImportMapping(std::string dependency, std::string replacement, SourceSpan span) : dependency(dependency), replacement(replacement), span(span) {}
};
    struct MockImportDirective : public std::enable_shared_from_this<MockImportDirective> {
    std::string kind;
    std::string sourcePattern;
    std::shared_ptr<std::vector<std::shared_ptr<MockImportMapping>>> mappings;
    SourceSpan span;
    MockImportDirective(std::string kind, std::string sourcePattern, std::shared_ptr<std::vector<std::shared_ptr<MockImportMapping>>> mappings, SourceSpan span) : kind(kind), sourcePattern(sourcePattern), mappings(mappings), span(span) {}
};
    struct ExportDeclaration : public std::enable_shared_from_this<ExportDeclaration> {
    std::string kind;
    Statement declaration;
    SourceSpan span;
    ExportDeclaration(std::string kind, Statement declaration, SourceSpan span) : kind(kind), declaration(declaration), span(span) {}
};
    struct ExportSpecifier : public std::enable_shared_from_this<ExportSpecifier> {
    std::string name;
    std::optional<std::string> alias;
    SourceSpan span;
    ExportSpecifier(std::string name, std::optional<std::string> alias, SourceSpan span) : name(name), alias(alias), span(span) {}
};
    struct ExportList : public std::enable_shared_from_this<ExportList> {
    std::string kind;
    std::shared_ptr<std::vector<std::shared_ptr<ExportSpecifier>>> specifiers;
    std::optional<std::string> source;
    SourceSpan span;
    ExportList(std::string kind, std::shared_ptr<std::vector<std::shared_ptr<ExportSpecifier>>> specifiers, std::optional<std::string> source, SourceSpan span) : kind(kind), specifiers(specifiers), source(source), span(span) {}
};
    struct Program : public std::enable_shared_from_this<Program> {
    std::string kind;
    std::shared_ptr<std::vector<Statement>> statements;
    SourceSpan span;
    Program(std::string kind, std::shared_ptr<std::vector<Statement>> statements, SourceSpan span) : kind(kind), statements(statements), span(span) {}
};
}

namespace app_src_analyzer_ {
    std::shared_ptr<ModuleAnalyzer> createAnalyzerWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader);
}

namespace app_src_emitter_names_ {
    void configureModuleNamespaces(const std::shared_ptr<std::vector<std::shared_ptr<ModuleNamespaceMapping>>>& mappings);
}

namespace app_src_emitter_monomorphize_ {
    std::shared_ptr<InstantiationPlan> buildInstantiationPlan(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result);
}

namespace app_src_emitter_module_ {
    std::shared_ptr<ModuleGraphEmission> emitModuleGraph(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::shared_ptr<ModuleEmissionCacheKey>>>& reusableModules, const std::string& configurationFingerprint, bool physicalSourcePaths);
}

namespace app_src_emitter_wasm_ {
    doof::Result<std::shared_ptr<WasmEmission>, std::string> emitWasmSupport(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::shared_ptr<::app_src_emitter_monomorphize_::InstantiationPlan>& instantiations);
}

namespace app_src_checker_ {
    std::shared_ptr<ModuleChecker> createChecker(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& entry, const std::string& entryMode);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateCheckedTypes(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateIsolationEffects(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateDeepReadonlyFields(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result);
}

namespace app_src_diagnostics_ {
    bool hasErrorDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics);
}

namespace app_src_compiler_ {
    std::shared_ptr<Compilation> compile(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, bool coverage);
    std::shared_ptr<Compilation> compileWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules, const std::string& emissionConfigurationFingerprint, bool physicalSourcePaths);
    std::shared_ptr<Compilation> checkWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::string& entryMode);
    std::shared_ptr<Compilation> compileInternal(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::string& entryMode, bool coverage, bool emit, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules, const std::string& emissionConfigurationFingerprint, bool physicalSourcePaths);
    void checkModuleDependencies(const std::string& path, const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& analysis, const std::shared_ptr<::app_src_checker_::ModuleChecker>& checker, const std::shared_ptr<std::vector<std::string>>& checkedPaths, const std::shared_ptr<std::vector<std::string>>& visitingPaths, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics);
    bool containsPath(const std::shared_ptr<std::vector<std::string>>& paths, const std::string& path);
    std::shared_ptr<::app_src_analyzer_::ModuleInfo> findAnalysisModule(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::string& path);
}
