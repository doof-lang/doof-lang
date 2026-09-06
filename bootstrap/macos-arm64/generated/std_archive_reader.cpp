#include "std_archive_reader.hpp"

namespace std_::archive::reader {
using namespace ::std_::blob::index;
using namespace ::std_::gzip::index;
using namespace ::std_::archive::types;
int64_t LOCAL_FILE_HEADER_SIGNATURE = 67324752LL;
int64_t CENTRAL_DIRECTORY_SIGNATURE = 33639248LL;
int64_t END_OF_CENTRAL_DIRECTORY_SIGNATURE = 101010256LL;
::std_::archive::types::ArchiveEntryKind entryKindForName(const std::string& name) {
    if ((static_cast<int32_t>(name.size()) > 0) && (doof::string_slice(name, (static_cast<int32_t>(name.size()) - 1)) == std::string("/"))) {
        return ::std_::archive::types::ArchiveEntryKind::Directory;
    }
    return ::std_::archive::types::ArchiveEntryKind::File;
}

doof::Result<void, std::string> requireRemaining(const std::shared_ptr<::doof_blob::NativeBlobReader>& reader, int64_t length, const std::string& context) {
    if (reader->remaining() < length) {
        return doof::Failure<std::string>{ (std::string("zip read failed: truncated ") + context) };
    }
    return doof::Success<void>{};
}
doof::Result<::std_::archive::types::ZipCompression, std::string> readCompression(int32_t method) {
    if (method == ::std_::archive::types::ZipCompression_value(::std_::archive::types::ZipCompression::Store)) {
        return doof::Success<::std_::archive::types::ZipCompression>{ ::std_::archive::types::ZipCompression::Store };
    }
    if (method == ::std_::archive::types::ZipCompression_value(::std_::archive::types::ZipCompression::Deflate)) {
        return doof::Success<::std_::archive::types::ZipCompression>{ ::std_::archive::types::ZipCompression::Deflate };
    }
    return doof::Failure<std::string>{ (std::string("zip read failed: unsupported compression method ") + doof::to_string(method)) };
}
doof::Result<std::shared_ptr<::std_::archive::types::ZipFileEntry>, std::string> readCentralDirectoryEntry(const std::shared_ptr<::doof_blob::NativeBlobReader>& reader) {
    auto _try_value_1 = requireRemaining(reader, 46LL, std::string("central directory entry"));
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
    const auto signature = reader->readUnsignedInt();
    if (signature != CENTRAL_DIRECTORY_SIGNATURE) {
        return doof::Failure<std::string>{ std::string("zip read failed: invalid central directory signature") };
    }
    reader->skip(4LL);
    const auto flags = reader->readUnsignedShort();
    const auto method = reader->readUnsignedShort();
    reader->skip(4LL);
    const auto crc = reader->readUnsignedInt();
    const auto compressedSize = reader->readUnsignedInt();
    const auto size = reader->readUnsignedInt();
    const auto nameLength = reader->readUnsignedShort();
    const auto extraLength = reader->readUnsignedShort();
    const auto commentLength = reader->readUnsignedShort();
    reader->skip(8LL);
    const auto localHeaderOffset = reader->readUnsignedInt();
    auto _try_value_2 = requireRemaining(reader, static_cast<int64_t>(((nameLength + extraLength) + commentLength)), std::string("central directory entry payload"));
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_2))};
    const auto name = reader->readString(static_cast<int64_t>(nameLength));
    reader->skip(static_cast<int64_t>((extraLength + commentLength)));
    if ((flags & 8) != 0) {
        return doof::Failure<std::string>{ std::string("zip read failed: data descriptors are not supported") };
    }
    auto _try_value_3 = readCompression(method);
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_3))};
    const auto compression = doof::success_value(_try_value_3);
    return doof::Success<std::shared_ptr<::std_::archive::types::ZipFileEntry>>{ std::make_shared<::std_::archive::types::ZipFileEntry>(name, entryKindForName(name), size, compressedSize, crc, compression, localHeaderOffset) };
}
doof::Result<int64_t, std::string> findEndOfCentralDirectory(const std::shared_ptr<std::vector<uint8_t>>& data) {
    if (static_cast<int32_t>((data)->size()) < 22) {
        return doof::Failure<std::string>{ std::string("zip read failed: input is too small") };
    }
    const auto lastStart = (static_cast<int32_t>((data)->size()) - 22);
    const auto lowerBound = ((static_cast<int32_t>((data)->size()) > 65557) ? (static_cast<int32_t>((data)->size()) - 65557) : 0);
    for (int32_t distance = 0; distance < ((lastStart - lowerBound) + 1); ++distance) {
        const auto index = (lastStart - distance);
        if ((((doof::array_at(data, index, "reader", 88) == 80) && (doof::array_at(data, (index + 1), "reader", 88) == 75)) && (doof::array_at(data, (index + 2), "reader", 88) == 5)) && (doof::array_at(data, (index + 3), "reader", 88) == 6)) {
            const auto commentLength = (static_cast<int32_t>(doof::array_at(data, (index + 20), "reader", 89)) + (static_cast<int32_t>(doof::array_at(data, (index + 21), "reader", 89)) * 256));
            if (((index + 22) + commentLength) == static_cast<int32_t>((data)->size())) {
                return doof::Success<int64_t>{ static_cast<int64_t>(index) };
            }
        }
    }
    return doof::Failure<std::string>{ std::string("zip read failed: end of central directory not found") };
}
doof::Result<std::shared_ptr<ZipDirectoryInfo>, std::string> readZipDirectoryInfo(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t eocdOffset, int64_t dataOffset, int64_t archiveSize) {
    const auto reader = ::doof_blob::NativeBlobReader::constructor(data, ::std_::blob::types::Endian::LittleEndian);
    reader->setPosition(eocdOffset);
    auto _try_value_5 = requireRemaining(reader, 22LL, std::string("end of central directory"));
    if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_5))};
    const auto signature = reader->readUnsignedInt();
    if (signature != END_OF_CENTRAL_DIRECTORY_SIGNATURE) {
        return doof::Failure<std::string>{ std::string("zip read failed: invalid end of central directory signature") };
    }
    const auto diskNumber = reader->readUnsignedShort();
    const auto centralDirectoryDisk = reader->readUnsignedShort();
    const auto diskEntryCount = reader->readUnsignedShort();
    const auto entryCount = reader->readUnsignedShort();
    const auto centralDirectorySize = reader->readUnsignedInt();
    const auto centralDirectoryOffset = reader->readUnsignedInt();
    const auto commentLength = reader->readUnsignedShort();
    if (((diskNumber != 0) || (centralDirectoryDisk != 0)) || (diskEntryCount != entryCount)) {
        return doof::Failure<std::string>{ std::string("zip read failed: multi-disk archives are not supported") };
    }
    if ((((eocdOffset + 22LL) + static_cast<int64_t>(commentLength)) != static_cast<int64_t>(static_cast<int32_t>((data)->size()))) || ((((dataOffset + eocdOffset) + 22LL) + static_cast<int64_t>(commentLength)) != archiveSize)) {
        return doof::Failure<std::string>{ std::string("zip read failed: truncated archive comment") };
    }
    const auto absoluteEocdOffset = (dataOffset + eocdOffset);
    if ((centralDirectoryOffset + centralDirectorySize) > absoluteEocdOffset) {
        return doof::Failure<std::string>{ std::string("zip read failed: central directory is out of bounds") };
    }
    return doof::Success<std::shared_ptr<ZipDirectoryInfo>>{ std::make_shared<ZipDirectoryInfo>(entryCount, centralDirectoryOffset, centralDirectorySize) };
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> unpackZipPayload(const std::shared_ptr<std::vector<uint8_t>>& compressed, ::std_::archive::types::ZipCompression compression) {
    if (compression == ::std_::archive::types::ZipCompression::Store) {
        return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ compressed };
    }
    return ::doof_gzip::inflateRaw(compressed);
}
doof::Result<int64_t, std::string> zipPayloadOffset(const std::shared_ptr<std::vector<uint8_t>>& header, int64_t localHeaderOffset) {
    const auto reader = ::doof_blob::NativeBlobReader::constructor(header, ::std_::blob::types::Endian::LittleEndian);
    auto _try_value_6 = requireRemaining(reader, 30LL, std::string("local file header"));
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
    const auto signature = reader->readUnsignedInt();
    if (signature != LOCAL_FILE_HEADER_SIGNATURE) {
        return doof::Failure<std::string>{ std::string("zip read failed: invalid local file header signature") };
    }
    reader->skip(22LL);
    const auto nameLength = reader->readUnsignedShort();
    const auto extraLength = reader->readUnsignedShort();
    return doof::Success<int64_t>{ ((localHeaderOffset + 30LL) + static_cast<int64_t>((nameLength + extraLength))) };
}
doof::Result<void, std::string> validateZipPayload(const std::shared_ptr<std::vector<uint8_t>>& payload, const std::shared_ptr<::std_::archive::types::ZipFileEntry>& central) {
    if (static_cast<int64_t>(static_cast<int32_t>((payload)->size())) != central->size) {
        return doof::Failure<std::string>{ (std::string("zip read failed: uncompressed size mismatch for ") + central->name) };
    }
    if (::doof_gzip::crc32Bytes(payload) != central->crc32) {
        return doof::Failure<std::string>{ (std::string("zip read failed: crc mismatch for ") + central->name) };
    }
    return doof::Success<void>{};
}
doof::Result<std::shared_ptr<::std_::archive::types::ZipEntry>, std::string> readEntryPayload(const std::shared_ptr<std::vector<uint8_t>>& data, const std::shared_ptr<::std_::archive::types::ZipFileEntry>& central) {
    if (central->localHeaderOffset > (static_cast<int64_t>(static_cast<int32_t>((data)->size())) - 30LL)) {
        return doof::Failure<std::string>{ std::string("zip read failed: truncated local file header") };
    }
    const auto header = doof::array_slice(data, static_cast<int32_t>(central->localHeaderOffset), static_cast<int32_t>((central->localHeaderOffset + 30LL)), "", 0);
    auto _try_value_7 = zipPayloadOffset(header, central->localHeaderOffset);
    if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_7))};
    const auto payloadOffset = doof::success_value(_try_value_7);
    const auto payloadEnd = (payloadOffset + central->compressedSize);
    if (payloadEnd > static_cast<int64_t>(static_cast<int32_t>((data)->size()))) {
        return doof::Failure<std::string>{ std::string("zip read failed: truncated entry payload") };
    }
    const auto compressed = doof::array_slice(data, static_cast<int32_t>(payloadOffset), static_cast<int32_t>(payloadEnd), "", 0);
    auto _try_value_8 = unpackZipPayload(compressed, central->compression);
    if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
    const auto payload = doof::success_value(_try_value_8);
    auto _try_value_9 = validateZipPayload(payload, central);
    if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
    return doof::Success<std::shared_ptr<::std_::archive::types::ZipEntry>>{ std::make_shared<::std_::archive::types::ZipEntry>(central->name, central->kind, central->size, central->compressedSize, central->crc32, central->compression, payload) };
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipEntry>>>, std::string> readZip(const std::shared_ptr<std::vector<uint8_t>>& data) {
    auto _try_value_10 = findEndOfCentralDirectory(data);
    if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_10))};
    const auto eocdOffset = doof::success_value(_try_value_10);
    auto _try_value_11 = readZipDirectoryInfo(data, eocdOffset, 0LL, static_cast<int64_t>(static_cast<int32_t>((data)->size())));
    if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_11))};
    const auto directory = doof::success_value(_try_value_11);
    const auto reader = ::doof_blob::NativeBlobReader::constructor(data, ::std_::blob::types::Endian::LittleEndian);
    reader->setPosition(directory->offset);
    std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>> centralEntries = std::make_shared<std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>>(std::vector<std::shared_ptr<::std_::archive::types::ZipFileEntry>>{});
    for (int32_t index = 0; index < directory->entryCount; ++index) {
        auto _try_value_12 = readCentralDirectoryEntry(reader);
        if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
        const auto entry = doof::success_value(_try_value_12);
        centralEntries->push_back(entry);
    }
    if (reader->getPosition() > (directory->offset + directory->size)) {
        return doof::Failure<std::string>{ std::string("zip read failed: central directory entries exceed declared size") };
    }
    std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipEntry>>> entries = std::make_shared<std::vector<std::shared_ptr<::std_::archive::types::ZipEntry>>>(std::vector<std::shared_ptr<::std_::archive::types::ZipEntry>>{});
    const auto& _iterable_16 = centralEntries;
    for (const auto& entry : *_iterable_16) {
        auto _try_value_14 = readEntryPayload(data, entry);
        if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
        const auto payload = doof::success_value(_try_value_14);
        entries->push_back(payload);
    }
    return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipEntry>>>>{ entries };
}
}
