#include "src_pkg_config.hpp"
#include <cmath>
#include "src_package_manifest.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_pkg_config_ {
using namespace ::app_src_package_manifest_;

doof::JsonObject PkgConfigCommandResult::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["exitCode"] = doof::json_value(this->exitCode);
    (*_json)["output"] = doof::json_value(this->output);
    (*_json)["error"] = doof::json_value(this->error);
    return _json;
}
doof::Result<std::shared_ptr<PkgConfigCommandResult>, std::string> PkgConfigCommandResult::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_exitCode = _object->find("exitCode");
    if (_iterator_exitCode == _object->end()) { return doof::Failure<std::string>{"Missing required field \"exitCode\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_exitCode->second) : doof::json_is_number(_iterator_exitCode->second)))) { return doof::Failure<std::string>{"Field \"exitCode\" expected number but got " + std::string(doof::json_type_name(_iterator_exitCode->second))}; }
    auto _field_exitCode = (_lenient ? doof::json_as_int_lenient(_iterator_exitCode->second) : doof::json_as_int(_iterator_exitCode->second));
    std::optional<std::string> _field_output;
    if (auto _iterator_output = _object->find("output"); _iterator_output != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_output->second) : doof::json_is_string(_iterator_output->second)))) { return doof::Failure<std::string>{"Field \"output\" expected string but got " + std::string(doof::json_type_name(_iterator_output->second))}; }
        _field_output = (_lenient ? doof::json_as_string_lenient(_iterator_output->second) : doof::json_as_string(_iterator_output->second));
    } else {
        _field_output = std::string{std::string("")};
    }
    std::optional<std::string> _field_error;
    if (auto _iterator_error = _object->find("error"); _iterator_error != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_error->second) : doof::json_is_string(_iterator_error->second)))) { return doof::Failure<std::string>{"Field \"error\" expected string but got " + std::string(doof::json_type_name(_iterator_error->second))}; }
        _field_error = (_lenient ? doof::json_as_string_lenient(_iterator_error->second) : doof::json_as_string(_iterator_error->second));
    } else {
        _field_error = std::string{std::string("")};
    }
    return doof::Success<std::shared_ptr<PkgConfigCommandResult>>{std::make_shared<PkgConfigCommandResult>(_field_exitCode, _field_output.value(), _field_error.value())};
}
doof::Result<void, std::string> applyPkgConfigResult(std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> native, std::string packageName, std::string mode, std::shared_ptr<PkgConfigCommandResult> result) {
    if (result->exitCode == -1) {
        const auto detail = ((result->error == std::string("")) ? std::string("the executable could not be started") : result->error);
        return doof::Failure<std::string>{ ((((std::string("Failed to run pkg-config while resolving package \"") + packageName) + std::string("\": ")) + detail) + std::string(". Install pkg-config, or remove the package from build.native.pkgConfigPackages.")) };
    }
    if (result->exitCode != 0) {
        const auto detail = doof::string_trim(result->output);
        const auto suffix = ((detail == std::string("")) ? std::string("") : (std::string(": ") + detail));
        return doof::Failure<std::string>{ ((((((std::string("pkg-config could not resolve package \"") + packageName) + std::string("\" (exit code ")) + doof::to_string(result->exitCode)) + std::string(")")) + suffix) + std::string(". Install the package metadata, or remove it from build.native.pkgConfigPackages.")) };
    }
    applyPkgConfigTokens(native, pkgConfigTokens(result->output), mode);
    return doof::Success<void>{};
}
std::shared_ptr<std::vector<std::string>> pkgConfigTokens(std::string output) {
    const auto normalized = doof::string_replaceAll(doof::string_replaceAll(doof::string_replaceAll(output, std::string("\n"), std::string(" ")), std::string("\r"), std::string(" ")), std::string("\t"), std::string(" "));
    std::shared_ptr<std::vector<std::string>> tokens = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_1 = doof::string_split(normalized, std::string(" "));
    for (const auto& token : *_iterable_1) {
        if (token != std::string("")) {
            tokens->push_back(token);
        }
    }
    return tokens;
}
void applyPkgConfigTokens(std::shared_ptr<::app_src_package_manifest_::NativeBuildPlan> native, std::shared_ptr<std::vector<std::string>> tokens, std::string mode) {
    auto index = 0;
    while (index < static_cast<int32_t>((tokens)->size())) {
        const auto token = (*tokens)[index];
        if (token == std::string("-framework")) {
            if ((index + 1) < static_cast<int32_t>((tokens)->size())) {
                appendUnique(native->frameworks, (*tokens)[(index + 1)]);
                (index += 2);
            } else {
                (index += 1);
            }
            continue;
        }
        if (((token == std::string("-I")) || (token == std::string("-L"))) || (token == std::string("-D"))) {
            if ((index + 1) < static_cast<int32_t>((tokens)->size())) {
                const auto value = (*tokens)[(index + 1)];
                if (token == std::string("-I")) {
                    appendUnique(native->includePaths, value);
                }
                if (token == std::string("-L")) {
                    appendUnique(native->libraryPaths, value);
                }
                if (token == std::string("-D")) {
                    appendUnique(native->defines, value);
                }
                (index += 2);
            } else {
                (index += 1);
            }
            continue;
        }
        if (doof::string_startsWith(token, std::string("-I"))) {
            appendUnique(native->includePaths, doof::string_substring(token, 2, static_cast<int32_t>(token.size())));
        } else if (doof::string_startsWith(token, std::string("-L"))) {
            appendUnique(native->libraryPaths, doof::string_substring(token, 2, static_cast<int32_t>(token.size())));
        } else if (doof::string_startsWith(token, std::string("-l"))) {
            appendUnique(native->linkLibraries, doof::string_substring(token, 2, static_cast<int32_t>(token.size())));
        } else if (doof::string_startsWith(token, std::string("-D"))) {
            appendUnique(native->defines, doof::string_substring(token, 2, static_cast<int32_t>(token.size())));
        } else if (mode == std::string("cflags")) {
            appendUnique(native->compilerFlags, token);
        } else {
            appendUnique(native->linkerFlags, token);
        }
        (index += 1);
    }
}
void appendUnique(std::shared_ptr<std::vector<std::string>> target, std::string value) {
    const auto& _iterable_2 = target;
    for (const auto& existing : *_iterable_2) {
        if (existing == value) {
            return;
        }
    }
    target->push_back(value);
}
}
