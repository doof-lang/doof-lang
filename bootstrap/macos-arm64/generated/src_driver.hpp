#pragma once
#include "doof_runtime.hpp"
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }
namespace std_::fs::types { enum class IoError; }
namespace std_::fs::types { struct FileInfo; }
namespace std_::fs::types { enum class EntryKind; }
namespace app_src_compiler_ { struct Compilation; }
namespace app_src_cli_ { struct CliRequest; }
namespace app_src_external_dependency_ { struct ExternalDependencyTarget; }
namespace app_src_dependency_policy_ { struct ReachedPackageInput; }
namespace app_src_dependency_policy_ { struct ResolvedExternalInput; }
namespace app_src_emitter_project_ { struct NativePackageInput; }
namespace app_src_emitter_project_ { struct ProjectEmission; }
namespace app_src_emitter_names_ { struct ModuleNamespaceMapping; }
namespace app_src_emitter_module_ { struct ModuleEmission; }
namespace app_src_emitter_module_ { struct ModuleEmissionCacheKey; }
namespace app_src_emitter_module_ { struct ModuleGraphEmission; }
namespace app_src_frontend_cache_ { struct FrontendCacheState; }
namespace app_src_frontend_cache_ { struct FrontendFileInput; }
namespace app_src_frontend_cache_ { struct FrontendModuleOutput; }
namespace app_src_frontend_cache_ { struct FrontendSourceProbe; }
namespace app_src_module_acquisition_ { struct ModuleAcquisition; }
namespace app_src_native_build_driver_ { enum class NativeBuildOutputMode; }
namespace app_src_native_build_ { enum class NativeBuildMode; }
namespace app_src_package_manifest_ { struct ExternalDependency; }
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace app_src_package_manifest_ { struct PackageDependency; }
namespace app_src_package_manifest_ { struct PackageManifest; }
namespace app_src_package_manifest_ { struct PackageResource; }
namespace app_src_package_acquisition_ { struct ExactPackageSource; }
namespace app_src_parser_ { struct Parser; }
namespace app_src_resource_state_ { struct MaterializedResource; }
namespace app_src_resource_state_ { struct ResourceState; }
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct SemanticLocation; }
namespace app_src_semantic_ { struct SemanticSpan; }
namespace app_src_semantic_ { struct SourceFile; }
namespace app_src_std_catalog_ { struct StdCatalog; }
namespace app_src_emitter_module_ { struct CoverageModuleMetadata; }
namespace app_src_test_runner_ { struct CoverageReport; }
namespace app_src_test_runner_ { struct DiscoveredTest; }
namespace std_::fs::types { enum class EntryKind; }
namespace std_::os::index { struct ExecOptions; }
namespace std_::os::index { enum class ProcessGroupMode; }
namespace std_::time::temporal { struct Instant; }

namespace app_src_semantic_ {
    struct SemanticLocation;
    struct SemanticSpan;
    struct Diagnostic;
    struct Symbol;
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
    struct Binding;
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

namespace app_src_emitter_names_ {
    struct ModuleNamespaceMapping;
}

namespace std_::blob::index {
}

namespace app_src_emitter_module_ {
    struct ModuleEmission;
    struct ModuleEmissionCacheKey;
    struct CoverageModuleMetadata;
    struct ModuleGraphEmission;
}

namespace app_src_compiler_ {
    struct Compilation;
}

namespace app_src_lexer_ {
    struct Token;
}

namespace app_src_parser_ {
    struct Parser;
}

namespace app_src_cli_ {
    struct CliRequest;
    struct CliParseResult;
}

namespace app_src_macos_app_ {
    struct MacOSAppResource;
    struct MacOSEmbeddedLibrary;
    struct MacOSAppConfig;
    struct MacOSPackageConfig;
}

namespace app_src_ios_app_ {
    struct IOSAppResource;
    struct IOSEmbeddedLibrary;
    struct IOSAppConfig;
    struct IOSPackageConfig;
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan;
    struct PackageResource;
    struct ExternalDependencyCopyFile;
    struct ExternalDependencyCommand;
    struct ExternalDependency;
    struct PackageDependency;
    struct DependencyResolution;
    struct DependencyPolicy;
    struct PackageManifest;
}

namespace std_::fs::types {
    struct FileInfo;
}

namespace std_::os::index {
    struct ExecOptions;
    struct ExecResult;
}

namespace app_src_external_dependency_ {
    struct ExternalDependencyTarget;
}

namespace std_::time::duration {
    struct Duration;
}

namespace std_::time::temporal {
    struct Instant;
    struct Date;
    struct Time;
    struct DateTime;
    struct TimeZone;
    struct ZonedDateTime;
}

namespace app_src_std_catalog_ {
    struct StdCatalogPackage;
    struct StdCatalog;
}

namespace app_src_dependency_policy_ {
    struct ReachedPackageInput;
    struct ResolvedExternalInput;
}

namespace app_src_emitter_project_ {
    struct NativePackageInput;
    struct ProjectNativeCopy;
    struct ProjectSupportFile;
    struct ProjectEmission;
}

namespace app_src_frontend_cache_ {
    struct FrontendSourceProbe;
    struct FrontendFileInput;
    struct FrontendModuleOutput;
    struct FrontendCacheState;
    extern int32_t FRONTEND_SEMANTIC_ABI;
}

namespace app_src_module_acquisition_ {
    struct ModuleAcquisition;
}

namespace app_src_package_acquisition_ {
    struct ExactPackageSource;
    struct AcquiredPackage;
}

namespace app_src_ios_device_ {
    struct IOSDeviceSigningOptions;
}

namespace app_src_project_ {
    struct ProjectSpec;
}

namespace app_src_run_command_ {
    struct RunInvocation;
}

namespace app_src_resource_state_ {
    struct MaterializedResource;
    struct ResourceState;
}

namespace app_src_test_runner_ {
    struct CoverageFileReport;
    struct CoverageReport;
    struct DiscoveredTest;
    struct TestCompilationGroup;
    struct TestDiscovery;
}

namespace app_src_wasm_test_runner_ {
    struct WasmTestRunnerPlan;
}

namespace app_src_driver_ {
    struct NativeCommandResult;
    struct TestExecutionResult;
    struct TestWorkerCompletion;
    struct TestProcessWorker;
    struct DriverSourceRoot;
    struct DriverReachedPackage;
    struct DriverAcquiredSource;
    struct DriverSourceState;
    extern int32_t MAX_PRINTED_DIAGNOSTICS;
    extern int64_t MAX_NATIVE_COMPILER_OUTPUT_BYTES;
    extern int64_t MAX_COVERAGE_OUTPUT_BYTES;
    extern std::shared_ptr<DriverSourceState> configuredDriverSourceState;
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

namespace app_src_parser_ {
    using doof_header_type_9 = std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>>;
    using doof_header_type_10 = std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>;
}

namespace std_::blob::types {
    enum class Endian {
    BigEndian = 0,
    LittleEndian = 1
};
inline const char* Endian_name(Endian value) {
  switch (value) {
    case Endian::BigEndian: return "BigEndian";
    case Endian::LittleEndian: return "LittleEndian";
  }
  return "";
}
inline std::optional<Endian> Endian_fromName(std::string_view value) {
  if (value == "BigEndian") return Endian::BigEndian;
  if (value == "LittleEndian") return Endian::LittleEndian;
  return std::nullopt;
}
inline std::optional<Endian> Endian_fromValue(int32_t value) {
  switch (static_cast<Endian>(value)) {
    case Endian::BigEndian: return Endian::BigEndian;
    case Endian::LittleEndian: return Endian::LittleEndian;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, Endian value) { return output << Endian_name(value); }
    enum class TextEncoding {
    Utf8 = 0,
    Utf16LE = 1,
    Utf16BE = 2,
    Latin1 = 3,
    Windows1252 = 4,
    CP437 = 5,
    Ascii = 6
};
inline const char* TextEncoding_name(TextEncoding value) {
  switch (value) {
    case TextEncoding::Utf8: return "Utf8";
    case TextEncoding::Utf16LE: return "Utf16LE";
    case TextEncoding::Utf16BE: return "Utf16BE";
    case TextEncoding::Latin1: return "Latin1";
    case TextEncoding::Windows1252: return "Windows1252";
    case TextEncoding::CP437: return "CP437";
    case TextEncoding::Ascii: return "Ascii";
  }
  return "";
}
inline std::optional<TextEncoding> TextEncoding_fromName(std::string_view value) {
  if (value == "Utf8") return TextEncoding::Utf8;
  if (value == "Utf16LE") return TextEncoding::Utf16LE;
  if (value == "Utf16BE") return TextEncoding::Utf16BE;
  if (value == "Latin1") return TextEncoding::Latin1;
  if (value == "Windows1252") return TextEncoding::Windows1252;
  if (value == "CP437") return TextEncoding::CP437;
  if (value == "Ascii") return TextEncoding::Ascii;
  return std::nullopt;
}
inline std::optional<TextEncoding> TextEncoding_fromValue(int32_t value) {
  switch (static_cast<TextEncoding>(value)) {
    case TextEncoding::Utf8: return TextEncoding::Utf8;
    case TextEncoding::Utf16LE: return TextEncoding::Utf16LE;
    case TextEncoding::Utf16BE: return TextEncoding::Utf16BE;
    case TextEncoding::Latin1: return TextEncoding::Latin1;
    case TextEncoding::Windows1252: return TextEncoding::Windows1252;
    case TextEncoding::CP437: return TextEncoding::CP437;
    case TextEncoding::Ascii: return TextEncoding::Ascii;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, TextEncoding value) { return output << TextEncoding_name(value); }
    enum class EncodingError {
    InvalidData = 0,
    UnrepresentableCharacter = 1,
    OutputTooLarge = 2
};
inline const char* EncodingError_name(EncodingError value) {
  switch (value) {
    case EncodingError::InvalidData: return "InvalidData";
    case EncodingError::UnrepresentableCharacter: return "UnrepresentableCharacter";
    case EncodingError::OutputTooLarge: return "OutputTooLarge";
  }
  return "";
}
inline std::optional<EncodingError> EncodingError_fromName(std::string_view value) {
  if (value == "InvalidData") return EncodingError::InvalidData;
  if (value == "UnrepresentableCharacter") return EncodingError::UnrepresentableCharacter;
  if (value == "OutputTooLarge") return EncodingError::OutputTooLarge;
  return std::nullopt;
}
inline std::optional<EncodingError> EncodingError_fromValue(int32_t value) {
  switch (static_cast<EncodingError>(value)) {
    case EncodingError::InvalidData: return EncodingError::InvalidData;
    case EncodingError::UnrepresentableCharacter: return EncodingError::UnrepresentableCharacter;
    case EncodingError::OutputTooLarge: return EncodingError::OutputTooLarge;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, EncodingError value) { return output << EncodingError_name(value); }
}

namespace app_src_lexer_ {
    enum class TokenType {
    IntLiteral,
    LongLiteral,
    FloatLiteral,
    DoubleLiteral,
    StringLiteral,
    CharLiteral,
    TemplateLiteralStart,
    TemplateLiteralMiddle,
    TemplateLiteralEnd,
    Identifier,
    CallerIntrinsic,
    Const,
    Readonly,
    Let,
    Function,
    Return,
    Yield,
    If,
    Else,
    Then,
    While,
    For,
    Of,
    Break,
    Continue,
    Case,
    Class,
    Struct,
    Interface,
    Implements,
    Enum,
    Type,
    Import,
    Export,
    From,
    As,
    True,
    False,
    None,
    Null,
    Void,
    Try,
    Catch,
    Static,
    This,
    Weak,
    Destructor,
    Async,
    Retire,
    Isolated,
    Private,
    With,
    Mock,
    Plus,
    Minus,
    Star,
    Slash,
    Backslash,
    Percent,
    StarStar,
    Ampersand,
    Pipe,
    Caret,
    Tilde,
    LessLess,
    GreaterGreater,
    GreaterGreaterGreater,
    AmpersandAmpersand,
    PipePipe,
    Bang,
    QuestionQuestion,
    EqualEqual,
    BangEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    Equal,
    ColonEqual,
    LeftArrow,
    PlusEqual,
    MinusEqual,
    StarEqual,
    SlashEqual,
    BackslashEqual,
    PercentEqual,
    StarStarEqual,
    AmpersandEqual,
    PipeEqual,
    CaretEqual,
    LessLessEqual,
    GreaterGreaterEqual,
    QuestionQuestionEqual,
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    LeftBracket,
    RightBracket,
    Dot,
    DotDot,
    DotDotLess,
    Comma,
    Colon,
    DoubleColon,
    Semicolon,
    RightArrow,
    Arrow,
    QuestionDot,
    BangDot,
    QuestionBracket,
    Underscore,
    DollarBrace,
    TagOpen,
    TagText,
    Ellipsis,
    EndOfFile
};
inline const char* TokenType_name(TokenType value) {
  switch (value) {
    case TokenType::IntLiteral: return "IntLiteral";
    case TokenType::LongLiteral: return "LongLiteral";
    case TokenType::FloatLiteral: return "FloatLiteral";
    case TokenType::DoubleLiteral: return "DoubleLiteral";
    case TokenType::StringLiteral: return "StringLiteral";
    case TokenType::CharLiteral: return "CharLiteral";
    case TokenType::TemplateLiteralStart: return "TemplateLiteralStart";
    case TokenType::TemplateLiteralMiddle: return "TemplateLiteralMiddle";
    case TokenType::TemplateLiteralEnd: return "TemplateLiteralEnd";
    case TokenType::Identifier: return "Identifier";
    case TokenType::CallerIntrinsic: return "CallerIntrinsic";
    case TokenType::Const: return "Const";
    case TokenType::Readonly: return "Readonly";
    case TokenType::Let: return "Let";
    case TokenType::Function: return "Function";
    case TokenType::Return: return "Return";
    case TokenType::Yield: return "Yield";
    case TokenType::If: return "If";
    case TokenType::Else: return "Else";
    case TokenType::Then: return "Then";
    case TokenType::While: return "While";
    case TokenType::For: return "For";
    case TokenType::Of: return "Of";
    case TokenType::Break: return "Break";
    case TokenType::Continue: return "Continue";
    case TokenType::Case: return "Case";
    case TokenType::Class: return "Class";
    case TokenType::Struct: return "Struct";
    case TokenType::Interface: return "Interface";
    case TokenType::Implements: return "Implements";
    case TokenType::Enum: return "Enum";
    case TokenType::Type: return "Type";
    case TokenType::Import: return "Import";
    case TokenType::Export: return "Export";
    case TokenType::From: return "From";
    case TokenType::As: return "As";
    case TokenType::True: return "True";
    case TokenType::False: return "False";
    case TokenType::None: return "None";
    case TokenType::Null: return "Null";
    case TokenType::Void: return "Void";
    case TokenType::Try: return "Try";
    case TokenType::Catch: return "Catch";
    case TokenType::Static: return "Static";
    case TokenType::This: return "This";
    case TokenType::Weak: return "Weak";
    case TokenType::Destructor: return "Destructor";
    case TokenType::Async: return "Async";
    case TokenType::Retire: return "Retire";
    case TokenType::Isolated: return "Isolated";
    case TokenType::Private: return "Private";
    case TokenType::With: return "With";
    case TokenType::Mock: return "Mock";
    case TokenType::Plus: return "Plus";
    case TokenType::Minus: return "Minus";
    case TokenType::Star: return "Star";
    case TokenType::Slash: return "Slash";
    case TokenType::Backslash: return "Backslash";
    case TokenType::Percent: return "Percent";
    case TokenType::StarStar: return "StarStar";
    case TokenType::Ampersand: return "Ampersand";
    case TokenType::Pipe: return "Pipe";
    case TokenType::Caret: return "Caret";
    case TokenType::Tilde: return "Tilde";
    case TokenType::LessLess: return "LessLess";
    case TokenType::GreaterGreater: return "GreaterGreater";
    case TokenType::GreaterGreaterGreater: return "GreaterGreaterGreater";
    case TokenType::AmpersandAmpersand: return "AmpersandAmpersand";
    case TokenType::PipePipe: return "PipePipe";
    case TokenType::Bang: return "Bang";
    case TokenType::QuestionQuestion: return "QuestionQuestion";
    case TokenType::EqualEqual: return "EqualEqual";
    case TokenType::BangEqual: return "BangEqual";
    case TokenType::Less: return "Less";
    case TokenType::LessEqual: return "LessEqual";
    case TokenType::Greater: return "Greater";
    case TokenType::GreaterEqual: return "GreaterEqual";
    case TokenType::Equal: return "Equal";
    case TokenType::ColonEqual: return "ColonEqual";
    case TokenType::LeftArrow: return "LeftArrow";
    case TokenType::PlusEqual: return "PlusEqual";
    case TokenType::MinusEqual: return "MinusEqual";
    case TokenType::StarEqual: return "StarEqual";
    case TokenType::SlashEqual: return "SlashEqual";
    case TokenType::BackslashEqual: return "BackslashEqual";
    case TokenType::PercentEqual: return "PercentEqual";
    case TokenType::StarStarEqual: return "StarStarEqual";
    case TokenType::AmpersandEqual: return "AmpersandEqual";
    case TokenType::PipeEqual: return "PipeEqual";
    case TokenType::CaretEqual: return "CaretEqual";
    case TokenType::LessLessEqual: return "LessLessEqual";
    case TokenType::GreaterGreaterEqual: return "GreaterGreaterEqual";
    case TokenType::QuestionQuestionEqual: return "QuestionQuestionEqual";
    case TokenType::LeftParen: return "LeftParen";
    case TokenType::RightParen: return "RightParen";
    case TokenType::LeftBrace: return "LeftBrace";
    case TokenType::RightBrace: return "RightBrace";
    case TokenType::LeftBracket: return "LeftBracket";
    case TokenType::RightBracket: return "RightBracket";
    case TokenType::Dot: return "Dot";
    case TokenType::DotDot: return "DotDot";
    case TokenType::DotDotLess: return "DotDotLess";
    case TokenType::Comma: return "Comma";
    case TokenType::Colon: return "Colon";
    case TokenType::DoubleColon: return "DoubleColon";
    case TokenType::Semicolon: return "Semicolon";
    case TokenType::RightArrow: return "RightArrow";
    case TokenType::Arrow: return "Arrow";
    case TokenType::QuestionDot: return "QuestionDot";
    case TokenType::BangDot: return "BangDot";
    case TokenType::QuestionBracket: return "QuestionBracket";
    case TokenType::Underscore: return "Underscore";
    case TokenType::DollarBrace: return "DollarBrace";
    case TokenType::TagOpen: return "TagOpen";
    case TokenType::TagText: return "TagText";
    case TokenType::Ellipsis: return "Ellipsis";
    case TokenType::EndOfFile: return "EndOfFile";
  }
  return "";
}
inline std::optional<TokenType> TokenType_fromName(std::string_view value) {
  if (value == "IntLiteral") return TokenType::IntLiteral;
  if (value == "LongLiteral") return TokenType::LongLiteral;
  if (value == "FloatLiteral") return TokenType::FloatLiteral;
  if (value == "DoubleLiteral") return TokenType::DoubleLiteral;
  if (value == "StringLiteral") return TokenType::StringLiteral;
  if (value == "CharLiteral") return TokenType::CharLiteral;
  if (value == "TemplateLiteralStart") return TokenType::TemplateLiteralStart;
  if (value == "TemplateLiteralMiddle") return TokenType::TemplateLiteralMiddle;
  if (value == "TemplateLiteralEnd") return TokenType::TemplateLiteralEnd;
  if (value == "Identifier") return TokenType::Identifier;
  if (value == "CallerIntrinsic") return TokenType::CallerIntrinsic;
  if (value == "Const") return TokenType::Const;
  if (value == "Readonly") return TokenType::Readonly;
  if (value == "Let") return TokenType::Let;
  if (value == "Function") return TokenType::Function;
  if (value == "Return") return TokenType::Return;
  if (value == "Yield") return TokenType::Yield;
  if (value == "If") return TokenType::If;
  if (value == "Else") return TokenType::Else;
  if (value == "Then") return TokenType::Then;
  if (value == "While") return TokenType::While;
  if (value == "For") return TokenType::For;
  if (value == "Of") return TokenType::Of;
  if (value == "Break") return TokenType::Break;
  if (value == "Continue") return TokenType::Continue;
  if (value == "Case") return TokenType::Case;
  if (value == "Class") return TokenType::Class;
  if (value == "Struct") return TokenType::Struct;
  if (value == "Interface") return TokenType::Interface;
  if (value == "Implements") return TokenType::Implements;
  if (value == "Enum") return TokenType::Enum;
  if (value == "Type") return TokenType::Type;
  if (value == "Import") return TokenType::Import;
  if (value == "Export") return TokenType::Export;
  if (value == "From") return TokenType::From;
  if (value == "As") return TokenType::As;
  if (value == "True") return TokenType::True;
  if (value == "False") return TokenType::False;
  if (value == "None") return TokenType::None;
  if (value == "Null") return TokenType::Null;
  if (value == "Void") return TokenType::Void;
  if (value == "Try") return TokenType::Try;
  if (value == "Catch") return TokenType::Catch;
  if (value == "Static") return TokenType::Static;
  if (value == "This") return TokenType::This;
  if (value == "Weak") return TokenType::Weak;
  if (value == "Destructor") return TokenType::Destructor;
  if (value == "Async") return TokenType::Async;
  if (value == "Retire") return TokenType::Retire;
  if (value == "Isolated") return TokenType::Isolated;
  if (value == "Private") return TokenType::Private;
  if (value == "With") return TokenType::With;
  if (value == "Mock") return TokenType::Mock;
  if (value == "Plus") return TokenType::Plus;
  if (value == "Minus") return TokenType::Minus;
  if (value == "Star") return TokenType::Star;
  if (value == "Slash") return TokenType::Slash;
  if (value == "Backslash") return TokenType::Backslash;
  if (value == "Percent") return TokenType::Percent;
  if (value == "StarStar") return TokenType::StarStar;
  if (value == "Ampersand") return TokenType::Ampersand;
  if (value == "Pipe") return TokenType::Pipe;
  if (value == "Caret") return TokenType::Caret;
  if (value == "Tilde") return TokenType::Tilde;
  if (value == "LessLess") return TokenType::LessLess;
  if (value == "GreaterGreater") return TokenType::GreaterGreater;
  if (value == "GreaterGreaterGreater") return TokenType::GreaterGreaterGreater;
  if (value == "AmpersandAmpersand") return TokenType::AmpersandAmpersand;
  if (value == "PipePipe") return TokenType::PipePipe;
  if (value == "Bang") return TokenType::Bang;
  if (value == "QuestionQuestion") return TokenType::QuestionQuestion;
  if (value == "EqualEqual") return TokenType::EqualEqual;
  if (value == "BangEqual") return TokenType::BangEqual;
  if (value == "Less") return TokenType::Less;
  if (value == "LessEqual") return TokenType::LessEqual;
  if (value == "Greater") return TokenType::Greater;
  if (value == "GreaterEqual") return TokenType::GreaterEqual;
  if (value == "Equal") return TokenType::Equal;
  if (value == "ColonEqual") return TokenType::ColonEqual;
  if (value == "LeftArrow") return TokenType::LeftArrow;
  if (value == "PlusEqual") return TokenType::PlusEqual;
  if (value == "MinusEqual") return TokenType::MinusEqual;
  if (value == "StarEqual") return TokenType::StarEqual;
  if (value == "SlashEqual") return TokenType::SlashEqual;
  if (value == "BackslashEqual") return TokenType::BackslashEqual;
  if (value == "PercentEqual") return TokenType::PercentEqual;
  if (value == "StarStarEqual") return TokenType::StarStarEqual;
  if (value == "AmpersandEqual") return TokenType::AmpersandEqual;
  if (value == "PipeEqual") return TokenType::PipeEqual;
  if (value == "CaretEqual") return TokenType::CaretEqual;
  if (value == "LessLessEqual") return TokenType::LessLessEqual;
  if (value == "GreaterGreaterEqual") return TokenType::GreaterGreaterEqual;
  if (value == "QuestionQuestionEqual") return TokenType::QuestionQuestionEqual;
  if (value == "LeftParen") return TokenType::LeftParen;
  if (value == "RightParen") return TokenType::RightParen;
  if (value == "LeftBrace") return TokenType::LeftBrace;
  if (value == "RightBrace") return TokenType::RightBrace;
  if (value == "LeftBracket") return TokenType::LeftBracket;
  if (value == "RightBracket") return TokenType::RightBracket;
  if (value == "Dot") return TokenType::Dot;
  if (value == "DotDot") return TokenType::DotDot;
  if (value == "DotDotLess") return TokenType::DotDotLess;
  if (value == "Comma") return TokenType::Comma;
  if (value == "Colon") return TokenType::Colon;
  if (value == "DoubleColon") return TokenType::DoubleColon;
  if (value == "Semicolon") return TokenType::Semicolon;
  if (value == "RightArrow") return TokenType::RightArrow;
  if (value == "Arrow") return TokenType::Arrow;
  if (value == "QuestionDot") return TokenType::QuestionDot;
  if (value == "BangDot") return TokenType::BangDot;
  if (value == "QuestionBracket") return TokenType::QuestionBracket;
  if (value == "Underscore") return TokenType::Underscore;
  if (value == "DollarBrace") return TokenType::DollarBrace;
  if (value == "TagOpen") return TokenType::TagOpen;
  if (value == "TagText") return TokenType::TagText;
  if (value == "Ellipsis") return TokenType::Ellipsis;
  if (value == "EndOfFile") return TokenType::EndOfFile;
  return std::nullopt;
}
inline std::optional<TokenType> TokenType_fromValue(int32_t value) {
  switch (static_cast<TokenType>(value)) {
    case TokenType::IntLiteral: return TokenType::IntLiteral;
    case TokenType::LongLiteral: return TokenType::LongLiteral;
    case TokenType::FloatLiteral: return TokenType::FloatLiteral;
    case TokenType::DoubleLiteral: return TokenType::DoubleLiteral;
    case TokenType::StringLiteral: return TokenType::StringLiteral;
    case TokenType::CharLiteral: return TokenType::CharLiteral;
    case TokenType::TemplateLiteralStart: return TokenType::TemplateLiteralStart;
    case TokenType::TemplateLiteralMiddle: return TokenType::TemplateLiteralMiddle;
    case TokenType::TemplateLiteralEnd: return TokenType::TemplateLiteralEnd;
    case TokenType::Identifier: return TokenType::Identifier;
    case TokenType::CallerIntrinsic: return TokenType::CallerIntrinsic;
    case TokenType::Const: return TokenType::Const;
    case TokenType::Readonly: return TokenType::Readonly;
    case TokenType::Let: return TokenType::Let;
    case TokenType::Function: return TokenType::Function;
    case TokenType::Return: return TokenType::Return;
    case TokenType::Yield: return TokenType::Yield;
    case TokenType::If: return TokenType::If;
    case TokenType::Else: return TokenType::Else;
    case TokenType::Then: return TokenType::Then;
    case TokenType::While: return TokenType::While;
    case TokenType::For: return TokenType::For;
    case TokenType::Of: return TokenType::Of;
    case TokenType::Break: return TokenType::Break;
    case TokenType::Continue: return TokenType::Continue;
    case TokenType::Case: return TokenType::Case;
    case TokenType::Class: return TokenType::Class;
    case TokenType::Struct: return TokenType::Struct;
    case TokenType::Interface: return TokenType::Interface;
    case TokenType::Implements: return TokenType::Implements;
    case TokenType::Enum: return TokenType::Enum;
    case TokenType::Type: return TokenType::Type;
    case TokenType::Import: return TokenType::Import;
    case TokenType::Export: return TokenType::Export;
    case TokenType::From: return TokenType::From;
    case TokenType::As: return TokenType::As;
    case TokenType::True: return TokenType::True;
    case TokenType::False: return TokenType::False;
    case TokenType::None: return TokenType::None;
    case TokenType::Null: return TokenType::Null;
    case TokenType::Void: return TokenType::Void;
    case TokenType::Try: return TokenType::Try;
    case TokenType::Catch: return TokenType::Catch;
    case TokenType::Static: return TokenType::Static;
    case TokenType::This: return TokenType::This;
    case TokenType::Weak: return TokenType::Weak;
    case TokenType::Destructor: return TokenType::Destructor;
    case TokenType::Async: return TokenType::Async;
    case TokenType::Retire: return TokenType::Retire;
    case TokenType::Isolated: return TokenType::Isolated;
    case TokenType::Private: return TokenType::Private;
    case TokenType::With: return TokenType::With;
    case TokenType::Mock: return TokenType::Mock;
    case TokenType::Plus: return TokenType::Plus;
    case TokenType::Minus: return TokenType::Minus;
    case TokenType::Star: return TokenType::Star;
    case TokenType::Slash: return TokenType::Slash;
    case TokenType::Backslash: return TokenType::Backslash;
    case TokenType::Percent: return TokenType::Percent;
    case TokenType::StarStar: return TokenType::StarStar;
    case TokenType::Ampersand: return TokenType::Ampersand;
    case TokenType::Pipe: return TokenType::Pipe;
    case TokenType::Caret: return TokenType::Caret;
    case TokenType::Tilde: return TokenType::Tilde;
    case TokenType::LessLess: return TokenType::LessLess;
    case TokenType::GreaterGreater: return TokenType::GreaterGreater;
    case TokenType::GreaterGreaterGreater: return TokenType::GreaterGreaterGreater;
    case TokenType::AmpersandAmpersand: return TokenType::AmpersandAmpersand;
    case TokenType::PipePipe: return TokenType::PipePipe;
    case TokenType::Bang: return TokenType::Bang;
    case TokenType::QuestionQuestion: return TokenType::QuestionQuestion;
    case TokenType::EqualEqual: return TokenType::EqualEqual;
    case TokenType::BangEqual: return TokenType::BangEqual;
    case TokenType::Less: return TokenType::Less;
    case TokenType::LessEqual: return TokenType::LessEqual;
    case TokenType::Greater: return TokenType::Greater;
    case TokenType::GreaterEqual: return TokenType::GreaterEqual;
    case TokenType::Equal: return TokenType::Equal;
    case TokenType::ColonEqual: return TokenType::ColonEqual;
    case TokenType::LeftArrow: return TokenType::LeftArrow;
    case TokenType::PlusEqual: return TokenType::PlusEqual;
    case TokenType::MinusEqual: return TokenType::MinusEqual;
    case TokenType::StarEqual: return TokenType::StarEqual;
    case TokenType::SlashEqual: return TokenType::SlashEqual;
    case TokenType::BackslashEqual: return TokenType::BackslashEqual;
    case TokenType::PercentEqual: return TokenType::PercentEqual;
    case TokenType::StarStarEqual: return TokenType::StarStarEqual;
    case TokenType::AmpersandEqual: return TokenType::AmpersandEqual;
    case TokenType::PipeEqual: return TokenType::PipeEqual;
    case TokenType::CaretEqual: return TokenType::CaretEqual;
    case TokenType::LessLessEqual: return TokenType::LessLessEqual;
    case TokenType::GreaterGreaterEqual: return TokenType::GreaterGreaterEqual;
    case TokenType::QuestionQuestionEqual: return TokenType::QuestionQuestionEqual;
    case TokenType::LeftParen: return TokenType::LeftParen;
    case TokenType::RightParen: return TokenType::RightParen;
    case TokenType::LeftBrace: return TokenType::LeftBrace;
    case TokenType::RightBrace: return TokenType::RightBrace;
    case TokenType::LeftBracket: return TokenType::LeftBracket;
    case TokenType::RightBracket: return TokenType::RightBracket;
    case TokenType::Dot: return TokenType::Dot;
    case TokenType::DotDot: return TokenType::DotDot;
    case TokenType::DotDotLess: return TokenType::DotDotLess;
    case TokenType::Comma: return TokenType::Comma;
    case TokenType::Colon: return TokenType::Colon;
    case TokenType::DoubleColon: return TokenType::DoubleColon;
    case TokenType::Semicolon: return TokenType::Semicolon;
    case TokenType::RightArrow: return TokenType::RightArrow;
    case TokenType::Arrow: return TokenType::Arrow;
    case TokenType::QuestionDot: return TokenType::QuestionDot;
    case TokenType::BangDot: return TokenType::BangDot;
    case TokenType::QuestionBracket: return TokenType::QuestionBracket;
    case TokenType::Underscore: return TokenType::Underscore;
    case TokenType::DollarBrace: return TokenType::DollarBrace;
    case TokenType::TagOpen: return TokenType::TagOpen;
    case TokenType::TagText: return TokenType::TagText;
    case TokenType::Ellipsis: return TokenType::Ellipsis;
    case TokenType::EndOfFile: return TokenType::EndOfFile;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, TokenType value) { return output << TokenType_name(value); }
}

namespace std_::fs::types {
    enum class EntryKind {
    File = 0,
    Directory = 1,
    Symlink = 2,
    Other = 3
};
inline const char* EntryKind_name(EntryKind value) {
  switch (value) {
    case EntryKind::File: return "File";
    case EntryKind::Directory: return "Directory";
    case EntryKind::Symlink: return "Symlink";
    case EntryKind::Other: return "Other";
  }
  return "";
}
inline std::optional<EntryKind> EntryKind_fromName(std::string_view value) {
  if (value == "File") return EntryKind::File;
  if (value == "Directory") return EntryKind::Directory;
  if (value == "Symlink") return EntryKind::Symlink;
  if (value == "Other") return EntryKind::Other;
  return std::nullopt;
}
inline std::optional<EntryKind> EntryKind_fromValue(int32_t value) {
  switch (static_cast<EntryKind>(value)) {
    case EntryKind::File: return EntryKind::File;
    case EntryKind::Directory: return EntryKind::Directory;
    case EntryKind::Symlink: return EntryKind::Symlink;
    case EntryKind::Other: return EntryKind::Other;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, EntryKind value) { return output << EntryKind_name(value); }
    enum class IoError {
    NotFound = 0,
    PermissionDenied = 1,
    AlreadyExists = 2,
    IsDirectory = 3,
    NotDirectory = 4,
    InvalidPath = 5,
    Interrupted = 6,
    Other = 7,
    Unsupported = 8
};
inline const char* IoError_name(IoError value) {
  switch (value) {
    case IoError::NotFound: return "NotFound";
    case IoError::PermissionDenied: return "PermissionDenied";
    case IoError::AlreadyExists: return "AlreadyExists";
    case IoError::IsDirectory: return "IsDirectory";
    case IoError::NotDirectory: return "NotDirectory";
    case IoError::InvalidPath: return "InvalidPath";
    case IoError::Interrupted: return "Interrupted";
    case IoError::Other: return "Other";
    case IoError::Unsupported: return "Unsupported";
  }
  return "";
}
inline std::optional<IoError> IoError_fromName(std::string_view value) {
  if (value == "NotFound") return IoError::NotFound;
  if (value == "PermissionDenied") return IoError::PermissionDenied;
  if (value == "AlreadyExists") return IoError::AlreadyExists;
  if (value == "IsDirectory") return IoError::IsDirectory;
  if (value == "NotDirectory") return IoError::NotDirectory;
  if (value == "InvalidPath") return IoError::InvalidPath;
  if (value == "Interrupted") return IoError::Interrupted;
  if (value == "Other") return IoError::Other;
  if (value == "Unsupported") return IoError::Unsupported;
  return std::nullopt;
}
inline std::optional<IoError> IoError_fromValue(int32_t value) {
  switch (static_cast<IoError>(value)) {
    case IoError::NotFound: return IoError::NotFound;
    case IoError::PermissionDenied: return IoError::PermissionDenied;
    case IoError::AlreadyExists: return IoError::AlreadyExists;
    case IoError::IsDirectory: return IoError::IsDirectory;
    case IoError::NotDirectory: return IoError::NotDirectory;
    case IoError::InvalidPath: return IoError::InvalidPath;
    case IoError::Interrupted: return IoError::Interrupted;
    case IoError::Other: return IoError::Other;
    case IoError::Unsupported: return IoError::Unsupported;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, IoError value) { return output << IoError_name(value); }
}

namespace std_::os::index {
    enum class ProcessGroupMode {
    Isolated,
    Inherited
};
inline const char* ProcessGroupMode_name(ProcessGroupMode value) {
  switch (value) {
    case ProcessGroupMode::Isolated: return "Isolated";
    case ProcessGroupMode::Inherited: return "Inherited";
  }
  return "";
}
inline std::optional<ProcessGroupMode> ProcessGroupMode_fromName(std::string_view value) {
  if (value == "Isolated") return ProcessGroupMode::Isolated;
  if (value == "Inherited") return ProcessGroupMode::Inherited;
  return std::nullopt;
}
inline std::optional<ProcessGroupMode> ProcessGroupMode_fromValue(int32_t value) {
  switch (static_cast<ProcessGroupMode>(value)) {
    case ProcessGroupMode::Isolated: return ProcessGroupMode::Isolated;
    case ProcessGroupMode::Inherited: return ProcessGroupMode::Inherited;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, ProcessGroupMode value) { return output << ProcessGroupMode_name(value); }
}

namespace std_::time::temporal {
    enum class DayOfWeek {
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
    Sunday = 7
};
inline const char* DayOfWeek_name(DayOfWeek value) {
  switch (value) {
    case DayOfWeek::Monday: return "Monday";
    case DayOfWeek::Tuesday: return "Tuesday";
    case DayOfWeek::Wednesday: return "Wednesday";
    case DayOfWeek::Thursday: return "Thursday";
    case DayOfWeek::Friday: return "Friday";
    case DayOfWeek::Saturday: return "Saturday";
    case DayOfWeek::Sunday: return "Sunday";
  }
  return "";
}
inline std::optional<DayOfWeek> DayOfWeek_fromName(std::string_view value) {
  if (value == "Monday") return DayOfWeek::Monday;
  if (value == "Tuesday") return DayOfWeek::Tuesday;
  if (value == "Wednesday") return DayOfWeek::Wednesday;
  if (value == "Thursday") return DayOfWeek::Thursday;
  if (value == "Friday") return DayOfWeek::Friday;
  if (value == "Saturday") return DayOfWeek::Saturday;
  if (value == "Sunday") return DayOfWeek::Sunday;
  return std::nullopt;
}
inline std::optional<DayOfWeek> DayOfWeek_fromValue(int32_t value) {
  switch (static_cast<DayOfWeek>(value)) {
    case DayOfWeek::Monday: return DayOfWeek::Monday;
    case DayOfWeek::Tuesday: return DayOfWeek::Tuesday;
    case DayOfWeek::Wednesday: return DayOfWeek::Wednesday;
    case DayOfWeek::Thursday: return DayOfWeek::Thursday;
    case DayOfWeek::Friday: return DayOfWeek::Friday;
    case DayOfWeek::Saturday: return DayOfWeek::Saturday;
    case DayOfWeek::Sunday: return DayOfWeek::Sunday;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, DayOfWeek value) { return output << DayOfWeek_name(value); }
}

namespace app_src_native_build_ {
    enum class NativeBuildMode {
    Debug,
    Release,
    Profile
};
inline const char* NativeBuildMode_name(NativeBuildMode value) {
  switch (value) {
    case NativeBuildMode::Debug: return "Debug";
    case NativeBuildMode::Release: return "Release";
    case NativeBuildMode::Profile: return "Profile";
  }
  return "";
}
inline std::optional<NativeBuildMode> NativeBuildMode_fromName(std::string_view value) {
  if (value == "Debug") return NativeBuildMode::Debug;
  if (value == "Release") return NativeBuildMode::Release;
  if (value == "Profile") return NativeBuildMode::Profile;
  return std::nullopt;
}
inline std::optional<NativeBuildMode> NativeBuildMode_fromValue(int32_t value) {
  switch (static_cast<NativeBuildMode>(value)) {
    case NativeBuildMode::Debug: return NativeBuildMode::Debug;
    case NativeBuildMode::Release: return NativeBuildMode::Release;
    case NativeBuildMode::Profile: return NativeBuildMode::Profile;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, NativeBuildMode value) { return output << NativeBuildMode_name(value); }
}

namespace app_src_native_build_driver_ {
    enum class NativeBuildOutputMode {
    Silent,
    Progress
};
inline const char* NativeBuildOutputMode_name(NativeBuildOutputMode value) {
  switch (value) {
    case NativeBuildOutputMode::Silent: return "Silent";
    case NativeBuildOutputMode::Progress: return "Progress";
  }
  return "";
}
inline std::optional<NativeBuildOutputMode> NativeBuildOutputMode_fromName(std::string_view value) {
  if (value == "Silent") return NativeBuildOutputMode::Silent;
  if (value == "Progress") return NativeBuildOutputMode::Progress;
  return std::nullopt;
}
inline std::optional<NativeBuildOutputMode> NativeBuildOutputMode_fromValue(int32_t value) {
  switch (static_cast<NativeBuildOutputMode>(value)) {
    case NativeBuildOutputMode::Silent: return NativeBuildOutputMode::Silent;
    case NativeBuildOutputMode::Progress: return NativeBuildOutputMode::Progress;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, NativeBuildOutputMode value) { return output << NativeBuildOutputMode_name(value); }
}

namespace app_src_semantic_ {
    using ResolvedType = std::variant<std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_ast_ {
    using TypeAnnotation = std::variant<std::shared_ptr<NamedType>, std::shared_ptr<ArrayType>, std::shared_ptr<UnionType>, std::shared_ptr<AstFunctionType>, std::shared_ptr<WeakType>>;
    using Expression = std::variant<std::shared_ptr<IntLiteral>, std::shared_ptr<LongLiteral>, std::shared_ptr<FloatLiteral>, std::shared_ptr<DoubleLiteral>, std::shared_ptr<StringLiteral>, std::shared_ptr<CharLiteral>, std::shared_ptr<BoolLiteral>, std::shared_ptr<NoneLiteral>, std::shared_ptr<Identifier>, std::shared_ptr<BinaryExpression>, std::shared_ptr<UnaryExpression>, std::shared_ptr<AssignmentExpression>, std::shared_ptr<MemberExpression>, std::shared_ptr<IndexExpression>, std::shared_ptr<CallExpression>, std::shared_ptr<ArrayLiteral>, std::shared_ptr<ObjectLiteral>, std::shared_ptr<TupleLiteral>, std::shared_ptr<LambdaExpression>, std::shared_ptr<IfExpression>, std::shared_ptr<CaseExpression>, std::shared_ptr<ConstructExpression>, std::shared_ptr<DotShorthand>, std::shared_ptr<ThisExpression>, std::shared_ptr<CallerExpression>, std::shared_ptr<AsyncExpression>, std::shared_ptr<RetireExpression>, std::shared_ptr<AsExpression>, std::shared_ptr<ActorCreationExpression>, std::shared_ptr<YieldBlockExpression>, std::shared_ptr<CatchExpression>>;
    using CasePattern = std::variant<std::shared_ptr<TypePattern>, std::shared_ptr<WildcardPattern>, std::shared_ptr<ValuePattern>, std::shared_ptr<RangePattern>>;
    using ImportSpecifier = std::variant<std::shared_ptr<NamedImport>, std::shared_ptr<NamespaceImport>>;
    using Statement = std::variant<std::shared_ptr<ConstDeclaration>, std::shared_ptr<ReadonlyDeclaration>, std::shared_ptr<ImmutableBinding>, std::shared_ptr<LetDeclaration>, std::shared_ptr<FunctionDeclaration>, std::shared_ptr<ClassDeclaration>, std::shared_ptr<InterfaceDeclaration>, std::shared_ptr<EnumDeclaration>, std::shared_ptr<TypeAliasDeclaration>, std::shared_ptr<ImportDeclaration>, std::shared_ptr<MockImportDirective>, std::shared_ptr<ExportDeclaration>, std::shared_ptr<ExportList>, std::shared_ptr<IfStatement>, std::shared_ptr<CaseStatement>, std::shared_ptr<WhileStatement>, std::shared_ptr<ForStatement>, std::shared_ptr<ForOfStatement>, std::shared_ptr<WithStatement>, std::shared_ptr<ReturnStatement>, std::shared_ptr<YieldStatement>, std::shared_ptr<BreakStatement>, std::shared_ptr<ContinueStatement>, std::shared_ptr<ExpressionStatement>, std::shared_ptr<DestructuringStatement>, std::shared_ptr<TryStatement>, std::shared_ptr<YieldBlockAssignmentStatement>, std::shared_ptr<Block>>;
}

namespace app_src_resolver_ {
    using SourceLoader = doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>;
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

namespace app_src_emitter_names_ {
    struct ModuleNamespaceMapping : public std::enable_shared_from_this<ModuleNamespaceMapping> {
    std::string logicalPrefix;
    std::string packageName;
    std::string outputRoot;
    ModuleNamespaceMapping(std::string logicalPrefix, std::string packageName, std::string outputRoot) : logicalPrefix(logicalPrefix), packageName(packageName), outputRoot(outputRoot) {}
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

namespace app_src_compiler_ {
    struct Compilation : public std::enable_shared_from_this<Compilation> {
    std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> emission;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sourceFiles;
    std::shared_ptr<std::vector<std::string>> resolutionProbes;
    Compilation(std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> emission, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>> sourceFiles, std::shared_ptr<std::vector<std::string>> resolutionProbes) : emission(emission), diagnostics(diagnostics), sourceFiles(sourceFiles), resolutionProbes(resolutionProbes) {}
};
}

namespace app_src_cli_ {
    struct CliRequest : public std::enable_shared_from_this<CliRequest> {
    std::string command;
    std::string entry;
    std::string outputDirectory;
    std::string compiler;
    std::string filter;
    bool listOnly;
    bool coverage;
    std::string coverageOutput;
    std::string traceOutput;
    std::string profileTimeLimit;
    bool profileNoOpen;
    std::string distDirectory;
    std::string macosSigning;
    std::string macosSignIdentity;
    bool macosSandbox;
    std::string macosEntitlements;
    std::string iosDestination;
    std::string iosDevice;
    std::string iosSignIdentity;
    std::string iosProvisioningProfile;
    std::string targetOverride;
    std::shared_ptr<std::vector<std::string>> programArguments;
    CliRequest(std::string command, std::string entry, std::string outputDirectory, std::string compiler, std::string filter, bool listOnly, bool coverage, std::string coverageOutput, std::string traceOutput, std::string profileTimeLimit, bool profileNoOpen, std::string distDirectory, std::string macosSigning, std::string macosSignIdentity, bool macosSandbox, std::string macosEntitlements, std::string iosDestination, std::string iosDevice, std::string iosSignIdentity, std::string iosProvisioningProfile, std::string targetOverride, std::shared_ptr<std::vector<std::string>> programArguments) : command(command), entry(entry), outputDirectory(outputDirectory), compiler(compiler), filter(filter), listOnly(listOnly), coverage(coverage), coverageOutput(coverageOutput), traceOutput(traceOutput), profileTimeLimit(profileTimeLimit), profileNoOpen(profileNoOpen), distDirectory(distDirectory), macosSigning(macosSigning), macosSignIdentity(macosSignIdentity), macosSandbox(macosSandbox), macosEntitlements(macosEntitlements), iosDestination(iosDestination), iosDevice(iosDevice), iosSignIdentity(iosSignIdentity), iosProvisioningProfile(iosProvisioningProfile), targetOverride(targetOverride), programArguments(programArguments) {}
};
    struct CliParseResult : public std::enable_shared_from_this<CliParseResult> {
    std::shared_ptr<CliRequest> request;
    std::string error;
    bool help;
    CliParseResult(std::shared_ptr<CliRequest> request, std::string error, bool help) : request(request), error(error), help(help) {}
};
}

namespace app_src_macos_app_ {
    struct MacOSAppResource : public std::enable_shared_from_this<MacOSAppResource> {
    std::string sourcePath;
    std::string destination;
    MacOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct MacOSEmbeddedLibrary : public std::enable_shared_from_this<MacOSEmbeddedLibrary> {
    std::string library;
    std::string path;
    MacOSEmbeddedLibrary(std::string library, std::string path) : library(library), path(path) {}
};
    struct MacOSAppConfig : public std::enable_shared_from_this<MacOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath;
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist;
    std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries;
    std::string category;
    std::string minimumSystemVersion;
    MacOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist, std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries, std::string category, std::string minimumSystemVersion) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), category(category), minimumSystemVersion(minimumSystemVersion) {}
};
    struct MacOSPackageConfig : public std::enable_shared_from_this<MacOSPackageConfig> {
    std::string distDirectory;
    std::string signing;
    std::string identity;
    bool sandbox;
    std::string entitlementsPath;
    MacOSPackageConfig(std::string distDirectory, std::string signing, std::string identity, bool sandbox, std::string entitlementsPath) : distDirectory(distDirectory), signing(signing), identity(identity), sandbox(sandbox), entitlementsPath(entitlementsPath) {}
};
}

namespace app_src_ios_app_ {
    struct IOSAppResource : public std::enable_shared_from_this<IOSAppResource> {
    std::string sourcePath;
    std::string destination;
    IOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct IOSEmbeddedLibrary : public std::enable_shared_from_this<IOSEmbeddedLibrary> {
    std::string library;
    std::string path;
    IOSEmbeddedLibrary(std::string library, std::string path) : library(library), path(path) {}
};
    struct IOSAppConfig : public std::enable_shared_from_this<IOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath;
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist;
    std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>> embeddedLibraries;
    std::string minimumDeploymentTarget;
    IOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist, std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>> embeddedLibraries, std::string minimumDeploymentTarget) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), minimumDeploymentTarget(minimumDeploymentTarget) {}
};
    struct IOSPackageConfig : public std::enable_shared_from_this<IOSPackageConfig> {
    std::string identity;
    std::string provisioningProfilePath;
    IOSPackageConfig(std::string identity, std::string provisioningProfilePath) : identity(identity), provisioningProfilePath(provisioningProfilePath) {}
};
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan : public std::enable_shared_from_this<NativeBuildPlan> {
    std::shared_ptr<std::vector<std::string>> includePaths;
    std::shared_ptr<std::vector<std::string>> sourceFiles;
    std::shared_ptr<std::vector<std::string>> libraryPaths;
    std::shared_ptr<std::vector<std::string>> extraCopyPaths;
    std::shared_ptr<std::vector<std::string>> linkLibraries;
    std::shared_ptr<std::vector<std::string>> frameworks;
    std::shared_ptr<std::vector<std::string>> pkgConfigPackages;
    std::shared_ptr<std::vector<std::string>> defines;
    std::shared_ptr<std::vector<std::string>> compilerFlags;
    std::shared_ptr<std::vector<std::string>> linkerFlags;
    NativeBuildPlan(std::shared_ptr<std::vector<std::string>> includePaths, std::shared_ptr<std::vector<std::string>> sourceFiles, std::shared_ptr<std::vector<std::string>> libraryPaths, std::shared_ptr<std::vector<std::string>> extraCopyPaths, std::shared_ptr<std::vector<std::string>> linkLibraries, std::shared_ptr<std::vector<std::string>> frameworks, std::shared_ptr<std::vector<std::string>> pkgConfigPackages, std::shared_ptr<std::vector<std::string>> defines, std::shared_ptr<std::vector<std::string>> compilerFlags, std::shared_ptr<std::vector<std::string>> linkerFlags) : includePaths(includePaths), sourceFiles(sourceFiles), libraryPaths(libraryPaths), extraCopyPaths(extraCopyPaths), linkLibraries(linkLibraries), frameworks(frameworks), pkgConfigPackages(pkgConfigPackages), defines(defines), compilerFlags(compilerFlags), linkerFlags(linkerFlags) {}
};
    struct PackageResource : public std::enable_shared_from_this<PackageResource> {
    std::string sourcePath;
    std::string destination;
    PackageResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct ExternalDependencyCopyFile : public std::enable_shared_from_this<ExternalDependencyCopyFile> {
    std::string source;
    std::string destination;
    ExternalDependencyCopyFile(std::string source, std::string destination) : source(source), destination(destination) {}
};
    struct ExternalDependencyCommand : public std::enable_shared_from_this<ExternalDependencyCommand> {
    std::string program;
    std::shared_ptr<std::vector<std::string>> args;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env;
    std::string workingDirectory;
    ExternalDependencyCommand(std::string program, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<doof::ordered_map<std::string, std::string>> env, std::string workingDirectory) : program(program), args(args), env(env), workingDirectory(workingDirectory) {}
};
    struct ExternalDependency : public std::enable_shared_from_this<ExternalDependency> {
    std::string name;
    std::string kind;
    std::string url;
    std::string destination;
    std::string sha256;
    int32_t stripComponents;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> copyFiles;
    std::string ref;
    std::string commit;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> commands;
    ExternalDependency(std::string name, std::string kind, std::string url, std::string destination, std::string sha256, int32_t stripComponents, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> copyFiles, std::string ref, std::string commit, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> commands) : name(name), kind(kind), url(url), destination(destination), sha256(sha256), stripComponents(stripComponents), copyFiles(copyFiles), ref(ref), commit(commit), commands(commands) {}
};
    struct PackageDependency : public std::enable_shared_from_this<PackageDependency> {
    std::string name;
    std::string path;
    std::string url;
    std::string ref;
    std::string commit;
    PackageDependency(std::string name, std::string path, std::string url, std::string ref, std::string commit) : name(name), path(path), url(url), ref(ref), commit(commit) {}
};
    struct DependencyResolution : public std::enable_shared_from_this<DependencyResolution> {
    std::string name;
    std::string kind;
    std::string url;
    std::string ref;
    std::string commit;
    std::string sha256;
    DependencyResolution(std::string name, std::string kind, std::string url, std::string ref, std::string commit, std::string sha256) : name(name), kind(kind), url(url), ref(ref), commit(commit), sha256(sha256) {}
};
    struct DependencyPolicy : public std::enable_shared_from_this<DependencyPolicy> {
    bool hasPackageSourceAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedPackageSources;
    bool hasExternalSourceAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedExternalSources;
    bool hasLinkLibraryAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedLinkLibraries;
    bool hasFrameworkAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedFrameworks;
    bool hasPkgConfigAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedPkgConfigPackages;
    DependencyPolicy(bool hasPackageSourceAllowlist, std::shared_ptr<std::vector<std::string>> allowedPackageSources, bool hasExternalSourceAllowlist, std::shared_ptr<std::vector<std::string>> allowedExternalSources, bool hasLinkLibraryAllowlist, std::shared_ptr<std::vector<std::string>> allowedLinkLibraries, bool hasFrameworkAllowlist, std::shared_ptr<std::vector<std::string>> allowedFrameworks, bool hasPkgConfigAllowlist, std::shared_ptr<std::vector<std::string>> allowedPkgConfigPackages) : hasPackageSourceAllowlist(hasPackageSourceAllowlist), allowedPackageSources(allowedPackageSources), hasExternalSourceAllowlist(hasExternalSourceAllowlist), allowedExternalSources(allowedExternalSources), hasLinkLibraryAllowlist(hasLinkLibraryAllowlist), allowedLinkLibraries(allowedLinkLibraries), hasFrameworkAllowlist(hasFrameworkAllowlist), allowedFrameworks(allowedFrameworks), hasPkgConfigAllowlist(hasPkgConfigAllowlist), allowedPkgConfigPackages(allowedPkgConfigPackages) {}
};
    struct PackageManifest : public std::enable_shared_from_this<PackageManifest> {
    std::string name;
    std::string version;
    std::string manifestPath;
    std::string rootDirectory;
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> externalDependencies;
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> packageResolutions;
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> externalResolutions;
    std::shared_ptr<DependencyPolicy> policy;
    std::shared_ptr<NativeBuildPlan> nativeBuild;
    std::string target;
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig;
    PackageManifest(std::string name, std::string version, std::string manifestPath, std::string rootDirectory, std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> externalDependencies, std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> packageResolutions, std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> externalResolutions, std::shared_ptr<DependencyPolicy> policy, std::shared_ptr<NativeBuildPlan> nativeBuild, std::string target, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig) : name(name), version(version), manifestPath(manifestPath), rootDirectory(rootDirectory), resources(resources), dependencies(dependencies), externalDependencies(externalDependencies), packageResolutions(packageResolutions), externalResolutions(externalResolutions), policy(policy), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
};
}

namespace std_::os::index {
    struct ExecResult : public std::enable_shared_from_this<ExecResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> stdout_;
    std::shared_ptr<std::vector<uint8_t>> stderr_;
    bool stdoutTruncated;
    bool stderrTruncated;
    ExecResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> stdout_, std::shared_ptr<std::vector<uint8_t>> stderr_, bool stdoutTruncated, bool stderrTruncated) : exitCode(exitCode), stdout_(stdout_), stderr_(stderr_), stdoutTruncated(stdoutTruncated), stderrTruncated(stderrTruncated) {}
};
}

namespace app_src_external_dependency_ {
    struct ExternalDependencyTarget : public std::enable_shared_from_this<ExternalDependencyTarget> {
    std::string nativeTarget;
    std::string sdkPath;
    std::string targetTriple;
    std::string configureHost;
    int32_t jobs;
    ExternalDependencyTarget(std::string nativeTarget, std::string sdkPath, std::string targetTriple, std::string configureHost, int32_t jobs) : nativeTarget(nativeTarget), sdkPath(sdkPath), targetTriple(targetTriple), configureHost(configureHost), jobs(jobs) {}
};
}

namespace std_::time::duration {
    // A signed elapsed duration with nanosecond precision.
struct Duration : public std::enable_shared_from_this<Duration> {
    int64_t nanos;
    static std::shared_ptr<Duration> ZERO;
    Duration(int64_t nanos) : nanos(nanos) {}
    static std::shared_ptr<Duration> ofNanos(int64_t n);
    static std::shared_ptr<Duration> ofMicros(int64_t us);
    static std::shared_ptr<Duration> ofMillis(int64_t ms);
    static std::shared_ptr<Duration> ofSeconds(int64_t s);
    static std::shared_ptr<Duration> ofMinutes(int64_t m);
    static std::shared_ptr<Duration> ofHours(int64_t h);
    static std::shared_ptr<Duration> ofDays(int64_t d);
    static doof::Result<std::shared_ptr<Duration>, std::string> parse(const std::string& s);
    int64_t toNanos();
    int64_t toMicros();
    int64_t toMillis();
    double toSeconds();
    double toMinutes();
    double toHours();
    double toDays();
    bool isNegative();
    bool isZero();
    std::shared_ptr<Duration> abs();
    std::shared_ptr<Duration> negated();
    std::shared_ptr<Duration> plus(const std::shared_ptr<Duration>& other);
    std::shared_ptr<Duration> minus(const std::shared_ptr<Duration>& other);
    std::shared_ptr<Duration> multipliedBy(int64_t factor);
    std::shared_ptr<Duration> dividedBy(int64_t divisor);
    int32_t compareTo(const std::shared_ptr<Duration>& other);
    bool isLessThan(const std::shared_ptr<Duration>& other);
    bool isGreaterThan(const std::shared_ptr<Duration>& other);
    bool equals(const std::shared_ptr<Duration>& other);
    std::string toISOString();
};
}

namespace std_::time::temporal {
    // A point in UTC time with nanosecond precision.
struct Instant : public std::enable_shared_from_this<Instant> {
    int64_t epochNanos;
    static std::shared_ptr<Instant> EPOCH;
    Instant(int64_t epochNanos) : epochNanos(epochNanos) {}
    static std::shared_ptr<Instant> now();
    static std::shared_ptr<Instant> ofEpochNanos(int64_t nanos);
    static std::shared_ptr<Instant> ofEpochMillis(int64_t ms);
    static std::shared_ptr<Instant> ofEpochSeconds(int64_t s);
    static doof::Result<std::shared_ptr<Instant>, std::string> parse(const std::string& s);
    int64_t toEpochNanos();
    int64_t toEpochMillis();
    int64_t toEpochSeconds();
    std::shared_ptr<Instant> plus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<Instant> minus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<::std_::time::duration::Duration> durationUntil(const std::shared_ptr<Instant>& other);
    std::shared_ptr<::std_::time::duration::Duration> durationSince(const std::shared_ptr<Instant>& other);
    int32_t compareTo(const std::shared_ptr<Instant>& other);
    bool isBefore(const std::shared_ptr<Instant>& other);
    bool isAfter(const std::shared_ptr<Instant>& other);
    bool equals(const std::shared_ptr<Instant>& other);
    std::shared_ptr<DateTime> toDateTime();
    std::shared_ptr<ZonedDateTime> toZonedDateTime(const std::shared_ptr<TimeZone>& zone);
    std::string toISOString();
    static doof::Result<std::shared_ptr<Instant>, std::string> parseHttpDate(const std::string& s);
    std::string toHttpDate();
};
    // A calendar date (year, month, day) with no time-of-day or timezone.
struct Date : public std::enable_shared_from_this<Date> {
    int32_t year;
    int32_t month;
    int32_t day;
    static std::shared_ptr<Date> MIN;
    static std::shared_ptr<Date> MAX;
    Date(int32_t year, int32_t month, int32_t day) : year(year), month(month), day(day) {}
    static doof::Result<std::shared_ptr<Date>, std::string> create(int32_t year, int32_t month, int32_t day);
    static std::shared_ptr<Date> todayUTC();
    static std::shared_ptr<Date> today(const std::shared_ptr<TimeZone>& zone);
    static doof::Result<std::shared_ptr<Date>, std::string> parse(const std::string& s);
    DayOfWeek dayOfWeek();
    int32_t dayOfYear();
    bool isLeapYear();
    int32_t daysInMonth();
    std::shared_ptr<Date> plusDays(int32_t n);
    std::shared_ptr<Date> minusDays(int32_t n);
    std::shared_ptr<Date> plusMonths(int32_t n);
    std::shared_ptr<Date> minusMonths(int32_t n);
    std::shared_ptr<Date> plusYears(int32_t n);
    std::shared_ptr<Date> minusYears(int32_t n);
    int32_t daysUntil(const std::shared_ptr<Date>& other);
    int32_t compareTo(const std::shared_ptr<Date>& other);
    bool isBefore(const std::shared_ptr<Date>& other);
    bool isAfter(const std::shared_ptr<Date>& other);
    bool equals(const std::shared_ptr<Date>& other);
    std::string toISOString();
};
    // A time-of-day with nanosecond precision. No date or timezone.
struct Time : public std::enable_shared_from_this<Time> {
    int32_t hour;
    int32_t minute;
    int32_t second;
    int32_t nanosecond;
    static std::shared_ptr<Time> MIDNIGHT;
    static std::shared_ptr<Time> NOON;
    Time(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond) : hour(hour), minute(minute), second(second), nanosecond(nanosecond) {}
    static doof::Result<std::shared_ptr<Time>, std::string> create(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond);
    static doof::Result<std::shared_ptr<Time>, std::string> parse(const std::string& s);
    std::shared_ptr<Time> plusHours(int32_t n);
    std::shared_ptr<Time> plusMinutes(int32_t n);
    std::shared_ptr<Time> plusSeconds(int32_t n);
    std::shared_ptr<Time> plusNanos(int64_t n);
    int32_t compareTo(const std::shared_ptr<Time>& other);
    bool isBefore(const std::shared_ptr<Time>& other);
    bool isAfter(const std::shared_ptr<Time>& other);
    bool equals(const std::shared_ptr<Time>& other);
    std::string toISOString();
};
    // A combined calendar date and time-of-day. No timezone.
struct DateTime : public std::enable_shared_from_this<DateTime> {
    std::shared_ptr<Date> date;
    std::shared_ptr<Time> time;
    DateTime(std::shared_ptr<Date> date, std::shared_ptr<Time> time) : date(date), time(time) {}
    static std::shared_ptr<DateTime> create(const std::shared_ptr<Date>& date, const std::shared_ptr<Time>& time);
    static doof::Result<std::shared_ptr<DateTime>, std::string> fromParts(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, int32_t nanosecond);
    static std::shared_ptr<DateTime> nowUTC();
    static doof::Result<std::shared_ptr<DateTime>, std::string> parse(const std::string& s);
    std::shared_ptr<DateTime> plusDays(int32_t n);
    std::shared_ptr<DateTime> minusDays(int32_t n);
    std::shared_ptr<DateTime> plusHours(int32_t n);
    std::shared_ptr<DateTime> plusMinutes(int32_t n);
    std::shared_ptr<DateTime> plusSeconds(int32_t n);
    std::shared_ptr<DateTime> plus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<DateTime> minus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<Instant> toInstantUTC();
    std::shared_ptr<Instant> toInstant(const std::shared_ptr<TimeZone>& zone);
    std::shared_ptr<ZonedDateTime> atZone(const std::shared_ptr<TimeZone>& zone);
    int32_t compareTo(const std::shared_ptr<DateTime>& other);
    bool isBefore(const std::shared_ptr<DateTime>& other);
    bool isAfter(const std::shared_ptr<DateTime>& other);
    bool equals(const std::shared_ptr<DateTime>& other);
    std::string toISOString();
};
    // An IANA timezone identifier (e.g. "America/New_York", "UTC").
struct TimeZone : public std::enable_shared_from_this<TimeZone> {
    std::string id;
    static std::shared_ptr<TimeZone> UTC;
    TimeZone(std::string id) : id(id) {}
    static doof::Result<std::shared_ptr<TimeZone>, std::string> lookup(const std::string& id);
    static std::shared_ptr<TimeZone> local();
    int32_t offsetSecondsAt(const std::shared_ptr<Instant>& instant);
    bool isDSTAt(const std::shared_ptr<Instant>& instant);
};
    // A DateTime with an explicit TimeZone.
struct ZonedDateTime : public std::enable_shared_from_this<ZonedDateTime> {
    std::shared_ptr<DateTime> dateTime;
    std::shared_ptr<TimeZone> zone;
    ZonedDateTime(std::shared_ptr<DateTime> dateTime, std::shared_ptr<TimeZone> zone) : dateTime(dateTime), zone(zone) {}
    static std::shared_ptr<ZonedDateTime> now(const std::shared_ptr<TimeZone>& zone);
    static std::shared_ptr<ZonedDateTime> nowUTC();
    std::shared_ptr<Date> date();
    std::shared_ptr<Time> time();
    int32_t offsetSeconds();
    std::shared_ptr<Instant> toInstant();
    std::shared_ptr<ZonedDateTime> withZoneSameInstant(const std::shared_ptr<TimeZone>& newZone);
    std::shared_ptr<ZonedDateTime> withZoneSameLocal(const std::shared_ptr<TimeZone>& newZone);
    std::shared_ptr<DateTime> toDateTime();
    std::shared_ptr<ZonedDateTime> toUTC();
    int32_t compareTo(const std::shared_ptr<ZonedDateTime>& other);
    bool isBefore(const std::shared_ptr<ZonedDateTime>& other);
    bool isAfter(const std::shared_ptr<ZonedDateTime>& other);
    std::string toISOString();
};
}

namespace app_src_std_catalog_ {
    struct StdCatalogPackage : public std::enable_shared_from_this<StdCatalogPackage> {
    std::string name;
    std::string url;
    std::string ref;
    std::string version;
    std::string commit;
    StdCatalogPackage(std::string name, std::string url, std::string ref, std::string version, std::string commit) : name(name), url(url), ref(ref), version(version), commit(commit) {}
};
    struct StdCatalog : public std::enable_shared_from_this<StdCatalog> {
    int32_t schemaVersion;
    std::string compilerVersion;
    std::string digest;
    std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> packages;
    StdCatalog(int32_t schemaVersion, std::string compilerVersion, std::string digest, std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> packages) : schemaVersion(schemaVersion), compilerVersion(compilerVersion), digest(digest), packages(packages) {}
};
}

namespace app_src_dependency_policy_ {
    struct ReachedPackageInput : public std::enable_shared_from_this<ReachedPackageInput> {
    std::string logicalPrefix;
    std::string introducedBy;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    std::string sourceKind;
    std::string sourceUrl;
    std::string sourceRef;
    std::string sourceCommit;
    std::string requestedUrl;
    std::string requestedRef;
    std::string requestedCommit;
    bool mutable_;
    ReachedPackageInput(std::string logicalPrefix, std::string introducedBy, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::string sourceKind, std::string sourceUrl, std::string sourceRef, std::string sourceCommit, std::string requestedUrl, std::string requestedRef, std::string requestedCommit, bool mutable_) : logicalPrefix(logicalPrefix), introducedBy(introducedBy), manifest(manifest), sourceKind(sourceKind), sourceUrl(sourceUrl), sourceRef(sourceRef), sourceCommit(sourceCommit), requestedUrl(requestedUrl), requestedRef(requestedRef), requestedCommit(requestedCommit), mutable_(mutable_) {}
};
    struct ResolvedExternalInput : public std::enable_shared_from_this<ResolvedExternalInput> {
    std::shared_ptr<ReachedPackageInput> owner;
    std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency;
    std::string selectedKind;
    std::string selectedUrl;
    std::string selectedRef;
    std::string selectedCommit;
    std::string selectedSha256;
    bool overridden;
    ResolvedExternalInput(std::shared_ptr<ReachedPackageInput> owner, std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::string selectedKind, std::string selectedUrl, std::string selectedRef, std::string selectedCommit, std::string selectedSha256, bool overridden) : owner(owner), dependency(dependency), selectedKind(selectedKind), selectedUrl(selectedUrl), selectedRef(selectedRef), selectedCommit(selectedCommit), selectedSha256(selectedSha256), overridden(overridden) {}
};
}

namespace app_src_emitter_project_ {
    struct NativePackageInput : public std::enable_shared_from_this<NativePackageInput> {
    std::string logicalPrefix;
    std::string outputRoot;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    NativePackageInput(std::string logicalPrefix, std::string outputRoot, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest) : logicalPrefix(logicalPrefix), outputRoot(outputRoot), manifest(manifest) {}
};
    struct ProjectNativeCopy : public std::enable_shared_from_this<ProjectNativeCopy> {
    std::string sourcePath;
    std::string relativePath;
    ProjectNativeCopy(std::string sourcePath, std::string relativePath) : sourcePath(sourcePath), relativePath(relativePath) {}
};
    struct ProjectSupportFile : public std::enable_shared_from_this<ProjectSupportFile> {
    std::string relativePath;
    std::string content;
    ProjectSupportFile(std::string relativePath, std::string content) : relativePath(relativePath), content(content) {}
};
    struct ProjectEmission : public std::enable_shared_from_this<ProjectEmission> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules;
    std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> supportFiles;
    std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> nativeCopies;
    std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild;
    std::shared_ptr<std::vector<std::string>> wasmExportNames;
    ProjectEmission(std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules, std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> supportFiles, std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> nativeCopies, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::shared_ptr<std::vector<std::string>> wasmExportNames) : modules(modules), supportFiles(supportFiles), nativeCopies(nativeCopies), nativeBuild(nativeBuild), wasmExportNames(wasmExportNames) {}
};
}

namespace app_src_frontend_cache_ {
    struct FrontendSourceProbe : public std::enable_shared_from_this<FrontendSourceProbe> {
    std::string logicalPath;
    std::string sourceHash;
    bool missing;
    FrontendSourceProbe(std::string logicalPath, std::string sourceHash, bool missing) : logicalPath(logicalPath), sourceHash(sourceHash), missing(missing) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendSourceProbe>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct FrontendFileInput : public std::enable_shared_from_this<FrontendFileInput> {
    std::string path;
    std::string sourceHash;
    FrontendFileInput(std::string path, std::string sourceHash) : path(path), sourceHash(sourceHash) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendFileInput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct FrontendModuleOutput : public std::enable_shared_from_this<FrontendModuleOutput> {
    std::string modulePath;
    std::string headerName;
    std::string sourceName;
    std::string fingerprint;
    FrontendModuleOutput(std::string modulePath, std::string headerName, std::string sourceName, std::string fingerprint) : modulePath(modulePath), headerName(headerName), sourceName(sourceName), fingerprint(fingerprint) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendModuleOutput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct FrontendCacheState : public std::enable_shared_from_this<FrontendCacheState> {
    int32_t version;
    std::string configurationFingerprint;
    std::shared_ptr<std::vector<std::shared_ptr<FrontendSourceProbe>>> probes;
    std::shared_ptr<std::vector<std::shared_ptr<FrontendFileInput>>> fileInputs;
    std::shared_ptr<std::vector<std::shared_ptr<FrontendModuleOutput>>> modules;
    FrontendCacheState(int32_t version, std::string configurationFingerprint, std::shared_ptr<std::vector<std::shared_ptr<FrontendSourceProbe>>> probes, std::shared_ptr<std::vector<std::shared_ptr<FrontendFileInput>>> fileInputs, std::shared_ptr<std::vector<std::shared_ptr<FrontendModuleOutput>>> modules) : version(version), configurationFingerprint(configurationFingerprint), probes(probes), fileInputs(fileInputs), modules(modules) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendCacheState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
}

namespace app_src_module_acquisition_ {
    struct ModuleAcquisition : public std::enable_shared_from_this<ModuleAcquisition> {
    std::string logicalPrefix;
    std::string diskRoot;
    ModuleAcquisition(std::string logicalPrefix, std::string diskRoot) : logicalPrefix(logicalPrefix), diskRoot(diskRoot) {}
};
}

namespace app_src_package_acquisition_ {
    struct ExactPackageSource : public std::enable_shared_from_this<ExactPackageSource> {
    std::string name;
    std::string expectedManifestName;
    std::string url;
    std::string ref;
    std::string commit;
    ExactPackageSource(std::string name, std::string expectedManifestName, std::string url, std::string ref, std::string commit) : name(name), expectedManifestName(expectedManifestName), url(url), ref(ref), commit(commit) {}
};
    struct AcquiredPackage : public std::enable_shared_from_this<AcquiredPackage> {
    std::shared_ptr<ExactPackageSource> source;
    std::string rootDirectory;
    bool mutable_;
    AcquiredPackage(std::shared_ptr<ExactPackageSource> source, std::string rootDirectory, bool mutable_) : source(source), rootDirectory(rootDirectory), mutable_(mutable_) {}
};
}

namespace app_src_ios_device_ {
    struct IOSDeviceSigningOptions : public std::enable_shared_from_this<IOSDeviceSigningOptions> {
    std::string signIdentity;
    std::string provisioningProfilePath;
    IOSDeviceSigningOptions(std::string signIdentity, std::string provisioningProfilePath) : signIdentity(signIdentity), provisioningProfilePath(provisioningProfilePath) {}
};
}

namespace app_src_project_ {
    struct ProjectSpec : public std::enable_shared_from_this<ProjectSpec> {
    std::string rootDirectory;
    std::string manifestPath;
    std::string name;
    std::string entry;
    std::string buildDirectory;
    bool hasManifest;
    bool explicitEntry;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>> externalDependencies;
    std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild;
    std::string target;
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig;
    ProjectSpec(std::string rootDirectory, std::string manifestPath, std::string name, std::string entry, std::string buildDirectory, bool hasManifest, bool explicitEntry, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>> externalDependencies, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::string target, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig) : rootDirectory(rootDirectory), manifestPath(manifestPath), name(name), entry(entry), buildDirectory(buildDirectory), hasManifest(hasManifest), explicitEntry(explicitEntry), manifest(manifest), resources(resources), externalDependencies(externalDependencies), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
};
}

namespace app_src_run_command_ {
    struct RunInvocation : public std::enable_shared_from_this<RunInvocation> {
    std::string command;
    std::shared_ptr<std::vector<std::string>> arguments;
    std::string directory;
    RunInvocation(std::string command, std::shared_ptr<std::vector<std::string>> arguments, std::string directory) : command(command), arguments(arguments), directory(directory) {}
};
}

namespace app_src_resource_state_ {
    struct MaterializedResource : public std::enable_shared_from_this<MaterializedResource> {
    std::string sourcePath;
    std::string outputPath;
    int64_t sourceSize;
    int64_t sourceModifiedNanos;
    int64_t outputSize;
    int64_t outputModifiedNanos;
    MaterializedResource(std::string sourcePath, std::string outputPath, int64_t sourceSize, int64_t sourceModifiedNanos, int64_t outputSize, int64_t outputModifiedNanos) : sourcePath(sourcePath), outputPath(outputPath), sourceSize(sourceSize), sourceModifiedNanos(sourceModifiedNanos), outputSize(outputSize), outputModifiedNanos(outputModifiedNanos) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MaterializedResource>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct ResourceState : public std::enable_shared_from_this<ResourceState> {
    int32_t version;
    std::shared_ptr<std::vector<std::shared_ptr<MaterializedResource>>> files;
    ResourceState(int32_t version, std::shared_ptr<std::vector<std::shared_ptr<MaterializedResource>>> files) : version(version), files(files) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ResourceState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
}

namespace app_src_test_runner_ {
    struct CoverageFileReport : public std::enable_shared_from_this<CoverageFileReport> {
    std::string path;
    int32_t covered;
    int32_t total;
    int32_t percentTenths;
    std::shared_ptr<std::vector<int32_t>> hitLines;
    std::shared_ptr<std::vector<int32_t>> missedLines;
    CoverageFileReport(std::string path, int32_t covered, int32_t total, int32_t percentTenths, std::shared_ptr<std::vector<int32_t>> hitLines, std::shared_ptr<std::vector<int32_t>> missedLines) : path(path), covered(covered), total(total), percentTenths(percentTenths), hitLines(hitLines), missedLines(missedLines) {}
};
    struct CoverageReport : public std::enable_shared_from_this<CoverageReport> {
    int32_t totalCovered;
    int32_t totalLines;
    int32_t totalPercentTenths;
    std::shared_ptr<std::vector<std::shared_ptr<CoverageFileReport>>> files;
    CoverageReport(int32_t totalCovered, int32_t totalLines, int32_t totalPercentTenths, std::shared_ptr<std::vector<std::shared_ptr<CoverageFileReport>>> files) : totalCovered(totalCovered), totalLines(totalLines), totalPercentTenths(totalPercentTenths), files(files) {}
};
    struct DiscoveredTest : public std::enable_shared_from_this<DiscoveredTest> {
    std::string id;
    std::string name;
    std::string modulePath;
    std::string moduleDisplayPath;
    bool usesMocks;
    DiscoveredTest(std::string id, std::string name, std::string modulePath, std::string moduleDisplayPath, bool usesMocks) : id(id), name(name), modulePath(modulePath), moduleDisplayPath(moduleDisplayPath), usesMocks(usesMocks) {}
};
    struct TestCompilationGroup : public std::enable_shared_from_this<TestCompilationGroup> {
    std::string outputName;
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests;
    TestCompilationGroup(std::string outputName, std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests) : outputName(outputName), tests(tests) {}
};
    struct TestDiscovery : public std::enable_shared_from_this<TestDiscovery> {
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests;
    std::shared_ptr<std::vector<std::string>> errors;
    TestDiscovery(std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> tests, std::shared_ptr<std::vector<std::string>> errors) : tests(tests), errors(errors) {}
};
}

namespace app_src_wasm_test_runner_ {
    struct WasmTestRunnerPlan : public std::enable_shared_from_this<WasmTestRunnerPlan> {
    std::string command;
    std::shared_ptr<std::vector<std::string>> arguments;
    WasmTestRunnerPlan(std::string command, std::shared_ptr<std::vector<std::string>> arguments) : command(command), arguments(arguments) {}
};
}

namespace app_src_driver_ {
    struct NativeCommandResult : public std::enable_shared_from_this<NativeCommandResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> output;
    std::string error;
    bool truncated;
    NativeCommandResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> output, std::string error, bool truncated) : exitCode(exitCode), output(output), error(error), truncated(truncated) {}
};
    struct TestExecutionResult : public std::enable_shared_from_this<TestExecutionResult> {
    std::string id;
    std::shared_ptr<NativeCommandResult> command;
    TestExecutionResult(std::string id, std::shared_ptr<NativeCommandResult> command) : id(id), command(command) {}
};
    struct TestWorkerCompletion : public std::enable_shared_from_this<TestWorkerCompletion> {
    int32_t workerIndex;
    std::shared_ptr<TestExecutionResult> test;
    TestWorkerCompletion(int32_t workerIndex, std::shared_ptr<TestExecutionResult> test) : workerIndex(workerIndex), test(test) {}
};
    struct TestProcessWorker : public std::enable_shared_from_this<TestProcessWorker> {
    std::string command;
    std::string wasmModule;
    std::string directory;
    int64_t maxOutputBytes;
    TestProcessWorker(std::string command, std::string wasmModule, std::string directory, int64_t maxOutputBytes) : command(command), wasmModule(wasmModule), directory(directory), maxOutputBytes(maxOutputBytes) {}
    std::shared_ptr<TestWorkerCompletion> runTest(int32_t workerIndex, const std::string& id);
};
    struct DriverSourceRoot : public std::enable_shared_from_this<DriverSourceRoot> {
    std::string logicalPrefix;
    std::string diskRoot;
    DriverSourceRoot(std::string logicalPrefix, std::string diskRoot) : logicalPrefix(logicalPrefix), diskRoot(diskRoot) {}
};
    struct DriverReachedPackage : public std::enable_shared_from_this<DriverReachedPackage> {
    std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    std::string introducedBy;
    std::string sourceKind;
    std::string sourceUrl;
    std::string sourceRef;
    std::string sourceCommit;
    std::string requestedUrl;
    std::string requestedRef;
    std::string requestedCommit;
    bool mutable_;
    DriverReachedPackage(std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::string introducedBy, std::string sourceKind, std::string sourceUrl, std::string sourceRef, std::string sourceCommit, std::string requestedUrl, std::string requestedRef, std::string requestedCommit, bool mutable_) : acquisition(acquisition), manifest(manifest), introducedBy(introducedBy), sourceKind(sourceKind), sourceUrl(sourceUrl), sourceRef(sourceRef), sourceCommit(sourceCommit), requestedUrl(requestedUrl), requestedRef(requestedRef), requestedCommit(requestedCommit), mutable_(mutable_) {}
};
    struct DriverAcquiredSource : public std::enable_shared_from_this<DriverAcquiredSource> {
    std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition;
    std::string introducedBy;
    std::string sourceKind;
    std::string sourceUrl;
    std::string sourceRef;
    std::string sourceCommit;
    std::string requestedUrl;
    std::string requestedRef;
    std::string requestedCommit;
    bool mutable_;
    DriverAcquiredSource(std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquisition, std::string introducedBy, std::string sourceKind, std::string sourceUrl, std::string sourceRef, std::string sourceCommit, std::string requestedUrl, std::string requestedRef, std::string requestedCommit, bool mutable_) : acquisition(acquisition), introducedBy(introducedBy), sourceKind(sourceKind), sourceUrl(sourceUrl), sourceRef(sourceRef), sourceCommit(sourceCommit), requestedUrl(requestedUrl), requestedRef(requestedRef), requestedCommit(requestedCommit), mutable_(mutable_) {}
};
    struct DriverSourceState : public std::enable_shared_from_this<DriverSourceState> {
    std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions;
    std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>> acquiredSources;
    std::shared_ptr<std::vector<std::shared_ptr<DriverReachedPackage>>> reachedPackages;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings;
    std::string nativePlatform;
    std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget> externalTarget;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest;
    std::shared_ptr<::app_src_std_catalog_::StdCatalog> stdCatalog;
    std::string packageAcquisitionRoot;
    DriverSourceState(std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>> localRoots, std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>> acquisitions, std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>> acquiredSources, std::shared_ptr<std::vector<std::shared_ptr<DriverReachedPackage>>> reachedPackages, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>> namespaceMappings, std::string nativePlatform, std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget> externalTarget, std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest, std::shared_ptr<::app_src_std_catalog_::StdCatalog> stdCatalog, std::string packageAcquisitionRoot) : localRoots(localRoots), acquisitions(acquisitions), acquiredSources(acquiredSources), reachedPackages(reachedPackages), namespaceMappings(namespaceMappings), nativePlatform(nativePlatform), externalTarget(externalTarget), rootManifest(rootManifest), stdCatalog(stdCatalog), packageAcquisitionRoot(packageAcquisitionRoot) {}
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

namespace doof_blob { using Endian = ::std_::blob::types::Endian; }
namespace doof_blob { using TextEncoding = ::std_::blob::types::TextEncoding; }
namespace doof_blob { using EncodingError = ::std_::blob::types::EncodingError; }
#include "native_blob.hpp"

namespace std_::crypto::index {
    std::string sha256HexString(const std::string& text);
}

namespace app_src_diagnostics_ {
    bool hasErrorDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics);
}

namespace app_src_compiler_ {
    std::shared_ptr<Compilation> compileWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::string& entryMode, bool coverage, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>>& reusableModules, const std::string& emissionConfigurationFingerprint, bool physicalSourcePaths);
    std::shared_ptr<Compilation> checkWithLoader(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::SourceFile>>>& sources, const std::string& entry, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader, const std::string& entryMode);
}

namespace app_src_lexer_ {
    struct Token {
    TokenType kind;
    int32_t length;
    int32_t valueOffset;
    int32_t valueLength;
    bool needsDecode;
    int32_t line;
    int32_t column;
    int32_t offset;
    Token(TokenType kind, int32_t length, int32_t valueOffset, int32_t valueLength, bool needsDecode, int32_t line, int32_t column, int32_t offset) : kind(kind), length(length), valueOffset(valueOffset), valueLength(valueLength), needsDecode(needsDecode), line(line), column(column), offset(offset) {}
    Token() {}
};
}

namespace app_src_parser_ {
    struct Parser : public std::enable_shared_from_this<Parser> {
    std::string source;
    std::shared_ptr<std::vector<::app_src_lexer_::Token>> tokens;
    int32_t pos;
    bool inForIterable;
    bool inTagAttribute;
    std::string errorMessage;
    int32_t errorLine;
    int32_t errorColumn;
    int32_t errorOffset;
    Parser(std::string source, std::shared_ptr<std::vector<::app_src_lexer_::Token>> tokens, int32_t pos, bool inForIterable, bool inTagAttribute, std::string errorMessage, int32_t errorLine, int32_t errorColumn, int32_t errorOffset) : source(source), tokens(tokens), pos(pos), inForIterable(inForIterable), inTagAttribute(inTagAttribute), errorMessage(errorMessage), errorLine(errorLine), errorColumn(errorColumn), errorOffset(errorOffset) {}
    std::shared_ptr<::app_src_ast_::Program> parse();
    ::app_src_lexer_::Token current();
    ::app_src_lexer_::Token peek(int32_t offset);
    bool atEnd();
    ::app_src_lexer_::Token advance();
    bool check(::app_src_lexer_::TokenType kind);
    bool match(::app_src_lexer_::TokenType kind);
    ::app_src_lexer_::Token expect(::app_src_lexer_::TokenType kind, const std::string& message);
    void fail(const std::string& message);
    std::string expectedLabel(::app_src_lexer_::TokenType kind);
    std::string text(::app_src_lexer_::Token token);
    std::string currentText();
    ::app_src_ast_::AstLocation location();
    ::app_src_ast_::SourceSpan span(::app_src_ast_::AstLocation start);
    bool sameLineAsPrevious();
    bool previousIs(::app_src_lexer_::TokenType kind);
    bool immediatelyAfterPrevious();
    void consumeSemicolon();
    ::app_src_ast_::SourceSpan locationSpan();
    doof_header_type_9 parseStatement();
    doof_header_type_9 parseExport();
    doof_header_type_9 parseConst(bool exported);
    doof_header_type_9 parseReadonly(bool exported);
    doof_header_type_9 parseLet();
    std::shared_ptr<::app_src_ast_::FunctionDeclaration> parseFunction(bool exported, bool static_, bool isolated_, bool private_, bool legacyMethod);
    doof_header_type_9 parseClass(bool exported, bool private_);
    doof_header_type_9 parseInterface(bool exported);
    doof_header_type_9 parseEnum(bool exported);
    doof_header_type_9 parseTypeAlias(bool exported);
    doof_header_type_9 parseImport();
    doof_header_type_9 parseMockImport();
    std::shared_ptr<::app_src_ast_::Block> parseBlock();
    doof_header_type_10 parseCaseExpression();
    bool looksLikePattern(::app_src_lexer_::TokenType separator);
    doof_header_type_9 parseDestructuring(const std::string& shape, const std::string& bindingKind, ::app_src_lexer_::TokenType separator);
    doof_header_type_9 parseTryStatement();
    std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseOptionalType();
    std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> parseTypeAnnotation();
    doof_header_type_10 parseExpression();
    doof_header_type_10 parseAdditive();
    doof_header_type_10 parseUnary();
};
}

namespace app_src_cli_ {
    std::string cliUsage();
    std::shared_ptr<CliParseResult> parseCli(const std::shared_ptr<std::vector<std::string>>& args);
}

namespace std_::path::index {
    doof::Result<std::string, std::string> absolute(const std::string& path);
}

namespace app_src_macos_app_ {
    std::string macOSPackageArchiveName(const std::string& executableName, const std::string& version);
}

namespace app_src_ios_app_ {
    std::string iosPackageArchiveName(const std::string& executableName, const std::string& version);
    doof::Result<std::string, std::string> iosTargetTriple(const std::string& minimumDeploymentTarget, const std::string& destination, const std::string& architecture);
}

namespace app_src_package_manifest_ {
    doof::Result<std::shared_ptr<PackageManifest>, std::string> parsePackageManifest(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& targetOverride);
}

namespace std_::fs::types {
    struct FileInfo : public std::enable_shared_from_this<FileInfo> {
    std::string name;
    EntryKind kind;
    int64_t size;
    std::shared_ptr<::std_::time::temporal::Instant> modifiedAt;
    FileInfo(std::string name, EntryKind kind, int64_t size, std::shared_ptr<::std_::time::temporal::Instant> modifiedAt) : name(name), kind(kind), size(size), modifiedAt(modifiedAt) {}
};
}

namespace doof_fs { using IoError = ::std_::fs::types::IoError; }
using IoError = ::std_::fs::types::IoError;
namespace doof_fs { using FileInfo = ::std_::fs::types::FileInfo; }
namespace doof_fs { using EntryKind = ::std_::fs::types::EntryKind; }
using EntryKind = ::std_::fs::types::EntryKind;
using FileInfo = ::std_::fs::types::FileInfo;
#include "native_fs.hpp"

namespace std_::fs::index {
    bool exists(const std::string& path);
    doof::Result<std::string, ::std_::fs::types::IoError> readText(const std::string& path);
    doof::Result<void, ::std_::fs::types::IoError> mkdir(const std::string& path);
    bool isDirectory(const std::string& path);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>>, ::std_::fs::types::IoError> readDir(const std::string& path);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBlob(const std::string& path);
    doof::Result<void, ::std_::fs::types::IoError> writeText(const std::string& path, const std::string& content);
    doof::Result<void, ::std_::fs::types::IoError> rename(const std::string& sourcePath, const std::string& destPath);
    doof::Result<void, ::std_::fs::types::IoError> remove(const std::string& path);
    doof::Result<void, ::std_::fs::types::IoError> writeBlob(const std::string& path, const std::shared_ptr<std::vector<uint8_t>>& data);
    doof::Result<std::shared_ptr<::std_::fs::types::FileInfo>, ::std_::fs::types::IoError> metadata(const std::string& path);
    doof::Result<void, ::std_::fs::types::IoError> copyPermissions(const std::string& sourcePath, const std::string& destPath);
    bool isFile(const std::string& path);
    doof::Result<std::string, ::std_::fs::types::IoError> readTextResource(const std::string& path);
}

namespace std_::os::index {
    struct ExecOptions : public std::enable_shared_from_this<ExecOptions> {
    std::optional<std::string> cwd;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env;
    bool inheritEnv;
    bool withStdin;
    bool mergeStderrIntoStdout;
    bool inheritOutput;
    ProcessGroupMode processGroupMode;
    std::optional<int64_t> maxOutputBytes;
    std::shared_ptr<::std_::time::duration::Duration> timeout;
    ExecOptions(std::optional<std::string> cwd, std::shared_ptr<doof::ordered_map<std::string, std::string>> env, bool inheritEnv, bool withStdin, bool mergeStderrIntoStdout, bool inheritOutput, ProcessGroupMode processGroupMode, std::optional<int64_t> maxOutputBytes, std::shared_ptr<::std_::time::duration::Duration> timeout) : cwd(cwd), env(env), inheritEnv(inheritEnv), withStdin(withStdin), mergeStderrIntoStdout(mergeStderrIntoStdout), inheritOutput(inheritOutput), processGroupMode(processGroupMode), maxOutputBytes(maxOutputBytes), timeout(timeout) {}
};
    std::string platform();
    std::string architecture();
    doof::Result<std::shared_ptr<ExecResult>, std::string> run(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options);
}

namespace app_src_external_dependency_ {
    doof::Result<void, std::string> acquirePackageExternalDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::shared_ptr<ExternalDependencyTarget>& target);
}

namespace app_src_std_catalog_ {
    std::string canonicalDependencyUrl(const std::string& value);
    doof::Result<std::shared_ptr<StdCatalog>, std::string> parseStdCatalog(const std::string& source);
    std::shared_ptr<StdCatalogPackage> stdCatalogPackage(const std::shared_ptr<StdCatalog>& catalog, const std::string& name);
}

namespace app_src_dependency_policy_ {
    bool hasMutableStdPackageInputs(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages);
    std::shared_ptr<::app_src_package_manifest_::PackageDependency> selectedPackageSource(const std::shared_ptr<::app_src_package_manifest_::PackageDependency>& dependency, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>& resolutions);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>, std::string> resolveExternalInputs(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest);
    doof::Result<void, std::string> validateDependencyPolicy(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages, const std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>& externals, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest);
}

namespace app_src_emitter_project_ {
    std::shared_ptr<ProjectEmission> planProjectEmission(const std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission>& graph, const std::shared_ptr<std::vector<std::shared_ptr<NativePackageInput>>>& packages);
}

namespace app_src_frontend_cache_ {
    std::shared_ptr<FrontendCacheState> parseFrontendCacheState(const std::string& source);
    std::string renderFrontendCacheState(const std::shared_ptr<FrontendCacheState>& state);
}

namespace app_src_module_acquisition_ {
    std::shared_ptr<ModuleAcquisition> acquiredPackageForModule(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions);
    std::optional<std::string> acquiredModuleDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<ModuleAcquisition>>>& acquisitions);
    std::string acquiredManifestPath(const std::shared_ptr<ModuleAcquisition>& acquisition);
}

namespace app_src_progress_ {
    std::string renderProgressBar(int32_t completed, int32_t total, int32_t width);
    int32_t boundedWorkerCount(int32_t itemCount, int32_t maximumWorkers);
}

namespace app_src_native_build_driver_ {
    int32_t buildNativeProject(const std::string& compilerOverride, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project, ::app_src_native_build_::NativeBuildMode mode, const std::string& platform, NativeBuildOutputMode outputMode, bool wasmCommand);
}

namespace app_src_package_acquisition_ {
    std::string workspacePackageAcquisitionRoot(const std::string& workspaceRoot);
    doof::Result<std::shared_ptr<AcquiredPackage>, std::string> acquireExactGitPackage(const std::shared_ptr<ExactPackageSource>& source, const std::string& packagesRoot);
}

namespace app_src_macos_app_driver_ {
    doof::Result<std::string, std::string> assembleMacOSApp(const std::string& buildDirectory, const std::string& executablePath, const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::shared_ptr<std::vector<std::string>>& libraryPaths);
    doof::Result<void, std::string> signAndArchiveMacOSApp(const std::string& appPath, const std::string& archivePath, const std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>& config, const std::string& buildDirectory);
}

namespace app_src_ios_device_ {
    doof::Result<std::shared_ptr<IOSDeviceSigningOptions>, std::string> resolveIOSDeviceSigningOptions(const std::string& bundleId, const std::string& signIdentityOverride, const std::string& provisioningProfileOverride, const std::string& workDirectory, const std::shared_ptr<std::vector<std::string>>& profileDirectories);
    doof::Result<std::string, std::string> resolveIOSDeviceIdentifier(const std::string& overrideIdentifier, const std::string& workDirectory);
    doof::Result<void, std::string> signIOSDeviceApp(const std::string& appPath, const std::string& bundleId, const std::shared_ptr<IOSDeviceSigningOptions>& options, const std::string& workDirectory);
}

namespace app_src_ios_app_driver_ {
    doof::Result<void, std::string> configureIOSNativeBuild(const std::string& outputDirectory, const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& destination, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native);
    doof::Result<std::string, std::string> assembleIOSApp(const std::string& buildDirectory, const std::string& executablePath, const std::shared_ptr<::app_src_ios_app_::IOSAppConfig>& config, const std::string& destination);
    doof::Result<void, std::string> signAndArchiveIOSApp(const std::string& appPath, const std::string& archivePath, const std::string& bundleId, const std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>& config, const std::string& buildDirectory);
}

namespace app_src_project_ {
    std::string environmentValue(const std::string& name);
    std::string fileName(const std::string& path);
    std::string parentPath(const std::string& path);
    std::string joinPath(const std::string& directory, const std::string& name);
    std::string projectEntryRequestError(const std::shared_ptr<ProjectSpec>& project, const std::string& requestedPath);
    std::shared_ptr<ProjectSpec> readProjectSpec(const std::string& requestedPath, const std::string& platform, const std::string& targetOverride);
}

namespace app_src_provenance_ {
    std::string renderBuildProvenance(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>& packages, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& externals, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& nativeBuild, const std::shared_ptr<::app_src_std_catalog_::StdCatalog>& catalog);
}

namespace app_src_run_command_ {
    std::shared_ptr<RunInvocation> planNativeProgramRun(const std::string& executablePath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planMacOSAppRun(const std::string& appPath, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSSimulatorInstall(const std::string& appPath, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSSimulatorLaunch(const std::string& bundleId, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSDeviceInstall(const std::string& appPath, const std::string& deviceIdentifier, const std::string& packageRoot);
    std::shared_ptr<RunInvocation> planIOSDeviceLaunch(const std::string& bundleId, const std::string& deviceIdentifier, const std::string& packageRoot);
}

namespace app_src_profile_command_ {
    std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileSymbols(const std::string& binaryPath, const std::string& symbolsPath, const std::string& packageRoot);
    std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileCapture(const std::string& targetPath, const std::shared_ptr<std::vector<std::string>>& programArguments, const std::string& packageRoot, const std::string& tracePath, const std::string& timeLimit, bool consoleTarget);
    std::shared_ptr<::app_src_run_command_::RunInvocation> planProfileOpen(const std::string& tracePath, const std::string& packageRoot);
}

namespace app_src_resource_state_ {
    std::shared_ptr<ResourceState> parseResourceState(const std::string& source);
    std::string renderResourceState(const std::shared_ptr<ResourceState>& state);
    std::shared_ptr<MaterializedResource> findMaterializedResource(const std::shared_ptr<ResourceState>& state, const std::string& sourcePath, const std::string& outputPath);
    bool materializedResourceIsCurrent(const std::shared_ptr<MaterializedResource>& previous, int64_t sourceSize, int64_t sourceModifiedNanos, int64_t outputSize, int64_t outputModifiedNanos);
}

namespace app_src_test_runner_ {
    std::shared_ptr<TestDiscovery> discoverModuleTests(const std::shared_ptr<::app_src_ast_::Program>& program, const std::string& modulePath, const std::string& rootDirectory);
    std::shared_ptr<std::vector<std::shared_ptr<TestCompilationGroup>>> groupTestsForCompilation(const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests);
    std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>> filterDiscoveredTests(const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests, const std::string& filter);
    std::string generateTestHarness(const std::string& harnessPath, const std::shared_ptr<std::vector<std::shared_ptr<DiscoveredTest>>>& tests);
    std::string formatParseFailure(const std::string& modulePath, const std::string& source, int32_t line, int32_t column, const std::string& message);
    void mergeCoverageOutput(const std::string& output, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& modules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& hitsByModule);
    std::string stripCoverageLines(const std::string& output);
    std::shared_ptr<CoverageReport> buildCoverageReport(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& modules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& hitsByModule, const std::string& rootDirectory);
    std::string renderCoverageJson(const std::shared_ptr<CoverageReport>& report);
    std::string renderCoverageHtml(const std::shared_ptr<CoverageReport>& report, const std::string& fileDirectoryName);
    std::string renderCoverageFileHtml(const std::shared_ptr<CoverageFileReport>& file, const std::string& source, const std::string& indexHref);
    std::string coverageFileRelativePath(const std::string& path);
}

namespace app_src_wasm_test_runner_ {
    std::shared_ptr<WasmTestRunnerPlan> planAppleWasmTestRunnerBuild(const std::string& sourcePath, const std::string& outputPath);
    std::shared_ptr<WasmTestRunnerPlan> planAppleWasmTestRun(const std::string& runnerPath, const std::string& modulePath, const std::string& testId);
}

namespace doof { using Compilation = ::app_src_compiler_::Compilation; }
namespace doof { using CliRequest = ::app_src_cli_::CliRequest; }
namespace doof { using ExternalDependencyTarget = ::app_src_external_dependency_::ExternalDependencyTarget; }
namespace doof { using ReachedPackageInput = ::app_src_dependency_policy_::ReachedPackageInput; }
namespace doof { using ResolvedExternalInput = ::app_src_dependency_policy_::ResolvedExternalInput; }
namespace doof { using NativePackageInput = ::app_src_emitter_project_::NativePackageInput; }
namespace doof { using ProjectEmission = ::app_src_emitter_project_::ProjectEmission; }
namespace doof { using ModuleNamespaceMapping = ::app_src_emitter_names_::ModuleNamespaceMapping; }
namespace doof { using ModuleEmission = ::app_src_emitter_module_::ModuleEmission; }
namespace doof { using ModuleEmissionCacheKey = ::app_src_emitter_module_::ModuleEmissionCacheKey; }
namespace doof { using ModuleGraphEmission = ::app_src_emitter_module_::ModuleGraphEmission; }
namespace doof { using FrontendCacheState = ::app_src_frontend_cache_::FrontendCacheState; }
namespace doof { using FrontendFileInput = ::app_src_frontend_cache_::FrontendFileInput; }
namespace doof { using FrontendModuleOutput = ::app_src_frontend_cache_::FrontendModuleOutput; }
namespace doof { using FrontendSourceProbe = ::app_src_frontend_cache_::FrontendSourceProbe; }
namespace doof { using ModuleAcquisition = ::app_src_module_acquisition_::ModuleAcquisition; }
namespace doof { using NativeBuildOutputMode = ::app_src_native_build_driver_::NativeBuildOutputMode; }
namespace doof { using NativeBuildMode = ::app_src_native_build_::NativeBuildMode; }
namespace doof { using ExternalDependency = ::app_src_package_manifest_::ExternalDependency; }
namespace doof { using NativeBuildPlan = ::app_src_package_manifest_::NativeBuildPlan; }
namespace doof { using PackageDependency = ::app_src_package_manifest_::PackageDependency; }
namespace doof { using PackageManifest = ::app_src_package_manifest_::PackageManifest; }
namespace doof { using PackageResource = ::app_src_package_manifest_::PackageResource; }
namespace doof { using ExactPackageSource = ::app_src_package_acquisition_::ExactPackageSource; }
namespace doof { using Parser = ::app_src_parser_::Parser; }
namespace doof { using MaterializedResource = ::app_src_resource_state_::MaterializedResource; }
namespace doof { using ResourceState = ::app_src_resource_state_::ResourceState; }
namespace doof { using SourceLoader = ::app_src_resolver_::SourceLoader; }
namespace doof { using Diagnostic = ::app_src_semantic_::Diagnostic; }
namespace doof { using SemanticLocation = ::app_src_semantic_::SemanticLocation; }
namespace doof { using SemanticSpan = ::app_src_semantic_::SemanticSpan; }
namespace doof { using SourceFile = ::app_src_semantic_::SourceFile; }
namespace doof { using StdCatalog = ::app_src_std_catalog_::StdCatalog; }
namespace doof { using CoverageModuleMetadata = ::app_src_emitter_module_::CoverageModuleMetadata; }
namespace doof { using CoverageReport = ::app_src_test_runner_::CoverageReport; }
namespace doof { using DiscoveredTest = ::app_src_test_runner_::DiscoveredTest; }
namespace doof { using EntryKind = ::std_::fs::types::EntryKind; }
namespace doof { using ExecOptions = ::std_::os::index::ExecOptions; }
namespace doof { using ProcessGroupMode = ::std_::os::index::ProcessGroupMode; }
namespace doof { using Instant = ::std_::time::temporal::Instant; }
#include "doof_runtime.hpp"

namespace app_src_driver_ {
    void printFlushed(const std::string& value);
    ::app_src_native_build_driver_::NativeBuildOutputMode nativeBuildOutputModeForCommand(const std::string& command);
    int32_t runProfileTarget(const std::shared_ptr<::app_src_cli_::CliRequest>& request, const std::string& targetPath, const std::string& binaryPath, const std::string& symbolsPath, const std::string& packageRoot, const std::string& buildDirectory, const std::string& traceName, bool consoleTarget);
    std::string hostPlatform();
    std::shared_ptr<NativeCommandResult> runNativeCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::optional<std::string>& directory, bool inheritOutput, ::std_::os::index::ProcessGroupMode processGroupMode, int64_t maxOutputBytes);
    int32_t printNativeCommandOutput(const std::shared_ptr<NativeCommandResult>& result, int32_t remainingLines);
    std::string driverWithExtension(const std::string& path);
    std::string driverLogicalPath(const std::string& path);
    std::string driverSourceSuffix(const std::string& path);
    std::string driverOutputPath(const std::string& directory, const std::string& name);
    std::string driverSourceDiskPath(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions);
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> loadDriverSource(const std::string& logicalPath, const std::shared_ptr<std::vector<std::shared_ptr<DriverSourceRoot>>>& localRoots, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions);
    doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>> configuredDriverSource(const std::string& logicalPath);
    std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition> acquiredPackageForLoadedSource(const std::string& logicalPath, const std::shared_ptr<DriverSourceState>& state);
    doof::Result<std::shared_ptr<::app_src_package_manifest_::PackageManifest>, std::string> parseDependencyManifestForTarget(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& nativePlatform, const std::string& rootTarget);
    doof::Result<void, std::shared_ptr<::app_src_semantic_::Diagnostic>> registerReachedPackage(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition);
    std::shared_ptr<DriverAcquiredSource> acquiredSourceFor(const std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>& acquisition);
    doof::Result<void, std::string> ensureStdPackageAcquisition(const std::string& logicalPath);
    doof::Result<void, std::string> ensureStdPackageReached(const std::string& packageName);
    std::shared_ptr<::app_src_semantic_::Diagnostic> driverDiagnostic(const std::string& module, const std::string& message);
    std::string driverSourceDiskRoot(const std::string& path);
    doof::Result<doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>, std::string> sourceLoaderForRequest(const std::string& entryPath, const std::string& stdlibRoot, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_names_::ModuleNamespaceMapping>>>& namespaceMappings, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget);
    doof::Result<void, std::string> configureDeclaredDependencies(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& ownerPrefix, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest, const std::string& packageAcquisitionRoot, const std::string& nativePlatform, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_module_acquisition_::ModuleAcquisition>>>& acquisitions, const std::shared_ptr<std::vector<std::shared_ptr<DriverAcquiredSource>>>& acquiredSources);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> reachedPackageInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>, std::string> resolvedDependencyInputs(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest);
    doof::Result<void, std::string> acquireResolvedExternalInputs(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& inputs, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& target);
    std::shared_ptr<::app_src_package_manifest_::ExternalDependency> selectedExternalDependency(const std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>& input);
    doof::Result<std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>, std::string> externalTargetForRequest(const std::string& target, const std::string& nativePlatform, const std::string& iosDestination, const std::string& iosMinimumVersion);
    std::string driverLogicalPrefix(const std::string& path);
    std::string driverRootLogicalPrefix(const std::string& packageName, const std::string& rootDirectory);
    std::string driverRootLogicalPath(const std::string& path, const std::string& rootDirectory, const std::string& packageName);
    std::string driverPackageOutputRoot(const std::string& logicalPrefix);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_project_::NativePackageInput>>> projectNativePackages(const std::string& projectRoot, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& projectManifest, const std::string& stdlibRoot);
    void ensureOutputDirectory(const std::string& path);
    void materializeNativeCopy(const std::string& sourcePath, const std::string& outputPath);
    void writeTextIfChanged(const std::string& path, const std::string& content);
    void materializeGeneratedText(const std::string& path, const std::string& content);
    std::string frontendCachePath(const std::string& buildDirectory, const std::string& kind);
    std::string frontendConfigurationFingerprint(const std::string& entry, const std::string& entryMode, const std::string& target, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::string& stdlibRoot, const std::string& nativePlatform, const std::shared_ptr<::app_src_external_dependency_::ExternalDependencyTarget>& externalTarget);
    std::string readTextOrEmpty(const std::string& path);
    std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> readFrontendState(const std::string& path);
    bool frontendStateMatches(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& configurationFingerprint, const doof::callback<doof::Result<std::shared_ptr<::app_src_semantic_::SourceFile>, std::shared_ptr<::app_src_semantic_::Diagnostic>>(std::string)>& loader);
    std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState> frontendStateForCompilation(const std::shared_ptr<::app_src_compiler_::Compilation>& result, const std::string& configurationFingerprint, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest);
    std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> cachedModuleGraph(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory);
    bool frontendEmissionCacheSupported(const std::string& target);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmissionCacheKey>>> reusableEmissionKeys(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state, const std::string& outputDirectory);
    void addFrontendFileInput(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_frontend_cache_::FrontendFileInput>>>& inputs, const std::string& path);
    void writeFrontendState(const std::string& path, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& state);
    void removeStaleFrontendOutputs(const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& previous, const std::shared_ptr<::app_src_frontend_cache_::FrontendCacheState>& current, const std::string& outputDirectory);
    void writeBlobIfChanged(const std::string& path, const std::shared_ptr<std::vector<uint8_t>>& content);
    bool blobsEqual(const std::shared_ptr<std::vector<uint8_t>>& left, const std::shared_ptr<std::vector<uint8_t>>& right);
    void materializeProject(const std::string& outputDirectory, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project);
    void materializeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory);
    std::shared_ptr<::app_src_resource_state_::ResourceState> readResourceState(const std::string& path);
    void materializeTrackedResource(const std::string& sourcePath, const std::string& outputPath, const std::shared_ptr<::app_src_resource_state_::ResourceState>& previous, const std::shared_ptr<::app_src_resource_state_::ResourceState>& next);
    bool resourceOutputIsCurrent(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_resource_state_::MaterializedResource>>>& files, const std::string& outputPath);
    void synchronizeExecutableResources(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>& resources, const std::string& outputDirectory, const std::string& statePath);
    void materializeRuntimeHeader(const std::string& outputDirectory);
    doof::Result<std::string, std::string> buildAppleWasmTestRunner(const std::string& buildRoot);
    std::string nativeBuildOutputName(const std::string& projectName, const std::string& nativePlatform);
    void printDiagnostics(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics);
    void collectTestFiles(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results, bool root);
    std::shared_ptr<std::vector<std::string>> sortedTestFiles(const std::shared_ptr<std::vector<std::string>>& values);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>> sortedDiscoveredTests(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_test_runner_::DiscoveredTest>>>& values);
    void mergeCoverageGroup(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& groupModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& groupHits, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::CoverageModuleMetadata>>>& allModules, const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>>& allHits);
    void printCoverageSummary(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report);
    std::string coverageHtmlPath(const std::string& jsonPath);
    std::string writeCoverageHtml(const std::shared_ptr<::app_src_test_runner_::CoverageReport>& report, const std::string& jsonPath, const std::string& rootDirectory);
    int32_t testRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request);
    std::shared_ptr<TestExecutionResult> findTestExecutionResult(const std::shared_ptr<std::vector<std::shared_ptr<TestExecutionResult>>>& results, const std::string& id);
    int32_t emitRequest(const std::shared_ptr<::app_src_cli_::CliRequest>& request);
    int32_t doof_main(const std::shared_ptr<std::vector<std::string>>& args);
}
