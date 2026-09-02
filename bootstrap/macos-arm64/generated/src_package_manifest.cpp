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
    if (manifestJsonHas(root, std::string("externalDependencies"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": externalDependencies is no longer supported; prepare third-party sources outside Doof")) };
    }
    if (manifestJsonHas(root, std::string("resolutions"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": resolutions is no longer supported because Doof only accepts local path dependencies")) };
    }
    if (manifestJsonHas(root, std::string("policy"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": dependency policy is no longer supported because Doof performs no remote acquisition")) };
    }
    auto _try_value_8 = parseStdlibPreparation(root, manifestPath);
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
    const auto stdlibPreparation = doof::success_value(_try_value_8);
    auto _try_value_9 = parseManifestTarget(root, manifestPath);
    if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
    const auto manifestTarget = doof::success_value(_try_value_9);
    const auto target = ((targetOverride == std::string("")) ? manifestTarget : targetOverride);
    auto _try_value_10 = parseManifestNativeBuild(root, manifestPath, rootDirectory, platform, target);
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_10))};
    const auto nativeBuild = doof::success_value(_try_value_10);
    auto _try_value_11 = parseMacOSApp(root, manifestPath, rootDirectory, name, version, target);
    if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_11))};
    const auto macosApp = doof::success_value(_try_value_11);
    auto _try_value_12 = parseIOSApp(root, manifestPath, rootDirectory, name, version, target);
    if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
    const auto iosApp = doof::success_value(_try_value_12);
    auto _try_value_13 = parseMacOSPackage(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
    const auto packageConfig = doof::success_value(_try_value_13);
    auto _try_value_14 = parseIOSPackage(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
    const auto iosPackageConfig = doof::success_value(_try_value_14);
    return doof::Success<std::shared_ptr<PackageManifest>>{ std::make_shared<PackageManifest>(name, version, manifestPath, rootDirectory, resources, dependencies, stdlibPreparation, nativeBuild, target, macosApp, iosApp, packageConfig, iosPackageConfig) };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>, std::string> parsePackageDependencies(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
    if (!manifestJsonHas(root, std::string("dependencies"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>>{ std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{}) };
    }
    auto _try_value_15 = manifestObject(manifestJsonField(root, std::string("dependencies")), manifestPath, std::string("dependencies"));
    if (doof::is_failure(_try_value_15)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_15))};
    const auto values = doof::success_value(_try_value_15);
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> result = std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{});
    const auto& _iterable_19 = values;
    for (const auto& [name, value] : *_iterable_19) {
        const auto fieldPath = (std::string("dependencies.") + name);
        if (name == std::string("")) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": dependency names must not be empty")) };
        }
        auto _try_value_16 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_16))};
        const auto object = doof::success_value(_try_value_16);
        if ((manifestJsonHas(object, std::string("url")) || manifestJsonHas(object, std::string("ref"))) || manifestJsonHas(object, std::string("commit"))) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must use a local path; remote package acquisition is no longer supported")) };
        }
        auto _try_value_17 = requiredManifestString(object, std::string("path"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_17)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_17))};
        const auto path = doof::success_value(_try_value_17);
        result->push_back(std::make_shared<PackageDependency>(name, manifestJoinPath(rootDirectory, path)));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>>{ result };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>>, std::string> parseStdlibPreparation(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath) {
    if (!manifestJsonHas(root, std::string("build"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>>>{ std::make_shared<std::vector<std::shared_ptr<StdlibPreparationCommand>>>(std::vector<std::shared_ptr<StdlibPreparationCommand>>{}) };
    }
    auto _try_value_20 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_20)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_20))};
    const auto build = doof::success_value(_try_value_20);
    if (!manifestJsonHas(build, std::string("stdlib"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>>>{ std::make_shared<std::vector<std::shared_ptr<StdlibPreparationCommand>>>(std::vector<std::shared_ptr<StdlibPreparationCommand>>{}) };
    }
    auto _try_value_21 = manifestObject(manifestJsonField(build, std::string("stdlib")), manifestPath, std::string("build.stdlib"));
    if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_21))};
    const auto stdlib = doof::success_value(_try_value_21);
    if (!manifestJsonHas(stdlib, std::string("prepare"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>>>{ std::make_shared<std::vector<std::shared_ptr<StdlibPreparationCommand>>>(std::vector<std::shared_ptr<StdlibPreparationCommand>>{}) };
    }
    return parsePreparationCommands(stdlib, std::string("prepare"), manifestPath, std::string("build.stdlib"));
}
doof::Result<std::string, std::string> requiredManifestString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath) {
    if (!manifestJsonHas(object, name)) {
        return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" is required")) };
    }
    auto _try_value_22 = manifestString(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_22))};
    const auto value = doof::success_value(_try_value_22);
    if (value == std::string("")) {
        return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" must not be empty")) };
    }
    return doof::Success<std::string>{ value };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>>, std::string> parsePreparationCommands(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath) {
    auto _try_value_23 = manifestArray(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_23))};
    const auto values = doof::success_value(_try_value_23);
    std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>> result = std::make_shared<std::vector<std::shared_ptr<StdlibPreparationCommand>>>(std::vector<std::shared_ptr<StdlibPreparationCommand>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        const auto entryPath = (((((fieldPath + std::string(".")) + name) + std::string("[")) + doof::to_string(index)) + std::string("]"));
        auto _try_value_24 = manifestObject(doof::array_at(values, index, "src/package-manifest", 172), manifestPath, entryPath);
        if (doof::is_failure(_try_value_24)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_24))};
        const auto entry = doof::success_value(_try_value_24);
        auto _try_value_25 = requiredManifestString(entry, std::string("program"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_25))};
        const auto program = doof::success_value(_try_value_25);
        std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        if (manifestJsonHas(entry, std::string("args"))) {
            auto _try_value_26 = manifestArray(manifestJsonField(entry, std::string("args")), manifestPath, (entryPath + std::string(".args")));
            if (doof::is_failure(_try_value_26)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_26))};
            const auto entries = doof::success_value(_try_value_26);
            for (int32_t argumentIndex = 0; argumentIndex < static_cast<int32_t>((entries)->size()); ++argumentIndex) {
                auto _try_value_27 = manifestString(doof::array_at(entries, argumentIndex, "src/package-manifest", 178), manifestPath, (((entryPath + std::string(".args[")) + doof::to_string(argumentIndex)) + std::string("]")));
                if (doof::is_failure(_try_value_27)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_27))};
                const auto argument = doof::success_value(_try_value_27);
                args->push_back(argument);
            }
        }
        std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
        if (manifestJsonHas(entry, std::string("env"))) {
            auto _try_value_29 = manifestObject(manifestJsonField(entry, std::string("env")), manifestPath, (entryPath + std::string(".env")));
            if (doof::is_failure(_try_value_29)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_29))};
            const auto entries = doof::success_value(_try_value_29);
            const auto& _iterable_32 = entries;
            for (const auto& [key, value] : *_iterable_32) {
                if (key == std::string("")) {
                    return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + entryPath) + std::string(".env keys must not be empty")) };
                }
                auto _try_value_30 = manifestString(value, manifestPath, ((entryPath + std::string(".env.")) + key));
                if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_30))};
                const auto text = doof::success_value(_try_value_30);
                doof::map_set(env, key, text, "", 0);
            }
        }
        auto workingDirectory = std::string("");
        if (manifestJsonHas(entry, std::string("workingDirectory"))) {
            auto _try_value_33 = manifestString(manifestJsonField(entry, std::string("workingDirectory")), manifestPath, (entryPath + std::string(".workingDirectory")));
            if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_33))};
            const auto parsed = doof::success_value(_try_value_33);
            if (parsed == std::string("")) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + entryPath) + std::string(".workingDirectory must not be empty")) };
            }
            (workingDirectory = parsed);
        }
        result->push_back(std::make_shared<StdlibPreparationCommand>(program, args, env, workingDirectory));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<StdlibPreparationCommand>>>>{ result };
}
doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> parseManifestNativeBuild(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory, const std::string& platform, const std::string& target) {
    const auto result = std::make_shared<NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    if (!manifestJsonHas(root, std::string("build"))) {
        return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
    }
    auto _try_value_35 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_35)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_35))};
    const auto build = doof::success_value(_try_value_35);
    if (!manifestJsonHas(build, std::string("native"))) {
        return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
    }
    auto _try_value_36 = manifestObject(manifestJsonField(build, std::string("native")), manifestPath, std::string("build.native"));
    if (doof::is_failure(_try_value_36)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_36))};
    const auto native = doof::success_value(_try_value_36);
    auto _try_value_37 = appendNativeFragment(result, native, manifestPath, rootDirectory, std::string("build.native"));
    if (doof::is_failure(_try_value_37)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_37))};
    const auto platformKey = ((target == std::string("wasm")) ? std::string("wasm") : ((platform == std::string("ios-simulator")) ? std::string("iosSimulator") : ((platform == std::string("ios-device")) ? std::string("iosDevice") : platform)));
    if ((platformKey != std::string("")) && manifestJsonHas(native, platformKey)) {
        auto _try_value_38 = manifestObject(manifestJsonField(native, platformKey), manifestPath, (std::string("build.native.") + platformKey));
        if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
        const auto platformValue = doof::success_value(_try_value_38);
        auto _try_value_39 = appendNativeFragment(result, platformValue, manifestPath, rootDirectory, (std::string("build.native.") + platformKey));
        if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_39))};
    }
    return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseManifestResources(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& root, const std::string& manifestPath, const std::string& rootDirectory) {
    if (manifestJsonHas(root, std::string("resources"))) {
        return parseResourceArray(manifestJsonField(root, std::string("resources")), manifestPath, rootDirectory, std::string("resources"));
    }
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_40 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_40)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_40))};
        const auto build = doof::success_value(_try_value_40);
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
        auto _try_value_41 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_41))};
        const auto build = doof::success_value(_try_value_41);
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
        auto _try_value_42 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_42)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_42))};
        const auto parsedBuild = doof::success_value(_try_value_42);
        (build = parsedBuild);
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> nested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(build, std::string("macosApp"))) {
        auto _try_value_43 = manifestObject(manifestJsonField(build, std::string("macosApp")), manifestPath, std::string("build.macosApp"));
        if (doof::is_failure(_try_value_43)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_43))};
        const auto parsedNested = doof::success_value(_try_value_43);
        (nested = parsedNested);
    }
    auto _try_value_44 = firstManifestString(root, std::string("executable"), build, std::string("executable"), build, std::string("targetExecutableName"), packageName, manifestPath, std::string("executable"));
    if (doof::is_failure(_try_value_44)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_44))};
    const auto executableName = doof::success_value(_try_value_44);
    if (((executableName == std::string("")) || doof::string_contains(executableName, std::string("/"))) || doof::string_contains(executableName, std::string("\\"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": executable must be a file name without path separators")) };
    }
    const auto defaultBundleId = (std::string("dev.doof.") + sanitizeBundleName(((packageName == std::string("")) ? executableName : packageName)));
    auto _try_value_45 = firstManifestString(root, std::string("id"), nested, std::string("bundleId"), build, std::string("id"), defaultBundleId, manifestPath, std::string("build.macosApp.bundleId"));
    if (doof::is_failure(_try_value_45)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_45))};
    const auto bundleId = doof::success_value(_try_value_45);
    auto _try_value_46 = firstManifestString(root, std::string("title"), nested, std::string("displayName"), build, std::string("title"), ((packageName == std::string("")) ? executableName : packageName), manifestPath, std::string("build.macosApp.displayName"));
    if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_46))};
    const auto displayName = doof::success_value(_try_value_46);
    auto _try_value_47 = optionalManifestString(nested, std::string("version"), packageVersion, manifestPath, std::string("build.macosApp.version"));
    if (doof::is_failure(_try_value_47)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_47))};
    const auto version = doof::success_value(_try_value_47);
    auto _try_value_48 = optionalManifestString(nested, std::string("category"), std::string("public.app-category.developer-tools"), manifestPath, std::string("build.macosApp.category"));
    if (doof::is_failure(_try_value_48)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_48))};
    const auto category = doof::success_value(_try_value_48);
    auto _try_value_49 = optionalManifestString(nested, std::string("minimumSystemVersion"), std::string("11.0"), manifestPath, std::string("build.macosApp.minimumSystemVersion"));
    if (doof::is_failure(_try_value_49)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_49))};
    const auto minimumSystemVersion = doof::success_value(_try_value_49);
    auto icon = std::string("");
    if (manifestJsonHas(root, std::string("icon"))) {
        auto _try_value_50 = manifestString(manifestJsonField(root, std::string("icon")), manifestPath, std::string("icon"));
        if (doof::is_failure(_try_value_50)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_50))};
        const auto parsed = doof::success_value(_try_value_50);
        (icon = parsed);
    } else if (manifestJsonHas(nested, std::string("icon"))) {
        auto _try_value_51 = manifestString(manifestJsonField(nested, std::string("icon")), manifestPath, std::string("build.macosApp.icon"));
        if (doof::is_failure(_try_value_51)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_51))};
        const auto parsed = doof::success_value(_try_value_51);
        (icon = parsed);
    } else if (manifestJsonHas(build, std::string("icon"))) {
        auto _try_value_52 = manifestString(manifestJsonField(build, std::string("icon")), manifestPath, std::string("build.icon"));
        if (doof::is_failure(_try_value_52)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_52))};
        const auto parsed = doof::success_value(_try_value_52);
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
        auto _try_value_53 = manifestObject(manifestJsonField(nested, std::string("infoPlist")), manifestPath, std::string("build.macosApp.infoPlist"));
        if (doof::is_failure(_try_value_53)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_53))};
        const auto parsedInfo = doof::success_value(_try_value_53);
        const auto& _iterable_55 = parsedInfo;
        for (const auto& [key, ignored] : *_iterable_55) {
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
        auto _try_value_56 = parseResourceArray(std::get<doof::JsonValue>(resourceValue), manifestPath, rootDirectory, resourceField);
        if (doof::is_failure(_try_value_56)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_56))};
        const auto parsedResources = doof::success_value(_try_value_56);
        const auto& _iterable_58 = parsedResources;
        for (const auto& resource : *_iterable_58) {
            resources->push_back(std::make_shared<::app_src_macos_app_::MacOSAppResource>(resource->sourcePath, resource->destination));
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>{});
    if (manifestJsonHas(nested, std::string("embeddedLibraries"))) {
        auto _try_value_59 = manifestArray(manifestJsonField(nested, std::string("embeddedLibraries")), manifestPath, std::string("build.macosApp.embeddedLibraries"));
        if (doof::is_failure(_try_value_59)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_59))};
        const auto entries = doof::success_value(_try_value_59);
        for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
            auto _try_value_60 = manifestObject(doof::array_at(entries, index, "src/package-manifest", 353), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("]")));
            if (doof::is_failure(_try_value_60)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_60))};
            const auto entry = doof::success_value(_try_value_60);
            const auto hasLibrary = manifestJsonHas(entry, std::string("library"));
            const auto hasPath = manifestJsonHas(entry, std::string("path"));
            if (hasLibrary == hasPath) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.embeddedLibraries[")) + doof::to_string(index)) + std::string("] requires exactly one of library or path")) };
            }
            if (hasLibrary) {
                auto _try_value_61 = manifestString(manifestJsonField(entry, std::string("library")), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("].library")));
                if (doof::is_failure(_try_value_61)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_61))};
                const auto library = doof::success_value(_try_value_61);
                if (((library == std::string("")) || doof::string_contains(library, std::string("/"))) || doof::string_contains(library, std::string("\\"))) {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded linked library names must not contain path separators")) };
                }
                embeddedLibraries->push_back(std::make_shared<::app_src_macos_app_::MacOSEmbeddedLibrary>(library, std::string("")));
            } else {
                auto _try_value_62 = manifestString(manifestJsonField(entry, std::string("path")), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("].path")));
                if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_62))};
                const auto path = doof::success_value(_try_value_62);
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
        auto _try_value_64 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_64)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_64))};
        const auto parsedBuild = doof::success_value(_try_value_64);
        (build = parsedBuild);
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> nested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(build, std::string("iosApp"))) {
        auto _try_value_65 = manifestObject(manifestJsonField(build, std::string("iosApp")), manifestPath, std::string("build.iosApp"));
        if (doof::is_failure(_try_value_65)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_65))};
        const auto parsedNested = doof::success_value(_try_value_65);
        (nested = parsedNested);
    }
    auto _try_value_66 = firstManifestString(root, std::string("executable"), build, std::string("executable"), build, std::string("targetExecutableName"), packageName, manifestPath, std::string("executable"));
    if (doof::is_failure(_try_value_66)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_66))};
    const auto executableName = doof::success_value(_try_value_66);
    if (((executableName == std::string("")) || doof::string_contains(executableName, std::string("/"))) || doof::string_contains(executableName, std::string("\\"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": executable must be a file name without path separators")) };
    }
    const auto defaultBundleId = (std::string("dev.doof.") + sanitizeBundleName(((packageName == std::string("")) ? executableName : packageName)));
    auto _try_value_67 = firstManifestString(root, std::string("id"), nested, std::string("bundleId"), build, std::string("id"), defaultBundleId, manifestPath, std::string("build.iosApp.bundleId"));
    if (doof::is_failure(_try_value_67)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_67))};
    const auto bundleId = doof::success_value(_try_value_67);
    auto _try_value_68 = firstManifestString(root, std::string("title"), nested, std::string("displayName"), build, std::string("title"), ((packageName == std::string("")) ? executableName : packageName), manifestPath, std::string("build.iosApp.displayName"));
    if (doof::is_failure(_try_value_68)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_68))};
    const auto displayName = doof::success_value(_try_value_68);
    auto _try_value_69 = optionalManifestString(nested, std::string("version"), packageVersion, manifestPath, std::string("build.iosApp.version"));
    if (doof::is_failure(_try_value_69)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_69))};
    const auto version = doof::success_value(_try_value_69);
    auto _try_value_70 = optionalManifestString(nested, std::string("minimumDeploymentTarget"), std::string("16.0"), manifestPath, std::string("build.iosApp.minimumDeploymentTarget"));
    if (doof::is_failure(_try_value_70)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_70))};
    const auto minimumDeploymentTarget = doof::success_value(_try_value_70);
    auto icon = std::string("");
    if (manifestJsonHas(root, std::string("icon"))) {
        auto _try_value_71 = manifestString(manifestJsonField(root, std::string("icon")), manifestPath, std::string("icon"));
        if (doof::is_failure(_try_value_71)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_71))};
        const auto parsed = doof::success_value(_try_value_71);
        (icon = parsed);
    } else if (manifestJsonHas(nested, std::string("icon"))) {
        auto _try_value_72 = manifestString(manifestJsonField(nested, std::string("icon")), manifestPath, std::string("build.iosApp.icon"));
        if (doof::is_failure(_try_value_72)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_72))};
        const auto parsed = doof::success_value(_try_value_72);
        (icon = parsed);
    } else if (manifestJsonHas(build, std::string("icon"))) {
        auto _try_value_73 = manifestString(manifestJsonField(build, std::string("icon")), manifestPath, std::string("build.icon"));
        if (doof::is_failure(_try_value_73)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_73))};
        const auto parsed = doof::success_value(_try_value_73);
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
        auto _try_value_74 = manifestObject(manifestJsonField(nested, std::string("infoPlist")), manifestPath, std::string("build.iosApp.infoPlist"));
        if (doof::is_failure(_try_value_74)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_74))};
        const auto parsedInfo = doof::success_value(_try_value_74);
        const auto& _iterable_76 = parsedInfo;
        for (const auto& [key, ignored] : *_iterable_76) {
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
        auto _try_value_77 = parseResourceArray(std::get<doof::JsonValue>(resourceValue), manifestPath, rootDirectory, resourceField);
        if (doof::is_failure(_try_value_77)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_77))};
        const auto parsedResources = doof::success_value(_try_value_77);
        const auto& _iterable_79 = parsedResources;
        for (const auto& resource : *_iterable_79) {
            resources->push_back(std::make_shared<::app_src_ios_app_::IOSAppResource>(resource->sourcePath, resource->destination));
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>{});
    if (manifestJsonHas(nested, std::string("embeddedLibraries"))) {
        auto _try_value_80 = manifestArray(manifestJsonField(nested, std::string("embeddedLibraries")), manifestPath, std::string("build.iosApp.embeddedLibraries"));
        if (doof::is_failure(_try_value_80)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_80))};
        const auto entries = doof::success_value(_try_value_80);
        for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
            const auto field = ((std::string("build.iosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("]"));
            auto _try_value_81 = manifestObject(doof::array_at(entries, index, "src/package-manifest", 475), manifestPath, field);
            if (doof::is_failure(_try_value_81)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_81))};
            const auto entry = doof::success_value(_try_value_81);
            const auto hasLibrary = manifestJsonHas(entry, std::string("library"));
            const auto hasPath = manifestJsonHas(entry, std::string("path"));
            if (hasLibrary == hasPath) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + field) + std::string(" requires exactly one of library or path")) };
            }
            if (hasLibrary) {
                auto _try_value_82 = manifestString(manifestJsonField(entry, std::string("library")), manifestPath, (field + std::string(".library")));
                if (doof::is_failure(_try_value_82)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_82))};
                const auto library = doof::success_value(_try_value_82);
                if (((library == std::string("")) || doof::string_contains(library, std::string("/"))) || doof::string_contains(library, std::string("\\"))) {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded linked library names must not contain path separators")) };
                }
                embeddedLibraries->push_back(std::make_shared<::app_src_ios_app_::IOSEmbeddedLibrary>(library, std::string("")));
            } else {
                auto _try_value_83 = manifestString(manifestJsonField(entry, std::string("path")), manifestPath, (field + std::string(".path")));
                if (doof::is_failure(_try_value_83)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_83))};
                const auto path = doof::success_value(_try_value_83);
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
    auto _try_value_85 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_85)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_85))};
    const auto build = doof::success_value(_try_value_85);
    if (!manifestJsonHas(build, std::string("package"))) {
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
    }
    auto _try_value_86 = manifestObject(manifestJsonField(build, std::string("package")), manifestPath, std::string("build.package"));
    if (doof::is_failure(_try_value_86)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_86))};
    const auto package = doof::success_value(_try_value_86);
    if (manifestJsonHas(package, std::string("distDir"))) {
        auto _try_value_87 = manifestString(manifestJsonField(package, std::string("distDir")), manifestPath, std::string("build.package.distDir"));
        if (doof::is_failure(_try_value_87)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_87))};
        const auto value = doof::success_value(_try_value_87);
        (distDirectory = manifestJoinPath(rootDirectory, value));
        if (!manifestPathWithinRoot(distDirectory, rootDirectory)) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.distDir must stay within the package root")) };
        }
    }
    if (manifestJsonHas(package, std::string("macos"))) {
        auto _try_value_88 = manifestObject(manifestJsonField(package, std::string("macos")), manifestPath, std::string("build.package.macos"));
        if (doof::is_failure(_try_value_88)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_88))};
        const auto macos = doof::success_value(_try_value_88);
        if (manifestJsonHas(macos, std::string("signing"))) {
            auto _try_value_89 = manifestString(manifestJsonField(macos, std::string("signing")), manifestPath, std::string("build.package.macos.signing"));
            if (doof::is_failure(_try_value_89)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_89))};
            const auto value = doof::success_value(_try_value_89);
            if ((value != std::string("developer-id")) && (value != std::string("ad-hoc"))) {
                return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.signing must be one of \"developer-id\", \"ad-hoc\"")) };
            }
            (signing = value);
        }
        if (manifestJsonHas(macos, std::string("identity"))) {
            auto _try_value_90 = manifestString(manifestJsonField(macos, std::string("identity")), manifestPath, std::string("build.package.macos.identity"));
            if (doof::is_failure(_try_value_90)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_90))};
            const auto value = doof::success_value(_try_value_90);
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
            auto _try_value_91 = manifestString(manifestJsonField(macos, std::string("entitlements")), manifestPath, std::string("build.package.macos.entitlements"));
            if (doof::is_failure(_try_value_91)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_91))};
            const auto value = doof::success_value(_try_value_91);
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
    auto _try_value_92 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_92)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_92))};
    const auto build = doof::success_value(_try_value_92);
    if (!manifestJsonHas(build, std::string("package"))) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
    auto _try_value_93 = manifestObject(manifestJsonField(build, std::string("package")), manifestPath, std::string("build.package"));
    if (doof::is_failure(_try_value_93)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_93))};
    const auto package = doof::success_value(_try_value_93);
    if (!manifestJsonHas(package, std::string("ios"))) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
    auto _try_value_94 = manifestObject(manifestJsonField(package, std::string("ios")), manifestPath, std::string("build.package.ios"));
    if (doof::is_failure(_try_value_94)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_94))};
    const auto ios = doof::success_value(_try_value_94);
    if (manifestJsonHas(ios, std::string("identity"))) {
        auto _try_value_95 = manifestString(manifestJsonField(ios, std::string("identity")), manifestPath, std::string("build.package.ios.identity"));
        if (doof::is_failure(_try_value_95)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_95))};
        const auto value = doof::success_value(_try_value_95);
        (identity = value);
    }
    if (manifestJsonHas(ios, std::string("provisioningProfile"))) {
        auto _try_value_96 = manifestString(manifestJsonField(ios, std::string("provisioningProfile")), manifestPath, std::string("build.package.ios.provisioningProfile"));
        if (doof::is_failure(_try_value_96)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_96))};
        const auto value = doof::success_value(_try_value_96);
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
    auto _try_value_98 = manifestArray(value, manifestPath, fieldPath);
    if (doof::is_failure(_try_value_98)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_98))};
    const auto entries = doof::success_value(_try_value_98);
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources = std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
        auto source = std::string("");
        auto destination = std::string("");
        {
            auto _case_subject = doof::array_at(entries, index, "src/package-manifest", 647);
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
                auto _try_value_99 = manifestString(manifestJsonField(object, std::string("from")), manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].from")));
                if (doof::is_failure(_try_value_99)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_99))};
                const auto parsedSource = doof::success_value(_try_value_99);
                auto _try_value_100 = manifestString(manifestJsonField(object, std::string("to")), manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].to")));
                if (doof::is_failure(_try_value_100)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_100))};
                const auto parsedDestination = doof::success_value(_try_value_100);
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
        auto _try_value_101 = normalizeResourceDestination(destination, manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].to")));
        if (doof::is_failure(_try_value_101)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_101))};
        const auto normalizedDestination = doof::success_value(_try_value_101);
        resources->push_back(std::make_shared<PackageResource>(sourcePath, normalizedDestination));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>>{ resources };
}
doof::Result<std::string, std::string> normalizeResourceDestination(const std::string& destination, const std::string& manifestPath, const std::string& fieldPath) {
    const auto portable = doof::string_replaceAll(destination, std::string("\\"), std::string("/"));
    if (doof::string_startsWith(portable, std::string("/")) || (((static_cast<int32_t>(portable.size()) >= 3) && (doof::string_at(portable, 1, "src/package-manifest", 696) == U'\u003A')) && (doof::string_at(portable, 2, "src/package-manifest", 696) == U'\u002F'))) {
        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be relative")) };
    }
    std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_104 = doof::string_split(portable, std::string("/"));
    for (const auto& segment : *_iterable_104) {
        if ((segment == std::string("")) || (segment == std::string("."))) {
            continue;
        }
        if (segment == std::string("..")) {
            if (static_cast<int32_t>((segments)->size()) == 0) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must stay within the executable resource directory")) };
            }
            const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(segments); if (doof::is_failure(_try_value)) doof::panic_at("src/package-manifest", 707, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
            continue;
        }
        segments->push_back(segment);
    }
    auto normalized = std::string("");
    const auto& _iterable_106 = segments;
    for (const auto& segment : *_iterable_106) {
        if (normalized != std::string("")) {
            (normalized = (normalized + std::string("/")));
        }
        (normalized = (normalized + segment));
    }
    return doof::Success<std::string>{ normalized };
}
doof::Result<void, std::string> appendNativeFragment(const std::shared_ptr<NativeBuildPlan>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& fragment, const std::string& manifestPath, const std::string& rootDirectory, const std::string& fieldPath) {
    auto _try_value_107 = appendStringArrayField(target->includePaths, fragment, std::string("includePaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_107)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_107))};
    auto _try_value_108 = appendStringArrayField(target->sourceFiles, fragment, std::string("sourceFiles"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_108)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_108))};
    auto _try_value_109 = appendStringArrayField(target->libraryPaths, fragment, std::string("libraryPaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_109)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_109))};
    auto _try_value_110 = appendStringArrayField(target->extraCopyPaths, fragment, std::string("extraCopyPaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_110)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_110))};
    auto _try_value_111 = appendStringArrayField(target->linkLibraries, fragment, std::string("linkLibraries"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_111)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_111))};
    auto _try_value_112 = appendStringArrayField(target->frameworks, fragment, std::string("frameworks"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_112)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_112))};
    auto _try_value_113 = appendStringArrayField(target->pkgConfigPackages, fragment, std::string("pkgConfigPackages"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_113)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_113))};
    auto _try_value_114 = appendStringArrayField(target->defines, fragment, std::string("defines"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_114)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_114))};
    auto _try_value_115 = appendStringArrayField(target->compilerFlags, fragment, std::string("compilerFlags"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_115)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_115))};
    auto _try_value_116 = appendStringArrayField(target->linkerFlags, fragment, std::string("linkerFlags"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_116)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_116))};
    return doof::Success<void>{};
}
doof::Result<void, std::string> appendStringArrayField(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name, const std::string& manifestPath, const std::string& fieldPath, const std::string& pathRoot) {
    if (!manifestJsonHas(object, name)) {
        return doof::Success<void>{};
    }
    auto _try_value_117 = manifestArray(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_117)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_117))};
    const auto values = doof::success_value(_try_value_117);
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        auto _try_value_118 = manifestString(doof::array_at(values, index, "src/package-manifest", 752), manifestPath, (((((fieldPath + std::string(".")) + name) + std::string("[")) + doof::to_string(index)) + std::string("]")));
        if (doof::is_failure(_try_value_118)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_118))};
        const auto value = doof::success_value(_try_value_118);
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
    const auto& _iterable_121 = values;
    for (const auto& value : *_iterable_121) {
        appendUnique(target, value);
    }
}
void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value) {
    const auto& _iterable_123 = target;
    for (const auto& existing : *_iterable_123) {
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
