#include "std_fs_index.hpp"

namespace std_::fs::index {
using namespace ::std_::path::index;
using namespace ::std_::stream::index;
using namespace ::std_::fs::types;
#line 21 "/std/fs/index.do"
doof::Result<std::string, ::std_::fs::types::IoError> resolveResourcePath(const std::string& path) {
#line 22 "/std/fs/index.do"
    auto _binding_value_1 = ::std_::path::index::resourcePath(path);
    if (doof::is_failure(_binding_value_1)) {
        const auto& resolvedPath = _binding_value_1;
#line 23 "/std/fs/index.do"
        return doof::Failure<::std_::fs::types::IoError>{ ::std_::fs::types::IoError::InvalidPath };
    }
    const auto resolvedPath = doof::success_value(_binding_value_1);
#line 25 "/std/fs/index.do"
    return doof::Success<std::string>{ resolvedPath };
}
#line 28 "/std/fs/index.do"
doof::Result<std::string, ::std_::fs::types::IoError> readTextResource(const std::string& path) {
#line 29 "/std/fs/index.do"
    auto _try_value_2 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_2)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_2))};
    const auto resolved = doof::success_value(_try_value_2);
#line 30 "/std/fs/index.do"
    return ::doof_fs::readText(resolved);
}
#line 33 "/std/fs/index.do"
doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBlobResource(const std::string& path) {
#line 34 "/std/fs/index.do"
    auto _try_value_3 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_3)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_3))};
    const auto resolved = doof::success_value(_try_value_3);
#line 35 "/std/fs/index.do"
    return ::doof_fs::readBlob(resolved);
}
#line 50 "/std/fs/index.do"
int32_t normalizeStreamBlockSize(int32_t blockSize) {
#line 51 "/std/fs/index.do"
    if (blockSize > 0) {
#line 52 "/std/fs/index.do"
        return blockSize;
    }
#line 55 "/std/fs/index.do"
    return 65536;
}

#line 62 "/std/fs/index.do"
bool BlockReadStream::next() {
#line 63 "/std/fs/index.do"
    const auto chunk = this->native->next();
#line 64 "/std/fs/index.do"
    if (doof::is_null(chunk)) {
#line 65 "/std/fs/index.do"
        return false;
    }
#line 67 "/std/fs/index.do"
    (this->currentValue = doof::unwrap_optional(chunk));
#line 68 "/std/fs/index.do"
    return true;
}
#line 71 "/std/fs/index.do"
std::shared_ptr<std::vector<uint8_t>> BlockReadStream::value() {
    return this->currentValue;
}
#line 74 "/std/fs/index.do"
doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readBlockStream(const std::string& path, int32_t blockSize) {
#line 75 "/std/fs/index.do"
    auto _try_value_4 = ::NativeBlobReadStream::open(path, normalizeStreamBlockSize(blockSize));
    if (doof::is_failure(_try_value_4)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_4))};
    const auto native = doof::success_value(_try_value_4);
#line 76 "/std/fs/index.do"
    return doof::Success<Stream__readonly_array_byte>{ std::make_shared<BlockReadStream>(native, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{})) };
}
#line 81 "/std/fs/index.do"
doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readBlobStream(const std::string& path, int32_t blockSize) {
#line 82 "/std/fs/index.do"
    return readBlockStream(path, blockSize);
}
#line 85 "/std/fs/index.do"
doof::Result<Stream__string, ::std_::fs::types::IoError> readLineStream(const std::string& path, int32_t blockSize) {
#line 86 "/std/fs/index.do"
    auto _try_value_5 = readBlockStream(path, blockSize);
    if (doof::is_failure(_try_value_5)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_5))};
    const auto blocks = doof::success_value(_try_value_5);
#line 87 "/std/fs/index.do"
    return doof::Success<Stream__string>{ ::std_::stream::index::blobStreamToLineStream(blocks) };
}
#line 90 "/std/fs/index.do"
doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readResourceBlockStream(const std::string& path, int32_t blockSize) {
#line 91 "/std/fs/index.do"
    auto _try_value_6 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_6)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_6))};
    const auto resolved = doof::success_value(_try_value_6);
#line 92 "/std/fs/index.do"
    return readBlockStream(resolved, blockSize);
}
#line 95 "/std/fs/index.do"
doof::Result<Stream__readonly_array_byte, ::std_::fs::types::IoError> readResourceBlobStream(const std::string& path, int32_t blockSize) {
#line 96 "/std/fs/index.do"
    return readResourceBlockStream(path, blockSize);
}
#line 99 "/std/fs/index.do"
doof::Result<Stream__string, ::std_::fs::types::IoError> readResourceLineStream(const std::string& path, int32_t blockSize) {
#line 100 "/std/fs/index.do"
    auto _try_value_7 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_7)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_7))};
    const auto resolved = doof::success_value(_try_value_7);
#line 101 "/std/fs/index.do"
    return readLineStream(resolved, blockSize);
}
#line 104 "/std/fs/index.do"
doof::Result<void, ::std_::fs::types::IoError> writeBlobStream(const std::string& path, const Stream__readonly_array_byte& chunks) {
#line 105 "/std/fs/index.do"
    auto _try_value_8 = ::NativeFileWriteStream::open(path);
    if (doof::is_failure(_try_value_8)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_8))};
    const auto writer = doof::success_value(_try_value_8);
#line 106 "/std/fs/index.do"
    const auto& _iterable_10 = chunks;
    while (std::visit([](auto&& _obj) { return _obj->next(); }, _iterable_10)) {
        const auto chunk = std::visit([](auto&& _obj) { return _obj->value(); }, _iterable_10);
#line 107 "/std/fs/index.do"
        auto _try_value_11 = writer->writeBlob(chunk);
        if (doof::is_failure(_try_value_11)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_11))};
    }
#line 109 "/std/fs/index.do"
    auto _try_value_12 = writer->close();
    if (doof::is_failure(_try_value_12)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_12))};
#line 110 "/std/fs/index.do"
    return doof::Success<void>{};
}
#line 113 "/std/fs/index.do"
doof::Result<void, ::std_::fs::types::IoError> writeLineStream(const std::string& path, const Stream__string& lines) {
#line 114 "/std/fs/index.do"
    auto _try_value_13 = ::NativeFileWriteStream::open(path);
    if (doof::is_failure(_try_value_13)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_13))};
    const auto writer = doof::success_value(_try_value_13);
#line 115 "/std/fs/index.do"
    const auto& _iterable_15 = lines;
    while (std::visit([](auto&& _obj) { return _obj->next(); }, _iterable_15)) {
        const auto line = std::visit([](auto&& _obj) { return _obj->value(); }, _iterable_15);
#line 116 "/std/fs/index.do"
        auto _try_value_16 = writer->writeLine(line);
        if (doof::is_failure(_try_value_16)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_16))};
    }
#line 118 "/std/fs/index.do"
    auto _try_value_17 = writer->close();
    if (doof::is_failure(_try_value_17)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_17))};
#line 119 "/std/fs/index.do"
    return doof::Success<void>{};
}
#line 127 "/std/fs/index.do"
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>>, ::std_::fs::types::IoError> readResourceDir(const std::string& path) {
#line 128 "/std/fs/index.do"
    auto _try_value_18 = resolveResourcePath(path);
    if (doof::is_failure(_try_value_18)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_18))};
    const auto resolved = doof::success_value(_try_value_18);
#line 129 "/std/fs/index.do"
    return ::doof_fs::readDir(resolved);
}
#line 1 "<doof-generated>"
bool exists(const std::string& path) {
    return ::doof_fs::exists(path);
}
doof::Result<std::string, ::std_::fs::types::IoError> readText(const std::string& path) {
    return ::doof_fs::readText(path);
}
doof::Result<void, ::std_::fs::types::IoError> mkdir(const std::string& path) {
    return ::doof_fs::mkdir(path);
}
bool isDirectory(const std::string& path) {
    return ::doof_fs::isDirectory(path);
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::fs::types::FileInfo>>>, ::std_::fs::types::IoError> readDir(const std::string& path) {
    return ::doof_fs::readDir(path);
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> readBlob(const std::string& path) {
    return ::doof_fs::readBlob(path);
}
doof::Result<void, ::std_::fs::types::IoError> writeText(const std::string& path, const std::string& content) {
    return ::doof_fs::writeText(path, content);
}
doof::Result<void, ::std_::fs::types::IoError> rename(const std::string& sourcePath, const std::string& destPath) {
    return ::doof_fs::rename(sourcePath, destPath);
}
doof::Result<void, ::std_::fs::types::IoError> remove(const std::string& path) {
    return ::doof_fs::remove(path);
}
doof::Result<void, ::std_::fs::types::IoError> writeBlob(const std::string& path, const std::shared_ptr<std::vector<uint8_t>>& data) {
    return ::doof_fs::writeBlob(path, data);
}
doof::Result<std::shared_ptr<::std_::fs::types::FileInfo>, ::std_::fs::types::IoError> metadata(const std::string& path) {
    return ::doof_fs::metadata(path);
}
bool isFile(const std::string& path) {
    return ::doof_fs::isFile(path);
}
}
