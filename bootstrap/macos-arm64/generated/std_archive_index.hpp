#pragma once
#include "doof_runtime.hpp"
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::types { enum class IoError; }
namespace std_::fs::types { struct FileInfo; }
namespace std_::fs::types { enum class EntryKind; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::os::index { enum class ProcessGroupMode; }
namespace std_::os::index { struct ExecOptions; }
namespace std_::os::index { struct Exec; }
namespace std_::os::index { struct ExecResult; }
namespace std_::time::duration { struct Duration; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::gzip::index { struct GzipStream; }
namespace std_::archive::tar_writer { struct TarChunkStream; }
namespace std_::zstd::index { struct ZstdCompressStream; }

namespace std_::fs::types {
    struct FileInfo;
}

namespace std_::fs::index {
    struct BlockReadStream;
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
    struct ExecStdoutStream;
    struct ExecStderrStream;
    struct Exec;
    struct ExecResult;
}

namespace std_::archive::types {
    struct ZipEntry;
    struct ZipFileEntry;
    struct TarEntry;
    struct TarArchive;
    struct TarWriteEntry;
}

namespace std_::gzip::index {
    struct GzipStream;
}

namespace std_::archive::tar_writer {
    struct TarChunk;
    struct TarChunkStream;
}

namespace std_::zstd::index {
    struct ZstdCompressStream;
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
    enum class TarEntryKind {
    File = 0,
    Directory = 1,
    SymbolicLink = 2
};
inline const char* TarEntryKind_name(TarEntryKind value) {
  switch (value) {
    case TarEntryKind::File: return "File";
    case TarEntryKind::Directory: return "Directory";
    case TarEntryKind::SymbolicLink: return "SymbolicLink";
  }
  doof::panic(std::string("Invalid TarEntryKind enum value: ") + doof::to_string(static_cast<int32_t>(value)));
}
inline std::optional<TarEntryKind> TarEntryKind_fromName(std::string_view value) {
  if (value == "File") return TarEntryKind::File;
  if (value == "Directory") return TarEntryKind::Directory;
  if (value == "SymbolicLink") return TarEntryKind::SymbolicLink;
  return std::nullopt;
}
inline int32_t TarEntryKind_value(TarEntryKind value) { return static_cast<int32_t>(value); }
inline std::optional<TarEntryKind> TarEntryKind_fromValue(int32_t value) {
  if (value == 0) return TarEntryKind::File;
  if (value == 1) return TarEntryKind::Directory;
  if (value == 2) return TarEntryKind::SymbolicLink;
  return std::nullopt;
}
inline std::shared_ptr<std::vector<TarEntryKind>> TarEntryKind_values() { return std::make_shared<std::vector<TarEntryKind>>(std::initializer_list<TarEntryKind>{TarEntryKind::File, TarEntryKind::Directory, TarEntryKind::SymbolicLink}); }
inline doof::JsonValue TarEntryKind_toJsonValue(TarEntryKind value) { return doof::json_value(TarEntryKind_value(value)); }
inline doof::Result<TarEntryKind, std::string> TarEntryKind_fromJsonValue(const doof::JsonValue& value, bool) {
  if (!(doof::json_is_integer(value))) return doof::Failure<std::string>{std::string("Expected integer for enum TarEntryKind, got ") + doof::json_type_name(value)};
  auto resolved = TarEntryKind_fromValue(doof::json_as_int(value));
  if (!resolved.has_value()) return doof::Failure<std::string>{std::string("Unknown backing value for enum TarEntryKind: ") + doof::to_string(doof::json_as_int(value)) + "; expected one of 0, 1, 2"};
  return doof::Success<TarEntryKind>{resolved.value()};
}
inline std::ostream& operator<<(std::ostream& output, TarEntryKind value) { return output << TarEntryKind_name(value); }
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

namespace std_::fs::types {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::fs::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::time::duration {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::time::temporal {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::os::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<ExecStdoutStream>, std::shared_ptr<ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::archive::types {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::gzip::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::archive::reader {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::archive::zip_file_reader {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::archive::writer {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::archive::tar_reader {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::archive::tar_file_reader {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::archive::tar_writer {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
}

namespace std_::zstd::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<ZstdCompressStream>>;
}

namespace std_::archive::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>, std::shared_ptr<::std_::gzip::index::GzipStream>, std::shared_ptr<::std_::archive::tar_writer::TarChunkStream>, std::shared_ptr<::std_::zstd::index::ZstdCompressStream>>;
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

namespace std_::archive::types {
    struct TarArchive : public std::enable_shared_from_this<TarArchive> {
    std::shared_ptr<std::vector<uint8_t>> data;
    std::shared_ptr<std::vector<std::shared_ptr<TarEntry>>> entries;
    TarArchive(std::shared_ptr<std::vector<uint8_t>> data, std::shared_ptr<std::vector<std::shared_ptr<TarEntry>>> entries) : data(data), entries(entries) {}
    std::shared_ptr<std::vector<uint8_t>> entryData(const std::shared_ptr<TarEntry>& entry);
};
}

namespace std_::archive::tar_writer {
    struct TarChunk : public std::enable_shared_from_this<TarChunk> {
    std::shared_ptr<std::vector<uint8_t>> data;
    TarChunk(std::shared_ptr<std::vector<uint8_t>> data) : data(data) {}
};
    struct TarChunkStream : public std::enable_shared_from_this<TarChunkStream> {
    std::shared_ptr<std::vector<std::shared_ptr<TarChunk>>> chunks;
    int32_t index;
    std::shared_ptr<std::vector<uint8_t>> currentValue;
    TarChunkStream(std::shared_ptr<std::vector<std::shared_ptr<TarChunk>>> chunks, int32_t index, std::shared_ptr<std::vector<uint8_t>> currentValue) : chunks(chunks), index(index), currentValue(currentValue) {}
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
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

namespace std_::fs::index {
    struct BlockReadStream : public std::enable_shared_from_this<BlockReadStream> {
    std::shared_ptr<::NativeBlobReadStream> native;
    std::shared_ptr<std::vector<uint8_t>> currentValue;
    BlockReadStream(std::shared_ptr<::NativeBlobReadStream> native, std::shared_ptr<std::vector<uint8_t>> currentValue) : native(native), currentValue(currentValue) {}
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
}

namespace doof_os { using ProcessGroupMode = ::std_::os::index::ProcessGroupMode; }
namespace doof_os { using ExecOptions = ::std_::os::index::ExecOptions; }
namespace doof_os { using Exec = ::std_::os::index::Exec; }
namespace doof_os { using ExecResult = ::std_::os::index::ExecResult; }
namespace doof_os { using Duration = ::std_::time::duration::Duration; }
using ProcessGroupMode = ::std_::os::index::ProcessGroupMode;
using ExecOptions = ::std_::os::index::ExecOptions;
using Exec = ::std_::os::index::Exec;
using ExecResult = ::std_::os::index::ExecResult;
using Duration = ::std_::time::duration::Duration;
#include "native_os.hpp"

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
    struct ExecStdoutStream : public std::enable_shared_from_this<ExecStdoutStream> {
    std::shared_ptr<::NativeExecProcess> process;
    std::shared_ptr<std::vector<uint8_t>> currentValue;
    ExecStdoutStream(std::shared_ptr<::NativeExecProcess> process, std::shared_ptr<std::vector<uint8_t>> currentValue) : process(process), currentValue(currentValue) {}
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
    struct ExecStderrStream : public std::enable_shared_from_this<ExecStderrStream> {
    std::shared_ptr<::NativeExecProcess> process;
    std::shared_ptr<std::vector<uint8_t>> currentValue;
    ExecStderrStream(std::shared_ptr<::NativeExecProcess> process, std::shared_ptr<std::vector<uint8_t>> currentValue) : process(process), currentValue(currentValue) {}
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
    struct Exec : public std::enable_shared_from_this<Exec> {
    std::shared_ptr<::NativeExecProcess> native;
    Exec(std::shared_ptr<::NativeExecProcess> native) : native(native) {}
    static doof::Result<std::shared_ptr<Exec>, std::string> spawn(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options);
    Stream__readonly_array_byte stdoutStream();
    Stream__readonly_array_byte stderrStream();
    std::shared_ptr<std::vector<uint8_t>> nextStdoutChunk();
    std::shared_ptr<std::vector<uint8_t>> nextStderrChunk();
    doof::Result<void, std::string> writeStdinText(const std::string& value);
    doof::Result<void, std::string> closeStdin();
    bool isRunning();
    doof::Result<int32_t, std::string> wait();
    doof::Result<void, std::string> terminate(int32_t signal);
    bool stdoutOpen();
    bool stderrOpen();
};
}

namespace std_::archive::types {
    struct ZipEntry : public std::enable_shared_from_this<ZipEntry> {
    std::string name;
    ArchiveEntryKind kind;
    int64_t size;
    int64_t compressedSize;
    int64_t crc32;
    ZipCompression compression;
    std::shared_ptr<std::vector<uint8_t>> data;
    ZipEntry(std::string name, ArchiveEntryKind kind, int64_t size, int64_t compressedSize, int64_t crc32, ZipCompression compression, std::shared_ptr<std::vector<uint8_t>> data) : name(name), kind(kind), size(size), compressedSize(compressedSize), crc32(crc32), compression(compression), data(data) {}
};
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
    struct TarEntry : public std::enable_shared_from_this<TarEntry> {
    std::string name;
    TarEntryKind kind;
    int64_t contentOffset;
    int64_t size;
    int32_t mode;
    std::shared_ptr<::std_::time::temporal::Instant> mtime;
    std::string linkName;
    TarEntry(std::string name, TarEntryKind kind, int64_t contentOffset, int64_t size, int32_t mode, std::shared_ptr<::std_::time::temporal::Instant> mtime, std::string linkName) : name(name), kind(kind), contentOffset(contentOffset), size(size), mode(mode), mtime(mtime), linkName(linkName) {}
};
    struct TarWriteEntry : public std::enable_shared_from_this<TarWriteEntry> {
    std::string name;
    TarEntryKind kind;
    std::shared_ptr<std::vector<uint8_t>> data;
    std::optional<int32_t> mode;
    std::shared_ptr<::std_::time::temporal::Instant> mtime;
    std::string linkName;
    TarWriteEntry(std::string name, TarEntryKind kind, std::shared_ptr<std::vector<uint8_t>> data, std::optional<int32_t> mode, std::shared_ptr<::std_::time::temporal::Instant> mtime, std::string linkName) : name(name), kind(kind), data(data), mode(mode), mtime(mtime), linkName(linkName) {}
};
}

namespace doof_gzip { using GzipStream = ::std_::gzip::index::GzipStream; }
#include "native_gzip.hpp"

namespace std_::gzip::index {
    struct GzipStream : public std::enable_shared_from_this<GzipStream> {
    Stream__readonly_array_byte source;
    std::shared_ptr<::doof_gzip::NativeGzipEncoder> native;
    std::shared_ptr<std::vector<uint8_t>> currentValue;
    bool sourceDone;
    bool finished;
    GzipStream(Stream__readonly_array_byte source, std::shared_ptr<::doof_gzip::NativeGzipEncoder> native, std::shared_ptr<std::vector<uint8_t>> currentValue, bool sourceDone, bool finished) : source(source), native(native), currentValue(currentValue), sourceDone(sourceDone), finished(finished) {}
    static std::shared_ptr<GzipStream> constructor(const Stream__readonly_array_byte& source);
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
}

namespace std_::archive::reader {
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipEntry>>>, std::string> readZip(const std::shared_ptr<std::vector<uint8_t>>& data);
}

namespace std_::archive::zip_file_reader {
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>>, std::string> scanZipFile(const std::string& path);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> readZipEntry(const std::string& path, const std::shared_ptr<::std_::archive::types::ZipFileEntry>& entry);
}

namespace std_::archive::writer {
    std::shared_ptr<std::vector<uint8_t>> writeZip(const std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipEntry>>>& entries);
}

namespace std_::archive::tar_reader {
    doof::Result<std::shared_ptr<::std_::archive::types::TarArchive>, std::string> readTarBlob(const std::shared_ptr<std::vector<uint8_t>>& data);
    doof::Result<std::shared_ptr<::std_::archive::types::TarArchive>, std::string> readTarFile(const std::string& path);
}

namespace std_::archive::tar_file_reader {
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>>, std::string> scanTarFile(const std::string& path);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> readTarEntry(const std::string& path, const std::shared_ptr<::std_::archive::types::TarEntry>& entry);
}

namespace std_::archive::tar_writer {
    std::shared_ptr<std::vector<uint8_t>> writeTarBlob(const std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarWriteEntry>>>& entries);
    doof::Result<void, std::string> writeTarFile(const std::string& path, const std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarWriteEntry>>>& entries);
}

namespace doof_zstd { using ZstdCompressStream = ::std_::zstd::index::ZstdCompressStream; }
#include "native_zstd.hpp"

namespace std_::zstd::index {
    struct ZstdCompressStream : public std::enable_shared_from_this<ZstdCompressStream> {
    Stream__readonly_array_byte source;
    int32_t level;
    std::shared_ptr<::doof_zstd::NativeZstdEncoder> native;
    std::shared_ptr<std::vector<uint8_t>> currentValue;
    bool sourceDone;
    bool finished;
    std::optional<std::string> failed;
    ZstdCompressStream(Stream__readonly_array_byte source, int32_t level, std::shared_ptr<::doof_zstd::NativeZstdEncoder> native, std::shared_ptr<std::vector<uint8_t>> currentValue, bool sourceDone, bool finished, std::optional<std::string> failed) : source(source), level(level), native(native), currentValue(currentValue), sourceDone(sourceDone), finished(finished), failed(failed) {}
    static std::shared_ptr<ZstdCompressStream> constructor(const Stream__readonly_array_byte& source, int32_t level);
    static std::shared_ptr<ZstdCompressStream> withLevel(const Stream__readonly_array_byte& source, int32_t level);
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
}
