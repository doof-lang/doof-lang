#include "src_checker_common.hpp"

namespace app_src_checker_common_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_analyzer_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_types_;
using namespace ::app_src_checker_state_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_validation_;
#line 43 "/src/checker-common.do"
std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>> finish(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType) {
#line 43 "/src/checker-common.do"
    (std::visit([](auto&& _obj) -> decltype(auto) { return (_obj->resolvedType); }, expression) = ::app_src_checker_symbols_::optionalResolvedType(resolvedType));
#line 43 "/src/checker-common.do"
    return resolvedType;
}
#line 44 "/src/checker-common.do"
void typeError(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& message, ::app_src_ast_::SourceSpan span) {
#line 44 "/src/checker-common.do"
    state->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, std::string("")));
}
#line 45 "/src/checker-common.do"
void deprecatedNoneAlias(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::string& spelling, ::app_src_ast_::SourceSpan span, const std::string& module) {
#line 46 "/src/checker-common.do"
    state->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("warning"), ((std::string("'") + spelling) + std::string("' is deprecated; replace it with 'none'")), ::app_src_checker_validation_::checkerSemanticSpan(span), ((module == std::string("")) ? state->info->path : module), std::string("none")));
}
#line 54 "/src/checker-common.do"
void deprecatedBuildReadonly(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, ::app_src_ast_::SourceSpan span) {
#line 55 "/src/checker-common.do"
    state->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("warning"), std::string("'buildReadonly' is deprecated; replace it with 'drainToReadonly'"), ::app_src_checker_validation_::checkerSemanticSpan(span), state->info->path, std::string("drainToReadonly")));
}
#line 63 "/src/checker-common.do"
void deprecatedClassMethodFunction(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::FunctionDeclaration>& fn) {
#line 64 "/src/checker-common.do"
    if (doof::is_null(fn->legacyMethodFunctionSpan)) {
#line 64 "/src/checker-common.do"
        return;
    }
#line 65 "/src/checker-common.do"
    state->diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("warning"), ((std::string("'function' on class methods is deprecated; declare '") + fn->name) + std::string("(...)' without the keyword")), ::app_src_checker_validation_::checkerSemanticSpan(doof::unwrap_optional(fn->legacyMethodFunctionSpan)), state->info->path, fn->name));
}
#line 73 "/src/checker-common.do"
void validateAssignmentBinding(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_semantic_::Binding>& binding, ::app_src_ast_::SourceSpan span) {
#line 74 "/src/checker-common.do"
    if (binding->kind != std::string("field")) {
#line 75 "/src/checker-common.do"
        if (!binding->mutable_) {
#line 75 "/src/checker-common.do"
            typeError(state, ((std::string("Cannot assign to immutable binding '") + binding->name) + std::string("'")), span);
        }
#line 76 "/src/checker-common.do"
        return;
    }
#line 78 "/src/checker-common.do"
    if (binding->mutable_) {
#line 78 "/src/checker-common.do"
        return;
    }
#line 79 "/src/checker-common.do"
    auto suffix = std::string("");
#line 80 "/src/checker-common.do"
    if (binding->fieldMode == std::string("implicit")) {
#line 80 "/src/checker-common.do"
        (suffix = std::string("; declare it with 'let' to allow reassignment"));
    }
#line 81 "/src/checker-common.do"
    typeError(state, (((((std::string("Cannot assign to immutable field '") + binding->fieldOwner) + std::string(".")) + binding->name) + std::string("'")) + suffix), span);
}
#line 83 "/src/checker-common.do"
void requireBool(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& resolvedType, ::app_src_ast_::SourceSpan span) {
#line 84 "/src/checker-common.do"
    {
        auto _case_subject = resolvedType;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::NeverType>>(_case_subject)) {
#line 85 "/src/checker-common.do"
            return;
    }
    else {
    }
    }
#line 88 "/src/checker-common.do"
    if ((::app_src_checker_types_::typeName(resolvedType) != std::string("bool")) && (::app_src_checker_types_::typeName(resolvedType) != std::string("unknown"))) {
#line 88 "/src/checker-common.do"
        typeError(state, (std::string("Expected bool, got ") + ::app_src_checker_types_::typeName(resolvedType)), span);
    }
}
#line 92 "/src/checker-common.do"
void keepAstTypes(const std::shared_ptr<::app_src_checker_state_::CheckerState>& state, const std::shared_ptr<::app_src_ast_::EnumDeclaration>& enum_, const std::shared_ptr<::app_src_ast_::ImportDeclaration>& import_, const std::shared_ptr<::app_src_ast_::ExportDeclaration>& export_, const std::shared_ptr<::app_src_ast_::ExportList>& exports_, const std::shared_ptr<::app_src_ast_::NamedImport>& namedImport, const std::shared_ptr<::app_src_ast_::NamespaceImport>& namespaceImport, const std::shared_ptr<::app_src_ast_::DotShorthand>& dot, const std::shared_ptr<::app_src_ast_::CallerExpression>& caller, const std::shared_ptr<::app_src_ast_::YieldStatement>& yield_) {
}
#line 1 "<doof-generated>"
}
