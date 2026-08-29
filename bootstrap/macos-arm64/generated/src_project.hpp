#pragma once
#include "doof_runtime.hpp"
namespace std_::fs::types { enum class IoError; }
namespace std_::fs::types { struct FileInfo; }
namespace std_::fs::types { enum class EntryKind; }

namespace app_src_macos_app_ {
    struct MacOSAppResource;
    struct MacOSEmbeddedLibrary;
    struct MacOSAppConfig;
    struct MacOSPackageConfig;
}

namespace app_src_ios_app_ {
    struct IOSAppResource;
    struct IOSEmbeddedLibrary;
    struct IOSAppConfig;
    struct IOSPackageConfig;
}

namespace app_src_package_manifest_ {
    struct NativeBuildPlan;
    struct PackageResource;
    struct ExternalDependencyCopyFile;
    struct ExternalDependencyCommand;
    struct ExternalDependency;
    struct PackageDependency;
    struct DependencyResolution;
    struct DependencyPolicy;
    struct PackageManifest;
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

namespace app_src_project_ {
    struct ProjectSpec;
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
  if (value == "Unsupported") return IoError::Unsupported;
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
    case IoError::Unsupported: return IoError::Unsupported;
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

namespace app_src_macos_app_ {
    struct MacOSAppResource : public std::enable_shared_from_this<MacOSAppResource> {
    std::string sourcePath;
    std::string destination;
    MacOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct MacOSEmbeddedLibrary : public std::enable_shared_from_this<MacOSEmbeddedLibrary> {
    std::string library;
    std::string path;
    MacOSEmbeddedLibrary(std::string library, std::string path) : library(library), path(path) {}
};
    struct MacOSAppConfig : public std::enable_shared_from_this<MacOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath;
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist;
    std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries;
    std::string category;
    std::string minimumSystemVersion;
    MacOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist, std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries, std::string category, std::string minimumSystemVersion) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), category(category), minimumSystemVersion(minimumSystemVersion) {}
};
    struct MacOSPackageConfig : public std::enable_shared_from_this<MacOSPackageConfig> {
    std::string distDirectory;
    std::string signing;
    std::string identity;
    bool sandbox;
    std::string entitlementsPath;
    MacOSPackageConfig(std::string distDirectory, std::string signing, std::string identity, bool sandbox, std::string entitlementsPath) : distDirectory(distDirectory), signing(signing), identity(identity), sandbox(sandbox), entitlementsPath(entitlementsPath) {}
};
}

namespace app_src_ios_app_ {
    struct IOSAppResource : public std::enable_shared_from_this<IOSAppResource> {
    std::string sourcePath;
    std::string destination;
    IOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct IOSEmbeddedLibrary : public std::enable_shared_from_this<IOSEmbeddedLibrary> {
    std::string library;
    std::string path;
    IOSEmbeddedLibrary(std::string library, std::string path) : library(library), path(path) {}
};
    struct IOSAppConfig : public std::enable_shared_from_this<IOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath;
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist;
    std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>> embeddedLibraries;
    std::string minimumDeploymentTarget;
    IOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist, std::shared_ptr<std::vector<std::shared_ptr<IOSAppResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<IOSEmbeddedLibrary>>> embeddedLibraries, std::string minimumDeploymentTarget) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), minimumDeploymentTarget(minimumDeploymentTarget) {}
};
    struct IOSPackageConfig : public std::enable_shared_from_this<IOSPackageConfig> {
    std::string identity;
    std::string provisioningProfilePath;
    IOSPackageConfig(std::string identity, std::string provisioningProfilePath) : identity(identity), provisioningProfilePath(provisioningProfilePath) {}
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
    struct PackageResource : public std::enable_shared_from_this<PackageResource> {
    std::string sourcePath;
    std::string destination;
    PackageResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
};
    struct ExternalDependencyCopyFile : public std::enable_shared_from_this<ExternalDependencyCopyFile> {
    std::string source;
    std::string destination;
    ExternalDependencyCopyFile(std::string source, std::string destination) : source(source), destination(destination) {}
};
    struct ExternalDependencyCommand : public std::enable_shared_from_this<ExternalDependencyCommand> {
    std::string program;
    std::shared_ptr<std::vector<std::string>> args;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env;
    std::string workingDirectory;
    ExternalDependencyCommand(std::string program, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<doof::ordered_map<std::string, std::string>> env, std::string workingDirectory) : program(program), args(args), env(env), workingDirectory(workingDirectory) {}
};
    struct ExternalDependency : public std::enable_shared_from_this<ExternalDependency> {
    std::string name;
    std::string kind;
    std::string url;
    std::string destination;
    std::string sha256;
    int32_t stripComponents;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> copyFiles;
    std::string ref;
    std::string commit;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> commands;
    ExternalDependency(std::string name, std::string kind, std::string url, std::string destination, std::string sha256, int32_t stripComponents, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> copyFiles, std::string ref, std::string commit, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> commands) : name(name), kind(kind), url(url), destination(destination), sha256(sha256), stripComponents(stripComponents), copyFiles(copyFiles), ref(ref), commit(commit), commands(commands) {}
};
    struct PackageDependency : public std::enable_shared_from_this<PackageDependency> {
    std::string name;
    std::string path;
    std::string url;
    std::string ref;
    std::string commit;
    PackageDependency(std::string name, std::string path, std::string url, std::string ref, std::string commit) : name(name), path(path), url(url), ref(ref), commit(commit) {}
};
    struct DependencyResolution : public std::enable_shared_from_this<DependencyResolution> {
    std::string name;
    std::string kind;
    std::string url;
    std::string ref;
    std::string commit;
    std::string sha256;
    DependencyResolution(std::string name, std::string kind, std::string url, std::string ref, std::string commit, std::string sha256) : name(name), kind(kind), url(url), ref(ref), commit(commit), sha256(sha256) {}
};
    struct DependencyPolicy : public std::enable_shared_from_this<DependencyPolicy> {
    bool hasPackageSourceAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedPackageSources;
    bool hasExternalSourceAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedExternalSources;
    bool hasLinkLibraryAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedLinkLibraries;
    bool hasFrameworkAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedFrameworks;
    bool hasPkgConfigAllowlist;
    std::shared_ptr<std::vector<std::string>> allowedPkgConfigPackages;
    DependencyPolicy(bool hasPackageSourceAllowlist, std::shared_ptr<std::vector<std::string>> allowedPackageSources, bool hasExternalSourceAllowlist, std::shared_ptr<std::vector<std::string>> allowedExternalSources, bool hasLinkLibraryAllowlist, std::shared_ptr<std::vector<std::string>> allowedLinkLibraries, bool hasFrameworkAllowlist, std::shared_ptr<std::vector<std::string>> allowedFrameworks, bool hasPkgConfigAllowlist, std::shared_ptr<std::vector<std::string>> allowedPkgConfigPackages) : hasPackageSourceAllowlist(hasPackageSourceAllowlist), allowedPackageSources(allowedPackageSources), hasExternalSourceAllowlist(hasExternalSourceAllowlist), allowedExternalSources(allowedExternalSources), hasLinkLibraryAllowlist(hasLinkLibraryAllowlist), allowedLinkLibraries(allowedLinkLibraries), hasFrameworkAllowlist(hasFrameworkAllowlist), allowedFrameworks(allowedFrameworks), hasPkgConfigAllowlist(hasPkgConfigAllowlist), allowedPkgConfigPackages(allowedPkgConfigPackages) {}
};
    struct PackageManifest : public std::enable_shared_from_this<PackageManifest> {
    std::string name;
    std::string version;
    std::string manifestPath;
    std::string rootDirectory;
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies;
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> externalDependencies;
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> packageResolutions;
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> externalResolutions;
    std::shared_ptr<DependencyPolicy> policy;
    std::shared_ptr<NativeBuildPlan> nativeBuild;
    std::string target;
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig;
    PackageManifest(std::string name, std::string version, std::string manifestPath, std::string rootDirectory, std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies, std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> externalDependencies, std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> packageResolutions, std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> externalResolutions, std::shared_ptr<DependencyPolicy> policy, std::shared_ptr<NativeBuildPlan> nativeBuild, std::string target, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig) : name(name), version(version), manifestPath(manifestPath), rootDirectory(rootDirectory), resources(resources), dependencies(dependencies), externalDependencies(externalDependencies), packageResolutions(packageResolutions), externalResolutions(externalResolutions), policy(policy), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
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

namespace app_src_project_ {
    struct ProjectSpec : public std::enable_shared_from_this<ProjectSpec> {
    std::string rootDirectory;
    std::string manifestPath;
    std::string name;
    std::string entry;
    std::string buildDirectory;
    bool hasManifest;
    bool explicitEntry;
    std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>> externalDependencies;
    std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild;
    std::string target;
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig;
    ProjectSpec(std::string rootDirectory, std::string manifestPath, std::string name, std::string entry, std::string buildDirectory, bool hasManifest, bool explicitEntry, std::shared_ptr<::app_src_package_manifest_::PackageManifest> manifest, std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>> externalDependencies, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::string target, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig) : rootDirectory(rootDirectory), manifestPath(manifestPath), name(name), entry(entry), buildDirectory(buildDirectory), hasManifest(hasManifest), explicitEntry(explicitEntry), manifest(manifest), resources(resources), externalDependencies(externalDependencies), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
};
}

#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text);
    std::string formatJsonValue(const doof::JsonValue& value);
}

namespace std_::path::index {
    doof::Result<std::string, std::string> absolute(const std::string& path);
    std::string join(const std::shared_ptr<std::vector<std::string>>& parts);
    std::string dirname(const std::string& path);
    std::string basename(const std::string& path);
}

namespace app_src_package_manifest_ {
    doof::Result<std::shared_ptr<PackageManifest>, std::string> parsePackageManifest(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& targetOverride);
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
    doof::Result<void, ::std_::fs::types::IoError> copyPermissions(const std::string& sourcePath, const std::string& destPath);
    bool isFile(const std::string& path);
}

namespace std_::os::index {
    doof::Result<std::string, std::string> env(const std::string& name);
}

namespace app_src_project_ {
    std::string projectManifestPath(const std::string& path);
    std::string environmentValue(const std::string& name);
    std::string fileName(const std::string& path);
    std::string parentPath(const std::string& path);
    std::string joinPath(const std::string& directory, const std::string& name);
    std::string projectEntryRequestError(const std::shared_ptr<ProjectSpec>& project, const std::string& requestedPath);
    std::shared_ptr<ProjectSpec> readProjectSpec(const std::string& requestedPath, const std::string& platform, const std::string& targetOverride);
}
