#include "src_dependency_policy.hpp"

namespace app_src_dependency_policy_ {
using namespace ::app_src_package_manifest_;
using namespace ::app_src_std_catalog_;


bool hasMutableStdPackageInputs(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages) {
    const auto& _iterable_2 = packages;
    for (const auto& package : *_iterable_2) {
        if (package->mutable_ && doof::string_startsWith(package->logicalPrefix, std::string("/std/"))) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<::app_src_package_manifest_::DependencyResolution> resolutionForUrl(const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>& resolutions, const std::string& url) {
    const auto canonical = ::app_src_std_catalog_::canonicalDependencyUrl(url);
    const auto& _iterable_4 = resolutions;
    for (const auto& resolution : *_iterable_4) {
        if (::app_src_std_catalog_::canonicalDependencyUrl(resolution->url) == canonical) {
            return resolution;
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_package_manifest_::PackageDependency> selectedPackageSource(const std::shared_ptr<::app_src_package_manifest_::PackageDependency>& dependency, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>& resolutions) {
    if (dependency->url == std::string("")) {
        return dependency;
    }
    const auto resolution = resolutionForUrl(resolutions, dependency->url);
    if (doof::is_null(resolution)) {
        return dependency;
    }
    return std::make_shared<::app_src_package_manifest_::PackageDependency>(dependency->name, std::string(""), ::app_src_std_catalog_::canonicalDependencyUrl(resolution->url), resolution->ref, resolution->commit);
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>, std::string> resolveExternalInputs(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
    std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>> result = std::make_shared<std::vector<std::shared_ptr<ResolvedExternalInput>>>(std::vector<std::shared_ptr<ResolvedExternalInput>>{});
    const auto& _iterable_6 = packages;
    for (const auto& owner : *_iterable_6) {
        const auto& _iterable_8 = owner->manifest->externalDependencies;
        for (const auto& dependency : *_iterable_8) {
            const auto resolution = resolutionForUrl(rootManifest->externalResolutions, dependency->url);
            if ((!doof::is_null(resolution)) && (resolution->kind != dependency->kind)) {
                return doof::Failure<std::string>{ (((std::string("External resolution for ") + ::app_src_std_catalog_::canonicalDependencyUrl(dependency->url)) + std::string(" must keep kind ")) + dependency->kind) };
            }
            const auto selected = resolvedExternalInput(owner, dependency, resolution);
            const auto& _iterable_10 = result;
            for (const auto& existing : *_iterable_10) {
                if (::app_src_std_catalog_::canonicalDependencyUrl(existing->selectedUrl) != ::app_src_std_catalog_::canonicalDependencyUrl(selected->selectedUrl)) {
                    continue;
                }
                if (!sameSelectedExternal(existing, selected) && doof::is_null(resolution)) {
                    return doof::Failure<std::string>{ ((((((std::string("Conflicting external dependency ") + ::app_src_std_catalog_::canonicalDependencyUrl(dependency->url)) + std::string(" requested by ")) + existing->owner->logicalPrefix) + std::string(" and ")) + owner->logicalPrefix) + std::string("; add a root resolutions.externalDependencies entry")) };
                }
            }
            result->push_back(selected);
        }
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>>{ result };
}
doof::Result<void, std::string> validateDependencyPolicy(const std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>>& packages, const std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>& externals, const std::shared_ptr<::app_src_package_manifest_::PackageManifest>& rootManifest) {
    const auto policy = rootManifest->policy;
    const auto& _iterable_12 = packages;
    for (const auto& package : *_iterable_12) {
        if (package->sourceKind == std::string("root")) {
            continue;
        }
        if (((package->introducedBy != std::string("")) && (package->sourceKind == std::string("git"))) && policy->hasPackageSourceAllowlist) {
            if (doof::is_null(resolutionForUrl(rootManifest->packageResolutions, package->sourceUrl)) && !containsCanonicalUrl(policy->allowedPackageSources, package->sourceUrl)) {
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive package ") + package->sourceUrl) + std::string(" introduced by ")) + package->introducedBy) };
            }
        }
        auto _try_value_13 = validateTransitiveNativePolicy(package, policy);
        if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
    }
    const auto& _iterable_15 = externals;
    for (const auto& external : *_iterable_15) {
        if (external->owner->sourceKind == std::string("root")) {
            continue;
        }
        if ((rootManifest->policy->hasExternalSourceAllowlist && doof::is_null(resolutionForUrl(rootManifest->externalResolutions, external->selectedUrl))) && !containsCanonicalUrl(rootManifest->policy->allowedExternalSources, external->selectedUrl)) {
            return doof::Failure<std::string>{ (((std::string("Policy rejected transitive external dependency ") + ::app_src_std_catalog_::canonicalDependencyUrl(external->selectedUrl)) + std::string(" introduced by ")) + external->owner->logicalPrefix) };
        }
    }
    return doof::Success<void>{};
}
std::shared_ptr<ResolvedExternalInput> resolvedExternalInput(const std::shared_ptr<ReachedPackageInput>& owner, const std::shared_ptr<::app_src_package_manifest_::ExternalDependency>& dependency, const std::shared_ptr<::app_src_package_manifest_::DependencyResolution>& resolution) {
    if (doof::is_null(resolution)) {
        return std::make_shared<ResolvedExternalInput>(owner, dependency, dependency->kind, ::app_src_std_catalog_::canonicalDependencyUrl(dependency->url), dependency->ref, dependency->commit, dependency->sha256, false);
    }
    return std::make_shared<ResolvedExternalInput>(owner, dependency, resolution->kind, ::app_src_std_catalog_::canonicalDependencyUrl(resolution->url), resolution->ref, resolution->commit, resolution->sha256, ((((resolution->kind != dependency->kind) || (resolution->ref != dependency->ref)) || (resolution->commit != dependency->commit)) || (resolution->sha256 != dependency->sha256)));
}
bool sameSelectedExternal(const std::shared_ptr<ResolvedExternalInput>& left, const std::shared_ptr<ResolvedExternalInput>& right) {
    if (left->selectedKind != right->selectedKind) {
        return false;
    }
    if (left->selectedKind == std::string("git")) {
        return (left->selectedCommit == right->selectedCommit);
    }
    return (left->selectedSha256 == right->selectedSha256);
}
bool containsCanonicalUrl(const std::shared_ptr<std::vector<std::string>>& values, const std::string& value) {
    const auto canonical = ::app_src_std_catalog_::canonicalDependencyUrl(value);
    const auto& _iterable_17 = values;
    for (const auto& existing : *_iterable_17) {
        if (::app_src_std_catalog_::canonicalDependencyUrl(existing) == canonical) {
            return true;
        }
    }
    return false;
}
doof::Result<void, std::string> validateTransitiveNativePolicy(const std::shared_ptr<ReachedPackageInput>& package, const std::shared_ptr<::app_src_package_manifest_::DependencyPolicy>& policy) {
    if (policy->hasLinkLibraryAllowlist) {
        const auto& _iterable_19 = package->manifest->nativeBuild->linkLibraries;
        for (const auto& value : *_iterable_19) {
            if (!doof::array_contains(policy->allowedLinkLibraries, value, "", 0)) {
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive link library ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
    if (policy->hasFrameworkAllowlist) {
        const auto& _iterable_21 = package->manifest->nativeBuild->frameworks;
        for (const auto& value : *_iterable_21) {
            if (!doof::array_contains(policy->allowedFrameworks, value, "", 0)) {
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive framework ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
    if (policy->hasPkgConfigAllowlist) {
        const auto& _iterable_23 = package->manifest->nativeBuild->pkgConfigPackages;
        for (const auto& value : *_iterable_23) {
            if (!doof::array_contains(policy->allowedPkgConfigPackages, value, "", 0)) {
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive pkg-config package ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
    return doof::Success<void>{};
}
}
