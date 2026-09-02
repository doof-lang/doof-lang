#pragma once
#include "doof_runtime.hpp"
namespace std_::blob::types { enum class Endian; }
namespace std_::blob::types { enum class TextEncoding; }
namespace std_::blob::types { enum class EncodingError; }

namespace std_::blob::index {
}

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
    struct StdlibPreparationCommand;
    struct PackageDependency;
    struct PackageManifest;
}

namespace std_::time::duration {
    struct Duration;
}

namespace std_::os::index {
    struct ExecOptions;
    struct ExecResult;
}

namespace app_src_stdlib_preparation_ {
    struct StdlibPreparationTarget;
    extern int64_t MAX_STDLIB_PREPARATION_OUTPUT_BYTES;
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
    struct StdlibPreparationCommand : public std::enable_shared_from_this<StdlibPreparationCommand> {
    std::string program;
    std::shared_ptr<std::vector<std::string>> args;
    std::shared_ptr<doof::ordered_map<std::string, std::string>> env;
    std::string workingDirectory;
    StdlibPreparationCommand(std::string program, std::shared_ptr<std::vector<std::string>> args, std::shared_ptr<doof::ordered_map<std::string, std::string>> env, std::string workingDirectory) : program(program), args(args), env(env), workingDirectory(workingDirectory) {}
};
    struct PackageDependency : public std::enable_shared_from_this<PackageDependency> {
    std::string name;
    std::string path;
    PackageDependency(std::string name, std::string path) : name(name), path(path) {}
};
    struct PackageManifest : public std::enable_shared_from_this<PackageManifest> {
    std::string name;
    std::string version;
    std::string manifestPath;
    std::string rootDirectory;
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources;
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies;
    std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>> stdlibPreparation;
    std::shared_ptr<NativeBuildPlan> nativeBuild;
    std::string target;
    std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp;
    std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp;
    std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig;
    std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig;
    PackageManifest(std::string name, std::string version, std::string manifestPath, std::string rootDirectory, std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources, std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> dependencies, std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>> stdlibPreparation, std::shared_ptr<NativeBuildPlan> nativeBuild, std::string target, std::shared_ptr<::app_src_macos_app_::MacOSAppConfig> macosApp, std::shared_ptr<::app_src_ios_app_::IOSAppConfig> iosApp, std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig> packageConfig, std::shared_ptr<::app_src_ios_app_::IOSPackageConfig> iosPackageConfig) : name(name), version(version), manifestPath(manifestPath), rootDirectory(rootDirectory), resources(resources), dependencies(dependencies), stdlibPreparation(stdlibPreparation), nativeBuild(nativeBuild), target(target), macosApp(macosApp), iosApp(iosApp), packageConfig(packageConfig), iosPackageConfig(iosPackageConfig) {}
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

namespace app_src_stdlib_preparation_ {
    struct StdlibPreparationTarget : public std::enable_shared_from_this<StdlibPreparationTarget> {
    std::string nativeTarget;
    std::string sdkPath;
    std::string targetTriple;
    std::string configureHost;
    int32_t jobs;
    StdlibPreparationTarget(std::string nativeTarget, std::string sdkPath, std::string targetTriple, std::string configureHost, int32_t jobs) : nativeTarget(nativeTarget), sdkPath(sdkPath), targetTriple(targetTriple), configureHost(configureHost), jobs(jobs) {}
};
}

namespace doof_blob { using Endian = ::std_::blob::types::Endian; }
namespace doof_blob { using TextEncoding = ::std_::blob::types::TextEncoding; }
namespace doof_blob { using EncodingError = ::std_::blob::types::EncodingError; }
#include "native_blob.hpp"

namespace std_::path::index {
    std::string join(const std::shared_ptr<std::vector<std::string>>& parts);
}

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
    doof::Result<std::shared_ptr<ExecResult>, std::string> run(const std::string& command, const std::shared_ptr<std::vector<std::string>>& args, const std::shared_ptr<ExecOptions>& options);
}

namespace app_src_stdlib_preparation_ {
    std::string applyStdlibPreparationSubstitutions(const std::string& value, const std::string& packageRoot, const std::shared_ptr<StdlibPreparationTarget>& target);
    bool withinPackage(const std::string& path, const std::string& packageRoot);
    doof::Result<void, std::string> runPreparationCommand(const std::shared_ptr<::app_src_package_manifest_::StdlibPreparationCommand>& command, int32_t index, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::shared_ptr<StdlibPreparationTarget>& target);
    doof::Result<void, std::string> prepareStdlibPackage(const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& manifest, const std::shared_ptr<StdlibPreparationTarget>& target);
}
