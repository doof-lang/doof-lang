#include "std_path_index.hpp"

namespace std_::path::index {
doof::Result<std::string, std::string> normalizePathResult(const doof::Result<std::string, std::string>& result) {
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
    return normalizePathResult(::doof_path::homeDirectory());
}
std::string tempDirectory() {
    return join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{::doof_path::tempDirectory()}));
}
doof::Result<std::string, std::string> dataDirectory(const std::optional<std::string>& appId) {
    return normalizePathResult(::doof_path::dataDirectory(appId));
}
doof::Result<std::string, std::string> cacheDirectory(const std::optional<std::string>& appId) {
    return normalizePathResult(::doof_path::cacheDirectory(appId));
}
doof::Result<std::string, std::string> currentWorkingDirectory() {
    return normalizePathResult(::doof_path::currentWorkingDirectory());
}
doof::Result<std::string, std::string> absolute(const std::string& path) {
    return normalizePathResult(::doof_path::absolute(join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}))));
}
doof::Result<std::string, std::string> resourcesDirectory() {
    return normalizePathResult(::doof_path::resourcesDirectory());
}
doof::Result<std::string, std::string> resourcePath(const std::string& path) {
    auto _try_value_1 = resourcesDirectory();
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
    const auto resources = doof::success_value(_try_value_1);
    return resolveWithin(resources, path);
}
std::string normalize(const std::string& path) {
    return join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}));
}
doof::Result<std::string, std::string> relative(const std::string& fromPath, const std::string& toPath) {
    const auto normalizedFrom = normalize(fromPath);
    const auto normalizedTo = normalize(toPath);
    const auto fromPrefix = rootPrefix(normalizedFrom);
    const auto toPrefix = rootPrefix(normalizedTo);
    if (!rootsEqual(fromPrefix, toPrefix)) {
        return doof::Failure<std::string>{ std::string("Cannot create a relative path between different roots") };
    }
    const auto fromSegments = pathSegments(normalizedFrom, fromPrefix);
    const auto toSegments = pathSegments(normalizedTo, toPrefix);
    const auto caseInsensitive = isWindowsRoot(fromPrefix);
    auto shared = 0;
    while (((shared < static_cast<int32_t>((fromSegments)->size())) && (shared < static_cast<int32_t>((toSegments)->size()))) && segmentsEqual(doof::array_at(fromSegments, shared, "index", 69), doof::array_at(toSegments, shared, "index", 69), caseInsensitive)) {
        (shared += 1);
    }
    std::shared_ptr<std::vector<std::string>> result = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    for (int32_t _discard_2_0 = shared; _discard_2_0 < static_cast<int32_t>((fromSegments)->size()); ++_discard_2_0) {
        result->push_back(std::string(".."));
    }
    for (int32_t index = shared; index < static_cast<int32_t>((toSegments)->size()); ++index) {
        result->push_back(doof::array_at(toSegments, index, "index", 78));
    }
    return doof::Success<std::string>{ join(result) };
}
doof::Result<std::string, std::string> resolveWithin(const std::string& base, const std::string& path) {
    const auto normalizedBase = normalize(base);
    if (!isAbsolute(normalizedBase)) {
        return doof::Failure<std::string>{ std::string("Base path must be absolute") };
    }
    const auto resolved = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{normalizedBase, path}));
    const auto basePrefix = rootPrefix(normalizedBase);
    const auto resolvedPrefix = rootPrefix(resolved);
    if (!rootsEqual(basePrefix, resolvedPrefix)) {
        return doof::Failure<std::string>{ std::string("Resolved path cannot escape the base path") };
    }
    const auto baseSegments = pathSegments(normalizedBase, basePrefix);
    const auto resolvedSegments = pathSegments(resolved, resolvedPrefix);
    const auto caseInsensitive = isWindowsRoot(basePrefix);
    if (static_cast<int32_t>((baseSegments)->size()) > static_cast<int32_t>((resolvedSegments)->size())) {
        return doof::Failure<std::string>{ std::string("Resolved path cannot escape the base path") };
    }
    for (int32_t index = 0; index < static_cast<int32_t>((baseSegments)->size()); ++index) {
        if (!segmentsEqual(doof::array_at(baseSegments, index, "index", 105), doof::array_at(resolvedSegments, index, "index", 105), caseInsensitive)) {
            return doof::Failure<std::string>{ std::string("Resolved path cannot escape the base path") };
        }
    }
    return doof::Success<std::string>{ resolved };
}
std::string join(const std::shared_ptr<std::vector<std::string>>& parts) {
    auto prefix = std::string("");
    std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_8 = parts;
    for (const auto& part : *_iterable_8) {
        if (static_cast<int32_t>(part.size()) == 0) {
            continue;
        }
        const auto normalizedPart = doof::string_replaceAll(part, std::string("\\"), std::string("/"));
        const auto partPrefix = rootPrefix(normalizedPart);
        if (partPrefix != std::string("")) {
            (prefix = partPrefix);
            (segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
        auto segmentSource = normalizedPart;
        if (partPrefix != std::string("")) {
            (segmentSource = doof::string_slice(normalizedPart, static_cast<int32_t>(partPrefix.size())));
            if (doof::string_startsWith(segmentSource, std::string("/"))) {
                (segmentSource = doof::string_slice(segmentSource, 1));
            }
        }
        const auto rawSegments = doof::string_split(segmentSource, std::string("/"));
        const auto& _iterable_6 = rawSegments;
        for (const auto& rawSegment : *_iterable_6) {
            if ((static_cast<int32_t>(rawSegment.size()) == 0) || (rawSegment == std::string("."))) {
                continue;
            }
            if (rawSegment == std::string("..")) {
                if ((static_cast<int32_t>((segments)->size()) > 0) && (doof::array_at(segments, (static_cast<int32_t>((segments)->size()) - 1), "index", 143) != std::string(".."))) {
                    (segments = doof::array_slice(segments, 0, (static_cast<int32_t>((segments)->size()) - 1), "", 0));
                } else if (prefix == std::string("")) {
                    segments->push_back(std::string(".."));
                }
                continue;
            }
            segments->push_back(rawSegment);
        }
    }
    return renderPath(segments, prefix);
}
std::string dirname(const std::string& path) {
    const auto normalized = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}));
    const auto prefix = rootPrefix(normalized);
    if ((normalized == std::string("/")) || ((prefix != std::string("")) && (normalized == (prefix + std::string("/"))))) {
        return normalized;
    }
    const auto separator = lastSeparatorIndex(normalized);
    if (separator < 0) {
        return std::string(".");
    }
    if (separator == 0) {
        return std::string("/");
    }
    if ((prefix != std::string("")) && (separator == static_cast<int32_t>(prefix.size()))) {
        return (prefix + std::string("/"));
    }
    return doof::string_substring(normalized, 0, separator);
}
std::string basename(const std::string& path) {
    const auto normalized = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}));
    const auto prefix = rootPrefix(normalized);
    if ((normalized == std::string("/")) || ((prefix != std::string("")) && (normalized == (prefix + std::string("/"))))) {
        return std::string("");
    }
    const auto separator = lastSeparatorIndex(normalized);
    if (separator < 0) {
        return normalized;
    }
    return doof::string_slice(normalized, (separator + 1));
}
std::string stem(const std::string& path) {
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
std::string extension(const std::string& path) {
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
bool isAbsolute(const std::string& path) {
    return (rootPrefix(doof::string_replaceAll(path, std::string("\\"), std::string("/"))) != std::string(""));
}
std::string rootPrefix(const std::string& path) {
    if (doof::string_startsWith(path, std::string("//"))) {
        const auto components = doof::string_split(path, std::string("/"));
        if (((static_cast<int32_t>((components)->size()) >= 4) && (doof::array_at(components, 2, "index", 225) != std::string(""))) && (doof::array_at(components, 3, "index", 225) != std::string(""))) {
            return (((std::string("//") + doof::array_at(components, 2, "index", 226)) + std::string("/")) + doof::array_at(components, 3, "index", 226));
        }
    }
    if (doof::string_startsWith(path, std::string("/"))) {
        return std::string("/");
    }
    if ((((static_cast<int32_t>(path.size()) >= 3) && isAsciiLetter(doof::string_at(path, 0, "", 0))) && (doof::string_at(path, 1, "", 0) == U'\u003A')) && (doof::string_at(path, 2, "", 0) == U'\u002F')) {
        return doof::string_substring(path, 0, 2);
    }
    return std::string("");
}
bool isAsciiLetter(char32_t character) {
    return (((character >= U'\u0041') && (character <= U'\u005A')) || ((character >= U'\u0061') && (character <= U'\u007A')));
}
bool rootsEqual(const std::string& left, const std::string& right) {
    return (doof::string_toLowerCase(left) == doof::string_toLowerCase(right));
}
bool isWindowsRoot(const std::string& prefix) {
    return ((prefix != std::string("")) && (prefix != std::string("/")));
}
bool segmentsEqual(const std::string& left, const std::string& right, bool caseInsensitive) {
    return (caseInsensitive ? (doof::string_toLowerCase(left) == doof::string_toLowerCase(right)) : (left == right));
}
std::shared_ptr<std::vector<std::string>> pathSegments(const std::string& path, const std::string& prefix) {
    auto source = path;
    if (prefix != std::string("")) {
        (source = doof::string_slice(path, static_cast<int32_t>(prefix.size())));
        if (doof::string_startsWith(source, std::string("/"))) {
            (source = doof::string_slice(source, 1));
        }
    }
    if ((source == std::string("")) || (source == std::string("."))) {
        return std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    }
    return doof::string_split(source, std::string("/"));
}
std::string renderPath(const std::shared_ptr<std::vector<std::string>>& segments, const std::string& prefix) {
    if (static_cast<int32_t>((segments)->size()) == 0) {
        return ((prefix == std::string("")) ? std::string(".") : ((prefix == std::string("/")) ? std::string("/") : (prefix + std::string("/"))));
    }
    auto output = doof::array_at(segments, 0, "index", 274);
    for (int32_t index = 1; index < static_cast<int32_t>((segments)->size()); ++index) {
        (output += (std::string("/") + doof::array_at(segments, index, "index", 276)));
    }
    if (prefix == std::string("/")) {
        return (std::string("/") + output);
    }
    if (prefix != std::string("")) {
        return ((prefix + std::string("/")) + output);
    }
    return output;
}
int32_t lastSeparatorIndex(const std::string& path) {
    auto index = (static_cast<int32_t>(path.size()) - 1);
    while (index >= 0) {
        if (doof::string_at(path, index, "", 0) == U'\u002F') {
            return index;
        }
        (index -= 1);
    }
    return -1;
}
int32_t lastDotIndex(const std::string& path) {
    auto index = (static_cast<int32_t>(path.size()) - 1);
    while (index >= 0) {
        if (doof::string_at(path, index, "", 0) == U'\u002E') {
            return index;
        }
        (index -= 1);
    }
    return -1;
}
}
