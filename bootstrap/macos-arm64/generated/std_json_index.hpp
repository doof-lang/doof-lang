#pragma once
#include "doof_runtime.hpp"
#include "std/json/native_json.hpp"

namespace std_::json::index {
    doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> parseJsonObject(const std::string& text);
}
