#pragma once
#include "doof_runtime.hpp"
namespace app_src_native_build_state_ {
    struct NativeInputSignature;
    struct NativeTaskState;
    struct NativeBuildState;
    extern int32_t NATIVE_BUILD_STATE_VERSION;
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

#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text);
    std::string formatJsonValue(const doof::JsonValue& value);
}

namespace app_src_native_build_state_ {
    std::shared_ptr<NativeBuildState> parseNativeBuildState(const std::string& source);
    std::string renderNativeBuildState(const std::shared_ptr<NativeBuildState>& state);
    std::shared_ptr<NativeTaskState> findNativeTaskState(const std::shared_ptr<NativeBuildState>& state, const std::string& id);
    std::shared_ptr<std::vector<std::string>> parseMakeDependencies(const std::string& source);
    std::shared_ptr<std::vector<std::string>> parseMsvcDependencies(const std::string& source);
    void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value);
}
