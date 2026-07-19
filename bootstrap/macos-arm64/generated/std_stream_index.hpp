#pragma once
#include "doof_runtime.hpp"
#include <cstdint>
#include <cmath>
#include <functional>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>
namespace std_::blob::index { struct BlobReader; }
namespace std_::blob::index { struct BlobBuilder; }
namespace std_::fs::index { struct BlockReadStream; }
namespace std_::http::index { struct BodyChunkStream; }
namespace std_::os::index { struct ExecStdoutStream; }
namespace std_::os::index { struct ExecStderrStream; }

namespace std_::stream::index {
    struct DecodedLineStream;
}

#include "std_blob_index.hpp"

namespace std_::stream::index {
    using Stream__readonly_array_byte = std::variant<std::shared_ptr<::std_::fs::index::BlockReadStream>, std::shared_ptr<::std_::http::index::BodyChunkStream>, std::shared_ptr<::std_::os::index::ExecStdoutStream>, std::shared_ptr<::std_::os::index::ExecStderrStream>>;
    using Stream__string = std::variant<std::shared_ptr<DecodedLineStream>>;
    struct DecodedLineStream : public std::enable_shared_from_this<DecodedLineStream> {
    Stream__readonly_array_byte source;
    std::shared_ptr<::doof_blob::NativeBlobBuilder> pendingLine = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian);
    std::shared_ptr<::doof_blob::NativeBlobReader> current = ::doof_blob::NativeBlobReader::constructor(std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), ::std_::blob::types::Endian::LittleEndian);
    std::optional<std::string> currentValue = std::nullopt;
    std::shared_ptr<std::vector<uint8_t>> lineBreakBytes = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{10, 13});
    bool sourceDone = false;
    bool skipLeadingLf = false;
    DecodedLineStream(Stream__readonly_array_byte source, std::shared_ptr<::doof_blob::NativeBlobBuilder> pendingLine = ::doof_blob::NativeBlobBuilder::constructor(0LL, ::std_::blob::types::Endian::LittleEndian), std::shared_ptr<::doof_blob::NativeBlobReader> current = ::doof_blob::NativeBlobReader::constructor(std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{}), ::std_::blob::types::Endian::LittleEndian), std::optional<std::string> currentValue = std::nullopt, std::shared_ptr<std::vector<uint8_t>> lineBreakBytes = std::make_shared<std::vector<uint8_t>>(std::vector<uint8_t>{10, 13}), bool sourceDone = false, bool skipLeadingLf = false) : source(source), pendingLine(pendingLine), current(current), currentValue(currentValue), lineBreakBytes(lineBreakBytes), sourceDone(sourceDone), skipLeadingLf(skipLeadingLf) {}
    bool loadNextChunk();
    void skipLeadingLineFeed();
    std::string finishPendingLine();
    std::optional<std::string> flushTrailingLine();
    std::optional<std::string> tryTakeCurrentLine();
    void moveCurrentRemainderToPending();
    bool next();
    std::string value();
};
    Stream__string blobStreamToLineStream(Stream__readonly_array_byte source);
}

namespace std_::stream::index {
}
