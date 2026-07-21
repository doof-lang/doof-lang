#include "src_native_build.hpp"
#include <cmath>
#include "src_emitter_module.hpp"
#include "src_package_manifest.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_native_build_ {
using namespace ::app_src_emitter_module_;
using namespace ::app_src_package_manifest_;

doof::JsonObject NativeCompileTask::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["compiler"] = doof::json_value(this->compiler);
    (*_json)["sourcePath"] = doof::json_value(this->sourcePath);
    (*_json)["outputPath"] = doof::json_value(this->outputPath);
    (*_json)["arguments"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->arguments->size()); for (const auto& _element : *this->arguments) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<NativeCompileTask>, std::string> NativeCompileTask::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_compiler = _object->find("compiler");
    if (_iterator_compiler == _object->end()) { return doof::Failure<std::string>{"Missing required field \"compiler\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_compiler->second) : doof::json_is_string(_iterator_compiler->second)))) { return doof::Failure<std::string>{"Field \"compiler\" expected string but got " + std::string(doof::json_type_name(_iterator_compiler->second))}; }
    auto _field_compiler = (_lenient ? doof::json_as_string_lenient(_iterator_compiler->second) : doof::json_as_string(_iterator_compiler->second));
    auto _iterator_sourcePath = _object->find("sourcePath");
    if (_iterator_sourcePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourcePath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourcePath->second) : doof::json_is_string(_iterator_sourcePath->second)))) { return doof::Failure<std::string>{"Field \"sourcePath\" expected string but got " + std::string(doof::json_type_name(_iterator_sourcePath->second))}; }
    auto _field_sourcePath = (_lenient ? doof::json_as_string_lenient(_iterator_sourcePath->second) : doof::json_as_string(_iterator_sourcePath->second));
    auto _iterator_outputPath = _object->find("outputPath");
    if (_iterator_outputPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputPath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_outputPath->second) : doof::json_is_string(_iterator_outputPath->second)))) { return doof::Failure<std::string>{"Field \"outputPath\" expected string but got " + std::string(doof::json_type_name(_iterator_outputPath->second))}; }
    auto _field_outputPath = (_lenient ? doof::json_as_string_lenient(_iterator_outputPath->second) : doof::json_as_string(_iterator_outputPath->second));
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_arguments;
    if (auto _iterator_arguments = _object->find("arguments"); _iterator_arguments != _object->end()) {
        if (!(doof::json_is_array(_iterator_arguments->second))) { return doof::Failure<std::string>{"Field \"arguments\" expected array but got " + std::string(doof::json_type_name(_iterator_arguments->second))}; }
        _field_arguments = [&]() { const auto* _array = doof::json_as_array(_iterator_arguments->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_arguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    return doof::Success<std::shared_ptr<NativeCompileTask>>{std::make_shared<NativeCompileTask>(_field_compiler, _field_sourcePath, _field_outputPath, _field_arguments.value())};
}

doof::JsonObject NativeCompilePlan::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["compiler"] = doof::json_value(this->compiler);
    (*_json)["linker"] = doof::json_value(this->linker);
    (*_json)["precompiledHeaderArguments"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->precompiledHeaderArguments->size()); for (const auto& _element : *this->precompiledHeaderArguments) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["compileTasks"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->compileTasks->size()); for (const auto& _element : *this->compileTasks) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    (*_json)["linkArguments"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->linkArguments->size()); for (const auto& _element : *this->linkArguments) { _array->push_back(doof::json_value(_element)); } return doof::json_value(_array); }();
    (*_json)["outputPath"] = doof::json_value(this->outputPath);
    return _json;
}
doof::Result<std::shared_ptr<NativeCompilePlan>, std::string> NativeCompilePlan::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_compiler = _object->find("compiler");
    if (_iterator_compiler == _object->end()) { return doof::Failure<std::string>{"Missing required field \"compiler\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_compiler->second) : doof::json_is_string(_iterator_compiler->second)))) { return doof::Failure<std::string>{"Field \"compiler\" expected string but got " + std::string(doof::json_type_name(_iterator_compiler->second))}; }
    auto _field_compiler = (_lenient ? doof::json_as_string_lenient(_iterator_compiler->second) : doof::json_as_string(_iterator_compiler->second));
    auto _iterator_linker = _object->find("linker");
    if (_iterator_linker == _object->end()) { return doof::Failure<std::string>{"Missing required field \"linker\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_linker->second) : doof::json_is_string(_iterator_linker->second)))) { return doof::Failure<std::string>{"Field \"linker\" expected string but got " + std::string(doof::json_type_name(_iterator_linker->second))}; }
    auto _field_linker = (_lenient ? doof::json_as_string_lenient(_iterator_linker->second) : doof::json_as_string(_iterator_linker->second));
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_precompiledHeaderArguments;
    if (auto _iterator_precompiledHeaderArguments = _object->find("precompiledHeaderArguments"); _iterator_precompiledHeaderArguments != _object->end()) {
        if (!(doof::json_is_array(_iterator_precompiledHeaderArguments->second))) { return doof::Failure<std::string>{"Field \"precompiledHeaderArguments\" expected array but got " + std::string(doof::json_type_name(_iterator_precompiledHeaderArguments->second))}; }
        _field_precompiledHeaderArguments = [&]() { const auto* _array = doof::json_as_array(_iterator_precompiledHeaderArguments->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_precompiledHeaderArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    std::optional<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>> _field_compileTasks;
    if (auto _iterator_compileTasks = _object->find("compileTasks"); _iterator_compileTasks != _object->end()) {
        if (!(doof::json_is_array(_iterator_compileTasks->second))) { return doof::Failure<std::string>{"Field \"compileTasks\" expected array but got " + std::string(doof::json_type_name(_iterator_compileTasks->second))}; }
        _field_compileTasks = [&]() { const auto* _array = doof::json_as_array(_iterator_compileTasks->second); auto _values = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(NativeCompileTask::fromJsonValue(_element, _lenient))); } return _values; }();
    } else {
        _field_compileTasks = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{});
    }
    std::optional<std::shared_ptr<std::vector<std::string>>> _field_linkArguments;
    if (auto _iterator_linkArguments = _object->find("linkArguments"); _iterator_linkArguments != _object->end()) {
        if (!(doof::json_is_array(_iterator_linkArguments->second))) { return doof::Failure<std::string>{"Field \"linkArguments\" expected array but got " + std::string(doof::json_type_name(_iterator_linkArguments->second))}; }
        _field_linkArguments = [&]() { const auto* _array = doof::json_as_array(_iterator_linkArguments->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back((_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element))); } return _values; }();
    } else {
        _field_linkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    auto _iterator_outputPath = _object->find("outputPath");
    if (_iterator_outputPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"outputPath\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_outputPath->second) : doof::json_is_string(_iterator_outputPath->second)))) { return doof::Failure<std::string>{"Field \"outputPath\" expected string but got " + std::string(doof::json_type_name(_iterator_outputPath->second))}; }
    auto _field_outputPath = (_lenient ? doof::json_as_string_lenient(_iterator_outputPath->second) : doof::json_as_string(_iterator_outputPath->second));
    return doof::Success<std::shared_ptr<NativeCompilePlan>>{std::make_shared<NativeCompilePlan>(_field_compiler, _field_linker, _field_precompiledHeaderArguments.value(), _field_compileTasks.value(), _field_linkArguments.value(), _field_outputPath)};
}
std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>> batchNativeCompileTasks(std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> tasks, int32_t maximumWorkers) {
    if ((static_cast<int32_t>((tasks)->size()) == 0) || (maximumWorkers <= 0)) {
        return std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>>(std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>{});
    }
    const auto workerCount = ((static_cast<int32_t>((tasks)->size()) < maximumWorkers) ? static_cast<int32_t>((tasks)->size()) : maximumWorkers);
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>> batches = std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>>(std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>{});
    while (static_cast<int32_t>((batches)->size()) < workerCount) {
        batches->push_back(std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{}));
    }
    for (int32_t index = 0; index < static_cast<int32_t>((tasks)->size()); ++index) {
        (*batches)[(index % workerCount)]->push_back((*tasks)[index]);
    }
    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>> readonlyBatches = std::make_shared<std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>>(std::vector<std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>>>{});
    const auto& _iterable_1 = batches;
    for (const auto& batch : *_iterable_1) {
        readonlyBatches->push_back(doof::array_buildReadonly(batch, "", 0));
    }
    return doof::array_buildReadonly(readonlyBatches, "", 0);
}
std::shared_ptr<NativeCompilePlan> planNativeCompile(std::string compiler, std::string outputDirectory, std::string outputPath, std::shared_ptr<std::vector<std::shared_ptr<::app_src_emitter_module_::ModuleEmission>>> modules, std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> native, bool release, std::string platform, std::shared_ptr<std::vector<std::string>> wasmExportNames, bool wasm) {
    std::shared_ptr<std::vector<std::string>> compileArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-std=c++17")});
    if (release) {
        compileArguments->push_back(std::string("-O2"));
        compileArguments->push_back(std::string("-DNDEBUG"));
    }
    if (wasm) {
        compileArguments->push_back(std::string("-Oz"));
        compileArguments->push_back(std::string("-flto"));
    }
    const auto& _iterable_2 = native->defines;
    for (const auto& define : *_iterable_2) {
        compileArguments->push_back((std::string("-D") + define));
    }
    compileArguments->push_back(std::string("-I"));
    compileArguments->push_back(outputDirectory);
    const auto& _iterable_3 = native->includePaths;
    for (const auto& includePath : *_iterable_3) {
        compileArguments->push_back(std::string("-I"));
        compileArguments->push_back(resolveBuildPath(outputDirectory, includePath));
    }
    const auto& _iterable_4 = native->compilerFlags;
    for (const auto& flag : *_iterable_4) {
        compileArguments->push_back(flag);
    }
    std::shared_ptr<std::vector<std::string>> precompiledHeaderArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto clangPchPath = std::string("");
    if ((static_cast<int32_t>((modules)->size()) > 1) && !wasm) {
        const auto runtimeHeader = resolveBuildPath(outputDirectory, std::string("doof_runtime.hpp"));
        const auto clangPch = usesClangPrecompiledHeader(compiler, platform);
        const auto pchPath = (runtimeHeader + (clangPch ? std::string(".pch") : std::string(".gch")));
        const auto& _iterable_5 = compileArguments;
        for (const auto& argument : *_iterable_5) {
            precompiledHeaderArguments->push_back(argument);
        }
        precompiledHeaderArguments->push_back(std::string("-x"));
        precompiledHeaderArguments->push_back(std::string("c++-header"));
        precompiledHeaderArguments->push_back(runtimeHeader);
        precompiledHeaderArguments->push_back(std::string("-o"));
        precompiledHeaderArguments->push_back(pchPath);
        if (clangPch) {
            (clangPchPath = pchPath);
        }
    }
    std::shared_ptr<std::vector<std::shared_ptr<NativeCompileTask>>> compileTasks = std::make_shared<std::vector<std::shared_ptr<NativeCompileTask>>>(std::vector<std::shared_ptr<NativeCompileTask>>{});
    std::shared_ptr<std::vector<std::string>> objectPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    for (int32_t index = 0; index < static_cast<int32_t>((modules)->size()); ++index) {
        const auto sourcePath = resolveBuildPath(outputDirectory, (*modules)[index]->sourceName);
        const auto objectPath = resolveBuildPath(outputDirectory, ((std::string(".doof-objects/generated-") + doof::to_string(index)) + std::string(".o")));
        const auto arguments = copyArguments(compileArguments);
        if (clangPchPath != std::string("")) {
            arguments->push_back(std::string("-include-pch"));
            arguments->push_back(clangPchPath);
        }
        appendObjectArguments(arguments, sourcePath, objectPath);
        compileTasks->push_back(std::make_shared<NativeCompileTask>(compiler, sourcePath, objectPath, doof::array_buildReadonly(arguments, "", 0)));
        objectPaths->push_back(objectPath);
    }
    for (int32_t index = 0; index < static_cast<int32_t>((native->sourceFiles)->size()); ++index) {
        const auto sourcePath = resolveBuildPath(outputDirectory, (*native->sourceFiles)[index]);
        const auto objectPath = resolveBuildPath(outputDirectory, ((std::string(".doof-objects/native-") + doof::to_string(index)) + std::string(".o")));
        const auto swiftSource = isSwiftSource(sourcePath);
        const auto cSource = isCSource(sourcePath);
        const auto arguments = (swiftSource ? swiftObjectArguments(sourcePath, objectPath) : copyNativeCompileArguments(compileArguments, cSource));
        if (!swiftSource) {
            appendObjectArguments(arguments, sourcePath, objectPath);
        }
        const auto taskCompiler = (swiftSource ? std::string("swiftc") : (cSource ? deriveCCompiler(compiler) : compiler));
        compileTasks->push_back(std::make_shared<NativeCompileTask>(taskCompiler, sourcePath, objectPath, doof::array_buildReadonly(arguments, "", 0)));
        objectPaths->push_back(objectPath);
    }
    std::shared_ptr<std::vector<std::string>> linkArguments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_6 = objectPaths;
    for (const auto& objectPath : *_iterable_6) {
        linkArguments->push_back(objectPath);
    }
    const auto& _iterable_7 = native->libraryPaths;
    for (const auto& libraryPath : *_iterable_7) {
        linkArguments->push_back((std::string("-L") + resolveBuildPath(outputDirectory, libraryPath)));
    }
    const auto& _iterable_8 = native->linkLibraries;
    for (const auto& library : *_iterable_8) {
        linkArguments->push_back((std::string("-l") + library));
    }
    const auto& _iterable_9 = native->frameworks;
    for (const auto& framework : *_iterable_9) {
        linkArguments->push_back(std::string("-framework"));
        linkArguments->push_back(framework);
    }
    const auto swiftLink = hasSwiftSource(native->sourceFiles);
    if (swiftLink && (platform == std::string("macos"))) {
        linkArguments->push_back(std::string("-Xlinker"));
        linkArguments->push_back(std::string("-lc++"));
    }
    if (!wasm) {
        const auto& _iterable_10 = native->linkerFlags;
        for (const auto& flag : *_iterable_10) {
            linkArguments->push_back(flag);
        }
    }
    if (wasm) {
        linkArguments->push_back(std::string("-Oz"));
        linkArguments->push_back(std::string("-flto"));
        linkArguments->push_back(std::string("--strip-debug"));
        linkArguments->push_back(std::string("-sASSERTIONS=0"));
        linkArguments->push_back(std::string("-sMALLOC=emmalloc"));
        linkArguments->push_back(std::string("-sSTANDALONE_WASM=1"));
        linkArguments->push_back(std::string("--no-entry"));
        linkArguments->push_back(std::string("-sFILESYSTEM=0"));
        linkArguments->push_back((std::string("-sEXPORTED_FUNCTIONS=") + wasmExportList(wasmExportNames)));
        const auto& _iterable_11 = native->linkerFlags;
        for (const auto& flag : *_iterable_11) {
            linkArguments->push_back(flag);
        }
    }
    linkArguments->push_back(std::string("-o"));
    linkArguments->push_back(outputPath);
    return std::make_shared<NativeCompilePlan>(compiler, (swiftLink ? std::string("swiftc") : compiler), precompiledHeaderArguments, compileTasks, linkArguments, outputPath);
}
std::shared_ptr<std::vector<std::string>> copyArguments(std::shared_ptr<std::vector<std::string>> source) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_12 = source;
    for (const auto& argument : *_iterable_12) {
        result->push_back(argument);
    }
    return result;
}
std::shared_ptr<std::vector<std::string>> copyNativeCompileArguments(std::shared_ptr<std::vector<std::string>> source, bool cSource) {
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_13 = source;
    for (const auto& argument : *_iterable_13) {
        if (!cSource || (argument != std::string("-std=c++17"))) {
            result->push_back(argument);
        }
    }
    return result;
}
bool isCSource(std::string path) {
    return doof::string_endsWith(doof::string_toLowerCase(path), std::string(".c"));
}
bool isSwiftSource(std::string path) {
    return doof::string_endsWith(doof::string_toLowerCase(path), std::string(".swift"));
}
bool hasSwiftSource(std::shared_ptr<std::vector<std::string>> paths) {
    const auto& _iterable_14 = paths;
    for (const auto& path : *_iterable_14) {
        if (isSwiftSource(path)) {
            return true;
        }
    }
    return false;
}
std::shared_ptr<std::vector<std::string>> swiftObjectArguments(std::string sourcePath, std::string objectPath) {
    return std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-parse-as-library"), std::string("-emit-object"), sourcePath, std::string("-o"), objectPath});
}
std::string deriveCCompiler(std::string compiler) {
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
std::string wasmExportList(std::shared_ptr<std::vector<std::string>> names) {
    auto result = std::string("[\"_malloc\",\"_free\",\"_doof_free\"");
    const auto& _iterable_15 = names;
    for (const auto& name : *_iterable_15) {
        (result = (((result + std::string(",\"_")) + name) + std::string("\"")));
    }
    return (result + std::string("]"));
}
void appendObjectArguments(std::shared_ptr<std::vector<std::string>> arguments, std::string sourcePath, std::string outputPath) {
    arguments->push_back(std::string("-c"));
    arguments->push_back(sourcePath);
    arguments->push_back(std::string("-o"));
    arguments->push_back(outputPath);
}
bool usesClangPrecompiledHeader(std::string compiler, std::string platform) {
    const auto name = doof::string_toLowerCase(compiler);
    if (doof::string_contains(name, std::string("clang"))) {
        return true;
    }
    if (doof::string_contains(name, std::string("g++")) || doof::string_contains(name, std::string("gcc"))) {
        return false;
    }
    return (platform == std::string("macos"));
}
std::string resolveBuildPath(std::string outputDirectory, std::string path) {
    if (doof::string_startsWith(path, std::string("/"))) {
        return path;
    }
    if (doof::string_endsWith(outputDirectory, std::string("/"))) {
        return (outputDirectory + path);
    }
    return ((outputDirectory + std::string("/")) + path);
}
}
