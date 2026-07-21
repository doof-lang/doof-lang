#include "std_json_index.hpp"
#include <cmath>
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace std_::json::index {
doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> parseJsonObject(std::string text) {
    auto _try_value_1 = ::doof_json::parse(text);
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::failure_error(_try_value_1)};
    const auto result = doof::success_value(_try_value_1);
    {
        auto _case_subject = result;
        if (doof::json_is_object(_case_subject)) {
            const auto o = doof::json_object(_case_subject);
            return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{ o };
    }
    else {
            return doof::Failure<std::string>{ std::string("Parsed value is not a JSON object") };
    }
    }
}
doof::Result<doof::JsonValue, std::string> parseJsonValue(std::string text) {
    return ::doof_json::parse(text);
}
std::string formatJsonValue(doof::JsonValue value) {
    return ::doof_json::format(value);
}
}
