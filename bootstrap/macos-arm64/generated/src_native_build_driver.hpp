#pragma once
#include "doof_runtime.hpp"
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }
namespace std_::fs::types { enum class IoError; }
namespace std_::fs::types { struct FileInfo; }
namespace std_::fs::types { enum class EntryKind; }

namespace std_::blob::index {
}

namespace app_src_emitter_module_ {
    struct ModuleEmission;
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan;
}

namespace std_::fs::types {
    struct FileInfo;
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

namespace app_src_native_build_driver_ {
    struct NativeCommandResult;
    struct NativeCompilerBatchResult;
    struct NativeCompilerIdentity;
    struct NativeCompilerWorker;
    extern int32_t MAX_NATIVE_OUTPUT_LINES;
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
  return "";
}
inline std::optional<EntryKind> EntryKind_fromName(std::string_view value) {
  if (value == "File") return EntryKind::File;
  if (value == "Directory") return EntryKind::Directory;
  if (value == "Symlink") return EntryKind::Symlink;
  if (value == "Other") return EntryKind::Other;
  return std::nullopt;
}
inline std::optional<EntryKind> EntryKind_fromValue(int32_t value) {
  switch (static_cast<EntryKind>(value)) {
    case EntryKind::File: return EntryKind::File;
    case EntryKind::Directory: return EntryKind::Directory;
    case EntryKind::Symlink: return EntryKind::Symlink;
    case EntryKind::Other: return EntryKind::Other;
    default: return std::nullopt;
  }
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
    Other = 7
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
  }
  return "";
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
  return std::nullopt;
}
inline std::optional<IoError> IoError_fromValue(int32_t value) {
  switch (static_cast<IoError>(value)) {
    case IoError::NotFound: return IoError::NotFound;
    case IoError::PermissionDenied: return IoError::PermissionDenied;
    case IoError::AlreadyExists: return IoError::AlreadyExists;
    case IoError::IsDirectory: return IoError::IsDirectory;
    case IoError::NotDirectory: return IoError::NotDirectory;
    case IoError::InvalidPath: return IoError::InvalidPath;
    case IoError::Interrupted: return IoError::Interrupted;
    case IoError::Other: return IoError::Other;
    default: return std::nullopt;
  }
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
  return "";
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
inline std::optional<DayOfWeek> DayOfWeek_fromValue(int32_t value) {
  switch (static_cast<DayOfWeek>(value)) {
    case DayOfWeek::Monday: return DayOfWeek::Monday;
    case DayOfWeek::Tuesday: return DayOfWeek::Tuesday;
    case DayOfWeek::Wednesday: return DayOfWeek::Wednesday;
    case DayOfWeek::Thursday: return DayOfWeek::Thursday;
    case DayOfWeek::Friday: return DayOfWeek::Friday;
    case DayOfWeek::Saturday: return DayOfWeek::Saturday;
    case DayOfWeek::Sunday: return DayOfWeek::Sunday;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, DayOfWeek value) { return output << DayOfWeek_name(value); }
}

namespace std_::os::index {
    enum class ProcessGroupMode {
    Isolated,
    Inherited
};
inline const char* ProcessGroupMode_name(ProcessGroupMode value) {
  switch (value) {
    case ProcessGroupMode::Isolated: return "Isolated";
    case ProcessGroupMode::Inherited: return "Inherited";
  }
  return "";
}
inline std::optional<ProcessGroupMode> ProcessGroupMode_fromName(std::string_view value) {
  if (value == "Isolated") return ProcessGroupMode::Isolated;
  if (value == "Inherited") return ProcessGroupMode::Inherited;
  return std::nullopt;
}
inline std::optional<ProcessGroupMode> ProcessGroupMode_fromValue(int32_t value) {
  switch (static_cast<ProcessGroupMode>(value)) {
    case ProcessGroupMode::Isolated: return ProcessGroupMode::Isolated;
    case ProcessGroupMode::Inherited: return ProcessGroupMode::Inherited;
    default: return std::nullopt;
  }
}
inline std::ostream& operator<<(std::ostream& output, ProcessGroupMode value) { return output << ProcessGroupMode_name(value); }
}

namespace app_src_native_build_ {
    using NativeCompileTaskBatch = std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>;
}

namespace app_src_emitter_module_ {
    struct ModuleEmission : public std::enable_shared_from_this<ModuleEmission> {
    std::string modulePath;
    std::string header;
    std::string source;
    std::string headerName;
    std::string sourceName;
    int32_t coverageModuleId = -1;
    std::shared_ptr<std::vector<int32_t>> instrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{});
    bool reused = false;
    std::string fingerprint = std::string("");
    ModuleEmission(std::string modulePath, std::string header, std::string source, std::string headerName, std::string sourceName, int32_t coverageModuleId = -1, std::shared_ptr<std::vector<int32_t>> instrumentedLines = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{}), bool reused = false, std::string fingerprint = std::string("")) : modulePath(modulePath), header(header), source(source), headerName(headerName), sourceName(sourceName), coverageModuleId(coverageModuleId), instrumentedLines(instrumentedLines), reused(reused), fingerprint(fingerprint) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ModuleEmission>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan : public std::enable_shared_from_this<NativeBuildPlan> {
    std::shared_ptr<std::vector<std::string>> includePaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> sourceFiles = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> libraryPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> extraCopyPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> linkLibraries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> frameworks = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> pkgConfigPackages = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> defines = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> compilerFlags = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::shared_ptr<std::vector<std::string>> linkerFlags = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    NativeBuildPlan(std::shared_ptr<std::vector<std::string>> includePaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> sourceFiles = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> libraryPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> extraCopyPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> linkLibraries = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> frameworks = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> pkgConfigPackages = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> defines = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> compilerFlags = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::shared_ptr<std::vector<std::string>> linkerFlags = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : includePaths(includePaths), sourceFiles(sourceFiles), libraryPaths(libraryPaths), extraCopyPaths(extraCopyPaths), linkLibraries(linkLibraries), frameworks(frameworks), pkgConfigPackages(pkgConfigPackages), defines(defines), compilerFlags(compilerFlags), linkerFlags(linkerFlags) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Duration>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Instant>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Date>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    static doof::Result<std::shared_ptr<Time>, std::string> create(int32_t hour, int32_t minute, int32_t second = 0, int32_t nanosecond = 0);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<Time>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    // A combined calendar date and time-of-day. No timezone.
struct DateTime : public std::enable_shared_from_this<DateTime> {
    std::shared_ptr<Date> date;
    std::shared_ptr<Time> time;
    DateTime(std::shared_ptr<Date> date, std::shared_ptr<Time> time) : date(date), time(time) {}
    static std::shared_ptr<DateTime> create(const std::shared_ptr<Date>& date, const std::shared_ptr<Time>& time);
    static doof::Result<std::shared_ptr<DateTime>, std::string> fromParts(int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second = 0, int32_t nanosecond = 0);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<DateTime>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<TimeZone>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ZonedDateTime>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace std_::os::index {
    struct ExecResult : public std::enable_shared_from_this<ExecResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> stdout_;
    std::shared_ptr<std::vector<uint8_t>> stderr_;
    bool stdoutTruncated = false;
    bool stderrTruncated = false;
    ExecResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> stdout_, std::shared_ptr<std::vector<uint8_t>> stderr_, bool stdoutTruncated = false, bool stderrTruncated = false) : exitCode(exitCode), stdout_(stdout_), stderr_(stderr_), stdoutTruncated(stdoutTruncated), stderrTruncated(stderrTruncated) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExecResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_emitter_project_ {
    struct ProjectNativeCopy : public std::enable_shared_from_this<ProjectNativeCopy> {
    std::string sourcePath;
    std::string relativePath;
    ProjectNativeCopy(std::string sourcePath, std::string relativePath) : sourcePath(sourcePath), relativePath(relativePath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ProjectNativeCopy>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ProjectSupportFile : public std::enable_shared_from_this<ProjectSupportFile> {
    std::string relativePath;
    std::string content;
    ProjectSupportFile(std::string relativePath, std::string content) : relativePath(relativePath), content(content) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ProjectSupportFile>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ProjectEmission : public std::enable_shared_from_this<ProjectEmission> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules;
    std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> supportFiles = std::make_shared<std::vector<std::shared_ptr<ProjectSupportFile>>>(std::vector<std::shared_ptr<ProjectSupportFile>>{});
    std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> nativeCopies = std::make_shared<std::vector<std::shared_ptr<ProjectNativeCopy>>>(std::vector<std::shared_ptr<ProjectNativeCopy>>{});
    std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild;
    std::shared_ptr<std::vector<std::string>> wasmExportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    ProjectEmission(std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules, std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> supportFiles, std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> nativeCopies, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::shared_ptr<std::vector<std::string>> wasmExportNames) : modules(modules), supportFiles(supportFiles), nativeCopies(nativeCopies), nativeBuild(nativeBuild), wasmExportNames(wasmExportNames) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ProjectEmission>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_native_build_ {
    struct NativeCompileTask : public std::enable_shared_from_this<NativeCompileTask> {
    std::string id;
    std::string compiler;
    std::string sourcePath;
    std::string outputPath;
    std::string dependencyFilePath = std::string("");
    std::shared_ptr<std::vector<std::string>> auxiliaryOutputPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    bool usesPrecompiledHeader = false;
    std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    NativeCompileTask(std::string id, std::string compiler, std::string sourcePath, std::string outputPath, std::string dependencyFilePath = std::string(""), std::shared_ptr<std::vector<std::string>> auxiliaryOutputPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), bool usesPrecompiledHeader = false, std::shared_ptr<std::vector<std::string>> arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : id(id), compiler(compiler), sourcePath(sourcePath), outputPath(outputPath), dependencyFilePath(dependencyFilePath), auxiliaryOutputPaths(auxiliaryOutputPaths), usesPrecompiledHeader(usesPrecompiledHeader), arguments(arguments) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompileTask>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeBuildSupportFile : public std::enable_shared_from_this<NativeBuildSupportFile> {
    std::string outputPath;
    std::string content;
    NativeBuildSupportFile(std::string outputPath, std::string content) : outputPath(outputPath), content(content) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeBuildSupportFile>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilePlan : public std::enable_shared_from_this<NativeCompilePlan> {
    std::string compiler;
    std::string linker;
    std::shared_ptr<std::vector<std::shared_ptr<NativeBuildSupportFile>>> supportFiles = std::make_shared<std::vector<std::shared_ptr<NativeBuildSupportFile>>>(std::vector<std::shared_ptr<NativeBuildSupportFile>>{});
    std::shared_ptr<NativeCompileTask> precompiledHeaderTask = nullptr;
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{});
    std::shared_ptr<std::vector<std::string>> linkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    std::string outputPath;
    NativeCompilePlan(std::string compiler, std::string linker, std::shared_ptr<std::vector<std::shared_ptr<NativeBuildSupportFile>>> supportFiles, std::shared_ptr<NativeCompileTask> precompiledHeaderTask, std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks, std::shared_ptr<std::vector<std::string>> linkArguments, std::string outputPath) : compiler(compiler), linker(linker), supportFiles(supportFiles), precompiledHeaderTask(precompiledHeaderTask), compileTasks(compileTasks), linkArguments(linkArguments), outputPath(outputPath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilePlan>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_native_build_state_ {
    struct NativeInputSignature : public std::enable_shared_from_this<NativeInputSignature> {
    std::string path;
    std::string signature;
    bool contentHash = true;
    int64_t size = -1LL;
    int64_t modifiedNanos = -1LL;
    NativeInputSignature(std::string path, std::string signature, bool contentHash = true, int64_t size = -1LL, int64_t modifiedNanos = -1LL) : path(path), signature(signature), contentHash(contentHash), size(size), modifiedNanos(modifiedNanos) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeInputSignature>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeTaskState : public std::enable_shared_from_this<NativeTaskState> {
    std::string id;
    std::string fingerprint;
    std::string outputPath;
    int64_t outputSize;
    int64_t outputModifiedNanos;
    std::shared_ptr<std::vector<std::shared_ptr<NativeInputSignature>>> inputs = std::make_shared<std::vector<std::shared_ptr<NativeInputSignature>>>(std::vector<std::shared_ptr<NativeInputSignature>>{});
    NativeTaskState(std::string id, std::string fingerprint, std::string outputPath, int64_t outputSize, int64_t outputModifiedNanos, std::shared_ptr<std::vector<std::shared_ptr<NativeInputSignature>>> inputs = std::make_shared<std::vector<std::shared_ptr<NativeInputSignature>>>(std::vector<std::shared_ptr<NativeInputSignature>>{})) : id(id), fingerprint(fingerprint), outputPath(outputPath), outputSize(outputSize), outputModifiedNanos(outputModifiedNanos), inputs(inputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeTaskState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeBuildState : public std::enable_shared_from_this<NativeBuildState> {
    int32_t version = 2;
    std::shared_ptr<std::vector<std::shared_ptr<NativeTaskState>>> tasks = std::make_shared<std::vector<std::shared_ptr<NativeTaskState>>>(std::vector<std::shared_ptr<NativeTaskState>>{});
    std::shared_ptr<std::vector<std::string>> managedOutputs = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    NativeBuildState(int32_t version = 2, std::shared_ptr<std::vector<std::shared_ptr<NativeTaskState>>> tasks = std::make_shared<std::vector<std::shared_ptr<NativeTaskState>>>(std::vector<std::shared_ptr<NativeTaskState>>{}), std::shared_ptr<std::vector<std::string>> managedOutputs = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : version(version), tasks(tasks), managedOutputs(managedOutputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeBuildState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_pkg_config_ {
    struct PkgConfigCommandResult : public std::enable_shared_from_this<PkgConfigCommandResult> {
    int32_t exitCode;
    std::string output = std::string("");
    std::string error = std::string("");
    PkgConfigCommandResult(int32_t exitCode, std::string output = std::string(""), std::string error = std::string("")) : exitCode(exitCode), output(output), error(error) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<PkgConfigCommandResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

namespace app_src_native_build_driver_ {
    struct NativeCommandResult : public std::enable_shared_from_this<NativeCommandResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<uint8_t>> output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    std::string error = std::string("");
    bool truncated;
    std::string quietSourcePath = std::string("");
    NativeCommandResult(int32_t exitCode, std::shared_ptr<std::vector<uint8_t>> output, std::string error, bool truncated, std::string quietSourcePath = std::string("")) : exitCode(exitCode), output(output), error(error), truncated(truncated), quietSourcePath(quietSourcePath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCommandResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilerBatchResult : public std::enable_shared_from_this<NativeCompilerBatchResult> {
    int32_t exitCode;
    std::shared_ptr<std::vector<std::shared_ptr<NativeCommandResult>>> outputs;
    NativeCompilerBatchResult(int32_t exitCode, std::shared_ptr<std::vector<std::shared_ptr<NativeCommandResult>>> outputs) : exitCode(exitCode), outputs(outputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilerBatchResult>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilerIdentity : public std::enable_shared_from_this<NativeCompilerIdentity> {
    std::string command;
    std::string signature;
    NativeCompilerIdentity(std::string command, std::string signature) : command(command), signature(signature) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilerIdentity>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeCompilerWorker : public std::enable_shared_from_this<NativeCompilerWorker> {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>> tasks;
    NativeCompilerWorker(std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_::NativeCompileTask>>> tasks) : tasks(tasks) {}
    std::shared_ptr<NativeCompilerBatchResult> compile();
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeCompilerWorker>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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

namespace std_::fs::types {
    struct FileInfo : public std::enable_shared_from_this<FileInfo> {
    std::string name;
    EntryKind kind;
    int64_t size;
    std::shared_ptr<::std_::time::temporal::Instant> modifiedAt;
    FileInfo(std::string name, EntryKind kind, int64_t size, std::shared_ptr<::std_::time::temporal::Instant> modifiedAt) : name(name), kind(kind), size(size), modifiedAt(modifiedAt) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FileInfo>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
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
    bool exists(const std::string& path);
    doof::Result<std::string, ::std_::fs::types::IoError> readText(const std::string& path);
    doof::Result<void, ::std_::fs::types::IoError> mkdir(const std::string& path);
    bool isDirectory(const std::string& path);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>>, ::std_::fs::types::IoError> readDir(const std::string& path);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBlob(const std::string& path);
    doof::Result<void, ::std_::fs::types::IoError> writeText(const std::string& path, const std::string& content);
    doof::Result<void, ::std_::fs::types::IoError> rename(const std::string& sourcePath, const std::string& destPath);
    doof::Result<void, ::std_::fs::types::IoError> remove(const std::string& path);
    doof::Result<void, ::std_::fs::types::IoError> writeBlob(const std::string& path, const std::shared_ptr<std::vector<uint8_t>>& data);
    doof::Result<std::shared_ptr<::std_::fs::types::FileInfo>, ::std_::fs::types::IoError> metadata(const std::string& path);
    bool isFile(const std::string& path);
}

namespace std_::os::index {
    struct ExecOptions : public std::enable_shared_from_this<ExecOptions> {
    std::optional<std::string> cwd = std::nullopt;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    bool inheritEnv = true;
    bool withStdin = true;
    bool mergeStderrIntoStdout = false;
    bool inheritOutput = false;
    ProcessGroupMode processGroupMode = ProcessGroupMode::Isolated;
    std::optional<int64_t> maxOutputBytes = std::nullopt;
    std::shared_ptr<::std_::time::duration::Duration> timeout = nullptr;
    ExecOptions(std::optional<std::string> cwd = std::nullopt, std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), bool inheritEnv = true, bool withStdin = true, bool mergeStderrIntoStdout = false, bool inheritOutput = false, ProcessGroupMode processGroupMode = ProcessGroupMode::Isolated, std::optional<int64_t> maxOutputBytes = std::nullopt, std::shared_ptr<::std_::time::duration::Duration> timeout = nullptr) : cwd(cwd), env(env), inheritEnv(inheritEnv), withStdin(withStdin), mergeStderrIntoStdout(mergeStderrIntoStdout), inheritOutput(inheritOutput), processGroupMode(processGroupMode), maxOutputBytes(maxOutputBytes), timeout(timeout) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExecOptions>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    doof::Result<std::string, std::string> env(const std::string& name);
    doof::Result<std::shared_ptr<ExecResult>, std::string> run(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), const std::shared_ptr<ExecOptions>& options = std::make_shared<ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, true, false, false, ProcessGroupMode::Isolated, std::nullopt, nullptr));
}

namespace app_src_native_build_ {
    bool isMsvcCompiler(const std::string& compiler);
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>> batchNativeCompileTasks(const std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>& tasks, int32_t maximumWorkers = 4);
    std::shared_ptr<NativeCompilePlan> planNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, bool release = false, const std::string& platform = std::string(""), const std::shared_ptr<std::vector<std::string>>& wasmExportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), bool wasm = false);
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

namespace app_src_native_build_driver_ {
    std::shared_ptr<NativeCommandResult> runBuildCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& quietSourcePath = std::string(""));
    bool isMsvcSourceEcho(const std::string& line, const std::string& sourcePath);
    int32_t printBuildOutput(const std::shared_ptr<NativeCommandResult>& result, int32_t remainingLines);
    int32_t buildNativeProject(const std::string& compilerOverride, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project, bool release, const std::string& platform);
    std::string envCompiler();
    int32_t executeNativePlan(const std::string& outputDirectory, const std::shared_ptr<::app_src_native_build_::NativeCompilePlan>& plan, const std::shared_ptr<::app_src_emitter_project_::ProjectEmission>& project);
    std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>> indexNativeTaskStates(const std::shared_ptr<::app_src_native_build_state_::NativeBuildState>& state);
    std::shared_ptr<::app_src_native_build_state_::NativeTaskState> indexedNativeTaskState(const std::shared_ptr<doof::ordered_map<std::string, std::shared_ptr<::app_src_native_build_state_::NativeTaskState>>>& indexed, const std::string& id);
    std::string compilerIdentity(const std::string& command, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities);
    std::string taskFingerprint(const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities);
    std::string linkFingerprint(const std::string& linker, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<NativeCompilerIdentity>>>& identities);
    std::shared_ptr<::app_src_native_build_state_::NativeInputSignature> pathSignature(const std::string& path, bool contentHash);
    std::shared_ptr<::app_src_native_build_state_::NativeInputSignature> currentInputSignature(const std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>& previous);
    bool taskIsCurrent(const std::shared_ptr<::app_src_native_build_state_::NativeTaskState>& previous, const std::string& fingerprint, const std::shared_ptr<std::vector<std::string>>& auxiliaryOutputPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    bool nativeTaskStateIsCurrent(const std::shared_ptr<::app_src_native_build_state_::NativeTaskState>& previous, const std::string& fingerprint, int64_t outputSize, int64_t outputModifiedNanos, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_native_build_state_::NativeInputSignature>>>& currentInputs, bool auxiliaryOutputsCurrent = true);
    std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureTaskState(const std::shared_ptr<::app_src_native_build_::NativeCompileTask>& task, const std::string& fingerprint);
    std::shared_ptr<::app_src_native_build_state_::NativeTaskState> captureLinkState(const std::string& outputPath, const std::string& fingerprint, const std::shared_ptr<std::vector<std::string>>& objectPaths);
    std::shared_ptr<::app_src_native_build_state_::NativeBuildState> readBuildState(const std::string& path);
    void writeBuildState(const std::string& path, const std::shared_ptr<::app_src_native_build_state_::NativeBuildState>& state);
    void writeTextIfChanged(const std::string& path, const std::string& content);
    bool nativeSupportFileNeedsWrite(const std::optional<std::string>& previous, const std::string& content);
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
    std::string parentDirectory(const std::string& path);
    void ensureDirectory(const std::string& path);
}
