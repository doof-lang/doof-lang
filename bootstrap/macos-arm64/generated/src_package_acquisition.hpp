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
namespace std_::blob::index { struct BlobReader; }
namespace std_::os::index { struct ExecOptions; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_package_acquisition_ {
    struct ExactPackageSource;
    struct AcquiredPackage;
}

#include "std_blob_index.hpp"
#include "std_fs_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "src_std_catalog.hpp"

namespace app_src_package_acquisition_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    struct ExactPackageSource : public std::enable_shared_from_this<ExactPackageSource> {
    std::string name;
    std::string expectedManifestName = std::string("");
    std::string url;
    std::string ref;
    std::string commit;
    ExactPackageSource(std::string name, std::string expectedManifestName, std::string url, std::string ref, std::string commit) : name(name), expectedManifestName(expectedManifestName), url(url), ref(ref), commit(commit) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<ExactPackageSource>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    struct AcquiredPackage : public std::enable_shared_from_this<AcquiredPackage> {
    std::shared_ptr<ExactPackageSource> source;
    std::string rootDirectory;
    bool mutable_ = false;
    AcquiredPackage(std::shared_ptr<ExactPackageSource> source, std::string rootDirectory, bool mutable_ = false) : source(source), rootDirectory(rootDirectory), mutable_(mutable_) {}
    doof::JsonObject toJsonObject() const;
    static doof::Result<std::shared_ptr<AcquiredPackage>, std::string> fromJsonValue(const doof::JsonValue& _json, bool _lenient = false);
};
    std::string workspacePackageAcquisitionRoot(std::string workspaceRoot);
    std::string packageAcquisitionPath(std::string packagesRoot, std::string packageName);
    std::string packageAcquisitionReceiptPath(std::string packageRoot);
    doof::Result<std::shared_ptr<AcquiredPackage>, std::string> acquireExactGitPackage(std::shared_ptr<ExactPackageSource> source, std::string packagesRoot);
    bool validPackageAcquisitionName(std::string name);
    bool reusableAcquiredPackage(std::string root, std::shared_ptr<ExactPackageSource> source);
    bool acquisitionReceiptMatches(std::string path, std::shared_ptr<ExactPackageSource> source);
    std::optional<std::string> acquisitionReceiptString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name);
    std::optional<int32_t> acquisitionReceiptInt(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name);
    std::string renderAcquisitionReceipt(std::shared_ptr<ExactPackageSource> source);
    doof::Result<void, std::string> validateAcquiredPackage(std::string root, std::shared_ptr<ExactPackageSource> source);
    doof::Result<std::string, std::string> packageCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments);
    doof::Result<void, std::string> ensurePackageDirectory(std::string path);
    doof::Result<void, std::string> removePackageTree(std::string path);
}

namespace app_src_package_acquisition_ {
}
