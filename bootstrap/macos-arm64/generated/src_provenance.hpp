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
namespace app_src_dependency_policy_ { struct ReachedPackageInput; }
namespace app_src_dependency_policy_ { struct ResolvedExternalInput; }
namespace app_src_package_manifest_ { struct NativeBuildPlan; }
namespace app_src_std_catalog_ { struct StdCatalog; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace app_src_provenance_ {
}

#include "src_dependency_policy.hpp"
#include "src_package_manifest.hpp"
#include "src_std_catalog.hpp"
#include "std_json_index.hpp"

namespace app_src_provenance_ {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    std::string renderBuildProvenance(std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> packages, std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> externals, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::shared_ptr<::app_src_std_catalog_::StdCatalog> catalog);
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenancePackage(std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput> package);
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenanceExternal(std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput> input);
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenanceNative(std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild);
    std::shared_ptr<std::vector<doof::JsonValue>> provenanceStrings(std::shared_ptr<std::vector<std::string>> values);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> sortedProvenancePackages(std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> values);
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> sortedProvenanceExternals(std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> values);
    void provenanceSet(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name, doof::JsonValue value);
}

namespace app_src_provenance_ {
}
