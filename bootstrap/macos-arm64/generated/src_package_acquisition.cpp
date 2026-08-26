#include "src_package_acquisition.hpp"

namespace app_src_package_acquisition_ {
using namespace ::std_::blob::index;
using namespace ::std_::fs::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
using namespace ::app_src_std_catalog_;
std::string PACKAGE_ACQUISITION_RECEIPT;
int32_t PACKAGE_ACQUISITION_SCHEMA_VERSION = 1;


#line 28 "/src/package-acquisition.do"
std::string workspacePackageAcquisitionRoot(const std::string& workspaceRoot) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{workspaceRoot, std::string(".doof"), std::string("packages")}));
}
#line 31 "/src/package-acquisition.do"
std::string packageAcquisitionPath(const std::string& packagesRoot, const std::string& packageName) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{packagesRoot, packageName}));
}
#line 33 "/src/package-acquisition.do"
std::string packageAcquisitionReceiptPath(const std::string& packageRoot) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{packageRoot, PACKAGE_ACQUISITION_RECEIPT}));
}
#line 35 "/src/package-acquisition.do"
doof::Result<std::shared_ptr<AcquiredPackage>, std::string> acquireExactGitPackage(const std::shared_ptr<ExactPackageSource>& source, const std::string& packagesRoot) {
#line 39 "/src/package-acquisition.do"
    if (static_cast<int32_t>(source->commit.size()) != 40) {
#line 39 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ ((std::string("Exact package ") + source->name) + std::string(" requires a 40-character commit")) };
    }
#line 40 "/src/package-acquisition.do"
    if (!validPackageAcquisitionName(source->name)) {
#line 40 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (std::string("Invalid acquired package name ") + source->name) };
    }
#line 41 "/src/package-acquisition.do"
    const auto root = packageAcquisitionPath(packagesRoot, source->name);
#line 42 "/src/package-acquisition.do"
    if (reusableAcquiredPackage(root, source)) {
#line 43 "/src/package-acquisition.do"
        return doof::Success<std::shared_ptr<AcquiredPackage>>{ std::make_shared<AcquiredPackage>(source, root, false) };
    }
#line 46 "/src/package-acquisition.do"
    auto _try_value_1 = ensurePackageDirectory(::std_::path::index::dirname(root));
    if (doof::is_failure(_try_value_1)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_1))};
#line 47 "/src/package-acquisition.do"
    const auto staging = ((root + std::string(".staging-")) + doof::to_string(::std_::os::index::pid()));
#line 48 "/src/package-acquisition.do"
    if (::doof_fs::exists(staging)) {
#line 48 "/src/package-acquisition.do"
        auto _try_value_2 = removePackageTree(staging);
        if (doof::is_failure(_try_value_2)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_2))};
    }
#line 49 "/src/package-acquisition.do"
    const auto clone = packageCommand(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("clone"), std::string("--depth"), std::string("1"), std::string("--branch"), source->ref, source->url, staging}));
#line 50 "/src/package-acquisition.do"
    auto _binding_value_3 = clone;
    if (doof::is_failure(_binding_value_3)) {
        const auto error = doof::failure_error(_binding_value_3);
#line 50 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (((std::string("Failed to acquire package ") + source->name) + std::string(": ")) + error) };
    }
#line 51 "/src/package-acquisition.do"
    auto _binding_value_4 = packageCommand(std::string("git"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("-C"), staging, std::string("rev-parse"), std::string("HEAD")}));
    if (doof::is_failure(_binding_value_4)) {
        const auto error = doof::failure_error(_binding_value_4);
#line 52 "/src/package-acquisition.do"
        auto _try_value_5 = removePackageTree(staging);
        if (doof::is_failure(_try_value_5)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_5))};
#line 53 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (((std::string("Failed to inspect package ") + source->name) + std::string(": ")) + error) };
    }
    const auto actual = doof::success_value(_binding_value_4);
#line 55 "/src/package-acquisition.do"
    if (doof::string_toLowerCase(actual) != doof::string_toLowerCase(source->commit)) {
#line 56 "/src/package-acquisition.do"
        auto _try_value_6 = removePackageTree(staging);
        if (doof::is_failure(_try_value_6)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_6))};
#line 57 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (((((std::string("Package ") + source->name) + std::string(" commit mismatch: expected ")) + doof::string_toLowerCase(source->commit)) + std::string(", got ")) + doof::string_toLowerCase(actual)) };
    }
#line 59 "/src/package-acquisition.do"
    auto _binding_value_7 = validateAcquiredPackage(staging, source);
    if (doof::is_failure(_binding_value_7)) {
        const auto error = doof::failure_error(_binding_value_7);
#line 60 "/src/package-acquisition.do"
        auto _try_value_8 = removePackageTree(staging);
        if (doof::is_failure(_try_value_8)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_8))};
#line 61 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ error };
    }
#line 63 "/src/package-acquisition.do"
    auto _binding_value_9 = removePackageTree(::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{staging, std::string(".git")})));
    if (doof::is_failure(_binding_value_9)) {
        const auto error = doof::failure_error(_binding_value_9);
#line 64 "/src/package-acquisition.do"
        auto _try_value_10 = removePackageTree(staging);
        if (doof::is_failure(_try_value_10)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_10))};
#line 65 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (((std::string("Could not remove Git metadata for package ") + source->name) + std::string(": ")) + error) };
    }
#line 67 "/src/package-acquisition.do"
    auto _binding_value_11 = ::doof_fs::writeText(packageAcquisitionReceiptPath(staging), renderAcquisitionReceipt(source));
    if (doof::is_failure(_binding_value_11)) {
#line 68 "/src/package-acquisition.do"
        auto _try_value_12 = removePackageTree(staging);
        if (doof::is_failure(_try_value_12)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_12))};
#line 69 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (std::string("Could not write acquisition receipt for package ") + source->name) };
    }
#line 71 "/src/package-acquisition.do"
    if (::doof_fs::exists(root)) {
#line 72 "/src/package-acquisition.do"
        auto _binding_value_13 = removePackageTree(root);
        if (doof::is_failure(_binding_value_13)) {
            const auto error = doof::failure_error(_binding_value_13);
#line 73 "/src/package-acquisition.do"
            auto _try_value_14 = removePackageTree(staging);
            if (doof::is_failure(_try_value_14)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_14))};
#line 74 "/src/package-acquisition.do"
            return doof::Failure<std::string>{ (((std::string("Could not replace acquired package ") + source->name) + std::string(": ")) + error) };
        }
    }
#line 77 "/src/package-acquisition.do"
    auto _binding_value_15 = ::doof_fs::rename(staging, root);
    if (doof::is_failure(_binding_value_15)) {
#line 78 "/src/package-acquisition.do"
        auto _try_value_16 = removePackageTree(staging);
        if (doof::is_failure(_try_value_16)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_16))};
#line 79 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (std::string("Could not finalize package ") + source->name) };
    }
#line 81 "/src/package-acquisition.do"
    return doof::Success<std::shared_ptr<AcquiredPackage>>{ std::make_shared<AcquiredPackage>(source, root, false) };
}
#line 84 "/src/package-acquisition.do"
bool validPackageAcquisitionName(const std::string& name) {
#line 85 "/src/package-acquisition.do"
    if (((name == std::string("")) || doof::string_startsWith(name, std::string("/"))) || doof::string_contains(name, std::string("\\"))) {
#line 85 "/src/package-acquisition.do"
        return false;
    }
#line 86 "/src/package-acquisition.do"
    const auto& _iterable_18 = doof::string_split(name, std::string("/"));
    for (const auto& segment : *_iterable_18) {
#line 87 "/src/package-acquisition.do"
        if (((segment == std::string("")) || (segment == std::string("."))) || (segment == std::string(".."))) {
#line 87 "/src/package-acquisition.do"
            return false;
        }
    }
#line 89 "/src/package-acquisition.do"
    return true;
}
#line 92 "/src/package-acquisition.do"
bool reusableAcquiredPackage(const std::string& root, const std::shared_ptr<ExactPackageSource>& source) {
#line 93 "/src/package-acquisition.do"
    if (!::doof_fs::isDirectory(root) || !acquisitionReceiptMatches(packageAcquisitionReceiptPath(root), source)) {
#line 93 "/src/package-acquisition.do"
        return false;
    }
#line 94 "/src/package-acquisition.do"
    auto _binding_value_19 = validateAcquiredPackage(root, source);
    if (doof::is_failure(_binding_value_19)) {
#line 94 "/src/package-acquisition.do"
        return false;
    }
#line 95 "/src/package-acquisition.do"
    return true;
}
#line 98 "/src/package-acquisition.do"
bool acquisitionReceiptMatches(const std::string& path, const std::shared_ptr<ExactPackageSource>& source) {
#line 99 "/src/package-acquisition.do"
    auto _binding_value_20 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_20)) {
        const auto& receiptSource = _binding_value_20;
#line 99 "/src/package-acquisition.do"
        return false;
    }
    const auto receiptSource = doof::success_value(_binding_value_20);
#line 100 "/src/package-acquisition.do"
    auto _binding_value_21 = ::doof_json::parse(receiptSource);
    if (doof::is_failure(_binding_value_21)) {
        const auto& parsed = _binding_value_21;
#line 100 "/src/package-acquisition.do"
        return false;
    }
    const auto parsed = doof::success_value(_binding_value_21);
#line 101 "/src/package-acquisition.do"
    auto _binding_value_22 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = parsed; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_22)) {
        const auto& object = _binding_value_22;
#line 101 "/src/package-acquisition.do"
        return false;
    }
    const auto object = doof::success_value(_binding_value_22);
#line 102 "/src/package-acquisition.do"
    const auto schemaVersion = acquisitionReceiptInt(object, std::string("schemaVersion"));
#line 103 "/src/package-acquisition.do"
    const auto name = acquisitionReceiptString(object, std::string("name"));
#line 104 "/src/package-acquisition.do"
    const auto url = acquisitionReceiptString(object, std::string("url"));
#line 105 "/src/package-acquisition.do"
    const auto ref = acquisitionReceiptString(object, std::string("ref"));
#line 106 "/src/package-acquisition.do"
    const auto commit = acquisitionReceiptString(object, std::string("commit"));
#line 107 "/src/package-acquisition.do"
    return (((((schemaVersion == PACKAGE_ACQUISITION_SCHEMA_VERSION) && (name == source->name)) && (url == ::app_src_std_catalog_::canonicalDependencyUrl(source->url))) && (ref == source->ref)) && (commit == doof::string_toLowerCase(source->commit)));
}
#line 111 "/src/package-acquisition.do"
std::optional<std::string> acquisitionReceiptString(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
#line 112 "/src/package-acquisition.do"
    auto _binding_value_23 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_23)) {
        const auto& value = _binding_value_23;
#line 112 "/src/package-acquisition.do"
        return std::nullopt;
    }
    const auto value = doof::success_value(_binding_value_23);
#line 113 "/src/package-acquisition.do"
    auto _binding_value_24 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = value; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_24)) {
        const auto& text = _binding_value_24;
#line 113 "/src/package-acquisition.do"
        return std::nullopt;
    }
    const auto text = doof::success_value(_binding_value_24);
#line 114 "/src/package-acquisition.do"
    return text;
}
#line 117 "/src/package-acquisition.do"
std::optional<int32_t> acquisitionReceiptInt(const std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>& object, const std::string& name) {
#line 118 "/src/package-acquisition.do"
    auto _binding_value_25 = doof::map_get(object, name, "", 0);
    if (doof::is_failure(_binding_value_25)) {
        const auto& value = _binding_value_25;
#line 118 "/src/package-acquisition.do"
        return std::nullopt;
    }
    const auto value = doof::success_value(_binding_value_25);
#line 119 "/src/package-acquisition.do"
    auto _binding_value_26 = [&]() -> doof::Result<int32_t, std::string> { auto _as_value = value; if (doof::json_is_number(_as_value)) return doof::Success<int32_t>{doof::json_as_int(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_26)) {
        const auto& number = _binding_value_26;
#line 119 "/src/package-acquisition.do"
        return std::nullopt;
    }
    const auto number = doof::success_value(_binding_value_26);
#line 120 "/src/package-acquisition.do"
    return number;
}
#line 123 "/src/package-acquisition.do"
std::string renderAcquisitionReceipt(const std::shared_ptr<ExactPackageSource>& source) {
#line 124 "/src/package-acquisition.do"
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> receipt = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
#line 125 "/src/package-acquisition.do"
    doof::map_set(receipt, std::string("schemaVersion"), doof::json_value(PACKAGE_ACQUISITION_SCHEMA_VERSION), "", 0);
#line 126 "/src/package-acquisition.do"
    doof::map_set(receipt, std::string("name"), doof::json_value(source->name), "", 0);
#line 127 "/src/package-acquisition.do"
    doof::map_set(receipt, std::string("url"), doof::json_value(::app_src_std_catalog_::canonicalDependencyUrl(source->url)), "", 0);
#line 128 "/src/package-acquisition.do"
    doof::map_set(receipt, std::string("ref"), doof::json_value(source->ref), "", 0);
#line 129 "/src/package-acquisition.do"
    doof::map_set(receipt, std::string("commit"), doof::json_value(doof::string_toLowerCase(source->commit)), "", 0);
#line 130 "/src/package-acquisition.do"
    return (::doof_json::format(doof::json_value(receipt)) + std::string("\n"));
}
#line 133 "/src/package-acquisition.do"
doof::Result<void, std::string> validateAcquiredPackage(const std::string& root, const std::shared_ptr<ExactPackageSource>& source) {
#line 134 "/src/package-acquisition.do"
    const auto manifestPath = ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{root, std::string("doof.json")}));
#line 135 "/src/package-acquisition.do"
    auto _binding_value_27 = ::doof_fs::readText(manifestPath);
    if (doof::is_failure(_binding_value_27)) {
        const auto& manifestSource = _binding_value_27;
#line 135 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ ((std::string("Acquired package ") + source->name) + std::string(" is missing doof.json")) };
    }
    const auto manifestSource = doof::success_value(_binding_value_27);
#line 136 "/src/package-acquisition.do"
    auto _binding_value_28 = ::doof_json::parse(manifestSource);
    if (doof::is_failure(_binding_value_28)) {
        const auto& parsed = _binding_value_28;
#line 136 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ ((std::string("Acquired package ") + source->name) + std::string(" has invalid doof.json")) };
    }
    const auto parsed = doof::success_value(_binding_value_28);
#line 137 "/src/package-acquisition.do"
    auto _binding_value_29 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = parsed; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_29)) {
        const auto& object = _binding_value_29;
#line 137 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ ((std::string("Acquired package ") + source->name) + std::string(" has invalid doof.json")) };
    }
    const auto object = doof::success_value(_binding_value_29);
#line 138 "/src/package-acquisition.do"
    auto _binding_value_30 = doof::map_get(object, std::string("name"), "", 0);
    if (doof::is_failure(_binding_value_30)) {
        const auto& nameValue = _binding_value_30;
#line 138 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (std::string("Acquired package must declare name ") + source->name) };
    }
    const auto nameValue = doof::success_value(_binding_value_30);
#line 139 "/src/package-acquisition.do"
    auto _binding_value_31 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = nameValue; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_31)) {
        const auto& name = _binding_value_31;
#line 139 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ std::string("Acquired package name must be a string") };
    }
    const auto name = doof::success_value(_binding_value_31);
#line 140 "/src/package-acquisition.do"
    if ((source->expectedManifestName != std::string("")) && (name != source->expectedManifestName)) {
#line 141 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (((std::string("Acquired package name mismatch: expected ") + source->expectedManifestName) + std::string(", got ")) + name) };
    }
#line 143 "/src/package-acquisition.do"
    return doof::Success<void>{};
}
#line 146 "/src/package-acquisition.do"
doof::Result<std::string, std::string> packageCommand(const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments) {
#line 147 "/src/package-acquisition.do"
    auto _binding_value_32 = ::std_::os::index::run(command, arguments, std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, std::nullopt, nullptr));
    if (doof::is_failure(_binding_value_32)) {
        const auto error = doof::failure_error(_binding_value_32);
#line 148 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ ((command + std::string(": ")) + error) };
    }
    const auto result = doof::success_value(_binding_value_32);
#line 150 "/src/package-acquisition.do"
    const auto output = doof::string_trim(::doof_blob::NativeBlobReader::constructor(result->stdout_, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((result->stdout_)->size()))));
#line 151 "/src/package-acquisition.do"
    if (result->exitCode != 0) {
#line 151 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (((command + std::string(" exited with code ")) + doof::to_string(result->exitCode)) + ((output == std::string("")) ? std::string("") : (std::string(":\n") + output))) };
    }
#line 152 "/src/package-acquisition.do"
    return doof::Success<std::string>{ output };
}
#line 155 "/src/package-acquisition.do"
doof::Result<void, std::string> ensurePackageDirectory(const std::string& path) {
#line 156 "/src/package-acquisition.do"
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
#line 156 "/src/package-acquisition.do"
        return doof::Success<void>{};
    }
#line 157 "/src/package-acquisition.do"
    const auto parent = ::std_::path::index::dirname(path);
#line 158 "/src/package-acquisition.do"
    if (parent != path) {
#line 158 "/src/package-acquisition.do"
        auto _try_value_33 = ensurePackageDirectory(parent);
        if (doof::is_failure(_try_value_33)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_33))};
    }
#line 159 "/src/package-acquisition.do"
    auto _binding_value_34 = ::doof_fs::mkdir(path);
    if (doof::is_failure(_binding_value_34)) {
#line 159 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (std::string("Could not create package acquisition directory ") + path) };
    }
#line 160 "/src/package-acquisition.do"
    return doof::Success<void>{};
}
#line 163 "/src/package-acquisition.do"
doof::Result<void, std::string> removePackageTree(const std::string& path) {
#line 164 "/src/package-acquisition.do"
    if (!::doof_fs::exists(path)) {
#line 164 "/src/package-acquisition.do"
        return doof::Success<void>{};
    }
#line 165 "/src/package-acquisition.do"
    if (::doof_fs::isDirectory(path)) {
#line 166 "/src/package-acquisition.do"
        auto _binding_value_35 = ::doof_fs::readDir(path);
        if (doof::is_failure(_binding_value_35)) {
            const auto& entries = _binding_value_35;
#line 166 "/src/package-acquisition.do"
            return doof::Failure<std::string>{ (std::string("Could not read ") + path) };
        }
        const auto entries = doof::success_value(_binding_value_35);
#line 167 "/src/package-acquisition.do"
        const auto& _iterable_37 = entries;
        for (const auto& entry : *_iterable_37) {
#line 167 "/src/package-acquisition.do"
            auto _try_value_38 = removePackageTree(::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{path, entry->name})));
            if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
        }
    }
#line 169 "/src/package-acquisition.do"
    auto _binding_value_39 = ::doof_fs::remove(path);
    if (doof::is_failure(_binding_value_39)) {
#line 169 "/src/package-acquisition.do"
        return doof::Failure<std::string>{ (std::string("Could not remove ") + path) };
    }
#line 170 "/src/package-acquisition.do"
    return doof::Success<void>{};
}
#line 1 "<doof-generated>"

void __doof_initialize_module() {
        PACKAGE_ACQUISITION_RECEIPT = std::string(".doof-acquisition.json");
}
}
