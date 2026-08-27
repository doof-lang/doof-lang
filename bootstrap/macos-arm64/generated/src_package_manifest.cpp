#include "src_package_manifest.hpp"

namespace app_src_package_manifest_ {
using namespace ::std_::json::index;
using namespace ::std_::path::index;
using namespace ::app_src_macos_app_;
using namespace ::app_src_ios_app_;
std::string manifestJoinPath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
doof::JsonValue manifestJsonField(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
    return [&]() -> doof::JsonValue { auto _try_value = doof::map_get(object, name, "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/package-manifest", 13, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
}
bool manifestJsonHas(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
    return [&]() -> bool { auto _map_has_1 = object; return _map_has_1->find(name) != _map_has_1->end(); }();
}









doof::Result<std::shared_ptr<PackageManifest>, std::string> parsePackageManifest(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& targetOverride) {
    auto _try_value_2 = ::doof_json::parse(source);
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_2))};
    const auto parsed = doof::success_value(_try_value_2);
    auto _try_value_3 = manifestObject(parsed, manifestPath, std::string("root"));
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_3))};
    const auto root = doof::success_value(_try_value_3);
    auto name = std::string("");
    if (manifestJsonHas(root, std::string("name"))) {
        auto _try_value_4 = manifestString(manifestJsonField(root, std::string("name")), manifestPath, std::string("name"));
        if (doof::is_failure(_try_value_4)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_4))};
        const auto parsedName = doof::success_value(_try_value_4);
        (name = parsedName);
    }
    auto version = std::string("1.0");
    if (manifestJsonHas(root, std::string("version"))) {
        auto _try_value_5 = manifestString(manifestJsonField(root, std::string("version")), manifestPath, std::string("version"));
        if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_5))};
        const auto parsedVersion = doof::success_value(_try_value_5);
        (version = parsedVersion);
    }
    auto _try_value_6 = parseManifestResources(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
    const auto resources = doof::success_value(_try_value_6);
    auto _try_value_7 = parsePackageDependencies(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_7))};
    const auto dependencies = doof::success_value(_try_value_7);
    auto _try_value_8 = parseExternalDependencies(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
    const auto externalDependencies = doof::success_value(_try_value_8);
    auto _try_value_9 = parseResolutions(root, manifestPath, std::string("packages"));
    if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
    const auto packageResolutions = doof::success_value(_try_value_9);
    auto _try_value_10 = parseResolutions(root, manifestPath, std::string("externalDependencies"));
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_10))};
    const auto externalResolutions = doof::success_value(_try_value_10);
    auto _try_value_11 = parseDependencyPolicy(root, manifestPath);
    if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_11))};
    const auto policy = doof::success_value(_try_value_11);
    auto _try_value_12 = parseManifestTarget(root, manifestPath);
    if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
    const auto manifestTarget = doof::success_value(_try_value_12);
    const auto target = ((targetOverride == std::string("")) ? manifestTarget : targetOverride);
    auto _try_value_13 = parseManifestNativeBuild(root, manifestPath, rootDirectory, platform, target);
    if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
    const auto nativeBuild = doof::success_value(_try_value_13);
    auto _try_value_14 = parseMacOSApp(root, manifestPath, rootDirectory, name, version, target);
    if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
    const auto macosApp = doof::success_value(_try_value_14);
    auto _try_value_15 = parseIOSApp(root, manifestPath, rootDirectory, name, version, target);
    if (doof::is_failure(_try_value_15)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_15))};
    const auto iosApp = doof::success_value(_try_value_15);
    auto _try_value_16 = parseMacOSPackage(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_16))};
    const auto packageConfig = doof::success_value(_try_value_16);
    auto _try_value_17 = parseIOSPackage(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_17)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_17))};
    const auto iosPackageConfig = doof::success_value(_try_value_17);
    return doof::Success<std::shared_ptr<PackageManifest>>{ std::make_shared<PackageManifest>(name, version, manifestPath, rootDirectory, resources, dependencies, externalDependencies, packageResolutions, externalResolutions, policy, nativeBuild, target, macosApp, iosApp, packageConfig, iosPackageConfig) };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>, std::string> parsePackageDependencies(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
    if (!manifestJsonHas(root, std::string("dependencies"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>>{ std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{}) };
    }
    auto _try_value_18 = manifestObject(manifestJsonField(root, std::string("dependencies")), manifestPath, std::string("dependencies"));
    if (doof::is_failure(_try_value_18)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_18))};
    const auto values = doof::success_value(_try_value_18);
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> result = std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{});
    const auto& _iterable_20 = values;
    for (const auto& [name, value] : *_iterable_20) {
        const auto fieldPath = (std::string("dependencies.") + name);
        if (name == std::string("")) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": dependency names must not be empty")) };
        }
        auto _try_value_21 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_21))};
        const auto object = doof::success_value(_try_value_21);
        if (manifestJsonHas(object, std::string("path"))) {
            if ((manifestJsonHas(object, std::string("url")) || manifestJsonHas(object, std::string("ref"))) || manifestJsonHas(object, std::string("commit"))) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must declare either path or url/ref/commit")) };
            }
            auto _try_value_22 = requiredManifestString(object, std::string("path"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_22))};
            const auto path = doof::success_value(_try_value_22);
            result->push_back(std::make_shared<PackageDependency>(name, manifestJoinPath(rootDirectory, path), std::string(""), std::string(""), std::string("")));
            continue;
        }
        auto _try_value_23 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_23))};
        const auto url = doof::success_value(_try_value_23);
        auto _try_value_24 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_24)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_24))};
        const auto ref = doof::success_value(_try_value_24);
        auto _try_value_25 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_25))};
        const auto commit = doof::success_value(_try_value_25);
        if (!isHexString(commit, 40)) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".commit must be a 40-character hex string")) };
        }
        result->push_back(std::make_shared<PackageDependency>(name, std::string(""), url, ref, doof::string_toLowerCase(commit)));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>>{ result };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>, std::string> parseResolutions(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& section) {
    if (!manifestJsonHas(root, std::string("resolutions"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>>{ std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{}) };
    }
    auto _try_value_26 = manifestObject(manifestJsonField(root, std::string("resolutions")), manifestPath, std::string("resolutions"));
    if (doof::is_failure(_try_value_26)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_26))};
    const auto resolutions = doof::success_value(_try_value_26);
    if (!manifestJsonHas(resolutions, section)) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>>{ std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{}) };
    }
    const auto fieldRoot = (std::string("resolutions.") + section);
    auto _try_value_27 = manifestObject(manifestJsonField(resolutions, section), manifestPath, fieldRoot);
    if (doof::is_failure(_try_value_27)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_27))};
    const auto values = doof::success_value(_try_value_27);
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> result = std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{});
    const auto& _iterable_29 = values;
    for (const auto& [name, value] : *_iterable_29) {
        const auto fieldPath = ((fieldRoot + std::string(".")) + name);
        auto _try_value_30 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_30))};
        const auto object = doof::success_value(_try_value_30);
        auto kind = std::string("git");
        if (manifestJsonHas(object, std::string("kind"))) {
            auto _try_value_31 = manifestString(manifestJsonField(object, std::string("kind")), manifestPath, (fieldPath + std::string(".kind")));
            if (doof::is_failure(_try_value_31)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_31))};
            const auto parsedKind = doof::success_value(_try_value_31);
            (kind = parsedKind);
        }
        if ((section == std::string("packages")) && (kind != std::string("git"))) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".kind must be \"git\"")) };
        }
        auto _try_value_32 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_32)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_32))};
        const auto url = doof::success_value(_try_value_32);
        if (kind == std::string("git")) {
            auto _try_value_33 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_33))};
            const auto ref = doof::success_value(_try_value_33);
            auto _try_value_34 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_34)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_34))};
            const auto commit = doof::success_value(_try_value_34);
            if (!isHexString(commit, 40)) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".commit must be a 40-character hex string")) };
            }
            result->push_back(std::make_shared<DependencyResolution>(name, kind, url, ref, doof::string_toLowerCase(commit), std::string("")));
            continue;
        }
        if (kind == std::string("archive")) {
            auto _try_value_35 = requiredManifestString(object, std::string("sha256"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_35)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_35))};
            const auto sha256 = doof::success_value(_try_value_35);
            if (!isHexString(sha256, 64)) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".sha256 must be a 64-character hex string")) };
            }
            result->push_back(std::make_shared<DependencyResolution>(name, kind, url, std::string(""), std::string(""), doof::string_toLowerCase(sha256)));
            continue;
        }
        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".kind must be either \"archive\" or \"git\"")) };
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>>{ result };
}
doof::Result<std::shared_ptr<DependencyPolicy>, std::string> parseDependencyPolicy(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath) {
    const auto result = std::make_shared<DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    if (!manifestJsonHas(root, std::string("policy"))) {
        return doof::Success<std::shared_ptr<DependencyPolicy>>{ result };
    }
    auto _try_value_36 = manifestObject(manifestJsonField(root, std::string("policy")), manifestPath, std::string("policy"));
    if (doof::is_failure(_try_value_36)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_36))};
    const auto policy = doof::success_value(_try_value_36);
    if (manifestJsonHas(policy, std::string("allowedPackageSources"))) {
        (result->hasPackageSourceAllowlist = true);
        auto _try_value_37 = appendPolicyStrings(result->allowedPackageSources, policy, std::string("allowedPackageSources"), manifestPath, std::string("policy"));
        if (doof::is_failure(_try_value_37)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_37))};
    }
    if (manifestJsonHas(policy, std::string("allowedExternalSources"))) {
        (result->hasExternalSourceAllowlist = true);
        auto _try_value_38 = appendPolicyStrings(result->allowedExternalSources, policy, std::string("allowedExternalSources"), manifestPath, std::string("policy"));
        if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
    }
    if (manifestJsonHas(policy, std::string("native"))) {
        auto _try_value_39 = manifestObject(manifestJsonField(policy, std::string("native")), manifestPath, std::string("policy.native"));
        if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_39))};
        const auto native = doof::success_value(_try_value_39);
        if (manifestJsonHas(native, std::string("allowedLinkLibraries"))) {
            (result->hasLinkLibraryAllowlist = true);
            auto _try_value_40 = appendPolicyStrings(result->allowedLinkLibraries, native, std::string("allowedLinkLibraries"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_40)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_40))};
        }
        if (manifestJsonHas(native, std::string("allowedFrameworks"))) {
            (result->hasFrameworkAllowlist = true);
            auto _try_value_41 = appendPolicyStrings(result->allowedFrameworks, native, std::string("allowedFrameworks"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_41))};
        }
        if (manifestJsonHas(native, std::string("allowedPkgConfigPackages"))) {
            (result->hasPkgConfigAllowlist = true);
            auto _try_value_42 = appendPolicyStrings(result->allowedPkgConfigPackages, native, std::string("allowedPkgConfigPackages"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_42)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_42))};
        }
    }
    return doof::Success<std::shared_ptr<DependencyPolicy>>{ result };
}
doof::Result<void, std::string> appendPolicyStrings(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath) {
    auto _try_value_43 = manifestArray(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_43)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_43))};
    const auto values = doof::success_value(_try_value_43);
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        auto _try_value_45 = manifestString(doof::array_at(values, index, "src/package-manifest", 275), manifestPath, (((((fieldPath + std::string(".")) + name) + std::string("[")) + doof::to_string(index)) + std::string("]")));
        if (doof::is_failure(_try_value_45)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_45))};
        const auto value = doof::success_value(_try_value_45);
        if (value == std::string("")) {
            return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" entries must not be empty")) };
        }
        appendUnique(target, value);
    }
    return doof::Success<void>{};
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>, std::string> parseExternalDependencies(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
    if (!manifestJsonHas(root, std::string("externalDependencies"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(std::vector<std::shared_ptr<ExternalDependency>>{}) };
    }
    auto _try_value_46 = manifestObject(manifestJsonField(root, std::string("externalDependencies")), manifestPath, std::string("externalDependencies"));
    if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_46))};
    const auto values = doof::success_value(_try_value_46);
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(std::vector<std::shared_ptr<ExternalDependency>>{});
    const auto& _iterable_48 = values;
    for (const auto& [name, value] : *_iterable_48) {
        const auto fieldPath = (std::string("externalDependencies.") + name);
        if (((name == std::string("")) || doof::string_contains(name, std::string("/"))) || doof::string_contains(name, std::string("\\"))) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": invalid external dependency name \"")) + name) + std::string("\"")) };
        }
        auto _try_value_49 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_49)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_49))};
        const auto object = doof::success_value(_try_value_49);
        auto _try_value_50 = requiredManifestString(object, std::string("kind"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_50)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_50))};
        const auto kind = doof::success_value(_try_value_50);
        auto _try_value_51 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_51)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_51))};
        const auto url = doof::success_value(_try_value_51);
        auto _try_value_52 = requiredManifestString(object, std::string("destination"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_52)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_52))};
        const auto destination = doof::success_value(_try_value_52);
        const auto destinationPath = manifestJoinPath(rootDirectory, destination);
        if (!manifestPathWithinRoot(destinationPath, rootDirectory)) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".destination must stay within the package root")) };
        }
        auto _try_value_53 = parseExternalDependencyCommands(object, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_53)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_53))};
        const auto commands = doof::success_value(_try_value_53);
        if (kind == std::string("archive")) {
            auto _try_value_54 = requiredManifestString(object, std::string("sha256"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_54)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_54))};
            const auto sha256 = doof::success_value(_try_value_54);
            if (!isSupportedExternalArchiveUrl(url)) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".url must end with .zip, .tar.gz, .tgz, .tar.bz2, .tbz2, or .tar.xz")) };
            }
            if (!isHexString(sha256, 64)) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".sha256 must be a 64-character hex string")) };
            }
            auto stripComponents = 1;
            if (manifestJsonHas(object, std::string("stripComponents"))) {
                {
                    auto _case_subject = manifestJsonField(object, std::string("stripComponents"));
                    if (doof::json_is_number(_case_subject)) {
                        const auto number = doof::json_as_int(_case_subject);
                        if (number < 0) {
                            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".stripComponents must be a non-negative integer")) };
                        }
                        (stripComponents = number);
                }
                else if (doof::json_is_number(_case_subject)) {
                        const auto number = doof::json_as_double(_case_subject);
                        (stripComponents = static_cast<int32_t>(number));
                        if ((number < 0.0) || (static_cast<double>(stripComponents) != number)) {
                            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".stripComponents must be a non-negative integer")) };
                        }
                }
                else {
                        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".stripComponents must be a non-negative integer")) };
                }
                }
            }
            auto _try_value_55 = parseExternalDependencyCopyFiles(object, manifestPath, fieldPath);
            if (doof::is_failure(_try_value_55)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_55))};
            const auto copyFiles = doof::success_value(_try_value_55);
            result->push_back(std::make_shared<ExternalDependency>(name, kind, url, destination, doof::string_toLowerCase(sha256), stripComponents, copyFiles, std::string(""), std::string(""), commands));
            continue;
        }
        if (kind == std::string("git")) {
            auto _try_value_56 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_56)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_56))};
            const auto ref = doof::success_value(_try_value_56);
            auto _try_value_57 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_57)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_57))};
            const auto commit = doof::success_value(_try_value_57);
            if (!isHexString(commit, 40)) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".commit must be a 40-character hex string")) };
            }
            result->push_back(std::make_shared<ExternalDependency>(name, kind, url, destination, std::string(""), 1, std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{}), ref, doof::string_toLowerCase(commit), commands));
            continue;
        }
        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".kind must be either \"archive\" or \"git\"")) };
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>>{ result };
}
doof::Result<std::string, std::string> requiredManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath) {
    if (!manifestJsonHas(object, name)) {
        return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" is required")) };
    }
    auto _try_value_58 = manifestString(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_58)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_58))};
    const auto value = doof::success_value(_try_value_58);
    if (value == std::string("")) {
        return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" must not be empty")) };
    }
    return doof::Success<std::string>{ value };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>, std::string> parseExternalDependencyCopyFiles(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& manifestPath, const std::string& fieldPath) {
    if (!manifestJsonHas(object, std::string("copyFiles"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{}) };
    }
    auto _try_value_59 = manifestArray(manifestJsonField(object, std::string("copyFiles")), manifestPath, (fieldPath + std::string(".copyFiles")));
    if (doof::is_failure(_try_value_59)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_59))};
    const auto values = doof::success_value(_try_value_59);
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        const auto entryPath = (((fieldPath + std::string(".copyFiles[")) + doof::to_string(index)) + std::string("]"));
        auto _try_value_61 = manifestObject(doof::array_at(values, index, "src/package-manifest", 380), manifestPath, entryPath);
        if (doof::is_failure(_try_value_61)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_61))};
        const auto entry = doof::success_value(_try_value_61);
        auto _try_value_62 = requiredManifestString(entry, std::string("from"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_62))};
        const auto source = doof::success_value(_try_value_62);
        auto _try_value_63 = requiredManifestString(entry, std::string("to"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_63))};
        const auto destination = doof::success_value(_try_value_63);
        result->push_back(std::make_shared<ExternalDependencyCopyFile>(source, destination));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>>{ result };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>, std::string> parseExternalDependencyCommands(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& manifestPath, const std::string& fieldPath) {
    if (!manifestJsonHas(object, std::string("commands"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{}) };
    }
    auto _try_value_64 = manifestArray(manifestJsonField(object, std::string("commands")), manifestPath, (fieldPath + std::string(".commands")));
    if (doof::is_failure(_try_value_64)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_64))};
    const auto values = doof::success_value(_try_value_64);
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        const auto entryPath = (((fieldPath + std::string(".commands[")) + doof::to_string(index)) + std::string("]"));
        auto _try_value_66 = manifestObject(doof::array_at(values, index, "src/package-manifest", 398), manifestPath, entryPath);
        if (doof::is_failure(_try_value_66)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_66))};
        const auto entry = doof::success_value(_try_value_66);
        auto _try_value_67 = requiredManifestString(entry, std::string("program"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_67)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_67))};
        const auto program = doof::success_value(_try_value_67);
        std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        if (manifestJsonHas(entry, std::string("args"))) {
            auto _try_value_68 = manifestArray(manifestJsonField(entry, std::string("args")), manifestPath, (entryPath + std::string(".args")));
            if (doof::is_failure(_try_value_68)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_68))};
            const auto entries = doof::success_value(_try_value_68);
            for (int32_t argumentIndex = 0; argumentIndex < static_cast<int32_t>((entries)->size()); ++argumentIndex) {
                auto _try_value_70 = manifestString(doof::array_at(entries, argumentIndex, "src/package-manifest", 404), manifestPath, (((entryPath + std::string(".args[")) + doof::to_string(argumentIndex)) + std::string("]")));
                if (doof::is_failure(_try_value_70)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_70))};
                const auto argument = doof::success_value(_try_value_70);
                args->push_back(argument);
            }
        }
        std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
        if (manifestJsonHas(entry, std::string("env"))) {
            auto _try_value_71 = manifestObject(manifestJsonField(entry, std::string("env")), manifestPath, (entryPath + std::string(".env")));
            if (doof::is_failure(_try_value_71)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_71))};
            const auto entries = doof::success_value(_try_value_71);
            const auto& _iterable_73 = entries;
            for (const auto& [key, value] : *_iterable_73) {
                if (key == std::string("")) {
                    return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + entryPath) + std::string(".env keys must not be empty")) };
                }
                auto _try_value_74 = manifestString(value, manifestPath, ((entryPath + std::string(".env.")) + key));
                if (doof::is_failure(_try_value_74)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_74))};
                const auto text = doof::success_value(_try_value_74);
                doof::map_set(env, key, text, "", 0);
            }
        }
        auto workingDirectory = std::string("");
        if (manifestJsonHas(entry, std::string("workingDirectory"))) {
            auto _try_value_75 = manifestString(manifestJsonField(entry, std::string("workingDirectory")), manifestPath, (entryPath + std::string(".workingDirectory")));
            if (doof::is_failure(_try_value_75)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_75))};
            const auto parsed = doof::success_value(_try_value_75);
            if (parsed == std::string("")) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + entryPath) + std::string(".workingDirectory must not be empty")) };
            }
            (workingDirectory = parsed);
        }
        result->push_back(std::make_shared<ExternalDependencyCommand>(program, args, env, workingDirectory));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>>{ result };
}
bool isSupportedExternalArchiveUrl(const std::string& url) {
    const auto lower = doof::string_toLowerCase(url);
    return (((((doof::string_endsWith(lower, std::string(".zip")) || doof::string_endsWith(lower, std::string(".tar.gz"))) || doof::string_endsWith(lower, std::string(".tgz"))) || doof::string_endsWith(lower, std::string(".tar.bz2"))) || doof::string_endsWith(lower, std::string(".tbz2"))) || doof::string_endsWith(lower, std::string(".tar.xz")));
}
bool isHexString(const std::string& value, int32_t length) {
    if (static_cast<int32_t>(value.size()) != length) {
        return false;
    }
    const auto digits = std::string("0123456789abcdefABCDEF");
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
        if (!doof::string_contains(digits, doof::string_substring(value, index, (index + 1)))) {
            return false;
        }
    }
    return true;
}
std::shared_ptr<NativeBuildPlan> mergeNativeBuildPlans(const std::shared_ptr<std::vector<std::shared_ptr<NativeBuildPlan>>>& plans) {
    const auto merged = std::make_shared<NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto& _iterable_78 = plans;
    for (const auto& plan : *_iterable_78) {
        appendNativeBuild(merged, plan);
    }
    return merged;
}
doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> parseManifestNativeBuild(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& target) {
    const auto result = std::make_shared<NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    if (!manifestJsonHas(root, std::string("build"))) {
        return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
    }
    auto _try_value_79 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_79)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_79))};
    const auto build = doof::success_value(_try_value_79);
    if (!manifestJsonHas(build, std::string("native"))) {
        return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
    }
    auto _try_value_80 = manifestObject(manifestJsonField(build, std::string("native")), manifestPath, std::string("build.native"));
    if (doof::is_failure(_try_value_80)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_80))};
    const auto native = doof::success_value(_try_value_80);
    auto _try_value_81 = appendNativeFragment(result, native, manifestPath, rootDirectory, std::string("build.native"));
    if (doof::is_failure(_try_value_81)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_81))};
    const auto platformKey = ((target == std::string("wasm")) ? std::string("wasm") : ((platform == std::string("ios-simulator")) ? std::string("iosSimulator") : ((platform == std::string("ios-device")) ? std::string("iosDevice") : platform)));
    if ((platformKey != std::string("")) && manifestJsonHas(native, platformKey)) {
        auto _try_value_82 = manifestObject(manifestJsonField(native, platformKey), manifestPath, (std::string("build.native.") + platformKey));
        if (doof::is_failure(_try_value_82)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_82))};
        const auto platformValue = doof::success_value(_try_value_82);
        auto _try_value_83 = appendNativeFragment(result, platformValue, manifestPath, rootDirectory, (std::string("build.native.") + platformKey));
        if (doof::is_failure(_try_value_83)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_83))};
    }
    return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseManifestResources(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
    if (manifestJsonHas(root, std::string("resources"))) {
        return parseResourceArray(manifestJsonField(root, std::string("resources")), manifestPath, rootDirectory, std::string("resources"));
    }
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_84 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_84)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_84))};
        const auto build = doof::success_value(_try_value_84);
        if (manifestJsonHas(build, std::string("resources"))) {
            return parseResourceArray(manifestJsonField(build, std::string("resources")), manifestPath, rootDirectory, std::string("build.resources"));
        }
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>>{ std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{}) };
}
doof::Result<std::string, std::string> parseManifestTarget(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath) {
    if (manifestJsonHas(root, std::string("target"))) {
        return manifestString(manifestJsonField(root, std::string("target")), manifestPath, std::string("target"));
    }
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_85 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_85)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_85))};
        const auto build = doof::success_value(_try_value_85);
        if (manifestJsonHas(build, std::string("target"))) {
            return manifestString(manifestJsonField(build, std::string("target")), manifestPath, std::string("build.target"));
        }
    }
    return doof::Success<std::string>{ std::string("") };
}
doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>, std::string> parseMacOSApp(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& packageName, const std::string& packageVersion, const std::string& target) {
    if (target != std::string("macos-app")) {
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>>{ nullptr };
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> build = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_86 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_86)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_86))};
        const auto parsedBuild = doof::success_value(_try_value_86);
        (build = parsedBuild);
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> nested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(build, std::string("macosApp"))) {
        auto _try_value_87 = manifestObject(manifestJsonField(build, std::string("macosApp")), manifestPath, std::string("build.macosApp"));
        if (doof::is_failure(_try_value_87)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_87))};
        const auto parsedNested = doof::success_value(_try_value_87);
        (nested = parsedNested);
    }
    auto _try_value_88 = firstManifestString(root, std::string("executable"), build, std::string("executable"), build, std::string("targetExecutableName"), packageName, manifestPath, std::string("executable"));
    if (doof::is_failure(_try_value_88)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_88))};
    const auto executableName = doof::success_value(_try_value_88);
    if (((executableName == std::string("")) || doof::string_contains(executableName, std::string("/"))) || doof::string_contains(executableName, std::string("\\"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": executable must be a file name without path separators")) };
    }
    const auto defaultBundleId = (std::string("dev.doof.") + sanitizeBundleName(((packageName == std::string("")) ? executableName : packageName)));
    auto _try_value_89 = firstManifestString(root, std::string("id"), nested, std::string("bundleId"), build, std::string("id"), defaultBundleId, manifestPath, std::string("build.macosApp.bundleId"));
    if (doof::is_failure(_try_value_89)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_89))};
    const auto bundleId = doof::success_value(_try_value_89);
    auto _try_value_90 = firstManifestString(root, std::string("title"), nested, std::string("displayName"), build, std::string("title"), ((packageName == std::string("")) ? executableName : packageName), manifestPath, std::string("build.macosApp.displayName"));
    if (doof::is_failure(_try_value_90)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_90))};
    const auto displayName = doof::success_value(_try_value_90);
    auto _try_value_91 = optionalManifestString(nested, std::string("version"), packageVersion, manifestPath, std::string("build.macosApp.version"));
    if (doof::is_failure(_try_value_91)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_91))};
    const auto version = doof::success_value(_try_value_91);
    auto _try_value_92 = optionalManifestString(nested, std::string("category"), std::string("public.app-category.developer-tools"), manifestPath, std::string("build.macosApp.category"));
    if (doof::is_failure(_try_value_92)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_92))};
    const auto category = doof::success_value(_try_value_92);
    auto _try_value_93 = optionalManifestString(nested, std::string("minimumSystemVersion"), std::string("11.0"), manifestPath, std::string("build.macosApp.minimumSystemVersion"));
    if (doof::is_failure(_try_value_93)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_93))};
    const auto minimumSystemVersion = doof::success_value(_try_value_93);
    auto icon = std::string("");
    if (manifestJsonHas(root, std::string("icon"))) {
        auto _try_value_94 = manifestString(manifestJsonField(root, std::string("icon")), manifestPath, std::string("icon"));
        if (doof::is_failure(_try_value_94)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_94))};
        const auto parsed = doof::success_value(_try_value_94);
        (icon = parsed);
    } else if (manifestJsonHas(nested, std::string("icon"))) {
        auto _try_value_95 = manifestString(manifestJsonField(nested, std::string("icon")), manifestPath, std::string("build.macosApp.icon"));
        if (doof::is_failure(_try_value_95)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_95))};
        const auto parsed = doof::success_value(_try_value_95);
        (icon = parsed);
    } else if (manifestJsonHas(build, std::string("icon"))) {
        auto _try_value_96 = manifestString(manifestJsonField(build, std::string("icon")), manifestPath, std::string("build.icon"));
        if (doof::is_failure(_try_value_96)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_96))};
        const auto parsed = doof::success_value(_try_value_96);
        (icon = parsed);
    }
    auto iconPath = std::string("");
    if (icon != std::string("")) {
        if (!doof::string_endsWith(doof::string_toLowerCase(icon), std::string(".png"))) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.icon must point to a PNG file")) };
        }
        (iconPath = manifestJoinPath(rootDirectory, icon));
        if (!manifestPathWithinRoot(iconPath, rootDirectory)) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.icon must stay within the package root")) };
        }
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr;
    if (manifestJsonHas(nested, std::string("infoPlist"))) {
        auto _try_value_97 = manifestObject(manifestJsonField(nested, std::string("infoPlist")), manifestPath, std::string("build.macosApp.infoPlist"));
        if (doof::is_failure(_try_value_97)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_97))};
        const auto parsedInfo = doof::success_value(_try_value_97);
        const auto& _iterable_99 = parsedInfo;
        for (const auto& [key, ignored] : *_iterable_99) {
            if (isManagedMacOSPlistKey(key)) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.infoPlist.")) + key) + std::string(" conflicts with a Doof-managed Info.plist key")) };
            }
        }
        (infoPlist = parsedInfo);
    }
    std::variant<std::monostate, doof::JsonValue> resourceValue = std::monostate{};
    auto resourceField = std::string("build.macosApp.resources");
    if (manifestJsonHas(root, std::string("resources"))) {
        (resourceValue = manifestJsonField(root, std::string("resources")));
        (resourceField = std::string("resources"));
    } else if (manifestJsonHas(nested, std::string("resources"))) {
        (resourceValue = manifestJsonField(nested, std::string("resources")));
    } else if (manifestJsonHas(build, std::string("resources"))) {
        (resourceValue = manifestJsonField(build, std::string("resources")));
        (resourceField = std::string("build.resources"));
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSAppResource>>>(std::vector<std::shared_ptr<::app_src_macos_app_::MacOSAppResource>>{});
    if (!doof::is_null(resourceValue)) {
        auto _try_value_100 = parseResourceArray(std::get<doof::JsonValue>(resourceValue), manifestPath, rootDirectory, resourceField);
        if (doof::is_failure(_try_value_100)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_100))};
        const auto parsedResources = doof::success_value(_try_value_100);
        const auto& _iterable_102 = parsedResources;
        for (const auto& resource : *_iterable_102) {
            resources->push_back(std::make_shared<::app_src_macos_app_::MacOSAppResource>(resource->sourcePath, resource->destination));
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>{});
    if (manifestJsonHas(nested, std::string("embeddedLibraries"))) {
        auto _try_value_103 = manifestArray(manifestJsonField(nested, std::string("embeddedLibraries")), manifestPath, std::string("build.macosApp.embeddedLibraries"));
        if (doof::is_failure(_try_value_103)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_103))};
        const auto entries = doof::success_value(_try_value_103);
        for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
            auto _try_value_105 = manifestObject(doof::array_at(entries, index, "src/package-manifest", 601), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("]")));
            if (doof::is_failure(_try_value_105)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_105))};
            const auto entry = doof::success_value(_try_value_105);
            const auto hasLibrary = manifestJsonHas(entry, std::string("library"));
            const auto hasPath = manifestJsonHas(entry, std::string("path"));
            if (hasLibrary == hasPath) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.embeddedLibraries[")) + doof::to_string(index)) + std::string("] requires exactly one of library or path")) };
            }
            if (hasLibrary) {
                auto _try_value_106 = manifestString(manifestJsonField(entry, std::string("library")), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("].library")));
                if (doof::is_failure(_try_value_106)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_106))};
                const auto library = doof::success_value(_try_value_106);
                if (((library == std::string("")) || doof::string_contains(library, std::string("/"))) || doof::string_contains(library, std::string("\\"))) {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded linked library names must not contain path separators")) };
                }
                embeddedLibraries->push_back(std::make_shared<::app_src_macos_app_::MacOSEmbeddedLibrary>(library, std::string("")));
            } else {
                auto _try_value_107 = manifestString(manifestJsonField(entry, std::string("path")), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("].path")));
                if (doof::is_failure(_try_value_107)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_107))};
                const auto path = doof::success_value(_try_value_107);
                const auto resolvedPath = manifestJoinPath(rootDirectory, path);
                if (!manifestPathWithinRoot(resolvedPath, rootDirectory)) {
                    return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.embeddedLibraries[")) + doof::to_string(index)) + std::string("].path must stay within the package root")) };
                }
                if ((!doof::string_endsWith(resolvedPath, std::string(".dylib")) && !doof::string_endsWith(resolvedPath, std::string(".so"))) && !doof::string_endsWith(resolvedPath, std::string(".framework"))) {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded library paths must be .dylib, .so, or .framework")) };
                }
                embeddedLibraries->push_back(std::make_shared<::app_src_macos_app_::MacOSEmbeddedLibrary>(std::string(""), resolvedPath));
            }
        }
    }
    return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>>{ std::make_shared<::app_src_macos_app_::MacOSAppConfig>(executableName, bundleId, displayName, version, iconPath, infoPlist, resources, embeddedLibraries, category, minimumSystemVersion) };
}
doof::Result<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>, std::string> parseIOSApp(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& packageName, const std::string& packageVersion, const std::string& target) {
    if (target != std::string("ios-app")) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>>{ nullptr };
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> build = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_108 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_108)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_108))};
        const auto parsedBuild = doof::success_value(_try_value_108);
        (build = parsedBuild);
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> nested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(build, std::string("iosApp"))) {
        auto _try_value_109 = manifestObject(manifestJsonField(build, std::string("iosApp")), manifestPath, std::string("build.iosApp"));
        if (doof::is_failure(_try_value_109)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_109))};
        const auto parsedNested = doof::success_value(_try_value_109);
        (nested = parsedNested);
    }
    auto _try_value_110 = firstManifestString(root, std::string("executable"), build, std::string("executable"), build, std::string("targetExecutableName"), packageName, manifestPath, std::string("executable"));
    if (doof::is_failure(_try_value_110)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_110))};
    const auto executableName = doof::success_value(_try_value_110);
    if (((executableName == std::string("")) || doof::string_contains(executableName, std::string("/"))) || doof::string_contains(executableName, std::string("\\"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": executable must be a file name without path separators")) };
    }
    const auto defaultBundleId = (std::string("dev.doof.") + sanitizeBundleName(((packageName == std::string("")) ? executableName : packageName)));
    auto _try_value_111 = firstManifestString(root, std::string("id"), nested, std::string("bundleId"), build, std::string("id"), defaultBundleId, manifestPath, std::string("build.iosApp.bundleId"));
    if (doof::is_failure(_try_value_111)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_111))};
    const auto bundleId = doof::success_value(_try_value_111);
    auto _try_value_112 = firstManifestString(root, std::string("title"), nested, std::string("displayName"), build, std::string("title"), ((packageName == std::string("")) ? executableName : packageName), manifestPath, std::string("build.iosApp.displayName"));
    if (doof::is_failure(_try_value_112)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_112))};
    const auto displayName = doof::success_value(_try_value_112);
    auto _try_value_113 = optionalManifestString(nested, std::string("version"), packageVersion, manifestPath, std::string("build.iosApp.version"));
    if (doof::is_failure(_try_value_113)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_113))};
    const auto version = doof::success_value(_try_value_113);
    auto _try_value_114 = optionalManifestString(nested, std::string("minimumDeploymentTarget"), std::string("16.0"), manifestPath, std::string("build.iosApp.minimumDeploymentTarget"));
    if (doof::is_failure(_try_value_114)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_114))};
    const auto minimumDeploymentTarget = doof::success_value(_try_value_114);
    auto icon = std::string("");
    if (manifestJsonHas(root, std::string("icon"))) {
        auto _try_value_115 = manifestString(manifestJsonField(root, std::string("icon")), manifestPath, std::string("icon"));
        if (doof::is_failure(_try_value_115)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_115))};
        const auto parsed = doof::success_value(_try_value_115);
        (icon = parsed);
    } else if (manifestJsonHas(nested, std::string("icon"))) {
        auto _try_value_116 = manifestString(manifestJsonField(nested, std::string("icon")), manifestPath, std::string("build.iosApp.icon"));
        if (doof::is_failure(_try_value_116)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_116))};
        const auto parsed = doof::success_value(_try_value_116);
        (icon = parsed);
    } else if (manifestJsonHas(build, std::string("icon"))) {
        auto _try_value_117 = manifestString(manifestJsonField(build, std::string("icon")), manifestPath, std::string("build.icon"));
        if (doof::is_failure(_try_value_117)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_117))};
        const auto parsed = doof::success_value(_try_value_117);
        (icon = parsed);
    }
    auto iconPath = std::string("");
    if (icon != std::string("")) {
        if (!doof::string_endsWith(doof::string_toLowerCase(icon), std::string(".png"))) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.iosApp.icon must point to a PNG file")) };
        }
        (iconPath = manifestJoinPath(rootDirectory, icon));
        if (!manifestPathWithinRoot(iconPath, rootDirectory)) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.iosApp.icon must stay within the package root")) };
        }
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr;
    if (manifestJsonHas(nested, std::string("infoPlist"))) {
        auto _try_value_118 = manifestObject(manifestJsonField(nested, std::string("infoPlist")), manifestPath, std::string("build.iosApp.infoPlist"));
        if (doof::is_failure(_try_value_118)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_118))};
        const auto parsedInfo = doof::success_value(_try_value_118);
        const auto& _iterable_120 = parsedInfo;
        for (const auto& [key, ignored] : *_iterable_120) {
            if (isManagedIOSPlistKey(key)) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.iosApp.infoPlist.")) + key) + std::string(" conflicts with a Doof-managed Info.plist key")) };
            }
        }
        (infoPlist = parsedInfo);
    }
    std::variant<std::monostate, doof::JsonValue> resourceValue = std::monostate{};
    auto resourceField = std::string("build.iosApp.resources");
    if (manifestJsonHas(root, std::string("resources"))) {
        (resourceValue = manifestJsonField(root, std::string("resources")));
        (resourceField = std::string("resources"));
    } else if (manifestJsonHas(nested, std::string("resources"))) {
        (resourceValue = manifestJsonField(nested, std::string("resources")));
    } else if (manifestJsonHas(build, std::string("resources"))) {
        (resourceValue = manifestJsonField(build, std::string("resources")));
        (resourceField = std::string("build.resources"));
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ios_app_::IOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<::app_src_ios_app_::IOSAppResource>>>(std::vector<std::shared_ptr<::app_src_ios_app_::IOSAppResource>>{});
    if (!doof::is_null(resourceValue)) {
        auto _try_value_121 = parseResourceArray(std::get<doof::JsonValue>(resourceValue), manifestPath, rootDirectory, resourceField);
        if (doof::is_failure(_try_value_121)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_121))};
        const auto parsedResources = doof::success_value(_try_value_121);
        const auto& _iterable_123 = parsedResources;
        for (const auto& resource : *_iterable_123) {
            resources->push_back(std::make_shared<::app_src_ios_app_::IOSAppResource>(resource->sourcePath, resource->destination));
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>{});
    if (manifestJsonHas(nested, std::string("embeddedLibraries"))) {
        auto _try_value_124 = manifestArray(manifestJsonField(nested, std::string("embeddedLibraries")), manifestPath, std::string("build.iosApp.embeddedLibraries"));
        if (doof::is_failure(_try_value_124)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_124))};
        const auto entries = doof::success_value(_try_value_124);
        for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
            const auto field = ((std::string("build.iosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("]"));
            auto _try_value_126 = manifestObject(doof::array_at(entries, index, "src/package-manifest", 723), manifestPath, field);
            if (doof::is_failure(_try_value_126)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_126))};
            const auto entry = doof::success_value(_try_value_126);
            const auto hasLibrary = manifestJsonHas(entry, std::string("library"));
            const auto hasPath = manifestJsonHas(entry, std::string("path"));
            if (hasLibrary == hasPath) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + field) + std::string(" requires exactly one of library or path")) };
            }
            if (hasLibrary) {
                auto _try_value_127 = manifestString(manifestJsonField(entry, std::string("library")), manifestPath, (field + std::string(".library")));
                if (doof::is_failure(_try_value_127)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_127))};
                const auto library = doof::success_value(_try_value_127);
                if (((library == std::string("")) || doof::string_contains(library, std::string("/"))) || doof::string_contains(library, std::string("\\"))) {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded linked library names must not contain path separators")) };
                }
                embeddedLibraries->push_back(std::make_shared<::app_src_ios_app_::IOSEmbeddedLibrary>(library, std::string("")));
            } else {
                auto _try_value_128 = manifestString(manifestJsonField(entry, std::string("path")), manifestPath, (field + std::string(".path")));
                if (doof::is_failure(_try_value_128)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_128))};
                const auto path = doof::success_value(_try_value_128);
                const auto resolvedPath = manifestJoinPath(rootDirectory, path);
                if (!manifestPathWithinRoot(resolvedPath, rootDirectory)) {
                    return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + field) + std::string(".path must stay within the package root")) };
                }
                if ((!doof::string_endsWith(resolvedPath, std::string(".dylib")) && !doof::string_endsWith(resolvedPath, std::string(".so"))) && !doof::string_endsWith(resolvedPath, std::string(".framework"))) {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded library paths must be .dylib, .so, or .framework")) };
                }
                embeddedLibraries->push_back(std::make_shared<::app_src_ios_app_::IOSEmbeddedLibrary>(std::string(""), resolvedPath));
            }
        }
    }
    return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>>{ std::make_shared<::app_src_ios_app_::IOSAppConfig>(executableName, bundleId, displayName, version, iconPath, infoPlist, resources, embeddedLibraries, minimumDeploymentTarget) };
}
doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>, std::string> parseMacOSPackage(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
    auto distDirectory = manifestJoinPath(rootDirectory, std::string("dist"));
    auto signing = std::string("developer-id");
    auto identity = std::string("");
    auto sandbox = false;
    auto entitlementsPath = std::string("");
    if (!manifestJsonHas(root, std::string("build"))) {
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
    }
    auto _try_value_129 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_129)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_129))};
    const auto build = doof::success_value(_try_value_129);
    if (!manifestJsonHas(build, std::string("package"))) {
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
    }
    auto _try_value_130 = manifestObject(manifestJsonField(build, std::string("package")), manifestPath, std::string("build.package"));
    if (doof::is_failure(_try_value_130)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_130))};
    const auto package = doof::success_value(_try_value_130);
    if (manifestJsonHas(package, std::string("distDir"))) {
        auto _try_value_131 = manifestString(manifestJsonField(package, std::string("distDir")), manifestPath, std::string("build.package.distDir"));
        if (doof::is_failure(_try_value_131)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_131))};
        const auto value = doof::success_value(_try_value_131);
        (distDirectory = manifestJoinPath(rootDirectory, value));
        if (!manifestPathWithinRoot(distDirectory, rootDirectory)) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.distDir must stay within the package root")) };
        }
    }
    if (manifestJsonHas(package, std::string("macos"))) {
        auto _try_value_132 = manifestObject(manifestJsonField(package, std::string("macos")), manifestPath, std::string("build.package.macos"));
        if (doof::is_failure(_try_value_132)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_132))};
        const auto macos = doof::success_value(_try_value_132);
        if (manifestJsonHas(macos, std::string("signing"))) {
            auto _try_value_133 = manifestString(manifestJsonField(macos, std::string("signing")), manifestPath, std::string("build.package.macos.signing"));
            if (doof::is_failure(_try_value_133)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_133))};
            const auto value = doof::success_value(_try_value_133);
            if ((value != std::string("developer-id")) && (value != std::string("ad-hoc"))) {
                return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.signing must be one of \"developer-id\", \"ad-hoc\"")) };
            }
            (signing = value);
        }
        if (manifestJsonHas(macos, std::string("identity"))) {
            auto _try_value_134 = manifestString(manifestJsonField(macos, std::string("identity")), manifestPath, std::string("build.package.macos.identity"));
            if (doof::is_failure(_try_value_134)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_134))};
            const auto value = doof::success_value(_try_value_134);
            (identity = value);
        }
        if (manifestJsonHas(macos, std::string("sandbox"))) {
            {
                auto _case_subject = manifestJsonField(macos, std::string("sandbox"));
                if (doof::json_is_boolean(_case_subject)) {
                    const auto value = doof::json_as_bool(_case_subject);
                    (sandbox = value);
            }
            else {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.sandbox must be a boolean")) };
            }
            }
        }
        if (manifestJsonHas(macos, std::string("entitlements"))) {
            auto _try_value_135 = manifestString(manifestJsonField(macos, std::string("entitlements")), manifestPath, std::string("build.package.macos.entitlements"));
            if (doof::is_failure(_try_value_135)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_135))};
            const auto value = doof::success_value(_try_value_135);
            (entitlementsPath = manifestJoinPath(rootDirectory, value));
            if (!manifestPathWithinRoot(entitlementsPath, rootDirectory)) {
                return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.entitlements must stay within the package root")) };
            }
        }
    }
    return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
}
doof::Result<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>, std::string> parseIOSPackage(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
    auto identity = std::string("");
    auto provisioningProfilePath = std::string("");
    if (!manifestJsonHas(root, std::string("build"))) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
    auto _try_value_136 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_136)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_136))};
    const auto build = doof::success_value(_try_value_136);
    if (!manifestJsonHas(build, std::string("package"))) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
    auto _try_value_137 = manifestObject(manifestJsonField(build, std::string("package")), manifestPath, std::string("build.package"));
    if (doof::is_failure(_try_value_137)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_137))};
    const auto package = doof::success_value(_try_value_137);
    if (!manifestJsonHas(package, std::string("ios"))) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
    auto _try_value_138 = manifestObject(manifestJsonField(package, std::string("ios")), manifestPath, std::string("build.package.ios"));
    if (doof::is_failure(_try_value_138)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_138))};
    const auto ios = doof::success_value(_try_value_138);
    if (manifestJsonHas(ios, std::string("identity"))) {
        auto _try_value_139 = manifestString(manifestJsonField(ios, std::string("identity")), manifestPath, std::string("build.package.ios.identity"));
        if (doof::is_failure(_try_value_139)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_139))};
        const auto value = doof::success_value(_try_value_139);
        (identity = value);
    }
    if (manifestJsonHas(ios, std::string("provisioningProfile"))) {
        auto _try_value_140 = manifestString(manifestJsonField(ios, std::string("provisioningProfile")), manifestPath, std::string("build.package.ios.provisioningProfile"));
        if (doof::is_failure(_try_value_140)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_140))};
        const auto value = doof::success_value(_try_value_140);
        (provisioningProfilePath = manifestJoinPath(rootDirectory, value));
        if (!manifestPathWithinRoot(provisioningProfilePath, rootDirectory)) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.ios.provisioningProfile must stay within the package root")) };
        }
    }
    return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(identity, provisioningProfilePath) };
}
doof::Result<std::string, std::string> optionalManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& key, const std::string& fallback, const std::string& manifestPath, const std::string& fieldPath) {
    if (!manifestJsonHas(object, key)) {
        return doof::Success<std::string>{ fallback };
    }
    return manifestString(manifestJsonField(object, key), manifestPath, fieldPath);
}
doof::Result<std::string, std::string> firstManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& first, const std::string& firstKey, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& second, const std::string& secondKey, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& third, const std::string& thirdKey, const std::string& fallback, const std::string& manifestPath, const std::string& fieldPath) {
    if (manifestJsonHas(first, firstKey)) {
        return manifestString(manifestJsonField(first, firstKey), manifestPath, firstKey);
    }
    if (manifestJsonHas(second, secondKey)) {
        return manifestString(manifestJsonField(second, secondKey), manifestPath, fieldPath);
    }
    if (manifestJsonHas(third, thirdKey)) {
        return manifestString(manifestJsonField(third, thirdKey), manifestPath, thirdKey);
    }
    return doof::Success<std::string>{ fallback };
}
std::string sanitizeBundleName(const std::string& value) {
    const auto allowed = std::string("abcdefghijklmnopqrstuvwxyz0123456789-");
    auto result = std::string("");
    const auto lower = doof::string_toLowerCase(value);
    for (int32_t index = 0; index < static_cast<int32_t>(lower.size()); ++index) {
        const auto text = doof::string_substring(lower, index, (index + 1));
        (result = (result + (doof::string_contains(allowed, text) ? text : std::string("-"))));
    }
    while (doof::string_startsWith(result, std::string("-"))) {
        (result = doof::string_substring(result, 1, static_cast<int32_t>(result.size())));
    }
    while (doof::string_endsWith(result, std::string("-"))) {
        (result = doof::string_substring(result, 0, (static_cast<int32_t>(result.size()) - 1)));
    }
    return ((result == std::string("")) ? std::string("app") : result);
}
bool manifestPathWithinRoot(const std::string& path, const std::string& rootDirectory) {
    const auto boundary = (doof::string_endsWith(rootDirectory, std::string("/")) ? rootDirectory : (rootDirectory + std::string("/")));
    return ((path == rootDirectory) || doof::string_startsWith(path, boundary));
}
bool isManagedMacOSPlistKey(const std::string& key) {
    const auto keys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("CFBundleDevelopmentRegion"), std::string("CFBundleDisplayName"), std::string("CFBundleExecutable"), std::string("CFBundleIconFile"), std::string("CFBundleIdentifier"), std::string("CFBundleInfoDictionaryVersion"), std::string("CFBundleName"), std::string("CFBundlePackageType"), std::string("CFBundleShortVersionString"), std::string("CFBundleVersion"), std::string("LSApplicationCategoryType"), std::string("LSMinimumSystemVersion"), std::string("NSHighResolutionCapable"), std::string("NSPrincipalClass")});
    return doof::array_contains(keys, key, "", 0);
}
bool isManagedIOSPlistKey(const std::string& key) {
    const auto keys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("CFBundleDevelopmentRegion"), std::string("CFBundleDisplayName"), std::string("CFBundleExecutable"), std::string("CFBundleIdentifier"), std::string("CFBundleInfoDictionaryVersion"), std::string("CFBundleName"), std::string("CFBundlePackageType"), std::string("CFBundleShortVersionString"), std::string("CFBundleVersion"), std::string("LSRequiresIPhoneOS"), std::string("MinimumOSVersion"), std::string("UIDeviceFamily"), std::string("UILaunchStoryboardName"), std::string("UIApplicationSceneManifest")});
    return doof::array_contains(keys, key, "", 0);
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseResourceArray(const doof::JsonValue& value, const std::string& manifestPath, const std::string& rootDirectory, const std::string& fieldPath) {
    auto _try_value_142 = manifestArray(value, manifestPath, fieldPath);
    if (doof::is_failure(_try_value_142)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_142))};
    const auto entries = doof::success_value(_try_value_142);
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources = std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
        auto source = std::string("");
        auto destination = std::string("");
        {
            auto _case_subject = doof::array_at(entries, index, "src/package-manifest", 895);
            if (doof::json_is_string(_case_subject)) {
                const auto text = doof::json_as_string(_case_subject);
                if (text == std::string("")) {
                    return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string("[")) + doof::to_string(index)) + std::string("] must not be empty")) };
                }
                (source = text);
                (destination = text);
        }
        else if (doof::json_is_object(_case_subject)) {
                const auto object = doof::json_object(_case_subject);
                if (!manifestJsonHas(object, std::string("from")) || !manifestJsonHas(object, std::string("to"))) {
                    return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string("[")) + doof::to_string(index)) + std::string("] requires string fields from and to")) };
                }
                auto _try_value_144 = manifestString(manifestJsonField(object, std::string("from")), manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].from")));
                if (doof::is_failure(_try_value_144)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_144))};
                const auto parsedSource = doof::success_value(_try_value_144);
                auto _try_value_145 = manifestString(manifestJsonField(object, std::string("to")), manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].to")));
                if (doof::is_failure(_try_value_145)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_145))};
                const auto parsedDestination = doof::success_value(_try_value_145);
                (source = parsedSource);
                (destination = parsedDestination);
        }
        else {
                return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string("[")) + doof::to_string(index)) + std::string("] must be a string or object")) };
        }
        }
        const auto sourcePath = manifestJoinPath(rootDirectory, source);
        const auto rootBoundary = (doof::string_endsWith(rootDirectory, std::string("/")) ? rootDirectory : (rootDirectory + std::string("/")));
        if ((sourcePath != rootDirectory) && !doof::string_startsWith(sourcePath, rootBoundary)) {
            return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string("[")) + doof::to_string(index)) + std::string("].from must stay within the package root")) };
        }
        auto _try_value_146 = normalizeResourceDestination(destination, manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].to")));
        if (doof::is_failure(_try_value_146)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_146))};
        const auto normalizedDestination = doof::success_value(_try_value_146);
        resources->push_back(std::make_shared<PackageResource>(sourcePath, normalizedDestination));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>>{ resources };
}
doof::Result<std::string, std::string> normalizeResourceDestination(const std::string& destination, const std::string& manifestPath, const std::string& fieldPath) {
    const auto portable = doof::string_replaceAll(destination, std::string("\\"), std::string("/"));
    if (doof::string_startsWith(portable, std::string("/")) || (((static_cast<int32_t>(portable.size()) >= 3) && (doof::string_at(portable, 1, "src/package-manifest", 944) == U'\u003A')) && (doof::string_at(portable, 2, "src/package-manifest", 944) == U'\u002F'))) {
        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be relative")) };
    }
    std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_148 = doof::string_split(portable, std::string("/"));
    for (const auto& segment : *_iterable_148) {
        if ((segment == std::string("")) || (segment == std::string("."))) {
            continue;
        }
        if (segment == std::string("..")) {
            if (static_cast<int32_t>((segments)->size()) == 0) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must stay within the executable resource directory")) };
            }
            const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(segments); if (doof::is_failure(_try_value)) doof::panic_at("src/package-manifest", 955, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
            continue;
        }
        segments->push_back(segment);
    }
    auto normalized = std::string("");
    const auto& _iterable_150 = segments;
    for (const auto& segment : *_iterable_150) {
        if (normalized != std::string("")) {
            (normalized = (normalized + std::string("/")));
        }
        (normalized = (normalized + segment));
    }
    return doof::Success<std::string>{ normalized };
}
doof::Result<void, std::string> appendNativeFragment(const std::shared_ptr<NativeBuildPlan>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& fragment, const std::string& manifestPath, const std::string& rootDirectory, const std::string& fieldPath) {
    auto _try_value_151 = appendStringArrayField(target->includePaths, fragment, std::string("includePaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_151)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_151))};
    auto _try_value_152 = appendStringArrayField(target->sourceFiles, fragment, std::string("sourceFiles"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_152)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_152))};
    auto _try_value_153 = appendStringArrayField(target->libraryPaths, fragment, std::string("libraryPaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_153)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_153))};
    auto _try_value_154 = appendStringArrayField(target->extraCopyPaths, fragment, std::string("extraCopyPaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_154)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_154))};
    auto _try_value_155 = appendStringArrayField(target->linkLibraries, fragment, std::string("linkLibraries"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_155)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_155))};
    auto _try_value_156 = appendStringArrayField(target->frameworks, fragment, std::string("frameworks"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_156)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_156))};
    auto _try_value_157 = appendStringArrayField(target->pkgConfigPackages, fragment, std::string("pkgConfigPackages"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_157)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_157))};
    auto _try_value_158 = appendStringArrayField(target->defines, fragment, std::string("defines"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_158)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_158))};
    auto _try_value_159 = appendStringArrayField(target->compilerFlags, fragment, std::string("compilerFlags"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_159)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_159))};
    auto _try_value_160 = appendStringArrayField(target->linkerFlags, fragment, std::string("linkerFlags"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_160)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_160))};
    return doof::Success<void>{};
}
doof::Result<void, std::string> appendStringArrayField(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath, const std::string& pathRoot) {
    if (!manifestJsonHas(object, name)) {
        return doof::Success<void>{};
    }
    auto _try_value_161 = manifestArray(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_161)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_161))};
    const auto values = doof::success_value(_try_value_161);
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        auto _try_value_163 = manifestString(doof::array_at(values, index, "src/package-manifest", 1000), manifestPath, (((((fieldPath + std::string(".")) + name) + std::string("[")) + doof::to_string(index)) + std::string("]")));
        if (doof::is_failure(_try_value_163)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_163))};
        const auto value = doof::success_value(_try_value_163);
        const auto normalized = ((pathRoot == std::string("")) ? value : manifestJoinPath(pathRoot, value));
        appendUnique(target, normalized);
    }
    return doof::Success<void>{};
}
void appendNativeBuild(const std::shared_ptr<NativeBuildPlan>& target, const std::shared_ptr<NativeBuildPlan>& source) {
    appendUniqueValues(target->includePaths, source->includePaths);
    appendUniqueValues(target->sourceFiles, source->sourceFiles);
    appendUniqueValues(target->libraryPaths, source->libraryPaths);
    appendUniqueValues(target->extraCopyPaths, source->extraCopyPaths);
    appendUniqueValues(target->linkLibraries, source->linkLibraries);
    appendUniqueValues(target->frameworks, source->frameworks);
    appendUniqueValues(target->pkgConfigPackages, source->pkgConfigPackages);
    appendUniqueValues(target->defines, source->defines);
    appendUniqueValues(target->compilerFlags, source->compilerFlags);
    appendUniqueValues(target->linkerFlags, source->linkerFlags);
}
void appendUniqueValues(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<std::vector<std::string>>& values) {
    const auto& _iterable_165 = values;
    for (const auto& value : *_iterable_165) {
        appendUnique(target, value);
    }
}
void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value) {
    const auto& _iterable_167 = target;
    for (const auto& existing : *_iterable_167) {
        if (existing == value) {
            return;
        }
    }
    target->push_back(value);
}
doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> manifestObject(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath) {
    {
        auto _case_subject = value;
        if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
            return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{ object };
    }
    else {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be an object")) };
    }
    }
    doof::unreachable();
}
doof::Result<std::shared_ptr<std::vector<doof::JsonValue>>, std::string> manifestArray(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath) {
    {
        auto _case_subject = value;
        if (doof::json_is_array(_case_subject)) {
            const auto array = std::get<doof::JsonArray>(doof::json_storage(_case_subject));
            return doof::Success<std::shared_ptr<std::vector<doof::JsonValue>>>{ array };
    }
    else {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be an array")) };
    }
    }
    doof::unreachable();
}
doof::Result<std::string, std::string> manifestString(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath) {
    {
        auto _case_subject = value;
        if (doof::json_is_string(_case_subject)) {
            const auto text = doof::json_as_string(_case_subject);
            return doof::Success<std::string>{ text };
    }
    else {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be a string")) };
    }
    }
    doof::unreachable();
}
}
