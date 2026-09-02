#pragma once
#include "doof_runtime.hpp"
namespace std_::parse::types {
    enum class ParsingError {
    InvalidFormat = 0,
    Overflow = 1,
    Underflow = 2,
    EmptyInput = 3,
    InvalidRadix = 4,
    NonFinite = 5
};
inline const char* ParsingError_name(ParsingError value) {
  switch (value) {
    case ParsingError::InvalidFormat: return "InvalidFormat";
    case ParsingError::Overflow: return "Overflow";
    case ParsingError::Underflow: return "Underflow";
    case ParsingError::EmptyInput: return "EmptyInput";
    case ParsingError::InvalidRadix: return "InvalidRadix";
    case ParsingError::NonFinite: return "NonFinite";
  }
  doof::panic(std::string("Invalid ParsingError enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<ParsingError> ParsingError_fromName(std::string_view value) {
  if (value == "InvalidFormat") return ParsingError::InvalidFormat;
  if (value == "Overflow") return ParsingError::Overflow;
  if (value == "Underflow") return ParsingError::Underflow;
  if (value == "EmptyInput") return ParsingError::EmptyInput;
  if (value == "InvalidRadix") return ParsingError::InvalidRadix;
  if (value == "NonFinite") return ParsingError::NonFinite;
  return std::nullopt;
}
inline int32_t ParsingError_value(ParsingError value) { return static_cast<int32_t>(value); }
inline std::optional<ParsingError> ParsingError_fromValue(int32_t value) {
  if (value == 0) return ParsingError::InvalidFormat;
  if (value == 1) return ParsingError::Overflow;
  if (value == 2) return ParsingError::Underflow;
  if (value == 3) return ParsingError::EmptyInput;
  if (value == 4) return ParsingError::InvalidRadix;
  if (value == 5) return ParsingError::NonFinite;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<ParsingError>> ParsingError_values() { return std::make_shared<std::vector<ParsingError>>(std::initializer_list<ParsingError>{ParsingError::InvalidFormat, ParsingError::Overflow, ParsingError::Underflow, ParsingError::EmptyInput, ParsingError::InvalidRadix, ParsingError::NonFinite}); }
inline doof::JsonValue ParsingError_toJsonValue(ParsingError value) { return doof::json_value(ParsingError_value(value)); }
inline doof::Result<ParsingError, std::string> ParsingError_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum ParsingError, got ") + doof::json_type_name(value)};
  auto resolved = ParsingError_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum ParsingError: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2, 3, 4, 5"};
  return doof::Success<ParsingError>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, ParsingError value) { return output << ParsingError_name(value); }
}
