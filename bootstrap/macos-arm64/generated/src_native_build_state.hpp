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

namespace app_src_native_build_state_ {
    struct NativeInputSignature;
    struct NativeTaskState;
    struct NativeBuildState;
}

#include "std_json_index.hpp"

namespace app_src_native_build_state_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct NativeInputSignature : public std::enable_shared_from_this<NativeInputSignature> {
    std::string path;
    std::string signature;
    bool contentHash = true;
    NativeInputSignature(std::string path, std::string signature, bool contentHash = true) : path(path), signature(signature), contentHash(contentHash) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeInputSignature>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeTaskState : public std::enable_shared_from_this<NativeTaskState> {
    std::string id;
    std::string fingerprint;
    std::string outputPath;
    int64_t outputSize;
    int64_t outputModifiedNanos;
    std::shared_ptr<std::vector<std::shared_ptr<NativeInputSignature>>> inputs = std::make_shared<std::vector<std::shared_ptr<NativeInputSignature>>>(std::vector<std::shared_ptr<NativeInputSignature>>{});
    NativeTaskState(std::string id, std::string fingerprint, std::string outputPath, int64_t outputSize, int64_t outputModifiedNanos, std::shared_ptr<std::vector<std::shared_ptr<NativeInputSignature>>> inputs = std::make_shared<std::vector<std::shared_ptr<NativeInputSignature>>>(std::vector<std::shared_ptr<NativeInputSignature>>{})) : id(id), fingerprint(fingerprint), outputPath(outputPath), outputSize(outputSize), outputModifiedNanos(outputModifiedNanos), inputs(inputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeTaskState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct NativeBuildState : public std::enable_shared_from_this<NativeBuildState> {
    int32_t version = 1;
    std::shared_ptr<std::vector<std::shared_ptr<NativeTaskState>>> tasks = std::make_shared<std::vector<std::shared_ptr<NativeTaskState>>>(std::vector<std::shared_ptr<NativeTaskState>>{});
    std::shared_ptr<std::vector<std::string>> managedOutputs = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    NativeBuildState(int32_t version = 1, std::shared_ptr<std::vector<std::shared_ptr<NativeTaskState>>> tasks = std::make_shared<std::vector<std::shared_ptr<NativeTaskState>>>(std::vector<std::shared_ptr<NativeTaskState>>{}), std::shared_ptr<std::vector<std::string>> managedOutputs = std::make_shared<std::vector<std::string>>(std::vector<std::string>{})) : version(version), tasks(tasks), managedOutputs(managedOutputs) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<NativeBuildState>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::shared_ptr<NativeBuildState> parseNativeBuildState(const std::string& source);
    std::string renderNativeBuildState(const std::shared_ptr<NativeBuildState>& state);
    std::shared_ptr<NativeTaskState> findNativeTaskState(const std::shared_ptr<NativeBuildState>& state, const std::string& id);
    std::shared_ptr<std::vector<std::string>> parseMakeDependencies(const std::string& source);
    void appendUnique(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value);
}

namespace app_src_native_build_state_ {
    extern int32_t NATIVE_BUILD_STATE_VERSION;
}
