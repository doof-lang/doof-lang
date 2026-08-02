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
namespace app_src_ast_ { struct Block; }
namespace app_src_ast_ { struct ClassDeclaration; }
namespace app_src_ast_ { struct ClassField; }
namespace app_src_ast_ { struct ConstDeclaration; }
namespace app_src_ast_ { struct FunctionDeclaration; }
namespace app_src_ast_ { struct InterfaceDeclaration; }
namespace app_src_ast_ { struct ImmutableBinding; }
namespace app_src_ast_ { struct LetDeclaration; }
namespace app_src_ast_ { struct ReadonlyDeclaration; }
namespace app_src_semantic_ { struct ActorType; }
namespace app_src_semantic_ { struct ArrayResolvedType; }
namespace app_src_semantic_ { struct ClassType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct InterfaceType; }
namespace app_src_semantic_ { struct PromiseType; }
namespace app_src_semantic_ { struct ResultResolvedType; }
namespace app_src_semantic_ { struct SetResolvedType; }
namespace app_src_semantic_ { struct StreamResolvedType; }
namespace app_src_semantic_ { struct Symbol; }
namespace app_src_semantic_ { struct TupleResolvedType; }
namespace app_src_semantic_ { struct UnionResolvedType; }
namespace app_src_semantic_ { struct UnknownType; }
namespace app_src_semantic_ { struct NoneType; }
namespace app_src_semantic_ { struct WeakResolvedType; }
namespace app_src_emitter_context_ { struct EmitContext; }
namespace app_src_emitter_monomorphize_ { struct MethodInstantiation; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_emitter_decl_ {
}

#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_stmt.hpp"
#include "src_emitter_types.hpp"
#include "src_emitter_expr_lambda.hpp"
#include "src_emitter_names.hpp"
#include "src_emitter_monomorphize.hpp"
#include "src_emitter_json.hpp"
#include "src_emitter_metadata.hpp"

namespace app_src_emitter_decl_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    std::string emitFunctionSignature(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& name = std::string(""), const std::string& modulePath = std::string(""), bool includeDefaults = false, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& defaultContext = nullptr, const std::shared_ptr<std::vector<std::string>>& ownerTypeParams = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    std::string emitFunctionDefinition(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& name = std::string(""));
    std::string emitFunctionDeclaration(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& name = std::string(""), const std::string& modulePath = std::string(""), const std::shared_ptr<::app_src_emitter_context_::EmitContext>& defaultContext = nullptr);
    std::string emitNativeFunctionAdapterDefinition(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& emittedName, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::string emitValueDeclaration(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::string emitModuleValueStorage(const std::variant<std::shared_ptr<::app_src_ast_::ConstDeclaration>, std::shared_ptr<::app_src_ast_::ReadonlyDeclaration>, std::shared_ptr<::app_src_ast_::ImmutableBinding>, std::shared_ptr<::app_src_ast_::LetDeclaration>>& statement, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& initializer = std::string(""));
    std::string valuePrefix(const std::string& name, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, bool mutable_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::shared_ptr<::app_src_semantic_::FunctionType> checkedFunctionType(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn);
    std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> functionReturnType(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn);
    bool canEmitDefault(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, int32_t index);
    void ensureKnown(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::string& owner);
    std::string emitClassDeclaration(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& decl, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& emittedName = std::string(""), const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>& concreteMethods = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>>(std::vector<std::shared_ptr<::app_src_emitter_monomorphize_::MethodInstantiation>>{}));
    bool defaultNeedsImportedDefinition(const std::string& defaultText, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> fieldTypeForEmission(const std::shared_ptr<::app_src_ast_::ClassField>& field);
    std::string fieldTypeTextForEmission(const std::shared_ptr<::app_src_ast_::ClassField>& field, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    bool hasInstanceFields(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& decl);
    std::string emitStaticClassFieldDefinitions(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::string emitInlineClassMethod(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, const std::string& emittedName = std::string(""));
    std::string templatePrefix(const std::shared_ptr<std::vector<std::string>>& typeParams);
    std::string emitDescriptionComment(const std::string& description, const std::string& indent);
    std::string emitCallableDescription(const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn, const std::string& indent);
    std::string emitInterfaceAlias(const std::shared_ptr<::app_src_ast_::InterfaceDeclaration>& decl, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::string ownedClassName(const std::shared_ptr<::app_src_semantic_::Symbol>& symbol, const std::string& currentModulePath);
    std::string emitClassMethodDefinition(const std::shared_ptr<::app_src_ast_::ClassDeclaration>& owner, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& method, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
    std::string emitExpressionCoverageMark(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context);
}

namespace app_src_emitter_decl_ {
}
