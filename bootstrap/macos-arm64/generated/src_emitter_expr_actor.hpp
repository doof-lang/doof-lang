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
namespace app_src_ast_ { struct ActorCreationExpression; }
namespace app_src_ast_ { struct AsyncExpression; }
namespace app_src_ast_ { struct Block; }
namespace app_src_ast_ { struct CallExpression; }
namespace app_src_ast_ { struct MemberExpression; }
namespace app_src_ast_ { struct RetireExpression; }
namespace app_src_semantic_ { struct ActorType; }
namespace app_src_semantic_ { struct FunctionType; }
namespace app_src_semantic_ { struct PromiseType; }
namespace app_src_semantic_ { struct NoneType; }
namespace app_src_emitter_context_ { struct EmitContext; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_emitter_expr_actor_ {
}

#include "src_ast.hpp"
#include "src_semantic.hpp"
#include "src_emitter_context.hpp"
#include "src_emitter_expr.hpp"
#include "src_emitter_types.hpp"

namespace app_src_emitter_expr_actor_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    std::string emitActorCreation(std::shared_ptr<::app_src_ast_::ActorCreationExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::string emitAsyncActorCall(std::shared_ptr<::app_src_ast_::AsyncExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::string emitRetireActor(std::shared_ptr<::app_src_ast_::RetireExpression> expression, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::string emitSyncActorCall(std::shared_ptr<::app_src_ast_::CallExpression> expression, std::shared_ptr<::app_src_ast_::MemberExpression> member, std::shared_ptr<::app_src_semantic_::ActorType> actor, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
    std::string emitActorMethodCall(std::shared_ptr<::app_src_ast_::CallExpression> expression, std::shared_ptr<::app_src_ast_::MemberExpression> member, std::shared_ptr<::app_src_semantic_::ActorType> actor, bool async_, std::shared_ptr<::app_src_emitter_context_::EmitContext> context);
}

namespace app_src_emitter_expr_actor_ {
}
