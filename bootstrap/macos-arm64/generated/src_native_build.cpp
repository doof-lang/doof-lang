#include "src_native_build.hpp"

namespace app_src_native_build_ {
using namespace ::app_src_emitter_module_;
using namespace ::app_src_package_manifest_;
using namespace ::std_::crypto::index;



#line 50 "/src/native-build.do"
bool isMsvcCompiler(const std::string& compiler) {
#line 51 "/src/native-build.do"
    const auto normalized = doof::string_toLowerCase(doof::string_replaceAll(compiler, std::string("\\"), std::string("/")));
#line 52 "/src/native-build.do"
    auto slash = -1;
#line 53 "/src/native-build.do"
    for (int32_t index = 0; index < static_cast<int32_t>(normalized.size()); ++index) {
#line 53 "/src/native-build.do"
        if (doof::string_at(normalized, index, "src/native-build", 53) == U'\u002F') {
#line 53 "/src/native-build.do"
            (slash = index);
        }
    }
#line 54 "/src/native-build.do"
    const auto name = ((slash < 0) ? normalized : doof::string_substring(normalized, (slash + 1), static_cast<int32_t>(normalized.size())));
#line 55 "/src/native-build.do"
    return ((name == std::string("cl")) || (name == std::string("cl.exe")));
}
#line 59 "/src/native-build.do"
std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>> batchNativeCompileTasks(const std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>& tasks, int32_t maximumWorkers) {
#line 63 "/src/native-build.do"
    if ((static_cast<int32_t>((tasks)->size()) == 0) || (maximumWorkers <= 0)) {
#line 63 "/src/native-build.do"
        return std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>>(std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>{});
    }
#line 64 "/src/native-build.do"
    const auto workerCount = ((static_cast<int32_t>((tasks)->size()) < maximumWorkers) ? static_cast<int32_t>((tasks)->size()) : maximumWorkers);
#line 65 "/src/native-build.do"
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>> batches = std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>>(std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>{});
#line 66 "/src/native-build.do"
    while (static_cast<int32_t>((batches)->size()) < workerCount) {
#line 66 "/src/native-build.do"
        batches->push_back(std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{}));
    }
#line 67 "/src/native-build.do"
    for (int32_t index = 0; index < static_cast<int32_t>((tasks)->size()); ++index) {
#line 67 "/src/native-build.do"
        doof::array_at(batches, (index % workerCount), "src/native-build", 67)->push_back(doof::array_at(tasks, index, "src/native-build", 67));
    }
#line 68 "/src/native-build.do"
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>> readonlyBatches = std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>>(std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>{});
#line 69 "/src/native-build.do"
    const auto& _iterable_4 = batches;
    for (const auto& batch : *_iterable_4) {
#line 69 "/src/native-build.do"
        readonlyBatches->push_back(doof::array_drainToReadonly(batch, "", 0));
    }
#line 70 "/src/native-build.do"
    return doof::array_drainToReadonly(readonlyBatches, "", 0);
}
#line 79 "/src/native-build.do"
std::shared_ptr<NativeCompilePlan> planNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, NativeBuildMode mode, const std::string& platform, const std::shared_ptr<std::vector<std::string>>& wasmExportNames, bool wasm) {
#line 90 "/src/native-build.do"
    if (isMsvcCompiler(compiler) && !wasm) {
#line 91 "/src/native-build.do"
        return planMsvcNativeCompile(compiler, outputDirectory, outputPath, modules, native, mode);
    }
#line 93 "/src/native-build.do"
    const auto release = (mode == NativeBuildMode::Release);
#line 94 "/src/native-build.do"
    const auto profile = (mode == NativeBuildMode::Profile);
#line 95 "/src/native-build.do"
    const auto swiftLink = hasSwiftSource(native->sourceFiles);
#line 96 "/src/native-build.do"
    std::shared_ptr<std::vector<std::string>> compileArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-std=c++17")});
#line 99 "/src/native-build.do"
    if (release || profile) {
#line 100 "/src/native-build.do"
        compileArguments->push_back(std::string("-O2"));
#line 101 "/src/native-build.do"
        compileArguments->push_back(std::string("-DNDEBUG"));
#line 105 "/src/native-build.do"
        compileArguments->push_back(std::string("-ffunction-sections"));
#line 106 "/src/native-build.do"
        compileArguments->push_back(std::string("-fdata-sections"));
#line 110 "/src/native-build.do"
        if ((release && !wasm) && !swiftLink) {
#line 110 "/src/native-build.do"
            compileArguments->push_back(std::string("-flto"));
        }
    }
#line 112 "/src/native-build.do"
    if (profile) {
#line 113 "/src/native-build.do"
        compileArguments->push_back(std::string("-g"));
#line 114 "/src/native-build.do"
        compileArguments->push_back(std::string("-fno-omit-frame-pointer"));
    }
#line 116 "/src/native-build.do"
    if (wasm) {
#line 117 "/src/native-build.do"
        compileArguments->push_back(std::string("-Oz"));
#line 118 "/src/native-build.do"
        compileArguments->push_back(std::string("-flto"));
    }
#line 120 "/src/native-build.do"
    const auto& _iterable_6 = native->defines;
    for (const auto& define : *_iterable_6) {
#line 120 "/src/native-build.do"
        compileArguments->push_back((std::string("-D") + define));
    }
#line 121 "/src/native-build.do"
    compileArguments->push_back(std::string("-I"));
#line 122 "/src/native-build.do"
    compileArguments->push_back(outputDirectory);
#line 123 "/src/native-build.do"
    const auto& _iterable_8 = native->includePaths;
    for (const auto& includePath : *_iterable_8) {
#line 124 "/src/native-build.do"
        compileArguments->push_back(std::string("-I"));
#line 125 "/src/native-build.do"
        compileArguments->push_back(resolveBuildPath(outputDirectory, includePath));
    }
#line 127 "/src/native-build.do"
    const auto& _iterable_10 = native->compilerFlags;
    for (const auto& flag : *_iterable_10) {
#line 127 "/src/native-build.do"
        compileArguments->push_back(flag);
    }
#line 128 "/src/native-build.do"
    std::shared_ptr<NativeCompileTask> precompiledHeaderTask = nullptr;
#line 129 "/src/native-build.do"
    auto clangPchPath = std::string("");
#line 132 "/src/native-build.do"
    if ((static_cast<int32_t>((modules)->size()) > 1) && !wasm) {
#line 133 "/src/native-build.do"
        const auto runtimeHeader = resolveBuildPath(outputDirectory, std::string("doof_runtime.hpp"));
#line 134 "/src/native-build.do"
        const auto clangPch = usesClangPrecompiledHeader(compiler, platform);
#line 135 "/src/native-build.do"
        const auto pchPath = (runtimeHeader + (clangPch ? std::string(".pch") : std::string(".gch")));
#line 136 "/src/native-build.do"
        std::shared_ptr<std::vector<std::string>> pchArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 137 "/src/native-build.do"
        const auto& _iterable_12 = compileArguments;
        for (const auto& argument : *_iterable_12) {
#line 137 "/src/native-build.do"
            pchArguments->push_back(argument);
        }
#line 138 "/src/native-build.do"
        const auto dependencyFile = (pchPath + std::string(".d"));
#line 139 "/src/native-build.do"
        pchArguments->push_back(std::string("-MMD"));
#line 140 "/src/native-build.do"
        pchArguments->push_back(std::string("-MF"));
#line 141 "/src/native-build.do"
        pchArguments->push_back(dependencyFile);
#line 142 "/src/native-build.do"
        pchArguments->push_back(std::string("-x"));
#line 143 "/src/native-build.do"
        pchArguments->push_back(std::string("c++-header"));
#line 144 "/src/native-build.do"
        pchArguments->push_back(runtimeHeader);
#line 145 "/src/native-build.do"
        pchArguments->push_back(std::string("-o"));
#line 146 "/src/native-build.do"
        pchArguments->push_back(pchPath);
#line 147 "/src/native-build.do"
        (precompiledHeaderTask = std::make_shared<NativeCompileTask>((std::string("pch:") + pchPath), compiler, runtimeHeader, pchPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, doof::array_drainToReadonly(pchArguments, "", 0)));
#line 155 "/src/native-build.do"
        if (clangPch) {
#line 155 "/src/native-build.do"
            (clangPchPath = pchPath);
        }
    }
#line 158 "/src/native-build.do"
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{});
#line 159 "/src/native-build.do"
    std::shared_ptr<std::vector<std::string>> objectPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 160 "/src/native-build.do"
    for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
#line 161 "/src/native-build.do"
        const auto sourcePath = resolveBuildPath(outputDirectory, doof::array_at(modules, index, "src/native-build", 161)->sourceName);
#line 162 "/src/native-build.do"
        const auto objectPath = resolveBuildPath(outputDirectory, (std::string(".doof-objects/generated/") + replaceSourceExtension(doof::array_at(modules, index, "src/native-build", 162)->sourceName, std::string(".o"))));
#line 163 "/src/native-build.do"
        const auto dependencyFile = (objectPath + std::string(".d"));
#line 164 "/src/native-build.do"
        const auto arguments = copyArguments(compileArguments);
#line 167 "/src/native-build.do"
        if (clangPchPath != std::string("")) {
#line 168 "/src/native-build.do"
            arguments->push_back(std::string("-include-pch"));
#line 169 "/src/native-build.do"
            arguments->push_back(clangPchPath);
        }
#line 171 "/src/native-build.do"
        arguments->push_back(std::string("-MMD"));
#line 172 "/src/native-build.do"
        arguments->push_back(std::string("-MF"));
#line 173 "/src/native-build.do"
        arguments->push_back(dependencyFile);
#line 174 "/src/native-build.do"
        appendObjectArguments(arguments, sourcePath, objectPath);
#line 175 "/src/native-build.do"
        compileTasks->push_back(std::make_shared<NativeCompileTask>((std::string("object:") + objectPath), compiler, sourcePath, objectPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), (!doof::is_null(precompiledHeaderTask)), doof::array_drainToReadonly(arguments, "", 0)));
#line 184 "/src/native-build.do"
        objectPaths->push_back(objectPath);
    }
#line 186 "/src/native-build.do"
    for (int32_t index = 0; index < static_cast<int32_t>((native->sourceFiles)->size()); ++index) {
#line 187 "/src/native-build.do"
        const auto sourcePath = resolveBuildPath(outputDirectory, doof::array_at(native->sourceFiles, index, "src/native-build", 187));
#line 188 "/src/native-build.do"
        const auto swiftSource = isSwiftSource(sourcePath);
#line 189 "/src/native-build.do"
        const auto objectPath = resolveBuildPath(outputDirectory, ((std::string(".doof-objects/native/") + ::std_::crypto::index::sha1HexString(doof::array_at(native->sourceFiles, index, "src/native-build", 189))) + std::string(".o")));
#line 190 "/src/native-build.do"
        const auto dependencyFile = (swiftSource ? std::string("") : (objectPath + std::string(".d")));
#line 191 "/src/native-build.do"
        const auto cSource = isCSource(sourcePath);
#line 192 "/src/native-build.do"
        const auto arguments = (swiftSource ? swiftObjectArguments(sourcePath, objectPath, mode) : copyNativeCompileArguments(compileArguments, cSource));
#line 193 "/src/native-build.do"
        if (!swiftSource) {
#line 194 "/src/native-build.do"
            arguments->push_back(std::string("-MMD"));
#line 195 "/src/native-build.do"
            arguments->push_back(std::string("-MF"));
#line 196 "/src/native-build.do"
            arguments->push_back(dependencyFile);
#line 197 "/src/native-build.do"
            appendObjectArguments(arguments, sourcePath, objectPath);
        }
#line 199 "/src/native-build.do"
        const auto taskCompiler = (swiftSource ? std::string("swiftc") : (cSource ? deriveCCompiler(compiler) : compiler));
#line 200 "/src/native-build.do"
        compileTasks->push_back(std::make_shared<NativeCompileTask>((std::string("object:") + objectPath), taskCompiler, sourcePath, objectPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, doof::array_drainToReadonly(arguments, "", 0)));
#line 208 "/src/native-build.do"
        objectPaths->push_back(objectPath);
    }
#line 211 "/src/native-build.do"
    std::shared_ptr<std::vector<std::string>> linkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 212 "/src/native-build.do"
    const auto& _iterable_16 = objectPaths;
    for (const auto& objectPath : *_iterable_16) {
#line 212 "/src/native-build.do"
        linkArguments->push_back(objectPath);
    }
#line 213 "/src/native-build.do"
    const auto& _iterable_18 = native->libraryPaths;
    for (const auto& libraryPath : *_iterable_18) {
#line 214 "/src/native-build.do"
        linkArguments->push_back((std::string("-L") + resolveBuildPath(outputDirectory, libraryPath)));
    }
#line 216 "/src/native-build.do"
    const auto& _iterable_20 = native->linkLibraries;
    for (const auto& library : *_iterable_20) {
#line 216 "/src/native-build.do"
        linkArguments->push_back((std::string("-l") + library));
    }
#line 217 "/src/native-build.do"
    const auto& _iterable_22 = native->frameworks;
    for (const auto& framework : *_iterable_22) {
#line 218 "/src/native-build.do"
        linkArguments->push_back(std::string("-framework"));
#line 219 "/src/native-build.do"
        linkArguments->push_back(framework);
    }
#line 221 "/src/native-build.do"
    if (swiftLink && (platform == std::string("macos"))) {
#line 222 "/src/native-build.do"
        linkArguments->push_back(std::string("-Xlinker"));
#line 223 "/src/native-build.do"
        linkArguments->push_back(std::string("-lc++"));
    }
#line 225 "/src/native-build.do"
    if ((release || profile) && !wasm) {
#line 226 "/src/native-build.do"
        if (release && !swiftLink) {
#line 226 "/src/native-build.do"
            linkArguments->push_back(std::string("-flto"));
        }
#line 227 "/src/native-build.do"
        appendOptimizedLinkerArguments(linkArguments, platform, swiftLink, release);
    }
#line 229 "/src/native-build.do"
    if (!wasm) {
#line 229 "/src/native-build.do"
        const auto& _iterable_24 = native->linkerFlags;
        for (const auto& flag : *_iterable_24) {
#line 229 "/src/native-build.do"
            linkArguments->push_back(flag);
        }
    }
#line 230 "/src/native-build.do"
    if (wasm) {
#line 231 "/src/native-build.do"
        linkArguments->push_back(std::string("-Oz"));
#line 232 "/src/native-build.do"
        linkArguments->push_back(std::string("-flto"));
#line 233 "/src/native-build.do"
        linkArguments->push_back(std::string("--strip-debug"));
#line 234 "/src/native-build.do"
        linkArguments->push_back(std::string("-sASSERTIONS=0"));
#line 235 "/src/native-build.do"
        linkArguments->push_back(std::string("-sMALLOC=emmalloc"));
#line 236 "/src/native-build.do"
        linkArguments->push_back(std::string("-sSTANDALONE_WASM=1"));
#line 237 "/src/native-build.do"
        linkArguments->push_back(std::string("--no-entry"));
#line 238 "/src/native-build.do"
        linkArguments->push_back(std::string("-sFILESYSTEM=0"));
#line 239 "/src/native-build.do"
        linkArguments->push_back((std::string("-sEXPORTED_FUNCTIONS=") + wasmExportList(wasmExportNames)));
#line 240 "/src/native-build.do"
        const auto& _iterable_26 = native->linkerFlags;
        for (const auto& flag : *_iterable_26) {
#line 240 "/src/native-build.do"
            linkArguments->push_back(flag);
        }
    }
#line 242 "/src/native-build.do"
    linkArguments->push_back(std::string("-o"));
#line 243 "/src/native-build.do"
    linkArguments->push_back(outputPath);
#line 244 "/src/native-build.do"
    return std::make_shared<NativeCompilePlan>(compiler, (swiftLink ? std::string("swiftc") : compiler), std::make_shared<std::vector<std::shared_ptr<NativeBuildSupportFile>>>(std::vector<std::shared_ptr<NativeBuildSupportFile>>{}), precompiledHeaderTask, compileTasks, linkArguments, outputPath);
}
#line 255 "/src/native-build.do"
std::shared_ptr<NativeCompilePlan> planMsvcNativeCompile(const std::string& compiler, const std::string& outputDirectory, const std::string& outputPath, const std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>>& modules, const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, NativeBuildMode mode) {
#line 263 "/src/native-build.do"
    const auto release = (mode == NativeBuildMode::Release);
#line 264 "/src/native-build.do"
    const auto profile = (mode == NativeBuildMode::Profile);
#line 265 "/src/native-build.do"
    std::shared_ptr<std::vector<std::string>> compileArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("/nologo"), std::string("/std:c++17"), std::string("/EHsc"), std::string("/utf-8"), std::string("/Zc:__cplusplus"), std::string("/permissive-")});
#line 268 "/src/native-build.do"
    if (release || profile) {
#line 269 "/src/native-build.do"
        compileArguments->push_back(std::string("/O2"));
#line 270 "/src/native-build.do"
        compileArguments->push_back(std::string("/DNDEBUG"));
#line 271 "/src/native-build.do"
        compileArguments->push_back(std::string("/Gy"));
#line 272 "/src/native-build.do"
        compileArguments->push_back(std::string("/Gw"));
#line 273 "/src/native-build.do"
        compileArguments->push_back(std::string("/GL"));
    }
#line 275 "/src/native-build.do"
    if (profile) {
#line 276 "/src/native-build.do"
        compileArguments->push_back(std::string("/Zi"));
#line 277 "/src/native-build.do"
        compileArguments->push_back(std::string("/Oy-"));
    }
#line 279 "/src/native-build.do"
    const auto& _iterable_28 = native->defines;
    for (const auto& define : *_iterable_28) {
#line 279 "/src/native-build.do"
        compileArguments->push_back((std::string("/D") + define));
    }
#line 280 "/src/native-build.do"
    compileArguments->push_back(std::string("/I"));
#line 281 "/src/native-build.do"
    compileArguments->push_back(outputDirectory);
#line 282 "/src/native-build.do"
    const auto& _iterable_30 = native->includePaths;
    for (const auto& includePath : *_iterable_30) {
#line 283 "/src/native-build.do"
        compileArguments->push_back(std::string("/I"));
#line 284 "/src/native-build.do"
        compileArguments->push_back(resolveBuildPath(outputDirectory, includePath));
    }
#line 286 "/src/native-build.do"
    const auto& _iterable_32 = native->compilerFlags;
    for (const auto& flag : *_iterable_32) {
#line 286 "/src/native-build.do"
        compileArguments->push_back(flag);
    }
#line 288 "/src/native-build.do"
    std::shared_ptr<std::vector<std::shared_ptr<NativeBuildSupportFile>>> supportFiles = std::make_shared<std::vector<std::shared_ptr<NativeBuildSupportFile>>>(std::vector<std::shared_ptr<NativeBuildSupportFile>>{});
#line 289 "/src/native-build.do"
    std::shared_ptr<NativeCompileTask> precompiledHeaderTask = nullptr;
#line 290 "/src/native-build.do"
    auto pchHeaderName = std::string("");
#line 291 "/src/native-build.do"
    auto pchPath = std::string("");
#line 292 "/src/native-build.do"
    auto pchObjectPath = std::string("");
#line 293 "/src/native-build.do"
    if (static_cast<int32_t>((modules)->size()) > 1) {
#line 294 "/src/native-build.do"
        (pchHeaderName = std::string("doof_msvc_pch.hpp"));
#line 295 "/src/native-build.do"
        const auto pchHeaderPath = resolveBuildPath(outputDirectory, pchHeaderName);
#line 296 "/src/native-build.do"
        const auto pchSourcePath = resolveBuildPath(outputDirectory, std::string("doof_msvc_pch.cpp"));
#line 297 "/src/native-build.do"
        (pchPath = resolveBuildPath(outputDirectory, std::string(".doof-objects/pch/doof_msvc.pch")));
#line 298 "/src/native-build.do"
        (pchObjectPath = resolveBuildPath(outputDirectory, std::string(".doof-objects/pch/doof_msvc_pch.obj")));
#line 299 "/src/native-build.do"
        const auto pchDependencyPath = (pchPath + std::string(".json"));
#line 300 "/src/native-build.do"
        supportFiles->push_back(std::make_shared<NativeBuildSupportFile>(pchHeaderPath, msvcPchHeaderSource()));
#line 301 "/src/native-build.do"
        supportFiles->push_back(std::make_shared<NativeBuildSupportFile>(pchSourcePath, ((std::string("#include \"") + pchHeaderName) + std::string("\"\n"))));
#line 302 "/src/native-build.do"
        const auto pchArguments = copyArguments(compileArguments);
#line 303 "/src/native-build.do"
        pchArguments->push_back(std::string("/TP"));
#line 304 "/src/native-build.do"
        pchArguments->push_back((std::string("/Yc") + pchHeaderName));
#line 305 "/src/native-build.do"
        pchArguments->push_back((std::string("/Fp") + pchPath));
#line 306 "/src/native-build.do"
        pchArguments->push_back(std::string("/sourceDependencies"));
#line 307 "/src/native-build.do"
        pchArguments->push_back(pchDependencyPath);
#line 308 "/src/native-build.do"
        pchArguments->push_back(std::string("/c"));
#line 309 "/src/native-build.do"
        pchArguments->push_back(pchSourcePath);
#line 310 "/src/native-build.do"
        pchArguments->push_back((std::string("/Fo") + pchObjectPath));
#line 311 "/src/native-build.do"
        (precompiledHeaderTask = std::make_shared<NativeCompileTask>((std::string("pch:") + pchPath), compiler, pchSourcePath, pchPath, pchDependencyPath, std::make_shared<std::vector<std::string>>(std::vector<std::string>{pchObjectPath}), false, doof::array_drainToReadonly(pchArguments, "", 0)));
    }
#line 322 "/src/native-build.do"
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{});
#line 323 "/src/native-build.do"
    std::shared_ptr<std::vector<std::string>> objectPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 324 "/src/native-build.do"
    if (pchObjectPath != std::string("")) {
#line 324 "/src/native-build.do"
        objectPaths->push_back(pchObjectPath);
    }
#line 325 "/src/native-build.do"
    const auto& _iterable_34 = modules;
    for (const auto& module : *_iterable_34) {
#line 326 "/src/native-build.do"
        const auto sourcePath = resolveBuildPath(outputDirectory, module->sourceName);
#line 327 "/src/native-build.do"
        const auto objectPath = resolveBuildPath(outputDirectory, (std::string(".doof-objects/generated/") + replaceSourceExtension(module->sourceName, std::string(".obj"))));
#line 328 "/src/native-build.do"
        const auto dependencyFile = (objectPath + std::string(".json"));
#line 329 "/src/native-build.do"
        const auto arguments = copyArguments(compileArguments);
#line 330 "/src/native-build.do"
        if (!doof::is_null(precompiledHeaderTask)) {
#line 331 "/src/native-build.do"
            arguments->push_back((std::string("/FI") + pchHeaderName));
#line 332 "/src/native-build.do"
            arguments->push_back((std::string("/Yu") + pchHeaderName));
#line 333 "/src/native-build.do"
            arguments->push_back((std::string("/Fp") + pchPath));
        }
#line 335 "/src/native-build.do"
        appendMsvcObjectArguments(arguments, sourcePath, objectPath, dependencyFile, false);
#line 336 "/src/native-build.do"
        compileTasks->push_back(std::make_shared<NativeCompileTask>((std::string("object:") + objectPath), compiler, sourcePath, objectPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), (!doof::is_null(precompiledHeaderTask)), doof::array_drainToReadonly(arguments, "", 0)));
#line 345 "/src/native-build.do"
        objectPaths->push_back(objectPath);
    }
#line 347 "/src/native-build.do"
    const auto& _iterable_36 = native->sourceFiles;
    for (const auto& sourceFile : *_iterable_36) {
#line 348 "/src/native-build.do"
        const auto sourcePath = resolveBuildPath(outputDirectory, sourceFile);
#line 349 "/src/native-build.do"
        const auto objectPath = resolveBuildPath(outputDirectory, ((std::string(".doof-objects/native/") + ::std_::crypto::index::sha1HexString(sourceFile)) + std::string(".obj")));
#line 350 "/src/native-build.do"
        const auto dependencyFile = (objectPath + std::string(".json"));
#line 351 "/src/native-build.do"
        const auto arguments = copyArguments(compileArguments);
#line 352 "/src/native-build.do"
        appendMsvcObjectArguments(arguments, sourcePath, objectPath, dependencyFile, isCSource(sourcePath));
#line 353 "/src/native-build.do"
        compileTasks->push_back(std::make_shared<NativeCompileTask>((std::string("object:") + objectPath), compiler, sourcePath, objectPath, dependencyFile, std::make_shared<std::vector<std::string>>(std::vector<std::string>{}), false, doof::array_drainToReadonly(arguments, "", 0)));
#line 361 "/src/native-build.do"
        objectPaths->push_back(objectPath);
    }
#line 364 "/src/native-build.do"
    std::shared_ptr<std::vector<std::string>> linkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("/nologo")});
#line 365 "/src/native-build.do"
    const auto& _iterable_38 = objectPaths;
    for (const auto& objectPath : *_iterable_38) {
#line 365 "/src/native-build.do"
        linkArguments->push_back(objectPath);
    }
#line 366 "/src/native-build.do"
    const auto& _iterable_40 = native->libraryPaths;
    for (const auto& libraryPath : *_iterable_40) {
#line 367 "/src/native-build.do"
        linkArguments->push_back((std::string("/LIBPATH:") + resolveBuildPath(outputDirectory, libraryPath)));
    }
#line 369 "/src/native-build.do"
    const auto& _iterable_42 = native->linkLibraries;
    for (const auto& library : *_iterable_42) {
#line 370 "/src/native-build.do"
        linkArguments->push_back((doof::string_endsWith(doof::string_toLowerCase(library), std::string(".lib")) ? library : (library + std::string(".lib"))));
    }
#line 372 "/src/native-build.do"
    if (release || profile) {
#line 373 "/src/native-build.do"
        linkArguments->push_back(std::string("/LTCG"));
#line 374 "/src/native-build.do"
        linkArguments->push_back(std::string("/OPT:REF"));
#line 375 "/src/native-build.do"
        linkArguments->push_back(std::string("/OPT:ICF"));
    }
#line 377 "/src/native-build.do"
    if (profile) {
#line 377 "/src/native-build.do"
        linkArguments->push_back(std::string("/DEBUG"));
    }
#line 378 "/src/native-build.do"
    const auto& _iterable_44 = native->linkerFlags;
    for (const auto& flag : *_iterable_44) {
#line 378 "/src/native-build.do"
        linkArguments->push_back(flag);
    }
#line 379 "/src/native-build.do"
    linkArguments->push_back((std::string("/OUT:") + outputPath));
#line 380 "/src/native-build.do"
    return std::make_shared<NativeCompilePlan>(compiler, std::string("link.exe"), supportFiles, precompiledHeaderTask, compileTasks, linkArguments, outputPath);
}
#line 392 "/src/native-build.do"
std::string msvcPchHeaderSource() {
#line 393 "/src/native-build.do"
    return std::string("#pragma once\n#include \"doof_runtime.hpp\"\n#if defined(_WIN32)\n#ifndef WIN32_LEAN_AND_MEAN\n#define WIN32_LEAN_AND_MEAN\n#endif\n#ifndef NOMINMAX\n#define NOMINMAX\n#endif\n#include <windows.h>\n#ifdef small\n#undef small\n#endif\n#endif\n");
}
#line 403 "/src/native-build.do"
void appendMsvcObjectArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& sourcePath, const std::string& outputPath, const std::string& dependencyFilePath, bool cSource) {
#line 410 "/src/native-build.do"
    arguments->push_back((cSource ? std::string("/TC") : std::string("/TP")));
#line 411 "/src/native-build.do"
    arguments->push_back(std::string("/sourceDependencies"));
#line 412 "/src/native-build.do"
    arguments->push_back(dependencyFilePath);
#line 413 "/src/native-build.do"
    arguments->push_back(std::string("/c"));
#line 414 "/src/native-build.do"
    arguments->push_back(sourcePath);
#line 415 "/src/native-build.do"
    arguments->push_back((std::string("/Fo") + outputPath));
}
#line 419 "/src/native-build.do"
void appendOptimizedLinkerArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& platform, bool swiftLink, bool stripSymbols) {
#line 420 "/src/native-build.do"
    if ((platform == std::string("macos")) || doof::string_startsWith(platform, std::string("ios-"))) {
#line 421 "/src/native-build.do"
        appendLinkerOption(arguments, std::string("-dead_strip"), swiftLink);
#line 422 "/src/native-build.do"
        if (stripSymbols) {
#line 423 "/src/native-build.do"
            appendLinkerOption(arguments, std::string("-S"), swiftLink);
#line 424 "/src/native-build.do"
            appendLinkerOption(arguments, std::string("-x"), swiftLink);
        }
#line 426 "/src/native-build.do"
        return;
    }
#line 428 "/src/native-build.do"
    appendLinkerOption(arguments, std::string("--gc-sections"), swiftLink);
#line 429 "/src/native-build.do"
    if (stripSymbols) {
#line 429 "/src/native-build.do"
        appendLinkerOption(arguments, std::string("--strip-all"), swiftLink);
    }
}
#line 432 "/src/native-build.do"
void appendLinkerOption(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& option, bool swiftLink) {
#line 433 "/src/native-build.do"
    if (swiftLink) {
#line 434 "/src/native-build.do"
        arguments->push_back(std::string("-Xlinker"));
#line 435 "/src/native-build.do"
        arguments->push_back(option);
    } else {
#line 437 "/src/native-build.do"
        arguments->push_back((std::string("-Wl,") + option));
    }
}
#line 441 "/src/native-build.do"
std::string replaceSourceExtension(const std::string& path, const std::string& extension) {
#line 442 "/src/native-build.do"
    if (doof::string_endsWith(path, std::string(".cpp"))) {
#line 442 "/src/native-build.do"
        return (doof::string_substring(path, 0, (static_cast<int32_t>(path.size()) - 4)) + extension);
    }
#line 443 "/src/native-build.do"
    return (path + extension);
}
#line 446 "/src/native-build.do"
std::shared_ptr<std::vector<std::string>> copyArguments(const std::shared_ptr<std::vector<std::string>>& source) {
#line 447 "/src/native-build.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 448 "/src/native-build.do"
    const auto& _iterable_46 = source;
    for (const auto& argument : *_iterable_46) {
#line 448 "/src/native-build.do"
        result->push_back(argument);
    }
#line 449 "/src/native-build.do"
    return result;
}
#line 452 "/src/native-build.do"
std::shared_ptr<std::vector<std::string>> copyNativeCompileArguments(const std::shared_ptr<std::vector<std::string>>& source, bool cSource) {
#line 453 "/src/native-build.do"
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 454 "/src/native-build.do"
    const auto& _iterable_48 = source;
    for (const auto& argument : *_iterable_48) {
#line 455 "/src/native-build.do"
        if (!cSource || (argument != std::string("-std=c++17"))) {
#line 455 "/src/native-build.do"
            result->push_back(argument);
        }
    }
#line 457 "/src/native-build.do"
    return result;
}
#line 460 "/src/native-build.do"
bool isCSource(const std::string& path) {
#line 461 "/src/native-build.do"
    return doof::string_endsWith(doof::string_toLowerCase(path), std::string(".c"));
}
#line 464 "/src/native-build.do"
bool isSwiftSource(const std::string& path) {
#line 465 "/src/native-build.do"
    return doof::string_endsWith(doof::string_toLowerCase(path), std::string(".swift"));
}
#line 468 "/src/native-build.do"
bool hasSwiftSource(const std::shared_ptr<std::vector<std::string>>& paths) {
#line 469 "/src/native-build.do"
    const auto& _iterable_50 = paths;
    for (const auto& path : *_iterable_50) {
#line 469 "/src/native-build.do"
        if (isSwiftSource(path)) {
#line 469 "/src/native-build.do"
            return true;
        }
    }
#line 470 "/src/native-build.do"
    return false;
}
#line 473 "/src/native-build.do"
std::shared_ptr<std::vector<std::string>> swiftObjectArguments(const std::string& sourcePath, const std::string& objectPath, NativeBuildMode mode) {
#line 474 "/src/native-build.do"
    auto arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-parse-as-library"), std::string("-emit-object")});
#line 475 "/src/native-build.do"
    if ((mode == NativeBuildMode::Release) || (mode == NativeBuildMode::Profile)) {
#line 475 "/src/native-build.do"
        arguments->push_back(std::string("-O"));
    }
#line 476 "/src/native-build.do"
    if (mode == NativeBuildMode::Profile) {
#line 476 "/src/native-build.do"
        arguments->push_back(std::string("-g"));
    }
#line 477 "/src/native-build.do"
    arguments->push_back(sourcePath);
#line 478 "/src/native-build.do"
    arguments->push_back(std::string("-o"));
#line 479 "/src/native-build.do"
    arguments->push_back(objectPath);
#line 480 "/src/native-build.do"
    return arguments;
}
#line 484 "/src/native-build.do"
std::string deriveCCompiler(const std::string& compiler) {
#line 485 "/src/native-build.do"
    if ((compiler == std::string("em++")) || doof::string_endsWith(compiler, std::string("/em++"))) {
#line 486 "/src/native-build.do"
        return (doof::string_substring(compiler, 0, (static_cast<int32_t>(compiler.size()) - 4)) + std::string("emcc"));
    }
#line 488 "/src/native-build.do"
    if ((compiler == std::string("g++")) || doof::string_endsWith(compiler, std::string("/g++"))) {
#line 489 "/src/native-build.do"
        return (doof::string_substring(compiler, 0, (static_cast<int32_t>(compiler.size()) - 3)) + std::string("gcc"));
    }
#line 491 "/src/native-build.do"
    if ((compiler == std::string("c++")) || doof::string_endsWith(compiler, std::string("/c++"))) {
#line 492 "/src/native-build.do"
        return (doof::string_substring(compiler, 0, (static_cast<int32_t>(compiler.size()) - 3)) + std::string("cc"));
    }
#line 494 "/src/native-build.do"
    if (doof::string_endsWith(compiler, std::string("++"))) {
#line 495 "/src/native-build.do"
        return doof::string_substring(compiler, 0, (static_cast<int32_t>(compiler.size()) - 2));
    }
#line 497 "/src/native-build.do"
    return compiler;
}
#line 500 "/src/native-build.do"
std::string wasmExportList(const std::shared_ptr<std::vector<std::string>>& names) {
#line 501 "/src/native-build.do"
    auto result = std::string("[\"_malloc\",\"_free\",\"_doof_free\"");
#line 502 "/src/native-build.do"
    const auto& _iterable_52 = names;
    for (const auto& name : *_iterable_52) {
#line 502 "/src/native-build.do"
        (result = (((result + std::string(",\"_")) + name) + std::string("\"")));
    }
#line 503 "/src/native-build.do"
    return (result + std::string("]"));
}
#line 506 "/src/native-build.do"
void appendObjectArguments(const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& sourcePath, const std::string& outputPath) {
#line 507 "/src/native-build.do"
    arguments->push_back(std::string("-c"));
#line 508 "/src/native-build.do"
    arguments->push_back(sourcePath);
#line 509 "/src/native-build.do"
    arguments->push_back(std::string("-o"));
#line 510 "/src/native-build.do"
    arguments->push_back(outputPath);
}
#line 513 "/src/native-build.do"
bool usesClangPrecompiledHeader(const std::string& compiler, const std::string& platform) {
#line 514 "/src/native-build.do"
    const auto name = doof::string_toLowerCase(compiler);
#line 515 "/src/native-build.do"
    if (doof::string_contains(name, std::string("clang"))) {
#line 515 "/src/native-build.do"
        return true;
    }
#line 516 "/src/native-build.do"
    if (doof::string_contains(name, std::string("g++")) || doof::string_contains(name, std::string("gcc"))) {
#line 516 "/src/native-build.do"
        return false;
    }
#line 519 "/src/native-build.do"
    return (platform == std::string("macos"));
}
#line 522 "/src/native-build.do"
std::string resolveBuildPath(const std::string& outputDirectory, const std::string& path) {
#line 523 "/src/native-build.do"
    if (doof::string_startsWith(path, std::string("/"))) {
#line 523 "/src/native-build.do"
        return path;
    }
#line 524 "/src/native-build.do"
    if (doof::string_endsWith(outputDirectory, std::string("/"))) {
#line 524 "/src/native-build.do"
        return (outputDirectory + path);
    }
#line 525 "/src/native-build.do"
    return ((outputDirectory + std::string("/")) + path);
}
#line 1 "<doof-generated>"
}
