#include "src_pkg_config.hpp"

namespace app_src_pkg_config_ {
using namespace ::app_src_package_manifest_;

doof::Result<void, std::string> applyPkgConfigResult(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, const std::string& packageName, const std::string& mode, const std::shared_ptr<PkgConfigCommandResult>& result) {
    if (result->exitCode == -1) {
        const auto detail = ((result->error == std::string("")) ? std::string("the executable could not be started") : result->error);
        return doof::Failure<std::string>{ ((((std::string("Failed to run pkg-config while resolving package \"") + packageName) + std::string("\": ")) + detail) + std::string(". Install pkg-config, or remove the package from build.native.pkgConfigPackages.")) };
    }
    if (result->exitCode != 0) {
        const auto detail = doof::string_trim(result->output);
        const auto suffix = ((detail == std::string("")) ? std::string("") : (std::string(": ") + detail));
        return doof::Failure<std::string>{ ((((((std::string("pkg-config could not resolve package \"") + packageName) + std::string("\" (exit code ")) + doof::to_string(result->exitCode)) + std::string(")")) + suffix) + std::string(". Install the package metadata, or remove it from build.native.pkgConfigPackages.")) };
    }
    (static_cast<void>(applyPkgConfigTokens(native, pkgConfigTokens(result->output), mode)), std::monostate{});
    return doof::Success<void>{};
}
std::shared_ptr<std::vector<std::string>> pkgConfigTokens(const std::string& output) {
    const auto normalized = doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(output, std::string("\n"), std::string(" ")), std::string("\r"), std::string(" ")), std::string("\t"), std::string(" "));
    std::shared_ptr<std::vector<std::string>> tokens = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_2 = doof::string_split(normalized, std::string(" "));
    for (const auto& token : *_iterable_2) {
        if (token != std::string("")) {
            (static_cast<void>(tokens->push_back(token)), std::monostate{});
        }
    }
    return tokens;
}
void applyPkgConfigTokens(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, const std::shared_ptr<std::vector<std::string>>& tokens, const std::string& mode) {
    auto index = 0;
    while (index < static_cast<int32_t>((tokens)->size())) {
        const auto token = doof::array_at(tokens, index, "src/pkg-config", 62);
        if (token == std::string("-framework")) {
            if ((index + 1) < static_cast<int32_t>((tokens)->size())) {
                (static_cast<void>(appendUnique(native->frameworks, doof::array_at(tokens, (index + 1), "src/pkg-config", 65))), std::monostate{});
                (index += 2);
            } else {
                (index += 1);
            }
            continue;
        }
        if (((token == std::string("-I")) || (token == std::string("-L"))) || (token == std::string("-D"))) {
            if ((index + 1) < static_cast<int32_t>((tokens)->size())) {
                const auto value = doof::array_at(tokens, (index + 1), "src/pkg-config", 75);
                if (token == std::string("-I")) {
                    (static_cast<void>(appendUnique(native->includePaths, value)), std::monostate{});
                }
                if (token == std::string("-L")) {
                    (static_cast<void>(appendUnique(native->libraryPaths, value)), std::monostate{});
                }
                if (token == std::string("-D")) {
                    (static_cast<void>(appendUnique(native->defines, value)), std::monostate{});
                }
                (index += 2);
            } else {
                (index += 1);
            }
            continue;
        }
        if (doof::string_startsWith(token, std::string("-I"))) {
            (static_cast<void>(appendUnique(native->includePaths, doof::string_substring(token, 2, static_cast<int32_t>(token.size())))), std::monostate{});
        } else if (doof::string_startsWith(token, std::string("-L"))) {
            (static_cast<void>(appendUnique(native->libraryPaths, doof::string_substring(token, 2, static_cast<int32_t>(token.size())))), std::monostate{});
        } else if (doof::string_startsWith(token, std::string("-l"))) {
            (static_cast<void>(appendUnique(native->linkLibraries, doof::string_substring(token, 2, static_cast<int32_t>(token.size())))), std::monostate{});
        } else if (doof::string_startsWith(token, std::string("-D"))) {
            (static_cast<void>(appendUnique(native->defines, doof::string_substring(token, 2, static_cast<int32_t>(token.size())))), std::monostate{});
        } else if (mode == std::string("cflags")) {
            (static_cast<void>(appendUnique(native->compilerFlags, token)), std::monostate{});
        } else {
            (static_cast<void>(appendUnique(native->linkerFlags, token)), std::monostate{});
        }
        (index += 1);
    }
}
void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value) {
    const auto& _iterable_4 = target;
    for (const auto& existing : *_iterable_4) {
        if (existing == value) {
            return;
        }
    }
    (static_cast<void>(target->push_back(value)), std::monostate{});
}
}
