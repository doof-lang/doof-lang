#pragma once
#include "doof_runtime.hpp"
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }
namespace std_::fs::types { enum class FileMode; }
namespace std_::fs::types { enum class FileLock; }
namespace std_::fs::types { enum class IoError; }
namespace std_::fs::file { struct File; }
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }

namespace std_::blob::index {
}

namespace std_::fs::file {
    struct File;
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

namespace std_::fs::types {
    enum class IoError {
    NotFound = 0,
    PermissionDenied = 1,
    AlreadyExists = 2,
    IsDirectory = 3,
    NotDirectory = 4,
    InvalidPath = 5,
    Interrupted = 6,
    Other = 7,
    Unsupported = 8,
    InvalidArgument = 9,
    Closed = 10,
    UnexpectedEof = 11,
    WouldBlock = 12
};
inline const char* IoError_name(IoError value) {
  switch (value) {
    case IoError::NotFound: return "NotFound";
    case IoError::PermissionDenied: return "PermissionDenied";
    case IoError::AlreadyExists: return "AlreadyExists";
    case IoError::IsDirectory: return "IsDirectory";
    case IoError::NotDirectory: return "NotDirectory";
    case IoError::InvalidPath: return "InvalidPath";
    case IoError::Interrupted: return "Interrupted";
    case IoError::Other: return "Other";
    case IoError::Unsupported: return "Unsupported";
    case IoError::InvalidArgument: return "InvalidArgument";
    case IoError::Closed: return "Closed";
    case IoError::UnexpectedEof: return "UnexpectedEof";
    case IoError::WouldBlock: return "WouldBlock";
  }
  doof::panic(std::string("Invalid IoError enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<IoError> IoError_fromName(std::string_view value) {
  if (value == "NotFound") return IoError::NotFound;
  if (value == "PermissionDenied") return IoError::PermissionDenied;
  if (value == "AlreadyExists") return IoError::AlreadyExists;
  if (value == "IsDirectory") return IoError::IsDirectory;
  if (value == "NotDirectory") return IoError::NotDirectory;
  if (value == "InvalidPath") return IoError::InvalidPath;
  if (value == "Interrupted") return IoError::Interrupted;
  if (value == "Other") return IoError::Other;
  if (value == "Unsupported") return IoError::Unsupported;
  if (value == "InvalidArgument") return IoError::InvalidArgument;
  if (value == "Closed") return IoError::Closed;
  if (value == "UnexpectedEof") return IoError::UnexpectedEof;
  if (value == "WouldBlock") return IoError::WouldBlock;
  return std::nullopt;
}
inline int32_t IoError_value(IoError value) { return static_cast<int32_t>(value); }
inline std::optional<IoError> IoError_fromValue(int32_t value) {
  if (value == 0) return IoError::NotFound;
  if (value == 1) return IoError::PermissionDenied;
  if (value == 2) return IoError::AlreadyExists;
  if (value == 3) return IoError::IsDirectory;
  if (value == 4) return IoError::NotDirectory;
  if (value == 5) return IoError::InvalidPath;
  if (value == 6) return IoError::Interrupted;
  if (value == 7) return IoError::Other;
  if (value == 8) return IoError::Unsupported;
  if (value == 9) return IoError::InvalidArgument;
  if (value == 10) return IoError::Closed;
  if (value == 11) return IoError::UnexpectedEof;
  if (value == 12) return IoError::WouldBlock;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<IoError>> IoError_values() { return std::make_shared<std::vector<IoError>>(std::initializer_list<IoError>{IoError::NotFound, IoError::PermissionDenied, IoError::AlreadyExists, IoError::IsDirectory, IoError::NotDirectory, IoError::InvalidPath, IoError::Interrupted, IoError::Other, IoError::Unsupported, IoError::InvalidArgument, IoError::Closed, IoError::UnexpectedEof, IoError::WouldBlock}); }
inline doof::JsonValue IoError_toJsonValue(IoError value) { return doof::json_value(IoError_value(value)); }
inline doof::Result<IoError, std::string> IoError_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum IoError, got ") + doof::json_type_name(value)};
  auto resolved = IoError_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum IoError: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12"};
  return doof::Success<IoError>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, IoError value) { return output << IoError_name(value); }
    enum class FileMode {
    ReadOnly = 0,
    ReadWrite = 1
};
inline const char* FileMode_name(FileMode value) {
  switch (value) {
    case FileMode::ReadOnly: return "ReadOnly";
    case FileMode::ReadWrite: return "ReadWrite";
  }
  doof::panic(std::string("Invalid FileMode enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<FileMode> FileMode_fromName(std::string_view value) {
  if (value == "ReadOnly") return FileMode::ReadOnly;
  if (value == "ReadWrite") return FileMode::ReadWrite;
  return std::nullopt;
}
inline int32_t FileMode_value(FileMode value) { return static_cast<int32_t>(value); }
inline std::optional<FileMode> FileMode_fromValue(int32_t value) {
  if (value == 0) return FileMode::ReadOnly;
  if (value == 1) return FileMode::ReadWrite;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<FileMode>> FileMode_values() { return std::make_shared<std::vector<FileMode>>(std::initializer_list<FileMode>{FileMode::ReadOnly, FileMode::ReadWrite}); }
inline doof::JsonValue FileMode_toJsonValue(FileMode value) { return doof::json_value(FileMode_value(value)); }
inline doof::Result<FileMode, std::string> FileMode_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum FileMode, got ") + doof::json_type_name(value)};
  auto resolved = FileMode_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum FileMode: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1"};
  return doof::Success<FileMode>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, FileMode value) { return output << FileMode_name(value); }
    enum class FileLock {
    None = 0,
    Shared = 1,
    Exclusive = 2
};
inline const char* FileLock_name(FileLock value) {
  switch (value) {
    case FileLock::None: return "None";
    case FileLock::Shared: return "Shared";
    case FileLock::Exclusive: return "Exclusive";
  }
  doof::panic(std::string("Invalid FileLock enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<FileLock> FileLock_fromName(std::string_view value) {
  if (value == "None") return FileLock::None;
  if (value == "Shared") return FileLock::Shared;
  if (value == "Exclusive") return FileLock::Exclusive;
  return std::nullopt;
}
inline int32_t FileLock_value(FileLock value) { return static_cast<int32_t>(value); }
inline std::optional<FileLock> FileLock_fromValue(int32_t value) {
  if (value == 0) return FileLock::None;
  if (value == 1) return FileLock::Shared;
  if (value == 2) return FileLock::Exclusive;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<FileLock>> FileLock_values() { return std::make_shared<std::vector<FileLock>>(std::initializer_list<FileLock>{FileLock::None, FileLock::Shared, FileLock::Exclusive}); }
inline doof::JsonValue FileLock_toJsonValue(FileLock value) { return doof::json_value(FileLock_value(value)); }
inline doof::Result<FileLock, std::string> FileLock_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum FileLock, got ") + doof::json_type_name(value)};
  auto resolved = FileLock_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum FileLock: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2"};
  return doof::Success<FileLock>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, FileLock value) { return output << FileLock_name(value); }
}

namespace doof_blob { using Endian = ::std_::blob::types::Endian; }
namespace doof_blob { using TextEncoding = ::std_::blob::types::TextEncoding; }
namespace doof_blob { using EncodingError = ::std_::blob::types::EncodingError; }
#include "native_blob.hpp"

namespace doof_fs { using FileMode = ::std_::fs::types::FileMode; }
namespace doof_fs { using FileLock = ::std_::fs::types::FileLock; }
namespace doof_fs { using IoError = ::std_::fs::types::IoError; }
namespace doof_fs { using File = ::std_::fs::file::File; }
namespace doof_fs { using Endian = ::std_::blob::types::Endian; }
namespace doof_fs { using TextEncoding = ::std_::blob::types::TextEncoding; }
namespace doof_fs { using EncodingError = ::std_::blob::types::EncodingError; }
#include "native_file.hpp"

namespace std_::fs::file {
    struct File : public std::enable_shared_from_this<File> {
    std::shared_ptr<::doof_fs::NativeFile> native;
    ::std_::blob::types::Endian endianness;
    File(std::shared_ptr<::doof_fs::NativeFile> native, ::std_::blob::types::Endian endianness) : native(native), endianness(endianness) {}
    static doof::Result<std::shared_ptr<File>, ::std_::fs::types::IoError> constructor(const std::string& path, ::std_::fs::types::FileMode mode, bool create, ::std_::fs::types::FileLock lock, bool waitForLock, ::std_::blob::types::Endian endianness);
    doof::Result<int64_t, ::std_::fs::types::IoError> getPosition();
    doof::Result<void, ::std_::fs::types::IoError> setPosition(int64_t position);
    doof::Result<int64_t, ::std_::fs::types::IoError> length();
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBytes(int64_t length);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readUpTo(int64_t length);
    doof::Result<void, ::std_::fs::types::IoError> writeBytes(const std::shared_ptr<std::vector<uint8_t>>& data);
    doof::Result<void, ::std_::fs::types::IoError> truncate(int64_t length);
    doof::Result<void, ::std_::fs::types::IoError> flush();
    doof::Result<void, ::std_::fs::types::IoError> close();
    doof::Result<int64_t, ::std_::fs::types::IoError> remaining();
    doof::Result<std::shared_ptr<::doof_blob::NativeBlobReader>, ::std_::fs::types::IoError> reader(int64_t length);
    doof::Result<uint8_t, ::std_::fs::types::IoError> readByte();
    doof::Result<void, ::std_::fs::types::IoError> writeByte(uint8_t value);
    doof::Result<int32_t, ::std_::fs::types::IoError> readSignedByte();
    doof::Result<void, ::std_::fs::types::IoError> writeSignedByte(int32_t value);
    doof::Result<bool, ::std_::fs::types::IoError> readBool();
    doof::Result<void, ::std_::fs::types::IoError> writeBool(bool value);
    doof::Result<int32_t, ::std_::fs::types::IoError> readShort();
    doof::Result<void, ::std_::fs::types::IoError> writeShort(int32_t value);
    doof::Result<int32_t, ::std_::fs::types::IoError> readUnsignedShort();
    doof::Result<void, ::std_::fs::types::IoError> writeUnsignedShort(int32_t value);
    doof::Result<int32_t, ::std_::fs::types::IoError> readInt();
    doof::Result<void, ::std_::fs::types::IoError> writeInt(int32_t value);
    doof::Result<int64_t, ::std_::fs::types::IoError> readUnsignedInt();
    doof::Result<void, ::std_::fs::types::IoError> writeUnsignedInt(int64_t value);
    doof::Result<int64_t, ::std_::fs::types::IoError> readLong();
    doof::Result<void, ::std_::fs::types::IoError> writeLong(int64_t value);
    doof::Result<float, ::std_::fs::types::IoError> readFloat();
    doof::Result<void, ::std_::fs::types::IoError> writeFloat(float value);
    doof::Result<double, ::std_::fs::types::IoError> readDouble();
    doof::Result<void, ::std_::fs::types::IoError> writeDouble(double value);
    doof::Result<std::string, ::std_::fs::types::IoError> readString(int64_t length);
    doof::Result<void, ::std_::fs::types::IoError> writeString(const std::string& value);
    doof::Result<std::string, std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>> readText(int64_t length, ::std_::blob::types::TextEncoding encoding);
    doof::Result<int32_t, std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>> writeText(const std::string& value, ::std_::blob::types::TextEncoding encoding);
    doof::Result<std::string, ::std_::fs::types::IoError> readTextLossy(int64_t length, ::std_::blob::types::TextEncoding encoding);
    doof::Result<int32_t, ::std_::fs::types::IoError> writeTextLossy(const std::string& value, ::std_::blob::types::TextEncoding encoding);
};
}
