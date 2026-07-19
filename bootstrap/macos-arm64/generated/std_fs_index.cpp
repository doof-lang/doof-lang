#include "std_fs_index.hpp"
#include <cmath>
#include "std_path_index.hpp"
#include "std_stream_index.hpp"
#include "std_fs_types.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"

namespace std_::fs::index {
using namespace ::std_::path::index;
using namespace ::std_::stream::index;
using namespace ::std_::fs::types;
doof::Result<std::string, ::std_::fs::types::IoError> resolveResourcePath(std::string path) {
    auto _binding_value_1 = ::std_::path::index::resourcePath(path);
    if (doof::is_failure(_binding_value_1)) {
        const auto& resolvedPath = _binding_value_1;
        return doof::Failure<::std_::fs::types::IoError>{ ::std_::fs::types::IoError::InvalidPath };
    }
    const auto resolvedPath = doof::success_value(_binding_value_1);
    return doof::Success<std::string>{ resolvedPath };
}
doof::Result<std::string, ::std_::fs::types::IoError> readTextResource(std::string path) {
    auto _try_value_2 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_2)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_2)};
    const auto resolved = doof::success_value(_try_value_2);
    return readText(resolved);
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBlobResource(std::string path) {
    auto _try_value_3 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_3)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_3)};
    const auto resolved = doof::success_value(_try_value_3);
    return readBlob(resolved);
}
int32_t normalizeStreamBlockSize(int32_t blockSize) {
    if (blockSize > 0) {
        return blockSize;
    }
    return 65536;
}

bool BlockReadStream::next() {
    const auto chunk = this->native->next();
    if (doof::is_null(chunk)) {
        return false;
    }
    (this->currentValue = doof::unwrap_optional(chunk));
    return true;
}
std::shared_ptr<std::vector<uint8_t>> BlockReadStream::value() {
    return this->currentValue;
}
doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readBlockStream(std::string path, int32_t blockSize) {
    auto _try_value_4 = ::NativeBlobReadStream::open(path, normalizeStreamBlockSize(blockSize));
    if (doof::is_failure(_try_value_4)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_4)};
    const auto native = doof::success_value(_try_value_4);
    return doof::Success<Stream__readonly_array_byte>{ std::make_shared<BlockReadStream>(native, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{})) };
}
doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readBlobStream(std::string path, int32_t blockSize) {
    return readBlockStream(path, blockSize);
}
doof::Result<Stream__string, ::std_::fs::types::IoError> readLineStream(std::string path, int32_t blockSize) {
    auto _try_value_5 = readBlockStream(path, blockSize);
    if (doof::is_failure(_try_value_5)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_5)};
    const auto blocks = doof::success_value(_try_value_5);
    return doof::Success<Stream__string>{ ::std_::stream::index::blobStreamToLineStream(blocks) };
}
doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readResourceBlockStream(std::string path, int32_t blockSize) {
    auto _try_value_6 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_6)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_6)};
    const auto resolved = doof::success_value(_try_value_6);
    return readBlockStream(resolved, blockSize);
}
doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readResourceBlobStream(std::string path, int32_t blockSize) {
    return readResourceBlockStream(path, blockSize);
}
doof::Result<Stream__string, ::std_::fs::types::IoError> readResourceLineStream(std::string path, int32_t blockSize) {
    auto _try_value_7 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_7)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_7)};
    const auto resolved = doof::success_value(_try_value_7);
    return readLineStream(resolved, blockSize);
}
doof::Result<void, ::std_::fs::types::IoError> writeBlobStream(std::string path, Stream__readonly_array_byte chunks) {
    auto _try_value_8 = ::NativeFileWriteStream::open(path);
    if (doof::is_failure(_try_value_8)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_8)};
    const auto writer = doof::success_value(_try_value_8);
    const auto& _iterable_9 = chunks;
    while (std::visit([](auto&& _obj) { return _obj->next(); }, _iterable_9)) {
        const auto chunk = std::visit([](auto&& _obj) { return _obj->value(); }, _iterable_9);
        auto _try_value_10 = writer->writeBlob(chunk);
        if (doof::is_failure(_try_value_10)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_10)};
    }
    auto _try_value_11 = writer->close();
    if (doof::is_failure(_try_value_11)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_11)};
    return doof::Success<void>{};
}
doof::Result<void, ::std_::fs::types::IoError> writeLineStream(std::string path, Stream__string lines) {
    auto _try_value_12 = ::NativeFileWriteStream::open(path);
    if (doof::is_failure(_try_value_12)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_12)};
    const auto writer = doof::success_value(_try_value_12);
    const auto& _iterable_13 = lines;
    while (std::visit([](auto&& _obj) { return _obj->next(); }, _iterable_13)) {
        const auto line = std::visit([](auto&& _obj) { return _obj->value(); }, _iterable_13);
        auto _try_value_14 = writer->writeLine(line);
        if (doof::is_failure(_try_value_14)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_14)};
    }
    auto _try_value_15 = writer->close();
    if (doof::is_failure(_try_value_15)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_15)};
    return doof::Success<void>{};
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>>, ::std_::fs::types::IoError> readResourceDir(std::string path) {
    auto _try_value_16 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_16)) return doof::Failure<::std_::fs::types::IoError>{doof::failure_error(_try_value_16)};
    const auto resolved = doof::success_value(_try_value_16);
    return readDir(resolved);
}
bool exists(std::string path) {
    return ::doof_fs::exists(path);
}
doof::Result<std::string, ::std_::fs::types::IoError> readText(std::string path) {
    return ::doof_fs::readText(path);
}
doof::Result<void, ::std_::fs::types::IoError> mkdir(std::string path) {
    return ::doof_fs::mkdir(path);
}
bool isDirectory(std::string path) {
    return ::doof_fs::isDirectory(path);
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>>, ::std_::fs::types::IoError> readDir(std::string path) {
    return ::doof_fs::readDir(path);
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBlob(std::string path) {
    return ::doof_fs::readBlob(path);
}
doof::Result<void, ::std_::fs::types::IoError> writeBlob(std::string path, std::shared_ptr<std::vector<uint8_t>> data) {
    return ::doof_fs::writeBlob(path, data);
}
doof::Result<void, ::std_::fs::types::IoError> writeText(std::string path, std::string content) {
    return ::doof_fs::writeText(path, content);
}
doof::Result<void, ::std_::fs::types::IoError> remove(std::string path) {
    return ::doof_fs::remove(path);
}
doof::Result<void, ::std_::fs::types::IoError> rename(std::string sourcePath, std::string destPath) {
    return ::doof_fs::rename(sourcePath, destPath);
}
bool isFile(std::string path) {
    return ::doof_fs::isFile(path);
}
}
