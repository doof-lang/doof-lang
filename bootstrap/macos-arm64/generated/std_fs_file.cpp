#include "std_fs_file.hpp"

namespace std_::fs::file {
using namespace ::std_::blob::index;
using namespace ::std_::fs::types;

doof::Result<std::shared_ptr<File>, ::std_::fs::types::IoError> File::constructor(const std::string& path, ::std_::fs::types::FileMode mode, bool create, ::std_::fs::types::FileLock lock, bool waitForLock, ::std_::blob::types::Endian endianness) {
    auto _try_value_1 = ::doof_fs::NativeFile::open(path, mode, create, lock, waitForLock);
    if (doof::is_failure(_try_value_1)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_1))};
    const auto native = doof::success_value(_try_value_1);
    return doof::Success<std::shared_ptr<File>>{ std::make_shared<File>(native, endianness) };
}
doof::Result<int64_t, ::std_::fs::types::IoError> File::getPosition() {
    return this->native->getPosition();
}
doof::Result<void, ::std_::fs::types::IoError> File::setPosition(int64_t position) {
    return this->native->setPosition(position);
}
doof::Result<int64_t, ::std_::fs::types::IoError> File::length() {
    return this->native->length();
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> File::readBytes(int64_t length) {
    return this->native->readBytes(length, true);
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, ::std_::fs::types::IoError> File::readUpTo(int64_t length) {
    return this->native->readBytes(length, false);
}
doof::Result<void, ::std_::fs::types::IoError> File::writeBytes(const std::shared_ptr<std::vector<uint8_t>>& data) {
    return this->native->writeBytes(data);
}
doof::Result<void, ::std_::fs::types::IoError> File::truncate(int64_t length) {
    return this->native->truncate(length);
}
doof::Result<void, ::std_::fs::types::IoError> File::flush() {
    return this->native->flush();
}
doof::Result<void, ::std_::fs::types::IoError> File::close() {
    return this->native->close();
}
doof::Result<int64_t, ::std_::fs::types::IoError> File::remaining() {
    auto _try_value_2 = length();
    if (doof::is_failure(_try_value_2)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_2))};
    const auto size = doof::success_value(_try_value_2);
    auto _try_value_3 = getPosition();
    if (doof::is_failure(_try_value_3)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_3))};
    const auto position = doof::success_value(_try_value_3);
    return doof::Success<int64_t>{ ((position < size) ? (size - position) : 0LL) };
}
doof::Result<std::shared_ptr<::doof_blob::NativeBlobReader>, ::std_::fs::types::IoError> File::reader(int64_t length) {
    auto _try_value_4 = readBytes(length);
    if (doof::is_failure(_try_value_4)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_4))};
    const auto data = doof::success_value(_try_value_4);
    return doof::Success<std::shared_ptr<::doof_blob::NativeBlobReader>>{ ::doof_blob::NativeBlobReader::constructor(data, this->endianness) };
}
doof::Result<uint8_t, ::std_::fs::types::IoError> File::readByte() {
    auto _try_value_5 = reader(1LL);
    if (doof::is_failure(_try_value_5)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_5))};
    const auto value = doof::success_value(_try_value_5);
    return doof::Success<uint8_t>{ value->readByte() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeByte(uint8_t value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeByte(value);
    return writeBytes(builder->build());
}
doof::Result<int32_t, ::std_::fs::types::IoError> File::readSignedByte() {
    auto _try_value_6 = reader(1LL);
    if (doof::is_failure(_try_value_6)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_6))};
    const auto value = doof::success_value(_try_value_6);
    return doof::Success<int32_t>{ value->readSignedByte() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeSignedByte(int32_t value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeSignedByte(value);
    return writeBytes(builder->build());
}
doof::Result<bool, ::std_::fs::types::IoError> File::readBool() {
    auto _try_value_7 = reader(1LL);
    if (doof::is_failure(_try_value_7)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_7))};
    const auto value = doof::success_value(_try_value_7);
    return doof::Success<bool>{ value->readBool() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeBool(bool value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeBool(value);
    return writeBytes(builder->build());
}
doof::Result<int32_t, ::std_::fs::types::IoError> File::readShort() {
    auto _try_value_8 = reader(2LL);
    if (doof::is_failure(_try_value_8)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_8))};
    const auto value = doof::success_value(_try_value_8);
    return doof::Success<int32_t>{ value->readShort() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeShort(int32_t value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeShort(value);
    return writeBytes(builder->build());
}
doof::Result<int32_t, ::std_::fs::types::IoError> File::readUnsignedShort() {
    auto _try_value_9 = reader(2LL);
    if (doof::is_failure(_try_value_9)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_9))};
    const auto value = doof::success_value(_try_value_9);
    return doof::Success<int32_t>{ value->readUnsignedShort() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeUnsignedShort(int32_t value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeUnsignedShort(value);
    return writeBytes(builder->build());
}
doof::Result<int32_t, ::std_::fs::types::IoError> File::readInt() {
    auto _try_value_10 = reader(4LL);
    if (doof::is_failure(_try_value_10)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_10))};
    const auto value = doof::success_value(_try_value_10);
    return doof::Success<int32_t>{ value->readInt() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeInt(int32_t value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeInt(value);
    return writeBytes(builder->build());
}
doof::Result<int64_t, ::std_::fs::types::IoError> File::readUnsignedInt() {
    auto _try_value_11 = reader(4LL);
    if (doof::is_failure(_try_value_11)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_11))};
    const auto value = doof::success_value(_try_value_11);
    return doof::Success<int64_t>{ value->readUnsignedInt() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeUnsignedInt(int64_t value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeUnsignedInt(value);
    return writeBytes(builder->build());
}
doof::Result<int64_t, ::std_::fs::types::IoError> File::readLong() {
    auto _try_value_12 = reader(8LL);
    if (doof::is_failure(_try_value_12)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_12))};
    const auto value = doof::success_value(_try_value_12);
    return doof::Success<int64_t>{ value->readLong() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeLong(int64_t value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeLong(value);
    return writeBytes(builder->build());
}
doof::Result<float, ::std_::fs::types::IoError> File::readFloat() {
    auto _try_value_13 = reader(4LL);
    if (doof::is_failure(_try_value_13)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_13))};
    const auto value = doof::success_value(_try_value_13);
    return doof::Success<float>{ value->readFloat() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeFloat(float value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeFloat(value);
    return writeBytes(builder->build());
}
doof::Result<double, ::std_::fs::types::IoError> File::readDouble() {
    auto _try_value_14 = reader(8LL);
    if (doof::is_failure(_try_value_14)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_14))};
    const auto value = doof::success_value(_try_value_14);
    return doof::Success<double>{ value->readDouble() };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeDouble(double value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeDouble(value);
    return writeBytes(builder->build());
}
doof::Result<std::string, ::std_::fs::types::IoError> File::readString(int64_t length) {
    auto _try_value_15 = reader(length);
    if (doof::is_failure(_try_value_15)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_15))};
    const auto value = doof::success_value(_try_value_15);
    return doof::Success<std::string>{ value->readString(length) };
}
doof::Result<void, ::std_::fs::types::IoError> File::writeString(const std::string& value) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    builder->writeString(value);
    return writeBytes(builder->build());
}
doof::Result<std::string, std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>> File::readText(int64_t length, ::std_::blob::types::TextEncoding encoding) {
    auto _try_value_16 = reader(length);
    if (doof::is_failure(_try_value_16)) return doof::Failure<std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>>{doof::variant_promote<std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>>(doof::failure_error(_try_value_16))};
    const auto value = doof::success_value(_try_value_16);
    auto _try_value_17 = value->readText(length, encoding);
    if (doof::is_failure(_try_value_17)) return doof::Failure<std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>>{doof::variant_promote<std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>>(doof::failure_error(_try_value_17))};
    const auto text = doof::success_value(_try_value_17);
    return doof::Success<std::string>{ text };
}
doof::Result<int32_t, std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>> File::writeText(const std::string& value, ::std_::blob::types::TextEncoding encoding) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    auto _try_value_18 = builder->writeText(value, encoding);
    if (doof::is_failure(_try_value_18)) return doof::Failure<std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>>{doof::variant_promote<std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>>(doof::failure_error(_try_value_18))};
    const auto count = doof::success_value(_try_value_18);
    auto _try_value_19 = writeBytes(builder->build());
    if (doof::is_failure(_try_value_19)) return doof::Failure<std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>>{doof::variant_promote<std::variant<::std_::fs::types::IoError, ::std_::blob::types::EncodingError>>(doof::failure_error(_try_value_19))};
    return doof::Success<int32_t>{ count };
}
doof::Result<std::string, ::std_::fs::types::IoError> File::readTextLossy(int64_t length, ::std_::blob::types::TextEncoding encoding) {
    auto _try_value_20 = reader(length);
    if (doof::is_failure(_try_value_20)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_20))};
    const auto value = doof::success_value(_try_value_20);
    return doof::Success<std::string>{ value->readTextLossy(length, encoding) };
}
doof::Result<int32_t, ::std_::fs::types::IoError> File::writeTextLossy(const std::string& value, ::std_::blob::types::TextEncoding encoding) {
    const auto builder = ::doof_blob::NativeBlobBuilder::constructor(0LL, this->endianness);
    const auto count = builder->writeTextLossy(value, encoding);
    auto _try_value_21 = writeBytes(builder->build());
    if (doof::is_failure(_try_value_21)) return doof::Failure<::std_::fs::types::IoError>{doof::variant_promote<::std_::fs::types::IoError>(doof::failure_error(_try_value_21))};
    return doof::Success<int32_t>{ count };
}
}
