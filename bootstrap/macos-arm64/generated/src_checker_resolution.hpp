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
namespace app_src_semantic_ { struct ClassMetadataResolvedType; }
namespace app_src_semantic_ { struct ClassType; }
namespace app_src_semantic_ { struct EnumType; }
namespace app_src_semantic_ { struct InterfaceType; }
namespace app_src_semantic_ { struct Diagnostic; }
namespace app_src_semantic_ { struct FunctionParamType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct JsonValueResolvedType; }
namespace app_src_semantic_ { struct MapResolvedType; }
namespace app_src_semantic_ { struct MethodReflectionResolvedType; }
namespace app_src_semantic_ { struct NoneType; }
namespace app_src_semantic_ { struct PrimitiveType; }
namespace app_src_semantic_ { struct PromiseType; }
namespace app_src_semantic_ { struct RangeResolvedType; }
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
namespace app_src_semantic_ { struct ResolvedTypeConstraint; }
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
namespace app_src_ast_ { struct CaseArm; }
namespace app_src_ast_ { struct CaseExpression; }
namespace app_src_ast_ { struct CaseStatement; }
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
namespace app_src_checker_state_ { struct CheckerState; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_checker_resolution_ {
}

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

namespace app_src_checker_resolution_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolveType(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::shared_ptr<::app_src_analyzer_::ModuleInfo> module, std::shared_ptr<::app_src_semantic_::Scope> scope);
    void validateTypeArgumentConstraints(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::shared_ptr<std::vector<std::string>> names, std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::TypeParameterConstraint>>> constraints, std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>> arguments, ::app_src_ast_::SourceSpan span, std::shared_ptr<::app_src_analyzer_::ModuleInfo> module, std::shared_ptr<::app_src_semantic_::Scope> outer);
    void reportConstraintViolation(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::string typeParam, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> argument, std::string constraint, ::app_src_ast_::SourceSpan span);
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> decorateType(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_ast_::NamedType>, std::shared_ptr<::app_src_ast_::ArrayType>, std::shared_ptr<::app_src_ast_::UnionType>, std::shared_ptr<::app_src_ast_::AstFunctionType>, std::shared_ptr<::app_src_ast_::WeakType>> annotation, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> resolvedType);
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> memberType(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> object, std::string property, ::app_src_ast_::SourceSpan span);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ast_::Program>>> jsonPrograms(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result);
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> indexType(std::shared_ptr<::app_src_checker_state_::CheckerState> state, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> object, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> index, ::app_src_ast_::SourceSpan span);
}

namespace app_src_checker_resolution_ {
}
