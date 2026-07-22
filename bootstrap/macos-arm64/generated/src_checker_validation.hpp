#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace app_src_semantic_ { struct ActorType; }
namespace app_src_semantic_ { struct ArrayResolvedType; }
namespace app_src_semantic_ { struct Binding; }
namespace app_src_semantic_ { struct CheckResult; }
namespace app_src_semantic_ { struct ClassType; }
namespace app_src_semantic_ { struct EnumType; }
namespace app_src_semantic_ { struct InterfaceType; }
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct FunctionParamType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct JsonValueResolvedType; }
namespace app_src_semantic_ { struct MapResolvedType; }
namespace app_src_semantic_ { struct NoneType; }
namespace app_src_semantic_ { struct PrimitiveType; }
namespace app_src_semantic_ { struct PromiseType; }
namespace app_src_semantic_ { struct ResultResolvedType; }
namespace app_src_semantic_ { struct Scope; }
namespace app_src_semantic_ { struct SemanticLocation; }
namespace app_src_semantic_ { struct SemanticSpan; }
namespace app_src_semantic_ { struct SetResolvedType; }
namespace app_src_semantic_ { struct Symbol; }
namespace app_src_semantic_ { struct StreamResolvedType; }
namespace app_src_semantic_ { struct TupleResolvedType; }
namespace app_src_semantic_ { struct UnionResolvedType; }
namespace app_src_semantic_ { struct UnknownType; }
namespace app_src_semantic_ { struct TypeParameterType; }
namespace app_src_semantic_ { struct WeakResolvedType; }
namespace app_src_analyzer_ { struct AnalysisResult; }
namespace app_src_analyzer_ { struct ModuleInfo; }
namespace app_src_ast_ { struct ArrayLiteral; }
namespace app_src_ast_ { struct ArrayType; }
namespace app_src_ast_ { struct AsExpression; }
namespace app_src_ast_ { struct AssignmentExpression; }
namespace app_src_ast_ { struct AstLocation; }
namespace app_src_ast_ { struct BinaryExpression; }
namespace app_src_ast_ { struct Block; }
namespace app_src_ast_ { struct BoolLiteral; }
namespace app_src_ast_ { struct CallExpression; }
namespace app_src_ast_ { struct CallerExpression; }
namespace app_src_ast_ { struct CharLiteral; }
namespace app_src_ast_ { struct ClassDeclaration; }
namespace app_src_ast_ { struct ClassField; }
namespace app_src_ast_ { struct ConstructExpression; }
namespace app_src_ast_ { struct ConstDeclaration; }
namespace app_src_ast_ { struct ContinueStatement; }
namespace app_src_ast_ { struct DestructuringStatement; }
namespace app_src_ast_ { struct DoubleLiteral; }
namespace app_src_ast_ { struct DotShorthand; }
namespace app_src_ast_ { struct EnumDeclaration; }
namespace app_src_ast_ { struct ExportDeclaration; }
namespace app_src_ast_ { struct ExportList; }
namespace app_src_ast_ { struct ExpressionStatement; }
namespace app_src_ast_ { struct FloatLiteral; }
namespace app_src_ast_ { struct ForOfStatement; }
namespace app_src_ast_ { struct ForStatement; }
namespace app_src_ast_ { struct FunctionDeclaration; }
namespace app_src_ast_ { struct AstFunctionType; }
namespace app_src_ast_ { struct IfExpression; }
namespace app_src_ast_ { struct IfStatement; }
namespace app_src_ast_ { struct ImmutableBinding; }
namespace app_src_ast_ { struct Identifier; }
namespace app_src_ast_ { struct ImportDeclaration; }
namespace app_src_ast_ { struct IndexExpression; }
namespace app_src_ast_ { struct IntLiteral; }
namespace app_src_ast_ { struct InterfaceDeclaration; }
namespace app_src_ast_ { struct LetDeclaration; }
namespace app_src_ast_ { struct LambdaExpression; }
namespace app_src_ast_ { struct LongLiteral; }
namespace app_src_ast_ { struct MemberExpression; }
namespace app_src_ast_ { struct NamedType; }
namespace app_src_ast_ { struct NoneLiteral; }
namespace app_src_ast_ { struct NamedImport; }
namespace app_src_ast_ { struct NamespaceImport; }
namespace app_src_ast_ { struct ObjectLiteral; }
namespace app_src_ast_ { struct ObjectProperty; }
namespace app_src_ast_ { struct Program; }
namespace app_src_ast_ { struct ReadonlyDeclaration; }
namespace app_src_ast_ { struct ReturnStatement; }
namespace app_src_ast_ { struct SourceSpan; }
namespace app_src_ast_ { struct StringLiteral; }
namespace app_src_ast_ { struct ThisExpression; }
namespace app_src_ast_ { struct TupleLiteral; }
namespace app_src_ast_ { struct TypeAliasDeclaration; }
namespace app_src_ast_ { struct UnaryExpression; }
namespace app_src_ast_ { struct UnionType; }
namespace app_src_ast_ { struct WhileStatement; }
namespace app_src_ast_ { struct WithBinding; }
namespace app_src_ast_ { struct WithStatement; }
namespace app_src_ast_ { struct BreakStatement; }
namespace app_src_ast_ { struct YieldStatement; }
namespace app_src_ast_ { struct YieldBlockExpression; }
namespace app_src_ast_ { struct YieldBlockAssignmentStatement; }
namespace app_src_ast_ { struct CatchExpression; }
namespace app_src_ast_ { struct CaseArm; }
namespace app_src_ast_ { struct CaseExpression; }
namespace app_src_ast_ { struct CaseStatement; }
namespace app_src_ast_ { struct RangePattern; }
namespace app_src_ast_ { struct TypePattern; }
namespace app_src_ast_ { struct ValuePattern; }
namespace app_src_ast_ { struct WildcardPattern; }
namespace app_src_ast_ { struct TryStatement; }
namespace app_src_ast_ { struct AsyncExpression; }
namespace app_src_ast_ { struct RetireExpression; }
namespace app_src_ast_ { struct ActorCreationExpression; }
namespace app_src_ast_ { struct Parameter; }
namespace app_src_ast_ { struct WeakType; }
namespace app_src_ast_ { struct TypeParameterConstraint; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_checker_validation_ {
}

#include "src_semantic.hpp"
#include "src_analyzer.hpp"
#include "src_ast.hpp"
#include "src_checker_types.hpp"
#include "src_json_semantics.hpp"
#include "src_checker_actor_boundary.hpp"
#include "src_checker_actor_lifecycle.hpp"
#include "src_checker_symbols.hpp"

namespace app_src_checker_validation_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> validateCheckedTypes(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result);
    void validateStatement(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void validateValue(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement, std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, std::variant<std::monostate, std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void validateFunction(std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void validateTypeParameterConstraints(std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void validateBlock(std::shared_ptr<::app_src_ast_::Block> block, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void validatePattern(std::variant<std::shared_ptr<::app_src_ast_::TypePattern>, std::shared_ptr<::app_src_ast_::WildcardPattern>, std::shared_ptr<::app_src_ast_::ValuePattern>, std::shared_ptr<::app_src_ast_::RangePattern>> pattern, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void validateExpression(std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>> expression, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    std::shared_ptr<::app_src_ast_::FunctionDeclaration> classConstructor(std::shared_ptr<::app_src_ast_::ClassDeclaration> class_);
    bool spanInsideFunction(::app_src_ast_::SourceSpan span, std::shared_ptr<::app_src_ast_::FunctionDeclaration> fn);
    void validateTypeAnnotation(std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::string module, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void validateResolved(std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType, ::app_src_ast_::SourceSpan span, std::string module, std::string owner, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    void addValidationError(std::string module, ::app_src_ast_::SourceSpan span, std::string message, std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>> diagnostics);
    ::app_src_semantic_::SemanticSpan checkerSemanticSpan(::app_src_ast_::SourceSpan span);
}

namespace app_src_checker_validation_ {
}
