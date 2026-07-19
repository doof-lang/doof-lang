#include "src_package_manifest.hpp"
#include <cmath>
#include "std_json_index.hpp"
#include "std_path_index.hpp"
#include "src_macos_app.hpp"
#include "src_ios_app.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_package_manifest_ {
using namespace ::std_::json::index;
using namespace ::std_::path::index;
using namespace ::app_src_macos_app_;
using namespace ::app_src_ios_app_;
std::string manifestJoinPath(std::string directory, std::string name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
doof::JsonValue manifestJsonField(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name) {
    return [&]() -> doof::JsonValue { auto _try_value = doof::map_get(object, name, "", 0); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
}
bool manifestJsonHas(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name) {
    return (object->find(name) != object->end());
}

doof::JsonObject NativeBuildPlan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["includePaths"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->includePaths->size()); for (const auto& _element : *this->includePaths) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["sourceFiles"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->sourceFiles->size()); for (const auto& _element : *this->sourceFiles) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["libraryPaths"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->libraryPaths->size()); for (const auto& _element : *this->libraryPaths) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["extraCopyPaths"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->extraCopyPaths->size()); for (const auto& _element : *this->extraCopyPaths) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["linkLibraries"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->linkLibraries->size()); for (const auto& _element : *this->linkLibraries) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["frameworks"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->frameworks->size()); for (const auto& _element : *this->frameworks) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["pkgConfigPackages"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->pkgConfigPackages->size()); for (const auto& _element : *this->pkgConfigPackages) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["defines"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->defines->size()); for (const auto& _element : *this->defines) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["compilerFlags"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->compilerFlags->size()); for (const auto& _element : *this->compilerFlags) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["linkerFlags"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->linkerFlags->size()); for (const auto& _element : *this->linkerFlags) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> NativeBuildPlan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_includePaths;
    if (auto _iterator_includePaths = _object->find("includePaths"); _iterator_includePaths != _object->end()) {
        if (!(doof::json_is_array(_iterator_includePaths->second))) { return doof::Failure<std::string>{"Field \"includePaths\" expected array but got " + std::string(doof::json_type_name(_iterator_includePaths->second))}; }
        _field_includePaths = [&]() { const auto* _array = doof::json_as_array(_iterator_includePaths->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_includePaths = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_sourceFiles;
    if (auto _iterator_sourceFiles = _object->find("sourceFiles"); _iterator_sourceFiles != _object->end()) {
        if (!(doof::json_is_array(_iterator_sourceFiles->second))) { return doof::Failure<std::string>{"Field \"sourceFiles\" expected array but got " + std::string(doof::json_type_name(_iterator_sourceFiles->second))}; }
        _field_sourceFiles = [&]() { const auto* _array = doof::json_as_array(_iterator_sourceFiles->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_sourceFiles = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_libraryPaths;
    if (auto _iterator_libraryPaths = _object->find("libraryPaths"); _iterator_libraryPaths != _object->end()) {
        if (!(doof::json_is_array(_iterator_libraryPaths->second))) { return doof::Failure<std::string>{"Field \"libraryPaths\" expected array but got " + std::string(doof::json_type_name(_iterator_libraryPaths->second))}; }
        _field_libraryPaths = [&]() { const auto* _array = doof::json_as_array(_iterator_libraryPaths->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_libraryPaths = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_extraCopyPaths;
    if (auto _iterator_extraCopyPaths = _object->find("extraCopyPaths"); _iterator_extraCopyPaths != _object->end()) {
        if (!(doof::json_is_array(_iterator_extraCopyPaths->second))) { return doof::Failure<std::string>{"Field \"extraCopyPaths\" expected array but got " + std::string(doof::json_type_name(_iterator_extraCopyPaths->second))}; }
        _field_extraCopyPaths = [&]() { const auto* _array = doof::json_as_array(_iterator_extraCopyPaths->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_extraCopyPaths = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_linkLibraries;
    if (auto _iterator_linkLibraries = _object->find("linkLibraries"); _iterator_linkLibraries != _object->end()) {
        if (!(doof::json_is_array(_iterator_linkLibraries->second))) { return doof::Failure<std::string>{"Field \"linkLibraries\" expected array but got " + std::string(doof::json_type_name(_iterator_linkLibraries->second))}; }
        _field_linkLibraries = [&]() { const auto* _array = doof::json_as_array(_iterator_linkLibraries->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_linkLibraries = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_frameworks;
    if (auto _iterator_frameworks = _object->find("frameworks"); _iterator_frameworks != _object->end()) {
        if (!(doof::json_is_array(_iterator_frameworks->second))) { return doof::Failure<std::string>{"Field \"frameworks\" expected array but got " + std::string(doof::json_type_name(_iterator_frameworks->second))}; }
        _field_frameworks = [&]() { const auto* _array = doof::json_as_array(_iterator_frameworks->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_frameworks = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_pkgConfigPackages;
    if (auto _iterator_pkgConfigPackages = _object->find("pkgConfigPackages"); _iterator_pkgConfigPackages != _object->end()) {
        if (!(doof::json_is_array(_iterator_pkgConfigPackages->second))) { return doof::Failure<std::string>{"Field \"pkgConfigPackages\" expected array but got " + std::string(doof::json_type_name(_iterator_pkgConfigPackages->second))}; }
        _field_pkgConfigPackages = [&]() { const auto* _array = doof::json_as_array(_iterator_pkgConfigPackages->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_pkgConfigPackages = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_defines;
    if (auto _iterator_defines = _object->find("defines"); _iterator_defines != _object->end()) {
        if (!(doof::json_is_array(_iterator_defines->second))) { return doof::Failure<std::string>{"Field \"defines\" expected array but got " + std::string(doof::json_type_name(_iterator_defines->second))}; }
        _field_defines = [&]() { const auto* _array = doof::json_as_array(_iterator_defines->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_defines = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_compilerFlags;
    if (auto _iterator_compilerFlags = _object->find("compilerFlags"); _iterator_compilerFlags != _object->end()) {
        if (!(doof::json_is_array(_iterator_compilerFlags->second))) { return doof::Failure<std::string>{"Field \"compilerFlags\" expected array but got " + std::string(doof::json_type_name(_iterator_compilerFlags->second))}; }
        _field_compilerFlags = [&]() { const auto* _array = doof::json_as_array(_iterator_compilerFlags->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_compilerFlags = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_linkerFlags;
    if (auto _iterator_linkerFlags = _object->find("linkerFlags"); _iterator_linkerFlags != _object->end()) {
        if (!(doof::json_is_array(_iterator_linkerFlags->second))) { return doof::Failure<std::string>{"Field \"linkerFlags\" expected array but got " + std::string(doof::json_type_name(_iterator_linkerFlags->second))}; }
        _field_linkerFlags = [&]() { const auto* _array = doof::json_as_array(_iterator_linkerFlags->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_linkerFlags = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    return doof::Success<std::shared_ptr<NativeBuildPlan>>{std::make_shared<NativeBuildPlan>(_field_includePaths.value(), _field_sourceFiles.value(), _field_libraryPaths.value(), _field_extraCopyPaths.value(), _field_linkLibraries.value(), _field_frameworks.value(), _field_pkgConfigPackages.value(), _field_defines.value(), _field_compilerFlags.value(), _field_linkerFlags.value())};
}

doof::JsonObject PackageResource::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["sourcePath"] = doof::json_value(this->sourcePath);
    (*_json)["destination"] = doof::json_value(this->destination);
    return _json;
}
doof::Result<std::shared_ptr<PackageResource>, std::string> PackageResource::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_sourcePath = _object->find("sourcePath");
    if (_iterator_sourcePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourcePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourcePath->second) : doof::json_is_string(_iterator_sourcePath->second)))) { return doof::Failure<std::string>{"Field \"sourcePath\" expected string but got " + std::string(doof::json_type_name(_iterator_sourcePath->second))}; }
    auto _field_sourcePath = (_lenient ? doof::json_as_string_lenient(_iterator_sourcePath->second) : doof::json_as_string(_iterator_sourcePath->second));
    auto _iterator_destination = _object->find("destination");
    if (_iterator_destination == _object->end()) { return doof::Failure<std::string>{"Missing required field \"destination\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_destination->second) : doof::json_is_string(_iterator_destination->second)))) { return doof::Failure<std::string>{"Field \"destination\" expected string but got " + std::string(doof::json_type_name(_iterator_destination->second))}; }
    auto _field_destination = (_lenient ? doof::json_as_string_lenient(_iterator_destination->second) : doof::json_as_string(_iterator_destination->second));
    return doof::Success<std::shared_ptr<PackageResource>>{std::make_shared<PackageResource>(_field_sourcePath, _field_destination)};
}

doof::JsonObject ExternalDependencyCopyFile::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["source"] = doof::json_value(this->source);
    (*_json)["destination"] = doof::json_value(this->destination);
    return _json;
}
doof::Result<std::shared_ptr<ExternalDependencyCopyFile>, std::string> ExternalDependencyCopyFile::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_source = _object->find("source");
    if (_iterator_source == _object->end()) { return doof::Failure<std::string>{"Missing required field \"source\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_source->second) : doof::json_is_string(_iterator_source->second)))) { return doof::Failure<std::string>{"Field \"source\" expected string but got " + std::string(doof::json_type_name(_iterator_source->second))}; }
    auto _field_source = (_lenient ? doof::json_as_string_lenient(_iterator_source->second) : doof::json_as_string(_iterator_source->second));
    auto _iterator_destination = _object->find("destination");
    if (_iterator_destination == _object->end()) { return doof::Failure<std::string>{"Missing required field \"destination\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_destination->second) : doof::json_is_string(_iterator_destination->second)))) { return doof::Failure<std::string>{"Field \"destination\" expected string but got " + std::string(doof::json_type_name(_iterator_destination->second))}; }
    auto _field_destination = (_lenient ? doof::json_as_string_lenient(_iterator_destination->second) : doof::json_as_string(_iterator_destination->second));
    return doof::Success<std::shared_ptr<ExternalDependencyCopyFile>>{std::make_shared<ExternalDependencyCopyFile>(_field_source, _field_destination)};
}

doof::JsonObject ExternalDependencyCommand::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["program"] = doof::json_value(this->program);
    (*_json)["args"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->args->size()); for (const auto& _element : *this->args) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["env"] = [&]() { auto _object_value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(); for (const auto& _entry : *this->env) { (*_object_value)[_entry.first] = doof::json_value(_entry.second); } return doof::json_value(_object_value); }();
    (*_json)["workingDirectory"] = doof::json_value(this->workingDirectory);
    return _json;
}
doof::Result<std::shared_ptr<ExternalDependencyCommand>, std::string> ExternalDependencyCommand::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_program = _object->find("program");
    if (_iterator_program == _object->end()) { return doof::Failure<std::string>{"Missing required field \"program\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_program->second) : doof::json_is_string(_iterator_program->second)))) { return doof::Failure<std::string>{"Field \"program\" expected string but got " + std::string(doof::json_type_name(_iterator_program->second))}; }
    auto _field_program = (_lenient ? doof::json_as_string_lenient(_iterator_program->second) : doof::json_as_string(_iterator_program->second));
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_args;
    if (auto _iterator_args = _object->find("args"); _iterator_args != _object->end()) {
        if (!(doof::json_is_array(_iterator_args->second))) { return doof::Failure<std::string>{"Field \"args\" expected array but got " + std::string(doof::json_type_name(_iterator_args->second))}; }
        _field_args = [&]() { const auto* _array = doof::json_as_array(_iterator_args->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_args = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<std::shared_ptr<doof::ordered_map<std::string, std::string>>> _field_env;
    if (auto _iterator_env = _object->find("env"); _iterator_env != _object->end()) {
        if (!(doof::json_is_object(_iterator_env->second))) { return doof::Failure<std::string>{"Field \"env\" expected object but got " + std::string(doof::json_type_name(_iterator_env->second))}; }
        _field_env = [&]() { const auto* _object_value = doof::json_as_object(_iterator_env->second); auto _values = std::make_shared<doof::ordered_map<std::string, std::string>>(); for (const auto& _entry : *_object_value) { (*_values)[_entry.first] = (_lenient ? doof::json_as_string_lenient(_entry.second) : doof::json_as_string(_entry.second)); } return _values; }();
    } else {
        _field_env = std::shared_ptr<doof::ordered_map<std::string, std::string>>{std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{})};
    }
    std::optional<std::string> _field_workingDirectory;
    if (auto _iterator_workingDirectory = _object->find("workingDirectory"); _iterator_workingDirectory != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_workingDirectory->second) : doof::json_is_string(_iterator_workingDirectory->second)))) { return doof::Failure<std::string>{"Field \"workingDirectory\" expected string but got " + std::string(doof::json_type_name(_iterator_workingDirectory->second))}; }
        _field_workingDirectory = (_lenient ? doof::json_as_string_lenient(_iterator_workingDirectory->second) : doof::json_as_string(_iterator_workingDirectory->second));
    } else {
        _field_workingDirectory = std::string{std::string("")};
    }
    return doof::Success<std::shared_ptr<ExternalDependencyCommand>>{std::make_shared<ExternalDependencyCommand>(_field_program, _field_args.value(), _field_env.value(), _field_workingDirectory.value())};
}

doof::JsonObject ExternalDependency::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["url"] = doof::json_value(this->url);
    (*_json)["destination"] = doof::json_value(this->destination);
    (*_json)["sha256"] = doof::json_value(this->sha256);
    (*_json)["stripComponents"] = doof::json_value(this->stripComponents);
    (*_json)["copyFiles"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->copyFiles->size()); for (const auto& _element : *this->copyFiles) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["ref"] = doof::json_value(this->ref);
    (*_json)["commit"] = doof::json_value(this->commit);
    (*_json)["commands"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->commands->size()); for (const auto& _element : *this->commands) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<ExternalDependency>, std::string> ExternalDependency::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    auto _iterator_url = _object->find("url");
    if (_iterator_url == _object->end()) { return doof::Failure<std::string>{"Missing required field \"url\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_url->second) : doof::json_is_string(_iterator_url->second)))) { return doof::Failure<std::string>{"Field \"url\" expected string but got " + std::string(doof::json_type_name(_iterator_url->second))}; }
    auto _field_url = (_lenient ? doof::json_as_string_lenient(_iterator_url->second) : doof::json_as_string(_iterator_url->second));
    auto _iterator_destination = _object->find("destination");
    if (_iterator_destination == _object->end()) { return doof::Failure<std::string>{"Missing required field \"destination\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_destination->second) : doof::json_is_string(_iterator_destination->second)))) { return doof::Failure<std::string>{"Field \"destination\" expected string but got " + std::string(doof::json_type_name(_iterator_destination->second))}; }
    auto _field_destination = (_lenient ? doof::json_as_string_lenient(_iterator_destination->second) : doof::json_as_string(_iterator_destination->second));
    std::optional<std::string> _field_sha256;
    if (auto _iterator_sha256 = _object->find("sha256"); _iterator_sha256 != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sha256->second) : doof::json_is_string(_iterator_sha256->second)))) { return doof::Failure<std::string>{"Field \"sha256\" expected string but got " + std::string(doof::json_type_name(_iterator_sha256->second))}; }
        _field_sha256 = (_lenient ? doof::json_as_string_lenient(_iterator_sha256->second) : doof::json_as_string(_iterator_sha256->second));
    } else {
        _field_sha256 = std::string{std::string("")};
    }
    std::optional<int32_t> _field_stripComponents;
    if (auto _iterator_stripComponents = _object->find("stripComponents"); _iterator_stripComponents != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_stripComponents->second) : doof::json_is_number(_iterator_stripComponents->second)))) { return doof::Failure<std::string>{"Field \"stripComponents\" expected number but got " + std::string(doof::json_type_name(_iterator_stripComponents->second))}; }
        _field_stripComponents = (_lenient ? doof::json_as_int_lenient(_iterator_stripComponents->second) : doof::json_as_int(_iterator_stripComponents->second));
    } else {
        _field_stripComponents = int32_t{1};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>> _field_copyFiles;
    if (auto _iterator_copyFiles = _object->find("copyFiles"); _iterator_copyFiles != _object->end()) {
        if (!(doof::json_is_array(_iterator_copyFiles->second))) { return doof::Failure<std::string>{"Field \"copyFiles\" expected array but got " + std::string(doof::json_type_name(_iterator_copyFiles->second))}; }
        _field_copyFiles = [&]() { const auto* _array = doof::json_as_array(_iterator_copyFiles->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(ExternalDependencyCopyFile::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_copyFiles = std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>{std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{})};
    }
    std::optional<std::string> _field_ref;
    if (auto _iterator_ref = _object->find("ref"); _iterator_ref != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_ref->second) : doof::json_is_string(_iterator_ref->second)))) { return doof::Failure<std::string>{"Field \"ref\" expected string but got " + std::string(doof::json_type_name(_iterator_ref->second))}; }
        _field_ref = (_lenient ? doof::json_as_string_lenient(_iterator_ref->second) : doof::json_as_string(_iterator_ref->second));
    } else {
        _field_ref = std::string{std::string("")};
    }
    std::optional<std::string> _field_commit;
    if (auto _iterator_commit = _object->find("commit"); _iterator_commit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_commit->second) : doof::json_is_string(_iterator_commit->second)))) { return doof::Failure<std::string>{"Field \"commit\" expected string but got " + std::string(doof::json_type_name(_iterator_commit->second))}; }
        _field_commit = (_lenient ? doof::json_as_string_lenient(_iterator_commit->second) : doof::json_as_string(_iterator_commit->second));
    } else {
        _field_commit = std::string{std::string("")};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>> _field_commands;
    if (auto _iterator_commands = _object->find("commands"); _iterator_commands != _object->end()) {
        if (!(doof::json_is_array(_iterator_commands->second))) { return doof::Failure<std::string>{"Field \"commands\" expected array but got " + std::string(doof::json_type_name(_iterator_commands->second))}; }
        _field_commands = [&]() { const auto* _array = doof::json_as_array(_iterator_commands->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(ExternalDependencyCommand::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_commands = std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>{std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{})};
    }
    return doof::Success<std::shared_ptr<ExternalDependency>>{std::make_shared<ExternalDependency>(_field_name, _field_kind, _field_url, _field_destination, _field_sha256.value(), _field_stripComponents.value(), _field_copyFiles.value(), _field_ref.value(), _field_commit.value(), _field_commands.value())};
}

doof::JsonObject PackageDependency::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["path"] = doof::json_value(this->path);
    (*_json)["url"] = doof::json_value(this->url);
    (*_json)["ref"] = doof::json_value(this->ref);
    (*_json)["commit"] = doof::json_value(this->commit);
    return _json;
}
doof::Result<std::shared_ptr<PackageDependency>, std::string> PackageDependency::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    std::optional<std::string> _field_path;
    if (auto _iterator_path = _object->find("path"); _iterator_path != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
        _field_path = (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second));
    } else {
        _field_path = std::string{std::string("")};
    }
    std::optional<std::string> _field_url;
    if (auto _iterator_url = _object->find("url"); _iterator_url != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_url->second) : doof::json_is_string(_iterator_url->second)))) { return doof::Failure<std::string>{"Field \"url\" expected string but got " + std::string(doof::json_type_name(_iterator_url->second))}; }
        _field_url = (_lenient ? doof::json_as_string_lenient(_iterator_url->second) : doof::json_as_string(_iterator_url->second));
    } else {
        _field_url = std::string{std::string("")};
    }
    std::optional<std::string> _field_ref;
    if (auto _iterator_ref = _object->find("ref"); _iterator_ref != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_ref->second) : doof::json_is_string(_iterator_ref->second)))) { return doof::Failure<std::string>{"Field \"ref\" expected string but got " + std::string(doof::json_type_name(_iterator_ref->second))}; }
        _field_ref = (_lenient ? doof::json_as_string_lenient(_iterator_ref->second) : doof::json_as_string(_iterator_ref->second));
    } else {
        _field_ref = std::string{std::string("")};
    }
    std::optional<std::string> _field_commit;
    if (auto _iterator_commit = _object->find("commit"); _iterator_commit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_commit->second) : doof::json_is_string(_iterator_commit->second)))) { return doof::Failure<std::string>{"Field \"commit\" expected string but got " + std::string(doof::json_type_name(_iterator_commit->second))}; }
        _field_commit = (_lenient ? doof::json_as_string_lenient(_iterator_commit->second) : doof::json_as_string(_iterator_commit->second));
    } else {
        _field_commit = std::string{std::string("")};
    }
    return doof::Success<std::shared_ptr<PackageDependency>>{std::make_shared<PackageDependency>(_field_name, _field_path.value(), _field_url.value(), _field_ref.value(), _field_commit.value())};
}

doof::JsonObject DependencyResolution::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["kind"] = doof::json_value(this->kind);
    (*_json)["url"] = doof::json_value(this->url);
    (*_json)["ref"] = doof::json_value(this->ref);
    (*_json)["commit"] = doof::json_value(this->commit);
    (*_json)["sha256"] = doof::json_value(this->sha256);
    return _json;
}
doof::Result<std::shared_ptr<DependencyResolution>, std::string> DependencyResolution::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    std::optional<std::string> _field_kind;
    if (auto _iterator_kind = _object->find("kind"); _iterator_kind != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
        _field_kind = (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second));
    } else {
        _field_kind = std::string{std::string("git")};
    }
    auto _iterator_url = _object->find("url");
    if (_iterator_url == _object->end()) { return doof::Failure<std::string>{"Missing required field \"url\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_url->second) : doof::json_is_string(_iterator_url->second)))) { return doof::Failure<std::string>{"Field \"url\" expected string but got " + std::string(doof::json_type_name(_iterator_url->second))}; }
    auto _field_url = (_lenient ? doof::json_as_string_lenient(_iterator_url->second) : doof::json_as_string(_iterator_url->second));
    std::optional<std::string> _field_ref;
    if (auto _iterator_ref = _object->find("ref"); _iterator_ref != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_ref->second) : doof::json_is_string(_iterator_ref->second)))) { return doof::Failure<std::string>{"Field \"ref\" expected string but got " + std::string(doof::json_type_name(_iterator_ref->second))}; }
        _field_ref = (_lenient ? doof::json_as_string_lenient(_iterator_ref->second) : doof::json_as_string(_iterator_ref->second));
    } else {
        _field_ref = std::string{std::string("")};
    }
    std::optional<std::string> _field_commit;
    if (auto _iterator_commit = _object->find("commit"); _iterator_commit != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_commit->second) : doof::json_is_string(_iterator_commit->second)))) { return doof::Failure<std::string>{"Field \"commit\" expected string but got " + std::string(doof::json_type_name(_iterator_commit->second))}; }
        _field_commit = (_lenient ? doof::json_as_string_lenient(_iterator_commit->second) : doof::json_as_string(_iterator_commit->second));
    } else {
        _field_commit = std::string{std::string("")};
    }
    std::optional<std::string> _field_sha256;
    if (auto _iterator_sha256 = _object->find("sha256"); _iterator_sha256 != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sha256->second) : doof::json_is_string(_iterator_sha256->second)))) { return doof::Failure<std::string>{"Field \"sha256\" expected string but got " + std::string(doof::json_type_name(_iterator_sha256->second))}; }
        _field_sha256 = (_lenient ? doof::json_as_string_lenient(_iterator_sha256->second) : doof::json_as_string(_iterator_sha256->second));
    } else {
        _field_sha256 = std::string{std::string("")};
    }
    return doof::Success<std::shared_ptr<DependencyResolution>>{std::make_shared<DependencyResolution>(_field_name, _field_kind.value(), _field_url, _field_ref.value(), _field_commit.value(), _field_sha256.value())};
}

doof::JsonObject DependencyPolicy::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["hasPackageSourceAllowlist"] = doof::json_value(this->hasPackageSourceAllowlist);
    (*_json)["allowedPackageSources"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->allowedPackageSources->size()); for (const auto& _element : *this->allowedPackageSources) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["hasExternalSourceAllowlist"] = doof::json_value(this->hasExternalSourceAllowlist);
    (*_json)["allowedExternalSources"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->allowedExternalSources->size()); for (const auto& _element : *this->allowedExternalSources) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["hasLinkLibraryAllowlist"] = doof::json_value(this->hasLinkLibraryAllowlist);
    (*_json)["allowedLinkLibraries"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->allowedLinkLibraries->size()); for (const auto& _element : *this->allowedLinkLibraries) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["hasFrameworkAllowlist"] = doof::json_value(this->hasFrameworkAllowlist);
    (*_json)["allowedFrameworks"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->allowedFrameworks->size()); for (const auto& _element : *this->allowedFrameworks) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["hasPkgConfigAllowlist"] = doof::json_value(this->hasPkgConfigAllowlist);
    (*_json)["allowedPkgConfigPackages"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->allowedPkgConfigPackages->size()); for (const auto& _element : *this->allowedPkgConfigPackages) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<DependencyPolicy>, std::string> DependencyPolicy::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<bool> _field_hasPackageSourceAllowlist;
    if (auto _iterator_hasPackageSourceAllowlist = _object->find("hasPackageSourceAllowlist"); _iterator_hasPackageSourceAllowlist != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_hasPackageSourceAllowlist->second) : doof::json_is_boolean(_iterator_hasPackageSourceAllowlist->second)))) { return doof::Failure<std::string>{"Field \"hasPackageSourceAllowlist\" expected boolean but got " + std::string(doof::json_type_name(_iterator_hasPackageSourceAllowlist->second))}; }
        _field_hasPackageSourceAllowlist = (_lenient ? doof::json_as_bool_lenient(_iterator_hasPackageSourceAllowlist->second) : doof::json_as_bool(_iterator_hasPackageSourceAllowlist->second));
    } else {
        _field_hasPackageSourceAllowlist = bool{false};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_allowedPackageSources;
    if (auto _iterator_allowedPackageSources = _object->find("allowedPackageSources"); _iterator_allowedPackageSources != _object->end()) {
        if (!(doof::json_is_array(_iterator_allowedPackageSources->second))) { return doof::Failure<std::string>{"Field \"allowedPackageSources\" expected array but got " + std::string(doof::json_type_name(_iterator_allowedPackageSources->second))}; }
        _field_allowedPackageSources = [&]() { const auto* _array = doof::json_as_array(_iterator_allowedPackageSources->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_allowedPackageSources = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<bool> _field_hasExternalSourceAllowlist;
    if (auto _iterator_hasExternalSourceAllowlist = _object->find("hasExternalSourceAllowlist"); _iterator_hasExternalSourceAllowlist != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_hasExternalSourceAllowlist->second) : doof::json_is_boolean(_iterator_hasExternalSourceAllowlist->second)))) { return doof::Failure<std::string>{"Field \"hasExternalSourceAllowlist\" expected boolean but got " + std::string(doof::json_type_name(_iterator_hasExternalSourceAllowlist->second))}; }
        _field_hasExternalSourceAllowlist = (_lenient ? doof::json_as_bool_lenient(_iterator_hasExternalSourceAllowlist->second) : doof::json_as_bool(_iterator_hasExternalSourceAllowlist->second));
    } else {
        _field_hasExternalSourceAllowlist = bool{false};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_allowedExternalSources;
    if (auto _iterator_allowedExternalSources = _object->find("allowedExternalSources"); _iterator_allowedExternalSources != _object->end()) {
        if (!(doof::json_is_array(_iterator_allowedExternalSources->second))) { return doof::Failure<std::string>{"Field \"allowedExternalSources\" expected array but got " + std::string(doof::json_type_name(_iterator_allowedExternalSources->second))}; }
        _field_allowedExternalSources = [&]() { const auto* _array = doof::json_as_array(_iterator_allowedExternalSources->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_allowedExternalSources = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<bool> _field_hasLinkLibraryAllowlist;
    if (auto _iterator_hasLinkLibraryAllowlist = _object->find("hasLinkLibraryAllowlist"); _iterator_hasLinkLibraryAllowlist != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_hasLinkLibraryAllowlist->second) : doof::json_is_boolean(_iterator_hasLinkLibraryAllowlist->second)))) { return doof::Failure<std::string>{"Field \"hasLinkLibraryAllowlist\" expected boolean but got " + std::string(doof::json_type_name(_iterator_hasLinkLibraryAllowlist->second))}; }
        _field_hasLinkLibraryAllowlist = (_lenient ? doof::json_as_bool_lenient(_iterator_hasLinkLibraryAllowlist->second) : doof::json_as_bool(_iterator_hasLinkLibraryAllowlist->second));
    } else {
        _field_hasLinkLibraryAllowlist = bool{false};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_allowedLinkLibraries;
    if (auto _iterator_allowedLinkLibraries = _object->find("allowedLinkLibraries"); _iterator_allowedLinkLibraries != _object->end()) {
        if (!(doof::json_is_array(_iterator_allowedLinkLibraries->second))) { return doof::Failure<std::string>{"Field \"allowedLinkLibraries\" expected array but got " + std::string(doof::json_type_name(_iterator_allowedLinkLibraries->second))}; }
        _field_allowedLinkLibraries = [&]() { const auto* _array = doof::json_as_array(_iterator_allowedLinkLibraries->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_allowedLinkLibraries = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<bool> _field_hasFrameworkAllowlist;
    if (auto _iterator_hasFrameworkAllowlist = _object->find("hasFrameworkAllowlist"); _iterator_hasFrameworkAllowlist != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_hasFrameworkAllowlist->second) : doof::json_is_boolean(_iterator_hasFrameworkAllowlist->second)))) { return doof::Failure<std::string>{"Field \"hasFrameworkAllowlist\" expected boolean but got " + std::string(doof::json_type_name(_iterator_hasFrameworkAllowlist->second))}; }
        _field_hasFrameworkAllowlist = (_lenient ? doof::json_as_bool_lenient(_iterator_hasFrameworkAllowlist->second) : doof::json_as_bool(_iterator_hasFrameworkAllowlist->second));
    } else {
        _field_hasFrameworkAllowlist = bool{false};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_allowedFrameworks;
    if (auto _iterator_allowedFrameworks = _object->find("allowedFrameworks"); _iterator_allowedFrameworks != _object->end()) {
        if (!(doof::json_is_array(_iterator_allowedFrameworks->second))) { return doof::Failure<std::string>{"Field \"allowedFrameworks\" expected array but got " + std::string(doof::json_type_name(_iterator_allowedFrameworks->second))}; }
        _field_allowedFrameworks = [&]() { const auto* _array = doof::json_as_array(_iterator_allowedFrameworks->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_allowedFrameworks = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    std::optional<bool> _field_hasPkgConfigAllowlist;
    if (auto _iterator_hasPkgConfigAllowlist = _object->find("hasPkgConfigAllowlist"); _iterator_hasPkgConfigAllowlist != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_hasPkgConfigAllowlist->second) : doof::json_is_boolean(_iterator_hasPkgConfigAllowlist->second)))) { return doof::Failure<std::string>{"Field \"hasPkgConfigAllowlist\" expected boolean but got " + std::string(doof::json_type_name(_iterator_hasPkgConfigAllowlist->second))}; }
        _field_hasPkgConfigAllowlist = (_lenient ? doof::json_as_bool_lenient(_iterator_hasPkgConfigAllowlist->second) : doof::json_as_bool(_iterator_hasPkgConfigAllowlist->second));
    } else {
        _field_hasPkgConfigAllowlist = bool{false};
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_allowedPkgConfigPackages;
    if (auto _iterator_allowedPkgConfigPackages = _object->find("allowedPkgConfigPackages"); _iterator_allowedPkgConfigPackages != _object->end()) {
        if (!(doof::json_is_array(_iterator_allowedPkgConfigPackages->second))) { return doof::Failure<std::string>{"Field \"allowedPkgConfigPackages\" expected array but got " + std::string(doof::json_type_name(_iterator_allowedPkgConfigPackages->second))}; }
        _field_allowedPkgConfigPackages = [&]() { const auto* _array = doof::json_as_array(_iterator_allowedPkgConfigPackages->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_allowedPkgConfigPackages = std::shared_ptr<std::vector<std::string>>{std::make_shared<std::vector<std::string>>(std::vector<std::string>{})};
    }
    return doof::Success<std::shared_ptr<DependencyPolicy>>{std::make_shared<DependencyPolicy>(_field_hasPackageSourceAllowlist.value(), _field_allowedPackageSources.value(), _field_hasExternalSourceAllowlist.value(), _field_allowedExternalSources.value(), _field_hasLinkLibraryAllowlist.value(), _field_allowedLinkLibraries.value(), _field_hasFrameworkAllowlist.value(), _field_allowedFrameworks.value(), _field_hasPkgConfigAllowlist.value(), _field_allowedPkgConfigPackages.value())};
}

doof::JsonObject PackageManifest::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["version"] = doof::json_value(this->version);
    (*_json)["manifestPath"] = doof::json_value(this->manifestPath);
    (*_json)["rootDirectory"] = doof::json_value(this->rootDirectory);
    (*_json)["resources"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->resources->size()); for (const auto& _element : *this->resources) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["dependencies"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->dependencies->size()); for (const auto& _element : *this->dependencies) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["externalDependencies"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->externalDependencies->size()); for (const auto& _element : *this->externalDependencies) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["packageResolutions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->packageResolutions->size()); for (const auto& _element : *this->packageResolutions) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["externalResolutions"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->externalResolutions->size()); for (const auto& _element : *this->externalResolutions) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["policy"] = doof::json_value(this->policy->toJsonObject());
    (*_json)["nativeBuild"] = doof::json_value(this->nativeBuild->toJsonObject());
    (*_json)["target"] = doof::json_value(this->target);
    (*_json)["macosApp"] = (this->macosApp ? doof::json_value(this->macosApp->toJsonObject()) : doof::json_value(nullptr));
    (*_json)["iosApp"] = (this->iosApp ? doof::json_value(this->iosApp->toJsonObject()) : doof::json_value(nullptr));
    (*_json)["packageConfig"] = (this->packageConfig ? doof::json_value(this->packageConfig->toJsonObject()) : doof::json_value(nullptr));
    (*_json)["iosPackageConfig"] = (this->iosPackageConfig ? doof::json_value(this->iosPackageConfig->toJsonObject()) : doof::json_value(nullptr));
    return _json;
}
doof::Result<std::shared_ptr<PackageManifest>, std::string> PackageManifest::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    std::optional<std::string> _field_version;
    if (auto _iterator_version = _object->find("version"); _iterator_version != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_version->second) : doof::json_is_string(_iterator_version->second)))) { return doof::Failure<std::string>{"Field \"version\" expected string but got " + std::string(doof::json_type_name(_iterator_version->second))}; }
        _field_version = (_lenient ? doof::json_as_string_lenient(_iterator_version->second) : doof::json_as_string(_iterator_version->second));
    } else {
        _field_version = std::string{std::string("1.0")};
    }
    auto _iterator_manifestPath = _object->find("manifestPath");
    if (_iterator_manifestPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"manifestPath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_manifestPath->second) : doof::json_is_string(_iterator_manifestPath->second)))) { return doof::Failure<std::string>{"Field \"manifestPath\" expected string but got " + std::string(doof::json_type_name(_iterator_manifestPath->second))}; }
    auto _field_manifestPath = (_lenient ? doof::json_as_string_lenient(_iterator_manifestPath->second) : doof::json_as_string(_iterator_manifestPath->second));
    auto _iterator_rootDirectory = _object->find("rootDirectory");
    if (_iterator_rootDirectory == _object->end()) { return doof::Failure<std::string>{"Missing required field \"rootDirectory\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_rootDirectory->second) : doof::json_is_string(_iterator_rootDirectory->second)))) { return doof::Failure<std::string>{"Field \"rootDirectory\" expected string but got " + std::string(doof::json_type_name(_iterator_rootDirectory->second))}; }
    auto _field_rootDirectory = (_lenient ? doof::json_as_string_lenient(_iterator_rootDirectory->second) : doof::json_as_string(_iterator_rootDirectory->second));
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>> _field_resources;
    if (auto _iterator_resources = _object->find("resources"); _iterator_resources != _object->end()) {
        if (!(doof::json_is_array(_iterator_resources->second))) { return doof::Failure<std::string>{"Field \"resources\" expected array but got " + std::string(doof::json_type_name(_iterator_resources->second))}; }
        _field_resources = [&]() { const auto* _array = doof::json_as_array(_iterator_resources->second); auto _values = std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(PackageResource::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_resources = std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>{std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>> _field_dependencies;
    if (auto _iterator_dependencies = _object->find("dependencies"); _iterator_dependencies != _object->end()) {
        if (!(doof::json_is_array(_iterator_dependencies->second))) { return doof::Failure<std::string>{"Field \"dependencies\" expected array but got " + std::string(doof::json_type_name(_iterator_dependencies->second))}; }
        _field_dependencies = [&]() { const auto* _array = doof::json_as_array(_iterator_dependencies->second); auto _values = std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(PackageDependency::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_dependencies = std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>{std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>> _field_externalDependencies;
    if (auto _iterator_externalDependencies = _object->find("externalDependencies"); _iterator_externalDependencies != _object->end()) {
        if (!(doof::json_is_array(_iterator_externalDependencies->second))) { return doof::Failure<std::string>{"Field \"externalDependencies\" expected array but got " + std::string(doof::json_type_name(_iterator_externalDependencies->second))}; }
        _field_externalDependencies = [&]() { const auto* _array = doof::json_as_array(_iterator_externalDependencies->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(ExternalDependency::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_externalDependencies = std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>{std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(std::vector<std::shared_ptr<ExternalDependency>>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>> _field_packageResolutions;
    if (auto _iterator_packageResolutions = _object->find("packageResolutions"); _iterator_packageResolutions != _object->end()) {
        if (!(doof::json_is_array(_iterator_packageResolutions->second))) { return doof::Failure<std::string>{"Field \"packageResolutions\" expected array but got " + std::string(doof::json_type_name(_iterator_packageResolutions->second))}; }
        _field_packageResolutions = [&]() { const auto* _array = doof::json_as_array(_iterator_packageResolutions->second); auto _values = std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(DependencyResolution::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_packageResolutions = std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>{std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{})};
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>> _field_externalResolutions;
    if (auto _iterator_externalResolutions = _object->find("externalResolutions"); _iterator_externalResolutions != _object->end()) {
        if (!(doof::json_is_array(_iterator_externalResolutions->second))) { return doof::Failure<std::string>{"Field \"externalResolutions\" expected array but got " + std::string(doof::json_type_name(_iterator_externalResolutions->second))}; }
        _field_externalResolutions = [&]() { const auto* _array = doof::json_as_array(_iterator_externalResolutions->second); auto _values = std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(DependencyResolution::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_externalResolutions = std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>{std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{})};
    }
    std::optional<std::shared_ptr<DependencyPolicy>> _field_policy;
    if (auto _iterator_policy = _object->find("policy"); _iterator_policy != _object->end()) {
        if (!(doof::json_is_object(_iterator_policy->second))) { return doof::Failure<std::string>{"Field \"policy\" expected object but got " + std::string(doof::json_type_name(_iterator_policy->second))}; }
        _field_policy = doof::success_value(DependencyPolicy::fromJsonValue(_iterator_policy->second, _lenient));
    } else {
        _field_policy = std::shared_ptr<DependencyPolicy>{std::make_shared<DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}))};
    }
    auto _iterator_nativeBuild = _object->find("nativeBuild");
    if (_iterator_nativeBuild == _object->end()) { return doof::Failure<std::string>{"Missing required field \"nativeBuild\""}; }
    if (!(doof::json_is_object(_iterator_nativeBuild->second))) { return doof::Failure<std::string>{"Field \"nativeBuild\" expected object but got " + std::string(doof::json_type_name(_iterator_nativeBuild->second))}; }
    auto _field_nativeBuild = doof::success_value(NativeBuildPlan::fromJsonValue(_iterator_nativeBuild->second, _lenient));
    std::optional<std::string> _field_target;
    if (auto _iterator_target = _object->find("target"); _iterator_target != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_target->second) : doof::json_is_string(_iterator_target->second)))) { return doof::Failure<std::string>{"Field \"target\" expected string but got " + std::string(doof::json_type_name(_iterator_target->second))}; }
        _field_target = (_lenient ? doof::json_as_string_lenient(_iterator_target->second) : doof::json_as_string(_iterator_target->second));
    } else {
        _field_target = std::string{std::string("")};
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
    return doof::Success<std::shared_ptr<PackageManifest>>{std::make_shared<PackageManifest>(_field_name, _field_version.value(), _field_manifestPath, _field_rootDirectory, _field_resources.value(), _field_dependencies.value(), _field_externalDependencies.value(), _field_packageResolutions.value(), _field_externalResolutions.value(), _field_policy.value(), _field_nativeBuild, _field_target.value(), _field_macosApp.value(), _field_iosApp.value(), _field_packageConfig.value(), _field_iosPackageConfig.value())};
}
doof::Result<std::shared_ptr<PackageManifest>, std::string> parsePackageManifest(std::string source, std::string manifestPath, std::string rootDirectory, std::string platform, std::string targetOverride) {
    auto _try_value_1 = ::std_::json::index::parseJsonValue(source);
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::failure_error(_try_value_1)};
    const auto parsed = doof::success_value(_try_value_1);
    auto _try_value_2 = manifestObject(parsed, manifestPath, std::string("root"));
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::failure_error(_try_value_2)};
    const auto root = doof::success_value(_try_value_2);
    auto name = std::string("");
    if (manifestJsonHas(root, std::string("name"))) {
        auto _try_value_3 = manifestString(manifestJsonField(root, std::string("name")), manifestPath, std::string("name"));
        if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::failure_error(_try_value_3)};
        const auto parsedName = doof::success_value(_try_value_3);
        (name = parsedName);
    }
    auto version = std::string("1.0");
    if (manifestJsonHas(root, std::string("version"))) {
        auto _try_value_4 = manifestString(manifestJsonField(root, std::string("version")), manifestPath, std::string("version"));
        if (doof::is_failure(_try_value_4)) return doof::Failure<std::string>{doof::failure_error(_try_value_4)};
        const auto parsedVersion = doof::success_value(_try_value_4);
        (version = parsedVersion);
    }
    auto _try_value_5 = parseManifestResources(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::failure_error(_try_value_5)};
    const auto resources = doof::success_value(_try_value_5);
    auto _try_value_6 = parsePackageDependencies(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::failure_error(_try_value_6)};
    const auto dependencies = doof::success_value(_try_value_6);
    auto _try_value_7 = parseExternalDependencies(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::failure_error(_try_value_7)};
    const auto externalDependencies = doof::success_value(_try_value_7);
    auto _try_value_8 = parseResolutions(root, manifestPath, std::string("packages"));
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::failure_error(_try_value_8)};
    const auto packageResolutions = doof::success_value(_try_value_8);
    auto _try_value_9 = parseResolutions(root, manifestPath, std::string("externalDependencies"));
    if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::failure_error(_try_value_9)};
    const auto externalResolutions = doof::success_value(_try_value_9);
    auto _try_value_10 = parseDependencyPolicy(root, manifestPath);
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::failure_error(_try_value_10)};
    const auto policy = doof::success_value(_try_value_10);
    auto _try_value_11 = parseManifestTarget(root, manifestPath);
    if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::failure_error(_try_value_11)};
    const auto manifestTarget = doof::success_value(_try_value_11);
    const auto target = ((targetOverride == std::string("")) ? manifestTarget : targetOverride);
    auto _try_value_12 = parseManifestNativeBuild(root, manifestPath, rootDirectory, platform, target);
    if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::failure_error(_try_value_12)};
    const auto nativeBuild = doof::success_value(_try_value_12);
    auto _try_value_13 = parseMacOSApp(root, manifestPath, rootDirectory, name, version, target);
    if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::failure_error(_try_value_13)};
    const auto macosApp = doof::success_value(_try_value_13);
    auto _try_value_14 = parseIOSApp(root, manifestPath, rootDirectory, name, version, target);
    if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::failure_error(_try_value_14)};
    const auto iosApp = doof::success_value(_try_value_14);
    auto _try_value_15 = parseMacOSPackage(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_15)) return doof::Failure<std::string>{doof::failure_error(_try_value_15)};
    const auto packageConfig = doof::success_value(_try_value_15);
    auto _try_value_16 = parseIOSPackage(root, manifestPath, rootDirectory);
    if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::failure_error(_try_value_16)};
    const auto iosPackageConfig = doof::success_value(_try_value_16);
    return doof::Success<std::shared_ptr<PackageManifest>>{ std::make_shared<PackageManifest>(name, version, manifestPath, rootDirectory, resources, dependencies, externalDependencies, packageResolutions, externalResolutions, policy, nativeBuild, target, macosApp, iosApp, packageConfig, iosPackageConfig) };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>, std::string> parsePackageDependencies(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory) {
    if (!manifestJsonHas(root, std::string("dependencies"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>>{ std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{}) };
    }
    auto _try_value_17 = manifestObject(manifestJsonField(root, std::string("dependencies")), manifestPath, std::string("dependencies"));
    if (doof::is_failure(_try_value_17)) return doof::Failure<std::string>{doof::failure_error(_try_value_17)};
    const auto values = doof::success_value(_try_value_17);
    std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>> result = std::make_shared<std::vector<std::shared_ptr<PackageDependency>>>(std::vector<std::shared_ptr<PackageDependency>>{});
    const auto& _iterable_18 = values;
    for (const auto& [name, value] : *_iterable_18) {
        const auto fieldPath = (std::string("dependencies.") + name);
        if (name == std::string("")) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": dependency names must not be empty")) };
        }
        auto _try_value_19 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_19)) return doof::Failure<std::string>{doof::failure_error(_try_value_19)};
        const auto object = doof::success_value(_try_value_19);
        if (manifestJsonHas(object, std::string("path"))) {
            if ((manifestJsonHas(object, std::string("url")) || manifestJsonHas(object, std::string("ref"))) || manifestJsonHas(object, std::string("commit"))) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must declare either path or url/ref/commit")) };
            }
            auto _try_value_20 = requiredManifestString(object, std::string("path"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_20)) return doof::Failure<std::string>{doof::failure_error(_try_value_20)};
            const auto path = doof::success_value(_try_value_20);
            result->push_back(std::make_shared<PackageDependency>(name, manifestJoinPath(rootDirectory, path), std::string(""), std::string(""), std::string("")));
            continue;
        }
        auto _try_value_21 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::failure_error(_try_value_21)};
        const auto url = doof::success_value(_try_value_21);
        auto _try_value_22 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::failure_error(_try_value_22)};
        const auto ref = doof::success_value(_try_value_22);
        auto _try_value_23 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::failure_error(_try_value_23)};
        const auto commit = doof::success_value(_try_value_23);
        if (!isHexString(commit, 40)) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".commit must be a 40-character hex string")) };
        }
        result->push_back(std::make_shared<PackageDependency>(name, std::string(""), url, ref, doof::string_toLowerCase(commit)));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageDependency>>>>{ result };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>, std::string> parseResolutions(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string section) {
    if (!manifestJsonHas(root, std::string("resolutions"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>>{ std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{}) };
    }
    auto _try_value_24 = manifestObject(manifestJsonField(root, std::string("resolutions")), manifestPath, std::string("resolutions"));
    if (doof::is_failure(_try_value_24)) return doof::Failure<std::string>{doof::failure_error(_try_value_24)};
    const auto resolutions = doof::success_value(_try_value_24);
    if (!manifestJsonHas(resolutions, section)) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>>>{ std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{}) };
    }
    const auto fieldRoot = (std::string("resolutions.") + section);
    auto _try_value_25 = manifestObject(manifestJsonField(resolutions, section), manifestPath, fieldRoot);
    if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::failure_error(_try_value_25)};
    const auto values = doof::success_value(_try_value_25);
    std::shared_ptr<std::vector<std::shared_ptr<DependencyResolution>>> result = std::make_shared<std::vector<std::shared_ptr<DependencyResolution>>>(std::vector<std::shared_ptr<DependencyResolution>>{});
    const auto& _iterable_26 = values;
    for (const auto& [name, value] : *_iterable_26) {
        const auto fieldPath = ((fieldRoot + std::string(".")) + name);
        auto _try_value_27 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_27)) return doof::Failure<std::string>{doof::failure_error(_try_value_27)};
        const auto object = doof::success_value(_try_value_27);
        auto kind = std::string("git");
        if (manifestJsonHas(object, std::string("kind"))) {
            auto _try_value_28 = manifestString(manifestJsonField(object, std::string("kind")), manifestPath, (fieldPath + std::string(".kind")));
            if (doof::is_failure(_try_value_28)) return doof::Failure<std::string>{doof::failure_error(_try_value_28)};
            const auto parsedKind = doof::success_value(_try_value_28);
            (kind = parsedKind);
        }
        if ((section == std::string("packages")) && (kind != std::string("git"))) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".kind must be \"git\"")) };
        }
        auto _try_value_29 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_29)) return doof::Failure<std::string>{doof::failure_error(_try_value_29)};
        const auto url = doof::success_value(_try_value_29);
        if (kind == std::string("git")) {
            auto _try_value_30 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_30)) return doof::Failure<std::string>{doof::failure_error(_try_value_30)};
            const auto ref = doof::success_value(_try_value_30);
            auto _try_value_31 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_31)) return doof::Failure<std::string>{doof::failure_error(_try_value_31)};
            const auto commit = doof::success_value(_try_value_31);
            if (!isHexString(commit, 40)) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".commit must be a 40-character hex string")) };
            }
            result->push_back(std::make_shared<DependencyResolution>(name, kind, url, ref, doof::string_toLowerCase(commit), std::string("")));
            continue;
        }
        if (kind == std::string("archive")) {
            auto _try_value_32 = requiredManifestString(object, std::string("sha256"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_32)) return doof::Failure<std::string>{doof::failure_error(_try_value_32)};
            const auto sha256 = doof::success_value(_try_value_32);
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
doof::Result<std::shared_ptr<DependencyPolicy>, std::string> parseDependencyPolicy(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath) {
    const auto result = std::make_shared<DependencyPolicy>(false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    if (!manifestJsonHas(root, std::string("policy"))) {
        return doof::Success<std::shared_ptr<DependencyPolicy>>{ result };
    }
    auto _try_value_33 = manifestObject(manifestJsonField(root, std::string("policy")), manifestPath, std::string("policy"));
    if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::failure_error(_try_value_33)};
    const auto policy = doof::success_value(_try_value_33);
    if (manifestJsonHas(policy, std::string("allowedPackageSources"))) {
        (result->hasPackageSourceAllowlist = true);
        auto _try_value_34 = appendPolicyStrings(result->allowedPackageSources, policy, std::string("allowedPackageSources"), manifestPath, std::string("policy"));
        if (doof::is_failure(_try_value_34)) return doof::Failure<std::string>{doof::failure_error(_try_value_34)};
    }
    if (manifestJsonHas(policy, std::string("allowedExternalSources"))) {
        (result->hasExternalSourceAllowlist = true);
        auto _try_value_35 = appendPolicyStrings(result->allowedExternalSources, policy, std::string("allowedExternalSources"), manifestPath, std::string("policy"));
        if (doof::is_failure(_try_value_35)) return doof::Failure<std::string>{doof::failure_error(_try_value_35)};
    }
    if (manifestJsonHas(policy, std::string("native"))) {
        auto _try_value_36 = manifestObject(manifestJsonField(policy, std::string("native")), manifestPath, std::string("policy.native"));
        if (doof::is_failure(_try_value_36)) return doof::Failure<std::string>{doof::failure_error(_try_value_36)};
        const auto native = doof::success_value(_try_value_36);
        if (manifestJsonHas(native, std::string("allowedLinkLibraries"))) {
            (result->hasLinkLibraryAllowlist = true);
            auto _try_value_37 = appendPolicyStrings(result->allowedLinkLibraries, native, std::string("allowedLinkLibraries"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_37)) return doof::Failure<std::string>{doof::failure_error(_try_value_37)};
        }
        if (manifestJsonHas(native, std::string("allowedFrameworks"))) {
            (result->hasFrameworkAllowlist = true);
            auto _try_value_38 = appendPolicyStrings(result->allowedFrameworks, native, std::string("allowedFrameworks"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::failure_error(_try_value_38)};
        }
        if (manifestJsonHas(native, std::string("allowedPkgConfigPackages"))) {
            (result->hasPkgConfigAllowlist = true);
            auto _try_value_39 = appendPolicyStrings(result->allowedPkgConfigPackages, native, std::string("allowedPkgConfigPackages"), manifestPath, std::string("policy.native"));
            if (doof::is_failure(_try_value_39)) return doof::Failure<std::string>{doof::failure_error(_try_value_39)};
        }
    }
    return doof::Success<std::shared_ptr<DependencyPolicy>>{ result };
}
doof::Result<void, std::string> appendPolicyStrings(std::shared_ptr<std::vector<std::string>> target, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name, std::string manifestPath, std::string fieldPath) {
    auto _try_value_40 = manifestArray(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_40)) return doof::Failure<std::string>{doof::failure_error(_try_value_40)};
    const auto values = doof::success_value(_try_value_40);
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        auto _try_value_41 = manifestString((*values)[index], manifestPath, (((((fieldPath + std::string(".")) + name) + std::string("[")) + doof::to_string(index)) + std::string("]")));
        if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::failure_error(_try_value_41)};
        const auto value = doof::success_value(_try_value_41);
        if (value == std::string("")) {
            return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" entries must not be empty")) };
        }
        appendUnique(target, value);
    }
    return doof::Success<void>{};
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>, std::string> parseExternalDependencies(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory) {
    if (!manifestJsonHas(root, std::string("externalDependencies"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(std::vector<std::shared_ptr<ExternalDependency>>{}) };
    }
    auto _try_value_42 = manifestObject(manifestJsonField(root, std::string("externalDependencies")), manifestPath, std::string("externalDependencies"));
    if (doof::is_failure(_try_value_42)) return doof::Failure<std::string>{doof::failure_error(_try_value_42)};
    const auto values = doof::success_value(_try_value_42);
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependency>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependency>>>(std::vector<std::shared_ptr<ExternalDependency>>{});
    const auto& _iterable_43 = values;
    for (const auto& [name, value] : *_iterable_43) {
        const auto fieldPath = (std::string("externalDependencies.") + name);
        if (((name == std::string("")) || doof::string_contains(name, std::string("/"))) || doof::string_contains(name, std::string("\\"))) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": invalid external dependency name \"")) + name) + std::string("\"")) };
        }
        auto _try_value_44 = manifestObject(value, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_44)) return doof::Failure<std::string>{doof::failure_error(_try_value_44)};
        const auto object = doof::success_value(_try_value_44);
        auto _try_value_45 = requiredManifestString(object, std::string("kind"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_45)) return doof::Failure<std::string>{doof::failure_error(_try_value_45)};
        const auto kind = doof::success_value(_try_value_45);
        auto _try_value_46 = requiredManifestString(object, std::string("url"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::failure_error(_try_value_46)};
        const auto url = doof::success_value(_try_value_46);
        auto _try_value_47 = requiredManifestString(object, std::string("destination"), manifestPath, fieldPath);
        if (doof::is_failure(_try_value_47)) return doof::Failure<std::string>{doof::failure_error(_try_value_47)};
        const auto destination = doof::success_value(_try_value_47);
        const auto destinationPath = manifestJoinPath(rootDirectory, destination);
        if (!manifestPathWithinRoot(destinationPath, rootDirectory)) {
            return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".destination must stay within the package root")) };
        }
        auto _try_value_48 = parseExternalDependencyCommands(object, manifestPath, fieldPath);
        if (doof::is_failure(_try_value_48)) return doof::Failure<std::string>{doof::failure_error(_try_value_48)};
        const auto commands = doof::success_value(_try_value_48);
        if (kind == std::string("archive")) {
            auto _try_value_49 = requiredManifestString(object, std::string("sha256"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_49)) return doof::Failure<std::string>{doof::failure_error(_try_value_49)};
            const auto sha256 = doof::success_value(_try_value_49);
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
            auto _try_value_50 = parseExternalDependencyCopyFiles(object, manifestPath, fieldPath);
            if (doof::is_failure(_try_value_50)) return doof::Failure<std::string>{doof::failure_error(_try_value_50)};
            const auto copyFiles = doof::success_value(_try_value_50);
            result->push_back(std::make_shared<ExternalDependency>(name, kind, url, destination, doof::string_toLowerCase(sha256), stripComponents, copyFiles, std::string(""), std::string(""), commands));
            continue;
        }
        if (kind == std::string("git")) {
            auto _try_value_51 = requiredManifestString(object, std::string("ref"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_51)) return doof::Failure<std::string>{doof::failure_error(_try_value_51)};
            const auto ref = doof::success_value(_try_value_51);
            auto _try_value_52 = requiredManifestString(object, std::string("commit"), manifestPath, fieldPath);
            if (doof::is_failure(_try_value_52)) return doof::Failure<std::string>{doof::failure_error(_try_value_52)};
            const auto commit = doof::success_value(_try_value_52);
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
doof::Result<std::string, std::string> requiredManifestString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name, std::string manifestPath, std::string fieldPath) {
    if (!manifestJsonHas(object, name)) {
        return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" is required")) };
    }
    auto _try_value_53 = manifestString(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_53)) return doof::Failure<std::string>{doof::failure_error(_try_value_53)};
    const auto value = doof::success_value(_try_value_53);
    if (value == std::string("")) {
        return doof::Failure<std::string>{ ((((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(".")) + name) + std::string(" must not be empty")) };
    }
    return doof::Success<std::string>{ value };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>, std::string> parseExternalDependencyCopyFiles(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string manifestPath, std::string fieldPath) {
    if (!manifestJsonHas(object, std::string("copyFiles"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{}) };
    }
    auto _try_value_54 = manifestArray(manifestJsonField(object, std::string("copyFiles")), manifestPath, (fieldPath + std::string(".copyFiles")));
    if (doof::is_failure(_try_value_54)) return doof::Failure<std::string>{doof::failure_error(_try_value_54)};
    const auto values = doof::success_value(_try_value_54);
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>(std::vector<std::shared_ptr<ExternalDependencyCopyFile>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        const auto entryPath = (((fieldPath + std::string(".copyFiles[")) + doof::to_string(index)) + std::string("]"));
        auto _try_value_55 = manifestObject((*values)[index], manifestPath, entryPath);
        if (doof::is_failure(_try_value_55)) return doof::Failure<std::string>{doof::failure_error(_try_value_55)};
        const auto entry = doof::success_value(_try_value_55);
        auto _try_value_56 = requiredManifestString(entry, std::string("from"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_56)) return doof::Failure<std::string>{doof::failure_error(_try_value_56)};
        const auto source = doof::success_value(_try_value_56);
        auto _try_value_57 = requiredManifestString(entry, std::string("to"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_57)) return doof::Failure<std::string>{doof::failure_error(_try_value_57)};
        const auto destination = doof::success_value(_try_value_57);
        result->push_back(std::make_shared<ExternalDependencyCopyFile>(source, destination));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCopyFile>>>>{ result };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>, std::string> parseExternalDependencyCommands(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string manifestPath, std::string fieldPath) {
    if (!manifestJsonHas(object, std::string("commands"))) {
        return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>>{ std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{}) };
    }
    auto _try_value_58 = manifestArray(manifestJsonField(object, std::string("commands")), manifestPath, (fieldPath + std::string(".commands")));
    if (doof::is_failure(_try_value_58)) return doof::Failure<std::string>{doof::failure_error(_try_value_58)};
    const auto values = doof::success_value(_try_value_58);
    std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>> result = std::make_shared<std::vector<std::shared_ptr<ExternalDependencyCommand>>>(std::vector<std::shared_ptr<ExternalDependencyCommand>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        const auto entryPath = (((fieldPath + std::string(".commands[")) + doof::to_string(index)) + std::string("]"));
        auto _try_value_59 = manifestObject((*values)[index], manifestPath, entryPath);
        if (doof::is_failure(_try_value_59)) return doof::Failure<std::string>{doof::failure_error(_try_value_59)};
        const auto entry = doof::success_value(_try_value_59);
        auto _try_value_60 = requiredManifestString(entry, std::string("program"), manifestPath, entryPath);
        if (doof::is_failure(_try_value_60)) return doof::Failure<std::string>{doof::failure_error(_try_value_60)};
        const auto program = doof::success_value(_try_value_60);
        std::shared_ptr<std::vector<std::string>> args = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        if (manifestJsonHas(entry, std::string("args"))) {
            auto _try_value_61 = manifestArray(manifestJsonField(entry, std::string("args")), manifestPath, (entryPath + std::string(".args")));
            if (doof::is_failure(_try_value_61)) return doof::Failure<std::string>{doof::failure_error(_try_value_61)};
            const auto entries = doof::success_value(_try_value_61);
            for (int32_t argumentIndex = 0; argumentIndex < static_cast<int32_t>((entries)->size()); ++argumentIndex) {
                auto _try_value_62 = manifestString((*entries)[argumentIndex], manifestPath, (((entryPath + std::string(".args[")) + doof::to_string(argumentIndex)) + std::string("]")));
                if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::failure_error(_try_value_62)};
                const auto argument = doof::success_value(_try_value_62);
                args->push_back(argument);
            }
        }
        std::shared_ptr<doof::ordered_map<std::string, std::string>> env = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
        if (manifestJsonHas(entry, std::string("env"))) {
            auto _try_value_63 = manifestObject(manifestJsonField(entry, std::string("env")), manifestPath, (entryPath + std::string(".env")));
            if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::failure_error(_try_value_63)};
            const auto entries = doof::success_value(_try_value_63);
            const auto& _iterable_64 = entries;
            for (const auto& [key, value] : *_iterable_64) {
                if (key == std::string("")) {
                    return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + entryPath) + std::string(".env keys must not be empty")) };
                }
                auto _try_value_65 = manifestString(value, manifestPath, ((entryPath + std::string(".env.")) + key));
                if (doof::is_failure(_try_value_65)) return doof::Failure<std::string>{doof::failure_error(_try_value_65)};
                const auto text = doof::success_value(_try_value_65);
                doof::map_set(env, key, text, "", 0);
            }
        }
        auto workingDirectory = std::string("");
        if (manifestJsonHas(entry, std::string("workingDirectory"))) {
            auto _try_value_66 = manifestString(manifestJsonField(entry, std::string("workingDirectory")), manifestPath, (entryPath + std::string(".workingDirectory")));
            if (doof::is_failure(_try_value_66)) return doof::Failure<std::string>{doof::failure_error(_try_value_66)};
            const auto parsed = doof::success_value(_try_value_66);
            if (parsed == std::string("")) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + entryPath) + std::string(".workingDirectory must not be empty")) };
            }
            (workingDirectory = parsed);
        }
        result->push_back(std::make_shared<ExternalDependencyCommand>(program, args, env, workingDirectory));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<ExternalDependencyCommand>>>>{ result };
}
bool isSupportedExternalArchiveUrl(std::string url) {
    const auto lower = doof::string_toLowerCase(url);
    return (((((doof::string_endsWith(lower, std::string(".zip")) || doof::string_endsWith(lower, std::string(".tar.gz"))) || doof::string_endsWith(lower, std::string(".tgz"))) || doof::string_endsWith(lower, std::string(".tar.bz2"))) || doof::string_endsWith(lower, std::string(".tbz2"))) || doof::string_endsWith(lower, std::string(".tar.xz")));
}
bool isHexString(std::string value, int32_t length) {
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
std::shared_ptr<NativeBuildPlan> mergeNativeBuildPlans(std::shared_ptr<std::vector<std::shared_ptr<NativeBuildPlan>>> plans) {
    const auto merged = std::make_shared<NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    const auto& _iterable_67 = plans;
    for (const auto& plan : *_iterable_67) {
        appendNativeBuild(merged, plan);
    }
    return merged;
}
doof::Result<std::shared_ptr<NativeBuildPlan>, std::string> parseManifestNativeBuild(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory, std::string platform, std::string target) {
    const auto result = std::make_shared<NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    if (!manifestJsonHas(root, std::string("build"))) {
        return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
    }
    auto _try_value_68 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_68)) return doof::Failure<std::string>{doof::failure_error(_try_value_68)};
    const auto build = doof::success_value(_try_value_68);
    if (!manifestJsonHas(build, std::string("native"))) {
        return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
    }
    auto _try_value_69 = manifestObject(manifestJsonField(build, std::string("native")), manifestPath, std::string("build.native"));
    if (doof::is_failure(_try_value_69)) return doof::Failure<std::string>{doof::failure_error(_try_value_69)};
    const auto native = doof::success_value(_try_value_69);
    auto _try_value_70 = appendNativeFragment(result, native, manifestPath, rootDirectory, std::string("build.native"));
    if (doof::is_failure(_try_value_70)) return doof::Failure<std::string>{doof::failure_error(_try_value_70)};
    const auto platformKey = ((target == std::string("wasm")) ? std::string("wasm") : ((platform == std::string("ios-simulator")) ? std::string("iosSimulator") : ((platform == std::string("ios-device")) ? std::string("iosDevice") : platform)));
    if ((platformKey != std::string("")) && manifestJsonHas(native, platformKey)) {
        auto _try_value_71 = manifestObject(manifestJsonField(native, platformKey), manifestPath, (std::string("build.native.") + platformKey));
        if (doof::is_failure(_try_value_71)) return doof::Failure<std::string>{doof::failure_error(_try_value_71)};
        const auto platformValue = doof::success_value(_try_value_71);
        auto _try_value_72 = appendNativeFragment(result, platformValue, manifestPath, rootDirectory, (std::string("build.native.") + platformKey));
        if (doof::is_failure(_try_value_72)) return doof::Failure<std::string>{doof::failure_error(_try_value_72)};
    }
    return doof::Success<std::shared_ptr<NativeBuildPlan>>{ result };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseManifestResources(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory) {
    if (manifestJsonHas(root, std::string("resources"))) {
        return parseResourceArray(manifestJsonField(root, std::string("resources")), manifestPath, rootDirectory, std::string("resources"));
    }
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_73 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_73)) return doof::Failure<std::string>{doof::failure_error(_try_value_73)};
        const auto build = doof::success_value(_try_value_73);
        if (manifestJsonHas(build, std::string("resources"))) {
            return parseResourceArray(manifestJsonField(build, std::string("resources")), manifestPath, rootDirectory, std::string("build.resources"));
        }
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>>{ std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{}) };
}
doof::Result<std::string, std::string> parseManifestTarget(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath) {
    if (manifestJsonHas(root, std::string("target"))) {
        return manifestString(manifestJsonField(root, std::string("target")), manifestPath, std::string("target"));
    }
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_74 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_74)) return doof::Failure<std::string>{doof::failure_error(_try_value_74)};
        const auto build = doof::success_value(_try_value_74);
        if (manifestJsonHas(build, std::string("target"))) {
            return manifestString(manifestJsonField(build, std::string("target")), manifestPath, std::string("build.target"));
        }
    }
    return doof::Success<std::string>{ std::string("") };
}
doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>, std::string> parseMacOSApp(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory, std::string packageName, std::string packageVersion, std::string target) {
    if (target != std::string("macos-app")) {
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>>{ nullptr };
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> build = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_75 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_75)) return doof::Failure<std::string>{doof::failure_error(_try_value_75)};
        const auto parsedBuild = doof::success_value(_try_value_75);
        (build = parsedBuild);
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> nested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(build, std::string("macosApp"))) {
        auto _try_value_76 = manifestObject(manifestJsonField(build, std::string("macosApp")), manifestPath, std::string("build.macosApp"));
        if (doof::is_failure(_try_value_76)) return doof::Failure<std::string>{doof::failure_error(_try_value_76)};
        const auto parsedNested = doof::success_value(_try_value_76);
        (nested = parsedNested);
    }
    auto _try_value_77 = firstManifestString(root, std::string("executable"), build, std::string("executable"), build, std::string("targetExecutableName"), packageName, manifestPath, std::string("executable"));
    if (doof::is_failure(_try_value_77)) return doof::Failure<std::string>{doof::failure_error(_try_value_77)};
    const auto executableName = doof::success_value(_try_value_77);
    if (((executableName == std::string("")) || doof::string_contains(executableName, std::string("/"))) || doof::string_contains(executableName, std::string("\\"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": executable must be a file name without path separators")) };
    }
    const auto defaultBundleId = (std::string("dev.doof.") + sanitizeBundleName(((packageName == std::string("")) ? executableName : packageName)));
    auto _try_value_78 = firstManifestString(root, std::string("id"), nested, std::string("bundleId"), build, std::string("id"), defaultBundleId, manifestPath, std::string("build.macosApp.bundleId"));
    if (doof::is_failure(_try_value_78)) return doof::Failure<std::string>{doof::failure_error(_try_value_78)};
    const auto bundleId = doof::success_value(_try_value_78);
    auto _try_value_79 = firstManifestString(root, std::string("title"), nested, std::string("displayName"), build, std::string("title"), ((packageName == std::string("")) ? executableName : packageName), manifestPath, std::string("build.macosApp.displayName"));
    if (doof::is_failure(_try_value_79)) return doof::Failure<std::string>{doof::failure_error(_try_value_79)};
    const auto displayName = doof::success_value(_try_value_79);
    auto _try_value_80 = optionalManifestString(nested, std::string("version"), packageVersion, manifestPath, std::string("build.macosApp.version"));
    if (doof::is_failure(_try_value_80)) return doof::Failure<std::string>{doof::failure_error(_try_value_80)};
    const auto version = doof::success_value(_try_value_80);
    auto _try_value_81 = optionalManifestString(nested, std::string("category"), std::string("public.app-category.developer-tools"), manifestPath, std::string("build.macosApp.category"));
    if (doof::is_failure(_try_value_81)) return doof::Failure<std::string>{doof::failure_error(_try_value_81)};
    const auto category = doof::success_value(_try_value_81);
    auto _try_value_82 = optionalManifestString(nested, std::string("minimumSystemVersion"), std::string("11.0"), manifestPath, std::string("build.macosApp.minimumSystemVersion"));
    if (doof::is_failure(_try_value_82)) return doof::Failure<std::string>{doof::failure_error(_try_value_82)};
    const auto minimumSystemVersion = doof::success_value(_try_value_82);
    auto icon = std::string("");
    if (manifestJsonHas(root, std::string("icon"))) {
        auto _try_value_83 = manifestString(manifestJsonField(root, std::string("icon")), manifestPath, std::string("icon"));
        if (doof::is_failure(_try_value_83)) return doof::Failure<std::string>{doof::failure_error(_try_value_83)};
        const auto parsed = doof::success_value(_try_value_83);
        (icon = parsed);
    } else if (manifestJsonHas(nested, std::string("icon"))) {
        auto _try_value_84 = manifestString(manifestJsonField(nested, std::string("icon")), manifestPath, std::string("build.macosApp.icon"));
        if (doof::is_failure(_try_value_84)) return doof::Failure<std::string>{doof::failure_error(_try_value_84)};
        const auto parsed = doof::success_value(_try_value_84);
        (icon = parsed);
    } else if (manifestJsonHas(build, std::string("icon"))) {
        auto _try_value_85 = manifestString(manifestJsonField(build, std::string("icon")), manifestPath, std::string("build.icon"));
        if (doof::is_failure(_try_value_85)) return doof::Failure<std::string>{doof::failure_error(_try_value_85)};
        const auto parsed = doof::success_value(_try_value_85);
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
        auto _try_value_86 = manifestObject(manifestJsonField(nested, std::string("infoPlist")), manifestPath, std::string("build.macosApp.infoPlist"));
        if (doof::is_failure(_try_value_86)) return doof::Failure<std::string>{doof::failure_error(_try_value_86)};
        const auto parsedInfo = doof::success_value(_try_value_86);
        const auto& _iterable_87 = parsedInfo;
        for (const auto& [key, ignored] : *_iterable_87) {
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
        auto _try_value_88 = parseResourceArray(std::get<doof::JsonValue>(resourceValue), manifestPath, rootDirectory, resourceField);
        if (doof::is_failure(_try_value_88)) return doof::Failure<std::string>{doof::failure_error(_try_value_88)};
        const auto parsedResources = doof::success_value(_try_value_88);
        const auto& _iterable_89 = parsedResources;
        for (const auto& resource : *_iterable_89) {
            resources->push_back(std::make_shared<::app_src_macos_app_::MacOSAppResource>(resource->sourcePath, resource->destination));
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<::app_src_macos_app_::MacOSEmbeddedLibrary>>{});
    if (manifestJsonHas(nested, std::string("embeddedLibraries"))) {
        auto _try_value_90 = manifestArray(manifestJsonField(nested, std::string("embeddedLibraries")), manifestPath, std::string("build.macosApp.embeddedLibraries"));
        if (doof::is_failure(_try_value_90)) return doof::Failure<std::string>{doof::failure_error(_try_value_90)};
        const auto entries = doof::success_value(_try_value_90);
        for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
            auto _try_value_91 = manifestObject((*entries)[index], manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("]")));
            if (doof::is_failure(_try_value_91)) return doof::Failure<std::string>{doof::failure_error(_try_value_91)};
            const auto entry = doof::success_value(_try_value_91);
            const auto hasLibrary = manifestJsonHas(entry, std::string("library"));
            const auto hasPath = manifestJsonHas(entry, std::string("path"));
            if (hasLibrary == hasPath) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.macosApp.embeddedLibraries[")) + doof::to_string(index)) + std::string("] requires exactly one of library or path")) };
            }
            if (hasLibrary) {
                auto _try_value_92 = manifestString(manifestJsonField(entry, std::string("library")), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("].library")));
                if (doof::is_failure(_try_value_92)) return doof::Failure<std::string>{doof::failure_error(_try_value_92)};
                const auto library = doof::success_value(_try_value_92);
                if (((library == std::string("")) || doof::string_contains(library, std::string("/"))) || doof::string_contains(library, std::string("\\"))) {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded linked library names must not contain path separators")) };
                }
                embeddedLibraries->push_back(std::make_shared<::app_src_macos_app_::MacOSEmbeddedLibrary>(library, std::string("")));
            } else {
                auto _try_value_93 = manifestString(manifestJsonField(entry, std::string("path")), manifestPath, ((std::string("build.macosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("].path")));
                if (doof::is_failure(_try_value_93)) return doof::Failure<std::string>{doof::failure_error(_try_value_93)};
                const auto path = doof::success_value(_try_value_93);
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
doof::Result<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>, std::string> parseIOSApp(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory, std::string packageName, std::string packageVersion, std::string target) {
    if (target != std::string("ios-app")) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSAppConfig>>{ nullptr };
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> build = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(root, std::string("build"))) {
        auto _try_value_94 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
        if (doof::is_failure(_try_value_94)) return doof::Failure<std::string>{doof::failure_error(_try_value_94)};
        const auto parsedBuild = doof::success_value(_try_value_94);
        (build = parsedBuild);
    }
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> nested = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    if (manifestJsonHas(build, std::string("iosApp"))) {
        auto _try_value_95 = manifestObject(manifestJsonField(build, std::string("iosApp")), manifestPath, std::string("build.iosApp"));
        if (doof::is_failure(_try_value_95)) return doof::Failure<std::string>{doof::failure_error(_try_value_95)};
        const auto parsedNested = doof::success_value(_try_value_95);
        (nested = parsedNested);
    }
    auto _try_value_96 = firstManifestString(root, std::string("executable"), build, std::string("executable"), build, std::string("targetExecutableName"), packageName, manifestPath, std::string("executable"));
    if (doof::is_failure(_try_value_96)) return doof::Failure<std::string>{doof::failure_error(_try_value_96)};
    const auto executableName = doof::success_value(_try_value_96);
    if (((executableName == std::string("")) || doof::string_contains(executableName, std::string("/"))) || doof::string_contains(executableName, std::string("\\"))) {
        return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": executable must be a file name without path separators")) };
    }
    const auto defaultBundleId = (std::string("dev.doof.") + sanitizeBundleName(((packageName == std::string("")) ? executableName : packageName)));
    auto _try_value_97 = firstManifestString(root, std::string("id"), nested, std::string("bundleId"), build, std::string("id"), defaultBundleId, manifestPath, std::string("build.iosApp.bundleId"));
    if (doof::is_failure(_try_value_97)) return doof::Failure<std::string>{doof::failure_error(_try_value_97)};
    const auto bundleId = doof::success_value(_try_value_97);
    auto _try_value_98 = firstManifestString(root, std::string("title"), nested, std::string("displayName"), build, std::string("title"), ((packageName == std::string("")) ? executableName : packageName), manifestPath, std::string("build.iosApp.displayName"));
    if (doof::is_failure(_try_value_98)) return doof::Failure<std::string>{doof::failure_error(_try_value_98)};
    const auto displayName = doof::success_value(_try_value_98);
    auto _try_value_99 = optionalManifestString(nested, std::string("version"), packageVersion, manifestPath, std::string("build.iosApp.version"));
    if (doof::is_failure(_try_value_99)) return doof::Failure<std::string>{doof::failure_error(_try_value_99)};
    const auto version = doof::success_value(_try_value_99);
    auto _try_value_100 = optionalManifestString(nested, std::string("minimumDeploymentTarget"), std::string("16.0"), manifestPath, std::string("build.iosApp.minimumDeploymentTarget"));
    if (doof::is_failure(_try_value_100)) return doof::Failure<std::string>{doof::failure_error(_try_value_100)};
    const auto minimumDeploymentTarget = doof::success_value(_try_value_100);
    auto icon = std::string("");
    if (manifestJsonHas(root, std::string("icon"))) {
        auto _try_value_101 = manifestString(manifestJsonField(root, std::string("icon")), manifestPath, std::string("icon"));
        if (doof::is_failure(_try_value_101)) return doof::Failure<std::string>{doof::failure_error(_try_value_101)};
        const auto parsed = doof::success_value(_try_value_101);
        (icon = parsed);
    } else if (manifestJsonHas(nested, std::string("icon"))) {
        auto _try_value_102 = manifestString(manifestJsonField(nested, std::string("icon")), manifestPath, std::string("build.iosApp.icon"));
        if (doof::is_failure(_try_value_102)) return doof::Failure<std::string>{doof::failure_error(_try_value_102)};
        const auto parsed = doof::success_value(_try_value_102);
        (icon = parsed);
    } else if (manifestJsonHas(build, std::string("icon"))) {
        auto _try_value_103 = manifestString(manifestJsonField(build, std::string("icon")), manifestPath, std::string("build.icon"));
        if (doof::is_failure(_try_value_103)) return doof::Failure<std::string>{doof::failure_error(_try_value_103)};
        const auto parsed = doof::success_value(_try_value_103);
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
        auto _try_value_104 = manifestObject(manifestJsonField(nested, std::string("infoPlist")), manifestPath, std::string("build.iosApp.infoPlist"));
        if (doof::is_failure(_try_value_104)) return doof::Failure<std::string>{doof::failure_error(_try_value_104)};
        const auto parsedInfo = doof::success_value(_try_value_104);
        const auto& _iterable_105 = parsedInfo;
        for (const auto& [key, ignored] : *_iterable_105) {
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
        auto _try_value_106 = parseResourceArray(std::get<doof::JsonValue>(resourceValue), manifestPath, rootDirectory, resourceField);
        if (doof::is_failure(_try_value_106)) return doof::Failure<std::string>{doof::failure_error(_try_value_106)};
        const auto parsedResources = doof::success_value(_try_value_106);
        const auto& _iterable_107 = parsedResources;
        for (const auto& resource : *_iterable_107) {
            resources->push_back(std::make_shared<::app_src_ios_app_::IOSAppResource>(resource->sourcePath, resource->destination));
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>> embeddedLibraries = std::make_shared<std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>>(std::vector<std::shared_ptr<::app_src_ios_app_::IOSEmbeddedLibrary>>{});
    if (manifestJsonHas(nested, std::string("embeddedLibraries"))) {
        auto _try_value_108 = manifestArray(manifestJsonField(nested, std::string("embeddedLibraries")), manifestPath, std::string("build.iosApp.embeddedLibraries"));
        if (doof::is_failure(_try_value_108)) return doof::Failure<std::string>{doof::failure_error(_try_value_108)};
        const auto entries = doof::success_value(_try_value_108);
        for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
            const auto field = ((std::string("build.iosApp.embeddedLibraries[") + doof::to_string(index)) + std::string("]"));
            auto _try_value_109 = manifestObject((*entries)[index], manifestPath, field);
            if (doof::is_failure(_try_value_109)) return doof::Failure<std::string>{doof::failure_error(_try_value_109)};
            const auto entry = doof::success_value(_try_value_109);
            const auto hasLibrary = manifestJsonHas(entry, std::string("library"));
            const auto hasPath = manifestJsonHas(entry, std::string("path"));
            if (hasLibrary == hasPath) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + field) + std::string(" requires exactly one of library or path")) };
            }
            if (hasLibrary) {
                auto _try_value_110 = manifestString(manifestJsonField(entry, std::string("library")), manifestPath, (field + std::string(".library")));
                if (doof::is_failure(_try_value_110)) return doof::Failure<std::string>{doof::failure_error(_try_value_110)};
                const auto library = doof::success_value(_try_value_110);
                if (((library == std::string("")) || doof::string_contains(library, std::string("/"))) || doof::string_contains(library, std::string("\\"))) {
                    return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": embedded linked library names must not contain path separators")) };
                }
                embeddedLibraries->push_back(std::make_shared<::app_src_ios_app_::IOSEmbeddedLibrary>(library, std::string("")));
            } else {
                auto _try_value_111 = manifestString(manifestJsonField(entry, std::string("path")), manifestPath, (field + std::string(".path")));
                if (doof::is_failure(_try_value_111)) return doof::Failure<std::string>{doof::failure_error(_try_value_111)};
                const auto path = doof::success_value(_try_value_111);
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
doof::Result<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>, std::string> parseMacOSPackage(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory) {
    auto distDirectory = manifestJoinPath(rootDirectory, std::string("dist"));
    auto signing = std::string("developer-id");
    auto identity = std::string("");
    auto sandbox = false;
    auto entitlementsPath = std::string("");
    if (!manifestJsonHas(root, std::string("build"))) {
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
    }
    auto _try_value_112 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_112)) return doof::Failure<std::string>{doof::failure_error(_try_value_112)};
    const auto build = doof::success_value(_try_value_112);
    if (!manifestJsonHas(build, std::string("package"))) {
        return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
    }
    auto _try_value_113 = manifestObject(manifestJsonField(build, std::string("package")), manifestPath, std::string("build.package"));
    if (doof::is_failure(_try_value_113)) return doof::Failure<std::string>{doof::failure_error(_try_value_113)};
    const auto package = doof::success_value(_try_value_113);
    if (manifestJsonHas(package, std::string("distDir"))) {
        auto _try_value_114 = manifestString(manifestJsonField(package, std::string("distDir")), manifestPath, std::string("build.package.distDir"));
        if (doof::is_failure(_try_value_114)) return doof::Failure<std::string>{doof::failure_error(_try_value_114)};
        const auto value = doof::success_value(_try_value_114);
        (distDirectory = manifestJoinPath(rootDirectory, value));
        if (!manifestPathWithinRoot(distDirectory, rootDirectory)) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.distDir must stay within the package root")) };
        }
    }
    if (manifestJsonHas(package, std::string("macos"))) {
        auto _try_value_115 = manifestObject(manifestJsonField(package, std::string("macos")), manifestPath, std::string("build.package.macos"));
        if (doof::is_failure(_try_value_115)) return doof::Failure<std::string>{doof::failure_error(_try_value_115)};
        const auto macos = doof::success_value(_try_value_115);
        if (manifestJsonHas(macos, std::string("signing"))) {
            auto _try_value_116 = manifestString(manifestJsonField(macos, std::string("signing")), manifestPath, std::string("build.package.macos.signing"));
            if (doof::is_failure(_try_value_116)) return doof::Failure<std::string>{doof::failure_error(_try_value_116)};
            const auto value = doof::success_value(_try_value_116);
            if ((value != std::string("developer-id")) && (value != std::string("ad-hoc"))) {
                return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.signing must be one of \"developer-id\", \"ad-hoc\"")) };
            }
            (signing = value);
        }
        if (manifestJsonHas(macos, std::string("identity"))) {
            auto _try_value_117 = manifestString(manifestJsonField(macos, std::string("identity")), manifestPath, std::string("build.package.macos.identity"));
            if (doof::is_failure(_try_value_117)) return doof::Failure<std::string>{doof::failure_error(_try_value_117)};
            const auto value = doof::success_value(_try_value_117);
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
            auto _try_value_118 = manifestString(manifestJsonField(macos, std::string("entitlements")), manifestPath, std::string("build.package.macos.entitlements"));
            if (doof::is_failure(_try_value_118)) return doof::Failure<std::string>{doof::failure_error(_try_value_118)};
            const auto value = doof::success_value(_try_value_118);
            (entitlementsPath = manifestJoinPath(rootDirectory, value));
            if (!manifestPathWithinRoot(entitlementsPath, rootDirectory)) {
                return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.macos.entitlements must stay within the package root")) };
            }
        }
    }
    return doof::Success<std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>>{ std::make_shared<::app_src_macos_app_::MacOSPackageConfig>(distDirectory, signing, identity, sandbox, entitlementsPath) };
}
doof::Result<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>, std::string> parseIOSPackage(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> root, std::string manifestPath, std::string rootDirectory) {
    auto identity = std::string("");
    auto provisioningProfilePath = std::string("");
    if (!manifestJsonHas(root, std::string("build"))) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
    auto _try_value_119 = manifestObject(manifestJsonField(root, std::string("build")), manifestPath, std::string("build"));
    if (doof::is_failure(_try_value_119)) return doof::Failure<std::string>{doof::failure_error(_try_value_119)};
    const auto build = doof::success_value(_try_value_119);
    if (!manifestJsonHas(build, std::string("package"))) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
    auto _try_value_120 = manifestObject(manifestJsonField(build, std::string("package")), manifestPath, std::string("build.package"));
    if (doof::is_failure(_try_value_120)) return doof::Failure<std::string>{doof::failure_error(_try_value_120)};
    const auto package = doof::success_value(_try_value_120);
    if (!manifestJsonHas(package, std::string("ios"))) {
        return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(std::string(""), std::string("")) };
    }
    auto _try_value_121 = manifestObject(manifestJsonField(package, std::string("ios")), manifestPath, std::string("build.package.ios"));
    if (doof::is_failure(_try_value_121)) return doof::Failure<std::string>{doof::failure_error(_try_value_121)};
    const auto ios = doof::success_value(_try_value_121);
    if (manifestJsonHas(ios, std::string("identity"))) {
        auto _try_value_122 = manifestString(manifestJsonField(ios, std::string("identity")), manifestPath, std::string("build.package.ios.identity"));
        if (doof::is_failure(_try_value_122)) return doof::Failure<std::string>{doof::failure_error(_try_value_122)};
        const auto value = doof::success_value(_try_value_122);
        (identity = value);
    }
    if (manifestJsonHas(ios, std::string("provisioningProfile"))) {
        auto _try_value_123 = manifestString(manifestJsonField(ios, std::string("provisioningProfile")), manifestPath, std::string("build.package.ios.provisioningProfile"));
        if (doof::is_failure(_try_value_123)) return doof::Failure<std::string>{doof::failure_error(_try_value_123)};
        const auto value = doof::success_value(_try_value_123);
        (provisioningProfilePath = manifestJoinPath(rootDirectory, value));
        if (!manifestPathWithinRoot(provisioningProfilePath, rootDirectory)) {
            return doof::Failure<std::string>{ ((std::string("Invalid doof.json at ") + manifestPath) + std::string(": build.package.ios.provisioningProfile must stay within the package root")) };
        }
    }
    return doof::Success<std::shared_ptr<::app_src_ios_app_::IOSPackageConfig>>{ std::make_shared<::app_src_ios_app_::IOSPackageConfig>(identity, provisioningProfilePath) };
}
doof::Result<std::string, std::string> optionalManifestString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string key, std::string fallback, std::string manifestPath, std::string fieldPath) {
    if (!manifestJsonHas(object, key)) {
        return doof::Success<std::string>{ fallback };
    }
    return manifestString(manifestJsonField(object, key), manifestPath, fieldPath);
}
doof::Result<std::string, std::string> firstManifestString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> first, std::string firstKey, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> second, std::string secondKey, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> third, std::string thirdKey, std::string fallback, std::string manifestPath, std::string fieldPath) {
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
std::string sanitizeBundleName(std::string value) {
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
bool manifestPathWithinRoot(std::string path, std::string rootDirectory) {
    const auto boundary = (doof::string_endsWith(rootDirectory, std::string("/")) ? rootDirectory : (rootDirectory + std::string("/")));
    return ((path == rootDirectory) || doof::string_startsWith(path, boundary));
}
bool isManagedMacOSPlistKey(std::string key) {
    const auto keys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("CFBundleDevelopmentRegion"), std::string("CFBundleDisplayName"), std::string("CFBundleExecutable"), std::string("CFBundleIconFile"), std::string("CFBundleIdentifier"), std::string("CFBundleInfoDictionaryVersion"), std::string("CFBundleName"), std::string("CFBundlePackageType"), std::string("CFBundleShortVersionString"), std::string("CFBundleVersion"), std::string("LSApplicationCategoryType"), std::string("LSMinimumSystemVersion"), std::string("NSHighResolutionCapable"), std::string("NSPrincipalClass")});
    return doof::array_contains(keys, key, "", 0);
}
bool isManagedIOSPlistKey(std::string key) {
    const auto keys = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("CFBundleDevelopmentRegion"), std::string("CFBundleDisplayName"), std::string("CFBundleExecutable"), std::string("CFBundleIdentifier"), std::string("CFBundleInfoDictionaryVersion"), std::string("CFBundleName"), std::string("CFBundlePackageType"), std::string("CFBundleShortVersionString"), std::string("CFBundleVersion"), std::string("LSRequiresIPhoneOS"), std::string("MinimumOSVersion"), std::string("UIDeviceFamily"), std::string("UILaunchStoryboardName"), std::string("UIApplicationSceneManifest")});
    return doof::array_contains(keys, key, "", 0);
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>, std::string> parseResourceArray(doof::JsonValue value, std::string manifestPath, std::string rootDirectory, std::string fieldPath) {
    auto _try_value_124 = manifestArray(value, manifestPath, fieldPath);
    if (doof::is_failure(_try_value_124)) return doof::Failure<std::string>{doof::failure_error(_try_value_124)};
    const auto entries = doof::success_value(_try_value_124);
    std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>> resources = std::make_shared<std::vector<std::shared_ptr<PackageResource>>>(std::vector<std::shared_ptr<PackageResource>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
        auto source = std::string("");
        auto destination = std::string("");
        {
            auto _case_subject = (*entries)[index];
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
                auto _try_value_125 = manifestString(manifestJsonField(object, std::string("from")), manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].from")));
                if (doof::is_failure(_try_value_125)) return doof::Failure<std::string>{doof::failure_error(_try_value_125)};
                const auto parsedSource = doof::success_value(_try_value_125);
                auto _try_value_126 = manifestString(manifestJsonField(object, std::string("to")), manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].to")));
                if (doof::is_failure(_try_value_126)) return doof::Failure<std::string>{doof::failure_error(_try_value_126)};
                const auto parsedDestination = doof::success_value(_try_value_126);
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
        auto _try_value_127 = normalizeResourceDestination(destination, manifestPath, (((fieldPath + std::string("[")) + doof::to_string(index)) + std::string("].to")));
        if (doof::is_failure(_try_value_127)) return doof::Failure<std::string>{doof::failure_error(_try_value_127)};
        const auto normalizedDestination = doof::success_value(_try_value_127);
        resources->push_back(std::make_shared<PackageResource>(sourcePath, normalizedDestination));
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<PackageResource>>>>{ resources };
}
doof::Result<std::string, std::string> normalizeResourceDestination(std::string destination, std::string manifestPath, std::string fieldPath) {
    const auto portable = doof::string_replaceAll(destination, std::string("\\"), std::string("/"));
    if (doof::string_startsWith(portable, std::string("/")) || (((static_cast<int32_t>(portable.size()) >= 3) && (portable[1] == U'\u003A')) && (portable[2] == U'\u002F'))) {
        return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must be relative")) };
    }
    std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_128 = doof::string_split(portable, std::string("/"));
    for (const auto& segment : *_iterable_128) {
        if ((segment == std::string("")) || (segment == std::string("."))) {
            continue;
        }
        if (segment == std::string("..")) {
            if (static_cast<int32_t>((segments)->size()) == 0) {
                return doof::Failure<std::string>{ ((((std::string("Invalid doof.json at ") + manifestPath) + std::string(": ")) + fieldPath) + std::string(" must stay within the executable resource directory")) };
            }
            const auto ignored = [&]() -> std::string { auto _try_value = doof::array_pop(segments); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
            continue;
        }
        segments->push_back(segment);
    }
    auto normalized = std::string("");
    const auto& _iterable_129 = segments;
    for (const auto& segment : *_iterable_129) {
        if (normalized != std::string("")) {
            (normalized = (normalized + std::string("/")));
        }
        (normalized = (normalized + segment));
    }
    return doof::Success<std::string>{ normalized };
}
doof::Result<void, std::string> appendNativeFragment(std::shared_ptr<NativeBuildPlan> target, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> fragment, std::string manifestPath, std::string rootDirectory, std::string fieldPath) {
    auto _try_value_130 = appendStringArrayField(target->includePaths, fragment, std::string("includePaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_130)) return doof::Failure<std::string>{doof::failure_error(_try_value_130)};
    auto _try_value_131 = appendStringArrayField(target->sourceFiles, fragment, std::string("sourceFiles"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_131)) return doof::Failure<std::string>{doof::failure_error(_try_value_131)};
    auto _try_value_132 = appendStringArrayField(target->libraryPaths, fragment, std::string("libraryPaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_132)) return doof::Failure<std::string>{doof::failure_error(_try_value_132)};
    auto _try_value_133 = appendStringArrayField(target->extraCopyPaths, fragment, std::string("extraCopyPaths"), manifestPath, fieldPath, rootDirectory);
    if (doof::is_failure(_try_value_133)) return doof::Failure<std::string>{doof::failure_error(_try_value_133)};
    auto _try_value_134 = appendStringArrayField(target->linkLibraries, fragment, std::string("linkLibraries"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_134)) return doof::Failure<std::string>{doof::failure_error(_try_value_134)};
    auto _try_value_135 = appendStringArrayField(target->frameworks, fragment, std::string("frameworks"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_135)) return doof::Failure<std::string>{doof::failure_error(_try_value_135)};
    auto _try_value_136 = appendStringArrayField(target->pkgConfigPackages, fragment, std::string("pkgConfigPackages"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_136)) return doof::Failure<std::string>{doof::failure_error(_try_value_136)};
    auto _try_value_137 = appendStringArrayField(target->defines, fragment, std::string("defines"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_137)) return doof::Failure<std::string>{doof::failure_error(_try_value_137)};
    auto _try_value_138 = appendStringArrayField(target->compilerFlags, fragment, std::string("compilerFlags"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_138)) return doof::Failure<std::string>{doof::failure_error(_try_value_138)};
    auto _try_value_139 = appendStringArrayField(target->linkerFlags, fragment, std::string("linkerFlags"), manifestPath, fieldPath, std::string(""));
    if (doof::is_failure(_try_value_139)) return doof::Failure<std::string>{doof::failure_error(_try_value_139)};
    return doof::Success<void>{};
}
doof::Result<void, std::string> appendStringArrayField(std::shared_ptr<std::vector<std::string>> target, std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name, std::string manifestPath, std::string fieldPath, std::string pathRoot) {
    if (!manifestJsonHas(object, name)) {
        return doof::Success<void>{};
    }
    auto _try_value_140 = manifestArray(manifestJsonField(object, name), manifestPath, ((fieldPath + std::string(".")) + name));
    if (doof::is_failure(_try_value_140)) return doof::Failure<std::string>{doof::failure_error(_try_value_140)};
    const auto values = doof::success_value(_try_value_140);
    for (int32_t index = 0; index < static_cast<int32_t>((values)->size()); ++index) {
        auto _try_value_141 = manifestString((*values)[index], manifestPath, (((((fieldPath + std::string(".")) + name) + std::string("[")) + doof::to_string(index)) + std::string("]")));
        if (doof::is_failure(_try_value_141)) return doof::Failure<std::string>{doof::failure_error(_try_value_141)};
        const auto value = doof::success_value(_try_value_141);
        const auto normalized = ((pathRoot == std::string("")) ? value : manifestJoinPath(pathRoot, value));
        appendUnique(target, normalized);
    }
    return doof::Success<void>{};
}
void appendNativeBuild(std::shared_ptr<NativeBuildPlan> target, std::shared_ptr<NativeBuildPlan> source) {
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
void appendUniqueValues(std::shared_ptr<std::vector<std::string>> target, std::shared_ptr<std::vector<std::string>> values) {
    const auto& _iterable_142 = values;
    for (const auto& value : *_iterable_142) {
        appendUnique(target, value);
    }
}
void appendUnique(std::shared_ptr<std::vector<std::string>> target, std::string value) {
    const auto& _iterable_143 = target;
    for (const auto& existing : *_iterable_143) {
        if (existing == value) {
            return;
        }
    }
    target->push_back(value);
}
doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> manifestObject(doof::JsonValue value, std::string manifestPath, std::string fieldPath) {
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
}
doof::Result<std::shared_ptr<std::vector<doof::JsonValue>>, std::string> manifestArray(doof::JsonValue value, std::string manifestPath, std::string fieldPath) {
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
}
doof::Result<std::string, std::string> manifestString(doof::JsonValue value, std::string manifestPath, std::string fieldPath) {
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
}
}
