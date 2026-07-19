#include "std_stream_index.hpp"
#include <cmath>
#include "std_blob_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"

namespace std_::stream::index {
using namespace ::std_::blob::index;





bool DecodedLineStream::loadNextChunk() {
    if (this->sourceDone) {
        return false;
    }
    if (!std::visit([&](auto&& _obj) { return _obj->next(); }, this->source)) {
        (this->sourceDone = true);
        return false;
    }
    const auto chunk = std::visit([&](auto&& _obj) { return _obj->value(); }, this->source);
    (this->current = ::doof_blob::NativeBlobReader::constructor(chunk, ::std_::blob::types::Endian::LittleEndian));
    return true;
}
void DecodedLineStream::skipLeadingLineFeed() {
    if (!this->skipLeadingLf || (this->current->remaining() == 0LL)) {
        return;
    }
    const auto nextPosition = this->current->getPosition();
    if (this->current->readByte() != 10) {
        this->current->setPosition(nextPosition);
    }
    (this->skipLeadingLf = false);
}
std::string DecodedLineStream::finishPendingLine() {
    const auto lineBytes = this->pendingLine->build();
    const auto lineReader = ::doof_blob::NativeBlobReader::constructor(lineBytes, ::std_::blob::types::Endian::LittleEndian);
    return lineReader->readString(lineReader->remaining());
}
std::optional<std::string> DecodedLineStream::flushTrailingLine() {
    const auto remaining = this->current->remaining();
    if (remaining > 0LL) {
        if (this->pendingLine->length() == 0LL) {
            return this->current->readString(remaining);
        }
        this->pendingLine->writeBytes(this->current->readBytes(remaining));
    }
    if (this->pendingLine->length() == 0LL) {
        return std::nullopt;
    }
    return finishPendingLine();
}
std::optional<std::string> DecodedLineStream::tryTakeCurrentLine() {
    if (this->current->remaining() == 0LL) {
        return std::nullopt;
    }
    const auto startPosition = this->current->getPosition();
    auto _binding_value_1 = this->current->findNextAny(this->lineBreakBytes);
    if (doof::is_null(_binding_value_1)) {
        const auto& delimiterIndex = _binding_value_1;
        return std::nullopt;
    }
    const auto delimiterIndex = doof::unwrap_optional(_binding_value_1);
    const auto lineLength = (delimiterIndex - startPosition);
    if (this->pendingLine->length() == 0LL) {
        const auto line = this->current->readString(lineLength);
        if (this->current->readByte() == 13) {
            (this->skipLeadingLf = true);
        }
        return line;
    }
    if (lineLength > 0LL) {
        this->pendingLine->writeBytes(this->current->readBytes(lineLength));
    }
    const auto line = finishPendingLine();
    if (this->current->readByte() == 13) {
        (this->skipLeadingLf = true);
    }
    return line;
}
void DecodedLineStream::moveCurrentRemainderToPending() {
    const auto remaining = this->current->remaining();
    if (remaining > 0LL) {
        this->pendingLine->writeBytes(this->current->readBytes(remaining));
    }
}
bool DecodedLineStream::next() {
    while (true) {
        skipLeadingLineFeed();
        const auto candidate = tryTakeCurrentLine();
        if (!doof::is_null(candidate)) {
            (this->currentValue = candidate);
            return true;
        }
        if (this->sourceDone) {
            const auto trailing = flushTrailingLine();
            if (doof::is_null(trailing)) {
                return false;
            }
            (this->currentValue = trailing);
            return true;
        }
        moveCurrentRemainderToPending();
        if (!loadNextChunk()) {
            const auto trailing = flushTrailingLine();
            if (doof::is_null(trailing)) {
                return false;
            }
            (this->currentValue = trailing);
            return true;
        }
    }
}
std::string DecodedLineStream::value() {
    return this->currentValue.value();
}
Stream__string blobStreamToLineStream(Stream__readonly_array_byte source) {
    Stream__string stream = std::make_shared<DecodedLineStream>(source, ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian), ::doof_blob::NativeBlobReader::constructor(std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), ::std_::blob::types::Endian::LittleEndian), std::nullopt, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{10, 13}), false, false);
    return stream;
}
}
