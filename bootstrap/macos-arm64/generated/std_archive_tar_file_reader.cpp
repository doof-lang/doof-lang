#include "std_archive_tar_file_reader.hpp"

namespace std_::archive::tar_file_reader {
using namespace ::std_::archive::types;
using namespace ::std_::archive::tar_reader;
int64_t TAR_BLOCK_SIZE = 512LL;
int64_t TAR_MODE_OFFSET = 100LL;
int64_t TAR_MODE_LENGTH = 8LL;
int64_t TAR_SIZE_OFFSET = 124LL;
int64_t TAR_SIZE_LENGTH = 12LL;
int64_t TAR_MTIME_OFFSET = 136LL;
int64_t TAR_MTIME_LENGTH = 12LL;
int64_t TAR_TYPE_OFFSET = 156LL;
int64_t TAR_LINK_NAME_OFFSET = 157LL;
int64_t TAR_LINK_NAME_LENGTH = 100LL;
int64_t MAX_BLOB_SIZE = 2147483647LL;
bool isGzipTarPath(const std::string& path) {
    return ((static_cast<int32_t>(path.size()) >= 7) && (doof::string_slice(path, (static_cast<int32_t>(path.size()) - 7)) == std::string(".tar.gz")));
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> readPaxPayload(const std::shared_ptr<::doof_archive::NativeArchiveFile>& file, int64_t offset, int64_t size) {
    if (size > MAX_BLOB_SIZE) {
        return doof::Failure<std::string>{ std::string("tar file scan failed: PAX metadata is too large") };
    }
    return file->read(offset, size);
}
doof::Result<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>>, std::string> scanTarFile(const std::string& path) {
    if (isGzipTarPath(path)) {
        return doof::Failure<std::string>{ std::string("tar file scan failed: compressed TAR files are not seekable") };
    }
    auto _binding_value_1 = ::doof_archive::NativeArchiveFile::open(path);
    if (doof::is_failure(_binding_value_1)) {
        const auto error = doof::failure_error(_binding_value_1);
        return doof::Failure<std::string>{ (std::string("tar file scan failed: ") + error) };
    }
    const auto file = doof::success_value(_binding_value_1);
    const auto fileSize = file->size();
    if ((fileSize < (TAR_BLOCK_SIZE * 2LL)) || ((fileSize % TAR_BLOCK_SIZE) != 0LL)) {
        return doof::Failure<std::string>{ std::string("tar read failed: archive must contain complete 512-byte blocks") };
    }
    auto offset = 0LL;
    std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>> entries = std::make_shared<std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>>(std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>{});
    const std::shared_ptr<doof::ordered_map<std::string, std::string>> globalPax = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    std::shared_ptr<doof::ordered_map<std::string, std::string>> localPax = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    while ((offset + TAR_BLOCK_SIZE) <= fileSize) {
        auto _binding_value_2 = file->read(offset, TAR_BLOCK_SIZE);
        if (doof::is_failure(_binding_value_2)) {
            const auto error = doof::failure_error(_binding_value_2);
            return doof::Failure<std::string>{ (std::string("tar file scan failed: ") + error) };
        }
        const auto header = doof::success_value(_binding_value_2);
        if (::std_::archive::tar_reader::isZeroRange(header, 0LL, TAR_BLOCK_SIZE)) {
            if ((offset + (TAR_BLOCK_SIZE * 2LL)) > fileSize) {
                return doof::Failure<std::string>{ std::string("tar read failed: archive terminator requires two zero blocks") };
            }
            auto _binding_value_3 = file->read((offset + TAR_BLOCK_SIZE), TAR_BLOCK_SIZE);
            if (doof::is_failure(_binding_value_3)) {
                const auto error = doof::failure_error(_binding_value_3);
                return doof::Failure<std::string>{ (std::string("tar file scan failed: ") + error) };
            }
            const auto second = doof::success_value(_binding_value_3);
            if (!::std_::archive::tar_reader::isZeroRange(second, 0LL, TAR_BLOCK_SIZE)) {
                return doof::Failure<std::string>{ std::string("tar read failed: archive terminator requires two zero blocks") };
            }
            auto trailingOffset = (offset + (TAR_BLOCK_SIZE * 2LL));
            while (trailingOffset < fileSize) {
                auto _binding_value_4 = file->read(trailingOffset, TAR_BLOCK_SIZE);
                if (doof::is_failure(_binding_value_4)) {
                    const auto error = doof::failure_error(_binding_value_4);
                    return doof::Failure<std::string>{ (std::string("tar file scan failed: ") + error) };
                }
                const auto trailing = doof::success_value(_binding_value_4);
                if (!::std_::archive::tar_reader::isZeroRange(trailing, 0LL, TAR_BLOCK_SIZE)) {
                    return doof::Failure<std::string>{ std::string("tar read failed: non-zero data follows archive terminator") };
                }
                (trailingOffset = (trailingOffset + TAR_BLOCK_SIZE));
            }
            return doof::Success<std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>>>{ doof::array_drainToReadonly(entries, "", 0) };
        }
        auto _try_value_5 = ::std_::archive::tar_reader::validateHeader(header, 0LL);
        if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_5))};
        auto _try_value_6 = ::std_::archive::tar_reader::readHeaderName(header, 0LL);
        if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
        const auto baseName = doof::success_value(_try_value_6);
        auto _try_value_7 = ::std_::archive::tar_reader::parseOctalField(header, TAR_MODE_OFFSET, TAR_MODE_LENGTH, std::string("entry mode"));
        if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_7))};
        const auto baseMode = doof::success_value(_try_value_7);
        auto _try_value_8 = ::std_::archive::tar_reader::parseOctalField(header, TAR_SIZE_OFFSET, TAR_SIZE_LENGTH, std::string("entry size"));
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
        const auto baseSize = doof::success_value(_try_value_8);
        auto _try_value_9 = ::std_::archive::tar_reader::parseOctalField(header, TAR_MTIME_OFFSET, TAR_MTIME_LENGTH, std::string("entry modification time"));
        if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
        const auto baseMtime = doof::success_value(_try_value_9);
        if (baseMode > 2147483647LL) {
            return doof::Failure<std::string>{ std::string("tar read failed: entry mode is out of range") };
        }
        if (baseMtime > 9223372036LL) {
            return doof::Failure<std::string>{ std::string("tar read failed: entry modification time is out of range") };
        }
        const auto typeFlag = doof::array_at(header, static_cast<int32_t>(TAR_TYPE_OFFSET), "tar_file_reader", 96);
        const auto contentOffset = (offset + TAR_BLOCK_SIZE);
        auto _try_value_10 = ::std_::archive::tar_reader::alignedPayloadEnd(contentOffset, baseSize, fileSize);
        if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_10))};
        const auto nextOffset = doof::success_value(_try_value_10);
        if ((typeFlag == 120) || (typeFlag == 103)) {
            auto _try_value_11 = readPaxPayload(file, contentOffset, baseSize);
            if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_11))};
            const auto paxPayload = doof::success_value(_try_value_11);
            const auto target = ((typeFlag == 103) ? globalPax : localPax);
            auto _try_value_12 = ::std_::archive::tar_reader::parsePaxRecords(paxPayload, 0LL, baseSize, target);
            if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
            (offset = nextOffset);
            continue;
        }
        const auto pathValue = ::std_::archive::tar_reader::paxValue(localPax, globalPax, std::string("path"));
        const auto resolvedName = (doof::is_null(pathValue) ? baseName : pathValue.value());
        auto _try_value_13 = ::std_::archive::tar_reader::readTextField(header, TAR_LINK_NAME_OFFSET, TAR_LINK_NAME_LENGTH, std::string("entry link name"));
        if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
        const auto baseLinkName = doof::success_value(_try_value_13);
        const auto linkPathValue = ::std_::archive::tar_reader::paxValue(localPax, globalPax, std::string("linkpath"));
        const auto resolvedLinkName = (doof::is_null(linkPathValue) ? baseLinkName : linkPathValue.value());
        const auto sizeText = ::std_::archive::tar_reader::paxValue(localPax, globalPax, std::string("size"));
        auto resolvedSize = baseSize;
        if (!doof::is_null(sizeText)) {
            auto _try_value_14 = ::std_::archive::tar_reader::parseDecimal(sizeText.value(), std::string("size"));
            if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
            const auto parsedSize = doof::success_value(_try_value_14);
            (resolvedSize = parsedSize);
        }
        auto resolvedNextOffset = nextOffset;
        if (resolvedSize != baseSize) {
            auto _try_value_15 = ::std_::archive::tar_reader::alignedPayloadEnd(contentOffset, resolvedSize, fileSize);
            if (doof::is_failure(_try_value_15)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_15))};
            const auto updatedOffset = doof::success_value(_try_value_15);
            (resolvedNextOffset = updatedOffset);
        }
        const auto mtimeText = ::std_::archive::tar_reader::paxValue(localPax, globalPax, std::string("mtime"));
        auto resolvedMtime = ::std_::time::temporal::Instant::ofEpochSeconds(baseMtime);
        if (!doof::is_null(mtimeText)) {
            auto _try_value_16 = ::std_::archive::tar_reader::parsePaxMtime(mtimeText.value());
            if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_16))};
            const auto parsedMtime = doof::success_value(_try_value_16);
            (resolvedMtime = parsedMtime);
        }
        auto kind = ::std_::archive::types::TarEntryKind::File;
        if (typeFlag == 53) {
            (kind = ::std_::archive::types::TarEntryKind::Directory);
        } else if (typeFlag == 50) {
            (kind = ::std_::archive::types::TarEntryKind::SymbolicLink);
        } else if ((typeFlag != 0) && (typeFlag != 48)) {
            return doof::Failure<std::string>{ (std::string("tar read failed: unsupported entry type ") + doof::to_string(typeFlag)) };
        }
        entries->push_back(std::make_shared<::std_::archive::types::TarEntry>(resolvedName, kind, contentOffset, resolvedSize, static_cast<int32_t>(baseMode), resolvedMtime, resolvedLinkName));
        (localPax = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}));
        (offset = resolvedNextOffset);
    }
    return doof::Failure<std::string>{ std::string("tar read failed: archive terminator not found") };
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> readTarEntry(const std::string& path, const std::shared_ptr<::std_::archive::types::TarEntry>& entry) {
    if (isGzipTarPath(path)) {
        return doof::Failure<std::string>{ std::string("tar entry read failed: compressed TAR files are not seekable") };
    }
    if (entry->size > MAX_BLOB_SIZE) {
        return doof::Failure<std::string>{ std::string("tar entry read failed: entry is too large for a byte array") };
    }
    auto _binding_value_17 = ::doof_archive::NativeArchiveFile::open(path);
    if (doof::is_failure(_binding_value_17)) {
        const auto error = doof::failure_error(_binding_value_17);
        return doof::Failure<std::string>{ (std::string("tar entry read failed: ") + error) };
    }
    const auto file = doof::success_value(_binding_value_17);
    auto _binding_value_18 = file->read(entry->contentOffset, entry->size);
    if (doof::is_failure(_binding_value_18)) {
        const auto error = doof::failure_error(_binding_value_18);
        return doof::Failure<std::string>{ (std::string("tar entry read failed: ") + error) };
    }
    const auto data = doof::success_value(_binding_value_18);
    return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ data };
}
}
