#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::path::index {
}

#include "native_path.hpp"

namespace std_::path::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    doof::Result<std::string, std::string> _homeDirectory();
    std::string _tempDirectory();
    doof::Result<std::string, std::string> _dataDirectory(std::optional<std::string> appId = std::nullopt);
    doof::Result<std::string, std::string> _cacheDirectory(std::optional<std::string> appId = std::nullopt);
    doof::Result<std::string, std::string> _currentWorkingDirectory();
    doof::Result<std::string, std::string> _absolute(std::string path);
    doof::Result<std::string, std::string> _resourcesDirectory();
    doof::Result<std::string, std::string> normalizePathResult(doof::Result<std::string, std::string> result);
    doof::Result<std::string, std::string> homeDirectory();
    std::string tempDirectory();
    doof::Result<std::string, std::string> dataDirectory(std::optional<std::string> appId = std::nullopt);
    doof::Result<std::string, std::string> cacheDirectory(std::optional<std::string> appId = std::nullopt);
    doof::Result<std::string, std::string> currentWorkingDirectory();
    doof::Result<std::string, std::string> absolute(std::string path);
    doof::Result<std::string, std::string> resourcesDirectory();
    doof::Result<std::string, std::string> resourcePath(std::string path);
    std::string join(std::shared_ptr<std::vector<std::string>> parts);
    std::string dirname(std::string path);
    std::string basename(std::string path);
    std::string stem(std::string path);
    std::string extension(std::string path);
    bool isAbsolute(std::string path);
    std::string renderPath(std::shared_ptr<std::vector<std::string>> segments, bool absolute);
    int32_t lastSeparatorIndex(std::string path);
    int32_t lastDotIndex(std::string path);
}

namespace std_::path::index {
}
