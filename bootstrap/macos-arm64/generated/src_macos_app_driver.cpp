#include "src_macos_app_driver.hpp"

namespace app_src_macos_app_driver_ {
using namespace ::app_src_macos_app_;
using namespace ::std_::blob::index;
using namespace ::std_::fs::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
int64_t MAX_MACOS_COMMAND_OUTPUT_BYTES = 262144LL;

#line 21 "/src/macos-app-driver.do"
std::string hostPlatform() {
#line 22 "/src/macos-app-driver.do"
    const auto value = ::std_::os::index::platform();
#line 23 "/src/macos-app-driver.do"
    return ((value == std::string("darwin")) ? std::string("macos") : value);
}
#line 26 "/src/macos-app-driver.do"
std::string outputPath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
#line 27 "/src/macos-app-driver.do"
std::string parentPath(const std::string& path) {
    return ::std_::path::index::dirname(path);
}
#line 28 "/src/macos-app-driver.do"
std::string fileName(const std::string& path) {
    return ::std_::path::index::basename(path);
}
#line 30 "/src/macos-app-driver.do"
std::shared_ptr<MacOSCommandResult> runMacOSCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments) {
#line 31 "/src/macos-app-driver.do"
    auto _binding_value_1 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, MAX_MACOS_COMMAND_OUTPUT_BYTES, nullptr));
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
#line 36 "/src/macos-app-driver.do"
        return std::make_shared<MacOSCommandResult>(-1, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), error);
    }
    const auto executed = doof::success_value(_binding_value_1);
#line 38 "/src/macos-app-driver.do"
    return std::make_shared<MacOSCommandResult>(executed->exitCode, executed->stdout_, std::string(""));
}
#line 41 "/src/macos-app-driver.do"
void ensureDirectory(const std::string& path) {
#line 42 "/src/macos-app-driver.do"
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
#line 42 "/src/macos-app-driver.do"
        return;
    }
#line 43 "/src/macos-app-driver.do"
    const auto parent = parentPath(path);
#line 44 "/src/macos-app-driver.do"
    if (parent != path) {
#line 44 "/src/macos-app-driver.do"
        ensureDirectory(parent);
    }
#line 45 "/src/macos-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::mkdir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 45, std::string("try! failed"));  }();
}
#line 48 "/src/macos-app-driver.do"
void copyPath(const std::string& sourcePath, const std::string& destinationPath) {
#line 49 "/src/macos-app-driver.do"
    if (::doof_fs::isDirectory(sourcePath)) {
#line 50 "/src/macos-app-driver.do"
        ensureDirectory(destinationPath);
#line 51 "/src/macos-app-driver.do"
        const auto& _iterable_3 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 51, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_3) {
#line 52 "/src/macos-app-driver.do"
            copyPath(outputPath(sourcePath, entry->name), outputPath(destinationPath, entry->name));
        }
#line 54 "/src/macos-app-driver.do"
        return;
    }
#line 56 "/src/macos-app-driver.do"
    ensureDirectory(parentPath(destinationPath));
#line 57 "/src/macos-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeBlob(destinationPath, [&]() -> std::shared_ptr<std::vector<uint8_t>> { auto _try_value = ::doof_fs::readBlob(sourcePath); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 57, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }()); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 57, std::string("try! failed"));  }();
}
#line 60 "/src/macos-app-driver.do"
void removeTree(const std::string& path) {
#line 61 "/src/macos-app-driver.do"
    if (!::doof_fs::exists(path)) {
#line 61 "/src/macos-app-driver.do"
        return;
    }
#line 62 "/src/macos-app-driver.do"
    if (::doof_fs::isDirectory(path)) {
#line 63 "/src/macos-app-driver.do"
        const auto& _iterable_5 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 63, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_5) {
#line 63 "/src/macos-app-driver.do"
            removeTree(outputPath(path, entry->name));
        }
    }
#line 65 "/src/macos-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::remove(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 65, std::string("try! failed"));  }();
}
#line 68 "/src/macos-app-driver.do"
std::string globBaseDirectory(const std::string& pattern) {
#line 69 "/src/macos-app-driver.do"
    auto wildcard = static_cast<int32_t>(pattern.size());
#line 70 "/src/macos-app-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>(pattern.size()); ++index) {
#line 71 "/src/macos-app-driver.do"
        if (doof::string_substring(pattern, index, (index + 1)) == std::string("*")) {
#line 71 "/src/macos-app-driver.do"
            (wildcard = index);
#line 71 "/src/macos-app-driver.do"
            break;
        }
    }
#line 73 "/src/macos-app-driver.do"
    if (wildcard == static_cast<int32_t>(pattern.size())) {
#line 73 "/src/macos-app-driver.do"
        return parentPath(pattern);
    }
#line 74 "/src/macos-app-driver.do"
    auto slash = wildcard;
#line 75 "/src/macos-app-driver.do"
    while ((slash > 0) && (doof::string_substring(pattern, (slash - 1), slash) != std::string("/"))) {
#line 75 "/src/macos-app-driver.do"
        (slash = (slash - 1));
    }
#line 76 "/src/macos-app-driver.do"
    return ((slash <= 1) ? std::string("/") : doof::string_substring(pattern, 0, (slash - 1)));
}
#line 79 "/src/macos-app-driver.do"
bool globMatches(const std::string& pattern, const std::string& value, int32_t patternIndex, int32_t valueIndex) {
#line 80 "/src/macos-app-driver.do"
    if (patternIndex == static_cast<int32_t>(pattern.size())) {
#line 80 "/src/macos-app-driver.do"
        return (valueIndex == static_cast<int32_t>(value.size()));
    }
#line 81 "/src/macos-app-driver.do"
    const auto current = doof::string_substring(pattern, patternIndex, (patternIndex + 1));
#line 82 "/src/macos-app-driver.do"
    if (current != std::string("*")) {
#line 83 "/src/macos-app-driver.do"
        return (((valueIndex < static_cast<int32_t>(value.size())) && (current == doof::string_substring(value, valueIndex, (valueIndex + 1)))) && globMatches(pattern, value, (patternIndex + 1), (valueIndex + 1)));
    }
#line 86 "/src/macos-app-driver.do"
    const auto doubleStar = (((patternIndex + 1) < static_cast<int32_t>(pattern.size())) && (doof::string_substring(pattern, (patternIndex + 1), (patternIndex + 2)) == std::string("*")));
#line 87 "/src/macos-app-driver.do"
    const auto nextPattern = (patternIndex + (doubleStar ? 2 : 1));
#line 88 "/src/macos-app-driver.do"
    if (globMatches(pattern, value, nextPattern, valueIndex)) {
#line 88 "/src/macos-app-driver.do"
        return true;
    }
#line 89 "/src/macos-app-driver.do"
    if (valueIndex >= static_cast<int32_t>(value.size())) {
#line 89 "/src/macos-app-driver.do"
        return false;
    }
#line 90 "/src/macos-app-driver.do"
    if (!doubleStar && (doof::string_substring(value, valueIndex, (valueIndex + 1)) == std::string("/"))) {
#line 90 "/src/macos-app-driver.do"
        return false;
    }
#line 91 "/src/macos-app-driver.do"
    return globMatches(pattern, value, patternIndex, (valueIndex + 1));
}
#line 94 "/src/macos-app-driver.do"
void collectResourceFiles(const std::string& path, const std::string& baseDirectory, const std::string& pattern, const std::shared_ptr<std::vector<std::string>>& results) {
#line 95 "/src/macos-app-driver.do"
    if (::doof_fs::isDirectory(path)) {
#line 96 "/src/macos-app-driver.do"
        const auto& _iterable_8 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 96, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_8) {
#line 96 "/src/macos-app-driver.do"
            collectResourceFiles(outputPath(path, entry->name), baseDirectory, pattern, results);
        }
#line 97 "/src/macos-app-driver.do"
        return;
    }
#line 99 "/src/macos-app-driver.do"
    const auto prefix = (doof::string_endsWith(baseDirectory, std::string("/")) ? baseDirectory : (baseDirectory + std::string("/")));
#line 100 "/src/macos-app-driver.do"
    const auto relative = (doof::string_startsWith(path, prefix) ? doof::string_substring(path, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(path.size())) : fileName(path));
#line 101 "/src/macos-app-driver.do"
    const auto relativePattern = (doof::string_startsWith(pattern, prefix) ? doof::string_substring(pattern, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(pattern.size())) : fileName(pattern));
#line 102 "/src/macos-app-driver.do"
    if (globMatches(relativePattern, relative, 0, 0)) {
#line 102 "/src/macos-app-driver.do"
        results->push_back(path);
    }
}
#line 105 "/src/macos-app-driver.do"
void materializeMacOSResources(const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::string& resourcesDirectory) {
#line 106 "/src/macos-app-driver.do"
    std::shared_ptr<std::vector<std::string>> destinations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 107 "/src/macos-app-driver.do"
    const auto& _iterable_10 = config->resources;
    for (const auto& resource : *_iterable_10) {
#line 108 "/src/macos-app-driver.do"
        std::shared_ptr<std::vector<std::string>> files = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 109 "/src/macos-app-driver.do"
        auto baseDirectory = globBaseDirectory(resource->sourcePath);
#line 110 "/src/macos-app-driver.do"
        if (doof::string_contains(resource->sourcePath, std::string("*"))) {
#line 111 "/src/macos-app-driver.do"
            if (::doof_fs::exists(baseDirectory)) {
#line 111 "/src/macos-app-driver.do"
                collectResourceFiles(baseDirectory, baseDirectory, resource->sourcePath, files);
            }
        } else if (::doof_fs::isDirectory(resource->sourcePath)) {
#line 113 "/src/macos-app-driver.do"
            collectResourceFiles(resource->sourcePath, resource->sourcePath, (resource->sourcePath + std::string("/**")), files);
#line 114 "/src/macos-app-driver.do"
            (baseDirectory = resource->sourcePath);
        } else if (::doof_fs::exists(resource->sourcePath)) {
#line 116 "/src/macos-app-driver.do"
            files->push_back(resource->sourcePath);
#line 117 "/src/macos-app-driver.do"
            (baseDirectory = parentPath(resource->sourcePath));
        }
#line 119 "/src/macos-app-driver.do"
        if (static_cast<int32_t>((files)->size()) == 0) {
#line 119 "/src/macos-app-driver.do"
            doof::panic((std::string("No files matched resource pattern: ") + resource->sourcePath));
        }
#line 120 "/src/macos-app-driver.do"
        const auto prefix = (doof::string_endsWith(baseDirectory, std::string("/")) ? baseDirectory : (baseDirectory + std::string("/")));
#line 121 "/src/macos-app-driver.do"
        const auto& _iterable_12 = files;
        for (const auto& sourcePath : *_iterable_12) {
#line 122 "/src/macos-app-driver.do"
            const auto relative = (doof::string_startsWith(sourcePath, prefix) ? doof::string_substring(sourcePath, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(sourcePath.size())) : fileName(sourcePath));
#line 123 "/src/macos-app-driver.do"
            const auto destinationRoot = ((resource->destination == std::string("")) ? resourcesDirectory : outputPath(resourcesDirectory, resource->destination));
#line 124 "/src/macos-app-driver.do"
            const auto destinationPath = outputPath(destinationRoot, relative);
#line 125 "/src/macos-app-driver.do"
            if (doof::array_contains(destinations, destinationPath, "", 0)) {
#line 125 "/src/macos-app-driver.do"
                doof::panic((std::string("Duplicate macOS app resource destination: ") + destinationPath));
            }
#line 126 "/src/macos-app-driver.do"
            destinations->push_back(destinationPath);
#line 127 "/src/macos-app-driver.do"
            copyPath(sourcePath, destinationPath);
        }
    }
}
#line 132 "/src/macos-app-driver.do"
doof::Result<void, std::string> runRequiredCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description) {
#line 133 "/src/macos-app-driver.do"
    const auto result = runMacOSCommand(command, arguments);
#line 134 "/src/macos-app-driver.do"
    if (result->exitCode != 0) {
#line 135 "/src/macos-app-driver.do"
        const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
#line 136 "/src/macos-app-driver.do"
        return doof::Failure<std::string>{ ((description + std::string(" failed: ")) + output) };
    }
#line 138 "/src/macos-app-driver.do"
    return doof::Success<void>{};
}
#line 141 "/src/macos-app-driver.do"
doof::Result<void, std::string> generateMacOSIcon(const std::string& iconPath, const std::string& destinationPath, const std::string& workRoot) {
#line 142 "/src/macos-app-driver.do"
    const auto iconset = outputPath(workRoot, std::string(".doof-app.iconset"));
#line 143 "/src/macos-app-driver.do"
    removeTree(iconset);
#line 144 "/src/macos-app-driver.do"
    ensureDirectory(iconset);
#line 145 "/src/macos-app-driver.do"
    const auto sizes = std::make_shared<std::vector<int32_t>>(std::vector<int32_t>{16, 32, 32, 64, 128, 256, 256, 512, 512, 1024});
#line 146 "/src/macos-app-driver.do"
    const auto names = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("icon_16x16.png"), std::string("icon_16x16@2x.png"), std::string("icon_32x32.png"), std::string("icon_32x32@2x.png"), std::string("icon_128x128.png"), std::string("icon_128x128@2x.png"), std::string("icon_256x256.png"), std::string("icon_256x256@2x.png"), std::string("icon_512x512.png"), std::string("icon_512x512@2x.png")});
#line 151 "/src/macos-app-driver.do"
    for (int32_t index = 0; index < static_cast<int32_t>((sizes)->size()); ++index) {
#line 152 "/src/macos-app-driver.do"
        auto _try_value_14 = runRequiredCommand(std::string("sips"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-z"), doof::to_string(doof::array_at(sizes, index, "src/macos-app-driver", 152)), doof::to_string(doof::array_at(sizes, index, "src/macos-app-driver", 152)), iconPath, std::string("--out"), outputPath(iconset, doof::array_at(names, index, "src/macos-app-driver", 152))}), std::string("macOS icon resize"));
        if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
    }
#line 154 "/src/macos-app-driver.do"
    const auto result = runRequiredCommand(std::string("iconutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), std::string("icns"), iconset, std::string("-o"), destinationPath}), std::string("macOS icon generation"));
#line 155 "/src/macos-app-driver.do"
    removeTree(iconset);
#line 156 "/src/macos-app-driver.do"
    return result;
}

#line 167 "/src/macos-app-driver.do"
doof::Result<std::string, std::string> commandText(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments, const std::string& description) {
#line 168 "/src/macos-app-driver.do"
    const auto result = runMacOSCommand(command, arguments);
#line 169 "/src/macos-app-driver.do"
    if (result->exitCode != 0) {
#line 170 "/src/macos-app-driver.do"
        const auto output = ((result->error != std::string("")) ? result->error : ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))));
#line 171 "/src/macos-app-driver.do"
        return doof::Failure<std::string>{ ((description + std::string(" failed: ")) + output) };
    }
#line 173 "/src/macos-app-driver.do"
    return doof::Success<std::string>{ ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size()))) };
}
#line 176 "/src/macos-app-driver.do"
doof::Result<std::string, std::string> resolveEmbeddedLibrary(const std::string& name, const std::shared_ptr<std::vector<std::string>>& libraryPaths, const std::string& buildDirectory) {
#line 177 "/src/macos-app-driver.do"
    const auto candidates = std::make_shared<std::vector<std::string>>(std::vector<std::string>{((std::string("lib") + name) + std::string(".dylib")), (name + std::string(".dylib")), ((std::string("lib") + name) + std::string(".so")), (name + std::string(".so")), (name + std::string(".framework"))});
#line 178 "/src/macos-app-driver.do"
    const auto& _iterable_16 = libraryPaths;
    for (const auto& libraryPath : *_iterable_16) {
#line 179 "/src/macos-app-driver.do"
        const auto resolvedRoot = (doof::string_startsWith(libraryPath, std::string("/")) ? libraryPath : outputPath(buildDirectory, libraryPath));
#line 180 "/src/macos-app-driver.do"
        const auto& _iterable_18 = candidates;
        for (const auto& candidate : *_iterable_18) {
#line 181 "/src/macos-app-driver.do"
            const auto candidatePath = outputPath(resolvedRoot, candidate);
#line 182 "/src/macos-app-driver.do"
            if (::doof_fs::exists(candidatePath)) {
#line 182 "/src/macos-app-driver.do"
                return doof::Success<std::string>{ candidatePath };
            }
        }
    }
#line 185 "/src/macos-app-driver.do"
    return doof::Failure<std::string>{ ((std::string("Could not resolve embedded linked library \"") + name) + std::string("\" in configured library paths")) };
}
#line 188 "/src/macos-app-driver.do"
std::string firstNonemptyOutputLine(const std::string& output) {
#line 189 "/src/macos-app-driver.do"
    const auto& _iterable_20 = doof::string_split(output, std::string("\n"));
    for (const auto& line : *_iterable_20) {
#line 190 "/src/macos-app-driver.do"
        auto start = 0;
#line 191 "/src/macos-app-driver.do"
        while ((start < static_cast<int32_t>(line.size())) && ((doof::string_substring(line, start, (start + 1)) == std::string(" ")) || (doof::string_substring(line, start, (start + 1)) == std::string("\t")))) {
#line 191 "/src/macos-app-driver.do"
            (start = (start + 1));
        }
#line 192 "/src/macos-app-driver.do"
        if (start < static_cast<int32_t>(line.size())) {
#line 192 "/src/macos-app-driver.do"
            return doof::string_substring(line, start, static_cast<int32_t>(line.size()));
        }
    }
#line 194 "/src/macos-app-driver.do"
    return std::string("");
}
#line 197 "/src/macos-app-driver.do"
doof::Result<std::string, std::string> readMachOInstallId(const std::string& path) {
#line 198 "/src/macos-app-driver.do"
    auto _try_value_21 = commandText(std::string("otool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-D"), path}), std::string("reading embedded library install name"));
    if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_21))};
    const auto commandOutput = doof::success_value(_try_value_21);
#line 199 "/src/macos-app-driver.do"
    auto first = true;
#line 200 "/src/macos-app-driver.do"
    const auto& _iterable_23 = doof::string_split(commandOutput, std::string("\n"));
    for (const auto& line : *_iterable_23) {
#line 201 "/src/macos-app-driver.do"
        if (first) {
#line 201 "/src/macos-app-driver.do"
            (first = false);
#line 201 "/src/macos-app-driver.do"
            continue;
        }
#line 202 "/src/macos-app-driver.do"
        const auto trimmed = firstNonemptyOutputLine(line);
#line 203 "/src/macos-app-driver.do"
        if (trimmed != std::string("")) {
#line 203 "/src/macos-app-driver.do"
            return doof::Success<std::string>{ trimmed };
        }
    }
#line 205 "/src/macos-app-driver.do"
    return doof::Success<std::string>{ std::string("") };
}
#line 208 "/src/macos-app-driver.do"
doof::Result<std::string, std::string> frameworkBinary(const std::string& frameworkPath) {
#line 209 "/src/macos-app-driver.do"
    const auto nameWithExtension = fileName(frameworkPath);
#line 210 "/src/macos-app-driver.do"
    const auto name = doof::string_substring(nameWithExtension, 0, (static_cast<int32_t>(nameWithExtension.size()) - static_cast<int32_t>(std::string(".framework").size())));
#line 211 "/src/macos-app-driver.do"
    const auto direct = outputPath(frameworkPath, name);
#line 212 "/src/macos-app-driver.do"
    if (::doof_fs::exists(direct)) {
#line 212 "/src/macos-app-driver.do"
        return doof::Success<std::string>{ direct };
    }
#line 213 "/src/macos-app-driver.do"
    const auto versioned = outputPath(frameworkPath, (std::string("Versions/Current/") + name));
#line 214 "/src/macos-app-driver.do"
    if (::doof_fs::exists(versioned)) {
#line 214 "/src/macos-app-driver.do"
        return doof::Success<std::string>{ versioned };
    }
#line 215 "/src/macos-app-driver.do"
    return doof::Failure<std::string>{ (std::string("Could not find executable in embedded framework: ") + frameworkPath) };
}
#line 218 "/src/macos-app-driver.do"
std::string frameworkReference(const std::string& frameworkName, const std::string& installId, const std::string& bundledBinary, const std::string& bundledRoot) {
#line 219 "/src/macos-app-driver.do"
    const auto marker = (frameworkName + std::string("/"));
#line 220 "/src/macos-app-driver.do"
    for (int32_t index = 0; index < ((static_cast<int32_t>(installId.size()) - static_cast<int32_t>(marker.size())) + 1); ++index) {
#line 221 "/src/macos-app-driver.do"
        if (doof::string_substring(installId, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
#line 222 "/src/macos-app-driver.do"
            return (((std::string("@rpath/") + frameworkName) + std::string("/")) + doof::string_substring(installId, (index + static_cast<int32_t>(marker.size())), static_cast<int32_t>(installId.size())));
        }
    }
#line 225 "/src/macos-app-driver.do"
    const auto prefix = (doof::string_endsWith(bundledRoot, std::string("/")) ? bundledRoot : (bundledRoot + std::string("/")));
#line 226 "/src/macos-app-driver.do"
    const auto relative = (doof::string_startsWith(bundledBinary, prefix) ? doof::string_substring(bundledBinary, static_cast<int32_t>(prefix.size()), static_cast<int32_t>(bundledBinary.size())) : fileName(bundledBinary));
#line 227 "/src/macos-app-driver.do"
    return (((std::string("@rpath/") + frameworkName) + std::string("/")) + relative);
}
#line 230 "/src/macos-app-driver.do"
doof::Result<std::shared_ptr<EmbeddedCode>, std::string> planEmbeddedCode(const std::string& sourcePath, const std::string& frameworksDirectory) {
#line 231 "/src/macos-app-driver.do"
    if (!::doof_fs::exists(sourcePath)) {
#line 231 "/src/macos-app-driver.do"
        return doof::Failure<std::string>{ (std::string("Embedded library not found: ") + sourcePath) };
    }
#line 232 "/src/macos-app-driver.do"
    if (doof::string_endsWith(sourcePath, std::string(".framework"))) {
#line 233 "/src/macos-app-driver.do"
        if (!::doof_fs::isDirectory(sourcePath)) {
#line 233 "/src/macos-app-driver.do"
            return doof::Failure<std::string>{ (std::string("Embedded framework must be a directory: ") + sourcePath) };
        }
#line 234 "/src/macos-app-driver.do"
        auto _try_value_25 = frameworkBinary(sourcePath);
        if (doof::is_failure(_try_value_25)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_25))};
        const auto sourceBinary = doof::success_value(_try_value_25);
#line 235 "/src/macos-app-driver.do"
        auto _try_value_26 = readMachOInstallId(sourceBinary);
        if (doof::is_failure(_try_value_26)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_26))};
        const auto installId = doof::success_value(_try_value_26);
#line 236 "/src/macos-app-driver.do"
        const auto frameworkName = fileName(sourcePath);
#line 237 "/src/macos-app-driver.do"
        const auto bundledRoot = outputPath(frameworksDirectory, frameworkName);
#line 238 "/src/macos-app-driver.do"
        const auto sourcePrefix = (doof::string_endsWith(sourcePath, std::string("/")) ? sourcePath : (sourcePath + std::string("/")));
#line 239 "/src/macos-app-driver.do"
        const auto relativeBinary = doof::string_substring(sourceBinary, static_cast<int32_t>(sourcePrefix.size()), static_cast<int32_t>(sourceBinary.size()));
#line 240 "/src/macos-app-driver.do"
        const auto bundledPath = outputPath(bundledRoot, relativeBinary);
#line 241 "/src/macos-app-driver.do"
        return doof::Success<std::shared_ptr<EmbeddedCode>>{ std::make_shared<EmbeddedCode>(sourcePath, bundledRoot, bundledPath, frameworkReference(frameworkName, installId, bundledPath, bundledRoot), installId) };
    }
#line 247 "/src/macos-app-driver.do"
    if (!doof::string_endsWith(sourcePath, std::string(".dylib")) && !doof::string_endsWith(sourcePath, std::string(".so"))) {
#line 248 "/src/macos-app-driver.do"
        return doof::Failure<std::string>{ (std::string("Embedded library must be a .dylib, .so, or .framework: ") + sourcePath) };
    }
#line 250 "/src/macos-app-driver.do"
    auto _try_value_27 = readMachOInstallId(sourcePath);
    if (doof::is_failure(_try_value_27)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_27))};
    const auto installId = doof::success_value(_try_value_27);
#line 251 "/src/macos-app-driver.do"
    const auto destinationName = ((installId == std::string("")) ? fileName(sourcePath) : fileName(installId));
#line 252 "/src/macos-app-driver.do"
    const auto bundledPath = outputPath(frameworksDirectory, destinationName);
#line 253 "/src/macos-app-driver.do"
    return doof::Success<std::shared_ptr<EmbeddedCode>>{ std::make_shared<EmbeddedCode>(sourcePath, bundledPath, bundledPath, (std::string("@rpath/") + destinationName), installId) };
}
#line 262 "/src/macos-app-driver.do"
doof::Result<std::shared_ptr<std::vector<std::string>>, std::string> machODependencies(const std::string& path) {
#line 263 "/src/macos-app-driver.do"
    auto _try_value_28 = commandText(std::string("otool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-L"), path}), std::string("reading Mach-O dependencies"));
    if (doof::is_failure(_try_value_28)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_28))};
    const auto commandOutput = doof::success_value(_try_value_28);
#line 264 "/src/macos-app-driver.do"
    std::shared_ptr<std::vector<std::string>> dependencies = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 265 "/src/macos-app-driver.do"
    auto first = true;
#line 266 "/src/macos-app-driver.do"
    const auto& _iterable_30 = doof::string_split(commandOutput, std::string("\n"));
    for (const auto& line : *_iterable_30) {
#line 267 "/src/macos-app-driver.do"
        if (first) {
#line 267 "/src/macos-app-driver.do"
            (first = false);
#line 267 "/src/macos-app-driver.do"
            continue;
        }
#line 268 "/src/macos-app-driver.do"
        const auto trimmed = firstNonemptyOutputLine(line);
#line 269 "/src/macos-app-driver.do"
        if (trimmed == std::string("")) {
#line 269 "/src/macos-app-driver.do"
            continue;
        }
#line 270 "/src/macos-app-driver.do"
        auto end = 0;
#line 271 "/src/macos-app-driver.do"
        while (((end < static_cast<int32_t>(trimmed.size())) && (doof::string_substring(trimmed, end, (end + 1)) != std::string(" "))) && (doof::string_substring(trimmed, end, (end + 1)) != std::string("\t"))) {
#line 271 "/src/macos-app-driver.do"
            (end = (end + 1));
        }
#line 272 "/src/macos-app-driver.do"
        if (end > 0) {
#line 272 "/src/macos-app-driver.do"
            dependencies->push_back(doof::string_substring(trimmed, 0, end));
        }
    }
#line 274 "/src/macos-app-driver.do"
    return doof::Success<std::shared_ptr<std::vector<std::string>>>{ dependencies };
}
#line 277 "/src/macos-app-driver.do"
bool isSystemMachODependency(const std::string& path) {
#line 278 "/src/macos-app-driver.do"
    return (doof::string_startsWith(path, std::string("/System/Library/")) || doof::string_startsWith(path, std::string("/usr/lib/")));
}
#line 281 "/src/macos-app-driver.do"
std::shared_ptr<EmbeddedCode> embeddedDependency(const std::string& dependency, const std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>>& embedded) {
#line 282 "/src/macos-app-driver.do"
    const auto& _iterable_32 = embedded;
    for (const auto& code : *_iterable_32) {
#line 283 "/src/macos-app-driver.do"
        if ((((dependency == code->bundleReference) || (dependency == code->sourcePath)) || (dependency == code->installId)) || (fileName(dependency) == fileName(code->bundleReference))) {
#line 284 "/src/macos-app-driver.do"
            return code;
        }
    }
#line 286 "/src/macos-app-driver.do"
    return nullptr;
}
#line 289 "/src/macos-app-driver.do"
doof::Result<void, std::string> rewriteEmbeddedDependencies(const std::string& codePath, const std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>>& embedded) {
#line 290 "/src/macos-app-driver.do"
    auto _try_value_33 = machODependencies(codePath);
    if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_33))};
    const auto dependencies = doof::success_value(_try_value_33);
#line 291 "/src/macos-app-driver.do"
    const auto& _iterable_35 = dependencies;
    for (const auto& dependency : *_iterable_35) {
#line 292 "/src/macos-app-driver.do"
        if (isSystemMachODependency(dependency)) {
#line 292 "/src/macos-app-driver.do"
            continue;
        }
#line 293 "/src/macos-app-driver.do"
        const auto target = embeddedDependency(dependency, embedded);
#line 294 "/src/macos-app-driver.do"
        if (doof::is_null(target)) {
#line 295 "/src/macos-app-driver.do"
            return doof::Failure<std::string>{ ((((std::string("Mach-O file ") + codePath) + std::string(" references non-system dependency ")) + dependency) + std::string(", which is not listed in embeddedLibraries")) };
        }
#line 297 "/src/macos-app-driver.do"
        if (dependency != target->bundleReference) {
#line 298 "/src/macos-app-driver.do"
            auto _try_value_36 = runRequiredCommand(std::string("install_name_tool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-change"), dependency, target->bundleReference, codePath}), std::string("rewriting embedded library dependency"));
            if (doof::is_failure(_try_value_36)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_36))};
        }
    }
#line 301 "/src/macos-app-driver.do"
    return doof::Success<void>{};
}
#line 304 "/src/macos-app-driver.do"
doof::Result<void, std::string> ensureMachORPath(const std::string& codePath, const std::string& rpath) {
#line 305 "/src/macos-app-driver.do"
    auto _try_value_37 = commandText(std::string("otool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-l"), codePath}), std::string("reading Mach-O rpaths"));
    if (doof::is_failure(_try_value_37)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_37))};
    const auto loadCommands = doof::success_value(_try_value_37);
#line 306 "/src/macos-app-driver.do"
    if (doof::string_contains(loadCommands, ((std::string("path ") + rpath) + std::string(" ")))) {
#line 306 "/src/macos-app-driver.do"
        return doof::Success<void>{};
    }
#line 307 "/src/macos-app-driver.do"
    return runRequiredCommand(std::string("install_name_tool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-add_rpath"), rpath, codePath}), std::string("adding bundled library rpath"));
}
#line 310 "/src/macos-app-driver.do"
doof::Result<void, std::string> embedMacOSLibraries(const std::string& executablePath, const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::shared_ptr<std::vector<std::string>>& libraryPaths, const std::string& buildDirectory, const std::string& contentsDirectory) {
#line 317 "/src/macos-app-driver.do"
    if (static_cast<int32_t>((config->embeddedLibraries)->size()) == 0) {
#line 317 "/src/macos-app-driver.do"
        return doof::Success<void>{};
    }
#line 318 "/src/macos-app-driver.do"
    const auto frameworksDirectory = outputPath(contentsDirectory, std::string("Frameworks"));
#line 319 "/src/macos-app-driver.do"
    ensureDirectory(frameworksDirectory);
#line 320 "/src/macos-app-driver.do"
    std::shared_ptr<std::vector<std::shared_ptr<EmbeddedCode>>> embedded = std::make_shared<std::vector<std::shared_ptr<EmbeddedCode>>>(std::vector<std::shared_ptr<EmbeddedCode>>{});
#line 321 "/src/macos-app-driver.do"
    std::shared_ptr<std::vector<std::string>> destinations = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 322 "/src/macos-app-driver.do"
    const auto& _iterable_39 = config->embeddedLibraries;
    for (const auto& entry : *_iterable_39) {
#line 323 "/src/macos-app-driver.do"
        auto sourcePath = entry->path;
#line 324 "/src/macos-app-driver.do"
        if (sourcePath == std::string("")) {
#line 325 "/src/macos-app-driver.do"
            auto _try_value_40 = resolveEmbeddedLibrary(entry->library, libraryPaths, buildDirectory);
            if (doof::is_failure(_try_value_40)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_40))};
            const auto resolvedSourcePath = doof::success_value(_try_value_40);
#line 326 "/src/macos-app-driver.do"
            (sourcePath = resolvedSourcePath);
        }
#line 328 "/src/macos-app-driver.do"
        auto _try_value_41 = planEmbeddedCode(sourcePath, frameworksDirectory);
        if (doof::is_failure(_try_value_41)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_41))};
        const auto code = doof::success_value(_try_value_41);
#line 329 "/src/macos-app-driver.do"
        if (doof::array_contains(destinations, code->bundledRoot, "", 0)) {
#line 329 "/src/macos-app-driver.do"
            return doof::Failure<std::string>{ (std::string("Duplicate embedded library destination: ") + code->bundledRoot) };
        }
#line 330 "/src/macos-app-driver.do"
        destinations->push_back(code->bundledRoot);
#line 331 "/src/macos-app-driver.do"
        removeTree(code->bundledRoot);
#line 332 "/src/macos-app-driver.do"
        copyPath(code->sourcePath, code->bundledRoot);
#line 333 "/src/macos-app-driver.do"
        if (!::doof_fs::isDirectory(code->bundledRoot)) {
#line 333 "/src/macos-app-driver.do"
            auto _try_value_42 = runRequiredCommand(std::string("chmod"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("+x"), code->bundledRoot}), std::string("marking embedded library executable"));
            if (doof::is_failure(_try_value_42)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_42))};
        }
#line 334 "/src/macos-app-driver.do"
        embedded->push_back(code);
    }
#line 336 "/src/macos-app-driver.do"
    auto _try_value_43 = rewriteEmbeddedDependencies(executablePath, embedded);
    if (doof::is_failure(_try_value_43)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_43))};
#line 337 "/src/macos-app-driver.do"
    const auto& _iterable_45 = embedded;
    for (const auto& code : *_iterable_45) {
#line 338 "/src/macos-app-driver.do"
        auto _try_value_46 = rewriteEmbeddedDependencies(code->bundledPath, embedded);
        if (doof::is_failure(_try_value_46)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_46))};
#line 339 "/src/macos-app-driver.do"
        auto _try_value_47 = runRequiredCommand(std::string("install_name_tool"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-id"), code->bundleReference, code->bundledPath}), std::string("setting embedded library install name"));
        if (doof::is_failure(_try_value_47)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_47))};
#line 340 "/src/macos-app-driver.do"
        auto _try_value_48 = ensureMachORPath(code->bundledPath, std::string("@loader_path"));
        if (doof::is_failure(_try_value_48)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_48))};
    }
#line 342 "/src/macos-app-driver.do"
    auto _try_value_49 = ensureMachORPath(executablePath, std::string("@executable_path/../Frameworks"));
    if (doof::is_failure(_try_value_49)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_49))};
#line 343 "/src/macos-app-driver.do"
    return doof::Success<void>{};
}
#line 346 "/src/macos-app-driver.do"
void collectNestedMacOSCode(const std::string& path, const std::shared_ptr<std::vector<std::string>>& results) {
#line 347 "/src/macos-app-driver.do"
    if (!::doof_fs::exists(path)) {
#line 347 "/src/macos-app-driver.do"
        return;
    }
#line 348 "/src/macos-app-driver.do"
    if (::doof_fs::isDirectory(path)) {
#line 349 "/src/macos-app-driver.do"
        const auto& _iterable_51 = [&]() -> std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>> { auto _try_value = ::doof_fs::readDir(path); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 349, std::string("try! failed")); return std::move(doof::success_value(_try_value)); }();
        for (const auto& entry : *_iterable_51) {
#line 349 "/src/macos-app-driver.do"
            collectNestedMacOSCode(outputPath(path, entry->name), results);
        }
#line 350 "/src/macos-app-driver.do"
        if ((doof::string_endsWith(path, std::string(".framework")) || doof::string_endsWith(path, std::string(".appex"))) || doof::string_endsWith(path, std::string(".xpc"))) {
#line 350 "/src/macos-app-driver.do"
            results->push_back(path);
        }
#line 351 "/src/macos-app-driver.do"
        return;
    }
#line 353 "/src/macos-app-driver.do"
    if (doof::string_endsWith(path, std::string(".dylib")) || doof::string_endsWith(path, std::string(".so"))) {
#line 353 "/src/macos-app-driver.do"
        results->push_back(path);
    }
}
#line 357 "/src/macos-app-driver.do"
doof::Result<std::string, std::string> assembleMacOSApp(const std::string& buildDirectory, const std::string& executablePath, const std::shared_ptr<::app_src_macos_app_::MacOSAppConfig>& config, const std::shared_ptr<std::vector<std::string>>& libraryPaths) {
#line 363 "/src/macos-app-driver.do"
    if (hostPlatform() != std::string("macos")) {
#line 363 "/src/macos-app-driver.do"
        return doof::Failure<std::string>{ std::string("macOS app builds are only supported on macOS") };
    }
#line 364 "/src/macos-app-driver.do"
    const auto appPath = outputPath(buildDirectory, (config->executableName + std::string(".app")));
#line 365 "/src/macos-app-driver.do"
    removeTree(appPath);
#line 366 "/src/macos-app-driver.do"
    const auto contentsDirectory = outputPath(appPath, std::string("Contents"));
#line 367 "/src/macos-app-driver.do"
    const auto macosDirectory = outputPath(contentsDirectory, std::string("MacOS"));
#line 368 "/src/macos-app-driver.do"
    const auto resourcesDirectory = outputPath(contentsDirectory, std::string("Resources"));
#line 369 "/src/macos-app-driver.do"
    ensureDirectory(macosDirectory);
#line 370 "/src/macos-app-driver.do"
    ensureDirectory(resourcesDirectory);
#line 371 "/src/macos-app-driver.do"
    const auto bundleExecutable = outputPath(macosDirectory, config->executableName);
#line 372 "/src/macos-app-driver.do"
    copyPath(executablePath, bundleExecutable);
#line 373 "/src/macos-app-driver.do"
    auto _try_value_52 = runRequiredCommand(std::string("chmod"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("+x"), bundleExecutable}), std::string("marking bundled executable"));
    if (doof::is_failure(_try_value_52)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_52))};
#line 374 "/src/macos-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(contentsDirectory, std::string("Info.plist")), ::app_src_macos_app_::renderMacOSInfoPlist(config)); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 374, std::string("try! failed"));  }();
#line 375 "/src/macos-app-driver.do"
    [&]() -> void { auto _try_value = ::doof_fs::writeText(outputPath(contentsDirectory, std::string("PkgInfo")), std::string("APPL\?\?\?\?")); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 375, std::string("try! failed"));  }();
#line 376 "/src/macos-app-driver.do"
    if (config->iconPath != std::string("")) {
#line 377 "/src/macos-app-driver.do"
        auto _try_value_53 = generateMacOSIcon(config->iconPath, outputPath(resourcesDirectory, (config->executableName + std::string(".icns"))), buildDirectory);
        if (doof::is_failure(_try_value_53)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_53))};
    }
#line 379 "/src/macos-app-driver.do"
    materializeMacOSResources(config, resourcesDirectory);
#line 380 "/src/macos-app-driver.do"
    auto _try_value_54 = embedMacOSLibraries(bundleExecutable, config, libraryPaths, buildDirectory, contentsDirectory);
    if (doof::is_failure(_try_value_54)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_54))};
#line 381 "/src/macos-app-driver.do"
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 382 "/src/macos-app-driver.do"
    collectNestedMacOSCode(outputPath(contentsDirectory, std::string("Frameworks")), nested);
#line 383 "/src/macos-app-driver.do"
    const auto& _iterable_56 = nested;
    for (const auto& path : *_iterable_56) {
#line 384 "/src/macos-app-driver.do"
        auto _try_value_57 = runRequiredCommand(std::string("codesign"), ::app_src_macos_app_::macOSCodesignArguments(path, std::string("-"), std::string("ad-hoc"), std::string("")), std::string("ad-hoc signing nested macOS code"));
        if (doof::is_failure(_try_value_57)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_57))};
    }
#line 386 "/src/macos-app-driver.do"
    auto _try_value_58 = runRequiredCommand(std::string("codesign"), ::app_src_macos_app_::macOSCodesignArguments(appPath, std::string("-"), std::string("ad-hoc"), std::string("")), std::string("ad-hoc signing macOS app"));
    if (doof::is_failure(_try_value_58)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_58))};
#line 387 "/src/macos-app-driver.do"
    return doof::Success<std::string>{ appPath };
}
#line 390 "/src/macos-app-driver.do"
doof::Result<std::string, std::string> developerIdIdentity(const std::string& configured) {
#line 391 "/src/macos-app-driver.do"
    if (configured != std::string("")) {
#line 391 "/src/macos-app-driver.do"
        return doof::Success<std::string>{ configured };
    }
#line 392 "/src/macos-app-driver.do"
    const auto result = runMacOSCommand(std::string("security"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("find-identity"), std::string("-v"), std::string("-p"), std::string("codesigning")}));
#line 393 "/src/macos-app-driver.do"
    if (result->exitCode != 0) {
#line 393 "/src/macos-app-driver.do"
        return doof::Failure<std::string>{ std::string("Could not discover Developer ID Application signing identities") };
    }
#line 394 "/src/macos-app-driver.do"
    const auto commandOutput = ::doof_blob::NativeBlobReader::constructor(result->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->output)->size())));
#line 395 "/src/macos-app-driver.do"
    std::shared_ptr<std::vector<std::string>> identities = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 396 "/src/macos-app-driver.do"
    const auto marker = std::string("\"Developer ID Application:");
#line 397 "/src/macos-app-driver.do"
    const auto& _iterable_60 = doof::string_split(commandOutput, std::string("\n"));
    for (const auto& line : *_iterable_60) {
#line 398 "/src/macos-app-driver.do"
        auto start = -1;
#line 399 "/src/macos-app-driver.do"
        for (int32_t index = 0; index < ((static_cast<int32_t>(line.size()) - static_cast<int32_t>(marker.size())) + 1); ++index) {
#line 400 "/src/macos-app-driver.do"
            if (doof::string_substring(line, index, (index + static_cast<int32_t>(marker.size()))) == marker) {
#line 400 "/src/macos-app-driver.do"
                (start = (index + 1));
#line 400 "/src/macos-app-driver.do"
                break;
            }
        }
#line 402 "/src/macos-app-driver.do"
        if (start < 0) {
#line 402 "/src/macos-app-driver.do"
            continue;
        }
#line 403 "/src/macos-app-driver.do"
        auto end = start;
#line 404 "/src/macos-app-driver.do"
        while ((end < static_cast<int32_t>(line.size())) && (doof::string_substring(line, end, (end + 1)) != std::string("\""))) {
#line 404 "/src/macos-app-driver.do"
            (end = (end + 1));
        }
#line 405 "/src/macos-app-driver.do"
        if (end > start) {
#line 405 "/src/macos-app-driver.do"
            identities->push_back(doof::string_substring(line, start, end));
        }
    }
#line 407 "/src/macos-app-driver.do"
    if (static_cast<int32_t>((identities)->size()) == 0) {
#line 407 "/src/macos-app-driver.do"
        return doof::Failure<std::string>{ std::string("No Developer ID Application signing identity found; pass --macos-sign-identity or use --macos-signing ad-hoc") };
    }
#line 408 "/src/macos-app-driver.do"
    if (static_cast<int32_t>((identities)->size()) > 1) {
#line 408 "/src/macos-app-driver.do"
        return doof::Failure<std::string>{ std::string("Multiple Developer ID Application identities found; pass --macos-sign-identity") };
    }
#line 409 "/src/macos-app-driver.do"
    return doof::Success<std::string>{ doof::array_at(identities, 0, "src/macos-app-driver", 409) };
}
#line 412 "/src/macos-app-driver.do"
doof::Result<std::string, std::string> effectiveEntitlements(const std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>& config, const std::string& buildDirectory) {
#line 413 "/src/macos-app-driver.do"
    if (!config->sandbox) {
#line 413 "/src/macos-app-driver.do"
        return doof::Success<std::string>{ config->entitlementsPath };
    }
#line 414 "/src/macos-app-driver.do"
    const auto destinationPath = outputPath(buildDirectory, std::string(".doof-package-entitlements.plist"));
#line 415 "/src/macos-app-driver.do"
    if (config->entitlementsPath != std::string("")) {
#line 416 "/src/macos-app-driver.do"
        copyPath(config->entitlementsPath, destinationPath);
#line 417 "/src/macos-app-driver.do"
        const auto sandboxValue = runMacOSCommand(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-extract"), std::string("com.apple.security.app-sandbox"), std::string("raw"), std::string("-o"), std::string("-"), destinationPath}));
#line 418 "/src/macos-app-driver.do"
        if (sandboxValue->exitCode == 0) {
#line 419 "/src/macos-app-driver.do"
            const auto value = doof::string_toLowerCase(::doof_blob::NativeBlobReader::constructor(sandboxValue->output, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((sandboxValue->output)->size()))));
#line 420 "/src/macos-app-driver.do"
            if (doof::string_contains(value, std::string("false"))) {
#line 421 "/src/macos-app-driver.do"
                return doof::Failure<std::string>{ std::string("macOS sandbox is enabled but the supplied entitlements explicitly disable it") };
            }
        }
#line 424 "/src/macos-app-driver.do"
        const auto replaced = runMacOSCommand(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-replace"), std::string("com.apple.security.app-sandbox"), std::string("-bool"), std::string("YES"), destinationPath}));
#line 425 "/src/macos-app-driver.do"
        if (replaced->exitCode != 0) {
#line 426 "/src/macos-app-driver.do"
            auto _try_value_62 = runRequiredCommand(std::string("plutil"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-insert"), std::string("com.apple.security.app-sandbox"), std::string("-bool"), std::string("YES"), destinationPath}), std::string("enabling App Sandbox"));
            if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_62))};
        }
    } else {
#line 429 "/src/macos-app-driver.do"
        [&]() -> void { auto _try_value = ::doof_fs::writeText(destinationPath, std::string("<\?xml version=\"1.0\" encoding=\"UTF-8\"\?>\n<plist version=\"1.0\"><dict><key>com.apple.security.app-sandbox</key><true/></dict></plist>\n")); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 429, std::string("try! failed"));  }();
    }
#line 431 "/src/macos-app-driver.do"
    return doof::Success<std::string>{ destinationPath };
}
#line 435 "/src/macos-app-driver.do"
doof::Result<void, std::string> signAndArchiveMacOSApp(const std::string& appPath, const std::string& archivePath, const std::shared_ptr<::app_src_macos_app_::MacOSPackageConfig>& config, const std::string& buildDirectory) {
#line 441 "/src/macos-app-driver.do"
    auto identity = std::string("-");
#line 442 "/src/macos-app-driver.do"
    if (config->signing != std::string("ad-hoc")) {
#line 443 "/src/macos-app-driver.do"
        auto _try_value_63 = developerIdIdentity(config->identity);
        if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_63))};
        const auto resolvedIdentity = doof::success_value(_try_value_63);
#line 444 "/src/macos-app-driver.do"
        (identity = resolvedIdentity);
    }
#line 446 "/src/macos-app-driver.do"
    auto _try_value_64 = effectiveEntitlements(config, buildDirectory);
    if (doof::is_failure(_try_value_64)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_64))};
    const auto entitlementsPath = doof::success_value(_try_value_64);
#line 447 "/src/macos-app-driver.do"
    std::shared_ptr<std::vector<std::string>> nested = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 448 "/src/macos-app-driver.do"
    collectNestedMacOSCode(outputPath(appPath, std::string("Contents/Frameworks")), nested);
#line 449 "/src/macos-app-driver.do"
    collectNestedMacOSCode(outputPath(appPath, std::string("Contents/PlugIns")), nested);
#line 450 "/src/macos-app-driver.do"
    collectNestedMacOSCode(outputPath(appPath, std::string("Contents/XPCServices")), nested);
#line 451 "/src/macos-app-driver.do"
    const auto& _iterable_66 = nested;
    for (const auto& path : *_iterable_66) {
#line 451 "/src/macos-app-driver.do"
        auto _try_value_67 = runRequiredCommand(std::string("codesign"), ::app_src_macos_app_::macOSCodesignArguments(path, identity, config->signing, std::string("")), std::string("signing nested macOS code"));
        if (doof::is_failure(_try_value_67)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_67))};
    }
#line 452 "/src/macos-app-driver.do"
    auto _try_value_68 = runRequiredCommand(std::string("codesign"), ::app_src_macos_app_::macOSCodesignArguments(appPath, identity, config->signing, entitlementsPath), std::string("signing macOS app"));
    if (doof::is_failure(_try_value_68)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_68))};
#line 453 "/src/macos-app-driver.do"
    auto _try_value_69 = runRequiredCommand(std::string("codesign"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("--verify"), std::string("--deep"), std::string("--strict"), std::string("--verbose=2"), appPath}), std::string("verifying macOS app signature"));
    if (doof::is_failure(_try_value_69)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_69))};
#line 454 "/src/macos-app-driver.do"
    ensureDirectory(parentPath(archivePath));
#line 455 "/src/macos-app-driver.do"
    if (::doof_fs::exists(archivePath)) {
#line 455 "/src/macos-app-driver.do"
        [&]() -> void { auto _try_value = ::doof_fs::remove(archivePath); if (doof::is_failure(_try_value)) doof::panic_at("src/macos-app-driver", 455, std::string("try! failed"));  }();
    }
#line 456 "/src/macos-app-driver.do"
    auto _try_value_70 = runRequiredCommand(std::string("ditto"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-c"), std::string("-k"), std::string("--sequesterRsrc"), std::string("--keepParent"), appPath, archivePath}), std::string("archiving macOS app"));
    if (doof::is_failure(_try_value_70)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_70))};
#line 457 "/src/macos-app-driver.do"
    return doof::Success<void>{};
}
#line 1 "<doof-generated>"
}
