#include "std_url_punycode_error.hpp"

namespace std_::url::punycode_error {

doof::Result<std::string, std::shared_ptr<PunycodeError>> punycodeFailure__string(const std::string& kind, int32_t index, const std::string& message) {
    return doof::Failure<std::shared_ptr<PunycodeError>>{ std::make_shared<PunycodeError>(kind, index, message) };
}
doof::Result<std::shared_ptr<std::vector<int32_t>>, std::shared_ptr<PunycodeError>> punycodeFailure__array_int(const std::string& kind, int32_t index, const std::string& message) {
    return doof::Failure<std::shared_ptr<PunycodeError>>{ std::make_shared<PunycodeError>(kind, index, message) };
}
}
