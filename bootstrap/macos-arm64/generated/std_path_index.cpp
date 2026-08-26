#include "std_path_index.hpp"

namespace std_::path::index {
#line 10 "/std/path/index.do"
doof::Result<std::string, std::string> normalizePathResult(const doof::Result<std::string, std::string>& result) {
#line 11 "/std/path/index.do"
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
#line 17 "/std/path/index.do"
doof::Result<std::string, std::string> homeDirectory() {
#line 18 "/std/path/index.do"
    return normalizePathResult(::doof_path::homeDirectory());
}
#line 21 "/std/path/index.do"
std::string tempDirectory() {
#line 22 "/std/path/index.do"
    return join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{::doof_path::tempDirectory()}));
}
#line 25 "/std/path/index.do"
doof::Result<std::string, std::string> dataDirectory(const std::optional<std::string>& appId) {
#line 26 "/std/path/index.do"
    return normalizePathResult(::doof_path::dataDirectory(appId));
}
#line 29 "/std/path/index.do"
doof::Result<std::string, std::string> cacheDirectory(const std::optional<std::string>& appId) {
#line 30 "/std/path/index.do"
    return normalizePathResult(::doof_path::cacheDirectory(appId));
}
#line 33 "/std/path/index.do"
doof::Result<std::string, std::string> currentWorkingDirectory() {
#line 34 "/std/path/index.do"
    return normalizePathResult(::doof_path::currentWorkingDirectory());
}
#line 37 "/std/path/index.do"
doof::Result<std::string, std::string> absolute(const std::string& path) {
#line 38 "/std/path/index.do"
    return normalizePathResult(::doof_path::absolute(join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}))));
}
#line 41 "/std/path/index.do"
doof::Result<std::string, std::string> resourcesDirectory() {
#line 42 "/std/path/index.do"
    return normalizePathResult(::doof_path::resourcesDirectory());
}
#line 45 "/std/path/index.do"
doof::Result<std::string, std::string> resourcePath(const std::string& path) {
#line 46 "/std/path/index.do"
    auto _try_value_1 = resourcesDirectory();
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
    const auto resources = doof::success_value(_try_value_1);
#line 47 "/std/path/index.do"
    const auto resolved = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{resources, path}));
#line 49 "/std/path/index.do"
    if ((resolved == resources) || doof::string_startsWith(resolved, (resources + std::string("/")))) {
#line 50 "/std/path/index.do"
        return doof::Success<std::string>{ resolved };
    }
#line 53 "/std/path/index.do"
    return doof::Failure<std::string>{ std::string("Resource path cannot escape the resources directory") };
}
#line 56 "/std/path/index.do"
std::string join(const std::shared_ptr<std::vector<std::string>>& parts) {
#line 57 "/std/path/index.do"
    auto prefix = std::string("");
#line 58 "/std/path/index.do"
    std::shared_ptr<std::vector<std::string>> segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
#line 60 "/std/path/index.do"
    const auto& _iterable_3 = parts;
    for (const auto& part : *_iterable_3) {
#line 61 "/std/path/index.do"
        if (static_cast<int32_t>(part.size()) == 0) {
#line 62 "/std/path/index.do"
            continue;
        }
#line 65 "/std/path/index.do"
        const auto normalizedPart = doof::string_replaceAll(part, std::string("\\"), std::string("/"));
#line 66 "/std/path/index.do"
        const auto partPrefix = rootPrefix(normalizedPart);
#line 67 "/std/path/index.do"
        if (partPrefix != std::string("")) {
#line 68 "/std/path/index.do"
            (prefix = partPrefix);
#line 69 "/std/path/index.do"
            (segments = std::make_shared<std::vector<std::string>>(std::vector<std::string>{}));
        }
#line 72 "/std/path/index.do"
        auto segmentSource = normalizedPart;
#line 73 "/std/path/index.do"
        if (partPrefix != std::string("")) {
#line 74 "/std/path/index.do"
            (segmentSource = doof::string_slice(normalizedPart, static_cast<int32_t>(partPrefix.size())));
#line 75 "/std/path/index.do"
            if (doof::string_startsWith(segmentSource, std::string("/"))) {
#line 76 "/std/path/index.do"
                (segmentSource = doof::string_slice(segmentSource, 1));
            }
        }
#line 79 "/std/path/index.do"
        const auto rawSegments = doof::string_split(segmentSource, std::string("/"));
#line 80 "/std/path/index.do"
        const auto& _iterable_5 = rawSegments;
        for (const auto& rawSegment : *_iterable_5) {
#line 81 "/std/path/index.do"
            if ((static_cast<int32_t>(rawSegment.size()) == 0) || (rawSegment == std::string("."))) {
#line 82 "/std/path/index.do"
                continue;
            }
#line 85 "/std/path/index.do"
            if (rawSegment == std::string("..")) {
#line 86 "/std/path/index.do"
                if ((static_cast<int32_t>((segments)->size()) > 0) && (doof::array_at(segments, (static_cast<int32_t>((segments)->size()) - 1), "index", 86) != std::string(".."))) {
#line 87 "/std/path/index.do"
                    (segments = doof::array_slice(segments, 0, (static_cast<int32_t>((segments)->size()) - 1), "", 0));
                } else if (prefix == std::string("")) {
#line 89 "/std/path/index.do"
                    segments->push_back(std::string(".."));
                }
#line 91 "/std/path/index.do"
                continue;
            }
#line 94 "/std/path/index.do"
            segments->push_back(rawSegment);
        }
    }
#line 98 "/std/path/index.do"
    return renderPath(segments, prefix);
}
#line 101 "/std/path/index.do"
std::string dirname(const std::string& path) {
#line 102 "/std/path/index.do"
    const auto normalized = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}));
#line 103 "/std/path/index.do"
    const auto prefix = rootPrefix(normalized);
#line 104 "/std/path/index.do"
    if ((normalized == std::string("/")) || ((prefix != std::string("")) && (normalized == (prefix + std::string("/"))))) {
#line 105 "/std/path/index.do"
        return normalized;
    }
#line 108 "/std/path/index.do"
    const auto separator = lastSeparatorIndex(normalized);
#line 109 "/std/path/index.do"
    if (separator < 0) {
#line 110 "/std/path/index.do"
        return std::string(".");
    }
#line 112 "/std/path/index.do"
    if (separator == 0) {
#line 113 "/std/path/index.do"
        return std::string("/");
    }
#line 115 "/std/path/index.do"
    if ((prefix != std::string("")) && (separator == static_cast<int32_t>(prefix.size()))) {
#line 116 "/std/path/index.do"
        return (prefix + std::string("/"));
    }
#line 118 "/std/path/index.do"
    return doof::string_substring(normalized, 0, separator);
}
#line 121 "/std/path/index.do"
std::string basename(const std::string& path) {
#line 122 "/std/path/index.do"
    const auto normalized = join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path}));
#line 123 "/std/path/index.do"
    const auto prefix = rootPrefix(normalized);
#line 124 "/std/path/index.do"
    if ((normalized == std::string("/")) || ((prefix != std::string("")) && (normalized == (prefix + std::string("/"))))) {
#line 125 "/std/path/index.do"
        return std::string("");
    }
#line 128 "/std/path/index.do"
    const auto separator = lastSeparatorIndex(normalized);
#line 129 "/std/path/index.do"
    if (separator < 0) {
#line 130 "/std/path/index.do"
        return normalized;
    }
#line 132 "/std/path/index.do"
    return doof::string_slice(normalized, (separator + 1));
}
#line 135 "/std/path/index.do"
std::string stem(const std::string& path) {
#line 136 "/std/path/index.do"
    const auto name = basename(path);
#line 137 "/std/path/index.do"
    if (((name == std::string("")) || (name == std::string("."))) || (name == std::string(".."))) {
#line 138 "/std/path/index.do"
        return name;
    }
#line 141 "/std/path/index.do"
    const auto dotIndex = lastDotIndex(name);
#line 142 "/std/path/index.do"
    if (dotIndex <= 0) {
#line 143 "/std/path/index.do"
        return name;
    }
#line 145 "/std/path/index.do"
    return doof::string_substring(name, 0, dotIndex);
}
#line 148 "/std/path/index.do"
std::string extension(const std::string& path) {
#line 149 "/std/path/index.do"
    const auto name = basename(path);
#line 150 "/std/path/index.do"
    if (((name == std::string("")) || (name == std::string("."))) || (name == std::string(".."))) {
#line 151 "/std/path/index.do"
        return std::string("");
    }
#line 154 "/std/path/index.do"
    const auto dotIndex = lastDotIndex(name);
#line 155 "/std/path/index.do"
    if (dotIndex <= 0) {
#line 156 "/std/path/index.do"
        return std::string("");
    }
#line 158 "/std/path/index.do"
    return doof::string_slice(name, dotIndex);
}
#line 161 "/std/path/index.do"
bool isAbsolute(const std::string& path) {
#line 162 "/std/path/index.do"
    return (rootPrefix(doof::string_replaceAll(path, std::string("\\"), std::string("/"))) != std::string(""));
}
#line 165 "/std/path/index.do"
std::string rootPrefix(const std::string& path) {
#line 166 "/std/path/index.do"
    if (doof::string_startsWith(path, std::string("//"))) {
#line 167 "/std/path/index.do"
        const auto components = doof::string_split(path, std::string("/"));
#line 168 "/std/path/index.do"
        if (((static_cast<int32_t>((components)->size()) >= 4) && (doof::array_at(components, 2, "index", 168) != std::string(""))) && (doof::array_at(components, 3, "index", 168) != std::string(""))) {
#line 169 "/std/path/index.do"
            return (((std::string("//") + doof::array_at(components, 2, "index", 169)) + std::string("/")) + doof::array_at(components, 3, "index", 169));
        }
    }
#line 172 "/std/path/index.do"
    if (doof::string_startsWith(path, std::string("/"))) {
#line 173 "/std/path/index.do"
        return std::string("/");
    }
#line 175 "/std/path/index.do"
    if ((((static_cast<int32_t>(path.size()) >= 3) && isAsciiLetter(doof::string_at(path, 0, "", 0))) && (doof::string_at(path, 1, "", 0) == U'\u003A')) && (doof::string_at(path, 2, "", 0) == U'\u002F')) {
#line 176 "/std/path/index.do"
        return doof::string_substring(path, 0, 2);
    }
#line 178 "/std/path/index.do"
    return std::string("");
}
#line 181 "/std/path/index.do"
bool isAsciiLetter(char32_t character) {
#line 182 "/std/path/index.do"
    return (((character >= U'\u0041') && (character <= U'\u005A')) || ((character >= U'\u0061') && (character <= U'\u007A')));
}
#line 185 "/std/path/index.do"
std::string renderPath(const std::shared_ptr<std::vector<std::string>>& segments, const std::string& prefix) {
#line 186 "/std/path/index.do"
    if (static_cast<int32_t>((segments)->size()) == 0) {
#line 187 "/std/path/index.do"
        return ((prefix == std::string("")) ? std::string(".") : ((prefix == std::string("/")) ? std::string("/") : (prefix + std::string("/"))));
    }
#line 190 "/std/path/index.do"
    auto output = doof::array_at(segments, 0, "index", 190);
#line 191 "/std/path/index.do"
    for (int32_t index = 1; index < static_cast<int32_t>((segments)->size()); ++index) {
#line 192 "/std/path/index.do"
        (output += (std::string("/") + doof::array_at(segments, index, "index", 192)));
    }
#line 194 "/std/path/index.do"
    if (prefix == std::string("/")) {
#line 195 "/std/path/index.do"
        return (std::string("/") + output);
    }
#line 197 "/std/path/index.do"
    if (prefix != std::string("")) {
#line 198 "/std/path/index.do"
        return ((prefix + std::string("/")) + output);
    }
#line 200 "/std/path/index.do"
    return output;
}
#line 203 "/std/path/index.do"
int32_t lastSeparatorIndex(const std::string& path) {
#line 204 "/std/path/index.do"
    auto index = (static_cast<int32_t>(path.size()) - 1);
#line 205 "/std/path/index.do"
    while (index >= 0) {
#line 206 "/std/path/index.do"
        if (doof::string_at(path, index, "", 0) == U'\u002F') {
#line 207 "/std/path/index.do"
            return index;
        }
#line 209 "/std/path/index.do"
        (index -= 1);
    }
#line 211 "/std/path/index.do"
    return -1;
}
#line 214 "/std/path/index.do"
int32_t lastDotIndex(const std::string& path) {
#line 215 "/std/path/index.do"
    auto index = (static_cast<int32_t>(path.size()) - 1);
#line 216 "/std/path/index.do"
    while (index >= 0) {
#line 217 "/std/path/index.do"
        if (doof::string_at(path, index, "", 0) == U'\u002E') {
#line 218 "/std/path/index.do"
            return index;
        }
#line 220 "/std/path/index.do"
        (index -= 1);
    }
#line 222 "/std/path/index.do"
    return -1;
}
#line 1 "<doof-generated>"
doof::Result<std::string, std::string> _homeDirectory() {
    return ::doof_path::homeDirectory();
}
std::string _tempDirectory() {
    return ::doof_path::tempDirectory();
}
doof::Result<std::string, std::string> _dataDirectory(const std::optional<std::string>& appId) {
    return ::doof_path::dataDirectory(appId);
}
doof::Result<std::string, std::string> _cacheDirectory(const std::optional<std::string>& appId) {
    return ::doof_path::cacheDirectory(appId);
}
doof::Result<std::string, std::string> _currentWorkingDirectory() {
    return ::doof_path::currentWorkingDirectory();
}
doof::Result<std::string, std::string> _absolute(const std::string& path) {
    return ::doof_path::absolute(path);
}
doof::Result<std::string, std::string> _resourcesDirectory() {
    return ::doof_path::resourcesDirectory();
}
}
