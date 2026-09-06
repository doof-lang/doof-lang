#include "std_archive_writer.hpp"

namespace std_::archive::writer {
using namespace ::std_::blob::index;
using namespace ::std_::gzip::index;
using namespace ::std_::archive::types;
int64_t LOCAL_FILE_HEADER_SIGNATURE = 67324752LL;
int64_t CENTRAL_DIRECTORY_SIGNATURE = 33639248LL;
int64_t END_OF_CENTRAL_DIRECTORY_SIGNATURE = 101010256LL;
int32_t ZIP_VERSION_NEEDED = 20;
int32_t ZIP_VERSION_MADE_BY = 20;
int32_t ZIP_UTF8_FLAG = 2048;
std::shared_ptr<std::vector<uint8_t>> encodedName(const std::string& name) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeString(name);
    return builder->build();
}
void writeLocalHeader(const std::shared_ptr<::doof_blob::NativeBlobBuilder>& builder, const std::shared_ptr<::std_::archive::types::ZipEntry>& entry, const std::shared_ptr<std::vector<uint8_t>>& nameBytes, const std::shared_ptr<std::vector<uint8_t>>& compressed) {
    builder->writeUnsignedInt(LOCAL_FILE_HEADER_SIGNATURE);
    builder->writeUnsignedShort(ZIP_VERSION_NEEDED);
    builder->writeUnsignedShort(ZIP_UTF8_FLAG);
    builder->writeUnsignedShort(::std_::archive::types::ZipCompression_value(entry->compression));
    builder->writeUnsignedShort(0);
    builder->writeUnsignedShort(0);
    builder->writeUnsignedInt(entry->crc32);
    builder->writeUnsignedInt(static_cast<int64_t>(static_cast<int32_t>((compressed)->size())));
    builder->writeUnsignedInt(static_cast<int64_t>(static_cast<int32_t>((entry->data)->size())));
    builder->writeUnsignedShort(static_cast<int32_t>((nameBytes)->size()));
    builder->writeUnsignedShort(0);
    builder->writeBytes(nameBytes);
}
void writeCentralHeader(const std::shared_ptr<::doof_blob::NativeBlobBuilder>& builder, const std::shared_ptr<::std_::archive::types::ZipEntry>& entry, const std::shared_ptr<std::vector<uint8_t>>& nameBytes, int64_t localHeaderOffset) {
    builder->writeUnsignedInt(CENTRAL_DIRECTORY_SIGNATURE);
    builder->writeUnsignedShort(ZIP_VERSION_MADE_BY);
    builder->writeUnsignedShort(ZIP_VERSION_NEEDED);
    builder->writeUnsignedShort(ZIP_UTF8_FLAG);
    builder->writeUnsignedShort(::std_::archive::types::ZipCompression_value(entry->compression));
    builder->writeUnsignedShort(0);
    builder->writeUnsignedShort(0);
    builder->writeUnsignedInt(entry->crc32);
    builder->writeUnsignedInt(entry->compressedSize);
    builder->writeUnsignedInt(static_cast<int64_t>(static_cast<int32_t>((entry->data)->size())));
    builder->writeUnsignedShort(static_cast<int32_t>((nameBytes)->size()));
    builder->writeUnsignedShort(0);
    builder->writeUnsignedShort(0);
    builder->writeUnsignedShort(0);
    builder->writeUnsignedShort(0);
    builder->writeUnsignedInt(0LL);
    builder->writeUnsignedInt(localHeaderOffset);
    builder->writeBytes(nameBytes);
}
std::shared_ptr<std::vector<uint8_t>> compressEntry(const std::shared_ptr<::std_::archive::types::ZipEntry>& entry) {
    if ((entry->kind == ::std_::archive::types::ArchiveEntryKind::Directory) || (entry->compression == ::std_::archive::types::ZipCompression::Store)) {
        return entry->data;
    }
    return ::doof_gzip::deflateRaw(entry->data);
}
std::shared_ptr<std::vector<uint8_t>> writeZip(const std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::ZipEntry>>>& entries) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    const auto centralBuilder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    const auto& _iterable_2 = entries;
    for (const auto& source : *_iterable_2) {
        const auto nameBytes = encodedName(source->name);
        const auto localHeaderOffset = builder->length();
        const auto compressed = compressEntry(source);
        const ::std_::archive::types::ZipCompression compression = ((source->kind == ::std_::archive::types::ArchiveEntryKind::Directory) ? ::std_::archive::types::ZipCompression::Store : source->compression);
        const auto entry = std::make_shared<::std_::archive::types::ZipEntry>(source->name, source->kind, static_cast<int64_t>(static_cast<int32_t>((source->data)->size())), static_cast<int64_t>(static_cast<int32_t>((compressed)->size())), ::doof_gzip::crc32Bytes(source->data), compression, source->data);
        writeLocalHeader(builder, entry, nameBytes, compressed);
        builder->writeBytes(compressed);
        writeCentralHeader(centralBuilder, entry, nameBytes, localHeaderOffset);
    }
    const auto centralDirectory = centralBuilder->build();
    const auto centralDirectoryOffset = builder->length();
    builder->writeBytes(centralDirectory);
    builder->writeUnsignedInt(END_OF_CENTRAL_DIRECTORY_SIGNATURE);
    builder->writeUnsignedShort(0);
    builder->writeUnsignedShort(0);
    builder->writeUnsignedShort(static_cast<int32_t>((entries)->size()));
    builder->writeUnsignedShort(static_cast<int32_t>((entries)->size()));
    builder->writeUnsignedInt(static_cast<int64_t>(static_cast<int32_t>((centralDirectory)->size())));
    builder->writeUnsignedInt(centralDirectoryOffset);
    builder->writeUnsignedShort(0);
    return builder->build();
}
}
