#include "std_json_index.hpp"

namespace std_::json::index {
#line 7 "/std/json/index.do"
doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> parseJsonObject(const std::string& text) {
#line 8 "/std/json/index.do"
    auto _try_value_1 = ::doof_json::parse(text);
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
    const auto result = doof::success_value(_try_value_1);
#line 9 "/std/json/index.do"
    {
        auto _case_subject = result;
        if (doof::json_is_object(_case_subject)) {
            const auto o = doof::json_object(_case_subject);
#line 10 "/std/json/index.do"
            return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{ o };
    }
    else {
#line 11 "/std/json/index.do"
            return doof::Failure<std::string>{ std::string("Parsed value is not a JSON object") };
    }
    }
    doof::unreachable();
}
#line 1 "<doof-generated>"
doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text) {
    return ::doof_json::parse(text);
}
std::string formatJsonValue(const doof::JsonValue& value) {
    return ::doof_json::format(value);
}
}
