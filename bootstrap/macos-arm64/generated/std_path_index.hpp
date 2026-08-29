#pragma once
#include "doof_runtime.hpp"
#include "native_path.hpp"

namespace std_::path::index {
    doof::Result<std::string, std::string> normalizePathResult(const doof::Result<std::string, std::string>& result);
    doof::Result<std::string, std::string> homeDirectory();
    std::string tempDirectory();
    doof::Result<std::string, std::string> dataDirectory(const std::optional<std::string>& appId);
    doof::Result<std::string, std::string> cacheDirectory(const std::optional<std::string>& appId);
    doof::Result<std::string, std::string> currentWorkingDirectory();
    doof::Result<std::string, std::string> absolute(const std::string& path);
    doof::Result<std::string, std::string> resourcesDirectory();
    doof::Result<std::string, std::string> resourcePath(const std::string& path);
    std::string join(const std::shared_ptr<std::vector<std::string>>& parts);
    std::string dirname(const std::string& path);
    std::string basename(const std::string& path);
    std::string stem(const std::string& path);
    std::string extension(const std::string& path);
    bool isAbsolute(const std::string& path);
    std::string rootPrefix(const std::string& path);
    bool isAsciiLetter(char32_t character);
    std::string renderPath(const std::shared_ptr<std::vector<std::string>>& segments, const std::string& prefix);
    int32_t lastSeparatorIndex(const std::string& path);
    int32_t lastDotIndex(const std::string& path);
}
