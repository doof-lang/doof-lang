#include "std_parse_index.hpp"
#include <cmath>
#include "std_parse_types.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::parse::index {
doof::Result<int32_t, ::std_::parse::types::ParsingError> parseInt(const std::string& value) {
    return ::doof_parse::parseInt(value);
}
}
