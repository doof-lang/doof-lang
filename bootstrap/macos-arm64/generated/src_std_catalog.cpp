#include "src_std_catalog.hpp"
#include <cmath>
#include "std_json_index.hpp"
#include "std_fs_index.hpp"
#include "std_http_index.hpp"
#include "std_os_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_std_catalog_ {
using namespace ::std_::json::index;

doof::JsonObject StdCatalogPackage::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["url"] = doof::json_value(this->url);
    (*_json)["ref"] = doof::json_value(this->ref);
    (*_json)["version"] = doof::json_value(this->version);
    (*_json)["commit"] = doof::json_value(this->commit);
    return _json;
}
doof::Result<std::shared_ptr<StdCatalogPackage>, std::string> StdCatalogPackage::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    auto _iterator_url = _object->find("url");
    if (_iterator_url == _object->end()) { return doof::Failure<std::string>{"Missing required field \"url\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_url->second) : doof::json_is_string(_iterator_url->second)))) { return doof::Failure<std::string>{"Field \"url\" expected string but got " + std::string(doof::json_type_name(_iterator_url->second))}; }
    auto _field_url = (_lenient ? doof::json_as_string_lenient(_iterator_url->second) : doof::json_as_string(_iterator_url->second));
    auto _iterator_ref = _object->find("ref");
    if (_iterator_ref == _object->end()) { return doof::Failure<std::string>{"Missing required field \"ref\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_ref->second) : doof::json_is_string(_iterator_ref->second)))) { return doof::Failure<std::string>{"Field \"ref\" expected string but got " + std::string(doof::json_type_name(_iterator_ref->second))}; }
    auto _field_ref = (_lenient ? doof::json_as_string_lenient(_iterator_ref->second) : doof::json_as_string(_iterator_ref->second));
    auto _iterator_version = _object->find("version");
    if (_iterator_version == _object->end()) { return doof::Failure<std::string>{"Missing required field \"version\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_version->second) : doof::json_is_string(_iterator_version->second)))) { return doof::Failure<std::string>{"Field \"version\" expected string but got " + std::string(doof::json_type_name(_iterator_version->second))}; }
    auto _field_version = (_lenient ? doof::json_as_string_lenient(_iterator_version->second) : doof::json_as_string(_iterator_version->second));
    auto _iterator_commit = _object->find("commit");
    if (_iterator_commit == _object->end()) { return doof::Failure<std::string>{"Missing required field \"commit\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_commit->second) : doof::json_is_string(_iterator_commit->second)))) { return doof::Failure<std::string>{"Field \"commit\" expected string but got " + std::string(doof::json_type_name(_iterator_commit->second))}; }
    auto _field_commit = (_lenient ? doof::json_as_string_lenient(_iterator_commit->second) : doof::json_as_string(_iterator_commit->second));
    return doof::Success<std::shared_ptr<StdCatalogPackage>>{std::make_shared<StdCatalogPackage>(_field_name, _field_url, _field_ref, _field_version, _field_commit)};
}

doof::JsonObject StdCatalog::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["schemaVersion"] = doof::json_value(this->schemaVersion);
    (*_json)["compilerVersion"] = doof::json_value(this->compilerVersion);
    (*_json)["digest"] = doof::json_value(this->digest);
    (*_json)["packages"] = [&]() { auto _array = std::make_shared<std::vector<doof::JsonValue>>(); _array->reserve(this->packages->size()); for (const auto& _element : *this->packages) { _array->push_back(doof::json_value(_element->toJsonObject())); } return doof::json_value(_array); }();
    return _json;
}
doof::Result<std::shared_ptr<StdCatalog>, std::string> StdCatalog::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_schemaVersion = _object->find("schemaVersion");
    if (_iterator_schemaVersion == _object->end()) { return doof::Failure<std::string>{"Missing required field \"schemaVersion\""}; }
    if (!((_lenient ? doof::json_is_lenient_number(_iterator_schemaVersion->second) : doof::json_is_number(_iterator_schemaVersion->second)))) { return doof::Failure<std::string>{"Field \"schemaVersion\" expected number but got " + std::string(doof::json_type_name(_iterator_schemaVersion->second))}; }
    auto _field_schemaVersion = (_lenient ? doof::json_as_int_lenient(_iterator_schemaVersion->second) : doof::json_as_int(_iterator_schemaVersion->second));
    auto _iterator_compilerVersion = _object->find("compilerVersion");
    if (_iterator_compilerVersion == _object->end()) { return doof::Failure<std::string>{"Missing required field \"compilerVersion\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_compilerVersion->second) : doof::json_is_string(_iterator_compilerVersion->second)))) { return doof::Failure<std::string>{"Field \"compilerVersion\" expected string but got " + std::string(doof::json_type_name(_iterator_compilerVersion->second))}; }
    auto _field_compilerVersion = (_lenient ? doof::json_as_string_lenient(_iterator_compilerVersion->second) : doof::json_as_string(_iterator_compilerVersion->second));
    auto _iterator_digest = _object->find("digest");
    if (_iterator_digest == _object->end()) { return doof::Failure<std::string>{"Missing required field \"digest\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_digest->second) : doof::json_is_string(_iterator_digest->second)))) { return doof::Failure<std::string>{"Field \"digest\" expected string but got " + std::string(doof::json_type_name(_iterator_digest->second))}; }
    auto _field_digest = (_lenient ? doof::json_as_string_lenient(_iterator_digest->second) : doof::json_as_string(_iterator_digest->second));
    auto _iterator_packages = _object->find("packages");
    if (_iterator_packages == _object->end()) { return doof::Failure<std::string>{"Missing required field \"packages\""}; }
    if (!(doof::json_is_array(_iterator_packages->second))) { return doof::Failure<std::string>{"Field \"packages\" expected array but got " + std::string(doof::json_type_name(_iterator_packages->second))}; }
    auto _field_packages = [&]() { const auto* _array = doof::json_as_array(_iterator_packages->second); auto _values = std::make_shared<std::vector<std::shared_ptr<StdCatalogPackage>>>(); _values->reserve(_array->size()); for (const auto& _element : *_array) { _values->push_back(doof::success_value(StdCatalogPackage::fromJsonValue(_element, _lenient))); } return _values; }();
    return doof::Success<std::shared_ptr<StdCatalog>>{std::make_shared<StdCatalog>(_field_schemaVersion, _field_compilerVersion, _field_digest, _field_packages)};
}
std::string canonicalDependencyUrl(std::string value) {
    auto result = doof::string_trim(value);
    while (doof::string_endsWith(result, std::string("/"))) {
        (result = doof::string_substring(result, 0, (static_cast<int32_t>(result.size()) - 1)));
    }
    if (doof::string_endsWith(result, std::string(".git"))) {
        (result = doof::string_substring(result, 0, (static_cast<int32_t>(result.size()) - 4)));
    }
    const auto marker = doof::string_indexOf(result, std::string("://"));
    if (marker < 0) {
        return result;
    }
    const auto scheme = doof::string_toLowerCase(doof::string_substring(result, 0, marker));
    const auto remainder = doof::string_substring(result, (marker + 3), static_cast<int32_t>(result.size()));
    const auto slash = doof::string_indexOf(remainder, std::string("/"));
    if (slash < 0) {
        return ((scheme + std::string("://")) + doof::string_toLowerCase(remainder));
    }
    const auto host = doof::string_toLowerCase(doof::string_substring(remainder, 0, slash));
    return (((scheme + std::string("://")) + host) + doof::string_substring(remainder, slash, static_cast<int32_t>(remainder.size())));
}
doof::Result<std::shared_ptr<StdCatalog>, std::string> parseStdCatalog(std::string source) {
    auto _try_value_1 = ::doof_json::parse(source);
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::failure_error(_try_value_1)};
    const auto parsed = doof::success_value(_try_value_1);
    auto _binding_value_2 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = parsed; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_2)) {
        const auto& root = _binding_value_2;
        return doof::Failure<std::string>{ std::string("Invalid std catalog: root must be an object") };
    }
    const auto root = doof::success_value(_binding_value_2);
    auto _try_value_3 = catalogInt(root, std::string("schemaVersion"));
    if (doof::is_failure(_try_value_3)) return doof::Failure<std::string>{doof::failure_error(_try_value_3)};
    const auto schemaVersion = doof::success_value(_try_value_3);
    if (schemaVersion != 1) {
        return doof::Failure<std::string>{ (std::string("Unsupported std catalog schema ") + doof::to_string(schemaVersion)) };
    }
    auto _try_value_4 = catalogString(root, std::string("compilerVersion"));
    if (doof::is_failure(_try_value_4)) return doof::Failure<std::string>{doof::failure_error(_try_value_4)};
    const auto compilerVersion = doof::success_value(_try_value_4);
    auto _try_value_5 = catalogString(root, std::string("digest"));
    if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::failure_error(_try_value_5)};
    const auto digest = doof::success_value(_try_value_5);
    if (static_cast<int32_t>(digest.size()) != 64) {
        return doof::Failure<std::string>{ std::string("Invalid std catalog digest") };
    }
    const auto rawPackages = [&]() -> doof::JsonValue { auto _try_value = doof::map_get(root, std::string("packages"), "", 0); if (doof::is_failure(_try_value)) doof::panic("try! failed"); return std::move(doof::success_value(_try_value)); }();
    auto _binding_value_6 = [&]() -> doof::Result<std::shared_ptr<std::vector<doof::JsonValue>>, std::string> { auto _as_value = rawPackages; if (doof::json_is_array(_as_value)) return doof::Success<std::shared_ptr<std::vector<doof::JsonValue>>>{std::get<doof::JsonArray>(doof::json_storage(_as_value))}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_6)) {
        const auto& packages = _binding_value_6;
        return doof::Failure<std::string>{ std::string("Invalid std catalog: packages must be an array") };
    }
    const auto packages = doof::success_value(_binding_value_6);
    std::shared_ptr<std::vector<std::shared_ptr<StdCatalogPackage>>> result = std::make_shared<std::vector<std::shared_ptr<StdCatalogPackage>>>(std::vector<std::shared_ptr<StdCatalogPackage>>{});
    auto previous = std::string("");
    for (int32_t index = 0; index < static_cast<int32_t>((packages)->size()); ++index) {
        auto _binding_value_7 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = (*packages)[index]; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
        if (doof::is_failure(_binding_value_7)) {
            const auto& object = _binding_value_7;
            return doof::Failure<std::string>{ (std::string("Invalid std catalog package at index ") + doof::to_string(index)) };
        }
        const auto object = doof::success_value(_binding_value_7);
        auto _try_value_8 = catalogString(object, std::string("name"));
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::failure_error(_try_value_8)};
        const auto name = doof::success_value(_try_value_8);
        auto _try_value_9 = catalogString(object, std::string("url"));
        if (doof::is_failure(_try_value_9)) return doof::Failure<std::string>{doof::failure_error(_try_value_9)};
        const auto url = doof::success_value(_try_value_9);
        auto _try_value_10 = catalogString(object, std::string("ref"));
        if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::failure_error(_try_value_10)};
        const auto ref = doof::success_value(_try_value_10);
        auto _try_value_11 = catalogString(object, std::string("version"));
        if (doof::is_failure(_try_value_11)) return doof::Failure<std::string>{doof::failure_error(_try_value_11)};
        const auto version = doof::success_value(_try_value_11);
        auto _try_value_12 = catalogString(object, std::string("commit"));
        if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::failure_error(_try_value_12)};
        const auto commit = doof::success_value(_try_value_12);
        if (!doof::string_startsWith(name, std::string("std/")) || doof::string_contains(doof::string_substring(name, 4, static_cast<int32_t>(name.size())), std::string("/"))) {
            return doof::Failure<std::string>{ (std::string("Invalid std catalog package name ") + name) };
        }
        if (static_cast<int32_t>(commit.size()) != 40) {
            return doof::Failure<std::string>{ (std::string("Invalid std catalog commit for ") + name) };
        }
        if ((previous != std::string("")) && (name <= previous)) {
            return doof::Failure<std::string>{ std::string("Std catalog packages must be sorted and unique") };
        }
        (previous = name);
        result->push_back(std::make_shared<StdCatalogPackage>(name, canonicalDependencyUrl(url), ref, version, doof::string_toLowerCase(commit)));
    }
    return doof::Success<std::shared_ptr<StdCatalog>>{ std::make_shared<StdCatalog>(schemaVersion, compilerVersion, doof::string_toLowerCase(digest), result) };
}
std::shared_ptr<StdCatalogPackage> stdCatalogPackage(std::shared_ptr<StdCatalog> catalog, std::string name) {
    const auto& _iterable_13 = catalog->packages;
    for (const auto& package : *_iterable_13) {
        if (package->name == name) {
            return package;
        }
    }
    return nullptr;
}
doof::Result<std::string, std::string> catalogString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name) {
    auto _binding_value_14 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_14)) {
        const auto& value = _binding_value_14;
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" is required")) };
    }
    const auto value = doof::success_value(_binding_value_14);
    auto _binding_value_15 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = value; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_15)) {
        const auto& text = _binding_value_15;
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" must be a string")) };
    }
    const auto text = doof::success_value(_binding_value_15);
    if (text == std::string("")) {
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" must not be empty")) };
    }
    return doof::Success<std::string>{ text };
}
doof::Result<int32_t, std::string> catalogInt(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name) {
    auto _binding_value_16 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_16)) {
        const auto& value = _binding_value_16;
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" is required")) };
    }
    const auto value = doof::success_value(_binding_value_16);
    auto _binding_value_17 = [&]() -> doof::Result<int32_t, std::string> { auto _as_value = value; if (doof::json_is_number(_as_value)) return doof::Success<int32_t>{doof::json_as_int(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_17)) {
        const auto& number = _binding_value_17;
        return doof::Failure<std::string>{ ((std::string("Invalid std catalog: ") + name) + std::string(" must be an integer")) };
    }
    const auto number = doof::success_value(_binding_value_17);
    return doof::Success<int32_t>{ number };
}
}
