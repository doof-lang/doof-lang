#include "std_archive_tar_writer.hpp"

namespace std_::archive::tar_writer {
using namespace ::std_::blob::index;
using namespace ::std_::fs::index;
using namespace ::std_::gzip::index;
using namespace ::std_::archive::types;
int64_t TAR_BLOCK_SIZE = 512LL;
int64_t TAR_MAX_BASE_SIZE = 8589934591LL;


bool TarChunkStream::next() {
    if (this->index >= static_cast<int32_t>((this->chunks)->size())) {
        return false;
    }
    (this->currentValue = doof::array_at(this->chunks, this->index, "tar_writer", 23)->data);
    (this->index = (this->index + 1));
    return true;
}
std::shared_ptr<std::vector<uint8_t>> TarChunkStream::value() {
    return this->currentValue;
}
std::string ioErrorText(::std_::fs::types::IoError error) {
    return [&]() -> std::string {
    auto _case_subject = error;
    if (_case_subject == ::std_::fs::types::IoError::NotFound) {
        return std::string("not found");
    }
    if (_case_subject == ::std_::fs::types::IoError::PermissionDenied) {
        return std::string("permission denied");
    }
    if (_case_subject == ::std_::fs::types::IoError::AlreadyExists) {
        return std::string("already exists");
    }
    if (_case_subject == ::std_::fs::types::IoError::IsDirectory) {
        return std::string("is a directory");
    }
    if (_case_subject == ::std_::fs::types::IoError::NotDirectory) {
        return std::string("not a directory");
    }
    if (_case_subject == ::std_::fs::types::IoError::InvalidPath) {
        return std::string("invalid path");
    }
    if (_case_subject == ::std_::fs::types::IoError::Interrupted) {
        return std::string("interrupted");
    }
    if (_case_subject == ::std_::fs::types::IoError::Other) {
        return std::string("other I/O error");
    }
    if (_case_subject == ::std_::fs::types::IoError::Unsupported) {
        return std::string("unsupported operation");
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
bool isGzipTarPath(const std::string& path) {
    return ((static_cast<int32_t>(path.size()) >= 7) && (doof::string_slice(path, (static_cast<int32_t>(path.size()) - 7)) == std::string(".tar.gz")));
}
std::shared_ptr<std::vector<uint8_t>> encodeText(const std::string& value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeString(value);
    return builder->build();
}
std::string octal(int64_t value) {
    if (value == 0LL) {
        return std::string("0");
    }
    auto remaining = value;
    auto result = std::string("");
    while (remaining > 0LL) {
        (result = (doof::to_string((remaining % 8LL)) + result));
        (remaining = (remaining / 8LL));
    }
    return result;
}
void writeTextAt(const std::shared_ptr<::doof_blob::NativeBlobBuilder>& builder, int64_t offset, const std::string& value) {
    builder->setPosition(offset);
    builder->writeString(value);
}
void writeOctalAt(const std::shared_ptr<::doof_blob::NativeBlobBuilder>& builder, int64_t offset, int32_t width, int64_t value) {
    const auto digits = octal(value);
    auto padded = digits;
    while (static_cast<int32_t>(padded.size()) < (width - 1)) {
        (padded = (std::string("0") + padded));
    }
    writeTextAt(builder, offset, padded);
    builder->writeByte(0);
}
std::shared_ptr<std::vector<uint8_t>> patchChecksum(const std::shared_ptr<std::vector<uint8_t>>& header) {
    auto checksum = 0LL;
    for (int32_t index = 0; index < static_cast<int32_t>((header)->size()); ++index) {
        (checksum = (checksum + (((index >= 148) && (index < 156)) ? 32LL : static_cast<int64_t>(doof::array_at(header, index, "tar_writer", 86)))));
    }
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeBytes(header);
    const auto digits = octal(checksum);
    auto padded = digits;
    while (static_cast<int32_t>(padded.size()) < 6) {
        (padded = (std::string("0") + padded));
    }
    writeTextAt(builder, 148LL, padded);
    builder->writeByte(0);
    builder->writeByte(32);
    return builder->build();
}

std::shared_ptr<UstarPath> ustarPath(const std::string& path) {
    const auto bytes = encodeText(path);
    const auto& _iterable_3 = bytes;
    for (const auto& value : *_iterable_3) {
        if (value > 127) {
            return nullptr;
        }
    }
    if (static_cast<int32_t>((bytes)->size()) <= 100) {
        return std::make_shared<UstarPath>(path, std::string(""));
    }
    for (int32_t distance = 1; distance < static_cast<int32_t>(path.size()); ++distance) {
        const auto slash = (static_cast<int32_t>(path.size()) - distance);
        if (doof::string_at(path, slash, "", 0) != U'\u002F') {
            continue;
        }
        const auto prefix = doof::string_substring(path, 0, slash);
        const auto name = doof::string_substring(path, (slash + 1), static_cast<int32_t>(path.size()));
        if (((static_cast<int32_t>(name.size()) > 0) && (static_cast<int32_t>((encodeText(prefix))->size()) <= 155)) && (static_cast<int32_t>((encodeText(name))->size()) <= 100)) {
            return std::make_shared<UstarPath>(name, prefix);
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<uint8_t>> buildHeader(const std::shared_ptr<UstarPath>& path, int64_t size, int32_t mode, const std::shared_ptr<::std_::time::temporal::Instant>& mtime, uint8_t typeFlag, const std::string& linkName) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeZeroes(TAR_BLOCK_SIZE);
    writeTextAt(builder, 0LL, path->name);
    writeOctalAt(builder, 100LL, 8, static_cast<int64_t>(mode));
    writeOctalAt(builder, 108LL, 8, 0LL);
    writeOctalAt(builder, 116LL, 8, 0LL);
    writeOctalAt(builder, 124LL, 12, size);
    writeOctalAt(builder, 136LL, 12, mtime->toEpochSeconds());
    writeTextAt(builder, 148LL, std::string("        "));
    builder->setPosition(156LL);
    builder->writeByte(typeFlag);
    writeTextAt(builder, 157LL, linkName);
    writeTextAt(builder, 257LL, std::string("ustar"));
    builder->setPosition(262LL);
    builder->writeByte(0);
    writeTextAt(builder, 263LL, std::string("00"));
    writeTextAt(builder, 345LL, path->prefix);
    return patchChecksum(builder->build());
}
std::shared_ptr<std::vector<uint8_t>> paxRecord(const std::string& key, const std::string& value) {
    const auto body = (((key + std::string("=")) + value) + std::string("\n"));
    auto length = static_cast<int32_t>((encodeText((std::string("0 ") + body)))->size());
    while (true) {
        const auto record = ((doof::to_string(length) + std::string(" ")) + body);
        const auto actualLength = static_cast<int32_t>((encodeText(record))->size());
        if (actualLength == length) {
            return encodeText(record);
        }
        (length = actualLength);
    }
}
std::string paxMtime(const std::shared_ptr<::std_::time::temporal::Instant>& value) {
    const auto nanos = value->toEpochNanos();
    const auto seconds = (nanos / 1000000000LL);
    auto remainder = (nanos % 1000000000LL);
    if (remainder == 0LL) {
        return doof::to_string(seconds);
    }
    if (remainder < 0LL) {
        (remainder = -remainder);
    }
    const auto fraction = doof::string_trimEnd(doof::string_padStart(doof::to_string(remainder), 9, U'\u0030'), U'\u0030');
    if ((nanos < 0LL) && (seconds == 0LL)) {
        return (std::string("-0.") + fraction);
    }
    return ((doof::to_string(seconds) + std::string(".")) + fraction);
}
std::shared_ptr<std::vector<uint8_t>> padding(int64_t size) {
    const auto length = static_cast<int32_t>(((TAR_BLOCK_SIZE - (size % TAR_BLOCK_SIZE)) % TAR_BLOCK_SIZE));
    if (length == 0) {
        return std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
    }
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    builder->writeZeroes(static_cast<int64_t>(length));
    return builder->build();
}
void appendPayload(const std::shared_ptr<std::vector<std::shared_ptr<TarChunk>>>& chunks, const std::shared_ptr<std::vector<uint8_t>>& data) {
    if (static_cast<int32_t>((data)->size()) > 0) {
        chunks->push_back(std::make_shared<TarChunk>(data));
    }
    const auto paddingBytes = padding(static_cast<int64_t>(static_cast<int32_t>((data)->size())));
    if (static_cast<int32_t>((paddingBytes)->size()) > 0) {
        chunks->push_back(std::make_shared<TarChunk>(paddingBytes));
    }
}
std::shared_ptr<std::vector<std::shared_ptr<TarChunk>>> buildTarChunks(const std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarWriteEntry>>>& entries) {
    std::shared_ptr<std::vector<std::shared_ptr<TarChunk>>> chunks = std::make_shared<std::vector<std::shared_ptr<TarChunk>>>(std::vector<std::shared_ptr<TarChunk>>{});
    for (int32_t index = 0; index < static_cast<int32_t>((entries)->size()); ++index) {
        const auto entry = doof::array_at(entries, index, "tar_writer", 214);
        const auto isDirectory = (entry->kind == ::std_::archive::types::TarEntryKind::Directory);
        const auto isSymbolicLink = (entry->kind == ::std_::archive::types::TarEntryKind::SymbolicLink);
        const std::shared_ptr<std::vector<uint8_t>> payload = ((isDirectory || isSymbolicLink) ? std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}) : entry->data);
        auto mode = (isSymbolicLink ? 511 : (isDirectory ? 493 : 420));
        if (!doof::is_null(entry->mode)) {
            (mode = doof::unwrap_optional(entry->mode));
        }
        const auto directPath = ustarPath(entry->name);
        const auto requiresPaxSize = (static_cast<int64_t>(static_cast<int32_t>((payload)->size())) > TAR_MAX_BASE_SIZE);
        const auto epochNanos = entry->mtime->toEpochNanos();
        const auto epochSeconds = entry->mtime->toEpochSeconds();
        const auto requiresPaxMtime = (((epochNanos < 0LL) || ((epochNanos % 1000000000LL) != 0LL)) || (epochSeconds > TAR_MAX_BASE_SIZE));
        const auto linkPath = ustarPath(entry->linkName);
        const auto requiresPaxLinkPath = (isSymbolicLink && (doof::is_null(linkPath) || (static_cast<int32_t>(linkPath->prefix.size()) > 0)));
        auto headerPath = directPath;
        if (((doof::is_null(directPath) || requiresPaxSize) || requiresPaxMtime) || requiresPaxLinkPath) {
            std::shared_ptr<std::vector<uint8_t>> paxPayload = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{});
            const auto paxBuilder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
            if (doof::is_null(directPath)) {
                paxBuilder->writeBytes(paxRecord(std::string("path"), entry->name));
            }
            if (requiresPaxSize) {
                paxBuilder->writeBytes(paxRecord(std::string("size"), doof::to_string(static_cast<int32_t>((payload)->size()))));
            }
            if (requiresPaxMtime) {
                paxBuilder->writeBytes(paxRecord(std::string("mtime"), paxMtime(entry->mtime)));
            }
            if (requiresPaxLinkPath) {
                paxBuilder->writeBytes(paxRecord(std::string("linkpath"), entry->linkName));
            }
            (paxPayload = paxBuilder->build());
            const auto paxName = (std::string("PaxHeaders/") + doof::to_string(index));
            chunks->push_back(std::make_shared<TarChunk>(buildHeader(std::make_shared<UstarPath>(paxName, std::string("")), static_cast<int64_t>(static_cast<int32_t>((paxPayload)->size())), 420, ::std_::time::temporal::Instant::EPOCH, 120, std::string(""))));
            appendPayload(chunks, paxPayload);
            (headerPath = std::make_shared<UstarPath>((std::string("PaxEntry/") + doof::to_string(index)), std::string("")));
        }
        const auto storedSize = (requiresPaxSize ? 0LL : static_cast<int64_t>(static_cast<int32_t>((payload)->size())));
        const auto storedMtime = (requiresPaxMtime ? ::std_::time::temporal::Instant::EPOCH : entry->mtime);
        const uint8_t typeFlag = (isDirectory ? 53 : (isSymbolicLink ? 50 : 48));
        const auto storedLinkName = ((isSymbolicLink && !requiresPaxLinkPath) ? entry->linkName : std::string(""));
        chunks->push_back(std::make_shared<TarChunk>(buildHeader(doof::unwrap_optional(headerPath), storedSize, mode, storedMtime, typeFlag, storedLinkName)));
        appendPayload(chunks, payload);
    }
    const auto terminator = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    terminator->writeZeroes((TAR_BLOCK_SIZE * 2LL));
    chunks->push_back(std::make_shared<TarChunk>(terminator->build()));
    return chunks;
}
std::shared_ptr<std::vector<uint8_t>> writeTarBlob(const std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarWriteEntry>>>& entries) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    const auto& _iterable_7 = buildTarChunks(entries);
    for (const auto& chunk : *_iterable_7) {
        builder->writeBytes(chunk->data);
    }
    return builder->build();
}
doof::Result<void, std::string> writeTarFile(const std::string& path, const std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarWriteEntry>>>& entries) {
    const auto source = std::make_shared<TarChunkStream>(buildTarChunks(entries), 0, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}));
    if (isGzipTarPath(path)) {
        return [&]() -> doof::Result<void, std::string> {
    auto _case_subject = ::std_::fs::index::writeBlobStream(path, ::std_::gzip::index::GzipStream::constructor(source));
    if (std::holds_alternative<doof::Success<void>>(_case_subject)) {
        return doof::Success<void>{};
    }
    if (std::holds_alternative<doof::Failure<::std_::fs::types::IoError>>(_case_subject)) {
        const auto& failure = std::get<doof::Failure<::std_::fs::types::IoError>>(_case_subject);
        return doof::Failure<std::string>{ (std::string("tar file write failed: ") + ioErrorText(failure.error)) };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
    }
    return [&]() -> doof::Result<void, std::string> {
    auto _case_subject = ::std_::fs::index::writeBlobStream(path, source);
    if (std::holds_alternative<doof::Success<void>>(_case_subject)) {
        return doof::Success<void>{};
    }
    if (std::holds_alternative<doof::Failure<::std_::fs::types::IoError>>(_case_subject)) {
        const auto& failure = std::get<doof::Failure<::std_::fs::types::IoError>>(_case_subject);
        return doof::Failure<std::string>{ (std::string("tar file write failed: ") + ioErrorText(failure.error)) };
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
}
