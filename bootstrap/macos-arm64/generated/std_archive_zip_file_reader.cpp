#include "std_archive_zip_file_reader.hpp"

namespace std_::archive::zip_file_reader {
using namespace ::std_::blob::index;
using namespace ::std_::archive::types;
using namespace ::std_::archive::reader;
int64_t ZIP_END_SEARCH_SIZE = 65557LL;
int64_t ZIP_LOCAL_HEADER_SIZE = 30LL;
int64_t MAX_BLOB_SIZE = 2147483647LL;
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>>, std::string> scanZipFile(const std::string& path) {
    auto _binding_value_1 = ::doof_archive::NativeArchiveFile::open(path);
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return doof::Failure<std::string>{ (std::string("zip file scan failed: ") + error) };
    }
    const auto file = doof::success_value(_binding_value_1);
    const auto fileSize = file->size();
    if (fileSize < 22LL) {
        return doof::Failure<std::string>{ std::string("zip read failed: input is too small") };
    }
    const auto tailSize = ((fileSize > ZIP_END_SEARCH_SIZE) ? ZIP_END_SEARCH_SIZE : fileSize);
    const auto tailOffset = (fileSize - tailSize);
    auto _binding_value_2 = file->read(tailOffset, tailSize);
    if (doof::is_failure(_binding_value_2)) {
        const auto error = doof::failure_error(_binding_value_2);
        return doof::Failure<std::string>{ (std::string("zip file scan failed: ") + error) };
    }
    const auto tail = doof::success_value(_binding_value_2);
    auto _try_value_3 = ::std_::archive::reader::findEndOfCentralDirectory(tail);
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_3))};
    const auto eocdOffset = doof::success_value(_try_value_3);
    auto _try_value_4 = ::std_::archive::reader::readZipDirectoryInfo(tail, eocdOffset, tailOffset, fileSize);
    if (doof::is_failure(_try_value_4)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_4))};
    const auto directory = doof::success_value(_try_value_4);
    if (directory->size > MAX_BLOB_SIZE) {
        return doof::Failure<std::string>{ std::string("zip file scan failed: central directory is too large") };
    }
    auto _binding_value_5 = file->read(directory->offset, directory->size);
    if (doof::is_failure(_binding_value_5)) {
        const auto error = doof::failure_error(_binding_value_5);
        return doof::Failure<std::string>{ (std::string("zip file scan failed: ") + error) };
    }
    const auto directoryBytes = doof::success_value(_binding_value_5);
    const auto reader = ::doof_blob::NativeBlobReader::constructor(directoryBytes, ::std_::blob::types::Endian::LittleEndian);
    std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>> entries = std::make_shared<std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>>(std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>{});
    for (int32_t index = 0; index < directory->entryCount; ++index) {
        auto _try_value_6 = ::std_::archive::reader::readCentralDirectoryEntry(reader);
        if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
        const auto entry = doof::success_value(_try_value_6);
        if (entry->localHeaderOffset > (fileSize - ZIP_LOCAL_HEADER_SIZE)) {
            return doof::Failure<std::string>{ (std::string("zip read failed: local file header is out of bounds for ") + entry->name) };
        }
        entries->push_back(entry);
    }
    if (reader->getPosition() > directory->size) {
        return doof::Failure<std::string>{ std::string("zip read failed: central directory entries exceed declared size") };
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>>>{ doof::array_drainToReadonly(entries, "", 0) };
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> readZipEntry(const std::string& path, const std::shared_ptr<::std_::archive::types::ZipFileEntry>& entry) {
    if ((entry->compressedSize > MAX_BLOB_SIZE) || (entry->size > MAX_BLOB_SIZE)) {
        return doof::Failure<std::string>{ std::string("zip entry read failed: entry is too large for a byte array") };
    }
    auto _binding_value_8 = ::doof_archive::NativeArchiveFile::open(path);
    if (doof::is_failure(_binding_value_8)) {
        const auto error = doof::failure_error(_binding_value_8);
        return doof::Failure<std::string>{ (std::string("zip entry read failed: ") + error) };
    }
    const auto file = doof::success_value(_binding_value_8);
    if ((entry->localHeaderOffset < 0LL) || (entry->localHeaderOffset > (file->size() - ZIP_LOCAL_HEADER_SIZE))) {
        return doof::Failure<std::string>{ std::string("zip entry read failed: local file header is out of bounds") };
    }
    auto _binding_value_9 = file->read(entry->localHeaderOffset, ZIP_LOCAL_HEADER_SIZE);
    if (doof::is_failure(_binding_value_9)) {
        const auto error = doof::failure_error(_binding_value_9);
        return doof::Failure<std::string>{ (std::string("zip entry read failed: ") + error) };
    }
    const auto header = doof::success_value(_binding_value_9);
    auto _binding_value_10 = ::std_::archive::reader::zipPayloadOffset(header, entry->localHeaderOffset);
    if (doof::is_failure(_binding_value_10)) {
        const auto error = doof::failure_error(_binding_value_10);
        return doof::Failure<std::string>{ (std::string("zip entry read failed: ") + error) };
    }
    const auto payloadOffset = doof::success_value(_binding_value_10);
    auto _binding_value_11 = file->read(payloadOffset, entry->compressedSize);
    if (doof::is_failure(_binding_value_11)) {
        const auto error = doof::failure_error(_binding_value_11);
        return doof::Failure<std::string>{ (std::string("zip entry read failed: ") + error) };
    }
    const auto compressed = doof::success_value(_binding_value_11);
    auto _binding_value_12 = ::std_::archive::reader::unpackZipPayload(compressed, entry->compression);
    if (doof::is_failure(_binding_value_12)) {
        const auto error = doof::failure_error(_binding_value_12);
        return doof::Failure<std::string>{ (std::string("zip entry read failed: ") + error) };
    }
    const auto payload = doof::success_value(_binding_value_12);
    auto _binding_value_13 = ::std_::archive::reader::validateZipPayload(payload, entry);
    if (doof::is_failure(_binding_value_13)) {
        const auto error = doof::failure_error(_binding_value_13);
        return doof::Failure<std::string>{ (std::string("zip entry read failed: ") + error) };
    }
    return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ payload };
}
}
