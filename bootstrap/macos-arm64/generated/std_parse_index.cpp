#include "std_parse_index.hpp"

namespace std_::parse::index {
doof::Result<int32_t, ::std_::parse::types::ParsingError> parseInt(const std::string& value) {
    return ::doof_parse::parseInt(value);
}
}
