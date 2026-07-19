#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_macos_app_ {
    struct MacOSAppResource;
    struct MacOSEmbeddedLibrary;
    struct MacOSAppConfig;
    struct MacOSPackageConfig;
}

namespace app_src_macos_app_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct MacOSAppResource : public std::enable_shared_from_this<MacOSAppResource> {
    std::string sourcePath;
    std::string destination;
    MacOSAppResource(std::string sourcePath, std::string destination) : sourcePath(sourcePath), destination(destination) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSAppResource>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct MacOSEmbeddedLibrary : public std::enable_shared_from_this<MacOSEmbeddedLibrary> {
    std::string library = std::string("");
    std::string path = std::string("");
    MacOSEmbeddedLibrary(std::string library = std::string(""), std::string path = std::string("")) : library(library), path(path) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSEmbeddedLibrary>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct MacOSAppConfig : public std::enable_shared_from_this<MacOSAppConfig> {
    std::string executableName;
    std::string bundleId;
    std::string displayName;
    std::string version;
    std::string iconPath = std::string("");
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr;
    std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<MacOSAppResource>>>(std::vector<std::shared_ptr<MacOSAppResource>>{});
    std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>{});
    std::string category = std::string("public.app-category.developer-tools");
    std::string minimumSystemVersion = std::string("11.0");
    MacOSAppConfig(std::string executableName, std::string bundleId, std::string displayName, std::string version, std::string iconPath = std::string(""), std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr, std::shared_ptr<std::vector<std::shared_ptr<MacOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<MacOSAppResource>>>(std::vector<std::shared_ptr<MacOSAppResource>>{}), std::shared_ptr<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<MacOSEmbeddedLibrary>>{}), std::string category = std::string("public.app-category.developer-tools"), std::string minimumSystemVersion = std::string("11.0")) : executableName(executableName), bundleId(bundleId), displayName(displayName), version(version), iconPath(iconPath), infoPlist(infoPlist), resources(resources), embeddedLibraries(embeddedLibraries), category(category), minimumSystemVersion(minimumSystemVersion) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSAppConfig>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct MacOSPackageConfig : public std::enable_shared_from_this<MacOSPackageConfig> {
    std::string distDirectory = std::string("");
    std::string signing = std::string("developer-id");
    std::string identity = std::string("");
    bool sandbox = false;
    std::string entitlementsPath = std::string("");
    MacOSPackageConfig(std::string distDirectory = std::string(""), std::string signing = std::string("developer-id"), std::string identity = std::string(""), bool sandbox = false, std::string entitlementsPath = std::string("")) : distDirectory(distDirectory), signing(signing), identity(identity), sandbox(sandbox), entitlementsPath(entitlementsPath) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MacOSPackageConfig>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string macOSPackageArchiveName(std::string executableName, std::string version);
    std::string renderMacOSInfoPlist(std::shared_ptr<MacOSAppConfig> config);
    std::shared_ptr<std::vector<std::string>> macOSCodesignArguments(std::string targetPath, std::string identity, std::string signing, std::string entitlementsPath = std::string(""));
    std::string plistString(std::string key, std::string value);
    std::string plistIndent(int32_t depth);
    std::string renderPlistValue(doof::JsonValue value, int32_t depth);
    std::string escapePlistText(std::string value);
}

namespace app_src_macos_app_ {
}
