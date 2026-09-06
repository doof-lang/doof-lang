#include "src_emitter_carrier_values.hpp"

namespace app_src_emitter_carrier_values_ {
using namespace ::app_src_semantic_;
using namespace ::app_src_emitter_carriers_;
using namespace ::app_src_emitter_context_;
using namespace ::app_src_emitter_types_;
std::string emitCarrierAbsence(const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& type_, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context) {
    const auto concreteType = ::app_src_emitter_types_::specializeEmitType(type_, context);
    const auto carrier = ::app_src_emitter_carriers_::carrierOf(concreteType, ::app_src_emitter_carriers_::CarrierPosition::Value);
    {
        auto _case_subject = carrier->kind;
        if (_case_subject == ::app_src_emitter_carriers_::CarrierKind::Unit) {
            return std::string("std::monostate{}");
    }
    else if (_case_subject == ::app_src_emitter_carriers_::CarrierKind::SharedPointer) {
            return std::string("nullptr");
    }
    else if (_case_subject == ::app_src_emitter_carriers_::CarrierKind::Optional) {
            return ((std::visit([](auto&& _obj) { return _obj->kind; }, concreteType) == std::string("weak")) ? (::app_src_emitter_types_::emitContextType(concreteType, context) + std::string("{}")) : std::string("std::nullopt"));
    }
    else if (_case_subject == ::app_src_emitter_carriers_::CarrierKind::WeakPointer) {
            return (::app_src_emitter_types_::emitContextType(concreteType, context) + std::string("{}"));
    }
    else if (_case_subject == ::app_src_emitter_carriers_::CarrierKind::Json) {
            return std::string("doof::json_value(nullptr)");
    }
    else if (_case_subject == ::app_src_emitter_carriers_::CarrierKind::Variant) {
            if (carrier->naturalNullable) {
                return (::app_src_emitter_types_::emitContextType(doof::unwrap_optional(carrier->member), context) + std::string("{}"));
            }
            if (carrier->hasNone) {
                return std::string("std::monostate{}");
            }
    }
    else {
    }
    }
    doof::panic((((std::string("No absence carrier for checked type ") + std::visit([](auto&& _obj) { return _obj->kind; }, concreteType)) + std::string(" in ")) + context->modulePath));
}
std::string emitCarrierNullTest(const std::string& value) {
    return ((std::string("doof::is_null(") + value) + std::string(")"));
}
std::string emitCarrierPresentValue(const std::string& value) {
    return ((std::string("doof::unwrap_optional(") + value) + std::string(")"));
}
std::string emitCarrierConversion(const std::string& value, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& source, const std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>& target, const std::shared_ptr<::app_src_emitter_context_::EmitContext>& context, ::app_src_emitter_carriers_::CarrierPosition position) {
    const auto fromType = ::app_src_emitter_types_::specializeEmitType(source, context);
    const auto toType = ::app_src_emitter_types_::specializeEmitType(target, context);
    const auto sourceCarrier = ::app_src_emitter_carriers_::carrierOf(fromType, position);
    const auto targetCarrier = ::app_src_emitter_carriers_::carrierOf(toType, ::app_src_emitter_carriers_::CarrierPosition::Value);
    if ((sourceCarrier->kind == ::app_src_emitter_carriers_::CarrierKind::Void) || ((sourceCarrier->kind == ::app_src_emitter_carriers_::CarrierKind::Unit) && (targetCarrier->kind != ::app_src_emitter_carriers_::CarrierKind::Unit))) {
        return ((((std::string("(static_cast<void>(") + value) + std::string("), ")) + emitCarrierAbsence(toType, context)) + std::string(")"));
    }
    if ((targetCarrier->kind == ::app_src_emitter_carriers_::CarrierKind::Variant) && !targetCarrier->naturalNullable) {
        const auto fromCpp = ::app_src_emitter_types_::emitContextType(fromType, context);
        const auto toCpp = ::app_src_emitter_types_::emitContextType(toType, context);
        if (fromCpp == toCpp) {
            return value;
        }
        if (sourceCarrier->hasNone && sourceCarrier->naturalNullable) {
            return ((((((((((((std::string("[&]() -> ") + toCpp) + std::string(" { const auto& _nullable_value = ")) + value) + std::string("; if (")) + emitCarrierNullTest(std::string("_nullable_value"))) + std::string(") return ")) + emitCarrierAbsence(toType, context)) + std::string("; return doof::variant_promote<")) + toCpp) + std::string(">(")) + emitCarrierPresentValue(std::string("_nullable_value"))) + std::string("); }()"));
        }
        return ((((std::string("doof::variant_promote<") + toCpp) + std::string(">(")) + value) + std::string(")"));
    }
    return value;
}
}
