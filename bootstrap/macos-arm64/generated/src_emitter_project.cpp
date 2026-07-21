#include "src_emitter_project.hpp"
#include <cmath>
#include "src_emitter_module.hpp"
#include "src_package_manifest.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_emitter_project_ {
using namespace ::app_src_emitter_module_;
using namespace ::app_src_package_manifest_;

doof::JsonObject NativePackageInput::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["logicalPrefix"] = doof::json_value(this->logicalPrefix);
    (*_json)["outputRoot"] = doof::json_value(this->outputRoot);
    (*_json)["manifest"] = doof::json_value(this->manifest->toJsonObject());
    return _json;
}
doof::Result<std::shared_ptr<NativePackageInput>, std::string> NativePackageInput::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_logicalPrefix = _object->find("logicalPrefix");
    if (_iterator_logicalPrefix == _object->end()) { return doof::Failure<std::string>{"Missing required field \"logicalPrefix\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_logicalPrefix->second) : doof::json_is_string(_iterator_logicalPrefix->second)))) { return doof::Failure<std::string>{"Field \"logicalPrefix\" expected string but got " + std::string(doof::json_type_name(_iterator_logicalPrefix->second))}; }
    auto _field_logicalPrefix = (_lenient ? doof::json_as_string_lenient(_iterator_logicalPrefix->second) : doof::json_as_string(_iterator_logicalPrefix->second));
    auto _iterator_outputRoot = _object->find("outputRoot");
    if (_iterator_outputRoot == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputRoot\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_outputRoot->second) : doof::json_is_string(_iterator_outputRoot->second)))) { return doof::Failure<std::string>{"Field \"outputRoot\" expected string but got " + std::string(doof::json_type_name(_iterator_outputRoot->second))}; }
    auto _field_outputRoot = (_lenient ? doof::json_as_string_lenient(_iterator_outputRoot->second) : doof::json_as_string(_iterator_outputRoot->second));
    auto _iterator_manifest = _object->find("manifest");
    if (_iterator_manifest == _object->end()) { return doof::Failure<std::string>{"Missing required field \"manifest\""}; }
    if (!(doof::json_is_object(_iterator_manifest->second))) { return doof::Failure<std::string>{"Field \"manifest\" expected object but got " + std::string(doof::json_type_name(_iterator_manifest->second))}; }
    auto _field_manifest = doof::success_value(::app_src_package_manifest_::PackageManifest::fromJsonValue(_iterator_manifest->second, _lenient));
    return doof::Success<std::shared_ptr<NativePackageInput>>{std::make_shared<NativePackageInput>(_field_logicalPrefix, _field_outputRoot, _field_manifest)};
}

doof::JsonObject ProjectNativeCopy::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["sourcePath"] = doof::json_value(this->sourcePath);
    (*_json)["relativePath"] = doof::json_value(this->relativePath);
    return _json;
}
doof::Result<std::shared_ptr<ProjectNativeCopy>, std::string> ProjectNativeCopy::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_sourcePath = _object->find("sourcePath");
    if (_iterator_sourcePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourcePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourcePath->second) : doof::json_is_string(_iterator_sourcePath->second)))) { return doof::Failure<std::string>{"Field \"sourcePath\" expected string but got " + std::string(doof::json_type_name(_iterator_sourcePath->second))}; }
    auto _field_sourcePath = (_lenient ? doof::json_as_string_lenient(_iterator_sourcePath->second) : doof::json_as_string(_iterator_sourcePath->second));
    auto _iterator_relativePath = _object->find("relativePath");
    if (_iterator_relativePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"relativePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_relativePath->second) : doof::json_is_string(_iterator_relativePath->second)))) { return doof::Failure<std::string>{"Field \"relativePath\" expected string but got " + std::string(doof::json_type_name(_iterator_relativePath->second))}; }
    auto _field_relativePath = (_lenient ? doof::json_as_string_lenient(_iterator_relativePath->second) : doof::json_as_string(_iterator_relativePath->second));
    return doof::Success<std::shared_ptr<ProjectNativeCopy>>{std::make_shared<ProjectNativeCopy>(_field_sourcePath, _field_relativePath)};
}

doof::JsonObject ProjectSupportFile::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["relativePath"] = doof::json_value(this->relativePath);
    (*_json)["content"] = doof::json_value(this->content);
    return _json;
}
doof::Result<std::shared_ptr<ProjectSupportFile>, std::string> ProjectSupportFile::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_relativePath = _object->find("relativePath");
    if (_iterator_relativePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"relativePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_relativePath->second) : doof::json_is_string(_iterator_relativePath->second)))) { return doof::Failure<std::string>{"Field \"relativePath\" expected string but got " + std::string(doof::json_type_name(_iterator_relativePath->second))}; }
    auto _field_relativePath = (_lenient ? doof::json_as_string_lenient(_iterator_relativePath->second) : doof::json_as_string(_iterator_relativePath->second));
    auto _iterator_content = _object->find("content");
    if (_iterator_content == _object->end()) { return doof::Failure<std::string>{"Missing required field \"content\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_content->second) : doof::json_is_string(_iterator_content->second)))) { return doof::Failure<std::string>{"Field \"content\" expected string but got " + std::string(doof::json_type_name(_iterator_content->second))}; }
    auto _field_content = (_lenient ? doof::json_as_string_lenient(_iterator_content->second) : doof::json_as_string(_iterator_content->second));
    return doof::Success<std::shared_ptr<ProjectSupportFile>>{std::make_shared<ProjectSupportFile>(_field_relativePath, _field_content)};
}

doof::JsonObject ProjectEmission::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["modules"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->modules->size()); for (const auto& _element : *this->modules) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["supportFiles"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->supportFiles->size()); for (const auto& _element : *this->supportFiles) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["nativeCopies"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->nativeCopies->size()); for (const auto& _element : *this->nativeCopies) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["nativeBuild"] = doof::json_value(this->nativeBuild->toJsonObject());
    (*_json)["wasmExportNames"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->wasmExportNames->size()); for (const auto& _element : *this->wasmExportNames) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<ProjectEmission>, std::string> ProjectEmission::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>> _field_modules;
    if (auto _iterator_modules = _object->find("modules"); _iterator_modules != _object->end()) {
        if (!(doof::json_is_array(_iterator_modules->second))) { return doof::Failure<std::string>{"Field \"modules\" expected array but got " + std::string(doof::json_type_name(_iterator_modules->second))}; }
        _field_modules = [&]() { const auto* _array = doof::json_as_array(_iterator_modules->second); auto _values = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(::app_src_emitter_module_::ModuleEmission::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_modules = std::make_shared<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>(std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>>> _field_supportFiles;
    if (auto _iterator_supportFiles = _object->find("supportFiles"); _iterator_supportFiles != _object->end()) {
        if (!(doof::json_is_array(_iterator_supportFiles->second))) { return doof::Failure<std::string>{"Field \"supportFiles\" expected array but got " + std::string(doof::json_type_name(_iterator_supportFiles->second))}; }
        _field_supportFiles = [&]() { const auto* _array = doof::json_as_array(_iterator_supportFiles->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ProjectSupportFile>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(ProjectSupportFile::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_supportFiles = std::make_shared<std::vector<std::shared_ptr<ProjectSupportFile>>>(std::vector<std::shared_ptr<ProjectSupportFile>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>>> _field_nativeCopies;
    if (auto _iterator_nativeCopies = _object->find("nativeCopies"); _iterator_nativeCopies != _object->end()) {
        if (!(doof::json_is_array(_iterator_nativeCopies->second))) { return doof::Failure<std::string>{"Field \"nativeCopies\" expected array but got " + std::string(doof::json_type_name(_iterator_nativeCopies->second))}; }
        _field_nativeCopies = [&]() { const auto* _array = doof::json_as_array(_iterator_nativeCopies->second); auto _values = std::make_shared<std::vector<std::shared_ptr<ProjectNativeCopy>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(ProjectNativeCopy::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_nativeCopies = std::make_shared<std::vector<std::shared_ptr<ProjectNativeCopy>>>(std::vector<std::shared_ptr<ProjectNativeCopy>>{});
    }
    std::optional<std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>> _field_nativeBuild;
    if (auto _iterator_nativeBuild = _object->find("nativeBuild"); _iterator_nativeBuild != _object->end()) {
        if (!(doof::json_is_object(_iterator_nativeBuild->second))) { return doof::Failure<std::string>{"Field \"nativeBuild\" expected object but got " + std::string(doof::json_type_name(_iterator_nativeBuild->second))}; }
        _field_nativeBuild = doof::success_value(::app_src_package_manifest_::NativeBuildPlan::fromJsonValue(_iterator_nativeBuild->second, _lenient));
    } else {
        _field_nativeBuild = std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_wasmExportNames;
    if (auto _iterator_wasmExportNames = _object->find("wasmExportNames"); _iterator_wasmExportNames != _object->end()) {
        if (!(doof::json_is_array(_iterator_wasmExportNames->second))) { return doof::Failure<std::string>{"Field \"wasmExportNames\" expected array but got " + std::string(doof::json_type_name(_iterator_wasmExportNames->second))}; }
        _field_wasmExportNames = [&]() { const auto* _array = doof::json_as_array(_iterator_wasmExportNames->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_wasmExportNames = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    return doof::Success<std::shared_ptr<ProjectEmission>>{std::make_shared<ProjectEmission>(_field_modules.value(), _field_supportFiles.value(), _field_nativeCopies.value(), _field_nativeBuild.value(), _field_wasmExportNames.value())};
}
std::shared_ptr<ProjectEmission> planProjectEmission(std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> graph, std::shared_ptr<std::vector<std::shared_ptr<NativePackageInput>>> packages) {
    const auto project = std::make_shared<ProjectEmission>(graph->modules, std::make_shared<std::vector<std::shared_ptr<ProjectSupportFile>>>(std::vector<std::shared_ptr<ProjectSupportFile>>{}), std::make_shared<std::vector<std::shared_ptr<ProjectNativeCopy>>>(std::vector<std::shared_ptr<ProjectNativeCopy>>{}), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    if (graph->wasmSupportSource != std::string("")) {
        project->supportFiles->push_back(std::make_shared<ProjectSupportFile>(std::string("doof_wasm.cpp"), graph->wasmSupportSource));
        project->nativeBuild->sourceFiles->push_back(std::string("doof_wasm.cpp"));
        (project->wasmExportNames = graph->wasmExportNames);
    }
    const auto& _iterable_1 = packages;
    for (const auto& package_ : *_iterable_1) {
        planPackageSupportFiles(project, graph, package_);
        planPackageNativeBuild(project, package_);
    }
    return project;
}
void planPackageSupportFiles(std::shared_ptr<ProjectEmission> project, std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission> graph, std::shared_ptr<NativePackageInput> package_) {
    const auto& _iterable_2 = graph->modules;
    for (const auto& module : *_iterable_2) {
        const auto relativeModulePath = logicalSuffix(module->modulePath, package_->logicalPrefix);
        if (doof::is_null(relativeModulePath)) {
            continue;
        }
        const auto relativeHeaderPath = replaceDoExtension(relativeModulePath.value());
        addSupportFile(project->supportFiles, std::make_shared<ProjectSupportFile>(projectJoinPath(package_->outputRoot, relativeHeaderPath), ((std::string("#pragma once\n#include \"") + module->headerName) + std::string("\"\n"))));
    }
}
void planPackageNativeBuild(std::shared_ptr<ProjectEmission> project, std::shared_ptr<NativePackageInput> package_) {
    const auto native = package_->manifest->nativeBuild;
    auto copiedAny = false;
    const auto& _iterable_3 = native->includePaths;
    for (const auto& includePath : *_iterable_3) {
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, includePath);
        appendUnique(project->nativeBuild->includePaths, relativePath);
        (copiedAny = true);
    }
    const auto& _iterable_4 = native->sourceFiles;
    for (const auto& sourcePath : *_iterable_4) {
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, sourcePath);
        appendUnique(project->nativeBuild->sourceFiles, relativePath);
        (copiedAny = true);
    }
    const auto& _iterable_5 = native->libraryPaths;
    for (const auto& libraryPath : *_iterable_5) {
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, libraryPath);
        appendUnique(project->nativeBuild->libraryPaths, relativePath);
        (copiedAny = true);
    }
    const auto& _iterable_6 = native->extraCopyPaths;
    for (const auto& extraCopyPath : *_iterable_6) {
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, extraCopyPath);
        appendUnique(project->nativeBuild->includePaths, projectParentPath(relativePath));
        (copiedAny = true);
    }
    if (copiedAny) {
        appendUnique(project->nativeBuild->includePaths, package_->outputRoot);
        if (package_->outputRoot != std::string("")) {
            appendUnique(project->nativeBuild->includePaths, projectParentPath(package_->outputRoot));
        }
    }
    appendUniqueValues(project->nativeBuild->linkLibraries, native->linkLibraries);
    appendUniqueValues(project->nativeBuild->frameworks, native->frameworks);
    appendUniqueValues(project->nativeBuild->pkgConfigPackages, native->pkgConfigPackages);
    appendUniqueValues(project->nativeBuild->defines, native->defines);
    appendUniqueValues(project->nativeBuild->compilerFlags, native->compilerFlags);
    appendUniqueValues(project->nativeBuild->linkerFlags, native->linkerFlags);
}
std::string addNativeCopy(std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>> copies, std::shared_ptr<NativePackageInput> package_, std::string sourcePath) {
    const auto relativeWithinPackage = diskSuffix(sourcePath, package_->manifest->rootDirectory);
    const auto relativePath = projectJoinPath(package_->outputRoot, relativeWithinPackage);
    const auto& _iterable_7 = copies;
    for (const auto& existing : *_iterable_7) {
        if (existing->relativePath == relativePath) {
            if (existing->sourcePath != sourcePath) {
                doof::panic((((((std::string("Native package copy collision for ") + relativePath) + std::string(": ")) + existing->sourcePath) + std::string(" conflicts with ")) + sourcePath));
            }
            return relativePath;
        }
    }
    copies->push_back(std::make_shared<ProjectNativeCopy>(sourcePath, relativePath));
    return relativePath;
}
std::optional<std::string> logicalSuffix(std::string path, std::string prefix) {
    if (path == prefix) {
        return std::string("");
    }
    const auto boundary = (prefix + std::string("/"));
    if (!doof::string_startsWith(path, boundary)) {
        return std::nullopt;
    }
    return doof::string_substring(path, static_cast<int32_t>(boundary.size()), static_cast<int32_t>(path.size()));
}
std::string diskSuffix(std::string path, std::string root) {
    if (path == root) {
        return std::string("");
    }
    const auto boundary = (doof::string_endsWith(root, std::string("/")) ? root : (root + std::string("/")));
    if (!doof::string_startsWith(path, boundary)) {
        doof::panic((((std::string("Native path ") + path) + std::string(" is outside package root ")) + root));
    }
    return doof::string_substring(path, static_cast<int32_t>(boundary.size()), static_cast<int32_t>(path.size()));
}
std::string replaceDoExtension(std::string path) {
    if (doof::string_endsWith(path, std::string(".do"))) {
        return (doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 3)) + std::string(".hpp"));
    }
    return (path + std::string(".hpp"));
}
std::string projectJoinPath(std::string directory, std::string suffix) {
    if (directory == std::string("")) {
        return suffix;
    }
    if (suffix == std::string("")) {
        return directory;
    }
    if (doof::string_endsWith(directory, std::string("/"))) {
        return (directory + suffix);
    }
    return ((directory + std::string("/")) + suffix);
}
std::string projectParentPath(std::string path) {
    auto separator = -1;
    auto index = 0;
    while (index < static_cast<int32_t>(path.size())) {
        if (path[index] == U'\u002F') {
            (separator = index);
        }
        (index = (index + 1));
    }
    if (separator < 0) {
        return std::string("");
    }
    return doof::string_substring(path, 0, separator);
}
void addSupportFile(std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>> files, std::shared_ptr<ProjectSupportFile> file) {
    const auto& _iterable_8 = files;
    for (const auto& existing : *_iterable_8) {
        if (existing->relativePath == file->relativePath) {
            if (existing->content != file->content) {
                doof::panic((std::string("Generated support file collision for ") + file->relativePath));
            }
            return;
        }
    }
    files->push_back(file);
}
void appendUniqueValues(std::shared_ptr<std::vector<std::string>> target, std::shared_ptr<std::vector<std::string>> values) {
    const auto& _iterable_9 = values;
    for (const auto& value : *_iterable_9) {
        appendUnique(target, value);
    }
}
void appendUnique(std::shared_ptr<std::vector<std::string>> target, std::string value) {
    const auto& _iterable_10 = target;
    for (const auto& existing : *_iterable_10) {
        if (existing == value) {
            return;
        }
    }
    target->push_back(value);
}
}
