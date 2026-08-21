#pragma once
#include "doof_runtime.hpp"
namespace app_src_std_catalog_ {
    struct StdCatalogPackage;
    struct StdCatalog;
}

namespace app_src_std_catalog_ {
    struct StdCatalogPackage : public std::enable_shared_from_this<StdCatalogPackage> {
    std::string name;
    std::string url;
    std::string ref;
    std::string version;
    std::string commit;
    StdCatalogPackage(std::string name, std::string url, std::string ref, std::string version, std::string commit) : name(name), url(url), ref(ref), version(version), commit(commit) {}
};
    struct StdCatalog : public std::enable_shared_from_this<StdCatalog> {
    int32_t schemaVersion;
    std::string compilerVersion;
    std::string digest;
    std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> packages;
    StdCatalog(int32_t schemaVersion, std::string compilerVersion, std::string digest, std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> packages) : schemaVersion(schemaVersion), compilerVersion(compilerVersion), digest(digest), packages(packages) {}
};
}

#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text);
    std::string formatJsonValue(const doof::JsonValue& value);
}

namespace app_src_std_catalog_ {
    std::string canonicalDependencyUrl(const std::string& value);
    doof::Result<std::shared_ptr<StdCatalog>, std::string> parseStdCatalog(const std::string& source);
    std::shared_ptr<StdCatalogPackage> stdCatalogPackage(const std::shared_ptr<StdCatalog>& catalog, const std::string& name);
    doof::Result<std::string, std::string> catalogString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name);
    doof::Result<int32_t, std::string> catalogInt(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name);
}
