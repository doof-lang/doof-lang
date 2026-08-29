#include "std_json_index.hpp"

namespace std_::json::index {
doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> parseJsonObject(const std::string& text) {
    auto _try_value_1 = ::doof_json::parse(text);
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
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
    doof::unreachable();
}
}
