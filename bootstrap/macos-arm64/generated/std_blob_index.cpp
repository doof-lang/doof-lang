#include "std_blob_index.hpp"

namespace std_::blob::index {
#line 54 "/std/blob/index.do"
doof::Result<std::string, ::std_::blob::types::EncodingError> decodeUtf8(const std::shared_ptr<std::vector<uint8_t>>& data) {
#line 55 "/std/blob/index.do"
    const auto reader = ::doof_blob::NativeBlobReader::constructor(data, ::std_::blob::types::Endian::LittleEndian);
#line 56 "/std/blob/index.do"
    return reader->readText(static_cast<int32_t>((data)->size()), ::std_::blob::types::TextEncoding::Utf8);
}
#line 1 "<doof-generated>"
}
