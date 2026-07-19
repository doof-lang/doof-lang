#include "std_path_index.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::path::index {
doof::Result<std::string, std::string> normalizePathResult(doof::Result<std::string, std::string> result) {
    return [&]() -> doof::Result<std::string, std::string> {
    auto _case_subject = result;
    if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
        const auto& s = std::get<doof::Success<std::string>>(_case_subject);
        return doof::Success<std::string>{ join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{s.value})) };
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        const auto& f = std::get<doof::Failure<std::string>>(_case_subject);
        return doof::Failure<std::string>{ f.error };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
doof::Result<std::string, std::string> homeDirectory() {
    return normalizePathResult(_homeDirectory());
}
std::string tempDirectory() {
    return join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{_tempDirectory()}));
}
doof::Result<std::string, std::string> dataDirectory(std::optional<std::string> appId) {
    return normalizePathResult(_dataDirectory(appId));
}
doof::Result<std::string, std::string> cacheDirectory(std::optional<std::string> appId) {
    return normalizePathResult(_cacheDirectory(appId));
}
doof::Result<std::string, std::string> currentWorkingDirectory() {
    return normalizePathResult(_currentWorkingDirectory());
}
doof::Result<std::string, std::string> absolute(std::string path) {
    return normalizePathResult(_absolute(path));
}
doof::Result<std::string, std::string> resourcesDirectory() {
    return normalizePathResult(_resourcesDirectory());
}
doof::Result<std::string, std::string> resourcePath(std::string path) {
    auto _try_value_1 = resourcesDirectory();
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::failure_error(_try_value_1)};
    const auto resources = doof::success_value(_try_value_1);
    const auto resolved = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{resources, path}));
    if ((resolved == resources) || doof::string_startsWith(resolved, (resources + std::string("/")))) {
        return doof::Success<std::string>{ resolved };
    }
    return doof::Failure<std::string>{ std::string("Resource path cannot escape the resources directory") };
}
std::string join(std::shared_ptr<std::vector<std::string>> parts) {
    auto absolute = false;
    std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_2 = parts;
    for (const auto& part : *_iterable_2) {
        if (static_cast<int32_t>(part.size()) == 0) {
            continue;
        }
        if (isAbsolute(part)) {
            (absolute = true);
            (segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        const auto rawSegments = doof::string_split(part, std::string("/"));
        const auto& _iterable_3 = rawSegments;
        for (const auto& rawSegment : *_iterable_3) {
            if ((static_cast<int32_t>(rawSegment.size()) == 0) || (rawSegment == std::string("."))) {
                continue;
            }
            if (rawSegment == std::string("..")) {
                if ((static_cast<int32_t>((segments)->size()) > 0) && ((*segments)[(static_cast<int32_t>((segments)->size()) - 1)] != std::string(".."))) {
                    (segments = doof::array_slice(segments, 0, (static_cast<int32_t>((segments)->size()) - 1), "", 0));
                } else if (!absolute) {
                    segments->push_back(std::string(".."));
                }
                continue;
            }
            segments->push_back(rawSegment);
        }
    }
    return renderPath(segments, absolute);
}
std::string dirname(std::string path) {
    const auto normalized = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}));
    if (normalized == std::string("/")) {
        return std::string("/");
    }
    const auto separator = lastSeparatorIndex(normalized);
    if (separator < 0) {
        return std::string(".");
    }
    if (separator == 0) {
        return std::string("/");
    }
    return doof::string_substring(normalized, 0, separator);
}
std::string basename(std::string path) {
    const auto normalized = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}));
    if (normalized == std::string("/")) {
        return std::string("");
    }
    const auto separator = lastSeparatorIndex(normalized);
    if (separator < 0) {
        return normalized;
    }
    return doof::string_slice(normalized, (separator + 1));
}
std::string stem(std::string path) {
    const auto name = basename(path);
    if (((name == std::string("")) || (name == std::string("."))) || (name == std::string(".."))) {
        return name;
    }
    const auto dotIndex = lastDotIndex(name);
    if (dotIndex <= 0) {
        return name;
    }
    return doof::string_substring(name, 0, dotIndex);
}
std::string extension(std::string path) {
    const auto name = basename(path);
    if (((name == std::string("")) || (name == std::string("."))) || (name == std::string(".."))) {
        return std::string("");
    }
    const auto dotIndex = lastDotIndex(name);
    if (dotIndex <= 0) {
        return std::string("");
    }
    return doof::string_slice(name, dotIndex);
}
bool isAbsolute(std::string path) {
    return doof::string_startsWith(path, std::string("/"));
}
std::string renderPath(std::shared_ptr<std::vector<std::string>> segments, bool absolute) {
    if (static_cast<int32_t>((segments)->size()) == 0) {
        return (absolute ? std::string("/") : std::string("."));
    }
    auto output = (*segments)[0];
    for (int32_t index = 1; index < static_cast<int32_t>((segments)->size()); ++index) {
        (output += (std::string("/") + (*segments)[index]));
    }
    if (absolute) {
        return (std::string("/") + output);
    }
    return output;
}
int32_t lastSeparatorIndex(std::string path) {
    auto index = (static_cast<int32_t>(path.size()) - 1);
    while (index >= 0) {
        if (doof::string_at(path, index, "", 0) == U'\u002F') {
            return index;
        }
        (index -= 1);
    }
    return -1;
}
int32_t lastDotIndex(std::string path) {
    auto index = (static_cast<int32_t>(path.size()) - 1);
    while (index >= 0) {
        if (doof::string_at(path, index, "", 0) == U'\u002E') {
            return index;
        }
        (index -= 1);
    }
    return -1;
}
doof::Result<std::string, std::string> _homeDirectory() {
    return ::doof_path::homeDirectory();
}
std::string _tempDirectory() {
    return ::doof_path::tempDirectory();
}
doof::Result<std::string, std::string> _dataDirectory(std::optional<std::string> appId) {
    return ::doof_path::dataDirectory(appId);
}
doof::Result<std::string, std::string> _cacheDirectory(std::optional<std::string> appId) {
    return ::doof_path::cacheDirectory(appId);
}
doof::Result<std::string, std::string> _currentWorkingDirectory() {
    return ::doof_path::currentWorkingDirectory();
}
doof::Result<std::string, std::string> _absolute(std::string path) {
    return ::doof_path::absolute(path);
}
doof::Result<std::string, std::string> _resourcesDirectory() {
    return ::doof_path::resourcesDirectory();
}
}
