#include "src_provenance.hpp"
#include <cmath>
#include "src_dependency_policy.hpp"
#include "src_package_manifest.hpp"
#include "src_std_catalog.hpp"
#include "std_json_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_provenance_ {
using namespace ::app_src_dependency_policy_;
using namespace ::app_src_package_manifest_;
using namespace ::app_src_std_catalog_;
using namespace ::std_::json::index;
std::string renderBuildProvenance(std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> packages, std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> externals, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild, std::shared_ptr<::app_src_std_catalog_::StdCatalog> catalog) {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    provenanceSet(root, std::string("schemaVersion"), doof::json_value(2));
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> compiler = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    provenanceSet(compiler, std::string("implementation"), doof::json_value(std::string("doof")));
    provenanceSet(compiler, std::string("version"), doof::json_value(catalog->compilerVersion));
    provenanceSet(compiler, std::string("stdCatalogDigest"), doof::json_value(catalog->digest));
    provenanceSet(root, std::string("compiler"), doof::json_value(compiler));
    std::shared_ptr<std::vector<doof::JsonValue>> packageValues = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    const auto& _iterable_1 = sortedProvenancePackages(packages);
    for (const auto& package : *_iterable_1) {
        packageValues->push_back(doof::json_value(provenancePackage(package)));
    }
    provenanceSet(root, std::string("packages"), doof::json_value(packageValues));
    std::shared_ptr<std::vector<doof::JsonValue>> externalValues = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    const auto& _iterable_2 = sortedProvenanceExternals(externals);
    for (const auto& input : *_iterable_2) {
        externalValues->push_back(doof::json_value(provenanceExternal(input)));
    }
    provenanceSet(root, std::string("externalDependencies"), doof::json_value(externalValues));
    provenanceSet(root, std::string("native"), doof::json_value(provenanceNative(nativeBuild)));
    return (::std_::json::index::formatJsonValue(doof::json_value(root)) + std::string("\n"));
}
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenancePackage(std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput> package) {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    provenanceSet(value, std::string("name"), doof::json_value(package->manifest->name));
    provenanceSet(value, std::string("logicalPrefix"), doof::json_value(package->logicalPrefix));
    provenanceSet(value, std::string("introducedBy"), doof::json_value(package->introducedBy));
    provenanceSet(value, std::string("kind"), doof::json_value(package->sourceKind));
    provenanceSet(value, std::string("mutable"), doof::json_value(package->mutable_));
    if (package->sourceUrl != std::string("")) {
        provenanceSet(value, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(package->sourceUrl)));
    }
    if (package->sourceRef != std::string("")) {
        provenanceSet(value, std::string("ref"), doof::json_value(package->sourceRef));
    }
    if (package->sourceCommit != std::string("")) {
        provenanceSet(value, std::string("commit"), doof::json_value(package->sourceCommit));
    }
    if ((package->requestedCommit != std::string("")) && ((::app_src_std_catalog_::canonicalDependencyUrl(package->requestedUrl) != ::app_src_std_catalog_::canonicalDependencyUrl(package->sourceUrl)) || (package->requestedCommit != package->sourceCommit))) {
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> requested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
        provenanceSet(requested, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(package->requestedUrl)));
        provenanceSet(requested, std::string("ref"), doof::json_value(package->requestedRef));
        provenanceSet(requested, std::string("commit"), doof::json_value(package->requestedCommit));
        provenanceSet(value, std::string("requested"), doof::json_value(requested));
    }
    if (package->sourceKind == std::string("local")) {
        provenanceSet(value, std::string("path"), doof::json_value(package->manifest->rootDirectory));
    }
    return value;
}
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenanceExternal(std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput> input) {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    provenanceSet(value, std::string("name"), doof::json_value(input->dependency->name));
    provenanceSet(value, std::string("introducedBy"), doof::json_value(input->owner->logicalPrefix));
    provenanceSet(value, std::string("kind"), doof::json_value(input->selectedKind));
    provenanceSet(value, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(input->selectedUrl)));
    provenanceSet(value, std::string("overridden"), doof::json_value(input->overridden));
    if (input->selectedKind == std::string("git")) {
        provenanceSet(value, std::string("ref"), doof::json_value(input->selectedRef));
        provenanceSet(value, std::string("commit"), doof::json_value(input->selectedCommit));
    } else {
        provenanceSet(value, std::string("sha256"), doof::json_value(input->selectedSha256));
    }
    if (input->overridden) {
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> requested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
        provenanceSet(requested, std::string("kind"), doof::json_value(input->dependency->kind));
        provenanceSet(requested, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(input->dependency->url)));
        if (input->dependency->kind == std::string("git")) {
            provenanceSet(requested, std::string("ref"), doof::json_value(input->dependency->ref));
            provenanceSet(requested, std::string("commit"), doof::json_value(input->dependency->commit));
        } else {
            provenanceSet(requested, std::string("sha256"), doof::json_value(input->dependency->sha256));
        }
        provenanceSet(value, std::string("requested"), doof::json_value(requested));
    }
    return value;
}
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenanceNative(std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> nativeBuild) {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    provenanceSet(value, std::string("linkLibraries"), doof::json_value(provenanceStrings(nativeBuild->linkLibraries)));
    provenanceSet(value, std::string("frameworks"), doof::json_value(provenanceStrings(nativeBuild->frameworks)));
    provenanceSet(value, std::string("pkgConfigPackages"), doof::json_value(provenanceStrings(nativeBuild->pkgConfigPackages)));
    provenanceSet(value, std::string("sourceFiles"), doof::json_value(provenanceStrings(nativeBuild->sourceFiles)));
    return value;
}
std::shared_ptr<std::vector<doof::JsonValue>> provenanceStrings(std::shared_ptr<std::vector<std::string>> values) {
    std::shared_ptr<std::vector<doof::JsonValue>> result = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
    const auto& _iterable_3 = values;
    for (const auto& value : *_iterable_3) {
        result->push_back(doof::json_value(value));
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> sortedProvenancePackages(std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> values) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>(std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>{});
    const auto& _iterable_4 = values;
    for (const auto& value : *_iterable_4) {
        result->push_back(value);
        auto index = (static_cast<int32_t>((result)->size()) - 1);
        while ((index > 0) && ((*result)[index]->logicalPrefix < (*result)[(index - 1)]->logicalPrefix)) {
            const auto previous = (*result)[(index - 1)];
            ((*result)[(index - 1)] = (*result)[index]);
            ((*result)[index] = previous);
            (index -= 1);
        }
    }
    return result;
}
std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> sortedProvenanceExternals(std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> values) {
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>(std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>{});
    const auto& _iterable_5 = values;
    for (const auto& value : *_iterable_5) {
        result->push_back(value);
        auto index = (static_cast<int32_t>((result)->size()) - 1);
        while (index > 0) {
            const auto key = ((((::app_src_std_catalog_::canonicalDependencyUrl((*result)[index]->selectedUrl) + std::string("u0000")) + (*result)[index]->owner->logicalPrefix) + std::string("u0000")) + (*result)[index]->dependency->name);
            const auto previousKey = ((((::app_src_std_catalog_::canonicalDependencyUrl((*result)[(index - 1)]->selectedUrl) + std::string("u0000")) + (*result)[(index - 1)]->owner->logicalPrefix) + std::string("u0000")) + (*result)[(index - 1)]->dependency->name);
            if (key >= previousKey) {
                break;
            }
            const auto previous = (*result)[(index - 1)];
            ((*result)[(index - 1)] = (*result)[index]);
            ((*result)[index] = previous);
            (index -= 1);
        }
    }
    return result;
}
void provenanceSet(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name, doof::JsonValue value) {
    doof::map_set(object, name, value, "", 0);
}
}
