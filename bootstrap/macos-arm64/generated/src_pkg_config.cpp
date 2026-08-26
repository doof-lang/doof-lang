#include "src_pkg_config.hpp"

namespace app_src_pkg_config_ {
using namespace ::app_src_package_manifest_;

#line 23 "/src/pkg-config.do"
doof::Result<void, std::string> applyPkgConfigResult(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, const std::string& packageName, const std::string& mode, const std::shared_ptr<PkgConfigCommandResult>& result) {
#line 29 "/src/pkg-config.do"
    if (result->exitCode == -1) {
#line 30 "/src/pkg-config.do"
        const auto detail = ((result->error == std::string("")) ? std::string("the executable could not be started") : result->error);
#line 31 "/src/pkg-config.do"
        return doof::Failure<std::string>{ ((((std::string("Failed to run pkg-config while resolving package \"") + packageName) + std::string("\": ")) + detail) + std::string(". Install pkg-config, or remove the package from build.native.pkgConfigPackages.")) };
    }
#line 36 "/src/pkg-config.do"
    if (result->exitCode != 0) {
#line 37 "/src/pkg-config.do"
        const auto detail = doof::string_trim(result->output);
#line 38 "/src/pkg-config.do"
        const auto suffix = ((detail == std::string("")) ? std::string("") : (std::string(": ") + detail));
#line 39 "/src/pkg-config.do"
        return doof::Failure<std::string>{ ((((((std::string("pkg-config could not resolve package \"") + packageName) + std::string("\" (exit code ")) + doof::to_string(result->exitCode)) + std::string(")")) + suffix) + std::string(". Install the package metadata, or remove it from build.native.pkgConfigPackages.")) };
    }
#line 46 "/src/pkg-config.do"
    applyPkgConfigTokens(native, pkgConfigTokens(result->output), mode);
#line 47 "/src/pkg-config.do"
    return doof::Success<void>{};
}
#line 50 "/src/pkg-config.do"
std::shared_ptr<std::vector<std::string>> pkgConfigTokens(const std::string& output) {
#line 51 "/src/pkg-config.do"
    const auto normalized = doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(output, std::string("\n"), std::string(" ")), std::string("\r"), std::string(" ")), std::string("\t"), std::string(" "));
#line 52 "/src/pkg-config.do"
    std::shared_ptr<std::vector<std::string>> tokens = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 53 "/src/pkg-config.do"
    const auto& _iterable_2 = doof::string_split(normalized, std::string(" "));
    for (const auto& token : *_iterable_2) {
#line 54 "/src/pkg-config.do"
        if (token != std::string("")) {
#line 54 "/src/pkg-config.do"
            tokens->push_back(token);
        }
    }
#line 56 "/src/pkg-config.do"
    return tokens;
}
#line 59 "/src/pkg-config.do"
void applyPkgConfigTokens(const std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan>& native, const std::shared_ptr<std::vector<std::string>>& tokens, const std::string& mode) {
#line 60 "/src/pkg-config.do"
    auto index = 0;
#line 61 "/src/pkg-config.do"
    while (index < static_cast<int32_t>((tokens)->size())) {
#line 62 "/src/pkg-config.do"
        const auto token = doof::array_at(tokens, index, "src/pkg-config", 62);
#line 63 "/src/pkg-config.do"
        if (token == std::string("-framework")) {
#line 64 "/src/pkg-config.do"
            if ((index + 1) < static_cast<int32_t>((tokens)->size())) {
#line 65 "/src/pkg-config.do"
                appendUnique(native->frameworks, doof::array_at(tokens, (index + 1), "src/pkg-config", 65));
#line 66 "/src/pkg-config.do"
                (index += 2);
            } else {
#line 68 "/src/pkg-config.do"
                (index += 1);
            }
#line 70 "/src/pkg-config.do"
            continue;
        }
#line 73 "/src/pkg-config.do"
        if (((token == std::string("-I")) || (token == std::string("-L"))) || (token == std::string("-D"))) {
#line 74 "/src/pkg-config.do"
            if ((index + 1) < static_cast<int32_t>((tokens)->size())) {
#line 75 "/src/pkg-config.do"
                const auto value = doof::array_at(tokens, (index + 1), "src/pkg-config", 75);
#line 76 "/src/pkg-config.do"
                if (token == std::string("-I")) {
#line 76 "/src/pkg-config.do"
                    appendUnique(native->includePaths, value);
                }
#line 77 "/src/pkg-config.do"
                if (token == std::string("-L")) {
#line 77 "/src/pkg-config.do"
                    appendUnique(native->libraryPaths, value);
                }
#line 78 "/src/pkg-config.do"
                if (token == std::string("-D")) {
#line 78 "/src/pkg-config.do"
                    appendUnique(native->defines, value);
                }
#line 79 "/src/pkg-config.do"
                (index += 2);
            } else {
#line 81 "/src/pkg-config.do"
                (index += 1);
            }
#line 83 "/src/pkg-config.do"
            continue;
        }
#line 86 "/src/pkg-config.do"
        if (doof::string_startsWith(token, std::string("-I"))) {
#line 86 "/src/pkg-config.do"
            appendUnique(native->includePaths, doof::string_substring(token, 2, static_cast<int32_t>(token.size())));
        } else if (doof::string_startsWith(token, std::string("-L"))) {
#line 87 "/src/pkg-config.do"
            appendUnique(native->libraryPaths, doof::string_substring(token, 2, static_cast<int32_t>(token.size())));
        } else if (doof::string_startsWith(token, std::string("-l"))) {
#line 88 "/src/pkg-config.do"
            appendUnique(native->linkLibraries, doof::string_substring(token, 2, static_cast<int32_t>(token.size())));
        } else if (doof::string_startsWith(token, std::string("-D"))) {
#line 89 "/src/pkg-config.do"
            appendUnique(native->defines, doof::string_substring(token, 2, static_cast<int32_t>(token.size())));
        } else if (mode == std::string("cflags")) {
#line 90 "/src/pkg-config.do"
            appendUnique(native->compilerFlags, token);
        } else {
#line 91 "/src/pkg-config.do"
            appendUnique(native->linkerFlags, token);
        }
#line 92 "/src/pkg-config.do"
        (index += 1);
    }
}
#line 96 "/src/pkg-config.do"
void appendUnique(const std::shared_ptr<std::vector<std::string>>& target, const std::string& value) {
#line 97 "/src/pkg-config.do"
    const auto& _iterable_4 = target;
    for (const auto& existing : *_iterable_4) {
#line 97 "/src/pkg-config.do"
        if (existing == value) {
#line 97 "/src/pkg-config.do"
            return;
        }
    }
#line 98 "/src/pkg-config.do"
    target->push_back(value);
}
#line 1 "<doof-generated>"
}
