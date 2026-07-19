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

namespace app_src_std_catalog_ {
    struct StdCatalogPackage;
    struct StdCatalog;
}

#include "std_json_index.hpp"

namespace app_src_std_catalog_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct StdCatalogPackage : public std::enable_shared_from_this<StdCatalogPackage> {
    std::string name;
    std::string url;
    std::string ref;
    std::string version;
    std::string commit;
    StdCatalogPackage(std::string name, std::string url, std::string ref, std::string version, std::string commit) : name(name), url(url), ref(ref), version(version), commit(commit) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<StdCatalogPackage>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct StdCatalog : public std::enable_shared_from_this<StdCatalog> {
    int32_t schemaVersion;
    std::string compilerVersion;
    std::string digest;
    std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> packages;
    StdCatalog(int32_t schemaVersion, std::string compilerVersion, std::string digest, std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> packages) : schemaVersion(schemaVersion), compilerVersion(compilerVersion), digest(digest), packages(packages) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<StdCatalog>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string canonicalDependencyUrl(std::string value);
    doof::Result<std::shared_ptr<StdCatalog>, std::string> parseStdCatalog(std::string source);
    std::shared_ptr<StdCatalogPackage> stdCatalogPackage(std::shared_ptr<StdCatalog> catalog, std::string name);
    doof::Result<std::string, std::string> catalogString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name);
    doof::Result<int32_t, std::string> catalogInt(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name);
}

namespace app_src_std_catalog_ {
}
