#pragma once
#include "doof_runtime.hpp"
namespace app_src_semantic_ {
    struct Symbol;
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
}

namespace app_src_emitter_carriers_ {
    struct NativeCarrier;
}

namespace app_src_semantic_ {
    using doof_header_type_1 = std::variant<std::monostate, std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_emitter_carriers_ {
    using doof_header_type_2 = std::variant<std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
    using doof_header_type_3 = std::variant<std::monostate, std::shared_ptr<::app_src_semantic_::PrimitiveType>, std::shared_ptr<::app_src_semantic_::ClassType>, std::shared_ptr<::app_src_semantic_::EnumType>, std::shared_ptr<::app_src_semantic_::InterfaceType>, std::shared_ptr<::app_src_semantic_::FunctionType>, std::shared_ptr<::app_src_semantic_::ActorType>, std::shared_ptr<::app_src_semantic_::PromiseType>, std::shared_ptr<::app_src_semantic_::ArrayResolvedType>, std::shared_ptr<::app_src_semantic_::MapResolvedType>, std::shared_ptr<::app_src_semantic_::SetResolvedType>, std::shared_ptr<::app_src_semantic_::StreamResolvedType>, std::shared_ptr<::app_src_semantic_::RangeResolvedType>, std::shared_ptr<::app_src_semantic_::JsonValueResolvedType>, std::shared_ptr<::app_src_semantic_::ResultResolvedType>, std::shared_ptr<::app_src_semantic_::TupleResolvedType>, std::shared_ptr<::app_src_semantic_::UnionResolvedType>, std::shared_ptr<::app_src_semantic_::WeakResolvedType>, std::shared_ptr<::app_src_semantic_::NoneType>, std::shared_ptr<::app_src_semantic_::NeverType>, std::shared_ptr<::app_src_semantic_::UnknownType>, std::shared_ptr<::app_src_semantic_::TypeParameterType>, std::shared_ptr<::app_src_semantic_::ClassMetadataResolvedType>, std::shared_ptr<::app_src_semantic_::MethodReflectionResolvedType>>;
}

namespace app_src_emitter_carriers_ {
    enum class CarrierPosition {
    Value = 0,
    Return = 1,
    Payload = 2
};
inline const char* CarrierPosition_name(CarrierPosition value) {
  switch (value) {
    case CarrierPosition::Value: return "Value";
    case CarrierPosition::Return: return "Return";
    case CarrierPosition::Payload: return "Payload";
  }
  doof::panic(std::string("Invalid CarrierPosition enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<CarrierPosition> CarrierPosition_fromName(std::string_view value) {
  if (value == "Value") return CarrierPosition::Value;
  if (value == "Return") return CarrierPosition::Return;
  if (value == "Payload") return CarrierPosition::Payload;
  return std::nullopt;
}
inline int32_t CarrierPosition_value(CarrierPosition value) { return static_cast<int32_t>(value); }
inline std::optional<CarrierPosition> CarrierPosition_fromValue(int32_t value) {
  if (value == 0) return CarrierPosition::Value;
  if (value == 1) return CarrierPosition::Return;
  if (value == 2) return CarrierPosition::Payload;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<CarrierPosition>> CarrierPosition_values() { return std::make_shared<std::vector<CarrierPosition>>(std::initializer_list<CarrierPosition>{CarrierPosition::Value, CarrierPosition::Return, CarrierPosition::Payload}); }
inline doof::JsonValue CarrierPosition_toJsonValue(CarrierPosition value) { return doof::json_value(CarrierPosition_value(value)); }
inline doof::Result<CarrierPosition, std::string> CarrierPosition_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum CarrierPosition, got ") + doof::json_type_name(value)};
  auto resolved = CarrierPosition_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum CarrierPosition: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2"};
  return doof::Success<CarrierPosition>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, CarrierPosition value) { return output << CarrierPosition_name(value); }
    enum class CarrierKind {
    Value = 0,
    Unit = 1,
    Void = 2,
    SharedPointer = 3,
    Optional = 4,
    WeakPointer = 5,
    Variant = 6,
    Json = 7
};
inline const char* CarrierKind_name(CarrierKind value) {
  switch (value) {
    case CarrierKind::Value: return "Value";
    case CarrierKind::Unit: return "Unit";
    case CarrierKind::Void: return "Void";
    case CarrierKind::SharedPointer: return "SharedPointer";
    case CarrierKind::Optional: return "Optional";
    case CarrierKind::WeakPointer: return "WeakPointer";
    case CarrierKind::Variant: return "Variant";
    case CarrierKind::Json: return "Json";
  }
  doof::panic(std::string("Invalid CarrierKind enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<CarrierKind> CarrierKind_fromName(std::string_view value) {
  if (value == "Value") return CarrierKind::Value;
  if (value == "Unit") return CarrierKind::Unit;
  if (value == "Void") return CarrierKind::Void;
  if (value == "SharedPointer") return CarrierKind::SharedPointer;
  if (value == "Optional") return CarrierKind::Optional;
  if (value == "WeakPointer") return CarrierKind::WeakPointer;
  if (value == "Variant") return CarrierKind::Variant;
  if (value == "Json") return CarrierKind::Json;
  return std::nullopt;
}
inline int32_t CarrierKind_value(CarrierKind value) { return static_cast<int32_t>(value); }
inline std::optional<CarrierKind> CarrierKind_fromValue(int32_t value) {
  if (value == 0) return CarrierKind::Value;
  if (value == 1) return CarrierKind::Unit;
  if (value == 2) return CarrierKind::Void;
  if (value == 3) return CarrierKind::SharedPointer;
  if (value == 4) return CarrierKind::Optional;
  if (value == 5) return CarrierKind::WeakPointer;
  if (value == 6) return CarrierKind::Variant;
  if (value == 7) return CarrierKind::Json;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<CarrierKind>> CarrierKind_values() { return std::make_shared<std::vector<CarrierKind>>(std::initializer_list<CarrierKind>{CarrierKind::Value, CarrierKind::Unit, CarrierKind::Void, CarrierKind::SharedPointer, CarrierKind::Optional, CarrierKind::WeakPointer, CarrierKind::Variant, CarrierKind::Json}); }
inline doof::JsonValue CarrierKind_toJsonValue(CarrierKind value) { return doof::json_value(CarrierKind_value(value)); }
inline doof::Result<CarrierKind, std::string> CarrierKind_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum CarrierKind, got ") + doof::json_type_name(value)};
  auto resolved = CarrierKind_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum CarrierKind: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2, 3, 4, 5, 6, 7"};
  return doof::Success<CarrierKind>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, CarrierKind value) { return output << CarrierKind_name(value); }
}

namespace app_src_semantic_ {
    using ResolvedType = std::variant<std::shared_ptr<PrimitiveType>, std::shared_ptr<ClassType>, std::shared_ptr<EnumType>, std::shared_ptr<InterfaceType>, std::shared_ptr<FunctionType>, std::shared_ptr<ActorType>, std::shared_ptr<PromiseType>, std::shared_ptr<ArrayResolvedType>, std::shared_ptr<MapResolvedType>, std::shared_ptr<SetResolvedType>, std::shared_ptr<StreamResolvedType>, std::shared_ptr<RangeResolvedType>, std::shared_ptr<JsonValueResolvedType>, std::shared_ptr<ResultResolvedType>, std::shared_ptr<TupleResolvedType>, std::shared_ptr<UnionResolvedType>, std::shared_ptr<WeakResolvedType>, std::shared_ptr<NoneType>, std::shared_ptr<NeverType>, std::shared_ptr<UnknownType>, std::shared_ptr<TypeParameterType>, std::shared_ptr<ClassMetadataResolvedType>, std::shared_ptr<MethodReflectionResolvedType>>;
}

namespace app_src_semantic_ {
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

namespace app_src_emitter_carriers_ {
    struct NativeCarrier : public std::enable_shared_from_this<NativeCarrier> {
    CarrierKind kind;
    bool hasNone;
    doof_header_type_3 member;
    bool wrapsOptional;
    bool naturalNullable;
    bool unionLike;
    NativeCarrier(CarrierKind kind, bool hasNone, doof_header_type_3 member, bool wrapsOptional, bool naturalNullable, bool unionLike) : kind(kind), hasNone(hasNone), member(member), wrapsOptional(wrapsOptional), naturalNullable(naturalNullable), unionLike(unionLike) {}
};
    std::shared_ptr<NativeCarrier> carrierOf(const doof_header_type_2& type_, CarrierPosition position);
    doof_header_type_3 naturalCarrierMember(const doof_header_type_2& type_);
    std::shared_ptr<std::vector<doof_header_type_2>> flattenCarrierMembers(const std::shared_ptr<std::vector<doof_header_type_2>>& types);
    bool weakTargetAllowsNone(const doof_header_type_2& type_);
    bool weakTargetUsesVariant(const doof_header_type_2& type_);
}
