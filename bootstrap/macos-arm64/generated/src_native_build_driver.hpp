#pragma once
#include "doof_runtime.hpp"
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }
namespace std_::fs::types { enum class IoError; }
namespace std_::fs::types { struct FileInfo; }
namespace std_::fs::types { enum class EntryKind; }
namespace app_src_native_build_driver_ { enum class NativeBuildOutputMode; }
namespace app_src_emitter_project_ { struct ProjectEmission; }
namespace app_src_native_build_ { enum class NativeBuildMode; }
namespace app_src_native_build_ { struct NativeCompilePlan; }
namespace app_src_native_build_ { struct NativeCompileTask; }
namespace app_src_native_build_state_ { struct NativeBuildState; }
namespace app_src_native_build_state_ { struct NativeInputSignature; }
namespace app_src_native_build_state_ { struct NativeTaskState; }
namespace app_src_pkg_config_ { struct PkgConfigCommandResult; }
namespace std_::os::index { struct ExecOptions; }

namespace std_::blob::index {
}

namespace app_src_emitter_module_ {
    struct ModuleEmission;
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan;
}

namespace app_src_emitter_project_ {
    struct ProjectNativeCopy;
    struct ProjectSupportFile;
    struct ProjectEmission;
}

namespace app_src_native_build_ {
    struct NativeCompileTask;
    struct NativeBuildSupportFile;
    struct NativeCompilePlan;
}

namespace app_src_native_build_state_ {
    struct NativeInputSignature;
    struct NativeTaskState;
    struct NativeBuildState;
}

namespace app_src_pkg_config_ {
    struct PkgConfigCommandResult;
}

namespace std_::fs::types {
    struct FileInfo;
}

namespace std_::fs::index {
}

namespace std_::time::duration {
    struct Duration;
}

namespace std_::time::temporal {
    struct Instant;
    struct Date;
    struct Time;
    struct DateTime;
    struct TimeZone;
    struct ZonedDateTime;
}

namespace std_::os::index {
    struct ExecOptions;
    struct ExecResult;
}

namespace app_src_native_build_driver_ {
    struct NativeCommandResult;
    struct NativeCompilerTaskResult;
    struct NativeCompilerIdentity;
    struct NativeCompilerWorker;
    extern int64_t MAX_NATIVE_OUTPUT_BYTES;
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

namespace app_src_native_build_ {
    enum class NativeBuildMode {
    Debug = 0,
    Release = 1,
    Profile = 2
};
inline const char* NativeBuildMode_name(NativeBuildMode value) {
  switch (value) {
    case NativeBuildMode::Debug: return "Debug";
    case NativeBuildMode::Release: return "Release";
    case NativeBuildMode::Profile: return "Profile";
  }
  doof::panic(std::string("Invalid NativeBuildMode enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<NativeBuildMode> NativeBuildMode_fromName(std::string_view value) {
  if (value == "Debug") return NativeBuildMode::Debug;
  if (value == "Release") return NativeBuildMode::Release;
  if (value == "Profile") return NativeBuildMode::Profile;
  return std::nullopt;
}
inline int32_t NativeBuildMode_value(NativeBuildMode value) { return static_cast<int32_t>(value); }
inline std::optional<NativeBuildMode> NativeBuildMode_fromValue(int32_t value) {
  if (value == 0) return NativeBuildMode::Debug;
  if (value == 1) return NativeBuildMode::Release;
  if (value == 2) return NativeBuildMode::Profile;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<NativeBuildMode>> NativeBuildMode_values() { return std::make_shared<std::vector<NativeBuildMode>>(std::initializer_list<NativeBuildMode>{NativeBuildMode::Debug, NativeBuildMode::Release, NativeBuildMode::Profile}); }
inline doof::JsonValue NativeBuildMode_toJsonValue(NativeBuildMode value) { return doof::json_value(NativeBuildMode_value(value)); }
inline doof::Result<NativeBuildMode, std::string> NativeBuildMode_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum NativeBuildMode, got ") + doof::json_type_name(value)};
  auto resolved = NativeBuildMode_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum NativeBuildMode: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2"};
  return doof::Success<NativeBuildMode>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, NativeBuildMode value) { return output << NativeBuildMode_name(value); }
}

namespace std_::fs::types {
    enum class EntryKind {
    File = 0,
    Directory = 1,
    Symlink = 2,
    Other = 3
};
inline const char* EntryKind_name(EntryKind value) {
  switch (value) {
    case EntryKind::File: return "File";
    case EntryKind::Directory: return "Directory";
    case EntryKind::Symlink: return "Symlink";
    case EntryKind::Other: return "Other";
  }
  doof::panic(std::string("Invalid EntryKind enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<EntryKind> EntryKind_fromName(std::string_view value) {
  if (value == "File") return EntryKind::File;
  if (value == "Directory") return EntryKind::Directory;
  if (value == "Symlink") return EntryKind::Symlink;
  if (value == "Other") return EntryKind::Other;
  return std::nullopt;
}
inline int32_t EntryKind_value(EntryKind value) { return static_cast<int32_t>(value); }
inline std::optional<EntryKind> EntryKind_fromValue(int32_t value) {
  if (value == 0) return EntryKind::File;
  if (value == 1) return EntryKind::Directory;
  if (value == 2) return EntryKind::Symlink;
  if (value == 3) return EntryKind::Other;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<EntryKind>> EntryKind_values() { return std::make_shared<std::vector<EntryKind>>(std::initializer_list<EntryKind>{EntryKind::File, EntryKind::Directory, EntryKind::Symlink, EntryKind::Other}); }
inline doof::JsonValue EntryKind_toJsonValue(EntryKind value) { return doof::json_value(EntryKind_value(value)); }
inline doof::Result<EntryKind, std::string> EntryKind_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum EntryKind, got ") + doof::json_type_name(value)};
  auto resolved = EntryKind_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum EntryKind: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2, 3"};
  return doof::Success<EntryKind>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, EntryKind value) { return output << EntryKind_name(value); }
    enum class IoError {
    NotFound = 0,
    PermissionDenied = 1,
    AlreadyExists = 2,
    IsDirectory = 3,
    NotDirectory = 4,
    InvalidPath = 5,
    Interrupted = 6,
    Other = 7,
    Unsupported = 8
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
  return std::nullopt;
}
inline std::shared_ptr<std::vector<IoError>> IoError_values() { return std::make_shared<std::vector<IoError>>(std::initializer_list<IoError>{IoError::NotFound, IoError::PermissionDenied, IoError::AlreadyExists, IoError::IsDirectory, IoError::NotDirectory, IoError::InvalidPath, IoError::Interrupted, IoError::Other, IoError::Unsupported}); }
inline doof::JsonValue IoError_toJsonValue(IoError value) { return doof::json_value(IoError_value(value)); }
inline doof::Result<IoError, std::string> IoError_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum IoError, got ") + doof::json_type_name(value)};
  auto resolved = IoError_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum IoError: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2, 3, 4, 5, 6, 7, 8"};
  return doof::Success<IoError>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, IoError value) { return output << IoError_name(value); }
}

namespace std_::time::temporal {
    enum class DayOfWeek {
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
    Sunday = 7
};
inline const char* DayOfWeek_name(DayOfWeek value) {
  switch (value) {
    case DayOfWeek::Monday: return "Monday";
    case DayOfWeek::Tuesday: return "Tuesday";
    case DayOfWeek::Wednesday: return "Wednesday";
    case DayOfWeek::Thursday: return "Thursday";
    case DayOfWeek::Friday: return "Friday";
    case DayOfWeek::Saturday: return "Saturday";
    case DayOfWeek::Sunday: return "Sunday";
  }
  doof::panic(std::string("Invalid DayOfWeek enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<DayOfWeek> DayOfWeek_fromName(std::string_view value) {
  if (value == "Monday") return DayOfWeek::Monday;
  if (value == "Tuesday") return DayOfWeek::Tuesday;
  if (value == "Wednesday") return DayOfWeek::Wednesday;
  if (value == "Thursday") return DayOfWeek::Thursday;
  if (value == "Friday") return DayOfWeek::Friday;
  if (value == "Saturday") return DayOfWeek::Saturday;
  if (value == "Sunday") return DayOfWeek::Sunday;
  return std::nullopt;
}
inline int32_t DayOfWeek_value(DayOfWeek value) { return static_cast<int32_t>(value); }
inline std::optional<DayOfWeek> DayOfWeek_fromValue(int32_t value) {
  if (value == 1) return DayOfWeek::Monday;
  if (value == 2) return DayOfWeek::Tuesday;
  if (value == 3) return DayOfWeek::Wednesday;
  if (value == 4) return DayOfWeek::Thursday;
  if (value == 5) return DayOfWeek::Friday;
  if (value == 6) return DayOfWeek::Saturday;
  if (value == 7) return DayOfWeek::Sunday;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<DayOfWeek>> DayOfWeek_values() { return std::make_shared<std::vector<DayOfWeek>>(std::initializer_list<DayOfWeek>{DayOfWeek::Monday, DayOfWeek::Tuesday, DayOfWeek::Wednesday, DayOfWeek::Thursday, DayOfWeek::Friday, DayOfWeek::Saturday, DayOfWeek::Sunday}); }
inline doof::JsonValue DayOfWeek_toJsonValue(DayOfWeek value) { return doof::json_value(DayOfWeek_value(value)); }
inline doof::Result<DayOfWeek, std::string> DayOfWeek_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum DayOfWeek, got ") + doof::json_type_name(value)};
  auto resolved = DayOfWeek_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum DayOfWeek: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 1, 2, 3, 4, 5, 6, 7"};
  return doof::Success<DayOfWeek>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, DayOfWeek value) { return output << DayOfWeek_name(value); }
}

namespace std_::os::index {
    enum class ProcessGroupMode {
    Isolated = 0,
    Inherited = 1
};
inline const char* ProcessGroupMode_name(ProcessGroupMode value) {
  switch (value) {
    case ProcessGroupMode::Isolated: return "Isolated";
    case ProcessGroupMode::Inherited: return "Inherited";
  }
  doof::panic(std::string("Invalid ProcessGroupMode enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<ProcessGroupMode> ProcessGroupMode_fromName(std::string_view value) {
  if (value == "Isolated") return ProcessGroupMode::Isolated;
  if (value == "Inherited") return ProcessGroupMode::Inherited;
  return std::nullopt;
}
inline int32_t ProcessGroupMode_value(ProcessGroupMode value) { return static_cast<int32_t>(value); }
inline std::optional<ProcessGroupMode> ProcessGroupMode_fromValue(int32_t value) {
  if (value == 0) return ProcessGroupMode::Isolated;
  if (value == 1) return ProcessGroupMode::Inherited;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<ProcessGroupMode>> ProcessGroupMode_values() { return std::make_shared<std::vector<ProcessGroupMode>>(std::initializer_list<ProcessGroupMode>{ProcessGroupMode::Isolated, ProcessGroupMode::Inherited}); }
inline doof::JsonValue ProcessGroupMode_toJsonValue(ProcessGroupMode value) { return doof::json_value(ProcessGroupMode_value(value)); }
inline doof::Result<ProcessGroupMode, std::string> ProcessGroupMode_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum ProcessGroupMode, got ") + doof::json_type_name(value)};
  auto resolved = ProcessGroupMode_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum ProcessGroupMode: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1"};
  return doof::Success<ProcessGroupMode>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, ProcessGroupMode value) { return output << ProcessGroupMode_name(value); }
}

namespace app_src_native_build_driver_ {
    enum class NativeBuildOutputMode {
    Silent = 0,
    Progress = 1
};
inline const char* NativeBuildOutputMode_name(NativeBuildOutputMode value) {
  switch (value) {
    case NativeBuildOutputMode::Silent: return "Silent";
    case NativeBuildOutputMode::Progress: return "Progress";
  }
  doof::panic(std::string("Invalid NativeBuildOutputMode enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<NativeBuildOutputMode> NativeBuildOutputMode_fromName(std::string_view value) {
  if (value == "Silent") return NativeBuildOutputMode::Silent;
  if (value == "Progress") return NativeBuildOutputMode::Progress;
  return std::nullopt;
}
inline int32_t NativeBuildOutputMode_value(NativeBuildOutputMode value) { return static_cast<int32_t>(value); }
inline std::optional<NativeBuildOutputMode> NativeBuildOutputMode_fromValue(int32_t value) {
  if (value == 0) return NativeBuildOutputMode::Silent;
  if (value == 1) return NativeBuildOutputMode::Progress;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<NativeBuildOutputMode>> NativeBuildOutputMode_values() { return std::make_shared<std::vector<NativeBuildOutputMode>>(std::initializer_list<NativeBuildOutputMode>{NativeBuildOutputMode::Silent, NativeBuildOutputMode::Progress}); }
inline doof::JsonValue NativeBuildOutputMode_toJsonValue(NativeBuildOutputMode value) { return doof::json_value(NativeBuildOutputMode_value(value)); }
inline doof::Result<NativeBuildOutputMode, std::string> NativeBuildOutputMode_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum NativeBuildOutputMode, got ") + doof::json_type_name(value)};
  auto resolved = NativeBuildOutputMode_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum NativeBuildOutputMode: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1"};
  return doof::Success<NativeBuildOutputMode>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, NativeBuildOutputMode value) { return output << NativeBuildOutputMode_name(value); }
}

namespace app_src_emitter_module_ {
    struct ModuleEmission : public std::enable_shared_from_this<ModuleEmission> {
    std::string modulePath;
    std::string header;
    std::string source;
    std::string headerName;
    std::string sourceName;
    int32_t coverageModuleId;
    std::shared_ptr<std::vector<int32_t>> instrumentedLines;
    bool reused;
    std::string fingerprint;
    ModuleEmission(std::string modulePath, std::string header, std::string source, std::string headerName, std::string sourceName, int32_t coverageModuleId, std::shared_ptr<std::vector<int32_t>> instrumentedLines, bool reused, std::string fingerprint) : modulePath(modulePath), header(header), source(source), headerName(headerName), sourceName(sourceName), coverageModuleId(coverageModuleId), instrumentedLines(instrumentedLines), reused(reused), fingerprint(fingerprint) {}
};
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan : public std::enable_shared_from_this<NativeBuildPlan> {
    std::shared_ptr<std::vector<std::string>> includePaths;
    std::shared_ptr<std::vector<std::string>> sourceFiles;
    std::shared_ptr<std::vector<std::string>> libraryPaths;
    std::shared_ptr<std::vector<std::string>> extraCopyPaths;
    std::shared_ptr<std::vector<std::string>> linkLibraries;
    std::shared_ptr<std::vector<std::string>> frameworks;
    std::shared_ptr<std::vector<std::string>> pkgConfigPackages;
    std::shared_ptr<std::vector<std::string>> defines;
    std::shared_ptr<std::vector<std::string>> compilerFlags;
    std::shared_ptr<std::vector<std::string>> linkerFlags;
    NativeBuildPlan(std::shared_ptr<std::vector<std::string>> includePaths, std::shared_ptr<std::vector<std::string>> sourceFiles, std::shared_ptr<std::vector<std::string>> libraryPaths, std::shared_ptr<std::vector<std::string>> extraCopyPaths, std::shared_ptr<std::vector<std::string>> linkLibraries, std::shared_ptr<std::vector<std::string>> frameworks, std::shared_ptr<std::vector<std::string>> pkgConfigPackages, std::shared_ptr<std::vector<std::string>> defines, std::shared_ptr<std::vector<std::string>> compilerFlags, std::shared_ptr<std::vector<std::string>> linkerFlags) : includePaths(includePaths), sourceFiles(sourceFiles), libraryPaths(libraryPaths), extraCopyPaths(extraCopyPaths), linkLibraries(linkLibraries), frameworks(frameworks), pkgConfigPackages(pkgConfigPackages), defines(defines), compilerFlags(compilerFlags), linkerFlags(linkerFlags) {}
};
}

namespace app_src_emitter_project_ {
    struct ProjectNativeCopy : public std::enable_shared_from_this<ProjectNativeCopy> {
    std::string sourcePath;
    std::string relativePath;
    ProjectNativeCopy(std::string sourcePath, std::string relativePath) : sourcePath(sourcePath), relativePath(relativePath) {}
};
    struct ProjectSupportFile : public std::enable_shared_from_this<ProjectSupportFile> {
    std::string relativePath;
    std::string content;
    ProjectSupportFile(std::string relativePath, std::string content) : relativePath(relativePath), content(content) {}
};
    struct ProjectEmission : public std::enable_shared_from_this<ProjectEmission> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules;
    std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> supportFiles;
    std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> nativeCopies;
    std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild;
    std::shared_ptr<std::vector<std::string>> wasmExportNames;
    ProjectEmission(std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules, std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> supportFiles, std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> nativeCopies, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::shared_ptr<std::vector<std::string>> wasmExportNames) : modules(modules), supportFiles(supportFiles), nativeCopies(nativeCopies), nativeBuild(nativeBuild), wasmExportNames(wasmExportNames) {}
};
}

namespace app_src_native_build_ {
    struct NativeCompileTask : public std::enable_shared_from_this<NativeCompileTask> {
    std::string id;
    std::string compiler;
    std::string sourcePath;
    std::string outputPath;
    std::string dependencyFilePath;
    std::shared_ptr<std::vector<std::string>> auxiliaryOutputPaths;
    bool usesPrecompiledHeader;
    std::shared_ptr<std::vector<std::string>> arguments;
    NativeCompileTask(std::string id, std::string compiler, std::string sourcePath, std::string outputPath, std::string dependencyFilePath, std::shared_ptr<std::vector<std::string>> auxiliaryOutputPaths, bool usesPrecompiledHeader, std::shared_ptr<std::vector<std::string>> arguments) : id(id), compiler(compiler), sourcePath(sourcePath), outputPath(outputPath), dependencyFilePath(dependencyFilePath), auxiliaryOutputPaths(auxiliaryOutputPaths), usesPrecompiledHeader(usesPrecompiledHeader), arguments(arguments) {}
};
    struct NativeBuildSupportFile : public std::enable_shared_from_this<NativeBuildSupportFile> {
    std::string outputPath;
    std::string content;
    NativeBuildSupportFile(std::string outputPath, std::string content) : outputPath(outputPath), content(content) {}
};
    struct NativeCompilePlan : public std::enable_shared_from_this<NativeCompilePlan> {
    std::string compiler;
    std::string linker;
    std::shared_ptr<std::vector<std::shared_ptr<NativeBuildSupportFile>>> supportFiles;
    std::shared_ptr<NativeCompileTask> precompiledHeaderTask;
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks;
    std::shared_ptr<std::vector<std::string>> linkArguments;
    std::string outputPath;
    NativeCompilePlan(std::string compiler, std::string linker, std::shared_ptr<std::vector<std::shared_ptr<NativeBuildSupportFile>>> supportFiles, std::shared_ptr<NativeCompileTask> precompiledHeaderTask, std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks, std::shared_ptr<std::vector<std::string>> linkArguments, std::string outputPath) : compiler(compiler), linker(linker), supportFiles(supportFiles), precompiledHeaderTask(precompiledHeaderTask), compileTasks(compileTasks), linkArguments(linkArguments), outputPath(outputPath) {}
};
}

namespace app_src_native_build_state_ {
    struct NativeInputSignature : public std::enable_shared_from_this<NativeInputSignature> {
    std::string path;
    std::string signature;
    bool contentHash;
    int64_t size;
    int64_t modifiedNanos;
    NativeInputSignature(std::string path, std::string signature, bool contentHash, int64_t size, int64_t modifiedNanos) : path(path), signature(signature), contentHash(contentHash), size(size), modifiedNanos(modifiedNanos) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeInputSignature>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct NativeTaskState : public std::enable_shared_from_this<NativeTaskState> {
    std::string id;
    std::string fingerprint;
    std::string outputPath;
    int64_t outputSize;
    int64_t outputModifiedNanos;
    std::shared_ptr<std::vector<std::shared_ptr<NativeInputSignature>>> inputs;
    NativeTaskState(std::string id, std::string fingerprint, std::string outputPath, int64_t outputSize, int64_t outputModifiedNanos, std::shared_ptr<std::vector<std::shared_ptr<NativeInputSignature>>> inputs) : id(id), fingerprint(fingerprint), outputPath(outputPath), outputSize(outputSize), outputModifiedNanos(outputModifiedNanos), inputs(inputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeTaskState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct NativeBuildState : public std::enable_shared_from_this<NativeBuildState> {
    int32_t version;
    std::shared_ptr<std::vector<std::shared_ptr<NativeTaskState>>> tasks;
    std::shared_ptr<std::vector<std::string>> managedOutputs;
    NativeBuildState(int32_t version, std::shared_ptr<std::vector<std::shared_ptr<NativeTaskState>>> tasks, std::shared_ptr<std::vector<std::string>> managedOutputs) : version(version), tasks(tasks), managedOutputs(managedOutputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeBuildState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
}

namespace app_src_pkg_config_ {
    struct PkgConfigCommandResult : public std::enable_shared_from_this<PkgConfigCommandResult> {
    int32_t exitCode;
    std::string output;
    std::string error;
    PkgConfigCommandResult(int32_t exitCode, std::string output, std::string error) : exitCode(exitCode), output(output), error(error) {}
};
}

namespace std_::time::duration {
    // A signed elapsed duration with nanosecond precision.
struct Duration : public std::enable_shared_from_this<Duration> {
    int64_t nanos;
    static std::shared_ptr<Duration> ZERO;
    Duration(int64_t nanos) : nanos(nanos) {}
    static std::shared_ptr<Duration> ofNanos(int64_t n);
    static std::shared_ptr<Duration> ofMicros(int64_t us);
    static std::shared_ptr<Duration> ofMillis(int64_t ms);
    static std::shared_ptr<Duration> ofSeconds(int64_t s);
    static std::shared_ptr<Duration> ofMinutes(int64_t m);
    static std::shared_ptr<Duration> ofHours(int64_t h);
    static std::shared_ptr<Duration> ofDays(int64_t d);
    static doof::Result<std::shared_ptr<Duration>, std::string> parse(const std::string& s);
    int64_t toNanos();
    int64_t toMicros();
    int64_t toMillis();
    double toSeconds();
    double toMinutes();
    double toHours();
    double toDays();
    bool isNegative();
    bool isZero();
    std::shared_ptr<Duration> abs();
    std::shared_ptr<Duration> negated();
    std::shared_ptr<Duration> plus(const std::shared_ptr<Duration>& other);
    std::shared_ptr<Duration> minus(const std::shared_ptr<Duration>& other);
    std::shared_ptr<Duration> multipliedBy(int64_t factor);
    std::shared_ptr<Duration> dividedBy(int64_t divisor);
    int32_t compareTo(const std::shared_ptr<Duration>& other);
    bool isLessThan(const std::shared_ptr<Duration>& other);
    bool isGreaterThan(const std::shared_ptr<Duration>& other);
    bool equals(const std::shared_ptr<Duration>& other);
    std::string toISOString();
};
}

namespace std_::time::temporal {
    // A point in UTC time with nanosecond precision.
struct Instant : public std::enable_shared_from_this<Instant> {
    int64_t epochNanos;
    static std::shared_ptr<Instant> EPOCH;
    Instant(int64_t epochNanos) : epochNanos(epochNanos) {}
    static std::shared_ptr<Instant> now();
    static std::shared_ptr<Instant> ofEpochNanos(int64_t nanos);
    static std::shared_ptr<Instant> ofEpochMillis(int64_t ms);
    static std::shared_ptr<Instant> ofEpochSeconds(int64_t s);
    static doof::Result<std::shared_ptr<Instant>, std::string> parse(const std::string& s);
    int64_t toEpochNanos();
    int64_t toEpochMillis();
    int64_t toEpochSeconds();
    std::shared_ptr<Instant> plus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<Instant> minus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<::std_::time::duration::Duration> durationUntil(const std::shared_ptr<Instant>& other);
    std::shared_ptr<::std_::time::duration::Duration> durationSince(const std::shared_ptr<Instant>& other);
    int32_t compareTo(const std::shared_ptr<Instant>& other);
    bool isBefore(const std::shared_ptr<Instant>& other);
    bool isAfter(const std::shared_ptr<Instant>& other);
    bool equals(const std::shared_ptr<Instant>& other);
    std::shared_ptr<DateTime> toDateTime();
    std::shared_ptr<ZonedDateTime> toZonedDateTime(const std::shared_ptr<TimeZone>& zone);
    std::string toISOString();
    static doof::Result<std::shared_ptr<Instant>, std::string> parseHttpDate(const std::string& s);
    std::string toHttpDate();
};
    // A calendar date (year, month, day) with no time-of-day or timezone.
struct Date : public std::enable_shared_from_this<Date> {
    int32_t year;
    int32_t month;
    int32_t day;
    static std::shared_ptr<Date> MIN;
    static std::shared_ptr<Date> MAX;
    Date(int32_t year, int32_t month, int32_t day) : year(year), month(month), day(day) {}
    static doof::Result<std::shared_ptr<Date>, std::string> create(int32_t year, int32_t month, int32_t day);
    static std::shared_ptr<Date> todayUTC();
    static std::shared_ptr<Date> today(const std::shared_ptr<TimeZone>& zone);
    static doof::Result<std::shared_ptr<Date>, std::string> parse(const std::string& s);
    DayOfWeek dayOfWeek();
    int32_t dayOfYear();
    bool isLeapYear();
    int32_t daysInMonth();
    std::shared_ptr<Date> plusDays(int32_t n);
    std::shared_ptr<Date> minusDays(int32_t n);
    std::shared_ptr<Date> plusMonths(int32_t n);
    std::shared_ptr<Date> minusMonths(int32_t n);
    std::shared_ptr<Date> plusYears(int32_t n);
    std::shared_ptr<Date> minusYears(int32_t n);
    int32_t daysUntil(const std::shared_ptr<Date>& other);
    int32_t compareTo(const std::shared_ptr<Date>& other);
    bool isBefore(const std::shared_ptr<Date>& other);
    bool isAfter(const std::shared_ptr<Date>& other);
    bool equals(const std::shared_ptr<Date>& other);
    std::string toISOString();
};
    // A time-of-day with nanosecond precision. No date or timezone.
struct Time : public std::enable_shared_from_this<Time> {
    int32_t hour;
    int32_t minute;
    int32_t second;
    int32_t nanosecond;
    static std::shared_ptr<Time> MIDNIGHT;
    static std::shared_ptr<Time> NOON;
    Time(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond) : hour(hour), minute(minute), second(second), nanosecond(nanosecond) {}
    static doof::Result<std::shared_ptr<Time>, std::string> create(int32_t hour, int32_t minute, int32_t second, int32_t nanosecond);
    static doof::Result<std::shared_ptr<Time>, std::string> parse(const std::string& s);
    std::shared_ptr<Time> plusHours(int32_t n);
    std::shared_ptr<Time> plusMinutes(int32_t n);
    std::shared_ptr<Time> plusSeconds(int32_t n);
    std::shared_ptr<Time> plusNanos(int64_t n);
    int32_t compareTo(const std::shared_ptr<Time>& other);
    bool isBefore(const std::shared_ptr<Time>& other);
    bool isAfter(const std::shared_ptr<Time>& other);
    bool equals(const std::shared_ptr<Time>& other);
    std::string toISOString();
};
    // A combined calendar date and time-of-day. No timezone.
struct DateTime : public std::enable_shared_from_this<DateTime> {
    std::shared_ptr<Date> date;
    std::shared_ptr<Time> time;
    DateTime(std::shared_ptr<Date> date, std::shared_ptr<Time> time) : date(date), time(time) {}
    static std::shared_ptr<DateTime> create(const std::shared_ptr<Date>& date, const std::shared_ptr<Time>& time);
    static doof::Result<std::shared_ptr<DateTime>, std::string> fromParts(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, int32_t nanosecond);
    static std::shared_ptr<DateTime> nowUTC();
    static doof::Result<std::shared_ptr<DateTime>, std::string> parse(const std::string& s);
    std::shared_ptr<DateTime> plusDays(int32_t n);
    std::shared_ptr<DateTime> minusDays(int32_t n);
    std::shared_ptr<DateTime> plusHours(int32_t n);
    std::shared_ptr<DateTime> plusMinutes(int32_t n);
    std::shared_ptr<DateTime> plusSeconds(int32_t n);
    std::shared_ptr<DateTime> plus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<DateTime> minus(const std::shared_ptr<::std_::time::duration::Duration>& d);
    std::shared_ptr<Instant> toInstantUTC();
    std::shared_ptr<Instant> toInstant(const std::shared_ptr<TimeZone>& zone);
    std::shared_ptr<ZonedDateTime> atZone(const std::shared_ptr<TimeZone>& zone);
    int32_t compareTo(const std::shared_ptr<DateTime>& other);
    bool isBefore(const std::shared_ptr<DateTime>& other);
    bool isAfter(const std::shared_ptr<DateTime>& other);
    bool equals(const std::shared_ptr<DateTime>& other);
    std::string toISOString();
};
    // An IANA timezone identifier (e.g. "America/New_York", "UTC").
struct TimeZone : public std::enable_shared_from_this<TimeZone> {
    std::string id;
    static std::shared_ptr<TimeZone> UTC;
    TimeZone(std::string id) : id(id) {}
    static doof::Result<std::shared_ptr<TimeZone>, std::string> lookup(const std::string& id);
    static std::shared_ptr<TimeZone> local();
    int32_t offsetSecondsAt(const std::shared_ptr<Instant>& instant);
    bool isDSTAt(const std::shared_ptr<Instant>& instant);
};
    // A DateTime with an explicit TimeZone.
struct ZonedDateTime : public std::enable_shared_from_this<ZonedDateTime> {
    std::shared_ptr<DateTime> dateTime;
    std::shared_ptr<TimeZone> zone;
    ZonedDateTime(std::shared_ptr<DateTime> dateTime, std::shared_ptr<TimeZone> zone) : dateTime(dateTime), zone(zone) {}
    static std::shared_ptr<ZonedDateTime> now(const std::shared_ptr<TimeZone>& zone);
    static std::shared_ptr<ZonedDateTime> nowUTC();
    std::shared_ptr<Date> date();
    std::shared_ptr<Time> time();
    int32_t offsetSeconds();
    std::shared_ptr<Instant> toInstant();
    std::shared_ptr<ZonedDateTime> withZoneSameInstant(const std::shared_ptr<TimeZone>& newZone);
    std::shared_ptr<ZonedDateTime> withZoneSameLocal(const std::shared_ptr<TimeZone>& newZone);
    std::shared_ptr<DateTime> toDateTime();
    std::shared_ptr<ZonedDateTime> toUTC();
    int32_t compareTo(const std::shared_ptr<ZonedDateTime>& other);
    bool isBefore(const std::shared_ptr<ZonedDateTime>& other);
    bool isAfter(const std::shared_ptr<ZonedDateTime>& other);
    std::string toISOString();
};
}

namespace std_::os::index {
    struct ExecResult : public std::enable_shared_from_this<ExecResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> stdout_;
    std::shared_ptr<std::vector<uint8_t>> stderr_;
    bool stdoutTruncated;
    bool stderrTruncated;
    ExecResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> stdout_, std::shared_ptr<std::vector<uint8_t>> stderr_, bool stdoutTruncated, bool stderrTruncated) : exitCode(exitCode), stdout_(stdout_), stderr_(stderr_), stdoutTruncated(stdoutTruncated), stderrTruncated(stderrTruncated) {}
};
}

namespace app_src_native_build_driver_ {
    struct NativeCommandResult : public std::enable_shared_from_this<NativeCommandResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> output;
    std::string error;
    bool truncated;
    NativeCommandResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> output, std::string error, bool truncated) : exitCode(exitCode), output(output), error(error), truncated(truncated) {}
};
    struct NativeCompilerTaskResult : public std::enable_shared_from_this<NativeCompilerTaskResult> {
    int32_t workerIndex;
    std::shared_ptr<NativeCommandResult> output;
    NativeCompilerTaskResult(int32_t workerIndex, std::shared_ptr<NativeCommandResult> output) : workerIndex(workerIndex), output(output) {}
};
    struct NativeCompilerIdentity : public std::enable_shared_from_this<NativeCompilerIdentity> {
    std::string command;
    std::string signature;
    NativeCompilerIdentity(std::string command, std::string signature) : command(command), signature(signature) {}
};
    struct NativeCompilerWorker : public std::enable_shared_from_this<NativeCompilerWorker> {
    NativeCompilerWorker() {}
    std::shared_ptr<NativeCompilerTaskResult> compile(int32_t workerIndex, const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task);
};
}

namespace doof_blob { using Endian = ::std_::blob::types::Endian; }
namespace doof_blob { using TextEncoding = ::std_::blob::types::TextEncoding; }
namespace doof_blob { using EncodingError = ::std_::blob::types::EncodingError; }
#include "native_blob.hpp"

namespace std_::crypto::index {
    std::string sha256Hex(const std::shared_ptr<std::vector<uint8_t>>& data);
    std::string sha256HexString(const std::string& text);
}

namespace app_src_native_build_ {
    bool isMsvcCompiler(const std::string& compiler);
    std::shared_ptr<NativeCompilePlan> planNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, NativeBuildMode mode, const std::string& platform, const std::shared_ptr<std::vector<std::string>>& wasmExportNames, bool wasm, bool wasmCommand);
}

namespace app_src_native_build_state_ {
    std::shared_ptr<NativeBuildState> parseNativeBuildState(const std::string& source);
    std::string renderNativeBuildState(const std::shared_ptr<NativeBuildState>& state);
    std::shared_ptr<std::vector<std::string>> parseMakeDependencies(const std::string& source);
    std::shared_ptr<std::vector<std::string>> parseMsvcDependencies(const std::string& source);
}

namespace app_src_pkg_config_ {
    doof::Result<void, std::string> applyPkgConfigResult(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, const std::string& packageName, const std::string& mode, const std::shared_ptr<PkgConfigCommandResult>& result);
}

namespace app_src_progress_ {
    std::string renderProgressBar(int32_t completed, int32_t total, int32_t width);
    int32_t boundedWorkerCount(int32_t itemCount, int32_t maximumWorkers);
}

namespace std_::fs::types {
    struct FileInfo : public std::enable_shared_from_this<FileInfo> {
    std::string name;
    EntryKind kind;
    int64_t size;
    std::shared_ptr<::std_::time::temporal::Instant> modifiedAt;
    FileInfo(std::string name, EntryKind kind, int64_t size, std::shared_ptr<::std_::time::temporal::Instant> modifiedAt) : name(name), kind(kind), size(size), modifiedAt(modifiedAt) {}
};
}

namespace doof_fs { using IoError = ::std_::fs::types::IoError; }
using IoError = ::std_::fs::types::IoError;
namespace doof_fs { using FileInfo = ::std_::fs::types::FileInfo; }
namespace doof_fs { using EntryKind = ::std_::fs::types::EntryKind; }
using EntryKind = ::std_::fs::types::EntryKind;
using FileInfo = ::std_::fs::types::FileInfo;
#include "native_fs.hpp"

namespace std_::os::index {
    struct ExecOptions : public std::enable_shared_from_this<ExecOptions> {
    std::optional<std::string> cwd;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env;
    bool inheritEnv;
    bool withStdin;
    bool mergeStderrIntoStdout;
    bool inheritOutput;
    ProcessGroupMode processGroupMode;
    std::optional<int64_t> maxOutputBytes;
    std::shared_ptr<::std_::time::duration::Duration> timeout;
    ExecOptions(std::optional<std::string> cwd, std::shared_ptr<doof::ordered_map<std::string, std::string>> env, bool inheritEnv, bool withStdin, bool mergeStderrIntoStdout, bool inheritOutput, ProcessGroupMode processGroupMode, std::optional<int64_t> maxOutputBytes, std::shared_ptr<::std_::time::duration::Duration> timeout) : cwd(cwd), env(env), inheritEnv(inheritEnv), withStdin(withStdin), mergeStderrIntoStdout(mergeStderrIntoStdout), inheritOutput(inheritOutput), processGroupMode(processGroupMode), maxOutputBytes(maxOutputBytes), timeout(timeout) {}
};
    doof::Result<std::string, std::string> env(const std::string& name);
    doof::Result<std::shared_ptr<ExecResult>, std::string> run(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options);
}

namespace doof { using NativeBuildOutputMode = ::app_src_native_build_driver_::NativeBuildOutputMode; }
namespace doof { using ProjectEmission = ::app_src_emitter_project_::ProjectEmission; }
namespace doof { using NativeBuildMode = ::app_src_native_build_::NativeBuildMode; }
namespace doof { using NativeCompilePlan = ::app_src_native_build_::NativeCompilePlan; }
namespace doof { using NativeCompileTask = ::app_src_native_build_::NativeCompileTask; }
namespace doof { using NativeBuildState = ::app_src_native_build_state_::NativeBuildState; }
namespace doof { using NativeInputSignature = ::app_src_native_build_state_::NativeInputSignature; }
namespace doof { using NativeTaskState = ::app_src_native_build_state_::NativeTaskState; }
namespace doof { using PkgConfigCommandResult = ::app_src_pkg_config_::PkgConfigCommandResult; }
namespace doof { using ExecOptions = ::std_::os::index::ExecOptions; }
#include "doof_runtime.hpp"

namespace app_src_native_build_driver_ {
    std::shared_ptr<NativeCommandResult> runBuildCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments);
    void printBuildOutput(const std::shared_ptr<NativeCommandResult>& result);
    std::string nativeCompilationSummary(int32_t fileCount);
    bool shouldPrintNativeCommandOutput(int32_t exitCode);
    int32_t buildNativeProject(const std::string& compilerOverride, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project, ::app_src_native_build_::NativeBuildMode mode, const std::string& platform, NativeBuildOutputMode outputMode, bool wasmCommand);
    std::string envCompiler();
    int32_t executeNativePlan(const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project, NativeBuildOutputMode outputMode);
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>> indexNativeTaskStates(const std::shared_ptr<::app_src_native_build_state_::NativeBuildState>& state);
    std::shared_ptr<::app_src_native_build_state_::NativeTaskState> indexedNativeTaskState(const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>& indexed, const std::string& id);
    std::string compilerIdentity(const std::string& command, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities);
    std::string taskFingerprint(const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities);
    std::string linkFingerprint(const std::string& linker, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities);
    std::shared_ptr<::app_src_native_build_state_::NativeInputSignature> pathSignature(const std::string& path, bool contentHash);
    std::shared_ptr<::app_src_native_build_state_::NativeInputSignature> currentInputSignature(const std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>& previous);
    bool taskIsCurrent(const std::shared_ptr<::app_src_native_build_state_::NativeTaskState>& previous, const std::string& fingerprint, const std::shared_ptr<std::vector<std::string>>& auxiliaryOutputPaths);
    bool nativeTaskStateIsCurrent(const std::shared_ptr<::app_src_native_build_state_::NativeTaskState>& previous, const std::string& fingerprint, int64_t outputSize, int64_t outputModifiedNanos, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>& currentInputs, bool auxiliaryOutputsCurrent);
    std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureTaskState(const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task, const std::string& fingerprint);
    std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureLinkState(const std::string& outputPath, const std::string& fingerprint, const std::shared_ptr<std::vector<std::string>>& objectPaths);
    std::shared_ptr<::app_src_native_build_state_::NativeBuildState> readBuildState(const std::string& path);
    void writeBuildState(const std::string& path, const std::shared_ptr<::app_src_native_build_state_::NativeBuildState>& state);
    void writeTextIfChanged(const std::string& path, const std::string& content);
    bool nativeSupportFileNeedsWrite(const std::optional<std::string>& previous, const std::string& content);
    std::string msvcLinkResponseFile(const std::shared_ptr<std::vector<std::string>>& arguments);
    std::string quoteMsvcResponseArgument(const std::string& argument);
    void collectManagedOutputs(const std::shared_ptr<std::vector<std::string>>& outputs, const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project);
    void collectManagedOutputsIndexed(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project);
    void collectManagedNativeCopyOutputs(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& sourcePath, const std::string& outputPath);
    void removeStaleOutputs(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current, const std::string& outputDirectory);
    std::shared_ptr<std::vector<std::string>> staleManagedOutputCandidates(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current, const std::string& outputDirectory);
    bool nativeManagedOutputsChanged(const std::shared_ptr<std::vector<std::string>>& previous, const std::shared_ptr<std::vector<std::string>>& current);
    std::shared_ptr<std::vector<std::string>> mutableArguments(const std::shared_ptr<std::vector<std::string>>& arguments);
    bool contains(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value);
    void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value);
    void appendManagedOutput(const std::shared_ptr<std::vector<std::string>>& outputs, const std::shared_ptr<doof::ordered_set<std::string>>& indexed, const std::string& value);
    std::string joinOutput(const std::string& directory, const std::string& name);
    std::string msvcLinkResponsePath(const std::string& outputDirectory);
    bool isMsvcLinker(const std::string& linker);
    std::string parentDirectory(const std::string& path);
    void ensureDirectory(const std::string& path);
}
