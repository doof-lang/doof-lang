#include "src_std_catalog.hpp"

namespace app_src_std_catalog_ {
using namespace ::std_::json::index;


#line 20 "/src/std-catalog.do"
std::string canonicalDependencyUrl(const std::string& value) {
#line 21 "/src/std-catalog.do"
    auto result = doof::string_trim(value);
#line 22 "/src/std-catalog.do"
    while (doof::string_endsWith(result, std::string("/"))) {
#line 22 "/src/std-catalog.do"
        (result = doof::string_substring(result, 0, (static_cast<int32_t>(result.size()) - 1)));
    }
#line 23 "/src/std-catalog.do"
    if (doof::string_endsWith(result, std::string(".git"))) {
#line 23 "/src/std-catalog.do"
        (result = doof::string_substring(result, 0, (static_cast<int32_t>(result.size()) - 4)));
    }
#line 24 "/src/std-catalog.do"
    const auto marker = doof::string_indexOf(result, std::string("://"));
#line 25 "/src/std-catalog.do"
    if (marker < 0) {
#line 25 "/src/std-catalog.do"
        return result;
    }
#line 26 "/src/std-catalog.do"
    const auto scheme = doof::string_toLowerCase(doof::string_substring(result, 0, marker));
#line 27 "/src/std-catalog.do"
    const auto remainder = doof::string_substring(result, (marker + 3), static_cast<int32_t>(result.size()));
#line 28 "/src/std-catalog.do"
    const auto slash = doof::string_indexOf(remainder, std::string("/"));
#line 29 "/src/std-catalog.do"
    if (slash < 0) {
#line 29 "/src/std-catalog.do"
        return ((scheme + std::string("://")) + doof::string_toLowerCase(remainder));
    }
#line 30 "/src/std-catalog.do"
    const auto host = doof::string_toLowerCase(doof::string_substring(remainder, 0, slash));
#line 31 "/src/std-catalog.do"
    return (((scheme + std::string("://")) + host) + doof::string_substring(remainder, slash, static_cast<int32_t>(remainder.size())));
}
#line 34 "/src/std-catalog.do"
doof::Result<std::shared_ptr<StdCatalog>, std::string> parseStdCatalog(const std::string& source) {
#line 35 "/src/std-catalog.do"
    auto _try_value_1 = ::doof_json::parse(source);
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
    const auto parsed = doof::success_value(_try_value_1);
#line 36 "/src/std-catalog.do"
    auto _binding_value_2 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = parsed; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_2)) {
        const auto& root = _binding_value_2;
#line 36 "/src/std-catalog.do"
        return doof::Failure<std::string>{ std::string("Invalid std catalog: root must be an object") };
    }
    const auto root = doof::success_value(_binding_value_2);
#line 37 "/src/std-catalog.do"
    auto _try_value_3 = catalogInt(root, std::string("schemaVersion"));
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_3))};
    const auto schemaVersion = doof::success_value(_try_value_3);
#line 38 "/src/std-catalog.do"
    if (schemaVersion != 1) {
#line 38 "/src/std-catalog.do"
        return doof::Failure<std::string>{ (std::string("Unsupported std catalog schema ") + doof::to_string(schemaVersion)) };
    }
#line 39 "/src/std-catalog.do"
    auto _try_value_4 = catalogString(root, std::string("compilerVersion"));
    if (doof::is_failure(_try_value_4)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_4))};
    const auto compilerVersion = doof::success_value(_try_value_4);
#line 40 "/src/std-catalog.do"
    auto _try_value_5 = catalogString(root, std::string("digest"));
    if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_5))};
    const auto digest = doof::success_value(_try_value_5);
#line 41 "/src/std-catalog.do"
    if (static_cast<int32_t>(digest.size()) != 64) {
#line 41 "/src/std-catalog.do"
        return doof::Failure<std::string>{ std::string("Invalid std catalog digest") };
    }
#line 42 "/src/std-catalog.do"
    const auto rawPackages = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(root, std::string("packages"), "", 0); if (doof::is_failure(_try_value)) doof::panic_at("src/std-catalog", 42, std::string("try! failed") + std::string(": ") + doof::failure_error(_try_value)); return std::move(doof::success_value(_try_value)); }();
#line 43 "/src/std-catalog.do"
    auto _binding_value_6 = [&]() -> doof::Result<std::shared_ptr<std::vector<doof::JsonValue>>, std::string> { auto _as_value = rawPackages; if (doof::json_is_array(_as_value)) return doof::Success<std::shared_ptr<std::vector<doof::JsonValue>>>{std::get<doof::JsonArray>(doof::json_storage(_as_value))}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_6)) {
        const auto& packages = _binding_value_6;
#line 43 "/src/std-catalog.do"
        return doof::Failure<std::string>{ std::string("Invalid std catalog: packages must be an array") };
    }
    const auto packages = doof::success_value(_binding_value_6);
#line 44 "/src/std-catalog.do"
    std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> result = std::make_shared<std::vector<std::shared_ptr<StdCatalogPackage>>>(std::vector<std::shared_ptr<StdCatalogPackage>>{});
#line 45 "/src/std-catalog.do"
    auto previous = std::string("");
#line 46 "/src/std-catalog.do"
    for (int32_t index = 0; index < static_cast<int32_t>((packages)->size()); ++index) {
#line 47 "/src/std-catalog.do"
        auto _binding_value_8 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = doof::array_at(packages, index, "src/std-catalog", 47); if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
        if (doof::is_failure(_binding_value_8)) {
            const auto& object = _binding_value_8;
#line 47 "/src/std-catalog.do"
            return doof::Failure<std::string>{ (std::string("Invalid std catalog package at index ") + doof::to_string(index)) };
        }
        const auto object = doof::success_value(_binding_value_8);
#line 48 "/src/std-catalog.do"
        auto _try_value_9 = catalogString(object, std::string("name"));
        if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_9))};
        const auto name = doof::success_value(_try_value_9);
#line 49 "/src/std-catalog.do"
        auto _try_value_10 = catalogString(object, std::string("url"));
        if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_10))};
        const auto url = doof::success_value(_try_value_10);
#line 50 "/src/std-catalog.do"
        auto _try_value_11 = catalogString(object, std::string("ref"));
        if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_11))};
        const auto ref = doof::success_value(_try_value_11);
#line 51 "/src/std-catalog.do"
        auto _try_value_12 = catalogString(object, std::string("version"));
        if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
        const auto version = doof::success_value(_try_value_12);
#line 52 "/src/std-catalog.do"
        auto _try_value_13 = catalogString(object, std::string("commit"));
        if (doof::is_failure(_try_value_13)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_13))};
        const auto commit = doof::success_value(_try_value_13);
#line 53 "/src/std-catalog.do"
        if (!doof::string_startsWith(name, std::string("std/")) || doof::string_contains(doof::string_substring(name, 4, static_cast<int32_t>(name.size())), std::string("/"))) {
#line 54 "/src/std-catalog.do"
            return doof::Failure<std::string>{ (std::string("Invalid std catalog package name ") + name) };
        }
#line 56 "/src/std-catalog.do"
        if (static_cast<int32_t>(commit.size()) != 40) {
#line 56 "/src/std-catalog.do"
            return doof::Failure<std::string>{ (std::string("Invalid std catalog commit for ") + name) };
        }
#line 57 "/src/std-catalog.do"
        if ((previous != std::string("")) && (name <= previous)) {
#line 57 "/src/std-catalog.do"
            return doof::Failure<std::string>{ std::string("Std catalog packages must be sorted and unique") };
        }
#line 58 "/src/std-catalog.do"
        (previous = name);
#line 59 "/src/std-catalog.do"
        result->push_back(std::make_shared<StdCatalogPackage>(name, canonicalDependencyUrl(url), ref, version, doof::string_toLowerCase(commit)));
    }
#line 61 "/src/std-catalog.do"
    return doof::Success<std::shared_ptr<StdCatalog>>{ std::make_shared<StdCatalog>(schemaVersion, compilerVersion, doof::string_toLowerCase(digest), result) };
}
#line 64 "/src/std-catalog.do"
std::shared_ptr<StdCatalogPackage> stdCatalogPackage(const std::shared_ptr<StdCatalog>& catalog, const std::string& name) {
#line 65 "/src/std-catalog.do"
    const auto& _iterable_15 = catalog->packages;
    for (const auto& package : *_iterable_15) {
#line 65 "/src/std-catalog.do"
        if (package->name == name) {
#line 65 "/src/std-catalog.do"
            return package;
        }
    }
#line 66 "/src/std-catalog.do"
    return nullptr;
}
#line 69 "/src/std-catalog.do"
doof::Result<std::string, std::string> catalogString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
#line 70 "/src/std-catalog.do"
    auto _binding_value_16 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_16)) {
        const auto& value = _binding_value_16;
#line 70 "/src/std-catalog.do"
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" is required")) };
    }
    const auto value = doof::success_value(_binding_value_16);
#line 71 "/src/std-catalog.do"
    auto _binding_value_17 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = value; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_17)) {
        const auto& text = _binding_value_17;
#line 71 "/src/std-catalog.do"
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" must be a string")) };
    }
    const auto text = doof::success_value(_binding_value_17);
#line 72 "/src/std-catalog.do"
    if (text == std::string("")) {
#line 72 "/src/std-catalog.do"
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" must not be empty")) };
    }
#line 73 "/src/std-catalog.do"
    return doof::Success<std::string>{ text };
}
#line 76 "/src/std-catalog.do"
doof::Result<int32_t, std::string> catalogInt(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
#line 77 "/src/std-catalog.do"
    auto _binding_value_18 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_18)) {
        const auto& value = _binding_value_18;
#line 77 "/src/std-catalog.do"
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" is required")) };
    }
    const auto value = doof::success_value(_binding_value_18);
#line 78 "/src/std-catalog.do"
    auto _binding_value_19 = [&]() -> doof::Result<int32_t, std::string> { auto _as_value = value; if (doof::json_is_number(_as_value)) return doof::Success<int32_t>{doof::json_as_int(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_19)) {
        const auto& number = _binding_value_19;
#line 78 "/src/std-catalog.do"
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" must be an integer")) };
    }
    const auto number = doof::success_value(_binding_value_19);
#line 79 "/src/std-catalog.do"
    return doof::Success<int32_t>{ number };
}
#line 1 "<doof-generated>"
}
