#include "src_project.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "src_package_manifest.hpp"
#include "src_macos_app.hpp"
#include "src_ios_app.hpp"
#include "std_http_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_project_ {
using namespace ::std_::fs::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
using namespace ::app_src_package_manifest_;
using namespace ::app_src_macos_app_;
using namespace ::app_src_ios_app_;
std::string projectManifestPath(std::string path) {
    auto directory = (::doof_fs::isDirectory(path) ? path : ::std_::path::index::dirname(path));
    while (true) {
        const auto candidate = ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, std::string("doof.json")}));
        if (::doof_fs::isFile(candidate)) {
            return candidate;
        }
        const auto parent = ::std_::path::index::dirname(directory);
        if (parent == directory) {
            return std::string("");
        }
        (directory = parent);
    }
    return std::string("");
}
std::string environmentValue(std::string name) {
    auto _binding_value_1 = ::std_::os::index::env(name);
    if (doof::is_failure(_binding_value_1)) {
        const auto& value = _binding_value_1;
        return std::string("");
    }
    const auto value = doof::success_value(_binding_value_1);
    return value;
}
std::string fileName(std::string path) {
    return ::std_::path::index::basename(path);
}
std::string parentPath(std::string path) {
    return ::std_::path::index::dirname(path);
}
std::string joinPath(std::string directory, std::string name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}

doof::JsonObject ProjectSpec::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["rootDirectory"] = doof::json_value(this->rootDirectory);
    (*_json)["manifestPath"] = doof::json_value(this->manifestPath);
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["entry"] = doof::json_value(this->entry);
    (*_json)["buildDirectory"] = doof::json_value(this->buildDirectory);
    (*_json)["hasManifest"] = doof::json_value(this->hasManifest);
    (*_json)["manifest"] = doof::json_value(this->manifest->toJsonObject());
    (*_json)["resources"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->resources->size()); for (const auto& _element : *this->resources) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["externalDependencies"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->externalDependencies->size()); for (const auto& _element : *this->externalDependencies) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["nativeBuild"] = doof::json_value(this->nativeBuild->toJsonObject());
    (*_json)["target"] = doof::json_value(this->target);
    (*_json)["macosApp"] = (this->macosApp ? doof::json_value(this->macosApp->toJsonObject()) : doof::json_value(nullptr));
    (*_json)["iosApp"] = (this->iosApp ? doof::json_value(this->iosApp->toJsonObject()) : doof::json_value(nullptr));
    (*_json)["packageConfig"] = (this->packageConfig ? doof::json_value(this->packageConfig->toJsonObject()) : doof::json_value(nullptr));
    (*_json)["iosPackageConfig"] = (this->iosPackageConfig ? doof::json_value(this->iosPackageConfig->toJsonObject()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<ProjectSpec>, std::string> ProjectSpec::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_rootDirectory = _object->find("rootDirectory");
    if (_iterator_rootDirectory == _object->end()) { return doof::Failure<std::string>{"Missing required field \"rootDirectory\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_rootDirectory->second) : doof::json_is_string(_iterator_rootDirectory->second)))) { return doof::Failure<std::string>{"Field \"rootDirectory\" expected string but got " + std::string(doof::json_type_name(_iterator_rootDirectory->second))}; }
    auto _field_rootDirectory = (_lenient ? doof::json_as_string_lenient(_iterator_rootDirectory->second) : doof::json_as_string(_iterator_rootDirectory->second));
    auto _iterator_manifestPath = _object->find("manifestPath");
    if (_iterator_manifestPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"manifestPath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_manifestPath->second) : doof::json_is_string(_iterator_manifestPath->second)))) { return doof::Failure<std::string>{"Field \"manifestPath\" expected string but got " + std::string(doof::json_type_name(_iterator_manifestPath->second))}; }
    auto _field_manifestPath = (_lenient ? doof::json_as_string_lenient(_iterator_manifestPath->second) : doof::json_as_string(_iterator_manifestPath->second));
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_entry = _object->find("entry");
    if (_iterator_entry == _object->end()) { return doof::Failure<std::string>{"Missing required field \"entry\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_entry->second) : doof::json_is_string(_iterator_entry->second)))) { return doof::Failure<std::string>{"Field \"entry\" expected string but got " + std::string(doof::json_type_name(_iterator_entry->second))}; }
    auto _field_entry = (_lenient ? doof::json_as_string_lenient(_iterator_entry->second) : doof::json_as_string(_iterator_entry->second));
    auto _iterator_buildDirectory = _object->find("buildDirectory");
    if (_iterator_buildDirectory == _object->end()) { return doof::Failure<std::string>{"Missing required field \"buildDirectory\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_buildDirectory->second) : doof::json_is_string(_iterator_buildDirectory->second)))) { return doof::Failure<std::string>{"Field \"buildDirectory\" expected string but got " + std::string(doof::json_type_name(_iterator_buildDirectory->second))}; }
    auto _field_buildDirectory = (_lenient ? doof::json_as_string_lenient(_iterator_buildDirectory->second) : doof::json_as_string(_iterator_buildDirectory->second));
    auto _iterator_hasManifest = _object->find("hasManifest");
    if (_iterator_hasManifest == _object->end()) { return doof::Failure<std::string>{"Missing required field \"hasManifest\""}; }
    if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_hasManifest->second) : doof::json_is_boolean(_iterator_hasManifest->second)))) { return doof::Failure<std::string>{"Field \"hasManifest\" expected boolean but got " + std::string(doof::json_type_name(_iterator_hasManifest->second))}; }
    auto _field_hasManifest = (_lenient ? doof::json_as_bool_lenient(_iterator_hasManifest->second) : doof::json_as_bool(_iterator_hasManifest->second));
    auto _iterator_manifest = _object->find("manifest");
    if (_iterator_manifest == _object->end()) { return doof::Failure<std::string>{"Missing required field \"manifest\""}; }
    if (!(doof::json_is_object(_iterator_manifest->second))) { return doof::Failure<std::string>{"Field \"manifest\" expected object but got " + std::string(doof::json_type_name(_iterator_manifest->second))}; }
    auto _field_manifest = doof::success_value(::app_src_package_manifest_::PackageManifest::fromJsonValue(_iterator_manifest->second, _lenient));
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>> _field_resources;
    if (auto _iterator_resources = _object->find("resources"); _iterator_resources != _object->end()) {
        if (!(doof::json_is_array(_iterator_resources->second))) { return doof::Failure<std::string>{"Field \"resources\" expected array but got " + std::string(doof::json_type_name(_iterator_resources->second))}; }
        _field_resources = [&]() { const auto* _array = doof::json_as_array(_iterator_resources->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_package_manifest_::PackageResource::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_resources = std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>> _field_externalDependencies;
    if (auto _iterator_externalDependencies = _object->find("externalDependencies"); _iterator_externalDependencies != _object->end()) {
        if (!(doof::json_is_array(_iterator_externalDependencies->second))) { return doof::Failure<std::string>{"Field \"externalDependencies\" expected array but got " + std::string(doof::json_type_name(_iterator_externalDependencies->second))}; }
        _field_externalDependencies = [&]() { const auto* _array = doof::json_as_array(_iterator_externalDependencies->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_package_manifest_::ExternalDependency::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_externalDependencies = std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{});
    }
    auto _iterator_nativeBuild = _object->find("nativeBuild");
    if (_iterator_nativeBuild == _object->end()) { return doof::Failure<std::string>{"Missing required field \"nativeBuild\""}; }
    if (!(doof::json_is_object(_iterator_nativeBuild->second))) { return doof::Failure<std::string>{"Field \"nativeBuild\" expected object but got " + std::string(doof::json_type_name(_iterator_nativeBuild->second))}; }
    auto _field_nativeBuild = doof::success_value(::app_src_package_manifest_::NativeBuildPlan::fromJsonValue(_iterator_nativeBuild->second, _lenient));
    std::optional<std::string> _field_target;
    if (auto _iterator_target = _object->find("target"); _iterator_target != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_target->second) : doof::json_is_string(_iterator_target->second)))) { return doof::Failure<std::string>{"Field \"target\" expected string but got " + std::string(doof::json_type_name(_iterator_target->second))}; }
        _field_target = (_lenient ? doof::json_as_string_lenient(_iterator_target->second) : doof::json_as_string(_iterator_target->second));
    } else {
        _field_target = std::string("");
    }
    std::optional<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>> _field_macosApp;
    if (auto _iterator_macosApp = _object->find("macosApp"); _iterator_macosApp != _object->end()) {
        if (!(doof::json_is_null(_iterator_macosApp->second) || doof::json_is_object(_iterator_macosApp->second))) { return doof::Failure<std::string>{"Field \"macosApp\" expected object or null but got " + std::string(doof::json_type_name(_iterator_macosApp->second))}; }
        _field_macosApp = (doof::json_is_null(_iterator_macosApp->second) ? nullptr : doof::success_value(::app_src_macos_app_::MacOSAppConfig::fromJsonValue(_iterator_macosApp->second, _lenient)));
    } else {
        _field_macosApp = std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>{nullptr};
    }
    std::optional<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>> _field_iosApp;
    if (auto _iterator_iosApp = _object->find("iosApp"); _iterator_iosApp != _object->end()) {
        if (!(doof::json_is_null(_iterator_iosApp->second) || doof::json_is_object(_iterator_iosApp->second))) { return doof::Failure<std::string>{"Field \"iosApp\" expected object or null but got " + std::string(doof::json_type_name(_iterator_iosApp->second))}; }
        _field_iosApp = (doof::json_is_null(_iterator_iosApp->second) ? nullptr : doof::success_value(::app_src_ios_app_::IOSAppConfig::fromJsonValue(_iterator_iosApp->second, _lenient)));
    } else {
        _field_iosApp = std::shared_ptr<::app_src_ios_app_::IOSAppConfig>{nullptr};
    }
    std::optional<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>> _field_packageConfig;
    if (auto _iterator_packageConfig = _object->find("packageConfig"); _iterator_packageConfig != _object->end()) {
        if (!(doof::json_is_null(_iterator_packageConfig->second) || doof::json_is_object(_iterator_packageConfig->second))) { return doof::Failure<std::string>{"Field \"packageConfig\" expected object or null but got " + std::string(doof::json_type_name(_iterator_packageConfig->second))}; }
        _field_packageConfig = (doof::json_is_null(_iterator_packageConfig->second) ? nullptr : doof::success_value(::app_src_macos_app_::MacOSPackageConfig::fromJsonValue(_iterator_packageConfig->second, _lenient)));
    } else {
        _field_packageConfig = std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>{nullptr};
    }
    std::optional<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>> _field_iosPackageConfig;
    if (auto _iterator_iosPackageConfig = _object->find("iosPackageConfig"); _iterator_iosPackageConfig != _object->end()) {
        if (!(doof::json_is_null(_iterator_iosPackageConfig->second) || doof::json_is_object(_iterator_iosPackageConfig->second))) { return doof::Failure<std::string>{"Field \"iosPackageConfig\" expected object or null but got " + std::string(doof::json_type_name(_iterator_iosPackageConfig->second))}; }
        _field_iosPackageConfig = (doof::json_is_null(_iterator_iosPackageConfig->second) ? nullptr : doof::success_value(::app_src_ios_app_::IOSPackageConfig::fromJsonValue(_iterator_iosPackageConfig->second, _lenient)));
    } else {
        _field_iosPackageConfig = std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>{nullptr};
    }
    return doof::Success<std::shared_ptr<ProjectSpec>>{std::make_shared<ProjectSpec>(_field_rootDirectory, _field_manifestPath, _field_name, _field_entry, _field_buildDirectory, _field_hasManifest, _field_manifest, _field_resources.value(), _field_externalDependencies.value(), _field_nativeBuild, _field_target.value(), _field_macosApp.value(), _field_iosApp.value(), _field_packageConfig.value(), _field_iosPackageConfig.value())};
}
std::shared_ptr<ProjectSpec> readProjectSpec(std::string requestedPath, std::string platform, std::string targetOverride) {
    const auto absolutePath = [&]() -> std::string { auto _try_value = ::std_::path::index::absolute(requestedPath); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    const auto directory = (::doof_fs::isDirectory(absolutePath) ? absolutePath : parentPath(absolutePath));
    const auto manifest = projectManifestPath(absolutePath);
    if (manifest == std::string("")) {
        const auto fallbackEntry = (::doof_fs::isDirectory(absolutePath) ? std::string("main.do") : fileName(absolutePath));
        return std::make_shared<ProjectSpec>(directory, std::string(""), fileName(directory), fallbackEntry, std::string("build"), false, std::make_shared<::app_src_package_manifest_::PackageManifest>(fileName(directory), std::string("1.0"), std::string(""), directory, std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::DependencyResolution>>{}), std::make_shared<::app_src_package_manifest_::DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::string(""), nullptr, nullptr, nullptr, nullptr), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::PackageResource>>{}), std::make_shared<std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>>(std::vector<std::shared_ptr<::app_src_package_manifest_::ExternalDependency>>{}), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), targetOverride, nullptr, nullptr, std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(joinPath(directory, std::string("dist")), std::string("developer-id"), std::string(""), false, std::string("")), nullptr);
    }
    const auto packageDirectory = parentPath(manifest);
    const auto manifestSource = [&]() -> std::string { auto _try_value = ::doof_fs::readText(manifest); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    const auto packageManifest = [&]() -> std::shared_ptr<::app_src_package_manifest_::PackageManifest> { auto _try_value = ::app_src_package_manifest_::parsePackageManifest(manifestSource, manifest, packageDirectory, platform, targetOverride); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    const auto root = [&]() -> std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> { auto _try_value = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = ::doof_json::parse(manifestSource); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    auto name = fileName(packageDirectory);
    if (root->find(std::string("name")) != root->end()) {
        (name = [&]() -> std::string { auto _try_value = [&]() -> doof::Result<std::string, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(root, std::string("name"), "", 0); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }());
    }
    auto entry = std::string("main.do");
    auto buildDirectory = std::string("build");
    if (root->find(std::string("build")) != root->end()) {
        const auto build = [&]() -> std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> { auto _try_value = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(root, std::string("build"), "", 0); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
        if (build->find(std::string("entry")) != build->end()) {
            (entry = [&]() -> std::string { auto _try_value = [&]() -> doof::Result<std::string, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(build, std::string("entry"), "", 0); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }());
        }
        if (build->find(std::string("buildDir")) != build->end()) {
            (buildDirectory = [&]() -> std::string { auto _try_value = [&]() -> doof::Result<std::string, std::string> { auto _as_value = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(build, std::string("buildDir"), "", 0); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }(); if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }(); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }());
        }
    }
    if (!::doof_fs::isDirectory(absolutePath)) {
        (entry = absolutePath);
    }
    return std::make_shared<ProjectSpec>(packageDirectory, manifest, name, entry, buildDirectory, true, packageManifest, packageManifest->resources, packageManifest->externalDependencies, packageManifest->nativeBuild, packageManifest->target, packageManifest->macosApp, packageManifest->iosApp, packageManifest->packageConfig, packageManifest->iosPackageConfig);
}
}
