#include "std_blob_index.hpp"
#include <cmath>
#include "std_blob_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::blob::index {
doof::Result<std::string, ::std_::blob::types::EncodingError> decodeUtf8(std::shared_ptr<std::vector<uint8_t>> data) {
    const auto reader = ::doof_blob::NativeBlobReader::constructor(data, ::std_::blob::types::Endian::LittleEndian);
    return reader->readText(static_cast<int32_t>((data)->size()), ::std_::blob::types::TextEncoding::Utf8);
}
}
