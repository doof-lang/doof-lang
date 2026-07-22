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
namespace app_src_analyzer_ { struct AnalysisResult; }
namespace app_src_analyzer_ { struct ModuleInfo; }
namespace app_src_semantic_ { struct ActorType; }
namespace app_src_semantic_ { struct ArrayResolvedType; }
namespace app_src_semantic_ { struct ClassType; }
namespace app_src_semantic_ { struct EnumType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct InterfaceType; }
namespace app_src_semantic_ { struct JsonValueResolvedType; }
namespace app_src_semantic_ { struct MapResolvedType; }
namespace app_src_semantic_ { struct NoneType; }
namespace app_src_semantic_ { struct PrimitiveType; }
namespace app_src_semantic_ { struct PromiseType; }
namespace app_src_semantic_ { struct ResultResolvedType; }
namespace app_src_semantic_ { struct SetResolvedType; }
namespace app_src_semantic_ { struct StreamResolvedType; }
namespace app_src_semantic_ { struct TupleResolvedType; }
namespace app_src_semantic_ { struct TypeParameterType; }
namespace app_src_semantic_ { struct UnionResolvedType; }
namespace app_src_semantic_ { struct UnknownType; }
namespace app_src_semantic_ { struct WeakResolvedType; }
namespace app_src_ast_ { struct ClassDeclaration; }
namespace app_src_ast_ { struct ExportDeclaration; }
namespace app_src_ast_ { struct InterfaceDeclaration; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_checker_actor_boundary_ {
    struct ActorBoundaryViolation;
}

#include "src_analyzer.hpp"
#include "src_semantic.hpp"
#include "src_ast.hpp"
#include "src_checker_types.hpp"

namespace app_src_checker_actor_boundary_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ActorBoundaryViolation : public std::enable_shared_from_this<ActorBoundaryViolation> {
    std::string reason;
    ActorBoundaryViolation(std::string reason) : reason(reason) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ActorBoundaryViolation>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<ActorBoundaryViolation> findActorBoundaryViolation(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_);
    std::shared_ptr<ActorBoundaryViolation> findViolation(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> type_, std::shared_ptr<std::vector<std::string>> seen);
    std::shared_ptr<ActorBoundaryViolation> findClassViolation(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::shared_ptr<::app_src_semantic_::ClassType> type_, std::shared_ptr<std::vector<std::string>> seen);
    std::shared_ptr<ActorBoundaryViolation> findInterfaceViolation(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::shared_ptr<::app_src_semantic_::InterfaceType> type_, std::shared_ptr<std::vector<std::string>> seen);
    std::shared_ptr<::app_src_ast_::ClassDeclaration> classDeclaration(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string modulePath, std::string name);
    std::shared_ptr<::app_src_ast_::InterfaceDeclaration> interfaceDeclaration(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string modulePath, std::string name);
    std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> unwrapExport(std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>, std::shared_ptr<::app_src_ast_::FunctionDeclaration>, std::shared_ptr<::app_src_ast_::ClassDeclaration>, std::shared_ptr<::app_src_ast_::InterfaceDeclaration>, std::shared_ptr<::app_src_ast_::EnumDeclaration>, std::shared_ptr<::app_src_ast_::TypeAliasDeclaration>, std::shared_ptr<::app_src_ast_::ImportDeclaration>, std::shared_ptr<::app_src_ast_::MockImportDirective>, std::shared_ptr<::app_src_ast_::ExportDeclaration>, std::shared_ptr<::app_src_ast_::ExportList>, std::shared_ptr<::app_src_ast_::IfStatement>, std::shared_ptr<::app_src_ast_::CaseStatement>, std::shared_ptr<::app_src_ast_::WhileStatement>, std::shared_ptr<::app_src_ast_::ForStatement>, std::shared_ptr<::app_src_ast_::ForOfStatement>, std::shared_ptr<::app_src_ast_::WithStatement>, std::shared_ptr<::app_src_ast_::ReturnStatement>, std::shared_ptr<::app_src_ast_::YieldStatement>, std::shared_ptr<::app_src_ast_::BreakStatement>, std::shared_ptr<::app_src_ast_::ContinueStatement>, std::shared_ptr<::app_src_ast_::ExpressionStatement>, std::shared_ptr<::app_src_ast_::DestructuringStatement>, std::shared_ptr<::app_src_ast_::TryStatement>, std::shared_ptr<::app_src_ast_::YieldBlockAssignmentStatement>, std::shared_ptr<::app_src_ast_::Block>> statement);
    std::shared_ptr<::app_src_analyzer_::ModuleInfo> findModule(std::shared_ptr<::app_src_analyzer_::AnalysisResult> result, std::string path);
    bool containsString(std::shared_ptr<std::vector<std::string>> values, std::string value);
}

namespace app_src_checker_actor_boundary_ {
}
