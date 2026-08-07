#pragma once
#include "doof_runtime.hpp"
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
    std::string sourceHash = std::string("");
    bool missing = false;
    FrontendSourceProbe(std::string logicalPath, std::string sourceHash = std::string(""), bool missing = false) : logicalPath(logicalPath), sourceHash(sourceHash), missing(missing) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendSourceProbe>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct FrontendFileInput : public std::enable_shared_from_this<FrontendFileInput> {
    std::string path;
    std::string sourceHash;
    FrontendFileInput(std::string path, std::string sourceHash) : path(path), sourceHash(sourceHash) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendFileInput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct FrontendModuleOutput : public std::enable_shared_from_this<FrontendModuleOutput> {
    std::string modulePath;
    std::string headerName;
    std::string sourceName;
    std::string fingerprint = std::string("");
    FrontendModuleOutput(std::string modulePath, std::string headerName, std::string sourceName, std::string fingerprint = std::string("")) : modulePath(modulePath), headerName(headerName), sourceName(sourceName), fingerprint(fingerprint) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendModuleOutput>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct FrontendCacheState : public std::enable_shared_from_this<FrontendCacheState> {
    int32_t version = 2;
    std::string configurationFingerprint;
    std::shared_ptr<std::vector<std::shared_ptr<FrontendSourceProbe>>> probes = std::make_shared<std::vector<std::shared_ptr<FrontendSourceProbe>>>(std::vector<std::shared_ptr<FrontendSourceProbe>>{});
    std::shared_ptr<std::vector<std::shared_ptr<FrontendFileInput>>> fileInputs = std::make_shared<std::vector<std::shared_ptr<FrontendFileInput>>>(std::vector<std::shared_ptr<FrontendFileInput>>{});
    std::shared_ptr<std::vector<std::shared_ptr<FrontendModuleOutput>>> modules = std::make_shared<std::vector<std::shared_ptr<FrontendModuleOutput>>>(std::vector<std::shared_ptr<FrontendModuleOutput>>{});
    FrontendCacheState(int32_t version, std::string configurationFingerprint, std::shared_ptr<std::vector<std::shared_ptr<FrontendSourceProbe>>> probes = std::make_shared<std::vector<std::shared_ptr<FrontendSourceProbe>>>(std::vector<std::shared_ptr<FrontendSourceProbe>>{}), std::shared_ptr<std::vector<std::shared_ptr<FrontendFileInput>>> fileInputs = std::make_shared<std::vector<std::shared_ptr<FrontendFileInput>>>(std::vector<std::shared_ptr<FrontendFileInput>>{}), std::shared_ptr<std::vector<std::shared_ptr<FrontendModuleOutput>>> modules = std::make_shared<std::vector<std::shared_ptr<FrontendModuleOutput>>>(std::vector<std::shared_ptr<FrontendModuleOutput>>{})) : version(version), configurationFingerprint(configurationFingerprint), probes(probes), fileInputs(fileInputs), modules(modules) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<FrontendCacheState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text);
    std::string formatJsonValue(const doof::JsonValue& value);
}

namespace app_src_frontend_cache_ {
    std::shared_ptr<FrontendCacheState> parseFrontendCacheState(const std::string& source);
    std::string renderFrontendCacheState(const std::shared_ptr<FrontendCacheState>& state);
}
