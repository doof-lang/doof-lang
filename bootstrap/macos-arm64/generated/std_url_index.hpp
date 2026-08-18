#pragma once
#include "doof_runtime.hpp"
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }

namespace std_::blob::index {
}

namespace std_::url::punycode_error {
    struct PunycodeError;
}

namespace std_::url::index {
    struct UrlError;
    struct Path;
    struct Authority;
    struct QueryParam;
    struct QueryParams;
}

namespace std_::blob::types {
    enum class Endian {
    BigEndian = 0,
    LittleEndian = 1
};
inline const char* Endian_name(Endian value) {
  switch (value) {
    case Endian::BigEndian: return "BigEndian";
    case Endian::LittleEndian: return "LittleEndian";
  }
  return "";
}
inline std::optional<Endian> Endian_fromName(std::string_view value) {
  if (value == "BigEndian") return Endian::BigEndian;
  if (value == "LittleEndian") return Endian::LittleEndian;
  return std::nullopt;
}
inline std::optional<Endian> Endian_fromValue(int32_t value) {
  switch (static_cast<Endian>(value)) {
    case Endian::BigEndian: return Endian::BigEndian;
    case Endian::LittleEndian: return Endian::LittleEndian;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, Endian value) { return output << Endian_name(value); }
    enum class TextEncoding {
    Utf8 = 0,
    Utf16LE = 1,
    Utf16BE = 2,
    Latin1 = 3,
    Windows1252 = 4,
    CP437 = 5,
    Ascii = 6
};
inline const char* TextEncoding_name(TextEncoding value) {
  switch (value) {
    case TextEncoding::Utf8: return "Utf8";
    case TextEncoding::Utf16LE: return "Utf16LE";
    case TextEncoding::Utf16BE: return "Utf16BE";
    case TextEncoding::Latin1: return "Latin1";
    case TextEncoding::Windows1252: return "Windows1252";
    case TextEncoding::CP437: return "CP437";
    case TextEncoding::Ascii: return "Ascii";
  }
  return "";
}
inline std::optional<TextEncoding> TextEncoding_fromName(std::string_view value) {
  if (value == "Utf8") return TextEncoding::Utf8;
  if (value == "Utf16LE") return TextEncoding::Utf16LE;
  if (value == "Utf16BE") return TextEncoding::Utf16BE;
  if (value == "Latin1") return TextEncoding::Latin1;
  if (value == "Windows1252") return TextEncoding::Windows1252;
  if (value == "CP437") return TextEncoding::CP437;
  if (value == "Ascii") return TextEncoding::Ascii;
  return std::nullopt;
}
inline std::optional<TextEncoding> TextEncoding_fromValue(int32_t value) {
  switch (static_cast<TextEncoding>(value)) {
    case TextEncoding::Utf8: return TextEncoding::Utf8;
    case TextEncoding::Utf16LE: return TextEncoding::Utf16LE;
    case TextEncoding::Utf16BE: return TextEncoding::Utf16BE;
    case TextEncoding::Latin1: return TextEncoding::Latin1;
    case TextEncoding::Windows1252: return TextEncoding::Windows1252;
    case TextEncoding::CP437: return TextEncoding::CP437;
    case TextEncoding::Ascii: return TextEncoding::Ascii;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, TextEncoding value) { return output << TextEncoding_name(value); }
    enum class EncodingError {
    InvalidData = 0,
    UnrepresentableCharacter = 1,
    OutputTooLarge = 2
};
inline const char* EncodingError_name(EncodingError value) {
  switch (value) {
    case EncodingError::InvalidData: return "InvalidData";
    case EncodingError::UnrepresentableCharacter: return "UnrepresentableCharacter";
    case EncodingError::OutputTooLarge: return "OutputTooLarge";
  }
  return "";
}
inline std::optional<EncodingError> EncodingError_fromName(std::string_view value) {
  if (value == "InvalidData") return EncodingError::InvalidData;
  if (value == "UnrepresentableCharacter") return EncodingError::UnrepresentableCharacter;
  if (value == "OutputTooLarge") return EncodingError::OutputTooLarge;
  return std::nullopt;
}
inline std::optional<EncodingError> EncodingError_fromValue(int32_t value) {
  switch (static_cast<EncodingError>(value)) {
    case EncodingError::InvalidData: return EncodingError::InvalidData;
    case EncodingError::UnrepresentableCharacter: return EncodingError::UnrepresentableCharacter;
    case EncodingError::OutputTooLarge: return EncodingError::OutputTooLarge;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, EncodingError value) { return output << EncodingError_name(value); }
}

namespace std_::url::punycode_error {
    struct PunycodeError : public std::enable_shared_from_this<PunycodeError> {
    std::string kind;
    int32_t index;
    std::string message;
    PunycodeError(std::string kind, int32_t index, std::string message) : kind(kind), index(index), message(message) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<PunycodeError>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace std_::url::index {
    struct UrlError : public std::enable_shared_from_this<UrlError> {
    std::string kind;
    int32_t index;
    std::string message;
    UrlError(std::string kind, int32_t index, std::string message) : kind(kind), index(index), message(message) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<UrlError>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct Path : public std::enable_shared_from_this<Path> {
    bool absolute;
    std::shared_ptr<std::vector<std::string>> segments;
    Path(bool absolute, std::shared_ptr<std::vector<std::string>> segments) : absolute(absolute), segments(segments) {}
    bool isEmpty();
    int32_t segmentCount();
    std::string segment(int32_t index);
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Path>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct Authority : public std::enable_shared_from_this<Authority> {
    std::optional<std::string> userinfo;
    std::string host;
    std::optional<std::string> port;
    Authority(std::optional<std::string> userinfo, std::string host, std::optional<std::string> port) : userinfo(userinfo), host(host), port(port) {}
    bool hasUserinfo();
    bool hasPort();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Authority>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct QueryParam : public std::enable_shared_from_this<QueryParam> {
    std::string name;
    std::optional<std::string> value;
    QueryParam(std::string name, std::optional<std::string> value) : name(name), value(value) {}
    bool hasValue();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<QueryParam>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct QueryParams : public std::enable_shared_from_this<QueryParams> {
    std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> entries;
    QueryParams(std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> entries) : entries(entries) {}
    bool isEmpty();
    int32_t size();
    bool has(const std::string& name);
    std::shared_ptr<QueryParam> first(const std::string& name);
    std::shared_ptr<std::vector<std::shared_ptr<QueryParam>>> all(const std::string& name);
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<QueryParams>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace doof_blob { using Endian = ::std_::blob::types::Endian; }
namespace doof_blob { using TextEncoding = ::std_::blob::types::TextEncoding; }
namespace doof_blob { using EncodingError = ::std_::blob::types::EncodingError; }
#include "native_blob.hpp"

namespace std_::url::punycode {
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> encodePunycodeLabel(const std::string& text);
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> decodePunycodeLabel(const std::string& text);
}

namespace std_::url::hostname {
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToAscii(const std::string& hostname);
    doof::Result<std::string, std::shared_ptr<::std_::url::punycode_error::PunycodeError>> hostnameToUnicode(const std::string& hostname);
}

namespace std_::url::index {
    doof::Result<std::shared_ptr<Path>, std::shared_ptr<UrlError>> parsePath(const std::string& text);
    doof::Result<std::shared_ptr<Authority>, std::shared_ptr<UrlError>> parseAuthority(const std::string& text);
    doof::Result<std::shared_ptr<QueryParams>, std::shared_ptr<UrlError>> parseQueryParams(const std::string& text);
    doof::Result<std::string, std::shared_ptr<UrlError>> decodeComponent(const std::string& text, bool plusAsSpace);
    int32_t findChar(const std::string& text, char32_t target);
    int32_t findLastChar(const std::string& text, char32_t target);
    int32_t findSingleChar(const std::string& text, char32_t target);
    int32_t hexValue(char32_t value);
    doof::Result<std::string, std::shared_ptr<UrlError>> invalidPercentEncoding(int32_t index);
    doof::Result<std::shared_ptr<Authority>, std::shared_ptr<UrlError>> invalidAuthority(int32_t index, const std::string& message);
}
