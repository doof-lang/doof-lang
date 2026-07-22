#include "src_dependency_policy.hpp"
#include <cmath>
#include "src_package_manifest.hpp"
#include "src_std_catalog.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_dependency_policy_ {
using namespace ::app_src_package_manifest_;
using namespace ::app_src_std_catalog_;

doof::JsonObject ReachedPackageInput::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["logicalPrefix"] = doof::json_value(this->logicalPrefix);
    (*_json)["introducedBy"] = doof::json_value(this->introducedBy);
    (*_json)["manifest"] = doof::json_value(this->manifest->toJsonObject());
    (*_json)["sourceKind"] = doof::json_value(this->sourceKind);
    (*_json)["sourceUrl"] = doof::json_value(this->sourceUrl);
    (*_json)["sourceRef"] = doof::json_value(this->sourceRef);
    (*_json)["sourceCommit"] = doof::json_value(this->sourceCommit);
    (*_json)["requestedUrl"] = doof::json_value(this->requestedUrl);
    (*_json)["requestedRef"] = doof::json_value(this->requestedRef);
    (*_json)["requestedCommit"] = doof::json_value(this->requestedCommit);
    (*_json)["mutable"] = doof::json_value(this->mutable_);
    return _json;
}
doof::Result<std::shared_ptr<ReachedPackageInput>, std::string> ReachedPackageInput::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_logicalPrefix = _object->find("logicalPrefix");
    if (_iterator_logicalPrefix == _object->end()) { return doof::Failure<std::string>{"Missing required field \"logicalPrefix\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_logicalPrefix->second) : doof::json_is_string(_iterator_logicalPrefix->second)))) { return doof::Failure<std::string>{"Field \"logicalPrefix\" expected string but got " + std::string(doof::json_type_name(_iterator_logicalPrefix->second))}; }
    auto _field_logicalPrefix = (_lenient ? doof::json_as_string_lenient(_iterator_logicalPrefix->second) : doof::json_as_string(_iterator_logicalPrefix->second));
    auto _iterator_introducedBy = _object->find("introducedBy");
    if (_iterator_introducedBy == _object->end()) { return doof::Failure<std::string>{"Missing required field \"introducedBy\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_introducedBy->second) : doof::json_is_string(_iterator_introducedBy->second)))) { return doof::Failure<std::string>{"Field \"introducedBy\" expected string but got " + std::string(doof::json_type_name(_iterator_introducedBy->second))}; }
    auto _field_introducedBy = (_lenient ? doof::json_as_string_lenient(_iterator_introducedBy->second) : doof::json_as_string(_iterator_introducedBy->second));
    auto _iterator_manifest = _object->find("manifest");
    if (_iterator_manifest == _object->end()) { return doof::Failure<std::string>{"Missing required field \"manifest\""}; }
    if (!(doof::json_is_object(_iterator_manifest->second))) { return doof::Failure<std::string>{"Field \"manifest\" expected object but got " + std::string(doof::json_type_name(_iterator_manifest->second))}; }
    auto _field_manifest = doof::success_value(::app_src_package_manifest_::PackageManifest::fromJsonValue(_iterator_manifest->second, _lenient));
    auto _iterator_sourceKind = _object->find("sourceKind");
    if (_iterator_sourceKind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceKind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceKind->second) : doof::json_is_string(_iterator_sourceKind->second)))) { return doof::Failure<std::string>{"Field \"sourceKind\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceKind->second))}; }
    auto _field_sourceKind = (_lenient ? doof::json_as_string_lenient(_iterator_sourceKind->second) : doof::json_as_string(_iterator_sourceKind->second));
    std::optional<std::string> _field_sourceUrl;
    if (auto _iterator_sourceUrl = _object->find("sourceUrl"); _iterator_sourceUrl != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceUrl->second) : doof::json_is_string(_iterator_sourceUrl->second)))) { return doof::Failure<std::string>{"Field \"sourceUrl\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceUrl->second))}; }
        _field_sourceUrl = (_lenient ? doof::json_as_string_lenient(_iterator_sourceUrl->second) : doof::json_as_string(_iterator_sourceUrl->second));
    } else {
        _field_sourceUrl = std::string("");
    }
    std::optional<std::string> _field_sourceRef;
    if (auto _iterator_sourceRef = _object->find("sourceRef"); _iterator_sourceRef != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceRef->second) : doof::json_is_string(_iterator_sourceRef->second)))) { return doof::Failure<std::string>{"Field \"sourceRef\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceRef->second))}; }
        _field_sourceRef = (_lenient ? doof::json_as_string_lenient(_iterator_sourceRef->second) : doof::json_as_string(_iterator_sourceRef->second));
    } else {
        _field_sourceRef = std::string("");
    }
    std::optional<std::string> _field_sourceCommit;
    if (auto _iterator_sourceCommit = _object->find("sourceCommit"); _iterator_sourceCommit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourceCommit->second) : doof::json_is_string(_iterator_sourceCommit->second)))) { return doof::Failure<std::string>{"Field \"sourceCommit\" expected string but got " + std::string(doof::json_type_name(_iterator_sourceCommit->second))}; }
        _field_sourceCommit = (_lenient ? doof::json_as_string_lenient(_iterator_sourceCommit->second) : doof::json_as_string(_iterator_sourceCommit->second));
    } else {
        _field_sourceCommit = std::string("");
    }
    std::optional<std::string> _field_requestedUrl;
    if (auto _iterator_requestedUrl = _object->find("requestedUrl"); _iterator_requestedUrl != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedUrl->second) : doof::json_is_string(_iterator_requestedUrl->second)))) { return doof::Failure<std::string>{"Field \"requestedUrl\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedUrl->second))}; }
        _field_requestedUrl = (_lenient ? doof::json_as_string_lenient(_iterator_requestedUrl->second) : doof::json_as_string(_iterator_requestedUrl->second));
    } else {
        _field_requestedUrl = std::string("");
    }
    std::optional<std::string> _field_requestedRef;
    if (auto _iterator_requestedRef = _object->find("requestedRef"); _iterator_requestedRef != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedRef->second) : doof::json_is_string(_iterator_requestedRef->second)))) { return doof::Failure<std::string>{"Field \"requestedRef\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedRef->second))}; }
        _field_requestedRef = (_lenient ? doof::json_as_string_lenient(_iterator_requestedRef->second) : doof::json_as_string(_iterator_requestedRef->second));
    } else {
        _field_requestedRef = std::string("");
    }
    std::optional<std::string> _field_requestedCommit;
    if (auto _iterator_requestedCommit = _object->find("requestedCommit"); _iterator_requestedCommit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_requestedCommit->second) : doof::json_is_string(_iterator_requestedCommit->second)))) { return doof::Failure<std::string>{"Field \"requestedCommit\" expected string but got " + std::string(doof::json_type_name(_iterator_requestedCommit->second))}; }
        _field_requestedCommit = (_lenient ? doof::json_as_string_lenient(_iterator_requestedCommit->second) : doof::json_as_string(_iterator_requestedCommit->second));
    } else {
        _field_requestedCommit = std::string("");
    }
    std::optional<bool> _field_mutable_;
    if (auto _iterator_mutable_ = _object->find("mutable"); _iterator_mutable_ != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_mutable_->second) : doof::json_is_boolean(_iterator_mutable_->second)))) { return doof::Failure<std::string>{"Field \"mutable\" expected boolean but got " + std::string(doof::json_type_name(_iterator_mutable_->second))}; }
        _field_mutable_ = (_lenient ? doof::json_as_bool_lenient(_iterator_mutable_->second) : doof::json_as_bool(_iterator_mutable_->second));
    } else {
        _field_mutable_ = false;
    }
    return doof::Success<std::shared_ptr<ReachedPackageInput>>{std::make_shared<ReachedPackageInput>(_field_logicalPrefix, _field_introducedBy, _field_manifest, _field_sourceKind, _field_sourceUrl.value(), _field_sourceRef.value(), _field_sourceCommit.value(), _field_requestedUrl.value(), _field_requestedRef.value(), _field_requestedCommit.value(), _field_mutable_.value())};
}

doof::JsonObject ResolvedExternalInput::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["owner"] = doof::json_value(this->owner->toJsonObject());
    (*_json)["dependency"] = doof::json_value(this->dependency->toJsonObject());
    (*_json)["selectedKind"] = doof::json_value(this->selectedKind);
    (*_json)["selectedUrl"] = doof::json_value(this->selectedUrl);
    (*_json)["selectedRef"] = doof::json_value(this->selectedRef);
    (*_json)["selectedCommit"] = doof::json_value(this->selectedCommit);
    (*_json)["selectedSha256"] = doof::json_value(this->selectedSha256);
    (*_json)["overridden"] = doof::json_value(this->overridden);
    return _json;
}
doof::Result<std::shared_ptr<ResolvedExternalInput>, std::string> ResolvedExternalInput::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_owner = _object->find("owner");
    if (_iterator_owner == _object->end()) { return doof::Failure<std::string>{"Missing required field \"owner\""}; }
    if (!(doof::json_is_object(_iterator_owner->second))) { return doof::Failure<std::string>{"Field \"owner\" expected object but got " + std::string(doof::json_type_name(_iterator_owner->second))}; }
    auto _field_owner = doof::success_value(ReachedPackageInput::fromJsonValue(_iterator_owner->second, _lenient));
    auto _iterator_dependency = _object->find("dependency");
    if (_iterator_dependency == _object->end()) { return doof::Failure<std::string>{"Missing required field \"dependency\""}; }
    if (!(doof::json_is_object(_iterator_dependency->second))) { return doof::Failure<std::string>{"Field \"dependency\" expected object but got " + std::string(doof::json_type_name(_iterator_dependency->second))}; }
    auto _field_dependency = doof::success_value(::app_src_package_manifest_::ExternalDependency::fromJsonValue(_iterator_dependency->second, _lenient));
    auto _iterator_selectedKind = _object->find("selectedKind");
    if (_iterator_selectedKind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"selectedKind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_selectedKind->second) : doof::json_is_string(_iterator_selectedKind->second)))) { return doof::Failure<std::string>{"Field \"selectedKind\" expected string but got " + std::string(doof::json_type_name(_iterator_selectedKind->second))}; }
    auto _field_selectedKind = (_lenient ? doof::json_as_string_lenient(_iterator_selectedKind->second) : doof::json_as_string(_iterator_selectedKind->second));
    auto _iterator_selectedUrl = _object->find("selectedUrl");
    if (_iterator_selectedUrl == _object->end()) { return doof::Failure<std::string>{"Missing required field \"selectedUrl\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_selectedUrl->second) : doof::json_is_string(_iterator_selectedUrl->second)))) { return doof::Failure<std::string>{"Field \"selectedUrl\" expected string but got " + std::string(doof::json_type_name(_iterator_selectedUrl->second))}; }
    auto _field_selectedUrl = (_lenient ? doof::json_as_string_lenient(_iterator_selectedUrl->second) : doof::json_as_string(_iterator_selectedUrl->second));
    std::optional<std::string> _field_selectedRef;
    if (auto _iterator_selectedRef = _object->find("selectedRef"); _iterator_selectedRef != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_selectedRef->second) : doof::json_is_string(_iterator_selectedRef->second)))) { return doof::Failure<std::string>{"Field \"selectedRef\" expected string but got " + std::string(doof::json_type_name(_iterator_selectedRef->second))}; }
        _field_selectedRef = (_lenient ? doof::json_as_string_lenient(_iterator_selectedRef->second) : doof::json_as_string(_iterator_selectedRef->second));
    } else {
        _field_selectedRef = std::string("");
    }
    std::optional<std::string> _field_selectedCommit;
    if (auto _iterator_selectedCommit = _object->find("selectedCommit"); _iterator_selectedCommit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_selectedCommit->second) : doof::json_is_string(_iterator_selectedCommit->second)))) { return doof::Failure<std::string>{"Field \"selectedCommit\" expected string but got " + std::string(doof::json_type_name(_iterator_selectedCommit->second))}; }
        _field_selectedCommit = (_lenient ? doof::json_as_string_lenient(_iterator_selectedCommit->second) : doof::json_as_string(_iterator_selectedCommit->second));
    } else {
        _field_selectedCommit = std::string("");
    }
    std::optional<std::string> _field_selectedSha256;
    if (auto _iterator_selectedSha256 = _object->find("selectedSha256"); _iterator_selectedSha256 != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_selectedSha256->second) : doof::json_is_string(_iterator_selectedSha256->second)))) { return doof::Failure<std::string>{"Field \"selectedSha256\" expected string but got " + std::string(doof::json_type_name(_iterator_selectedSha256->second))}; }
        _field_selectedSha256 = (_lenient ? doof::json_as_string_lenient(_iterator_selectedSha256->second) : doof::json_as_string(_iterator_selectedSha256->second));
    } else {
        _field_selectedSha256 = std::string("");
    }
    std::optional<bool> _field_overridden;
    if (auto _iterator_overridden = _object->find("overridden"); _iterator_overridden != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_overridden->second) : doof::json_is_boolean(_iterator_overridden->second)))) { return doof::Failure<std::string>{"Field \"overridden\" expected boolean but got " + std::string(doof::json_type_name(_iterator_overridden->second))}; }
        _field_overridden = (_lenient ? doof::json_as_bool_lenient(_iterator_overridden->second) : doof::json_as_bool(_iterator_overridden->second));
    } else {
        _field_overridden = false;
    }
    return doof::Success<std::shared_ptr<ResolvedExternalInput>>{std::make_shared<ResolvedExternalInput>(_field_owner, _field_dependency, _field_selectedKind, _field_selectedUrl, _field_selectedRef.value(), _field_selectedCommit.value(), _field_selectedSha256.value(), _field_overridden.value())};
}
bool hasMutableStdPackageInputs(std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>> packages) {
    const auto& _iterable_1 = packages;
    for (const auto& package : *_iterable_1) {
        if (package->mutable_ && doof::string_startsWith(package->logicalPrefix, std::string("/std/"))) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<::app_src_package_manifest_::DependencyResolution> resolutionForUrl(std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>> resolutions, std::string url) {
    const auto canonical = ::app_src_std_catalog_::canonicalDependencyUrl(url);
    const auto& _iterable_2 = resolutions;
    for (const auto& resolution : *_iterable_2) {
        if (::app_src_std_catalog_::canonicalDependencyUrl(resolution->url) == canonical) {
            return resolution;
        }
    }
    return nullptr;
}
std::shared_ptr<::app_src_package_manifest_::PackageDependency> selectedPackageSource(std::shared_ptr<::app_src_package_manifest_::PackageDependency> dependency, std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>> resolutions) {
    if (dependency->url == std::string("")) {
        return dependency;
    }
    const auto resolution = resolutionForUrl(resolutions, dependency->url);
    if (doof::is_null(resolution)) {
        return dependency;
    }
    return std::make_shared<::app_src_package_manifest_::PackageDependency>(dependency->name, std::string(""), ::app_src_std_catalog_::canonicalDependencyUrl(resolution->url), resolution->ref, resolution->commit);
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>>, std::string> resolveExternalInputs(std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>> packages, std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest) {
    std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>> result = std::make_shared<std::vector<std::shared_ptr<ResolvedExternalInput>>>(std::vector<std::shared_ptr<ResolvedExternalInput>>{});
    const auto& _iterable_3 = packages;
    for (const auto& owner : *_iterable_3) {
        const auto& _iterable_4 = owner->manifest->externalDependencies;
        for (const auto& dependency : *_iterable_4) {
            const auto resolution = resolutionForUrl(rootManifest->externalResolutions, dependency->url);
            if ((!doof::is_null(resolution)) && (resolution->kind != dependency->kind)) {
                return doof::Failure<std::string>{ (((std::string("External resolution for ") + ::app_src_std_catalog_::canonicalDependencyUrl(dependency->url)) + std::string(" must keep kind ")) + dependency->kind) };
            }
            const auto selected = resolvedExternalInput(owner, dependency, resolution);
            const auto& _iterable_5 = result;
            for (const auto& existing : *_iterable_5) {
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
doof::Result<void, std::string> validateDependencyPolicy(std::shared_ptr<std::vector<std::shared_ptr<ReachedPackageInput>>> packages, std::shared_ptr<std::vector<std::shared_ptr<ResolvedExternalInput>>> externals, std::shared_ptr<::app_src_package_manifest_::PackageManifest> rootManifest) {
    const auto policy = rootManifest->policy;
    const auto& _iterable_6 = packages;
    for (const auto& package : *_iterable_6) {
        if (package->sourceKind == std::string("root")) {
            continue;
        }
        if (((package->introducedBy != std::string("")) && (package->sourceKind == std::string("git"))) && policy->hasPackageSourceAllowlist) {
            if (doof::is_null(resolutionForUrl(rootManifest->packageResolutions, package->sourceUrl)) && !containsCanonicalUrl(policy->allowedPackageSources, package->sourceUrl)) {
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive package ") + package->sourceUrl) + std::string(" introduced by ")) + package->introducedBy) };
            }
        }
        auto _try_value_7 = validateTransitiveNativePolicy(package, policy);
        if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::failure_error(_try_value_7)};
    }
    const auto& _iterable_8 = externals;
    for (const auto& external : *_iterable_8) {
        if (external->owner->sourceKind == std::string("root")) {
            continue;
        }
        if ((rootManifest->policy->hasExternalSourceAllowlist && doof::is_null(resolutionForUrl(rootManifest->externalResolutions, external->selectedUrl))) && !containsCanonicalUrl(rootManifest->policy->allowedExternalSources, external->selectedUrl)) {
            return doof::Failure<std::string>{ (((std::string("Policy rejected transitive external dependency ") + ::app_src_std_catalog_::canonicalDependencyUrl(external->selectedUrl)) + std::string(" introduced by ")) + external->owner->logicalPrefix) };
        }
    }
    return doof::Success<void>{};
}
std::shared_ptr<ResolvedExternalInput> resolvedExternalInput(std::shared_ptr<ReachedPackageInput> owner, std::shared_ptr<::app_src_package_manifest_::ExternalDependency> dependency, std::shared_ptr<::app_src_package_manifest_::DependencyResolution> resolution) {
    if (doof::is_null(resolution)) {
        return std::make_shared<ResolvedExternalInput>(owner, dependency, dependency->kind, ::app_src_std_catalog_::canonicalDependencyUrl(dependency->url), dependency->ref, dependency->commit, dependency->sha256, false);
    }
    return std::make_shared<ResolvedExternalInput>(owner, dependency, resolution->kind, ::app_src_std_catalog_::canonicalDependencyUrl(resolution->url), resolution->ref, resolution->commit, resolution->sha256, ((((resolution->kind != dependency->kind) || (resolution->ref != dependency->ref)) || (resolution->commit != dependency->commit)) || (resolution->sha256 != dependency->sha256)));
}
bool sameSelectedExternal(std::shared_ptr<ResolvedExternalInput> left, std::shared_ptr<ResolvedExternalInput> right) {
    if (left->selectedKind != right->selectedKind) {
        return false;
    }
    if (left->selectedKind == std::string("git")) {
        return (left->selectedCommit == right->selectedCommit);
    }
    return (left->selectedSha256 == right->selectedSha256);
}
bool containsCanonicalUrl(std::shared_ptr<std::vector<std::string>> values, std::string value) {
    const auto canonical = ::app_src_std_catalog_::canonicalDependencyUrl(value);
    const auto& _iterable_9 = values;
    for (const auto& existing : *_iterable_9) {
        if (::app_src_std_catalog_::canonicalDependencyUrl(existing) == canonical) {
            return true;
        }
    }
    return false;
}
doof::Result<void, std::string> validateTransitiveNativePolicy(std::shared_ptr<ReachedPackageInput> package, std::shared_ptr<::app_src_package_manifest_::DependencyPolicy> policy) {
    if (policy->hasLinkLibraryAllowlist) {
        const auto& _iterable_10 = package->manifest->nativeBuild->linkLibraries;
        for (const auto& value : *_iterable_10) {
            if (!doof::array_contains(policy->allowedLinkLibraries, value, "", 0)) {
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive link library ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
    if (policy->hasFrameworkAllowlist) {
        const auto& _iterable_11 = package->manifest->nativeBuild->frameworks;
        for (const auto& value : *_iterable_11) {
            if (!doof::array_contains(policy->allowedFrameworks, value, "", 0)) {
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive framework ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
    if (policy->hasPkgConfigAllowlist) {
        const auto& _iterable_12 = package->manifest->nativeBuild->pkgConfigPackages;
        for (const auto& value : *_iterable_12) {
            if (!doof::array_contains(policy->allowedPkgConfigPackages, value, "", 0)) {
                return doof::Failure<std::string>{ (((std::string("Policy rejected transitive pkg-config package ") + value) + std::string(" introduced by ")) + package->logicalPrefix) };
            }
        }
    }
    return doof::Success<void>{};
}
}
