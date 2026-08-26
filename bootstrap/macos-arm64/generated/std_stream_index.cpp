#include "std_stream_index.hpp"

namespace std_::stream::index {
using namespace ::std_::blob::index;





#line 79 "/std/stream/index.do"
bool DecodedLineStream::loadNextChunk() {
#line 80 "/std/stream/index.do"
    if (this->sourceDone) {
#line 81 "/std/stream/index.do"
        return false;
    }
#line 84 "/std/stream/index.do"
    if (!std::visit([&](auto&& _obj) { return _obj->next(); }, this->source)) {
#line 85 "/std/stream/index.do"
        (this->sourceDone = true);
#line 86 "/std/stream/index.do"
        return false;
    }
#line 88 "/std/stream/index.do"
    const auto chunk = std::visit([&](auto&& _obj) { return _obj->value(); }, this->source);
#line 90 "/std/stream/index.do"
    (this->current = ::doof_blob::NativeBlobReader::constructor(chunk, ::std_::blob::types::Endian::LittleEndian));
#line 91 "/std/stream/index.do"
    return true;
}
#line 94 "/std/stream/index.do"
void DecodedLineStream::skipLeadingLineFeed() {
#line 95 "/std/stream/index.do"
    if (!this->skipLeadingLf || (this->current->remaining() == 0LL)) {
#line 96 "/std/stream/index.do"
        return;
    }
#line 99 "/std/stream/index.do"
    const auto nextPosition = this->current->getPosition();
#line 100 "/std/stream/index.do"
    if (this->current->readByte() != 10) {
#line 101 "/std/stream/index.do"
        this->current->setPosition(nextPosition);
    }
#line 103 "/std/stream/index.do"
    (this->skipLeadingLf = false);
}
#line 106 "/std/stream/index.do"
std::string DecodedLineStream::finishPendingLine() {
#line 107 "/std/stream/index.do"
    const auto lineBytes = this->pendingLine->build();
#line 108 "/std/stream/index.do"
    const auto lineReader = ::doof_blob::NativeBlobReader::constructor(lineBytes, ::std_::blob::types::Endian::LittleEndian);
#line 109 "/std/stream/index.do"
    return lineReader->readString(lineReader->remaining());
}
#line 112 "/std/stream/index.do"
std::optional<std::string> DecodedLineStream::flushTrailingLine() {
#line 113 "/std/stream/index.do"
    const auto remaining = this->current->remaining();
#line 114 "/std/stream/index.do"
    if (remaining > 0LL) {
#line 115 "/std/stream/index.do"
        if (this->pendingLine->length() == 0LL) {
#line 116 "/std/stream/index.do"
            return this->current->readString(remaining);
        }
#line 119 "/std/stream/index.do"
        this->pendingLine->writeBytes(this->current->readBytes(remaining));
    }
#line 122 "/std/stream/index.do"
    if (this->pendingLine->length() == 0LL) {
#line 123 "/std/stream/index.do"
        return std::nullopt;
    }
#line 126 "/std/stream/index.do"
    return finishPendingLine();
}
#line 129 "/std/stream/index.do"
std::optional<std::string> DecodedLineStream::tryTakeCurrentLine() {
#line 130 "/std/stream/index.do"
    if (this->current->remaining() == 0LL) {
#line 131 "/std/stream/index.do"
        return std::nullopt;
    }
#line 134 "/std/stream/index.do"
    const auto startPosition = this->current->getPosition();
#line 135 "/std/stream/index.do"
    auto _binding_value_1 = this->current->findNextAny(this->lineBreakBytes);
    if (doof::is_null(_binding_value_1)) {
        const auto& delimiterIndex = _binding_value_1;
#line 136 "/std/stream/index.do"
        return std::nullopt;
    }
    const auto delimiterIndex = doof::unwrap_optional(_binding_value_1);
#line 139 "/std/stream/index.do"
    const auto lineLength = (delimiterIndex - startPosition);
#line 140 "/std/stream/index.do"
    if (this->pendingLine->length() == 0LL) {
#line 141 "/std/stream/index.do"
        const auto line = this->current->readString(lineLength);
#line 142 "/std/stream/index.do"
        if (this->current->readByte() == 13) {
#line 143 "/std/stream/index.do"
            (this->skipLeadingLf = true);
        }
#line 145 "/std/stream/index.do"
        return line;
    }
#line 148 "/std/stream/index.do"
    if (lineLength > 0LL) {
#line 149 "/std/stream/index.do"
        this->pendingLine->writeBytes(this->current->readBytes(lineLength));
    }
#line 152 "/std/stream/index.do"
    const auto line = finishPendingLine();
#line 153 "/std/stream/index.do"
    if (this->current->readByte() == 13) {
#line 154 "/std/stream/index.do"
        (this->skipLeadingLf = true);
    }
#line 157 "/std/stream/index.do"
    return line;
}
#line 160 "/std/stream/index.do"
void DecodedLineStream::moveCurrentRemainderToPending() {
#line 161 "/std/stream/index.do"
    const auto remaining = this->current->remaining();
#line 162 "/std/stream/index.do"
    if (remaining > 0LL) {
#line 163 "/std/stream/index.do"
        this->pendingLine->writeBytes(this->current->readBytes(remaining));
    }
}
#line 167 "/std/stream/index.do"
bool DecodedLineStream::next() {
#line 168 "/std/stream/index.do"
    while (true) {
#line 169 "/std/stream/index.do"
        skipLeadingLineFeed();
#line 171 "/std/stream/index.do"
        const auto candidate = tryTakeCurrentLine();
#line 172 "/std/stream/index.do"
        if (!doof::is_null(candidate)) {
#line 173 "/std/stream/index.do"
            (this->currentValue = candidate);
#line 174 "/std/stream/index.do"
            return true;
        }
#line 177 "/std/stream/index.do"
        if (this->sourceDone) {
#line 178 "/std/stream/index.do"
            const auto trailing = flushTrailingLine();
#line 179 "/std/stream/index.do"
            if (doof::is_null(trailing)) {
#line 180 "/std/stream/index.do"
                return false;
            }
#line 182 "/std/stream/index.do"
            (this->currentValue = trailing);
#line 183 "/std/stream/index.do"
            return true;
        }
#line 186 "/std/stream/index.do"
        moveCurrentRemainderToPending();
#line 188 "/std/stream/index.do"
        if (!loadNextChunk()) {
#line 189 "/std/stream/index.do"
            const auto trailing = flushTrailingLine();
#line 190 "/std/stream/index.do"
            if (doof::is_null(trailing)) {
#line 191 "/std/stream/index.do"
                return false;
            }
#line 193 "/std/stream/index.do"
            (this->currentValue = trailing);
#line 194 "/std/stream/index.do"
            return true;
        }
    }
}
#line 199 "/std/stream/index.do"
std::string DecodedLineStream::value() {
    return this->currentValue.value();
}
#line 202 "/std/stream/index.do"
Stream__string blobStreamToLineStream(const Stream__readonly_array_byte& source) {
#line 203 "/std/stream/index.do"
    Stream__string stream = std::make_shared<DecodedLineStream>(source, ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian), ::doof_blob::NativeBlobReader::constructor(std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), ::std_::blob::types::Endian::LittleEndian), std::nullopt, std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{10, 13}), false, false);
#line 206 "/std/stream/index.do"
    return stream;
}
#line 1 "<doof-generated>"
}
