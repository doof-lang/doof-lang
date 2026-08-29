#pragma once
#include "doof_runtime.hpp"
namespace std_::json::index {
}

namespace app_src_frontend_cache_ {
    struct FrontendSourceProbe;
    struct FrontendFileInput;
    struct FrontendModuleOutput;
    struct FrontendCacheState;
    extern int32_t FRONTEND_CACHE_VERSION;
    extern int32_t FRONTEND_SEMANTIC_ABI;
}

namespace app_src_frontend_cache_ {
    struct FrontendSourceProbe : public std::enable_shared_from_this<FrontendSourceProbe> {
    std::string logicalPath;
    std::string sourceHash;
    bool missing;
    FrontendSourceProbe(std::string logicalPath, std::string sourceHash, bool missing) : logicalPath(logicalPath), sourceHash(sourceHash), missing(missing) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendSourceProbe>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct FrontendFileInput : public std::enable_shared_from_this<FrontendFileInput> {
    std::string path;
    std::string sourceHash;
    FrontendFileInput(std::string path, std::string sourceHash) : path(path), sourceHash(sourceHash) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendFileInput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct FrontendModuleOutput : public std::enable_shared_from_this<FrontendModuleOutput> {
    std::string modulePath;
    std::string headerName;
    std::string sourceName;
    std::string fingerprint;
    FrontendModuleOutput(std::string modulePath, std::string headerName, std::string sourceName, std::string fingerprint) : modulePath(modulePath), headerName(headerName), sourceName(sourceName), fingerprint(fingerprint) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendModuleOutput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
    struct FrontendCacheState : public std::enable_shared_from_this<FrontendCacheState> {
    int32_t version;
    std::string configurationFingerprint;
    std::shared_ptr<std::vector<std::shared_ptr<FrontendSourceProbe>>> probes;
    std::shared_ptr<std::vector<std::shared_ptr<FrontendFileInput>>> fileInputs;
    std::shared_ptr<std::vector<std::shared_ptr<FrontendModuleOutput>>> modules;
    FrontendCacheState(int32_t version, std::string configurationFingerprint, std::shared_ptr<std::vector<std::shared_ptr<FrontendSourceProbe>>> probes, std::shared_ptr<std::vector<std::shared_ptr<FrontendFileInput>>> fileInputs, std::shared_ptr<std::vector<std::shared_ptr<FrontendModuleOutput>>> modules) : version(version), configurationFingerprint(configurationFingerprint), probes(probes), fileInputs(fileInputs), modules(modules) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendCacheState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient);
};
}

#include "std/json/native_json.hpp"

namespace app_src_frontend_cache_ {
    std::shared_ptr<FrontendCacheState> parseFrontendCacheState(const std::string& source);
    std::string renderFrontendCacheState(const std::shared_ptr<FrontendCacheState>& state);
}
