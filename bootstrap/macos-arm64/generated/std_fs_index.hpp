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
namespace std_::fs::types { enum class IoError; }
namespace std_::fs::types { struct FileInfo; }
namespace std_::fs::types { enum class EntryKind; }
namespace std_::time::temporal { struct Instant; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }
namespace std_::stream::index { struct DecodedLineStream; }

namespace std_::fs::index {
    struct BlockReadStream;
}

#include "std_path_index.hpp"
#include "std_stream_index.hpp"
#include "std_fs_types.hpp"

namespace doof_fs { using IoError = ::std_::fs::types::IoError; }
using IoError = ::std_::fs::types::IoError;
namespace doof_fs { using FileInfo = ::std_::fs::types::FileInfo; }
namespace doof_fs { using ::std_::path::index::resourcePath; }
namespace doof_fs { using ::std_::stream::index::blobStreamToLineStream; }
namespace doof_fs { using EntryKind = ::std_::fs::types::EntryKind; }
namespace doof_fs { using Instant = ::std_::time::temporal::Instant; }
#include "native_fs.hpp"

namespace std_::fs::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<::std_::stream::index::DecodedLineStream>>;
    bool exists(std::string path);
    doof::Result<std::string, ::std_::fs::types::IoError> readText(std::string path);
    doof::Result<void, ::std_::fs::types::IoError> mkdir(std::string path);
    bool isDirectory(std::string path);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>>, ::std_::fs::types::IoError> readDir(std::string path);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBlob(std::string path);
    doof::Result<void, ::std_::fs::types::IoError> writeBlob(std::string path, std::shared_ptr<std::vector<uint8_t>> data);
    doof::Result<void, ::std_::fs::types::IoError> writeText(std::string path, std::string content);
    doof::Result<void, ::std_::fs::types::IoError> remove(std::string path);
    doof::Result<void, ::std_::fs::types::IoError> rename(std::string sourcePath, std::string destPath);
    bool isFile(std::string path);
    struct BlockReadStream : public std::enable_shared_from_this<BlockReadStream> {
    std::shared_ptr<::NativeBlobReadStream> native;
    std::shared_ptr<std::vector<uint8_t>> currentValue = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    BlockReadStream(std::shared_ptr<::NativeBlobReadStream> native, std::shared_ptr<std::vector<uint8_t>> currentValue = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{})) : native(native), currentValue(currentValue) {}
    bool next();
    std::shared_ptr<std::vector<uint8_t>> value();
};
    doof::Result<std::string, ::std_::fs::types::IoError> resolveResourcePath(std::string path);
    doof::Result<std::string, ::std_::fs::types::IoError> readTextResource(std::string path);
    doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBlobResource(std::string path);
    int32_t normalizeStreamBlockSize(int32_t blockSize);
    doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readBlockStream(std::string path, int32_t blockSize = 65536);
    doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readBlobStream(std::string path, int32_t blockSize = 65536);
    doof::Result<Stream__string, ::std_::fs::types::IoError> readLineStream(std::string path, int32_t blockSize = 65536);
    doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readResourceBlockStream(std::string path, int32_t blockSize = 65536);
    doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readResourceBlobStream(std::string path, int32_t blockSize = 65536);
    doof::Result<Stream__string, ::std_::fs::types::IoError> readResourceLineStream(std::string path, int32_t blockSize = 65536);
    doof::Result<void, ::std_::fs::types::IoError> writeBlobStream(std::string path, Stream__readonly_array_byte chunks);
    doof::Result<void, ::std_::fs::types::IoError> writeLineStream(std::string path, Stream__string lines);
    doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>>, ::std_::fs::types::IoError> readResourceDir(std::string path);
}

namespace std_::fs::index {
}
