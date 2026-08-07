#pragma once
#include "doof_runtime.hpp"
namespace app_src_resource_state_ {
    struct MaterializedResource;
    struct ResourceState;
    extern int32_t RESOURCE_STATE_VERSION;
}

namespace app_src_resource_state_ {
    struct MaterializedResource : public std::enable_shared_from_this<MaterializedResource> {
    std::string sourcePath;
    std::string outputPath;
    int64_t sourceSize;
    int64_t sourceModifiedNanos;
    int64_t outputSize;
    int64_t outputModifiedNanos;
    MaterializedResource(std::string sourcePath, std::string outputPath, int64_t sourceSize, int64_t sourceModifiedNanos, int64_t outputSize, int64_t outputModifiedNanos) : sourcePath(sourcePath), outputPath(outputPath), sourceSize(sourceSize), sourceModifiedNanos(sourceModifiedNanos), outputSize(outputSize), outputModifiedNanos(outputModifiedNanos) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<MaterializedResource>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct ResourceState : public std::enable_shared_from_this<ResourceState> {
    int32_t version = 1;
    std::shared_ptr<std::vector<std::shared_ptr<MaterializedResource>>> files = std::make_shared<std::vector<std::shared_ptr<MaterializedResource>>>(std::vector<std::shared_ptr<MaterializedResource>>{});
    ResourceState(int32_t version = 1, std::shared_ptr<std::vector<std::shared_ptr<MaterializedResource>>> files = std::make_shared<std::vector<std::shared_ptr<MaterializedResource>>>(std::vector<std::shared_ptr<MaterializedResource>>{})) : version(version), files(files) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ResourceState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
}

#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text);
    std::string formatJsonValue(const doof::JsonValue& value);
}

namespace app_src_resource_state_ {
    std::shared_ptr<ResourceState> parseResourceState(const std::string& source);
    std::string renderResourceState(const std::shared_ptr<ResourceState>& state);
    std::shared_ptr<MaterializedResource> findMaterializedResource(const std::shared_ptr<ResourceState>& state, const std::string& sourcePath, const std::string& outputPath);
    bool materializedResourceIsCurrent(const std::shared_ptr<MaterializedResource>& previous, int64_t sourceSize, int64_t sourceModifiedNanos, int64_t outputSize, int64_t outputModifiedNanos);
}
