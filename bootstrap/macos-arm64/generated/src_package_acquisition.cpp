#include "src_package_acquisition.hpp"
#include <cmath>
#include "std_blob_index.hpp"
#include "std_fs_index.hpp"
#include "std_json_index.hpp"
#include "std_os_index.hpp"
#include "std_path_index.hpp"
#include "src_std_catalog.hpp"
#include "std_http_index.hpp"
#include "std_stream_index.hpp"

namespace app_src_package_acquisition_ {
using namespace ::std_::blob::index;
using namespace ::std_::fs::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
using namespace ::app_src_std_catalog_;
const auto PACKAGE_ACQUISITION_RECEIPT = std::string(".doof-acquisition.json");
const auto PACKAGE_ACQUISITION_SCHEMA_VERSION = 1;

doof::JsonObject ExactPackageSource::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["name"] = doof::json_value(this->name);
    (*_json)["expectedManifestName"] = doof::json_value(this->expectedManifestName);
    (*_json)["url"] = doof::json_value(this->url);
    (*_json)["ref"] = doof::json_value(this->ref);
    (*_json)["commit"] = doof::json_value(this->commit);
    return _json;
}
doof::Result<std::shared_ptr<ExactPackageSource>, std::string> ExactPackageSource::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_name = _object->find("name");
    if (_iterator_name == _object->end()) { return doof::Failure<std::string>{"Missing required field \"name\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_name->second) : doof::json_is_string(_iterator_name->second)))) { return doof::Failure<std::string>{"Field \"name\" expected string but got " + std::string(doof::json_type_name(_iterator_name->second))}; }
    auto _field_name = (_lenient ? doof::json_as_string_lenient(_iterator_name->second) : doof::json_as_string(_iterator_name->second));
    std::optional<std::string> _field_expectedManifestName;
    if (auto _iterator_expectedManifestName = _object->find("expectedManifestName"); _iterator_expectedManifestName != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_expectedManifestName->second) : doof::json_is_string(_iterator_expectedManifestName->second)))) { return doof::Failure<std::string>{"Field \"expectedManifestName\" expected string but got " + std::string(doof::json_type_name(_iterator_expectedManifestName->second))}; }
        _field_expectedManifestName = (_lenient ? doof::json_as_string_lenient(_iterator_expectedManifestName->second) : doof::json_as_string(_iterator_expectedManifestName->second));
    } else {
        _field_expectedManifestName = std::string("");
    }
    auto _iterator_url = _object->find("url");
    if (_iterator_url == _object->end()) { return doof::Failure<std::string>{"Missing required field \"url\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_url->second) : doof::json_is_string(_iterator_url->second)))) { return doof::Failure<std::string>{"Field \"url\" expected string but got " + std::string(doof::json_type_name(_iterator_url->second))}; }
    auto _field_url = (_lenient ? doof::json_as_string_lenient(_iterator_url->second) : doof::json_as_string(_iterator_url->second));
    auto _iterator_ref = _object->find("ref");
    if (_iterator_ref == _object->end()) { return doof::Failure<std::string>{"Missing required field \"ref\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_ref->second) : doof::json_is_string(_iterator_ref->second)))) { return doof::Failure<std::string>{"Field \"ref\" expected string but got " + std::string(doof::json_type_name(_iterator_ref->second))}; }
    auto _field_ref = (_lenient ? doof::json_as_string_lenient(_iterator_ref->second) : doof::json_as_string(_iterator_ref->second));
    auto _iterator_commit = _object->find("commit");
    if (_iterator_commit == _object->end()) { return doof::Failure<std::string>{"Missing required field \"commit\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_commit->second) : doof::json_is_string(_iterator_commit->second)))) { return doof::Failure<std::string>{"Field \"commit\" expected string but got " + std::string(doof::json_type_name(_iterator_commit->second))}; }
    auto _field_commit = (_lenient ? doof::json_as_string_lenient(_iterator_commit->second) : doof::json_as_string(_iterator_commit->second));
    return doof::Success<std::shared_ptr<ExactPackageSource>>{std::make_shared<ExactPackageSource>(_field_name, _field_expectedManifestName.value(), _field_url, _field_ref, _field_commit)};
}

doof::JsonObject AcquiredPackage::toJsonObject() const {
    auto _json = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>();
    (*_json)["source"] = doof::json_value(this->source->toJsonObject());
    (*_json)["rootDirectory"] = doof::json_value(this->rootDirectory);
    (*_json)["mutable"] = doof::json_value(this->mutable_);
    return _json;
}
doof::Result<std::shared_ptr<AcquiredPackage>, std::string> AcquiredPackage::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    const auto* _object = doof::json_as_object(_json);
    if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_source = _object->find("source");
    if (_iterator_source == _object->end()) { return doof::Failure<std::string>{"Missing required field \"source\""}; }
    if (!(doof::json_is_object(_iterator_source->second))) { return doof::Failure<std::string>{"Field \"source\" expected object but got " + std::string(doof::json_type_name(_iterator_source->second))}; }
    auto _field_source = doof::success_value(ExactPackageSource::fromJsonValue(_iterator_source->second, _lenient));
    auto _iterator_rootDirectory = _object->find("rootDirectory");
    if (_iterator_rootDirectory == _object->end()) { return doof::Failure<std::string>{"Missing required field \"rootDirectory\""}; }
    if (!((_lenient ? doof::json_is_lenient_string(_iterator_rootDirectory->second) : doof::json_is_string(_iterator_rootDirectory->second)))) { return doof::Failure<std::string>{"Field \"rootDirectory\" expected string but got " + std::string(doof::json_type_name(_iterator_rootDirectory->second))}; }
    auto _field_rootDirectory = (_lenient ? doof::json_as_string_lenient(_iterator_rootDirectory->second) : doof::json_as_string(_iterator_rootDirectory->second));
    std::optional<bool> _field_mutable_;
    if (auto _iterator_mutable_ = _object->find("mutable"); _iterator_mutable_ != _object->end()) {
        if (!((_lenient ? doof::json_is_lenient_boolean(_iterator_mutable_->second) : doof::json_is_boolean(_iterator_mutable_->second)))) { return doof::Failure<std::string>{"Field \"mutable\" expected boolean but got " + std::string(doof::json_type_name(_iterator_mutable_->second))}; }
        _field_mutable_ = (_lenient ? doof::json_as_bool_lenient(_iterator_mutable_->second) : doof::json_as_bool(_iterator_mutable_->second));
    } else {
        _field_mutable_ = false;
    }
    return doof::Success<std::shared_ptr<AcquiredPackage>>{std::make_shared<AcquiredPackage>(_field_source, _field_rootDirectory, _field_mutable_.value())};
}
std::string workspacePackageAcquisitionRoot(std::string workspaceRoot) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{workspaceRoot, std::string(".doof"), std::string("packages")}));
}
std::string packageAcquisitionPath(std::string packagesRoot, std::string packageName) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{packagesRoot, packageName}));
}
std::string packageAcquisitionReceiptPath(std::string packageRoot) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{packageRoot, PACKAGE_ACQUISITION_RECEIPT}));
}
doof::Result<std::shared_ptr<AcquiredPackage>, std::string> acquireExactGitPackage(std::shared_ptr<ExactPackageSource> source, std::string packagesRoot) {
    if (static_cast<int32_t>(source->commit.size()) != 40) {
        return doof::Failure<std::string>{ ((std::string("Exact package ") + source->name) + std::string(" requires a 40-character commit")) };
    }
    if (!validPackageAcquisitionName(source->name)) {
        return doof::Failure<std::string>{ (std::string("Invalid acquired package name ") + source->name) };
    }
    const auto root = packageAcquisitionPath(packagesRoot, source->name);
    if (reusableAcquiredPackage(root, source)) {
        return doof::Success<std::shared_ptr<AcquiredPackage>>{ std::make_shared<AcquiredPackage>(source, root, false) };
    }
    auto _try_value_1 = ensurePackageDirectory(::std_::path::index::dirname(root));
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::failure_error(_try_value_1)};
    const auto staging = ((root + std::string(".staging-")) + doof::to_string(::std_::os::index::pid()));
    if (::doof_fs::exists(staging)) {
        auto _try_value_2 = removePackageTree(staging);
        if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::failure_error(_try_value_2)};
    }
    const auto clone = packageCommand(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("clone"), std::string("--depth"), std::string("1"), std::string("--branch"), source->ref, source->url, staging}));
    auto _binding_value_3 = clone;
    if (doof::is_failure(_binding_value_3)) {
        const auto error = doof::failure_error(_binding_value_3);
        return doof::Failure<std::string>{ (((std::string("Failed to acquire package ") + source->name) + std::string(": ")) + error) };
    }
    auto _binding_value_4 = packageCommand(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-C"), staging, std::string("rev-parse"), std::string("HEAD")}));
    if (doof::is_failure(_binding_value_4)) {
        const auto error = doof::failure_error(_binding_value_4);
        auto _try_value_5 = removePackageTree(staging);
        if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::failure_error(_try_value_5)};
        return doof::Failure<std::string>{ (((std::string("Failed to inspect package ") + source->name) + std::string(": ")) + error) };
    }
    const auto actual = doof::success_value(_binding_value_4);
    if (doof::string_toLowerCase(actual) != doof::string_toLowerCase(source->commit)) {
        auto _try_value_6 = removePackageTree(staging);
        if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::failure_error(_try_value_6)};
        return doof::Failure<std::string>{ (((((std::string("Package ") + source->name) + std::string(" commit mismatch: expected ")) + doof::string_toLowerCase(source->commit)) + std::string(", got ")) + doof::string_toLowerCase(actual)) };
    }
    auto _binding_value_7 = validateAcquiredPackage(staging, source);
    if (doof::is_failure(_binding_value_7)) {
        const auto error = doof::failure_error(_binding_value_7);
        auto _try_value_8 = removePackageTree(staging);
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::failure_error(_try_value_8)};
        return doof::Failure<std::string>{ error };
    }
    auto _binding_value_9 = removePackageTree(::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{staging, std::string(".git")})));
    if (doof::is_failure(_binding_value_9)) {
        const auto error = doof::failure_error(_binding_value_9);
        auto _try_value_10 = removePackageTree(staging);
        if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::failure_error(_try_value_10)};
        return doof::Failure<std::string>{ (((std::string("Could not remove Git metadata for package ") + source->name) + std::string(": ")) + error) };
    }
    auto _binding_value_11 = ::doof_fs::writeText(packageAcquisitionReceiptPath(staging), renderAcquisitionReceipt(source));
    if (doof::is_failure(_binding_value_11)) {
        auto _try_value_12 = removePackageTree(staging);
        if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::failure_error(_try_value_12)};
        return doof::Failure<std::string>{ (std::string("Could not write acquisition receipt for package ") + source->name) };
    }
    if (::doof_fs::exists(root)) {
        auto _binding_value_13 = removePackageTree(root);
        if (doof::is_failure(_binding_value_13)) {
            const auto error = doof::failure_error(_binding_value_13);
            auto _try_value_14 = removePackageTree(staging);
            if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::failure_error(_try_value_14)};
            return doof::Failure<std::string>{ (((std::string("Could not replace acquired package ") + source->name) + std::string(": ")) + error) };
        }
    }
    auto _binding_value_15 = ::doof_fs::rename(staging, root);
    if (doof::is_failure(_binding_value_15)) {
        auto _try_value_16 = removePackageTree(staging);
        if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::failure_error(_try_value_16)};
        return doof::Failure<std::string>{ (std::string("Could not finalize package ") + source->name) };
    }
    return doof::Success<std::shared_ptr<AcquiredPackage>>{ std::make_shared<AcquiredPackage>(source, root, false) };
}
bool validPackageAcquisitionName(std::string name) {
    if (((name == std::string("")) || doof::string_startsWith(name, std::string("/"))) || doof::string_contains(name, std::string("\\"))) {
        return false;
    }
    const auto& _iterable_17 = doof::string_split(name, std::string("/"));
    for (const auto& segment : *_iterable_17) {
        if (((segment == std::string("")) || (segment == std::string("."))) || (segment == std::string(".."))) {
            return false;
        }
    }
    return true;
}
bool reusableAcquiredPackage(std::string root, std::shared_ptr<ExactPackageSource> source) {
    if (!::doof_fs::isDirectory(root) || !acquisitionReceiptMatches(packageAcquisitionReceiptPath(root), source)) {
        return false;
    }
    auto _binding_value_18 = validateAcquiredPackage(root, source);
    if (doof::is_failure(_binding_value_18)) {
        return false;
    }
    return true;
}
bool acquisitionReceiptMatches(std::string path, std::shared_ptr<ExactPackageSource> source) {
    auto _binding_value_19 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_19)) {
        const auto& receiptSource = _binding_value_19;
        return false;
    }
    const auto receiptSource = doof::success_value(_binding_value_19);
    auto _binding_value_20 = ::doof_json::parse(receiptSource);
    if (doof::is_failure(_binding_value_20)) {
        const auto& parsed = _binding_value_20;
        return false;
    }
    const auto parsed = doof::success_value(_binding_value_20);
    auto _binding_value_21 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = parsed; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_21)) {
        const auto& object = _binding_value_21;
        return false;
    }
    const auto object = doof::success_value(_binding_value_21);
    const auto schemaVersion = acquisitionReceiptInt(object, std::string("schemaVersion"));
    const auto name = acquisitionReceiptString(object, std::string("name"));
    const auto url = acquisitionReceiptString(object, std::string("url"));
    const auto ref = acquisitionReceiptString(object, std::string("ref"));
    const auto commit = acquisitionReceiptString(object, std::string("commit"));
    return (((((schemaVersion == PACKAGE_ACQUISITION_SCHEMA_VERSION) && (name == source->name)) && (url == ::app_src_std_catalog_::canonicalDependencyUrl(source->url))) && (ref == source->ref)) && (commit == doof::string_toLowerCase(source->commit)));
}
std::optional<std::string> acquisitionReceiptString(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name) {
    auto _binding_value_22 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_22)) {
        const auto& value = _binding_value_22;
        return std::nullopt;
    }
    const auto value = doof::success_value(_binding_value_22);
    auto _binding_value_23 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = value; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_23)) {
        const auto& text = _binding_value_23;
        return std::nullopt;
    }
    const auto text = doof::success_value(_binding_value_23);
    return text;
}
std::optional<int32_t> acquisitionReceiptInt(std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> object, std::string name) {
    auto _binding_value_24 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_24)) {
        const auto& value = _binding_value_24;
        return std::nullopt;
    }
    const auto value = doof::success_value(_binding_value_24);
    auto _binding_value_25 = [&]() -> doof::Result<int32_t, std::string> { auto _as_value = value; if (doof::json_is_number(_as_value)) return doof::Success<int32_t>{doof::json_as_int(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_25)) {
        const auto& number = _binding_value_25;
        return std::nullopt;
    }
    const auto number = doof::success_value(_binding_value_25);
    return number;
}
std::string renderAcquisitionReceipt(std::shared_ptr<ExactPackageSource> source) {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> receipt = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    doof::map_set(receipt, std::string("schemaVersion"), doof::json_value(PACKAGE_ACQUISITION_SCHEMA_VERSION), "", 0);
    doof::map_set(receipt, std::string("name"), doof::json_value(source->name), "", 0);
    doof::map_set(receipt, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(source->url)), "", 0);
    doof::map_set(receipt, std::string("ref"), doof::json_value(source->ref), "", 0);
    doof::map_set(receipt, std::string("commit"), doof::json_value(doof::string_toLowerCase(source->commit)), "", 0);
    return (::doof_json::format(doof::json_value(receipt)) + std::string("\n"));
}
doof::Result<void, std::string> validateAcquiredPackage(std::string root, std::shared_ptr<ExactPackageSource> source) {
    const auto manifestPath = ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{root, std::string("doof.json")}));
    auto _binding_value_26 = ::doof_fs::readText(manifestPath);
    if (doof::is_failure(_binding_value_26)) {
        const auto& manifestSource = _binding_value_26;
        return doof::Failure<std::string>{ ((std::string("Acquired package ") + source->name) + std::string(" is missing doof.json")) };
    }
    const auto manifestSource = doof::success_value(_binding_value_26);
    auto _binding_value_27 = ::doof_json::parse(manifestSource);
    if (doof::is_failure(_binding_value_27)) {
        const auto& parsed = _binding_value_27;
        return doof::Failure<std::string>{ ((std::string("Acquired package ") + source->name) + std::string(" has invalid doof.json")) };
    }
    const auto parsed = doof::success_value(_binding_value_27);
    auto _binding_value_28 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = parsed; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_28)) {
        const auto& object = _binding_value_28;
        return doof::Failure<std::string>{ ((std::string("Acquired package ") + source->name) + std::string(" has invalid doof.json")) };
    }
    const auto object = doof::success_value(_binding_value_28);
    auto _binding_value_29 = doof::map_get(object, std::string("name"), "", 0);
    if (doof::is_failure(_binding_value_29)) {
        const auto& nameValue = _binding_value_29;
        return doof::Failure<std::string>{ (std::string("Acquired package must declare name ") + source->name) };
    }
    const auto nameValue = doof::success_value(_binding_value_29);
    auto _binding_value_30 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = nameValue; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_30)) {
        const auto& name = _binding_value_30;
        return doof::Failure<std::string>{ std::string("Acquired package name must be a string") };
    }
    const auto name = doof::success_value(_binding_value_30);
    if ((source->expectedManifestName != std::string("")) && (name != source->expectedManifestName)) {
        return doof::Failure<std::string>{ (((std::string("Acquired package name mismatch: expected ") + source->expectedManifestName) + std::string(", got ")) + name) };
    }
    return doof::Success<void>{};
}
doof::Result<std::string, std::string> packageCommand(std::string command, std::shared_ptr<std::vector<std::string>> arguments) {
    auto _binding_value_31 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, std::nullopt, nullptr));
    if (doof::is_failure(_binding_value_31)) {
        const auto error = doof::failure_error(_binding_value_31);
        return doof::Failure<std::string>{ ((command + std::string(": ")) + error) };
    }
    const auto result = doof::success_value(_binding_value_31);
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(result->stdout, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->stdout)->size()))));
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ (((command + std::string(" exited with code ")) + doof::to_string(result->exitCode)) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
    return doof::Success<std::string>{ output };
}
doof::Result<void, std::string> ensurePackageDirectory(std::string path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return doof::Success<void>{};
    }
    const auto parent = ::std_::path::index::dirname(path);
    if (parent != path) {
        auto _try_value_32 = ensurePackageDirectory(parent);
        if (doof::is_failure(_try_value_32)) return doof::Failure<std::string>{doof::failure_error(_try_value_32)};
    }
    auto _binding_value_33 = ::doof_fs::mkdir(path);
    if (doof::is_failure(_binding_value_33)) {
        return doof::Failure<std::string>{ (std::string("Could not create package acquisition directory ") + path) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> removePackageTree(std::string path) {
    if (!::doof_fs::exists(path)) {
        return doof::Success<void>{};
    }
    if (::doof_fs::isDirectory(path)) {
        auto _binding_value_34 = ::doof_fs::readDir(path);
        if (doof::is_failure(_binding_value_34)) {
            const auto& entries = _binding_value_34;
            return doof::Failure<std::string>{ (std::string("Could not read ") + path) };
        }
        const auto entries = doof::success_value(_binding_value_34);
        const auto& _iterable_35 = entries;
        for (const auto& entry : *_iterable_35) {
            auto _try_value_36 = removePackageTree(::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path, entry->name})));
            if (doof::is_failure(_try_value_36)) return doof::Failure<std::string>{doof::failure_error(_try_value_36)};
        }
    }
    auto _binding_value_37 = ::doof_fs::remove(path);
    if (doof::is_failure(_binding_value_37)) {
        return doof::Failure<std::string>{ (std::string("Could not remove ") + path) };
    }
    return doof::Success<void>{};
}
}
