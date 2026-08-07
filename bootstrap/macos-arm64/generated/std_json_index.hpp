#pragma once
#include "doof_runtime.hpp"
#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<doof::JsonValue, std::string> parseJsonValue(const std::string& text);
    std::string formatJsonValue(const doof::JsonValue& value);
    doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> parseJsonObject(const std::string& text);
}
