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

namespace app_src_resource_state_ {
    struct MaterializedResource;
    struct ResourceState;
    extern int32_t RESOURCE_STATE_VERSION;
}

#include "std_json_index.hpp"

namespace app_src_resource_state_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
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
    std::shared_ptr<ResourceState> parseResourceState(const std::string& source);
    std::string renderResourceState(const std::shared_ptr<ResourceState>& state);
    std::shared_ptr<MaterializedResource> findMaterializedResource(const std::shared_ptr<ResourceState>& state, const std::string& sourcePath, const std::string& outputPath);
    bool materializedResourceIsCurrent(const std::shared_ptr<MaterializedResource>& previous, int64_t sourceSize, int64_t sourceModifiedNanos, int64_t outputSize, int64_t outputModifiedNanos);
}

namespace app_src_resource_state_ {
}
