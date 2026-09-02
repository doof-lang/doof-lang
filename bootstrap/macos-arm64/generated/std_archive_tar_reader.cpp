#include "std_archive_tar_reader.hpp"

namespace std_::archive::tar_reader {
using namespace ::std_::blob::index;
using namespace ::std_::fs::index;
using namespace ::std_::gzip::index;
using namespace ::std_::archive::types;
int64_t TAR_BLOCK_SIZE = 512LL;
int64_t TAR_NAME_OFFSET = 0LL;
int64_t TAR_NAME_LENGTH = 100LL;
int64_t TAR_MODE_OFFSET = 100LL;
int64_t TAR_MODE_LENGTH = 8LL;
int64_t TAR_SIZE_OFFSET = 124LL;
int64_t TAR_SIZE_LENGTH = 12LL;
int64_t TAR_MTIME_OFFSET = 136LL;
int64_t TAR_MTIME_LENGTH = 12LL;
int64_t TAR_CHECKSUM_OFFSET = 148LL;
int64_t TAR_CHECKSUM_LENGTH = 8LL;
int64_t TAR_TYPE_OFFSET = 156LL;
int64_t TAR_LINK_NAME_OFFSET = 157LL;
int64_t TAR_LINK_NAME_LENGTH = 100LL;
int64_t TAR_MAGIC_OFFSET = 257LL;
int64_t TAR_PREFIX_OFFSET = 345LL;
int64_t TAR_PREFIX_LENGTH = 155LL;
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
bool isZeroRange(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t offset, int64_t length) {
    if ((((offset < 0LL) || (length < 0LL)) || (offset > static_cast<int64_t>(static_cast<int32_t>((data)->size())))) || (length > (static_cast<int64_t>(static_cast<int32_t>((data)->size())) - offset))) {
        return false;
    }
    auto index = offset;
    while (index < (offset + length)) {
        if (doof::array_at(data, static_cast<int32_t>(index), "tar_reader", 49) != 0) {
            return false;
        }
        (index = (index + 1LL));
    }
    return true;
}
int64_t fieldEnd(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t offset, int64_t length) {
    auto index = offset;
    while (index < (offset + length)) {
        if (doof::array_at(data, static_cast<int32_t>(index), "tar_reader", 60) == 0) {
            return index;
        }
        (index = (index + 1LL));
    }
    return (offset + length);
}
doof::Result<std::string, std::string> readTextField(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t offset, int64_t length, const std::string& context) {
    const auto end = fieldEnd(data, offset, length);
    const auto bytes = doof::array_slice(data, static_cast<int32_t>(offset), static_cast<int32_t>(end), "", 0);
    auto _binding_value_1 = ::std_::blob::index::decodeUtf8(bytes);
    if (doof::is_failure(_binding_value_1)) {
        const auto& decoded = _binding_value_1;
        return doof::Failure<std::string>{ (std::string("tar read failed: invalid UTF-8 in ") + context) };
    }
    const auto decoded = doof::success_value(_binding_value_1);
    return doof::Success<std::string>{ decoded };
}
doof::Result<int64_t, std::string> parseOctalField(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t offset, int64_t length, const std::string& context) {
    auto value = 0LL;
    auto sawDigit = false;
    auto ended = false;
    auto index = offset;
    while (index < (offset + length)) {
        const auto character = doof::array_at(data, static_cast<int32_t>(index), "tar_reader", 84);
        if ((character == 0) || (character == 32)) {
            if (sawDigit) {
                (ended = true);
            }
            (index = (index + 1LL));
            continue;
        }
        if ((ended || (character < 48)) || (character > 55)) {
            return doof::Failure<std::string>{ (std::string("tar read failed: invalid octal ") + context) };
        }
        const auto digit = static_cast<int64_t>((character - 48));
        if (value > ((9223372036854775807LL - digit) / 8LL)) {
            return doof::Failure<std::string>{ (std::string("tar read failed: overflowing octal ") + context) };
        }
        (value = ((value * 8LL) + digit));
        (sawDigit = true);
        (index = (index + 1LL));
    }
    if (!sawDigit) {
        return doof::Success<int64_t>{ 0LL };
    }
    return doof::Success<int64_t>{ value };
}
int64_t headerChecksum(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t offset) {
    auto sum = 0LL;
    auto relative = 0LL;
    while (relative < TAR_BLOCK_SIZE) {
        if ((relative >= TAR_CHECKSUM_OFFSET) && (relative < (TAR_CHECKSUM_OFFSET + TAR_CHECKSUM_LENGTH))) {
            (sum = (sum + 32LL));
        } else {
            (sum = (sum + static_cast<int64_t>(doof::array_at(data, static_cast<int32_t>((offset + relative)), "tar_reader", 117))));
        }
        (relative = (relative + 1LL));
    }
    return sum;
}
doof::Result<void, std::string> validateHeader(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t offset) {
    auto _try_value_2 = parseOctalField(data, (offset + TAR_CHECKSUM_OFFSET), TAR_CHECKSUM_LENGTH, std::string("checksum"));
    if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_2))};
    const auto storedChecksum = doof::success_value(_try_value_2);
    if (storedChecksum != headerChecksum(data, offset)) {
        return doof::Failure<std::string>{ std::string("tar read failed: header checksum mismatch") };
    }
    if ((((((doof::array_at(data, static_cast<int32_t>((offset + TAR_MAGIC_OFFSET)), "tar_reader", 130) != 117) || (doof::array_at(data, static_cast<int32_t>(((offset + TAR_MAGIC_OFFSET) + 1LL)), "tar_reader", 131) != 115)) || (doof::array_at(data, static_cast<int32_t>(((offset + TAR_MAGIC_OFFSET) + 2LL)), "tar_reader", 132) != 116)) || (doof::array_at(data, static_cast<int32_t>(((offset + TAR_MAGIC_OFFSET) + 3LL)), "tar_reader", 133) != 97)) || (doof::array_at(data, static_cast<int32_t>(((offset + TAR_MAGIC_OFFSET) + 4LL)), "tar_reader", 134) != 114)) || (doof::array_at(data, static_cast<int32_t>(((offset + TAR_MAGIC_OFFSET) + 5LL)), "tar_reader", 135) != 0)) {
        return doof::Failure<std::string>{ std::string("tar read failed: unsupported header format") };
    }
    return doof::Success<void>{};
}
doof::Result<std::string, std::string> readHeaderName(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t offset) {
    auto _try_value_3 = readTextField(data, (offset + TAR_NAME_OFFSET), TAR_NAME_LENGTH, std::string("entry name"));
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_3))};
    const auto name = doof::success_value(_try_value_3);
    auto _try_value_4 = readTextField(data, (offset + TAR_PREFIX_OFFSET), TAR_PREFIX_LENGTH, std::string("entry prefix"));
    if (doof::is_failure(_try_value_4)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_4))};
    const auto prefix = doof::success_value(_try_value_4);
    if ((static_cast<int32_t>(prefix.size()) > 0) && (static_cast<int32_t>(name.size()) > 0)) {
        return doof::Success<std::string>{ ((prefix + std::string("/")) + name) };
    }
    if (static_cast<int32_t>(prefix.size()) > 0) {
        return doof::Success<std::string>{ prefix };
    }
    return doof::Success<std::string>{ name };
}
doof::Result<int64_t, std::string> parseDecimal(const std::string& value, const std::string& context) {
    if (static_cast<int32_t>(value.size()) == 0) {
        return doof::Failure<std::string>{ (std::string("tar read failed: empty PAX ") + context) };
    }
    auto result = 0LL;
    for (int32_t index = 0; index < static_cast<int32_t>(value.size()); ++index) {
        const auto character = doof::string_at(value, index, "", 0);
        if ((character < U'\u0030') || (character > U'\u0039')) {
            return doof::Failure<std::string>{ (std::string("tar read failed: invalid PAX ") + context) };
        }
        const auto digit = static_cast<int64_t>((static_cast<int32_t>(character) - static_cast<int32_t>(U'\u0030')));
        if (result > ((9223372036854775807LL - digit) / 10LL)) {
            return doof::Failure<std::string>{ (std::string("tar read failed: overflowing PAX ") + context) };
        }
        (result = ((result * 10LL) + digit));
    }
    return doof::Success<int64_t>{ result };
}
doof::Result<std::shared_ptr<::std_::time::temporal::Instant>, std::string> parsePaxMtime(const std::string& value) {
    if (static_cast<int32_t>(value.size()) == 0) {
        return doof::Failure<std::string>{ std::string("tar read failed: empty PAX mtime") };
    }
    auto negative = false;
    auto start = 0;
    const auto first = doof::string_at(value, 0, "", 0);
    if ((first == U'\u002D') || (first == U'\u002B')) {
        (negative = (first == U'\u002D'));
        (start = 1);
    }
    auto decimal = doof::string_indexOf(value, std::string("."));
    if (decimal < 0) {
        (decimal = static_cast<int32_t>(value.size()));
    }
    if ((start >= static_cast<int32_t>(value.size())) || (decimal == start)) {
        return doof::Failure<std::string>{ std::string("tar read failed: invalid PAX mtime") };
    }
    auto _try_value_6 = parseDecimal(doof::string_substring(value, start, decimal), std::string("mtime"));
    if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
    const auto seconds = doof::success_value(_try_value_6);
    auto nanos = 0LL;
    if (decimal < static_cast<int32_t>(value.size())) {
        const auto fraction = doof::string_slice(value, (decimal + 1));
        if ((static_cast<int32_t>(fraction.size()) == 0) || (static_cast<int32_t>(fraction.size()) > 9)) {
            return doof::Failure<std::string>{ std::string("tar read failed: unsupported PAX mtime precision") };
        }
        auto _try_value_7 = parseDecimal(fraction, std::string("mtime fraction"));
        if (doof::is_failure(_try_value_7)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_7))};
        const auto fractionValue = doof::success_value(_try_value_7);
        (nanos = fractionValue);
        auto fractionDigits = static_cast<int32_t>(fraction.size());
        while (fractionDigits < 9) {
            (nanos = (nanos * 10LL));
            (fractionDigits = (fractionDigits + 1));
        }
    }
    if ((seconds > 9223372036LL) || ((seconds == 9223372036LL) && (nanos > 854775807LL))) {
        return doof::Failure<std::string>{ std::string("tar read failed: PAX mtime is out of range") };
    }
    const auto magnitude = ((seconds * 1000000000LL) + nanos);
    const auto epochNanos = (negative ? -magnitude : magnitude);
    return doof::Success<std::shared_ptr<::std_::time::temporal::Instant>>{ ::std_::time::temporal::Instant::ofEpochNanos(epochNanos) };
}
doof::Result<void, std::string> parsePaxRecords(const std::shared_ptr<std::vector<uint8_t>>& data, int64_t offset, int64_t size, const std::shared_ptr<doof::ordered_map<std::string, std::string>>& values) {
    const auto end = (offset + size);
    auto position = offset;
    while (position < end) {
        auto lengthEnd = position;
        while ((lengthEnd < end) && (doof::array_at(data, static_cast<int32_t>(lengthEnd), "tar_reader", 229) != 32)) {
            const auto character = doof::array_at(data, static_cast<int32_t>(lengthEnd), "tar_reader", 230);
            if ((character < 48) || (character > 57)) {
                return doof::Failure<std::string>{ std::string("tar read failed: invalid PAX record length") };
            }
            (lengthEnd = (lengthEnd + 1LL));
        }
        if ((lengthEnd == position) || (lengthEnd >= end)) {
            return doof::Failure<std::string>{ std::string("tar read failed: invalid PAX record length") };
        }
        auto _try_value_8 = readTextField(data, position, (lengthEnd - position), std::string("PAX record length"));
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
        const auto lengthText = doof::success_value(_try_value_8);
        auto _try_value_9 = parseDecimal(lengthText, std::string("record length"));
        if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
        const auto recordLength = doof::success_value(_try_value_9);
        if ((recordLength <= ((lengthEnd - position) + 2LL)) || (recordLength > (end - position))) {
            return doof::Failure<std::string>{ std::string("tar read failed: invalid PAX record bounds") };
        }
        const auto recordEnd = (position + recordLength);
        if (doof::array_at(data, static_cast<int32_t>((recordEnd - 1LL)), "tar_reader", 246) != 10) {
            return doof::Failure<std::string>{ std::string("tar read failed: PAX record is missing newline") };
        }
        const auto contentStart = (lengthEnd + 1LL);
        auto equals = contentStart;
        while ((equals < (recordEnd - 1LL)) && (doof::array_at(data, static_cast<int32_t>(equals), "tar_reader", 252) != 61)) {
            (equals = (equals + 1LL));
        }
        if ((equals == contentStart) || (equals >= (recordEnd - 1LL))) {
            return doof::Failure<std::string>{ std::string("tar read failed: invalid PAX key/value record") };
        }
        const auto keyBytes = doof::array_slice(data, static_cast<int32_t>(contentStart), static_cast<int32_t>(equals), "", 0);
        const auto valueBytes = doof::array_slice(data, static_cast<int32_t>((equals + 1LL)), static_cast<int32_t>((recordEnd - 1LL)), "", 0);
        auto _binding_value_10 = ::std_::blob::index::decodeUtf8(keyBytes);
        if (doof::is_failure(_binding_value_10)) {
            const auto& key = _binding_value_10;
            return doof::Failure<std::string>{ std::string("tar read failed: invalid UTF-8 in PAX key") };
        }
        const auto key = doof::success_value(_binding_value_10);
        auto _binding_value_11 = ::std_::blob::index::decodeUtf8(valueBytes);
        if (doof::is_failure(_binding_value_11)) {
            const auto& value = _binding_value_11;
            return doof::Failure<std::string>{ std::string("tar read failed: invalid UTF-8 in PAX value") };
        }
        const auto value = doof::success_value(_binding_value_11);
        doof::map_set(values, key, value, "", 0);
        (position = recordEnd);
    }
    return doof::Success<void>{};
}
std::optional<std::string> paxValue(const std::shared_ptr<doof::ordered_map<std::string, std::string>>& local, const std::shared_ptr<doof::ordered_map<std::string, std::string>>& global, const std::string& key) {
    return [&]() -> std::optional<std::string> {
    auto _case_subject = doof::map_get(local, key, "", 0);
    if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
        const auto& found = std::get<doof::Success<std::string>>(_case_subject);
        return found.value;
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        return [&]() -> std::optional<std::string> {
    auto _case_subject = doof::map_get(global, key, "", 0);
    if (std::holds_alternative<doof::Success<std::string>>(_case_subject)) {
        const auto& found = std::get<doof::Success<std::string>>(_case_subject);
        return found.value;
    }
    if (std::holds_alternative<doof::Failure<std::string>>(_case_subject)) {
        return std::nullopt;
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
    }
    throw std::runtime_error("non-exhaustive case expression");
}();
}
doof::Result<int64_t, std::string> alignedPayloadEnd(int64_t contentOffset, int64_t size, int64_t dataLength) {
    if ((((size < 0LL) || (contentOffset < 0LL)) || (contentOffset > dataLength)) || (size > (dataLength - contentOffset))) {
        return doof::Failure<std::string>{ std::string("tar read failed: truncated entry payload") };
    }
    const auto payloadEnd = (contentOffset + size);
    const auto padding = ((TAR_BLOCK_SIZE - (size % TAR_BLOCK_SIZE)) % TAR_BLOCK_SIZE);
    if (padding > (dataLength - payloadEnd)) {
        return doof::Failure<std::string>{ std::string("tar read failed: truncated entry padding") };
    }
    return doof::Success<int64_t>{ (payloadEnd + padding) };
}
doof::Result<std::shared_ptr<::std_::archive::types::TarArchive>, std::string> readTarBlob(const std::shared_ptr<std::vector<uint8_t>>& data) {
    if ((static_cast<int64_t>(static_cast<int32_t>((data)->size())) < (TAR_BLOCK_SIZE * 2LL)) || ((static_cast<int64_t>(static_cast<int32_t>((data)->size())) % TAR_BLOCK_SIZE) != 0LL)) {
        return doof::Failure<std::string>{ std::string("tar read failed: archive must contain complete 512-byte blocks") };
    }
    auto offset = 0LL;
    std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>> entries = std::make_shared<std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>>(std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>{});
    const std::shared_ptr<doof::ordered_map<std::string, std::string>> globalPax = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    std::shared_ptr<doof::ordered_map<std::string, std::string>> localPax = std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{});
    while ((offset + TAR_BLOCK_SIZE) <= static_cast<int64_t>(static_cast<int32_t>((data)->size()))) {
        if (isZeroRange(data, offset, TAR_BLOCK_SIZE)) {
            if (((offset + (TAR_BLOCK_SIZE * 2LL)) > static_cast<int64_t>(static_cast<int32_t>((data)->size()))) || !isZeroRange(data, (offset + TAR_BLOCK_SIZE), TAR_BLOCK_SIZE)) {
                return doof::Failure<std::string>{ std::string("tar read failed: archive terminator requires two zero blocks") };
            }
            if (!isZeroRange(data, (offset + (TAR_BLOCK_SIZE * 2LL)), ((static_cast<int64_t>(static_cast<int32_t>((data)->size())) - offset) - (TAR_BLOCK_SIZE * 2LL)))) {
                return doof::Failure<std::string>{ std::string("tar read failed: non-zero data follows archive terminator") };
            }
            return doof::Success<std::shared_ptr<::std_::archive::types::TarArchive>>{ std::make_shared<::std_::archive::types::TarArchive>(data, doof::array_drainToReadonly(entries, "", 0)) };
        }
        auto _try_value_12 = validateHeader(data, offset);
        if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
        auto _try_value_13 = readHeaderName(data, offset);
        if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
        const auto baseName = doof::success_value(_try_value_13);
        auto _try_value_14 = parseOctalField(data, (offset + TAR_MODE_OFFSET), TAR_MODE_LENGTH, std::string("entry mode"));
        if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
        const auto baseMode = doof::success_value(_try_value_14);
        auto _try_value_15 = parseOctalField(data, (offset + TAR_SIZE_OFFSET), TAR_SIZE_LENGTH, std::string("entry size"));
        if (doof::is_failure(_try_value_15)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_15))};
        const auto baseSize = doof::success_value(_try_value_15);
        auto _try_value_16 = parseOctalField(data, (offset + TAR_MTIME_OFFSET), TAR_MTIME_LENGTH, std::string("entry modification time"));
        if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_16))};
        const auto baseMtime = doof::success_value(_try_value_16);
        if (baseMode > 2147483647LL) {
            return doof::Failure<std::string>{ std::string("tar read failed: entry mode is out of range") };
        }
        if (baseMtime > 9223372036LL) {
            return doof::Failure<std::string>{ std::string("tar read failed: entry modification time is out of range") };
        }
        const auto typeFlag = doof::array_at(data, static_cast<int32_t>((offset + TAR_TYPE_OFFSET)), "tar_reader", 327);
        const auto contentOffset = (offset + TAR_BLOCK_SIZE);
        auto _try_value_17 = alignedPayloadEnd(contentOffset, baseSize, static_cast<int64_t>(static_cast<int32_t>((data)->size())));
        if (doof::is_failure(_try_value_17)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_17))};
        const auto nextOffset = doof::success_value(_try_value_17);
        if ((typeFlag == 120) || (typeFlag == 103)) {
            const auto target = ((typeFlag == 103) ? globalPax : localPax);
            auto _try_value_18 = parsePaxRecords(data, contentOffset, baseSize, target);
            if (doof::is_failure(_try_value_18)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_18))};
            (offset = nextOffset);
            continue;
        }
        const auto pathValue = paxValue(localPax, globalPax, std::string("path"));
        const auto resolvedName = (doof::is_null(pathValue) ? baseName : pathValue.value());
        auto _try_value_19 = readTextField(data, (offset + TAR_LINK_NAME_OFFSET), TAR_LINK_NAME_LENGTH, std::string("entry link name"));
        if (doof::is_failure(_try_value_19)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_19))};
        const auto baseLinkName = doof::success_value(_try_value_19);
        const auto linkPathValue = paxValue(localPax, globalPax, std::string("linkpath"));
        const auto resolvedLinkName = (doof::is_null(linkPathValue) ? baseLinkName : linkPathValue.value());
        const auto sizeText = paxValue(localPax, globalPax, std::string("size"));
        auto resolvedSize = baseSize;
        if (!doof::is_null(sizeText)) {
            auto _try_value_20 = parseDecimal(sizeText.value(), std::string("size"));
            if (doof::is_failure(_try_value_20)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_20))};
            const auto parsedSize = doof::success_value(_try_value_20);
            (resolvedSize = parsedSize);
        }
        auto resolvedNextOffset = nextOffset;
        if (resolvedSize != baseSize) {
            auto _try_value_21 = alignedPayloadEnd(contentOffset, resolvedSize, static_cast<int64_t>(static_cast<int32_t>((data)->size())));
            if (doof::is_failure(_try_value_21)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_21))};
            const auto updatedOffset = doof::success_value(_try_value_21);
            (resolvedNextOffset = updatedOffset);
        }
        const auto mtimeText = paxValue(localPax, globalPax, std::string("mtime"));
        auto resolvedMtime = ::std_::time::temporal::Instant::ofEpochSeconds(baseMtime);
        if (!doof::is_null(mtimeText)) {
            auto _try_value_22 = parsePaxMtime(mtimeText.value());
            if (doof::is_failure(_try_value_22)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_22))};
            const auto parsedMtime = doof::success_value(_try_value_22);
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
doof::Result<std::shared_ptr<::std_::archive::types::TarArchive>, std::string> readTarFile(const std::string& path) {
    auto _binding_value_23 = ::doof_fs::readBlob(path);
    if (doof::is_failure(_binding_value_23)) {
        const auto error = doof::failure_error(_binding_value_23);
        return doof::Failure<std::string>{ (std::string("tar file read failed: ") + ioErrorText(error)) };
    }
    const auto bytes = doof::success_value(_binding_value_23);
    if (isGzipTarPath(path)) {
        auto _binding_value_24 = ::doof_gzip::gunzip(bytes);
        if (doof::is_failure(_binding_value_24)) {
            const auto error = doof::failure_error(_binding_value_24);
            return doof::Failure<std::string>{ (std::string("tar file read failed: ") + error) };
        }
        const auto decoded = doof::success_value(_binding_value_24);
        return readTarBlob(decoded);
    }
    return readTarBlob(bytes);
}
}
