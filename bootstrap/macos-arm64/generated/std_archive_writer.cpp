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
    (static_cast<void>(builder->writeString(name)), std::monostate{});
    return builder->build();
}
void writeLocalHeader(const std::shared_ptr<::doof_blob::NativeBlobBuilder>& builder, const std::shared_ptr<::std_::archive::types::ZipEntry>& entry, const std::shared_ptr<std::vector<uint8_t>>& nameBytes, const std::shared_ptr<std::vector<uint8_t>>& compressed) {
    (static_cast<void>(builder->writeUnsignedInt(LOCAL_FILE_HEADER_SIGNATURE)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(ZIP_VERSION_NEEDED)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(ZIP_UTF8_FLAG)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(::std_::archive::types::ZipCompression_value(entry->compression))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(entry->crc32)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(static_cast<int64_t>(static_cast<int32_t>((compressed)->size())))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(static_cast<int64_t>(static_cast<int32_t>((entry->data)->size())))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(static_cast<int32_t>((nameBytes)->size()))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeBytes(nameBytes)), std::monostate{});
}
void writeCentralHeader(const std::shared_ptr<::doof_blob::NativeBlobBuilder>& builder, const std::shared_ptr<::std_::archive::types::ZipEntry>& entry, const std::shared_ptr<std::vector<uint8_t>>& nameBytes, int64_t localHeaderOffset) {
    (static_cast<void>(builder->writeUnsignedInt(CENTRAL_DIRECTORY_SIGNATURE)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(ZIP_VERSION_MADE_BY)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(ZIP_VERSION_NEEDED)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(ZIP_UTF8_FLAG)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(::std_::archive::types::ZipCompression_value(entry->compression))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(entry->crc32)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(entry->compressedSize)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(static_cast<int64_t>(static_cast<int32_t>((entry->data)->size())))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(static_cast<int32_t>((nameBytes)->size()))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(0LL)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(localHeaderOffset)), std::monostate{});
    (static_cast<void>(builder->writeBytes(nameBytes)), std::monostate{});
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
        (static_cast<void>(writeLocalHeader(builder, entry, nameBytes, compressed)), std::monostate{});
        (static_cast<void>(builder->writeBytes(compressed)), std::monostate{});
        (static_cast<void>(writeCentralHeader(centralBuilder, entry, nameBytes, localHeaderOffset)), std::monostate{});
    }
    const auto centralDirectory = centralBuilder->build();
    const auto centralDirectoryOffset = builder->length();
    (static_cast<void>(builder->writeBytes(centralDirectory)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(END_OF_CENTRAL_DIRECTORY_SIGNATURE)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(static_cast<int32_t>((entries)->size()))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(static_cast<int32_t>((entries)->size()))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(static_cast<int64_t>(static_cast<int32_t>((centralDirectory)->size())))), std::monostate{});
    (static_cast<void>(builder->writeUnsignedInt(centralDirectoryOffset)), std::monostate{});
    (static_cast<void>(builder->writeUnsignedShort(0)), std::monostate{});
    return builder->build();
}
}
