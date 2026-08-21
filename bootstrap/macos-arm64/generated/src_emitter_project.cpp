#include "src_emitter_project.hpp"

namespace app_src_emitter_project_ {
using namespace ::app_src_emitter_module_;
using namespace ::app_src_package_manifest_;




std::shared_ptr<ProjectEmission> planProjectEmission(const std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission>& graph, const std::shared_ptr<std::vector<std::shared_ptr<NativePackageInput>>>& packages) {
    const auto project = std::make_shared<ProjectEmission>(graph->modules, std::make_shared<std::vector<std::shared_ptr<ProjectSupportFile>>>(std::vector<std::shared_ptr<ProjectSupportFile>>{}), std::make_shared<std::vector<std::shared_ptr<ProjectNativeCopy>>>(std::vector<std::shared_ptr<ProjectNativeCopy>>{}), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
    if (graph->wasmSupportSource != std::string("")) {
        project->supportFiles->push_back(std::make_shared<ProjectSupportFile>(std::string("doof_wasm.cpp"), graph->wasmSupportSource));
        project->nativeBuild->sourceFiles->push_back(std::string("doof_wasm.cpp"));
        (project->wasmExportNames = graph->wasmExportNames);
    }
    const auto& _iterable_2 = packages;
    for (const auto& package_ : *_iterable_2) {
        planPackageSupportFiles(project, graph, package_);
        planPackageNativeBuild(project, package_);
    }
    return project;
}
void planPackageSupportFiles(const std::shared_ptr<ProjectEmission>& project, const std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission>& graph, const std::shared_ptr<NativePackageInput>& package_) {
    const auto& _iterable_4 = graph->modules;
    for (const auto& module : *_iterable_4) {
        const auto relativeModulePath = logicalSuffix(module->modulePath, package_->logicalPrefix);
        if (doof::is_null(relativeModulePath)) {
            continue;
        }
        const auto relativeHeaderPath = replaceDoExtension(relativeModulePath.value());
        addSupportFile(project->supportFiles, std::make_shared<ProjectSupportFile>(projectJoinPath(package_->outputRoot, relativeHeaderPath), ((std::string("#pragma once\n#include \"") + module->headerName) + std::string("\"\n"))));
    }
}
void planPackageNativeBuild(const std::shared_ptr<ProjectEmission>& project, const std::shared_ptr<NativePackageInput>& package_) {
    const auto native = package_->manifest->nativeBuild;
    auto copiedAny = false;
    const auto& _iterable_6 = native->includePaths;
    for (const auto& includePath : *_iterable_6) {
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, includePath);
        appendUnique(project->nativeBuild->includePaths, relativePath);
        (copiedAny = true);
    }
    const auto& _iterable_8 = native->sourceFiles;
    for (const auto& sourcePath : *_iterable_8) {
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, sourcePath);
        appendUnique(project->nativeBuild->sourceFiles, relativePath);
        (copiedAny = true);
    }
    const auto& _iterable_10 = native->libraryPaths;
    for (const auto& libraryPath : *_iterable_10) {
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, libraryPath);
        appendUnique(project->nativeBuild->libraryPaths, relativePath);
        (copiedAny = true);
    }
    const auto& _iterable_12 = native->extraCopyPaths;
    for (const auto& extraCopyPath : *_iterable_12) {
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
std::string addNativeCopy(const std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>>& copies, const std::shared_ptr<NativePackageInput>& package_, const std::string& sourcePath) {
    const auto relativeWithinPackage = diskSuffix(sourcePath, package_->manifest->rootDirectory);
    const auto relativePath = projectJoinPath(package_->outputRoot, relativeWithinPackage);
    const auto& _iterable_14 = copies;
    for (const auto& existing : *_iterable_14) {
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
std::optional<std::string> logicalSuffix(const std::string& path, const std::string& prefix) {
    if (path == prefix) {
        return std::string("");
    }
    const auto boundary = (prefix + std::string("/"));
    if (!doof::string_startsWith(path, boundary)) {
        return std::nullopt;
    }
    return doof::string_substring(path, static_cast<int32_t>(boundary.size()), static_cast<int32_t>(path.size()));
}
std::string diskSuffix(const std::string& path, const std::string& root) {
    if (path == root) {
        return std::string("");
    }
    const auto boundary = (doof::string_endsWith(root, std::string("/")) ? root : (root + std::string("/")));
    if (!doof::string_startsWith(path, boundary)) {
        doof::panic((((std::string("Native path ") + path) + std::string(" is outside package root ")) + root));
    }
    return doof::string_substring(path, static_cast<int32_t>(boundary.size()), static_cast<int32_t>(path.size()));
}
std::string replaceDoExtension(const std::string& path) {
    if (doof::string_endsWith(path, std::string(".do"))) {
        return (doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 3)) + std::string(".hpp"));
    }
    return (path + std::string(".hpp"));
}
std::string projectJoinPath(const std::string& directory, const std::string& suffix) {
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
std::string projectParentPath(const std::string& path) {
    auto separator = -1;
    auto index = 0;
    while (index < static_cast<int32_t>(path.size())) {
        if (doof::string_at(path, index, "src/emitter-project", 168) == U'\u002F') {
            (separator = index);
        }
        (index = (index + 1));
    }
    if (separator < 0) {
        return std::string("");
    }
    return doof::string_substring(path, 0, separator);
}
void addSupportFile(const std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>>& files, const std::shared_ptr<ProjectSupportFile>& file) {
    const auto& _iterable_16 = files;
    for (const auto& existing : *_iterable_16) {
        if (existing->relativePath == file->relativePath) {
            if (existing->content != file->content) {
                doof::panic((std::string("Generated support file collision for ") + file->relativePath));
            }
            return;
        }
    }
    files->push_back(file);
}
void appendUniqueValues(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<std::vector<std::string>>& values) {
    const auto& _iterable_18 = values;
    for (const auto& value : *_iterable_18) {
        appendUnique(target, value);
    }
}
void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value) {
    const auto& _iterable_20 = target;
    for (const auto& existing : *_iterable_20) {
        if (existing == value) {
            return;
        }
    }
    target->push_back(value);
}
}
