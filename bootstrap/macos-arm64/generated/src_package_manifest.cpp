#include "src_package_manifest.hpp"

namespace app_src_package_manifest_ {
using namespace ::std_::json::index;
using namespace ::std_::path::index;
using namespace ::app_src_macos_app_;
using namespace ::app_src_ios_app_;
#line 12 "/src/package-manifest.do"
std::string manifestJoinPath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
#line 13 "/src/package-manifest.do"
doof::JsonValue manifestJsonField(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
    return [&]() -> doof::JsonValue { auto _try_value = doof::map_get(object, name, "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/package-manifest", 13, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
}
#line 14 "/src/package-manifest.do"
bool manifestJsonHas(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
    return [&]() -> bool { auto _map_has_1 = object; return _map_has_1->find(name) != _map_has_1->end(); }();
}









#line 118 "/src/package-manifest.do"
doof::Result<std::shared_ptr<PackageManifest>, std::string> parsePackageManifest(const std::string& source, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& targetOverride) {
#line 125 "/src/package-manifest.do"
    auto _try_value_2 = ::doof_json::parse(source);
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_2))};
    const auto parsed = doof::success_value(_try_value_2);
#line 126 "/src/package-manifest.do"
    auto _try_value_3 = manifestObject(parsed, manifestPath, std::string("root"));
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_3))};
    const auto root = doof::success_value(_try_value_3);
#line 128 "/src/package-manifest.do"
    auto name = std::string("");
#line 129 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("name"))) {
#line 130 "/src/package-manifest.do"
        auto _try_value_4 = manifestString(manifestJsonField(root, std::string("name")), manifestPath, std::string("name"));
        if (doof::is_failure(_try_value_4)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_4))};
        const auto parsedName = doof::success_value(_try_value_4);
#line 131 "/src/package-manifest.do"
        (name = parsedName);
    }
#line 134 "/src/package-manifest.do"
    auto version = std::string("1.0");
#line 135 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("version"))) {
#line 136 "/src/package-manifest.do"
        auto _try_value_5 = manifestString(manifestJsonField(root, std::string("version")), manifestPath, std::string("version"));
        if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_5))};
        const auto parsedVersion = doof::success_value(_try_value_5);
#line 137 "/src/package-manifest.do"
        (version = parsedVersion);
    }
#line 140 "/src/package-manifest.do"
    auto _try_value_6 = parseManifestResources(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
    const auto resources = doof::success_value(_try_value_6);
#line 141 "/src/package-manifest.do"
    auto _try_value_7 = parsePackageDependencies(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_7))};
    const auto dependencies = doof::success_value(_try_value_7);
#line 142 "/src/package-manifest.do"
    auto _try_value_8 = parseExternalDependencies(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
    const auto externalDependencies = doof::success_value(_try_value_8);
#line 143 "/src/package-manifest.do"
    auto _try_value_9 = parseResolutions(root, manifestPath, std::string("packages"));
    if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
    const auto packageResolutions = doof::success_value(_try_value_9);
#line 144 "/src/package-manifest.do"
    auto _try_value_10 = parseResolutions(root, manifestPath, std::string("externalDependencies"));
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_10))};
    const auto externalResolutions = doof::success_value(_try_value_10);
#line 145 "/src/package-manifest.do"
    auto _try_value_11 = parseDependencyPolicy(root, manifestPath);
    if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_11))};
    const auto policy = doof::success_value(_try_value_11);
#line 146 "/src/package-manifest.do"
    auto _try_value_12 = parseManifestTarget(root, manifestPath);
    if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
    const auto manifestTarget = doof::success_value(_try_value_12);
#line 147 "/src/package-manifest.do"
    const auto target = ((targetOverride == std::string("")) ? manifestTarget : targetOverride);
#line 148 "/src/package-manifest.do"
    auto _try_value_13 = parseManifestNativeBuild(root, manifestPath, rootDirectory, platform, target);
    if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
    const auto nativeBuild = doof::success_value(_try_value_13);
#line 149 "/src/package-manifest.do"
    auto _try_value_14 = parseMacOSApp(root, manifestPath, rootDirectory, name, version, target);
    if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
    const auto macosApp = doof::success_value(_try_value_14);
#line 150 "/src/package-manifest.do"
    auto _try_value_15 = parseIOSApp(root, manifestPath, rootDirectory, name, version, target);
    if (doof::is_failure(_try_value_15)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_15))};
    const auto iosApp = doof::success_value(_try_value_15);
#line 151 "/src/package-manifest.do"
    auto _try_value_16 = parseMacOSPackage(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_16))};
    const auto packageConfig = doof::success_value(_try_value_16);
#line 152 "/src/package-manifest.do"
    auto _try_value_17 = parseIOSPackage(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_17)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_17))};
    const auto iosPackageConfig = doof::success_value(_try_value_17);
#line 153 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<PackageManifest>>{ std::make_shared<PackageManifest>(name, version, manifestPath, rootDirectory, resources, dependencies, externalDependencies, packageResolutions, externalResolutions, policy, nativeBuild, target, macosApp, iosApp, packageConfig, iosPackageConfig) };
}
#line 160 "/src/package-manifest.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>, std::string> parsePackageDependencies(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
#line 165 "/src/package-manifest.do"
    if (!manifestJsonHas(root, std::string("dependencies"))) {
#line 165 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>>{ std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{}) };
    }
#line 166 "/src/package-manifest.do"
    auto _try_value_18 = manifestObject(manifestJsonField(root, std::string("dependencies")), manifestPath, std::string("dependencies"));
    if (doof::is_failure(_try_value_18)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_18))};
    const auto values = doof::success_value(_try_value_18);
#line 167 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> result = std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{});
#line 168 "/src/package-manifest.do"
    const auto& _iterable_20 = values;
    for (const auto& [name, value] : *_iterable_20) {
#line 169 "/src/package-manifest.do"
        const auto fieldPath = (std::string("dependencies.") + name);
#line 170 "/src/package-manifest.do"
        if (name == std::string("")) {
#line 170 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": dependency names must not be empty")) };
        }
#line 171 "/src/package-manifest.do"
        auto _try_value_21 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_21))};
        const auto object = doof::success_value(_try_value_21);
#line 172 "/src/package-manifest.do"
        if (manifestJsonHas(object, std::string("path"))) {
#line 173 "/src/package-manifest.do"
            if ((manifestJsonHas(object, std::string("url")) || manifestJsonHas(object, std::string("ref"))) || manifestJsonHas(object, std::string("commit"))) {
#line 174 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must declare either path or url/ref/commit")) };
            }
#line 176 "/src/package-manifest.do"
            auto _try_value_22 = requiredManifestString(object, std::string("path"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_22))};
            const auto path = doof::success_value(_try_value_22);
#line 177 "/src/package-manifest.do"
            result->push_back(std::make_shared<PackageDependency>(name, manifestJoinPath(rootDirectory, path), std::string(""), std::string(""), std::string("")));
#line 178 "/src/package-manifest.do"
            continue;
        }
#line 180 "/src/package-manifest.do"
        auto _try_value_23 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_23))};
        const auto url = doof::success_value(_try_value_23);
#line 181 "/src/package-manifest.do"
        auto _try_value_24 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_24)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_24))};
        const auto ref = doof::success_value(_try_value_24);
#line 182 "/src/package-manifest.do"
        auto _try_value_25 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_25))};
        const auto commit = doof::success_value(_try_value_25);
#line 183 "/src/package-manifest.do"
        if (!isHexString(commit, 40)) {
#line 184 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".commit must be a 40-character hex string")) };
        }
#line 186 "/src/package-manifest.do"
        result->push_back(std::make_shared<PackageDependency>(name, std::string(""), url, ref, doof::string_toLowerCase(commit)));
    }
#line 188 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>>{ result };
}
#line 191 "/src/package-manifest.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>, std::string> parseResolutions(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& section) {
#line 196 "/src/package-manifest.do"
    if (!manifestJsonHas(root, std::string("resolutions"))) {
#line 196 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>>{ std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{}) };
    }
#line 197 "/src/package-manifest.do"
    auto _try_value_26 = manifestObject(manifestJsonField(root, std::string("resolutions")), manifestPath, std::string("resolutions"));
    if (doof::is_failure(_try_value_26)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_26))};
    const auto resolutions = doof::success_value(_try_value_26);
#line 198 "/src/package-manifest.do"
    if (!manifestJsonHas(resolutions, section)) {
#line 198 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>>{ std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{}) };
    }
#line 199 "/src/package-manifest.do"
    const auto fieldRoot = (std::string("resolutions.") + section);
#line 200 "/src/package-manifest.do"
    auto _try_value_27 = manifestObject(manifestJsonField(resolutions, section), manifestPath, fieldRoot);
    if (doof::is_failure(_try_value_27)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_27))};
    const auto values = doof::success_value(_try_value_27);
#line 201 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> result = std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{});
#line 202 "/src/package-manifest.do"
    const auto& _iterable_29 = values;
    for (const auto& [name, value] : *_iterable_29) {
#line 203 "/src/package-manifest.do"
        const auto fieldPath = ((fieldRoot + std::string(".")) + name);
#line 204 "/src/package-manifest.do"
        auto _try_value_30 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_30))};
        const auto object = doof::success_value(_try_value_30);
#line 205 "/src/package-manifest.do"
        auto kind = std::string("git");
#line 206 "/src/package-manifest.do"
        if (manifestJsonHas(object, std::string("kind"))) {
#line 207 "/src/package-manifest.do"
            auto _try_value_31 = manifestString(manifestJsonField(object, std::string("kind")), manifestPath, (fieldPath + std::string(".kind")));
            if (doof::is_failure(_try_value_31)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_31))};
            const auto parsedKind = doof::success_value(_try_value_31);
#line 208 "/src/package-manifest.do"
            (kind = parsedKind);
        }
#line 210 "/src/package-manifest.do"
        if ((section == std::string("packages")) && (kind != std::string("git"))) {
#line 211 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".kind must be \"git\"")) };
        }
#line 213 "/src/package-manifest.do"
        auto _try_value_32 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_32)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_32))};
        const auto url = doof::success_value(_try_value_32);
#line 214 "/src/package-manifest.do"
        if (kind == std::string("git")) {
#line 215 "/src/package-manifest.do"
            auto _try_value_33 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_33))};
            const auto ref = doof::success_value(_try_value_33);
#line 216 "/src/package-manifest.do"
            auto _try_value_34 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_34)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_34))};
            const auto commit = doof::success_value(_try_value_34);
#line 217 "/src/package-manifest.do"
            if (!isHexString(commit, 40)) {
#line 218 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".commit must be a 40-character hex string")) };
            }
#line 220 "/src/package-manifest.do"
            result->push_back(std::make_shared<DependencyResolution>(name, kind, url, ref, doof::string_toLowerCase(commit), std::string("")));
#line 221 "/src/package-manifest.do"
            continue;
        }
#line 223 "/src/package-manifest.do"
        if (kind == std::string("archive")) {
#line 224 "/src/package-manifest.do"
            auto _try_value_35 = requiredManifestString(object, std::string("sha256"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_35)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_35))};
            const auto sha256 = doof::success_value(_try_value_35);
#line 225 "/src/package-manifest.do"
            if (!isHexString(sha256, 64)) {
#line 226 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".sha256 must be a 64-character hex string")) };
            }
#line 228 "/src/package-manifest.do"
            result->push_back(std::make_shared<DependencyResolution>(name, kind, url, std::string(""), std::string(""), doof::string_toLowerCase(sha256)));
#line 229 "/src/package-manifest.do"
            continue;
        }
#line 231 "/src/package-manifest.do"
        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".kind must be either \"archive\" or \"git\"")) };
    }
#line 233 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>>{ result };
}
#line 236 "/src/package-manifest.do"
doof::Result<std::shared_ptr<DependencyPolicy>, std::string> parseDependencyPolicy(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath) {
#line 237 "/src/package-manifest.do"
    const auto result = std::make_shared<DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 238 "/src/package-manifest.do"
    if (!manifestJsonHas(root, std::string("policy"))) {
#line 238 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<DependencyPolicy>>{ result };
    }
#line 239 "/src/package-manifest.do"
    auto _try_value_36 = manifestObject(manifestJsonField(root, std::string("policy")), manifestPath, std::string("policy"));
    if (doof::is_failure(_try_value_36)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_36))};
    const auto policy = doof::success_value(_try_value_36);
#line 240 "/src/package-manifest.do"
    if (manifestJsonHas(policy, std::string("allowedPackageSources"))) {
#line 241 "/src/package-manifest.do"
        (result->hasPackageSourceAllowlist = true);
#line 242 "/src/package-manifest.do"
        auto _try_value_37 = appendPolicyStrings(result->allowedPackageSources, policy, std::string("allowedPackageSources"), manifestPath, std::string("policy"));
        if (doof::is_failure(_try_value_37)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_37))};
    }
#line 244 "/src/package-manifest.do"
    if (manifestJsonHas(policy, std::string("allowedExternalSources"))) {
#line 245 "/src/package-manifest.do"
        (result->hasExternalSourceAllowlist = true);
#line 246 "/src/package-manifest.do"
        auto _try_value_38 = appendPolicyStrings(result->allowedExternalSources, policy, std::string("allowedExternalSources"), manifestPath, std::string("policy"));
        if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
    }
#line 248 "/src/package-manifest.do"
    if (manifestJsonHas(policy, std::string("native"))) {
#line 249 "/src/package-manifest.do"
        auto _try_value_39 = manifestObject(manifestJsonField(policy, std::string("native")), manifestPath, std::string("policy.native"));
        if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_39))};
        const auto native = doof::success_value(_try_value_39);
#line 250 "/src/package-manifest.do"
        if (manifestJsonHas(native, std::string("allowedLinkLibraries"))) {
#line 251 "/src/package-manifest.do"
            (result->hasLinkLibraryAllowlist = true);
#line 252 "/src/package-manifest.do"
            auto _try_value_40 = appendPolicyStrings(result->allowedLinkLibraries, native, std::string("allowedLinkLibraries"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_40)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_40))};
        }
#line 254 "/src/package-manifest.do"
        if (manifestJsonHas(native, std::string("allowedFrameworks"))) {
#line 255 "/src/package-manifest.do"
            (result->hasFrameworkAllowlist = true);
#line 256 "/src/package-manifest.do"
            auto _try_value_41 = appendPolicyStrings(result->allowedFrameworks, native, std::string("allowedFrameworks"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_41))};
        }
#line 258 "/src/package-manifest.do"
        if (manifestJsonHas(native, std::string("allowedPkgConfigPackages"))) {
#line 259 "/src/package-manifest.do"
            (result->hasPkgConfigAllowlist = true);
#line 260 "/src/package-manifest.do"
            auto _try_value_42 = appendPolicyStrings(result->allowedPkgConfigPackages, native, std::string("allowedPkgConfigPackages"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_42)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_42))};
        }
    }
#line 263 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<DependencyPolicy>>{ result };
}
#line 266 "/src/package-manifest.do"
doof::Result<void, std::string> appendPolicyStrings(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath) {
#line 273 "/src/package-manifest.do"
    auto _try_value_43 = manifestArray(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_43)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_43))};
    const auto values = doof::success_value(_try_value_43);
#line 274 "/src/package-manifest.do"
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
#line 275 "/src/package-manifest.do"
        auto _try_value_45 = manifestString(doof::array_at(values, index, "src/package-manifest", 275), manifestPath, (((((fieldPath + std::string(".")) + name) + std::string("[")) + doof::to_string(index)) + std::string("]")));
        if (doof::is_failure(_try_value_45)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_45))};
        const auto value = doof::success_value(_try_value_45);
#line 276 "/src/package-manifest.do"
        if (value == std::string("")) {
#line 276 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" entries must not be empty")) };
        }
#line 277 "/src/package-manifest.do"
        appendUnique(target, value);
    }
#line 279 "/src/package-manifest.do"
    return doof::Success<void>{};
}
#line 282 "/src/package-manifest.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>, std::string> parseExternalDependencies(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
#line 287 "/src/package-manifest.do"
    if (!manifestJsonHas(root, std::string("externalDependencies"))) {
#line 287 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(std::vector<std::shared_ptr<ExternalDependency>>{}) };
    }
#line 288 "/src/package-manifest.do"
    auto _try_value_46 = manifestObject(manifestJsonField(root, std::string("externalDependencies")), manifestPath, std::string("externalDependencies"));
    if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_46))};
    const auto values = doof::success_value(_try_value_46);
#line 289 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(std::vector<std::shared_ptr<ExternalDependency>>{});
#line 290 "/src/package-manifest.do"
    const auto& _iterable_48 = values;
    for (const auto& [name, value] : *_iterable_48) {
#line 291 "/src/package-manifest.do"
        const auto fieldPath = (std::string("externalDependencies.") + name);
#line 292 "/src/package-manifest.do"
        if (((name == std::string("")) || doof::string_contains(name, std::string("/"))) || doof::string_contains(name, std::string("\\"))) {
#line 293 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": invalid external dependency name \"")) + name) + std::string("\"")) };
        }
#line 295 "/src/package-manifest.do"
        auto _try_value_49 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_49)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_49))};
        const auto object = doof::success_value(_try_value_49);
#line 296 "/src/package-manifest.do"
        auto _try_value_50 = requiredManifestString(object, std::string("kind"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_50)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_50))};
        const auto kind = doof::success_value(_try_value_50);
#line 297 "/src/package-manifest.do"
        auto _try_value_51 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_51)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_51))};
        const auto url = doof::success_value(_try_value_51);
#line 298 "/src/package-manifest.do"
        auto _try_value_52 = requiredManifestString(object, std::string("destination"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_52)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_52))};
        const auto destination = doof::success_value(_try_value_52);
#line 299 "/src/package-manifest.do"
        const auto destinationPath = manifestJoinPath(rootDirectory, destination);
#line 300 "/src/package-manifest.do"
        if (!manifestPathWithinRoot(destinationPath, rootDirectory)) {
#line 301 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".destination must stay within the package root")) };
        }
#line 303 "/src/package-manifest.do"
        auto _try_value_53 = parseExternalDependencyCommands(object, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_53)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_53))};
        const auto commands = doof::success_value(_try_value_53);
#line 305 "/src/package-manifest.do"
        if (kind == std::string("archive")) {
#line 306 "/src/package-manifest.do"
            auto _try_value_54 = requiredManifestString(object, std::string("sha256"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_54)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_54))};
            const auto sha256 = doof::success_value(_try_value_54);
#line 307 "/src/package-manifest.do"
            if (!isSupportedExternalArchiveUrl(url)) {
#line 308 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".url must end with .zip, .tar.gz, .tgz, .tar.bz2, .tbz2, or .tar.xz")) };
            }
#line 310 "/src/package-manifest.do"
            if (!isHexString(sha256, 64)) {
#line 311 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".sha256 must be a 64-character hex string")) };
            }
#line 313 "/src/package-manifest.do"
            auto stripComponents = 1;
#line 314 "/src/package-manifest.do"
            if (manifestJsonHas(object, std::string("stripComponents"))) {
#line 315 "/src/package-manifest.do"
                {
                    auto _case_subject = manifestJsonField(object, std::string("stripComponents"));
                    if (doof::json_is_number(_case_subject)) {
                        const auto number = doof::json_as_int(_case_subject);
#line 317 "/src/package-manifest.do"
                        if (number < 0) {
#line 318 "/src/package-manifest.do"
                            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".stripComponents must be a non-negative integer")) };
                        }
#line 320 "/src/package-manifest.do"
                        (stripComponents = number);
                }
                else if (doof::json_is_number(_case_subject)) {
                        const auto number = doof::json_as_double(_case_subject);
#line 323 "/src/package-manifest.do"
                        (stripComponents = static_cast<int32_t>(number));
#line 324 "/src/package-manifest.do"
                        if ((number < 0.0) || (static_cast<double>(stripComponents) != number)) {
#line 325 "/src/package-manifest.do"
                            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".stripComponents must be a non-negative integer")) };
                        }
                }
                else {
#line 328 "/src/package-manifest.do"
                        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".stripComponents must be a non-negative integer")) };
                }
                }
            }
#line 331 "/src/package-manifest.do"
            auto _try_value_55 = parseExternalDependencyCopyFiles(object, manifestPath, fieldPath);
            if (doof::is_failure(_try_value_55)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_55))};
            const auto copyFiles = doof::success_value(_try_value_55);
#line 332 "/src/package-manifest.do"
            result->push_back(std::make_shared<ExternalDependency>(name, kind, url, destination, doof::string_toLowerCase(sha256), stripComponents, copyFiles, std::string(""), std::string(""), commands));
#line 335 "/src/package-manifest.do"
            continue;
        }
#line 338 "/src/package-manifest.do"
        if (kind == std::string("git")) {
#line 339 "/src/package-manifest.do"
            auto _try_value_56 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_56)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_56))};
            const auto ref = doof::success_value(_try_value_56);
#line 340 "/src/package-manifest.do"
            auto _try_value_57 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_57)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_57))};
            const auto commit = doof::success_value(_try_value_57);
#line 341 "/src/package-manifest.do"
            if (!isHexString(commit, 40)) {
#line 342 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".commit must be a 40-character hex string")) };
            }
#line 344 "/src/package-manifest.do"
            result->push_back(std::make_shared<ExternalDependency>(name, kind, url, destination, std::string(""), 1, std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{}), ref, doof::string_toLowerCase(commit), commands));
#line 347 "/src/package-manifest.do"
            continue;
        }
#line 349 "/src/package-manifest.do"
        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".kind must be either \"archive\" or \"git\"")) };
    }
#line 351 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>>{ result };
}
#line 354 "/src/package-manifest.do"
doof::Result<std::string, std::string> requiredManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath) {
#line 360 "/src/package-manifest.do"
    if (!manifestJsonHas(object, name)) {
#line 361 "/src/package-manifest.do"
        return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" is required")) };
    }
#line 363 "/src/package-manifest.do"
    auto _try_value_58 = manifestString(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_58)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_58))};
    const auto value = doof::success_value(_try_value_58);
#line 364 "/src/package-manifest.do"
    if (value == std::string("")) {
#line 365 "/src/package-manifest.do"
        return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" must not be empty")) };
    }
#line 367 "/src/package-manifest.do"
    return doof::Success<std::string>{ value };
}
#line 370 "/src/package-manifest.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>, std::string> parseExternalDependencyCopyFiles(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& manifestPath, const std::string& fieldPath) {
#line 375 "/src/package-manifest.do"
    if (!manifestJsonHas(object, std::string("copyFiles"))) {
#line 375 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{}) };
    }
#line 376 "/src/package-manifest.do"
    auto _try_value_59 = manifestArray(manifestJsonField(object, std::string("copyFiles")), manifestPath, (fieldPath + std::string(".copyFiles")));
    if (doof::is_failure(_try_value_59)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_59))};
    const auto values = doof::success_value(_try_value_59);
#line 377 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{});
#line 378 "/src/package-manifest.do"
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
#line 379 "/src/package-manifest.do"
        const auto entryPath = (((fieldPath + std::string(".copyFiles[")) + doof::to_string(index)) + std::string("]"));
#line 380 "/src/package-manifest.do"
        auto _try_value_61 = manifestObject(doof::array_at(values, index, "src/package-manifest", 380), manifestPath, entryPath);
        if (doof::is_failure(_try_value_61)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_61))};
        const auto entry = doof::success_value(_try_value_61);
#line 381 "/src/package-manifest.do"
        auto _try_value_62 = requiredManifestString(entry, std::string("from"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_62))};
        const auto source = doof::success_value(_try_value_62);
#line 382 "/src/package-manifest.do"
        auto _try_value_63 = requiredManifestString(entry, std::string("to"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_63))};
        const auto destination = doof::success_value(_try_value_63);
#line 383 "/src/package-manifest.do"
        result->push_back(std::make_shared<ExternalDependencyCopyFile>(source, destination));
    }
#line 385 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>>{ result };
}
#line 388 "/src/package-manifest.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>, std::string> parseExternalDependencyCommands(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& manifestPath, const std::string& fieldPath) {
#line 393 "/src/package-manifest.do"
    if (!manifestJsonHas(object, std::string("commands"))) {
#line 393 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{}) };
    }
#line 394 "/src/package-manifest.do"
    auto _try_value_64 = manifestArray(manifestJsonField(object, std::string("commands")), manifestPath, (fieldPath + std::string(".commands")));
    if (doof::is_failure(_try_value_64)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_64))};
    const auto values = doof::success_value(_try_value_64);
#line 395 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{});
#line 396 "/src/package-manifest.do"
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
#line 397 "/src/package-manifest.do"
        const auto entryPath = (((fieldPath + std::string(".commands[")) + doof::to_string(index)) + std::string("]"));
#line 398 "/src/package-manifest.do"
        auto _try_value_66 = manifestObject(doof::array_at(values, index, "src/package-manifest", 398), manifestPath, entryPath);
        if (doof::is_failure(_try_value_66)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_66))};
        const auto entry = doof::success_value(_try_value_66);
#line 399 "/src/package-manifest.do"
        auto _try_value_67 = requiredManifestString(entry, std::string("program"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_67)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_67))};
        const auto program = doof::success_value(_try_value_67);
#line 400 "/src/package-manifest.do"
        std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 401 "/src/package-manifest.do"
        if (manifestJsonHas(entry, std::string("args"))) {
#line 402 "/src/package-manifest.do"
            auto _try_value_68 = manifestArray(manifestJsonField(entry, std::string("args")), manifestPath, (entryPath + std::string(".args")));
            if (doof::is_failure(_try_value_68)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_68))};
            const auto entries = doof::success_value(_try_value_68);
#line 403 "/src/package-manifest.do"
            for (int32_t argumentIndex = 0; argumentIndex < static_cast<int32_t>((entries)->size()); ++argumentIndex) {
#line 404 "/src/package-manifest.do"
                auto _try_value_70 = manifestString(doof::array_at(entries, argumentIndex, "src/package-manifest", 404), manifestPath, (((entryPath + std::string(".args[")) + doof::to_string(argumentIndex)) + std::string("]")));
                if (doof::is_failure(_try_value_70)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_70))};
                const auto argument = doof::success_value(_try_value_70);
#line 405 "/src/package-manifest.do"
                args->push_back(argument);
            }
        }
#line 408 "/src/package-manifest.do"
        std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
#line 409 "/src/package-manifest.do"
        if (manifestJsonHas(entry, std::string("env"))) {
#line 410 "/src/package-manifest.do"
            auto _try_value_71 = manifestObject(manifestJsonField(entry, std::string("env")), manifestPath, (entryPath + std::string(".env")));
            if (doof::is_failure(_try_value_71)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_71))};
            const auto entries = doof::success_value(_try_value_71);
#line 411 "/src/package-manifest.do"
            const auto& _iterable_73 = entries;
            for (const auto& [key, value] : *_iterable_73) {
#line 412 "/src/package-manifest.do"
                if (key == std::string("")) {
#line 412 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + entryPath) + std::string(".env keys must not be empty")) };
                }
#line 413 "/src/package-manifest.do"
                auto _try_value_74 = manifestString(value, manifestPath, ((entryPath + std::string(".env.")) + key));
                if (doof::is_failure(_try_value_74)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_74))};
                const auto text = doof::success_value(_try_value_74);
#line 414 "/src/package-manifest.do"
                doof::map_set(env, key, text, "", 0);
            }
        }
#line 417 "/src/package-manifest.do"
        auto workingDirectory = std::string("");
#line 418 "/src/package-manifest.do"
        if (manifestJsonHas(entry, std::string("workingDirectory"))) {
#line 419 "/src/package-manifest.do"
            auto _try_value_75 = manifestString(manifestJsonField(entry, std::string("workingDirectory")), manifestPath, (entryPath + std::string(".workingDirectory")));
            if (doof::is_failure(_try_value_75)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_75))};
            const auto parsed = doof::success_value(_try_value_75);
#line 420 "/src/package-manifest.do"
            if (parsed == std::string("")) {
#line 420 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + entryPath) + std::string(".workingDirectory must not be empty")) };
            }
#line 421 "/src/package-manifest.do"
            (workingDirectory = parsed);
        }
#line 423 "/src/package-manifest.do"
        result->push_back(std::make_shared<ExternalDependencyCommand>(program, args, env, workingDirectory));
    }
#line 425 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>>{ result };
}
#line 428 "/src/package-manifest.do"
bool isSupportedExternalArchiveUrl(const std::string& url) {
#line 429 "/src/package-manifest.do"
    const auto lower = doof::string_toLowerCase(url);
#line 430 "/src/package-manifest.do"
    return (((((doof::string_endsWith(lower, std::string(".zip")) || doof::string_endsWith(lower, std::string(".tar.gz"))) || doof::string_endsWith(lower, std::string(".tgz"))) || doof::string_endsWith(lower, std::string(".tar.bz2"))) || doof::string_endsWith(lower, std::string(".tbz2"))) || doof::string_endsWith(lower, std::string(".tar.xz")));
}
#line 434 "/src/package-manifest.do"
bool isHexString(const std::string& value, int32_t length) {
#line 435 "/src/package-manifest.do"
    if (static_cast<int32_t>(value.size()) != length) {
#line 435 "/src/package-manifest.do"
        return false;
    }
#line 436 "/src/package-manifest.do"
    const auto digits = std::string("0123456789abcdefABCDEF");
#line 437 "/src/package-manifest.do"
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
#line 438 "/src/package-manifest.do"
        if (!doof::string_contains(digits, doof::string_substring(value, index, (index + 1)))) {
#line 438 "/src/package-manifest.do"
            return false;
        }
    }
#line 440 "/src/package-manifest.do"
    return true;
}
#line 444 "/src/package-manifest.do"
std::shared_ptr<NativeBuildPlan> mergeNativeBuildPlans(const std::shared_ptr<std::vector<std::shared_ptr<NativeBuildPlan>>>& plans) {
#line 445 "/src/package-manifest.do"
    const auto merged = std::make_shared<NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 446 "/src/package-manifest.do"
    const auto& _iterable_78 = plans;
    for (const auto& plan : *_iterable_78) {
#line 446 "/src/package-manifest.do"
        appendNativeBuild(merged, plan);
    }
#line 447 "/src/package-manifest.do"
    return merged;
}
#line 450 "/src/package-manifest.do"
doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> parseManifestNativeBuild(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& target) {
#line 457 "/src/package-manifest.do"
    const auto result = std::make_shared<NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 458 "/src/package-manifest.do"
    if (!manifestJsonHas(root, std::string("build"))) {
#line 458 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
    }
#line 459 "/src/package-manifest.do"
    auto _try_value_79 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_79)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_79))};
    const auto build = doof::success_value(_try_value_79);
#line 460 "/src/package-manifest.do"
    if (!manifestJsonHas(build, std::string("native"))) {
#line 460 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
    }
#line 461 "/src/package-manifest.do"
    auto _try_value_80 = manifestObject(manifestJsonField(build, std::string("native")), manifestPath, std::string("build.native"));
    if (doof::is_failure(_try_value_80)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_80))};
    const auto native = doof::success_value(_try_value_80);
#line 463 "/src/package-manifest.do"
    auto _try_value_81 = appendNativeFragment(result, native, manifestPath, rootDirectory, std::string("build.native"));
    if (doof::is_failure(_try_value_81)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_81))};
#line 464 "/src/package-manifest.do"
    const auto platformKey = ((target == std::string("wasm")) ? std::string("wasm") : ((platform == std::string("ios-simulator")) ? std::string("iosSimulator") : ((platform == std::string("ios-device")) ? std::string("iosDevice") : platform)));
#line 465 "/src/package-manifest.do"
    if ((platformKey != std::string("")) && manifestJsonHas(native, platformKey)) {
#line 466 "/src/package-manifest.do"
        auto _try_value_82 = manifestObject(manifestJsonField(native, platformKey), manifestPath, (std::string("build.native.") + platformKey));
        if (doof::is_failure(_try_value_82)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_82))};
        const auto platformValue = doof::success_value(_try_value_82);
#line 471 "/src/package-manifest.do"
        auto _try_value_83 = appendNativeFragment(result, platformValue, manifestPath, rootDirectory, (std::string("build.native.") + platformKey));
        if (doof::is_failure(_try_value_83)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_83))};
    }
#line 473 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
}
#line 476 "/src/package-manifest.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseManifestResources(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
#line 481 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("resources"))) {
#line 482 "/src/package-manifest.do"
        return parseResourceArray(manifestJsonField(root, std::string("resources")), manifestPath, rootDirectory, std::string("resources"));
    }
#line 484 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("build"))) {
#line 485 "/src/package-manifest.do"
        auto _try_value_84 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_84)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_84))};
        const auto build = doof::success_value(_try_value_84);
#line 486 "/src/package-manifest.do"
        if (manifestJsonHas(build, std::string("resources"))) {
#line 487 "/src/package-manifest.do"
            return parseResourceArray(manifestJsonField(build, std::string("resources")), manifestPath, rootDirectory, std::string("build.resources"));
        }
    }
#line 495 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>>{ std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{}) };
}
#line 498 "/src/package-manifest.do"
doof::Result<std::string, std::string> parseManifestTarget(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath) {
#line 499 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("target"))) {
#line 500 "/src/package-manifest.do"
        return manifestString(manifestJsonField(root, std::string("target")), manifestPath, std::string("target"));
    }
#line 502 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("build"))) {
#line 503 "/src/package-manifest.do"
        auto _try_value_85 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_85)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_85))};
        const auto build = doof::success_value(_try_value_85);
#line 504 "/src/package-manifest.do"
        if (manifestJsonHas(build, std::string("target"))) {
#line 505 "/src/package-manifest.do"
            return manifestString(manifestJsonField(build, std::string("target")), manifestPath, std::string("build.target"));
        }
    }
#line 508 "/src/package-manifest.do"
    return doof::Success<std::string>{ std::string("") };
}
#line 511 "/src/package-manifest.do"
doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>, std::string> parseMacOSApp(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& packageName, const std::string& packageVersion, const std::string& target) {
#line 519 "/src/package-manifest.do"
    if (target != std::string("macos-app")) {
#line 519 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>>{ nullptr };
    }
#line 520 "/src/package-manifest.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> build = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 521 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("build"))) {
#line 522 "/src/package-manifest.do"
        auto _try_value_86 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_86)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_86))};
        const auto parsedBuild = doof::success_value(_try_value_86);
#line 523 "/src/package-manifest.do"
        (build = parsedBuild);
    }
#line 525 "/src/package-manifest.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> nested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 526 "/src/package-manifest.do"
    if (manifestJsonHas(build, std::string("macosApp"))) {
#line 527 "/src/package-manifest.do"
        auto _try_value_87 = manifestObject(manifestJsonField(build, std::string("macosApp")), manifestPath, std::string("build.macosApp"));
        if (doof::is_failure(_try_value_87)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_87))};
        const auto parsedNested = doof::success_value(_try_value_87);
#line 528 "/src/package-manifest.do"
        (nested = parsedNested);
    }
#line 531 "/src/package-manifest.do"
    auto _try_value_88 = firstManifestString(root, std::string("executable"), build, std::string("executable"), build, std::string("targetExecutableName"), packageName, manifestPath, std::string("executable"));
    if (doof::is_failure(_try_value_88)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_88))};
    const auto executableName = doof::success_value(_try_value_88);
#line 535 "/src/package-manifest.do"
    if (((executableName == std::string("")) || doof::string_contains(executableName, std::string("/"))) || doof::string_contains(executableName, std::string("\\"))) {
#line 536 "/src/package-manifest.do"
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": executable must be a file name without path separators")) };
    }
#line 538 "/src/package-manifest.do"
    const auto defaultBundleId = (std::string("dev.doof.") + sanitizeBundleName(((packageName == std::string("")) ? executableName : packageName)));
#line 539 "/src/package-manifest.do"
    auto _try_value_89 = firstManifestString(root, std::string("id"), nested, std::string("bundleId"), build, std::string("id"), defaultBundleId, manifestPath, std::string("build.macosApp.bundleId"));
    if (doof::is_failure(_try_value_89)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_89))};
    const auto bundleId = doof::success_value(_try_value_89);
#line 540 "/src/package-manifest.do"
    auto _try_value_90 = firstManifestString(root, std::string("title"), nested, std::string("displayName"), build, std::string("title"), ((packageName == std::string("")) ? executableName : packageName), manifestPath, std::string("build.macosApp.displayName"));
    if (doof::is_failure(_try_value_90)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_90))};
    const auto displayName = doof::success_value(_try_value_90);
#line 541 "/src/package-manifest.do"
    auto _try_value_91 = optionalManifestString(nested, std::string("version"), packageVersion, manifestPath, std::string("build.macosApp.version"));
    if (doof::is_failure(_try_value_91)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_91))};
    const auto version = doof::success_value(_try_value_91);
#line 542 "/src/package-manifest.do"
    auto _try_value_92 = optionalManifestString(nested, std::string("category"), std::string("public.app-category.developer-tools"), manifestPath, std::string("build.macosApp.category"));
    if (doof::is_failure(_try_value_92)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_92))};
    const auto category = doof::success_value(_try_value_92);
#line 543 "/src/package-manifest.do"
    auto _try_value_93 = optionalManifestString(nested, std::string("minimumSystemVersion"), std::string("11.0"), manifestPath, std::string("build.macosApp.minimumSystemVersion"));
    if (doof::is_failure(_try_value_93)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_93))};
    const auto minimumSystemVersion = doof::success_value(_try_value_93);
#line 545 "/src/package-manifest.do"
    auto icon = std::string("");
#line 546 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("icon"))) {
#line 547 "/src/package-manifest.do"
        auto _try_value_94 = manifestString(manifestJsonField(root, std::string("icon")), manifestPath, std::string("icon"));
        if (doof::is_failure(_try_value_94)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_94))};
        const auto parsed = doof::success_value(_try_value_94);
#line 548 "/src/package-manifest.do"
        (icon = parsed);
    } else if (manifestJsonHas(nested, std::string("icon"))) {
#line 550 "/src/package-manifest.do"
        auto _try_value_95 = manifestString(manifestJsonField(nested, std::string("icon")), manifestPath, std::string("build.macosApp.icon"));
        if (doof::is_failure(_try_value_95)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_95))};
        const auto parsed = doof::success_value(_try_value_95);
#line 551 "/src/package-manifest.do"
        (icon = parsed);
    } else if (manifestJsonHas(build, std::string("icon"))) {
#line 553 "/src/package-manifest.do"
        auto _try_value_96 = manifestString(manifestJsonField(build, std::string("icon")), manifestPath, std::string("build.icon"));
        if (doof::is_failure(_try_value_96)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_96))};
        const auto parsed = doof::success_value(_try_value_96);
#line 554 "/src/package-manifest.do"
        (icon = parsed);
    }
#line 556 "/src/package-manifest.do"
    auto iconPath = std::string("");
#line 557 "/src/package-manifest.do"
    if (icon != std::string("")) {
#line 558 "/src/package-manifest.do"
        if (!doof::string_endsWith(doof::string_toLowerCase(icon), std::string(".png"))) {
#line 559 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.icon must point to a PNG file")) };
        }
#line 561 "/src/package-manifest.do"
        (iconPath = manifestJoinPath(rootDirectory, icon));
#line 562 "/src/package-manifest.do"
        if (!manifestPathWithinRoot(iconPath, rootDirectory)) {
#line 563 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.icon must stay within the package root")) };
        }
    }
#line 567 "/src/package-manifest.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr;
#line 568 "/src/package-manifest.do"
    if (manifestJsonHas(nested, std::string("infoPlist"))) {
#line 569 "/src/package-manifest.do"
        auto _try_value_97 = manifestObject(manifestJsonField(nested, std::string("infoPlist")), manifestPath, std::string("build.macosApp.infoPlist"));
        if (doof::is_failure(_try_value_97)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_97))};
        const auto parsedInfo = doof::success_value(_try_value_97);
#line 570 "/src/package-manifest.do"
        const auto& _iterable_99 = parsedInfo;
        for (const auto& [key, ignored] : *_iterable_99) {
#line 571 "/src/package-manifest.do"
            if (isManagedMacOSPlistKey(key)) {
#line 572 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.infoPlist.")) + key) + std::string(" conflicts with a Doof-managed Info.plist key")) };
            }
        }
#line 575 "/src/package-manifest.do"
        (infoPlist = parsedInfo);
    }
#line 578 "/src/package-manifest.do"
    std::variant<std::monostate, doof::JsonValue> resourceValue = std::monostate{};
#line 579 "/src/package-manifest.do"
    auto resourceField = std::string("build.macosApp.resources");
#line 580 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("resources"))) {
#line 581 "/src/package-manifest.do"
        (resourceValue = manifestJsonField(root, std::string("resources")));
#line 582 "/src/package-manifest.do"
        (resourceField = std::string("resources"));
    } else if (manifestJsonHas(nested, std::string("resources"))) {
#line 584 "/src/package-manifest.do"
        (resourceValue = manifestJsonField(nested, std::string("resources")));
    } else if (manifestJsonHas(build, std::string("resources"))) {
#line 586 "/src/package-manifest.do"
        (resourceValue = manifestJsonField(build, std::string("resources")));
#line 587 "/src/package-manifest.do"
        (resourceField = std::string("build.resources"));
    }
#line 589 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSAppResource>>>(std::vector<std::shared_ptr<::app_src_macos_app_::MacOSAppResource>>{});
#line 590 "/src/package-manifest.do"
    if (!doof::is_null(resourceValue)) {
#line 591 "/src/package-manifest.do"
        auto _try_value_100 = parseResourceArray(std::get<doof::JsonValue>(resourceValue), manifestPath, rootDirectory, resourceField);
        if (doof::is_failure(_try_value_100)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_100))};
        const auto parsedResources = doof::success_value(_try_value_100);
#line 592 "/src/package-manifest.do"
        const auto& _iterable_102 = parsedResources;
        for (const auto& resource : *_iterable_102) {
#line 593 "/src/package-manifest.do"
            resources->push_back(std::make_shared<::app_src_macos_app_::MacOSAppResource>(resource->sourcePath, resource->destination));
        }
    }
#line 597 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>{});
#line 598 "/src/package-manifest.do"
    if (manifestJsonHas(nested, std::string("embeddedLibraries"))) {
#line 599 "/src/package-manifest.do"
        auto _try_value_103 = manifestArray(manifestJsonField(nested, std::string("embeddedLibraries")), manifestPath, std::string("build.macosApp.embeddedLibraries"));
        if (doof::is_failure(_try_value_103)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_103))};
        const auto entries = doof::success_value(_try_value_103);
#line 600 "/src/package-manifest.do"
        for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
#line 601 "/src/package-manifest.do"
            auto _try_value_105 = manifestObject(doof::array_at(entries, index, "src/package-manifest", 601), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("]")));
            if (doof::is_failure(_try_value_105)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_105))};
            const auto entry = doof::success_value(_try_value_105);
#line 602 "/src/package-manifest.do"
            const auto hasLibrary = manifestJsonHas(entry, std::string("library"));
#line 603 "/src/package-manifest.do"
            const auto hasPath = manifestJsonHas(entry, std::string("path"));
#line 604 "/src/package-manifest.do"
            if (hasLibrary == hasPath) {
#line 605 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.embeddedLibraries[")) + doof::to_string(index)) + std::string("] requires exactly one of library or path")) };
            }
#line 607 "/src/package-manifest.do"
            if (hasLibrary) {
#line 608 "/src/package-manifest.do"
                auto _try_value_106 = manifestString(manifestJsonField(entry, std::string("library")), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("].library")));
                if (doof::is_failure(_try_value_106)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_106))};
                const auto library = doof::success_value(_try_value_106);
#line 609 "/src/package-manifest.do"
                if (((library == std::string("")) || doof::string_contains(library, std::string("/"))) || doof::string_contains(library, std::string("\\"))) {
#line 610 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded linked library names must not contain path separators")) };
                }
#line 612 "/src/package-manifest.do"
                embeddedLibraries->push_back(std::make_shared<::app_src_macos_app_::MacOSEmbeddedLibrary>(library, std::string("")));
            } else {
#line 614 "/src/package-manifest.do"
                auto _try_value_107 = manifestString(manifestJsonField(entry, std::string("path")), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("].path")));
                if (doof::is_failure(_try_value_107)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_107))};
                const auto path = doof::success_value(_try_value_107);
#line 615 "/src/package-manifest.do"
                const auto resolvedPath = manifestJoinPath(rootDirectory, path);
#line 616 "/src/package-manifest.do"
                if (!manifestPathWithinRoot(resolvedPath, rootDirectory)) {
#line 617 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.embeddedLibraries[")) + doof::to_string(index)) + std::string("].path must stay within the package root")) };
                }
#line 619 "/src/package-manifest.do"
                if ((!doof::string_endsWith(resolvedPath, std::string(".dylib")) && !doof::string_endsWith(resolvedPath, std::string(".so"))) && !doof::string_endsWith(resolvedPath, std::string(".framework"))) {
#line 620 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded library paths must be .dylib, .so, or .framework")) };
                }
#line 622 "/src/package-manifest.do"
                embeddedLibraries->push_back(std::make_shared<::app_src_macos_app_::MacOSEmbeddedLibrary>(std::string(""), resolvedPath));
            }
        }
    }
#line 627 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>>{ std::make_shared<::app_src_macos_app_::MacOSAppConfig>(executableName, bundleId, displayName, version, iconPath, infoPlist, resources, embeddedLibraries, category, minimumSystemVersion) };
}
#line 633 "/src/package-manifest.do"
doof::Result<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>, std::string> parseIOSApp(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& packageName, const std::string& packageVersion, const std::string& target) {
#line 641 "/src/package-manifest.do"
    if (target != std::string("ios-app")) {
#line 641 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>>{ nullptr };
    }
#line 642 "/src/package-manifest.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> build = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 643 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("build"))) {
#line 644 "/src/package-manifest.do"
        auto _try_value_108 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_108)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_108))};
        const auto parsedBuild = doof::success_value(_try_value_108);
#line 645 "/src/package-manifest.do"
        (build = parsedBuild);
    }
#line 647 "/src/package-manifest.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> nested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 648 "/src/package-manifest.do"
    if (manifestJsonHas(build, std::string("iosApp"))) {
#line 649 "/src/package-manifest.do"
        auto _try_value_109 = manifestObject(manifestJsonField(build, std::string("iosApp")), manifestPath, std::string("build.iosApp"));
        if (doof::is_failure(_try_value_109)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_109))};
        const auto parsedNested = doof::success_value(_try_value_109);
#line 650 "/src/package-manifest.do"
        (nested = parsedNested);
    }
#line 653 "/src/package-manifest.do"
    auto _try_value_110 = firstManifestString(root, std::string("executable"), build, std::string("executable"), build, std::string("targetExecutableName"), packageName, manifestPath, std::string("executable"));
    if (doof::is_failure(_try_value_110)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_110))};
    const auto executableName = doof::success_value(_try_value_110);
#line 657 "/src/package-manifest.do"
    if (((executableName == std::string("")) || doof::string_contains(executableName, std::string("/"))) || doof::string_contains(executableName, std::string("\\"))) {
#line 658 "/src/package-manifest.do"
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": executable must be a file name without path separators")) };
    }
#line 660 "/src/package-manifest.do"
    const auto defaultBundleId = (std::string("dev.doof.") + sanitizeBundleName(((packageName == std::string("")) ? executableName : packageName)));
#line 661 "/src/package-manifest.do"
    auto _try_value_111 = firstManifestString(root, std::string("id"), nested, std::string("bundleId"), build, std::string("id"), defaultBundleId, manifestPath, std::string("build.iosApp.bundleId"));
    if (doof::is_failure(_try_value_111)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_111))};
    const auto bundleId = doof::success_value(_try_value_111);
#line 662 "/src/package-manifest.do"
    auto _try_value_112 = firstManifestString(root, std::string("title"), nested, std::string("displayName"), build, std::string("title"), ((packageName == std::string("")) ? executableName : packageName), manifestPath, std::string("build.iosApp.displayName"));
    if (doof::is_failure(_try_value_112)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_112))};
    const auto displayName = doof::success_value(_try_value_112);
#line 663 "/src/package-manifest.do"
    auto _try_value_113 = optionalManifestString(nested, std::string("version"), packageVersion, manifestPath, std::string("build.iosApp.version"));
    if (doof::is_failure(_try_value_113)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_113))};
    const auto version = doof::success_value(_try_value_113);
#line 664 "/src/package-manifest.do"
    auto _try_value_114 = optionalManifestString(nested, std::string("minimumDeploymentTarget"), std::string("16.0"), manifestPath, std::string("build.iosApp.minimumDeploymentTarget"));
    if (doof::is_failure(_try_value_114)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_114))};
    const auto minimumDeploymentTarget = doof::success_value(_try_value_114);
#line 666 "/src/package-manifest.do"
    auto icon = std::string("");
#line 667 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("icon"))) {
#line 668 "/src/package-manifest.do"
        auto _try_value_115 = manifestString(manifestJsonField(root, std::string("icon")), manifestPath, std::string("icon"));
        if (doof::is_failure(_try_value_115)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_115))};
        const auto parsed = doof::success_value(_try_value_115);
#line 669 "/src/package-manifest.do"
        (icon = parsed);
    } else if (manifestJsonHas(nested, std::string("icon"))) {
#line 671 "/src/package-manifest.do"
        auto _try_value_116 = manifestString(manifestJsonField(nested, std::string("icon")), manifestPath, std::string("build.iosApp.icon"));
        if (doof::is_failure(_try_value_116)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_116))};
        const auto parsed = doof::success_value(_try_value_116);
#line 672 "/src/package-manifest.do"
        (icon = parsed);
    } else if (manifestJsonHas(build, std::string("icon"))) {
#line 674 "/src/package-manifest.do"
        auto _try_value_117 = manifestString(manifestJsonField(build, std::string("icon")), manifestPath, std::string("build.icon"));
        if (doof::is_failure(_try_value_117)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_117))};
        const auto parsed = doof::success_value(_try_value_117);
#line 675 "/src/package-manifest.do"
        (icon = parsed);
    }
#line 677 "/src/package-manifest.do"
    auto iconPath = std::string("");
#line 678 "/src/package-manifest.do"
    if (icon != std::string("")) {
#line 679 "/src/package-manifest.do"
        if (!doof::string_endsWith(doof::string_toLowerCase(icon), std::string(".png"))) {
#line 680 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.iosApp.icon must point to a PNG file")) };
        }
#line 682 "/src/package-manifest.do"
        (iconPath = manifestJoinPath(rootDirectory, icon));
#line 683 "/src/package-manifest.do"
        if (!manifestPathWithinRoot(iconPath, rootDirectory)) {
#line 684 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.iosApp.icon must stay within the package root")) };
        }
    }
#line 688 "/src/package-manifest.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> infoPlist = nullptr;
#line 689 "/src/package-manifest.do"
    if (manifestJsonHas(nested, std::string("infoPlist"))) {
#line 690 "/src/package-manifest.do"
        auto _try_value_118 = manifestObject(manifestJsonField(nested, std::string("infoPlist")), manifestPath, std::string("build.iosApp.infoPlist"));
        if (doof::is_failure(_try_value_118)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_118))};
        const auto parsedInfo = doof::success_value(_try_value_118);
#line 691 "/src/package-manifest.do"
        const auto& _iterable_120 = parsedInfo;
        for (const auto& [key, ignored] : *_iterable_120) {
#line 692 "/src/package-manifest.do"
            if (isManagedIOSPlistKey(key)) {
#line 693 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.iosApp.infoPlist.")) + key) + std::string(" conflicts with a Doof-managed Info.plist key")) };
            }
        }
#line 696 "/src/package-manifest.do"
        (infoPlist = parsedInfo);
    }
#line 699 "/src/package-manifest.do"
    std::variant<std::monostate, doof::JsonValue> resourceValue = std::monostate{};
#line 700 "/src/package-manifest.do"
    auto resourceField = std::string("build.iosApp.resources");
#line 701 "/src/package-manifest.do"
    if (manifestJsonHas(root, std::string("resources"))) {
#line 702 "/src/package-manifest.do"
        (resourceValue = manifestJsonField(root, std::string("resources")));
#line 703 "/src/package-manifest.do"
        (resourceField = std::string("resources"));
    } else if (manifestJsonHas(nested, std::string("resources"))) {
#line 705 "/src/package-manifest.do"
        (resourceValue = manifestJsonField(nested, std::string("resources")));
    } else if (manifestJsonHas(build, std::string("resources"))) {
#line 707 "/src/package-manifest.do"
        (resourceValue = manifestJsonField(build, std::string("resources")));
#line 708 "/src/package-manifest.do"
        (resourceField = std::string("build.resources"));
    }
#line 710 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ios_app_::IOSAppResource>>> resources = std::make_shared<std::vector<std::shared_ptr<::app_src_ios_app_::IOSAppResource>>>(std::vector<std::shared_ptr<::app_src_ios_app_::IOSAppResource>>{});
#line 711 "/src/package-manifest.do"
    if (!doof::is_null(resourceValue)) {
#line 712 "/src/package-manifest.do"
        auto _try_value_121 = parseResourceArray(std::get<doof::JsonValue>(resourceValue), manifestPath, rootDirectory, resourceField);
        if (doof::is_failure(_try_value_121)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_121))};
        const auto parsedResources = doof::success_value(_try_value_121);
#line 713 "/src/package-manifest.do"
        const auto& _iterable_123 = parsedResources;
        for (const auto& resource : *_iterable_123) {
#line 714 "/src/package-manifest.do"
            resources->push_back(std::make_shared<::app_src_ios_app_::IOSAppResource>(resource->sourcePath, resource->destination));
        }
    }
#line 718 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>{});
#line 719 "/src/package-manifest.do"
    if (manifestJsonHas(nested, std::string("embeddedLibraries"))) {
#line 720 "/src/package-manifest.do"
        auto _try_value_124 = manifestArray(manifestJsonField(nested, std::string("embeddedLibraries")), manifestPath, std::string("build.iosApp.embeddedLibraries"));
        if (doof::is_failure(_try_value_124)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_124))};
        const auto entries = doof::success_value(_try_value_124);
#line 721 "/src/package-manifest.do"
        for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
#line 722 "/src/package-manifest.do"
            const auto field = ((std::string("build.iosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("]"));
#line 723 "/src/package-manifest.do"
            auto _try_value_126 = manifestObject(doof::array_at(entries, index, "src/package-manifest", 723), manifestPath, field);
            if (doof::is_failure(_try_value_126)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_126))};
            const auto entry = doof::success_value(_try_value_126);
#line 724 "/src/package-manifest.do"
            const auto hasLibrary = manifestJsonHas(entry, std::string("library"));
#line 725 "/src/package-manifest.do"
            const auto hasPath = manifestJsonHas(entry, std::string("path"));
#line 726 "/src/package-manifest.do"
            if (hasLibrary == hasPath) {
#line 726 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + field) + std::string(" requires exactly one of library or path")) };
            }
#line 727 "/src/package-manifest.do"
            if (hasLibrary) {
#line 728 "/src/package-manifest.do"
                auto _try_value_127 = manifestString(manifestJsonField(entry, std::string("library")), manifestPath, (field + std::string(".library")));
                if (doof::is_failure(_try_value_127)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_127))};
                const auto library = doof::success_value(_try_value_127);
#line 729 "/src/package-manifest.do"
                if (((library == std::string("")) || doof::string_contains(library, std::string("/"))) || doof::string_contains(library, std::string("\\"))) {
#line 730 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded linked library names must not contain path separators")) };
                }
#line 732 "/src/package-manifest.do"
                embeddedLibraries->push_back(std::make_shared<::app_src_ios_app_::IOSEmbeddedLibrary>(library, std::string("")));
            } else {
#line 734 "/src/package-manifest.do"
                auto _try_value_128 = manifestString(manifestJsonField(entry, std::string("path")), manifestPath, (field + std::string(".path")));
                if (doof::is_failure(_try_value_128)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_128))};
                const auto path = doof::success_value(_try_value_128);
#line 735 "/src/package-manifest.do"
                const auto resolvedPath = manifestJoinPath(rootDirectory, path);
#line 736 "/src/package-manifest.do"
                if (!manifestPathWithinRoot(resolvedPath, rootDirectory)) {
#line 737 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + field) + std::string(".path must stay within the package root")) };
                }
#line 739 "/src/package-manifest.do"
                if ((!doof::string_endsWith(resolvedPath, std::string(".dylib")) && !doof::string_endsWith(resolvedPath, std::string(".so"))) && !doof::string_endsWith(resolvedPath, std::string(".framework"))) {
#line 740 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded library paths must be .dylib, .so, or .framework")) };
                }
#line 742 "/src/package-manifest.do"
                embeddedLibraries->push_back(std::make_shared<::app_src_ios_app_::IOSEmbeddedLibrary>(std::string(""), resolvedPath));
            }
        }
    }
#line 747 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>>{ std::make_shared<::app_src_ios_app_::IOSAppConfig>(executableName, bundleId, displayName, version, iconPath, infoPlist, resources, embeddedLibraries, minimumDeploymentTarget) };
}
#line 753 "/src/package-manifest.do"
doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>, std::string> parseMacOSPackage(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
#line 754 "/src/package-manifest.do"
    auto distDirectory = manifestJoinPath(rootDirectory, std::string("dist"));
#line 755 "/src/package-manifest.do"
    auto signing = std::string("developer-id");
#line 756 "/src/package-manifest.do"
    auto identity = std::string("");
#line 757 "/src/package-manifest.do"
    auto sandbox = false;
#line 758 "/src/package-manifest.do"
    auto entitlementsPath = std::string("");
#line 759 "/src/package-manifest.do"
    if (!manifestJsonHas(root, std::string("build"))) {
#line 760 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
    }
#line 762 "/src/package-manifest.do"
    auto _try_value_129 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_129)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_129))};
    const auto build = doof::success_value(_try_value_129);
#line 763 "/src/package-manifest.do"
    if (!manifestJsonHas(build, std::string("package"))) {
#line 764 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
    }
#line 766 "/src/package-manifest.do"
    auto _try_value_130 = manifestObject(manifestJsonField(build, std::string("package")), manifestPath, std::string("build.package"));
    if (doof::is_failure(_try_value_130)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_130))};
    const auto package = doof::success_value(_try_value_130);
#line 767 "/src/package-manifest.do"
    if (manifestJsonHas(package, std::string("distDir"))) {
#line 768 "/src/package-manifest.do"
        auto _try_value_131 = manifestString(manifestJsonField(package, std::string("distDir")), manifestPath, std::string("build.package.distDir"));
        if (doof::is_failure(_try_value_131)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_131))};
        const auto value = doof::success_value(_try_value_131);
#line 769 "/src/package-manifest.do"
        (distDirectory = manifestJoinPath(rootDirectory, value));
#line 770 "/src/package-manifest.do"
        if (!manifestPathWithinRoot(distDirectory, rootDirectory)) {
#line 771 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.distDir must stay within the package root")) };
        }
    }
#line 774 "/src/package-manifest.do"
    if (manifestJsonHas(package, std::string("macos"))) {
#line 775 "/src/package-manifest.do"
        auto _try_value_132 = manifestObject(manifestJsonField(package, std::string("macos")), manifestPath, std::string("build.package.macos"));
        if (doof::is_failure(_try_value_132)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_132))};
        const auto macos = doof::success_value(_try_value_132);
#line 776 "/src/package-manifest.do"
        if (manifestJsonHas(macos, std::string("signing"))) {
#line 777 "/src/package-manifest.do"
            auto _try_value_133 = manifestString(manifestJsonField(macos, std::string("signing")), manifestPath, std::string("build.package.macos.signing"));
            if (doof::is_failure(_try_value_133)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_133))};
            const auto value = doof::success_value(_try_value_133);
#line 778 "/src/package-manifest.do"
            if ((value != std::string("developer-id")) && (value != std::string("ad-hoc"))) {
#line 779 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.signing must be one of \"developer-id\", \"ad-hoc\"")) };
            }
#line 781 "/src/package-manifest.do"
            (signing = value);
        }
#line 783 "/src/package-manifest.do"
        if (manifestJsonHas(macos, std::string("identity"))) {
#line 784 "/src/package-manifest.do"
            auto _try_value_134 = manifestString(manifestJsonField(macos, std::string("identity")), manifestPath, std::string("build.package.macos.identity"));
            if (doof::is_failure(_try_value_134)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_134))};
            const auto value = doof::success_value(_try_value_134);
#line 785 "/src/package-manifest.do"
            (identity = value);
        }
#line 787 "/src/package-manifest.do"
        if (manifestJsonHas(macos, std::string("sandbox"))) {
#line 788 "/src/package-manifest.do"
            {
                auto _case_subject = manifestJsonField(macos, std::string("sandbox"));
                if (doof::json_is_boolean(_case_subject)) {
                    const auto value = doof::json_as_bool(_case_subject);
#line 789 "/src/package-manifest.do"
                    (sandbox = value);
            }
            else {
#line 790 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.sandbox must be a boolean")) };
            }
            }
        }
#line 793 "/src/package-manifest.do"
        if (manifestJsonHas(macos, std::string("entitlements"))) {
#line 794 "/src/package-manifest.do"
            auto _try_value_135 = manifestString(manifestJsonField(macos, std::string("entitlements")), manifestPath, std::string("build.package.macos.entitlements"));
            if (doof::is_failure(_try_value_135)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_135))};
            const auto value = doof::success_value(_try_value_135);
#line 795 "/src/package-manifest.do"
            (entitlementsPath = manifestJoinPath(rootDirectory, value));
#line 796 "/src/package-manifest.do"
            if (!manifestPathWithinRoot(entitlementsPath, rootDirectory)) {
#line 797 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.entitlements must stay within the package root")) };
            }
        }
    }
#line 801 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
}
#line 804 "/src/package-manifest.do"
doof::Result<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>, std::string> parseIOSPackage(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
#line 805 "/src/package-manifest.do"
    auto identity = std::string("");
#line 806 "/src/package-manifest.do"
    auto provisioningProfilePath = std::string("");
#line 807 "/src/package-manifest.do"
    if (!manifestJsonHas(root, std::string("build"))) {
#line 807 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
#line 808 "/src/package-manifest.do"
    auto _try_value_136 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_136)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_136))};
    const auto build = doof::success_value(_try_value_136);
#line 809 "/src/package-manifest.do"
    if (!manifestJsonHas(build, std::string("package"))) {
#line 809 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
#line 810 "/src/package-manifest.do"
    auto _try_value_137 = manifestObject(manifestJsonField(build, std::string("package")), manifestPath, std::string("build.package"));
    if (doof::is_failure(_try_value_137)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_137))};
    const auto package = doof::success_value(_try_value_137);
#line 811 "/src/package-manifest.do"
    if (!manifestJsonHas(package, std::string("ios"))) {
#line 811 "/src/package-manifest.do"
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
#line 812 "/src/package-manifest.do"
    auto _try_value_138 = manifestObject(manifestJsonField(package, std::string("ios")), manifestPath, std::string("build.package.ios"));
    if (doof::is_failure(_try_value_138)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_138))};
    const auto ios = doof::success_value(_try_value_138);
#line 813 "/src/package-manifest.do"
    if (manifestJsonHas(ios, std::string("identity"))) {
#line 814 "/src/package-manifest.do"
        auto _try_value_139 = manifestString(manifestJsonField(ios, std::string("identity")), manifestPath, std::string("build.package.ios.identity"));
        if (doof::is_failure(_try_value_139)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_139))};
        const auto value = doof::success_value(_try_value_139);
#line 815 "/src/package-manifest.do"
        (identity = value);
    }
#line 817 "/src/package-manifest.do"
    if (manifestJsonHas(ios, std::string("provisioningProfile"))) {
#line 818 "/src/package-manifest.do"
        auto _try_value_140 = manifestString(manifestJsonField(ios, std::string("provisioningProfile")), manifestPath, std::string("build.package.ios.provisioningProfile"));
        if (doof::is_failure(_try_value_140)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_140))};
        const auto value = doof::success_value(_try_value_140);
#line 819 "/src/package-manifest.do"
        (provisioningProfilePath = manifestJoinPath(rootDirectory, value));
#line 820 "/src/package-manifest.do"
        if (!manifestPathWithinRoot(provisioningProfilePath, rootDirectory)) {
#line 821 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.ios.provisioningProfile must stay within the package root")) };
        }
    }
#line 824 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(identity, provisioningProfilePath) };
}
#line 827 "/src/package-manifest.do"
doof::Result<std::string, std::string> optionalManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& key, const std::string& fallback, const std::string& manifestPath, const std::string& fieldPath) {
#line 828 "/src/package-manifest.do"
    if (!manifestJsonHas(object, key)) {
#line 828 "/src/package-manifest.do"
        return doof::Success<std::string>{ fallback };
    }
#line 829 "/src/package-manifest.do"
    return manifestString(manifestJsonField(object, key), manifestPath, fieldPath);
}
#line 832 "/src/package-manifest.do"
doof::Result<std::string, std::string> firstManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& first, const std::string& firstKey, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& second, const std::string& secondKey, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& third, const std::string& thirdKey, const std::string& fallback, const std::string& manifestPath, const std::string& fieldPath) {
#line 840 "/src/package-manifest.do"
    if (manifestJsonHas(first, firstKey)) {
#line 840 "/src/package-manifest.do"
        return manifestString(manifestJsonField(first, firstKey), manifestPath, firstKey);
    }
#line 841 "/src/package-manifest.do"
    if (manifestJsonHas(second, secondKey)) {
#line 841 "/src/package-manifest.do"
        return manifestString(manifestJsonField(second, secondKey), manifestPath, fieldPath);
    }
#line 842 "/src/package-manifest.do"
    if (manifestJsonHas(third, thirdKey)) {
#line 842 "/src/package-manifest.do"
        return manifestString(manifestJsonField(third, thirdKey), manifestPath, thirdKey);
    }
#line 843 "/src/package-manifest.do"
    return doof::Success<std::string>{ fallback };
}
#line 846 "/src/package-manifest.do"
std::string sanitizeBundleName(const std::string& value) {
#line 847 "/src/package-manifest.do"
    const auto allowed = std::string("abcdefghijklmnopqrstuvwxyz0123456789-");
#line 848 "/src/package-manifest.do"
    auto result = std::string("");
#line 849 "/src/package-manifest.do"
    const auto lower = doof::string_toLowerCase(value);
#line 850 "/src/package-manifest.do"
    for (int32_t index = 0; index < static_cast<int32_t>(lower.size()); ++index) {
#line 851 "/src/package-manifest.do"
        const auto text = doof::string_substring(lower, index, (index + 1));
#line 852 "/src/package-manifest.do"
        (result = (result + (doof::string_contains(allowed, text) ? text : std::string("-"))));
    }
#line 854 "/src/package-manifest.do"
    while (doof::string_startsWith(result, std::string("-"))) {
#line 854 "/src/package-manifest.do"
        (result = doof::string_substring(result, 1, static_cast<int32_t>(result.size())));
    }
#line 855 "/src/package-manifest.do"
    while (doof::string_endsWith(result, std::string("-"))) {
#line 855 "/src/package-manifest.do"
        (result = doof::string_substring(result, 0, (static_cast<int32_t>(result.size()) - 1)));
    }
#line 856 "/src/package-manifest.do"
    return ((result == std::string("")) ? std::string("app") : result);
}
#line 859 "/src/package-manifest.do"
bool manifestPathWithinRoot(const std::string& path, const std::string& rootDirectory) {
#line 860 "/src/package-manifest.do"
    const auto boundary = (doof::string_endsWith(rootDirectory, std::string("/")) ? rootDirectory : (rootDirectory + std::string("/")));
#line 861 "/src/package-manifest.do"
    return ((path == rootDirectory) || doof::string_startsWith(path, boundary));
}
#line 864 "/src/package-manifest.do"
bool isManagedMacOSPlistKey(const std::string& key) {
#line 865 "/src/package-manifest.do"
    const auto keys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("CFBundleDevelopmentRegion"), std::string("CFBundleDisplayName"), std::string("CFBundleExecutable"), std::string("CFBundleIconFile"), std::string("CFBundleIdentifier"), std::string("CFBundleInfoDictionaryVersion"), std::string("CFBundleName"), std::string("CFBundlePackageType"), std::string("CFBundleShortVersionString"), std::string("CFBundleVersion"), std::string("LSApplicationCategoryType"), std::string("LSMinimumSystemVersion"), std::string("NSHighResolutionCapable"), std::string("NSPrincipalClass")});
#line 871 "/src/package-manifest.do"
    return doof::array_contains(keys, key, "", 0);
}
#line 874 "/src/package-manifest.do"
bool isManagedIOSPlistKey(const std::string& key) {
#line 875 "/src/package-manifest.do"
    const auto keys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("CFBundleDevelopmentRegion"), std::string("CFBundleDisplayName"), std::string("CFBundleExecutable"), std::string("CFBundleIdentifier"), std::string("CFBundleInfoDictionaryVersion"), std::string("CFBundleName"), std::string("CFBundlePackageType"), std::string("CFBundleShortVersionString"), std::string("CFBundleVersion"), std::string("LSRequiresIPhoneOS"), std::string("MinimumOSVersion"), std::string("UIDeviceFamily"), std::string("UILaunchStoryboardName"), std::string("UIApplicationSceneManifest")});
#line 881 "/src/package-manifest.do"
    return doof::array_contains(keys, key, "", 0);
}
#line 884 "/src/package-manifest.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseResourceArray(const doof::JsonValue& value, const std::string& manifestPath, const std::string& rootDirectory, const std::string& fieldPath) {
#line 890 "/src/package-manifest.do"
    auto _try_value_142 = manifestArray(value, manifestPath, fieldPath);
    if (doof::is_failure(_try_value_142)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_142))};
    const auto entries = doof::success_value(_try_value_142);
#line 891 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources = std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{});
#line 892 "/src/package-manifest.do"
    for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
#line 893 "/src/package-manifest.do"
        auto source = std::string("");
#line 894 "/src/package-manifest.do"
        auto destination = std::string("");
#line 895 "/src/package-manifest.do"
        {
            auto _case_subject = doof::array_at(entries, index, "src/package-manifest", 895);
            if (doof::json_is_string(_case_subject)) {
                const auto text = doof::json_as_string(_case_subject);
#line 897 "/src/package-manifest.do"
                if (text == std::string("")) {
#line 898 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string("[")) + doof::to_string(index)) + std::string("] must not be empty")) };
                }
#line 900 "/src/package-manifest.do"
                (source = text);
#line 901 "/src/package-manifest.do"
                (destination = text);
        }
        else if (doof::json_is_object(_case_subject)) {
                const auto object = doof::json_object(_case_subject);
#line 904 "/src/package-manifest.do"
                if (!manifestJsonHas(object, std::string("from")) || !manifestJsonHas(object, std::string("to"))) {
#line 905 "/src/package-manifest.do"
                    return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string("[")) + doof::to_string(index)) + std::string("] requires string fields from and to")) };
                }
#line 907 "/src/package-manifest.do"
                auto _try_value_144 = manifestString(manifestJsonField(object, std::string("from")), manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].from")));
                if (doof::is_failure(_try_value_144)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_144))};
                const auto parsedSource = doof::success_value(_try_value_144);
#line 912 "/src/package-manifest.do"
                auto _try_value_145 = manifestString(manifestJsonField(object, std::string("to")), manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].to")));
                if (doof::is_failure(_try_value_145)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_145))};
                const auto parsedDestination = doof::success_value(_try_value_145);
#line 917 "/src/package-manifest.do"
                (source = parsedSource);
#line 918 "/src/package-manifest.do"
                (destination = parsedDestination);
        }
        else {
#line 920 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string("[")) + doof::to_string(index)) + std::string("] must be a string or object")) };
        }
        }
#line 923 "/src/package-manifest.do"
        const auto sourcePath = manifestJoinPath(rootDirectory, source);
#line 924 "/src/package-manifest.do"
        const auto rootBoundary = (doof::string_endsWith(rootDirectory, std::string("/")) ? rootDirectory : (rootDirectory + std::string("/")));
#line 925 "/src/package-manifest.do"
        if ((sourcePath != rootDirectory) && !doof::string_startsWith(sourcePath, rootBoundary)) {
#line 926 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string("[")) + doof::to_string(index)) + std::string("].from must stay within the package root")) };
        }
#line 928 "/src/package-manifest.do"
        auto _try_value_146 = normalizeResourceDestination(destination, manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].to")));
        if (doof::is_failure(_try_value_146)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_146))};
        const auto normalizedDestination = doof::success_value(_try_value_146);
#line 933 "/src/package-manifest.do"
        resources->push_back(std::make_shared<PackageResource>(sourcePath, normalizedDestination));
    }
#line 935 "/src/package-manifest.do"
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>>{ resources };
}
#line 938 "/src/package-manifest.do"
doof::Result<std::string, std::string> normalizeResourceDestination(const std::string& destination, const std::string& manifestPath, const std::string& fieldPath) {
#line 943 "/src/package-manifest.do"
    const auto portable = doof::string_replaceAll(destination, std::string("\\"), std::string("/"));
#line 944 "/src/package-manifest.do"
    if (doof::string_startsWith(portable, std::string("/")) || (((static_cast<int32_t>(portable.size()) >= 3) && (doof::string_at(portable, 1, "src/package-manifest", 944) == U'\u003A')) && (doof::string_at(portable, 2, "src/package-manifest", 944) == U'\u002F'))) {
#line 945 "/src/package-manifest.do"
        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be relative")) };
    }
#line 948 "/src/package-manifest.do"
    std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 949 "/src/package-manifest.do"
    const auto& _iterable_148 = doof::string_split(portable, std::string("/"));
    for (const auto& segment : *_iterable_148) {
#line 950 "/src/package-manifest.do"
        if ((segment == std::string("")) || (segment == std::string("."))) {
#line 950 "/src/package-manifest.do"
            continue;
        }
#line 951 "/src/package-manifest.do"
        if (segment == std::string("..")) {
#line 952 "/src/package-manifest.do"
            if (static_cast<int32_t>((segments)->size()) == 0) {
#line 953 "/src/package-manifest.do"
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must stay within the executable resource directory")) };
            }
#line 955 "/src/package-manifest.do"
            const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(segments); if (doof::is_failure(_try_value)) doof::panic_at("src/package-manifest", 955, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 956 "/src/package-manifest.do"
            continue;
        }
#line 958 "/src/package-manifest.do"
        segments->push_back(segment);
    }
#line 960 "/src/package-manifest.do"
    auto normalized = std::string("");
#line 961 "/src/package-manifest.do"
    const auto& _iterable_150 = segments;
    for (const auto& segment : *_iterable_150) {
#line 962 "/src/package-manifest.do"
        if (normalized != std::string("")) {
#line 962 "/src/package-manifest.do"
            (normalized = (normalized + std::string("/")));
        }
#line 963 "/src/package-manifest.do"
        (normalized = (normalized + segment));
    }
#line 965 "/src/package-manifest.do"
    return doof::Success<std::string>{ normalized };
}
#line 968 "/src/package-manifest.do"
doof::Result<void, std::string> appendNativeFragment(const std::shared_ptr<NativeBuildPlan>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& fragment, const std::string& manifestPath, const std::string& rootDirectory, const std::string& fieldPath) {
#line 975 "/src/package-manifest.do"
    auto _try_value_151 = appendStringArrayField(target->includePaths, fragment, std::string("includePaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_151)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_151))};
#line 976 "/src/package-manifest.do"
    auto _try_value_152 = appendStringArrayField(target->sourceFiles, fragment, std::string("sourceFiles"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_152)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_152))};
#line 977 "/src/package-manifest.do"
    auto _try_value_153 = appendStringArrayField(target->libraryPaths, fragment, std::string("libraryPaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_153)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_153))};
#line 978 "/src/package-manifest.do"
    auto _try_value_154 = appendStringArrayField(target->extraCopyPaths, fragment, std::string("extraCopyPaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_154)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_154))};
#line 979 "/src/package-manifest.do"
    auto _try_value_155 = appendStringArrayField(target->linkLibraries, fragment, std::string("linkLibraries"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_155)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_155))};
#line 980 "/src/package-manifest.do"
    auto _try_value_156 = appendStringArrayField(target->frameworks, fragment, std::string("frameworks"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_156)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_156))};
#line 981 "/src/package-manifest.do"
    auto _try_value_157 = appendStringArrayField(target->pkgConfigPackages, fragment, std::string("pkgConfigPackages"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_157)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_157))};
#line 982 "/src/package-manifest.do"
    auto _try_value_158 = appendStringArrayField(target->defines, fragment, std::string("defines"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_158)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_158))};
#line 983 "/src/package-manifest.do"
    auto _try_value_159 = appendStringArrayField(target->compilerFlags, fragment, std::string("compilerFlags"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_159)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_159))};
#line 984 "/src/package-manifest.do"
    auto _try_value_160 = appendStringArrayField(target->linkerFlags, fragment, std::string("linkerFlags"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_160)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_160))};
#line 985 "/src/package-manifest.do"
    return doof::Success<void>{};
}
#line 988 "/src/package-manifest.do"
doof::Result<void, std::string> appendStringArrayField(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath, const std::string& pathRoot) {
#line 996 "/src/package-manifest.do"
    if (!manifestJsonHas(object, name)) {
#line 996 "/src/package-manifest.do"
        return doof::Success<void>{};
    }
#line 997 "/src/package-manifest.do"
    auto _try_value_161 = manifestArray(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_161)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_161))};
    const auto values = doof::success_value(_try_value_161);
#line 998 "/src/package-manifest.do"
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
#line 999 "/src/package-manifest.do"
        auto _try_value_163 = manifestString(doof::array_at(values, index, "src/package-manifest", 1000), manifestPath, (((((fieldPath + std::string(".")) + name) + std::string("[")) + doof::to_string(index)) + std::string("]")));
        if (doof::is_failure(_try_value_163)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_163))};
        const auto value = doof::success_value(_try_value_163);
#line 1004 "/src/package-manifest.do"
        const auto normalized = ((pathRoot == std::string("")) ? value : manifestJoinPath(pathRoot, value));
#line 1005 "/src/package-manifest.do"
        appendUnique(target, normalized);
    }
#line 1007 "/src/package-manifest.do"
    return doof::Success<void>{};
}
#line 1010 "/src/package-manifest.do"
void appendNativeBuild(const std::shared_ptr<NativeBuildPlan>& target, const std::shared_ptr<NativeBuildPlan>& source) {
#line 1011 "/src/package-manifest.do"
    appendUniqueValues(target->includePaths, source->includePaths);
#line 1012 "/src/package-manifest.do"
    appendUniqueValues(target->sourceFiles, source->sourceFiles);
#line 1013 "/src/package-manifest.do"
    appendUniqueValues(target->libraryPaths, source->libraryPaths);
#line 1014 "/src/package-manifest.do"
    appendUniqueValues(target->extraCopyPaths, source->extraCopyPaths);
#line 1015 "/src/package-manifest.do"
    appendUniqueValues(target->linkLibraries, source->linkLibraries);
#line 1016 "/src/package-manifest.do"
    appendUniqueValues(target->frameworks, source->frameworks);
#line 1017 "/src/package-manifest.do"
    appendUniqueValues(target->pkgConfigPackages, source->pkgConfigPackages);
#line 1018 "/src/package-manifest.do"
    appendUniqueValues(target->defines, source->defines);
#line 1019 "/src/package-manifest.do"
    appendUniqueValues(target->compilerFlags, source->compilerFlags);
#line 1020 "/src/package-manifest.do"
    appendUniqueValues(target->linkerFlags, source->linkerFlags);
}
#line 1023 "/src/package-manifest.do"
void appendUniqueValues(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<std::vector<std::string>>& values) {
#line 1024 "/src/package-manifest.do"
    const auto& _iterable_165 = values;
    for (const auto& value : *_iterable_165) {
#line 1024 "/src/package-manifest.do"
        appendUnique(target, value);
    }
}
#line 1027 "/src/package-manifest.do"
void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value) {
#line 1028 "/src/package-manifest.do"
    const auto& _iterable_167 = target;
    for (const auto& existing : *_iterable_167) {
#line 1028 "/src/package-manifest.do"
        if (existing == value) {
#line 1028 "/src/package-manifest.do"
            return;
        }
    }
#line 1029 "/src/package-manifest.do"
    target->push_back(value);
}
#line 1032 "/src/package-manifest.do"
doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> manifestObject(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath) {
#line 1033 "/src/package-manifest.do"
    {
        auto _case_subject = value;
        if (doof::json_is_object(_case_subject)) {
            const auto object = doof::json_object(_case_subject);
#line 1034 "/src/package-manifest.do"
            return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{ object };
    }
    else {
#line 1035 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be an object")) };
    }
    }
    doof::unreachable();
}
#line 1039 "/src/package-manifest.do"
doof::Result<std::shared_ptr<std::vector<doof::JsonValue>>, std::string> manifestArray(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath) {
#line 1040 "/src/package-manifest.do"
    {
        auto _case_subject = value;
        if (doof::json_is_array(_case_subject)) {
            const auto array = std::get<doof::JsonArray>(doof::json_storage(_case_subject));
#line 1041 "/src/package-manifest.do"
            return doof::Success<std::shared_ptr<std::vector<doof::JsonValue>>>{ array };
    }
    else {
#line 1042 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be an array")) };
    }
    }
    doof::unreachable();
}
#line 1046 "/src/package-manifest.do"
doof::Result<std::string, std::string> manifestString(const doof::JsonValue& value, const std::string& manifestPath, const std::string& fieldPath) {
#line 1047 "/src/package-manifest.do"
    {
        auto _case_subject = value;
        if (doof::json_is_string(_case_subject)) {
            const auto text = doof::json_as_string(_case_subject);
#line 1048 "/src/package-manifest.do"
            return doof::Success<std::string>{ text };
    }
    else {
#line 1049 "/src/package-manifest.do"
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be a string")) };
    }
    }
    doof::unreachable();
}
#line 1 "<doof-generated>"
}
