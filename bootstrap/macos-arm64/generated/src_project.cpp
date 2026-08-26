#include "src_project.hpp"

namespace app_src_project_ {
using namespace ::std_::fs::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
using namespace ::app_src_package_manifest_;
using namespace ::app_src_macos_app_;
using namespace ::app_src_ios_app_;
#line 15 "/src/project.do"
std::string projectManifestPath(const std::string& path) {
#line 16 "/src/project.do"
    auto directory = (::doof_fs::isDirectory(path) ? path : ::std_::path::index::dirname(path));
#line 17 "/src/project.do"
    while (true) {
#line 18 "/src/project.do"
        const auto candidate = ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, std::string("doof.json")}));
#line 19 "/src/project.do"
        if (::doof_fs::isFile(candidate)) {
#line 19 "/src/project.do"
            return candidate;
        }
#line 20 "/src/project.do"
        const auto parent = ::std_::path::index::dirname(directory);
#line 21 "/src/project.do"
        if (parent == directory) {
#line 21 "/src/project.do"
            return std::string("");
        }
#line 22 "/src/project.do"
        (directory = parent);
    }
#line 24 "/src/project.do"
    return std::string("");
}
#line 27 "/src/project.do"
std::string environmentValue(const std::string& name) {
#line 28 "/src/project.do"
    auto _binding_value_1 = ::std_::os::index::env(name);
    if (doof::is_failure(_binding_value_1)) {
        const auto& value = _binding_value_1;
#line 28 "/src/project.do"
        return std::string("");
    }
    const auto value = doof::success_value(_binding_value_1);
#line 29 "/src/project.do"
    return value;
}
#line 32 "/src/project.do"
std::string fileName(const std::string& path) {
    return ::std_::path::index::basename(path);
}
#line 33 "/src/project.do"
std::string parentPath(const std::string& path) {
    return ::std_::path::index::dirname(path);
}
#line 34 "/src/project.do"
std::string joinPath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}

#line 55 "/src/project.do"
std::string projectEntryRequestError(const std::shared_ptr<ProjectSpec>& project, const std::string& requestedPath) {
#line 56 "/src/project.do"
    if (!project->hasManifest && (!project->explicitEntry || !doof::string_endsWith(requestedPath, std::string(".do")))) {
#line 57 "/src/project.do"
        return std::string("no doof.json found; pass an explicit .do entry file");
    }
#line 59 "/src/project.do"
    return std::string("");
}
#line 62 "/src/project.do"
std::shared_ptr<ProjectSpec> readProjectSpec(const std::string& requestedPath, const std::string& platform, const std::string& targetOverride) {
#line 63 "/src/project.do"
    const auto absolutePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(requestedPath); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 63, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 64 "/src/project.do"
    const auto directory = (::doof_fs::isDirectory(absolutePath) ? absolutePath : parentPath(absolutePath));
#line 65 "/src/project.do"
    const auto manifest = projectManifestPath(absolutePath);
#line 66 "/src/project.do"
    if (manifest == std::string("")) {
#line 67 "/src/project.do"
        const auto fallbackEntry = (::doof_fs::isDirectory(absolutePath) ? std::string("main.do") : fileName(absolutePath));
#line 68 "/src/project.do"
        return std::make_shared<ProjectSpec>(directory, std::string(""), fileName(directory), fallbackEntry, std::string("build"), false, !::doof_fs::isDirectory(absolutePath), std::make_shared<::app_src_package_manifest_::PackageManifest>(fileName(directory), std::string("1.0"), std::string(""), directory, std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<::app_src_package_manifest_::DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::string(""), nullptr, nullptr, nullptr, nullptr), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{}), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), targetOverride, nullptr, nullptr, std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(joinPath(directory, std::string("dist")), std::string("developer-id"), std::string(""), false, std::string("")), nullptr);
    }
#line 86 "/src/project.do"
    const auto packageDirectory = parentPath(manifest);
#line 87 "/src/project.do"
    const auto manifestSource = [&]() -> std::string { auto _try_value = ::doof_fs::readText(manifest); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 87, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
#line 88 "/src/project.do"
    const auto packageManifest = [&]() -> std::shared_ptr<::app_src_package_manifest_::PackageManifest> { auto _try_value = ::app_src_package_manifest_::parsePackageManifest(manifestSource, manifest, packageDirectory, platform, targetOverride); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 88, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 89 "/src/project.do"
    const auto root = [&]() -> std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> { auto _try_value = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = ::doof_json::parse(manifestSource); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 89, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 89, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 90 "/src/project.do"
    auto name = fileName(packageDirectory);
#line 91 "/src/project.do"
    if ([&]() -> bool { auto _map_has_2 = root; return _map_has_2->find(std::string("name")) != _map_has_2->end(); }()) {
#line 91 "/src/project.do"
        (name = [&]() -> std::string { auto _try_value = [&]() -> doof::Result<std::string, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(root, std::string("name"), "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 91, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 91, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
    }
#line 92 "/src/project.do"
    auto entry = std::string("main.do");
#line 93 "/src/project.do"
    auto buildDirectory = std::string("build");
#line 94 "/src/project.do"
    if ([&]() -> bool { auto _map_has_3 = root; return _map_has_3->find(std::string("build")) != _map_has_3->end(); }()) {
#line 95 "/src/project.do"
        const auto build = [&]() -> std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> { auto _try_value = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(root, std::string("build"), "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 95, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 95, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 96 "/src/project.do"
        if ([&]() -> bool { auto _map_has_4 = build; return _map_has_4->find(std::string("entry")) != _map_has_4->end(); }()) {
#line 96 "/src/project.do"
            (entry = [&]() -> std::string { auto _try_value = [&]() -> doof::Result<std::string, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(build, std::string("entry"), "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 96, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 96, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        }
#line 97 "/src/project.do"
        if ([&]() -> bool { auto _map_has_5 = build; return _map_has_5->find(std::string("buildDir")) != _map_has_5->end(); }()) {
#line 97 "/src/project.do"
            (buildDirectory = [&]() -> std::string { auto _try_value = [&]() -> doof::Result<std::string, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(build, std::string("buildDir"), "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 97, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic_at("src/project", 97, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }());
        }
    }
#line 101 "/src/project.do"
    if (!::doof_fs::isDirectory(absolutePath)) {
#line 101 "/src/project.do"
        (entry = absolutePath);
    }
#line 102 "/src/project.do"
    return std::make_shared<ProjectSpec>(packageDirectory, manifest, name, entry, buildDirectory, true, !::doof_fs::isDirectory(absolutePath), packageManifest, packageManifest->resources, packageManifest->externalDependencies, packageManifest->nativeBuild, packageManifest->target, packageManifest->macosApp, packageManifest->iosApp, packageManifest->packageConfig, packageManifest->iosPackageConfig);
}
#line 1 "<doof-generated>"
}
