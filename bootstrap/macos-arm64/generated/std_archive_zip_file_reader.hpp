#pragma once
#include "doof_runtime.hpp"
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }
namespace std_::archive::types { struct ZipFileEntry; }

namespace std_::blob::index {
}

namespace std_::archive::types {
    struct ZipFileEntry;
}

namespace std_::archive::reader {
    struct ZipDirectoryInfo;
}

namespace std_::archive::zip_file_reader {
    extern int64_t ZIP_END_SEARCH_SIZE;
    extern int64_t ZIP_LOCAL_HEADER_SIZE;
    extern int64_t MAX_BLOB_SIZE;
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
  doof::panic(std::string("Invalid Endian enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<Endian> Endian_fromName(std::string_view value) {
  if (value == "BigEndian") return Endian::BigEndian;
  if (value == "LittleEndian") return Endian::LittleEndian;
  return std::nullopt;
}
inline int32_t Endian_value(Endian value) { return static_cast<int32_t>(value); }
inline std::optional<Endian> Endian_fromValue(int32_t value) {
  if (value == 0) return Endian::BigEndian;
  if (value == 1) return Endian::LittleEndian;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<Endian>> Endian_values() { return std::make_shared<std::vector<Endian>>(std::initializer_list<Endian>{Endian::BigEndian, Endian::LittleEndian}); }
inline doof::JsonValue Endian_toJsonValue(Endian value) { return doof::json_value(Endian_value(value)); }
inline doof::Result<Endian, std::string> Endian_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum Endian, got ") + doof::json_type_name(value)};
  auto resolved = Endian_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum Endian: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1"};
  return doof::Success<Endian>{resolved.value()};
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
  doof::panic(std::string("Invalid TextEncoding enum value: ") + doof::to_string(static_cast<int32_t>(value)));
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
inline int32_t TextEncoding_value(TextEncoding value) { return static_cast<int32_t>(value); }
inline std::optional<TextEncoding> TextEncoding_fromValue(int32_t value) {
  if (value == 0) return TextEncoding::Utf8;
  if (value == 1) return TextEncoding::Utf16LE;
  if (value == 2) return TextEncoding::Utf16BE;
  if (value == 3) return TextEncoding::Latin1;
  if (value == 4) return TextEncoding::Windows1252;
  if (value == 5) return TextEncoding::CP437;
  if (value == 6) return TextEncoding::Ascii;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<TextEncoding>> TextEncoding_values() { return std::make_shared<std::vector<TextEncoding>>(std::initializer_list<TextEncoding>{TextEncoding::Utf8, TextEncoding::Utf16LE, TextEncoding::Utf16BE, TextEncoding::Latin1, TextEncoding::Windows1252, TextEncoding::CP437, TextEncoding::Ascii}); }
inline doof::JsonValue TextEncoding_toJsonValue(TextEncoding value) { return doof::json_value(TextEncoding_value(value)); }
inline doof::Result<TextEncoding, std::string> TextEncoding_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum TextEncoding, got ") + doof::json_type_name(value)};
  auto resolved = TextEncoding_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum TextEncoding: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2, 3, 4, 5, 6"};
  return doof::Success<TextEncoding>{resolved.value()};
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
  doof::panic(std::string("Invalid EncodingError enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<EncodingError> EncodingError_fromName(std::string_view value) {
  if (value == "InvalidData") return EncodingError::InvalidData;
  if (value == "UnrepresentableCharacter") return EncodingError::UnrepresentableCharacter;
  if (value == "OutputTooLarge") return EncodingError::OutputTooLarge;
  return std::nullopt;
}
inline int32_t EncodingError_value(EncodingError value) { return static_cast<int32_t>(value); }
inline std::optional<EncodingError> EncodingError_fromValue(int32_t value) {
  if (value == 0) return EncodingError::InvalidData;
  if (value == 1) return EncodingError::UnrepresentableCharacter;
  if (value == 2) return EncodingError::OutputTooLarge;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<EncodingError>> EncodingError_values() { return std::make_shared<std::vector<EncodingError>>(std::initializer_list<EncodingError>{EncodingError::InvalidData, EncodingError::UnrepresentableCharacter, EncodingError::OutputTooLarge}); }
inline doof::JsonValue EncodingError_toJsonValue(EncodingError value) { return doof::json_value(EncodingError_value(value)); }
inline doof::Result<EncodingError, std::string> EncodingError_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum EncodingError, got ") + doof::json_type_name(value)};
  auto resolved = EncodingError_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum EncodingError: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2"};
  return doof::Success<EncodingError>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, EncodingError value) { return output << EncodingError_name(value); }
}

namespace std_::archive::types {
    enum class ArchiveEntryKind {
    File = 0,
    Directory = 1
};
inline const char* ArchiveEntryKind_name(ArchiveEntryKind value) {
  switch (value) {
    case ArchiveEntryKind::File: return "File";
    case ArchiveEntryKind::Directory: return "Directory";
  }
  doof::panic(std::string("Invalid ArchiveEntryKind enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<ArchiveEntryKind> ArchiveEntryKind_fromName(std::string_view value) {
  if (value == "File") return ArchiveEntryKind::File;
  if (value == "Directory") return ArchiveEntryKind::Directory;
  return std::nullopt;
}
inline int32_t ArchiveEntryKind_value(ArchiveEntryKind value) { return static_cast<int32_t>(value); }
inline std::optional<ArchiveEntryKind> ArchiveEntryKind_fromValue(int32_t value) {
  if (value == 0) return ArchiveEntryKind::File;
  if (value == 1) return ArchiveEntryKind::Directory;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<ArchiveEntryKind>> ArchiveEntryKind_values() { return std::make_shared<std::vector<ArchiveEntryKind>>(std::initializer_list<ArchiveEntryKind>{ArchiveEntryKind::File, ArchiveEntryKind::Directory}); }
inline doof::JsonValue ArchiveEntryKind_toJsonValue(ArchiveEntryKind value) { return doof::json_value(ArchiveEntryKind_value(value)); }
inline doof::Result<ArchiveEntryKind, std::string> ArchiveEntryKind_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum ArchiveEntryKind, got ") + doof::json_type_name(value)};
  auto resolved = ArchiveEntryKind_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum ArchiveEntryKind: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1"};
  return doof::Success<ArchiveEntryKind>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, ArchiveEntryKind value) { return output << ArchiveEntryKind_name(value); }
    enum class ZipCompression {
    Store = 0,
    Deflate = 8
};
inline const char* ZipCompression_name(ZipCompression value) {
  switch (value) {
    case ZipCompression::Store: return "Store";
    case ZipCompression::Deflate: return "Deflate";
  }
  doof::panic(std::string("Invalid ZipCompression enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<ZipCompression> ZipCompression_fromName(std::string_view value) {
  if (value == "Store") return ZipCompression::Store;
  if (value == "Deflate") return ZipCompression::Deflate;
  return std::nullopt;
}
inline int32_t ZipCompression_value(ZipCompression value) { return static_cast<int32_t>(value); }
inline std::optional<ZipCompression> ZipCompression_fromValue(int32_t value) {
  if (value == 0) return ZipCompression::Store;
  if (value == 8) return ZipCompression::Deflate;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<ZipCompression>> ZipCompression_values() { return std::make_shared<std::vector<ZipCompression>>(std::initializer_list<ZipCompression>{ZipCompression::Store, ZipCompression::Deflate}); }
inline doof::JsonValue ZipCompression_toJsonValue(ZipCompression value) { return doof::json_value(ZipCompression_value(value)); }
inline doof::Result<ZipCompression, std::string> ZipCompression_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum ZipCompression, got ") + doof::json_type_name(value)};
  auto resolved = ZipCompression_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum ZipCompression: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 8"};
  return doof::Success<ZipCompression>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, ZipCompression value) { return output << ZipCompression_name(value); }
}

namespace std_::archive::reader {
    struct ZipDirectoryInfo : public std::enable_shared_from_this<ZipDirectoryInfo> {
    int32_t entryCount;
    int64_t offset;
    int64_t size;
    ZipDirectoryInfo(int32_t entryCount, int64_t offset, int64_t size) : entryCount(entryCount), offset(offset), size(size) {}
};
}

namespace doof_blob { using Endian = ::std_::blob::types::Endian; }
namespace doof_blob { using TextEncoding = ::std_::blob::types::TextEncoding; }
namespace doof_blob { using EncodingError = ::std_::blob::types::EncodingError; }
#include "native_blob.hpp"

namespace std_::archive::types {
    struct ZipFileEntry : public std::enable_shared_from_this<ZipFileEntry> {
    std::string name;
    ArchiveEntryKind kind;
    int64_t size;
    int64_t compressedSize;
    int64_t crc32;
    ZipCompression compression;
    int64_t localHeaderOffset;
    ZipFileEntry(std::string name, ArchiveEntryKind kind, int64_t size, int64_t compressedSize, int64_t crc32, ZipCompression compression, int64_t localHeaderOffset) : name(name), kind(kind), size(size), compressedSize(compressedSize), crc32(crc32), compression(compression), localHeaderOffset(localHeaderOffset) {}
};
}

namespace std_::archive::reader {
    doof::Result<std::shared_ptr<::std_::archive::types::ZipFileEntry>, std::string> readCentralDirectoryEntry(const std::shared_ptr<::doof_blob::NativeBlobReader>& reader);
    doof::Result<int64_t, std::string> findEndOfCentralDirectory(const std::shared_ptr<std::vector<uint8_t>>& data);
    doof::Result<std::shared_ptr<ZipDirectoryInfo>, std::string> readZipDirectoryInfo(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t eocdOffset, int64_t dataOffset, int64_t archiveSize);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> unpackZipPayload(const std::shared_ptr<std::vector<uint8_t>>& compressed, ::std_::archive::types::ZipCompression compression);
    doof::Result<int64_t, std::string> zipPayloadOffset(const std::shared_ptr<std::vector<uint8_t>>& header, int64_t localHeaderOffset);
    doof::Result<void, std::string> validateZipPayload(const std::shared_ptr<std::vector<uint8_t>>& payload, const std::shared_ptr<::std_::archive::types::ZipFileEntry>& central);
}

namespace doof_archive { using ZipFileEntry = ::std_::archive::types::ZipFileEntry; }
#include "native_archive_file.hpp"

namespace std_::archive::zip_file_reader {
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>>, std::string> scanZipFile(const std::string& path);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> readZipEntry(const std::string& path, const std::shared_ptr<::std_::archive::types::ZipFileEntry>& entry);
}
