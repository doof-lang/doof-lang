#include "src_dependency_policy.hpp"

namespace app_src_dependency_policy_ {
using namespace ::app_src_package_manifest_;
using namespace ::app_src_std_catalog_;


#line 34 "/src/dependency-policy.do"
bool hasMutableStdPackageInputs(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages) {
#line 35 "/src/dependency-policy.do"
    const auto& _iterable_2 = packages;
    for (const auto& package : *_iterable_2) {
#line 36 "/src/dependency-policy.do"
        if (package->mutable_ && doof::string_startsWith(package->logicalPrefix, std::string("/std/"))) {
#line 36 "/src/dependency-policy.do"
            return true;
        }
    }
#line 38 "/src/dependency-policy.do"
    return false;
}
#line 41 "/src/dependency-policy.do"
std::shared_ptr<::app_src_package_manifest_::DependencyResolution> resolutionForUrl(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>& resolutions, const std::string& url) {
#line 45 "/src/dependency-policy.do"
    const auto canonical = ::app_src_std_catalog_::canonicalDependencyUrl(url);
#line 46 "/src/dependency-policy.do"
    const auto& _iterable_4 = resolutions;
    for (const auto& resolution : *_iterable_4) {
#line 47 "/src/dependency-policy.do"
        if (::app_src_std_catalog_::canonicalDependencyUrl(resolution->url) == canonical) {
#line 47 "/src/dependency-policy.do"
            return resolution;
        }
    }
#line 49 "/src/dependency-policy.do"
    return nullptr;
}
#line 52 "/src/dependency-policy.do"
std::shared_ptr<::app_src_package_manifest_::PackageDependency> selectedPackageSource(const std::shared_ptr<::app_src_package_manifest_::PackageDependency>& dependency, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>& resolutions) {
#line 56 "/src/dependency-policy.do"
    if (dependency->url == std::string("")) {
#line 56 "/src/dependency-policy.do"
        return dependency;
    }
#line 57 "/src/dependency-policy.do"
    const auto resolution = resolutionForUrl(resolutions, dependency->url);
#line 58 "/src/dependency-policy.do"
    if (doof::is_null(resolution)) {
#line 58 "/src/dependency-policy.do"
        return dependency;
    }
#line 59 "/src/dependency-policy.do"
    return std::make_shared<::app_src_package_manifest_::PackageDependency>(dependency->name, std::string(""), ::app_src_std_catalog_::canonicalDependencyUrl(resolution->url), resolution->ref, resolution->commit);
}
#line 67 "/src/dependency-policy.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>, std::string> resolveExternalInputs(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
#line 71 "/src/dependency-policy.do"
    std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>> result = std::make_shared<std::vector<std::shared_ptr<ResolvedExternalInput>>>(std::vector<std::shared_ptr<ResolvedExternalInput>>{});
#line 72 "/src/dependency-policy.do"
    const auto& _iterable_6 = packages;
    for (const auto& owner : *_iterable_6) {
#line 73 "/src/dependency-policy.do"
        const auto& _iterable_8 = owner->manifest->externalDependencies;
        for (const auto& dependency : *_iterable_8) {
#line 74 "/src/dependency-policy.do"
            const auto resolution = resolutionForUrl(rootManifest->externalResolutions, dependency->url);
#line 75 "/src/dependency-policy.do"
            if ((!doof::is_null(resolution)) && (resolution->kind != dependency->kind)) {
#line 76 "/src/dependency-policy.do"
                return doof::Failure<std::string>{ (((std::string("External resolution for ") + ::app_src_std_catalog_::canonicalDependencyUrl(dependency->url)) + std::string(" must keep kind ")) + dependency->kind) };
            }
#line 78 "/src/dependency-policy.do"
            const auto selected = resolvedExternalInput(owner, dependency, resolution);
#line 79 "/src/dependency-policy.do"
            const auto& _iterable_10 = result;
            for (const auto& existing : *_iterable_10) {
#line 80 "/src/dependency-policy.do"
                if (::app_src_std_catalog_::canonicalDependencyUrl(existing->selectedUrl) != ::app_src_std_catalog_::canonicalDependencyUrl(selected->selectedUrl)) {
#line 80 "/src/dependency-policy.do"
                    continue;
                }
#line 81 "/src/dependency-policy.do"
                if (!sameSelectedExternal(existing, selected) && doof::is_null(resolution)) {
#line 82 "/src/dependency-policy.do"
                    return doof::Failure<std::string>{ ((((((std::string("Conflicting external dependency ") + ::app_src_std_catalog_::canonicalDependencyUrl(dependency->url)) + std::string(" requested by ")) + existing->owner->logicalPrefix) + std::string(" and ")) + owner->logicalPrefix) + std::string("; add a root resolutions.externalDependencies entry")) };
                }
            }
#line 89 "/src/dependency-policy.do"
            result->push_back(selected);
        }
    }
#line 92 "/src/dependency-policy.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>>{ result };
}
#line 95 "/src/dependency-policy.do"
doof::Result<void, std::string> validateDependencyPolicy(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages, const std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>& externals, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
#line 100 "/src/dependency-policy.do"
    const auto policy = rootManifest->policy;
#line 101 "/src/dependency-policy.do"
    const auto& _iterable_12 = packages;
    for (const auto& package : *_iterable_12) {
#line 102 "/src/dependency-policy.do"
        if (package->sourceKind == std::string("root")) {
#line 102 "/src/dependency-policy.do"
            continue;
        }
#line 103 "/src/dependency-policy.do"
        if (((package->introducedBy != std::string("")) && (package->sourceKind == std::string("git"))) && policy->hasPackageSourceAllowlist) {
#line 104 "/src/dependency-policy.do"
            if (doof::is_null(resolutionForUrl(rootManifest->packageResolutions, package->sourceUrl)) && !containsCanonicalUrl(policy->allowedPackageSources, package->sourceUrl)) {
#line 106 "/src/dependency-policy.do"
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive package ") + package->sourceUrl) + std::string(" introduced by ")) + package->introducedBy) };
            }
        }
#line 109 "/src/dependency-policy.do"
        auto _try_value_13 = validateTransitiveNativePolicy(package, policy);
        if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
    }
#line 111 "/src/dependency-policy.do"
    const auto& _iterable_15 = externals;
    for (const auto& external : *_iterable_15) {
#line 112 "/src/dependency-policy.do"
        if (external->owner->sourceKind == std::string("root")) {
#line 112 "/src/dependency-policy.do"
            continue;
        }
#line 113 "/src/dependency-policy.do"
        if ((rootManifest->policy->hasExternalSourceAllowlist && doof::is_null(resolutionForUrl(rootManifest->externalResolutions, external->selectedUrl))) && !containsCanonicalUrl(rootManifest->policy->allowedExternalSources, external->selectedUrl)) {
#line 116 "/src/dependency-policy.do"
            return doof::Failure<std::string>{ (((std::string("Policy rejected transitive external dependency ") + ::app_src_std_catalog_::canonicalDependencyUrl(external->selectedUrl)) + std::string(" introduced by ")) + external->owner->logicalPrefix) };
        }
    }
#line 122 "/src/dependency-policy.do"
    return doof::Success<void>{};
}
#line 125 "/src/dependency-policy.do"
std::shared_ptr<ResolvedExternalInput> resolvedExternalInput(const std::shared_ptr<ReachedPackageInput>& owner, const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::shared_ptr<::app_src_package_manifest_::DependencyResolution>& resolution) {
#line 130 "/src/dependency-policy.do"
    if (doof::is_null(resolution)) {
#line 131 "/src/dependency-policy.do"
        return std::make_shared<ResolvedExternalInput>(owner, dependency, dependency->kind, ::app_src_std_catalog_::canonicalDependencyUrl(dependency->url), dependency->ref, dependency->commit, dependency->sha256, false);
    }
#line 136 "/src/dependency-policy.do"
    return std::make_shared<ResolvedExternalInput>(owner, dependency, resolution->kind, ::app_src_std_catalog_::canonicalDependencyUrl(resolution->url), resolution->ref, resolution->commit, resolution->sha256, ((((resolution->kind != dependency->kind) || (resolution->ref != dependency->ref)) || (resolution->commit != dependency->commit)) || (resolution->sha256 != dependency->sha256)));
}
#line 144 "/src/dependency-policy.do"
bool sameSelectedExternal(const std::shared_ptr<ResolvedExternalInput>& left, const std::shared_ptr<ResolvedExternalInput>& right) {
#line 145 "/src/dependency-policy.do"
    if (left->selectedKind != right->selectedKind) {
#line 145 "/src/dependency-policy.do"
        return false;
    }
#line 146 "/src/dependency-policy.do"
    if (left->selectedKind == std::string("git")) {
#line 146 "/src/dependency-policy.do"
        return (left->selectedCommit == right->selectedCommit);
    }
#line 147 "/src/dependency-policy.do"
    return (left->selectedSha256 == right->selectedSha256);
}
#line 150 "/src/dependency-policy.do"
bool containsCanonicalUrl(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
#line 151 "/src/dependency-policy.do"
    const auto canonical = ::app_src_std_catalog_::canonicalDependencyUrl(value);
#line 152 "/src/dependency-policy.do"
    const auto& _iterable_17 = values;
    for (const auto& existing : *_iterable_17) {
#line 152 "/src/dependency-policy.do"
        if (::app_src_std_catalog_::canonicalDependencyUrl(existing) == canonical) {
#line 152 "/src/dependency-policy.do"
            return true;
        }
    }
#line 153 "/src/dependency-policy.do"
    return false;
}
#line 156 "/src/dependency-policy.do"
doof::Result<void, std::string> validateTransitiveNativePolicy(const std::shared_ptr<ReachedPackageInput>& package, const std::shared_ptr<::app_src_package_manifest_::DependencyPolicy>& policy) {
#line 160 "/src/dependency-policy.do"
    if (policy->hasLinkLibraryAllowlist) {
#line 161 "/src/dependency-policy.do"
        const auto& _iterable_19 = package->manifest->nativeBuild->linkLibraries;
        for (const auto& value : *_iterable_19) {
#line 162 "/src/dependency-policy.do"
            if (!doof::array_contains(policy->allowedLinkLibraries, value, "", 0)) {
#line 163 "/src/dependency-policy.do"
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive link library ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
#line 167 "/src/dependency-policy.do"
    if (policy->hasFrameworkAllowlist) {
#line 168 "/src/dependency-policy.do"
        const auto& _iterable_21 = package->manifest->nativeBuild->frameworks;
        for (const auto& value : *_iterable_21) {
#line 169 "/src/dependency-policy.do"
            if (!doof::array_contains(policy->allowedFrameworks, value, "", 0)) {
#line 170 "/src/dependency-policy.do"
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive framework ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
#line 174 "/src/dependency-policy.do"
    if (policy->hasPkgConfigAllowlist) {
#line 175 "/src/dependency-policy.do"
        const auto& _iterable_23 = package->manifest->nativeBuild->pkgConfigPackages;
        for (const auto& value : *_iterable_23) {
#line 176 "/src/dependency-policy.do"
            if (!doof::array_contains(policy->allowedPkgConfigPackages, value, "", 0)) {
#line 177 "/src/dependency-policy.do"
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive pkg-config package ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
#line 181 "/src/dependency-policy.do"
    return doof::Success<void>{};
}
#line 1 "<doof-generated>"
}
