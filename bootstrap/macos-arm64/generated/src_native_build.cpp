#include "src_native_build.hpp"

namespace app_src_native_build_ {
using namespace ::app_src_emitter_module_;
using namespace ::app_src_package_manifest_;
using namespace ::std_::crypto::index;



bool isMsvcCompiler(const std::string& compiler) {
    const auto normalized = doof::string_toLowerCase(doof::string_replaceAll(compiler, std::string("\\"), std::string("/")));
    auto slash = -1;
    for (int32_t index = 0; index < static_cast<int32_t>(normalized.size()); ++index) {
        if (doof::string_at(normalized, index, "src/native-build", 50) == U'\u002F') {
            (slash = index);
        }
    }
    const auto name = ((slash < 0) ? normalized : doof::string_substring(normalized, (slash + 1), static_cast<int32_t>(normalized.size())));
    return ((name == std::string("cl")) || (name == std::string("cl.exe")));
}
std::shared_ptr<NativeCompilePlan> planNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, NativeBuildMode mode, const std::string& platform, const std::shared_ptr<std::vector<std::string>>& wasmExportNames, bool wasm, bool wasmCommand) {
    if (isMsvcCompiler(compiler) && !wasm) {
        return planMsvcNativeCompile(compiler, outputDirectory, outputPath, modules, native, mode);
    }
    const auto release = (mode == NativeBuildMode::Release);
    const auto profile = (mode == NativeBuildMode::Profile);
    const auto swiftLink = hasSwiftSource(native->sourceFiles);
    std::shared_ptr<std::vector<std::string>> compileArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-std=c++17")});
    if (release || profile) {
        (static_cast<void>(compileArguments->push_back(std::string("-O2"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("-DNDEBUG"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("-ffunction-sections"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("-fdata-sections"))), std::monostate{});
        if ((release && !wasm) && !swiftLink) {
            (static_cast<void>(compileArguments->push_back(std::string("-flto"))), std::monostate{});
        }
    }
    if (profile) {
        (static_cast<void>(compileArguments->push_back(std::string("-g"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("-fno-omit-frame-pointer"))), std::monostate{});
    }
    if (wasm) {
        (static_cast<void>(compileArguments->push_back(std::string("-Oz"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("-flto"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("-fwasm-exceptions"))), std::monostate{});
    }
    const auto& _iterable_3 = native->defines;
    for (const auto& define : *_iterable_3) {
        (static_cast<void>(compileArguments->push_back((std::string("-D") + define))), std::monostate{});
    }
    (static_cast<void>(compileArguments->push_back(std::string("-I"))), std::monostate{});
    (static_cast<void>(compileArguments->push_back(outputDirectory)), std::monostate{});
    const auto& _iterable_5 = native->includePaths;
    for (const auto& includePath : *_iterable_5) {
        (static_cast<void>(compileArguments->push_back(std::string("-I"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(resolveBuildPath(outputDirectory, includePath))), std::monostate{});
    }
    const auto& _iterable_7 = native->compilerFlags;
    for (const auto& flag : *_iterable_7) {
        (static_cast<void>(compileArguments->push_back(flag)), std::monostate{});
    }
    std::shared_ptr<NativeCompileTask> precompiledHeaderTask = nullptr;
    auto clangPchPath = std::string("");
    if ((static_cast<int32_t>((modules)->size()) > 1) && !wasm) {
        const auto runtimeHeader = resolveBuildPath(outputDirectory, std::string("doof_runtime.hpp"));
        const auto clangPch = usesClangPrecompiledHeader(compiler, platform);
        const auto pchPath = (runtimeHeader + (clangPch ? std::string(".pch") : std::string(".gch")));
        std::shared_ptr<std::vector<std::string>> pchArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        const auto& _iterable_9 = compileArguments;
        for (const auto& argument : *_iterable_9) {
            (static_cast<void>(pchArguments->push_back(argument)), std::monostate{});
        }
        const auto dependencyFile = (pchPath + std::string(".d"));
        (static_cast<void>(pchArguments->push_back(std::string("-MMD"))), std::monostate{});
        (static_cast<void>(pchArguments->push_back(std::string("-MF"))), std::monostate{});
        (static_cast<void>(pchArguments->push_back(dependencyFile)), std::monostate{});
        (static_cast<void>(pchArguments->push_back(std::string("-x"))), std::monostate{});
        (static_cast<void>(pchArguments->push_back(std::string("c++-header"))), std::monostate{});
        (static_cast<void>(pchArguments->push_back(runtimeHeader)), std::monostate{});
        (static_cast<void>(pchArguments->push_back(std::string("-o"))), std::monostate{});
        (static_cast<void>(pchArguments->push_back(pchPath)), std::monostate{});
        (precompiledHeaderTask = std::make_shared<NativeCompileTask>((std::string("pch:") + pchPath), compiler, runtimeHeader, pchPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, doof::array_drainToReadonly(pchArguments, "", 0)));
        if (clangPch) {
            (clangPchPath = pchPath);
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{});
    std::shared_ptr<std::vector<std::string>> objectPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
        const auto sourcePath = resolveBuildPath(outputDirectory, doof::array_at(modules, index, "src/native-build", 148)->sourceName);
        const auto objectPath = resolveBuildPath(outputDirectory, (std::string(".doof-objects/generated/") + replaceSourceExtension(doof::array_at(modules, index, "src/native-build", 149)->sourceName, std::string(".o"))));
        const auto dependencyFile = (objectPath + std::string(".d"));
        const auto arguments = copyArguments(compileArguments);
        if (clangPchPath != std::string("")) {
            (static_cast<void>(arguments->push_back(std::string("-include-pch"))), std::monostate{});
            (static_cast<void>(arguments->push_back(clangPchPath)), std::monostate{});
        }
        (static_cast<void>(arguments->push_back(std::string("-MMD"))), std::monostate{});
        (static_cast<void>(arguments->push_back(std::string("-MF"))), std::monostate{});
        (static_cast<void>(arguments->push_back(dependencyFile)), std::monostate{});
        (static_cast<void>(appendObjectArguments(arguments, sourcePath, objectPath)), std::monostate{});
        (static_cast<void>(compileTasks->push_back(std::make_shared<NativeCompileTask>((std::string("object:") + objectPath), compiler, sourcePath, objectPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), (!doof::is_null(precompiledHeaderTask)), doof::array_drainToReadonly(arguments, "", 0)))), std::monostate{});
        (static_cast<void>(objectPaths->push_back(objectPath)), std::monostate{});
    }
    for (int32_t index = 0; index < static_cast<int32_t>((native->sourceFiles)->size()); ++index) {
        const auto sourcePath = resolveBuildPath(outputDirectory, doof::array_at(native->sourceFiles, index, "src/native-build", 174));
        const auto swiftSource = isSwiftSource(sourcePath);
        const auto objectPath = resolveBuildPath(outputDirectory, ((std::string(".doof-objects/native/") + ::std_::crypto::index::sha1HexString(doof::array_at(native->sourceFiles, index, "src/native-build", 176))) + std::string(".o")));
        const auto dependencyFile = (swiftSource ? std::string("") : (objectPath + std::string(".d")));
        const auto cSource = isCSource(sourcePath);
        const auto arguments = (swiftSource ? swiftObjectArguments(sourcePath, objectPath, mode) : copyNativeCompileArguments(compileArguments, cSource));
        if (!swiftSource) {
            (static_cast<void>(arguments->push_back(std::string("-MMD"))), std::monostate{});
            (static_cast<void>(arguments->push_back(std::string("-MF"))), std::monostate{});
            (static_cast<void>(arguments->push_back(dependencyFile)), std::monostate{});
            (static_cast<void>(appendObjectArguments(arguments, sourcePath, objectPath)), std::monostate{});
        }
        const auto taskCompiler = (swiftSource ? std::string("swiftc") : (cSource ? deriveCCompiler(compiler) : compiler));
        (static_cast<void>(compileTasks->push_back(std::make_shared<NativeCompileTask>((std::string("object:") + objectPath), taskCompiler, sourcePath, objectPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, doof::array_drainToReadonly(arguments, "", 0)))), std::monostate{});
        (static_cast<void>(objectPaths->push_back(objectPath)), std::monostate{});
    }
    std::shared_ptr<std::vector<std::string>> linkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_13 = objectPaths;
    for (const auto& objectPath : *_iterable_13) {
        (static_cast<void>(linkArguments->push_back(objectPath)), std::monostate{});
    }
    const auto& _iterable_15 = native->libraryPaths;
    for (const auto& libraryPath : *_iterable_15) {
        (static_cast<void>(linkArguments->push_back((std::string("-L") + resolveBuildPath(outputDirectory, libraryPath)))), std::monostate{});
    }
    const auto& _iterable_17 = native->linkLibraries;
    for (const auto& library : *_iterable_17) {
        (static_cast<void>(linkArguments->push_back((std::string("-l") + library))), std::monostate{});
    }
    const auto& _iterable_19 = native->frameworks;
    for (const auto& framework : *_iterable_19) {
        (static_cast<void>(linkArguments->push_back(std::string("-framework"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(framework)), std::monostate{});
    }
    if (swiftLink && (platform == std::string("macos"))) {
        (static_cast<void>(linkArguments->push_back(std::string("-Xlinker"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("-lc++"))), std::monostate{});
    }
    if ((release || profile) && !wasm) {
        if (release && !swiftLink) {
            (static_cast<void>(linkArguments->push_back(std::string("-flto"))), std::monostate{});
        }
        (static_cast<void>(appendOptimizedLinkerArguments(linkArguments, platform, swiftLink, release)), std::monostate{});
    }
    if (!wasm) {
        const auto& _iterable_21 = native->linkerFlags;
        for (const auto& flag : *_iterable_21) {
            (static_cast<void>(linkArguments->push_back(flag)), std::monostate{});
        }
    }
    if (wasm) {
        (static_cast<void>(linkArguments->push_back(std::string("-Oz"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("-flto"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("--strip-debug"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("-sASSERTIONS=0"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("-sMALLOC=emmalloc"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("-sSTANDALONE_WASM=1"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("-sFILESYSTEM=0"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("-fwasm-exceptions"))), std::monostate{});
        if (!wasmCommand) {
            (static_cast<void>(linkArguments->push_back(std::string("--no-entry"))), std::monostate{});
            (static_cast<void>(linkArguments->push_back((std::string("-sEXPORTED_FUNCTIONS=") + wasmExportList(wasmExportNames)))), std::monostate{});
        }
        const auto& _iterable_23 = native->linkerFlags;
        for (const auto& flag : *_iterable_23) {
            (static_cast<void>(linkArguments->push_back(flag)), std::monostate{});
        }
    }
    (static_cast<void>(linkArguments->push_back(std::string("-o"))), std::monostate{});
    (static_cast<void>(linkArguments->push_back(outputPath)), std::monostate{});
    return std::make_shared<NativeCompilePlan>(compiler, (swiftLink ? std::string("swiftc") : compiler), std::make_shared<std::vector<std::shared_ptr<NativeBuildSupportFile>>>(std::vector<std::shared_ptr<NativeBuildSupportFile>>{}), precompiledHeaderTask, compileTasks, linkArguments, outputPath);
}
std::shared_ptr<NativeCompilePlan> planMsvcNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, NativeBuildMode mode) {
    const auto release = (mode == NativeBuildMode::Release);
    const auto profile = (mode == NativeBuildMode::Profile);
    std::shared_ptr<std::vector<std::string>> compileArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("/nologo"), std::string("/std:c++17"), std::string("/EHsc"), std::string("/utf-8"), std::string("/Zc:__cplusplus"), std::string("/permissive-")});
    if (release || profile) {
        (static_cast<void>(compileArguments->push_back(std::string("/O2"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("/DNDEBUG"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("/Gy"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("/Gw"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("/GL"))), std::monostate{});
    }
    if (profile) {
        (static_cast<void>(compileArguments->push_back(std::string("/Zi"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(std::string("/Oy-"))), std::monostate{});
    }
    const auto& _iterable_25 = native->defines;
    for (const auto& define : *_iterable_25) {
        (static_cast<void>(compileArguments->push_back((std::string("/D") + define))), std::monostate{});
    }
    (static_cast<void>(compileArguments->push_back(std::string("/I"))), std::monostate{});
    (static_cast<void>(compileArguments->push_back(outputDirectory)), std::monostate{});
    const auto& _iterable_27 = native->includePaths;
    for (const auto& includePath : *_iterable_27) {
        (static_cast<void>(compileArguments->push_back(std::string("/I"))), std::monostate{});
        (static_cast<void>(compileArguments->push_back(resolveBuildPath(outputDirectory, includePath))), std::monostate{});
    }
    const auto& _iterable_29 = native->compilerFlags;
    for (const auto& flag : *_iterable_29) {
        (static_cast<void>(compileArguments->push_back(flag)), std::monostate{});
    }
    std::shared_ptr<std::vector<std::shared_ptr<NativeBuildSupportFile>>> supportFiles = std::make_shared<std::vector<std::shared_ptr<NativeBuildSupportFile>>>(std::vector<std::shared_ptr<NativeBuildSupportFile>>{});
    std::shared_ptr<NativeCompileTask> precompiledHeaderTask = nullptr;
    auto pchHeaderName = std::string("");
    auto pchPath = std::string("");
    auto pchObjectPath = std::string("");
    if (static_cast<int32_t>((modules)->size()) > 1) {
        (pchHeaderName = std::string("doof_msvc_pch.hpp"));
        const auto pchHeaderPath = resolveBuildPath(outputDirectory, pchHeaderName);
        const auto pchSourcePath = resolveBuildPath(outputDirectory, std::string("doof_msvc_pch.cpp"));
        (pchPath = resolveBuildPath(outputDirectory, std::string(".doof-objects/pch/doof_msvc.pch")));
        (pchObjectPath = resolveBuildPath(outputDirectory, std::string(".doof-objects/pch/doof_msvc_pch.obj")));
        const auto pchDependencyPath = (pchPath + std::string(".json"));
        (static_cast<void>(supportFiles->push_back(std::make_shared<NativeBuildSupportFile>(pchHeaderPath, msvcPchHeaderSource()))), std::monostate{});
        (static_cast<void>(supportFiles->push_back(std::make_shared<NativeBuildSupportFile>(pchSourcePath, ((std::string("#include \"") + pchHeaderName) + std::string("\"\n"))))), std::monostate{});
        const auto pchArguments = copyArguments(compileArguments);
        (static_cast<void>(pchArguments->push_back(std::string("/TP"))), std::monostate{});
        (static_cast<void>(pchArguments->push_back((std::string("/Yc") + pchHeaderName))), std::monostate{});
        (static_cast<void>(pchArguments->push_back((std::string("/Fp") + pchPath))), std::monostate{});
        (static_cast<void>(pchArguments->push_back(std::string("/sourceDependencies"))), std::monostate{});
        (static_cast<void>(pchArguments->push_back(pchDependencyPath)), std::monostate{});
        (static_cast<void>(pchArguments->push_back(std::string("/c"))), std::monostate{});
        (static_cast<void>(pchArguments->push_back(pchSourcePath)), std::monostate{});
        (static_cast<void>(pchArguments->push_back((std::string("/Fo") + pchObjectPath))), std::monostate{});
        (precompiledHeaderTask = std::make_shared<NativeCompileTask>((std::string("pch:") + pchPath), compiler, pchSourcePath, pchPath, pchDependencyPath, std::make_shared<std::vector<std::string>>(std::vector<std::string>{pchObjectPath}), false, doof::array_drainToReadonly(pchArguments, "", 0)));
    }
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{});
    std::shared_ptr<std::vector<std::string>> objectPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    if (pchObjectPath != std::string("")) {
        (static_cast<void>(objectPaths->push_back(pchObjectPath)), std::monostate{});
    }
    const auto& _iterable_31 = modules;
    for (const auto& module : *_iterable_31) {
        const auto sourcePath = resolveBuildPath(outputDirectory, module->sourceName);
        const auto objectPath = resolveBuildPath(outputDirectory, (std::string(".doof-objects/generated/") + replaceSourceExtension(module->sourceName, std::string(".obj"))));
        const auto dependencyFile = (objectPath + std::string(".json"));
        const auto arguments = copyArguments(compileArguments);
        if (!doof::is_null(precompiledHeaderTask)) {
            (static_cast<void>(arguments->push_back((std::string("/FI") + pchHeaderName))), std::monostate{});
            (static_cast<void>(arguments->push_back((std::string("/Yu") + pchHeaderName))), std::monostate{});
            (static_cast<void>(arguments->push_back((std::string("/Fp") + pchPath))), std::monostate{});
        }
        (static_cast<void>(appendMsvcObjectArguments(arguments, sourcePath, objectPath, dependencyFile, false)), std::monostate{});
        (static_cast<void>(compileTasks->push_back(std::make_shared<NativeCompileTask>((std::string("object:") + objectPath), compiler, sourcePath, objectPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), (!doof::is_null(precompiledHeaderTask)), doof::array_drainToReadonly(arguments, "", 0)))), std::monostate{});
        (static_cast<void>(objectPaths->push_back(objectPath)), std::monostate{});
    }
    const auto& _iterable_33 = native->sourceFiles;
    for (const auto& sourceFile : *_iterable_33) {
        const auto sourcePath = resolveBuildPath(outputDirectory, sourceFile);
        const auto objectPath = resolveBuildPath(outputDirectory, ((std::string(".doof-objects/native/") + ::std_::crypto::index::sha1HexString(sourceFile)) + std::string(".obj")));
        const auto dependencyFile = (objectPath + std::string(".json"));
        const auto arguments = copyArguments(compileArguments);
        (static_cast<void>(appendMsvcObjectArguments(arguments, sourcePath, objectPath, dependencyFile, isCSource(sourcePath))), std::monostate{});
        (static_cast<void>(compileTasks->push_back(std::make_shared<NativeCompileTask>((std::string("object:") + objectPath), compiler, sourcePath, objectPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, doof::array_drainToReadonly(arguments, "", 0)))), std::monostate{});
        (static_cast<void>(objectPaths->push_back(objectPath)), std::monostate{});
    }
    std::shared_ptr<std::vector<std::string>> linkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("/nologo")});
    const auto& _iterable_35 = objectPaths;
    for (const auto& objectPath : *_iterable_35) {
        (static_cast<void>(linkArguments->push_back(objectPath)), std::monostate{});
    }
    const auto& _iterable_37 = native->libraryPaths;
    for (const auto& libraryPath : *_iterable_37) {
        (static_cast<void>(linkArguments->push_back((std::string("/LIBPATH:") + resolveBuildPath(outputDirectory, libraryPath)))), std::monostate{});
    }
    const auto& _iterable_39 = native->linkLibraries;
    for (const auto& library : *_iterable_39) {
        (static_cast<void>(linkArguments->push_back((doof::string_endsWith(doof::string_toLowerCase(library), std::string(".lib")) ? library : (library + std::string(".lib"))))), std::monostate{});
    }
    if (release || profile) {
        (static_cast<void>(linkArguments->push_back(std::string("/LTCG"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("/OPT:REF"))), std::monostate{});
        (static_cast<void>(linkArguments->push_back(std::string("/OPT:ICF"))), std::monostate{});
    }
    if (profile) {
        (static_cast<void>(linkArguments->push_back(std::string("/DEBUG"))), std::monostate{});
    }
    const auto& _iterable_41 = native->linkerFlags;
    for (const auto& flag : *_iterable_41) {
        (static_cast<void>(linkArguments->push_back(flag)), std::monostate{});
    }
    (static_cast<void>(linkArguments->push_back((std::string("/OUT:") + outputPath))), std::monostate{});
    return std::make_shared<NativeCompilePlan>(compiler, std::string("link.exe"), supportFiles, precompiledHeaderTask, compileTasks, linkArguments, outputPath);
}
std::string msvcPchHeaderSource() {
    return std::string("#pragma once\n#include \"doof_runtime.hpp\"\n#if defined(_WIN32)\n#ifndef WIN32_LEAN_AND_MEAN\n#define WIN32_LEAN_AND_MEAN\n#endif\n#ifndef NOMINMAX\n#define NOMINMAX\n#endif\n#include <windows.h>\n#ifdef small\n#undef small\n#endif\n#endif\n");
}
void appendMsvcObjectArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& sourcePath, const std::string& outputPath, const std::string& dependencyFilePath, bool cSource) {
    (static_cast<void>(arguments->push_back((cSource ? std::string("/TC") : std::string("/TP")))), std::monostate{});
    (static_cast<void>(arguments->push_back(std::string("/sourceDependencies"))), std::monostate{});
    (static_cast<void>(arguments->push_back(dependencyFilePath)), std::monostate{});
    (static_cast<void>(arguments->push_back(std::string("/c"))), std::monostate{});
    (static_cast<void>(arguments->push_back(sourcePath)), std::monostate{});
    (static_cast<void>(arguments->push_back((std::string("/Fo") + outputPath))), std::monostate{});
}
void appendOptimizedLinkerArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& platform, bool swiftLink, bool stripSymbols) {
    if ((platform == std::string("macos")) || doof::string_startsWith(platform, std::string("ios-"))) {
        (static_cast<void>(appendLinkerOption(arguments, std::string("-dead_strip"), swiftLink)), std::monostate{});
        if (stripSymbols) {
            (static_cast<void>(appendLinkerOption(arguments, std::string("-S"), swiftLink)), std::monostate{});
            (static_cast<void>(appendLinkerOption(arguments, std::string("-x"), swiftLink)), std::monostate{});
        }
        return;
    }
    (static_cast<void>(appendLinkerOption(arguments, std::string("--gc-sections"), swiftLink)), std::monostate{});
    if (stripSymbols) {
        (static_cast<void>(appendLinkerOption(arguments, std::string("--strip-all"), swiftLink)), std::monostate{});
    }
}
void appendLinkerOption(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& option, bool swiftLink) {
    if (swiftLink) {
        (static_cast<void>(arguments->push_back(std::string("-Xlinker"))), std::monostate{});
        (static_cast<void>(arguments->push_back(option)), std::monostate{});
    } else {
        (static_cast<void>(arguments->push_back((std::string("-Wl,") + option))), std::monostate{});
    }
}
std::string replaceSourceExtension(const std::string& path, const std::string& extension) {
    if (doof::string_endsWith(path, std::string(".cpp"))) {
        return (doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 4)) + extension);
    }
    return (path + extension);
}
std::shared_ptr<std::vector<std::string>> copyArguments(const std::shared_ptr<std::vector<std::string>>& source) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_43 = source;
    for (const auto& argument : *_iterable_43) {
        (static_cast<void>(result->push_back(argument)), std::monostate{});
    }
    return result;
}
std::shared_ptr<std::vector<std::string>> copyNativeCompileArguments(const std::shared_ptr<std::vector<std::string>>& source, bool cSource) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_45 = source;
    for (const auto& argument : *_iterable_45) {
        if (!cSource || (argument != std::string("-std=c++17"))) {
            (static_cast<void>(result->push_back(argument)), std::monostate{});
        }
    }
    return result;
}
bool isCSource(const std::string& path) {
    return doof::string_endsWith(doof::string_toLowerCase(path), std::string(".c"));
}
bool isSwiftSource(const std::string& path) {
    return doof::string_endsWith(doof::string_toLowerCase(path), std::string(".swift"));
}
bool hasSwiftSource(const std::shared_ptr<std::vector<std::string>>& paths) {
    const auto& _iterable_47 = paths;
    for (const auto& path : *_iterable_47) {
        if (isSwiftSource(path)) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<std::vector<std::string>> swiftObjectArguments(const std::string& sourcePath, const std::string& objectPath, NativeBuildMode mode) {
    auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-parse-as-library"), std::string("-emit-object")});
    if ((mode == NativeBuildMode::Release) || (mode == NativeBuildMode::Profile)) {
        (static_cast<void>(arguments->push_back(std::string("-O"))), std::monostate{});
    }
    if (mode == NativeBuildMode::Profile) {
        (static_cast<void>(arguments->push_back(std::string("-g"))), std::monostate{});
    }
    (static_cast<void>(arguments->push_back(sourcePath)), std::monostate{});
    (static_cast<void>(arguments->push_back(std::string("-o"))), std::monostate{});
    (static_cast<void>(arguments->push_back(objectPath)), std::monostate{});
    return arguments;
}
std::string deriveCCompiler(const std::string& compiler) {
    if ((compiler == std::string("em++")) || doof::string_endsWith(compiler, std::string("/em++"))) {
        return (doof::string_substring(compiler, 0, (static_cast<int32_t>(compiler.size()) - 4)) + std::string("emcc"));
    }
    if ((compiler == std::string("g++")) || doof::string_endsWith(compiler, std::string("/g++"))) {
        return (doof::string_substring(compiler, 0, (static_cast<int32_t>(compiler.size()) - 3)) + std::string("gcc"));
    }
    if ((compiler == std::string("c++")) || doof::string_endsWith(compiler, std::string("/c++"))) {
        return (doof::string_substring(compiler, 0, (static_cast<int32_t>(compiler.size()) - 3)) + std::string("cc"));
    }
    if (doof::string_endsWith(compiler, std::string("++"))) {
        return doof::string_substring(compiler, 0, (static_cast<int32_t>(compiler.size()) - 2));
    }
    return compiler;
}
std::string wasmExportList(const std::shared_ptr<std::vector<std::string>>& names) {
    auto result = std::string("[\"_malloc\",\"_free\",\"_doof_free\"");
    const auto& _iterable_49 = names;
    for (const auto& name : *_iterable_49) {
        (result = (((result + std::string(",\"_")) + name) + std::string("\"")));
    }
    return (result + std::string("]"));
}
void appendObjectArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& sourcePath, const std::string& outputPath) {
    (static_cast<void>(arguments->push_back(std::string("-c"))), std::monostate{});
    (static_cast<void>(arguments->push_back(sourcePath)), std::monostate{});
    (static_cast<void>(arguments->push_back(std::string("-o"))), std::monostate{});
    (static_cast<void>(arguments->push_back(outputPath)), std::monostate{});
}
bool usesClangPrecompiledHeader(const std::string& compiler, const std::string& platform) {
    const auto name = doof::string_toLowerCase(compiler);
    if (doof::string_contains(name, std::string("clang"))) {
        return true;
    }
    if (doof::string_contains(name, std::string("g++")) || doof::string_contains(name, std::string("gcc"))) {
        return false;
    }
    return (platform == std::string("macos"));
}
std::string resolveBuildPath(const std::string& outputDirectory, const std::string& path) {
    if (doof::string_startsWith(path, std::string("/"))) {
        return path;
    }
    if (doof::string_endsWith(outputDirectory, std::string("/"))) {
        return (outputDirectory + path);
    }
    return ((outputDirectory + std::string("/")) + path);
}
}
