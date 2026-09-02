#include "src_stdlib_bundle.hpp"

namespace app_src_stdlib_bundle_ {
using namespace ::std_::blob::index;
using namespace ::std_::crypto::index;
using namespace ::std_::fs::index;
using namespace ::std_::json::index;
using namespace ::std_::os::index;
using namespace ::std_::path::index;
using namespace ::std_::zstd::index;
int32_t STDLIB_BUNDLE_SCHEMA_VERSION = 4;
std::string STDLIB_BUNDLE_FORMAT;
std::string STDLIB_BUNDLE_RECEIPT;

doof::Result<std::shared_ptr<StdlibBundleMember>, std::string> StdlibBundleMember::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_kind = _object->find("kind");
    if (_iterator_kind == _object->end()) { return doof::Failure<std::string>{"Missing required field \"kind\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_kind->second) : doof::json_is_string(_iterator_kind->second)))) { return doof::Failure<std::string>{"Field \"kind\" expected string but got " + std::string(doof::json_type_name(_iterator_kind->second))}; }
    auto _field_kind = doof::json_decode_at("Field \"kind\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_kind->second) : doof::json_as_string(_iterator_kind->second)); });
    auto _iterator_packageName = _object->find("packageName");
    if (_iterator_packageName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"packageName\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_packageName->second) : doof::json_is_string(_iterator_packageName->second)))) { return doof::Failure<std::string>{"Field \"packageName\" expected string but got " + std::string(doof::json_type_name(_iterator_packageName->second))}; }
    auto _field_packageName = doof::json_decode_at("Field \"packageName\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_packageName->second) : doof::json_as_string(_iterator_packageName->second)); });
    auto _iterator_path = _object->find("path");
    if (_iterator_path == _object->end()) { return doof::Failure<std::string>{"Missing required field \"path\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
    auto _field_path = doof::json_decode_at("Field \"path\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second)); });
    auto _iterator_member = _object->find("member");
    if (_iterator_member == _object->end()) { return doof::Failure<std::string>{"Missing required field \"member\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_member->second) : doof::json_is_string(_iterator_member->second)))) { return doof::Failure<std::string>{"Field \"member\" expected string but got " + std::string(doof::json_type_name(_iterator_member->second))}; }
    auto _field_member = doof::json_decode_at("Field \"member\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_member->second) : doof::json_as_string(_iterator_member->second)); });
    auto _iterator_sourceBytes = _object->find("sourceBytes");
    if (_iterator_sourceBytes == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sourceBytes\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_sourceBytes->second) : doof::json_is_number(_iterator_sourceBytes->second)))) { return doof::Failure<std::string>{"Field \"sourceBytes\" expected number but got " + std::string(doof::json_type_name(_iterator_sourceBytes->second))}; }
    auto _field_sourceBytes = doof::json_decode_at("Field \"sourceBytes\"", [&]() { return (_lenient ? doof::json_as_long_lenient(_iterator_sourceBytes->second) : doof::json_as_long(_iterator_sourceBytes->second)); });
    auto _iterator_compressedBytes = _object->find("compressedBytes");
    if (_iterator_compressedBytes == _object->end()) { return doof::Failure<std::string>{"Missing required field \"compressedBytes\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_compressedBytes->second) : doof::json_is_number(_iterator_compressedBytes->second)))) { return doof::Failure<std::string>{"Field \"compressedBytes\" expected number but got " + std::string(doof::json_type_name(_iterator_compressedBytes->second))}; }
    auto _field_compressedBytes = doof::json_decode_at("Field \"compressedBytes\"", [&]() { return (_lenient ? doof::json_as_long_lenient(_iterator_compressedBytes->second) : doof::json_as_long(_iterator_compressedBytes->second)); });
    auto _iterator_sha256 = _object->find("sha256");
    if (_iterator_sha256 == _object->end()) { return doof::Failure<std::string>{"Missing required field \"sha256\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_sha256->second) : doof::json_is_string(_iterator_sha256->second)))) { return doof::Failure<std::string>{"Field \"sha256\" expected string but got " + std::string(doof::json_type_name(_iterator_sha256->second))}; }
    auto _field_sha256 = doof::json_decode_at("Field \"sha256\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_sha256->second) : doof::json_as_string(_iterator_sha256->second)); });
        return doof::Success<std::shared_ptr<StdlibBundleMember>>{std::make_shared<StdlibBundleMember>(_field_kind, _field_packageName, _field_path, _field_member, _field_sourceBytes, _field_compressedBytes, _field_sha256)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::Result<std::shared_ptr<StdlibBundleLicenseFile>, std::string> StdlibBundleLicenseFile::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_packageName = _object->find("packageName");
    if (_iterator_packageName == _object->end()) { return doof::Failure<std::string>{"Missing required field \"packageName\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_packageName->second) : doof::json_is_string(_iterator_packageName->second)))) { return doof::Failure<std::string>{"Field \"packageName\" expected string but got " + std::string(doof::json_type_name(_iterator_packageName->second))}; }
    auto _field_packageName = doof::json_decode_at("Field \"packageName\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_packageName->second) : doof::json_as_string(_iterator_packageName->second)); });
    auto _iterator_path = _object->find("path");
    if (_iterator_path == _object->end()) { return doof::Failure<std::string>{"Missing required field \"path\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_path->second) : doof::json_is_string(_iterator_path->second)))) { return doof::Failure<std::string>{"Field \"path\" expected string but got " + std::string(doof::json_type_name(_iterator_path->second))}; }
    auto _field_path = doof::json_decode_at("Field \"path\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_path->second) : doof::json_as_string(_iterator_path->second)); });
    auto _iterator_member = _object->find("member");
    if (_iterator_member == _object->end()) { return doof::Failure<std::string>{"Missing required field \"member\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_member->second) : doof::json_is_string(_iterator_member->second)))) { return doof::Failure<std::string>{"Field \"member\" expected string but got " + std::string(doof::json_type_name(_iterator_member->second))}; }
    auto _field_member = doof::json_decode_at("Field \"member\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_member->second) : doof::json_as_string(_iterator_member->second)); });
        return doof::Success<std::shared_ptr<StdlibBundleLicenseFile>>{std::make_shared<StdlibBundleLicenseFile>(_field_packageName, _field_path, _field_member)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}

doof::Result<std::shared_ptr<StdlibBundleIndex>, std::string> StdlibBundleIndex::fromJsonValue(const doof::JsonValue& _json, bool _lenient) {
    try {
        const auto* _object = doof::json_as_object(_json);
        if (_object == nullptr) { return doof::Failure<std::string>{"Expected JSON object"}; }
    auto _iterator_schemaVersion = _object->find("schemaVersion");
    if (_iterator_schemaVersion == _object->end()) { return doof::Failure<std::string>{"Missing required field \"schemaVersion\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_schemaVersion->second) : doof::json_is_number(_iterator_schemaVersion->second)))) { return doof::Failure<std::string>{"Field \"schemaVersion\" expected number but got " + std::string(doof::json_type_name(_iterator_schemaVersion->second))}; }
    auto _field_schemaVersion = doof::json_decode_at("Field \"schemaVersion\"", [&]() { return (_lenient ? doof::json_as_int_lenient(_iterator_schemaVersion->second) : doof::json_as_int(_iterator_schemaVersion->second)); });
    auto _iterator_format = _object->find("format");
    if (_iterator_format == _object->end()) { return doof::Failure<std::string>{"Missing required field \"format\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_format->second) : doof::json_is_string(_iterator_format->second)))) { return doof::Failure<std::string>{"Field \"format\" expected string but got " + std::string(doof::json_type_name(_iterator_format->second))}; }
    auto _field_format = doof::json_decode_at("Field \"format\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_format->second) : doof::json_as_string(_iterator_format->second)); });
    auto _iterator_bundleDigest = _object->find("bundleDigest");
    if (_iterator_bundleDigest == _object->end()) { return doof::Failure<std::string>{"Missing required field \"bundleDigest\""}; }
        if (!((_lenient ? doof::json_is_lenient_string(_iterator_bundleDigest->second) : doof::json_is_string(_iterator_bundleDigest->second)))) { return doof::Failure<std::string>{"Field \"bundleDigest\" expected string but got " + std::string(doof::json_type_name(_iterator_bundleDigest->second))}; }
    auto _field_bundleDigest = doof::json_decode_at("Field \"bundleDigest\"", [&]() { return (_lenient ? doof::json_as_string_lenient(_iterator_bundleDigest->second) : doof::json_as_string(_iterator_bundleDigest->second)); });
    auto _iterator_zstdLevel = _object->find("zstdLevel");
    if (_iterator_zstdLevel == _object->end()) { return doof::Failure<std::string>{"Missing required field \"zstdLevel\""}; }
        if (!((_lenient ? doof::json_is_lenient_number(_iterator_zstdLevel->second) : doof::json_is_number(_iterator_zstdLevel->second)))) { return doof::Failure<std::string>{"Field \"zstdLevel\" expected number but got " + std::string(doof::json_type_name(_iterator_zstdLevel->second))}; }
    auto _field_zstdLevel = doof::json_decode_at("Field \"zstdLevel\"", [&]() { return (_lenient ? doof::json_as_int_lenient(_iterator_zstdLevel->second) : doof::json_as_int(_iterator_zstdLevel->second)); });
    auto _iterator_targets = _object->find("targets");
    if (_iterator_targets == _object->end()) { return doof::Failure<std::string>{"Missing required field \"targets\""}; }
        if (!(doof::json_is_array(_iterator_targets->second))) { return doof::Failure<std::string>{"Field \"targets\" expected array but got " + std::string(doof::json_type_name(_iterator_targets->second))}; }
    auto _field_targets = doof::json_decode_at("Field \"targets\"", [&]() { return [&]() { const auto* _array = doof::json_as_array(_iterator_targets->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (size_t _index = 0; _index < _array->size(); ++_index) { const auto& _element = (*_array)[_index]; _values->push_back(doof::json_decode_at(std::string("[") + doof::to_string(_index) + "]", [&]() { return (_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element)); })); } return _values; }(); });
    auto _iterator_packages = _object->find("packages");
    if (_iterator_packages == _object->end()) { return doof::Failure<std::string>{"Missing required field \"packages\""}; }
        if (!(doof::json_is_array(_iterator_packages->second))) { return doof::Failure<std::string>{"Field \"packages\" expected array but got " + std::string(doof::json_type_name(_iterator_packages->second))}; }
    auto _field_packages = doof::json_decode_at("Field \"packages\"", [&]() { return [&]() { const auto* _array = doof::json_as_array(_iterator_packages->second); auto _values = std::make_shared<std::vector<std::string>>(); _values->reserve(_array->size()); for (size_t _index = 0; _index < _array->size(); ++_index) { const auto& _element = (*_array)[_index]; _values->push_back(doof::json_decode_at(std::string("[") + doof::to_string(_index) + "]", [&]() { return (_lenient ? doof::json_as_string_lenient(_element) : doof::json_as_string(_element)); })); } return _values; }(); });
    auto _iterator_members = _object->find("members");
    if (_iterator_members == _object->end()) { return doof::Failure<std::string>{"Missing required field \"members\""}; }
        if (!(doof::json_is_array(_iterator_members->second))) { return doof::Failure<std::string>{"Field \"members\" expected array but got " + std::string(doof::json_type_name(_iterator_members->second))}; }
    auto _field_members = doof::json_decode_at("Field \"members\"", [&]() { return [&]() { const auto* _array = doof::json_as_array(_iterator_members->second); auto _values = std::make_shared<std::vector<std::shared_ptr<StdlibBundleMember>>>(); _values->reserve(_array->size()); for (size_t _index = 0; _index < _array->size(); ++_index) { const auto& _element = (*_array)[_index]; _values->push_back(doof::json_decode_at(std::string("[") + doof::to_string(_index) + "]", [&]() { return doof::json_decode_value(StdlibBundleMember::fromJsonValue(_element, _lenient)); })); } return _values; }(); });
    auto _iterator_licenseFiles = _object->find("licenseFiles");
    if (_iterator_licenseFiles == _object->end()) { return doof::Failure<std::string>{"Missing required field \"licenseFiles\""}; }
        if (!(doof::json_is_array(_iterator_licenseFiles->second))) { return doof::Failure<std::string>{"Field \"licenseFiles\" expected array but got " + std::string(doof::json_type_name(_iterator_licenseFiles->second))}; }
    auto _field_licenseFiles = doof::json_decode_at("Field \"licenseFiles\"", [&]() { return [&]() { const auto* _array = doof::json_as_array(_iterator_licenseFiles->second); auto _values = std::make_shared<std::vector<std::shared_ptr<StdlibBundleLicenseFile>>>(); _values->reserve(_array->size()); for (size_t _index = 0; _index < _array->size(); ++_index) { const auto& _element = (*_array)[_index]; _values->push_back(doof::json_decode_at(std::string("[") + doof::to_string(_index) + "]", [&]() { return doof::json_decode_value(StdlibBundleLicenseFile::fromJsonValue(_element, _lenient)); })); } return _values; }(); });
        return doof::Success<std::shared_ptr<StdlibBundleIndex>>{std::make_shared<StdlibBundleIndex>(_field_schemaVersion, _field_format, _field_bundleDigest, _field_zstdLevel, _field_targets, _field_packages, _field_members, _field_licenseFiles)};
    } catch (const doof::JsonDecodeError& _error) {
        return doof::Failure<std::string>{_error.message()};
    }
}


std::string bundlePath(const std::string& directory, const std::string& name) {
    return ::std_::path::index::join(std::make_shared<std::vector<std::string>>(std::vector<std::string>{directory, name}));
}
bool safeRelativePath(const std::string& value) {
    if (((value == std::string("")) || doof::string_startsWith(value, std::string("/"))) || doof::string_contains(value, std::string("\\"))) {
        return false;
    }
    const auto& _iterable_2 = doof::string_split(value, std::string("/"));
    for (const auto& segment : *_iterable_2) {
        if (((segment == std::string("")) || (segment == std::string("."))) || (segment == std::string(".."))) {
            return false;
        }
    }
    return true;
}
std::string packageShortName(const std::string& packageName) {
    return doof::string_substring(packageName, 4, static_cast<int32_t>(packageName.size()));
}
std::shared_ptr<::std_::archive::types::TarEntry> memberArchiveEntry(const std::shared_ptr<StdlibBundleProvider>& provider, const std::string& name) {
    const auto& _iterable_4 = provider->archiveEntries;
    for (const auto& entry : *_iterable_4) {
        if (entry->name == name) {
            return entry;
        }
    }
    return nullptr;
}
std::string canonicalBundleDigest(const std::shared_ptr<StdlibBundleIndex>& index) {
    auto canonical = std::string("schema=4\n");
    const auto& _iterable_6 = index->targets;
    for (const auto& target : *_iterable_6) {
        (canonical += ((std::string("target=") + target) + std::string("\n")));
    }
    const auto& _iterable_8 = index->packages;
    for (const auto& packageName : *_iterable_8) {
        (canonical += ((std::string("package=") + packageName) + std::string("\n")));
    }
    const auto& _iterable_10 = index->members;
    for (const auto& member : *_iterable_10) {
        (canonical += ((((((((((((((std::string("member=") + member->kind) + std::string("u0000")) + member->packageName) + std::string("u0000")) + member->path) + std::string("u0000")) + member->member) + std::string("u0000")) + doof::to_string(member->sourceBytes)) + std::string("u0000")) + doof::to_string(member->compressedBytes)) + std::string("u0000")) + member->sha256) + std::string("\n")));
    }
    const auto& _iterable_12 = index->licenseFiles;
    for (const auto& license : *_iterable_12) {
        (canonical += ((((((std::string("license=") + license->packageName) + std::string("u0000")) + license->path) + std::string("u0000")) + license->member) + std::string("\n")));
    }
    return ::std_::crypto::index::sha256HexString(canonical);
}
doof::Result<void, std::string> validateMemberShape(const std::shared_ptr<StdlibBundleMember>& member, const std::shared_ptr<std::vector<std::string>>& packages) {
    if (!doof::array_contains(packages, member->packageName, "", 0)) {
        return doof::Failure<std::string>{ (std::string("Stdlib bundle member names unknown package ") + member->packageName) };
    }
    if (static_cast<int32_t>(member->sha256.size()) != 64) {
        return doof::Failure<std::string>{ (std::string("Stdlib bundle member has invalid SHA-256: ") + member->member) };
    }
    if ((member->sourceBytes < 0LL) || (member->compressedBytes < 0LL)) {
        return doof::Failure<std::string>{ (std::string("Stdlib bundle member has invalid size: ") + member->member) };
    }
    const auto shortName = packageShortName(member->packageName);
    if (member->kind == std::string("manifest")) {
        if ((member->path != std::string("doof.json")) || (member->member != ((std::string("manifests/") + shortName) + std::string(".tar.zst")))) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle has invalid manifest member for ") + member->packageName) };
        }
    } else if (member->kind == std::string("module")) {
        if ((!safeRelativePath(member->path) || !doof::string_endsWith(member->path, std::string(".do"))) || (member->member != ((((std::string("modules/") + shortName) + std::string("/")) + member->path) + std::string(".tar.zst")))) {
            return doof::Failure<std::string>{ (((std::string("Stdlib bundle has invalid module member for ") + member->packageName) + std::string(": ")) + member->member) };
        }
    } else if (member->kind == std::string("native")) {
        if ((member->path != std::string("")) || (member->member != ((std::string("native/") + shortName) + std::string(".tar.zst")))) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle has invalid native member for ") + member->packageName) };
        }
    } else {
        return doof::Failure<std::string>{ (std::string("Stdlib bundle has unsupported member kind ") + member->kind) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> validateBundleIndex(const std::shared_ptr<StdlibBundleIndex>& index, const std::shared_ptr<std::vector<std::shared_ptr<::std_::archive::types::TarEntry>>>& entries) {
    if (index->schemaVersion != STDLIB_BUNDLE_SCHEMA_VERSION) {
        return doof::Failure<std::string>{ (std::string("Unsupported stdlib bundle schema ") + doof::to_string(index->schemaVersion)) };
    }
    if (index->format != STDLIB_BUNDLE_FORMAT) {
        return doof::Failure<std::string>{ (std::string("Unsupported stdlib bundle format ") + index->format) };
    }
    if (static_cast<int32_t>((index->targets)->size()) == 0) {
        return doof::Failure<std::string>{ std::string("Stdlib bundle must support at least one target") };
    }
    auto previousTarget = std::string("");
    auto supportedTargets = std::make_shared<std::vector<std::string>>(std::vector<std::string>{std::string("ios-device"), std::string("ios-simulator"), std::string("linux"), std::string("macos"), std::string("wasm"), std::string("windows")});
    const auto& _iterable_14 = index->targets;
    for (const auto& target : *_iterable_14) {
        if (!doof::array_contains(supportedTargets, target, "", 0) || ((previousTarget != std::string("")) && (target <= previousTarget))) {
            return doof::Failure<std::string>{ std::string("Stdlib bundle target list must contain sorted unique supported targets") };
        }
        (previousTarget = target);
    }
    if ((static_cast<int32_t>(index->bundleDigest.size()) != 64) || (canonicalBundleDigest(index) != index->bundleDigest)) {
        return doof::Failure<std::string>{ std::string("Stdlib bundle digest is invalid") };
    }
    auto previousPackage = std::string("");
    const auto& _iterable_16 = index->packages;
    for (const auto& packageName : *_iterable_16) {
        if ((!doof::string_startsWith(packageName, std::string("std/")) || doof::string_contains(doof::string_substring(packageName, 4, static_cast<int32_t>(packageName.size())), std::string("/"))) || ((previousPackage != std::string("")) && (packageName <= previousPackage))) {
            return doof::Failure<std::string>{ std::string("Stdlib bundle package list must contain sorted unique std package names") };
        }
        (previousPackage = packageName);
    }
    std::shared_ptr<std::vector<std::string>> seenOuter = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_18 = entries;
    for (const auto& entry : *_iterable_18) {
        if (entry->kind != ::std_::archive::types::TarEntryKind::File) {
            return doof::Failure<std::string>{ std::string("Stdlib bundle outer archive may contain files only") };
        }
        if (doof::array_contains(seenOuter, entry->name, "", 0)) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle has duplicate outer member ") + entry->name) };
        }
        seenOuter->push_back(entry->name);
    }
    if (((static_cast<int32_t>((entries)->size()) != (static_cast<int32_t>((index->members)->size()) + 1)) || (static_cast<int32_t>((entries)->size()) == 0)) || (doof::array_at(entries, 0, "src/stdlib-bundle", 148)->name != std::string("bundle-index.json"))) {
        return doof::Failure<std::string>{ std::string("Stdlib bundle outer archive does not match its index") };
    }
    std::shared_ptr<std::vector<std::string>> seenMembers = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_22 = index->packages;
    for (const auto& packageName : *_iterable_22) {
        auto manifestCount = 0;
        const auto& _iterable_20 = index->members;
        for (const auto& member : *_iterable_20) {
            if ((member->packageName == packageName) && (member->kind == std::string("manifest"))) {
                (manifestCount += 1);
            }
        }
        if (manifestCount != 1) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle requires one manifest for ") + packageName) };
        }
    }
    const auto& _iterable_25 = index->members;
    for (const auto& member : *_iterable_25) {
        auto _try_value_23 = validateMemberShape(member, index->packages);
        if (doof::is_failure(_try_value_23)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_23))};
        if (doof::array_contains(seenMembers, member->member, "", 0)) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle index duplicates member ") + member->member) };
        }
        seenMembers->push_back(member->member);
        const auto entry = memberArchiveEntry(std::make_shared<StdlibBundleProvider>(std::string(""), index, entries), member->member);
        if (doof::is_null(entry) || (entry->size != member->compressedBytes)) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle member is missing or has the wrong size: ") + member->member) };
        }
    }
    std::shared_ptr<std::vector<std::string>> seenLicenses = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    const auto& _iterable_29 = index->licenseFiles;
    for (const auto& license : *_iterable_29) {
        if ((!doof::array_contains(index->packages, license->packageName, "", 0) || !safeRelativePath(license->path)) || (license->member != ((std::string("native/") + packageShortName(license->packageName)) + std::string(".tar.zst")))) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle has invalid license entry for ") + license->packageName) };
        }
        const auto licenseKey = ((license->packageName + std::string("u0000")) + license->path);
        if (doof::array_contains(seenLicenses, licenseKey, "", 0)) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle duplicates required license ") + license->path) };
        }
        seenLicenses->push_back(licenseKey);
        auto hasNativeMember = false;
        const auto& _iterable_27 = index->members;
        for (const auto& member : *_iterable_27) {
            if (((member->packageName == license->packageName) && (member->kind == std::string("native"))) && (member->member == license->member)) {
                (hasNativeMember = true);
            }
        }
        if (!hasNativeMember) {
            return doof::Failure<std::string>{ (std::string("Stdlib bundle license member is missing for ") + license->packageName) };
        }
    }
    return doof::Success<void>{};
}
doof::Result<std::shared_ptr<StdlibBundleProvider>, std::string> openStdlibBundle(const std::string& path) {
    auto _binding_value_30 = ::std_::archive::tar_file_reader::scanTarFile(path);
    if (doof::is_failure(_binding_value_30)) {
        const auto error = doof::failure_error(_binding_value_30);
        return doof::Failure<std::string>{ (std::string("Could not scan bundled stdlib: ") + error) };
    }
    const auto entries = doof::success_value(_binding_value_30);
    if ((static_cast<int32_t>((entries)->size()) == 0) || (doof::array_at(entries, 0, "src/stdlib-bundle", 191)->name != std::string("bundle-index.json"))) {
        return doof::Failure<std::string>{ std::string("Bundled stdlib is missing bundle-index.json") };
    }
    auto _binding_value_31 = ::std_::archive::tar_file_reader::readTarEntry(path, doof::array_at(entries, 0, "src/stdlib-bundle", 194));
    if (doof::is_failure(_binding_value_31)) {
        const auto error = doof::failure_error(_binding_value_31);
        return doof::Failure<std::string>{ (std::string("Could not read bundled stdlib index: ") + error) };
    }
    const auto indexData = doof::success_value(_binding_value_31);
    const auto indexText = ::doof_blob::NativeBlobReader::constructor(indexData, ::std_::blob::types::Endian::LittleEndian)->readString(static_cast<int64_t>(static_cast<int32_t>((indexData)->size())));
    auto _binding_value_32 = ::doof_json::parse(indexText);
    if (doof::is_failure(_binding_value_32)) {
        const auto error = doof::failure_error(_binding_value_32);
        return doof::Failure<std::string>{ (std::string("Invalid bundled stdlib index: ") + error) };
    }
    const auto parsed = doof::success_value(_binding_value_32);
    auto _binding_value_33 = StdlibBundleIndex::fromJsonValue(parsed, true);
    if (doof::is_failure(_binding_value_33)) {
        const auto error = doof::failure_error(_binding_value_33);
        return doof::Failure<std::string>{ (std::string("Invalid bundled stdlib index: ") + error) };
    }
    const auto index = doof::success_value(_binding_value_33);
    auto _try_value_34 = validateBundleIndex(index, entries);
    if (doof::is_failure(_try_value_34)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_34))};
    return doof::Success<std::shared_ptr<StdlibBundleProvider>>{ std::make_shared<StdlibBundleProvider>(path, index, entries) };
}
doof::Result<void, std::string> ensureDirectory(const std::string& path) {
    if ((path == std::string("")) || ::doof_fs::exists(path)) {
        return doof::Success<void>{};
    }
    const auto parent = ::std_::path::index::dirname(path);
    if (parent != path) {
        auto _try_value_35 = ensureDirectory(parent);
        if (doof::is_failure(_try_value_35)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_35))};
    }
    auto _binding_value_36 = ::doof_fs::mkdir(path);
    if (doof::is_failure(_binding_value_36)) {
        return doof::Failure<std::string>{ (std::string("Could not create stdlib bundle directory ") + path) };
    }
    return doof::Success<void>{};
}
doof::Result<void, std::string> removeTree(const std::string& path) {
    if (!::doof_fs::exists(path)) {
        return doof::Success<void>{};
    }
    if (::doof_fs::isDirectory(path)) {
        auto _binding_value_37 = ::doof_fs::readDir(path);
        if (doof::is_failure(_binding_value_37)) {
            const auto& entries = _binding_value_37;
            return doof::Failure<std::string>{ (std::string("Could not read ") + path) };
        }
        const auto entries = doof::success_value(_binding_value_37);
        const auto& _iterable_40 = entries;
        for (const auto& entry : *_iterable_40) {
            auto _try_value_38 = removeTree(bundlePath(path, entry->name));
            if (doof::is_failure(_try_value_38)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_38))};
        }
    }
    auto _binding_value_41 = ::doof_fs::remove(path);
    if (doof::is_failure(_binding_value_41)) {
        return doof::Failure<std::string>{ (std::string("Could not remove ") + path) };
    }
    return doof::Success<void>{};
}
std::optional<std::string> permissionText(int32_t mode) {
    if (mode == 420) {
        return std::string("644");
    }
    if (mode == 493) {
        return std::string("755");
    }
    return std::nullopt;
}
doof::Result<void, std::string> applyMode(const std::string& path, int32_t mode) {
    if (::std_::os::index::platform() == std::string("windows")) {
        return doof::Success<void>{};
    }
    const auto text = permissionText(mode);
    if (doof::is_null(text)) {
        return doof::Failure<std::string>{ (((std::string("Bundled stdlib entry has unsupported file mode ") + doof::to_string(mode)) + std::string(": ")) + path) };
    }
    auto _binding_value_42 = ::std_::os::index::run(std::string("chmod"), std::make_shared<std::vector<std::string>>(std::vector<std::string>{text.value(), path}), std::make_shared<::std_::os::index::ExecOptions>(std::nullopt, std::make_shared<doof::ordered_map<std::string, std::string>>(std::initializer_list<std::pair<std::string, std::string>>{}), true, false, true, false, ::std_::os::index::ProcessGroupMode::Isolated, std::nullopt, nullptr));
    if (doof::is_failure(_binding_value_42)) {
        const auto error = doof::failure_error(_binding_value_42);
        return doof::Failure<std::string>{ (((std::string("Could not set bundled stdlib permissions for ") + path) + std::string(": ")) + error) };
    }
    const auto result = doof::success_value(_binding_value_42);
    if (result->exitCode != 0) {
        return doof::Failure<std::string>{ (std::string("Could not set bundled stdlib permissions for ") + path) };
    }
    return doof::Success<void>{};
}
bool receiptMatches(const std::string& path, const std::shared_ptr<StdlibBundleProvider>& provider, const std::string& packageName) {
    auto _binding_value_43 = ::doof_fs::readText(path);
    if (doof::is_failure(_binding_value_43)) {
        const auto& source = _binding_value_43;
        return false;
    }
    const auto source = doof::success_value(_binding_value_43);
    auto _binding_value_44 = ::doof_json::parse(source);
    if (doof::is_failure(_binding_value_44)) {
        const auto& parsed = _binding_value_44;
        return false;
    }
    const auto parsed = doof::success_value(_binding_value_44);
    auto _binding_value_45 = [&]() -> doof::Result<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>, std::string> { auto _as_value = parsed; if (doof::json_is_object(_as_value)) return doof::Success<std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>>>{doof::json_object(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_45)) {
        const auto& object = _binding_value_45;
        return false;
    }
    const auto object = doof::success_value(_binding_value_45);
    auto _binding_value_46 = doof::map_get(object, std::string("bundleDigest"), "", 0);
    if (doof::is_failure(_binding_value_46)) {
        const auto& digestValue = _binding_value_46;
        return false;
    }
    const auto digestValue = doof::success_value(_binding_value_46);
    auto _binding_value_47 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = digestValue; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_47)) {
        const auto& digest = _binding_value_47;
        return false;
    }
    const auto digest = doof::success_value(_binding_value_47);
    auto _binding_value_48 = doof::map_get(object, std::string("packageName"), "", 0);
    if (doof::is_failure(_binding_value_48)) {
        const auto& packageValue = _binding_value_48;
        return false;
    }
    const auto packageValue = doof::success_value(_binding_value_48);
    auto _binding_value_49 = [&]() -> doof::Result<std::string, std::string> { auto _as_value = packageValue; if (doof::json_is_string(_as_value)) return doof::Success<std::string>{doof::json_as_string(_as_value)}; return doof::Failure<std::string>{"JsonValue narrowing failed"}; }();
    if (doof::is_failure(_binding_value_49)) {
        const auto& recordedPackage = _binding_value_49;
        return false;
    }
    const auto recordedPackage = doof::success_value(_binding_value_49);
    return ((digest == provider->index->bundleDigest) && (recordedPackage == packageName));
}
std::string receiptSource(const std::shared_ptr<StdlibBundleProvider>& provider, const std::string& packageName) {
    std::shared_ptr<doof::ordered_map<std::string, doof::JsonValue>> value = std::make_shared<doof::ordered_map<std::string, doof::JsonValue>>(std::initializer_list<std::pair<std::string, doof::JsonValue>>{});
    doof::map_set(value, std::string("schemaVersion"), doof::json_value(1), "", 0);
    doof::map_set(value, std::string("bundleDigest"), doof::json_value(provider->index->bundleDigest), "", 0);
    doof::map_set(value, std::string("packageName"), doof::json_value(packageName), "", 0);
    return (::doof_json::format(doof::json_value(value)) + std::string("\n"));
}
doof::Result<std::shared_ptr<std::vector<uint8_t>>, std::string> readCompressedMember(const std::shared_ptr<StdlibBundleProvider>& provider, const std::shared_ptr<StdlibBundleMember>& member) {
    const auto entry = memberArchiveEntry(provider, member->member);
    if (doof::is_null(entry)) {
        return doof::Failure<std::string>{ (std::string("Bundled stdlib member is missing: ") + member->member) };
    }
    auto _binding_value_50 = ::std_::archive::tar_file_reader::readTarEntry(provider->path, doof::unwrap_optional(entry));
    if (doof::is_failure(_binding_value_50)) {
        const auto error = doof::failure_error(_binding_value_50);
        return doof::Failure<std::string>{ (((std::string("Could not read bundled stdlib member ") + member->member) + std::string(": ")) + error) };
    }
    const auto data = doof::success_value(_binding_value_50);
    if (::std_::crypto::index::sha256Hex(data) != member->sha256) {
        return doof::Failure<std::string>{ (std::string("Bundled stdlib member failed SHA-256 validation: ") + member->member) };
    }
    return doof::Success<std::shared_ptr<std::vector<uint8_t>>>{ data };
}
doof::Result<void, std::string> materializeInnerArchive(const std::shared_ptr<StdlibBundleProvider>& provider, const std::shared_ptr<StdlibBundleMember>& member, const std::string& staging, const std::shared_ptr<std::vector<std::string>>& writtenPaths) {
    auto _try_value_51 = readCompressedMember(provider, member);
    if (doof::is_failure(_try_value_51)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_51))};
    const auto compressed = doof::success_value(_try_value_51);
    auto _binding_value_52 = ::doof_zstd::decompress(compressed);
    if (doof::is_failure(_binding_value_52)) {
        const auto error = doof::failure_error(_binding_value_52);
        return doof::Failure<std::string>{ (((std::string("Could not decompress bundled stdlib member ") + member->member) + std::string(": ")) + error) };
    }
    const auto innerData = doof::success_value(_binding_value_52);
    auto _binding_value_53 = ::std_::archive::tar_reader::readTarBlob(innerData);
    if (doof::is_failure(_binding_value_53)) {
        const auto error = doof::failure_error(_binding_value_53);
        return doof::Failure<std::string>{ (((std::string("Could not read bundled stdlib member ") + member->member) + std::string(": ")) + error) };
    }
    const auto archive = doof::success_value(_binding_value_53);
    if ((member->kind != std::string("native")) && (static_cast<int32_t>((archive->entries)->size()) != 1)) {
        return doof::Failure<std::string>{ (((std::string("Bundled stdlib ") + member->kind) + std::string(" member must contain exactly one file: ")) + member->member) };
    }
    auto sourceBytes = 0LL;
    const auto& _iterable_58 = archive->entries;
    for (const auto& entry : *_iterable_58) {
        if ((entry->kind != ::std_::archive::types::TarEntryKind::File) || !safeRelativePath(entry->name)) {
            return doof::Failure<std::string>{ (std::string("Bundled stdlib inner archive contains an unsafe entry: ") + entry->name) };
        }
        if ((member->kind != std::string("native")) && (entry->name != member->path)) {
            return doof::Failure<std::string>{ (std::string("Bundled stdlib member path does not match its index: ") + member->member) };
        }
        if (doof::array_contains(writtenPaths, entry->name, "", 0)) {
            return doof::Failure<std::string>{ (std::string("Bundled stdlib package duplicates path ") + entry->name) };
        }
        (sourceBytes += entry->size);
        writtenPaths->push_back(entry->name);
        const auto outputPath = bundlePath(staging, entry->name);
        auto _try_value_54 = ensureDirectory(::std_::path::index::dirname(outputPath));
        if (doof::is_failure(_try_value_54)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_54))};
        auto _binding_value_55 = ::doof_fs::writeBlob(outputPath, archive->entryData(entry));
        if (doof::is_failure(_binding_value_55)) {
            return doof::Failure<std::string>{ (std::string("Could not write bundled stdlib file ") + outputPath) };
        }
        auto _try_value_56 = applyMode(outputPath, entry->mode);
        if (doof::is_failure(_try_value_56)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_56))};
    }
    if (sourceBytes != member->sourceBytes) {
        return doof::Failure<std::string>{ (std::string("Bundled stdlib member source size does not match its index: ") + member->member) };
    }
    return doof::Success<void>{};
}
std::string packageCacheRoot(const std::string& packagesRoot, const std::shared_ptr<StdlibBundleProvider>& provider, const std::string& targetKey, const std::string& packageName) {
    return bundlePath(bundlePath(bundlePath(bundlePath(packagesRoot, std::string("stdlib-bundles")), provider->index->bundleDigest), targetKey), packageShortName(packageName));
}
doof::Result<std::shared_ptr<MaterializedStdlibPackage>, std::string> materializeStdlibBundlePackage(const std::shared_ptr<StdlibBundleProvider>& provider, const std::string& packageName, const std::string& packagesRoot, const std::string& targetKey, const std::string& nativeTarget) {
    if (!doof::array_contains(provider->index->packages, packageName, "", 0)) {
        return doof::Failure<std::string>{ (std::string("Unknown standard package ") + packageName) };
    }
    if (!doof::array_contains(provider->index->targets, nativeTarget, "", 0)) {
        return doof::Failure<std::string>{ (std::string("Bundled standard library does not support target ") + nativeTarget) };
    }
    if (static_cast<int32_t>(targetKey.size()) != 64) {
        return doof::Failure<std::string>{ std::string("Invalid stdlib bundle target key") };
    }
    const auto root = packageCacheRoot(packagesRoot, provider, targetKey, packageName);
    const auto receiptPath = bundlePath(root, STDLIB_BUNDLE_RECEIPT);
    if (::doof_fs::isDirectory(root) && receiptMatches(receiptPath, provider, packageName)) {
        return doof::Success<std::shared_ptr<MaterializedStdlibPackage>>{ std::make_shared<MaterializedStdlibPackage>(root, provider->index->bundleDigest) };
    }
    auto _try_value_59 = ensureDirectory(::std_::path::index::dirname(root));
    if (doof::is_failure(_try_value_59)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_59))};
    if (::doof_fs::exists(root)) {
        if (::doof_fs::isDirectory(root) && receiptMatches(receiptPath, provider, packageName)) {
            return doof::Success<std::shared_ptr<MaterializedStdlibPackage>>{ std::make_shared<MaterializedStdlibPackage>(root, provider->index->bundleDigest) };
        }
        const auto displaced = ((root + std::string(".invalid-")) + doof::to_string(::std_::os::index::pid()));
        if (::doof_fs::exists(displaced)) {
            auto _try_value_60 = removeTree(displaced);
            if (doof::is_failure(_try_value_60)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_60))};
        }
        auto _binding_value_61 = ::doof_fs::rename(root, displaced);
        if (doof::is_failure(_binding_value_61)) {
            if (::doof_fs::isDirectory(root) && receiptMatches(receiptPath, provider, packageName)) {
                return doof::Success<std::shared_ptr<MaterializedStdlibPackage>>{ std::make_shared<MaterializedStdlibPackage>(root, provider->index->bundleDigest) };
            }
            return doof::Failure<std::string>{ (std::string("Could not replace incomplete bundled stdlib package ") + packageName) };
        }
        auto _try_value_62 = removeTree(displaced);
        if (doof::is_failure(_try_value_62)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_62))};
    }
    const auto staging = ((root + std::string(".staging-")) + doof::to_string(::std_::os::index::pid()));
    if (::doof_fs::exists(staging)) {
        auto _try_value_63 = removeTree(staging);
        if (doof::is_failure(_try_value_63)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_63))};
    }
    auto _try_value_64 = ensureDirectory(staging);
    if (doof::is_failure(_try_value_64)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_64))};
    std::shared_ptr<std::vector<std::string>> writtenPaths = std::make_shared<std::vector<std::string>>(std::vector<std::string>{});
    auto selectedMembers = 0;
    const auto& _iterable_68 = provider->index->members;
    for (const auto& member : *_iterable_68) {
        if (member->packageName != packageName) {
            continue;
        }
        (selectedMembers += 1);
        auto _binding_value_65 = materializeInnerArchive(provider, member, staging, writtenPaths);
        if (doof::is_failure(_binding_value_65)) {
            const auto error = doof::failure_error(_binding_value_65);
            auto _try_value_66 = removeTree(staging);
            if (doof::is_failure(_try_value_66)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_66))};
            return doof::Failure<std::string>{ error };
        }
    }
    if ((selectedMembers == 0) || !doof::array_contains(writtenPaths, std::string("doof.json"), "", 0)) {
        auto _try_value_69 = removeTree(staging);
        if (doof::is_failure(_try_value_69)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_69))};
        return doof::Failure<std::string>{ (std::string("Bundled stdlib has no materializable package ") + packageName) };
    }
    const auto& _iterable_72 = provider->index->licenseFiles;
    for (const auto& license : *_iterable_72) {
        if ((license->packageName == packageName) && !doof::array_contains(writtenPaths, license->path, "", 0)) {
            auto _try_value_70 = removeTree(staging);
            if (doof::is_failure(_try_value_70)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_70))};
            return doof::Failure<std::string>{ (std::string("Bundled stdlib package is missing required license ") + license->path) };
        }
    }
    auto _binding_value_73 = ::doof_fs::writeText(bundlePath(staging, STDLIB_BUNDLE_RECEIPT), receiptSource(provider, packageName));
    if (doof::is_failure(_binding_value_73)) {
        auto _try_value_74 = removeTree(staging);
        if (doof::is_failure(_try_value_74)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_74))};
        return doof::Failure<std::string>{ (std::string("Could not write bundled stdlib receipt for ") + packageName) };
    }
    auto _binding_value_75 = ::doof_fs::rename(staging, root);
    if (doof::is_failure(_binding_value_75)) {
        if (::doof_fs::isDirectory(root) && receiptMatches(receiptPath, provider, packageName)) {
            auto _try_value_76 = removeTree(staging);
            if (doof::is_failure(_try_value_76)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_76))};
        } else {
            auto _try_value_77 = removeTree(staging);
            if (doof::is_failure(_try_value_77)) return doof::Failure<std::string>{doof::variant_promote<std::string>(doof::failure_error(_try_value_77))};
            return doof::Failure<std::string>{ (std::string("Could not finalize bundled stdlib package ") + packageName) };
        }
    }
    return doof::Success<std::shared_ptr<MaterializedStdlibPackage>>{ std::make_shared<MaterializedStdlibPackage>(root, provider->index->bundleDigest) };
}
std::string stdlibBundleTargetKey(const std::string& nativeTarget, const std::string& sdkPath, const std::string& targetTriple, const std::string& configureHost) {
    return ::std_::crypto::index::sha256HexString(((((((((std::string("schema=1\ntarget=") + nativeTarget) + std::string("\nsdk=")) + sdkPath) + std::string("\ntriple=")) + targetTriple) + std::string("\nhost=")) + configureHost) + std::string("\n")));
}

void __doof_initialize_module() {
        STDLIB_BUNDLE_FORMAT = std::string("doof-stdlib-tar-of-tar-zst");
        STDLIB_BUNDLE_RECEIPT = std::string(".doof-stdlib-bundle.json");
}
}
