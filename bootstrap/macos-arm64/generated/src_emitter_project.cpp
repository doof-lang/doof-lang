#include "src_emitter_project.hpp"

namespace app_src_emitter_project_ {
using namespace ::app_src_emitter_module_;
using namespace ::app_src_package_manifest_;




#line 39 "/src/emitter-project.do"
std::shared_ptr<ProjectEmission> planProjectEmission(const std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission>& graph, const std::shared_ptr<std::vector<std::shared_ptr<NativePackageInput>>>& packages) {
#line 43 "/src/emitter-project.do"
    const auto project = std::make_shared<ProjectEmission>(graph->modules, std::make_shared<std::vector<std::shared_ptr<ProjectSupportFile>>>(std::vector<std::shared_ptr<ProjectSupportFile>>{}), std::make_shared<std::vector<std::shared_ptr<ProjectNativeCopy>>>(std::vector<std::shared_ptr<ProjectNativeCopy>>{}), std::make_shared<::app_src_package_manifest_::NativeBuildPlan>(std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), std::make_shared<std::vector<std::string>>(std::vector<std::string>{})), std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
#line 44 "/src/emitter-project.do"
    if (graph->wasmSupportSource != std::string("")) {
#line 45 "/src/emitter-project.do"
        project->supportFiles->push_back(std::make_shared<ProjectSupportFile>(std::string("doof_wasm.cpp"), graph->wasmSupportSource));
#line 46 "/src/emitter-project.do"
        project->nativeBuild->sourceFiles->push_back(std::string("doof_wasm.cpp"));
#line 47 "/src/emitter-project.do"
        (project->wasmExportNames = graph->wasmExportNames);
    }
#line 49 "/src/emitter-project.do"
    const auto& _iterable_2 = packages;
    for (const auto& package_ : *_iterable_2) {
#line 50 "/src/emitter-project.do"
        planPackageSupportFiles(project, graph, package_);
#line 51 "/src/emitter-project.do"
        planPackageNativeBuild(project, package_);
    }
#line 53 "/src/emitter-project.do"
    return project;
}
#line 56 "/src/emitter-project.do"
void planPackageSupportFiles(const std::shared_ptr<ProjectEmission>& project, const std::shared_ptr<::app_src_emitter_module_::ModuleGraphEmission>& graph, const std::shared_ptr<NativePackageInput>& package_) {
#line 61 "/src/emitter-project.do"
    const auto& _iterable_4 = graph->modules;
    for (const auto& module : *_iterable_4) {
#line 62 "/src/emitter-project.do"
        const auto relativeModulePath = logicalSuffix(module->modulePath, package_->logicalPrefix);
#line 63 "/src/emitter-project.do"
        if (doof::is_null(relativeModulePath)) {
#line 63 "/src/emitter-project.do"
            continue;
        }
#line 64 "/src/emitter-project.do"
        const auto relativeHeaderPath = replaceDoExtension(relativeModulePath.value());
#line 65 "/src/emitter-project.do"
        addSupportFile(project->supportFiles, std::make_shared<ProjectSupportFile>(projectJoinPath(package_->outputRoot, relativeHeaderPath), ((std::string("#pragma once\n#include \"") + module->headerName) + std::string("\"\n"))));
    }
}
#line 75 "/src/emitter-project.do"
void planPackageNativeBuild(const std::shared_ptr<ProjectEmission>& project, const std::shared_ptr<NativePackageInput>& package_) {
#line 76 "/src/emitter-project.do"
    const auto native = package_->manifest->nativeBuild;
#line 77 "/src/emitter-project.do"
    auto copiedAny = false;
#line 79 "/src/emitter-project.do"
    const auto& _iterable_6 = native->includePaths;
    for (const auto& includePath : *_iterable_6) {
#line 80 "/src/emitter-project.do"
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, includePath);
#line 81 "/src/emitter-project.do"
        appendUnique(project->nativeBuild->includePaths, relativePath);
#line 82 "/src/emitter-project.do"
        (copiedAny = true);
    }
#line 84 "/src/emitter-project.do"
    const auto& _iterable_8 = native->sourceFiles;
    for (const auto& sourcePath : *_iterable_8) {
#line 85 "/src/emitter-project.do"
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, sourcePath);
#line 86 "/src/emitter-project.do"
        appendUnique(project->nativeBuild->sourceFiles, relativePath);
#line 87 "/src/emitter-project.do"
        (copiedAny = true);
    }
#line 89 "/src/emitter-project.do"
    const auto& _iterable_10 = native->libraryPaths;
    for (const auto& libraryPath : *_iterable_10) {
#line 90 "/src/emitter-project.do"
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, libraryPath);
#line 91 "/src/emitter-project.do"
        appendUnique(project->nativeBuild->libraryPaths, relativePath);
#line 92 "/src/emitter-project.do"
        (copiedAny = true);
    }
#line 94 "/src/emitter-project.do"
    const auto& _iterable_12 = native->extraCopyPaths;
    for (const auto& extraCopyPath : *_iterable_12) {
#line 95 "/src/emitter-project.do"
        const auto relativePath = addNativeCopy(project->nativeCopies, package_, extraCopyPath);
#line 96 "/src/emitter-project.do"
        appendUnique(project->nativeBuild->includePaths, projectParentPath(relativePath));
#line 97 "/src/emitter-project.do"
        (copiedAny = true);
    }
#line 100 "/src/emitter-project.do"
    if (copiedAny) {
#line 101 "/src/emitter-project.do"
        appendUnique(project->nativeBuild->includePaths, package_->outputRoot);
#line 102 "/src/emitter-project.do"
        if (package_->outputRoot != std::string("")) {
#line 103 "/src/emitter-project.do"
            appendUnique(project->nativeBuild->includePaths, projectParentPath(package_->outputRoot));
        }
    }
#line 106 "/src/emitter-project.do"
    appendUniqueValues(project->nativeBuild->linkLibraries, native->linkLibraries);
#line 107 "/src/emitter-project.do"
    appendUniqueValues(project->nativeBuild->frameworks, native->frameworks);
#line 108 "/src/emitter-project.do"
    appendUniqueValues(project->nativeBuild->pkgConfigPackages, native->pkgConfigPackages);
#line 109 "/src/emitter-project.do"
    appendUniqueValues(project->nativeBuild->defines, native->defines);
#line 110 "/src/emitter-project.do"
    appendUniqueValues(project->nativeBuild->compilerFlags, native->compilerFlags);
#line 111 "/src/emitter-project.do"
    appendUniqueValues(project->nativeBuild->linkerFlags, native->linkerFlags);
}
#line 114 "/src/emitter-project.do"
std::string addNativeCopy(const std::shared_ptr<std::vector<std::shared_ptr<ProjectNativeCopy>>>& copies, const std::shared_ptr<NativePackageInput>& package_, const std::string& sourcePath) {
#line 119 "/src/emitter-project.do"
    const auto relativeWithinPackage = diskSuffix(sourcePath, package_->manifest->rootDirectory);
#line 120 "/src/emitter-project.do"
    const auto relativePath = projectJoinPath(package_->outputRoot, relativeWithinPackage);
#line 121 "/src/emitter-project.do"
    const auto& _iterable_14 = copies;
    for (const auto& existing : *_iterable_14) {
#line 122 "/src/emitter-project.do"
        if (existing->relativePath == relativePath) {
#line 123 "/src/emitter-project.do"
            if (existing->sourcePath != sourcePath) {
#line 124 "/src/emitter-project.do"
                doof::panic((((((std::string("Native package copy collision for ") + relativePath) + std::string(": ")) + existing->sourcePath) + std::string(" conflicts with ")) + sourcePath));
            }
#line 129 "/src/emitter-project.do"
            return relativePath;
        }
    }
#line 132 "/src/emitter-project.do"
    copies->push_back(std::make_shared<ProjectNativeCopy>(sourcePath, relativePath));
#line 133 "/src/emitter-project.do"
    return relativePath;
}
#line 136 "/src/emitter-project.do"
std::optional<std::string> logicalSuffix(const std::string& path, const std::string& prefix) {
#line 137 "/src/emitter-project.do"
    if (path == prefix) {
#line 137 "/src/emitter-project.do"
        return std::string("");
    }
#line 138 "/src/emitter-project.do"
    const auto boundary = (prefix + std::string("/"));
#line 139 "/src/emitter-project.do"
    if (!doof::string_startsWith(path, boundary)) {
#line 139 "/src/emitter-project.do"
        return std::nullopt;
    }
#line 140 "/src/emitter-project.do"
    return doof::string_substring(path, static_cast<int32_t>(boundary.size()), static_cast<int32_t>(path.size()));
}
#line 143 "/src/emitter-project.do"
std::string diskSuffix(const std::string& path, const std::string& root) {
#line 144 "/src/emitter-project.do"
    if (path == root) {
#line 144 "/src/emitter-project.do"
        return std::string("");
    }
#line 145 "/src/emitter-project.do"
    const auto boundary = (doof::string_endsWith(root, std::string("/")) ? root : (root + std::string("/")));
#line 146 "/src/emitter-project.do"
    if (!doof::string_startsWith(path, boundary)) {
#line 147 "/src/emitter-project.do"
        doof::panic((((std::string("Native path ") + path) + std::string(" is outside package root ")) + root));
    }
#line 149 "/src/emitter-project.do"
    return doof::string_substring(path, static_cast<int32_t>(boundary.size()), static_cast<int32_t>(path.size()));
}
#line 152 "/src/emitter-project.do"
std::string replaceDoExtension(const std::string& path) {
#line 153 "/src/emitter-project.do"
    if (doof::string_endsWith(path, std::string(".do"))) {
#line 153 "/src/emitter-project.do"
        return (doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 3)) + std::string(".hpp"));
    }
#line 154 "/src/emitter-project.do"
    return (path + std::string(".hpp"));
}
#line 157 "/src/emitter-project.do"
std::string projectJoinPath(const std::string& directory, const std::string& suffix) {
#line 158 "/src/emitter-project.do"
    if (directory == std::string("")) {
#line 158 "/src/emitter-project.do"
        return suffix;
    }
#line 159 "/src/emitter-project.do"
    if (suffix == std::string("")) {
#line 159 "/src/emitter-project.do"
        return directory;
    }
#line 160 "/src/emitter-project.do"
    if (doof::string_endsWith(directory, std::string("/"))) {
#line 160 "/src/emitter-project.do"
        return (directory + suffix);
    }
#line 161 "/src/emitter-project.do"
    return ((directory + std::string("/")) + suffix);
}
#line 164 "/src/emitter-project.do"
std::string projectParentPath(const std::string& path) {
#line 165 "/src/emitter-project.do"
    auto separator = -1;
#line 166 "/src/emitter-project.do"
    auto index = 0;
#line 167 "/src/emitter-project.do"
    while (index < static_cast<int32_t>(path.size())) {
#line 168 "/src/emitter-project.do"
        if (doof::string_at(path, index, "src/emitter-project", 168) == U'\u002F') {
#line 168 "/src/emitter-project.do"
            (separator = index);
        }
#line 169 "/src/emitter-project.do"
        (index = (index + 1));
    }
#line 171 "/src/emitter-project.do"
    if (separator < 0) {
#line 171 "/src/emitter-project.do"
        return std::string("");
    }
#line 172 "/src/emitter-project.do"
    return doof::string_substring(path, 0, separator);
}
#line 175 "/src/emitter-project.do"
void addSupportFile(const std::shared_ptr<std::vector<std::shared_ptr<ProjectSupportFile>>>& files, const std::shared_ptr<ProjectSupportFile>& file) {
#line 176 "/src/emitter-project.do"
    const auto& _iterable_16 = files;
    for (const auto& existing : *_iterable_16) {
#line 177 "/src/emitter-project.do"
        if (existing->relativePath == file->relativePath) {
#line 178 "/src/emitter-project.do"
            if (existing->content != file->content) {
#line 179 "/src/emitter-project.do"
                doof::panic((std::string("Generated support file collision for ") + file->relativePath));
            }
#line 181 "/src/emitter-project.do"
            return;
        }
    }
#line 184 "/src/emitter-project.do"
    files->push_back(file);
}
#line 187 "/src/emitter-project.do"
void appendUniqueValues(const std::shared_ptr<std::vector<std::string>>& target, const std::shared_ptr<std::vector<std::string>>& values) {
#line 188 "/src/emitter-project.do"
    const auto& _iterable_18 = values;
    for (const auto& value : *_iterable_18) {
#line 188 "/src/emitter-project.do"
        appendUnique(target, value);
    }
}
#line 191 "/src/emitter-project.do"
void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value) {
#line 192 "/src/emitter-project.do"
    const auto& _iterable_20 = target;
    for (const auto& existing : *_iterable_20) {
#line 192 "/src/emitter-project.do"
        if (existing == value) {
#line 192 "/src/emitter-project.do"
            return;
        }
    }
#line 193 "/src/emitter-project.do"
    target->push_back(value);
}
#line 1 "<doof-generated>"
}
