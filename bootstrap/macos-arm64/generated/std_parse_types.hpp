#pragma once
#include "doof_runtime.hpp"
namespace std_::parse::types {
    enum class ParsingError {
    InvalidFormat = 0,
    Overflow = 1,
    Underflow = 2,
    EmptyInput = 3
};
inline const char* ParsingError_name(ParsingError value) {
  switch (value) {
    case ParsingError::InvalidFormat: return "InvalidFormat";
    case ParsingError::Overflow: return "Overflow";
    case ParsingError::Underflow: return "Underflow";
    case ParsingError::EmptyInput: return "EmptyInput";
  }
  return "";
}
inline std::optional<ParsingError> ParsingError_fromName(std::string_view value) {
  if (value == "InvalidFormat") return ParsingError::InvalidFormat;
  if (value == "Overflow") return ParsingError::Overflow;
  if (value == "Underflow") return ParsingError::Underflow;
  if (value == "EmptyInput") return ParsingError::EmptyInput;
  return std::nullopt;
}
inline std::optional<ParsingError> ParsingError_fromValue(int32_t value) {
  switch (static_cast<ParsingError>(value)) {
    case ParsingError::InvalidFormat: return ParsingError::InvalidFormat;
    case ParsingError::Overflow: return ParsingError::Overflow;
    case ParsingError::Underflow: return ParsingError::Underflow;
    case ParsingError::EmptyInput: return ParsingError::EmptyInput;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, ParsingError value) { return output << ParsingError_name(value); }
}
