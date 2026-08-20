#include "src_macos_app_driver.hpp"

namespace app_src_macos_app_driver_ {
using namespace ::app_src_macos_app_;
using namespace ::std_::blob::index;
using namespace ::std_::fs::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
int64_t MAX_MACOS_COMMAND_OUTPUT_BYTES = 262144LL;

doof::JsonObject MacOSCommandResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["exitCode"] = doof::json_value(this->exitCode);
    (*_json)["output"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->output->size()); for (const auto& _element : *this->output) { _array->push_back(doof::json_value(static_cast<int32_t>(_element))); } return doof::json_value(_array); }();
    (*_json)["error"] = doof::json_value(this->error);
    return _json;
}
doof::Result<std::shared_ptr<MacOSCommandResult>, std::string> MacOSCommandResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_exitCode = _object->find("exitCode");
    if (_iterator_exitCode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"exitCode\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_exitCode->second) : doof::json_is_number(_iterator_exitCode->second)))) { return doof::Failure<std::string>{"Field \"exitCode\" expected number but got " + std::string(doof::json_type_name(_iterator_exitCode->second))}; }
    auto _field_exitCode = (_lenient ? doof::json_as_int_lenient(_iterator_exitCode->second) : doof::json_as_int(_iterator_exitCode->second));
    std::optional<std::shared_ptr<std::vector<uint8_t>>> _field_output;
    if (auto _iterator_output = _object->find("output"); _iterator_output != _object->end()) {
            if (!(doof::json_is_array(_iterator_output->second))) { return doof::Failure<std::string>{"Field \"output\" expected array but got " + std::string(doof::json_type_name(_iterator_output->second))}; }
        _field_output = [&]() { const auto* _array = doof::json_as_array(_iterator_output->second); auto _values = std::make_shared<std::vector<uint8_t>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(static_cast<uint8_t>(_lenient ? doof::json_as_int_lenient(_element) : doof::json_as_int(_element))); } return _values; }();
    } else {
        _field_output = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    }
    std::optional<std::string> _field_error;
    if (auto _iterator_error = _object->find("error"); _iterator_error != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_error->second) : doof::json_is_string(_iterator_error->second)))) { return doof::Failure<std::string>{"Field \"error\" expected string but got " + std::string(doof::json_type_name(_iterator_error->second))}; }
        _field_error = (_lenient ? doof::json_as_string_lenient(_iterator_error->second) : doof::json_as_string(_iterator_error->second));
    } else {
        _field_error = std::string("");
    }
        return doof::Success<std::shared_ptr<MacOSCommandResult>>{std::make_shared<MacOSCommandResult>(_field_exitCode, _field_output.value(), _field_error.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
std::string hostPlatform() {
    const auto value = ::std_::os::index::platform();
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}
std::string outputPath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
std::string parentPath(const std::string& path) {
    return ::std_::path::index::dirname(path);
}
std::string fileName(const std::string& path) {
    return ::std_::path::index::basename(path);
}
std::shared_ptr<MacOSCommandResult> runMacOSCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments) {
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_MACOS_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return std::make_shared<MacOSCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error);
    }
    const auto executed = doof::success_value(_binding_value_1);
    return std::make_shared<MacOSCommandResult>(executed->exitCode, executed->stdout_, std::string(""));
}
void ensureDirectory(const std::string& path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return;
    }
    const auto parent = parentPath(path);
    if (parent != path) {
        ensureDirectory(parent);
    }
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 45, std::string("try! failed"));  }();
}
void copyPath(const std::string& sourcePath, const std::string& destinationPath) {
    if (::doof_fs::isDirectory(sourcePath)) {
        ensureDirectory(destinationPath);
        const auto& _iterable_3 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 51, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_3) {
            copyPath(outputPath(sourcePath, entry->name), outputPath(destinationPath, entry->name));
        }
        return;
    }
    ensureDirectory(parentPath(destinationPath));
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(destinationPath, [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 57, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }()); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 57, std::string("try! failed"));  }();
}
void removeTree(const std::string& path) {
    if (!::doof_fs::exists(path)) {
        return;
    }
    if (::doof_fs::isDirectory(path)) {
        const auto& _iterable_5 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 63, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_5) {
            removeTree(outputPath(path, entry->name));
        }
    }
    [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 65, std::string("try! failed"));  }();
}
std::string globBaseDirectory(const std::string& pattern) {
    auto wildcard = static_cast<int32_t>(pattern.size());
    for (int32_t index = 0; index < static_cast<int32_t>(pattern.size()); ++index) {
        if (doof::string_substring(pattern, index, (index + 1)) == std::string("*")) {
            (wildcard = index);
            break;
        }
    }
    if (wildcard == static_cast<int32_t>(pattern.size())) {
        return parentPath(pattern);
    }
    auto slash = wildcard;
    while ((slash > 0) && (doof::string_substring(pattern, (slash - 1), slash) != std::string("/"))) {
        (slash = (slash - 1));
    }
    return ((slash <= 1) ? std::string("/") : doof::string_substring(pattern, 0, (slash - 1)));
}
bool globMatches(const std::string& pattern, const std::string& value, int32_t patternIndex, int32_t valueIndex) {
    if (patternIndex == static_cast<int32_t>(pattern.size())) {
        return (valueIndex == static_cast<int32_t>(value.size()));
    }
    const auto current = doof::string_substring(pattern, patternIndex, (patternIndex + 1));
    if (current != std::string("*")) {
        return (((valueIndex < static_cast<int32_t>(value.size())) && (current == doof::string_substring(value, valueIndex, (valueIndex + 1)))) && globMatches(pattern, value, (patternIndex + 1), (valueIndex + 1)));
    }
    const auto doubleStar = (((patternIndex + 1) < static_cast<int32_t>(pattern.size())) && (doof::string_substring(pattern, (patternIndex + 1), (patternIndex + 2)) == std::string("*")));
    const auto nextPattern = (patternIndex + (doubleStar ? 2 : 1));
    if (globMatches(pattern, value, nextPattern, valueIndex)) {
        return true;
    }
    if (valueIndex >= static_cast<int32_t>(value.size())) {
        return false;
    }
    if (!doubleStar && (doof::string_substring(value, valueIndex, (valueIndex + 1)) == std::string("/"))) {
        return false;
    }
    return globMatches(pattern, value, patternIndex, (valueIndex + 1));
}
void collectResourceFiles(const std::string& path, const std::string& baseDirectory, const std::string& pattern, const std::shared_ptr<std::vector<std::string>>& results) {
    if (::doof_fs::isDirectory(path)) {
        const auto& _iterable_8 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 96, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_8) {
            collectResourceFiles(outputPath(path, entry->name), baseDirectory, pattern, results);
        }
        return;
    }
    const auto prefix = (doof::string_endsWith(baseDirectory, std::string("/")) ? baseDirectory : (baseDirectory + std::string("/")));
    const auto relative = (doof::string_startsWith(path, prefix) ? doof::string_substring(path, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(path.size())) : fileName(path));
    const auto relativePattern = (doof::string_startsWith(pattern, prefix) ? doof::string_substring(pattern, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(pattern.size())) : fileName(pattern));
    if (globMatches(relativePattern, relative, 0, 0)) {
        results->push_back(path);
    }
}
void materializeMacOSResources(const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::string& resourcesDirectory) {
    std::shared_ptr<std::vector<std::string>> destinations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_10 = config->resources;
    for (const auto& resource : *_iterable_10) {
        std::shared_ptr<std::vector<std::string>> files = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
        auto baseDirectory = globBaseDirectory(resource->sourcePath);
        if (doof::string_contains(resource->sourcePath, std::string("*"))) {
            if (::doof_fs::exists(baseDirectory)) {
                collectResourceFiles(baseDirectory, baseDirectory, resource->sourcePath, files);
            }
        } else if (::doof_fs::isDirectory(resource->sourcePath)) {
            collectResourceFiles(resource->sourcePath, resource->sourcePath, (resource->sourcePath + std::string("/**")), files);
            (baseDirectory = resource->sourcePath);
        } else if (::doof_fs::exists(resource->sourcePath)) {
            files->push_back(resource->sourcePath);
            (baseDirectory = parentPath(resource->sourcePath));
        }
        if (static_cast<int32_t>((files)->size()) == 0) {
            doof::panic((std::string("No files matched resource pattern: ") + resource->sourcePath));
        }
        const auto prefix = (doof::string_endsWith(baseDirectory, std::string("/")) ? baseDirectory : (baseDirectory + std::string("/")));
        const auto& _iterable_12 = files;
        for (const auto& sourcePath : *_iterable_12) {
            const auto relative = (doof::string_startsWith(sourcePath, prefix) ? doof::string_substring(sourcePath, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(sourcePath.size())) : fileName(sourcePath));
            const auto destinationRoot = ((resource->destination == std::string("")) ? resourcesDirectory : outputPath(resourcesDirectory, resource->destination));
            const auto destinationPath = outputPath(destinationRoot, relative);
            if (doof::array_contains(destinations, destinationPath, "", 0)) {
                doof::panic((std::string("Duplicate macOS app resource destination: ") + destinationPath));
            }
            destinations->push_back(destinationPath);
            copyPath(sourcePath, destinationPath);
        }
    }
}
doof::Result<void, std::string> runRequiredCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description) {
    const auto result = runMacOSCommand(command, arguments);
    if (result->exitCode != 0) {
        const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
        return doof::Failure<std::string>{ ((description + std::string(" failed: ")) + output) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> generateMacOSIcon(const std::string& iconPath, const std::string& destinationPath, const std::string& workRoot) {
    const auto iconset = outputPath(workRoot, std::string(".doof-app.iconset"));
    removeTree(iconset);
    ensureDirectory(iconset);
    const auto sizes = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{16, 32, 32, 64, 128, 256, 256, 512, 512, 1024});
    const auto names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("icon_16x16.png"), std::string("icon_16x16@2x.png"), std::string("icon_32x32.png"), std::string("icon_32x32@2x.png"), std::string("icon_128x128.png"), std::string("icon_128x128@2x.png"), std::string("icon_256x256.png"), std::string("icon_256x256@2x.png"), std::string("icon_512x512.png"), std::string("icon_512x512@2x.png")});
    for (int32_t index = 0; index < static_cast<int32_t>((sizes)->size()); ++index) {
        auto _try_value_14 = runRequiredCommand(std::string("sips"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-z"), doof::to_string(doof::array_at(sizes, index, "src/macos-app-driver", 152)), doof::to_string(doof::array_at(sizes, index, "src/macos-app-driver", 152)), iconPath, std::string("--out"), outputPath(iconset, doof::array_at(names, index, "src/macos-app-driver", 152))}), std::string("macOS icon resize"));
        if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
    }
    const auto result = runRequiredCommand(std::string("iconutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), std::string("icns"), iconset, std::string("-o"), destinationPath}), std::string("macOS icon generation"));
    removeTree(iconset);
    return result;
}

doof::JsonObject EmbeddedCode::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["sourcePath"] = doof::json_value(this->sourcePath);
    (*_json)["bundledRoot"] = doof::json_value(this->bundledRoot);
    (*_json)["bundledPath"] = doof::json_value(this->bundledPath);
    (*_json)["bundleReference"] = doof::json_value(this->bundleReference);
    (*_json)["installId"] = doof::json_value(this->installId);
    return _json;
}
doof::Result<std::shared_ptr<EmbeddedCode>, std::string> EmbeddedCode::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_sourcePath = _object->find("sourcePath");
    if (_iterator_sourcePath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourcePath\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sourcePath->second) : doof::json_is_string(_iterator_sourcePath->second)))) { return doof::Failure<std::string>{"Field \"sourcePath\" expected string but got " + std::string(doof::json_type_name(_iterator_sourcePath->second))}; }
    auto _field_sourcePath = (_lenient ? doof::json_as_string_lenient(_iterator_sourcePath->second) : doof::json_as_string(_iterator_sourcePath->second));
    auto _iterator_bundledRoot = _object->find("bundledRoot");
    if (_iterator_bundledRoot == _object->end()) { return doof::Failure<std::string>{"Missing required field \"bundledRoot\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_bundledRoot->second) : doof::json_is_string(_iterator_bundledRoot->second)))) { return doof::Failure<std::string>{"Field \"bundledRoot\" expected string but got " + std::string(doof::json_type_name(_iterator_bundledRoot->second))}; }
    auto _field_bundledRoot = (_lenient ? doof::json_as_string_lenient(_iterator_bundledRoot->second) : doof::json_as_string(_iterator_bundledRoot->second));
    auto _iterator_bundledPath = _object->find("bundledPath");
    if (_iterator_bundledPath == _object->end()) { return doof::Failure<std::string>{"Missing required field \"bundledPath\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_bundledPath->second) : doof::json_is_string(_iterator_bundledPath->second)))) { return doof::Failure<std::string>{"Field \"bundledPath\" expected string but got " + std::string(doof::json_type_name(_iterator_bundledPath->second))}; }
    auto _field_bundledPath = (_lenient ? doof::json_as_string_lenient(_iterator_bundledPath->second) : doof::json_as_string(_iterator_bundledPath->second));
    auto _iterator_bundleReference = _object->find("bundleReference");
    if (_iterator_bundleReference == _object->end()) { return doof::Failure<std::string>{"Missing required field \"bundleReference\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_bundleReference->second) : doof::json_is_string(_iterator_bundleReference->second)))) { return doof::Failure<std::string>{"Field \"bundleReference\" expected string but got " + std::string(doof::json_type_name(_iterator_bundleReference->second))}; }
    auto _field_bundleReference = (_lenient ? doof::json_as_string_lenient(_iterator_bundleReference->second) : doof::json_as_string(_iterator_bundleReference->second));
    std::optional<std::string> _field_installId;
    if (auto _iterator_installId = _object->find("installId"); _iterator_installId != _object->end()) {
            if (!((_lenient ? doof::json_is_lenient_string(_iterator_installId->second) : doof::json_is_string(_iterator_installId->second)))) { return doof::Failure<std::string>{"Field \"installId\" expected string but got " + std::string(doof::json_type_name(_iterator_installId->second))}; }
        _field_installId = (_lenient ? doof::json_as_string_lenient(_iterator_installId->second) : doof::json_as_string(_iterator_installId->second));
    } else {
        _field_installId = std::string("");
    }
        return doof::Success<std::shared_ptr<EmbeddedCode>>{std::make_shared<EmbeddedCode>(_field_sourcePath, _field_bundledRoot, _field_bundledPath, _field_bundleReference, _field_installId.value())};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}
doof::Result<std::string, std::string> commandText(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description) {
    const auto result = runMacOSCommand(command, arguments);
    if (result->exitCode != 0) {
        const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
        return doof::Failure<std::string>{ ((description + std::string(" failed: ")) + output) };
    }
    return doof::Success<std::string>{ ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))) };
}
doof::Result<std::string, std::string> resolveEmbeddedLibrary(const std::string& name, const std::shared_ptr<std::vector<std::string>>& libraryPaths, const std::string& buildDirectory) {
    const auto candidates = std::make_shared<std::vector<std::string>>(std::vector<std::string>{((std::string("lib") + name) + std::string(".dylib")), (name + std::string(".dylib")), ((std::string("lib") + name) + std::string(".so")), (name + std::string(".so")), (name + std::string(".framework"))});
    const auto& _iterable_16 = libraryPaths;
    for (const auto& libraryPath : *_iterable_16) {
        const auto resolvedRoot = (doof::string_startsWith(libraryPath, std::string("/")) ? libraryPath : outputPath(buildDirectory, libraryPath));
        const auto& _iterable_18 = candidates;
        for (const auto& candidate : *_iterable_18) {
            const auto candidatePath = outputPath(resolvedRoot, candidate);
            if (::doof_fs::exists(candidatePath)) {
                return doof::Success<std::string>{ candidatePath };
            }
        }
    }
    return doof::Failure<std::string>{ ((std::string("Could not resolve embedded linked library \"") + name) + std::string("\" in configured library paths")) };
}
std::string firstNonemptyOutputLine(const std::string& output) {
    const auto& _iterable_20 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_20) {
        auto start = 0;
        while ((start < static_cast<int32_t>(line.size())) && ((doof::string_substring(line, start, (start + 1)) == std::string(" ")) || (doof::string_substring(line, start, (start + 1)) == std::string("\t")))) {
            (start = (start + 1));
        }
        if (start < static_cast<int32_t>(line.size())) {
            return doof::string_substring(line, start, static_cast<int32_t>(line.size()));
        }
    }
    return std::string("");
}
doof::Result<std::string, std::string> readMachOInstallId(const std::string& path) {
    auto _try_value_21 = commandText(std::string("otool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-D"), path}), std::string("reading embedded library install name"));
    if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_21))};
    const auto commandOutput = doof::success_value(_try_value_21);
    auto first = true;
    const auto& _iterable_23 = doof::string_split(commandOutput, std::string("\n"));
    for (const auto& line : *_iterable_23) {
        if (first) {
            (first = false);
            continue;
        }
        const auto trimmed = firstNonemptyOutputLine(line);
        if (trimmed != std::string("")) {
            return doof::Success<std::string>{ trimmed };
        }
    }
    return doof::Success<std::string>{ std::string("") };
}
doof::Result<std::string, std::string> frameworkBinary(const std::string& frameworkPath) {
    const auto nameWithExtension = fileName(frameworkPath);
    const auto name = doof::string_substring(nameWithExtension, 0, (static_cast<int32_t>(nameWithExtension.size()) - static_cast<int32_t>(std::string(".framework").size())));
    const auto direct = outputPath(frameworkPath, name);
    if (::doof_fs::exists(direct)) {
        return doof::Success<std::string>{ direct };
    }
    const auto versioned = outputPath(frameworkPath, (std::string("Versions/Current/") + name));
    if (::doof_fs::exists(versioned)) {
        return doof::Success<std::string>{ versioned };
    }
    return doof::Failure<std::string>{ (std::string("Could not find executable in embedded framework: ") + frameworkPath) };
}
std::string frameworkReference(const std::string& frameworkName, const std::string& installId, const std::string& bundledBinary, const std::string& bundledRoot) {
    const auto marker = (frameworkName + std::string("/"));
    for (int32_t index = 0; index < ((static_cast<int32_t>(installId.size()) - static_cast<int32_t>(marker.size())) + 1); ++index) {
        if (doof::string_substring(installId, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
            return (((std::string("@rpath/") + frameworkName) + std::string("/")) + doof::string_substring(installId, (index + static_cast<int32_t>(marker.size())), static_cast<int32_t>(installId.size())));
        }
    }
    const auto prefix = (doof::string_endsWith(bundledRoot, std::string("/")) ? bundledRoot : (bundledRoot + std::string("/")));
    const auto relative = (doof::string_startsWith(bundledBinary, prefix) ? doof::string_substring(bundledBinary, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(bundledBinary.size())) : fileName(bundledBinary));
    return (((std::string("@rpath/") + frameworkName) + std::string("/")) + relative);
}
doof::Result<std::shared_ptr<EmbeddedCode>, std::string> planEmbeddedCode(const std::string& sourcePath, const std::string& frameworksDirectory) {
    if (!::doof_fs::exists(sourcePath)) {
        return doof::Failure<std::string>{ (std::string("Embedded library not found: ") + sourcePath) };
    }
    if (doof::string_endsWith(sourcePath, std::string(".framework"))) {
        if (!::doof_fs::isDirectory(sourcePath)) {
            return doof::Failure<std::string>{ (std::string("Embedded framework must be a directory: ") + sourcePath) };
        }
        auto _try_value_25 = frameworkBinary(sourcePath);
        if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_25))};
        const auto sourceBinary = doof::success_value(_try_value_25);
        auto _try_value_26 = readMachOInstallId(sourceBinary);
        if (doof::is_failure(_try_value_26)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_26))};
        const auto installId = doof::success_value(_try_value_26);
        const auto frameworkName = fileName(sourcePath);
        const auto bundledRoot = outputPath(frameworksDirectory, frameworkName);
        const auto sourcePrefix = (doof::string_endsWith(sourcePath, std::string("/")) ? sourcePath : (sourcePath + std::string("/")));
        const auto relativeBinary = doof::string_substring(sourceBinary, static_cast<int32_t>(sourcePrefix.size()), static_cast<int32_t>(sourceBinary.size()));
        const auto bundledPath = outputPath(bundledRoot, relativeBinary);
        return doof::Success<std::shared_ptr<EmbeddedCode>>{ std::make_shared<EmbeddedCode>(sourcePath, bundledRoot, bundledPath, frameworkReference(frameworkName, installId, bundledPath, bundledRoot), installId) };
    }
    if (!doof::string_endsWith(sourcePath, std::string(".dylib")) && !doof::string_endsWith(sourcePath, std::string(".so"))) {
        return doof::Failure<std::string>{ (std::string("Embedded library must be a .dylib, .so, or .framework: ") + sourcePath) };
    }
    auto _try_value_27 = readMachOInstallId(sourcePath);
    if (doof::is_failure(_try_value_27)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_27))};
    const auto installId = doof::success_value(_try_value_27);
    const auto destinationName = ((installId == std::string("")) ? fileName(sourcePath) : fileName(installId));
    const auto bundledPath = outputPath(frameworksDirectory, destinationName);
    return doof::Success<std::shared_ptr<EmbeddedCode>>{ std::make_shared<EmbeddedCode>(sourcePath, bundledPath, bundledPath, (std::string("@rpath/") + destinationName), installId) };
}
doof::Result<std::shared_ptr<std::vector<std::string>>, std::string> machODependencies(const std::string& path) {
    auto _try_value_28 = commandText(std::string("otool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-L"), path}), std::string("reading Mach-O dependencies"));
    if (doof::is_failure(_try_value_28)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_28))};
    const auto commandOutput = doof::success_value(_try_value_28);
    std::shared_ptr<std::vector<std::string>> dependencies = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto first = true;
    const auto& _iterable_30 = doof::string_split(commandOutput, std::string("\n"));
    for (const auto& line : *_iterable_30) {
        if (first) {
            (first = false);
            continue;
        }
        const auto trimmed = firstNonemptyOutputLine(line);
        if (trimmed == std::string("")) {
            continue;
        }
        auto end = 0;
        while (((end < static_cast<int32_t>(trimmed.size())) && (doof::string_substring(trimmed, end, (end + 1)) != std::string(" "))) && (doof::string_substring(trimmed, end, (end + 1)) != std::string("\t"))) {
            (end = (end + 1));
        }
        if (end > 0) {
            dependencies->push_back(doof::string_substring(trimmed, 0, end));
        }
    }
    return doof::Success<std::shared_ptr<std::vector<std::string>>>{ dependencies };
}
bool isSystemMachODependency(const std::string& path) {
    return (doof::string_startsWith(path, std::string("/System/Library/")) || doof::string_startsWith(path, std::string("/usr/lib/")));
}
std::shared_ptr<EmbeddedCode> embeddedDependency(const std::string& dependency, const std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>>& embedded) {
    const auto& _iterable_32 = embedded;
    for (const auto& code : *_iterable_32) {
        if ((((dependency == code->bundleReference) || (dependency == code->sourcePath)) || (dependency == code->installId)) || (fileName(dependency) == fileName(code->bundleReference))) {
            return code;
        }
    }
    return nullptr;
}
doof::Result<void, std::string> rewriteEmbeddedDependencies(const std::string& codePath, const std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>>& embedded) {
    auto _try_value_33 = machODependencies(codePath);
    if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_33))};
    const auto dependencies = doof::success_value(_try_value_33);
    const auto& _iterable_35 = dependencies;
    for (const auto& dependency : *_iterable_35) {
        if (isSystemMachODependency(dependency)) {
            continue;
        }
        const auto target = embeddedDependency(dependency, embedded);
        if (doof::is_null(target)) {
            return doof::Failure<std::string>{ ((((std::string("Mach-O file ") + codePath) + std::string(" references non-system dependency ")) + dependency) + std::string(", which is not listed in embeddedLibraries")) };
        }
        if (dependency != target->bundleReference) {
            auto _try_value_36 = runRequiredCommand(std::string("install_name_tool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-change"), dependency, target->bundleReference, codePath}), std::string("rewriting embedded library dependency"));
            if (doof::is_failure(_try_value_36)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_36))};
        }
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> ensureMachORPath(const std::string& codePath, const std::string& rpath) {
    auto _try_value_37 = commandText(std::string("otool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-l"), codePath}), std::string("reading Mach-O rpaths"));
    if (doof::is_failure(_try_value_37)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_37))};
    const auto loadCommands = doof::success_value(_try_value_37);
    if (doof::string_contains(loadCommands, ((std::string("path ") + rpath) + std::string(" ")))) {
        return doof::Success<void>{};
    }
    return runRequiredCommand(std::string("install_name_tool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-add_rpath"), rpath, codePath}), std::string("adding bundled library rpath"));
}
doof::Result<void, std::string> embedMacOSLibraries(const std::string& executablePath, const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::shared_ptr<std::vector<std::string>>& libraryPaths, const std::string& buildDirectory, const std::string& contentsDirectory) {
    if (static_cast<int32_t>((config->embeddedLibraries)->size()) == 0) {
        return doof::Success<void>{};
    }
    const auto frameworksDirectory = outputPath(contentsDirectory, std::string("Frameworks"));
    ensureDirectory(frameworksDirectory);
    std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>> embedded = std::make_shared<std::vector<std::shared_ptr<EmbeddedCode>>>(std::vector<std::shared_ptr<EmbeddedCode>>{});
    std::shared_ptr<std::vector<std::string>> destinations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_39 = config->embeddedLibraries;
    for (const auto& entry : *_iterable_39) {
        auto sourcePath = entry->path;
        if (sourcePath == std::string("")) {
            auto _try_value_40 = resolveEmbeddedLibrary(entry->library, libraryPaths, buildDirectory);
            if (doof::is_failure(_try_value_40)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_40))};
            const auto resolvedSourcePath = doof::success_value(_try_value_40);
            (sourcePath = resolvedSourcePath);
        }
        auto _try_value_41 = planEmbeddedCode(sourcePath, frameworksDirectory);
        if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_41))};
        const auto code = doof::success_value(_try_value_41);
        if (doof::array_contains(destinations, code->bundledRoot, "", 0)) {
            return doof::Failure<std::string>{ (std::string("Duplicate embedded library destination: ") + code->bundledRoot) };
        }
        destinations->push_back(code->bundledRoot);
        removeTree(code->bundledRoot);
        copyPath(code->sourcePath, code->bundledRoot);
        if (!::doof_fs::isDirectory(code->bundledRoot)) {
            auto _try_value_42 = runRequiredCommand(std::string("chmod"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("+x"), code->bundledRoot}), std::string("marking embedded library executable"));
            if (doof::is_failure(_try_value_42)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_42))};
        }
        embedded->push_back(code);
    }
    auto _try_value_43 = rewriteEmbeddedDependencies(executablePath, embedded);
    if (doof::is_failure(_try_value_43)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_43))};
    const auto& _iterable_45 = embedded;
    for (const auto& code : *_iterable_45) {
        auto _try_value_46 = rewriteEmbeddedDependencies(code->bundledPath, embedded);
        if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_46))};
        auto _try_value_47 = runRequiredCommand(std::string("install_name_tool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-id"), code->bundleReference, code->bundledPath}), std::string("setting embedded library install name"));
        if (doof::is_failure(_try_value_47)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_47))};
        auto _try_value_48 = ensureMachORPath(code->bundledPath, std::string("@loader_path"));
        if (doof::is_failure(_try_value_48)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_48))};
    }
    auto _try_value_49 = ensureMachORPath(executablePath, std::string("@executable_path/../Frameworks"));
    if (doof::is_failure(_try_value_49)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_49))};
    return doof::Success<void>{};
}
void collectNestedMacOSCode(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results) {
    if (!::doof_fs::exists(path)) {
        return;
    }
    if (::doof_fs::isDirectory(path)) {
        const auto& _iterable_51 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 349, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_51) {
            collectNestedMacOSCode(outputPath(path, entry->name), results);
        }
        if ((doof::string_endsWith(path, std::string(".framework")) || doof::string_endsWith(path, std::string(".appex"))) || doof::string_endsWith(path, std::string(".xpc"))) {
            results->push_back(path);
        }
        return;
    }
    if (doof::string_endsWith(path, std::string(".dylib")) || doof::string_endsWith(path, std::string(".so"))) {
        results->push_back(path);
    }
}
doof::Result<std::string, std::string> assembleMacOSApp(const std::string& buildDirectory, const std::string& executablePath, const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::shared_ptr<std::vector<std::string>>& libraryPaths) {
    if (hostPlatform() != std::string("macos")) {
        return doof::Failure<std::string>{ std::string("macOS app builds are only supported on macOS") };
    }
    const auto appPath = outputPath(buildDirectory, (config->executableName + std::string(".app")));
    removeTree(appPath);
    const auto contentsDirectory = outputPath(appPath, std::string("Contents"));
    const auto macosDirectory = outputPath(contentsDirectory, std::string("MacOS"));
    const auto resourcesDirectory = outputPath(contentsDirectory, std::string("Resources"));
    ensureDirectory(macosDirectory);
    ensureDirectory(resourcesDirectory);
    const auto bundleExecutable = outputPath(macosDirectory, config->executableName);
    copyPath(executablePath, bundleExecutable);
    auto _try_value_52 = runRequiredCommand(std::string("chmod"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("+x"), bundleExecutable}), std::string("marking bundled executable"));
    if (doof::is_failure(_try_value_52)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_52))};
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(contentsDirectory, std::string("Info.plist")), ::app_src_macos_app_::renderMacOSInfoPlist(config)); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 374, std::string("try! failed"));  }();
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(contentsDirectory, std::string("PkgInfo")), std::string("APPL\?\?\?\?")); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 375, std::string("try! failed"));  }();
    if (config->iconPath != std::string("")) {
        auto _try_value_53 = generateMacOSIcon(config->iconPath, outputPath(resourcesDirectory, (config->executableName + std::string(".icns"))), buildDirectory);
        if (doof::is_failure(_try_value_53)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_53))};
    }
    materializeMacOSResources(config, resourcesDirectory);
    auto _try_value_54 = embedMacOSLibraries(bundleExecutable, config, libraryPaths, buildDirectory, contentsDirectory);
    if (doof::is_failure(_try_value_54)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_54))};
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    collectNestedMacOSCode(outputPath(contentsDirectory, std::string("Frameworks")), nested);
    const auto& _iterable_56 = nested;
    for (const auto& path : *_iterable_56) {
        auto _try_value_57 = runRequiredCommand(std::string("codesign"), ::app_src_macos_app_::macOSCodesignArguments(path, std::string("-"), std::string("ad-hoc"), std::string("")), std::string("ad-hoc signing nested macOS code"));
        if (doof::is_failure(_try_value_57)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_57))};
    }
    auto _try_value_58 = runRequiredCommand(std::string("codesign"), ::app_src_macos_app_::macOSCodesignArguments(appPath, std::string("-"), std::string("ad-hoc"), std::string("")), std::string("ad-hoc signing macOS app"));
    if (doof::is_failure(_try_value_58)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_58))};
    return doof::Success<std::string>{ appPath };
}
doof::Result<std::string, std::string> developerIdIdentity(const std::string& configured) {
    if (configured != std::string("")) {
        return doof::Success<std::string>{ configured };
    }
    const auto result = runMacOSCommand(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("find-identity"), std::string("-v"), std::string("-p"), std::string("codesigning")}));
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ std::string("Could not discover Developer ID Application signing identities") };
    }
    const auto commandOutput = ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size())));
    std::shared_ptr<std::vector<std::string>> identities = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto marker = std::string("\"Developer ID Application:");
    const auto& _iterable_60 = doof::string_split(commandOutput, std::string("\n"));
    for (const auto& line : *_iterable_60) {
        auto start = -1;
        for (int32_t index = 0; index < ((static_cast<int32_t>(line.size()) - static_cast<int32_t>(marker.size())) + 1); ++index) {
            if (doof::string_substring(line, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
                (start = (index + 1));
                break;
            }
        }
        if (start < 0) {
            continue;
        }
        auto end = start;
        while ((end < static_cast<int32_t>(line.size())) && (doof::string_substring(line, end, (end + 1)) != std::string("\""))) {
            (end = (end + 1));
        }
        if (end > start) {
            identities->push_back(doof::string_substring(line, start, end));
        }
    }
    if (static_cast<int32_t>((identities)->size()) == 0) {
        return doof::Failure<std::string>{ std::string("No Developer ID Application signing identity found; pass --macos-sign-identity or use --macos-signing ad-hoc") };
    }
    if (static_cast<int32_t>((identities)->size()) > 1) {
        return doof::Failure<std::string>{ std::string("Multiple Developer ID Application identities found; pass --macos-sign-identity") };
    }
    return doof::Success<std::string>{ doof::array_at(identities, 0, "src/macos-app-driver", 409) };
}
doof::Result<std::string, std::string> effectiveEntitlements(const std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>& config, const std::string& buildDirectory) {
    if (!config->sandbox) {
        return doof::Success<std::string>{ config->entitlementsPath };
    }
    const auto destinationPath = outputPath(buildDirectory, std::string(".doof-package-entitlements.plist"));
    if (config->entitlementsPath != std::string("")) {
        copyPath(config->entitlementsPath, destinationPath);
        const auto sandboxValue = runMacOSCommand(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("com.apple.security.app-sandbox"), std::string("raw"), std::string("-o"), std::string("-"), destinationPath}));
        if (sandboxValue->exitCode == 0) {
            const auto value = doof::string_toLowerCase(::doof_blob::NativeBlobReader::constructor(sandboxValue->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((sandboxValue->output)->size()))));
            if (doof::string_contains(value, std::string("false"))) {
                return doof::Failure<std::string>{ std::string("macOS sandbox is enabled but the supplied entitlements explicitly disable it") };
            }
        }
        const auto replaced = runMacOSCommand(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-replace"), std::string("com.apple.security.app-sandbox"), std::string("-bool"), std::string("YES"), destinationPath}));
        if (replaced->exitCode != 0) {
            auto _try_value_62 = runRequiredCommand(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-insert"), std::string("com.apple.security.app-sandbox"), std::string("-bool"), std::string("YES"), destinationPath}), std::string("enabling App Sandbox"));
            if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_62))};
        }
    } else {
        [&]() -> void { auto _try_value = ::doof_fs::writeText(destinationPath, std::string("<\?xml version=\"1.0\" encoding=\"UTF-8\"\?>\n<plist version=\"1.0\"><dict><key>com.apple.security.app-sandbox</key><true/></dict></plist>\n")); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 429, std::string("try! failed"));  }();
    }
    return doof::Success<std::string>{ destinationPath };
}
doof::Result<void, std::string> signAndArchiveMacOSApp(const std::string& appPath, const std::string& archivePath, const std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>& config, const std::string& buildDirectory) {
    auto identity = std::string("-");
    if (config->signing != std::string("ad-hoc")) {
        auto _try_value_63 = developerIdIdentity(config->identity);
        if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_63))};
        const auto resolvedIdentity = doof::success_value(_try_value_63);
        (identity = resolvedIdentity);
    }
    auto _try_value_64 = effectiveEntitlements(config, buildDirectory);
    if (doof::is_failure(_try_value_64)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_64))};
    const auto entitlementsPath = doof::success_value(_try_value_64);
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    collectNestedMacOSCode(outputPath(appPath, std::string("Contents/Frameworks")), nested);
    collectNestedMacOSCode(outputPath(appPath, std::string("Contents/PlugIns")), nested);
    collectNestedMacOSCode(outputPath(appPath, std::string("Contents/XPCServices")), nested);
    const auto& _iterable_66 = nested;
    for (const auto& path : *_iterable_66) {
        auto _try_value_67 = runRequiredCommand(std::string("codesign"), ::app_src_macos_app_::macOSCodesignArguments(path, identity, config->signing, std::string("")), std::string("signing nested macOS code"));
        if (doof::is_failure(_try_value_67)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_67))};
    }
    auto _try_value_68 = runRequiredCommand(std::string("codesign"), ::app_src_macos_app_::macOSCodesignArguments(appPath, identity, config->signing, entitlementsPath), std::string("signing macOS app"));
    if (doof::is_failure(_try_value_68)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_68))};
    auto _try_value_69 = runRequiredCommand(std::string("codesign"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--verify"), std::string("--deep"), std::string("--strict"), std::string("--verbose=2"), appPath}), std::string("verifying macOS app signature"));
    if (doof::is_failure(_try_value_69)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_69))};
    ensureDirectory(parentPath(archivePath));
    if (::doof_fs::exists(archivePath)) {
        [&]() -> void { auto _try_value = ::doof_fs::remove(archivePath); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 455, std::string("try! failed"));  }();
    }
    auto _try_value_70 = runRequiredCommand(std::string("ditto"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), std::string("-k"), std::string("--sequesterRsrc"), std::string("--keepParent"), appPath, archivePath}), std::string("archiving macOS app"));
    if (doof::is_failure(_try_value_70)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_70))};
    return doof::Success<void>{};
}
}
