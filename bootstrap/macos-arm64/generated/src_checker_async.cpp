#include "src_checker_async.hpp"

namespace app_src_checker_async_ {
using namespace ::app_src_analyzer_;
using namespace ::app_src_semantic_;
using namespace ::app_src_ast_;
using namespace ::app_src_checker_actor_boundary_;
using namespace ::app_src_checker_actor_lifecycle_;
using namespace ::app_src_checker_symbols_;
using namespace ::app_src_checker_types_;

#line 22 "/src/checker-async.do"
void validateAsyncBlock(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_ast_::AsyncExpression>& expression, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 23 "/src/checker-async.do"
    {
        auto _case_subject = expression->expression;
        if (doof::variant_is<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>(_case_subject)) {
#line 24 "/src/checker-async.do"
            return;
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Block>>(_case_subject)) {
            const auto& block = std::get<std::shared_ptr<::app_src_ast_::Block>>(_case_subject);
#line 26 "/src/checker-async.do"
            (expression->resolvedCaptureNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 27 "/src/checker-async.do"
            const auto roots = blockExpressions(block);
#line 28 "/src/checker-async.do"
            const auto& _iterable_2 = roots;
            for (const auto& nested : *_iterable_2) {
#line 29 "/src/checker-async.do"
                {
                    auto _case_subject = nested;
                    if (std::holds_alternative<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject)) {
                        const auto& identifier = std::get<std::shared_ptr<::app_src_ast_::Identifier>>(_case_subject);
#line 30 "/src/checker-async.do"
                        validateIdentifierCapture(result, expression, block, identifier, module, diagnostics);
                }
                else if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject)) {
                        const auto& this_ = std::get<std::shared_ptr<::app_src_ast_::ThisExpression>>(_case_subject);
#line 32 "/src/checker-async.do"
                        pushDiagnostic(diagnostics, module, this_->span, std::string("Async blocks cannot capture 'this'; copy deeply immutable values into local bindings first"));
                }
                else {
                }
                }
            }
    }
    }
}
#line 41 "/src/checker-async.do"
std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> blockExpressions(const std::shared_ptr<::app_src_ast_::Block>& block) {
#line 42 "/src/checker-async.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> roots = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 43 "/src/checker-async.do"
    ::app_src_checker_actor_lifecycle_::collectBlockExpressions(block, roots);
#line 44 "/src/checker-async.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> result = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 45 "/src/checker-async.do"
    const auto& _iterable_4 = roots;
    for (const auto& root : *_iterable_4) {
#line 45 "/src/checker-async.do"
        collectTree(root, result);
    }
#line 46 "/src/checker-async.do"
    return result;
}
#line 49 "/src/checker-async.do"
void collectTree(const std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>& expression, const std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>& result) {
#line 50 "/src/checker-async.do"
    result->push_back(expression);
#line 51 "/src/checker-async.do"
    std::shared_ptr<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>> nested = std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>>(std::vector<std::variant<std::shared_ptr<::app_src_ast_::IntLiteral>, std::shared_ptr<::app_src_ast_::LongLiteral>, std::shared_ptr<::app_src_ast_::FloatLiteral>, std::shared_ptr<::app_src_ast_::DoubleLiteral>, std::shared_ptr<::app_src_ast_::StringLiteral>, std::shared_ptr<::app_src_ast_::CharLiteral>, std::shared_ptr<::app_src_ast_::BoolLiteral>, std::shared_ptr<::app_src_ast_::NoneLiteral>, std::shared_ptr<::app_src_ast_::Identifier>, std::shared_ptr<::app_src_ast_::BinaryExpression>, std::shared_ptr<::app_src_ast_::UnaryExpression>, std::shared_ptr<::app_src_ast_::AssignmentExpression>, std::shared_ptr<::app_src_ast_::MemberExpression>, std::shared_ptr<::app_src_ast_::IndexExpression>, std::shared_ptr<::app_src_ast_::CallExpression>, std::shared_ptr<::app_src_ast_::ArrayLiteral>, std::shared_ptr<::app_src_ast_::ObjectLiteral>, std::shared_ptr<::app_src_ast_::TupleLiteral>, std::shared_ptr<::app_src_ast_::LambdaExpression>, std::shared_ptr<::app_src_ast_::IfExpression>, std::shared_ptr<::app_src_ast_::CaseExpression>, std::shared_ptr<::app_src_ast_::ConstructExpression>, std::shared_ptr<::app_src_ast_::DotShorthand>, std::shared_ptr<::app_src_ast_::ThisExpression>, std::shared_ptr<::app_src_ast_::CallerExpression>, std::shared_ptr<::app_src_ast_::AsyncExpression>, std::shared_ptr<::app_src_ast_::RetireExpression>, std::shared_ptr<::app_src_ast_::AsExpression>, std::shared_ptr<::app_src_ast_::ActorCreationExpression>, std::shared_ptr<::app_src_ast_::YieldBlockExpression>, std::shared_ptr<::app_src_ast_::CatchExpression>>>{});
#line 52 "/src/checker-async.do"
    ::app_src_checker_actor_lifecycle_::collectNestedExpressions(expression, nested);
#line 53 "/src/checker-async.do"
    const auto& _iterable_6 = nested;
    for (const auto& child : *_iterable_6) {
#line 53 "/src/checker-async.do"
        collectTree(child, result);
    }
}
#line 56 "/src/checker-async.do"
void validateIdentifierCapture(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_ast_::AsyncExpression>& async_, const std::shared_ptr<::app_src_ast_::Block>& block, const std::shared_ptr<::app_src_ast_::Identifier>& identifier, const std::string& module, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics) {
#line 57 "/src/checker-async.do"
    if (doof::is_null(identifier->resolvedBinding)) {
#line 57 "/src/checker-async.do"
        return;
    }
#line 58 "/src/checker-async.do"
    const auto binding = doof::unwrap_optional(identifier->resolvedBinding);
#line 59 "/src/checker-async.do"
    if ((binding->kind == std::string("field")) || (binding->kind == std::string("method"))) {
#line 60 "/src/checker-async.do"
        pushDiagnostic(diagnostics, module, identifier->span, ((std::string("Async blocks cannot capture 'this' through \"") + identifier->name) + std::string("\"; copy deeply immutable values into local bindings first")));
#line 62 "/src/checker-async.do"
        return;
    }
#line 64 "/src/checker-async.do"
    if (((((!doof::is_null(binding->symbol)) || (binding->kind == std::string("builtin"))) || (binding->kind == std::string("import"))) || (binding->kind == std::string("script-global"))) || (binding->kind == std::string("script-arguments"))) {
#line 65 "/src/checker-async.do"
        return;
    }
#line 66 "/src/checker-async.do"
    if (inside(block->span, binding->span)) {
#line 66 "/src/checker-async.do"
        return;
    }
#line 67 "/src/checker-async.do"
    addCapture(async_->resolvedCaptureNames, binding->name);
#line 68 "/src/checker-async.do"
    if (binding->mutable_) {
#line 69 "/src/checker-async.do"
        pushDiagnostic(diagnostics, module, identifier->span, ((std::string("Async block capture \"") + identifier->name) + std::string("\" must come from an immutable binding")));
#line 71 "/src/checker-async.do"
        return;
    }
#line 73 "/src/checker-async.do"
    std::optional<std::string> reason = std::nullopt;
#line 74 "/src/checker-async.do"
    const auto boundaryViolation = ::app_src_checker_actor_boundary_::findActorBoundaryViolation(result, binding->type_);
#line 75 "/src/checker-async.do"
    if (!doof::is_null(boundaryViolation)) {
#line 75 "/src/checker-async.do"
        (reason = boundaryViolation->reason);
    }
#line 76 "/src/checker-async.do"
    if (doof::is_null(reason)) {
#line 77 "/src/checker-async.do"
        const auto affineViolation = findAsyncAffineViolation(result, binding->type_, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 78 "/src/checker-async.do"
        if (!doof::is_null(affineViolation)) {
#line 78 "/src/checker-async.do"
            (reason = affineViolation->reason);
        }
    }
#line 80 "/src/checker-async.do"
    if (!doof::is_null(reason)) {
#line 81 "/src/checker-async.do"
        pushDiagnostic(diagnostics, module, identifier->span, (((((std::string("Async block capture \"") + identifier->name) + std::string("\" of type \"")) + ::app_src_checker_types_::typeName(binding->type_)) + std::string("\" cannot cross to the worker: ")) + reason.value()));
    }
}
#line 86 "/src/checker-async.do"
bool inside(::app_src_ast_::SourceSpan outer, ::app_src_semantic_::SemanticSpan inner) {
#line 87 "/src/checker-async.do"
    return ((inner.start.offset >= outer.start.offset) && (inner.end.offset <= outer.end.offset));
}
#line 90 "/src/checker-async.do"
void addCapture(const std::shared_ptr<std::vector<std::string>>& names, const std::string& name) {
#line 91 "/src/checker-async.do"
    const auto& _iterable_8 = names;
    for (const auto& existing : *_iterable_8) {
#line 91 "/src/checker-async.do"
        if (existing == name) {
#line 91 "/src/checker-async.do"
            return;
        }
    }
#line 92 "/src/checker-async.do"
    names->push_back(name);
}
#line 95 "/src/checker-async.do"
std::shared_ptr<AsyncBoundaryViolation> findAsyncAffineViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::string>>& seen, const std::shared_ptr<std::vector<std::string>>& safe) {
#line 96 "/src/checker-async.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
#line 97 "/src/checker-async.do"
            return std::make_shared<AsyncBoundaryViolation>(std::string("actor-affine callbacks cannot cross into async blocks"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
#line 98 "/src/checker-async.do"
            return std::make_shared<AsyncBoundaryViolation>(std::string("weak references cannot cross into async blocks"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
#line 99 "/src/checker-async.do"
            return std::make_shared<AsyncBoundaryViolation>(std::string("streams cannot cross into async blocks"));
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 100 "/src/checker-async.do"
            return findAsyncAffineViolation(result, array->elementType, seen, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 102 "/src/checker-async.do"
            const auto violation = findAsyncAffineViolation(result, map->keyType, seen, safe);
#line 103 "/src/checker-async.do"
            if (!doof::is_null(violation)) {
#line 103 "/src/checker-async.do"
                return violation;
            }
#line 104 "/src/checker-async.do"
            return findAsyncAffineViolation(result, map->valueType, seen, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 106 "/src/checker-async.do"
            return findAsyncAffineViolation(result, set_->elementType, seen, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 108 "/src/checker-async.do"
            const auto violation = findAsyncAffineViolation(result, result_->valueType, seen, safe);
#line 109 "/src/checker-async.do"
            if (!doof::is_null(violation)) {
#line 109 "/src/checker-async.do"
                return violation;
            }
#line 110 "/src/checker-async.do"
            return findAsyncAffineViolation(result, result_->errorType, seen, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 113 "/src/checker-async.do"
            const auto& _iterable_10 = tuple->elements;
            for (const auto& element : *_iterable_10) {
#line 114 "/src/checker-async.do"
                const auto violation = findAsyncAffineViolation(result, element, seen, safe);
#line 115 "/src/checker-async.do"
                if (!doof::is_null(violation)) {
#line 115 "/src/checker-async.do"
                    return violation;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 119 "/src/checker-async.do"
            const auto& _iterable_12 = union_->types;
            for (const auto& member : *_iterable_12) {
#line 120 "/src/checker-async.do"
                const auto violation = findAsyncAffineViolation(result, member, seen, safe);
#line 121 "/src/checker-async.do"
                if (!doof::is_null(violation)) {
#line 121 "/src/checker-async.do"
                    return violation;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 124 "/src/checker-async.do"
            return findClassAsyncViolation(result, class_, seen, false, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 125 "/src/checker-async.do"
            return findInterfaceAsyncViolation(result, interface_, seen, false, safe);
    }
    else {
    }
    }
#line 128 "/src/checker-async.do"
    return nullptr;
}
#line 131 "/src/checker-async.do"
std::optional<std::string> asyncResultViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_) {
#line 132 "/src/checker-async.do"
    return findAsyncResultViolation(result, type_, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
}
#line 135 "/src/checker-async.do"
std::optional<std::string> findAsyncResultViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<std::vector<std::string>>& seen, const std::shared_ptr<std::vector<std::string>>& safe) {
#line 136 "/src/checker-async.do"
    {
        auto _case_subject = type_;
        if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ActorType>>(_case_subject)) {
#line 137 "/src/checker-async.do"
            return std::string("Actor<T> references are persistent domains");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::PromiseType>>(_case_subject)) {
#line 138 "/src/checker-async.do"
            return std::string("Promise<T> values are asynchronous handles");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::FunctionType>>(_case_subject)) {
#line 139 "/src/checker-async.do"
            return std::string("actor-affine callbacks cannot be transferred from async blocks");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::WeakResolvedType>>(_case_subject)) {
#line 140 "/src/checker-async.do"
            return std::string("weak references cannot be transferred from async blocks");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::StreamResolvedType>>(_case_subject)) {
#line 141 "/src/checker-async.do"
            return std::string("streams cannot be transferred from async blocks");
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject)) {
            const auto& array = std::get<std::shared_ptr<::app_src_semantic_::ArrayResolvedType>>(_case_subject);
#line 142 "/src/checker-async.do"
            return findAsyncResultViolation(result, array->elementType, seen, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject)) {
            const auto& map = std::get<std::shared_ptr<::app_src_semantic_::MapResolvedType>>(_case_subject);
#line 144 "/src/checker-async.do"
            const auto violation = findAsyncResultViolation(result, map->keyType, seen, safe);
#line 145 "/src/checker-async.do"
            if (!doof::is_null(violation)) {
#line 145 "/src/checker-async.do"
                return violation;
            }
#line 146 "/src/checker-async.do"
            return findAsyncResultViolation(result, map->valueType, seen, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject)) {
            const auto& set_ = std::get<std::shared_ptr<::app_src_semantic_::SetResolvedType>>(_case_subject);
#line 148 "/src/checker-async.do"
            return findAsyncResultViolation(result, set_->elementType, seen, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject)) {
            const auto& result_ = std::get<std::shared_ptr<::app_src_semantic_::ResultResolvedType>>(_case_subject);
#line 150 "/src/checker-async.do"
            const auto violation = findAsyncResultViolation(result, result_->valueType, seen, safe);
#line 151 "/src/checker-async.do"
            if (!doof::is_null(violation)) {
#line 151 "/src/checker-async.do"
                return violation;
            }
#line 152 "/src/checker-async.do"
            return findAsyncResultViolation(result, result_->errorType, seen, safe);
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject)) {
            const auto& tuple = std::get<std::shared_ptr<::app_src_semantic_::TupleResolvedType>>(_case_subject);
#line 155 "/src/checker-async.do"
            const auto& _iterable_14 = tuple->elements;
            for (const auto& element : *_iterable_14) {
#line 156 "/src/checker-async.do"
                const auto violation = findAsyncResultViolation(result, element, seen, safe);
#line 157 "/src/checker-async.do"
                if (!doof::is_null(violation)) {
#line 157 "/src/checker-async.do"
                    return violation;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject)) {
            const auto& union_ = std::get<std::shared_ptr<::app_src_semantic_::UnionResolvedType>>(_case_subject);
#line 161 "/src/checker-async.do"
            const auto& _iterable_16 = union_->types;
            for (const auto& member : *_iterable_16) {
#line 162 "/src/checker-async.do"
                const auto violation = findAsyncResultViolation(result, member, seen, safe);
#line 163 "/src/checker-async.do"
                if (!doof::is_null(violation)) {
#line 163 "/src/checker-async.do"
                    return violation;
                }
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_semantic_::ClassType>>(_case_subject);
#line 167 "/src/checker-async.do"
            const auto violation = findClassAsyncViolation(result, class_, seen, true, safe);
#line 168 "/src/checker-async.do"
            if (!doof::is_null(violation)) {
#line 168 "/src/checker-async.do"
                return violation->reason;
            }
    }
    else if (std::holds_alternative<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_semantic_::InterfaceType>>(_case_subject);
#line 171 "/src/checker-async.do"
            const auto violation = findInterfaceAsyncViolation(result, interface_, seen, true, safe);
#line 172 "/src/checker-async.do"
            if (!doof::is_null(violation)) {
#line 172 "/src/checker-async.do"
                return violation->reason;
            }
    }
    else {
    }
    }
#line 176 "/src/checker-async.do"
    return std::nullopt;
}
#line 179 "/src/checker-async.do"
std::shared_ptr<AsyncBoundaryViolation> findClassAsyncViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::ClassType>& type_, const std::shared_ptr<std::vector<std::string>>& seen, bool resultMode, const std::shared_ptr<std::vector<std::string>>& safe) {
#line 180 "/src/checker-async.do"
    const auto key = (((std::string("class:") + type_->symbol->module) + std::string(":")) + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(type_)));
#line 181 "/src/checker-async.do"
    if (contains(safe, key)) {
#line 181 "/src/checker-async.do"
        return nullptr;
    }
#line 182 "/src/checker-async.do"
    if (contains(seen, key)) {
#line 182 "/src/checker-async.do"
        return nullptr;
    }
#line 183 "/src/checker-async.do"
    const auto next = appended(seen, key);
#line 184 "/src/checker-async.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(result, type_->symbol);
#line 185 "/src/checker-async.do"
    if (doof::is_null(declaration)) {
#line 185 "/src/checker-async.do"
        return nullptr;
    }
#line 186 "/src/checker-async.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject)) {
            const auto& class_ = std::get<std::shared_ptr<::app_src_ast_::ClassDeclaration>>(_case_subject);
#line 188 "/src/checker-async.do"
            const auto& _iterable_18 = class_->fields;
            for (const auto& field : *_iterable_18) {
#line 189 "/src/checker-async.do"
                if (doof::is_null(field->resolvedType)) {
#line 189 "/src/checker-async.do"
                    continue;
                }
#line 190 "/src/checker-async.do"
                const auto effective = ::app_src_checker_types_::substituteTypeParams(doof::unwrap_optional(field->resolvedType), class_->typeParams, type_->typeArgs);
#line 191 "/src/checker-async.do"
                std::optional<std::string> reason = std::nullopt;
#line 192 "/src/checker-async.do"
                if (resultMode) {
#line 192 "/src/checker-async.do"
                    (reason = findAsyncResultViolation(result, effective, next, safe));
                } else {
#line 194 "/src/checker-async.do"
                    const auto violation = findAsyncAffineViolation(result, effective, next, safe);
#line 195 "/src/checker-async.do"
                    if (!doof::is_null(violation)) {
#line 195 "/src/checker-async.do"
                        (reason = violation->reason);
                    }
                }
#line 197 "/src/checker-async.do"
                if (!doof::is_null(reason)) {
#line 198 "/src/checker-async.do"
                    const auto name = ((static_cast<int32_t>((field->names)->size()) == 0) ? std::string("<field>") : doof::array_at(field->names, 0, "src/checker-async", 198));
#line 199 "/src/checker-async.do"
                    return std::make_shared<AsyncBoundaryViolation>((((std::string("field \"") + name) + std::string("\" cannot cross the async boundary: ")) + reason.value()));
                }
            }
    }
    else {
    }
    }
#line 205 "/src/checker-async.do"
    safe->push_back(key);
#line 206 "/src/checker-async.do"
    return nullptr;
}
#line 209 "/src/checker-async.do"
std::shared_ptr<AsyncBoundaryViolation> findInterfaceAsyncViolation(const std::shared_ptr<::app_src_analyzer_::AnalysisResult>& result, const std::shared_ptr<::app_src_semantic_::InterfaceType>& type_, const std::shared_ptr<std::vector<std::string>>& seen, bool resultMode, const std::shared_ptr<std::vector<std::string>>& safe) {
#line 210 "/src/checker-async.do"
    const auto key = (((std::string("interface:") + type_->symbol->module) + std::string(":")) + ::app_src_checker_types_::typeName(doof::variant_promote<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>(type_)));
#line 211 "/src/checker-async.do"
    if (contains(safe, key)) {
#line 211 "/src/checker-async.do"
        return nullptr;
    }
#line 212 "/src/checker-async.do"
    if (contains(seen, key)) {
#line 212 "/src/checker-async.do"
        return nullptr;
    }
#line 213 "/src/checker-async.do"
    const auto next = appended(seen, key);
#line 214 "/src/checker-async.do"
    const auto declaration = ::app_src_checker_symbols_::declarationFor(result, type_->symbol);
#line 215 "/src/checker-async.do"
    if (doof::is_null(declaration)) {
#line 215 "/src/checker-async.do"
        return nullptr;
    }
#line 216 "/src/checker-async.do"
    {
        auto _case_subject = doof::unwrap_optional(declaration);
        if (std::holds_alternative<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject)) {
            const auto& interface_ = std::get<std::shared_ptr<::app_src_ast_::InterfaceDeclaration>>(_case_subject);
#line 218 "/src/checker-async.do"
            const auto& _iterable_20 = interface_->fields;
            for (const auto& field : *_iterable_20) {
#line 219 "/src/checker-async.do"
                if (doof::is_null(field->resolvedType)) {
#line 219 "/src/checker-async.do"
                    continue;
                }
#line 220 "/src/checker-async.do"
                const auto effective = ::app_src_checker_types_::substituteTypeParams(doof::unwrap_optional(field->resolvedType), interface_->typeParams, type_->typeArgs);
#line 221 "/src/checker-async.do"
                std::optional<std::string> reason = std::nullopt;
#line 222 "/src/checker-async.do"
                if (resultMode) {
#line 222 "/src/checker-async.do"
                    (reason = findAsyncResultViolation(result, effective, next, safe));
                } else {
#line 224 "/src/checker-async.do"
                    const auto violation = findAsyncAffineViolation(result, effective, next, safe);
#line 225 "/src/checker-async.do"
                    if (!doof::is_null(violation)) {
#line 225 "/src/checker-async.do"
                        (reason = violation->reason);
                    }
                }
#line 227 "/src/checker-async.do"
                if (!doof::is_null(reason)) {
#line 227 "/src/checker-async.do"
                    return std::make_shared<AsyncBoundaryViolation>((((std::string("field \"") + field->name) + std::string("\" cannot cross the async boundary: ")) + reason.value()));
                }
            }
#line 229 "/src/checker-async.do"
            if (!doof::is_null(interface_->resolvedSymbol)) {
#line 230 "/src/checker-async.do"
                const auto& _iterable_22 = interface_->resolvedSymbol->implementations;
                for (const auto& implementation : *_iterable_22) {
#line 231 "/src/checker-async.do"
                    const auto violation = findClassAsyncViolation(result, std::make_shared<::app_src_semantic_::ClassType>(std::string("class"), implementation->name, implementation, std::make_shared<std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>>(std::vector<std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>>{})), next, resultMode, safe);
#line 232 "/src/checker-async.do"
                    if (!doof::is_null(violation)) {
#line 232 "/src/checker-async.do"
                        return std::make_shared<AsyncBoundaryViolation>((((std::string("implementation \"") + implementation->name) + std::string("\" cannot cross the async boundary: ")) + violation->reason));
                    }
                }
            }
    }
    else {
    }
    }
#line 238 "/src/checker-async.do"
    safe->push_back(key);
#line 239 "/src/checker-async.do"
    return nullptr;
}
#line 242 "/src/checker-async.do"
bool contains(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 243 "/src/checker-async.do"
    const auto& _iterable_24 = values;
    for (const auto& item : *_iterable_24) {
#line 243 "/src/checker-async.do"
        if (item == value) {
#line 243 "/src/checker-async.do"
            return true;
        }
    }
#line 244 "/src/checker-async.do"
    return false;
}
#line 247 "/src/checker-async.do"
std::shared_ptr<std::vector<std::string>> appended(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 248 "/src/checker-async.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 249 "/src/checker-async.do"
    const auto& _iterable_26 = values;
    for (const auto& item : *_iterable_26) {
#line 249 "/src/checker-async.do"
        result->push_back(item);
    }
#line 250 "/src/checker-async.do"
    result->push_back(value);
#line 251 "/src/checker-async.do"
    return result;
}
#line 254 "/src/checker-async.do"
::app_src_semantic_::SemanticSpan semanticSpan(::app_src_ast_::SourceSpan span) {
#line 255 "/src/checker-async.do"
    return ::app_src_semantic_::SemanticSpan{::app_src_semantic_::SemanticLocation{span.start.line, span.start.column, span.start.offset}, ::app_src_semantic_::SemanticLocation{span.end.line, span.end.column, span.end.offset}};
}
#line 261 "/src/checker-async.do"
void pushDiagnostic(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_semantic_::Diagnostic>>>& diagnostics, const std::string& module, ::app_src_ast_::SourceSpan span, const std::string& message) {
#line 262 "/src/checker-async.do"
    diagnostics->push_back(std::make_shared<::app_src_semantic_::Diagnostic>(std::string("error"), message, semanticSpan(span), module, std::string("")));
}
#line 1 "<doof-generated>"
}
