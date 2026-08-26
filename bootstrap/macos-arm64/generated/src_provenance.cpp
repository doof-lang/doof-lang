#include "src_provenance.hpp"

namespace app_src_provenance_ {
using namespace ::app_src_dependency_policy_;
using namespace ::app_src_package_manifest_;
using namespace ::app_src_std_catalog_;
using namespace ::std_::json::index;
#line 8 "/src/provenance.do"
std::string renderBuildProvenance(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>& packages, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& externals, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& nativeBuild, const std::shared_ptr<::app_src_std_catalog_::StdCatalog>& catalog) {
#line 14 "/src/provenance.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 15 "/src/provenance.do"
    provenanceSet(root, std::string("schemaVersion"), doof::json_value(2));
#line 16 "/src/provenance.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> compiler = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 17 "/src/provenance.do"
    provenanceSet(compiler, std::string("implementation"), doof::json_value(std::string("doof")));
#line 18 "/src/provenance.do"
    provenanceSet(compiler, std::string("version"), doof::json_value(catalog->compilerVersion));
#line 19 "/src/provenance.do"
    provenanceSet(compiler, std::string("stdCatalogDigest"), doof::json_value(catalog->digest));
#line 20 "/src/provenance.do"
    provenanceSet(root, std::string("compiler"), doof::json_value(compiler));
#line 22 "/src/provenance.do"
    std::shared_ptr<std::vector<doof::JsonValue>> packageValues = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
#line 23 "/src/provenance.do"
    const auto& _iterable_2 = sortedProvenancePackages(packages);
    for (const auto& package : *_iterable_2) {
#line 23 "/src/provenance.do"
        packageValues->push_back(doof::json_value(provenancePackage(package)));
    }
#line 24 "/src/provenance.do"
    provenanceSet(root, std::string("packages"), doof::json_value(packageValues));
#line 26 "/src/provenance.do"
    std::shared_ptr<std::vector<doof::JsonValue>> externalValues = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
#line 27 "/src/provenance.do"
    const auto& _iterable_4 = sortedProvenanceExternals(externals);
    for (const auto& input : *_iterable_4) {
#line 27 "/src/provenance.do"
        externalValues->push_back(doof::json_value(provenanceExternal(input)));
    }
#line 28 "/src/provenance.do"
    provenanceSet(root, std::string("externalDependencies"), doof::json_value(externalValues));
#line 29 "/src/provenance.do"
    provenanceSet(root, std::string("native"), doof::json_value(provenanceNative(nativeBuild)));
#line 30 "/src/provenance.do"
    return (::doof_json::format(doof::json_value(root)) + std::string("\n"));
}
#line 33 "/src/provenance.do"
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenancePackage(const std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>& package) {
#line 34 "/src/provenance.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 35 "/src/provenance.do"
    provenanceSet(value, std::string("name"), doof::json_value(package->manifest->name));
#line 36 "/src/provenance.do"
    provenanceSet(value, std::string("logicalPrefix"), doof::json_value(package->logicalPrefix));
#line 37 "/src/provenance.do"
    provenanceSet(value, std::string("introducedBy"), doof::json_value(package->introducedBy));
#line 38 "/src/provenance.do"
    provenanceSet(value, std::string("kind"), doof::json_value(package->sourceKind));
#line 39 "/src/provenance.do"
    provenanceSet(value, std::string("mutable"), doof::json_value(package->mutable_));
#line 40 "/src/provenance.do"
    if (package->sourceUrl != std::string("")) {
#line 40 "/src/provenance.do"
        provenanceSet(value, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(package->sourceUrl)));
    }
#line 41 "/src/provenance.do"
    if (package->sourceRef != std::string("")) {
#line 41 "/src/provenance.do"
        provenanceSet(value, std::string("ref"), doof::json_value(package->sourceRef));
    }
#line 42 "/src/provenance.do"
    if (package->sourceCommit != std::string("")) {
#line 42 "/src/provenance.do"
        provenanceSet(value, std::string("commit"), doof::json_value(package->sourceCommit));
    }
#line 43 "/src/provenance.do"
    if ((package->requestedCommit != std::string("")) && ((::app_src_std_catalog_::canonicalDependencyUrl(package->requestedUrl) != ::app_src_std_catalog_::canonicalDependencyUrl(package->sourceUrl)) || (package->requestedCommit != package->sourceCommit))) {
#line 47 "/src/provenance.do"
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> requested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 48 "/src/provenance.do"
        provenanceSet(requested, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(package->requestedUrl)));
#line 49 "/src/provenance.do"
        provenanceSet(requested, std::string("ref"), doof::json_value(package->requestedRef));
#line 50 "/src/provenance.do"
        provenanceSet(requested, std::string("commit"), doof::json_value(package->requestedCommit));
#line 51 "/src/provenance.do"
        provenanceSet(value, std::string("requested"), doof::json_value(requested));
    }
#line 53 "/src/provenance.do"
    if (package->sourceKind == std::string("local")) {
#line 53 "/src/provenance.do"
        provenanceSet(value, std::string("path"), doof::json_value(package->manifest->rootDirectory));
    }
#line 54 "/src/provenance.do"
    return value;
}
#line 57 "/src/provenance.do"
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenanceExternal(const std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>& input) {
#line 58 "/src/provenance.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 59 "/src/provenance.do"
    provenanceSet(value, std::string("name"), doof::json_value(input->dependency->name));
#line 60 "/src/provenance.do"
    provenanceSet(value, std::string("introducedBy"), doof::json_value(input->owner->logicalPrefix));
#line 61 "/src/provenance.do"
    provenanceSet(value, std::string("kind"), doof::json_value(input->selectedKind));
#line 62 "/src/provenance.do"
    provenanceSet(value, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(input->selectedUrl)));
#line 63 "/src/provenance.do"
    provenanceSet(value, std::string("overridden"), doof::json_value(input->overridden));
#line 64 "/src/provenance.do"
    if (input->selectedKind == std::string("git")) {
#line 65 "/src/provenance.do"
        provenanceSet(value, std::string("ref"), doof::json_value(input->selectedRef));
#line 66 "/src/provenance.do"
        provenanceSet(value, std::string("commit"), doof::json_value(input->selectedCommit));
    } else {
#line 68 "/src/provenance.do"
        provenanceSet(value, std::string("sha256"), doof::json_value(input->selectedSha256));
    }
#line 70 "/src/provenance.do"
    if (input->overridden) {
#line 71 "/src/provenance.do"
        std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> requested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 72 "/src/provenance.do"
        provenanceSet(requested, std::string("kind"), doof::json_value(input->dependency->kind));
#line 73 "/src/provenance.do"
        provenanceSet(requested, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(input->dependency->url)));
#line 74 "/src/provenance.do"
        if (input->dependency->kind == std::string("git")) {
#line 75 "/src/provenance.do"
            provenanceSet(requested, std::string("ref"), doof::json_value(input->dependency->ref));
#line 76 "/src/provenance.do"
            provenanceSet(requested, std::string("commit"), doof::json_value(input->dependency->commit));
        } else {
#line 78 "/src/provenance.do"
            provenanceSet(requested, std::string("sha256"), doof::json_value(input->dependency->sha256));
        }
#line 80 "/src/provenance.do"
        provenanceSet(value, std::string("requested"), doof::json_value(requested));
    }
#line 82 "/src/provenance.do"
    return value;
}
#line 85 "/src/provenance.do"
std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> provenanceNative(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& nativeBuild) {
#line 86 "/src/provenance.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 87 "/src/provenance.do"
    provenanceSet(value, std::string("linkLibraries"), doof::json_value(provenanceStrings(nativeBuild->linkLibraries)));
#line 88 "/src/provenance.do"
    provenanceSet(value, std::string("frameworks"), doof::json_value(provenanceStrings(nativeBuild->frameworks)));
#line 89 "/src/provenance.do"
    provenanceSet(value, std::string("pkgConfigPackages"), doof::json_value(provenanceStrings(nativeBuild->pkgConfigPackages)));
#line 90 "/src/provenance.do"
    provenanceSet(value, std::string("sourceFiles"), doof::json_value(provenanceStrings(nativeBuild->sourceFiles)));
#line 91 "/src/provenance.do"
    return value;
}
#line 94 "/src/provenance.do"
std::shared_ptr<std::vector<doof::JsonValue>> provenanceStrings(const std::shared_ptr<std::vector<std::string>>& values) {
#line 95 "/src/provenance.do"
    std::shared_ptr<std::vector<doof::JsonValue>> result = std::make_shared<std::vector<doof::JsonValue>>(std::vector<doof::JsonValue>{});
#line 96 "/src/provenance.do"
    const auto& _iterable_6 = values;
    for (const auto& value : *_iterable_6) {
#line 96 "/src/provenance.do"
        result->push_back(doof::json_value(value));
    }
#line 97 "/src/provenance.do"
    return result;
}
#line 100 "/src/provenance.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> sortedProvenancePackages(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>& values) {
#line 101 "/src/provenance.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>>(std::vector<std::shared_ptr<::app_src_dependency_policy_::ReachedPackageInput>>{});
#line 102 "/src/provenance.do"
    const auto& _iterable_8 = values;
    for (const auto& value : *_iterable_8) {
#line 103 "/src/provenance.do"
        result->push_back(value);
#line 104 "/src/provenance.do"
        auto index = (static_cast<int32_t>((result)->size()) - 1);
#line 105 "/src/provenance.do"
        while ((index > 0) && (doof::array_at(result, index, "src/provenance", 105)->logicalPrefix < doof::array_at(result, (index - 1), "src/provenance", 105)->logicalPrefix)) {
#line 106 "/src/provenance.do"
            const auto previous = doof::array_at(result, (index - 1), "src/provenance", 106);
#line 107 "/src/provenance.do"
            (doof::array_at(result, (index - 1), "src/provenance", 107) = doof::array_at(result, index, "src/provenance", 107));
#line 108 "/src/provenance.do"
            (doof::array_at(result, index, "src/provenance", 108) = previous);
#line 109 "/src/provenance.do"
            (index -= 1);
        }
    }
#line 112 "/src/provenance.do"
    return result;
}
#line 115 "/src/provenance.do"
std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> sortedProvenanceExternals(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>& values) {
#line 116 "/src/provenance.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>> result = std::make_shared<std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>>(std::vector<std::shared_ptr<::app_src_dependency_policy_::ResolvedExternalInput>>{});
#line 117 "/src/provenance.do"
    const auto& _iterable_10 = values;
    for (const auto& value : *_iterable_10) {
#line 118 "/src/provenance.do"
        result->push_back(value);
#line 119 "/src/provenance.do"
        auto index = (static_cast<int32_t>((result)->size()) - 1);
#line 120 "/src/provenance.do"
        while (index > 0) {
#line 121 "/src/provenance.do"
            const auto key = ((((::app_src_std_catalog_::canonicalDependencyUrl(doof::array_at(result, index, "src/provenance", 121)->selectedUrl) + std::string("u0000")) + doof::array_at(result, index, "src/provenance", 121)->owner->logicalPrefix) + std::string("u0000")) + doof::array_at(result, index, "src/provenance", 121)->dependency->name);
#line 122 "/src/provenance.do"
            const auto previousKey = ((((::app_src_std_catalog_::canonicalDependencyUrl(doof::array_at(result, (index - 1), "src/provenance", 122)->selectedUrl) + std::string("u0000")) + doof::array_at(result, (index - 1), "src/provenance", 122)->owner->logicalPrefix) + std::string("u0000")) + doof::array_at(result, (index - 1), "src/provenance", 122)->dependency->name);
#line 123 "/src/provenance.do"
            if (key >= previousKey) {
#line 123 "/src/provenance.do"
                break;
            }
#line 124 "/src/provenance.do"
            const auto previous = doof::array_at(result, (index - 1), "src/provenance", 124);
#line 125 "/src/provenance.do"
            (doof::array_at(result, (index - 1), "src/provenance", 125) = doof::array_at(result, index, "src/provenance", 125));
#line 126 "/src/provenance.do"
            (doof::array_at(result, index, "src/provenance", 126) = previous);
#line 127 "/src/provenance.do"
            (index -= 1);
        }
    }
#line 130 "/src/provenance.do"
    return result;
}
#line 133 "/src/provenance.do"
void provenanceSet(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const doof::JsonValue& value) {
#line 134 "/src/provenance.do"
    doof::map_set(object, name, value, "", 0);
}
#line 1 "<doof-generated>"
}
